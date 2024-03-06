@ NOTE: Route 104's sail to Dewford script references local IDs from Dewford's map. 
@  These are labeled in DewfordTown/scripts.inc
.set LOCALID_RIVAL, 34

Route104_MapScripts:: @ 81ECC32
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route104_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_OnTransition
	.byte 0

Route104_OnFrame: @ 81ECC3D
	map_script_2 VAR_BOARD_BRINEY_BOAT_STATE, 1, Route104_EventScript_StartSailToDewford
	.2byte 0

Route104_EventScript_StartSailToDewford:: @ 81ECC47
	lockall
	goto Route104_EventScript_SailToDewford
	end

Route104_OnTransition: @ 81ECC4E
	call Common_EventScript_SetupRivalGfxId
	call Route104_EventScript_TrySetRivalPos
	call Route104_EventScript_ShowOrHideWhiteHerbFlorist
	end

Route104_EventScript_ShowOrHideWhiteHerbFlorist:: @ 81ECC5E
	goto_if_unset FLAG_MET_PRETTY_PETAL_SHOP_OWNER, Route104_EventScript_HideWhiteHerbFlorist
	goto_if_unset FLAG_BADGE03_GET, Route104_EventScript_HideWhiteHerbFlorist
	clearflag FLAG_HIDE_ROUTE_104_WHITE_HERB_FLORIST
	return

Route104_EventScript_HideWhiteHerbFlorist:: @ 81ECC74
	setflag FLAG_HIDE_ROUTE_104_WHITE_HERB_FLORIST
	return

Route104_EventScript_TrySetRivalPos:: @ 81ECC78
	compare VAR_BOARD_BRINEY_BOAT_STATE, 1
	goto_if_ge Route104_EventScript_DontSetRivalPos
	goto_if_set FLAG_MET_RIVAL_RUSTBORO, Route104_EventScript_DontSetRivalPos
	goto_if_unset FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_DontSetRivalPos
	setobjectxyperm LOCALID_RIVAL, 17, 52
	return

Route104_EventScript_DontSetRivalPos:: @ 81ECC9D
	return

Route104_EventScript_Rival:: @ 81ECC9E
	lockall
	setvar VAR_0x8008, 1
	applymovement LOCALID_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	goto Route104_EventScript_RivalEncounter

Route104_EventScript_RivalTrigger:: @ 81ECCB3
	lockall
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setvar VAR_RUSTBORO_CITY_STATE, 8
	setvar VAR_ROUTE104_STATE, 2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 10
	addobject LOCALID_RIVAL
	clearflag FLAG_HIDE_ROUTE_104_RIVAL
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerBackUp
	waitmovement 0
	applymovement LOCALID_RIVAL, Route104_Movement_RivalExitBrineysCottage
	waitmovement 0
	delay 20
	setvar VAR_0x8008, 0
	call RustboroCity_EventScript_PlayRivalMusic
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	goto Route104_EventScript_RivalEncounter

@ Unused, shares script with Rustboro encounter instead
Route104_EventScript_PlayRivalMusic:: @ 81ECD11
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq Route104_EventScript_PlayMayMusic
	compare VAR_RESULT, FEMALE
	goto_if_eq Route104_EventScript_PlayBrendanMusic
	return

Route104_EventScript_PlayMayMusic:: @ 81ECD29
	playbgm MUS_ENCOUNTER_MAY, 1
	return

Route104_EventScript_PlayBrendanMusic:: @ 81ECD2E
	playbgm MUS_ENCOUNTER_BRENDAN, 1
	return

Route104_EventScript_RivalEncounter:: @ 81ECD33
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq Route104_EventScript_MayEncounter
	compare VAR_RESULT, FEMALE
	goto_if_eq Route104_EventScript_BrendanEncounter
	end

Route104_EventScript_MayEncounter:: @ 81ECD4B
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE_104, Route104_EventScript_MayDefeated
	goto_if_set FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_MayAskToBattle
	setflag FLAG_REGISTER_RIVAL_POKENAV
	msgbox Route104_Text_MayWeShouldRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route104_Text_RegisteredMay, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerFaceRival
	applymovement LOCALID_RIVAL, Route104_Movement_RivalWalkSlowLeft
	msgbox Route104_Text_MayHowsYourPokedex, MSGBOX_DEFAULT
	closemessage
	waitmovement 0
	applymovement LOCALID_RIVAL, Route104_Movement_RivalApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_RIVAL
	msgbox Route104_Text_MayMinesDecentLetsBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route104_EventScript_BattleMay
	msgbox Route104_Text_MayHaventRaisedPokemon, MSGBOX_DEFAULT
	call Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_Movement_RivalWalkSlowLeft: @ 81ECDC8
	walk_slow_left
	step_end

