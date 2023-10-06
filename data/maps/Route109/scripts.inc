@ NOTE: Route 109's sail to Dewford script references local IDs from Dewford's map. 
@  These are labeled in DewfordTown/scripts.inc

Route109_MapScripts:: @ 81EE75F
	.byte 0

Route109_EventScript_StartDepartForDewford:: @ 81EE760
	call EventScript_BackupMrBrineyLocation
	setobjectpriority LOCALID_BRINEY_R109, MAP_ROUTE109, 0
	setobjectpriority OBJ_EVENT_ID_PLAYER, MAP_ROUTE109, 0
	applymovement LOCALID_BRINEY_R109, Route109_Movement_BrineyEnterBoat
	waitmovement 0
	removeobject LOCALID_BRINEY_R109
	switch VAR_FACING
	case DIR_SOUTH, Route109_EventScript_EnterBoatSouth
	case DIR_WEST, Route109_EventScript_EnterBoatWest
	case DIR_EAST, Route109_EventScript_EnterBoatEast
	end

Route109_EventScript_EnterBoatSouth:: @ 81EE7A5
	applymovement OBJ_EVENT_ID_PLAYER, Route109_Movement_PlayerEnterBoatSouth
	waitmovement 0
	goto Route109_EventScript_DoSailToDewford
	end

Route109_EventScript_EnterBoatEast:: @ 81EE7B5
	applymovement OBJ_EVENT_ID_PLAYER, Route109_Movement_PlayerEnterBoatEast
	waitmovement 0
	goto Route109_EventScript_DoSailToDewford
	end

Route109_EventScript_EnterBoatWest:: @ 81EE7C5
	applymovement OBJ_EVENT_ID_PLAYER, Route109_Movement_PlayerEnterBoatWest
	waitmovement 0
	goto Route109_EventScript_DoSailToDewford
	end

Route109_EventScript_DoSailToDewford:: @ 81EE7D5
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_ROUTE109
	call Common_EventScript_PlayBrineysBoatMusic
	applymovement LOCALID_BOAT_R109, Route109_Movement_SailToDewford
	applymovement OBJ_EVENT_ID_PLAYER, Route109_Movement_SailToDewford
	waitmovement 0
	delay 50
	call Common_EventScript_StopBrineysBoatMusic
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN
	applymovement OBJ_EVENT_ID_PLAYER, Route109_Movement_PlayerExitBoat
	waitmovement 0
	addobject LOCALID_BOAT_DEWFORD
	clearflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	setobjectxyperm LOCALID_BRINEY_DEWFORD, 12, 8
	addobject LOCALID_BRINEY_DEWFORD
	setobjectpriority LOCALID_BRINEY_DEWFORD, MAP_DEWFORD_TOWN, 0
	applymovement LOCALID_BRINEY_DEWFORD, Route109_Movement_BrineyExitBoat
	waitmovement 0
	clearflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	hideobjectat LOCALID_BOAT_R109, MAP_ROUTE109
	msgbox DewfordTown_Text_BrineyLandedInDewford, MSGBOX_DEFAULT
	closemessage
	copyvar VAR_BRINEY_LOCATION, VAR_0x8008
	resetobjectpriority OBJ_EVENT_ID_PLAYER, MAP_ROUTE109
	resetobjectpriority LOCALID_BRINEY_DEWFORD, MAP_DEWFORD_TOWN
	copyobjectxytoperm LOCALID_BRINEY_DEWFORD
	release
	end

Route109_Movement_SailToDewford: @ 81EE84F
	walk_in_place_fastest_down
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_left
	walk_left
	walk_in_place_fastest_down
	step_end

Route109_Movement_PlayerEnterBoatSouth: @ 81EE8FD
	walk_down
	walk_down
	step_end

Route109_Movement_PlayerExitBoat: @ 81EE900
	walk_down
	walk_down
	walk_left
	walk_in_place_fastest_right
	step_end

Route109_Movement_PlayerEnterBoatEast: @ 81EE905
	walk_right
	walk_down
	step_end

Route109_Movement_PlayerEnterBoatWest: @ 81EE908
	walk_left
	walk_down
	step_end

