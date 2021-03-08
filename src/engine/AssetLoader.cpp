#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "engine/AssetLoader.hpp"
#include "engine/Engine.hpp"

SDL_Rect AssetLoader::bullet;
SDL_Rect** AssetLoader::player;

// Enemies
SDL_Rect** AssetLoader::basicEnemy;
SDL_Rect** AssetLoader::burstEnemy;

// Static
SDL_Rect AssetLoader::topWall;
SDL_Rect AssetLoader::bottomWall;
SDL_Rect AssetLoader::leftWall;
SDL_Rect AssetLoader::rightWall;

SDL_Rect AssetLoader::topLeftWall;
SDL_Rect AssetLoader::bottomRightWall;
SDL_Rect AssetLoader::topRightWall;
SDL_Rect AssetLoader::bottomLeftWall;

SDL_Rect AssetLoader::floorTile;

SDL_Texture* AssetLoader::tilesheet = nullptr;

AssetLoader::AssetLoader(std::string tileSheetPath){
    auto tilesheetSurface = IMG_Load(tileSheetPath.c_str());
    if( tilesheetSurface == NULL ){
		SDL_Log("Unable to load tilesheet.");
		exit(1);
	}

    AssetLoader::tilesheet = SDL_CreateTextureFromSurface(Engine::getRenderer(), tilesheetSurface);

    // Setup the assets
    bullet = {289, 273, 6, 7};

    player = new SDL_Rect*[4] {
        new SDL_Rect({129, 237, 15, 19}),
        new SDL_Rect({145, 237, 15, 19}),
        new SDL_Rect({160, 237, 15, 19}),
        new SDL_Rect({177, 237, 15, 19})
    };

    // Enemies
    basicEnemy = new SDL_Rect*[3] {
        new SDL_Rect({371, 334, 11, 18}),
        new SDL_Rect({387, 334, 11, 18}),
        new SDL_Rect({403, 334, 11, 18})
    };

    burstEnemy = new SDL_Rect*[4] {
        new SDL_Rect({372, 38, 10, 10}),
        new SDL_Rect({388, 38, 10, 10}),
        new SDL_Rect({404, 38, 10, 10}),
        new SDL_Rect({420, 38, 10, 10})
    };

    // Static
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
    SDL_DestroyTexture(AssetLoader::tilesheet);
}