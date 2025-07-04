/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deryacar <deryacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:16:00 by deryacar          #+#    #+#             */
/*   Updated: 2025/06/24 16:16:00 by deryacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "../Commands.hpp"

namespace Commands
{
    void userCommand(Server &server, int client_fd, std::istringstream &iss)
    {
        std::string username, mode, unused;
        std::string realname;

        iss >> username >> mode >> unused;
        std::getline(iss, realname);

        if (!server.isAuthorized(client_fd))
        {
            std::string msg = ":ft_irc 451 :Nice try 😄 but you need to enter the password first.\r\n";
            send(client_fd, msg.c_str(), msg.size(), 0);
            return;
        }

        if (username.empty() || mode.empty() || unused.empty() || realname.empty())
        {
            std::string error_msg = ":ft_irc 461 USER :Not enough parameters\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        if (realname[0] == ' ')
            realname = realname.substr(1);
        if (realname[0] != ':')
        {
            std::string error_msg = ":ft_irc 461 USER :Realname must start with ':'\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        std::string cleanRealname = realname.substr(1);
        std::cout << "✅ USER command processed. Username: " << username << ", Real name: " << cleanRealname << std::endl;

        std::string response = ":ft_irc 002 " + username + " :User registered successfully " + cleanRealname + "\r\n";
        send(client_fd, response.c_str(), response.size(), 0);
    }
}
