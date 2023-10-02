.set LOCALID_LASS, 1
.set LOCALID_MAN, 2
.set LOCALID_POKEFAN_M, 3
.set LOCALID_LITTLE_GIRL, 4
.set LOCALID_NINJA_BOY, 5
.set LOCALID_BOY, 6
.set LOCALID_WOMAN, 7
.set LOCALID_EXPERT_F, 8

LilycoveCity_PokemonTrainerFanClub_MapScripts:: @ 821C785
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LilycoveCity_PokemonTrainerFanClub_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_PokemonTrainerFanClub_OnTransition
	.byte 0

	@ See field_specials.c for a breakdown of the Fan Club and its variables

LilycoveCity_PokemonTrainerFanClub_OnFrame: @ 821C790
	map_script_2 VAR_LILYCOVE_FAN_CLUB_STATE, 1, LilycoveCity_PokemonTrainerFanClub_EventScript_MeetFirstFans
	.2byte 0

LilycoveCity_PokemonTrainerFanClub_EventScript_MeetFirstFans:: @ 821C79A
	lockall
	applymovement LOCALID_LASS, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_OhWowItsPlayer, MSGBOX_DEFAULT
	applymovement LOCALID_LITTLE_GIRL, LilycoveCity_PokemonTrainerFanClub_Movement_LittleGirlWatchPlayer
	applymovement LOCALID_MAN, LilycoveCity_PokemonTrainerFanClub_Movement_FanApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_HeardAboutYouImYourFan, MSGBOX_DEFAULT
	applymovement LOCALID_LITTLE_GIRL, LilycoveCity_PokemonTrainerFanClub_Movement_LittleGirlMoveCloserToPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement LOCALID_LITTLE_GIRL, LilycoveCity_PokemonTrainerFanClub_Movement_LittleGirlHideFromPlayer
	waitmovement 0
	setvar VAR_LILYCOVE_FAN_CLUB_STATE, 2
	releaseall
	end

LilycoveCity_PokemonTrainerFanClub_Movement_FanApproachPlayer: @ 821C7F5
	delay_8
	walk_in_place_fastest_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

LilycoveCity_PokemonTrainerFanClub_Movement_LittleGirlWatchPlayer: @ 821C7FD
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_down
	step_end

LilycoveCity_PokemonTrainerFanClub_Movement_LittleGirlMoveCloserToPlayer: @ 821C804
	walk_down
	walk_in_place_fastest_right
	step_end

LilycoveCity_PokemonTrainerFanClub_Movement_LittleGirlHideFromPlayer: @ 821C807
	jump_in_place_right
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_in_place_fastest_down
	step_end

LilycoveCity_PokemonTrainerFanClub_OnTransition: @ 821C80D
	call LilycoveCity_PokemonTrainerFanClub_EventScript_HideOrShowInterviewer
	compare VAR_LILYCOVE_FAN_CLUB_STATE, 1
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_SetFanMemberPositionsForFirstFanMeeting
	compare VAR_LILYCOVE_FAN_CLUB_STATE, 2
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_UpdateFanMemberPositions
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_UpdateFanMemberPositions:: @ 821C829
	special TryLoseFansFromPlayTime
	call LilycoveCity_PokemonTrainerFanClub_EventScript_CheckSetUpTVShow
	setvar VAR_0x8004, FANCLUB_MEMBER1
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember1ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER2
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember2ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER3
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember3ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER4
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember4ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER5
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember5ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER6
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember6ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER7
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember7ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER8
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember8ToFarTable
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_HideOrShowInterviewer:: @ 821C8DA
	specialvar VAR_RESULT, ShouldHideFanClubInterviewer
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_HideInterviewer
	clearflag FLAG_HIDE_LILYCOVE_FAN_CLUB_INTERVIEWER
	clearflag FLAG_FAN_CLUB_STRENGTH_SHARED
	return

