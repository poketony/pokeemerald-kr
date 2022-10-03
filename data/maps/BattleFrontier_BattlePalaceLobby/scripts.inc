.set LOCALID_ATTENDANT_SINGLES, 1
.set LOCALID_ATTENDANT_DOUBLES, 6

BattleFrontier_BattlePalaceLobby_MapScripts:: @ 824D77E
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePalaceLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePalaceLobby_OnWarp
	.byte 0

BattleFrontier_BattlePalaceLobby_OnWarp: @ 824D789
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePalaceLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePalaceLobby_EventScript_TurnPlayerNorth:: @ 824D793
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePalaceLobby_OnFrame: @ 824D79D
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattlePalaceLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePalaceLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePalaceLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_WON, BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePalaceLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattlePalaceLobby_EventScript_GetChallengeStatus:: @ 824D7C7
	frontier_getstatus
	end

BattleFrontier_BattlePalaceLobby_EventScript_QuitWithoutSaving:: @ 824D7D0
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_FailedToSaveBeforeEndingChallenge, MSGBOX_DEFAULT
	closemessage
	palace_set PALACE_DATA_WIN_STREAK, 0
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge:: @ 824D817
	lockall
	frontier_isbrain
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattlePalaceLobby_EventScript_DefeatedMaven
	msgbox BattleFrontier_BattlePalaceLobby_Text_FirmTrueBondsFor7WinStreak, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePalaceLobby_EventScript_DefeatedMaven:: @ 824D838
	msgbox BattleFrontier_BattlePalaceLobby_Text_ToDefeatMavenAnd7Trainers, MSGBOX_DEFAULT
BattleFrontier_BattlePalaceLobby_EventScript_GiveBattlePoints:: @ 824D840
	msgbox BattleFrontier_BattlePalaceLobby_Text_PresentYouWithBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattlePalaceLobby_Text_FeatWillBeRecorded
	waitmessage
	call BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_LostChallenge:: @ 824D873
	lockall
	message BattleFrontier_BattlePalaceLobby_Text_ResultsWillBeRecorded
	waitmessage
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge:: @ 824D8A1
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	palace_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge
	message BattleFrontier_BattlePalaceLobby_Text_LikeToRecordMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_RecordMatch
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge

BattleFrontier_BattlePalaceLobby_EventScript_RecordMatch:: @ 824D902
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge:: @ 824D907
	return

BattleFrontier_BattlePalaceLobby_EventScript_ResumeChallenge:: @ 824D908
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_WeHaveBeenWaiting, MSGBOX_DEFAULT
	message BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge
	waitmessage
	palace_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_0, 255
	goto BattleFrontier_BattlePalaceLobby_EventScript_EnterChallenge

BattleFrontier_BattlePalaceLobby_EventScript_SinglesAttendant:: @ 824D944
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PALACE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattlePalaceLobby_EventScript_Attendant
	end

BattleFrontier_BattlePalaceLobby_EventScript_DoublesAttendant:: @ 824D956
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PALACE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattlePalaceLobby_EventScript_Attendant
	end

BattleFrontier_BattlePalaceLobby_EventScript_Attendant:: @ 824D968
	palace_get PALACE_DATA_PRIZE
	compare VAR_RESULT, ITEM_NONE
	goto_if_ne BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge
	special SavePlayerParty
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForSingleBattle
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForDoubleBattle
BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge:: @ 824D999
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattlePalaceLobby_EventScript_AskTakeSingleBattleChallenge
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattlePalaceLobby_EventScript_AskTakeDoubleBattleChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_TryEnterChallenge:: @ 824D9E6
	message BattleFrontier_BattlePalaceLobby_Text_WhichChallenge
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, 0
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge
	frontier_checkineligible
	compare VAR_0x8004, TRUE
	goto_if_eq BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePalaceLobby_Text_NowSelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge2, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePalaceLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_SaveBeforeChallenge:: @ 824DA87
	setvar VAR_TEMP_0, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	palace_init
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_0, 255
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattlePalaceLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattlePalaceLobby_EventScript_EnterChallenge:: @ 824DAF3
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePalaceLobby_Text_FollowMe, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattlePalaceLobby_EventScript_WalkToDoor
	warp MAP_BATTLE_FRONTIER_BATTLE_PALACE_CORRIDOR, 255, 8, 13
	setvar VAR_TEMP_0, 0
	waitstate
	end

