#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"
#include <SDL.h>

CGame::CGame(){
	estado=ESTADO_INICIANDO;
	//atexit(SDL_Quit);
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
	delete nave;
	//delete(keys);
	delete * enemigoArreglo;
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
	for(int i=0;i<10;i++){
		enemigoArreglo[i] = new Nave(screen,"../Data/enemigo.bmp",i*60,0);
		enemigoArreglo[i]->SetAutoMovimiento(false);
		enemigoArreglo[i]->SetPasoLimite(4);
	}
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
			for(int i=0;i<10;i++){
				enemigoArreglo[i]->Actualizar();
			}
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
			for(int i=0;i<10;i++)
				enemigoArreglo[i]->Pintar();
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
		while(SDL_PollEvent(&event)) //Aqui SDL creara una lista de eventos ocurridos
		{
			if(event.type == SDL_QUIT) {salirJuego = true;} //Si se detecta una salida de SDL o...
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
	for(int i=0;i<10;i++){
		///PASO 0///
		if(enemigoArreglo[i]->ObtenerPasoActual()==0)
			if (!EsLimitePantalla(enemigoArreglo[i],BORDE_DERECHO))
				enemigoArreglo[i]->Mover(1);//Derecha
			else{
				enemigoArreglo[i]->IncrementarPasoActual();
				enemigoArreglo[i]->IncrementarPasoActual();
			}
			///PASO 1///
		//if(enemigoArreglo[i]->ObtenerPasoActual()==1)
		//	if (!EsLimitePantalla(enemigoArreglo[i],BORDE_INFERIOR))
		//		enemigoArreglo[i]->Mover(1);//Abajo
			///PASO 2///
		if(enemigoArreglo[i]->ObtenerPasoActual()==2)
			if (!EsLimitePantalla(enemigoArreglo[i],BORDE_IZQUIERDO))
				enemigoArreglo[i]->Mover(-1);//Izquierda
			else{
				enemigoArreglo[i]->IncrementarPasoActual();
				enemigoArreglo[i]->IncrementarPasoActual();
			}
			///PASO 3///
		//if(enemigoArreglo[i]->ObtenerPasoActual()==3)
		//	if (!EsLimitePantalla(enemigoArreglo[i],BORDE_INFERIOR))
		//		enemigoArreglo[i]->Mover(1);//Abajo
	}
}
