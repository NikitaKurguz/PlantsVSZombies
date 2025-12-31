#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class TextureManager
{
private:
	struct Tex_data {
		sf::Texture* tex;
		std::string filename;
	};
	static TextureManager* texture_instance;
	std::vector<Tex_data> textures;

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

