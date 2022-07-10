.set LOCALID_CHALLENGE_BIKER, 21
.set LOCALID_RIVAL, 28
.set LOCALID_RIVAL_ON_BIKE, 29
.set LOCALID_BIRCH, 36

Route110_MapScripts:: @ 81EF269
	map_script MAP_SCRIPT_ON_RESUME, Route110_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route110_OnFrame
	.byte 0

Route110_OnResume: @ 81EF279
	special UpdateCyclingRoadState
	end

Route110_OnTransition: @ 81EF27D
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	compare VAR_CYCLING_CHALLENGE_STATE, 1
	call_if_eq Route110_EventScript_SaveCyclingMusic
	end

Route110_EventScript_SaveCyclingMusic:: @ 81EF293
	savebgm MUS_CYCLING
	return

Route110_OnFrame: @ 81EF297
	map_script_2 VAR_CYCLING_CHALLENGE_STATE, 1, Route110_EventScript_BeginCylcingRoadChallenge
	.2byte 0

Route110_EventScript_BeginCylcingRoadChallenge:: @ 81EF2A1
	special Special_BeginCyclingRoadChallenge
	setvar VAR_CYCLING_CHALLENGE_STATE, 2
	return

Route110_EventScript_AquaGrunt1:: @ 81EF2AA
	lock
	faceplayer
	msgbox Route110_Text_WeCantTalkAboutAquaActivities, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_AquaGrunt2:: @ 81EF2C0
	lock
	faceplayer
	msgbox Route110_Text_KickUpARuckus, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_AquaGrunt3:: @ 81EF2D6
	lock
	faceplayer
	msgbox Route110_Text_MyFirstJobInAqua, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_AquaGrunt4:: @ 81EF2EC
	lock
	faceplayer
	msgbox Route110_Text_AquaActionsBringSmiles, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_Boy1:: @ 81EF302
	msgbox Route110_Text_RideBikeAtFullSpeed, MSGBOX_NPC
	end

Route110_EventScript_CyclingGirl1:: @ 81EF30B
	msgbox Route110_Text_HairStreamsBehindMe, MSGBOX_NPC
	end

Route110_EventScript_CyclingGuy1:: @ 81EF314
	msgbox Route110_Text_YouGotBikeFromRydel, MSGBOX_NPC
	end

Route110_EventScript_OldMan:: @ 81EF31D
	msgbox Route110_Text_TwoRoads, MSGBOX_NPC
	end

Route110_EventScript_OldWoman:: @ 81EF326
	msgbox Route110_Text_WalkOnTheLowRoad, MSGBOX_NPC
	end

Route110_EventScript_CyclingGuy2:: @ 81EF32F
	msgbox Route110_Text_BikeTechniques, MSGBOX_NPC
	end

Route110_EventScript_Boy2:: @ 81EF338
	msgbox Route110_Text_WhichShouldIChoose, MSGBOX_NPC
	end

Route110_EventScript_SlateportCitySign:: @ 81EF341
	msgbox Route110_Text_SlateportCitySign, MSGBOX_SIGN
	end

Route110_EventScript_CyclingRoadSign:: @ 81EF34A
	msgbox Route110_Text_CyclingRoadSign, MSGBOX_SIGN
	end

Route110_EventScript_VandalizedSign:: @ 81EF353
	msgbox Route110_Text_AquaWasHere, MSGBOX_SIGN
	end

Route110_EventScript_Route103Sign:: @ 81EF35C
	msgbox Route110_Text_Route103Sign, MSGBOX_SIGN
	end

Route110_EventScript_SeasideParkingSign:: @ 81EF365
	msgbox Route110_Text_SeasideParkingSign, MSGBOX_SIGN
	end

Route110_EventScript_MauvilleCitySign:: @ 81EF36E
	msgbox Route110_Text_MauvilleCitySign, MSGBOX_SIGN
	end

Route110_EventScript_TrainerTipsPrlzSleep:: @ 81EF377
	msgbox Route110_Text_TrainerTipsPrlzSleep, MSGBOX_SIGN
	end

Route110_EventScript_TrainerTipsRegisterItems:: @ 81EF380
	msgbox Route110_Text_TrainerTipsRegisterItems, MSGBOX_SIGN
	end

Route110_EventScript_TrickHouseSign:: @ 81EF389
	msgbox Route110_Text_TrickHouseSign, MSGBOX_SIGN
	end

Route110_EventScript_CyclingRoadResultsSign:: @ 81EF392
	lockall
	specialvar VAR_RESULT, GetRecordedCyclingRoadResults
	compare VAR_RESULT, FALSE
	goto_if_eq Route110_EventScript_NoRecordSet
	msgbox Route110_Text_BestRecord, MSGBOX_DEFAULT
	releaseall
	end

