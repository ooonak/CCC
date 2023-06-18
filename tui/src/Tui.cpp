#include "tui/Tui.hpp"
#include "TuiImpl.hpp"
#include "TuiConfig.hpp"

#include <sstream>
#include <memory>
#include <string>

std::string CCC::Tui::version()
{
  std::ostringstream os;
  os << TUI_VERSION_MAJOR << "." << TUI_VERSION_MINOR << "." << TUI_VERSION_PATCH;
  return os.str();
}

CCC::Tui::Tui::Tui() : mImpl{std::make_unique<CCC::Tui::TuiImpl>()} {}

bool CCC::Tui::Tui::run()
{
  if (mImpl != nullptr)
  {
    return mImpl->run();
  }

  return false;
}

CCC::Tui::Tui::~Tui() {}
