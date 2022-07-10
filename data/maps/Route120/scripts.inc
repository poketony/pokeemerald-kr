.set LOCALID_BRIDGE_KECLEON, 30
.set LOCALID_STEVEN, 31
.set LOCALID_BRIDGE_KECLEON_SHADOW, 36  @ They use a second object which is identical to Kecleon but has a reflection palette tag for the bridge shadow

Route120_MapScripts:: @ 81F53EC
	map_script MAP_SCRIPT_ON_RESUME, Route120_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route120_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route120_OnLoad
	.byte 0

Route120_OnResume: @ 81F53FC
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Route120_EventScript_RemoveKecleonObject
	end

Route120_EventScript_RemoveKecleonObject:: @ 81F5406
	compare VAR_0x8009, 0
	call_if_eq Route120_EventScript_RemoveBridgeKecleon
	compare VAR_0x8009, 1
	call_if_eq Route120_EventScript_RemoveKecleon
	compare VAR_0x8009, 2
	call_if_eq Route120_EventScript_RemoveKecleon
	compare VAR_0x8009, 3
	call_if_eq Route120_EventScript_RemoveKecleon
	compare VAR_0x8009, 4
	call_if_eq Route120_EventScript_RemoveKecleon
	compare VAR_0x8009, 5
	call_if_eq Route120_EventScript_RemoveKecleon
	return

Route120_EventScript_RemoveBridgeKecleon:: @ 81F5449
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne Common_EventScript_NopReturn
	removeobject LOCALID_BRIDGE_KECLEON
	removeobject LOCALID_BRIDGE_KECLEON_SHADOW
	return

Route120_EventScript_RemoveKecleon:: @ 81F5460
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

Route120_OnLoad: @ 81F5474
	call_if_unset FLAG_REGI_DOORS_OPENED, Route120_EventScript_CloseAncientTomb
	call_if_set FLAG_RECEIVED_DEVON_SCOPE, Route120_EventScript_SetBridgeClearMetatiles
	call_if_unset FLAG_RECEIVED_DEVON_SCOPE, Route120_EventScript_SetBridgeKecleonMovement
	end

Route120_EventScript_CloseAncientTomb:: @ 81F5490
	setmetatile 7, 54, METATILE_General_RockWall_RockBase, 1
	setmetatile 7, 55, METATILE_General_RockWall_SandBase, 1
	return

Route120_EventScript_SetBridgeClearMetatiles:: @ 81F54A3
	setmetatile 13, 15, METATILE_Fortree_WoodBridge1_Top, 0
	setmetatile 12, 16, METATILE_Fortree_WoodBridge1_Bottom, 0
	setmetatile 12, 17, METATILE_General_ReflectiveWater, 0
	setmetatile 13, 17, METATILE_General_ReflectiveWater, 0
	return

Route120_EventScript_SetBridgeKecleonMovement:: @ 81F54C8
	setobjectmovementtype LOCALID_BRIDGE_KECLEON_SHADOW, MOVEMENT_TYPE_FACE_RIGHT
	return

Route120_OnTransition: @ 81F54CD
	call GabbyAndTy_EventScript_UpdateLocation
	call Route120_EventScript_SetWeather
	end

Route120_EventScript_SetWeather:: @ 81F54D8
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	compare VAR_TEMP_1, 14
	goto_if_le Route120_EventScript_SetSunnyWeather
	compare VAR_TEMP_1, 60
	goto_if_le Route120_EventScript_TrySetRainyWeather
	compare VAR_TEMP_1, 61
	goto_if_ge Route120_EventScript_SetCloudyWeather
	return

Route120_EventScript_SetCloudyWeather:: @ 81F54FF
	setweather WEATHER_SUNNY_CLOUDS
	return

Route120_EventScript_SetSunnyWeather:: @ 81F5503
	setweather WEATHER_SUNNY
	return

Route120_EventScript_TrySetRainyWeather:: @ 81F5507
	compare VAR_TEMP_0, 7
	goto_if_le Route120_EventScript_SetRainyWeather
	compare VAR_TEMP_0, 19
	goto_if_le Route120_EventScript_SetSunnyWeather
	goto Route120_EventScript_SetRainyWeather
	end

Route120_EventScript_SetRainyWeather:: @ 81F5523
	setweather WEATHER_RAIN
	return

