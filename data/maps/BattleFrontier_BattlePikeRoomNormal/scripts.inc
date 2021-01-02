@ Objects in this room are set dynamically with OBJ_EVENT_GFX_VAR_0 and OBJ_EVENT_GFX_VAR_1
@ Note: LOCALIDs shared with data/scripts/battle_pike.inc
.equ LOCALID_OBJ_0, 1
.equ LOCALID_OBJ_1, 2

BattleFrontier_BattlePikeRoomNormal_MapScripts:: @ 825D152
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattlePikeRoom_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePikeRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePikeRoomNormal_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePikeRoom_OnWarp
	.byte 0

BattleFrontier_BattlePikeRoomNormal_OnFrame: @ 825D167
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterRoom
	.2byte 0

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterRoom:: @ 825D171
	setvar VAR_TEMP_0, 1
	pike_getroomtype
	switch VAR_RESULT
	case PIKE_ROOM_SINGLE_BATTLE, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterSingleBattleRoom
	case PIKE_ROOM_HEAL_FULL, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterFullHealRoom
	case PIKE_ROOM_STATUS, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterStatusRoom
	case PIKE_ROOM_HARD_BATTLE, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterHardBattleRoom
	case PIKE_ROOM_DOUBLE_BATTLE, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterDoubleBattleRoom
	case PIKE_ROOM_BRAIN, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterBrainRoom
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterSingleBattleRoom:: @ 825D1C6
	lockall
	delay 16
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_ApproachPlayer
	waitmovement 0
	pike_gettrainerintro 0
	msgbox gStringVar4, MSGBOX_DEFAULT
	waitmessage
	closemessage
	releaseall
	setvar VAR_0x8004, SPECIAL_BATTLE_PIKE_SINGLE
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePikeRoomNormal_EventScript_WonSingleBattle
BattleFrontier_BattlePikeRoomNormal_EventScript_WarpToLobbyLost:: @ 825D20A
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	warp MAP_BATTLE_FRONTIER_BATTLE_PIKE_LOBBY, 255, 5, 6
	waitstate
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_WonSingleBattle:: @ 825D226
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_NPCExit
	waitmovement 0
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterHardBattleRoom:: @ 825D231
	lockall
	delay 16
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_BattleSomewhatToughTrainer, MSGBOX_DEFAULT
	waitmessage
	closemessage
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_ApproachPlayer
	waitmovement 0
	pike_gettrainerintro 0
	msgbox gStringVar4, MSGBOX_DEFAULT
	waitmessage
	closemessage
	releaseall
	setvar VAR_0x8004, SPECIAL_BATTLE_PIKE_SINGLE
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePikeRoomNormal_EventScript_WonHardBattle
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_WonHardBattle:: @ 825D285
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_NPCExit
	waitmovement 0
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_HealNPCApproachPlayer
	waitmovement 0
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_RestoreToFullHealth, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_EnjoyRestOfChallenge2, MSGBOX_DEFAULT
	closemessage
	release
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_NPCExit
	waitmovement 0
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterBrainRoom:: @ 825D2BF
	delay 22
	lockall
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_PreQueenHealNPCApproachPlayer
	waitmovement 0
	pike_prequeenheal
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeRoomNormal_EventScript_PreQueenNoHeal
	case 1, BattleFrontier_BattlePikeRoomNormal_EventScript_PreQueenHealOneMon
	case 2, BattleFrontier_BattlePikeRoomNormal_EventScript_PreQueenHealTwoMons

BattleFrontier_BattlePikeRoomNormal_EventScript_LucyEnter:: @ 825D2FB
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ShallFetchOurMaster, MSGBOX_DEFAULT
	closemessage
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleFrontier_BattlePikeRoomNormal_Movement_CameraPanUp
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_HealNPCExitForLucy
	waitmovement 0
	playse SE_PIKE_CURTAIN_CLOSE
	call BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesLittleClosed
	delay 4
	call BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesMostlyClosed
	delay 4
	call BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesClosed
	delay 4
	waitse
	delay 60
	playse SE_PIKE_CURTAIN_OPEN
	delay 65
	call BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesMostlyClosed
	showobjectat LOCALID_OBJ_0, MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_NORMAL
	delay 4
	call BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesLittleClosed
	delay 4
	call BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesOpen
	waitse
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_LucyEnter
	waitmovement 0
	pike_getbrainstatus
	switch VAR_RESULT
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattlePikeRoomNormal_EventScript_IntroLucyGold
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattlePikeRoomNormal_EventScript_BattleLucySilver
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattlePikeRoomNormal_EventScript_BattleLucyGold
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattlePikeRoomNormal_EventScript_BattleLucySilver
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ImThePikeQueen, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
BattleFrontier_BattlePikeRoomNormal_EventScript_BattleLucySilver:: @ 825D3BD
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_HopeYouDidntUseUpLuck, MSGBOX_DEFAULT
	call BattleFrontier_BattlePikeRoomNormal_EventScript_DoPikeQueenBattle
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucySilver
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_WarpToLobbyLost

BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucySilver:: @ 825D3DA
	frontier_getsymbols
	compare VAR_RESULT, 0
	goto_if_ne BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucy
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_LucyShowMeFrontierPass, MSGBOX_DEFAULT
	waitmessage
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattlePikeRoomNormal_Text_ReceivedLuckSymbol
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_AllThereIsDisappear, MSGBOX_DEFAULT
	closemessage
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucy

BattleFrontier_BattlePikeRoomNormal_EventScript_IntroLucyGold:: @ 825D416
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattlePikeRoomNormal_EventScript_BattleLucyGold
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_LucyYouAgain, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
BattleFrontier_BattlePikeRoomNormal_EventScript_BattleLucyGold:: @ 825D443
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_NowComeOn, MSGBOX_DEFAULT
	call BattleFrontier_BattlePikeRoomNormal_EventScript_DoPikeQueenBattle
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucyGold
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_WarpToLobbyLost

BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucyGold:: @ 825D460
	frontier_getsymbols
	compare VAR_RESULT, 2
	goto_if_eq BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucy
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_LucyFrontierPass, MSGBOX_DEFAULT
	waitmessage
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattlePikeRoomNormal_Text_LuckSymbolTookGoldenShine
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_IWontForget, MSGBOX_DEFAULT
	closemessage
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucy
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucy:: @ 825D49D
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_LucyMoveAside
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePikeRoomNormal_Movement_PlayerWalkUp2
	waitmovement 0
	pike_get PIKE_DATA_WIN_STREAK
	addvar VAR_RESULT, 1
	pike_set PIKE_DATA_WIN_STREAK VAR_RESULT
	call BattleFrontier_BattlePikeRoom_EventScript_WarpToFinalRoom
	waitstate
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_PreQueenNoHeal:: @ 825D4DC
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ChoseRoomNoHeal, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_LucyEnter
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_PreQueenHealOneMon:: @ 825D4EA
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ChoseRoomHealOne, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_LucyEnter
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_PreQueenHealTwoMons:: @ 825D4FC
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ChoseRoomHealTwo, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_LucyEnter
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterFullHealRoom:: @ 825D50E
	lockall
	delay 16
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_ApproachPlayer
	waitmovement 0
	message BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreToFullHealth
	waitmessage
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_EnjoyRestOfChallenge, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_NPCExit
	waitmovement 0
	releaseall
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterDoubleBattleRoom:: @ 825D53E
	lockall
	delay 16
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_Trainer1WalkRight
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_Trainer2WalkLeft
	waitmovement 0
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_DoubleTrainersWalkDown
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_DoubleTrainersWalkDown
	waitmovement 0
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_Trainer1FacePlayer
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_Trainer2FacePlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceTrainer1
	waitmovement 0
	pike_gettrainerintro 0
	msgbox gStringVar4, MSGBOX_DEFAULT
	closemessage
	delay 16
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceTrainer2
	waitmovement 0
	pike_gettrainerintro 1
	msgbox gStringVar4, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, SPECIAL_BATTLE_PIKE_DOUBLE
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePikeRoomNormal_EventScript_WonDoubleBattle
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_WonDoubleBattle:: @ 825D5DC
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceTrainer2
	waitmovement 0
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_Trainer1Exit
	waitmovement 0
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_Trainer2Exit
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceUp
	waitmovement 0
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterStatusRoom:: @ 825D605
	lockall
	message BattleFrontier_BattlePikeRoomNormal_Text_WatchOut
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_MonApproachPlayer
	waitmovement 0
	pike_getstatusmon
	copyvar VAR_0x8004, VAR_RESULT
	compare VAR_0x8004, PIKE_STATUSMON_KIRLIA
	call_if_eq BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaAttack
	compare VAR_0x8004, PIKE_STATUSMON_DUSCLOPS
	call_if_eq BattleFrontier_BattlePikeRoomNormal_EventScript_DusclopsAttack
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_AttacksWhenStartled, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaAttack:: @ 825D643
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_KirliaStop, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_KIRLIA, 0
	waitmoncry
	pike_getstatus
	compare VAR_RESULT, PIKE_STATUS_TOXIC
	call_if_eq BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedToxic
	compare VAR_RESULT, PIKE_STATUS_BURN
	call_if_eq BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedWillOWisp
	compare VAR_RESULT, PIKE_STATUS_PARALYSIS
	call_if_eq BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedThunderWave
	compare VAR_RESULT, PIKE_STATUS_SLEEP
	call_if_eq BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedHypnosis
	pike_flashscreen
	waitstate
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_NPCApproachMon
	waitmovement 0
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_MonFaceNPC
	waitmovement 0
	waitse
	playmoncry SPECIES_KIRLIA, 0
	waitmoncry
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ThatsEnough, MSGBOX_DEFAULT
	waitse
	playmoncry SPECIES_KIRLIA, 0
	waitmoncry
	closemessage
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_MonMoveAside
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_StatusNPCApproachPlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ApologizeForKirlia, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_DusclopsAttack:: @ 825D6D5
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_DusclopsStop, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_DUSCLOPS, 0
	waitmoncry
	pike_getstatus
	compare VAR_RESULT, PIKE_STATUS_FREEZE
	call_if_eq BattleFrontier_BattlePikeRoomNormal_EventScript_DusclopsUsedIceBeam
	compare VAR_RESULT, PIKE_STATUS_BURN
	call_if_eq BattleFrontier_BattlePikeRoomNormal_EventScript_DusclopsUsedWillOWisp
	pike_flashscreen
	waitstate
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_NPCApproachMon
	waitmovement 0
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_MonFaceNPC
	waitmovement 0
	waitse
	playmoncry SPECIES_DUSCLOPS, 0
	waitmoncry
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ThatsEnough, MSGBOX_DEFAULT
	waitse
	playmoncry SPECIES_DUSCLOPS, 0
	waitmoncry
	closemessage
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_MonMoveAside
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_StatusNPCApproachPlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ApologizeForDusclops, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedToxic:: @ 825D751
	message BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedToxic
	waitmessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedWillOWisp:: @ 825D758
	message BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedWillOWisp
	waitmessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedThunderWave:: @ 825D75F
	message BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedThunderWave
	waitmessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedHypnosis:: @ 825D766
	message BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedHypnosis
	waitmessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_DusclopsUsedIceBeam:: @ 825D76D
	message BattleFrontier_BattlePikeRoomNormal_Text_DusclopsUsedIceBeam
	waitmessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_DusclopsUsedWillOWisp:: @ 825D774
	message BattleFrontier_BattlePikeRoomNormal_Text_DusclopsUsedWillOWisp
	waitmessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_DoPikeQueenBattle:: @ 825D77B
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePikeRoomNormal_Movement_PlayerWalkUp2
	waitmovement 0
	setvar VAR_0x8004, SPECIAL_BATTLE_PIKE_SINGLE
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	return

