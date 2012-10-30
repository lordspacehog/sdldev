#include "SDL/SDL.h"
#include <string>

//screen attrib
const int screen_w = 640;
const int screen_h = 480;
const int screen_b = 32;	

//surfaces
SDL_Surface *dude = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

//events
SDL_Event event;

SDL_Surface *load_image(std::string strFile){
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optImage = NULL;

	loadedImage = SDL_LoadBMP(strFile.c_str());

	if(loadedImage!=NULL){
		optImage = SDL_DisplayFormat(loadedImage);

		SDL_FreeSurface(loadedImage);
		
		if(optImage != NULL) {
			Uint32 colorkey = SDL_MapRGB(optImage->format,0,0xFF,0x42);


			SDL_SetColorKey(optImage,SDL_SRCCOLORKEY,colorkey);
		}
	}

	return optImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* dest){
	//temp
	SDL_Rect offset;

	//offset rect
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, dest, &offset);
}

//init
bool init() {
	//init SDL
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1){
		return false;
	}

	//Init Screen
	screen = SDL_SetVideoMode(screen_w, screen_h, screen_b, SDL_SWSURFACE);
	
	if(screen==NULL){
		return false;
	}

	//Set Window Caption
	SDL_WM_SetCaption("Hello World", NULL);

	//return good
	return true;
}

bool load_files(){
	//load images
	dude = load_image("dude.bmp");
	background = load_image("background.bmp");

	if(dude == NULL||background == NULL){
		return false;
	}

	return true;
}

bool Clean(){
	//free image
	SDL_FreeSurface(dude);	
	SDL_FreeSurface(background);	

	//quit
	SDL_Quit();
}

int main(int argc, char* args[]) {
	if(init()==false){
		return 1;
	}

	if(load_files()==false){
		return 1;
	}

	//apply background
	apply_surface(0,0,background,screen);
	
	//apply dude
	apply_surface(320,200,dude,screen);
	
	//Update
	if(SDL_Flip(screen)==-1){
		return 1;
	}
	
	bool q=NULL;

	while( q==false){
		while(SDL_PollEvent(&event)){
			if(event.type==SDL_QUIT){
				q=true;
			}
		}
	}
	
	Clean();

	return 0;
}
