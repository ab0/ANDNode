//---------------------------------------------------------------------------
#pragma hdrstop

//###########################################################################
#include "aHilo.h"
//###########################################################################

#pragma package(smart_init)
//---------------------------------------------------------------------------


//###########################################################################
//---------------------------------------------------------------------------
VOID  CALLBACK ScHiloTTimerProc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
/**/
	aHilo *hi = ( aHilo* )idEvent;

	DWORD dwExitCode;
	bool  bRet = GetExitCodeThread( hi->GetHilo(), &dwExitCode );

	if ( bRet && dwExitCode != STILL_ACTIVE ) {
		KillTimer( hwnd, idEvent );
		CloseHandle( hi->GetHilo() );
		hi->Terminar();
	}
}
//---------------------------------------------------------------------------
DWORD CALLBACK ScHiloThreadProc( LPVOID lpParameter )
{
/**/
	aHilo *hi = ( aHilo* )lpParameter;

	if ( hi ) {
		try {
			if ( hi->OnFuncion )
				hi->OnFuncion( hi );
		}
		catch ( Exception& E ) {
			hi->Error = "(" + hi->IdHilo + ")(" + E.ClassName() + ")" + E.Message;
        }
	}

	return 0;
}
//---------------------------------------------------------------------------
VOID  CALLBACK ScHiloSTimerProc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
/**/
	KillTimer( hwnd, idEvent );

	unsigned int hi = ( unsigned int )idEvent;
	hi -= 1;
	aHilo* hil = ( aHilo* )hi;

	hil->OnSincronizar( hil );

	ReleaseSemaphore( hil->GetHMutex(), 1, 0 );
}
//---------------------------------------------------------------------------
//###########################################################################


//public#####################################################################
//Metodos
void* __fastcall aHilo::GetHilo()
{
/**/
	return _Hilo;
}
//---------------------------------------------------------------------------
void* __fastcall aHilo::GetHMutex()
{
/**/
	return _HMutex;
}
//---------------------------------------------------------------------------

void __fastcall aHilo::Resume()
{
/**/
	ResumeThread( _Hilo );
}
//---------------------------------------------------------------------------
void __fastcall aHilo::Pausar()
{
/**/
	SuspendThread( _Hilo );
}
//---------------------------------------------------------------------------
void __fastcall aHilo::Cancelar()
{
/**/
	if ( OnCancelar )
		OnCancelar( this );
}
//---------------------------------------------------------------------------
void __fastcall aHilo::Terminar()
{
/**/
	if ( OnTerminar )
		OnTerminar( this );

	_Hilo = NULL;
}
//---------------------------------------------------------------------------
void __fastcall aHilo::Sincronizar( TNotifyEvent FFuncion )
{
/**/
	OnSincronizar = FFuncion;

	_HMutex = CreateSemaphoreW( 0, 1, 1, 0 );
	WaitForSingleObject( _HMutex, INFINITE );

	SetTimer( _Handle, ( unsigned int )this + 1, 0, ScHiloSTimerProc );

	WaitForSingleObject( _HMutex, INFINITE );
}
//---------------------------------------------------------------------------

void __fastcall aHilo::EmpezarHilo()
{
/**/
	if ( _Hilo       ) return;
	if ( SuperHandle ) _Handle = SuperHandle;
	if ( !_Handle    ) MessageBoxW( NULL, L"Falta Handle en hilo", L"Falta Handle en hilo", 0 );

	Cancelado = false;

	//Crear la hilo
	_Hilo = CreateThread (
		NULL            , //Atributo de seguridad: Usar el de la thread actual
		0               , //Tamaño del stack. Usar el tamaño por defecto
		ScHiloThreadProc, //Función inicial de la thread
		this            , //Datos a pasar a la thread
		0               , //Flags de creación
		NULL              //Identificador del subproceso
	);

	//Esperar a que temine hilo
	_Timer = SetTimer( _Handle, ( unsigned int )this, 50, ScHiloTTimerProc );
}
//---------------------------------------------------------------------------
//###########################################################################


/************************************(  )************************************/
//---------------------------------------------------------------------------
__fastcall aHilo::aHilo()
	: TPersistent()
{
/**/
//private
	//Variables
	_Handle  = GetActiveWindow();
	_Timer   = 0                ;

	//Punteros
	_Hilo   = NULL;
	_HMutex = NULL;

//public
	//Variavles
	for ( int i = 0; i < scHiloNumeroArreglos; i++ ) {
		TagI[ i ] = 0   ;
		TagS[ i ] = ""  ;
		TagD[ i ] = 0   ;
		TagO[ i ] = NULL;
	}

	Cancelado   = false;
	SuperHandle = NULL ;
	Error       = ""   ;
	IdHilo      = ""   ;

	//Eventos
	OnFuncion     = NULL;
	OnSincronizar = NULL;
	OnCancelar    = NULL;
	OnTerminar    = NULL;
}
//---------------------------------------------------------------------------



