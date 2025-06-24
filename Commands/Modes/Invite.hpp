/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:20:37 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 04:20:37 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_MODE_HPP
# define INVITE_MODE_HPP

# include "../Server.hpp"

namespace Modes {
    void setInviteOnly(Server& server, int client_fd, const std::string& channel, bool enable);
}

#endif
