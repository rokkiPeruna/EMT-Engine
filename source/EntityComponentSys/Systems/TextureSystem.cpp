#pragma comment(lib, "ws2_32.lib")
#include <EntityComponentSys/Systems/TextureSystem.hpp>
#include <Utility\Messenger.hpp>
#include <winsock.h>
#include <fstream>

namespace jej
{
	TextureSystem::TextureSystem()
	{

	}
	TextureSystem::~TextureSystem()
	{

	}
	TextureSystem& TextureSystem::GetInstance()
	{
		static TextureSystem system;
		return system;
	}

	void TextureSystem::_bind(unsigned int p_unit)
	{

	}


	void TextureSystem::_initialize(const std::string& p_textureName)
	{
		unsigned int width, height, numComponents;
		char* imageData;
		GLuint m_texture;


		FileHandler fileHandler;
		fileHandler.Read(p_textureName);
		imageData = fileHandler.m_fileContents;

		std::fstream file(p_textureName.c_str(), std::ios_base::binary | std::ios_base::in);

		if (!file.is_open() || !file)
		{
			file.close();
			Messenger::Add(Messenger::MessageType::Error, "Failed to open texture");
		}

		file.seekg(16);
		file.read((char*)&width, 4);
		file.read((char*)&height, 4);

		width = ntohl(width);
		height = ntohl(height);

		glGenTextures(1, &m_texture);

		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);


	}


	void TextureSystem::_update(const float deltaTime)
	{

	}



}