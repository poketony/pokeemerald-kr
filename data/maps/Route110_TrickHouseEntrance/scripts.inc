.set LOCALID_TRICK_MASTER, 1

Route110_TrickHouseEntrance_MapScripts:: @ 8269A50
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHouseEntrance_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route110_TrickHouseEntrance_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route110_TrickHouseEntrance_OnWarp
	.byte 0

	@ State descriptions for VAR_TRICK_HOUSE_ENTRANCE_STATE
	@ 0: Trick Master is hiding
	@ 1: Trick Master has left at start of challenge
	@ 2: Trick Master ready to give normal reward from previous challenge (if bag was full)
	@ 3: Trick Master still making next puzzle
	@ 4: Finished final puzzle
	@ 5: Completed previous challenge
	@ 6: 'Trick Master' mechadoll ready to give Tent reward from final challenge (if bag was full)

Route110_TrickHouseEntrance_OnTransition: @ 8269A60
	setflag FLAG_LANDMARK_TRICK_HOUSE
	compare VAR_TRICK_HOUSE_ENTER_FROM_CORRIDOR, 1
	goto_if_eq Route110_TrickHouseEntrance_EventScript_EnterFromCorridor
	compare VAR_TRICK_HOUSE_PRIZE_PICKUP, 1
	goto_if_eq Route110_TrickHouseEntrance_EventScript_SetReadyToGiveReward
	compare VAR_TRICK_HOUSE_FOUND_TRICK_MASTER, 1
	goto_if_eq Route110_TrickHouseEntrance_EventScript_MoveTrickMasterToDoor
	compare VAR_TRICK_HOUSE_ENTRANCE_STATE, 5
	call_if_eq Route110_TrickHouseEntrance_EventScript_CheckReadyForNextPuzzle
	compare VAR_TRICK_HOUSE_ENTRANCE_STATE, 3
	call_if_eq Route110_TrickHouseEntrance_EventScript_CheckReadyForNextPuzzle
	compare VAR_TRICK_HOUSE_ENTRANCE_STATE, 0
	call_if_eq Route110_TrickHouseEntrance_EventScript_CheckReadyForNextPuzzle
	switch VAR_TRICK_HOUSE_ENTRANCE_STATE
	case 0, Route110_TrickHouseEntrance_EventScript_ReadyBeingWatchedTrigger
	case 1, Route110_TrickHouseEntrance_EventScript_SetNotBeingWatched1
	case 3, Route110_TrickHouseEntrance_EventScript_SetNotBeingWatched2
	case 4, Route110_TrickHouseEntrance_EventScript_SetNotBeingWatched3
	end

Route110_TrickHouseEntrance_EventScript_SetReadyToGiveReward:: @ 8269AD7
	setvar VAR_TRICK_HOUSE_BEING_WATCHED_STATE, 1
	compare VAR_TRICK_HOUSE_LEVEL, 8
	goto_if_eq Route110_TrickHouseEntrance_EventScript_ReadyToGiveTentReward
	setvar VAR_TRICK_HOUSE_ENTRANCE_STATE, 2
	end

Route110_TrickHouseEntrance_EventScript_ReadyToGiveTentReward:: @ 8269AED
	setvar VAR_TRICK_HOUSE_ENTRANCE_STATE, 6
	end

Route110_TrickHouseEntrance_EventScript_EnterFromCorridor:: @ 8269AF3
	setvar VAR_TRICK_HOUSE_ENTER_FROM_CORRIDOR, 0
	setvar VAR_TRICK_HOUSE_ENTRANCE_STATE, 5
	setvar VAR_TRICK_HOUSE_BEING_WATCHED_STATE, 1
	end

Route110_TrickHouseEntrance_EventScript_CheckReadyForNextPuzzle:: @ 8269B03
	setvar VAR_TRICK_HOUSE_ENTRANCE_STATE, 0
	compare VAR_TRICK_HOUSE_LEVEL, 1
	call_if_eq Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle2
	compare VAR_TRICK_HOUSE_LEVEL, 2
	call_if_eq Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle3
	compare VAR_TRICK_HOUSE_LEVEL, 3
	call_if_eq Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle4
	compare VAR_TRICK_HOUSE_LEVEL, 4
	call_if_eq Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle5
	compare VAR_TRICK_HOUSE_LEVEL, 5
	call_if_eq Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle6
	compare VAR_TRICK_HOUSE_LEVEL, 6
	call_if_eq Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle7
	compare VAR_TRICK_HOUSE_LEVEL, 7
	call_if_eq Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle8
	compare VAR_TRICK_HOUSE_LEVEL, 8
	call_if_eq Route110_TrickHouseEntrance_EventScript_FinishedPuzzles
	return

Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle2:: @ 8269B61
	call_if_unset FLAG_BADGE03_GET, Route110_TrickHouseEntrance_EventScript_NotReadyForPuzzle
	return

Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle3:: @ 8269B6B
	call_if_unset FLAG_BADGE04_GET, Route110_TrickHouseEntrance_EventScript_NotReadyForPuzzle
	return

Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle4:: @ 8269B75
	call_if_unset FLAG_BADGE05_GET, Route110_TrickHouseEntrance_EventScript_NotReadyForPuzzle
	return

Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle5:: @ 8269B7F
	call_if_unset FLAG_BADGE06_GET, Route110_TrickHouseEntrance_EventScript_NotReadyForPuzzle
	return

Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle6:: @ 8269B89
	call_if_unset FLAG_BADGE07_GET, Route110_TrickHouseEntrance_EventScript_NotReadyForPuzzle
	return

Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle7:: @ 8269B93
	call_if_unset FLAG_BADGE08_GET, Route110_TrickHouseEntrance_EventScript_NotReadyForPuzzle
	return

