#pragma once;
#include "Nave.h"

class CGame
{
public:
	bool Start();
	static CGame instanceGame;

	enum Estado{
		ESTADO_INICIANDO,
		ESTADO_MENU,
		ESTADO_JUGANDO,
		ESTADO_TERMINANDO,
		ESTADO_FINALIZANDO
	};
	CGame();
	void Finalize();

private:
	void Iniciando();
	void Menu();
	void MoverEnemigo();
	bool EsLimitePantalla(Nave * objeto, int bandera);

	int opcionSeleccionada;
	Uint8 * keys; //Esta variable nos servira para ver si determinadas teclas estan o no pulsadas.
	SDL_Event event; //La variable event de tipo evento de SDL nos servira para monitorizar el teclado.

	SDL_Surface * screen;
	SDL_Surface * imagen;

	Nave * nave;
	Nave * enemigoArreglo [10];

	Nave * menu;//Fondo del Menu
	Nave * textos;//Textos del Menu
	Nave * fondo;//Fondo del Juego

	int tick;
	int tiempoFrameInicial;
	int tiempoFrameFinal;

	Estado estado; 
};