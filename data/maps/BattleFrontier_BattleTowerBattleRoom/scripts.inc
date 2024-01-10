.set LOCALID_OPPONENT, 1
.set LOCALID_ATTENDANT_1, 2
.set LOCALID_ATTENDANT_2, 3

BattleFrontier_BattleTowerBattleRoom_MapScripts:: @ 8241B40
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerBattleRoom_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerBattleRoom_OnWarp
	.byte 0

BattleFrontier_BattleTowerBattleRoom_OnWarp: @ 8241B4B
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerBattleRoom_EventScript_SetUpObjects
	.2byte 0

BattleFrontier_BattleTowerBattleRoom_EventScript_SetUpObjects:: @ 8241B55
	setvar VAR_TEMP_1, 1
	applymovement LOCALID_ATTENDANT_2, BattleFrontier_BattleTowerBattleRoom_Movement_SetInvisible
	end

BattleFrontier_BattleTowerBattleRoom_OnFrame: @ 8241B62
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattleTowerBattleRoom_EventScript_EnterRoom
	.2byte 0

BattleFrontier_BattleTowerBattleRoom_EventScript_EnterRoom:: @ 8241B6C
	setvar VAR_TEMP_0, 1
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerBattleRoom_Movement_PlayerEnter
	waitmovement 0
	frontier_get FRONTIER_DATA_BATTLE_NUM
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattleTowerBattleRoom_EventScript_OpponentEnter
	applymovement LOCALID_ATTENDANT_1, BattleFrontier_BattleTowerBattleRoom_Movement_AttendantApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerBattleRoom_Movement_PlayerFaceAttendant
	waitmovement 0
	setvar VAR_TEMP_2, 1
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleTowerBattleRoom_EventScript_OpponentEnter:: @ 8241BC3
	tower_setopponent
	addobject LOCALID_OPPONENT
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleTowerBattleRoom_Movement_OpponentEnter
	waitmovement 0
	tower_getopponentintro 0
	msgbox gStringVar4, MSGBOX_DEFAULT
	waitmessage
	call BattleFrontier_BattleTowerBattleRoom_EventScript_DoTowerBattle
	switch VAR_RESULT
	case B_OUTCOME_WON, BattleFrontier_BattleTowerBattleRoom_EventScript_DefeatedOpponent
BattleFrontier_BattleTower_EventScript_WarpToLobbyLost:: @ 8241C03
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	tower_set TOWER_DATA_LVL_MODE
	setvar VAR_0x8004, FANCOUNTER_USED_BATTLE_TOWER
	special Script_TryGainNewFanFromCounter
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobby

BattleFrontier_BattleTowerBattleRoom_EventScript_DefeatedOpponent:: @ 8241C2F
	call BattleFrontier_EventScript_IncrementWinStreak
	tower_setbattlewon
	switch VAR_RESULT
	case 7, BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyWon
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleTowerBattleRoom_Movement_OpponentExit
	waitmovement 0
	removeobject LOCALID_OPPONENT
	frontier_getbrainstatus
	compare VAR_RESULT, FRONTIER_BRAIN_NOT_READY
	call_if_ne BattleFrontier_BattleTowerBattleRoom_EventScript_SecondAttendantEnter
	applymovement LOCALID_ATTENDANT_1, BattleFrontier_BattleTowerBattleRoom_Movement_AttendantApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerBattleRoom_Movement_PlayerFaceAttendant
	waitmovement 0
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_RestoreMonsToFullHealth, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent:: @ 8241C8F
	frontier_getbrainstatus
	copyvar VAR_TEMP_F, VAR_RESULT
	compare VAR_RESULT, FRONTIER_BRAIN_NOT_READY
	goto_if_ne BattleFrontier_BattleTowerBattleRoom_EventScript_MaidenUpNext
	frontier_get FRONTIER_DATA_BATTLE_NUM
	call BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyForOpponent
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponentNoRecord
	multichoice 19, 4, MULTI_GO_ON_RECORD_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleTowerBattleRoom_EventScript_ContinueChallenge
	case 1, BattleFrontier_BattleTowerBattleRoom_EventScript_AskRecordBattle
	case 2, BattleFrontier_BattleTowerBattleRoom_EventScript_AskPauseChallenge
	case 3, BattleFrontier_BattleTowerBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponentNoRecord:: @ 8241D0A
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleTowerBattleRoom_EventScript_ContinueChallenge
	case 1, BattleFrontier_BattleTowerBattleRoom_EventScript_AskPauseChallenge
	case 2, BattleFrontier_BattleTowerBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleTowerBattleRoom_EventScript_AskRecordBattle:: @ 8241D40
	message BattleFrontier_BattleTowerBattleRoom_Text_RecordYourBattle
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent
	case 0, BattleFrontier_BattleTowerBattleRoom_EventScript_RecordBattle
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleTowerBattleRoom_EventScript_RecordBattle:: @ 8241D72
	call BattleFrontier_EventScript_SaveBattle
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleTowerBattleRoom_EventScript_AskPauseChallenge:: @ 8241D7C
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_SaveAndQuitGame, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent
	case YES, BattleFrontier_BattleTowerBattleRoom_EventScript_PauseChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleTowerBattleRoom_EventScript_AskRetireChallenge:: @ 8241DAA
	message BattleFrontier_BattleTowerBattleRoom_Text_CancelYourChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent
	case 0, BattleFrontier_BattleTowerBattleRoom_EventScript_RetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleTowerBattleRoom_EventScript_ContinueChallenge:: @ 8241DDC
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerBattleRoom_Movement_PlayerFaceBattle
	waitmovement 0
	applymovement LOCALID_ATTENDANT_1, BattleFrontier_BattleTowerBattleRoom_Movement_AttendantReturnToPos
	waitmovement 0
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_OpponentEnter

BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyWon:: @ 8241DF6
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_WON
	tower_set TOWER_DATA_LVL_MODE
	setvar VAR_0x8004, FANCOUNTER_USED_BATTLE_TOWER
	special Script_TryGainNewFanFromCounter
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobby

BattleFrontier_BattleTowerBattleRoom_EventScript_PauseChallenge:: @ 8241E22
	message BattleFrontier_BattleTowerBattleRoom_Text_SavingPleaseWait
	waitmessage
	tower_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyForOpponent:: @ 8241E44
	copyvar VAR_TEMP_F, VAR_RESULT
	switch VAR_TEMP_F
	case 1, BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor2ndOpponent
	case 2, BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor3rdOpponent
	case 3, BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor4thOpponent
	case 4, BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor5thOpponent
	case 5, BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor6thOpponent
	case 6, BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor7thOpponent

BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor2ndOpponent:: @ 8241E90
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor2ndOpponent
	waitmessage
	return

BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor3rdOpponent:: @ 8241E97
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor3rdOpponent
	waitmessage
	return

BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor4thOpponent:: @ 8241E9E
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor4thOpponent
	waitmessage
	return

BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor5thOpponent:: @ 8241EA5
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor5thOpponent
	waitmessage
	return

BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor6thOpponent:: @ 8241EAC
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor6thOpponent
	waitmessage
	return

BattleFrontier_BattleTowerBattleRoom_EventScript_ReadyFor7thOpponent:: @ 8241EB3
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor7thOpponent
	waitmessage
	return

BattleFrontier_EventScript_IncrementWinStreak:: @ 8241EBA
	frontier_incrementstreak
	return

BattleFrontier_BattleTowerBattleRoom_EventScript_SecondAttendantEnter:: @ 8241EC3
	applymovement LOCALID_ATTENDANT_2, BattleFrontier_BattleTowerBattleRoom_Movement_SecondAttendantEnter
	waitmovement 0
	applymovement LOCALID_ATTENDANT_2, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_ATTENDANT_1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ATTENDANT_1, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_ATTENDANT_2, BattleFrontier_BattleTowerBattleRoom_Movement_SecondAttendantDelay
	applymovement LOCALID_ATTENDANT_1, BattleFrontier_BattleTowerBattleRoom_Movement_AttendantFaceSecondAttendant
	waitmovement 0
	applymovement LOCALID_ATTENDANT_2, BattleFrontier_BattleTowerBattleRoom_Movement_SecondAttendantExit
	waitmovement 0
	return

