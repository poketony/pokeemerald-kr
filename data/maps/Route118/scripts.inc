.set LOCALID_STEVEN, 19

Route118_MapScripts:: @ 81F3DBC
	map_script MAP_SCRIPT_ON_TRANSITION, Route118_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route118_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route118_OnFrame
	.byte 0

Route118_OnTransition: @ 81F3DCC
	call GabbyAndTy_EventScript_UpdateLocation
	compare VAR_SHOULD_END_ABNORMAL_WEATHER, 1
	call_if_eq AbnormalWeather_EventScript_HideMapNamePopup
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_118_EAST
	call_if_eq AbnormalWeather_StartGroudonWeather
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_118_WEST
	call_if_eq AbnormalWeather_StartGroudonWeather
	end

Route118_OnLoad: @ 81F3DF3
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_118_EAST
	call_if_eq AbnormalWeather_EventScript_PlaceTilesRoute118East
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_118_WEST
	call_if_eq AbnormalWeather_EventScript_PlaceTilesRoute118West
	end

Route118_OnFrame: @ 81F3E0A
	map_script_2 VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_EndEventAndCleanup_1
	.2byte 0

Route118_EventScript_GoodRodFisherman:: @ 81F3E14
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_GOOD_ROD, Route118_EventScript_ReceivedGoodRod
	msgbox Route118_Text_YouAgreeGoodRodIsGood, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route118_EventScript_ReceiveGoodRod
	compare VAR_RESULT, NO
	goto_if_eq Route118_EventScript_DeclineGoodRod
	end

Route118_EventScript_ReceiveGoodRod:: @ 81F3E3E
	msgbox Route118_Text_IdenticalMindsTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GOOD_ROD
	setflag FLAG_RECEIVED_GOOD_ROD
	msgbox Route118_Text_TryYourLuckFishing, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_DeclineGoodRod:: @ 81F3E5F
	msgbox Route118_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_ReceivedGoodRod:: @ 81F3E69
	msgbox Route118_Text_TryCatchingMonWithGoodRod, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_Girl:: @ 81F3E73
	msgbox Route118_Text_CanCrossRiversWithSurf, MSGBOX_NPC
	end

Route118_EventScript_RouteSignMauville:: @ 81F3E7C
	msgbox Route118_Text_RouteSignMauville, MSGBOX_SIGN
	end

Route118_EventScript_RouteSign119:: @ 81F3E85
	msgbox Route118_Text_RouteSign119, MSGBOX_SIGN
	end

Route118_EventScript_StevenTrigger0:: @ 81F3E8E
	lockall
	setvar VAR_0x8008, 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_STEVEN, Route118_Movement_StevenApproachLedge0
	waitmovement 0
	goto Route118_EventScript_StevenTrigger
	end

Route118_EventScript_StevenTrigger1:: @ 81F3EAE
	lockall
	setvar VAR_0x8008, 1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	goto Route118_EventScript_StevenTrigger
	end

Route118_EventScript_StevenTrigger2:: @ 81F3EC4
	lockall
	setvar VAR_0x8008, 2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_STEVEN, Route118_Movement_StevenApproachLedge2
	waitmovement 0
	goto Route118_EventScript_StevenTrigger
	end

Route118_EventScript_StevenTrigger:: @ 81F3EE4
	playse SE_LEDGE
	applymovement LOCALID_STEVEN, Route118_Movement_StevenJumpLedge
	waitmovement 0
	delay 30
	msgbox Route118_Text_StevenQuestions, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 0
	call_if_eq Route118_EventScript_StevenExit0
	compare VAR_0x8008, 1
	call_if_eq Route118_EventScript_StevenExit1
	compare VAR_0x8008, 2
	call_if_eq Route118_EventScript_StevenExit2
	setvar VAR_ROUTE118_STATE, 1
	removeobject LOCALID_STEVEN
	releaseall
	end

Route118_EventScript_StevenExit0:: @ 81F3F28
	applymovement OBJ_EVENT_ID_PLAYER, Route118_Movement_PlayerWatchStevenExit
	applymovement LOCALID_STEVEN, Route118_Movement_StevenExit0
	waitmovement 0
	return

Route118_EventScript_StevenExit1:: @ 81F3F3A
	applymovement OBJ_EVENT_ID_PLAYER, Route118_Movement_PlayerWatchStevenExit
	applymovement LOCALID_STEVEN, Route118_Movement_StevenExit1
	waitmovement 0
	return

Route118_EventScript_StevenExit2:: @ 81F3F4C
	applymovement OBJ_EVENT_ID_PLAYER, Route118_Movement_PlayerWatchStevenExit
	applymovement LOCALID_STEVEN, Route118_Movement_StevenExit2
	waitmovement 0
	return

Route118_Movement_PlayerWatchStevenExit: @ 81F3F5E
	delay_16
	walk_in_place_fastest_right
	step_end

Route118_Movement_StevenApproachLedge0: @ 81F3F61
	walk_left
	step_end

Route118_Movement_StevenApproachLedge2: @ 81F3F63
	walk_right
	step_end

Route118_Movement_StevenJumpLedge: @ 81F3F65
	jump_2_down
	delay_16
	walk_down
	step_end

