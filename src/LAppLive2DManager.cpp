/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "LAppLive2DManager.hpp"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Rendering/CubismRenderer.hpp>
#include "LAppPal.hpp"
#include "LAppDefine.hpp"
#include "LAppDelegate.hpp"
#include "LAppModel.hpp"
#include "LAppView.hpp"

/*

这段代码是 Live2D 示例项目中的 LAppLive2DManager 类，主要负责管理和操作模型。以下是代码的主要功能解释：

FinishedMotion 函数：动作完成时的回调函数。
GetInstance 函数：获取 LAppLive2DManager 类的单例实例。
ReleaseInstance 函数：释放 LAppLive2DManager 类的单例实例。
LAppLive2DManager 构造函数：初始化视图矩阵和场景索引。
LAppLive2DManager 析构函数：释放所有模型。
ReleaseAllModel 函数：释放所有模型。
GetModel 函数：获取指定编号的模型。
OnDrag 函数：处理拖拽事件，设置模型的拖拽状态。
OnTap 函数：处理点击事件，判断点击区域并执行相应操作（如设置随机表情或启动随机动作）。
OnUpdate 函数：更新模型的状态并进行绘制。
NextScene 函数：切换到下一个场景。
ChangeScene 函数：根据给定的索引更改场景，加载对应的模型并设置渲染目标。
GetModelNum 函数：获取当前模型的数量。
SetViewMatrix 函数：设置视图矩阵。

*/

using namespace Csm;
using namespace LAppDefine;
using namespace std;

namespace
{
    LAppLive2DManager* s_instance = NULL;

    // 动作完成时的回调函数
    void FinishedMotion(ACubismMotion* self)
    {
        LAppPal::PrintLog("Motion Finished: %x", self);
    }
}

// 获取 LAppLive2DManager 实例
LAppLive2DManager* LAppLive2DManager::GetInstance()
{
    if (s_instance == NULL)
    {
        s_instance = new LAppLive2DManager();
    }

    return s_instance;
}

// 释放 LAppLive2DManager 实例
void LAppLive2DManager::ReleaseInstance()
{
    if (s_instance != NULL)
    {
        delete s_instance;
    }

    s_instance = NULL;
}

// LAppLive2DManager 构造函数
LAppLive2DManager::LAppLive2DManager()
    : _viewMatrix(NULL)
    , _sceneIndex(0)
{
    _viewMatrix = new CubismMatrix44();

    ChangeScene(_sceneIndex);
}

// LAppLive2DManager 析构函数
LAppLive2DManager::~LAppLive2DManager()
{
    ReleaseAllModel();
}

// 释放所有模型
void LAppLive2DManager::ReleaseAllModel()
{
    for (csmUint32 i = 0; i < _models.GetSize(); i++)
    {
        delete _models[i];
    }

    _models.Clear();
}

// 获取指定编号的模型
LAppModel* LAppLive2DManager::GetModel(csmUint32 no) const
{
    if (no < _models.GetSize())
    {
        return _models[no];
    }

    return NULL;
}

// 处理拖拽事件
void LAppLive2DManager::OnDrag(csmFloat32 x, csmFloat32 y) const
{
    for (csmUint32 i = 0; i < _models.GetSize(); i++)
    {
        LAppModel* model = GetModel(i);

        model->SetDragging(x, y);
    }
}

// 处理点击事件
void LAppLive2DManager::OnTap(csmFloat32 x, csmFloat32 y)
{
    if (DebugLogEnable)
    {
        LAppPal::PrintLog("[APP]tap point: {x:%.2f y:%.2f}", x, y);
    }

    for (csmUint32 i = 0; i < _models.GetSize(); i++)
    {
        if (_models[i]->HitTest(HitAreaNameHead, x, y))
        {
            if (DebugLogEnable)
            {
                LAppPal::PrintLog("[APP]hit area: [%s]", HitAreaNameHead);
            }
            _models[i]->SetRandomExpression();
        }
        else if (_models[i]->HitTest(HitAreaNameBody, x, y))
        {
            if (DebugLogEnable)
            {
                LAppPal::PrintLog("[APP]hit area: [%s]", HitAreaNameBody);
            }
            _models[i]->StartRandomMotion(MotionGroupTapBody, PriorityNormal, FinishedMotion);
        }
    }
}
void LAppLive2DManager::OnUpdate() const
{
    // 缩放屏幕大小？
    int width, height;
    glfwGetWindowSize(LAppDelegate::GetInstance()->GetWindow(), &width, &height);

    csmUint32 modelCount = _models.GetSize();
    for (csmUint32 i = 0; i < modelCount; ++i)
    {
        CubismMatrix44 projection;
        LAppModel* model = GetModel(i);

        if (model->GetModel() == NULL)
        {
            LAppPal::PrintLog("Failed to model->GetModel().");
            continue;
        }

        if (model->GetModel()->GetCanvasWidth() > 1.0f && width < height)
        {
            // 当模型宽度大于1且窗口高度大于宽度时，以模型宽度为基准进行缩放
            model->GetModelMatrix()->SetWidth(2.0f);
            projection.Scale(1.0f, static_cast<float>(width) / static_cast<float>(height));
        }
        else
        {
            projection.Scale(static_cast<float>(height) / static_cast<float>(width), 1.0f);
        }

        // 对模型大小的修改
        // 在这里添加平移操作，向上移动模型，只显示半身
        model->GetModelMatrix()->TranslateY(ModelFix[_sceneIndex][0]);
        
        // 放大模型2倍
        model->GetModelMatrix()->Scale(ModelFix[_sceneIndex][1], ModelFix[_sceneIndex][2]);

        // 如果需要，可以在这里进行矩阵乘法
        if (_viewMatrix != NULL)
        {
            projection.MultiplyByMatrix(_viewMatrix);
        }

        // 模型绘制前调用
        LAppDelegate::GetInstance()->GetView()->PreModelDraw(*model);

        model->Update();
        model->Draw(projection); // 传递引用，projection会发生变化

        // 模型绘制后调用
        LAppDelegate::GetInstance()->GetView()->PostModelDraw(*model);
    }
}

