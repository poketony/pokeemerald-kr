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
	.string "이봐-아! 거기 트레이너!\n"
	.string "대단한낚싯대는 진짜 대단하다고\p"
	.string "해저에 있는 포켓몬까지\n"
	.string "낚아 올릴 수 있으니까 말이다!\p"
	.string "어때? 갖고 싶나?$"

MossdeepCity_House3_Text_SuperRodIsSuper: @ 82226B6
	.string "암 그렇겠지 당연히 갖고 싶겠지!\n"
	.string "대단한낚싯대는 진짜\l"
	.string "대단하니까 말이다!$"

MossdeepCity_House3_Text_TryDroppingRodInWater: @ 82226F0
	.string "물이 있는 곳이라면 무조건\n"
	.string "낚싯대를 써보는 게 좋을 거다!$"

MossdeepCity_House3_Text_DontYouLikeToFish: @ 8222733
	.string "엉?\n"
	.string "낚시는 싫은감?$"

MossdeepCity_House3_Text_GoAfterSeafloorPokemon: @ 8222751
	.string "대단한낚싯대로\n"
	.string "해저에 있는 포켓몬을\l"
	.string "낚아 올려보라고!$"

