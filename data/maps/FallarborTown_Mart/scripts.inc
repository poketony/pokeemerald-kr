FallarborTown_Mart_MapScripts:: @ 81FFCBE
	.byte 0

FallarborTown_Mart_EventScript_Clerk:: @ 81FFCBF
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FallarborTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FallarborTown_Mart_Pokemart: @ 81FFCD8
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_NONE
	release
	end

FallarborTown_Mart_EventScript_Woman:: @ 81FFCF4
	msgbox FallarborTown_Mart_Text_DecidingSkittyEvolve, MSGBOX_NPC
	end

FallarborTown_Mart_EventScript_PokefanM:: @ 81FFCFD
	msgbox FallarborTown_Mart_Text_SellNuggetIFound, MSGBOX_NPC
	end

FallarborTown_Mart_EventScript_Skitty:: @ 81FFD06
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, 0
	msgbox FallarborTown_Mart_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_Mart_Text_DecidingSkittyEvolve: @ 81FFD19
	.string "내 에나비한테\n"
	.string "달의돌을 써서...\p"
	.string "진화시킬지 말지\n"
	.string "엄청 고민하고 있어\p"
	.string "진화시키면 강해지지만\n"
	.string "모습이 달라져 버리잖아...$"

FallarborTown_Mart_Text_Skitty: @ 81FFDFA
	.string "에나비: 냐-오?$"

FallarborTown_Mart_Text_SellNuggetIFound: @ 81FFE09
	.string "금구슬을 주웠는데...\n"
	.string "역시 팔아야겠지...?\l"
	.string "달리 쓸 데도 없으니까...$"

