.set LOCALID_BLACK_BELT_1, 1
.set LOCALID_BLACK_BELT_2, 2
.set LOCALID_BLACK_BELT_3, 3
.set LOCALID_BLACK_BELT_4, 4
.set LOCALID_ATTENDANT, 5
.set LOCALID_OPPONENT, 7
.set LOCALID_PLAYER, 8
.set LOCALID_ANNOUNCER, 9

BattleFrontier_BattleArenaBattleRoom_MapScripts:: @ 8257487
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleArenaBattleRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleArenaBattleRoom_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleArenaBattleRoom_OnWarp
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleArenaBattleRoom_OnResume
	.byte 0

	@ On this map the player (OBJ_EVENT_ID_PLAYER) is hidden
	@ The player is represented instead by LOCALID_PLAYER, which has the gfx id VAR_OBJ_GFX_ID_1

BattleFrontier_BattleArenaBattleRoom_OnResume:
	special OffsetCameraForBattle
	end

BattleFrontier_BattleArenaBattleRoom_OnTransition:
	frontier_settrainers
	call BattleFrontier_BattleArenaBattleRoom_EventScript_SetPlayerGfx
	end

BattleFrontier_BattleArenaBattleRoom_EventScript_SetPlayerGfx::
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_SetPlayerGfxMale
	compare VAR_RESULT, FEMALE
	goto_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_SetPlayerGfxFemale
	return

BattleFrontier_BattleArenaBattleRoom_EventScript_SetPlayerGfxMale::
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	return

BattleFrontier_BattleArenaBattleRoom_EventScript_SetPlayerGfxFemale::
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	return

BattleFrontier_BattleArenaBattleRoom_OnFrame:
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattleArenaBattleRoom_EventScript_EnterRoom
	.2byte 0

BattleFrontier_BattleArenaBattleRoom_EventScript_EnterRoom::
	lockall
	showobjectat LOCALID_PLAYER, MAP_BATTLE_FRONTIER_BATTLE_ARENA_BATTLE_ROOM
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaBattleRoom_Movement_PlayerEnter
	waitmovement 0
	frontier_get FRONTIER_DATA_BATTLE_NUM
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_AnnounceTrainers
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaBattleRoom_Movement_WalkInPlaceDown
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaBattleRoom_Movement_WalkInPlaceLeft
	setvar VAR_TEMP_2, 1
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleArenaBattleRoom_EventScript_AnnounceTrainers::
	tower_setopponent
	addobject LOCALID_OPPONENT
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleArenaBattleRoom_Movement_OpponentEnter
	waitmovement 0
	applymovement LOCALID_ANNOUNCER, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceDown
	playse SE_M_BELLY_DRUM
	waitse
	waitmovement 0
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_PlayerStepForward, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaBattleRoom_Movement_PlayerStepForward
	waitmovement 0
	applymovement LOCALID_ANNOUNCER, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceDown
	playse SE_M_BELLY_DRUM
	waitse
	waitmovement 0
	arena_gettrainername
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_OpponentStepForward, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleArenaBattleRoom_Movement_OpponentStepForward
	waitmovement 0
	applymovement LOCALID_ANNOUNCER, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceDown
	playse SE_M_BELLY_DRUM
	waitse
	waitmovement 0
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_SetKOTourneyBegin, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaBattleRoom_Movement_PlayerStepForward
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleArenaBattleRoom_Movement_OpponentStepForward
	waitmovement 0
	palace_getopponentintro
	msgbox gStringVar4, MSGBOX_DEFAULT
	waitmessage
	call BattleFrontier_BattleArenaBattleRoom_EventScript_DoArenaBattle
	switch VAR_RESULT
	case 1, BattleFrontier_BattleArenaBattleRoom_EventScript_DefeatedOpponent
BattleFrontier_BattleArenaBattleRoom_EventScript_DeclareOpponentWinner:: @ 82575DB
	applymovement LOCALID_ANNOUNCER, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceDown
	applymovement LOCALID_BLACK_BELT_1, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceDown
	applymovement LOCALID_BLACK_BELT_2, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceDown
	applymovement LOCALID_BLACK_BELT_3, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceUp
	applymovement LOCALID_BLACK_BELT_4, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceUp
	playse SE_M_SNORE
	waitse
	waitmovement 0
	arena_gettrainername
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_WinnerIsOpponent, MSGBOX_DEFAULT
BattleFrontier_BattleArenaBattleRoom_EventScript_WarpToLobbyLost::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	warp MAP_BATTLE_FRONTIER_BATTLE_ARENA_LOBBY, 255, 7, 8
	waitstate