BattleFrontier_BattlePikeRoomNormal_Movement_ApproachPlayer: @ 825D795
	walk_down
	walk_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_NPCExit: @ 825D798
	walk_up
	walk_up
	walk_up
	set_invisible
	walk_up
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_HealNPCExit: @ 825D79E
	walk_up
	set_invisible
	walk_up
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_NPCApproachMon: @ 825D7A2
	walk_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_StatusNPCApproachPlayer: @ 825D7A4
	walk_down
	face_left
	delay_16
	delay_16
	face_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_MonApproachPlayer: @ 825D7AA
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_left
	face_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_MonFaceNPC: @ 825D7B1
	face_up
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_MonMoveAside: @ 825D7B3
	walk_left
BattleFrontier_BattlePikeRoomNormal_Movement_MonFaceRight: @ 825D7B4
	face_right
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_HealNPCApproachPlayer: @ 825D7B6
	walk_down
	walk_down
	walk_right
	face_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceTrainer1: @ 825D7BB
	face_left
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceTrainer2: @ 825D7BD
	face_right
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceUp: @ 825D7BF
	face_up
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_Trainer1WalkRight: @ 825D7C1
	walk_right
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_Trainer2WalkLeft: @ 825D7C3
	walk_left
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_DoubleTrainersWalkDown: @ 825D7C5
	walk_down
	walk_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_Trainer1FacePlayer: @ 825D7C8
	face_right
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_Trainer2FacePlayer: @ 825D7CA
	face_left
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_Trainer1Exit: @ 825D7CC
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	set_invisible
	walk_up
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_Trainer2Exit: @ 825D7D4
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	set_invisible
	walk_up
	step_end