Route120_EventScript_BerryBeauty:: @ 81F5527
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_ROUTE_120_RECEIVED_BERRY, Route120_EventScript_ReceivedBerry
	msgbox Route120_Text_BerriesExpressionOfLoveIsntIt, MSGBOX_YESNO
	compare VAR_RESULT, YES
	call_if_eq Route120_EventScript_BerryLove
	compare VAR_RESULT, NO
	call_if_eq Route120_EventScript_BerryNotLove
	specialvar VAR_RESULT, GetPlayerTrainerIdOnesDigit
	switch VAR_RESULT
	case 0, Route120_EventScript_GiveFigyBerry
	case 5, Route120_EventScript_GiveFigyBerry
	case 1, Route120_EventScript_GiveWikiBerry
	case 6, Route120_EventScript_GiveWikiBerry
	case 2, Route120_EventScript_GiveMagoBerry
	case 7, Route120_EventScript_GiveMagoBerry
	case 3, Route120_EventScript_GiveAguavBerry
	case 8, Route120_EventScript_GiveAguavBerry
	case 4, Route120_EventScript_GiveIapapaBerry
	case 9, Route120_EventScript_GiveIapapaBerry
	end

Route120_EventScript_GiveFigyBerry:: @ 81F55CA
	setvar VAR_0x8004, ITEM_FIGY_BERRY
	goto Route120_EventScript_GiveBerry
	end

Route120_EventScript_GiveWikiBerry:: @ 81F55D5
	setvar VAR_0x8004, ITEM_WIKI_BERRY
	goto Route120_EventScript_GiveBerry
	end

Route120_EventScript_GiveMagoBerry:: @ 81F55E0
	setvar VAR_0x8004, ITEM_MAGO_BERRY
	goto Route120_EventScript_GiveBerry
	end

Route120_EventScript_GiveAguavBerry:: @ 81F55EB
	setvar VAR_0x8004, ITEM_AGUAV_BERRY
	goto Route120_EventScript_GiveBerry
	end

Route120_EventScript_GiveIapapaBerry:: @ 81F55F6
	setvar VAR_0x8004, ITEM_IAPAPA_BERRY
	goto Route120_EventScript_GiveBerry
	end

Route120_EventScript_GiveBerry:: @ 81F5601
	giveitem VAR_0x8004
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_ROUTE_120_RECEIVED_BERRY
	msgbox Route120_Text_BerryIsRareRaiseItWithCare, MSGBOX_DEFAULT
	release
	end

Route120_EventScript_ReceivedBerry:: @ 81F5625
	msgbox Route120_Text_IllGetMoreBerriesFromBerryMaster, MSGBOX_DEFAULT
	release
	end

Route120_EventScript_BerryLove:: @ 81F562F
	msgbox Route120_Text_YesYouUnderstand, MSGBOX_DEFAULT
	return

Route120_EventScript_BerryNotLove:: @ 81F5638
	msgbox Route120_Text_MakeYourOwnImpressions, MSGBOX_DEFAULT
	return

Route120_EventScript_Steven:: @ 81F5641
	lock
	faceplayer
	goto_if_set FLAG_NOT_READY_FOR_BATTLE_ROUTE_120, Route120_EventScript_StevenAskReadyForBattle
	msgbox Route120_Text_StevenGreeting, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route120_EventScript_StevenNotReady
	goto Route120_EventScript_StevenBattleKecleon
	end

Route120_EventScript_StevenNotReady:: @ 81F5665
	msgbox Route120_Text_StevenIllWaitHere, MSGBOX_DEFAULT
	setflag FLAG_NOT_READY_FOR_BATTLE_ROUTE_120
	release
	end

Route120_EventScript_StevenAskReadyForBattle:: @ 81F5672
	msgbox Route120_Text_StevenReadyForBattle, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route120_EventScript_StevenNotReady
	goto Route120_EventScript_StevenBattleKecleon
	end

Route120_EventScript_StevenBattleKecleon:: @ 81F568B
	msgbox Route120_Text_StevenShowMeYourPower, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_NORTH
	call_if_eq Route120_EventScript_PlayerApproachKecleonNorth
	compare VAR_FACING, DIR_WEST
	call_if_eq Route120_EventScript_PlayerApproachKecleonWest
	applymovement LOCALID_STEVEN, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 20
	msgbox Route120_Text_StevenUsedDevonScope, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BRIDGE_KECLEON, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement LOCALID_BRIDGE_KECLEON, Movement_KecleonAppears
	waitmovement 0
	waitse
	playmoncry SPECIES_KECLEON, 2
	delay 40
	waitmoncry
	setwildbattle SPECIES_KECLEON, 30, ITEM_NONE
	setvar VAR_0x8009, 0
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Route120_EventScript_RemoveBridgeKecleonPostBattle
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq Route120_EventScript_RemoveBridgeKecleonPostBattle
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq Route120_EventScript_RemoveBridgeKecleonPostBattle
	goto Route120_EventScript_StevenGiveDeconScope
	end

