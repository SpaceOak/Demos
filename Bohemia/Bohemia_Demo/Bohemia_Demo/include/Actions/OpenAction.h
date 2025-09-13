// ================================================
// File: include/Actions/OpenAction.h
// ================================================

#pragma once
#include "Core/EntityAction.h"
#include "Core/EntityActionManager.h"
#include <iostream>

namespace gp {

    class OpenAction : public EntityAction {
    public:
        OpenAction(Entity& e, EntityActionManager& m)
            : EntityAction(e), mgr_(&m) {
            mgr_->Register(*this);
        }

        ~OpenAction() override { if (mgr_) mgr_->Unregister(*this); }

        std::string Name() const override { return "Open"; }
        bool CanBeVisible(const VisibilityQuery& q) const override { return !q.isOpen && !q.isLocked; }

        void Execute() override {
            std::cout << "[Action] Open executed\n";
        }

    private:
        EntityActionManager* mgr_{};
    };

} // namespace gp
