.set LOCALID_MECHADOLL_1, 1
.set LOCALID_MECHADOLL_2, 2
.set LOCALID_MECHADOLL_3, 3
.set LOCALID_MECHADOLL_4, 4
.set LOCALID_MECHADOLL_5, 5

Route110_TrickHousePuzzle5_MapScripts:: @ 826CAF0
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHousePuzzle5_OnTransition
	.byte 0

Route110_TrickHousePuzzle5_OnTransition: @ 826CAF6
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_4, 0
	setvar VAR_TEMP_5, 0
	setvar VAR_TEMP_8, 0
	end

Route110_TrickHousePuzzle5_EventScript_Scroll:: @ 826CB15
	lockall
	compare VAR_TRICK_HOUSE_PUZZLE_5_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle5_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle5_EventScript_FoundScroll:: @ 826CB27
	setvar VAR_TRICK_HOUSE_PUZZLE_5_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll1:: @ 826CB32
	lockall
	applymovement LOCALID_MECHADOLL_1, Common_Movement_FacePlayer
	waitmovement 0
	compare VAR_TEMP_1, 1
	goto_if_eq Route110_TrickHousePuzzle5_EventScript_CorrectGoThrough
	setvar VAR_TEMP_9, 0
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll1Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll2:: @ 826CB53
	lockall
	applymovement LOCALID_MECHADOLL_2, Common_Movement_FacePlayer
	waitmovement 0
	compare VAR_TEMP_2, 1
	goto_if_eq Route110_TrickHousePuzzle5_EventScript_CorrectGoThrough
	setvar VAR_TEMP_9, 0
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll2Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll3:: @ 826CB74
	lockall
	applymovement LOCALID_MECHADOLL_3, Common_Movement_FacePlayer
	waitmovement 0
	compare VAR_TEMP_3, 1
	goto_if_eq Route110_TrickHousePuzzle5_EventScript_CorrectGoThrough
	setvar VAR_TEMP_9, 0
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll3Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll4:: @ 826CB95
	lockall
	applymovement LOCALID_MECHADOLL_4, Common_Movement_FacePlayer
	waitmovement 0
	compare VAR_TEMP_4, 1
	goto_if_eq Route110_TrickHousePuzzle5_EventScript_CorrectGoThrough
	setvar VAR_TEMP_9, 0
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll4Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll5:: @ 826CBB6
	lockall
	applymovement LOCALID_MECHADOLL_5, Common_Movement_FacePlayer
	waitmovement 0
	compare VAR_TEMP_5, 1
	goto_if_eq Route110_TrickHousePuzzle5_EventScript_CorrectGoThrough
	setvar VAR_TEMP_9, 0
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll5Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll1Trigger0:: @ 826CBD7
	lockall
	setvar VAR_TEMP_9, 0
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll1Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll1Trigger1:: @ 826CBE3
	lockall
	setvar VAR_TEMP_9, 1
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll1Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll1Trigger2:: @ 826CBEF
	lockall
	setvar VAR_TEMP_9, 2
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll1Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll1Trigger3:: @ 826CBFB
	lockall
	setvar VAR_TEMP_9, 3
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll1Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll1Trigger4:: @ 826CC07
	lockall
	setvar VAR_TEMP_9, 4
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll1Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll2Trigger0:: @ 826CC13
	lockall
	setvar VAR_TEMP_9, 0
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll2Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll2Trigger1:: @ 826CC1F
	lockall
	setvar VAR_TEMP_9, 1
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll2Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll2Trigger2:: @ 826CC2B
	lockall
	setvar VAR_TEMP_9, 2
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll2Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll2Trigger3:: @ 826CC37
	lockall
	setvar VAR_TEMP_9, 3
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll2Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll2Trigger4:: @ 826CC43
	lockall
	setvar VAR_TEMP_9, 4
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll2Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll2Trigger5:: @ 826CC4F
	lockall
	setvar VAR_TEMP_9, 5
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll2Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll3Trigger0:: @ 826CC5B
	lockall
	setvar VAR_TEMP_9, 0
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll3Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll3Trigger1:: @ 826CC67
	lockall
	setvar VAR_TEMP_9, 1
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll3Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll3Trigger2:: @ 826CC73
	lockall
	setvar VAR_TEMP_9, 2
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll3Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll3Trigger3:: @ 826CC7F
	lockall
	setvar VAR_TEMP_9, 3
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll3Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll3Trigger4:: @ 826CC8B
	lockall
	setvar VAR_TEMP_9, 4
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll3Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll4Trigger0:: @ 826CC97
	lockall
	setvar VAR_TEMP_9, 0
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll4Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll4Trigger1:: @ 826CCA3
	lockall
	setvar VAR_TEMP_9, 1
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll4Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll4Trigger2:: @ 826CCAF
	lockall
	setvar VAR_TEMP_9, 2
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll4Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll4Trigger3:: @ 826CCBB
	lockall
	setvar VAR_TEMP_9, 3
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll4Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll4Trigger4:: @ 826CCC7
	lockall
	setvar VAR_TEMP_9, 4
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll4Activate
	end

