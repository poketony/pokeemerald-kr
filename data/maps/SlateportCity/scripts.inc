.set LOCALID_FAT_MAN, 1
.set LOCALID_MAN_1, 2
.set LOCALID_RICH_BOY, 3
.set LOCALID_GRUNT_1, 5
.set LOCALID_COOK, 6
.set LOCALID_OLD_WOMAN, 7
.set LOCALID_GIRL, 8
.set LOCALID_TY, 9
.set LOCALID_GABBY, 10
.set LOCALID_CAPT_STERN, 11
.set LOCALID_GRUNT_2, 18
.set LOCALID_GRUNT_3, 19
.set LOCALID_GRUNT_4, 26
.set LOCALID_GRUNT_5, 27
.set LOCALID_GRUNT_6, 28
.set LOCALID_GRUNT_7, 29
.set LOCALID_GRUNT_8, 30
.set LOCALID_GRUNT_9, 31
.set LOCALID_GRUNT_11, 33
.set LOCALID_SCOTT, 35

SlateportCity_MapScripts:: @ 81DCC61
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SlateportCity_OnFrame
	.byte 0

SlateportCity_OnTransition: @ 81DCC6C
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 0
	call SlateportCity_EventScript_EnterSlateport
	compare VAR_SLATEPORT_CITY_STATE, 1
	call_if_eq SlateportCity_EventScript_MovePeopleForSternInterview
	compare VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1
	call_if_eq SlateportCity_EventScript_SetReadyForScottScene
	end

SlateportCity_EventScript_EnterSlateport:: @ 81DCC8D
	setflag FLAG_VISITED_SLATEPORT_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_SLATEPORT_CITY_CONTEST_REPORTER
	return

SlateportCity_EventScript_MovePeopleForSternInterview:: @ 81DCC99
	setobjectxyperm LOCALID_CAPT_STERN, 28, 13
	setobjectxyperm LOCALID_OLD_WOMAN, 25, 13
	setobjectxyperm LOCALID_RICH_BOY, 25, 14
	setobjectxyperm LOCALID_COOK, 27, 16
	setobjectxyperm LOCALID_GIRL, 28, 16
	setobjectxyperm LOCALID_FAT_MAN, 29, 16
	setobjectxyperm LOCALID_MAN_1, 31, 14
	setobjectmovementtype LOCALID_CAPT_STERN, MOVEMENT_TYPE_FACE_DOWN
	setobjectmovementtype LOCALID_OLD_WOMAN, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT
	setobjectmovementtype LOCALID_RICH_BOY, MOVEMENT_TYPE_FACE_UP_AND_RIGHT
	setobjectmovementtype LOCALID_COOK, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_GIRL, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_FAT_MAN, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_MAN_1, MOVEMENT_TYPE_FACE_LEFT
	return

SlateportCity_EventScript_SetReadyForScottScene:: @ 81DCCE7
	setflag FLAG_HIDE_MAP_NAME_POPUP
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 30
	goto_if_eq SlateportCity_EventScript_MoveScottLeft
	setobjectxyperm LOCALID_SCOTT, 23, 27
	setobjectmovementtype LOCALID_SCOTT, MOVEMENT_TYPE_FACE_RIGHT
	return

SlateportCity_EventScript_MoveScottLeft:: @ 81DCD06
	setobjectxyperm LOCALID_SCOTT, 22, 27
	setobjectmovementtype LOCALID_SCOTT, MOVEMENT_TYPE_FACE_RIGHT
	return

SlateportCity_OnFrame: @ 81DCD12
	map_script_2 VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1, SlateportCity_EventScript_ScottScene
	.2byte 0

SlateportCity_EventScript_ScottScene:: @ 81DCD1C
	lockall
	addobject LOCALID_SCOTT
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_Movement_PlayerFaceScott
	applymovement LOCALID_SCOTT, SlateportCity_Movement_ScottApproachPlayer
	waitmovement 0
	msgbox SlateportCity_Text_YouDroveTeamAquaAway, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 60
	msgbox SlateportCity_Text_MaybeThisTrainer, MSGBOX_DEFAULT
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox SlateportCity_Text_LetsRegisterEachOther, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SlateportCity_Text_RegisteredScott, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_SCOTT_MATCH_CALL
	msgbox SlateportCity_Text_KeepEyeOnTrainersBeSeeingYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCOTT, SlateportCity_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_SCOTT
	setobjectxyperm LOCALID_SCOTT, 10, 12
	setobjectmovementtype LOCALID_SCOTT, MOVEMENT_TYPE_FACE_DOWN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 2
	addvar VAR_SCOTT_STATE, 1
	releaseall
	end

SlateportCity_Movement_PlayerFaceScott: @ 81DCDA8
	delay_16
	delay_8
	walk_in_place_fastest_left
	step_end

SlateportCity_Movement_ScottApproachPlayer: @ 81DCDAC
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_Movement_ScottExit: @ 81DCDB4
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_EventScript_EnergyGuru:: @ 81DCDBD
	lock
	faceplayer
	message SlateportCity_Text_EnergyGuruSellWhatYouNeed
	waitmessage
	pokemart SlateportCity_Pokemart_EnergyGuru
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_Pokemart_EnergyGuru: @ 81DCDD4
	.2byte ITEM_PROTEIN
	.2byte ITEM_IRON
	.2byte ITEM_CARBOS
	.2byte ITEM_ZINC
	.2byte ITEM_CALCIUM
	.2byte ITEM_HP_UP
	.2byte ITEM_NONE
	release
	end

SlateportCity_EventScript_EffortRibbonWoman:: @ 81DCDE4
	lock
	faceplayer
	bufferleadmonspeciesname 0
	msgbox SlateportCity_Text_OhYourPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, LeadMonHasEffortRibbon
	compare VAR_RESULT, TRUE
	call_if_eq SlateportCity_EventScript_MonHasEffortRibbon
	specialvar VAR_RESULT, Special_AreLeadMonEVsMaxedOut
	compare VAR_RESULT, FALSE
	call_if_eq SlateportCity_EventScript_MonEVsNotMaxed
	msgbox SlateportCity_Text_PleaseGiveItThisEffortRibbon, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_Text_ReceivedEffortRibbon
	waitfanfare
	msgbox SlateportCity_Text_PutEffortRibbonOnMon, MSGBOX_DEFAULT
	special GiveLeadMonEffortRibbon
	release
	end

