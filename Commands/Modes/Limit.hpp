/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Limit.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:25:33 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 04:25:33 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIMIT_MODE_HPP
# define LIMIT_MODE_HPP

# include "../Server.hpp"

namespace Modes {
    void setLimit(Server& server, int client_fd, const std::string& channel, int limit);
}

#endif
