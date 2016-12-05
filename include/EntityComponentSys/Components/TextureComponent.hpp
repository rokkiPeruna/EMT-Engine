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
        friend class FileHandler;

    public:

        struct TextureData
        {
            std::string imageName = "";             //Texture filename with extension
            Vector2i wholeImageSize;                //Size of the whole image in pixels
            unsigned int imageCount = 0u;           //Number of images in the whole file
            unsigned char* displayImage = nullptr;  //Image to render
            unsigned int imageDataSize = 0u;        //Number of bytes of data
            GLuint m_textureID;                     //ID of the texture handled by OpenGL
            int imageOffset = 0;                    //Offset //TODO: Find out what does this thing do
            

            TextureData(){};
            NOCOPY(TextureData);
            ~TextureData()
            {
                //Free texture if present (also called in texcomp dtor)
                if (displayImage)
                {
                    delete[] displayImage;
                    displayImage = nullptr;
                }
            };
        };

        struct Font
        {
            stbtt_fontinfo fontInfo;
            unsigned char* fontData = nullptr;
            unsigned int fontDataSize = 0u;
            unsigned int fontOffset = 0;

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
        TextureComponent(Entity* entity);

        //Disabled copy-constructors
        NOCOPY(TextureComponent);

        //Destructor
        virtual ~TextureComponent();

        //  //Return texture data
        //  const TextureData& GetTextureDataRef() const;
        //
        //  //Return texture data
        //  TextureData& GetTextureDataRef();
        //
        //  const Font& GetFontRef() const;
        //
        //  Font& GetFontRef();

        //Adds a displayable image
        //Sets the image to be rendered
        //p_name: Name of the file with extension
        //p_images: Number of images in the file, defaults to whole file
        bool AddImage(const std::string& p_name, const unsigned short int p_imageCount = 0u);

        //Set selected image to be rendered
        //p_imageIndex: Index of the image in the sheet
        bool UseImage(const unsigned int p_imageIndex);

        //Add font to print characters
        //p_name: Name of the file with extension, currentlty only supports truetype fonts (.ttf)
        bool AddFont(const std::string& p_name);


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