Route109_Movement_BrineyEnterBoat: @ 81EE90B
	walk_down
	step_end

Route109_Movement_BrineyExitBoat: @ 81EE90D
	walk_down
	walk_in_place_fastest_left
	step_end

Route109_EventScript_MrBriney:: @ 81EE910
	lock
	faceplayer
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, Route109_EventScript_HaveNotDeliveredDevonGood
	goto Route109_EventScript_DeliveredDevonGoods
	end

Route109_EventScript_HaveNotDeliveredDevonGood:: @ 81EE921
	message Route109_Text_BrineySailToDewfordQuestion
	msgbox Route109_Text_BrineySailToDewfordQuestion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route109_EventScript_StayHere
	goto Route109_EventScript_SailToDewford
	end

Route109_EventScript_DeliveredDevonGoods:: @ 81EE93F
	message Route109_Text_BrineyWhereAreWeBound
	waitmessage
	multichoicedefault 21, 8, MULTI_BRINEY_OFF_DEWFORD, 1, 0
	switch VAR_RESULT
	case 0, Route109_EventScript_SailToDewford
	case 1, Route109_EventScript_ChoseNotToSail
	case MULTI_B_PRESSED, Route109_EventScript_ChoseNotToSail
	end

Route109_EventScript_SailToDewford:: @ 81EE972
	msgbox Route109_Text_BrineyDewfordItIs, MSGBOX_DEFAULT
	closemessage
	goto Route109_EventScript_StartDepartForDewford
	end

Route109_EventScript_StayHere:: @ 81EE981
	msgbox Route109_Text_BrineyDeliverDevonGoods, MSGBOX_DEFAULT
	release
	end

Route109_EventScript_ChoseNotToSail:: @ 81EE98B
	msgbox Route109_Text_BrineyTellMeWhenYouNeedToSail, MSGBOX_DEFAULT
	release
	end

Route109_EventScript_SeashoreHouseGirl:: @ 81EE995
	msgbox Route109_Text_ChillAtMyPapasSpot, MSGBOX_NPC
	end

Route109_EventScript_SandCastleBoy:: @ 81EE99E
	lock
	faceplayer
	msgbox Route109_Text_SandCastleTakingLongTime, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route109_EventScript_SoftSandGirl:: @ 81EE9B5
	lock
	faceplayer
	special GetPlayerBigGuyGirlString
	goto_if_set FLAG_RECEIVED_SOFT_SAND, Route109_EventScript_AlreadyReceivedSoftSand
	msgbox Route109_Text_YouCanHaveThis, MSGBOX_DEFAULT
	giveitem ITEM_SOFT_SAND
	compare VAR_RESULT, 0
	goto_if_eq Common_EventScript_ShowBagIsFull
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_RECEIVED_SOFT_SAND
	release
	end

Route109_EventScript_AlreadyReceivedSoftSand:: @ 81EE9F2
	msgbox Route109_Text_WereGoingToMakeBigCastle, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route109_EventScript_Woman:: @ 81EEA06
	msgbox Route109_Text_LittleKidsDartAround, MSGBOX_NPC
	end

Route109_EventScript_OldMan:: @ 81EEA0F
	msgbox Route109_Text_ZigzagoonPicksUpLitter, MSGBOX_NPC
	end

Route109_EventScript_Zigzagoon:: @ 81EEA18
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, 0
	msgbox Route109_Text_ZigzagoonCry, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route109_EventScript_SeashoreHouseSign:: @ 81EEA2B
	msgbox Route109_Text_SeashoreHouseSign, MSGBOX_SIGN
	end

Route109_EventScript_TrainerTipsSign:: @ 81EEA34
	msgbox Route109_Text_TrainerTipsSign, MSGBOX_SIGN
	end

Route109_EventScript_David:: @ 81EEA3D
	trainerbattle_single TRAINER_DAVID, Route109_Text_DavidIntro, Route109_Text_DavidDefeated
	msgbox Route109_Text_DavidPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_EventScript_Alice:: @ 81EEA54
	trainerbattle_single TRAINER_ALICE, Route109_Text_AliceIntro, Route109_Text_AliceDefeated
	msgbox Route109_Text_AlicePostBattle, MSGBOX_AUTOCLOSE
	end