Route110_EventScript_NoRecordSet:: @ 81EF3AD
	msgbox Route110_Text_ThereIsNoRecord, MSGBOX_DEFAULT
	releaseall
	end

Route110_EventScript_ChallengeGuy:: @ 81EF3B7
	lock
	faceplayer
	specialvar VAR_RESULT, GetPlayerAvatarBike
	compare VAR_RESULT, 1
	goto_if_eq Route110_EventScript_PlayerRidingAcroBike
	compare VAR_CYCLING_CHALLENGE_STATE, 0
	goto_if_eq Route110_EventScript_PlayerNotRidingBike
	msgbox Route110_Text_AlwaysAimHigher, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_PlayerNotRidingBike:: @ 81EF3DE
	msgbox Route110_Text_RatedForNumberOfCollisions, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_PlayerRidingAcroBike:: @ 81EF3E8
	msgbox Route110_Text_AcroBikesDoNotQualify, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_Edward:: @ 81EF3F2
	trainerbattle_single TRAINER_EDWARD, Route110_Text_EdwardIntro, Route110_Text_EdwardDefeated
	msgbox Route110_Text_EdwardPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Jaclyn:: @ 81EF409
	trainerbattle_single TRAINER_JACLYN, Route110_Text_JaclynIntro, Route110_Text_JaclynDefeated
	msgbox Route110_Text_JaclynPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Edwin:: @ 81EF420
	trainerbattle_single TRAINER_EDWIN_1, Route110_Text_EdwinIntro, Route110_Text_EdwinDefeated, Route110_EventScript_EdwinRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route110_EventScript_EdwinRematch
	msgbox Route110_Text_EdwinPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_EdwinRegisterMatchCallAfterBattle:: @ 81EF44C
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_EdwinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_EDWIN_1
	release
	end

Route110_EventScript_EdwinRematch:: @ 81EF46B
	trainerbattle_rematch TRAINER_EDWIN_1, Route110_Text_EdwinRematchIntro, Route110_Text_EdwinRematchDefeated
	msgbox Route110_Text_EdwinRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Dale:: @ 81EF482
	trainerbattle_single TRAINER_DALE, Route110_Text_DaleIntro, Route110_Text_DaleDefeated
	msgbox Route110_Text_DalePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Jacob:: @ 81EF499
	trainerbattle_single TRAINER_JACOB, Route110_Text_JacobIntro, Route110_Text_JacobDefeated
	msgbox Route110_Text_JacobPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Anthony:: @ 81EF4B0
	trainerbattle_single TRAINER_ANTHONY, Route110_Text_AnthonyIntro, Route110_Text_AnthonyDefeated
	msgbox Route110_Text_AnthonyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Benjamin:: @ 81EF4C7
	trainerbattle_single TRAINER_BENJAMIN_1, Route110_Text_BenjaminIntro, Route110_Text_BenjaminDefeated, Route110_EventScript_BenjaminRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route110_EventScript_BenjaminRematch
	msgbox Route110_Text_BenjaminPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_BenjaminRegisterMatchCallAfterBattle:: @ 81EF4F3
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_BenjaminRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BENJAMIN_1
	release
	end

Route110_EventScript_BenjaminRematch:: @ 81EF512
	trainerbattle_rematch TRAINER_BENJAMIN_1, Route110_Text_BenjaminRematchIntro, Route110_Text_BenjaminRematchDefeated
	msgbox Route110_Text_BenjaminRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Jasmine:: @ 81EF529
	trainerbattle_single TRAINER_JASMINE, Route110_Text_JasmineIntro, Route110_Text_JasmineDefeated
	msgbox Route110_Text_JasminePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Abigail:: @ 81EF540
	trainerbattle_single TRAINER_ABIGAIL_1, Route110_Text_AbigailIntro, Route110_Text_AbigailDefeated, Route110_EventScript_AbigailRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route110_EventScript_AbigailRematch
	msgbox Route110_Text_AbigailPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_AbigailRegisterMatchCallAfterBattle:: @ 81EF56C
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_AbigailRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ABIGAIL_1
	release
	end

Route110_EventScript_AbigailRematch:: @ 81EF58B
	trainerbattle_rematch TRAINER_ABIGAIL_1, Route110_Text_AbigailRematchIntro, Route110_Text_AbigailRematchDefeated
	msgbox Route110_Text_AbigailRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Isabel:: @ 81EF5A2
	trainerbattle_single TRAINER_ISABEL_1, Route110_Text_IsabelIntro, Route110_Text_IsabelDefeated, Route110_EventScript_IsabelRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route110_EventScript_IsabelRematch
	msgbox Route110_Text_IsabelPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_IsabelRegisterMatchCallAfterBattle:: @ 81EF5CE
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_IsabelRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ISABEL_1
	release
	end

