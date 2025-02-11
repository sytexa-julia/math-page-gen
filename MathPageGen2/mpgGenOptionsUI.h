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
 |  FILENAME: mpgGenOptionsUI.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Wednesday, July 26, 2006 11:31:15 PM
 +--------------------------------------------------------
 */ 

#ifndef MPG_GEN_OPTIONS__H
#define MPG_GEN_OPTIONS__H

#include "wx/wx.h"
#include "wx/gbsizer.h"
#include "wx/spinctrl.h"
#include "wx/tglbtn.h"

class mpgGenOptionsUI :
	public wxPanel
{
private:
	wxGridBagSizer *gridbag;

	wxStaticBitmap *optionsImage;
	wxStaticText *lblOptions;

	wxStaticText *lblProblemType;
	wxComboBox *cmboProblemType;
	wxStaticText *lblProblemOrientation;
	wxComboBox *cmboProblemOrientation;
	wxStaticText *lblProblemComplexity;
	wxComboBox *cmboProblemComplexity;
	
	wxStaticText *lblProblemCount;
	wxSpinCtrl *spnProblemCount;
	wxStaticText *lblPageCount;
	wxSpinCtrl *spnPageCount;

	wxCheckBox *chkPositiveSolutions;
	wxCheckBox *chkDisplaySolutions;

	wxButton *btnGenerate;
	wxButton *btnPrint;

public:
	mpgGenOptionsUI( wxWindow *parent, wxWindowID id = wxID_ANY );
	~mpgGenOptionsUI( void );

	void SetActionsEnabled( bool e );
	void SetOutputEnabled( bool e );
	void ExecDefaultGeneration( int probType );

	int GetProblemType( void ) const;
	int GetProblemOrientation( void ) const;
	int GetComplexity( void ) const;
	int GetNumProblems( void ) const;
	int GetNumPages( void ) const;

	bool PositiveSolutions( void ) const;

	bool DisplaySolutions( void ) const;

	void OnProblemTypeSelected( wxCommandEvent &WXUNUSED( evt ) );
	void OnGenerate( wxCommandEvent &WXUNUSED( evt ) );

	DECLARE_EVENT_TABLE()
};

enum mpgGenOptionsUIControls
{
	ID_Control_CmboProbType = 0,
	ID_Control_CmboProbOrient,
	ID_Control_CmboProbComplex,

	ID_Control_SpnProbCount,
	ID_Control_SpnVarCount,
	ID_Control_SpnPageCount,

	ID_Control_ChkPositiveSltn,
	ID_Control_ChkDispSolutions,

	ID_Control_BtnGenerate,
	ID_Control_BtnPrint
};

#endif
