//---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop

//###########################################################################
#include "_01_Principal.h"

#include "aASN.h"
#include "Shlobj.h"
#include "aDialogo.h"
#include "Registry.hpp"
#include "aMenuNuevo.h"
#include "aMenuAbrir.h"
#include "aMenuError.h"
#include "aMenuControl.h"
#include "aMenuConsola.h"

#define AltoTitulo 46

#define MenuNuevo   283
#define MenuAbrir   92
#define MenuControl 92.5
#define MenuConsola 93
#define MenuError   93.5

#pragma resource "_ANDNode.res"
//###########################################################################

#pragma package(smart_init)
#pragma resource "*.fmx"
Tf1_prin *f1_prin;
//---------------------------------------------------------------------------


//###########################################################################
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::Parametros()
{
/**/
	String par = ParamStr( 1 );

	if ( par.Pos( "[AsociarExtensiones]" ) ) {
		//Borrar Extencion
			String DirectorioExtencion = "";
			TRegistry* reg = new TRegistry;
			reg->RootKey   = HKEY_CLASSES_ROOT;

			if ( reg->OpenKey( ".asn", false ) ) {
				DirectorioExtencion = reg->ReadString( "" );
				reg->CloseKey();
				reg->DeleteKey( ".asn" );
			}

			if ( DirectorioExtencion != "" ) reg->DeleteKey( DirectorioExtencion );

			reg->CloseKey();
			delete reg;

		//Asosiar Extenciones
			String RutaExe              = ParamStr( 0 );
			String Extencion            = ".asn";
			String RutaIcono            = ParamStr( 0 );
			String NombreMenu           = "Nodo1";
			String IndiceIcono          = "1";
			String CaptionMenu          = "Proyecto de servidor Node.js";
				   DirectorioExtencion  = "ANDNode01" + Extencion;
			String DescripcionExtencion = "Proyecto de servidor Node.js";

			reg          = new TRegistry;
			reg->RootKey = HKEY_CLASSES_ROOT;

			if ( reg->OpenKey( Extencion, true ) ){
				reg->WriteString( "", DirectorioExtencion );
				reg->CloseKey();

				if ( reg->OpenKey( DirectorioExtencion, true ) ){
					reg->WriteString( "", DescripcionExtencion );
					reg->CloseKey();

					if ( reg->OpenKey( DirectorioExtencion + "\\DefaultIcon", true ) ){
						reg->WriteString( "", "\"" + RutaIcono + "\"," + IndiceIcono );
						reg->CloseKey();
					}

					if ( reg->OpenKey( DirectorioExtencion + "\\Shell", true ) ){
						reg->WriteString( "", NombreMenu );
						reg->CloseKey();

						if ( reg->OpenKey( DirectorioExtencion + "\\Shell\\" + NombreMenu, true ) ){
							reg->WriteString( "", CaptionMenu );
							reg->CloseKey();
						}

						if ( reg->OpenKey( DirectorioExtencion + "\\Shell\\" + NombreMenu + "\\Command", true ) ){
							reg->WriteString( "", "\"" + RutaExe + "\" \"%1\"" );
							reg->CloseKey();
						}
					}
				}
			}

			reg->CloseKey( );
			delete reg;

		//Recargar explorer.exe
			SHChangeNotify( SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL );

		//Cerrando Aplicacion
			MessageBoxA( GetActiveWindow(), "La extensión se asoció correctamente.", "", MB_ICONINFORMATION );
			TerminateProcess( GetCurrentProcess(), 0 );
	}
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::ArchivoModificado()
{
/**/
 	if ( lAsterisco )
		lAsterisco->Text = "*";

	if ( bGuardar )
		bGuardar->Enabled = true;
}
//---------------------------------------------------------------------------
int __fastcall Tf1_prin::RToInt( String cadena )
{
/**/
	try {
		return cadena.ToInt();
	}
	catch ( ... ) {
		return 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::AbrirASN( String archivo )
{
/**/
	aASN *ar = new aASN( this );
	ar->Leer( archivo );

	if ( lArchivo ) {
		lArchivo->Text = archivo;
		lArchivo->Canvas->Font->Size = lArchivo->Font->Size;
		lArchivo->Width = lArchivo->Canvas->TextWidth( lArchivo->Text );
		lArchivo->TagString =
			"[arc=" + ar->Archivo + "]"
			"[car=" + ar->Carpeta + "]"
			"[rnc=" + ( String )( int )ar->RChrome    + "]"
			"[rnm=" + ( String )( int )ar->RMozilla   + "]"
			"[rno=" + ( String )( int )ar->ROpera     + "]"
			"[rni=" + ( String )( int )ar->RIExplorer + "]"
		;
	}

	delete ar;
}
//---------------------------------------------------------------------------
String __fastcall Tf1_prin::GetEtiqueta( String Etiqueta, String Todo )
{
/**/
	if ( Todo.Pos( "[" + Etiqueta + "=" ) == 0 )
		return "";

	Todo = Todo.SubString( Todo.Pos( "[" + Etiqueta + "=" ) + Etiqueta.Length() + 2, Todo.Length() );
	return Todo.SubString( 1, Todo.Pos( "]" ) - 1 );
}
//---------------------------------------------------------------------------
String __fastcall Tf1_prin::SetEtiqueta( String Etiqueta, String Valor, String Todo )
{
/**/
	if ( Todo.Pos( "[" + Etiqueta + "=" ) > 0 )
		Todo = StringReplace( Todo, "[" + Etiqueta + "=" + GetEtiqueta( Etiqueta, Todo ) + "]", "", TReplaceFlags() << rfReplaceAll );

	return Todo + "[" + Etiqueta + "=" + Valor + "]";
}
//---------------------------------------------------------------------------

void __fastcall Tf1_prin::bCerrarOnClick( TObject *val )
{
/**/
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::bRestaurarOnClick( TObject *val )
{
/**/
	WindowState = TWindowState::wsMinimized;
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::bFijarOnClick( TObject *val )
{
/**/
	TButton *bot = ( TButton* )val;

	if ( bot->Tag == 0 ) {
		bot->Tag = 1;
		TRectangle *rec = ( TRectangle* )bot->FindStyleResource( "fondo" );
		if ( rec ) rec->Height = 10;

		SetWindowPos( GetActiveWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE + SWP_NOSIZE );
	}
	else {
		bot->Tag = 0;
		TRectangle *rec = ( TRectangle* )bot->FindStyleResource( "fondo" );
		if ( rec ) rec->Height = 5;

		SetWindowPos( GetActiveWindow(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE + SWP_NOSIZE );
	}
}
//---------------------------------------------------------------------------

void __fastcall Tf1_prin::bNuevoOnClick( TObject *val )
{
/**/
	if ( val->ClassType() == __classid( TButton ) ) {
		if ( rTitulo->Height == AltoTitulo ) {
			float dur = ( ( MenuNuevo - rTitulo->Height ) * 0.08 ) / 100;
			if ( dur <= -1  ) dur *= -1;
			if ( dur < 0.1 && dur  > 0.01 ) dur = 0.1;
			if ( dur < 0.01 ) dur  = 0;
			if ( dur > 0.4  ) dur  = 0.4;

			aOpciones->Duration   = dur;
			aOpciones->OnFinish   = bNuevoOnClick;
			aOpciones->StartValue = rTitulo->Height;
			aOpciones->StopValue  = MenuNuevo;
			aOpciones->Start();
		}
		else {
			aOpacidad->OnFinish   = bNuevoOnClick;
			aOpacidad->StartValue = 1;
			aOpacidad->StopValue  = 0;
			aOpacidad->Start();
		}
	}
	else if ( val->ClassType() == __classid( TFloatAnimation ) ) {
		TFloatAnimation *fl = ( TFloatAnimation* )val;

		if ( fl->PropertyName == "Height" ) {
			aMenuNuevo *nu  = new aMenuNuevo( this );
			nu->Parent      = lContenido;
			nu->Align       = TAlignLayout::alClient;
			nu->StyleLookup = "menu_nuevo";

			if ( lArchivo ) {
				String cad;
				nu->Editando = true;

				if ( nu->eCarpeta    ) nu->eCarpeta   ->Text      = GetEtiqueta( "car", lArchivo->TagString );
				if ( nu->eArchivo    ) nu->eArchivo   ->Text      = GetEtiqueta( "arc", lArchivo->TagString );
				if ( nu->cRChrome    ) nu->cRChrome   ->IsChecked = lArchivo->TagString.Pos( "[rnc=1]" ) > 0;
				if ( nu->cRMozilla   ) nu->cRMozilla  ->IsChecked = lArchivo->TagString.Pos( "[rnm=1]" ) > 0;
				if ( nu->cROpera     ) nu->cROpera    ->IsChecked = lArchivo->TagString.Pos( "[rno=1]" ) > 0;
				if ( nu->cRIExplorer ) nu->cRIExplorer->IsChecked = lArchivo->TagString.Pos( "[rni=1]" ) > 0;

				nu->Editando = false;
			}

			lContenido->TagObject = nu;

			aOpacidad->OnFinish   = NULL;
			aOpacidad->StartValue = 0;
			aOpacidad->StopValue  = 1;
			aOpacidad->Start();
		}
		else if ( fl->PropertyName == "Opacity" ) {
			if ( lContenido->TagObject ) {
				delete lContenido->TagObject;
				lContenido->TagObject = NULL;
			}

			if ( rTitulo->Height == MenuNuevo ) {
				aOpciones->OnFinish   = NULL;
				aOpciones->StartValue = MenuNuevo;
				aOpciones->StopValue  = AltoTitulo;
				aOpciones->Start();
			}
			else {
				float dur = ( ( MenuNuevo - rTitulo->Height ) * 0.08 ) / 100;
				if ( dur <= -1  ) dur *= -1;
				if ( dur < 0.1 && dur  > 0.01 ) dur = 0.1;
				if ( dur < 0.01 ) dur  = 0;
				if ( dur > 0.4  ) dur  = 0.4;

				aOpciones->Duration   = dur;
				aOpciones->OnFinish   = bNuevoOnClick;
				aOpciones->StartValue = rTitulo->Height;
				aOpciones->StopValue  = MenuNuevo;
				aOpciones->Start();
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::bAbrirOnClick( TObject *val )
{
/**/
	if ( val->ClassType() == __classid( TButton ) ) {
		if ( rTitulo->Height == AltoTitulo ) {
			float dur = ( ( MenuAbrir - rTitulo->Height ) * 0.08 ) / 100;
			if ( dur <= -1  ) dur *= -1;
			if ( dur < 0.1 && dur  > 0.01 ) dur = 0.1;
			if ( dur < 0.01 ) dur  = 0;
			if ( dur > 0.4  ) dur  = 0.4;

			aOpciones->Duration   = dur;
			aOpciones->OnFinish   = bAbrirOnClick;
			aOpciones->StartValue = rTitulo->Height;
			aOpciones->StopValue  = MenuAbrir;
			aOpciones->Start();
		}
		else {
			aOpacidad->OnFinish   = bAbrirOnClick;
			aOpacidad->StartValue = 1;
			aOpacidad->StopValue  = 0;
			aOpacidad->Start();
		}
	}
	else if ( val->ClassType() == __classid( TFloatAnimation ) ) {
		TFloatAnimation *fl = ( TFloatAnimation* )val;

		if ( fl->PropertyName == "Height" ) {
			aMenuAbrir *nu  = new aMenuAbrir( this );
			nu->Parent      = lContenido;
			nu->Align       = TAlignLayout::alClient;
			nu->StyleLookup = "menu_abrir";

			if ( lArchivo && nu->eArchivo ) {
				nu->Editando       = true;
				nu->eArchivo->Text = lArchivo->Text;
				nu->Editando       = false;
			}

			lContenido->TagObject = nu;

			aOpacidad->OnFinish   = NULL;
			aOpacidad->StartValue = 0;
			aOpacidad->StopValue  = 1;
			aOpacidad->Start();
		}
		else if ( fl->PropertyName == "Opacity" ) {
			if ( lContenido->TagObject ) {
				delete lContenido->TagObject;
				lContenido->TagObject = NULL;
			}

			if ( rTitulo->Height == MenuAbrir ) {
				aOpciones->OnFinish   = NULL;
				aOpciones->StartValue = MenuAbrir;
				aOpciones->StopValue  = AltoTitulo;
				aOpciones->Start();
			}
			else {
				float dur = ( ( MenuAbrir - rTitulo->Height ) * 0.08 ) / 100;
				if ( dur <= -1  ) dur *= -1;
				if ( dur < 0.1 && dur  > 0.01 ) dur = 0.1;
				if ( dur < 0.01 ) dur  = 0;
				if ( dur > 0.4  ) dur  = 0.4;

				aOpciones->Duration   = dur;
				aOpciones->OnFinish   = bAbrirOnClick;
				aOpciones->StartValue = rTitulo->Height;
				aOpciones->StopValue  = MenuAbrir;
				aOpciones->Start();
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::bGuardarOnClick( TObject *val )
{
/**/
	if ( !lArchivo ) return;

	if ( !FileExists( lArchivo->Text ) ) {
		aDialogo *di        = new aDialogo( this );
		di->Filtro          = "[t1=*.asn][d1=Proyecto de servidor Node.js]";
		di->IndiceExtencion = 1;
		di->OpcionesDialogo = di->OpcionesDialogo << odSobrescribirArchivo;

		if ( di->EjecutarSA( GetActiveWindow() ) ) {
			if ( ExtractFileExt( di->Ruta ).LowerCase() != ".asn" )
				di->Ruta += ".asn";

			lArchivo->Text  = di->Ruta;
			lArchivo->Canvas->Font->Size = lArchivo->Font->Size;
			lArchivo->Width = lArchivo->Canvas->TextWidth( lArchivo->Text ) + 1;

			goto salto1;
		}
	}
	else {
		salto1:
		aASN *ar        = new aASN( this );
		ar->Archivo     = GetEtiqueta( "arc", lArchivo->TagString );
		ar->Carpeta     = GetEtiqueta( "car", lArchivo->TagString );
		ar->RChrome    = RToInt( GetEtiqueta( "rnc", lArchivo->TagString ) );
		ar->RMozilla   = RToInt( GetEtiqueta( "rnm", lArchivo->TagString ) );
		ar->ROpera     = RToInt( GetEtiqueta( "rno", lArchivo->TagString ) );
		ar->RIExplorer = RToInt( GetEtiqueta( "rni", lArchivo->TagString ) );
		ar->Crear( lArchivo->Text );

		if ( lAsterisco )
			lAsterisco->Text = "";

		if ( bGuardar )
			bGuardar->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tf1_prin::bControlOnClick( TObject *val )
{
/**/
	if ( val->ClassType() == __classid( TButton ) ) {
		if ( rTitulo->Height == AltoTitulo ) {
			float dur = ( ( MenuAbrir - rTitulo->Height ) * 0.08 ) / 100;
			if ( dur <= -1  ) dur *= -1;
			if ( dur < 0.1 && dur  > 0.01 ) dur = 0.1;
			if ( dur < 0.01 ) dur  = 0;
			if ( dur > 0.4  ) dur  = 0.4;

			aOpciones->Duration   = dur;
			aOpciones->OnFinish   = bControlOnClick;
			aOpciones->StartValue = rTitulo->Height;
			aOpciones->StopValue  = MenuControl;
			aOpciones->Start();
		}
		else {
			aOpacidad->OnFinish   = bControlOnClick;
			aOpacidad->StartValue = 1;
			aOpacidad->StopValue  = 0;
			aOpacidad->Start();
		}
	}
	else if ( val->ClassType() == __classid( TFloatAnimation ) ) {
		TFloatAnimation *fl = ( TFloatAnimation* )val;

		if ( fl->PropertyName == "Height" ) {
			aMenuControl *nu  = new aMenuControl( this );
			nu->Parent      = lContenido;
			nu->Align       = TAlignLayout::alClient;
			nu->StyleLookup = "menu_control";

			TLayout *la = ( TLayout* )nu->FindStyleResource( "separacion" );
			if ( la && bControl ) la->Width = bControl->AbsoluteRect.Left;

			lContenido->TagObject = nu;

			aOpacidad->OnFinish   = NULL;
			aOpacidad->StartValue = 0;
			aOpacidad->StopValue  = 1;
			aOpacidad->Start();
		}
		else if ( fl->PropertyName == "Opacity" ) {
			if ( lContenido->TagObject ) {
				delete lContenido->TagObject;
				lContenido->TagObject = NULL;
			}

			if ( rTitulo->Height == MenuControl ) {
				aOpciones->OnFinish   = NULL;
				aOpciones->StartValue = MenuControl;
				aOpciones->StopValue  = AltoTitulo;
				aOpciones->Start();
			}
			else {
				float dur = ( ( MenuControl - rTitulo->Height ) * 0.08 ) / 100;
				if ( dur <= -1  ) dur *= -1;
				if ( dur < 0.1 && dur  > 0.01 ) dur = 0.1;
				if ( dur < 0.01 ) dur  = 0;
				if ( dur > 0.4  ) dur  = 0.4;

				aOpciones->Duration   = dur;
				aOpciones->OnFinish   = bControlOnClick;
				aOpciones->StartValue = rTitulo->Height;
				aOpciones->StopValue  = MenuControl;
				aOpciones->Start();
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::bConsolaOnClick( TObject *val )
{
/**/
	if ( val->ClassType() == __classid( TButton ) ) {
		if ( rTitulo->Height == AltoTitulo ) {
			float dur = ( ( MenuConsola - rTitulo->Height ) * 0.08 ) / 100;
			if ( dur <= -1  ) dur *= -1;
			if ( dur < 0.1 && dur  > 0.01 ) dur = 0.1;
			if ( dur < 0.01 ) dur  = 0;
			if ( dur > 0.4  ) dur  = 0.4;

			aOpciones->Duration   = dur;
			aOpciones->OnFinish   = bConsolaOnClick;
			aOpciones->StartValue = rTitulo->Height;
			aOpciones->StopValue  = MenuConsola;
			aOpciones->Start();
		}
		else {
			aOpacidad->OnFinish   = bConsolaOnClick;
			aOpacidad->StartValue = 1;
			aOpacidad->StopValue  = 0;
			aOpacidad->Start();
		}
	}
	else if ( val->ClassType() == __classid( TFloatAnimation ) ) {
		TFloatAnimation *fl = ( TFloatAnimation* )val;

		if ( fl->PropertyName == "Height" ) {
			aMenuConsola *nu  = new aMenuConsola( this );
			nu->Parent      = lContenido;
			nu->Align       = TAlignLayout::alClient;
			nu->StyleLookup = "menu_consola";

			TLayout *la = ( TLayout* )nu->FindStyleResource( "separacion" );
			if ( la && bConsola ) la->Width = bConsola->AbsoluteRect.Left;

			lContenido->TagObject = nu;

			aOpacidad->OnFinish   = NULL;
			aOpacidad->StartValue = 0;
			aOpacidad->StopValue  = 1;
			aOpacidad->Start();
		}
		else if ( fl->PropertyName == "Opacity" ) {
			if ( lContenido->TagObject ) {
				delete lContenido->TagObject;
				lContenido->TagObject = NULL;
			}

			if ( rTitulo->Height == MenuConsola ) {
				aOpciones->OnFinish   = NULL;
				aOpciones->StartValue = MenuConsola;
				aOpciones->StopValue  = AltoTitulo;
				aOpciones->Start();
			}
			else {
				float dur = ( ( MenuConsola - rTitulo->Height ) * 0.08 ) / 100;
				if ( dur <= -1  ) dur *= -1;
				if ( dur < 0.1 && dur  > 0.01 ) dur = 0.1;
				if ( dur < 0.01 ) dur  = 0;
				if ( dur > 0.4  ) dur  = 0.4;

				aOpciones->Duration   = dur;
				aOpciones->OnFinish   = bConsolaOnClick;
				aOpciones->StartValue = rTitulo->Height;
				aOpciones->StopValue  = MenuConsola;
				aOpciones->Start();
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::bErrorOnClick( TObject *val )
{
/**/
	if ( val->ClassType() == __classid( TButton ) ) {
		if ( rTitulo->Height == AltoTitulo ) {
			float dur = ( ( MenuError - rTitulo->Height ) * 0.08 ) / 100;
			if ( dur <= -1  ) dur *= -1;
			if ( dur < 0.1 && dur  > 0.01 ) dur = 0.1;
			if ( dur < 0.01 ) dur  = 0;
			if ( dur > 0.4  ) dur  = 0.4;

			aOpciones->Duration   = dur;
			aOpciones->OnFinish   = bErrorOnClick;
			aOpciones->StartValue = rTitulo->Height;
			aOpciones->StopValue  = MenuError;
			aOpciones->Start();
		}
		else {
			aOpacidad->OnFinish   = bErrorOnClick;
			aOpacidad->StartValue = 1;
			aOpacidad->StopValue  = 0;
			aOpacidad->Start();
		}
	}
	else if ( val->ClassType() == __classid( TFloatAnimation ) ) {
		TFloatAnimation *fl = ( TFloatAnimation* )val;

		if ( fl->PropertyName == "Height" ) {
			aMenuError *nu  = new aMenuError( this );
			nu->Parent      = lContenido;
			nu->Align       = TAlignLayout::alClient;
			nu->StyleLookup = "menu_error";

			TLayout *la = ( TLayout* )nu->FindStyleResource( "separacion" );
			if ( la && bConsola ) la->Width = bError->AbsoluteRect.Left;

			if ( nu->bVigilarError )
				nu->bVigilarError->IsPressed = VError != NULL;

			lContenido->TagObject = nu;

			aOpacidad->OnFinish   = NULL;
			aOpacidad->StartValue = 0;
			aOpacidad->StopValue  = 1;
			aOpacidad->Start();
		}
		else if ( fl->PropertyName == "Opacity" ) {
			if ( lContenido->TagObject ) {
				delete lContenido->TagObject;
				lContenido->TagObject = NULL;
			}

			if ( rTitulo->Height == MenuError ) {
				aOpciones->OnFinish   = NULL;
				aOpciones->StartValue = MenuError;
				aOpciones->StopValue  = AltoTitulo;
				aOpciones->Start();
			}
			else {
				float dur = ( ( MenuError - rTitulo->Height ) * 0.08 ) / 100;
				if ( dur <= -1  ) dur *= -1;
				if ( dur < 0.1 && dur  > 0.01 ) dur = 0.1;
				if ( dur < 0.01 ) dur  = 0;
				if ( dur > 0.4  ) dur  = 0.4;

				aOpciones->Duration   = dur;
				aOpciones->OnFinish   = bErrorOnClick;
				aOpciones->StartValue = rTitulo->Height;
				aOpciones->StopValue  = MenuError;
				aOpciones->Start();
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::bMicroOnClick( TObject *val )
{
/**/
	TButton *bot = ( TButton* )rTitulo->FindStyleResource( "bnuevo"   ); if ( bot ) bot->Enabled = _Height != 0;
			 bot = ( TButton* )rTitulo->FindStyleResource( "babrir"   ); if ( bot ) bot->Enabled = _Height != 0;
			 bot = ( TButton* )rTitulo->FindStyleResource( "bguardar" ); if ( bot ) bot->Enabled = _Height != 0;
			 bot = ( TButton* )rTitulo->FindStyleResource( "bcontrol" ); if ( bot ) bot->Enabled = _Height != 0;
			 bot = ( TButton* )rTitulo->FindStyleResource( "bconsola" ); if ( bot ) bot->Enabled = _Height != 0;

	TRect med;
	SystemParametersInfo( SPI_GETWORKAREA, 0, &med, SPIF_SENDCHANGE );

	if ( _Height == 0 ) {
		_Width          = this->Width ;
		_Height         = this->Height;

		rTitulo->Height = 46;
		this->Height    = 46;
		this->Top       = _Micro.Top     < 0   ? 0   : ( _Micro.Top  + _Micro.Height() > med.Height() ? med.Height() - _Micro.Height() : _Micro.Top  );
		this->Left      = _Micro.Left    < 0   ? 0   : ( _Micro.Left + _Micro.Width()  > med.Width () ? med.Width () - _Micro.Width () : _Micro.Left );
		this->Width     = _Micro.Width() < 100 ? 295 : _Micro.Width();
		iGrip->Cursor   = crSizeWE;

		if ( lContenido->TagObject ){
			delete lContenido->TagObject;
			lContenido->TagObject = NULL;
		}
	}
	else {
		iGrip->Cursor = crSizeNWSE;
		_Micro.Top    = this->Top;
		_Micro.Left   = this->Left;
		_Micro.Right  = this->Left + this->Width;
		this->Width   = _Width;
		this->Height  = _Height;

		if ( this->Top  + this->Height > med.Height() ) this->Top  = med.Height() - this->Height;
		if ( this->Left + this->Width  > med.Width () ) this->Left = med.Width () - this->Width ;

		_Height       = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tf1_prin::bRefrescarOnClick( TObject *val )
{
/**/
	if ( Consola )
		Consola->RefrescarServidor();
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::bVigilarOnClick( TObject *val )
{
/**/
	if ( !bViguilar || !lArchivo ) return;

	if ( bViguilar->IsPressed ) {
		Vigilar = new aViguilarCarpeta( this );
		Vigilar->ComenzarViguilancia( GetEtiqueta( "car", lArchivo->TagString ) );
	}
	else if ( Vigilar ) {
		Vigilar->TerminarViguilancia();
		delete Vigilar;
		Vigilar = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::bIniciarOnClick( TObject *val )
{
/**/
	if ( val->ClassType() == __classid( TButton ) ) {
		if ( !lArchivo ) return;

		String cad = lArchivo->TagString;
		cad = cad.SubString( cad.Pos( "[arc=" ) + 5, cad.Length() );
		cad = cad.SubString( 1, cad.Pos( "]" ) - 1 );

		if ( FileExists( cad ) ) {
			if ( !Consola )
				Consola = new aConsola( this );

			Consola->OnConsola = bIniciarOnClick;
			Consola->IniciarServidor( cad );
		}
	}
	else if ( val->ClassType() == __classid( aConsola ) ) {
		aConsola *co = ( aConsola* )val;

		if ( co->SalidaConsola != "" ) {
			int pos = co->SalidaConsola.Pos( "\n" );

			while ( pos > 0 ) {
				int           ind = lConsola->Items->Add( co->SalidaConsola.SubString( 1, pos - 1 ) );
				TListBoxItem *ite = lConsola->ItemByIndex( ind );
				TText        *tex = ( TText* )ite->FindStyleResource( "text" );
				if ( tex ) {
					tex->Canvas->Font->Size = tex->Font->Size;
					ite->Height = tex->Canvas->TextHeight( tex->Text ) + 2;
				}

				co->SalidaConsola = co->SalidaConsola.SubString( pos + 1, co->SalidaConsola.Length() );
				pos = co->SalidaConsola.Pos( "\n" );
			}

			if ( co->SalidaConsola != "" ) {
				int           ind = lConsola->Items->Add( co->SalidaConsola );
				TListBoxItem *ite = lConsola->ItemByIndex( ind );
				TText        *tex = ( TText* )ite->FindStyleResource( "text" );
				if ( tex ) {
					tex->Canvas->Font->Size = tex->Font->Size;
					ite->Height = tex->Canvas->TextHeight( tex->Text ) + 2;
				}
			}
		}
    }
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::bPararOnClick( TObject *val )
{
/**/
	if ( Consola )
		Consola->PararServidor();
}
//---------------------------------------------------------------------------
//###########################################################################


/************************************(  )************************************/
//---------------------------------------------------------------------------
__fastcall Tf1_prin::Tf1_prin(TComponent* Owner)
	: TForm(Owner)
{
/**/
	_Height = 0;

	//Inicio
		Parametros();
		rTitulo->StyleLookup = "barra_titulo";
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::FormShow(TObject *Sender)
{
/**/
	String par = ParamStr( 1 );

	if ( FileExists( par ) )
		AbrirASN( par );
}
//---------------------------------------------------------------------------
__fastcall Tf1_prin::~Tf1_prin()
{
/**/
	if ( Consola )
		delete Consola;
}
//---------------------------------------------------------------------------


/*********************************( Imagen )*********************************/
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::iGripMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y)
{
/**/
	int    w = this->Width, h = this->Height;
	bool abd = GetSystemMetrics( SM_SWAPBUTTON ) != 0;
	TPoint a, n;

	GetCursorPos( &a );

	while ( ( !abd && GetAsyncKeyState( VK_LBUTTON ) != 0 ) || ( abd && GetAsyncKeyState( VK_RBUTTON ) != 0 ) ) {
		GetCursorPos( &n );
		int ny = n.y - a.y, nx = n.x - a.x;

		if ( _Height == 0 ) this->Height = h + ny;

		this->Width = w + nx;

		Application->ProcessMessages();
	}
}
//---------------------------------------------------------------------------


/*******************************( Rectangulo )*******************************/
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::rTituloApplyStyleLookup(TObject *Sender)
{
/**/
	//Botones de Sistema
		TButton *bot = ( TButton* )rTitulo->FindStyleResource( "cerrar"     ); if ( bot        )   bot       ->OnClick = bCerrarOnClick   ;
				 bot = ( TButton* )rTitulo->FindStyleResource( "restaurar"  ); if ( bot        )   bot       ->OnClick = bRestaurarOnClick;
				 bot = ( TButton* )rTitulo->FindStyleResource( "fijar"      ); if ( bot        )   bot       ->OnClick = bFijarOnClick    ;

	//Botones de Accion
		bot          = ( TButton* )rTitulo->FindStyleResource( "bnuevo"     ); if ( bot        )   bot       ->OnClick = bNuevoOnClick    ;
		bot          = ( TButton* )rTitulo->FindStyleResource( "bAbrir"     ); if ( bot        )   bot       ->OnClick = bAbrirOnClick    ;
		bGuardar     = ( TButton* )rTitulo->FindStyleResource( "bGuardar"   ); if ( bGuardar   ) { bGuardar  ->OnClick = bGuardarOnClick  ; bGuardar  ->Enabled = false; }

		bot          = ( TButton* )rTitulo->FindStyleResource( "bMicro"     ); if ( bot        )   bot       ->OnClick = bMicroOnClick    ;
		bControl     = ( TButton* )rTitulo->FindStyleResource( "bControl"   ); if ( bControl   )   bControl  ->OnClick = bControlOnClick  ;
		bError       = ( TButton* )rTitulo->FindStyleResource( "bError"     ); if ( bError     )   bError    ->OnClick = bErrorOnClick    ;
		bConsola     = ( TButton* )rTitulo->FindStyleResource( "bConsola"   ); if ( bConsola   )   bConsola  ->OnClick = bConsolaOnClick  ;

		bRefrescar   = ( TButton* )rTitulo->FindStyleResource( "bRefrescar" ); if ( bRefrescar ) { bRefrescar->OnClick = bRefrescarOnClick; bRefrescar->Enabled = false; }
		bViguilar    = ( TButton* )rTitulo->FindStyleResource( "bvigilar"   ); if ( bViguilar  ) { bViguilar->OnClick  = bVigilarOnClick  ; bViguilar ->Enabled = false; }
		bIniciar     = ( TButton* )rTitulo->FindStyleResource( "bIniciar"   ); if ( bIniciar   )   bIniciar  ->OnClick = bIniciarOnClick  ;
		bParar       = ( TButton* )rTitulo->FindStyleResource( "bParar"     ); if ( bParar     ) { bParar->OnClick     = bPararOnClick    ; bParar    ->Enabled = false; }

	//Titulos
		lArchivo     = ( TText*   )rTitulo->FindStyleResource( "archivo"    );
		lAsterisco   = ( TText*   )rTitulo->FindStyleResource( "asterisco"  );

	_Micro.Top  = this->Top ;
	_Micro.left = this->Left;
}
//---------------------------------------------------------------------------
void __fastcall Tf1_prin::rTituloMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  float X, float Y)
{
/**/
	bool abd = GetSystemMetrics( SM_SWAPBUTTON ) != 0;
	HWND han = GetActiveWindow();

	while ( ( !abd && GetAsyncKeyState( VK_LBUTTON ) != 0 ) || ( abd && GetAsyncKeyState( VK_RBUTTON ) != 0 ) ) {
		SendMessage( han, WM_LBUTTONUP    , 0        , 0 );
		SendMessage( han, WM_NCLBUTTONDOWN, HTCAPTION, 0 );
		Application->ProcessMessages();
	}
}
//---------------------------------------------------------------------------
