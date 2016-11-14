#include <EntityComponentSys/Systems/RenderSystem.hpp>
#include <EntityComponentSys/Components/RenderComponent.hpp>


namespace jej
{
    RenderSystem::RenderSystem()
    {

    }
    //

    RenderSystem::~RenderSystem()
    {

    }
    //

    RenderSystem& RenderSystem::GetInstance()
    {
        static RenderSystem system;
        return system;
    }
    //

    void RenderSystem::Update()
    {
        for (auto const& renderComp : m_components)
        {
            //TODO: Everything
            
        }
    }
}