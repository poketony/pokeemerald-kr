.set LOCALID_VICTOR, 1
.set LOCALID_VICTORIA, 2
.set LOCALID_VIVI, 3
.set LOCALID_VICKY, 4
.set LOCALID_PLAYER_FALLING, 45
.set LOCALID_ROCK_SMASH_MAN, 46

Route111_MapScripts:: @ 81F0CA7
	map_script MAP_SCRIPT_ON_LOAD, Route111_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, Route111_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route111_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route111_OnFrame
	.byte 0

Route111_OnLoad: @ 81F0CBC
	call_if_unset FLAG_REGI_DOORS_OPENED, Route111_EventScript_CloseDesertRuins
	compare VAR_MIRAGE_TOWER_STATE, 1
	call_if_eq Route111_EventScript_ShowTemporaryMirageTower
	end

Route111_EventScript_CloseDesertRuins:: @ 81F0CD1
	setmetatile 29, 86, METATILE_General_RockWall_RockBase, 1
	setmetatile 29, 87, METATILE_General_RockWall_SandBase, 1
	return

@ Show Mirage Tower just prior to disintegration. Mirage Tower is otherwise handled by the map layout
Route111_EventScript_ShowTemporaryMirageTower:: @ 81F0CE4
	setmetatile 18, 53, METATILE_Mauville_MirageTower_Tile0, 0
	setmetatile 19, 53, METATILE_Mauville_MirageTower_Tile1, 0
	setmetatile 20, 53, METATILE_Mauville_MirageTower_Tile2, 0
	setmetatile 18, 54, METATILE_Mauville_MirageTower_Tile3, 0
	setmetatile 19, 54, METATILE_Mauville_MirageTower_Tile4, 0
	setmetatile 20, 54, METATILE_Mauville_MirageTower_Tile5, 0
	setmetatile 18, 55, METATILE_Mauville_MirageTower_Tile6, 0
	setmetatile 19, 55, METATILE_Mauville_MirageTower_Tile7, 0
	setmetatile 20, 55, METATILE_Mauville_MirageTower_Tile8, 0
	setmetatile 18, 56, METATILE_Mauville_MirageTower_Tile9, 0
	setmetatile 19, 56, METATILE_Mauville_MirageTower_TileA, 0
	setmetatile 20, 56, METATILE_Mauville_MirageTower_TileB, 0
	setmetatile 18, 57, METATILE_Mauville_MirageTower_TileC, 0
	setmetatile 19, 57, METATILE_Mauville_MirageTower_TileD, 0
	setmetatile 20, 57, METATILE_Mauville_MirageTower_TileE, 0
	setmetatile 18, 58, METATILE_Mauville_MirageTower_TileF, 0
	setmetatile 19, 58, METATILE_Mauville_MirageTower_Tile10, 0
	setmetatile 20, 58, METATILE_Mauville_MirageTower_Tile11, 0
	return

Route111_OnTransition: @ 81F0D87
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 0
	special SetMirageTowerVisibility
	call_if_unset FLAG_MIRAGE_TOWER_VISIBLE, Route111_EventScript_SetLayoutNoMirageTower
	compare VAR_MIRAGE_TOWER_STATE, 1
	call_if_eq Route111_EventScript_SetFallingPlayerGfx
	compare VAR_MIRAGE_TOWER_STATE, 2
	call_if_eq Route111_EventScript_SetMirageTowerGone
	call Route111_EventScript_CheckSetSandstorm
	call GabbyAndTy_EventScript_UpdateLocation
	goto_if_not_defeated TRAINER_VICKY, Route111_EventScript_SetWinstratesNotDefeated
	end

Route111_EventScript_SetFallingPlayerGfx:: @ 81F0DC2
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq Route111_EventScript_SetFallingPlayerGfxMale
	compare VAR_RESULT, FEMALE
	goto_if_eq Route111_EventScript_SetFallingPlayerGfxFemale
	return

Route111_EventScript_SetFallingPlayerGfxMale:: @ 81F0DDA
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	return

Route111_EventScript_SetFallingPlayerGfxFemale:: @ 81F0DE0
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	return

