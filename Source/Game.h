#include "Sprite.h"

class CGame
{
public:
	bool Start();
	static CGame instanceGame;

	CGame();
	void Finalize();

	enum Estado{
		ESTADO_INICIANDO,
		ESTADO_MENU,
		ESTADO_JUGANDO,
		ESTADO_TERMINANDO,
		ESTADO_FINALIZANDO
	};

private:
<<<<<<< HEAD
	void Iniciando();
	SDL_Surface * screen;
	Sprite * nave;
=======
	void Iniciando();//ACT3: Mal, este es el metodo que debes de crear.
	SDL_Surface *screen;
>>>>>>> 04a24772a425749c83f6b46d1b6519a18ae5ede7
	Estado estado; 
};