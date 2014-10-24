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
			//system("cls");
			/*printf("\n1. ESTADO_INICIANDO");
			printf("\n2. ESTADO_MENU");
			printf("\n3. ESTADO_JUGANDO");
			printf("\n4. ESTADO_TERMINANDO");
			printf("\n2. ESTADO_MENU");
			printf("\n5. ESTADO_FINALIZANDO");
			scanf("%d",&estado);*/
			Iniciando();
			estado = ESTADO_MENU;
			//getchar();
			break;
		case Estado::ESTADO_MENU:
			enemigo->Actualizar();
			/*system("cls");
			printf("\n2. ESTADO_MENU");*/
			//nave->PintarModulo(1,0,0);
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));
			keys = SDL_GetKeyState(NULL);
			if(keys[SDLK_RIGHT]){
				if(!EsLimitePantalla(nave))
					nave->Mover(1);
			}
			if(keys[SDLK_LEFT]){
				nave->Mover(-1);
			}
			nave->Pintar();
			enemigo->Pintar();
			//getchar();
			break;
		case Estado::ESTADO_JUGANDO:
			/*system("cls");
			printf("\n3. ESTADO_JUGANDO");
			getchar();*/
			break;
		case Estado::ESTADO_TERMINANDO:
			/*system("cls");
			printf("\n4. ESTADO_TERMINANDO");
			getchar();*/
			break;
		case Estado::ESTADO_FINALIZANDO:
			/*system("cls");
			printf("\n5. ESTADO_FINALIZANDO");
			getchar();*/
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
	if(objeto->ObtenerX() <= 0)
		return true;
	if(objeto->ObtenerY() <= 0)
		return true;
	if(objeto->ObtenerX() >= WIDTH_SCREEN - objeto->ObtenerW())
		return true;
	if(objeto->ObtenerY() >= HEIGHT_SCREEN - objeto->ObtenerH())
		return true;
	return false;
}