SlateportCity_EventScript_MonEVsNotMaxed:: @ 81DCE2E
	msgbox SlateportCity_Text_GoForItLittleHarder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_MonHasEffortRibbon:: @ 81DCE38
	msgbox SlateportCity_Text_EffortRibbonLooksGoodOnIt, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Cook:: @ 81DCE42
	lock
	faceplayer
	compare VAR_SLATEPORT_CITY_STATE, 1
	call_if_eq SlateportCity_EventScript_CookSternInterview
	msgbox SlateportCity_Text_SeaweedFullOfLife, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_CookSternInterview:: @ 81DCE59
	msgbox SlateportCity_Text_CaptainComeBackWithBigFish, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_OldWoman:: @ 81DCE63
	lock
	faceplayer
	compare VAR_SLATEPORT_CITY_STATE, 1
	call_if_eq SlateportCity_EventScript_OldWomanSternInterview
	msgbox SlateportCity_Text_HowTownIsBornAndGrows, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_OldWomanSternInterview:: @ 81DCE7A
	msgbox SlateportCity_Text_CaptSternBeingInterviewed, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Girl:: @ 81DCE84
	lock
	faceplayer
	compare VAR_SLATEPORT_CITY_STATE, 1
	call_if_eq SlateportCity_EventScript_GirlSternInterview
	goto_if_set FLAG_RECEIVED_SECRET_POWER, SlateportCity_EventScript_GirlSecretBase
	msgbox SlateportCity_Text_SlateportWonderfulPlace, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_GirlSternInterview:: @ 81DCEA4
	msgbox SlateportCity_Text_InterviewerSoCool, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_GirlSecretBase:: @ 81DCEAE
	msgbox SlateportCity_Text_BuyBricksSoDecorWontGetDirty, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_RichBoy:: @ 81DCEB8
	lock
	faceplayer
	compare VAR_SLATEPORT_CITY_STATE, 1
	call_if_eq SlateportCity_EventScript_RichBoySternInterview
	msgbox SlateportCity_Text_GoingToCompeteInBattleTent, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_RichBoySternInterview:: @ 81DCECF
	msgbox SlateportCity_Text_SternSaysDiscoveredSomething, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_FatMan:: @ 81DCED9
	compare VAR_SLATEPORT_CITY_STATE, 1
	goto_if_eq SlateportCity_EventScript_FatManSternInterview
	msgbox SlateportCity_Text_BushedHikingFromMauville, MSGBOX_NPC
	end

SlateportCity_EventScript_FatManSternInterview:: @ 81DCEED
	msgbox SlateportCity_Text_AmIOnTV, MSGBOX_SIGN
	end

SlateportCity_EventScript_Man1:: @ 81DCEF6
	lock
	faceplayer
	compare VAR_SLATEPORT_CITY_STATE, 1
	call_if_eq SlateportCity_EventScript_Man1SternInterview
	msgbox SlateportCity_Text_EveryoneCallsHimCaptStern, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Man1SternInterview:: @ 81DCF0D
	msgbox SlateportCity_Text_CaptainsACelebrity, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman1:: @ 81DCF17
	lock
	faceplayer
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_EventScript_Woman1AquaGone
	msgbox SlateportCity_Text_WhatsLongLineOverThere, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman1AquaGone:: @ 81DCF2C
	msgbox SlateportCity_Text_VisitedMuseumOften, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_BattleTentSign:: @ 81DCF36
	msgbox SlateportCity_Text_BattleTentSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_SternsShipyardSign:: @ 81DCF3F
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_EventScript_SternsShipyardFerryComplete
	goto_if_set FLAG_BADGE07_GET, SlateportCity_EventScript_SternsShipyardNearsCompletion
	msgbox SlateportCity_Text_SternsShipyardWantedSign, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_SternsShipyardNearsCompletion:: @ 81DCF5C
	msgbox SlateportCity_Text_SternsShipyardNearsCompletion, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_SternsShipyardFerryComplete:: @ 81DCF66
	msgbox SlateportCity_Text_SternsShipyardFerryComplete, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_PokemonFanClubSign:: @ 81DCF70
	msgbox SlateportCity_Text_PokemonFanClubSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_OceanicMuseumSign:: @ 81DCF79
	msgbox SlateportCity_Text_OceanicMuseumSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_CitySign:: @ 81DCF82
	msgbox SlateportCity_Text_CitySign, MSGBOX_SIGN
	end

SlateportCity_EventScript_MarketSign:: @ 81DCF8B
	msgbox SlateportCity_Text_MarketSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_HarborSign:: @ 81DCF94
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_EventScript_HarborSignFerryComplete
	msgbox SlateportCity_Text_HarborFerryUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_HarborSignFerryComplete:: @ 81DCFA8
	msgbox SlateportCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_NameRatersHouseSign:: @ 81DCFB2
	msgbox SlateportCity_Text_NameRatersHouseSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_Maniac:: @ 81DCFBB
	lock
	faceplayer
	compare VAR_SLATEPORT_CITY_STATE, 1
	call_if_eq SlateportCity_EventScript_ManiacSternInterview
	msgbox SlateportCity_Text_GetNameRaterToHelpYou, MSGBOX_DEFAULT
	release
	end

@ Unclear if the text here was meant to be different, but its not
SlateportCity_EventScript_ManiacSternInterview:: @ 81DCFD2
	msgbox SlateportCity_Text_GetNameRaterToHelpYou, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman2:: @ 81DCFDC
	msgbox SlateportCity_Text_CantChangeTradeMonName, MSGBOX_NPC
	end

SlateportCity_EventScript_Sailor1:: @ 81DCFE5
	msgbox SlateportCity_Text_SeaIsSoWet, MSGBOX_NPC
	end

SlateportCity_EventScript_Sailor2:: @ 81DCFEE
	msgbox SlateportCity_Text_SinkOldBoats, MSGBOX_NPC
	end

SlateportCity_EventScript_PokefanF:: @ 81DCFF7
	msgbox SlateportCity_Text_BuyTooMuch, MSGBOX_NPC
	end

SlateportCity_EventScript_Man2:: @ 81DD000
	msgbox SlateportCity_Text_BattleTentBuiltRecently, MSGBOX_NPC
	end

SlateportCity_EventScript_AquaGrunt1:: @ 81DD009
	lock
	faceplayer
	msgbox SlateportCity_Text_QuitPushing, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt2:: @ 81DD020
	lock
	faceplayer
	msgbox SlateportCity_Text_AquaHasPolicy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt3:: @ 81DD037
	lock
	faceplayer
	msgbox SlateportCity_Text_BossIsBrilliant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt4:: @ 81DD04E
	lock
	faceplayer
	msgbox SlateportCity_Text_WhatsNewSchemeIWonder, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt5:: @ 81DD065
	lock
	faceplayer
	msgbox SlateportCity_Text_ShouldTakeItAll, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_5, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt6:: @ 81DD07C
	lock
	faceplayer
	msgbox SlateportCity_Text_DontButtIn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_6, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt7:: @ 81DD093
	lock
	faceplayer
	msgbox SlateportCity_Text_RemindsMeOfLongLineForGames, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_7, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt8:: @ 81DD0AA
	lock
	faceplayer
	msgbox SlateportCity_Text_WhyAreWeLiningUp, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_8, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt9:: @ 81DD0C1
	lock
	faceplayer
	playse SE_PIN
	applymovement LOCALID_GRUNT_9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_GRUNT_9, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_Text_WhatDoYouWant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement LOCALID_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	applymovement LOCALID_GRUNT_9, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_Text_IllReadSignForYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement LOCALID_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	msgbox SlateportCity_Text_SaysSomethingLikeSeaIsEndless, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_9, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	applymovement LOCALID_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_Movement_DelayAquaGrunt: @ 81DD147
	delay_16
	delay_16
	step_end

SlateportCity_EventScript_AquaGrunt10:: @ 81DD14A
	msgbox SlateportCity_Text_ShouldveBroughtMyGameBoy, MSGBOX_SIGN
	end

