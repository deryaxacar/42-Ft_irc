/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Limit.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:49:43 by ndogan            #+#    #+#             */
/*   Updated: 2025/06/24 15:49:43 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../Server.hpp"

namespace Modes {
    void setLimit(Server& server, int client_fd, const std::string& channel, int limit);
}