@ Unused
Route110_TrickHousePuzzle5_EventScript_Mechadoll4Trigger5:: @ 826CCD3
	lockall
	setvar VAR_TEMP_9, 5
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll4Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll5Trigger0:: @ 826CCDF
	lockall
	setvar VAR_TEMP_9, 0
	goto Route110_TrickHousePuzzle5_EventScript_Mechadoll5Activate
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll1Activate:: @ 826CCEB
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_8, LOCALID_MECHADOLL_1
	playse SE_PIN
	applymovement LOCALID_MECHADOLL_1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MECHADOLL_1, Common_Movement_Delay48
	waitmovement 0
	compare VAR_TEMP_9, 1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft1
	compare VAR_TEMP_9, 2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft2
	compare VAR_TEMP_9, 3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft3
	compare VAR_TEMP_9, 4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft4
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll1Intro, MSGBOX_DEFAULT
	random 3
	switch VAR_RESULT
	case 0, Route110_TrickHousePuzzle5_EventScript_Mechadoll1Quiz1
	case 1, Route110_TrickHousePuzzle5_EventScript_Mechadoll1Quiz2
	case 2, Route110_TrickHousePuzzle5_EventScript_Mechadoll1Quiz3
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll2Activate:: @ 826CD6A
	setvar VAR_TEMP_2, 1
	setvar VAR_TEMP_8, LOCALID_MECHADOLL_2
	playse SE_PIN
	applymovement LOCALID_MECHADOLL_2, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MECHADOLL_2, Common_Movement_Delay48
	waitmovement 0
	compare VAR_TEMP_9, 1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkRight1
	compare VAR_TEMP_9, 2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkRight2
	compare VAR_TEMP_9, 3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkRight3
	compare VAR_TEMP_9, 4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkRight4
	compare VAR_TEMP_9, 5
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkRight5
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll2Intro, MSGBOX_DEFAULT
	random 3
	switch VAR_RESULT
	case 0, Route110_TrickHousePuzzle5_EventScript_Mechadoll2Quiz1
	case 1, Route110_TrickHousePuzzle5_EventScript_Mechadoll2Quiz2
	case 2, Route110_TrickHousePuzzle5_EventScript_Mechadoll2Quiz3
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll3Activate:: @ 826CDF4
	setvar VAR_TEMP_3, 1
	setvar VAR_TEMP_8, LOCALID_MECHADOLL_3
	playse SE_PIN
	applymovement LOCALID_MECHADOLL_3, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MECHADOLL_3, Common_Movement_Delay48
	waitmovement 0
	compare VAR_TEMP_9, 1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft1
	compare VAR_TEMP_9, 2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft2
	compare VAR_TEMP_9, 3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft3
	compare VAR_TEMP_9, 4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft4
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll3Intro, MSGBOX_DEFAULT
	random 3
	switch VAR_RESULT
	case 0, Route110_TrickHousePuzzle5_EventScript_Mechadoll3Quiz1
	case 1, Route110_TrickHousePuzzle5_EventScript_Mechadoll3Quiz2
	case 2, Route110_TrickHousePuzzle5_EventScript_Mechadoll3Quiz3
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll4Activate:: @ 826CE73
	setvar VAR_TEMP_4, 1
	setvar VAR_TEMP_8, LOCALID_MECHADOLL_4
	playse SE_PIN
	applymovement LOCALID_MECHADOLL_4, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MECHADOLL_4, Common_Movement_Delay48
	waitmovement 0
	compare VAR_TEMP_9, 1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft1
	compare VAR_TEMP_9, 2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft2
	compare VAR_TEMP_9, 3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft3
	compare VAR_TEMP_9, 4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft4
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll4Intro, MSGBOX_DEFAULT
	random 3
	switch VAR_RESULT
	case 0, Route110_TrickHousePuzzle5_EventScript_Mechadoll4Quiz1
	case 1, Route110_TrickHousePuzzle5_EventScript_Mechadoll4Quiz2
	case 2, Route110_TrickHousePuzzle5_EventScript_Mechadoll4Quiz3
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll5Activate:: @ 826CEF2
	setvar VAR_TEMP_5, 1
	setvar VAR_TEMP_8, LOCALID_MECHADOLL_5
	playse SE_PIN
	applymovement LOCALID_MECHADOLL_5, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MECHADOLL_5, Common_Movement_Delay48
	waitmovement 0
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll5Intro, MSGBOX_DEFAULT
	random 3
	switch VAR_RESULT
	case 0, Route110_TrickHousePuzzle5_EventScript_Mechadoll5Quiz1
	case 1, Route110_TrickHousePuzzle5_EventScript_Mechadoll5Quiz2
	case 2, Route110_TrickHousePuzzle5_EventScript_Mechadoll5Quiz3
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll1Quiz1:: @ 826CF45
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll1Quiz1, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL1_Q1, 1
	switch VAR_RESULT
	case 2, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll1Quiz2:: @ 826CF68
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll1Quiz2, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL1_Q2, 1
	switch VAR_RESULT
	case 0, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll1Quiz3:: @ 826CF8B
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll1Quiz3, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL1_Q3, 1
	switch VAR_RESULT
	case 0, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll2Quiz1:: @ 826CFAE
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll2Quiz1, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL2_Q1, 1
	switch VAR_RESULT
	case 1, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll2Quiz2:: @ 826CFD1
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll2Quiz2, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL2_Q2, 1
	switch VAR_RESULT
	case 2, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll2Quiz3:: @ 826CFF4
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll2Quiz3, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL2_Q3, 1
	switch VAR_RESULT
	case 0, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll3Quiz1:: @ 826D017
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll3Quiz1, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL3_Q1, 1
	switch VAR_RESULT
	case 0, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll3Quiz2:: @ 826D03A
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll3Quiz2, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL3_Q2, 1
	switch VAR_RESULT
	case 2, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll3Quiz3:: @ 826D05D
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll3Quiz3, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL3_Q3, 1
	switch VAR_RESULT
	case 1, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll4Quiz1:: @ 826D080
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll4Quiz1, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL4_Q1, 1
	switch VAR_RESULT
	case 0, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll4Quiz2:: @ 826D0A3
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll4Quiz2, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL4_Q2, 1
	switch VAR_RESULT
	case 0, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll4Quiz3:: @ 826D0C6
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll4Quiz3, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL4_Q3, 1
	switch VAR_RESULT
	case 1, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll5Quiz1:: @ 826D0E9
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll5Quiz1, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL5_Q1, 1
	switch VAR_RESULT
	case 1, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll5Quiz2:: @ 826D10C
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll5Quiz2, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL5_Q2, 1
	switch VAR_RESULT
	case 0, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_Mechadoll5Quiz3:: @ 826D12F
	msgbox Route110_TrickHousePuzzle5_Text_Mechadoll5Quiz3, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MECHADOLL5_Q3, 1
	switch VAR_RESULT
	case 2, Route110_TrickHousePuzzle5_EventScript_CorrectAnswer
	goto Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer
	end