BattleFrontier_BattleArenaBattleRoom_EventScript_DefeatedOpponent::
	call BattleFrontier_BattleArenaBattleRoom_EventScript_DeclarePlayerWinner
	frontier_get FRONTIER_DATA_BATTLE_NUM
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	switch VAR_RESULT
	case 7, BattleFrontier_BattleArenaBattleRoom_EventScript_ReturnToLobbyWon
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaBattleRoom_Movement_PlayerWalkBackToLine
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleArenaBattleRoom_Movement_OpponentExit
	waitmovement 0
	removeobject LOCALID_OPPONENT
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaBattleRoom_Movement_WalkInPlaceDown
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaBattleRoom_Movement_WalkInPlaceLeft
	waitmovement 0
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_MonsWillBeRestored, MSGBOX_DEFAULT
	special LoadPlayerParty
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForOpponent::
	frontier_getbrainstatus
	copyvar VAR_TEMP_F, VAR_RESULT
	compare VAR_RESULT, FRONTIER_BRAIN_NOT_READY
	goto_if_ne BattleFrontier_BattleArenaBattleRoom_EventScript_TycoonUpNext
	frontier_get FRONTIER_DATA_BATTLE_NUM
	compare VAR_RESULT, 1
	call_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_ReadyFor2ndOpponent
	compare VAR_RESULT, 2
	call_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_ReadyFor3rdOpponent
	compare VAR_RESULT, 3
	call_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_ReadyFor4thOpponent
	compare VAR_RESULT, 4
	call_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_ReadyFor5thOpponent
	compare VAR_RESULT, 5
	call_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_ReadyFor6thOpponent
	compare VAR_RESULT, 6
	call_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_ReadyFor7thOpponent
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForOpponentNoRecord
	multichoice 19, 4, MULTI_GO_ON_RECORD_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaBattleRoom_EventScript_ContinueChallenge
	case 1, BattleFrontier_BattleArenaBattleRoom_EventScript_AskRecordBattle
	case 2, BattleFrontier_BattleArenaBattleRoom_EventScript_AskPauseChallenge
	case 3, BattleFrontier_BattleArenaBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForOpponentNoRecord::
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaBattleRoom_EventScript_ContinueChallenge
	case 1, BattleFrontier_BattleArenaBattleRoom_EventScript_AskPauseChallenge
	case 2, BattleFrontier_BattleArenaBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleArenaBattleRoom_EventScript_AskRecordBattle::
	message BattleFrontier_BattleArenaBattleRoom_Text_RecordLastBattle
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForOpponent
	case 0, BattleFrontier_BattleArenaBattleRoom_EventScript_RecordBattle
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleArenaBattleRoom_EventScript_RecordBattle::
	call BattleFrontier_EventScript_SaveBattle
	goto BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleArenaBattleRoom_EventScript_AskPauseChallenge::
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_SaveAndShutDown, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForOpponent
	case YES, BattleFrontier_BattleArenaBattleRoom_EventScript_PauseChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleArenaBattleRoom_EventScript_AskRetireChallenge::
	message BattleFrontier_BattleArenaBattleRoom_Text_RetireFromChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForOpponent
	case 0, BattleFrontier_BattleArenaBattleRoom_EventScript_WarpToLobbyLost
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleArenaBattleRoom_EventScript_ContinueChallenge::
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaBattleRoom_Movement_WalkInPlaceRight
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaBattleRoom_Movement_WalkInPlaceRight
	waitmovement 0
	goto BattleFrontier_BattleArenaBattleRoom_EventScript_AnnounceTrainers
	waitstate
BattleFrontier_BattleArenaBattleRoom_EventScript_ReturnToLobbyWon::
	delay 60
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_WON
	warp MAP_BATTLE_FRONTIER_BATTLE_ARENA_LOBBY, 255, 7, 8
	waitstate

BattleFrontier_BattleArenaBattleRoom_EventScript_ReadyFor2ndOpponent::
	message BattleFrontier_BattleArenaBattleRoom_Text_ReadyFor2ndOpponent
	waitmessage
	return

BattleFrontier_BattleArenaBattleRoom_EventScript_ReadyFor3rdOpponent::
	message BattleFrontier_BattleArenaBattleRoom_Text_ReadyFor3rdOpponent
	waitmessage
	return

