//---------------------------------------------------------------------------
#ifndef aMenuConsolaH
#define aMenuConsolaH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include <Objbase.h>
#include <Shobjidl.h>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
//---------------------------------------------------------------------------
class PACKAGE aMenuConsola : public TPanel
{
private:
	//Eventos
	void __fastcall OnAplicarEstilo( TObject *val );

	void __fastcall bGuardarOnClick( TObject *val );
	void __fastcall bLimpiarOnClick( TObject *val );

public:
	//Punteros
	TButton *bGuardar;
	TButton *bLimpiar;

	//Creacion
	__fastcall aMenuConsola( TComponent *Owner );
};
//---------------------------------------------------------------------------
#endif
