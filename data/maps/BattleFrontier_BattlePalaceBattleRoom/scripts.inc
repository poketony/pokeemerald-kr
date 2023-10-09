.set LOCALID_PLAYER, 1
.set LOCALID_OPPONENT, 2
.set LOCALID_ATTENDANT, 3
.set LOCALID_DUSCLOPS, 4
.set LOCALID_AZURILL, 5

BattleFrontier_BattlePalaceBattleRoom_MapScripts:: @ 824F815
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePalaceBattleRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePalaceBattleRoom_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePalaceBattleRoom_OnWarp
	.byte 0

	@ On this map the player (OBJ_EVENT_ID_PLAYER) is hidden
	@ The player is represented instead by LOCALID_PLAYER, which has the gfx id VAR_OBJ_GFX_ID_0
	@ The opponent is represented by LOCALID_OPPONENT, which has the gfx id VAR_OBJ_GFX_ID_1

BattleFrontier_BattlePalaceBattleRoom_OnTransition: @ 824F825
	frontier_settrainers
	call BattleFrontier_BattlePalaceBattleRoom_EventScript_SetPlayerGfx
	end

BattleFrontier_BattlePalaceBattleRoom_EventScript_SetPlayerGfx:: @ 824F833
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_SetPlayerGfxMale
	compare VAR_RESULT, FEMALE
	goto_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_SetPlayerGfxFemale
	return

@ The opponent's gfx are set to the players by default
BattleFrontier_BattlePalaceBattleRoom_EventScript_SetPlayerGfxMale:: @ 824F84B
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	return

BattleFrontier_BattlePalaceBattleRoom_EventScript_SetPlayerGfxFemale:: @ 824F856
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	return

BattleFrontier_BattlePalaceBattleRoom_OnFrame: @ 824F861
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattlePalaceBattleRoom_EventScript_EnterRoom
	.2byte 0

BattleFrontier_BattlePalaceBattleRoom_EventScript_EnterRoom:: @ 824F86B
	showobjectat LOCALID_PLAYER, MAP_BATTLE_FRONTIER_BATTLE_PALACE_BATTLE_ROOM
	frontier_get FRONTIER_DATA_BATTLE_NUM
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_BeginChallenge
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceBattleRoom_Movement_PlayerReturnToChallenge
	waitmovement 0
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePalaceBattleRoom_Movement_FaceDown
	setvar VAR_TEMP_2, 1
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattlePalaceBattleRoom_EventScript_BeginChallenge:: @ 824F8B5
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceBattleRoom_Movement_PlayerEnterRoom
	waitmovement 0
BattleFrontier_BattlePalaceBattleRoom_EventScript_NextOpponentEnter:: @ 824F8BF
	tower_setopponent
	addobject LOCALID_OPPONENT
	applymovement LOCALID_OPPONENT, BattleFrontier_BattlePalaceBattleRoom_Movement_OpponentEnter
	waitmovement 0
	palace_getopponentintro
	msgbox gStringVar4, MSGBOX_DEFAULT
	waitmessage
	call BattleFrontier_BattlePalaceBattleRoom_EventScript_DoPalaceBattle
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePalaceBattleRoom_EventScript_DefeatedOpponent
BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobbyLost:: @ 824F8FA
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	goto BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobby

BattleFrontier_BattlePalaceBattleRoom_EventScript_DefeatedOpponent:: @ 824F911
	call BattleFrontier_EventScript_IncrementWinStreak
	frontier_get FRONTIER_DATA_BATTLE_NUM
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	switch VAR_RESULT
	case 7, BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobbyWon
	applymovement LOCALID_OPPONENT, BattleFrontier_BattlePalaceBattleRoom_Movement_OpponentExit
	waitmovement 0
	removeobject LOCALID_OPPONENT
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceBattleRoom_Movement_FaceUp
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePalaceBattleRoom_Movement_FaceDown
	waitmovement 0
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_LetMeRestoreYourMons, MSGBOX_DEFAULT
	special LoadPlayerParty
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForOpponent:: @ 824F98A
	frontier_getbrainstatus
	copyvar VAR_TEMP_F, VAR_RESULT
	compare VAR_RESULT, FRONTIER_BRAIN_NOT_READY
	goto_if_ne BattleFrontier_BattlePalaceBattleRoom_EventScript_MavenUpNext
	frontier_get FRONTIER_DATA_BATTLE_NUM
	compare VAR_RESULT, 1
	call_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_ReadyFor2ndOpponent
	compare VAR_RESULT, 2
	call_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_ReadyFor3rdOpponent
	compare VAR_RESULT, 3
	call_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_ReadyFor4thOpponent
	compare VAR_RESULT, 4
	call_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_ReadyFor5thOpponent
	compare VAR_RESULT, 5
	call_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_ReadyFor6thOpponent
	compare VAR_RESULT, 6
	call_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_ReadyFor7thOpponent
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForOpponentNoRecord
	multichoice 19, 4, MULTI_GO_ON_RECORD_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceBattleRoom_EventScript_ContinueChallenge
	case 1, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskRecordBattle
	case 2, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskPauseChallenge
	case 3, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForOpponentNoRecord:: @ 824FA42
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceBattleRoom_EventScript_ContinueChallenge
	case 1, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskPauseChallenge
	case 2, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattlePalaceBattleRoom_EventScript_AskRecordBattle:: @ 824FA78
	message BattleFrontier_BattlePalaceBattleRoom_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForOpponent
	case 0, BattleFrontier_BattlePalaceBattleRoom_EventScript_RecordBattle
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattlePalaceBattleRoom_EventScript_RecordBattle:: @ 824FAAA
	call BattleFrontier_EventScript_SaveBattle
	goto BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattlePalaceBattleRoom_EventScript_AskPauseChallenge:: @ 824FAB4
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_SaveAndQuitGame, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForOpponent
	case YES, BattleFrontier_BattlePalaceBattleRoom_EventScript_PauseChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattlePalaceBattleRoom_EventScript_AskRetireChallenge:: @ 824FAE2
	message BattleFrontier_BattlePalaceBattleRoom_Text_WishToQuitChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForOpponent
	case 0, BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobbyLost
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattlePalaceBattleRoom_EventScript_ContinueChallenge:: @ 824FB14
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceBattleRoom_Movement_FaceRight
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePalaceBattleRoom_Movement_FaceRight
	closemessage
	goto BattleFrontier_BattlePalaceBattleRoom_EventScript_NextOpponentEnter

BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobbyWon:: @ 824FB28
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_WON
	goto BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobby

BattleFrontier_BattlePalaceBattleRoom_EventScript_PauseChallenge:: @ 824FB3F
	message BattleFrontier_BattlePalaceBattleRoom_Text_SavingData
	waitmessage
	palace_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

BattleFrontier_BattlePalaceBattleRoom_EventScript_MavenUpNext:: @ 824FB61
	compare VAR_TEMP_2, 1
	goto_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForMaven
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_ChallengingPalaceMaven, MSGBOX_DEFAULT
	setvar VAR_TEMP_2, 1
BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForMaven:: @ 824FB79
	message BattleFrontier_BattlePalaceBattleRoom_Text_ReadyForPalaceMaven
	waitmessage
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForMavenNoRecord
	multichoice 19, 4, MULTI_GO_ON_RECORD_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceBattleRoom_EventScript_BattleSpenser
	case 1, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskRecordBattle
	case 2, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskPauseChallenge
	case 3, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForMaven

BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForMavenNoRecord:: @ 824FBD0
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceBattleRoom_EventScript_BattleSpenser
	case 1, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskPauseChallenge
	case 2, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceBattleRoom_EventScript_AskReadyForMaven

