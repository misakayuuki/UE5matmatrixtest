// Copyright Epic Games, Inc. All Rights Reserved.

#include "createtexCommands.h"

#define LOCTEXT_NAMESPACE "FcreatetexModule"

void FcreatetexCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "createtex", "Execute createtex action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