Route111_EventScript_CheckSetSandstorm:: @ 81F0DE6
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	compare VAR_TEMP_1, 34
	goto_if_lt Route111_EventScript_EndCheckSetSandstorm
	compare VAR_TEMP_1, 107
	goto_if_gt Route111_EventScript_EndCheckSetSandstorm
	compare VAR_TEMP_1, 72
	goto_if_gt Route111_EventScript_SetSandstorm
	compare VAR_TEMP_0, 2000
	goto_if_gt Route111_EventScript_EndCheckSetSandstorm
	compare VAR_TEMP_0, 8
	goto_if_lt Route111_EventScript_EndCheckSetSandstorm
Route111_EventScript_SetSandstorm:: @ 81F0E22
	setweather WEATHER_SANDSTORM
Route111_EventScript_EndCheckSetSandstorm:: @ 81F0E25
	return

Route111_EventScript_SetWinstratesNotDefeated:: @ 81F0E26
	clearflag FLAG_HIDE_ROUTE_111_VICTOR_WINSTRATE
	setflag FLAG_HIDE_ROUTE_111_VICTORIA_WINSTRATE
	setflag FLAG_HIDE_ROUTE_111_VIVI_WINSTRATE
	setflag FLAG_HIDE_ROUTE_111_VICKY_WINSTRATE
	cleartrainerflag TRAINER_VICTOR
	cleartrainerflag TRAINER_VICTORIA
	cleartrainerflag TRAINER_VIVI
	end

Route111_EventScript_SetLayoutNoMirageTower:: @ 81F0E3C
	setmaplayoutindex LAYOUT_ROUTE111_NO_MIRAGE_TOWER
	return

Route111_EventScript_SetMirageTowerGone:: @ 81F0E40
	setvar VAR_MIRAGE_TOWER_STATE, 3
	return

Route111_OnWarp: @ 81F0E46
	map_script_2 VAR_MIRAGE_TOWER_STATE, 1, Route111_EventScript_HidePlayerForMirageTower
	.2byte 0

Route111_EventScript_HidePlayerForMirageTower:: @ 81F0E50
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_LITTLEROOT_TOWN
	end

Route111_OnFrame: @ 81F0E56
	map_script_2 VAR_MIRAGE_TOWER_STATE, 1, Route111_EventScript_MirageTowerDisappear
	.2byte 0

Route111_EventScript_MirageTowerDisappear:: @ 81F0E60
	lockall
	special StartMirageTowerShake
	waitstate
	delay 24
	playse SE_FALL
	addobject LOCALID_PLAYER_FALLING
	special StartPlayerDescendMirageTower
	waitstate
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_LITTLEROOT_TOWN
	removeobject LOCALID_PLAYER_FALLING
	delay 16
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 16
	special StartMirageTowerDisintegration
	waitstate
	special StartMirageTowerFossilFallAndSink
	waitstate
	setvar VAR_MIRAGE_TOWER_STATE, 2
	clearflag FLAG_HIDE_DESERT_UNDERPASS_FOSSIL
	goto_if_set FLAG_CHOSE_CLAW_FOSSIL, Route111_EventScript_RootFossilDisappeared
	msgbox Route111_Text_ClawFossilDisappeared, MSGBOX_DEFAULT
	releaseall
	end

Route111_EventScript_RootFossilDisappeared:: @ 81F0EA7
	msgbox Route111_Text_RootFossilDisappeared, MSGBOX_DEFAULT
	releaseall
	end

@ Unused
Route111_Movement_PlayerFall:: @ 81F0EB1
	store_lock_anim
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

Route111_EventScript_Girl:: @ 81F0EB9
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_ROUTE_111_RECEIVED_BERRY, Route111_EventScript_ReceivedBerry
	msgbox Route111_Text_WateredPlantsEveryDayTakeBerry, MSGBOX_DEFAULT
	giveitem ITEM_RAZZ_BERRY
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_ROUTE_111_RECEIVED_BERRY
	special GetPlayerBigGuyGirlString
	msgbox Route111_Text_GoingToTryToMakeDifferentColorBerries, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_ReceivedBerry:: @ 81F0EF4
	msgbox Route111_Text_WhatColorBerriesToLookForToday, MSGBOX_DEFAULT
	release
	end

@ Unused
Route111_EventScript_ViciousSandstormTriggerUp:: @ 81F0EFE
	lockall
	setvar VAR_0x8004, 0
	goto Route111_EventScript_ViciousSandstormTrigger
	end

Route111_EventScript_ViciousSandstormTriggerDown:: @ 81F0F0A
	lockall
	setvar VAR_0x8004, 1
	goto Route111_EventScript_ViciousSandstormTrigger
	end

