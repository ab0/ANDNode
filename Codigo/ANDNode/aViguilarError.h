//---------------------------------------------------------------------------
#ifndef aViguilarErrorH
#define aViguilarErrorH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include "aHilo.h"
//---------------------------------------------------------------------------
class PACKAGE aViguilarError : public TComponent
{
private:
	//Variables
	HWND   _sh;
	String _nMutex;

	//Punteros
	void *_hMutex;

	//Metodos
	void __fastcall HViguilarServidor( TObject *val );
	void __fastcall SViguilarServidor( TObject *val );

public:
	//Creacion
	__fastcall  aViguilarError( TComponent *Owner );

	//Metodos
	void __fastcall ComenzarViguilancia();
	void __fastcall TerminarViguilancia();
};
//---------------------------------------------------------------------------
#endif
