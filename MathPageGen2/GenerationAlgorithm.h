/*
 +--------------------------------------------------------
 |  Math Page Generator
 |  FILENAME: GenerationAlgorithm.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Monday, October 09, 2006 4:12:23 PM
 +--------------------------------------------------------
 */ 

#ifndef __GENERATION_ALGORITHM_H
#define __GENERATION_ALGORITHM_H

#include <deque>
#include "MathProblem.h"

using std::deque;

class GenerationAlgorithm
{
private:
	int problemCount;
	int complexity;

	int maxEasy;
	int minNonEasyNum;
	int easyThreshold;

	bool requireOneSingleDigit;

public:
	GenerationAlgorithm( int prblmCnt, int cplxty = 1 );	// Default complexity is 'Moderate'
	virtual ~GenerationAlgorithm( void );

	int GetProblemCount( void ) const;
	void SetProblemCount( int cnt );
	int GetComplexity( void ) const;
	void SetComplexity( int cmplxty );
	int GetMaxEasyProblems( void ) const;
	int GetMinNumForNonEasy( void ) const;
	int GetEasyThreshold( void ) const;
	bool GetRequireOneSingleDigit( void ) const;

	virtual deque<MathProblem> generate( void ) = 0;

protected:
	bool CheckDuplicate( const deque<MathProblem> &needle, const MathProblem &haystack);
};

enum Complexity
{
	COMPLEXITY_SIMPLE = 1,
	COMPLEXITY_AVERAGE,
	COMPLEXITY_ADVANCED
};

#endif
