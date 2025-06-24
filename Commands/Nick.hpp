/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 00:29:16 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 00:29:16 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICK_HPP
# define NICK_HPP

# include "../Server.hpp"
# include <sstream>

namespace Commands {
    void nickCommand(Server& server, int client_fd, std::istringstream& iss);
}

#endif
