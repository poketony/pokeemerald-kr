.set LOCALID_MC, 1
.set LOCALID_JUDGE, 2
.set LOCALID_CONTESTANT_1, 3
.set LOCALID_CONTESTANT_2, 4
.set LOCALID_CONTESTANT_3, 5
.set LOCALID_AUDIENCE_1, 6
.set LOCALID_AUDIENCE_3, 7
.set LOCALID_AUDIENCE_4, 8
.set LOCALID_AUDIENCE_5, 9
.set LOCALID_AUDIENCE_6, 10
.set LOCALID_AUDIENCE_7, 11
.set LOCALID_AUDIENCE_2, 12
.set LOCALID_POKEBALL, 13
.set LOCALID_CONTESTANT_4, 14
.set LOCALID_ARTIST, 15

@ Either ends or returns to EventScript_ContestReceptionist after submitting a contest entry
LilycoveCity_ContestLobby_EventScript_SpeakToContestReceptionist:: @ 8279CC5
	lock
	faceplayer
	compare VAR_CONTEST_PRIZE_PICKUP, 0
	goto_if_ne LilycoveCity_ContestLobby_EventScript_PickUpPrize
	call_if_set FLAG_RECEIVED_POKEBLOCK_CASE, LilycoveCity_ContestLobby_EventScript_ReceptionWelcome
	call_if_unset FLAG_RECEIVED_POKEBLOCK_CASE, LilycoveCity_ContestLobby_EventScript_GivePokeblockCase
	goto LilycoveCity_ContestLobby_EventScript_AskEnterContest
	end

LilycoveCity_ContestLobby_EventScript_ReceptionWelcome:: @ 8279CEA
	msgbox LilycoveCity_ContestLobby_Text_ContestReception, MSGBOX_DEFAULT
	return

LilycoveCity_ContestLobby_EventScript_GivePokeblockCase:: @ 8279CF3
	msgbox LilycoveCity_ContestLobby_Text_ReceptionDontHavePokeblockCase, MSGBOX_DEFAULT
	giveitem ITEM_POKEBLOCK_CASE
	setflag FLAG_RECEIVED_POKEBLOCK_CASE
	msgbox LilycoveCity_ContestLobby_Text_NowThatWeveClearedThatUp, MSGBOX_DEFAULT
	return

LilycoveCity_ContestLobby_EventScript_PickUpPrize:: @ 8279D13
	msgbox LilycoveCity_ContestLobby_Text_PokemonWonWeHavePrize, MSGBOX_DEFAULT
	switch VAR_CONTEST_PRIZE_PICKUP
	case 4, LilycoveCity_ContestLobby_EventScript_GiveLuxuryBallAtCounter
	end

LilycoveCity_ContestLobby_EventScript_GiveLuxuryBallAtCounter:: @ 8279D2C
	giveitem ITEM_LUXURY_BALL
	compare VAR_RESULT, FALSE
	goto_if_eq LilycoveCity_ContestLobby_EventScript_NoRoomForLuxuryBallAtCounter
	setvar VAR_CONTEST_PRIZE_PICKUP, 0
	closemessage
	release
	end

LilycoveCity_ContestLobby_EventScript_NoRoomForLuxuryBallAtCounter:: @ 8279D4B
	call Common_EventScript_BagIsFull
	msgbox LilycoveCity_ContestLobby_Text_ComeBackForPrizeLater, MSGBOX_DEFAULT
	release
	end

LilycoveCity_ContestLobby_EventScript_AskEnterContest:: @ 8279D5A
	message LilycoveCity_ContestLobby_Text_EnterContest1
	waitmessage
	multichoice 0, 0, MULTI_ENTERINFO, 0
	switch VAR_RESULT
	case 0, LilycoveCity_ContestLobby_EventScript_ChooseContestRank
	case 1, LilycoveCity_ContestLobby_EventScript_ContestInfo
	case 2, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	case MULTI_B_PRESSED, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	end

LilycoveCity_ContestLobby_EventScript_ContestInfo:: @ 8279D97
	message LilycoveCity_ContestLobby_Text_WhichTopic1
	waitmessage
	multichoice 0, 0, MULTI_CONTEST_INFO, 0
	switch VAR_RESULT
	case 0, LilycoveCity_ContestLobby_EventScript_ExplainContests
	case 1, LilycoveCity_ContestLobby_EventScript_ExplainContestTypes
	case 2, LilycoveCity_ContestLobby_EventScript_ExplainContestRanks
	case 3, LilycoveCity_ContestLobby_EventScript_AskEnterContest
	case MULTI_B_PRESSED, LilycoveCity_ContestLobby_EventScript_AskEnterContest
	end

LilycoveCity_ContestLobby_EventScript_ExplainContests:: @ 8279DDF
	msgbox LilycoveCity_ContestLobby_Text_ExplainContests, MSGBOX_DEFAULT
	goto LilycoveCity_ContestLobby_EventScript_ContestInfo
	end

LilycoveCity_ContestLobby_EventScript_ExplainContestTypes:: @ 8279DED
	msgbox LilycoveCity_ContestLobby_Text_ExplainContestTypes, MSGBOX_DEFAULT
	goto LilycoveCity_ContestLobby_EventScript_ContestInfo
	end

LilycoveCity_ContestLobby_EventScript_ExplainContestRanks:: @ 8279DFB
	msgbox LilycoveCity_ContestLobby_Text_ExplainContestRanks, MSGBOX_DEFAULT
	goto LilycoveCity_ContestLobby_EventScript_ContestInfo
	end

LilycoveCity_ContestLobby_EventScript_CancelEnterContest:: @ 8279E09
	msgbox LilycoveCity_ContestLobby_Text_ParticipateAnotherTime, MSGBOX_DEFAULT
	release
	end

LilycoveCity_ContestLobby_EventScript_ChooseContestMon:: @ 8279E13
	msgbox LilycoveCity_ContestLobby_Text_EnterWhichPokemon1, MSGBOX_DEFAULT
	choosecontestmon
	compare VAR_0x8004, 255
	goto_if_eq LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	special TryEnterContestMon
	compare VAR_RESULT, CANT_ENTER_CONTEST
	goto_if_eq LilycoveCity_ContestLobby_EventScript_CantEnterLowRank
	compare VAR_RESULT, CAN_ENTER_CONTEST_EQUAL_RANK
	goto_if_eq LilycoveCity_ContestLobby_EventScript_EnterMon
	compare VAR_RESULT, CAN_ENTER_CONTEST_HIGH_RANK
	goto_if_eq LilycoveCity_ContestLobby_EventScript_ConfirmEntryAlreadyWon
	compare VAR_RESULT, CANT_ENTER_CONTEST_EGG
	goto_if_eq LilycoveCity_ContestLobby_EventScript_CantEnterEgg
	compare VAR_RESULT, CANT_ENTER_CONTEST_FAINTED
	goto_if_eq LilycoveCity_ContestLobby_EventScript_CantEnterFainted
	end

LilycoveCity_ContestLobby_EventScript_ChooseContestRank:: @ 8279E62
	message LilycoveCity_ContestLobby_Text_EnterWhichRank
	waitmessage
	multichoice 0, 0, MULTI_CONTEST_RANK, 0
	switch VAR_RESULT
	case 0, LilycoveCity_ContestLobby_EventScript_EnterNormalRank
	case 1, LilycoveCity_ContestLobby_EventScript_EnterSuperRank
	case 2, LilycoveCity_ContestLobby_EventScript_EnterHyperRank
	case 3, LilycoveCity_ContestLobby_EventScript_EnterMasterRank
	case 4, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	case MULTI_B_PRESSED, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	end

LilycoveCity_ContestLobby_EventScript_EnterNormalRank:: @ 8279EB5
	setvar VAR_CONTEST_RANK, CONTEST_RANK_NORMAL
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestType
	end

LilycoveCity_ContestLobby_EventScript_EnterSuperRank:: @ 8279EC0
	setvar VAR_CONTEST_RANK, CONTEST_RANK_SUPER
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestType
	end

LilycoveCity_ContestLobby_EventScript_EnterHyperRank:: @ 8279ECB
	setvar VAR_CONTEST_RANK, CONTEST_RANK_HYPER
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestType
	end

LilycoveCity_ContestLobby_EventScript_EnterMasterRank:: @ 8279ED6
	setvar VAR_CONTEST_RANK, CONTEST_RANK_MASTER
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestType
	end

@ The multichoice selection IDs are equal to the CATEGORY values
@ So rather than list the cases they just copy VAR_RESULT for a valid selection into VAR_CONTEST_CATEGORY
LilycoveCity_ContestLobby_EventScript_ChooseContestType:: @ 8279EE1
	message LilycoveCity_ContestLobby_Text_EnterWhichContest1
	waitmessage
	multichoice 0, 0, MULTI_CONTEST_TYPE, 0
	switch VAR_RESULT
	case 5, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	case MULTI_B_PRESSED, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	copyvar VAR_CONTEST_CATEGORY, VAR_RESULT
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	end

LilycoveCity_ContestLobby_EventScript_CantEnterLowRank:: @ 8279F12
	msgbox LilycoveCity_ContestLobby_Text_MonNotQualifiedForRank, MSGBOX_DEFAULT
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	release
	end

@ Unused
LilycoveCity_ContestLobby_EventScript_ConfirmEntry:: @ 8279F21
	msgbox LilycoveCity_ContestLobby_Text_ConfirmContestMon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	case YES, LilycoveCity_ContestLobby_EventScript_EnterMon
	end

LilycoveCity_ContestLobby_EventScript_ConfirmEntryAlreadyWon:: @ 8279F45
	msgbox LilycoveCity_ContestLobby_Text_AlreadyWonEnterAnyway, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	case YES, LilycoveCity_ContestLobby_EventScript_EnterMon
	end

LilycoveCity_ContestLobby_EventScript_CantEnterEgg:: @ 8279F69
	msgbox LilycoveCity_ContestLobby_Text_EggCannotTakePart, MSGBOX_DEFAULT
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	release
	end

