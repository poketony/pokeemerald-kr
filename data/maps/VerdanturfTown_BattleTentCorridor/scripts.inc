.set LOCALID_ATTENDANT, 1

VerdanturfTown_BattleTentCorridor_MapScripts:: @ 820208A
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VerdanturfTown_BattleTentCorridor_OnFrame
	.byte 0

VerdanturfTown_BattleTentCorridor_OnFrame: @ 8202090
	map_script_2 VAR_TEMP_0, 0, VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor:: @ 820209A
	lockall
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	setvar VAR_0x8006, 0
	warp MAP_VERDANTURF_TOWN_BATTLE_TENT_BATTLE_ROOM, 255, 6, 5
	waitstate
	releaseall
	end

VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor: @ 82020DE
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor: @ 82020E3
	walk_up
VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor: @ 82020E4
	walk_up
	set_invisible
	step_end


@ Leftover text from when this was a Contest Hall in R/S
@ Unused
VerdanturfTown_ContestHall_Text_WhichContestYouEntering: @ 82020E7
	.string "넌 무슨 콘테스트에 나갈 거야?\n"
	.string "하나 어드바이스해 줄게!\p"
	.string "예를 들어 귀여움콘테스트에서는\n"
	.string "1차 심사에서 귀여움만이\l"
	.string "평가되는 게 아닌 것 같아\p"
	.string "키우는 방법을 구분해 두는 게 좋아!$"

@ Unused
VerdanturfTown_ContestHall_Text_RaisedMonToBeCute: @ 82021C4
	.string "포켓몬이 귀여워지도록\n"
	.string "키우고 있는데\p"
	.string "콘테스트에서는 귀여움으로도\n"
	.string "경쟁할 수가 있구나!\p"
	.string "소중하게 키워서 다행이다...$"

@ Unused
VerdanturfTown_ContestHall_Text_MyMonRules: @ 8202251
	.string "내 포켓몬...\p"
	.string "엄청나게 근사하고\n"
	.string "강인하고 아름답고\l"
	.string "귀엽고 슬기로운데 말야\p"
	.string "이렇게 된 이상 모든 콘테스트에서\n"
	.string "닥치는 대로 우승을 노릴 거야!$"

@ Unused
VerdanturfTown_ContestHall_Text_NormalRankStage: @ 82022D6
	.string "포켓몬 콘테스트\n"
	.string "노말랭크 스테이지!$"

