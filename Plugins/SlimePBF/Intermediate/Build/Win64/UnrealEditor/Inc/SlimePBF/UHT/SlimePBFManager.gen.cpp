// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SlimePBFManager.h"
#include "SlimePBFTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSlimePBFManager() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_UWorld_NoRegister();
PROCEDURALMESHCOMPONENT_API UClass* Z_Construct_UClass_UProceduralMeshComponent_NoRegister();
SLIMEPBF_API UClass* Z_Construct_UClass_USlimePBFManager();
SLIMEPBF_API UClass* Z_Construct_UClass_USlimePBFManager_NoRegister();
SLIMEPBF_API UFunction* Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature();
SLIMEPBF_API UScriptStruct* Z_Construct_UScriptStruct_FSlimeParticleController();
UPackage* Z_Construct_UPackage__Script_SlimePBF();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnSlimeBubblePopped **************************************************
struct Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics
{
	struct _Script_SlimePBF_eventOnSlimeBubblePopped_Parms
	{
		FVector PopWorldPosition;
		float BubbleWorldRadius;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_PopWorldPosition;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BubbleWorldRadius;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::NewProp_PopWorldPosition = { "PopWorldPosition", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SlimePBF_eventOnSlimeBubblePopped_Parms, PopWorldPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::NewProp_BubbleWorldRadius = { "BubbleWorldRadius", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SlimePBF_eventOnSlimeBubblePopped_Parms, BubbleWorldRadius), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::NewProp_PopWorldPosition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::NewProp_BubbleWorldRadius,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_SlimePBF, nullptr, "OnSlimeBubblePopped__DelegateSignature", Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::_Script_SlimePBF_eventOnSlimeBubblePopped_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::_Script_SlimePBF_eventOnSlimeBubblePopped_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnSlimeBubblePopped_DelegateWrapper(const FMulticastScriptDelegate& OnSlimeBubblePopped, FVector PopWorldPosition, float BubbleWorldRadius)
{
	struct _Script_SlimePBF_eventOnSlimeBubblePopped_Parms
	{
		FVector PopWorldPosition;
		float BubbleWorldRadius;
	};
	_Script_SlimePBF_eventOnSlimeBubblePopped_Parms Parms;
	Parms.PopWorldPosition=PopWorldPosition;
	Parms.BubbleWorldRadius=BubbleWorldRadius;
	OnSlimeBubblePopped.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnSlimeBubblePopped ****************************************************

// ********** Begin Class USlimePBFManager Function InitializeSimulation ***************************
struct Z_Construct_UFunction_USlimePBFManager_InitializeSimulation_Statics
{
	struct SlimePBFManager_eventInitializeSimulation_Parms
	{
		UWorld* InWorld;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "SlimePBF" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InWorld;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USlimePBFManager_InitializeSimulation_Statics::NewProp_InWorld = { "InWorld", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SlimePBFManager_eventInitializeSimulation_Parms, InWorld), Z_Construct_UClass_UWorld_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USlimePBFManager_InitializeSimulation_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USlimePBFManager_InitializeSimulation_Statics::NewProp_InWorld,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USlimePBFManager_InitializeSimulation_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USlimePBFManager_InitializeSimulation_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_USlimePBFManager, nullptr, "InitializeSimulation", Z_Construct_UFunction_USlimePBFManager_InitializeSimulation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USlimePBFManager_InitializeSimulation_Statics::PropPointers), sizeof(Z_Construct_UFunction_USlimePBFManager_InitializeSimulation_Statics::SlimePBFManager_eventInitializeSimulation_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USlimePBFManager_InitializeSimulation_Statics::Function_MetaDataParams), Z_Construct_UFunction_USlimePBFManager_InitializeSimulation_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_USlimePBFManager_InitializeSimulation_Statics::SlimePBFManager_eventInitializeSimulation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USlimePBFManager_InitializeSimulation()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USlimePBFManager_InitializeSimulation_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USlimePBFManager::execInitializeSimulation)
{
	P_GET_OBJECT(UWorld,Z_Param_InWorld);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitializeSimulation(Z_Param_InWorld);
	P_NATIVE_END;
}
// ********** End Class USlimePBFManager Function InitializeSimulation *****************************

// ********** Begin Class USlimePBFManager Function OnKeyP *****************************************
struct Z_Construct_UFunction_USlimePBFManager_OnKeyP_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Slime|Control" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USlimePBFManager_OnKeyP_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_USlimePBFManager, nullptr, "OnKeyP", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USlimePBFManager_OnKeyP_Statics::Function_MetaDataParams), Z_Construct_UFunction_USlimePBFManager_OnKeyP_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_USlimePBFManager_OnKeyP()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USlimePBFManager_OnKeyP_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USlimePBFManager::execOnKeyP)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnKeyP();
	P_NATIVE_END;
}
// ********** End Class USlimePBFManager Function OnKeyP *******************************************

// ********** Begin Class USlimePBFManager Function OnKeyR *****************************************
struct Z_Construct_UFunction_USlimePBFManager_OnKeyR_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Slime|Control" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USlimePBFManager_OnKeyR_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_USlimePBFManager, nullptr, "OnKeyR", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USlimePBFManager_OnKeyR_Statics::Function_MetaDataParams), Z_Construct_UFunction_USlimePBFManager_OnKeyR_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_USlimePBFManager_OnKeyR()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USlimePBFManager_OnKeyR_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USlimePBFManager::execOnKeyR)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnKeyR();
	P_NATIVE_END;
}
// ********** End Class USlimePBFManager Function OnKeyR *******************************************

// ********** Begin Class USlimePBFManager Function UpdateSimulation *******************************
struct Z_Construct_UFunction_USlimePBFManager_UpdateSimulation_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "SlimePBF" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USlimePBFManager_UpdateSimulation_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_USlimePBFManager, nullptr, "UpdateSimulation", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USlimePBFManager_UpdateSimulation_Statics::Function_MetaDataParams), Z_Construct_UFunction_USlimePBFManager_UpdateSimulation_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_USlimePBFManager_UpdateSimulation()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USlimePBFManager_UpdateSimulation_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USlimePBFManager::execUpdateSimulation)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateSimulation();
	P_NATIVE_END;
}
// ********** End Class USlimePBFManager Function UpdateSimulation *********************************

