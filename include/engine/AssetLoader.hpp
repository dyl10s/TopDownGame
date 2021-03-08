#ifndef			__HPP__ASSETLOADER__
#define			__HPP__ASSETLOADER__

#include <SDL2/SDL.h>
#include <string>

// This can handle all the loading and destroying of textures
class AssetLoader {
	public:
		AssetLoader(std::string tileSheet);
                ~AssetLoader();

                static SDL_Rect** enemyBullet;
                static SDL_Rect** friendlyBullet;

                static SDL_Rect** hearts;
                static SDL_Rect** player;

                static SDL_Rect** door;

                // Enemies
                static SDL_Rect** basicEnemy;
                static SDL_Rect** burstEnemy;

                // Static
                static SDL_Rect topWall;
                static SDL_Rect bottomWall;
                static SDL_Rect leftWall;
                static SDL_Rect rightWall;

                static SDL_Rect topLeftWall;
                static SDL_Rect bottomRightWall;
                static SDL_Rect topRightWall;
                static SDL_Rect bottomLeftWall;

                static SDL_Rect floorTile;

                static SDL_Texture* tilesheet;

	private:
                SDL_Surface* loadFromTilesheet(int x, int y, int w, int h);
};

#endif
