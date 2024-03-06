MossdeepCity_House4_MapScripts:: @ 8222DD7
	.byte 0

MossdeepCity_House4_EventScript_Woman:: @ 8222DD8
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_House4_EventScript_CanBattleAtSecretBases
	msgbox MossdeepCity_House4_Text_BrotherLikesToFindBases, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_CanBattleAtSecretBases:: @ 8222DED
	msgbox MossdeepCity_House4_Text_BrotherLikesToVisitBasesAndBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_NinjaBoy:: @ 8222DF7
	lock
	faceplayer
	special CheckPlayerHasSecretBase
	compare VAR_RESULT, FALSE
	goto_if_eq MossdeepCity_House4_EventScript_NoSecretBase
	special GetSecretBaseNearbyMapName
	msgbox MossdeepCity_House4_Text_YouMadeSecretBaseNearX, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_NoSecretBase:: @ 8222E14
	msgbox MossdeepCity_House4_Text_MakeSecretBase, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_Skitty:: @ 8222E1E
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, 0
	msgbox MossdeepCity_House4_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

MossdeepCity_House4_Text_BrotherLikesToFindBases: @ 8222E31
	.string "동생 말이야\n"
	.string "사람들의 비밀기지를 찾는 게\l"
	.string "즐겁대!$"
	@ おとうと ったらｎ
	@ ひとの ひみつきちを さがすのがｌ
	@ たのしみ なんだって!

MossdeepCity_House4_Text_BrotherLikesToVisitBasesAndBattle: @ 8222E73
	.string "동생 말이야\n"
	.string "친구들의 비밀기지에 가서\l"
	.string "포켓몬 승부를 하는 게\l"
	.string "즐겁대!$"
	@ おとうと ったらｎ
	@ ともだちの ひみつきちに いってｌ
	@ ポケモンしょうぶを するのがｌ
	@ たのしみ なんだって!

MossdeepCity_House4_Text_YouMadeSecretBaseNearX: @ 8222ECC
	.string "혹시 {STR_VAR_1}에\n"
	.string "비밀기지를 만든 사람이 너야?$"
	@ ひょっとして §い にｎ
	@ ひみつきち つくったの きみ?

MossdeepCity_House4_Text_MakeSecretBase: @ 8222EF7
	.string "너 어딘가에 비밀기지를 만들어 봐!\n"
	.string "내가 찾아내 줄 테니까 말야$"
	@ きみ どこかに ひみつきち つくりなよ!ｎ
	@ ぼくが さがしだして みせるからさ

MossdeepCity_House4_Text_Skitty: @ 8222F31
	.string "델케티: 미양?$"
	@ エネコ『みゃあん?

