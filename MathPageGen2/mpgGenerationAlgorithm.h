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
 |  FILENAME: mpgGenerationAlgorithm.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Monday, October 09, 2006 4:12:23 PM
 +--------------------------------------------------------
 */ 

#ifndef __MPG_GENERATION_ALGORITHM_H
#define __MPG_GENERATION_ALGORITHM_H

#include <deque>

#include "mpgMathProblem.h"
#include "mpgArithmaticProblem.h"
#include "mpgConstants.h"
#include "mpgStatusBar.h"

using std::deque;

class mpgGenerationAlgorithm
{
private:
	int problemCount;
	int complexity;
	int pageCount;

	bool allowNegativeSolutions;
	bool requireWholeSolutions;

	mpgStatusBar *statusBar;

public:
	mpgGenerationAlgorithm( void );
	mpgGenerationAlgorithm( int prblmCnt, int cplxty = COMPLEXITY_AVERAGE, int pgCnt = 1, bool allowNeg = false, bool requireWhole = true );
	virtual ~mpgGenerationAlgorithm( void );

	void SetStatusBar( mpgStatusBar * const stbar );

	int GetProblemCount( void ) const;
	void SetProblemCount( int cnt );
	int GetComplexity( void ) const;
	void SetComplexity( int cmplxty );
	int GetPageCount( void ) const;
	void SetPageCount( int cnt );
	bool GetAllowNegative( void ) const;
	void SetAllowNegative( bool a );
	bool GetRequireWholeSolutions( void ) const;
	void SetRequireWholeSolutions( bool r );
	int GetMaxEasyProblems( void ) const;
	int GetMinNumForNonEasy( void ) const;
	int GetEasyThreshold( void ) const;
	bool GetRequireOneSingleDigit( void ) const;

	virtual deque<mpgMathProblem *> generate( void ) = 0;

protected:
	deque<mpgMathProblem *> *problems;

	void UpdateStatus( string msg = "Ready.", int percent = 0 );

	bool CheckDuplicate( const deque<mpgArithmaticProblem> &haystack, const mpgArithmaticProblem &needle, const unsigned int startPos = 0 );
	virtual void clearProblemStore( void );
};

#endif
