BattleFrontier_Lounge3_MapScripts:: @ 8261D82
	.byte 0

	.set BET_AMOUNT_5,  5
	.set BET_AMOUNT_10, 10
	.set BET_AMOUNT_15, 15

BattleFrontier_Lounge3_EventScript_Gambler:: @ 8261D83
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_GAMBLER, BattleFrontier_Lounge3_EventScript_AlreadyMetGambler
	call BattleFrontier_Lounge3_EventScript_CountSilverSymbols
	compare VAR_0x8004, 2
	goto_if_le BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols
	setflag FLAG_MET_BATTLE_FRONTIER_GAMBLER
	msgbox BattleFrontier_Lounge3_Text_YouLookToughExplainGambling, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_AskToEnterChallenge:: @ 8261DAF
	special ShowFrontierGamblerLookingMessage
	waitmessage
	waitbuttonpress
	msgbox BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge3_EventScript_DeclineChallenge
	msgbox BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge3_EventScript_DeclineChallenge
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	special ShowBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_ChooseBetAmount:: @ 8261DE9
	multichoice 20, 4, MULTI_FRONTIER_GAMBLER_BET, 0
	copyvar VAR_FRONTIER_GAMBLER_AMOUNT_BET, VAR_RESULT
	switch VAR_RESULT
	case FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_Bet5
	case FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_Bet10
	case FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_Bet15
	case FRONTIER_GAMBLER_BET_CANCEL, BattleFrontier_Lounge3_EventScript_CancelBet
	case MULTI_B_PRESSED, BattleFrontier_Lounge3_EventScript_CancelBet
	end

BattleFrontier_Lounge3_EventScript_Bet5:: @ 8261E30
	setvar VAR_0x8008, BET_AMOUNT_5
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet10:: @ 8261E3B
	setvar VAR_0x8008, BET_AMOUNT_10
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet15:: @ 8261E46
	setvar VAR_0x8008, BET_AMOUNT_15
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_TryPlaceBet:: @ 8261E51
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	compare VAR_TEMP_1, VAR_0x8008
	goto_if_ge BattleFrontier_Lounge3_EventScript_PlaceBet
	msgbox BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints, MSGBOX_DEFAULT
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_PlaceBet:: @ 8261E75
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BattleFrontier_Lounge3_Text_ThanksOffYouGo, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FinishBet
	end

BattleFrontier_Lounge3_EventScript_FinishBet:: @ 8261E96
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_Lounge3_EventScript_CountSilverSymbols:: @ 8261EA0
	setvar VAR_0x8004, 0
	call_if_set FLAG_SYS_TOWER_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_DOME_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PALACE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_ARENA_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_FACTORY_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PIKE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PYRAMID_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	return

BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount:: @ 8261EE5
	addvar VAR_0x8004, 1
	return

BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols:: @ 8261EEB
	msgbox BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_AlreadyMetGambler:: @ 8261EF9
	msgbox BattleFrontier_Lounge3_Text_Oh, MSGBOX_DEFAULT
	compare VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET
	goto_if_ge BattleFrontier_Lounge3_EventScript_CheckBetResults
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_CheckBetResults:: @ 8261F12
	compare VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET
	goto_if_eq BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted
	compare VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WON
	goto_if_eq BattleFrontier_Lounge3_EventScript_WonChallenge
	goto BattleFrontier_Lounge3_EventScript_LostChallenge
	end

