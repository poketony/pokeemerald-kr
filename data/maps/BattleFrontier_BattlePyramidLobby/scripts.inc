.set LOCALID_ATTENDANT, 1
.set LOCALID_HINT_GIVER, 2

BattleFrontier_BattlePyramidLobby_MapScripts:: @ 8250716
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleDomeLobby_OnWarp
	.byte 0

@ Unused. Pyramid uses Dome's OnWarp (presumably by mistake). Their effects are identical
BattleFrontier_BattlePyramidLobby_OnWarp: @ 8250721
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth: @ 825072B
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePyramidLobby_OnFrame: @ 8250735
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_WON, BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus:: @ 825075F
	frontier_getstatus
	end

BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving:: @ 8250768
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	closemessage
	pyramid_set PYRAMID_DATA_WIN_STREAK, 0
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge:: @ 82507B1
	lockall
	frontier_isbrain
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing:: @ 82507D2
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints:: @ 82507DA
	special DoBattlePyramidMonsHaveHeldItem
	compare VAR_RESULT, TRUE
	call_if_eq BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag
	clearflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	message BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
	waitmessage
	pyramid_setprize
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge:: @ 8250852
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
	waitmessage
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge:: @ 82508AC
	goto BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge

BattleFrontier_BattlePyramidLobby_EventScript_Attendant:: @ 82508B1
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PYRAMID
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge:: @ 82508C8
	message BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge:: @ 8250904
	message BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, 0
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	frontier_checkineligible
	compare VAR_0x8004, TRUE
	goto_if_eq BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge:: @ 82509A5
	setvar VAR_TEMP_0, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	pyramid_init
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	pyramid_seedfloor
	pyramid_settrainers
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_0, 255
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge:: @ 8250A21
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	special HealPlayerParty
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 255, 1, 1
	setvar VAR_TEMP_0, 0
	waitstate
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge:: @ 8250A68
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons:: @ 8250A75
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50:: @ 8250A90
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen:: @ 8250A9D
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed:: @ 8250AAA
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge:: @ 8250AC1
	special LoadPlayerParty
BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge:: @ 8250AC4
	msgbox BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge:: @ 8250ACC
	release
	end

BattleFrontier_BattlePyramidLobby_EventScript_HintGiver:: @ 8250ACE
	lockall
	applymovement LOCALID_HINT_GIVER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait, MSGBOX_DEFAULT
	call BattleFrontier_BattlePyramidLobby_EventScript_GiveHint
	msgbox BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_GiveHint:: @ 8250AF0
	multichoice 17, 6, MULTI_LEVEL_MODE, 0
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
	return

@ Shouldnt occur
BattleFrontier_BattlePyramidLobby_EventScript_NoHint:: @ 8250B27
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50:: @ 8250B28
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_50
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak:: @ 8250B53
	pyramid_get PYRAMID_DATA_WIN_STREAK_50
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen:: @ 8250B66
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_OPEN
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak:: @ 8250B91
	pyramid_get PYRAMID_DATA_WIN_STREAK_OPEN
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment:: @ 8250BA4
	copyvar VAR_0x8004, VAR_RESULT
	special GetBattlePyramidHint
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_HintPoison
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_HintBurn
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate
	case 5, BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility
	case 6, BattleFrontier_BattlePyramidLobby_EventScript_HintIce
	case 7, BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion
	case 8, BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic
	case 9, BattleFrontier_BattlePyramidLobby_EventScript_HintRock
	case 10, BattleFrontier_BattlePyramidLobby_EventScript_HintFighting
	case 11, BattleFrontier_BattlePyramidLobby_EventScript_HintWeather
	case 12, BattleFrontier_BattlePyramidLobby_EventScript_HintBug
	case 13, BattleFrontier_BattlePyramidLobby_EventScript_HintDark
	case 14, BattleFrontier_BattlePyramidLobby_EventScript_HintWater
	case 15, BattleFrontier_BattlePyramidLobby_EventScript_HintGhost
	case 16, BattleFrontier_BattlePyramidLobby_EventScript_HintSteel
	case 17, BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon
	case 18, BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve
	case 19, BattleFrontier_BattlePyramidLobby_EventScript_HintNormal
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis:: @ 8250C8E
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintParalysis, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPoison:: @ 8250C97
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPoison, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBurn:: @ 8250CA0
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBurn, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste:: @ 8250CA9
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPPWaste, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate:: @ 8250CB2
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintLevitate, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility:: @ 8250CBB
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintIce:: @ 8250CC4
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintIce, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion:: @ 8250CCD
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintExplosion, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic:: @ 8250CD6
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPsychic, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintRock:: @ 8250CDF
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintRock, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFighting:: @ 8250CE8
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFighting, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWeather:: @ 8250CF1
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWeather, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBug:: @ 8250CFA
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBug, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintDark:: @ 8250D03
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintDark, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWater:: @ 8250D0C
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWater, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintGhost:: @ 8250D15
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintGhost, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintSteel:: @ 8250D1E
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintSteel, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon:: @ 8250D27
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve:: @ 8250D30
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintNormal:: @ 8250D39
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintNormal, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_ShowResults:: @ 8250D42
	lockall
	frontier_results FRONTIER_FACILITY_PYRAMID
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag:: @ 8250D56
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag

BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag:: @ 8250D94
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag:: @ 8250D9C
	message BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel
	waitmovement 0
	return

BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel: @ 8250DC4
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_down
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel: @ 8250DCD
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside: @ 8250DD5
	walk_right
	face_left
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel: @ 8250DD8
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag:: @ 8250DDB
	msgbox BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake, MSGBOX_DEFAULT
	setflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	special TryStoreHeldItemsInPyramidBag
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag
	message BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag:: @ 8250E00
	msgbox BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag, MSGBOX_DEFAULT
	return

@ When exiting Battle Pyramid with a full pyramid bag and held items the player must select to keep/toss party held items and make room for any kept items by tossing from the pyramid bag
BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep:: @ 8250E09
	multichoice 17, 6, MULTI_FRONTIER_ITEM_CHOOSE, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag:: @ 8250E40
	special ChooseItemsToTossFromPyramidBag
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty:: @ 8250E50
	special BattlePyramidChooseMonHeldItems
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems:: @ 8250E60
	special DoBattlePyramidMonsHaveHeldItem
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems
	return

BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems:: @ 8250E6F
	msgbox BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem, MSGBOX_DEFAULT
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_Woman:: @ 8250E83
	msgbox BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_FatMan:: @ 8250E8C
	msgbox BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBoard:: @ 8250E95
	lockall
	msgbox BattleFrontier_BattlePyramidLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard:: @ 8250EA4
	message BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 15, 2, MULTI_BATTLE_PYRAMID_RULES, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_RulesBag
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon:: @ 8250EF7
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers:: @ 8250F05
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze:: @ 8250F13
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBag:: @ 8250F21
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitRules:: @ 8250F2F
	releaseall
	end

BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid: @ 8250F31
	.string "트레이너의 용기를 시험하는 장소!\n"
	.string "배틀피라미드에 어서 오십시오!\p"
	.string "여기서는 배틀어드벤처의\n"
	.string "안내를 하고 있습니다!$"
	// トレ-ナ-の ゆうきを ためす ばしょ!ｎ
	// バトルピラミッドへ ようこそ!ｐ
	// こちらでは バトルアドベンチャ-のｎ
	// ごあんないを しておりますぞ!

BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge: @ 8250FA7
	.string "배틀어드벤처에\n"
	.string "도전하겠습니까?$"
	// バトルアドベンチャ-にｎ
	// ちょうせん されますかな?

BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge: @ 8250FE5
	.string "다음 도전을\n"
	.string "기다리고 있겠습니다!$"
	// またの ちょうせんをｎ
	// おまちして おりますぞ!

BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid: @ 825100C
	.string "배틀어드벤처는\n"
	.string "피라미드 안에 들어가\l"
	.string "정상 제패를 노리는\l"
	.string "모험 이벤트입니다!\p"
	.string "피라미드 안은\n"
	.string "7층의 미로로 나눠져 있고\l"
	.string "실력이 좋은 트레이너와\l"
	.string "야생 포켓몬이 기다리고 있습니다!\p"
	.string "도구를 지니지 않은\n"
	.string "3마리의 포켓몬과\l"
	.string "빌려드릴 배틀백을 가지고\l"
	.string "정상을 노려주세요!\p"
	.string "이 배틀백에 넣은 도구는\n"
	.string "모험에 실패하면\l"
	.string "없어져 버리므로\l"
	.string "주의해 주십시오!\p"
	.string "또한 모험을 중단할 때\n"
	.string "“쉰다”를 선택하지 않으면\l"
	.string "모험은 중지됩니다!\l"
	.string "부디 주의해 주십시오!$"
	// バトルアドベンチャ-はｎ
	// ピラミッドの なかへ はいりｌ
	// ちょうじょう せいはを めざすｌ
	// ぼうけん イベント ですぞ!ｐ
	// ピラミッドの なかはｎ
	// 7だんの めいろで わかれていてｌ
	// うでに おぼえの ある トレ-ナ-とｌ
	// やせい ポケモンが まって いますぞ!ｐ
	// どうぐを もたせて いないｎ
	// 3ひきの ポケモンとｌ
	// おわたしする バトルバッグを もってｌ
	// ちょうじょうを めざして いただきますぞ!ｐ
	// この バトルバッグに いれた どうぐはｎ
	// ぼうけんに しっぱいするとｌ
	// なくなって しまいますのでｌ
	// おきをつけ くだされ!ｐ
	// また ぼうけんを ちゅうだん するときはｎ
	// 「やすむ」を えらんで おわらせないとｌ
	// ぼうけんは ちゅうしと なってしまいます!ｌ
	// じゅうぶん おきをつけ くだされ!

BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode: @ 8251248
	.string "피라미드에는\n"
	.string "레벨 50과 오픈 레벨이 있습니다만\l"
	.string "어느 쪽으로 들어가겠습니까?$"
	// ピラミッドにはｎ
	// レベル50と オ-プンレベルと ありますがｌ
	// どちらに はいられますかな?

BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons: @ 8251297
	.string "그럼 데려갈 포켓몬을\n"
	.string "3마리 선택해 주십시오!$"
	// では つれていく ポケモンをｎ
	// 3ひき おえらび くだされ!

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen: @ 82512E2
	.string "모험자여!!\p"
	.string "데려갈 수 있는 포켓몬이\n"
	.string "3마리는 필요합니다!\p"
	.string "또 포켓몬이 지니고 있는 도구를\n"
	.string "모두 정리하여 주십시오!\p"
	.string "그리고 알, 뮤,\n"
	.string "뮤츠, 칠색조,\l"
	.string "루기아, 세레비,\l"
	.string "가이오가, 그란돈,\l"
	.string "레쿠쟈, 지라치,\l"
	.string "테오키스는\l"
	.string "참가시킬 수 없습니다!\p"
	.string "준비되면\n"
	.string "다시 방문해 주십시오$"
	// ぼうけんしゃよ!!ｐ
	// つれていける ポケモンがｎ
	// 3ひき いないようですぞ!ｐ
	// また ポケモンに もたせている どうぐはｎ
	// すべて はずしてくだされ!ｐ
	// なお タマゴいさんか させる ことは できませんぞ!ｐ
	// じゅんびが できましたらｎ
	// また おこし くだされ!

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50: @ 82513C1
	.string "모험자여!!\p"
	.string "데려갈 수 있는 포켓몬이\n"
	.string "3마리는 필요합니다!\p"
	.string "참가하려면 레벨 50 이하의\n"
	.string "종류가 다른 포켓몬을\l"
	.string "3마리 준비해 주십시오!\p"
	.string "또 포켓몬이 지니고 있는 도구를\n"
	.string "모두 정리하여 주십시오!\p"
	.string "그리고 알, 뮤,\n"
	.string "뮤츠, 칠색조,\l"
	.string "루기아, 세레비,\l"
	.string "가이오가, 그란돈,\l"
	.string "레쿠쟈, 지라치,\l"
	.string "테오키스는\l"
	.string "참가시킬 수 없습니다!\p"
	.string "준비되면\n"
	.string "다시 방문해 주십시오$"
	// ぼうけんしゃよ!!ｐ
	// つれていける ポケモンがｎ
	// 3ひき いないようですぞ!ｐ
	// つれていく ためには レベルが 50いかでｎ
	// すべて ちがう しゅるいの ポケモンをｌ
	// 3ひき よういして くだされ!ｐ
	// また ポケモンに もたせている どうぐはｎ
	// すべて はずしてくだされ!ｐ
	// なお タマゴいさんか させる ことは できませんぞ!ｐ
	// じゅんびが できましたらｎ
	// また おこし くだされ!

BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge: @ 82514E6
	.string "배틀피라미드에 들어가기 전에\n"
	.string "리포트를 작성합니다만\l"
	.string "괜찮겠습니까?$"
	// バトルピラミッドへ はいる まえにｎ
	// レポ-トを かきますが よろしいですかな?

BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid: @ 8251531
	.string "그럼 배틀피라미드 안으로\n"
	.string "모셔다 드리겠습니다!$"
	// では バトルピラミッドの なかへｎ
	// おつれいたしますぞ!

BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping: @ 8251569
	.string "{PLAYER}님이 가지고 계신 가방은\n"
	.string "이쪽에서 맡도록 하겠습니다!$"
	// あさんの もっている バッグはｎ
	// こちらで あずからせて いただきますぞ!

BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag: @ 82515AD
	.string "대신 전에 사용하셨던\n"
	.string "이 배틀백을 가져가 주십시오!$"
	// かわりに ぜんかい おつかいになったｎ
	// この バトルバッグを おもちくだされ!

BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag: @ 82515F4
	.string "대신 이쪽의\n"
	.string "배틀백을 가져가 주십시오!$"
	// かわりに こちらのｎ
	// バトルバッグを おもちくだされ!

BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag: @ 825161E
	.string "{PLAYER}{K_EUNNEUN} 가방을 맡기고\n"
	.string "배틀백을 받았다!$"
	// あは バッグを あずけてｎ
	// バトルバッグを うけとった!

BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel: @ 8251647
	.string "이쪽에 있는 마루를 밟아주시면\n"
	.string "피라미드의 위층으로\l"
	.string "나아갈 수 있습니다!\p"
	.string "무사히 모험을 할 수 있기를\n"
	.string "바라겠습니다!$"
	// こちらにある ゆかを ふんで いただくとｎ
	// ピラミッドの うえの だんへとｌ
	// すすむことが できますぞ!ｐ
	// ぶじ ぼうけんが すすむことをｎ
	// いのって おりますぞ!

BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag: @ 82516D6
	.string "모험자여!\p"
	.string "지난번 종료하기 전에\n"
	.string "리포트를 제대로\l"
	.string "작성하지 않으셨죠?\p"
	.string "죄송하지만 이런 경우에는\n"
	.string "도전이 무효가 됩니다!\p"
	.string "맡고 있던\n"
	.string "가방은 돌려드리겠습니다!\p"
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "가방을 받았다!$"
	// ぼうけんしゃよ!ｐ
	// ぜんかい レポ-トを かいてｎ
	// しゅうりょう しませんでしたな?ｐ
	// ざんねんですが この ばあいｎ
	// ちょうせんは むこうと なりますぞ!ｐ
	// おあずかり していたｎ
	// バッグは おかえし いたしますぞ!ｐ
	// あはｎ
	// バッグを うけとった!

BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid: @ 82517B5
	.string "돌아오셨습니까!\p"
	.string "훌륭히 배틀피라미드를\n"
	.string "제패하셨군요!$"
	// おかえりなさいませ!ｐ
	// みごとに バトルピラミッドをｎ
	// せいは されましたな!

BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake: @ 82517FC
	.string "아앗!\p"
	.string "포켓몬에게\n"
	.string "도구를 지니게 하셨군요...\p"
	.string "죄송하지만\n"
	.string "피라미드에서 얻은 도구는\l"
	.string "가지고 가실 수 없습니다!$"
	// おおっ!ｐ
	// ポケモンにｎ
	// どうぐを もたせていますな……ｐ
	// もうしわけ ありませんがｎ
	// ピラミッドで てにいれた どうぐはｌ
	// もっていくことが できませんぞ!

BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag: @ 8251881
	.string "지니게 한 도구는\n"
	.string "모두 {PLAYER}님의 배틀백에\l"
	.string "넣어두겠습니다!$"
	// もたせている どうぐはｎ
	// すべて あさんの バトルバッグにｌ
	// いれておきますぞ!

BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep: @ 82518C6
	.string "배틀백에는\n"
	.string "모두 들어가지 않으므로\l"
	.string "배틀백과 지니게 한 도구를\l"
	.string "정리해 주세요!$"
	// バトルバッグにはｎ
	// すべて はいらない ようなのでｌ
	// バトルバッグと もたせたどうぐをｌ
	// せいりして くだされ!

BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem: @ 825194F
	.string "아직 포켓몬이\n"
	.string "도구를 지니고 있습니다!$"
	// ポケモンにｎ
	// まだ どうぐを もたせていますぞ!$

BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep: @ 825197E
	.string "배틀백과 지니게 한 도구를\n"
	.string "정리해 주세요!$"
	// バトルバッグと もたせたどうぐをｎ
	// せいりして くだされ!

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ReturnedEverythingMonsHeld: @ 82519CA
	.string "{PLAYER}{K_EUNNEUN} 지니게 한\n"
	.string "도구를 바꿨다!$"
	// あは ポケモンに もたせているｎ
	// どうぐを かえした!

BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept: @ 82519F8
	.string "수고하셨습니다 배틀백은\n"
	.string "다음 도전까지\l"
	.string "맡아두도록 하겠습니다!\p"
	.string "{PLAYER}{K_EUNNEUN} 배틀백을 맡기고\n"
	.string "가방을 받았다!$"
	// おつかいになられた バトルバッグはｎ
	// じかいの ちょうせんまでｌ
	// おあずかり いたしますぞ!ｐ
	// あは バトルバッグを あずけてｎ
	// バッグを うけとった!

BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait: @ 8251A77
	.string "성적을 리포트에 작성하므로\n"
	.string "기다려 주십시오!$"
	// せいせきを レポ-トに かきますのでｎ
	// おまちくだされ!

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ForConqueringPyramidTakeThis: @ 8251AA0
	.string "배틀피라미드 제패를 기념하여\n"
	.string "이 상품을 받아주세요!$"
	// バトルピラミッド せいはの きねんとしてｎ
	// この しょうひんを おうけとり くだされ!

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ReceivedPrizeItem: @ 8251AE2
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "{STR_VAR_1}{K_EULREUL} 받았다!$"
	// あはｎ
	// いを もらった!

@ Unused
BattleFrontier_BattlePyramidLobby_Text_BagIsFull: @ 8251AFC
	.string "...호오!\n"
	.string "도구가 가득찬 모양입니다\p"
	.string "도구를 정리하고 나서\n"
	.string "다시 와주십시오!$"
	// ……ほう!ｎ
	// どうぐが いっぱいの ようですなｐ
	// どうぐを せいりしてからｎ
	// また おこしくだされ!

BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag: @ 8251B5A
	.string "아쉽게 되었군요...\p"
	.string "맡아두었던\n"
	.string "가방을 돌려드리겠습니다!\p"
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "가방을 받았다!$"
	// ざんねんでしたな……ｐ
	// おあずかりしていたｎ
	// バッグは おかえし いたしますぞ!ｐ
	// あはｎ
	// バッグを うけとった!

BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge: @ 8251BB6
	.string "다음 도전을\n"
	.string "기다리고 있겠습니다!$"
	// またの ちょうせんをｎ
	// おまちして おりますぞ!

@ Unused
BattleFrontier_BattlePyramidLobby_Text_HereIsPrize: @ 8251BDE
	.string "기다리고 있었습니다!\p"
	.string "배틀피라미드 제패를 기념하여\n"
	.string "이 상품을 드리겠습니다!$"
	// おまちしておりましたぞ!ｐ
	// バトルピラミッド せいはの きねんとしてｎ
	// この しょうひんを おうけとり くだされ!

BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait: @ 8251C3B
	.string "어서 오세요...\p"
	.string "피라미드에서 일어날 일들을\n"
	.string "점쳐 드리겠습니다...$"
	// ようこそ……ｐ
	// ピラミッドで おこる わざわいをｎ
	// うらなって さしあげましょう……

BattleFrontier_BattlePyramidLobby_Text_Aah: @ 8251C8A
	.string "........................\n"
	.string "........................\p"
	.string "...아앗!$"
	// ………………………………………………………ｎ
	// ………………………………………………………ｐ
	// ……っああっ!

