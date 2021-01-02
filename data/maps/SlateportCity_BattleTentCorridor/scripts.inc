.set LOCALID_ATTENDANT, 1

SlateportCity_BattleTentCorridor_MapScripts:: @ 8208E26
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SlateportCity_BattleTentCorridor_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SlateportCity_BattleTentCorridor_OnWarp
	.byte 0

	@ This is Slateport Tent's version of the Battle Factory Pre-Battle Room

SlateportCity_BattleTentCorridor_OnWarp: @ 8208E31
	map_script_2 VAR_TEMP_1, 0, SlateportCity_BattleTentCorridor_EventScript_SetUpObjects
	.2byte 0

SlateportCity_BattleTentCorridor_EventScript_SetUpObjects:: @ 8208E3B
	setvar VAR_TEMP_1, 1
	compare VAR_0x8006, 1
	goto_if_ne SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth
	setobjectxy LOCALID_ATTENDANT, 2, 2
	turnobject LOCALID_ATTENDANT, DIR_SOUTH
SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth:: @ 8208E56
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

SlateportCity_BattleTentCorridor_OnFrame: @ 8208E5B
	map_script_2 VAR_TEMP_0, 0, SlateportCity_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

SlateportCity_BattleTentCorridor_EventScript_EnterCorridor:: @ 8208E65
	compare VAR_0x8006, 1
	goto_if_eq SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantEnter
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerEnter
	waitmovement 0
	compare VAR_0x8006, 2
	goto_if_eq SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge
	slateporttent_generaterentalmons
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_HoldMonsChooseFromSelection, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	slateporttent_rentmons
	waitstate
SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom:: @ 8208EB4
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_RightThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantExit
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerExit
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	warp MAP_SLATEPORT_CITY_BATTLE_TENT_BATTLE_ROOM, 255, 4, 4
	waitstate
	end

SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle:: @ 8208EEE
	factory_setopponentmons
	factory_resethelditems
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LetUsRestoreMons, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent:: @ 8208F0D
	frontier_get FRONTIER_DATA_BATTLE_NUM
	compare VAR_RESULT, 1
	call_if_eq SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent
	compare VAR_RESULT, 2
	call_if_eq SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, 1
	switch VAR_RESULT
	case 0, SlateportCity_BattleTentCorridor_EventScript_AskSwapMon
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge
	case 2, SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge

SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge:: @ 8208F5B
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_SaveAndQuitGame, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case YES, SlateportCity_BattleTentCorridor_EventScript_PauseChallenge
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge:: @ 8208F89
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_RetireFromChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case 0, SlateportCity_BattleTent_EventScript_WarpToLobbyLost
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskSwapMon:: @ 8208FBB
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LikeToSwapMon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	case YES, SlateportCity_BattleTentCorridor_EventScript_SwapMons
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_SwapMons:: @ 8208FF1
	fadescreen FADE_TO_BLACK
	slateporttent_swapmons
	waitstate
	compare VAR_RESULT, 1
	goto_if_eq SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_YourSwapIsComplete, MSGBOX_DEFAULT
	goto SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent:: @ 8209014
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor2ndOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent:: @ 820901B
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor3rdOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_PauseChallenge:: @ 8209022
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_SavingDataPleaseWait
	waitmessage
	slateporttent_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge:: @ 8209044
	special SavePlayerParty
	factory_setparties 0
	goto SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_Movement_PlayerEnter: @ 8209059
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SlateportCity_BattleTentCorridor_Movement_PlayerExit: @ 820905E
	walk_up
	walk_up
	set_invisible
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantEnter: @ 8209062
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantExit: @ 8209068
	walk_up
	set_invisible
	step_end

@ Leftover text from when this was a Contest Hall in R/S
@ Unused
SlateportCity_ContestHall_Text_AdviceForContests: @ 820906B
	.string "콘테스트의 나이스한 정보를\n"
	.string "알려줄게!\p"
	.string "몇몇 기술 다음에\n"
	.string "특정한 기술로 어필하면\l"
	.string "엄청 눈에 띄는 경우가 있어!\p"
	.string "잘하면 꽤나\n"
	.string "유리한 어필이 가능하다고!\p"
	.string "다만 방해받는 경우도 있어$"

@ Unused
SlateportCity_ContestHall_Text_MyPapaIsContestJudge: @ 820917A
	.string "우리 아빠는 콘테스트의\n"
	.string "심사위원을 하고 있어!\p"
	.string "나 어른이 되면\n"
	.string "콘테스트의 심사위원하고\l"
	.string "체육관 관장 중에 뭘 할까?$"

