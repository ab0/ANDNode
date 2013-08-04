//---------------------------------------------------------------------------
#ifndef aMenuNuevoH
#define aMenuNuevoH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include <Objbase.h>
#include <Shobjidl.h>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
//---------------------------------------------------------------------------
class PACKAGE aMenuNuevo : public TPanel
{
private:
	//Eventos
	void __fastcall OnAplicarEstilo( TObject *val );

	void __fastcall eArchivoOnChange( TObject *val );
	void __fastcall bArchivoOnClick ( TObject *val );
	void __fastcall bCarpetaOnClick ( TObject *val );

public:
	//Variables
	bool Editando;

	//Punteros
	TEdit     *eArchivo   ;
	TButton   *bArchivo   ;
	TEdit     *eCarpeta   ;
	TButton   *bCarpeta   ;
	TCheckBox *cRChrome   ;
	TCheckBox *cRMozilla  ;
	TCheckBox *cROpera    ;
	TCheckBox *cRIExplorer;

	//Creacion
	__fastcall aMenuNuevo( TComponent *Owner );
};
//---------------------------------------------------------------------------
#endif
