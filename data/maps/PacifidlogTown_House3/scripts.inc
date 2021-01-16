PacifidlogTown_House3_MapScripts:: @ 8203C10
	.byte 0

PacifidlogTown_House3_EventScript_Trader:: @ 8203C11
	lock
	faceplayer
	goto_if_set FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED, PacifidlogTown_House3_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_HORSEA
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox PacifidlogTown_House3_Text_WillingToTradeIt, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq PacifidlogTown_House3_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	compare VAR_0x8004, 255
	goto_if_eq PacifidlogTown_House3_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	compare VAR_RESULT, VAR_0x8009
	goto_if_ne PacifidlogTown_House3_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname 0, VAR_0x8009
	msgbox PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou, MSGBOX_DEFAULT
	setflag FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED
	release
	end

PacifidlogTown_House3_EventScript_DeclineTrade:: @ 8203C93
	msgbox PacifidlogTown_House3_Text_NotDesperateOrAnything, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_NotRequestedMon:: @ 8203C9D
	bufferspeciesname 0, VAR_0x8009
	msgbox PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_TradeCompleted:: @ 8203CAB
	msgbox PacifidlogTown_House3_Text_ReallyWantedToGetBagon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_Girl:: @ 8203CB5
	msgbox PacifidlogTown_House3_Text_IsThatAPokedex, MSGBOX_NPC
	end

PacifidlogTown_House3_Text_WillingToTradeIt: @ 8203CBE
	.string "봐줘 나의 {STR_VAR_2}!\n"
	.string "내가 어제 생일이었던\l"
	.string "기념으로 잡은 {STR_VAR_2}{K_I}야!\p"
	.string "오! 갖고 싶다는 얼굴인데?\n"
	.string "뭐 소중한 {STR_VAR_2}{K_I}니까!\p"
	.string "좋아! {STR_VAR_1}{K_I}라면\n"
	.string "교환해 주도록 할게!$"
	// みてくれよ この §う!ｎ
	// おれが きのう じぶんの たんじょうびにｌ
	// きねんに つかまえた §うだ!ｐ
	// お! ほしい って かおを したな?ｎ
	// まっ きちょうな §うだからな!ｐ
	// よし! §いと だったらｎ
	// こうかん して やっても いいぞ!

PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou: @ 8203D87
	.string "오옷 이게 {STR_VAR_1}{K_I}구나-!\n"
	.string "역시 {STR_VAR_2}{K_WAGWA}는\l"
	.string "여러 가지 닮았으면서도\l"
	.string "미묘하게 다르네!\p"
	.string "고마워!$"
	// おっ これが §い かあ-!ｎ
	// やっぱ §う とはｌ
	// いろいろ にている ようでｌ
	// びみょうに ちがうなあ!ｐ
	// サンキュ!

PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon: @ 8203DDE
	.string "안돼안돼! {STR_VAR_1}{K_IGA} 아니라면\n"
	.string "받을 수 없어!$"
	// だめだめ! §い じゃないと ｎ
	// ひきうけられないね!

PacifidlogTown_House3_Text_NotDesperateOrAnything: @ 8203E12
	.string "흐-음 관두는 거구가...\p"
	.string "뭐 나도\n"
	.string "꼭 해야만 하는 건 아니니까$"
	// ふ-ん やめるのか……ｐ
	// まっ おれのほうもｎ
	// どうしても って わけじゃ ないしね

PacifidlogTown_House3_Text_ReallyWantedToGetBagon: @ 8203E7F
	.string "스스로 찾아도 되지만...\p"
	.string "다른 트레이너가 잡은\n"
	.string "아공이란 녀석을\l"
	.string "어떻게든 갖고 싶단 말이지$"
	// じぶんで さがしても いいんだけど……ｐ
	// ほかの トレ-ナ-が つかまえたｎ
	// タツベイ って いうのがｌ
	// どうしても ほしかったんだよね

PacifidlogTown_House3_Text_IsThatAPokedex: @ 8203EF1
	.string "그거 포켓몬 도감이야?\p"
	.string "그 말은 너 많은 포켓몬이랑\n"
	.string "만났다는 소리 아니야?\p"
	.string "그거 정말 부러워!$"
	// それって ポケモンずかん?ｐ
	// それって あなた たくさんのｎ
	// ポケモンと であった ってこと?ｐ
	// それって すっごい うらやましい!

