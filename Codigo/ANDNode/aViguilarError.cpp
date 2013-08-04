//---------------------------------------------------------------------------
#pragma hdrstop

//###########################################################################
#include "aViguilarError.h"

#include "_01_Principal.h"
//###########################################################################

#pragma package(smart_init)
//---------------------------------------------------------------------------


//private ###################################################################
//---------------------------------------------------------------------------
//Metodos
void __fastcall aViguilarError::HViguilarServidor( TObject *val )
{
/**/
	aHilo *hil = ( aHilo* )val;

	if ( f1_prin->Consola && !f1_prin->Consola->Corriendo )
		hil->Sincronizar( SViguilarServidor );

	if ( OpenMutex( MUTEX_ALL_ACCESS, false, _nMutex.w_str() ) != NULL ) {
		Sleep( 100 );

		aHilo *hi       = new aHilo();
		hi->SuperHandle = hil->SuperHandle;
		hi->OnFuncion   = HViguilarServidor;
		hi->EmpezarHilo();
	}

	delete hil;
}
//---------------------------------------------------------------------------
void __fastcall aViguilarError::SViguilarServidor( TObject *val )
{
/**/
	if ( f1_prin->Consola )
		f1_prin->Consola->RefrescarServidor();
}
//---------------------------------------------------------------------------
//###########################################################################


//public ####################################################################
//---------------------------------------------------------------------------
//Creacion
__fastcall  aViguilarError::aViguilarError( TComponent *Owner ) : TComponent( Owner )
{
/**/
//private:
	//Variables
	_sh     = GetActiveWindow();
	_nMutex = "";

	//Punteros
	_hMutex = NULL;
}
//---------------------------------------------------------------------------

//Metodos
void __fastcall aViguilarError::ComenzarViguilancia()
{
/**/
	if ( !f1_prin->lArchivo ) return;

	String cad = f1_prin->GetEtiqueta( "arc", f1_prin->lArchivo->TagString );

	if ( cad == "" || !FileExists( cad ) ) return;

	_nMutex = Date().DateString() + Time().TimeString();
	_hMutex = CreateMutex( NULL, true, _nMutex.w_str() );

	aHilo *hi       = new aHilo();
	hi->SuperHandle = _sh;
	hi->OnFuncion   = HViguilarServidor;
	hi->EmpezarHilo();
}
//---------------------------------------------------------------------------
void __fastcall aViguilarError::TerminarViguilancia()
{
/**/
	ReleaseMutex( _hMutex );
}
//---------------------------------------------------------------------------
//###########################################################################