Route104_Movement_RivalApproachPlayer: @ 81ECDCA
	walk_down
	face_right
	step_end

Route104_Movement_PlayerFaceRival: @ 81ECDCD
	delay_4
	walk_in_place_fastest_left
	step_end

Route104_EventScript_MayAskToBattle:: @ 81ECDD0
	msgbox Route104_Text_MayLetsBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route104_EventScript_BattleMay
	msgbox Route104_Text_MayHaventRaisedPokemon, MSGBOX_DEFAULT
	releaseall
	end

Route104_EventScript_BattleMay:: @ 81ECDED
	msgbox Route104_Text_MayIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route104_EventScript_BattleMayTreecko
	case 1, Route104_EventScript_BattleMayTorchic
	case 2, Route104_EventScript_BattleMayMudkip
	end

Route104_EventScript_MayDefeated:: @ 81ECE1C
	msgbox Route104_Text_MayPostBattle, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_EventScript_RestoreMusic:: @ 81ECE31
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

Route104_EventScript_BattleMayTreecko:: @ 81ECE36
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TREECKO, Route104_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_MayDefeated
	end

Route104_EventScript_BattleMayTorchic:: @ 81ECE49
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TORCHIC, Route104_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_MayDefeated
	end

Route104_EventScript_BattleMayMudkip:: @ 81ECE5C
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_MUDKIP, Route104_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_MayDefeated
	end

Route104_EventScript_BrendanEncounter:: @ 81ECE6F
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE_104, Route104_EventScript_BrendanDefeated
	goto_if_set FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_BrendanAskToBattle
	setflag FLAG_REGISTER_RIVAL_POKENAV
	msgbox Route104_Text_BrendanWeShouldRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route104_Text_RegisteredBrendan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerFaceRival
	applymovement LOCALID_RIVAL, Route104_Movement_RivalWalkSlowLeft
	msgbox Route104_Text_BrendanHowsYourPokedex, MSGBOX_DEFAULT
	closemessage
	waitmovement 0
	applymovement LOCALID_RIVAL, Route104_Movement_RivalApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_RIVAL
	msgbox Route104_Text_BrendanDoingGreatLetsBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route104_EventScript_BattleBrendan
	msgbox Route104_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	call Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_EventScript_BrendanAskToBattle:: @ 81ECEEC
	msgbox Route104_Text_BrendanLetsBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route104_EventScript_BattleBrendan
	msgbox Route104_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	releaseall
	end

Route104_EventScript_BattleBrendan:: @ 81ECF09
	msgbox Route104_Text_BrendanIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route104_EventScript_BattleBrendanTreecko
	case 1, Route104_EventScript_BattleBrendanTorchic
	case 2, Route104_EventScript_BattleBrendanMudkip
	end

Route104_EventScript_BrendanDefeated:: @ 81ECF38
	msgbox Route104_Text_BrendanPostBattle, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_EventScript_BattleBrendanTreecko:: @ 81ECF4D
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TREECKO, Route104_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_BrendanDefeated
	end

Route104_EventScript_BattleBrendanTorchic:: @ 81ECF60
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TORCHIC, Route104_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_BrendanDefeated
	end

Route104_EventScript_BattleBrendanMudkip:: @ 81ECF73
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_MUDKIP, Route104_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_BrendanDefeated
	end

Route104_Movement_PlayerBackUp: @ 81ECF86
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

Route104_Movement_RivalExitBrineysCottage: @ 81ECF8A
	walk_down
	step_end

Route104_EventScript_ExpertF:: @ 81ECF8C
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CHESTO_BERRY_ROUTE_104, Route104_EventScript_ReceivedBerry
	msgbox Route104_Text_PlantBerriesInSoilTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_CHESTO_BERRY
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CHESTO_BERRY_ROUTE_104
	msgbox Route104_Text_TrainersOftenMakeMonHoldBerries, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_ReceivedBerry:: @ 81ECFC3
	msgbox Route104_Text_TrainersOftenMakeMonHoldBerries, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_WhiteHerbFlorist:: @ 81ECFCD
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WHITE_HERB, Route104_EventScript_ReceivedWhiteHerb
	msgbox Route104_Text_DontNeedThisTakeIt, MSGBOX_DEFAULT
	giveitem ITEM_WHITE_HERB
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_WHITE_HERB
	release
	end

