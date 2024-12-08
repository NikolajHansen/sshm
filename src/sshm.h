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

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cctype>
#include <climits>
#include <unistd.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define SSHMVERSION "0.4.2"
#define BUFFER 200
#define RANDTEMPLEN 7

#include "Action.h"
#include "Parameter.h"
#include "Check.h"
#include "Connect.h"
#include "Search.h"
