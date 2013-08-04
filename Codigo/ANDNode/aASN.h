//---------------------------------------------------------------------------
#ifndef aASNH
#define aASNH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class EArchivo_NO_Valido: public EExternal
{
public:
	inline __fastcall EArchivo_NO_Valido( const String Msg ) : EExternal( Msg ) {}
};
//---------------------------------------------------------------------------
class ELA_RUTA_NO_ES_VALIDA: public EExternal
{
public:
	inline __fastcall ELA_RUTA_NO_ES_VALIDA( const String Msg ) : EExternal( Msg ) {}
};
//---------------------------------------------------------------------------
class PACKAGE aASN : public TComponent
{
public:
	//Variables
	String Archivo   ;
	String Carpeta   ;
	bool   RChrome   ;
	bool   RMozilla  ;
	bool   ROpera    ;
	bool   RIExplorer;

	//Creacion
	__fastcall aASN( TComponent *Owner );

	//Metodos
	void __fastcall Crear( String archivo );
	void __fastcall Leer( String archivo );
};
//---------------------------------------------------------------------------
#endif
