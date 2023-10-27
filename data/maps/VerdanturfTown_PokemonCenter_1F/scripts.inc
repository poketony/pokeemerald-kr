.set LOCALID_NURSE, 1

VerdanturfTown_PokemonCenter_1F_MapScripts:: @ 8202726
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

VerdanturfTown_PokemonCenter_1F_OnTransition: @ 8202731
	setrespawn HEAL_LOCATION_VERDANTURF_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Nurse:: @ 820273A
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Gentleman:: @ 8202748
	msgbox VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_EventScript_ExpertM:: @ 8202751
	msgbox VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon: @ 820275A
	.string "포켓몬을 믿지 못하면\n"
	.string "트레이너로서 실격이지\p"
	.string "싸우는 포켓몬들을\n"
	.string "마지막까지 믿고 지켜보는 자만이\l"
	.string "이겨나갈 수 있는 거란다$"
	// ポケモンを しんじられない ようではｎ
	// いちにんまえ とは いえないねｐ
	// たたかう ポケモンたちをｎ
	// さいごまで しんじる ものだけがｌ
	// かちぬく ことが できるんだ

VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent: @ 820280B
	.string "잔디마을에 온 이유는\n"
	.string "역시 배틀텐트지?\p"
	.string "아니면 누구 만나고 싶은 사람이라도\n"
	.string "있는 건가?$"
	// シダケにくる りゆうと いえばｎ
	// ずばり バトルテントじゃろ?ｐ
	// それとも だれか あいたい ひとでもｎ
	// いるのかね?

