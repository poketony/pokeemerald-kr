PetalburgCity_Mart_MapScripts:: @ 8207D68
	.byte 0

PetalburgCity_Mart_EventScript_Clerk:: @ 8207D69
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_PETALBURG_MART_EXPANDED_ITEMS, PetalburgCity_Mart_EventScript_ExpandedItems
	pokemart PetalburgCity_Mart_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_Basic: @ 8207D8C
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_ORANGE_MAIL
	.2byte ITEM_NONE
	release
	end

PetalburgCity_Mart_EventScript_ExpandedItems:: @ 8207DA6
	pokemart PetalburgCity_Mart_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_Expanded: @ 8207DB8
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_ORANGE_MAIL
	.2byte ITEM_NONE
	release
	end

PetalburgCity_Mart_EventScript_Woman:: @ 8207DD6
	msgbox PetalburgCity_Mart_Text_WeakWillGrowStronger, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_Boy:: @ 8207DDF
	msgbox PetalburgCity_Mart_Text_RepelIsUseful, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_Man:: @ 8207DE8
	msgbox PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou, MSGBOX_NPC
	end

PetalburgCity_Mart_Text_WeakWillGrowStronger: @ 8207DF1
	.string "지금은 약한 포켓몬이라도\n"
	.string "잘 키워주면 분명 강해지겠지!\p"
	.string "중요한 건\n"
	.string "포켓몬을 향한 애정이야!$"
	// いまは よわい ポケモンでもｎ
	// そだててあげれば きっと つよくなる!ｐ
	// だいじ なのはｎ
	// ポケモンへの あいじょうよ!

PetalburgCity_Mart_Text_RepelIsUseful: @ 8207E60
	.string "벌레회피스프레이는 쓰고 있니?\n"
	.string "그걸 쓰면 포켓몬이 나타나지 않아서\l"
	.string "서둘러야 할 때 편리하다고!$"
	// むしよけスプレ- つかってる?ｎ
	// つかうと ポケモンが よってこないからｌ
	// いそぐとき べんり なんだぜ!

PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou: @ 8207EB0
	.string "자네 해독제는 가지고 있나?\p"
	.string "포켓몬은 독에 걸린 채로\n"
	.string "걸어다니고 있으면 체력이 줄어들어서\l"
	.string "쓰러져버리니까 가지고 있으면 좋겠지!$"
	// きみ どくけし もってるかい?ｐ
	// ポケモン どくを くらったままｎ
	// あるいていると たいりょく なくなってｌ
	// たおれちゃうから もっておくと いいよ!

