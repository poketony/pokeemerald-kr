FortreeCity_House5_MapScripts:: @ 8217EF1
	.byte 0

FortreeCity_House5_EventScript_PokefanF:: @ 8217EF2
	msgbox FortreeCity_House5_Text_TreeHousesAreGreat, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Man:: @ 8217EFB
	msgbox FortreeCity_House5_Text_AdaptedToNature, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Zigzagoon:: @ 8217F04
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, 0
	msgbox FortreeCity_House5_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House5_Text_TreeHousesAreGreat: @ 8217F17
	.string "검방울시티의 트리하우스는 굉장해!\n"
	.string "포켓몬이랑 같이 살기에\l"
	.string "가장 좋은 마을이라고 생각하고 있어!$"
	// ヒワマキの ツリ-ハウスって さいこう!ｎ
	// ポケモンと いっしょに くらすならｌ
	// いちばんの まちだと おもっているわ!

FortreeCity_House5_Text_AdaptedToNature: @ 8217F80
	.string "포켓몬도 사람도\n"
	.string "자연과 함께 어울려 살아왔으니\p"
	.string "이제 와서 억지로 우리 사정에\n"
	.string "자연을 맞추려고 하지 않아도 돼$"
	// ポケモンも ひともｎ
	// しぜんに あわせて くらしてきたからなｐ
	// いまさら じぶんらの つごうにｎ
	// しぜんを あわせなくて いいんだよ

FortreeCity_House5_Text_Zigzagoon: @ 8217FFB
	.string "지그제구리: 부후우!!$"
	// ジグザグマ『ぶふう!!