Route104_EventScript_ReceivedWhiteHerb:: @ 81ECFFC
	msgbox Route104_Text_FlowerShopSellingSaplings, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Girl1:: @ 81ED006
	msgbox Route104_Text_BrineyLivesInSeasideCottage, MSGBOX_NPC
	end

Route104_EventScript_BugCatcher:: @ 81ED00F
	msgbox Route104_Text_WhatsItLikeAtBottomOfSea, MSGBOX_SIGN
	end

Route104_EventScript_BrineysCottageSign:: @ 81ED018
	msgbox Route104_Text_MrBrineysCottage, MSGBOX_SIGN
	end

Route104_EventScript_RouteSignPetalburg:: @ 81ED021
	msgbox Route104_Text_RouteSignPetalburg, MSGBOX_SIGN
	end

Route104_EventScript_RouteSignRustboro:: @ 81ED02A
	msgbox Route104_Text_RouteSignRustboro, MSGBOX_SIGN
	end

Route104_EventScript_FlowerShopSign:: @ 81ED033
	msgbox Route104_Text_PrettyPetalFlowShop, MSGBOX_SIGN
	end

Route104_EventScript_TrainerTipsDoubleBattles:: @ 81ED03C
	msgbox Route104_Text_TrainerTipsDoubleBattles, MSGBOX_SIGN
	end

Route104_EventScript_Boy1:: @ 81ED045
	msgbox Route104_Text_ThrowBallAtWeakenedPokemon, MSGBOX_NPC
	end

Route104_EventScript_Woman:: @ 81ED04E
	msgbox Route104_Text_OnlyThrowBallAtWildPokemon, MSGBOX_NPC
	end

Route104_EventScript_Boy2:: @ 81ED057
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM09, Route104_EventScript_ReceivedBulletSeed
	msgbox Route104_Text_LikeFillingMouthWithSeedsTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM09
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM09
	release
	end

Route104_EventScript_ReceivedBulletSeed:: @ 81ED086
	msgbox Route104_Text_TMsAreOneTimeUse, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Girl2:: @ 81ED090
	msgbox Route104_Text_ImNotATrainer, MSGBOX_NPC
	end

Route104_EventScript_SailToDewford:: @ 81ED099
	setobjectpriority LOCALID_BRINEY_R104, MAP_ROUTE104, 0
	setobjectpriority OBJ_EVENT_ID_PLAYER, MAP_ROUTE104, 0
	applymovement LOCALID_BRINEY_R104, Route104_Movement_BrineyBoardBoat
	waitmovement 0
	removeobject LOCALID_BRINEY_R104
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerBoardBoat
	waitmovement 0
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_ROUTE104
	call Common_EventScript_PlayBrineysBoatMusic
	goto_if_set FLAG_ENABLE_NORMAN_MATCH_CALL, Route104_EventScript_SailToDewfordNoCall
	goto_if_unset FLAG_ENABLE_NORMAN_MATCH_CALL, Route104_EventScript_SailToDewfordDadCalls
	end

Route104_EventScript_SailToDewfordNoCall:: @ 81ED0D9
	applymovement LOCALID_BOAT_R104, Route104_Movement_SailToDewford
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_SailToDewford
	waitmovement 0
	goto Route104_EventScript_ArriveInDewford

Route104_EventScript_SailToDewfordDadCalls:: @ 81ED0EF
	applymovement LOCALID_BOAT_R104, Route104_Movement_SailToDewfordBeforeDadCalls
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_SailToDewfordBeforeDadCalls
	waitmovement 0
	pokenavcall Route104_Text_DadPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route104_Text_RegisteredDadInPokenav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_NORMAN_MATCH_CALL
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_SailToDewfordAfterDadCalls
	applymovement LOCALID_BOAT_R104, Route104_Movement_SailToDewfordAfterDadCalls, MAP_ROUTE104
	waitmovement LOCALID_BOAT_R104, MAP_ROUTE104
	waitmovement 0
	goto Route104_EventScript_ArriveInDewford

