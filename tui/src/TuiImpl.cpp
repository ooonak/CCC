#include "TuiImpl.hpp"

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Input, Renderer, ResizableSplitLeft
#include "ftxui/component/component_base.hpp"  // for ComponentBase, Component
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for operator|, separator, text, Element, flex, vbox, border

CCC::Tui::TuiImpl::TuiImpl()
{

}

CCC::Tui::TuiImpl::~TuiImpl()
{

}

bool CCC::Tui::TuiImpl::run()
{
  using namespace ftxui;

      std::string placeholder = "placeholder";
  std::string content_1;
  std::string content_2;
  auto textarea_1 = Input(&content_1, &placeholder);
  auto textarea_2 = Input(&content_2, &placeholder);
  int size = 50;
  auto layout = ResizableSplitLeft(textarea_1, textarea_2, &size);

      auto component = Renderer(layout,
                                [&]
                                {
                                  return vbox({
                                               text("Input:"),
                                               separator(),
                                               layout->Render() | flex,
                                               }) |
                                         border;
                                });

  auto screen = ScreenInteractive::Fullscreen();
  screen.Loop(component);

  return true;
}

void CCC::Tui::TuiImpl::update(const RowType &row)
{
  std::lock_guard<std::mutex> lock(mMtx);
  Tui::update(mRows, row);
}
