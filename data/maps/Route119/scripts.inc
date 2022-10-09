.set LOCALID_RIVAL, 16
.set LOCALID_RIVAL_ON_BIKE, 25
.set LOCALID_SCOTT, 43

Route119_MapScripts:: @ 81F4424
	map_script MAP_SCRIPT_ON_RESUME, Route119_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_OnTransition
	.byte 0

Route119_OnResume: @ 81F442F
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Route119_EventScript_TryRemoveKecleon
	end

Route119_EventScript_TryRemoveKecleon:: @ 81F4439
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

Route119_OnTransition: @ 81F444D
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	compare VAR_WEATHER_INSTITUTE_STATE, 1
	call_if_eq Route119_EventScript_MoveInstituteWorkersDownstairs
	special SetRoute119Weather
	end

Route119_EventScript_MoveInstituteWorkersDownstairs:: @ 81F4466
	setflag FLAG_HIDE_WEATHER_INSTITUTE_2F_WORKERS
	clearflag FLAG_HIDE_WEATHER_INSTITUTE_1F_WORKERS
	setvar VAR_WEATHER_INSTITUTE_STATE, 2
	return

Route119_EventScript_RivalTrigger1:: @ 81F4472
	setvar VAR_TEMP_1, 1
	goto Route119_EventScript_RivalEncounter
	end

Route119_EventScript_RivalTrigger2:: @ 81F447D
	setvar VAR_TEMP_1, 2
	goto Route119_EventScript_RivalEncounter
	end

Route119_EventScript_RivalEncounter:: @ 81F4488
	lockall
	addobject LOCALID_RIVAL_ON_BIKE
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq Route119_EventScript_PlayMayMusic
	compare VAR_RESULT, FEMALE
	call_if_eq Route119_EventScript_PlayBrendanMusic
	delay 65
	compare VAR_TEMP_1, 1
	call_if_eq Route119_EventScript_RivalEnter1
	compare VAR_TEMP_1, 2
	call_if_eq Route119_EventScript_RivalEnter2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 30
	compare VAR_TEMP_1, 1
	call_if_eq Route119_EventScript_SetRivalPos1
	compare VAR_TEMP_1, 2
	call_if_eq Route119_EventScript_SetRivalPos2
	removeobject LOCALID_RIVAL_ON_BIKE
	addobject LOCALID_RIVAL
	delay 30
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq Route119_EventScript_BattleMay
	compare VAR_RESULT, FEMALE
	goto_if_eq Route119_EventScript_BattleBrendan
	releaseall
	end

Route119_EventScript_PlayMayMusic:: @ 81F4501
	playbgm MUS_ENCOUNTER_MAY, 1
	return

Route119_EventScript_PlayBrendanMusic:: @ 81F4506
	playbgm MUS_ENCOUNTER_BRENDAN, 1
	return

Route119_EventScript_BattleMay:: @ 81F450B
	msgbox Route119_Text_MayIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route119_EventScript_BattleMayTreecko
	case 1, Route119_EventScript_BattleMayTorchic
	case 2, Route119_EventScript_BattleMayMudkip
	end

Route119_EventScript_BattleMayTreecko:: @ 81F453A
	trainerbattle_no_intro TRAINER_MAY_ROUTE_119_TREECKO, Route119_Text_MayDefeat
	goto Route119_EventScript_DefeatedMay
	end

Route119_EventScript_BattleMayTorchic:: @ 81F454A
	trainerbattle_no_intro TRAINER_MAY_ROUTE_119_TORCHIC, Route119_Text_MayDefeat
	goto Route119_EventScript_DefeatedMay
	end

Route119_EventScript_BattleMayMudkip:: @ 81F455A
	trainerbattle_no_intro TRAINER_MAY_ROUTE_119_MUDKIP, Route119_Text_MayDefeat
	goto Route119_EventScript_DefeatedMay
	end

