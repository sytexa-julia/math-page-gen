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
 |  FILENAME: MathPageGenUI.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Wednesday, July 19, 2006 10:50:55 PM
 +--------------------------------------------------------
 */ 

#include "MathPageGenUI.h"

#include <deque>
#include <string>
#include <sstream>

#include "wx/wx.h"
#include "wx/file.h"
#include "wx/dir.h"
#include "wx/wxhtml.h"
#include "wx/fs_mem.h"
#include "wx/image.h"
#include "wx/mstream.h"
#include "wx/html/htmprint.h"
#include "wx/html/helpctrl.h"
#include "wx/protocol/http.h"
#include "wxUtilities.h"

#include "mpgAboutDialog.h"
#include "mpgMenuBar.h"
#include "mpgStatusBar.h"
#include "mpgGenOptionsUI.h"
#include "mpgAdditionProbGen.h"
#include "mpgSubtractionProbGen.h"
#include "mpgMultiplicationProbGen.h"
#include "mpgAlgebraProbGen.h"
#include "mpgHtmlGenerator.h"
#include "mpgArithmaticProblem.h"
#include "mpgConstants.h"

#include "resource.h"
#include "arrow_png.h"

using std::deque;
using std::string;
using std::stringstream;

/* ====================================================================
 * ==== EVENT TABLE DECLARATION =====================================*/

BEGIN_EVENT_TABLE( MathPageGenUI, wxFrame )
	EVT_MENU( ID_MenuItem_NewMathPage, MathPageGenUI::OnNewMathPage )
	EVT_MENU( ID_MenuItem_Save, MathPageGenUI::OnSave )
	EVT_MENU( ID_MenuItem_PrintPrev, MathPageGenUI::OnPrintPreview )
	EVT_MENU( ID_MenuItem_Print, MathPageGenUI::OnPrint )
    EVT_MENU( ID_MenuItem_Exit, MathPageGenUI::OnQuit )

	EVT_MENU( ID_MenuItem_ShowGenMenu, MathPageGenUI::OnToggleGenMenu )

	EVT_MENU( ID_MenuItem_CreateAddit, MathPageGenUI::OnCreateAddition )
	EVT_MENU( ID_MenuItem_CreateSubtr, MathPageGenUI::OnCreateSubtraction )
	EVT_MENU( ID_MenuItem_CreateMulti, MathPageGenUI::OnCreateMultiplication )
	EVT_MENU( ID_MenuItem_CreateAlgeb, MathPageGenUI::OnCreateAlgebra )

	EVT_MENU( ID_MenuItem_Help, MathPageGenUI::OnHelp )
	EVT_MENU( ID_MenuItem_CheckUpdate, MathPageGenUI::OnCheckUpdate )
    EVT_MENU( ID_MenuItem_About, MathPageGenUI::OnAbout )

	EVT_BUTTON( ID_Control_BtnGenerate, MathPageGenUI::RenderNewPreview )
	EVT_BUTTON( ID_Control_BtnPrint, MathPageGenUI::OnPrint )
	EVT_CHECKBOX( ID_Control_ChkDispSolutions, MathPageGenUI::ToggleAnswerDisplay )
END_EVENT_TABLE()

/* ====================================================================
 * ==== CONSTRUCTOR / DESTRUCTOR ====================================*/

