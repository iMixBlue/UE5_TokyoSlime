#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "PropertyNameMappings.h"

namespace UmgMcpJsonUtils
{
    inline TSharedPtr<FJsonObject> NormalizeJsonKeysToPascalCase(const TSharedPtr<FJsonObject>& SourceJson)
    {
        if (!SourceJson.IsValid())
        {
            return nullptr;
        }

        TSharedPtr<FJsonObject> NormalizedJson = MakeShared<FJsonObject>();

        for (const auto& Pair : SourceJson->Values)
        {
            const FString NormalizedKey = NormalizePropertyName(Pair.Key);
            const TSharedPtr<FJsonValue>& Value = Pair.Value;

            if (Value->Type == EJson::Object)
            {
                NormalizedJson->SetObjectField(NormalizedKey, NormalizeJsonKeysToPascalCase(Value->AsObject()));
            }
            else if (Value->Type == EJson::Array)
            {
                TArray<TSharedPtr<FJsonValue>> NormalizedArray;
                for (const TSharedPtr<FJsonValue>& ArrayValue : Value->AsArray())
                {
                    if (ArrayValue->Type == EJson::Object)
                    {
                        NormalizedArray.Add(MakeShared<FJsonValueObject>(NormalizeJsonKeysToPascalCase(ArrayValue->AsObject())));
                    }
                    else
                    {
                        NormalizedArray.Add(ArrayValue);
                    }
                }

                NormalizedJson->SetArrayField(NormalizedKey, NormalizedArray);
            }
            else
            {
                NormalizedJson->SetField(NormalizedKey, Value);
            }
        }

        return NormalizedJson;
    }
}
