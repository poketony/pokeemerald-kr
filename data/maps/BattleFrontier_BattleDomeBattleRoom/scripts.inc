.set LOCALID_ANNOUNCER, 1
.set LOCALID_AUDIENCE_TWIN, 2
.set LOCALID_AUDIENCE_WALKING, 6
.set LOCALID_REFEREE, 9
.set LOCALID_PLAYER, 13
.set LOCALID_OPPONENT, 15

BattleFrontier_BattleDomeBattleRoom_MapScripts:: @ 824BC9C
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleDomeBattleRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleDomeBattleRoom_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleDomeBattleRoom_OnWarp
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleDomeBattleRoom_OnResume
	.byte 0

	.set NO_DRAW,       0
	.set DRAW_TRAINER,  1
	.set DRAW_TUCKER,   2

BattleFrontier_BattleDomeBattleRoom_OnTransition:
	dome_setopponentgfx
	frontier_get FRONTIER_DATA_BATTLE_NUM
	copyvar VAR_TEMP_F, VAR_RESULT
	compare VAR_RESULT, DOME_ROUND1
	call_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_SetWalkingAudienceMemberPos
	call BattleFrontier_BattleDomeBattleRoom_EventScript_SetPlayerGfx
	end

BattleFrontier_BattleDomeBattleRoom_EventScript_SetPlayerGfx::
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_SetPlayerGfxMale
	compare VAR_RESULT, FEMALE
	goto_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_SetPlayerGfxFemale
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_SetPlayerGfxMale::
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_SetPlayerGfxFemale::
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	return

BattleFrontier_BattleDomeBattleRoom_OnFrame:
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattleDomeBattleRoom_EventScript_EnterRoom
	.2byte 0

BattleFrontier_BattleDomeBattleRoom_EventScript_EnterRoom::
	lockall
	call BattleFrontier_BattleDomeBattleRoom_EventScript_GetRoundNum
	compare VAR_RESULT, DOME_ROUND1
	call_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_TryDoAudienceMemberWalkToSeat
	applymovement LOCALID_ANNOUNCER, Common_Movement_WalkInPlaceDown
	waitmovement 0
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayer
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_PlayerHasEnteredDome, MSGBOX_DEFAULT
	closemessage
	showobjectat LOCALID_PLAYER, MAP_BATTLE_FRONTIER_BATTLE_DOME_BATTLE_ROOM
	compare VAR_TEMP_F, DOME_FINAL
	goto_if_ne BattleFrontier_BattleDomeBattleRoom_EventScript_PlayerEnter
	compare VAR_TEMP_E, FRONTIER_BRAIN_NOT_READY
	goto_if_ne BattleFrontier_BattleDomeBattleRoom_EventScript_PlayerEnterForTucker
BattleFrontier_BattleDomeBattleRoom_EventScript_PlayerEnter:: @ 824BD4E
	applymovement LOCALID_PLAYER, BattleFrontier_BattleDomeBattleRoom_Movement_PlayerEnter
	goto BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceReactToPlayer

BattleFrontier_BattleDomeBattleRoom_EventScript_PlayerEnterForTucker:: @ 824BD5A
	applymovement LOCALID_PLAYER, BattleFrontier_BattleDomeBattleRoom_Movement_PlayerEnterForTucker
BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceReactToPlayer:: @ 824BD61
	playse SE_M_ENCORE2
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceLookAround
	waitmovement 0
	compare VAR_TEMP_F, DOME_FINAL
	goto_if_ne BattleFrontier_BattleDomeBattleRoom_EventScript_BattleOpponent
	compare VAR_TEMP_E, FRONTIER_BRAIN_NOT_READY
	goto_if_ne BattleFrontier_BattleDomeBattleRoom_EventScript_AnnounceTucker
BattleFrontier_BattleDomeBattleRoom_EventScript_BattleOpponent::
	dome_getopponentname
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_PlayerVersusTrainer, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_BattleDomeBattleRoom_Movement_PlayerStepForward
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleDomeBattleRoom_Movement_OpponentStepForward
	waitmovement 0
	tower_getopponentintro 0
	msgbox gStringVar4, MSGBOX_DEFAULT
	closemessage
	dome_initopponentparty
	call BattleFrontier_BattleDomeBattleRoom_EventScript_DoDomeBattle
	setvar VAR_TEMP_2, NO_DRAW
	switch VAR_RESULT
	case B_OUTCOME_WON, BattleFrontier_BattleDomeBattleRoom_EventScript_DefeatedOpponent
	case B_OUTCOME_LOST, BattleFrontier_BattleDomeBattleRoom_EventScript_LostToOpponent
	case B_OUTCOME_FORFEITED, BattleFrontier_BattleDomeBattleRoom_EventScript_LostToOpponent
	setvar VAR_TEMP_2, DRAW_TRAINER
BattleFrontier_BattleDomeBattleRoom_EventScript_Draw::
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_RefereeDecisionPleaseWait, MSGBOX_DEFAULT
	closemessage
	playse SE_M_ENCORE2
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceLookAround
	delay 60
	applymovement LOCALID_REFEREE, BattleFrontier_BattleDomeBattleRoom_Movement_RefereeEnter
	waitmovement 0
	applymovement LOCALID_ANNOUNCER, BattleFrontier_BattleDomeBattleRoom_Movement_AnnouncerFaceLeft
	waitmovement 0
	delay 180
	applymovement LOCALID_REFEREE, BattleFrontier_BattleDomeBattleRoom_Movement_RefereeExit
	waitmovement 0
	compare VAR_TEMP_2, DRAW_TUCKER 
	goto_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_LostToOpponent
	dome_compareseeds
	switch VAR_RESULT
	case 1, BattleFrontier_BattleDomeBattleRoom_EventScript_DefeatedOpponent
BattleFrontier_BattleDomeBattleRoom_EventScript_LostToOpponent:: @ 824BE4F
	applymovement LOCALID_ANNOUNCER, Common_Movement_WalkInPlaceDown
	waitmovement 0
	dome_getopponentname
	compare VAR_TEMP_2, NO_DRAW
	call_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_OpponentWon
	compare VAR_TEMP_2, DRAW_TRAINER
	call_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_OpponentWonDraw
	compare VAR_TEMP_2, DRAW_TUCKER
	call_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_TuckerWonDraw
	playse SE_M_ENCORE2
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceLookAround
	delay 60
