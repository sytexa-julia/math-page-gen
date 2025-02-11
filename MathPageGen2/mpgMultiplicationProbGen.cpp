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
 |  FILENAME: mpgMultiplicationProbGen.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Saturday, October 21, 2006 6:13:15 PM
 +--------------------------------------------------------
 */

#include <algorithm>
#include <deque>
#include <time.h>

#include "mpgMultiplicationProbGen.h"
#include "mpgArithmaticProblem.h"
#include "mpgConstants.h"

using std::deque;

mpgMultiplicationProbGen::mpgMultiplicationProbGen( void ) : mpgGenerationAlgorithm()
{ }

mpgMultiplicationProbGen::mpgMultiplicationProbGen( int prblmCnt, int cmplxty ) : mpgGenerationAlgorithm( prblmCnt, cmplxty, 1 )
{ }

deque<mpgMathProblem *> mpgMultiplicationProbGen::generate( void )
{
	clearProblemStore();
	
	srand( ( unsigned int ) time( NULL ) );

	int a, b, easyCount = 0;
	int progress;
	bool currEasy = false;
	deque<mpgArithmaticProblem> tempProblems;

	UpdateStatus( "Generating multiplication problems..." );

	for ( int i = 0; i < GetPageCount(); i++ )
	{
		for ( int j = 0; j < GetProblemCount(); j++ )
		{
			a = int( ( ( 12 * GetComplexity() + 1 ) * rand() / ( RAND_MAX + 1.0 ) ) );
			b = int( ( ( 12 * GetComplexity() + 1 ) * rand() / ( RAND_MAX + 1.0 ) ) );

			// If we want 'Simple' problems, at least one of the numbers should be single digit
			if ( GetRequireOneSingleDigit() && a > 9 && b > 9 )
			{
				while ( b > 9 )
					b = int( ( ( 15 * GetComplexity() + 1 ) * rand() / ( RAND_MAX + 1.0 ) ) );
			}

			if ( a <= GetEasyThreshold() || b <= GetEasyThreshold() )
			{
				currEasy = true;
				easyCount++;
			}

			if ( currEasy && easyCount > GetMaxEasyProblems() )
			{
				a = int( ( ( 12 * GetComplexity() + 1 ) * rand() / ( RAND_MAX + 1.0 ) ) ) + GetMinNumForNonEasy();
				b = int( ( ( 12 * GetComplexity() + 1 ) * rand() / ( RAND_MAX + 1.0 ) ) ) + GetMinNumForNonEasy();

				if ( GetRequireOneSingleDigit() && a > 9 && b > 9 )
				{
					while ( a > 9 )
						a = int( ( ( 15 * GetComplexity() + 1 ) * rand() / ( RAND_MAX + 1.0 ) ) );
				}

				easyCount--;
			}

			// If this problem is a duplicate, don't add it to the list and 
			// run an extra iteration of the loop
			if ( !CheckDuplicate( tempProblems, mpgArithmaticProblem( a, b, TYPE_MULTIPLICATION ), i * GetProblemCount() ) )
			{
				tempProblems.push_back( mpgArithmaticProblem( a, b, TYPE_MULTIPLICATION ) );
				problems->push_back( new mpgArithmaticProblem( a, b, TYPE_MULTIPLICATION ) );

				progress = int( 100 * ( ( j + 1 ) + ( i * GetProblemCount() ) ) / ( GetPageCount() * GetProblemCount() ) );
				UpdateStatus( "Generating multiplication problems...", progress );
			}
			else
			{
				j--;
			}

			currEasy = false;
		}

		easyCount = 0;
	}

	random_shuffle( problems->begin(), problems->end() );

	return *problems;
}
