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
 |  FILENAME: mpgHtmlGenerator.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Tuesday, October 10, 2006 9:00:06 PM
 +--------------------------------------------------------
 */ 

#include <algorithm>
#include <sstream>
#include <string>
#include <deque>

#include "mpgHtmlGenerator.h"
#include "mpgMathProblem.h"
#include "mpgArithmaticProblem.h"
#include "mpgAlgebraProblem.h"
#include "mpgConstants.h"

using std::string;
using std::stringstream;
using std::deque;

mpgHtmlGenerator::mpgHtmlGenerator( void ) : orientation( HORIZONTAL )
{
	htmlBuffer = new string;
	smallFontProbTypes.push_back( TYPE_ALGEBRA );
}

mpgHtmlGenerator::mpgHtmlGenerator( int o ) : orientation( o )
{
	htmlBuffer = new string;
	smallFontProbTypes.push_back( TYPE_ALGEBRA );
}

mpgHtmlGenerator::~mpgHtmlGenerator( void )
{
	delete htmlBuffer;
}

string mpgHtmlGenerator::render( int orientation, deque<mpgMathProblem *> probs, bool solutions, const int probsPerPage )
{
	switch ( orientation )
	{
	case HORIZONTAL:
		return renderHorizontal( probs, solutions, probsPerPage );
		break;

	case VERTICAL:
		return renderVertical( probs, solutions, probsPerPage );
		break;

	default:
		return "";
		break;
	}
}

string mpgHtmlGenerator::renderHorizontal( deque<mpgMathProblem *> probs, bool solutions, const int probsPerPage )
{
	if ( probs[ 0 ]->GetProblemType() == TYPE_ALGEBRA )
		return generateAlgebraDisplay( probs, solutions, probsPerPage );
	
	stringstream working;
	string size = "size='+1'";

	if ( UseSmallFont( probs[ 0 ]->GetProblemType() ) )
		size = "";

	if ( solutions )
		working << "<cmnt>sol</cmnt>";
	else
		working << "<cmnt>clr</cmnt>";

	working << "<html><head></head><body><font face='Courier New, Courier, monospace' " << size <<"><div align='center'><cmnt>addbr</cmnt><cmnt>addbr</cmnt><table border='0' cellspacing='0' cellpadding='4' width='70%'>";
	
	deque<mpgMathProblem *>::iterator it = probs.begin();
	int probCnt = 0;

	while ( it != probs.end() )
	{
		// First column
		working << "<tr><td width='60%' align='left'>" << ( *it )->GetProblem() << " = ";
		if ( solutions )
			working << "<cmnt>ans</cmnt><b><i>" << ( *it )->GetSolution() << "</i></b><cmnt>/ans</cmnt>";
		else
			working << "<cmnt><b><i>" << ( *it )->GetSolution() << "</i></b></cmnt>";
		working << "<cmnt>addbr</cmnt></td>";
		it++;
		probCnt++;

		// Start a new page (uneven number of problems)?
		if ( it != probs.end() && probCnt == probsPerPage )
		{
			probCnt = 0;
			working << "<td></td></tr></table><hr><cmnt>addbr</cmnt><cmnt>addbr</cmnt><cmnt>addbr</cmnt><table border='0' cellspacing='0' cellpadding='6' width='70%'>";
			continue;
		}

		// Uneven number of problems. . .
		if ( it == probs.end() )
		{
			working << "<td></td></tr>";
			break;
		}

		// Second column, if applicable
		working << "<td width='40%' align='left'>" << ( *it )->GetProblem() << " = ";
		if ( solutions )
			working << "<cmnt>ans</cmnt><b><i>" << ( *it )->GetSolution() << "</i></b><cmnt>/ans</cmnt>";
		else
			working << "<cmnt><i><b>" << ( *it )->GetSolution() << "</i></b></cmnt>";
		working << "<cmnt>addbr</cmnt></td></tr>";
		it++;
		probCnt++;

		// Start a new page (even number of problems)?
		if ( it != probs.end() && probCnt == probsPerPage )
		{
			probCnt = 0;
			working << "</table><hr><table border='0' cellspacing='0' cellpadding='4' width='70%'>";
		}
	}

	working << "</table></div></font></body></html>";

	return working.str();
}

