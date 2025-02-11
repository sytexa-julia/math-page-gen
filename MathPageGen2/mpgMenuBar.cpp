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
 |  FILENAME: mpgMenuBar.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Wednesday, July 26, 2006 11:04:52 PM
 +--------------------------------------------------------
 */ 

#include "mpgMenuBar.h"

mpgMenuBar::mpgMenuBar( void ) : wxMenuBar()
{
	// Create menus
	menuFile = new wxMenu;
	menuView = new wxMenu;
	menuActions = new wxMenu;
	menuHelp = new wxMenu;

	// Add 'File' menu items
    menuFile->Append( ID_MenuItem_NewMathPage, wxT("New Math Page\tCtrl-N"), wxT("Clear the preview area and prepare to create a new practice page.") );
    menuFile->Append( ID_MenuItem_Save, wxT("Save as HTML\tCtrl-S"), wxT("Saves the currently displayed math page in HTML format.") );
	menuFile->AppendSeparator();
	menuFile->Append( ID_MenuItem_PrintPrev, wxT("Print Preview"), wxT("Preview the print layout of the page(s) currently displayed in the preview area.") );
	menuFile->Append( ID_MenuItem_Print, wxT("Print\tCtrl-P"), wxT("Print the page(s) currently displayed in the preview area.") );
	menuFile->AppendSeparator();
    menuFile->Append( ID_MenuItem_Exit, wxT("Exit"), wxT("Exit the Math Page Generator application.") );

	// Add 'View' menu items
	wxMenuItem *showGenMenu = new wxMenuItem( menuView, ID_MenuItem_ShowGenMenu, wxT("Display Generation Menu\tCtrl-D"), wxT("Display the math page generation options menu."), wxITEM_CHECK );
	menuView->Append(showGenMenu);
	showGenMenu->Check( true );

	// Add 'Actions' menu items
	menuActions->Append( ID_MenuItem_CreateAddit, wxT("Create Addition Page\tAlt-A"), wxT("Generate an addition practice page with default configuration.") );
	menuActions->Append( ID_MenuItem_CreateSubtr, wxT("Create Subtraction Page\tAlt-S"), wxT("Generate a subtraction practice page with default configuration.") );
	menuActions->Append( ID_MenuItem_CreateMulti, wxT("Create Multiplication Page\tAlt-M"), wxT("Generate a multiplication practice page with default configuration.") );
	menuActions->Append( ID_MenuItem_CreateAlgeb, wxT("Create Algebra Page\tAlt-X"), wxT("Generate an algebra practice page with default configuration.") );

	// Add 'Help' menu items
	menuHelp->Append( ID_MenuItem_Help, wxT("Math Page Generator Help...\tF1"), wxT("View the Math Page Generator help files.") );
	menuHelp->Append( ID_MenuItem_CheckUpdate, wxT("Check for Updates"), wxT("Check online to see if a newer version is available.") );
	menuHelp->AppendSeparator();
	menuHelp->Append( ID_MenuItem_About, wxT("About...\tCtrl-A"), wxT("Learn more about Math Page Generator.") );
 
	// Add menus to menu bar
	Append( menuFile, wxT("&File") );
	Append( menuView, wxT("&View") );
	Append( menuActions, wxT("&Action") );
	Append( menuHelp, wxT("&Help") );
}

void mpgMenuBar::SetActionsEnabled( bool e )
{
	menuFile->Enable( ID_MenuItem_NewMathPage, e );
	menuFile->Enable( ID_MenuItem_Save, e );
	menuFile->Enable( ID_MenuItem_PrintPrev, e );
	menuFile->Enable( ID_MenuItem_Print, e );
	
	menuActions->Enable( ID_MenuItem_CreateAddit, e );
	menuActions->Enable( ID_MenuItem_CreateSubtr, e );
	menuActions->Enable( ID_MenuItem_CreateMulti, e );
	menuActions->Enable( ID_MenuItem_CreateAlgeb, e );
}

void mpgMenuBar::SetOutputEnabled( bool e )
{
	menuFile->Enable( ID_MenuItem_Save, e );
	menuFile->Enable( ID_MenuItem_PrintPrev, e );
	menuFile->Enable( ID_MenuItem_Print, e );
}

void mpgMenuBar::SetToggleGenOptionsEnabled( bool e )
{
	menuView->Enable( ID_MenuItem_ShowGenMenu, e );
}
