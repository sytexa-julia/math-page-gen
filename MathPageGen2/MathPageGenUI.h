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
 |  FILENAME: MathPageGenUI.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Wednesday, July 19, 2006 10:50:33 PM
 +--------------------------------------------------------
 */ 

#ifndef __MPG_UI_H
#define __MPG_UI_H

#include <string>
#include <vector>

#include "wx/wx.h"
#include "wx/splitter.h"
#include "wx/wxhtml.h"
#include "wx/html/htmprint.h"
#include "wx/html/helpctrl.h"

#include "mpgAboutDialog.h"
#include "mpgMenuBar.h"
#include "mpgStatusBar.h"
#include "mpgGenerationAlgorithm.h"
#include "mpgHtmlGenerator.h"
#include "mpgGenOptionsUI.h"

using std::string;
using std::vector;

#define ALGORITHM_COUNT 4

class MathPageGenUI : public wxFrame
{
private:
	// Algorithms and tools
	vector< mpgGenerationAlgorithm * > *algorithms;
	mpgHtmlGenerator *htmlGen;

	// HTML buffer
	string *htmlBuffer;
	wxString *saveBuffer;
	wxString *printBuffer;

	// Controls
	mpgMenuBar *menuBar;

	mpgStatusBar *progStatBar;
	wxSplitterWindow *splitter;

	wxHtmlWindow *previewPane;
	mpgGenOptionsUI *optionsPane;

	// Dialogs
	mpgAboutDialog *aboutDialog;
	wxFileDialog *saveDialog;
	wxHtmlEasyPrinting *printDialog;
	wxHtmlHelpController *helpDialog;

    // Other
    bool pageSet;

	// Helper methods
	void SetDisplayOptionsVisible( bool disp );
	long UpdateSaveNumber( void );

public:
    MathPageGenUI( const wxString& title, const wxPoint& pos, const wxSize& size );
	~MathPageGenUI( void );

	void RenderNewPreview( wxCommandEvent &WXUNUSED( event ) );
	void ToggleAnswerDisplay( wxCommandEvent &event );

	// 'File' menu event handlers
	void OnNewMathPage( wxCommandEvent &WXUNUSED( event ) );
	void OnSave( wxCommandEvent &WXUNUSED( event ) );
	void OnPrint( wxCommandEvent &WXUNUSED( event ) );
	void OnPrintPreview( wxCommandEvent &WXUNUSED( event ) );
    void OnQuit( wxCommandEvent &WXUNUSED( event ) );

	// 'View' menu event handlers
	void OnToggleGenMenu( wxCommandEvent &WXUNUSED( event ) );

	// 'Action' menu event handlers
	void OnCreateAddition( wxCommandEvent &WXUNUSED( event ) );
	void OnCreateSubtraction( wxCommandEvent &WXUNUSED( event ) );
	void OnCreateMultiplication( wxCommandEvent &WXUNUSED( event ) );
	void OnCreateAlgebra( wxCommandEvent &WXUNUSED( event ) );

	// 'Help' menu event handlers
	void OnHelp( wxCommandEvent &WXUNUSED( event ) );
	void OnCheckUpdate( wxCommandEvent &WXUNUSED( event ) );
    void OnAbout( wxCommandEvent &WXUNUSED( event ) );

	DECLARE_EVENT_TABLE()
};

enum
{
	ID_Control_Splitter = 100,
	ID_Control_Preview,
	ID_Control_Options
};

#endif
