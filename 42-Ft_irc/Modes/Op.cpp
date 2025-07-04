/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Op.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:40:57 by ndogan            #+#    #+#             */
/*   Updated: 2025/06/24 15:40:57 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Op.hpp"
#include <iostream>
#include <sys/socket.h>

namespace Modes
{

    void setOperator(Server &server, int client_fd, const std::string &channel, const std::string &targetNick, bool enable)
    {
        std::string nick = server.getNicknames()[client_fd];

        if (server.getChannels()[channel].find(client_fd) == server.getChannels()[channel].end())
        {
            std::string error_msg = ":ft_irc 442 " + nick + " " + channel + " :You're not on that channel\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        if (server.getChannelOperators()[channel].find(client_fd) == server.getChannelOperators()[channel].end())
        {
            std::string error_msg = ":ft_irc 482 " + nick + " " + channel + " :You're not channel operator\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        int targetFd = server.getUserFdByNick(targetNick);
        if (targetFd == -1 || server.getChannels()[channel].find(targetFd) == server.getChannels()[channel].end())
        {
            std::string error_msg = ":ft_irc 441 " + nick + " " + targetNick + " " + channel + " :They aren't on that channel\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        if (enable)
        {
            if (server.getChannelOperators()[channel].count(targetFd))
            {
                std::string error_msg = ":ft_irc 482 " + nick + " " + channel + " :User is already an operator\r\n";
                send(client_fd, error_msg.c_str(), error_msg.size(), 0);
                return;
            }

            server.getChannelOperators()[channel].insert(targetFd);
            std::string msg = ":ft_irc MODE " + nick + " "  + channel + " +o " + targetNick + "\r\n";
            server.sendToChannel(channel, "server", msg, client_fd);
            send(targetFd, msg.c_str(), msg.size(), 0);
        }
        else
        {
            if (!server.getChannelOperators()[channel].count(targetFd))
            {
                std::string error_msg = ":ft_irc 482 " + nick + " " + channel + " :User is not an operator\r\n";
                send(client_fd, error_msg.c_str(), error_msg.size(), 0);
                return;
            }

            server.getChannelOperators()[channel].erase(targetFd);
            std::string msg = ":ft_irc MODE " + nick + " "  + channel + " +o " + targetNick + "\r\n";
            server.sendToChannel(channel, "server", msg, client_fd);
            send(targetFd, msg.c_str(), msg.size(), 0);
        }
    }

}