MathPageGenUI::MathPageGenUI(const wxString& title, 
       const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size, wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	// Initiallize the generation algorithms
	algorithms = new vector< mpgGenerationAlgorithm * >( ALGORITHM_COUNT );
	(*algorithms)[ TYPE_ADDITION ] = new mpgAdditionProbGen( 50, COMPLEXITY_AVERAGE );
	(*algorithms)[ TYPE_SUBTRACTION ] = new mpgSubtractionProbGen( 50, COMPLEXITY_AVERAGE );
	(*algorithms)[ TYPE_MULTIPLICATION ] = new mpgMultiplicationProbGen( 50, COMPLEXITY_AVERAGE );
	(*algorithms)[ TYPE_ALGEBRA ] = new mpgAlgebraProbGen( 50, COMPLEXITY_AVERAGE );

	// Initiallize the HTML buffer
	htmlGen = new mpgHtmlGenerator;
	htmlBuffer = new string;
	saveBuffer = new wxString;
	printBuffer = new wxString;

	// Create and set the menu bar
	menuBar = new mpgMenuBar;
    SetMenuBar( menuBar );

	// Create and add the status bar
	progStatBar = new mpgStatusBar( this, 15 );
	SetStatusBar( progStatBar );

	(*algorithms)[ TYPE_ADDITION ]->SetStatusBar( progStatBar );
	(*algorithms)[ TYPE_SUBTRACTION ]->SetStatusBar( progStatBar );
	(*algorithms)[ TYPE_MULTIPLICATION ]->SetStatusBar( progStatBar );
	(*algorithms)[ TYPE_ALGEBRA ]->SetStatusBar( progStatBar );

	// Set the frame icon from the resource file
	wxIcon appIco = wxIcon( wxICON( APPICON ) );

	if ( appIco.Ok() )
		SetIcon( appIco );

	// Initiallize the main UI
	splitter = new wxSplitterWindow( this, ID_Control_Splitter, wxPoint(0, 0), wxDefaultSize, wxSP_3D | wxSP_LIVE_UPDATE );
	
	previewPane = new wxHtmlWindow( splitter, ID_Control_Preview, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER );
	previewPane->SetMinSize( wxSize(590, 0) );
	
	optionsPane = new mpgGenOptionsUI( splitter, ID_Control_Options );

	splitter->SplitVertically( previewPane, optionsPane );

	// Set up the about dialog
	aboutDialog = new mpgAboutDialog( this );

	// Set up the file save dialog
	saveDialog = new wxFileDialog( this, wxT( "Save as HTML" ), wxT( "." ), wxT( "Math_Page_1.html" ), wxT( "HTML files (*.html)|*.html" ), wxSAVE | wxOVERWRITE_PROMPT ) ;
	UpdateSaveNumber();

	// Set up the print dialog
	stringstream formId;
	formId << "<p align='left'>( Page <b>@PAGENUM@</b> of <b>@PAGESCNT@</b> )</p> <p align='right'>Form " << wxDateTime::GetCurrentMonth() << wxDateTime::Now().GetDay() << wxDateTime::GetCurrentYear() << "</p>";
	
	printDialog = new wxHtmlEasyPrinting( wxT( "Print" ), this );
	printDialog->SetHeader( wxT( "<p align='right'>Name:_________________________________</p><br>" ), wxPAGE_ALL );
	printDialog->SetFooter( wxUtilities::string2wxString( formId.str() ), wxPAGE_ALL );

	printDialog->GetPageSetupData()->SetMarginTopLeft( wxPoint( 20, 10 ) );
	printDialog->GetPageSetupData()->SetMarginBottomRight( wxPoint( 20, 10 ) );
	printDialog->GetPageSetupData()->SetPaperId( wxPAPER_LETTER );

	// Help dialog
	helpDialog = new wxHtmlHelpController;
	helpDialog->AddBook( wxFileName( wxT( "MathPageGen2.htb" ) ) );

	// Load the get started preview
	wxFileSystem myfs;
 	if ( myfs.OpenFile( wxT( "memory:arrow.png" ) ) != NULL )
  		wxMemoryFSHandler::RemoveFile( wxT( "arrow.png" ) );

	wxMemoryInputStream istream( arrow_png, sizeof arrow_png );
	wxImage image( istream, wxBITMAP_TYPE_PNG );
	wxMemoryFSHandler::AddFile( wxT( "arrow.png" ), image, wxBITMAP_TYPE_PNG );
	
	previewPane->SetPage( wxT( "<br><br><br><br><br><br><br><br><br><br><br><br><br><br><p align='right'><img src='memory:arrow.png' width='370' height='70' border='0'></p>" ) );
    
	optionsPane->SetOutputEnabled( false );
	menuBar->SetOutputEnabled( false );
	menuBar->SetToggleGenOptionsEnabled( false );
	pageSet = false;
}

MathPageGenUI::~MathPageGenUI( void )
{
	delete previewPane;
	delete optionsPane;

	delete splitter;
	delete progStatBar;

	delete aboutDialog;
	delete saveDialog;
	delete printDialog;
	delete helpDialog;

	delete htmlGen;
	delete htmlBuffer;
	delete saveBuffer;
	delete printBuffer;

	// Delete the mpgGenerationAlgorithm instances, then the vector itself
	for ( unsigned int i = 0; i < algorithms->size(); i++ )
		delete (*algorithms)[i];

	delete algorithms;
}

