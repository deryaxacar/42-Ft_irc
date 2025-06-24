/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:31:56 by eakman            #+#    #+#             */
/*   Updated: 2025/04/14 21:31:56 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"
#include "../Commands.hpp"

namespace Commands {

void inviteCommand(Server& server, int client_fd, std::istringstream& iss) {
    std::string targetNick, channel;
    iss >> targetNick >> channel;

    if (!server.isAuthorized(client_fd)) {
        std::string msg = ":ft_irc 451 : If you register, you are blessed.\r\n";
        send(client_fd, msg.c_str(), msg.size(), 0);
        return;
    }

    if (targetNick.empty() || channel.empty()) {
        std::string error_msg = ":ft_irc 461 INVITE :Not enough parameters\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    if (channel[0] != '#') {
        std::string error_msg = ":ft_irc 403 " + channel + " :Invalid channel name\r\n";
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

    if (server.getChannels()[channel].count(targetFd)) {
        std::string error_msg = ":ft_irc 443 " + targetNick + " " + channel + " :is already on channel\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    
    server.getInvitedUsers()[channel].insert(targetFd);

    
    std::string senderNick = server.getNicknames()[client_fd];
    std::string inviteMsg = ":" + senderNick + " INVITE " + targetNick + " " + channel + "\r\n";
    send(targetFd, inviteMsg.c_str(), inviteMsg.size(), 0);

    
    std::string confirm = ":ft_irc 341 " + targetNick + " " + channel + "\r\n";
    send(client_fd, confirm.c_str(), confirm.size(), 0);
    }

}