Route111_EventScript_ViciousSandstormTriggerLeft:: @ 81F0F16
	lockall
	setvar VAR_0x8004, 2
	goto Route111_EventScript_ViciousSandstormTrigger
	end

@ Unused
Route111_EventScript_ViciousSandstormTriggerRight:: @ 81F0F22
	lockall
	setvar VAR_0x8004, 3
	goto Route111_EventScript_ViciousSandstormTrigger
	end

Route111_EventScript_ViciousSandstormTrigger:: @ 81F0F2E
	checkitem ITEM_GO_GOGGLES, 1
	compare VAR_RESULT, FALSE
	goto_if_eq Route111_EventScript_PreventRouteAccess
	setvar VAR_TEMP_3, 1
	releaseall
	end

Route111_EventScript_PreventRouteAccess:: @ 81F0F45
	msgbox gText_SandstormIsVicious, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8004, 0
	call_if_eq Route111_EventScript_PushUpFromRoute
	compare VAR_0x8004, 1
	call_if_eq Route111_EventScript_PushDownFromRoute
	compare VAR_0x8004, 2
	call_if_eq Route111_EventScript_PushLeftFromRoute
	compare VAR_0x8004, 3
	call_if_eq Route111_EventScript_PushRightFromRoute
	releaseall
	end

Route111_EventScript_PushUpFromRoute:: @ 81F0F7C
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_PushUpFromRoute
	waitmovement 0
	return

Route111_EventScript_PushDownFromRoute:: @ 81F0F87
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_PushDownFromRoute
	waitmovement 0
	return

Route111_EventScript_PushLeftFromRoute:: @ 81F0F92
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_PushLeftFromRoute
	waitmovement 0
	return

Route111_EventScript_PushRightFromRoute:: @ 81F0F9D
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_PushRightFromRoute
	waitmovement 0
	return

Route111_Movement_PushUpFromRoute: @ 81F0FA8
	walk_up
	step_end

Route111_Movement_PushDownFromRoute: @ 81F0FAA
	walk_down
	step_end

Route111_Movement_PushLeftFromRoute: @ 81F0FAC
	walk_left
	step_end

Route111_Movement_PushRightFromRoute: @ 81F0FAE
	walk_right
	step_end

Route111_EventScript_SunTrigger:: @ 81F0FB0
	setweather WEATHER_SUNNY
	fadenewbgm MUS_ROUTE110
	doweather
	setvar VAR_TEMP_3, 0
	end

Route111_EventScript_SandstormTrigger:: @ 81F0FBD
	setweather WEATHER_SANDSTORM
	fadenewbgm MUS_ROUTE111
	doweather
	end

Route111_EventScript_Victor:: @ 81F0FC5
	lock
	faceplayer
	setflag FLAG_LANDMARK_WINSTRATE_FAMILY
	msgbox Route111_Text_BattleOurFamily, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route111_EventScript_BattleWinstrates
	msgbox Route111_Text_IsThatSo, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_BattleWinstrates:: @ 81F0FE7
	msgbox Route111_Text_VictorIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_VICTOR, Route111_Text_VictorDefeat
	applymovement LOCALID_VICTOR, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	msgbox Route111_Text_VictorPostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_VICTOR, Route111_Movement_WinstrateEnterHouse
	waitmovement 0
	removeobject LOCALID_VICTOR
	call Route111_EventScript_CloseWinstrateDoor
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_WaitForNextWinstrate
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	addobject LOCALID_VICTORIA
	applymovement LOCALID_VICTORIA, Route111_Movement_WinstrateExitHouse
	waitmovement 0
	call Route111_EventScript_CloseWinstrateDoor
	msgbox Route111_Text_VictoriaIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_VICTORIA, Route111_Text_VictoriaDefeat
	applymovement LOCALID_VICTORIA, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	msgbox Route111_Text_VictoriaPostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_VICTORIA, Route111_Movement_WinstrateEnterHouse
	waitmovement 0
	removeobject LOCALID_VICTORIA
	call Route111_EventScript_CloseWinstrateDoor
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_WaitForNextWinstrate
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	addobject LOCALID_VIVI
	applymovement LOCALID_VIVI, Route111_Movement_WinstrateExitHouse
	waitmovement 0
	call Route111_EventScript_CloseWinstrateDoor
	msgbox Route111_Text_ViviIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_VIVI, Route111_Text_ViviDefeat
	applymovement LOCALID_VIVI, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	msgbox Route111_Text_ViviPostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_VIVI, Route111_Movement_WinstrateEnterHouse
	waitmovement 0
	removeobject LOCALID_VIVI
	call Route111_EventScript_CloseWinstrateDoor
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_WaitForNextWinstrate
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	addobject LOCALID_VICKY
	applymovement LOCALID_VICKY, Route111_Movement_WinstrateExitHouse
	waitmovement 0
	call Route111_EventScript_CloseWinstrateDoor
	msgbox Route111_Text_VickyIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_VICKY, Route111_Text_VickyDefeat
	msgbox Route111_Text_VickyPostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_VICKY, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	applymovement LOCALID_VICKY, Route111_Movement_WinstrateEnterHouse
	waitmovement 0
	removeobject LOCALID_VICKY
	call Route111_EventScript_CloseWinstrateDoor
	release
	end