BattleFrontier_BattleDomeBattleRoom_EventScript_LostTourney::
	dome_resolvewinners DOME_PLAYER_LOST_MATCH
BattleFrontier_BattleDomeBattleRoom_EventScript_WarpToLobbyLost::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	goto BattleFrontier_BattleDomeBattleRoom_EventScript_WarpToLobby

BattleFrontier_BattleDomeBattleRoom_EventScript_OpponentWon::
	frontier_gettrainername 1
	message BattleFrontier_BattleDomeBattleRoom_Text_TrainerIsWinner
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_OpponentWonDraw::
	frontier_gettrainername 0
	message BattleFrontier_BattleDomeBattleRoom_Text_RefereesDecidedWinnerTrainer
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_TuckerWonDraw::
	message BattleFrontier_BattleDomeBattleRoom_Text_RefereesDecidedWinnerTucker
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_DefeatedOpponent:: @ 824BEE0
	applymovement LOCALID_ANNOUNCER, Common_Movement_WalkInPlaceDown
	waitmovement 0
	compare VAR_TEMP_2, NO_DRAW
	call_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_PlayerWon
	compare VAR_TEMP_2, DRAW_TRAINER
	call_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_PlayerWonDraw
	playse SE_M_ENCORE2
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceLookAround
	delay 60
	dome_getroundtext
	dome_resolvewinners DOME_PLAYER_WON_MATCH
	frontier_get FRONTIER_DATA_BATTLE_NUM
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	switch VAR_RESULT
	case DOME_ROUNDS_COUNT, BattleFrontier_BattleDomeBattleRoom_EventScript_WonTourney
	setvar VAR_0x8006, 1
	warp MAP_BATTLE_FRONTIER_BATTLE_DOME_PRE_BATTLE_ROOM, 255, 5, 3
	waitstate

BattleFrontier_BattleDomeBattleRoom_EventScript_WonTourney:: @ 824BF62
	applymovement LOCALID_PLAYER, BattleFrontier_BattleDomeBattleRoom_Movement_PlayerApproachAudience
	waitmovement 0
	frontier_get FRONTIER_DATA_LVL_MODE
	switch VAR_RESULT
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleDomeBattleRoom_EventScript_WonLvOpenTourney
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_PlayerIsLv50Champ, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeBattleRoom_EventScript_CelebrateWin

BattleFrontier_BattleDomeBattleRoom_EventScript_WonLvOpenTourney::
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_PlayerIsLvOpenChamp, MSGBOX_DEFAULT
BattleFrontier_BattleDomeBattleRoom_EventScript_CelebrateWin:: @ 824BF9E
	special DoDomeConfetti
	playse SE_M_ENCORE2
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceLookAround
	delay 60
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_WON
	goto BattleFrontier_BattleDomeBattleRoom_EventScript_WarpToLobby

BattleFrontier_BattleDomeBattleRoom_EventScript_PlayerWon::
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_PlayerIsWinner, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_PlayerWonDraw::
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_RefereesDecidedWinnerPlayer, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayer::
	dome_get DOME_DATA_ATTEMPTED_CHALLENGE
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerFirstAttempt
	dome_get DOME_DATA_HAS_WON_CHALLENGE
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerNeverWon
	dome_get DOME_DATA_WIN_STREAK_ACTIVE
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerBrokenStreak
	goto BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerChampion
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerFirstAttempt::
	call BattleFrontier_BattleDomeBattleRoom_EventScript_GetRoundNum
	switch VAR_RESULT
	case DOME_ROUND1, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerFirstAttemptRound1
	case DOME_ROUND2, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerFirstAttemptRound2
	case DOME_SEMIFINAL, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerFirstAttemptSemifinal
	case DOME_FINAL, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerFirstAttemptFinal
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerFirstAttemptRound1::
	message BattleFrontier_BattleDomeBattleRoom_Text_BrightNewHope
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerFirstAttemptRound2::
	message BattleFrontier_BattleDomeBattleRoom_Text_RisingStar
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerFirstAttemptSemifinal::
	message BattleFrontier_BattleDomeBattleRoom_Text_WillTheyRaceToChampionship
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerFirstAttemptFinal::
	message BattleFrontier_BattleDomeBattleRoom_Text_CanAchieveChampionFirstTry
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerNeverWon::
	call BattleFrontier_BattleDomeBattleRoom_EventScript_GetRoundNum
	switch VAR_RESULT
	case DOME_ROUND1, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerNeverWonRound1
	case DOME_ROUND2, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerNeverWonRound2
	case DOME_SEMIFINAL, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerNeverWonSemifinal
	case DOME_FINAL, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerNeverWonFinal
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerNeverWonRound1::
	message BattleFrontier_BattleDomeBattleRoom_Text_CanLossBeAvenged
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerNeverWonRound2::
	message BattleFrontier_BattleDomeBattleRoom_Text_OnFireForChampionship
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerNeverWonSemifinal::
	message BattleFrontier_BattleDomeBattleRoom_Text_WinHereAdvancesToFinal
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerNeverWonFinal::
	message BattleFrontier_BattleDomeBattleRoom_Text_WillLongHeldDreamComeTrue
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerChampion::
	compare VAR_TEMP_F, DOME_FINAL
	goto_if_ne BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerChampionNoTucker
	switch VAR_TEMP_E
	case FRONTIER_BRAIN_SILVER, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerPreTuckerSilver
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerPreTuckerGold
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerPreTuckerSilver
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerPreTuckerGold
BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerChampionNoTucker::
	call BattleFrontier_BattleDomeBattleRoom_EventScript_GetRoundNum
	switch VAR_RESULT
	case DOME_ROUND1, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerChampionRound1
	case DOME_ROUND2, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerChampionRound2
	case DOME_SEMIFINAL, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerChampionSemifinal
	case DOME_FINAL, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerChampionFinal
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerChampionRound1::
	message BattleFrontier_BattleDomeBattleRoom_Text_TheInvincibleChampion
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerChampionRound2::
	message BattleFrontier_BattleDomeBattleRoom_Text_CanAnyoneHopeToBeatTrainer
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerChampionSemifinal::
	message BattleFrontier_BattleDomeBattleRoom_Text_DoBattlesExistSolelyForTrainer
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerChampionFinal::
	message BattleFrontier_BattleDomeBattleRoom_Text_CurrentChampAimingToRetainTitle
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerPreTuckerSilver::
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_FeelGlowOfTrueMaster, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerPreTuckerGold::
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_CanWinStreakBeStretched, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerBrokenStreak::
	call BattleFrontier_BattleDomeBattleRoom_EventScript_GetRoundNum
	switch VAR_RESULT
	case DOME_ROUND1, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerBrokenStreakRound1
	case DOME_ROUND2, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerBrokenStreakRound2
	case DOME_SEMIFINAL, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerBrokenStreakSemifinal
	case DOME_FINAL, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerBrokenStreakFinal
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerBrokenStreakRound1::
	message BattleFrontier_BattleDomeBattleRoom_Text_FormerChampHasReturned
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerBrokenStreakRound2::
	message BattleFrontier_BattleDomeBattleRoom_Text_FormerToughnessReturned
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerBrokenStreakSemifinal::
	message BattleFrontier_BattleDomeBattleRoom_Text_WillDoExpectedAdvanceToFinals
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnouncePlayerBrokenStreakFinal::
	message BattleFrontier_BattleDomeBattleRoom_Text_WillFormerChampRegainGlory
	waitmessage
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_GetRoundNum::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnounceTucker::
	switch VAR_TEMP_E
	case FRONTIER_BRAIN_SILVER, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnounceTuckerSilver
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnounceTuckerGold
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnounceTuckerSilver
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattleDomeBattleRoom_EventScript_AnnounceTuckerGold

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnounceTuckerSilver::
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_MakeWayForDomeAceTucker, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeBattleRoom_EventScript_TuckerEnter

