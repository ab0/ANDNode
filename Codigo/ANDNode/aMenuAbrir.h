//---------------------------------------------------------------------------
#ifndef aMenuAbrirH
#define aMenuAbrirH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include <Objbase.h>
#include <Shobjidl.h>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
//---------------------------------------------------------------------------
class PACKAGE aMenuAbrir : public TPanel
{
private:
	//Eventos
	void __fastcall OnAplicarEstilo( TObject *val );

	void __fastcall eArchivoOnChange( TObject *val );
	void __fastcall bDialogoOnClick ( TObject *val );

public:
	//Variables
	bool Editando;

	//Punteros
	TEdit   *eArchivo;
	TButton *bDialogo;

	//Creacion
	__fastcall aMenuAbrir( TComponent *Owner );
};
//---------------------------------------------------------------------------
#endif
