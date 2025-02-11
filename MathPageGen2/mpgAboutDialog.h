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
 |  FILENAME: mpgAboutDialog.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Wednesday, November 08, 2006 5:30:50 PM
 +--------------------------------------------------------
 */ 

#ifndef __MPG_ABOUT_DIALOG_H
#define __MPG_ABOUT_DIALOG_H

#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "wx/gbsizer.h"

class mpgAboutDialog :
	protected wxDialog
{
private:
	wxGridBagSizer *gridbag;

	wxStaticBitmap *progIcon;

	wxStaticText *lblTitle;
	wxStaticText *lblVersion;
	wxStaticText *lblCopyright;
	wxStaticText *lblFreeSoftware;

	wxHtmlWindow *gplDisplay;

	wxButton *btnClose;

public:
	mpgAboutDialog( wxWindow *parent, wxWindowID id = wxID_ANY );
	~mpgAboutDialog( void );

	void Show( void );

	void OnClose( wxCommandEvent &WXUNUSED( evt ) );

	DECLARE_EVENT_TABLE()
};

enum AboutControls
{
	ID_Control_GplDisplay = 1,
	ID_Control_BtnClose
};

#endif
