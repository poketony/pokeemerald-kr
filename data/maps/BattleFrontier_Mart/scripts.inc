.set LOCALID_OLD_WOMAN, 2

BattleFrontier_Mart_MapScripts:: @ 8267ACB
	.byte 0

BattleFrontier_Mart_EventScript_Clerk:: @ 8267ACC
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart BattleFrontier_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
BattleFrontier_Mart_Pokemart: @ 8267AE4
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_PROTEIN
	.2byte ITEM_CALCIUM
	.2byte ITEM_IRON
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_HP_UP
	.2byte ITEM_NONE
	release
	end

BattleFrontier_Mart_EventScript_OldMan:: @ 8267B02
	msgbox BattleFrontier_Mart_Text_ChaperonGrandson, MSGBOX_NPC
	end

BattleFrontier_Mart_EventScript_OldWoman:: @ 8267B0B
	lock
	applymovement LOCALID_OLD_WOMAN, Common_Movement_FaceDown
	waitmovement 0
	msgbox BattleFrontier_Mart_Text_ProteinMakeNiceGift, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Mart_EventScript_Boy:: @ 8267B20
	msgbox BattleFrontier_Mart_Text_FacilitiesDontAllowItems, MSGBOX_NPC
	end

BattleFrontier_Mart_Text_ChaperonGrandson: @ 8267B29
	.string "우리는 손자를 도와주러\n"
	.string "여기에 왔는데\p"
	.string "모처럼이니까 기념품으로\n"
	.string "뭘 사러 왔단다$"
	// わたしらは マゴの つきそいでｎ
	// ここに きたんだがｌ
	// せっかく だから きねんにｌ
	// なにか おみやげをと おもってな

BattleFrontier_Mart_Text_ProteinMakeNiceGift: @ 8267B8F
	.string "저기 할아범\n"
	.string "이거라면 좋을 거 같지 않수?\p"
	.string "타... 우... 타우...린이라는 게\n"
	.string "왠지 맛있어 보이는구먼$"
	// ネエ じいさんｎ
	// これなんか いいんじゃ ないかねえ?ｌ
	// た… う… タウリ……ソ って いうやつｐ
	// なんだか おいしそうよ

BattleFrontier_Mart_Text_FacilitiesDontAllowItems: @ 8267C01
	.string "배틀프런티어의 시설에서는\n"
	.string "전투 중에 도구를 쓸 수 없다는\l"
	.string "규칙이 있는 곳이 많지\l"
	.string "힘들어 정말-$"
	// バトルフロンティアの しせつではｎ
	// せんとうちゅうに どうぐが つかえないｌ
	// ル-ルの ところが おおいんだよねｌ
	// きびしいな-

