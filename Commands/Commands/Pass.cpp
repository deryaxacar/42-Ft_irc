/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:55:08 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 03:55:08 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"
#include "../Commands.hpp"

namespace Commands {

void passCommand(Server& server, int client_fd, std::istringstream& iss) {
    std::string password;
    iss >> password;

    if (server.isAuthorized(client_fd)) {
        std::string msg = ":ft_irc 462 :NewUser Nice try, but you can’t register twice. One ticket per customer.\r\n";
        send(client_fd, msg.c_str(), msg.size(), 0);
        return;
    }

    if (password != server.getPassword()) {
        std::string error_msg = ":ft_irc 464 :NewUser Wrong password. Not even close. 🧠🔒\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);
        return;
    }

    std::string success_msg = ":ft_irc 001 NewUser Well done, genius! How on earth did you guess the right password? 😉\r\n";
    send(client_fd, success_msg.c_str(), success_msg.size(), 0);
    server.authorizeClient(client_fd);
}

}
