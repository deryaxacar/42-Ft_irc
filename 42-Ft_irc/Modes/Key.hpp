/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Key.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:48:44 by ndogan            #+#    #+#             */
/*   Updated: 2025/06/24 15:48:44 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Server.hpp"
#include <string>

namespace Modes
{
    void setKey(Server &server, int client_fd, const std::string &channel, const std::string &key);
}
