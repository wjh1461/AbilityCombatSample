// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbilityCombatFramework.h"
#include "GameplayTagsManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FAbilityCombatFrameworkModule"

void FAbilityCombatFrameworkModule::StartupModule()
{
	TSharedPtr<IPlugin> AbilityCombatPlugin = IPluginManager::Get().FindPlugin(TEXT("AbilityCombatFramework"));
	if (AbilityCombatPlugin.IsValid())
	{
		FString PluginConfigDir = FPaths::Combine(AbilityCombatPlugin->GetBaseDir(), TEXT("Config"), TEXT("Tags"));
		UGameplayTagsManager::Get().AddTagIniSearchPath(PluginConfigDir);
	}
}

void FAbilityCombatFrameworkModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAbilityCombatFrameworkModule, AbilityCombatFramework)