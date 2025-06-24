/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Op.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:41:19 by ndogan            #+#    #+#             */
/*   Updated: 2025/06/24 15:41:19 by ndogan           ###   ########.fr       */
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
