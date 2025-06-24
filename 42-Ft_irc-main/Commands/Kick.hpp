/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deryacar <deryacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:13:36 by deryacar          #+#    #+#             */
/*   Updated: 2025/06/24 16:13:36 by deryacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICK_HPP
#define KICK_HPP

#include "../Server.hpp"
#include <sstream>

namespace Commands
{
    void kickCommand(Server &server, int client_fd, std::istringstream &iss);
}

#endif
