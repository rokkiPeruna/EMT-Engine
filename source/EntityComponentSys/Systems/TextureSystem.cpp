#include <EntityComponentSys/Systems/TextureSystem.hpp>

namespace jej
{

    std::vector<std::shared_ptr<TextureComponent>> TextureSystem::m_components = {};

	TextureSystem::TextureSystem():
		System()
	{

	}

	TextureSystem::~TextureSystem()
	{

	}

	TextureSystem& TextureSystem::GetInstance()
	{
		static TextureSystem instance;
		return instance;
	}

    void TextureSystem::_update(const float p_deltaTime)
    {

    }

}