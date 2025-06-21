#pragma once

#include "Server.hpp"
#include "Commands/Kick.hpp"
#include <string>
#include <sstream>

#include "Commands/Join.hpp"
#include "Commands/Topic.hpp"
#include "Commands/Kick.hpp"
#include "Commands/Invite.hpp"
#include "Commands/Part.hpp"
#include "Commands/Quit.hpp"
#include "Commands/Nick.hpp"
#include "Commands/Privmsg.hpp"
#include "Commands/User.hpp"

namespace Commands
{
    void processMessage(Server &server, int client_fd, const std::string &message);
    void modeCommand(Server &server, int client_fd, std::istringstream &iss);
    void handleFounderExit(Server &server, const std::string &channel, int client_fd);
    void passCommand(Server &server, int client_fd, std::istringstream &iss);
}
