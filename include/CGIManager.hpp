/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIManager.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:04:01 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/16 19:16:29 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

class CGIManager
{
private:
    std::vector<t_header_argument>  _env;
    void    initEnv(Request request, conf config);
    char    **charArray( void ) const;
public:
    CGIManager();
    CGIManager(Request request, conf config);
    CGIManager(const CGIManager &src);
    std::string     runCGI( void );
    ~CGIManager();
};
