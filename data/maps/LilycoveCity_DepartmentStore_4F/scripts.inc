LilycoveCity_DepartmentStore_4F_MapScripts:: @ 821FDEA
	.byte 0

LilycoveCity_DepartmentStore_4F_EventScript_Gentleman:: @ 821FDEB
	msgbox LilycoveCity_DepartmentStore_4F_Text_AttackOrDefenseTM, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_4F_EventScript_Woman:: @ 821FDF4
	msgbox LilycoveCity_DepartmentStore_4F_Text_FiftyDifferentTMs, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_4F_EventScript_Youngster:: @ 821FDFD
	msgbox LilycoveCity_DepartmentStore_4F_Text_PokemonOnlyHaveFourMoves, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_4F_EventScript_ClerkLeft:: @ 821FE06
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_4F_Pokemart_AttackTMs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_4F_Pokemart_AttackTMs: @ 821FE20
	.2byte ITEM_TM38  @ Fire Blast
	.2byte ITEM_TM25  @ Thunder
	.2byte ITEM_TM14  @ Blizzard
	.2byte ITEM_TM15  @ Hyper Beam
	.2byte ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_4F_EventScript_ClerkRight:: @ 821FE2C
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_4F_Pokemart_DefenseTMs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_4F_Pokemart_DefenseTMs: @ 821FE44
	.2byte ITEM_TM17  @ Protect
	.2byte ITEM_TM20  @ Safeguard
	.2byte ITEM_TM33  @ Reflect
	.2byte ITEM_TM16  @ Light Screen
	.2byte ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_4F_Text_AttackOrDefenseTM: @ 821FE50
	.string "음...\p"
	.string "공격의 기술인가...\n"
	.string "방어의 기술인가...\p"
	.string "어떤 기술머신을\n"
	.string "포켓몬에게 배우게 할지 고민되는군...$"
	// むむ……ｐ
	// こうげきの わざ か……ｎ
	// まもりの わざ か……ｐ
	// どの わざマシンをｎ
	// ポケモンに おぼえさせるか なやむ……

LilycoveCity_DepartmentStore_4F_Text_FiftyDifferentTMs: @ 821FEC7
	.string "기술머신이 잔뜩 있구나!\p"
	.string "무언가의 카탈로그에는\n"
	.string "전부 50종류라고\l"
	.string "적혀 있었어$"
	// わざマシンって たくさん あるのね!ｐ
	// なにかの カタログにはｎ
	// ぜんぶで 50しゅるい ってｌ
	// かいて あったわ

LilycoveCity_DepartmentStore_4F_Text_PokemonOnlyHaveFourMoves: @ 821FF2D
	.string "기술머신 전부 가지고 싶은데\n"
	.string "포켓몬이 4개밖에 기술을 못 배워$"
	// わざマシン ぜんぶ ほしいけどｎ
	// ポケモン 4つしか わざ おぼえないもんな