Route104_EventScript_ArriveInDewford:: @ 81ED139
	delay 50
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerExitBoat
	waitmovement 0
	call Common_EventScript_StopBrineysBoatMusic
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerMoveForBriney
	waitmovement 0
	setobjectxyperm LOCALID_BRINEY_DEWFORD, 12, 8
	addobject LOCALID_BRINEY_DEWFORD
	setobjectpriority LOCALID_BRINEY_DEWFORD, MAP_DEWFORD_TOWN, 0
	clearflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	applymovement LOCALID_BRINEY_DEWFORD, Route104_Movement_BrineyExitBoat
	waitmovement 0
	addobject LOCALID_BOAT_DEWFORD
	clearflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	call Common_EventScript_StopBrineysBoatMusic
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	hideobjectat LOCALID_BOAT_R104, MAP_ROUTE104
	copyvar VAR_BRINEY_LOCATION, VAR_0x8008
	resetobjectpriority OBJ_EVENT_ID_PLAYER, MAP_ROUTE104
	resetobjectpriority LOCALID_BRINEY_DEWFORD, MAP_DEWFORD_TOWN
	copyobjectxytoperm LOCALID_BRINEY_DEWFORD
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 0
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, Route104_EventScript_DeliverLetterReminder
	goto_if_set FLAG_DELIVERED_STEVEN_LETTER, Route104_EventScript_LandedInDewford
	end

Route104_EventScript_DeliverLetterReminder:: @ 81ED1B4
	msgbox Route104_Text_LandedInDewfordDeliverLetter, MSGBOX_DEFAULT
	releaseall
	end

Route104_EventScript_LandedInDewford:: @ 81ED1BE
	msgbox DewfordTown_Text_BrineyLandedInDewford, MSGBOX_DEFAULT
	releaseall
	end

Route104_Movement_SailToDewfordBeforeDadCalls: @ 81ED1C8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	step_end

Route104_Movement_SailToDewfordAfterDadCalls: @ 81ED22A
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_down
	walk_down
	step_end

Route104_Movement_SailToDewford: @ 81ED28C
	walk_down
	walk_down
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_down
	walk_down
	step_end

Route104_Movement_PlayerBoardBoat: @ 81ED34F
	walk_left
	walk_down
	walk_down
	step_end

Route104_Movement_PlayerExitBoat: @ 81ED353
	walk_down
	step_end

Route104_Movement_PlayerMoveForBriney: @ 81ED355
	walk_down
	walk_left
	walk_in_place_fastest_right
	step_end

Route104_Movement_BrineyBoardBoat: @ 81ED359
	walk_down
	walk_down
	step_end

Route104_Movement_BrineyExitBoat: @ 81ED35C
	walk_down
	walk_in_place_fastest_left
	step_end

Route104_EventScript_Ivan:: @ 81ED35F
	trainerbattle_single TRAINER_IVAN, Route104_Text_IvanIntro, Route104_Text_IvanDefeat
	msgbox Route104_Text_IvanPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Billy:: @ 81ED376
	trainerbattle_single TRAINER_BILLY, Route104_Text_BillyIntro, Route104_Text_BillyDefeat
	msgbox Route104_Text_BillyPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Haley:: @ 81ED38D
	trainerbattle_single TRAINER_HALEY_1, Route104_Text_HaleyIntro, Route104_Text_HaleyDefeat, Route104_EventScript_TryRegisterHaleyAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route104_EventScript_RematchHaley
	setvar VAR_0x8004, TRAINER_HALEY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	compare VAR_RESULT, FALSE
	goto_if_eq Route104_EventScript_TryRegisterHaley
	msgbox Route104_Text_HaleyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_TryRegisterHaleyAfterBattle:: @ 81ED3CE
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterHaleyAfterBattle
	release
	end

Route104_EventScript_RegisterHaleyAfterBattle:: @ 81ED3DF
	msgbox Route104_Text_HaleyRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_HALEY_1
	release
	end

Route104_EventScript_TryRegisterHaley:: @ 81ED3F8
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterHaley
	msgbox Route104_Text_HaleyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_RegisterHaley:: @ 81ED40B
	msgbox Route104_Text_HaleyRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_HALEY_1
	release
	end

