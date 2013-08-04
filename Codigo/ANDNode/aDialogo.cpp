//---------------------------------------------------------------------------
#pragma hdrstop

//###########################################################################
#include "aDialogo.h"
//###########################################################################

#pragma package(smart_init)
//---------------------------------------------------------------------------


//private ###################################################################
//---------------------------------------------------------------------------
//Almacenados
bool __fastcall aDialogo::ATodosLosFormatos()
{
/**/
	return _TodosLosFormatos != "Todos los Formatos";
}
//---------------------------------------------------------------------------
bool __fastcall aDialogo::ATodosLosArchivos()
{
/**/
	return _TodosLosArchivos != "Todos los Archivos";
}
//---------------------------------------------------------------------------
bool __fastcall aDialogo::AOpcionesDialogo()
{
/**/
	scOpcionesDialogo op;
	op.Clear();
	op = op << odForsarExtencion;

	return _OpcionesDialogo != op;
}
//---------------------------------------------------------------------------

//Metodos
HRESULT __fastcall aDialogo::CargarFiltro( IFileDialog *Dialogo, String val )
{
/**/
	if ( !Dialogo ) return NULL;

	int num = 0;

	while ( val.Pos( "d" + String( num + 1 ) ) && val.Pos( "t" + String( num + 1 ) ) ) num++;

	if ( _TipoDialogo != tdGuardar ) {
		//Todos los Formatos
		if ( _TodosLosFormatos != "" && num > 1 ) {
			int n = 0;
			String tem = "";

			while ( val.Pos( "t" + ( String )++n ) ) {
				if ( tem != "" ) tem += ";";
				tem += GetEtiqueta( "t" + ( String )n, val );
			}

			num++;
			SetEtiqueta( "d" + ( String )num, val, _TodosLosFormatos );
			SetEtiqueta( "t" + ( String )num, val, tem               );
		}

		//Todos los Archivos
		if ( _TodosLosArchivos != "" && num > 0 ) {
			num++;
			SetEtiqueta( "d" + ( String )num, val, _TodosLosArchivos );
			SetEtiqueta( "t" + ( String )num, val, "*.*"             );
		}
    }

	String* d = new String[ num ];
	String* t = new String[ num ];
	COMDLG_FILTERSPEC* FilTip = new COMDLG_FILTERSPEC[ num ];

	SecureZeroMemory( d     , sizeof( d      ) );
	SecureZeroMemory( t     , sizeof( t      ) );
	SecureZeroMemory( FilTip, sizeof( FilTip ) );

	for ( int i = 0; i < num; i++ ) {
		d[ i ] = GetEtiqueta( "d" + String( i + 1 ), val );
		t[ i ] = GetEtiqueta( "t" + String( i + 1 ), val );

		FilTip[ i ].pszName = d[ i ].w_str();
		FilTip[ i ].pszSpec = t[ i ].w_str();
	}

	delete[] d;
	delete[] t;

	return Dialogo->SetFileTypes( num, FilTip );
}
//---------------------------------------------------------------------------
HRESULT __fastcall aDialogo::CargarOpciones( IFileDialog *Dialogo, scOpcionesDialogo val )
{
/**/
	if ( !Dialogo ) return NULL;

	FILEOPENDIALOGOPTIONS FilOps = 0;

	if ( val.Contains( odSobrescribirArchivo    ) ) FilOps |= FOS_OVERWRITEPROMPT   ;
	if ( val.Contains( odEstrictoTipos          ) ) FilOps |= FOS_STRICTFILETYPES   ;
	if ( val.Contains( odNoCargarDir            ) ) FilOps |= FOS_NOCHANGEDIR       ;
	if ( val.Contains( odSeleccionarCarpetas    ) ) FilOps |= FOS_PICKFOLDERS       ;
	if ( val.Contains( odVerArchivosSystema     ) ) FilOps |= FOS_FORCEFILESYSTEM   ;
	if ( val.Contains( odSeleccionarTodosShell  ) ) FilOps |= FOS_ALLNONSTORAGEITEMS;
	if ( val.Contains( odNoValidar              ) ) FilOps |= FOS_NOVALIDATE        ;
	if ( val.Contains( odMultiSeleccion         ) ) FilOps |= FOS_ALLOWMULTISELECT  ;
	if ( val.Contains( odCarpetaDebeExistir     ) ) FilOps |= FOS_PATHMUSTEXIST     ;
	if ( val.Contains( odArchivoDebeExistir     ) ) FilOps |= FOS_FILEMUSTEXIST     ;
	if ( val.Contains( odPreguntarCrear         ) ) FilOps |= FOS_CREATEPROMPT      ;
	if ( val.Contains( odShareAware             ) ) FilOps |= FOS_SHAREAWARE        ;
	if ( val.Contains( odNoDevolverSoloLectura  ) ) FilOps |= FOS_NOREADONLYRETURN  ;
	if ( val.Contains( odNoEstrictoEnCreacion   ) ) FilOps |= FOS_NOTESTFILECREATE  ;
	if ( val.Contains( odOcultarListaRecientes  ) ) FilOps |= FOS_HIDEMRUPLACES     ;
	if ( val.Contains( odOcultarPaneles         ) ) FilOps |= FOS_HIDEPINNEDPLACES  ;
	if ( val.Contains( odNoReferenciaDeLNK      ) ) FilOps |= FOS_NODEREFERENCELINKS;
	if ( val.Contains( odNoAgregarRecientes     ) ) FilOps |= FOS_DONTADDTORECENT   ;
	if ( val.Contains( odMostrarArchivosOcultos ) ) FilOps |= FOS_FORCESHOWHIDDEN   ;
	if ( val.Contains( odDefaultNoModoMini      ) ) FilOps |= FOS_DEFAULTNOMINIMODE ;
	if ( val.Contains( odVerPanelVistaPrevia    ) ) FilOps |= FOS_FORCEPREVIEWPANEON;

	return Dialogo->SetOptions( FilOps );
}
//---------------------------------------------------------------------------
HRESULT __fastcall aDialogo::CargarCarpetaDefault( IFileDialog *Dialogo, String val )
{
/**/
//	if ( !Dialogo ) return NULL;
//
//	IShellItem* DefDir;
//	HRESULT hr = SHCreateItemFromParsingName( val.w_str(), NULL, IID_PPV_ARGS( &DefDir ) );
//
//	if ( SUCCEEDED( hr ) )
//		hr = Dialogo->SetDefaultFolder( DefDir );
//
//	DefDir->Release();
//	return hr;
	return 0;
}
//---------------------------------------------------------------------------
HRESULT __fastcall aDialogo::DevolverRutas( IFileOpenDialog *Dialogo, TStringList *Rutas, String &Ruta )
{
/**/
	if ( !Dialogo ) return NULL;

	Ruta = "";
	Rutas->Clear();
	IShellItemArray* ArrRut = NULL;

	HRESULT hr = Dialogo->GetResults( &ArrRut );

	if ( SUCCEEDED( hr ) ) {
		DWORD NumRut;
		hr = ArrRut->GetCount( &NumRut );

		if ( SUCCEEDED( hr ) ) {
			for ( DWORD i = 0; i < NumRut; i++ ) {
				IShellItem *psi = NULL;
				hr = ArrRut->GetItemAt( i, &psi );

				if ( SUCCEEDED( hr ) ) {
					PWSTR sRuta = NULL;
					hr = psi->GetDisplayName( SIGDN_FILESYSPATH, &sRuta );

					if ( SUCCEEDED( hr ) ) {
						Rutas->Add( ( String )sRuta );
					}

					psi->Release();
				}
			}

			if ( Rutas->Count )
				Ruta = Rutas->Strings[ 0 ];
		}
	}

	ArrRut->Release();
	return hr;
}
//---------------------------------------------------------------------------