LilycoveCity_PokemonTrainerFanClub_EventScript_HideInterviewer:: @ 821C8F1
	setflag FLAG_HIDE_LILYCOVE_FAN_CLUB_INTERVIEWER
	return

@ Set up the fan club TV show, if the player has at least 5 fans in the club
@ Rather than counting up, 1 is subtracted from the total for each member not a fan of the players
LilycoveCity_PokemonTrainerFanClub_EventScript_CheckSetUpTVShow:: @ 821C8F5
	setvar VAR_0x8005, NUM_TRAINER_FAN_CLUB_MEMBERS
	setvar VAR_0x8004, FANCLUB_MEMBER1
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_CountNotPlayersFan
	setvar VAR_0x8004, FANCLUB_MEMBER2
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_CountNotPlayersFan
	setvar VAR_0x8004, FANCLUB_MEMBER3
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_CountNotPlayersFan
	setvar VAR_0x8004, FANCLUB_MEMBER4
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_CountNotPlayersFan
	setvar VAR_0x8004, FANCLUB_MEMBER5
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_CountNotPlayersFan
	setvar VAR_0x8004, FANCLUB_MEMBER6
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_CountNotPlayersFan
	setvar VAR_0x8004, FANCLUB_MEMBER7
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_CountNotPlayersFan
	setvar VAR_0x8004, FANCLUB_MEMBER8
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_CountNotPlayersFan
	compare VAR_0x8005, 5
	goto_if_ge LilycoveCity_PokemonTrainerFanClub_EventScript_TrySetUpTVShow
	return

LilycoveCity_PokemonTrainerFanClub_EventScript_CountNotPlayersFan:: @ 821C9AE
	subvar VAR_0x8005, 1
	return

LilycoveCity_PokemonTrainerFanClub_EventScript_TrySetUpTVShow:: @ 821C9B4
	special TrySetUpTrainerFanClubSpecial
	return

LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember1ToFarTable:: @ 821C9B8
	setobjectxyperm LOCALID_LASS, 7, 5
	return

LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember2ToFarTable:: @ 821C9C0
	setobjectxyperm LOCALID_POKEFAN_M, 3, 4
	return

LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember3ToFarTable:: @ 821C9C8
	setobjectxyperm LOCALID_LITTLE_GIRL, 7, 2
	return

LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember4ToFarTable:: @ 821C9D0
	setobjectxyperm LOCALID_NINJA_BOY, 5, 5
	return

LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember5ToFarTable:: @ 821C9D8
	setobjectxyperm LOCALID_BOY, 5, 2
	return

LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember6ToFarTable:: @ 821C9E0
	setobjectxyperm LOCALID_MAN, 8, 4
	return

LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember7ToFarTable:: @ 821C9E8
	setobjectxyperm LOCALID_WOMAN, 3, 3
	return

LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember8ToFarTable:: @ 821C9F0
	setobjectxyperm LOCALID_EXPERT_F, 8, 3
	return

