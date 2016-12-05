#ifndef JEJ_TEXTURE_COMPONENT_HPP
#define JEJ_TEXTURE_COMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>

#include <Core/BaseStructs.hpp>
#include <External/OpenGL_ES2/GLES2/gl2.h>
#include <External/STB/stb_image.h>
#include <External/STB/stb_truetype.h>

#include <string>
#include <vector>

namespace jej
{

    class Entity;
    class TextureComponent : public Component
    {

        friend class TextureSystem;
        friend class RenderSystem;

    public:


        struct TextureData
        {
            std::string imageName = "";                 //Texture filename with extension
            Vector2i wholeImageSize;                    //Size of the whole image in pixels
            Vector2i singleImageSize;                   //Size of a single image in pixels
            unsigned int imageCount = 0u;               //Number of images in the whole file
            std::vector<unsigned char> selectedImages;  //Indices of the images that will be loaded, defaults to whole file
            unsigned char* displayImage = nullptr;      //Image to render
            GLuint m_textureID;                         //ID of the texture handled by OpenGL
            int offset = 0;                             //Offset //TODO: Find out what does this thing do

            TextureData(){};
            NOCOPY(TextureData);
            ~TextureData()
            {
                //Free texture if present (also called in texcomp dtor)
                if (displayImage)
                {
                    stbi_image_free(displayImage);
                    displayImage = nullptr;
                }
            };
        };

        struct Font
        {
            stbtt_fontinfo fontInfo;
            unsigned char* fontData = nullptr;
            unsigned int offset = 0;

            Font(){};
            NOCOPY(Font);
            ~Font()
            {
                //Free fontdata if present (also called in texcomp dtor)
                if (fontData)
                {
                    stbi_image_free(fontData);
                    fontData = nullptr;
                }
            }
        };




        //Constructor
        //p_name: Name of the image with extension
        //p_imageCount: Number of images in the sheet
        //p_selectedImages: Indices of the images you wish to load from the sheet
        TextureComponent(Entity* entity, const std::string& p_name, const unsigned short int p_imageCount = 0u, const std::vector<unsigned char>& p_selectedImages = std::vector<unsigned char>());

        //Disabled copy-constructors
        NOCOPY(TextureComponent);

        //Destructor
        virtual ~TextureComponent();

        //Return texture data
        const TextureData& GetTextureData() const;

        //Return texture data
        TextureData& GetTextureData();

        //Add a displayable image
        //p_name: Name of the file with extension
        //p_images: Separate images in the file
        //p_pixelsInOne: Pixels in a single image (Images should be the same size in the file)
        bool AddImage(const std::string& p_name, const unsigned short int p_images, const Vector2i& p_pixelsInOne);

        //Add a displayable image
        //p_name: Name of the file with extension
        //p_startPixel: Upper left corner of an image you 
        //bool AddImage(const std::string& p_name, const Vector2i& p_startPixel)

    private:

        //Data of the read image
        TextureData m_textureData;

        //Data of the read font
        Font m_fontData;

        //Requested image data from the file
        unsigned char* m_completeImageData;

    };

}

#endif