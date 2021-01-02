.set LOCALID_NURSE, 1

PacifidlogTown_PokemonCenter_1F_MapScripts:: @ 82034A7
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

PacifidlogTown_PokemonCenter_1F_OnTransition: @ 82034B2
	setrespawn HEAL_LOCATION_PACIFIDLOG_TOWN
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Nurse:: @ 82034B6
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Girl:: @ 82034C4
	msgbox PacifidlogTown_PokemonCenter_1F_Text_WhatColorTrainerCard, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Woman:: @ 82034CD
	msgbox PacifidlogTown_PokemonCenter_1F_Text_OnColonyOfCorsola, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_EventScript_OldMan:: @ 82034D6
	msgbox PacifidlogTown_PokemonCenter_1F_Text_AncestorsLivedOnBoats, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_Text_WhatColorTrainerCard: @ 82034DF
	.string "너의 트레이너카드는 무슨 색이야?\n"
	.string "나는 코퍼야!$"

PacifidlogTown_PokemonCenter_1F_Text_OnColonyOfCorsola: @ 820350F
	.string "황금마을은 코산호들이\n"
	.string "모여 있는 곳 위에 떠 있어\p"
	.string "...라고 말하면\n"
	.string "넌 믿을래?$"

PacifidlogTown_PokemonCenter_1F_Text_AncestorsLivedOnBoats: @ 820356F
	.string "황금마을 사람들의 선조는\n"
	.string "배 위에서 태어나\l"
	.string "배 위에서 죽었다고 하지\p"
	.string "뭔가를 찾기 위해\n"
	.string "그런 삶을 살았다는 모양이야$"

