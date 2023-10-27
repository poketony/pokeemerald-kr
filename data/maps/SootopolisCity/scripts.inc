.set LOCALID_EXPERT, 1
.set LOCALID_WOMAN_2, 2
.set LOCALID_KIRI, 3
.set LOCALID_NINJA_BOY, 4
.set LOCALID_BOY_1, 5
.set LOCALID_STEVEN, 7
.set LOCALID_WOMAN_1, 8
.set LOCALID_GROUDON, 9
.set LOCALID_KYOGRE, 10
.set LOCALID_RAYQUAZA, 11
.set LOCALID_MANIAC, 12
.set LOCALID_GIRL, 13
.set LOCALID_BLACK_BELT, 14
.set LOCALID_BOY_2, 15
.set LOCALID_MAXIE, 16
.set LOCALID_ARCHIE, 17
.set LOCALID_WALLACE, 18

SootopolisCity_MapScripts:: @ 81E565C
	map_script MAP_SCRIPT_ON_LOAD, SootopolisCity_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SootopolisCity_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SootopolisCity_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SootopolisCity_OnWarp
	.byte 0

SootopolisCity_OnLoad: @ 81E5676
	call_if_unset FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE, SootopolisCity_EventScript_LockGymDoor
	goto_if_unset FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, SootopolisCity_EventScript_LegendariesNotArrived
	call_if_unset FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE, SootopolisCity_EventScript_LockHouseDoors
	end

SootopolisCity_EventScript_LegendariesNotArrived:: @ 81E5692
	end

SootopolisCity_EventScript_LockHouseDoors:: @ 81E5693
	setmetatile 9, 6, METATILE_Sootopolis_Door_Closed, 1
	setmetatile 9, 17, METATILE_Sootopolis_Door_Closed, 1
	setmetatile 9, 26, METATILE_Sootopolis_Door_Closed, 1
	setmetatile 44, 17, METATILE_Sootopolis_Door_Closed, 1
	setmetatile 8, 35, METATILE_Sootopolis_Door_Closed, 1
	setmetatile 53, 28, METATILE_Sootopolis_Door_Closed, 1
	setmetatile 45, 6, METATILE_Sootopolis_Door_Closed, 1
	setmetatile 48, 25, METATILE_Sootopolis_Door_Closed, 1
	setmetatile 51, 36, METATILE_Sootopolis_Door_Closed, 1
	return

SootopolisCity_EventScript_LockGymDoor:: @ 81E56E5
	setmetatile 31, 32, METATILE_Sootopolis_GymDoor_Closed, 1
	return

SootopolisCity_OnTransition: @ 81E56EF
	setflag FLAG_VISITED_SOOTOPOLIS_CITY
	compare VAR_SOOTOPOLIS_CITY_STATE, 1
	call_if_eq SootopolisCity_EventScript_HideMapNamePopup
	compare VAR_SKY_PILLAR_STATE, 1
	call_if_eq SootopolisCity_EventScript_HideMapNamePopup
	call SootopolisCity_EventScript_SetWeather
	call SootopolisCity_EventScript_SetLayout
	compare VAR_SOOTOPOLIS_CITY_STATE, 1
	call_if_eq SootopolisCity_EventScript_SetBattleSpectators
	compare VAR_SOOTOPOLIS_CITY_STATE, 2
	call_if_eq SootopolisCity_EventScript_SetBattleSpectators
	compare VAR_SOOTOPOLIS_CITY_STATE, 3
	call_if_eq SootopolisCity_EventScript_SetBattleSpectators
	compare VAR_SOOTOPOLIS_CITY_STATE, 4
	call_if_eq SootopolisCity_EventScript_SetBattleSpectators
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	call_if_eq SootopolisCity_EventScript_SetBattleSpectators
	compare VAR_SOOTOPOLIS_CITY_STATE, 2
	call_if_eq SootopolisCity_EventScript_CheckSetEnterCaveOfOriginObjPos
	compare VAR_SOOTOPOLIS_CITY_STATE, 3
	call_if_eq SootopolisCity_EventScript_CheckSetEnterCaveOfOriginObjPos
	compare VAR_SOOTOPOLIS_CITY_STATE, 4
	call_if_eq SootopolisCity_EventScript_SetExitCaveOfOriginObjPos
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	call_if_eq SootopolisCity_EventScript_SetOutsideGymObjPos
	compare VAR_SOOTOPOLIS_CITY_STATE, 6
	call_if_eq SootopolisCity_EventScript_SetExpertBlockCaveEntrance
	end

SootopolisCity_EventScript_HideMapNamePopup:: @ 81E5781
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

SootopolisCity_EventScript_SetBattleSpectators:: @ 81E5785
	setobjectxyperm LOCALID_KIRI, 13, 48
	setobjectxyperm LOCALID_BOY_1, 46, 32
	setobjectxyperm LOCALID_NINJA_BOY, 48, 41
	setobjectxyperm LOCALID_WOMAN_1, 45, 43
	setobjectmovementtype LOCALID_KIRI, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_BOY_1, MOVEMENT_TYPE_FACE_LEFT
	setobjectmovementtype LOCALID_NINJA_BOY, MOVEMENT_TYPE_FACE_LEFT
	setobjectmovementtype LOCALID_WOMAN_1, MOVEMENT_TYPE_FACE_LEFT
	return

SootopolisCity_EventScript_SetLayout:: @ 81E57B2
	compare VAR_SOOTOPOLIS_CITY_STATE, 0
	goto_if_eq SootopolisCity_EventScript_SetNormalLayout
	compare VAR_SOOTOPOLIS_CITY_STATE, 6
	goto_if_ge SootopolisCity_EventScript_SetNormalLayout
	compare VAR_SOOTOPOLIS_CITY_STATE, 1
	goto_if_eq SootopolisCity_EventScript_SetLegendariesLayout
	compare VAR_SOOTOPOLIS_CITY_STATE, 2
	goto_if_eq SootopolisCity_EventScript_SetLegendariesLayout
	compare VAR_SOOTOPOLIS_CITY_STATE, 3
	goto_if_eq SootopolisCity_EventScript_SetLegendariesLayout
	compare VAR_SOOTOPOLIS_CITY_STATE, 4
	goto_if_eq SootopolisCity_EventScript_SetLegendariesLayout
	compare VAR_SKY_PILLAR_STATE, 1
	goto_if_le SootopolisCity_EventScript_SetLegendariesLayout
	return

SootopolisCity_EventScript_SetNormalLayout:: @ 81E5800
	return

SootopolisCity_EventScript_SetLegendariesLayout:: @ 81E5801
	setmaplayoutindex LAYOUT_SOOTOPOLIS_CITY_LEGENDS_BATTLE
	return

SootopolisCity_EventScript_SetWeather:: @ 81E5805
	compare VAR_SOOTOPOLIS_CITY_STATE, 0
	goto_if_eq SootopolisCity_EventScript_SetNormalWeather
	compare VAR_SOOTOPOLIS_CITY_STATE, 6
	goto_if_ge SootopolisCity_EventScript_SetNormalWeather
	compare VAR_SOOTOPOLIS_CITY_STATE, 1
	goto_if_eq SootopolisCity_EventScript_SetDownpour
	compare VAR_SKY_PILLAR_STATE, 1
	goto_if_eq SootopolisCity_EventScript_SetDownpour
	compare VAR_SKY_PILLAR_STATE, 1
	goto_if_le Common_EventScript_SetAbnormalWeather
	return

SootopolisCity_EventScript_SetNormalWeather:: @ 81E583D
	return

SootopolisCity_EventScript_SetDownpour:: @ 81E583E
	setweather WEATHER_DOWNPOUR
	return

SootopolisCity_EventScript_CheckSetEnterCaveOfOriginObjPos:: @ 81E5842
	goto_if_set FLAG_STEVEN_GUIDES_TO_CAVE_OF_ORIGIN, SootopolisCity_EventScript_SetEnterCaveOfOriginObjPos
	return

SootopolisCity_EventScript_SetEnterCaveOfOriginObjPos:: @ 81E584C
	setobjectxyperm LOCALID_EXPERT, 30, 18
	setobjectxyperm LOCALID_STEVEN, 32, 18
	return

SootopolisCity_EventScript_SetExitCaveOfOriginObjPos:: @ 81E585B
	setobjectxyperm LOCALID_EXPERT, 30, 18
	setobjectxyperm LOCALID_WALLACE, 31, 18
	setobjectxyperm LOCALID_STEVEN, 32, 18
	end

