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
 |  FILENAME: mpgAlgebraProblem.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Monday, October 23, 2006 4:18:58 PM
 +--------------------------------------------------------
 */ 

#include "mpgAlgebraProblem.h"
#include "mpgConstants.h"

mpgAlgebraProblem::mpgAlgebraProblem( void ) : mpgMathProblem( TYPE_ALGEBRA, "" ), problem( "" ), solution( 0.0 )
{ }

mpgAlgebraProblem::mpgAlgebraProblem( const string &prob, const string &var, const double sltn ) : mpgMathProblem( TYPE_ALGEBRA, prob ), variable( var ), solution( sltn )
{ }

mpgAlgebraProblem::~mpgAlgebraProblem( void )
{ }

void mpgAlgebraProblem::SetSolution( double sol )
{
	this->solution = sol;
}

double mpgAlgebraProblem::GetSolution( void ) const
{
	return this->solution;
}

void mpgAlgebraProblem::SetVariable( const string &var )
{
	this->variable = var;
}

string mpgAlgebraProblem::GetVariable( void ) const
{
	return this->variable;
}

// Note: this method is not implemented, as algebra problems
// are usually displayed horizontally.
const string *mpgAlgebraProblem::GetTermArray( void )
{
	return NULL;
}
