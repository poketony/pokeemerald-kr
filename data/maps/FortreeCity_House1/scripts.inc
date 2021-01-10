FortreeCity_House1_MapScripts:: @ 82162BA
	.byte 0

FortreeCity_House1_EventScript_Trader:: @ 82162BB
	lock
	faceplayer
	goto_if_set FLAG_FORTREE_NPC_TRADE_COMPLETED, FortreeCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_PLUSLE
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox FortreeCity_House1_Text_YouWillTradeWontYou, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq FortreeCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	compare VAR_0x8004, 255
	goto_if_eq FortreeCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	compare VAR_RESULT, VAR_0x8009
	goto_if_ne FortreeCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname 0, VAR_0x8009
	msgbox FortreeCity_House1_Text_MonYouTakeCare, MSGBOX_DEFAULT
	setflag FLAG_FORTREE_NPC_TRADE_COMPLETED
	release
	end

FortreeCity_House1_EventScript_DeclineTrade:: @ 821633D
	msgbox FortreeCity_House1_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_NotRequestedMon:: @ 8216347
	bufferspeciesname 0, VAR_0x8009
	msgbox FortreeCity_House1_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_TradeCompleted:: @ 8216355
	msgbox FortreeCity_House1_Text_GoingToMakeVolbeatStrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_ExpertF:: @ 821635F
	msgbox FortreeCity_House1_Text_TradingMemoriesWithOthers, MSGBOX_NPC
	end

FortreeCity_House1_EventScript_Zigzagoon:: @ 8216368
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, 0
	msgbox FortreeCity_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House1_Text_YouWillTradeWontYou: @ 821637B
	.string "우오-!\n"
	.string "어떻게 해서든 {STR_VAR_1}{K_EULREUL}\l"
	.string "가지고 싶어! ...이런\l"
	.string "마음의 소리를 들켜버렸군!\p"
	.string "들었다면\n"
	.string "네 {STR_VAR_1}{K_WAGWA} {STR_VAR_2}{K_EULREUL}\l"
	.string "당연히 교환해 줘야겠어!$"
	// うぉ-!ｎ
	// どうしても §いが ほし-っ!ｌ
	// ……とｌ
	// こころの さけびを きかれて しまった!ｐ
	// きいた からにはｎ
	// きみの §いと ボクの §うをｌ
	// もちろん こうかん するでしょ!

FortreeCity_House1_Text_MonYouTakeCare: @ 8216440
	.string "오- 해냈다-!\p"
	.string "{STR_VAR_1} 잘 왔어-!\n"
	.string "{STR_VAR_2} 건강해야 해-!$"
	// お- やった-!ｐ
	// §い よくきたな-!ｎ
	// §う げんきで やれよ-!

FortreeCity_House1_Text_ThisIsntAMon: @ 8216474
	.string "아니 그거\n"
	.string "{STR_VAR_1} 아니잖아$"
	// いやソレｎ
	// §いじゃないでしょ

FortreeCity_House1_Text_YouWontTradeMe: @ 821649F
	.string "뭐 교환하지 않는 거야?\n"
	.string "마음의 소리를 들었으면서...?$"
	// え こうかん しないの?ｎ
	// こころの さけびを きいたくせに……

FortreeCity_House1_Text_GoingToMakeVolbeatStrong: @ 82164DB
	.string "좋아 지금부터\n"
	.string "볼비트를 강하게 키우겠어-!\l"
	.string "플러시도 강하게 키울 거야-!$"
	// よし いまからｎ
	// バルビ-トを つよく するぞ-!ｌ
	// プラスルも つよく してやってよ!

FortreeCity_House1_Text_TradingMemoriesWithOthers: @ 821653B
	.string "다른 사람과 포켓몬을\n"
	.string "교환하는 것...\p"
	.string "그건 자신들의 추억을\n"
	.string "교환하는 거나 마찬가지지$"

FortreeCity_House1_Text_Zigzagoon: @ 8216597
	.string "지그제구리: 크옹?$"