Route119_EventScript_DefeatedMay:: @ 81F456A
	msgbox Route119_Text_MayPresentForYou, MSGBOX_DEFAULT
	call Route119_EventScript_GiveFlyHM
	msgbox Route119_Text_MayExplainFly, MSGBOX_DEFAULT
	goto Route119_EventScript_RivalExitScottArrive
	end

Route119_EventScript_BattleBrendan:: @ 81F4585
	msgbox Route119_Text_BrendanIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route119_EventScript_BattleBrendanTreecko
	case 1, Route119_EventScript_BattleBrendanTorchic
	case 2, Route119_EventScript_BattleBrendanMudkip
	end

Route119_EventScript_BattleBrendanTreecko:: @ 81F45B4
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_119_TREECKO, Route119_Text_BrendanDefeat
	goto Route119_EventScript_DefeatedBrendan
	end

Route119_EventScript_BattleBrendanTorchic:: @ 81F45C4
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_119_TORCHIC, Route119_Text_BrendanDefeat
	goto Route119_EventScript_DefeatedBrendan
	end

Route119_EventScript_BattleBrendanMudkip:: @ 81F45D4
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_119_MUDKIP, Route119_Text_BrendanDefeat
	goto Route119_EventScript_DefeatedBrendan
	end

Route119_EventScript_DefeatedBrendan:: @ 81F45E4
	msgbox Route119_Text_BrendanIllGiveYouThis, MSGBOX_DEFAULT
	call Route119_EventScript_GiveFlyHM
	msgbox Route119_Text_BrendanExplainFly, MSGBOX_DEFAULT
	goto Route119_EventScript_RivalExitScottArrive
	end

Route119_EventScript_GiveFlyHM:: @ 81F45FF
	giveitem ITEM_HM02
	setflag FLAG_RECEIVED_HM02
	return

Route119_EventScript_RivalExitScottArrive:: @ 81F460F
	closemessage
	compare VAR_TEMP_1, 1
	call_if_eq Route119_EventScript_SetRivalPos1
	compare VAR_TEMP_1, 2
	call_if_eq Route119_EventScript_SetRivalPos2
	removeobject LOCALID_RIVAL
	addobject LOCALID_RIVAL_ON_BIKE
	delay 30
	compare VAR_TEMP_1, 1
	call_if_eq Route119_EventScript_RivalExit1
	compare VAR_TEMP_1, 2
	call_if_eq Route119_EventScript_RivalExit2
	removeobject LOCALID_RIVAL_ON_BIKE
	setvar VAR_ROUTE119_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	delay 60
	compare VAR_TEMP_1, 1
	call_if_eq Route119_EventScript_SetScottPos1
	compare VAR_TEMP_1, 2
	call_if_eq Route119_EventScript_SetScottPos2
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, Route119_Movement_ScottEnter
	waitmovement 0
	addvar VAR_SCOTT_STATE, 1
	msgbox Route119_Text_ScottWayToGoBeSeeingYou, MSGBOX_DEFAULT
	closemessage
	compare VAR_TEMP_1, 1
	call_if_eq Route119_EventScript_ScottExit1
	compare VAR_TEMP_1, 2
	call_if_eq Route119_EventScript_ScottExit2
	removeobject LOCALID_SCOTT
	releaseall
	end

Route119_EventScript_SetScottPos1:: @ 81F46A0
	setobjectxyperm LOCALID_SCOTT, 27, 25
	return

Route119_EventScript_SetScottPos2:: @ 81F46A8
	setobjectxyperm LOCALID_SCOTT, 28, 25
	return

Route119_EventScript_ScottExit1:: @ 81F46B0
	applymovement LOCALID_SCOTT, Route119_Movement_ScottExit1
	waitmovement 0
	return

Route119_EventScript_ScottExit2:: @ 81F46BB
	applymovement LOCALID_SCOTT, Route119_Movement_ScottExit2
	waitmovement 0
	return

Route119_EventScript_RivalEnter1:: @ 81F46C6
	applymovement LOCALID_RIVAL_ON_BIKE, Route119_Movement_RivalEnter1
	waitmovement 0
	return

