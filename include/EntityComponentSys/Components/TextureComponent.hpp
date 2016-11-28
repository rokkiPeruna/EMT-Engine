#ifndef JEJ_TEXTURE_COMPONENT_HPP
#define JEJ_TEXTURE_COMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>
#include <External/OpenGL_ES2/GLES2/gl2.h>
#include <Core/BaseStructs.hpp>

#include <string>
#include <vector>

namespace jej
{

    struct TextureData
    {
        std::string imageName = "";                 //Texture filename with extension
        Vector2i wholeImageSize;                    //Size of the whole image in pixels
        Vector2i singleImageSize;                   //Size of a single image in pixels
        unsigned int imageCount = 0u;               //Number of images in the whole file
        std::vector<unsigned int> selectedImages;   //Indices of the images that will be loaded, defaults to whole file
        std::vector<char> readImageData;            //Requested image data from the file
        GLuint m_textureID;                         //ID of the texture handled by OpenGL

        TextureData(){};
    };

    class TextureComponent : public Component
    {
        friend class TextureSystem;
        friend class RenderSystem;

    public:

        

        //Constructor
        //p_name: Name of the image with extension
        TextureComponent(Entity* entity, const std::string& p_name);

        //Disabled copy-constructors
        TextureComponent(const TextureComponent&) = delete;
        TextureComponent operator=(const TextureComponent&) = delete;

        //Destructor
        virtual ~TextureComponent();

    private:

        //Data of the read image
        TextureData m_textureData;

        //Returns data from loaded image with the desired index
      //  std::vector<char> _getImage(const unsigned int p_index);

    };

}

#endif