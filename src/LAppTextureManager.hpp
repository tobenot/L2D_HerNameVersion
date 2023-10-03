/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Type/csmVector.hpp>

 /**
 * @brief 纹理管理类
 *
 * 图像读取、管理类。
 * 
 这段代码定义了一个名为LAppTextureManager的纹理管理类。这个类主要负责图像的读取和管理。以下是代码的详细解释：

struct TextureInfo：定义了一个包含纹理ID、宽度、高度和文件名的图像信息结构体。

LAppTextureManager()：类的构造函数。

~LAppTextureManager()：类的析构函数。

Premultiply()：预乘处理函数，用于处理图像的Red、Green、Blue和Alpha值，返回预乘处理后的颜色值。

CreateTextureFromPngFile()：从PNG文件创建纹理，传入文件路径名，返回图像信息结构体。如果读取失败，返回NULL。

ReleaseTextures()：释放数组中的所有图像。

ReleaseTexture(Csm::csmUint32 textureId)：释放指定纹理ID的图像。

ReleaseTexture(std::string fileName)：释放指定名称的图像。

GetTextureInfoById(GLuint textureId) const：根据纹理ID获取纹理信息。如果纹理存在，则返回TextureInfo结构体。

_textures：私有成员变量，用于存储纹理信息结构体的数组
 */
class LAppTextureManager
{
public:

    /**
    * @brief 图像信息结构体
    */
    struct TextureInfo
    {
        GLuint id;              ///< 纹理ID
        int width;              ///< 宽度
        int height;             ///< 高度
        std::string fileName;   ///< 文件名
    };

    /**
    * @brief 构造函数
    */
    LAppTextureManager();

    /**
    * @brief 析构函数
    *
    */
    ~LAppTextureManager();


    /**
    * @brief 预乘处理
    *
    * @param[in] red  图像的Red值
    * @param[in] green  图像的Green值
    * @param[in] blue  图像的Blue值
    * @param[in] alpha  图像的Alpha值
    *
    * @return 预乘处理后的颜色值
    */
    inline unsigned int Premultiply(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
    {
        return static_cast<unsigned>(\
            (red * (alpha + 1) >> 8) | \
            ((green * (alpha + 1) >> 8) << 8) | \
            ((blue * (alpha + 1) >> 8) << 16) | \
            (((alpha)) << 24)   \
            );
    }

    /**
    * @brief 读取图像
    *
    * @param[in] fileName  读取的图像文件路径名
    * @return 图像信息。读取失败时返回NULL
    */
    TextureInfo* CreateTextureFromPngFile(std::string fileName);

    /**
    * @brief 释放图像
    *
    * 释放数组中的所有图像
    */
    void ReleaseTextures();

    /**
     * @brief 释放图像
     *
     * 释放指定纹理ID的图像
     * @param[in] textureId  要释放的纹理ID
     **/
    void ReleaseTexture(Csm::csmUint32 textureId);

    /**
    * @brief 释放图像
    *
    * 释放指定名称的图像
    * @param[in] fileName  要释放的图像文件路径名
    **/
    void ReleaseTexture(std::string fileName);

    /**
     * @brief 根据纹理ID获取纹理信息
     *
     * @param   textureId[in]       要获取的纹理ID
     * @return  如果纹理存在，则返回TextureInfo
     */
    TextureInfo* GetTextureInfoById(GLuint textureId) const;

private:
    Csm::csmVector<TextureInfo*> _textures;
};