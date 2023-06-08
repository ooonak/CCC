#include <iostream>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"

#include "msgpack.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <emscripten/emscripten.h>
#include "emscripten/websocket.h"

// Random Googled example from https://gist.github.com/nus/564e9e57e4c107faa1a45b8332c265b9

EM_BOOL onopen(int eventType, const EmscriptenWebSocketOpenEvent *websocketEvent, void *userData) {
    std::cout << __func__ << std::endl;
    std::cout << '\0' << std::endl;

    EMSCRIPTEN_RESULT result;
    result = emscripten_websocket_send_utf8_text(websocketEvent->socket, "Joh  N Doe");
    if (result) {
        std::cerr << "Failed to emscripten_websocket_send_utf8_text(): " << result << std::endl;
    }
    return EM_TRUE;
}

EM_BOOL onerror(int eventType, const EmscriptenWebSocketErrorEvent *websocketEvent, void *userData) {
    std::cout << __func__ << std::endl;
    std::cout << '\0' << std::endl;

    return EM_TRUE;
}

EM_BOOL onclose(int eventType, const EmscriptenWebSocketCloseEvent *websocketEvent, void *userData) {
    std::cout << __func__ << std::endl;
    std::cout << '\0' << std::endl;

    if (userData != nullptr)
    {
        *(bool*)userData = true;
    }

    return EM_TRUE;
}

EM_BOOL onmessage(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent, void *userData) {
    std::cout << __func__ << std::endl;
    std::cout << '\0' << std::endl;
    if (websocketEvent->isText) {
        // For only ascii chars.
        std::cout << "message: " << websocketEvent->data << std::endl;
        std::cout << '\0' << std::endl;
    }

    EMSCRIPTEN_RESULT result;
    result = emscripten_websocket_close(websocketEvent->socket, 1000, "no reason");
    if (result) {
        std::cerr << "Failed to emscripten_websocket_close(): " << result << std::endl;
    }
    return EM_TRUE;
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
    bool stop = false;

    if (emscripten_websocket_is_supported())
    {
        EmscriptenWebSocketCreateAttributes ws_attrs = {
        "ws://websockets.chilkat.io/wsChilkatEcho.ashx",
        nullptr,
        EM_TRUE
    };

    EMSCRIPTEN_WEBSOCKET_T ws = emscripten_websocket_new(&ws_attrs);
    if (ws <= 0)
    {
        std::cerr << "emscripten_websocket_new failed " << ws << std::endl;
        return EXIT_FAILURE;
    }

    emscripten_websocket_set_onopen_callback(ws, NULL, onopen);
    emscripten_websocket_set_onerror_callback(ws, NULL, onerror);
    emscripten_websocket_set_onclose_callback(ws, &stop, onclose);
    emscripten_websocket_set_onmessage_callback(ws, NULL, onmessage);
    }

    log_init();
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
