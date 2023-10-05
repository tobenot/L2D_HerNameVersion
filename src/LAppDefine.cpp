/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */
#include "LAppDefine.hpp"
#include <CubismFramework.hpp>

namespace LAppDefine
{

    using namespace Csm;

    // 屏幕
    const csmFloat32 ViewScale = 1.0f;
    const csmFloat32 ViewMaxScale = 2.0f;
    const csmFloat32 ViewMinScale = 0.8f;

    const csmFloat32 ViewLogicalLeft = -1.0f;
    const csmFloat32 ViewLogicalRight = 1.0f;
    const csmFloat32 ViewLogicalBottom = -1.0f;
    const csmFloat32 ViewLogicalTop = -1.0f;

    const csmFloat32 ViewLogicalMaxLeft = -2.0f;
    const csmFloat32 ViewLogicalMaxRight = 2.0f;
    const csmFloat32 ViewLogicalMaxBottom = -2.0f;
    const csmFloat32 ViewLogicalMaxTop = 2.0f;

    // 相对路径
    const csmChar* ResourcesPath = "resources/";

    // 模型后面的背景图片文件
    const csmChar* BackImageName = "back_class_normal.png";
    // 齿轮图标
    const csmChar* GearImageName = "icon_gear.png";
    // 关闭按钮
    const csmChar* PowerImageName = "close.png";

    // 模型定义------------------------------------------
    // 模型所在目录名的数组
    // 保持目录名与model3.json的名称一致
    const csmChar* ModelDir[] = {
        "Mao"
    };
    const csmInt32 ModelDirSize = sizeof(ModelDir) / sizeof(const csmChar*);

    const float ModelFix[][3] = {
        {-0.65f, 2.2f, 2.2f},
    };

    // 与外部定义文件(json)保持一致
    const csmChar* MotionGroupIdle = "Idle"; // 空闲
    const csmChar* MotionGroupTapBody = "TapBody"; // 点击身体时

    // 与外部定义文件(json)保持一致
    const csmChar* HitAreaNameHead = "Head";
    const csmChar* HitAreaNameBody = "Body";

    // 动作优先级常量
    const csmInt32 PriorityNone = 0;
    const csmInt32 PriorityIdle = 1;
    const csmInt32 PriorityNormal = 2;
    const csmInt32 PriorityForce = 3;

    // MOC3文件的一致性验证选项
    const csmBool MocConsistencyValidationEnable = true;

    // 调试日志显示选项
    const csmBool DebugLogEnable = true;
    const csmBool DebugTouchLogEnable = false;

    // Framework输出的日志级别设置
    const CubismFramework::Option::LogLevel CubismLoggingLevel = CubismFramework::Option::LogLevel_Verbose;

    // 默认渲染目标尺寸
    const csmInt32 RenderTargetWidth = 900;
    const csmInt32 RenderTargetHeight = 900;
}