BattleFrontier_BattlePalaceLobby_EventScript_ExplainChallenge:: @ 824DB20
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto_if_eq BattleFrontier_BattlePalaceLobby_EventScript_ExplainDoublesChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainSingleBattleChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePalaceLobby_EventScript_ExplainDoublesChallenge:: @ 824DB38
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainDoubleBattleChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons:: @ 824DB45
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLv50:: @ 824DB60
	msgbox BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLvOpen:: @ 824DB6D
	msgbox BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_CancelChallengeSaveFailed:: @ 824DB7A
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge:: @ 824DB91
	special LoadPlayerParty
BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge:: @ 824DB94
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified, MSGBOX_DEFAULT
BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge:: @ 824DB9C
	release
	end

BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForSingleBattle:: @ 824DB9E
	msgbox BattleFrontier_BattlePalaceLobby_Text_WelcomeForSingleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForDoubleBattle:: @ 824DBA7
	msgbox BattleFrontier_BattlePalaceLobby_Text_WelcomeForDoubleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceLobby_EventScript_AskTakeSingleBattleChallenge:: @ 824DBB0
	message BattleFrontier_BattlePalaceLobby_Text_TakeSingleBattleChallenge
	return

BattleFrontier_BattlePalaceLobby_EventScript_AskTakeDoubleBattleChallenge:: @ 824DBB6
	message BattleFrontier_BattlePalaceLobby_Text_TakeDoubleBattleChallenge
	return

BattleFrontier_BattlePalaceLobby_EventScript_WalkToDoor:: @ 824DBBC
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattlePalaceLobby_EventScript_TalkedToSinglesAttendant
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattlePalaceLobby_EventScript_TalkedToDoublesAttendant
	applymovement VAR_LAST_TALKED, BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor
	waitmovement 0
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattlePalaceLobby_EventScript_OpenSinglesHallDoor
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattlePalaceLobby_EventScript_OpenDoublesHallDoor
	waitdooranim
	applymovement VAR_LAST_TALKED, BattleFrontier_BattlePalaceLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePalaceLobby_Movement_PlayerEnterDoor
	waitmovement 0
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattlePalaceLobby_EventScript_CloseSinglesHallDoor
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattlePalaceLobby_EventScript_CloseDoublesHallDoor
	waitdooranim
	return

BattleFrontier_BattlePalaceLobby_EventScript_TalkedToSinglesAttendant:: @ 824DC23
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_SINGLES
	return

BattleFrontier_BattlePalaceLobby_EventScript_TalkedToDoublesAttendant:: @ 824DC29
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_DOUBLES
	return

BattleFrontier_BattlePalaceLobby_EventScript_OpenSinglesHallDoor:: @ 824DC2F
	opendoor 5, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_OpenDoublesHallDoor:: @ 824DC35
	opendoor 19, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_CloseSinglesHallDoor:: @ 824DC3B
	closedoor 5, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_CloseDoublesHallDoor:: @ 824DC41
	closedoor 19, 4
	return

BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor: @ 824DC47
	walk_up
	step_end