void MathPageGenUI::RenderNewPreview( wxCommandEvent &WXUNUSED( event ) )
{
	// Disable generation controls
	this->SetCursor( wxCursor( wxCURSOR_WAIT ) );
	menuBar->SetActionsEnabled( false );
	optionsPane->SetActionsEnabled( false );
	
	int probType = optionsPane->GetProblemType();
	(*algorithms)[ probType ]->SetProblemCount( optionsPane->GetNumProblems() );
	(*algorithms)[ probType ]->SetComplexity( optionsPane->GetComplexity() );
	(*algorithms)[ probType ]->SetPageCount( optionsPane->GetNumPages() );
	(*algorithms)[ probType ]->SetProblemCount( optionsPane->GetNumProblems() );
	(*algorithms)[ probType ]->SetAllowNegative( optionsPane->PositiveSolutions() );

	deque<mpgMathProblem *> temp = (*algorithms)[ probType ]->generate();

	progStatBar->UpdateStatus( wxT( "Rendering preview..." ), 100 );

	htmlBuffer->clear();
	*htmlBuffer = htmlGen->render( optionsPane->GetProblemOrientation(), temp, optionsPane->DisplaySolutions(), optionsPane->GetNumProblems() );
	*saveBuffer = wxUtilities::string2wxString( htmlGen->previewToOutput( htmlBuffer ) );
	*printBuffer = wxUtilities::string2wxString( htmlGen->previewToPrintable( htmlBuffer ) );

	previewPane->SetPage( wxUtilities::string2wxString( *htmlBuffer ) );

	// Give the program 2/5 second to catch up
	wxMilliSleep( 400 );

	progStatBar->UpdateStatus( wxT( "Ready." ) );

	// Re-enable generation controls
	pageSet = true;

	menuBar->SetActionsEnabled( true );
	menuBar->SetToggleGenOptionsEnabled( true );
	optionsPane->SetActionsEnabled( true );
	this->SetCursor( wxCursor( wxCURSOR_ARROW ) );
}

void MathPageGenUI::ToggleAnswerDisplay( wxCommandEvent &event )
{
	if ( !pageSet )
        return;
    
    int totProbs = optionsPane->GetNumProblems() * optionsPane->GetNumPages();
	
	// Disable generation controls
	if ( totProbs >= 250 )
	{
		progStatBar->UpdateStatus( wxT( "Rendering preview (with solutions)..." ) );

		this->SetCursor( wxCursor( wxCURSOR_WAIT ) );
		menuBar->SetActionsEnabled( false );
		optionsPane->SetActionsEnabled( false );
	}
	
	htmlGen->revealSolutions( htmlBuffer, event.IsChecked() );
	previewPane->SetPage( wxUtilities::string2wxString( *htmlBuffer ) );

	// Also, refresh the other buffers
	*saveBuffer = wxUtilities::string2wxString( htmlGen->previewToOutput( htmlBuffer ) );
	*printBuffer = wxUtilities::string2wxString( htmlGen->previewToPrintable( htmlBuffer ) );

	if ( event.IsChecked() )
		printDialog->SetHeader( wxT( "<p align='right'><u>Solution Guide</u></p>" ), wxPAGE_ALL );
	else
		printDialog->SetHeader( wxT( "<p align='right'>Name:<u>_________________________________</u></p><br>" ), wxPAGE_ALL );

	// Re-enable generation controls
	if ( totProbs >= 250 )
	{
		progStatBar->UpdateStatus( wxT( "Ready." ) );
		
		menuBar->SetActionsEnabled( true );
		optionsPane->SetActionsEnabled( true );
		this->SetCursor( wxCursor( wxCURSOR_ARROW ) );
	}
}

/* ====================================================================
 * ==== EVENT HANDLERS ==============================================*/

void MathPageGenUI::OnNewMathPage( wxCommandEvent &WXUNUSED( event ) )
{
	previewPane->SetPage( wxT( "<br><br><br><br><br><br><br><br><br><br><br><br><br><br><p align='right'><img src='memory:arrow.png' width='370' height='70' border='0'></p>" ) );
	SetDisplayOptionsVisible( true );
    
	optionsPane->SetOutputEnabled( false );
	menuBar->SetOutputEnabled( false );
	menuBar->SetToggleGenOptionsEnabled( false );
	pageSet = false;
}

