MossdeepCity_Mart_MapScripts:: @ 82223C7
	.byte 0

MossdeepCity_Mart_EventScript_Clerk:: @ 82223C8
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MossdeepCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MossdeepCity_Mart_Pokemart: @ 82223E0
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_NONE
	release
	end

MossdeepCity_Mart_EventScript_Woman:: @ 82223F6
	msgbox MossdeepCity_Mart_Text_ReviveIsFantastic, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Boy:: @ 82223FF
	msgbox MossdeepCity_Mart_Text_MaxRepelLastsLongest, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Sailor:: @ 8222408
	msgbox MossdeepCity_Mart_Text_NetAndDiveBallsRare, MSGBOX_NPC
	end

MossdeepCity_Mart_Text_ReviveIsFantastic: @ 8222411
	.string "기력의조각은 정말 대단해!\p"
	.string "이걸 주면\n"
	.string "기절한 포켓몬도 깨어나거든!\p"
	.string "그치만 파워포인트는\n"
	.string "회복 안 되니까 조심해!$"
	@ げんきのかけら って すごい!ｐ
	@ これを あたえるとｎ
	@ ひんしの ポケモンも めざめるの!ｐ
	@ でも パワ-ポイントはｎ
	@ かいふく しないから きをつけて!

MossdeepCity_Mart_Text_MaxRepelLastsLongest: @ 82224A0
	.string "골드스프레이는\n"
	.string "약한 포켓몬이 못 오게 해\p"
	.string "다양한 스프레이 중에서\n"
	.string "제일 지속 시간이 길어!$"
	@ ゴ-ルドスプレ-はｎ
	@ よわい ポケモンを よせつけないｐ
	@ かずある スプレ-の なかでｎ
	@ いちばん ながもち するんだ!

MossdeepCity_Mart_Text_NetAndDiveBallsRare: @ 82224FA
	.string "넷트볼과 다이브볼은\n"
	.string "여기 이끼시티에서만 파는\l"
	.string "희귀한 몬스터볼이야!\p"
	.string "넷트볼은 벌레타입이나\n"
	.string "물타입 포켓몬에게 효과적이야!\p"
	.string "다이브볼은 해저에 있는\n"
	.string "포켓몬을 쉽게 잡을 수 있어!$"
	@ ネットボ-ルと ダイブボ-ルはｎ
	@ ここ トクサネでしか つくっていないｌ
	@ めずらしい モンスタ-ボ-ル!ｐ
	@ ネットボ-ルは むしタイプやｎ
	@ みずタイプの ポケモンに こうかてき!ｐ
	@ ダイブボ-ルは かいていに いるｎ
	@ ポケモンを つかまえ やすいんだ!

