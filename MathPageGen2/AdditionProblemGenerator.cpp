/*
 +--------------------------------------------------------
 |  Math Page Generator
 |  FILENAME: AdditionProblemGenerator.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Monday, October 09, 2006 4:31:09 PM
 +--------------------------------------------------------
 */ 

#include <algorithm>
#include <deque>
#include <time.h>
#include "AdditionProblemGenerator.h"
#include "MathProblem.h"

using std::deque;

AdditionProblemGenerator::AdditionProblemGenerator( int prblmCnt, int cmplxty ) : GenerationAlgorithm( prblmCnt, cmplxty )
{
	problems = new deque<MathProblem>;
}

AdditionProblemGenerator::~AdditionProblemGenerator(void)
{
	delete problems;
}

deque<MathProblem> AdditionProblemGenerator::generate( void )
{
	srand( ( unsigned int ) time( NULL ) );

	int a, b, easyCount = 0;
	bool currEasy = false;

	for ( int i = 0; i < GetProblemCount(); i++ )
	{
		a = int( ( ( 15 * GetComplexity() + 1 ) * rand() / ( RAND_MAX + 1.0 ) ) );
		b = int( ( ( 15 * GetComplexity() + 1 ) * rand() / ( RAND_MAX + 1.0 ) ) );

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
			a = int( ( ( 15 * GetComplexity() + 1 ) * rand() / ( RAND_MAX + 1.0 ) ) ) + GetMinNumForNonEasy();
			b = int( ( ( 15 * GetComplexity() + 1 ) * rand() / ( RAND_MAX + 1.0 ) ) ) + GetMinNumForNonEasy();

			if ( GetRequireOneSingleDigit() && a > 9 && b > 9 )
			{
				while ( a > 9 )
					a = int( ( ( 15 * GetComplexity() + 1 ) * rand() / ( RAND_MAX + 1.0 ) ) );
			}
		}

		// If this problem is a duplicate, don't add it to the list and 
		// run an extra iteration of the loop
		if ( !CheckDuplicate( *problems, MathProblem( a, b, ADDITION ) ) )
			problems->push_back( MathProblem( a, b, ADDITION ) );
		else
			i--;

		currEasy = false;
	}

	random_shuffle( problems->begin(), problems->end() );

	return *problems;
}