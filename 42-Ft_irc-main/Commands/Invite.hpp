/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deryacar <deryacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:13:05 by deryacar          #+#    #+#             */
/*   Updated: 2025/06/24 16:13:05 by deryacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_HPP
#define INVITE_HPP

#include "../Server.hpp"
#include <sstream>

namespace Commands
{
    void inviteCommand(Server &server, int client_fd, std::istringstream &iss);
}

#endif
