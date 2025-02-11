/*
 +--------------------------------------------------------
 |  Math Page Generator
 |  FILENAME: mpgImageIcon.h
 |  VERSION:  2.0.0
 |  ========================================

 |  (C) 2004-2007 Julia Anderson
 |  http://sytexa.com
 |  ========================================
 |  Time: Tuesday, August 01, 2006 6:36:54 PM
 +--------------------------------------------------------
 */

#include "mpgImageIcon.h"
#include "wx/wx.h"
#include "wx/image.h"

BEGIN_EVENT_TABLE( mpgImageIcon, wxPanel )
	EVT_PAINT( mpgImageIcon::OnPaint )
END_EVENT_TABLE()

mpgImageIcon::mpgImageIcon( mpgImageIcon &other ) : wxPanel( other.GetParent(), wxID_ANY, other.GetPosition(), other.GetSize(), other.GetWindowStyle(), other.GetName() ), borderWidth( 2 )
{
	SetImage( other.GetImage() );
	SetBorder( 1 );
}

mpgImageIcon::mpgImageIcon( wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name ), borderWidth( 2 )
{
	SetBorder( 1 );
}

mpgImageIcon::mpgImageIcon( const wxString& imgPath, wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name ), borderWidth( 2 )
{
	SetImage( imgPath );
	SetBorder( 1 );
}

mpgImageIcon::mpgImageIcon( wxImage *image, wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name ), borderWidth( 2 )
{
	SetImage( image );
	SetBorder( 1 );
}

mpgImageIcon::~mpgImageIcon( void )
{
	delete renderer;
	delete base;
}

void mpgImageIcon::OnPaint( wxPaintEvent &event )
{
	wxPaintDC dc( this );
	PrepareDC( dc );

	// TODO: Add support for drawing animated image files
	if ( renderer && renderer->Ok() )
		dc.DrawBitmap( *renderer, renderXPos, renderYPos, false );
}

void mpgImageIcon::SetBorder( int border )
{
	if ( border >= 0 )
	{
		this->borderWidth = border;
		this->SetSize( wxSize( GetImage()->GetWidth() + border, GetImage()->GetHeight() + border ) );

		renderXPos = (int) ( ( GetSize().GetWidth() - GetImage()->GetWidth() ) / 2);
		renderYPos = (int) ( ( GetSize().GetHeight() - GetImage()->GetHeight() ) / 2 );
	}
}

int mpgImageIcon::GetBorder( void )
{
	return this->borderWidth;
}

const wxImage* mpgImageIcon::GetImage( void )
{
	return this->base;
}

void mpgImageIcon::SetImage( const wxImage *img )
{
	this->base = new wxImage( img );

	if ( base->Ok() )
		this->renderer = new wxBitmap( base );
}

void mpgImageIcon::SetImage( const wxString &path )
{
	this->base = new wxImage( path, GetTypeFromExtention( path ) );

	if ( base->Ok() )
		this->renderer = new wxBitmap( base );
}

long mpgImageIcon::GetTypeFromExtention( const wxString &fileName )
{
	wxString ext = fileName.Mid( fileName.Find('.', true) + 1 );
	long imgType = wxBITMAP_TYPE_ANY;

	if ( ext.Cmp(wxT("bmp")) == 0 )
		imgType = wxBITMAP_TYPE_BMP;
	else if ( ext.Cmp(wxT("png")) == 0 )
		imgType = wxBITMAP_TYPE_PNG;
	else if ( ext.Cmp(wxT("jpg")) == 0 || ext.Cmp(wxT("jpeg")) == 0 )
		imgType = wxBITMAP_TYPE_JPEG;
	else if ( ext.Cmp(wxT("gif")) == 0 )
		imgType = wxBITMAP_TYPE_GIF;
	else if ( ext.Cmp(wxT("pcx")) == 0 )
		imgType = wxBITMAP_TYPE_PCX;
	else if ( ext.Cmp(wxT("pnm")) == 0 )
		imgType = wxBITMAP_TYPE_PNM;
	else if ( ext.Cmp(wxT("tiff")) == 0 || ext.Cmp(wxT("tif")) == 0 )
		imgType = wxBITMAP_TYPE_TIF;
	else if ( ext.Cmp(wxT("xpm")) == 0 )
		imgType = wxBITMAP_TYPE_XPM;
	else if ( ext.Cmp(wxT("ico")) == 0 )
		imgType = wxBITMAP_TYPE_ICO;
	else if ( ext.Cmp(wxT("cur")) == 0 )
		imgType = wxBITMAP_TYPE_CUR;
	else if ( ext.Cmp(wxT("ani")) == 0 )
		imgType = wxBITMAP_TYPE_ANI;

	return imgType;
}
