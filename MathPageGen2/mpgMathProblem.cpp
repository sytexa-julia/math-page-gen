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
 |  FILENAME: mpgMathProblem.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Monday, October 09, 2006 3:54:50 PM
 +--------------------------------------------------------
 */ 

#include "mpgMathProblem.h"

mpgMathProblem::mpgMathProblem( void ) : probType( -1 ), problem( string( "No problem created." ) )
{ }

mpgMathProblem::mpgMathProblem( int type ) : probType( type ), problem( string( "No problem created." ) )
{ }

mpgMathProblem::mpgMathProblem( int type, const string &prblm ) : probType( type ), problem( string( prblm ) )
{ }

mpgMathProblem::~mpgMathProblem( void )
{ }

void mpgMathProblem::SetProblem( const string &prblm )
{
	problem = string( prblm );
}

const string &mpgMathProblem::GetProblem( void ) const
{
	return problem;
}

int mpgMathProblem::GetProblemType( void ) const
{
	return probType;
}

double mpgMathProblem::GetSolution( void ) const
{
	return 0.0;
}

const string *mpgMathProblem::GetTermArray( void ) const
{
	return NULL;
}

string mpgMathProblem::GetOperatorSymbol( void ) const
{
	return "(!)";
}