Route110_EventScript_IsabelRematch:: @ 81EF5ED
	trainerbattle_rematch TRAINER_ISABEL_1, Route110_Text_IsabelRematchIntro, Route110_Text_IsabelRematchDefeated
	msgbox Route110_Text_IsabelRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Timmy:: @ 81EF604
	trainerbattle_single TRAINER_TIMMY, Route110_Text_TimmyIntro, Route110_Text_TimmyDefeated
	msgbox Route110_Text_TimmyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Unused:: @ 81EF61B
	end

Route110_EventScript_Kaleb:: @ 81EF61C
	trainerbattle_single TRAINER_KALEB, Route110_Text_KalebIntro, Route110_Text_KalebDefeated
	msgbox Route110_Text_KalebPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Joseph:: @ 81EF633
	trainerbattle_single TRAINER_JOSEPH, Route110_Text_JosephIntro, Route110_Text_JosephDefeated
	msgbox Route110_Text_JosephPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Alyssa:: @ 81EF64A
	trainerbattle_single TRAINER_ALYSSA, Route110_Text_AlyssaIntro, Route110_Text_AlyssaDefeated
	msgbox Route110_Text_AlyssaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_CyclingChallengeEnd:: @ 81EF661
	lockall
	applymovement LOCALID_CHALLENGE_BIKER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	call Route110_EventScript_CyclingChallengeResults
	releaseall
	end

Route110_EventScript_CyclingChallengeResults:: @ 81EF673
	special FinishCyclingRoadChallenge
	msgbox Route110_Text_CyclingChallengeResultSummary, MSGBOX_DEFAULT
	switch VAR_RESULT
	case 10, Route110_EventScript_ChallengeReactionBest
	case 9, Route110_EventScript_ChallengeReactionGood
	case 8, Route110_EventScript_ChallengeReactionGood
	case 7, Route110_EventScript_ChallengeReactionGood
	case 6, Route110_EventScript_ChallengeReactionOk
	case 5, Route110_EventScript_ChallengeReactionOk
	case 4, Route110_EventScript_ChallengeReactionOk
	case 3, Route110_EventScript_ChallengeReactionBad
	case 2, Route110_EventScript_ChallengeReactionBad
	case 1, Route110_EventScript_ChallengeReactionBad
	case 0, Route110_EventScript_ChallengeReactionWorst
	end

Route110_EventScript_ChallengeReactionBest:: @ 81EF6FD
	msgbox Route110_Text_ChallengeReactionBest, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_ChallengeReactionGood:: @ 81EF70B
	msgbox Route110_Text_ChallengeReactionGood, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_ChallengeReactionOk:: @ 81EF719
	msgbox Route110_Text_ChallengeReactionOk, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_ChallengeReactionBad:: @ 81EF727
	msgbox Route110_Text_ChallengeReactionBad, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_ChallengeReactionWorst:: @ 81EF735
	msgbox Route110_Text_ChallengeReactionWorst, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_EndChallenge:: @ 81EF743
	setvar VAR_CYCLING_CHALLENGE_STATE, 3
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

Route110_EventScript_RivalTrigger1:: @ 81EF74D
	setvar VAR_0x8008, 1
	goto Route110_EventScript_RivalScene
	end

Route110_EventScript_RivalTrigger2:: @ 81EF758
	setvar VAR_0x8008, 2
	goto Route110_EventScript_RivalScene
	end

Route110_EventScript_RivalTrigger3:: @ 81EF763
	setvar VAR_0x8008, 3
	goto Route110_EventScript_RivalScene
	end

Route110_EventScript_RivalScene:: @ 81EF76E
	lockall
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq Route110_EventScript_PlayMayMusic
	compare VAR_RESULT, FEMALE
	call_if_eq Route110_EventScript_PlayBrendanMusic
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	delay 30
	compare VAR_0x8008, 1
	call_if_eq Route110_EventScript_RivalApproachPlayer1
	compare VAR_0x8008, 2
	call_if_eq Route110_EventScript_RivalApproachPlayer2
	compare VAR_0x8008, 3
	call_if_eq Route110_EventScript_RivalApproachPlayer3
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq Route110_EventScript_MayBattle
	compare VAR_RESULT, FEMALE
	goto_if_eq Route110_EventScript_BrendanBattle
	releaseall
	end