Route110_TrickHouseEntrance_EventScript_CheckReadyForPuzzle8:: @ 8269B9D
	call_if_unset FLAG_SYS_GAME_CLEAR, Route110_TrickHouseEntrance_EventScript_NotReadyForPuzzle
	return

Route110_TrickHouseEntrance_EventScript_FinishedPuzzles:: @ 8269BA7
	setvar VAR_TRICK_HOUSE_ENTRANCE_STATE, 4
	return

Route110_TrickHouseEntrance_EventScript_NotReadyForPuzzle:: @ 8269BAD
	setvar VAR_TRICK_HOUSE_ENTRANCE_STATE, 3
	return

Route110_TrickHouseEntrance_EventScript_MoveTrickMasterToDoor:: @ 8269BB3
	setobjectxyperm LOCALID_TRICK_MASTER, 5, 2
	end

Route110_TrickHouseEntrance_EventScript_ReadyBeingWatchedTrigger:: @ 8269BBB
	setvar VAR_TRICK_HOUSE_BEING_WATCHED_STATE, 0
	end

Route110_TrickHouseEntrance_EventScript_SetNotBeingWatched1:: @ 8269BC1
	setvar VAR_TRICK_HOUSE_BEING_WATCHED_STATE, 1
	end

Route110_TrickHouseEntrance_EventScript_SetNotBeingWatched2:: @ 8269BC7
	setvar VAR_TRICK_HOUSE_BEING_WATCHED_STATE, 1
	end

Route110_TrickHouseEntrance_EventScript_SetNotBeingWatched3:: @ 8269BCD
	setvar VAR_TRICK_HOUSE_BEING_WATCHED_STATE, 1
	end

Route110_TrickHouseEntrance_OnWarp: @ 8269BD3
	map_script_2 VAR_TRICK_HOUSE_FOUND_TRICK_MASTER, 1, Route110_TrickHouseEntrance_EventScript_TrickMasterFound
	map_script_2 VAR_TRICK_HOUSE_ENTRANCE_STATE, 0, Route110_TrickHouseEntrance_EventScript_SetTrickMasterHidingSpot
	map_script_2 VAR_TRICK_HOUSE_ENTRANCE_STATE, 1, Route110_TrickHouseEntrance_EventScript_RemoveTrickMaster
	map_script_2 VAR_TRICK_HOUSE_ENTRANCE_STATE, 2, Route110_TrickHouseEntrance_EventScript_SetTrickMasterFacingDoor
	map_script_2 VAR_TRICK_HOUSE_ENTRANCE_STATE, 3, Route110_TrickHouseEntrance_EventScript_SetTrickMasterFacingDoor
	map_script_2 VAR_TRICK_HOUSE_ENTRANCE_STATE, 4, Route110_TrickHouseEntrance_EventScript_RemoveTrickMaster
	map_script_2 VAR_TRICK_HOUSE_ENTRANCE_STATE, 5, Route110_TrickHouseEntrance_EventScript_RemoveTrickMaster
	map_script_2 VAR_TRICK_HOUSE_ENTRANCE_STATE, 6, Route110_TrickHouseEntrance_EventScript_SetTrickMasterInFrontOfDoor
	.2byte 0

Route110_TrickHouseEntrance_EventScript_TrickMasterFound:: @ 8269C15
	addobject LOCALID_TRICK_MASTER
	showobjectat LOCALID_TRICK_MASTER, MAP_ROUTE110_TRICK_HOUSE_ENTRANCE
	turnobject LOCALID_TRICK_MASTER, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	end

Route110_TrickHouseEntrance_EventScript_SetTrickMasterHidingSpot:: @ 8269C26
	addobject LOCALID_TRICK_MASTER
	hideobjectat LOCALID_TRICK_MASTER, MAP_ROUTE110_TRICK_HOUSE_ENTRANCE
	switch VAR_TRICK_HOUSE_LEVEL
	case 0, Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle1
	case 1, Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle2
	case 2, Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle3
	case 3, Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle4
	case 4, Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle5
	case 5, Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle6
	case 6, Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle7
	case 7, Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle8
	end

Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle1:: @ 8269C8C
	setobjectxy LOCALID_TRICK_MASTER, 6, 3
	end

Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle2:: @ 8269C94
	setobjectxy LOCALID_TRICK_MASTER, 11, 5
	end

Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle3:: @ 8269C9C
	setobjectxy LOCALID_TRICK_MASTER, 9, 1
	end

Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle4:: @ 8269CA4
	setobjectxy LOCALID_TRICK_MASTER, 3, 1
	end

Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle5:: @ 8269CAC
	setobjectxy LOCALID_TRICK_MASTER, 0, 5
	end

Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle6:: @ 8269CB4
	setobjectxy LOCALID_TRICK_MASTER, 11, 1
	end

Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle7:: @ 8269CBC
	setobjectxy LOCALID_TRICK_MASTER, 8, 1
	end

Route110_TrickHouseEntrance_EventScript_SetHidingSpotPuzzle8:: @ 8269CC4
	setobjectxy LOCALID_TRICK_MASTER, 4, 4
	end

Route110_TrickHouseEntrance_EventScript_RemoveTrickMaster:: @ 8269CCC
	removeobject LOCALID_TRICK_MASTER
	end

Route110_TrickHouseEntrance_EventScript_SetTrickMasterFacingDoor:: @ 8269CD0
	addobject LOCALID_TRICK_MASTER
	setobjectxy LOCALID_TRICK_MASTER, 5, 2
	turnobject LOCALID_TRICK_MASTER, DIR_NORTH
	end

