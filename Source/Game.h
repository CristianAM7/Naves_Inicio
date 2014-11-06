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
	void MoverEnemigo();
	bool EsLimitePantalla(Nave * objeto, int bandera);

	Uint8 * keys; //Esta variable nos servira para ver si determinadas teclas esta o no pulsadas.
	SDL_Event event; //La variable event de tipo evento de SDL nos servira para monitorizar el teclado.

	SDL_Surface * screen;

	Nave * nave;
	Nave * enemigoArreglo [10];

	int tick;
	int tiempoFrame;

	Estado estado; 
};