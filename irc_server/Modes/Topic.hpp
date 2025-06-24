/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:26:51 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 04:26:51 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPIC_LOCK_MODE_HPP
# define TOPIC_LOCK_MODE_HPP

# include "../Server.hpp"

namespace Modes {
    void setTopicLock(Server& server, int client_fd, const std::string& channel, bool enable);
}

#endif
