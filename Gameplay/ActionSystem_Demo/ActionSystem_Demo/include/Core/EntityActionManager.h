// ============================================================
// File: include/Core/EntityActionManager.h
// ============================================================

#pragma once
#include <vector>
#include "Core/ObjectManager.h"
#include "Core/EntityAction.h"

namespace gp {

    /**
     * @brief Manager for actions of a specific Entity.
     *
     * Extends ObjectManager<EntityAction> with visibility filtering.
     */
    class EntityActionManager : public ObjectManager<EntityAction> {
    public:
        using ObjectManager::ObjectManager; ///< Reuse ctor(Entity&).

        /**
         * @brief Collect actions visible under a given query.
         * @return Non-owning pointers valid while actions stay registered.
         */
        std::vector<EntityAction*> Visible(const VisibilityQuery& q) {
            std::vector<EntityAction*> out;
            this->ForEach([&](EntityAction& a) { if (a.CanBeVisible(q)) out.push_back(&a); });
            return out;
        }
    };

} // namespace gp
