#include <Core/Scene.hpp>

#include <Utility/Messenger.hpp>

#include <iterator>

namespace jej
{


	JEJ_COUNT Scene::m_sceneCounter = 0u;
    
	
	Scene::Scene(const std::string& p_name) :
		m_name(p_name),
		m_ID(++m_sceneCounter),
        m_entities(),
		m_active(false)
    {

    }

    Scene::~Scene()
    {
        while (!m_entities.empty())
        {
            for (unsigned int i = 0u; i < m_entities.size(); ++i)
            {
                m_entities.erase(m_entities.begin() + i);
                break;
            }
        }
    }

  // std::vector<std::shared_ptr<Entity>>* Scene::GetEntities()
  // {
  //     return &m_entities;
  // }

    Entity& Scene::AddEntity(const std::string& p_name)
    {
        m_entities.emplace_back(std::make_shared<Entity>(p_name));
        return *m_entities.back().get();
    }

    Entity* Scene::GetEntityPtr(const std::string& p_name)
    {
        for (auto& itr : m_entities)
            if (itr->m_name == p_name)
                return itr.get();

        return nullptr;
    }

    Entity* Scene::GetEntityPtr(const unsigned int p_ID)
    {
        for (auto& itr : m_entities)
            if (itr->m_entityID == p_ID)
                return itr.get();

        return nullptr;
    }

    const Entity* Scene::GetEntityPtr(const std::string& p_name) const
    {
        for (const auto& itr : m_entities)
            if (itr->m_name == p_name)
                return itr.get();

        return nullptr;
    }

    const Entity* Scene::GetEntityPtr(const unsigned int p_ID) const
    {
        for (const auto& itr : m_entities)
            if (itr->m_entityID == p_ID)
                return itr.get();

        return nullptr;
    }

    bool Scene::HasEntity(const std::string& p_name)
    {
        for (const auto& itr : m_entities)
            if (itr->m_name == p_name)
                return true;

        return false;
    }

    bool Scene::HasEntity(const unsigned int p_ID)
    {
		for (const auto& itr : m_entities)
            if (itr->m_entityID == p_ID)
                return true;

        return false;
    }

    bool Scene::RemoveEntity(const std::string& p_name)
    {
       //for (auto& itr = m_entities.begin(); itr != m_entities.end(); ++itr)
       //{
       //    if (itr->get()->m_name == p_name)
       //    {
       //        m_entities.erase(itr);
       //        return true;
       //    }
       //}
        return false;
    }

    bool Scene::RemoveEntity(const unsigned int p_ID)
    {
        //for (auto& itr = m_entities.begin(); itr != m_entities.end(); ++itr)
        //    if (itr->get()->m_entityID == p_ID)
        //    {
        //        m_entities.erase(itr);
        //        return true;
        //    }
        return false;
    }

}