Route118_Movement_StevenExit0: @ 81F3F69
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route118_Movement_StevenExit1: @ 81F3F74
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route118_Movement_StevenExit2: @ 81F3F7E
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route118_EventScript_Rose:: @ 81F3F87
	trainerbattle_single TRAINER_ROSE_1, Route118_Text_RoseIntro, Route118_Text_RoseDefeat, Route118_EventScript_RegisterRose
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route118_EventScript_RematchRose
	msgbox Route118_Text_RosePostBattle, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_RegisterRose:: @ 81F3FB3
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route118_Text_RoseRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ROSE_1
	release
	end

Route118_EventScript_RematchRose:: @ 81F3FD2
	trainerbattle_rematch TRAINER_ROSE_1, Route118_Text_RoseRematchIntro, Route118_Text_RoseRematchDefeat
	msgbox Route118_Text_RosePostRematch, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Barny:: @ 81F3FE9
	trainerbattle_single TRAINER_BARNY, Route118_Text_BarnyIntro, Route118_Text_BarnyDefeat
	msgbox Route118_Text_BarnyPostBattle, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Wade:: @ 81F4000
	trainerbattle_single TRAINER_WADE, Route118_Text_WadeIntro, Route118_Text_WadeDefeat
	msgbox Route118_Text_WadePostBattle, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Dalton:: @ 81F4017
	trainerbattle_single TRAINER_DALTON_1, Route118_Text_DaltonIntro, Route118_Text_DaltonDefeat, Route118_EventScript_RegisterDalton
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route118_EventScript_RematchDalton
	msgbox Route118_Text_DaltonPostBattle, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_RegisterDalton:: @ 81F4043
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route118_Text_DaltonRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DALTON_1
	release
	end

Route118_EventScript_RematchDalton:: @ 81F4062
	trainerbattle_rematch TRAINER_DALTON_1, Route118_Text_DaltonRematchIntro, Route118_Text_DaltonRematchDefeat
	msgbox Route118_Text_DaltonPostRematch, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Perry:: @ 81F4079
	trainerbattle_single TRAINER_PERRY, Route118_Text_PerryIntro, Route118_Text_PerryDefeat
	msgbox Route118_Text_PerryPostBattle, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Chester:: @ 81F4090
	trainerbattle_single TRAINER_CHESTER, Route118_Text_ChesterIntro, Route118_Text_ChesterDefeat
	msgbox Route118_Text_ChesterPostBattle, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Deandre:: @ 81F40A7
	trainerbattle_single TRAINER_DEANDRE, Route118_Text_DeandreIntro, Route118_Text_DeandreDefeat
	msgbox Route118_Text_DeandrePostBattle, MSGBOX_AUTOCLOSE
	end

Route118_Text_StevenQuestions: @ 81F40BE
	.string "성호: 안녕!\p"
	.string "넌 무로마을에서 만났던\n"
	.string "트레이너였지!\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "그래 {PLAYER}{K_I}라고 하는구나\n"
	.string "기억해둘게\p"
	.string "{PLAYER}\p"
	.string "이 넓은 세계에는\n"
	.string "다양한 포켓몬이 있고\l"
	.string "각자 여러 가지 타입을 가지고 있어\p"
	.string "여러 가지 타입의\n"
	.string "포켓몬을 키울 것인가\l"
	.string "아니면 좋아하는 타입의\l"
	.string "포켓몬만을 키울 것인가...\p"
	.string "넌 포켓몬 트레이너로서\n"
	.string "어떻게 생각해?\p"
	.string "내가 신경 쓸 건 아니긴 한데\p"
	.string "그럼\n"
	.string "또 만날 수 있음 좋겠네$"

Route118_Text_YouAgreeGoodRodIsGood: @ 81F427B
	.string "음!\n"
	.string "좋은낚싯대는 정말 좋은 거 같아!\p"
	.string "너도 그렇게 생각하지?$"

Route118_Text_IdenticalMindsTakeThis: @ 81F42AF
	.string "음!\n"
	.string "너랑은 죽이 맞는데!\p"
	.string "음!\n"
	.string "좋은낚싯대를 줄게!$"

Route118_Text_TryYourLuckFishing: @ 81F42E7
	.string "물이 있는 곳이라면\n"
	.string "어디서든 낚시를 하는 게 좋을 거야!$"

Route118_Text_DontYouLikeToFish: @ 81F4319
	.string "낚시 싫어하니?$"

Route118_Text_TryCatchingMonWithGoodRod: @ 81F4331
	.string "좋은낚싯대로\n"
	.string "다양한 포켓몬을 낚아 봐!$"

Route118_Text_CanCrossRiversWithSurf: @ 81F4367
	.string "배를 안 가지고 있어도\n"
	.string "파도타기를 배운 포켓몬이 있으면\l"
	.string "바다든 강이든 건너갈 수 있어!\p"
	.string "포켓몬은 정말 믿음직스러운 거 같아!$"

Route118_Text_RouteSignMauville: @ 81F43F4
	.string "여기는 118번도로\n"
	.string "{LEFT_ARROW} 보라시티$"

Route118_Text_RouteSign119: @ 81F440E
	.string "여기는 118번도로\n"
	.string "{UP_ARROW} 119번도로$"

