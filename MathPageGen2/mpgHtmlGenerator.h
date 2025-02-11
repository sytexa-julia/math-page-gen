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
 |  FILENAME: mpgHtmlGenerator.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Tuesday, October 10, 2006 8:49:22 PM
 +--------------------------------------------------------
 */ 

#ifndef __MPG_HTML_GENERATOR_H
#define __MPG_HTML_GENERATOR_H

#include <string>
#include <deque>

#include "mpgMathProblem.h"
#include "mpgArithmaticProblem.h"
#include "mpgConstants.h"

using std::string;
using std::deque;

class mpgHtmlGenerator
{
private:
	int orientation;
	string *htmlBuffer;

	deque< int > smallFontProbTypes;

	string createVerticalProblem( mpgMathProblem *prob );
	string generateAlgebraDisplay( deque<mpgMathProblem *> probs, bool solutions, const int probsPerPage );
	int countDigits( const int input );

	bool UseSmallFont( int probType );

public:
	mpgHtmlGenerator( void );
	mpgHtmlGenerator( int o );
	~mpgHtmlGenerator( void );
	
	string render( int orientation, deque<mpgMathProblem *> probs, bool solutions, const int probsPerPage );
	string renderHorizontal( deque<mpgMathProblem *> probs, bool solutions, const int probsPerPage );
	string renderVertical( deque<mpgMathProblem *> probs, bool solutions, const int probsPerPage );
	
	string previewToOutput( const string * const html ) const;
	string previewToPrintable( const string * const html ) const;
	void revealSolutions( string *html, bool solutions = true ) const;
};

#endif
