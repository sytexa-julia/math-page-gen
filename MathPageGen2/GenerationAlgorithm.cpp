/*
 +--------------------------------------------------------
 |  Math Page Generator
 |  FILENAME: GenerationAlgorithm.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Monday, October 09, 2006 4:12:18 PM
 +--------------------------------------------------------
 */ 

#include <deque>
#include "GenerationAlgorithm.h"
#include "MathProblem.h"

using std::deque;

GenerationAlgorithm::GenerationAlgorithm( int prblmCnt, int cplxty ) : problemCount( prblmCnt ), complexity( cplxty )
{ }

GenerationAlgorithm::~GenerationAlgorithm( void )
{ }

int GenerationAlgorithm::GetProblemCount( void ) const
{
	return this->problemCount;
}

void GenerationAlgorithm::SetProblemCount( int cnt )
{
	this->problemCount = cnt;
}

int GenerationAlgorithm::GetComplexity( void ) const
{
	return this->complexity;
}

void GenerationAlgorithm::SetComplexity( int cmplxty )
{
	this->complexity = cmplxty;
}

int GenerationAlgorithm::GetMaxEasyProblems( void ) const
{
	switch ( this->complexity )
	{
	case COMPLEXITY_SIMPLE:
		return 5;
		break;
	case COMPLEXITY_AVERAGE:
		return 3;
		break;
	case COMPLEXITY_ADVANCED:
		return 0;
		break;
	default:
		return 3;
		break;
	}
}

int GenerationAlgorithm::GetMinNumForNonEasy( void ) const
{
	switch ( this->complexity )
	{
	case COMPLEXITY_SIMPLE:
		return 4;
		break;
	case COMPLEXITY_AVERAGE:
		return 7;
		break;
	case COMPLEXITY_ADVANCED:
		return 11;
		break;
	default:
		return 7;
		break;
	}
}

int GenerationAlgorithm::GetEasyThreshold( void ) const
{
	switch ( this->complexity )
	{
	case COMPLEXITY_SIMPLE:
		return 2;
		break;
	case COMPLEXITY_AVERAGE:
		return 5;
		break;
	case COMPLEXITY_ADVANCED:
		return 8;
		break;
	default:
		return 5;
		break;
	}
}

bool GenerationAlgorithm::GetRequireOneSingleDigit( void ) const
{
	if ( this->complexity == COMPLEXITY_SIMPLE )
		return true;
	
	return false;
}

bool GenerationAlgorithm::CheckDuplicate( const deque<MathProblem> &haystack, const MathProblem &needle )
{
	if ( haystack.size() < 1 )
		return false;

	if ( haystack.size() > 1 && haystack.front() == haystack.back() )
		return false;
	
	MathProblem needleRev = MathProblem( needle.SecndDigit(), needle.FirstDigit(), needle.Operation() );

	for ( unsigned int i = 0; i < haystack.size(); i++ )
	{
		if ( haystack[i] == needle || haystack[i] == needleRev )
			return true;
	}

	return false;
}
