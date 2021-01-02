.set LOCALID_NORMAN, 1
.set LOCALID_WALLY, 10
.set LOCALID_WALLYS_DAD, 11

PetalburgCity_Gym_MapScripts:: @ 8204889
	map_script MAP_SCRIPT_ON_LOAD, PetalburgCity_Gym_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_Gym_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_Gym_OnFrame
	.byte 0

PetalburgCity_Gym_OnLoad: @ 820489E
	compare VAR_PETALBURG_GYM_STATE, 6
	goto_if_eq PetalburgCity_Gym_EventScript_OpenUnlockedDoors
	compare VAR_PETALBURG_GYM_STATE, 7
	call_if_ge PetalburgCity_Gym_EventScript_UnlockAllDoors
	end

@ NOTE: Strength and OHKO rooms are misleading. Both are more accurately Critical-Hit
PetalburgCity_Gym_EventScript_OpenUnlockedDoors:: @ 82048B5
	setvar VAR_0x8005, 1
	call PetalburgCity_Gym_EventScript_OpenGymEntranceDoors
	call_if_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors
	call_if_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors
	call_if_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	call_if_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	call_if_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	call_if_defeated TRAINER_JODY, PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors
	call_if_defeated TRAINER_BERKE, PetalburgCity_Gym_EventScript_OpenOHKORoomDoors
	end

PetalburgCity_Gym_EventScript_UnlockAllDoors:: @ 82048FF
	setvar VAR_0x8005, 1
	call PetalburgCity_Gym_EventScript_OpenGymEntranceDoors
	call PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors
	call PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors
	call PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	call PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	call PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	call PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors
	call PetalburgCity_Gym_EventScript_OpenOHKORoomDoors
	return

PetalburgCity_Gym_OnTransition: @ 820492D
	compare VAR_PETALBURG_GYM_STATE, 1
	call_if_eq PetalburgCity_Gym_EventScript_MoveWallyToEntrance
	compare VAR_PETALBURG_GYM_STATE, 6
	call_if_lt PetalburgCity_Gym_EventScript_MoveNormanToEntrance
	call_if_set FLAG_SYS_GAME_CLEAR, PetalburgCity_Gym_EventScript_CheckNormanForRematch
	end

PetalburgCity_Gym_EventScript_MoveWallyToEntrance:: @ 820494D
	setobjectxyperm LOCALID_WALLY, 5, 108
	return

PetalburgCity_Gym_EventScript_MoveNormanToEntrance:: @ 8204955
	setobjectxyperm LOCALID_NORMAN, 4, 107
	return

PetalburgCity_Gym_EventScript_CheckNormanForRematch:: @ 820495D
	setorcopyvar VAR_TRAINER_BATTLE_OPPONENT_A, TRAINER_NORMAN_1
	specialvar VAR_RESULT, IsTrainerReadyForRematch
	compare VAR_RESULT, TRUE
	goto_if_eq PetalburgCity_Gym_EventScript_DontMoveNormanToFront
	compare VAR_PETALBURG_GYM_STATE, 8
	goto_if_eq PetalburgCity_Gym_EventScript_DontMoveNormanToFront
	setobjectxyperm LOCALID_NORMAN, 4, 107
	return

PetalburgCity_Gym_EventScript_DontMoveNormanToFront:: @ 8204985
	setvar VAR_PETALBURG_GYM_STATE, 8
	end

PetalburgCity_Gym_OnWarp: @ 820498B
	map_script_2 VAR_PETALBURG_GYM_STATE, 1, PetalburgCity_Gym_EventScript_TurnPlayerNorth
	.2byte 0

PetalburgCity_Gym_EventScript_TurnPlayerNorth:: @ 8204995
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

PetalburgCity_Gym_OnFrame: @ 820499A
	map_script_2 VAR_PETALBURG_GYM_STATE, 1, PetalburgCity_Gym_EventScript_ReturnFromWallyTutorial
	.2byte 0

PetalburgCity_Gym_EventScript_ReturnFromWallyTutorial:: @ 82049A4
	lockall
	msgbox PetalburgCity_Gym_Text_DadSoDidItWorkOut, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_WallyThankYouBye, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitGym
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_WALLY
	setflag FLAG_HIDE_PETALBURG_CITY_WALLY
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox PetalburgCity_Gym_Text_DadGoCollectBadges, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_GYM_STATE, 2
	releaseall
	end

PetalburgCity_Gym_Movement_WallyExitGym: @ 82049EC
	walk_down
	walk_down
	walk_down
	delay_16
	step_end

PetalburgCity_Gym_EventScript_Norman:: @ 82049F1
	lock
	faceplayer
	switch VAR_PETALBURG_GYM_STATE
	case 2, PetalburgCity_Gym_EventScript_NormanNoBadges
	case 3, PetalburgCity_Gym_EventScript_NormanOneBadge
	case 4, PetalburgCity_Gym_EventScript_NormanTwoBadges
	case 5, PetalburgCity_Gym_EventScript_NormanThreeBadges
	case 6, PetalburgCity_Gym_EventScript_NormanBattle
	case 7, PetalburgCity_Gym_EventScript_NormanPostBattle
	case 8, PetalburgCity_Gym_EventScript_NormanRematch
	msgbox PetalburgCity_Gym_Text_DadYoureHereWithYourPokemon, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, PetalburgCity_Gym_EventScript_BeginWallyTutorialSouth
	case DIR_NORTH, PetalburgCity_Gym_EventScript_BeginWallyTutorialNorth
	case DIR_WEST, PetalburgCity_Gym_EventScript_BeginWallyTutorialWest
	case DIR_EAST, PetalburgCity_Gym_EventScript_BeginWallyTutorialEast
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorialSouth:: @ 8204A80
	setvar VAR_0x8008, 0
	goto PetalburgCity_Gym_EventScript_BeginWallyTutorial
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorialNorth:: @ 8204A8B
	setvar VAR_0x8008, 1
	goto PetalburgCity_Gym_EventScript_BeginWallyTutorial
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorialWest:: @ 8204A96
	setvar VAR_0x8008, 2
	goto PetalburgCity_Gym_EventScript_BeginWallyTutorial
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorialEast:: @ 8204AA1
	setvar VAR_0x8008, 3
	goto PetalburgCity_Gym_EventScript_BeginWallyTutorial
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorial:: @ 8204AAC
	addobject LOCALID_WALLY
	playse SE_DOOR
	compare VAR_0x8008, 0
	call_if_eq PetalburgCity_Gym_EventScript_WallyArriveSouth
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_WallyArriveNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_WallyArriveWestEast
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_WallyArriveWestEast
	msgbox PetalburgCity_Gym_Text_WallyIdLikeAPokemon, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_DadOhYoureWallyRight, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_WallyIveNeverCaughtAPokemon, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_DadHmISee, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq PetalburgCity_Gym_EventScript_NormanAddressPlayerSouth
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_NormanAddressPlayerNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_NormanAddressPlayerWest
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_NormanAddressPlayerEast
	msgbox PetalburgCity_Gym_Text_DadPlayerGoWithWally, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq PetalburgCity_Gym_EventScript_NormanAddressWallySouth
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_NormanAddressWallyNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_NormanAddressWallyWest
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_NormanAddressWallyEast
	msgbox PetalburgCity_Gym_Text_IllLoanYouMyZigzagoon, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_WallyThankYouAndDadGivesPokeBall, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_WallyOhWowThankYou, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq PetalburgCity_Gym_EventScript_NormanFaceDoorSouth
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_NormanFaceDoorNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_NormanFaceDoorWest
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_NormanFaceDoorEast
	compare VAR_0x8008, 0
	call_if_eq PetalburgCity_Gym_EventScript_WallyFacePlayer
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_WallyFaceDown
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_WallyFacePlayer
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_WallyFacePlayer
	msgbox PetalburgCity_Gym_Text_WouldYouReallyComeWithMe, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_DONT_TRANSITION_MUSIC
	playbgm MUS_FOLLOW_ME, 0
	compare VAR_0x8008, 0
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallySouth
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallyNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallyWest
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallyEast
	removeobject LOCALID_WALLY
	setflag FLAG_HIDE_PETALBURG_CITY_WALLYS_MOM
	setvar VAR_PETALBURG_GYM_STATE, 1
	setvar VAR_PETALBURG_CITY_STATE, 2
	clearflag FLAG_HIDE_PETALBURG_CITY_WALLY
	clearflag FLAG_HIDE_PETALBURG_GYM_WALLY
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	special InitBirchState
	warp MAP_PETALBURG_CITY, 255, 15, 8
	waitstate
	release
	end