Route111_EventScript_OpenWinstrateDoor:: @ 81F113C
	opendoor 13, 113
	waitdooranim
	return

Route111_EventScript_CloseWinstrateDoor:: @ 81F1143
	closedoor 13, 113
	waitdooranim
	return

Route111_Movement_WinstrateEnterHouse: @ 81F114A
	walk_in_place_fastest_up
	walk_up
	step_end

Route111_Movement_WinstrateExitHouse: @ 81F114D
	walk_down
	step_end

Route111_Movement_WaitForNextWinstrate: @ 81F114F
	delay_16
	delay_16
	delay_16
	step_end

Route111_EventScript_RouteSignMauville:: @ 81F1153
	msgbox Route111_Text_RouteSignMauville, MSGBOX_SIGN
	end

Route111_EventScript_WinstrateHouseSign:: @ 81F115C
	msgbox Route111_Text_WinstrateHouseSign, MSGBOX_SIGN
	end

Route111_EventScript_RouteSign112:: @ 81F1165
	msgbox Route111_Text_RouteSign112, MSGBOX_SIGN
	end

Route111_EventScript_RouteSign113:: @ 81F116E
	msgbox Route111_Text_RouteSign113, MSGBOX_SIGN
	end

Route111_EventScript_OldLadysRestStopSign:: @ 81F1177
	msgbox Route111_Text_OldLadysRestStopSign, MSGBOX_SIGN
	end

Route111_EventScript_TrainerTipsSpAtkSpDef:: @ 81F1180
	msgbox Route111_Text_TrainerTipsSpAtkSpDef, MSGBOX_SIGN
	end

Route111_EventScript_Man1:: @ 81F1189
	msgbox Route111_Text_ToughToKeepWinningUpTheRanks, MSGBOX_NPC
	end

Route111_EventScript_Man2:: @ 81F1192
	msgbox Route111_Text_WinstrateFamilyDestroyedMe, MSGBOX_NPC
	end

Route111_EventScript_Hiker:: @ 81F119B
	lock
	faceplayer
	compare VAR_MIRAGE_TOWER_STATE, 3
	goto_if_eq Route111_EventScript_HikerMirageTowerGone
	compare VAR_MIRAGE_TOWER_STATE, 2
	goto_if_eq Route111_EventScript_HikerMirageTowerDisintegrated
	goto_if_set FLAG_MIRAGE_TOWER_VISIBLE, Route111_EventScript_HikerMirageTowerVisible
	msgbox Route111_Text_ShouldBeMirageTowerAroundHere, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_HikerMirageTowerGone:: @ 81F11C6
	msgbox Route111_Text_MirageTowerHasntBeenSeenSince, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_HikerMirageTowerDisintegrated:: @ 81F11D0
	msgbox Route111_Text_ThatWasShockingSandRainedDown, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_HikerMirageTowerVisible:: @ 81F11DA
	msgbox Route111_Text_MirageTowerClearlyVisible, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_RockSmashTipFatMan:: @ 81F11E4
	lockall
	applymovement LOCALID_ROCK_SMASH_MAN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Route111_Text_MauvilleUncleToldMeToTakeRockSmash, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROCK_SMASH_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

