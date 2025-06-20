#pragma once

#include "../Server.hpp"

namespace Modes
{
    void setLimit(Server &server, int client_fd, const std::string &channel, int limit);
}
