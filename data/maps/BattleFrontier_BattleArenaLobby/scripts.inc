.set LOCALID_ATTENDANT, 1

BattleFrontier_BattleArenaLobby_MapScripts:: @ 8255C36
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleArenaLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleArenaLobby_OnWarp
	.byte 0

BattleFrontier_BattleArenaLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleArenaLobby_OnFrame:
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_WON, BattleFrontier_BattleArenaLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_LOST, BattleFrontier_BattleArenaLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown, MSGBOX_DEFAULT
	closemessage
	arena_set ARENA_DATA_WIN_STREAK, 0
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon::
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleArenaLobby_Text_RecordAchievement
	waitmessage
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave
	waitmessage
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	arena_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	message BattleFrontier_BattleArenaLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	case 0, BattleFrontier_BattleArenaLobby_EventScript_RecordMatch
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge

BattleFrontier_BattleArenaLobby_EventScript_RecordMatch::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge::
	return

BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame
	waitmessage
	arena_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_0, 255
	goto BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge

BattleFrontier_BattleArenaLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARENA
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, 0
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	frontier_checkineligible
	compare VAR_0x8004, TRUE
	goto_if_eq BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleArenaLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_OkayToSave, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_0, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	arena_init
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_0, 255
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattleArenaLobby_Text_GuideYouToArena, MSGBOX_DEFAULT
	closemessage
	frontier_get FRONTIER_DATA_LVL_MODE
	compare VAR_RESULT, FRONTIER_LVL_50
	call_if_eq BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50
	compare VAR_RESULT, FRONTIER_LVL_OPEN
	call_if_eq BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen
	warp MAP_BATTLE_FRONTIER_BATTLE_ARENA_CORRIDOR, 255, 9, 13
	setvar VAR_TEMP_0, 0
	waitstate
	end

BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50:: @ 8256005
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor
	waitmovement 0
	opendoor 2, 2
	waitdooranim
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen:: @ 8256050
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor
	waitmovement 0
	opendoor 11, 2
	waitdooranim
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 11, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

BattleFrontier_BattleArenaLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_ARENA
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_Youngster::
	msgbox BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Man::
	msgbox BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Camper::
	msgbox BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 2, MULTI_BATTLE_ARENA_RULES, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_BattleRules
	case 1, BattleFrontier_BattleArenaLobby_EventScript_MindRules
	case 2, BattleFrontier_BattleArenaLobby_EventScript_SkillRules
	case 3, BattleFrontier_BattleArenaLobby_EventScript_BodyRules
	case 4, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	end

BattleFrontier_BattleArenaLobby_EventScript_BattleRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_MindRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainMindRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_SkillRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_BodyRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena:
	.string "트레이너의 투지를 시험하는 장소!!\p"
	.string "배틀아레나에\n"
	.string "어서 오십시오!\p"
	.string "여기서는 연승팀배틀의\n"
	.string "안내를 하고 있습니다!$"
	@ トレ-ナ-の とうしを ためす ばしょ!!ｐ
	@ バトルアリ-ナへｎ
	@ ようこそ おいでなされた!ｐ
	@ こちらでは かちぬきチ-ムバトルのｎ
	@ あんないを しておりますぞ!

BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge:
	.string "배틀아레나에\n"
	.string "도전하겠습니까?$"
	@ バトルアリ-ナにｎ
	@ ちょうせん されますかな?

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge:
	.string "다음에 또 도전해 주시죠\n"
	.string "기다리고 있겠습니다!$"
	@ またの ちょうせんをｎ
	@ おまちして おりますぞ!

