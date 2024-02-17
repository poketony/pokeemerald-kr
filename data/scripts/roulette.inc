Roulette_EventScript_Table1:: @ 82A5AB1
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 0
	getpricereduction POKENEWS_GAME_CORNER
	compare VAR_RESULT, FALSE
	goto_if_eq Roulette_EventScript_Play
	addvar VAR_0x8004, ROULETTE_SPECIAL_RATE
	goto Roulette_EventScript_Play
	end

Roulette_EventScript_Table2:: @ 82A5ADF
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 1
	getpricereduction POKENEWS_GAME_CORNER
	compare VAR_RESULT, FALSE
	goto_if_eq Roulette_EventScript_Play
	addvar VAR_0x8004, ROULETTE_SPECIAL_RATE
	goto Roulette_EventScript_Play
	end

Roulette_EventScript_Play:: @ 82A5B0D
	special PlayRoulette
	waitstate
	end
	
Roulette_Text_PlayMinimumWagerIsX::
	.string "여기는 레이트 {STR_VAR_1}의 룰렛입니다\n"
	.string "룰렛을 즐기겠습니까?$"
	// ここは レ-ト§いの ル-レットだい ですｎ
	// ル-レットで あそびますか?

Roulette_Text_NotEnoughCoins::
	.string "동전이 부족합니다$"
	// コインが たりません

Roulette_Text_SpecialRateTable::
	.string "오늘 이 테이블은\n"
	.string "레이트 업!$"
	// ほんじつ このだいではｎ
	// レ-ト アップ じっしちゅう!

Roulette_Text_ControlsInstruction::
	.string "베팅할 곳을 십자 버튼으로 선택하고\n"
	.string "A 버튼으로 결정합니다$"
	// ベットする わくを じゅうじボタンで えらんでｎ
	// Aボタンで けってい します

Roulette_Text_ItsAHit::
	.string "당첨-!$"
	// あたり-!

Roulette_Text_Jackpot::
	.string "대당첨!!$"
	// おおあたり!!

Roulette_Text_NothingDoing::
	.string "꽝-$"
	// はずれ-

Roulette_Text_YouveWonXCoins::
	.string "축하합니다!\n"
	.string "동전 {STR_VAR_1}개를 얻습니다!$"
	// おめでとう ございます!ｎ
	// コイン §いまい はいります!

Roulette_Text_NoCoinsLeft::
	.string "동전이 다 떨어졌습니다$"
	// コインが なくなりました

Roulette_Text_KeepPlaying::
	.string "계속해서 즐기겠습니까?$"
	// つづけて あそびますか?

Roulette_Text_BoardWillBeCleared::
	.string "테이블 위의 구슬을\n"
	.string "리셋합니다$"
	// だいの うえの たまをｎ
	// クリア します

@ Unused
Roulette_Text_YouDontHaveACoinCase::
	.string "동전케이스를 가지고 있지 않습니다!$"
	// コインケ-スを もっていません!

Roulette_Text_CoinCaseIsFull::
	.string "동전이 가득 찼습니다!\n"
	.string "경품과 교환해 주십시오$"
	// コインが いっぱいです!ｎ
	// けいひんと こうかん して ください
