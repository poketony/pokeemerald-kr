.set LOCALID_NURSE, 1

SootopolisCity_PokemonCenter_1F_MapScripts:: @ 82264F1
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

SootopolisCity_PokemonCenter_1F_OnTransition: @ 82264FC
	setrespawn HEAL_LOCATION_SOOTOPOLIS_CITY
	end

SootopolisCity_PokemonCenter_1F_EventScript_Nurse:: @ 8226500
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

SootopolisCity_PokemonCenter_1F_EventScript_Gentleman:: @ 822650E
	lock
	faceplayer
	compare VAR_SKY_PILLAR_STATE, 2
	goto_if_ge SootopolisCity_PokemonCenter_1F_EventScript_GentlemanNoLegendaries
	goto_if_unset FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, SootopolisCity_PokemonCenter_1F_EventScript_GentlemanNoLegendaries
	msgbox SootopolisCity_PokemonCenter_1F_Text_EveryoneTakenRefuge, MSGBOX_DEFAULT
	release
	end

SootopolisCity_PokemonCenter_1F_EventScript_GentlemanNoLegendaries:: @ 822652E
	msgbox SootopolisCity_PokemonCenter_1F_Text_WallaceToughestInHoenn, MSGBOX_DEFAULT
	release
	end

SootopolisCity_PokemonCenter_1F_EventScript_Woman:: @ 8226538
	lock
	faceplayer
	compare VAR_SKY_PILLAR_STATE, 2
	goto_if_ge SootopolisCity_PokemonCenter_1F_EventScript_WomanNoLegendaries
	goto_if_unset FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, SootopolisCity_PokemonCenter_1F_EventScript_WomanNoLegendaries
	msgbox SootopolisCity_PokemonCenter_1F_Text_ArentPokemonOurFriends, MSGBOX_DEFAULT
	release
	end

SootopolisCity_PokemonCenter_1F_EventScript_WomanNoLegendaries:: @ 8226558
	msgbox SootopolisCity_PokemonCenter_1F_Text_AlwaysBeFriendsWithPokemon, MSGBOX_DEFAULT
	release
	end

SootopolisCity_PokemonCenter_1F_Text_WallaceToughestInHoenn: @ 8226562
	.string "이 마을의 체육관 관장은\n"
	.string "호연지방에서도 제일 강하다고\l"
	.string "여겨지는 실력자 윤진에게\p"
	.string "포켓몬 승부의 첫걸음을\n"
	.string "가르쳐 준 사람이죠\p"
	.string "하지만 그런 윤진의 스승보다\n"
	.string "더 강하다고 하는 사천왕...\l"
	.string "그 강함은 대체 어느 정도일지$"
	// この まちの ジムリ-ダ-はｎ
	// ホウエンちほう でも いちばんとｌ
	// うわさの じつりょくしゃ ミクリにｐ
	// ポケモン しょうぶの てほどきを したｎ
	// じんぶつが やっているのだｐ
	// しかし そんな ミクリの ししょうよりもｎ
	// つよいと いわれる してんのう……ｌ
	// その つよさは どれほどの ものだろう

SootopolisCity_PokemonCenter_1F_Text_EveryoneTakenRefuge: @ 822664B
	.string "이 마을에 사는 사람들이 모두\n"
	.string "집에 틀어박혀서 나오질 않아요!\p"
	.string "이렇게 말하는 저도\n"
	.string "여기서 나가고 싶진 않지만요...$"
	// この まちの みんなが みんなｎ
	// いえに とじこもって でてこないんです!ｐ
	// そう いってる わたしもｎ
	// ここから でたくないんです……

SootopolisCity_PokemonCenter_1F_Text_AlwaysBeFriendsWithPokemon: @ 82266B9
	.string "어떤 때라도\n"
	.string "무슨 일이 있더라도\l"
	.string "난 계속 포켓몬과 친구로 있을 거야\p"
	.string "왜냐면 포켓몬이랑 같이 있으면\n"
	.string "엄청 즐거우니까!$"
	// どんな ときでもｎ
	// どんな ことが あってもｌ
	// あたし ポケモンと ともだちで いるわｐ
	// だって ポケモンと いっしょだとｎ
	// すごく たのしいもの!

SootopolisCity_PokemonCenter_1F_Text_ArentPokemonOurFriends: @ 822672F
	.string "포켓몬은\n"
	.string "우리들의 친구... 인 거지?\p"
	.string "그런데 왜\n"
	.string "저렇게 날뛰고 있는 거야?$"
	// ポケモンってｎ
	// あたしたちの ともだちじゃ…… ないの?ｐ
	// どうしてｎ
	// あんなふうに あばれて いるの?