bool __fastcall aDialogo::EjecutarOP7( HWND Padre )
{
/**/
	bool reg = false;
	_TipoDialogo = tdAbrir;

	IFileOpenDialog *Dialogo;
	HRESULT hr = CoCreateInstance( CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &Dialogo ) );

	//Titulo
	if ( SUCCEEDED( hr ) ) {
		hr = Dialogo->SetTitle( _Titulo.w_str() );

		//Filtro
		if ( SUCCEEDED( hr ) ) {
			hr = CargarFiltro( Dialogo, _Filtro );

			//Indice Filtro
			if ( SUCCEEDED( hr ) ) {
				if ( _Filtro != "" && _IndiceExtencion > -1 )
					hr = Dialogo->SetFileTypeIndex( _IndiceExtencion );

				//Opciones
				if ( SUCCEEDED( hr ) ) {
					hr = CargarOpciones( Dialogo, _OpcionesDialogo );

					//Ruta
					if ( SUCCEEDED( hr ) ) {
						hr = Dialogo->SetFileName( _Ruta.w_str() );

						//Carpeta Default
						if ( SUCCEEDED( hr ) ) {
							hr = CargarCarpetaDefault( Dialogo, _Carpeta );

							//Mostrar Dialogo
							if ( SUCCEEDED( hr ) ) {
								hr = Dialogo->Show( Padre );

								//Ruta Regreso
								if ( SUCCEEDED( hr ) ) {
									hr = DevolverRutas( Dialogo, _Rutas, _Ruta );

									if ( SUCCEEDED( hr ) ) {
										unsigned int ind;
										hr = Dialogo->GetFileTypeIndex( &ind );

										if ( SUCCEEDED( hr ) ) {
											_IndiceExtencion = ind;
											_Extencion       = GetEtiqueta  ( "t" + ( String )ind, _Filtro );
											_Extencion       = StringReplace( _Extencion, "*", "", TReplaceFlags() << rfReplaceAll );
										}

										reg = true;
									}
								}
							}
						}
					}
				}
            }
        }
    }

	Dialogo->Release();
	return reg;
}
//---------------------------------------------------------------------------
bool __fastcall aDialogo::EjecutarSA7( HWND Padre )
{
/**/
	bool reg = false;
	_TipoDialogo = tdGuardar;

	IFileSaveDialog *Dialogo;
	HRESULT hr = CoCreateInstance( CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &Dialogo ) );

	//Titulo
	if ( SUCCEEDED( hr ) ) {
		hr = Dialogo->SetTitle( _Titulo.w_str() );

		//Filtro
		if ( SUCCEEDED( hr ) ) {
			hr = CargarFiltro( Dialogo, _Filtro );

			//Indice Filtro
			if ( SUCCEEDED( hr ) ) {
				if ( _IndiceExtencion > -1 ) hr = Dialogo->SetFileTypeIndex( _IndiceExtencion );

				//Opciones
				if ( SUCCEEDED( hr ) ) {
					hr = CargarOpciones( Dialogo, _OpcionesDialogo );

					//Ruta
					if ( SUCCEEDED( hr ) ) {
						hr = Dialogo->SetFileName( _Ruta.w_str() );

						//Carpeta Default
						if ( SUCCEEDED( hr ) ) {
							hr = CargarCarpetaDefault( Dialogo, _Carpeta );

							//Mostrar Dialogo
							if ( SUCCEEDED( hr ) ) {
								hr = Dialogo->Show( Padre );

								if ( SUCCEEDED( hr ) ) {
									IShellItem *psr;
									hr = Dialogo->GetResult( &psr );

									if ( SUCCEEDED( hr ) ) {
										PWSTR FilPat = NULL;
										hr = psr->GetDisplayName( SIGDN_FILESYSPATH, &FilPat );

										if ( SUCCEEDED( hr ) ) {
											_Ruta = ( String )FilPat;

											unsigned int ind;
											hr = Dialogo->GetFileTypeIndex( &ind );

											if ( SUCCEEDED( hr ) ) {
												_IndiceExtencion = ind;
												_Extencion       = GetEtiqueta( "t" + ( String )ind, _Filtro );
												_Extencion       = StringReplace( _Extencion, "*", "", TReplaceFlags() << rfReplaceAll );

												if ( _OpcionesDialogo.Contains( odForsarExtencion ) && ExtractFileExt( _Ruta ).LowerCase() != _Extencion.LowerCase() )
													_Ruta += _Extencion;
											}

											reg = true;
										}

										psr->Release();
									}
								}
							}
						}
					}
				}
            }
        }
    }

	Dialogo->Release();
	return reg;
}
//---------------------------------------------------------------------------
bool __fastcall aDialogo::EjecutarDI7( HWND Padre )
{
/**/
	bool reg = false;
	_TipoDialogo = tdDirectorio;

	IFileDialog *Dialogo;
	HRESULT hr = CoCreateInstance( CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &Dialogo ) );

	//Titulo
	if ( SUCCEEDED( hr ) ) {
		hr = Dialogo->SetTitle( _Titulo.w_str() );

		//Opciones
		if ( SUCCEEDED( hr ) ) {
			hr = CargarOpciones( Dialogo, _OpcionesDialogo << odSeleccionarCarpetas );

			//Carpeta
			if ( SUCCEEDED( hr ) ) {
				hr = Dialogo->SetFileName( _Ruta.w_str() );

				//Carpeta Default
				if ( SUCCEEDED( hr ) ) {
					hr = CargarCarpetaDefault( Dialogo, _Carpeta );

					//Mostrar Dialogo
					if ( SUCCEEDED( hr ) ) {
						hr = Dialogo->Show( Padre );

						if ( SUCCEEDED( hr ) ) {
							IShellItem *psr;
							hr = Dialogo->GetResult( &psr );

							if ( SUCCEEDED( hr ) ) {
								PWSTR FilPat = NULL;
								hr = psr->GetDisplayName( SIGDN_FILESYSPATH, &FilPat );

								if ( SUCCEEDED( hr ) ) {
									_Ruta = ( String )FilPat;
									reg = true;
								}

								psr->Release();
							}
						}
					}
				}
			}
		}
	}

	Dialogo->Release();
	return reg;
}
//---------------------------------------------------------------------------

