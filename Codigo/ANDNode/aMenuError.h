//---------------------------------------------------------------------------
#ifndef aMenuErrorH
#define aMenuErrorH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include <Objbase.h>
#include <Shobjidl.h>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
//---------------------------------------------------------------------------
class PACKAGE aMenuError : public TPanel
{
private:
	//Eventos
	void __fastcall OnAplicarEstilo( TObject *val );

	void __fastcall bVigilarErrorOnClick( TObject *val );

public:
	//Punteros
	TButton *bVigilarError;

	//Creacion
	__fastcall aMenuError( TComponent *Owner );
};
//---------------------------------------------------------------------------
#endif