@ For approaching Lucy and exiting room after defeating Lucy
BattleFrontier_BattlePikeRoomNormal_Movement_PlayerWalkUp2: @ 825D7DC
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_PreQueenHealNPCApproachPlayer: @ 825D7DF
	walk_down
	walk_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_HealNPCExitForLucy: @ 825D7E2
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_LucyEnter: @ 825D7E7
	set_visible
	walk_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_LucyMoveAside: @ 825D7EA
	walk_left
	face_right
	step_end

BattleFrontier_BattlePikeRoomNormal_EventScript_NPC:: @ 825D7ED
	pike_getroomtype
	switch VAR_RESULT
	case PIKE_ROOM_NPC, BattleFrontier_BattlePikeRoomNormal_EventScript_NormalNPC
	case PIKE_ROOM_STATUS, BattleFrontier_BattlePikeRoomNormal_EventScript_StatusNPC
	case PIKE_ROOM_HEAL_PART, BattleFrontier_BattlePikeRoomNormal_EventScript_HealNPC
BattleFrontier_BattlePikeRoomNormal_EventScript_NormalNPC:: @ 825D81B
	lock
	faceplayer
	pike_getnpcmsg
	msgbox gStringVar4, MSGBOX_DEFAULT
	waitmessage
	closemessage
	release
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_StatusNPC:: @ 825D831
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ApologizeHopeMonsAreFine, MSGBOX_DEFAULT
	closemessage
	release
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_HealNPC:: @ 825D83E
	pike_healonetwomons
	compare VAR_RESULT, 2
	call_if_eq BattleFrontier_BattlePikeRoomNormal_EventScript_WillRestoreTwoMons
	compare VAR_RESULT, 1
	call_if_eq BattleFrontier_BattlePikeRoomNormal_EventScript_WillRestoreOneMon
	playfanfare MUS_HEAL
	waitfanfare
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_BestOfLuckFarewell, MSGBOX_DEFAULT
	closemessage
	release
	applymovement LOCALID_OBJ_0, BattleFrontier_BattlePikeRoomNormal_Movement_HealNPCExit
	waitmovement 0
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_WillRestoreOneMon:: @ 825D875
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreOneMon, MSGBOX_DEFAULT
	closemessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_WillRestoreTwoMons:: @ 825D881
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreTwoMons, MSGBOX_DEFAULT
	closemessage
	return

