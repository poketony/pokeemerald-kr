.set LOCALID_ATTENDANT_SINGLES, 1
.set LOCALID_ATTENDANT_DOUBLES, 6

BattleFrontier_BattleFactoryLobby_MapScripts:: @ 82583E8
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleFactoryLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleFactoryLobby_OnWarp
	.byte 0

BattleFrontier_BattleFactoryLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleFactoryLobby_OnFrame:
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_WON, BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_LOST, BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	factory_setswapped
	factory_set FACTORY_DATA_WIN_STREAK_SWAPS, 0
	factory_set FACTORY_DATA_WIN_STREAK, 0
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	factory_save 0
	playse SE_SAVE
	waitse
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle
	end

BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	factory_save 0
	playse SE_SAVE
	waitse

BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle:: @ 825853B
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
	message BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle

BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume
	waitmessage
	factory_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_0, 255
	setvar VAR_0x8006, 2
	goto BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge

BattleFrontier_BattleFactoryLobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
	end

BattleFrontier_BattleFactoryLobby_EventScript_DoublesAttendant::
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
	end

BattleFrontier_BattleFactoryLobby_EventScript_Attendant::
	special SavePlayerParty
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle
BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge::
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, 0
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_0, 0
	factory_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_0, 255
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed
	setvar VAR_0x8006, 0
BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	msgbox BattleFrontier_BattleFactoryLobby_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor
	waitmovement 0
	warp MAP_BATTLE_FRONTIER_BATTLE_FACTORY_PRE_BATTLE_ROOM, 255, 8, 13
	setvar VAR_TEMP_0, 0
	waitstate
	end

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant:: @ 825875C
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_SINGLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant:: @ 8258762
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_DOUBLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge::
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	call_if_eq BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge
	compare VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	call_if_eq BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor:
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ShowSinglesResults::
	lockall
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults::
	lockall
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Camper::
	msgbox BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Picnicker::
	lock
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_EventScript_FatMan::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 0, MULTI_BATTLE_FACTORY_RULES, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber
	case 3, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes
	case 4, BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv
	case 5, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle:
	.string "트레이너의 지식을 겨루는 장소!!\n"
	.string "배틀팩토리에 어서 오세요!\p"
	.string "배틀트레이드 싱글의\n"
	.string "안내를 하고 있습니다!$"
	// トレ-ナ-の ちしきを はかる ばしょ!!ｎ
	// バトルファクトリ-に ようこそ!ｐ
	// バトルトレ-ド シングルへのｎ
	// ごあんないは こちらです!

BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge:
	.string "배틀트레이드 싱글에\n"
	.string "도전하겠습니까?$"
	// バトルトレ-ド シングルにｎ
	// ちょうせん しますか?

BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge:
	.string "여기서는 대여 포켓몬을 빌려서\n"
	.string "배틀트레이드 싱글이라는\l"
	.string "이벤트를 열고 있습니다!\p"
	.string "우선 배틀트레이드 전용의\n"
	.string "포켓몬 3마리를 빌려드립니다!\p"
	.string "다음은 그 포켓몬을\n"
	.string "써서 싱글배틀을\l"
	.string "치루시면 됩니다!\p"
	.string "배틀에서 승리하면 한 번만\n"
	.string "포켓몬을 트레이드할 수 있습니다!\p"
	.string "트레이드와 배틀을 반복해서\n"
	.string "멋지게 7연승을 하시면\l"
	.string "배틀포인트를 드립니다!\p"
	.string "또한 도중에 도전을\n"
	.string "중단하고 싶을 경우에는\l"
	.string "제대로 리포트를 작성하지 않으면\l"
	.string "계속해서 도전할 수 없습니다!\p"
	.string "아무쪼록 주의를 부탁드립니다!$"
	// こちらでは レンタルポケモンを つかったｎ
	// バトルトレ-ド シングル というｌ
	// イベントを おこなって います!ｐ
	// まずは バトルトレ-ド せんようのｎ
	// ポケモン 3ひきを おかし します!ｐ
	// つぎに そちらの ポケモンをｎ
	// つかって シングルバトルをｌ
	// おこなって いただきます!ｐ
	// たたかいに しょうりすると いちど だけｎ
	// ポケモンを トレ-ド できます!ｐ
	// トレ-ドと たたかいを くりかえしｎ
	// みごと 7れんしょう したらｌ
	// バトルポイントを さしあげます!ｐ
	// なお とちゅうで ちょうせんをｎ
	// ちゅうだん したい ばあいはｌ
	// きちんと レポ-トを かかないとｌ
	// つづけて ちょうせんが できません!ｐ
	// くれぐれも きをつけて くださいね!

BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit:
	.string "다음 이용을 기다리고 있겠습니다!$"
	// またの ごりようを おまちしていますよ!

BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode:
	.string "레벨 50과 오픈 레벨의 이벤트\n"
	.string "어느 쪽에 도전하겠습니까?$"
	// レベル50と オ-プンレベルの イベントｎ
	// どちらに ちょうせん しますか?

BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge:
	.string "그럼 도전을 시작하기 전에\n"
	.string "리포트를 작성합니다만 괜찮겠습니까?$"
	// では ちょうせんを はじめる まえにｎ
	// レポ-トを かきますが よろしいですか?

BattleFrontier_BattleFactoryLobby_Text_WillHoldMonsForSafekeeping:
	.string "그럼 포켓몬을\n"
	.string "맡아두겠습니다!$"
	// それでは ポケモンをｎ
	// おあずかり します!

BattleFrontier_BattleFactoryLobby_Text_StepThisWay:
	.string "자자 이쪽으로 와 주세요!$"
	// さあさあ こちらに どうぞ!

BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults:
	.string "수고하셨습니다!\p"
	.string "대여 포켓몬과\n"
	.string "맡아두고 있던 포켓몬을\l"
	.string "교환합니다!\p"
	.string "성적을 리포트에 작성하므로\n"
	.string "잠시 기다려 주십시오!$"
	// おつかれさまでした!ｐ
	// レンタルポケモンとｎ
	// おあずかり していた ポケモンをｌ
	// こうかん します!ｐ
	// せいせきを レポ-トに かきますのでｎ
	// しょうしょう おまちください!

BattleFrontier_BattleFactoryLobby_Text_ReturnMons:
	.string "대여 포켓몬과\n"
	.string "맡아두고 있던 포켓몬을\l"
	.string "교환합니다!$"
	// レンタルポケモンとｎ
	// おあずかり していた ポケモンをｌ
	// こうかん します!

BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins:
	.string "배틀트레이드 7전 돌파\n"
	.string "축하드립니다!$"
	// バトルトレ-ド 7せん とっぱｎ
	// おめでとう ございます!

BattleFrontier_BattleFactoryLobby_Text_AwardBattlePointsForStreak:
	.string "7연승을 한 기념으로\n"
	.string "배틀포인트를 드립니다!$"
	// 7れんしょうを きねんしてｎ
	// バトルポイントを さしあげます!

BattleFrontier_BattleFactoryLobby_Text_MaxBattlePoints:
	.string "어라라?\p"
	.string "배틀포인트가 가득 찼군요-\p"
	.string "포인트를 사용하고 나서\n"
	.string "다시 와주십시오!$"
	// おやや?ｐ
	// バトルポイントが いっぱい ですね-ｐ
	// ポイントを ごりようしてからｎ
	// また きてください!

BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume:
	.string "기다리고 있었습니다!\p"
	.string "도전을 재개하기 전에\n"
	.string "리포트를 작성합니다!$"
	// おまちしておりましたよ!ｐ
	// ちょうせんを さいかいする まえにｎ
	// レポ-トを かきます!

BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting:
	.string "손님-!!\p"
	.string "지난번에 종료하기 전에 리포트를\n"
	.string "제대로 작성하지 않으셨죠!\p"
	.string "죄송합니다만\n"
	.string "도전은 무효가 됩니다!$"
	// おきゃくさま-!!ｐ
	// ぜんかい ちゃんと レポ-トを かいてｎ
	// しゅうりょう しません でしたね!ｐ
	// ざんねんですがｎ
	// ちょうせんは むこうと なります!

BattleFrontier_BattleFactoryLobby_Text_WellReturnMons:
	.string "손님의 포켓몬을\n"
	.string "돌려드리겠습니다!$"
	// おきゃくさまの ポケモンをｎ
	// おかえしします!

BattleFrontier_BattleFactoryLobby_Text_ReceivedPrizeItem:
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "{STR_VAR_1}{K_EULREUL} 받았다!$"

BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle:
	.string "트레이너의 지식을 겨루는 장소!!\n"
	.string "배틀팩토리에 어서 오세요!\p"
	.string "배틀트레이드 더블의\n"
	.string "안내를 하고 있습니다!$"
	// トレ-ナ-の ちしきを はかる ばしょ!!ｎ
	// バトルファクトリ-に ようこそ!ｐ
	// バトルトレ-ド ダブルのｎ
	// ごあんないは こちらです!

BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge:
	.string "배틀팩토리 더블에\n"
	.string "도전하겠습니까?$"
	// バトルトレ-ド ダブルにｎ
	// ちょうせん しますか?

BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge:
	.string "여기서는 대여 포켓몬을 빌려서\n"
	.string "배틀트레이드 더블이라는\l"
	.string "이벤트를 열고 있습니다!\p"
	.string "우선 배틀트레이드 전용의\n"
	.string "포켓몬 3마리를 빌려드립니다!\p"
	.string "다음은 그 포켓몬을\n"
	.string "써서 더블배틀을\l"
	.string "치루시면 됩니다!\p"
	.string "배틀에서 승리하면 한 번만\n"
	.string "포켓몬을 트레이드할 수 있습니다!\p"
	.string "트레이드와 배틀을 반복해서\n"
	.string "멋지게 7연승을 하시면\l"
	.string "배틀포인트를 드립니다!\p"
	.string "또한 도중에 도전을\n"
	.string "중단하고 싶을 경우에는\l"
	.string "제대로 리포트를 작성하지 않으면\l"
	.string "계속해서 도전할 수 없습니다!\p"
	.string "부디 주의해 주십시오!$"
	// こちらでは レンタルポケモンを つかったｎ
	// バトルトレ-ド ダブル というｌ
	// イベントを おこなって いますｐ
	// まずは バトルトレ-ド せんようのｎ
	// ポケモン 3ひきを おかし します!ｐ
	// つぎに そちらの ポケモンをｎ
	// つかって ダブルバトルをｌ
	// おこなって いただきます!ｐ
	// たたかいに しょうりすると いちど だけｎ
	// ポケモンを トレ-ド できます!ｐ
	// トレ-ドと たたかいを くりかえしｎ
	// みごと 7れんしょうを したらｌ
	// バトルポイントを さしあげます!ｐ
	// なお とちゅうで ちょうせんをｎ
	// ちゅうだん したい ときにはｌ
	// きちんと レポ-トを かかないとｌ
	// つづけて ちょうせんが できません!ｐ
	// くれぐれも きをつけて くださいね!

BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead:
	.string "팩토리책임자에게서 승리!\n"
	.string "또 7연승 달성을\l"
	.string "축하드립니다!$"
	// ファクトリ-ヘッドへの しょうり!ｎ
	// ならびに 7れんしょう たっせいｌ
	// おめでとう ございます!

BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints:
	.string "손님의 깊은 지식을 기리며\n"
	.string "배틀포인트를 드리겠습니다!$"
	// おきゃくさまの ふかい ちしきを たたえｎ
	// バトルポイントを さしあげます!

BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave:
	.string "대여 포켓몬과\n"
	.string "맡아두고 있던 포켓몬을\l"
	.string "교환합니다!\p"
	.string "성적을 리포트에 작성하므로\n"
	.string "잠시 기다려 주십시오!$"
	// レンタルポケモンとｎ
	// おあずかり していた ポケモンをｌ
	// こうかん しましょう!ｐ
	// せいせきを レポ-トに かきますのでｎ
	// しょうしょう おまちください!

BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch:
	.string "배틀팩토리에서\n"
	.string "마지막으로 한 배틀을\l"
	.string "프런티어패스에 기록하겠습니까?$"
	// バトルファクトリ-でｎ
	// さいごに おこなった たたかいをｌ
	// フロンティアパスに きろく いたしますか?

BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves:
	.string "잠깐! 너!\p"
	.string "포켓몬을 키우지 않아도\n"
	.string "도전할 수 있으니까 쉽네-!\p"
	.string "라고 생각하는 거 아냐?\p"
	.string "여기는 포켓몬과 그 기술에\n"
	.string "관한 지식이 없으면\l"
	.string "이겨나가기 엄-청나게\l"
	.string "힘든 장소라고!!$"
	// ちょっと! キミ!ｐ
	// ポケモンを そだてなくてもｎ
	// ちょうせん できる から らくしょう-!ｐ
	// とか おもってない?ｐ
	// ここは ポケモンと そのわざにｎ
	// かんする ちしきが ないとｌ
	// かちぬけない ひじょうに きびし-ｌ
	// ところ なのよ!!

BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon:
	.string "종류에 속아서 약한 포켓몬과\n"
	.string "교환해 버렸어...\p"
	.string "완패야...$"
	// しゅるいに だまされて よわいポケモンとｎ
	// こうかん しちゃった……ｐ
	// ボロまけ……

BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons:
	.string "안되겠네-!\p"
	.string "트레이너가 좋은 포켓몬을 가지고\n"
	.string "있으면 배틀하는 도중에\l"
	.string "체크해야겠어!$"
	// ダメダメね-!ｐ
	// トレ-ナ-が いいポケモン もってたらｎ
	// たたかいの あいだにｌ
	// チェック しとかなきゃ!

BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints:
	.string "여기 스태프 말야 배틀하기 전에\n"
	.string "다음에 싸울 트레이너에 대해\l"
	.string "조금만 알려주잖아-?\p"
	.string "근데 나 어른인데도\n"
	.string "그 녀석들이 하는 설명을\l"
	.string "전혀 못 알아듣겠어$"
	// ここの スタッフさぁ たたかいの まえにｎ
	// つぎに たたかう トレ-ナ-のことｌ
	// ちょっとだけ おしえて くれるだろ-?ｐ
	// でも オレ いい おとな なのにｎ
	// あいつらの せつめいの いみがｌ
	// ぜんぜん わからないんだ よう

BattleFrontier_BattleFactoryLobby_Text_RentalMonsAreVaried:
	.string "나- 제법- 강한데-\n"
	.string "엄청- 지친다-\l"
	.string "일단-\l"
	.string "모두 트레이드하면서-\l"
	.string "배틀하고 있었는데-\l"
	.string "그랬더니 말야-\l"
	.string "계속해서 배틀트레이드에-\l"
	.string "도전했을 때-\l"
	.string "대여해주는-\l"
	.string "포켓몬의-\l"
	.string "종류가 말이지-\l"
	.string "조금씩 말이지-\l"
	.string "달랐던 것 같아-$"
	// ぼくって- バッチリ- つよいけど-ｎ
	// すっごく- あきっぽい からさ-ｌ
	// とりあえず-ｌ
	// ばんばん トレ-ド しながら-ｌ
	// たたかってたのさ-ｌ
	// そしたらさ-ｌ
	// つづけて- バトルトレ-ドに-ｌ
	// ちょうせん したとき-ｌ
	// レンタル してくれる-ｌ
	// ポケモンの-ｌ
	// しゅるいがさ-ｌ
	// なんかさ-ｌ
	// ちょっとさ-ｌ
	// ちがったんだよね-

