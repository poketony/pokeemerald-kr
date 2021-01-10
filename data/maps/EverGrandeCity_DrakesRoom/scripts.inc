EverGrandeCity_DrakesRoom_MapScripts:: @ 822869C
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_DrakesRoom_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_DrakesRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_SidneysRoom_OnWarp
	.byte 0

@ Unused, Drake uses Sidneys identical OnWarp for some reason
EverGrandeCity_DrakesRoom_OnWarp: @ 82286AC
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_DrakesRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_DrakesRoom_EventScript_PlayerTurnNorth:: @ 82286B6
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_DrakesRoom_OnFrame: @ 82286BB
	map_script_2 VAR_ELITE_4_STATE, 3, EverGrandeCity_DrakesRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_DrakesRoom_EventScript_WalkInCloseDoor:: @ 82286C5
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 4
	releaseall
	end

EverGrandeCity_DrakesRoom_OnLoad: @ 82286D2
	call_if_set FLAG_DEFEATED_ELITE_4_DRAKE, EverGrandeCity_DrakesRoom_EventScript_ResetAdvanceToNextRoom
	compare VAR_ELITE_4_STATE, 4
	call_if_eq EverGrandeCity_DrakesRoom_EventScript_CloseDoor
	end

EverGrandeCity_DrakesRoom_EventScript_ResetAdvanceToNextRoom:: @ 82286E7
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_DrakesRoom_EventScript_CloseDoor:: @ 82286ED
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_DrakesRoom_EventScript_Drake:: @ 82286F3
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_DRAKE, EverGrandeCity_DrakesRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, 0
	msgbox EverGrandeCity_DrakesRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_DRAKE, EverGrandeCity_DrakesRoom_Text_Defeat
	goto EverGrandeCity_DrakesRoom_EventScript_Defeated
	end

EverGrandeCity_DrakesRoom_EventScript_PostBattleSpeech:: @ 822871A
	msgbox EverGrandeCity_DrakesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_DrakesRoom_EventScript_Defeated:: @ 8228724
	setvar VAR_0x8004, FANCOUNTER_DEFEATED_DRAKE
	special Script_TryGainNewFanFromCounter
	setflag FLAG_DEFEATED_ELITE_4_DRAKE
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_DrakesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_DrakesRoom_Text_IntroSpeech: @ 822873E
	.string "이 몸이 바로 포켓몬리그의\n"
	.string "마지막 사천왕인\l"
	.string "드래곤 조련사 권수!\p"
	.string "포켓몬은 본디\n"
	.string "자유로운 야생의 생물이다\p"
	.string "때로는 인간을 곤란하게 하고\n"
	.string "때로는 인간을 도와주지\p"
	.string "그런 포켓몬과 함께하는 승부에\n"
	.string "무엇이 필요한지\l"
	.string "넌 알고 있는가?\p"
	.string "그걸 모른다면\n"
	.string "넌 이 몸을 이길 수 없다!$"

EverGrandeCity_DrakesRoom_Text_Defeat: @ 8228895
	.string "훌륭하다! 라고 할 만하군!$"

EverGrandeCity_DrakesRoom_Text_PostBattleSpeech: @ 82288B0
	.string "과연 여기까지\n"
	.string "도달한 포켓몬 트레이너군\l"
	.string "무엇이 필요한지\l"
	.string "잘 알고 있는 것 같다\p"
	.string "그렇다! 트레이너에게\n"
	.string "필요한 것은 올바른 마음!\p"
	.string "포켓몬은 트레이너의\n"
	.string "올바른 마음을 느끼고\l"
	.string "사물의 선악을 판단해서\l"
	.string "올바른 마음을 느껴 강해지는 거다!\p"
	.string "자! 계속 나아가라!\n"
	.string "챔피언이 기다리고 있다!$"