BattleFrontier_BattleArenaLobby_Text_ExplainChallenge:
	.string "배틀아레나는 연승팀배틀을\n"
	.string "할 수 있는 시설입니다!\p"
	.string "참가하는 분께서는 출전시킬\n"
	.string "3마리의 포켓몬과 배틀에 내보낼\l"
	.string "순서를 정해 주십시오!\p"
	.string "배틀하는 동안은\n"
	.string "이 순서대로\l"
	.string "포켓몬을 내보내게 됩니다!\p"
	.string "배틀에 한번 내보낸 포켓몬은\n"
	.string "결착이 날 때까지\l"
	.string "교체할 수 없습니다!\p"
	.string "게다가 3턴 이내에\n"
	.string "배틀의 결착이 나지 않는다면\l"
	.string "판정이 나게 됩니다!\p"
	.string "또한 도중에 도전을\n"
	.string "중단하고 싶을 경우에는\l"
	.string "리포트를 작성하지 않으면\l"
	.string "계속해서 도전을 할 수 없으므로\l"
	.string "주의해 주십시오!\p"
	.string "멋지게 7명을 돌파하시면\n"
	.string "배틀포인트를 드립니다!$"
	@ バトルアリ-ナは かちぬきチ-ムバトルをｎ
	@ おこなう しせつですぞ!ｐ
	@ さんかする かたには しゅつじょう させるｎ
	@ 3ひきの ポケモンと たたかいに だすｌ
	@ じゅんばんを きめて いただきますぞ!ｐ
	@ たたかいの あいだはｎ
	@ この じゅんばん どおりにｌ
	@ ポケモンを だすことに なりますな!ｐ
	@ たたかいに いちど だした ポケモンはｎ
	@ けっちゃくが つくまでｌ
	@ こうたい させる ことが できませぬ!ｐ
	@ さらに 3タ-ン いないにｎ
	@ たたかいの けっちゃくが つかなければｌ
	@ はんていと なりますぞ!ｐ
	@ また とちゅうで ちょうせんをｎ
	@ ちゅうだんしたい ばあいはｌ
	@ レポ-トを かかないとｌ
	@ つづけて ちょうせんが できないのでｌ
	@ おきをつけ くだされ!ｐ
	@ みごと 7にんぬきを なされた あかつきにはｎ
	@ バトルポイントを おおくり いたしますぞ!

BattleFrontier_BattleArenaLobby_Text_OkayToSave:
	.string "배틀아레나에 입장하기 전에\n"
	.string "리포트를 작성합니다만 괜찮겠습니까?$"
	@ バトルアリ-ナへ おつれする まえにｎ
	@ レポ-トを かきますが よろしいですかな?

BattleFrontier_BattleArenaLobby_Text_WhichLevelMode:
	.string "배틀아레나에는\n"
	.string "레벨 50과 오픈 레벨이 있습니다만\l"
	.string "어느 쪽으로 입장하겠습니까?$"
	@ バトルアリ-ナにはｎ
	@ レベル50と オ-プンレベルと ありますがｌ
	@ どちらに まいられますかな?

