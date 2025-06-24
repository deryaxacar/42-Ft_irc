/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:19:06 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 04:19:06 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
# define MODE_HPP

# include "../Server.hpp"
# include <sstream>

namespace Commands {
    void modeCommand(Server& server, int client_fd, std::istringstream& iss);
}

#endif