BattleFrontier_BattlePalaceLobby_Movement_AttendantEnterDoor: @ 824DC49
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePalaceLobby_Movement_PlayerEnterDoor: @ 824DC4C
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePalaceLobby_EventScript_ShowSinglesResults:: @ 824DC50
	lockall
	frontier_results FRONTIER_FACILITY_PALACE, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_ShowDoublesResults:: @ 824DC69
	lockall
	frontier_results FRONTIER_FACILITY_PALACE, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_BlackBelt:: @ 824DC82
	msgbox BattleFrontier_BattlePalaceLobby_Text_LadyCanTellWhatMonsThink, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Man:: @ 824DC8B
	msgbox BattleFrontier_BattlePalaceLobby_Text_NatureAndMovesKeyHere, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Beauty:: @ 824DC94
	msgbox BattleFrontier_BattlePalaceLobby_Text_MonDocileButTransforms, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Maniac:: @ 824DC9D
	msgbox BattleFrontier_BattlePalaceLobby_Text_WhatNatureFavorsChippingAway, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesBoard:: @ 824DCA6
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard:: @ 824DCB5
	message BattleFrontier_BattlePalaceLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 16, 0, MULTI_BATTLE_PALACE_RULES, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_RulesBasics
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_RulesNature
	case 2, BattleFrontier_BattlePalaceLobby_EventScript_RulesMoves
	case 3, BattleFrontier_BattlePalaceLobby_EventScript_RulesUnderpowered
	case 4, BattleFrontier_BattlePalaceLobby_EventScript_RulesWhenInDanger
	case 5, BattleFrontier_BattlePalaceLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesBasics:: @ 824DD13
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesBasics, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesNature:: @ 824DD21
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesNature, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesMoves:: @ 824DD2F
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesMoves, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesUnderpowered:: @ 824DD3D
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesUnderpowered, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesWhenInDanger:: @ 824DD4B
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesWhenInDanger, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_ExitRules:: @ 824DD59
	releaseall
	end

BattleFrontier_BattlePalaceLobby_Text_WelcomeForSingleBattle: @ 824DD5B
	.string "트레이너의 마음을 시험하는 장소!\n"
	.string "배틀팰리스에 어서 오게\p"
	.string "여기서는 싱글 배틀홀로의\n"
	.string "도전을 받고 있지...$"
	// トレ-ナ-の こころを ためす ばしょｎ
	// バトルパレスへ ようこそｐ
	// ここでは シングル バトルホ-ルへのｎ
	// ちょうせんを うけつけて おる……

BattleFrontier_BattlePalaceLobby_Text_TakeSingleBattleChallenge: @ 824DDE1
	.string "싱글 배틀홀에\n"
	.string "도전할 텐가?$"
	// シングル バトルホ-ルにｎ
	// ちょうせん するか?

BattleFrontier_BattlePalaceLobby_Text_ExplainSingleBattleChallenge: @ 824DE17
	.string "여기에는 싱글 배틀홀이라는\n"
	.string "이름의 싱글배틀을 하기 위한\l"
	.string "방이 여러 개 준비되어 있네\p"
	.string "이곳의 배틀에서는\n"
	.string "반드시 지켜야만 하는\l"
	.string "하나의 규칙이 있지\p"
	.string "여기서는 포켓몬에게\n"
	.string "교체만 명령할 수 있고\p"
	.string "그 외의 명령은\n"
	.string "일체 금지되어 있다네!\p"
	.string "포켓몬이 성격대로\n"
	.string "생각하고 행동해야 하지!\p"
	.string "자네는 자신의\n"
	.string "포켓몬들을 믿고\l"
	.string "배틀을 지켜보면 된다네\p"
	.string "훌륭히 7명의 트레이너를\n"
	.string "돌파하게 된다면\l"
	.string "배틀포인트를 주도록 하지\p"
	.string "또한 도중에 도전을\n"
	.string "중단하고 싶을 경우에는\l"
	.string "제대로 리포트를 작성하지 않으면\l"
	.string "계속해서 도전할 수 없게 되니\l"
	.string "주의를 부탁하네...$"
	// ここには シングル バトルホ-ルとｎ
	// よばれる シングルバトルの ためのｌ
	// ひろまを いくつか ようい しておるｐ
	// ここでの たたかいにはｎ
	// まもらなければ ならないｌ
	// ひとつの おきてが あるｐ
	// ここでは ポケモンはｎ
	// いれかえ しか できない!ｐ
	// それいがいの めいれいはｎ
	// いっさい きんし して おるのだ!ｐ
	// ポケモンには せいかくの ままにｎ
	// かんがえ こうどう して もらう!ｐ
	// おぬしは じぶんのｎ
	// ポケモンたちを しんじてｌ
	// たたかいを みまもって やれｐ
	// みごと 7にんの トレ-ナ-をｎ
	// うちやぶることが できればｌ
	// バトルポイントを さしあげようｐ
	// また とちゅうで ちょうせんをｎ
	// ちゅうだん したい ときはｌ
	// きちんと レポ-トを かかないとｌ
	// つづけて ちょうせん できんからなｌ
	// きを つけてくれ……

BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified: @ 824E0D8
	.string "자신의 마음과 포켓몬을 단련하고\n"
	.string "나서 다시 오게나...$"
	// おのれの こころと ポケモンを きたえたらｎ
	// また くるがよい……

BattleFrontier_BattlePalaceLobby_Text_WhichChallenge: @ 824E119
	.string "레벨 50과 오픈 레벨의 방이\n"
	.string "있는데 어느 쪽에 도전할 텐가?$"
	// レベル50のへや オ-プンレベルのへやがｎ
	// あるが どちらに ちょうせん するのだ?

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLv50: @ 824E173
	.string "자네...\p"
	.string "도전할 수 있는 포켓몬이\n"
	.string "3마리는 필요하다네!\p"
	.string "도전하려면 레벨 50 이하의\n"
	.string "종류가 다른 포켓몬을\p"
	.string "3마리 준비해 주게\p"
	.string "또한 지니게 할 도구도\n"
	.string "모두 다른 도구여야 하네\p"
	.string "그리고 알{STR_VAR_1}"
	.string "참가시킬 수 없네!\p"
	.string "준비되면 다시 와 주게나$"
	// おぬし……ｐ
	// ちょうせん できる ポケモンがｎ
	// 3ひき おらんぞ!ｐ
	// ちょうせん するには レベルが 50いかでｎ
	// すべて ちがう しゅるいの ポケモンをｐ
	// 3ひき ようい してくれｐ
	// また もたせる どうぐもｎ
	// すべて ちがう もので なければ いかんｐ
	// そして タマゴ いちょうせん させる ことは できん!ｐ
	// じゅんびを ととのえてから また きなさい

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLvOpen: @ 824E29E
	.string "자네...\p"
	.string "도전할 수 있는 포켓몬이\n"
	.string "3마리는 필요하다네!\p"
	.string "도전하려면\n"
	.string "종류가 다른 포켓몬을\p"
	.string "3마리 준비해 주게\p"
	.string "또한 지니게 할 도구도\n"
	.string "모두 다른 도구여야 하네\p"
	.string "그리고 알{STR_VAR_1}"
	.string "참가시킬 수 없네!\p"
	.string "준비되면 다시 와 주게나$"
	// おぬし……ｐ
	// ちょうせん できる ポケモンがｎ
	// 3ひき おらんぞ!ｐ
	// ちょうせん するにはｎ
	// すべて ちがう しゅるいの ポケモンをｐ
	// 3ひき ようい してくれｐ
	// また もたせる どうぐもｎ
	// すべて ちがう もので なければ いかんｐ
	// そして タマゴ いちょうせん させる ことは できん!ｐ
	// じゅんびを ととのえてから また きなさい

BattleFrontier_BattlePalaceLobby_Text_NowSelectThreeMons: @ 824E399
	.string "그럼 도전할 포켓몬을\n"
	.string "3마리 고르게나$"
	// では ちょうせんする ポケモンをｎ
	// 3ひき えらんでくれ

BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge2: @ 824E3C8
	.string "배틀홀로 가기 전에\n"
	.string "리포트를 작성할 건데 괜찮겠는가?$"
	// バトルホ-ルへ むかうまえにｎ
	// レポ-トを かくが よろしいか?

