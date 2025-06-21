#pragma once

#include "../Server.hpp"

namespace Modes
{
    void setInviteOnly(Server &server, int client_fd, const std::string &channel, bool enable);
}
