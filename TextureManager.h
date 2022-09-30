/*! 
* \file TextureManager.h
* \breif A texture manager, to make loading and using textures via SDL less painful
*
* \author Dennis Fredriksson
* \date 2014-02-26
*/
#pragma once

#include <map>
#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

/*!
* \def TexManager
* \brief This is used to make life easier using the singleton
*/
#define TexManager TextureManager::GetInstance()

/*!
* \class TextureManager
* \brief A texture manager for SDL. Requires SDL_image library to work
*
* \author Dennis Fredriksson
*/
class TextureManager
{
private:
	struct TextureData
	{
		SDL_Texture* texture;
		SDL_Rect position;
	};

	/*!
	* \var map<unsigned int, TextureData> m_Textures
	* \brief Contains all loaded textures
	* \private
	*/
	map<unsigned int, TextureData> m_Textures;

	/*!
	* \var map<string, unsigned int> m_TexturesByName
	* \brief Contains any names assigned to a loaded texture
	* \private
	*/
	map<string, unsigned int> m_TexturesByName;

	/*!
	* \var SDL_Renderer* m_SDLRenderer
	* \brief Stores a pointer to the current renderer
	* \private
	*/
	SDL_Renderer* m_SDLRenderer;

	/*! 
	* \var static bool m_InstanceFlag
    * \brief Singleton instance flag
	* \private
	*/
	static bool m_InstanceFlag;

	/*! 
	* \var static TextureManager* m_Singleton
    * \brief Singleton class pointer
	* \private
	*/
	static TextureManager* m_Singleton;

	/*!
	* \fn TextureManager()
	* \brief Class constructor
	* \private
	*/
	TextureManager();

public:
	/*!
	* \fn static TextureManager* GetInstance(void)
	* \brief Returns an instance of the class singleton
	*
	* \retval static TextureManager*
	*/
	static TextureManager* GetInstance(void);

	/*!
	* \fn ~TextureManager()
	* \brief Class deconstructor
	*/
	~TextureManager();

	/*!
	* \fn void ChangeRenderer(SDL_Renderer* i_SDLRenderer)
	* \brief Changes the renderer this class uses to load its texture
	*
	* \param[in] i_SDLRenderer A pointer to the SDL renderer we wish to use
	*/
	void ChangeRenderer(SDL_Renderer* i_SDLRenderer);

	/*!
	* \fn bool LoadTexture(string i_Filename, unsigned int i_UniqueID)
	* \brief Loads an external image file into the software
	*
	* The function will return true if the file was successfully loaded or false if the unique ID is already taken
	*
	* \param[in] i_Filename The name and path to the image to load, relative to the current working directory
	* \param[in] i_UniqueID The unique ID for this texture
	* \retval bool
	*/
	bool LoadTexture(string i_Filename, unsigned int i_UniqueID);

	/*!
	* \fn bool SetImageName(unsigned int i_UniqueID, string i_Name)
	* \brief Assigns a name to any given valid image ID
	*
	* The function will return false if the name is already in use or if there isn't a texture loaded to the given ID number, otherwise it will return true
	*
	* \param[in] i_Name The name you wish to use
	* \param[in] i_UniqueID The unique ID to assign a name to
	* \retval bool
	*/
	bool SetImageName(string i_Name, unsigned int i_UniqueID);

	/*!
	* \fn SDL_Texture* GetTexture(unsigned int i_UniqueID)
	* \brief Returns a pointer to the texture with a given ID
	*
	* The function will return false if the ID doesn't exist
	*
	* \param[in] i_UniqueID The unique texture ID
	* \retval SDL_Texture*
	*/
	SDL_Texture* GetTexture(unsigned int i_UniqueID);

	/*!
	* \fn SDL_Texture* GetTexture(string i_Name)
	* \brief Returns a pointer to the texture with a given name
	*
	* The function will return false if the name doesn't exist
	*
	* \param[in] i_Name The name of the texture (set using SetImageName)
	* \retval SDL_Texture*
	*/
	SDL_Texture* GetTexture(string i_Name);

	/*!
	* \fn void DrawTexture(int i_X, int i_Y, unsigned int i_UniqueID)
	* \brief Draws a texture to the screen
	*
	* \param[in] i_X The X position
	* \param[in] i_Y The Y position
	* \param[in] i_UniqueID The textures unique ID
	*/
	void DrawTexture(int i_X, int i_Y, unsigned int i_UniqueID);

	/*!
	* \fn void DrawTexture(int i_X, int i_Y, string i_Name)
	* \brief Draws a texture to the screen
	*
	* \param[in] i_X The X position
	* \param[in] i_Y The Y position
	* \param[in] i_Name The textures name
	*/
	void DrawTexture(int i_X, int i_Y, string i_Name);

	/*!
	* \fn bool DeleteTexture(unsigned int i_UniqueID)
	* \brief Deletes a texture from the manager and frees up the resource
	*
	* \param[in] i_UniqueID The textures unique ID
	* \retval bool
	*/
	bool DeleteTexture(unsigned int i_UniqueID);

	/*!
	* \fn bool DeleteTexture(string i_Name)
	* \brief Deletes a texture from the manager and frees up the resource
	*
	* \param[in] i_Name The textures name
	* \retval bool
	*/
	bool DeleteTexture(string i_Name);

	/*!
	* \fn void ClearTextures(void
	* \brief Deletes all loaded textures
	*/
	void ClearTextures(void);
};