#pragma once

#include "../Server.hpp"
#include <string>

namespace Modes
{
    void setOperator(Server &server, int client_fd, const std::string &channel, const std::string &targetNick, bool enable);
}