Route110_TrickHousePuzzle5_EventScript_IncorrectAnswer:: @ 826D152
	waitse
	playse SE_FAILURE
	msgbox Route110_TrickHousePuzzle5_Text_DisappointmentError, MSGBOX_DEFAULT
	applymovement LOCALID_MECHADOLL_1, Route110_TrickHousePuzzle5_Movement_MechadollShake
	applymovement LOCALID_MECHADOLL_2, Route110_TrickHousePuzzle5_Movement_MechadollShake
	applymovement LOCALID_MECHADOLL_3, Route110_TrickHousePuzzle5_Movement_MechadollShake
	applymovement LOCALID_MECHADOLL_4, Route110_TrickHousePuzzle5_Movement_MechadollShake
	applymovement LOCALID_MECHADOLL_5, Route110_TrickHousePuzzle5_Movement_MechadollShake
	msgbox Route110_TrickHousePuzzle5_Text_Wahahahaha, MSGBOX_DEFAULT
	waitmovement 0
	msgbox Route110_TrickHousePuzzle5_Text_WaitForNextChallenge, MSGBOX_DEFAULT
	closemessage
	warp MAP_ROUTE110_TRICK_HOUSE_PUZZLE5, 255, 0, 21
	waitstate
	releaseall
	end

Route110_TrickHousePuzzle5_EventScript_CorrectAnswer:: @ 826D1A0
	waitse
	playse SE_SUCCESS
	goto Route110_TrickHousePuzzle5_EventScript_CorrectGoThrough
	end

Route110_TrickHousePuzzle5_EventScript_CorrectGoThrough:: @ 826D1AA
	msgbox Route110_TrickHousePuzzle5_Text_CorrectGoThrough, MSGBOX_DEFAULT
	releaseall
	end

@ Absurd redundancy in movement scripts that could be resolved by using VAR_TEMP_8 for applymovement instead
@ Many of the below movement scripts arent even used, see below
@   Mechadoll 2 is the only mechadoll to walk right, all the other WalkRight scripts are unused
@   Mechadoll 5 never walks, all the Mechadoll5Walk scripts are unused
@   No mechadoll walks left 5 paces, all the WalkLeft5 scripts are unused
Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft1:: @ 826D1B4
	compare VAR_TEMP_8, LOCALID_MECHADOLL_1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkLeft1
	compare VAR_TEMP_8, LOCALID_MECHADOLL_2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkLeft1
	compare VAR_TEMP_8, LOCALID_MECHADOLL_3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkLeft1
	compare VAR_TEMP_8, LOCALID_MECHADOLL_4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkLeft1
	compare VAR_TEMP_8, LOCALID_MECHADOLL_5
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkLeft1
	return

Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft2:: @ 826D1EC
	compare VAR_TEMP_8, LOCALID_MECHADOLL_1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkLeft2
	compare VAR_TEMP_8, LOCALID_MECHADOLL_2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkLeft2
	compare VAR_TEMP_8, LOCALID_MECHADOLL_3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkLeft2
	compare VAR_TEMP_8, LOCALID_MECHADOLL_4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkLeft2
	compare VAR_TEMP_8, LOCALID_MECHADOLL_5
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkLeft2
	return

Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft3:: @ 826D224
	compare VAR_TEMP_8, LOCALID_MECHADOLL_1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkLeft3
	compare VAR_TEMP_8, LOCALID_MECHADOLL_2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkLeft3
	compare VAR_TEMP_8, LOCALID_MECHADOLL_3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkLeft3
	compare VAR_TEMP_8, LOCALID_MECHADOLL_4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkLeft3
	compare VAR_TEMP_8, LOCALID_MECHADOLL_5
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkLeft3
	return

Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft4:: @ 826D25C
	compare VAR_TEMP_8, LOCALID_MECHADOLL_1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkLeft4
	compare VAR_TEMP_8, LOCALID_MECHADOLL_2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkLeft4
	compare VAR_TEMP_8, LOCALID_MECHADOLL_3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkLeft4
	compare VAR_TEMP_8, LOCALID_MECHADOLL_4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkLeft4
	compare VAR_TEMP_8, LOCALID_MECHADOLL_5
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkLeft4
	return