BattleFrontier_BattleDomeBattleRoom_EventScript_AnnounceTuckerGold::
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_LegendHasReturnedDomeAceTucker, MSGBOX_DEFAULT
BattleFrontier_BattleDomeBattleRoom_EventScript_TuckerEnter::
	closemessage
	applymovement LOCALID_AUDIENCE_TWIN, BattleFrontier_BattleDomeBattleRoom_Movement_AudienceTwinJump
	applymovement LOCALID_ANNOUNCER, BattleFrontier_BattleDomeBattleRoom_Movement_AnnouncerMoveForTuckerEntrance
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleDomeBattleRoom_Movement_TuckerEnterAndDance
	playse SE_M_ENCORE2
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceLookAround
	waitse
	playse SE_M_ENCORE2
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceLookAround
	waitse
	playse SE_M_ENCORE2
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceLookAround
	waitse
	playse SE_M_ENCORE2
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceLookAround
	waitse
	playse SE_M_ENCORE2
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceLookAround
	waitse
	waitmovement 0
	message BattleFrontier_BattleDomeBattleRoom_Text_SpectatorTuckerChant
	waitmessage
	playse SE_M_ENCORE2
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceLookAround
	waitse
	switch VAR_TEMP_E
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattleDomeBattleRoom_EventScript_TuckerGoldIntro
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattleDomeBattleRoom_EventScript_BattleTuckerSilver
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattleDomeBattleRoom_EventScript_BattleTuckerGold
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattleDomeBattleRoom_EventScript_BattleTuckerSilver
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_TuckerSilverIntro, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
BattleFrontier_BattleDomeBattleRoom_EventScript_BattleTuckerSilver::
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_LetsSeeYourStrategy, MSGBOX_DEFAULT
	call BattleFrontier_BattleDomeBattleRoom_EventScript_DoTuckerBattle
	switch VAR_RESULT
	case B_OUTCOME_LOST, BattleFrontier_BattleDomeBattleRoom_EventScript_LostToTucker
	case B_OUTCOME_FORFEITED, BattleFrontier_BattleDomeBattleRoom_EventScript_LostToTucker
	case B_OUTCOME_DREW, BattleFrontier_BattleDomeBattleRoom_EventScript_TuckerDraw
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_IncredibleVictorIsPlayer, MSGBOX_DEFAULT
	dome_resolvewinners DOME_PLAYER_WON_MATCH
	frontier_getsymbols
	compare VAR_RESULT, 0
	goto_if_ne BattleFrontier_BattleDomeBattleRoom_EventScript_WonTourney
	closemessage
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleDomeBattleRoom_Movement_TuckerApproachPlayer
	waitmovement 0
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_SeeYourFrontierPass, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattleDomeBattleRoom_Text_ReceivedTacticsSymbol
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_WontUnderestimateYouNextTime, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeBattleRoom_EventScript_WonTourney

BattleFrontier_BattleDomeBattleRoom_EventScript_TuckerGoldIntro::
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattleDomeBattleRoom_EventScript_BattleTuckerGold
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_TuckerGoldIntro, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
BattleFrontier_BattleDomeBattleRoom_EventScript_BattleTuckerGold::
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_UnleashAllPowerIPossess, MSGBOX_DEFAULT
	call BattleFrontier_BattleDomeBattleRoom_EventScript_DoTuckerBattle
	switch VAR_RESULT
	case B_OUTCOME_LOST, BattleFrontier_BattleDomeBattleRoom_EventScript_LostToTucker
	case B_OUTCOME_FORFEITED, BattleFrontier_BattleDomeBattleRoom_EventScript_LostToTucker
	case B_OUTCOME_DREW, BattleFrontier_BattleDomeBattleRoom_EventScript_TuckerDraw
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_IncredibleVictorIsPlayer, MSGBOX_DEFAULT
	dome_resolvewinners DOME_PLAYER_WON_MATCH
	frontier_getsymbols
	compare VAR_RESULT, 2
	goto_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_WonTourney
	closemessage
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleDomeBattleRoom_Movement_TuckerApproachPlayer
	waitmovement 0
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_NeverLostWhenPowerUnleashed, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattleDomeBattleRoom_Text_TacticsSymbolTookGoldenShine
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_LookForwardToNextEncounter, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeBattleRoom_EventScript_WonTourney

BattleFrontier_BattleDomeBattleRoom_EventScript_DoTuckerBattle::
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_PlayerVersusTucker, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_BattleDomeBattleRoom_Movement_PlayerStepForward2
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleDomeBattleRoom_Movement_TuckerStepForward
	waitmovement 0
	call BattleFrontier_BattleDomeBattleRoom_EventScript_DoDomeBattle
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_LostToTucker::
	msgbox BattleFrontier_BattleDomeBattleRoom_Text_WinnerIsTucker, MSGBOX_DEFAULT
	playse SE_M_ENCORE2
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceLookAround
	waitse
	goto BattleFrontier_BattleDomeBattleRoom_EventScript_LostTourney

