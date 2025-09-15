#include <gtest/gtest.h>
#include "Core/Entity.h"
#include "Actions/OpenAction.h"
#include "Actions/LockpickAction.h"

using namespace gp;

static size_t Count(EntityActionManager& m) {
    size_t n = 0;
    m.ForEach([&](EntityAction&) { ++n; });
    return n;
}

TEST(EntityActions, RegisterAndUnregisterLifecycle) {
    Entity e;
    EXPECT_EQ(Count(e.Actions()), 0u);

    auto& a1 = e.AddAction<OpenAction>();
    (void)a1;
    auto& a2 = e.AddAction<LockpickAction>();
    (void)a2;

    EXPECT_EQ(Count(e.Actions()), 2u);
}

TEST(EntityActions, VisibilityFiltering) {
    Entity e;
    e.AddAction<OpenAction>();
    e.AddAction<LockpickAction>();

    // locked, no key -> only Lockpick
    auto v1 = e.Actions().Visible({ /*hasKey*/false, /*isOpen*/false, /*isLocked*/true });
    ASSERT_EQ(v1.size(), 1u);
    EXPECT_EQ(v1[0]->Name(), "Lockpick");

    // closed + key, unlocked -> only Open
    auto v2 = e.Actions().Visible({ true, false, false });
    ASSERT_EQ(v2.size(), 1u);
    EXPECT_EQ(v2[0]->Name(), "Open");

    // already open -> none
    auto v3 = e.Actions().Visible({ false, true, false });
    EXPECT_TRUE(v3.empty());
}

TEST(EntityActions, DestructionOrder_NoCrash) {
    // If destruction order is wrong, this test would crash on scope exit.
    {
        Entity e;
        e.AddAction<OpenAction>();
        e.AddAction<LockpickAction>();
        EXPECT_EQ(Count(e.Actions()), 2u);
    }
    SUCCEED();
}
