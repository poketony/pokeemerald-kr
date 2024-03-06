LavaridgeTown_Mart_MapScripts:: @ 81FF9CD
	.byte 0

LavaridgeTown_Mart_EventScript_Clerk:: @ 81FF9CE
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LavaridgeTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LavaridgeTown_Mart_Pokemart: @ 81FF9E8
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_NONE
	release
	end

LavaridgeTown_Mart_EventScript_ExpertM:: @ 81FF9FE
	msgbox LavaridgeTown_Mart_Text_XSpeedFirstStrike, MSGBOX_NPC
	end

LavaridgeTown_Mart_EventScript_OldWoman:: @ 81FFA07
	msgbox LavaridgeTown_Mart_Text_LocalSpecialtyOnMtChimney, MSGBOX_NPC
	end

LavaridgeTown_Mart_Text_XSpeedFirstStrike: @ 81FFA10
	.string "스피드업을 사용해서\n"
	.string "포켓몬의 스피드를 올리는 게야!\p"
	.string "그러면 선제공격할 수 있어서\n"
	.string "배틀에서 유리해지거든!$"
	@ スピ-ダ- つかってｎ
	@ ポケモンの すばやさ あげるんじゃ!ｐ
	@ そうすりゃ せんせいこうげき できてｎ
	@ たたかいが ゆうりに なるからのう!

LavaridgeTown_Mart_Text_LocalSpecialtyOnMtChimney: @ 81FFA83
	.string "굴뚝산의 정상에서만\n"
	.string "살 수 있는 명물 과자는\l"
	.string "포켓몬에게 주면 아주 좋아한단다!$"
	@ えんとつやまの ちょうじょう だけでｎ
	@ かうことが できる おみやげはｌ
	@ ポケモンに あげると よろこぶよ!

