/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:27:00 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 04:27:00 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"
#include <iostream>
#include <sys/socket.h>

namespace Modes {

void setTopicLock(Server& server, int client_fd, const std::string& channel, bool enable) {

    server.getChannelModes()[channel] += 't'; 

    std::string response = ":ft_irc MODE " + channel + (enable ? " +t" : " -t") + "\r\n";
    server.sendToChannel(channel, "server", response, client_fd);
    send(client_fd, response.c_str(), response.size(), 0);
}

}
