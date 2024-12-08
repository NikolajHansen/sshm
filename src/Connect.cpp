/***************************************************************************
 *   Copyright (C) 2007-2009 by Patrick Matthäi                            *
 *   pmatthaei@debian.org	                                               *
 *   http://www.Linux-Dev.org/                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "sshm.h"

int Connect::initial(char *serv){
	if(Search::line(serv) != 0){
		std::string serverstring = Search::get(serv);
		session(serverstring, serv);
	} else {
		std::cerr << "Can't find this server. Please have a look at the server list." << std::endl;
	}
	return EXIT_SUCCESS;
}

int Connect::session(std::string server, char *servalias){
	int cut = 0, i = 0;
	std::string ip, port, user, options;

	while(cut < 5){
		if(i > BUFFER){
			std::cerr << "Errorcode -2. Aborting!" << std::endl;
			exit(-2);
		}
		else if(isspace(server[i]) && cut == 0){
			cut++;
		}
		else if(cut == 1 && !isspace(server[i])){
			user += server[i];
		}
		else if(cut == 1 && isspace(server[i])){
			cut++;
		}
		else if(cut == 2 && !isspace(server[i])){
			ip += server[i];
		}
		else if(cut == 2 && isspace(server[i])){
			cut++;
		}
		else if(cut == 3 && !isspace(server[i])){
			port += server[i];
		}
		else if(cut == 3 && isspace(server[i])){
			cut++;
		}
		else if(cut == 4 && !(server[i] == '\0' || server[i] == '\n')){
			options += server[i];
		}
		else if(cut == 4 && server[i] == '\0' || server[i] == '\n'){
			cut++;
		}
		i++;
	}

	std::stringstream ss;
	ss << "ssh -l " << user << " -p " << port << " " << ip;
    if(options[0] != '\0')
        ss << " " << options;
	std::cout << "Connecting now to: " << servalias << std::endl;

	int ReturnCode = system(ss.str().c_str());
	return ReturnCode;
}

Connect::~Connect(){
}
