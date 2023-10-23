.set LOCALID_LITTLE_BOY, 7
.set LOCALID_LITTLE_GIRL, 8
.set LOCALID_DEVON_EMPLOYEE, 9
.set LOCALID_GRUNT, 10
.set LOCALID_RIVAL, 14
.set LOCALID_SCIENTIST, 15

RustboroCity_MapScripts:: @ 81E06BD
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_OnFrame
	.byte 0

RustboroCity_OnTransition: @ 81E06C8
	setflag FLAG_VISITED_RUSTBORO_CITY
	call Common_EventScript_SetupRivalGfxId
	compare VAR_RUSTBORO_CITY_STATE, 6
	call_if_eq RustboroCity_EventScript_HideMapNamePopup
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	compare VAR_RUSTBORO_CITY_STATE, 6
	goto_if_eq RustboroCity_EventScript_PositionScientistForExit
	end

RustboroCity_EventScript_PositionScientistForExit:: @ 81E06EC
	compare VAR_TEMP_0, 11
	goto_if_eq RustboroCity_EventScript_PositionScientistLeftExit
	setobjectxyperm LOCALID_SCIENTIST, 12, 15
	end

RustboroCity_EventScript_PositionScientistLeftExit:: @ 81E06FF
	setobjectxyperm LOCALID_SCIENTIST, 11, 15
	end

RustboroCity_EventScript_HideMapNamePopup:: @ 81E0707
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

RustboroCity_OnFrame: @ 81E070B
	map_script_2 VAR_RUSTBORO_CITY_STATE, 6, RustboroCity_EventScript_ScientistAddMatchCall
	.2byte 0

RustboroCity_EventScript_ScientistAddMatchCall:: @ 81E0715
	lockall
	setvar VAR_ROUTE104_STATE, 1
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_Movement_PlayerWalkDown
	waitmovement 0
	playse SE_EXIT
	delay 10
	addobject LOCALID_SCIENTIST
	applymovement LOCALID_SCIENTIST, RustboroCity_Movement_ScientistApproachPlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	applymovement LOCALID_SCIENTIST, RustboroCity_Movement_ScientistWalkInPlaceDown
	waitmovement 0
	msgbox RustboroCity_Text_DevelopedNewPokenavFeature, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HAS_MATCH_CALL
	applymovement LOCALID_SCIENTIST, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 20
	applymovement LOCALID_SCIENTIST, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox RustboroCity_Text_AddedMatchCallPleaseCallMrStone, MSGBOX_DEFAULT
	closemessage
	delay 20
	goto RustboroCity_EventScript_MatchCallTutorial

RustboroCity_EventScript_PleaseSelectPokenav:: @ 81E07AC
	msgbox RustboroCity_Text_PleaseSelectPokenav, MSGBOX_DEFAULT
	closemessage
	delay 10
	goto RustboroCity_EventScript_MatchCallTutorial

RustboroCity_EventScript_MatchCallTutorial:: @ 81E07BD
	setflag FLAG_ADDED_MATCH_CALL_TO_POKENAV
	special ScriptMenu_CreateStartMenuForPokenavTutorial
	waitstate
	switch VAR_RESULT
	case 0, RustboroCity_EventScript_PleaseSelectPokenav
	case 1, RustboroCity_EventScript_PleaseSelectPokenav
	case 2, RustboroCity_EventScript_PleaseSelectPokenav
	case 4, RustboroCity_EventScript_PleaseSelectPokenav
	case 5, RustboroCity_EventScript_PleaseSelectPokenav
	case 6, RustboroCity_EventScript_PleaseSelectPokenav
	case 7, RustboroCity_EventScript_PleaseSelectPokenav
	case MULTI_B_PRESSED, RustboroCity_EventScript_PleaseSelectPokenav
	special OpenPokenavForTutorial
	waitstate
	delay 20
	msgbox RustboroCity_Text_IdBetterGetBackToWork, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCIENTIST, RustboroCity_Movement_ScientistLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_SCIENTIST
	setflag FLAG_HIDE_RUSTBORO_CITY_SCIENTIST
	setvar VAR_RUSTBORO_CITY_STATE, 7
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	releaseall
	end

RustboroCity_Movement_ScientistWalkInPlaceDown: @ 81E084E
	walk_in_place_down
	step_end

RustboroCity_Movement_PlayerWalkDown: @ 81E0850
	walk_down
	step_end

RustboroCity_Movement_ScientistApproachPlayer: @ 81E0852
	walk_down
	delay_16
	step_end

@ Unused
RustboroCity_Movement_ScientistWalkAroundPlayer: @ 81E0855
	delay_16
	walk_left
	walk_down
	walk_down
	walk_right
	walk_in_place_fastest_up
	delay_16
	step_end

RustboroCity_Movement_ScientistLeave: @ 81E085D
	walk_up
	step_end

RustboroCity_EventScript_FatMan:: @ 81E085F
	lock
	faceplayer
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_EventScript_FatManSawGrunt
	msgbox RustboroCity_Text_WeShortenItToDevon, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_FatManSawGrunt:: @ 81E0874
	msgbox RustboroCity_Text_SneakyLookingManWentAroundCorner, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_DevonEmployee2:: @ 81E087E
	lock
	faceplayer
	msgbox RustboroCity_Text_YoureNewAroundHere, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_Woman:: @ 81E088A
	msgbox RustboroCity_Text_GymLeaderIsntEasyWithFire, MSGBOX_NPC
	end

RustboroCity_EventScript_Man1:: @ 81E0893
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, RustboroCity_EventScript_Man1HaveBadge
	msgbox RustboroCity_Text_HaveYouChallengedGym, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_Man1HaveBadge:: @ 81E08A8
	msgbox RustboroCity_Text_HeyThatsRustborosGymBadge, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_Boy2:: @ 81E08B2
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POKENAV, RustboroCity_EventScript_Boy2BrineyLeftTunnel
	msgbox RustboroCity_Text_MrBrineyWalksInTheTunnel, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_Boy2BrineyLeftTunnel:: @ 81E08C7
	msgbox RustboroCity_Text_MrBrineyLovesPeeko, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_Twin:: @ 81E08D1
	msgbox RustboroCity_Text_WowYouHavePokemon, MSGBOX_NPC
	end

