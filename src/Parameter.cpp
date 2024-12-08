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

int Parameter::help(char *exec){
	std::cout << "Usage of " << exec << ":\n" << std::endl;
	std::cout << "\t--help\t\tDisplays the help." << std::endl;
	std::cout << "\t--version\tDisplays the program version." << std::endl;
	std::cout << "\t--list\t\tLists all servers." << std::endl;
	std::cout << "\t--add\t\tAdds a server." << std::endl;
	std::cout << "\t--del [name]\tDeletes a server." << std::endl;
	std::cout << "\t--show [name]\tShows information about a given server." << std::endl;
	std::cout << "\nTo connect to a server, you only have to give the serveralias as an argument." << std::endl;
	std::cout << "\nNote: You can use all parameters in the format like \'-h\'." << std::endl;
	return EXIT_SUCCESS;
}

int Parameter::wrong(char *exec){
	std::cerr << "You have entered too many arguments.\nPlease have a look at the help." << std::endl;
	return EXIT_SUCCESS;
}

int Parameter::version(char *exec){
	std::cout << exec << " version: " << SSHMVERSION << std::endl;
	return EXIT_SUCCESS;
}

int Parameter::add(){
	std::string configfile = Check::getpath();
	char servername[90], ip[90], user[25], port[15]; //***

	std::cout << "Enter your connection data for the server:" << std::endl;

	while(true){
		std::cout << "\nHostname/IP: ";
		std::cin >> ip;
		if(Check::domain(ip) == false){
			std::cerr << "\nError. Only 85 chars are allowed for the hostname. Please reenter it." << std::endl;
		} else {
			break;
		}
	}

	while(true){
		std::cout << "\nPort: ";
		std::cin >> port;
		if(Check::port(port) == false){
			std::cerr << "\nError. The port " << port << " isn't valid. Please reenter it." << std::endl;
		} else {
			break;
		}
	}

	while(true){
		std::cout << "\nUsername: ";
		std::cin >> user;
		if(Check::username(user) == false){
			std::cerr << "\nError. Only 20 chars are allowed for the username. Please reenter it." << std::endl;
		} else {
			break;
		}
	}

	while(true){
		std::cout << "\nServeralias: ";
		std::cin >> servername;
		if(Search::line(servername) != 0){
			std::cerr << "\nError. This serveralias is already used, please choose another one." << std::endl;
		}
		else if(Check::valid(servername) == false){
			std::cerr << "\nError. The serveralias contains unallowed characters such as \'#\'." << std::endl;
		} else {
			break;
		}
	}

	FILE *stream_add;
	stream_add = fopen(configfile.c_str(),"a");
	fprintf(stream_add, "%s %s %s %s\n", servername, user, ip, port);
	fclose(stream_add);

	if(Search::line(servername) != 0){
		std::cout << "\nAdded server." << std::endl;
	} else {
		std::cerr << "You have to define a serveralias to delete." << std::endl;
	}

	return EXIT_SUCCESS;
}

int Parameter::del(char *todel){
	if(!todel){
		std::cerr << "You habe to define a serveralias to delete." << std::endl;
		return EXIT_SUCCESS;
	}
	else if(Search::line(todel) == 0){
		std::cerr << "Can't find this server at the configfile. Please have a look at the --list option." << std::endl;
		return EXIT_SUCCESS;
	}
	else if(Action::del(todel) == true){
		std::cout << "Deleted the server." << std::endl;
	} else {
		std::cerr << "An error occurred while deleting the entry." << std::endl;
	}
	return EXIT_SUCCESS;
}

int Parameter::show(char *arg){
	if(!arg){
		std::cerr << "You have to define a serveralias." << std::endl;
		return EXIT_SUCCESS;
	}

	std::string server = Search::get(arg);
	std::cout << "Serveralias / User / Hostname / Port:\n" << server << std::endl;

	return EXIT_SUCCESS;
}

int Parameter::list(char *search){
	unsigned int counter=0;
	char serverlist[BUFFER];

	std::string configfile = Check::getpath();
	FILE *stream_list;
	stream_list = fopen(configfile.c_str(),"r");

	while(fgets(serverlist, BUFFER, stream_list) != NULL){
		char servername[85], ip[85], user[20], port[10], options[256];
		port[0] = '\0';
		options[0] = '\0';
		if(sscanf(serverlist, "%s %s %s %s", servername, user, ip, port) != 4){
			continue;
		}
		else if(servername[0] == '\0' || port[0] == '\0' || servername[0] == '#' || servername[0] == '\n'){
			continue;
		}
		else if(search && strstr(serverlist,search) == 0){
			continue;
		} else {
            unsigned int pos = strlen(servername) + 1 + strlen(user) + 1 + strlen(ip) + 1 + strlen(port) + 1;
            if(strlen(serverlist)>pos){
                strncpy(options, serverlist+pos, 256);
                if(options[strlen(options)-1]=='\n')
                    options[strlen(options)-1] = '\0';
            }
			counter++;
			if(counter == 1){
				std::cout << "List of all added servers:" << std::endl;
				std::cout << "\t#\tServeralias\tUser @ Hostname : Port\t[Options]\n" << std::endl;
			}
			std::string tabs = "\t";
			if(strlen(servername) < 8){
				tabs += "\t";
			}
			std::cout << "\t" << counter << ".\t" << servername << tabs << user << "@" << ip << ":" << port;
            if(options[0] != '\0')
                std::cout << "\t" << "[" << options << "]";
            std::cout << std::endl;
		}
	}

	if(counter == 0){
		std::cout << "No server found." << std::endl;
	}

	fclose(stream_list);
	return EXIT_SUCCESS;
}

Parameter::~Parameter(){
}
