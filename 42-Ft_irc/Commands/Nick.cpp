/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deryacar <deryacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:13:45 by deryacar          #+#    #+#             */
/*   Updated: 2025/06/24 16:13:45 by deryacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"
#include "../Commands.hpp"

namespace Commands
{
    void nickCommand(Server &server, int client_fd, std::istringstream &iss)
    {
        std::string nickname;
        iss >> nickname;

        if (!server.isAuthorized(client_fd))
        {
            std::string msg = ":ft_irc 451 : Nice try 😄 but you need to enter the password first.\r\n";
            send(client_fd, msg.c_str(), msg.size(), 0);
            return;
        }

        if (nickname.empty())
        {
            std::string error_msg = ":ft_irc 431 * :No nickname given\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        for (size_t i = 1; i < server.getClients().size(); ++i)
        {
            if (server.getNicknames()[server.getClients()[i].fd] == nickname)
            {
                std::string error_msg = ":ft_irc 433 " + nickname + " :Nickname is already in use\r\n";
                send(client_fd, error_msg.c_str(), error_msg.size(), 0);
                return;
            }
        }

        server.getNicknames()[client_fd] = nickname;
        std::string response = ":ft_irc 001 " + nickname + " :Nickname set successfully\r\n";
        send(client_fd, response.c_str(), response.size(), 0);
    }
}