Route119_EventScript_RivalEnter2:: @ 81F46D1
	applymovement LOCALID_RIVAL_ON_BIKE, Route119_Movement_RivalEnter2
	waitmovement 0
	return

Route119_EventScript_RivalExit1:: @ 81F46DC
	applymovement OBJ_EVENT_ID_PLAYER, Route119_Movement_PlayerWatchRivalExit1
	applymovement LOCALID_RIVAL_ON_BIKE, Route119_Movement_RivalExit1
	waitmovement 0
	return

Route119_EventScript_RivalExit2:: @ 81F46EE
	applymovement OBJ_EVENT_ID_PLAYER, Route119_Movement_PlayerWatchRivalExit2
	applymovement LOCALID_RIVAL_ON_BIKE, Route119_Movement_RivalExit2
	waitmovement 0
	return

Route119_EventScript_SetRivalPos1:: @ 81F4700
	setobjectxyperm LOCALID_RIVAL, 25, 32
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 25, 32
	return

Route119_EventScript_SetRivalPos2:: @ 81F470F
	setobjectxyperm LOCALID_RIVAL, 26, 32
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 26, 32
	return

Route119_Movement_PlayerWatchRivalExit1: @ 81F471E
	delay_16
	walk_in_place_fastest_right
	delay_8
	walk_in_place_fastest_up
	step_end

Route119_Movement_PlayerWatchRivalExit2: @ 81F4723
	delay_16
	walk_in_place_fastest_left
	delay_8
	walk_in_place_fastest_up
	step_end

Route119_Movement_RivalEnter1: @ 81F4728
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end

Route119_Movement_RivalEnter2: @ 81F4732
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end

Route119_Movement_RivalExit1: @ 81F473D
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route119_Movement_RivalExit2: @ 81F4747
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route119_Movement_ScottEnter: @ 81F4752
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	step_end

Route119_Movement_ScottExit1: @ 81F475A
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route119_Movement_ScottExit2: @ 81F4763
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route119_EventScript_CyclingTriathleteM:: @ 81F476B
	msgbox Route119_Text_TallGrassSnaresBikeTires, MSGBOX_NPC
	end

Route119_EventScript_RouteSignFortree:: @ 81F4774
	msgbox Route119_Text_RouteSignFortree, MSGBOX_SIGN
	end

Route119_EventScript_WeatherInstituteSign:: @ 81F477D
	msgbox Route119_Text_WeatherInstitute, MSGBOX_SIGN
	end

Route119_EventScript_Brent:: @ 81F4786
	trainerbattle_single TRAINER_BRENT, Route119_Text_BrentIntro, Route119_Text_BrentDefeat
	msgbox Route119_Text_BrentPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Donald:: @ 81F479D
	trainerbattle_single TRAINER_DONALD, Route119_Text_DonaldIntro, Route119_Text_DonaldDefeat
	msgbox Route119_Text_DonaldPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Taylor:: @ 81F47B4
	trainerbattle_single TRAINER_TAYLOR, Route119_Text_TaylorIntro, Route119_Text_TaylorDefeat
	msgbox Route119_Text_TaylorPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Doug:: @ 81F47CB
	trainerbattle_single TRAINER_DOUG, Route119_Text_DougIntro, Route119_Text_DougDefeat
	msgbox Route119_Text_DougPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Greg:: @ 81F47E2
	trainerbattle_single TRAINER_GREG, Route119_Text_GregIntro, Route119_Text_GregDefeat
	msgbox Route119_Text_GregPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Kent:: @ 81F47F9
	trainerbattle_single TRAINER_KENT, Route119_Text_KentIntro, Route119_Text_KentDefeat
	msgbox Route119_Text_KentPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Jackson:: @ 81F4810
	trainerbattle_single TRAINER_JACKSON_1, Route119_Text_JacksonIntro, Route119_Text_JacksonDefeat, Route119_EventScript_RegisterJackson
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route119_EventScript_RematchJackson
	msgbox Route119_Text_JacksonPostBattle, MSGBOX_DEFAULT
	release
	end

