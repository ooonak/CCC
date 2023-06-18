#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <mutex>

namespace CCC {
namespace Tui {

using RowType = std::tuple<uint64_t, std::string, std::string>;
using RowContainerType = std::vector<RowType>;

void update(RowContainerType &rows, const RowType &row);

} // namespace Tui
} // namespace CCC
