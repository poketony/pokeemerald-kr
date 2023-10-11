FortreeCity_DecorationShop_MapScripts:: @ 821800D
	.byte 0

FortreeCity_DecorationShop_EventScript_PokefanM:: @ 821800E
	msgbox FortreeCity_DecorationShop_Text_MerchandiseSentToPC, MSGBOX_NPC
	end

FortreeCity_DecorationShop_EventScript_Girl:: @ 8218017
	msgbox FortreeCity_DecorationShop_Text_BuyingDeskForDolls, MSGBOX_NPC
	end

FortreeCity_DecorationShop_EventScript_ClerkDesks:: @ 8218020
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration FortreeCity_DecorationShop_PokemartDecor_Desks
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

    .align 2
FortreeCity_DecorationShop_PokemartDecor_Desks: @ 8218038
	.2byte DECOR_SMALL_DESK
	.2byte DECOR_POKEMON_DESK
	.2byte DECOR_HEAVY_DESK
	.2byte DECOR_RAGGED_DESK
	.2byte DECOR_COMFORT_DESK
	.2byte DECOR_BRICK_DESK
	.2byte DECOR_CAMP_DESK
	.2byte DECOR_HARD_DESK
	.2byte DECOR_NONE
	release
	end

FortreeCity_DecorationShop_EventScript_ClerkChairs:: @ 821804C
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration FortreeCity_DecorationShop_PokemartDecor_Chairs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_DecorationShop_PokemartDecor_Chairs: @ 8218064
	.2byte DECOR_SMALL_CHAIR
	.2byte DECOR_POKEMON_CHAIR
	.2byte DECOR_HEAVY_CHAIR
	.2byte DECOR_RAGGED_CHAIR
	.2byte DECOR_COMFORT_CHAIR
	.2byte DECOR_BRICK_CHAIR
	.2byte DECOR_CAMP_CHAIR
	.2byte DECOR_HARD_CHAIR
	.2byte DECOR_NONE
	release
	end

FortreeCity_DecorationShop_Text_MerchandiseSentToPC: @ 8218078
	.string "여기서 산 물건은\n"
	.string "PC로 배달돼!\p"
	.string "정말 멋진 거 같아! 덤으로 나도\n"
	.string "집까지 배달해주면 안 되나$"
	// ここで かった ものはｎ
	// パソコンに とどけられる!ｐ
	// なんと すばらしい! ついでに わしもｎ
	// いえまで とどけて くれないものか

FortreeCity_DecorationShop_Text_BuyingDeskForDolls: @ 82180ED
	.string "멋진 책상을 사서 그 위에\n"
	.string "귀여운 인형을 놓을 거야!\p"
	.string "그러지 않으면 비밀기지에 놓을 때\n"
	.string "흙으로 더러워지거나 가시에 찔려서\l"
	.string "인형이 불쌍한걸!$"
	// すてきな つくえを かって そのうえにｎ
	// かわいい ぬいぐるみを ならべるんだ!ｐ
	// そうしないと ひみつきちに おくときｎ
	// つちで よごれたり トゲが ささってｌ
	// ぬいぐるみが かわいそう だもん!

