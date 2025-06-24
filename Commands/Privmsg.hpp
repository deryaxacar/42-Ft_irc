/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 00:23:58 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 00:23:58 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

# include "../Server.hpp"
# include <sstream>

namespace Commands {
    void privmsgCommand(Server& server, int client_fd, std::istringstream& iss);
}

#endif
