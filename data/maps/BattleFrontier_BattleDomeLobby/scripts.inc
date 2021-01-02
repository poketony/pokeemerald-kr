.set LOCALID_ATTENDANT_SINGLES, 1
.set LOCALID_ATTENDANT_DOUBLES, 6

BattleFrontier_BattleDomeLobby_MapScripts:: @ 82497E2
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleDomeLobby_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleDomeLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleDomeLobby_OnWarp
	.byte 0

BattleFrontier_BattleDomeLobby_OnResume:
	dome_initresultstree
	end

BattleFrontier_BattleDomeLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleDomeLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleDomeLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleDomeLobby_OnFrame:
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattleDomeLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleDomeLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleDomeLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_WON, BattleFrontier_BattleDomeLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_LOST, BattleFrontier_BattleDomeLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleDomeLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleDomeLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleDomeLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	dome_set DOME_DATA_WIN_STREAK, 0
	dome_set DOME_DATA_WIN_STREAK_ACTIVE, FALSE
	dome_set DOME_DATA_ATTEMPTED_CHALLENGE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattleDomeLobby_EventScript_WonChallenge::
	call BattleFrontier_EventScript_IncrementWinStreak
	lockall
	frontier_isbrain
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattleDomeLobby_EventScript_DefeatedAce
	msgbox BattleFrontier_BattleDomeLobby_Text_CongratsForWinningTourney, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleDomeLobby_EventScript_DefeatedAce::
	msgbox BattleFrontier_BattleDomeLobby_Text_CongratsDefeatedTucker, MSGBOX_DEFAULT
BattleFrontier_BattleDomeLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleDomeLobby_Text_AwardTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleDomeLobby_Text_RecordWillBeSaved
	waitmessage
	special LoadPlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	frontier_checkairshow
	dome_set DOME_DATA_ATTEMPTED_CHALLENGE, TRUE
	dome_set DOME_DATA_HAS_WON_CHALLENGE, TRUE
	dome_set DOME_DATA_WIN_STREAK_ACTIVE, TRUE
	special LoadPlayerParty
	special HealPlayerParty
	goto BattleFrontier_BattleDomeLobby_EventScript_AskRecordBattle

BattleFrontier_BattleDomeLobby_EventScript_LostChallenge::
	lockall
	msgbox BattleFrontier_BattleDomeLobby_Text_ThankYouForPlaying, MSGBOX_DEFAULT
	message BattleFrontier_BattleDomeLobby_Text_RecordWillBeSaved
	waitmessage
	special LoadPlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	frontier_checkairshow
	dome_set DOME_DATA_WIN_STREAK_ACTIVE, FALSE
	dome_set DOME_DATA_ATTEMPTED_CHALLENGE, TRUE
	special LoadPlayerParty
	special HealPlayerParty
BattleFrontier_BattleDomeLobby_EventScript_AskRecordBattle::
	dome_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattleDomeLobby_EventScript_EndChallenge
	message BattleFrontier_BattleDomeLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattleDomeLobby_EventScript_EndChallenge
	case 0, BattleFrontier_BattleDomeLobby_EventScript_RecordBattle
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_EndChallenge

BattleFrontier_BattleDomeLobby_EventScript_RecordBattle::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleDomeLobby_EventScript_EndChallenge::
	msgbox BattleFrontier_BattleDomeLobby_Text_HopeToSeeYouAgain, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattleDomeLobby_EventScript_ResumeChallenge::
	lockall
	msgbox BattleFrontier_BattleDomeLobby_Text_WeveBeenWaitingForYou, MSGBOX_DEFAULT
	message BattleFrontier_BattleDomeLobby_Text_OkayToSaveBeforeChallenge2
	waitmessage
	dome_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_0, 255
	goto BattleFrontier_BattleDomeLobby_EventScript_EnterChallenge

BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_DOME
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattleDomeLobby_EventScript_AttendantWelcome
	end

BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_DOME
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattleDomeLobby_EventScript_AttendantWelcome
	end

BattleFrontier_BattleDomeLobby_EventScript_AttendantWelcome::
	special SavePlayerParty
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_WelcomeSingles
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_WelcomeDoubles
BattleFrontier_BattleDomeLobby_EventScript_AskTakeChallenge::
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_TakeSinglesChallenge
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_TakeDoublesChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattleDomeLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleDomeLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge

BattleFrontier_BattleDomeLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleDomeLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, 0
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge
	frontier_checkineligible
	compare VAR_0x8004, TRUE
	goto_if_eq BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleDomeLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattleDomeLobby_EventScript_LoadPartyCancelChallenge
	msgbox BattleFrontier_BattleDomeLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleDomeLobby_EventScript_LoadPartyCancelChallenge
	case YES, BattleFrontier_BattleDomeLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_LoadPartyCancelChallenge

BattleFrontier_BattleDomeLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_0, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	dome_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_0, 255
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattleDomeLobby_EventScript_CancelChallengeSaveFailed
	dome_inittrainers
BattleFrontier_BattleDomeLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	dome_settrainers
	msgbox BattleFrontier_BattleDomeLobby_Text_ShowYouToBattleDome, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattleDomeLobby_EventScript_WalkToDoor
	special HealPlayerParty
	warp MAP_BATTLE_FRONTIER_BATTLE_DOME_CORRIDOR, 255, 23, 6
	setvar VAR_TEMP_0, 0
	waitstate
	end

BattleFrontier_BattleDomeLobby_EventScript_ExplainChallenge::
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_ExplainSinglesChallenge
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_ExplainDoublesChallenge
	goto BattleFrontier_BattleDomeLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleDomeLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge

BattleFrontier_BattleDomeLobby_EventScript_LoadPartyCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleDomeLobby_Text_HopeToSeeYouAgain, MSGBOX_DEFAULT
BattleFrontier_BattleDomeLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattleDomeLobby_EventScript_WalkToDoor::
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendantWalkToDoor
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendantWalkToDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleDomeLobby_Movement_WalkToDoor
	waitmovement 0
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_OpenSinglesDoor
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_OpenDoublesDoor
	waitdooranim
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendantEnterDoor
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleDomeLobby_Movement_PlayerEnterDoor
	waitmovement 0
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_CloseSinglesDoor
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_CloseDoublesDoor
	waitdooranim
	return

BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendantWalkToDoor:: @ 8249CDD
	applymovement LOCALID_ATTENDANT_SINGLES, BattleFrontier_BattleDomeLobby_Movement_WalkToDoor
	return

BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendantWalkToDoor:: @ 8249CE5
	applymovement LOCALID_ATTENDANT_DOUBLES, BattleFrontier_BattleDomeLobby_Movement_WalkToDoor
	return

BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendantEnterDoor:: @ 8249CED
	applymovement LOCALID_ATTENDANT_SINGLES, BattleFrontier_BattleDomeLobby_Movement_AttendantEnterDoor
	return

BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendantEnterDoor:: @ 8249CF5
	applymovement LOCALID_ATTENDANT_DOUBLES, BattleFrontier_BattleDomeLobby_Movement_AttendantEnterDoor
	return

BattleFrontier_BattleDomeLobby_EventScript_WelcomeSingles::
	msgbox BattleFrontier_BattleDomeLobby_Text_WelcomeSingleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeLobby_EventScript_WelcomeDoubles::
	msgbox BattleFrontier_BattleDomeLobby_Text_WelcomeDoubleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeLobby_EventScript_TakeSinglesChallenge::
	message BattleFrontier_BattleDomeLobby_Text_TakeSinglesChallenge
	return

BattleFrontier_BattleDomeLobby_EventScript_TakeDoublesChallenge::
	message BattleFrontier_BattleDomeLobby_Text_TakeDoublesChallenge
	return