SlateportCity_EventScript_AquaGrunt11:: @ 81DD153
	lock
	faceplayer
	msgbox SlateportCity_Text_HotSpringsAfterOperation, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_11, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_DollClerk:: @ 81DD16A
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration SlateportCity_PokemartDecor_Dolls
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_PokemartDecor_Dolls: @ 81DD184
	.2byte DECOR_AZURILL_DOLL
	.2byte DECOR_MARILL_DOLL
	.2byte DECOR_SKITTY_DOLL
	.2byte DECOR_NONE
	release
	end

SlateportCity_EventScript_ComeBackWithSecretPower:: @ 81DD18E
	msgbox gText_ComeBackWithSecretPower, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_DecorClerk:: @ 81DD198
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_SECRET_POWER, SlateportCity_EventScript_ComeBackWithSecretPower
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration SlateportCity_PokemartDecor
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemartDecor: @ 81DD1B8
	.2byte DECOR_RED_BRICK
	.2byte DECOR_BLUE_BRICK
	.2byte DECOR_YELLOW_BRICK
	.2byte DECOR_RED_BALLOON
	.2byte DECOR_BLUE_BALLOON
	.2byte DECOR_YELLOW_BALLOON
	.2byte DECOR_C_LOW_NOTE_MAT
	.2byte DECOR_D_NOTE_MAT
	.2byte DECOR_E_NOTE_MAT
	.2byte DECOR_F_NOTE_MAT
	.2byte DECOR_G_NOTE_MAT
	.2byte DECOR_A_NOTE_MAT
	.2byte DECOR_B_NOTE_MAT
	.2byte DECOR_C_HIGH_NOTE_MAT
	.2byte DECOR_NONE
	release
	end

SlateportCity_EventScript_PowerTMClerk:: @ 81DD1D8
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart SlateportCity_Pokemart_PowerTMs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_PowerTMs: @ 81DD1F0
	.2byte ITEM_TM10  @ Hidden Power
	.2byte ITEM_TM43  @ Secret Power
	.2byte ITEM_NONE
	release
	end

@ Scene with Capt Sterns interview and Team Aqua announcing plans to steal Submarine
SlateportCity_EventScript_CaptStern:: @ 81DD1F8
	lockall
	msgbox SlateportCity_Text_SternMoveAheadWithExploration, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_GabbyWonderfulThanksForInterview, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GABBY, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 10
	applymovement LOCALID_TY, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 25
	applymovement LOCALID_CAPT_STERN, SlateportCity_Movement_SternWatchGabbyAndTyExit
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_Movement_PlayerFaceStern
	applymovement LOCALID_GABBY, SlateportCity_Movement_GabbyExit
	applymovement LOCALID_TY, SlateportCity_Movement_TyExit
	waitmovement 0
	removeobject LOCALID_GABBY
	removeobject LOCALID_TY
	msgbox SlateportCity_Text_SternWhewFirstInterview, MSGBOX_DEFAULT
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox SlateportCity_Text_OhPlayerWeMadeDiscovery, MSGBOX_DEFAULT
	playbgm MUS_ENCOUNTER_AQUA, 0
	msgbox SlateportCity_Text_AquaWillAssumeControlOfSubmarine, MSGBOX_DEFAULT
	applymovement LOCALID_COOK, Common_Movement_WalkInPlaceFastestLeft
	applymovement LOCALID_FAT_MAN, Common_Movement_WalkInPlaceFastestLeft
	applymovement LOCALID_OLD_WOMAN, SlateportCity_Movement_OldWomanConcern
	applymovement LOCALID_RICH_BOY, Common_Movement_QuestionMark
	applymovement LOCALID_MAN_1, SlateportCity_Movement_ManConcern
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox SlateportCity_Text_SternWhatWasAllThat, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_CAPT_STERN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox SlateportCity_Text_FromHarborTryingToTakeSub, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_PleaseComeWithMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CAPT_STERN, SlateportCity_Movement_SternEnterHarbor
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_Movement_PlayerEnterHarbor
	waitmovement 0
	removeobject LOCALID_CAPT_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_CAPTAIN_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_SUBMARINE_SHADOW
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_AQUA_GRUNT
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_ARCHIE
	setvar VAR_SLATEPORT_CITY_STATE, 2
	warp MAP_SLATEPORT_CITY_HARBOR, 255, 11, 14
	waitstate
	releaseall
	end

SlateportCity_Movement_OldWomanConcern: @ 81DD309
	delay_16
	delay_16
	emote_question_mark
	walk_in_place_fastest_right
	delay_16
	delay_16
	walk_in_place_fastest_left
	step_end

SlateportCity_Movement_ManConcern: @ 81DD311
	emote_question_mark
	walk_in_place_fastest_up
	delay_16
	walk_in_place_fastest_down
	delay_16
	delay_16
	walk_in_place_fastest_left
	step_end

SlateportCity_Movement_GabbyExit: @ 81DD319
	delay_16
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_Movement_TyExit: @ 81DD326
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_Movement_Unused: @ 81DD334
	walk_down
	walk_in_place_fastest_up
	step_end

SlateportCity_Movement_SternEnterHarbor: @ 81DD337
	walk_right
	walk_up
	walk_up
	set_invisible
	step_end

SlateportCity_Movement_SternWatchGabbyAndTyExit: @ 81DD33C
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_down
	walk_left
	step_end

SlateportCity_Movement_PlayerEnterHarbor: @ 81DD344
	walk_in_place_fastest_right
	delay_16
	delay_16
	walk_right
	walk_up
	step_end

SlateportCity_Movement_PlayerFaceStern: @ 81DD34A
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_fastest_down
	step_end

SlateportCity_EventScript_Ty:: @ 81DD353
	msgbox SlateportCity_Text_BigSmileForCamera, MSGBOX_SIGN
	end

SlateportCity_EventScript_Gabby:: @ 81DD35C
	msgbox SlateportCity_Text_MostInvaluableExperience, MSGBOX_SIGN
	end

SlateportCity_EventScript_Man3:: @ 81DD365
	msgbox SlateportCity_Text_WonderIfLighthouseStartlesPokemon, MSGBOX_NPC
	end

SlateportCity_EventScript_BerryPowderClerk:: @ 81DD36E
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POWDER_JAR, SlateportCity_EventScript_ReceivedPowderJar
	msgbox SlateportCity_Text_ExplainBerries, MSGBOX_DEFAULT
	giveitem ITEM_POWDER_JAR
	setflag FLAG_RECEIVED_POWDER_JAR
	msgbox SlateportCity_Text_ExplainBerryPowder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ReceivedPowderJar:: @ 81DD39A
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, HasEnoughBerryPowder
	compare VAR_RESULT, FALSE
	goto_if_eq SlateportCity_EventScript_ExplainBerryPowder
	msgbox SlateportCity_Text_BroughtMeSomeBerryPowder, MSGBOX_DEFAULT
	special DisplayBerryPowderVendorMenu
	goto SlateportCity_EventScript_ChooseBerryPowderItem
	end

