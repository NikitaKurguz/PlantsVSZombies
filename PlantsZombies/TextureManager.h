#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class TextureManager
{
private:
	static TextureManager* texture_instance;
	std::vector<std::pair<std::string, sf::Texture*>> textures;

	TextureManager();
	~TextureManager();
	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
public:
	bool LoadTextureFromFile(const std::string& filename);
	sf::Texture* GetTexturePointer(const std::string& filename);
	void DestroyTextures();

	static TextureManager* GetTextureInstance();
	void KillTextureInstance();
};

