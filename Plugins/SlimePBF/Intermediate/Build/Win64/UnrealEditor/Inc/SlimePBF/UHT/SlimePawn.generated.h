// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SlimePawn.h"

#ifdef SLIMEPBF_SlimePawn_generated_h
#error "SlimePawn.generated.h already included, missing '#pragma once' in SlimePawn.h"
#endif
#define SLIMEPBF_SlimePawn_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ASlimePawn ***************************************************************
SLIMEPBF_API UClass* Z_Construct_UClass_ASlimePawn_NoRegister();

#define FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePawn_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASlimePawn(); \
	friend struct Z_Construct_UClass_ASlimePawn_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SLIMEPBF_API UClass* Z_Construct_UClass_ASlimePawn_NoRegister(); \
public: \
	DECLARE_CLASS2(ASlimePawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SlimePBF"), Z_Construct_UClass_ASlimePawn_NoRegister) \
	DECLARE_SERIALIZER(ASlimePawn)


#define FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePawn_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ASlimePawn(ASlimePawn&&) = delete; \
	ASlimePawn(const ASlimePawn&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASlimePawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASlimePawn); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASlimePawn) \
	NO_API virtual ~ASlimePawn();


#define FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePawn_h_12_PROLOG
#define FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePawn_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePawn_h_15_INCLASS_NO_PURE_DECLS \
	FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePawn_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ASlimePawn;

// ********** End Class ASlimePawn *****************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePawn_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