Route110_TrickHouseEntrance_EventScript_SetTrickMasterInFrontOfDoor:: @ 8269CDF
	addobject LOCALID_TRICK_MASTER
	setobjectxy LOCALID_TRICK_MASTER, 5, 2
	turnobject LOCALID_TRICK_MASTER, DIR_SOUTH
	end

Route110_TrickHouseEntrance_OnFrame: @ 8269CEE
	map_script_2 VAR_TRICK_HOUSE_FOUND_TRICK_MASTER, 1, Route110_TrickHouseEntrance_EventScript_BeginChallenge
	.2byte 0

Route110_TrickHouseEntrance_EventScript_BeginChallenge:: @ 8269CF8
	lockall
	delay 20
	compare VAR_TRICK_HOUSE_LEVEL, 0
	call_if_eq Route110_TrickHouseEntrance_EventScript_MeetTrickMaster
	msgbox Route110_TrickHouseEntrance_Text_ComeToChallengeTrickHouse, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement LOCALID_TRICK_MASTER, Route110_TrickHouse_Movement_TrickMasterSpin
	waitmovement 0
	playse SE_M_EXPLOSION
	applymovement LOCALID_TRICK_MASTER, Route110_TrickHouse_Movement_TrickMasterJumpAway
	waitmovement 0
	removeobject LOCALID_TRICK_MASTER
	setvar VAR_TRICK_HOUSE_ENTRANCE_STATE, 1
	setvar VAR_TRICK_HOUSE_FOUND_TRICK_MASTER, 0
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_UnusedRelease:: @ 8269D39
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_TrickMaster:: @ 8269D3B
	lockall
	switch VAR_TRICK_HOUSE_ENTRANCE_STATE
	case 0, Route110_TrickHouseEntrance_EventScript_FoundTrickMaster
	case 2, Route110_TrickHouseEntrance_EventScript_GiveReward
	case 3, Route110_TrickHouseEntrance_EventScript_StillMakingPuzzle
	case 6, Route110_TrickHouseEntrance_EventScript_MechadollReward
	end

Route110_TrickHouseEntrance_EventScript_FoundTrickMaster:: @ 8269D6E
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	compare VAR_TRICK_HOUSE_LEVEL, 0
	call_if_eq Route110_TrickHouseEntrance_EventScript_FoundBeneathDesk
	compare VAR_TRICK_HOUSE_LEVEL, 1
	call_if_eq Route110_TrickHouseEntrance_EventScript_FoundBehindTree
	compare VAR_TRICK_HOUSE_LEVEL, 2
	call_if_eq Route110_TrickHouseEntrance_EventScript_FoundInDresser
	compare VAR_TRICK_HOUSE_LEVEL, 3
	call_if_eq Route110_TrickHouseEntrance_EventScript_FoundBeyondWindow
	compare VAR_TRICK_HOUSE_LEVEL, 4
	call_if_eq Route110_TrickHouseEntrance_EventScript_FoundInPlanter
	compare VAR_TRICK_HOUSE_LEVEL, 5
	call_if_eq Route110_TrickHouseEntrance_EventScript_FoundInCupboard
	compare VAR_TRICK_HOUSE_LEVEL, 6
	call_if_eq Route110_TrickHouseEntrance_EventScript_FoundBehindWindow
	compare VAR_TRICK_HOUSE_LEVEL, 7
	call_if_eq Route110_TrickHouseEntrance_EventScript_FoundBeneathCushion
	closemessage
	setvar VAR_TRICK_HOUSE_FOUND_TRICK_MASTER, 1
	warpsilent MAP_ROUTE110_TRICK_HOUSE_ENTRANCE, 255, 6, 2
	waitstate
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_FoundBeneathDesk:: @ 8269DEE
	msgbox Route110_TrickHouseEntrance_Text_ConcealedBeneathDesk, MSGBOX_DEFAULT
	return

Route110_TrickHouseEntrance_EventScript_FoundBehindTree:: @ 8269DF7
	msgbox Route110_TrickHouseEntrance_Text_ConcealedBehindTree, MSGBOX_DEFAULT
	return

Route110_TrickHouseEntrance_EventScript_FoundInDresser:: @ 8269E00
	msgbox Route110_TrickHouseEntrance_Text_ConcealedInDresser, MSGBOX_DEFAULT
	return

Route110_TrickHouseEntrance_EventScript_FoundBeyondWindow:: @ 8269E09
	msgbox Route110_TrickHouseEntrance_Text_ConealedBeyondWindow, MSGBOX_DEFAULT
	return

Route110_TrickHouseEntrance_EventScript_FoundInPlanter:: @ 8269E12
	msgbox Route110_TrickHouseEntrance_Text_ConcealedInPlanter, MSGBOX_DEFAULT
	return

Route110_TrickHouseEntrance_EventScript_FoundInCupboard:: @ 8269E1B
	msgbox Route110_TrickHouseEntrance_Text_ConcealedInCupboard, MSGBOX_DEFAULT
	return

Route110_TrickHouseEntrance_EventScript_FoundBehindWindow:: @ 8269E24
	msgbox Route110_TrickHouseEntrance_Text_ConcealedBehindWindow, MSGBOX_DEFAULT
	return

Route110_TrickHouseEntrance_EventScript_FoundBeneathCushion:: @ 8269E2D
	msgbox Route110_TrickHouseEntrance_Text_ConcealedBeneathCushion, MSGBOX_DEFAULT
	return