Route110_TrickHousePuzzle5_EventScript_MechadollWalkLeft5:: @ 826D294
	compare VAR_TEMP_8, LOCALID_MECHADOLL_1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkLeft5
	compare VAR_TEMP_8, LOCALID_MECHADOLL_2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkLeft5
	compare VAR_TEMP_8, LOCALID_MECHADOLL_3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkLeft5
	compare VAR_TEMP_8, LOCALID_MECHADOLL_4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkLeft5
	compare VAR_TEMP_8, LOCALID_MECHADOLL_5
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkLeft5
	return

Route110_TrickHousePuzzle5_EventScript_MechadollWalkRight1:: @ 826D2CC
	compare VAR_TEMP_8, LOCALID_MECHADOLL_1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkRight1
	compare VAR_TEMP_8, LOCALID_MECHADOLL_2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkRight1
	compare VAR_TEMP_8, LOCALID_MECHADOLL_3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkRight1
	compare VAR_TEMP_8, LOCALID_MECHADOLL_4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkRight1
	compare VAR_TEMP_8, LOCALID_MECHADOLL_5
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkRight1
	return

Route110_TrickHousePuzzle5_EventScript_MechadollWalkRight2:: @ 826D304
	compare VAR_TEMP_8, LOCALID_MECHADOLL_1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkRight2
	compare VAR_TEMP_8, LOCALID_MECHADOLL_2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkRight2
	compare VAR_TEMP_8, LOCALID_MECHADOLL_3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkRight2
	compare VAR_TEMP_8, LOCALID_MECHADOLL_4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkRight2
	compare VAR_TEMP_8, LOCALID_MECHADOLL_5
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkRight2
	return

Route110_TrickHousePuzzle5_EventScript_MechadollWalkRight3:: @ 826D33C
	compare VAR_TEMP_8, LOCALID_MECHADOLL_1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkRight3
	compare VAR_TEMP_8, LOCALID_MECHADOLL_2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkRight3
	compare VAR_TEMP_8, LOCALID_MECHADOLL_3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkRight3
	compare VAR_TEMP_8, LOCALID_MECHADOLL_4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkRight3
	compare VAR_TEMP_8, LOCALID_MECHADOLL_5
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkRight3
	return

Route110_TrickHousePuzzle5_EventScript_MechadollWalkRight4:: @ 826D374
	compare VAR_TEMP_8, LOCALID_MECHADOLL_1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkRight4
	compare VAR_TEMP_8, LOCALID_MECHADOLL_2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkRight4
	compare VAR_TEMP_8, LOCALID_MECHADOLL_3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkRight4
	compare VAR_TEMP_8, LOCALID_MECHADOLL_4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkRight4
	compare VAR_TEMP_8, LOCALID_MECHADOLL_5
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkRight4
	return

