EverGrandeCity_MapScripts:: @ 81E7D1B
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_OnTransition
	.byte 0

EverGrandeCity_OnTransition: @ 81E7D21
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

EverGrandeCity_EventScript_VictoryRoadSign:: @ 81E7D2B
	msgbox EverGrandeCity_Text_EnteringVictoryRoad, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_CitySign:: @ 81E7D34
	msgbox EverGrandeCity_Text_CitySign, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_PokemonLeagueSign:: @ 81E7D3D
	msgbox EverGrandeCity_Text_EnteringPokemonLeague, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_SetVisitedEverGrande:: @ 81E7D46
	setflag FLAG_VISITED_EVER_GRANDE_CITY
	setvar VAR_TEMP_1, 1
	end

EverGrandeCity_Text_EnteringVictoryRoad: @ 81E7D4F
	.string "이 앞은 챔피언로드$"
	// これより チャンピオン ロ-ド

EverGrandeCity_Text_EnteringPokemonLeague: @ 81E7D65
	.string "이 앞은 포켓몬리그\n"
	.string "정면 게이트$"
	// これより ポケモン リ-グｎ
	// しょうめん ゲ-ト

EverGrandeCity_Text_CitySign: @ 81E7D89
	.string "여기는 그랜드시티\n"
	.string "꽃과 바다와 포켓몬의 낙원$"
	// ここは サイユウ シティｎ
	// はなと うみと ポケモンの らくえん