@ Unused
SlateportCity_ContestHall_Text_ImLikeMajorlyCheesed: @ 82091DC
	.string "어째서 내 포켓몬이\n"
	.string "우승하지 못했는지\l"
	.string "전혀 납득할 수 없어서 말이야\l"
	.string "심사위원한테 좀 따져봤는데\p"
	.string "전혀 상대해주지 않아서\n"
	.string "너무 분해 죽겠어!\p"
	.string "어이 너!\n"
	.string "잠자코 이거나 받아!$"

@ Unused
SlateportCity_ContestHall_Text_ExplainTorment: @ 8209322
	.string "기술머신41은 트집!\p"
	.string "상대가 같은 기술을 반복해서\n"
	.string "사용할 수 없게 만드는 기술이지!\p"
	.string "참고로 말하지만\n"
	.string "난 트집 잡은 적 없다!$"

@ Unused
SlateportCity_ContestHall_Text_MCStepUpTakePartInContest: @ 82093ED
	.string "사회자: 어머! 꽤 멋진\n"
	.string "포켓몬을 데리고 있네!\p"
	.string "부디! 콘테스트에\n"
	.string "참가해줘!\p"
	.string "분명 잘 될 거야!\n"
	.string "내 눈은 확실하거든!$"

@ Unused
SlateportCity_ContestHall_Text_JudgeWouldntDoToMissContest: @ 82094A1
	.string "심사위원: 여어, 안녕하신가!\n"
	.string "너도 트레이너인가 보구나!\p"
	.string "그러면 포켓몬 콘테스트에\n"
	.string "나올 수 없는 건 아니야!\p"
	.string "콘테스트패스를 잔디마을에서 받고\n"
	.string "지금 바로 참가하는 거다!$"

@ Unused
SlateportCity_ContestHall_Text_ItsAppealTime: @ 820954E
	.string "드디어 이제부터 어필타임!\n"
	.string "어느 기술부터 보여줄까나?$"

@ Unused
SlateportCity_ContestHall_Text_DidntPayAttentionToAppeal: @ 8209579
	.string "내 포켓몬의 어필\n"
	.string "그다지 주목받지 못했어...\p"
	.string "흥... 저 심사위원\n"
	.string "보는 눈이 없군!$"

@ Unused
SlateportCity_ContestHall_Text_RewardWithSageAdvice: @ 82095F1
	.string "앗! 이런 곳에까지 온 너\n"
	.string "연구에 열심이구나!\l"
	.string "그러면 좋은 걸 알려줄게\p"
	.string "보여준 기술의 반응이 좋으면\n"
	.string "회장이 익사이트 해져!\p"
	.string "가장 익사이트 해졌을 때\n"
	.string "어필한 포켓몬에겐...\p"
	.string "좋은 일이 일어날지도!$"

@ Unused
SlateportCity_ContestHall_Text_MoreFreakedOutThanMon: @ 8209718
	.string "아 안되겠어! 포켓몬보다\n"
	.string "내가 더 긴장하고 있잖아!\l"
	.string "부들부들.... 두근두근...$"

@ Unused
SlateportCity_ContestHall_Text_BattleAndContestAlike: @ 8209775
	.string "포켓몬 승부와 콘테스트는\n"
	.string "다른 것 같으면서도 닮았어!\p"
	.string "소중히 키운 포켓몬을\n"
	.string "믿고 응원한다는 점이 말야!$"

@ Unused
SlateportCity_ContestHall_Text_MonLooksOnTopOfGame: @ 82097F6
	.string "저 포켓몬 기세 좋아 보인다!\p"
	.string "2차 심사에서 기세가 좋은\n"
	.string "포켓몬은 딱히 긴장하지 않아서\l"
	.string "어필할 수 있는 것 같네$"

@ Unused
SlateportCity_ContestHall_Text_MyMonBetterThanThatLot: @ 8209890
	.string "뭐야- 이 정도면\n"
	.string "내 포켓몬 쪽이\l"
	.string "더 대단하다고!$"

@ Unused
SlateportCity_ContestHall_Text_GetUrgeToMoveWithMon: @ 82098E6
	.string "기운 넘치는 어필을 보고 있으면\n"
	.string "같이 몸이\l"
	.string "기운 넘치게 되지 않아?$"

@ Unused
SlateportCity_ContestHall_Text_HyperRankStage: @ 820993D
	.string "포켓몬 콘테스트\n"
	.string "하이퍼랭크 스테이지!$"