SlateportCity_EventScript_ExplainBerryPowder:: @ 81DD3C0
	msgbox SlateportCity_Text_ExplainBerryPowder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ChooseBerryPowderItem:: @ 81DD3CA
	message SlateportCity_Text_ExchangeWhatWithIt
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BERRY_POWDER_VENDOR
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, SlateportCity_EventScript_EnergyPowder
	case 1, SlateportCity_EventScript_EnergyRoot
	case 2, SlateportCity_EventScript_HealPowder
	case 3, SlateportCity_EventScript_RevivalHerb
	case 4, SlateportCity_EventScript_Protein
	case 5, SlateportCity_EventScript_Iron
	case 6, SlateportCity_EventScript_Carbos
	case 7, SlateportCity_EventScript_Calcium
	case 8, SlateportCity_EventScript_Zinc
	case 9, SlateportCity_EventScript_HPUp
	case 10, SlateportCity_EventScript_PPUp
	case 11, SlateportCity_EventScript_CancelPowderItemSelect
	case MULTI_B_PRESSED, SlateportCity_EventScript_CancelPowderItemSelect
	end

SlateportCity_EventScript_EnergyPowder:: @ 81DD46E
	bufferitemname 0, ITEM_ENERGY_POWDER
	setvar VAR_0x8008, ITEM_ENERGY_POWDER
	setvar VAR_0x8009, 50
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_EnergyRoot:: @ 81DD482
	bufferitemname 0, ITEM_ENERGY_ROOT
	setvar VAR_0x8008, ITEM_ENERGY_ROOT
	setvar VAR_0x8009, 80
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_HealPowder:: @ 81DD496
	bufferitemname 0, ITEM_HEAL_POWDER
	setvar VAR_0x8008, ITEM_HEAL_POWDER
	setvar VAR_0x8009, 50
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_RevivalHerb:: @ 81DD4AA
	bufferitemname 0, ITEM_REVIVAL_HERB
	setvar VAR_0x8008, ITEM_REVIVAL_HERB
	setvar VAR_0x8009, 300
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Protein:: @ 81DD4BE
	bufferitemname 0, ITEM_PROTEIN
	setvar VAR_0x8008, ITEM_PROTEIN
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Iron:: @ 81DD4D2
	bufferitemname 0, ITEM_IRON
	setvar VAR_0x8008, ITEM_IRON
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Carbos:: @ 81DD4E6
	bufferitemname 0, ITEM_CARBOS
	setvar VAR_0x8008, ITEM_CARBOS
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Calcium:: @ 81DD4FA
	bufferitemname 0, ITEM_CALCIUM
	setvar VAR_0x8008, ITEM_CALCIUM
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Zinc:: @ 81DD50E
	bufferitemname 0, ITEM_ZINC
	setvar VAR_0x8008, ITEM_ZINC
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_HPUp:: @ 81DD522
	bufferitemname 0, ITEM_HP_UP
	setvar VAR_0x8008, ITEM_HP_UP
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_PPUp:: @ 81DD536
	bufferitemname 0, ITEM_PP_UP
	setvar VAR_0x8008, ITEM_PP_UP
	setvar VAR_0x8009, 3000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_CancelPowderItemSelect:: @ 81DD54A
	msgbox SlateportCity_Text_ComeBackToTradeBerryPowder, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_TryBuyBerryPowderItem:: @ 81DD557
	msgbox SlateportCity_Text_ExchangeBerryPowderForItem, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SlateportCity_EventScript_ChooseBerryPowderItem
	copyvar VAR_0x8004, VAR_0x8009
	specialvar VAR_RESULT, HasEnoughBerryPowder
	compare VAR_RESULT, FALSE
	goto_if_eq SlateportCity_EventScript_NotEnoughBerryPowder
	giveitem VAR_0x8008
	compare VAR_RESULT, FALSE
	goto_if_eq SlateportCity_EventScript_NoRoomForBerryPowderItem
	copyvar VAR_0x8004, VAR_0x8009
	special TakeBerryPowder
	special PrintPlayerBerryPowderAmount
	msgbox SlateportCity_Text_FineBerryPowderTradeSomethingElse, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SlateportCity_EventScript_ChooseBerryPowderItem
	msgbox SlateportCity_Text_WhenYouGetMoreBringItToMe, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_NoRoomForBerryPowderItem:: @ 81DD5C1
	msgbox gText_TheBagIsFull, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_NotEnoughBerryPowder:: @ 81DD5CE
	msgbox SlateportCity_Text_DontHaveEnoughBerryPowder, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_ChooseBerryPowderItem
	end

SlateportCity_EventScript_ScottBattleTentScene:: @ 81DD5DC
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	opendoor 10, 12
	waitdooranim
	addobject LOCALID_SCOTT
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_Movement_PushPlayerDown
	applymovement LOCALID_SCOTT, SlateportCity_Movement_ScottExitBattleTent
	waitmovement 0
	closedoor 10, 12
	waitdooranim
	msgbox SlateportCity_Text_TakingBattleTentChallenge, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, SlateportCity_Movement_ScottExitAfterBattleTent
	waitmovement 0
	removeobject LOCALID_SCOTT
	addvar VAR_SCOTT_STATE, 1
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 3
	releaseall
	end

SlateportCity_Movement_PushPlayerDown: @ 81DD630
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

SlateportCity_Movement_PlayerWatchScottExit: @ 81DD634
	delay_16
	walk_in_place_fastest_right
	step_end

SlateportCity_Movement_ScottExitBattleTent: @ 81DD637
	delay_8
	walk_down
	step_end

SlateportCity_Movement_ScottExitAfterBattleTent: @ 81DD63A
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_EventScript_BerryCrushRankingsSign:: @ 81DD643
	lockall
	special ShowBerryCrushRankings
	waitstate
	releaseall
	end

SlateportCity_Text_EnergyGuruSellWhatYouNeed: @ 81DD64A
	.string "나는 노력가! 열심히 노력해서\n"
	.string "여러 가지를 팔지요!$"

SlateportCity_Text_OhYourPokemon: @ 81DD68A
	.string "어머?\n"
	.string "네 {STR_VAR_1}...$"

SlateportCity_Text_PleaseGiveItThisEffortRibbon: @ 81DD697
	.string "엄청 노력했구나!\p"
	.string "상으로\n"
	.string "이 노력리본을 달아 줘!$"

SlateportCity_Text_ReceivedEffortRibbon: @ 81DD6E3
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "노력리본을 받았다!$"

SlateportCity_Text_PutEffortRibbonOnMon: @ 81DD702
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "노력리본을\l"
	.string "{STR_VAR_1}에게 달아 줬다!$"

SlateportCity_Text_GoForItLittleHarder: @ 81DD722
	.string "좀 더 노력해봐!\p"
	.string "열심히 노력하면 내가 포켓몬한테\n"
	.string "좋은 걸 줄게!$"

SlateportCity_Text_EffortRibbonLooksGoodOnIt: @ 81DD77B
	.string "오! 네 {STR_VAR_1}\n"
	.string "노력리본이 잘 어울린다!$"

SlateportCity_Text_WonderIfLighthouseStartlesPokemon: @ 81DD7AD
	.string "등대의 불빛은\n"
	.string "수십 킬로 떨어진 곳에서도 보여\p"
	.string "바닷속에 있는 포켓몬 너무\n"
	.string "눈부셔서 놀라거나 하지 않을까?$"

SlateportCity_Text_SeaweedFullOfLife: @ 81DD81A
	.string "여기 한번 보세요!\p"
	.string "이 근방에서 딴 해초는\n"
	.string "신선하고 팔팔하답니다!\l"
	.string "당장이라도 덮쳐 올 것 같아요!$"

