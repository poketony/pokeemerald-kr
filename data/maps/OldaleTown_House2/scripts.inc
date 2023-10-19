OldaleTown_House2_MapScripts:: @ 81FBF5A
	.byte 0

OldaleTown_House2_EventScript_Woman:: @ 81FBF5B
	msgbox OldaleTown_House2_Text_PokemonLevelUp, MSGBOX_NPC
	end

OldaleTown_House2_EventScript_Man:: @ 81FBF64
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	end

OldaleTown_House2_Text_PokemonLevelUp: @ 81FBF6D
	.string "포켓몬은 배틀을 하면\n"
	.string "레벨 업해서 강해진단다!$"
	// ポケモンって たたかうとｎ
	// レベルアップして つよくなるのよ!

OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon: @ 81FBFB0
	.string "데리고 걷는 포켓몬이 강해지면\n"
	.string "먼 곳까지 갈 수 있게 될 거야!$"
	// つれて あるく ポケモンが つよかったらｎ
	// とおくまで いけるように なるね!