RustboroCity_EventScript_NinjaBoy:: @ 81E08DA
	msgbox RustboroCity_Text_CatchRarePokemonIfIGoToSchool, MSGBOX_SIGN
	end

RustboroCity_EventScript_TunnelSign:: @ 81E08E3
	msgbox RustboroCity_Text_TunnelNearingCompletion, MSGBOX_SIGN
	end

RustboroCity_EventScript_DevonCorpSign:: @ 81E08EC
	msgbox RustboroCity_Text_DevonCorpSign, MSGBOX_SIGN
	end

RustboroCity_EventScript_GymSign:: @ 81E08F5
	msgbox RustboroCity_Text_GymSign, MSGBOX_SIGN
	end

@ Unused
RustboroCity_EventScript_DevonCorpBranchOfficeSign:: @ 81E08FE
	msgbox RustboroCity_Text_DevonCorpBranchOfficeSign, MSGBOX_SIGN
	end

RustboroCity_EventScript_CitySign:: @ 81E0907
	msgbox RustboroCity_Text_CitySign, MSGBOX_SIGN
	end

RustboroCity_EventScript_TrainersSchoolSign:: @ 81E0910
	msgbox RustboroCity_Text_TrainersSchoolSign, MSGBOX_SIGN
	end

RustboroCity_EventScript_CuttersHouseSign:: @ 81E0919
	msgbox RustboroCity_Text_CuttersHouse, MSGBOX_SIGN
	end

RustboroCity_EventScript_LittleBoy:: @ 81E0922
	lock
	faceplayer
	msgbox RustboroCity_Text_PokemonCanChangeLookFromExp, MSGBOX_DEFAULT
	applymovement LOCALID_LITTLE_BOY, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_EventScript_LittleGirl:: @ 81E0938
	lock
	faceplayer
	msgbox RustboroCity_Text_PokemonChangeShape, MSGBOX_DEFAULT
	applymovement LOCALID_LITTLE_GIRL, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_EventScript_Man2:: @ 81E094E
	lock
	faceplayer
	msgbox RustboroCity_Text_TradePokemonGrowFast, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_StolenGoodsTrigger0:: @ 81E095A
	lockall
	setobjectxyperm LOCALID_DEVON_EMPLOYEE, 14, 21
	setobjectmovementtype LOCALID_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 0
	goto RustboroCity_EventScript_StolenGoodsScene
	end

RustboroCity_EventScript_StolenGoodsTrigger1:: @ 81E0971
	lockall
	setobjectxyperm LOCALID_DEVON_EMPLOYEE, 14, 21
	setobjectmovementtype LOCALID_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 1
	goto RustboroCity_EventScript_StolenGoodsScene
	end

RustboroCity_EventScript_StolenGoodsTrigger2:: @ 81E0988
	lockall
	setobjectxyperm LOCALID_DEVON_EMPLOYEE, 14, 21
	setobjectmovementtype LOCALID_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 2
	goto RustboroCity_EventScript_StolenGoodsScene
	end

RustboroCity_EventScript_StolenGoodsTrigger3:: @ 81E099F
	lockall
	setobjectxyperm LOCALID_DEVON_EMPLOYEE, 14, 21
	setobjectmovementtype LOCALID_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 3
	goto RustboroCity_EventScript_StolenGoodsScene
	end

RustboroCity_EventScript_StolenGoodsTrigger4:: @ 81E09B6
	lockall
	setobjectxyperm LOCALID_DEVON_EMPLOYEE, 14, 21
	setobjectmovementtype LOCALID_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 4
	goto RustboroCity_EventScript_StolenGoodsScene
	end

RustboroCity_EventScript_StolenGoodsScene:: @ 81E09CD
	msgbox RustboroCity_Text_OutOfTheWay, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, 0
	addobject LOCALID_GRUNT
	addobject LOCALID_DEVON_EMPLOYEE
	applymovement LOCALID_GRUNT, RustboroCity_Movement_GruntEscape
	waitmovement 0
	removeobject LOCALID_GRUNT
	applymovement LOCALID_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeChaseGrunt1
	waitmovement 0
	msgbox RustboroCity_Text_WaitDontTakeMyGoods, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeChaseGrunt2
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_DEVON_EMPLOYEE
	setobjectxyperm LOCALID_DEVON_EMPLOYEE, 30, 10
	clearflag FLAG_HIDE_RUSTBORO_CITY_DEVON_EMPLOYEE_1
	setflag FLAG_DEVON_GOODS_STOLEN
	setvar VAR_RUSTBORO_CITY_STATE, 2
	setvar VAR_RUSTURF_TUNNEL_STATE, 2
	setvar VAR_ROUTE116_STATE, 1
	clearflag FLAG_HIDE_ROUTE_116_MR_BRINEY
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_PEEKO
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_AQUA_GRUNT
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	releaseall
	end

@ Unused
RustboroCity_EventScript_ShadyCharacterTookOff:: @ 81E0A3B
	msgbox RustboroCity_Text_ShadyCharacterTookOffTowardsTunnel, MSGBOX_DEFAULT
	return

@ Unused
RustboroCity_EventScript_YouGotItThankYou:: @ 81E0A44
	msgbox RustboroCity_Text_YouGotItThankYou, MSGBOX_DEFAULT
	return

@ Unknown, unused employee movements. Based on the differences in movement theyre for approaching an object (probably the player) in different positions
RustboroCity_EventScript_EmployeeApproachUp:: @ 81E0A4D
	applymovement LOCALID_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachUp
	waitmovement 0
	return

@ Unused, see above
RustboroCity_EventScript_EmployeeApproachLeft:: @ 81E0A58
	applymovement LOCALID_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachLeft
	waitmovement 0
	return

@ Unused, see above
RustboroCity_EventScript_EmployeeApproachRight:: @ 81E0A63
	applymovement LOCALID_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachRight
	waitmovement 0
	return

