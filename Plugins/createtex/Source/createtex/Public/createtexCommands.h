// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "createtexStyle.h"

class FcreatetexCommands : public TCommands<FcreatetexCommands>
{
public:

	FcreatetexCommands()
		: TCommands<FcreatetexCommands>(TEXT("createtex"), NSLOCTEXT("Contexts", "createtex", "createtex Plugin"), NAME_None, FcreatetexStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
