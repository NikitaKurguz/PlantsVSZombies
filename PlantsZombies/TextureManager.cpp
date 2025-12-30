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
	for (auto& pair : textures)
	{
		if (pair.first == filename) return true;
	}
	sf::Texture* texture = new sf::Texture();
	if (texture->loadFromFile(filename)) {
		textures.push_back({ filename, texture });
		return true;
	}
	delete texture;
	return false;
}

sf::Texture* TextureManager::GetTexturePointer(const std::string& filename)
{
	for (auto& pair : textures) {
		if (pair.first == filename) 
			return pair.second;
	}
	return nullptr;
}

void TextureManager::DestroyTextures()
{
	for (auto& pair : textures) {
		delete pair.second;
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
