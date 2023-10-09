.set LOCALID_HINT_GIVER, 2

BattleFrontier_BattlePikeThreePathRoom_MapScripts:: @ 825C843
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattlePikeRoom_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePikeThreePathRoom_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePikeThreePathRoom_OnWarp
	.byte 0

BattleFrontier_BattlePikeThreePathRoom_OnFrame: @ 825C853
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattlePikeThreePathRoom_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpToLobby
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePikeThreePathRoom_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_5, 0, BattleFrontier_BattlePikeThreePathRoom_EventScript_SetHintRoom
	map_script_2 VAR_TEMP_5, 1, BattleFrontier_BattlePikeThreePathRoom_EventScript_GivePikeQueenHint
	.2byte 0

BattleFrontier_BattlePikeThreePathRoom_OnWarp: @ 825C87D
	map_script_2 VAR_TEMP_4, 0, BattleFrontier_BattlePikeThreePathRoom_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePikeThreePathRoom_EventScript_TurnPlayerNorth:: @ 825C887
	setvar VAR_TEMP_4, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_GetChallengeStatus:: @ 825C891
	frontier_getstatus
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpToLobby:: @ 825C89A
	warp MAP_BATTLE_FRONTIER_BATTLE_PIKE_LOBBY, 255, 5, 6
	waitstate
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_ResumeChallenge:: @ 825C8A4
	lockall
	message BattleFrontier_BattlePikeThreePathRoom_Text_AwaitingReturnSaveBeforeResume
	waitmessage
	pike_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_0, 255
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_PleaseEnjoyChallenge, MSGBOX_DEFAULT
	closemessage
	releaseall
	frontier_settrainers
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 99
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_Attendant:: @ 825C908
	frontier_get FRONTIER_DATA_BATTLE_NUM  @ Room number
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom1
	case 3, BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom3
	case 5, BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom5
	case 7, BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom7
	case 9, BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom9
	case 11, BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom11
	case 13, BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom13
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom1:: @ 825C968
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom1, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_AskContinueChallenge
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom3:: @ 825C978
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom3, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_AskContinueChallenge
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom5:: @ 825C988
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom5, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_AskContinueChallenge
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom7:: @ 825C998
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom7, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_AskContinueChallenge
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom9:: @ 825C9A8
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom9, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_AskContinueChallenge
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom11:: @ 825C9B8
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom11, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_AskContinueChallenge
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_AttendantRoom13:: @ 825C9C8
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom13, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_AskContinueChallenge
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_AskContinueChallenge:: @ 825C9D8
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_ContinueWithChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePikeThreePathRoom_EventScript_AskSaveChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeThreePathRoom_EventScript_AskSaveChallenge
	release
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_PauseChallenge:: @ 825C9FD
	frontier_saveparty
	message BattleFrontier_BattlePikeThreePathRoom_Text_SavingYourData
	waitmessage
	special LoadPlayerParty
	pike_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_AskSaveChallenge:: @ 825CA2A
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_SaveChallengeAndQuit, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, BattleFrontier_BattlePikeThreePathRoom_EventScript_PauseChallenge
	case NO, BattleFrontier_BattlePikeThreePathRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeThreePathRoom_EventScript_AskRetireChallenge
	release
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_AskRetireChallenge:: @ 825CA5A
	message BattleFrontier_BattlePikeThreePathRoom_Text_RetireFromChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePike_EventScript_Retire
	release
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_SetHintRoom:: @ 825CA78
	pike_sethintroom
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattlePikeThreePathRoom_EventScript_SetPikeQueenHint
	setvar VAR_TEMP_5, 255
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_SetPikeQueenHint:: @ 825CA91
	setvar VAR_TEMP_5, 1
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_GivePikeQueenHint:: @ 825CA97
	applymovement LOCALID_HINT_GIVER, BattleFrontier_BattlePikeThreePathRoom_Movement_HintGiverApproachPlayer
	waitmovement 0
	lockall
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_TerrifyingEvent, MSGBOX_DEFAULT
	releaseall
	applymovement LOCALID_HINT_GIVER, BattleFrontier_BattlePikeThreePathRoom_Movement_HintGiverReturnToPos
	waitmovement 0
	setvar VAR_TEMP_5, 255
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_HintGiver:: @ 825CABB
	pike_gethint
	compare VAR_RESULT, PIKE_HINT_BRAIN
	goto_if_eq BattleFrontier_BattlePikeThreePathRoom_EventScript_GiveBrainHint
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_FindingItDifficultToChoose, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, BattleFrontier_BattlePikeThreePathRoom_EventScript_AcceptHint
	case NO, BattleFrontier_BattlePikeThreePathRoom_EventScript_DeclineHint
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeThreePathRoom_EventScript_DeclineHint
	release
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_DeclineHint:: @ 825CB00
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_ApologizeForImpertinence, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_AcceptHint:: @ 825CB0A
	pike_gethintroomid
	switch VAR_RESULT
	case PIKE_ROOM_LEFT, BattleFrontier_BattlePikeThreePathRoom_EventScript_GiveLeftRoomHint
	case PIKE_ROOM_CENTER, BattleFrontier_BattlePikeThreePathRoom_EventScript_GiveCenterRoomHint
	case PIKE_ROOM_RIGHT, BattleFrontier_BattlePikeThreePathRoom_EventScript_GiveRightRoomHint
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_GiveLeftRoomHint:: @ 825CB39
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_SomethingAboutLeftPath, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_GiveHint

