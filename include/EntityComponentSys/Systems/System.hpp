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

        //Staattinen säiliö Transform komponenteille
        static std::vector<TransformComponent> _transformCont;

        //Staattinen säiliö nönnönönönöö komponenteille
        //Staattinen säiliö n-1 komponenteille
    };
}


#endif