@ Dusclops or Kirlia
BattleFrontier_BattlePikeRoomNormal_EventScript_StatusMon:: @ 825D88D
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_Silence, MSGBOX_DEFAULT
	closemessage
	release
	applymovement LOCALID_OBJ_1, BattleFrontier_BattlePikeRoomNormal_Movement_MonFaceRight
	waitmovement 0
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesMostlyClosed:: @ 825D8A4
	setmetatile 4, 1, METATILE_BattlePike_Curtain_Stage1_Tile0, 1
	setmetatile 3, 2, METATILE_BattlePike_Curtain_Stage1_Tile1, 1
	setmetatile 4, 2, METATILE_BattlePike_Curtain_Stage1_Tile2, 1
	setmetatile 5, 2, METATILE_BattlePike_Curtain_Stage1_Tile3, 1
	setmetatile 3, 3, METATILE_BattlePike_Curtain_Stage1_Tile4, 1
	setmetatile 4, 3, METATILE_BattlePike_Curtain_Stage1_Tile5, 0
	setmetatile 5, 3, METATILE_BattlePike_Curtain_Stage1_Tile6, 1
	special DrawWholeMapView
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesLittleClosed:: @ 825D8E7
	setmetatile 4, 1, METATILE_BattlePike_Curtain_Stage2_Tile0, 1
	setmetatile 3, 2, METATILE_BattlePike_Curtain_Stage2_Tile1, 1
	setmetatile 4, 2, METATILE_BattlePike_Curtain_Stage2_Tile2, 1
	setmetatile 5, 2, METATILE_BattlePike_Curtain_Stage2_Tile3, 1
	setmetatile 3, 3, METATILE_BattlePike_Curtain_Stage2_Tile4, 1
	setmetatile 4, 3, METATILE_BattlePike_Curtain_Stage2_Tile5, 0
	setmetatile 5, 3, METATILE_BattlePike_Curtain_Stage2_Tile6, 1
	special DrawWholeMapView
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesOpen:: @ 825D92A
	setmetatile 4, 1, METATILE_BattlePike_Curtain_Stage3_Tile0, 1
	setmetatile 3, 2, METATILE_BattlePike_Curtain_Stage3_Tile1, 1
	setmetatile 4, 2, METATILE_BattlePike_Curtain_Stage3_Tile2, 1
	setmetatile 5, 2, METATILE_BattlePike_Curtain_Stage3_Tile3, 1
	setmetatile 3, 3, METATILE_BattlePike_Curtain_Stage3_Tile4, 1
	setmetatile 4, 3, METATILE_BattlePike_Curtain_Stage3_Tile5, 0
	setmetatile 5, 3, METATILE_BattlePike_Curtain_Stage3_Tile6, 1
	special DrawWholeMapView
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesClosed:: @ 825D96D
	setmetatile 4, 1, METATILE_BattlePike_Curtain_Stage0_Tile0, 1
	setmetatile 3, 2, METATILE_BattlePike_Curtain_Stage0_Tile1, 1
	setmetatile 4, 2, METATILE_BattlePike_Curtain_Stage0_Tile2, 1
	setmetatile 5, 2, METATILE_BattlePike_Curtain_Stage0_Tile3, 1
	setmetatile 3, 3, METATILE_BattlePike_Curtain_Stage0_Tile4, 1
	setmetatile 4, 3, METATILE_BattlePike_Curtain_Stage0_Tile5, 0
	setmetatile 5, 3, METATILE_BattlePike_Curtain_Stage0_Tile6, 1
	special DrawWholeMapView
	return

BattleFrontier_BattlePikeRoomNormal_Movement_CameraPanUp: @ 825D9B0
	walk_up
	walk_up
	step_end

@ Unused
BattleFrontier_BattlePikeRoomNormal_Movement_CameraPanDown: @ 825D9B3
	walk_down
	walk_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreToFullHealth: @ 825D9B6
	.string "잘 오셨습니다...\n"
	.string "손님은 운이 좋으시군요...\p"
	.string "포켓몬을 회복시켜 드리겠습니다...$"
	// ようこそ……ｎ
	// おきゃくさまは ラッキ- ですね……ｐ
	// ポケモンを かいふくして さしあげます……

BattleFrontier_BattlePikeRoomNormal_Text_EnjoyRestOfChallenge: @ 825DA13
	.string "그럼 계속해서\n"
	.string "게임을 즐겨 주십시오...$"
	// それでは ひきつづきｎ
	// ゲ-ムを おたのしみ ください……

BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreOneMon: @ 825DA51
	.string "오오 넌 운이 좋구나\p"
	.string "지금 나는 조금\n"
	.string "기분이 좋으니까\p"
	.string "네 포켓몬을 1마리만\n"
	.string "회복시켜 주도록 하지!$"
	// おお きみは ツイてるなｐ
	// いまの わしは ちょっとだけｎ
	// きげんが いいからなｐ
	// きみの ポケモンを 1ひき だけｎ
	// かいふくして あげようじゃ ないか!

BattleFrontier_BattlePikeRoomNormal_Text_BestOfLuckFarewell: @ 825DABE
	.string "그럼 안녕히...$"
	// それでは ごきげんよう……

