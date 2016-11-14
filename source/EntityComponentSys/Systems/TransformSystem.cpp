#include <EntityComponentSys/Systems/TransformSystem.hpp>

namespace jej
{

    std::vector<std::shared_ptr<TransformComponent>> TransformSystem::m_components = {};

    TransformSystem::TransformSystem():
        System()
    {

    }

    TransformSystem& TransformSystem::GetInstance()
    {
        static TransformSystem system;
        return system;
    }

    TransformSystem::~TransformSystem()
    {

    }

    void TransformSystem::update(const float deltaTime)
    {

    }

}