Route104_EventScript_RematchHaley:: @ 81ED424
	trainerbattle_rematch TRAINER_HALEY_1, Route104_Text_HaleyRematchIntro, Route104_Text_HaleyRematchDefeat
	msgbox Route104_Text_HaleyPostRematch, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Winston:: @ 81ED43B
	trainerbattle_single TRAINER_WINSTON_1, Route104_Text_WinstonIntro, Route104_Text_WinstonDefeat, Route104_EventScript_TryRegisterWinstonAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route104_EventScript_RematchWinston
	setvar VAR_0x8004, TRAINER_WINSTON_1
	specialvar VAR_RESULT, IsTrainerRegistered
	compare VAR_RESULT, FALSE
	goto_if_eq Route104_EventScript_TryRegisterWinston
	msgbox Route104_Text_WinstonPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_TryRegisterWinstonAfterBattle:: @ 81ED47C
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterWinstonAfterBattle
	release
	end

Route104_EventScript_RegisterWinstonAfterBattle:: @ 81ED48D
	msgbox Route104_Text_WinstonRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_WINSTON_1
	release
	end

Route104_EventScript_TryRegisterWinston:: @ 81ED4A6
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterWinston
	msgbox Route104_Text_WinstonPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_RegisterWinston:: @ 81ED4B9
	msgbox Route104_Text_WinstonRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_WINSTON_1
	release
	end

Route104_EventScript_RematchWinston:: @ 81ED4D2
	trainerbattle_rematch TRAINER_WINSTON_1, Route104_Text_WinstonRematchIntro, Route104_Text_WinstonRematchDefeat
	msgbox Route104_Text_WinstonPostRematch, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Cindy:: @ 81ED4E9
	trainerbattle_single TRAINER_CINDY_1, Route104_Text_CindyIntro, Route104_Text_CindyDefeat, Route104_EventScript_TryRegisterCindyAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route104_EventScript_RematchCindy
	setvar VAR_0x8004, TRAINER_CINDY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	compare VAR_RESULT, FALSE
	goto_if_eq Route104_EventScript_TryRegisterCindy
	msgbox Route104_Text_CindyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_TryRegisterCindyAfterBattle:: @ 81ED52A
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterCindyAfterBattle
	release
	end

Route104_EventScript_RegisterCindyAfterBattle:: @ 81ED53B
	msgbox Route104_Text_CindyRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_CINDY_1
	release
	end

Route104_EventScript_TryRegisterCindy:: @ 81ED554
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterCindy
	msgbox Route104_Text_CindyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_RegisterCindy:: @ 81ED567
	msgbox Route104_Text_CindyRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_CINDY_1
	release
	end

Route104_EventScript_RematchCindy:: @ 81ED580
	trainerbattle_rematch TRAINER_CINDY_1, Route104_Text_CindyRematchIntro, Route104_Text_CindyRematchDefeat
	msgbox Route104_Text_CindyPostRematch, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Gina:: @ 81ED597
	trainerbattle_double TRAINER_GINA_AND_MIA_1, Route104_Text_GinaIntro, Route104_Text_GinaDefeat, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route104_Text_GinaPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Mia:: @ 81ED5B6
	trainerbattle_double TRAINER_GINA_AND_MIA_1, Route104_Text_MiaIntro, Route104_Text_MiaDefeat, Route104_Text_MiaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route104_Text_MiaPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Darian:: @ 81ED5D5
	trainerbattle_single TRAINER_DARIAN, Route104_Text_DarianIntro, Route104_Text_DarianDefeat
	msgbox Route104_Text_DarianPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_Text_BrineyLivesInSeasideCottage: @ 81ED5EC
	.string "저기 해변에 있는 작은 집에는\n"
	.string "하기노인이라는 사람이 살고 있어!\p"
	.string "옛날엔 어떤 파도도 무서워하지 않는\n"
	.string "굉장한 실력의 선원이었다고 해!$"
	@ その はまべの こやにはｎ
	@ ハギろうじん という ひとが すんでるの!ｐ
	@ むかしは どんな あらなみも おそれないｎ
	@ すごうでの ふなのり だった らしいわ!

Route104_Text_WhatsItLikeAtBottomOfSea: @ 81ED662
	.string "바다라...\p"
	.string "바다 깊은 곳은 대체\n"
	.string "어떤 모습을 하고 있을까?$"
	@ うみ かぁ……ｐ
	@ うみのそこ って いったいｎ
	@ どんな ふうに なってるのかな?