BattleFrontier_BattleDomeBattleRoom_EventScript_TuckerDraw::
	setvar VAR_TEMP_2, DRAW_TUCKER
	goto BattleFrontier_BattleDomeBattleRoom_EventScript_Draw

BattleFrontier_BattleDomeBattleRoom_EventScript_DoDomeBattle::
	frontier_set FRONTIER_DATA_RECORD_DISABLED, FALSE
	special HealPlayerParty
	setvar VAR_0x8004, SPECIAL_BATTLE_DOME
	setvar VAR_0x8005, 0
	setvar VAR_TEMP_9, 1
	special DoSpecialTrainerBattle
	waitstate
	setvar VAR_TEMP_9, 0
	dome_restorehelditems
	special HealPlayerParty
	dome_resetsketch
	return

BattleFrontier_BattleDomeBattleRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleDomeBattleRoom_EventScript_SetUpObjects
	.2byte 0

BattleFrontier_BattleDomeBattleRoom_EventScript_SetUpObjects:: @ 824C48B
	hideobjectat LOCALID_PLAYER, MAP_BATTLE_FRONTIER_BATTLE_DOME_BATTLE_ROOM
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AddAudience
	call BattleFrontier_BattleDomeBattleRoom_EventScript_SetPlayerGfx
	setvar VAR_TEMP_1, 1
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleDomeBattleRoom_Movement_SetInvisible
	frontier_get FRONTIER_DATA_BATTLE_NUM
	compare VAR_RESULT, DOME_FINAL
	goto_if_ne BattleFrontier_BattleDomeBattleRoom_EventScript_EndSetUpObjects
	frontier_getbrainstatus
	copyvar VAR_TEMP_E, VAR_RESULT
	compare VAR_RESULT, FRONTIER_BRAIN_NOT_READY
	goto_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_EndSetUpObjects
	call BattleFrontier_EventScript_SetBrainObjectGfx
	setobjectxyperm LOCALID_OPPONENT, 13, 9
	removeobject LOCALID_OPPONENT
	addobject LOCALID_OPPONENT
	applymovement LOCALID_OPPONENT, BattleFrontier_BattleDomeBattleRoom_Movement_SetInvisibleFacingUp
BattleFrontier_BattleDomeBattleRoom_EventScript_EndSetUpObjects:: @ 824C4EF
	end

BattleFrontier_BattleDomeBattleRoom_OnResume:
	compare VAR_TEMP_9, 1
	call_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_CallAddAudience
	end

BattleFrontier_BattleDomeBattleRoom_EventScript_CallAddAudience::
	call BattleFrontier_BattleDomeBattleRoom_EventScript_AddAudience
	return

@ Add audience members to supplement the permanent object event audience
BattleFrontier_BattleDomeBattleRoom_EventScript_AddAudience::
	compare VAR_TEMP_F, DOME_ROUND1
	call_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_AddRound1Audience
	compare VAR_TEMP_F, DOME_ROUND2
	call_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_AddRound2Audience
	compare VAR_TEMP_F, DOME_SEMIFINAL
	call_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_AddSemifinalAudience
	compare VAR_TEMP_F, DOME_FINAL
	call_if_eq BattleFrontier_BattleDomeBattleRoom_EventScript_AddFinalAudience
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AddRound1Audience::
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AddRound2Audience::
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 1, 3, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_EXPERT_F, 4, 6, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_NINJA_BOY, 6, 8, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_LITTLE_GIRL, 9, 11, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 11, 13, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_MAN_5, 13, 15, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_BEAUTY, 19, 7, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_WOMAN_5, 22, 11, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_LITTLE_BOY, 25, 15, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_YOUNGSTER, 26, 2, 2, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_SCHOOL_KID_M, 29, 5, 1, 3, DIR_SOUTH
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AddSemifinalAudience::
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 1, 3, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_EXPERT_F, 4, 6, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_NINJA_BOY, 6, 8, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_WOMAN_2, 7, 9, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_LITTLE_GIRL, 9, 11, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_LASS, 10, 12, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 11, 13, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_MAN_5, 13, 15, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_GENTLEMAN, 15, 2, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_NINJA_BOY, 16, 3, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_WOMAN_2, 17, 4, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_BEAUTY, 19, 7, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_EXPERT_F, 20, 9, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_WOMAN_5, 22, 11, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 23, 13, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_LITTLE_BOY, 25, 15, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_YOUNGSTER, 26, 2, 2, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_HEX_MANIAC, 28, 5, 2, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_SCHOOL_KID_M, 29, 5, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_MART_EMPLOYEE, 30, 6, 2, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_WOMAN_5, 31, 8, 2, 3, 1
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_AddFinalAudience::
	createvobject OBJ_EVENT_GFX_NINJA_BOY, 0, 2, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 1, 3, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_BEAUTY, 2, 15, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_MAN_5, 3, 5, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_EXPERT_F, 4, 6, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 5, 7, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_NINJA_BOY, 6, 8, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_WOMAN_2, 7, 9, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_WOMAN_3, 8, 10, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_LITTLE_GIRL, 9, 11, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_LASS, 10, 12, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 11, 13, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_BEAUTY, 12, 14, 0, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_MAN_5, 13, 15, 2, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_HIKER, 14, 12, 2, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_GENTLEMAN, 15, 2, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_NINJA_BOY, 16, 3, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_WOMAN_2, 17, 4, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_WOMAN_3, 18, 6, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_BEAUTY, 19, 7, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_EXPERT_F, 20, 9, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_MAN_2, 21, 10, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_WOMAN_5, 22, 11, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 23, 13, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_GENTLEMAN, 24, 14, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_LITTLE_BOY, 25, 15, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_YOUNGSTER, 26, 2, 2, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_FAT_MAN, 27, 3, 2, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_HEX_MANIAC, 28, 5, 2, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_SCHOOL_KID_M, 29, 5, 1, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_MART_EMPLOYEE, 30, 6, 2, 3, DIR_SOUTH
	createvobject OBJ_EVENT_GFX_WOMAN_5, 31, 8, 2, 3, DIR_SOUTH
	return