BattleFrontier_BattleArenaBattleRoom_EventScript_ReadyFor4thOpponent::
	message BattleFrontier_BattleArenaBattleRoom_Text_ReadyFor4thOpponent
	waitmessage
	return

BattleFrontier_BattleArenaBattleRoom_EventScript_ReadyFor5thOpponent::
	message BattleFrontier_BattleArenaBattleRoom_Text_ReadyFor5thOpponent
	waitmessage
	return

BattleFrontier_BattleArenaBattleRoom_EventScript_ReadyFor6thOpponent::
	message BattleFrontier_BattleArenaBattleRoom_Text_ReadyFor6thOpponent
	waitmessage
	return

BattleFrontier_BattleArenaBattleRoom_EventScript_ReadyFor7thOpponent::
	message BattleFrontier_BattleArenaBattleRoom_Text_ReadyFor7thOpponent
	waitmessage
	return

BattleFrontier_BattleArenaBattleRoom_EventScript_PauseChallenge::
	message BattleFrontier_BattleArenaBattleRoom_Text_SavingPleaseWait
	waitmessage
	arena_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

BattleFrontier_BattleArenaBattleRoom_EventScript_TycoonUpNext::
	compare VAR_TEMP_2, 1
	goto_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForTycoon
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_NowFaceTycoon, MSGBOX_DEFAULT
	setvar VAR_TEMP_2, 1
BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForTycoon::
	message BattleFrontier_BattleArenaBattleRoom_Text_PreparedForTycoon
	waitmessage
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForTycoonNoRecord
	multichoice 19, 4, MULTI_GO_ON_RECORD_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaBattleRoom_EventScript_BattleGreta
	case 1, BattleFrontier_BattleArenaBattleRoom_EventScript_AskRecordBattle
	case 2, BattleFrontier_BattleArenaBattleRoom_EventScript_AskPauseChallenge
	case 3, BattleFrontier_BattleArenaBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForTycoon

BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForTycoonNoRecord::
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaBattleRoom_EventScript_BattleGreta
	case 1, BattleFrontier_BattleArenaBattleRoom_EventScript_AskPauseChallenge
	case 2, BattleFrontier_BattleArenaBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaBattleRoom_EventScript_AskReadyForTycoon

BattleFrontier_BattleArenaBattleRoom_EventScript_BattleGreta::
	call BattleFrontier_EventScript_SetBrainObjectGfx
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaBattleRoom_Movement_WalkInPlaceRight
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaBattleRoom_Movement_WalkInPlaceRight
	waitmovement 0
	applymovement LOCALID_ANNOUNCER, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceDown
	playse SE_M_BELLY_DRUM
	waitse
	waitmovement 0
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_PlayerStepForward, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaBattleRoom_Movement_PlayerStepForwardLong
	waitmovement 0
	applymovement LOCALID_ANNOUNCER, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceDown
	playse SE_M_BELLY_DRUM
	waitse
	waitmovement 0
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_MakeWayForGreta, MSGBOX_DEFAULT
	closemessage
	addobject LOCALID_OPPONENT
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleArenaBattleRoom_Movement_GretaEnter
	waitmovement 0
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleArenaBattleRoom_Movement_OpponentStepForward
	waitmovement 0
	switch VAR_TEMP_F
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattleArenaBattleRoom_EventScript_IntroGretaGold
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattleArenaBattleRoom_EventScript_BattleGretaSilver
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattleArenaBattleRoom_EventScript_BattleGretaGold
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattleArenaBattleRoom_EventScript_BattleGretaSilver
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_GretaYoureChallenger, MSGBOX_DEFAULT
	closemessage
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleArenaBattleRoom_Movement_GretaLookAroundPlayer
	waitmovement 0
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_IsThatRight, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleArenaBattleRoom_Movement_GretaWalkBackToCenter
	waitmovement 0
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_YouLookWeakTakeThingsEasy, MSGBOX_DEFAULT
BattleFrontier_BattleArenaBattleRoom_EventScript_BattleGretaSilver::
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_IgniteMyPassionForBattle, MSGBOX_DEFAULT
	call BattleFrontier_BattleArenaBattleRoom_EventScript_StartArenaBattle
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_DefeatedGretaSilver
	goto BattleFrontier_BattleArenaBattleRoom_EventScript_DeclareOpponentWinner

