/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:00:57 by eakman            #+#    #+#             */
/*   Updated: 2025/04/14 21:00:57 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"
#include "../Commands.hpp"
#include <set>
#include <string>

namespace Commands {

void joinCommand(Server& server, int client_fd, std::istringstream& iss) {
    std::string channel, key;
    iss >> channel >> key;

    if (!server.isAuthorized(client_fd)) {
        std::string msg = ":ft_irc 451 : If you register, you are blessed.\r\n";
        send(client_fd, msg.c_str(), msg.size(), 0);
        return;
    }

    if (!server.getNicknames().count(client_fd)) {
        std::string msg = ":ft_irc 431 : No nickname given\r\n";
        send(client_fd, msg.c_str(), msg.size(), 0);
        return;
    }

    if (channel.empty() || channel[0] != '#') {
        std::string error_msg = ":ft_irc 400 JOIN : Invalid channel name. Usage: JOIN #channel [key]\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    bool isNewChannel = false;

    if (server.getChannels().find(channel) == server.getChannels().end()) {
        isNewChannel = true;
        server.getChannels()[channel].insert(client_fd);
        server.getChannelModes()[channel] = "";
        server.getChannelFounders()[channel] = client_fd;
        std::cout << "🆕 New Channel created: " << channel << "\n";
    } else {
        if (server.getInviteOnlyChannels().count(channel) &&
            server.getInvitedUsers()[channel].count(client_fd) == 0) {
            std::string error_msg = ":ft_irc 473 " + channel + " : You must be invited to join this channel\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        if (server.getChannelKeys().count(channel)) {
            std::string expectedKey = server.getChannelKeys()[channel];
            if (!expectedKey.empty() && expectedKey != key) {
                std::string error_msg = ":ft_irc 475 " + channel + " :Incorrect channel key\r\n";
                send(client_fd, error_msg.c_str(), error_msg.size(), 0);
                return;
            }
        }

        if (server.getChannelLimits().count(channel)) {
            int limit = server.getChannelLimits()[channel];
            if ((int)server.getChannels()[channel].size() >= limit) {
                std::string error_msg = ":ft_irc 471 " + channel + " :Cannot join channel (+l limit reached)\r\n";
                send(client_fd, error_msg.c_str(), error_msg.size(), 0);
                return;
            }
        }

        server.getChannels()[channel].insert(client_fd);
    }

    std::string joinMsg = ":" + server.getNicknames()[client_fd] + " JOIN " + channel + "\r\n";
    if (server.getNicknames()[client_fd] != ""){
        std::string userMsg = "Hi there I'm " + server.getNicknames()[client_fd] + "\r\n";
        server.sendToChannel(channel, server.getNicknames()[client_fd], userMsg, client_fd, true);
    }
    std::cout << "📨 User joins: " << channel << " channel\n";
    send(client_fd, joinMsg.c_str(), joinMsg.size(), 0);

    if (!server.getChannelTopics()[channel].empty()) {
        std::string topicMsg = ":ft_irc 332 " + server.getNicknames()[client_fd] + " " + channel + " :" + server.getChannelTopics()[channel] + "\r\n";
        send(client_fd, topicMsg.c_str(), topicMsg.size(), 0);
    }

    if (isNewChannel) {
        server.getChannelOperators()[channel].insert(client_fd);
        std::string opMsg = ":ft_irc MODE " + channel + " +o " + server.getNicknames()[client_fd] + "\r\n";
        send(client_fd, opMsg.c_str(), opMsg.size(), 0);
    }
}

}