BattleFrontier_BattleDomeLobby_EventScript_ExplainSinglesChallenge::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeLobby_EventScript_ExplainDoublesChallenge::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeLobby_EventScript_OpenSinglesDoor::
	opendoor 5, 4
	return

BattleFrontier_BattleDomeLobby_EventScript_OpenDoublesDoor::
	opendoor 17, 4
	return

BattleFrontier_BattleDomeLobby_EventScript_CloseSinglesDoor::
	closedoor 5, 4
	return

BattleFrontier_BattleDomeLobby_EventScript_CloseDoublesDoor::
	closedoor 17, 4
	return

BattleFrontier_BattleDomeLobby_Movement_WalkToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleDomeLobby_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleDomeLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleDomeLobby_EventScript_ShowSinglesResults::
	lockall
	frontier_results FRONTIER_FACILITY_DOME, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleDomeLobby_EventScript_ShowDoublesResults::
	lockall
	frontier_results FRONTIER_FACILITY_DOME, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleDomeLobby_EventScript_ShowPrevTourneyTree::
	dome_get DOME_DATA_PREV_TOURNEY_TYPE
	compare VAR_RESULT, 0
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsSinglesLv50
	compare VAR_RESULT, 1
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsDoublesLv50
	compare VAR_RESULT, 2
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsSinglesLvOpen
	compare VAR_RESULT, 3
	call_if_eq BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsDoublesLvOpen
	fadescreen FADE_TO_BLACK
	dome_showprevtourneytree
	waitstate
	end

BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsSinglesLv50::
	msgbox BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsSinglesLv50, MSGBOX_SIGN
	return

BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsDoublesLv50::
	msgbox BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsDoublesLv50, MSGBOX_SIGN
	return

BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsSinglesLvOpen::
	msgbox BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsSinglesLvOpen, MSGBOX_SIGN
	return

BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsDoublesLvOpen::
	msgbox BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsDoublesLvOpen, MSGBOX_SIGN
	return

BattleFrontier_BattleDomeLobby_EventScript_Maniac::
	dome_getwinnersname
	msgbox BattleFrontier_BattleDomeLobby_Text_LastWinnerWasTough, MSGBOX_NPC
	end

BattleFrontier_BattleDomeLobby_EventScript_Lass::
	msgbox BattleFrontier_BattleDomeLobby_Text_WinnersGainReputation, MSGBOX_NPC
	end

BattleFrontier_BattleDomeLobby_EventScript_FatMan::
	msgbox BattleFrontier_BattleDomeLobby_Text_TrashedInFirstRound, MSGBOX_NPC
	end

BattleFrontier_BattleDomeLobby_EventScript_Man::
	msgbox BattleFrontier_BattleDomeLobby_Text_NeedToCheckOpponentCarefully, MSGBOX_NPC
	end

@ A few OutsideWest event scripts are inserted here instead, two of which are unused
BattleFrontier_OutsideWest_EventScript_Man3::
	msgbox BattleFrontier_OutsideWest_Text_LongDreamedAboutBattleFrontier, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_BattleDomeSign2::
	msgbox BattleFrontier_OutsideWest_Text_BattleDomeSign2, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnderConstructionSign::
	msgbox BattleFrontier_OutsideWest_Text_QuestionMarkUnderConstruction, MSGBOX_NPC
	end

BattleFrontier_BattleDomeLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleDomeLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleDomeLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 4, MULTI_BATTLE_DOME_RULES, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattleDomeLobby_EventScript_RulesMatchup
	case 1, BattleFrontier_BattleDomeLobby_EventScript_RulesTourneyTree
	case 2, BattleFrontier_BattleDomeLobby_EventScript_RulesDoubleKO
	case 3, BattleFrontier_BattleDomeLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_ExitRules
	end

