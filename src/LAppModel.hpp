/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include <CubismFramework.hpp>
#include <Model/CubismUserModel.hpp>
#include <ICubismModelSetting.hpp>
#include <Type/csmRectF.hpp>
#include <Rendering/OpenGL/CubismOffscreenSurface_OpenGLES2.hpp>

#include "LAppWavFileHandler.hpp"

 /**
  * @brief 用户实际使用的模型实现类
  *         进行模型生成、功能组件生成、更新处理和渲染调用。
  
  这段代码定义了一个名为LAppModel的类，该类继承自Csm::CubismUserModel。这个类主要用于处理Live2D模型的加载、渲染、动画播放、表情设置以及碰撞检测等功能。

构造函数和析构函数用于初始化和销毁类的实例。
LoadAssets用于从指定的目录和文件名加载模型资源。
ReloadRenderer用于重建渲染器。
Update用于更新模型的状态。
Draw用于绘制模型。
StartMotion和StartRandomMotion用于播放指定或随机选择的动画。
SetExpression和SetRandomExpression用于设置指定或随机选择的表情。
MotionEventFired用于接收动画事件触发。
HitTest用于进行碰撞检测。
GetRenderBuffer用于获取绘制缓冲区。
HasMocConsistencyFromFile用于检查.moc3文件的一致性。
另外，还有一些私有方法和成员变量，用于在类内部处理模型的加载、纹理设置、动画和表情的加载与释放等功能。

  */
class LAppModel : public Csm::CubismUserModel
{
public:
    /**
     * @brief 构造函数
     */
    LAppModel();

    /**
     * @brief 析构函数
     *
     */
    virtual ~LAppModel();

    /**
     * @brief 从model3.json所在目录和文件路径创建模型
     *
     */
    void LoadAssets(const Csm::csmChar* dir, const  Csm::csmChar* fileName);

    /**
     * @brief 重建渲染器
     *
     */
    void ReloadRenderer();

    /**
     * @brief 更新模型处理。从模型参数确定绘制状态。
     *
     */
    void Update();

    /**
     * @brief 绘制模型处理。传递绘制模型空间的View-Projection矩阵。
     *
     * @param[in]  matrix  View-Projection矩阵
     */
    void Draw(Csm::CubismMatrix44& matrix);

    /**
     * @brief 开始播放指定的动作。
     *
     * @param[in]   group                       动作组名
     * @param[in]   no                          组内编号
     * @param[in]   priority                    优先级
     * @param[in]   onFinishedMotionHandler     动作播放结束时调用的回调函数。如果为NULL，则不调用。
     * @return                                  返回开始的动作的识别号。用于判断单个动作是否结束的IsFinished()参数。如果无法开始，则返回“-1”
     */
    Csm::CubismMotionQueueEntryHandle StartMotion(const Csm::csmChar* group, Csm::csmInt32 no, Csm::csmInt32 priority, Csm::ACubismMotion::FinishedMotionCallback onFinishedMotionHandler = NULL);

    /**
     * @brief 开始播放随机选择的动作。
     *
     * @param[in]   group                       动作组名
     * @param[in]   priority                    优先级
     * @param[in]   onFinishedMotionHandler     动作播放结束时调用的回调函数。如果为NULL，则不调用。
     * @return                                  返回开始的动作的识别号。用于判断单个动作是否结束的IsFinished()参数。如果无法开始，则返回“-1”
     */
    Csm::CubismMotionQueueEntryHandle StartRandomMotion(const Csm::csmChar* group, Csm::csmInt32 priority, Csm::ACubismMotion::FinishedMotionCallback onFinishedMotionHandler = NULL);

    /**
     * @brief 设置指定的表情动作
     *
     * @param   expressionID    表情动作的ID
     */
    void SetExpression(const Csm::csmChar* expressionID);

    /**
     * @brief 设置随机选择的表情动作
     *
     */
    void SetRandomExpression();

    /**
    * @brief 接收事件触发
    *
    */
    virtual void MotionEventFired(const Live2D::Cubism::Framework::csmString& eventValue);