@ Unused, see above
RustboroCity_EventScript_EmployeeApproachDown:: @ 81E0A6E
	applymovement LOCALID_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachDown
	waitmovement 0
	return

@ Unused, similar movement to the above scripts
RustboroCity_EventScript_EmployeeApproachPlayerFar:: @ 81E0A79
	applymovement LOCALID_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachPlayerFar
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

@ Unused
RustboroCity_Movement_GruntEscapeExtended: @ 81E0A8E
	walk_fastest_right
	walk_fastest_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

RustboroCity_Movement_GruntEscape: @ 81E0AA0
	walk_fastest_right
	walk_fastest_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

RustboroCity_Movement_EmployeeChaseGrunt1: @ 81E0AB1
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

RustboroCity_Movement_EmployeeChaseGrunt2: @ 81E0AB9
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

@ Functionally unused
RustboroCity_Movement_EmployeeApproachUp: @ 81E0AC1
	walk_down
	walk_right
	walk_right
	step_end

@ Functionally unused
RustboroCity_Movement_EmployeeApproachLeft: @ 81E0AC5
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

@ Functionally unused
RustboroCity_Movement_EmployeeApproachRight: @ 81E0ACA
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

@ Functionally unused
RustboroCity_Movement_EmployeeApproachDown: @ 81E0ACF
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

@ Functionally unused
RustboroCity_Movement_EmployeeApproachPlayerFar: @ 81E0AD5
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_down
	step_end

RustboroCity_EventScript_DevonEmployee1:: @ 81E0ADD
	lock
	faceplayer
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_EventScript_ReturnGoodsSpokeToEmployee
	msgbox RustboroCity_Text_ShadyCharacterTookOffTowardsTunnel, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_ReturnGoodsSpokeToEmployee:: @ 81E0AF2
	waitse
	setvar VAR_TEMP_1, 4
	goto RustboroCity_EventScript_ReturnGoods
	end

RustboroCity_EventScript_HelpGetGoodsTrigger0:: @ 81E0AFE
	lockall
	setvar VAR_TEMP_1, 0
	goto RustboroCity_EventScript_EmployeeAskToGetGoods
	end

RustboroCity_EventScript_HelpGetGoodsTrigger1:: @ 81E0B0A
	lockall
	setvar VAR_TEMP_1, 1
	goto RustboroCity_EventScript_EmployeeAskToGetGoods
	end

RustboroCity_EventScript_HelpGetGoodsTrigger2:: @ 81E0B16
	lockall
	setvar VAR_TEMP_1, 2
	goto RustboroCity_EventScript_EmployeeAskToGetGoods
	end

RustboroCity_EventScript_HelpGetGoodsTrigger3:: @ 81E0B22
	lockall
	setvar VAR_TEMP_1, 3
	goto RustboroCity_EventScript_EmployeeAskToGetGoods
	end

RustboroCity_EventScript_EmployeeAskToGetGoods:: @ 81E0B2E
	compare VAR_TEMP_1, 0
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerUp1
	compare VAR_TEMP_1, 1
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerLeft1
	compare VAR_TEMP_1, 2
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerDown1
	compare VAR_TEMP_1, 3
	call_if_eq RustboroCity_EventScript_EmployeeApproachPlayerDown1
	setflag FLAG_INTERACTED_WITH_DEVON_EMPLOYEE_GOODS_STOLEN
	setvar VAR_RUSTBORO_CITY_STATE, 3
	copyobjectxytoperm LOCALID_DEVON_EMPLOYEE
	msgbox RustboroCity_Text_HelpMeIWasRobbed, MSGBOX_DEFAULT
	releaseall
	end

@ The below movement scripts are either partially or fully duplicated by the movement scripts when the player returns the goods
RustboroCity_EventScript_EmployeeFacePlayerUp1:: @ 81E0B6F
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeFacePlayerLeft1:: @ 81E0B9B
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeFacePlayerDown1:: @ 81E0BC7
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeApproachPlayerDown1:: @ 81E0BF3
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachPlayerDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

RustboroCity_Movement_EmployeeApproachPlayerDown: @ 81E0C29
	walk_down
	step_end

RustboroCity_EventScript_ReturnGoodsTrigger0:: @ 81E0C2B
	lockall
	setvar VAR_TEMP_1, 0
	goto RustboroCity_EventScript_ReturnGoods
	end

RustboroCity_EventScript_ReturnGoodsTrigger1:: @ 81E0C37
	lockall
	setvar VAR_TEMP_1, 1
	goto RustboroCity_EventScript_ReturnGoods
	end

RustboroCity_EventScript_ReturnGoodsTrigger2:: @ 81E0C43
	lockall
	setvar VAR_TEMP_1, 2
	goto RustboroCity_EventScript_ReturnGoods
	end

RustboroCity_EventScript_ReturnGoodsTrigger3:: @ 81E0C4F
	lockall
	setvar VAR_TEMP_1, 3
	goto RustboroCity_EventScript_ReturnGoods
	end

RustboroCity_EventScript_ReturnGoods:: @ 81E0C5B
	compare VAR_TEMP_1, 0
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerUp2
	compare VAR_TEMP_1, 1
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerLeft2
	compare VAR_TEMP_1, 2
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerDown2
	compare VAR_TEMP_1, 3
	call_if_eq RustboroCity_EventScript_EmployeeApproachPlayerDown2
	compare VAR_TEMP_1, 4
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerRight
	msgbox RustboroCity_Text_YouGotItThankYou, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL
	compare VAR_RESULT, FALSE
	call_if_eq RustboroCity_EventScript_BagFull
	msgbox RustboroCity_Text_PleaseComeWithMe, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_RETURNED_DEVON_GOODS
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_EMPLOYEE_1
	setvar VAR_RUSTBORO_CITY_STATE, 5
	delay 30
	warp MAP_RUSTBORO_CITY_DEVON_CORP_3F, 255, 2, 2
	waitstate
	releaseall
	end

RustboroCity_EventScript_BagFull:: @ 81E0CD3
	msgbox RustboroCity_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
	return