Route119_EventScript_RegisterJackson:: @ 81F483C
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route119_Text_JacksonRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JACKSON_1
	release
	end

Route119_EventScript_RematchJackson:: @ 81F485B
	trainerbattle_rematch TRAINER_JACKSON_1, Route119_Text_JacksonRematchIntro, Route119_Text_JacksonRematchDefeat
	msgbox Route119_Text_JacksonPostRematch, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Catherine:: @ 81F4872
	trainerbattle_single TRAINER_CATHERINE_1, Route119_Text_CatherineIntro, Route119_Text_CatherineDefeat, Route119_EventScript_RegisterCatherine
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route119_EventScript_RematchCatherine
	msgbox Route119_Text_CatherinePostBattle, MSGBOX_DEFAULT
	release
	end

Route119_EventScript_RegisterCatherine:: @ 81F489E
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route119_Text_CatherineRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_CATHERINE_1
	release
	end

Route119_EventScript_RematchCatherine:: @ 81F48BD
	trainerbattle_rematch TRAINER_CATHERINE_1, Route119_Text_CatherineRematchIntro, Route119_Text_CatherineRematchDefeat
	msgbox Route119_Text_CatherinePostRematch, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Hugh:: @ 81F48D4
	trainerbattle_single TRAINER_HUGH, Route119_Text_HughIntro, Route119_Text_HughDefeat
	msgbox Route119_Text_HughPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Phil:: @ 81F48EB
	trainerbattle_single TRAINER_PHIL, Route119_Text_PhilIntro, Route119_Text_PhilDefeat
	msgbox Route119_Text_PhilPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Yasu:: @ 81F4902
	trainerbattle_single TRAINER_YASU, Route119_Text_YasuIntro, Route119_Text_YasuDefeat
	msgbox Route119_Text_YasuPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Takashi:: @ 81F4919
	trainerbattle_single TRAINER_TAKASHI, Route119_Text_TakashiIntro, Route119_Text_TakashiDefeat
	msgbox Route119_Text_TakashiPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Hideo:: @ 81F4930
	trainerbattle_single TRAINER_HIDEO, Route119_Text_HideoIntro, Route119_Text_HideoDefeat
	msgbox Route119_Text_HideoPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Chris:: @ 81F4947
	trainerbattle_single TRAINER_CHRIS, Route119_Text_ChrisIntro, Route119_Text_ChrisDefeat
	msgbox Route119_Text_ChrisPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Fabian:: @ 81F495E
	trainerbattle_single TRAINER_FABIAN, Route119_Text_FabianIntro, Route119_Text_FabianDefeat
	msgbox Route119_Text_FabianPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Dayton:: @ 81F4975
	trainerbattle_single TRAINER_DAYTON, Route119_Text_DaytonIntro, Route119_Text_DaytonDefeat
	msgbox Route119_Text_DaytonPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Rachel:: @ 81F498C
	trainerbattle_single TRAINER_RACHEL, Route119_Text_RachelIntro, Route119_Text_RachelDefeat
	msgbox Route119_Text_RachelPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_BridgeAquaGrunt1:: @ 81F49A3
	lock
	faceplayer
	msgbox Route119_Text_StayAwayFromWeatherInstitute, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route119_EventScript_BridgeAquaGrunt2:: @ 81F49BA
	lock
	faceplayer
	msgbox Route119_Text_DontGoNearWeatherInstitute, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route119_EventScript_Boy1:: @ 81F49D1
	msgbox Route119_Text_ThoughtFlyByCatchingBirdMons, MSGBOX_NPC
	end

Route119_EventScript_Boy2:: @ 81F49DA
	msgbox Route119_Text_CanYourMonMakeSecretBase, MSGBOX_NPC
	end

Route119_EventScript_TrainerTipsDecoration:: @ 81F49E3
	msgbox Route119_Text_TrainerTipsDecoration, MSGBOX_SIGN
	end

