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
 |  FILENAME: mpgGenerationAlgorithm.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Monday, October 09, 2006 4:12:18 PM
 +--------------------------------------------------------
 */ 

#include <deque>

#include "wxUtilities.h"

#include "mpgGenerationAlgorithm.h"
#include "mpgMathProblem.h"
#include "mpgArithmaticProblem.h"
#include "mpgConstants.h"
#include "mpgStatusBar.h"

using std::deque;

mpgGenerationAlgorithm::mpgGenerationAlgorithm( void ) : problemCount( 50 ), complexity( COMPLEXITY_AVERAGE ), pageCount( 1 ), allowNegativeSolutions( false ), requireWholeSolutions( true )
{
	problems = new deque< mpgMathProblem * >;
}

mpgGenerationAlgorithm::mpgGenerationAlgorithm( int prblmCnt, int cplxty, int pgCnt, bool allowNeg, bool requireWhole ) : problemCount( prblmCnt ), complexity( cplxty ), pageCount( pgCnt), allowNegativeSolutions( allowNeg ), requireWholeSolutions( requireWhole )
{
	problems = new deque< mpgMathProblem * >;
}

mpgGenerationAlgorithm::~mpgGenerationAlgorithm( void )
{
	clearProblemStore();
	delete problems;
}

void mpgGenerationAlgorithm::SetStatusBar( mpgStatusBar * const stbar )
{
	this->statusBar = stbar;
}

int mpgGenerationAlgorithm::GetProblemCount( void ) const
{
	return this->problemCount;
}

void mpgGenerationAlgorithm::SetProblemCount( int cnt )
{
	this->problemCount = cnt;
}

int mpgGenerationAlgorithm::GetComplexity( void ) const
{
	return this->complexity;
}

void mpgGenerationAlgorithm::SetComplexity( int cmplxty )
{
	this->complexity = cmplxty;
}

int mpgGenerationAlgorithm::GetPageCount( void ) const
{
	return this->pageCount;
}

void mpgGenerationAlgorithm::SetPageCount( int cnt )
{
	this->pageCount = cnt;
}

bool mpgGenerationAlgorithm::GetAllowNegative( void ) const
{
	return this->allowNegativeSolutions;
}

void mpgGenerationAlgorithm::SetAllowNegative( bool a )
{
	this->allowNegativeSolutions = a;
}

bool mpgGenerationAlgorithm::GetRequireWholeSolutions( void ) const
{
	return this->requireWholeSolutions;
}

void mpgGenerationAlgorithm::SetRequireWholeSolutions( bool r )
{
	this->requireWholeSolutions = r;
}

int mpgGenerationAlgorithm::GetMaxEasyProblems( void ) const
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

int mpgGenerationAlgorithm::GetMinNumForNonEasy( void ) const
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

int mpgGenerationAlgorithm::GetEasyThreshold( void ) const
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

bool mpgGenerationAlgorithm::GetRequireOneSingleDigit( void ) const
{
	if ( this->complexity == COMPLEXITY_SIMPLE )
		return true;
	
	return false;
}

void mpgGenerationAlgorithm::UpdateStatus( string msg, int percent )
{
	if ( this->statusBar )
	{
		statusBar->UpdateStatus( wxUtilities::string2wxString( msg ), percent );
	}
}

bool mpgGenerationAlgorithm::CheckDuplicate( const deque<mpgArithmaticProblem> &haystack, const mpgArithmaticProblem &needle, const unsigned int startPos )
{
	if ( haystack.size() < 1 )
		return false;

	if ( haystack.size() > 1 && haystack.front() == haystack.back() )
		return false;
	
	mpgArithmaticProblem needleRev = mpgArithmaticProblem( needle.SecndDigit(), needle.FirstDigit(), needle.GetProblemType() );

	for ( unsigned int i = startPos; i < haystack.size(); i++ )
	{
		if ( haystack[i] == needle || haystack[i] == needleRev )
			return true;
	}

	return false;
}

void mpgGenerationAlgorithm::clearProblemStore( void )
{
	for ( unsigned int i = 0; i < problems->size(); i++ )
		delete (*problems)[ i ];
	
	problems->clear();
}