PetalburgCity_Gym_EventScript_WallyArriveSouth:: @ 8204C31
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestDown
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyArrive
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallyArriveNorth:: @ 8204C43
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyArriveNorth
	waitmovement 0
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallyArriveWestEast:: @ 8204C5F
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestDown
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyArrive
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallySouth:: @ 8204C78
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestDown
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitSouthWest
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallySouth
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallyNorth:: @ 8204C91
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitNorth
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallyNorth
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallyWest:: @ 8204CA3
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitSouthWest
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallyWest
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallyEast:: @ 8204CB5
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitEast
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallyEast
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressPlayerSouth:: @ 8204CC7
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressPlayerNorth:: @ 8204CD2
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestDown
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressPlayerWest:: @ 8204CE4
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressPlayerEast:: @ 8204CF6
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestLeft
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressWallySouth:: @ 8204D08
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressWallyNorth:: @ 8204D13
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressWallyWest:: @ 8204D1E
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanAddressWallyEast:: @ 8204D29
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallyFacePlayer:: @ 8204D34
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallyFaceDown:: @ 8204D3F
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanNoBadges:: @ 8204D4A
	msgbox PetalburgCity_Gym_Text_NormanGoToRustboro, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_NormanOneBadge:: @ 8204D54
	msgbox PetalburgCity_Gym_Text_NormanGoToDewford, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_NormanTwoBadges:: @ 8204D5E
	msgbox PetalburgCity_Gym_Text_YouHaveGottenStronger, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_NormanThreeBadges:: @ 8204D68
	msgbox PetalburgCity_Gym_Text_YouHaveGottenStronger, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_NormanFaceDoorSouth:: @ 8204D72
	return

@ For all other NormanFaceDoorX, Norman is already facing the door from NormanAddressWallyX
PetalburgCity_Gym_EventScript_NormanFaceDoorNorth:: @ 8204D73
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_NormanFaceDoorWest:: @ 8204D7E
	return

PetalburgCity_Gym_EventScript_NormanFaceDoorEast:: @ 8204D7F
	return

PetalburgCity_Gym_EventScript_NormanPostBattle:: @ 8204D80
	call PetalburgCity_Gym_EventScript_ShouldGiveEnigmaBerry
	compare VAR_RESULT, TRUE
	goto_if_eq PetalburgCity_Gym_EventScript_GiveEnigmaBerry
	goto_if_unset FLAG_RECEIVED_TM42, PetalburgCity_Gym_EventScript_GiveFacade2
	goto_if_set FLAG_SYS_GAME_CLEAR, PetalburgCity_Gym_EventScript_NoAmountOfTrainingIsEnough
	msgbox PetalburgCity_Gym_Text_DadGoingToKeepTraining, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_GiveFacade2:: @ 8204DAC
	call PetalburgCity_Gym_EventScript_GiveFacade
	release
	end

PetalburgCity_Gym_EventScript_NormanRematch:: @ 8204DB3
	trainerbattle_rematch_double TRAINER_NORMAN_1, PetalburgCity_Gym_Text_NormanPreRematch, PetalburgCity_Gym_Text_NormanRematchDefeat, PetalburgCity_Gym_Text_NormanRematchNeedTwoMons
	msgbox PetalburgCity_Gym_Text_NormanPostRematch, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_ShouldGiveEnigmaBerry:: @ 8204DCE
	specialvar VAR_RESULT, IsEnigmaBerryValid
	compare VAR_RESULT, FALSE
	goto_if_eq PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry
	checkitem ITEM_ENIGMA_BERRY, 1
	compare VAR_RESULT, TRUE
	goto_if_eq PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry
	checkpcitem ITEM_ENIGMA_BERRY, 1
	compare VAR_RESULT, TRUE
	goto_if_eq PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry
	compare VAR_ENIGMA_BERRY_AVAILABLE, 0
	goto_if_eq PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry
	msgbox PetalburgCity_Gym_Text_GiveEnigmaBerry, MSGBOX_DEFAULT
	setvar VAR_RESULT, TRUE
	return

PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry:: @ 8204E17
	setvar VAR_RESULT, FALSE
	return

PetalburgCity_Gym_EventScript_GiveEnigmaBerry:: @ 8204E1D
	giveitem ITEM_ENIGMA_BERRY
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setvar VAR_ENIGMA_BERRY_AVAILABLE, 0
	release
	end

PetalburgCity_Gym_EventScript_NormanBattle:: @ 8204E3B
	msgbox PetalburgCity_Gym_Text_NormanIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_NORMAN_1, PetalburgCity_Gym_Text_NormanDefeat
	message PetalburgCity_Gym_Text_ReceivedBalanceBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox PetalburgCity_Gym_Text_ExplainBalanceBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_PETALBURG_GYM
	setvar VAR_PETALBURG_GYM_STATE, 7
	setflag FLAG_BADGE05_GET
	special ResetHealLocationFromDewford
	call EventScript_HideMrBriney
	setflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	clearflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setvar VAR_0x8008, 5
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_DEWFORD_HALL_SLUDGE_BOMB_MAN
	call PetalburgCity_Gym_EventScript_UnlockAllDoors
	special DrawWholeMapView
	call PetalburgCity_Gym_EventScript_GiveFacade
	delay 30
	msgbox PetalburgCity_Gym_Text_DadHappyAndSad, MSGBOX_DEFAULT
	closemessage
	delay 40
	playse SE_DOOR
	delay 10
	addobject LOCALID_WALLYS_DAD
	switch VAR_FACING
	case DIR_NORTH, PetalburgCity_Gym_EventScript_WallysDadArrivesNorth
	case DIR_WEST, PetalburgCity_Gym_EventScript_WallysDadArrivesWest
	case DIR_EAST, PetalburgCity_Gym_EventScript_WallysDadArrivesEast
	end

