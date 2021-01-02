.set LOCALID_NURSE, 1

LilycoveCity_PokemonCenter_1F_MapScripts:: @ 821C5B2
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

LilycoveCity_PokemonCenter_1F_OnTransition: @ 821C5BD
	setrespawn HEAL_LOCATION_LILYCOVE_CITY
	goto LilycoveCity_PokemonCenter_1F_EventScript_SetLilycoveLadyGfx
	end

@ SetLilycoveLadyGfx returns TRUE if its the Contest Lady
LilycoveCity_PokemonCenter_1F_EventScript_SetLilycoveLadyGfx:: @ 821C5C6
	special SetLilycoveLadyGfx
	compare VAR_RESULT, FALSE
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_HideContestLadyMon
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_ShowContestLadyMon
	end

LilycoveCity_PokemonCenter_1F_EventScript_HideContestLadyMon:: @ 821C5E0
	setflag FLAG_HIDE_LILYCOVE_POKEMON_CENTER_CONTEST_LADY_MON
	end

LilycoveCity_PokemonCenter_1F_EventScript_ShowContestLadyMon:: @ 821C5E4
	clearflag FLAG_HIDE_LILYCOVE_POKEMON_CENTER_CONTEST_LADY_MON
	end

LilycoveCity_PokemonCenter_1F_EventScript_Nurse:: @ 821C5E8
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_Boy:: @ 821C5F6
	msgbox LilycoveCity_PokemonCenter_1F_Text_HowManyKindsOfPokemon, MSGBOX_NPC
	end

LilycoveCity_PokemonCenter_1F_EventScript_Maniac:: @ 821C5FF
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_PokemonCenter_1F_EventScript_ManiacBadTeamGone
	msgbox LilycoveCity_PokemonCenter_1F_Text_HeardAboutRottenScoundrels, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_ManiacBadTeamGone:: @ 821C614
	msgbox LilycoveCity_PokemonCenter_1F_Text_HaventSeenRottenScoundrels, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_Text_HowManyKindsOfPokemon: @ 821C61E
	.string "이 세상에는\n"
	.string "포켓몬이 과연 얼마나 있는 걸까?\p"
	.string "언젠가 바다를 넘어서\n"
	.string "먼 나라 사람과\l"
	.string "포켓몬 교환하고 싶다!$"

LilycoveCity_PokemonCenter_1F_Text_HeardAboutRottenScoundrels: @ 821C69D
	.string "최근 사람들의 포켓몬을 뺏거나\n"
	.string "운석을 훔치거나 하는\l"
	.string "골치 아픈 놈들이 있다고 하더라고!$"

LilycoveCity_PokemonCenter_1F_Text_HaventSeenRottenScoundrels: @ 821C6F6
	.string "사람들의 포켓몬을 뺏거나\n"
	.string "운석을 훔치거나 했던\l"
	.string "골치 아픈 놈들...\p"
	.string "요즘 안 보이더라$"

