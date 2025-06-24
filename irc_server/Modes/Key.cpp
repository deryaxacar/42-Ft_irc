/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Key.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:24:13 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 04:24:13 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Key.hpp"
#include <iostream>
#include <sys/socket.h>

namespace Modes {

void setKey(Server& server, int client_fd, const std::string& channel, const std::string& key) {

    if (server.getChannelOperators()[channel].find(client_fd) == server.getChannelOperators()[channel].end()) {
        std::string error_msg = ":ft_irc 482 " + channel + " :You're not channel operator\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    if(key.size() > 50) {
        std::string error_msg = ":ft_irc 461 MODE " + channel + " +k :Key too long\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }
    if(key.find(' ') != std::string::npos) {
        std::string error_msg = ":ft_irc 461 MODE " + channel + " +k :Key cannot contain spaces\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }
    if(key == server.getChannelKeys()[channel]) {
        std::string error_msg = ":ft_irc 461 MODE " + channel + " +k :Key already set\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }
    if(key.empty()) {
        server.getChannelKeys().erase(channel);
        server.getChannelModes()[channel].erase(server.getChannelModes()[channel].find('k'));
        std::string response = ":ft_irc MODE " + channel + " -k\r\n";
        send(client_fd, response.c_str(), response.size(), 0);
        return;
    }

    server.getChannelKeys()[channel] = key;
    server.getChannelModes()[channel] += 'k';

    std::string response = (!key.empty())
        ? ":ft_irc MODE " + channel + " +k " + key + "\r\n"
        : ":ft_irc MODE " + channel + " -k\r\n";

    server.sendToChannel(channel, "server", response, client_fd, true);

    send(client_fd, response.c_str(), response.size(), 0);
}

}