string mpgHtmlGenerator::renderVertical( deque<mpgMathProblem *> probs, bool solutions, const int probsPerPage )
{
	stringstream working;
	string size = "size='+1'";

	if ( UseSmallFont( probs[ 0 ]->GetProblemType() ) )
		size = "";

	if ( solutions )
		working << "<cmnt>sol</cmnt>";
	else
		working << "<cmnt>clr</cmnt>";

	working << "<html><head></head><body><font face='Courier New, Courier, monospace' " << size << "><cmnt>addbr</cmnt><cmnt>addbr</cmnt><table border='0' cellspacing='0' cellpadding='4' width='95%' align='center'>";
	
	deque<mpgMathProblem *>::iterator it = probs.begin();
	bool quitFlag = false, breakFlag = false;
	int probCnt = 0;

	while ( it != probs.end() )
	{
		working << "<tr>";

		for ( int i = 0; i < 7; i++ )
		{
			working << "<td width='14%' align='right'>" << createVerticalProblem( *it );
			if ( solutions )
				working << "<cmnt>ans</cmnt><br>&nbsp;&nbsp;<b><i>" << ( *it )->GetSolution() << "</i></b><cmnt>/ans</cmnt>";
			else
				working << "<cmnt><br>&nbsp;&nbsp;<b><i>" << ( *it )->GetSolution() << "</i></b></cmnt>";
			working << "</td>";
			it++;
			probCnt++;

			// Start a new page (uneven number of problems)?
			if ( it != probs.end() && probCnt == probsPerPage )
			{
				probCnt = 0;

				// Finish the row
				for ( int j = 0; j < 7 - i; j++ )
					working << "<td></td>";

				working << "</tr></table><hr><cmnt>addbr</cmnt><cmnt>addbr</cmnt><cmnt>addbr</cmnt><table border='0' cellspacing='0' cellpadding='4' width='95%' align='center'>";
				breakFlag = true;
				break;
			}

			// Uneven number of problems. . .
			if ( it == probs.end() )
			{
				// Finish the row
				for ( int j = 0; j < 7 - (i + 1); j++ )
					working << "<td></td>";

				quitFlag = true;
				break ;
			}
		}

		// No need to write a blank row
		if ( breakFlag )
		{
			breakFlag = false;
			continue;
		}

		// Start a new page (even number of problems)?
		if ( it != probs.end() && probCnt == probsPerPage )
		{
			probCnt = 0;
			working << "</tr></table><hr><table border='0' cellspacing='0' cellpadding='4' width='95%' align='center'>";
		}
		else if ( quitFlag )
		{
			working << "</tr>";
			break;
		}
		else
		{
			working << "</tr><tr><td><br><br></td></tr>";
		}
	}

	working << "</table></font></body></html>";

	return working.str();
}

/*
 * Converts HTML generated for preview to HTML suitable for 
 * saving; that is, one practice page per printed page.
 */
string mpgHtmlGenerator::previewToOutput( const string * const htmlBuffer ) const
{
	string working = string( *htmlBuffer );

	// Remove the solution status comment
	working.erase( 0, 16 );

	// Adjust font size
	string::size_type temp = working.find( "size='+1'", 0 );
	working.replace( temp + 6, 2, "-1" );
	
	// Remove all other comments
	string::size_type pos = working.find( "<cmnt>", 0 );
	string::size_type end = working.find( "</cmnt>", 0 );

	while ( pos != string::npos && end != string::npos )
	{
		working.erase( pos, (end + 7) - pos );	// Remove everything between the comment tags

		pos = working.find( "<cmnt>", 0 );
		end = working.find( "</cmnt>", 0 );
	}

	// Convert <hr> tags into page breaks. The hidden dash is a workaround to an IE7 bug with empty div tags.
	pos = working.find( "<hr>", 0 );
	
	while ( pos != string::npos )
	{
		working.erase( pos, 4 );
		working.insert( pos, "<br><br><div style='page-break-after:always'><span style='visibility: hidden'>-</span></div>" );

		pos = working.find( "<hr>", 0 );
	}

	return working;
}