Route120_EventScript_RemoveBridgeKecleonPostBattle:: @ 81F571C
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_BRIDGE_KECLEON
	removeobject LOCALID_BRIDGE_KECLEON_SHADOW
	fadescreenswapbuffers FADE_FROM_BLACK
	goto Route120_EventScript_StevenGiveDeconScope
	end

Route120_EventScript_StevenGiveDeconScope:: @ 81F572C
	applymovement LOCALID_STEVEN, Common_Movement_WalkInPlaceFastestDown
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox Route120_Text_StevenGiveDevonScope, MSGBOX_DEFAULT
	giveitem ITEM_DEVON_SCOPE
	setflag FLAG_RECEIVED_DEVON_SCOPE
	msgbox Route120_Text_StevenGoodbye, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_STEVEN, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_STEVEN
	waitfieldeffect FLDEFF_NPCFLY_OUT
	setmetatile 13, 15, METATILE_Fortree_WoodBridge1_Top, 0
	setmetatile 12, 16, METATILE_Fortree_WoodBridge1_Bottom, 0
	setmetatile 12, 17, METATILE_General_ReflectiveWater, 0
	setmetatile 13, 17, METATILE_General_ReflectiveWater, 0
	special DrawWholeMapView
	release
	end

Route120_EventScript_PlayerApproachKecleonNorth:: @ 81F57A3
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

Route120_EventScript_PlayerApproachKecleonWest:: @ 81F57AE
	applymovement OBJ_EVENT_ID_PLAYER, Route120_Movement_ApproachKecleonWest
	waitmovement 0
	return

Route120_Movement_ApproachKecleonWest: @ 81F57B9
	walk_down
	walk_left
	step_end

Route120_EventScript_BridgeKecleon:: @ 81F57BC
	msgbox Kecleon_Text_SomethingUnseeable, MSGBOX_NPC
	end

Route120_EventScript_RouteSignFortree:: @ 81F57C5
	msgbox Route120_Text_RouteSignFortree, MSGBOX_SIGN
	end

Route120_EventScript_RouteSign121:: @ 81F57CE
	msgbox Route120_Text_RouteSign121, MSGBOX_SIGN
	end

Route120_EventScript_Colin:: @ 81F57D7
	trainerbattle_single TRAINER_COLIN, Route120_Text_ColinIntro, Route120_Text_ColinDefeat
	msgbox Route120_Text_ColinPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Robert:: @ 81F57EE
	trainerbattle_single TRAINER_ROBERT_1, Route120_Text_RobertIntro, Route120_Text_RobertDefeat, Route120_EventScript_RegisterRobert
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route120_EventScript_RematchRobert
	msgbox Route120_Text_RobertPostBattle, MSGBOX_DEFAULT
	release
	end

Route120_EventScript_RegisterRobert:: @ 81F581A
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route120_Text_RobertRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ROBERT_1
	release
	end

Route120_EventScript_RematchRobert:: @ 81F5839
	trainerbattle_rematch TRAINER_ROBERT_1, Route120_Text_RobertRematchIntro, Route120_Text_RobertRematchDefeat
	msgbox Route120_Text_RobertPostRematch, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Lorenzo:: @ 81F5850
	trainerbattle_single TRAINER_LORENZO, Route120_Text_LorenzoIntro, Route120_Text_LorenzoDefeat
	msgbox Route120_Text_LorenzoPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Jenna:: @ 81F5867
	trainerbattle_single TRAINER_JENNA, Route120_Text_JennaIntro, Route120_Text_JennaDefeat
	msgbox Route120_Text_JennaPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Jeffrey:: @ 81F587E
	trainerbattle_single TRAINER_JEFFREY_1, Route120_Text_JeffreyIntro, Route120_Text_JeffreyDefeat, Route120_EventScript_RegisterJeffrey
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route120_EventScript_RematchJeffrey
	msgbox Route120_Text_JeffreyPostBattle, MSGBOX_DEFAULT
	release
	end

Route120_EventScript_RegisterJeffrey:: @ 81F58AA
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route120_Text_JeffreyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JEFFREY_1
	release
	end

