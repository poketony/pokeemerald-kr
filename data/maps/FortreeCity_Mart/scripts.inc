FortreeCity_Mart_MapScripts:: @ 8217665
	.byte 0

FortreeCity_Mart_EventScript_Clerk:: @ 8217666
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FortreeCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_Mart_Pokemart: @ 8217680
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_REVIVE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_WOOD_MAIL
	.2byte ITEM_NONE
	release
	end

FortreeCity_Mart_EventScript_Woman:: @ 8217698
	msgbox FortreeCity_Mart_Text_SuperRepelBetter, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Girl:: @ 82176A1
	msgbox FortreeCity_Mart_Text_StockUpOnItems, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Boy:: @ 82176AA
	msgbox FortreeCity_Mart_Text_RareCandyMakesMonGrow, MSGBOX_NPC
	end

FortreeCity_Mart_Text_SuperRepelBetter: @ 82176B3
	.string "실버스프레이는\n"
	.string "효과도 좋고 오래가!\p"
	.string "그러니까 벌레회피스프레이보다\n"
	.string "굉장하다는 거지!$"

FortreeCity_Mart_Text_StockUpOnItems: @ 8217715
	.string "언제 무슨 일이 일어날지 모르니까\n"
	.string "도구는 항상 많이 사두곤 해$"

FortreeCity_Mart_Text_RareCandyMakesMonGrow: @ 821778E
	.string "이상한사탕을 주면\n"
	.string "포켓몬이 단숨에 성장해서\l"
	.string "레벨이 올라가!$"

