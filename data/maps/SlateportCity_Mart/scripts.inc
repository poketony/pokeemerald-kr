SlateportCity_Mart_MapScripts:: @ 820DC48
	.byte 0

SlateportCity_Mart_EventScript_Clerk:: @ 820DC49
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart SlateportCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_Mart_Pokemart: @ 820DC60
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_HARBOR_MAIL
	.2byte ITEM_NONE
	release
	end

SlateportCity_Mart_EventScript_BlackBelt:: @ 820DC76
	msgbox SlateportCity_Mart_Text_SomeItemsOnlyAtMart, MSGBOX_NPC
	end

SlateportCity_Mart_EventScript_Man:: @ 820DC7F
	msgbox SlateportCity_Mart_Text_GreatBallIsBetter, MSGBOX_NPC
	end

SlateportCity_Mart_Text_SomeItemsOnlyAtMart: @ 820DC88
	.string "물론 시장에서도 여러 가지\n"
	.string "진귀한 물건을 팔고 있지\p"
	.string "하지만 프렌들리숍이 아니면\n"
	.string "살 수 없는 물건도 있다$"

SlateportCity_Mart_Text_GreatBallIsBetter: @ 820DCF8
	.string "수퍼볼은 몬스터볼보다\n"
	.string "포켓몬을 잡기 쉽다!\p"
	.string "이제 그 엄청난 포켓몬도\n"
	.string "잘만 하면..$"

