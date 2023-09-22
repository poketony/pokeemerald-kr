EverGrandeCity_GlaciasRoom_MapScripts:: @ 8228412
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_GlaciasRoom_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_GlaciasRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_GlaciasRoom_OnWarp
	.byte 0

EverGrandeCity_GlaciasRoom_OnWarp: @ 8228422
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_GlaciasRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_GlaciasRoom_EventScript_PlayerTurnNorth:: @ 822842C
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_GlaciasRoom_OnFrame: @ 8228431
	map_script_2 VAR_ELITE_4_STATE, 2, EverGrandeCity_GlaciasRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_GlaciasRoom_EventScript_WalkInCloseDoor:: @ 822843B
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 3
	releaseall
	end

EverGrandeCity_GlaciasRoom_OnLoad: @ 8228448
	call_if_set FLAG_DEFEATED_ELITE_4_GLACIA, EverGrandeCity_GlaciasRoom_EventScript_ResetAdvanceToNextRoom
	compare VAR_ELITE_4_STATE, 3
	call_if_eq EverGrandeCity_GlaciasRoom_EventScript_CloseDoor
	end

EverGrandeCity_GlaciasRoom_EventScript_ResetAdvanceToNextRoom:: @ 822845D
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_GlaciasRoom_EventScript_CloseDoor:: @ 8228463
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_GlaciasRoom_EventScript_Glacia:: @ 8228469
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_GLACIA, EverGrandeCity_GlaciasRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, 0
	msgbox EverGrandeCity_GlaciasRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GLACIA, EverGrandeCity_GlaciasRoom_Text_Defeat
	goto EverGrandeCity_GlaciasRoom_EventScript_Defeated
	end

EverGrandeCity_GlaciasRoom_EventScript_PostBattleSpeech:: @ 8228490
	msgbox EverGrandeCity_GlaciasRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_GlaciasRoom_EventScript_Defeated:: @ 822849A
	setflag FLAG_DEFEATED_ELITE_4_GLACIA
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_GlaciasRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_GlaciasRoom_Text_IntroSpeech: @ 82284AC
	.string "어서 오세요\n"
	.string "사천왕 미혜입니다\p"
	.string "얼음타입 기술을 갈고닦으려고\n"
	.string "머나먼 호연지방까지 왔습니다\p"
	.string "하지만 이곳에 도전해오는 건\n"
	.string "모두 어설픈\l"
	.string "트레이너와 포켓몬뿐...\p"
	.string "당신은 어떤가요?\p"
	.string "제 진짜 실력을 발휘해도\n"
	.string "괜찮을 정도라면\l"
	.string "정말 기쁠 텐데 말이죠...!!$"

EverGrandeCity_GlaciasRoom_Text_Defeat: @ 82285B4
	.string "당신과 포켓몬들의\n"
	.string "뜨거운 혼!\p"
	.string "그것은 무엇보다도 뜨거워서\n"
	.string "제 얼음타입 기술이\l"
	.string "통할 만한 것이 아니었군요$"

EverGrandeCity_GlaciasRoom_Text_PostBattleSpeech: @ 8228640
	.string "계속 나아가세요\p"
	.string "그리고 포켓몬리그의\n"
	.string "진정한 두려움을 느껴보시길...$"

