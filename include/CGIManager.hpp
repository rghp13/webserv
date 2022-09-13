/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIManager.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:04:01 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/13 17:18:50 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

class CGIManager
{
private:
    /* data */
public:
    CGIManager();
    CGIManager(Request request, conf config);
    CGIManager(const CGIManager &src);
    ~CGIManager();
};
