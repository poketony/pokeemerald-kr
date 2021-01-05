BattleFrontier_Lounge6_MapScripts:: @ 8264FEC
	.byte 0

BattleFrontier_Lounge6_EventScript_Trader:: @ 8264FED
	lock
	faceplayer
	goto_if_set FLAG_BATTLE_FRONTIER_TRADE_DONE, BattleFrontier_Lounge6_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_MEOWTH
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox BattleFrontier_Lounge6_Text_WouldYouLikeToTrade, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge6_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	compare VAR_0x8004, 255
	goto_if_eq BattleFrontier_Lounge6_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	compare VAR_RESULT, VAR_0x8009
	goto_if_ne BattleFrontier_Lounge6_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt, MSGBOX_DEFAULT
	setflag FLAG_BATTLE_FRONTIER_TRADE_DONE
	release
	end

BattleFrontier_Lounge6_EventScript_DeclineTrade:: @ 826506B
	msgbox BattleFrontier_Lounge6_Text_WellThatsFineToo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_NotRequestedMon:: @ 8265075
	bufferspeciesname 0, VAR_0x8009
	msgbox BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TradeCompleted:: @ 8265083
	msgbox BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_Text_WouldYouLikeToTrade: @ 826508D
	.string "나의 이 포켓몬\n"
	.string "{STR_VAR_2}{K_I}라는데 알고 있나요?\l"
	.string "꽤 귀엽고 느낌도 좋아요-\p"
	.string "이 애라면 저\n"
	.string "자신 있게 교환할 수 있어요!\p"
	.string "어때요?\n"
	.string "저의 이 {STR_VAR_2}{K_WAGWA}\l"
	.string "{STR_VAR_1}{K_EULREUL} 교환하실래요?$"
	// わたしの この ポケモンｎ
	// §うって いうんですよ しってます?ｌ
	// なかなか かわいくて イイかんじ ですよ-ｐ
	// このコ だったら わたしｎ
	// むねをはって こうかんに だせます!ｐ
	// どうです?ｎ
	// わたしの この §うｌ
	// §いと こうかん しません?

BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt: @ 8265128
	.string "와- 귀엽네요-...!\n"
	.string "정말 고마워요\l"
	.string "소중하게 키울게요!\p"
	.string "앗 {STR_VAR_2}도\n"
	.string "잘 부탁드려요!$"
	// わ- かわいい ですね-……!ｎ
	// どうも ありがとうｌ
	// たいせつに しますよ!ｐ
	// あっ §うもｎ
	// よろしく おねがい します!

BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon: @ 826518D
	.string "앗 죄송해요!\n"
	.string "저 {STR_VAR_1}{K_IGA} 아니면\l"
	.string "교환할 생각이 없어서-$"
	// あ ゴメンなさい!ｎ
	// わたし §い いがいとはｌ
	// こうかん するつもり ないんで-

BattleFrontier_Lounge6_Text_WellThatsFineToo: @ 82651CB
	.string "아 안되는 건가요!\n"
	.string "딱히 상관은 없지만\l"
	.string "다음에 또 와주세요-$"
	// あ やめますか!ｎ
	// べつに いいですよｌ
	// また こんど きてください-

BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined: @ 826520E
	.string "우후후!\n"
	.string "에나비가 생각했던 것보다 더\l"
	.string "귀여워서 정말로 기뻐요-$"
	// うふふ!ｎ
	// エネコが おもってたより ずっとｌ
	// かわいくて ほんと うれしいです-
