/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "LAppDelegate.hpp"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "LAppView.hpp"
#include "LAppPal.hpp"
#include "LAppDefine.hpp"
#include "LAppLive2DManager.hpp"
#include "LAppTextureManager.hpp"

/*
这段代码的含义如下：

LAppDelegate::Initialize() 函数用于初始化应用程序，包括初始化 GLFW、创建窗口、设置上下文、初始化 GLEW、设置纹理采样、设置透明度、注册回调函数、初始化 AppView 和 Cubism SDK。
LAppDelegate::Release() 函数用于释放应用程序资源，包括删除窗口、终止 GLFW、删除纹理管理器和视图、释放 LAppLive2DManager 实例以及释放 Cubism SDK。
LAppDelegate::Run() 函数是应用程序的主循环，负责处理窗口大小变化、更新时间、清除屏幕、更新绘制、交换缓冲以及处理事件。
LAppDelegate::InitializeCubism() 函数用于设置和初始化 Cubism SDK，加载模型以及初始化精灵。
其他辅助函数包括鼠标回调函数和创建着色器函数。总体来说，这段代码主要用于初始化、运行和释放基于 Live2D Cubism SDK 的应用程序。

OnMouseCallBack 函数处理鼠标点击事件，当按下鼠标左键时调用 _view->OnTouchesBegan，当松开鼠标左键时调用 _view->OnTouchesEnded。

另一个 OnMouseCallBack 函数处理鼠标移动事件，当鼠标移动时调用 _view->OnTouchesMoved。

CreateShader 函数创建一个着色器程序，包括编译顶点着色器和片段着色器，并将它们链接到一个程序对象。这个函数返回程序对象的 ID。

CheckShader 函数检查着色器是否编译成功，如果编译失败，它将输出错误日志并返回 false。
*/

using namespace Csm;
using namespace std;
using namespace LAppDefine;

namespace
{
    LAppDelegate* s_instance = NULL;
}

LAppDelegate* LAppDelegate::GetInstance()
{
    if (s_instance == NULL)
    {
        s_instance = new LAppDelegate();
    }

    return s_instance;
}

void LAppDelegate::ReleaseInstance()
{
    if (s_instance != NULL)
    {
        delete s_instance;
    }

    s_instance = NULL;
}

bool LAppDelegate::Initialize()
{
    if (DebugLogEnable)
    {
        LAppPal::PrintLog("START");
    }

    // 初始化 GLFW
    if (glfwInit() == GL_FALSE)
    {
        if (DebugLogEnable)
        {
            LAppPal::PrintLog("Can't initilize GLFW");
        }
        return GL_FALSE;
    }

    // 创建窗口
    _window = glfwCreateWindow(RenderTargetWidth, RenderTargetHeight, "WHAT YOU SEE", NULL, NULL);
    if (_window == NULL)
    {
        if (DebugLogEnable)
        {
            LAppPal::PrintLog("Can't create GLFW window.");
        }
        glfwTerminate();
        return GL_FALSE;
    }

    // 设置当前窗口的上下文
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        if (DebugLogEnable)
        {
            LAppPal::PrintLog("Can't initilize glew.");
        }
        glfwTerminate();
        return GL_FALSE;
    }

    //设置纹理采样
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //设置透明度
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //注册回调函数
    glfwSetMouseButtonCallback(_window, EventHandler::OnMouseCallBack);
    glfwSetCursorPosCallback(_window, EventHandler::OnMouseCallBack);

    // 记录窗口大小
    int width, height;
    glfwGetWindowSize(LAppDelegate::GetInstance()->GetWindow(), &width, &height);
    _windowWidth = width;
    _windowHeight = height;

    // 初始化 AppView
    _view->Initialize();

    // 初始化 Cubism SDK
    InitializeCubism();

    return GL_TRUE;
}

void LAppDelegate::Release()
{
    // 删除窗口
    glfwDestroyWindow(_window);

    glfwTerminate();

    delete _textureManager;
    delete _view;

    // 释放资源
    LAppLive2DManager::ReleaseInstance();

    // 释放 Cubism SDK
    CubismFramework::Dispose();
}

