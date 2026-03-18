// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SlimePBFManager.h"

#ifdef SLIMEPBF_SlimePBFManager_generated_h
#error "SlimePBFManager.generated.h already included, missing '#pragma once' in SlimePBFManager.h"
#endif
#define SLIMEPBF_SlimePBFManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class UWorld;

// ********** Begin Delegate FOnSlimeBubblePopped **************************************************
#define FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h_8_DELEGATE \
SLIMEPBF_API void FOnSlimeBubblePopped_DelegateWrapper(const FMulticastScriptDelegate& OnSlimeBubblePopped, FVector PopWorldPosition, float BubbleWorldRadius);


// ********** End Delegate FOnSlimeBubblePopped ****************************************************

// ********** Begin Class USlimePBFManager *********************************************************
#define FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnKeyR); \
	DECLARE_FUNCTION(execOnKeyP); \
	DECLARE_FUNCTION(execUpdateSimulation); \
	DECLARE_FUNCTION(execInitializeSimulation);


SLIMEPBF_API UClass* Z_Construct_UClass_USlimePBFManager_NoRegister();

#define FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSlimePBFManager(); \
	friend struct Z_Construct_UClass_USlimePBFManager_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SLIMEPBF_API UClass* Z_Construct_UClass_USlimePBFManager_NoRegister(); \
public: \
	DECLARE_CLASS2(USlimePBFManager, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SlimePBF"), Z_Construct_UClass_USlimePBFManager_NoRegister) \
	DECLARE_SERIALIZER(USlimePBFManager)


#define FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h_14_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	USlimePBFManager(USlimePBFManager&&) = delete; \
	USlimePBFManager(const USlimePBFManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USlimePBFManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USlimePBFManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USlimePBFManager)


#define FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h_11_PROLOG
#define FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h_14_INCLASS_NO_PURE_DECLS \
	FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class USlimePBFManager;

// ********** End Class USlimePBFManager ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
