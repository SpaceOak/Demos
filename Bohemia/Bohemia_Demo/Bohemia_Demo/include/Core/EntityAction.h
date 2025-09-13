// ============================================================
// File: include/Core/EntityAction.h
// ============================================================

#pragma once
#include <string>
#include "Core/Object.h"

namespace gp {

    /// @brief Visibility state passed to actions when filtering.
    struct VisibilityQuery {
        bool hasKey{ false };   ///< Player has a key.
        bool isOpen{ false };   ///< Target is currently open.
        bool isLocked{ false }; ///< Target is currently locked.
    };

    class EntityActionManager; // fwd

    /**
     * @brief Base class for actions attached to an Entity.
     *
     * Defines name/visibility/execute interface. Registration with the
     * manager is performed by concrete actions (in their ctor/dtor).
     */
    class EntityAction : public Object {
    public:
        /// Bind action to owning entity (no registration here).
        using Object::Object;
        virtual ~EntityAction() = default;

        /// @return Display name (e.g., "Open", "Lockpick").
        virtual std::string Name() const = 0;

        /**
         * @brief Visibility predicate for UI/interaction queries.
         * Default returns true (override in concrete actions).
         */
        virtual bool CanBeVisible(const VisibilityQuery& q) const { (void)q; return true; }

        /// @brief Execute the action (default no-op; override as needed).
        virtual void Execute() {}
    };

} // namespace gp
