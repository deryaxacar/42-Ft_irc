/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Limit.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:49:34 by ndogan            #+#    #+#             */
/*   Updated: 2025/06/24 15:49:34 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Limit.hpp"
#include <iostream>
#include <sstream>
#include <sys/socket.h>

namespace Modes
{

    void setLimit(Server &server, int client_fd, const std::string &channel, int limit, bool enable)
    {
        std::string nick = server.getNicknames()[client_fd];

        if (server.getChannelOperators()[channel].find(client_fd) == server.getChannelOperators()[channel].end())
        {
            std::string error_msg = ":ft_irc 482 " + nick + " " + channel + " :You're not channel operator\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        if (limit <= 0 && enable)
        {
            std::string error_msg = ":ft_irc 461 " + nick + " " + channel + " :Limit parameter missing or invalid\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        if (limit == 0 && !enable)
        {
            if (server.getChannelLimits()[channel])
            {
                server.getChannelLimits().erase(channel);
                server.getChannelModes()[channel].erase(server.getChannelModes()[channel].find('l'));
            }
            std::string response = ":ft_irc MODE " + channel + " -l\r\n";
            server.sendToChannel(channel, "server", response, client_fd, true);
            send(client_fd, response.c_str(), response.size(), 0);
            return;
        }

        server.getChannelLimits()[channel] = limit;
        if (server.getChannelModes()[channel].find('l') == std::string::npos)
            server.getChannelModes()[channel] += 'l';

        std::ostringstream oss;
        oss << limit;
        std::string response = ":ft_irc MODE " + channel + " +l " + oss.str() + "\r\n";
        server.sendToChannel(channel, "server", response, client_fd);
        send(client_fd, response.c_str(), response.size(), 0);
    }

}
