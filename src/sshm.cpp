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

int main(int argc, char *argv[]){
	Check::main();

	if(argc > 3){
		Parameter::wrong(argv[0]);
	}
	else if(argc < 2 || strcmp(argv[1],"--help") == 0 || strcmp(argv[1],"-h") == 0){
		Parameter::help(argv[0]);
	}
	else if(strcmp(argv[1],"--version") == 0 || strcmp(argv[1],"-v") == 0){
		Parameter::version(argv[0]);
	}
	else if(strcmp(argv[1],"--list") == 0 || strcmp(argv[1],"-l") == 0){
		Parameter::list(argv[2]);
	}
	else if(strcmp(argv[1],"--add") == 0 || strcmp(argv[1],"-a") == 0){
		Parameter::add();
	}
	else if(strcmp(argv[1],"--del") == 0 || strcmp(argv[1],"-d") == 0){
		Parameter::del(argv[2]);
	}
	else if(strcmp(argv[1],"--show") == 0 || strcmp(argv[1],"-s") == 0){
		Parameter::show(argv[2]);
	} else {
		Connect::initial(argv[1]);
	}
	return EXIT_SUCCESS;
}
