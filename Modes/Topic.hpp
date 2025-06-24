/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:48:17 by ndogan            #+#    #+#             */
/*   Updated: 2025/06/24 15:48:17 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../Server.hpp"

namespace Modes {
    void setTopicLock(Server& server, int client_fd, const std::string& channel, bool enable);
}
