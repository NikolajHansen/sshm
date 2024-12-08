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

std::string Search::get(char *name){
	int count = 0;
	std::string informations;
	char serversearch[BUFFER];

	std::string configfile = Check::getpath();
	int line = Search::line(name);

	FILE *stream_get;
	stream_get = fopen(configfile.c_str(),"r");

	while(fgets(serversearch, BUFFER, stream_get) != NULL){
		count++;
		if(count == line){
			informations = serversearch;
			break;
		}
	}

	fclose(stream_get);
	return informations;
}

int Search::line(char *word){
	int line = 0;
	char serversearch[BUFFER];
	std::string configfile = Check::getpath();

	FILE *stream_line;
	stream_line = fopen(configfile.c_str(),"r");

	while(fgets(serversearch, BUFFER, stream_line) != NULL){
		line++;
		char servername[85], ip[85], user[20], port[10], options[256];
		port[0] = '\0';
		if(sscanf(serversearch, "%s %s %s %s %s", servername, user, ip, port, options) < 4)
			continue;
		else if(servername == NULL)
			continue;
        else if(strcmp(servername,word) == 0 && port[0] != '\0' && servername[0] != '#'){
			fclose(stream_line);
			return line;
		}
	}

	fclose(stream_line);
	return 0;
}

Search::~Search(){
}