LilycoveCity_PokemonTrainerFanClub_EventScript_SetFanMemberPositionsForFirstFanMeeting:: @ 821C9F8
	call LilycoveCity_PokemonTrainerFanClub_EventScript_CheckSetUpTVShow
	call LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember2ToFarTable
	call LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember4ToFarTable
	call LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember5ToFarTable
	call LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember7ToFarTable
	call LilycoveCity_PokemonTrainerFanClub_EventScript_MoveMember8ToFarTable
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_Man:: @ 821CA17
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER6
	special BufferFanClubTrainerName
	compare VAR_LILYCOVE_FAN_CLUB_STATE, 0
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_ManPlayerNotChampion
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_ManPlayersFan
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1)
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_ManOnlyNonFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_TrainersPowerIsOutOfTheOrdinary, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_ManPlayersFan:: @ 821CA56
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_ManOnlyFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_YoureOneWeWantToWin, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_ManOnlyFan:: @ 821CA70
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_OthersDontKnowYoureTheBest, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_ManOnlyNonFan:: @ 821CA7A
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_TrainerIsBestNoOneWantsToListen, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_ManPlayerNotChampion:: @ 821CA84
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_HearingAboutToughNewTrainer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_Lass:: @ 821CA8E
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER1
	special BufferFanClubTrainerName
	compare VAR_LILYCOVE_FAN_CLUB_STATE, 0
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_LassPlayerNotChampion
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_LassPlayersFan
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1)
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_LassOnlyNonFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_ICantHelpLikingBrawly, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_LassPlayersFan:: @ 821CACD
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_LassOnlyFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_ImPullingForYou, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_LassOnlyFan:: @ 821CAE7
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_BrawlyNoImYourFan, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_LassOnlyNonFan:: @ 821CAF1
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_NobodyUnderstandsBrawly, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_LassPlayerNotChampion:: @ 821CAFB
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_MyFavoriteTrainerIsBrawly, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_PokefanM:: @ 821CB05
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER2
	special BufferFanClubTrainerName
	compare VAR_LILYCOVE_FAN_CLUB_STATE, 0
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_PokefanMPlayerNotChampion
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_PokefanMPlayersFan
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1)
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_PokefanMOnlyNonFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_LongWayToGoComparedToNorman, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_PokefanMPlayersFan:: @ 821CB44
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_PokefanMOnlyFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_YouveSurpassedYourFather, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_PokefanMOnlyFan:: @ 821CB5E
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_YourFatherNeverGaveUpSoKeepOnBattling, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_PokefanMOnlyNonFan:: @ 821CB68
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_YouAndNormanAreDifferent, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_PokefanMPlayerNotChampion:: @ 821CB72
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_WeDiscussStrongestTrainers, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_LittleGirl:: @ 821CB7C
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER3
	special BufferFanClubTrainerName
	compare VAR_LILYCOVE_FAN_CLUB_STATE, 0
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_LittleGirlPlayerNotChampion
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_LittleGirlPlayersFan
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1)
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_LittleGirlOnlyNonFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_EveryoneThinksTrainerIsCool, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_LittleGirlPlayersFan:: @ 821CBBB
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_LittleGirlOnlyFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_OhWoweeItsPlayer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_LittleGirlOnlyFan:: @ 821CBD5
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_AlwaysCheerForYou, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_LittleGirlOnlyNonFan:: @ 821CBDF
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_TrainerIsReallyCoolItsJustMe, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_LittleGirlPlayerNotChampion:: @ 821CBE9
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_WishThereWasTrainerLikeThat, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_NinjaBoy:: @ 821CBF3
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER4
	special BufferFanClubTrainerName
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_NinjaBoyPlayersFan
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1)
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_NinjaBoyOnlyNonFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_TrainerIsWickedlyCool, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_NinjaBoyPlayersFan:: @ 821CC27
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_NinjaBoyOnlyFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_WantToBeStrongLikeYou, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_NinjaBoyOnlyFan:: @ 821CC41
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_OnlyOneWhoCheersForYou, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_NinjaBoyOnlyNonFan:: @ 821CC4B
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_NeverGoingToStopBeingTrainersFan, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_Boy:: @ 821CC55
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER5
	special BufferFanClubTrainerName
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_BoyPlayersFan
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1)
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_BoyOnlyNonFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_ThinkTrainerIsNumberOne, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_BoyPlayersFan:: @ 821CC89
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_BoyOnlyFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_YoureAmazingAfterAll, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_BoyOnlyFan:: @ 821CCA3
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_ImInYourCorner, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_BoyOnlyNonFan:: @ 821CCAD
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_YoureMaybeStrongerThanTrainer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_Woman:: @ 821CCB7
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER7
	special BufferFanClubTrainerName
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_WomanPlayersFan
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1)
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_WomanOnlyNonFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_TrainerIsStandout, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_WomanPlayersFan:: @ 821CCEB
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_WomanOnlyFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_YouChangedMyMind, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_WomanOnlyFan:: @ 821CD05
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_YouBattleAttractivelyInToughSituation, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_WomanOnlyNonFan:: @ 821CD0F
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_NoOneCanKnockYouButTrainerStronger, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_ExpertF:: @ 821CD19
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER8
	special BufferFanClubTrainerName
	specialvar VAR_RESULT, IsFanClubMemberFanOfPlayer
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_ExpertFPlayersFan
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1)
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_ExpertFOnlyNonFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_HaventRealizedPotential, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_ExpertFPlayersFan:: @ 821CD4D
	specialvar VAR_RESULT, GetNumFansOfPlayerInTrainerFanClub
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_ExpertFOnlyFan
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_YouImpressive, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_ExpertFOnlyFan:: @ 821CD67
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_OnlyIRecognizeYourTrueWorth, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_ExpertFOnlyNonFan:: @ 821CD71
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_YourePowerfulButNotTrueStrength, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_Interviewer:: @ 821CD7B
	lock
	faceplayer
	goto_if_set FLAG_FAN_CLUB_STRENGTH_SHARED, LilycoveCity_PokemonTrainerFanClub_EventScript_AlreadyInterviewed
	goto_if_unset FLAG_FAN_CLUB_STRENGTH_SHARED, LilycoveCity_PokemonTrainerFanClub_EventScript_Interview
	end