SootopolisCity_EventScript_SetOutsideGymObjPos:: @ 81E5871
	setobjectxyperm LOCALID_EXPERT, 31, 18
	setobjectxyperm LOCALID_STEVEN, 29, 33
	setobjectxyperm LOCALID_MAXIE, 33, 35
	setobjectxyperm LOCALID_ARCHIE, 34, 35
	compare VAR_SOOTOPOLIS_WALLACE_STATE, 0
	call_if_eq SootopolisCity_EventScript_SetWallaceMiddle
	compare VAR_SOOTOPOLIS_WALLACE_STATE, 1
	call_if_eq SootopolisCity_EventScript_SetWallaceRight
	compare VAR_SOOTOPOLIS_WALLACE_STATE, 2
	call_if_eq SootopolisCity_EventScript_SetWallaceLeft
	return

SootopolisCity_EventScript_SetWallaceMiddle:: @ 81E58AF
	setobjectxyperm LOCALID_WALLACE, 31, 33
	setobjectmovementtype LOCALID_WALLACE, MOVEMENT_TYPE_FACE_DOWN
	return

SootopolisCity_EventScript_SetWallaceRight:: @ 81E58BB
	setobjectxyperm LOCALID_WALLACE, 32, 33
	setobjectmovementtype LOCALID_WALLACE, MOVEMENT_TYPE_FACE_DOWN
	return

SootopolisCity_EventScript_SetWallaceLeft:: @ 81E58C7
	setobjectxyperm LOCALID_WALLACE, 30, 33
	setobjectmovementtype LOCALID_WALLACE, MOVEMENT_TYPE_FACE_DOWN
	return

SootopolisCity_EventScript_SetExpertBlockCaveEntrance:: @ 81E58D3
	setobjectxyperm LOCALID_EXPERT, 31, 18
	return

SootopolisCity_OnWarp: @ 81E58DB
	map_script_2 VAR_SOOTOPOLIS_CITY_STATE, 5, SootopolisCity_EventScript_PlayerFaceLegendaries
	.2byte 0

SootopolisCity_EventScript_PlayerFaceLegendaries:: @ 81E58E5
	compare VAR_SKY_PILLAR_STATE, 1
	call_if_eq SootopolisCity_EventScript_PlayerFaceLegendaries1
	compare VAR_SKY_PILLAR_STATE, 2
	call_if_eq SootopolisCity_EventScript_PlayerFaceLegendaries2
	end

SootopolisCity_EventScript_PlayerFaceLegendaries1:: @ 81E58FC
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	return

SootopolisCity_EventScript_PlayerFaceLegendaries2:: @ 81E5901
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	setvar VAR_SKY_PILLAR_STATE, 3
	return

SootopolisCity_OnResume: @ 81E590B
	setdivewarp MAP_UNDERWATER_SOOTOPOLIS_CITY, 255, 9, 6
	end

SootopolisCity_OnFrame: @ 81E5914
	map_script_2 VAR_SOOTOPOLIS_CITY_STATE, 1, SootopolisCity_EventScript_StartLegendariesScene
	map_script_2 VAR_SKY_PILLAR_STATE, 1, SootopolisCity_EventScript_StartRayquazaScene
	.2byte 0

@ If not at PokeCenter, assumed to have arrived via Dive
SootopolisCity_EventScript_StartLegendariesScene:: @ 81E5926
	lockall
	special StorePlayerCoordsInVars
	compare VAR_0x8004, 43
	goto_if_ne SootopolisCity_EventScript_LegendariesSceneFromDive
	compare VAR_0x8005, 32
	goto_if_ne SootopolisCity_EventScript_LegendariesSceneFromDive
	goto SootopolisCity_EventScript_LegendariesSceneFromPokeCenter
	end

SootopolisCity_EventScript_LegendariesSceneFromPokeCenter:: @ 81E5946
	delay 60
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SootopolisCity_Movement_PanToActionFromPokeCenter
	waitmovement 0
	special RemoveCameraObject
	delay 60
	fadescreenspeed FADE_TO_BLACK, 8
	setweather WEATHER_ABNORMAL
	doweather
	setvar VAR_0x8004, FALSE @ Just do Groudon/Kyogre fight scene
	special Script_DoRayquazaScene
	waitstate
	applymovement LOCALID_KYOGRE, Common_Movement_WalkInPlaceFastestLeft
	applymovement LOCALID_GROUDON, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 60
	waitse
	playmoncry SPECIES_KYOGRE, 2
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_KyogreAttack
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_GroudonDefend
	waitmovement 0
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_KyogreMoveBack
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_GroudonMoveBack
	waitmovement 0
	waitse
	playmoncry SPECIES_GROUDON, 2
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_GroudonAttack
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_KyogreDefend
	waitmovement 0
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_KyogreMoveBack
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_GroudonMoveBack
	waitmovement 0
	waitse
	playmoncry SPECIES_KYOGRE, 2
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_KyogreAttack
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_GroudonDefend
	waitmovement 0
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_KyogreMoveBack
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_GroudonMoveBack
	waitmovement 0
	special SpawnCameraObject
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_KyogreIdle
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_GroudonIdle
	applymovement OBJ_EVENT_ID_CAMERA, SootopolisCity_Movement_PanBackToPokeCenter
	waitmovement 0
	special RemoveCameraObject
	setvar VAR_SOOTOPOLIS_CITY_STATE, 2
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	releaseall
	end

SootopolisCity_Movement_PanToActionFromPokeCenter: @ 81E5A68
	walk_slow_diag_southwest
	walk_slow_diag_southwest
	walk_slow_diag_southwest
	walk_slow_diag_southwest
	walk_slow_diag_southwest
	walk_slow_diag_southwest
	walk_slow_diag_southwest
	walk_slow_diag_southwest
	walk_slow_diag_southwest
	walk_slow_diag_southwest
	walk_slow_diag_southwest
	walk_slow_diag_southwest
	step_end

SootopolisCity_Movement_PanBackToPokeCenter: @ 81E5A75
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	step_end

SootopolisCity_EventScript_LegendariesSceneFromDive:: @ 81E5A82
	delay 60
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SootopolisCity_Movement_PanToActionFromDive
	waitmovement 0
	special RemoveCameraObject
	delay 60
	fadescreenspeed FADE_TO_BLACK, 8
	setweather WEATHER_ABNORMAL
	doweather
	setvar VAR_0x8004, FALSE @ Just do Groudon/Kyogre fight scene
	special Script_DoRayquazaScene
	waitstate
	applymovement LOCALID_KYOGRE, Common_Movement_WalkInPlaceFastestLeft
	applymovement LOCALID_GROUDON, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 60
	waitse
	playmoncry SPECIES_KYOGRE, 2
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_KyogreAttack
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_GroudonDefend
	waitmovement 0
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_KyogreMoveBack
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_GroudonMoveBack
	waitmovement 0
	waitse
	playmoncry SPECIES_GROUDON, 2
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_GroudonAttack
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_KyogreDefend
	waitmovement 0
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_KyogreMoveBack
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_GroudonMoveBack
	waitmovement 0
	waitse
	playmoncry SPECIES_KYOGRE, 2
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_KyogreAttack
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_GroudonDefend
	waitmovement 0
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_KyogreMoveBack
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_GroudonMoveBack
	waitmovement 0
	special SpawnCameraObject
	applymovement LOCALID_KYOGRE, SootopolisCity_Movement_KyogreIdle
	applymovement LOCALID_GROUDON, SootopolisCity_Movement_GroudonIdle
	applymovement OBJ_EVENT_ID_CAMERA, SootopolisCity_Movement_PanBackToDive
	waitmovement 0
	special RemoveCameraObject
	setvar VAR_SOOTOPOLIS_CITY_STATE, 2
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	releaseall
	end

SootopolisCity_Movement_PanToActionFromDive: @ 81E5BA4
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SootopolisCity_Movement_PanBackToDive: @ 81E5BAE
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_slow_diag_southwest
	walk_slow_diag_southwest
	step_end

SootopolisCity_Movement_KyogreAttack: @ 81E5BB8
	walk_in_place_slow_left
	walk_in_place_slow_left
	walk_in_place_slow_left
	delay_16
	delay_16
	delay_16
	init_affine_anim
	walk_left_affine
	clear_affine_anim
	step_end

SootopolisCity_Movement_GroudonAttack: @ 81E5BC2
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	init_affine_anim
	walk_left_affine
	clear_affine_anim
	step_end

SootopolisCity_Movement_KyogreMoveBack: @ 81E5BCF
	lock_facing_direction
	walk_right
	delay_16
	delay_16
	delay_16
	unlock_facing_direction
	step_end

SootopolisCity_Movement_KyogreIdle: @ 81E5BD6
	walk_in_place_slow_left
	walk_in_place_slow_left
	walk_in_place_slow_left
	walk_in_place_slow_left
	walk_in_place_slow_left
	walk_in_place_slow_left
	step_end