SlateportCity_Text_HowTownIsBornAndGrows: @ 81DD8A6
	.string "물이 맑은 곳에\n"
	.string "많은 열매가 열리고\p"
	.string "사람들이 많이 가는 곳에\n"
	.string "시장이 생긴다...\p"
	.string "이렇게 마을은 점점 커져가는 거야$"

SlateportCity_Text_SlateportWonderfulPlace: @ 81DD93D
	.string "바다의 향기가 나는 곳에서\n"
	.string "쇼핑을 할 수 있다니...\p"
	.string "잿빛도시는 정말 멋진 곳이야!$"

SlateportCity_Text_BuyBricksSoDecorWontGetDirty: @ 81DD999
	.string "봉제인형이나 쿠션은\n"
	.string "바닥에 놔두면 더러워지잖아?\p"
	.string "그래서 봉제인형이나 쿠션이\n"
	.string "더러워지지 않도록\l"
	.string "올려 둘 수 있는 벽돌을 사러 왔어!$"

SlateportCity_Text_GoingToCompeteInBattleTent: @ 81DDA34
	.string "우오-! 배틀텐트에\n"
	.string "나도 출전해야지-!\p"
	.string "일단 그 전에!\n"
	.string "포켓몬 잡아 와야지!$"
	// うぉ-! バトルテントにｎ
	// ぼくも しゅつじょう するぞお-!ｐ
	// と そのまえに!ｎ
	// ポケモン つかまえて こなくちゃ!

SlateportCity_Text_BushedHikingFromMauville: @ 81DDA9A
	.string "후우 후우...\p"
	.string "난 보라시티에서\n"
	.string "여기까지 걸어서 왔는데\l"
	.string "이 마을 무지 넓네...\p"
	.string "이럴 줄 알았으면\n"
	.string "자전거 타고 올 걸 그랬어!$"
	// ふぅ ふぅ……ｐ
	// おれは キンセツシティ からｎ
	// あるいて ここまで きたんだけどｌ
	// この まちって ひろいなぁ……ｐ
	// こんな ことなら じてんしゃにｎ
	// のって くれば よかったよ!

SlateportCity_Text_EveryoneCallsHimCaptStern: @ 81DDB21
	.string "이 박물관을 만든\n"
	.string "해양이라는 사람은\p"
	.string "해저 조사대\n"
	.string "리더이기도 해!\p"
	.string "아무튼 사람들은 그를\n"
	.string "해양관장이라고 부르고 있어!$"
	// この はくぶつかんを つくったのはｎ
	// クスノキさん といってｐ
	// かいていを たんさくする せんすいていのｎ
	// かんちょう でも あるんだ!ｐ
	// せんすいていの かんちょうでｎ
	// はくぶつかんの かんちょう……ｐ
	// まあ どっちにせよｎ
	// クスノキかんちょう と よんでおけばｌ
	// まちがい ないよな!

SlateportCity_Text_WhatsLongLineOverThere: @ 81DDBAC
	.string "뭐지 저 줄은\n"
	.string "뭔 일 있나?$"
	// なんなのかしらｎ
	// あの ぎょうれつ?

SlateportCity_Text_VisitedMuseumOften: @ 81DDBD5
	.string "이 박물관에는\n"
	.string "나도 어렸을 때 많이 왔어요\p"
	.string "여기 전시된 전시품을 보고\n"
	.string "바다의 신비를 동경했었죠$"
	// この はくぶつかん にはｎ
	// こどもの ころ わたしも よく きましたｐ
	// かんないの てんじひんを みてｎ
	// うみの しんぴに あこがれた ものです

SlateportCity_Text_QuitPushing: @ 81DDC4F
	.string "잠깐 너! 밀지 마!\n"
	.string "순서 지켜야지!$"
	// ちょっと あんた! おさないでよ!ｎ
	// じゅんばん なんだから!

SlateportCity_Text_AquaHasPolicy: @ 81DDC8A
	.string "우리 아쿠아단의 기본 방침은\n"
	.string "“현지 집합” 그리고\l"
	.string "“현지 해산”이다!$"
	// おれたち アクアだんの ポリシ-はｎ
	// 「げんち しゅうごう」 そしてｌ
	// 「げんち かいさん」 なんだぜ!

SlateportCity_Text_BossIsBrilliant: @ 81DDCD5
	.string "리더같이 똑똑하신 분이\n"
	.string "이제 와서 박물관에는\l"
	.string "무슨 볼일이지...?$"
	// リ-ダ-ほど あたまの いい ひとがｎ
	// いまさら はくぶつかんにｌ
	// なんの ようじが あるんだ……?

SlateportCity_Text_WhatsNewSchemeIWonder: @ 81DDD18
	.string "이번 작전은 뭐지?\p"
	.string "리더를 화나게 만들면 무서우니까\n"
	.string "절대 실패하고 싶지 않아...$"
	// こんどの さくせんは なんだろう?ｐ
	// リ-ダ-を おこらせると こわいからｎ
	// しっぱい したくないぜ……

SlateportCity_Text_ShouldTakeItAll: @ 81DDD7D
	.string "박물관 안에 갖고 싶은 게 있으면\n"
	.string "아예 통째로 뺏어버리면 될 텐데...$"
	// はくぶつかんに ほしいもの あるならｎ
	// まるごと うばっちゃえば いいのに……

SlateportCity_Text_DontButtIn: @ 81DDDC0
	.string "어이 거기!\n"
	.string "순서 지켜라!$"
	// おい こら!ｎ
	// じゅんばん ぬかすなよ!

SlateportCity_Text_RemindsMeOfLongLineForGames: @ 81DDDDF
	.string "이런 줄을 보면\p"
	.string "엄청난 인기였던 게임을 샀을 때를\n"
	.string "떠올리게 되네...$"
	// ぎょうれつ というとｎ
	// だいにんきの ゲ-ムを かったときをｌ
	// おもいだすなあ……

SlateportCity_Text_WhyAreWeLiningUp: @ 81DDE2F
	.string "착실하게 돈 내지 말고\n"
	.string "억지로 그냥 들어가면 될 텐데!$"
	// まじめに おかね はらわずにｎ
	// むりやり はいれば いいのによ!

SlateportCity_Text_WhatDoYouWant: @ 81DDE6E
	.string "뭐야 뭐야!?$"
	// なんだ なんだ!?

SlateportCity_Text_IllReadSignForYou: @ 81DDE86
	.string "너 이 간판이 읽고 싶은 거야?\n"
	.string "그럼 내가 대신 읽어줄게!$"
	// おまえ このカンバンが よみたいのか?ｎ
	// なら オレが かわりに よんでやらぁ!

SlateportCity_Text_SaysSomethingLikeSeaIsEndless: @ 81DDEB8
	.string "음- 어디 보자...\p"
	.string "“없는 그것은 의 근”\p"
	.string "...이라고 적혀 있어!$"
	// え-と……ｐ
	// 『てしない それは の の』ｐ
	// ……って かいて あるぜ!

