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
 |  FILENAME: mpgMenuBar.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Wednesday, July 26, 2006 11:04:52 PM
 +--------------------------------------------------------
 */ 

#ifndef MPG_MENU_BAR__H
#define MPG_MENU_BAR__H

#include "wx/wx.h"

class mpgMenuBar :
	public wxMenuBar
{
private:
	wxMenu *menuFile;
	wxMenu *menuView;
	wxMenu *menuActions;
	wxMenu *menuHelp;

public:
	mpgMenuBar( void );

	void SetActionsEnabled( bool e );
	void SetOutputEnabled( bool e );
	void SetToggleGenOptionsEnabled( bool e );
};

enum MenuItems
{
    ID_MenuItem_NewMathPage = 1,
	ID_MenuItem_Save,
	ID_MenuItem_PrintPrev,
	ID_MenuItem_Print,
	ID_MenuItem_Exit,

	ID_MenuItem_ShowGenMenu,
	ID_MenuItem_ShowAdvancedOpts,

	ID_MenuItem_CreateMulti,
	ID_MenuItem_CreateAddit,
	ID_MenuItem_CreateSubtr,
	ID_MenuItem_CreateAlgeb,
	ID_MenuItem_GenerateBatch,

	ID_MenuItem_Help,
	ID_MenuItem_CheckUpdate,
	ID_MenuItem_About
};

#endif
