/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Op.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:29:15 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 04:29:15 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Op.hpp"
#include <iostream>
#include <sys/socket.h>

namespace Modes {

void setOperator(Server& server, int client_fd, const std::string& channel, const std::string& targetNick, bool enable) {


    if (server.getChannels()[channel].find(client_fd) == server.getChannels()[channel].end()) {
        std::string error_msg = ":ft_irc 442 " + channel + " :You're not on that channel\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    if (server.getChannelOperators()[channel].find(client_fd) == server.getChannelOperators()[channel].end()) {
        std::string error_msg = ":ft_irc 482 " + channel + " :You're not channel operator\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    int targetFd = server.getUserFdByNick(targetNick);
    if (targetFd == -1 || server.getChannels()[channel].find(targetFd) == server.getChannels()[channel].end()) {
        std::string error_msg = ":ft_irc 441 " + targetNick + " " + channel + " :They aren't on that channel\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    if (enable) {
        if (server.getChannelOperators()[channel].count(targetFd)) {
            std::string error_msg = ":ft_irc 482 " + channel + " :User is already an operator\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        server.getChannelOperators()[channel].insert(targetFd);
        std::string msg = ":ft_irc MODE " + channel + " +o " + targetNick + "\r\n";
        server.sendToChannel(channel, "server", msg, client_fd);
        send(targetFd, msg.c_str(), msg.size(), 0);
    } 
    else {
        if (!server.getChannelOperators()[channel].count(targetFd)) {
            std::string error_msg = ":ft_irc 482 " + channel + " :User is not an operator\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        server.getChannelOperators()[channel].erase(targetFd);
        std::string msg = ":ft_irc MODE " + channel + " -o " + targetNick + "\r\n";
        server.sendToChannel(channel, "server", msg, client_fd);
        send(targetFd, msg.c_str(), msg.size(), 0);
    }
}

}
