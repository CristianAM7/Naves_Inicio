#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"
#include <SDL.h>

CGame::CGame(){
	estado=ESTADO_INICIANDO;
	atexit(SDL_Quit);
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
	delete(nave);
	SDL_FreeSurface(screen);
	SDL_Quit();
}

void CGame::Iniciando(){
	if (SDL_Init( SDL_INIT_VIDEO )){
		printf("Error %s ", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	screen = SDL_SetVideoMode( WIDTH_SCREEN, HEIGHT_SCREEN, 24, SDL_HWSURFACE);
	if (screen == NULL){
		printf("Error %s ", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption( "Mi Primer Juego", NULL );
	atexit(SDL_Quit);

	nave = new Nave(screen,"../Data/minave.bmp",(WIDTH_SCREEN/2)/*-(sprite->WidthModule(0)/2)*/,(HEIGHT_SCREEN-80)/*-(sprite->HeightModule(0))*/);
	enemigo = new Nave(screen,"../Data/enemigo.bmp",0,0);
	enemigo->SetAutoMovimiento(false);
	enemigo->SetPasoLimite(4);
	//delete nave;
}

bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;

	while (salirJuego == false){  
		//Maquina de estados
		switch(estado){
		case Estado::ESTADO_INICIANDO:
			Iniciando();
			estado = ESTADO_MENU;
			break;
		case Estado::ESTADO_MENU:
			enemigo->Actualizar();
			MoverEnemigo();
			//enemigo->Actualizar();
			//nave->PintarModulo(1,0,0);
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));
			keys = SDL_GetKeyState(NULL);
			if(keys[SDLK_RIGHT]){
				if(!EsLimitePantalla(nave, BORDE_DERECHO))
					nave->Mover(1);
			}
			if(keys[SDLK_LEFT]){
				nave->Mover(-1);
			}
			nave->Pintar();
			enemigo->Pintar();
			break;
		case Estado::ESTADO_JUGANDO:
			break;
		case Estado::ESTADO_TERMINANDO:
			break;
		case Estado::ESTADO_FINALIZANDO:
			salirJuego = false;
			Finalize();
			break;
		}
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) {salirJuego = true;}
			if(event.type == SDL_KEYDOWN) {  }
		}

		//Este codigo estara provicionalmente aqui.
		SDL_Flip(screen);
	}
	return true;
}
bool CGame::EsLimitePantalla(Nave * objeto, int bandera){
	if(bandera & BORDE_IZQUIERDO)
		if(objeto->ObtenerX() <= 0)
			return true;
	if(bandera & BORDE_SUPERIOR)
		if(objeto->ObtenerY() <= 0)
			return true;
	if(bandera & BORDE_DERECHO)
		if(objeto->ObtenerX() >= WIDTH_SCREEN - objeto->ObtenerW())
			return true;
	if(bandera & BORDE_INFERIOR)
		if(objeto->ObtenerY() >= HEIGHT_SCREEN - objeto->ObtenerH())
			return true;
	return false;
}

void CGame::MoverEnemigo(){
	if(enemigo->ObtenerPasoActual()==0)
		if(!EsLimitePantalla(enemigo,BORDE_DERECHO))
			enemigo->Mover(1); //Derecha
		else
			enemigo->IncrementarPasoActual();
			enemigo->IncrementarPasoActual();
	//if(enemigo->ObtenerPasoActual()==1)
		//if(!EsLimitePantalla(enemigo,BORDE_INFERIOR))
			//enemigo->Mover(1); //Abajo
	if(enemigo->ObtenerPasoActual()==2)
		if(!EsLimitePantalla(enemigo,BORDE_IZQUIERDO))
			enemigo->Mover(-1);
		else{
			enemigo->IncrementarPasoActual();
			enemigo->IncrementarPasoActual();
		}
			//enemigo->Mover(1); //Izquierda
	//if(enemigo->ObtenerPasoActual()==3)
		//if(!EsLimitePantalla(enemigo,BORDE_INFERIOR))
			//enemigo->Mover(1); //Abajo
}