PetalburgCity_Gym_EventScript_GiveFacade:: @ 8204ED2
	giveitem ITEM_TM42
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_BagIsFull
	setflag FLAG_RECEIVED_TM42
	msgbox PetalburgCity_Gym_Text_ExplainFacade, MSGBOX_DEFAULT
	return

PetalburgCity_Gym_EventScript_WallysDadArrivesNorth:: @ 8204EF5
	setvar VAR_0x8008, 1
	goto PetalburgCity_Gym_EventScript_WallysDadArrives

PetalburgCity_Gym_EventScript_WallysDadArrivesEast:: @ 8204EFF
	setvar VAR_0x8008, 2
	goto PetalburgCity_Gym_EventScript_WallysDadArrives

PetalburgCity_Gym_EventScript_WallysDadArrivesWest:: @ 8204F09
	setvar VAR_0x8008, 3
	goto PetalburgCity_Gym_EventScript_WallysDadArrives

PetalburgCity_Gym_EventScript_WallysDadArrives:: @ 8204F13
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadEnterGym
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WALLYS_DAD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLYS_DAD, Common_Movement_Delay48
	waitmovement 0
	delay 10
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_WallysDadApproachPlayerNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_WallysDadApproachPlayerEast
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_WallysDadApproachPlayerWest
	msgbox PetalburgCity_Gym_Text_PleaseComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 20
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_WallysDadFaceNormanNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_WallysDadFaceNormanEast
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_WallysDadFaceNormanWest
	msgbox PetalburgCity_Gym_Text_LetMeBorrowPlayer, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_DONT_TRANSITION_MUSIC
	playbgm MUS_FOLLOW_ME, 0
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallysDadNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallysDadEast
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallysDadWest
	removeobject LOCALID_WALLYS_DAD
	setvar VAR_PETALBURG_CITY_STATE, 4
	clearflag FLAG_HIDE_PETALBURG_CITY_WALLYS_DAD
	warp MAP_PETALBURG_CITY, 255, 15, 8
	waitstate
	release
	end

PetalburgCity_Gym_EventScript_WallysDadFaceNormanNorth:: @ 8204FCC
	applymovement LOCALID_WALLYS_DAD, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysDadFaceNormanEast:: @ 8204FD7
	applymovement LOCALID_WALLYS_DAD, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysDadFaceNormanWest:: @ 8204FE2
	applymovement LOCALID_WALLYS_DAD, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysDadApproachPlayerNorth:: @ 8204FED
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadApproachPlayerNorth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysDadApproachPlayerEast:: @ 8205009
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadApproachPlayerEast
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysDadApproachPlayerWest:: @ 8205025
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadApproachPlayerWest
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallysDadNorth:: @ 8205041
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadExitNorth
	applymovement LOCALID_NORMAN, Common_Movement_WalkInPlaceFastestDown
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallysDadNorth
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallysDadEast:: @ 820505A
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadExitEast
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallysDadEast
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallysDadWest:: @ 820506C
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Gym_Movement_WallysDadExitWest
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallysDadWest
	waitmovement 0
	return

PetalburgCity_Gym_Movement_WallysDadExitNorth: @ 820507E
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_fastest_up
	delay_8
	walk_in_place_down
	set_invisible
	step_end

PetalburgCity_Gym_Movement_WallysDadExitEast: @ 8205089
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_fastest_up
	delay_8
	walk_in_place_down
	set_invisible
	step_end

PetalburgCity_Gym_Movement_WallysDadExitWest: @ 8205094
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_fastest_up
	delay_8
	walk_in_place_down
	set_invisible
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallysDadNorth: @ 82050A1
	delay_16
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallysDadEast: @ 82050A9
	delay_16
	walk_down
	walk_down
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallysDadWest: @ 82050B1
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

PetalburgCity_Gym_Movement_WallysDadEnterGym: @ 82050BB
	walk_up
	delay_8
	walk_in_place_fastest_right
	delay_8
	walk_in_place_fastest_left
	delay_16
	walk_in_place_fastest_up
	step_end

PetalburgCity_Gym_Movement_WallysDadApproachPlayerNorth: @ 82050C3
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_right
	step_end

PetalburgCity_Gym_Movement_WallysDadApproachPlayerEast: @ 82050CA
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

PetalburgCity_Gym_Movement_WallysDadApproachPlayerWest: @ 82050D0
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	step_end

PetalburgCity_Gym_Movement_Unused: @ 82050D8
	walk_in_place_fastest_up
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_fastest_down
	step_end

PetalburgCity_Gym_Movement_WallyArriveNorth: @ 82050E1
	delay_16
	walk_up
	delay_16
	delay_8
	walk_up
	walk_right
	walk_up
	walk_up
	walk_in_place_fastest_left
	step_end

PetalburgCity_Gym_Movement_WallyArrive: @ 82050EB
	delay_16
	walk_up
	delay_16
	delay_8
	walk_up
	walk_up
	step_end

PetalburgCity_Gym_Movement_WallyExitNorth: @ 82050F2
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_up
	delay_16
	walk_in_place_down
	step_end

PetalburgCity_Gym_Movement_WallyExitEast: @ 82050FA
	walk_down
	walk_down
	walk_right
	walk_down
	walk_in_place_fastest_up
	delay_16
	walk_in_place_down
	step_end

PetalburgCity_Gym_Movement_WallyExitSouthWest: @ 8205102
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_up
	delay_16
	walk_in_place_down
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallyNorth: @ 8205109
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallySouth: @ 8205111
	delay_16
	delay_16
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallyWest: @ 820511B
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallyEast: @ 8205123
	walk_in_place_fastest_down
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_right
	walk_down
	delay_8
	step_end

PetalburgCity_Gym_EventScript_NoAmountOfTrainingIsEnough:: @ 820512D
	msgbox PetalburgCity_Gym_Text_DadNoAmountOfTrainingIsEnough, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_SpeedRoomDoor:: @ 8205137
	lockall
	compare VAR_PETALBURG_GYM_STATE, 6
	goto_if_lt PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 85
	msgbox PetalburgCity_Gym_Text_EnterSpeedRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_EnterRoom:: @ 820516C
	closemessage
	delay 30
	warpdoor MAP_PETALBURG_CITY_GYM, 255, VAR_0x8008, VAR_0x8009
	waitstate
	releaseall
	end

PetalburgCity_Gym_EventScript_DontEnterRoom:: @ 820517B
	releaseall
	end

PetalburgCity_Gym_EventScript_DoorLocked:: @ 820517D
	msgbox PetalburgCity_Gym_Text_DoorAppearsLocked, MSGBOX_DEFAULT
	releaseall
	end

