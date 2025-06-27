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

#include "Server.hpp"
#include <cerrno>
#include <climits>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "❌ Usage: ./ircserv <port> <password>" << std::endl;
        return EXIT_FAILURE;
    }

    char *endPtr = NULL;
    errno = 0;
    long port = strtol(argv[1], &endPtr, 10);

    if (errno != 0 || *endPtr != '\0' || port <= 0 || port > 65535)
    {
        std::cerr << "❌ Error: Invalid port number. Port must be between 1 and 65535." << std::endl;
        return EXIT_FAILURE;
    }

    std::string password = argv[2];

    Server server(port, password);
    server.init();
    server.run();
    return 0;
}
