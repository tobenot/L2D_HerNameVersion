#include "LAppDelegate.hpp"
#include "l2d_l2dTestMain.h"

JNIEXPORT void JNICALL Java_l2d_Java2CPPTest_initializeL2DApp
(JNIEnv*, jobject)
{
    if (LAppDelegate::GetInstance()->Initialize() != GL_FALSE)
    {
        LAppDelegate::GetInstance()->Run();
    }
}