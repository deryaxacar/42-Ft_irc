/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:20:44 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 04:20:44 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"
#include <iostream>
#include <string>
#include <set>
#include <sys/socket.h>

namespace Modes {

void setInviteOnly(Server& server, int client_fd, const std::string& channel, bool enable) {

    std::string& currentModes = server.getChannelModes()[channel];

    if (server.getChannelOperators()[channel].find(client_fd) == server.getChannelOperators()[channel].end()) {
        std::string error_msg = ":ft_irc 482 " + channel + " :You're not channel operator\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    if (enable) {
        if (currentModes.find('i') == std::string::npos)
            currentModes += 'i';
        server.getInviteOnlyChannels().insert(channel);
        server.getChannelModes()[channel] += 'i';
    } else {
        size_t pos = currentModes.find('i');
        if (pos != std::string::npos)
            currentModes.erase(pos, 1);
        server.getInviteOnlyChannels().erase(channel);
    }


    std::string response = ":ft_irc MODE " + channel + (enable ? " +i" : " -i") + "\r\n";
    send(client_fd, response.c_str(), response.size(), 0);
}

}
