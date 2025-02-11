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
 |  FILENAME: mpgAlgebraProbGen.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Monday, October 23, 2006 3:13:04 PM
 +--------------------------------------------------------
 */ 

/*
 * IMPLEMENTATION NOTES:
 * ---------------------
 * This class does not attempt to create and then solve algebra problems.
 * Instead, it creates problems by simple numJulia manipulation, starting
 * with a randomly chosen final solution. The general format for the algorithm
 * is:
 *
 * 1.) Choose a random solution
 * 2.) Choose random modifying terms to add complexity
 * 3.) Calculate an 'equals' values to put on the other side of the equals sign
 * 4.) Assemble the problem as a string and put it in an mpgAlgebraProblem
 *
 * The code is not very 'neat', especially for the generateAdvanced function. The code
 * will be cleaned up over time.
 */

#include <algorithm>
#include <deque>
#include <sstream>
#include <time.h>

#include "mpgAlgebraProbGen.h"
#include "mpgMathProblem.h"
#include "mpgAlgebraProblem.h"
#include "mpgConstants.h"
#include "mpgFraction.h"

using std::deque;
using std::string;
using std::stringstream;

#define VARIABLE_COUNT 9
string mpgAlgebraProbGen::variables[ 9 ] = { "x", "y", "z", "p", "q", "r", "a", "b", "c" };

mpgAlgebraProbGen::mpgAlgebraProbGen( void ) : mpgGenerationAlgorithm()
{ }

mpgAlgebraProbGen::mpgAlgebraProbGen( int prblmCnt, int cmplxty ) : mpgGenerationAlgorithm( prblmCnt, cmplxty, 1 )
{ }

deque<mpgMathProblem *> mpgAlgebraProbGen::generate( void )
{
	clearProblemStore();
	
	srand( ( unsigned int ) time( NULL ) );

	switch ( GetComplexity() )
	{
	case COMPLEXITY_SIMPLE:
		generateSimple();
		break;

	case COMPLEXITY_AVERAGE:
		generateAverage();
		break;

	case COMPLEXITY_ADVANCED:
		generateAdvanced();
		break;

	default:
		generateSimple();
		break;
	}

	return *problems;
}

/*
 * Creates very basic simplification problems of the form
 * 2x + 1 = 5; sltn: x = 2
 */
