//---------------------------------------------------------------------------
#pragma hdrstop

//###########################################################################
#include "aMenuError.h"

#include "_01_Principal.h"
//###########################################################################

#pragma package(smart_init)
//---------------------------------------------------------------------------


//private ###################################################################
//---------------------------------------------------------------------------
//Eventos
void __fastcall aMenuError::OnAplicarEstilo( TObject *val )
{
/**/
	bVigilarError = ( TButton *)this->FindStyleResource( "bVigilarError" ); if ( bVigilarError ) bVigilarError->OnClick = bVigilarErrorOnClick;
}
//---------------------------------------------------------------------------

void __fastcall aMenuError::bVigilarErrorOnClick( TObject *val )
{
/**/
	if ( f1_prin->VError == NULL ) {
		f1_prin->VError = new aViguilarError( f1_prin );
		f1_prin->VError->ComenzarViguilancia();
	}
	else {
		f1_prin->VError->TerminarViguilancia();
		delete f1_prin->VError;
		f1_prin->VError = NULL;
    }
}
//---------------------------------------------------------------------------
//###########################################################################


//public ####################################################################
//---------------------------------------------------------------------------
//Creacion
__fastcall aMenuError::aMenuError( TComponent *Owner ) : TPanel( Owner )
{
/**/
//public:
	//Punteros
	bVigilarError = NULL;

//Inicio
	this->OnApplyStyleLookup = OnAplicarEstilo;
}
//---------------------------------------------------------------------------
//###########################################################################
