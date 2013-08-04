//---------------------------------------------------------------------------
#pragma hdrstop

//###########################################################################
#include "aConsola.h"

#include "_01_Principal.h"
//###########################################################################

#pragma package(smart_init)
//---------------------------------------------------------------------------

void *hproc;
//private ###################################################################
//---------------------------------------------------------------------------
//Metodos
void __fastcall aConsola::Inicio()
{
/**/
//private:
	//Variables
	_sh = GetActiveWindow();
	_ro = NULL;
	_ri = NULL;
	_wo = NULL;
	_wi = NULL;

	_Corriendo   = false;
	_Refrescando = false;
	_Servidor    = "";

	//Eventos
	_OnConsola = NULL;
}
//---------------------------------------------------------------------------
void __fastcall aConsola::ActivarBotones( DWORD ExitCode )
{
/**/
	_Corriendo = _Refrescando || ExitCode == STILL_ACTIVE;

	if ( Corriendo && f1_prin->bIniciar && f1_prin->bIniciar->Enabled ) {
		if ( f1_prin->bIniciar   ) f1_prin->bIniciar  ->Enabled = false;
		if ( f1_prin->bParar     ) f1_prin->bParar    ->Enabled = true ;
		if ( f1_prin->bRefrescar ) f1_prin->bRefrescar->Enabled = true ;
		if ( f1_prin->bViguilar  ) {
			f1_prin->bViguilar->Enabled   = f1_prin->GetEtiqueta( "car", f1_prin->lArchivo->TagString ) != "";
			f1_prin->bViguilar->IsPressed = false;
		}
	}
	else if ( !Corriendo && f1_prin->bIniciar && !f1_prin->bIniciar->Enabled ) {
		if ( f1_prin->bIniciar   ) f1_prin->bIniciar  ->Enabled = true ;
		if ( f1_prin->bParar     ) f1_prin->bParar    ->Enabled = false;
		if ( f1_prin->bRefrescar ) f1_prin->bRefrescar->Enabled = false;
		if ( f1_prin->bViguilar  ) {
			f1_prin->bViguilar->Enabled   = false;
			f1_prin->bViguilar->IsPressed = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall aConsola::HVerSalida( TObject *val )
{
/**/
	Sleep( 100 );

	char  Buffer[ 4096 ];
	DWORD bLeidos;

	ZeroMemory( &Buffer, 4096 );
	PeekNamedPipe( _ro, Buffer, sizeof( Buffer ), &bLeidos, NULL, NULL );
	SalidaConsola = "";

	if ( bLeidos > 0 ) {
		ReadFile( _ro, Buffer, bLeidos, NULL, NULL );
		SalidaConsola = Buffer;
	}

	GetExitCodeProcess( pi.hProcess, &_ExitCode );

	( ( aHilo* )val )->Sincronizar( SVerSalida );

	if ( _ExitCode == STILL_ACTIVE ) {
		aHilo *hi       = new aHilo();
		hi->SuperHandle = ( ( aHilo* )val )->SuperHandle;
		hi->IdHilo      = "ver_salida";
		hi->OnFuncion   = HVerSalida;
		hi->EmpezarHilo();
	}

	delete val;
}
//---------------------------------------------------------------------------
void __fastcall aConsola::SVerSalida( TObject *val )
{
/**/
	if ( _OnConsola ) _OnConsola( this );
	ActivarBotones( _ExitCode );
}
//---------------------------------------------------------------------------
//###########################################################################


//public ####################################################################
//---------------------------------------------------------------------------
//Creacion
__fastcall aConsola::aConsola( TComponent *Owner ) : TComponent( Owner )
{
/**/
	Inicio();
}
//---------------------------------------------------------------------------
__fastcall aConsola::aConsola( TComponent *Owner, String servidor ) : TComponent( Owner )
{
/**/
	Inicio();
	IniciarServidor( servidor );
}
//---------------------------------------------------------------------------
__fastcall aConsola::~aConsola()
{
/**/
	TerminateProcess( pi.hProcess, 0 );
}
//---------------------------------------------------------------------------

//Metodos
void __fastcall aConsola::PararServidor()
{
/**/
	if ( pi.hProcess != NULL ) {
		TerminateProcess( pi.hProcess, 0 );

		CloseHandle( _ro ); _ro = NULL;
		CloseHandle( _wo ); _wo = NULL;
		CloseHandle( _ri ); _ri = NULL;
		CloseHandle( _wi ); _wi = NULL;
	}

	ActivarBotones( STILL_ACTIVE + 1 );
}
//---------------------------------------------------------------------------
void __fastcall aConsola::RefrescarServidor()
{
/**/
	_Refrescando = true;

	try {
		PararServidor();
		IniciarServidor( _Servidor );
	}
	__finally {
		_Refrescando = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall aConsola::ViguilarServidor( bool viguilar )
{
/**/

}
//---------------------------------------------------------------------------
void __fastcall aConsola::IniciarServidor( String servidor )
{
/**/
	if ( FileExists( servidor ) ) {
		_Servidor = servidor;

		STARTUPINFO         si;
		SECURITY_ATTRIBUTES sa;
		SECURITY_DESCRIPTOR sd;

		//Inicialisacion de estructuras
			InitializeSecurityDescriptor( &sd, SECURITY_DESCRIPTOR_REVISION );
			SetSecurityDescriptorDacl( &sd, true, NULL, false );
			sa.lpSecurityDescriptor = &sd;

			sa.nLength = sizeof( SECURITY_ATTRIBUTES );
			sa.bInheritHandle = true;

		//Iniciando Node.js
			if ( CreatePipe( &_ri, &_wi, &sa, 0 ) ) {
				if ( CreatePipe( &_ro, &_wo, &sa, 0 ) ) {
					GetStartupInfo( &si );

					si.dwFlags     = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
					si.wShowWindow = SW_HIDE;
					si.hStdOutput  = _wo;
					si.hStdError   = _wo;
					si.hStdInput   = _ri;

					String cad = "node \"" + ExtractFileName( _Servidor ) + "\"";
					CreateProcess( NULL, cad.w_str(), NULL, NULL, true, CREATE_NEW_CONSOLE, NULL, ExtractFileDir( _Servidor ).w_str(), &si, &pi );
				}
			}

		//Viguilando Proceso
			aHilo *hi       = new aHilo();
			hi->SuperHandle = _sh;
			hi->OnFuncion   = HVerSalida;
			hi->EmpezarHilo();
	}
}
//---------------------------------------------------------------------------
//###########################################################################
