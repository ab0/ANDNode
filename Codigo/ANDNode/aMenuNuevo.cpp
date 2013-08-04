//---------------------------------------------------------------------------
#pragma hdrstop

//###########################################################################
#include "aMenuNuevo.h"

#include "aDialogo.h"
#include "_01_Principal.h"
//###########################################################################

#pragma package(smart_init)
//---------------------------------------------------------------------------


//private ###################################################################
//---------------------------------------------------------------------------
//Eventos
void __fastcall aMenuNuevo::OnAplicarEstilo( TObject *val )
{
/**/
	eArchivo    = ( TEdit    * )this->FindStyleResource( "earchivo"    ); if ( eArchivo    ) eArchivo   ->OnChange = eArchivoOnChange;
	bArchivo    = ( TButton  * )this->FindStyleResource( "barchivo"    ); if ( bArchivo    ) bArchivo   ->OnClick  = bArchivoOnClick ;
	eCarpeta    = ( TEdit    * )this->FindStyleResource( "ecarpeta"    ); if ( eCarpeta    ) eCarpeta   ->OnChange = eArchivoOnChange;
	bCarpeta    = ( TButton  * )this->FindStyleResource( "bcarpeta"    ); if ( bCarpeta    ) bCarpeta   ->OnClick  = bCarpetaOnClick ;
	cRChrome    = ( TCheckBox* )this->FindStyleResource( "cRChrome"    ); if ( cRChrome    ) cRChrome   ->OnChange = eArchivoOnChange;
	cRMozilla   = ( TCheckBox* )this->FindStyleResource( "cRMozilla"   ); if ( cRMozilla   ) cRMozilla  ->OnChange = eArchivoOnChange;
	cROpera     = ( TCheckBox* )this->FindStyleResource( "cROpera"     ); if ( cROpera     ) cROpera    ->OnChange = eArchivoOnChange;
	cRIExplorer = ( TCheckBox* )this->FindStyleResource( "cRIExplorer" ); if ( cRIExplorer ) cRIExplorer->OnChange = eArchivoOnChange;
}
//---------------------------------------------------------------------------

void __fastcall aMenuNuevo::eArchivoOnChange( TObject *val )
{
/**/
	if ( Editando )
		return;

	if ( f1_prin->lArchivo && eArchivo && eCarpeta && cRChrome ) {
		f1_prin->lArchivo->TagString =
			"[arc=" + eArchivo->Text + "]"
			"[car=" + eCarpeta->Text + "]"
			"[rnc=" + ( String )( int )cRChrome   ->IsChecked + "]"
			"[rnm=" + ( String )( int )cRMozilla  ->IsChecked + "]"
			"[rno=" + ( String )( int )cROpera    ->IsChecked + "]"
			"[rni=" + ( String )( int )cRIExplorer->IsChecked + "]"
		;

		f1_prin->ArchivoModificado();
	}
}
//---------------------------------------------------------------------------
void __fastcall aMenuNuevo::bArchivoOnClick( TObject *val )
{
/**/
	if ( !eArchivo ) return;

	aDialogo *di         = new aDialogo( this );
	di->Filtro           = "[t1=*.js][d1=Archivo JavaScript]";
	di->TodosLosArchivos = "Todos los Archivos";
	di->IndiceExtencion  = 1;

	if ( di->EjecutarSA( GetActiveWindow() ) )
		eArchivo->Text = di->Ruta;

	delete di;
}
//---------------------------------------------------------------------------
void __fastcall aMenuNuevo::bCarpetaOnClick( TObject *val )
{
/**/
	if ( !eArchivo ) return;

	aDialogo *di = new aDialogo( this );

	if ( di->EjecutarDI( GetActiveWindow() ) )
		eCarpeta->Text = di->Ruta;

	delete di;
}
//---------------------------------------------------------------------------
//###########################################################################


//public ####################################################################
//---------------------------------------------------------------------------
//Creacion
__fastcall aMenuNuevo::aMenuNuevo( TComponent *Owner ) : TPanel( Owner )
{
/**/
//public:
	//Punteros
	eArchivo = NULL;
	bArchivo = NULL;
	eCarpeta = NULL;
	bCarpeta = NULL;

//private:
	//Variables
	Editando = false;

//Inicio
	this->OnApplyStyleLookup = OnAplicarEstilo;
	this->StyleLookup        = "Menu_Nuevo";
}
//---------------------------------------------------------------------------
//###########################################################################