Route110_TrickHouse_Movement_TrickMasterSpin: @ 8269E36
	face_up
	delay_4
	face_left
	delay_4
	face_down
	delay_4
	face_right
	delay_4
	step_end

Route110_TrickHouse_Movement_TrickMasterJumpAway: @ 8269E3F
	face_up
	disable_anim
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end

Route110_TrickHouseEntrance_EventScript_MeetTrickMaster:: @ 8269E48
	msgbox Route110_TrickHouseEntrance_Text_TheyCallMeTrickMaster, MSGBOX_DEFAULT
	return

Route110_TrickHouseEntrance_EventScript_StillMakingPuzzle:: @ 8269E51
	msgbox Route110_TrickHouseEntrance_Text_NextTimeUseThisTrick, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TRICK_MASTER, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_TRICK_MASTER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_TRICK_MASTER, Common_Movement_Delay48
	waitmovement 0
	msgbox Route110_TrickHouseEntrance_Text_InMidstOfDevisingNewChallenges, MSGBOX_DEFAULT
	applymovement LOCALID_TRICK_MASTER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_GiveReward:: @ 8269E8F
	applymovement LOCALID_TRICK_MASTER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Route110_TrickHouseEntrance_Text_YoureHereToAcceptReward, MSGBOX_DEFAULT
	compare VAR_TRICK_HOUSE_LEVEL, 1
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GivePuzzle1Reward
	compare VAR_TRICK_HOUSE_LEVEL, 2
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GivePuzzle2Reward
	compare VAR_TRICK_HOUSE_LEVEL, 3
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GivePuzzle3Reward
	compare VAR_TRICK_HOUSE_LEVEL, 4
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GivePuzzle4Reward
	compare VAR_TRICK_HOUSE_LEVEL, 5
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GivePuzzle5Reward
	compare VAR_TRICK_HOUSE_LEVEL, 6
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GivePuzzle6Reward
	compare VAR_TRICK_HOUSE_LEVEL, 7
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GivePuzzle7Reward
	end

Route110_TrickHouseEntrance_EventScript_GivePuzzle1Reward:: @ 8269EEF
	giveitem ITEM_RARE_CANDY
	compare VAR_RESULT, TRUE
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GotReward
	compare VAR_RESULT, FALSE
	call_if_eq Common_EventScript_BagIsFull
	msgbox Route110_TrickHouseEntrance_Text_DidYouNotComeToClaimReward, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_GivePuzzle2Reward:: @ 8269F1B
	giveitem ITEM_TIMER_BALL
	compare VAR_RESULT, TRUE
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GotReward
	compare VAR_RESULT, FALSE
	call_if_eq Common_EventScript_BagIsFull
	msgbox Route110_TrickHouseEntrance_Text_DidYouNotComeToClaimReward, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_GivePuzzle3Reward:: @ 8269F47
	giveitem ITEM_HARD_STONE
	compare VAR_RESULT, TRUE
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GotReward
	compare VAR_RESULT, FALSE
	call_if_eq Common_EventScript_BagIsFull
	msgbox Route110_TrickHouseEntrance_Text_DidYouNotComeToClaimReward, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_GivePuzzle4Reward:: @ 8269F73
	giveitem ITEM_SMOKE_BALL
	compare VAR_RESULT, TRUE
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GotReward
	compare VAR_RESULT, FALSE
	call_if_eq Common_EventScript_BagIsFull
	msgbox Route110_TrickHouseEntrance_Text_DidYouNotComeToClaimReward, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_GivePuzzle5Reward:: @ 8269F9F
	giveitem ITEM_TM12
	compare VAR_RESULT, TRUE
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GotReward
	compare VAR_RESULT, FALSE
	call_if_eq Common_EventScript_BagIsFull
	msgbox Route110_TrickHouseEntrance_Text_DidYouNotComeToClaimReward, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_GivePuzzle6Reward:: @ 8269FCB
	giveitem ITEM_MAGNET
	compare VAR_RESULT, TRUE
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GotReward
	compare VAR_RESULT, FALSE
	call_if_eq Common_EventScript_BagIsFull
	msgbox Route110_TrickHouseEntrance_Text_DidYouNotComeToClaimReward, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_GivePuzzle7Reward:: @ 8269FF7
	giveitem ITEM_PP_MAX
	compare VAR_RESULT, TRUE
	goto_if_eq Route110_TrickHouseEntrance_EventScript_GotReward
	compare VAR_RESULT, FALSE
	call_if_eq Common_EventScript_BagIsFull
	msgbox Route110_TrickHouseEntrance_Text_DidYouNotComeToClaimReward, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_GotReward:: @ 826A023
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	setvar VAR_TRICK_HOUSE_ENTRANCE_STATE, 3
	applymovement LOCALID_TRICK_MASTER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_MechadollReward:: @ 826A039
	applymovement LOCALID_TRICK_MASTER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Route110_TrickHouseEntrance_Text_MechadollWhichTent, MSGBOX_DEFAULT
	call Route110_TrickHouseEntrance_EventScript_ChooseTent
	compare VAR_RESULT, TRUE
	goto_if_eq Route110_TrickHouseEntrance_EventScript_ReceivedTent
	compare VAR_RESULT, FALSE
	call_if_eq Common_EventScript_NoRoomForDecor
	msgbox Route110_TrickHouseEntrance_Text_PCFullAgain, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_ChooseTent:: @ 826A070
	multichoice 0, 0, MULTI_TENT, 1
	switch VAR_RESULT
	case 0, Route110_TrickHouseEntrance_EventScript_GiveRedTent
	goto Route110_TrickHouseEntrance_EventScript_GiveBlueTent