BattleFrontier_BattleArenaBattleRoom_EventScript_DefeatedGretaSilver::
	call BattleFrontier_BattleArenaBattleRoom_EventScript_DeclarePlayerWinner
	frontier_getsymbols
	compare VAR_RESULT, 0
	goto_if_ne BattleFrontier_BattleArenaBattleRoom_EventScript_ReturnToLobbyWon
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleArenaBattleRoom_Movement_OpponentStepForwardLong
	waitmovement 0
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_GretaYoureToughAfterAll, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattleArenaBattleRoom_Text_ReceivedGutsSymbol
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_GoingToBeFunNextTime, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaBattleRoom_EventScript_ReturnToLobbyWon

BattleFrontier_BattleArenaBattleRoom_EventScript_IntroGretaGold::
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattleArenaBattleRoom_EventScript_BattleGretaGold
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_GretaLookingForwardToSeeingAgain, MSGBOX_DEFAULT
	closemessage
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleArenaBattleRoom_Movement_GretaLookAroundPlayer
	waitmovement 0
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_SoAreYouReady, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleArenaBattleRoom_Movement_GretaWalkBackToCenter
	waitmovement 0
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_WontAllowHalfheartedEffort, MSGBOX_DEFAULT
BattleFrontier_BattleArenaBattleRoom_EventScript_BattleGretaGold::
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_LetsGetThisStarted, MSGBOX_DEFAULT
	call BattleFrontier_BattleArenaBattleRoom_EventScript_StartArenaBattle
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_DefeatedGretaGold
	goto BattleFrontier_BattleArenaBattleRoom_EventScript_DeclareOpponentWinner

BattleFrontier_BattleArenaBattleRoom_EventScript_DefeatedGretaGold::
	call BattleFrontier_BattleArenaBattleRoom_EventScript_DeclarePlayerWinner
	frontier_getsymbols
	compare VAR_RESULT, 2
	goto_if_eq BattleFrontier_BattleArenaBattleRoom_EventScript_ReturnToLobbyWon
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleArenaBattleRoom_Movement_OpponentStepForwardLong
	waitmovement 0
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_GretaBlownAway, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattleArenaBattleRoom_Text_GutsSymbolTookGoldenShine
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_IfWeBattleAgainWontLose, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaBattleRoom_EventScript_ReturnToLobbyWon

BattleFrontier_BattleArenaBattleRoom_EventScript_StartArenaBattle::
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_SetKOTourneyBegin, MSGBOX_DEFAULT
	call BattleFrontier_BattleArenaBattleRoom_EventScript_DoArenaBattle
	return

BattleFrontier_BattleArenaBattleRoom_EventScript_DoArenaBattle::
	closemessage
	setvar VAR_TEMP_2, 0
	frontier_set FRONTIER_DATA_RECORD_DISABLED, FALSE
	special HealPlayerParty
	setvar VAR_0x8004, SPECIAL_BATTLE_ARENA
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	frontier_restorehelditems
	special HealPlayerParty
	frontier_resetsketch
	return

BattleFrontier_BattleArenaBattleRoom_EventScript_DeclarePlayerWinner:: @ 8257BA9
	applymovement LOCALID_ANNOUNCER, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceDown
	applymovement LOCALID_BLACK_BELT_1, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceDown
	applymovement LOCALID_BLACK_BELT_2, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceDown
	applymovement LOCALID_BLACK_BELT_3, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceUp
	applymovement LOCALID_BLACK_BELT_4, BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceUp
	playse SE_BANG
	waitse
	waitmovement 0
	msgbox BattleFrontier_BattleArenaBattleRoom_Text_WinnerIsPlayer, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_EventScript_IncrementWinStreak
	return

BattleFrontier_BattleArenaBattleRoom_Movement_PlayerEnter:
	walk_right
	walk_right
BattleFrontier_BattleArenaBattleRoom_Movement_PlayerStepForwardLong:
	walk_right
BattleFrontier_BattleArenaBattleRoom_Movement_PlayerStepForward:
	walk_right
	step_end

BattleFrontier_BattleArenaBattleRoom_Movement_PlayerWalkBackToLine:
	walk_left
	walk_left
	walk_in_place_fastest_right
	step_end

BattleFrontier_BattleArenaBattleRoom_Movement_WalkInPlaceLeft:
	walk_in_place_fastest_up
	step_end

