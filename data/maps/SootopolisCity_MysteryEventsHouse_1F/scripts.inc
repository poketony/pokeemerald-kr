.set LOCALID_OLD_MAN, 1

SootopolisCity_MysteryEventsHouse_1F_MapScripts:: @ 8227953
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_MysteryEventsHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SootopolisCity_MysteryEventsHouse_1F_OnFrame
	.byte 0

SootopolisCity_MysteryEventsHouse_1F_OnTransition: @ 822795E
	frontier_checkvisittrainer
	compare VAR_RESULT, 0
	call_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_SetTrainerVisitingLayout
	compare VAR_SOOTOPOLIS_MYSTERY_EVENTS_STATE, 0
	call_if_ne SootopolisCity_MysteryEventsHouse_1F_EventScript_MoveOldManToDoor
	end

SootopolisCity_MysteryEventsHouse_1F_EventScript_SetTrainerVisitingLayout:: @ 822797D
	setvar VAR_TEMP_1, 1
	setobjectxyperm LOCALID_OLD_MAN, 3, 2
	setobjectmovementtype LOCALID_OLD_MAN, MOVEMENT_TYPE_FACE_DOWN
	setmaplayoutindex LAYOUT_SOOTOPOLIS_CITY_MYSTERY_EVENTS_HOUSE_1F_STAIRS_UNBLOCKED
	return

SootopolisCity_MysteryEventsHouse_1F_EventScript_MoveOldManToDoor:: @ 8227991
	setobjectxyperm LOCALID_OLD_MAN, 2, 2
	setobjectmovementtype LOCALID_OLD_MAN, MOVEMENT_TYPE_FACE_RIGHT
	return

SootopolisCity_MysteryEventsHouse_1F_OnFrame: @ 822799D
	map_script_2 VAR_SOOTOPOLIS_MYSTERY_EVENTS_STATE, 1, SootopolisCity_MysteryEventsHouse_1F_EventScript_OldManCommentOnBattle
	map_script_2 VAR_SOOTOPOLIS_MYSTERY_EVENTS_STATE, 2, SootopolisCity_MysteryEventsHouse_1F_EventScript_OldManCommentOnBattle
	map_script_2 VAR_SOOTOPOLIS_MYSTERY_EVENTS_STATE, 3, SootopolisCity_MysteryEventsHouse_1F_EventScript_OldManCommentOnBattle
	.2byte 0

SootopolisCity_MysteryEventsHouse_1F_EventScript_OldManCommentOnBattle:: @ 82279B7
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_MysteryEventsHouse_1F_Movement_PlayerExitStairs
	waitmovement 0
	applymovement LOCALID_OLD_MAN, SootopolisCity_MysteryEventsHouse_1F_Movement_OldManWalkBehindPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_OLD_MAN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	compare VAR_SOOTOPOLIS_MYSTERY_EVENTS_STATE, 1
	call_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_BattleWonComment
	compare VAR_SOOTOPOLIS_MYSTERY_EVENTS_STATE, 2
	call_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_BattleLostComment
	compare VAR_SOOTOPOLIS_MYSTERY_EVENTS_STATE, 3
	call_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_BattleTiedComment
	special LoadPlayerParty
	setvar VAR_SOOTOPOLIS_MYSTERY_EVENTS_STATE, 0
	releaseall
	end

SootopolisCity_MysteryEventsHouse_1F_EventScript_BattleWonComment:: @ 8227A04
	msgbox SootopolisCity_MysteryEventsHouse_1F_Text_ThatWasSuperlative, MSGBOX_DEFAULT
	return

SootopolisCity_MysteryEventsHouse_1F_EventScript_BattleLostComment:: @ 8227A0D
	msgbox SootopolisCity_MysteryEventsHouse_1F_Text_TooBadForYou, MSGBOX_DEFAULT
	return

SootopolisCity_MysteryEventsHouse_1F_EventScript_BattleTiedComment:: @ 8227A16
	msgbox SootopolisCity_MysteryEventsHouse_1F_Text_BrilliantStandoff, MSGBOX_DEFAULT
	return

SootopolisCity_MysteryEventsHouse_1F_Movement_PlayerExitStairs: @ 8227A1F
	walk_down
	step_end

SootopolisCity_MysteryEventsHouse_1F_Movement_OldManWalkBehindPlayer: @ 8227A21
	walk_right
	walk_in_place_fastest_down
	step_end

SootopolisCity_MysteryEventsHouse_1F_EventScript_OldMan:: @ 8227A24
	lock
	faceplayer
	frontier_checkvisittrainer
	compare VAR_RESULT, 1
	goto_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_InvalidVisitingTrainer
	compare VAR_TEMP_1, 1
	goto_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_TrainerVisiting
	msgbox SootopolisCity_MysteryEventsHouse_1F_Text_OnlyAmusementWatchingBattles, MSGBOX_DEFAULT
	release
	end