Route110_TrickHouseEntrance_EventScript_GiveRedTent:: @ 826A08A
	givedecoration DECOR_RED_TENT
	return

Route110_TrickHouseEntrance_EventScript_GiveBlueTent:: @ 826A092
	givedecoration DECOR_BLUE_TENT
	return

Route110_TrickHouseEntrance_EventScript_ReceivedTent:: @ 826A09A
	msgbox Route110_TrickHouseEntrance_Text_ThenFarewell, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TRICK_MASTER, Route110_TrickHousePuzzle5_Movement_MechadollShake
	waitmovement 0
	applymovement LOCALID_TRICK_MASTER, Route110_TrickHouse_Movement_TrickMasterSpin
	waitmovement 0
	playse SE_M_EXPLOSION
	applymovement LOCALID_TRICK_MASTER, Route110_TrickHouse_Movement_TrickMasterJumpAway
	waitmovement 0
	removeobject LOCALID_TRICK_MASTER
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	setvar VAR_TRICK_HOUSE_ENTRANCE_STATE, 5
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_Door:: @ 826A0D3
	lockall
	switch VAR_TRICK_HOUSE_ENTRANCE_STATE
	case 0, Route110_TrickHouseEntrance_EventScript_ItsAScroll
	case 1, Route110_TrickHouseEntrance_EventScript_GoInHolePrompt
	case 4, Route110_TrickHouseEntrance_EventScript_LeftOnJourneyNote
	case 5, Route110_TrickHouseEntrance_EventScript_CheckLevelForMessage
	end

Route110_TrickHouseEntrance_EventScript_ItsAScroll:: @ 826A106
	msgbox Route110_TrickHouseEntrance_Text_ItsAScroll, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_GoInHolePrompt:: @ 826A110
	msgbox Route110_TrickHouseEntrance_Text_GoInHoleBehindScroll, MSGBOX_YESNO
	closemessage
	compare VAR_RESULT, YES
	goto_if_eq Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom:: @ 826A126
	setmetatile 5, 1, METATILE_GenericBuilding_TrickHouse_Stairs_Down, 0
	special DrawWholeMapView
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Route110_TrickHouseEntrance_Movement_EnterRoom
	waitmovement 0
	switch VAR_TRICK_HOUSE_LEVEL
	case 0, Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom1
	case 1, Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom2
	case 2, Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom3
	case 3, Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom4
	case 4, Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom5
	case 5, Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom6
	case 6, Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom7
	case 7, Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom8
	end

Route110_TrickHouseEntrance_Movement_EnterRoom: @ 826A1A7
	set_invisible
	step_end

Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom1:: @ 826A1A9
	warp MAP_ROUTE110_TRICK_HOUSE_PUZZLE1, 255, 0, 21
	waitstate
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom2:: @ 826A1B4
	warp MAP_ROUTE110_TRICK_HOUSE_PUZZLE2, 255, 0, 21
	waitstate
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom3:: @ 826A1BF
	warp MAP_ROUTE110_TRICK_HOUSE_PUZZLE3, 255, 0, 21
	waitstate
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom4:: @ 826A1CA
	warp MAP_ROUTE110_TRICK_HOUSE_PUZZLE4, 255, 0, 21
	waitstate
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom5:: @ 826A1D5
	warp MAP_ROUTE110_TRICK_HOUSE_PUZZLE5, 255, 0, 21
	waitstate
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom6:: @ 826A1E0
	warp MAP_ROUTE110_TRICK_HOUSE_PUZZLE6, 255, 0, 21
	waitstate
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom7:: @ 826A1EB
	warp MAP_ROUTE110_TRICK_HOUSE_PUZZLE7, 255, 0, 21
	waitstate
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_EnterPuzzleRoom8:: @ 826A1F6
	warp MAP_ROUTE110_TRICK_HOUSE_PUZZLE8, 255, 0, 21
	waitstate
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_LeftOnJourneyNote:: @ 826A201
	msgbox Route110_TrickHouseEntrance_Text_LeavingOnJourneyNote, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_CheckLevelForMessage:: @ 826A20B
	compare VAR_TRICK_HOUSE_LEVEL, 8
	goto_if_eq Route110_TrickHouseEntrance_EventScript_LeftOnJourneyNote2
	msgbox Route110_TrickHouseEntrance_Text_ItsAScroll, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_LeftOnJourneyNote2:: @ 826A220
	msgbox Route110_TrickHouseEntrance_Text_LeavingOnJourneyNote, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHousePuzzle_EventScript_Door:: @ 826A22A
	lockall
	switch VAR_TRICK_HOUSE_LEVEL
	case 0, Route110_TrickHousePuzzle1_EventScript_Door
	case 1, Route110_TrickHousePuzzle2_EventScript_Door
	case 2, Route110_TrickHousePuzzle3_EventScript_Door
	case 3, Route110_TrickHousePuzzle4_EventScript_Door
	case 4, Route110_TrickHousePuzzle5_EventScript_Door
	case 5, Route110_TrickHousePuzzle6_EventScript_Door
	case 6, Route110_TrickHousePuzzle7_EventScript_Door
	case 7, Route110_TrickHousePuzzle8_EventScript_Door
	end

Route110_TrickHousePuzzle1_EventScript_Door:: @ 826A289
	compare VAR_TRICK_HOUSE_PUZZLE_1_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle_EventScript_DoorLocked
	msgbox Route110_TrickHousePuzzle1_Text_WroteSecretCodeLockOpened, MSGBOX_DEFAULT
	playse SE_PIN
	setvar VAR_TRICK_HOUSE_PUZZLE_1_STATE, 2
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, 0
	special DrawWholeMapView
	releaseall
	end