void LAppLive2DManager::NextScene()
{
    csmInt32 no = (_sceneIndex + 1) % ModelDirSize;
    ChangeScene(no);
}

void LAppLive2DManager::ChangeScene(Csm::csmInt32 index)
{
    _sceneIndex = index;
    if (DebugLogEnable)
    {
        LAppPal::PrintLog("[APP]model index: %d", _sceneIndex);
    }

    // 根据ModelDir[]中保存的目录名确定
    // model3.json的路径。
    // 请确保目录名与model3.json的名称相匹配。
    std::string model = ModelDir[index];
    std::string modelPath = ResourcesPath + model + "/";
    std::string modelJsonName = ModelDir[index];
    modelJsonName += ".model3.json";

    ReleaseAllModel();
    _models.PushBack(new LAppModel());
    _models[0]->LoadAssets(modelPath.c_str(), modelJsonName.c_str());

    // 显示半透明模型的示例。
    {
#if defined(USE_RENDER_TARGET)
        // 如果要在LAppView的目标上进行绘制，请选择此选项
        LAppView::SelectTarget useRenderTarget = LAppView::SelectTarget_ViewFrameBuffer;
#elif defined(USE_MODEL_RENDER_TARGET)
        // 如果要在每个LAppModel的目标上进行绘制，请选择此选项
        LAppView::SelectTarget useRenderTarget = LAppView::SelectTarget_ModelFrameBuffer;
#else
        // 默认渲染到主帧缓冲区（通常）
        LAppView::SelectTarget useRenderTarget = LAppView::SelectTarget_None;
#endif

#if defined(USE_RENDER_TARGET) || defined(USE_MODEL_RENDER_TARGET)
        // 作为一个示例，为每个模型分配α值，创建另一个模型，并稍微移动位置
        _models.PushBack(new LAppModel());
        _models[1]->LoadAssets(modelPath.c_str(), modelJsonName.c_str());
        _models[1]->GetModelMatrix()->TranslateX(0.2f);
#endif

        LAppDelegate::GetInstance()->GetView()->SwitchRenderingTarget(useRenderTarget);

        // 当选择其他渲染目标时的背景清除颜色
        float clearColor[3] = { 1.0f, 1.0f, 1.0f };
        LAppDelegate::GetInstance()->GetView()->SetRenderTargetClearColor(clearColor[0], clearColor[1], clearColor[2]);
    }
}

csmUint32 LAppLive2DManager::GetModelNum() const
{
    return _models.GetSize();
}

void LAppLive2DManager::SetViewMatrix(CubismMatrix44* m)
{
    for (int i = 0; i < 16; i++)
    {
        _viewMatrix->GetArray()[i] = m->GetArray()[i];
    }
}

Csm::CubismMotionQueueEntryHandle LAppLive2DManager::StartMotion(const Csm::csmChar* group, Csm::csmInt32 no, Csm::csmInt32 priority)
{
    Csm::CubismMotionQueueEntryHandle motionQueueEntryHandle = 0;
    for (csmUint32 i = 0; i < _models.GetSize(); i++)
    {
        motionQueueEntryHandle = _models[i]->StartMotion(group, no, priority);
    }
    return motionQueueEntryHandle;
}

Csm::CubismMotionQueueEntryHandle LAppLive2DManager::StartRandomMotion(const Csm::csmChar* group, Csm::csmInt32 priority)
{
    Csm::CubismMotionQueueEntryHandle motionQueueEntryHandle = 0;
    for (csmUint32 i = 0; i < _models.GetSize(); i++)
    {
        motionQueueEntryHandle = _models[i]->StartRandomMotion(group, priority);
    }
    return motionQueueEntryHandle;
}

void LAppLive2DManager::SetExpression(const Csm::csmChar* expressionID)
{
    for (csmUint32 i = 0; i < _models.GetSize(); i++)
    {
        _models[i]->SetExpression(expressionID);
    }
}

void LAppLive2DManager::SetRandomExpression()
{
    for (csmUint32 i = 0; i < _models.GetSize(); i++)
    {
        _models[i]->SetRandomExpression();
    }
}