@ The interviewer doesnt count as an individual fan club member
@ Instead they always ask about whoever the Lass would be interested in, if not the player
LilycoveCity_PokemonTrainerFanClub_EventScript_Interview:: @ 821CD90
	setvar VAR_0x8005, TVSHOW_FAN_CLUB_SPECIAL
	special InterviewBefore
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_AlreadyInterviewed2
	copyvar VAR_0x800A, VAR_0x8006
	setvar VAR_0x8004, FANCLUB_MEMBER1
	special BufferFanClubTrainerName
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_WhatsYourOpinionOfTrainer, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_FAN_QUESTION
	copyvar VAR_0x8005, VAR_0x800A
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_SubmitOpinion
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_CancelGiveOpinion
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_SubmitOpinion:: @ 821CDE0
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_ThatsWhatYouThink, MSGBOX_DEFAULT
	goto LilycoveCity_PokemonTrainerFanClub_EventScript_RateTrainer
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_CancelGiveOpinion:: @ 821CDEE
	setvar VAR_0x8004, FANCLUB_MEMBER1
	special BufferFanClubTrainerName
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_HaveYouForgottenTrainer, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_ForgetTrainer
	compare VAR_RESULT, NO
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_AskForOpinion
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_AskForOpinion:: @ 821CE15
	setvar VAR_0x8004, FANCLUB_MEMBER1
	special BufferFanClubTrainerName
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_WhatsYourOpinionOfTrainer2, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_FAN_QUESTION
	copyvar VAR_0x8005, VAR_0x800A
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_SubmitOpinion
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_CancelGiveOpinion
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_RateTrainer:: @ 821CE4D
	setvar VAR_0x8004, FANCLUB_MEMBER1
	special BufferFanClubTrainerName
	message LilycoveCity_PokemonTrainerFanClub_Text_HowStrongRateTrainer
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_POKEMON_FAN_CLUB_RATER
	special ShowScrollableMultichoice
	waitstate
	setvar VAR_0x8004, FANCLUB_MEMBER1
	switch VAR_RESULT
	case 11, LilycoveCity_PokemonTrainerFanClub_EventScript_CancelRateTrainer
	case MULTI_B_PRESSED, LilycoveCity_PokemonTrainerFanClub_EventScript_CancelRateTrainer
	setvar VAR_0x8004, FANCLUB_MEMBER1
	special BufferFanClubTrainerName
	copyvar VAR_0x8006, VAR_0x800A
	copyvar VAR_0x8005, VAR_RESULT
	special PutFanClubSpecialOnTheAir
	goto LilycoveCity_PokemonTrainerFanClub_EventScript_CompleteInterview
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_CancelRateTrainer:: @ 821CE9F
	setvar VAR_0x8004, FANCLUB_MEMBER1
	special BufferFanClubTrainerName
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_HaveYouForgottenTrainer2, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_ForgetTrainer
	compare VAR_RESULT, NO
	goto_if_eq LilycoveCity_PokemonTrainerFanClub_EventScript_RateTrainer
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_ForgetTrainer:: @ 821CEC6
	setvar VAR_0x8004, FANCLUB_MEMBER1
	special BufferFanClubTrainerName
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_YouShouldMeetTrainer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_CompleteInterview:: @ 821CED8
	setvar VAR_0x8004, FANCLUB_MEMBER1
	special BufferFanClubTrainerName
	msgbox LilycoveCity_PokemonTrainerFanClub_Text_ThankYouIllShareThisInfo, MSGBOX_DEFAULT
	setflag FLAG_FAN_CLUB_STRENGTH_SHARED
	release
	end

