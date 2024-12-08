/***************************************************************************
 *   Copyright (C) 2007-2009 by Patrick Matthäi                            *
 *   pmatthaei@debian.org								                   *
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

bool Action::cconf(std::string path){
	FILE *stream_w;
	if((stream_w = fopen(path.c_str(),"w")) != NULL){
		fputs("# Configfile from sshm\n", stream_w);
		fclose(stream_w);
		return false;
	} else {
		return true;
	}
}

bool Action::del(char *delentry){
	int count = 0;
	int line = Search::line(delentry);

	if(line == 0){
		std::cerr << "Second check can't find server in the list. Fatal error." << std::endl;
		exit(-1);
	}

	char serversearch[BUFFER], servercopy[BUFFER];
	std::string configfile = Check::getpath();
	FILE *stream_del, *stream_tmp, *stream_rw;

	char tmp_pattern[20];
	strcpy(tmp_pattern,"/tmp/sshm.XXXXXX");

	int tmp_file = mkstemp(tmp_pattern);
	if(tmp_file == -1){
		std::cerr << "Couldn't open temporary file. Error!" << std::endl;
		exit(-2);
	}
	else if(!(stream_tmp = fdopen(tmp_file,"a+"))){
		std::cerr << "Couldn't create temporary file descriptor. Error!" << std::endl;
		exit(-2);
	}

	stream_del = fopen(configfile.c_str(),"r");

	while(fgets(serversearch, BUFFER, stream_del) != NULL){
		count++;
		if(count != line){
			fputs(serversearch, stream_tmp);
			fflush(stream_tmp);
		}
	}

	fclose(stream_del);

	stream_rw = fopen(configfile.c_str(),"w");
	fseek(stream_tmp, 0L, SEEK_SET);
	while(fgets(servercopy, BUFFER, stream_tmp) != NULL){
		fputs(servercopy, stream_rw);
	}

	fclose(stream_rw);
	fclose(stream_tmp);

	if(unlink(tmp_pattern) == -1){
		perror("Error at removing the temporary file.");
		exit(-4);
	}
	return true;
}

Action::~Action(){
}
