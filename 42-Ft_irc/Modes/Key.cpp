/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Key.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:48:38 by ndogan            #+#    #+#             */
/*   Updated: 2025/06/24 15:48:38 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Key.hpp"
#include <iostream>
#include <sys/socket.h>

namespace Modes
{

    void setKey(Server &server, int client_fd, const std::string &channel, const std::string &key)
    {
        std::string nick = server.getNicknames()[client_fd];
        if (server.getChannelOperators()[channel].find(client_fd) == server.getChannelOperators()[channel].end())
        {
            std::string error_msg = ":ft_irc 482 " + nick + " " + channel + " :You're not channel operator\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        if (key.size() > 50)
        {
            std::string error_msg = ":ft_irc 461 MODE " + channel + " +k :Key too long\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }
        if (key.find(' ') != std::string::npos)
        {
            std::string error_msg = ":ft_irc 461 MODE " + channel + " +k :Key cannot contain spaces\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }
        if (key == server.getChannelKeys()[channel])
        {
            std::string error_msg = ":ft_irc 467 MODE " + nick + " " + channel + " +k :Key already set\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }
        if (key.empty())
        {
            server.getChannelKeys().erase(channel);
            server.getChannelModes()[channel].erase(server.getChannelModes()[channel].find('k'));
            std::string response = ":ft_irc MODE " + channel + " -k\r\n";
            send(client_fd, response.c_str(), response.size(), 0);
            return;
        }
        if (server.getChannelModes()[channel].find('k') == std::string::npos)
            server.getChannelModes()[channel] += 'k';
        server.getChannelKeys()[channel] = key;

        std::string response = (!key.empty())
                                   ? ":ft_irc MODE " + channel + " +k " + key + "\r\n"
                                   : ":ft_irc MODE " + channel + " -k\r\n";

        server.sendToChannel(channel, "server", response, client_fd, true);

        send(client_fd, response.c_str(), response.size(), 0);
    }

}
