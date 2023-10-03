/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */
#pragma once

#include <CubismFramework.hpp>

 /**
 * @brief  示例App中使用的常量
 *
 * 
    这段代码定义了一个名为LAppDefine的命名空间，其中包含了一系列在示例App中使用的常量。这些常量包括：
    视图缩放比例及其最大最小值
    逻辑
 */
namespace LAppDefine
{

    using namespace Csm;

    extern const csmFloat32 ViewScale;              ///< 缩放比例
    extern const csmFloat32 ViewMaxScale;           ///< 缩放比例的最大值
    extern const csmFloat32 ViewMinScale;           ///< 缩放比例的最小值

    extern const csmFloat32 ViewLogicalLeft;        ///< 逻辑视图坐标系的左边界值
    extern const csmFloat32 ViewLogicalRight;       ///< 逻辑视图坐标系的右边界值
    extern const csmFloat32 ViewLogicalBottom;      ///< 逻辑视图坐标系的下边界值
    extern const csmFloat32 ViewLogicalTop;         ///< 逻辑视图坐标系的上边界值

    extern const csmFloat32 ViewLogicalMaxLeft;     ///< 逻辑视图坐标系的左边界的最大值
    extern const csmFloat32 ViewLogicalMaxRight;    ///< 逻辑视图坐标系的右边界的最大值
    extern const csmFloat32 ViewLogicalMaxBottom;   ///< 逻辑视图坐标系的下边界的最大值
    extern const csmFloat32 ViewLogicalMaxTop;      ///< 逻辑视图坐标系的上边界的最大值

    extern const csmChar* ResourcesPath;            ///< 素材路径
    extern const csmChar* BackImageName;         ///< 背景图片文件
    extern const csmChar* GearImageName;         ///< 齿轮图片文件
    extern const csmChar* PowerImageName;        ///< 关闭按钮图片文件

    // 模型定义--------------------------------------------
    extern const csmChar* ModelDir[];               ///< 模型所在目录名的数组。请确保目录名与model3.json的名称相匹配。
    extern const csmInt32 ModelDirSize;             ///< 模型目录数组的大小

    // 与外部定义文件(json)保持一致
    extern const csmChar* MotionGroupIdle;          ///< 空闲时播放的动作列表
    extern const csmChar* MotionGroupTapBody;       ///< 点击身体时播放的动作列表

    // 与外部定义文件(json)保持一致
    extern const csmChar* HitAreaNameHead;          ///< 碰撞检测的[Head]标签
    extern const csmChar* HitAreaNameBody;          ///< 碰撞检测的[Body]标签

    // 动作优先级常量
    extern const csmInt32 PriorityNone;             ///< 动作优先级常量：0
    extern const csmInt32 PriorityIdle;             ///< 动作优先级常量：1
    extern const csmInt32 PriorityNormal;           ///< 动作优先级常量：2
    extern const csmInt32 PriorityForce;            ///< 动作优先级常量：3

    extern const csmBool MocConsistencyValidationEnable; ///< MOC3一致性验证功能的启用/禁用

    // 显示调试用日志
    extern const csmBool DebugLogEnable;            ///< 调试用日志显示的启用/禁用
    extern const csmBool DebugTouchLogEnable;       ///< 触摸处理的调试用日志显示的启用/禁用

    // 设置从Framework输出的日志级别
    extern const CubismFramework::Option::LogLevel CubismLoggingLevel;

    // 默认渲染目标尺寸
    extern const csmInt32 RenderTargetWidth;
    extern const csmInt32 RenderTargetHeight;
}