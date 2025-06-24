/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Modes.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:50:57 by ndogan            #+#    #+#             */
/*   Updated: 2025/06/24 15:50:57 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Commands.hpp"
#include "Modes.hpp"
#include "../Server.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>

void Modes::processMode(Server &server, int client_fd, const std::string &channel,
                        const std::string &modes, std::vector<std::string> &params)
{
    std::ostringstream joined;
    for (size_t i = 0; i < params.size(); ++i)
        joined << (i ? " " : "") << params[i];

    std::cout << "🔍 DEBUG: processMode called. Channel: [" << channel
              << "], Modes: [" << modes << "], Parameters: [" << joined.str() << "]\n";

    if (channel.empty() || channel[0] != '#')
        return (void)send(client_fd, (":ft_irc 403 " + channel + " :No such channel (must start with '#')\r\n").c_str(), 
                          channel.length() + 45, 0);

    if (server.getChannels().find(channel) == server.getChannels().end())
        return (void)send(client_fd, (":ft_irc 403 " + channel + " :No such channel\r\n").c_str(), 
                          channel.length() + 28, 0);

    if (modes.empty() || (modes[0] != '+' && modes[0] != '-'))
    {
        std::string msg = ":ft_irc 472 " + channel + " " + modes + " :Unknown mode\r\n";
        server.sendToChannel(channel, "server", msg, client_fd, true);
        return;
    }

    std::string &currentModes = server.getChannelModes()[channel];
    bool enable = true;
    size_t paramIndex = 0;

    for (size_t i = 0; i < modes.size(); ++i)
    {
        char mode = modes[i];
        if (mode == '+' || mode == '-') { enable = (mode == '+'); continue; }

        std::string paramToken;
        bool needsParam = (mode == 'k' || mode == 'l' || mode == 'o');

        if (needsParam)
        {
            if (paramIndex >= params.size())
            {
                std::string msg = ":ft_irc 461 MODE " + channel + " " + mode + " :Parameter required\r\n";
                send(client_fd, msg.c_str(), msg.size(), 0);
                continue;
            }
            paramToken = params[paramIndex++];
        }

        switch (mode)
        {
        case 'i':
            setInviteOnly(server, client_fd, channel, enable);
            break;
        case 'k':
            setKey(server, client_fd, channel, enable ? paramToken : "");
            break;
        case 'l':
            if (enable)
            {
                char *endptr;
                long limit = std::strtol(paramToken.c_str(), &endptr, 10);
                if (*endptr != '\0' || limit <= 0)
                {
                    std::string msg = ":ft_irc 461 MODE " + channel + " +l :Invalid limit\r\n";
                    send(client_fd, msg.c_str(), msg.size(), 0);
                    continue;
                }
                setLimit(server, client_fd, channel, static_cast<int>(limit));
            }
            else
                setLimit(server, client_fd, channel, 0);
            break;
        case 'o':
            setOperator(server, client_fd, channel, paramToken, enable);
            break;
        case 't':
            setTopicLock(server, client_fd, channel, enable);
            break;
        default:
            std::string msg = ":ft_irc 472 " + channel + " " + mode + " :Unknown mode\r\n";
            send(client_fd, msg.c_str(), msg.size(), 0);
            break;
        }

        if (enable)
        {
            if (currentModes.find(mode) != std::string::npos)
                currentModes += mode;
        }
        else
        {
            size_t pos = currentModes.find(mode);
            if (pos != std::string::npos)
                currentModes.erase(pos, 1);
        }
    }

    std::string updatedModes = currentModes.empty() ? "+No modes set" : "+" + currentModes;
    std::string notify = ":ft_irc 324 " + channel + " " + updatedModes + "\r\n";
    send(client_fd, notify.c_str(), notify.size(), 0);
}


void Modes::getChannelModes(Server &server, int client_fd, const std::string &channel)
{

    if (server.getChannels().find(channel) == server.getChannels().end())
    {
        std::string error_msg = ":ft_irc 403 " + channel + " :No such channel\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    std::string modes = server.getChannelModes()[channel];
    std::string response = ":ft_irc 324 " + channel + " Waiting... " + modes + "\r\n";
    send(client_fd, response.c_str(), response.size(), 0);
}
