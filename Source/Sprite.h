#ifndef __SPRITE_H__
#define __SPRITE_H__
#include <SDL.h>
#include "SpriteDef.h"

class Sprite{
	SDL_Surface * imagen;
	SDL_Surface * screen;
	SpriteDef spriteDef;
public:
	Sprite(SDL_Surface * screen);
	~Sprite();
	void CargarImagen(char * nombre);
	void PintarModulo(int nombre, int x, int y, int w, int h);
	void PintarModulo(int nombre, int x, int y);
};
#endif 