BattleFrontier_BattlePalaceLobby_Text_FollowMe: @ 824E408
	.string "그럼\n"
	.string "나를 따라오게...$"
	// それではｎ
	// わしに ついてこい……

BattleFrontier_BattlePalaceLobby_Text_ResultsWillBeRecorded: @ 824E41E
	.string "좋은 구경을 했네\p"
	.string "그럼 성적을 리포트에 작성할 테니\n"
	.string "잠시 기다려 주게...$"
	// よいものを みせて もらったｐ
	// それでは せいせきを レポ-トに かくぞｎ
	// しばし またれよ……

BattleFrontier_BattlePalaceLobby_Text_FirmTrueBondsFor7WinStreak: @ 824E497
	.string "7연승 달성이라니...\p"
	.string "자네와 포켓몬의 마음속 유대감은\n"
	.string "진짜로구먼...$"
	// 7にんぬき たっせい とは……ｐ
	// おぬしと ポケモンの こころの きずなはｎ
	// まことの ようじゃな……

BattleFrontier_BattlePalaceLobby_Text_FeatWillBeRecorded: @ 824E4F7
	.string "성적을 리포트에 작성할 테니\n"
	.string "잠시 기다려 주게...$"
	// せいせきを レポ-トに かくぞｎ
	// しばし またれよ……

@ Unused
BattleFrontier_BattlePalaceLobby_Text_BattlePointsFor7WinStreak: @ 824E5333
    .string "7연승을 거둔 증거로\n"
    .string "배틀포인트를 주겠네...$"
	// 7にんぬきの あかしにｎ
	// バトルポイントを さしあげよう……

BattleFrontier_BattlePalaceLobby_Text_NoSpaceForPrize: @ 824E57B
	.string "도구가 가득한 모양이구먼...\p"
	.string "도구를 정리하고 나서\n"
	.string "다시 와 주게나...$"
	// どうぐが いっぱいの ようだな……ｐ
	// どうぐを せいりしてからｎ
	// また くるがよい……

BattleFrontier_BattlePalaceLobby_Text_WeHaveBeenWaiting: @ 824E5D8
	.string "기다리고 있었네...$"
	// まっておったぞ……

BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge: @ 824E5F6
	.string "배틀홀로 가기 전에\n"
	.string "리포트를 작성하겠네...$"
	// バトルホ-ルへ むかうまえにｎ
	// レポ-トを かくぞ……

BattleFrontier_BattlePalaceLobby_Text_FailedToSaveBeforeEndingChallenge: @ 824E636
	.string "자네...\p"
	.string "지난번 종료하기 전에\n"
	.string "리포트를 제대로\l"
	.string "작성하지 않았지?\p"
	.string "안타깝지만 이런 경우에는\n"
	.string "도전이 무효가 된다네...$"
	// おぬし……ｐ
	// ぜんかい ちゃんと レポ-トを かいてｎ
	// しゅうりょう しなかったな?ｐ
	// ざんねんだが そのばあいｎ
	// ちょうせんは むこうと なる……

@ Unused
BattleFrontier_BattlePalaceLobby_Text_ReceivedPrize: @ 824E6C9
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "{STR_VAR_1}{K_EULREUL} 받았다!$"
	// {PLAYER}はｎ
	// {STR_VAR_1}を もらった!

BattleFrontier_BattlePalaceLobby_Text_LadyCanTellWhatMonsThink: @ 824E6E3
	.string "후! 후! 노력가인 제게는\n"
	.string "노력하는 포켓몬이 딱 맞슴다!\p"
	.string "공격이야말로 최대의 방어!\n"
	.string "팍팍 공격해서 최고임다!\p"
	.string "그런데 잠깐 들어보십쇼\p"
	.string "두근두근 여기에 엄청\n"
	.string "귀여운 여자애가\l"
	.string "놀러오는데요\l"
	.string "그 애는 포켓몬의 생각을\l"
	.string "알 수 있다고 합니다\p"
	.string "이야- 정말 귀엽지 않습니까...\p"
	.string "...응 뭡니까? 그 눈은?$"
	// ウス! ウス! がんばりやの わしにはｎ
	// がんばりやの ポケモンが ぴったりっス!ｐ
	// こうげき こそ さいだいの ぼうぎょ!ｎ
	// ガンガン せめまくって さいこうっス!ｐ
	// ところで きいて くださいッスよ-ｐ
	// ときどき ここに とってもｎ
	// かわいい おじょうちゃんがｌ
	// あそびに くるッスけどｌ
	// そのこったら ポケモンの きもちがｌ
	// わかるとか いうんスよ-ｐ
	// いや- ほんと かわいいッスよね-……ｐ
	// …… ん なんスか? そのめは?

