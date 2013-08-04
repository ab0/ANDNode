//---------------------------------------------------------------------------
#pragma hdrstop

//###########################################################################
#include "aMenuControl.h"

#include "aASN.h"
#include "aDialogo.h"
#include "_01_Principal.h"
//###########################################################################

#pragma package(smart_init)
//---------------------------------------------------------------------------


//private ###################################################################
//---------------------------------------------------------------------------
//Eventos
void __fastcall aMenuControl::OnAplicarEstilo( TObject *val )
{
/**/
	bAsociar = ( TButton *)this->FindStyleResource( "bAsociar" );

	if ( bAsociar )
		bAsociar->OnClick = bAsociarOnClick;
}
//---------------------------------------------------------------------------

void __fastcall aMenuControl::bAsociarOnClick( TObject *val )
{
/**/
	SHELLEXECUTEINFO shex;

	ZeroMemory( &shex, sizeof( shex ) );

	shex.cbSize       = sizeof( SHELLEXECUTEINFO );
	shex.fMask        = 0                         ;
	shex.lpVerb       = L"runas"                  ;
	shex.lpFile       = ParamStr( 0 ).w_str()     ;
	shex.lpParameters = L"[AsociarExtensiones]"   ;
	shex.nShow        = SW_HIDE                   ;

	ShellExecuteEx( &shex );
}
//---------------------------------------------------------------------------
//###########################################################################


//public ####################################################################
//---------------------------------------------------------------------------
//Creacion
__fastcall aMenuControl::aMenuControl( TComponent *Owner ) : TPanel( Owner )
{
/**/
//public:
	//Punteros
	bAsociar = NULL;

//Inicio
	this->OnApplyStyleLookup = OnAplicarEstilo;
}
//---------------------------------------------------------------------------
//###########################################################################