SlateportCity_Text_ShouldveBroughtMyGameBoy: @ 81DDF32
	.string "중얼중얼...\p"
	.string "게임보이가 있으면\n"
	.string "긴 줄도 지루하지 않아\p"
	.string "중얼중얼...$"
	// ぶつぶつぶつ……ｐ
	// ゲ-ムボ-イが あればｎ
	// ぎょうれつも たいくつ しないぜｐ
	// ぶつぶつぶつ……

SlateportCity_Text_HotSpringsAfterOperation: @ 81DDF8D
	.string "이 작전이 끝나면\n"
	.string "온천에 데려가 주마!\p"
	.string "라고 리더가 말했어\n"
	.string "좋을 거야...$"
	// このさくせんが おわったらｎ
	// おんせんに つれていって やる!ｐ
	// って リ-ダ-が いってたんだｎ
	// たのしみ だなぁ……

SlateportCity_Text_SeaIsSoWet: @ 81DDFF7
	.string "바다는 정말 넓어...\p"
	.string "혹시 바다는\n"
	.string "포켓몬이 흘린 눈물로\l"
	.string "되어 있는 걸까....$"
	// うみって おおきいなあ……ｐ
	// ひょっとして うみってｎ
	// ポケモンが ながした なみだでｌ
	// できてるのかなあ……

SlateportCity_Text_SinkOldBoats: @ 81DE04B
	.string "오래 돼서 탈 수 없게 된 배가\n"
	.string "어떻게 되는지 알고 있나?\p"
	.string "바닷속에 가라앉혀서\n"
	.string "포켓몬의 거처가 되도록 하는 거야!$"
	// ふるく なって のれない ふねはｎ
	// どうするか しって いるかね?ｐ
	// うみの そこに しずめてｎ
	// ポケモンの すみかに してやるのだよ!

SlateportCity_Text_BuyTooMuch: @ 81DE0D2
	.string "여기 오면 너무 좋아서\n"
	.string "나도 모르게 많이 사 버려!$"
	// ここに くると うれしくてｎ
	// つい たくさん かいもの しちゃう!

SlateportCity_Text_GetNameRaterToHelpYou: @ 81DE10E
	.string "포켓몬의 닉네임을 바꾸고 싶다면\n"
	.string "이 마을에 살고 있는\l"
	.string "이름 감정사한테 부탁하면 돼!$"
	// ポケモンの ニックネ-ムを かえたいならｎ
	// せいめい はんだんしに たのむんだね!

SlateportCity_Text_CantChangeTradeMonName: @ 81DE16C
	.string "다른 사람이랑 교환한 포켓몬은\n"
	.string "닉네임을 바꿀 수 없어!\p"
	.string "왜냐하면 닉네임은 지어준 사람의\n"
	.string "마음이 담겨 있으니까!$"
	// ひとと こうかんした ポケモンはｎ
	// ニックネ-ムを かえられないわよ!ｐ
	// だって つけた ひとの きもちがｎ
	// こめられて いるんですもの!

SlateportCity_Text_BattleTentBuiltRecently: @ 81DE1EC
	.string "최근 잿빛도시에\n"
	.string "배틀텐트가 생겼어\l"
	.string "체육관도 좋지만 배틀텐트도 좋지!\p"
	.string "너도 강한 포켓몬을 찾으러\n"
	.string "한번 가 봐!$"
	// さいきん カイナにはｎ
	// バトルテントが できたんだｌ
	// ジムも いいけど バトルテントも いいぜ!ｐ
	// おまえも つよい ポケモン さがしにｎ
	// いって みなよ!

SlateportCity_Text_CaptSternBeingInterviewed: @ 81DE28E
	.string "유명한 스타가 온 줄 알고\n"
	.string "사인 받으려고 했는데\p"
	.string "인터뷰하고 있는 사람\n"
	.string "어라...? 해양관장 아냐?$"
	// ゆうめいな スタ-が きていたらｎ
	// サインを もらうつもり だったのにｐ
	// インタビュ- されてるのはｎ
	// あれ…… クスノキさん でないかい?

SlateportCity_Text_InterviewerSoCool: @ 81DE30C
	.string "저 인터뷰어 언니\n"
	.string "미인에다가 멋있기까지 해!\p"
	.string "나도 크면\n"
	.string "국제 저널리스트가 될 거야!$"
	// あの インタビュア-の おねえさんｎ
	// かっこよくて びじん!ｐ
	// あたしも おおきく なったらｎ
	// こくさい ジャ-ナリストに なるわ!

SlateportCity_Text_SternSaysDiscoveredSomething: @ 81DE376
	.string "해양관장이 바닷속에서\n"
	.string "무언가를 발견했다나 봐!\p"
	.string "그게 뭘까? 뭘까?$"
	// クスノキかんちょうは うみの そこでｎ
	// なにかを はっけん したんだって!ｐ
	// なんだろな-? なんだろな-?

SlateportCity_Text_CaptainComeBackWithBigFish: @ 81DE3E2
	.string "뭐야 뭐야!?\p"
	.string "관장이 바다에서\n"
	.string "대물이라도 낚아 올린 거야?$"
	// なんだ なんだ!?ｐ
	// かんちょうは うみの そこからｎ
	// おおもの でも つりあげたのか?

SlateportCity_Text_AmIOnTV: @ 81DE43D
	.string "얘들아-! 보고 있어-?\n"
	.string "나 TV에 잘 나오고 있니-?$"
	// みんな-! みてるか-!ｎ
	// おれも テレビに うつってるか-?

SlateportCity_Text_CaptainsACelebrity: @ 81DE460
	.string "방송국에서 취재하러 오다니\n"
	.string "관장도 유명인이 다 됐네!$"
	// テレビが しゅざいに くる なんてｎ
	// かんちょうも ゆうめいじん ですなあ!

SlateportCity_Text_BigSmileForCamera: @ 81DE491
	.string "다이: 자 해양씨\n"
	.string "거기서 웃으세요!$"
	// ダイ『はい クスノキさんｎ
	// そこで えがお!

SlateportCity_Text_MostInvaluableExperience: @ 81DE4C4
	.string "마리: 아... 그렇군요...\n"
	.string "참 귀중한 경험을 하셨네요...$"
	// マリ『なるほど なるほど それはｎ
	// きちょうな たいけんを なさいましたね……

SlateportCity_Text_SternMoveAheadWithExploration: @ 81DE502
	.string "해양: ...그럼 앞으로도\n"
	.string "조사는 계속해 나갈게요!$"
	// クスノキ『……というわけで こんごもｎ
	// ちょうさは つづけて いきますよ!

SlateportCity_Text_GabbyWonderfulThanksForInterview: @ 81DE54A
	.string "마리: 그렇군요 아 그럼 해양씨!\n"
	.string "오늘 바쁘신데 시간 내주셔서\l"
	.string "정말 감사합니다!\p"
	.string "또 뭔가 발견하시면\n"
	.string "다시 취재하러 오겠습니다!$"
	// マリ『そうですか いやあ クスノキさん!ｎ
	// きょうは おいそがしい ところｌ
	// どうも ありがとう ございました!ｐ
	// また なにか はっけんが ありましたらｎ
	// ぜひ しゅざい させて くださいね!

