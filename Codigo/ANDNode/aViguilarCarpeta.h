//---------------------------------------------------------------------------
#ifndef aViguilarCarpetaH
#define aViguilarCarpetaH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include "aHilo.h"
#include "aConsola.h"
//---------------------------------------------------------------------------
class PACKAGE aViguilarCarpeta : public TComponent
{
private:
	//Variables
	HWND    _sh;
	int     _nArchi;
	String  _nMutex;

	//Punteros
	void *_hMutex;

	//Metodos
	void __fastcall RecorrerCarpeta  ( String carpeta, HWND shandle );

	void __fastcall HViguilarArchivos( TObject *val   );
	void __fastcall SViguilarArchivos( TObject *val   );

public:
	//Creacion
	__fastcall  aViguilarCarpeta( TComponent *Owner );

	//Metodos
	void __fastcall ComenzarViguilancia( String carpeta );
	void __fastcall TerminarViguilancia();
};
//---------------------------------------------------------------------------
#endif
