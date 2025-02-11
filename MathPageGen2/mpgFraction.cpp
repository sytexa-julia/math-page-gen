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
 |  FILENAME: mpgFraction.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Saturday, November 18, 2006 5:06:18 PM
 +--------------------------------------------------------
 */

#include "mpgFraction.h"

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

mpgFraction::mpgFraction( void ) : numerator( 1 ), denominator( 1 )
{ }

mpgFraction::mpgFraction( int numer, int denom ) : numerator( numer ), denominator( denom )
{ }

mpgFraction mpgFraction::operator+( const mpgFraction &other )
{
	mpgFraction op1( this->numerator * other.denominator, this->denominator * other.denominator );
	mpgFraction op2( other.numerator * this->denominator, other.denominator * this->numerator );
	mpgFraction frac( op1.numerator + op2.numerator, op1.denominator );
	frac.Reduce();
	return frac;
}

mpgFraction mpgFraction::operator-( const mpgFraction &other )
{
	mpgFraction op1( this->numerator * other.denominator, this->denominator * other.denominator );
	mpgFraction op2( other.numerator * this->denominator, other.denominator * this->numerator );
	mpgFraction frac( op1.numerator - op2.numerator, op1.denominator );
	frac.Reduce();
	return frac;
}

mpgFraction mpgFraction::operator*( const mpgFraction &other )
{
	mpgFraction frac( this->numerator * other.numerator, this->denominator * other.denominator );
	frac.Reduce();
	return frac;
}

mpgFraction mpgFraction::operator/( const mpgFraction &other )
{
	mpgFraction frac( this->numerator * other.denominator, this->denominator * other.numerator );
	frac.Reduce();
	return frac;
}

mpgFraction mpgFraction::operator+( const int &other )
{
	mpgFraction op1( other * this->denominator, this->denominator );
	mpgFraction frac( op1.numerator + this->numerator, op1.denominator );
	frac.Reduce();
	return frac;
}

mpgFraction mpgFraction::operator-( const int &other )
{
	mpgFraction op1( other * this->denominator, this->denominator );
	mpgFraction frac( op1.numerator - this->numerator, op1.denominator );
	frac.Reduce();
	return frac;
}

mpgFraction mpgFraction::operator*( const int &other )
{
	mpgFraction frac( this->numerator * other, this->denominator );
	frac.Reduce();
	return frac;
}

mpgFraction mpgFraction::operator/( const int &other )
{
	mpgFraction frac( this->numerator, this->denominator * other );
	frac.Reduce();
	return frac;
}

mpgFraction mpgFraction::operator+=( const mpgFraction &other )
{
	return this->operator+( other );
}

mpgFraction mpgFraction::operator-=( const mpgFraction &other )
{
	return this->operator-( other );
}

void mpgFraction::Reduce( void )
{
	// Nothing yet...
}

void mpgFraction::SetNegative( bool neg )
{
	this->negative = neg;

	if ( neg && GetDecimal() > 0 )
	{
		SetNumerator( -1 * GetNumerator() );
	}
	else if ( !neg && GetDecimal() < 0 )
	{
		if ( GetNumerator() < 0 )
			SetNumerator( -1 * GetNumerator() );
		else
			SetDenominator( -1 * GetDenominator() );
	}
}

bool mpgFraction::GetNegative( void ) const
{
	return this->negative;
}

void mpgFraction::SetNumerator( int numer )
{
	if ( numer < 0 )
		SetNegative( true );
	else
		SetNegative( false );
	
	this->numerator = numer;
}

int mpgFraction::GetNumerator( void ) const
{
	return this->numerator;
}

void mpgFraction::SetDenominator( int denom )
{
	if ( denom < 0 )
		SetNegative( true );
	else
		SetNegative( false );
	
	this->denominator = denom;
}

int mpgFraction::GetDenominator( void ) const
{
	return this->denominator;
}

double mpgFraction::GetDecimal( void ) const
{
	if ( denominator == 0 )
		return 0;
	
	return (double) numerator / denominator;
}

string mpgFraction::ToString( bool parentheses ) const
{
	stringstream frac;

	if ( this->denominator == 1 )
	{
		frac << numerator;
	}
	else if ( this->denominator == -1 )
	{
		frac << "-" << numerator;
	}
	else
	{
		if ( parentheses )
			frac << "(" << numerator << "/" << denominator << ")";
		else
			frac << numerator << "/" << denominator;
	}

	return frac.str();
}

string mpgFraction::GetDecimalStr( void ) const
{
	stringstream ans;
	ans << GetDecimal();
	return ans.str();
}