RustboroCity_EventScript_EmployeeFacePlayerUp2:: @ 81E0CDC
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeFacePlayerLeft2:: @ 81E0D08
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeFacePlayerDown2:: @ 81E0D34
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeApproachPlayerDown2:: @ 81E0D60
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachPlayerDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeFacePlayerRight:: @ 81E0D96
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_Delay48
	waitmovement 0
	return

RustboroCity_EventScript_Rival:: @ 81E0DB8
	lockall
	call_if_unset FLAG_MET_RIVAL_RUSTBORO, RustboroCity_EventScript_PlayRivalMusic
	applymovement LOCALID_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_PlayRivalMusic:: @ 81E0DD1
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq RustboroCity_EventScript_PlayMayMusic
	compare VAR_RESULT, FEMALE
	goto_if_eq RustboroCity_EventScript_PlayBrendanMusic
	return

RustboroCity_EventScript_PlayMayMusic:: @ 81E0DE9
	playbgm MUS_ENCOUNTER_MAY, 1
	return

RustboroCity_EventScript_PlayBrendanMusic:: @ 81E0DEE
	playbgm MUS_ENCOUNTER_BRENDAN, 1
	return

RustboroCity_EventScript_RivalTrigger0:: @ 81E0DF3
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RIVAL, RustboroCity_Movement_RivalApproachPlayer0
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger1:: @ 81E0E33
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RIVAL, RustboroCity_Movement_RivalApproachPlayer1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger2:: @ 81E0E73
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RIVAL, RustboroCity_Movement_RivalApproachPlayer2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger3:: @ 81E0EB3
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RIVAL, RustboroCity_Movement_RivalApproachPlayer3
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger4:: @ 81E0EF3
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RIVAL, RustboroCity_Movement_RivalApproachPlayer4
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger5:: @ 81E0F33
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RIVAL, RustboroCity_Movement_RivalApproachPlayer5
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger6:: @ 81E0F73
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RIVAL, RustboroCity_Movement_RivalApproachPlayer6
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger7:: @ 81E0FB3
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RIVAL, RustboroCity_Movement_RivalApproachPlayer7
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalEncounter:: @ 81E0FF3
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq RustboroCity_EventScript_MayEncounter
	compare VAR_RESULT, FEMALE
	goto_if_eq RustboroCity_EventScript_BrendanEncounter
	end

RustboroCity_EventScript_MayEncounter:: @ 81E100B
	goto_if_set FLAG_DEFEATED_RIVAL_RUSTBORO, RustboroCity_EventScript_MayBrineyHint
	goto_if_set FLAG_MET_RIVAL_RUSTBORO, RustboroCity_EventScript_MayAskToBattle
	setflag FLAG_MET_RIVAL_RUSTBORO
	msgbox RustboroCity_Text_MayHiLetsRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox RustboroCity_Text_RegisteredMay, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	setvar VAR_RUSTBORO_CITY_STATE, 8
	setvar VAR_ROUTE104_STATE, 2
	setvar VAR_0x8008, 0
	msgbox RustboroCity_Text_MayPassedBrineyWantToBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq RustboroCity_EventScript_BattleMay
	msgbox RustboroCity_Text_MayOhHaventRaisedPokemonEnough, MSGBOX_DEFAULT
	call RustboroCity_EventScript_RestoreBgm
	releaseall
	end

RustboroCity_EventScript_MayAskToBattle:: @ 81E1070
	setvar VAR_0x8008, 1
	msgbox RustboroCity_Text_MayWantToBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq RustboroCity_EventScript_BattleMay
	msgbox RustboroCity_Text_MayOhHaventRaisedPokemonEnough, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_EventScript_BattleMay:: @ 81E1092
	msgbox RustboroCity_Text_MayImNotGoingToLose, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, RustboroCity_EventScript_BattleMayTreecko
	case 1, RustboroCity_EventScript_BattleMayTorchic
	case 2, RustboroCity_EventScript_BattleMayMudkip
	end

RustboroCity_EventScript_MayBrineyHint:: @ 81E10C1
	msgbox RustboroCity_Text_MayMrBrineyHint, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq RustboroCity_EventScript_RestoreBgm
	releaseall
	end

RustboroCity_EventScript_RestoreBgm:: @ 81E10D6
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

RustboroCity_EventScript_BattleMayTreecko:: @ 81E10DB
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TREECKO, RustboroCity_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto RustboroCity_EventScript_MayBrineyHint
	end

RustboroCity_EventScript_BattleMayTorchic:: @ 81E10EE
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TORCHIC, RustboroCity_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto RustboroCity_EventScript_MayBrineyHint
	end

RustboroCity_EventScript_BattleMayMudkip:: @ 81E1101
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_MUDKIP, RustboroCity_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto RustboroCity_EventScript_MayBrineyHint
	end

RustboroCity_EventScript_BrendanEncounter:: @ 81E1114
	goto_if_set FLAG_DEFEATED_RIVAL_RUSTBORO, RustboroCity_EventScript_BrendanBrineyHint
	goto_if_set FLAG_MET_RIVAL_RUSTBORO, RustboroCity_EventScript_BrendanAskToBattle
	setflag FLAG_MET_RIVAL_RUSTBORO
	msgbox RustboroCity_Text_BrendanHiLetsRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox RustboroCity_Text_RegisteredBrendan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	setvar VAR_RUSTBORO_CITY_STATE, 8
	setvar VAR_ROUTE104_STATE, 2
	msgbox RustboroCity_Text_BrendanPassedBrineyWantToBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq RustboroCity_EventScript_BattleBrendan
	msgbox RustboroCity_Text_BrendanNoConfidenceInPokemon, MSGBOX_DEFAULT
	call RustboroCity_EventScript_RestoreBgm
	releaseall
	end

RustboroCity_EventScript_BrendanAskToBattle:: @ 81E1174
	msgbox RustboroCity_Text_BrendanWantToBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq RustboroCity_EventScript_BattleBrendan
	msgbox RustboroCity_Text_BrendanNoConfidenceInPokemon, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_EventScript_BattleBrendan:: @ 81E1191
	msgbox RustboroCity_Text_BrendanIWontGoEasy, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, RustboroCity_EventScript_BattleBrendanTreecko
	case 1, RustboroCity_EventScript_BattleBrendanTorchic
	case 2, RustboroCity_EventScript_BattleBrendanMudkip
	end

