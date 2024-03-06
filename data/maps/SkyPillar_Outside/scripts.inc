.set LOCALID_WALLACE, 1

SkyPillar_Outside_MapScripts:: @ 82392A8
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_Outside_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, SkyPillar_Outside_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SkyPillar_Outside_OnFrame
	.byte 0

SkyPillar_Outside_OnTransition: @ 82392B8
	compare VAR_SOOTOPOLIS_CITY_STATE, 3
	call_if_eq SkyPillar_Outside_EventScript_HideMapNamePopup
	compare VAR_SOOTOPOLIS_CITY_STATE, 4
	call_if_ge SkyPillar_Outside_EventScript_CheckSetAbnormalWeather
	end

SkyPillar_Outside_EventScript_HideMapNamePopup:: @ 82392CF
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

SkyPillar_Outside_EventScript_CheckSetAbnormalWeather:: @ 82392D3
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	return

SkyPillar_Outside_OnLoad: @ 82392DD
	call_if_set FLAG_WALLACE_GOES_TO_SKY_PILLAR, SkyPillar_Outside_EventScript_OpenDoor
	end

SkyPillar_Outside_EventScript_OpenDoor:: @ 82392E7
	setmetatile 14, 4, METATILE_Pacifidlog_SkyPillar_DoorOpen_Top, 0
	setmetatile 14, 5, METATILE_Pacifidlog_SkyPillar_DoorOpen_Bottom, 0
	return

SkyPillar_Outside_OnFrame: @ 82392FA
	map_script_2 VAR_SOOTOPOLIS_CITY_STATE, 3, SkyPillar_Outside_EventScript_WallaceScene
	.2byte 0

SkyPillar_Outside_EventScript_WallaceScene:: @ 8239304
	lockall
	applymovement LOCALID_WALLACE, SkyPillar_Outside_Movement_WallaceApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox SkyPillar_Outside_Text_OpenedDoorToSkyPillar, MSGBOX_DEFAULT
	closemessage
	delay 30
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	delay 40
	msgbox SkyPillar_Outside_Text_EarthquakeNotMomentToWaste, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SkyPillar_Outside_Movement_PlayerClimbSkyPillar
	applymovement LOCALID_WALLACE, SkyPillar_Outside_Movement_WallaceClimbSkyPillar
	waitmovement 0
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 3   @ horizontal pan
	setvar VAR_0x8006, 20  @ num shakes
	setvar VAR_0x8007, 5   @ shake delay
	special ShakeCamera
	waitstate
	delay 20
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 10
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 20
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 30
	msgbox SkyPillar_Outside_Text_SituationGettingWorse, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SYS_WEATHER_CTRL
	setweather WEATHER_ABNORMAL
	doweather
	special WaitWeather
	waitstate
	delay 30
	msgbox SkyPillar_Outside_Text_GotToGoBackForSootopolis, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreenswapbuffers FADE_TO_BLACK
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_SOOTOPOLIS_CITY_STATE, 4
	removeobject LOCALID_WALLACE
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end

SkyPillar_Outside_Movement_WallaceApproachPlayer: @ 82393D3
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

SkyPillar_Outside_Movement_WallaceClimbSkyPillar: @ 82393DE
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SkyPillar_Outside_Movement_PlayerClimbSkyPillar: @ 82393EB
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

SkyPillar_Outside_EventScript_Wallace:: @ 82393F8
	end

SkyPillar_Outside_EventScript_ClosedDoor:: @ 82393F9
	msgbox SkyPillar_Outside_Text_DoorIsClosed, MSGBOX_SIGN
	end

SkyPillar_Outside_Text_DoorIsClosed: @ 8239402
	.string "문이 닫혀 있다!$"
	@ とびらは とざされて いる!

SkyPillar_Outside_Text_OpenedDoorToSkyPillar: @ 8239416
	.string "윤진: 앗 미안 미안!\p"
	.string "너무 급하다 보니\n"
	.string "너를 두고 갈 뻔했어!\p"
	.string "잠겨 있던 하늘기둥의 문은\n"
	.string "내가 열어 뒀어\p"
	.string "{PLAYER} 자 가자!$"
	@ ミクリ『やっ ごめん ごめん!ｐ
	@ あんまり あわてた ものだからｎ
	@ きみを おいてきて しまったよ!ｐ
	@ しまっていた そらのはしらの とびらはｎ
	@ わたしが あけて おいたｐ
	@ §あ§お さあ いこう!

SkyPillar_Outside_Text_EarthquakeNotMomentToWaste: @ 82394BC
	.string "윤진: 지진이야!\p"
	.string "이러고 있을 때가 아냐\n"
	.string "앞으로 서두르자!$"
	@ ミクリ『じしんだ!ｐ
	@ こうしては いられないｎ
	@ さきを いそごう!

SkyPillar_Outside_Text_SituationGettingWorse: @ 823950C
	.string "윤진: 으-음 상황은\n"
	.string "점점 나빠지고 있어...$"
	@ ミクリ『う-む じょうきょうはｎ
	@ だんだん わるくなって きている……

SkyPillar_Outside_Text_GotToGoBackForSootopolis: @ 823953A
	.string "윤진: 위험한걸...\p"
	.string "날씨의 왜곡이 이 주변까지\n"
	.string "퍼져나가기 시작했어...\p"
	.string "{PLAYER}\p"
	.string "여기를 올라가면\n"
	.string "레쿠쟈가 있을 거야\p"
	.string "나는 마을이 걱정되니까\n"
	.string "먼저 루네시티로 돌아갈게!\p"
	.string "여기는 너에게 맡길 테니까\n"
	.string "제대로 해 줘!$"
	@ ミクリ『まずいな……ｐ
	@ てんこうの みだれが このあたりまでｎ
	@ ひろがり はじめている……ｐ
	@ §あ§おｐ
	@ ここを のぼって いけばｎ
	@ レックウザが いるはずだｐ
	@ わたしは まちのことが しんぱい だからｎ
	@ さきに ルネまで もどっていよう!ｐ
	@ ここは きみに まかせるからｎ
	@ しっかり たのんだよ!
