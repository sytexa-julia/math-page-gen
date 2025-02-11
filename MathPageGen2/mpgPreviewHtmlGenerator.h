/*
 +--------------------------------------------------------
 |  Math Page Generator
 |  FILENAME: mpgPreviewHtmlGenerator.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Tuesday, October 10, 2006 8:49:22 PM
 +--------------------------------------------------------
 */ 

#ifndef __MPG_PREVIEW_HTML_GENERATOR_H
#define __MPG_PREVIEW_HTML_GENERATOR_H

#include <string>
#include <deque>

#include "mpgMathProblem.h"
#include "mpgConstants.h"

using std::string;
using std::deque;

class mpgPreviewHtmlGenerator
{
private:
	static string createVerticalProblem( const mpgMathProblem &prob );
	static int countDigits( const int input );

public:
	static string render( int orientation, deque<mpgMathProblem> probs, bool solutions );
	static string renderHorizontal( deque<mpgMathProblem> probs, bool solutions );
	static string renderVertical( deque<mpgMathProblem> probs, bool solutions );
	
	static void SetOrientation( int orient );
};

#endif
