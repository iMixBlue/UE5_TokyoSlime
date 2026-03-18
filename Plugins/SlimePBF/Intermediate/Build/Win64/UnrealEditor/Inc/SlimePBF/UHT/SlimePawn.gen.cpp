// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SlimePawn.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSlimePawn() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_APawn();
ENGINE_API UClass* Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
SLIMEPBF_API UClass* Z_Construct_UClass_ASlimePawn();
SLIMEPBF_API UClass* Z_Construct_UClass_ASlimePawn_NoRegister();
SLIMEPBF_API UClass* Z_Construct_UClass_USlimePBFInstancedMeshComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_SlimePBF();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASlimePawn ***************************************************************
void ASlimePawn::StaticRegisterNativesASlimePawn()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASlimePawn;
UClass* ASlimePawn::GetPrivateStaticClass()
{
	using TClass = ASlimePawn;
	if (!Z_Registration_Info_UClass_ASlimePawn.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SlimePawn"),
			Z_Registration_Info_UClass_ASlimePawn.InnerSingleton,
			StaticRegisterNativesASlimePawn,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_ASlimePawn.InnerSingleton;
}
UClass* Z_Construct_UClass_ASlimePawn_NoRegister()
{
	return ASlimePawn::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASlimePawn_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "SlimePawn.h" },
		{ "ModuleRelativePath", "Public/SlimePawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SphereComponent_MetaData[] = {
		{ "Category", "Slime" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd ---\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/SlimePawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd ---" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SlimePBFComponent_MetaData[] = {
		{ "Category", "Slime" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/SlimePawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveSpeed_MetaData[] = {
		{ "Category", "Slime Control" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- \xef\xbf\xbd\xc6\xb6\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Public/SlimePawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- \xef\xbf\xbd\xc6\xb6\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpForce_MetaData[] = {
		{ "Category", "Slime Control" },
		{ "ModuleRelativePath", "Public/SlimePawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EyeInstancedMeshComp_MetaData[] = {
		{ "Category", "Slime" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xd7\xa8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc8\xbe\xca\xb7\xef\xbf\xbd\xef\xbf\xbd\xc4\xb7\xef\xbf\xbd\xdb\xbe\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xca\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/SlimePawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xd7\xa8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc8\xbe\xca\xb7\xef\xbf\xbd\xef\xbf\xbd\xc4\xb7\xef\xbf\xbd\xdb\xbe\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xca\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BubbleInstancedMeshComp_MetaData[] = {
		{ "Category", "Slime" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --------- \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd7\xa8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc8\xbe\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xdd\xb5\xef\xbf\xbd\xca\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd ---------\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/SlimePawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--------- \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd7\xa8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc8\xbe\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xdd\xb5\xef\xbf\xbd\xca\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd ---------" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SphereComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SlimePBFComponent;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MoveSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_JumpForce;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EyeInstancedMeshComp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BubbleInstancedMeshComp;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASlimePawn>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASlimePawn_Statics::NewProp_SphereComponent = { "SphereComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASlimePawn, SphereComponent), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SphereComponent_MetaData), NewProp_SphereComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASlimePawn_Statics::NewProp_SlimePBFComponent = { "SlimePBFComponent", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASlimePawn, SlimePBFComponent), Z_Construct_UClass_USlimePBFInstancedMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SlimePBFComponent_MetaData), NewProp_SlimePBFComponent_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASlimePawn_Statics::NewProp_MoveSpeed = { "MoveSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASlimePawn, MoveSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveSpeed_MetaData), NewProp_MoveSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASlimePawn_Statics::NewProp_JumpForce = { "JumpForce", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASlimePawn, JumpForce), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpForce_MetaData), NewProp_JumpForce_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASlimePawn_Statics::NewProp_EyeInstancedMeshComp = { "EyeInstancedMeshComp", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASlimePawn, EyeInstancedMeshComp), Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EyeInstancedMeshComp_MetaData), NewProp_EyeInstancedMeshComp_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASlimePawn_Statics::NewProp_BubbleInstancedMeshComp = { "BubbleInstancedMeshComp", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASlimePawn, BubbleInstancedMeshComp), Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BubbleInstancedMeshComp_MetaData), NewProp_BubbleInstancedMeshComp_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASlimePawn_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASlimePawn_Statics::NewProp_SphereComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASlimePawn_Statics::NewProp_SlimePBFComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASlimePawn_Statics::NewProp_MoveSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASlimePawn_Statics::NewProp_JumpForce,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASlimePawn_Statics::NewProp_EyeInstancedMeshComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASlimePawn_Statics::NewProp_BubbleInstancedMeshComp,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASlimePawn_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASlimePawn_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APawn,
	(UObject* (*)())Z_Construct_UPackage__Script_SlimePBF,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASlimePawn_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASlimePawn_Statics::ClassParams = {
	&ASlimePawn::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASlimePawn_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASlimePawn_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASlimePawn_Statics::Class_MetaDataParams), Z_Construct_UClass_ASlimePawn_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASlimePawn()
{
	if (!Z_Registration_Info_UClass_ASlimePawn.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASlimePawn.OuterSingleton, Z_Construct_UClass_ASlimePawn_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASlimePawn.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASlimePawn);
ASlimePawn::~ASlimePawn() {}
// ********** End Class ASlimePawn *****************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePawn_h__Script_SlimePBF_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASlimePawn, ASlimePawn::StaticClass, TEXT("ASlimePawn"), &Z_Registration_Info_UClass_ASlimePawn, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASlimePawn), 3816109442U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePawn_h__Script_SlimePBF_855043654(TEXT("/Script/SlimePBF"),
	Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePawn_h__Script_SlimePBF_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePawn_h__Script_SlimePBF_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
