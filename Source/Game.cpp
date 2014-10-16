#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"
#include <SDL.h>

CGame::CGame(){
	estado=ESTADO_INICIANDO;
	
	Estado::ESTADO_INICIANDO; 
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
		if (screen == NULL)
		{
			printf("Error %s ", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		SDL_WM_SetCaption( "Mi primer Juego", NULL );
		atexit(SDL_Quit);
		nave = new Nave(screen,"../Data/minave.bmp",(WIDTH_SCREEN/2)/*-(sprite->WidthModule(0)/2)*/,(HEIGHT_SCREEN-80)/*-(sprite->HeightModule(0))*/);
		enemigo = new Nave(screen,"../Data/enemigo.bmp",0,0);
		enemigo->SetAutoMovimiento(true);
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
			printf("\n1. ESTADO_INICIANDO");
			Iniciando();
			estado = ESTADO_MENU;
			break;
		case Estado::ESTADO_MENU:
			enemigo->Actualizar();
			printf("\n2. ESTADO_MENU");
			//nave->PintarModulo(1,0,0);*/
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,250,280,280));
			keys = SDL_GetKeyState(NULL);
			if(keys[SDLK_RIGHT]){
				nave->Mover(1);
			}
			if(keys[SDLK_LEFT]){
				nave->Mover(-1);
			}
			nave->Pintar();
			enemigo->Pintar();
			break;
		case Estado::ESTADO_JUGANDO:
			printf("\n3. ESTADO_JUGANDO");
			break;
		case Estado::ESTADO_TERMINANDO:
			printf("\n4. ESTADO_TERMINANDO");
			break;
		case Estado::ESTADO_FINALIZANDO:
			printf("\n5. ESTADO_FINALIZANDO");
			salirJuego = true;
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
