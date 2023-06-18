#pragma once

#include <string>
#include <memory>

namespace CCC {
namespace Tui {

class TuiImpl;

std::string version();

class Tui {
    public:

      explicit Tui();

     virtual ~Tui();

     bool run();

    private:
      std::unique_ptr<TuiImpl> mImpl;
};

} // namespace CCC
} // namespace Tui
