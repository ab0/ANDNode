//---------------------------------------------------------------------------
#pragma hdrstop

//###########################################################################
#include "aASN.h"

#define of( A ) sizeof( A )
#define zm( A, B ) ZeroMemory( A, B )
//###########################################################################

#pragma package(smart_init)
//---------------------------------------------------------------------------


//public ####################################################################
//---------------------------------------------------------------------------
//Creacion
__fastcall aASN::aASN( TComponent *Owner ) : TComponent( Owner )
{
/**/
//public:
	//Variables
	Archivo    = "";
	Carpeta    = "";
	RChrome    = false;
	RMozilla   = false;
	ROpera     = false;
	RIExplorer = false;
}
//---------------------------------------------------------------------------

//Metodos
void __fastcall aASN::Crear( String archivo )
{
/**/
	if ( archivo == "" )
		throw ELA_RUTA_NO_ES_VALIDA( "La ruta del archivo esta vacía." );

	int   iDato;
	char *cDato;
	TMemoryStream *ms = new TMemoryStream;

	try {
		ms->Clear();
		ms->Position = 0;

		//Id de Archivo
			cDato = "ASN0.1";                      ms->Write(  cDato, 8                );
			iDato = Archivo.Length();              ms->Write( &iDato, of( iDato )      );
			cDato = AnsiString( Archivo ).c_str(); ms->Write(  cDato, Archivo.Length() );
			iDato = Carpeta.Length();              ms->Write( &iDato, of( iDato )      );
			cDato = AnsiString( Carpeta ).c_str(); ms->Write(  cDato, Carpeta.Length() );
			iDato = ( int )RChrome   ;             ms->Write( &iDato, of( iDato )      );
			iDato = ( int )RMozilla  ;             ms->Write( &iDato, of( iDato )      );
			iDato = ( int )ROpera    ;             ms->Write( &iDato, of( iDato )      );
			iDato = ( int )RIExplorer;             ms->Write( &iDato, of( iDato )      );

		//Guardando Archivo
			if ( FileExists( archivo ) )
				DeleteFile( archivo );

			ms->Position = 0;
			ms->SaveToFile( archivo );
	}
	 __finally {
		delete ms;
	}
}
//---------------------------------------------------------------------------
void __fastcall aASN::Leer( String archivo )
{
/**/
	int  iDato;
	char cDato[ 1024 ];
	TMemoryStream *ms = new TMemoryStream;

	try {
		ms->LoadFromFile( archivo );
		ms->Position = 0;

		//Id de Archivo
			zm( cDato, 1024 ); ms->Read( &cDato, 8           ); if ( ( String )cDato != "ASN0.1" ) throw EArchivo_NO_Valido( "No es un formato valido." );
							   ms->Read( &iDato, of( iDato ) );
			zm( cDato, 1024 ); ms->Read( &cDato,     iDato   ); Archivo    = ( String )cDato;
							   ms->Read( &iDato, of( iDato ) );
			zm( cDato, 1024 ); ms->Read( &cDato,     iDato   ); Carpeta    = ( String )cDato;
							   ms->Read( &iDato, of( iDato ) ); RChrome    = iDato;
							   ms->Read( &iDato, of( iDato ) ); RMozilla   = iDato;
							   ms->Read( &iDato, of( iDato ) ); ROpera     = iDato;
							   ms->Read( &iDato, of( iDato ) ); RIExplorer = iDato;
	}
	 __finally {
		delete ms;
	}
}
//---------------------------------------------------------------------------
//###########################################################################