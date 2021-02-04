#include "game.h"

Game::Game(){}
Game::~Game(){}

void Game::init(char* _title, int _xpos, int _ypos, int _width, int _height, bool _fullscreen){
	renderer = new Renderer();
	if(renderer->CreateWindow(_title, _xpos, _ypos, _width, _height, _fullscreen)){
		isRunning = true;
	}
	controlObject = new Object(0,0,renderer->GetRenderer());
}

void Game::input(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_UP:
						controlObject->ChangeDir(0);
						break;
					case SDLK_RIGHT:
						controlObject->ChangeDir(1);
						break;
					case SDLK_DOWN:
						controlObject->ChangeDir(2);
						break;
					case SDLK_LEFT:
						controlObject->ChangeDir(3);
						break;

				}
				break;
			default:
				break;
		}
	}
}

void Game::update(){
	if(controlObject->Step()){
		printf("You lost, your score is %d", controlObject->length - 3);
		isRunning = false;
	}
}

void Game::render(){
	// Clear Render
	SDL_RenderClear(renderer->GetRenderer());

	// Prepare render
	controlObject->Draw();
	// Render
	renderer->RenderWindow();
	return;
}

void Game::clean(){
	renderer->CloseWindow();
	isRunning = false;
}