/*
 * Converts HTML generated for preview to HTML suitable for 
 * printing; that is, one practice page per printed page.
 */
string mpgHtmlGenerator::previewToPrintable( const string * const htmlBuffer ) const
{
	string working = string( *htmlBuffer );

	// Remove the solution status comment
	working.erase( 0, 16 );

	// Add extra spacing
	string::size_type pos = working.find( "<cmnt>addbr</cmnt>", 0 );

	while ( pos != string::npos )
	{
		working.insert( pos, "<br>"  );	// Add <br> before tag
		working.erase( pos + 4, 18 );	// Remove the addbr notifier 

		pos = working.find( "<cmnt>addbr</cmnt>", pos );
	}
	// Remove all other comments
	pos = working.find( "<cmnt>", 0 );
	string::size_type end = working.find( "</cmnt>", 0 );

	while ( pos != string::npos && end != string::npos )
	{
		working.erase( pos, (end + 7) - pos );	// Remove everything between the comment tags

		pos = working.find( "<cmnt>", 0 );
		end = working.find( "</cmnt>", 0 );
	}

	// Convert <hr> tags into page breaks.
	pos = working.find( "<hr>", 0 );
	
	while ( pos != string::npos )
	{
		working.erase( pos, 4 );
		working.insert( pos, "<div style='page-break-before:always'></div>" );

		pos = working.find( "<hr>", 0 );
	}

	return working;
}

/*
 * Reveals or hides the solutions for the input HTML, if possible.
 * NOTE: Modifies the input.
 */
void mpgHtmlGenerator::revealSolutions( string *html, bool solutions ) const
{
	// Sanity checks
	if ( html->substr( 0, 16 ) == "<cmnt>sol</cmnt>" && solutions )
		return;
	
	if ( html->substr( 0, 16 ) == "<cmnt>clr</cmnt>" && !solutions )
		return;

	string::size_type pos = html->find( "<cmnt>", 16 );
	string::size_type end = html->find( "</cmnt>", 16 );

	if ( solutions )
	{
		html->replace( 6, 3, "sol" );
		
		// Reveal the solutions, but make sure they can be found again	
		while ( pos != string::npos && end != string::npos )
		{
			if ( html->substr( pos + 6, 5 ).compare( "addbr" ) == 0 )
			{
				pos = html->find( "<cmnt>", end + 7 );	  // Find the next start and end comment tag pair
				end = html->find( "</cmnt>", end + 7 );
				
				continue;	// Skip the non-answer related comment
			}
			
			html->insert( pos + 6, "ans</cmnt>" );	  // Insert an answer locater start tag
			html->insert( end + 10, "<cmnt>/ans" );   // Insert an answer locater end tag

			pos = html->find( "<cmnt>", end + 27 );	  // Find the next start and end comment tag pair
			end = html->find( "</cmnt>", end + 27 );
		}
	}
	else
	{
		html->replace( 6, 3, "clr" );
		
		pos = html->find( "<cmnt>ans</cmnt>", 16 );

		// Hide the solutions	
		while ( pos != string::npos && end != string::npos )
		{
			html->erase( pos + 6, 10 );					   // Remove 'ans</cmnt>
			pos = html->find( "<cmnt>/ans</cmnt>", pos );  // Find the end tag to the end of the answer locater
			html->erase( pos, 10 );						   // Remove '<cmnt>/ans'

			pos = html->find( "<cmnt>ans</cmnt>", pos );  // Find the next start comment tag
		}
	}
}