LilycoveCity_ContestLobby_EventScript_CantEnterFainted:: @ 8279F78
	msgbox LilycoveCity_ContestLobby_Text_MonInNoConditionForContest, MSGBOX_DEFAULT
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	release
	end

@ The return here is back to LilycoveCity_ContestLobby_EventScript_ContestReceptionist
LilycoveCity_ContestLobby_EventScript_EnterMon:: @ 8279F87
	msgbox LilycoveCity_ContestLobby_Text_YourMonIsEntryNum4, MSGBOX_DEFAULT
	closemessage
	releaseall
	setvar VAR_CONTEST_HALL_STATE, 1
	return

ContestHall_EventScript_DoContest:: @ 8279F97
	special LinkContestTryShowWirelessIndicator
	setvar VAR_0x8006, 0
	lockall
	applymovement LOCALID_CONTESTANT_4, ContestHall_Movement_Player4FaceUp
	waitmovement 0
	applymovement LOCALID_MC, ContestHall_Movement_MCWalkDown
	waitmovement 0
	releaseall
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_GetContestRankStringId
	call ContestHall_EventScript_GetContestCategory
	call ContestHall_EventScript_ContestGettingStarted
	call ContestHall_EventScript_ShowContestMons
	call ContestHall_EventScript_DoContestAppeals
	call ContestHall_EventScript_ContestResults
	call ContestHall_EventScript_GetWinnerObjEventId
	call ContestHall_EventScript_CongratulateWinner
	call ContestHall_EventScript_AudienceLookAround
	call ContestHall_EventScript_GiveWinnerPrize
	setvar VAR_CONTEST_HALL_STATE, 2
	return

ContestHall_EventScript_GetContestRankStringId:: @ 8279FF2
	switch VAR_CONTEST_RANK
	case CONTEST_RANK_NORMAL, ContestHall_EventScript_GetNormalStringId
	case CONTEST_RANK_SUPER, ContestHall_EventScript_GetSuperStringId
	case CONTEST_RANK_HYPER, ContestHall_EventScript_GetHyperStringId
	case CONTEST_RANK_MASTER, ContestHall_EventScript_GetMasterStringId
	return

ContestHall_EventScript_GetNormalStringId:: @ 827A024
	setvar VAR_0x8009, STDSTRING_NORMAL
	return

ContestHall_EventScript_GetSuperStringId:: @ 827A02A
	setvar VAR_0x8009, STDSTRING_SUPER
	return

ContestHall_EventScript_GetHyperStringId:: @ 827A030
	setvar VAR_0x8009, STDSTRING_HYPER
	return

ContestHall_EventScript_GetMasterStringId:: @ 827A036
	setvar VAR_0x8009, STDSTRING_MASTER
	return

@ This whole switch is equivalent to copyvar VAR_0x8008, VAR_CONTEST_CATEGORY
ContestHall_EventScript_GetContestCategory:: @ 827A03C
	switch VAR_CONTEST_CATEGORY
	case CONTEST_CATEGORY_COOL, ContestHall_EventScript_GetCategoryCool
	case CONTEST_CATEGORY_BEAUTY, ContestHall_EventScript_GetCategoryBeauty
	case CONTEST_CATEGORY_CUTE, ContestHall_EventScript_GetCategoryCute
	case CONTEST_CATEGORY_SMART, ContestHall_EventScript_GetCategorySmart
	case CONTEST_CATEGORY_TOUGH, ContestHall_EventScript_GetCategoryTough
	return

ContestHall_EventScript_GetCategoryCool:: @ 827A079
	setvar VAR_0x8008, CONTEST_CATEGORY_COOL
	return

ContestHall_EventScript_GetCategoryBeauty:: @ 827A07F
	setvar VAR_0x8008, CONTEST_CATEGORY_BEAUTY
	return

ContestHall_EventScript_GetCategoryCute:: @ 827A085
	setvar VAR_0x8008, CONTEST_CATEGORY_CUTE
	return

ContestHall_EventScript_GetCategorySmart:: @ 827A08B
	setvar VAR_0x8008, CONTEST_CATEGORY_SMART
	return

ContestHall_EventScript_GetCategoryTough:: @ 827A091
	setvar VAR_0x8008, CONTEST_CATEGORY_TOUGH
	return

ContestHall_EventScript_ContestGettingStarted:: @ 827A097
	buffercontesttypestring 1, VAR_0x8008
	bufferstdstring 2, VAR_0x8009
	call ContestHall_EventScript_GettingStarted
	lockall
	applymovement LOCALID_MC, ContestHall_Movement_MCBackUp
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_GettingStarted:: @ 827A0B1
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_GettingStartedLink
	lockall
	msgbox ContestHall_Text_GettingStartedParticipantsAsFollows, MSGBOX_DEFAULT
	releaseall
	return

ContestHall_EventScript_GettingStartedLink:: @ 827A0C7
	specialvar VAR_RESULT, IsWirelessContest
	compare VAR_RESULT, TRUE
	goto_if_eq ContestHall_EventScript_GettingStartedWireless
	messageautoscroll ContestHall_Text_GettingStartedParticipantsAsFollowsLink
	waitmessage
	return

ContestHall_EventScript_GettingStartedWireless:: @ 827A0DE
	messageautoscroll ContestHall_Text_GettingStartedWireless
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_ParticipantsAsFollows
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	return

ContestHall_EventScript_ShowContestMons:: @ 827A0F5
	call ContestHall_EventScript_ContestantWalkToCenter
	call ContestHall_EventScript_ShowContestMonPic
	call ContestHall_EventScript_AudienceHeartEmotes
	call ContestHall_EventScript_AudienceReactToContestant
	call ContestHall_EventScript_ContestantReturn
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_TryWaitForLink
	addvar VAR_0x8006, 1
	compare VAR_0x8006, CONTESTANT_COUNT
	goto_if_ne ContestHall_EventScript_ShowContestMons
	call ContestHall_EventScript_AudienceVote
	setvar VAR_TEMP_1, 6
	return

ContestHall_EventScript_TryWaitForLink:: @ 827A133
	specialvar VAR_RESULT, IsWirelessContest
	compare VAR_RESULT, TRUE
	goto_if_eq ContestHall_EventScript_WaitForLink
	return

ContestHall_EventScript_WaitForLink:: @ 827A144
	special LinkContestWaitForConnection
	waitstate
	return

ContestHall_EventScript_ContestantWalkToCenter:: @ 827A149
	compare VAR_0x8006, 0
	goto_if_eq ContestHall_EventScript_Player1WalkToCenter
	compare VAR_0x8006, 1
	goto_if_eq ContestHall_EventScript_Player2WalkToCenter
	compare VAR_0x8006, 2
	goto_if_eq ContestHall_EventScript_Player3WalkToCenter
	compare VAR_0x8006, 3
	goto_if_eq ContestHall_EventScript_Player4WalkToCenter
	return

ContestHall_EventScript_Player1WalkToCenter:: @ 827A176
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement LOCALID_CONTESTANT_1, ContestHall_Movement_Player1WalkToCenter
	waitmovement 0
	releaseall
	setvar VAR_0x800B, LOCALID_CONTESTANT_1
	return

ContestHall_EventScript_Player2WalkToCenter:: @ 827A18D
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement LOCALID_CONTESTANT_2, ContestHall_Movement_Player2WalkToCenter
	waitmovement 0
	releaseall
	setvar VAR_0x800B, LOCALID_CONTESTANT_2
	return

ContestHall_EventScript_Player3WalkToCenter:: @ 827A1A4
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement LOCALID_CONTESTANT_3, ContestHall_Movement_Player3WalkToCenter
	waitmovement 0
	releaseall
	setvar VAR_0x800B, LOCALID_CONTESTANT_3
	return

ContestHall_EventScript_Player4WalkToCenter:: @ 827A1BB
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement LOCALID_CONTESTANT_4, ContestHall_Movement_Player4WalkToCenter
	waitmovement 0
	releaseall
	setvar VAR_0x800B, LOCALID_CONTESTANT_4
	return

ContestHall_EventScript_ShowContestMonPic:: @ 827A1D2
	special BufferContestTrainerAndMonNames
	addvar VAR_0x8006, 1
	buffernumberstring 1, VAR_0x8006
	lockall
	applymovement VAR_0x800B, ContestHall_Movement_ContestantDelay32
	waitmovement 0
	releaseall
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_CheckIfContestWithRSPlayer
	addobject LOCALID_POKEBALL
	playse SE_LEDGE
	lockall
	applymovement VAR_0x800B, ContestHall_Movement_ContestantDelay32
	waitmovement 0
	releaseall
	addvar VAR_0x8006, -1
	playse SE_BALL_OPEN
	special ShowContestEntryMonPic
	call ContestHall_EventScript_EntryXTrainersMon
	return

ContestHall_EventScript_EntryXTrainersMon:: @ 827A217
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_EntryXTrainersMonLink
	message ContestHall_Text_EntryXTrainersMon
	waitmessage
	return

ContestHall_EventScript_EntryXTrainersMonLink:: @ 827A229
	messageautoscroll ContestHall_Text_EntryXTrainersMon
	waitmessage
	return

ContestHall_EventScript_AudienceVote:: @ 827A230
	call ContestHall_EventScript_AudienceWillVote
	call ContestHall_EventScript_VotingUnderWay
	playse SE_M_ENCORE2
	waitmessage
	call ContestHall_EventScript_AudienceLookAround
	applymovement LOCALID_MC, ContestHall_Movement_MCFaceJudge2
	waitmovement 0
	applymovement LOCALID_JUDGE, ContestHall_Movement_JudgeFaceMC
	waitmovement 0
	delay 20
	applymovement LOCALID_MC, ContestHall_Movement_FaceContestants
	applymovement LOCALID_JUDGE, ContestHall_Movement_FaceContestants
	waitmovement 0
	return

ContestHall_EventScript_AudienceWillVote:: @ 827A26C
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_AudienceWillVoteLink
	msgbox ContestHall_Text_SeenContestantsAudienceWillVote, MSGBOX_DEFAULT
	return