// ********** Begin Class USlimePBFManager *********************************************************
void USlimePBFManager::StaticRegisterNativesUSlimePBFManager()
{
	UClass* Class = USlimePBFManager::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "InitializeSimulation", &USlimePBFManager::execInitializeSimulation },
		{ "OnKeyP", &USlimePBFManager::execOnKeyP },
		{ "OnKeyR", &USlimePBFManager::execOnKeyR },
		{ "UpdateSimulation", &USlimePBFManager::execUpdateSimulation },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_USlimePBFManager;
UClass* USlimePBFManager::GetPrivateStaticClass()
{
	using TClass = USlimePBFManager;
	if (!Z_Registration_Info_UClass_USlimePBFManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SlimePBFManager"),
			Z_Registration_Info_UClass_USlimePBFManager.InnerSingleton,
			StaticRegisterNativesUSlimePBFManager,
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
	return Z_Registration_Info_UClass_USlimePBFManager.InnerSingleton;
}
UClass* Z_Construct_UClass_USlimePBFManager_NoRegister()
{
	return USlimePBFManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_USlimePBFManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "SlimePBFManager.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MainControllerPosition_MetaData[] = {
		{ "Category", "Slime|Control" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MainControllerVelocity_MetaData[] = {
		{ "Category", "Slime|Control" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe4\xb8\x96\xe7\x95\x8c\xe5\x9d\x90\xe6\xa0\x87\n" },
#endif
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe4\xb8\x96\xe7\x95\x8c\xe5\x9d\x90\xe6\xa0\x87" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Concentration_MetaData[] = {
		{ "Category", "Slime|Control" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe4\xb8\x96\xe7\x95\x8c\xe7\xa9\xba\xe9\x97\xb4\xe9\x80\x9f\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe4\xb8\x96\xe7\x95\x8c\xe7\xa9\xba\xe9\x97\xb4\xe9\x80\x9f\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Gravity_MetaData[] = {
		{ "Category", "Slime|Simulation" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ViscosityStrength_MetaData[] = {
		{ "Category", "Slime|Simulation" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Threshold_MetaData[] = {
		{ "Category", "Slime|Surface" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseAnisotropic_MetaData[] = {
		{ "Category", "Slime|Surface" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BubbleSpeed_MetaData[] = {
		{ "Category", "Slime|Effects" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BubbleEmitRadius_MetaData[] = {
		{ "Category", "Slime|Effects" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\xb3\xa1\xe6\xb3\xa1\xe5\x8f\x91\xe5\xb0\x84\xe5\x9c\x86\xe7\x9a\x84\xe5\x8d\x8a\xe5\xbe\x84\xef\xbc\x88\xe6\xa8\xa1\xe6\x8b\x9f\xe7\xa9\xba\xe9\x97\xb4\xef\xbc\x89 */" },
#endif
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xb3\xa1\xe6\xb3\xa1\xe5\x8f\x91\xe5\xb0\x84\xe5\x9c\x86\xe7\x9a\x84\xe5\x8d\x8a\xe5\xbe\x84\xef\xbc\x88\xe6\xa8\xa1\xe6\x8b\x9f\xe7\xa9\xba\xe9\x97\xb4\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BubbleEmitSideOffset_MetaData[] = {
		{ "Category", "Slime|Effects" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x8f\x91\xe5\xb0\x84\xe5\x9c\x86\xe5\xbf\x83\xe7\x9b\xb8\xe5\xaf\xb9\xe5\x8f\xb2\xe8\x8e\xb1\xe5\xa7\x86\xe4\xb8\xad\xe5\xbf\x83\xe7\x9a\x84\xe5\xb7\xa6\xe5\x8f\xb3\xe5\x81\x8f\xe7\xa7\xbb\xe8\xb7\x9d\xe7\xa6\xbb\xef\xbc\x88\xe6\xa8\xa1\xe6\x8b\x9f\xe7\xa9\xba\xe9\x97\xb4\xef\xbc\x89 */" },
#endif
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8f\x91\xe5\xb0\x84\xe5\x9c\x86\xe5\xbf\x83\xe7\x9b\xb8\xe5\xaf\xb9\xe5\x8f\xb2\xe8\x8e\xb1\xe5\xa7\x86\xe4\xb8\xad\xe5\xbf\x83\xe7\x9a\x84\xe5\xb7\xa6\xe5\x8f\xb3\xe5\x81\x8f\xe7\xa7\xbb\xe8\xb7\x9d\xe7\xa6\xbb\xef\xbc\x88\xe6\xa8\xa1\xe6\x8b\x9f\xe7\xa9\xba\xe9\x97\xb4\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BubbleEmitDownOffset_MetaData[] = {
		{ "Category", "Slime|Effects" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x8f\x91\xe5\xb0\x84\xe5\x9c\x86\xe5\xbf\x83\xe7\x9b\xb8\xe5\xaf\xb9\xe5\x8f\xb2\xe8\x8e\xb1\xe5\xa7\x86\xe4\xb8\xad\xe5\xbf\x83\xe7\x9a\x84\xe5\x90\x91\xe4\xb8\x8b\xe5\x81\x8f\xe7\xa7\xbb\xef\xbc\x88\xe6\xa8\xa1\xe6\x8b\x9f\xe7\xa9\xba\xe9\x97\xb4\xef\xbc\x8c\xe6\xad\xa3\xe5\x80\xbc=\xe5\x90\x91\xe4\xb8\x8b\xef\xbc\x89 */" },
#endif
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8f\x91\xe5\xb0\x84\xe5\x9c\x86\xe5\xbf\x83\xe7\x9b\xb8\xe5\xaf\xb9\xe5\x8f\xb2\xe8\x8e\xb1\xe5\xa7\x86\xe4\xb8\xad\xe5\xbf\x83\xe7\x9a\x84\xe5\x90\x91\xe4\xb8\x8b\xe5\x81\x8f\xe7\xa7\xbb\xef\xbc\x88\xe6\xa8\xa1\xe6\x8b\x9f\xe7\xa9\xba\xe9\x97\xb4\xef\xbc\x8c\xe6\xad\xa3\xe5\x80\xbc=\xe5\x90\x91\xe4\xb8\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BubbleEmitMaxPerZone_MetaData[] = {
		{ "Category", "Slime|Effects" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\xaf\x8f\xe5\xb8\xa7\xe6\xaf\x8f\xe4\xb8\xaa\xe5\x8f\x91\xe5\xb0\x84\xe5\x8c\xba\xe5\x9f\x9f\xe7\x9a\x84\xe6\x9c\x80\xe5\xa4\xa7\xe7\x94\x9f\xe6\x88\x90\xe6\x95\xb0\xe9\x87\x8f */" },
#endif
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xaf\x8f\xe5\xb8\xa7\xe6\xaf\x8f\xe4\xb8\xaa\xe5\x8f\x91\xe5\xb0\x84\xe5\x8c\xba\xe5\x9f\x9f\xe7\x9a\x84\xe6\x9c\x80\xe5\xa4\xa7\xe7\x94\x9f\xe6\x88\x90\xe6\x95\xb0\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Controllers_MetaData[] = {
		{ "Category", "Slime|Control" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnBubblePopped_MetaData[] = {
		{ "Category", "Slime|Effects" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinPos_MetaData[] = {
		{ "Category", "Slime|Surface" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xb0\x83\xe8\xaf\x95\xe7\x94\xa8\n" },
#endif
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xb0\x83\xe8\xaf\x95\xe7\x94\xa8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxPos_MetaData[] = {
		{ "Category", "Slime|Surface" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlockNum_MetaData[] = {
		{ "Category", "Slime|Surface" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BubblesNum_MetaData[] = {
		{ "Category", "Slime|Effects" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDebugMode_MetaData[] = {
		{ "Category", "Slime|Debug" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SurfaceMesh_MetaData[] = {
		{ "Category", "SlimePBFManager" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/SlimePBFManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_MainControllerPosition;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MainControllerVelocity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Concentration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Gravity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ViscosityStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Threshold;
	static void NewProp_bUseAnisotropic_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseAnisotropic;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BubbleSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BubbleEmitRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BubbleEmitSideOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BubbleEmitDownOffset;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BubbleEmitMaxPerZone;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Controllers_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Controllers;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnBubblePopped;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MinPos;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MaxPos;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BlockNum;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BubblesNum;
	static void NewProp_bDebugMode_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDebugMode;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SurfaceMesh;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USlimePBFManager_InitializeSimulation, "InitializeSimulation" }, // 1179632555
		{ &Z_Construct_UFunction_USlimePBFManager_OnKeyP, "OnKeyP" }, // 3682328472
		{ &Z_Construct_UFunction_USlimePBFManager_OnKeyR, "OnKeyR" }, // 1671483777
		{ &Z_Construct_UFunction_USlimePBFManager_UpdateSimulation, "UpdateSimulation" }, // 642912545
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USlimePBFManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_MainControllerPosition = { "MainControllerPosition", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, MainControllerPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MainControllerPosition_MetaData), NewProp_MainControllerPosition_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_MainControllerVelocity = { "MainControllerVelocity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, MainControllerVelocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MainControllerVelocity_MetaData), NewProp_MainControllerVelocity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_Concentration = { "Concentration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, Concentration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Concentration_MetaData), NewProp_Concentration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_Gravity = { "Gravity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, Gravity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Gravity_MetaData), NewProp_Gravity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_ViscosityStrength = { "ViscosityStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, ViscosityStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ViscosityStrength_MetaData), NewProp_ViscosityStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_Threshold = { "Threshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, Threshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Threshold_MetaData), NewProp_Threshold_MetaData) };
void Z_Construct_UClass_USlimePBFManager_Statics::NewProp_bUseAnisotropic_SetBit(void* Obj)
{
	((USlimePBFManager*)Obj)->bUseAnisotropic = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_bUseAnisotropic = { "bUseAnisotropic", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(USlimePBFManager), &Z_Construct_UClass_USlimePBFManager_Statics::NewProp_bUseAnisotropic_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseAnisotropic_MetaData), NewProp_bUseAnisotropic_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BubbleSpeed = { "BubbleSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, BubbleSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BubbleSpeed_MetaData), NewProp_BubbleSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BubbleEmitRadius = { "BubbleEmitRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, BubbleEmitRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BubbleEmitRadius_MetaData), NewProp_BubbleEmitRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BubbleEmitSideOffset = { "BubbleEmitSideOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, BubbleEmitSideOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BubbleEmitSideOffset_MetaData), NewProp_BubbleEmitSideOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BubbleEmitDownOffset = { "BubbleEmitDownOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, BubbleEmitDownOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BubbleEmitDownOffset_MetaData), NewProp_BubbleEmitDownOffset_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BubbleEmitMaxPerZone = { "BubbleEmitMaxPerZone", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, BubbleEmitMaxPerZone), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BubbleEmitMaxPerZone_MetaData), NewProp_BubbleEmitMaxPerZone_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_Controllers_Inner = { "Controllers", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FSlimeParticleController, METADATA_PARAMS(0, nullptr) }; // 3235733113
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_Controllers = { "Controllers", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, Controllers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Controllers_MetaData), NewProp_Controllers_MetaData) }; // 3235733113
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_OnBubblePopped = { "OnBubblePopped", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, OnBubblePopped), Z_Construct_UDelegateFunction_SlimePBF_OnSlimeBubblePopped__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnBubblePopped_MetaData), NewProp_OnBubblePopped_MetaData) }; // 1783918295
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_MinPos = { "MinPos", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, MinPos), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinPos_MetaData), NewProp_MinPos_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_MaxPos = { "MaxPos", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, MaxPos), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxPos_MetaData), NewProp_MaxPos_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BlockNum = { "BlockNum", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, BlockNum), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlockNum_MetaData), NewProp_BlockNum_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BubblesNum = { "BubblesNum", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, BubblesNum), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BubblesNum_MetaData), NewProp_BubblesNum_MetaData) };
void Z_Construct_UClass_USlimePBFManager_Statics::NewProp_bDebugMode_SetBit(void* Obj)
{
	((USlimePBFManager*)Obj)->bDebugMode = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_bDebugMode = { "bDebugMode", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(USlimePBFManager), &Z_Construct_UClass_USlimePBFManager_Statics::NewProp_bDebugMode_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDebugMode_MetaData), NewProp_bDebugMode_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USlimePBFManager_Statics::NewProp_SurfaceMesh = { "SurfaceMesh", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USlimePBFManager, SurfaceMesh), Z_Construct_UClass_UProceduralMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SurfaceMesh_MetaData), NewProp_SurfaceMesh_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USlimePBFManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_MainControllerPosition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_MainControllerVelocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_Concentration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_Gravity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_ViscosityStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_Threshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_bUseAnisotropic,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BubbleSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BubbleEmitRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BubbleEmitSideOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BubbleEmitDownOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BubbleEmitMaxPerZone,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_Controllers_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_Controllers,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_OnBubblePopped,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_MinPos,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_MaxPos,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BlockNum,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_BubblesNum,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_bDebugMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlimePBFManager_Statics::NewProp_SurfaceMesh,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USlimePBFManager_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_USlimePBFManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_SlimePBF,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USlimePBFManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USlimePBFManager_Statics::ClassParams = {
	&USlimePBFManager::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_USlimePBFManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_USlimePBFManager_Statics::PropPointers),
	0,
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USlimePBFManager_Statics::Class_MetaDataParams), Z_Construct_UClass_USlimePBFManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USlimePBFManager()
{
	if (!Z_Registration_Info_UClass_USlimePBFManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USlimePBFManager.OuterSingleton, Z_Construct_UClass_USlimePBFManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USlimePBFManager.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(USlimePBFManager);
// ********** End Class USlimePBFManager ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h__Script_SlimePBF_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USlimePBFManager, USlimePBFManager::StaticClass, TEXT("USlimePBFManager"), &Z_Registration_Info_UClass_USlimePBFManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USlimePBFManager), 545340331U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h__Script_SlimePBF_1749081289(TEXT("/Script/SlimePBF"),
	Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h__Script_SlimePBF_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_MySlime_Plugins_SlimePBF_Source_SlimePBF_Public_SlimePBFManager_h__Script_SlimePBF_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
