EverGrandeCity_PhoebesRoom_MapScripts:: @ 8228174
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_PhoebesRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_PhoebesRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_PhoebesRoom_OnFrame
	.byte 0

EverGrandeCity_PhoebesRoom_OnWarp: @ 8228184
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_PhoebesRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_PhoebesRoom_EventScript_PlayerTurnNorth:: @ 822818E
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_PhoebesRoom_OnFrame: @ 8228193
	map_script_2 VAR_ELITE_4_STATE, 1, EverGrandeCity_PhoebesRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_PhoebesRoom_EventScript_WalkInCloseDoor:: @ 822819D
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 2
	releaseall
	end

EverGrandeCity_PhoebesRoom_OnLoad: @ 82281AA
	call_if_set FLAG_DEFEATED_ELITE_4_PHOEBE, EverGrandeCity_PhoebesRoom_EventScript_ResetAdvanceToNextRoom
	compare VAR_ELITE_4_STATE, 2
	call_if_eq EverGrandeCity_PhoebesRoom_EventScript_CloseDoor
	end

EverGrandeCity_PhoebesRoom_EventScript_ResetAdvanceToNextRoom:: @ 82281BF
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_PhoebesRoom_EventScript_CloseDoor:: @ 82281C5
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_PhoebesRoom_EventScript_Phoebe:: @ 82281CB
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_PHOEBE, EverGrandeCity_PhoebesRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, 0
	msgbox EverGrandeCity_PhoebesRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PHOEBE, EverGrandeCity_PhoebesRoom_Text_Defeat
	goto EverGrandeCity_PhoebesRoom_EventScript_Defeated
	end

EverGrandeCity_PhoebesRoom_EventScript_PostBattleSpeech:: @ 82281F2
	msgbox EverGrandeCity_PhoebesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_PhoebesRoom_EventScript_Defeated:: @ 82281FC
	setflag FLAG_DEFEATED_ELITE_4_PHOEBE
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_PhoebesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_PhoebesRoom_Text_IntroSpeech: @ 822820E
	.string "아하하!\p"
	.string "난 사천왕 회연이야\p"
	.string "송화산에서 수행하면서\n"
	.string "고스트타입 포켓몬과 마음이\l"
	.string "통하는 것이 가능하게 됐어\p"
	.string "맞아 나와 포켓몬의 유대감은\n"
	.string "엄청 강해!\p"
	.string "이런 내 포켓몬들에게\n"
	.string "데미지를 줄 수 있을지\l"
	.string "시험해 봐!$"
	// アハハ!ｐ
	// アタシ してんのうの フヨウｐ
	// おくりびやまで しゅぎょう するうちにｎ
	// ゴ-ストタイプの ポケモンと きもちをｌ
	// かよわせる ことが できるように なったのｐ
	// そう アタシと ポケモンの きずなｎ
	// とっても つよいんだ!ｐ
	// そんな アタシの ポケモンたちにｎ
	// ダメ-ジを あたえる ことが できるかｌ
	// ためして ごらんよ!

EverGrandeCity_PhoebesRoom_Text_Defeat: @ 8228325
	.string "아-아\n"
	.string "져버렸네$"
	// あ-あｎ
	// まけちゃった

EverGrandeCity_PhoebesRoom_Text_PostBattleSpeech: @ 8228343
	.string "너와 포켓몬 사이에도\n"
	.string "분명한 유대감이 있구나\p"
	.string "그걸 눈치채지 못했으니\n"
	.string "내가 지는 것도 당연하지\p"
	.string "응 너희의 유대감이\n"
	.string "어디까지 통할지 보고 싶어\l"
	.string "다음 방으로 나아가봐$"
	// あなたと ポケモンとの あいだにもｎ
	// たしかな きずなが あったのねｐ
	// それが わからなかったｎ
	// アタシが まけたのは とうぜんｐ
	// ウン あなたたちの きずながｎ
	// どこまで つうじるか みてみたいなｌ
	// つぎの へやに すすみなよ