LilycoveCity_PokemonTrainerFanClub_EventScript_AlreadyInterviewed:: @ 821CEED
	setvar VAR_0x8004, FANCLUB_MEMBER1
	special BufferFanClubTrainerName
	msgbox LilycoveCity_PokemonTrainerFanClub_HopeYouCatchTVSpecial, MSGBOX_DEFAULT
	release
	end

@ Shouldnt be reached
LilycoveCity_PokemonTrainerFanClub_EventScript_AlreadyInterviewed2:: @ 821CEFF
	end

LilycoveCity_PokemonTrainerFanClub_Text_OhWowItsPlayer: @ 821CF00
	.string "아!\n"
	.string "{PLAYER}{K_I}다!!$"

LilycoveCity_PokemonTrainerFanClub_Text_HeardAboutYouImYourFan: @ 821CF12
	.string "들었어!\n"
	.string "너 강하다고 말야\p"
	.string "여기에서는 모두\n"
	.string "누가 가장 강한 트레이너인가\l"
	.string "이야기하고 있는데\p"
	.string "나 너에 대한 소문을 들어서\n"
	.string "네 팬이 되기로 했어!\p"
	.string "앞으로도 강한 트레이너와\n"
	.string "팍팍 싸워서\p"
	.string "우리들에게 뜨거운\n"
	.string "배틀을 보여줘!\p"
	.string "그러면 분명 모두\n"
	.string "너를 다시 보게 될 거야\p"
	.string "그럼 기대하고 있을게!\n"
	.string "{PLAYER}!!$"

LilycoveCity_PokemonTrainerFanClub_Text_YoureOneWeWantToWin: @ 821D094
	.string "오 {PLAYER}!!\n"
	.string "응원하고 있어!!$"

LilycoveCity_PokemonTrainerFanClub_Text_OthersDontKnowYoureTheBest: @ 821D0BB
	.string "저 녀석들은 몰라\n"
	.string "네가 가장 최고라는 걸 말야!\p"
	.string "그렇지 {PLAYER}!\n"
	.string "근성을 보여줘!$"

LilycoveCity_PokemonTrainerFanClub_Text_TrainersPowerIsOutOfTheOrdinary: @ 821D12A
	.string "너에게는 미안하지만 지금 가장\n"
	.string "주목받는 트레이너는\l"
	.string "{STR_VAR_1}{K_I}라고!\p"
	.string "그 강함은\n"
	.string "보통이 아니지$"

LilycoveCity_PokemonTrainerFanClub_Text_TrainerIsBestNoOneWantsToListen: @ 821D1B5
	.string "젠장- 지금은 {STR_VAR_1}{K_IGA}\n"
	.string "가장 강하다고 말하는데도\p"
	.string "아무도 들어주지 않아...$"

