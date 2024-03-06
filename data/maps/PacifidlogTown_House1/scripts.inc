PacifidlogTown_House1_MapScripts:: @ 820365C
	.byte 0

PacifidlogTown_House1_EventScript_Man:: @ 820365D
	msgbox PacifidlogTown_House1_Text_RegiStory, MSGBOX_NPC
	end

PacifidlogTown_House1_EventScript_Woman:: @ 8203666
	msgbox PacifidlogTown_House1_Text_SixDotsOpenThreeDoors, MSGBOX_NPC
	end

PacifidlogTown_House1_Text_RegiStory: @ 820366F
	.string "호연지방에는\n"
	.string "바위... 얼음... 강철...\p"
	.string "각각의 힘을 다스리는\n"
	.string "3마리의 포켓몬이\l"
	.string "각각 어딘가 동굴에 있다...\p"
	.string "나 어렸을 때\n"
	.string "그런 이야기를 들은 적이 있어$"
	@ ホウエンちほう にはｎ
	@ いわ…… こおり…… はがね……ｐ
	@ それぞれの ちからを つかさどるｎ
	@ 3びきの ポケモンがｌ
	@ それぞれ どこかの どうくつに いる……ｐ
	@ おれ ちいさな ころにｎ
	@ そんな はなしを きいたことが あるよ

PacifidlogTown_House1_Text_SixDotsOpenThreeDoors: @ 820373A
	.string "“6개의 점이\n"
	.string "  3개의 문을 연다”\p"
	.string "할아버지께서 자주 말씀하셨지만\n"
	.string "아직도 무슨 뜻인지 모르겠어$"
	@ 「むっつの てんがｎ
	@  みっつの とびらを あける」ｐ
	@ おじいちゃんが よく いっていたけどｎ
	@ いまだに なんのことだか わからないわ

