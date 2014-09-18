
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
	Estado estado; ///ACT2: Esto esta MAL
	///Corregido, maestro.
=======
	int estado; ///ACT2: Esto esta MAL
>>>>>>> d656e19adfdff1e01012b3cc7dd2d000e9d90611
};