BattleFrontier_BattlePalaceLobby_Text_NatureAndMovesKeyHere: @ 824E851
	.string "으-음...\p"
	.string "아무래도 여기서는 포켓몬의 성격과\n"
	.string "배운 기술의 상성이\l"
	.string "배틀의 열쇠를 쥐고 있는 것 같아\p"
	.string "그래... 만약 네 포켓몬이\n"
	.string "자신의 힘을 발휘하지 못해\l"
	.string "곤란해하고 있다면\l"
	.string "배운 기술부터\l"
	.string "바꿀 필요가 있을지도 몰라$"
	// う-ん……ｐ
	// どうやら ここでは ポケモンの せいかくとｎ
	// おぼえさせている わざとの あいしょうがｌ
	// たたかいの カギを にぎってる ようだｐ
	// そう…… もし きみの ポケモンがｎ
	// じぶんの ちからが はっき できなくてｌ
	// こまっている ようす だったらｌ
	// おぼえさせている わざからｌ
	// かんがえ なおす ひつようが あるかもな

BattleFrontier_BattlePalaceLobby_Text_MonDocileButTransforms: @ 824E992
	.string "내 포켓몬\n"
	.string "평소에는 아주 얌전해\p"
	.string "근데 배틀홀에서 싸울 때에는\n"
	.string "가끔씩 눈빛이\l"
	.string "확 달라져!\p"
	.string "박력이 엄청나서 놀랐어!$"
	// あたしの ポケモンｎ
	// ふだんは と-っても おとなしいのよｐ
	// だけど バトルホ-ルで たたかってるとｎ
	// ときどき めつきがｌ
	// ガラッと かわっちゃうの!ｐ
	// すっごい はくりょくで びっくりしちゃう!

BattleFrontier_BattlePalaceLobby_Text_WhatNatureFavorsChippingAway: @ 824EA4B
	.string "상대를 약하게 하거나...\n"
	.string "천천히 몰아가는 건\l"
	.string "어떤 성격일까...\p"
	.string "...의외로 촐랑인가?\p"
	.string "...에이 설마...$"
	// あいてを よわらせたり……ｎ
	// じわじわ せめて くれるのはｌ
	// どんな せいかくかな……ｐ
	// …… いがいに のうてんき とか?ｐ
	// …… まさかねぇ……

BattleFrontier_BattlePalaceLobby_Text_WelcomeForDoubleBattle: @ 824EB06
	.string "트레이너의 마음을 시험하는 장소!\n"
	.string "배틀팰리스에 어서 오게\p"
	.string "여기서는 싱글 배틀홀로의\n"
	.string "도전을 받고 있지...$"
	// トレ-ナ-の こころを ためす ばしょｎ
	// バトルパレスへ ようこそｐ
	// ここでは ダブル バトルホ-ルへのｎ
	// ちょうせんを うけつけておる……

BattleFrontier_BattlePalaceLobby_Text_TakeDoubleBattleChallenge: @ 824EB8C
	.string "더블 배틀홀에\n"
	.string "도전할 텐가?$"
	// ダブル バトルホ-ルにｎ
	// ちょうせん するか?