void MathPageGenUI::OnSave( wxCommandEvent &WXUNUSED( event ) )
{
	if ( !pageSet )
        return;
	
	// Disable generation controls
	menuBar->SetActionsEnabled( false );
	optionsPane->SetActionsEnabled( false );

	*saveBuffer = wxUtilities::string2wxString( htmlGen->previewToOutput( htmlBuffer ) );
	
	if ( saveDialog->ShowModal() == wxID_OK )
	{
		wxString fileChosen = saveDialog->GetPath();
		wxFile theFile;

		if ( !wxFile::Exists( fileChosen.c_str() ) || wxFile::Access( fileChosen.c_str(), wxFile::write ) )
		{
			theFile.Open( fileChosen.c_str(), wxFile::write );
			theFile.Create( fileChosen.wx_str(), true );
			theFile.Write( *saveBuffer );

			UpdateSaveNumber();
		}
		else
		{
			wxMessageBox( wxT( "Saving of file failed. Please check that the destination drive or file is not read-only." ), wxT( "Math Page Generator" ), wxOK | wxICON_ERROR, this );
		}
	}

	// Re-enable generation controls
	menuBar->SetActionsEnabled( true );
	optionsPane->SetActionsEnabled( true );
}

void MathPageGenUI::OnPrint( wxCommandEvent &WXUNUSED( event ) )
{
	if ( !pageSet )
        return;
	
	stringstream formId;
	formId << "<p align='left'>( Page <b>@PAGENUM@</b> of <b>@PAGESCNT@</b> )</p> <p align='right'>Form " << wxDateTime::GetCurrentMonth() << wxDateTime::Now().GetDay() << wxDateTime::GetCurrentYear() << "</p>";
	printDialog->SetFooter( wxUtilities::string2wxString( formId.str() ), wxPAGE_ALL );

	printDialog->PrintText( *printBuffer );
}

void MathPageGenUI::OnPrintPreview( wxCommandEvent &WXUNUSED( event ) )
{
	if ( !pageSet )
        return;
	
	stringstream formId;
	formId << "<p align='left'>( Page <b>@PAGENUM@</b> of <b>@PAGESCNT@</b> )</p> <p align='right'>Form " << wxDateTime::GetCurrentMonth() << wxDateTime::Now().GetDay() << wxDateTime::GetCurrentYear() << "</p>";
	printDialog->SetFooter( wxUtilities::string2wxString( formId.str() ), wxPAGE_ALL );

	printDialog->PreviewText( *printBuffer );
}
 
void MathPageGenUI::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close( true );
}

void MathPageGenUI::OnToggleGenMenu( wxCommandEvent& WXUNUSED(event) )
{
	if ( splitter->IsSplit() )
		SetDisplayOptionsVisible( false );
	else
		SetDisplayOptionsVisible( true );
}

// ====================

void MathPageGenUI::OnCreateAddition( wxCommandEvent& WXUNUSED(event) )
{
	optionsPane->ExecDefaultGeneration( TYPE_ADDITION );
	previewPane->SetFocus();
}

void MathPageGenUI::OnCreateSubtraction( wxCommandEvent& WXUNUSED(event) )
{
	optionsPane->ExecDefaultGeneration( TYPE_SUBTRACTION );
	previewPane->SetFocus();
}

void MathPageGenUI::OnCreateMultiplication( wxCommandEvent& WXUNUSED(event) )
{
	optionsPane->ExecDefaultGeneration( TYPE_MULTIPLICATION );
	previewPane->SetFocus();
}

void MathPageGenUI::OnCreateAlgebra( wxCommandEvent& WXUNUSED(event) )
{
	optionsPane->ExecDefaultGeneration( TYPE_ALGEBRA );
	previewPane->SetFocus();
}

// ====================

void MathPageGenUI::OnHelp( wxCommandEvent &WXUNUSED( event ) )
{
	if ( !helpDialog->DisplayContents() )
	{
		wxMessageBox( wxT( "There was an error loading the help file." ), wxT( "Math Page Generator" ), wxICON_ERROR );
	}

	helpDialog->SetFrameParameters( wxT( "Help: %s" ), wxSize( 780, 580 ) );
}