ContestHall_EventScript_AudienceWillVoteLink:: @ 827A280
	specialvar VAR_RESULT, IsWirelessContest
	compare VAR_RESULT, TRUE
	goto_if_eq ContestHall_EventScript_AudienceWillVoteWireless
	messageautoscroll ContestHall_Text_SeenContestantsAudienceWillVote
	waitmessage
	return

ContestHall_EventScript_AudienceWillVoteWireless:: @ 827A297
	messageautoscroll ContestHall_Text_WeveSeenContestants
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_AudienceWillVote
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_LetVotingBegin
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	return

ContestHall_EventScript_VotingUnderWay:: @ 827A2B9
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_VotingUnderWayLink
	message ContestHall_Text_VotingUnderWay
	return

ContestHall_EventScript_VotingUnderWayLink:: @ 827A2CA
	messageautoscroll ContestHall_Text_VotingUnderWay
	call ContestHall_EventScript_TryWaitForLink
	return

ContestHall_EventScript_AudienceReactToContestant:: @ 827A2D5
	call ContestHall_EventScript_TryWaitForLink
	applymovement LOCALID_MC, ContestHall_Movement_AudienceMemberLookLeft
	waitmovement 0
	playse SE_M_ENCORE2
	call ContestHall_EventScript_VObjectAudienceLookAround
	applymovement LOCALID_AUDIENCE_5, ContestHall_Movement_AudienceMemberLookRight
	applymovement LOCALID_AUDIENCE_2, ContestHall_Movement_AudienceMemberLookDown
	applymovement LOCALID_AUDIENCE_3, ContestHall_Movement_AudienceMemberLookRight
	waitmovement 0
	applymovement LOCALID_MC, ContestHall_Movement_AudienceMemberLookRight
	waitmovement 0
	applymovement LOCALID_AUDIENCE_6, ContestHall_Movement_AudienceMemberLookLeft
	applymovement LOCALID_AUDIENCE_7, ContestHall_Movement_AudienceMemberLookDown
	applymovement LOCALID_AUDIENCE_1, ContestHall_Movement_AudienceMemberLookUp
	applymovement LOCALID_AUDIENCE_4, ContestHall_Movement_AudienceMemberLookLeft
	waitmovement 0
	applymovement LOCALID_MC, ContestHall_Movement_MCLookAtJudge
	waitmovement 0
	applymovement LOCALID_MC, ContestHall_Movement_MCWalkInPlaceDown
	applymovement LOCALID_JUDGE, ContestHall_Movement_JudgeLookAtMC
	waitmovement 0
	releaseall
	call ContestHall_EventScript_TryWaitForLink
	return

@ For below VAR_TEMP_0 is the number of heart emotes to try to display in the audience
@ The number of hearts to try to display is based on the condition of the presented pokemon and the rank
@ For each heart to display a random audience member is chosen, and a new one chosen if they already displayed a heart
@ VAR_TEMP_1 through VAR_TEMP_8 represent each of the 8 audience members that are actual object events
@    and are set to 9 if they havent displayed a heart yet, and 1 if they have
ContestHall_EventScript_AudienceHeartEmotes:: @ 827A34F
	special GetContestMonCondition
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_NPC_NORMAL
	call_if_eq ContestHall_EventScript_GetNumberOfHeartsNormal
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_NPC_SUPER
	call_if_eq ContestHall_EventScript_GetNumberOfHeartsSuper
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_NPC_HYPER
	call_if_eq ContestHall_EventScript_GetNumberOfHeartsHyper
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_NPC_MASTER
	call_if_eq ContestHall_EventScript_GetNumberOfHeartsMaster
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	call_if_eq ContestHall_EventScript_GetNumberOfHeartsLink
	setvar VAR_TEMP_1, 9
	setvar VAR_TEMP_2, 9
	setvar VAR_TEMP_3, 9
	setvar VAR_TEMP_4, 9
	setvar VAR_TEMP_5, 9
	setvar VAR_TEMP_6, 9
	setvar VAR_TEMP_7, 9
	setvar VAR_TEMP_8, 9
	compare VAR_TEMP_0, 0
	call_if_gt ContestHall_EventScript_DisplayHearts
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_4, 0
	setvar VAR_TEMP_5, 0
	setvar VAR_TEMP_6, 0
	setvar VAR_TEMP_7, 0
	setvar VAR_TEMP_8, 0
	return

ContestHall_EventScript_DisplayHearts:: @ 827A3E5
	setvar VAR_RESULT, 8
	special GenerateContestRand
	compare VAR_RESULT, 0
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember1
	compare VAR_RESULT, 1
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember2
	compare VAR_RESULT, 2
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember3
	compare VAR_RESULT, 3
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember4
	compare VAR_RESULT, 4
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember5
	compare VAR_RESULT, 5
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember6
	compare VAR_RESULT, 6
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember7
	compare VAR_RESULT, 7
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember8
	compare VAR_TEMP_0, 0  @ Still more hearts to display
	goto_if_gt ContestHall_EventScript_DisplayHearts
	waitmovement 0
	return

ContestHall_EventScript_GetNumberOfHeartsNormal:: @ 827A454
	compare VAR_0x8004, 80
	goto_if_gt ContestHall_EventScript_Set8Hearts
	compare VAR_0x8004, 70
	goto_if_gt ContestHall_EventScript_Set7Hearts
	compare VAR_0x8004, 60
	goto_if_gt ContestHall_EventScript_Set6Hearts
	compare VAR_0x8004, 50
	goto_if_gt ContestHall_EventScript_Set5Hearts
	compare VAR_0x8004, 40
	goto_if_gt ContestHall_EventScript_Set4Hearts
	compare VAR_0x8004, 30
	goto_if_gt ContestHall_EventScript_Set3Hearts
	compare VAR_0x8004, 20
	goto_if_gt ContestHall_EventScript_Set2Hearts
	compare VAR_0x8004, 10
	goto_if_gt ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

ContestHall_EventScript_GetNumberOfHeartsSuper:: @ 827A4B2
	compare VAR_0x8004, 230
	goto_if_gt ContestHall_EventScript_Set8Hearts
	compare VAR_0x8004, 210
	goto_if_gt ContestHall_EventScript_Set7Hearts
	compare VAR_0x8004, 190
	goto_if_gt ContestHall_EventScript_Set6Hearts
	compare VAR_0x8004, 170
	goto_if_gt ContestHall_EventScript_Set5Hearts
	compare VAR_0x8004, 150
	goto_if_gt ContestHall_EventScript_Set4Hearts
	compare VAR_0x8004, 130
	goto_if_gt ContestHall_EventScript_Set3Hearts
	compare VAR_0x8004, 110
	goto_if_gt ContestHall_EventScript_Set2Hearts
	compare VAR_0x8004, 90
	goto_if_gt ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

ContestHall_EventScript_GetNumberOfHeartsHyper:: @ 827A510
	compare VAR_0x8004, 380
	goto_if_gt ContestHall_EventScript_Set8Hearts
	compare VAR_0x8004, 350
	goto_if_gt ContestHall_EventScript_Set7Hearts
	compare VAR_0x8004, 320
	goto_if_gt ContestHall_EventScript_Set6Hearts
	compare VAR_0x8004, 290
	goto_if_gt ContestHall_EventScript_Set5Hearts
	compare VAR_0x8004, 260
	goto_if_gt ContestHall_EventScript_Set4Hearts
	compare VAR_0x8004, 230
	goto_if_gt ContestHall_EventScript_Set3Hearts
	compare VAR_0x8004, 200
	goto_if_gt ContestHall_EventScript_Set2Hearts
	compare VAR_0x8004, 170
	goto_if_gt ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

ContestHall_EventScript_GetNumberOfHeartsMaster:: @ 827A56E
	compare VAR_0x8004, 600
	goto_if_gt ContestHall_EventScript_Set8Hearts
	compare VAR_0x8004, 560
	goto_if_gt ContestHall_EventScript_Set7Hearts
	compare VAR_0x8004, 520
	goto_if_gt ContestHall_EventScript_Set6Hearts
	compare VAR_0x8004, 480
	goto_if_gt ContestHall_EventScript_Set5Hearts
	compare VAR_0x8004, 440
	goto_if_gt ContestHall_EventScript_Set4Hearts
	compare VAR_0x8004, 400
	goto_if_gt ContestHall_EventScript_Set3Hearts
	compare VAR_0x8004, 360
	goto_if_gt ContestHall_EventScript_Set2Hearts
	compare VAR_0x8004, 320
	goto_if_gt ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

ContestHall_EventScript_GetNumberOfHeartsLink:: @ 827A5CC
	compare VAR_0x8004, 600
	goto_if_gt ContestHall_EventScript_Set8Hearts
	compare VAR_0x8004, 550
	goto_if_gt ContestHall_EventScript_Set7Hearts
	compare VAR_0x8004, 500
	goto_if_gt ContestHall_EventScript_Set6Hearts
	compare VAR_0x8004, 450
	goto_if_gt ContestHall_EventScript_Set5Hearts
	compare VAR_0x8004, 400
	goto_if_gt ContestHall_EventScript_Set4Hearts
	compare VAR_0x8004, 300
	goto_if_gt ContestHall_EventScript_Set3Hearts
	compare VAR_0x8004, 200
	goto_if_gt ContestHall_EventScript_Set2Hearts
	compare VAR_0x8004, 100
	goto_if_gt ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

ContestHall_EventScript_Set1Heart:: @ 827A62A
	setvar VAR_TEMP_0, 1
	return

ContestHall_EventScript_Set2Hearts:: @ 827A630
	setvar VAR_TEMP_0, 2
	return

ContestHall_EventScript_Set3Hearts:: @ 827A636
	setvar VAR_TEMP_0, 3
	return

ContestHall_EventScript_Set4Hearts:: @ 827A63C
	setvar VAR_TEMP_0, 4
	return

ContestHall_EventScript_Set5Hearts:: @ 827A642
	setvar VAR_TEMP_0, 5
	return