BattleFrontier_BattlePalaceBattleRoom_EventScript_BattleSpenser:: @ 824FC06
	call BattleFrontier_EventScript_SetBrainObjectGfx
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_AnnounceArrivalOfSpenser, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceBattleRoom_Movement_FaceRight
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePalaceBattleRoom_Movement_FaceRight
	setobjectxyperm LOCALID_OPPONENT, 15, 1
	addobject LOCALID_OPPONENT
	hideobjectat LOCALID_OPPONENT, MAP_BATTLE_FRONTIER_BATTLE_PALACE_BATTLE_ROOM
	setobjectxy LOCALID_OPPONENT, 13, 1
	setobjectxyperm LOCALID_OPPONENT, 13, 1
	applymovement LOCALID_DUSCLOPS, BattleFrontier_BattlePalaceBattleRoom_Movement_DusclopsEnter
	applymovement LOCALID_AZURILL, BattleFrontier_BattlePalaceBattleRoom_Movement_AzurillEnter
	applymovement LOCALID_OPPONENT, BattleFrontier_BattlePalaceBattleRoom_Movement_SpenserEnter
	waitmovement 0
	switch VAR_TEMP_F
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattlePalaceBattleRoom_EventScript_IntroSpenserGold
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattlePalaceBattleRoom_EventScript_BattleSpenserSilver
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattlePalaceBattleRoom_EventScript_BattleSpenserGold
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattlePalaceBattleRoom_EventScript_BattleSpenserSilver
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_SpenserFirstIntro, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
BattleFrontier_BattlePalaceBattleRoom_EventScript_BattleSpenserSilver:: @ 824FCAA
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_ProveYourBondWithMons, MSGBOX_DEFAULT
	call BattleFrontier_BattlePalaceBattleRoom_EventScript_DoPalaceBattle
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_DefeatedSpenserSilver
	goto BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobbyLost

BattleFrontier_BattlePalaceBattleRoom_EventScript_DefeatedSpenserSilver:: @ 824FCC7
	palace_incrementstreak
	frontier_getsymbols
	compare VAR_RESULT, 0
	goto_if_ne BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobbyWon
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_SpenserPostSilverBattle, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceBattleRoom_Movement_FaceUp
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePalaceBattleRoom_Movement_FaceDown
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_LetsSeeFrontierPass, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattlePalaceBattleRoom_Text_ReceivedSpiritsSymbol
	waitmessage
	waitfanfare
	frontier_givesymbol
	applymovement LOCALID_OPPONENT, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	applymovement LOCALID_ATTENDANT, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_SpenserAwaitNextTime, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobbyWon

BattleFrontier_BattlePalaceBattleRoom_EventScript_IntroSpenserGold:: @ 824FD3A
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattlePalaceBattleRoom_EventScript_BattleSpenserGold
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_SpenserThisTimeWontHoldBack, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
BattleFrontier_BattlePalaceBattleRoom_EventScript_BattleSpenserGold:: @ 824FD67
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_Kaaah, MSGBOX_DEFAULT
	call BattleFrontier_BattlePalaceBattleRoom_EventScript_DoPalaceBattle
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_DefeatedSpenserGold
	goto BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobbyLost

BattleFrontier_BattlePalaceBattleRoom_EventScript_DefeatedSpenserGold:: @ 824FD84
	palace_incrementstreak
	frontier_getsymbols
	compare VAR_RESULT, 2
	goto_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobbyWon
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_SpenserYourTeamIsAdmirable, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceBattleRoom_Movement_FaceUp
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePalaceBattleRoom_Movement_FaceDown
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_HurryWithFrontierPass, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattlePalaceBattleRoom_Text_SpiritsSymbolTookGoldenShine
	waitmessage
	waitfanfare
	frontier_givesymbol
	applymovement LOCALID_OPPONENT, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	applymovement LOCALID_ATTENDANT, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox BattleFrontier_BattlePalaceBattleRoom_Text_SpenserComeSeeMeAgain, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobbyWon

BattleFrontier_BattlePalaceBattleRoom_EventScript_DoPalaceBattle:: @ 824FDF7
	closemessage
	setvar VAR_TEMP_2, 0
	frontier_set FRONTIER_DATA_RECORD_DISABLED, FALSE
	special HealPlayerParty
	setvar VAR_0x8004, SPECIAL_BATTLE_PALACE
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	frontier_restorehelditems
	special HealPlayerParty
	frontier_resetsketch
	return