Route110_TrickHousePuzzle5_EventScript_MechadollWalkRight5:: @ 826D3AC
	compare VAR_TEMP_8, LOCALID_MECHADOLL_1
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkRight5
	compare VAR_TEMP_8, LOCALID_MECHADOLL_2
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkRight5
	compare VAR_TEMP_8, LOCALID_MECHADOLL_3
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkRight5
	compare VAR_TEMP_8, LOCALID_MECHADOLL_4
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkRight5
	compare VAR_TEMP_8, LOCALID_MECHADOLL_5
	call_if_eq Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkRight5
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkLeft1:: @ 826D3E4
	applymovement LOCALID_MECHADOLL_1, Route110_TrickHousePuzzle5_Movement_WalkLeft1
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkLeft1:: @ 826D3EF
	applymovement LOCALID_MECHADOLL_2, Route110_TrickHousePuzzle5_Movement_WalkLeft1
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkLeft1:: @ 826D3FA
	applymovement LOCALID_MECHADOLL_3, Route110_TrickHousePuzzle5_Movement_WalkLeft1
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkLeft1:: @ 826D405
	applymovement LOCALID_MECHADOLL_4, Route110_TrickHousePuzzle5_Movement_WalkLeft1
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkLeft1:: @ 826D410
	applymovement LOCALID_MECHADOLL_5, Route110_TrickHousePuzzle5_Movement_WalkLeft1
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkLeft2:: @ 826D41B
	applymovement LOCALID_MECHADOLL_1, Route110_TrickHousePuzzle5_Movement_WalkLeft2
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkLeft2:: @ 826D426
	applymovement LOCALID_MECHADOLL_2, Route110_TrickHousePuzzle5_Movement_WalkLeft2
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkLeft2:: @ 826D431
	applymovement LOCALID_MECHADOLL_3, Route110_TrickHousePuzzle5_Movement_WalkLeft2
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkLeft2:: @ 826D43C
	applymovement LOCALID_MECHADOLL_4, Route110_TrickHousePuzzle5_Movement_WalkLeft2
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkLeft2:: @ 826D447
	applymovement LOCALID_MECHADOLL_5, Route110_TrickHousePuzzle5_Movement_WalkLeft2
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkLeft3:: @ 826D452
	applymovement LOCALID_MECHADOLL_1, Route110_TrickHousePuzzle5_Movement_WalkLeft3
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkLeft3:: @ 826D45D
	applymovement LOCALID_MECHADOLL_2, Route110_TrickHousePuzzle5_Movement_WalkLeft3
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkLeft3:: @ 826D468
	applymovement LOCALID_MECHADOLL_3, Route110_TrickHousePuzzle5_Movement_WalkLeft3
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkLeft3:: @ 826D473
	applymovement LOCALID_MECHADOLL_4, Route110_TrickHousePuzzle5_Movement_WalkLeft3
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkLeft3:: @ 826D47E
	applymovement LOCALID_MECHADOLL_5, Route110_TrickHousePuzzle5_Movement_WalkLeft3
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkLeft4:: @ 826D489
	applymovement LOCALID_MECHADOLL_1, Route110_TrickHousePuzzle5_Movement_WalkLeft4
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkLeft4:: @ 826D494
	applymovement LOCALID_MECHADOLL_2, Route110_TrickHousePuzzle5_Movement_WalkLeft4
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkLeft4:: @ 826D49F
	applymovement LOCALID_MECHADOLL_3, Route110_TrickHousePuzzle5_Movement_WalkLeft4
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkLeft4:: @ 826D4AA
	applymovement LOCALID_MECHADOLL_4, Route110_TrickHousePuzzle5_Movement_WalkLeft4
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkLeft4:: @ 826D4B5
	applymovement LOCALID_MECHADOLL_5, Route110_TrickHousePuzzle5_Movement_WalkLeft4
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkLeft5:: @ 826D4C0
	applymovement LOCALID_MECHADOLL_1, Route110_TrickHousePuzzle5_Movement_WalkLeft5
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkLeft5:: @ 826D4CB
	applymovement LOCALID_MECHADOLL_2, Route110_TrickHousePuzzle5_Movement_WalkLeft5
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkLeft5:: @ 826D4D6
	applymovement LOCALID_MECHADOLL_3, Route110_TrickHousePuzzle5_Movement_WalkLeft5
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkLeft5:: @ 826D4E1
	applymovement LOCALID_MECHADOLL_4, Route110_TrickHousePuzzle5_Movement_WalkLeft5
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkLeft5:: @ 826D4EC
	applymovement LOCALID_MECHADOLL_5, Route110_TrickHousePuzzle5_Movement_WalkLeft5
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkRight1:: @ 826D4F7
	applymovement LOCALID_MECHADOLL_1, Route110_TrickHousePuzzle5_Movement_WalkRight1
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkRight1:: @ 826D502
	applymovement LOCALID_MECHADOLL_2, Route110_TrickHousePuzzle5_Movement_WalkRight1
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkRight1:: @ 826D50D
	applymovement LOCALID_MECHADOLL_3, Route110_TrickHousePuzzle5_Movement_WalkRight1
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkRight1:: @ 826D518
	applymovement LOCALID_MECHADOLL_4, Route110_TrickHousePuzzle5_Movement_WalkRight1
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkRight1:: @ 826D523
	applymovement LOCALID_MECHADOLL_5, Route110_TrickHousePuzzle5_Movement_WalkRight1
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkRight2:: @ 826D52E
	applymovement LOCALID_MECHADOLL_1, Route110_TrickHousePuzzle5_Movement_WalkRight2
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkRight2:: @ 826D539
	applymovement LOCALID_MECHADOLL_2, Route110_TrickHousePuzzle5_Movement_WalkRight2
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkRight2:: @ 826D544
	applymovement LOCALID_MECHADOLL_3, Route110_TrickHousePuzzle5_Movement_WalkRight2
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkRight2:: @ 826D54F
	applymovement LOCALID_MECHADOLL_4, Route110_TrickHousePuzzle5_Movement_WalkRight2
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkRight2:: @ 826D55A
	applymovement LOCALID_MECHADOLL_5, Route110_TrickHousePuzzle5_Movement_WalkRight2
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkRight3:: @ 826D565
	applymovement LOCALID_MECHADOLL_1, Route110_TrickHousePuzzle5_Movement_WalkRight3
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkRight3:: @ 826D570
	applymovement LOCALID_MECHADOLL_2, Route110_TrickHousePuzzle5_Movement_WalkRight3
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkRight3:: @ 826D57B
	applymovement LOCALID_MECHADOLL_3, Route110_TrickHousePuzzle5_Movement_WalkRight3
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkRight3:: @ 826D586
	applymovement LOCALID_MECHADOLL_4, Route110_TrickHousePuzzle5_Movement_WalkRight3
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkRight3:: @ 826D591
	applymovement LOCALID_MECHADOLL_5, Route110_TrickHousePuzzle5_Movement_WalkRight3
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkRight4:: @ 826D59C
	applymovement LOCALID_MECHADOLL_1, Route110_TrickHousePuzzle5_Movement_WalkRight4
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkRight4:: @ 826D5A7
	applymovement LOCALID_MECHADOLL_2, Route110_TrickHousePuzzle5_Movement_WalkRight4
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkRight4:: @ 826D5B2
	applymovement LOCALID_MECHADOLL_3, Route110_TrickHousePuzzle5_Movement_WalkRight4
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkRight4:: @ 826D5BD
	applymovement LOCALID_MECHADOLL_4, Route110_TrickHousePuzzle5_Movement_WalkRight4
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkRight4:: @ 826D5C8
	applymovement LOCALID_MECHADOLL_5, Route110_TrickHousePuzzle5_Movement_WalkRight4
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll1WalkRight5:: @ 826D5D3
	applymovement LOCALID_MECHADOLL_1, Route110_TrickHousePuzzle5_Movement_WalkRight5
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll2WalkRight5:: @ 826D5DE
	applymovement LOCALID_MECHADOLL_2, Route110_TrickHousePuzzle5_Movement_WalkRight5
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll3WalkRight5:: @ 826D5E9
	applymovement LOCALID_MECHADOLL_3, Route110_TrickHousePuzzle5_Movement_WalkRight5
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll4WalkRight5:: @ 826D5F4
	applymovement LOCALID_MECHADOLL_4, Route110_TrickHousePuzzle5_Movement_WalkRight5
	waitmovement 0
	return

