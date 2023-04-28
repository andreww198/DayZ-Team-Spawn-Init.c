void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
}

class CustomMission: MissionServer
// This Section Creates the arrays for Teams and Team Members
{

    ref array< string > Team1Members = new array< string >;
    ref array< string > Team2Members = new array< string >;
    ref array< string > Team3Members = new array< string >;

    void CustomMission()
    {
        Team1Members = new array< string >;
        Team2Members = new array< string >;
		Team3Members = new array< string >;
        InitPlayerWhitelist();
	}
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.45, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}

	void addMags(PlayerBase player, string mag_type, int count)
	{
		if (count < 1)
			return;

		EntityAI mag;

		for (int i = 0; i < count; i++) {
			mag = player.GetInventory().CreateInInventory(mag_type);
		}

		player.SetQuickBarEntityShortcut(mag, 2, true);
	}
	//This Section Sets Teams by Steam ID - BEGIN--------------------------------------

	void InitPlayerWhitelist()
    {
		// Example with Steam64 ID: 	TeamMembers.Insert( "1234567890123456" ); //PLAYER
				
		// Team1Members: Can be Steam64 ID
		Team1Members.Insert( "12345678901234567" ); // PLAYER

		// Team2Members: Steam64 ID
		Team2Members.Insert( "12345678901234567" ); // PLAYER
				
		// Team3Members: Can be Steam64 ID Team3 is a catch all team, anyone who joins that isnt assigned a team will be on this team by default
		Team3Members.Insert( "12345678901234567" ); // PLAYER
    }