Route110_TrickHousePuzzle2_EventScript_Door:: @ 826A2B2
	compare VAR_TRICK_HOUSE_PUZZLE_2_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle_EventScript_DoorLocked
	msgbox Route110_TrickHousePuzzle2_Text_WroteSecretCodeLockOpened, MSGBOX_DEFAULT
	playse SE_PIN
	setvar VAR_TRICK_HOUSE_PUZZLE_2_STATE, 2
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, 0
	special DrawWholeMapView
	releaseall
	end

Route110_TrickHousePuzzle3_EventScript_Door:: @ 826A2DB
	compare VAR_TRICK_HOUSE_PUZZLE_3_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle_EventScript_DoorLocked
	msgbox Route110_TrickHousePuzzle3_Text_WroteSecretCodeLockOpened, MSGBOX_DEFAULT
	playse SE_PIN
	setvar VAR_TRICK_HOUSE_PUZZLE_3_STATE, 2
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, 0
	special DrawWholeMapView
	releaseall
	end

Route110_TrickHousePuzzle4_EventScript_Door:: @ 826A304
	compare VAR_TRICK_HOUSE_PUZZLE_4_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle_EventScript_DoorLocked
	msgbox Route110_TrickHousePuzzle4_Text_WroteSecretCodeLockOpened, MSGBOX_DEFAULT
	playse SE_PIN
	setvar VAR_TRICK_HOUSE_PUZZLE_4_STATE, 2
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, 0
	special DrawWholeMapView
	releaseall
	end

Route110_TrickHousePuzzle5_EventScript_Door:: @ 826A32D
	compare VAR_TRICK_HOUSE_PUZZLE_5_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle_EventScript_DoorLocked
	msgbox Route110_TrickHousePuzzle5_Text_WroteSecretCodeLockOpened, MSGBOX_DEFAULT
	playse SE_PIN
	setvar VAR_TRICK_HOUSE_PUZZLE_5_STATE, 2
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, 0
	special DrawWholeMapView
	releaseall
	end

Route110_TrickHousePuzzle6_EventScript_Door:: @ 826A356
	compare VAR_TRICK_HOUSE_PUZZLE_6_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle_EventScript_DoorLocked
	msgbox Route110_TrickHousePuzzle6_Text_WroteSecretCodeLockOpened, MSGBOX_DEFAULT
	playse SE_PIN
	setvar VAR_TRICK_HOUSE_PUZZLE_6_STATE, 2
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, 0
	special DrawWholeMapView
	releaseall
	end

Route110_TrickHousePuzzle7_EventScript_Door:: @ 826A37F
	compare VAR_TRICK_HOUSE_PUZZLE_7_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle_EventScript_DoorLocked
	msgbox Route110_TrickHousePuzzle7_EventScript_WroteSecretCodeLockOpened, MSGBOX_DEFAULT
	playse SE_PIN
	setvar VAR_TRICK_HOUSE_PUZZLE_7_STATE, 2
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, 0
	special DrawWholeMapView
	releaseall
	end

Route110_TrickHousePuzzle8_EventScript_Door:: @ 826A3A8
	compare VAR_TRICK_HOUSE_PUZZLE_8_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle_EventScript_DoorLocked
	msgbox Route110_TrickHousePuzzle8_EventScript_WroteSecretCodeLockOpened, MSGBOX_DEFAULT
	playse SE_PIN
	setvar VAR_TRICK_HOUSE_PUZZLE_8_STATE, 2
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, 0
	special DrawWholeMapView
	releaseall
	end

Route110_TrickHousePuzzle_EventScript_DoorLocked:: @ 826A3D1
	msgbox Route110_TrickHouseEntrance_Text_DoorLockedWriteSecretCodeHere, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHousePuzzle_EventScript_ReadScrollAgain:: @ 826A3DB
	msgbox Route110_TrickHousePuzzle_Text_SecretCodeWrittenOnIt, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHousePuzzle_EventScript_FoundScroll:: @ 826A3E5
	playfanfare MUS_OBTAIN_ITEM
	message Route110_TrickHousePuzzle_Text_FoundAScroll
	waitfanfare
	msgbox Route110_TrickHousePuzzle_Text_MemorizedSecretCode, MSGBOX_DEFAULT
	releaseall
	end

Route110_TrickHouseEntrance_EventScript_TrickMasterHiding:: @ 826A3F8
	lockall
	msgbox Route110_TrickHouseEntrance_Text_YoureBeingWatched, MSGBOX_DEFAULT
	releaseall
	compare VAR_TRICK_HOUSE_LEVEL, 0
	call_if_eq Route110_TrickHouseEntrance_EventScript_DoHidingSpotSparkle1
	compare VAR_TRICK_HOUSE_LEVEL, 1
	call_if_eq Route110_TrickHouseEntrance_EventScript_DoHidingSpotSparkle2
	compare VAR_TRICK_HOUSE_LEVEL, 2
	call_if_eq Route110_TrickHouseEntrance_EventScript_DoHidingSpotSparkle3
	setvar VAR_TRICK_HOUSE_BEING_WATCHED_STATE, 1
	end

Route110_TrickHouseEntrance_EventScript_DoHidingSpotSparkle1:: @ 826A429
	setvar VAR_0x8004, 6  @ x
	setvar VAR_0x8005, 3  @ y
	call Route110_TrickHouseEntrance_EventScript_DoHidingSpotSparkle
	return