BattleFrontier_BattleArenaBattleRoom_Movement_WalkInPlaceRight:
	walk_in_place_fastest_right
	step_end

BattleFrontier_BattleArenaBattleRoom_Movement_OpponentEnter:
	walk_left
	walk_left
BattleFrontier_BattleArenaBattleRoom_Movement_OpponentStepForwardLong:
	walk_left
BattleFrontier_BattleArenaBattleRoom_Movement_OpponentStepForward:
	walk_left
	step_end

BattleFrontier_BattleArenaBattleRoom_Movement_GretaEnter:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

BattleFrontier_BattleArenaBattleRoom_Movement_OpponentExit:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceDown:
	disable_jump_landing_ground_effect
	jump_in_place_down
	step_end

BattleFrontier_BattleArenaBattleRoom_Movement_JumpInPlaceUp:
	disable_jump_landing_ground_effect
	jump_in_place_up
	step_end

BattleFrontier_BattleArenaBattleRoom_Movement_WalkInPlaceDown:
	walk_in_place_fastest_down
	step_end

@ Unused, redundant
BattleFrontier_BattleArenaBattleRoom_Movement_WalkInPlaceRight2:
	walk_in_place_fastest_right
	step_end

BattleFrontier_BattleArenaBattleRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleArenaBattleRoom_EventScript_SetUpRoomObjects
	.2byte 0

BattleFrontier_BattleArenaBattleRoom_EventScript_SetUpRoomObjects:: @ 8257C16
	hideobjectat LOCALID_PLAYER, MAP_BATTLE_FRONTIER_BATTLE_ARENA_BATTLE_ROOM
	removeobject LOCALID_OPPONENT
	call BattleFrontier_BattleDomeBattleRoom_EventScript_SetPlayerGfx
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleDomeBattleRoom_Movement_SetInvisible
	setvar VAR_TEMP_1, 1
	end

BattleFrontier_BattleArenaBattleRoom_Movement_GretaLookAroundPlayer:
	walk_down
	walk_in_place_fastest_left
	delay_16
	delay_16
	delay_16
	delay_16
	walk_up
	walk_up
	walk_in_place_fastest_left
	step_end

BattleFrontier_BattleArenaBattleRoom_Movement_GretaWalkBackToCenter:
	walk_down
	walk_in_place_fastest_left
	step_end

BattleFrontier_BattleArenaBattleRoom_Text_PlayerStepForward:
	.string "심판: 트레이너 {PLAYER}!\n"
	.string "앞으로---!$"
	// しんぱん『トレ-ナ- {PLAYER}!\n
	// まえへ---!

BattleFrontier_BattleArenaBattleRoom_Text_OpponentStepForward:
	.string "심판: 트레이너 {STR_VAR_1}!\n"
	.string "앞으로---!$"
	// しんぱん『トレ-ナ- {STR_VAR_1}!\n
	// まえへ---!

BattleFrontier_BattleArenaBattleRoom_Text_SetKOTourneyBegin:
	.string "심판: 연승팀배틀!\n"
	.string "시작---!!$"
	// しんぱん『かちぬきチ-ムバトル!ｎ
	// はじめ---!!

BattleFrontier_BattleArenaBattleRoom_Text_WinnerIsPlayer:
	.string "심판: 승자는---!\n"
	.string "{PLAYER}!!$"
	// しんぱん『しょうしゃ---!ｎ
	// {PLAYER}!!

BattleFrontier_BattleArenaBattleRoom_Text_WinnerIsOpponent:
	.string "심판: 승자는---!\n"
	.string "{STR_VAR_1}!!$"
	// しんぱん『しょうしゃ---!ｎ
	// {STR_VAR_1}!!

BattleFrontier_BattleArenaBattleRoom_Text_MonsWillBeRestored:
	.string "포켓몬의 체력을\n"
	.string "회복시켜 드리겠습니다!$"
	// ポケモンの たいりょくをｎ
	// かいふく いたしますぞ!

BattleFrontier_BattleArenaBattleRoom_Text_ReadyFor2ndOpponent:
	.string "다음은 2명째 상대입니다!\n"
	.string "준비되셨습니까?$"
	// つぎは 2にんめの あいてですぞ!ｎ
	// じゅんびは よろしい ですかな?

BattleFrontier_BattleArenaBattleRoom_Text_ReadyFor3rdOpponent:
	.string "다음은 3명째 상대입니다!\n"
	.string "준비되셨습니까?$"
	// つぎは 3にんめの あいてですぞ!ｎ
	// じゅんびは よろしい ですかな?

