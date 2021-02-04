#include "sprite.h"

Sprite::Sprite(SDL_Renderer* _ren, const char* _source, int _w, int _h, int _x, int _y, int _xoff, int _yoff) {
	sRect = new SDL_Rect();
	dRect = new SDL_Rect();
	offset = new SDL_Point();
	sRect->x = _x;
	sRect->y = _y;
	sRect->w = _w;
	sRect->h = _h;
	texture = TextureManager::LoadTexture(_source, _ren);
	offset->x = _xoff;
	offset->y = _yoff;
	dRect->w = 2 * sRect->w;
	dRect->h = 2 * sRect->h;
	dRect->x = 0;
	dRect->y = 0;
}

void Sprite::Render(SDL_Renderer* _ren, int _x, int _y){
	dRect->x = _x;
	dRect->y = _y;
	SDL_RenderCopy(_ren, texture, sRect, dRect);
}

void Sprite::RenderExt(SDL_Renderer* _ren, int _x, int _y, double _angle){
	dRect->x = _x;
	dRect->y = _y;
	SDL_Point* temp;
	temp = new SDL_Point();
	temp->x = dRect->h / 2;
	temp->y = dRect->h / 2;
	SDL_RenderCopyEx(_ren, texture, sRect, dRect, _angle, temp, SDL_FLIP_NONE);
}
