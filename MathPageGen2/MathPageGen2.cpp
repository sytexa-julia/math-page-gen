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
 |  FILENAME: MathPageGen2.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Wednesday, July 19, 2006 10:51:17 PM
 +--------------------------------------------------------
 */ 

#include "wx/image.h"
#include "wx/fs_mem.h"
#include "wx/fs_zip.h"

#include "MathPageGen2.h"
#include "MathPageGenUI.h"

bool MathPageGen2::OnInit()
{
    // Extra wxWidgets setup
	wxImage::AddHandler( new wxPNGHandler() );
	wxFileSystem::AddHandler( new wxMemoryFSHandler() );
	wxFileSystem::AddHandler( new wxZipFSHandler() );
	
	// Create and show main window
	MathPageGenUI *ui = new MathPageGenUI( wxT( "Math Page Generator" ), wxPoint( 50, 50 ), wxSize( 835, 626 ) );
	ui->Centre();
    ui->Show( true );
    
	SetTopWindow( ui );

    return true;
} 