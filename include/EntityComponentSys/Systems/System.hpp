#ifndef JEJ_SYSTEM_HPP
#define JEJ_SYSTEM_HPP

//
#include <vector>
//

//
#include <EntityComponentSys/Components/TransformComponent.hpp>
//

namespace jej
{
    class System
    {
    public:
        //
        System();

        //
        virtual ~System();

        //Staattinen s�ili� Transform komponenteille
        static std::vector<TransformComponent> _transformCont;

        //Staattinen s�ili� n�nn�n�n�n�� komponenteille
        //Staattinen s�ili� n-1 komponenteille
    };
}


#endif