BattleFrontier_BattlePalaceBattleRoom_OnWarp: @ 824FE34
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePalaceBattleRoom_EventScript_SetUpRoomObjects
	.2byte 0

BattleFrontier_BattlePalaceBattleRoom_EventScript_SetUpRoomObjects:: @ 824FE3E
	hideobjectat LOCALID_PLAYER, MAP_BATTLE_FRONTIER_BATTLE_PALACE_BATTLE_ROOM
	call BattleFrontier_BattlePalaceBattleRoom_EventScript_SetPlayerGfx
	setvar VAR_TEMP_1, 1
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePalaceBattleRoom_Movement_SetInvisible
	removeobject LOCALID_OPPONENT
	applymovement LOCALID_DUSCLOPS, BattleFrontier_BattlePalaceBattleRoom_Movement_SetInvisible
	applymovement LOCALID_AZURILL, BattleFrontier_BattlePalaceBattleRoom_Movement_SetInvisible
	end

BattleFrontier_BattlePalaceBattleRoom_EventScript_ReadyFor2ndOpponent:: @ 824FE66
	message BattleFrontier_BattlePalaceBattleRoom_Text_PreparedFor2ndOpponent
	waitmessage
	return

BattleFrontier_BattlePalaceBattleRoom_EventScript_ReadyFor3rdOpponent:: @ 824FE6D
	message BattleFrontier_BattlePalaceBattleRoom_Text_PreparedFor3rdOpponent
	waitmessage
	return

BattleFrontier_BattlePalaceBattleRoom_EventScript_ReadyFor4thOpponent:: @ 824FE74
	message BattleFrontier_BattlePalaceBattleRoom_Text_PreparedFor4thOpponent
	waitmessage
	return

BattleFrontier_BattlePalaceBattleRoom_EventScript_ReadyFor5thOpponent:: @ 824FE7B
	message BattleFrontier_BattlePalaceBattleRoom_Text_PreparedFor5thOpponent
	waitmessage
	return

BattleFrontier_BattlePalaceBattleRoom_EventScript_ReadyFor6thOpponent:: @ 824FE82
	message BattleFrontier_BattlePalaceBattleRoom_Text_PreparedFor6thOpponent
	waitmessage
	return

BattleFrontier_BattlePalaceBattleRoom_EventScript_ReadyFor7thOpponent:: @ 824FE89
	message BattleFrontier_BattlePalaceBattleRoom_Text_PreparedFor7thOpponent
	waitmessage
	return

BattleFrontier_BattlePalaceBattleRoom_Movement_SetInvisible: @ 824FE90
	set_invisible
	step_end

BattleFrontier_BattlePalaceBattleRoom_Movement_PlayerEnterRoom: @ 824FE92
	set_visible
	walk_up
	walk_up
	walk_up
	walk_up
BattleFrontier_BattlePalaceBattleRoom_Movement_FaceRight: @ 824FE97
	face_right
	step_end

BattleFrontier_BattlePalaceBattleRoom_Movement_FaceUp: @ 824FE99
	face_up
	step_end

BattleFrontier_BattlePalaceBattleRoom_Movement_PlayerReturnToChallenge: @ 824FE9B
	set_visible
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePalaceBattleRoom_Movement_OpponentEnter: @ 824FEA1
	walk_down
	walk_down
	walk_down
	walk_down
	face_left
	step_end

BattleFrontier_BattlePalaceBattleRoom_Movement_OpponentExit: @ 824FEA7
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePalaceBattleRoom_Movement_FaceDown: @ 824FEAC
	face_down
	step_end

BattleFrontier_BattlePalaceBattleRoom_Movement_UnusedOpponentEnter1: @ 824FEAE
	set_visible
	walk_slow_down
	walk_slow_down
	face_left
	step_end

