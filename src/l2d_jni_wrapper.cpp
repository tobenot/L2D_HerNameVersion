#include "LAppDelegate.hpp"
#include "LAppLive2DManager.hpp"
#include "l2d_l2dTestMain.h"

// 新增的头文件
#include <string>
#include <jni.h>

// 工具函数：将jstring转换为std::string
std::string jstring2string(JNIEnv* env, jstring jStr)
{
    if (!jStr) return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray)env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t)env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char*)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

JNIEXPORT void JNICALL Java_l2d_Java2CPPDefine_initializeL2DApp
(JNIEnv*, jobject)
{
    if (LAppDelegate::GetInstance()->Initialize() != GL_FALSE)
    {
        LAppDelegate::GetInstance()->Run();
    }
}

JNIEXPORT void JNICALL Java_l2d_Java2CPPDefine_startMotion(JNIEnv* env, jobject obj, jstring group, jint no, jint priority, jobject onFinishedMotionHandler)
{
    std::string groupStr = jstring2string(env, group);
    LAppLive2DManager* live2DManager = LAppLive2DManager::GetInstance();
    live2DManager->StartMotion(groupStr.c_str(), no, priority);
    return;// live2DManager->StartMotion(groupStr.c_str(), no, priority); // 注意：这里暂时没有处理回调函数
}

JNIEXPORT void JNICALL Java_l2d_Java2CPPDefine_startRandomMotion(JNIEnv* env, jobject obj, jstring group, jint priority, jobject onFinishedMotionHandler)
{
    std::string groupStr = jstring2string(env, group);
    LAppLive2DManager* live2DManager = LAppLive2DManager::GetInstance();
    live2DManager->StartRandomMotion(groupStr.c_str(), priority);
    return;// live2DManager->StartRandomMotion(groupStr.c_str(), priority); // 注意：这里暂时没有处理回调函数
}

JNIEXPORT void JNICALL Java_l2d_Java2CPPDefine_setExpression(JNIEnv* env, jobject obj, jstring expressionID)
{
    std::string expressionIDStr = jstring2string(env, expressionID);
    LAppLive2DManager* live2DManager = LAppLive2DManager::GetInstance();
    live2DManager->SetExpression(expressionIDStr.c_str());
}

JNIEXPORT void JNICALL Java_l2d_Java2CPPDefine_setRandomExpression(JNIEnv* env, jobject obj)
{
    LAppLive2DManager* live2DManager = LAppLive2DManager::GetInstance();
    live2DManager->SetRandomExpression();
}