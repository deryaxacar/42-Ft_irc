/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:54:58 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 03:54:58 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASS_HPP
# define PASS_HPP

# include "../Server.hpp"
# include <sstream>

namespace Commands {
    void passCommand(Server& server, int client_fd, std::istringstream& iss);
}

#endif