BattleFrontier_BattleArenaLobby_Text_SelectThreeMons:
	.string "그럼 참가할 포켓몬을\n"
	.string "3마리 선택해 주십시오!$"
	@ では さんかする ポケモンをｎ
	@ 3ひき おえらび くだされ!

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen:
	.string "손님!!\p"
	.string "참가할 수 있는 포켓몬이\n"
	.string "3마리는 필요합니다!\p"
	.string "참가하려면\n"
	.string "종류가 다른 포켓몬을\l"
	.string "3마리 준비해 주십시오!\p"
	.string "또한 지니게 할 도구도\n"
	.string "모두 다른 도구로 해주십시오!\p"
	.string "그리고 알{STR_VAR_1}"
	.string "참가시킬 수 없습니다!\p"
	.string "준비되면\n"
	.string "다시 방문해 주십시오!$"
	@ おきゃくじん!!ｐ
	@ さんかできる ポケモンがｎ
	@ 3ひき おりませぬ!ｐ
	@ さんかする ためにはｎ
	@ すべて ちがう しゅるいの ポケモンをｌ
	@ 3ひき よういして くだされ!ｐ
	@ また もたせる どうぐもｎ
	@ すべて ちがう どうぐに してくだされ!ｐ
	@ なお タマゴ{STR_VAR_1}さんか させる ことは できませぬ!ｐ
	@ じゅんびが できましたらｎ
	@ また おこし くだされ!

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50:
	.string "손님!!\p"
	.string "참가할 수 있는 포켓몬이\n"
	.string "3마리는 필요합니다!\p"
	.string "참가하려면 레벨 50 이하의\n"
	.string "종류가 다른 포켓몬을\l"
	.string "3마리 준비해 주십시오!\p"
	.string "또한 지니게 할 도구도\n"
	.string "모두 다른 도구로 해주십시오!\p"
	.string "그리고 알{STR_VAR_1}"
	.string "참가시킬 수 없습니다!\p"
	.string "준비되면\n"
	.string "다시 방문해 주십시오!$"
	@ おきゃくじん!!ｐ
	@ さんかできる ポケモンがｎ
	@ 3ひき おりませぬ!ｐ
	@ さんかする ためには レベルが 50いかでｎ
	@ すべて ちがう しゅるいの ポケモンをｌ
	@ 3ひき よういして くだされ!ｐ
	@ また もたせる どうぐもｎ
	@ すべて ちがう どうぐに してくだされ!ｐ
	@ なお タマゴ{STR_VAR_1}さんか させる ことは できませぬ!ｐ
	@ じゅんびが できましたらｎ
	@ また おこし くだされ!

BattleFrontier_BattleArenaLobby_Text_GuideYouToArena:
	.string "그럼 배틀아레나로\n"
	.string "안내하겠습니다!$"
	@ では バトルアリ-ナへｎ
	@ おつれいたしますぞ!

BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown:
	.string "손님!\p"
	.string "지난번 종료하기 전에\n"
	.string "리포트를 제대로 작성하지 않으셨죠?\p"
	.string "유감이지만 이런 경우에는\n"
	.string "도전이 무효가 됩니다!\p"
	.string "다시 처음부터\n"
	.string "도전해 주십시오!!$"
	@ おきゃくじん!ｐ
	@ ぜんかい レポ-トを かいてｎ
	@ しゅうりょう しませんでしたな?ｐ
	@ ざんねんですが その ばあいｎ
	@ ちょうせんは むこうと なりますぞ!ｐ
	@ また はじめからｎ
	@ ちょうせん してくだされ!!

BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins:
	.string "7명 돌파를 달성하셨군요\n"
	.string "정말로 멋졌습니다!$"
	@ 7にんぬき たっせいｎ
	@ おみごとで ございました!

BattleFrontier_BattleArenaLobby_Text_RecordAchievement:
	.string "성적을 리포트에 작성하므로\n"
	.string "기다려 주십시오!$"
	@ せいせきを レポ-トに かきますのでｎ
	@ おまちくだされ!

@ Unused
BattleFrontier_BattleArenaLobby_Text_PresentYouWithPrize:
	.string "7명을 돌파하기를 달성하였으므로\n"
	.string "이 상품을 드리겠습니다!$"
	@ 7にんぬきを たっせい されましたのでｎ
	@ この しょうひんを おうけとり くだされ!

@ Unused
BattleFrontier_BattleArenaLobby_Text_ReceivedPrize:
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "{STR_VAR_1}{K_EULREUL} 받았다!$"
	@ {PLAYER}はｎ
	@ {STR_VAR_1}を もらった!

@ Unused
BattleFrontier_BattleArenaLobby_Text_BagFullReturnForPrize:
	.string "..오옷!\n"
	.string "도구가 가득하시군요!\p"
	.string "도구를 정리하고 나서\n"
	.string "다시 와주십시오!$"
	@ ……おおっ!ｎ
	@ どうぐが いっぱいの ようですな!ｐ
	@ どうぐを せいりしてからｎ
	@ また おこしくだされ!

BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave:
	.string "수고하셨습니다!\p"
	.string "성적을 리포트에 작성하므로\n"
	.string "기다려 주십시오$"
	@ おつかれさまでした!ｐ
	@ せいせきを レポ-トに かきますのでｎ
	@ おまちくだされ!

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2:
	.string "다음에 도전해 주세요\n"
	.string "기다리고 있겠습니다!$"
	@ またの ちょうせんをｎ
	@ おまちして おりますぞ!

BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame:
	.string "기다리고 있었습니다!\p"
	.string "배틀아레나에 입장하기 전에\n"
	.string "리포트를 작성하고 있으므로\l"
	.string "잠시 기다려 주십시오!$"
	@ おまちしておりました!ｐ
	@ バトルアリ-ナに おつれする まえにｎ
	@ レポ-トを かきますので おまちくだされ!

BattleFrontier_BattleArenaLobby_Text_RecordLastMatch:
	.string "배틀아레나에서\n"
	.string "마지막으로 한 배틀을\l"
	.string "프런티어패스에 기록하겠습니까?$"
	@ バトルアリ-ナでｎ
	@ さいごに おこなった たたかいをｌ
	@ フロンティアパスに きろく されますかな?

BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack:
	.string "판정에서 져버렸어...\p"
	.string "방어하기만 해서\n"
	.string "공격하지 못한 게 좋지 않았나 봐...$"
	@ はんていで まけちゃった……ｐ
	@ まもる ばっかりでｎ
	@ せめなかったのが よくなかった みたい……

BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked:
	.string "판정에서 이겼어!\p"
	.string "상대 포켓몬에게\n"
	.string "기술을 확실하게 맞춰서 다행이야!$"
	@ はんていで かったぜ!ｐ
	@ あいての ポケモンにｎ
	@ わざを かくじつに あてたのが よかったぜ!

BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw:
	.string "판정으로 무승부가 났어\p"
	.string "시간이 다 되었을 때\n"
	.string "상대 포켓몬과 남은 HP가\l"
	.string "같았기 때문이지...$"
	@ はんていで ひきわけ だったよｐ
	@ じかんぎれに なったときにｎ
	@ あいて ポケモンと のこりの HPがｌ
	@ おなじ くらい だったからねぇ……

BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant:
	.string "배틀아레나에서는 포켓몬의 순서가\n"
	.string "엄청 중요해!\p"
	.string "예를 들어 1번째 포켓몬의\n"
	.string "약점이 되는 타입에 대해\p"
	.string "효과가 굉장한 기술을 가지고 있는\n"
	.string "포켓몬을 2번째로 참가시킨다면\l"
	.string "좋은 팀이 될 거라고 생각해!$"
	@ バトルアリ-ナでは ポケモンの じゅんばんがｎ
	@ とっても だいじ なのよ!ｐ
	@ たとえば 1ばんめの ポケモンのｎ
	@ じゃくてん となる タイプに たいしてｐ
	@ こうかばつぐんの わざを もっているｎ
	@ ポケモンを 2ばんめに いれておけばｌ
	@ いいチ-ムに なると おもうわ!

BattleFrontier_BattleArenaLobby_Text_RulesAreListed:
	.string "연승팀배틀의\n"
	.string "규칙이 적혀 있다!$"
	@ かちぬきチ-ムバトルのｎ
	@ ル-ルが かかれている!

BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading:
	.string "어느 설명을 읽겠습니까?$"
	@ どの せつめいを よみますか?

BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules:
	.string "연승팀배틀은 보통의 배틀과\n"
	.string "다른 특별한 규칙이 있습니다\p"
	.string "먼저 1번째 배틀은\n"
	.string "3턴에 끝나게 됩니다\p"
	.string "3턴에 승부가 나지 않을 때는\n"
	.string "심판에 의한 판정이 납니다\p"
	.string "판정은 포켓몬의 배틀 방식을\n"
	.string "보고 승패를 결정합니다\p"
	.string "또 승부가 날 때까지\n"
	.string "포켓몬을 교체할 수 없습니다$"
	@ かちぬきチ-ムバトルは ふつうの たたかいとｎ
	@ ちがい とくべつな ル-ルが ありますｐ
	@ まず 1かいの たたかいはｎ
	@ 3タ-ンで しゅうりょうと なりますｐ
	@ 3タ-ンで しょうぶが つかないときはｎ
	@ しんぱんに よる はんていに なりますｐ
	@ はんていは ポケモンの たたかいかたをｎ
	@ みて しょうはいを けってい しますｐ
	@ また しょうぶの けっちゃくが つくまでｎ
	@ ポケモンの こうたいは できません

