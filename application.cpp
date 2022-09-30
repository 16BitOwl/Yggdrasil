#include "application.h"

Application::Application()
{
	m_SDLWindow = NULL;
	m_SDLRenderer = NULL;

	m_IsRunning = true;

	m_PlayerX = m_PlayerY = 0;
	m_PlayerSpeed = 100;

	m_DrawCircles = false;
	m_DrawTriGraph = false;
	m_DrawTriGraphMST = false;
	m_DrawRoomCircles = false;
	m_DrawCorridors = true;
	m_DrawPortals = false;
	m_DrawGrid = true;
	m_PauseGenerator = false;
}

int Application::onExecute(void)
{
	if (onInit() == false)
	{
		return -1;
	}

	SDL_Event mEvent;

	while (m_IsRunning)
	{
		while (SDL_PollEvent(&mEvent))
		{
			onEvent(&mEvent);
		}

		onLoop();
		onRender();
	}

	onCleanup();

	return 0;
}

bool Application::onInit(void)
{
	// First of all, read settings ini file
	m_IniSetup.SetUnicode();
	m_IniResources.SetUnicode();
	m_IniSetup.LoadFile("settings.ini");
	m_IniResources.LoadFile("resources.ini");
	int t_Width = (int)m_IniSetup.GetDoubleValue("Setup", "Width", 1600);
	int t_Height = (int)m_IniSetup.GetDoubleValue("Setup", "Height", 900);

	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL failed to initialize" << endl;
		return false;
	}

	// Init window
	m_SDLWindow = SDL_CreateWindow(DEF_WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, t_Width, t_Height, SDL_WINDOW_OPENGL);
	if (m_SDLWindow == false)
	{
		cout << "SDL failed to create a window" << endl;
		return false;
	}

	// Init renderer
	m_SDLRenderer = SDL_CreateRenderer(m_SDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_SDLRenderer == false)
	{
		cout << "SDL failed to create a renderer" << endl;
		return false;
	}

	// Init TTF fonts
	if (TTF_Init() == -1)
	{
		cout << "SDL plugin(TTF fonts) failed to initialize" << endl;
		return false;
	}

	// Init TextureManager
	TexManager->ChangeRenderer(m_SDLRenderer);

	// Generate stuff
	m_Generator.Reset();
	if (m_Generator.generationMode == 1) // Direct generation
	{
		m_Generator.GenerateDirect();
	}

	cout << " - SDL and plugins successfully loaded! - " << endl;

	//  <<-- Do own stuff below this line -->>
	this->LoadResources();

	// Assign SDL textures from the manager
	m_WallTexture = TexManager->GetTexture("Wall");
	m_FloorTexture = TexManager->GetTexture("Floor");
	m_StartTexture = TexManager->GetTexture("Start");
	m_GoalTexture = TexManager->GetTexture("Goal");

	time(&m_LastTimeChanged);

	cout << " - Resources successfully loaded! - " << endl;

	return true;
}

void Application::onEvent(SDL_Event* i_Event)
{
	// SDL is shutting down, close the program
	if(i_Event->type == SDL_QUIT)
	{
		m_IsRunning = false;
	}

	// SDL detected a key press
	if (i_Event->type == SDL_KEYDOWN)
	{
		if (i_Event->key.keysym.sym == SDLK_ESCAPE) // Quit
		{
			m_IsRunning = false;
		}
		if (i_Event->key.keysym.sym == SDLK_c) // Clear and do it again
		{
			m_Generator.Reset();
			if (m_Generator.generationMode == 1) // Direct generation
			{
				m_Generator.GenerateDirect();
			}
		}
		if (i_Event->key.keysym.sym == SDLK_u) // Toggle circles
		{
			m_DrawCircles = !m_DrawCircles;
		}
		if (i_Event->key.keysym.sym == SDLK_i) // Toggle tri graph
		{
			m_DrawTriGraphMST = false;
			m_DrawCorridors = false;
			m_DrawTriGraph = !m_DrawTriGraph;
		}
		if (i_Event->key.keysym.sym == SDLK_o) // Toggle tri graph MST
		{
			m_DrawTriGraph = false;
			m_DrawCorridors = false;
			m_DrawTriGraphMST = !m_DrawTriGraphMST;
		}
		if (i_Event->key.keysym.sym == SDLK_k) // Toggle corridors
		{
			m_DrawTriGraph = false;
			m_DrawTriGraphMST = false;
			m_DrawCorridors = !m_DrawCorridors;
		}
		if (i_Event->key.keysym.sym == SDLK_h) // Toggle portal circles
		{
			m_DrawPortals = !m_DrawPortals;
		}
		if (i_Event->key.keysym.sym == SDLK_p) // Toggle room outline circles
		{
			m_DrawRoomCircles = !m_DrawRoomCircles;
		}
		if (i_Event->key.keysym.sym == SDLK_j) // Toggle grid render
		{
			m_DrawGrid = !m_DrawGrid;
		}
		if (i_Event->key.keysym.sym == SDLK_SPACE) // Toggle generator pause
		{
			m_PauseGenerator = !m_PauseGenerator;
		}
		if (i_Event->key.keysym.sym == SDLK_w) 
		{
			m_PlayerY -= m_PlayerSpeed;
		}
		if (i_Event->key.keysym.sym == SDLK_s) 
		{
			m_PlayerY += m_PlayerSpeed;
		}
		if (i_Event->key.keysym.sym == SDLK_d) 
		{
			m_PlayerX += m_PlayerSpeed;
		}
		if (i_Event->key.keysym.sym == SDLK_a) 
		{
			m_PlayerX -= m_PlayerSpeed;
		}
	}
}

