#include "msgservice/MsgService.hpp"
#include "gtest/gtest.h"

TEST(Tui, Version) { EXPECT_TRUE(CCC::MsgService::version().size() > 0); }