String __fastcall aDialogo::CargarFiltro( String val )
{
/**/
	int num = 0;

	while ( val.Pos( "d" + String( num + 1 ) ) && val.Pos( "t" + String( num + 1 ) ) ) num++;

	if ( _TipoDialogo != tdGuardar ) {
		//Todos los Formatos
		if ( _TodosLosFormatos != "" && num > 1 ) {
			int n = 0;
			String tem = "";

			while ( val.Pos( "t" + ( String )++n ) ) {
				if ( tem != "" ) tem += ";";
				tem += GetEtiqueta( "t" + ( String )n, val );
			}

			num++;
			SetEtiqueta( "d" + ( String )num, val, _TodosLosFormatos );
			SetEtiqueta( "t" + ( String )num, val, tem               );
		}

		//Todos los Archivos
		if ( _TodosLosArchivos != "" && num > 0 ) {
			num++;
			SetEtiqueta( "d" + ( String )num, val, _TodosLosArchivos );
			SetEtiqueta( "t" + ( String )num, val, "*.*"             );
		}
	}

	//Filtros
	String fil = "";

	for ( int i = 0; i < num; i++ )
		fil += ( GetEtiqueta( "d" + String( i + 1 ), val ) + '\0' + GetEtiqueta( "t" + String( i + 1 ), val ) + '\0' );

	return fil;
}
//---------------------------------------------------------------------------
unsigned long __fastcall aDialogo::CargarOpciones( scOpcionesDialogo val )
{
/**/
	unsigned long FilOps = 0;

	if ( val.Contains( odSobrescribirArchivo    ) ) FilOps |= OFN_OVERWRITEPROMPT   ;
	if ( val.Contains( odEstrictoTipos          ) ) FilOps |= OFN_EXTENSIONDIFFERENT;
	if ( val.Contains( odNoCargarDir            ) ) FilOps |= OFN_NOCHANGEDIR       ;
//	if ( val.Contains( odSeleccionarCarpetas    ) ) FilOps |= ;
//	if ( val.Contains( odVerArchivosSystema     ) ) FilOps |= ;
//	if ( val.Contains( odSeleccionarTodosShell  ) ) FilOps |= ;
	if ( val.Contains( odNoValidar              ) ) FilOps |= OFN_NOVALIDATE        ;
	if ( val.Contains( odMultiSeleccion         ) ) FilOps |= OFN_ALLOWMULTISELECT | OFN_EXPLORER;
	if ( val.Contains( odCarpetaDebeExistir     ) ) FilOps |= OFN_PATHMUSTEXIST     ;
	if ( val.Contains( odArchivoDebeExistir     ) ) FilOps |= OFN_FILEMUSTEXIST     ;
	if ( val.Contains( odPreguntarCrear         ) ) FilOps |= OFN_CREATEPROMPT      ;
	if ( val.Contains( odShareAware             ) ) FilOps |= OFN_SHAREAWARE        ;
	if ( val.Contains( odNoDevolverSoloLectura  ) ) FilOps |= OFN_READONLY          ;
	if ( val.Contains( odNoEstrictoEnCreacion   ) ) FilOps |= OFN_NOTESTFILECREATE  ;
//	if ( val.Contains( odOcultarListaRecientes  ) ) FilOps |= ;
//	if ( val.Contains( odOcultarPaneles         ) ) FilOps |= ;
	if ( val.Contains( odNoReferenciaDeLNK      ) ) FilOps |= OFN_NODEREFERENCELINKS;
	if ( val.Contains( odNoAgregarRecientes     ) ) FilOps |= OFN_DONTADDTORECENT   ;
	if ( val.Contains( odMostrarArchivosOcultos ) ) FilOps |= OFN_FORCESHOWHIDDEN   ;
	if ( val.Contains( odDefaultNoModoMini      ) ) FilOps |= OFN_ENABLESIZING      ;
//	if ( val.Contains( odVerPanelVistaPrevia    ) ) FilOps |= ;

	return FilOps;
}
//---------------------------------------------------------------------------

