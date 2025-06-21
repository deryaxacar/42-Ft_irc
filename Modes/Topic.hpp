#pragma once

#include "../Server.hpp"

namespace Modes
{
    void setTopicLock(Server &server, int client_fd, const std::string &channel, bool enable);
}