SootopolisCity_MysteryEventsHouse_1F_EventScript_InvalidVisitingTrainer:: @ 8227A4E
	msgbox SootopolisCity_MysteryEventsHouse_1F_Text_OnlyAmusementWatchingBattles, MSGBOX_DEFAULT
	release
	end

SootopolisCity_MysteryEventsHouse_1F_EventScript_TrainerVisiting:: @ 8227A58
	special SavePlayerParty
	special BufferEReaderTrainerName
	msgbox SootopolisCity_MysteryEventsHouse_1F_Text_ChallengeVisitingTrainer, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_DeclineBattle
	call SootopolisCity_MysteryEventsHouse_1F_EventScript_ChooseParty
	compare VAR_RESULT, 0
	goto_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_DeclineBattle
	msgbox SootopolisCity_MysteryEventsHouse_1F_Text_SaveProgressBeforeBattle, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_DeclineBattle
	special LoadPlayerParty
	call Common_EventScript_SaveGame
	compare VAR_RESULT, FALSE
	goto_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_DeclineBattle
	special SavePlayerParty
	special ReducePlayerPartyToSelectedMons
	msgbox SootopolisCity_MysteryEventsHouse_1F_Text_HopeToSeeGoodMatch, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_NORTH
	call_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_EnterBasementNorth
	compare VAR_FACING, DIR_EAST
	call_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_EnterBasementEast
	compare VAR_FACING, DIR_WEST
	call_if_eq SootopolisCity_MysteryEventsHouse_1F_EventScript_EnterBasementWest
	warp MAP_SOOTOPOLIS_CITY_MYSTERY_EVENTS_HOUSE_B1F, 255, 3, 1
	waitstate
	release
	end

SootopolisCity_MysteryEventsHouse_1F_EventScript_DeclineBattle:: @ 8227AE2
	special LoadPlayerParty
	msgbox SootopolisCity_MysteryEventsHouse_1F_Text_YouWontBattle, MSGBOX_DEFAULT
	release
	end

SootopolisCity_MysteryEventsHouse_1F_EventScript_ChooseParty:: @ 8227AEF
	msgbox SootopolisCity_MysteryEventsHouse_1F_Text_KeepItTo3On3, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	waitstate
	return

SootopolisCity_MysteryEventsHouse_1F_EventScript_EnterBasementNorth:: @ 8227AFE
	applymovement VAR_LAST_TALKED, SootopolisCity_MysteryEventsHouse_1F_Movement_OldManMoveAsideLeft
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_MysteryEventsHouse_1F_Movement_PlayerEnterBasementNorth
	waitmovement 0
	return

SootopolisCity_MysteryEventsHouse_1F_EventScript_EnterBasementEast:: @ 8227B10
	applymovement VAR_LAST_TALKED, SootopolisCity_MysteryEventsHouse_1F_Movement_OldManMoveAsideRight
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_MysteryEventsHouse_1F_Movement_PlayerEnterBasementEast
	waitmovement 0
	return

SootopolisCity_MysteryEventsHouse_1F_EventScript_EnterBasementWest:: @ 8227B22
	applymovement VAR_LAST_TALKED, SootopolisCity_MysteryEventsHouse_1F_Movement_OldManMoveAsideLeft
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_MysteryEventsHouse_1F_Movement_PlayerEnterBasementWest
	waitmovement 0
	return

SootopolisCity_MysteryEventsHouse_1F_Movement_PlayerEnterBasementNorth: @ 8227B34
	delay_16
	walk_up
	walk_up
	step_end

SootopolisCity_MysteryEventsHouse_1F_Movement_PlayerEnterBasementEast: @ 8227B38
	delay_16
	walk_right
	walk_up
	step_end

SootopolisCity_MysteryEventsHouse_1F_Movement_PlayerEnterBasementWest: @ 8227B3C
	delay_16
	walk_left
	walk_up
	step_end

SootopolisCity_MysteryEventsHouse_1F_Movement_OldManMoveAsideLeft: @ 8227B40
	walk_left
	walk_in_place_fastest_right
	step_end

SootopolisCity_MysteryEventsHouse_1F_Movement_OldManMoveAsideRight: @ 8227B43
	walk_right
	walk_in_place_fastest_left
	step_end