ContestHall_EventScript_Set6Hearts:: @ 827A648
	setvar VAR_TEMP_0, 6
	return

ContestHall_EventScript_Set7Hearts:: @ 827A64E
	setvar VAR_TEMP_0, 7
	return

ContestHall_EventScript_Set8Hearts:: @ 827A654
	setvar VAR_TEMP_0, 8
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember1:: @ 827A65A
	compare VAR_TEMP_1, 1
	goto_if_eq ContestHall_EventScript_AudienceMember1AlreadyEmoted
	applymovement LOCALID_AUDIENCE_1, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_1, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember1AlreadyEmoted:: @ 827A67D
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember2:: @ 827A67E
	compare VAR_TEMP_2, 1
	goto_if_eq ContestHall_EventScript_AudienceMember2AlreadyEmoted
	applymovement LOCALID_AUDIENCE_2, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_2, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember2AlreadyEmoted:: @ 827A6A1
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember3:: @ 827A6A2
	compare VAR_TEMP_3, 1
	goto_if_eq ContestHall_EventScript_AudienceMember3AlreadyEmoted
	applymovement LOCALID_AUDIENCE_3, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_3, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember3AlreadyEmoted:: @ 827A6C5
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember4:: @ 827A6C6
	compare VAR_TEMP_4, 1
	goto_if_eq ContestHall_EventScript_Audience4MemberAlreadyEmoted
	applymovement LOCALID_AUDIENCE_4, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_4, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_Audience4MemberAlreadyEmoted:: @ 827A6E9
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember5:: @ 827A6EA
	compare VAR_TEMP_5, 1
	goto_if_eq ContestHall_EventScript_AudienceMember5AlreadyEmoted
	applymovement LOCALID_AUDIENCE_5, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_5, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember5AlreadyEmoted:: @ 827A70D
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember6:: @ 827A70E
	compare VAR_TEMP_6, 1
	goto_if_eq ContestHall_EventScript_AudienceMember6AlreadyEmoted
	applymovement LOCALID_AUDIENCE_6, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_6, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember6AlreadyEmoted:: @ 827A731
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember7:: @ 827A732
	compare VAR_TEMP_7, 1
	goto_if_eq ContestHall_EventScript_AudienceMember7AlreadyEmoted
	applymovement LOCALID_AUDIENCE_7, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_7, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember7AlreadyEmoted:: @ 827A755
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember8:: @ 827A756
	compare VAR_TEMP_8, 1
	goto_if_eq ContestHall_EventScript_AudienceMember8AlreadyEmoted
	applymovement LOCALID_ARTIST, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_8, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember8AlreadyEmoted:: @ 827A779
	return

ContestHall_EventScript_ContestantReturn:: @ 827A77A
	closemessage
	release
	removeobject LOCALID_POKEBALL
	special HideContestEntryMonPic
	call ContestHall_EventScript_TryWaitForLink
	switch VAR_0x8006
	case 0, ContestHall_EventScript_Player1WalkBack
	case 1, ContestHall_EventScript_Player2WalkBack
	case 2, ContestHall_EventScript_Player3WalkBack
	case 3, ContestHall_EventScript_Player4WalkBack
	return

ContestHall_EventScript_Player1WalkBack:: @ 827A7B9
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement VAR_0x800B, ContestHall_Movement_Player1WalkBack
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_Player2WalkBack:: @ 827A7CB
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement VAR_0x800B, ContestHall_Movement_Player2WalkBack
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_Player3WalkBack:: @ 827A7DD
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement VAR_0x800B, ContestHall_Movement_Player3WalkBack
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_Player4WalkBack:: @ 827A7EF
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement VAR_0x800B, ContestHall_Movement_Player4WalkBack
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_DoContestAppeals:: @ 827A801
	lockall
	applymovement LOCALID_MC, ContestHall_Movement_FaceContestants2
	waitmovement 0
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_LetsAppeal
	waitmessage
	applymovement LOCALID_MC, ContestHall_Movement_WalkStageLeft
	applymovement LOCALID_JUDGE, ContestHall_Movement_WalkStageRight
	waitmovement 0
	releaseall
	call ContestHall_EventScript_TryWaitForLink
	setvar VAR_TEMP_9, 1
	special LinkContestTryHideWirelessIndicator
	startcontest
	special LinkContestTryShowWirelessIndicator
	setvar VAR_TEMP_9, 0
	lockall
	applymovement LOCALID_MC, ContestHall_Movement_WalkStageRight
	applymovement LOCALID_JUDGE, ContestHall_Movement_WalkStageLeft
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_LetsAppeal:: @ 827A853
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_LetsAppealLink
	msgbox ContestHall_Text_VotingCompleteLetsAppeal, MSGBOX_DEFAULT
	return

ContestHall_EventScript_LetsAppealLink:: @ 827A867
	specialvar VAR_RESULT, IsWirelessContest
	compare VAR_RESULT, TRUE
	goto_if_eq ContestHall_EventScript_LetsAppealWireless
	messageautoscroll ContestHall_Text_VotingCompleteLetsAppeal
	waitmessage
	return

ContestHall_EventScript_LetsAppealWireless:: @ 827A87E
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_VotingComplete
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_SecondStageOfJudging
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_LetsAppeal
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	return

ContestHall_EventScript_ContestResults:: @ 827A8A5
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_ThatsItForJudging
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_ThankYouForAppeals
	call ContestHall_EventScript_TryWaitForLink
	applymovement LOCALID_MC, ContestHall_Movement_MCFaceJudge
	waitmovement 0
	call ContestHall_EventScript_JudgeLooksReady
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_WeWillDeclareWinner
	call ContestHall_EventScript_TryWaitForLink
	applymovement LOCALID_MC, ContestHall_Movement_FaceContestants
	waitmovement 0
	closemessage
	releaseall
	special LinkContestTryHideWirelessIndicator
	setvar VAR_TEMP_9, 1
	showcontestresults
	setvar VAR_TEMP_9, 0
	playbgm MUS_CONTEST_WINNER, 0
	return

ContestHall_EventScript_ThatsItForJudging:: @ 827A8FB
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_ThatsItForJudgingLink
	msgbox ContestHall_Text_ThatsItForJudging, MSGBOX_DEFAULT
	return

ContestHall_EventScript_ThatsItForJudgingLink:: @ 827A90F
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_ThatsItForJudging
	waitmessage
	delay 30
	return

ContestHall_EventScript_ThankYouForAppeals:: @ 827A91E
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_ThankYouForAppealsLink
	msgbox ContestHall_Text_ThankYouForAppeals, MSGBOX_DEFAULT
	return

ContestHall_EventScript_ThankYouForAppealsLink:: @ 827A932
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_ThankYouForAppeals
	waitmessage
	delay 30
	return

ContestHall_EventScript_JudgeLooksReady:: @ 827A941
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_JudgeLooksReadyLink
	msgbox ContestHall_Text_JudgeLooksReady, MSGBOX_DEFAULT
	return

ContestHall_EventScript_JudgeLooksReadyLink:: @ 827A955
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_JudgeLooksReady
	waitmessage
	delay 30
	return

ContestHall_EventScript_WeWillDeclareWinner:: @ 827A964
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_WeWillDeclareWinnerLink
	msgbox ContestHall_Text_WeWillNowDeclareWinner, MSGBOX_DEFAULT
	return

ContestHall_EventScript_WeWillDeclareWinnerLink:: @ 827A978
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_WeWillNowDeclareWinner
	waitmessage
	delay 30
	return

ContestHall_EventScript_GetWinnerObjEventId:: @ 827A987
	special GetContestWinnerId
	switch VAR_0x8005
	case 0, ContestHall_EventScript_GetPlayer1ObjEventId
	case 1, ContestHall_EventScript_GetPlayer2ObjEventId
	case 2, ContestHall_EventScript_GetPlayer3ObjEventId
	case 3, ContestHall_EventScript_GetPlayer4ObjEventId
	return

ContestHall_EventScript_GetPlayer1ObjEventId:: @ 827A9BC
	setvar VAR_TEMP_3, LOCALID_CONTESTANT_1
	return

ContestHall_EventScript_GetPlayer2ObjEventId:: @ 827A9C2
	setvar VAR_TEMP_3, LOCALID_CONTESTANT_2
	return

ContestHall_EventScript_GetPlayer3ObjEventId:: @ 827A9C8
	setvar VAR_TEMP_3, LOCALID_CONTESTANT_3
	return

ContestHall_EventScript_GetPlayer4ObjEventId:: @ 827A9CE
	setvar VAR_TEMP_3, LOCALID_CONTESTANT_4
	return

ContestHall_EventScript_CongratulateWinner:: @ 827A9D4
	special BufferContestWinnerTrainerName
	special BufferContestWinnerMonName
	addvar VAR_0x8005, 1
	buffernumberstring 1, VAR_0x8005
	addvar VAR_0x8005, -1
	call ContestHall_EventScript_CongratsWinner
	applymovement VAR_TEMP_3, ContestHall_Movement_WinningPlayerWalkUp
	waitmovement 0
	playse SE_M_ENCORE2
	setvar VAR_TEMP_1, 0
	return

ContestHall_EventScript_CongratsWinner:: @ 827AA00
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_CongratsWinnerLink
	msgbox ContestHall_Text_CongratsTrainerXandMon, MSGBOX_DEFAULT
	return

ContestHall_EventScript_CongratsWinnerLink:: @ 827AA14
	messageautoscroll ContestHall_Text_CongratsTrainerXandMon
	waitmessage
	return

