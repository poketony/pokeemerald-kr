.set LOCALID_ATTENDANT, 1

BattleFrontier_BattlePikeLobby_MapScripts:: @ 825B6C6
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePikeLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePikeLobby_OnWarp
	.byte 0

BattleFrontier_BattlePikeLobby_OnFrame: @ 825B6D1
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_WON, BattleFrontier_BattlePikeLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePikeLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattlePikeLobby_OnWarp: @ 825B6F3
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth:: @ 825B6FD
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus:: @ 825B707
	frontier_getstatus
	end

BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving:: @ 825B710
	special HealPlayerParty
	pike_resethelditems
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	pike_set PIKE_DATA_WIN_STREAK 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WonChallenge:: @ 825B762
	lockall
	frontier_isbrain
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen
	msgbox BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen:: @ 825B784
	msgbox BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints:: @ 825B78D
	msgbox BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	frontier_checkairshow
	pike_get PIKE_DATA_TOTAL_STREAKS
	addvar VAR_RESULT, 1
	pike_set PIKE_DATA_TOTAL_STREAKS, VAR_RESULT
	special LoadPlayerParty
	special HealPlayerParty
	pike_resethelditems
	message BattleFrontier_BattlePikeLobby_Text_ShallRecordResults
	waitmessage
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_LostChallenge:: @ 825B806
	lockall
	message BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults
	waitmessage
	frontier_checkairshow
	frontier_set FRONTIER_DATA_BATTLE_NUM, 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	special LoadPlayerParty
	special HealPlayerParty
	pike_resethelditems
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_Attendant:: @ 825B868
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PIKE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge:: @ 825B87F
	message BattleFrontier_BattlePikeLobby_Text_TakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge:: @ 825B8BB
	message BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, 0
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	frontier_checkineligible
	compare VAR_0x8004, TRUE
	goto_if_eq BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge:: @ 825B95C
	setvar VAR_TEMP_0, 0
	setvar VAR_TEMP_1, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	pike_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, TRUE
	pike_savehelditems
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_0, 255
	pike_savehelditems
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattlePikeLobby_EventScript_CancelChallengeSaveFailed
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePikeLobby_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	frontier_settrainers
	call BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor
	special HealPlayerParty
	call BattleFrontier_BattlePike_EventScript_CloseCurtain
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_CORRIDOR, 255, 6, 7
	setvar VAR_TEMP_0, 0
	waitstate
	end

BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge:: @ 825BA1A
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons:: @ 825BA27
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLv50:: @ 825BA42
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLvOpen:: @ 825BA4F
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_CancelChallengeSaveFailed:: @ 825BA5C
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge:: @ 825BA73
	special LoadPlayerParty
BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge:: @ 825BA76
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge:: @ 825BA7E
	release
	end

BattleFrontier_BattlePikeLobby_EventScript_ShowResults:: @ 825BA80
	lockall
	frontier_results FRONTIER_FACILITY_PIKE
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor:: @ 825BA94
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor
	waitmovement 0
	return

BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor: @ 825BAA6
	walk_up
BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor: @ 825BAA7
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePikeLobby_EventScript_Hiker:: @ 825BAAB
	msgbox BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Twin:: @ 825BAB4
	msgbox BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Beauty:: @ 825BABD
	msgbox BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesBoard:: @ 825BAC6
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard:: @ 825BAD5
	message BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 16, 4, MULTI_BATTLE_PIKE_RULES, 0
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag
	case 1, BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems
	case 2, BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder
	case 3, BattleFrontier_BattlePikeLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag:: @ 825BB1D
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems:: @ 825BB2B
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder:: @ 825BB39
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_ExitRules:: @ 825BB47
	releaseall
	end

BattleFrontier_BattlePike_EventScript_CloseCurtain:: @ 825BB49
	playse SE_PIKE_CURTAIN_CLOSE
	special CloseBattlePikeCurtain
	waitstate
	waitse
	return

BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike: @ 825BB52
	.string "트레이너의 운을 시험하는 장소...\n"
	.string "배틀튜브에 어서 오세요...\p"
	.string "배틀게임의 안내는\n"
	.string "이쪽에서 하고 있습니다...$"
	// トレ-ナ-の うんを ためす ばしょ……ｎ
	// バトルチュ-ブへ ようこそ……ｐ
	// バトルゲ-ムへの ごあんないはｎ
	// こちらで ございます……

BattleFrontier_BattlePikeLobby_Text_TakeChallenge: @ 825BBC1
	.string "배틀게임에\n"
	.string "도전하겠습니까...?$"
	// バトルゲ-ムにｎ
	// ちょうせん されますか……?

BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike: @ 825BBF5
	.string "이곳에서는 배틀게임이라고 하는\n"
	.string "행사를 개최하고 있습니다\p"
	.string "배틀게임의 규칙은 간단...\p"
	.string "3개의 길을 선택하면서\n"
	.string "배틀튜브의 가장 안쪽에 있는\l"
	.string "목표인 방을 향해\l"
	.string "나아가기만 하면 됩니다\p"
	.string "...단 선택한 길 앞에\n"
	.string "뭐가 일어날지는 손님의\l"
	.string "운에 달렸습니다...\p"
	.string "만약 목표에 도달하게 된다면\n"
	.string "배틀포인트를 드리겠습니다\p"
	.string "또한 게임의 도전을\n"
	.string "중단하고 싶을 경우에는\l"
	.string "큰 방에 있는 스태프에게\l"
	.string "말씀해 주세요...\p"
	.string "리포트를 작성하지 않으면\n"
	.string "게임을 재개할 수 없습니다\p"
	.string "아무쪼록 주의해 주십시오...$"
	// こちらでは バトルゲ-ムと いうｎ
	// もよおしを かいさいして おりますｐ
	// バトルゲ-ムの ル-ルは かんたん……ｐ
	// 3つの みちを えらびながらｎ
	// バトルチュ-ブの いちばん おくに あるｌ
	// ゴ-ルの へやを めざしてｌ
	// すすんで いく だけで よいのですｐ
	// …… ただし えらんだ みちの さきでｎ
	// なにが おこるかは おきゃくさまのｌ
	// うん しだい ですが……ｐ
	// もしも ゴ-ルに つくことが できたならｎ
	// バトルポイントを さしあげましょうｐ
	// なお ゲ-ムの ちょうせんをｎ
	// ちゅうだんしたい ばあいはｌ
	// おおべやに たいき している スタッフにｌ
	// おもうしつけ ください……ｐ
	// レポ-トを かかないとｎ
	// ゲ-ムの さいかいが できません……ｐ
	// くれぐれも ごちゅうい ください……

BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou: @ 825BE02
	.string "그럼 다음 기회를\n"
	.string "기다리고 있겠습니다...$"
	// では またの きかいをｎ
	// おまちして おります……

BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode: @ 825BE35
	.string "레벨 50과 오픈 레벨\n"
	.string "어느 쪽에 도전하겠습니까?$"
	// レベル50と オ-プンレベルの ゲ-ムｎ
	// どちらに ちょうせん しますか?

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50: @ 825BE8C
	.string "...손님\p"
	.string "배틀게임에 참가할 수 있는\n"
	.string "포켓몬 3마리가 없습니다...\p"
	.string "참가하려면 레벨 50 이하의\n"
	.string "종류가 다른 포켓몬을\l"
	.string "3마리 준비해 주십시오\p"
	.string "또한 지니게 할 도구도\n"
	.string "모두 다르게 해주십시오...\p"
	.string "그리고 알{STR_VAR_1}"
	.string "참가시킬 수 없습니다\p"
	.string "준비가 끝났다면\n"
	.string "다시 방문해 주십시오...$"
	// …… おきゃくさまｐ
	// バトルゲ-ムに さんかできるｎ
	// ポケモンが 3ひき おりません……ｐ
	// さんかには レベルが 50いかでｎ
	// すべて ちがう しゅるいの ポケモンをｌ
	// 3ひき ごようい くださいｐ
	// また もたせる どうぐも すべてｎ
	// ちがうもので なければ いけません……ｐ
	// なお タマゴいさんか させる ことは できませんｐ
	// じゅんびが ととのいましたらｎ
	// また おこしください……

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen: @ 825BF9A
	.string "...손님\p"
	.string "배틀게임에 참가할 수 있는\n"
	.string "포켓몬 3마리가 없습니다...\p"
	.string "참가하려면 종류가 다른\n"
	.string "포켓몬을 3마리 준비해 주십시오\p"
	.string "또한 지니게 할 도구도\n"
	.string "모두 다르게 해주십시오...\p"
	.string "그리고 알{STR_VAR_1}"
	.string "참가시킬 수 없습니다\p"
	.string "준비가 끝났다면\n"
	.string "다시 방문해 주십시오...$"
	// …… おきゃくさまｐ
	// バトルゲ-ムに さんかできるｎ
	// ポケモンが 3ひき おりません……ｐ
	// さんかには すべて ちがう しゅるいのｎ
	// ポケモンを 3ひき ごようい くださいｐ
	// また もたせる どうぐも すべてｎ
	// ちがうもので なければ いけません……ｐ
	// なお タマゴさんか させる ことは できませんｐ
	// じゅんびが ととのいましたらｎ
	// また おこしください……

BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons: @ 825C094
	.string "그럼 게임에 도전할\n"
	.string "포켓몬을 3마리 선택해 주십시오...$"
	// それでは ゲ-ムに ちょうせんするｎ
	// ポケモンを 3ひき おえらび ください……

BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge: @ 825C0D8
	.string "배틀게임을 시작하기 전에\n"
	.string "리포트를 작성합니다...\l"
	.string "괜찮겠습니까?$"
	// バトルゲ-ムを かいしする まえにｎ
	// レポ-トを かきます…… よろしいですか?

BattleFrontier_BattlePikeLobby_Text_StepThisWay: @ 825C130
	.string "그럼 이쪽으로 와주세요...$"
	// では こちらに どうぞ……

BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults: @ 825C146
	.string "게임 종료네요...\p"
	.string "성적을 리포트에 작성합시다...\n"
	.string "잠시 기다려 주십시오...$"
	// ゲ-ム しゅうりょう ですね……ｐ
	// せいせきを レポ-トに かきましょう……ｎ
	// しょうしょう おまちください……

BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance: @ 825C18A
	.string "게임 클리어네요...\p"
	.string "손님... 꽤 괜찮은 운을\n"
	.string "지니신 것 같군요...$"
	// ゲ-ム クリア ですね……ｐ
	// おきゃくさま…… なかなかの うんをｎ
	// おもちの ようですね……

BattleFrontier_BattlePikeLobby_Text_ShallRecordResults: @ 825C1DF
	.string "성적을 리포트에 작성합시다...\n"
	.string "잠시 기다려 주십시오...$"
	// せいせきを レポ-トに かきましょう……ｎ
	// しばらく おまちください……

@ Unused
BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints2: @ 825C209
	.string "게임 클리어를 기념하여\n"
	.string "배틀포인트를 증정합니다...\p"
	.string "부디 받아 주세요...$"
	// ゲ-ム クリアを きねんしてｎ
	// バトルポイントを しんてい します……ｐ
	// どうぞ おおさめ ください……

@ Unused
BattleFrontier_BattlePikeLobby_Text_ReachedBattlePointLimit: @ 825C26C
	.string "포인트가 가득하군요...\n"
	.string "포인트를 정리하고 나서\n"
	.string "다시 와 주세요...$"
	// ポイントが いっぱいの ようですね……ｐ
	// ポイントを せいりしてからｎ
	// また おこしください……

BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting: @ 825C2E0
	.string "...손님\p"
	.string "성적을 제대로 리포트에 작성하지\n"
	.string "않고 종료하셨군요...\p"
	.string "죄송하지만 도전은\n"
	.string "무효로 하도록 하겠습니다...$"
	// おきゃくさま……ｐ
	// ぜんかい きちんと レポ-トを かかずにｎ
	// しゅうりょう されましたね……ｐ
	// もうしわけ ありませんが ちょうせんはｎ
	// むこうと させて いただきます……

BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen: @ 825C383
	.string "... 축하드립니다...\n"
	.string "튜브퀸에게 승리하고\l"
	.string "게임을 클리어하셨군요...$"
	// …… おめでとう ございます……ｎ
	// チュ-ブクイ-ンに しょうりしｌ
	// ゲ-ムを クリア されましたね……

BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints: @ 825C3D9
	.string "손님의 강한 운을 기리며\n"
	.string "배틀포인트를 드리겠습니다...$"
	// おきゃくさまの つよき うんを たたえｎ
	// バトルポイントを さしあげます……

BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal: @ 825C422
	.string "으으-! 젠장-!!\n"
	.string "앞으로 목표까지 방 1개였는데-!\p"
	.string "너! 여기서는 독이나 얼음에\n"
	.string "조심하는 게 좋다고!$"
	// んん-! ちくしょ-!!ｎ
	// あと 1へやで ゴ-ルだったのによ-!ｐ
	// おまえ! ここでは どくや こおりにはｎ
	// ちゅうい したほうが いいぞ!

BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer: @ 825C4A5
	.string "나 10번은 클리어했는데\n"
	.string "한 번도 트레이너와\l"
	.string "대결한 적이 없어!$"
	// あたし 10かいは クリアしたけどｎ
	// いっかいも トレ-ナ-とｌ
	// たたかった こと ないんだよぅ!

BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere: @ 825C4FD
	.string "저기! 저기!\p"
	.string "여기라면 포켓몬의 특성이\n"
	.string "활약할 수 있을 것 같지 않아?$"
	// ねえ! ねえ!ｐ
	// ここって ポケモンの とくせいがｎ
	// かつやく すると おもわない?

@ Unused
BattleFrontier_BattlePikeLobby_Text_TrainersWhicheverPathIChoose: @ 825C558
	.string "뭐야 여기!! 전혀 모르겠어-!\p"
	.string "몇 번이고 도전해도\n"
	.string "어느 길을 골라도\l"
	.string "트레이너가 나와 버리잖아-!$"
	// なんだよ ここ! いみ わかんないよ-!ｐ
	// なんかい チャレンジ してもｎ
	// どの みち えらんでもｌ
	// トレ-ナ-しか でてこない じゃないか-!

BattleFrontier_BattlePikeLobby_Text_RulesAreListed: @ 825C5FB
	.string "배틀게임의 규칙이 적혀 있다!$"
	// バトルゲ-ムの ル-ルが かかれている!

BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading: @ 825C621
	.string "어느 설명을 읽겠습니까?$"
	// どの せつめいを よみますか?

BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules: @ 825C644
	.string "배틀게임을 하는 동안에는\n"
	.string "가방과 포켓내비를\l"
	.string "사용할 수 없습니다$"
	// バトルゲ-ムの あいだはｎ
	// バッグと ポケナビの しようはｌ
	// きんし されています

BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules: @ 825C68A
	.string "배틀게임에서\n"
	.string "포켓몬이 지닌 나무열매나 허브는\l"
	.string "한 번만 사용할 수 있습니다$"
	// バトルゲ-ムではｎ
	// ポケモンに もたせた きのみや ハ-ブはｌ
	// いちどしか こうかを はっき しません

BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules: @ 825C6EB
	.string "배틀게임을 하는 동안에는\n"
	.string "도전할 때 정했던\l"
	.string "포켓몬의 순서를\l"
	.string "바꿀 수 없습니다$"
	// バトルゲ-ムの あいだはｎ
	// ちょうせんする ときに きめたｌ
	// ポケモンの じゅんばんをｌ
	// いれかえる ことは できません

