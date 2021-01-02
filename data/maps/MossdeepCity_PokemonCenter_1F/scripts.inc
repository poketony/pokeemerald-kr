.set LOCALID_NURSE, 1

MossdeepCity_PokemonCenter_1F_MapScripts:: @ 822223F
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

MossdeepCity_PokemonCenter_1F_OnTransition: @ 822224A
	setrespawn HEAL_LOCATION_MOSSDEEP_CITY
	end

MossdeepCity_PokemonCenter_1F_EventScript_Nurse:: @ 822224E
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

MossdeepCity_PokemonCenter_1F_EventScript_Woman:: @ 822225C
	msgbox MossdeepCity_PokemonCenter_1F_Text_GymLeaderDuoFormidable, MSGBOX_NPC
	end

MossdeepCity_PokemonCenter_1F_EventScript_Girl:: @ 8222265
	msgbox MossdeepCity_PokemonCenter_1F_Text_AbilitiesMightChangeMoves, MSGBOX_NPC
	end

MossdeepCity_PokemonCenter_1F_Text_GymLeaderDuoFormidable: @ 822226E
	.string "이 마을의 체육관 관장\n"
	.string "다른 걸 떠나서\l"
	.string "일단 그 콤비네이션은\p"
	.string "정말 최고야!\n"
	.string "아무도 따라갈 수가 없어$"

MossdeepCity_PokemonCenter_1F_Text_AbilitiesMightChangeMoves: @ 82222D9
	.string "포켓몬의 특성에 의해서\n"
	.string "기술의 위력이 바뀌거나\l"
	.string "효과가 없거나 해!$"