ContestHall_EventScript_AudienceLookAround:: @ 827AA1B
	addvar VAR_TEMP_1, 1
	lockall
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_NPC_NORMAL
	call_if_gt ContestHall_EventScript_VObjectAudienceLookAround
	applymovement LOCALID_AUDIENCE_5, ContestHall_Movement_AudienceMemberLookRight
	applymovement LOCALID_AUDIENCE_2, ContestHall_Movement_AudienceMemberLookDown
	applymovement LOCALID_AUDIENCE_3, ContestHall_Movement_AudienceMemberLookRight
	delay 30
	applymovement LOCALID_AUDIENCE_6, ContestHall_Movement_AudienceMemberLookLeft
	applymovement LOCALID_AUDIENCE_7, ContestHall_Movement_AudienceMemberLookDown
	applymovement LOCALID_AUDIENCE_1, ContestHall_Movement_AudienceMemberLookUp
	applymovement LOCALID_AUDIENCE_4, ContestHall_Movement_AudienceMemberLookLeft
	compare VAR_TEMP_1, 4
	goto_if_ne ContestHall_EventScript_AudienceLookAround
	delay 30
	return

ContestHall_EventScript_VObjectAudienceLookAround:: @ 827AA6F
	turnvobject 0, DIR_SOUTH
	turnvobject 2, DIR_SOUTH
	turnvobject 4, DIR_EAST
	turnvobject 6, DIR_SOUTH
	turnvobject 8, DIR_SOUTH
	turnvobject 10, DIR_SOUTH
	turnvobject 12, DIR_SOUTH
	turnvobject 14, DIR_SOUTH
	turnvobject 16, DIR_SOUTH
	turnvobject 18, DIR_SOUTH
	turnvobject 20, DIR_EAST
	turnvobject 22, DIR_EAST
	turnvobject 25, DIR_EAST
	turnvobject 27, DIR_WEST
	turnvobject 28, DIR_EAST
	delay 10
	turnvobject 0, DIR_EAST
	turnvobject 2, DIR_EAST
	turnvobject 4, DIR_EAST
	turnvobject 6, DIR_EAST
	turnvobject 8, DIR_EAST
	turnvobject 10, DIR_WEST
	turnvobject 12, DIR_WEST
	turnvobject 14, DIR_WEST
	turnvobject 16, DIR_WEST
	turnvobject 18, DIR_WEST
	turnvobject 20, DIR_SOUTH
	turnvobject 22, DIR_SOUTH
	turnvobject 25, DIR_NORTH
	turnvobject 27, DIR_NORTH
	turnvobject 28, DIR_NORTH
	delay 10
	turnvobject 1, DIR_NORTH
	turnvobject 3, DIR_NORTH
	turnvobject 5, DIR_NORTH
	turnvobject 7, DIR_NORTH
	turnvobject 9, DIR_EAST
	turnvobject 11, DIR_NORTH
	turnvobject 15, DIR_NORTH
	turnvobject 13, DIR_NORTH
	turnvobject 17, DIR_NORTH
	turnvobject 19, DIR_NORTH
	turnvobject 21, DIR_WEST
	turnvobject 23, DIR_WEST
	turnvobject 24, DIR_WEST
	turnvobject 26, DIR_EAST
	turnvobject 29, DIR_WEST
	turnvobject 30, DIR_WEST
	delay 10
	turnvobject 1, DIR_EAST
	turnvobject 3, DIR_EAST
	turnvobject 5, DIR_EAST
	turnvobject 7, DIR_EAST
	turnvobject 9, DIR_EAST
	turnvobject 11, DIR_WEST
	turnvobject 15, DIR_WEST
	turnvobject 13, DIR_WEST
	turnvobject 17, DIR_WEST
	turnvobject 19, DIR_WEST
	turnvobject 21, DIR_SOUTH
	turnvobject 23, DIR_SOUTH
	turnvobject 24, DIR_SOUTH
	turnvobject 26, DIR_NORTH
	turnvobject 29, DIR_NORTH
	turnvobject 30, DIR_NORTH
	delay 10
	return

ContestHall_EventScript_GiveWinnerPrize:: @ 827AB36
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_EndLinkContest
	call ContestHall_EventScript_CheckShouldSkipPrize
	goto_if_set FLAG_TEMP_2, ContestHall_EventScript_SkipPrize
	lockall
	msgbox ContestHall_Text_AcceptYourPrize, MSGBOX_DEFAULT
	releaseall
	call ContestHall_EventScript_WinnerApproachForPrize
	call ContestHall_EventScript_GivePrizeIfWinner
	playse SE_M_ENCORE2
	setvar VAR_TEMP_1, 0
	call ContestHall_EventScript_AudienceLookAround
	delay 30
	special ShouldReadyContestArtist
	compare VAR_0x8004, TRUE
	goto_if_eq ContestHall_EventScript_SetReadyForContestArtist
	return

ContestHall_EventScript_SkipPrize:: @ 827AB82
	lockall
	msgbox ContestHall_Text_CongratsPleaseCompeteAgain, MSGBOX_DEFAULT
	releaseall
	delay 90
	special ShouldReadyContestArtist
	compare VAR_0x8004, TRUE
	goto_if_eq ContestHall_EventScript_SetReadyForContestArtist
	return

ContestHall_EventScript_CheckShouldSkipPrize:: @ 827AB9E
	specialvar VAR_RESULT, HasMonWonThisContestBefore
	compare VAR_RESULT, TRUE
	goto_if_eq ContestHall_EventScript_CheckPlayerWon
	return

ContestHall_EventScript_CheckPlayerWon:: @ 827ABAF
	special GetContestWinnerId
	compare VAR_0x8005, 3
	goto_if_eq ContestHall_EventScript_CheckRankIsMaster
	return

ContestHall_EventScript_CheckRankIsMaster:: @ 827ABBE
	compare VAR_CONTEST_RANK, CONTEST_RANK_MASTER
	goto_if_eq ContestHall_EventScript_DontSkipPrize
	setflag FLAG_TEMP_2
	return

ContestHall_EventScript_DontSkipPrize:: @ 827ABCD
	return

@ This flag is never read
ContestHall_EventScript_SetSketchFlag:: @ 827ABCE
	setflag FLAG_CONTEST_SKETCH_CREATED
	return

ContestHall_EventScript_SetReadyForContestArtist:: @ 827ABD2
	setvar VAR_LILYCOVE_CONTEST_LOBBY_STATE, 1
	return

ContestHall_EventScript_EndLinkContest:: @ 827ABD8
	delay 60
	special GetContestPlayerId
	special GetContestWinnerId
	special ShouldReadyContestArtist
	compare VAR_0x8004, TRUE
	goto_if_eq ContestHall_EventScript_SetReadyForLinkContestArtist
	closemessage
	return

ContestHall_EventScript_SetReadyForLinkContestArtist:: @ 827ABF1
	setvar VAR_LILYCOVE_CONTEST_LOBBY_STATE, 2
	return

@ Unused
ContestHall_EventScript_Ret:: @ 827ABF7
	return

ContestHall_EventScript_WinnerApproachForPrize:: @ 827ABF8
	switch VAR_0x8005
	case 0, ContestHall_EventScript_Player1ApproachForPrize
	case 1, ContestHall_EventScript_Player2ApproachForPrize
	case 2, ContestHall_EventScript_Player3ApproachForPrize
	case 3, ContestHall_EventScript_Player4ApproachForPrize
	return

ContestHall_EventScript_Player1ApproachForPrize:: @ 827AC2A
	lockall
	applymovement VAR_TEMP_3, ContestHall_Movement_Player1ApproachForPrize
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_Player2ApproachForPrize:: @ 827AC37
	lockall
	applymovement VAR_TEMP_3, ContestHall_Movement_Player2ApproachForPrize
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_Player3ApproachForPrize:: @ 827AC44
	lockall
	applymovement VAR_TEMP_3, ContestHall_Movement_Player3ApproachForPrize
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_Player4ApproachForPrize:: @ 827AC51
	lockall
	applymovement VAR_TEMP_3, ContestHall_Movement_Player4ApproachForPrize
	waitmovement 0
	releaseall
	return

@ In NPC Contests, the player is always entry 4 (id number 3)
ContestHall_EventScript_GivePrizeIfWinner:: @ 827AC5E
	special GetContestWinnerId
	compare VAR_0x8005, 3
	goto_if_eq ContestHall_EventScript_GiveContestPrizes
	lockall
	msgbox ContestHall_Text_CongratsPleaseCompeteAgain, MSGBOX_DEFAULT
	releaseall
	return

ContestHall_EventScript_GiveContestPrizes:: @ 827AC77
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_NPC_SUPER
	call_if_eq ContestHall_EventScript_SetSketchFlag
	specialvar VAR_RESULT, HasMonWonThisContestBefore
	compare VAR_RESULT, FALSE
	goto_if_eq ContestHall_EventScript_ReceiveContestRibbon
	compare VAR_CONTEST_RANK, CONTEST_RANK_MASTER
	goto_if_eq ContestHall_EventScript_GiveLuxuryBall
	lockall
	msgbox ContestHall_Text_CongratsPleaseCompeteAgain, MSGBOX_DEFAULT
	releaseall
	return

ContestHall_EventScript_NoRoomForLuxuryBall:: @ 827ACA8
	lockall
	call Common_EventScript_BagIsFull
	msgbox ContestHall_Text_PickUpPrizeAtCounterLater, MSGBOX_DEFAULT
	releaseall
	setvar VAR_CONTEST_PRIZE_PICKUP, 4
	return

ContestHall_EventScript_GiveLuxuryBall:: @ 827ACBD
	giveitem ITEM_LUXURY_BALL
	compare VAR_RESULT, FALSE
	goto_if_eq ContestHall_EventScript_NoRoomForLuxuryBall
	lockall
	msgbox ContestHall_Text_CongratsPleaseCompeteAgain, MSGBOX_DEFAULT
	releaseall
	return

ContestHall_EventScript_ReceiveContestRibbon:: @ 827ACDF
	special GiveMonContestRibbon
	incrementgamestat GAME_STAT_RECEIVED_RIBBONS
	setflag FLAG_SYS_RIBBON_GET
	lockall
	msgbox ContestHall_Text_ConferRibbonAsPrize, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	msgbox ContestHall_Text_ReceivedRibbon, MSGBOX_DEFAULT
	waitfanfare
	special BufferContestWinnerMonName
	msgbox ContestHall_Text_PutRibbonOnMon, MSGBOX_DEFAULT
	releaseall
	return