Route110_EventScript_PlayMayMusic:: @ 81EF7E1
	playbgm MUS_ENCOUNTER_MAY, 1
	return

Route110_EventScript_PlayBrendanMusic:: @ 81EF7E6
	playbgm MUS_ENCOUNTER_BRENDAN, 1
	return

Route110_EventScript_MayBattle:: @ 81EF7EB
	msgbox Route110_Text_MayLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route110_EventScript_MayBattleTreecko
	case 1, Route110_EventScript_MayBattleTorchic
	case 2, Route110_EventScript_MayBattleMudkip
	end

Route110_EventScript_MayBattleTreecko:: @ 81EF81A
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_TREECKO, Route110_Text_MayDefeated
	goto Route110_EventScript_MayDefeated
	end

Route110_EventScript_MayBattleTorchic:: @ 81EF82A
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_TORCHIC, Route110_Text_MayDefeated
	goto Route110_EventScript_MayDefeated
	end

Route110_EventScript_MayBattleMudkip:: @ 81EF83A
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_MUDKIP, Route110_Text_MayDefeated
	goto Route110_EventScript_MayDefeated
	end

Route110_EventScript_MayDefeated:: @ 81EF84A
	msgbox Route110_Text_MayTakeThis, MSGBOX_DEFAULT
	call Route110_EventScript_GiveItemfinder
	msgbox Route110_Text_MayExplainItemfinder, MSGBOX_DEFAULT
	goto Route110_EventScript_RivalExit
	end

Route110_EventScript_BrendanBattle:: @ 81EF865
	msgbox Route110_Text_BrendanLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route110_EventScript_BrendanBattleTreecko
	case 1, Route110_EventScript_BrendanBattleTorchic
	case 2, Route110_EventScript_BrendanBattleMudkip
	end

Route110_EventScript_BrendanBattleTreecko:: @ 81EF894
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_TREECKO, Route110_Text_BrendanDefeated
	goto Route110_EventScript_BrendanDefeated
	end

Route110_EventScript_BrendanBattleTorchic:: @ 81EF8A4
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_TORCHIC, Route110_Text_BrendanDefeated
	goto Route110_EventScript_BrendanDefeated
	end

Route110_EventScript_BrendanBattleMudkip:: @ 81EF8B4
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_MUDKIP, Route110_Text_BrendanDefeated
	goto Route110_EventScript_BrendanDefeated
	end

Route110_EventScript_BrendanDefeated:: @ 81EF8C4
	msgbox Route110_Text_BrendanTakeThis, MSGBOX_DEFAULT
	call Route110_EventScript_GiveItemfinder
	msgbox Route110_Text_BrendanExplainItemfinder, MSGBOX_DEFAULT
	goto Route110_EventScript_RivalExit
	end

Route110_EventScript_GiveItemfinder:: @ 81EF8DF
	giveitem ITEM_ITEMFINDER
	return

Route110_EventScript_RivalExit:: @ 81EF8EC
	closemessage
	compare VAR_0x8008, 1
	call_if_eq Route110_EventScript_MoveRival1
	compare VAR_0x8008, 2
	call_if_eq Route110_EventScript_MoveRival2
	compare VAR_0x8008, 3
	call_if_eq Route110_EventScript_MoveRival3
	setobjectmovementtype LOCALID_RIVAL, MOVEMENT_TYPE_FACE_RIGHT
	setobjectmovementtype LOCALID_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_RIGHT
	removeobject LOCALID_RIVAL
	addobject LOCALID_RIVAL_ON_BIKE
	delay 45
	compare VAR_0x8008, 1
	call_if_eq Route110_EventScript_RivalExit1
	compare VAR_0x8008, 2
	call_if_eq Route110_EventScript_RivalExit2
	compare VAR_0x8008, 3
	call_if_eq Route110_EventScript_RivalExit3
	removeobject LOCALID_RIVAL_ON_BIKE
	setvar VAR_ROUTE110_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Route110_EventScript_RivalApproachPlayer1:: @ 81EF94E
	applymovement LOCALID_RIVAL, Route110_Movement_RivalApproachPlayer1
	waitmovement 0
	return

Route110_EventScript_RivalApproachPlayer2:: @ 81EF959
	applymovement LOCALID_RIVAL, Route110_Movement_RivalApproachPlayer2
	waitmovement 0
	return

Route110_EventScript_RivalApproachPlayer3:: @ 81EF964
	applymovement LOCALID_RIVAL, Route110_Movement_RivalApproachPlayer3
	waitmovement 0
	return

Route110_EventScript_RivalExit1:: @ 81EF96F
	applymovement LOCALID_RIVAL_ON_BIKE, Route110_Movement_RivalExit1
	waitmovement 0
	return

