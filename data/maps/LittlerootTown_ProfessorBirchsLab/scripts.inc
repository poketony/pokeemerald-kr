.set LOCALID_AIDE, 1
.set LOCALID_BIRCH, 2
.set LOCALID_RIVAL, 3
.set LOCALID_BALL_CYNDAQUIL, 4
.set LOCALID_BALL_TOTODILE, 5
.set LOCALID_BALL_CHIKORITA, 6

LittlerootTown_ProfessorBirchsLab_MapScripts:: @ 81F9C91
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_ProfessorBirchsLab_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_ProfessorBirchsLab_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_ProfessorBirchsLab_OnFrame
	.byte 0

	@ State descriptions for VAR_DEX_UPGRADE_JOHTO_STARTER_STATE
	@ 1: Beat Elite Four, Dex upgrade ready
	@ 2: Received National Dex
	@ 3: Left lab after receiving National Dex
	@ 4: Entered lab after catching all Hoenn mons
	@ 5: Birch told player to choose Johto starter
	@ 6: Chose Johto starter

	@ State descriptions for VAR_BIRCH_LAB_STATE
	@ 1: Never occurs
	@ 2: Chose starter
	@ 3: Received starter in lab
	@ 4: Defeated rival on Route 103
	@ 5: Received pokedex

LittlerootTown_ProfessorBirchsLab_OnTransition: @ 81F9CA1
	call Common_EventScript_SetupRivalGfxId
	call ProfBirch_EventScript_UpdateLocation
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	goto_if_ge LittlerootTown_ProfessorBirchsLab_EventScript_SetAfterJohtoStarterLayout
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4
	goto_if_ge LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_CheckReadyForJohtoStarter
	end

LittlerootTown_ProfessorBirchsLab_EventScript_CheckReadyForJohtoStarter:: @ 81F9CCD
	specialvar VAR_RESULT, HasAllHoennMons
	compare VAR_RESULT, TRUE
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_SetReadyForJohtoStarter
	setobjectmovementtype LOCALID_RIVAL, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
	setobjectxyperm LOCALID_RIVAL, 5, 10
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SetReadyForJohtoStarter:: @ 81F9CE9
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4
	goto LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout

LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout:: @ 81F9CF3
	setmaplayoutindex LAYOUT_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB_WITH_TABLE
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SetAfterJohtoStarterLayout:: @ 81F9CF7
	setmaplayoutindex LAYOUT_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB_WITH_TABLE
	setobjectmovementtype LOCALID_RIVAL, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
	setobjectxyperm LOCALID_RIVAL, 5, 10
	end

LittlerootTown_ProfessorBirchsLab_OnWarp: @ 81F9D06
	map_script_2 VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_SetPlayerPosForReceiveStarter
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_AddRivalObject
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AddRivalObject
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters
	.2byte 0

LittlerootTown_ProfessorBirchsLab_EventScript_SetPlayerPosForReceiveStarter:: @ 81F9D40
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade:: @ 81F9D45
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	addobject LOCALID_BIRCH
	addobject LOCALID_RIVAL
	turnobject LOCALID_RIVAL, DIR_NORTH
	setobjectxy LOCALID_RIVAL, 5, 5
	turnobject LOCALID_BIRCH, DIR_SOUTH
	setobjectxy LOCALID_BIRCH, 6, 4
	turnobject LOCALID_AIDE, DIR_EAST
	setobjectxy LOCALID_AIDE, 10, 10
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AddRivalObject:: @ 81F9D71
	addobject LOCALID_RIVAL
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters:: @ 81F9D75
	addobject LOCALID_BALL_CYNDAQUIL
	addobject LOCALID_BALL_TOTODILE
	addobject LOCALID_BALL_CHIKORITA
	addobject LOCALID_RIVAL
	turnobject LOCALID_BALL_CYNDAQUIL, DIR_SOUTH
	setobjectxy LOCALID_BALL_CYNDAQUIL, 8, 4
	turnobject LOCALID_BALL_TOTODILE, DIR_SOUTH
	setobjectxy LOCALID_BALL_TOTODILE, 9, 4
	turnobject LOCALID_BALL_CHIKORITA, DIR_SOUTH
	setobjectxy LOCALID_BALL_CHIKORITA, 10, 4
	turnobject LOCALID_BIRCH, DIR_SOUTH
	setobjectxy LOCALID_BIRCH, 6, 4
	turnobject LOCALID_RIVAL, DIR_EAST
	setobjectxy LOCALID_RIVAL, 5, 5
	end

LittlerootTown_ProfessorBirchsLab_OnFrame: @ 81F9DB9
	map_script_2 VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_GiveStarterEvent
	map_script_2 VAR_BIRCH_LAB_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedexEvent
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_ProfessorBirchsLab_EventScript_UpgradeToNationalDex
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_ChooseJohtoStarter
	.2byte 0

@ The starter is technically given prior to this on Route 101 by special ChooseStarter
@ This is just where the game tells you its yours and lets you nickname it
LittlerootTown_ProfessorBirchsLab_EventScript_GiveStarterEvent:: @ 81F9DDB
	lockall
	bufferleadmonspeciesname 0
	message LittlerootTown_ProfessorBirchsLab_Text_LikeYouToHavePokemon
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox LittlerootTown_ProfessorBirchsLab_Text_WhyNotGiveNicknameToMon, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_NicknameStarter
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival
	end

LittlerootTown_ProfessorBirchsLab_EventScript_NicknameStarter:: @ 81F9E07
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival:: @ 81F9E17
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MightBeGoodIdeaToGoSeeRival, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival:: @ 81F9E36
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GetRivalToTeachYou, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_ROUTE_101_BOY
	setvar VAR_BIRCH_LAB_STATE, 3
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival:: @ 81F9E48
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DontBeThatWay, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedexEvent:: @ 81F9E67
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForPokedex
	waitmovement 0
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedex
	end

LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForPokedex: @ 81F9E78
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_ProfessorBirchsLab_EventScript_UpgradeToNationalDex:: @ 81F9E80
	lockall
	delay 30
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OtherRegionsUpgradeToNational, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCH, LittlerootTown_ProfessorBirchsLab_Movement_BirchRetrievePokedexes
	waitmovement 0
	delay 20
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 20
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_MayUpgradeComment
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_BrendanUpgradeComment
	playse SE_PC_ON
	waitse
	delay 20
	applymovement LOCALID_BIRCH, LittlerootTown_ProfessorBirchsLab_Movement_BirchReturnPokedex
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OkayAllDone, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_ProfessorBirchsLab_Text_PokedexUpgradedToNational
	waitmessage
	waitfanfare
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2
	setvar VAR_SCOTT_BF_CALL_STEP_COUNTER, 0
	setflag FLAG_SCOTT_CALL_BATTLE_FRONTIER
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayUpgradeComment:: @ 81F9F32
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayUpgradeSoCool, MSGBOX_DEFAULT
	closemessage
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanUpgradeComment:: @ 81F9F3C
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanYouCanThankMe, MSGBOX_DEFAULT
	closemessage
	return

LittlerootTown_ProfessorBirchsLab_Movement_BirchRetrievePokedexes: @ 81F9F46
	walk_left
	walk_in_place_fastest_down
	delay_16
	delay_16
	walk_right
	walk_in_place_fastest_down
	delay_16
	delay_16
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_BirchReturnPokedex: @ 81F9F58
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_in_place_fastest_down
	step_end

LittlerootTown_ProfessorBirchsLab_EventScript_ChooseJohtoStarter:: @ 81F9F62
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForJohtoStarter
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CompletedDexChoosePokemon, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForJohtoStarter: @ 81F9F7C
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_ProfessorBirchsLab_EventScript_Aide:: @ 81F9F84
	lock
	faceplayer
	compare VAR_BIRCH_LAB_STATE, 3
	goto_if_ge LittlerootTown_ProfessorBirchsLab_EventScript_AideReceivedStarter
	goto_if_set FLAG_BIRCH_AIDE_MET, LittlerootTown_ProfessorBirchsLab_EventScript_AideAlreadyMet
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchAwayOnFieldwork, MSGBOX_DEFAULT
	setflag FLAG_BIRCH_AIDE_MET
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AideAlreadyMet:: @ 81F9FA7
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchIsntOneForDeskWork, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AideReceivedStarter:: @ 81F9FB1
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchEnjoysRivalsHelpToo, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Cyndaquil:: @ 81F9FBB
	release
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	goto_if_ge LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	showmonpic SPECIES_CYNDAQUIL, 10, 3
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeCyndaquil, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveCyndaquil
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Totodile:: @ 81F9FEF
	release
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	goto_if_ge LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	showmonpic SPECIES_TOTODILE, 10, 3
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeTotodile, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveTotodile
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Chikorita:: @ 81FA023
	release
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	goto_if_ge LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	showmonpic SPECIES_CHIKORITA, 10, 3
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeChikorita, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveChikorita
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter:: @ 81FA057
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BetterLeaveOthersAlone, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime:: @ 81FA061
	hidemonpic
	msgbox LittlerootTown_ProfessorBirchsLab_Text_TakeYourTimeAllInvaluable, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GiveCyndaquil:: @ 81FA06C
	bufferspeciesname 0, SPECIES_CYNDAQUIL
	setvar VAR_TEMP_1, SPECIES_CYNDAQUIL
	givemon SPECIES_CYNDAQUIL, 5, ITEM_NONE
	compare VAR_RESULT, 0
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToParty
	compare VAR_RESULT, 1
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToPC
	hidemonpic
	goto Common_EventScript_NoMoreRoomForPokemon
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToParty:: @ 81FA0A1
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BALL_CYNDAQUIL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToPC:: @ 81FA0CC
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BALL_CYNDAQUIL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC
	end

LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC:: @ 81FA0F2
	call Common_EventScript_TransferredToPC
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil:: @ 81FA0FD
	hidemonpic
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GiveTotodile:: @ 81FA10D
	bufferspeciesname 0, SPECIES_TOTODILE
	setvar VAR_TEMP_1, SPECIES_TOTODILE
	givemon SPECIES_TOTODILE, 5, ITEM_NONE
	compare VAR_RESULT, 0
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToParty
	compare VAR_RESULT, 1
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToPC
	hidemonpic
	goto Common_EventScript_NoMoreRoomForPokemon
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToParty:: @ 81FA142
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BALL_TOTODILE
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToPC:: @ 81FA16D
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BALL_TOTODILE
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC
	end

LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC:: @ 81FA193
	call Common_EventScript_TransferredToPC
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile:: @ 81FA19E
	hidemonpic
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GiveChikorita:: @ 81FA1AE
	bufferspeciesname 0, SPECIES_CHIKORITA
	setvar VAR_TEMP_1, SPECIES_CHIKORITA
	givemon SPECIES_CHIKORITA, 5, ITEM_NONE
	compare VAR_RESULT, 0
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToParty
	compare VAR_RESULT, 1
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToPC
	hidemonpic
	goto Common_EventScript_NoMoreRoomForPokemon
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToParty:: @ 81FA1E3
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BALL_CHIKORITA
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToPC:: @ 81FA20E
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BALL_CHIKORITA
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC:: @ 81FA234
	call Common_EventScript_TransferredToPC
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita:: @ 81FA23F
	hidemonpic
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter:: @ 81FA24F
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_ProfessorBirchsLab_Text_ReceivedJohtoStarter
	waitmessage
	waitfanfare
	return

