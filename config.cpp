class CfgPatches
{
	class ZenChickenCoops
	{
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Structures_Residential"
		};
		units[] =
		{
			"Zen_ChickenCoop",
			"Zen_ChickenCoop_Debug"
		};
	};
};

class CfgMods
{
	class ZenChickenCoops
	{
		dir = "ZenChickenCoops";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "ZenChickenCoops";
		credits = "";
		author = "Zenarchist";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = { "Game","World","Mission" };
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = { "ZenChickenCoops/scripts/3_Game"; };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "ZenChickenCoops/scripts/4_World" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "ZenChickenCoops/scripts/5_Mission" };
			};
		};
	};
};

class CfgVehicles
{
	class HouseNoDestruct;
	// Create invisible model that we can interact with and will envelope the chicken coop
	class Zen_ChickenCoop : HouseNoDestruct
	{
		scope = 1;
		model = "ZenChickenCoops\data\objects\zen_coop.p3d";
	};
	class Zen_ChickenCoop_Debug : Zen_ChickenCoop
	{
		scope = 1;
		model = "ZenChickenCoops\data\objects\zen_coop_debug.p3d";
	};
	class Zen_ChickenCoop2 : Zen_ChickenCoop
	{
		scope = 1;
		model = "ZenChickenCoops\data\objects\zen_coop2.p3d";
	};
	class Zen_ChickenCoop2_Debug : Zen_ChickenCoop
	{
		scope = 1;
		model = "ZenChickenCoops\data\objects\zen_coop2_debug.p3d";
	};
};