void Application::onLoop(void)
{
	// Find the mouse position
	SDL_GetMouseState(&m_MouseX, &m_MouseY);

	// Check file for changes
	if (stat("dungeon.ini", &dungeonFileInfo) == 0)
	{
		time_t updatedTime = dungeonFileInfo.st_mtime;
		double seconds = difftime(updatedTime, m_LastTimeChanged);
		if (seconds > 0)
		{
			m_Generator.Reset();
			if (m_Generator.generationMode == 1) // Direct generation
			{
				m_Generator.GenerateDirect();
			}
			m_LastTimeChanged = updatedTime;
		}
	}

	// Only generate step by step if told so
	if (m_Generator.generationMode == 0) 
	{
		if (m_PauseGenerator == false)
		{
			m_Generator.GenerateStep();
		}
	}
}

void Application::onRender(void)
{
	// Clear SDL renderer
	SDL_SetRenderDrawColor(m_SDLRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_SDLRenderer);

	// Render grid
	if (m_Generator.currentlyRunning >= 4)
	{
		for (unsigned int i = 0; i < m_Generator.dungeonGrid->width; i++)
		{
			for (unsigned int j = 0; j < m_Generator.dungeonGrid->height; j++)
			{
				// Render cell
				if (m_Generator.dungeonGrid->grid[i][j].type == ROOM)
				{
					SDL_SetRenderDrawColor(m_SDLRenderer, 155, 155, 155, 255);
				}
				else if (m_Generator.dungeonGrid->grid[i][j].type == CORRIDOR)
				{
					SDL_SetRenderDrawColor(m_SDLRenderer, 255, 155, 0, 255);
				}
				else
				{
					SDL_SetRenderDrawColor(m_SDLRenderer, 0, 30, 50, 255);
				}

				SDL_Rect rect;
				rect.x = (i) * 8;
				rect.y = (j) * 8;
				rect.w = 8;
				rect.h = 8;
				SDL_RenderDrawRect(m_SDLRenderer, &rect);
			}
		}
	}

	// Draw rooms
	if (m_Generator.currentlyRunning < 4)
	{
		for (unsigned int i = 0; i < m_Generator.roomGenerator->rooms.size(); i++)
		{
			// Draw room cells
			SDL_SetRenderDrawColor(m_SDLRenderer, 255, 255, 255, 255);
			for (int m = 0; m < m_Generator.roomGenerator->rooms[i]->width; m++)
			{
				for (int n = 0; n < m_Generator.roomGenerator->rooms[i]->height; n++)
				{
					SDL_Rect rect;
					rect.x = (m_Generator.roomGenerator->rooms[i]->x1 + m) * 8;
					rect.y = (m_Generator.roomGenerator->rooms[i]->y1 + n) * 8;
					rect.w = 8;
					rect.h = 8;
					SDL_RenderDrawRect(m_SDLRenderer, &rect);
				}
			}

			// Draw room outline
			SDL_SetRenderDrawColor(m_SDLRenderer, 255, 0, 255, 255);
			SDL_Rect rect;
			rect.x = (m_Generator.roomGenerator->rooms[i]->x1) * 8;
			rect.y = (m_Generator.roomGenerator->rooms[i]->y1) * 8;
			rect.w = m_Generator.roomGenerator->rooms[i]->width * 8;
			rect.h = m_Generator.roomGenerator->rooms[i]->height * 8;
			SDL_RenderDrawRect(m_SDLRenderer, &rect);

			// Draw graph
			SDL_SetRenderDrawColor(m_SDLRenderer, 255, 255, 0, 255);
			if (m_Generator.roomGenerator->rooms[i]->node != NULL)
			{
				for (unsigned int m = 0; m < m_Generator.roomGenerator->rooms[i]->node->neighbors.size(); m++)
				{
					SDL_RenderDrawLine(m_SDLRenderer, (m_Generator.roomGenerator->rooms[i]->centerX) * 8, (m_Generator.roomGenerator->rooms[i]->centerY) * 8,
						(m_Generator.roomGenerator->rooms[i]->node->neighbors[m]->node->room->centerX) * 8, (m_Generator.roomGenerator->rooms[i]->node->neighbors[m]->node->room->centerY) * 8);
				}
			}
		}

		// Draw corridors
		for (unsigned int i = 0; i < m_Generator.corridorGenerator->corridors.size(); i++)
		{
			// Draw blocks
			SDL_SetRenderDrawColor(m_SDLRenderer, 155, 255, 0, 255);
			for (unsigned int j = 0; j < m_Generator.corridorGenerator->corridors[i]->blocks.size(); j++)
			{
				SDL_Rect rect;
				rect.x = (m_Generator.corridorGenerator->corridors[i]->blocks[j]->x1) * 8;
				rect.y = (m_Generator.corridorGenerator->corridors[i]->blocks[j]->y1) * 8;
				rect.w = (m_Generator.corridorGenerator->corridors[i]->blocks[j]->width) * 8;
				rect.h = (m_Generator.corridorGenerator->corridors[i]->blocks[j]->height) * 8;
				SDL_RenderDrawRect(m_SDLRenderer, &rect);
			}
		}
	}

	// Draw walls
	for (unsigned int i = 0; i < m_Generator.wallGenerator->walls.size(); i++)
	{
		// Render walls
		SDL_SetRenderDrawColor(m_SDLRenderer, 0, 255, 255, 255);
		int x1 = m_Generator.wallGenerator->walls[i]->x1;
		int x2 = m_Generator.wallGenerator->walls[i]->x2;
		int y1 = m_Generator.wallGenerator->walls[i]->y1;
		int y2 = m_Generator.wallGenerator->walls[i]->y2;

		SDL_RenderDrawLine(m_SDLRenderer, x1 * 8, y1 * 8, x2 * 8, y2 * 8);
	}

	// Render BSP tree
	BspTree* leaf = m_Generator.dungeonBspTree;
	bool foundLeaf = false;
	if (m_Generator.currentlyRunning >= 6)
	{
		SDL_SetRenderDrawColor(m_SDLRenderer, 155, 255, 0, 255);
		unsigned int bspLevel = 0, estimated = 0;
		if (m_Generator.dungeonBspTree->x * 8 < m_MouseX && m_Generator.dungeonBspTree->y * 8 < m_MouseY && (m_Generator.dungeonBspTree->x + m_Generator.dungeonBspTree->width) * 8 > m_MouseX && (m_Generator.dungeonBspTree->y + m_Generator.dungeonBspTree->height) * 8 > m_MouseY)
		{
			while (estimated == bspLevel)
			{
				// Sanity first, check if outside
				if (m_Generator.dungeonBspTree->x * 8 >= m_MouseX && m_Generator.dungeonBspTree->y * 8 >= m_MouseY && (m_Generator.dungeonBspTree->x + m_Generator.dungeonBspTree->width) * 8 <= m_MouseX && (m_Generator.dungeonBspTree->y + m_Generator.dungeonBspTree->height) * 8 <= m_MouseY)
				{
					break;
				}
				foundLeaf = false;

				// Check the left child
				if (leaf->leftChild != NULL && foundLeaf == false)
				{
					if (leaf->leftChild->x * 8 <= m_MouseX && leaf->leftChild->y * 8 <= m_MouseY && (leaf->leftChild->x + leaf->leftChild->width) * 8 >= m_MouseX && (leaf->leftChild->y + leaf->leftChild->height) * 8 >= m_MouseY)
					{
						leaf = leaf->leftChild;
						foundLeaf = true;
						bspLevel++;
					}
				}

				// Check right leaf
				if (leaf->rightChild != NULL && foundLeaf == false)
				{
					if (leaf->rightChild->x * 8 <= m_MouseX && leaf->rightChild->y * 8 <= m_MouseY && (leaf->rightChild->x + leaf->rightChild->width)  * 8 >= m_MouseX && (leaf->rightChild->y + leaf->rightChild->height) * 8 >= m_MouseY)
					{
						leaf = leaf->rightChild;
						foundLeaf = true;
						bspLevel++;
					}
				}

				// Finished
				if (!leaf->rightChild && !leaf->leftChild)
				{
					break;
				}
				estimated++;
			}
		}
		SDL_Rect rectBSP;
		rectBSP.x = (leaf->x) * 8;
		rectBSP.y = (leaf->y) * 8;
		rectBSP.w = (leaf->width) * 8;
		rectBSP.h = (leaf->height) * 8;
		SDL_RenderDrawRect(m_SDLRenderer, &rectBSP);

		for (unsigned int i = 0; i < leaf->rooms.size(); i++)
		{
			SDL_Rect rectBSPRoom;
			rectBSPRoom.x = (leaf->rooms[i]->x1) * 8;
			rectBSPRoom.y = (leaf->rooms[i]->y1) * 8;
			rectBSPRoom.w = (leaf->rooms[i]->width) * 8;
			rectBSPRoom.h = (leaf->rooms[i]->height) * 8;
			SDL_RenderDrawRect(m_SDLRenderer, &rectBSPRoom);
		}
	}

	// Render info text
	stringstream t_TextStream;

	DrawText(1100, 20, "=== Usage Info ===");
	DrawText(1100, 40, "Key u - Toggle graph circles");
	DrawText(1100, 60, "Key i - Toggle node graph");
	DrawText(1100, 80, "Key o - Toggle minimum spanning tree");
	DrawText(1100, 100, "Key p - Toggle room radius circles");
	DrawText(1100, 120, "Key k - Toggle corridors");
	DrawText(1100, 140, "Key h - Toggle portals");
	DrawText(1100, 160, "Key j - Toggle grid/gridless render");

	DrawText(1100, 400, "=== Generation Info ===");
	t_TextStream << "Time spent: " << m_Generator.totalTimeSpent << " ms" << endl;
	DrawText(1100, 420, t_TextStream.str().c_str());
	t_TextStream.clear();
	t_TextStream.str(std::string());

	t_TextStream << "BSP rooms: " << leaf->rooms.size() << endl;
	DrawText(1100, 440, t_TextStream.str().c_str());
	t_TextStream.clear();
	t_TextStream.str(std::string());

	if (m_PauseGenerator)
	{
		DrawText(1100, 460, "Paused! Press space to unpause");
	}

	// Refresh SDL screen and show us magic!
	SDL_RenderPresent(m_SDLRenderer);
}

