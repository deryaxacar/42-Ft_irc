/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:53:45 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 03:53:45 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "../Server.hpp"
# include <sstream>

namespace Commands {
    void userCommand(Server& server, int client_fd, std::istringstream& iss);
}

#endif
