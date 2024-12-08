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

void Check::main(){
	if(sshcheck() == 1){
		std::cerr << "Error. Can't find the ssh executable." << std::endl;
		exit(1);
	}
	else if(onstart() == 1){
		std::cerr << "Error. Can't read or write to the configfile." << std::endl;
		exit(2);
	}
}

bool Check::onstart(){
	std::string path = getpath();

	FILE *stream_r;
	if((stream_r = fopen(path.c_str(),"r")) != NULL){
		fclose(stream_r);
		return false;
	}
	else if(Action::cconf(path) == false){
		return false;
	} else {
		return true;
	}
}

bool Check::sshcheck(){
	FILE *ssh_r;
	if((ssh_r = fopen("/usr/bin/ssh","r")) != NULL){
		fclose(ssh_r);
		return false;
	} else {
		return true;
	}
}

std::string Check::getpath(){
	std::string returnValue;

	returnValue += getenv("HOME");
	returnValue += "/.sshm";

	return returnValue;
}

bool Check::fexists(std::string file){
	FILE *stream_e;
	if((stream_e = fopen(file.c_str(),"r")) == NULL){
		return false;
	} else {
		fclose(stream_e);
		return true;
	}
}

bool Check::valid(char *server){
	if(server[0] == '\0' || strlen(server) == 0){
		return false;
	}
	for(unsigned int i=0; i < strlen(server); i++){
		if(!isprint(server[i]) || isspace(server[i]) || server[i] == '#'){
			return false;
		}
	}
	return true;
}

bool Check::port(char *port){
	if(atoi(port) < 1 || atoi(port) > 65536 || strlen(port) < 1){
		return false;
	}
	for(unsigned int i=0; i < strlen(port); i++){
		if(!isdigit(port[i])){
			return false;
		}
	}
	return true;
}

bool Check::username(char *user){
	int slength = strlen(user);
	if(slength < 1 || slength > 20){
		return false;
	}
	for(unsigned int i = 0; i < slength; i++){
		if(!isprint(user[i])){
			return false;
		}
	}
	return true;
}

bool Check::domain(char *domain){
	int slength = strlen(domain);
	if(slength < 1 || slength > 85){
		return false;
	}
	for(unsigned int i=0; i < slength; i++){
		if(!isprint(domain[i])){
			return false;
		}
	}
	return true;
}

Check::~Check(){
}