BattleFrontier_BattleDomeLobby_EventScript_RulesMatchup::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainMatchupRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleDomeLobby_EventScript_RulesTourneyTree::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainTourneyTree, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleDomeLobby_EventScript_RulesDoubleKO::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainDoubleKORules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleDomeLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattleDomeLobby_Text_WelcomeSingleBattle:
	.string "트레이너의 전략을 시험하는 장소!\n"
	.string "배틀돔에 어서 오십시오!\p"
	.string "여기서는\n"
	.string "싱글 배틀토너먼트의\l"
	.string "안내를 하고 있습니다$"
	// トレ-ナ-の せんりゃくを ためす ばしょ!ｎ
	// バトルド-ムへ ようこそ!ｐ
	// こちらではｎ
	// シングル バトルト-ナメントのｌ
	// ごあんないを しております

BattleFrontier_BattleDomeLobby_Text_TakeSinglesChallenge:
	.string "싱글 배틀토너먼트에\n"
	.string "도전하겠습니까?$"
	// シングル バトルト-ナメントにｎ
	// ちょうせん しますか?

BattleFrontier_BattleDomeLobby_Text_HopeToSeeYouAgain:
	.string "다음에 또 이용해 주세요\n"
	.string "기다리고 있겠습니다$"
	// またの ごりようを おまちして おります

BattleFrontier_BattleDomeLobby_Text_ExplainSinglesChallenge:
	.string "싱글 배틀토너먼트는\n"
	.string "싱글배틀로 이루어지는\l"
	.string "토너먼트 대회입니다\p"
	.string "참가하는 분께서는 출전시킬\n"
	.string "포켓몬을 3마리 선택해 주십시오\p"
	.string "시합에서는 3마리의 지닌 포켓몬에서\n"
	.string "1마리를 대기시키고\l"
	.string "2마리로 대전을 진행합니다\p"
	.string "내보낸 포켓몬은 대전 상대의\n"
	.string "포켓몬을 잘 보고 선택해 주세요\p"
	.string "토너먼트를 4회 연속으로 이기면\n"
	.string "훌륭히 우승하게 됩니다\p"
	.string "배틀포인트를 받을 수 있으므로\n"
	.string "열심히 해주세요!\p"
	.string "또한 도중에 도전을\n"
	.string "중단하고 싶을 경우에는\l"
	.string "제대로 리포트를 작성하지 않으면\l"
	.string "계속해서 도전을 할 수 없으므로\l"
	.string "주의해 주세요!$"
	// シングル バトルト-ナメントはｎ
	// シングルバトルで おこなわれるｌ
	// ト-ナメントたいかい ですｐ
	// さんかする かたには しゅつじょう させるｎ
	// ポケモンを 3ひき えらんで いただきますｐ
	// しあいでは 3ひきの てもち ポケモンからｎ
	// 1ひきを ひかえにしてｌ
	// 2ひきずつで たいせんを おこないますｐ
	// だす ポケモンは たいせん あいてのｎ
	// ポケモンを よくみて えらんで くださいねｐ
	// ト-ナメントを 4かい かちすすむとｎ
	// みごと ゆうしょうと なりますｐ
	// バトルポイントが もらえますのでｎ
	// がんばって くださいね!ｐ
	// また とちゅうで ちょうせんをｎ
	// ちゅうだんしたい ばあいはｌ
	// ちゃんと レポ-トを かかないとｌ
	// つづけて ちょうせんが できないのでｌ
	// きをつけて くださいね!

BattleFrontier_BattleDomeLobby_Text_OkayToSaveBeforeChallenge:
	.string "배틀돔에 입장하기 전에\n"
	.string "리포트를 작성합니다만\l"
	.string "괜찮겠습니까?$"
	// バトルド-ムへ ごあんないする まえにｎ
	// レポ-トを かきますが よろしいですか?

BattleFrontier_BattleDomeLobby_Text_WhichLevelMode:
	.string "토너먼트에는\n"
	.string "레벨 50과 오픈 레벨이 있습니다만\l"
	.string "어느 쪽으로 도전하겠습니까?$"
	// ト-ナメントにはｎ
	// レベル50と オ-プンレベルと ありますがｌ
	// どちらに ちょうせん しますか?

