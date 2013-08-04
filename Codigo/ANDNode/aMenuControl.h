//---------------------------------------------------------------------------
#ifndef aMenuControlH
#define aMenuControlH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include <Objbase.h>
#include <Shobjidl.h>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
//---------------------------------------------------------------------------
class PACKAGE aMenuControl : public TPanel
{
private:
	//Eventos
	void __fastcall OnAplicarEstilo( TObject *val );

	void __fastcall bAsociarOnClick ( TObject *val );

public:
	//Punteros
	TButton *bAsociar;

	//Creacion
	__fastcall aMenuControl( TComponent *Owner );
};
//---------------------------------------------------------------------------
#endif
