/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Op.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:29:05 by eakman            #+#    #+#             */
/*   Updated: 2025/04/15 04:29:05 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_MODE_HPP
# define OPERATOR_MODE_HPP

# include "../Server.hpp"
# include <string>

namespace Modes {
    void setOperator(Server& server, int client_fd, const std::string& channel, const std::string& targetNick, bool enable);
}

#endif
