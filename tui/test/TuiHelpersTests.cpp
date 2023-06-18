#include "TuiHelpers.hpp"
#include "gtest/gtest.h"

TEST(TuiHelpers, update)
{
  CCC::Tui::RowContainerType rows;
  CCC::Tui::RowType row1 { 1, "First", "Entry" };
  CCC::Tui::update(rows, row1);

  ASSERT_EQ(rows.size(), 1);

  CCC::Tui::RowType row2 { 2, "Second", "Entry" };
  CCC::Tui::update(rows, row2);

  ASSERT_EQ(rows.size(), 2);

  CCC::Tui::update(rows, row1);

  ASSERT_EQ(rows.size(), 2);
}
