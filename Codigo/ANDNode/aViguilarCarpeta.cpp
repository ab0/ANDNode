//---------------------------------------------------------------------------
#pragma hdrstop

//###########################################################################
#include "_01_Principal.h"
#include "aViguilarCarpeta.h"
//###########################################################################

#pragma package(smart_init)
//---------------------------------------------------------------------------


//###########################################################################
HWND __sh;
//---------------------------------------------------------------------------
BOOL EnumWindowsProc( HWND han, long lParam )
{
/**/
	wchar_t BuffTit[ 255 ], BuffCla[ 255 ];

	//Obteniendo Titulo y Clase
		GetWindowText( han, BuffTit, 254 );
		GetClassName ( han, BuffCla, 254 );

		String Titulo = ( String )BuffTit, Clase = ( String )BuffCla, Condiciones = f1_prin->lArchivo->TagString;

	//Refrescando Navegadores
		if (
			( Clase == "Chrome_WidgetWin_1" && Titulo.Pos( " - Google Chrome"             ) && Condiciones.Pos( "[rnc=1]" ) ) ||
			( Clase == "MozillaWindowClass" && Titulo.Pos( " - Mozilla Firefox"           ) && Condiciones.Pos( "[rnm=1]" ) ) ||
			( Clase == "Chrome_WidgetWin_0" && Titulo.Pos( " - Opera"                     ) && Condiciones.Pos( "[rno=1]" ) ) ||
			( Clase == "IEFrame"            && Titulo.Pos( " - Windows Internet Explorer" ) && Condiciones.Pos( "[rni=1]" ) )
		) {
			HWND ha = GetForegroundWindow();

			//Trayendo al Frente Navegador
				::SendMessage( han, WM_SYSCOMMAND, SC_HOTKEY, ( LPARAM )han );
				::ShowWindow( han, SW_SHOW );
				::SetForegroundWindow( han );
				::SetFocus( han );
				::EnableWindow( han, false );
				::keybd_event( VK_F5, 0, WM_KEYDOWN, 0 );
				::EnableWindow( han, true );

			//Traer enfrente ventana anterior
				::SendMessage( ha, WM_SYSCOMMAND, SC_HOTKEY, ( LPARAM )ha );
				::ShowWindow( ha, SW_SHOW );
				::SetForegroundWindow( ha );
				::SetFocus( ha );
		}

	return true;
}
//---------------------------------------------------------------------------
//###########################################################################


//private ###################################################################
//---------------------------------------------------------------------------
//Metodos
void __fastcall aViguilarCarpeta::RecorrerCarpeta( String carpeta, HWND shandle )
{
/**/
	HWND hFile;
	int  i;
	int  iAttributes;
	TSearchRec info;

	iAttributes = faReadOnly | faHidden | faSysFile | faDirectory | faArchive | faAnyFile;
	i = FindFirst( carpeta + "\\*.*", iAttributes, info );

	while ( i == 0 && _nArchi < 1000 ) {
		if ( info.Name != "." && info.Name != ".." ) {
			_nArchi++;

			String rut = carpeta + "\\" + info.Name;

			if ( DirectoryExists( rut ) )
				RecorrerCarpeta( rut, shandle );
			else if ( FileExists( rut ) ) {
				aHilo *hi       = new aHilo();
				hi->TagS[ 0 ]   = rut;
				hi->SuperHandle = shandle;
				hi->OnFuncion   = HViguilarArchivos;
				hi->EmpezarHilo();
			}
        }

		i = FindNext( info );
	}

	FindClose( info );
}
//---------------------------------------------------------------------------

void __fastcall aViguilarCarpeta::HViguilarArchivos( TObject *val )
{
/**/
	aHilo *hil = ( aHilo* )val;
	String rut = hil->TagS[ 0 ];

	unsigned int hFile;
	FILETIME FecMod;
	FILETIME localfiletime;
	SYSTEMTIME systime;
	TDateTime FechaModificacion;

	hFile = FileOpen( rut, fmOpenRead );
	GetFileTime( ( void* )hFile , NULL, NULL, &FecMod );
	FileClose( ( int )hFile );

	try {
		FileTimeToLocalFileTime( &FecMod, &localfiletime );
		FileTimeToSystemTime( &localfiletime, &systime );
		FechaModificacion = TDateTime( systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds );
	}
	catch ( ... ) {
		FechaModificacion = 0;
	}

	if ( ( int )FechaModificacion != 0 ) {
		if ( hil->TagD[ 0 ] != 0 && ( TDateTime )hil->TagD[ 0 ] != FechaModificacion )
			hil->Sincronizar( SViguilarArchivos );

		hil->TagD[ 0 ] = FechaModificacion;
	}

	if ( f1_prin->Consola && f1_prin->Consola->Corriendo && OpenMutex( MUTEX_ALL_ACCESS, false, _nMutex.w_str() ) != NULL ) {
		Sleep( 100 );

		aHilo *hi       = new aHilo();
		hi->TagS[ 0 ]   = hil->TagS[ 0 ];
		hi->TagD[ 0 ]   = hil->TagD[ 0 ];
		hi->SuperHandle = hil->SuperHandle;
		hi->OnFuncion   = HViguilarArchivos;
		hi->EmpezarHilo();
	}

	delete hil;
}
//---------------------------------------------------------------------------
void __fastcall aViguilarCarpeta::SViguilarArchivos( TObject *val )
{
/**/
	if ( f1_prin->Consola )
		f1_prin->Consola->RefrescarServidor();

	__sh = _sh;
	if ( f1_prin->lArchivo )
		EnumWindows( ( WNDENUMPROC )EnumWindowsProc, 0 );
}
//---------------------------------------------------------------------------
//###########################################################################


//public ####################################################################
//---------------------------------------------------------------------------
//Creacion
__fastcall  aViguilarCarpeta::aViguilarCarpeta( TComponent *Owner ) : TComponent( Owner )
{
/**/
//private:
	//Variables
	_sh     = GetActiveWindow();
	_nArchi = 0;
	_nMutex = NULL;

	//Punteros
	_hMutex = NULL;
}
//---------------------------------------------------------------------------

//Metodos
void __fastcall aViguilarCarpeta::ComenzarViguilancia( String carpeta )
{
/**/
	if ( carpeta == "" || !DirectoryExists( carpeta ) ) return;

	_nArchi = 0;
	_nMutex = Date().DateString() + Time().TimeString();
	_hMutex = CreateMutex( NULL, true, _nMutex.w_str() );

	RecorrerCarpeta( carpeta, _sh );
}
//---------------------------------------------------------------------------
void __fastcall aViguilarCarpeta::TerminarViguilancia()
{
/**/
	ReleaseMutex( _hMutex );
}
//---------------------------------------------------------------------------
//###########################################################################