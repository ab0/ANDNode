//---------------------------------------------------------------------------
#ifndef aConsolaH
#define aConsolaH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include <Objbase.h>
#include <Shobjidl.h>

#include "aHilo.h"
//---------------------------------------------------------------------------
class PACKAGE aConsola : public TComponent
{
private:
	//Variables
	HWND   _sh;
	HANDLE _ro;
	HANDLE _ri;
	HANDLE _wo;
	HANDLE _wi;

	bool   _Corriendo  ;
	bool   _Refrescando;
	DWORD  _ExitCode   ;
	String _Servidor   ;

	//Eventos
	TNotifyEvent _OnConsola;

	//Metodos
	void __fastcall Inicio();
	void __fastcall ActivarBotones( DWORD ExitCode );

	void __fastcall HVerSalida( TObject *val );
	void __fastcall SVerSalida( TObject *val );
	void __fastcall SIniciarServidor( TObject *val );

public:
	//Variables
	String SalidaConsola;
	PROCESS_INFORMATION pi;

	//Creacion
	__fastcall  aConsola( TComponent *Owner );
	__fastcall  aConsola( TComponent *Owner, String servidor );
	__fastcall ~aConsola();

	//Metodos
	void __fastcall PararServidor    ();
	void __fastcall RefrescarServidor();
	void __fastcall ViguilarServidor ( bool   viguilar );
	void __fastcall IniciarServidor  ( String servidor );

	//Propiedades
	__property bool         Corriendo = { read = _Corriendo };
	__property String       Servidor  = { read = _Servidor  };
	__property TNotifyEvent OnConsola = { read = _OnConsola, write = _OnConsola };
};
//---------------------------------------------------------------------------
#endif
