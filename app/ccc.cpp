#include <iostream>
#include "msgservice/MsgService.hpp"
#include "tui/Tui.hpp"

int main()
{
    /*
    std::cout << "Using libMsgService " << CCC::MsgService::version() << std::endl;
    std::cout << "Using libTui " << CCC::Tui::version() << std::endl;
    */

  CCC::Tui::Tui ui;
    ui.run();

    return EXIT_SUCCESS;
}

