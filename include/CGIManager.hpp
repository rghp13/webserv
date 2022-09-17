/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIManager.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:04:01 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/17 16:35:39 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

class CGIManager
{
private:
	Request							_request;
	conf							_config;
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
