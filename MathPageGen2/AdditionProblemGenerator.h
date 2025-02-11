/*
 +--------------------------------------------------------
 |  Math Page Generator
 |  FILENAME: AdditionProblemGenerator.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Monday, October 09, 2006 4:30:18 PM
 +--------------------------------------------------------
 */ 

#ifndef __ADDITION_PROBLEM_GENERATOR_H
#define __ADDITION_PROBLEM_GENERATOR_H

#include <deque>
#include "GenerationAlgorithm.h"
#include "MathProblem.h"

using std::deque;

class AdditionProblemGenerator :
	public GenerationAlgorithm
{
private:
	deque<MathProblem> *problems;

public:
	AdditionProblemGenerator( int prblmCnt, int cmplxty );
	~AdditionProblemGenerator( void );

	deque<MathProblem> generate( void );
};

#endif