Route111_EventScript_Drew:: @ 81F1204
	trainerbattle_single TRAINER_DREW, Route111_Text_DrewIntro, Route111_Text_DrewDefeat
	msgbox Route111_Text_DrewPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Heidi:: @ 81F121B
	trainerbattle_single TRAINER_HEIDI, Route111_Text_HeidiIntro, Route111_Text_HeidiDefeat
	msgbox Route111_Text_HeidiPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Beau:: @ 81F1232
	trainerbattle_single TRAINER_BEAU, Route111_Text_BeauIntro, Route111_Text_BeauDefeat
	msgbox Route111_Text_BeauPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Becky:: @ 81F1249
	trainerbattle_single TRAINER_BECKY, Route111_Text_BeckyIntro, Route111_Text_BeckyDefeat
	msgbox Route111_Text_BeckyPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Dusty:: @ 81F1260
	trainerbattle_single TRAINER_DUSTY_1, Route111_Text_DustyIntro, Route111_Text_DustyDefeat, Route111_EventScript_RegisterDusty
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route111_EventScript_RematchDusty
	msgbox Route111_Text_DustyPostBattle, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_RegisterDusty:: @ 81F128C
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route111_Text_DustyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DUSTY_1
	release
	end

Route111_EventScript_RematchDusty:: @ 81F12AB
	trainerbattle_rematch TRAINER_DUSTY_1, Route111_Text_DustyRematchIntro, Route111_Text_DustyRematchDefeat
	msgbox Route111_Text_DustyPostRematch, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Travis:: @ 81F12C2
	trainerbattle_single TRAINER_TRAVIS, Route111_Text_TravisIntro, Route111_Text_TravisDefeat
	msgbox Route111_Text_TravisPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Irene:: @ 81F12D9
	trainerbattle_single TRAINER_IRENE, Route111_Text_IreneIntro, Route111_Text_IreneDefeat
	msgbox Route111_Text_IrenePostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Daisuke:: @ 81F12F0
	trainerbattle_single TRAINER_DAISUKE, Route111_Text_DaisukeIntro, Route111_Text_DaisukeDefeat
	msgbox Route111_Text_DaisukePostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Wilton:: @ 81F1307
	trainerbattle_single TRAINER_WILTON_1, Route111_Text_WiltonIntro, Route111_Text_WiltonDefeat, Route111_EventScript_RegisterWilton
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route111_EventScript_RematchWilton
	msgbox Route111_Text_WiltonPostBattle, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_RegisterWilton:: @ 81F1333
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route111_Text_WiltonRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_WILTON_1
	release
	end

Route111_EventScript_RematchWilton:: @ 81F1352
	trainerbattle_rematch TRAINER_WILTON_1, Route111_Text_WiltonRematchIntro, Route111_Text_WiltonRematchDefeat
	msgbox Route111_Text_WiltonPostRematch, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Brooke:: @ 81F1369
	trainerbattle_single TRAINER_BROOKE_1, Route111_Text_BrookeIntro, Route111_Text_BrookeDefeat, Route111_EventScript_RegisterBrooke
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route111_EventScript_RematchBrooke
	msgbox Route111_Text_BrookePostBattle, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_RegisterBrooke:: @ 81F1395
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route111_Text_BrookeRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BROOKE_1
	release
	end

Route111_EventScript_RematchBrooke:: @ 81F13B4
	trainerbattle_rematch TRAINER_BROOKE_1, Route111_Text_BrookeRematchIntro, Route111_Text_BrookeRematchDefeat
	msgbox Route111_Text_BrookePostRematch, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Hayden:: @ 81F13CB
	trainerbattle_single TRAINER_HAYDEN, Route111_Text_HaydenIntro, Route111_Text_HaydenDefeat
	msgbox Route111_Text_HaydenPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Bianca:: @ 81F13E2
	trainerbattle_single TRAINER_BIANCA, Route111_Text_BiancaIntro, Route111_Text_BiancaDefeat
	msgbox Route111_Text_BiancaPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Tyron:: @ 81F13F9
	trainerbattle_single TRAINER_TYRON, Route111_Text_TyronIntro, Route111_Text_TyronDefeat
	msgbox Route111_Text_TyronPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Celina:: @ 81F1410
	trainerbattle_single TRAINER_CELINA, Route111_Text_CelinaIntro, Route111_Text_CelinaDefeat
	msgbox Route111_Text_CelinaPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Celia:: @ 81F1427
	trainerbattle_single TRAINER_CELIA, Route111_Text_CeliaIntro, Route111_Text_CeliaDefeat
	msgbox Route111_Text_CeliaPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Bryan:: @ 81F143E
	trainerbattle_single TRAINER_BRYAN, Route111_Text_BryanIntro, Route111_Text_BryanDefeat
	msgbox Route111_Text_BryanPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Branden:: @ 81F1455
	trainerbattle_single TRAINER_BRANDEN, Route111_Text_BrandenIntro, Route111_Text_BrandenDefeat
	msgbox Route111_Text_BrandenPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_TrainerHillSign:: @ 81F146C
	msgbox Route111_Text_TrainerHillSign, MSGBOX_SIGN
	end