LittlerootTown_ProfessorBirchsLab_EventScript_Birch:: @ 81FA25A
	lock
	faceplayer
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_CanHaveAnyOneOfRarePokemon
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_GrassyPatchWaiting
	goto_if_unset FLAG_HAS_MATCH_CALL, LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister
	goto_if_unset FLAG_ENABLE_PROF_BIRCH_MATCH_CALL, EventScript_RegisterProfBirch
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister
	end

LittlerootTown_ProfessorBirchsLab_EventScript_CanHaveAnyOneOfRarePokemon:: @ 81FA28A
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CanHaveAnyOneOfRarePokemon, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GrassyPatchWaiting:: @ 81FA294
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister:: @ 81FA29E
	goto_if_unset FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380, ProfBirch_EventScript_RatePokedexOrRegister
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3
	goto_if_eq ProfBirch_EventScript_RatePokedexOrRegister
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	goto_if_ge ProfBirch_EventScript_RatePokedexOrRegister
	compare VAR_BIRCH_LAB_STATE, 5
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_PokemonAwait
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchRivalGoneHome, MSGBOX_DEFAULT
	release
	end

EventScript_RegisterProfBirch:: @ 81FA2D2
	msgbox MatchCall_Text_BirchRegisterCall, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MatchCall_Text_RegisteredBirch, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
	setvar VAR_REGISTER_BIRCH_STATE, 2
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedex:: @ 81FA2F8
	msgbox LittlerootTown_ProfessorBirchsLab_Text_HeardYouBeatRivalTakePokedex, MSGBOX_DEFAULT
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex
	msgbox LittlerootTown_ProfessorBirchsLab_Text_ExplainPokedex, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, LittlerootTown_ProfessorBirchsLab_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_MayGivePokeBalls
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_BrendanGivePokeBalls
	setvar VAR_BIRCH_LAB_STATE, 5
	setflag FLAG_ADVENTURE_STARTED
	setvar VAR_OLDALE_TOWN_STATE, 1
	setvar VAR_LITTLEROOT_RIVAL_STATE, 4
	setvar VAR_LITTLEROOT_TOWN_STATE, 3
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayGivePokeBalls:: @ 81FA352
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayGotPokedexTooTakeThese, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	compare VAR_RESULT, FALSE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_MayNoRoomForPokeBalls
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CatchCutePokemonWithPokeBalls, MSGBOX_DEFAULT
	setvar VAR_RESULT, 0
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanGivePokeBalls:: @ 81FA37F
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanGotPokedexTooTakeThese, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	compare VAR_RESULT, FALSE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_BrendanNoRoomForPokeBalls
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CatchCoolPokemonWithPokeBalls, MSGBOX_DEFAULT
	setvar VAR_RESULT, 1
	return

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex:: @ 81FA3AC
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokedex
	waitfanfare
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 1
	return

LittlerootTown_ProfessorBirchsLab_EventScript_PokemonAwait:: @ 81FA3C4
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CountlessPokemonAwait, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayNoRoomForPokeBalls:: @ 81FA3CE
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OhYourBagsFull, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanNoRoomForPokeBalls:: @ 81FA3D7
	msgbox LittlerootTown_ProfessorBirchsLab_Text_HeyYourBagsFull, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_Movement_RivalApproachPlayer: @ 81FA3E0
	walk_down
	walk_in_place_fastest_left
	step_end

LittlerootTown_ProfessorBirchsLab_EventScript_Machine:: @ 81FA3E3
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Rival:: @ 81FA3EC
	lock
	faceplayer
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_RivalFuturePlans
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	goto_if_ge LittlerootTown_ProfessorBirchsLab_EventScript_RivalHaveYouGoneToBattleFrontier
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2
	goto_if_ge LittlerootTown_ProfessorBirchsLab_EventScript_RivalTakeBreakFromFieldwork
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_MayWhereShouldIGoNext
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_BrendanWhereShouldIGoNext
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayWhereShouldIGoNext:: @ 81FA428
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayWhereShouldIGoNext, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanWhereShouldIGoNext:: @ 81FA431
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanWhereShouldIGoNext, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_RivalFuturePlans:: @ 81FA43A
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_MayWhatNextImStayingHere
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_BrendanPreferCollectingSlowly
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayWhatNextImStayingHere:: @ 81FA453
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayWhatNextImStayingHere, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanPreferCollectingSlowly: @ 81FA45C
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanPreferCollectingSlowly, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_RivalHaveYouGoneToBattleFrontier:: @ 81FA465
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_MayHaveYouGoneToBattleFrontier
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_BrendanHaveYouGoneToBattleFrontier
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayHaveYouGoneToBattleFrontier:: @ 81FA47E
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayHaveYouGoneToBattleFrontier, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanHaveYouGoneToBattleFrontier:: @ 81FA487
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanHaveYouGoneToBattleFrontier, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_RivalTakeBreakFromFieldwork:: @ 81FA490
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_MayTakeBreakFromFieldwork
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_BrendanTakeBreakFromFieldwork
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayTakeBreakFromFieldwork:: @ 81FA4A9
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayTakeBreakFromFieldwork, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanTakeBreakFromFieldwork:: @ 81FA4B2
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanTakeBreakFromFieldwork, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_PC:: @ 81FA4BB
	msgbox LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Bookshelf:: @ 81FA4C4
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Book:: @ 81FA4CD
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BookTooHardToRead, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ScottAboardSSTidalCall:: @ 81FA4D6
	lockall
	pokenavcall LittlerootTown_ProfessorBirchsLab_Text_ScottAboardSSTidalCall
	waitmessage
	clearflag FLAG_SCOTT_CALL_BATTLE_FRONTIER
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_Text_BirchAwayOnFieldwork: @ 81FA4E2
	.string "응? 털보박사님?\p"
	.string "박사님이라면 필드워크하러\n"
	.string "나가셔서 지금 안 계세요\p"
	.string "...아 필드워크라는 건\p"
	.string "실제로 산이나 들로 나가서\n"
	.string "연구를 하는 걸 말하는 겁니다!\p"
	.string "박사님은 책상 위에서 연구하시기보단\n"
	.string "실제로 밖으로 나가서\l"
	.string "체험하는 타입의 사람이에요!$"
	// え? オダマキはかせ?ｐ
	// はかせ なら フィ-ルドワ-クにｎ
	// でかけていて いませんよｐ
	// ……あ フィ-ルドワ-クって いうのはｐ
	// じっさいに のやまへ でかけていってｎ
	// けんきゅうを すること ですね!ｐ
	// はかせは つくえのうえで けんきゅうをｎ
	// するよりも じっさいに そとへ とびだしてｌ
	// たいけんする タイプのひと なんです!

