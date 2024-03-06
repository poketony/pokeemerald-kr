.set LOCALID_NURSE, 1

OldaleTown_PokemonCenter_1F_MapScripts:: @ 81FC006
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

OldaleTown_PokemonCenter_1F_OnTransition: @ 81FC011
	setrespawn HEAL_LOCATION_OLDALE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

OldaleTown_PokemonCenter_1F_EventScript_Nurse:: @ 81FC01A
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_Gentleman:: @ 81FC028
	msgbox OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Boy:: @ 81FC031
	msgbox OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Girl:: @ 81FC03A
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEDEX_GET, OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable
	msgbox OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable:: @ 81FC04F
	msgbox OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC: @ 81FC059
	.string "구석에 있는 PC는\n"
	.string "포켓몬 트레이너를 위해 놔둔 거란다\p"
	.string "자네도 자유롭게 써도 된다고!$"
	@ すみっこに おいてある パソコンはｎ
	@ ポケモントレ-ナ-の ための ものなんだｐ
	@ きみも じゆうに つかって いいんだよ!

OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat: @ 81FC0CD
	.string "포켓몬센터는 정말 굉장해!\p"
	.string "포켓몬을 몇 마리 맡겨도\n"
	.string "돈이 들지 않으니까\l"
	.string "언제 어디서라도 안심할 수 있어!$"
	@ ポケモンセンタ-って すごいよな!ｐ
	@ ポケモン なんびき あずけてもｎ
	@ おかねが かからないからｌ
	@ どんな ときでも あんしん だよね!

OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable: @ 81FC148
	.string "2층의 포켓몬 무선 클럽은\n"
	.string "얼마 전에 생겼어\p"
	.string "하지만 아직\n"
	.string "조정 중인가 봐$"
	@ 2かいの ポケモン ワイヤレス クラブはｎ
	@ つい さいきん できたのｐ
	@ でも まだｎ
	@ ちょうせいちゅう ですって

OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub: @ 81FC1B9
	.string "2층의 포켓몬 무선 클럽은\n"
	.string "얼마 전에 생겼어\p"
	.string "그래서 바로\n"
	.string "포켓몬 교환을 했지!$"
	@ 2かいの ポケモン ワイヤレス クラブはｎ
	@ つい さいきん できたのｐ
	@ あたし さっそくｎ
	@ ポケモンこうかん しちゃった!

