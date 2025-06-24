/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deryacar <deryacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:13:23 by deryacar          #+#    #+#             */
/*   Updated: 2025/06/24 16:13:23 by deryacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_HPP
#define JOIN_HPP

#include "../Server.hpp"
#include <sstream>

namespace Commands
{
    void joinCommand(Server &server, int client_fd, std::istringstream &iss);
}

#endif