LilycoveCity_PokemonTrainerFanClub_Text_HearingAboutToughNewTrainer: @ 821D20C
	.string "최근 차례차례 체육관 관장을\n"
	.string "쓰러뜨리고 있다고 하는\p"
	.string "강한 트레이너가\n"
	.string "나타난 것 같아\p"
	.string "너 뭐 아는 거 없어?$"

LilycoveCity_PokemonTrainerFanClub_Text_ImPullingForYou: @ 821D2A6
	.string "아!\n"
	.string "{PLAYER}!!\p"
	.string "힘내\n"
	.string "응원하고 있으니까!$"

LilycoveCity_PokemonTrainerFanClub_Text_BrawlyNoImYourFan: @ 821D2CE
	.string "철구님...\p"
	.string "아!\n"
	.string "아냐 아냐!\p"
	.string "나는 어디까지나 당신의\n"
	.string "팬이니까!\p"
	.string "그러니까 나를 위해\n"
	.string "힘내줘!$"

LilycoveCity_PokemonTrainerFanClub_Text_ICantHelpLikingBrawly: @ 821D347
	.string "역시 나는 철구님만을\n"
	.string "좋아할 수밖에 없어-$"

LilycoveCity_PokemonTrainerFanClub_Text_NobodyUnderstandsBrawly: @ 821D377
	.string "아무도 철구님의\n"
	.string "매력을 알아주지 않아...\p"
	.string "좋아!\p"
	.string "나 혼자서라도 철구님을\n"
	.string "응원해 나갈 테니까!$"

LilycoveCity_PokemonTrainerFanClub_Text_MyFavoriteTrainerIsBrawly: @ 821D3EE
	.string "내가 가장 좋아하는\n"
	.string "트레이너는 누가 뭐래도\p"
	.string "무로마을의 체육관 관장\n"
	.string "철구님이야!$"

LilycoveCity_PokemonTrainerFanClub_Text_YouveSurpassedYourFather: @ 821D438
	.string "너는 드디어 모든 면에서\n"
	.string "너의 아버지를 넘어섰구나!\p"
	.string "이 내가 말하는 거니까\n"
	.string "틀림없다!$"

LilycoveCity_PokemonTrainerFanClub_Text_YourFatherNeverGaveUpSoKeepOnBattling: @ 821D4A3
	.string "네 아버지는 위기가 되어도\n"
	.string "포기하지 않고 싸우고 있었다...\p"
	.string "나는 알고 있다네\p"
	.string "너는 아무리 져도 결코\n"
	.string "포기하지 않을 것을!\l"
	.string "그러니 힘내주게!$"

LilycoveCity_PokemonTrainerFanClub_Text_LongWayToGoComparedToNorman: @ 821D52E
	.string "너보다 종길씨 쪽이\n"
	.string "더 강하고 근사하게\l"
	.string "볼 만한 배틀을 했었다!\p"
	.string "아무리 네가 강하다고\n"
	.string "말해진다 한들\p"
	.string "네 아버지와 비교하면\n"
	.string "아직이구나$"

LilycoveCity_PokemonTrainerFanClub_Text_YouAndNormanAreDifferent: @ 821D5DC
	.string "너도 종길씨와 같은 분위기\n"
	.string "라고 해야 하나 박력 있구나\p"
	.string "하지만 종길씨와는 결정적으로\n"
	.string "다른 것이 있다!\p"
	.string "...그건 내가 말할 수 없다\n"
	.string "스스로 찾아보거라$"

LilycoveCity_PokemonTrainerFanClub_Text_WeDiscussStrongestTrainers: @ 821D69C
	.string "여기 있는 모두는\n"
	.string "포켓몬 승부를 좋아해서 말야\p"
	.string "누가 가장 강한 트레이너인지\n"
	.string "이야기하고 있어!\p"
	.string "너도 유명해진다면\n"
	.string "모두 팬이 될지도 몰라!$"

