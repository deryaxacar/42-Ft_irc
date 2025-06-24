/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:00:44 by eakman            #+#    #+#             */
/*   Updated: 2025/04/14 21:00:44 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_HPP
# define JOIN_HPP

# include "../Server.hpp"
# include <sstream>

namespace Commands {
    void joinCommand(Server& server, int client_fd, std::istringstream& iss);
}

#endif
