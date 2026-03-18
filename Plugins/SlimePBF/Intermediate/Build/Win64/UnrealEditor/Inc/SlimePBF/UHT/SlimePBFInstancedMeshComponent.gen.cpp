// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SlimePBFInstancedMeshComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSlimePBFInstancedMeshComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
ENGINE_API UClass* Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
SLIMEPBF_API UClass* Z_Construct_UClass_USlimePBFInstancedMeshComponent();
SLIMEPBF_API UClass* Z_Construct_UClass_USlimePBFInstancedMeshComponent_NoRegister();
SLIMEPBF_API UClass* Z_Construct_UClass_USlimePBFManager_NoRegister();
UPackage* Z_Construct_UPackage__Script_SlimePBF();
// ********** End Cross Module References **********************************************************

// ********** Begin Class USlimePBFInstancedMeshComponent Function InitializePBF *******************
struct Z_Construct_UFunction_USlimePBFInstancedMeshComponent_InitializePBF_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "SlimePBF" },
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USlimePBFInstancedMeshComponent_InitializePBF_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_USlimePBFInstancedMeshComponent, nullptr, "InitializePBF", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USlimePBFInstancedMeshComponent_InitializePBF_Statics::Function_MetaDataParams), Z_Construct_UFunction_USlimePBFInstancedMeshComponent_InitializePBF_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_USlimePBFInstancedMeshComponent_InitializePBF()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USlimePBFInstancedMeshComponent_InitializePBF_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USlimePBFInstancedMeshComponent::execInitializePBF)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitializePBF();
	P_NATIVE_END;
}
// ********** End Class USlimePBFInstancedMeshComponent Function InitializePBF *********************

// ********** Begin Class USlimePBFInstancedMeshComponent ******************************************
void USlimePBFInstancedMeshComponent::StaticRegisterNativesUSlimePBFInstancedMeshComponent()
{
	UClass* Class = USlimePBFInstancedMeshComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "InitializePBF", &USlimePBFInstancedMeshComponent::execInitializePBF },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_USlimePBFInstancedMeshComponent;