LittlerootTown_ProfessorBirchsLab_Text_BirchIsntOneForDeskWork: @ 81FA641
	.string "박사님은 책상 위에서 연구하시기보단\n"
	.string "실제로 밖으로 나가서\l"
	.string "체험하는 타입의 사람이에요!$"
	// はかせは つくえのうえで けんきゅうをｎ
	// するよりも じっさいに そとへ とびだしてｌ
	// たいけんする タイプのひと なんです!

LittlerootTown_ProfessorBirchsLab_Text_BirchEnjoysRivalsHelpToo: @ 81FA6CE
	.string "털보박사님은\n"
	.string "포켓몬이 어디에 살고 있는가\l"
	.string "분포를 조사하고 있어요\p"
	.string "{RIVAL}{K_I}는 좋아하는 아빠를\n"
	.string "도와주고 있답니다$"
	// オダマキはかせはｎ
	// ポケモンが どこに すんでいるのかｌ
	// ぶんぷの ちょうさを なさっていますｐ
	// §かさんは すきな おとうさんのｎ
	// おてつだいを なさって いるのですよ

LittlerootTown_ProfessorBirchsLab_Text_LikeYouToHavePokemon: @ 81FA74D
	.string "털보박사: ...자 그럼 {PLAYER}{K_AYA}!\p"
	.string "너에 대한 얘기는 너희 아버지한테\n"
	.string "항상 듣고 있단다!\p"
	.string "넌 아직 자신의 포켓몬을\n"
	.string "가져본 적이 없다고 하던데?\p"
	.string "그런 거치고 방금 전의 배틀은\n"
	.string "꽤 훌륭했는데 말이지!\p"
	.string "역시 너한테는 아버지의\n"
	.string "피가 흐르고 있나 보구나!\p"
	.string "그래그래! 구해준 보답으로\n"
	.string "아까 고른 포켓몬을\l"
	.string "너에게 선물하도록 하마!\p"
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "{STR_VAR_1}{K_EULREUL} 받았다!$"
	// オダマキ『……さて §あ§お!ｐ
	// きみのことは おとうさん からｎ
	// いつも きかされていたよ!ｐ
	// きみは まだ じぶんの ポケモンをｎ
	// もったことが ないんだって?ｐ
	// それにしては さっきの たたかいぶりｎ
	// なかなか みごと だったよ!ｐ
	// やっぱり きみには おとうさんのｎ
	// ちが ながれて いるんだな!ｐ
	// そうそう! たすけてくれた おれいにｎ
	// さっきの ポケモンは わたしからｌ
	// きみへの プレゼントに しよう!ｐ
	// §あはｎ
	// §いを もらった!

LittlerootTown_ProfessorBirchsLab_Text_WhyNotGiveNicknameToMon: @ 81FA8B1
	.string "털보박사: 모처럼이니까 {STR_VAR_1}에게\n"
	.string "닉네임을 지어주는 건 어떠니?$"
	// オダマキ『せっかく だから §いにｎ
	// ニックネ-ムを つけてみては どうだい?

LittlerootTown_ProfessorBirchsLab_Text_MightBeGoodIdeaToGoSeeRival: @ 81FA8F6
	.string "털보박사: 앞으로 더욱더 많은\n"
	.string "경험을 쌓아 가면\l"
	.string "좋은 트레이너가 될 거 같구나!\p"
	.string "마침 우리 {RIVAL}{K_I}도\n"
	.string "나를 도와주고 있으니까\l"
	.string "포켓몬 조사를 하고 있거든\p"
	.string "{PLAYER}{K_AYA}\n"
	.string "만나러 가면 어떻겠느냐?$"
	// オダマキ『これから さらにｎ
	// けいけんを つんで いけばｌ
	// いい トレ-ナ-に なれそうだ!ｐ
	// ちょうど うちの §かもｎ
	// わたしを てつだい ながらｌ
	// ポケモンの ちょうさを しているんだｐ
	// §あ§お いちどｎ
	// あいに いったら どうだろう?

LittlerootTown_ProfessorBirchsLab_Text_GetRivalToTeachYou: @ 81FA9D5
	.string "털보박사: 그럴래!\n"
	.string "그거 {RIVAL}{K_I}도 좋아하겠구나!\p"
	.string "트레이너가 어떤 건지\n"
	.string "배워보는 것도 좋겠지!$"
	// オダマキ『そうか!ｎ
	// それは §かも よろこぶぞ!ｐ
	// トレ-ナ-が どんな ものかｎ
	// おしえてもらうと いいぞ!

LittlerootTown_ProfessorBirchsLab_Text_DontBeThatWay: @ 81FAA35
	.string "털보박사: 그러지 말고\n"
	.string "만나러 가면 어떻겠느냐?$"
	// オダマキ『そんなこと いわずにｎ
	// あいに いったら どうだろう?

