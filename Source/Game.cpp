#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"
#include <SDL.h>

CGame::CGame(){
<<<<<<< HEAD
	estado=ESTADO_INICIANDO; ///ACT2: Mal, debes de usar tu variable estado que creaste en el Game.h y alguna de las banderas del enum, que indicaran el estado inicial del juego.
	
=======
	Estado::ESTADO_INICIANDO; 
	atexit(SDL_Quit);
>>>>>>> 04a24772a425749c83f6b46d1b6519a18ae5ede7
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

		nave = new Sprite(screen);
		nave->CargarImagen("../Data/minave.bmp");

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
			//nave->PintarModulo(0, 0, 0, 64, 64);
			nave->PintarModulo(0,100,100);
			break;
		case Estado::ESTADO_JUGANDO:
			break;
		case Estado::ESTADO_TERMINANDO:
			break;
		case Estado::ESTADO_FINALIZANDO:
			salirJuego = true;
			Finalize();
			break;
<<<<<<< HEAD
		}
	/*if (SDL_Init( SDL_INIT_VIDEO )){
=======
			///////////ACT3: Mal, esta seccion debe estar en un metodo llamado inicio///////
	if (SDL_Init( SDL_INIT_VIDEO )){
>>>>>>> 04a24772a425749c83f6b46d1b6519a18ae5ede7

printf("Error %s ", SDL_GetError());

exit(EXIT_FAILURE);

}

screen = SDL_SetVideoMode( 640, 480, 24, SDL_SWSURFACE );
		};
		if (screen == NULL){

printf("Error %s ", SDL_GetError());

exit(EXIT_FAILURE);

}
*/
SDL_WM_SetCaption( "Mi primer Juego", NULL );
///////ACT3: Mal, aqui termina el codigo mal.

//Este codigo estara provicionalmente aqui.
SDL_Flip(screen);
}
	return true;
	}
