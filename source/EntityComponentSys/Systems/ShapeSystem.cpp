#include <EntityComponentSys/Systems/ShapeSystem.hpp>

namespace jej
{

    std::vector<std::shared_ptr<ShapeComponent>> ShapeSystem::m_components = {};

    ShapeSystem::ShapeSystem():
        System()
    {

    }

    ShapeSystem::~ShapeSystem()
    {

    }

    ShapeSystem& ShapeSystem::GetInstance()
    {
        static ShapeSystem instance;
        return instance;
    }

    void ShapeSystem::_update(const float p_deltaTime)
    {

    }




}