@ VAR_0x8008 and VAR_0x8009 below are the x and y coordinates of the warp
PetalburgCity_Gym_EventScript_AccuracyRoomDoor:: @ 8205187
	lockall
	compare VAR_PETALBURG_GYM_STATE, 6
	goto_if_lt PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 98
	msgbox PetalburgCity_Gym_Text_EnterAccuracyRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_ConfusionRoomDoor:: @ 82051BC
	lockall
	goto_if_not_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 46
	msgbox PetalburgCity_Gym_Text_EnterConfusionRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftDefenseRoomDoor:: @ 82051EF
	lockall
	goto_if_not_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 59
	msgbox PetalburgCity_Gym_Text_EnterDefenseRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightDefenseRoomDoor:: @ 8205222
	lockall
	goto_if_not_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 59
	msgbox PetalburgCity_Gym_Text_EnterDefenseRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RecoveryRoomDoor:: @ 8205255
	lockall
	goto_if_not_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 72
	msgbox PetalburgCity_Gym_Text_EnterRecoveryRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftStrengthRoomDoor:: @ 8205288
	lockall
	goto_if_not_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 20
	msgbox PetalburgCity_Gym_Text_EnterStrengthRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightStrengthRoomDoor:: @ 82052BB
	lockall
	goto_if_not_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 20
	msgbox PetalburgCity_Gym_Text_EnterStrengthRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftOHKORoomDoor:: @ 82052EE
	lockall
	goto_if_not_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 33
	msgbox PetalburgCity_Gym_Text_EnterOHKORoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightOHKORoomDoor:: @ 8205321
	lockall
	goto_if_not_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 33
	msgbox PetalburgCity_Gym_Text_EnterOHKORoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftGymLeadersRoomDoor:: @ 8205354
	lockall
	goto_if_not_defeated TRAINER_JODY, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 7
	msgbox PetalburgCity_Gym_Text_EnterGymLeadersRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightGymLeadersRoomDoor:: @ 8205387
	lockall
	goto_if_not_defeated TRAINER_BERKE, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 7
	msgbox PetalburgCity_Gym_Text_EnterGymLeadersRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_Randall:: @ 82053BA
	trainerbattle_single TRAINER_RANDALL, PetalburgCity_Gym_Text_RandallIntro, PetalburgCity_Gym_Text_RandallDefeat, PetalburgCity_Gym_EventScript_SlideOpenSpeedRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_RandallPostBadge
	msgbox PetalburgCity_Gym_Text_RandallPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenSpeedRoomDoors:: @ 82053DE
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_RandallPostBadge:: @ 82053ED
	msgbox PetalburgCity_Gym_Text_RandallPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Parker:: @ 82053F6
	trainerbattle_single TRAINER_PARKER, PetalburgCity_Gym_Text_ParkerIntro, PetalburgCity_Gym_Text_ParkerDefeat, PetalburgCity_Gym_EventScript_SlideOpenConfusionRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_ParkerPostBadge
	msgbox PetalburgCity_Gym_Text_ParkerPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenConfusionRoomDoors:: @ 820541A
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_ParkerPostBadge:: @ 8205429
	msgbox PetalburgCity_Gym_Text_ParkerPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_George:: @ 8205432
	trainerbattle_single TRAINER_GEORGE, PetalburgCity_Gym_Text_GeorgeIntro, PetalburgCity_Gym_Text_GeorgeDefeat, PetalburgCity_Gym_EventScript_SlideOpenRecoveryRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_GeorgePostBadge
	msgbox PetalburgCity_Gym_Text_GeorgePostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenRecoveryRoomDoors:: @ 8205456
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_GeorgePostBadge:: @ 8205465
	msgbox PetalburgCity_Gym_Text_GeorgePostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Berke:: @ 820546E
	trainerbattle_single TRAINER_BERKE, PetalburgCity_Gym_Text_BerkeIntro, PetalburgCity_Gym_Text_BerkeDefeat, PetalburgCity_Gym_EventScript_SlideOpenOHKORoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_BerkePostBadge
	msgbox PetalburgCity_Gym_Text_BerkePostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenOHKORoomDoors:: @ 8205492
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenOHKORoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_BerkePostBadge:: @ 82054A1
	msgbox PetalburgCity_Gym_Text_BerkePostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Mary:: @ 82054AA
	trainerbattle_single TRAINER_MARY, PetalburgCity_Gym_Text_MaryIntro, PetalburgCity_Gym_Text_MaryDefeat, PetalburgCity_Gym_EventScript_SlideOpenAccuracyRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_MaryPostBadge
	msgbox PetalburgCity_Gym_Text_MaryPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenAccuracyRoomDoors:: @ 82054CE
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_MaryPostBadge:: @ 82054DD
	msgbox PetalburgCity_Gym_Text_MaryPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Alexia:: @ 82054E6
	trainerbattle_single TRAINER_ALEXIA, PetalburgCity_Gym_Text_AlexiaIntro, PetalburgCity_Gym_Text_AlexiaDefeat, PetalburgCity_Gym_EventScript_SlideOpenDefenseRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_AlexiaPostBadge
	msgbox PetalburgCity_Gym_Text_AlexiaPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenDefenseRoomDoors:: @ 820550A
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_AlexiaPostBadge:: @ 8205519
	msgbox PetalburgCity_Gym_Text_AlexiaPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Jody:: @ 8205522
	trainerbattle_single TRAINER_JODY, PetalburgCity_Gym_Text_JodyIntro, PetalburgCity_Gym_Text_JodyDefeat, PetalburgCity_Gym_EventScript_SlideOpenStrengthRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_JodyPostBadge
	msgbox PetalburgCity_Gym_Text_JodyPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenStrengthRoomDoors:: @ 8205546
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_JodyPostBadge:: @ 8205555
	msgbox PetalburgCity_Gym_Text_JodyPostBadge, MSGBOX_NPC
	end

@ VAR_0x8004 below is the room number
@ VAR_0x8005 below is 0 when the door should be slid open and 1 when it should be unlocked immediately
PetalburgCity_Gym_EventScript_OpenGymEntranceDoors:: @ 820555E
	setvar VAR_0x8004, 1
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetEntranceRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors:: @ 820557F
	setvar VAR_0x8004, 2
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetSpeedRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors:: @ 82055A0
	setvar VAR_0x8004, 3
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetAccuracyRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors:: @ 82055C1
	setvar VAR_0x8004, 4
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetConfusionRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors:: @ 82055E2
	setvar VAR_0x8004, 5
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetDefenseRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors:: @ 8205603
	setvar VAR_0x8004, 6
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetRecoveryRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors:: @ 8205624
	setvar VAR_0x8004, 7
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetStrengthRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenOHKORoomDoors:: @ 8205645
	setvar VAR_0x8004, 8
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetOHKORoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_SetEntranceRoomDoorMetatiles:: @ 8205666
	setmetatile 6, 85, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 7, 85, METATILE_PetalburgGym_RoomEntrance_Right, 0
	setmetatile 1, 98, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 2, 98, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetSpeedRoomDoorMetatiles:: @ 820568B
	setmetatile 6, 46, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 7, 46, METATILE_PetalburgGym_RoomEntrance_Right, 0
	setmetatile 1, 59, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 2, 59, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetAccuracyRoomDoorMetatiles:: @ 82056B0
	setmetatile 6, 59, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 7, 59, METATILE_PetalburgGym_RoomEntrance_Right, 0
	setmetatile 1, 72, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 2, 72, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetConfusionRoomDoorMetatiles:: @ 82056D5
	setmetatile 1, 20, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 2, 20, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetDefenseRoomDoorMetatiles:: @ 82056E8
	setmetatile 6, 20, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 7, 20, METATILE_PetalburgGym_RoomEntrance_Right, 0
	setmetatile 1, 33, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 2, 33, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetRecoveryRoomDoorMetatiles:: @ 820570D
	setmetatile 6, 33, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 7, 33, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetStrengthRoomDoorMetatiles:: @ 8205720
	setmetatile 1, 7, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 2, 7, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetOHKORoomDoorMetatiles:: @ 8205733
	setmetatile 6, 7, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 7, 7, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SlideOpenRoomDoors:: @ 8205746
	special PetalburgGymSlideOpenRoomDoors
	waitstate
	return

