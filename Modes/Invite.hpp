/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:47:41 by ndogan            #+#    #+#             */
/*   Updated: 2025/06/24 15:47:41 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_MODE_HPP
# define INVITE_MODE_HPP

# include "../Server.hpp"

namespace Modes {
    void setInviteOnly(Server& server, int client_fd, const std::string& channel, bool enable);
}

#endif