SootopolisCity_Movement_KyogreDefend: @ 81E5BDD
	walk_in_place_slow_right
	walk_in_place_slow_right
	walk_in_place_slow_right
	delay_16
	delay_16
	delay_16
	walk_fast_right
	step_end

SootopolisCity_Movement_GroudonDefend: @ 81E5BE5
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_fast_right
	step_end

SootopolisCity_Movement_GroudonMoveBack: @ 81E5BF0
	lock_facing_direction
	walk_left
	delay_16
	delay_16
	delay_16
	unlock_facing_direction
	step_end

SootopolisCity_Movement_GroudonIdle: @ 81E5BF7
	walk_in_place_slow_right
	walk_in_place_slow_right
	walk_in_place_slow_right
	walk_in_place_slow_right
	walk_in_place_slow_right
	walk_in_place_slow_right
	step_end

@ If not at PokeCenter, assumed to have arrived via Dive
SootopolisCity_EventScript_StartRayquazaScene:: @ 81E5BFE
	lockall
	special StorePlayerCoordsInVars
	compare VAR_0x8004, 43
	goto_if_ne SootopolisCity_EventScript_RayquazaSceneFromDive
	compare VAR_0x8005, 32
	goto_if_ne SootopolisCity_EventScript_RayquazaSceneFromDive
	goto SootopolisCity_EventScript_RayquazaSceneFromPokeCenter
	end

SootopolisCity_EventScript_RayquazaSceneFromPokeCenter:: @ 81E5C1E
	delay 60
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SootopolisCity_Movement_PanToActionFromPokeCenter
	waitmovement 0
	special RemoveCameraObject
	delay 60
	fadescreenspeed FADE_TO_BLACK, 8
	call SootopolisCity_EventScript_SetRoughWater
	removeobject LOCALID_GROUDON
	removeobject LOCALID_KYOGRE
	addobject LOCALID_RAYQUAZA
	setvar VAR_0x8004, TRUE
	special Script_DoRayquazaScene
	waitstate
	playse SE_THUNDER
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SootopolisCity_Movement_PanUp
	waitmovement 0
	waitse
	playmoncry SPECIES_RAYQUAZA, 2
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	waitse
	playmoncry SPECIES_RAYQUAZA, 2
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	waitmoncry
	setweather WEATHER_NONE
	doweather
	applymovement LOCALID_RAYQUAZA, SootopolisCity_Movement_RayquazaFlyOff
	waitmovement 0
	removeobject LOCALID_RAYQUAZA
	special WaitWeather
	waitstate
	clearflag FLAG_SYS_WEATHER_CTRL
	setvar VAR_SKY_PILLAR_STATE, 3
	clearflag FLAG_LEGENDARIES_IN_SOOTOPOLIS
	fadenewbgm MUS_SOOTOPOLIS
	delay 120
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	warpsootopolislegend MAP_SOOTOPOLIS_CITY, 255, 43, 32
	waitstate
	end

SootopolisCity_EventScript_RayquazaSceneFromDive:: @ 81E5CCE
	delay 60
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SootopolisCity_Movement_PanToActionFromDive
	waitmovement 0
	special RemoveCameraObject
	delay 60
	fadescreenspeed FADE_TO_BLACK, 8
	call SootopolisCity_EventScript_SetRoughWater
	removeobject LOCALID_GROUDON
	removeobject LOCALID_KYOGRE
	addobject LOCALID_RAYQUAZA
	setvar VAR_0x8004, TRUE
	special Script_DoRayquazaScene
	waitstate
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SootopolisCity_Movement_PanUp
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_Movement_PlayerApproachLegendaries
	waitmovement 0
	waitse
	playmoncry SPECIES_RAYQUAZA, 2
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	waitse
	playmoncry SPECIES_RAYQUAZA, 2
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	waitmoncry
	setweather WEATHER_NONE
	doweather
	applymovement LOCALID_RAYQUAZA, SootopolisCity_Movement_RayquazaFlyOff
	waitmovement 0
	removeobject LOCALID_RAYQUAZA
	special WaitWeather
	waitstate
	clearflag FLAG_SYS_WEATHER_CTRL
	setvar VAR_SKY_PILLAR_STATE, 2
	clearflag FLAG_LEGENDARIES_IN_SOOTOPOLIS
	fadenewbgm MUS_SURF
	delay 120
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	warpsootopolislegend MAP_SOOTOPOLIS_CITY, 255, 29, 53
	waitstate
	end

SootopolisCity_EventScript_SetRoughWater:: @ 81E5D82
	setmetatile 27, 43, METATILE_Sootopolis_RoughWater, 0
	setmetatile 28, 43, METATILE_Sootopolis_RoughWater, 0
	setmetatile 29, 43, METATILE_Sootopolis_RoughWater, 0
	setmetatile 30, 43, METATILE_Sootopolis_RoughWater, 0
	setmetatile 27, 44, METATILE_Sootopolis_RoughWater, 0
	setmetatile 28, 44, METATILE_Sootopolis_RoughWater, 0
	setmetatile 29, 44, METATILE_Sootopolis_RoughWater, 0
	setmetatile 30, 44, METATILE_Sootopolis_RoughWater, 0
	setmetatile 27, 45, METATILE_Sootopolis_RoughWater, 0
	setmetatile 28, 45, METATILE_Sootopolis_RoughWater, 0
	setmetatile 29, 45, METATILE_Sootopolis_RoughWater, 0
	setmetatile 30, 45, METATILE_Sootopolis_RoughWater, 0
	setmetatile 32, 43, METATILE_Sootopolis_RoughWater, 0
	setmetatile 33, 43, METATILE_Sootopolis_RoughWater, 0
	setmetatile 34, 43, METATILE_Sootopolis_RoughWater, 0
	setmetatile 35, 43, METATILE_Sootopolis_RoughWater, 0
	setmetatile 32, 44, METATILE_Sootopolis_RoughWater, 0
	setmetatile 33, 44, METATILE_Sootopolis_RoughWater, 0
	setmetatile 34, 44, METATILE_Sootopolis_RoughWater, 0
	setmetatile 35, 44, METATILE_Sootopolis_RoughWater, 0
	setmetatile 32, 45, METATILE_Sootopolis_RoughWater, 0
	setmetatile 33, 45, METATILE_Sootopolis_RoughWater, 0
	setmetatile 34, 45, METATILE_Sootopolis_RoughWater, 0
	setmetatile 35, 45, METATILE_Sootopolis_RoughWater, 0
	return

SootopolisCity_Movement_RayquazaFlyOff: @ 81E5E5B
	walk_fast_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	step_end

SootopolisCity_Movement_PanUp: @ 81E5E63
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SootopolisCity_Movement_PlayerApproachLegendaries: @ 81E5E68
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

@ Unused
SootopolisCity_Movement_PlayerApproachLegendariesDown: @ 81E5E6D
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

@ Unused
SootopolisCity_Movement_UnusedPanUp: @ 81E5E72
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_slow_diag_northeast
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

@ Unused
SootopolisCity_Movement_UnusedPanBack: @ 81E5E7F
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_slow_diag_southwest
	walk_slow_diag_southwest
	step_end

SootopolisCity_EventScript_CaveOfOriginExpert:: @ 81E5E8D
	lock
	faceplayer
	compare VAR_SOOTOPOLIS_CITY_STATE, 6
	goto_if_ge SootopolisCity_EventScript_ExpertPostLegendaries
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	goto_if_eq SootopolisCity_EventScript_ExpertLegendaries
	compare VAR_SOOTOPOLIS_CITY_STATE, 2
	goto_if_ge SootopolisCity_EventScript_ExpertLeadToCave
	msgbox SootopolisCity_Text_CaveOfOriginPleaseLeave, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_ExpertLeadToCave:: @ 81E5EBA
	msgbox SootopolisCity_Text_LeadSuperiorTrainerToCave, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_ExpertPostLegendaries:: @ 81E5EC4
	msgbox SootopolisCity_Text_CaveOfOriginSleepsToo, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_ExpertLegendaries:: @ 81E5ECE
	msgbox SootopolisCity_Text_AwakenedPokemonClash, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_Kiri:: @ 81E5ED8
	lock
	faceplayer
	compare VAR_SOOTOPOLIS_CITY_STATE, 1
	goto_if_le SootopolisCity_EventScript_KiriGiveBerry
	compare VAR_SOOTOPOLIS_CITY_STATE, 6
	goto_if_ge SootopolisCity_EventScript_KiriGiveBerry
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	goto_if_eq SootopolisCity_EventScript_KiriRayquaza
	msgbox SootopolisCity_Text_BigPokemonFighting, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_KIRI, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SootopolisCity_EventScript_KiriRayquaza:: @ 81E5F10
	msgbox SootopolisCity_Text_PrettyMonCameFromSky, MSGBOX_DEFAULT
	closemessage
	release
	end

