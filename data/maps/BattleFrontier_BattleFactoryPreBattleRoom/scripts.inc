.set LOCALID_ATTENDANT, 1

BattleFrontier_BattleFactoryPreBattleRoom_MapScripts:: @ 8259ABA
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleFactoryPreBattleRoom_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleFactoryPreBattleRoom_OnWarp
	.byte 0

BattleFrontier_BattleFactoryPreBattleRoom_OnWarp: @ 8259AC5
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_SetUpObjects
	.2byte 0

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_SetUpObjects:: @ 8259ACF
	setvar VAR_TEMP_1, 1
	compare VAR_0x8006, 1
	goto_if_ne BattleFrontier_BattleFactoryPreBattleRoom_EventScript_TurnPlayerNorth
	setobjectxy LOCALID_ATTENDANT, 8, 7
	turnobject LOCALID_ATTENDANT, DIR_SOUTH
BattleFrontier_BattleFactoryPreBattleRoom_EventScript_TurnPlayerNorth:: @ 8259AEA
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleFactoryPreBattleRoom_OnFrame: @ 8259AEF
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_EnterRoom
	.2byte 0

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_EnterRoom:: @ 8259AF9
	compare VAR_0x8006, 1
	goto_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReturnToRoomFromBattle
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleFactoryPreBattleRoom_Movement_AttendantEnterRoom
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleFactoryPreBattleRoom_Movement_PlayerEnterRoom
	waitmovement 0
	compare VAR_0x8006, 2
	goto_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ResumeChallenge
	factory_generaterentalmons
	factory_generateopponentmons
	factory_getopponentmontype
	setorcopyvar VAR_0x8005, VAR_RESULT
	factory_getopponentstyle
	setorcopyvar VAR_0x8006, VAR_RESULT
	call BattleFrontier_BattleFactoryPreBattleRoom_EventScript_CommentOnOpponentType
	call BattleFrontier_BattleFactoryPreBattleRoom_EventScript_CommentOnOpponentStyle
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_HoldMonsChooseFromSelection, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	factory_setswapped
	factory_rentmons
	waitstate
BattleFrontier_BattleFactoryPreBattleRoom_EventScript_EnterBattleRoom:: @ 8259B74
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_RightThisWay, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_EventScript_GetLvlMode
	compare VAR_RESULT, FRONTIER_LVL_50
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_WalkToBattleRoomLv50
	compare VAR_RESULT, FRONTIER_LVL_OPEN
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_WalkToBattleRoomLvOpen
	waitmovement 0
	warp MAP_BATTLE_FRONTIER_BATTLE_FACTORY_BATTLE_ROOM, 255, 6, 11
	waitstate
	end

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReturnToRoomFromBattle:: @ 8259BA5
	factory_setopponentmons
	factory_resethelditems
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LetUsRestoreMons, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	frontier_getbrainstatus
	compare VAR_RESULT, FRONTIER_BRAIN_NOT_READY
	goto_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForRegularOpponent
	playse SE_POKENAV_CALL
	waitse
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_WaitFewMoments, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleFactoryPreBattleRoom_Movement_AttendantMoveToReceiveCall
	waitmovement 0
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_UnderstoodSirWillDo, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleFactoryPreBattleRoom_Movement_AttendantReturnToPlayer
	waitmovement 0
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_MessageFromHeadComeRightNow, MSGBOX_DEFAULT
	closemessage
	delay 16
	goto BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForHead
	end

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForOpponent:: @ 8259C13
	frontier_getbrainstatus
	compare VAR_RESULT, FRONTIER_BRAIN_NOT_READY
	goto_if_ne BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForHead
BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForRegularOpponent:: @ 8259C26
	frontier_get FRONTIER_DATA_BATTLE_NUM
	compare VAR_RESULT, 1
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReadyFor2ndOpponent
	compare VAR_RESULT, 2
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReadyFor3rdOpponent
	compare VAR_RESULT, 3
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReadyFor4thOpponent
	compare VAR_RESULT, 4
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReadyFor5thOpponent
	compare VAR_RESULT, 5
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReadyFor6thOpponent
	compare VAR_RESULT, 6
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReadyFor7thOpponent
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForOpponentNoRecord
	multichoice 19, 4, MULTI_GO_ON_RECORD_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskSwapMon
	case 1, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskRecordBattle
	case 2, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskPauseChallenge
	case 3, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForOpponentNoRecord:: @ 8259CC6
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskSwapMon
	case 1, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskPauseChallenge
	case 2, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskRecordBattle:: @ 8259CFC
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_RecordLatestBattle
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForOpponent
	case 0, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_RecordBattle
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_RecordBattle:: @ 8259D2E
	call BattleFrontier_EventScript_SaveBattle
	goto BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskPauseChallenge:: @ 8259D38
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_SaveAndQuitGame, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForOpponent
	case YES, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_PauseChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskRetireChallenge:: @ 8259D66
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_RetireFromChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForOpponent
	case 0, BattleFrontier_BattleFactoryBattleRoom_EventScript_WarpToLobbyLost
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskSwapMon:: @ 8259D98
	factory_generateopponentmons
	factory_getopponentmontype
	setorcopyvar VAR_0x8005, VAR_RESULT
	factory_getopponentstyle
	setorcopyvar VAR_0x8006, VAR_RESULT
	call BattleFrontier_BattleFactoryPreBattleRoom_EventScript_CommentOnOpponentType
	call BattleFrontier_BattleFactoryPreBattleRoom_EventScript_CommentOnOpponentStyle
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LikeToSwapMon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_EnterBattleRoom
	case YES, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_SwapMons
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_EnterBattleRoom

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_SwapMons:: @ 8259DF2
	fadescreen FADE_TO_BLACK
	factory_swapmons
	waitstate
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_EnterBattleRoom
	factory_setswapped
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_YourSwapIsComplete, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryPreBattleRoom_EventScript_EnterBattleRoom

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReadyFor2ndOpponent:: @ 8259E1D
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor2ndOpponent
	waitmessage
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReadyFor3rdOpponent:: @ 8259E24
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor3rdOpponent
	waitmessage
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReadyFor4thOpponent:: @ 8259E2B
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor4thOpponent
	waitmessage
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReadyFor5thOpponent:: @ 8259E32
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor5thOpponent
	waitmessage
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReadyFor6thOpponent:: @ 8259E39
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor6thOpponent
	waitmessage
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ReadyFor7thOpponent:: @ 8259E40
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor7thOpponent
	waitmessage
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_PauseChallenge:: @ 8259E47
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_SavingDataPleaseWait
	waitmessage
	factory_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_ResumeChallenge:: @ 8259E69
	special SavePlayerParty
	factory_setparties 0
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	special CalculatePlayerPartyCount
	goto BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForOpponent

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_CommentOnOpponentType:: @ 8259E93
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_InvestigatedUpcomingOpponent, MSGBOX_DEFAULT
	compare VAR_0x8005, TYPE_NORMAL
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesNormal
	compare VAR_0x8005, TYPE_FIGHTING
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesFighting
	compare VAR_0x8005, TYPE_FLYING
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesFlying
	compare VAR_0x8005, TYPE_POISON
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesPoison
	compare VAR_0x8005, TYPE_GROUND
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesGround
	compare VAR_0x8005, TYPE_ROCK
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesRock
	compare VAR_0x8005, TYPE_BUG
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesBug
	compare VAR_0x8005, TYPE_GHOST
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesGhost
	compare VAR_0x8005, TYPE_STEEL
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesSteel
	compare VAR_0x8005, TYPE_FIRE
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesFire
	compare VAR_0x8005, TYPE_WATER
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesWater
	compare VAR_0x8005, TYPE_GRASS
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesGrass
	compare VAR_0x8005, TYPE_ELECTRIC
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesElectric
	compare VAR_0x8005, TYPE_PSYCHIC
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesPsychic
	compare VAR_0x8005, TYPE_ICE
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesIce
	compare VAR_0x8005, TYPE_DRAGON
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesDragon
	compare VAR_0x8005, TYPE_DARK
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesDark
	compare VAR_0x8005, NUMBER_OF_MON_TYPES
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentHasNoMostCommonType
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesNormal:: @ 8259F62
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInNormalType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesFighting:: @ 8259F6B
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInFightingType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesFlying:: @ 8259F74
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInFlyingType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesPoison:: @ 8259F7D
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInPoisonType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesGround:: @ 8259F86
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInGroundType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesRock:: @ 8259F8F
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInRockType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesBug:: @ 8259F98
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInBugType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesGhost:: @ 8259FA1
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInGhostType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesSteel:: @ 8259FAA
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInSteelType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesFire:: @ 8259FB3
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInFireType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesWater:: @ 8259FBC
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInWaterType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesGrass:: @ 8259FC5
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInGrassType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesElectric:: @ 8259FCE
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInElectricType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesPsychic:: @ 8259FD7
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInPsychicType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesIce:: @ 8259FE0
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInIceType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesDragon:: @ 8259FE9
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInDragonType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentUsesDark:: @ 8259FF2
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInDarkType, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_OpponentHasNoMostCommonType:: @ 8259FFB
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerHasNoClearFavorite, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_CommentOnOpponentStyle:: @ 825A004
	compare VAR_0x8006, FACTORY_STYLE_NONE
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleUnrestrained
	compare VAR_0x8006, FACTORY_STYLE_PREPARATION
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleTotalPreparation
	compare VAR_0x8006, FACTORY_STYLE_SLOW_STEADY
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleSlowAndSteady
	compare VAR_0x8006, FACTORY_STYLE_ENDURANCE
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleEndurance
	compare VAR_0x8006, FACTORY_STYLE_HIGH_RISK
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleHighRisk
	compare VAR_0x8006, FACTORY_STYLE_WEAKENING
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleWeakenFoe
	compare VAR_0x8006, FACTORY_STYLE_UNPREDICTABLE
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleImpossibleToPredict
	compare VAR_0x8006, FACTORY_STYLE_WEATHER
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleDependsOnFlow
	compare VAR_0x8006, FACTORY_NUM_STYLES
	call_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleFlexible
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleUnrestrained:: @ 825A068
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleUnrestrained, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleTotalPreparation:: @ 825A071
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleTotalPreparation, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleSlowAndSteady:: @ 825A07A
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleSlowAndSteady, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleEndurance:: @ 825A083
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleEndurance, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleHighRisk:: @ 825A08C
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleHighRisk, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleWeakenFoe:: @ 825A095
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleWeakenFoe, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleImpossibleToPredict:: @ 825A09E
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleImpossibleToPredict, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleDependsOnFlow:: @ 825A0A7
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleDependsOnFlow, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_StyleFlexible:: @ 825A0B0
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleFlexible, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForHead:: @ 825A0B9
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_PreparedToFaceHead
	waitmessage
	call BattleFrontier_EventScript_GetCantRecordBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForHeadNoRecord
	multichoice 19, 4, MULTI_GO_ON_RECORD_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskSwapBeforeHead
	case 1, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskRecordBattle
	case 2, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskPauseChallenge
	case 3, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForHead

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForHeadNoRecord:: @ 825A110
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskSwapBeforeHead
	case 1, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskPauseChallenge
	case 2, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskReadyForHead

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_AskSwapBeforeHead:: @ 825A146
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_CantTellAnythingAboutHead, MSGBOX_DEFAULT
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LikeToSwapMon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_EnterBattleRoom
	case YES, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_SwapMons
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryPreBattleRoom_EventScript_EnterBattleRoom

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_WalkToBattleRoomLv50:: @ 825A17C
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleFactoryPreBattleRoom_Movement_GuideWalkToBattleRoomLv50
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleFactoryPreBattleRoom_Movement_PlayerWalkToBattleRoomLv50
	return