BattleFrontier_BattlePikeThreePathRoom_EventScript_GiveCenterRoomHint:: @ 825CB46
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_SomethingAboutCenterPath, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_GiveHint

BattleFrontier_BattlePikeThreePathRoom_EventScript_GiveRightRoomHint:: @ 825CB53
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_SomethingAboutRightPath, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_GiveHint

BattleFrontier_BattlePikeThreePathRoom_EventScript_GiveHint:: @ 825CB60
	pike_gethint
	switch VAR_RESULT
	case PIKE_HINT_NOSTALGIA, BattleFrontier_BattlePikeThreePathRoom_EventScript_HintNostalgia
	case PIKE_HINT_WHISPERING, BattleFrontier_BattlePikeThreePathRoom_EventScript_HintWhispering
	case PIKE_HINT_POKEMON, BattleFrontier_BattlePikeThreePathRoom_EventScript_HintPokemon
	case PIKE_HINT_PEOPLE, BattleFrontier_BattlePikeThreePathRoom_EventScript_HintPeople
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_HintNostalgia:: @ 825CB9A
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_WaveOfNostaliga, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_HintWhispering:: @ 825CBA4
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_HeardWhispering, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_HintPokemon:: @ 825CBAE
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_AromaOfPokemon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_HintPeople:: @ 825CBB8
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_PresenceOfPeople, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_GiveBrainHint:: @ 825CBC2
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_DreadfulPresence, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattlePikeThreePathRoom_Movement_HintGiverApproachPlayer: @ 825CBCE
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

BattleFrontier_BattlePikeThreePathRoom_Movement_HintGiverReturnToPos: @ 825CBD5
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	face_down
	step_end

BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom1: @ 825CBDD
	.string "현재 손님은\n"
	.string "1번째 방에 계십니다...$"
	// げんざい おきゃくさまはｎ
	// 1へやめに いらっしゃいます……

BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom3: @ 825CC00
	.string "현재 손님은\n"
	.string "3번째 방에 계십니다...$"
	// げんざい おきゃくさまはｎ
	// 3へやめに いらっしゃいます……

BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom5: @ 825CC23
	.string "현재 손님은\n"
	.string "5번째 방에 계십니다...$"
	// げんざい おきゃくさまはｎ
	// 5へやめに いらっしゃいます……

BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom7: @ 825CC46
	.string "현재 손님은\n"
	.string "7번째 방에 계십니다...$"
	// げんざい おきゃくさまはｎ
	// 7へやめに いらっしゃいます……

BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom9: @ 825CC69
	.string "현재 손님은\n"
	.string "9번째 방에 계십니다...$"
	// げんざい おきゃくさまはｎ
	// 9へやめに いらっしゃいます……

BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom11: @ 825CC8C
	.string "현재 손님은\n"
	.string "11번째 방에 계십니다...$"
	// げんざい おきゃくさまはｎ
	// 11へやめに いらっしゃいます……

BattleFrontier_BattlePikeThreePathRoom_Text_CurrentlyInRoom13: @ 825CCB0
	.string "현재 손님은\n"
	.string "13번째 방에 계십니다...$"
	// げんざい おきゃくさまはｎ
	// 13へやめに いらっしゃいます……

BattleFrontier_BattlePikeThreePathRoom_Text_ContinueWithChallenge: @ 825CCD4
	.string "이대로 도전을 계속하겠습니까?$"
	// このまま ちょうせんを つづけられますか?

BattleFrontier_BattlePikeThreePathRoom_Text_SaveChallengeAndQuit: @ 825CCFB
	.string "리포트를 작성하고\n"
	.string "종료하겠습니까...?$"
	// レポ-トを かいてｎ
	// しゅうりょう なさいますか……?

BattleFrontier_BattlePikeThreePathRoom_Text_RetireFromChallenge: @ 825CD3C
	.string "배틀게임의 도전을\n"
	.string "중단하겠습니까...?$"
	// バトルゲ-ムの ちょうせんをｎ
	// ちゅうし なさいますか……?

