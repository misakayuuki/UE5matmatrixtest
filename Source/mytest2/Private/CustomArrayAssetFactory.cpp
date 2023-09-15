

// Fill out your copyright notice in the Description page of Project Settings.



#include "CustomArrayAssetFactory.h"
#include "AssetTypeCategories.h"
#include "UUtilityFunctionBPLibrary.h"

#define LOCTEXT_NAMESPACE "FcreatetexModule"
UCustomArrayAssetFactory::UCustomArrayAssetFactory(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = false;
	SupportedClass = UTexture2D::StaticClass();
}


uint32 UCustomArrayAssetFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Textures;
}

void ClearTexture2D(UTexture2D* Texture2D, FLinearColor ClearColor)
{
	const int32 DestBufferSize = Texture2D->Source.CalcMipSize(0);

	TArray<FFloat16Color> M_SrcData;
	M_SrcData.Empty();
	M_SrcData.AddUninitialized(DestBufferSize);
	for (int32 i = 0; i < M_SrcData.Num(); i++) {
		M_SrcData[i] = ClearColor;
	}
	uint32* DestBuffer = (uint32*)Texture2D->Source.LockMip(0);
	FMemory::Memcpy(DestBuffer, M_SrcData.GetData(), DestBufferSize);
	Texture2D->Source.UnlockMip(0);
	Texture2D->UpdateResource();
	return;
}




UObject* UCustomArrayAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UTexture2D* PseudoComputeTexture = NewObject<UTexture2D>(InParent, Class, Name, Flags);
	PseudoComputeTexture->SRGB = 0;
	PseudoComputeTexture->AddressX = TA_Clamp;
	PseudoComputeTexture->AddressY = TA_Clamp;
	PseudoComputeTexture->CompressionSettings = TC_HDR;
	PseudoComputeTexture->Filter = TextureFilter::TF_Nearest;
	PseudoComputeTexture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;

	PseudoComputeTexture->Source.Init(64,64,1,1,TSF_RGBA32F);
	ClearTexture2D(PseudoComputeTexture, FLinearColor(1,1,1,1));
	//UTexture2DDynamic* dytexture = NewObject<UTexture2DDynamic>(InParent, Class, Name, Flags);
	//dytexture->Source.LockMip(0);

	
	
	

	return PseudoComputeTexture;
}

#undef LOCTEXT_NAMESPACE