Route109_EventScript_Huey:: @ 81EEA6B
	trainerbattle_single TRAINER_HUEY, Route109_Text_HueyIntro, Route109_Text_HueyDefeated
	msgbox Route109_Text_HueyPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_EventScript_Edmond:: @ 81EEA82
	trainerbattle_single TRAINER_EDMOND, Route109_Text_EdmondIntro, Route109_Text_EdmondDefeated
	msgbox Route109_Text_EdmondPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_EventScript_Ricky:: @ 81EEA99
	trainerbattle_single TRAINER_RICKY_1, Route109_Text_RickyIntro, Route109_Text_RickyDefeated, Route109_EventScript_RickyRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route109_EventScript_RickyRematch
	msgbox Route109_Text_RickyPostBattle, MSGBOX_DEFAULT
	release
	end

Route109_EventScript_RickyRegisterMatchCallAfterBattle:: @ 81EEAC5
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route109_Text_RickyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_RICKY_1
	release
	end

Route109_EventScript_RickyRematch:: @ 81EEAE4
	trainerbattle_rematch TRAINER_RICKY_1, Route109_Text_RickyRematchIntro, Route109_Text_RickyRematchDefeated
	msgbox Route109_Text_RickyRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_EventScript_Lola:: @ 81EEAFB
	trainerbattle_single TRAINER_LOLA_1, Route109_Text_LolaIntro, Route109_Text_LolaDefeated, Route109_EventScript_LolaRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route109_EventScript_LolaRematch
	msgbox Route109_Text_LolaPostBattle, MSGBOX_DEFAULT
	release
	end

Route109_EventScript_LolaRegisterMatchCallAfterBattle:: @ 81EEB27
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route109_Text_LolaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_LOLA_1
	release
	end

Route109_EventScript_LolaRematch:: @ 81EEB46
	trainerbattle_rematch TRAINER_LOLA_1, Route109_Text_LolaRematchIntro, Route109_Text_LolaRematchDefeated
	msgbox Route109_Text_LolaRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_EventScript_Austina:: @ 81EEB5D
	trainerbattle_single TRAINER_AUSTINA, Route109_Text_AustinaIntro, Route109_Text_AustinaDefeated
	msgbox Route109_Text_AustinaPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_EventScript_Gwen:: @ 81EEB74
	trainerbattle_single TRAINER_GWEN, Route109_Text_GwenIntro, Route109_Text_GwenDefeated
	msgbox Route109_Text_GwenPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_EventScript_Carter:: @ 81EEB8B
	trainerbattle_single TRAINER_CARTER, Route109_Text_CarterIntro, Route109_Text_CarterDefeated
	msgbox Route109_Text_CarterPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_EventScript_Paul:: @ 81EEBA2
	trainerbattle_double TRAINER_MEL_AND_PAUL, Route109_Text_PaulIntro, Route109_Text_PaulDefeated, Route109_Text_PaulNotEnoughPokemon
	msgbox Route109_Text_PaulPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_EventScript_Mel:: @ 81EEBBD
	trainerbattle_double TRAINER_MEL_AND_PAUL, Route109_Text_MelIntro, Route109_Text_MelDefeated, Route109_Text_MelNotEnoughPokemon
	msgbox Route109_Text_MelPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_EventScript_Chandler:: @ 81EEBD8
	trainerbattle_single TRAINER_CHANDLER, Route109_Text_ChandlerIntro, Route109_Text_ChandlerDefeated
	msgbox Route109_Text_ChandlerPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_EventScript_Hailey:: @ 81EEBEF
	trainerbattle_single TRAINER_HAILEY, Route109_Text_HaileyIntro, Route109_Text_HaileyDefeated
	msgbox Route109_Text_HaileyPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_EventScript_Elijah:: @ 81EEC06
	trainerbattle_single TRAINER_ELIJAH, Route109_Text_ElijahIntro, Route109_Text_ElijahDefeated
	msgbox Route109_Text_ElijahPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Text_BrineyLandedInSlateportDeliverGoods: @ 81EEC1D
	.string "하기: 호이! 잿빛도시에 도착!\p"
	.string "분명 해양씨한테\n"
	.string "데봉화물을 전달한다고 했었지!$"