LittlerootTown_ProfessorBirchsLab_Text_BirchRivalGoneHome: @ 81FAA74
	.string "털보박사: {RIVAL}{K_I}라면\n"
	.string "집에 돌아가 있는 거 아니니?\p"
	.string "아니면 또 어딘가의 풀숲을\n"
	.string "뒤지고 있을지도 모르겠구나...\p"
	.string "그리고 네 포켓몬이 다쳤다면\n"
	.string "너희 집에서 쉬었다가 움직이렴!$"
	// オダマキ『§か だったらｎ
	// いえに かえってるんじゃ ないのか?ｐ
	// それとも また どこかの くさむらにｎ
	// もぐりこんで いるのかも……ｐ
	// もしも きみの ポケモンが キズついたらｎ
	// じぶんの いえで やすむと いいぞ!

LittlerootTown_ProfessorBirchsLab_Text_HeardYouBeatRivalTakePokedex: @ 81FAB22
	.string "털보박사: 오 {PLAYER}{K_AYA}!\p"
	.string "처음인데도 {RIVAL}{K_I}한테\n"
	.string "이기다니 대단하구나!\p"
	.string "{RIVAL}{K_I}는 상당히 예전부터\n"
	.string "내 연구를 도와주고 있어서\l"
	.string "트레이너 경력은 꽤 긴데 말이지!\p"
	.string "그래! {PLAYER}한테도\n"
	.string "연구를 위해 마련해 놓은\l"
	.string "이 포켓몬 도감을 주도록 하마!$"
	// オダマキ『おっ §あ§お!ｐ
	// はじめてで §かにｎ
	// かつ だなんて すごいじゃないか!ｐ
	// §かは かなり まえからｎ
	// わたしの けんきゅうを てつだっていてｌ
	// トレ-ナ-れきは けっこう ながいんだよ!ｐ
	// うむ! §あ§お にもｎ
	// けんきゅうの ために とりよせたｌ
	// この ポケモンずかんを あげよう!
	
LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokedex: @ 81FAC32
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "포켓몬 도감을 받았다!$"
	// §あはｎ
	// ポケモンずかんを もらった!

LittlerootTown_ProfessorBirchsLab_Text_ExplainPokedex: @ 81FAC4B
	.string "털보박사: 그 포켓몬 도감은\n"
	.string "네가 만난 포켓몬을\p"
	.string "자동으로 기록해주는\n"
	.string "하이테크한 도구란다!\p"
	.string "{RIVAL}{K_I}도 그 도감을 들고\n"
	.string "이곳저곳 놀러 다니고 있지\p"
	.string "그러면서 희귀한 포켓몬을 잡아서\n"
	.string "도감에 기록하면 말이지\p"
	.string "필드워크하고 있는 나를\n"
	.string "찾아내고는 그걸 보여준단다!$"
	// オダマキ『その ポケモンずかんはｎ
	// きみが であった ポケモンをｐ
	// じどうてきに きろく していってくれるｎ
	// ハイテクな どうぐ なんだ!ｐ
	// §かも その ずかんを もっていてｎ
	// あちこちに あそびに いくんだなｐ
	// で めずらしい ポケモンを つかまえてｎ
	// ずかんに きろく できるとだねｐ
	// フィ-ルドワ-クを している わたしをｎ
	// さがしだしては みせて くれるんだよ!

LittlerootTown_ProfessorBirchsLab_Text_CountlessPokemonAwait: @ 81FAD6F
	.string "털보박사: 너의 앞길에는\n"
	.string "수많은 포켓몬이 기다리고 있단다!\p"
	.string "아- 빨리 필드워크하러\n"
	.string "나가고 싶어졌다!$"
	// オダマキ『きみの ゆくてにはｎ
	// たくさんの ポケモンが まっているよ!ｐ
	// あ- はやく フィ-ルドワ-クにｎ
	// いきたく なってきたぞ!

LittlerootTown_ProfessorBirchsLab_Text_MayGotPokedexTooTakeThese: @ 81FADD7
	.string "봄이: {PLAYER}도\n"
	.string "포켓몬 도감을 받았구나!\p"
	.string "잘됐다! 나랑 똑같네!\n"
	.string "그럼 난 이걸 줄게!$"
	// ハルカ『§あ§おもｎ
	// ポケモンずかん もらったんだね!ｐ
	// よかったね! あたしと いっしょだよ!ｎ
	// じゃあ あたしは これを あげる!

LittlerootTown_ProfessorBirchsLab_Text_CatchCutePokemonWithPokeBalls: @ 81FAE40
	.string "봄이: 포켓몬이\n"
	.string "잔뜩 있으면 즐겁지!\p"
	.string "난 여러 포켓몬을 찾고 싶으니까\n"
	.string "다양한 곳을 찾을 거야!\p"
	.string "그리고 귀여운 포켓몬이 있으면\n"
	.string "몬스터볼로 잡아버려야지!$"
	// ハルカ『ポケモンがｎ
	// たくさん いると たのしいよ!ｐ
	// あたし いろんな ポケモン さがしたいからｎ
	// いろんな ところを さがすわ!ｐ
	// そして かわいい ポケモンが いたらｎ
	// モンスタ-ボ-ルで つかまえちゃう!

LittlerootTown_ProfessorBirchsLab_Text_OhYourBagsFull: @ 81FAEF3
	.string "어라? 가방이 가득 찼네$"
	// あら? バッグ いっぱいだよ

LittlerootTown_ProfessorBirchsLab_Text_MayWhereShouldIGoNext: @ 81FAF08
	.string "봄이: 이번엔 어디까지\n"
	.string "포켓몬 찾으러 가볼까?$"
	// ハルカ『こんどは どこまでｎ
	// ポケモンを さがしに いこうかな?

LittlerootTown_ProfessorBirchsLab_Text_BrendanGotPokedexTooTakeThese: @ 81FAF3F
	.string "휘웅: 흐음 {PLAYER}도\n"
	.string "포켓몬 도감을 받았구나\p"
	.string "그럼 난 이걸 줄게$"
	// ユウキ『ふうん §あもｎ
	// ポケモンずかん もらったのかｐ
	// じゃあ オレは これ やるよ