    /**
     * @brief 碰撞检测测试。
     *            计算指定ID的顶点列表的矩形，判断坐标是否在矩形范围内。
     *
     * @param[in]   hitAreaName     要测试的碰撞检测目标ID
     * @param[in]   x               要进行判断的X坐标
     * @param[in]   y               要进行判断的Y坐标
     */
    virtual Csm::csmBool HitTest(const Csm::csmChar* hitAreaName, Csm::csmFloat32 x, Csm::csmFloat32 y);

    /**
     * @brief 获取用于绘制到其他目标的缓冲区
     */
    Csm::Rendering::CubismOffscreenFrame_OpenGLES2& GetRenderBuffer();

    /**
     * @brief 检查.moc3文件的一致性
     *
     * @param[in]   mocName MOC3文件名
     * @return      如果MOC3文件具有一致性，则返回'true'，否则返回'false'。
     */
    Csm::csmBool HasMocConsistencyFromFile(const Csm::csmChar* mocFileName);

protected:
    /**
     *  @brief  绘制模型处理。传递绘制模型空间的View-Projection矩阵。
     *
     */
    void DoDraw();

private:
    /**
     * @brief 从model3.json创建模型。
     *         根据model3.json的描述创建模型、动作、物理运算等组件。
     *
     * @param[in]   setting     ICubismModelSetting的实例
     *
     */
    void SetupModel(Csm::ICubismModelSetting* setting);

    /**
     * @brief 将纹理加载到OpenGL的纹理单元
     *
     */
    void SetupTextures();

    /**
     * @brief 从组名一次性加载动作数据。
     *           动作数据的名称在内部从ModelSetting获取。
     *
     * @param[in]   group  动作数据的组名
     */
    void PreloadMotionGroup(const Csm::csmChar* group);

    /**
     * @brief 从组名一次性释放动作数据。
     *           动作数据的名称在内部从ModelSetting获取。
     *
     * @param[in]   group  动作数据的组名
     */
    void ReleaseMotionGroup(const Csm::csmChar* group) const;

    /**
    * @brief 释放所有动作数据
    *
    * 释放所有动作数据。
    */
    void ReleaseMotions();

    /**
    * @brief 释放所有表情数据
    *
    * 释放所有表情数据。
    */
    void ReleaseExpressions();

    Csm::ICubismModelSetting* _modelSetting; ///< 模型设置信息
    Csm::csmString _modelHomeDir; ///< 模型设置所在目录
    Csm::csmFloat32 _userTimeSeconds; ///< 累积的时间增量（秒）
    Csm::csmVector<Csm::CubismIdHandle> _eyeBlinkIds; ///< 模型中设置的眨眼功能参数ID
    Csm::csmVector<Csm::CubismIdHandle> _lipSyncIds; ///< 模型中设置的唇形同步功能参数ID
    Csm::csmMap<Csm::csmString, Csm::ACubismMotion*>   _motions; ///< 已加载的动作列表
    Csm::csmMap<Csm::csmString, Csm::ACubismMotion*>   _expressions; ///< 已加载的表情列表
    Csm::csmVector<Csm::csmRectF> _hitArea;
    Csm::csmVector<Csm::csmRectF> _userArea;
    const Csm::CubismId* _idParamAngleX; ///< 参数ID: ParamAngleX
    const Csm::CubismId* _idParamAngleY; ///< 参数ID: ParamAngleY
    const Csm::CubismId* _idParamAngleZ; ///< 参数ID: ParamAngleZ
    const Csm::CubismId* _idParamBodyAngleX; ///< 参数ID: ParamBodyAngleX
    const Csm::CubismId* _idParamEyeBallX; ///< 参数ID: ParamEyeBallX
    const Csm::CubismId* _idParamEyeBallY; ///< 参数ID: ParamEyeBallY

    LAppWavFileHandler _wavFileHandler; ///< wav文件处理器

    Csm::Rendering::CubismOffscreenFrame_OpenGLES2  _renderBuffer;   ///< 用于非帧缓冲区的绘制目标
};
