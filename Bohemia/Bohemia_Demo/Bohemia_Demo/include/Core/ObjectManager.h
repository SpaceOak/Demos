// ============================================================
// File: include/Core/ObjectManager.h
// ============================================================

#pragma once
#include <unordered_map>
#include "Core/SlotMap.h"

namespace gp {

    class Entity; // fwd

    /**
     * @brief Generic non-owning registry for T.
     *
     * Objects self-register/unregister (RAII) and the manager stores pointers.
     * Provides iteration and broadcast invocation utilities.
     */
    template <typename T>
    class ObjectManager {
    public:
        /// Construct a manager bound to an owning entity context.
        explicit ObjectManager(Entity& owner) : owner_(owner) {}
        virtual ~ObjectManager() = default;

        /// Register an object instance (expects one-time call per lifetime).
        void Register(T& obj) {
            auto h = storage_.insert(&obj);
            handles_[&obj] = h;
        }

        /// Unregister an object instance (safe from object destructor).
        void Unregister(T& obj) {
            auto it = handles_.find(&obj);
            if (it != handles_.end()) {
                storage_.erase(it->second);
                handles_.erase(it);
            }
        }

        /**
         * @brief Visit all registered objects.
         * @tparam Fn Callable like void(T&).
         */
        template <class Fn>
        void ForEach(Fn&& fn) {
            storage_.for_each([&](T& t) { fn(t); });
        }

        /**
         * @brief Invoke a member function on all objects.
         * @tparam Method pointer-to-member, e.g. &T::Execute
         */
        template <typename Method, typename... Args>
        void CallAll(Method memfn, Args&&... args) {
            ForEach([&](T& t) { (t.*memfn)(std::forward<Args>(args)...); });
        }

        /// @return Owning entity context.
        Entity& Owner() const { return owner_; }

    protected:
        Entity& owner_; ///< Owning context (non-owning reference).
        SlotMap<T> storage_{}; ///< Slots of non-owning pointers.
        std::unordered_map<T*, typename SlotMap<T>::Handle> handles_{}; ///< Reverse map for fast erase.
    };

} // namespace gp
