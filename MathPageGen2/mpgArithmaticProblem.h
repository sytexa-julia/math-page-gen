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
 |  FILENAME: mpgArithmaticProblem.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Monday, October 09, 2006 3:55:00 PM
 +--------------------------------------------------------
 */ 

#ifndef __MPG_ARITHMATIC_PROBLEM_H
#define __MPG_ARITHMATIC_PROBLEM_H

#include <string>
#include "mpgMathProblem.h"

using std::string;

class mpgArithmaticProblem : 
	public mpgMathProblem
{
private:
	int firstDigit;
	int secndDigit;
	int operation;

	string *terms;

	void ConstructProblem( void );

public:
	mpgArithmaticProblem( int type );
	mpgArithmaticProblem( int fd, int sd, int type );
	mpgArithmaticProblem( const mpgArithmaticProblem &prblm );
	~mpgArithmaticProblem( void );

	const mpgArithmaticProblem &operator=( const mpgArithmaticProblem &right );
	bool operator==( const mpgArithmaticProblem &right ) const;
	bool operator!=( const mpgArithmaticProblem &right ) const;

	const int FirstDigit( void ) const;
	const int SecndDigit( void ) const;
	const int Operation( void ) const;

	string GetOperatorSymbol( void ) const;

	double GetSolution( void ) const;
	const string *GetTermArray( void ) const;
};

#endif