ContestHall_Movement_MCWalkDown: @ 827AD09
	walk_down
	step_end

ContestHall_Movement_MCBackUp: @ 827AD0B
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

ContestHall_Movement_MCFaceJudge: @ 827AD0F
	walk_in_place_fastest_right
	step_end

ContestHall_Movement_Heart: @ 827AD11
	emote_heart
	step_end

ContestHall_Movement_FaceContestants: @ 827AD13
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_WalkStageLeft: @ 827AD15
	walk_left
	walk_left
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_WalkStageRight: @ 827AD19
	walk_right
	walk_right
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_WinningPlayerWalkUp: @ 827AD1D
	walk_up
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_ContestantDelay32: @ 827AD20
	delay_16
	delay_16
	step_end

ContestHall_Movement_MCFaceJudge2: @ 827AD23
	walk_in_place_fastest_right
	step_end

ContestHall_Movement_JudgeFaceMC: @ 827AD25
	walk_in_place_fastest_left
	step_end

ContestHall_Movement_FaceContestants2: @ 827AD27
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_Player3ApproachForPrize: @ 827AD29
	walk_left
	walk_left
	walk_up
	step_end

ContestHall_Movement_Player4ApproachForPrize: @ 827AD2D
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

ContestHall_Movement_AudienceMemberLookLeft: @ 827AD33
	face_left
	delay_16
	face_original_direction
	step_end

ContestHall_Movement_AudienceMemberLookUp: @ 827AD37
	face_up
	delay_16
	face_original_direction
	step_end

ContestHall_Movement_AudienceMemberLookRight: @ 827AD3B
	face_right
	delay_16
	face_original_direction
	step_end

ContestHall_Movement_AudienceMemberLookDown: @ 827AD3F
	face_down
	delay_16
	face_original_direction
	step_end

ContestHall_Movement_Player4FaceUp: @ 827AD43
	face_up
	step_end

ContestHall_Movement_MCLookAtJudge: @ 827AD45
	face_up
	delay_16
	walk_in_place_fastest_right
	step_end

ContestHall_Movement_JudgeLookAtMC: @ 827AD49
	walk_in_place_fastest_left
	delay_16
	delay_16
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_MCWalkInPlaceDown: @ 827AD4E
	delay_16
	delay_16
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_Player1WalkToCenter: @ 827AD52
	walk_up
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player1WalkBack: @ 827AD58
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player2WalkToCenter: @ 827AD5E
	walk_up
	walk_right
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player2WalkBack: @ 827AD62
	walk_fast_left
	walk_fast_down
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player3WalkToCenter: @ 827AD66
	walk_up
	walk_left
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player3WalkBack: @ 827AD6A
	walk_fast_right
	walk_fast_down
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player4WalkToCenter: @ 827AD6E
	walk_up
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player4WalkBack: @ 827AD74
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player1ApproachForPrize: @ 827AD7A
	walk_right
	walk_right
	walk_up
	step_end

ContestHall_Movement_Player2ApproachForPrize: @ 827AD7E
	walk_up
	step_end

@ IsContestWithRSPlayer has no side effect, so this is nop
ContestHall_EventScript_CheckIfContestWithRSPlayer:: @ 827AD80
	specialvar VAR_RESULT, IsContestWithRSPlayer
	compare VAR_RESULT, TRUE
	goto_if_eq ContestHall_EventScript_RetRSPlayer
	return

ContestHall_EventScript_RetRSPlayer:: @ 827AD91
	return

LilycoveCity_ContestLobby_EventScript_DelayIfContestWithRSPlayer:: @ 827AD92
	specialvar VAR_RESULT, IsContestWithRSPlayer
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_ContestLobby_EventScript_DelayForRSPlayer
	return

LilycoveCity_ContestLobby_EventScript_DelayForRSPlayer:: @ 827ADA3
	delay 9
	return

LilycoveCity_ContestLobby_Text_ReceptionDontHavePokeblockCase: @ 827ADA7
	.string "안녕하세요!\p"
	.string "여기에서는 포켓몬 콘테스트의\n"
	.string "접수를 받고...\p"
	.string "어라?\p"
	.string "손님은 아직 포켓몬스넥케이스를\n"
	.string "가지고 있지 않으시군요\p"
	.string "그럼 이걸 드리겠습니다!$"
	// こんにちは!ｐ
	// こちらでは ポケモンコンテストｎ
	// うけつけを おこなって……ｌ
	// ……あら?ｐ
	// おきゃくさまは まだ ポロックケ-スをｎ
	// もっていらっしゃらない ようですねｐ
	// では こちらを さしあげましょう!

LilycoveCity_ContestLobby_Text_NowThatWeveClearedThatUp: @ 827AE47
	.string "그러면 다시 한번...\p"
	.string "안녕하세요!\p"
	.string "여기에서는 포켓몬 콘테스트의\n"
	.string "접수를 받고 있습니다!$"
	// というわけで あらためまして……ｐ
	// こんにちは!ｐ
	// こちらでは ポケモンコンテストｎ
	// うけつけを おこなって います!

LilycoveCity_ContestLobby_Text_ContestReception: @ 827AEA8
	.string "안녕하세요!\p"
	.string "여기에서는 포켓몬 콘테스트의\n"
	.string "접수를 받고 있습니다!$"
	// こんにちは!ｐ
	// こちらでは ポケモンコンテストｎ
	// うけつけを おこなって います!

@ Unused
LilycoveCity_ContestLobby_Text_CounterOnlyFor4PlayerContests: @ 827AEE3
	.string "안녕하세요!\p"
	.string "여기에서는 포켓몬 콘테스트\n"
	.string "4인 전용 접수를 받고 있습니다!$"
	// こんにちはｐ
	// こちらは ポケモンコンテストのｎ
	// 4めいさま せんようの うけつけです!

LilycoveCity_ContestLobby_Text_EnterContest1: @ 827AF28
	.string "당신의 포켓몬도\n"
	.string "참가시켜 보겠습니까?$"

LilycoveCity_ContestLobby_Text_WhichTopic1: @ 827AF5E
	.string "어느 설명을 듣겠습니까?$"

LilycoveCity_ContestLobby_Text_ExplainContests: @ 827AF7A
	.string "포켓몬 콘테스트는\n"
	.string "4명의 트레이너가\p"
	.string "포켓몬을 1마리씩 데리고 와서\n"
	.string "총 4마리로 진행됩니다!\p"
	.string "콘테스트는 1차 심사와\n"
	.string "2차 심사가 있습니다!\p"
	.string "1차 심사에서는 회장의\n"
	.string "관객이 맘에 드는\l"
	.string "포켓몬에게 투표합니다!\p"
	.string "2차 심사에서는 포켓몬의 특기인\n"
	.string "기술로 어필합니다!\l"
	.string "심사위원의 주목을 받거나\l"
	.string "관객을 기술로 열광시키거나...\l"
	.string "어쨌든 마구 눈에 띄면 됩니다!\p"
	.string "1차 심사와 2차 심사의 결과로\n"
	.string "종합 포인트를 합산하여\l"
	.string "가장 평가가 높은 포켓몬이\l"
	.string "우승하게 됩니다!$"

LilycoveCity_ContestLobby_Text_ExplainContestTypes: @ 827B17D
	.string "콘테스트는 총 5종류!\n"
	.string "근사함, 아름다움, 귀여움\l"
	.string "슬기로움, 그리고 강인함입니다!\p"
	.string "참가할 포켓몬이 가장\n"
	.string "자신 있어 할 만한 콘테스트를\l"
	.string "선택해 주십시오$"

LilycoveCity_ContestLobby_Text_ExplainContestRanks: @ 827B221
	.string "포켓몬 콘테스트에는\n"
	.string "노말랭크, 슈퍼랭크\p"
	.string "하이퍼랭크, 마스터랭크의\n"
	.string "4개 랭크가 있습니다\p"
	.string "노말랭크에는 모든\n"
	.string "포켓몬이 나갈 수 있습니다\p"
	.string "노말랭크에서 우승한\n"
	.string "포켓몬은 같은 종류의\p"
	.string "슈퍼랭크의 콘테스트에\n"
	.string "나갈 수 있게 됩니다!\p"
	.string "마찬가지로 슈퍼에서\n"
	.string "우승하면 하이퍼에\p"
	.string "하이퍼에서 우승하면\n"
	.string "마스터랭크에 나갈 수 있습니다\p"
	.string "마스터랭크에서 우승한\n"
	.string "포켓몬은 몇 번이고\p"
	.string "마스터랭크의 콘테스트에\n"
	.string "나갈 수 있습니다$"

LilycoveCity_ContestLobby_Text_EnterWhichRank: @ 827B3FF
	.string "어느 랭크에 참가하겠습니까?$"

LilycoveCity_ContestLobby_Text_EnterWhichContest1: @ 827B423
	.string "어느 콘테스트에 참가하겠습니까?$"
	// どの コンテストに さんか しますか?

LilycoveCity_ContestLobby_Text_EnterWhichPokemon1: @ 827B44A
	.string "어느 포켓몬을 참가시키겠습니까?$"

LilycoveCity_ContestLobby_Text_MonNotQualifiedForRank: @ 827B471
	.string "죄송합니다만\n"
	.string "손님의 포켓몬으로는\l"
	.string "이 랭크에는 아직\l"
	.string "참가할 수 없는 듯합니다...$"

LilycoveCity_ContestLobby_Text_EggCannotTakePart: @ 827B4C4
	.string "죄송합니다!\n"
	.string "알은 참가할 수 없습니다...$"

LilycoveCity_ContestLobby_Text_MonInNoConditionForContest: @ 827B501
	.string "그 포켓몬은 건강하지 않은 것\n"
	.string "같으니 참가할 수 없습니다...$"

LilycoveCity_ContestLobby_Text_AlreadyWonEnterAnyway: @ 827B547
	.string "어라 그 리본은...\p"
	.string "손님의 포켓몬은 이미\n"
	.string "이 콘테스트에서 우승한 적이\l"
	.string "있습니다..\p"
	.string "그래도 괜찮겠습니까?$"