Route111_Text_BattleOurFamily: @ 81F1475
	.string "이보게! 여행 중인 건 알고 있지만,\p"
	.string "잠깐 어떤가? 지금 여기서\n"
	.string "우리 가족 4명과\l"
	.string "포켓몬 승부를 해보지 않겠나?$"

Route111_Text_IsThatSo: @ 81F14F5
	.string "그렇군!\n"
	.string "마음이 바뀌면 다시 오게!$"

Route111_Text_VictorIntro: @ 81F1523
	.string "멋진 배짱이군! 마음에 들었다!$"

Route111_Text_VictorDefeat: @ 81F1542
	.string "어허!\n"
	.string "생각했던 것보다 강하군!$"

Route111_Text_VictorPostBattle: @ 81F156F
	.string "이봐-!\n"
	.string "상당히 강한 트레이너가 있다-!$"

Route111_Text_VictoriaIntro: @ 81F159D
	.string "어머머! 생각보다 어리군요?!\p"
	.string "우리 남편을 이기다니\n"
	.string "정말 굉장한 실력의\l"
	.string "트레이너인가 보죠?\p"
	.string "자 그럼 이번엔 저와 승부해요!$"

Route111_Text_VictoriaDefeat: @ 81F1616
	.string "에구머니나!\n"
	.string "어쩜 그렇게 강하신가요?!$"

Route111_Text_VictoriaPostBattle: @ 81F1645
	.string "강해-!\n"
	.string "이 사람 엄청나게 강해요-!$"

Route111_Text_ViviIntro: @ 81F167E
	.string "엄마보다 강하다니 굉장하다!\p"
	.string "하지만 나도 꽤 강하다고!\n"
	.string "진짜라니까?!$"

Route111_Text_ViviDefeat: @ 81F16C6
	.string "응? 서, 설마 져버린 건가...?$"

Route111_Text_ViviPostBattle: @ 81F16DC
	.string "너무 분해...\p"
	.string "...훌쩍!\n"
	.string "할머니이-이!!$"

Route111_Text_VickyIntro: @ 81F16FB
	.string "요 녀석-!\n"
	.string "우리 귀여운 손녀에게\l"
	.string "무슨 짓을 한 게냐!\p"
	.string "이렇게 된 이상 내가 직접\n"
	.string "네 포켓몬을 혼내줄 테니 각오해라잇!$"

Route111_Text_VickyDefeat: @ 81F1756
	.string "아이고! 강하구먼...\n"
	.string "우리 손녀가 한 말이 사실이었어$"

Route111_Text_VickyPostBattle: @ 81F1788
	.string "얘야... 갈 길이 바쁘지 않으면\n"
	.string "종종 우리 집에 들렀다 가거라...$"

Route111_Text_ToughToKeepWinningUpTheRanks: @ 81F17BA
	.string "좀 더 포켓몬을 단련시키지 않으면\n"
	.string "앞으로 이기기 어려울 것 같아\p"
	.string "포켓몬리그에 있는 사천왕은\n"
	.string "지금까지 승부했던\l"
	.string "체육관 관장들보다\l"
	.string "훨씬 강하다고 하니까 말이야$"

Route111_Text_WinstrateFamilyDestroyedMe: @ 81F186E
	.string "연승가족에게 도전했는데\n"
	.string "4명과 연속으로\l"
	.string "포켓몬 승부를 하는 건\l"
	.string "정말 힘들더라... 완패하고 말았어$"

Route111_Text_RouteSignMauville: @ 81F18CE
	.string "여기는 111번도로\n"
	.string "{DOWN_ARROW} 보라시티$"

Route111_Text_WinstrateHouseSign: @ 81F18E8
	.string "우리 가족은 한마음\n"
	.string "“연승가족의 집”$"

Route111_Text_RouteSign112: @ 81F1921
	.string "여기는 111번도로\n"
	.string "{LEFT_ARROW} 112번도로$"

Route111_Text_RouteSign113: @ 81F1937
	.string "여기는 111번도로\n"
	.string "{LEFT_ARROW} 113번도로$"

