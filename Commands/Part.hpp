/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 00:20:04 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 00:20:04 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PART_HPP
# define PART_HPP

# include "../Server.hpp"
# include <sstream>

namespace Commands {
    void partCommand(Server& server, int client_fd, std::istringstream& iss);
}

#endif