BattleFrontier_BattleDomeBattleRoom_Movement_SetInvisible:
	set_invisible
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_PlayerEnter:
	set_visible
	delay_16
	walk_up
	walk_up
	walk_up
	walk_right
BattleFrontier_BattleDomeBattleRoom_Movement_PlayerStepForward:
	walk_right
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_PlayerApproachAudience:
	walk_up
	step_end

@ Identical to Movement_PlayerEnter
BattleFrontier_BattleDomeBattleRoom_Movement_PlayerEnterForTucker:
	set_visible
	delay_16
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_PlayerStepForward2:
	walk_right
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_OpponentStepForward:
	walk_left
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_SetInvisibleFacingUp:
	face_up
	set_invisible
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_TuckerEnterAndDance:
	set_visible
	walk_up
	walk_up
	walk_up
	face_left
	delay_8
	delay_4
	face_down
	delay_8
	delay_4
	face_right
	delay_8
	delay_4
	face_up
	delay_8
	delay_4
	face_left
	delay_16
	walk_fast_up
	walk_fast_up
	face_left
	delay_8
	delay_4
	face_down
	delay_8
	delay_4
	face_right
	delay_8
	delay_4
	face_up
	delay_8
	delay_4
	face_left
	jump_2_left
	unlock_facing_direction
	face_up
	lock_facing_direction
	jump_2_left
	jump_2_left
	unlock_facing_direction
	face_right
	lock_facing_direction
	jump_2_left
	unlock_facing_direction
	face_down
	delay_2
	face_left
	delay_8
	delay_4
	face_up
	delay_8
	delay_4
	face_right
	delay_8
	delay_4
	face_down
	delay_8
	delay_4
	face_left
	delay_4
	face_up
	delay_4
	face_right
	delay_4
	face_down
	delay_4
	face_left
	delay_2
	face_up
	delay_2
	face_right
	delay_2
	face_down
	delay_2
	face_left
	lock_facing_direction
	walk_right
	walk_slow_right
	walk_right
	walk_slow_right
	unlock_facing_direction
	face_up
	delay_16
	jump_in_place_up
	jump_in_place_up
	delay_16
	walk_right
	walk_right
	walk_right
	jump_in_place_up
	delay_16
	walk_right
	walk_down
	walk_down
	face_left
	delay_2
	face_up
	delay_2
	face_right
	delay_2
	face_down
	delay_2
	face_left
	delay_4
	walk_left
	walk_left
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_AnnouncerMoveForTuckerEntrance: @ 824C7F9
	delay_16
	delay_16
	walk_left
	walk_left
	walk_in_place_fastest_right
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_right
	walk_right
	walk_in_place_fastest_down
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_TuckerStepForward:
	walk_left
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_TuckerApproachPlayer:
	walk_left
	walk_left
	step_end

BattleFrontier_BattleDomeBattleRoom_EventScript_AudienceLookAround::
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
	turnvobject 20, DIR_EAST
	turnvobject 22, DIR_EAST
	turnvobject 24, DIR_EAST
	turnvobject 26, DIR_EAST
	turnvobject 28, DIR_EAST
	turnvobject 30, DIR_EAST
	delay 20
	turnvobject 0, DIR_SOUTH
	turnvobject 2, DIR_SOUTH
	turnvobject 4, DIR_SOUTH
	turnvobject 6, DIR_SOUTH
	turnvobject 8, DIR_SOUTH
	turnvobject 10, DIR_SOUTH
	turnvobject 12, DIR_SOUTH
	turnvobject 14, DIR_SOUTH
	turnvobject 16, DIR_SOUTH
	turnvobject 18, DIR_SOUTH
	turnvobject 20, DIR_SOUTH
	turnvobject 22, DIR_SOUTH
	turnvobject 24, DIR_SOUTH
	turnvobject 26, DIR_SOUTH
	turnvobject 28, DIR_SOUTH
	turnvobject 30, DIR_SOUTH
	delay 20
	turnvobject 1, DIR_EAST
	turnvobject 3, DIR_EAST
	turnvobject 5, DIR_EAST
	turnvobject 7, DIR_EAST
	turnvobject 9, DIR_EAST
	turnvobject 11, DIR_WEST
	turnvobject 13, DIR_WEST
	turnvobject 15, DIR_WEST
	turnvobject 17, DIR_WEST
	turnvobject 19, DIR_WEST
	turnvobject 21, DIR_EAST
	turnvobject 23, DIR_EAST
	turnvobject 25, DIR_EAST
	turnvobject 27, DIR_WEST
	turnvobject 31, DIR_WEST
	delay 20
	turnvobject 1, DIR_SOUTH
	turnvobject 3, DIR_SOUTH
	turnvobject 5, DIR_SOUTH
	turnvobject 7, DIR_SOUTH
	turnvobject 9, DIR_SOUTH
	turnvobject 11, DIR_SOUTH
	turnvobject 13, DIR_SOUTH
	turnvobject 15, DIR_SOUTH
	turnvobject 17, DIR_SOUTH
	turnvobject 19, DIR_SOUTH
	turnvobject 21, DIR_SOUTH
	turnvobject 23, DIR_SOUTH
	turnvobject 25, DIR_SOUTH
	turnvobject 27, DIR_SOUTH
	turnvobject 31, DIR_SOUTH
	delay 20
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_WarpToLobby::
	copyvar VAR_RESULT, VAR_FRONTIER_BATTLE_MODE
	compare VAR_RESULT, FRONTIER_MODE_DOUBLES
	goto_if_eq BattleFrontier_BattleDomePreBattleRoom_EventScript_WarpToLobbyDoubles
	warp MAP_BATTLE_FRONTIER_BATTLE_DOME_LOBBY, 255, 5, 11
	waitstate
	end

BattleFrontier_BattleDomePreBattleRoom_EventScript_WarpToLobbyDoubles::
	warp MAP_BATTLE_FRONTIER_BATTLE_DOME_LOBBY, 255, 17, 11
	waitstate
	end

@ On round 1 there's a 50% chance that a specific audience member will walk to his seat
BattleFrontier_BattleDomeBattleRoom_EventScript_SetWalkingAudienceMemberPos::
	random 2
	copyvar VAR_TEMP_D, VAR_RESULT
	compare VAR_TEMP_D, 0
	goto_if_eq Common_EventScript_NopReturn
	setobjectxyperm LOCALID_AUDIENCE_WALKING, 2, 0
	setobjectmovementtype LOCALID_AUDIENCE_WALKING, MOVEMENT_TYPE_FACE_RIGHT
	return