Route111_Text_OldLadysRestStopSign: @ 81F194D
	.string "“건강할머니의 집”\n"
	.string "지쳤다고 느낀다면 들렀다 가렴!$"

Route111_Text_TrainerTipsSpAtkSpDef: @ 81F1987
	.string "정보 나눔 게시판!!\p"
	.string "포켓몬의 능력을 나타내는 말 중에\n"
	.string "특수공격이란\l"
	.string "특수공격력을\p"
	.string "특수방어란\n"
	.string "특수방어력을 뜻하는 말입니다!$"

Route111_Text_ShouldBeMirageTowerAroundHere: @ 81F1A22
	.string "이 주변에 모래로 된\n"
	.string "탑이 있을 텐데\p"
	.string "어떻게 된 건지\n"
	.string "보였다 말았다 해\p"
	.string "그래서 나는 그걸\n"
	.string "환영탑이라고 부르고 있지...$"
	// この あたりに すなで できたｎ
	// とうが たっている はず なんだがｐ
	// どうしたわけかｎ
	// みえるときと みえないときが あるのだｐ
	// だから わたしは それをｎ
	// げんえいのとう と よんでいる……

Route111_Text_MirageTowerClearlyVisible: @ 81F1AC7
	.string "보인다! 모래로 된 탑이!\n"
	.string "환영이라고 불렸던 모래탑이\l"
	.string "확실하게 보인다고!\p"
	.string "하지만 그 모습은 덧없이\n"
	.string "지금도 무너져 내리는 듯하군...\p"
	.string "음- 들어가고 싶지만\n"
	.string "무서워서 용기가 생기지 않아!$"
	// みえるぞ! すなのとう が!ｎ
	// げんえい と よばれた すなのとうがｎ
	// はっきりと みえる!ｐ
	// しかし そのすがたは はかなくてｎ
	// いまにも くずれて しまいそうだ……ｐ
	// う-ん はいって みたいがｎ
	// こわくて ゆうきが でん!

Route111_Text_ThatWasShockingSandRainedDown: @ 81F1B92
	.string "하- 깜짝 놀랐어...\p"
	.string "갑자기 하늘에서 모래가\n"
	.string "뿔뿔이 내릴 줄이야\p"
	.string "그래서 안은 어땠어?\n"
	.string "역시 모래 귀신이 나온 거야?$"
	// は- びっくりした……ｐ
	// いきなり すなが そらからｎ
	// バラバラと ふって きたんじゃｐ
	// で なかは どうじゃった?ｎ
	// やはり すなの オバケ とか でたか?

Route111_Text_MirageTowerHasntBeenSeenSince: @ 81F1C12
	.string "그때 이후로\n"
	.string "모래탑을 볼 수 없게 됐어\p"
	.string "역시 환영이었던 건가$"
	// あれからｎ
	// すなのとう は みえなく なったｐ
	// やはり げんえいのとう だったのか……

Route111_Text_ClawFossilDisappeared: @ 81F1C74
	.string "발톱화석은\n"
	.string "모래 속으로 파묻혔다...$"
	// ツメのかせきはｎ
	// すなに もぐって しまった……

Route111_Text_RootFossilDisappeared: @ 81F1C9F
	.string "뿌리화석은\n"
	.string "모래 속으로 파묻혔다...$"
	// ねっこのかせきはｎ
	// すなに もぐって しまった……

Route111_Text_MauvilleUncleToldMeToTakeRockSmash: @ 81F1CCA
	.string "아 이런!\p"
	.string "111번도로에 가면\n"
	.string "바위깨기를 가져가라고\l"
	.string "보라시티의 삼촌이 말했었는데!\p"
	.string "삼촌? 사이클숍의\n"
	.string "건너편의 집에 살고 있어$"
	// しまった!ｐ
	// 111ばんどうろに いくならｎ
	// いわくだきを もっていけ ってｌ
	// キンセツの おじさんに いわれてたんだ!ｐ
	// おじさん? サイクルショップのｎ
	// むかいがわの いえに すんでるよ

Route111_Text_TrainerHillSign: @ 81F1D61
	.string "{RIGHT_ARROW} 트레이너힐 입구\n"
	.string "뛰어올라라! 뜨거운 트레이너들이여!$"
	// ©しう トレ-ナ-ヒル いりぐちｎ
	// かけあがれ! あつき トレ-ナ-たち!

