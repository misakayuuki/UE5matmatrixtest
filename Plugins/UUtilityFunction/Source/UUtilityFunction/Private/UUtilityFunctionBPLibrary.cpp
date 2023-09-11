// Copyright Epic Games, Inc. All Rights Reserved.

#include "UUtilityFunctionBPLibrary.h"
#include "UUtilityFunction.h"

UUUtilityFunctionBPLibrary::UUUtilityFunctionBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UUUtilityFunctionBPLibrary::UUtilityFunctionSampleFunction(float Param)
{
	return -1;
}

void UUUtilityFunctionBPLibrary::ClearTexture2D(UTexture2D* Texture2D, FLinearColor ClearColor)
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

void UUUtilityFunctionBPLibrary::SetVectorsDataToTexture2D(UTexture2D* Texture2D, TArray<FLinearColor> WriteData)
{
	if (Texture2D != nullptr) {
		const int32 DestBufferSize = Texture2D->Source.CalcMipSize(0);

		TArray<FFloat16Color> M_SrcData;
		M_SrcData.Empty();
		M_SrcData.Init(FLinearColor(1, 1, 1, 1), DestBufferSize);
		for (int32 i = 0; i < WriteData.Num(); i++) {
			M_SrcData[i] = WriteData[i];
		}

		uint32* DestBuffer = (uint32*)Texture2D->Source.LockMip(0);
		FMemory::Memcpy(DestBuffer, M_SrcData.GetData(), DestBufferSize);
		Texture2D->Source.UnlockMip(0);
		Texture2D->UpdateResource();
		return;







	}



}

