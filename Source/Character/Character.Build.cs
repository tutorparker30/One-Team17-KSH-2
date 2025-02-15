// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Character : ModuleRules
{
	public Character(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {			// 공개된 종속 모댈? 프로잭트에서 사용하는 필수 엔진들
			"Core",				//엔진의 기본 기능
			"CoreUObject",		//리프랙션 시프템
			"Engine",			//게임엔진
			"InputCore",		//입력시스템
			"EnhancedInput",	//엔진이랑 연결해주는 인풋시스템? 배웠는데 잘 모름ㅋㅋ
			"UMG"});			//위젯 블루프린트

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
