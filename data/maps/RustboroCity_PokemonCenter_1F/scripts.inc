.set LOCALID_NURSE, 1

RustboroCity_PokemonCenter_1F_MapScripts:: @ 8214D62
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

RustboroCity_PokemonCenter_1F_OnTransition: @ 8214D6D
	setrespawn HEAL_LOCATION_RUSTBORO_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

RustboroCity_PokemonCenter_1F_EventScript_Nurse:: @ 8214D76
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

RustboroCity_PokemonCenter_1F_EventScript_Man:: @ 8214D84
	msgbox RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Boy:: @ 8214D8D
	msgbox RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Girl:: @ 8214D96
	msgbox RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities: @ 8214D9F
	.string "내 포켓몬은 천진난만하고\n"
	.string "내 친구의 포켓몬은 명랑하지\p"
	.string "포켓몬에게도 성격이 있다니\n"
	.string "참 재미있군-!$"
	@ わしの ポケモンは むじゃき でｎ
	@ ともだちの ポケモンは ようき なんだよｐ
	@ ポケモンにも せいかくが ある というのはｎ
	@ なかなか おもしろい もんだね-!

RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon: @ 8214E13
	.string "인간이랑 똑같이\n"
	.string "포켓몬도 수컷이랑 암컷이 있는데\l"
	.string "성별에 따라 뭐가 다른지는\l"
	.string "아직 아무것도 밝혀지지 않았대$"
	@ にんげんと おなじでｎ
	@ ポケモンにも オスと メスが いるんだけどｌ
	@ だから なにが ちがうのかはｌ
	@ さっぱり わかっていない らしいよ

RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor: @ 8214E81
	.string "옆집 아저씨가 준\n"
	.string "비전머신으로 내 포켓몬은\l"
	.string "얇은 나무를 자를 수 있게 됐어!$"
	@ となりの いえの おじさんが くれたｎ
	@ ひでんマシンで あたしの ポケモンｌ
	@ ほそい きを きることが できるんだ!

