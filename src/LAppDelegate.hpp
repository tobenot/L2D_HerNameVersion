/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "LAppAllocator.hpp"

class LAppView;
class LAppTextureManager;

/**
* @brief   应用程序类。
*   管理Cubism SDK。
* 
这段代码定义了一个名为`LAppDelegate`的类，它负责管理Cubism SDK及应用程序的生命周期。这个类是一个单例类，意味着在整个应用程序中只有一个实例。类中包含了一些公共方法，如初始化、释放、运行、处理鼠标回调等，以及一些私有方法，如初始化Cubism SDK、检查着色器等。

此外，还定义了一个名为`EventHandler`的类，它包含了两个静态方法，用于处理鼠标事件的回调。

以下是`LAppDelegate`类的主要功能：

1. `GetInstance()` 和 `ReleaseInstance()` 方法分别用于获取和释放这个类的单例实例。
2. `Initialize()` 方法用于初始化应用程序所需的内容，如创建窗口、初始化Cubism SDK等。
3. `Release()` 方法用于释放资源。
4. `Run()` 方法用于执行应用程序的主循环。
5. `OnMouseCallBack()` 方法用于处理鼠标事件回调，如点击和光标移动。
6. `CreateShader()` 方法用于创建和注册着色器。
7. 一些 getter 方法用于获取窗口信息、视图信息、纹理管理器等。

`EventHandler` 类包含了两个静态方法，分别对应于 glfw 的鼠标事件回调函数。这些方法将回调的处理委托给 `LAppDelegate` 类的实例。
*/
class LAppDelegate
{
public:
    /**
    * @brief   返回类的实例（单例）。<br>
    *           如果实例尚未生成，则在内部生成实例。
    *
    * @return  类的实例
    */
    static LAppDelegate* GetInstance();

    /**
    * @brief   释放类的实例（单例）。
    *
    */
    static void ReleaseInstance();

    /**
    * @brief   初始化APP所需的内容。
    */
    bool Initialize();

    /**
    * @brief   释放。
    */
    void Release();

    /**
    * @brief   执行处理。
    */
    void Run();

    /**
    * @brief   用于OpenGL的glfwSetMouseButtonCallback函数。
    *
    * @param[in]       window            调用回调的窗口信息
    * @param[in]       button            按钮类型
    * @param[in]       action            执行结果
    * @param[in]       modify
    */
    void OnMouseCallBack(GLFWwindow* window, int button, int action, int modify);

    /**
    * @brief   用于OpenGL的glfwSetCursorPosCallback函数。
    *
    * @param[in]       window            调用回调的窗口信息
    * @param[in]       x                 x坐标
    * @param[in]       y                 y坐标
    */
    void OnMouseCallBack(GLFWwindow* window, double x, double y);

    /**
    * @brief 注册着色器。
    */
    GLuint CreateShader();

    /**
    * @brief   获取窗口信息。
    */
    GLFWwindow* GetWindow()
    {
        return _window;
    }

    /**
    * @brief   获取视图信息。
    */
    LAppView* GetView()
    {
        return _view;
    }

    /**
    * @brief   是否结束应用程序。
    */
    bool GetIsEnd()
    {
        return _isEnd;
    }

    /**
    * @brief   结束应用程序。
    */
    void AppEnd()
    {
        _isEnd = true;
    }

    LAppTextureManager* GetTextureManager()
    {
        return _textureManager;
    }

private:
    /**
    * @brief   构造函数
    */
    LAppDelegate();

    /**
    * @brief   析构函数
    */
    ~LAppDelegate();

    /**
    * @brief   初始化Cubism SDK。
    */
    void InitializeCubism();

    /**
     * @brief   CreateShader内部函数 错误检查
     */
    bool CheckShader(GLuint shaderId);

    LAppAllocator _cubismAllocator;              ///< Cubism SDK 分配器
    Csm::CubismFramework::Option _cubismOption;  ///< Cubism SDK 选项
    GLFWwindow* _window;                         ///< OpenGL 窗口
    LAppView* _view;                             ///< 视图信息
    bool _captured;                              ///< 是否点击
    float _mouseX;                               ///< 鼠标X坐标
    float _mouseY;                               ///< 鼠标Y坐标
    bool _isEnd;                                 ///< APP是否结束
    LAppTextureManager* _textureManager;         ///< 纹理管理器

    int _windowWidth;                            ///< Initialize函数设置的窗口宽度
    int _windowHeight;                           ///< Initialize函数设置的窗口高度
};

class EventHandler
{
public:
    /**
    * @brief   glfwSetMouseButtonCallback用回调函数。
    */
    static void OnMouseCallBack(GLFWwindow* window, int button, int action, int modify)
    {
        LAppDelegate::GetInstance()->OnMouseCallBack(window, button, action, modify);
    }

    /**
    * @brief   glfwSetCursorPosCallback用回调函数。
    */
    static void OnMouseCallBack(GLFWwindow* window, double x, double y)
    {
        LAppDelegate::GetInstance()->OnMouseCallBack(window, x, y);
    }

};