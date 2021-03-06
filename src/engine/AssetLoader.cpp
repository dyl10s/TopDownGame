#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "engine/AssetLoader.hpp"

SDL_Rect AssetLoader::bullet;
SDL_Rect AssetLoader::player;
SDL_Rect AssetLoader::basicEnemy;

SDL_Rect AssetLoader::topWall;
SDL_Rect AssetLoader::bottomWall;
SDL_Rect AssetLoader::leftWall;
SDL_Rect AssetLoader::rightWall;

SDL_Rect AssetLoader::topLeftWall;
SDL_Rect AssetLoader::bottomRightWall;
SDL_Rect AssetLoader::topRightWall;
SDL_Rect AssetLoader::bottomLeftWall;

SDL_Rect AssetLoader::floorTile;

SDL_Surface* AssetLoader::tilesheet = nullptr;

AssetLoader::AssetLoader(std::string tileSheetPath){
    AssetLoader::tilesheet = IMG_Load(tileSheetPath.c_str());
    if( AssetLoader::tilesheet == NULL ){
		SDL_Log("Unable to load tilesheet.");
		exit(1);
	}

    // Setup the assets
    bullet = {289, 273, 6, 7};
    player = {145, 205, 15, 19};
    basicEnemy = {371, 334, 11, 18};

    topWall = {42, 124, 12, 20};
    bottomWall = {42, 156, 12, 19};
    leftWall = {32, 144, 5, 12};
    rightWall = {59, 144, 5, 12};

    topLeftWall = {32, 124, 10, 20};
    bottomRightWall = {54, 156, 10, 20};
    topRightWall = {54, 124, 10, 20};
    bottomLeftWall = {32, 156, 10, 19};

    floorTile = {16, 64, 16, 16};
}

AssetLoader::~AssetLoader(){
    SDL_FreeSurface(AssetLoader::tilesheet);
}