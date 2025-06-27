/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:47:30 by ndogan            #+#    #+#             */
/*   Updated: 2025/06/24 15:47:30 by ndogan           ###   ########.fr       */
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
        std::string nick = server.getNicknames()[client_fd];

        if (server.getChannelOperators()[channel].find(client_fd) == server.getChannelOperators()[channel].end()) {
            std::string error_msg = ":ft_irc 482 " + nick + " " + channel + " :You're not channel operator\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        if (enable) {
            if (currentModes.find('i') == std::string::npos)
                currentModes += 'i';
            server.getInviteOnlyChannels().insert(channel);
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
