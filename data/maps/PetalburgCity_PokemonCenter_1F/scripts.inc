.set LOCALID_NURSE, 1

PetalburgCity_PokemonCenter_1F_MapScripts:: @ 82079E8
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

PetalburgCity_PokemonCenter_1F_OnTransition: @ 82079F3
	setrespawn HEAL_LOCATION_PETALBURG_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

PetalburgCity_PokemonCenter_1F_EventScript_Nurse:: @ 82079FC
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_FatMan:: @ 8207A0A
	msgbox PetalburgCity_PokemonCenter_1F_Text_PCStorageSystem, MSGBOX_NPC
	end

PetalburgCity_PokemonCenter_1F_EventScript_Youngster:: @ 8207A13
	msgbox PetalburgCity_PokemonCenter_1F_Text_OranBerryRegainedHP, MSGBOX_NPC
	end

PetalburgCity_PokemonCenter_1F_EventScript_Woman:: @ 8207A1C
	lock
	faceplayer
	msgbox PetalburgCity_PokemonCenter_1F_Text_ManyTypesOfPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, IsStarterInParty
	compare VAR_RESULT, TRUE
	goto_if_eq PetalburgCity_PokemonCenter_1F_EventScript_SayStarterTypeInfo
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_SayStarterTypeInfo:: @ 8207A38
	compare VAR_STARTER_MON, 0
	call_if_eq PetalburgCity_PokemonCenter_1F_EventScript_SayTreeckoType
	compare VAR_STARTER_MON, 1
	call_if_eq PetalburgCity_PokemonCenter_1F_EventScript_SayTorchicType
	compare VAR_STARTER_MON, 2
	call_if_eq PetalburgCity_PokemonCenter_1F_EventScript_SayMudkipType
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_SayTreeckoType:: @ 8207A5B
	msgbox PetalburgCity_PokemonCenter_1F_Text_TreeckoIsGrassType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_EventScript_SayTorchicType:: @ 8207A64
	msgbox PetalburgCity_PokemonCenter_1F_Text_TorchicIsFireType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_EventScript_SayMudkipType:: @ 8207A6D
	msgbox PetalburgCity_PokemonCenter_1F_Text_MudkipIsWaterType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_Text_PCStorageSystem: @ 8207A76
	.string "PC를 이용한\n"
	.string "포켓몬 보관 시스템이라니...\p"
	.string "만든 녀석은\n"
	.string "엄청나게 과학에 빠삭할 거야!$"
	// パソコンで つかえるｎ
	// ポケモン あずかり システム……ｐ
	// つくった やつはｎ
	// すげ- かがくに くわしいんだろうな!

PetalburgCity_PokemonCenter_1F_Text_OranBerryRegainedHP: @ 8207AD6
	.string "포켓몬한테 오랭열매를 먹였더니\n"
	.string "체력을 회복했어!$"
	// ポケモンに オレンのみ を たべさせたらｎ
	// たいりょくが かいふく したんだぜ!

PetalburgCity_PokemonCenter_1F_Text_ManyTypesOfPokemon: @ 8207B09
	.string "포켓몬에겐\n"
	.string "다양한 타입이 있어!\p"
	.string "그리고 타입에는 상성이 있어서\n"
	.string "포켓몬 승부를 할 때\l"
	.string "유리할 때도 있고 불리할 때도 있지$"
	// ポケモンにはｎ
	// いろいろ タイプが あるの!ｐ
	// で タイプには あいしょうが あるからｎ
	// ポケモンしょうぶの ときｌ
	// ゆうり だったり ふり だったりするの

PetalburgCity_PokemonCenter_1F_Text_TreeckoIsGrassType: @ 8207BB0
	.string "예를 들면 너의 나무지기는\n"
	.string "풀타입이니까\p"
	.string "물타입이나 땅타입에 강하고\n"
	.string "불꽃타입에는 약해!$"
	// たとえば あなたの キモリはｎ
	// くさタイプ でしょｐ
	// みずタイプや じめんタイプに つよくてｎ
	// ほのおタイプが にがて なのよね!

PetalburgCity_PokemonCenter_1F_Text_TorchicIsFireType: @ 8207C35
	.string "예를 들면 너의 아차모는\n"
	.string "불꽃타입이니까\p"
	.string "풀타입이나 벌레타입에 강하고\n"
	.string "물타입에는 약해!$"
	// たとえば あなたのｎ
	// アチャモは ほのおタイプ でしょｐ
	// くさタイプや むしタイプに つよくてｎ
	// みずタイプが にがて なんだ!

PetalburgCity_PokemonCenter_1F_Text_MudkipIsWaterType: @ 8207CB7
	.string "예를 들면 너의 물짱이는\n"
	.string "물타입이니까\p"
	.string "불꽃타입에 강하고\n"
	.string "풀타입이나 전기타입에는 약해!$"
	// たとえば あなたのｎ
	// ミズゴロウは みずタイプ だよねｐ
	// ほのおタイプに つよくてｎ
	// くさタイプや でんきタイプが にがて ね!

