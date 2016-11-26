#ifndef JEJ_SPRITECOMPONENT_HPP
#define JEJ_SPRITECOMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>
#include <Core/BaseStructs.hpp>

#include <string>
#include <vector>

namespace jej
{

	class SpriteComponent:public Component
    {
        friend class SpriteSystem;
		friend class RenderSystem;

	public:
        //Constructor
		//name is filename with extension
		//sizeOne is single image in pixels
        //p_count is number of images in the spritesheet
        //startImage is first image to load
        SpriteComponent(Entity& entity, const std::string& p_name, const Vector2f& p_sizeOne, const unsigned int p_count, const unsigned int p_startImage = 0u);

        //Destructor
		virtual ~SpriteComponent();

	private:
        //data of the image
		std::vector<char> m_data;

		//size of a single image
		Vector2f m_sizeOne;

        //number of images in the spritesheet
		unsigned int m_count;

        //returns data from loaded image with the desired index
        std::vector<char> _getImage(const unsigned int p_index);

	};

}

#endif