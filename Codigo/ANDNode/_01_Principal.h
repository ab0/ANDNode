//---------------------------------------------------------------------------
#ifndef _01_PrincipalH
#define _01_PrincipalH
//---------------------------------------------------------------------------
#include "aConsola.h"
#include "aViguilarError.h"
#include "aViguilarCarpeta.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Ani.hpp>
//---------------------------------------------------------------------------
class Tf1_prin : public TForm
{
__published:
	//Punteros
	TStyleBook *sty;
	TPanel *rTitulo;
	TRectangle *rFondo;
	TLayout *lPie;
	TImage *iGrip;
	TFloatAnimation *aOpciones;
	TLayout *lContenido;
	TFloatAnimation *aOpacidad;
	TListBox *lConsola;

	//Eventos
	void   __fastcall Parametros();
	void   __fastcall ArchivoModificado();
	int    __fastcall RToInt     ( String cadena  );
	void __fastcall AbrirASN     ( String archivo );
	String __fastcall GetEtiqueta( String Etiqueta, String Todo );
	String __fastcall SetEtiqueta( String Etiqueta, String Valor, String Todo );

	void __fastcall bCerrarOnClick   ( TObject *val );
	void __fastcall bRestaurarOnClick( TObject *val );
	void __fastcall bFijarOnClick    ( TObject *val );

	void __fastcall bNuevoOnClick    ( TObject *val );
	void __fastcall bAbrirOnClick    ( TObject *val );
	void __fastcall bGuardarOnClick  ( TObject *val );

	void __fastcall bControlOnClick  ( TObject *val );
	void __fastcall bConsolaOnClick  ( TObject *val );
	void __fastcall bErrorOnClick    ( TObject *val );
	void __fastcall bMicroOnClick    ( TObject *val );

	void __fastcall bRefrescarOnClick( TObject *val );
	void __fastcall bVigilarOnClick  ( TObject *val );
	void __fastcall bIniciarOnClick  ( TObject *val );
	void __fastcall bPararOnClick    ( TObject *val );

	void __fastcall rTituloMouseDown( TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y );
	void __fastcall rTituloApplyStyleLookup(TObject *Sender);
	void __fastcall iGripMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall FormShow(TObject *Sender);

private:
	//Variables
	int   _Height;
	int   _Width ;
	TRect _Micro ;

public:
	//Punteros
	aConsola         *Consola;
	aViguilarError   *VError ;
	aViguilarCarpeta *Vigilar;

	TButton  *bIniciar  ;
	TButton  *bParar    ;
	TButton  *bRefrescar;
	TButton  *bViguilar ;
	TButton  *bError    ;
	TButton  *bGuardar  ;
	TButton  *bControl  ;
	TButton  *bConsola  ;
	TText    *lArchivo  ;
	TText    *lAsterisco;

	//Componente
	__fastcall  Tf1_prin( TComponent *Owner );
	__fastcall ~Tf1_prin();
};
//---------------------------------------------------------------------------
extern PACKAGE Tf1_prin *f1_prin;
//---------------------------------------------------------------------------
#endif
