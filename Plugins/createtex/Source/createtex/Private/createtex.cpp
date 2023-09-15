// Copyright Epic Games, Inc. All Rights Reserved.

#include "createtex.h"

#include <string>

#include "createtexStyle.h"
#include "createtexCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "AssetRegistry/AssetRegistryModule.h"

static const FName createtexTabName("createtex");

#define LOCTEXT_NAMESPACE "FcreatetexModule"

void FcreatetexModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FcreatetexStyle::Initialize();
	FcreatetexStyle::ReloadTextures();

	FcreatetexCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FcreatetexCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FcreatetexModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FcreatetexModule::RegisterMenus));
}

void FcreatetexModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FcreatetexStyle::Shutdown();

	FcreatetexCommands::Unregister();
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

void CreateTexture(int i)
{
	
	const FString Path = "/Game";
	const FString Name = FString::FromInt(i);
	const int size = 64;
	const ETextureSourceFormat format = TSF_RGBA32F;
	const FString PackageName = Path + TEXT("/") + Name;
	UPackage* package = CreatePackage(*PackageName);
	package->FullyLoad();
	UTexture2D* PseudoComputeTexture = NewObject<UTexture2D>(package, FName(*Name), RF_Public | RF_Standalone| RF_MarkAsRootSet);
	PseudoComputeTexture->SRGB = 0;
	PseudoComputeTexture->AddressX = TA_Clamp;
	PseudoComputeTexture->AddressY = TA_Clamp;
	PseudoComputeTexture->CompressionSettings = TC_HDR;
	PseudoComputeTexture->Filter = TextureFilter::TF_Nearest;
	PseudoComputeTexture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;

	PseudoComputeTexture->Source.Init(64,64,1,1,TSF_RGBA16F);
	ClearTexture2D(PseudoComputeTexture, FLinearColor(1,1,1,1));
	package->MarkPackageDirty();
	FAssetRegistryModule::AssetCreated(PseudoComputeTexture);
	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	bool bSaved = UPackage::SavePackage(package, PseudoComputeTexture, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr, true, true, SAVE_NoError);
	check(bSaved);
	//PseudoComputeTexture->PostEditChange();
}


void FcreatetexModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FcreatetexModule::PluginButtonClicked()")),
							FText::FromString(TEXT("createtex.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	for(int i = 0;i<16253;i++)
	{
		CreateTexture(i);
	}
	






	
}

void FcreatetexModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FcreatetexCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FcreatetexCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FcreatetexModule, createtex)