void LAppDelegate::Run()
{
    // 主循环
    while (glfwWindowShouldClose(_window) == GL_FALSE && !_isEnd)
    {
        int width, height;
        glfwGetWindowSize(LAppDelegate::GetInstance()->GetWindow(), &width, &height);
        if ((_windowWidth != width || _windowHeight != height) && width > 0 && height > 0)
        {
            // 初始化 AppView
            _view->Initialize();
            // 重新设置精灵大小
            _view->ResizeSprite();
            // 保存大小
            _windowWidth = width;
            _windowHeight = height;

            // 修改视口
            glViewport(0, 0, width, height);
        }

        // 更新时间
        LAppPal::UpdateTime();

        // 清除屏幕
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepth(1.0);

        // 更新绘制
        _view->Render();

        // 交换缓冲
        glfwSwapBuffers(_window);

        // 处理事件
        glfwPollEvents();
    }

    Release();

    LAppDelegate::ReleaseInstance();
}

LAppDelegate::LAppDelegate() :
    _cubismOption(),
    _window(NULL),
    _captured(false),
    _mouseX(0.0f),
    _mouseY(0.0f),
    _isEnd(false),
    _windowWidth(0),
    _windowHeight(0)
{
    _view = new LAppView();
    _textureManager = new LAppTextureManager();
}

LAppDelegate::~LAppDelegate()
{

}

void LAppDelegate::InitializeCubism()
{
    // 设置cubism
    _cubismOption.LogFunction = LAppPal::PrintMessage;
    _cubismOption.LoggingLevel = LAppDefine::CubismLoggingLevel;
    Csm::CubismFramework::StartUp(&_cubismAllocator, &_cubismOption);

    // 初始化cubism
    CubismFramework::Initialize();

    // 加载模型
    LAppLive2DManager::GetInstance();

    // 默认投影
    CubismMatrix44 projection;

    LAppPal::UpdateTime();

    _view->InitializeSprite();
}

void LAppDelegate::OnMouseCallBack(GLFWwindow* window, int button, int action, int modify)
{
    if (_view == NULL)
    {
        return;
    }
    if (GLFW_MOUSE_BUTTON_LEFT != button)
    {
        return;
    }

    // 当按下鼠标左键时
    if (GLFW_PRESS == action)
    {
        _captured = true;
        _view->OnTouchesBegan(_mouseX, _mouseY);
    }
    // 当松开鼠标左键时
    else if (GLFW_RELEASE == action)
    {
        if (_captured)
        {
            _captured = false;
            _view->OnTouchesEnded(_mouseX, _mouseY);
        }
    }
}

void LAppDelegate::OnMouseCallBack(GLFWwindow* window, double x, double y)
{
    _mouseX = static_cast<float>(x);
    _mouseY = static_cast<float>(y);

    if (!_captured)
    {
        return;
    }
    if (_view == NULL)
    {
        return;
    }

    _view->OnTouchesMoved(_mouseX, _mouseY);
}

GLuint LAppDelegate::CreateShader()
{
    // 编译顶点着色器
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShader =
        "#version 120\n"
        "attribute vec3 position;"
        "attribute vec2 uv;"
        "varying vec2 vuv;"
        "void main(void){"
        "    gl_Position = vec4(position, 1.0);"
        "    vuv = uv;"
        "}";
    glShaderSource(vertexShaderId, 1, &vertexShader, NULL);
    glCompileShader(vertexShaderId);
    if (!CheckShader(vertexShaderId))
    {
        return 0;
    }

    // 编译片段着色器
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShader =
        "#version 120\n"
        "varying vec2 vuv;"
        "uniform sampler2D texture;"
        "uniform vec4 baseColor;"
        "void main(void){"
        "    gl_FragColor = texture2D(texture, vuv) * baseColor;"
        "}";
    glShaderSource(fragmentShaderId, 1, &fragmentShader, NULL);
    glCompileShader(fragmentShaderId);
    if (!CheckShader(fragmentShaderId))
    {
        return 0;
    }

    // 创建程序对象
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    // 链接
    glLinkProgram(programId);

    glUseProgram(programId);

    return programId;
}

bool LAppDelegate::CheckShader(GLuint shaderId)
{
    GLint status;
    GLint logLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar* log = reinterpret_cast<GLchar*>(CSM_MALLOC(logLength));
        glGetShaderInfoLog(shaderId, logLength, &logLength, log);
        CubismLogError("Shader compile log: %s", log);
        CSM_FREE(log);
    }

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        glDeleteShader(shaderId);
        return false;
    }

    return true;
}