BattleFrontier_BattleArenaBattleRoom_Text_ReadyFor4thOpponent:
	.string "다음은 4명째 상대입니다!\n"
	.string "준비되셨습니까?$"
	// つぎは 4にんめの あいてですぞ!ｎ
	// じゅんびは よろしい ですかな?

BattleFrontier_BattleArenaBattleRoom_Text_ReadyFor5thOpponent:
	.string "다음은 5명째 상대입니다!\n"
	.string "준비되셨습니까?$"
	// つぎは 5にんめの あいてですぞ!ｎ
	// じゅんびは よろしい ですかな?

BattleFrontier_BattleArenaBattleRoom_Text_ReadyFor6thOpponent:
	.string "다음은 6명째 상대입니다!\n"
	.string "준비되셨습니까?$"
	// つぎは 6にんめの あいてですぞ!ｎ
	// じゅんびは よろしい ですかな?

BattleFrontier_BattleArenaBattleRoom_Text_ReadyFor7thOpponent:
	.string "다음은 7명째 상대입니다!\n"
	.string "준비되셨습니까?$"
	// つぎは 7にんめの あいてですぞ!ｎ
	// じゅんびは よろしい ですかな?

BattleFrontier_BattleArenaBattleRoom_Text_SaveAndShutDown:
	.string "리포트를 작성하고\n"
	.string "중단할까요?$"
	// レポ-トを かいてｎ
	// しゅうりょう なされますかな?

BattleFrontier_BattleArenaBattleRoom_Text_RetireFromChallenge:
	.string "연승팀배틀의 도전을\n"
	.string "중단할까요?$"
	// かちぬきチ-ムバトルの ちょうせんをｎ
	// ちゅうし なされますかな?

BattleFrontier_BattleArenaBattleRoom_Text_SavingPleaseWait:
	.string "리포트를 작성하고 있습니다!\n"
	.string "잠시 기다려 주십시오$"
	// レポ-トを かいております!ｎ
	// しばし おまちくだされ!

BattleFrontier_BattleArenaBattleRoom_Text_RecordLastBattle:
	.string "지금의 승부를\n"
	.string "프런티어패스에 기록하겠습니까?$"
	// さきほどの たたかいをｎ
	// フロンティアパスに きろく されますかな?

BattleFrontier_BattleArenaBattleRoom_Text_NowFaceTycoon:
	.string "손님!\p"
	.string "당신의 실력은\n"
	.string "실로 굉장하군요!\n"
	.string "그러니 이쯤에서 한번\n"
	.string "우리들의 대장 아레나캡틴과\l"
	.string "한 수 부탁드립니다!$"
	// おきゃくじん!ｐ
	// あなたの じつりょくはｎ
	// じつに すさまじいで ございますな!ｐ
	// そこで ここらで ひとつｎ
	// われらが たいしょう アリ-ナキャプテンとｌ
	// おてあわせ いただき ましょう!

BattleFrontier_BattleArenaBattleRoom_Text_PreparedForTycoon:
	.string "아레나캡틴과의 승부!\n"
	.string "각오는 되셨습니까?$"
	// アリ-ナキャプテンとの しょうぶ!ｎ
	// かくごの ほうは よろしい ですかな?

BattleFrontier_BattleArenaBattleRoom_Text_MakeWayForGreta:
	.string "심판: 아레나캡틴! 나리님!\n"
	.string "입장하십니다---!$"
	// しんぱん『アリ-ナキャプテン! コゴミさま!ｎ
	// ごにゅうじょう---!

BattleFrontier_BattleArenaBattleRoom_Text_GretaYoureChallenger:
	.string "나리: 네엡! 잘 부탁해-!!\p"
	.string "... 라니 당신이 도전자?$"
	// コゴミ『ウィ-ッス! よろしく-!!ｐ
	// …… って あなたが ちょうせんしゃ?

BattleFrontier_BattleArenaBattleRoom_Text_IsThatRight:
	.string "흐-음... 헤-에... 헤에에에...$"
	// ふ-ん…… へ-え…… へえぇぇ……

