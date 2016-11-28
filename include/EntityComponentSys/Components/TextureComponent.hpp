#ifndef JEJ_SPRITECOMPONENT_HPP
#define JEJ_SPRITECOMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>
#include <Core/BaseStructs.hpp>

#include <string>
#include <vector>

namespace jej
{

	class TextureComponent:public Component
    {
        friend class TextureSystem;
		friend class RenderSystem;

	public:
		struct TextureData
		{
			std::string imageName = "";
			Vector2i wholeImageSize;
			Vector2i singleImageSize;
			unsigned int imageCount = 0u;
			std::vector<unsigned int> selectedImages;

			TextureData(){};
		};

        //Constructor
		//name is filename with extension
		//sizeOne is single image in pixels
        //p_count is number of images in the spritesheet
        //startImage is first image to load
        TextureComponent(Entity* entity, const TextureData& p_data);

        //Destructor
		virtual ~TextureComponent();

	private:
        //data of the image
		std::vector<char> m_imageData;
		TextureData m_textureData;

        //returns data from loaded image with the desired index
        std::vector<char> _getImage(const unsigned int p_index);

	};

}

#endif