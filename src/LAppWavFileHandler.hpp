/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include <CubismFramework.hpp>
#include <Utils/CubismString.hpp>

 /**
  * @brief wav文件处理器
  * @attention 目前只实现了16位wav文件的读取
  * 
  这段代码定义了一个名为LAppWavFileHandler的类，用于处理wav文件。这个类包含了一些用于加载、读取和操作wav文件的方法，以及一些内部结构体用于存储文件信息和字节读取器。这个类主要用于读取16位wav文件，并可以获取当前的RMS值。
  */
class LAppWavFileHandler
{
public:
    /**
     * @brief 构造函数
     */
    LAppWavFileHandler();

    /**
     * @brief 析构函数
     */
    ~LAppWavFileHandler();

    /**
     * @brief 更新wav文件处理器的内部状态
     *
     * @param[in]   deltaTimeSeconds    增量时间[秒]
     * @retval  true    已更新
     * @retval  false   未更新
     */
    Csm::csmBool Update(Csm::csmFloat32 deltaTimeSeconds);

    /**
     * @brief 开始读取指定的wav文件
     *
     * @param[in] filePath wav文件的路径
     */
    void Start(const Csm::csmString& filePath);

    /**
     * @brief 获取当前的RMS值
     *
     * @retval  csmFloat32 RMS值
     */
    Csm::csmFloat32 GetRms() const;

private:
    /**
     * @brief 加载wav文件
     *
     * @param[in] filePath wav文件的路径
     * @retval  true    读取成功
     * @retval  false   读取失败
     */
    Csm::csmBool LoadWavFile(const Csm::csmString& filePath);

    /**
     * @brief 释放PCM数据
     */
    void ReleasePcmData();

    /**
     * @brief 获取-1～1范围的一个样本
     * @retval    csmFloat32    标准化的样本
     */
    Csm::csmFloat32 GetPcmSample();

    /**
     * @brief 读取的wav文件信息
     */
    struct WavFileInfo
    {
        /**
         * @brief 构造函数
         */
        WavFileInfo() : _fileName(""), _numberOfChannels(0),
            _bitsPerSample(0), _samplingRate(0), _samplesPerChannel(0)
        {
        }

        Csm::csmString _fileName; ///< 文件名
        Csm::csmUint32 _numberOfChannels; ///< 通道数
        Csm::csmUint32 _bitsPerSample; ///< 每个样本的位数
        Csm::csmUint32 _samplingRate; ///< 采样率
        Csm::csmUint32 _samplesPerChannel; ///< 每个通道的总样本数
    } _wavFileInfo;

    /**
     * @brief 字节读取器
     */
    struct ByteReader
    {
        /**
         * @brief 构造函数
         */
        ByteReader() : _fileByte(NULL), _fileSize(0), _readOffset(0)
        {
        }

        /**
         * @brief 读取8位
         * @return Csm::csmUint8 读取到的8位值
         */
        Csm::csmUint8 Get8()
        {
            const Csm::csmUint8 ret = _fileByte[_readOffset];
            _readOffset++;
            return ret;
        }

        /**
         * @brief 读取16位（小端）
         * @return Csm::csmUint16 读取到的16位值
         */
        Csm::csmUint16 Get16LittleEndian()
        {
            const Csm::csmUint16 ret = (_fileByte[_readOffset + 1] << 8) | _fileByte[_readOffset];
            _readOffset += 2;
            return ret;
        }

        /**
         * @brief 读取24位（小端）
         * @return Csm::csmUint32 读取到的24位值（设置在低24位）
         */
        Csm::csmUint32 Get24LittleEndian()
        {
            const Csm::csmUint32 ret =
                (_fileByte[_readOffset + 2] << 16) | (_fileByte[_readOffset + 1] << 8)
                | _fileByte[_readOffset];
            _readOffset += 3;
            return ret;
        }

        /**
 * @brief 读取32位（小端）
 * @return Csm::csmUint32 读取到的32位值
 */
        Csm::csmUint32 Get32LittleEndian()
        {
            const Csm::csmUint32 ret =
                (_fileByte[_readOffset + 3] << 24) | (_fileByte[_readOffset + 2] << 16)
                | (_fileByte[_readOffset + 1] << 8) | _fileByte[_readOffset];
            _readOffset += 4;
            return ret;
        }

        /**
         * @brief 获取签名并与参考字符串进行匹配检查
         * @param[in] reference 要检查的签名字符串
         * @retval  true    匹配
         * @retval  false   不匹配
         */
        Csm::csmBool GetCheckSignature(const Csm::csmString& reference)
        {
            Csm::csmChar getSignature[4] = { 0, 0, 0, 0 };
            const Csm::csmChar* referenceString = reference.GetRawString();
            if (reference.GetLength() != 4)
            {
                return false;
            }
            for (Csm::csmUint32 signatureOffset = 0; signatureOffset < 4; signatureOffset++)
            {
                getSignature[signatureOffset] = static_cast<Csm::csmChar>(Get8());
            }
            return (getSignature[0] == referenceString[0]) && (getSignature[1] == referenceString[1])
                && (getSignature[2] == referenceString[2]) && (getSignature[3] == referenceString[3]);
        }

        Csm::csmByte* _fileByte; ///< 加载的文件字节序列
        Csm::csmSizeInt _fileSize; ///< 文件大小
        Csm::csmUint32 _readOffset; ///< 文件读取位置
    } _byteReader;

    Csm::csmFloat32** _pcmData; ///< 表示音频数据数组的范围为-1到1
    Csm::csmUint32 _sampleOffset; ///< 样本读取位置
    Csm::csmFloat32 _lastRms; ///< 最后测量的RMS值
    Csm::csmFloat32 _userTimeSeconds; ///< 增量时间累积值[秒]
};