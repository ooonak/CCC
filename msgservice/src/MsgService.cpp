#include <sstream>
#include "msgservice/MsgService.hpp"
#include "MsgServiceConfig.hpp"

std::string CCC::MsgService::version()
{
    std::ostringstream os;
    os << MSGSERVICE_VERSION_MAJOR << "."
       << MSGSERVICE_VERSION_MINOR << "."
       << MSGSERVICE_VERSION_PATCH;
    return os.str();
}