SlateportCity_Text_SternWhewFirstInterview: @ 81DE5F7
	.string "해양: 후우...\p"
	.string "방송국 카메라에 찍히는 건\n"
	.string "태어나서 처음이라 긴장했어!$"
	// クスノキ『ふう……ｐ
	// テレビカメラに うつされる なんてｎ
	// はじめて だったから きんちょう したよ!

SlateportCity_Text_OhPlayerWeMadeDiscovery: @ 81DE64F
	.string "오! {PLAYER}!\n"
	.string "잘 지내는 것 같네!\p"
	.string "이번 해저 조사에서\n"
	.string "엄청난 발견을 했어!\p"
	.string "128번 수로에서\n"
	.string "아주 먼 옛날에 멸종된 걸로 알려진\l"
	.string "포켓몬의 둥지로 추정되는\l"
	.string "해저동굴을 찾...$"
	// おっ! §あ§おｎ
	// げんきそう だね!ｐ
	// こんかいの かいてい ちょうさでｎ
	// すごい はっけんを したんだよ!ｐ
	// 128ばん すいどうでｎ
	// おおむかしに ぜつめつ したと いわれるｌ
	// ポケモンの すみかと おもわれるｌ
	// かいてい どうくつを みつけた……

SlateportCity_Text_AquaWillAssumeControlOfSubmarine: @ 81DE724
	.string "“후후후...\n"
	.string "해양관장이라는 자여\p"
	.string "네놈의 잠수정은\n"
	.string "우리 아쿠아단이 가져가겠다!\p"
	.string "너희들은 우리에게 잠자코\n"
	.string "협력하면 되는 거다!\p"
	.string "후후후...\n"
	.string "지금부터 아쿠아단이 뭘 하는지\l"
	.string "기대하고 있도록!”$"
	// 『フフフ……ｎ
	// クスノキかんちょう とやらｐ
	// きみの せんすいていはｎ
	// われわれ アクアだんが いただく!ｐ
	// きみたちは われわれに だまってｎ
	// きょうりょく すれば いいのだよ!ｐ
	// フフフ……ｎ
	// これから アクアだんが なにを するかｌ
	// たのしみに していたまえ!』

SlateportCity_Text_SternWhatWasAllThat: @ 81DE7F7
	.string "해양: 방금 목소리는...?\p"
	.string "누가 확성기를 써서...\n"
	.string "어디서 말하고 있는 거지...?$"
	// クスノキ『いまの こえは……?ｐ
	// だれかが かくせいきを つかって……ｐ
	// どこから はなしてるんだ……?

SlateportCity_Text_FromHarborTryingToTakeSub: @ 81DE860
	.string "선착장 안이야!\p"
	.string "잠수정을...\n"
	.string "빼앗으려고 하고 있어...?$"
	// ふねのりばの なか!ｐ
	// せんすいていが…… うばわれる……?

SlateportCity_Text_PleaseComeWithMe: @ 81DE8A0
	.string "{PLAYER}!\n"
	.string "함께 와 줘! 부탁해!$"
	// §あ§お!ｎ
	// いっしょに きてくれ!

SlateportCity_Text_BattleTentSign: @ 81DE8BC
	.string "배틀텐트 잿빛도시 회장\n"
	.string "찾아라! 최강 포켓몬$"
	// バトルテント カイナシティ かいじょうｎ
	// さがせ! さいきょう ポケモン

SlateportCity_Text_SternsShipyardWantedSign: @ 81DE8F8
	.string "“해양조선소”\p"
	.string "파도를 자유자재로 조종하는 선원\n"
	.string "모집 중!$"
	// 「クスノキ ぞうせんじょ」ｐ
	// なみを じざいに あやつる ふなのりｎ
	// だいぼしゅう してます!

SlateportCity_Text_SternsShipyardNearsCompletion: @ 81DE940
	.string "“해양조선소”\p"
	.string "잿빛도시와 해안시티를 연결하는\n"
	.string "연락선 타이드립호는\l"
	.string "완성이 이제 눈앞에!$"
	// 「クスノキ ぞうせんじょ」ｐ
	// カイナと ミナモを むすぶｎ
	// れんらくせん タイドリップごうはｌ
	// かんせい まで あと わずか!

SlateportCity_Text_SternsShipyardFerryComplete: @ 81DE9AA
	.string "“해양조선소”\p"
	.string "연락선 타이드립호에\n"
	.string "승선을 희망하는 분은\l"
	.string "배 타는 곳의 접수처로 오세요!$"
	// 「クスノキ ぞうせんじょ」ｐ
	// れんらくせん タイドリップごうにｎ
	// じょうせんを きぼう される かたはｌ
	// ふねのりば うけつけ まで どうぞ!

SlateportCity_Text_PokemonFanClubSign: @ 81DEA0B
	.string "“포켓몬 애호가클럽”\p"
	.string "포켓몬을 좋아하는 사람\n"
	.string "모두 모여라!$"
	// 「ポケモン だいすきクラブ」ｎ
	// ポケモンが すきなひと みんな あつまれ!

SlateportCity_Text_OceanicMuseumSign: @ 81DEA3B
	.string "끝없는 바다...\n"
	.string "그것은 생명의 근원...\p"
	.string "“바다의 과학박물관”$"
	// はてしない うみ……ｎ
	// それは いのちの みなもと……ｐ
	// 「うみの かがく はくぶつかん」

SlateportCity_Text_CitySign: @ 81DEA6F
	.string "여기는 잿빛도시\n"
	.string "사람과 포켓몬이 왕래하는 항구$"
	// ここは カイナ シティｎ
	// ヒトと ポケモンが いきかう みなと

SlateportCity_Text_MarketSign: @ 81DEAAF
	.string "“잿빛시장”\p"
	.string "여기서밖에\n"
	.string "구할 수 없는 물건 한가득!$"
	// 「カイナ いちば」ｎ
	// ここでしか かえない もの たくさん!

SlateportCity_Text_HarborFerryUnderConstruction: @ 81DEAE3
	.string "“잿빛도시 배 타는 곳”\p"
	.string "연락선 타이드립호는\n"
	.string "조선소에서 건조 중!\p"
	.string "조금만 더 기다려 주세요!$"
	// 「カイナ シティ ふねのりば」ｐ
	// れんらくせん タイドリップごう はｎ
	// ぞうせんじょ にて けんぞう ちゅう!ｐ
	// もう しばらく おまちください!

SlateportCity_Text_HarborSign: @ 81DEB5A
	.string "“잿빛도시 배 타는 곳”\p"
	.string "연락선 타이드립호로\n"
	.string "신나는 배여행을 즐겨 주세요!$"
	// 「カイナ シティ ふねのりば」ｐ
	// れんらくせん タイドリップごうでｎ
	// ふねの たびを おたのしみ ください!

SlateportCity_Text_NameRatersHouseSign: @ 81DEBA0
	.string "“이름 감정사의 집”\n"
	.string "포켓몬의 이름을 점칩니다$"
	// 「せいめい はんだんし の いえ」ｎ
	// ポケモンの なまえ うらないます

