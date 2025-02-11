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
 |  Time: Sunday, November 05, 2006 3:32:15 PM
 +--------------------------------------------------------
 */ 

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation
#endif

#include "wx/wxprec.h"


#include "wx/defs.h"
#if wxUSE_HTML && wxUSE_STREAMS

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WXPRECOMP
#endif

#include "wx/html/forcelnk.h"
#include "wx/html/m_templ.h"

FORCE_LINK_ME( m_comment )


TAG_HANDLER_BEGIN( CMNT, "CMNT" )
    TAG_HANDLER_CONSTR( CMNT ) { }

    TAG_HANDLER_PROC( WXUNUSED( tag ) )
    {
        // Ignored. Used as a workaround to bugs in wxHtml's
		// comment handling.
        return true;
    }

TAG_HANDLER_END( CMNT )


TAGS_MODULE_BEGIN( CmntTag )

    TAGS_MODULE_ADD( CMNT )

TAGS_MODULE_END( CmntTag )

#endif
