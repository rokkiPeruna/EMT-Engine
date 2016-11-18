#include <EntityComponentSys/Systems/SpriteSystem.hpp>

namespace jej
{

	SpriteSystem::SpriteSystem():
		System(),
		m_components()
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

    void SpriteSystem::update(const float p_deltaTime)
    {

    }

}