BattleFrontier_BattleDomeBattleRoom_EventScript_TryDoAudienceMemberWalkToSeat::
	compare VAR_TEMP_D, 0
	goto_if_eq Common_EventScript_NopReturn
	applymovement LOCALID_AUDIENCE_WALKING, BattleFrontier_BattleDomeBattleRoom_Movement_AudienceMemberWalkToSeat
	return

BattleFrontier_BattleDomeBattleRoom_Movement_AudienceTwinJump:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_down
	delay_4
	jump_in_place_down
	enable_jump_landing_ground_effect
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_AudienceMemberWalkToSeat:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_in_place_fastest_down
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_RefereeEnter: @ 824C964
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_AnnouncerFaceLeft: @ 824C969
	walk_in_place_fastest_left
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_RefereeExit: @ 824C96B
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

BattleFrontier_BattleDomeBattleRoom_Text_PlayerHasEnteredDome:
	.string "{PLAYER}의\n"
	.string "입장입니다!$"
	// {PLAYER}さんのｎ
	// にゅうじょう です!$

BattleFrontier_BattleDomeBattleRoom_Text_PlayerVersusTrainer:
	.string "{STR_VAR_1}전!\p"
	.string "{PLAYER} VS\n"
	.string "{STR_VAR_2}\p"
	.string "지금부터 시작하겠습니다!$"
	// {STR_VAR_1}せん!ｐ
	// {PLAYER}さん VSｎ
	// {STR_VAR_2}さんｐ
	// ただいま より はじめます!

BattleFrontier_BattleDomeBattleRoom_Text_PlayerIsWinner:
	.string "{PLAYER}의 승리입니다!\n"
	.string "축하드립니다!$"
	// {PLAYER}さんの かちですｎ
	// おめでとう ございます!

BattleFrontier_BattleDomeBattleRoom_Text_TrainerIsWinner:
	.string "{STR_VAR_2}의 승리입니다!\n"
	.string "축하드립니다!$"
	// {STR_VAR_2}さんの かちですｎ
	// おめでとう ございます!

BattleFrontier_BattleDomeBattleRoom_Text_PlayerIsLv50Champ:
	.string "배틀토너먼트 레벨 50\n"
	.string "우승자는 {PLAYER}입니다!\l"
	.string "축하드립니다!$"
	// バトルト-ナメント レベル50ｎ
	// ゆうしょうは {PLAYER}さん です!ｌ
	// おめでとう ございます!

BattleFrontier_BattleDomeBattleRoom_Text_PlayerIsLvOpenChamp:
	.string "배틀토너먼트 오픈 레벨\n"
	.string "우승자는 {PLAYER}입니다!\l"
	.string "축하드립니다!$"
	// バトルト-ナメント オ-プンレベルｎ
	// ゆうしょうは {PLAYER}さん です!ｌ
	// おめでとう ございます!

BattleFrontier_BattleDomeBattleRoom_Text_RefereeDecisionPleaseWait:
	.string "엄청난 일이 일어났습니다!\p"
	.string "더블 녹아웃의 경우\n"
	.string "배틀토너먼트의 규칙에 의해\l"
	.string "판정됩니다\p"
	.string "잠시 기다려 주십시오...!$"
	// たいへんな ことに なりました!ｐ
	// ダブルノックアウトの ばあいｎ
	// バトルト-ナメントの ル-ルに のっとりｌ
	// はんていと なりますｐ
	// しばらく おまちください……!

BattleFrontier_BattleDomeBattleRoom_Text_RefereesDecidedWinnerTrainer:
	.string "심판으로부터\n"
	.string "판정 결과가 나왔습니다!\p"
	.string "승자는\n"
	.string "바로! 바로! 바로!\l"
	.string "{STR_VAR_1}입니다!\l"
	.string "축하드립니다!$"
	// しんぱんいん よりｎ
	// はんていの けっかが でました!ｐ
	// しょうしゃはｎ
	// なんと! なんと! なんと!ｌ
	// {STR_VAR_1}さん です!ｌ
	// おめでとうございます!

BattleFrontier_BattleDomeBattleRoom_Text_RefereesDecidedWinnerPlayer:
	.string "심판으로부터\n"
	.string "판정 결과가 나왔습니다!\p"
	.string "승자는\n"
	.string "바로! 바로! 바로!\l"
	.string "{PLAYER}입니다!\l"
	.string "축하드립니다!$"
	// しんぱんいん よりｎ
	// はんていの けっかが でました!ｐ
	// しょうしゃはｎ
	// なんと! なんと! なんと!ｌ
	// {PLAYER}さん です!ｌ
	// おめでとうございます!

BattleFrontier_BattleDomeBattleRoom_Text_BrightNewHope:
	.string "기대받는 대형 신인!\p"
	.string "$"
	// きたいの おおがた しんじん!ｐ
	//

BattleFrontier_BattleDomeBattleRoom_Text_RisingStar:
	.string "더 높은 곳을 향해서!\p"
	.string "$"
	// さらなる うえを めざして!ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_WillTheyRaceToChampionship:
	.string "한번에 우승까지\n"
	.string "올라갈 수 있을 것인가!?\p"
	.string "$"
	// いっきに ゆうしょうまでｎ
	// のぼりつめて しまうのでしょうか!?ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_CanAchieveChampionFirstTry:
	.string "첫 출전 첫 우승의\n"
	.string "위업을 달성할 수 있을 것인가!?\p"
	.string "$"
	// はつしゅつじょう はつゆうしょうのｎ
	// いぎょう たっせい なるか!?ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_CanLossBeAvenged:
	.string "지난번의 리벤지를 할 수 있을까!?\p"
	.string "$"
	// ぜんかいの リベンジなるか!?ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_OnFireForChampionship:
	.string "처음으로 우승을 향해서\n"
	.string "불타고 있습니다!\p"
	.string "$"
	// はじめての ゆうしょうへ むけてｎ
	// もえています!ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_WinHereAdvancesToFinal:
	.string "이 시합에서 이기면\n"
	.string "드디어 결승전입니다!\p"
	.string "$"
	// この しあいに かてばｎ
	// いよいよ けっしょうせん です!ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_WillLongHeldDreamComeTrue:
	.string "꿈꾸던 우승은 이루어질 것인가!?\p"
	.string "$"
	// ひがんの はつゆうしょう なるか!?ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_TheInvincibleChampion:
	.string "무적의 챔피언!\p"
	.string "$"
	// むてきの チャンピオン!ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_CanAnyoneHopeToBeatTrainer:
	.string "이 사람을 이길 수 있는 트레이너는\n"
	.string "정말로 있는 걸까요!?\p"
	.string "$"
	// この ひとに かてる トレ-ナ-はｎ
	// はたして いるのでしょうか!?ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_DoBattlesExistSolelyForTrainer:
	.string "이 사람을 위해\n"
	.string "이 대회가 있는 걸까요!?\p"
	.string "$"
	// この ひとの ためにｎ
	// この たいかいは あるのでしょうか!?ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_CurrentChampAimingToRetainTitle:
	.string "과연 연패가 될 것인가!?\p"
	.string "$"
	// はたして れんぱ なるか!?ｐ