BattleFrontier_BattleFactoryPreBattleRoom_EventScript_WalkToBattleRoomLvOpen:: @ 825A18B
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleFactoryPreBattleRoom_Movement_GuideWalkToBattleRoomLvOpen
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleFactoryPreBattleRoom_Movement_PlayerWalkToBattleRoomLvOpen
	return

BattleFrontier_BattleFactoryPreBattleRoom_Movement_PlayerEnterRoom: @ 825A19A
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleFactoryPreBattleRoom_Movement_PlayerWalkToBattleRoomLv50: @ 825A1A0
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

BattleFrontier_BattleFactoryPreBattleRoom_Movement_PlayerWalkToBattleRoomLvOpen: @ 825A1A6
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

BattleFrontier_BattleFactoryPreBattleRoom_Movement_AttendantEnterRoom: @ 825A1AC
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_down
	step_end

BattleFrontier_BattleFactoryPreBattleRoom_Movement_GuideWalkToBattleRoomLv50: @ 825A1B3
	walk_left
	walk_left
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleFactoryPreBattleRoom_Movement_GuideWalkToBattleRoomLvOpen: @ 825A1B9
	walk_right
	walk_right
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleFactoryPreBattleRoom_Movement_AttendantMoveToReceiveCall: @ 825A1BF
	walk_left
	walk_left
	walk_left
	step_end

