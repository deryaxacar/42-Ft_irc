/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Key.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:24:06 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 04:24:06 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_MODE_HPP
# define KEY_MODE_HPP

# include "../Server.hpp"
# include <string>

namespace Modes {
    void setKey(Server& server, int client_fd, const std::string& channel, const std::string& key);
}

#endif
