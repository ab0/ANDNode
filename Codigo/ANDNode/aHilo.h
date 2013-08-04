//---------------------------------------------------------------------------
#ifndef aHiloH
#define aHiloH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#define scHiloNumeroArreglos 20
//---------------------------------------------------------------------------
class PACKAGE aHilo : public TPersistent
{
private:
	//Variables
	HWND         _Handle;
	unsigned int _Timer ;

	//Punteros
	void *_Hilo  ;
	void *_HMutex;

	//Eventos
	void __fastcall __OnCancelar( TObject *val );
	void __fastcall __OnTerminar( TObject *val );

	//Entradas
	void __fastcall EMensaje( String val );

public:
	//Variavles
	bool    Cancelado                   ;
	HWND    SuperHandle                 ;
	String  Error                       ;
	String  IdHilo                      ;
	String  TagS[ scHiloNumeroArreglos ];
	double  TagD[ scHiloNumeroArreglos ];
	__int64 TagI[ scHiloNumeroArreglos ];

	//Punteros
	TObject *TagO[ scHiloNumeroArreglos ];

	//Eventos
	TNotifyEvent OnFuncion    ;
	TNotifyEvent OnSincronizar;
	TNotifyEvent OnCancelar   ;
	TNotifyEvent OnTerminar   ;

	//Creacion
	__fastcall aHilo();

	//Metodos
	void*__fastcall GetHilo  ();
	void*__fastcall GetHMutex();

	void __fastcall Resume();
	void __fastcall Pausar();
	void __fastcall Cancelar();
	void __fastcall Terminar();
	void __fastcall Sincronizar( TNotifyEvent FFuncion );

	void __fastcall EmpezarHilo();
};
//---------------------------------------------------------------------------
#endif




