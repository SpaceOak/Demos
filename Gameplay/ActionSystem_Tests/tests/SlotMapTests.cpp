#include <gtest/gtest.h>
#include "Core/SlotMap.h"

using gp::SlotMap;

TEST(SlotMap, HandleGenerationPreventsStaleAccess) {
    SlotMap<int> sm;
    int a = 1, b = 2, c = 3;

    auto ha = sm.insert(&a);
    auto hb = sm.insert(&b);

    ASSERT_EQ(sm.size_alive(), 2u);
    ASSERT_EQ(sm.get(ha), &a);
    ASSERT_EQ(sm.get(hb), &b);

    // erase 'a' -> old handle ha becomes stale
    EXPECT_TRUE(sm.erase(ha));
    EXPECT_EQ(sm.get(ha), nullptr);
    EXPECT_EQ(sm.size_alive(), 1u);

    // insert 'c' — may reuse the same slot index, but with a new generation
    auto hc = sm.insert(&c);
    EXPECT_EQ(sm.get(hc), &c);
    EXPECT_EQ(sm.size_alive(), 2u);

    // old handle 'ha' must still be invalid
    EXPECT_EQ(sm.get(ha), nullptr);

    // for_each visits only alive elements (b and c)
    size_t count = 0;
    sm.for_each([&](int&) { ++count; });
    EXPECT_EQ(count, 2u);
}
