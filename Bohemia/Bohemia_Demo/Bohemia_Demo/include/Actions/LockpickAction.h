// ================================================
// File: include/Actions/LockpickAction.h
// ================================================

#pragma once
#include "Core/EntityAction.h"
#include "Core/EntityActionManager.h"
#include <iostream>

namespace gp {

    class LockpickAction : public EntityAction {
    public:
        LockpickAction(Entity& e, EntityActionManager& m)
            : EntityAction(e), mgr_(&m) {
            mgr_->Register(*this);
        }

        ~LockpickAction() override { if (mgr_) mgr_->Unregister(*this); }

        std::string Name() const override { return "Lockpick"; }

        bool CanBeVisible(const VisibilityQuery& q) const override {
            return q.isLocked && !q.hasKey;
        }

        void Execute() override {
            std::cout << "[Action] Lockpick executed\n";
        }

    private:
        EntityActionManager* mgr_{};
    };

} // namespace gp