@ Seems there was a planned room type where the player could choose to battle and would be healed if they won
@ Possibly replaced/superseded by the hard battle room, which is the same but the battle isnt optional
@ Unused
BattleFrontier_BattlePikeRoomNormal_Text_CareForBattleWillRestoreMons: @ 825DAE1
	.string "너...\p"
	.string "나하고 배틀하지 않을래?\n"
	.string "이기면 포켓몬을 회복시켜 줄게$"
	// きみ……ｐ
	// わたしと バトルしないかね?ｎ
	// かてば ポケモンを かいふくして あげよう

@ Unused
BattleFrontier_BattlePikeRoomNormal_Text_NowShallWe: @ 825DB2F
	.string "좋아...\n"
	.string "...그럼 간다!$"
	// よろしい……ｎ
	// ……それでは いくぞ!

@ Unused
BattleFrontier_BattlePikeRoomNormal_Text_HowUnsportingOfYou: @ 825DB49
	.string "그래... 아쉽게 됐네...$"
	// そうか… ざんねんだな……

@ Unused
BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreMonsAsPromised: @ 825DB67
	.string "대단해...\p"
	.string "약속대로 포켓몬을\n"
	.string "회복시켜 줄게...$"
	// すばらしい……ｐ
	// やくそくどおり ポケモンをｎ
	// かいふくしよう……

@ Unused
BattleFrontier_BattlePikeRoomNormal_Text_BestOfLuckFarewell2: @ 825DBAE
	.string "그럼 안녕...$"
	// それでは ごきげんよう……

BattleFrontier_BattlePikeRoomNormal_Text_WatchOut: @ 825DBD1
	.string "!!\p"
	.string "너! 위험해!!$"
	// !!ｐ
	// きみ! あぶないっ!!

BattleFrontier_BattlePikeRoomNormal_Text_KirliaStop: @ 825DBE4
	.string "이봐!\n"
	.string "킬리아!! 그만해!$"
	// おいっ!ｎ
	// キルリア!! やめなさいっ!

BattleFrontier_BattlePikeRoomNormal_Text_DusclopsStop: @ 825DC01
	.string "이봐!\n"
	.string "미라몽!! 그만해!$"
	// おいっ!ｎ
	// サマヨ-ル!! やめなさいっ!

BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedToxic: @ 825DC20
	.string "킬리아의 맹독 공격!$"
	// キルリアの どくどく こうげき!

BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedHypnosis: @ 825DC33
	.string "킬리아의 최면술!$"
	// キルリアの さいみんじゅつ!

BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedThunderWave: @ 825DC49
	.string "킬리아의 전기자석파!$"
	// キルリアの でんじは!

BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedWillOWisp: @ 825DC63
	.string "킬리아의 도깨비불!$"
	// キルリアの おにび!

BattleFrontier_BattlePikeRoomNormal_Text_DusclopsUsedWillOWisp: @ 825DC7C
	.string "미라몽의 도깨비불!$"
	// サマヨ-ルの おにび!

BattleFrontier_BattlePikeRoomNormal_Text_DusclopsUsedIceBeam: @ 825DC97
	.string "미라몽의 냉동빔!$"
	// サマヨ-ルの れいとうビ-ム!

BattleFrontier_BattlePikeRoomNormal_Text_ThatsEnough: @ 825DCAF
	.string "에잇! 적당히 하라고!!$"
	// ええいっ! いいかげんに しないかっ!!

BattleFrontier_BattlePikeRoomNormal_Text_ApologizeForKirlia: @ 825DCCF
	.string "정말 미안해...\p"
	.string "내 킬리아는 겁쟁이라서...$"
	// もうしわけない……ｐ
	// わたしの キルリアは おくびょう でな……

BattleFrontier_BattlePikeRoomNormal_Text_ApologizeForDusclops: @ 825DD06
	.string "정말 미안해...\p"
	.string "내 미라몽은 겁쟁이라서...$"
	// もうしわけない ……ｐ
	// わたしの サマヨ-ルは おくびょう でな……

BattleFrontier_BattlePikeRoomNormal_Text_AttacksWhenStartled: @ 825DD3F
	.string "갑자기 사람을 보면 놀라서\n"
	.string "습격해 버려...\p"
	.string "너와 네 포켓몬은 괜찮아?$"
	// きゅうに ひとを みると おどろいてｎ
	// おそいかかって しまうのだ……ｐ
	// きみも ポケモンも だいじょうぶか?

