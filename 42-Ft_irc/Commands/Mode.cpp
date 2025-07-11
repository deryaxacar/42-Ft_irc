/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:37:55 by ndogan            #+#    #+#             */
/*   Updated: 2025/06/24 15:37:55 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"
#include "../Commands.hpp"
#include "../Modes/Modes.hpp"

namespace Commands
{
    void modeCommand(Server& server, int client_fd, std::istringstream& iss) 
    {
        std::string channel, modeStr;
        iss >> channel >> modeStr;
    
        if (!server.isAuthorized(client_fd)) {
            std::string msg = ":ft_irc 451 :You have not registered\r\n";
            send(client_fd, msg.c_str(), msg.size(), 0);
            return;
        }
    
        if (channel.empty()) {
            std::string error_msg = ":ft_irc 461 MODE :Not enough parameters\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        if (channel[0] != '#') {
            std::string error_msg = ":ft_irc 403 " + channel + " :No such channel\r\n";
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
    
        if (modeStr.empty()) {
            Modes::getChannelModes(server, client_fd, channel);
            return;
        }
    
        std::vector<std::string> parameters;
        std::string word;
        while (iss >> word)
            parameters.push_back(word);
    
        Modes::processMode(server, client_fd, channel, modeStr, parameters);
    }    
}
