#include "SpriteDef.h"
#include "Config.h"

SpriteDef::SpriteDef(){
	modulos[0].id = MODULO_MINAVE_NAVE;
	modulos[0].x = 0;
	modulos[0].y = 0;
	modulos[0].w = 64;
	modulos[0].h = 64;

	modulos[1].id = MODULO_MENUFONDO_FONDO;
	modulos[1].x = 0;
	modulos[1].y = 0;
	modulos[1].w = WIDTH_SCREEN;
	modulos[1].h = HEIGHT_SCREEN;

	modulos[2].id = MODULO_ENEMIGO_NAVE;
	modulos[2].x = 0;
	modulos[2].y = 0;
	modulos[2].w = 54;
	modulos[2].h = 61;

	modulos[3].id = MODULO_MENUTEXTO_TITULO;
	modulos[3].x = 151;
	modulos[3].y = 48;
	modulos[3].w = 357;
	modulos[3].h = 37;

	modulos[4].id = MODULO_MENUTEXTO_NOMBRE;
	modulos[4].x = 327;
	modulos[4].y = 440;
	modulos[4].w = 307;
	modulos[4].h = 27;

	modulos[5].id = MODULO_MENUTEXTO_OPCION1;
	modulos[5].x = 260;
	modulos[5].y = 162;
	modulos[5].w = 129;
	modulos[5].h = 33;

	modulos[6].id = MODULO_MENUTEXTO_OPCION2;
	modulos[6].x = 260;
	modulos[6].y = 202;
	modulos[6].w = 97;
	modulos[6].h = 32;

	modulos[7].id = MODULO_MENUTEXTO_OPCION1SELECCIONADO;
	modulos[7].x = 390;
	modulos[7].y = 162;
	modulos[7].w = 129;
	modulos[7].h = 33;

	modulos[8].id = MODULO_MENUTEXTO_OPCION2SELECCIONADO;
	modulos[8].x = 388;
	modulos[8].y = 202;
	modulos[8].w = 97;
	modulos[8].h = 32;
}
