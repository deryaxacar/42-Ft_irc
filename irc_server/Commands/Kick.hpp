/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:56:48 by eakman            #+#    #+#             */
/*   Updated: 2025/04/14 16:56:48 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICK_HPP
# define KICK_HPP

# include "../Server.hpp"
# include <sstream>

namespace Commands {
    void kickCommand(Server& server, int client_fd, std::istringstream& iss);
}

#endif