bool __fastcall aDialogo::EjecutarOPXP( HWND Padre )
{
/**/
	_TipoDialogo = tdAbrir;

	bool reg = false;
	wchar_t cad[ MAX_PATH ];

	OPENFILENAME ofn;

	ZeroMemory( &ofn, sizeof( ofn ) );
	ZeroMemory( &cad, sizeof( cad ) );

	wcsncat( cad, _Ruta.w_str(), MAX_PATH );

	ofn.lStructSize     = sizeof( ofn );
	ofn.hwndOwner       = Padre;
	ofn.lpstrFilter     = CargarFiltro( _Filtro ).w_str();
	ofn.nFilterIndex    = _IndiceExtencion;
	ofn.lpstrFile       = cad;
	ofn.nMaxFile        = MAX_PATH;
	ofn.lpstrFileTitle  = NULL;
	ofn.nMaxFileTitle   = NULL;
	ofn.lpstrInitialDir = _Carpeta != "" ? _Carpeta.w_str() : NULL;
	ofn.lpstrTitle      = _Titulo  != "" ? _Titulo.w_str()  : NULL;
	ofn.Flags           = CargarOpciones( _OpcionesDialogo );

	reg =  GetOpenFileName( &ofn );

	_Rutas->Clear();
	int len = wcslen( ofn.lpstrFile );

	if( ofn.lpstrFile[ len + 1 ] == 0 ) {
		_Ruta = ( String )ofn.lpstrFile;
		if ( reg ) _Rutas->Add( _Ruta );
	}
	else {
		_Ruta = ( String )ofn.lpstrFile;
		ofn.lpstrFile += len + 1;

		while( ofn.lpstrFile[ 0 ] ) {
			_Rutas->Add( ofn.lpstrFile );
			len = wcslen( ofn.lpstrFile );
			ofn.lpstrFile += len + 1;
		}
	}

	if ( reg && _Rutas->Count > 1 ) {
		for ( int i = 0; i < _Rutas->Count; i++ )
			_Rutas->Strings[ i ] = _Ruta + "\\" + _Rutas->Strings[ i ];
	}

	_IndiceExtencion = ofn.nFilterIndex                                        ;
	_Extencion       = GetEtiqueta( "t" + ( String )_IndiceExtencion, _Filtro );
	_Extencion       = StringReplace( _Extencion, "*", "", TReplaceFlags() << rfReplaceAll );
	_Carpeta         = ( String )ofn.lpstrInitialDir                           ;

	return reg;
}
//---------------------------------------------------------------------------
bool __fastcall aDialogo::EjecutarSAXP( HWND Padre )
{
/**/
	_TipoDialogo = tdGuardar;

	bool reg = false;
	wchar_t cad[ MAX_PATH ];

	OPENFILENAME ofn;

	ZeroMemory( &ofn, sizeof( ofn ) );
	ZeroMemory( &cad, sizeof( cad ) );

	wcsncat( cad, _Ruta.w_str(), MAX_PATH );

	ofn.lStructSize     = sizeof( ofn );
	ofn.hwndOwner       = Padre;
	ofn.lpstrFilter     = CargarFiltro( _Filtro ).w_str();
	ofn.nFilterIndex    = _IndiceExtencion;
	ofn.lpstrFile       = cad;
	ofn.nMaxFile        = MAX_PATH;
	ofn.lpstrFileTitle  = NULL;
	ofn.nMaxFileTitle   = NULL;
	ofn.lpstrInitialDir = _Carpeta != "" ? _Carpeta.w_str() : NULL;
	ofn.lpstrTitle      = _Titulo  != "" ? _Titulo.w_str()  : NULL;
	ofn.Flags           = CargarOpciones( _OpcionesDialogo );

	reg =  GetSaveFileName( &ofn );

	_IndiceExtencion = ofn.nFilterIndex                                        ;
	_Ruta            = ( String )ofn.lpstrFile                                 ;
	_Extencion       = GetEtiqueta( "t" + ( String )_IndiceExtencion, _Filtro );
	_Extencion       = StringReplace( _Extencion, "*", "", TReplaceFlags() << rfReplaceAll );
	_Carpeta         = ( String )ofn.lpstrInitialDir                           ;


	if ( _OpcionesDialogo.Contains( odForsarExtencion ) && ExtractFileExt( _Ruta ).LowerCase() != _Extencion.LowerCase() )
		_Ruta += _Extencion;

	return reg;
}
//---------------------------------------------------------------------------
bool __fastcall aDialogo::EjecutarDIXP( HWND Padre )
{
/**/
//	bool reg;
//	_TipoDialogo = tdDirectorio;
//
//	reg = SelectDirectory(
//		_Titulo,
//		_Carpeta.w_str(),
//		_Ruta,
//		TSelectDirExtOpts() << sdNewFolder << sdShowEdit << sdShowShares << sdNewUI << sdShowFiles << sdValidateDir,
//		FindControl( Padre != NULL ? Padre->Handle : NULL )
//	);
//
	return false;
}
//---------------------------------------------------------------------------