Route110_TrickHouseEntrance_EventScript_DoHidingSpotSparkle2:: @ 826A439
	setvar VAR_0x8004, 11  @ x
	setvar VAR_0x8005, 5   @ y
	call Route110_TrickHouseEntrance_EventScript_DoHidingSpotSparkle
	return

Route110_TrickHouseEntrance_EventScript_DoHidingSpotSparkle3:: @ 826A449
	setvar VAR_0x8004, 9  @ x
	setvar VAR_0x8005, 2  @ y
	call Route110_TrickHouseEntrance_EventScript_DoHidingSpotSparkle
	return

Route110_TrickHouseEntrance_EventScript_DoHidingSpotSparkle:: @ 826A459
	setvar VAR_0x8006, 0
	dofieldeffectsparkle VAR_0x8004, VAR_0x8005, VAR_0x8006
	waitfieldeffect FLDEFF_SPARKLE
	delay 10
	return

Route110_TrickHouseEntrance_Text_YoureBeingWatched: @ 826A474
	.string "누군가의 시선이 느껴진다...$"
	@ だれかの しせんを かんじる…

Route110_TrickHouseEntrance_Text_ConcealedBeneathDesk: @ 826A48A
	.string "으 으음...!\p"
	.string "어떻게 이 몸이 책상 밑에\n"
	.string "숨어 있다는 걸 알았지? ...대단한데!$"
	@ む むむ…!ｐ
	@ なぜ わがはいが つくえの したにｎ
	@ かくれていると わかった? ……できる!

Route110_TrickHouseEntrance_Text_ConcealedBehindTree: @ 826A4DA
	.string "으 으음...!\p"
	.string "어떻게 이 몸이 나무 밑에\n"
	.string "숨어 있다는 걸 알았지? ...대단한데!$"
	@ む むむ…!ｐ
	@ なぜ わがはいが きの うしろにｎ
	@ かくれていると わかった? ……できる!

Route110_TrickHouseEntrance_Text_ConcealedInDresser: @ 826A529
	.string "으 으음...!\p"
	.string "어떻게 이 몸이 옷장 안에\n"
	.string "숨어 있다는 걸 알았지? ...대단한데!$"
	@ む むむ…!ｐ
	@ なぜ わがはいが タンスの なかにｎ
	@ かくれていると わかった? ……できる!

Route110_TrickHouseEntrance_Text_ConealedBeyondWindow: @ 826A577
	.string "으 으음...!\p"
	.string "어떻게 이 몸이 창문 건너편에\n"
	.string "숨어 있다는 걸 알았지? ...대단한데!$"
	@ む むむ…!ｐ
	@ なぜ わがはいが まどの むこうにｎ
	@ かくれていると わかった? ……できる!

Route110_TrickHouseEntrance_Text_ConcealedInPlanter: @ 826A5C8
	.string "으 으음...!\p"
	.string "어떻게 이 몸이 화분 안에\n"
	.string "숨어 있다는 걸 알았지? ...대단한데!$"
	@ む むむ…!ｐ
	@ なぜ わがはいが うえきばちの なかにｎ
	@ かくれていると わかった? ……できる!

Route110_TrickHouseEntrance_Text_ConcealedInCupboard: @ 826A616
	.string "으 으음...!\p"
	.string "어떻게 이 몸이 찬장 안에\n"
	.string "숨어 있다는 걸 알았지? ...대단한데!$"
	@ む むむ…!ｐ
	@ なぜ わがはいが とだなの なかにｎ
	@ かくれていると わかった? ……できる!

Route110_TrickHouseEntrance_Text_ConcealedBehindWindow: @ 826A665
	.string "으 으음...!\p"
	.string "어떻게 이 몸이 창문 건너편에\n"
	.string "숨어 있다는 걸 알았지? ...대단한데!$"
	@ む むむ…!ｐ
	@ なぜ わがはいが まどの うらにｎ
	@ かくれていると わかった? ……できる!

Route110_TrickHouseEntrance_Text_ConcealedBeneathCushion: @ 826A6B6
	.string "으 으음...!\p"
	.string "어떻게 이 몸이 방석 밑에\n"
	.string "숨어 있다는 걸 알았지? ...대단한데!$"
	@ む むむ…!ｐ
	@ なぜ わがはいが ざぶとんの したにｎ
	@ かくれていると わかった? ……できる!

Route110_TrickHouseEntrance_Text_TheyCallMeTrickMaster: @ 826A709
	.string "이 몸이 바로\p"
	.string "호연지방 최대의\n"
	.string "수수께끼 인물!\l"
	.string "그 이름도 유명한...\p"
	.string "미궁대왕이닷!\n"
	.string "와하하하! 잘 부탁한다!$"
	@ わがはい こそ!ｐ
	@ ホウエンちほう さいだいのｎ
	@ なぞの じんぶつｌ
	@ ひと よんで……ｐ
	@ カラクリだいおう!ｎ
	@ わははは! はじめまして!

Route110_TrickHouseEntrance_Text_ComeToChallengeTrickHouse: @ 826A78C
	.string "자네 이 몸의 미궁의 대저택에\n"
	.string "도전하러 온 것이로군\l"
	.string "그렇지 내 말이 맞지!\l"
	.string "좋아 도전을 받아주마!\p"
	.string "저기 있는 족자로 들어가서\n"
	.string "도전하도록!\l"
	.string "이 몸은 안쪽 방에서 기다리겠다!$"
	@ あんた わがはいの カラクリやしきにｎ
	@ ちょうせんしに きたってｌ
	@ わけだろう そうだろう!ｌ
	@ よしっ ちょうせんを みとめよう!ｐ
	@ そこの かけじくから はいってｎ
	@ ちょうせん するがいい!ｌ
	@ わがはいは おくの へやで まってるぞ!