BattleFrontier_BattleDomeLobby_Text_SelectThreeMons:
	.string "그럼 참가할 포켓몬을\n"
	.string "3마리 선택해 주십시오$"
	// それでは さんかする ポケモンをｎ
	// 3ひき おえらび ください

BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsLvOpen:
	.string "손님!!\p"
	.string "참가할 수 있는 포켓몬이\n"
	.string "3마리는 필요합니다!\p"
	.string "또한 지니게 할 도구도\n"
	.string "모두 다른 도구로 해주십시오!\p"
	.string "그리고 알, 뮤,\n"
	.string "뮤츠, 칠색조,\l"
	.string "루기아, 세레비,\l"
	.string "가이오가, 그란돈,\l"
	.string "레쿠쟈, 지라치,\l"
	.string "테오키스는\l"
	.string "참가시킬 수 없습니다!\p"
	.string "준비되면\n"
	.string "다시 방문해 주십시오$"
	// おきゃくさま!ｐ
	// さんかできる ポケモンが 3ひき いません!ｐ
	// また もたせる どうぐもｎ
	// すべて ちがう どうぐに してください!ｐ
	// なお タマゴ{STR_VAR_1}さんか させる ことは できません!ｐ
	// じゅんびが できましたらｎ
	// また おこし ください

BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsLv50:
	.string "손님!\p"
	.string "참가할 수 있는 포켓몬이\n"
	.string "3마리는 필요합니다!\p"
	.string "참가하려면 레벨 50 이하의\n"
	.string "종류가 다른 포켓몬을\l"
	.string "3마리 준비해 주십시오\p"
	.string "또한 지니게 할 도구도\n"
	.string "모두 다른 도구로 해주십시오!\p"
	.string "그리고 알, 뮤,\n"
	.string "뮤츠, 칠색조,\l"
	.string "루기아, 세레비,\l"
	.string "가이오가, 그란돈,\l"
	.string "레쿠쟈, 지라치,\l"
	.string "테오키스는\l"
	.string "참가시킬 수 없습니다!\p"
	.string "준비되면\n"
	.string "다시 방문해 주십시오$"
	// おきゃくさま!ｐ
	// さんかできる ポケモンが 3ひき いません!ｐ
	// さんかする ためには レベルが 50いかでｎ
	// すべて ちがう しゅるいの ポケモンをｌ
	// 3ひき よういして くださいｐ
	// また もたせる どうぐもｎ
	// すべて ちがう どうぐに してください!ｐ
	// なお タマゴ{STR_VAR_1}さんか させる ことは できません!ｐ
	// じゅんびが できましたらｎ
	// また おこし ください

BattleFrontier_BattleDomeLobby_Text_ShowYouToBattleDome:
	.string "그럼 배틀돔으로\n"
	.string "안내하겠습니다!$"
	// それでは バトルド-ムへｎ
	//ごあんない します!

BattleFrontier_BattleDomeLobby_Text_DidntSaveBeforeQuitting:
	.string "손님!\p"
	.string "지난번 종료하기 전에\n"
	.string "리포트를 제대로\l"
	.string "작성하지 않으셨죠?\p"
	.string "죄송하지만 이런 경우에는\n"
	.string "도전이 무효가 됩니다$"
	// おきゃくさま!ｐ
	// ぜんかい ちゃんと レポ-トを かいてｎ
	// しゅうりょう しませんでしたね?ｐ
	// もうしわけ ありませんが そのばあいｎ
	// ちょうせんは むこうと なります

BattleFrontier_BattleDomeLobby_Text_CongratsForWinningTourney:
	.string "배틀토너먼트 우승\n"
	.string "축하합니다!$"
	// バトルト-ナメント ゆうしょうｎ
	// おめでとう ございます!

