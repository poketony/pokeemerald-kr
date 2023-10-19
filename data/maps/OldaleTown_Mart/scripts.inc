OldaleTown_Mart_MapScripts:: @ 81FC23F
	.byte 0

OldaleTown_Mart_EventScript_Clerk:: @ 81FC240
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_ExpandedItems
	pokemart OldaleTown_Mart_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_Pokemart_Basic: @ 81FC260
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_NONE
	release
	end

OldaleTown_Mart_ExpandedItems:: @ 81FC26C
	pokemart OldaleTown_Mart_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
OldaleTown_Mart_Pokemart_Expanded: @ 81FC27C
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_NONE
	release
	end

OldaleTown_Mart_EventScript_Woman:: @ 81FC28A
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_EventScript_PokeBallsInStock
	msgbox OldaleTown_Mart_Text_PokeBallsAreSoldOut, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_PokeBallsInStock:: @ 81FC29F
	msgbox OldaleTown_Mart_Text_ImGoingToBuyPokeBalls, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_Boy:: @ 81FC2A9
	msgbox OldaleTown_Mart_Text_RestoreHPWithPotion, MSGBOX_NPC
	end

OldaleTown_Mart_Text_PokeBallsAreSoldOut: @ 81FC2B2
	.string "물건들이 다 팔려서\n"
	.string "몬스터볼을 살 수가 없어...$"
	// なんでも うりきれ らしくてｎ
	// モンスタ-ボ-ル かえないの……

OldaleTown_Mart_Text_ImGoingToBuyPokeBalls: @ 81FC2F3
	.string "엄청 몬스터볼을 많이 사서\n"
	.string "엄청 포켓몬을 많이 잡을 거야!$"
	// どんどん モンスタ-ボ-ル かってｎ
	// どんどん ポケモン つかまえちゃうわよ!

OldaleTown_Mart_Text_RestoreHPWithPotion: @ 81FC338
	.string "포켓몬은 체력이 약해지면\n"
	.string "싸울 힘도 없어져\p"
	.string "그럴 때는 상처약을 써서\n"
	.string "체력을 회복시켜줘야 돼!$"
	// ポケモンは たいりょくが なくなるとｎ
	// たたかう げんきも なくなるｐ
	// そんな ときは キズぐすりを つかってｎ
	// たいりょくを かいふく してあげるんだ!

