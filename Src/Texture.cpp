#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

FTexture::FTexture(std::string filename)
{
    glGenTextures(1,&Id);
    unsigned char* data = stbi_load( filename.c_str(), &width, &height, &channel,0);
    if(data)
    {
        GLenum format;
        if(channel ==1)
            format = GL_RED;
        else if(channel ==3)
            format =GL_RGB;
        else if(channel ==4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D,Id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        //设置纹理环绕模式，过滤模式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        
    }
    else
    {
        std::cout << "Texture failed to load at path: "  << std::endl;
        stbi_image_free(data);
    }

}