BattleFrontier_BattleArenaBattleRoom_Text_YouLookWeakTakeThingsEasy:
	.string "뭐랄까- 솔직히 말해서\n"
	.string "은근 약할 것 같은 느낌인데-\l"
	.string "나하고 배틀해도\l"
	.string "괜찮으려나-?\p"
	.string "으으-음...\n"
	.string "뭐 좋아!\n"
	.string "곧고 가볍게 솜씨 좀 봐야겠어!$"
	// なんて いうか- しょうじき いってｎ
	// かなり よわっちい かんじ なんだけど-ｌ
	// アタシと たたかってもｌ
	// だいじょうぶ なのかな-?ｐ
	// ぅう-ん……ｐ
	// まあ いいかっ!ｎ
	// まずは かる-く おてなみ はいけんねっ!

BattleFrontier_BattleArenaBattleRoom_Text_IgniteMyPassionForBattle:
	.string "자!\n"
	.string "내 투지에 불을 붙여줘!$"
	// さあっ!ｎ
	// アタシの とうしに ひを つけてねっ!

BattleFrontier_BattleArenaBattleRoom_Text_GretaYoureToughAfterAll:
	.string "나리: 어머 잠깐만-!\n"
	.string "당신 엄청나게 강하잖아-!!\l"
	.string "마음에 들었어! 프런티어패스 줘 봐!$"
	// コゴミ『やだ ちょっと-!ｎ
	// あなた ぜんぜん つよい じゃん-!ｌ
	// きにいった! フロンティアパス かしてっ!

BattleFrontier_BattleArenaBattleRoom_Text_ReceivedGutsSymbol:
	.string "프런티어패스에\n"
	.string "거츠심볼이 새겨졌다!$"
	// フロンティアパスにｎ
	// ガッツシンボルが きざまれた!

BattleFrontier_BattleArenaBattleRoom_Text_GoingToBeFunNextTime:
	.string "으-음!\p"
	.string "다음에 만날 때가\n"
	.string "기대되기 시작했어-!$"
	// ぅう-ん!ｐ
	// つぎに あえるときがｎ
	// たのしみに なって きたな-!

BattleFrontier_BattleArenaBattleRoom_Text_GretaLookingForwardToSeeingAgain:
	.string "나리: 네-엡! 오랜만이네-!\n"
	.string "드디어 여기까지 이겨 왔구나!\p"
	.string "늦어서 걱정했단 말야-!\n"
	.string "당신과 만나는 걸 엄-청나게!\l"
	.string "기대하고 있었으니까-!!$"
	// コゴミ『ウィ-ッス! ごぶさた-!ｎ
	// や-っと ここまで かちぬいて きたね!ｐ
	// おそいから しんぱい しちゃったよ-っ!ｎ
	// あなたと あえるの もの すっご-くっ!ｌ
	// たのしみに してたん だからね-っ!!

BattleFrontier_BattleArenaBattleRoom_Text_SoAreYouReady:
	.string "...... ...... ...... ...... 그러니까 준비됐어?$"
	// …… …… …… …… だから い-い?

BattleFrontier_BattleArenaBattleRoom_Text_WontAllowHalfheartedEffort:
	.string "어중간한 배틀은 용서하지 않을 거야\n"
	.string "각오하고 있으라고!!$"
	// はんぱな たたかいじゃ ゆるさないっ!!ｎ
	// かくご しといてねっ!!

BattleFrontier_BattleArenaBattleRoom_Text_LetsGetThisStarted:
	.string "이봐 심판!\n"
	.string "얼른 시작하도록 해!!$"
	// ほらっ しんぱん!ｎ
	// さっさと はじめなさいっ!!

BattleFrontier_BattleArenaBattleRoom_Text_GretaBlownAway:
	.string "나리: 아---! 정말---!!\n"
	.string "얼른 프런티어패스 줘 봐!$"
	// コゴミ『あ---っ! も---っ!!ｎ
	// さっさと フロンティアパス かしてよっ!

BattleFrontier_BattleArenaBattleRoom_Text_GutsSymbolTookGoldenShine:
	.string "거츠심볼이\n"
	.string "금색으로 빛났다!$"
	// ガッツシンボルがｎ
	// きんいろに かがやいた!

BattleFrontier_BattleArenaBattleRoom_Text_IfWeBattleAgainWontLose:
	.string "으아-아!! 분하다---아!!\p"
	.string "다음에 배틀하게 된다면\n"
	.string "절-대로 지지 않을 거얏! 바이바이!$"
	// むき-っ!! くやし---っ!!ｐ
	// こんど たたかう ことが あったらｎ
	// ぜ-ったい まけない からっ! バイバイっ!
