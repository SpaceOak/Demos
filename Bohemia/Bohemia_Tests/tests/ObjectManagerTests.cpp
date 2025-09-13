#include <gtest/gtest.h>
#include "Core/Entity.h"
#include "Core/EntityActionManager.h"

// Local probe action to count calls without printing
namespace {
    struct ProbeAction : gp::EntityAction {
        explicit ProbeAction(gp::Entity& e, gp::EntityActionManager& m)
            : gp::EntityAction(e), mgr(&m) { mgr->Register(*this); }
        ~ProbeAction() override { if (mgr) mgr->Unregister(*this); }

        std::string Name() const override { return "Probe"; }
        bool CanBeVisible(const gp::VisibilityQuery&) const override { return true; }
        void Execute() override { ++execCount; }

        gp::EntityActionManager* mgr{};
        int execCount{ 0 };
    };
} // namespace

using namespace gp;

TEST(ObjectManager, ForEachVisitsAll) {
    Entity e;
    auto& a = e.AddAction<ProbeAction>();
    auto& b = e.AddAction<ProbeAction>();
    auto& c = e.AddAction<ProbeAction>();

    int visited = 0;
    e.Actions().ForEach([&](EntityAction&) { ++visited; });
    EXPECT_EQ(visited, 3);

    // Also ensure pointers are valid
    auto vis = e.Actions().Visible({});
    ASSERT_EQ(vis.size(), 3u);
    for (auto* p : vis) ASSERT_NE(p, nullptr);
}

TEST(ObjectManager, CallAllInvokesMemberFunction) {
    Entity e;
    auto& a = e.AddAction<ProbeAction>();
    auto& b = e.AddAction<ProbeAction>();

    e.Actions().CallAll(&EntityAction::Execute);
    EXPECT_EQ(static_cast<ProbeAction&>(a).execCount, 1);
    EXPECT_EQ(static_cast<ProbeAction&>(b).execCount, 1);

    // Call again -> counters increment
    e.Actions().CallAll(&EntityAction::Execute);
    EXPECT_EQ(static_cast<ProbeAction&>(a).execCount, 2);
    EXPECT_EQ(static_cast<ProbeAction&>(b).execCount, 2);
}