Route110_EventScript_RivalExit2:: @ 81EF97A
	applymovement LOCALID_RIVAL_ON_BIKE, Route110_Movement_RivalExit2
	waitmovement 0
	return

Route110_EventScript_RivalExit3:: @ 81EF985
	applymovement LOCALID_RIVAL_ON_BIKE, Route110_Movement_RivalExit3
	waitmovement 0
	return

Route110_EventScript_MoveRival1:: @ 81EF990
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 33, 55
	return

Route110_EventScript_MoveRival2:: @ 81EF998
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 34, 55
	return

Route110_EventScript_MoveRival3:: @ 81EF9A0
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 35, 55
	return

Route110_Movement_RivalApproachPlayer1: @ 81EF9A8
	walk_down
	walk_left
	walk_in_place_fastest_down
	step_end

Route110_Movement_RivalApproachPlayer2: @ 81EF9AC
	walk_down
	step_end

Route110_Movement_RivalApproachPlayer3: @ 81EF9AE
	walk_down
	walk_right
	walk_in_place_fastest_down
	step_end

Route110_Movement_RivalExit1: @ 81EF9B2
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route110_Movement_RivalExit2: @ 81EF9BA
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_down
	step_end

Route110_Movement_RivalExit3: @ 81EF9C3
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route110_EventScript_BirchScene1:: @ 81EF9CB
	lockall
	setvar VAR_0x8008, 1
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene2:: @ 81EF9D6
	lockall
	setvar VAR_0x8008, 2
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene3:: @ 81EF9E1
	lockall
	setvar VAR_0x8008, 3
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene4:: @ 81EF9EC
	lockall
	setvar VAR_0x8008, 4
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene:: @ 81EF9F7
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, Route110_Movement_BirchEntrance
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_BIRCH, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_BIRCH, Common_Movement_Delay48
	waitmovement 0
	compare VAR_0x8008, 1
	call_if_eq Route110_EventScript_BirchApproachPlayer1
	compare VAR_0x8008, 2
	call_if_eq Route110_EventScript_BirchApproachPlayer2
	compare VAR_0x8008, 3
	call_if_eq Route110_EventScript_BirchApproachPlayer3
	compare VAR_0x8008, 4
	call_if_eq Route110_EventScript_BirchApproachPlayer4
	msgbox Route110_Text_ImagineSeeingYouHere, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 10
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 20
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 30
	msgbox Route110_Text_HeardYouInstallMatchCall, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route110_Text_RegisteredBirchInPokenav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
	msgbox Route110_Text_KeepAnEyeOutForRival, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 1
	call_if_eq Route110_EventScript_BirchExit1
	compare VAR_0x8008, 2
	call_if_eq Route110_EventScript_BirchExit2
	compare VAR_0x8008, 3
	call_if_eq Route110_EventScript_BirchExit3
	compare VAR_0x8008, 4
	call_if_eq Route110_EventScript_BirchExit4
	removeobject LOCALID_BIRCH
	setvar VAR_REGISTER_BIRCH_STATE, 2
	releaseall
	end

Route110_EventScript_BirchApproachPlayer1:: @ 81EFAD8
	applymovement LOCALID_BIRCH, Route110_Movement_BirchApproachPlayer1
	waitmovement 0
	return

Route110_EventScript_BirchApproachPlayer2:: @ 81EFAE3
	applymovement LOCALID_BIRCH, Route110_Movement_BirchApproachPlayer2
	waitmovement 0
	return

Route110_EventScript_BirchApproachPlayer3:: @ 81EFAEE
	applymovement LOCALID_BIRCH, Route110_Movement_BirchApproachPlayer3
	waitmovement 0
	return

Route110_EventScript_BirchApproachPlayer4:: @ 81EFAF9
	applymovement LOCALID_BIRCH, Route110_Movement_BirchApproachPlayer4
	waitmovement 0
	return

Route110_EventScript_BirchExit1:: @ 81EFB04
	applymovement LOCALID_BIRCH, Route110_Movement_BirchExit1
	waitmovement 0
	return

Route110_EventScript_BirchExit2:: @ 81EFB0F
	applymovement LOCALID_BIRCH, Route110_Movement_BirchExit2
	waitmovement 0
	return

Route110_EventScript_BirchExit3:: @ 81EFB1A
	applymovement LOCALID_BIRCH, Route110_Movement_BirchExit3
	waitmovement 0
	return

Route110_EventScript_BirchExit4:: @ 81EFB25
	applymovement LOCALID_BIRCH, Route110_Movement_BirchExit4
	waitmovement 0
	return

