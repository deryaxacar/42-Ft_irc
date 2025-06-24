/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:01:30 by eakman            #+#    #+#             */
/*   Updated: 2025/04/14 21:01:30 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPIC_HPP
# define TOPIC_HPP

# include "../Server.hpp"
# include <sstream>

namespace Commands {
    void topicCommand(Server& server, int client_fd, std::istringstream& iss);
}

#endif
