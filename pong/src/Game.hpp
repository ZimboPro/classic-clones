#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include "screens/Screen.hpp"

class Game
{
	private:

	public:

		Game();
		~Game();

		void init();
    void clear();
		void render();
    void clean();
    bool isRunning();

    static GameScreen currentScreen;
    static Font font;
    static Music music;
    static Sound fxCoin;

};
#endif
