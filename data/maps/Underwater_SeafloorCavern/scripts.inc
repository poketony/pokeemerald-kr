Underwater_SeafloorCavern_MapScripts:: @ 823433B
	map_script MAP_SCRIPT_ON_RESUME, Underwater_SeafloorCavern_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Underwater_SeafloorCavern_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Underwater_SeafloorCavern_OnLoad
	.byte 0

Underwater_SeafloorCavern_OnTransition: @ 823434B
	setflag FLAG_LANDMARK_SEAFLOOR_CAVERN
	goto_if_set FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, Underwater_SeafloorCavern_EventScript_HideSubmarine
	end

Underwater_SeafloorCavern_EventScript_HideSubmarine:: @ 8234358
	setflag FLAG_HIDE_UNDERWATER_SEA_FLOOR_CAVERN_STOLEN_SUBMARINE
	end

Underwater_SeafloorCavern_OnLoad: @ 823435C
	call_if_set FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, Underwater_SeafloorCavern_EventScript_SetSubmarineGoneMetatiles
	end

Underwater_SeafloorCavern_EventScript_SetSubmarineGoneMetatiles:: @ 8234366
	setmetatile 5, 3, METATILE_Underwater_RockWall, 1
	setmetatile 6, 3, METATILE_Underwater_RockWall, 1
	setmetatile 7, 3, METATILE_Underwater_RockWall, 1
	setmetatile 8, 3, METATILE_Underwater_RockWall, 1
	setmetatile 5, 4, METATILE_Underwater_FloorShadow, 0
	setmetatile 6, 4, METATILE_Underwater_FloorShadow, 0
	setmetatile 7, 4, METATILE_Underwater_FloorShadow, 0
	setmetatile 8, 4, METATILE_Underwater_FloorShadow, 0
	setmetatile 5, 5, METATILE_Underwater_FloorShadow, 0
	setmetatile 6, 5, METATILE_Underwater_FloorShadow, 0
	setmetatile 7, 5, METATILE_Underwater_FloorShadow, 0
	setmetatile 8, 5, METATILE_Underwater_FloorShadow, 0
	return

Underwater_SeafloorCavern_OnResume: @ 82343D3
	setdivewarp MAP_SEAFLOOR_CAVERN_ENTRANCE, 255, 10, 17
	end

Underwater_SeafloorCavern_EventScript_CheckStolenSub:: @ 82343DC
	msgbox Underwater_SeafloorCavern_Text_SubExplorer1, MSGBOX_SIGN
	end

Underwater_SeafloorCavern_Text_SubExplorer1: @ 82343E5
	.string "잠수정에는\n"
	.string "“해연 1호”라고 적혀 있다\p"
	.string "아쿠아단이 잿빛도시 조선소에서\n"
	.string "빼앗아 온 잠수정이다!\p"
	.string "아쿠아단은\n"
	.string "여기 위로 올라간 것 같다$"