@ Gives 2 berries daily. First ranges from FIRST_KIRI_BERRY to LAST_KIRI_BERRY, second is always Figy or Iapapa
SootopolisCity_EventScript_KiriGiveBerry:: @ 81E5F1B
	dotimebasedevents
	special GetPlayerBigGuyGirlString
	goto_if_set FLAG_DAILY_SOOTOPOLIS_RECEIVED_BERRY, SootopolisCity_EventScript_KiriReceivedBerry
	msgbox SootopolisCity_Text_NameIsKiriHaveOneOfThese, MSGBOX_DEFAULT
	random NUM_KIRI_BERRIES
	addvar VAR_RESULT, NUM_KIRI_BERRIES_SKIPPED
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_SOOTOPOLIS_RECEIVED_BERRY
	msgbox SootopolisCity_Text_GiveYouThisBerryToo, MSGBOX_DEFAULT
	random 2
	compare VAR_RESULT, 0
	goto_if_eq SootopolisCity_EventScript_GiveFigyBerry
	compare VAR_RESULT, 1
	goto_if_eq SootopolisCity_EventScript_GiveIapapaBerry
	end

SootopolisCity_EventScript_GiveFigyBerry:: @ 81E5F79
	giveitem ITEM_FIGY_BERRY
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	msgbox SootopolisCity_Text_WhatKindOfWishInYourName, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_GiveIapapaBerry:: @ 81E5F9A
	giveitem ITEM_IAPAPA_BERRY
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	msgbox SootopolisCity_Text_WhatKindOfWishInYourName, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_KiriReceivedBerry:: @ 81E5FBB
	msgbox SootopolisCity_Text_LikeSeasonBornIn, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SootopolisCity_EventScript_KiriLikeSeasonBornIn
	msgbox SootopolisCity_Text_OhDoesntMatter, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_KiriLikeSeasonBornIn:: @ 81E5FD8
	msgbox SootopolisCity_Text_ThenILoveAutumn, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_Woman2:: @ 81E5FE2
	lockall
	applymovement LOCALID_WOMAN_2, Common_Movement_FacePlayer
	waitmovement 0
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	goto_if_eq SootopolisCity_EventScript_Woman2Rayquaza
	msgbox SootopolisCity_Text_WeatherWentWild, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WOMAN_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SootopolisCity_EventScript_Woman2Rayquaza:: @ 81E600D
	msgbox SootopolisCity_Text_YouBroughtFlyingMon, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_EventScript_Man:: @ 81E6017
	lock
	faceplayer
	compare VAR_SOOTOPOLIS_CITY_STATE, 6
	goto_if_ge SootopolisCity_EventScript_ManPostLegendaries
	msgbox SootopolisCity_Text_NoOrdinaryTourist, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_ManPostLegendaries:: @ 81E602E
	msgbox SootopolisCity_Text_CityRegainedCalm, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_Woman1:: @ 81E6038
	lock
	faceplayer
	compare VAR_SOOTOPOLIS_CITY_STATE, 6
	goto_if_ge SootopolisCity_EventScript_Woman1PostLegendaries
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	goto_if_eq SootopolisCity_EventScript_Woman1Rayquaza
	compare VAR_SOOTOPOLIS_CITY_STATE, 2
	goto_if_ge SootopolisCity_EventScript_Woman1Legendaries
	msgbox SootopolisCity_Text_SootopolisSkyBeautiful, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_Woman1Legendaries:: @ 81E6065
	msgbox SootopolisCity_Text_GiganticPokemonFight, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WOMAN_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SootopolisCity_EventScript_Woman1PostLegendaries:: @ 81E607A
	msgbox SootopolisCity_Text_NightSkyFavoriteScenery, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_Woman1Rayquaza:: @ 81E6084
	msgbox SootopolisCity_Text_FearedWorstWhenPokemonFlewDown, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_NinjaBoy:: @ 81E608E
	lockall
	applymovement LOCALID_NINJA_BOY, Common_Movement_FacePlayer
	waitmovement 0
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	goto_if_eq SootopolisCity_EventScript_NinjaBoyRayquaza
	compare VAR_SOOTOPOLIS_CITY_STATE, 6
	goto_if_ge SootopolisCity_EventScript_NinjaBoyNormal
	compare VAR_SOOTOPOLIS_CITY_STATE, 1
	goto_if_le SootopolisCity_EventScript_NinjaBoyNormal
	msgbox SootopolisCity_Text_ThisIsWicked, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_NINJA_BOY, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SootopolisCity_EventScript_NinjaBoyNormal:: @ 81E60CF
	msgbox SootopolisCity_Text_WonderWhatWorldIsLike, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_NinjaBoyRayquaza:: @ 81E60D9
	msgbox SootopolisCity_Text_ThatWasWicked, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_Boy1:: @ 81E60E3
	lockall
	applymovement LOCALID_BOY_1, Common_Movement_FacePlayer
	waitmovement 0
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	goto_if_eq SootopolisCity_EventScript_Boy1Rayquaza
	goto_if_set FLAG_SYS_GAME_CLEAR, SootopolisCity_EventScript_Boy1GameClear
	compare VAR_SOOTOPOLIS_CITY_STATE, 6
	goto_if_ge SootopolisCity_EventScript_Boy1Normal
	compare VAR_SOOTOPOLIS_CITY_STATE, 1
	goto_if_le SootopolisCity_EventScript_Boy1Normal
	msgbox SootopolisCity_Text_GiantPokemonSuddenlyAppeared, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BOY_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SootopolisCity_EventScript_Boy1Rayquaza:: @ 81E612D
	msgbox SootopolisCity_Text_WhatIsThatGreenPokemon, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_Boy1GameClear:: @ 81E6137
	msgbox SootopolisCity_Text_WhereDidLegendariesGo, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_Boy1Normal:: @ 81E6141
	msgbox SootopolisCity_Text_PhysicallyFitLivingHere, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_GymSign:: @ 81E614B
	msgbox SootopolisCity_Text_GymSign, MSGBOX_SIGN
	end

SootopolisCity_EventScript_CitySign:: @ 81E6154
	msgbox SootopolisCity_Text_CitySign, MSGBOX_SIGN
	end

EventScript_ClosedSootopolisDoor:: @ 81E615D
	msgbox SootopolisCity_Text_DoorIsClosed, MSGBOX_SIGN
	end

SootopolisCity_EventScript_Steven:: @ 81E6166
	lockall
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	call_if_unset FLAG_STEVEN_GUIDES_TO_CAVE_OF_ORIGIN, SootopolisCity_EventScript_StevenLeadPlayerCaveOfOrigin
	compare VAR_SOOTOPOLIS_CITY_STATE, 2
	goto_if_eq SootopolisCity_EventScript_StevenHelpWallace
	compare VAR_SOOTOPOLIS_CITY_STATE, 3
	goto_if_eq SootopolisCity_EventScript_StevenHelpedWallace
	compare VAR_SOOTOPOLIS_CITY_STATE, 4
	goto_if_eq SootopolisCity_EventScript_StevenHelpedWallace
	goto_if_set FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE, SootopolisCity_EventScript_StevenMaxieArchieLeft
	msgbox SootopolisCity_Text_SoThatsRayquaza, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_EventScript_StevenHelpWallace:: @ 81E61AE
	msgbox SootopolisCity_Text_KnowWhatsNeededToHelpHim, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_EventScript_StevenMaxieArchieLeft:: @ 81E61B8
	msgbox SootopolisCity_Text_MaxieArchieLeft, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_EventScript_StevenHelpedWallace:: @ 81E61C2
	msgbox SootopolisCity_Text_NeverBeenToSkyPillar, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_EventScript_StevenLeadPlayerCaveOfOrigin:: @ 81E61CC
	msgbox SootopolisCity_Text_InvolvedWithCrisisComeWithMe, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_WEST
	call_if_eq SootopolisCity_EventScript_StartWalkToCaveOfOriginWest
	compare VAR_FACING, DIR_NORTH
	call_if_eq SootopolisCity_EventScript_StartWalkToCaveOfOriginNorth
	msgbox SootopolisCity_Text_DoesThisMakeYourFearPokemon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_STEVEN, SootopolisCity_Movement_StevenWalkToCaveOfOrigin
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_Movement_PlayerWalkToCaveOfOrigin
	waitmovement 0
	delay 120
	applymovement LOCALID_EXPERT, SootopolisCity_Movement_ExpertMoveAside
	waitmovement 0
	applymovement LOCALID_STEVEN, SootopolisCity_Movement_StevenArriveCaveEntrance
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_Movement_PlayerArriveCaveEntrance
	waitmovement 0
	msgbox SootopolisCity_Text_HereWereAreHelpWallace, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_STEVEN_GUIDES_TO_CAVE_OF_ORIGIN
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_Movement_PlayerEnterCaveOfOrigin
	waitmovement 0
	warp MAP_CAVE_OF_ORIGIN_ENTRANCE, 255, 9, 20
	waitstate
	end