Route104_Text_ThrowBallAtWeakenedPokemon: @ 81ED6A2
	.string "몬스터볼을 던질 때\n"
	.string "포켓몬의 기술로\l"
	.string "독이나 화상 상태로 만들거나\l"
	.string "잠들게 해 놓으면 훨씬 잡기가 쉬워!$"
	@ モンスタ-ボ-ルを なげるときはｎ
	@ ポケモンの わざでｌ
	@ どくや やけどに したりｌ
	@ ねむらせると つかまえ やすいよ!

Route104_Text_OnlyThrowBallAtWildPokemon: @ 81ED735
	.string "남의 포켓몬을 잡으면 도둑이야\p"
	.string "몬스터볼은\n"
	.string "야생 포켓몬에게만 던져야 돼!$"
	@ ひとの ポケモンを とったら どろぼうよｐ
	@ モンスタ-ボ-ルはｎ
	@ やせいの ポケモンにだけ なげましょうね!

Route104_Text_ImNotATrainer: @ 81ED7A2
	.string "난 트레이너가 아니야\p"
	.string "그치만 트레이너끼리 눈이 마주치면\n"
	.string "승부를 하자는 사인이지!\p"
	.string "만약 배틀하고 싶지 않을 때는\n"
	.string "시선을 마주치지 않으면 돼!$"
	@ わたし トレ-ナ-じゃ ないわよｐ
	@ でも トレ-ナ-どうし しせんが あうのはｎ
	@ しょうぶしようって サイン なのよね!ｐ
	@ もし たたかいたく なかったらｎ
	@ しせんを あわさなければ いいのよね!

Route104_Text_LikeFillingMouthWithSeedsTakeThis: @ 81ED838
	.string "입안을 씨앗으로 가득 채우고\n"
	.string "빠르게 푸푸풋! 뱉는 게 상쾌해서 좋아!\p"
	.string "너도 이거 줄 테니까 써 봐!\p"
	.string "포켓몬에게 쓰면\n"
	.string "씨앗을 날리는 기술을 배울 거야!$"
	@ くちのなかに タネを いっぱい いれてｎ
	@ それを プププッ! とふきだすのが すき!ｐ
	@ おまえも これを やるから つかえよ!ｐ
	@ ポケモンに つかうとさｎ
	@ タネを とばす わざを おぼえるから!

Route104_Text_TMsAreOneTimeUse: @ 81ED8E7
	.string "하나 어드바이스 해줄게!\p"
	.string "기술머신은 일회용이야!\n"
	.string "쓰면 사라져 버리지\l"
	.string "잘 생각하고 나서 써야 돼!$"
	@ ひとこと アドバイスな!ｐ
	@ わざマシンは つかいすて!ｎ
	@ つかうと なくなるからｌ
	@ よく かんがえてから つかえよな!

Route104_Text_DontNeedThisTakeIt: @ 81ED96A
	.string "여기 플라워숍 요즘에\n"
	.string "화분도 팔고 있어!\p"
	.string "너무 기뻐서 잔뜩 사버리는 바람에\n"
	.string "내 하양허브는 이제 필요가 없어\l"
	.string "그러니까 네가 가져가!$"
	@ この フラワ-ショップ ちかごろｎ
	@ うえきも うって くれるのよ!ｐ
	@ うれしくて たくさん かっちゃったからｎ
	@ あたしの しろいハ-ブは もう いらないわｌ
	@ あなた もらってよ!

Route104_Text_FlowerShopSellingSaplings: @ 81EDA0F
	.string "여기 플라워숍 요즘에\n"
	.string "화분도 팔고 있어!\p"
	.string "너무 기뻐서 잔뜩 사버렸지 뭐야!\n"
	.string "어디에 장식할까?$"
	@ この フラワ-ショップ ちかごろｎ
	@ うえきも うって くれるのよ!ｐ
	@ うれしくて たくさん かっちゃった!ｎ
	@ どこに かざろうかしら?

Route104_Text_MrBrineysCottage: @ 81EDA8C
	.string "“하기노인의 작은 집”$"
	@ 「ハギろうじんの こや」

Route104_Text_RouteSignPetalburg: @ 81EDAA1
	.string "여기는 104번 도로\n"
	.string "{RIGHT_ARROW} 등화도시$"
	@ ここは 104ばん どうろｎ
	@ ©しう トウカシティ