RustboroCity_EventScript_BrendanBrineyHint:: @ 81E11C0
	msgbox RustboroCity_Text_BrendanMrBrineyHint, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq RustboroCity_EventScript_RestoreBgm
	releaseall
	end

RustboroCity_EventScript_BattleBrendanTreecko:: @ 81E11D5
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TREECKO, RustboroCity_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto RustboroCity_EventScript_BrendanBrineyHint
	end

RustboroCity_EventScript_BattleBrendanTorchic:: @ 81E11E8
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TORCHIC, RustboroCity_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto RustboroCity_EventScript_BrendanBrineyHint
	end

RustboroCity_EventScript_BattleBrendanMudkip:: @ 81E11FB
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_MUDKIP, RustboroCity_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto RustboroCity_EventScript_BrendanBrineyHint
	end

RustboroCity_Movement_RivalApproachPlayer0: @ 81E120E
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer1: @ 81E1215
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer2: @ 81E121B
	walk_down
	walk_left
	walk_left
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer3: @ 81E1220
	walk_down
	walk_left
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer4: @ 81E1224
	walk_down
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer5: @ 81E1227
	walk_down
	walk_right
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer6: @ 81E122B
	walk_down
	walk_right
	walk_right
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer7: @ 81E1230
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	step_end

RustboroCity_EventScript_Boy1:: @ 81E1236
	msgbox RustboroCity_Text_YouCanHave2On2Battle, MSGBOX_NPC
	end

RustboroCity_Text_WeShortenItToDevon: @ 81E123F
	.string "데봉 코포레이션...\n"
	.string "길어서 다들 데봉이라고 줄여서 부르지\p"
	.string "저 회사에서는 여러 가지\n"
	.string "편리한 물건을 만들고 있어!$"
	// デボン コ-ポレ-ション……ｎ
	// ながいから みんな デボンって よぶけどｐ
	// あの かいしゃ では いろいろとｎ
	// べんりな ものを つくってるんだ!

RustboroCity_Text_SneakyLookingManWentAroundCorner: @ 81E12AC
	.string "응? 수상한 남자?\p"
	.string "그러고 보니 인상이 험한 남자가\n"
	.string "저기 모퉁이를 돌아갔어$"
	// ん? あやしい おとこ?ｐ
	// そういえば にんそうの わるい おとこがｎ
	// そこの かどを まがっていったよ

RustboroCity_Text_HaveYouChallengedGym: @ 81E130D
	.string "포켓몬체육관에 도전했니?\p"
	.string "그 반짝반짝 빛나는\n"
	.string "체육관 배지를 가지면 트레이너로서의\l"
	.string "자각이 싹트게 된다고!$"
	// ポケモンジムに ちょうせん したかい?ｐ
	// あの キラリと かがやくｎ
	// ジムバッジを もつと トレ-ナ-としてのｌ
	// じかくが めばえて くるんだな!

RustboroCity_Text_HeyThatsRustborosGymBadge: @ 81E139E
	.string "앗! 금탄의 체육관 배지!\p"
	.string "여러 배지 중에서도\n"
	.string "금탄도시의 배지가 제일 멋지지!$"
	// おっ! カナズミの ジムバッジ!ｐ
	// いくつか ある バッジの なかでｎ
	// カナズミの やつが いちばん かっこいいな!

RustboroCity_Text_YoureNewAroundHere: @ 81E1407
	.string "어라? 넌 누구니?\n"
	.string "이 근처에서 본 적 없는 얼굴이군\p"
	.string "트레이너스쿨의 전학생?$"
	// おや? きみは だれだい?ｎ
	// この あたりでは みかけない かお だねｐ
	// トレ-ナ-ズ スク-ルの てんこうせい?

RustboroCity_Text_GymLeaderIsntEasyWithFire: @ 81E1480
	.string "체육관 관장에게 도전했는데...\p"
	.string "내 불꽃타입 포켓몬으론\n"
	.string "이기기 조금 어려울 것 같아...\p"
	.string "왜냐면 불꽃타입은\n"
	.string "바위타입에게 상성이 나쁘잖아...$"
	// ジムリ-ダ-に ちょうせん したけど……ｐ
	// あたしの ほのおタイプの ポケモンじゃｎ
	// ちょっと かつのは たいへんそう……ｐ
	// だって ほのおタイプ ってｎ
	// いわタイプに あいしょうが わるいもの……

RustboroCity_Text_MrBrineyWalksInTheTunnel: @ 81E1520
	.string "해변의 작은 집에 사는\n"
	.string "선원인 하기노인은\l"
	.string "가끔 터널로 산책을 가$"
	// はまべの こやに すんでいるｎ
	// ふなのりの ハギろうじんｌ
	// ときどき トンネルに さんぽに いくんだよ

RustboroCity_Text_MrBrineyLovesPeeko: @ 81E1589
	.string "해변의 작은 집에 사는\n"
	.string "선원인 하기노인은\l"
	.string "피코를 위해 잿빛도시에 가서\l"
	.string "쇼핑을 한대\p"
	.string "그 할아버지\n"
	.string "정말 피코를 좋아하나봐!$"
	// はまべの こやに すんでいるｎ
	// ふなのりの ハギろうじんｌ
	// ピ-コちゃんの ために カイナに いってｌ
	// かいもの するんだってさｐ
	// ほんとうに ピ-コちゃんが すきなんだな!ｎ
	// あの じいさん

RustboroCity_Text_WowYouHavePokemon: @ 81E1633
	.string "너도 포켓몬을 데리고 있구나\p"
	.string "나도 어른이 되면\n"
	.string "포켓몬과 어딘가로 떠날 거야!$"
	// あなたも ポケモンを つれてるのねｐ
	// あたしも おおきくなったらｎ
	// ポケモンと どこかに いくんだ!

