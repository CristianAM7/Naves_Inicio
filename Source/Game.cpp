#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"
#include <SDL.h>

CGame::CGame(){
	tiempoFrameInicial = 0;
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

	nave = new Nave(screen,"../Data/minave.bmp",(WIDTH_SCREEN/2),(HEIGHT_SCREEN-80),MODULO_MINAVE_NAVE);
	menu = new Nave(screen,"../Data/menufondo.bmp",0,0,MODULO_MENUFONDO_FONDO);
	textos = new Nave(screen,"../Data/menutexto.bmp",0,0,MODULO_MENUTEXTO_TITULO);
	fondo = new Nave(screen,"../Data/juegofondo.bmp",0,0,1);
	for(int i=0;i<10;i++){
		enemigoArreglo[i] = new Nave(screen,"../Data/enemigo.bmp",i*60,0,MODULO_ENEMIGO_NAVE);
		enemigoArreglo[i]->SetAutoMovimiento(false);
		enemigoArreglo[i]->SetPasoLimite(4);
	}
	tick=0;
	opcionSeleccionada = MODULO_MENUTEXTO_OPCION1;
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
			menu->Pintar();
			textos->Pintar(MODULO_MENUTEXTO_TITULO,151,48);
			textos->Pintar(MODULO_MENUTEXTO_NOMBRE,327,440);
			Menu();
			//estado = ESTADO_JUGANDO;
			break;
		case Estado::ESTADO_JUGANDO:
			for(int i=0;i<10;i++){
				enemigoArreglo[i]->Actualizar();
			}
			MoverEnemigo();
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));
			fondo->Pintar();
			keys = SDL_GetKeyState(NULL);
			if(keys[SDLK_RIGHT]){
				if(!EsLimitePantalla(nave, BORDE_DERECHO))
					nave->MoverX(10);
			}
			if(keys[SDLK_LEFT]){
				nave->MoverX(-10);
			}
			if(keys[SDLK_DOWN]){
				if(!EsLimitePantalla(nave, BORDE_DERECHO))
					nave->MoverY(10);
			}
			if(keys[SDLK_UP]){
				nave->MoverY(-10);
			}
			nave->Pintar();
			for(int i=0;i<10;i++)
				enemigoArreglo[i]->Pintar();
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

		//Calculando FPS
		tiempoFrameFinal = SDL_GetTicks();
		while(tiempoFrameFinal < (tiempoFrameInicial + FPS_DELAY)){
			tiempoFrameFinal=SDL_GetTicks();
			SDL_Delay(1);
		}
		printf("Frames:%d Tiempo:%d Tiempo Promedio:%f Tiempo por Frame:%d FPS:%f\n",tick,SDL_GetTicks(), (float)SDL_GetTicks()/(float)tick, tiempoFrameFinal - tiempoFrameInicial, 1000.0f / (float)(tiempoFrameFinal - tiempoFrameInicial));
		tiempoFrameInicial = tiempoFrameFinal; //Marcamos el inicio nuevamente.
		tick++;
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
				enemigoArreglo[i]->MoverX(10);//Derecha
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
				enemigoArreglo[i]->MoverX(-10);//Izquierda
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

void CGame::Menu(){
	for (int i = MODULO_MENUTEXTO_OPCION1, j = 0; i <= MODULO_MENUTEXTO_OPCION2; i++, j++){
		if(i == opcionSeleccionada)
			textos->Pintar(i+2,260,160+(j*40));
		else
			textos->Pintar(i,260,162+(j*40));
	}
}