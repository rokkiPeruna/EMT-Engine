#include <EntityComponentSys/Systems/TransformSystem.hpp>

namespace jej
{

    std::vector<std::shared_ptr<TransformComponent>> TransformSystem::m_components = {};

    TransformSystem::TransformSystem() :
        System()
    {

    }
    //////////////////////////////////////////

    TransformSystem& TransformSystem::GetInstance()
    {
        static TransformSystem system;
        return system;
    }
    //////////////////////////////////////////

    TransformSystem::~TransformSystem()
    {

    }
    //////////////////////////////////////////

    void TransformSystem::_update(const float deltaTime)
    {

    }
    //////////////////////////////////////////

    bool TransformSystem::_finalize()
    {
        //TODO:
        return true;
    }
    //////////////////////////////////////////

    bool TransformSystem::_initialize()
    {
        //TODO:
        return true;
    }
    //////////////////////////////////////////

}