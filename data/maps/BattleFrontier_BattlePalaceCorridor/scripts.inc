.set LOCALID_ATTENDANT, 1

BattleFrontier_BattlePalaceCorridor_MapScripts:: @ 824F4A3
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePalaceCorridor_OnFrame
	.byte 0

BattleFrontier_BattlePalaceCorridor_OnFrame: @ 824F4A9
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattlePalaceCorridor_EventScript_WalkThroughCorridor
	.2byte 0

BattleFrontier_BattlePalaceCorridor_EventScript_WalkThroughCorridor:: @ 824F4B3
	delay 16
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePalaceCorridor_Movement_EnterCorridor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePalaceCorridor_Movement_EnterCorridor
	waitmovement 0
	lockall
	palace_getcomment
	compare VAR_RESULT, 0
	call_if_eq BattleFrontier_BattlePalaceCorridor_EventScript_RandomComment1
	compare VAR_RESULT, 1
	call_if_eq BattleFrontier_BattlePalaceCorridor_EventScript_RandomComment2
	compare VAR_RESULT, 2
	call_if_eq BattleFrontier_BattlePalaceCorridor_EventScript_RandomComment3
	compare VAR_RESULT, 3
	call_if_eq BattleFrontier_BattlePalaceCorridor_EventScript_StreakComment
	compare VAR_RESULT, 4
	call_if_eq BattleFrontier_BattlePalaceCorridor_EventScript_LongStreakComment
	closemessage
	frontier_get FRONTIER_DATA_LVL_MODE
	compare VAR_RESULT, FRONTIER_LVL_OPEN
	goto_if_eq BattleFrontier_BattlePalaceCorridor_EventScript_WalkToOpenBattleRoom
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePalaceCorridor_Movement_AttendantWalkTo50BattleRoom
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePalaceCorridor_Movement_PlayerWalkTo50BattleRoom
	waitmovement 0
	opendoor 6, 3
	waitdooranim
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePalaceCorridor_Movement_AttendantEnterBattleRoom
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePalaceCorridor_Movement_PlayerEnterBattleRoom
	waitmovement 0
	closedoor 6, 3
	waitdooranim
	goto BattleFrontier_BattlePalaceCorridor_EventScript_WarpToBattleRoom

BattleFrontier_BattlePalaceCorridor_EventScript_WalkToOpenBattleRoom:: @ 824F553
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePalaceCorridor_Movement_AttendantWalkToOpenBattleRoom
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePalaceCorridor_Movement_PlayerWalkToOpenBattleRoom
	waitmovement 0
	opendoor 10, 3
	waitdooranim
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePalaceCorridor_Movement_AttendantEnterBattleRoom
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePalaceCorridor_Movement_PlayerEnterBattleRoom
	waitmovement 0
	closedoor 10, 3
	waitdooranim
BattleFrontier_BattlePalaceCorridor_EventScript_WarpToBattleRoom:: @ 824F581
	warp MAP_BATTLE_FRONTIER_BATTLE_PALACE_BATTLE_ROOM, 255, 7, 4
	waitstate
	end

BattleFrontier_BattlePalaceCorridor_EventScript_RandomComment1:: @ 824F58B
	msgbox BattleFrontier_BattlePalaceCorridor_Text_PeopleAndMonAreSame, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceCorridor_EventScript_RandomComment2:: @ 824F594
	msgbox BattleFrontier_BattlePalaceCorridor_Text_LetMonDoWhatItLikes, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceCorridor_EventScript_RandomComment3:: @ 824F59D
	msgbox BattleFrontier_BattlePalaceCorridor_Text_MonDifferentWhenCornered, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceCorridor_EventScript_StreakComment:: @ 824F5A6
	msgbox BattleFrontier_BattlePalaceCorridor_Text_BeginningToUnderstandNature, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceCorridor_EventScript_LongStreakComment:: @ 824F5AF
	msgbox BattleFrontier_BattlePalaceCorridor_Text_HeartfeltBondBetweenYouAndMons, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceCorridor_Movement_EnterCorridor: @ 824F5B8
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePalaceCorridor_Movement_AttendantWalkTo50BattleRoom: @ 824F5BD
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePalaceCorridor_Movement_PlayerWalkTo50BattleRoom: @ 824F5C4
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	step_end

BattleFrontier_BattlePalaceCorridor_Movement_AttendantWalkToOpenBattleRoom: @ 824F5CB
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePalaceCorridor_Movement_PlayerWalkToOpenBattleRoom: @ 824F5D2
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePalaceCorridor_Movement_PlayerEnterBattleRoom: @ 824F5D9
	walk_up
BattleFrontier_BattlePalaceCorridor_Movement_AttendantEnterBattleRoom: @ 824F5DA
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePalaceCorridor_Text_PeopleAndMonAreSame: @ 824F5DD
	.string "사람도 포켓몬도 모두 같다...\p"
	.string "각자 성격에 따라\n"
	.string "능숙하고 서투른 것이 있지...$"
	@ ひとも ポケモンも みな おなじ……ｐ
	@ それぞれの せいかくに よってｎ
	@ とくいなこと にがてなことが ある……

BattleFrontier_BattlePalaceCorridor_Text_LetMonDoWhatItLikes: @ 824F65B
	.string "서투른 것보단 능숙한 것...\p"
	.string "포켓몬의 기분으로\n"
	.string "배우게 할 기술을 생각해 봐라$"
	@ にがてなこと よりも とくいな こと……ｐ
	@ ポケモンの きもちに なってｎ
	@ おぼえさせる わざを かんがえて みろ

BattleFrontier_BattlePalaceCorridor_Text_MonDifferentWhenCornered: @ 824F718
	.string "성격이란 신기한 것이지...\p"
	.string "궁지에 몰림으로써 갑자기\n"
	.string "행동이 바뀌기도 한다네$"
	@ せいかくとは ふしぎな ものだ……ｐ
	@ おいつめられる ことで ガラッとｎ
	@ こうどうが かわる ものも おる……

BattleFrontier_BattlePalaceCorridor_Text_BeginningToUnderstandNature: @ 824F78C
	.string "... 슬슬 포켓몬의 성격을\n"
	.string "지켜볼 수 있게 되었나?$"
	@ …… そろそろ ポケモンの せいかくをｎ
	@ みきわめられる ように なってきたか?

BattleFrontier_BattlePalaceCorridor_Text_HeartfeltBondBetweenYouAndMons: @ 824F7D4
	.string "오오... 자네와 포켓몬 사이에\n"
	.string "강한 유대감이 보이는구먼...$"
	@ おお…… おぬしと ポケモンの あいだにｎ
	@ つよい こころの きずなが みえる……