BattleFrontier_BattleTowerBattleRoom_EventScript_MaidenUpNext:: @ 8241F0A
	compare VAR_TEMP_2, 1
	goto_if_eq BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForMaiden
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_SalonMaidenOnHerWay, MSGBOX_DEFAULT
	setvar VAR_TEMP_2, 1
BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForMaiden:: @ 8241F22
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyForSalonMaiden
	waitmessage
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForMaidenNoRecord
	multichoice 19, 4, MULTI_GO_ON_RECORD_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabel
	case 1, BattleFrontier_BattleTowerBattleRoom_EventScript_AskRecordBattle
	case 2, BattleFrontier_BattleTowerBattleRoom_EventScript_AskPauseChallenge
	case 3, BattleFrontier_BattleTowerBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForMaiden

BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForMaidenNoRecord:: @ 8241F79
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabel
	case 1, BattleFrontier_BattleTowerBattleRoom_EventScript_AskPauseChallenge
	case 2, BattleFrontier_BattleTowerBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerBattleRoom_EventScript_AskReadyForMaiden

BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabel:: @ 8241FAF
	call BattleFrontier_EventScript_SetBrainObjectGfx
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerBattleRoom_Movement_PlayerFaceBattle
	waitmovement 0
	applymovement LOCALID_ATTENDANT_1, BattleFrontier_BattleTowerBattleRoom_Movement_AttendantReturnToPos
	waitmovement 0
	addobject LOCALID_OPPONENT
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleTowerBattleRoom_Movement_AnabelEnter
	waitmovement 0
	switch VAR_TEMP_F
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattleTowerBattleRoom_EventScript_AnabelGoldIntro
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabelSilver
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabelGold
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabelSilver
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_GreetingsImAnabel, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabelSilver:: @ 8242029
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_LetMeSeeYourTalent, MSGBOX_DEFAULT
	call BattleFrontier_BattleTowerBattleRoom_EventScript_DoTowerBattle
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq BattleFrontier_BattleTowerBattleRoom_EventScript_DefeatedAnabelSilver
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost

BattleFrontier_BattleTowerBattleRoom_EventScript_DefeatedAnabelSilver:: @ 8242046
	call BattleFrontier_EventScript_IncrementWinStreak
	frontier_getsymbols
	compare VAR_RESULT, 0
	goto_if_ne BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyWon
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_AnabelTalentShallBeRecognized, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattleTowerBattleRoom_Text_ReceivedAbilitySymbol
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_UntilNextTime, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyWon

BattleFrontier_BattleTowerBattleRoom_EventScript_AnabelGoldIntro:: @ 8242085
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabelGold
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_AnabelYouCameBack, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
BattleFrontier_BattleTowerBattleRoom_EventScript_BattleAnabelGold:: @ 82420B2
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_LetsBeginShallWe, MSGBOX_DEFAULT
	call BattleFrontier_BattleTowerBattleRoom_EventScript_DoTowerBattle
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq BattleFrontier_BattleTowerBattleRoom_EventScript_DefeatedAnabelGold
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost

BattleFrontier_BattleTowerBattleRoom_EventScript_DefeatedAnabelGold:: @ 82420CF
	call BattleFrontier_EventScript_IncrementWinStreak
	frontier_getsymbols
	compare VAR_RESULT, 2
	goto_if_eq BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyWon
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_AnabelCongratsYourPassPlease, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattleTowerBattleRoom_Text_AbilitySymbolTookGoldenShine
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_WishICouldBattleYouAgain, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyWon

BattleFrontier_BattleTowerBattleRoom_EventScript_DoTowerBattle:: @ 824210E
	closemessage
	setvar VAR_TEMP_2, 0
	frontier_set FRONTIER_DATA_RECORD_DISABLED, FALSE
	special HealPlayerParty
	setvar VAR_0x8004, SPECIAL_BATTLE_TOWER
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	copyvar VAR_0x8004, VAR_FRONTIER_BATTLE_MODE
	compare VAR_0x8004, FRONTIER_MODE_LINK_MULTIS
	goto_if_eq BattleFrontier_BattleTowerBattleRoom_EventScript_EndTowerBattle
	frontier_restorehelditems
	special HealPlayerParty
	frontier_resetsketch