BattleFrontier_BattleDomeBattleRoom_Text_FormerChampHasReturned:
	.string "돌아왔습니다!\n"
	.string "$"
	// かえってきました!ｎ
	// もと チャンピオン!ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_FormerToughnessReturned:
	.string "그 강함이 돌아왔다!\p"
	.string "$"
	// あの つよさが もどってきました!ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_WillDoExpectedAdvanceToFinals:
	.string "결승으로 향하는 건\n"
	.string "역시 이 사람인 걸까요!?\p"
	.string "$"
	// けっしょうに すすむのはｎ
	// やっぱり この ひと なんでしょうか!?ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_WillFormerChampRegainGlory:
	.string "멋지게 부활해서 우승을\n"
	.string "거머쥘 것인가!?\p"
	.string "$"
	// みごとに ふっかつ ゆうしょう なるか!?ｐ
	// 

BattleFrontier_BattleDomeBattleRoom_Text_FeelGlowOfTrueMaster:
	.string "왕자의 품격이 느껴진다!$"
	// おうじゃの ふうかく ただよう!
	//

BattleFrontier_BattleDomeBattleRoom_Text_MakeWayForDomeAceTucker:
	.string "그리고... {PLAYER}의\n"
	.string "기록을 막아설 트레이너는...\p"
	.string "그렇다... 그 이름은!!\n"
	.string "배틀돔의 위원이기도 한!!\l"
	.string "우리들의 돔슈퍼스타!!\l"
	.string "하인즈다아------!$"
	// そして…… {PLAYER}さんのｎ
	// きろくを はばむ トレ-ナ-は……ｐ
	// そう…… そのなは!!ｎ
	// バトルド-ムの コミッショナ-に して!!ｌ
	// われらが ド-ムス-パ-スタ-!!ｌ
	// ヒ-ス だぁ------!

BattleFrontier_BattleDomeBattleRoom_Text_SpectatorTuckerChant:
	.string "관객: 하인즈!! 하인즈!!\n"
	.string "하인즈!! 하인즈!! 하인즈!!$"
	// かんきゃく『ヒ-スっ!! ヒ-スっ!!ｎ
	// ヒ-スっ!! ヒ-スっ!! ヒ-スっ!!

BattleFrontier_BattleDomeBattleRoom_Text_TuckerSilverIntro:
	.string "하인즈: 아하하!!\p"
	.string "들려? 이 커다란 함성!\n"
	.string "우리들의 시합을 눈앞에 두고\l"
	.string "모두 들떠 있는 거야!!\p"
	.string "아하하!!\p"
	.string "너는 나와 싸울 생각에\n"
	.string "흥분하고 긴장해서\l"
	.string "바르르 떨고 있구나!!\p"
	.string "하지만 괜찮아!!\p"
	.string "배틀돔의 일등성!!\n"
	.string "돔슈퍼스타 하인즈의 반짝임으로\l"
	.string "너를 비춰줄 테니까!!$"
	// ヒ-ス『アッハッハッ!!ｐ
	// きこえるっ? この だいかんせい!ｎ
	// わたしたちの しあいを まえにｌ
	// みんな ウズウズ してるよっ!!ｐ
	// アッハッハッ!!ｐ
	// キミは わたしと たたかえるｎ
	// こうふんと きんちょうでｌ
	// ピクピク ビクビク してるねっ!!ｐ
	// でも だいじょうぶっ!!ｐ
	// バトルド-ムの いちばんぼしっ!!ｎ
	// ド-ムス-パ-スタ- ヒ-スの かがやきでｌ
	// きみを てらして あげる からっ!!

BattleFrontier_BattleDomeBattleRoom_Text_LetsSeeYourStrategy:
	.string "네 전략! 한번 보여줘!$"
	// キミの せんりゃく! みせて ごらんっ!

BattleFrontier_BattleDomeBattleRoom_Text_IncredibleVictorIsPlayer:
	.string "이럴 수가------! \n"
	.string "배틀에서 이긴 사람은\l"
	.string "{PLAYER}{K_I}다아---!$"
	// なんと---! なんと---っ!ｎ
	// たたかいに かったのはｌ
	// {PLAYER}さんだぁ---!

BattleFrontier_BattleDomeBattleRoom_Text_WinnerIsTucker:
	.string "돔슈퍼스타!!\n"
	.string "하인즈의 승리입니다!\p"
	.string "축하드립니다----! 하인즈!!$"
	// ド-ムス-パ-スタ-!!ｎ
	// ヒ-スの しょうりです!ｐ
	// おめでとう----! ヒ-ス!!

BattleFrontier_BattleDomeBattleRoom_Text_SeeYourFrontierPass:
	.string "하인즈: 규칙은 규칙이니까!\n"
	.string "네 프런티어패스를 빌려줘!$"
	// ヒ-ス『きまり だからねっ!ｎ
	// キミの フロンティアパスを かしてっ!!

BattleFrontier_BattleDomeBattleRoom_Text_ReceivedTacticsSymbol:
	.string "프런티어패스에\n"
	.string "택틱스심볼이 새겨졌다!$"
	// $フロンティアパスにｎ
	// タクティクスシンボルが きざまれた!

