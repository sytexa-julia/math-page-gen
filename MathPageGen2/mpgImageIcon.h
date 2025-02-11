/*
 +--------------------------------------------------------
 |  Math Page Generator
 |  FILENAME: mpgImageIcon.cpp
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Tuesday, August 01, 2006 6:37:05 PM
 +--------------------------------------------------------
 */ 

#ifndef MPG_IMAGE_ICON__H
#define MPG_IMAGE_ICON__H

#include "wx/wx.h"
#include "wx/string.h"

class mpgImageIcon : public wxPanel
{
private:
	wxImage *base;
	wxBitmap *renderer;

	int borderWidth;
	int renderXPos;
	int renderYPos;

	DECLARE_EVENT_TABLE()
public:
	mpgImageIcon( mpgImageIcon &other );
	mpgImageIcon( wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT( "imgicon" ) );
	mpgImageIcon( const wxString &imgPath, wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT( "imgicon" ) );
	mpgImageIcon( wxImage *image, wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT( "imgicon" ) );
	~mpgImageIcon( void );

	void SetBorder( int border );
	int GetBorder( void );

	const wxImage* GetImage( void );
	void SetImage( const wxImage *img );
	void SetImage( const wxString &path );

	void OnPaint( wxPaintEvent &event );

protected:
	long GetTypeFromExtention( const wxString &fileName );
};

#endif
