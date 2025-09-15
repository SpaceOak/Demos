// ============================================================
// File: include/Actions/LockpickAction.h
// ============================================================

#pragma once
#include "Core/EntityAction.h"
#include "Core/EntityActionManager.h"
#include <iostream>

namespace gp {

    /**
     * @brief Action that attempts to lockpick a locked target.
     *
     * Visible when the target is locked and the player has no key.
     * Registers in manager on construction; unregisters on destruction.
     */
    class LockpickAction : public EntityAction {
    public:
        /// Construct and auto-register.
        LockpickAction(Entity& e, EntityActionManager& m) : EntityAction(e), mgr_(&m) { mgr_->Register(*this); }
        /// RAII cleanup: auto-unregister.
        ~LockpickAction() override { if (mgr_) mgr_->Unregister(*this); }

        /// @return "Lockpick".
        std::string Name() const override { return "Lockpick"; }
        /// Visible iff isLocked && !hasKey.
        bool CanBeVisible(const VisibilityQuery& q) const override { return q.isLocked && !q.hasKey; }
        /// Demo execution prints to stdout.
        void Execute() override { std::cout << "[Action] Lockpick executed\n"; }

    private:
        EntityActionManager* mgr_{}; ///< Non-owning back-reference to the manager.
    };

} // namespace gp
