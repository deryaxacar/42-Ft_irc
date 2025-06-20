#pragma once

#include "../Server.hpp"
#include <string>

namespace Modes
{
    void setKey(Server &server, int client_fd, const std::string &channel, const std::string &key);
}