Route104_Text_RouteSignRustboro: @ 81EDABC
	.string "여기는 104번 도로\n"
	.string "{UP_ARROW} 금탄도시$"
	@ ここは 104ばん どうろｎ
	@ ©し  カナズミシティ

Route104_Text_PrettyPetalFlowShop: @ 81EDAD6
	.string "“플라워숍 꽃잎 화원”$"
	@ 「フラワ-ショップ サン®トウカ」

Route104_Text_TrainerTipsDoubleBattles: @ 81EDAEF
	.string "정보 나눔 게시판!!\p"
	.string "호연지방에는\n"
	.string "더블배틀이라고 해서 2대2로\l"
	.string "포켓몬 승부를 걸어오는\l"
	.string "트레이너가 있습니다!\p"
	.string "더블배틀에서는 포켓몬 리스트의\n"
	.string "왼쪽과 가장 위에 있는\l"
	.string "포켓몬이 나가서 배틀을 하니\l"
	.string "리스트 순서에 주의합시다!$"
	@ おとくな けいじばん!!ｐ
	@ ホウエンちほう にはｎ
	@ ダブルバトルと いって 2たい2のｌ
	@ ポケモンしょうぶを いどんでくるｌ
	@ トレ-ナ-が います!ｐ
	@ ダブルバトルでは ポケモンの リストのｎ
	@ ひだりと いちばん うえにいるｌ
	@ ポケモンが とびだして たたかうのでｌ
	@ リストの ならびには ようちゅうい!

Route104_Text_MayWeShouldRegister: @ 81EDBFF
	.string "봄이: 앗 {PLAYER}{K_AYA}!\p"
	.string "데봉 코포레이션에서 포켓내비에\n"
	.string "엔트리콜을 장착받았구나!\p"
	.string "그럼 우리도\n"
	.string "서로 전화할 수 있게\l"
	.string "이름을 등록해 놓자!$"
	@ ハルカ『あっ §あ§お!ｐ
	@ デボンコ-ポレ-ションで ポケナビにｎ
	@ エントリ-コ-ルを つけて もらったのね!ｐ
	@ じゃあ あたしたちもｎ
	@ おたがいに よびだせる ようにｌ
	@ なまえを とうろく しておこうよ!

Route104_Text_RegisteredMay: @ 81EDC8F
	.string "{PLAYER}{K_EUNNEUN} 봄이를\n"
	.string "포켓내비에 등록했다!$"
	@ §あは ハルカをｎ
	@ ポケナビに とうろく した!

Route104_Text_MayHowsYourPokedex: @ 81EDCB1
	.string "봄이: 그런데 {PLAYER}{K_AYA}\n"
	.string "포켓몬 도감의 상태는 어때?$"
	@ ハルカ『ところで §あ§おのｎ
	@ ポケモンずかんの ちょうしは どう?

Route104_Text_MayMinesDecentLetsBattle: @ 81EDCED
	.string "나는 꽤 좋은 느낌이야!\n"
	.string "어때? 한번 승부해 볼래?$"
	@ あたしは かなり いい かんじ!ｎ
	@ どう? ちょっと しょうぶ してみる?

Route104_Text_MayHaventRaisedPokemon: @ 81EDD2A
	.string "봄이: 에이 뭐야-\n"
	.string "그다지 포켓몬을 잡거나\l"
	.string "키우지 않았구나?\p"
	.string "그럼 트레이너로서\n"
	.string "아직 멀었네!$"
	@ ハルカ『え- なんでよ-ｎ
	@ あんまり ポケモン つかまえたりｌ
	@ そだてたり してないのかな?ｐ
	@ それじゃあ トレ-ナ-としてｎ
	@ まだまだ ね!

Route104_Text_MayLetsBattle: @ 81EDD9F
	.string "봄이: 어때? 나하고 여기서\n"
	.string "한번 승부해 볼래?$"
	@ ハルカ『どう? あたしと ここでｎ
	@ ちょっと しょうぶ してみる?

Route104_Text_MayIntro: @ 81EDDDB
	.string "봄이: 이제 막 트레이너가 된\n"
	.string "{PLAYER}에게는 지지 않을 거야!$"
	@ ハルカ『トレ-ナ-に なった ばかりのｎ
	@ §あ§おには まけないよ!

Route104_Text_MayDefeat: @ 81EDE18
	.string "우와...\n"
	.string "벌써 이렇게 강해졌을 줄이야...$"
	@ うわあ……ｎ
	@ もう こんなに つよいなんて……

