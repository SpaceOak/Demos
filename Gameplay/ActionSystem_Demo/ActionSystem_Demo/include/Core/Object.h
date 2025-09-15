// ============================================================
// File: include/Core/Object.h
// ============================================================

#pragma once
#include <utility>

namespace gp {

    class Entity; // fwd

    /**
     * @brief Lightweight base for objects tied to an Entity context.
     *
     * Holds a non-owning reference to the owner entity and disables
     * copy/move to avoid accidental dangling registrations.
     */
    class Object {
    public:
        /// Bind this object to an owning entity context.
        explicit Object(Entity& owner) : owner_(owner) {}
        virtual ~Object() = default;

        /// @return Owning entity.
        Entity& Owner() const { return owner_; }

        // No copy/move to avoid dangling registrations in managers.
        Object(const Object&) = delete;
        Object& operator=(const Object&) = delete;
        Object(Object&&) = delete;
        Object& operator=(Object&&) = delete;

    protected:
        Entity& owner_; ///< Non-owning reference to owning entity.
    };

} // namespace gp
