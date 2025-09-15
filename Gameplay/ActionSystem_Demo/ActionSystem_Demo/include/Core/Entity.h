// ============================================================
// File: include/Core/Entity.h
// ============================================================

#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include "Core/EntityActionManager.h"

namespace gp {

    /**
     * @brief Game entity that owns actions and exposes an action manager.
     *
     * Owns actions via unique_ptr and guarantees safe RAII unregister:
     * actions are destroyed before the manager (see members' order).
     */
    class Entity {
    public:
        /// Initialize action manager bound to this entity.
        Entity() : actions_(*this) {}
        ~Entity() = default;

        // Disable copy/move to keep registration lifecycle trivial.
        Entity(const Entity&) = delete;
        Entity& operator=(const Entity&) = delete;
        Entity(Entity&&) = delete;
        Entity& operator=(Entity&&) = delete;

        /**
         * @brief Create and own a new action of type TAction.
         * @tparam TAction Must derive from EntityAction.
         * @tparam Args Forwarded to TAction constructor (expects (Entity&, EntityActionManager&, ...)).
         * @return Reference to the created action.
         */
        template <class TAction, class... Args>
        TAction& AddAction(Args&&... args) {
            static_assert(std::is_base_of_v<EntityAction, TAction>, "TAction must derive from EntityAction");
            auto up = std::make_unique<TAction>(*this, actions_, std::forward<Args>(args)...);
            auto& ref = *up;
            actionsOwner_.push_back(std::move(up));
            return ref;
        }

        /// @return Action manager (mutable).
        EntityActionManager& Actions() { return actions_; }
        /// @return Action manager (const).
        const EntityActionManager& Actions() const { return actions_; }

    private:
        // IMPORTANT: manager declared before owning vector, so during destruction
        // actions (owned) are destroyed first -> they Unregister() while manager is still alive.
        EntityActionManager actions_;
        std::vector<std::unique_ptr<EntityAction>> actionsOwner_{};
    };

} // namespace gp
