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
 |  FILENAME: mpgSubtractionProbGen.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Saturday, October 21, 2006 8:22:41 PM
 +--------------------------------------------------------
 */

#ifndef __MPG_SUBTRACTION_PROB_GEN_H
#define __MPG_SUBTRACTION_PROB_GEN_H

#include <deque>

#include "mpgGenerationAlgorithm.h"
#include "mpgMathProblem.h"
#include "mpgArithmaticProblem.h"

using std::deque;

class mpgSubtractionProbGen :
	public mpgGenerationAlgorithm
{
private:
	bool SubtractionTooEasy( int numA, int numB );

public:
	mpgSubtractionProbGen( void );
	mpgSubtractionProbGen( int prblmCnt, int cmplxty );

	deque<mpgMathProblem *> generate( void );
};

#endif