SlateportCity_Text_ExplainBerries: @ 81DEBCE
	.string "상처 입은 야생의 포켓몬은\n"
	.string "나무열매를 먹어서 부상을 치료해\p"
	.string "알고 있었어?\p"
	.string "그걸 목격한 누군가가\n"
	.string "나무열매로 약을\l"
	.string "만들자는 생각을 했지\p"
	.string "알고 있었어?\p"
	.string "나무열매를 약으로 바꾸려면\n"
	.string "산산조각으로 부숴\l"
	.string "가루로 만든다는 걸\p"
	.string "알고 있었어?\p"
	.string "당신...\n"
	.string "나무열매에 흥미가 있구나!\p"
	.string "좋은 걸 줄게$"
	// きずついた やせいの ポケモンはｎ
	// きのみを かじって けがを なおすのｐ
	// しってた?ｐ
	// それを もくげきした だれかがｎ
	// きのみから くすりを つくることをｌ
	// おもいついたのｐ
	// しってた?ｐ
	// きのみを くすりに するためにはｎ
	// こなごなに くだいて こなにするのｐ
	// しってた?ｐ
	// あなた……ｎ
	// きのみに きょうみが ありそうね!ｐ
	// いいものを あげるわ

SlateportCity_Text_ExplainBerryPowder: @ 81DED27
	.string "최근 포켓몬센터의 2층에\n"
	.string "다이렉트 코너라는 곳에\l"
	.string "나무열매를 부수는 기계를\l"
	.string "설치해 놨어\p"
	.string "알고 있었어?\p"
	.string "그곳에서 나무열매 가루를\n"
	.string "만들 수 있어!\p"
	.string "나무열매 가루를\n"
	.string "잔뜩 만들어 오면\l"
	.string "여러 약을 줄게$"
	// さいきん ポケモンセンタ-の 2かいのｎ
	// ダイレクト コ-ナ- というところにｌ
	// きのみを つぶす きかいをｌ
	// おいて もらったのｐ
	// しってた?ｐ
	// そこで きのみの こなを つくってきて!ｐ
	// きのみの こなをｎ
	// たくさん つくって きてくれたらｌ
	// いろいろな くすりを あげるわ

SlateportCity_Text_BroughtMeSomeBerryPowder: @ 81DEE40
	.string "나무열매 가루를 가져왔어?$"
	// きのみの こなを もってきたの?

SlateportCity_Text_ExchangeWhatWithIt: @ 81DEE67
	.string "뭐하고 교환할래?$"
	// なにと こうかん しましょ?

SlateportCity_Text_ExchangeBerryPowderForItem: @ 81DEE90
	.string "{STR_VAR_1}{K_WAGWA}\n"
	.string "교환할래?$"
	// §い とｎ
	// こうかん するのね?

SlateportCity_Text_DontHaveEnoughBerryPowder: @ 81DEEC9
	.string "어라라!?\n"
	.string "가루가 부족한 거 아냐?$"
	// あれま!?ｎ
	// こなが たりない じゃないの!

SlateportCity_Text_FineBerryPowderTradeSomethingElse: @ 81DEEF7
	.string "꽤 괜찮은 가루네!\p"
	.string "당신이 준 가루로\n"
	.string "또 좋은 약을 만들 수 있겠어!\p"
	.string "또 교환할 거 있어?$"
	// まあ いいこな だこと!ｐ
	// あなたが くれた こなでｎ
	// また いいくすりを つくれるわ!ｐ
	// ほかにも なにか こうかんする?

SlateportCity_Text_WhenYouGetMoreBringItToMe: @ 81DEF79
	.string "그래\n"
	.string "가루가 생기면 다시 잘 부탁할게!$"
	// そうｎ
	// こなが できたら また よろしくね!

SlateportCity_Text_ComeBackToTradeBerryPowder: @ 81DEFBC
	.string "약과 교환하고 싶으면\n"
	.string "다시 여기로 와\p"
	.string "나는 언제나\n"
	.string "가게를 열고 있으니까\p"
	.string "알고 있었어?$"
	// くすりと こうかん したくなったらｎ
	// また ここに くるのよｐ
	// わたしが いつもｎ
	// おみせ だしてるから ねｐ
	// しってた?

SlateportCity_Text_YouDroveTeamAquaAway: @ 81DF032
	.string "금작화: ...어라?\n"
	.string "너하고는 전에 어딘가에서 만났지\p"
	.string "자기소개를 했었던가?\n"
	.string "나는 금작화라고 해\p"
	.string "지금 여기서 아쿠아단이\n"
	.string "도망치는 걸 봤는데\p"
	.string "혹시 네가 해치운 거야?$"
	// エニシダ『……あれ?ｎ
	// きみとは まえに どこかで あったよねｐ
	// じこしょうかい したっけ?ｎ
	// わたしは エニシダ って いうんだｐ
	// いま ここから アクアだんがｎ
	// にげだして いったけどｌ
	// もしかして きみが やっつけたの かい?

SlateportCity_Text_MaybeThisTrainer: @ 81DF0FE
	.string "금작화: 으-음 이건\n"
	.string "설마 설마...$"
	// エニシダ『う-む これはｎ
	// ひょっとして ひょっとすると……

SlateportCity_Text_LetsRegisterEachOther: @ 81DF12B
	.string "금작화: ...좋아!\n"
	.string "너하고는 친해지고 싶으니까\l"
	.string "서로 포켓내비에\l"
	.string "이름을 등록해 두자!\p"
	.string "...... ...... ......$"
	// エニシダ『……よっし!ｎ
	// きみとは なかよく なれそう だからｌ
	// おたがい ポケナビにｌ
	// なまえを とうろく しておこう!ｐ
	// …… …… ……

SlateportCity_Text_RegisteredScott: @ 81DF1A6
	.string "금작화라고 하는 사람을\n"
	.string "포켓내비에 등록했다!$"
	// エニシダ という ひとをｎ
	// ポケナビに とうろく した!

SlateportCity_Text_KeepEyeOnTrainersBeSeeingYou: @ 81DF1D3
	.string "금작화: 사실은 너에 대해서\n"
	.string "자세히 알고 싶지만\l"
	.string "다른 사람의 재능도 신경 쓰이고\p"
	.string "조금 더 여러 마을을\n"
	.string "방문해 보려고!\p"
	.string "그럼 안녕 {PLAYER}{K_AYA}!$"
	// エニシダ『ホントは きみにｎ
	// くっついて いきたい ところ だけどｌ
	// ほかのひとの さいのうも きになるしｐ
	// もうすこし いろんな まちをｎ
	// たずね あるいて みるよ!ｐ
	// じゃあね §あ§お!

SlateportCity_Text_TakingBattleTentChallenge: @ 81DF28C
	.string "금작화: 오 이런\n"
	.string "{PLAYER}{K_I}구나!\p"
	.string "...혹시 {PLAYER}\n"
	.string "배틀텐트에 도전할 생각이야?\p"
	.string "음! 그거 좋지!\n"
	.string "엄청 좋은 생각이야!\l"
	.string "배틀텐트에는 강한 트레이너가\l"
	.string "어울리니까!\p"
	.string "그럼 힘내!$"
	// エニシダ『お おおっとｎ
	// §あ§おか!ｐ
	// ……もしかして §あ§おｎ
	// バトルテントに ちょうせん するのかい?ｐ
	// うん! それは いいことだな!ｎ
	// ものすごく いいことだ!ｌ
	// バトルテントには つよい トレ-ナ-がｌ
	// とっても ふさわしい からねｐ
	// じゃ がんばってね!
