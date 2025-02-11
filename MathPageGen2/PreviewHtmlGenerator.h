/*
 +--------------------------------------------------------
 |  Math Page Generator
 |  FILENAME: PreviewHtmlGenerator.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Tuesday, October 10, 2006 8:49:22 PM
 +--------------------------------------------------------
 */ 

#ifndef __PREVIEW_HTML_GENERATOR_H
#define __PREVIEW_HTML_GENERATOR_H

#include "MathProblem.h"
#include <string>
#include <deque>

using std::string;
using std::deque;

class PreviewHtmlGenerator
{
private:
	static string createVerticalProblem( const MathProblem &prob );
	static int countDigits( const int input );

public:
	static string generateHorizontal( deque<MathProblem> probs, bool solutions );
	static string generateVertical( deque<MathProblem> probs, bool solutions );
};

#endif
