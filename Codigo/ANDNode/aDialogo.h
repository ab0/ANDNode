//---------------------------------------------------------------------------
#ifndef aDialogoH
#define aDialogoH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include <Objbase.h>
#include <Shobjidl.h>
//---------------------------------------------------------------------------
enum scTipoDialogo{ tdAbrir, tdGuardar, tdDirectorio, tdNinguno };
//---------------------------------------------------------------------------
#pragma option push -b-
enum _scOpcionesDialogo : unsigned char
{
	odSobrescribirArchivo   ,
	odEstrictoTipos         ,
	odNoCargarDir           ,
	odSeleccionarCarpetas   ,
	odVerArchivosSystema    ,
	odSeleccionarTodosShell ,
	odNoValidar             ,
	odMultiSeleccion        ,
	odCarpetaDebeExistir    ,
	odArchivoDebeExistir    ,
	odPreguntarCrear        ,
	odShareAware            ,
	odNoDevolverSoloLectura ,
	odNoEstrictoEnCreacion  ,
	odOcultarListaRecientes ,
	odOcultarPaneles        ,
	odNoReferenciaDeLNK     ,
	odNoAgregarRecientes    ,
	odMostrarArchivosOcultos,
	odDefaultNoModoMini     ,
	odVerPanelVistaPrevia   ,
	odForsarExtencion
};
#pragma option pop
typedef System::Set<_scOpcionesDialogo, _scOpcionesDialogo::odSobrescribirArchivo, _scOpcionesDialogo::odForsarExtencion> scOpcionesDialogo;
//---------------------------------------------------------------------------
class PACKAGE aDialogo : public TComponent
{
private:
	//Variables
	int               _IndiceExtencion ;
	String            _Ruta            ;
	String            _Filtro          ;
	String            _Titulo          ;
	String            _Carpeta         ;
	String            _Extencion       ;
	String            _TodosLosFormatos;
	String            _TodosLosArchivos;
	scTipoDialogo     _TipoDialogo     ;
	scOpcionesDialogo _OpcionesDialogo ;

	//Punteros
	TStringList *_Rutas;

	//Almacenados
	bool __fastcall ATodosLosFormatos();
	bool __fastcall ATodosLosArchivos();
	bool __fastcall AOpcionesDialogo ();

	//Metodos
	HRESULT __fastcall CargarFiltro        ( IFileDialog     *Dialogo, String            val );
	HRESULT __fastcall CargarOpciones      ( IFileDialog     *Dialogo, scOpcionesDialogo val );
	HRESULT __fastcall CargarCarpetaDefault( IFileDialog     *Dialogo, String            val );
	HRESULT __fastcall DevolverRutas       ( IFileOpenDialog *Dialogo, TStringList    *Rutas, String &Ruta );

	bool __fastcall EjecutarOP7( HWND Padre );
	bool __fastcall EjecutarSA7( HWND Padre );
	bool __fastcall EjecutarDI7( HWND Padre );

	String        __fastcall CargarFiltro  ( String            val );
	unsigned long __fastcall CargarOpciones( scOpcionesDialogo val );

	bool __fastcall EjecutarOPXP( HWND Padre );
	bool __fastcall EjecutarSAXP( HWND Padre );
	bool __fastcall EjecutarDIXP( HWND Padre );

	String __fastcall GetEtiqueta( String Etiqueta, String  Todo );
	void   __fastcall SetEtiqueta( String Etiqueta, String& Todo , String Valor );

public:
	//Variables
	bool EsWindows7;

	//Creacion
	__fastcall  aDialogo( TComponent *Owner );
	__fastcall ~aDialogo();

	//Metodos
	void __fastcall Clonar( aDialogo *Dialogo );

	bool __fastcall Ejecutar  ( HWND Padre = NULL );
	bool __fastcall EjecutarOP( HWND Padre = NULL );
	bool __fastcall EjecutarSA( HWND Padre = NULL );
	bool __fastcall EjecutarDI( HWND Padre = NULL );

	//Propiedades
	__property String Extencion = { read = _Extencion };

	__property TStringList *Rutas = { read = _Rutas };

__published:
	//Variables
	__property int               IndiceExtencion  = { read = _IndiceExtencion , write = _IndiceExtencion  , default = -1                          };
	__property String            Ruta             = { read = _Ruta            , write = _Ruta                                                     };
	__property String            Filtro           = { read = _Filtro          , write = _Filtro                                                   };
	__property String            Titulo           = { read = _Titulo          , write = _Titulo                                                   };
	__property String            Carpeta          = { read = _Carpeta         , write = _Carpeta                                                  };
	__property String            TodosLosFormatos = { read = _TodosLosFormatos, write = _TodosLosFormatos , stored = ATodosLosFormatos, nodefault };
	__property String            TodosLosArchivos = { read = _TodosLosArchivos, write = _TodosLosArchivos , stored = ATodosLosArchivos, nodefault };
	__property scTipoDialogo     TipoDialogo      = { read = _TipoDialogo     , write = _TipoDialogo      , default = tdNinguno                   };
	__property scOpcionesDialogo OpcionesDialogo  = { read = _OpcionesDialogo , write = _OpcionesDialogo  , stored = AOpcionesDialogo , nodefault };
};
//---------------------------------------------------------------------------
#endif