BattleFrontier_BattleDomeLobby_Text_HereIsYourPrize:
	.string "우승했으므로\n"
	.string "이 상품을 드립니다!$"
	// ゆうしょう されましたのでｎ
	// この しょうひんを さしあげます!

BattleFrontier_BattleDomeLobby_Text_ReceivedPrize:
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "{STR_VAR_1}{K_EULREUL} 받았다!$"

@ Unused
BattleFrontier_BattleDomeLobby_Text_BagFullMakeRoom:
	.string "...어라 도구가 가득하네요\p"
	.string "도구를 정리하고 나서\n"
	.string "다시 들러 주십시오$"
	// ……あら どうぐが いっぱいですねｐ
	// どうぐを せいりしてからｎ
	// またおこしください

BattleFrontier_BattleDomeLobby_Text_ThankYouForPlaying:
	.string "수고하셨습니다!$"

BattleFrontier_BattleDomeLobby_Text_RecordWillBeSaved:
	.string "성적을 리포트에 작성하므로\n"
	.string "기다려 주십시오$"
	// せいせきを レポ-トに かきますのでｎ
	// おまちください

BattleFrontier_BattleDomeLobby_Text_WeveBeenWaitingForYou:
	.string "기다리고 있었습니다!$"
	// おまちしておりました!

BattleFrontier_BattleDomeLobby_Text_OkayToSaveBeforeChallenge2:
	.string "배틀돔으로 안내하기 전에\n"
	.string "리포트를 작성하므로\l"
	.string "기다려 주십시오$"
	// バトルド-ムに ごあんないする まえにｎ
	// レポ-トを かきますので おまちください

BattleFrontier_BattleDomeLobby_Text_WelcomeDoubleBattle:
	.string "트레이너의 전략을 시험하는 장소!\n"
	.string "배틀돔에 어서 오십시오!\p"
	.string "이쪽에서는\n"
	.string "더블 배틀토너먼트의\l"
	.string "안내를 하고 있습니다$"

BattleFrontier_BattleDomeLobby_Text_TakeDoublesChallenge:
	.string "더블 배틀토너먼트에\n"
	.string "도전하겠습니까?$"

BattleFrontier_BattleDomeLobby_Text_ExplainDoublesChallenge:
	.string "더블 배틀토너먼트는\n"
	.string "더블배틀로 이루어지는\l"
	.string "토너먼트 대회입니다\p"
	.string "참가하는 분께서는 출전시킬\n"
	.string "포켓몬을 3마리 선택해 주십시오\p"
	.string "시합에서는 3마리의 지닌 포켓몬에서\n"
	.string "1마리를 대기시키고\l"
	.string "2마리로 더블배틀\l"
	.string "대전을 진행합니다\p"
	.string "내보낸 포켓몬은 대전 상대의\n"
	.string "포켓몬을 잘 보고 선택해 주세요\p"
	.string "토너먼트를 4회 연속으로 이기면\n"
	.string "훌륭히 우승하게 됩니다\p"
	.string "배틀포인트를 받을 수 있으므로\n"
	.string "열심히 해주세요!\p"
	.string "또한 도중에 도전을\n"
	.string "중단하고 싶을 경우에는\l"
	.string "제대로 리포트를 작성하지 않으면\l"
	.string "계속해서 도전을 할 수 없으므로\l"
	.string "주의해 주세요!$"
	// ダブル バトルト-ナメントはｎ
	// ダブルバトルで おこなわれるｌ
	// ト-ナメントたいかい ですｐ
	// さんかする かたには しゅつじょう させるｎ
	// ポケモンを 3ひき えらんで いただきますｐ
	// しあいでは 3ひきの てもち ポケモンからｎ
	// 1ひきを ひかえにしてｌ
	// 2ひきによる ダブルバトルのｌ
	// たいせんを おこないますｐ
	// だす ポケモンは たいせん あいてのｎ
	// ポケモンを よくみて えらんで くださいねｐ
	// ト-ナメントを 4かい かちすすむとｎ
	// みごと ゆうしょうと なりますｐ
	// ゆうしょうされると バトルポイントがｎ
	// もらえますので がんばってください!ｐ
	// また とちゅうで ちょうせんをｎ
	// ちゅうだんしたい ばあいはｌ
	// ちゃんと レポ-トを かかないとｌ
	// つづけて ちょうせんが できないのでｌ
	// きをつけて くださいね

BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsSinglesLv50:
	.string "지난번에 치뤄진 레벨 50\n"
	.string "싱글 배틀토너먼트의 결과다!$"
	// ぜんかい おこなわれた レベル50ｎ
	// シングル バトルト-ナメントの けっかだ!

BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsDoublesLv50:
	.string "지난번에 치뤄진 레벨 50\n"
	.string "더블 배틀토너먼트의 결과다!$"

BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsSinglesLvOpen:
	.string "지난번에 치뤄진 오픈 레벨\n"
	.string "싱글 배틀토너먼트의 결과다!$"

BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsDoublesLvOpen:
	.string "지난번에 치뤄진 오픈 레벨\n"
	.string "더블 배틀토너먼트의 결과다!$"

BattleFrontier_BattleDomeLobby_Text_LastWinnerWasTough:
	.string "너 봤어?\n"
	.string "지난번 배틀토너먼트!\p"
	.string "우승한\n"
	.string "{STR_VAR_1}{K_EUNNEUN} 정말 강했어\p"
	.string "PC 옆에 있는 모니터로\n"
	.string "결과를 보고 오도록 해$"
	// きみは みた?ｎ
	// ぜんかいの バトルト-ナメント!ｐ
	// ゆうしょう したｎ
	// いは ほんと つよかったんだよｐ
	// パソコンの よこに ある モニタ-でｎ
	// けっかを みてみると いいよ

BattleFrontier_OutsideWest_Text_LongDreamedAboutBattleFrontier:
	.string "배틀프런티어...\n"
	.string "내가 꿈꾸던 곳이야...$"
	// バトルフロンティア……ｎ
	// わたしの ゆめ だった……

BattleFrontier_OutsideWest_Text_BattleDomeSign2:
	.string "여기는 배틀돔\n"
	.string "노려라 무적의 슈퍼스타!$"

BattleFrontier_OutsideWest_Text_QuestionMarkUnderConstruction:
	.string "여기는 ??????\n"
	.string "지금은 건설 중!$"

BattleFrontier_BattleDomeLobby_Text_WinnersGainReputation:
	.string "배틀돔에서 연패를 계속하게 되면\n"
	.string "그 소문을 듣고\l"
	.string "강한 트레이너가 모여들게 돼\p"
	.string "연패를 계속해 나가야\n"
	.string "진정한 슈퍼스타라고 할 수 있지!$"
	// バトルド-ムで れんぱを つづけていくとｎ
	// その うわさを ききつけてｌ
	// つよい トレ-ナ-が あつまって くるのｐ
	// れんぱを つづけてこそｎ
	// しんの ス-パ-スタ- ね!

BattleFrontier_BattleDomeLobby_Text_TrashedInFirstRound:
	.string "1차전에서 갑자기\n"
	.string "우승 후보하고 만나버려서\l"
	.string "완전 엉망으로 졌어...$"
	// 1かいせんで いきなりｎ
	// ゆうしょうこうほと あたっちゃってｌ
	// もう ボコボコに やられたよ……

BattleFrontier_BattleDomeLobby_Text_NeedToCheckOpponentCarefully:
	.string "이 포켓몬을 대기시켜 놓으면\n"
	.string "이길 수 있으려나-\p"
	.string "시합에 내보낼 포켓몬을 고를 때\n"
	.string "상대의 포켓몬을 잘 보는 건\l"
	.string "정말로 중요해!$"
	// この ポケモンを ひかえに していればｎ
	// かてたんだよな-ｐ
	// しあいに だす ポケモン えらびはｎ
	// あいての ポケモンを よく みることがｌ
	// ほんとうに たいせつだよ!

