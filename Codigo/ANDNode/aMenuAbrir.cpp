//---------------------------------------------------------------------------
#pragma hdrstop

//###########################################################################
#include "aMenuAbrir.h"

#include "aASN.h"
#include "aDialogo.h"
#include "_01_Principal.h"
//###########################################################################

#pragma package(smart_init)
//---------------------------------------------------------------------------


//private ###################################################################
//---------------------------------------------------------------------------
//Eventos
void __fastcall aMenuAbrir::OnAplicarEstilo( TObject *val )
{
/**/
	eArchivo = ( TEdit   *)this->FindStyleResource( "edit"  );
	bDialogo = ( TButton *)this->FindStyleResource( "boton" );

	if ( eArchivo )
		eArchivo->OnChange = eArchivoOnChange;

	if ( bDialogo )
		bDialogo->OnClick = bDialogoOnClick;
}
//---------------------------------------------------------------------------

void __fastcall aMenuAbrir::eArchivoOnChange( TObject *val )
{
/**/
	if ( Editando )
		return;

	if ( f1_prin->lArchivo && eArchivo ) {
		if ( ExtractFileExt( eArchivo->Text ).LowerCase() == ".js" ) {
			f1_prin->lArchivo->TagString = f1_prin->SetEtiqueta( "arc", eArchivo->Text, f1_prin->lArchivo->TagString );
			f1_prin->ArchivoModificado();
		}
		else f1_prin->AbrirASN( eArchivo->Text );
	}
}
//---------------------------------------------------------------------------
void __fastcall aMenuAbrir::bDialogoOnClick( TObject *val )
{
/**/
	if ( !eArchivo ) return;

	aDialogo *di         = new aDialogo( this );
	di->Filtro           = "[t1=*.js][t2=*.asn][d1=Archivo JavaScript][d2=Archivo de Servidor AND]";
	di->TodosLosArchivos = "Todos los Archivos";
	di->TodosLosFormatos = "Todos los Formatos";
	di->IndiceExtencion  = 3;

	if ( di->EjecutarOP( GetActiveWindow() ) ) {
		eArchivo->Text = di->Ruta;
	}

	delete di;
}
//---------------------------------------------------------------------------
//###########################################################################


//public ####################################################################
//---------------------------------------------------------------------------
//Creacion
__fastcall aMenuAbrir::aMenuAbrir( TComponent *Owner ) : TPanel( Owner )
{
/**/
//public:
	//Punteros
	eArchivo = NULL;
	bDialogo = NULL;

//private:
	//Variables
	Editando = false;

//Inicio
	this->OnApplyStyleLookup = OnAplicarEstilo;
	this->StyleLookup        = "Menu_Abrir";
}
//---------------------------------------------------------------------------
//###########################################################################