BattleFrontier_BattleTowerBattleRoom_EventScript_EndTowerBattle:: @ 824215A
	tower_setinterviewdata
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	return

BattleFrontier_EventScript_SetBrainObjectGfx:: @ 8242170
	frontier_setbrainobj
	return

BattleFrontier_BattleTowerBattleRoom_Movement_PlayerEnter: @ 8242179
	walk_up
	walk_up
	walk_up
	face_right
	step_end

BattleFrontier_BattleTowerBattleRoom_Movement_PlayerFaceAttendant: @ 824217E
	face_down
	step_end

BattleFrontier_BattleTowerBattleRoom_Movement_PlayerFaceBattle: @ 8242180
	face_right
	step_end

BattleFrontier_BattleTowerBattleRoom_Movement_OpponentEnter: @ 8242182
	walk_down
	walk_down
	walk_down
	walk_down
	face_left
	step_end

BattleFrontier_BattleTowerBattleRoom_Movement_OpponentExit: @ 8242188
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleTowerBattleRoom_Movement_AttendantApproachPlayer: @ 824218D
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

BattleFrontier_BattleTowerBattleRoom_Movement_AttendantReturnToPos: @ 8242192
	walk_down
	walk_left
	walk_left
	walk_left
	face_right
	step_end

BattleFrontier_BattleTowerBattleRoom_Movement_SetInvisible: @ 8242198
	set_invisible
	step_end

BattleFrontier_BattleTowerBattleRoom_Movement_SecondAttendantEnter: @ 824219A
	set_visible
	delay_16
	walk_up
	walk_left
	walk_left
	delay_8
	step_end

BattleFrontier_BattleTowerBattleRoom_Movement_SecondAttendantExit: @ 82421A1
	walk_right
	walk_right
	walk_down
	set_invisible
	step_end

BattleFrontier_BattleTowerBattleRoom_Movement_SecondAttendantDelay: @ 82421A6
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

BattleFrontier_BattleTowerBattleRoom_Movement_AttendantFaceSecondAttendant: @ 82421AB
	face_right
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_right
	step_end

BattleFrontier_BattleTowerBattleRoom_Movement_AnabelEnter: @ 82421B2
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	face_left
	step_end

BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobby:: @ 82421B8
	copyvar VAR_RESULT, VAR_FRONTIER_BATTLE_MODE
	compare VAR_RESULT, FRONTIER_MODE_DOUBLES
	goto_if_eq BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyDoubles
	compare VAR_RESULT, FRONTIER_MODE_MULTIS
	goto_if_eq BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyMultis
	compare VAR_RESULT, FRONTIER_MODE_LINK_MULTIS
	goto_if_eq BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyLinkMultis
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_LOBBY, 255, 6, 6
	waitstate
	end

BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyDoubles:: @ 82421E8
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_LOBBY, 255, 10, 6
	waitstate
	end

BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyMultis:: @ 82421F2
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_LOBBY, 255, 14, 6
	waitstate
	end

BattleFrontier_BattleTowerBattleRoom_EventScript_WarpToLobbyLinkMultis:: @ 82421FC
	tower_closelink
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_LOBBY, 255, 18, 6
	waitstate
	end

BattleFrontier_BattleTowerBattleRoom_EventScript_RetireChallenge:: @ 824220E
	setflag FLAG_CANCEL_BATTLE_ROOM_CHALLENGE
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattleTowerBattleRoom_Text_RestoreMonsToFullHealth: @ 8242217
	.string "포켓몬의 체력을\n"
	.string "회복시켜 드리겠습니다$"
	// ポケモンの たいりょくをｎ
	// かいふくして さしあげます

@ Unused
BattleFrontier_BattleTowerBattleRoom_Text_ReadyForOpponent: @ 8242244
	.string "다음은 {STR_VAR_1}명째 상대입니다\n"
	.string "준비되셨습니까?$"
	// つぎは いにんめの あいてですｎ
	// じゅんびは いいですか?

BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor2ndOpponent: @ 8242277
	.string "다음은 2명째 상대입니다\n"
	.string "준비되셨습니까?$"

BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor3rdOpponent: @ 82422A9
	.string "다음은 3명째 상대입니다\n"
	.string "준비되셨습니까?$"

BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor4thOpponent: @ 82422DB
	.string "다음은 4명째 상대입니다\n"
	.string "준비되셨습니까?$"

BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor5thOpponent: @ 824230D
	.string "다음은 5명째 상대입니다\n"
	.string "준비되셨습니까?$"

BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor6thOpponent: @ 824233F
	.string "다음은 6명째 상대입니다\n"
	.string "준비되셨습니까?$"

BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor7thOpponent: @ 8242371
	.string "다음은 7명째 상대입니다\n"
	.string "준비되셨습니까?$"
	// つぎは 7にんめの あいてですｎ
	// じゅんびは いいですか?

BattleFrontier_BattleTowerBattleRoom_Text_RecordYourBattle: @ 82423A3
	.string "방금 전 배틀을\n"
	.string "프런티어패스에 기록하겠습니까?$"
	// さきほどの たたかいをｎ
	// フロンティアパスに きろく しますか?

BattleFrontier_BattleTowerLobby_Text_BattleRecordedOnPass: @ 82423CD
	.string "{PLAYER}의 배틀이\n"
	.string "프런티어패스에 기록되었다!$"
	// §あの たたかいがｎ
	// フロンティアパスに きろく された!

BattleFrontier_BattleTowerBattleRoom_Text_SaveAndQuitGame: @ 82423FC
	.string "리포트를 작성하고 종료할까요?$"
	// レポ-トを かいて しゅうりょう しますか?

BattleFrontier_BattleTowerBattleRoom_Text_SavingPleaseWait: @ 8242426
	.string "리포트를 작성하고 있습니다!\n"
	.string "잠시 기다려 주십시오!$"
	// レポ-トを かいています!ｎ
	// しばらく おまちくださいませ!

BattleFrontier_BattleTowerBattleRoom_Text_CancelYourChallenge: @ 824244C
	.string "배틀룸 도전을\n"
	.string "중지할까요?$"
	// バトルル-ムの ちょうせんをｎ
	// ちゅうし しますか?

BattleFrontier_BattleTowerBattleRoom_Text_RecordCouldntBeSaved:: @ 8242481
	.string "오류가 발생하여\n"
	.string "기록하지 못했습니다!$"
	// ふぐあいに よりｎ
	// きろく できませんでした!

BattleFrontier_BattleTowerBattleRoom_Text_SalonMaidenOnHerWay: @ 82424C2
	.string "...손님\p"
	.string "실은 저희의 주인이신\n"
	.string "타워타이쿤께서\l"
	.string "손님과의 대전을 위해 곧\l"
	.string "배틀룸에 오시는 것 같습니다$"
	// …… おきゃくさまｐ
	// じつは わたくしどもの しゅじんで あるｎ
	// タワ-タイク-ンがｌ
	// あなたと たたかう ために まもなくｌ
	// バトルル-ムに いらっしゃる そうです

BattleFrontier_BattleTowerBattleRoom_Text_ReadyForSalonMaiden: @ 8242542
	.string "타워타이쿤과의 승부입니다!\n"
	.string "각오는 되셨나요?$"
	// タワ-タイク-ンとの たたかい です!ｎ
	// かくごは よろしい ですか?

BattleFrontier_BattleTowerBattleRoom_Text_GreetingsImAnabel: @ 8242579
	.string "반가워...\p"
	.string "내 이름은 리라\n"
	.string "배틀타워를 관리하는 자...\l"
	.string "타워타이쿤이야...\p"
	.string "네 소문은\n"
	.string "많이 들었어\p"
	.string "솔직히 나는 매력을\n"
	.string "느끼지 못하는 것들뿐이지만...\p"
	.string "내가 널 만나러 온 이유...\n"
	.string "그건 단 한 가지...$"
	// はじめまして……ｐ
	// ぼくの なまえは リラｎ
	// バトルタワ-を かんりする もの……ｌ
	// タワ-タイク-ンだ……ｐ
	// あなたの うわさはｎ
	// いろいろと きいて いるよｐ
	// しょうじき ぼくには みりょくをｎ
	// かんじない こと ばかり だけどね……ｐ
	// ぼくが あなたに あいに きた りゆう……ｎ
	// それは ただ ひとつ……