Route110_Movement_BirchEntrance: @ 81EFB30
	walk_down
	walk_down
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer1: @ 81EFB34
	walk_down
	walk_left
	walk_left
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer2: @ 81EFB39
	walk_down
	walk_left
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer3: @ 81EFB3D
	walk_down
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer4: @ 81EFB40
	walk_down
	walk_right
	walk_down
	step_end

Route110_Movement_BirchExit1: @ 81EFB44
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

Route110_Movement_BirchExit2: @ 81EFB4B
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route110_Movement_BirchExit3: @ 81EFB51
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route110_Movement_BirchExit4: @ 81EFB57
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route110_Text_WeCantTalkAboutAquaActivities: @ 81EFB5D
	.string "아쿠아단의 활동에 대해서\n"
	.string "지금은 아직\l"
	.string "아무에게도 말할 수 없어$"

Route110_Text_KickUpARuckus: @ 81EFB93
	.string "나도 잿빛도시에 가서\n"
	.string "한바탕하고 싶었는데-!$"

Route110_Text_MyFirstJobInAqua: @ 81EFBCA
	.string "아쿠아단에 들어와서 맡은\n"
	.string "첫 일이야... 두근두근$"

Route110_Text_AquaActionsBringSmiles: @ 81EFC0D
	.string "아쿠아단의 활동은 반드시\n"
	.string "사람들에게 웃음을 주게 될 거야$"

Route110_Text_MayLetsBattle: @ 81EFC48
	.string "봄이: {PLAYER}{K_AYA} 오랜만!\p"
	.string "여러 포켓몬을 찾는 동안에\n"
	.string "내 포켓몬들도 강해졌어!\p"
	.string "그러니까...\n"
	.string "잠깐 승부하자!$"

Route110_Text_MayDefeated: @ 81EFCCB
	.string "으아-!\n"
	.string "생각했던 것보다 강하구나!$"

Route110_Text_MayTakeThis: @ 81EFCF1
	.string "봄이: {PLAYER}도\n"
	.string "포켓몬을 잘 키우고 있구나!\p"
	.string "음 그럼 이건\n"
	.string "내가 주는 선물이야!$"

Route110_Text_MayExplainItemfinder: @ 81EFD58
	.string "봄이: 그건 다우징머신!\p"
	.string "다우징머신을 쓰면\n"
	.string "눈에는 보이지 않아도 떨어져 있는\l"
	.string "도구에 반응하여\l"
	.string "소리로 알려준다고!\p"
	.string "그럼 {PLAYER}\n"
	.string "또 어디선가 보자!\p"
	.string "진 내가 이런 말하긴 그렇지만\n"
	.string "그때까지 좀 더 포켓몬\l"
	.string "키워두는 게 좋을걸!$"

Route110_Text_BrendanLetsBattle: @ 81EFE3F
	.string "휘웅: {PLAYER}{K_I}구나\n"
	.string "이런 곳에 있었네\l"
	.string "어떻게 지냈어?\p"
	.string "포켓몬이 어떻게 성장했는지\n"
	.string "내가 확인해줄게$"

Route110_Text_BrendanDefeated: @ 81EFEB4
	.string "흠...\n"
	.string "꽤 하네$"

Route110_Text_BrendanTakeThis: @ 81EFECD
	.string "휘웅: {PLAYER} 어느새\n"
	.string "이렇게 포켓몬을 키웠구나...\p"
	.string "좋아!\n"
	.string "이걸 줄게$"

Route110_Text_BrendanExplainItemfinder: @ 81EFF1C
	.string "휘웅: 그 녀석은 다우징머신\p"
	.string "쓰면 눈에는 보이지 않아도\n"
	.string "떨어져 있는 도구가 있으면\l"
	.string "반응하여 소리로 장소를 알려줘\p"
	.string "그럼 난 새로운\n"
	.string "포켓몬을 찾으러 갈게$"

Route110_Text_RideBikeAtFullSpeed: @ 81EFFC3
	.string "이 사이클링 로드를\n"
	.string "자전거로 달려나가면\l"
	.string "훨씬 기분 좋을 거야!$"

Route110_Text_HairStreamsBehindMe: @ 81F0006
	.string "어때? 바람에 휘날리는\n"
	.string "나의 검은 머리가!\p"
	.string "이걸 위해 머리를 기른 거라고!$"

