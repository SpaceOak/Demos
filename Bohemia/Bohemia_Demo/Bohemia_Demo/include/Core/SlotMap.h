#pragma once
#include <cstdint>
#include <vector>
#include <limits>
#include <utility>
#include <type_traits>

namespace gp {


	// A minimal pointer slot-map that stores non-owning T*.
	// Provides stable handles and O(1) insert/erase on average.
	// Not thread-safe.
	template <typename T>
	class SlotMap {
		static_assert(!std::is_reference_v<T>, "SlotMap<T> expects T to be a non-reference type");
	public:
		struct Handle { uint32_t idx{ std::numeric_limits<uint32_t>::max() }; uint32_t gen{}; };


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


		bool erase(Handle h) {
			if (!is_valid(h)) return false;
			auto& s = slots_[h.idx];
			s.ptr = nullptr; s.alive = false; s.nextFree = freeHead_; freeHead_ = h.idx; ++s.gen;
			return true;
		}


		T* get(Handle h) const {
			return is_valid(h) ? slots_[h.idx].ptr : nullptr;
		}


		template <class Fn>
		void for_each(Fn&& fn) {
			for (auto& s : slots_) if (s.alive && s.ptr) fn(*s.ptr);
		}


		size_t size_alive() const {
			size_t n = 0; for (auto& s : slots_) if (s.alive && s.ptr) ++n; return n;
		}


	private:
		struct Slot { T* ptr{}; uint32_t gen{}; uint32_t nextFree{ npos }; bool alive{}; };


		bool is_valid(Handle h) const {
			return h.idx < slots_.size() && slots_[h.idx].alive && slots_[h.idx].gen == h.gen;
		}


		static constexpr uint32_t npos = std::numeric_limits<uint32_t>::max();
		std::vector<Slot> slots_{};
		uint32_t freeHead_{ npos };
	};


} // namespace gp