LilycoveCity_PokemonTrainerFanClub_Text_OhWoweeItsPlayer: @ 821D751
	.string "우와-! {PLAYER}{K_I}다-\n"
	.string "나 처음 봐-!\p"
	.string "악수해줘-\n"
	.string "악수!$"

LilycoveCity_PokemonTrainerFanClub_Text_AlwaysCheerForYou: @ 821D79B
	.string "나 언제까지나 {PLAYER}{K_EULREUL}\n"
	.string "응원할 거야!\p"
	.string "나 더 이상 {PLAYER}의 지는\n"
	.string "모습 보고 싶지 않아\p"
	.string "{PLAYER} 사실은\n"
	.string "강한걸 그치!$"

LilycoveCity_PokemonTrainerFanClub_Text_EveryoneThinksTrainerIsCool: @ 821D822
	.string "{STR_VAR_1}씨는 근사해...\p"
	.string "저기 모두도\n"
	.string "그렇다고 생각하지-?$"

LilycoveCity_PokemonTrainerFanClub_Text_TrainerIsReallyCoolItsJustMe: @ 821D857
	.string "{STR_VAR_1}씨는 정말\n"
	.string "근사하지...\p"
	.string "나 혼자가 되어도\n"
	.string "쭉 응원할 거야-!$"

LilycoveCity_PokemonTrainerFanClub_Text_WishThereWasTrainerLikeThat: @ 821D8C4
	.string "나 말야\n"
	.string "좋아하는 트레이너는\p"
	.string "근사하고\p"
	.string "강하고\p"
	.string "그리고 상냥한\p"
	.string "그런 트레이너가 좋아...$"

LilycoveCity_PokemonTrainerFanClub_Text_WantToBeStrongLikeYou: @ 821D921
	.string "아! {PLAYER}{K_I}다-!\n"
	.string "굉장해-!\p"
	.string "나도 자라면\n"
	.string "{PLAYER} 같이 강해지고 싶어!$"

LilycoveCity_PokemonTrainerFanClub_Text_OnlyOneWhoCheersForYou: @ 821D96A
	.string "...\n"
	.string "나 혼자가 되어도\p"
	.string "쭉 {PLAYER}{K_EULREUL}\n"
	.string "응원할 거야!\p"
	.string "그야 {PLAYER}{K_EULREUL}\n"
	.string "믿고 있으니까!$"

LilycoveCity_PokemonTrainerFanClub_Text_TrainerIsWickedlyCool: @ 821D9D1
	.string "{STR_VAR_1}{K_EUNNEUN} 근사하지-\n"
	.string "나하고 악수해주면 좋겠다$"

LilycoveCity_PokemonTrainerFanClub_Text_NeverGoingToStopBeingTrainersFan: @ 821DA0D
	.string "...\n"
	.string "나 혼자가 되어도\p"
	.string "반드시 {STR_VAR_1}의 팬을\n"
	.string "그만두지 않을 거야!\p"
	.string "그야 나 들었어\n"
	.string "{STR_VAR_1}{K_EUNNEUN} 절대 지지 않는대$"

LilycoveCity_PokemonTrainerFanClub_Text_YoureAmazingAfterAll: @ 821DA73
	.string "{PLAYER}!\n"
	.string "역시 대단해 들었어!\p"
	.string "나는 너를 처음 봤을 때부터\n"
	.string "대단한 녀석이라고 생각했었어!\l"
	.string "역시 내 눈은 확실하다니까!$"

LilycoveCity_PokemonTrainerFanClub_Text_ImInYourCorner: @ 821DAF5
	.string "뭐 다른 녀석들의\n"
	.string "말하는 건 신경 쓰지 마\l"
	.string "내가 있으니까!\p"
	.string "너는 걱정하지 말고 평소대로\n"
	.string "싸우고 있으면 돼$"

