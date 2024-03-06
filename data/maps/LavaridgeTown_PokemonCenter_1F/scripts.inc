.set LOCALID_NURSE, 1

LavaridgeTown_PokemonCenter_1F_MapScripts:: @ 81FFAFA
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

LavaridgeTown_PokemonCenter_1F_OnTransition: @ 81FFB05
	setrespawn HEAL_LOCATION_LAVARIDGE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Nurse:: @ 81FFB0E
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Youngster:: @ 81FFB1C
	msgbox LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Woman:: @ 81FFB25
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Gentleman:: @ 81FFB2E
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether: @ 81FFB37
	.string "포켓몬이랑 같이 걷다 보면\n"
	.string "왠지 포켓몬이 더 잘 따르는 듯한\l"
	.string "느낌이 든단 말이지$"
	@ ポケモンと いっしょに あるいているとｎ
	@ なんだか ポケモンが なついてくれるようなｌ
	@ そんな きが するのよね

LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate: @ 81FFBAD
	.string "온천에 들어간 것만으로도\n"
	.string "건강해진다니 신기해-!\l"
	.string "포켓몬하고 같이 들어가고 싶어-$"
	@ おんせんに はいる だけでｎ
	@ げんきに なるなんて ふしぎだな-!ｌ
	@ ポケモンも いれて あげたいな-

LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo: @ 81FFC21
	.string "허허허! 젊구먼\n"
	.string "여기서 온천에 갈 수 있단다!\p"
	.string "포켓몬이 여기서 쉰다면\n"
	.string "사람도 온천에서 푹 쉬어야지!$"
	@ ほっほっほ! おわかいのｎ
	@ ここから おんせんに いけますぞ!ｐ
	@ ポケモンが ここで やすむのならｎ
	@ ひとも おんせんで ゆっくり しませんと!