Route104_Text_MayPostBattle: @ 81EDE3E
	.string "봄이: 제법 포켓몬을\n"
	.string "잘 다루기 시작했구나!\p"
	.string "하지만 싸우는 것만이 아니라\n"
	.string "그곳의 하기노인처럼\l"
	.string "포켓몬과 사이좋게 지내는 것도\l"
	.string "엄청 중요해!$"
	@ ハルカ『けっこう ポケモンの あつかいｎ
	@ うまく なってきた みたいね!ｐ
	@ でも たたかわせる だけじゃなくてｎ
	@ そこの ハギろうじん みたいにｌ
	@ ポケモンと なかよくする っていうのもｌ
	@ だいじなこと なのよ!

Route104_Text_BrendanWeShouldRegister: @ 81EDF04
	.string "휘웅: 오 {PLAYER}{K_AYA}!\p"
	.string "데봉 코포레이션에서 포켓내비에\n"
	.string "엔트리콜을 장착받았구나!\p"
	.string "그럼 우리\n"
	.string "서로 전화할 수 있게\l"
	.string "이름을 등록해 놓자!$"
	@ ユウキ『おっ §あ!ｐ
	@ デボンコ-ポレ-ションで ポケナビにｎ
	@ エントリ-コ-ルを つけて もらったな!ｐ
	@ じゃあ オレたちｎ
	@ おたがいに よびだせる ようにｌ
	@ なまえを とうろく しておこうよ!

Route104_Text_RegisteredBrendan: @ 81EDFA0
	.string "{PLAYER}{K_EUNNEUN} 휘웅을\n"
	.string "포켓내비에 등록했다!$"
	@ §あは ユウキをｎ
	@ ポケナビに とうろく した!

Route104_Text_BrendanHowsYourPokedex: @ 81EDFC6
	.string "휘웅: 그나저나 {PLAYER}의\n"
	.string "포켓몬 도감은 어때?\l"
	.string "조금은 채웠으려나?$"
	@ ユウキ『ところで §あのｎ
	@ ポケモンずかんは どう?ｌ
	@ ちょっとは ペ-ジ うまったか?

Route104_Text_BrendanDoingGreatLetsBattle: @ 81EE009
	.string "나는 엄청 잘되고 있어!\n"
	.string "어때 포켓몬 승부로\l"
	.string "그 성과를 시험해 볼래?$"
	@ オレは すごいよ!ｎ
	@ どうだ ポケモン しょうぶでｌ
	@ そのせいかを ためして やろうか?

Route104_Text_BrendanNoConfidence: @ 81EE04D
	.string "휘웅: 뭐야\n"
	.string "자기 포켓몬을 못 믿겠어?$"
	@ ユウキ『なんだよｎ
	@ もってる ポケモンに じしんが ないのか?

Route104_Text_BrendanLetsBattle: @ 81EE094
	.string "휘웅: 어때 나하고 여기서\n"
	.string "승부해 볼래?$"
	@ ユウキ『どうだい オレと ここでｎ
	@ しょうぶ してみるか?

Route104_Text_BrendanIntro: @ 81EE0C7
	.string "휘웅: 이제 막 트레이너가 되었다고\n"
	.string "적당히 봐주지는 않을 거야!$"
	@ ユウキ『トレ-ナ-に なりたて だってｎ
	@ てかげんは しないからな!

Route104_Text_BrendanDefeat: @ 81EE107
	.string "흐음...\n"
	.string "제법 하는걸$"
	@ へえ……ｎ
	@ なかなか やるじゃないか

Route104_Text_BrendanPostBattle: @ 81EE120
	.string "휘웅: 제법 포켓몬을\n"
	.string "잘 다루기 시작했구나!\p"
	.string "하지만 배틀하는 것만이 아니라\n"
	.string "그곳의 하기노인처럼\l"
	.string "포켓몬과 사이좋게 지내는 것도\l"
	.string "엄청 중요하다고!$"
	@ ユウキ『けっこう ポケモンの あつかいｎ
	@ うまく なってきたな!ｐ
	@ でも たたかわせる だけじゃなくてｎ
	@ そこの ハギろうじん みたいにｌ
	@ ポケモンと なかよくする ってのもｌ
	@ だいじなこと なんだぜ!