BattleFrontier_BattleFactoryPreBattleRoom_Movement_AttendantReturnToPlayer: @ 825A1C3
	walk_right
	walk_right
	walk_right
	face_down
	step_end

BattleFrontier_BattleFactoryPreBattleRoom_Text_HoldMonsChooseFromSelection: @ 825A1C8
	.string "그럼 먼저 손님의\n"
	.string "포켓몬을 맡고\l"
	.string "포켓몬 대여를 실시합니다!\l"
	.string "잘 생각하고 선택해 주세요!!$"
	// では まず おきゃくさまのｎ
	// ポケモンを おあずかりしてｌ
	// ポケモンレンタルを おこないます!ｌ
	// よ-く かんがえて えらんで くださいよ!!

BattleFrontier_BattleFactoryPreBattleRoom_Text_LetUsRestoreMons: @ 825A22D
	.string "수고하셨습니다!\n"
	.string "포켓몬을 회복시켜 드리겠습니다!$"
	// おつかれさま です!ｎ
	// ポケモンを かいふく しましょう!

BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor2ndOpponent: @ 825A263
	.string "다음은 2차전입니다!\n"
	.string "준비되셨습니까?$"
	// つぎは 2せんめ ですよ!ｎ
	// じゅんびは よろしい ですか?

BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor3rdOpponent: @ 825A289
	.string "다음은 3차전입니다!\n"
	.string "준비되셨습니까?$"
	// つぎは 3せんめ ですよ!ｎ
	// じゅんびは よろしい ですか?

BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor4thOpponent: @ 825A2AF
	.string "다음은 4차전입니다!\n"
	.string "준비되셨습니까?$"
	// つぎは 4せんめ ですよ!ｎ
	// じゅんびは よろしい ですか?

BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor5thOpponent: @ 825A2D5
	.string "다음은 5차전입니다!\n"
	.string "준비되셨습니까?$"
	// つぎは 5せんめ ですよ!ｎ
	// じゅんびは よろしい ですか?

BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor6thOpponent: @ 825A2FB
	.string "다음은 6차전입니다!\n"
	.string "준비되셨습니까?$"
	// つぎは 6せんめ ですよ!ｎ
	// じゅんびは よろしい ですか?

BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor7thOpponent: @ 825A321
	.string "다음은 7차전입니다!\n"
	.string "준비되셨습니까?$"
	// いよいよ 7せんめ ですよ!ｎ
	// じゅんびは よろしい ですか?

BattleFrontier_BattleFactoryPreBattleRoom_Text_SaveAndQuitGame: @ 825A350
	.string "리포트를 쓰고\n"
	.string "종료하겠습니까?$"
	// レポ-トを かいてｎ
	// しゅうりょう なさいますか?

BattleFrontier_BattleFactoryPreBattleRoom_Text_RetireFromChallenge: @ 825A37A
	.string "배틀트레이드 도전을\n"
	.string "중지하겠습니까?$"
	// バトルトレ-ドの ちょうせんをｎ
	// ちゅうし されますか?