BattleFrontier_BattlePyramidLobby_Text_HintParalysis: @ 8251CB3
	.string "전기가 튀고 있는 게 보입니다...\p"
	.string "...그리고\n"
	.string "마비로 생각대로 움직일 수 없는\l"
	.string "당신의 포켓몬의 모습도...$"
	// でんきが とびちっています……ｐ
	// ……そしてｎ
	// まひにより おもうように うごけないｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintPoison: @ 8251D07
	.string "독이 보입니다...\p"
	.string "...그리고\n"
	.string "독에 걸려 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// どくが みえます……ｐ
	// ……そしてｎ
	// どくに おかされ くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintBurn: @ 8251D54
	.string "새빨간 불꽃이 보입니다...\p"
	.string "...그리고\n"
	.string "화상으로 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// まっかな ほのおが みえます……ｐ
	// ……そしてｎ
	// やけどを おって くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintPPWaste: @ 8251D9C
	.string "굉장한 프레셔와 원념...\n"
	.string "원한의 힘이 보입니다...\p"
	.string "...그리고\n"
	.string "파워포인트가 없어져서\l"
	.string "발버둥치고 있는\l"
	.string "당신의 포켓몬의 모습도...$"
	// すさまじい プレッシャ-と おんねん……ｎ
	// うらみの ちからが みえます……ｐ
	// そして……ｎ
	// パワ-ポイントが なくなりｌ
	// わるあがきを するｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintLevitate: @ 8251E3D
	.string "완만하게 부유하는...\n"
	.string "포켓몬들이 보입니다...\p"
	.string "...그리고\n"
	.string "땅 기술을 쓰지 못해 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// ゆるやかに ふゆうするｎ
	// ポケモンたちが みえます……ｐ
	// ……そしてｎ
	// じめんの わざを つかえずに くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility: @ 8251EA1
	.string "발밑에서 솟아오르는\n"
	.string "강한 힘이 보입니다...\p"
	.string "...그리고\n"
	.string "도망치려고 해도 도망칠 수 없는\l"
	.string "당신의 포켓몬의 모습도...$"
	// あしもとから わきおこるｎ
	// つよい ちからが みえます……ｐ
	// ……そしてｎ
	// にげようとしても にげられないｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintIce: @ 8251F17
	.string "얼음타입의\n"
	.string "포켓몬들이 보입니다...\p"
	.string "...그리고\n"
	.string "얼음 기술로 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// こおりタイプのｎ
	// ポケモンたちが みえます……ｐ
	// ……そしてｎ
	// こおりの わざに くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintExplosion: @ 8251F6E
	.string "목숨을 깎으며\n"
	.string "반복되는 기술이 보입니다...\p"
	.string "...그리고\n"
	.string "기술을 맞고 쓰러져 가는\l"
	.string "당신의 포켓몬의 모습도...$"
	// いのちを かけてｎ
	// くりだされる わざが みえます……ｐ
	// ……そしてｎ
	// わざを うけて たおれていくｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintPsychic: @ 8251FC7
	.string "에스퍼타입의\n"
	.string "포켓몬들이 보입니다...\p"
	.string "...그리고\n"
	.string "에스퍼 기술로 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// エスパ-タイプのｎ
	// ポケモンたちが みえます……ｐ
	// ……そしてｎ
	// エスパ-の わざに くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintRock: @ 825201B
	.string "바위타입의\n"
	.string "포켓몬들이 보입니다...\p"
	.string "...그리고\n"
	.string "바위 기술로 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// いわタイプのｎ
	// ポケモンたちが みえます……ｐ
	// ……そしてｎ
	// いわの わざに くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintFighting: @ 8252068
	.string "격투타입의\n"
	.string "포켓몬들이 보입니다...\p"
	.string "...그리고\n"
	.string "격투 기술로 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// かくとうタイプのｎ
	// ポケモンたちが みえます……ｐ
	// ……そしてｎ
	// かくとうの わざに くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintWeather: @ 82520BA
	.string "비바라기... 쾌청...\n"
	.string "모래바람... 싸라기눈...\p"
	.string "날씨 변화로 강해지는\n"
	.string "포켓몬들이 보입니다\p"
	.string "...그리고\n"
	.string "여러 타입에 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// あまごい…… にほんばれ……ｎ
	// すなあらし…… あられ……ｐ
	// てんこうの へんかで つよくなるｎ
	// ポケモンたちが みえますｐ
	// ……そしてｎ
	// さまざまな タイプに くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintBug: @ 8252158
	.string "벌레타입의\n"
	.string "포켓몬들이 보입니다...\p"
	.string "...그리고\n"
	.string "여러 공격으로 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// むしタイプのｎ
	// ポケモンたちが みえます……ｐ
	// ……そしてｎ
	// さまざまな こうげきで くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintDark: @ 82521B4
	.string "악타입의\n"
	.string "포켓몬들이 보입니다...\p"
	.string "...그리고\n"
	.string "악 기술로 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// あく タイプのｎ
	// ポケモンたちが みえます……ｐ
	// ……そしてｎ
	// あくの わざに くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintWater: @ 8252206
	.string "물타입의\n"
	.string "포켓몬들이 보입니다...\p"
	.string "...그리고\n"
	.string "물 기술로 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// みずタイプのｎ
	// ポケモンたちが みえます……ｐ
	// ……そしてｎ
	// みずの わざに くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintGhost: @ 825225A
	.string "고스트타입의\n"
	.string "포켓몬들이 보입니다...\p"
	.string "...그리고\n"
	.string "고스트 기술로 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// ゴ-ストタイプのｎ
	// ポケモンたちが みえます……ｐ
	// ……そしてｎ
	// ゴ-ストの わざに くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintSteel: @ 82522AE
	.string "강철타입의\n"
	.string "포켓몬들이 보입니다...\p"
	.string "...그리고\n"
	.string "강한 기술로 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// はがねタイプのｎ
	// ポケモンたちが みえます……ｐ
	// ……そしてｎ
	// きょうだいな わざに くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon: @ 825230B
	.string "하늘을 나는\n"
	.string "포켓몬들이 보입니다...\p"
	.string "...그리고\n"
	.string "강한 기술로 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// そらをとぶｎ
	// ポケモンたちが みえます……ｐ
	// ……そしてｎ
	// きょうだいな わざに くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve: @ 8252364
	.string "돌의 힘으로\n"
	.string "진화한 자들이 보입니다...\p"
	.string "...그리고\n"
	.string "불꽃... 물... 전기...\p"
	.string "3개의 힘으로 괴로워하는\n"
	.string "당신의 포켓몬의 모습도...$"
	// いしの ちからによりｎ
	// しんかした ものたちが みえます……ｐ
	// ……そしてｎ
	// ほのお…… みず…… でんき……ｐ
	// 3つの ちからに くるしむｎ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_HintNormal: @ 8252403
	.string "노말타입의\n"
	.string "포켓몬들이 보입니다...\p"
	.string "...그리고\n"
	.string "강한 기술로 괴로워하는\l"
	.string "당신의 포켓몬의 모습도...$"
	// ノ-マルタイプのｎ
	// ポケモンたちが みえます……ｐ
	// ……そしてｎ
	// きょうだいな わざに くるしむｌ
	// あなたの ポケモンの すがたも……

BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot: @ 8252461
	.string "점을 믿든 그렇지 않든\n"
	.string "선택은 당신의 몫...\p"
	.string "미래는 언제나 바뀔 수 있습니다...\n"
	.string "부디 무사하시길...$"
	// うらないを しんじるも しんじないもｎ
	// あなた しだい……ｐ
	// みらいは いつでも かえられます……ｎ
	// どうぞ ごぶじで……

BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning: @ 82524DA
	.string "너 그거 알아?\p"
	.string "빠르게 달리면\n"
	.string "트레이너가 발소리를 듣고\l"
	.string "승부를 걸어와!\p"
	.string "그러니까 트레이너하고\n"
	.string "눈을 마주치지 않으려면\l"
	.string "트레이너의 움직임을 보면서\l"
	.string "차분히 걷는 편이 좋지!$"
	// あなた しってた?ｐ
	// はやく はしるとｎ
	// トレ-ナ-が あしおとに きづいてｌ
	// しょうぶを しかけて くるの!ｐ
	// だから トレ-ナ-とｎ
	// めを あわせたくない ときはｌ
	// トレ-ナ-の ようすを みながらｌ
	// ゆっくり あるいた ほうが いいのよ!

BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems: @ 8252595
	.string "우오오오------옷!\p"
	.string "도구를 가득 가져왔었는데\n"
	.string "져서 전부 없어져 버렸다...\p"
	.string "우오오오------옷!$"
	// うおおおお------ん!ｐ
	// どうぐを いっぱい もってたのにｎ
	// まけたら ぜんぶ なくなっちゃった……ｐ
	// うおおおお------ん!

BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing: @ 82525F4
	.string "돌아오셨습니까!\p"
	.string "피라미드킹을 쓰러뜨리고\n"
	.string "훌륭히 배틀피라미드를\l"
	.string "제패하셨군요!$"
	// おかえりなさいませ!ｐ
	// ピラミッドキングを たおしｎ
	// みごと バトルピラミッドをｌ
	// せいは されましたな!

BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints: @ 8252662
	.string "모험자여!\n"
	.string "당신의 뜨거운 용기를 기리며\l"
	.string "배틀포인트를 드리겠습니다!$"
	// ぼうけんしゃよ!ｎ
	// あなたの あつい ゆうきを たたえｌ
	// バトルポイントを おおくり しましょう!

BattleFrontier_BattlePyramidLobby_Text_RulesAreListed: @ 82526B6
	.string "배틀어드벤처의\n"
	.string "규칙이 적혀 있다!$"
	// バトルアドベンチャ-のｎ
	// ル-ルが かかれている!

BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading: @ 82526D9
	.string "어느 설명을 읽겠습니까?$"
	// どの せつめいを よみますか?

BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules: @ 82526FC
	.string "피라미드 안에서 튀어나오는\n"
	.string "야생 포켓몬은\l"
	.string "피라미드를 제패하면 바뀝니다\p"
	.string "어떤 포켓몬이 나오는지는\n"
	.string "실제로 모험하면서 알아봅시다$"
	// ピラミッドの なかで でてくるｎ
	// やせい ポケモンはｌ
	// ピラミッドを せいはすると かわりますｐ
	// どんな ポケモンが でてくるのかはｎ
	// じっさいに ぼうけんして おぼえましょう

BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules: @ 82527A9
	.string "피라미드 안에서는\n"
	.string "트레이너가 대기하고 있습니다\p"
	.string "한 층마다 최대\n"
	.string "8명까지 트레이너가 있습니다\p"
	.string "또한 트레이너에게 이기면\n"
	.string "조금 모험에 도움이 되는\l"
	.string "힌트를 받을 수 있습니다$"
	// ピラミッドの なかにはｎ
	// トレ-ナ-が まちかまえて いますｐ
	// 1つの だんには さいこうでｎ
	// 8にんの トレ-ナ-が いますｐ
	// また トレ-ナ-に かつとｎ
	// ちょっと ぼうけんに やくだつｌ
	// ヒントが もらえます

BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules: @ 825285A
	.string "피라미드의 미로는\n"
	.string "들어갈 때마다 바뀝니다\p"
	.string "안은 매우 어두우므로\n"
	.string "신중히 나아갑시다\p"
	.string "또한 야생 포켓몬이나 트레이너와\n"
	.string "배틀할 때마다\l"
	.string "조금씩 주변이 밝아집니다$"
	// ピラミッドの めいろはｎ
	// はいる たびに かわりますｐ
	// なかは とても くらく なっているのでｎ
	// しんちょうに すすみましょうｐ
	// また やせいポケモンや トレ-ナ-とのｎ
	// たたかいに かつとｌ
	// ちょっとだけ まわりが あかるくなります

BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules: @ 8252924
	.string "배틀백은 피라미드에 있는 동안\n"
	.string "쓸 수 있습니다\p"
	.string "레벨 50과 오픈 레벨의\n"
	.string "가방이 각각 준비되어 있으며\l"
	.string "10종류의 도구를\l"
	.string "99개까지 넣을 수 있습니다\p"
	.string "또한 가방의 내용물은 모험에\n"
	.string "실패하면 없어져 버립니다$"
	// バトルバッグは ピラミッドに いる あいだｎ
	// つかうことが できますｐ
	// レベル50と オ-プンレベルのｎ
	// バッグが それぞれ ようい されていてｌ
	// 10しゅるいの どうぐをｌ
	// 99こ まで いれることが できますｐ
	// また バッグの なかみは ぼうけんにｎ
	// しっぱい すると なくなって しまいます