UClass* USlimePBFInstancedMeshComponent::GetPrivateStaticClass()
{
	using TClass = USlimePBFInstancedMeshComponent;
	if (!Z_Registration_Info_UClass_USlimePBFInstancedMeshComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SlimePBFInstancedMeshComponent"),
			Z_Registration_Info_UClass_USlimePBFInstancedMeshComponent.InnerSingleton,
			StaticRegisterNativesUSlimePBFInstancedMeshComponent,
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
	return Z_Registration_Info_UClass_USlimePBFInstancedMeshComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_USlimePBFInstancedMeshComponent_NoRegister()
{
	return USlimePBFInstancedMeshComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "SlimePBFInstancedMeshComponent.h" },
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InstancedMeshComponent_MetaData[] = {
		{ "Category", "SlimePBF" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PBFManager_MetaData[] = {
		{ "Category", "SlimePBF" },
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoInitialize_MetaData[] = {
		{ "Category", "SlimePBF" },
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsInitialized_MetaData[] = {
		{ "Category", "SlimePBF" },
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleMesh_MetaData[] = {
		{ "Category", "SlimePBF|Visual" },
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleMaterial_MetaData[] = {
		{ "Category", "SlimePBF|Visual" },
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EyeInstancedMeshComponent_MetaData[] = {
		{ "Category", "SlimePBF" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EyeScaleMultiplier_MetaData[] = {
		{ "Category", "SlimePBF|Visual" },
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EyeSurfaceOffset_MetaData[] = {
		{ "Category", "SlimePBF|Visual" },
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EyeHeightOffset_MetaData[] = {
		{ "Category", "SlimePBF|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe7\x9c\xbc\xe7\x9d\x9b\xe5\x9c\xa8Z\xe8\xbd\xb4\xe6\x96\xb9\xe5\x90\x91\xe7\x9a\x84\xe9\xa2\x9d\xe5\xa4\x96\xe9\xab\x98\xe5\xba\xa6\xe5\x81\x8f\xe7\xa7\xbb\xef\xbc\x88\xe4\xb8\x96\xe7\x95\x8c\xe7\xa9\xba\xe9\x97\xb4\xe5\x8d\x95\xe4\xbd\x8d\xef\xbc\x89 */" },
#endif
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x9c\xbc\xe7\x9d\x9b\xe5\x9c\xa8Z\xe8\xbd\xb4\xe6\x96\xb9\xe5\x90\x91\xe7\x9a\x84\xe9\xa2\x9d\xe5\xa4\x96\xe9\xab\x98\xe5\xba\xa6\xe5\x81\x8f\xe7\xa7\xbb\xef\xbc\x88\xe4\xb8\x96\xe7\x95\x8c\xe7\xa9\xba\xe9\x97\xb4\xe5\x8d\x95\xe4\xbd\x8d\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BubbleScaleMultiplier_MetaData[] = {
		{ "Category", "SlimePBF|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x94\xa8\xe4\xba\x8e\xe5\x9c\xa8\xe8\x93\x9d\xe5\x9b\xbe\xe9\x87\x8c\xe8\x87\xaa\xe7\x94\xb1\xe6\x94\xbe\xe5\xa4\xa7\xe6\x88\x96\xe7\xbc\xa9\xe5\xb0\x8f\xe6\xb3\xa1\xe6\xb3\xa1\n" },
#endif
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x94\xa8\xe4\xba\x8e\xe5\x9c\xa8\xe8\x93\x9d\xe5\x9b\xbe\xe9\x87\x8c\xe8\x87\xaa\xe7\x94\xb1\xe6\x94\xbe\xe5\xa4\xa7\xe6\x88\x96\xe7\xbc\xa9\xe5\xb0\x8f\xe6\xb3\xa1\xe6\xb3\xa1" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BubbleInstancedMeshComponent_MetaData[] = {
		{ "Category", "SlimePBF" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --------- \xe6\x96\xb0\xe5\xa2\x9e\xef\xbc\x9a\xe6\xb3\xa1\xe6\xb3\xa1\xe7\xbb\x84\xe4\xbb\xb6\xe5\xbc\x95\xe7\x94\xa8 ---------\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/SlimePBFInstancedMeshComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--------- \xe6\x96\xb0\xe5\xa2\x9e\xef\xbc\x9a\xe6\xb3\xa1\xe6\xb3\xa1\xe7\xbb\x84\xe4\xbb\xb6\xe5\xbc\x95\xe7\x94\xa8 ---------" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InstancedMeshComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PBFManager;
	static void NewProp_bAutoInitialize_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoInitialize;
	static void NewProp_bIsInitialized_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsInitialized;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ParticleMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ParticleMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EyeInstancedMeshComponent;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EyeScaleMultiplier;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EyeSurfaceOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EyeHeightOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BubbleScaleMultiplier;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BubbleInstancedMeshComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USlimePBFInstancedMeshComponent_InitializePBF, "InitializePBF" }, // 692404683
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USlimePBFInstancedMeshComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_InstancedMeshComponent = { "InstancedMeshComponent", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFInstancedMeshComponent, InstancedMeshComponent), Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InstancedMeshComponent_MetaData), NewProp_InstancedMeshComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_PBFManager = { "PBFManager", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFInstancedMeshComponent, PBFManager), Z_Construct_UClass_USlimePBFManager_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PBFManager_MetaData), NewProp_PBFManager_MetaData) };
void Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_bAutoInitialize_SetBit(void* Obj)
{
	((USlimePBFInstancedMeshComponent*)Obj)->bAutoInitialize = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_bAutoInitialize = { "bAutoInitialize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(USlimePBFInstancedMeshComponent), &Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_bAutoInitialize_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoInitialize_MetaData), NewProp_bAutoInitialize_MetaData) };
void Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_bIsInitialized_SetBit(void* Obj)
{
	((USlimePBFInstancedMeshComponent*)Obj)->bIsInitialized = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_bIsInitialized = { "bIsInitialized", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(USlimePBFInstancedMeshComponent), &Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_bIsInitialized_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsInitialized_MetaData), NewProp_bIsInitialized_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_ParticleMesh = { "ParticleMesh", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFInstancedMeshComponent, ParticleMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleMesh_MetaData), NewProp_ParticleMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_ParticleMaterial = { "ParticleMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFInstancedMeshComponent, ParticleMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleMaterial_MetaData), NewProp_ParticleMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_EyeInstancedMeshComponent = { "EyeInstancedMeshComponent", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFInstancedMeshComponent, EyeInstancedMeshComponent), Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EyeInstancedMeshComponent_MetaData), NewProp_EyeInstancedMeshComponent_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_EyeScaleMultiplier = { "EyeScaleMultiplier", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFInstancedMeshComponent, EyeScaleMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EyeScaleMultiplier_MetaData), NewProp_EyeScaleMultiplier_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_EyeSurfaceOffset = { "EyeSurfaceOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFInstancedMeshComponent, EyeSurfaceOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EyeSurfaceOffset_MetaData), NewProp_EyeSurfaceOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_EyeHeightOffset = { "EyeHeightOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFInstancedMeshComponent, EyeHeightOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EyeHeightOffset_MetaData), NewProp_EyeHeightOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_BubbleScaleMultiplier = { "BubbleScaleMultiplier", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFInstancedMeshComponent, BubbleScaleMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BubbleScaleMultiplier_MetaData), NewProp_BubbleScaleMultiplier_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_BubbleInstancedMeshComponent = { "BubbleInstancedMeshComponent", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFInstancedMeshComponent, BubbleInstancedMeshComponent), Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BubbleInstancedMeshComponent_MetaData), NewProp_BubbleInstancedMeshComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_InstancedMeshComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_PBFManager,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_bAutoInitialize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_bIsInitialized,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_ParticleMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_ParticleMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_EyeInstancedMeshComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_EyeScaleMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_EyeSurfaceOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_EyeHeightOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_BubbleScaleMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::NewProp_BubbleInstancedMeshComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_SlimePBF,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::ClassParams = {
	&USlimePBFInstancedMeshComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USlimePBFInstancedMeshComponent()
{
	if (!Z_Registration_Info_UClass_USlimePBFInstancedMeshComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USlimePBFInstancedMeshComponent.OuterSingleton, Z_Construct_UClass_USlimePBFInstancedMeshComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USlimePBFInstancedMeshComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(USlimePBFInstancedMeshComponent);
USlimePBFInstancedMeshComponent::~USlimePBFInstancedMeshComponent() {}
// ********** End Class USlimePBFInstancedMeshComponent ********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFInstancedMeshComponent_h__Script_SlimePBF_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USlimePBFInstancedMeshComponent, USlimePBFInstancedMeshComponent::StaticClass, TEXT("USlimePBFInstancedMeshComponent"), &Z_Registration_Info_UClass_USlimePBFInstancedMeshComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USlimePBFInstancedMeshComponent), 810537636U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFInstancedMeshComponent_h__Script_SlimePBF_1727131584(TEXT("/Script/SlimePBF"),
	Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFInstancedMeshComponent_h__Script_SlimePBF_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFInstancedMeshComponent_h__Script_SlimePBF_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
