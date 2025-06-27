/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:48:08 by ndogan            #+#    #+#             */
/*   Updated: 2025/06/24 15:48:08 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"
#include <iostream>
#include <sys/socket.h>

namespace Modes {

    void setTopicLock(Server& server, int client_fd, const std::string& channel, bool enable) {
    if (server.getChannelOperators()[channel].find(client_fd) == server.getChannelOperators()[channel].end()) {
        std::string error_msg = ":ft_irc 482 " + channel + " :You're not channel operator\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    std::string& currentModes = server.getChannelModes()[channel];

    if (enable) {
        if (currentModes.find('t') == std::string::npos)
            currentModes += 't';
    } else {
        size_t pos = currentModes.find('t');
        if (pos != std::string::npos)
            currentModes.erase(pos, 1);
    }

    std::string response = ":ft_irc MODE " + channel + (enable ? " +t" : " -t") + "\r\n";
    server.sendToChannel(channel, "server", response, client_fd);
    send(client_fd, response.c_str(), response.size(), 0);
}


}