BattleFrontier_BattlePalaceBattleRoom_Movement_UnusedOpponentEnter2: @ 824FEB3
	set_visible
	walk_slow_down
	step_end

BattleFrontier_BattlePalaceBattleRoom_Movement_UnusedOpponentEnter3: @ 824FEB6
	walk_slow_down
	walk_slow_down
	walk_slow_down
	face_left
	step_end

BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobby:: @ 824FEBB
	copyvar VAR_RESULT, VAR_FRONTIER_BATTLE_MODE
	compare VAR_RESULT, FRONTIER_MODE_DOUBLES
	goto_if_eq BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobbyDoubles
	warp MAP_BATTLE_FRONTIER_BATTLE_PALACE_LOBBY, 255, 5, 7
	waitstate
	end

BattleFrontier_BattlePalaceBattleRoom_EventScript_WarpToLobbyDoubles:: @ 824FED5
	warp MAP_BATTLE_FRONTIER_BATTLE_PALACE_LOBBY, 255, 19, 7
	waitstate
	end

BattleFrontier_BattlePalaceBattleRoom_Movement_DusclopsEnter: @ 824FEDF
	delay_16
	delay_16
	set_visible
	walk_down
	walk_right
	walk_down
	walk_in_place_fastest_left
	step_end

BattleFrontier_BattlePalaceBattleRoom_Movement_AzurillEnter: @ 824FEE7
	set_visible
	walk_fast_down
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_in_place_fastest_left
	delay_16
	step_end

BattleFrontier_BattlePalaceBattleRoom_Movement_SpenserEnter: @ 824FEF2
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	set_visible
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	face_left
	step_end

BattleFrontier_BattlePalaceBattleRoom_Text_LetMeRestoreYourMons: @ 824FF00
	.string "훌륭하구먼...\n"
	.string "포켓몬을 회복시켜 주겠네...$"
	// おみごと……ｎ
	// ポケモンを かいふくして やろう……

BattleFrontier_BattlePalaceBattleRoom_Text_PreparedFor2ndOpponent: @ 824FF28
	.string "다음은 2번째 상대라네\n"
	.string "준비는 되었는가?$"
	// つぎは 2にんめの あいて だがｎ
	// じゅんびは よろしいか?

BattleFrontier_BattlePalaceBattleRoom_Text_PreparedFor3rdOpponent: @ 824FF54
	.string "다음은 3번째 상대라네\n"
	.string "준비는 되었는가?$"
	// つぎは 3にんめの あいて だがｎ
	// じゅんびは よろしいか?

BattleFrontier_BattlePalaceBattleRoom_Text_PreparedFor4thOpponent: @ 824FF80
	.string "다음은 4번째 상대라네\n"
	.string "준비는 되었는가?$"
	// つぎは 4にんめの あいて だがｎ
	// じゅんびは よろしいか?

BattleFrontier_BattlePalaceBattleRoom_Text_PreparedFor5thOpponent: @ 824FFAC
	.string "다음은 5번째 상대라네\n"
	.string "준비는 되었는가?$"
	// つぎは 5にんめの あいて だがｎ
	// じゅんびは よろしいか?

BattleFrontier_BattlePalaceBattleRoom_Text_PreparedFor6thOpponent: @ 824FFD8
	.string "다음은 6번째 상대라네\n"
	.string "준비는 되었는가?$"
	// つぎは 6にんめの あいて だがｎ
	// じゅんびは よろしいか?

BattleFrontier_BattlePalaceBattleRoom_Text_PreparedFor7thOpponent: @ 8250004
	.string "다음은 7번째 상대라네\n"
	.string "준비는 되었는가?$"
	// つぎは 7にんめの あいて だがｎ
	// じゅんびは よろしいか?

BattleFrontier_BattlePalaceBattleRoom_Text_SaveAndQuitGame: @ 8250030
	.string "리포트를 작성하고 종료할 텐가?$"
	// レポ-トを かいて しゅうりょう するか?

BattleFrontier_BattlePalaceBattleRoom_Text_WishToQuitChallenge: @ 825005A
	.string "도전을 중단할 텐가?$"
	// ちょうせんを ちゅうし するのか?