Route110_Text_YouGotBikeFromRydel: @ 81F006A
	.string "어! 그 자전거\n"
	.string "미스터 카제노에게 받았구나!\p"
	.string "딱 보면 알지\n"
	.string "왜냐면 너의 자전거에...\p"
	.string "카제노 카제노 카제노 카제노 카제노\n"
	.string "카제노 카제노 카제노 카제노\p"
	.string "카제노 카제노 카제노 카제노 카제노\n"
	.string "카제노 카제노 카제노 카제노\p"
	.string "카제노 카제노 카제노 카제노 카제노\n"
	.string "카제노 카제노 카제노 카제노\p"
	.string "카제노 카제노 카제노 카제노 카제노\n"
	.string "카제노 카제노 카제노 카제노\p"
	.string "카제노 카제노 카제노 카제노 카제노\n"
	.string "카제노 카제노 카제노 카제노\l"
	.string "...라고 쓰여 있거든!\p"
	.string "여기저기 타고 다니며\n"
	.string "선전해주면 좋을 거야!$"

Route110_Text_TwoRoads: @ 81F0261
	.string "위와 아래 2가지 도로...\p"
	.string "사람과 포켓몬\n"
	.string "각각의 도로라고 생각하면\l"
	.string "이런 게 있는 것도 이해는 가네$"

Route110_Text_WalkOnTheLowRoad: @ 81F02CA
	.string "난 자전거가 없어서 말이야\n"
	.string "아래쪽 길을 느긋하게 걸어갈 거야$"

Route110_Text_BikeTechniques: @ 81F030E
	.string "여러 테크닉을 배우면\n"
	.string "더욱 자전거가 즐거워질 거야!\p"
	.string "테크닉을 안 쓰면\n"
	.string "지나갈 수 없는 장소도 있어!$"

Route110_Text_WhichShouldIChoose: @ 81F0390
	.string "사이클링 로드를 타고\n"
	.string "보라시티로 갈지\p"
	.string "아래쪽 길로 가서\n"
	.string "포켓몬을 찾을지\l"
	.string "어느 쪽으로 할까?$"

Route110_Text_CyclingChallengeResultSummary: @ 81F03FF
	.string "부딪힌 횟수\n"
	.string " ... {STR_VAR_1}!\p"
	.string "걸린 타임\n"
	.string " ... {STR_VAR_2}!$"

Route110_Text_ChallengeReactionBest: @ 81F0431
	.string "브라보-!! 대단해!!\p"
	.string "넌 자전거를 진심으로\n"
	.string "사랑하고 있어! 영혼까지 감동했어!$"

Route110_Text_ChallengeReactionGood: @ 81F04A4
	.string "어느 정도의 테크닉을 가지고 있군!\p"
	.string "뭐 너무 스피드를 내서\n"
	.string "사고를 일으키지 않도록 하라고!$"

Route110_Text_ChallengeReactionOk: @ 81F0500
	.string "아직 미숙한 부분도 있지만\n"
	.string "모처럼 이렇게 자전거를\l"
	.string "즐기고 있다는 그 마음을 잊지는 마$"

Route110_Text_ChallengeReactionBad: @ 81F0567
	.string "이봐 이봐 뭔가\n"
	.string "아슬아슬한 운전을 하고 있네\l"
	.string "좀 더 연습하라고$"

Route110_Text_ChallengeReactionWorst: @ 81F05CE
	.string "끄응... 끄으응...\p"
	.string "너에게 자전거는 어울리지 않는지도\n"
	.string "미스터 카제노에게 돌려주는 게 어때?$"

Route110_Text_RatedForNumberOfCollisions: @ 81F0661
	.string "이 사이클링 로드!\p"
	.string "보라시티에서 잿빛도시로 향해서\n"
	.string "마하자전거로 달려나가는\l"
	.string "레이서의 부딪힌 횟수와\l"
	.string "걸린 타임을 재고 있어!$"

Route110_Text_AlwaysAimHigher: @ 81F06FB
	.string "어떤 결과가 나오든 더 위를\n"
	.string "노리는 도전자가 기다리고 있어!$"

Route110_Text_AcroBikesDoNotQualify: @ 81F0755
	.string "이 사이클링 로드에서는\n"
	.string "마하자전거로 달려나가는\l"
	.string "레이서의 부딪힌 횟수와\l"
	.string "걸린 타임을 재고 있어!\p"
	.string "더트자전거라면 꺾이기 쉬우니까\n"
	.string "기록을 잴 수 없어!$"

Route110_Text_SlateportCitySign: @ 81F0812
	.string "여기는 110번 도로\n"
	.string "{DOWN_ARROW} 잿빛도시$"

Route110_Text_CyclingRoadSign: @ 81F082D
	.string "“시사이드 사이클링 로드”$"

