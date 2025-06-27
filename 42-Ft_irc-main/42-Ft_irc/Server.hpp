/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:12:50 by mertcaki          #+#    #+#             */
/*   Updated: 2025/06/24 16:12:50 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <poll.h>
#include <map>
#include <set>

class Server
{
private:
    int port;
    int server_socket;
    struct sockaddr_in server_addr;
    std::string password;

    std::set<int> authorizedClients;
    std::vector<struct pollfd> clients;
    std::map<int, std::string> nicknames;

    std::map<std::string, std::set<int> > channels;
    std::map<std::string, std::string> channelModes;
    std::map<std::string, std::string> channelKeys;
    std::map<std::string, int> channelLimits;
    std::map<std::string, std::set<int> > channelOperators;
    std::map<std::string, int> channelFounders;
    std::map<std::string, std::string> channelTopics;

    std::set<std::string> inviteOnlyChannels;
    std::map<std::string, std::set<int> > invitedUsers;

    std::map<int, std::string> clientBuffers;

public:
    Server(int port, const std::string &password);
    ~Server();

    void init();
    void run();
    void acceptClient();
    void receiveMessage(int client_fd);
    void removeClient(int client_fd);

    void sendToChannel(const std::string &channel, const std::string &sender,
                       const std::string &message, int sender_fd, bool isCommand = false);
    void partChannel(int client_fd, const std::string &channel);
    void quitClient(int client_fd, const std::string &reason);

    bool isAuthorized(int fd) const;
    void authorizeClient(int fd);
    const std::string &getPassword() const;

    std::vector<struct pollfd> &getClients();
    std::map<int, std::string> &getNicknames();
    std::map<std::string, std::set<int> > &getChannels();
    std::map<std::string, std::string> &getChannelModes();
    std::set<std::string> &getInviteOnlyChannels();
    std::map<std::string, std::set<int> > &getInvitedUsers();
    std::map<std::string, std::string> &getChannelKeys();
    std::map<std::string, int> &getChannelLimits();
    std::map<std::string, std::set<int> > &getChannelOperators();
    std::map<std::string, int> &getChannelFounders();
    std::map<std::string, std::string> &getChannelTopics();

    int getUserFdByNick(const std::string &nickname);
};
