/*
 +--------------------------------------------------------
 |  Math Page Generator
 |  FILENAME: PreviewHtmlGenerator.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Tuesday, October 10, 2006 9:00:06 PM
 +--------------------------------------------------------
 */ 

#include "PreviewHtmlGenerator.h"
#include <sstream>
#include <deque>

using std::stringstream;
using std::deque;

string PreviewHtmlGenerator::generateHorizontal( deque<MathProblem> probs, bool solutions )
{
	stringstream working;
	working << "<html><head></head><body><font face='Courier New, Courier, monospace'><div align='center'><table border='0' cellspacing='0' cellpadding='4' width='70%'>";
	
	deque<MathProblem>::iterator it = probs.begin();

	while ( it != probs.end() )
	{
		// First column
		working << "<tr><td width='65%' align='left'>" << it->GetProblem() << " = ";
		if ( solutions )
			working << it->GetSolution();
		working << "</td>";
		it++;

		// Uneven number of problems. . .
		if ( it == probs.end() )
		{
			working << "<td></td></tr>";
			break;
		}

		// Second column, if applicable
		working << "<td width='35%' align='left'>" << it->GetProblem() << " = ";
		if ( solutions )
			working << it->GetSolution();
		working << "</td></tr>";
		it++;
	}

	working << "</table></div></font></body></html>";

	return working.str();
}

string PreviewHtmlGenerator::generateVertical( deque<MathProblem> probs, bool solutions )
{
	stringstream working;
	working << "<html><head></head><body><font face='Courier New, Courier, monospace'><table border='0' cellspacing='0' cellpadding='4' width='95%' align='center'>";
	
	deque<MathProblem>::iterator it = probs.begin();
	bool quitFlag = false;

	while ( it != probs.end() )
	{
		working << "<tr>";

		for ( int i = 0; i < 7; i++ )
		{
			working << "<td width='14%' align='right'>" << createVerticalProblem( *it );
			if ( solutions )
				working << "<br>&nbsp;&nbsp;" << it->GetSolution();
			working << "</td></tr>";
			it++;

			// Uneven number of problems. . .
			if ( it == probs.end() )
			{
				for ( int j = 0; j < 7 - i; j++ )
					working << "<td></td>";

				quitFlag = true;
				break ;
			}
		}

		working << "</tr><tr><td><br><br></td></tr>";

		if ( quitFlag )
			break;
	}

	working << "</table></font></body></html>";

	return working.str();
}

string PreviewHtmlGenerator::createVerticalProblem( const MathProblem &prob )
{
	int size1 = countDigits( prob.FirstDigit() );
	int size2 = countDigits( prob.SecndDigit() );
	int diff;

	stringstream problem;

	if ( size1 > size2 )
	{
		diff = size1 - size2;

		problem << prob.FirstDigit() << "<br><u>" << prob.GetOperatorSymbol();
		for ( int i = 0; i < diff; i++)
			problem << "&nbsp;";
		problem << prob.SecndDigit() << "</u>";
	}
	else
	{
		diff = size2 - size1;

		problem << prob.SecndDigit() << "<br><u>" << prob.GetOperatorSymbol();
		for ( int i = 0; i < diff; i++)
			problem << "&nbsp;";
		problem << prob.FirstDigit() << "</u>";
	}

	return problem.str();
}

int PreviewHtmlGenerator::countDigits( const int input )
{
	if ( input == 0 )
		return 1;
	
	int cnt = 0;
	int temp = input;

	while ( temp > 0 )
	{
		temp /= 10;
		cnt++;
	}

	return cnt;
}