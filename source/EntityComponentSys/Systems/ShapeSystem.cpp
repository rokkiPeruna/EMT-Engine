#include <EntityComponentSys/Systems/ShapeSystem.hpp>

#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{

    std::vector<std::shared_ptr<ShapeComponent>> ShapeSystem::m_components = {};


    ShapeSystem::ShapeSystem() :
        System()
    {

    }
    //////////////////////////////////////////


    ShapeSystem::~ShapeSystem()
    {

    }
    //////////////////////////////////////////


    ShapeSystem& ShapeSystem::GetInstance()
    {
        static ShapeSystem instance;
        return instance;
    }
    //////////////////////////////////////////


    void ShapeSystem::_update(const float p_deltaTime)
    {

    }
    //////////////////////////////////////////


    bool ShapeSystem::_finalize()
    {
        //TODO:
        return true;
    }
    //////////////////////////////////////////

    bool ShapeSystem::_initialize()
    {
        //TODO:
        return true;
    }
    //////////////////////////////////////////

    bool ShapeSystem::_setTextureID(const TextureComponent::ShapeData* p_shapeData)
    {
        for (const auto& itrComp : m_components)
            if (itrComp->GetParentID() == p_shapeData->parentID)
                for (auto& itrShape : itrComp->m_shapes)
                    if (itrShape->GetID() == p_shapeData->shapeID)
                    {
                        itrShape->m_textureID = p_shapeData->textureID;
                        return true;
                    }
        return false;
    }

}