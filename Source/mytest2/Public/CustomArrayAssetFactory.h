// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "UObject/ObjectMacros.h"
#include "Engine/Texture2D.h"
#include "Engine/Texture2DDynamic.h"
#include "CustomArrayAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class MYTEST2_API UCustomArrayAssetFactory : public UFactory
{
	GENERATED_BODY()
	//UCustomArrayAssetFactory(const FObjectInitializer& ObjectInitializer);
	UCustomArrayAssetFactory(const FObjectInitializer& ObjectInitializer);
	
	virtual uint32 GetMenuCategories() const override;
	
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
};
