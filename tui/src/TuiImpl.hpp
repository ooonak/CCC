#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <mutex>

#include "TuiHelpers.hpp"

namespace CCC {
namespace Tui {

class TuiImpl {
 public:

  explicit TuiImpl();

  virtual ~TuiImpl();

  bool run();

  void update(const RowType &row);

 private:
  std::mutex mMtx;

  RowContainerType mRows;

};

} // namespace Tui
} // namespace CCC
