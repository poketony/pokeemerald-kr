RustboroCity_House1_MapScripts:: @ 821593E
	.byte 0

RustboroCity_House1_EventScript_Trader:: @ 821593F
	lock
	faceplayer
	goto_if_set FLAG_RUSTBORO_NPC_TRADE_COMPLETED, RustboroCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_SEEDOT
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox RustboroCity_House1_Text_IllTradeIfYouWant, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	compare VAR_0x8004, 255
	goto_if_eq RustboroCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	compare VAR_RESULT, VAR_0x8009
	goto_if_ne RustboroCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox RustboroCity_House1_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_RUSTBORO_NPC_TRADE_COMPLETED
	release
	end

RustboroCity_House1_EventScript_DeclineTrade:: @ 82159BD
	msgbox RustboroCity_House1_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_NotRequestedMon:: @ 82159C7
	bufferspeciesname 0, VAR_0x8009
	msgbox RustboroCity_House1_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TradeCompleted:: @ 82159D5
	msgbox RustboroCity_House1_Text_AnyPokemonCanBeCute, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_Hiker:: @ 82159DF
	msgbox RustboroCity_House1_Text_AllSortsOfPlaces, MSGBOX_NPC
	end

RustboroCity_House1_Text_IllTradeIfYouWant: @ 82159E8
	.string "뭐?\n"
	.string "내 포켓몬이 귀엽다고?\l"
	.string "응 알고 있어-\p"
	.string "앗 정말로 원한다면\n"
	.string "교환해 줄 수 있어\p"
	.string "그럼 내 {STR_VAR_2}{K_EULREUL}\n"
	.string "{STR_VAR_1}{K_WAGWA} 교환해 줄게$"
	@ いいえ?ｎ
	@ ぼくの ポケモンが かわいい?ｌ
	@ ウン しってるよ-ｐ
	@ あっ どうしても って いうならｎ
	@ こうかん して あげても いいよｐ
	@ じゃあ ぼくの §うｎ
	@ §い となら こうかん するよ

RustboroCity_House1_Text_PleaseBeGoodToMyPokemon: @ 8215A77
	.string "에헤헤...\n"
	.string "제대로 귀여워해 줘$"
	@ えへへ……ｎ
	@ ちゃんと かわいがってね

RustboroCity_House1_Text_DoesntLookLikeMonToMe: @ 8215A9D
	.string "어- 아무리 봐도 {STR_VAR_1}{K_EU}로는\n"
	.string "안 보이는데...$"
	@ え- どうみても §いにｎ
	@ みえないんだけど……

RustboroCity_House1_Text_YouDontWantToThatsOkay: @ 8215ACE
	.string "아 싫으면 됐어...\n"
	.string "참 귀여운 포켓몬인데...$"
	@ あ いやなら いいけど……ｎ
	@ せっかく かわいい ポケモンなのに

RustboroCity_House1_Text_AnyPokemonCanBeCute: @ 8215B17
	.string "소중히 키운다면\n"
	.string "어떤 포켓몬도 엄청 귀엽지-$"
	@ だいじに そだてるとｎ
	@ どんな ポケモンも すごく かわいいよね-

RustboroCity_House1_Text_AllSortsOfPlaces: @ 8215B57
	.string "다양한 장소에\n"
	.string "다양한 포켓몬이 있고\l"
	.string "다양한 사람들도 있어\p"
	.string "그게 좋아서 나도\n"
	.string "다양한 곳으로 가는 거야!$"
	@ いろんな ばしょにｎ
	@ いろんな ポケモンが いるｌ
	@ いろんな ひとも いるｐ
	@ それが たのしみで わしもｎ
	@ いろんな ところに でかけるのさ!

