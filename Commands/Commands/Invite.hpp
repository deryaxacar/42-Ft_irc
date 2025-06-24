/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:12:59 by eakman            #+#    #+#             */
/*   Updated: 2025/04/14 21:12:59 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_HPP
# define INVITE_HPP

# include "../Server.hpp"
# include <sstream>

namespace Commands {
    void inviteCommand(Server& server, int client_fd, std::istringstream& iss);
}

#endif
