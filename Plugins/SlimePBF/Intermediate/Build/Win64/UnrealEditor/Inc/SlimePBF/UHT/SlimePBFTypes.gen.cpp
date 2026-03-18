// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SlimePBFTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSlimePBFTypes() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
SLIMEPBF_API UScriptStruct* Z_Construct_UScriptStruct_FSlimeParticle();
SLIMEPBF_API UScriptStruct* Z_Construct_UScriptStruct_FSlimeParticleController();
UPackage* Z_Construct_UPackage__Script_SlimePBF();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FSlimeParticle ****************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FSlimeParticle;
class UScriptStruct* FSlimeParticle::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FSlimeParticle.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FSlimeParticle.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FSlimeParticle, (UObject*)Z_Construct_UPackage__Script_SlimePBF(), TEXT("SlimeParticle"));
	}
	return Z_Registration_Info_UScriptStruct_FSlimeParticle.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FSlimeParticle_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/SlimePBFTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "Category", "SlimeParticle" },
		{ "ModuleRelativePath", "Public/SlimePBFTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ID_MetaData[] = {
		{ "Category", "SlimeParticle" },
		{ "ModuleRelativePath", "Public/SlimePBFTypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ID;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSlimeParticle>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSlimeParticle_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSlimeParticle, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FSlimeParticle_Statics::NewProp_ID = { "ID", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSlimeParticle, ID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ID_MetaData), NewProp_ID_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSlimeParticle_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSlimeParticle_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSlimeParticle_Statics::NewProp_ID,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSlimeParticle_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSlimeParticle_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_SlimePBF,
	nullptr,
	&NewStructOps,
	"SlimeParticle",
	Z_Construct_UScriptStruct_FSlimeParticle_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSlimeParticle_Statics::PropPointers),
	sizeof(FSlimeParticle),
	alignof(FSlimeParticle),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSlimeParticle_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FSlimeParticle_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FSlimeParticle()
{
	if (!Z_Registration_Info_UScriptStruct_FSlimeParticle.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FSlimeParticle.InnerSingleton, Z_Construct_UScriptStruct_FSlimeParticle_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FSlimeParticle.InnerSingleton;
}
// ********** End ScriptStruct FSlimeParticle ******************************************************

// ********** Begin ScriptStruct FSlimeParticleController ******************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FSlimeParticleController;
class UScriptStruct* FSlimeParticleController::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FSlimeParticleController.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FSlimeParticleController.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FSlimeParticleController, (UObject*)Z_Construct_UPackage__Script_SlimePBF(), TEXT("SlimeParticleController"));
	}
	return Z_Registration_Info_UScriptStruct_FSlimeParticleController.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FSlimeParticleController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/SlimePBFTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Center_MetaData[] = {
		{ "Category", "SlimeParticleController" },
		{ "ModuleRelativePath", "Public/SlimePBFTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Radius_MetaData[] = {
		{ "Category", "SlimeParticleController" },
		{ "ModuleRelativePath", "Public/SlimePBFTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[] = {
		{ "Category", "SlimeParticleController" },
		{ "ModuleRelativePath", "Public/SlimePBFTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Concentration_MetaData[] = {
		{ "Category", "SlimeParticleController" },
		{ "ModuleRelativePath", "Public/SlimePBFTypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Center;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Radius;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Concentration;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSlimeParticleController>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSlimeParticleController_Statics::NewProp_Center = { "Center", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSlimeParticleController, Center), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Center_MetaData), NewProp_Center_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSlimeParticleController_Statics::NewProp_Radius = { "Radius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSlimeParticleController, Radius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Radius_MetaData), NewProp_Radius_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSlimeParticleController_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSlimeParticleController, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Velocity_MetaData), NewProp_Velocity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSlimeParticleController_Statics::NewProp_Concentration = { "Concentration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSlimeParticleController, Concentration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Concentration_MetaData), NewProp_Concentration_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSlimeParticleController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSlimeParticleController_Statics::NewProp_Center,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSlimeParticleController_Statics::NewProp_Radius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSlimeParticleController_Statics::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSlimeParticleController_Statics::NewProp_Concentration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSlimeParticleController_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSlimeParticleController_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_SlimePBF,
	nullptr,
	&NewStructOps,
	"SlimeParticleController",
	Z_Construct_UScriptStruct_FSlimeParticleController_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSlimeParticleController_Statics::PropPointers),
	sizeof(FSlimeParticleController),
	alignof(FSlimeParticleController),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSlimeParticleController_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FSlimeParticleController_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FSlimeParticleController()
{
	if (!Z_Registration_Info_UScriptStruct_FSlimeParticleController.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FSlimeParticleController.InnerSingleton, Z_Construct_UScriptStruct_FSlimeParticleController_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FSlimeParticleController.InnerSingleton;
}
// ********** End ScriptStruct FSlimeParticleController ********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFTypes_h__Script_SlimePBF_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FSlimeParticle::StaticStruct, Z_Construct_UScriptStruct_FSlimeParticle_Statics::NewStructOps, TEXT("SlimeParticle"), &Z_Registration_Info_UScriptStruct_FSlimeParticle, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FSlimeParticle), 4028720884U) },
		{ FSlimeParticleController::StaticStruct, Z_Construct_UScriptStruct_FSlimeParticleController_Statics::NewStructOps, TEXT("SlimeParticleController"), &Z_Registration_Info_UScriptStruct_FSlimeParticleController, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FSlimeParticleController), 3235733113U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFTypes_h__Script_SlimePBF_154837173(TEXT("/Script/SlimePBF"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFTypes_h__Script_SlimePBF_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFTypes_h__Script_SlimePBF_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
