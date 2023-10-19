PacifidlogTown_House4_MapScripts:: @ 8203F4B
	.byte 0

PacifidlogTown_House4_EventScript_LittleGirl:: @ 8203F4C
	msgbox PacifidlogTown_House4_Text_SkyPokemon, MSGBOX_NPC
	end

PacifidlogTown_House4_EventScript_Woman:: @ 8203F55
	msgbox PacifidlogTown_House4_Text_PeopleSawHighFlyingPokemon, MSGBOX_NPC
	end

PacifidlogTown_House4_EventScript_Boy:: @ 8203F5E
	lock
	faceplayer
	msgbox PacifidlogTown_House4_Text_WhereDidYouComeFrom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PacifidlogTown_House4_EventScript_Yes
	compare VAR_RESULT, NO
	goto_if_eq PacifidlogTown_House4_EventScript_No
	end

PacifidlogTown_House4_EventScript_Yes:: @ 8203F7F
	msgbox PacifidlogTown_House4_Text_YesTown, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House4_EventScript_No:: @ 8203F89
	msgbox PacifidlogTown_House4_Text_YouHaveToComeFromSomewhere, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House4_Text_PeopleSawHighFlyingPokemon: @ 8203F93
	.string "호연의 하늘 높은 곳을 날아가는\n"
	.string "포켓몬을 봤어! 라고 하는 사람이 있는데\p"
	.string "계속 날아다니고 있는 걸까?\n"
	.string "어딘가에서 쉬기도 할 것 같은데$"
	// ホウエンの そらたかくを とんでいくｎ
	// ポケモンを みた! って ひとが いるけどｐ
	// ずっと とびまわって いるのかしら?ｎ
	// どこかで やすんだり しそうだけど

PacifidlogTown_House4_Text_SkyPokemon: @ 8204017
	.string "하늘의 포켓몬!\n"
	.string "하늘의 포켓몬!$"
	// おそらの ポケモン!ｎ
	// おそらの ポケモン!

PacifidlogTown_House4_Text_WhereDidYouComeFrom: @ 8204035
	.string "넌 어디서 왔니?$"
	// きみ どこから きたの?

PacifidlogTown_House4_Text_YesTown: @ 820404E
	.string "예...?\n"
	.string "예... 마을...?\p"
	.string "몰라 그런 마을은$"
	// はい……?ｎ
	// ハイ… タウン……?ｐ
	// しらないなぁ そんな まち

PacifidlogTown_House4_Text_YouHaveToComeFromSomewhere: @ 8204084
	.string "아니요라니...\n"
	.string "어디서든 왔을 거 아니야\p"
	.string "서 설마 너...\n"
	.string "바닷속에서 태어나기라도 한 거야...?$"
	// いいえ って そんな……ｎ
	// どこからも きてない はずが ないでしょｐ
	// ま まさか きみ……ｎ
	// うみの そこで うまれた とか……?