BattleFrontier_BattlePikeRoomNormal_Text_ApologizeHopeMonsAreFine: @ 825DDA3
	.string "미안해...\n"
	.string "네 포켓몬은 괜찮아?$"
	// すまなかったな……ｎ
	// きみの ポケモンは ぶじか?

BattleFrontier_BattlePikeRoomNormal_Text_Silence: @ 825DDE6
	.string "...... ...... ......\n"
	.string "...... ...... ......$"
	// …… …… ……ｎ
	// …… …… ……

BattleFrontier_BattlePikeRoomNormal_Text_BattleSomewhatToughTrainer: @ 825DDFE
	.string "잘 오셨습니다...\p"
	.string "여기서는 상당히 실력이 좋은\n"
	.string "트레이너와 싸우셔야 합니다...$"
	// ようこそ……ｐ
	// こちらでは しょうしょう うでの たつｎ
	// トレ-ナ-と たたかって いただきます……

BattleFrontier_BattlePikeRoomNormal_Text_RestoreToFullHealth: @ 825DE3F
	.string "대단하군요…\p"
	.string "손님의 승리를 기리며\n"
	.string "포켓몬을 회복시켜 드리겠습니다...$"
	// ……すばらしい……ｐ
	// おきゃくさまの しょうりを たたえｎ
	// ポケモンを かいふくして さしあげます……

BattleFrontier_BattlePikeRoomNormal_Text_EnjoyRestOfChallenge2: @ 825DE94
	.string "그럼 계속해서\n"
	.string "게임을 즐겨 주십시오...$"
	// それでは ひきつづきｎ
	// ゲ-ムを おたのしみ ください……

BattleFrontier_BattlePikeRoomNormal_Text_ImThePikeQueen: @ 825DED2
	.string "나는 다슬...\n"
	.string "이곳의 주인... 튜브퀸...\p"
	.string "...뭐 알겠지만\n"
	.string "나를 쓰러뜨리지 않으면\l"
	.string "이 앞으로 갈 수 없어...\p"
	.string "...수다 떨기 싫으니까\n"
	.string "빨리 덤벼...$"
	// あたしは アザミ……ｎ
	// ここの あるじ…… チュ-ブクイ-ン……ｐ
	// …… まあ わかると おもうけどｎ
	// あたしを たおさなきゃｌ
	// このさき すすめないよ……ｐ
	// …… おしゃべりは すきじゃ ないからねｎ
	// さっさと かかっといで……

BattleFrontier_BattlePikeRoomNormal_Text_HopeYouDidntUseUpLuck: @ 825DF71
	.string "네 운…\n"
	.string "여기서 끝나지 않으면 좋겠지만...$"
	// あんたの うん……ｎ
	// ここで つきなきゃ いい けどね……

BattleFrontier_BattlePikeRoomNormal_Text_LucyShowMeFrontierPass: @ 825DFA2
	.string "다슬: ...... ...... ......\n"
	.string "프런티어패스 줘 봐...$"
	// アザミ『…… …… …… ……ｎ
	// フロンティアパス よこしな……

BattleFrontier_BattlePikeRoomNormal_Text_ReceivedLuckSymbol: @ 825DFD0
	.string "프런티어패스에\n"
	.string "럭심볼이 새겨졌다!$"
	// フロンティアパスにｎ
	// ラックシンボルが きざまれた!

BattleFrontier_BattlePikeRoomNormal_Text_AllThereIsDisappear: @ 825E003
	.string "... 야... 빨리 나가...$"
	// …… ほら…… さっさと きえな………

BattleFrontier_BattlePikeRoomNormal_Text_LucyYouAgain: @ 825E02C
	.string "다슬: ...또 너냐...\p"
	.string "...... ...... ...... ......\p"
	.string "...... ...산전수전 다 겪은\n"
	.string "지금의 나... ......\p"
	.string "그래그래 같은 상대에게\n"
	.string "져 줄 필요는 없지...\l"
	.string "...... ...... ...... ...... 좋아...\l"
	.string "해주겠어.... ...... ...... ......$"
	// アザミ『…… また あんたか……ｐ
	// …… …… …… ……ｐ
	// …… …… はなも あらしも ふみこえてｎ
	// いきてきた この あたし…… ……ｐ
	// そうそう おなじ あいてにｎ
	// まけて やる ひつようも ないね……ｌ
	// …… …… …… …… いいわ……ｌ
	// やって やるよ…… …… …… ……

