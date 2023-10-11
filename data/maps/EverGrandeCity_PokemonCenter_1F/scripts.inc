.set LOCALID_NURSE, 1
.set LOCALID_SCOTT, 4

EverGrandeCity_PokemonCenter_1F_MapScripts:: @ 8229A34
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

EverGrandeCity_PokemonCenter_1F_OnTransition: @ 8229A3F
	setrespawn HEAL_LOCATION_EVER_GRANDE_CITY
	call_if_unset FLAG_MET_SCOTT_IN_EVERGRANDE, EverGrandeCity_PokemonCenter_1F_EventScript_TryShowScott
	end

EverGrandeCity_PokemonCenter_1F_EventScript_TryShowScott:: @ 8229A4C
	goto_if_unset FLAG_BADGE06_GET, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_EVER_GRANDE_POKEMON_CENTER_1F_SCOTT
	return

EverGrandeCity_PokemonCenter_1F_EventScript_Nurse:: @ 8229A59
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

EverGrandeCity_PokemonCenter_1F_EventScript_Woman:: @ 8229A67
	msgbox EverGrandeCity_PokemonCenter_1F_Text_LeagueAfterVictoryRoad, MSGBOX_NPC
	end

EverGrandeCity_PokemonCenter_1F_EventScript_ExpertM:: @ 8229A70
	msgbox EverGrandeCity_PokemonCenter_1F_Text_BelieveInYourPokemon, MSGBOX_NPC
	end

EverGrandeCity_PokemonCenter_1F_EventScript_Scott:: @ 8229A79
	lock
	faceplayer
	msgbox EverGrandeCity_PokemonCenter_1F_Text_ScottHappyForYou, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_NORTH
	call_if_eq EverGrandeCity_PokemonCenter_1F_EventScript_ScottExitNorth
	compare VAR_FACING, DIR_EAST
	call_if_eq EverGrandeCity_PokemonCenter_1F_EventScript_ScottExit
	compare VAR_FACING, DIR_WEST
	call_if_eq EverGrandeCity_PokemonCenter_1F_EventScript_ScottExit
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_IN_EVERGRANDE
	playse SE_EXIT
	waitse
	removeobject LOCALID_SCOTT
	release
	end

EverGrandeCity_PokemonCenter_1F_EventScript_ScottExitNorth:: @ 8229AB6
	applymovement LOCALID_SCOTT, EverGrandeCity_PokemonCenter_1F_Movement_ScottExitNorth
	waitmovement 0
	return

EverGrandeCity_PokemonCenter_1F_EventScript_ScottExit:: @ 8229AC1
	applymovement LOCALID_SCOTT, EverGrandeCity_PokemonCenter_1F_Movement_ScottExit
	waitmovement 0
	return

EverGrandeCity_PokemonCenter_1F_Movement_ScottExitNorth: @ 8229ACC
	walk_left
	walk_down
	walk_down
	walk_left
	walk_down
	walk_down
	step_end

EverGrandeCity_PokemonCenter_1F_Movement_ScottExit: @ 8229AD3
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

EverGrandeCity_PokemonCenter_1F_Text_LeagueAfterVictoryRoad: @ 8229ADA
	.string "포켓몬리그는\n"
	.string "챔피언로드를 빠져나가면 바로 눈앞이야!\p"
	.string "여기까지 왔으면\n"
	.string "앞으로 나아가는 수밖에 없어!$"
	// ポケモンリ-グはｎ
	// チャンピオンロ-ドを ぬけると すぐ!ｐ
	// ここまで きたらｎ
	// まえに すすむしかないわ!

EverGrandeCity_PokemonCenter_1F_Text_BelieveInYourPokemon: @ 8229B62
	.string "챔피언로드의\n"
	.string "멀고 험한 길...\p"
	.string "마치 지금까지 걸어온 여정을\n"
	.string "다시 떠올리게 하는군\p"
	.string "너도 자신의 포켓몬을\n"
	.string "믿고 최선을 다하도록!$"
	// チャンピオンロ-ドのｎ
	// ながくて けわしい みちのり……ｐ
	// まるで いままで あるいてきた みちをｎ
	// おもいださせるかの ようだなｐ
	// きみ じぶんの ポケモンをｎ
	// しんじて がんばりたまえ!

EverGrandeCity_PokemonCenter_1F_Text_ScottHappyForYou: @ 8229BF1
	.string "금작화: {PLAYER}\n"
	.string "드디어 포켓몬리그구나!\l"
	.string "나도 응원해 온 보람이 있었어!\p"
	.string "만약 {PLAYER}{K_IGA}\n"
	.string "포켓몬 챔피언이 된다면...\l"
	.string "그때는 다시 연락할게\p"
	.string "그럼...\n"
	.string "힘내 {PLAYER}{K_AYA}!$"
	// エニシダ『§あ§おｎ
	// ついに ポケモンリ-グだね!ｌ
	// わたしも おうえん した かいがあったよ!ｐ
	// もし §あ§おがｎ
	// ポケモンチャンピオンに なったら……ｌ
	// そのときは また れんらく するからねｐ
	// じゃ……ｎ
	// §あ§お がんばってね!

