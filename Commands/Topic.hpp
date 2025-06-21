#pragma once

#include "../Server.hpp"
#include <sstream>

namespace Commands
{
    void topicCommand(Server &server, int client_fd, std::istringstream &iss);
}