BattleFrontier_BattlePalaceLobby_Text_ExplainDoubleBattleChallenge: @ 824EBC2
	.string "여기에는 더블 배틀홀이라는\n"
	.string "이름의 더블배틀을 하기 위한\l"
	.string "방이 여러 개 준비되어 있네\p"
	.string "이곳의 배틀에서는\n"
	.string "반드시 지켜야만 하는\l"
	.string "하나의 규칙이 있다네\p"
	.string "여기서는 포켓몬에게\n"
	.string "교체만 명령할 수 있고\p"
	.string "그 외의 명령은\n"
	.string "일체 금지되어 있다네!\p"
	.string "포켓몬이 성격대로\n"
	.string "생각하고 행동해야 하지!\p"
	.string "자네는 자신의\n"
	.string "포켓몬들을 믿고\l"
	.string "배틀을 지켜보면 된다네\p"
	.string "훌륭히 7명의 트레이너를\n"
	.string "돌파하게 된다면\l"
	.string "배틀포인트를 주도록 하지\p"
	.string "또한 도중에 도전을\n"
	.string "중단하고 싶을 경우에는\l"
	.string "제대로 리포트를 작성하지 않으면\l"
	.string "계속해서 도전할 수 없게 되니\l"
	.string "주의를 부탁하네...$"
	// ここには ダブル バトルホ-ルとｎ
	// よばれる ダブルバトルの ためのｌ
	// ひろまを いくつか ようい しておるｐ
	// ここでの たたかいにはｎ
	// まもらなければ ならないｌ
	// ひとつの おきてが あるｐ
	// ここでは ポケモンはｎ
	// いれかえ しか できない!ｐ
	// それいがいの めいれいはｎ
	// いっさい きんし して おるのだ!ｐ
	// ポケモンには せいかくの ままにｎ
	// かんがえ こうどう して もらう!ｐ
	// おぬしは じぶんのｎ
	// ポケモンたちを しんじてｌ
	// たたかいを みまもって やれｐ
	// みごと 7にんの トレ-ナ-をｎ
	// うちやぶることが できればｌ
	// バトルポイントを さしあげようｐ
	// また とちゅうで ちょうせんをｎ
	// ちゅうだん したい ときはｌ
	// きちんと レポ-トを かかないとｌ
	// つづけて ちょうせん できんからなｌ
	// きを つけてくれ……

BattleFrontier_BattlePalaceLobby_Text_ToDefeatMavenAnd7Trainers: @ 824EE81
	.string "팰리스가디언을 쓰러뜨리고\n"
	.string "7연승을 달성하다니...$"
	// パレスガ-ディアンを たおしｎ
	// 7にんぬきを たっせいするとは……

BattleFrontier_BattlePalaceLobby_Text_PresentYouWithBattlePoints: @ 824EEB9
	.string "자네와 포켓몬의 유대감을 기려서\n"
	.string "배틀포인트를 수여하겠네...$"
	// おぬしと ポケモンの きずなを たたえｎ
	// バトルポイントを おくろう……

BattleFrontier_BattlePalaceLobby_Text_LikeToRecordMatch: @ 824EF16
	.string "배틀팰리스에서\n"
	.string "마지막에 했던 배틀을\l"
	.string "프런티어패스에 기록하겠나?$"
	// バトルパレスでｎ
	// さいごに おこなった たたかいをｌ
	// フロンティアパスに きろく するか?

BattleFrontier_BattlePalaceLobby_Text_RulesAreListed: @ 824EF66
	.string "배틀홀의 규칙이 적혀 있다!$"
	// バトルホ-ルの ル-ルが かかれている!

