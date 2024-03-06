LavaridgeTown_HerbShop_MapScripts:: @ 81FE4D6
	.byte 0

LavaridgeTown_HerbShop_EventScript_Clerk:: @ 81FE4D7
	lock
	faceplayer
	message LavaridgeTown_HerbShop_Text_WelcomeToHerbShop
	waitmessage
	pokemart LavaridgeTown_HerbShop_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LavaridgeTown_HerbShop_Pokemart: @ 81FE4F0
	.2byte ITEM_ENERGY_POWDER
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_HEAL_POWDER
	.2byte ITEM_REVIVAL_HERB
	.2byte ITEM_NONE
	release
	end

LavaridgeTown_HerbShop_EventScript_ExpertM:: @ 81FE4FC
	msgbox LavaridgeTown_HerbShop_Text_HerbalMedicineWorksButMonWillDislike, MSGBOX_NPC
	end

LavaridgeTown_HerbShop_EventScript_OldMan:: @ 81FE505
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CHARCOAL, LavaridgeTown_HerbShop_EventScript_ExplainCharcoal
	msgbox LavaridgeTown_HerbShop_Text_YouveComeToLookAtHerbalMedicine, MSGBOX_DEFAULT
	giveitem ITEM_CHARCOAL
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CHARCOAL
	release
	end

LavaridgeTown_HerbShop_EventScript_ExplainCharcoal:: @ 81FE534
	msgbox LavaridgeTown_HerbShop_Text_ExplainCharcoal, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_HerbShop_Text_WelcomeToHerbShop: @ 81FE53E
	.string "어서 오세요!\n"
	.string "싸고 효과 좋은 한방약국입니다$"
	@ どうも!ｎ
	@ やすくて よく きく かんぽうや です

LavaridgeTown_HerbShop_Text_YouveComeToLookAtHerbalMedicine: @ 81FE584
	.string "용암마을의 한약을\n"
	.string "보러 오다니 뭘 좀 아는구먼\p"
	.string "마음에 들었네! 이걸 가져가게나!$"
	@ フエンの かんぽうやくをｎ
	@ みにくるとは なかなか しぶいのうｐ
	@ きにいった! これを もってけ!

LavaridgeTown_HerbShop_Text_ExplainCharcoal: @ 81FE5EB
	.string "자네에게 준 목탄은\n"
	.string "한약을 만들 때 쓰는 물건이지만\l"
	.string "포켓몬에게 지니게 해도 굉장하지!\p"
	.string "불꽃타입 기술의 위력을\n"
	.string "높여 주거든!$"
	@ おまえさんに あげた もくたんはｎ
	@ かんぽうやくを つくるのに つかうがｌ
	@ ポケモンに もたせても すごいぞ!ｐ
	@ ほのおタイプの わざの いりょくをｎ
	@ たかめて くれるのじゃよ!

LavaridgeTown_HerbShop_Text_HerbalMedicineWorksButMonWillDislike: @ 81FE685
	.string "한약의 효과는 엄청나지만\n"
	.string "포켓몬에게 마시게 하면 미움받는다네\l"
	.string "분명 엄청 써서 그런 것일 테지!$"
	@ かんぽうやくの ききめは すごいがｎ
	@ ポケモンに のませると きらわれるぞよｌ
	@ きっと すっごく にがいんじゃろうな!

