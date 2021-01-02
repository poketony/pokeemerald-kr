RustboroCity_Flat1_1F_MapScripts:: @ 82150CD
	.byte 0

RustboroCity_Flat1_1F_EventScript_Man:: @ 82150CE
	msgbox RustboroCity_Flat1_1F_Text_EveryPokemonHasAbility, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_EventScript_Woman:: @ 82150D7
	msgbox RustboroCity_Flat1_1F_Text_PokemonStrange, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_Text_EveryPokemonHasAbility: @ 82150E0
	.string "포켓몬은 각각\n"
	.string "특성이라고 하는 신비한 힘을\l"
	.string "지니고 있지$"

RustboroCity_Flat1_1F_Text_PokemonStrange: @ 8215115
	.string "포켓몬은 정말\n"
	.string "신비한 생물이구나$"

