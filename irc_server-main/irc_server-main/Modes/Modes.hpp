#pragma once

#include "../Server.hpp"
#include <string>
#include <sstream>

#include "Invite.hpp"
#include "Key.hpp"
#include "Limit.hpp"
#include "Topic.hpp"
#include "Op.hpp"

namespace Modes
{
    void processMode(Server &server, int client_fd, const std::string &channel, const std::string &modes, std::vector<std::string> &params);
    void getChannelModes(Server &server, int client_fd, const std::string &channel);
}