BattleFrontier_BattlePikeThreePathRoom_Text_AwaitingReturnSaveBeforeResume: @ 825CD75
	.string "기다리고 있었습니다...\p"
	.string "배틀게임을 개최하기 전에\n"
	.string "리포트를 작성합시다...$"
	// おまちして おりました……ｐ
	// バトルゲ-ムを さいかいする まえにｎ
	// レポ-トを かきましょう……

BattleFrontier_BattlePikeThreePathRoom_Text_PleaseEnjoyChallenge: @ 825CDDA
	.string "그럼 계속해서\n"
	.string "게임을 즐겨 주십시오...$"
	// それでは ひきつづきｎ
	// ゲ-ムを おたのしみ ください……

BattleFrontier_BattlePikeThreePathRoom_Text_SavingYourData: @ 825CE08
	.string "리포트를 작성하고 있습니다...\n"
	.string "잠시 기다려 주십시오...$"
	// レポ-トを かいています……ｎ
	// しょうしょう おまち ください……

BattleFrontier_BattlePike_Text_PathBlockedNoTurningBack: @ 825CE36
	.string "길이 막혀 있다!\n"
	.string "돌아갈 수 없다...$"
	// みちが とざされている!ｎ
	// ひきかえすことは できない……

BattleFrontier_BattlePikeThreePathRoom_Text_FindingItDifficultToChoose: @ 825CE69
	.string "... 손님...\p"
	.string "실례지만 어느 길로 갈지\n"
	.string "고민하고 계신가요...?$"
	// …… おきゃくさま……ｐ
	// しつれいですが どのみちに すすむかｎ
	// まよって いらっしゃるの ですか……?

BattleFrontier_BattlePikeThreePathRoom_Text_ApologizeForImpertinence: @ 825CEBB
	.string "그렇습니까...\n"
	.string "실례했습니다...$"
	// さようで ございますか……ｎ
	// これは しつれいを しました……

BattleFrontier_BattlePikeThreePathRoom_Text_SomethingAboutRightPath: @ 825CEE3
	.string "그렇군요...\n"
	.string "... 저는 오른쪽 길에서...$"
	// そうですね……ｎ
	// …… わたくしは みぎがわの みちから……

BattleFrontier_BattlePikeThreePathRoom_Text_SomethingAboutCenterPath: @ 825CF23
	.string "그렇군요...\n"
	.string "... 저는 가운데 길에서...$"
	// そうですね……ｎ
	// …… わたくしは まんなかの みちから……

BattleFrontier_BattlePikeThreePathRoom_Text_SomethingAboutLeftPath: @ 825CF64
	.string "그렇군요...\n"
	.string "... 저는 왼쪽 길에서...$"
	// そうですね……ｎ
	// …… わたくしは ひだりがわの みちから……

BattleFrontier_BattlePikeThreePathRoom_Text_AromaOfPokemon: @ 825CFA3
	.string "포켓몬의 냄새가\n"
	.string "나는 듯한\l"
	.string "기분이 듭니다만...$"
	// ポケモンの においがｎ
	// ただよってくる ようなｌ
	// きが するの ですが……

BattleFrontier_BattlePikeThreePathRoom_Text_PresenceOfPeople: @ 825CFE5
	.string "트레이너... 인가요...?\n"
	.string "사람의 기척을 느꼈습니다만...$"
	// トレ-ナ-…… でしょうか……?ｎ
	// ひとの けはいを かんじるの ですが……

BattleFrontier_BattlePikeThreePathRoom_Text_HeardWhispering: @ 825D017
	.string "뭔가가 속삭이는 듯한 소리가\n"
	.string "들렸습니다만...$"
	// なにかが ささやく ような ものおとがｎ
	// きこえたの ですが……

BattleFrontier_BattlePikeThreePathRoom_Text_WaveOfNostaliga: @ 825D054
	.string "어째서인지 조금 그리운\n"
	.string "분위기를 느낍니다만...$"
	// なぜだか すこし だけ なつかしいｎ
	// ふんいきを かんじるの ですが……

BattleFrontier_BattlePikeThreePathRoom_Text_TerrifyingEvent: @ 825D094
	.string "손님...\p"
	.string "이 앞에서 매우\n"
	.string "무서운 일이 손님을\l"
	.string "기다리고 있을 겁니다...\p"
	.string "각오해 주세요...$"
	// おきゃくさま……ｐ
	// このさき たいへんにｎ
	// おそろしい できごとが おきゃくさまをｌ
	// まちうけている でしょう……ｐ
	// かくごして おいて ください……

BattleFrontier_BattlePikeThreePathRoom_Text_DreadfulPresence: @ 825D125
	.string "... 어느 길에서나\n"
	.string "무서운 기척이 느껴집니다...$"
	// …… どの みちの さきからもｎ
	// おそろしい けはいを かんじます……