PetalburgCity_Gym_EventScript_UnlockRoomDoors:: @ 820574B
	special PetalburgGymUnlockRoomDoors
	return

PetalburgCity_Gym_EventScript_GymGuide:: @ 820574F
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_GymGuidePostVictory
	msgbox PetalburgCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_GymGuidePostVictory:: @ 8205764
	msgbox PetalburgCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_LeftGymStatue:: @ 820576E
	lockall
	goto_if_set FLAG_BADGE05_GET, PetalburgCity_Gym_EventScript_GymStatueCertified
	goto PetalburgCity_Gym_EventScript_GymStatue
	end

PetalburgCity_Gym_EventScript_RightGymStatue:: @ 820577E
	lockall
	goto_if_set FLAG_BADGE05_GET, PetalburgCity_Gym_EventScript_GymStatueCertified
	goto PetalburgCity_Gym_EventScript_GymStatue
	end

PetalburgCity_Gym_EventScript_GymStatueCertified:: @ 820578E
	msgbox PetalburgCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

PetalburgCity_Gym_EventScript_GymStatue:: @ 8205798
	msgbox PetalburgCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

PetalburgCity_Gym_Text_DadYoureHereWithYourPokemon: @ 82057A2
	.string "아빠: 응?\p"
	.string "{PLAYER}{K_I}잖아!\n"
	.string "그런가 이사가 다 끝났나 보구나\p"
	.string "그것보다\n"
	.string "여기까지 잘도 혼자 왔구나\p"
	.string "그렇군...\n"
	.string "포켓몬과 함께인 건가\p"
	.string "흠... 그럼 {PLAYER}{K_I}도\n"
	.string "나 같은\l"
	.string "포켓몬 트레이너가 되는 건가\p"
	.string "그거 기대되는걸!$"
	// パパ『ん?ｐ
	// §あじゃ ないか!ｎ
	// そうか ひっこしが おわったんだねｐ
	// それにしてもｎ
	// よく ここまで ひとりで これたなｐ
	// なるほど……ｎ
	// ポケモンと いっしょ なのかｐ
	// ふむ…… じゃあ §あもｎ
	// わたしの ようにｌ
	// ポケモントレ-ナ-に なるのかｐ
	// それは たのしみ だな!

PetalburgCity_Gym_Text_WallyIdLikeAPokemon: @ 82058B1
	.string "저기... 저...\n"
	.string "포켓몬이 가지고 싶은데요...$"
	// あの…… ぼく……ｎ
	// ポケモンが ほしいん ですけど……

PetalburgCity_Gym_Text_DadOhYoureWallyRight: @ 82058DB
	.string "아빠: 음? 너는... 아마\n"
	.string "민진이라고 했지$"
	// パパ『ん? きみは…… たしかｎ
	// ミツルくんと いったよね

PetalburgCity_Gym_Text_WallyIveNeverCaughtAPokemon: @ 8205910
	.string "민진: 전 오늘부터 잔디마을의\n"
	.string "친척 집에 가는데\p"
	.string "혼자서는 외로우니까 포켓몬을\n"
	.string "데려갈까 해서요...\p"
	.string "하지만 지금까지 스스로 포켓몬을\n"
	.string "잡아본 적이 없어서\l"
	.string "어떻게 해야 할지...$"
	// ミツル『ぼく きょうから シダケタウンのｎ
	// しんせきの うちに いくんですけどｐ
	// ひとりじゃ さみしいから ポケモンをｎ
	// つれて いこうかと おもって……ｐ
	// でも いままで じぶんで ポケモンをｎ
	// つかまえた ことが ないからｌ
	// どう やったら いいのか……

PetalburgCity_Gym_Text_DadHmISee: @ 82059D8
	.string "아빠: ...흠 그렇군$"
	// パパ『……ふむ なるほど

PetalburgCity_Gym_Text_DadPlayerGoWithWally: @ 82059E8
	.string "아빠: {PLAYER}!\n"
	.string "얘기는 들었겠지?\p"
	.string "민진군이 무사히\n"
	.string "포켓몬을 잡을 수 있도록\l"
	.string "잘 지켜봐 주도록 하거라$"
	// パパ『§あ! はなしは きいたねｐ
	// ミツルくんが ぶじにｎ
	// ポケモンを つかまえられるかｌ
	// みまもって あげるんだ

PetalburgCity_Gym_Text_IllLoanYouMyZigzagoon: @ 8205A46
	.string "민진군\n"
	.string "나의 포켓몬을 빌려주겠네!\p"
	.string "민진은\n"
	.string "지그제구리를 받았다!$"
	// ミツルくんｎ
	// わたしの ポケモンを かして あげよう!ｐ
	// ミツルはｎ
	// ジグザグマを あずかった!

PetalburgCity_Gym_Text_WallyThankYouAndDadGivesPokeBall: @ 8205A89
	.string "민진: 우와...\n"
	.string "포켓몬이다...!\p"
	.string "아빠: 흠...\n"
	.string "몬스터볼을 줄 테니\l"
	.string "열심히 해봐라!\p"
	.string "민진은\n"
	.string "몬스터볼을 받았다!$"
	// ミツル『わあ……ｎ
	// ポケモンだぁ……!ｐ
	// パパ『うむ……ｎ
	// モンスタ-ボ-ルは あげるからｌ
	// がんばって みなさい!ｐ
	// ミツルはｎ
	// モンスタ-ボ-ルを もらった!
	
PetalburgCity_Gym_Text_WallyOhWowThankYou: @ 8205AF4
	.string "민진: 아저씨 감사합니다!$"
	// ミツル『おじさん ありがとう!

PetalburgCity_Gym_Text_WouldYouReallyComeWithMe: @ 8205B0F
	.string "{PLAYER}님...\n"
    .string "저랑 같이 가주실 거죠$"
	// §あさん……ｎ
	// ぼくと いっしょに きてくれますよね

PetalburgCity_Gym_Text_DadSoDidItWorkOut: @ 8205B32
	.string "아빠: 성공했니?$"
	// パパ『うまく いったかい?

