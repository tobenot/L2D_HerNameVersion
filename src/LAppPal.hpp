/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include <CubismFramework.hpp>
#include <string>

 /**
 * @brief Cubism Platform Abstraction Layer，用于抽象平台依赖功能。
 *
 * 整合了文件读取、时间获取等与平台相关的功能
 
 这段代码是一个名为 LAppPal 的类定义，它是一个 Cubism Platform Abstraction Layer，用于抽象平台依赖功能，例如文件读取、时间获取等。

类中包含以下成员函数：

LoadFileAsBytes：以字节数据形式读取文件。输入参数为文件路径，输出参数为文件大小，返回值为字节数据。

ReleaseBytes：释放字节数据。输入参数为要释放的字节数据。

GetDeltaTime：获取与上一帧的时间差。返回值为时间差（毫秒）。

UpdateTime：更新时间。

PrintLog：输出日志。输入参数为格式化字符串和可变参数。

PrintMessage：输出消息。输入参数为字符串。

类中还包含三个静态私有成员变量：s_currentFrame、s_lastFrame 和 s_deltaTime，用于存储当前帧、上一帧和时间差。

 */
class LAppPal
{
public:
    /**
    * @brief 以字节数据形式读取文件
    *
    * 以字节数据形式读取文件
    *
    * @param[in]   filePath    要读取的目标文件的路径
    * @param[out]  outSize     文件大小
    * @return                  字节数据
    */
    static Csm::csmByte* LoadFileAsBytes(const std::string filePath, Csm::csmSizeInt* outSize);


    /**
    * @brief 释放字节数据
    *
    * 释放字节数据
    *
    * @param[in]   byteData    要释放的字节数据
    */
    static void ReleaseBytes(Csm::csmByte* byteData);

    /**
    * @brief 获取与上一帧的时间差
    *
    * @return  时间差[ms]
    *
    */
    static Csm::csmFloat32 GetDeltaTime();

    static void UpdateTime();

    /**
    * @brief 输出日志
    *
    * 输出日志
    *
    * @param[in]   format  格式化字符串
    * @param[in]   ...     (可变参数)字符串
    *
    */
    static void PrintLog(const Csm::csmChar* format, ...);

    /**
    * @brief 输出消息
    *
    * 输出消息
    *
    * @param[in]   message  字符串
    *
    */
    static void PrintMessage(const Csm::csmChar* message);

private:
    static double s_currentFrame;
    static double s_lastFrame;
    static double s_deltaTime;
};