LilycoveCity_ContestLobby_Text_ConfirmContestMon: @ 827B5C4
	.string "그 포켓몬으로 하시겠습니까?$"

LilycoveCity_ContestLobby_Text_YourMonIsEntryNum4: @ 827B5E2
	.string "그럼 손님의 포켓몬을\n"
	.string "참가시킵니다!\l"
	.string "참가 번호는\l"
	.string "4번입니다!\l"
	.string "콘테스트가 곧 시작됩니다!$"
	// それでは おきゃくさまの ポケモンをｎ
	// エントリ- します!ｌ
	// おきゃくさまの エントリ-ナンバ-はｌ
	// 4ばん に なります!ｌ
	// コンテストは すぐに はじまります!

LilycoveCity_ContestLobby_Text_ComeThroughHere: @ 827B653
	.string "그럼 이쪽으로 오세요!\n"
	.string "힘내세요!$"

LilycoveCity_ContestLobby_Text_PokemonWonWeHavePrize: @ 827B67B
	.string "콘테스트 우승 축하합니다!\p"
	.string "상품을 받아 주세요!\n"
	.string "자 여기 있습니다!$"

LilycoveCity_ContestLobby_Text_ComeBackForPrizeLater: @ 827B6E7
	.string "그럼 또 다음에\n"
	.string "가지러 와주십시오!$"

ContestHall_Text_GettingStartedParticipantsAsFollows: @ 827B711
	.string "사회자: 네! 이제부터 {STR_VAR_3}랭크\n"
	.string "포켓몬 {STR_VAR_2}를\l"
	.string "시작하겠습니다!\p"
	.string "참가한 트레이너와\n"
	.string "포켓몬들은 모두 이쪽!$"

ContestHall_Text_GettingStartedParticipantsAsFollowsLink: @ 827B78F
	.string "사회자: 네! 이제부터 친구 4인 통신\n"
	.string "포켓몬 {STR_VAR_2}를\l"
	.string "시작하겠습니다!\p"
	.string "참가한 트레이너와\n"
	.string "포켓몬들은 모두 이쪽!$"

ContestHall_Text_EntryXTrainersMon: @ 827B815
	.string "사회자: 참가 번호 {STR_VAR_2}번!\n"
	.string "{STR_VAR_1}님의 {STR_VAR_3}!$"

ContestHall_Text_SeenContestantsAudienceWillVote: @ 827B830
	.string "사회자: 자\n"
	.string "포켓몬의 소개가 끝났습니다\l"
	.string "1차 심사를 시작합니다!\p"
	.string "회장의 관객은\n"
	.string "포켓몬의 인기투표를 해주십시오!\p"
	.string "그럼 바로 시작합시다!\n"
	.string "투표 부탁드립니다!$"

ContestHall_Text_VotingUnderWay: @ 827B8F2
	.string "                      투표 중...$"

ContestHall_Text_VotingCompleteLetsAppeal: @ 827B904
	.string "자!\n"
	.string "투표가 끝났습니다!\l"
	.string "포인트를 집계하는 동안에\l"
	.string "2차 심사를 시작하겠습니다!\p"
	.string "2차 심사는 드디어\n"
	.string "기다리시던 어필타임!\l"
	.string "기술로 마구 어필합시다-!\p"
	.string "그럼 힘내서 갑시다!\n"
	.string "렛츠 어필!$"

ContestHall_Text_ThatsItForJudging: @ 827BA15
	.string "사회자: 거기까지--!!$"

ContestHall_Text_ThankYouForAppeals: @ 827BA30
	.string "여러분들 대단한 어필이었습니다!\n"
	.string "이것으로 모두 종료입니다!\l"
	.string "수고하셨습니다!$"

ContestHall_Text_JudgeLooksReady: @ 827BAAC
	.string "자 그럼 남은 것은\n"
	.string "두근거리는 결과 발표입니다!\p"
	.string "발표는 심사위원 쪽에서\n"
	.string "이루어집니다!$"

ContestHall_Text_WeWillNowDeclareWinner: @ 827BB25
	.string "심사위원: 그럼 발표하겠습니다!$"

ContestHall_Text_CongratsTrainerXandMon: @ 827BB4C
	.string "사회자: 참가 번호 {STR_VAR_2}번\p"
	.string "{STR_VAR_3}님과 {STR_VAR_1}!\n"
	.string "축하합니다!$"

ContestHall_Text_CongratsPleaseCompeteAgain: @ 827BB7A
	.string "사회자: 축하합니다!\n"
	.string "또 참가해 주세요!$"

ContestHall_Text_AcceptYourPrize: @ 827BBA8
	.string "사회자: 자!\n"
	.string "상품을 받아주세요!$"

ContestHall_Text_ConferRibbonAsPrize: @ 827BBD4
	.string "상품으로\n"
	.string "이 리본을 받아주세요!$"

ContestHall_Text_ReceivedRibbon: @ 827BC00
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "리본을 받았다!$"

ContestHall_Text_PutRibbonOnMon: @ 827BC16
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "리본을\l"
	.string "{STR_VAR_1}에게 달아 줬다!$"

ContestHall_Text_PickUpPrizeAtCounterLater: @ 827BC2F
	.string "그럼 상품은 나중에\n"
	.string "접수처에서 받아 주세요!\l"
	.string "또 참가해 주세요!$"

@ Unused
ContestHall_Text_OnlyRegister4Players: @ 827BC82
	.string "I only register four players for\n"
	.string "POKéMON CONTESTS.\p"
	.string "If three other players link up, all\n"
	.string "four may enter the same CONTEST.\p"
	.string "Would you like to take part?$"

LilycoveCity_ContestLobby_Text_ProgressWillBeSaved: @ 827BD17
	.string "콘테스트에 참가하기 전에\n"
	.string "리포트를 작성하겠습니다$"
	// コンテストに エントリ-する まえにｎ
	// レポ-トを かきます

LilycoveCity_ContestLobby_Text_ParticipateAnotherTime: @ 827BD4F
	.string "다음번 참가를 기다리고 있겠습니다!$"
	// またの さんかを おまち してます!

@ Unused
LilycoveCity_ContestLobby_Text_EnterContest2: @ 827BD7A
	.string "Would you like to enter a CONTEST?$"

@ Unused
LilycoveCity_ContestLobby_Text_Explain4PlayerContest: @ 827BD9D
	.string "When four players are ready, connect\n"
	.string "over a Game Link cable, and register\l"
	.string "with me, please.\p"
	.string "Please choose the same CONTEST\n"
	.string "as your fellow contestants.\p"
	.string "The CONTEST begins as soon as all\n"
	.string "players register their entry.\p"
	.string "After that, the usual CONTEST rules\n"
	.string "apply.$"

@ Unused
LilycoveCity_ContestLobby_Text_EnterWhichContest2: @ 827BE9E
	.string "Which CONTEST would you like to enter?$"

@ Unused
LilycoveCity_ContestLobby_Text_EnterWhichPokemon2: @ 827BEC5
	.string "Which POKéMON would you like to enter?$"

LilycoveCity_ContestLobby_Text_Transmitting: @ 827BEEC
	.string "통신하고 있습니다...$"

LilycoveCity_ContestLobby_Text_TransmissionError: @ 827BEFA
	.string "통신에 실패했습니다$"

LilycoveCity_ContestLobby_Text_PlayersChoseDifferentContest: @ 827BF0E
	.string "선택한 콘테스트가\n"
	.string "친구들과 다른 것 같습니다!$"
	// えらんだ コンテストがｎ
	// おともだちと ちがう ようです!

LilycoveCity_ContestLobby_Text_PlayersMadeDifferentChoice: @ 827BF4B
	.string "서로의 선택이\n"
	.string "다른 것 같습니다$"
	// おたがいの せんたくが ちがっているようです

LilycoveCity_ContestLobby_Text_PleaseWaitBButtonCancel: @ 827BF85
	.string "잠시 기다려 주십시오\n"
	.string "...B 버튼으로 취소$"

@ Unused
LilycoveCity_ContestLobby_Text_ParticipateAnotherTime2: @ 827BFA7
	.string "We hope you will participate another\n"
	.string "time.$"

@ Unused
LilycoveCity_ContestLobby_Text_TransmissionErrorTryAgain: @ 827BFD2
	.string "Transmission error.\n"
	.string "Please try again.$"

LilycoveCity_ContestLobby_Text_YourMonIsEntryNumX: @ 827BFF8
	.string "그럼 손님의 포켓몬을\n"
	.string "참가시킵니다!\p"
	.string "손님의 참가 번호는\n"
	.string "{STR_VAR_2}번입니다!$"
	// それでは おきゃくさまの ポケモンをｎ
	// エントリ- します!ｐ
	// おきゃくさまの エントリ-ナンバ-はｎ
	// §うばん に なります!

LilycoveCity_ContestLobby_Text_ContestBeginShortly: @ 827C043
	.string "콘테스트가 곧 시작됩니다!$"
	// コンテストは すぐに はじまります!

LilycoveCity_ContestLobby_Text_LinkContestReception: @ 827C063
	.string "포켓몬 콘테스트\n"
	.string "통신 접수처에 어서 오세요!\p"
	.string "여기에서는 친구들과\n"
	.string "같은 콘테스트에 나갈 수 있습니다$"
	// ポケモン コンテストｎ
	// つうしん うけつけへ ようこそ!ｐ
	// こちらでは ともだちとｎ
	// おなじ コンテストに でられます

LilycoveCity_ContestLobby_Text_WhichTopic2: @ 827C0DA
	.string "어느 설명을 듣겠습니까?$"
	// どの せつめいを ききますか?

LilycoveCity_ContestLobby_Text_EnterContest3: @ 827C0F6
	.string "콘테스트에\n"
	.string "참가하겠습니까?$"
	// コンテストにｎ
	// さんか しますか?