PetalburgCity_Gym_Text_WallyThankYouBye: @ 8205B4C
	.string "민진: 아저씨\n"
	.string "빌려주신 포켓몬 돌려 드릴게요\p"
	.string "{PLAYER}님 저랑 같이 가주셔서\n"
	.string "정말 감사했습니다...\p"
	.string "두 분 덕분에\n"
	.string "포켓몬을 잡을 수 있었어요!\l"
	.string "잡은 포켓몬 정말 소중히 키울게요\p"
	.string "...아! 엄마가 기다리시니\n"
	.string "이제 가야 해요!\p"
	.string "나중에 또 봐요 {PLAYER}님!$"
	// ミツル『おじさんｎ
	// おかりした ポケモン おかえし しますｐ
	// §あさん いっしょに きてくれてｎ
	// どうも ありがとう……ｐ
	// ポケモンを つかまえることが できたのはｎ
	// ふたりの おかげです!ｌ
	// つかまえた ポケモン たいせつに しますねｐ
	// ……あ! おかあさんが まってるからｎ
	// ぼくは もう いかなきゃ!ｐ
	// じゃあね §あさん!
	
PetalburgCity_Gym_Text_DadGoCollectBadges: @ 8205C40
	.string "아빠: 그럼...\p"
	.string "{PLAYER}! 포켓몬 트레이너로서\n"
	.string "강해지고 싶다면\l"
	.string "내 어드바이스를 듣거라\p"
	.string "먼저 이 앞에 있는\n"
	.string "금탄도시로 가거라\p"
	.string "거기서 원규라는 체육관 관장과\n"
	.string "배틀하도록 해!\p"
	.string "그렇게 각 지역의 포켓몬체육관에서\n"
	.string "체육관 관장을 쓰러뜨리고\l"
	.string "체육관 배지를 모아가는 거다\p"
	.string "물론 나도 체육관 관장이다\n"
	.string "언젠가는 {PLAYER}{K_WAGWA} 승부를 하겠지\p"
	.string "하지만 그건\n"
	.string "{PLAYER}{K_IGA} 강해졌을 때의 이야기다$"
	// パパ『さて……ｐ
	// §あ! ポケモントレ-ナ- としてｎ
	// つよく なりたいのならｌ
	// わたしの アドバイスを ききなさいｐ
	// まずは この さきにあるｎ
	// カナズミシティに いくんだｐ
	// そこで ツツジ という ジムリ-ダ-とｎ
	// たたかうと いい!ｐ
	// そうやって かくちの ポケモンジムでｎ
	// ジムリ-ダ-を たおしてｌ
	// ジムバッジを あつめて いくんだｐ
	// もちろん わたしも ジムリ-ダ-だｎ
	// いずれ §あと しょうぶ するだろうｐ
	// だが それは §あがｎ
	// つよくなってからの はなし だよ

PetalburgCity_Gym_Text_NormanGoToRustboro: @ 8205DB4
	.string "아빠: 응? 금탄도시의\n"
	.string "포켓몬체육관에는 가지 않니?\p"
	.string "아직 풋내 나는 트레이너와\n"
	.string "배틀해도 재미가 없지 않니\p"
	.string "{PLAYER}{K_IGA} 더욱 강해져서\n"
	.string "내 앞에 나타나 줬으면 좋겠구나\p"
	.string "그래 체육관 배지를\n"
	.string "4개 모으면 그때는\l"
	.string "{PLAYER}{K_WAGWA} 승부하지!$"

PetalburgCity_Gym_Text_NormanGoToDewford: @ 8205EAE
	.string "아빠: 그렇군... 금탄도시의\n"
	.string "체육관 관장에게 이겼구나\p"
	.string "하지만 아직도 {PLAYER}보다\n"
	.string "강한 트레이너는 많이 있다\p"
	.string "바다의 저편 무로마을의 체육관 관장\n"
	.string "그 이름은 철구...\p"
	.string "그하고도 배틀해보도록 해$"

PetalburgCity_Gym_Text_YouHaveGottenStronger: @ 8205F87
	.string "아빠: 흠... {PLAYER}\n"
	.string "강해지고 있구나\p"
	.string "그 배지의 수를 보면\n"
	.string "알 수 있어$"

PetalburgCity_Gym_Text_NormanIntro: @ 8205FE5
	.string "아빠: 그래...\n"
	.string "체육관 배지 4개를 모았구나\p"
	.string "그럼 약속대로\n"
	.string "포켓몬 승부를 해야겠지...\p"
	.string "{PLAYER}...\p"
	.string "난 지금 이렇게\n"
	.string "내 아이와 진지하게\l"
	.string "승부를 할 수 있다는 게\l"
	.string "매우 기쁘단다!\p"
	.string "하지만 승부는 승부!\p"
	.string "난 체육관 관장으로서\n"
	.string "최선을 다하마!\p"
	.string "{PLAYER}도 진심을 다해\n"
	.string "덤비도록!$"

PetalburgCity_Gym_Text_NormanDefeat: @ 8206107
	.string "...!\p"
	.string "설마...\p"
	.string "설마 {PLAYER}에게...\p"
	.string "{PLAYER}에게 질 줄이야...\p"
	.string "...좋다! 규칙은 규칙이다!\n"
	.string "이걸 주도록 하지$"

PetalburgCity_Gym_Text_ReceivedBalanceBadge: @ 8206162
	.string "{PLAYER}{K_EUNNEUN} 아빠에게\n"
	.string "밸런스배지를 받았다!!$"

PetalburgCity_Gym_Text_ExplainBalanceBadgeTakeThis: @ 820618A
	.string "아빠: 그 밸런스배지로\n"
	.string "{PLAYER}의 포켓몬들의\l"
	.string "방어력이 올라가게 된다\p"
	.string "비전기술 파도타기를\n"
	.string "배운 포켓몬이 있다면\l"
	.string "물 위를 이동할 수 있지\p"
	.string "이건 내가 주는 선물이다\n"
	.string "{PLAYER}{K_I}라면 잘 다룰 수 있겠지!$"

PetalburgCity_Gym_Text_ExplainFacade: @ 8206254
	.string "아빠: 기술머신42는 객기\p"
    .string "독, 마비, 화상에 걸리면\n"
	.string "기술의 위력이 2배가 되지!\p"
	.string "위기를 기회로\n"
	.string "바꿀 수 있을지도 모른다$"

PetalburgCity_Gym_Text_DadHappyAndSad: @ 82062FB
	.string "아빠: 체육관 관장으로서\n"
	.string "분해서 말이 안 나오는구나...\p"
	.string "하지만 부모로서는\n"
	.string "기쁘면서도 한편으로는\l"
	.string "조금 쓸쓸한 복잡한 기분이야...$"

PetalburgCity_Gym_Text_PleaseComeWithMe: @ 8206377
	.string "오오 있었구나 {PLAYER}{K_AYA}!\p"
	.string "잠깐 와주렴\n"
	.string "네게 주고 싶은 것이 있단다!$"
	// おお いたいた §あ§お!ｐ
	// ちょっと きてくれないかｎ
	// きみに わたしたい ものが あるんだ!

PetalburgCity_Gym_Text_LetMeBorrowPlayer: @ 82063CA
	.string "저기 종길씨 괜찮죠?\p"
	.string "종길씨네 {PLAYER}{K_EULREUL}\n"
	.string "잠깐 빌리겠습니다!$"
	// なあ センリさん いいだろう?ｐ
	// おたくの §あ§おをｎ
	// ちょっと おかりして いくよ!