Route110_TrickHousePuzzle5_EventScript_Mechadoll5WalkRight5:: @ 826D5FF
	applymovement LOCALID_MECHADOLL_5, Route110_TrickHousePuzzle5_Movement_WalkRight5
	waitmovement 0
	return

Route110_TrickHousePuzzle5_Movement_WalkLeft1: @ 826D60A
	walk_left
	step_end

Route110_TrickHousePuzzle5_Movement_WalkLeft2: @ 826D60C
	walk_left
	walk_left
	step_end

Route110_TrickHousePuzzle5_Movement_WalkLeft3: @ 826D60F
	walk_left
	walk_left
	walk_left
	step_end

Route110_TrickHousePuzzle5_Movement_WalkLeft4: @ 826D613
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route110_TrickHousePuzzle5_Movement_WalkLeft5: @ 826D618
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route110_TrickHousePuzzle5_Movement_WalkRight1: @ 826D61E
	walk_right
	step_end

Route110_TrickHousePuzzle5_Movement_WalkRight2: @ 826D620
	walk_right
	walk_right
	step_end

Route110_TrickHousePuzzle5_Movement_WalkRight3: @ 826D623
	walk_right
	walk_right
	walk_right
	step_end

Route110_TrickHousePuzzle5_Movement_WalkRight4: @ 826D627
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route110_TrickHousePuzzle5_Movement_WalkRight5: @ 826D62C
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route110_TrickHousePuzzle5_Movement_MechadollShake: @ 826D632
	face_left
	delay_2
	face_right
	delay_2
	face_left
	delay_2
	face_right
	delay_2
	face_left
	delay_2
	face_right
	delay_2
	face_left
	delay_2
	face_right
	delay_2
	face_left
	delay_2
	face_right
	delay_2
	face_left
	delay_2
	face_right
	delay_2
	face_left
	delay_2
	face_right
	delay_2
	face_left
	delay_2
	face_right
	delay_2
	face_left
	delay_2
	face_right
	delay_2
	face_left
	delay_2
	face_right
	delay_2
	face_left
	delay_2
	face_right
	delay_2
	face_down
	step_end

Route110_TrickHousePuzzle5_Text_WroteSecretCodeLockOpened: @ 826D660
	.string "{PLAYER}{K_EUNNEUN} 암호를\n"
	.string "문에 적었다!\p"
	.string "“미궁대왕님 천재”\p"
	.string "...... ...... ......\p"
	.string "문의 자물쇠가 풀렸다!$"
	@ §あは あいことばをｎ
	@ とびらに かきつけた!ｐ
	@ 「カラクリだいおう さま てんさい」ｐ
	@ …… …… ……ｐ
	@ かぎの はずれる おとがした!

