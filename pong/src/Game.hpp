#ifndef GAME_H
#define GAME_H

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

};
#endif