String __fastcall aDialogo::GetEtiqueta( String Etiqueta, String Todo )
{
/**/
	if ( !Todo.Pos( "[" + Etiqueta + "=" ) ) return "";

	Todo = Todo.SubString( Todo.Pos( "[" + Etiqueta + "=" ) + Etiqueta.Length( ) + 2, Todo.Length( ) );
	Todo = Todo.SubString( 1, Todo.Pos( "]" ) - 1 );

	return Todo;
}
//---------------------------------------------------------------------------
void __fastcall aDialogo::SetEtiqueta( String Etiqueta, String& Todo, String Valor )
{
/**/
	if ( !Todo.Pos( "[" + Etiqueta + "=" ) ) Todo += "[" + Etiqueta + "=" + Valor + "]";
	else {
		String TemVal = Todo.SubString( Todo.Pos( "[" + Etiqueta + "=" ) + Etiqueta.Length( ) + 2, Todo.Length( ) );
		TemVal = TemVal.SubString( 1, TemVal.Pos( "]" ) - 1 );
		Todo = StringReplace( Todo, "[" + Etiqueta + "=" + TemVal + "]", "[" + Etiqueta + "=" + Valor + "]", TReplaceFlags( ) );
	}
}
//---------------------------------------------------------------------------
//###########################################################################


