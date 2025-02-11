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
 |  FILENAME: mpgGenOptionsUI.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Wednesday, July 26, 2006 11:31:15 PM
 +--------------------------------------------------------
 */ 

#include "wx/wx.h"
#include "wx/gbsizer.h"
#include "wx/arrstr.h"
#include "wx/image.h"
#include "wx/mstream.h"
#include "wx/spinctrl.h"
#include "wx/tglbtn.h"

#include "mpgGenOptionsUI.h"
#include "MathPageGenUI.h"
#include "mpgConstants.h"

#include "genopts_png.h"

BEGIN_EVENT_TABLE( mpgGenOptionsUI, wxPanel )
	EVT_COMBOBOX( ID_Control_CmboProbType, mpgGenOptionsUI::OnProblemTypeSelected )
END_EVENT_TABLE()

mpgGenOptionsUI::mpgGenOptionsUI( wxWindow *parent, wxWindowID id ) : wxPanel( parent, id, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER )
{
	// Instantiate the options controls
	// Labels
	lblOptions = new wxStaticText( this, wxID_ANY, wxT( "Generation Options" ) );
	lblOptions->SetFont( wxFont( 14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

	lblProblemType = new wxStaticText( this, wxID_ANY, wxT( "Problem Type:" ) );
	lblProblemOrientation = new wxStaticText( this, wxID_ANY, wxT( "Problem Orientation:" ) );
	lblProblemComplexity = new wxStaticText( this, wxID_ANY, wxT( "Problem Complexity:" ) );

	lblProblemCount = new wxStaticText( this, wxID_ANY, wxT( "Number of Problems:" ) );
	lblPageCount = new wxStaticText( this, wxID_ANY, wxT( "Number of Pages:" ) );

	// Controls
	wxMemoryInputStream istream( genopts_png, sizeof genopts_png );
	wxBitmap genOptsImg( istream, wxBITMAP_TYPE_PNG );
	optionsImage = new wxStaticBitmap( this, wxID_ANY, genOptsImg );

	wxArrayString probTypes;
	probTypes.Add( wxT( "Addition" ) );
	probTypes.Add( wxT( "Subtraction" ) );
	probTypes.Add( wxT( "Multiplication" ) );
	probTypes.Add( wxT( "Algebra" ) );

	cmboProblemType = new wxComboBox( this, ID_Control_CmboProbType, wxT("Addition"), wxDefaultPosition, wxDefaultSize, probTypes, wxCB_READONLY | wxTAB_TRAVERSAL );

	wxArrayString probOrien;
	probOrien.Add( wxT( "Horizontal" ) );
	probOrien.Add( wxT( "Vertical (\"Stacked\")" ) );

	cmboProblemOrientation = new wxComboBox( this, ID_Control_CmboProbOrient, wxT("Horizontal"), wxDefaultPosition, wxDefaultSize, probOrien, wxCB_READONLY | wxTAB_TRAVERSAL );
	
	wxArrayString probCompl;
	probCompl.Add( wxT( "Simple" ) );
	probCompl.Add( wxT( "Average" ) );
	probCompl.Add( wxT( "Advanced" ) );

	cmboProblemComplexity = new wxComboBox( this, ID_Control_CmboProbComplex, wxT("Average"), wxDefaultPosition, wxDefaultSize, probCompl, wxCB_READONLY | wxTAB_TRAVERSAL );
	
	spnProblemCount = new wxSpinCtrl( this, ID_Control_SpnProbCount, wxEmptyString, wxDefaultPosition, wxSize( 60, 20 ), wxSP_ARROW_KEYS | wxTAB_TRAVERSAL, 1, 50, 50 );
	spnProblemCount->SetValue( 50 );
	spnPageCount = new wxSpinCtrl( this, ID_Control_SpnPageCount, wxEmptyString, wxDefaultPosition, wxSize( 60, 20 ), wxSP_ARROW_KEYS | wxTAB_TRAVERSAL, 1, 50, 1 );
	spnPageCount->SetValue( 1 );

	chkPositiveSolutions = new wxCheckBox( this, ID_Control_ChkPositiveSltn, wxT( "Allow &Negative Solutions" ), wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	chkPositiveSolutions->SetValue( false );
	chkPositiveSolutions->Disable();

	chkDisplaySolutions = new wxCheckBox( this, ID_Control_ChkDispSolutions, wxT( "&Display Solutions" ), wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	chkDisplaySolutions->SetValue( false );

	btnGenerate = new wxButton( this, ID_Control_BtnGenerate, wxT( "&Generate" ) );
	btnPrint = new wxButton( this, ID_Control_BtnPrint, wxT( "&Print" ) );

	// Create the layout sizer and add the controls
	gridbag = new wxGridBagSizer();

	wxFlexGridSizer *headerSizer = new wxFlexGridSizer( 2, 1 );
	headerSizer->Add( optionsImage, 0, wxALIGN_CENTER_VERTICAL );
	headerSizer->Add( lblOptions, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL );

	gridbag->Add( headerSizer, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ) );

	gridbag->Add( lblProblemType, wxGBPosition( 1, 0 ), wxDefaultSpan, wxALIGN_CENTER_VERTICAL | wxALL, 3 );
	gridbag->Add( cmboProblemType, wxGBPosition( 1, 1 ), wxDefaultSpan, wxALL | wxGROW, 3 );

	gridbag->Add( lblProblemOrientation, wxGBPosition( 2, 0 ), wxDefaultSpan, wxALIGN_CENTER_VERTICAL | wxALL, 3 );
	gridbag->Add( cmboProblemOrientation, wxGBPosition( 2, 1 ), wxDefaultSpan, wxALL | wxGROW, 3 );

	gridbag->Add( lblProblemComplexity, wxGBPosition( 3, 0 ), wxDefaultSpan, wxALIGN_CENTER_VERTICAL | wxALL, 3 );
	gridbag->Add( cmboProblemComplexity, wxGBPosition( 3, 1 ), wxDefaultSpan, wxALL | wxGROW, 3 );

	gridbag->Add( lblProblemCount, wxGBPosition( 4, 0 ), wxDefaultSpan, wxALIGN_CENTER_VERTICAL | wxALL, 3 );
	gridbag->Add( spnProblemCount, wxGBPosition( 4, 1 ), wxDefaultSpan, wxALL, 3 );

	gridbag->Add( lblPageCount, wxGBPosition( 5, 0 ), wxDefaultSpan, wxALIGN_CENTER_VERTICAL | wxALL, 3 );
	gridbag->Add( spnPageCount, wxGBPosition( 5, 1 ), wxDefaultSpan, wxALL, 3 );

	gridbag->Add( chkPositiveSolutions, wxGBPosition( 6, 0 ), wxGBSpan( 1, 2 ), wxLEFT | wxTOP, 10 );
	gridbag->Add( chkDisplaySolutions, wxGBPosition( 7, 0 ), wxGBSpan( 1, 2 ), wxLEFT | wxTOP, 10 );

	gridbag->Add( btnGenerate, wxGBPosition( 9, 0 ), wxGBSpan( 1, 2 ), wxALL | wxGROW, 6 );
	gridbag->Add( btnPrint, wxGBPosition( 10, 0 ), wxGBSpan( 1, 2 ), wxALL | wxGROW, 6 );

	gridbag->AddGrowableCol( 0 );
	gridbag->SetEmptyCellSize( wxSize( 10, 20 ) );

	gridbag->Fit( this );
	gridbag->SetSizeHints( this );

	SetSizer( gridbag );
}

mpgGenOptionsUI::~mpgGenOptionsUI( void )
{
	delete lblOptions;

	delete lblProblemType;
	delete cmboProblemType;
	delete lblProblemOrientation;
	delete cmboProblemOrientation;
	delete lblProblemComplexity;
	delete cmboProblemComplexity;
	
	delete lblProblemCount;
	delete spnProblemCount;
	delete lblPageCount;
	delete spnPageCount;

	delete chkPositiveSolutions;
	delete chkDisplaySolutions;

	delete btnGenerate;
	delete btnPrint;
}

void mpgGenOptionsUI::SetActionsEnabled( bool e )
{
	if ( e )
	{
		btnGenerate->Enable();
		btnPrint->Enable();
		chkDisplaySolutions->Enable();
	}
	else
	{
		btnGenerate->Disable();
		btnPrint->Disable();
		chkDisplaySolutions->Disable();
	}
}

void mpgGenOptionsUI::SetOutputEnabled( bool e )
{
	if ( e )
	{
		btnPrint->Enable();
	}
	else
	{
		btnPrint->Disable();
	}
}

void mpgGenOptionsUI::ExecDefaultGeneration( int probType )
{
	cmboProblemComplexity->SetValue( wxT( "Average" ) );
	cmboProblemOrientation->SetValue( wxT( "Horizontal" ) );
		
	chkPositiveSolutions->SetValue( false );

	switch ( probType )
	{
	case TYPE_ADDITION:
		cmboProblemType->SetValue( wxT( "Addition" ) );
		break;

	case TYPE_SUBTRACTION:
		cmboProblemType->SetValue( wxT( "Subtraction" ) );
		break;

	case TYPE_MULTIPLICATION:
		cmboProblemType->SetValue( wxT( "Multiplication" ) );
		break;

	case TYPE_ALGEBRA:
		cmboProblemType->SetValue( wxT( "Algebra" ) );
		break;

	default:
		cmboProblemType->SetValue( wxT( "Addition" ) );
		break;
	}

	spnProblemCount->SetRange( 1, 50 );	// Hack: forces the value to actually set...
	spnProblemCount->SetValue( 50 );
	spnPageCount->SetValue( 1 );

	// Simulate a button click for the Generate button and a combobox selected event
	// for the problem type combobox
	GetEventHandler()->AddPendingEvent( wxCommandEvent( wxEVT_COMMAND_COMBOBOX_SELECTED, ID_Control_CmboProbType ) );
	GetEventHandler()->AddPendingEvent( wxCommandEvent( wxEVT_COMMAND_BUTTON_CLICKED, ID_Control_BtnGenerate ) );
}

int mpgGenOptionsUI::GetProblemType( void ) const
{
	wxString value = cmboProblemType->GetValue();
	
	if ( value.Cmp( wxT( "Addition" ) ) == 0 )
		return TYPE_ADDITION;
	else if ( value.Cmp( wxT( "Subtraction" ) ) == 0 )
		return TYPE_SUBTRACTION;
	else if ( value.Cmp( wxT( "Multiplication" ) ) == 0 )
		return TYPE_MULTIPLICATION;
	else if ( value.Cmp( wxT( "Algebra" ) ) == 0 )
		return TYPE_ALGEBRA;

	return -1;
}

int mpgGenOptionsUI::GetProblemOrientation( void ) const
{
	if ( cmboProblemOrientation->GetValue().Cmp( wxT( "Horizontal" ) ) == 0 )
		return HORIZONTAL;
	else if ( cmboProblemOrientation->GetValue().Cmp( wxT( "Vertical (\"Stacked\")" ) ) == 0 )
		return VERTICAL;

	return -1;
}

int mpgGenOptionsUI::GetComplexity( void ) const
{
	if ( cmboProblemComplexity->GetValue().Cmp( wxT( "Simple" ) ) == 0 )
		return COMPLEXITY_SIMPLE;
	else if ( cmboProblemComplexity->GetValue().Cmp( wxT( "Average" ) ) == 0 )
		return COMPLEXITY_AVERAGE;
	else if ( cmboProblemComplexity->GetValue().Cmp( wxT( "Advanced" ) ) == 0 )
		return COMPLEXITY_ADVANCED;

	return -1;
}

int mpgGenOptionsUI::GetNumProblems( void ) const
{
	int temp = spnProblemCount->GetValue();
	return temp;
}

int mpgGenOptionsUI::GetNumPages( void ) const
{
	return spnPageCount->GetValue();
}

bool mpgGenOptionsUI::PositiveSolutions( void ) const
{
	return chkPositiveSolutions->IsChecked();
}

bool mpgGenOptionsUI::DisplaySolutions( void ) const
{
	return chkDisplaySolutions->IsChecked();
}

void mpgGenOptionsUI::OnProblemTypeSelected( wxCommandEvent &evt )
{
	if ( cmboProblemType->GetValue().Cmp( wxT("Subtraction") ) == 0 )
	{
		chkPositiveSolutions->Enable();
		cmboProblemOrientation->Enable();		

		spnProblemCount->SetRange( 1, 50 );
	}
	else if ( cmboProblemType->GetValue().Cmp( wxT("Algebra") ) == 0 )
	{
		chkPositiveSolutions->Enable();

		// Only horizontal orientation...
		cmboProblemOrientation->SetValue( wxT( "Horizontal" ) );
		cmboProblemOrientation->Disable();

		// Only 20 algebra problems per page...
		if ( spnProblemCount->GetValue() > 20 )
			spnProblemCount->SetValue( 20 );

		spnProblemCount->SetRange( 1, 20 );
	}
	else
	{
		chkPositiveSolutions->Disable();
		cmboProblemOrientation->Enable();
	
		spnProblemCount->SetRange( 1, 50 );
	}
}