BattleFrontier_BattlePalaceBattleRoom_Text_SavingData: @ 825007E
	.string "리포트를 작성 중이라네...\n"
	.string "잠시 기다려 주게...$"
	// レポ-トを かいておる……ｎ
	// しばし またれよ……

BattleFrontier_BattlePalaceBattleRoom_Text_RecordLastMatch: @ 825009E
	.string "지금의 배틀을\n"
	.string "프런티어패스에 기록하겠나?$"
	// さきほどの たたかいをｎ
	// フロンティアパスに きろく するか?

BattleFrontier_BattlePalaceBattleRoom_Text_ChallengingPalaceMaven: @ 82500DD
	.string "자 그럼...\p"
	.string "지금까지 연승해 온 자네는\n"
	.string "우리들의 주인 팰리스가디언께\l"
	.string "도전할 자격을 얻었다네...$"
	// さて……ｐ
	// ここまで かちぬいた おぬしはｎ
	// われらが あるじ パレスガ-ディアンにｌ
	// ちょうせんする しかくを てにした……

BattleFrontier_BattlePalaceBattleRoom_Text_ReadyForPalaceMaven: @ 825014A
	.string "팰리스가디언을 부르겠네\n"
	.string "...각오는 되었는가?$"
	// パレスガ-ディアンを およびするｎ
	// ……かくごは よいか?

BattleFrontier_BattlePalaceBattleRoom_Text_AnnounceArrivalOfSpenser: @ 825017C
	.string "팰리스가디언 우근님---!\n"
	.string "입장하십니다---!!$"
	// パレスガ-ディアン ウコンさま---!ｎ
	// ごらいでん---!!

BattleFrontier_BattlePalaceBattleRoom_Text_SpenserFirstIntro: @ 82501C1
	.string "우근: 이 몸\n"
	.string "항상 포켓몬과 함께하리!\p"
	.string "이 마음\n"
	.string "항상 포켓몬과 함께하리!\p"
	.string "젊은 트레이너여!!\n"
	.string "자네는 포켓몬을\l"
	.string "믿고 있는가?\p"
	.string "자네는 포켓몬을\n"
	.string "계속 믿어나갈 수 있는가!\p"
	.string "약한 유대감으로는\n"
	.string "내 형제를 이길 수 없다!!$"
	// ウコン『わが みｎ
	// つねに ポケモンと ありっ!ｐ
	// わが こころｎ
	// つねに ポケモンと ありっ!ｐ
	// わかき トレ-ナ-よ!!ｎ
	// きさまは ポケモンをｌ
	// しんじて おるか?ｐ
	// きさまは ポケモンをｎ
	// しんじぬく ことが できるかっ!ｐ
	// もろき しんらいの きずな ではｎ
	// わが きょうだい には かてん!!

BattleFrontier_BattlePalaceBattleRoom_Text_ProveYourBondWithMons: @ 82502C4
	.string "포켓몬과의 유대감!!\n"
	.string "여기에 보여 봐라!!$"
	// ポケモンとの きずな!!ｎ
	// ここに しめせぇい!!

BattleFrontier_BattlePalaceBattleRoom_Text_SpenserPostSilverBattle: @ 82502FF
	.string "우근: 크하하핫!\p"
	.string "역시 허세는 안 통하는군!!\n"
	.string "겁줘서 미안했네!!\p"
	.string "이봐! 그걸 가져오게!$"
	// ウコン『ぐわはっはっ!ｐ
	// やはり ハッタリ なんぞ きかんか!!ｎ
	// おどしたり して わるかったのぅ!!ｐ
	// お-い! あれを!

BattleFrontier_BattlePalaceBattleRoom_Text_LetsSeeFrontierPass: @ 825036D
	.string "이런이런 그대로 위엄을\n"
	.string "유지해 주셨으면 좋았을 텐데...\p"
	.string "이보게! 프런티어패스를 줘보게나!$"
	// やれやれ あのまま いげんを たもってｎ
	// おいて くだされば よい ものを……ｐ
	// おい! フロンティアパスを かさんか!