//public ####################################################################
//---------------------------------------------------------------------------
//Creacion
__fastcall aDialogo::aDialogo(TComponent* Owner)
	: TComponent(Owner)
{
/**/
//private
	//Variables
	_IndiceExtencion  = -1       ;
	_Ruta             = ""       ;
	_Filtro           = ""       ;
	_Titulo           = ""       ;
	_Carpeta          = ""       ;
	_Extencion        = ""       ;
	_TodosLosFormatos = ""       ;
	_TodosLosArchivos = ""       ;
	_TipoDialogo      = tdNinguno;
	_OpcionesDialogo  = scOpcionesDialogo() << odForsarExtencion;

	//Punteros
	_Rutas = new TStringList;

//public
	//Variables
	EsWindows7 = CheckWin32Version( 6, 0 );
}
//---------------------------------------------------------------------------
__fastcall aDialogo::~aDialogo()
{
/**/
	delete _Rutas;
}
//---------------------------------------------------------------------------

//Metodos
void __fastcall aDialogo::Clonar( aDialogo *Dialogo )
{
/**/
//private
	//Variables
	_IndiceExtencion  = Dialogo->_IndiceExtencion ;
	_Ruta             = Dialogo->_Ruta            ;
	_Filtro           = Dialogo->_Filtro          ;
	_Titulo           = Dialogo->_Titulo          ;
	_Carpeta          = Dialogo->_Carpeta         ;
	_TodosLosFormatos = Dialogo->_TodosLosFormatos;
	_TodosLosArchivos = Dialogo->_TodosLosArchivos;
	_TipoDialogo      = Dialogo->_TipoDialogo     ;
	_OpcionesDialogo  = Dialogo->_OpcionesDialogo ;

//public
	//Variables
	EsWindows7 = Dialogo->EsWindows7;
	_Extencion = Dialogo->Extencion ;
}
//---------------------------------------------------------------------------

bool __fastcall aDialogo::Ejecutar( HWND Padre )
{
/**/
	switch ( _TipoDialogo ) {
		case tdAbrir:
			return EjecutarOP( Padre );

		case tdGuardar:
			return EjecutarSA( Padre );

		case tdDirectorio:
			return EjecutarDI( Padre );

		case tdNinguno:
			return false;
	}

	return false;
}
//---------------------------------------------------------------------------
bool __fastcall aDialogo::EjecutarOP( HWND Padre )
{
/**/
	if ( EsWindows7 ) return EjecutarOP7( Padre );
	else return EjecutarOPXP( Padre );
}
//---------------------------------------------------------------------------
bool __fastcall aDialogo::EjecutarSA( HWND Padre )
{
/**/
	if ( EsWindows7 ) return EjecutarSA7( Padre );
	else return EjecutarSAXP( Padre );
}
//---------------------------------------------------------------------------
bool __fastcall aDialogo::EjecutarDI( HWND Padre )
{
/**/
	if ( EsWindows7 ) return EjecutarDI7( Padre );
	else return EjecutarDIXP( Padre );
}
//---------------------------------------------------------------------------
//###########################################################################