BattleFrontier_Lounge3_EventScript_WonChallenge:: @ 8261F2E
	msgbox BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints, MSGBOX_DEFAULT
	compare VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_5
	call_if_eq BattleFrontier_Lounge3_EventScript_RewardBet5
	compare VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_10
	call_if_eq BattleFrontier_Lounge3_EventScript_RewardBet10
	compare VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_15
	call_if_eq BattleFrontier_Lounge3_EventScript_RewardBet15
	msgbox BattleFrontier_Lounge3_Text_ObtainedBattlePoints, MSGBOX_GETPOINTS
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_LostChallenge:: @ 8261F71
	msgbox BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_RewardBet5:: @ 8261F80
	buffernumberstring 0, (BET_AMOUNT_5 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_5 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet10:: @ 8261F8A
	buffernumberstring 0, (BET_AMOUNT_10 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_10 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet15:: @ 8261F94
	buffernumberstring 0, (BET_AMOUNT_15 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_15 * 2)
	return

BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted:: @ 8261F9E
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge3_EventScript_DeclineChallenge:: @ 8261FA5
	msgbox BattleFrontier_Lounge3_Text_NotInterested, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_CancelBet:: @ 8261FAF
	special CloseBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_DeclineChallenge
	end

BattleFrontier_Lounge3_EventScript_Man:: @ 8261FB8
	msgbox BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges, MSGBOX_NPC
	end

BattleFrontier_Lounge3_EventScript_Woman:: @ 8261FC1
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_BackedWrongTrainer, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_PokefanF:: @ 8261FD1
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FatMan:: @ 8261FE1
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_TrainerGoodButRattled, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FaceOriginalDirection:: @ 8261FF1
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere:: @ 8261FFE
	.string "뭐야?\p"
	.string "우린 지금 바빠!\n"
	.string "다음에 오도록 해!$"
	// なんだぁ?ｐ
	// おれたちゃ いま いそがしいの!ｎ
	// また こんどに してくれや!

BattleFrontier_Lounge3_Text_YouLookToughExplainGambling:: @ 8262061
	.string "...응?\n"
	.string "당신 강해 보이네...\p"
	.string "헤헤... ......\n"
	.string "잠깐 좋은 얘기가\l"
	.string "있으니까 들어봐!\p"
	.string "실은 우리 그룹이 말야\n"
	.string "배틀프런티어 안에서\l"
	.string "게임을 하고 있거든...\p"
	.string "규칙은 간단하지-\n"
	.string "우선 매회 시설 중\l"
	.string "하나를 골라!\p"
	.string "그리고 그곳에 도전하는\n"
	.string "트레이너 중 한 명을 고르고\l"
	.string "자신의 배틀포인트를 거는 거야!\p"
	.string "그렇게 해서 가장 좋은 성적을\n"
	.string "낸 트레이너에 건 녀석이\l"
	.string "배틀포인트를 전부 가져가는 거야!\p"
	.string "알겠어? 간단하지?\n"
	.string "...그래서$"
	// …… ん?ｎ
	// あんた つよそうだねぇ……ｐ
	// へっへ…… ……ｎ
	// ちょっと ィイはなしがｌ
	// あるから きいてけよ!ｐ
	// じつは おれたち グル-プはなｎ
	// バトルフロンティアの なかでｌ
	// ちょっとした ゲ-ムを してんのよ……ｐ
	// ル-ルは かんたん だぜ-ｎ
	// まずは まいかい どこかの しせつをｌ
	// ひとつ えらぶ!ｐ
	// つぎに そこに ちょうせん してるｎ
	// トレ-ナ-の だれか ひとりを えらんでｌ
	// じぶんの バトルポイントを かけるのよ!ｐ
	// んで いちばん いい せいせきをｎ
	// だした トレ-ナ-に かけてた やつがｌ
	// バトルポイントを ひとりじめ すんの!ｐ
	// なあっ? かんたん だろ?ｎ
	// んで……

BattleFrontier_Lounge3_Text_ChallengeBattleTowerSingle:: @ 8262261
	.string "지금 말야\n"
	.string "배틀타워의 싱글 배틀룸에\l"
	.string "도전할 트레이너를\l"
	.string "찾고 있었거든...\p"
	.string "느낌이 오는 트레이너가 없어서...\n"
	.string "있잖아...$"
	// ちょうど いまは よぉｎ
	// バトルタワ-の シングル バトルル-ムにｌ
	// ちょうせんする トレ-ナ-をｌ
	// さがしてん だけどよ……ｐ
	// ピンとくる トレ-ナ-が いなくてなぁ……ｎ
	// なぁ……

BattleFrontier_Lounge3_Text_ChallengeBattleTowerDouble:: @ 826230D
	.string "지금 말야\n"
	.string "배틀타워의 더블 배틀룸에\l"
	.string "도전할 트레이너를\l"
	.string "찾고 있었거든...\p"
	.string "느낌이 오는 트레이너가 없어서...\n"
	.string "있잖아...$"
	// ちょうど いまは よぉｎ
	// バトルタワ-の ダブル バトルル-ムにｌ
	// ちょうせんする トレ-ナ-をｌ
	// さがしてん だけどよ……ｐ
	// ピンとくる トレ-ナ-が いなくてなぁ……ｎ
	// なぁ……

BattleFrontier_Lounge3_Text_ChallengeBattleTowerMulti:: @ 82623B9
	.string "지금 말야\n"
	.string "배틀타워의 멀티 배틀룸에\l"
	.string "도전할 트레이너를\l"
	.string "찾고 있었거든...\p"
	.string "느낌이 오는 트레이너가 없어서...\n"
	.string "있잖아...$"
	// ちょうど いまは よぉｎ
	// バトルタワ-の マルチ バトルル-ムにｌ
	// ちょうせんする トレ-ナ-をｌ
	// さがしてん だけどよ……ｐ
	// ピンとくる トレ-ナ-が いなくてなぁ……ｎ
	// なぁ……

BattleFrontier_Lounge3_Text_ChallengeBattleDomeSingle:: @ 8262464
	.string "지금 말야\n"
	.string "배틀돔에서 하는\l"
	.string "싱글 배틀토너먼트에\l"
	.string "도전할 트레이너를\l"
	.string "찾고 있었거든...\p"
	.string "느낌이 오는 트레이너가 없어서...\n"
	.string "있잖아...$"
	// ちょうど いまは よぉｎ
	// バトルド-ムで やってるｌ
	// シングル バトルト-ナメントにｌ
	// ちょうせんする トレ-ナ-をｌ
	// さがしてん だけどよ……ｐ
	// ピンとくる トレ-ナ-が いなくてなぁ……ｎ
	// なぁ……

BattleFrontier_Lounge3_Text_ChallengeBattleDomeDouble:: @ 826250E
	.string "지금 말야\n"
	.string "배틀돔에서 하는\l"
	.string "더블 배틀토너먼트에\l"
	.string "도전할 트레이너를\l"
	.string "찾고 있었거든...\p"
	.string "느낌이 오는 트레이너가 없어서...\n"
	.string "있잖아...$"
	// ちょうど いまは よぉｎ
	// バトルド-ムで やってるｌ
	// ダブル バトルト-ナメントにｌ
	// ちょうせんする トレ-ナ-をｌ
	// さがしてん だけどよ……ｐ
	// ピンとくる トレ-ナ-が いなくてなぁ……ｎ
	// なぁ……

BattleFrontier_Lounge3_Text_ChallengeBattleFactorySingle:: @ 82625B8
	.string "지금 말야\n"
	.string "배틀팩토리에서 하는\l"
	.string "배틀트레이드 싱글에\l"
	.string "도전할 트레이너를\l"
	.string "찾고 있었거든...\p"
	.string "느낌이 오는 트레이너가 없어서...\n"
	.string "있잖아...$"
	// ちょうど いまは よぉｎ
	// バトルファクトリ-で やってるｌ
	// バトルトレ-ド シングルにｌ
	// ちょうせんする トレ-ナ-をｌ
	// さがしてん だけどよ……ｐ
	// ピンとくる トレ-ナ-が いなくてなぁ……ｎ
	// なぁ……

BattleFrontier_Lounge3_Text_ChallengeBattleFactoryDouble:: @ 826266A
	.string "지금 말야\n"
	.string "배틀팩토리에서 하는\l"
	.string "배틀트레이드 더블에\l"
	.string "도전할 트레이너를\l"
	.string "찾고 있었거든...\p"
	.string "느낌이 오는 트레이너가 없어서...\n"
	.string "있잖아...$"
	// ちょうど いまは よぉｎ
	// バトルファクトリ-で やってるｌ
	// バトルトレ-ド ダブルにｌ
	// ちょうせんする トレ-ナ-をｌ
	// さがしてん だけどよ……ｐ
	// ピンとくる トレ-ナ-が いなくてなぁ……ｎ
	// なぁ……

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceSingle:: @ 826271C
	.string "지금 말야\n"
	.string "배틀팰리스에서 하는\l"
	.string "싱글 배틀홀에\l"
	.string "도전할 트레이너를\l"
	.string "찾고 있었거든...\p"
	.string "느낌이 오는 트레이너가 없어서...\n"
	.string "있잖아...$"
	// ちょうど いまは よぉｎ
	// バトルパレスのｌ
	// シングル バトルホ-ルにｌ
	// ちょうせんする トレ-ナ-をｌ
	// さがしてん だけどよ……ｐ
	// ピンとくる トレ-ナ-が いなくてなぁ……ｎ
	// なぁ……

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceDouble:: @ 82627C9
	.string "지금 말야\n"
	.string "배틀팰리스에서 하는\l"
	.string "더블 배틀홀에\l"
	.string "도전할 트레이너를\l"
	.string "찾고 있었거든...\p"
	.string "느낌이 오는 트레이너가 없어서...\n"
	.string "있잖아...$"
	// ちょうど いまは よぉｎ
	// バトルパレスのｌ
	// ダブル バトルホ-ルにｌ
	// ちょうせんする トレ-ナ-をｌ
	// さがしてん だけどよ……ｐ
	// ピンとくる トレ-ナ-が いなくてなぁ……ｎ
	// なぁ……

BattleFrontier_Lounge3_Text_ChallengeBattleArena:: @ 8262876
	.string "지금 말야\n"
	.string "배틀아레나에서 하는\l"
	.string "연승팀배틀에\l"
	.string "도전할 트레이너를\l"
	.string "찾고 있었거든...\p"
	.string "느낌이 오는 트레이너가 없어서...\n"
	.string "있잖아...$"
	// ちょうど いまは よぉｎ
	// バトルアリ-ナで やってるｌ
	// かちぬきチ-ムバトルにｌ
	// ちょうせんする トレ-ナ-をｌ
	// さがしてん だけどよ……ｐ
	// ピンとくる トレ-ナ-が いなくてなぁ……ｎ
	// なぁ……

BattleFrontier_Lounge3_Text_ChallengeBattlePike:: @ 826291A
	.string "지금 말야\n"
	.string "배틀튜브에서 하는\l"
	.string "배틀게임에\l"
	.string "도전할 트레이너를\l"
	.string "찾고 있었거든...\p"
	.string "느낌이 오는 트레이너가 없어서...\n"
	.string "있잖아...$"
	// ちょうど いまは よぉｎ
	// バトルチュ-ブで やってるｌ
	// バトルゲ-ムにｌ
	// ちょうせんする トレ-ナ-をｌ
	// さがしてん だけどよ……ｐ
	// ピンとくる トレ-ナ-が いなくてなぁ……ｎ
	// なぁ……

BattleFrontier_Lounge3_Text_ChallengeBattlePyramid:: @ 82629BC
	.string "지금 말야\n"
	.string "배틀피라미드에서 하는\l"
	.string "배틀어드벤처에\l"
	.string "도전할 트레이너를\l"
	.string "찾고 있었거든...\p"
	.string "느낌이 오는 트레이너가 없어서...\n"
	.string "있잖아...$"
	// ちょうど いまは よぉｎ
	// バトルピラミッドで やってるｌ
	// バトルアドベンチャ-にｌ
	// ちょうせんする トレ-ナ-をｌ
	// さがしてん だけどよ……ｐ
	// ピンとくる トレ-ナ-が いなくてなぁ……ｎ
	// なぁ……

BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe:: @ 8262A60
	.string "너한테도 포인트 벌게 해줄 테니까-\n"
	.string "한번 도전해 보는 건 어때?$"
	// あんたにも もうけさせて やるからよぅ-ｎ
	// サクっと ちょうせん してきて くんねぇ?

BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints:: @ 8262ABD
	.string "그럼... 너의\n"
	.string "배틀포인트 잠깐이라도 좋으니까\l"
	.string "나한테 맡겨보지 않을래?\p"
	.string "제대로 은혜는 갚을 테니까!$"
	// じゃあよ…… あんたのｎ
	// バトルポイント ちょ-っとで いいからｌ
	// おれに あずけて くんねぇ?ｐ
	// ちゃ-んと おれいは するからよ!

BattleFrontier_Lounge3_Text_HowMuchCanYouSpot:: @ 8262B42
	.string "좋아! 좋아!\n"
	.string "그래서? 얼마나 빌려줄 거야?$"
	// ィイね! ィイね!ｎ
	// で? で? で? いくら かして くれます?

BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints:: @ 8262B6E
	.string "싫어싫어싫어-!!\p"
	.string "배틀포인트가 부족하잖아!\n"
	.string "재미없는 농담은 그만두라고!$"
	// いやいやいや-!!ｐ
	// バトルポイントが たらない じゃない!ｎ
	// つまんない じょうだん やめましょうや!

BattleFrontier_Lounge3_Text_ThanksOffYouGo:: @ 8262BE0
	.string "헤헤헤... 고마워!\n"
	.string "그럼-$"
	// へっへっへっ…… あんがとよ!ｎ
	// そんじゃ-

BattleFrontier_Lounge3_Text_GetToBattleTowerSingle:: @ 8262C04
	.string "그럼 제대로\n"
	.string "배틀타워 싱글 배틀룸에\p"
	.string "다녀오도록 해!\n"
	.string "져서 돌아오지 말라고!\l"
	.string "나와 너의 미래를 위해!$"
	// サクサクッとｎ
	// バトルタワ-の シングル バトルル-ムにｌ
	// いってきて ちょ-だいっ!ｐ
	// がんばれ よぉ-!ｎ
	// まちがえんな よぉ-!ｌ
	// おれと あんたの みらいの ためだかんな!

BattleFrontier_Lounge3_Text_GetToBattleTowerDouble:: @ 8262C90
	.string "그럼 제대로\n"
	.string "배틀타워 더블 배틀룸에\p"
	.string "다녀오도록 해!\n"
	.string "져서 돌아오지 말라고!\l"
	.string "나와 너의 미래를 위해!$"
	// サクサクッとｎ
	// バトルタワ-の ダブル バトルル-ムにｌ
	// いってきて ちょ-だいっ!ｐ
	// がんばれ よぉ-!ｎ
	// まちがえんな よぉ-!ｌ
	// おれと あんたの みらいの ためだかんな!

BattleFrontier_Lounge3_Text_GetToBattleTowerMulti:: @ 8262D1C
	.string "그럼 제대로\n"
	.string "배틀타워 멀티 배틀룸에\p"
	.string "다녀오도록 해!\n"
	.string "져서 돌아오지 말라고!\l"
	.string "나와 너의 미래를 위해!$"
	// サクサクッとｎ
	// バトルタワ-の マルチ バトルル-ムにｌ
	// いってきて ちょ-だいっ!ｐ
	// がんばれ よぉ-!ｎ
	// まちがえんな よぉ-!ｌ
	// おれと あんたの みらいの ためだかんな!

BattleFrontier_Lounge3_Text_GetToBattleDomeSingle:: @ 8262DA7
	.string "그럼 제대로 배틀돔의\n"
	.string "싱글 배틀토너먼트에\p"
	.string "다녀오도록 해!\n"
	.string "져서 돌아오지 말라고!\l"
	.string "나와 너의 미래를 위해!$"
	// サクサクッと バトルド-ムのｎ
	// シングル バトルト-ナメントにｌ
	// いってきて ちょ-だいっ!ｐ
	// がんばれ よぉ-!ｎ
	// まちがえんな よぉ-!ｌ
	// おれと あんたの みらいの ためだかんな!

BattleFrontier_Lounge3_Text_GetToBattleDomeDouble:: @ 8262E34
	.string "그럼 제대로 배틀돔의\n"
	.string "더블 배틀토너먼트에\p"
	.string "다녀오도록 해!\n"
	.string "져서 돌아오지 말라고!\l"
	.string "나와 너의 미래를 위해!$"
	// サクサクッと バトルド-ムのｎ
	// ダブル バトルト-ナメントにｌ
	// いってきて ちょ-だいっ!ｐ
	// がんばれ よぉ-!ｎ
	// まちがえんな よぉ-!ｌ
	// おれと あんたの みらいの ためだかんな!

BattleFrontier_Lounge3_Text_GetToBattleFactorySingle:: @ 8262EC1
	.string "그럼 제대로 배틀팩토리의\n"
	.string "배틀트레이드 싱글에\p"
	.string "다녀오도록 해!\n"
	.string "져서 돌아오지 말라고!\l"
	.string "나와 너의 미래를 위해!$"
	// サクサクッと バトルファクトリ-のｎ
	// バトルトレ-ド シングルにｌ
	// いってきて ちょ-だいっ!ｐ
	// がんばれ よぉ-!ｎ
	// まちがえんな よぉ-!ｌ
	// おれと あんたの みらいの ためだかんな!

BattleFrontier_Lounge3_Text_GetToBattleFactoryDouble:: @ 8262F56
	.string "그럼 제대로 배틀팩토리의\n"
	.string "배틀트레이드 더블에\p"
	.string "다녀오도록 해!\n"
	.string "져서 돌아오지 말라고!\l"
	.string "나와 너의 미래를 위해!$"
	// サクサクッと バトルファクトリ-のｎ
	// バトルトレ-ド ダブルにｌ
	// いってきて ちょ-だいっ!ｐ
	// がんばれ よぉ-!ｎ
	// まちがえんな よぉ-!ｌ
	// おれと あんたの みらいの ためだかんな!

BattleFrontier_Lounge3_Text_GetToBattlePalaceSingle:: @ 8262FEB
	.string "그럼 제대로 배틀팰리스의\n"
	.string "싱글 배틀홀에\p"
	.string "다녀오도록 해!\n"
	.string "져서 돌아오지 말라고!\l"
	.string "나와 너의 미래를 위해!$"
	// サクサクッと バトルパレスのｎ
	// シングル バトルホ-ルにｌ
	// いってきて ちょ-だいっ!ｐ
	// がんばれ よぉ-!ｎ
	// まちがえんな よぉ-!ｌ
	// おれと あんたの みらいの ためだかんな!

BattleFrontier_Lounge3_Text_GetToBattlePalaceDouble:: @ 8263078
	.string "그럼 제대로 배틀팩토리의\n"
	.string "더블 배틀홀에\p"
	.string "다녀오도록 해!\n"
	.string "져서 돌아오지 말라고!\l"
	.string "나와 너의 미래를 위해!$"
	// サクサクッと バトルパレスのｎ
	// ダブル バトルホ-ルにｌ
	// いってきて ちょ-だいっ!ｐ
	// がんばれ よぉ-!ｎ
	// まちがえんな よぉ-!ｌ
	// おれと あんたの みらいの ためだかんな!

BattleFrontier_Lounge3_Text_GetToBattleArena:: @ 8263105
	.string "그럼 제대로 배틀아레나의\n"
	.string "연승팀배틀에\p"
	.string "다녀오도록 해!\n"
	.string "져서 돌아오지 말라고!\l"
	.string "나와 너의 미래를 위해!$"
	// サクサクッと バトルアリ-ナのｎ
	// かちぬきチ-ムバトルにｌ
	// いってきて ちょ-だいっ!ｐ
	// がんばれ よぉ-!ｎ
	// まちがえんな よぉ-!ｌ
	// おれと あんたの みらいの ためだかんな!

BattleFrontier_Lounge3_Text_GetToBattlePike:: @ 826318C
	.string "그럼 제대로 배틀튜브의\n"
	.string "배틀게임에\p"
	.string "다녀오도록 해!\n"
	.string "져서 돌아오지 말라고!\l"
	.string "나와 너의 미래를 위해!$"
	// サクサクッと バトルチュ-ブのｎ
	// バトルゲ-ムにｌ
	// いってきて ちょ-だいっ!ｐ
	// がんばれ よぉ-!ｎ
	// まちがえんな よぉ-!ｌ
	// おれと あんたの みらいの ためだかんな!

BattleFrontier_Lounge3_Text_GetToBattlePyramid:: @ 8263211
	.string "그럼 제대로 배틀피라미드의\n"
	.string "배틀어드벤처에\p"
	.string "다녀오도록 해!\n"
	.string "져서 돌아오지 말라고!\l"
	.string "나와 너의 미래를 위해!$"
	// サクサクッと バトルピラミッドのｎ
	// バトルアドベンチャ-にｌ
	// いってきて ちょ-だいっ!ｐ
	// がんばれ よぉ-!ｎ
	// まちがえんな よぉ-!ｌ
	// おれと あんたの みらいの ためだかんな!

BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints:: @ 8263298
	.string "아아 너... 수고했어...\p"
	.string "미안하지만 배틀포인트는\n"
	.string "못 갚게 됐어...\p"
	.string "...뭐 서로 다음 기회에\n"
	.string "힘내 보자...$"
	// あぁ あんた…… ごくろう さん……ｐ
	// わり-けど バトルポイントはｎ
	// かえせねぇよ……ｐ
	// …… まぁ おたがい つぎの きかいにｎ
	// がんばり ましょうや……

BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints:: @ 8263334
	.string "어이! 선생님!!\p"
	.string "역시! 당신이에요-!!\n"
	.string "저 엄청 벌었어요!\p"
	.string "배틀포인트 돌려드릴게요!\n"
	.string "기꺼이 돌려드리겠습니다!$"
	// ぃよおっ!! せんせい!!ｐ
	// さすが! さすが ですねぇ-!!ｎ
	// わたくし おおもうけで ございますよぉ!ｐ
	// バトルポイント おかえし しますよっ!ｎ
	// しっかり のしつけて さしあげますよぉ!

BattleFrontier_Lounge3_Text_ObtainedBattlePoints:: @ 82633D4
	.string "{PLAYER}{K_EUNNEUN} 배틀포인트를\n"
	.string "{STR_VAR_1}BP 손에 넣었다!$"
	// §あは バトルポイントをｎ
	// §いBP てにいれた!

BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge:: @ 82633F2
	.string "또 뭔가 볼일이 있다면\n"
	.string "잘 부탁드리겠습니다!!$"
	// また なんか あったらｎ
	// よろしく たのみますよっ!!

BattleFrontier_Lounge3_Text_NotInterested:: @ 826342D
	.string "그건 아니지-!\n"
	.string "세상 물정 모르는 꼬마구나!$"
	// そりゃ ないぜ-!ｎ
	// せちがれぇ おこさま だなぁ!!

BattleFrontier_Lounge3_Text_Oh:: @ 826346B
	.string "오옷...$"
	// おっ……

BattleFrontier_Lounge3_Text_BackedWrongTrainer:: @ 826346F
	.string "또 빗나갔어?\p"
	.string "나도 평범하게\n"
	.string "배틀하는 편이 좋으려나...$"
	// ま-た- は-ず-れ-?ｐ
	// あたし ふつうにｎ
	// たたかった ほうが いいの かなぁ-

BattleFrontier_Lounge3_Text_TrainerGoodButRattled:: @ 82634C9
	.string "저 트레이너... 강하지만\p"
	.string "배틀돔에서는 엄청 긴장해\n"
	.string "버린단 말이지..$"
	// あの トレ-ナ-…… つよいけどｎ
	// バトルド-ムだと すごく きんちょうｌ
	// しちゃうん だよなぁ……

BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne:: @ 826351D
	.string "우후훗!\n"
	.string "왕창! 왕창 벌 거야!$"
	// うふふっ!ｎ
	// ボロもうけ! ボロもうけなのよ!

BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges:: @ 8263545
	.string "저 녀석들 트레이너면서\n"
	.string "도전하지 않고\l"
	.string "뭐하고 있는 걸까?$"
	// あいつら トレ-ナ-の くせにｎ
	// ちょうせんも しないでｌ
	// なに してるん だろうな?
