/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deryacar <deryacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:16:16 by deryacar          #+#    #+#             */
/*   Updated: 2025/06/24 16:16:16 by deryacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Modes/Modes.hpp"
#include <signal.h>
#include <iostream>
#include <sstream>
#include <cctype>

static std::string toUpper(const std::string &str)
{
    std::string result = str;
    for (size_t i = 0; i < result.length(); ++i)
        result[i] = std::toupper(result[i]);
    return result;
}

void Commands::processMessage(Server &server, int client_fd, const std::string &message)
{
    std::istringstream iss(message);
    std::string command;
    iss >> command;
    command = toUpper(command);

    if (command == "PASS")
    {
        passCommand(server, client_fd, iss);
        return;
    }
    else if (command == "NICK")
        nickCommand(server, client_fd, iss);
    else if (command == "USER")
        userCommand(server, client_fd, iss);
    else if (command == "JOIN")
        joinCommand(server, client_fd, iss);
    else if (command == "PART")
        partCommand(server, client_fd, iss);
    else if (command == "QUIT")
        quitCommand(server, client_fd, iss);
    else if (command == "MODE")
        modeCommand(server, client_fd, iss);
    else if (command == "KICK")
        kickCommand(server, client_fd, iss);
    else if (command == "TOPIC")
        topicCommand(server, client_fd, iss);
    else if (command == "INVITE")
        inviteCommand(server, client_fd, iss);
    else if (command == "PRIVMSG")
        privmsgCommand(server, client_fd, iss);
}
