/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIManager.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:04:01 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/24 14:42:53 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

class CGIManager
{
private:
    location                            _location;
	Request							    _request;
	conf							    _config;
    std::map<std::string, std::string>  _env;
    void    initEnv();
    char    **charArray( void ) const;
public:
    CGIManager();
    CGIManager(Request request, conf config, location location);
    CGIManager(const CGIManager &src);
    std::string     runCGI( void );
    ~CGIManager();
};
