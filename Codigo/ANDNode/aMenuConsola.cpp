//---------------------------------------------------------------------------
#pragma hdrstop

//###########################################################################
#include "aMenuConsola.h"

#include "aASN.h"
#include "aDialogo.h"
#include "_01_Principal.h"
//###########################################################################

#pragma package(smart_init)
//---------------------------------------------------------------------------


//private ###################################################################
//---------------------------------------------------------------------------
//Eventos
void __fastcall aMenuConsola::OnAplicarEstilo( TObject *val )
{
/**/
	bGuardar = ( TButton *)this->FindStyleResource( "bGuardar" ); if ( bGuardar ) bGuardar->OnClick = bGuardarOnClick;
	bLimpiar = ( TButton *)this->FindStyleResource( "bLimpiar" ); if ( bLimpiar ) bLimpiar->OnClick = bLimpiarOnClick;
}
//---------------------------------------------------------------------------

void __fastcall aMenuConsola::bGuardarOnClick( TObject *val )
{
/**/
	aDialogo *di        = new aDialogo( this );
	di->Filtro          = "[t1=*.txt][d1=Archivo de Texto Plano]";
	di->IndiceExtencion = 1;
	di->OpcionesDialogo = di->OpcionesDialogo << odSobrescribirArchivo;

	if ( di->EjecutarSA( GetActiveWindow() ) ) {
		if ( ExtractFileExt( di->Ruta ).LowerCase() != ".txt" )
			di->Ruta += ".txt";

		f1_prin->lConsola->Items->SaveToFile( di->Ruta );
	}

	delete di;
}
//---------------------------------------------------------------------------
void __fastcall aMenuConsola::bLimpiarOnClick( TObject *val )
{
/**/
	if ( MessageBox( GetActiveWindow(), L"Realmente desea borrar la consola", L"", MB_YESNO + MB_ICONQUESTION + MB_DEFBUTTON2 ) == IDYES )
		f1_prin->lConsola->Items->Clear();
}
//---------------------------------------------------------------------------
//###########################################################################


//public ####################################################################
//---------------------------------------------------------------------------
//Creacion
__fastcall aMenuConsola::aMenuConsola( TComponent *Owner ) : TPanel( Owner )
{
/**/
//public:
	//Punteros
	bGuardar = NULL;
	bLimpiar = NULL;

//Inicio
	this->OnApplyStyleLookup = OnAplicarEstilo;
}
//---------------------------------------------------------------------------
//###########################################################################
