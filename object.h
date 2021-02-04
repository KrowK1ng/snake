#ifndef OBJECT_H
#define OBJECT_H
#include "sprite.h"
#include "gamelibs.h"

class Object{
	
	public:
		Object(int _x, int _y, SDL_Renderer* _ren);
		void AddSprite(SDL_Renderer* _ren, const char* _source, int _w, int _h, int _x, int _y, int _xoff, int _yoff);
		virtual void Start();
		virtual int Step();
		void Input();
		virtual void Draw();
		int GetDir(int _x, int _y, int _val);
		bool IsValid(int _x, int _y);
		void ChangeDir(int _dir);
		void SpawnApple();

		int x, y;
		int timer, speed;
		int table[20][20];
		int length, direction;
		int xpos, ypos;
		SDL_Renderer* ren;
		Sprite* sprite = nullptr; 
		Sprite* HeadSprite = nullptr;
		Sprite* TailSprite = nullptr;
		Sprite* BackSprite = nullptr;
		Sprite* MiddleSprite = nullptr;
		Sprite* JointSprite = nullptr;
		Sprite* AppleSprite = nullptr;

};

#endif
