/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include <CubismFramework.hpp>
#include <Math/CubismMatrix44.hpp>
#include <Type/csmVector.hpp>

class LAppModel;

/**
* @brief 在示例应用程序中管理CubismModel的类
*         进行模型生成和销毁、触摸事件处理、模型切换等操作。

这段代码是一个名为LAppLive2DManager的类，它在示例应用程序中管理CubismModel。这个类负责模型的生成和销毁、触摸事件处理、模型切换等操作。

主要功能如下：

GetInstance()：获取类的实例（单例模式），如果实例尚未创建，则在内部创建实例。
ReleaseInstance()：释放类的实例（单例模式）。
GetModel()：根据索引值获取当前场景中的模型。
ReleaseAllModel()：释放当前场景中的所有模型。
OnDrag()：处理屏幕拖动事件。
OnTap()：处理屏幕点击事件。
OnUpdate()：在更新屏幕时进行模型的更新处理和绘制处理。
NextScene()：切换到下一个场景，在示例应用程序中执行模型集切换操作。
ChangeScene()：根据索引值切换场景，在示例应用程序中执行模型集切换操作。
GetModelNum()：获取当前场景中的模型数量。
SetViewMatrix()：设置用于模型绘制的View矩阵。
类的私有成员包括：

_viewMatrix：用于模型绘制的View矩阵。
_models：模型实例的容器。
_sceneIndex：显示场景的索引值。
类的构造函数和析构函数为：

LAppLive2DManager()：构造函数，用于初始化类的实例。
~LAppLive2DManager()：析构函数，用于释放类的实例和相关资源。

*/
class LAppLive2DManager
{

public:
    /**
    * @brief   返回类的实例（单例）。如果实例尚未创建，将在内部创建实例。
    *
    * @return  类的实例
    */
    static LAppLive2DManager* GetInstance();

    /**
    * @brief   释放类的实例（单例）。
    *
    */
    static void ReleaseInstance();

    /**
    * @brief   返回当前场景持有的模型
    *
    * @param[in]   no  模型列表的索引值
    * @return      返回模型实例。如果索引值超出范围，则返回NULL。
    */
    LAppModel* GetModel(Csm::csmUint32 no) const;

    /**
    * @brief   释放当前场景持有的所有模型
    *
    */
    void ReleaseAllModel();

    /**
    * @brief   处理屏幕拖动事件
    *
    * @param[in]   x   屏幕的X坐标
    * @param[in]   y   屏幕的Y坐标
    */
    void OnDrag(Csm::csmFloat32 x, Csm::csmFloat32 y) const;

    /**
    * @brief   处理屏幕点击事件
    *
    * @param[in]   x   屏幕的X坐标
    * @param[in]   y   屏幕的Y坐标
    */
    void OnTap(Csm::csmFloat32 x, Csm::csmFloat32 y);

    /**
    * @brief   更新屏幕时的处理
    *          进行模型的更新处理和绘制处理
    */
    void OnUpdate() const;

    /**
    * @brief   切换到下一个场景
    *           在示例应用程序中，执行模型集切换操作。
    */
    void NextScene();

    /**
    * @brief   切换场景
    *           在示例应用程序中，执行模型集切换操作。
    */
    void ChangeScene(Csm::csmInt32 index);

    /**
     * @brief   获取模型数量
     * @return  持有模型数量
     */
    Csm::csmUint32 GetModelNum() const;

    /**
     * @brief   设置viewMatrix
     */
    void SetViewMatrix(Live2D::Cubism::Framework::CubismMatrix44* m);

private:
    /**
    * @brief  构造函数
    */
    LAppLive2DManager();

    /**
    * @brief  析构函数
    */
    virtual ~LAppLive2DManager();

    Csm::CubismMatrix44* _viewMatrix; ///< 用于模型绘制的View矩阵
    Csm::csmVector<LAppModel*>  _models; ///< 模型实例的容器
    Csm::csmInt32               _sceneIndex; ///< 显示场景的索引值
};