SootopolisCity_EventScript_StartWalkToCaveOfOriginWest:: @ 81E6243
	applymovement LOCALID_STEVEN, SootopolisCity_Movement_StevenStartWalkToCaveOfOrigin
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_Movement_PlayerStartWalkToCaveOfOriginWest
	waitmovement 0
	return

SootopolisCity_EventScript_StartWalkToCaveOfOriginNorth:: @ 81E6255
	applymovement LOCALID_STEVEN, SootopolisCity_Movement_StevenStartWalkToCaveOfOrigin
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_Movement_PlayerStartWalkToCaveOfOriginNorth
	waitmovement 0
	return

SootopolisCity_Movement_StevenStartWalkToCaveOfOrigin: @ 81E6267
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

SootopolisCity_Movement_PlayerStartWalkToCaveOfOriginWest: @ 81E628C
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SootopolisCity_Movement_PlayerStartWalkToCaveOfOriginNorth: @ 81E62B0
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SootopolisCity_Movement_StevenWalkToCaveOfOrigin: @ 81E62D4
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	delay_4
	walk_in_place_fastest_left
	delay_16
	delay_16
	walk_right
	walk_up
	walk_up
	step_end

SootopolisCity_Movement_PlayerWalkToCaveOfOrigin: @ 81E630E
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

SootopolisCity_Movement_ExpertMoveAside: @ 81E6341
	walk_slow_left
	walk_in_place_fastest_right
	step_end

SootopolisCity_Movement_StevenArriveCaveEntrance: @ 81E6344
	walk_down
	walk_down
	walk_left
	delay_8
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	walk_in_place_fastest_left
	step_end

SootopolisCity_Movement_PlayerArriveCaveEntrance: @ 81E634F
	delay_16
	delay_16
	delay_16
	delay_8
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_right
	step_end

SootopolisCity_Movement_PlayerEnterCaveOfOrigin: @ 81E635A
	walk_up
	walk_up
	step_end

SootopolisCity_EventScript_Boy2:: @ 81E635D
	lockall
	applymovement LOCALID_BOY_2, Common_Movement_FacePlayer
	waitmovement 0
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	goto_if_eq SootopolisCity_EventScript_Boy2Rayquaza
	msgbox SootopolisCity_Text_TwoPokemonArentAngry, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BOY_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SootopolisCity_EventScript_Boy2Rayquaza:: @ 81E6388
	msgbox SootopolisCity_Text_FlyingMonStoppedRampage, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

SootopolisCity_EventScript_BlackBelt:: @ 81E6393
	lockall
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	goto_if_eq SootopolisCity_EventScript_BlackBeltRayquaza
	msgbox SootopolisCity_Text_GoRedAndBlueMon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BLACK_BELT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SootopolisCity_Text_DoYouKnowMonNames, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BLACK_BELT, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SootopolisCity_EventScript_BlackBeltRayquaza:: @ 81E63C7
	applymovement LOCALID_BLACK_BELT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SootopolisCity_Text_GreenOneSettlesThings, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_EventScript_Girl:: @ 81E63DB
	lockall
	applymovement LOCALID_GIRL, Common_Movement_FacePlayer
	waitmovement 0
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	goto_if_eq SootopolisCity_EventScript_GirlRayquaza
	msgbox SootopolisCity_Text_SootopolisWillBeWrecked, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GIRL, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SootopolisCity_EventScript_GirlRayquaza:: @ 81E6406
	msgbox SootopolisCity_Text_SootopolisDidntGetWrecked, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

SootopolisCity_EventScript_Maniac:: @ 81E6411
	lockall
	applymovement LOCALID_MANIAC, Common_Movement_FacePlayer
	waitmovement 0
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	goto_if_eq SootopolisCity_EventScript_ManiacRayquaza
	msgbox SootopolisCity_Text_SeeingLegendWithOwnEyes, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MANIAC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SootopolisCity_EventScript_ManiacRayquaza:: @ 81E643C
	msgbox SootopolisCity_Text_SawLegendWithOwnEyes, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_EventScript_Wallace:: @ 81E6446
	lock
	faceplayer
	compare VAR_SOOTOPOLIS_CITY_STATE, 4
	goto_if_eq SootopolisCity_EventScript_GoToSkyPillar
	goto_if_set FLAG_RECEIVED_HM07, SootopolisCity_EventScript_GoToGym
	goto_if_set FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE, SootopolisCity_EventScript_GiveWaterfall
	msgbox SootopolisCity_Text_AquaMagmaDidntMeanHarm, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_GiveWaterfall:: @ 81E646F
	msgbox SootopolisCity_Text_ThankYouForHelpAcceptThis, MSGBOX_DEFAULT
	giveitem ITEM_HM07
	setflag FLAG_RECEIVED_HM07
	msgbox SootopolisCity_Text_ExplainWaterfallGoToGym, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_NORTH
	call_if_eq SootopolisCity_EventScript_WallaceMoveFromGym
	compare VAR_FACING, DIR_EAST
	call_if_eq SootopolisCity_EventScript_WallaceMoveFromGym
	compare VAR_FACING, DIR_WEST
	call_if_eq SootopolisCity_EventScript_WallaceMoveFromGymWest
	release
	end

SootopolisCity_EventScript_WallaceMoveFromGym:: @ 81E64B2
	applymovement LOCALID_WALLACE, SootopolisCity_Movement_WallaceMoveFromGym
	waitmovement 0
	copyobjectxytoperm LOCALID_WALLACE
	setvar VAR_SOOTOPOLIS_WALLACE_STATE, 1
	return

SootopolisCity_EventScript_WallaceMoveFromGymWest:: @ 81E64C5
	applymovement LOCALID_WALLACE, SootopolisCity_Movement_WallaceMoveFromGymWest
	waitmovement 0
	copyobjectxytoperm LOCALID_WALLACE
	setvar VAR_SOOTOPOLIS_WALLACE_STATE, 2
	return

SootopolisCity_EventScript_GoToSkyPillar:: @ 81E64D8
	msgbox SootopolisCity_Text_HaventYouScaledSkyPillar, MSGBOX_DEFAULT
	release
	end

SootopolisCity_EventScript_GoToGym:: @ 81E64E2
	msgbox SootopolisCity_Text_DazzledByMentor, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Movement_WallaceMoveFromGym: @ 81E64EC
	walk_right
	walk_in_place_fastest_down
	step_end

SootopolisCity_Movement_WallaceMoveFromGymWest: @ 81E64EF
	walk_left
	walk_in_place_fastest_down
	step_end

SootopolisCity_EventScript_Maxie:: @ 81E64F2
	lockall
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	goto_if_eq SootopolisCity_EventScript_MaxieRayquaza
	msgbox SootopolisCity_Text_GroudonPleaseStop, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

SootopolisCity_EventScript_MaxieRayquaza:: @ 81E6509
	msgbox SootopolisCity_Text_AfterAllOurScheming, MSGBOX_DEFAULT
	setflag FLAG_MET_MAXIE_SOOTOPOLIS
	goto_if_set FLAG_MET_ARCHIE_SOOTOPOLIS, SootopolisCity_EventScript_MaxieArchieLeave
	releaseall
	end

SootopolisCity_EventScript_Archie:: @ 81E651F
	lockall
	compare VAR_SOOTOPOLIS_CITY_STATE, 5
	goto_if_eq SootopolisCity_EventScript_ArchieRayquaza
	msgbox SootopolisCity_Text_KyogreCalmDown, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

SootopolisCity_EventScript_ArchieRayquaza:: @ 81E6536
	msgbox SootopolisCity_Text_TryingMeaninglessToPokemon, MSGBOX_DEFAULT
	setflag FLAG_MET_ARCHIE_SOOTOPOLIS
	goto_if_set FLAG_MET_MAXIE_SOOTOPOLIS, SootopolisCity_EventScript_MaxieArchieLeave
	releaseall
	end

