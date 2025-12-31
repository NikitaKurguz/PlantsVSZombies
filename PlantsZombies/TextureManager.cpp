#include "TextureManager.h"
TextureManager* TextureManager::texture_instance = nullptr;
TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	DestroyTextures();
}

bool TextureManager::LoadTextureFromFile(const std::string& filename)
{
	for (auto& data : textures)
		if (data.filename == filename)
			return true;

	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(filename))
	{
		delete texture;
		return false;
	}

	textures.push_back({ texture, filename}); 
	return true;
}


sf::Texture* TextureManager::GetTexturePointer(const std::string& filename)
{
	for (auto& data : textures) {
		if (data.filename == filename) 
			return data.tex;
	}
	return nullptr;
}
void TextureManager::DestroyTextures()
{
	for (auto& data : textures) {
		delete data.tex;
	}
	textures.clear();
}

TextureManager* TextureManager::GetTextureInstance()
{
	if (texture_instance == nullptr) 
		texture_instance = new TextureManager();
	return texture_instance;
}

void TextureManager::KillTextureInstance()
{
	if (texture_instance) delete texture_instance;
	texture_instance = nullptr;
}