LittlerootTown_ProfessorBirchsLab_Text_CatchCoolPokemonWithPokeBalls: @ 81FAF8E
	.string "휘웅: 포켓몬이\n"
	.string "잔뜩 있으면 즐거우니까\p"
	.string "난 여러 포켓몬을 찾기 위해\n"
	.string "다양한 곳에 갈 거야\p"
	.string "그리고 멋진 포켓몬이 있으면\n"
	.string "몬스터볼로 잡을 거야$"
	// ユウキ『ポケモンがｎ
	// たくさん いると たのしいからなｐ
	// オレ いろんな ポケモン さがすためｎ
	// いろんな ところに いくんだｐ
	// そして かっこいい ポケモンが いたらｎ
	// モンスタ-ボ-ルで つかまえるんだ

LittlerootTown_ProfessorBirchsLab_Text_HeyYourBagsFull: @ 81FB05D
	.string "어라? 가방이 가득 찼네$"
	// おや? バッグ いっぱいだよ

LittlerootTown_ProfessorBirchsLab_Text_BrendanWhereShouldIGoNext: @ 81FB073
	.string "휘웅: 이번엔 어디로\n"
	.string "포켓몬 찾으러 가볼까...$"
	// ユウキ『こんどは どこにｎ
	// ポケモン さがしに いこうかな……

LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine: @ 81FB0A2
	.string "뭔가 엄청나 보이는 머신이다!\n"
	.string "박사님이 연구에 사용하시는 걸까?$"
	// なんか すごそうな マシンだ!ｎ
	// はかせが けんきゅうに つかうのかな?

LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch: @ 81FB0E7
	.string "연구에 사용되고 있는 PC다!\n"
	.string "... 만지지는 말자$"
	// けんきゅうに つかわれている パソコンだ!ｎ
	// …… さわるのは やめておこう

LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon: @ 81FB124
	.string "포켓몬에 대해 적힌\n"
	.string "책이 가득 있다!$"
	// ポケモンに ついて かかれたｎ
	// ほんが いっぱい ある!

LittlerootTown_ProfessorBirchsLab_Text_BookTooHardToRead: @ 81FB148
	.string "어려워 보이는 책이 놓여 있다!$"
	// むずかしそうな ほんが おいてある!

LittlerootTown_ProfessorBirchsLab_Text_OtherRegionsUpgradeToNational: @ 81FB16D
	.string "털보박사: ...자 그럼\p"
	.string "{PLAYER}{K_WAGWA} {RIVAL}{K_I}에게 포켓몬의\n"
	.string "조사를 부탁했었는데\p"
	.string "너희들의 노력 덕분에\n"
	.string "여러 가지를 알 수 있었단다!\p"
	.string "아무래도 호연지방에는\n"
	.string "다른 지방의 포켓몬도\l"
	.string "서식하고 있는 것 같아!\p"
	.string "그만큼 호연지방이\n"
	.string "풍부한 자연으로 둘러싸여\l"
	.string "있다는 거겠지!\p"
	.string "그런 이유로 너희들의 도감을\n"
	.string "전국도감으로\l"
	.string "버전 업시켜 주려고 한단다!\p"
	.string "자 도감을 줘 보렴!$"
	// オダマキ『……さてｐ
	// §あ§おと §かに ポケモンのｎ
	// ちょうさを おねがい していた わけだがｐ
	// きみたちの どりょくの おかげでｎ
	// いろんな ことが わかってきた!ｐ
	// どうやら ホウエンちほう にはｎ
	// それいがいの ちほうの ポケモンもｌ
	// せいそく している らしいんだ!ｐ
	// それだけ ホウエンちほうはｎ
	// ゆたかな しぜんに めぐまれているｌ
	// という ことなんだろうな!ｐ
	// というわけで きみたちの ずかんをｎ
	// ぜんこくばんに バ-ジョンアップｌ
	// してあげようと おもう!ｐ
	// さあ ずかんを かしておくれ!

LittlerootTown_ProfessorBirchsLab_Text_MayUpgradeSoCool: @ 81FB30F
	.string "봄이: 에헤헤-!\p"
	.string "내 도감까지\n"
	.string "전국도감으로 해주시다니\p"
	.string "{PLAYER}{K_IGA} 잔뜩 포켓몬을\n"
	.string "조사해 준 덕분이야!$"
	// ハルカ『えへへ-!ｐ
	// あたしの ずかんまでｎ
	// ぜんこくばんに してもらえる なんてｐ
	// §あ§おが たくさん ポケモンをｎ
	// しらべてくれた おかげだね!

LittlerootTown_ProfessorBirchsLab_Text_BrendanYouCanThankMe: @ 81FB38E
	.string "휘웅: 내가 열심히 호연지방의\n"
	.string "포켓몬을 조사했으니까\p"
	.string "{PLAYER}의 도감도 전국도감으로\n"
	.string "해주신 거야 운이 좋구나!$"
	// ユウキ『オレ はりきって ホウエンじゅうのｎ
	// ポケモンのこと しらべたからなｐ
	// §あも ずかんを ぜんこくばんにｎ
	// してもらえて ラッキ-だったな!

LittlerootTown_ProfessorBirchsLab_Text_OkayAllDone: @ 81FB419
	.string "털보박사: 자 다 됐다!$"
	// オダマキ『ホイ できたぞ!

LittlerootTown_ProfessorBirchsLab_Text_PokedexUpgradedToNational: @ 81FB436
	.string "{PLAYER}의 포켓몬 도감이\n"
	.string "전국도감으로 버전 업했다!$"
	// §あの ポケモンずかんがｎ
	// ぜんこくばんに バ-ジョンアップ した!

LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2: @ 81FB466
	.string "털보박사: 알겠니?\n"
	.string "챔피언이 되었다고 해서\l"
	.string "포켓몬의 길은 끝난 게 아니란다\p"
	.string "아직 발을 내딛지 않은 풀숲은\n"
	.string "언제까지나 널 기다리고 있지!$"
	// オダマキ『いいかい?ｎ
	// チャンピオンに なったから といってｌ
	// ポケモンの みちに おわりは ないんだｐ
	// まだ あしを ふみいれていない くさむらはｎ
	// いつまでも きみを まっているよ!

LittlerootTown_ProfessorBirchsLab_Text_MayTakeBreakFromFieldwork: @ 81FB528
	.string "봄이: 그럼 필드워크는\n"
	.string "조금 미뤄두고\p"
	.string "당분간은 여기서\n"
	.string "박사님을 도와드려야겠네-$"
	// ハルカ『さ-て フィ-ルドワ-クはｎ
	// ちょっとだけ おやすみしてｐ
	// しばらくは ここでｎ
	// はかせの おてつだいでも しよっかな-

LittlerootTown_ProfessorBirchsLab_Text_BrendanTakeBreakFromFieldwork: @ 81FB58A
	.string "휘웅: 나는 일단\n"
	.string "필드워크를 미뤄둘 거야!\p"
	.string "당분간은 여기서\n"
	.string "박사님을 도와드리려고!$"
	// ユウキ『オレは とりあえずｎ
	// フィ-ルドワ-クは おやすみだな!ｐ
	// しばらくは ここでｎ
	// はかせの てつだいでも してるよ!

LittlerootTown_ProfessorBirchsLab_Text_CompletedDexChoosePokemon: @ 81FB5F9
	.string "털보박사: 오오 {PLAYER}{K_AYA}!\n"
	.string "잠깐 도감 좀 보여주려무나\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "...음 역시 틀림없어!\n"
	.string "너는 정말로 호연지방의\l"
	.string "도감을 완성시킨 거야!\p"
	.string "이야- 대단하구나!\p"
	.string "너의 그 굉장한 업적에\n"
	.string "감사의 마음을 담아\l"
	.string "내가 선물을 주도록 하마!\p"
	.string "그건...\p"
	.string "다른 지방에서만 볼 수 있는\n"
	.string "희귀한 포켓몬이란다!\p"
	.string "3마리 중에서\n"
	.string "마음에 드는 1마리를 줄게!$"
	// オダマキ『おお §あ§お!ｎ
	// ちょっと ずかんを みせて もらうよｐ
	// …… …… ……ｎ
	// …… …… ……ｐ
	// ……うむ やはり まちがいない!ｎ
	// キミは ほんとうに ホウエンちほうのｌ
	// ずかんを かんせい させたんだな!ｐ
	// いや- たいしたもんだ!ｐ
	// きみの その すばらしい はたらきにｎ
	// かんしゃの きもちを こめてｌ
	// わたしから プレゼントを おくろう!ｐ
	// それは……ｐ
	// ほかの ちほうでしか みつからないｎ
	// めずらしい ポケモンだよ!ｐ
	// 3ひきの なかからｎ
	// すきなものを 1ひきだけ あげよう!

LittlerootTown_ProfessorBirchsLab_Text_CanHaveAnyOneOfRarePokemon: @ 81FB787
	.string "털보박사: 다른 지방에서만\n"
	.string "볼 수 있는 희귀한 포켓몬이란다!\p"
	.string "3마리 중에서\n"
	.string "마음에 드는 1마리를 줄게!$"
	// オダマキ『ほかの ちほうでしかｎ
	// みつからない めずらしい ポケモンだよ!ｐ
	// 3ひきの なかからｎ
	// すきなものを 1ひきだけ あげよう!

LittlerootTown_ProfessorBirchsLab_Text_YoullTakeCyndaquil: @ 81FB7F6
	.string "털보박사: 불꽃의 포켓몬 브케인이\n"
	.string "마음에 들다니 역시 감이 좋구나!\p"
	.string "그럼 브케인으로 괜찮겠니?$"
	// オダマキ『ほのおの ポケモン ヒノアラシにｎ
	// めを つけるとは やはり するどいな!ｐ
	// じゃあ ヒノアラシで いいんだね?

LittlerootTown_ProfessorBirchsLab_Text_YoullTakeTotodile: @ 81FB869
	.string "털보박사: 물의 포켓몬 리아코인가\n"
	.string "으-음 좋은 선택이구나!\p"
	.string "좋아 리아코로 괜찮겠니?$"
	// オダマキ『みずの ポケモン ワニノコかｎ
	// う-む いいものを えらぶじゃないか!ｐ
	// よし ワニノコで いいんだね?

LittlerootTown_ProfessorBirchsLab_Text_YoullTakeChikorita: @ 81FB8E0
	.string "털보박사: 풀의 포켓몬 치코리타인가\n"
	.string "역시 뭘 좀 아는구나!\p"
	.string "그렇다면 치코리타로 결정한 거니?$"
	// オダマキ『くさの ポケモン チコリ-タかｎ
	// さすがだ わかってるなあ!ｐ
	// ならば チコリ-タで けっていだね?

LittlerootTown_ProfessorBirchsLab_Text_TakeYourTimeAllInvaluable: @ 81FB959
	.string "털보박사: 천천히 생각하고\n"
	.string "고르도록 하렴\p"
	.string "모두 귀중한 포켓몬이니까$"
	// オダマキ『じっくり かんがえてｎ
	// きめると いいよｌ
	// どれも きちょうな ポケモン だからね

@ Unused
LittlerootTown_ProfessorBirchsLab_Text_PickedFinePokemon: @ 81FB9A8
	.string "털보박사: 과연!\n"
	.string "좋은 포켓몬을 골랐구나!$"
	// オダマキ『なるほど!ｎ
	// いい ポケモンを えらんだね!

