/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Op.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deryacar <deryacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:40:57 by ndogan            #+#    #+#             */
/*   Updated: 2025/06/24 16:38:53 by deryacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Server.hpp"
#include <string>
namespace Modes
{
    void setOperator(Server &server, int client_fd, const std::string &channel, const std::string &targetNick, bool enable);
}