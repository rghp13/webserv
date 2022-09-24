/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIManager.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:04:01 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/24 02:00:25 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

class CGIManager
{
private:
	Request							    _request;
	conf							    _config;
    std::map<std::string, std::string>  _env;
    void    initEnv(Request request, conf config);
    char    **charArray( void ) const;
public:
    CGIManager();
    CGIManager(Request request, conf config);
    CGIManager(const CGIManager &src);
    std::string     runCGI( void );
    ~CGIManager();
};