SootopolisCity_EventScript_MaxieArchieLeave:: @ 81E654C
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_MAXIE
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_ARCHIE
	setflag FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_MAXIE
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_ARCHIE
	setvar VAR_MT_PYRE_STATE, 2
	warpsilent MAP_SOOTOPOLIS_CITY, 255, 31, 34
	waitstate
	releaseall
	end

@ Unused
SootopolisCity_Movement_Levitate:: @ 81E656B
	levitate
	step_end

@ Unused
SootopolisCity_Movement_DestroyTask:: @ 81E656D
	destroy_extra_task
	step_end

SootopolisCity_Text_GymSign: @ 81E656F
	.string "루네시티 포켓몬체육관\n"
	.string "관장 아단\l"
	.string "물이 싱그러운 체육관 관장!$"
	// ルネ シティ ポケモンジムｎ
	// リ-ダ- アダンｌ
	// みずも したたる ジムリ-ダ-!

SootopolisCity_Text_CitySign: @ 81E65C8
	.string "여기는 루네시티\n"
	.string "역사가 잠들어 있는 신비한 마을$"
	// ここは ルネ シティｎ
	// れきしが ねむる しんぴの まち

SootopolisCity_Text_DoorIsClosed: @ 81E6604
	.string "문이 닫혀 있다!$"
	// とびらは とざされて いる!

SootopolisCity_Text_PhysicallyFitLivingHere: @ 81E6618
	.string "바다로 잠수하거나\n"
	.string "계단을 오르락내리락...\p"
	.string "이 마을에서 살다 보면\n"
	.string "몸이 꽤 튼튼해진단 말이지$"
	// うみに もぐったりｎ
	// かいだんを のぼったり おりたり……ｐ
	// このまちで くらして いるとｎ
	// けっこう たくましく なるんだよね

SootopolisCity_Text_GiantPokemonSuddenlyAppeared: @ 81E6692
	.string "커다란 포켓몬이 갑자기\n"
	.string "마을 한가운데에 나타났어!\l"
	.string "게다가 본 적도 없는 게 두 마리나!\p"
	.string "저 두 마리...\n"
	.string "왜 싸우고 있는 거야?\l"
	.string "포켓몬끼리 사이좋게 지내면 안 돼?$"
	// おっきな ポケモンが とつぜんｎ
	// まちの まんなかに あらわれたんだ!ｌ
	// しかも みたことない やつが 2ひきも!ｐ
	// あの 2ひき……ｎ
	// どうして ぶつかり あってるの?ｌ
	// ポケモンどうし なかよく できないの?

SootopolisCity_Text_WhatIsThatGreenPokemon: @ 81E6750
	.string "뭐야? 뭐야? 뭐야?\n"
	.string "저 초록색 포켓몬은 뭐야-!?$"
	// なに? なに? なに?ｎ
	// あの みどりの ポケモン なに-!?

SootopolisCity_Text_WhereDidLegendariesGo: @ 81E677F
	.string "그란돈과 가이오가\n"
	.string "어디로 가버린 걸까...\p"
	.string "또 어딘가에서 가뭄이나\n"
	.string "폭우를 일으키며 다니는 걸까?$"
	// グラ-ドンと カイオ-ガｎ
	// どこ いっちゃったんだろう……ｐ
	// また どこかで ひでりに したりｎ
	// おおあめ ふらせたり してるのかな?

SootopolisCity_Text_TwoPokemonArentAngry: @ 81E67DC
	.string "왠지 모르게 느껴져... 저 두 마리\n"
	.string "화난 게 아닌가봐\p"
	.string "아마... 자신의 힘을\n"
	.string "컨트롤할 수 없는 걸 거야...$"
	// なんとなく かんじるよ…… あの2ひきｎ
	// おこってる わけじゃ ないみたいｐ
	// たぶん…… じぶんの ちからをｎ
	// コントロ-ル できなく なってるんだ……

SootopolisCity_Text_FlyingMonStoppedRampage: @ 81E6853
	.string "하늘에서 온 포켓몬이\n"
	.string "날뛰고 있던 두 마리를\l"
	.string "조용하게 만들었어...$"
	// そらから きた ポケモンがｎ
	// あばれていた 2ひきをｌ
	// おとなしく させちゃった……

SootopolisCity_Text_WonderWhatWorldIsLike: @ 81E68A1
	.string "나 아직 단 한 번도 이 마을에서\n"
	.string "벗어나 본 적이 없어\p"
	.string "저 동그란 하늘 저편에는\n"
	.string "어떤 세계가 있는 걸까?$"
	// ぼく…… まだ いちども このまちからｎ
	// そとに でたこと ないんだｐ
	// あの まあるい そらの むこうにはｎ
	// どんな せかいが あるのかな?

SootopolisCity_Text_ThisIsWicked: @ 81E690B
	.string "굉장해- 완전 박력 있어!$"
	// すげ- だいはくりょく!

SootopolisCity_Text_ThatWasWicked: @ 81E6920
	.string "굉장해- 완전 박력 있었어!$"
	// すげ- だいはくりょく だった!

SootopolisCity_Text_GoRedAndBlueMon: @ 81E6936
	.string "가라! 빨간 포켓몬!\n"
	.string "지지 마! 파란 포켓몬!$"
	// それいけ! あかい ポケモン!ｎ
	// まけるな! あおい ポケモン!

SootopolisCity_Text_DoYouKnowMonNames: @ 81E696C
	.string "...... ...... ......\p"
	.string "너 저기서 싸우고 있는\n"
	.string "포켓몬들의 이름 알아?$"
	// …… …… ……ｐ
	// きみ あそこで たたかってるｎ
	// ポケモンたちの なまえ しってる?

SootopolisCity_Text_GreenOneSettlesThings: @ 81E69B8
	.string "빨간 포켓몬과 파란 포켓몬\n"
	.string "어느 쪽이 이길까 고민했는데\l"
	.string "초록색 포켓몬이 이겼네!\p"
	.string "정말 대역전극이었어!$"
	// あかい ポケモンと あおい ポケモンｎ
	// どっちが かつのかと おもったらｌ
	// みどりの ポケモンかよ!ｐ
	// こりゃ だいドンデンがえしだ!

SootopolisCity_Text_SeeingLegendWithOwnEyes: @ 81E6A50
	.string "포켓몬의 싸움에 의해\n"
	.string "땅과 바다가 만들어졌다고 하는\l"
	.string "먼 옛날부터 전해진 얘기가\p"
	.string "지금 눈앞에서 펼쳐지고 있어!\p"
	.string "우오오-! 이런 굉장한 걸\n"
	.string "직접 보게 되다니-!!$"
	// ポケモンの たたかいに よってｎ
	// りくちと うみが つくられた というｌ
	// おおむかし からの いいつたえがｐ
	// いま めのまえで さいげん されている!ｐ
	// うぉぉ-! こんな すごいものをｎ
	// この めで みられる なんて-!!

SootopolisCity_Text_SawLegendWithOwnEyes: @ 81E6B2A
	.string "포켓몬의 싸움에 의해\n"
	.string "땅과 바다가 만들어졌다고 하는\l"
	.string "먼 옛날부터 전해진 얘기가\p"
	.string "지금 이 마을에서 재현됐어!\p"
	.string "우오오-! 이런 굉장한 걸\n"
	.string "직접 봤다니-!!$"
	// ポケモンの たたかいに よってｎ
	// りくちと うみが つくられた というｌ
	// おおむかし からの いいつたえがｐ
	// いま このまちで さいげん された!ｐ
	// うぉぉ-! こんな すごいものをｎ
	// この めで みられた なんて-!!

SootopolisCity_Text_BigPokemonFighting: @ 81E6BFF
	.string "커다란 포켓몬과 포켓몬이\n"
	.string "싸우고 있어!\p"
	.string "누가 좀 멈춰줘!$"
	// おっきな ポケモンと ポケモンがｎ
	// けんか してるよ!ｐ
	// だれか とめて あげて!

SootopolisCity_Text_PrettyMonCameFromSky: @ 81E6C53
	.string "아름다운 포켓몬이\n"
	.string "하늘에서 내려왔어...$"
	// きれいな ポケモンｎ
	// おそらから おりて きた……

SootopolisCity_Text_SootopolisWillBeWrecked: @ 81E6C7C
	.string "히익- 루네시티가 무너질 거야-!$"
	// ひ- ルネシティが こわれちゃうよ-!

SootopolisCity_Text_SootopolisDidntGetWrecked: @ 81E6CA6
	.string "루네시티가 무너지지 않았어-!$"
	// ルネシティ こわれないで すんだよ-!

