// ============================================================
// File: include/Core/SlotMap.h
// ============================================================

#pragma once
#include <cstdint>
#include <vector>
#include <limits>
#include <utility>
#include <type_traits>

namespace gp {

    /**
     * @brief Minimal pointer slot-map storing non-owning T*.
     *
     * Stable handles + O(1) insert/erase on average. Not thread-safe.
     * The container does not own elements; callers manage lifetime.
     * @tparam T Element type (must NOT be a reference type).
     */
    template <typename T>
    class SlotMap {
        static_assert(!std::is_reference_v<T>, "SlotMap<T> expects T to be a non-reference type");
    public:
        /// Opaque stable handle for elements inside the slot map.
        struct Handle { uint32_t idx{ std::numeric_limits<uint32_t>::max() }; uint32_t gen{}; };

        /**
         * @brief Insert a non-owning pointer and return its handle.
         * @param ptr Pointer to an externally-owned object (must remain alive).
         * @return Stable handle (invalidated after erase or reuse).
         */
        Handle insert(T* ptr) {
            uint32_t idx;
            if (freeHead_ != npos) {
                idx = freeHead_;
                freeHead_ = slots_[idx].nextFree;
                auto& s = slots_[idx];
                s.ptr = ptr; s.alive = true; ++s.gen; s.nextFree = npos;
            }
            else {
                idx = static_cast<uint32_t>(slots_.size());
                slots_.push_back({ ptr, 0u, npos, true });
            }
            return { idx, slots_[idx].gen };
        }

        /**
         * @brief Erase an element by handle (idempotent for stale/invalid handles).
         * @return true if erased, false if handle was invalid/stale.
         */
        bool erase(Handle h) {
            if (!is_valid(h)) return false;
            auto& s = slots_[h.idx];
            s.ptr = nullptr; s.alive = false; s.nextFree = freeHead_; freeHead_ = h.idx; ++s.gen;
            return true;
        }

        /**
         * @brief Resolve handle to pointer.
         * @return T* if valid; nullptr otherwise.
         */
        T* get(Handle h) const { return is_valid(h) ? slots_[h.idx].ptr : nullptr; }

        /**
         * @brief Visit all alive elements.
         * @tparam Fn Callable like void(T&).
         */
        template <class Fn>
        void for_each(Fn&& fn) {
            for (auto& s : slots_) if (s.alive && s.ptr) fn(*s.ptr);
        }

        /// @brief Count alive (non-null) entries (for diagnostics/testing).
        size_t size_alive() const {
            size_t n = 0; for (auto& s : slots_) if (s.alive && s.ptr) ++n; return n;
        }

    private:
        struct Slot { T* ptr{}; uint32_t gen{}; uint32_t nextFree{ npos }; bool alive{}; };

        /// @brief Validate handle against current slot state/generation.
        bool is_valid(Handle h) const {
            return h.idx < slots_.size() && slots_[h.idx].alive && slots_[h.idx].gen == h.gen;
        }

        static constexpr uint32_t npos = std::numeric_limits<uint32_t>::max();
        std::vector<Slot> slots_{};
        uint32_t freeHead_{ npos };
    };

} // namespace gp
