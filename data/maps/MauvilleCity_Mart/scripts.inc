MauvilleCity_Mart_MapScripts:: @ 82110E5
	.byte 0

MauvilleCity_Mart_EventScript_Clerk:: @ 82110E6
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MauvilleCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MauvilleCity_Mart_Pokemart: @ 8211100
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_NONE
	release
	end

MauvilleCity_Mart_EventScript_ExpertM:: @ 821111C
	msgbox MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats, MSGBOX_NPC
	end

MauvilleCity_Mart_EventScript_Man:: @ 8211125
	msgbox MauvilleCity_Mart_Text_DecisionsDetermineBattle, MSGBOX_NPC
	end

MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats: @ 821112E
	.string "포켓몬이 배틀하고 있을 때\n"
	.string "능력을 일시적으로\l"
	.string "올리는 도구가 있다네\p"
	.string "내가 알고 있는 건\n"
	.string "플러스파워\l"
	.string "디펜드업...\p"
	.string "분명 이것 말고도 더 있었는데...$"
	// ポケモンが たたかっているときｎ
	// のうりょくを いちじてきにｌ
	// たかめる どうぐが あるのじゃｐ
	// わしが しっているのはｎ
	// プラスパワ-ｌ
	// ディフェンダ-……ｐ
	// たしか ほかにも あったのう……

MauvilleCity_Mart_Text_DecisionsDetermineBattle: @ 82111D8
	.string "기술을 쓸 것인가\n"
	.string "아니면 도구를 사용할 것인가...\p"
	.string "트레이너의 판단으로\n"
	.string "승부가 결정되는 걸지도 모르지!$"
	// わざを くりだすのかｎ
	// それとも どうぐを つかうのか……ｐ
	// トレ-ナ-の はんだんでｎ
	// しょうぶが きまるのかも しれないな!

