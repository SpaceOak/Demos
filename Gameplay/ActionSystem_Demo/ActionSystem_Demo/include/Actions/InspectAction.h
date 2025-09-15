// ============================================================
// File: include/Actions/InspectAction.h
// ============================================================

#pragma once
#include "Core/EntityAction.h"
#include "Core/EntityActionManager.h"
#include <iostream>

namespace gp {

    /**
     * @brief Action that inspects an entity (always visible in this demo).
     *
     * Prints a short description to stdout. Useful to differentiate the
     * Chest entity from the Door entity in the console demo.
     */
    class InspectAction : public EntityAction {
    public:
        InspectAction(Entity& e, EntityActionManager& m)
            : EntityAction(e), mgr_(&m) {
            mgr_->Register(*this);
        }
        ~InspectAction() override { if (mgr_) mgr_->Unregister(*this); }

        std::string Name() const override { return "Inspect"; }
        bool CanBeVisible(const VisibilityQuery& q) const override { (void)q; return true; }
        void Execute() override { std::cout << "[Action] Inspect executed\n"; }

    private:
        EntityActionManager* mgr_{};
    };

} // namespace gp