string mpgHtmlGenerator::createVerticalProblem( mpgMathProblem *prob )
{
	stringstream problem;

	const string *terms = prob->GetTermArray();

	if ( prob->GetProblemType() != TYPE_ALGEBRA )
	{
		// Handle as an arithmatic problem, which is easier

		size_t size1 = terms[ 0 ].length();
		size_t size2 = terms[ 1 ].length();
		size_t diff;
		
		if ( size1 > size2 )
		{
			diff = size1 - size2;

			problem << terms[ 0 ] << "<br><u>" << prob->GetOperatorSymbol();
			for ( unsigned int i = 0; i < diff; i++)
				problem << "&nbsp;";
			problem << terms[ 1 ] << "</u>";
		}
		else
		{
			diff = size2 - size1;

			if ( diff != 0 )
				diff -= 1;

			problem << terms[ 0 ] << "<br><u>" << prob->GetOperatorSymbol();
			for ( unsigned int i = 0; i < diff; i++)
				problem << "&nbsp;";
			problem << terms[ 1 ] << "</u>";
		}
	}
	else
	{
		// Handle as an algebra problem
	}

	return problem.str();
}

/*
 * There are enough differences that algebra problems warrant a
 * unique generation method. The chief difference is in the way
 * solutions are displayed, but there are also changes in spacing.
 */
string mpgHtmlGenerator::generateAlgebraDisplay( deque<mpgMathProblem *> probs, bool solutions, const int probsPerPage )
{
	stringstream working;
	string size = "size='+1'";

	if ( UseSmallFont( probs[ 0 ]->GetProblemType() ) )
		size = "";

	if ( solutions )
		working << "<cmnt>sol</cmnt>";
	else
		working << "<cmnt>clr</cmnt>";

	working << "<html><head></head><body><font face='Courier New, Courier, monospace' " << size << "><div align='center'><cmnt>addbr</cmnt><cmnt>addbr</cmnt><cmnt>addbr</cmnt><table border='0' cellspacing='0' cellpadding='4' width='90%'>";
	
	deque<mpgMathProblem *>::iterator it = probs.begin();
	int probCnt = 0;
	mpgAlgebraProblem *algProb;


	while ( it != probs.end() )
	{
		algProb = dynamic_cast< mpgAlgebraProblem * > ( *it );
		
		// First column
		working << "<tr><td width='55%' align='left'>" << algProb->GetProblem() << "<br><br>";

		if ( solutions )
			working << "<cmnt>ans</cmnt><b><i>" << algProb->GetVariable() << " = " << algProb->GetSolution() << "</i></b><cmnt>/ans</cmnt><br>";
		else
			working << "<cmnt><b><i>" << algProb->GetVariable() << " = " << algProb->GetSolution() << "</i></b></cmnt><br>";
		
		working << "<cmnt>addbr</cmnt></td>";
		it++;
		probCnt++;

		// Start a new page (uneven number of problems)?
		if ( it != probs.end() && probCnt == probsPerPage )
		{
			probCnt = 0;
			working << "<td></td></tr></table><hr><table border='0' cellspacing='0' cellpadding='6' width='95%'>";
			continue;
		}

		// Uneven number of problems. . .
		if ( it == probs.end() )
		{
			working << "<td></td></tr>";
			break;
		}

		// Second column, if applicable
		algProb = dynamic_cast< mpgAlgebraProblem * > ( *it );

		working << "<td width='45%' align='left'>" << algProb->GetProblem() << "<br><br>";

		if ( solutions )
			working << "<cmnt>ans</cmnt><b><i>" << algProb->GetVariable() << " = " << algProb->GetSolution() << "</i></b><cmnt>/ans</cmnt><br>";
		else
			working << "<cmnt><b><i>" << algProb->GetVariable() << " = " << algProb->GetSolution() << "</i></b></cmnt><br>";
		
		working << "<cmnt>addbr</cmnt></td></tr>";
		it++;
		probCnt++;

		// Start a new page (even number of problems)?
		if ( it != probs.end() && probCnt == probsPerPage )
		{
			probCnt = 0;
			working << "</table><hr><table border='0' cellspacing='0' cellpadding='4' width='95%'>";
		}
	}

	working << "</table></div></font></body></html>";

	return working.str();
}

int mpgHtmlGenerator::countDigits( const int input )
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

bool mpgHtmlGenerator::UseSmallFont( int probType )
{
	for ( unsigned int i = 0; i < smallFontProbTypes.size(); i++ )
		if ( smallFontProbTypes[ i ] == probType )
			return true;

	return false;
}
