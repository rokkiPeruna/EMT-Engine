#include <EntityComponentSys/Systems/SpriteSystem.hpp>

namespace jej
{

    std::vector<std::shared_ptr<SpriteComponent>> SpriteSystem::m_components = {};

	SpriteSystem::SpriteSystem():
		System()
	{

	}

	SpriteSystem::~SpriteSystem()
	{

	}

	SpriteSystem& SpriteSystem::GetInstance()
	{
		static SpriteSystem instance;
		return instance;
	}

    void SpriteSystem::_update(const float p_deltaTime)
    {

    }

}