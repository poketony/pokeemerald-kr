LilycoveCity_DepartmentStore_3F_MapScripts:: @ 821FC64
	.byte 0

LilycoveCity_DepartmentStore_3F_EventScript_ClerkLeft:: @ 821FC65
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_3F_Pokemart_Vitamins
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

LilycoveCity_DepartmentStore_3F_Pokemart_Vitamins: @ 821FC7C
	.2byte ITEM_PROTEIN
	.2byte ITEM_CALCIUM
	.2byte ITEM_IRON
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_HP_UP
	.2byte ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_3F_EventScript_ClerkRight:: @ 821FC8C
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_3F_Pokemart_StatBoosters
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_3F_Pokemart_StatBoosters: @ 821FCA4
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_3F_EventScript_TriathleteM:: @ 821FCB6
	msgbox LilycoveCity_DepartmentStore_3F_Text_ItemsBestForTougheningPokemon, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_3F_EventScript_PokefanM:: @ 821FCBF
	msgbox LilycoveCity_DepartmentStore_3F_Text_WantMoreEndurance, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_3F_EventScript_Woman:: @ 821FCC8
	msgbox LilycoveCity_DepartmentStore_3F_Text_GaveCarbosToSpeedUpMon, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_3F_Text_ItemsBestForTougheningPokemon: @ 821FCD1
	.string "쉽고 빠르게 포켓몬을 강하게 하려면\n"
	.string "도구를 사용하는 게 최고다!\p"
	.string "타우린은 공격이 오르고!\n"
	.string "리보플라빈은 특수공격이 올라간다고!$"
	// てっとりばやく ポケモンを つよくするならｎ
	// どうぐを あたえるのが いちばん!ｐ
	// タウリンなら こうげきりょく アップ!ｎ
	// リゾチウムなら とくこう アップ だぜ!

LilycoveCity_DepartmentStore_3F_Text_WantMoreEndurance: @ 821FD3B
	.string "튼튼한 포켓몬으로\n"
	.string "자라주었으면 하는데 말이지\p"
	.string "사포닌으로 방어력을 올릴지\n"
	.string "키토산으로 특수방어를 올릴지\l"
	.string "지금 막 고민하는 중이라네$"
	// じょうぶな ポケモンにｎ
	// なって ほしいからねｐ
	// ブロムヘキシンで ぼうぎょりょくを あげるかｎ
	// キトサンで とくぼうを あげるかｌ
	// いま かんがえている ところ なんだ

LilycoveCity_DepartmentStore_3F_Text_GaveCarbosToSpeedUpMon: @ 821FDB4
	.string "포켓몬한테\n"
	.string "알칼로이드를 사용했더니\l"
	.string "스피드가 빨라졌어!$"
	// ポケモンにねｎ
	// インドメタシンを あげたらｌ
	// すばやさが あがったの!

