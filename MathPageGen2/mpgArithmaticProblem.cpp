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
 |  FILENAME: mpgArithmaticProblem.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Monday, October 09, 2006 3:54:50 PM
 +--------------------------------------------------------
 */ 

#include <string>
#include <sstream>

#include "mpgArithmaticProblem.h"
#include "mpgConstants.h"

using std::string;
using std::stringstream;

mpgArithmaticProblem::mpgArithmaticProblem( int type ) : mpgMathProblem( type ), firstDigit( 0 ), secndDigit( 0 ), operation( ADDITION )
{
	ConstructProblem();
}

mpgArithmaticProblem::mpgArithmaticProblem( int fd, int sd, int type ) : mpgMathProblem( type ), firstDigit( fd ), secndDigit( sd )
{
	switch ( type )
	{
	case TYPE_ADDITION:
		operation = ADDITION;
		break;
	case TYPE_SUBTRACTION:
		operation = SUBTRACTION;
		break;
	case TYPE_MULTIPLICATION:
		operation = MULTIPLICATION;
		break;
	case TYPE_DIVISION:
		operation = DIVISION;
		break;
	default:
		operation = ADDITION;
		break;
	}

	ConstructProblem();
}

mpgArithmaticProblem::mpgArithmaticProblem( const mpgArithmaticProblem &prblm ) : firstDigit( prblm.firstDigit ), secndDigit( prblm.secndDigit ), operation( prblm.operation )
{
	ConstructProblem();
}

mpgArithmaticProblem::~mpgArithmaticProblem( void )
{ 
	delete [] terms;
}

const mpgArithmaticProblem &mpgArithmaticProblem::operator=( const mpgArithmaticProblem &right )
{
	if ( &right != this )
	{
		this->firstDigit = right.FirstDigit();
		this->secndDigit = right.SecndDigit();
		this->operation  = right.Operation();
		ConstructProblem();
	}

	return *this;
}

bool mpgArithmaticProblem::operator==( const mpgArithmaticProblem &right ) const
{
	if ( right.firstDigit == this->firstDigit && right.secndDigit == this->secndDigit && 
			right.operation == this->operation )
		return true;

	return false;
}

bool mpgArithmaticProblem::operator!=( const mpgArithmaticProblem &right ) const
{
	return !( right == *this );
}

void mpgArithmaticProblem::ConstructProblem( void )
{
	// Create the term array
	string first, second;
	stringstream intToStr;

	intToStr << firstDigit;
	first = intToStr.str();

	intToStr.str( "" );
	intToStr << secndDigit;
	second = intToStr.str();
	
	terms = new string[ 2 ];
	terms[ 0 ] = first;
	terms[ 1 ] = second;

	// Create the string representation of the problem
	stringstream prbTmp;
	prbTmp << firstDigit << " " << GetOperatorSymbol() << " " << secndDigit;

	SetProblem( prbTmp.str() );
}

const int mpgArithmaticProblem::FirstDigit( void ) const
{
	return this->firstDigit;
}

const int mpgArithmaticProblem::SecndDigit( void ) const
{
	return this->secndDigit;
}

const int mpgArithmaticProblem::Operation( void ) const
{
	return this->operation;
}

string mpgArithmaticProblem::GetOperatorSymbol( void ) const
{
	switch ( this->operation )
	{
	case ADDITION:
		return "+";
	case SUBTRACTION:
		return "-";
	case MULTIPLICATION:
		return "&times;";
	case DIVISION:
		return "&#247;";
	default:
		return "?";
	}
}

double mpgArithmaticProblem::GetSolution( void ) const
{
	switch ( this->operation )
	{
	case ADDITION:
		return firstDigit + secndDigit;
		break;
	case SUBTRACTION:
		return firstDigit - secndDigit;
		break;
	case MULTIPLICATION:
		return firstDigit * secndDigit;
		break;
	case DIVISION:
		return firstDigit / secndDigit;
		break;
	default:
		return 0;
		break;
	}
}

const string *mpgArithmaticProblem::GetTermArray( void ) const
{
	return terms;
}
