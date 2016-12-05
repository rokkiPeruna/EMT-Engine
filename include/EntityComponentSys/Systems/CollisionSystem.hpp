#ifndef JEJ_COLLISION_SYSTEM_HPP
#define JEJ_COLLISION_SYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>
#include <EntityComponentSys/Components/CollisionComponent.hpp>

namespace jej
{
	class CollisionSystem : public System
	{

        friend class EngineObject;
        friend class Entity;
        

	private:

		CollisionSystem();

		
	public:

        //Disabled copy-constructors
        NOCOPY(CollisionSystem);

		~CollisionSystem();

		static CollisionSystem& GetInstance();
		
    protected:

        void _update(const float deltaTime) override;

        bool _finalize() override;

        bool _initialize() override;

        static std::vector<std::shared_ptr<CollisionComponent>> m_components;

	};



}

#endif