BattleFrontier_BattlePalaceLobby_Text_ReadWhichHeading: @ 824EF88
	.string "어느 설명을 읽겠습니까?$"
	// どの せつめいを よみますか?

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesBasics: @ 824EFAB
	.string "여기서는 포켓몬들이\n"
	.string "스스로 생각해서 배틀합니다\p"
	.string "순수한 야생과는 달리\n"
	.string "사람과 살아온 포켓몬은\l"
	.string "성격에 따라 어떤 행동을\l"
	.string "할지가 결정됩니다$"
	// ここでは ポケモンたちがｎ
	// じぶんで かんがえ たたかいますｐ
	// じゅんすいな やせいの ときとは ちがってｎ
	// ひとと くらしている ポケモンはｌ
	// せいかくに よって どんな こうどうをｌ
	// するかが かわるのです

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesNature: @ 824F049
	.string "아무튼 공격하는 것을\n"
	.string "선호하는 성격\p"
	.string "자신의 몸을 지키는 것을\n"
	.string "선호하는 성격\p"
	.string "상대를 난처하게\n"
	.string "만드는 것을 선호하는 성격\p"
	.string "포켓몬은 성격에 따라\n"
	.string "좋아하고 능숙한 기술과\l"
	.string "싫어하고 서투른 기술이 다릅니다$"
	// とにかく こうげきがｎ
	// すきな せいかくｐ
	// じぶんの からだを まもる ことがｎ
	// すきな せいかくｐ
	// あいてを こまらせたり かわった ことをｎ
	// するのが すきな せいかくｐ
	// ポケモンは せいかくに よってｎ
	// すきで とくいな わざとｌ
	// きらいで にがてな わざが ちがいます

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesMoves: @ 824F190
	.string "상대를 향해서 자신이\n"
	.string "직접 데미지를 주는\l"
	.string "공격 기술\p"
	.string "배틀의 준비나 상처입은 몸을\n"
	.string "회복하는 방어 기술\p"
	.string "상대의 능력을 내리거나\n"
	.string "독이나 마비를 거는 등의\l"
	.string "조금 변화를 주는 기술\p"
	.string "포켓몬은 모든 기술은\n"
	.string "크게 3개의 종류로 나눠서\l"
	.string "어떤 기술을 쓸지 생각합니다$"
	// あいてに むかって じぶんからｎ
	// ちょくせつ ダメ-ジを あたえるｌ
	// こうげきの わざｐ
	// たたかいの じゅんびや キズついた からだのｎ
	// かいふくを する ぼうぎょの わざｐ
	// あいての のうりょくを さげたりｎ
	// どくや まひに したり などのｌ
	// すこし かわった ことを する わざｐ
	// ポケモンは すべての わざをｎ
	// おおきく 3つの しゅるいに わけてｌ
	// どんな わざを だすか かんがえて います

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesUnderpowered: @ 824F2E8
	.string "트레이너의 명령을 받지 않는\n"
	.string "포켓몬은 기술을 잘\l"
	.string "쓸 수 없을 때가 있습니다\p"
	.string "포켓몬은 싫어하는 기술을\n"
	.string "쓰는 것에 서투릅니다\p"
	.string "성격에 맞지 않는 기술만을\n"
	.string "배우고 있다면 배틀에서\l"
	.string "포켓몬이 자신의 힘을 발휘할\l"
	.string "수 없을 확률이 큽니다$"
	// トレ-ナ-の めいれいを うけて いないｎ
	// ポケモンは うまく わざをｌ
	// だせない ことが ありますｐ
	// ポケモンは きらいな わざをｎ
	// つかうのは とくいでは ありませんｐ
	// せいかくに あわない わざ ばかりをｎ
	// おぼえさせて いると たたかいでｌ
	// ポケモンが じぶんの ちからを はっきｌ
	// できない ことが おおく なります

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesWhenInDanger: @ 824F3F4
	.string "포켓몬의 성격 중에서는\n"
	.string "위기에 몰리면 원래\l"
	.string "성격과는 다른 종류의\l"
	.string "기술을 쓰는\l"
	.string "경우가 있습니다\p"
	.string "위기에 몰렸을 때 조금\n"
	.string "다른 행동을 시작한 포켓몬은\l"
	.string "주의하도록 합시다$"
	// ポケモンの せいかくの なかにはｎ
	// ピンチに なることで もともとのｌ
	// せいかくとは ちがう タイプのｌ
	// わざを つかう ようにｌ
	// なるものが ありますｐ
	// ピンチに なって すこし かわったｎ
	// こうどうを はじめた ポケモンにはｌ
	// じゅうぶん ちゅうい しましょう