Route119_EventScript_ScottWonAtFortreeGymCall:: @ 81F49EC
	lockall
	pokenavcall Route119_Text_ScottYouWonAtFortreeGym
	waitmessage
	clearflag FLAG_SCOTT_CALL_FORTREE_GYM
	addvar VAR_SCOTT_STATE, 1
	releaseall
	end

Route119_Text_MayIntro: @ 81F49FD
	.string "봄이: {PLAYER}!\n"
	.string "어디에 있었어? 찾았잖아!\p"
	.string "얼마나 강해졌는지\n"
	.string "잠깐 시험해 볼게!\p"
	.string "포켓몬의 준비는...\n"
	.string "당연히 끝났겠지! 간다!$"

Route119_Text_MayDefeat: @ 81F4A98
	.string "으아-!\n"
	.string "{PLAYER} 강하잖아!\p"
	.string "포켓몬을 키우지 못해서\n"
	.string "곤란할 거라고 걱정하고 있었는데$"

Route119_Text_MayPresentForYou: @ 81F4AF3
	.string "봄이: 전혀 아무렇지도 않아!\n"
	.string "그 기세로 힘내도록 해!\p"
	.string "이건 내가 주는 선물이야!$"

Route119_Text_MayExplainFly: @ 81F4B56
	.string "봄이: 공중날기를 쓰면\n"
	.string "한 번 갔던 도시라면 순식간에\l"
	.string "날아갈 수 있게 돼!\p"
	.string "하지만 공중날기를 쓰려면\n"
	.string "검방울시티의\l"
	.string "체육관 배지가 필요해\l"
	.string "이거 중요한 거니까 잊지 마!\p"
	.string "가끔 공중날기로\n"
	.string "미로마을에 가보는 것도\l"
	.string "좋을 것 같아\p"
	.string "{PLAYER}네 엄마\n"
	.string "걱정하고 계실지도 모르니까...\p"
	.string "그럼\n"
	.string "또 어딘가에서 만나!$"

Route119_Text_BrendanIntro: @ 81F4C9A
	.string "휘웅: {PLAYER}!\n"
	.string "여기에서 포켓몬 찾고 있었어?\p"
	.string "얼마나 강해졌는지\n"
	.string "시험해 줄게\p"
	.string "자!\n"
	.string "승부 승부다!$"

Route119_Text_BrendanDefeat: @ 81F4D24
	.string "흠...\n"
	.string "꽤 강해졌구나$"

Route119_Text_BrendanIllGiveYouThis: @ 81F4D4B
	.string "휘웅: 그 정도면\n"
	.string "어디에서 포켓몬을 찾아도\l"
	.string "아무 문제 없겠는데\p"
	.string "이거 줄 테니까 써 봐!$"

Route119_Text_BrendanExplainFly: @ 81F4DB5
	.string "휘웅: 공중날기를 쓰면\n"
	.string "한 번 갔던 도시라면\l"
	.string "순식간에 날아갈 수 있어\p"
	.string "단지 검방울시티 체육관의\n"
	.string "체육관 배지가 필요하지만...\p"
	.string "그럼 난 먼저 갈게$"

Route119_Text_ScottWayToGoBeSeeingYou: @ 81F4E60
	.string "금작화: 우후후!\n"
	.string "꽤 하네 {PLAYER}...!\p"
	.string "지금 자전거를 탄 트레이너와\n"
	.string "엇갈렸는데 말이야\l"
	.string "너 그 트레이너한테 이겼지?\l"
	.string "알고 있다고-!\p"
	.string "그야 그 애 새빨간 얼굴로\n"
	.string "무척 분해하고 있었으니까!\p"
	.string "그건 그렇고 너하고는\n"
	.string "여러 곳에서 만나는구나!\l"
	.string "다음은 검방울체육관에 갈 거지?\p"
	.string "체육관전도 기대하고 있을게!\n"
	.string "그럼 또 보자!$"
	// エニシダ『うふふ!ｎ
	// やるねえ §あ§お……!ｐ
	// いま じてんしゃに のった トレ-ナ-とｎ
	// すれちがったん だけどさｌ
	// きみ あのトレ-ナ-に かったんだろ?ｌ
	// わかるよ-!ｐ
	// だって あのコ まっかな かおしてｎ
	// すっごく くやしそう だったからね!ｐ
	// それにしても きみとはｎ
	// いろいろな ところで あうね!ｌ
	// この あとは ヒワマキジムに いくのかな?ｐ
	// ジムせんも きたい してるよ!ｎ
	// じゃ また あおうね!