SootopolisCity_Text_NoOrdinaryTourist: @ 81E6CCA
	.string "호오!\n"
	.string "일부러 여기 루네시티까지 오다니\l"
	.string "평범한 관광객은 아니군!\p"
	.string "그렇다고 돈을 내고 온\n"
	.string "관광객도 아니고...$"
	// ほう!ｎ
	// わざわざ ルネに やってくるとはｌ
	// ただの かんこうきゃく じゃ ないな!ｐ
	// だからといって おかねを はらったｎ
	// かんこうきゃく でも ないな……

SootopolisCity_Text_CityRegainedCalm: @ 81E6D57
	.string "마을이 다시 조용해졌어...$"
	// まちが また しずかに なった……

SootopolisCity_Text_CaveOfOriginPleaseLeave: @ 81E6D77
	.string "당신은 무슨 일로 오셨나요?\p"
	.string "이곳은 각성의 사당...\p"
	.string "송화산에서 잠든\n"
	.string "포켓몬의 영혼이\l"
	.string "되살아난다고 전해지는 장소...\p"
	.string "부디 돌아가 주십시오$"
	// あなたは なんですかな?ｐ
	// ここは めざめのほこら……ｐ
	// おくりびやまで しずめられたｎ
	// ポケモンの たましいがｌ
	// よみがえると いわれる ばしょ……ｐ
	// どうか おひきとり ください

SootopolisCity_Text_LeadSuperiorTrainerToCave: @ 81E6DFE
	.string "강한 의지와 뛰어난 재능\p"
	.string "그리고 수많은 포켓몬을 봐온\n"
	.string "지식과 경험...\p"
	.string "그런 인물이 찾아온다면\n"
	.string "이 사당으로 안내하라고\l"
	.string "윤진님께 들었습니다$"
	// つよい いしと すぐれた さいのうｐ
	// そして たくさんの ポケモンを みてきたｎ
	// ちしきと けいけん……ｐ
	// そんな じんぶつが やってきたらｎ
	// この ほこらへ あんない するようｌ
	// ミクリから もうしつけられて いたのです

SootopolisCity_Text_AwakenedPokemonClash: @ 81E6ED4
	.string "오오...\p"
	.string "각성한 두 마리의 싸움을\n"
	.string "다른 한 마리의 각성이 잠재웠어...$"
	// おお……ｐ
	// めざめた 2ひきの あらそいをｎ
	// もう 1ひきの めざめが しずめた……

SootopolisCity_Text_CaveOfOriginSleepsToo: @ 81E6F38
	.string "여기는 각성의 사당...\p"
	.string "하지만 재앙이 사라진 지금\n"
	.string "사당도 조용히 잠들겠지요...$"
	// ここは めざめのほこら……ｐ
	// けれど わざわいが きえさった いまｎ
	// ほこらも しずかに ねむるのです……

SootopolisCity_Text_SootopolisSkyBeautiful: @ 81E6F90
	.string "루네시티는 운석의 낙하로 인해 생긴\n"
	.string "크레이터의 중심에 있는 마을이야\p"
	.string "위를 보면 크레이터의 가장자리도\n"
	.string "같이 보여서\l"
	.string "하늘 전체를 볼 수는 없어...\p"
	.string "하지만 그렇기 때문에\n"
	.string "루네시티에서 보이는 하늘이\l"
	.string "가장 아름다워$"
	// ルネは かざんのｎ
	// かこうの なかに できた まちｐ
	// うえを みあげるとｎ
	// かこうも いっしょに みえてしまってｌ
	// そらの すべては みえないｐ
	// でも だからこそｎ
	// ルネから みえる そらがｌ
	// いちばん うつくしいの

SootopolisCity_Text_GiganticPokemonFight: @ 81E7078
	.string "저렇게 큰 포켓몬이\n"
	.string "두 마리나 날뛰다니\l"
	.string "어떻게 해야 할지 모르겠어!$"
	// あんなに おおきな ポケモンがｎ
	// 2ひきも あばれている なんてｌ
	// とても わたしたちの てに おえないわ!

SootopolisCity_Text_FearedWorstWhenPokemonFlewDown: @ 81E70D4
	.string "세 번째 커다란 포켓몬이\n"
	.string "하늘에서 내려왔을 때부터\l"
	.string "이젠 끝인가 싶었지...$"
	// 3ひきめの おおきな ポケモンがｎ
	// そらから おりてきた ときにはｌ
	// もう どうなることかと おもったわ……

SootopolisCity_Text_NightSkyFavoriteScenery: @ 81E710B
	.string "운석의 크레이터라는\n"
	.string "고리에 둘러싸인 둥근 밤하늘\p"
	.string "그 안에서는 수많은 별이\n"
	.string "살아 있는 것처럼 반짝여...\l"
	.string "내가 제일 좋아하는 풍경이야$"
	// かざんの かこう というｎ
	// わっかに かこまれた まるい よぞらｐ
	// その なかでは たくさんの ほしがｎ
	// いきている みたいに またたくの……ｌ
	// わたしが いちばん すきな けしき

SootopolisCity_Text_WeatherWentWild: @ 81E71A1
	.string "오늘 아침엔 날씨가 엄청 좋았어\n"
	.string "그런데...\p"
	.string "갑자기 구름이 드리우고\n"
	.string "강한 비가 내리기 시작하더니\l"
	.string "번개도 우르릉 치고\l"
	.string "날씨가 엉망진창이 됐어\p"
	.string "이것도 저것도 전부\n"
	.string "저 포켓몬 때문일까...?$"
	// きょうの あさは いいてんき だったのよｎ
	// それが……ｐ
	// とつぜん くもり はじめたと おもったらｎ
	// つよい あめが ふりだしてｌ
	// かみなりも ゴロゴロ なりだしてｌ
	// てんきが メチャメチャに なっちゃったのｐ
	// それも これも ぜんぶｎ
	// あの ポケモンの せい かしら……?

SootopolisCity_Text_YouBroughtFlyingMon: @ 81E728C
	.string "뭐!\p"
	.string "그 하늘로부터 내려온 포켓몬을\n"
	.string "데리고 온 게 너라고!?\p"
	.string "...흐음 제법인데!$"
	// えっ!ｐ
	// あの そらから おりてきた ポケモンをｎ
	// つれてきたの って あなたなの!?ｐ
	// ……へえ やるじゃない!

SootopolisCity_Text_GroudonPleaseStop: @ 81E72DB
	.string "마적: 그... 그란돈...\n"
	.string "부탁이니 이제 그만해!\p"
	.string "너의 힘은 이제 알았다!\p"
	.string "이대로라면 루네시티뿐만 아니라\n"
	.string "호연지방 전체가\l"
	.string "엉망진창이 될 거야!$"
	// マツブサ『グ… グラ-ドン……ｎ
	// たのむから もう やめてくれ!ｐ
	// おまえの ちからは もう わかった!ｐ
	// このままでは ルネ だけじゃないｎ
	// ホウエンじゅうがｌ
	// めちゃめちゃに なってしまう!

SootopolisCity_Text_AfterAllOurScheming: @ 81E737E
	.string "마적: 초 고대포켓몬은\n"
	.string "그란돈과 가이오가만 있던 게\l"
	.string "아니었다는 건가...\p"
	.string "우리는 필사적으로\n"
	.string "이곳저곳을 돌아다녔는데\l"
	.string "그 포켓몬의 힘 한 번으로\l"
	.string "전부 원래대로 돌아왔군...\p"
	.string "흐... 흐하하하...$"
	// マツブサ『ちょうこだい ポケモンはｎ
	// グラ-ドンと カイオ-ガ だけじゃｌ
	// なかったと いうのか……ｐ
	// われわれは ひっしに なってｎ
	// あれこれ うごきまわって きたがｌ
	// あの ポケモンの ひとはたらきでｌ
	// ぜんぶ もとどおり というわけか……ｐ
	// ふ…… ふははは……

SootopolisCity_Text_KyogreCalmDown: @ 81E7460
	.string "아강: 가이오가! 어떻게 된 거야!?\n"
	.string "이걸 봐라! 주홍구슬이다!\l"
	.string "말을 듣는 거다! 가이오가!\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "틀렸어! 전혀 말을 듣지 않아!$"
	// アオギリ『カイオ-ガ! どうした!?ｎ
	// これを みろ! べにいろのたま だぞ!ｌ
	// おとなしくなるんだ! カイオ-ガ!ｐ
	// …… …… ……ｎ
	// …… …… ……ｐ
	// だめだ! ぜんぜん きかない!

