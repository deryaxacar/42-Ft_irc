/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deryacar <deryacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:15:52 by deryacar          #+#    #+#             */
/*   Updated: 2025/06/24 16:15:52 by deryacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Server.hpp"
#include <sstream>

namespace Commands
{
    void topicCommand(Server &server, int client_fd, std::istringstream &iss);
}
