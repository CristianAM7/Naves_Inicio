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

	Uint8 * keys;
	SDL_Event event;

	SDL_Surface * screen;
	Nave * nave;
	Nave * enemigo;
	Estado estado; 
};