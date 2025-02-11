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
 |  FILENAME: mpgAboutDialog.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Wednesday, November 08, 2006 5:31:19 PM
 +--------------------------------------------------------
 */ 

#include "mpgAboutDialog.h"

#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "wx/gbsizer.h"
#include "wx/image.h"
#include "wx/mstream.h"

#include "license.h"
#include "genopts_png.h"

BEGIN_EVENT_TABLE( mpgAboutDialog, wxDialog )
	EVT_BUTTON( ID_Control_BtnClose, mpgAboutDialog::OnClose )
END_EVENT_TABLE()

mpgAboutDialog::mpgAboutDialog( wxWindow *parent, wxWindowID id ) : wxDialog( parent, id, wxT( "About Math Page Generator" ), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE ) 
{	
	// Instantiate the controls
	// Labels
	wxMemoryInputStream istream( genopts_png, sizeof genopts_png );
	wxBitmap icoImg( istream, wxBITMAP_TYPE_PNG );
	progIcon = new wxStaticBitmap( this, wxID_ANY, icoImg );

	lblTitle = new wxStaticText( this, wxID_ANY, wxT( "Math Page Generator" ), wxDefaultPosition, wxDefaultSize );
	lblTitle->SetFont( wxFont( 18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );
	lblVersion = new wxStaticText( this, wxID_ANY, wxT( "Version 2.0.0 for Windows" ), wxDefaultPosition, wxDefaultSize );
	lblVersion->SetFont( wxFont( 13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL ) );
	lblCopyright = new wxStaticText( this, wxID_ANY, wxT( "� 2006 Julia Anderson. Uses portions of the Tango icon theme." ), wxDefaultPosition, wxDefaultSize );
	lblFreeSoftware = new wxStaticText( this, wxID_ANY, wxT( "Math Page Generator is free software. The source code is licensed under the GNU GPL version 2:" ), wxDefaultPosition, wxDefaultSize );

	// Controls
	gplDisplay = new wxHtmlWindow( this, ID_Control_GplDisplay, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER );
	gplDisplay->SetPage( gpl );

	btnClose = new wxButton( this, ID_Control_BtnClose, wxT( "Close" ), wxDefaultPosition, wxDefaultSize );

	// Create the layout sizer and add the controls
	gridbag = new wxGridBagSizer();

	wxFlexGridSizer *headerSizer = new wxFlexGridSizer( 2, 3 );
	headerSizer->Add( progIcon, 0, wxALIGN_CENTER_VERTICAL );
	headerSizer->Add( lblTitle, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxLEFT, 12 );
	headerSizer->AddSpacer( 1 );
	headerSizer->Add( lblVersion, 0, wxLEFT, 14 );
	headerSizer->AddSpacer( 1 );
	headerSizer->Add( lblCopyright, 0, wxLEFT, 14 );

	gridbag->Add( headerSizer, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxLEFT | wxTOP, 8 );

	gridbag->Add( lblFreeSoftware, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxLEFT | wxRIGHT | wxBOTTOM, 4 );
	gridbag->Add( gplDisplay, wxGBPosition( 3, 0 ), wxGBSpan( 7, 2 ), wxGROW | wxLEFT | wxRIGHT, 4 );

	gridbag->Add( btnClose, wxGBPosition( 10, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT | wxALL, 5 );

	gridbag->AddGrowableCol( 0 );
	gridbag->SetEmptyCellSize( wxSize( 10, 20 ) );

	gridbag->Fit( this );
	gridbag->SetSizeHints( this );

	SetSizer( gridbag );
}

mpgAboutDialog::~mpgAboutDialog( void )
{
	delete progIcon;
	
	delete lblTitle;
	delete lblVersion;
	delete lblCopyright;
	delete lblFreeSoftware;

	delete gplDisplay;

	delete btnClose;
}

void mpgAboutDialog::Show( void )
{
	gplDisplay->Scroll( 0, 0 );
	ShowModal();
}

void mpgAboutDialog::OnClose( wxCommandEvent &WXUNUSED( evt ) )
{
	this->Close();
}
