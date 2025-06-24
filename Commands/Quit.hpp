/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quite.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 00:14:49 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 00:14:49 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUIT_HPP
# define QUIT_HPP

# include "../Server.hpp"
# include <sstream>

namespace Commands {
    void quitCommand(Server& server, int client_fd, std::istringstream& iss);
}

#endif
