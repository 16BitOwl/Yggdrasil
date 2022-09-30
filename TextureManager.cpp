#include "TextureManager.h"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	m_InstanceFlag = false;
	this->ClearTextures();
}

TextureManager* TextureManager::GetInstance(void)
{
	if(!m_InstanceFlag)
	{
		m_Singleton = new TextureManager();
		m_InstanceFlag = true;
	}
	
	return m_Singleton;
}

void TextureManager::ChangeRenderer(SDL_Renderer* i_SDLRenderer)
{
	m_SDLRenderer = i_SDLRenderer;
}

bool TextureManager::LoadTexture(string i_Filename, unsigned int i_UniqueID)
{
	TextureData t_TextureData;

	// Load and check for errors
	t_TextureData.texture = IMG_LoadTexture(m_SDLRenderer, i_Filename.c_str());
	if (t_TextureData.texture == NULL)
	{
		return false;
	}

	SDL_QueryTexture(t_TextureData.texture, NULL, NULL, &t_TextureData.position.w, &t_TextureData.position.h);

	// Store and return success
	m_Textures.insert(pair<unsigned int, TextureData>(i_UniqueID, t_TextureData));
	cout << "Image (" << i_Filename << ") successfully loaded!" << endl;

	return true;
}

bool TextureManager::SetImageName(string i_Name, unsigned int i_UniqueID)
{
	if (m_TexturesByName.find(i_Name) != m_TexturesByName.end() || m_Textures.find(i_UniqueID) == m_Textures.end())
	{
		return false;
	}

	m_TexturesByName.insert(pair<string, unsigned int>(i_Name, i_UniqueID));

	return true;
}

SDL_Texture* TextureManager::GetTexture(unsigned int i_UniqueID)
{
	map<unsigned int, TextureData>::iterator t_Iterator = m_Textures.find(i_UniqueID);

	// Is there anything with the given ID? If no, return false
	if (t_Iterator == m_Textures.end())
	{
		return false;
	}

	return t_Iterator->second.texture;
}

SDL_Texture* TextureManager::GetTexture(string i_Name)
{
	map<string, unsigned int>::iterator t_Iterator = m_TexturesByName.find(i_Name);

	// Is there anything with the given name? If no, return false
	if (t_Iterator == m_TexturesByName.end())
	{
		return false;
	}

	// Call the ID GetTexture() function and return whatever it returns
	return this->GetTexture(t_Iterator->second);
}

void TextureManager::DrawTexture(int i_X, int i_Y, unsigned int i_UniqueID)
{
	map<unsigned int, TextureData>::iterator t_Iterator = m_Textures.find(i_UniqueID);

	// Is there anything with the given ID? If no, return false
	if (t_Iterator == m_Textures.end())
	{
		return;
	}

	t_Iterator->second.position.x = i_X;
	t_Iterator->second.position.y = i_Y;
	SDL_RenderCopy(m_SDLRenderer, t_Iterator->second.texture, NULL, &t_Iterator->second.position);
}

void TextureManager::DrawTexture(int i_X, int i_Y, string i_Name)
{
	map<string, unsigned int>::iterator t_Iterator = m_TexturesByName.find(i_Name);

	// Is there anything with the given name? If no, return false
	if (t_Iterator == m_TexturesByName.end())
	{
		return;
	}

	this->DrawTexture(i_X, i_Y, t_Iterator->second);
}

bool TextureManager::DeleteTexture(unsigned int i_UniqueID)
{
	map<unsigned int, TextureData>::iterator t_Iterator = m_Textures.find(i_UniqueID);

	// Is there anything with the given ID? If no, return false
	if (t_Iterator == m_Textures.end())
	{
		return false;
	}

	SDL_DestroyTexture(t_Iterator->second.texture);
	m_Textures.erase(t_Iterator);

	return true;
}

bool TextureManager::DeleteTexture(string i_Name)
{
	map<string, unsigned int>::iterator t_Iterator = m_TexturesByName.find(i_Name);

	// Is there anything with the given name? If no, return false
	if (t_Iterator == m_TexturesByName.end())
	{
		return false;
	}

	return this->DeleteTexture(t_Iterator->second);
}

void TextureManager::ClearTextures(void)
{
	for (map<unsigned int, TextureData>::iterator it = m_Textures.begin(); it != m_Textures.end(); ++it)
	{
		SDL_DestroyTexture(it->second.texture);
	}
	m_Textures.clear();
	m_TexturesByName.clear();
}

// Initialize the global logger variable
bool TextureManager::m_InstanceFlag = false;
TextureManager* TextureManager::m_Singleton = NULL;