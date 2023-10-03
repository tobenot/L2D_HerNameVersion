/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Math/CubismMatrix44.hpp>
#include <Math/CubismViewMatrix.hpp>
#include "CubismFramework.hpp"
#include <Rendering/OpenGL/CubismOffscreenSurface_OpenGLES2.hpp>

class TouchManager;
class LAppSprite;
class LAppModel;

/**
* @brief 绘制类
* 
* 
这是一个名为LAppView的绘制类，它负责处理模型的绘制、触摸事件以及渲染目标的切换等。

类中的枚举类型SelectTarget定义了渲染的目标，包括默认的帧缓冲、LAppModel各自持有的帧缓冲和LAppView持有的帧缓冲。

类中的成员函数包括初始化、绘制、处理触摸事件、坐标转换、在绘制模型之前和之后调用的函数、获取精灵的透明度、切换渲染目标以及设置非默认渲染目标的背景清除颜色等。

类中的成员变量包括触摸管理器、设备到屏幕的矩阵、view矩阵、着色器ID、背景图片、齿轮图片、电源图片、根据模式绘制的纹理、渲染目标的选择以及渲染目标的清除颜色等。
*/
class LAppView
{
public:

    /**
     * @brief LAppModel的渲染目标
     */
    enum SelectTarget
    {
        SelectTarget_None,                ///< 渲染到默认的帧缓冲
        SelectTarget_ModelFrameBuffer,    ///< 渲染到LAppModel各自持有的帧缓冲
        SelectTarget_ViewFrameBuffer,     ///< 渲染到LAppView持有的帧缓冲
    };

    /**
    * @brief 构造函数
    */
    LAppView();

    /**
    * @brief 析构函数
    */
    ~LAppView();

    /**
    * @brief 初始化。
    */
    void Initialize();

    /**
    * @brief 进行绘制。
    */
    void Render();

    /**
    * @brief 对图像进行初始化。
    */
    void InitializeSprite();

    /**
    * @brief 重新设置精灵系的大小
    */
    void ResizeSprite();

    /**
    * @brief 当触摸时调用。
    *
    * @param[in]       pointX            屏幕X坐标
    * @param[in]       pointY            屏幕Y坐标
    */
    void OnTouchesBegan(float pointX, float pointY) const;

    /**
    * @brief 当触摸时指针移动时调用。
    *
    * @param[in]       pointX            屏幕X坐标
    * @param[in]       pointY            屏幕Y坐标
    */
    void OnTouchesMoved(float pointX, float pointY) const;

    /**
    * @brief 当触摸结束时调用。
    *
    * @param[in]       pointX            屏幕X坐标
    * @param[in]       pointY            屏幕Y坐标
    */
    void OnTouchesEnded(float pointX, float pointY) const;

    /**
    * @brief 将X坐标转换为View坐标。
    *
    * @param[in]       deviceX            设备X坐标
    */
    float TransformViewX(float deviceX) const;

    /**
    * @brief 将Y坐标转换为View坐标。
    *
    * @param[in]       deviceY            设备Y坐标
    */
    float TransformViewY(float deviceY) const;

    /**
    * @brief 将X坐标转换为屏幕坐标。
    *
    * @param[in]       deviceX            设备X坐标
    */
    float TransformScreenX(float deviceX) const;

    /**
    * @brief 将Y坐标转换为屏幕坐标。
    *
    * @param[in]       deviceY            设备Y坐标
    */
    float TransformScreenY(float deviceY) const;

    /**
     * @brief   在绘制一个模型之前调用
     */
    void PreModelDraw(LAppModel& refModel);

    /**
     * @brief   在绘制一个模型之后调用
     */
    void PostModelDraw(LAppModel& refModel);

    /**
     * @brief   在将模型绘制到另一个渲染目标的示例中
     *           确定绘制时的α值
     */
    float GetSpriteAlpha(int assign) const;

    /**
     * @brief 切换渲染目标
     */
    void SwitchRenderingTarget(SelectTarget targetType);

    /**
     * @brief 设置渲染到非默认目标时的背景清除颜色
     * @param[in]   r   红色(0.0~1.0)
     * @param[in]   g   绿色(0.0~1.0)
     * @param[in]   b   蓝色(0.0~1.0)
     */
    void SetRenderTargetClearColor(float r, float g, float b);

private:
    TouchManager* _touchManager;                 ///< 触摸管理器
    Csm::CubismMatrix44* _deviceToScreen;    ///< 设备到屏幕的矩阵
    Csm::CubismViewMatrix* _viewMatrix;      ///< viewMatrix
    GLuint _programId;                       ///< 着色器ID
    LAppSprite* _back;                       ///< 背景图片
    LAppSprite* _gear;                       ///< 齿轮图片
    LAppSprite* _power;                      ///< 电源图片

    // 使用另一个渲染目标的方式时使用
    LAppSprite* _renderSprite;                                      ///< 根据模式绘制_renderBuffer的纹理
    Csm::Rendering::CubismOffscreenFrame_OpenGLES2 _renderBuffer;   ///< 根据模式将Cubism模型结果渲染到这里
    SelectTarget _renderTarget;     ///< 渲染目标的选择
    float _clearColor[4];           ///< 渲染目标的清除颜色
};