RustboroCity_Text_CatchRarePokemonIfIGoToSchool: @ 81E1695
	.string "포켓몬 트레이너스쿨이라!\p"
	.string "이곳에 입학하면\n"
	.string "희귀한 포켓몬도 쉽게\l"
	.string "잡을 수 있게 될까?$"
	// ぽけもん とれ-な-ず すく-る かぁ!ｐ
	// ここに にゅうがく すればｎ
	// めずらしい ポケモンでも かんたんにｌ
	// つかまえられるように なるのかな?

RustboroCity_Text_PokemonCanChangeLookFromExp: @ 81E16F4
	.string "포켓몬은 배틀의 경험을\n"
	.string "쌓아가면 생김새가\l"
	.string "변하기도 한다고!$"
	// ポケモンって たたかいの けいけんをｎ
	// つんでいくと すがたかたち がｌ
	// かわっちゃうことが あるんだよ!

RustboroCity_Text_PokemonChangeShape: @ 81E174B
	.string "포켓몬의 생김새가 바뀐다고?\n"
	.string "갑자기 바뀌면 놀라겠는데!$"
	// ポケモンの すがたが かわっちゃうの?ｎ
	// いきなり かわると ビックリしちゃう!

RustboroCity_Text_TradePokemonGrowFast: @ 81E1789
	.string "다른 사람과 교환한 포켓몬은\n"
	.string "성장이 빨라!\p"
	.string "...하지만 체육관 배지가 없으면\n"
	.string "말을 들어주질 않아$"
	// ひとと こうかんした ポケモンはｎ
	// そだつのが はやい!ｐ
	// ……でも ジムバッジを もっていないとｎ
	// いうことを きいて くれないんだ

RustboroCity_Text_OutOfTheWay: @ 81E17FE
	.string "비켜-! 비켜 비켜-!!$"
	// どけ-! どけどけ-!!

RustboroCity_Text_WaitDontTakeMyGoods: @ 81E1817
	.string "거기 서-!\p"
	.string "그 화물을 돌려줘어어어-!!$"
	// まってぇ-!ｐ
	// その にもつを かえしてぇぇぇ-!!

RustboroCity_Text_HelpMeIWasRobbed: @ 81E183E
	.string "아아 당신은!\p"
	.string "등화숲에서 도와주신\n"
	.string "멋진 트레이너 아니신가요!\p"
	.string "부탁합니다!\p"
	.string "아쿠아단에게 빼앗긴\n"
	.string "데봉화물을 되찾아 주십시오!\p"
	.string "그게 없으면....\n"
	.string "전 매우 곤란해집니다$"
	// ああ きみは!ｐ
	// トウカのもりで たすけてくれたｎ
	// すてきな トレ-ナ-じゃ ないですか!ｐ
	// おねがいです!ｐ
	// アクアだんに うばわれたｎ
	// デボンのにもつ とりかえして ください!ｐ
	// あれが ないと……ｎ
	// わたし とても こまるんです

RustboroCity_Text_ShadyCharacterTookOffTowardsTunnel: @ 81E1904
	.string "방금 전의 수상한 녀석은\n"
	.string "건너편의 터널 쪽으로\l"
	.string "도망갔을 거라고 생각합니다$"
	// さっきの あやしい やつはｎ
	// むこうの トンネルの ほうにｌ
	// にげていったと おもうのですよ

RustboroCity_Text_YouGotItThankYou: @ 81E194D
	.string "아아! 어떻게 됐나요\n"
	.string "데봉화물은...?\p"
	.string "그렇군요!\n"
	.string "되찾아 주신 건가요!\p"
	.string "당신은 정말\n"
	.string "대단한 트레이너군요!\p"
	.string "...그래요! 답례로 또\n"
	.string "수퍼볼을 드리죠!$"
	// ああ! どうでしたｎ
	// デボンのにもつ は……?ｐ
	// そうですか!ｎ
	// とりかえして くれたのですか!ｐ
	// きみは ほんとうにｎ
	// すごい トレ-ナ- ですね!ｐ
	// ……そうだ! おれいに またｎ
	// ス-パ-ボ-ルを あげちゃおう!

RustboroCity_Text_YoureLoadedWithItems: @ 81E19E5
	.string "가방이 가득 찼다면\n"
	.string "수퍼볼은 드릴 수 없겠네요$"
	// どうぐ いっぱいでｎ
	// ス-パ-ボ-ル あげられないね

RustboroCity_Text_PleaseComeWithMe: @ 81E1A21
	.string "저기! 저기!\n"
	.string "절 따라와 주세요!$"
	// きみ! きみ!ｎ
	// わたしに ついてきて ください!

RustboroCity_Text_MayHiLetsRegister: @ 81E1A49
	.string "봄이: 아 {PLAYER}{K_AYA}!\p"
	.string "포켓내비에 엔트리콜을\n"
	.string "장착받았구나!\p"
	.string "그럼 우리\n"
	.string "서로 전화할 수 있도록\l"
	.string "이름을 등록해두자!\p"
	.string "...... ...... ......$"
	// ハルカ『あっ §あ§お!ｐ
	// ポケナビに エントリ-コ-ルをｎ
	// つけて もらったのね!ｐ
	// じゃあ あたしたちｎ
	// おたがいに よびだせる ようにｌ
	// なまえを とうろく しておこうよ!ｐ
	// …… …… ……

RustboroCity_Text_RegisteredMay: @ 81E1ADB
	.string "봄이를\n"
	.string "포켓내비에 등록했다!$"
	// ハルカをｎ
	// ポケナビに とうろく した!

RustboroCity_Text_MayPassedBrineyWantToBattle: @ 81E1AFA
	.string "봄이: 그러고 보니 등화숲에서\n"
	.string "하기노인하고 스쳐 지나갔는데\p"
	.string "아마... 해변의 작은 집으로\n"
	.string "돌아가는 중이 아니었을까!\p"
	.string "으-음... 그것보다 {PLAYER}의\n"
	.string "포켓몬 도감은 많이 채워졌어?\p"
	.string "난 꽤 괜찮은 느낌이야!\n"
	.string "어때? 한번 승부해 볼래?$"
	// ハルカ『そういえば トウカのもりでｎ
	// ハギろうじんと すれちがったわｐ
	// たぶん…… はまべの こやにｎ
	// もどるところ だったんじゃ ないかな!ｐ
	// え-と…… それより §あ§おのｎ
	// ポケモンずかんの ちょうしは どう?ｐ
	// あたしは かなり いい かんじ!ｎ
	// どう? ちょっと しょうぶ してみる?