void Application::onCleanup(void)
{
	// Destroy SDL
	SDL_DestroyRenderer(m_SDLRenderer);
	SDL_DestroyWindow(m_SDLWindow);

	cout << " - Window and renderer removed! - " << endl;

	// Destroy textures
	TexManager->ClearTextures();

	// Destroy TTF fonts
	TTF_CloseFont(m_MainFont);
	TTF_CloseFont(m_MainFontLarge);
	TTF_Quit();

	cout << " - External resources freed! - " << endl;

	// Tell SDL to quit
	SDL_Quit();
}

void Application::ApplySurface(int i_X, int i_Y, SDL_Texture* i_Texture)
{
	SDL_Rect t_Position;
	t_Position.x = i_X;
	t_Position.y = i_Y;
	SDL_QueryTexture(i_Texture, NULL, NULL, &t_Position.w, &t_Position.h);

	SDL_RenderCopy(m_SDLRenderer, i_Texture, NULL, &t_Position);
}

void Application::DrawText(int i_X, int i_Y, const char* i_Text)
{
	SDL_Surface* t_TextSurface;
	SDL_Texture* t_FontTexture;
	SDL_Color t_Color = {255, 255, 255};

	t_TextSurface = TTF_RenderText_Solid(m_MainFont, i_Text, t_Color);
	t_FontTexture = SDL_CreateTextureFromSurface(m_SDLRenderer, t_TextSurface);
	ApplySurface(i_X, i_Y, t_FontTexture);

	SDL_DestroyTexture(t_FontTexture);
	SDL_FreeSurface(t_TextSurface);
}

void Application::LoadResources(void)
{
	// Load textures from an external file
	CSimpleIniA::TNamesDepend t_Values;
	CSimpleIniA::TNamesDepend::const_iterator it;
	unsigned int t_IDIterator = 0;
	m_IniResources.GetAllSections(t_Values);

	for (it = t_Values.begin(); it != t_Values.end(); ++it) 
	{
		TexManager->LoadTexture(m_IniResources.GetValue(it->pItem, "File"), t_IDIterator);
		TexManager->SetImageName(it->pItem, t_IDIterator);
		t_IDIterator++;
	}

	// Load fonts
	m_MainFont = TTF_OpenFont("fonts/EqualSans_Demo.ttf", 20);
	m_MainFontLarge = TTF_OpenFont("fonts/EqualSans_Demo.ttf", 80);
}