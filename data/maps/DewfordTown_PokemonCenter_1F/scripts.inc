.set LOCALID_NURSE, 1

DewfordTown_PokemonCenter_1F_MapScripts:: @ 81FC523
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

DewfordTown_PokemonCenter_1F_OnTransition: @ 81FC52E
	setrespawn HEAL_LOCATION_DEWFORD_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

DewfordTown_PokemonCenter_1F_EventScript_Nurse:: @ 81FC537
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

DewfordTown_PokemonCenter_1F_EventScript_PokefanF:: @ 81FC545
	msgbox DewfordTown_PokemonCenter_1F_Text_StoneCavern, MSGBOX_NPC
	end

DewfordTown_PokemonCenter_1F_EventScript_Man:: @ 81FC54E
	msgbox DewfordTown_PokemonCenter_1F_Text_FaintedMonCanUseHM, MSGBOX_NPC
	end

DewfordTown_PokemonCenter_1F_Text_StoneCavern: @ 81FC557
	.string "마을에서 떨어진 곳에 있는\n"
	.string "바위 동굴에는\l"
	.string "희귀한 돌이 있다고 들었어$"

DewfordTown_PokemonCenter_1F_Text_FaintedMonCanUseHM: @ 81FC5AE
	.string "지쳐서 배틀을 할 수 없는\n"
	.string "포켓몬도 비전이라고 불리는\l"
	.string "기술은 쓸 수 있어!$"

