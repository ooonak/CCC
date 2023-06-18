#include "TuiHelpers.hpp"

#include <algorithm>

void CCC::Tui::update(RowContainerType &rows, const RowType &row)
{
  const auto compare_id = [&row](const RowType& r1){ return std::get<0>(r1) == std::get<0>(row); };
  const auto entry = std::find_if(rows.begin(), rows.end(), compare_id );
  if (entry == rows.end())
  {
    rows.emplace_back(row);
  }
  else
  {
    *entry = row;
  }
}