SootopolisCity_Text_TryingMeaninglessToPokemon: @ 81E74F6
	.string "아강: 가이오가와 그란돈은\n"
	.string "어딘가로 가버렸군\p"
	.string "그리고 호연의 날씨도\n"
	.string "다시 원래대로 돌아왔고...\p"
	.string "하하 하하하...\p"
	.string "우리가 해왔던 건\n"
	.string "포켓몬에게 있어서\l"
	.string "정말 보잘것없는 거였을지도...$"
	// アオギリ『カイオ-ガと グラ-ドンはｎ
	// どこかへ とびさって しまったｐ
	// そして ホウエンの てんきもｎ
	// また もとどおりに なった……ｐ
	// はは ははは……ｐ
	// おれたちの やろうと したことはｎ
	// ポケモンから みればｌ
	// ちっぽけなこと だったの かもな……

SootopolisCity_Text_InvolvedWithCrisisComeWithMe: @ 81E75CB
	.string "성호: 저기서 싸우고 있는 건\n"
	.string "그란돈...\l"
	.string "그리고 가이오가...\p"
	.string "긴 잠으로부터 눈을 뜬\n"
	.string "두 마리의 초 고대포켓몬은\p"
	.string "어떻게 할 수 없는 에너지를\n"
	.string "서로에게 부딪치고 있어...\p"
	.string "...{PLAYER}\p"
	.string "여기까지 왔다는 건\n"
	.string "넌 이 사건에 끼어들\l"
	.string "각오가 되어있다는 거겠지\p"
	.string "좋아! 그렇다면\n"
	.string "너에게 소개할 사람이 있어\p"
	.string "잠깐 나를 따라와줘$"
	// ダイゴ『あそこで たたかって いるのはｎ
	// グラ-ドン……ｌ
	// そして カイオ-ガ……ｐ
	// ながい ねむりから めざめたｎ
	// 2ひきの ちょうこだい ポケモンはｐ
	// やりばのない エネルギ-をｎ
	// おたがいに ぶつけあっている……ｐ
	// ……§あ§おｐ
	// ここまで きた ということはｎ
	// きみは このじけんに かかわるｌ
	// かくごが できている ということだねｐ
	// よし! それならｎ
	// きみに あわせたい ひとが いるんだｐ
	// ちょっと ボクに ついておいで

SootopolisCity_Text_DoesThisMakeYourFearPokemon: @ 81E7737
	.string "성호: 저기 {PLAYER}\n"
	.string "그란돈과 가이오가를 보고\l"
	.string "포켓몬이 두렵다고 생각했어?\p"
	.string "하지만 그렇지는 않아\n"
	.string "포켓몬은 사실 좀 더...\p"
	.string "...아니 너라면 그런 건\n"
	.string "이미 알고 있겠지$"
	// ダイゴ『ねえ §あ§おｎ
	// グラ-ドンと カイオ-ガを みてｌ
	// ポケモンは こわいものだと おもったかい?ｐ
	// でも そんなことは ないんだよｎ
	// ポケモンって ほんとうは もっと……ｐ
	// ……いや きみなら そんなことはｎ
	// もう とっくに きがついて いるよね

SootopolisCity_Text_HereWereAreHelpWallace: @ 81E77F0
	.string "성호: 자 도착했어!\p"
	.string "이 안에 윤진이라고 하는\n"
	.string "사람이 있어\p"
	.string "너라면 그의 힘이\n"
	.string "되어줄 수 있을 거라고 생각해...$"
	// ダイゴ『さあ ついた!ｐ
	// このおくに ミクリさん というｎ
	// ひとが いるんだｐ
	// きみなら かれの ちからにｎ
	// なって あげられると おもうよ……

SootopolisCity_Text_KnowWhatsNeededToHelpHim: @ 81E7866
	.string "성호: 너라면 그의 힘이\n"
	.string "되어줄 수 있을 거라고 생각해...$"
	// ダイゴ『きみなら かれの ちからにｎ
	// なって あげられると おもうよ……

SootopolisCity_Text_NeverBeenToSkyPillar: @ 81E789A
	.string "성호: 하늘기둥...\n"
	.string "나도 아직 가본 적이 없는데\l"
	.string "대체 어디에 있는 걸까$"
	// ダイゴ『そらのはしら……ｎ
	// ボクも まだ いったことが ないけどｌ
	// いったい どこに あるんだろうね

SootopolisCity_Text_SoThatsRayquaza: @ 81E78E5
	.string "성호: 저게 레쿠쟈...\p"
	.string "날뛰고 있던 두 마리가\n"
	.string "겁먹고 도망가다니 대단한걸...$"
	// ダイゴ『あれが レックウザか……ｐ
	// あばれていた 2ひきが おそれをなしてｎ
	// さっていく なんて すごいや……

SootopolisCity_Text_MaxieArchieLeft: @ 81E794B
	.string "성호: 마적과 아강 두 사람은\n"
	.string "어딘가로 가버린 모양이야\p"
	.string "어쩌면 송화산에\n"
	.string "구슬을 돌려주러 갔을지도...$"
	// ダイゴ『マツブサと アオギリの ふたりはｎ
	// どこかへ いって しまった ようだねｐ
	// もしかすると おくりびやまにｎ
	// たまを かえしに いったのかも……

SootopolisCity_Text_HaventYouScaledSkyPillar: @ 81E79C8
	.string "윤진: 어라? {PLAYER}\p"
	.string "그 이후로 하늘기둥을\n"
	.string "오른 게 아니었어?\p"
	.string "너라면 분명 갈 수 있을 거야\n"
	.string "하늘기둥의 꼭대기에...$"
	// ミクリ『おや? §あ§おｐ
	// あれから そらのはしらを のぼってｎ
	// いかなかったのかい?ｐ
	// きみなら きっと いけるさｎ
	// そらのはしらの おくじょうへ……

SootopolisCity_Text_AquaMagmaDidntMeanHarm: @ 81E7A3E
	.string "윤진: {PLAYER}...\p"
	.string "마그마단과 아쿠아단인 두 사람도\n"
	.string "분명 나쁜 뜻은 아니었을 거야\p"
	.string "잠깐 그들의 이야기를\n"
	.string "들어보는 건 어떨까...$"
	// ミクリ『§あ§お……ｐ
	// マグマだんと アクアだんの ふたりもｎ
	// きっと わるぎは なかったの だろうねｐ
	// ちょっと かれらの はなしをｎ
	// きいてやって みては どうかな……

SootopolisCity_Text_ThankYouForHelpAcceptThis: @ 81E7ACF
	.string "윤진: {PLAYER}...\n"
	.string "역시 내 눈이 맞았어\p"
	.string "네가 힘을 빌려준 덕분에\n"
	.string "루네시티가...\l"
	.string "아니 호연지방이 구원받았어\p"
	.string "마을의 모두를 대표해서\n"
	.string "감사를 표하도록 할게\l"
	.string "...정말 고마워\p"
	.string "이건 내가 주는 선물이야\n"
	.string "부디 받아줘!$"
	// ミクリ『§あ§お……ｎ
	// やはり わたしの めは ただしかったｐ
	// きみが ちからを かしてくれた おかげでｎ
	// ルネシティは……ｌ
	// いや ホウエンは すくわれたんだよｐ
	// まちの みんなを だいひょうしてｎ
	// おれいを いわせて もらうよｌ
	// ……ありがとうｐ
	// これは わたしからの プレゼントだｎ
	// うけとって くれたまえ!

SootopolisCity_Text_ExplainWaterfallGoToGym: @ 81E7B86
	.string "그 비전머신은 폭포오르기!\p"
	.string "레인배지를 갖고 있으면\n"
	.string "그 기술을 배운 포켓몬이\l"
	.string "폭포를 오를 수 있지!\p"
	.string "그리고... 레인배지는\n"
	.string "어디서 받을 수 있냐면...\p"
	.string "이미 알고 있을 것 같네\n"
	.string "그래! 루네시티의\l"
	.string "체육관 관장에게 이기면 돼\p"
	.string "자 준비가 되었다면\n"
	.string "안으로 들어가 봐!$"
	// その ひでんマシンは たきのぼり!ｐ
	// レインバッジを もっていればｎ
	// そのわざを おぼえさせた ポケモンがｌ
	// たきを のぼれるように なるのさ!ｐ
	// そして…… レインバッジはｎ
	// どこで もらえるのか というと……ｐ
	// もう おわかりだねｎ
	// そう! ルネの ジムリ-ダ-に かつことｐ
	// さあ じゅんびが できたらｎ
	// なかに はいって くれたまえ!

SootopolisCity_Text_DazzledByMentor: @ 81E7CBC
	.string "윤진: 내 스승의\n"
	.string "화려하고 우아한 배틀에\l"
	.string "넌 분명 놀라게 될 거야!$"
	// ミクリ『わたしの ししょうのｎ
	// かれい かつ ゆうがな たたかいぶりにｌ
	// きっと きみは おどろく だろうよ!