RustboroCity_Text_MayOhHaventRaisedPokemonEnough: @ 81E1BD3
	.string "봄이: 에- 뭐야-\n"
	.string "그다지 포켓몬을 잡거나\l"
	.string "키우질 않은 거야?\p"
	.string "그래서는 트레이너로서\n"
	.string "한참 멀었다고!$"
	// ハルカ『え- なんでよ-ｎ
	// あんまり ポケモン つかまえたりｌ
	// そだてたり してないのかな?ｐ
	// それじゃあ トレ-ナ-としてｎ
	// まだまだ ね!

RustboroCity_Text_MayWantToBattle: @ 81E1C48
	.string "봄이: 어때? 나하고 여기서\n"
	.string "한번 승부해 볼래?$"
	// ハルカ『どう? あたしと ここでｎ
	// ちょっと しょうぶ してみる?

RustboroCity_Text_MayImNotGoingToLose: @ 81E1C84
	.string "봄이: 트레이너가 된 지 얼마 안 된\n"
	.string "{PLAYER}에게는 질 수 없지!$"
	// ハルカ『トレ-ナ-に なった ばかりのｎ
	// §あ§おには まけないよ!

RustboroCity_Text_MayDefeat: @ 81E1CC1
	.string "우와아...\n"
	.string "벌써 이렇게 강해지다니...$"
	// うわあ……ｎ
	// もう こんなに つよいなんて……

RustboroCity_Text_MayMrBrineyHint: @ 81E1CE7
	.string "봄이: 그러고 보니 방금 스쳐 지나간\n"
	.string "하기노인 말인데\p"
	.string "{PLAYER}{K_EUNNEUN} 막 이사 와서\n"
	.string "잘 모를 테지만\l"
	.string "예전에 대단한 선원이었어!$"
	// ハルカ『そういえば さっき すれちがったｎ
	// ハギろうじん なんだけどねｐ
	// §あ§おは ひっこして きたばかりでｎ
	// しらないかも しれないけどｌ
	// むかしは すっごい ふなのり だったのよ!

RustboroCity_Text_BrendanHiLetsRegister: @ 81E1D7D
	.string "휘웅: 오 {PLAYER}{K_AYA}!\p"
	.string "포켓내비에 엔트리콜을\n"
	.string "장착받았구나!\p"
	.string "그럼 우리\n"
	.string "서로 전화할 수 있도록\l"
	.string "이름을 등록해두자!\p"
	.string "...... ...... ......$"
	// ユウキ『おっ §あ!ｐ
	// ポケナビに エントリ-コ-ルをｎ
	// つけて もらったんだな!ｐ
	// じゃあ オレたちｎ
	// おたがいに よびだせる ようにｌ
	// なまえを とうろく しておこうよ!ｐ
	// …… …… ……

RustboroCity_Text_RegisteredBrendan: @ 81E1E11
	.string "휘웅을\n"
	.string "포켓내비에 등록했다!$"
	// ユウキをｎ
	// ポケナビに とうろく した!

RustboroCity_Text_BrendanPassedBrineyWantToBattle: @ 81E1E34
	.string "휘웅: 그러고 보니 {PLAYER}{K_AYA}\p"
	.string "방금 등화숲에서\n"
	.string "하기노인과 스쳐 지나갔어\p"
	.string "분명... 해변의 작은 집으로\n"
	.string "돌아가는 길이었을 거야!\p"
	.string "으-음... 그것보다 {PLAYER}의\n"
	.string "포켓몬 도감은 어때?\l"
	.string "페이지 많이 채웠어?\p"
	.string "난 완전 끝내준다!\n"
	.string "어때 포켓몬 승부로\l"
	.string "그 성과를 시험해 볼래?$"
	// ユウキ『そういえば §あｐ
	// さっき トウカのもりでｎ
	// ハギろうじんと すれちがったよｐ
	// たぶん…… はまべの こやにｎ
	// もどるところ だったんじゃ ないかな!ｐ
	// え-と…… それより §あのｎ
	// ポケモンずかんは どう?ｌ
	// ちょっとは ペ-ジ うまったか?ｐ
	// オレは すごいよ!ｎ
	// どうだ ポケモン しょうぶでｌ
	// そのせいかを ためして やろうか?

RustboroCity_Text_BrendanNoConfidenceInPokemon: @ 81E1F2F
	.string "휘웅: 뭐야\n"
	.string "지닌 포켓몬에 자신이 없는 거야?$"
	// ユウキ『なんだよｎ
	// もってる ポケモンに じしんが ないのか?

RustboroCity_Text_BrendanWantToBattle: @ 81E1F76
	.string "휘웅: 어때 나하고 여기서\n"
	.string "승부해 볼래?$"
	// ユウキ『どうだい オレと ここでｎ
	// しょうぶ してみるか?

RustboroCity_Text_BrendanIWontGoEasy: @ 81E1FA9
	.string "휘웅: 신참 트레이너라고 해서\n"
	.string "적당히 하진 않을 거야!$"
	// ユウキ『トレ-ナ-に なりたて だってｎ
	// てかげんは しないからな!

RustboroCity_Text_BrendanDefeat: @ 81E1FE9
	.string "헤에...\n"
	.string "꽤 하는데$"
	// へえ……ｎ
	// なかなか やるじゃないか

RustboroCity_Text_BrendanMrBrineyHint: @ 81E2002
	.string "휘웅: 그러고 보니 방금 스쳐 지나간\n"
	.string "하기노인 말인데\p"
	.string "{PLAYER}{K_EUNNEUN} 이사 온 지\n"
	.string "얼마 안 돼서 잘 모르겠지만\l"
	.string "예전에 대단한 선원이었어!$"
	// ユウキ『そういえば さっき すれちがったｎ
	// ハギろうじん だけどなｐ
	// §あは ひっこして きたばかりでｎ
	// しらないかも しれないけどｌ
	// むかしは すごい ふなのり だったんだ!