Route109_Text_BrineySailToDewfordQuestion: @ 81EEC96
	.string "하기: 화물을 전달 안 하나?\p"
	.string "그게 아니면\n"
	.string "무로마을로 돌아가는 겐가?$"

Route109_Text_BrineyDewfordItIs: @ 81EED06
	.string "하기: 무로마을 말이지\p"
	.string "좋다! 가자 피코!$"

Route109_Text_BrineyDeliverDevonGoods: @ 81EED5E
	.string "하기: 그럼 화물을 전달하고 오게나\n"
	.string "난 여기서 기다리고 있을 테니$"

DewfordTown_Text_BrineyLandedInSlateport: @ 81EEDA7
	.string "하기: 호이! 잿빛도시에 도착!\p"
	.string "배를 타고 싶어지면\n"
	.string "언제든 나한테 말해 주게나!$"

Route109_Text_BrineyWhereAreWeBound: @ 81EEE17
	.string "하기: 여어! 자네가 원한다면\n"
	.string "언제든지 배를 준비시키지!\p"
	.string "자네가 가고 싶은 곳은 어딘가?$"

Route109_Text_BrineyTellMeWhenYouNeedToSail: @ 81EEE72
	.string "하기: 배를 타야 할 때는\n"
	.string "언제든지 말해 주게나$"

Route109_Text_ChillAtMyPapasSpot: @ 81EEEB4
	.string "뜨거운 트레이너 분들! 그리고\n"
	.string "뜨겁지 않은 트레이너 분들!\l"
	.string "모두 우리 아빠 가게에 들러주세요-!$"

Route109_Text_LittleKidsDartAround: @ 81EEF08
	.string "아이는 이곳저곳 돌아다니니까\n"
	.string "걱정이 돼서 눈을 뗄 수가 없어!\p"
	.string "그나마 포켓몬이 같이 있으니까\n"
	.string "괜찮을 거라고 생각하지만...$"

Route109_Text_SandCastleTakingLongTime: @ 81EEFB0
	.string "좀처럼 모래성이 완성이 안돼$"

Route109_Text_YouCanHaveThis: @ 81EEFDE
	.string "{K_GIRL_CALL}!\n"
	.string "이거 줄게!$"

Route109_Text_WereGoingToMakeBigCastle: @ 81EEFF1
	.string "모래사장에 있는 모래 전-부 모아서\n"
	.string "커-다란 성을 만들 거야\p"
	.string "그래서 우리는\n"
	.string "왕이랑 여왕이 될 거야\p"
	.string "{K_GIRL_CALL}는 특별히\n"
	.string "우리 신하 하게 해줄게$"

Route109_Text_ZigzagoonPicksUpLitter: @ 81EF080
	.string "이 주변 바다는 깨끗하긴 한데\p"
	.string "그래도 가끔 이렇게 버려지는\n"
	.string "쓰레기를 지그제구리가\l"
	.string "모아주고 있단다\p"
	.string "더러워진 물은 비가 돼서\n"
	.string "강으로 흘러 들어가\l"
	.string "마시는 물이 되지...\p"
	.string "결국 바다를 더럽히면\n"
	.string "피해를 보는 건\l"
	.string "자기 자신이란 소리일세$"

Route109_Text_ZigzagoonCry: @ 81EF173
	.string "지그제구리: 구구?$"

Route109_Text_SeashoreHouseSign: @ 81EF185
	.string "“바다의 집”\p"
	.string "모래사장 하면 또 포켓몬 승부지!\n"
	.string "뜨거운 트레이너들은 여기 모여라!$"

Route109_Text_TrainerTipsSign: @ 81EF1D5
	.string "정보 나눔 게시판!!\p"
	.string "포켓몬의 레벨이 같아도\n"
	.string "그 파워까지 같진 않아요!\p"
	.string "그리고 트레이너가 키운\n"
	.string "포켓몬이 더 강해진다고\l"
	.string "알려져 있지요!$"
