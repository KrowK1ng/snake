#include "object.h"

Object::Object(int _x, int _y, SDL_Renderer* _ren){
	x = _x;
	y = _y;
	ren = _ren;
	Start();
}

void Object::AddSprite(SDL_Renderer* _ren, const char* _source, int _w, int _h, int _x, int _y, int _xoff, int _yoff){
	sprite = new Sprite(_ren, _source, _w, _h, _x, _y, _xoff, _yoff);
}

void Object::Start(){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			table[i][j] = 0;
		}	
	}

	table[8][10] = 4;
	table[9][10] = 3;
	table[10][10] = 2;

	length = 3;
	direction = 1;
	xpos = 10;
	ypos = 10;

	HeadSprite = new Sprite(ren, "assets/spritesheet.png", 16, 16, 0, 0, 0 ,0);
	TailSprite = new Sprite(ren, "assets/spritesheet.png", 16, 16, 16, 16, 0 ,0);
	BackSprite = new Sprite(ren, "assets/spritesheet.png", 16, 16, 32, 0, 0 ,0);
	AppleSprite = new Sprite(ren, "assets/spritesheet.png", 16, 16, 32, 16, 0 ,0);
	JointSprite = new Sprite(ren, "assets/spritesheet.png", 16, 16, 16, 0, 0 ,0);
	MiddleSprite = new Sprite(ren, "assets/spritesheet.png", 16, 16, 0, 16, 0 ,0);
	speed = 5;
	timer = speed;

	SpawnApple();
}

int Object::Step(){

	if (timer > 0){
		timer--;
		return 0;
	}else{
		timer = speed;
	}

	// Move next
	xpos -= (direction % 2) * (direction - 2);
	ypos += ((direction + 1) % 2 ) * (direction - 1);
	
	if(xpos < 0 || xpos > 19 || ypos < 0 || ypos > 19)
		return 1;

	if(table[xpos][ypos] > 1 && table[xpos][ypos] < length + 1)
		return 1;

	if(table[xpos][ypos] == 1){
		length++;
		if(256 - length)
			SpawnApple();
	}

	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			if(table[i][j] > 1){
				table[i][j]++;
			}
			if(table[i][j] == length + 2){
				table[i][j] = 0;
			}
		}	
	}

	table[xpos][ypos] = 2;

	return 0;
}

bool Object::IsValid(int _x, int _y){
	if(_x < 0 || _x > 19 || _y < 0 || _y > 19)
		return false;
	return true;
}

void Object::SpawnApple(){
	srand(SDL_GetTicks());
	
	int place = rand() % (255 - length) + 1;

	for(int i = 0;i < 20; i++){
		for (int j = 0; j < 20; j++) {
			if(!table[i][j])
				place--;
			if(!place){
				table[i][j] = 1;
				return;
			}
		}
	}
}

int Object::GetDir(int _x, int _y, int _val){
	int tempdir = 0;
	int tempx, tempy;
	for(; tempdir < 4; tempdir++){
		tempx = _x - (tempdir % 2) * (tempdir - 2);
		tempy = _y + ((tempdir + 1) % 2 ) * (tempdir - 1);
		if(IsValid(tempx, tempy) && table[tempx][tempy] == _val)
			return tempdir;
	}
	return 4;

}

void Object::ChangeDir(int _dir){
	if (_dir == GetDir(xpos, ypos, 3))
		return;
	
	direction = _dir;
}

void Object::Draw(){
	int _dir1, _dir2;
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			BackSprite->Render(ren, i * 32, j * 32);
			if(table[i][j] > 1){
				if(table[i][j] == 2){
					_dir1 = GetDir(i,j, 3);
					HeadSprite->RenderExt(ren, i * 32, j * 32, 90 * ((_dir1 + 2) % 4));
				}else if(table[i][j] == length + 1){
					_dir1 = GetDir(i,j, length);
					TailSprite->RenderExt(ren, i * 32, j * 32, 90 * _dir1);
				}else{
					_dir1 = GetDir(i,j, table[i][j] + 1);
					_dir2 = GetDir(i,j, table[i][j] - 1);
					if (abs(_dir1 - _dir2) == 2){
						MiddleSprite->RenderExt(ren, i * 32, j * 32, 90 * (_dir1 % 2));
					}else {
						if((_dir1 > _dir2 && (_dir2 || _dir1 != 3 )) || (_dir1 == 0 && _dir2 == 3)){
							JointSprite->RenderExt(ren, i * 32, j * 32, 90 * _dir2);
						}else {
							JointSprite->RenderExt(ren, i * 32, j * 32, 90 * _dir1);
						}
					}
				}
			}else if(table[i][j]){
				AppleSprite->Render(ren, i * 32, j * 32);
			} 
		}	
	}
	
}