Route120_EventScript_RematchJeffrey:: @ 81F58C9
	trainerbattle_rematch TRAINER_JEFFREY_1, Route120_Text_JeffreyRematchIntro, Route120_Text_JeffreyRematchDefeat
	msgbox Route120_Text_JeffreyPostRematch, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Jennifer:: @ 81F58E0
	trainerbattle_single TRAINER_JENNIFER, Route120_Text_JenniferIntro, Route120_Text_JenniferDefeat
	msgbox Route120_Text_JenniferPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Chip:: @ 81F58F7
	trainerbattle_single TRAINER_CHIP, Route120_Text_ChipIntro, Route120_Text_ChipDefeat
	msgbox Route120_Text_ChipPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Clarissa:: @ 81F590E
	trainerbattle_single TRAINER_CLARISSA, Route120_Text_ClarissaIntro, Route120_Text_ClarissaDefeat
	msgbox Route120_Text_ClarissaPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Angelica:: @ 81F5925
	trainerbattle_single TRAINER_ANGELICA, Route120_Text_AngelicaIntro, Route120_Text_AngelicaDefeat
	msgbox Route120_Text_AngelicaPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Keigo:: @ 81F593C
	trainerbattle_single TRAINER_KEIGO, Route120_Text_KeigoIntro, Route120_Text_KeigoDefeat
	msgbox Route120_Text_KeigoPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Riley:: @ 81F5953
	trainerbattle_single TRAINER_RILEY, Route120_Text_RileyIntro, Route120_Text_RileyDefeat
	msgbox Route120_Text_RileyPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Leonel:: @ 81F596A
	trainerbattle_single TRAINER_LEONEL, Route120_Text_LeonelIntro, Route120_Text_LeonelDefeat
	msgbox Route120_Text_LeonelPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Callie:: @ 81F5981
	trainerbattle_single TRAINER_CALLIE, Route120_Text_CallieIntro, Route120_Text_CallieDefeat
	msgbox Route120_Text_CalliePostBattle, MSGBOX_AUTOCLOSE
	end

Route120_Text_StevenGreeting: @ 81F5998
	.string "성호: 응? {PLAYER}{K_I}구나\n"
	.string "오랜만이네\p"
	.string "여기에 보이지 않는 무언가가 있지?\p"
	.string "그 보이지 않는 무언가에게\n"
	.string "이 도구를 쓰면...\p"
	.string "아니지... 설명하는 것보다\n"
	.string "실제로 써보는 편이 재미있겠어\p"
	.string "{PLAYER} 너의 포켓몬\n"
	.string "승부할 준비는 돼 있나?$"

Route120_Text_StevenIllWaitHere: @ 81F5AAC
	.string "성호: 그래?\p"
	.string "나는 여기서 기다리고 있을 테니\n"
	.string "준비를 하도록 해$"

Route120_Text_StevenReadyForBattle: @ 81F5ADE
	.string "성호: {PLAYER} 너의 포켓몬\n"
	.string "승부할 준비는 돼 있나?$"

Route120_Text_StevenShowMeYourPower: @ 81F5B0F
	.string "성호: {PLAYER}\n"
	.string "너의 트레이너로서의\l"
	.string "실력을 보여줘!$"

Route120_Text_StevenUsedDevonScope: @ 81F5B43
	.string "성호는\n"
	.string "데봉스코프를 사용했다!\p"
	.string "투명했던 포켓몬의 모습이\n"
	.string "훤히 보이게 됐다!\p"
	.string "포켓몬은\n"
	.string "놀라서 덤벼들었다!$"

Route120_Text_StevenGiveDevonScope: @ 81F5BAF
	.string "성호: 역시\n"
	.string "너의 배틀 방식은 재미있구나\p"
	.string "처음에 무로마을에서 만났을 때보다\n"
	.string "포켓몬도 성장해 있고...\p"
	.string "그렇지\n"
	.string "이 데봉스코프는 너에게 줄게\p"
	.string "또 모습을 숨기고 있는\n"
	.string "포켓몬이 있을지도 모르니까$"

Route120_Text_StevenGoodbye: @ 81F5C7B
	.string "성호: {PLAYER}\p"
	.string "나는 열심히 하는\n"
	.string "트레이너와 포켓몬을 좋아하지\p"
	.string "그래서 너도 좋아해\p"
	.string "그럼\n"
	.string "다시 어딘가에서 만나자!$"

Kecleon_Text_SomethingUnseeable: @ 81F5D00
	.string "보이지 않는 무언가가 있는 것 같다$"

Kecleon_Text_WantToUseDevonScope: @ 81F5D23
	.string "보이지 않는 무언가가 있는 것 같다\p"
	.string "데봉스코프를 사용하겠습니까?$"

Kecleon_Text_UseDevonScopeMonAttacked: @ 81F5D63
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "데봉스코프를 사용했다!\p"
	.string "투명했던 포켓몬의 모습이\n"
	.string "훤히 보이게 됐다!\p"
	.string "포켓몬은\n"
	.string "놀라서 덤벼들었다!$"

Route120_Text_RouteSignFortree: @ 81F5DCB
	.string "여기는 120번 도로\n"
	.string "{LEFT_ARROW} 검방울시티$"

Route120_Text_RouteSign121: @ 81F5DE4
	.string "{RIGHT_ARROW} 121번 도로\n"
	.string "{LEFT_ARROW} 120번 도로$"