Route110_TrickHousePuzzle5_Text_Mechadoll1Intro: @ 826D6CE
	.string "달그락달그락...\n"
	.string "이 몸은 꼭두각시인형 1호!\p"
	.string "꼭두각시인형 5호가 있는 곳까지\n"
	.string "연속으로 퀴즈를 맞히면\l"
	.string "암호를 알 수 있을 거야!$"
	@ カタカタ…ｎ
	@ ワガハイ ハ からくりニンギョウ 1ゴウ!ｐ
	@ からくりニンギョウ 5ゴウノ トコロマデｎ
	@ ツヅケテ くいずニ セイカイ スレバｌ
	@ あいことばニ タドリツケルゾ!

Route110_TrickHousePuzzle5_Text_Mechadoll1Quiz1: @ 826D757
	.string "꼭두각시인형 1호 퀴즈!\p"
	.string "이 중에 110번 도로에\n"
	.string "없는 포켓몬은 뭘까?$"
	@ からくりニンギョウ 1ゴウ くいず!ｐ
	@ このなかで 110ばんどうろにｎ
	@ いない ポケモンは どれ?

Route110_TrickHousePuzzle5_Text_Mechadoll1Quiz2: @ 826D7AA
	.string "꼭두각시인형 1호 퀴즈!\p"
	.string "이 중에서 물타입이 아닌\n"
	.string "포켓몬은 뭘까?$"
	@ からくりニンギョウ 1ゴウ くいず!ｐ
	@ このなかで みずタイプが はいってないｎ
	@ ポケモンは どれ?

Route110_TrickHousePuzzle5_Text_Mechadoll1Quiz3: @ 826D7FC
	.string "꼭두각시인형 1호 퀴즈!\p"
	.string "이 중에서 흡혈을\n"
	.string "사용하지 못하는 포켓몬은 뭘까?$"
	@ からくりニンギョウ 1ゴウ くいず!ｐ
	@ このなかで きゅうけつをｎ
	@ つかえない ポケモンは どれ?

Route110_TrickHousePuzzle5_Text_CorrectGoThrough: @ 826D84D
	.string "축하해 정답이야-!\n"
	.string "자 그럼 안으로 가!$"
	@ オメデトウ セイカイ デ-ス!ｎ
	@ サキヘ ドウゾ!

Route110_TrickHousePuzzle5_Text_DisappointmentError: @ 826D883
	.string "땡!\n"
	.string "틀렸어---!$"
	@ ザンネン!ｎ
	@ マチガイ デ---ス!

Route110_TrickHousePuzzle5_Text_Wahahahaha: @ 826D8A1
	.string "와하하하하! 와하하하하! 달그락달그락!$"
	@ ワハハハハ! ワハハハハ! カタカタ!

Route110_TrickHousePuzzle5_Text_WaitForNextChallenge: @ 826D8C9
	.string "재도전을 기다릴게-!$"
	@ マタノ ちゃれんじ オマチシテマ-ス!

Route110_TrickHousePuzzle5_Text_Mechadoll2Intro: @ 826D8EA
	.string "달그락달그락...\n"
	.string "이 몸은 꼭두각시인형 2호!\l"
	.string "1호의 퀴즈는 너무 쉬워!$"
	@ カタカタ…ｎ
	@ ワガハイ ハ からくりニンギョウ 2ゴウ!ｌ
	@ 1ゴウノ くいずハ ヤサシスギルヨ!

Route110_TrickHousePuzzle5_Text_Mechadoll2Quiz1: @ 826D940
	.string "꼭두각시인형 2호 퀴즈!\p"
	.string "민진이 아빠한테서 빌린\n"
	.string "포켓몬은 뭐였을까?$"
	@ からくりニンギョウ 2ゴウ くいず!ｐ
	@ ミツルくんが パパから かしてもらったｎ
	@ ポケモンは なんだった?

Route110_TrickHousePuzzle5_Text_Mechadoll2Quiz2: @ 826D98C
	.string "꼭두각시인형 2호 퀴즈!\p"
	.string "털보박사를 뒤쫓고 있었던\n"
	.string "포켓몬은 뭐였을까?$"
	@ からくりニンギョウ 2ゴウ くいず!ｐ
	@ オダマキはかせを おいかけていたｎ
	@ ポケモンは なんだった?

Route110_TrickHousePuzzle5_Text_Mechadoll2Quiz3: @ 826D9CE
	.string "꼭두각시인형 2호 퀴즈!\p"
	.string "등화숲에서 아쿠아단이\n"
	.string "사용했던 포켓몬은 뭐였을까?$"
	@ からくりニンギョウ 2ゴウ くいず!ｐ
	@ トウカのもりで アクアだんがｎ
	@ たたかわせた ポケモンは なんだった?

Route110_TrickHousePuzzle5_Text_Mechadoll3Intro: @ 826DA1E
	.string "달그락달그락...\n"
	.string "이 몸은 꼭두각시인형 3호!\l"
	.string "돈에 대해서는 좀 까다롭지!$"
	@ カタカタ…ｎ
	@ ワガハイ ハ からくりニンギョウ 3ゴウ!ｌ
	@ オカネニハ ウルサイノダ!