BattleFrontier_BattleArenaLobby_Text_ExplainMindRules:
	.string "1번째 판정 포인트인\n"
	.string "“마음”은\l"
	.string "공격한 정도를 봅니다\p"
	.string "얼마나 트레이너가 공격하는 기술로\n"
	.string "명령을 따랐는지에 따라\l"
	.string "평가가 바뀝니다$"
	@ 1つめの はんてい ポイントであるｎ
	@ 「こころ」はｌ
	@ せめる きもちを みられますｐ
	@ どれだけ トレ-ナ-が こうげきする わざをｎ
	@ めいれい したかに よってｌ
	@ ひょうかが かわります

BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules:
	.string "2번째 판정 포인트인\n"
	.string "“기술”은 포켓몬의 기술이\l"
	.string "잘 통했는지를 봅니다\p"
	.string "기술이 성공하면\n"
	.string "평가가 올라갑니다\p"
	.string "기술이 실패하면\n"
	.string "평가가 떨어집니다\p"
	.string "게다가 상대에게 기술을 맞혔을 때\n"
	.string "“효과가 굉장하면” 올라가고\l"
	.string "“효과가 별로면” 내려갑니다\p"
	.string "또 “방어”나 “판별”은\n"
	.string "써도 평가가 오르지 않습니다\p"
	.string "상대의 “방어”나 “판별”로\n"
	.string "기술을 쓰지 못해도\l"
	.string "평가는 내려가지 않습니다$"
	@ 2つめの はんてい ポイントであるｎ
	@ 「わざ」は ポケモンの わざがｌ
	@ うまく できたかを みられますｐ
	@ わざが せいこう するとｎ
	@ ひょうかは あがりますｐ
	@ わざが しっぱい するとｎ
	@ ひょうかは さがりますｐ
	@ さらに あいてに わざを あてたときはｎ
	@ 「こうかはばつぐん」で あがりｌ
	@ 「こうかはいまひとつ」などで さがりますｐ
	@ また 「まもる」や 「みきり」はｎ
	@ だしても ひょうかは あがりませんｐ
	@ あいての 「まもる」や 「みきり」でｎ
	@ わざを だせなくてもｌ
	@ ひょうかは さがりません

BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules:
	.string "3번째 판정 포인트인\n"
	.string "“몸”은 대전 이후의\l"
	.string "포켓몬의 HP를 봅니다\p"
	.string "대전이 시작하기 전의\n"
	.string "HP와 비교해\l"
	.string "대전 후의 HP가 얼마나 남았는가로\l"
	.string "평가가 바뀝니다$"
	@ 3つめの はんてい ポイントであるｎ
	@ 「からだ」は たいせん したあとのｌ
	@ ポケモンの HPを みられますｐ
	@ たいせんが はじまる まえのｎ
	@ HPと くらべてｌ
	@ たいせんごの HPが どれだけ あるかでｌ
	@ ひょうかが かわります

BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon:
	.string "아레나캡틴에게 승리!\n"
	.string "그리고 7명을 돌파하셨군요!\l"
	.string "정말 훌륭했습니다!$"
	@ アリ-ナキャプテンからの きんぼし!ｎ
	@ ならびに 7にんぬき たっせい!ｌ
	@ まこと みごとで ございました!

BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints:
	.string "손님의 불굴의 투지를 기리며\n"
	.string "배틀포인트를 드리겠습니다!$"
	@ おきゃくじんの ふくつの とうしを たたえｎ
	@ バトルポイントを さしあげましょう!
