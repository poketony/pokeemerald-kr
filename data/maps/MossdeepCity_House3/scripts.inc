MossdeepCity_House3_MapScripts:: @ 82225C2
	.byte 0

MossdeepCity_House3_EventScript_SuperRodFisherman:: @ 82225C3
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SUPER_ROD, MossdeepCity_House3_EventScript_ReceivedSuperRod
	msgbox MossdeepCity_House3_Text_YouWantSuperRod, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MossdeepCity_House3_EventScript_DeclineSuperRod
	msgbox MossdeepCity_House3_Text_SuperRodIsSuper, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	setflag FLAG_RECEIVED_SUPER_ROD
	msgbox MossdeepCity_House3_Text_TryDroppingRodInWater, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_ReceivedSuperRod:: @ 8222602
	msgbox MossdeepCity_House3_Text_GoAfterSeafloorPokemon, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_DeclineSuperRod:: @ 822260C
	msgbox MossdeepCity_House3_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_Text_YouWantSuperRod: @ 8222616
	.string "이봐-! 거기 트레이너!\n"
	.string "대단한낚싯대는 정말로 대단하다고\p"
	.string "왜냐면 해저에 있는\n"
	.string "포켓몬도 낚아 올릴 수 있거든!\p"
	.string "어때? 갖고 싶어졌어?$"
	@ お-い! トレ-ナ-よお!ｎ
	@ すごいつりざおは ほんとうに すごいぞおｐ
	@ なんたって かいていに いるｎ
	@ ポケモンも つりあげられる からのお!ｐ
	@ どお? ほしく なった?

MossdeepCity_House3_Text_SuperRodIsSuper: @ 82226B6
	.string "그치 그치! 대단한낚싯대는\n"
	.string "정말로 대단하니까 말이다!$"
	@ そうだろ そうだろ! すごいつりざおはｎ
	@ ほんとうに すごい からのお!

MossdeepCity_House3_Text_TryDroppingRodInWater: @ 82226F0
	.string "물이 있는 곳이라면\n"
	.string "어디든 낚싯대를 써보도록 해!$"
	@ みずの ある ところならｎ
	@ どこでも つりざお つかうと いいぞお!

MossdeepCity_House3_Text_DontYouLikeToFish: @ 8222733
	.string "어라?\n"
	.string "낚시는 싫은 거야?$"
	@ あら?ｎ
	@ つりは きらい なのかね?

MossdeepCity_House3_Text_GoAfterSeafloorPokemon: @ 8222751
	.string "대단한낚싯대로\n"
	.string "해저의 포켓몬도 낚아 올려봐!$"
	@ すごいつりざおでｎ
	@ かいていの ポケモンも つりあげろお!