// This Section sets the Teams Starting Gear and Starting Location	
	EntityAI randomTeam1Class(PlayerBase player)
	{
		// arrays of items that a team member can spawn with
		ref TStringArray foodArray = {"BoxCerealCrunchin","PowderedMilk","Rice","BakedBeansCan_Opened","PeachesCan_Opened","SpaghettiCan_Opened","SardinesCan_Opened","TunaCan_Opened","Apple","Tomato","GreenBellPepper","Zucchini","SlicedPumpkin","Potato","SambucusBerry","CaninaBerry","Plum","Pear","AgaricusMushroom","AmanitaMushroom","MacrolepiotaMushroom","LactariusMushroom","PsilocybeMushroom","AuriculariaMushroom"};
		ref TStringArray drinkArray = {"SodaCan_Cola","SodaCan_Pipsi","SodaCan_Spite","SodaCan_Kvass","WaterBottle"};
		ref TStringArray hatArray = {"BaseballCap_Blue","","","","BaseballCap_Beige","","","","BaseballCap_Black","","","","BaseballCap_Olive","","","","BaseballCap_Pink","","","","BaseballCap_Red","","","","BaseballCap_Camo","","","","BaseballCap_CMMG_Black","","","","BaseballCap_CMMG_Pink","","","","BeanieHat_Beige","","","","BeanieHat_Black","","","","BeanieHat_Blue","","","","BeanieHat_Brown","","","","BeanieHat_Green","","","","BeanieHat_Grey","","","","BeanieHat_Pink","","","","BeanieHat_Red","","","","Ushanka_Black","","","","Ushanka_Blue","","","","Ushanka_Green","","","","RadarCap_Black","","","","RadarCap_Blue","","","","RadarCap_Brown","","","","RadarCap_Green","","","","RadarCap_Red","","","","FlatCap_Black","","","","FlatCap_Blue","","","","FlatCap_Red","","","","FlatCap_Brown","","","","FlatCap_Grey","","","","FlatCap_BrownCheck","","","","FlatCap_GreyCheck","","","","FlatCap_BlackCheck","","","","ZmijovkaCap_Black","","","","ZmijovkaCap_Blue","","","","ZmijovkaCap_Brown","","","","ZmijovkaCap_Green","","","","ZmijovkaCap_Red","","","","CowboyHat_Brown","","","","CowboyHat_black","","","","CowboyHat_darkBrown","","","","CowboyHat_green","","","","SkateHelmet_Black","","","","SkateHelmet_Blue","","","","SkateHelmet_Gray","","","","SkateHelmet_Green","","","","SkateHelmet_Red","","","","WeldingMask","","","","LeatherHat_Natural","","","","LeatherHat_Beige","","","","LeatherHat_Brown","","","","LeatherHat_Black","","","","GreatHelm","","",""};
		ref TStringArray topArray = {"Sweater_Gray","Sweater_Blue","Sweater_Green","Sweater_Red","Shirt_BlueCheck","Shirt_BlueCheckBright","Shirt_GreenCheck","Shirt_RedCheck","Shirt_WhiteCheck","Shirt_PlaneBlack","TacticalShirt_Grey","TacticalShirt_Black","M65Jacket_Black","TShirt_Beige","TShirt_Black","TShirt_Blue","TShirt_Green","TShirt_OrangeWhiteStripes","TShirt_Red","TShirt_RedBlackStripes","TShirt_White","TShirt_Grey","Hoodie_Blue","Hoodie_Black","Hoodie_Brown","Hoodie_Green","Hoodie_Grey","Hoodie_Red","HikingJacket_Black","HikingJacket_Blue","HikingJacket_Red","HikingJacket_Green","Raincoat_Orange","Raincoat_Green","Raincoat_Yellow","Raincoat_Pink","Raincoat_Red","Raincoat_Blue","Raincoat_Black","TrackSuitJacket_Black","TrackSuitJacket_Blue","TrackSuitJacket_Green","TrackSuitJacket_LightBlue","TrackSuitJacket_Red","QuiltedJacket_Black","QuiltedJacket_Green","QuiltedJacket_Blue","QuiltedJacket_Red","QuiltedJacket_Grey","QuiltedJacket_Orange","QuiltedJacket_Yellow","QuiltedJacket_Violet","BomberJacket_Black","BomberJacket_Brown","BomberJacket_Blue","BomberJacket_Grey","BomberJacket_Maroon","BomberJacket_Olive","BomberJacket_SkyBlue"};
		ref TStringArray pantsArray = {"Jeans_Black","Jeans_Blue","Jeans_Brown","Jeans_Green","Jeans_Grey","Jeans_BlueDark","CargoPants_Beige","CargoPants_Black","CargoPants_Blue","CargoPants_Green","CargoPants_Grey","CanvasPants_Beige","CanvasPants_Blue","CanvasPants_Grey","CanvasPants_Red","CanvasPants_Violet","CanvasPantsMidi_Beige","CanvasPantsMidi_Blue","CanvasPantsMidi_Grey","CanvasPantsMidi_Red","CanvasPantsMidi_Violet","TrackSuitPants_Black","TrackSuitPants_Blue","TrackSuitPants_Green","TrackSuitPants_Red","TrackSuitPants_LightBlue","SlacksPants_Beige","SlacksPants_Black","SlacksPants_Blue","SlacksPants_Brown","SlacksPants_DarkGrey","SlacksPants_Khaki","SlacksPants_LightGrey","SlacksPants_White","Breeches_Pink","Breeches_Red","Breeches_White","Breeches_Green","Breeches_Browncheck","Breeches_Blue","Breeches_Blackcheck","Breeches_Black","Breeches_Beige","Breeches_Beetcheck","ShortJeans_Black","ShortJeans_Blue","ShortJeans_Brown","ShortJeans_Darkblue","ShortJeans_Green","ShortJeans_Red"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","","","SportGlasses_Black","","","","SportGlasses_Green","","","","SportGlasses_Orange","","","","AviatorGlasses","","","","ThickFramesGlasses","","","","ThinFramesGlasses","","",""};
		ref TStringArray shoesArray = {"AthleticShoes_Blue","AthleticShoes_Black","AthleticShoes_Brown","AthleticShoes_Green","AthleticShoes_Grey","DressShoes_Beige","DressShoes_Black","DressShoes_Brown","DressShoes_Sunburst","DressShoes_White","HikingBoots_Brown","HikingBoots_Black","HikingBootsLow_Black","HikingBootsLow_Blue","HikingBootsLow_Beige","HikingBootsLow_Grey","Wellies_Black","Wellies_Brown","Wellies_Green","Wellies_Grey","WorkingBoots_Grey","WorkingBoots_Brown","WorkingBoots_Green","WorkingBoots_Yellow","WorkingBoots_Beige","JoggingShoes_Black","JoggingShoes_Blue","JoggingShoes_Red","JoggingShoes_Violet","JoggingShoes_White","Sneakers_Black","Sneakers_Gray","Sneakers_Green","Sneakers_Red","Sneakers_White"};
		ref TStringArray maskArray = {"BandanaMask_RedPattern","","","","","","BandanaMask_BlackPattern","","","","","","BandanaMask_PolkaPattern","","","","","","BandanaMask_GreenPattern","","","","","","BandanaMask_CamoPattern","","","","","","NioshFaceMask","","","","","","HockeyMask","","","","","","BalaclavaMask_Black","","","","","","BalaclavaMask_Blackskull","","","","","","BalaclavaMask_Beige","","","","","","BalaclavaMask_Blue","","","","","","BalaclavaMask_Green","","","","","","BalaclavaMask_Pink","","","","","","BalaclavaMask_White","","","","","","GP5GasMask","","","","",""};
		ref TStringArray lightArray = {"Chemlight_White","Chemlight_Blue","Chemlight_Green","Chemlight_White","Chemlight_Red","Chemlight_Yellow","Roadflare","Chemlight_White"};
		ref TStringArray toolArray = {"StoneKnife","CanOpener","Compass"};
		ref TStringArray meleeArray = {"NailedBaseballBat","Pipe","Crowbar"};

		// items that the players spawn with
		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory(lightArray.GetRandomElement());
		player.GetInventory().CreateInInventory(toolArray.GetRandomElement());
		player.GetInventory().CreateInInventory("BandageDressing");
		EntityAI gun = player.GetInventory().CreateInInventory("MKII");
		addMags(player, "Mag_MKII_10Rnd", 2);
		player.GetInventory().CreateInInventory("Ammo_22");
		player.GetInventory().CreateInInventory("Ammo_22");
		player.GetInventory().CreateInInventory("Ammo_22");
		ItemBase melee = player.GetInventory().CreateInInventory(meleeArray.GetRandomElement());
		
		player.SetQuickBarEntityShortcut(gun, 0, true);
		player.SetQuickBarEntityShortcut(melee, 1, true);
		player.SetPosition("12004 3.46 3422"); //Spawn Location Kamyshovo, Removing this line will make this team spawn at vanilla locations
		return gun;
	}

	EntityAI randomTeam2Class(PlayerBase player)
	{
		// arrays of items that a team member can spawn with
		ref TStringArray foodArray = {"BoxCerealCrunchin","PowderedMilk","Rice","BakedBeansCan_Opened","PeachesCan_Opened","SpaghettiCan_Opened","SardinesCan_Opened","TunaCan_Opened","Apple","Tomato","GreenBellPepper","Zucchini","SlicedPumpkin","Potato","SambucusBerry","CaninaBerry","Plum","Pear","AgaricusMushroom","AmanitaMushroom","MacrolepiotaMushroom","LactariusMushroom","PsilocybeMushroom","AuriculariaMushroom"};
		ref TStringArray drinkArray = {"SodaCan_Cola","SodaCan_Pipsi","SodaCan_Spite","SodaCan_Kvass","WaterBottle"};
		ref TStringArray hatArray = {"BaseballCap_Blue","","","","BaseballCap_Beige","","","","BaseballCap_Black","","","","BaseballCap_Olive","","","","BaseballCap_Pink","","","","BaseballCap_Red","","","","BaseballCap_Camo","","","","BaseballCap_CMMG_Black","","","","BaseballCap_CMMG_Pink","","","","BeanieHat_Beige","","","","BeanieHat_Black","","","","BeanieHat_Blue","","","","BeanieHat_Brown","","","","BeanieHat_Green","","","","BeanieHat_Grey","","","","BeanieHat_Pink","","","","BeanieHat_Red","","","","Ushanka_Black","","","","Ushanka_Blue","","","","Ushanka_Green","","","","RadarCap_Black","","","","RadarCap_Blue","","","","RadarCap_Brown","","","","RadarCap_Green","","","","RadarCap_Red","","","","FlatCap_Black","","","","FlatCap_Blue","","","","FlatCap_Red","","","","FlatCap_Brown","","","","FlatCap_Grey","","","","FlatCap_BrownCheck","","","","FlatCap_GreyCheck","","","","FlatCap_BlackCheck","","","","ZmijovkaCap_Black","","","","ZmijovkaCap_Blue","","","","ZmijovkaCap_Brown","","","","ZmijovkaCap_Green","","","","ZmijovkaCap_Red","","","","CowboyHat_Brown","","","","CowboyHat_black","","","","CowboyHat_darkBrown","","","","CowboyHat_green","","","","SkateHelmet_Black","","","","SkateHelmet_Blue","","","","SkateHelmet_Gray","","","","SkateHelmet_Green","","","","SkateHelmet_Red","","","","WeldingMask","","","","LeatherHat_Natural","","","","LeatherHat_Beige","","","","LeatherHat_Brown","","","","LeatherHat_Black","","","","GreatHelm","","",""};
		ref TStringArray topArray = {"Sweater_Gray","Sweater_Blue","Sweater_Green","Sweater_Red","Shirt_BlueCheck","Shirt_BlueCheckBright","Shirt_GreenCheck","Shirt_RedCheck","Shirt_WhiteCheck","Shirt_PlaneBlack","TacticalShirt_Grey","TacticalShirt_Black","M65Jacket_Black","TShirt_Beige","TShirt_Black","TShirt_Blue","TShirt_Green","TShirt_OrangeWhiteStripes","TShirt_Red","TShirt_RedBlackStripes","TShirt_White","TShirt_Grey","Hoodie_Blue","Hoodie_Black","Hoodie_Brown","Hoodie_Green","Hoodie_Grey","Hoodie_Red","HikingJacket_Black","HikingJacket_Blue","HikingJacket_Red","HikingJacket_Green","Raincoat_Orange","Raincoat_Green","Raincoat_Yellow","Raincoat_Pink","Raincoat_Red","Raincoat_Blue","Raincoat_Black","TrackSuitJacket_Black","TrackSuitJacket_Blue","TrackSuitJacket_Green","TrackSuitJacket_LightBlue","TrackSuitJacket_Red","QuiltedJacket_Black","QuiltedJacket_Green","QuiltedJacket_Blue","QuiltedJacket_Red","QuiltedJacket_Grey","QuiltedJacket_Orange","QuiltedJacket_Yellow","QuiltedJacket_Violet","BomberJacket_Black","BomberJacket_Brown","BomberJacket_Blue","BomberJacket_Grey","BomberJacket_Maroon","BomberJacket_Olive","BomberJacket_SkyBlue"};
		ref TStringArray pantsArray = {"Jeans_Black","Jeans_Blue","Jeans_Brown","Jeans_Green","Jeans_Grey","Jeans_BlueDark","CargoPants_Beige","CargoPants_Black","CargoPants_Blue","CargoPants_Green","CargoPants_Grey","CanvasPants_Beige","CanvasPants_Blue","CanvasPants_Grey","CanvasPants_Red","CanvasPants_Violet","CanvasPantsMidi_Beige","CanvasPantsMidi_Blue","CanvasPantsMidi_Grey","CanvasPantsMidi_Red","CanvasPantsMidi_Violet","TrackSuitPants_Black","TrackSuitPants_Blue","TrackSuitPants_Green","TrackSuitPants_Red","TrackSuitPants_LightBlue","SlacksPants_Beige","SlacksPants_Black","SlacksPants_Blue","SlacksPants_Brown","SlacksPants_DarkGrey","SlacksPants_Khaki","SlacksPants_LightGrey","SlacksPants_White","Breeches_Pink","Breeches_Red","Breeches_White","Breeches_Green","Breeches_Browncheck","Breeches_Blue","Breeches_Blackcheck","Breeches_Black","Breeches_Beige","Breeches_Beetcheck","ShortJeans_Black","ShortJeans_Blue","ShortJeans_Brown","ShortJeans_Darkblue","ShortJeans_Green","ShortJeans_Red"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","","","SportGlasses_Black","","","","SportGlasses_Green","","","","SportGlasses_Orange","","","","AviatorGlasses","","","","ThickFramesGlasses","","","","ThinFramesGlasses","","",""};
		ref TStringArray shoesArray = {"AthleticShoes_Blue","AthleticShoes_Black","AthleticShoes_Brown","AthleticShoes_Green","AthleticShoes_Grey","DressShoes_Beige","DressShoes_Black","DressShoes_Brown","DressShoes_Sunburst","DressShoes_White","HikingBoots_Brown","HikingBoots_Black","HikingBootsLow_Black","HikingBootsLow_Blue","HikingBootsLow_Beige","HikingBootsLow_Grey","Wellies_Black","Wellies_Brown","Wellies_Green","Wellies_Grey","WorkingBoots_Grey","WorkingBoots_Brown","WorkingBoots_Green","WorkingBoots_Yellow","WorkingBoots_Beige","JoggingShoes_Black","JoggingShoes_Blue","JoggingShoes_Red","JoggingShoes_Violet","JoggingShoes_White","Sneakers_Black","Sneakers_Gray","Sneakers_Green","Sneakers_Red","Sneakers_White"};
		ref TStringArray maskArray = {"BandanaMask_RedPattern","","","","","","BandanaMask_BlackPattern","","","","","","BandanaMask_PolkaPattern","","","","","","BandanaMask_GreenPattern","","","","","","BandanaMask_CamoPattern","","","","","","NioshFaceMask","","","","","","HockeyMask","","","","","","BalaclavaMask_Black","","","","","","BalaclavaMask_Blackskull","","","","","","BalaclavaMask_Beige","","","","","","BalaclavaMask_Blue","","","","","","BalaclavaMask_Green","","","","","","BalaclavaMask_Pink","","","","","","BalaclavaMask_White","","","","","","GP5GasMask","","","","",""};
		ref TStringArray lightArray = {"Chemlight_White","Chemlight_Blue","Chemlight_Green","Chemlight_White","Chemlight_Red","Chemlight_Yellow","Roadflare","Chemlight_White"};
		ref TStringArray toolArray = {"StoneKnife","CanOpener","Compass"};
		ref TStringArray meleeArray = {"NailedBaseballBat","Pipe","Crowbar"};

		// items that the players spawn with
		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory(lightArray.GetRandomElement());
		player.GetInventory().CreateInInventory(toolArray.GetRandomElement());
		player.GetInventory().CreateInInventory("BandageDressing");
		EntityAI gun = player.GetInventory().CreateInInventory("MKII");
		addMags(player, "Mag_MKII_10Rnd", 2);
		player.GetInventory().CreateInInventory("Ammo_22");
		player.GetInventory().CreateInInventory("Ammo_22");
		player.GetInventory().CreateInInventory("Ammo_22");
		ItemBase melee = player.GetInventory().CreateInInventory(meleeArray.GetRandomElement());
		
		player.SetQuickBarEntityShortcut(gun, 0, true);
		player.SetQuickBarEntityShortcut(melee, 1, true);
		player.SetPosition("9814 3.07 1781"); //Spawn Location Elektrozavodsk, Removing this line will make this team spawn at vanilla locations
		return gun;
	}
	
	EntityAI randomTeam3Class(PlayerBase player)
	{
		// arrays of items that a team member can spawn with
		ref TStringArray foodArray = {"BoxCerealCrunchin","PowderedMilk","Rice","BakedBeansCan_Opened","PeachesCan_Opened","SpaghettiCan_Opened","SardinesCan_Opened","TunaCan_Opened","Apple","Tomato","GreenBellPepper","Zucchini","SlicedPumpkin","Potato","SambucusBerry","CaninaBerry","Plum","Pear","AgaricusMushroom","AmanitaMushroom","MacrolepiotaMushroom","LactariusMushroom","PsilocybeMushroom","AuriculariaMushroom"};
		ref TStringArray drinkArray = {"SodaCan_Cola","SodaCan_Pipsi","SodaCan_Spite","SodaCan_Kvass","WaterBottle"};
		ref TStringArray hatArray = {"BaseballCap_Blue","","","","BaseballCap_Beige","","","","BaseballCap_Black","","","","BaseballCap_Olive","","","","BaseballCap_Pink","","","","BaseballCap_Red","","","","BaseballCap_Camo","","","","BaseballCap_CMMG_Black","","","","BaseballCap_CMMG_Pink","","","","BeanieHat_Beige","","","","BeanieHat_Black","","","","BeanieHat_Blue","","","","BeanieHat_Brown","","","","BeanieHat_Green","","","","BeanieHat_Grey","","","","BeanieHat_Pink","","","","BeanieHat_Red","","","","Ushanka_Black","","","","Ushanka_Blue","","","","Ushanka_Green","","","","RadarCap_Black","","","","RadarCap_Blue","","","","RadarCap_Brown","","","","RadarCap_Green","","","","RadarCap_Red","","","","FlatCap_Black","","","","FlatCap_Blue","","","","FlatCap_Red","","","","FlatCap_Brown","","","","FlatCap_Grey","","","","FlatCap_BrownCheck","","","","FlatCap_GreyCheck","","","","FlatCap_BlackCheck","","","","ZmijovkaCap_Black","","","","ZmijovkaCap_Blue","","","","ZmijovkaCap_Brown","","","","ZmijovkaCap_Green","","","","ZmijovkaCap_Red","","","","CowboyHat_Brown","","","","CowboyHat_black","","","","CowboyHat_darkBrown","","","","CowboyHat_green","","","","SkateHelmet_Black","","","","SkateHelmet_Blue","","","","SkateHelmet_Gray","","","","SkateHelmet_Green","","","","SkateHelmet_Red","","","","WeldingMask","","","","LeatherHat_Natural","","","","LeatherHat_Beige","","","","LeatherHat_Brown","","","","LeatherHat_Black","","","","GreatHelm","","",""};
		ref TStringArray topArray = {"Sweater_Gray","Sweater_Blue","Sweater_Green","Sweater_Red","Shirt_BlueCheck","Shirt_BlueCheckBright","Shirt_GreenCheck","Shirt_RedCheck","Shirt_WhiteCheck","Shirt_PlaneBlack","TacticalShirt_Grey","TacticalShirt_Black","M65Jacket_Black","TShirt_Beige","TShirt_Black","TShirt_Blue","TShirt_Green","TShirt_OrangeWhiteStripes","TShirt_Red","TShirt_RedBlackStripes","TShirt_White","TShirt_Grey","Hoodie_Blue","Hoodie_Black","Hoodie_Brown","Hoodie_Green","Hoodie_Grey","Hoodie_Red","HikingJacket_Black","HikingJacket_Blue","HikingJacket_Red","HikingJacket_Green","Raincoat_Orange","Raincoat_Green","Raincoat_Yellow","Raincoat_Pink","Raincoat_Red","Raincoat_Blue","Raincoat_Black","TrackSuitJacket_Black","TrackSuitJacket_Blue","TrackSuitJacket_Green","TrackSuitJacket_LightBlue","TrackSuitJacket_Red","QuiltedJacket_Black","QuiltedJacket_Green","QuiltedJacket_Blue","QuiltedJacket_Red","QuiltedJacket_Grey","QuiltedJacket_Orange","QuiltedJacket_Yellow","QuiltedJacket_Violet","BomberJacket_Black","BomberJacket_Brown","BomberJacket_Blue","BomberJacket_Grey","BomberJacket_Maroon","BomberJacket_Olive","BomberJacket_SkyBlue"};
		ref TStringArray pantsArray = {"Jeans_Black","Jeans_Blue","Jeans_Brown","Jeans_Green","Jeans_Grey","Jeans_BlueDark","CargoPants_Beige","CargoPants_Black","CargoPants_Blue","CargoPants_Green","CargoPants_Grey","CanvasPants_Beige","CanvasPants_Blue","CanvasPants_Grey","CanvasPants_Red","CanvasPants_Violet","CanvasPantsMidi_Beige","CanvasPantsMidi_Blue","CanvasPantsMidi_Grey","CanvasPantsMidi_Red","CanvasPantsMidi_Violet","TrackSuitPants_Black","TrackSuitPants_Blue","TrackSuitPants_Green","TrackSuitPants_Red","TrackSuitPants_LightBlue","SlacksPants_Beige","SlacksPants_Black","SlacksPants_Blue","SlacksPants_Brown","SlacksPants_DarkGrey","SlacksPants_Khaki","SlacksPants_LightGrey","SlacksPants_White","Breeches_Pink","Breeches_Red","Breeches_White","Breeches_Green","Breeches_Browncheck","Breeches_Blue","Breeches_Blackcheck","Breeches_Black","Breeches_Beige","Breeches_Beetcheck","ShortJeans_Black","ShortJeans_Blue","ShortJeans_Brown","ShortJeans_Darkblue","ShortJeans_Green","ShortJeans_Red"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","","","SportGlasses_Black","","","","SportGlasses_Green","","","","SportGlasses_Orange","","","","AviatorGlasses","","","","ThickFramesGlasses","","","","ThinFramesGlasses","","",""};
		ref TStringArray shoesArray = {"AthleticShoes_Blue","AthleticShoes_Black","AthleticShoes_Brown","AthleticShoes_Green","AthleticShoes_Grey","DressShoes_Beige","DressShoes_Black","DressShoes_Brown","DressShoes_Sunburst","DressShoes_White","HikingBoots_Brown","HikingBoots_Black","HikingBootsLow_Black","HikingBootsLow_Blue","HikingBootsLow_Beige","HikingBootsLow_Grey","Wellies_Black","Wellies_Brown","Wellies_Green","Wellies_Grey","WorkingBoots_Grey","WorkingBoots_Brown","WorkingBoots_Green","WorkingBoots_Yellow","WorkingBoots_Beige","JoggingShoes_Black","JoggingShoes_Blue","JoggingShoes_Red","JoggingShoes_Violet","JoggingShoes_White","Sneakers_Black","Sneakers_Gray","Sneakers_Green","Sneakers_Red","Sneakers_White"};
		ref TStringArray maskArray = {"BandanaMask_RedPattern","","","","","","BandanaMask_BlackPattern","","","","","","BandanaMask_PolkaPattern","","","","","","BandanaMask_GreenPattern","","","","","","BandanaMask_CamoPattern","","","","","","NioshFaceMask","","","","","","HockeyMask","","","","","","BalaclavaMask_Black","","","","","","BalaclavaMask_Blackskull","","","","","","BalaclavaMask_Beige","","","","","","BalaclavaMask_Blue","","","","","","BalaclavaMask_Green","","","","","","BalaclavaMask_Pink","","","","","","BalaclavaMask_White","","","","","","GP5GasMask","","","","",""};
		ref TStringArray lightArray = {"Chemlight_White","Chemlight_Blue","Chemlight_Green","Chemlight_White","Chemlight_Red","Chemlight_Yellow","Roadflare","Chemlight_White"};
		ref TStringArray toolArray = {"StoneKnife","CanOpener","Compass"};
		ref TStringArray meleeArray = {"NailedBaseballBat","Pipe","Crowbar"};

		// items that the players spawn with
		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory(lightArray.GetRandomElement());
		player.GetInventory().CreateInInventory(toolArray.GetRandomElement());
		player.GetInventory().CreateInInventory("BandageDressing");
		EntityAI gun = player.GetInventory().CreateInInventory("MKII");
		addMags(player, "Mag_MKII_10Rnd", 2);
		player.GetInventory().CreateInInventory("Ammo_22");
		player.GetInventory().CreateInInventory("Ammo_22");
		player.GetInventory().CreateInInventory("Ammo_22");
		ItemBase melee = player.GetInventory().CreateInInventory(meleeArray.GetRandomElement());
		
		player.SetQuickBarEntityShortcut(gun, 0, true);
		player.SetQuickBarEntityShortcut(melee, 1, true);
		player.SetPosition(" 8057 2.86 2807"); //Spawn Location Chernogorsk, Removing this line will make this team spawn at vanilla locations

		return gun;
	}
	
// This section sets the Teams Loadout to the Team Members.
// Team3 is a catch all team, anyone who joins that isnt assigned a team will be on this team by default

	override void StartingEquipSetup( PlayerBase player, bool clothesChosen )
	{
		player.RemoveAllItems();
					
			if (Team1Members.Find(GetUserID(player)) != -1 || Team1Members.Find(GetUserSteamID(player)) != -1 ) {		
				randomTeam1Class(player);
			} else if (Team2Members.Find(GetUserID(player)) != -1 || Team2Members.Find(GetUserSteamID(player)) != -1 ) { 		
				randomTeam2Class(player);				
			} else {
				randomTeam3Class(player);	
			}
		// This Section Sets fresh spawn water and energy values
		
		player.GetStatWater().Set( 1000 );
		player.GetStatEnergy().Set( 1000 );
	}
	
		string GetUserID(PlayerBase player)
    {
        if ( player.GetIdentity() )
            return player.GetIdentity().GetPlainId();
        
        return "OFFLINE";
    }

    string GetUserSteamID(PlayerBase player)
    {
        if ( player.GetIdentity() )
            return player.GetIdentity().GetId();
        
        return "OFFLINE";
    }

};
  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
}