PetalburgCity_Gym_Text_DadGoingToKeepTraining: @ 8206417
	.string "아빠: {PLAYER}! 가끔은 엄마를\n"
	.string "만나러 가도록 해!\p"
	.string "나는 여기서\n"
	.string "스스로를 단련하겠다!\p"
	.string "{PLAYER}에게 진 채로는\n"
	.string "트레이너로서 분하니까 말이야$"
	// パパ『§あ! たまには ママにもｎ
	// あいに いって あげるんだぞ!ｐ
	// わたしは ここでｎ
	// じぶんを きたえなおす!ｐ
	// §あに まけた ままではｎ
	// トレ-ナ-として くやしすぎる からな

PetalburgCity_Gym_Text_DadNoAmountOfTrainingIsEnough: @ 82064C3
	.string "아빠: {PLAYER}!\n"
    .string "상태는 어때?\p"
	.string "포켓몬은 심오하다!\n"
	.string "나는 아무리 수행해도\l"
	.string "부족하다고 느끼고 있는 중이다$"
	// パパ『§あ!ｎ
	// ちょうしは どうだ?ｐ
	// ポケモンは おくが ふかい!ｎ
	// わたしは いくら しゅぎょう してもｌ
	// たりなく おもっている ところだよ

PetalburgCity_Gym_Text_GymGuideAdvice: @ 8206542
	.string "잘 있었나!!\n"
	.string "챔피언을 노리는 {PLAYER}!!\p"
	.string "이 체육관은 방에 있는 트레이너를\n"
	.string "쓰러뜨리면 안쪽에 있는 문이 열려!\p"
	.string "...앗! 이 방은 이미\n"
	.string "문이 열리게 되어 있으니\l"
	.string "날 쓰러뜨리지는 말아 달라고!\p"
	.string "이곳 등화체육관의 트레이너들은\n"
	.string "다양한 도구를 쓰지!\p"
	.string "참고로 지금 이 방에서\n"
	.string "갈 수 있는 곳은\p"
	.string "왼쪽... 스피드 방과\n"
	.string "오른쪽... 명중의 방이야!\p"
	.string "문에도 쓰여 있으니\n"
	.string "잘 읽고 들어가 봐!\p"
	.string "자! 어느 쪽으로 갈지 정했나?\n"
	.string "그럼 힘내라고-!!$"

PetalburgCity_Gym_Text_GymGuidePostVictory: @ 82066F3
	.string "{PLAYER}{K_EUNNEUN} 자신의 아버지마저\n"
	.string "뛰어넘은 건가?!\p"
	.string "으아- 정말 기절초풍!!$"

PetalburgCity_Gym_Text_RandallIntro: @ 820674F
	.string "상대보다 먼저 공격한다...\p"
	.string "그것만으로도 승부가\n"
	.string "상당히 유리해지겠지?$"

PetalburgCity_Gym_Text_RandallDefeat: @ 82067B9
	.string "정말 눈부신 승부였다...!$"

PetalburgCity_Gym_Text_RandallPostBattle: @ 82067D8
	.string "안쪽 방으로 향해라!\n"
	.string "더 혹독한 시련이 널 기다리고 있다\p"
	.string "왼쪽은 떨어지지 않는 방\n"
	.string "오른쪽은 방어의 방이다!$"
	// おくの へやに すすみたまえ!ｎ
	// さらなる しれんが きみを まっているｐ
	// ひだりは さがらずの へや!ｎ
	// みぎは まもりの へや だ!

PetalburgCity_Gym_Text_RandallPostBadge: @ 820685E
	.string "누구한테 이기든\n"
	.string "누구한테 지든\l"
	.string "자신과 포켓몬을 계속 단련시키는 것...\p"
	.string "그게 바로 체육관 관장이야$"

PetalburgCity_Gym_Text_ParkerIntro: @ 82068FD
	.string "내 포켓몬의 능력을\n"
	.string "아무리 낮추려 해도 소용없어!$"

PetalburgCity_Gym_Text_ParkerDefeat: @ 820694F
	.string "능력은 떨어지지 않았지만\n"
	.string "그래도 이길 수 없었다...$"

PetalburgCity_Gym_Text_ParkerPostBattle: @ 8206996
	.string "다음은 힘의 방! 과연 그\n"
	.string "공격력을 버틸 수 있을까?$"

PetalburgCity_Gym_Text_ParkerPostBadge: @ 82069D9
	.string "체육관 관장이 너에게 지고 나서부터\n"
	.string "훈련의 강도가 더 세졌어!$"

PetalburgCity_Gym_Text_GeorgeIntro: @ 8206A1B
	.string "거의 쓰러뜨렸다고 생각했을 때\n"
	.string "상대의 HP가 회복된다\l"
	.string "그게 얼마나 혹독한 일인지...\p"
	.string "그 고통을 맛보게 해주마!$"

PetalburgCity_Gym_Text_GeorgeDefeat: @ 8206AB8
	.string "미처 다 회복하지 못할 정도의...\n"
	.string "엄청난 공격력이다...$"

PetalburgCity_Gym_Text_GeorgePostBattle: @ 8206AE9
	.string "과연 체육관 관장의 아이군...\p"
	.string "아니지! 트레이너의 재능은\n"
	.string "노력을 바탕으로 만들어지는 것...\p"
	.string "너에게 진 건\n"
	.string "나의 노력이 부족했기 때문이다...!\p"
	.string "자, 다음은 일격의 방이다!$"

PetalburgCity_Gym_Text_GeorgePostBadge: @ 8206BB1
	.string "포켓몬체육관에서 계속 수행해서\n"
	.string "언젠가는 체육관 관장이\l"
	.string "되고야 말겠어$"

PetalburgCity_Gym_Text_BerkeIntro: @ 8206BF4
	.string "체육관 관장의 아이라고 해서\n"
	.string "봐주지 않을 거야!\p"
	.string "급소를 맞는 두려움을\n"
	.string "실컷 맛보게 해줄게!$"

PetalburgCity_Gym_Text_BerkeDefeat: @ 8206C7D
	.string "네 실력은 진짜다...!$"

PetalburgCity_Gym_Text_BerkePostBattle: @ 8206C9F
	.string "네 아빠는 정말 강하면서도\n"
	.string "존경할 수 있는 트레이너야!\p"
	.string "그리고 너에게도\n"
	.string "네 아빠와 같은\l"
	.string "반짝임이 느껴져...\p"
	.string "가족이 서로의 실력을 겨루는\n"
	.string "최고의 명승부를 보여줘!$"

PetalburgCity_Gym_Text_BerkePostBadge: @ 8206D56
	.string "네 아빠가 체육관 관장으로\n"
	.string "오고 나서 등화도시에\l"
	.string "있는 트레이너들도 강해졌어$"

PetalburgCity_Gym_Text_MaryIntro: @ 8206DB2
	.string "후후후...\n"
	.string "여긴 명중의 방!\p"
	.string "모든 공격이 맞게 되면\n"
	.string "꽤 성가실 거야$"