void MathPageGenUI::OnCheckUpdate( wxCommandEvent &WXUNUSED( event ) )
{
    // Disable generation controls
	this->SetCursor( wxCursor( wxCURSOR_WAIT ) );
	menuBar->SetActionsEnabled( false );
	optionsPane->SetActionsEnabled( false );
	progStatBar->SetStatusText( wxT( "Checking for updates, please wait..." ) );

	// Initiallize connection
	wxHTTP http; 
	char buffer[ 1024 ];

    wxString url = wxT( "sytexa.com" );

    http.SetHeader( wxT( "Accept" ), wxT( "text/*" ) ); 
    http.SetHeader( wxT( "User-Agent" ), wxT( "MathPageGen2" ) ); 

	// Try to connect
    if ( http.Connect( url ) ) 
    { 
		// Try to read data
		wxInputStream *stream = http.GetInputStream( wxT( "/Services/UpdateCheck.aspx?app=mathpagegen2" ) ); 
		wxProtocolError err = http.GetError(); 

		// If no error occurred, read the data
		if ( err == wxPROTO_NOERR ) 
		{ 
			stream->Read( &buffer, 1024 );
			string data( buffer );
			
			// Get the latest version, and compare to the version of this instance
			string::size_type pos = data.find( "<span id=\"lblLatestVersion\">" );
			string::size_type end = data.find( "</span>", pos );

			if ( pos != string::npos && end != string::npos )
			{
				string latestVer = data.substr( pos + 28, end - ( pos + 28 ) );
				
				if ( APP_VERSION < latestVer )
				{
					// New version available...
					int goDownloadNow = wxMessageBox( wxT( "A newer version of Math Page Generator is available. Would you like to visit the download website now?" ), wxT( "Math Page Generator" ), wxYES_NO, this );

					if ( goDownloadNow == wxYES )
						wxLaunchDefaultBrowser( wxT( "http://sytexa.com/Services/Redirect.aspx?act=dl&dlid=101" ) );
				}
				else if ( APP_VERSION == latestVer )
				{
					// This instance is up to date
					wxMessageBox( wxT( "You are running the latest version of Math Page Generator." ), wxT( "Math Page Generator" ) );
				}
			}
		}
    }
	else
	{
		wxMessageBox( wxT( "The was an error connecting to the update service. The service may be\noffline, or you may not be connected to the Internet." ), wxT( "Math Page Generator" ), wxICON_ERROR );
	}

	// Re-enable generation controls
	menuBar->SetActionsEnabled( true );
	optionsPane->SetActionsEnabled( true );
	this->SetCursor( wxCursor( wxCURSOR_ARROW ) );
	progStatBar->SetStatusText( wxT( "Ready." ) );
}

void MathPageGenUI::OnAbout( wxCommandEvent &WXUNUSED( event ) )
{
    aboutDialog->Show();
}

/* ====================================================================
 * ==== OTHER FUNCTIONS =============================================*/

long MathPageGenUI::UpdateSaveNumber( void )
{
	wxDir dir;
	dir.Open( saveDialog->GetDirectory() );

	wxString fname;
	bool o = dir.GetFirst( &fname );
	long bTemp, biggest = 1;

	while ( o )
	{
		if ( fname.substr( 0, 10 ) == wxT( "Math_Page_" ) )
		{
			fname = fname.Mid( 10, fname.Length() - fname.find( wxT( ".html" ) ) - 4 );
			fname.ToLong( &bTemp );

			if ( bTemp >= biggest ) 
				biggest = bTemp + 1;
		}

		o = dir.GetNext( &fname );
	}

	stringstream fTemp;
	fTemp << "Math_Page_" << biggest << ".html";
	saveDialog->SetFilename( wxUtilities::string2wxString( fTemp.str() ) );

	return biggest;
}

void MathPageGenUI::SetDisplayOptionsVisible( bool disp )
{
	if ( disp )
	{
		previewPane->SetMinSize( wxSize(590, 0) );
		previewPane->Show( true );
		optionsPane->Show( true );
		splitter->SplitVertically( previewPane, optionsPane );
	}
	else
	{
		splitter->Unsplit();
	}
}