LittlerootTown_ProfessorBirchsLab_Text_ReceivedJohtoStarter: @ 81FB9D7
	.string "{PLAYER}{K_EUNNEUN} 털보박사에게서\n"
	.string "{STR_VAR_1}{K_EULREUL} 받았다!$"
	// §あは オダマキはかせ からｎ
	// §いを もらった!

@ Unused
LittlerootTown_ProfessorBirchsLab_Text_NicknameJohtoStarter: @ 81FB9FC
	.string "받은 {STR_VAR_1}에게\n"
	.string "닉네임을 붙이겠습니까?$"
	// もらった §いにｎ
	// ニックネ-ムを つけますか?

LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting: @ 81FBA2C
	.string "털보박사: {PLAYER}{K_AYA} 알겠니?\n"
	.string "호연도감을 완성했어도\l"
	.string "포켓몬의 길은 끝난 게 아니란다\p"
	.string "아직 발을 내딛지 않은 풀숲은\n"
	.string "언제까지나 널 기다리고 있지!$"
	// オダマキ『§あ§お いいかい?ｎ
	// ホウエンの ずかんが かんせい してもｌ
	// ポケモンの みちに おわりは ないんだｐ
	// まだ あしを ふみいれていない くさむらはｎ
	// いつまでも きみを まっているよ!

LittlerootTown_ProfessorBirchsLab_Text_BetterLeaveOthersAlone: @ 81FBAF8
	.string "약속한 1마리는 이미 받았으니까\n"
	.string "남은 건 건드리지 말자!$"
	// やくそくの 1ひきは もう もらったからｎ
	// のこりには さわらないで おこう!

@ Unused
LittlerootTown_ProfessorBirchsLab_Text_DontHaveAnyRoomForPokemon: @ 81FBB3A
	.string "으음? 그 이상\n"
	.string "포켓몬을 지닐 수가 없구나$"
	// おや? それいじょうｎ
	// ポケモンを もてない みたいだな

LittlerootTown_ProfessorBirchsLab_Text_MayWhatNextImStayingHere: @ 81FBB68
	.string "봄이: {PLAYER}{K_EUNNEUN}\n"
	.string "이제... 뭘 할 거야?\p"
	.string "포켓몬 승부의 길을 나아갈 거야?\p"
	.string "아니면 전국도감의\n"
	.string "완성을 노릴 거야?\p"
	.string "나는 여기서\n"
	.string "박사님을 계속 도와드리려고$"
	// ハルカ『§あ§おはｎ
	// このあと…… どうする つもり?ｐ
	// ポケモン しょうぶの みちを きわめる?ｐ
	// それとも ぜんこく ずかんのｎ
	// かんせいを めざすの?ｐ
	// あたしは ここでｎ
	// はかせの おてつだいを つづけるわ

LittlerootTown_ProfessorBirchsLab_Text_BrendanPreferCollectingSlowly: @ 81FBC2D
	.string "휘웅: 나는 포켓몬을 모으는 것보다\n"
	.string "이거다! 라는 생각이 드는 1마리를\l"
	.string "차분히 키우는 게 좋아!$"
	// ユウキ『オレは ポケモン あつめるよりｎ
	// これは! と おもった 1ひきをｌ
	// じっくり そだてるのが すきなのさ!

LittlerootTown_ProfessorBirchsLab_Text_MayHaveYouGoneToBattleFrontier: @ 81FBC8D
	.string "봄이: 앗 {PLAYER}{K_AYA}!\n"
	.string "배틀프런티어라는 곳은\l"
	.string "이미 가봤어?$"
	// ハルカ『あっ §あ§お!ｎ
	// バトルフロンティア っていう ところにはｌ
	// もう いってみた?

LittlerootTown_ProfessorBirchsLab_Text_BrendanHaveYouGoneToBattleFrontier: @ 81FBCD2
	.string "휘웅: 여어 {PLAYER}{K_AYA}!\n"
	.string "배틀프런티어라는 곳은\l"
	.string "이미 가본 거야?$"
	// ユウキ『やあ §あか!ｎ
	// バトルフロンティア って ところにはｌ
	// もう いってみたか?

LittlerootTown_ProfessorBirchsLab_Text_ScottAboardSSTidalCall: @ 81FBD1A
	.string "...... ...... ......\n"
	.string "...... ...... ...... 삑!\p"
	.string "금작화: 여어 {PLAYER}{K_AYA}!\n"
	.string "나야 금작화!\p"
	.string "지금 타이드립호에 타고 있는데\n"
	.string "역시 바다는 기분이 좋네-\p"
	.string "그건 그렇고...\p"
	.string "너를 초대하고 싶은 장소가\n"
	.string "있는데 어때?\p"
	.string "만약 흥미가 있다면\n"
	.string "잿빛도시나 해안시티의 배 타는 곳에서\l"
	.string "배에 타 줘!\p"
	.string "자세한 건 만나고 나서 알려줄게\n"
	.string "그럼 나중에 보자!\p"
	.string "...... ...... ......\n"
	.string "...... ...... ...... 삐-$"
	// …… …… ……ｎ
	// …… …… …… ピッ!ｐ
	// エニシダ『やあやあ §あ§お!ｎ
	// わたしだよ エニシダだよ!ｐ
	// いま タイドリップごうに のってるんだけどｎ
	// やっぱり うみは きもちが いいねえ-ｐ
	// ところで……ｐ
	// きみを しょうたい したい ばしょがｎ
	// あるんだけど どうだい?ｐ
	// もし きょうみが あるならｎ
	// カイナか ミナモの ふねのりばからｌ
	// ふねに のっておくれ!ｐ
	// くわしいことは あったときに おしえようｎ
	// じゃあな まってるぞ!ｐ
	// …… …… ……ｎ
	// …… …… …… ツ-