SootopolisCity_MysteryEventsHouse_1F_Text_OnlyAmusementWatchingBattles: @ 8227B46
	.string "나도 젊었을 때는\n"
	.string "포켓몬 트레이너로서\l"
	.string "전 세계를 여행했었지\p"
	.string "할아버지가 되어 버린 지금은\n"
	.string "젊은 트레이너의 승부를 보는 게\l"
	.string "유일한 낙이라네$"
	@ わしも わかいころはｎ
	@ ポケモン トレ-ナ-としてｌ
	@ せかいじゅうを たび していたのじゃｐ
	@ ジジイとなった いまではｎ
	@ わかい トレ-ナ-の しょうぶを みるのがｌ
	@ ゆいいつの たのしみ じゃ

SootopolisCity_MysteryEventsHouse_1F_Text_DoorAppearsToBeLocked: @ 8227BDD
	.string "문이 잠겨 있는 것 같다!$"
	@ とびらには かぎが かかって いるようだ!

SootopolisCity_MysteryEventsHouse_1F_Text_ChallengeVisitingTrainer: @ 8227BFC
	.string "지금 {STR_VAR_1}{K_I}라는 트레이너가\n"
	.string "우리 집에 와 있네!\p"
	.string "{STR_VAR_1}{K_WAGWA} 승부하지 않겠나?$"
	@ いまは §い という トレ-ナ-がｎ
	@ わしの いえに きておる!ｐ
	@ §いと しょうぶ してみたいのじゃな?

SootopolisCity_MysteryEventsHouse_1F_Text_YouWontBattle: @ 8227C44
	.string "승부하지 않는 겐가...\n"
	.string "승부를 볼 수 없어서 실망이구먼...$"
	@ しょうぶ せんのか……ｎ
	@ しょうぶを みられなくて ガッカリ……

SootopolisCity_MysteryEventsHouse_1F_Text_KeepItTo3On3: @ 8227C84
	.string "오오 그래그래!\p"
	.string "헌데 이 집은\n"
	.string "그다지 튼튼하지 않으니까\p"
	.string "많아도 3대3\n"
	.string "승부로 해 주지 않겠나?$"
	@ おお そうか そうか!ｐ
	@ じゃが この いえはｎ
	@ あんまり がんじょう じゃないからｐ
	@ せめて 3たい3のｎ
	@ しょうぶに して くれんかのう?

SootopolisCity_MysteryEventsHouse_1F_Text_SaveProgressBeforeBattle: @ 8227CEB
	.string "그럼 승부 전에\n"
	.string "리포트를 해 두는 편이 좋네$"
	@ じゃあ しょうぶの まえにｎ
	@ レポ-トを かいて おいたほうが よいぞ

SootopolisCity_MysteryEventsHouse_1F_Text_HopeToSeeGoodMatch: @ 8227D21
	.string "좋은 승부를 기대하고 있겠네!$"
	@ よい しょうぶを きたい しておるぞ!

@ Unused
SootopolisCity_MysteryEventsHouse_1F_Text_StrVar1Tie: @ 8227D3D
	.string "{STR_VAR_1}$"

SootopolisCity_MysteryEventsHouse_B1F_Text_MatchEndedUpDraw: @ 8227D40
	.string "승부는 무승부로 끝났다!$"
	@ しょうぶは ひきわけに おわった!

SootopolisCity_MysteryEventsHouse_1F_Text_BrilliantStandoff: @ 8227D5B
	.string "무승부였나!\p"
	.string "서로 한방도 용납하지 않는\n"
	.string "굉장한 승부였다네!$"
	@ ひきわけ じゃったか!ｐ
	@ おたがい いっぽも ゆずらぬｎ
	@ すばらしい しょうぶ じゃったぞ!

@ Unused
SootopolisCity_MysteryEventsHouse_1F_Text_StrVar1Won: @ 8227DB5
	.string "{STR_VAR_1}$"

SootopolisCity_MysteryEventsHouse_1F_Text_ThatWasSuperlative: @ 8227DB8
	.string "훌륭했네!\p"
	.string "마치 내 젊은 시절을\n"
	.string "보는 것 같구먼!$"
	@ みごと じゃったぞ!ｐ
	@ まるで わしの わかい ころをｎ
	@ みている ようじゃわい!


@ Unused
SootopolisCity_MysteryEventsHouse_1F_Text_StrVar1Lost: @ 8227E00
	.string "{STR_VAR_1}$"

SootopolisCity_MysteryEventsHouse_1F_Text_TooBadForYou: @ 8227E03
	.string "유감이구먼\n"
	.string "하지만 좋은 승부였네!\l"
	.string "다음 번은 이기면 좋겠구먼!$"
	@ ざんねん じゃったのうｎ
	@ じゃが よい しょうぶ じゃったぞ!ｌ
	@ つぎこそは かてると よいのう