BattleFrontier_BattleTowerBattleRoom_Text_LetMeSeeYourTalent: @ 824268C
	.string "너의 재능을\n"
	.string "여기서 증명해 봐...$"
	// あなたの さいのうをｎ
	// ここに しめしなさい……

BattleFrontier_BattleTowerBattleRoom_Text_AnabelTalentShallBeRecognized: @ 82426B4
	.string "리라: 후후후 좋네...\p"
	.string "그럼 프런티어패스를...\n"
	.string "네 재능의 증거를 새기자$"
	// リラ『ふふふ いいね……ｐ
	// では フロンティアパスを……ｎ
	// あなたの さいのうの あかしを きざもう

BattleFrontier_BattleTowerBattleRoom_Text_ReceivedAbilitySymbol: @ 824270E
	.string "프런티어패스에\n"
	.string "어빌리티심볼이 새겨졌다!$"
	// フロンティアパスにｎ
	// アビリティシンボルが きざまれた!

BattleFrontier_BattleTowerBattleRoom_Text_UntilNextTime: @ 8242744
	.string "...... ...... ......\p"
	.string "너도 포켓몬 배틀에\n"
	.string "자신이 있는 거지?\p"
	.string "그렇다면 더욱더 싸워서\n"
	.string "더욱더 이겨나가겠구나\p"
	.string "다시 만날 그때를\n"
	.string "나는 기다리고 있을게...$"
	// …… …… ……ｐ
	// あなたは ポケモンバトルにｎ
	// じしんが あるのだろ?ｐ
	// だったら もっと もっと たたかってｎ
	// もっと もっと かちぬいて おいでよｐ
	// また あえる そのときをｎ
	// ぼくは まってる から……

BattleFrontier_BattleTowerBattleRoom_Text_AnabelYouCameBack: @ 82427F9
	.string "리라: 정말로 와주었구나...\p"
	.string "...... ...... ...... ......\p"
	.string "여기까지 이겨 온 너...\n"
	.string "... 네가 상대라면\l"
	.string "나도 진심으로 싸울 수 있겠어...\p"
	.string "오랜만이야...\p"
	.string "아무것도 생각하지 않고\n"
	.string "싸울 수 있는 건...$"
	// リラ『ほんとに きて くれたんだね……ｐ
	// …… …… …… ……ｐ
	// ここまで かちぬいた あなた……ｎ
	// …… あなたが あいて だったらｌ
	// ぼくも てかげん せずに たたかえる……ｐ
	// ひさしぶり……ｐ
	// なんにも かんがえずにｎ
	// たたかう ことが できる なんて……

BattleFrontier_BattleTowerBattleRoom_Text_LetsBeginShallWe: @ 82428E0
	.string "자 시작하자!$"
	// さあ はじめようよ!

BattleFrontier_BattleTowerBattleRoom_Text_AnabelCongratsYourPassPlease: @ 82428F7
	.string "리라: 후훗 축하해...\n"
	.string "자 너의 프런티어패스를...$"
	// リラ『ふふっ おめでとう……ｎ
	// さあ あなたの フロンティアパスを……

BattleFrontier_BattleTowerBattleRoom_Text_AbilitySymbolTookGoldenShine: @ 8242932
	.string "어빌리티심볼이\n"
	.string "금색으로 빛났다!$"
	// アビリティシンボルがｎ
	// きんいろに かがやいた!

BattleFrontier_BattleTowerBattleRoom_Text_WishICouldBattleYouAgain: @ 824295D
	.string "즐거웠어...\p"
	.string "포켓몬 배틀이 이렇게나\n"
	.string "즐거운 건 처음이야...\p"
	.string "또 너와 배틀할 수 있으면 좋겠다...$"
	// たのしかった……ｐ
	// こんなに ポケモンバトルがｎ
	// たのしい なんて はじめて……ｐ
	// また あなたと たたかえると いいな……

