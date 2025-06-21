#pragma once

#include "../Server.hpp"
#include <sstream>

namespace Commands
{
    void inviteCommand(Server &server, int client_fd, std::istringstream &iss);
}