LilycoveCity_PokemonTrainerFanClub_Text_ThinkTrainerIsNumberOne: @ 821DB69
	.string "너도 상당히\n"
	.string "좋은 트레이너라고 생각하는데\p"
	.string "지금은 역시 {STR_VAR_1}{K_IGA}\n"
	.string "제일이라고 생각해\p"
	.string "뭐 내가 생각하는 것뿐이니까\n"
	.string "그렇게 신경 쓰지 않아도 돼$"

LilycoveCity_PokemonTrainerFanClub_Text_YoureMaybeStrongerThanTrainer: @ 821DBFB
	.string "너는 정말로 강하구나...\n"
	.string "{STR_VAR_1}보다 강할지도 모르겠어\p"
	.string "하지만 내가 {STR_VAR_1}{K_EULREUL}\n"
	.string "응원하지 않으면\l"
	.string "누가 응원하겠어!$"

LilycoveCity_PokemonTrainerFanClub_Text_YouChangedMyMind: @ 821DC68
	.string "다시 봤어!\n"
	.string "당신 정말로 강하구나!\p"
	.string "어떻게 하면 그렇게 강해지는지\n"
	.string "가르침 받고 싶은걸$"

LilycoveCity_PokemonTrainerFanClub_Text_YouBattleAttractivelyInToughSituation: @ 821DCD6
	.string "당신은 위기에 몰리면 몰릴수록\n"
	.string "화려한 배틀을 하는구나\l"
	.string "다음 대전이 기대되는걸!$"

LilycoveCity_PokemonTrainerFanClub_Text_TrainerIsStandout: @ 821DD36
	.string "최근 트레이너하면\n"
	.string "역시 {STR_VAR_1}{K_I}지!\l"
	.string "그 강함은 보통이 아니야\p"
	.string "당신도 잘하지만\n"
	.string "{STR_VAR_1}{K_WAGWA} 비교하면 아직이지-$"

LilycoveCity_PokemonTrainerFanClub_Text_NoOneCanKnockYouButTrainerStronger: @ 821DDCE
	.string "당신 정말로\n"
	.string "인기 있네...\p"
	.string "강하지 포켓몬에게 상냥하지\p"
	.string "말할 것도 없네\p"
	.string "하지만 말야! 나는\n"
	.string "{STR_VAR_1}{K_EULREUL} 믿고 있어!\p"
	.string "{STR_VAR_1} 쪽이 확실히\n"
	.string "강하다고 정해져 있으니까!$"

LilycoveCity_PokemonTrainerFanClub_Text_YouImpressive: @ 821DE72
	.string "자네...\p"
	.string "꽤 하는군!$"

LilycoveCity_PokemonTrainerFanClub_Text_OnlyIRecognizeYourTrueWorth: @ 821DE83
	.string "자네의 진정한 힘은\n"
	.string "이 나만이 알고 있으면 된다\p"
	.string "모두는 그 감춰진 힘을\n"
	.string "알지 못할 게다...$"

LilycoveCity_PokemonTrainerFanClub_Text_HaventRealizedPotential: @ 821DEFF
	.string "음 자네 상당히 좋은\n"
	.string "눈을 하고 있구먼\p"
	.string "허나!\p"
	.string "...음\n"
	.string "아직인 모양이구먼$"

LilycoveCity_PokemonTrainerFanClub_Text_YourePowerfulButNotTrueStrength: @ 821DF51
	.string "확실히 자네는\n"
	.string "터무니없이 강할지도 모르겠군\p"
	.string "허나!\n"
	.string "나는 알 수 있다\p"
	.string "그 강함은 아직\n"
	.string "진정한 강함이라고 할 수 없다!\l"
	.string "진정한 강함이란!\p"
	.string "......\p"
	.string "실은 나도\n"
	.string "잘 모르겠구먼$"
