// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlimePBF.h"

#define LOCTEXT_NAMESPACE "FSlimePBFModule"

void FSlimePBFModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FSlimePBFModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSlimePBFModule, SlimePBF)

//TODO(2025.11.26)
/*
1. UpdateSurface()函数内增加对应位置的函数调用   √
2. 和Unity的对应一对一检查，*理解*    √
3. Surface中增加各项异性版本 (各向异性 covariance + Eigen 特征分解)  √
4. 增加Marching Cube算法  
5. Update函数以及HandleMouseInput
6. TickComponent（FixedUpdate）的调用要改   √
7. debug(drawgizmos) + render mode



TODO（2025.11.28）
1.继续完成Marching Cube 从new PrefixSum()的实现开始
2.Update函数以及HandleMouseInput
3.debug(drawgizmos) + render mode
4.Control和Bubble要逐行检查
*/