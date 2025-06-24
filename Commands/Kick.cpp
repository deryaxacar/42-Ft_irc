/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:27:48 by eakman            #+#    #+#             */
/*   Updated: 2025/04/14 16:27:48 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick.hpp"
#include "../Commands.hpp"  

namespace Commands {

void kickCommand(Server& server, int client_fd, std::istringstream& iss) {
    std::string first, second;
    iss >> first >> second;

    if (!server.isAuthorized(client_fd)) {
        std::string msg = ":ft_irc 451 : If you register, you are blessed.\r\n";
        send(client_fd, msg.c_str(), msg.size(), 0);
        return;
    }

    if (first.empty() || second.empty()) {
        std::string error_msg = ":ft_irc 461 KICK :Not enough parameters\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    std::string channel, targetNick;
    if (first[0] == '#') {
        channel = first;
        targetNick = second;
    } else if (second[0] == '#') {
        channel = second;
        targetNick = first;
    } else {
        std::string error_msg = ":ft_irc 403 * :No valid channel name provided\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    if (server.getChannels().find(channel) == server.getChannels().end()) {
        std::string error_msg = ":ft_irc 403 " + channel + " :No such channel\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }
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
    if (targetFd == -1) {
        std::string error_msg = ":ft_irc 401 " + targetNick + " :No such nick\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }
    if (server.getChannels()[channel].find(targetFd) == server.getChannels()[channel].end()) {
        std::string error_msg = ":ft_irc 441 " + targetNick + " " + channel + " :They aren't on that channel\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }
    if (server.getChannelFounders()[channel] == targetFd && client_fd != targetFd) {
        std::string error_msg = ":ft_irc 482 " + channel + " :Cannot kick the channel founder\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    std::string senderNick = server.getNicknames()[client_fd];
    if(targetFd == client_fd) {
        std::string error_msg = ":ft_irc 441 " + targetNick + " " + channel + " :You cannot kick yourself\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }
    std::string kickMsg = ":" + senderNick + " KICK " + channel + " " + targetNick + " :Kicked\r\n";
    server.sendToChannel(channel, senderNick, "has kicked " + targetNick, client_fd);
    send(targetFd, kickMsg.c_str(), kickMsg.size(), 0);

    server.getChannels()[channel].erase(targetFd);
    server.getChannelOperators()[channel].erase(targetFd);

    if (server.getChannels()[channel].empty()) {
        server.getChannels().erase(channel);
        server.getChannelOperators().erase(channel);
        server.getChannelFounders().erase(channel);
        server.getChannelModes().erase(channel);
        server.getChannelKeys().erase(channel);
        server.getChannelLimits().erase(channel);
        server.getInviteOnlyChannels().erase(channel);
    }
}

}

