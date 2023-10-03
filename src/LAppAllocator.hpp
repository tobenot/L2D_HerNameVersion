/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include <CubismFramework.hpp>
#include <ICubismAllocator.hpp>

 /**
 * @brief 实现内存分配的类。
 *
 * 实现内存分配和释放接口。
 * 由框架调用。
 *  
    这段代码定义了一个名为LAppAllocator的类，该类继承自Csm::ICubismAllocator接口。这个类主要用于实现内存分配和释放的功能，它由Live2D Cubism框架调用。
    Allocate函数：根据传入的size参数分配内存区域，并返回分配的内存区域。
    Deallocate函数：释放传入的memory参数所指向的内存区域。
    AllocateAligned函数：根据传入的size和alignment参数分配对齐的内存区域，并返回分配的内存区域。
    DeallocateAligned函数：释放传入的alignedMemory参数所指向的对齐内存区域。
 */
class LAppAllocator : public Csm::ICubismAllocator
{
    /**
    * @brief  分配内存区域。
    *
    * @param[in]   size    要分配的大小。
    * @return  指定的内存区域
    */
    void* Allocate(const Csm::csmSizeType size);

    /**
    * @brief   释放内存区域
    *
    * @param[in]   memory    要释放的内存。
    */
    void Deallocate(void* memory);

    /**
    * @brief
    *
    * @param[in]   size         要分配的大小。
    * @param[in]   alignment    要分配的对齐大小。
    * @return  alignedAddress
    */
    void* AllocateAligned(const Csm::csmSizeType size, const Csm::csmUint32 alignment);

    /**
    * @brief
    *
    * @param[in]   alignedMemory    要释放的内存。
    */
    void DeallocateAligned(void* alignedMemory);
};