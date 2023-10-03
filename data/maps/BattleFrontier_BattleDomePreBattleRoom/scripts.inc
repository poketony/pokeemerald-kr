.set LOCALID_ATTENDANT, 1

BattleFrontier_BattleDomePreBattleRoom_MapScripts:: @ 824B1F9
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleDomePreBattleRoom_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleDomePreBattleRoom_OnWarp
	.byte 0

BattleFrontier_BattleDomePreBattleRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleDomePreBattleRoom_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleDomePreBattleRoom_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleDomePreBattleRoom_OnFrame:
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattleDomePreBattleRoom_EventScript_EnterRoom
	.2byte 0

BattleFrontier_BattleDomePreBattleRoom_EventScript_EnterRoom::
	compare VAR_0x8006, 1
	goto_if_eq BattleFrontier_BattleDomePreBattleRoom_EventScript_ReturnFromBattle
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	setvar VAR_TEMP_0, 1
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleDomePreBattleRoom_Movement_PlayerEnter
	waitmovement 0
	lockall
BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound::
	call BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForNextRoundMessage
	waitmessage
	switch VAR_RESULT 
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRoundNoRecord
	multichoice 16, 0, MULTI_TOURNEY_WITH_RECORD, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleDomePreBattleRoom_EventScript_ShowOpponentInfo
	case 1, BattleFrontier_BattleDomePreBattleRoom_EventScript_ShowTourneyTree
	case 2, BattleFrontier_BattleDomePreBattleRoom_EventScript_ContinueChallenge
	case 3, BattleFrontier_BattleDomePreBattleRoom_EventScript_AskRecordBattle
	case 4, BattleFrontier_BattleDomePreBattleRoom_EventScript_AskPauseChallenge
	case 5, BattleFrontier_BattleDomePreBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound

BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRoundNoRecord::
	multichoice 16, 2, MULTI_TOURNEY_NO_RECORD, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleDomePreBattleRoom_EventScript_ShowOpponentInfo
	case 1, BattleFrontier_BattleDomePreBattleRoom_EventScript_ShowTourneyTree
	case 2, BattleFrontier_BattleDomePreBattleRoom_EventScript_ContinueChallenge
	case 3, BattleFrontier_BattleDomePreBattleRoom_EventScript_AskPauseChallenge
	case 4, BattleFrontier_BattleDomePreBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound

BattleFrontier_BattleDomePreBattleRoom_EventScript_AskRecordBattle::
	message BattleFrontier_BattleDomePreBattleRoom_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound
	case 0, BattleFrontier_BattleDomePreBattleRoom_EventScript_RecordBattle
	case MULTI_B_PRESSED, BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound

BattleFrontier_BattleDomePreBattleRoom_EventScript_RecordBattle::
	call BattleFrontier_EventScript_SaveBattle
	goto BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound

BattleFrontier_BattleDomePreBattleRoom_EventScript_AskPauseChallenge::
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_SaveAndQuitGame, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound
	case YES, BattleFrontier_BattleDomePreBattleRoom_EventScript_PauseChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound

BattleFrontier_BattleDomePreBattleRoom_EventScript_AskRetireChallenge::
	message BattleFrontier_BattleDomePreBattleRoom_Text_RetireYourChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound
	case 0, BattleFrontier_BattleDomePreBattleRoom_EventScript_RetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound

BattleFrontier_BattleDomePreBattleRoom_EventScript_RetireChallenge::
	dome_resolvewinners DOME_PLAYER_RETIRED
	goto BattleFrontier_BattleDomeBattleRoom_EventScript_WarpToLobbyLost

BattleFrontier_BattleDomePreBattleRoom_EventScript_PauseChallenge::
	message BattleFrontier_BattleDomePreBattleRoom_Text_SavingDataPleaseWait
	waitmessage
	dome_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

BattleFrontier_BattleDomePreBattleRoom_EventScript_ShowOpponentInfo::
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_PlayersNextOpponentIsTrainer, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	dome_showopponentinfo
	waitstate
	goto BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound

BattleFrontier_BattleDomePreBattleRoom_EventScript_ShowTourneyTree::
	call BattleFrontier_BattleDomePreBattleRoom_EventScript_ShowRoundMessage
	fadescreen FADE_TO_BLACK
	dome_showtourneytree
	waitstate
	goto BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound

BattleFrontier_BattleDomePreBattleRoom_EventScript_ShowRoundMessage::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	switch VAR_RESULT
	case DOME_ROUND1, BattleFrontier_BattleDomePreBattleRoom_EventScript_TourneyInRound1
	case DOME_ROUND2, BattleFrontier_BattleDomePreBattleRoom_EventScript_TourneyInRound2
	case DOME_SEMIFINAL, BattleFrontier_BattleDomePreBattleRoom_EventScript_TourneyInSemifinals
	case DOME_FINAL, BattleFrontier_BattleDomePreBattleRoom_EventScript_TourneyInFinals
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_TourneyInRound1::
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_TourneyInRound1, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_TourneyInRound2::
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_TourneyInRound2, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_TourneyInSemifinals::
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_TourneyInSemifinals, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_TourneyInFinals::
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_TourneyInFinals, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_ContinueChallenge::
	message BattleFrontier_BattleDomePreBattleRoom_Text_ChooseTwoMons
	waitmessage
	waitbuttonpress
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, DOME_BATTLE_PARTY_SIZE 
	special ChoosePartyForBattleFrontier
	waitstate
	frontier_resetsketch
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound
	dome_set DOME_DATA_SELECTED_MONS
	dome_reduceparty
	dome_setopponent
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_RightThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleDomePreBattleRoom_Movement_AttendantMoveAside
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleDomePreBattleRoom_Movement_PlayerWalkToDoor
	waitmovement 0
	opendoor 5, 1
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleDomePreBattleRoom_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 5, 1
	waitdooranim
	warp MAP_BATTLE_FRONTIER_BATTLE_DOME_BATTLE_ROOM, 255, 9, 5
	setvar VAR_TEMP_0, 0
	waitstate
	end

BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForNextRoundMessage::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	switch VAR_RESULT
	case DOME_ROUND1, BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForRound1
	case DOME_ROUND2, BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForRound2
	case DOME_SEMIFINAL, BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForSemifinals
	case DOME_FINAL, BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForFinals
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForRound1::
	message BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForRound1
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForRound2::
	message BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForRound2
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForSemifinals::
	message BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForSemifinals
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForFinals::
	frontier_getbrainstatus
	switch VAR_RESULT
	case FRONTIER_BRAIN_SILVER, BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForTuckerSilver
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForTuckerGold
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForTuckerSilver
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForTuckerGold
	message BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForFinals
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForTuckerSilver::
	goto_if_set FLAG_TEMP_1, BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForTuckerSilverShort
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForTuckerSilver, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForTuckerGold::
	goto_if_set FLAG_TEMP_1, BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForTuckerGoldShort
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForTuckerGold, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForTuckerSilverShort::
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForTuckerSilverShort, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_ReadyForTuckerGoldShort::
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForTuckerGoldShort, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_ReturnFromBattle::
	setvar VAR_TEMP_0, 1
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_RestoreMonsToFullHealth, MSGBOX_DEFAULT
	special LoadPlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	call BattleFrontier_BattleDomePreBattleRoom_EventScript_RoundCompleteMessage
	fadescreen FADE_TO_BLACK
	dome_showstatictourneytree
	waitstate
	goto BattleFrontier_BattleDomePreBattleRoom_EventScript_AskReadyForNextRound

BattleFrontier_BattleDomePreBattleRoom_EventScript_RoundCompleteMessage::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	switch VAR_RESULT
	case DOME_ROUND2, BattleFrontier_BattleDomePreBattleRoom_EventScript_Round1Complete
	case DOME_SEMIFINAL, BattleFrontier_BattleDomePreBattleRoom_EventScript_Round2Complete
	case DOME_FINAL, BattleFrontier_BattleDomePreBattleRoom_EventScript_SemifinalsComplete
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_Round1Complete::
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_Round1Complete, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_Round2Complete::
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_Round2Complete, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomePreBattleRoom_EventScript_SemifinalsComplete::
	msgbox BattleFrontier_BattleDomePreBattleRoom_Text_SemifinalsComplete, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomePreBattleRoom_Movement_AttendantMoveAside:
	walk_right
	face_left
	step_end