PetalburgCity_Gym_Text_MaryDefeat: @ 8206E0D
	.string "네가 한 수 위구나...$"

PetalburgCity_Gym_Text_MaryPostBattle: @ 8206E26
	.string "안에는 더욱더 강한 트레이너가\n"
	.string "너를 기다리고 있어\p"
	.string "왼쪽은 방어의 방\n"
	.string "오른쪽은 회복의 방이야\p"
	.string "네 포켓몬의 공격력이\n"
	.string "시험받게 될 거야$"

PetalburgCity_Gym_Text_MaryPostBadge: @ 8206ED8
	.string "넌 우리 같은 트레이너가\n"
	.string "무엇을 목표로 하고 있는지 아니?\p"
	.string "...그건 말야 포켓몬과\n"
	.string "한마음이 되는 거야!$"

PetalburgCity_Gym_Text_AlexiaIntro: @ 8206F44
	.string "방어가 강하면 강할수록\n"
	.string "과감하게 공격할 수 있어$"

PetalburgCity_Gym_Text_AlexiaDefeat: @ 8206F82
	.string "완벽하게 방어할 수 없었어...$"

PetalburgCity_Gym_Text_AlexiaPostBattle: @ 8206F9F
	.string "너에게는 소중한 무언가를\n"
	.string "배운 거 같아...\p"
	.string "자, 그럼 다음으로 가!\n"
	.string "왼쪽은 힘의 방\l"
	.string "오른쪽은 일격의 방\p"
	.string "양쪽 모두\n"
	.string "공격을 중시하고 있어!$"

PetalburgCity_Gym_Text_AlexiaPostBadge: @ 8207069
	.string "어때? 파도타기는\n"
	.string "잘 쓰고 있어?$"

PetalburgCity_Gym_Text_JodyIntro: @ 8207088
	.string "온 힘을 다해 너를\n"
	.string "쓰러뜨리라고\l"
	.string "체육관 관장이 말했어...\p"
	.string "설령 그 상대가\n"
	.string "체육관 관장의 아이라 해도!$"

PetalburgCity_Gym_Text_JodyDefeat: @ 82070E6
	.string "모든 힘을 다 쏟아부었는데...!$"

PetalburgCity_Gym_Text_JodyPostBattle: @ 82070FB
	.string "네가 포켓몬을 다루는 방법...\n"
	.string "어딘지 모르게\l"
	.string "너의 아빠와 닮았어\p"
	.string "자! 이 안쪽에는 체육관 관장,\n"
	.string "네 아빠가 기다리고 있어!$"

PetalburgCity_Gym_Text_JodyPostBadge: @ 8207170
	.string "포켓몬을 강하게 키우는 것도\n"
	.string "좋지만 승부의 승패를\l"
	.string "정하는 건 포켓몬을 생각하는\l"
	.string "그 자신의 마음이야...!$"

PetalburgCity_Gym_Text_DoorAppearsLocked: @ 82071F4
	.string "지금 이 문은\n"
	.string "아직 잠겨 있는 것 같다...$"

PetalburgCity_Gym_Text_EnterSpeedRoom: @ 820721E
	.string "이 앞은 스피드의 방\p"
	.string "...이라고 쓰여 있다\n"
	.string "안으로 들어가겠습니까?$"

@ Unused
PetalburgCity_Gym_Text_DoorAppearsLocked2: @ 8207256
	.string "지금 이 문은\n"
	.string "아직 잠겨 있는 것 같다...$"

PetalburgCity_Gym_Text_EnterAccuracyRoom: @ 8207280
	.string "이 앞은 명중의 방\p"
	.string "...이라고 쓰여 있다\n"
	.string "안으로 들어가겠습니까?$"

PetalburgCity_Gym_Text_EnterConfusionRoom: @ 82072BB
	.string "이 앞은 떨어지지 않는 방\p"
	.string "...이라고 쓰여 있다\n"
	.string "안으로 들어가겠습니까?$"

PetalburgCity_Gym_Text_EnterDefenseRoom: @ 82072F7
	.string "이 앞은 방어의 방\p"
	.string "...이라고 쓰여 있다\n"
	.string "안으로 들어가겠습니까?$"

PetalburgCity_Gym_Text_EnterRecoveryRoom: @ 8207331
	.string "이 앞은 회복의 방\p"
	.string "...이라고 쓰여 있다\n"
	.string "안으로 들어가겠습니까?$"

PetalburgCity_Gym_Text_EnterStrengthRoom: @ 820736C
	.string "이 앞은 힘의 방\p"
	.string "...이라고 쓰여 있다\n"
	.string "안으로 들어가겠습니까?$"

PetalburgCity_Gym_Text_EnterOHKORoom: @ 82073A7
	.string "이 앞은 일격의 방\p"
	.string "...이라고 쓰여 있다\n"
	.string "안으로 들어가겠습니까?$"

PetalburgCity_Gym_Text_EnterGymLeadersRoom: @ 82073E4
	.string "이 앞은 체육관 관장\p"
	.string "어떤 포켓몬이 기다리고 있는지는\n"
	.string "자신의 눈으로 확인해라!\p"
	.string "...라고 쓰여 있다\n"
	.string "안으로 들어가겠습니까?$"

PetalburgCity_Gym_Text_GymStatue: @ 820744C
	.string "등화도시 포켓몬체육관$"

PetalburgCity_Gym_Text_GymStatueCertified: @ 8207467
	.string "등화도시 포켓몬체육관\p"
	.string "체육관 관장 종길\n"
	.string "인정 트레이너!\l"
	.string "{PLAYER}$"

PetalburgCity_Gym_Text_NormanPreRematch: @ 82074A2
	.string "DAD: {PLAYER}…\n"
	.string "I had a feeling that you would come.\p"
	.string "I would never refuse to accept\n"
	.string "a challenge from you.\p"
	.string "You do understand, don't you?\p"
	.string "Inside a GYM, it doesn't matter that\n"
	.string "we are a parent and child.\p"
	.string "…No, because we are parent and child,\n"
	.string "we owe it to each other to do the best\l"
	.string "we can. Isn't that right, {PLAYER}?$"

PetalburgCity_Gym_Text_NormanRematchDefeat: @ 82075CE
	.string "Uh… Haha…\n"
	.string "Maybe that was going too hard…$"

PetalburgCity_Gym_Text_NormanPostRematch: @ 82075F7
	.string "DAD: {PLAYER}…\n"
	.string "What is your dream?\p"
	.string "My dream…\n"
	.string "Hahaha…\l"
	.string "It has already come true, actually.$"

PetalburgCity_Gym_Text_NormanRematchNeedTwoMons: @ 820764A
	.string "DAD: {PLAYER}…\n"
	.string "I had a feeling that you would come.\p"
	.string "I would never refuse to accept\n"
	.string "a challenge from you.\p"
	.string "You do understand, don't you?\p"
	.string "Inside a GYM, it doesn't matter that\n"
	.string "we are a parent and child.\p"
	.string "Hm? Wait a second, {PLAYER}.\p"
	.string "Do you only have one POKéMON that is\n"
	.string "capable of battle?\p"
	.string "Sorry, but you'll have to come back\n"
	.string "with at least two POKéMON.$"

