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
 |  FILENAME: mpgFraction.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Saturday, November 18, 2006 5:06:24 PM
 +--------------------------------------------------------
 */

#ifndef __MPG_FRACTION_H
#define __MPG_FRACTION_H

#include <string>

using std::string;

class mpgFraction
{
private:
	int numerator;
	int denominator;
	bool negative;

public:
	mpgFraction( void );
	mpgFraction( int numer, int denom = 1 );

	mpgFraction operator+( const mpgFraction &other );
	mpgFraction operator-( const mpgFraction &other );
	mpgFraction operator*( const mpgFraction &other );
	mpgFraction operator/( const mpgFraction &other );

	mpgFraction operator+( const int &other );
	mpgFraction operator-( const int &other );
	mpgFraction operator*( const int &other );
	mpgFraction operator/( const int &other );

	mpgFraction operator+=( const mpgFraction &other );
	mpgFraction operator-=( const mpgFraction &other );

	void Reduce( void );

	void SetNegative( bool neg );
	bool GetNegative( void ) const;
	void SetNumerator( int numer );
	void SetDenominator( int denom );
	int GetNumerator( void ) const;
	int GetDenominator( void ) const;
	double GetDecimal( void ) const;

	string ToString( bool parentheses = false ) const;
	string GetDecimalStr( void ) const;
};

#endif