BattleFrontier_BattleDomeLobby_Text_CongratsDefeatedTucker:
	.string "축하합니다!\p"
	.string "멋지게 돔슈퍼스타를 이겨서\n"
	.string "배틀토너먼트의\l"
	.string "우승자가 되셨습니다!$"
	// おめでとう ございます!ｐ
	// みごと ド-ムス-パ-スタ-を たおしｎ
	// バトルト-ナメントにｌ
	// ゆうしょう されましたね!

BattleFrontier_BattleDomeLobby_Text_AwardTheseBattlePoints:
	.string "손님의\n"
	.string "아름다운 전략을 기리며\l"
	.string "배틀포인트를 드리겠습니다!$"
	// おきゃくさまのｎ
	// うつくしい せんりゃくを たたえｌ
	// バトルポイントを さしあげます!

BattleFrontier_BattleDomeLobby_Text_RecordLastMatch:
	.string "배틀돔에서\n"
	.string "마지막으로 한 배틀을\l"
	.string "프런티어패스에 기록하겠습니까?$"
	// バトルド-ムでｎ
	// さいごに おこなった たたかいをｌ
	// フロンティアパスに きろく されますか?

BattleFrontier_BattleDomeLobby_Text_RulesAreListed:
	.string "배틀토너먼트의\n"
	.string "규칙이 적혀 있다!$"
	// バトルト-ナメントのｎ
	// ル-ルが かかれている!

BattleFrontier_BattleDomeLobby_Text_ReadWhichHeading:
	.string "어느 설명을 읽겠습니까?$"
	// どの せつめいを よみますか?

BattleFrontier_BattleDomeLobby_Text_ExplainMatchupRules:
	.string "토너먼트의 조합은\n"
	.string "트레이너가 데리고 있는\l"
	.string "포켓몬의 힘을 보고 만들어집니다\p"
	.string "처음부터 강한 트레이너끼리는\n"
	.string "만나지 않도록 되어있습니다$"
	// ト-ナメントの くみあわせはｎ
	// トレ-ナ-が つれているｌ
	// ポケモンの ちからを みて つくられますｐ
	// さいしょから つよい トレ-ナ-どうしはｎ
	// あたらないように なっています

BattleFrontier_BattleDomeLobby_Text_ExplainTourneyTree:
	.string "토너먼트표는\n"
	.string "시합 전에 대기실에서\l"
	.string "담당자가 보여줄 겁니다\p"
	.string "토너먼트표에는\n"
	.string "“지난번의 시합 결과”\p"
	.string "“트레이너가 지니고 있는\n"
	.string "  포켓몬의 정보”\p"
	.string "“트레이너의 배틀 방식”\p"
	.string "...등의 정보가 적혀 있으므로\l"
	.string "제대로 보도록 합시다$"
	// ト-ナメントひょうはｎ
	// しあいまえの ひかえしつでｌ
	// かかりいんが みせてくれますｐ
	// ト-ナメントひょう にはｎ
	// 「ぜんかいの しあいけっか」ｐ
	// 「トレ-ナ-の もっているｎ 
	// ポケモンの じょうほう」ｐ
	// 「トレ-ナ-の たたかいかた」ｐ
	// ……などの じょうほうが かかれているのでｎ
	// しっかりと みましょう

BattleFrontier_BattleDomeLobby_Text_ExplainDoubleKORules:
	.string "토너먼트의 시합에서\n"
	.string "같은 턴에 동시에 쓰러진\l"
	.string "더블녹아웃이 되었을 때는\l"
	.string "시합을 보고 있던 심판단에 의한\l"
	.string "판정으로 승자가 결정됩니다$"
	// ト-ナメントの しあいでｎ
	// おなじタ-ンで どうじに たおれてｌ
	// ダブルノックアウトに なった ときはｌ
	// しあいを みていた しんぱんだんに よるｌ
	// はんていで しょうしゃを けってい します
