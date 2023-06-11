#include "tui/Tui.hpp"
#include "gtest/gtest.h"

TEST(Tui, Version) { EXPECT_TRUE(CCC::Tui::version().size() > 0); }