BattleFrontier_BattleDomePreBattleRoom_Movement_PlayerEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleDomePreBattleRoom_Movement_PlayerWalkToDoor:
	walk_up
	step_end

BattleFrontier_BattleDomePreBattleRoom_Movement_PlayerEnterDoor:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForRound1:
	.string "곧 1차전이 시작됩니다\n"
	.string "준비는 다 되셨습니까?$"

BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForRound2:
	.string "곧 2차전이 시작됩니다\n"
	.string "준비는 다 되셨습니까?$"

BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForSemifinals:
	.string "곧 준결승이 시작됩니다\n"
	.string "준비는 다 되셨습니까?$"

BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForFinals:
	.string "곧 결승전이 시작됩니다\n"
	.string "준비는 다 되셨습니까?$"

BattleFrontier_BattleDomePreBattleRoom_Text_ChooseTwoMons:
	.string "그럼 시합에 내보낼\n"
	.string "포켓몬 2마리를 선택해 주십시오$"
	// それでは しあいに だすｎ
	// ポケモンを 2ひき えらんでください

BattleFrontier_BattleDomePreBattleRoom_Text_RightThisWay:
	.string "그럼 이쪽으로 오십시오!$"
	// では こちらから どうぞ!

BattleFrontier_BattleDomePreBattleRoom_Text_RestoreMonsToFullHealth:
	.string "수고하셨습니다!\p"
	.string "포켓몬의 체력을\n"
	.string "회복시켜 드리겠습니다$"
	// おつかれさまでした!ｐ
	// ポケモンの たいりょくをｎ
	// かいふく いたします!

BattleFrontier_BattleDomePreBattleRoom_Text_Round1Complete:
	.string "이걸로 1차전은\n"
	.string "모두 종료되었습니다!\p"
	.string "승리한 팀들을 봐주십시오!$"
	// これで 1かいせんがｎ
	// すべて しゅうりょう しました!ｐ
	// かちあがりを ごらん ください!

BattleFrontier_BattleDomePreBattleRoom_Text_Round2Complete:
	.string "이걸로 2차전은\n"
	.string "모두 종료되었습니다!\p"
	.string "승리한 팀들을 봐주십시오!$"
	// これで 1かいせんがｎ
	// すべて しゅうりょう しました!ｐ
	// かちあがりを ごらん ください!

BattleFrontier_BattleDomePreBattleRoom_Text_SemifinalsComplete:
	.string "이걸로 준결승은\n"
	.string "모두 종료되었습니다!\p"
	.string "승리한 팀들을 봐주십시오!$"
	// これで じゅんけっしょうがｎ
	// すべて しゅうりょう しました!ｐ
	// かちあがりを ごらん ください!

BattleFrontier_BattleDomePreBattleRoom_Text_CongratsReadyForRound2:
	.string "1차전 돌파\n"
	.string "축하합니다!\p"
	.string "다음은 2차전입니다\n"
	.string "준비는 다 되셨습니까?$"
	// 1かいせん とっぱｎ
	// おめでとう ございます!ｐ
	// つぎは 2かいせん ですｎ
	// じゅんびの ほうは いかがですか?

BattleFrontier_BattleDomePreBattleRoom_Text_CongratsReadyForSemifinals:
	.string "준결승 진출\n"
	.string "축하합니다\p"
	.string "자 베스트 4의 격돌입니다\n"
	.string "준비는 다 되셨습니까?$"
	// じゅんけっしょう しんしゅつｎ
	// おめでとう ございますｐ
	// さあ ベスト4の げきとつですｎ
	// じゅんびの ほうは いかがですか?

