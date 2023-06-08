#include <iostream>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"

#include "msgpack.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "emscripten/websocket.h"

void websocket()
{
    if (emscripten_websocket_is_supported())
    {
        spdlog::info("Websocket is supported.");
    }

}

void log_init()
{
    try
    {
        auto console = spdlog::stdout_color_mt("console");
        spdlog::set_default_logger(console);
        spdlog::set_level(spdlog::level::debug);
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
}

int main(void) {
    log_init();
    websocket();

    spdlog::info("spdlog {}, msgpack-cxx {}", SPDLOG_VERSION, msgpack_version());
    std::cout << std::endl;

    using namespace ftxui;

    auto summary = [&] {
        auto content = vbox({
                hbox({text(L"- done:   "), text(L"3") | bold}) | color(Color::Green),
                hbox({text(L"- active: "), text(L"2") | bold}) | color(Color::RedLight),
                hbox({text(L"- queue:  "), text(L"9") | bold}) | color(Color::Red),
                });
        return window(text(L" Summary "), content);
    };

    auto document =  //
        vbox({
                hbox({
                        summary(),
                        summary(),
                        summary() | flex,
                        }),
                summary(),
                summary(),
                });

    // Limit the size of the document to 80 char.
    document = document | size(WIDTH, LESS_THAN, 80);

    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    Render(screen, document);

    std::cout << screen.ToString() << '\0' << std::endl;

    return EXIT_SUCCESS;
}
