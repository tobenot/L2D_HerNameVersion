/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

 /**
 * @brief 实现精灵的类。
 *
 * 管理纹理ID、Rect。

 这段代码定义了一个名为LAppSprite的类，用于实现精灵（二维图形对象）的功能。这个类包含了以下几个部分：

Rect结构体：用于表示精灵的矩形区域，包含左、右、上、下四个边的坐标。
构造函数：用于创建一个LAppSprite对象，需要提供x、y坐标，宽度、高度，纹理ID和着色器ID。
析构函数：用于销毁LAppSprite对象。
GetTextureId()方法：获取纹理ID。
Render()方法：绘制精灵。
RenderImmidiate()方法：使用指定的纹理ID和UV顶点立即绘制精灵。
IsHit()方法：检测给定的x和y坐标是否在精灵的矩形区域内。
SetColor()方法：设置精灵的颜色，需要提供红、绿、蓝、透明度

 */
class LAppSprite
{
public:
    /**
    * @brief Rect 结构体。
    */
    struct Rect
    {
    public:
        float left;     ///< 左边
        float right;    ///< 右边
        float up;       ///< 上边
        float down;     ///< 下边
    };

    /**
    * @brief 构造函数
    *
    * @param[in]       x            x坐标
    * @param[in]       y            y坐标
    * @param[in]       width        宽度
    * @param[in]       height       高度
    * @param[in]       textureId    纹理ID
    * @param[in]       programId    着色器ID
    */
    LAppSprite(float x, float y, float width, float height, GLuint textureId, GLuint programId);

    /**
    * @brief 析构函数
    */
    ~LAppSprite();

    /**
    * @brief Getter 纹理ID
    * @return 返回纹理ID
    */
    GLuint GetTextureId()
    {
        return _textureId;
    }

    /**
    * @brief 绘制
    *
    */
    void Render() const;

    /**
    * @brief 使用指定的纹理ID绘制
    *
    */
    void RenderImmidiate(GLuint textureId, const GLfloat uvVertex[8]) const;

    /**
    * @brief 构造函数
    *
    * @param[in]       pointX    x坐标
    * @param[in]       pointY    y坐标
    */
    bool IsHit(float pointX, float pointY) const;

    /**
     * @brief 设置颜色
     *
     * @param[in]       r (0.0~1.0)
     * @param[in]       g (0.0~1.0)
     * @param[in]       b (0.0~1.0)
     * @param[in]       a (0.0~1.0)
     */
    void SetColor(float r, float g, float b, float a);

    /**
     * @brief 重新设置大小
     *
     * @param[in]       x            x坐标
     * @param[in]       y            y坐标
     * @param[in]       width        宽度
     * @param[in]       height       高度
     */
    void ResetRect(float x, float y, float width, float height);

private:
    GLuint _textureId;      ///< 纹理ID
    Rect _rect;             ///< 矩形
    int _positionLocation;  ///< 位置属性
    int _uvLocation;        ///< UV属性
    int _textureLocation;   ///< 纹理属性
    int _colorLocation;     ///< 颜色属性

    float _spriteColor[4];  ///< 显示颜色
};
