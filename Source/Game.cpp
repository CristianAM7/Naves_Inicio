#include <stdio.h>
#include <stdlib.h>
#include "Game.h"

CGame::CGame(){
	int estado = 0;////ACT2: Mal, si te fijas en "Game.h" ya tienes esta variable dada de alta, ahora debes de darle el valor inicial, indica cual es tu primer estado.
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
}

bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;
          
	while (salirJuego == false){
            
		//Maquina de estados
		switch(estado){
		case Estado::ESTADO_INICIANDO:
			break;
		case Estado::ESTADO_MENU:
			break;
		case Estado::ESTADO_JUGANDO:
			break;
		case Estado::ESTADO_TERMINANDO:
			break;
		case Estado::ESTADO_FINALIZANDO:
				salirJuego = true;
			break;
		};
    }
	return true;
}
