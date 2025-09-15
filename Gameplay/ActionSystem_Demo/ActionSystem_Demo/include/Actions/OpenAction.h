// ============================================================
// File: include/Actions/OpenAction.h
// ============================================================

#pragma once
#include "Core/EntityAction.h"
#include "Core/EntityActionManager.h"
#include <iostream>

namespace gp {

    /**
     * @brief Action that opens a target (e.g., door/chest).
     *
     * Visible when the target is closed and not locked.
     * Registers in manager on construction; unregisters on destruction.
     */
    class OpenAction : public EntityAction {
    public:
        /// Construct and auto-register.
        OpenAction(Entity& e, EntityActionManager& m) : EntityAction(e), mgr_(&m) { mgr_->Register(*this); }
        /// RAII cleanup: auto-unregister.
        ~OpenAction() override { if (mgr_) mgr_->Unregister(*this); }

        /// @return "Open".
        std::string Name() const override { return "Open"; }
        /// Visible iff !isOpen && !isLocked.
        bool CanBeVisible(const VisibilityQuery& q) const override { return !q.isOpen && !q.isLocked; }
        /// Demo execution prints to stdout.
        void Execute() override { std::cout << "[Action] Open executed\n"; }

    private:
        EntityActionManager* mgr_{}; ///< Non-owning back-reference to the manager.
    };

} // namespace gp