BattleFrontier_BattlePalaceBattleRoom_Text_ReceivedSpiritsSymbol: @ 82503DC
	.string "프런티어패스에\n"
	.string "스피릿심볼이 새겨졌다!$"
	// フロンティアパスにｎ
	// スピリットシンボルが きざまれた!

BattleFrontier_BattlePalaceBattleRoom_Text_SpenserAwaitNextTime: @ 8250412
	.string "우근: 자네의 포켓몬들은\n"
	.string "정말 맑은 눈을 하고 있군!\p"
	.string "다음을 기대하고 있겠네!$"
	// ウコン『おまえの ポケモンたちはｎ
	// まことに すんだ ひとみを しとる!ｐ
	// つぎの きかいを たのしみに しとるぞ!

BattleFrontier_BattlePalaceBattleRoom_Text_SpenserThisTimeWontHoldBack: @ 8250485
	.string "우근: 크하하핫!\n"
	.string "여기까지 이겨왔단 말인가!\p"
	.string "자넨 포켓몬들과\n"
	.string "정말 좋은 관계를\l"
	.string "맺은 것 같구먼!\p"
	.string "음!\p"
	.string "그렇다면 이번엔 우리도\n"
	.string "허세나 적당히 봐주는 건\l"
	.string "전부 그만두도록 하지!\p"
	.string "알았나? 각오하거라!!$"
	// ウコン『ぐわはっはっ!ｎ
	// ここまで かちぬいて きおったか!ｐ
	// おまえは ポケモン たちとｎ
	// まことに ええ かんけいをｌ
	// きずいて おるよう だな!ｐ
	// うむ!ｐ
	// ほいじゃあ こんどは わしらもｎ
	// ハッタリや てかげんはｌ
	// いっさい ぬきで いくと しよう!ｐ
	// ええか? かくご せい!!

BattleFrontier_BattlePalaceBattleRoom_Text_Kaaah: @ 8250572
	.string "...... ...... ...... 카-악!!!$"
	// …… …… …… か-っ!!!

BattleFrontier_BattlePalaceBattleRoom_Text_SpenserYourTeamIsAdmirable: @ 825057E
	.string "우근: 거 참 정말로 해냈구먼!!\n"
	.string "전력을 다한 내 형제가\l"
	.string "지다니 말이야!\p"
	.string "이야- 자네들은 정말 대단하군!\n"
	.string "이보게-! 빨리 그걸 가져오게!$"
	// ウコン『いやはや よう やったわ!!ｎ
	// ぜんりょくの わが きょうだいがｌ
	// はが たたん とは なぁ!ｐ
	// いや- おまえらは まことに すんばらしい!ｎ
	// お-いっ! はやく あれを!!

BattleFrontier_BattlePalaceBattleRoom_Text_HurryWithFrontierPass: @ 8250629
	.string "정말 이곳의 체면은\n"
	.string "생각해 주지 않는 분이시군...\p"
	.string "에잇! 자네!!\n"
	.string "빨리 프런티어패스를 줘보게!$"
	// ったく ここの イメ-ジと いうのをｎ
	// かんがえて くれない おかた だ……ｐ
	// ええい! おまえ!!ｎ
	// さっさと フロンティアパスを かさんか!

BattleFrontier_BattlePalaceBattleRoom_Text_SpiritsSymbolTookGoldenShine: @ 8250699
	.string "스피릿심볼이\n"
	.string "금색으로 빛났다!$"
	// スピリットシンボルがｎ
	// きんいろに かがやいた!

BattleFrontier_BattlePalaceBattleRoom_Text_SpenserComeSeeMeAgain: @ 82506C4
	.string "우근: 크하하핫!\p"
	.string "앞으로도 가끔씩 찾아오거라!\n"
	.string "나도 형제도 기다리고 있을 테니!!$"
	// ウコン『ぐわはっはっ!ｐ
	// これからも ときどき あそびに こいよ!ｎ
	// わしも きょうだいも まっとる からな!!