BattleFrontier_BattleFactoryLobby_Text_RulesAreListed:
	.string "배틀트레이드의 규칙이 적혀 있다!$"
	// バトルトレ-ドの ル-ルが かかれている!

BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading:
	.string "어느 설명을 읽겠습니까?$"
	// どの せつめいを よみますか?

BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules:
	.string "배틀트레이드에서 사용할 수 있는\n"
	.string "포켓몬은 3마리까지입니다\p"
	.string "대여할 때 트레이드할 때\n"
	.string "어느 때라도\l"
	.string "같은 종류의 포켓몬을\l"
	.string "2마리 이상 지닐 수는 없습니다$"
	// バトルトレ-ドで つかうことの できるｎ
	// ポケモンは 3ひき まで ですｐ
	// レンタルするとき トレ-ドするときｎ
	// どちらの とき でもｌ
	// おなじ しゅるいの ポケモンをｌ
	// 2ひき いじょう もつことは できません

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules:
	.string "트레이드할 수 있는 상대는\n"
	.string "당신이 배틀에서\l"
	.string "쓰러뜨린 트레이너입니다\p"
	.string "트레이드로 받을 수 있는 건\n"
	.string "트레이너가 사용하던 포켓몬입니다$"
	// トレ-ドが できる あいてはｎ
	// あなたが たたかいでｌ
	// たおした トレ-ナ-ですｐ
	// トレ-ドで うけとる ことが できるのはｎ
	// トレ-ナ-が つかっていた ポケモンです

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules:
	.string "한 번 배틀에서 이길 때마다\n"
	.string "1회에 1마리만 포켓몬을\l"
	.string "트레이드할 수 있습니다\p"
	.string "1회의 도전으로\n"
	.string "트레이드할 수 있는 건\l"
	.string "6번째의 트레이너까지입니다$"
	// いちど たたかいに かつ たびにｎ
	// 1かい 1ひき だけ ポケモンをｌ
	// トレ-ド することが できますｐ
	// 1かいの ちょうせんでｎ
	// トレ-ドが できるのはｌ
	// 6にんめの トレ-ナ-まで です

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules:
	.string "트레이드를 할 때에는\n"
	.string "2개 주의할 사항이 있습니다\p"
	.string "1번째로 트레이드를 할 때는\n"
	.string "상대로부터 받는 포켓몬의\l"
	.string "능력치를 확인할 수 없습니다\p"
	.string "2번째로 도전을 시작했을 때에\n"
	.string "빌린 대여 포켓몬의 순서가\l"
	.string "트레이드 이후의 배틀에도\l"
	.string "이어지게 됩니다$"
	// トレ-ドを おこなう ときにはｎ
	// 2つ ちゅういする ことが ありますｐ
	// その1 トレ-ドを おこなう ときはｎ
	// あいてから うけとる ポケモンのｌ
	// つよさは かくにん できませんｐ
	// その2 ちょうせんを はじめた ときにｎ
	// かりた レンタルポケモンの じゅんばんがｌ
	// トレ-ドの あとの たたかいにもｌ
	// ひきつがれます

BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules:
	.string "오픈 레벨의 도전에서는\n"
	.string "대여할 수 있는 포켓몬도\l"
	.string "상대 트레이너가 쓰는 포켓몬도\l"
	.string "모두 레벨 100이 됩니다$"
	// オ-プンレベルの ちょうせんではｎ
	// レンタルできる ポケモンもｌ
	// あいての トレ-ナ-が つかう ポケモンもｌ
	// すべて レベル100に なります
