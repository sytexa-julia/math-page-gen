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
 |  FILENAME: mpgStatusBar.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Wednesday, July 19, 2006 10:59:24 PM
 +--------------------------------------------------------
 */ 

#include "mpgStatusBar.h"
#include "wx/wx.h"

BEGIN_EVENT_TABLE( mpgStatusBar, wxStatusBar )
	EVT_SIZE( mpgStatusBar::OnSize )
END_EVENT_TABLE()

mpgStatusBar::mpgStatusBar( wxWindow *parent, int max ) : wxStatusBar( parent, wxID_ANY, 0 )
{
	wxSize size = GetSize();
	progressBar = new wxGauge( this, ID_ProgressBar, max, 
								wxPoint(size.x - 147, (size.y - 13) / 2), wxSize(125, 13) );
	progressBar->SetRange( 100 );
	
	SetFieldsCount( 1 );
	SetStatusText( wxT("Ready.") );
}

mpgStatusBar::~mpgStatusBar( void )
{ }

void mpgStatusBar::OnSize( wxSizeEvent & event )
{
	wxSize size = GetSize();
	wxSize progSize = progressBar->GetSize();

	progressBar->Move(size.x - progSize.x - 2, (size.y - progSize.y + 3) / 2);
}

void mpgStatusBar::UpdateStatus( const wxString &msg, int percent )
{
	if ( this->GetStatusText() != msg )
		this->SetStatusText( msg );
	this->UpdateProgress( percent );
}

void mpgStatusBar::UpdateProgress( int value )
{
	if ( value >= 0 && value <= progressBar->GetRange() )
	{
		progressBar->SetValue( value );
	}
}

void mpgStatusBar::ResetProgress( void )
{
	progressBar->SetValue( 0 );
}

void mpgStatusBar::SetMaximum( int max )
{
	progressBar->SetRange( max );
}

int mpgStatusBar::GetMaximum( void )
{
	return progressBar->GetRange();
}
