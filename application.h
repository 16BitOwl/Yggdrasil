/*! 
* \file application.h
* \breif The SDL main file
*
* \author Dennis Fredriksson
* \date 2014-02-11
*/
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_timer.h>

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <ctime>

#include "Logger.h"
#include "TextureManager.h"
#include "SimpleIni.h"
#include "Rooms.h"
#include "bspTree.h"
#include "dungeonGenerator.h"

#include "SDL2_gfxPrimitives.h"

using namespace std;

/*!
* \def DEF_WINDOW_WIDTH
* \brief Default window width
*/
#define DEF_WINDOW_WIDTH 1600

/*!
* \def DEF_WINDOW_HEIGHT
* \brief Default window height
*/
#define DEF_WINDOW_HEIGHT 900

/*!
* \def DEF_WINDOW_TITLE
* \brief Default window title, for easy changing
*/
#define DEF_WINDOW_TITLE "Yggdrasil Layout tech demo | Ver 1.0.0| Using SDL"

/*!
* \class Application
* \brief The SDL application class the handles graphics, input and game logic
*
* \author Dennis Fredriksson
*/
class Application
{
private:
	bool m_IsRunning;

	SDL_Window* m_SDLWindow;
	SDL_Renderer* m_SDLRenderer;

	SDL_Texture* m_WallTexture;
	SDL_Texture* m_FloorTexture;
	SDL_Texture* m_StartTexture;
	SDL_Texture* m_GoalTexture;

	bool m_DrawCircles;
	bool m_DrawTriGraph, m_DrawTriGraphMST, m_DrawCorridors;
	bool m_DrawRoomCircles, m_DrawPortals;
	bool m_DrawGrid;
	bool m_PauseGenerator;

	TTF_Font* m_MainFont;
	TTF_Font* m_MainFontLarge;

	int m_PlayerX, m_PlayerY, m_PlayerSpeed;

	CSimpleIniA m_IniSetup, m_IniResources;

	struct stat dungeonFileInfo;
	time_t m_LastTimeChanged;

	int m_MouseX, m_MouseY;

	dungeonGenerator m_Generator;

	/*!
	* \fn void ApplySurface(int i_X, int i_Y, SDL_Texture* i_Texture)
	* \brief Helper function, applies an image to the current visible screenspace
	* \private
	*
	* \param[in] i_X The images position on the X axis
	* \param[in] i_Y The images position on the Y axis
	* \param[in] i_Texture A pointer to the image
	*/
	void ApplySurface(int i_X, int i_Y, SDL_Texture* i_Texture);

	/*!
	* \fn void DrawText(int i_X, int i_Y, const char* i_Text)
	* \brief Helper function, prints some text to the screen at a given position
	* \private
	*
	* \param[in] i_X The text position on the X axis
	* \param[in] i_Y The text position on the Y axis
	* \param[in] i_Text The text to print to the screen
	*/
	void DrawText(int i_X, int i_Y, const char* i_Text);

	/*!
	* \fn void LoadResources(void)
	* \brief Helper function, loads all of the resources used by this application
	* \private
	*/
	void LoadResources(void);

public:
	/*!
	* \fn Application()
	* \brief Class constructor
	*/
	Application();

	/*!
	* \fn int onExecute(void)
	* \brief The application execute function, maintains render and game logic loops and cleanup
	*
	* \retval int
	*/
	int onExecute(void);

	/*!
	* \fn bool onInit(void)
	* \brief The applications init function, loads resources and sets up classes and instances used
	*
	* \retval bool
	*/
	bool onInit(void);

	/*!
	* \fn void onEvent(SDL_Event* i_Event)
	* \brief The applications event handler, takes care of messages received from SDL, as well as input from the user
	*
	* \param[in] i_Event The event that was sent from SDL
	*/
	void onEvent(SDL_Event* i_Event);

	/*!
	* \fn void onLoop(void)
	* \brief The applications main loop, any game logic takes place in here
	*/
	void onLoop(void);

	/*!
	* \fn void onRender(void)
	* \brief The applications render loop, anything that is to be rendered is done here
	*/
	void onRender(void);

	/*!
	* \fn void onCleanup(void)
	* \brief The applications cleanup function, removes loaded resources as well as destroying any instanced classes
	*/
	void onCleanup(void);
};