Route119_Text_ScottYouWonAtFortreeGym: @ 81F4FBA
	.string "...... ...... ......\n"
	.string "...... ...... ...삑!\p"
	.string "금작화: 여어 안녕\n"
	.string "{PLAYER} 나야!\p"
	.string "생각했던 대로!\n"
	.string "검방울체육관에서도 이겼구나!\p"
	.string "너의 그 강함은 어쩌면...\n"
	.string "내가 찾고 있던 트레이너는\l"
	.string "정말로 너일지도 모르겠어!\p"
	.string "응 너에 대해선 앞으로도\n"
	.string "멀리서나마 응원하고 있을게!\l"
	.string "그럼 힘내라고!\p"
	.string "...... ...... ......\n"
	.string "...... ...... ...... 딸깍-$"
	// …… …… ……ｎ
	// …… …… …… ピッ!ｐ
	// エニシダ『やあどうもｎ
	// §あ§お わたしだよ!ｐ
	// おもった とおり!ｎ
	// ヒワマキジム でも きみは かったね!ｐ
	// きみの その つよさ もしかしたら……ｎ
	// わたしの もとめている トレ-ナ-はｌ
	// ほんとうに きみかも しれないな!ｐ
	// うん きみのこと これからもｎ
	// かげながら おうえん しているから!ｌ
	// じゃ がんばってよ!ｐ
	// …… …… ……ｎ
	// …… …… …… ツ-

Route119_Text_StayAwayFromWeatherInstitute: @ 81F50EB
	.string "우린 여기에서 망을 보고 있지\p"
	.string "어이 너! 위험하니까\n"
	.string "날씨 연구소에는 가까이 가지 마$"

Route119_Text_DontGoNearWeatherInstitute: @ 81F5147
	.string "망보는 건 의외로 한가롭네...\p"
	.string "어이 너! 부탁이니까 연구소에는\n"
	.string "가까이 가지 마라!$"

Route119_Text_ThoughtFlyByCatchingBirdMons: @ 81F51A2
	.string "새포켓몬을 많이 잡아서\n"
	.string "매달리면\l"
	.string "하늘을 날 수 있을 거라 생각했어요\p"
	.string "그런데 “공중날기”라는\n"
	.string "비전기술이 있다는 거예요!?\p"
	.string "좀 더 일찍 알고 싶었는데...$"

Route119_Text_TallGrassSnaresBikeTires: @ 81F5261
	.string "큰일이야...\p"
	.string "긴 풀이 타이어에 휘감기니까\n"
	.string "자전거를 탈 수가 없어...$"

Route119_Text_CanYourMonMakeSecretBase: @ 81F52B9
	.string "너의 포켓몬\n"
	.string "비밀의힘이라는 기술을 써서\l"
	.string "큰 풀 덩어리에\l"
	.string "비밀기지를 만들 수 있어?$"

Route119_Text_RouteSignFortree: @ 81F530E
	.string "여기는 119번 도로\n"
	.string "{RIGHT_ARROW} 검방울시티$"

Route119_Text_WeatherInstitute: @ 81F5327
	.string "“날씨 연구소”$"

Route119_Text_TrainerTipsDecoration: @ 81F5339
	.string "정보 나눔 게시판!!\p"
	.string "비밀기지에는 굿즈를\n"
	.string "16개까지 놓을 수 있습니다!\p"
	.string "좋아하는 굿즈를 선택해서\n"
	.string "당신만의 마음에 드는\l"
	.string "비밀기지를 만듭시다!$"
