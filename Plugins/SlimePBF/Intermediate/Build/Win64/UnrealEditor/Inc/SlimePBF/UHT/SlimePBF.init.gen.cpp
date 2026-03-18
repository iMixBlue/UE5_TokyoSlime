// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSlimePBF_init() {}
	SLIMEPBF_API UFunction* Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_SlimePBF;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_SlimePBF()
	{
		if (!Z_Registration_Info_UPackage__Script_SlimePBF.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/SlimePBF",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x9C62989F,
				0x469D3255,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_SlimePBF.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_SlimePBF.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_SlimePBF(Z_Construct_UPackage__Script_SlimePBF, TEXT("/Script/SlimePBF"), Z_Registration_Info_UPackage__Script_SlimePBF, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x9C62989F, 0x469D3255));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