BattleFrontier_BattleDomeBattleRoom_Text_WontUnderestimateYouNextTime:
	.string "...... ...... ......\p"
	.string "나는 널 잘못 보고 있었구나\n"
	.string "다음엔 이렇지 않을 거야...$"
	// …… …… ……ｐ
	// わたしは キミを ごかい してたよｎ
	// つぎは こうは いかない からね……

BattleFrontier_BattleDomeBattleRoom_Text_CanWinStreakBeStretched:
	.string "어디까지 이겨 나갈 생각인가?\n"
	.string "관록은 충분!$"
	// どこまで かちつづける つもり なのか?ｎ
	// かんろく じゅうぶん!

BattleFrontier_BattleDomeBattleRoom_Text_LegendHasReturnedDomeAceTucker:
	.string "... 그리고 여러부----운!!\p"
	.string "드디어! 드디어 그 트레이너가\n"
	.string "돌아왔다---!\p"
	.string "그렇다... 그 트레이너의 이름은---\n"
	.string "우리들의 돔슈퍼스타----!!\l"
	.string "하인즈다아------!$"
	// …… そして みなさ----ん!!ｐ
	// ついに! ついに あのトレ-ナ-がｎ
	// かえって きたぞ---!ｐ
	// そう…… その トレ-ナ-の なは---ｎ
	// われらが ド-ムス-パ-スタ----!!ｌ
	// ヒ-ス だぁ------!

BattleFrontier_BattleDomeBattleRoom_Text_TuckerGoldIntro:
	.string "하인즈: 우레와도 같은 함성...\n"
	.string "숨이 막히는 것 같은 열기...\l"
	.string "역시 이곳은 굉장하군...\p"
	.string "... 나는 돔슈퍼스타...\n"
	.string "모두의 기대와 존경을 받는 별...\l"
	.string "흘러 사라질 일은 없어...\p"
	.string "더욱더 빛나고! 더욱더 반짝여서!\n"
	.string "이곳에 찾아오는 모든 사람들을\l"
	.string "비추지 않으면 안된다!!$"
	// ヒ-ス『われるような かんせい……ｎ
	// むせかえる ような ねっき……ｌ
	// やっぱり ここは すばらしいよ……ｐ
	// …… わたしは ド-ムス-パ-スタ-……ｎ
	// みんなの きたいと あこがれの ほし……ｌ
	// ながれ きえさる ことなど できない……ｐ
	// もっと ひかりっ! もっと かがやいてっ!ｎ
	// ここに やってくる すべての ひとびとをｌ
	// てらさなければ いけないっ!!

BattleFrontier_BattleDomeBattleRoom_Text_UnleashAllPowerIPossess:
	.string "자! 내 모든 걸!\n"
	.string "여기에 내보이겠어!!$"
	// さあっ! わたしの すべてっ!ｎ
	// ここに ひろう するよっ!!

BattleFrontier_BattleDomeBattleRoom_Text_NeverLostWhenPowerUnleashed:
	.string "하인즈: 정-말로 멋지군! 너는!!\p"
	.string "모든 걸 쏟아부은 내가\n"
	.string "이길 수 없다니 처음이야!!\p"
	.string "자아! 네 프런티어패스를!!$"
	// ヒ-ス『ほ-んと ステキっ! キミはっ!!ｐ
	// すべてを だしきった わたしがｎ
	// かなわない なんて はじめてっ!!ｐ
	// さあっ! キミの フロンティアパスを!!

BattleFrontier_BattleDomeBattleRoom_Text_TacticsSymbolTookGoldenShine:
	.string "택틱스심볼이\n"
	.string "금색으로 빛났다!$"
	// タクティクスシンボルがｎ
	// きんいろに かがやいた!

BattleFrontier_BattleDomeBattleRoom_Text_LookForwardToNextEncounter:
	.string "강하고! 무엇보다도 귀여워 너!!\n"
	.string "너에게는 나 같은\n"
	.string "슈퍼스타가 될 수 있는\l"
	.string "가능성을 느낄 수 있어!\l"
	.string "다시 만날 때를 기대할게!!$"
	// つよく! なにより かわいい キミっ!!ｐ
	// キミには わたしの ようなｎ
	// ス-パ-スタ-に なれるｌ
	// かのうせいを かんじるよっ!ｌ
	// また あえるときを たのしみに しようっ!!

BattleFrontier_BattleDomeBattleRoom_Text_PlayerIsLv50Champ2:
	.string "배틀토너먼트 레벨 50\n"
	.string "우승은 {PLAYER}!\p"
	.string "축하드립니다!!$"
	// バトルト-ナメント レベル50ｎ
	// ゆうしょうは {PLAYER}さんっ!ｐ
	// おめでとう ございます!!

BattleFrontier_BattleDomeBattleRoom_Text_PlayerIsLvOpenChamp2:
	.string "배틀토너먼트 오픈 레벨\n"
	.string "우승은 {PLAYER}!\p"
	.string "축하드립니다!!$"
	// バトルト-ナメント オ-プンレベルｎ
	// ゆうしょうは {PLAYER}さんっ!ｐ
	// おめでとう ございます!!

BattleFrontier_BattleDomeBattleRoom_Text_PlayerVersusTucker:
	.string "결승전!\p"
	.string "{PLAYER} VS\n"
	.string "돔슈퍼스타 하인즈\p"
	.string "지금부터 시작하겠습니다!$"
	// けっしょうせん!ｐ
	// {PLAYER}さん VSｎ
	// ド-ムス-パ-スタ- ヒ-スｐ
	// ただいま より はじめます!

BattleFrontier_BattleDomeBattleRoom_Text_RefereesDecidedWinnerTucker:
	.string "심판으로부터\n"
	.string "판정 결과가 나왔습니다!\p"
	.string "승자는\n"
	.string "바로! 바로! 바로!\l"
	.string "우리들의 슈퍼스타! 하인즈입니다!\p"
	.string "축하해! 그리고 고마워!!\n"
	.string "우리들의 돔슈퍼스타 하인즈!!$"
	// しんぱんいん よりｎ
	// はんていの けっかが でました!ｐ
	// しょうしゃはｎ
	// なんと! なんと! なんと!ｌ
	// われらの ス-パ-スタ-! ヒ-ス です!ｐ
	// おめでとう! そして ありがとう!!ｎ
	// われらの ド-ムス-パ-スタ- ヒ-ス!!
