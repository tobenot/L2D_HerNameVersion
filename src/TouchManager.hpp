/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

/*

这段代码是一个名为 TouchManager 的类，它主要用于处理触摸事件。类中包含了一些公共方法，用于获取触摸事件的相关信息，如触摸点坐标、移动距离、缩放比例等。此外，还有一些私有方法，用于计算两点之间的距离和移动量。

公共方法：

TouchesBegan：触摸开始时的事件处理
TouchesMoved：触摸移动（拖拽）时的事件处理，分为单指和双指两种情况
GetFlickDistance：获取触摸滑动距离
私有方法：

CalculateDistance：计算两点之间的距离
CalculateMovingAmount：计算两个值的移动量

总结一下，这个 TouchManager 类主要用于处理触摸事件，包括触摸开始、移动（拖拽）等。类中的公共方法提供了获取触摸事件相关信息的功能，而私有方法则用于计算触摸事件中涉及的一些数值，如距离和移动量。通过这个类，可以方便地处理触摸事件，并根据需要获取相关信息。
*/
class TouchManager
{
public:

    TouchManager();

    float GetCenterX() const
    {
        return _lastX;
    }
    float GetCenterY() const
    {
        return _lastY;
    }
    float GetDeltaX() const
    {
        return _deltaX;
    }
    float GetDeltaY() const
    {
        return _deltaY;
    }
    float GetStartX() const
    {
        return _startX;
    }
    float GetStartY() const
    {
        return _startY;
    }
    float GetScale() const
    {
        return _scale;
    }
    float GetX() const
    {
        return _lastX;
    }
    float GetY() const
    {
        return _lastY;
    }
    float GetX1() const
    {
        return _lastX1;
    }
    float GetY1() const
    {
        return _lastY1;
    }
    float GetX2() const
    {
        return _lastX2;
    }
    float GetY2() const
    {
        return _lastY2;
    }
    bool IsSingleTouch() const
    {
        return _touchSingle;
    }
    bool IsFlickAvailable() const
    {
        return _flipAvailable;
    }
    void DisableFlick()
    {
        _flipAvailable = false;
    }

    // 触摸开始时的事件
    void TouchesBegan(float deviceX, float deviceY);

    // 拖拽时的事件
    void TouchesMoved(float deviceX, float deviceY);

    // 双指拖拽时的事件
    void TouchesMoved(float deviceX1, float deviceY1, float deviceX2, float deviceY2);

    // 计算触摸滑动距离
    float GetFlickDistance() const;

private:
    // 计算两点之间的距离
    float CalculateDistance(float x1, float y1, float x2, float y2) const;

    // 计算两个值的移动量
    float CalculateMovingAmount(float v1, float v2);

    float _startY;              // 触摸开始时的x坐标
    float _startX;              // 触摸开始时的y坐标
    float _lastX;               // 单指触摸时的x坐标
    float _lastY;               // 单指触摸时的y坐标
    float _lastX1;              // 双指触摸时第一个触点的x坐标
    float _lastY1;              // 双指触摸时第一个触点的y坐标
    float _lastX2;              // 双指触摸时第二个触点的x坐标
    float _lastY2;              // 双指触摸时第二个触点的y坐标
    float _lastTouchDistance;   // 两指触摸时两个触点之间的距离
    float _deltaX;              // x轴移动距离
    float _deltaY;              // y轴移动距离
    float _scale;               // 缩放比例
    bool _touchSingle;          // 是否单指触摸
    bool _flipAvailable;        // 是否可以翻转

};