BattleFrontier_BattleFactoryPreBattleRoom_Text_InvestigatedUpcomingOpponent: @ 825A3B4
	.string "자 자!\n"
	.string "이번 대전 상대 말입니다만\l"
	.string "저의 조사로는...$"
	// さあさあ!ｎ
	// こんかいの たいせんあいて ですがｌ
	// わたしの ちょうさ では……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInNormalType: @ 825A3F8
	.string "아무래도 노말타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら ノ-マルタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInFireType: @ 825A43E
	.string "아무래도 불꽃타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら ほのおタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInWaterType: @ 825A482
	.string "아무래도 물타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら みずタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInElectricType: @ 825A4C7
	.string "아무래도 전기타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら でんきタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInGrassType: @ 825A50F
	.string "아무래도 풀타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら くさタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInIceType: @ 825A554
	.string "아무래도 얼음타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら こおりタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInFightingType: @ 825A597
	.string "아무래도 격투타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら かくとうタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInPoisonType: @ 825A5DF
	.string "아무래도 독타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら どくタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInGroundType: @ 825A625
	.string "아무래도 땅타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら じめんタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInFlyingType: @ 825A66B
	.string "아무래도 비행타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら ひこうタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInPsychicType: @ 825A6B1
	.string "아무래도 에스퍼타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら エスパ-タイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInBugType: @ 825A6F8
	.string "아무래도 벌레타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら むしタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInRockType: @ 825A73B
	.string "아무래도 바위타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら いわタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInGhostType: @ 825A77F
	.string "아무래도 고스트타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら ゴ-ストタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInDragonType: @ 825A7C4
	.string "아무래도 드래곤타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら ドラゴンタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInDarkType: @ 825A80A
	.string "아무래도 악타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら あくタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerSkilledInSteelType: @ 825A84E
	.string "아무래도 강철타입을\n"
	.string "가장 잘 다루는 듯합니다$"
	// どうやら はがねタイプをｎ
	// とくいと して いて……

BattleFrontier_BattleFactoryPreBattleRoom_Text_TrainerHasNoClearFavorite: @ 825A893
	.string "아무래도 포켓몬의 타입에는\n"
	.string "구애를 받지 않는 듯합니다$"
	// どうやら ポケモンの タイプにはｎ
	// とくに こだわりが ないようで……

BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleSlowAndSteady: @ 825A8D9
	.string "“차분하고 천천히” 배틀을\n"
	.string "하는 성격인 것 같습니다$"
	// 『じっくり じわじわ』とした バトルをｎ
	// こころがけている ようですよ!

BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleEndurance: @ 825A912
	.string "“지금부터 시작이야!” 배틀을\n"
	.string "하는 성격인 것 같습니다$"
	// 『まだまだ これから!』な バトルをｎ
	// こころがけている ようですよ!

BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleHighRisk: @ 825A94C
	.string "“운에 맡기고 단판 승부” 배틀을\n"
	.string "하는 성격인 것 같습니다$"
	// 『けんこん いってき』の バトルをｎ
	// こころがけている ようですよ!

BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleDependsOnFlow: @ 825A98C
	.string "“되는 대로” 배틀을\n"
	.string "하는 성격인 것 같습니다$"
	// 『くもゆき しだい』の バトルをｎ
	// こころがけている かたの ようですよ!

BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleTotalPreparation: @ 825A9CE
	.string "“준비가 완벽”한 배틀을\n"
	.string "하는 성격인 것 같습니다$"
	// 『じゅんび ばんたん』の バトルをｎ
	// こころがけている ようですよ!

BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleWeakenFoe: @ 825AA16
	.string "“우선은 약하게 하는” 배틀을\n"
	.string "하는 성격인 것 같습니다$"
	// 『まずは よわらせて…』という バトルをｎ
	// こころがけている ようですよ!

BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleFlexible: @ 825AA5A
	.string "“임기응변” 배틀을\n"
	.string "하는 성격인 것 같습니다$"
	// 『りんきおうへん』な バトルをｎ
	// こころがけている ようですよ!

BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleImpossibleToPredict: @ 825AAA7
	.string "“예측 불가능”한 배틀을\n"
	.string "하는 성격인 것 같습니다$"
	// 『よそく ふかのう』な バトルをｎ
	// こころがけている ようですよ!

BattleFrontier_BattleFactoryPreBattleRoom_Text_StyleUnrestrained: @ 825AAE6
	.string "“자유분방”한 배틀을\n"
	.string "하는 성격인 것 같습니다$"
	// 『じゆう ほんぽう』な バトルをｎ
	// こころがけている ようですよ!

BattleFrontier_BattleFactoryPreBattleRoom_Text_LikeToSwapMon: @ 825AB2E
	.string "그럼 배틀을 시작하기 전에\n"
	.string "포켓몬 교환을 하겠습니까?$"
	// では バトルを はじめる まえにｎ
	// ポケモンの こうかんを おこないますか?

BattleFrontier_BattleFactoryPreBattleRoom_Text_YourSwapIsComplete: @ 825AB6C
	.string "수고하셨습니다!\n"
	.string "포켓몬 교환이 끝났습니다!$"
	// おつかれさまです!ｎ
	// ポケモンこうかん かんりょう ですね!

BattleFrontier_BattleFactoryPreBattleRoom_Text_RightThisWay: @ 825AB96
	.string "그럼 안으로 들어오세요!$"
	// それでは おくに どうぞ!

BattleFrontier_BattleFactoryPreBattleRoom_Text_SavingDataPleaseWait: @ 825ABAE
	.string "리포트를 작성하고 있습니다\n"
	.string "잠시 기다려 주십시오$"
	// ただいま レポ-トを かいて います……ｎ
	// しょうしょう おまちください

BattleFrontier_BattleFactoryPreBattleRoom_Text_RecordLatestBattle: @ 825ABD2
	.string "지금의 승부를\n"
	.string "프런티어패스에 기록하겠습니까?$"
	// さきほどの たたかいをｎ
	// フロンティアパスに きろく しますか?

BattleFrontier_BattleFactoryPreBattleRoom_Text_WaitFewMoments: @ 825AC15
	.string "죄송합니다!\n"
	.string "잠시 기다려 주십시오!$"
	// もうしわけ ありません!ｎ
	// しょうしょう おまちください!

BattleFrontier_BattleFactoryPreBattleRoom_Text_UnderstoodSirWillDo: @ 825AC58
	.string "...음 ...? ...네!\n"
	.string "알겠습니다!! 확인했습니다!$"
	// …… えっ …… ? ……ひぃっ!ｎ
	// わっかりましたっ!! りょうかいです!

BattleFrontier_BattleFactoryPreBattleRoom_Text_MessageFromHeadComeRightNow: @ 825AC89
	.string "아하하... 기다리셨습니다!\p"
	.string "이 시설의 소장인\n"
	.string "팩토리책임자께서 연락이\l"
	.string "왔으니 전하겠습니다!\p"
	.string "“좋아! 지금 당장 와라!”\n"
	.string "라고 말하셨습니다!$"
	// やはは…… おまたせ しました!ｐ
	// このしせつの しょちょうで あるｎ
	// ファクトリ-ヘッドからの でんごんがｌ
	// ありますので おつたえ します!ｐ
	// 『やるぞっ! いますぐ こいっ!』ｎ
	// との ことです!

BattleFrontier_BattleFactoryPreBattleRoom_Text_PreparedToFaceHead: @ 825AD20
	.string "팩토리책임자께서 부르십니다!\n"
	.string "각오는 되셨나요?$"
	// ファクトリ-ヘッドが およびです!ｎ
	// かくごは よろしい ですか?

BattleFrontier_BattleFactoryPreBattleRoom_Text_CantTellAnythingAboutHead: @ 825AD61
	.string "죄송합니다만\n"
	.string "팩토리책임자에 대해서는\l"
	.string "정보를 알려드릴 수 없습니다!$"
	// もうしわけ ありませんがｎ
	// ファクトリ-ヘッドに ついてのｌ
	// じょうほうは おおしえ できません!
