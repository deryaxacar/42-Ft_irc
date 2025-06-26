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

        if (server.getChannelModes()[channel].find('t') == std::string::npos)
            server.getChannelModes()[channel] += 't'; 

        std::string response = ":ft_irc MODE " + channel + (enable ? " +t" : " -t") + "\r\n";
        server.sendToChannel(channel, "server", response, client_fd);
        send(client_fd, response.c_str(), response.size(), 0);
    }

}
