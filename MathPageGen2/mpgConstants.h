/*
 * Math Page Generator 2.0 is an educational tool for building arithmetic skills.
 * Copyright (C) 2006  Julia Anderson
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 *
 * The full text of the GNU GPL v2 is included with this distribution in
 * a file called LICENSE.TXT.
 */

/*
 +--------------------------------------------------------
 |  Math Page Generator
 |  FILENAME: mpgConstants.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Tuesday, October 17, 2006 9:54:35 PM
 +--------------------------------------------------------
 */ 

#ifndef __MPG_CONSTANTS_H
#define __MPG_CONSTANTS_H

#include <string>

using std::string;

static const string APP_VERSION = "2.0.0";

enum ProblemType
{
	TYPE_ADDITION = 0,
	TYPE_SUBTRACTION,
	TYPE_MULTIPLICATION,
	TYPE_ALGEBRA,
	TYPE_DIVISION
};

enum Complexity
{
	COMPLEXITY_SIMPLE = 1,
	COMPLEXITY_AVERAGE,
	COMPLEXITY_ADVANCED,
	COMPLEXITY_LARGENUMS
};

enum Operators
{
	ADDITION = 0,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION
};

enum Orientation
{
	HORIZONTAL = 0,
	VERTICAL
};


#endif