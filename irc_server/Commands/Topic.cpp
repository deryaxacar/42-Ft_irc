/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:01:43 by eakman            #+#    #+#             */
/*   Updated: 2025/04/14 21:01:43 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"
#include "../Commands.hpp"

namespace Commands {

    void topicCommand(Server& server, int client_fd, std::istringstream& iss) {
        std::string channel;
        iss >> channel;
    
        if (!server.isAuthorized(client_fd)) {
            std::string msg = ":ft_irc 462 :You are not registered\r\n";
            send(client_fd, msg.c_str(), msg.size(), 0);
            return;
        }
    
        if (channel.empty() || channel[0] != '#') {
            std::string error_msg = ":ft_irc 461 TOPIC :Not enough parameters\r\n";
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
    
        std::string topic;
        std::getline(iss, topic);
        size_t start = topic.find_first_not_of(" \t\r\n");
        topic = (start != std::string::npos) ? topic.substr(start) : "";
    
        if (topic.empty() || topic[0] != ':') {
            std::string currentTopic = server.getChannelTopics()[channel];
            std::string response;
            if (currentTopic.empty()) {
                response = ":ft_irc 331 " + server.getNicknames()[client_fd] + " " + channel + " :No topic is set\r\n";
            } else {
                response = ":ft_irc 332 " + server.getNicknames()[client_fd] + " " + channel + " :" + currentTopic + "\r\n";
            }
            send(client_fd, response.c_str(), response.size(), 0);
            return;
        }
    
        if (server.getChannelModes()[channel].find('t') != std::string::npos &&
            server.getChannelOperators()[channel].find(client_fd) == server.getChannelOperators()[channel].end()) {
            std::string error_msg = ":ft_irc 482 " + channel + " :You're not channel operator\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }
    
        topic = topic.substr(1);
        server.getChannelTopics()[channel] = topic;
    
        std::string nick = server.getNicknames()[client_fd];
        std::string topicMsg = ":" + nick + " TOPIC " + channel + " :" + topic + "\r\n";
    
        const std::set<int>& users = server.getChannels()[channel];
        for (std::set<int>::const_iterator it = users.begin(); it != users.end(); ++it) {
            send(*it, topicMsg.c_str(), topicMsg.size(), 0);
        }
    }    

}
