#ifndef GAME_HPP
#define GAME_HPP

#include "gamelibs.h"
#include "object.h"
#include "renderer.h"

class Game {
	public:
		Game();
		~Game();

		void init(char* _title, int _xpos, int _ypos, int _width, int _height, bool _fullscreen);
		void input();
		void update();
		void render();
		void clean();
		
		bool running(){return isRunning;}
	private : 
		bool isRunning;
		Renderer* renderer;
		Object* controlObject;
};
#endif