Route110_TrickHousePuzzle5_Text_Mechadoll3Quiz1: @ 826DA64
	.string "꼭두각시인형 3호 퀴즈!\p"
	.string "항구메일 3개 사는 거랑\n"
	.string "화상치료제 1개 사는 거랑\l"
	.string "뭐가 더 비쌀까?$"
	@ からくりニンギョウ 3ゴウ くいず!ｐ
	@ ハ-バ-メ-ル 3つ かうのとｎ
	@ やけどなおし 1つ かうのとｌ
	@ どっちが たかい?

Route110_TrickHousePuzzle5_Text_Mechadoll3Quiz2: @ 826DAAD
	.string "꼭두각시인형 3호 퀴즈!\p"
	.string "수퍼볼을 팔아서\n"
	.string "상처약을 사면 얼마 남을까?$"
	@ からくりニンギョウ 3ゴウ くいず!ｐ
	@ ス-パ-ボ-ルを うってｎ
	@ キズぐすりを かうと いくら のこる?

Route110_TrickHousePuzzle5_Text_Mechadoll3Quiz3: @ 826DAFF
	.string "꼭두각시인형 3호 퀴즈!\p"
	.string "벌레회피스프레이랑 미네랄사이다를 사면\n"
	.string "좋은상처약보다 비싸질까?$"
	@ からくりニンギョウ 3ゴウ くいず!ｐ
	@ むしよけスプレ-と サイコソ-ダを かうとｎ
	@ いいキズぐすり より たかくなる?

Route110_TrickHousePuzzle5_Text_Mechadoll4Intro: @ 826DB4C
	.string "달그락달그락...\n"
	.string "난 꼭두각시인형 4호야!\l"
	.string "아름다운 나의 퀴즈를 한번 맞혀봐!$"
	@ カタカタ…ｎ
	@ からくりニンギョウ 4ゴウ ヨ-ン!ｌ
	@ ウツクシイ ワタシノ くいず イクワヨ!

Route110_TrickHousePuzzle5_Text_Mechadoll4Quiz1: @ 826DB94
	.string "꼭두각시인형 4호 퀴즈야!\p"
	.string "바다의 집에는 남성과 여성 중\n"
	.string "어느 쪽이 많을까?$"
	@ からくりニンギョウ 4ゴウ くいずヨ!ｐ
	@ うみのいえには だんせいと じょせいｎ
	@ どちらが おおい?

Route110_TrickHousePuzzle5_Text_Mechadoll4Quiz2: @ 826DBD7
	.string "꼭두각시인형 4호 퀴즈야!\p"
	.string "용암마을에는\n"
	.string "할아버지와 할머니 중 어느 쪽이 많을까?$"
	@ からくりニンギョウ 4ゴウ くいずヨ!ｐ
	@ フエンタウンに いるｎ
	@ おじいさんと おばあさん どっちがおおい?

Route110_TrickHousePuzzle5_Text_Mechadoll4Quiz3: @ 826DC2A
	.string "꼭두각시인형 4호 퀴즈야!\p"
	.string "포켓몬 트레이너스쿨에는\n"
	.string "여학생이 몇 명 있을까?$"
	@ からくりニンギョウ 4ゴウ くいずヨ!ｐ
	@ ポケモン トレ-ナ-ズ スク-ルにｎ
	@ おんなのこの せいとは なんにん いた?

Route110_TrickHousePuzzle5_Text_Mechadoll5Intro: @ 826DC78
	.string "달그락달그락...\n"
	.string "이 몸은 꼭두각시인형 5호!\l"
	.string "대왕의 최고 걸작!$"
	@ カタカタ…ｎ
	@ ワガハイ ハ からくりニンギョウ 5ゴウ!ｌ
	@ ダイオウノ サイコウ ケッサク!

Route110_TrickHousePuzzle5_Text_Mechadoll5Quiz1: @ 826DCCB
	.string "꼭두각시인형 5호 퀴즈!\p"
	.string "잿빛도시의 애호가클럽에\n"
	.string "있는 포켓몬은 몇 마리일까?$"
	@ からくりニンギョウ 5ゴウ くいず!ｐ
	@ カイナシティの だいすきクラブにｎ
	@ ポケモンは なんひき いた?

Route110_TrickHousePuzzle5_Text_Mechadoll5Quiz2: @ 826DD1B
	.string "꼭두각시인형 5호 퀴즈!\p"
	.string "검방울시티에 있는 트리하우스는\n"
	.string "모두 몇 채일까?$"
	@ からくりニンギョウ 5ゴウ くいず!ｐ
	@ ヒワマキシティに ある ツリ-ハウスｎ
	@ ぜんぶで いくつ?

Route110_TrickHousePuzzle5_Text_Mechadoll5Quiz3: @ 826DD5F
	.string "꼭두각시인형 5호 퀴즈!\p"
	.string "사이클링 로드 위쪽에 있는\n"
	.string "트라이애슬리트는 몇 명일까?$"
	@ からくりニンギョウ 5ゴウ くいず!ｐ
	@ サイクリングロ-ドの うえにｎ
	@ トライアスリ-トは なんにん いた?
