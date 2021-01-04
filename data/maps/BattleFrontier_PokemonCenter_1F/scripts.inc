.set LOCALID_NURSE, 1

BattleFrontier_PokemonCenter_1F_MapScripts:: @ 82678F9
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

BattleFrontier_PokemonCenter_1F_OnTransition: @ 8267904
	setrespawn HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST
	end

BattleFrontier_PokemonCenter_1F_EventScript_Nurse:: @ 8267908
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_PokemonCenter_1F_EventScript_SchoolKid:: @ 8267916
	msgbox BattleFrontier_PokemonCenter_1F_Text_NeverSeenPokemon, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Man:: @ 826791F
	msgbox BattleFrontier_PokemonCenter_1F_Text_NextStopBattleArena, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Picnicker:: @ 8267928
	msgbox BattleFrontier_PokemonCenter_1F_Text_GoingThroughEveryChallenge, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Skitty:: @ 8267931
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, 0
	msgbox BattleFrontier_PokemonCenter_1F_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_PokemonCenter_1F_Text_NeverSeenPokemon: @ 8267944
	.string "본 적이 없는 포켓몬을\n"
	.string "쓰는 사람이 있었어!\p"
	.string "트레이너스쿨에서도\n"
	.string "알려준 적이 없었는데\l"
	.string "어디서 잡는 걸까나!$"
	// みたこともない ポケモンをｎ
	// つかってる ひとが いた!ｐ
	// トレ-ナ-ズスク-ルでもｎ
	// ならわなかった けどｌ
	// あんなの どこに いるのかなあ!

BattleFrontier_PokemonCenter_1F_Text_NextStopBattleArena: @ 82679EB
	.string "좋아! 다음은 배틀아레나다!\n"
	.string "그 포켓몬과 그 포켓몬을\l"
	.string "PC에서 데리고 가자!$"
	// よしっ! おつぎは バトルアリ-ナだ!ｎ
	// あのポケモンと あのポケモンをｌ
	// パソコンから つれて いくぜ!

BattleFrontier_PokemonCenter_1F_Text_GoingThroughEveryChallenge: @ 8267A4B
	.string "우후 저는 전부\n"
	.string "이 아이와 함께 도전할 거예요!$"
	// うふ わたしは ぜ-んぶｎ
	// このコと がんばるんだ もんね!

BattleFrontier_PokemonCenter_1F_Text_Skitty: @ 8267A90
	.string "에나비: 미야 미야-앗!$"
	// エネコ『みゃ みゃ-っ!