Route110_Text_AquaWasHere: @ 81F0842
	.string "“아쿠아단 등장!”\p"
	.string "...간판에 낙서가 있다\n"
	.string "그 낙서 위에 다른 페인트로\p"
	.string "“마그마단 등장!”\n"
	.string "...이라고 적혀 있다$"
	// 「アクアだん さんじょう!」ｐ
	// ……と かんばんに らくがき されているがｎ
	// そのもじの うえに べつのペンキでｐ
	// 「マグマだん さんじょう!」ｎ
	// ……と かかれている

Route110_Text_Route103Sign: @ 81F08CD
	.string "여기는 110번 도로\n"
	.string "{LEFT_ARROW} 103번 도로$"

Route110_Text_SeasideParkingSign: @ 81F08E3
	.string "“시사이드 주차장”$"

Route110_Text_MauvilleCitySign: @ 81F08F3
	.string "여기는 110번 도로\n"
	.string "{UP_ARROW} 보라시티$"

Route110_Text_TrainerTipsPrlzSleep: @ 81F090D
	.string "정보 나눔 게시판!!\p"
	.string "포켓몬은 잠들게 하거나 마비시키면\n"
	.string "상대의 자유를 뺏을 수 있습니다!\p"
	.string "이것은 포켓몬 승부의\n"
	.string "중요한 테크닉입니다!$"

Route110_Text_TrainerTipsRegisterItems: @ 81F0992
	.string "정보 나눔 게시판!!\p"
	.string "가방의 메뉴에서\n"
	.string "SELECT 버튼을 누르면\l"
	.string "도구의 순서를 바꿀 수 있습니다$"

Route110_Text_TrickHouseSign: @ 81F09DB
	.string "여기서부터 {RIGHT_ARROW}3걸음 {UP_ARROW}2걸음 가면\n"
	.string "그곳은 멋진 “미궁의 대저택”!$"

Route110_Text_BestRecord: @ 81F0A1E
	.string "지금까지의 최고 기록...\p"
	.string "부딪힌 횟수\n"
	.string " ... {STR_VAR_1}!\p"
	.string "걸린 타임\n"
	.string " ... {STR_VAR_2}!!$"

Route110_Text_ThereIsNoRecord: @ 81F0A5E
	.string "지금까지의 최고 기록...\p"
	.string "아직 도전하지 않았는지\n"
	.string "아무것도 기록되어 있지 않다!$"

Route110_Text_ImagineSeeingYouHere: @ 81F0AB5
	.string "털보박사: 오오 {PLAYER}{K_AYA}!\n"
	.string "이런 곳에 있었구나!\p"
	.string "으-음 우리 {RIVAL}{K_EUNNEUN}...$"
	// オダマキ『おお §あ§お!ｎ
	// こんな ところに いたのかい!ｐ
	// え-と うちの §かは……

Route110_Text_HeardYouInstallMatchCall: @ 81F0AFF
	.string "그런가!\n"
	.string "너희들 따로 다니고 있구나\p"
	.string "뭐 그건 제쳐두고...\n"
	.string "그래그래! 너의 포켓내비에\l"
	.string "엔트리콜이 세팅되어 있지?\p"
	.string "그렇다면 나도 등록해줘!\p"
	.string "그러면 너하고 떨어져 있어도\n"
	.string "언제든지 포켓몬 도감의 평가를\l"
	.string "해줄 수 있으니까!\p"
	.string "...... ...... ......$"
	// そうか!ｎ
	// きみたちは べつこうどう なんだねｐ
	// まあ それは いいとして……ｎ
	// そうそう! きみの ポケナビにｌ
	// エントリ-コ-ルが セットされたって?ｐ
	// ならば わたしも とうろく しておこう!ｐ
	// そうすれば きみと はなれていてもｎ
	// いつでも ポケモンずかんの ひょうかをｌ
	// してあげられる からね!ｐ
	// …… …… ……

Route110_Text_RegisteredBirchInPokenav: @ 81F0C0C
	.string "털보박사를\n"
	.string "포켓내비에 등록했다!$"
	// オダマキはかせをｎ
	// ポケナビに とうろく した!

Route110_Text_KeepAnEyeOutForRival: @ 81F0C33
	.string "털보박사: {PLAYER}{K_AYA}...\p"
	.string "{RIVAL}{K_I}를 잘 부탁한다\n"
	.string "...... ...... ......\p"
	.string "그럼 난 이제 가보도록 하마\n"
	.string "나중에 보자 {PLAYER}{K_AYA}!$"
	// オダマキ『§あ§お……ｐ
	// §かのこと よろしく たのむよｎ
	// …… …… ……ｐ
	// じゃあ わたしは これで しつれいするｎ
	// またな §あ§お!