BattleFrontier_BattleDomePreBattleRoom_Text_CongratsReadyForFinals:
	.string "결승 진출\n"
	.string "축하합니다\p"
	.string "우승까지 앞으로 1승입니다\n"
	.string "준비는 다 되셨습니까?$"
	// けっしょう しんしゅつｎ
	// おめでとう ございますｐ
	// ゆうしょうまで あと 1しょう ですねｎ
	// じゅんびの ほうは いかがですか?

BattleFrontier_BattleDomePreBattleRoom_Text_PlayersNextOpponentIsTrainer:
	.string "{PLAYER}님의\n"
	.string "다음 상대는 이분입니다$"

BattleFrontier_BattleDomePreBattleRoom_Text_TourneyInRound1:
	.string "현재 토너먼트는\n"
	.string "1차전입니다!$"
	// げんざい ト-ナメントはｎ
	// 1かいせん です!

BattleFrontier_BattleDomePreBattleRoom_Text_TourneyInRound2:
	.string "현재 토너먼트는\n"
	.string "2차전입니다!$"
	// げんざい ト-ナメントはｎ
	// 2かいせん です!

BattleFrontier_BattleDomePreBattleRoom_Text_TourneyInSemifinals:
	.string "현재 토너먼트는\n"
	.string "준결승입니다!$"
	// げんざい ト-ナメントはｎ
	// じゅんけっしょう です!

BattleFrontier_BattleDomePreBattleRoom_Text_TourneyInFinals:
	.string "현재 토너먼트는\n"
	.string "결승전입니다!$"
	// げんざい ト-ナメントはｎ
	// けっしょうせん です!

BattleFrontier_BattleDomePreBattleRoom_Text_SaveAndQuitGame:
	.string "리포트를 기록하고 종료하겠습니까?$"
	// レポ-トを かいて しゅうりょう しますか?

BattleFrontier_BattleDomePreBattleRoom_Text_RetireYourChallenge:
	.string "배틀토너먼트의 도전을\n"
	.string "중단하겠습니까?$"
	// バトルト-ナメントの ちょうせんをｎ
	// ちゅうし しますか?

BattleFrontier_BattleDomePreBattleRoom_Text_SavingDataPleaseWait:
	.string "리포트를 기록하고 있습니다\n"
	.string "잠시 기다려 주십시오!$"
	// レポ-トを かいていますｎ
	// しばらく おまちくださいませ!

BattleFrontier_BattleDomePreBattleRoom_Text_RecordLastMatch:
	.string "방금 전의 배틀을\n"
	.string "프런티어패스에 기록하겠습니까?$"
	// さきほどの たたかいをｎ
	// フロンティアパスに きろく しますか?

BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForTuckerSilver:
	.string "결승 진출\n"
	.string "축하합니다\p"
	.string "다음은 돔슈퍼스타 하인즈님과\n"
	.string "대결하는 결승전입니다!\p"
	.string "준비는 다 되셨습니까?$"
	// けっしょう しんしゅつｎ
	// おめでとう ございますｐ
	// つぎは ド-ムス-パ-スタ- ヒ-スさまにｎ
	// いどむ けっしょうせん です!ｐ
	// じゅんびの ほうは いかがですか?

BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForTuckerGold:
	.string "결승 진출\n"
	.string "축하합니다\p"
	.string "다음은 돔슈퍼스타 하인즈님과\n"
	.string "대결하는 결승전입니다!\p"
	.string "준비는 다 되셨습니까?$"
	// けっしょう しんしゅつｎ
	// おめでとう ございますｐ
	// つぎは ド-ムス-パ-スタ- ヒ-スさまにｎ
	// いどむ けっしょうせん です!ｐ
	// じゅんびの ほうは いかがですか?

BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForTuckerSilverShort:
	.string "자 하인즈님과의 결승전입니다!\n"
	.string "준비는 다 되셨습니까?$"
	// さあ ヒ-スさまとの けっしょうせん です!ｎ
	// じゅんびの ほうは いかがですか?$

BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForTuckerGoldShort:
	.string "자 하인즈님과의 결승전입니다!\n"
	.string "준비는 다 되셨습니까?$"
	// さあ ヒ-スさまとの けっしょうせん です!ｎ
	// じゅんびの ほうは いかがですか?$
