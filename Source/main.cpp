#include "Game.h"
#include  <stdlib.h>
#include <SDL.h>
#include <Windows.h>
#include <iostream>
#include <mmsystem.h>
#include <fstream>
#include <conio.h>

using namespace std;
// La función principal del juego
int main(int argc, char *argv[]){
	CGame *navesGame = new CGame();//Crea un objeto usando apuntadores

	if(navesGame->Start())   
		navesGame->Finalize(); // Liberamos los recursos utilizados.
	
	//PlaySound("musicafondo.wav",NULL, SND_FILENAME|SND_ASYNC);
	////"C:\\Users\\Cristian\\Documents\\GitHub\\Naves_Inicio\\Data\\*/
	//system("PAUSE");
    return EXIT_SUCCESS;
}