LilycoveCity_ContestLobby_Text_EnterWhichContest3: @ 827C119
	.string "어느 콘테스트에 참가하겠습니까?$"
	// どの コンテストに さんか しますか?

LilycoveCity_ContestLobby_Text_MonInNoCondition2: @ 827C140
	.string "그 포켓몬은 건강하지 않은 것\n"
	.string "같으니 참가할 수 없습니다...$"
	// そちらの ポケモンは げんきがないｎ
	// ようなので しゅつじょう できないです…

LilycoveCity_ContestLobby_Text_EggCannotTakePart2: @ 827C186
	.string "죄송합니다!\n"
	.string "알은 참가할 수 없습니다...$"
	// ごめんなさい!ｎ
	// タマゴは コンテストに でられないんです…

LilycoveCity_ContestLobby_Text_EnterWhichPokemon3: @ 827C1C3
	.string "어느 포켓몬을 참가시키겠습니까?$"
	// どの ポケモンを さんか させますか?

LilycoveCity_ContestLobby_Text_PleaseDecideLinkLeader: @ 827C1EA
	.string "모두와 의논해서 한 명이\n"
	.string "그룹의 리더가 되어 주십시오\p"
	.string "다른 사람은 그룹에 들어간다를\n"
	.string "선택해 주십시오$"
	// みんなで はなしあって ひとりがｎ
	// グル-プリ-ダ-に なってくださいｐ
	// ほかの ひとは グル-プにはいる をｎ
	// えらんでください

LilycoveCity_ContestLobby_Text_PlayerAt4PCounterUseGMode: @ 827C254
	.string "친구 중에서\n"
	.string "4인 전용의 접수처에서\l"
	.string "참가하신 분이 있습니다\p"
	.string "통신케이블을 연결한 친구를\n"
	.string "4명 모아서\l"
	.string "글로벌 모드를 선택한 뒤\l"
	.string "다시 등록해 주십시오$"
	// ともだちの なかにｎ
	// 4にんせんようの うけつけからｌ
	// エントリ-している かたが いますｐ
	// つうしんケ-ブルを つなげた ともだちをｎ
	// 4にん あつめてｌ
	// グロ-バルモ-ドを えらんでｌ
	// とうろくを やりなおして ください

LilycoveCity_ContestLobby_Text_ExplainLinkContest: @ 827C340
	.string "무선어댑터나 통신케이블을\n"
	.string "연결한 친구가 2인 이상\l"
	.string "있으면 할 수 있습니다!\p"
	.string "참가하실 분은\n"
	.string "먼저 참가할 모드를\p"
	.string "선택해 주십시오!\p"
	.string "2인부터 4인까지 자유롭게\n"
	.string "등록할 수 있는 에메랄드 모드와\p"
	.string "4인 전용 접수처에서 참가하는\n"
	.string "친구들과도 함께 등록할 수 있는\l"
	.string "글로벌 모드의\p"
	.string "2종류의 모드가 있으므로\n"
	.string "친구들과 상담해서\l"
	.string "같은 모드를 선택해 주십시오!\p"
	.string "친구들과 같은 모드로\n"
	.string "같은 콘테스트를 선택하면\l"
	.string "참가가 완료됩니다!\p"
	.string "그러면 언제나처럼 콘테스트가\n"
	.string "시작되니 힘내주세요!$"
	// ワイヤレスアダプタか つうしんケ-ブルをｎ
	// つないだ ともだちが 2にん いじょうｌ
	// あつまると おこなえます!ｐ
	// さんかする かたにはｎ
	// まず エントリ-する モ-ドをｌ
	// えらんで いただきます!ｐ
	// 2にん から 4にん まで じゆうにｎ
	// とうろく できる エメラルドモ-ドとｐ
	// 4にんせんようの うけつけから さんかするｎ
	// ともだちとも いっしょに とうろく できるｌ
	// グロ-バルモ-ドとｐ
	// 2しゅるいの モ-ドが ありますのでｎ
	// ともだちと そうだんしてｌ
	// おなじ モ-ドを えらんで くださいね!ｐ
	// ともだちと おなじ モ-ドでｎ
	// おなじ コンテストを えらぶとｌ
	// エントリ- かんりょうと なります!ｐ
	// いつもの とおりに コンテストがｎ
	// はじまりますので がんばって くださいね!

LilycoveCity_ContestLobby_Text_ExplainEMode: @ 827C5B1
	.string "에메랄드 모드에서는\n"
	.string "통신케이블이나 무선어댑터를\l"
	.string "연결한 친구가\l"
	.string "2인 이상 모이면\l"
	.string "통신 콘테스트를 할 수 있습니다!\p"
	.string "4명이 아닐 때는\n"
	.string "회장에 있는 트레이너가\l"
	.string "콘테스트에 참가해 옵니다!\p"
	.string "단 모드를 선택할 수 없는\n"
	.string "4인 전용 접수처에서\l"
	.string "참가하는 친구가 있는 경우엔\l"
	.string "이쪽의 모드로는 할 수 없으니\l"
	.string "주의해 주십시오!$"
	// エメラルドモ-ドではｎ
	// つうしんケ-ブルか ワイヤレスアダプタをｌ
	// つなげた ともだちがｌ
	// 2にん いじょう あつまればｌ
	// つうしんコンテストが おこなえます!ｐ
	// 4にん いない ときはｎ
	// かいじょうに いる トレ-ナ-がｌ
	// コンテストに さんかして くれますよ!ｐ
	// ただし モ-ドを えらぶことが できないｎ
	// 4にんせんようの うけつけからｌ
	// さんかする ともだちが いるばあいはｌ
	// こちらの モ-ドでは できませんのでｌ
	// ごちゅうい ください!

LilycoveCity_ContestLobby_Text_ExplainGMode: @ 827C742
	.string "글로벌 모드에서는\n"
	.string "모드를 선택할 수 없는\l"
	.string "4인 전용 접수처에서\l"
	.string "참가하는 친구와도\l"
	.string "통신 콘테스트를 할 수 있습니다!\p"
	.string "이 모드에서는\n"
	.string "통신케이블을 연결한\l"
	.string "친구가 4인 모이지 않으면\l"
	.string "콘테스트를 할 수 없습니다!$"
	// グロ-バルモ-ドではｎ
	// モ-ドを えらぶことが できないｌ
	// 4にんせんようの うけつけからｌ
	// さんかする ともだち ともｌ
	// つうしんコンテストが おこなえます!ｐ
	// この モ-ドではｎ
	// つうしんケ-ブルを つないだｌ
	// ともだちが 4にん あつまらないとｌ
	// コンテストが おこなえません!

LilycoveCity_ContestLobby_Text_NoWirelessAdapterInGMode: @ 827C879
	.string "죄송합니다!\p"
	.string "무선어댑터로는\n"
	.string "글로벌 모드를 실행할 수 없습니다!\p"
	.string "에메랄드 모드를 선택하거나\n"
	.string "통신케이블을 연결해서\l"
	.string "다시 시도해 주십시오!$"
	// もうしわけ ありません!ｐ
	// ワイヤレスアダプタではｎ
	// グロ-バルモ-ドは おこなえません!ｐ
	// エメラルドモ-ドを えらぶかｎ
	// つうしんケ-ブルを つなげてｌ
	// やりなおして ください!

LilycoveCity_ContestLobby_Text_WhichContestMode: @ 827C8FD
	.string "어느 모드로\n"
	.string "콘테스트에 참가하겠습니까?$"
	// どの モ-ドでｎ
	// コンテストに さんかしますか?

ContestHall_Text_GettingStartedWireless: @ 827C929
	.string "사회자: 네! 이제부터\n"
	.string "친구 4인 통신\l"
	.string "포켓몬 {STR_VAR_2}를\l"
	.string "시작하겠습니다!$"
	// しかい『はい! これよりｎ
	// おともだち 4にん つうしんのｌ
	// ポケモン §うコンテストがｌ
	// はじまります!

ContestHall_Text_ParticipantsAsFollows: @ 827C972
	.string "참가한 트레이너와\n"
	.string "포켓몬들은 모두 이쪽!$"
	// しゅつじょう される トレ-ナ-とｎ
	// ポケモンの みなさんは こちら!

ContestHall_Text_WeveSeenContestants: @ 827C9AF
	.string "사회자: 자\n"
	.string "포켓몬의 소개가 끝났습니다\l"
	.string "1차 심사를 시작합니다!$"
	// しかい『さあｎ
	// ポケモンの しょうかいが おわりましたｌ
	// 1じ しんさに はいりましょう!

ContestHall_Text_AudienceWillVote: @ 827CA04
	.string "회장의 관객은\n"
	.string "포켓몬의 인기투표를 해주십시오!$"
	// かいじょうの おきゃくさまに よるｎ
	// ポケモンの にんき とうひょうです!

ContestHall_Text_LetVotingBegin: @ 827CA42
	.string "그럼 바로 시작합시다!\n"
	.string "투표 부탁드립니다!$"
	// では さっそく はじめましょう!ｎ
	// とうひょう おねがいします!

ContestHall_Text_VotingComplete: @ 827CA71
	.string "자!\n"
	.string "투표가 끝났습니다!\l"
	.string "포인트를 집계하는 동안에\l"
	.string "2차 심사를 시작하겠습니다!$"
	// さあ!ｎ
	// いま とうひょうが おわりました!ｌ
	// しゅうけいを している あいだにｌ
	// 2じ しんさに うつりましょう!

ContestHall_Text_SecondStageOfJudging: @ 827CAD0
	.string "2차 심사는 드디어\n"
	.string "기다리시던 어필타임!\l"
	.string "기술로 마구 어필합시다-!$"
	// 2じ しんさは いよいよｎ
	// おまちかねの アピ-ルタイム!ｌ
	// わざで アピ-ル しまくりましょう-!

ContestHall_Text_LetsAppeal: @ 827CB55
	.string "그럼 힘내서 갑시다!\n"
	.string "렛츠 어필!$"
	// では はりきって どうぞ!ｎ
	// レッツ! アピ-ル
