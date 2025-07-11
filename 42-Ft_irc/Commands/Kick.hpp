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

#pragma once

#include "../Server.hpp"
#include <sstream>

namespace Commands
{
    void kickCommand(Server &server, int client_fd, std::istringstream &iss);
}