RustboroCity_Text_TunnelNearingCompletion: @ 81E20A6
	.string "“편리한 터널 곧 완성!”\p"
	.string "...이라고 간판에 적혀 있지만\n"
	.string "그 위에 빨간 페인트로\l"
	.string "크게 X 표시가 그려져 있다$"
	// 「べんりな トンネル かんせい まぢか!」ｐ
	// ……と かんばんに かかれているがｎ
	// その うえに あかい ペンキでｌ
	// おおきな バッテンが つけられている

RustboroCity_Text_DevonCorpSign: @ 81E2128
	.string "“데봉 코포레이션”\p"
	.string "여러분의 생활을 위해\n"
	.string "무엇이든 만들고 있습니다!$"
	// 「デボン コ-ポレ-ション」ｐ
	// みなさんの せいかつの ためにｎ
	// なんでも つくっています!

RustboroCity_Text_GymSign: @ 81E2167
	.string "금탄도시 포켓몬체육관\n"
	.string "관장 원규\l"
	.string "바위를 보면 가슴이 뛰는 우등생!$"
	// カナズミ シティ ポケモンジムｎ
	// リ-ダ- ツツジｌ
	// いわに ときめく ゆうとうせい!

RustboroCity_Text_DevonCorpBranchOfficeSign: @ 81E21B3
	.string "“데봉 코포레이션 분실”\p"
	.string "관계자 외 출입 금지\n"
	.string "양해 바랍니다!$"
	// 「デボン コ-ポレ-ション ぶんしつ」ｐ
	// かんけいしゃ いがいの たちいりはｎ
	// どうぞ ごえんりょ ください!

RustboroCity_Text_CitySign: @ 81E220B
	.string "여기는 금탄도시\p"
	.string "자연과 과학의 융합을\n"
	.string "추구하는 마을$"
	// ここは カナズミ シティｐ
	// しぜんと かがくの ゆうごうをｎ
	// ついきゅうする まち

RustboroCity_Text_TrainersSchoolSign: @ 81E2253
	.string "“포켓몬 트레이너스쿨”\n"
	.string "포켓몬에 대해 뭐든지 가르쳐 드립니다!$"
	// 「ポケモン トレ-ナ-ズ スク-ル」ｎ
	// ポケモンのことなら なんでも おしえます!

RustboroCity_Text_CuttersHouse: @ 81E2296
	.string "“풀베기아저씨의 집”$"
	// 「いあいぎりオヤジの いえ」

RustboroCity_Text_DevelopedNewPokenavFeature: @ 81E22A5
	.string "지금 포켓내비의 추가 기능을\n"
	.string "개발했는데...\p"
	.string "잘 작동됩니다!\p"
	.string "{PLAYER}님!\p"
	.string "사장님께 받은 그 포켓내비\n"
	.string "잠깐 빌려주세요!$"
	// いま ポケナビの ついかきのうをｎ
	// かいはつ していたのですが……ｐ
	// うまく いきましたよ!ｐ
	// §あさん!ｐ
	// しゃちょうに いただいた そのポケナビｎ
	// ちょっと かしてくださいね!

RustboroCity_Text_AddedMatchCallPleaseCallMrStone: @ 81E2331
	.string "네! {PLAYER}님의 포켓내비에\n"
	.string "엔트리콜이라고 하는 기능을\l"
	.string "추가했습니다!\p"
	.string "포켓내비에 등록되어 있다면\n"
	.string "멀리 떨어진 곳의 사람과\l"
	.string "엔트리콜을 통해서\l"
	.string "대화할 수 있게 된 겁니다!\p"
	.string "{PLAYER}님의 포켓내비에는\n"
	.string "우리 나발명 사장님의 이름이\l"
	.string "등록되어 있을 겁니다\p"
	.string "시험 삼아 사장님께\n"
	.string "전화해 보세요!$"
	// はい! §あさんの ポケナビにｎ
	// エントリ-コ-ル という きのうをｌ
	// ついか しました!ｐ
	// ポケナビに とうろく されていればｎ
	// とおく はなれた ところの ひととｌ
	// エントリ-コ-ルを つうじてｌ
	// かいわが できて しまうんです!ｐ
	// §あさんの ポケナビにはｎ
	// うちの ツワブキ しゃちょうの なまえがｌ
	// とうろく してある はずですｐ
	// ためしに ちょっと しゃちょうをｎ
	// よびだして みてください!

RustboroCity_Text_PleaseSelectPokenav: @ 81E2449
	.string "포켓내비를 선택해 주십시오!$"
	// ポケナビを えらんで ください!

RustboroCity_Text_IdBetterGetBackToWork: @ 81E2464
	.string "...그럼 저는 일하러 돌아가겠습니다\p"
	.string "{PLAYER}님 조심히 가세요!$"
	// ……では わたしは しごとに もどりますｐ
	// §あさん おきをつけて!

RustboroCity_Text_YouCanHave2On2Battle: @ 81E249D
	.string "너 알고 있어?\n"
	.string "한 쌍의 트레이너가 아니어도\l"
	.string "2대2로 승부할 수 있어!\p"
	.string "2마리 이상의 포켓몬을 지녔을 때\n"
	.string "두 명의 트레이너와 눈이 마주치면\l"
	.string "동시에 승부를 걸어올 거야!\p"
	.string "단 혼자서 두 명을 상대로\n"
	.string "이긴다면 멋지겠다-!$"
	// きみ しってる?ｎ
	// ふたりづれの トレ-ナ-とじゃ なくてもｌ
	// 2たい2の しょうぶが できるんだ!ｐ
	// 2ひき いじょう ポケモンを もってるときｎ
	// ふたりの トレ-ナ-と めが あえばｌ
	// しょうぶを どうじに いどんで くるよ!ｐ
	// たった ひとりで ふたりを あいてにｎ
	// かてたら カッコいいよね-!