BattleFrontier_BattlePikeRoomNormal_Text_NowComeOn: @ 825E0E8
	.string "이봐!! 덤벼!!$"
	// おらっ!! かかっといでっ!!

BattleFrontier_BattlePikeRoomNormal_Text_LucyFrontierPass: @ 825E0F6
	.string "다슬: ...... ...... ...... ......\p"
	.string "...... ...... 프런티어패스...$"
	// アザミ『…… …… …… ……ｐ
	// …… …… フロンティアパス……

BattleFrontier_BattlePikeRoomNormal_Text_LuckSymbolTookGoldenShine: @ 825E118
	.string "럭심볼이\n"
	.string "금색으로 빛났다!$"
	// ラックシンボルがｎ
	// きんいろに かがやいた!

BattleFrontier_BattlePikeRoomNormal_Text_IWontForget: @ 825E140
	.string "...... ...... 너...\n"
	.string "평생 잊지 않을 거야...$"
	// …… …… あんた……ｎ
	// いっしょう わすれない からね………

BattleFrontier_BattlePikeRoomNormal_Text_ChoseRoomNoHeal: @ 825E15D
	.string "잘 오셨습니다...\p"
	.string "우후후...\n"
	.string "정말 운도 없으시군요...\p"
	.string "마지막에 선택한 것이\n"
	.string "이 방만 아니었어도 포켓몬들을\l"
	.string "회복시킬 수 있었을 텐데...$"
	// ようこそ いらっしゃい ました……ｐ
	// うふふ……ｎ
	// なんて うんの ない おかた……ｐ
	// さいごに えらんだのがｎ
	// このへやで なければ ポケモンたちをｌ
	// かいふくして さしあげたのに……

BattleFrontier_BattlePikeRoomNormal_Text_ChoseRoomHealOne: @ 825E1DD
	.string "잘 오셨습니다...\p"
	.string "마지막에 이 방을 선택한\n"
	.string "손님께 포켓몬을 1마리만\l"
	.string "회복시켜 드리겠습니다...$"
	// ようこそ いらっしゃい ました……ｐ
	// さいごに このへやを えらばれたｎ
	// おきゃくさまは ポケモンを 1ひきだけｌ
	// かいふくして さしあげましょう……

BattleFrontier_BattlePikeRoomNormal_Text_ChoseRoomHealTwo: @ 825E238
	.string "잘 오셨습니다...\p"
	.string "마지막에 이 방을 선택한\n"
	.string "손님께 포켓몬을 2마리\l"
	.string "회복시켜 드리겠습니다...$"
	// ようこそ いらっしゃい ました……ｐ
	// さいごに このへやを えらばれたｎ
	// おきゃくさまは ポケモンを 2ひきｌ
	// かいふくして さしあげましょう……

@ Unused
BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreAllMons: @ 825E293
	.string "잘 오셨습니다...\p"
	.string "우후후...\n"
	.string "정말 운이 좋으시군요...\p"
	.string "마지막에 이 방을 선택한\n"
	.string "손님께 포켓몬을 전부\l"
	.string "회복시켜 드리겠습니다...$"
	// ようこそ いらっしゃい ました……ｐ
	// うふふ……ｎ
	// ほんとうに ラッキ-な おかた……ｐ
	// さいごに このへやを えらばれたｎ
	// おきゃくさまは ポケモンを すべてｌ
	// かいふくして さしあげましょう……

BattleFrontier_BattlePikeRoomNormal_Text_ShallFetchOurMaster: @ 825E311
	.string "그럼 저희의 주인을\n"
	.string "불러오도록 하겠습니다...$"
	// では わたくしどもの あるじをｎ
	// よんで まいり ますね……

BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreTwoMons: @ 825E32E
	.string "오오 넌 운이 좋구나!\p"
	.string "지금 나는 기분이 좋으니!\n"
	.string "네 포켓몬을 2마리\l"
	.string "회복시켜 주겠다!!$"
	// おお きみは ツイてるぞ!ｐ
	// いまの わしは きげんが いいからな!ｎ
	// きみの ポケモンを 2ひきｌ
	// かいふくして あげよう!