void mpgAlgebraProbGen::generateSimple( void )
{
	clearProblemStore();
	
	srand( ( unsigned int ) time( NULL ) );

	int solution, multiplier, other, equals, sign, temp;
	int negCount = 0, maxNegative = int( GetProblemCount() / 3 );
	int progress;
	string var, signStr;
	stringstream assembler;

	UpdateStatus( "Generating simple algebra problems..." );
	
	for ( int i = 0; i < GetPageCount(); i++ )
	{
		for ( int j = 0; j < GetProblemCount(); j++ )
		{
			assembler.str( "" );

			// The Solution...
			solution = int( ( 12 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;

			// Add a little negativeness?
			temp = ( int( ( 30 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1 );

			if ( GetAllowNegative() && temp % 3 == 0 && negCount < maxNegative )
			{
				solution *= -1;
				negCount++;
			}

			// Create the other operands
			multiplier = int( ( 11 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;
			other = int( ( 18 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;
			
			// Add or subtract?
			temp = ( int( ( 30 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1 );
			if ( temp % 2 == 0 )
			{
				sign = 1;
				signStr = "+";
			}
			else
			{
				sign = -1;
				signStr = "-";
			}

			// Figure out what it all equals
			equals = solution * multiplier + other * sign;

			// Pick a variable to use
			temp = int( ( ( VARIABLE_COUNT ) * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;
			var = variables[ temp - 1 ];

			// Assemble the problem
			assembler << multiplier << var << " " << signStr << " " << other << " = " << equals;
		
			problems->push_back( new mpgAlgebraProblem( assembler.str(), var, solution ) );

			progress = int( 100 * ( ( j + 1 ) + ( i * GetProblemCount() ) ) / ( GetPageCount() * GetProblemCount() ) );
			UpdateStatus( "Generating simple algebra problems...", progress );
		}

		negCount = 0;
	}
}

/*
 * Adds an extra variable term. Number size increases.
 */
void mpgAlgebraProbGen::generateAverage( void )
{
	clearProblemStore();
	
	srand( ( unsigned int ) time( NULL ) );

    int solution, multiplier, adder, other, equals, sign, temp;
	int negCount = 0, maxNegative = int( GetProblemCount() / 3 );
	int progress;
	string var, signStr, otherSignStr;
	stringstream assembler;

	UpdateStatus( "Generating average algebra problems..." );
	
	for ( int i = 0; i < GetPageCount(); i++ )
	{
		for ( int j = 0; j < GetProblemCount(); j++ )
		{
			assembler.str( "" );

			// The Solution...
			solution = int( ( 18 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;

			// Add a little negativeness?
			temp = ( int( ( 30 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1 );

			if ( GetAllowNegative() && temp % 3 == 0 && negCount < maxNegative )
			{
				solution *= -1;
				negCount++;
			}

			// Create the other operands
			multiplier = int( ( 14 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;
			adder = int( ( 18 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;

			// adder: add or subtract?
			temp = ( int( ( 30 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1 );
			if ( temp % 2 == 0 )
			{
				sign = 1;
				signStr = "+";
			}
			else
			{
				sign = -1;
				signStr = "-";
			}

			// Figure out what it all equals
			equals = solution * multiplier + adder * sign;

			// Add in another term
			do
				other = int( ( 18 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;
			while ( other == multiplier );

			// other: Add or subtract?
			temp = ( int( ( 30 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1 );
			if ( temp % 2 == 0 )
			{
				multiplier += other;
				otherSignStr = "+";
			}
			else
			{
				multiplier -= other;
				otherSignStr = "-";
			}

			// Pick a variable to use
			temp = int( ( ( VARIABLE_COUNT ) * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;
			var = variables[ temp - 1 ];

			// Assemble the problem
			assembler << multiplier << var << " " << signStr << " " << adder << " = " << equals << " "  << otherSignStr << " " << other << var;
		
			problems->push_back( new mpgAlgebraProblem( assembler.str(), var, solution ) );

			progress = int( 100 * ( ( j + 1 ) + ( i * GetProblemCount() ) ) / ( GetPageCount() * GetProblemCount() ) );
			UpdateStatus( "Generating average algebra problems...", progress );
		}

		negCount = 0;
	}
}

/*
 * Adds constant distribution complexity. Number sizes do not increase.
 */
void mpgAlgebraProbGen::generateAdvanced( void )
{
	clearProblemStore();
	
	srand( ( unsigned int ) time( NULL ) );

	int solution, multiplier, adder, other, equals, sign, distrib, temp;
	int negCount = 0, maxNegative = int( GetProblemCount() / 3 );
	int progress;
	string var, signStr, otherSignStr;
	stringstream assembler;

	UpdateStatus( "Generating advanced algebra problems..." );
	
	for ( int i = 0; i < GetPageCount(); i++ )
	{
		for ( int j = 0; j < GetProblemCount(); j++ )
		{
			assembler.str( "" );

			// The Solution...
			solution = int( ( 18 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;

			// Add a little negativeness?
			temp = ( int( ( 30 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1 );

			if ( GetAllowNegative() && temp % 3 == 0 && negCount < maxNegative )
			{
				solution *= -1;
				negCount++;
			}

			// Create the other operands
			multiplier = int( ( 14 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;
			adder = int( ( 18 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;

			// adder: add or subtract?
			temp = ( int( ( 30 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1 );
			if ( temp % 2 == 0 )
			{
				sign = 1;
				signStr = "+";
			}
			else
			{
				sign = -1;
				signStr = "-";
			}

			// Figure out what it all equals
			equals = solution * multiplier + adder * sign;

			// Add in another term
			do
				other = int( ( 18 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;
			while ( other == multiplier );

			// other: Add or subtract?
			temp = ( int( ( 30 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1 );
			if ( temp % 2 == 0 )
			{
				multiplier += other;
				otherSignStr = "+";
			}
			else
			{
				multiplier -= other;
				other *= -1;
				otherSignStr = "-";
			}

			// Choose a number for distribution
			distrib = int( ( 10 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;
			
			// distrib: negative or positive?
			temp = ( int( ( 30 * rand() / ( RAND_MAX + 1.0 ) ) ) + 1 );
			if ( temp % 2 != 0 )
			{
				distrib *= -1;
			}

			// Pick a variable to use
			temp = int( ( ( VARIABLE_COUNT ) * rand() / ( RAND_MAX + 1.0 ) ) ) + 1;
			var = variables[ temp - 1 ];
			
			// Re-figure the sign on the right
			if ( distrib * other < 0 )
				otherSignStr = "-";
			else
				otherSignStr = "+";

			// Assemble the problem
			assembler << distrib << "(" << multiplier << var << " " << signStr << " " << adder;
			assembler << ") = " << distrib * equals << " "  << otherSignStr << " " << abs( distrib * other ) << var;
		
			problems->push_back( new mpgAlgebraProblem( assembler.str(), var, solution ) );

			progress = int( 100 * ( ( j + 1 ) + ( i * GetProblemCount() ) ) / ( GetPageCount() * GetProblemCount() ) );
			UpdateStatus( "Generating advanced algebra problems...", progress );
		}

		negCount = 0;
	}
}