Route110_TrickHouseEntrance_Text_ItsAScroll: @ 826A878
	.string "족자다!$"
	@ かけじくだ!

Route110_TrickHouseEntrance_Text_GoInHoleBehindScroll: @ 826A887
	.string "족자 뒤를 들여다보니\n"
	.string "커다란 구멍이 있다!\p"
	.string "안으로 들어가 보겠습니까?$"
	@ かけじくの うらを のぞくとｎ
	@ おおきい あなが あった!ｐ
	@ おくに すすんで みますか?

Route110_TrickHouseEntrance_Text_LeavingOnJourneyNote: @ 826A8BD
	.string "족자 위에는 메모가 붙어 있다\p"
	.string "“여행을 떠납니다... 찾지 말아 주세요\n"
	.string "미궁대왕”$"
	@ かけじくの うえに メモが はってあるｐ
	@ 「たびに でます…… さがさないでねｎ
	@ カラクリだいおう」

Route110_TrickHouseEntrance_Text_NextTimeUseThisTrick: @ 826A921
	.string "자 그럼 이번 장치에는\n"
	.string "이런 거나 저런 걸...\p"
	.string "우후후 내가 생각해 봐도\n"
	.string "어려운걸... 우후후$"
	@ さて こんどの しかけはｎ
	@ あんなことや こんなことを……ｐ
	@ うふふ われながらｎ
	@ むずかしいぞ… むふふ

Route110_TrickHouseEntrance_Text_InMidstOfDevisingNewChallenges: @ 826A9AF
	.string "우왓 뭐야! 자넨가!\p"
	.string "지금은 아직 다음에 쓸 장치를\n"
	.string "생각 중이라고!\p"
	.string "좀 더 이 몸에게\n"
	.string "생각할 시간을\l"
	.string "줘도 괜찮잖아!\l"
	.string "좀 있다가 다시 와줘!$"
	@ わっ なんだ! あんたか!ｐ
	@ いま まだ つぎの しかけをｎ
	@ かんがえちゅう なんだよ!ｐ
	@ もっと わがはいにｎ
	@ かんがえる じかんをｌ
	@ あたえて くれたって いいだろ!ｌ
	@ もうちょっと したら また きてくれ!

Route110_TrickHouseEntrance_Text_YoureHereToAcceptReward: @ 826AA82
	.string "오오 자넨가! 어디 보자 지난번의\n"
	.string "선물을 가지러 온 것이로군!\l"
	.string "좋아 지금 주마!$"
	@ おお あんた! さては このあいだのｎ
	@ ほうびを とりに きたんだろう そうだろう!ｌ
	@ よしっ いま やろう!

Route110_TrickHouseEntrance_Text_DidYouNotComeToClaimReward: @ 826AB00
	.string "어라? 선물을 가지러 온 게 아니었어?$"
	@ あれ? とりに きたんじゃ ないのか?

Route110_TrickHouseEntrance_Text_MechadollWhichTent: @ 826AB2C
	.string "이 몸은 꼭두각시인형 5호!\n"
	.string "선물을 받지 않으면\l"
	.string "대왕의 뒤를 따라갈 수 없다고!\p"
	.string "“빨강텐트”와 “파랑텐트”\n"
	.string "둘 중에 어느 걸 가지고 싶어?$"
	@ ワガハイ ハ からくりニンギョウ 5ゴウ!ｎ
	@ ぷれぜんとヲ ウケトッテ クレナイトｌ
	@ ダイオウノ アトヲ オッテ イケナイヨ!ｐ
	@ 「アカイてんと」ト「アオイてんと」ｎ
	@ フタツノ ウチ ドチラガ ホシイ?

Route110_TrickHouseEntrance_Text_ThenFarewell: @ 826ABAE
	.string "그럼 안녕!$"
	@ ソレデハ さらば!

Route110_TrickHouseEntrance_Text_PCFullAgain: @ 826ABBD
	.string "엑! 또 PC가\n"
	.string "가득 찼다고...? 너무해!$"
	@ エッ! マタ ぱそこんガｎ
	@ イッパイ ダッテ……? アンマリダ!

Route110_TrickHousePuzzle_Text_FoundAScroll: @ 826ABE8
	.string "{PLAYER}{K_EUNNEUN} 두루마리를 발견했다!$"
	@ §あは まきものを みつけた!

Route110_TrickHousePuzzle_Text_MemorizedSecretCode: @ 826ABFB
	.string "{PLAYER}{K_EUNNEUN} 두루마리에 적혀 있는\n"
	.string "암호를 기억했다!$"
	@ §あは まきものに かいてあるｎ
	@ あいことばを おぼえた!

Route110_TrickHousePuzzle_Text_SecretCodeWrittenOnIt: @ 826AC2F
	.string "암호가 적혀 있다$"
	@ あいことばが かいてある

Route110_TrickHouseEntrance_Text_DoorLockedWriteSecretCodeHere: @ 826AC4F
	.string "문이 잠겨 있다!\p"
	.string "...잘 보니 문에 문자가 적혀 있다\n"
	.string "“여기에 암호를 적어라”$"
	@ とびらには カギが かかっている!ｐ
	@ ……よくみると とびらに もじが かいてあるｎ
	@ 「ここに あいことばを かきつけよ」
