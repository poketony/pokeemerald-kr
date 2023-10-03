.set LOCALID_ATTENDANT, 1

BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts:: @ 8243D92
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerMultiPartnerRoom_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame
	.byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_OnResume: @ 8243DA7
	pyramid_resetparty
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition: @ 8243DB0
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_1
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_2
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_3
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_4
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_5
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_6
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2
	tower_loadpartners
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner:: @ 8243DDA
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_4, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_5, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_6, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_7, OBJ_EVENT_GFX_BOY_1
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_3, 1
	setobjectxyperm LOCALID_ATTENDANT, 10, 2
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp: @ 8243E14
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth:: @ 8243E1E
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame: @ 8243E23
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom:: @ 8243E35
	lockall
	setvar VAR_TEMP_3, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom:: @ 8243E41
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom
	waitmovement 0
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit
	waitmovement 0
	copyobjectxytoperm LOCALID_ATTENDANT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner, MSGBOX_DEFAULT
	special HealPlayerParty
	setvar VAR_TEMP_1, 1
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom: @ 8243E75
	walk_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit: @ 8243E77
	walk_left
	walk_in_place_fastest_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Attendant:: @ 8243E7A
	lock
	faceplayer
	message BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge:: @ 8243E9D
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator:: @ 8243EB5
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	opendoor 10, 1
	waitdooranim
	call BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator
	closedoor 10, 1
	waitdooranim
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR, 255, 1, 6
	waitstate
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator:: @ 8243EE4
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorEast: @ 8243EF6
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorWest: @ 8243F08
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator: @ 8243F1A
	walk_up
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast: @ 8243F1E
	walk_right
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest: @ 8243F22
	walk_left
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator: @ 8243F26
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner1:: @ 8243F29
	lock
	faceplayer
	setvar VAR_TEMP_2, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner:: @ 8243F36
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_INTRO
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON1
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON2_ASK
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, 0
	switch VAR_RESULT
	case 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_ACCEPT
	waitmessage
	waitbuttonpress
	closemessage
	compare VAR_FACING, DIR_SOUTH
	call_if_ne BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit
	compare VAR_FACING, DIR_SOUTH
	call_if_eq BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth
	removeobject VAR_LAST_TALKED
	setflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_PARTNER_ROOM, 255, 10, 3
	waitstate
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner:: @ 8243FC3
	tower_dopartnermsg PARTNER_MSGID_REJECT
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit:: @ 8243FD4
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth:: @ 8243FDF
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit: @ 8243FEA
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth: @ 8243FF2
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner2:: @ 8243FFB
	lock
	faceplayer
	setvar VAR_TEMP_2, 1
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner3:: @ 8244008
	lock
	faceplayer
	setvar VAR_TEMP_2, 2
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner4:: @ 8244015
	lock
	faceplayer
	setvar VAR_TEMP_2, 3
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner5:: @ 8244022
	lock
	faceplayer
	setvar VAR_TEMP_2, 4
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner6:: @ 824402F
	lock
	faceplayer
	setvar VAR_TEMP_2, 5
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner7:: @ 824403C
	lock
	faceplayer
	setvar VAR_TEMP_2, 6
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner8:: @ 8244049
	lock
	faceplayer
	setvar VAR_TEMP_2, 7
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner: @ 8244056
	.string "여기에 있는 트레이너 중에서\n"
	.string "파트너를 찾으세요!$"
	// こちらに いる トレ-ナ-の なかからｎ
	// パ-トナ-を おさがしください!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner: @ 8244094
	.string "{PLAYER}님은 아직\n"
	.string "파트너를 찾지 못했습니다!\p"
	.string "파트너 찾기를 중지하고\n"
	.string "접수처로 되돌아갈까요?$"
	// あさんはｎ
	// まだ パ-トナ-を みつけていません!ｐ
	// パ-トナ-を さがすのを やめてｎ
	// うけつけへ もどりますか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2: @ 824410C
	.string "그럼\n"
	.string "여기에 있는 트레이너 중에서\l"
	.string "파트너를 찾으세요!$"
	// それではｎ
	// こちらに いる トレ-ナ-の なかからｌ
	// パ-トナ-を おさがしください!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner:: @ 8244149
	.string "파트너 찾기\n"
	.string "수고하셨습니다!\p"
	.string "그럼 멀티 배틀룸으로\n"
	.string "안내하겠습니다!$"
	// パ-トナ-さがしｎ
	// おつかれさまでした!ｐ
	// それでは マルチ バトルル-ムへｎ
	// おつれいたします

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Intro:: @ 824419A
	.string "저는\n"
	.string "{STR_VAR_1}님의 {STR_VAR_2}번째 제자\l"
	.string "그 이름은 {STR_VAR_3}!$"
	// ぼくはｎ
	// いさんの うばん でしｌ
	// そのなも え!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon1:: @ 82441CA
	.string "{STR_VAR_1}의 어드바이스를 받아서\n"
	.string "{STR_VAR_2}{K_EULREUL} 지닌 {STR_VAR_3}{K_WAGWA}$"
	// いから アドバイスを うけてｎ
	// うを もつ えと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon2Ask:: @ 82441F7
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있어요\p"
	.string "부탁드립니다!\n"
	.string "저하고 팀이 되어주세요!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Accept:: @ 824422E
	.string "감사합니다!\n"
	.string "바로 접수하고 올게요!$"
	// ありがとうございます!ｎ
	// さっそく うけつけを すませてきますね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Reject:: @ 8244255
	.string "{PLAYER}님과\n"
	.string "꼭 팀이 되고 싶었어요...$"
	// あさんとｎ
	// ぜひ タッグを くみたかったです……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Intro:: @ 8244286
	.string "저는\n"
	.string "{STR_VAR_1}님의 {STR_VAR_2}번째 제자\l"
	.string "{STR_VAR_3}{K_I}라고 합니다$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon1:: @ 82442B2
	.string "{STR_VAR_1}의 어드바이스를 받아서\n"
	.string "{STR_VAR_2}{K_EULREUL} 지닌 {STR_VAR_3}{K_WAGWA}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon2Ask:: @ 82442E4
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있어요\p"
	.string "부탁드립니다!\n"
	.string "저하고 팀이 되어주세요!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Accept:: @ 8244313
	.string "감사합니다!\n"
	.string "바로 접수하고 오겠습니다!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Reject:: @ 8244350
	.string "{PLAYER}님과\n"
	.string "꼭 팀이 되고 싶었어요...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Intro:: @ 8244383
	.string "저는 {STR_VAR_3}{K_I}고\n"
	.string "{STR_VAR_1}님의 {STR_VAR_2}번째 제자입니다\p"
	.string "훌쩍...\p"
	.string "죄송합니다!\n"
	.string "긴장해서 그런지 눈물이...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon1:: @ 82443E7
	.string "저 {STR_VAR_3}님의 어드바이스로\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon2Ask:: @ 8244413
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있습니다\p"
	.string "훌쩍... 저 저하고\n"
	.string "팀이 되어주세요!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Accept:: @ 824444B
	.string "앗 정말인가요!\n"
	.string "해냈다! 기뻐요! 와하하!\p"
	.string "아... 죄송합니다\n"
	.string "너무 기뻐서 눈물이...\p"
	.string "바 바로 접수처에\n"
	.string "갔다 올 테니 기다려 주세요!$"
	// え- ほんとですか!ｎ
	// やった! うれしいよう! うぉぉ-ん!ｐ
	// あ…… ごめん なさいｎ
	// うれしくて なみだが……ｐ
	// さっ さっそく うけつけにｎ
	// いってきますから まってて ください!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Reject:: @ 82444D6
	.string "그 그럴 수가...\n"
	.string "으 으으 으아-앙!$"
	// そ そんな……ｎ
	// う うう うわ-ん!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Intro:: @ 82444EF
	.string "안녕! 나는 {STR_VAR_3}!\n"
	.string "{STR_VAR_1}님의 {STR_VAR_2}번째 제자야!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon1:: @ 824451E
	.string "{STR_VAR_3}님한테 추천받아서\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon2Ask:: @ 8244549
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_IGA}\n"
	.string "있는데 괜찮지?\l"
	.string "저기 나하고 같이!\l"
	.string "팀이 되어주라!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Accept:: @ 824459B
	.string "야호 해냈다!\n"
	.string "그럼 내가\l"
	.string "접수처에 갔다 올게!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Reject:: @ 82445C5
	.string "어라 어째서?\n"
	.string "{PLAYER}하고 팀이 되고 싶었는데-$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Intro:: @ 82445E8
	.string "제가 그 유명한\n"
	.string "{STR_VAR_1}의 {STR_VAR_2}번째 제자\l"
	.string "{STR_VAR_3}입니다!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon1:: @ 8244618
	.string "{STR_VAR_3}님한테서\n"
	.string "어드바이스를 받아\l"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon2Ask:: @ 8244643
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있죠\p"
	.string "부탁드립니다!\n"
	.string "저하고 팀이 되어주세요!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Accept:: @ 824468F
	.string "감사합니다!\n"
	.string "바로 접수처에 갔다 올게요!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Reject:: @ 82446B4
	.string "{PLAYER}님과 꼭\n"
	.string "팀이 되고 싶었어요...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Intro:: @ 82446E5
	.string "저... 저 같은 거에\n"
	.string "말을 걸어주셔서 매우 기뻐요\l"
	.string "저는 {STR_VAR_3}입니다\l"
	.string "{STR_VAR_1}님의 {STR_VAR_2}번째 제자죠...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon1:: @ 824474D
	.string "{STR_VAR_3}님이 저 같은 거에게도\n"
	.string "어드바이스를 해주셔서\l"
	.string "{STR_VAR_1}{K_EUNNEUN} 지닌 {STR_VAR_2}{K_WAGWA}...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon2Ask:: @ 824479E
	.string "{STR_VAR_1}{K_EUNNEUN} 지닌 {STR_VAR_2}{K_EUNNEUN}\n"
	.string "데리고 있습니다... 황송하지만\p"
	.string "무리라고 생각하지만...\n"
	.string "저와 팀이 되어주실 수 있나요?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Accept:: @ 824480C
	.string "정말요? 믿어지지 않네요!\n"
	.string "저 같은 거와 팀이 되어주시다니!\l"
	.string "...열심히 하겠습니다!\p"
	.string "저... 저로 괜찮다면\n"
	.string "지금부터 접수처에 갔다 오겠습니다!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Reject:: @ 82448A7
	.string "여 역시...\n"
	.string "저 같은 건 안되는 거군요$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Intro:: @ 82448CD
	.string "저는 {STR_VAR_3}\n"
	.string "{STR_VAR_1}님의 {STR_VAR_2}번째 제자입니다!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon1:: @ 82448F5
	.string "{STR_VAR_3}님이 말해 주셔서\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon2Ask:: @ 8244939
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있습니다!\l"
	.string "나쁘지 않죠?\l"
	.string "저와 팀이 되실래요?$"
	// §い つかいの §うをｎ
	// もって いるわけ!ｌ
	// わるくない でしょ?ｌ
	// あなたと タッグを くんで あげようか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Accept:: @ 8244989
	.string "음 그럼 잘 부탁드려요\n"
	.string "발목을 잡으시면 안돼요!\l"
	.string "바로 접수처에 다녀오겠습니다!$"
	// うん じゃあ よろしくねｎ
	// わたしの あしを ひっぱらないでよね!ｌ
	// さっそく うけつけに いってくるわ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Reject:: @ 82449E6
	.string "어라? 어째서 거절하는 거죠?\n"
	.string "보는 눈이 없으시군요$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Intro:: @ 8244A23
	.string "난 트라이애슬리트 {STR_VAR_3}!\n"
	.string "조깅 트레이닝 래핑으로\l"
	.string "매일을 바쁘게 보내는 와중에도\l"
	.string "{STR_VAR_1}의 {STR_VAR_2}번째 제자를 하고 있어!$"
	// オレは トライアスリ-トの §え!ｎ
	// ジョギング トレ-ニング ラッピングとｌ
	// まいにち いそがしい なかｌ
	// §いの §うばんでし やってる!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon1:: @ 8244AA9
	.string "{STR_VAR_3}의 추천!\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}$"
	// §えの オススメ!ｎ
	// §いを もつ §うと

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon2Ask:: @ 8244AD6
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "바쁜 와중에도 열심히 키우고 있지!\p"
	.string "나랑 태그를 맺고 힘내자고!$"
	// §いを もつ §うをｎ
	// いそがしい なか がんばって そだてたぜ!ｐ
	// オレと タッグを くんで がんばろうぜ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Accept:: @ 8244B52
	.string "땡큐 그렇게 나와야지!\n"
	.string "그럼 나 접수처에 말하고 올게!$"
	// サンキュ- そう こなくっちゃ!ｎ
	// んじゃ オレ うけつけを すませてくるわ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Reject:: @ 8244B93
	.string "이봐이봐 바쁜 와중에도 왔는데\n"
	.string "그건 아니지!$"
	// おいおい いそがしい なか きたのにｎ
	// そりゃ ないぜ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Intro:: @ 8244BD2
	.string "하-이! 상태는 어때?\n"
	.string "{STR_VAR_1}님의 {STR_VAR_2}번째\l"
	.string "제자 트레이너 {STR_VAR_3}{K_I}야 잘 부탁해!$"
	// ハ-イ! ちょうしは どう?ｎ
	// §いさんの §うばんのｌ
	// でしトレ-ナ- §えよ よろしくぅ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon1:: @ 8244C18
	.string "들어봐 들어봐! {STR_VAR_3}님이\n"
	.string "추천해주신 포켓몬은 말이지\l"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_I}랑$"
	// きいてきいて! §えさんがｎ
	// おすすめ してくれた ポケモンはねｌ
	// §いを もつ §うと

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon2Ask:: @ 8244C6E
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_I}야\n"
	.string "물론 제대로 키웠어!\p"
	.string "그러니까 나랑 팀을 맺지 않을래?\n"
	.string "분명 좋은 느낌일 거야!$"
	// §いを もつ §うなのｎ
	// もちろん バッチリ そだてたわ!ｐ
	// というわけで わたしと くまない?ｎ
	// きっと いいカンジよ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Accept:: @ 8244CD6
	.string "오예- 재밌어질 것 같아-!\n"
	.string "그럼 내가 접수처에 갔다 올게!$"
	// わ-い たのしく なりそう-!ｎ
	// じゃ わたしが うけつけに いってくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Reject:: @ 8244D07
	.string "정말- 쩨쩨하기는!\n"
	.string "추천받은 조합이라고!$"
	// も- いじわる!ｎ
	// わたし オススメなのに!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Intro:: @ 8244D36
	.string "{STR_VAR_3}{K_I}라고 합니다\n"
	.string "전 {STR_VAR_1}님의 {STR_VAR_2}번째\l"
	.string "제자예요...$"
	// §えと もうしますｎ
	// わたくし §いさまの §うばんのｌ
	// でしで ございますの……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon1:: @ 8244D82
	.string "{STR_VAR_3}님의 가르침을 받아\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_I}랑...$"
	// §えさまに おしえを こいｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon2Ask:: @ 8244DC6
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "키워왔어요!\p"
	.string "부탁드립니다 저랑 태그를\n"
	.string "맺어주세요!$"
	// §いを もつ §うをｎ
	// そだて あげましたの!ｐ
	// おねがい わたくしと タッグをｎ
	// くんで くださると おっしゃって!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Accept:: @ 8244DFE
	.string "기 기뻐요...\n"
	.string "저 전력으로 임할게요!\p"
	.string "물론 접수처는 제가 갔다 오겠습니다!\n"
	.string "잠깐 기다려 주세요$"
	// うっ うれしい ですわ……ｎ
	// わたくし ぜんりょくで つとめますわ!ｐ
	// もちろん うけつけは わたくしが!ｎ
	// すこし おまちくださいませ

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Reject:: @ 8244E5B
	.string "{PLAYER}님과\n"
	.string "꼭 태그를 맺고 싶었어요...$"
	// §あさんとｎ
	// ぜひ タッグを くみたかったです……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Intro:: @ 8244E7E
	.string "꺄-! 말 걸었다!\n"
	.string "가 감격했어...!\p"
	.string "저! {STR_VAR_3}{K_I}라고 해요!\n"
	.string "{STR_VAR_1} 선생님의\l"
	.string "{STR_VAR_2}번째 제자죠!$"
	// キャ-! はなしかけられたっ!ｎ
	// かっ かんげきっ……!ｐ
	// わたし! §えと いいますっ!ｎ
	// §い せんせいのｌ
	// §うばん でし ですっ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon1:: @ 8244ECA
	.string "{STR_VAR_3} 선생님의 어드바이스로\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_I}랑$"
	// §え せんせいの アドバイスでｎ
	// §いをもつ §うちゃんと

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon2Ask:: @ 8244EF4
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "키웠답니다-!\p"
	.string "저기 부탁이 있어요!\n"
	.string "저랑 태그를 맺어주셨으면 해요!$"
	// §いをもつ §うちゃんをｎ
	// そだてました-っ!ｐ
	// あの おねがいが!ｎ
	// わたしと タッグをくんで ほしいのですっ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Accept:: @ 8244F4F
	.string "꺄-! 가 감격했어...!\n"
	.string "정말 감사합니다!\l"
	.string "그럼 접수처에 갔다 올게요!$"
	// キャ-! かっ かんげきっ……!ｎ
	// おありがとう ございますう!ｌ
	// ではっ うけつけを して まいりますっ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Reject:: @ 8244F98
	.string "우와아아아!\n"
	.string "피도 눈물도 없군요! 하지만 멋져요!$"
	// うっわあああ!ｎ
	// ちも なみだも ないですねっ! でもステキ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Intro:: @ 8244FD3
	.string "이-예이! {STR_VAR_1}님의\n"
	.string "{STR_VAR_2}번째 제자인 아저씨\p"
	.string "{STR_VAR_3}입니다 헬로 헬로!$"
	// いえ-い! §いさんのｎ
	// §うばん でしの おじさんはｌ
	// §えです ハロウ ハロウ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon1:: @ 8245013
	.string "{STR_VAR_3} 티처의 추천으로\n"
	.string "{STR_VAR_1} 마스터 {STR_VAR_2}{K_I}랑$"
	// §え ティ-チャ- おすすめのｎ
	// §い マスタ- §うと

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon2Ask:: @ 824503D
	.string "{STR_VAR_1} 마스터 {STR_VAR_2}{K_EULREUL}\n"
	.string "트레이닝시켰다구-!\l"
	.string "굿 타이밍이네!\l"
	.string "당연히 아저씨랑 태그를 맺을 거지?$"
	// §い マスタ- §うをｎ
	// トレイン したんだよ-!ｌ
	// グッドタイミングだね!ｌ
	// もちろん おじさんと タッグを くむだろ?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Accept:: @ 8245087
	.string "오케이 엑설런트!\n"
	.string "그럼 팟 하고 접수처에 갔다 올게$"
	// オ-ケイ エクセレント!ｎ
	// じゃ バ-っと うけつけを すませてくるね

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Reject:: @ 82450C0
	.string "크윽-!\n"
	.string "{PLAYER}씨는 쿨하구만!$"
	// ぐわ-っ!ｎ
	// §あさん ってのは ク-ルだね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Intro:: @ 82450E6
	.string "어 어이 큰일이야!\n"
	.string "배틀타워 오늘로 마지막인가봐!\p"
	.string "...... ...... ......\n"
	.string "농담이야 거짓말이라구 거짓말!\p"
	.string "나는 {STR_VAR_3}{K_I}라고 해\n"
	.string "{STR_VAR_1}의 1000번째 제자야!\l"
	.string "거짓말이고 사실은 {STR_VAR_2}번째!$"
	// お おいっ たいへんだ!ｎ
	// バトルタワ- きょうで おしまいらしいぞ!ｐ
	// …… …… ……ｎ
	// なんてね うっそ うそ!ｐ
	// おいらは §え って いうんだｎ
	// §いの 1000ばんめの でしだ!ｌ
	// うそ ほんとは §うばん!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon1:: @ 8245196
	.string "{STR_VAR_3}{K_IGA} 어드바이스를 줘서 말이지\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_I}랑$"
	// §えが アドバイスを くれてねｎ
	// §いを もつ §うとね

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon2Ask:: @ 82451BD
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "10마리씩 가지고 있어-!\l"
	.string "거짓말이고 사실은 1마리씩!\p"
	.string "어때? 이런 나와\n"
	.string "태그배틀하지 않을래?$"
	// §いを もつ §うをねｎ
	// 10ぴきずつ もって いま-す!ｌ
	// うそ ほんとは 1ぴきずつだよ!ｐ
	// ひとつ どうだろ? こんな おいらとｎ
	// タッグバトルを して みないかな?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Accept:: @ 824522F
	.string "앗싸-!\n"
	.string "답례로 포켓몬 줄게!\p"
	.string "물론 농담이고...\n"
	.string "일단 접수처에 갔다 올게!$"
	// やった-!ｎ
	// おれいに ポケモン あげちゃおう!ｐ
	// なんて じょうだん だけど……ｎ
	// とりあえず うけつけを すませてくるよ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Reject:: @ 824529A
	.string "그런 차가운 말을 하면\n"
	.string "배틀타워를 부숴버릴 거야!\p"
	.string "물론 거짓말이지롱!$"
	// そんな つめたい こと いうとｎ
	// バトルタワ-を こわして しまうぞ!ｐ
	// なんてね うそ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Intro:: @ 82452EF
	.string "안.녕.하.세.요!\n"
	.string "오 안녕하시군요!\p"
	.string "저는 경쾌한 선원 {STR_VAR_3}!\n"
	.string "{STR_VAR_1}님의 {STR_VAR_2}번째 제자!$"
	// ご®き®げ®ん®よ®う!ｎ
	// は-い ごきげんよう!ｐ
	// わしは ノリノリ ふなのり §え!ｎ
	// §いさんの §うばんの でしだよ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon1:: @ 82453B4
	.string "{STR_VAR_3}님의 어드바이스로 키운\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}$"
	// §えさん アドバイスの たまものｎ
	// §いを もつ §うと

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon2Ask:: @ 8245406
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_IGA}\n"
	.string "제 자랑스러운 포켓몬입니다!\p"
	.string "자 이 만남을 기념하여\n"
	.string "저와 태그배틀을 해주시죠!$"
	// §いを もつ §うがｎ
	// わしの じまんの ポケモン!ｐ
	// さあ この であいを きねんしてｎ
	// わしと タッグバトルを やってください!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Accept:: @ 8245464
	.string "오우오우! 좋다 이겁니까\n"
	.string "잘 부탁드린다구요!\l"
	.string "그럼 접수처는 제가 다녀오죠!$"
	// ようよう! ノリが いいねｎ
	// よろしく たのみますよ!ｌ
	// じゃ うけつけは わしが いってくるよ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Reject:: @ 82454A3
	.string "그럴 수가 {PLAYER}님!\n"
	.string "설마 내빼시는 겁니까!$"
	// そんな §あさん!ｎ
	// ノリが わるいじゃ ないか!$

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Intro:: @ 82454D6
	.string "이야아앗훠어어우우우우!\n"
	.string "아 도망치지 마 돌아가지 마!\p"
	.string "안녕 난 {STR_VAR_3}!\n"
	.string "{STR_VAR_1}님의 {STR_VAR_2}번째 제자야!$"
	// イャァアッホオオォォウウ!ｎ
	// あ にげないでェ かえらないでェ!ｐ
	// オスっ オレっ §え!ｎ
	// §いさんの §うばん でしなのさ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon1:: @ 8245535
	.string "{STR_VAR_3}님이 나한테!\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}!$"
	// §えさんったら オレに!ｎ
	// §いを もつ §うと!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon2Ask:: @ 824555F
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}!\n"
	.string "쓰라고 해서 그렇게 했어!\p"
	.string "아니 이렇게 말해서 어쩌자는 거야?\n"
	.string "바로 부탁해 봐야 되나?\p"
	.string "부탁할게!\n"
	.string "나랑 태그를 맺어줘어어!$"
	// §いを もつ §うを!ｎ
	// つかえって いうから そうしたぜエェ!ｐ
	// って ことで どうする オレ?ｎ
	// さっそく たのんでみる?ｐ
	// おねがいです!ｎ
	// オレと タッグを くんでエェ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Accept:: @ 82455EC
	.string "앗싸 럭키 엄청 기쁘다고!!\n"
	.string "바로 접수처에 다녀온다!?\l"
	.string "그럼 잠깐만 기다려!$"
	// やったラッキ- うれし-よ オレ!!ｎ
	// さっそく うけつけに いってくる!?ｌ
	// じゃ ちょっと まっててェ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Reject:: @ 8245656
	.string "아니 거절하는 거야!?\n"
	.string "{PLAYER}님 까다롭네!$"
	// って ことわられてる オレっ!?ｎ
	// §あさん つれないよォ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Intro:: @ 824568A
	.string "콜록!\p"
	.string "앗 미안 감기 걸렸거든...\n"
	.string "포켓몬은 건강하니까 괜찮아\p"
	.string "난 {STR_VAR_3}\n"
	.string "{STR_VAR_1}님의 {STR_VAR_2}번째 제자야\l"
	.string "...콜록 콜록 잘 부탁해!$"
	// ゴホっ!ｐ
	// あっ ゴメン カゼ ひいてて……ｎ
	// ポケモンは げんきだから ダイジョブだよｐ
	// おれは §えｎ
	// §いさんの §うばんでしだよｌ
	// ……ゴホっ ゴホっ よろしく!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon1:: @ 82456F5
	.string "{STR_VAR_3}님의 어드바이스로\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// §えさんの アドバイスでｎ
	// §いを もつ §うとさ……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon2Ask:: @ 8245740
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "비 오는 날에도 바람 부는 날에도 키워왔어\l"
	.string "...그래서 감기에 걸린 거겠지 분명\p"
	.string "뭐 일단은 그래\n"
	.string "이런 나하고 함께 배틀하지 않을래?$"
	// §いを もつ §うをｎ
	// あめのひも かぜのひも そだてあげたよｌ
	// ……それで カゼを ひいたんだ きっとｐ
	// まあ そういう わけだからさｎ
	// こんな おれと いっしょに くまないかい?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Accept:: @ 82457D9
	.string "고맙고 미안해\n"
	.string "...콜록 콜록!\l"
	.string "접수처에 갔다 올 테니까...\l"
	.string "콜록 기다려줘$"
	// ありがとう わるいねｎ
	// ……ゴホ ゴホ!ｌ
	// うけつけを すませてくるから……ｌ
	// ゴホ まっててね

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Reject:: @ 824581F
	.string "에- 어째서!\n"
	.string "{PLAYER}님과 난 좋은 콤비가 될 텐데$"
	// え- なんで!ｎ
	// §あさんと オレって いいけどなあ

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Intro:: @ 8245851
	.string "앗 아 안녕!\n"
	.string "부끄럽네\p"
	.string "저기 난 {STR_VAR_3}{K_I}야! {STR_VAR_1}님의\n"
	.string "{STR_VAR_2}번째 제자를 하고 있어...!$"
	// あっ ど どうも!ｎ
	// てれるなあｐ
	// あの §えです! §いさんのｎ
	// §うばんの でし やってます……!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon1:: @ 824589C
	.string "{STR_VAR_3}님이 좋다고 해서\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_I}랑...$"
	// §えさんが よいと いったのでｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon2Ask:: @ 82458CE
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "키우고 있어... 부끄럽지만\p"
	.string "그 부끄럽지만 나하고\n"
	.string "태그를 맺어줄 수 있어...?$"
	// §いを もつ §うをｎ
	// そだててるんだ…… はずかしながらｐ
	// その はずかしい けど ワシと……ｎ
	// タッグを くんで もらえる かな……?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Accept:: @ 8245923
	.string "고 고마워!\n"
	.string "부끄럽지만 힘내볼게\p"
	.string "그럼... 저 접수처에 갔다 올게$"
	// あ ありがとう!ｎ
	// はずかしい けど がんばって みるよｐ
	// じゃ…… う うけつけ してくるね

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Reject:: @ 824597F
	.string "거 거절하지 말아줘!\n"
	.string "나한테 창피 주지 마!$"
	// こ ことわらないでくれ!ｎ
	// ワシに はじを かかせないで くれ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Intro:: @ 82459BE
	.string "난 {STR_VAR_3}{K_I}다\n"
	.string "거짓말이 아니라!\l"
	.string "{STR_VAR_1}의 {STR_VAR_2}번째 제자지$"
	// わたしは §えだｎ
	// うそじゃない!ｌ
	// §いさんの §うばんの でしだ

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon1:: @ 82459F7
	.string "{STR_VAR_3}님한테 추천을 받았는데\n"
	.string "역시 정말로 좋은 것 같아서\l"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}$"
	// §えさんから すすめられてｎ
	// どうやら ほんき みたい だったからｌ
	// §いを もつ §うと

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon2Ask:: @ 8245A5F
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 왔지 정말이라고!\p"
	.string "그나저나 만약 괜찮다면 날\n"
	.string "네 파트너로 인정해줬으면 하는데$"
	// §いを もつ §うをｎ
	// つれているんだ ほんとうだよ!ｐ
	// ところで もし よかったら わたしをｎ
	// キミの パ-トナ-に みとめて ほしい

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Accept:: @ 8245AB4
	.string "정말로 인정해 주는 건가?\n"
	.string "거짓말이라면 원망할 거다\p"
	.string "아니 진심이라면 좋지 미안하다\n"
	.string "바로 접수처에 갔다 오지$"
	// ほんとうに みとめて くれるのかね?ｎ
	// うそだったら いやすぎる からなｐ
	// いや ほんとうなら いいんだ すまなかったｎ
	// さっそく うけつけを すませてくる

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Reject:: @ 8245B3E
	.string "어? 왜 거절하는 건가?\n"
	.string "질 나쁜 농담인 거겠지?$"
	// え? なぜ ことわるのかね?ｎ
	// わるい じょうだん では ないのかね?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassIntro:: @ 8245B79
	.string "난\n"
	.string	"짧은 치마 {STR_VAR_1}!$"
	// わたしｎ
	// ミニスカ-ト §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon1:: @ 8245B91
	.string "난 말이지...\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わたしはね……ｎ
	// §いを つかう §うとね……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon2Ask:: @ 8245BBD
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있어!\p"
	.string "어때?\n"
	.string "파트너가 되어줄래?$"
	// §いを つかう §うをｎ
	// つれて あるいているの!ｐ
	// どう?ｎ
	// パ-トナ-に なってくれない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassAccept:: @ 8245C05
	.string "고마워-!\n"
	.string "지금 등록하고 올게$"
	// ありがとう-!ｎ
	// いまから とうろく してくるわね

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassReject:: @ 8245C2D
	.string "내 파트너가 되지 않겠다니\n"
	.string "분명 후회할 거야!$"
	// わたしの パ-トナ-に ならないなんてｎ
	// きっと こうかい するから!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterIntro:: @ 8245C66
	.string "저기 있잖아!\p"
	.string "난\n"
	.string "반바지 꼬마 {STR_VAR_1}{K_I}야!$"
	// あのね!ｐ
	// ぼくはｎ
	// たんパンこぞう §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon1:: @ 8245C7F
	.string "난 말이지...\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// ぼくはね……ｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon2Ask:: @ 8245CAC
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_EULREUL}\n"
	.string "가지고 있어!\p"
	.string "저기 저기\n"
	.string "같이 태그를 맺지 않을래?$"
	// §いを つかう §うをｎ
	// もっているよ!ｐ
	// ねぇねぇｎ
	// いっしょに タッグを くもうよ?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterAccept:: @ 8245CE6
	.string "앗싸-!\n"
	.string "접수처에 등록하고 올게-!$"
	// やった-!ｎ
	// うけつけで とうろく してくるね-!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterReject:: @ 8245D07
	.string "내 포켓몬과 태그를 맺으면\n"
	.string "분명 강할 텐데-!$"
	// ぼくの ポケモンと タッグを くめばｎ
	// きっと つよいのに-!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerIntro:: @ 8245D4B
	.string "야호!\p"
	.string "전\n"
	.string "등산가 {STR_VAR_1}입니다!$"
	// ヤッホ-!ｐ
	// わしｎ
	// やまおとこ §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon1:: @ 8245D60
	.string "전\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// わしｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon2Ask:: @ 8245D8D
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있지요!\p"
	.string "어떻습니까?\n"
	.string "함께 태그를 맺지 않겠습니까?$"
	// §いを もつ §うをｎ
	// つれて あるいています!ｐ
	// どうですかな?ｎ
	// いっしょに タッグを くみませんか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerAccept:: @ 8245DC7
	.string "야호!\p"
	.string "지금 접수처에서\n"
	.string "등록하고 오겠습니다$"
	// ヤッホ-!ｐ
	// いまから うけつけでｎ
	// とうろくを すませてきますよ

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerReject:: @ 8245DF0
	.string "당신과 함께\n"
	.string "배틀하고 싶었어요$"
	// きみと いっしょにｎ
	// バトルを したかったです

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyIntro:: @ 8245E20
	.string "안녕!\p"
	.string "난\n"
	.string "아가씨 {STR_VAR_1}{K_I}야!$"
	// こんにちは!ｐ
	// わたしｎ
	// おとなのおねえさん §いよ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon1:: @ 8245E41
	.string "난\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わたしｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon2Ask:: @ 8245E78
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_EULREUL}\n"
	.string "키우고 있어!\p"
	.string "어때?\n"
	.string "함께 태그를 맺어보지 않을래?$"
	// §いを つかう §うをｎ
	// そだてているのよ!ｐ
	// どう?ｎ
	// いっしょに タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyAccept:: @ 8245EBD
	.string "기쁜걸!\p"
	.string "바로 접수처에 갔다 올게$"
	// うれしい!ｐ
	// すぐに とうろくを すませるわね

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyReject:: @ 8245EEC
	.string "유감이네!\p"
	.string "당신과 내가\n"
	.string "팀이 된다면 최고일 텐데...$"
	// ざんねんね!ｐ
	// あなたと わたしがｎ
	// くんだら さいこう だったのに……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanIntro:: @ 8245F2B
	.string "요-!\p"
	.string "난\n"
	.string "낚시꾼 {STR_VAR_1}!$"
	// よ-!ｐ
	// わしｎ
	// つりびと §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon1:: @ 8245F58
	.string "나는\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わしはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon2Ask:: @ 8245F87
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있어\p"
	.string "어때?\n"
	.string "같이 배틀해보지 않을래?$"
	// §いを つかう §うをｎ
	// つれているぞｐ
	// どうだね?ｎ
	// いっしょに たたかうかね?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanAccept:: @ 8245FC6
	.string "좋아 좋아!\n"
	.string "맡겨 둬-\p"
	.string "지금 등록하고 올게!$"
	// よしよし!ｎ
	// まかせとけ-ｐ
	// いまから とうろくを するからな!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanReject:: @ 8246002
	.string "너와 내가 같이한다면\n"
	.string "딱 좋을 거 같았는데...$"
	// きみと わしの あいしょうはｎ
	// バッチリ だったのにな……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyIntro:: @ 8246020
	.string "전\n"
	.string "아기씨\l"
	.string "{STR_VAR_1}{K_I}라고 합니다!$"
	// わたくしｎ
	// おじょうさま §いとｌ
	// もうします!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon1:: @ 8246051
	.string "저는\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わたくしｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon2Ask:: @ 8246082
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있어요\p"
	.string "어떠신가요?\p"
	.string "저와 함께\n"
	.string "태그를 맺어보지 않겠나요?$"
	// §いを つかう §うをｎ
	// つれていますのｐ
	// どうですか?ｐ
	// わたくしと いっしょにｎ
	// タッグを くんで いただけませんか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyAccept:: @ 82460D5
	.string "감사합니다!\p"
	.string "그럼 전\n"
	.string "등록하고 올게요$"
	// ありがとうございます!ｐ
	// では わたくしは ｎ
	// とうろくを すませてきますわ

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyReject:: @ 824610D
	.string "제 파트너가 되지 않은 걸\n"
	.string "분명 후회하시게 될걸요$"
	// わたくしの パ-トナ-に ならないとｎ
	// きっと こうかい しますわよ

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFIntro:: @ 824614A
	.string "난\n"
	.string "트라이애슬리트 {STR_VAR_1}!$"
	// わたしｎ
	// トライアスリ-ト §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon1:: @ 824615D
	.string "난 말이지...\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// わたしはね……ｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon2Ask:: @ 824617D
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "지니고 있어!\p"
	.string "부탁이야!\n"
	.string "함께 태그를 맺지 않을래?$"
	// §いを もつ §うをｎ
	// もっているの!ｐ
	// おねがい!ｎ
	// いっしょに タッグを くんでよ?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFAccept:: @ 82461C7
	.string "고마워-!\n"
	.string "접수처에 등록하고 올게-$"
	// ありがとう-!ｎ
	// うけつけで とうろく してくる-

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFReject:: @ 82461F5
	.string "나와 태그를 맺으면\n"
	.string "분명 강할 텐데-!$"
	// わたしと タッグを くんだらｎ
	// っと つよいのに-!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherIntro:: @ 824622A
	.string "여어!\p"
	.string "난\n"
	.string "곤충채집소년 {STR_VAR_1}{K_I}야!$"
	// やあ!ｐ
	// ぼくｎ
	// むしとりしょうねん §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon1:: @ 8246244
	.string "난\n"
	.string "{STR_VAR_1}{K_EULREUL} 배운 {STR_VAR_2}{K_WAGWA}...$"
	// ぼくｎ
	// §いを おぼえた §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon2Ask:: @ 824626E
	.string "{STR_VAR_1}{K_EULREUL} 배운 {STR_VAR_2}{K_EULREUL}\n"
	.string "지니고 있어!\p"
	.string "저기\n"
	.string "나랑 같이 태그를 맺지 않을래?$"
	// §いを おぼえた §うをｎ
	// もっているよ!ｐ
	// ね-?ｎ
	// ぼくと いっしょに タッグを くまない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherAccept:: @ 82462AA
	.string "앗싸!\p"
	.string "그럼 지금부터 접수처에\n"
	.string "등록하고 올게!$"
	// やったね!ｐ
	// じゃ いまから うけつけでｎ
	// とうろくを すませてくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherReject:: @ 82462E4
	.string "내 포켓몬 최고인데!\n"
	.string "후회하지 마$"
	// ぼくの ポケモン さいこう なのに!ｎ
	// こうかい しないでよ

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMIntro:: @ 824631F
	.string "안녕하세요!\p"
	.string "전\n"
	.string "학원 끝난 아이 {STR_VAR_1}입니다$"
	// こんにちは!ｐ
	// ぼくはｎ
	// じゅくがえり §い です

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon1:: @ 824633C
	.string "저는\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// ぼくはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon2Ask:: @ 824636B
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_EULREUL}\n"
	.string "키우고 있습니다!\p"
	.string "어떤가요?\p"
	.string "저와\n"
	.string "태그를 맺어보지 않을래요?$"
	// §いを つかう §うをｎ
	// そだてています!ｐ
	// どうです?ｐ
	// ぼくとｎ
	// いっしょに タッグを くみませんか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMAccept:: @ 82463C5
	.string "감사합니다!\p"
	.string "그럼\n"
	.string "접수처에 등록하고 올게요!$"
	// ありがとうございます!ｐ
	// ではｎ
	// うけつけで とうろくを すませてきますね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMReject:: @ 82463FF
	.string "유감이군요...\p"
	.string "당신과 함께 태그를 맺어서\n"
	.string "공부하고 싶었어요...$"
	// ざんねんです……ｐ
	// きみと いっしょに タッグを くんでｎ
	// べんきょう したかったです……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyIntro:: @ 8246449
	.string "Yo! Let me tell you who I am!\n"
	.string "I'm RICH BOY {STR_VAR_1}!$"
	// よう!ｐ
	// オレｎおぼっちゃま §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon1:: @ 8246478
	.string "Guess what I got!\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"
	// オレｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon2Ask:: @ 824649D
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "I'm willing to offer you the chance\n"
	.string "to be in a tag team with me.$"
	// §いを もつ §うをｎ
	// もっているんだぜ!ｐ
	// オレ いっしょにｎ
	// タッグを くんでもいいぜ?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyAccept:: @ 82464EE
	.string "Smart move!\p"
	.string "I'll finish up the registration\n"
	.string "process quick!$"
	// よし!ｐ
	// じゃあ いまからｎ
	// うけつけで とうろくを すませてくるぜ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyReject:: @ 8246529
	.string "You'd turn me of all people down?\n"
	.string "You'll regret that decision for sure!$"
	// オレと タッグを くまない なんてｎ
	// きっと こうかい するぜ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltIntro:: @ 8246571
	.string "Hiyah!\n"
	.string "I am BLACK BELT {STR_VAR_1}.$"
	// オッス!ｐ
	// カラテおう §いｎと もうします

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon1:: @ 824658C
	.string "As my companions, I have\n"
	.string "one {STR_VAR_2} using {STR_VAR_1}$"
	// いま わたくしｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon2Ask:: @ 82465B5
	.string "and one {STR_VAR_2} using\n"
	.string "{STR_VAR_1}.\p"
	.string "Please, grant me my wish!\n"
	.string "Allow me to be your tag partner!$"
	// §いを もつ §うをｎ
	// つれております!ｐ
	// おねがいします!ｐ
	// わたくしとｎ
	// タッグを くんで くれませんか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltAccept:: @ 8246605
	.string "Hiyah!\n"
	.string "I will go register forthwith!$"
	// オッス!ｐ
	// さっそくｎ
	// うけつけに とうろく してまいります!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltReject:: @ 824662A
	.string "I see… I hope for an opportunity\n"
	.string "the next time we meet…$"
	// オッス……ｐ
	// つぎの きかいはｎ
	// ぜひ タッグを くんでください……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFIntro:: @ 8246662
	.string "Hi, there!\n"
	.string "I'm {STR_VAR_1}, and I'm a TUBER!$"
	// こんにちは!ｐ
	// わたしｎ
	// うきわガ-ル §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon1:: @ 8246686
	.string "I'll tell you what I have.\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"
	// わたしｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon2Ask:: @ 82466B4
	.string "one {STR_VAR_2} with {STR_VAR_1}!\n"
	.string "May I please be on your tag team?$"
	// §いを もつ §うをｎ
	// つれているの!ｐ
	// ねぇ?ｐ
	// いっしょにｎ
	// タッグを くんでよ-?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFAccept:: @ 82466E6
	.string "Thank you!\n"
	.string "I'll go register us now!$"
	// ありがとう-!ｐ
	// じゃあ いまからｎ
	// うけつけで とうろくを すませてくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFReject:: @ 824670A
	.string "If we'd become partners, we could\n"
	.string "have been so strong!$"
	// わたしと タッグを くんだらｎ
	// とっても つよかったのに-!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacIntro:: @ 8246741
	.string "Greetings…\n"
	.string "I am HEX MANIAC {STR_VAR_1}…$"
	// こんにちは……ｐ
	// オカルトマニア §いとｎ
	// もうします……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon1:: @ 8246760
	.string "I bear with me one {STR_VAR_1}-using\n"
	.string "{STR_VAR_2} together with one$"
	// わたくし……ｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon2Ask:: @ 8246791
	.string "{STR_VAR_1}-using {STR_VAR_2}…\p"
	.string "I beseech you…\n"
	.string "Join me in a tag team…$"
	// §いを もつ §うをｎ
	// もっております……ｐ
	// どうか わたくしとｎ
	// タッグを くんでいただけませんか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacAccept:: @ 82467C4
	.string "I thank you…\n"
	.string "I shall register us…$"
	// ありがとうございます……ｎ
	// うけつけで とうろくを してきます……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacReject:: @ 82467E6
	.string "I so longed to join you…$"
	// あなたと タッグをｎ
	// くみたかったです……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMIntro:: @ 82467FF
	.string "How do you do? I'm {STR_VAR_1},\n"
	.string "and I'm a POKéMON BREEDER!$"
	// やあ!ｐ
	// ぼくｎ
	// ポケモンブリ-ダ- §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon1:: @ 8246831
	.string "I'm raising a couple good ones!\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"
	// ぼくは いまｎ
	// §いを もつ §うとね……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon2Ask:: @ 8246864
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "How about it?\n"
	.string "Feel like making a tag team with me?$"
	// §いを もつ §うをｎ
	// そだてているんだ!ｐ
	// どう?ｐ
	// ぼくとｎ
	// いっしょに タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMAccept:: @ 82468A7
	.string "Thank you kindly!\p"
	.string "I'll go take care of the registration\n"
	.string "stuff, so you wait right here!$"
	// ありがとう!ｐ
	// では さっそくｎ
	// うけつけで とうろくを すませてきますね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMReject:: @ 82468FE
	.string "I was looking forward to being\n"
	.string "your partner…$"
	// きみと いっしょに タッグをｎ
	// くみたかったよ……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFIntro:: @ 824692B
	.string "Well, hello!\n"
	.string "I'm TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon1:: @ 824694B
	.string "Want to know what I run with?\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon2Ask:: @ 824697C
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "Well?\n"
	.string "Want to be in a tag team with me?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFAccept:: @ 82469B4
	.string "Good going!\p"
	.string "I'll be quick and get the registration\n"
	.string "all done!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFReject:: @ 82469F1
	.string "You and me, we would've been tops.\n"
	.string "It's too bad…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMIntro:: @ 8246A22
	.string "Hey, there! My name's {STR_VAR_1}!\n"
	.string "I'm a TRIATHLETE!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon1:: @ 8246A4E
	.string "I go on runs with my durable team--\n"
	.string "one {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon2Ask:: @ 8246A85
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "Not too shabby, huh?\n"
	.string "We should be in a tag team together!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMAccept:: @ 8246ACF
	.string "All right!\n"
	.string "I'll go register in a flash!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMReject:: @ 8246AF7
	.string "I really wanted to battle as your\n"
	.string "tag-team partner…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlIntro:: @ 8246B2B
	.string "I'm BATTLE GIRL {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon1:: @ 8246B3F
	.string "I've been toughening up one\n"
	.string "{STR_VAR_1}-using {STR_VAR_2} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon2Ask:: @ 8246B6B
	.string "one {STR_VAR_1}-using {STR_VAR_2}!\p"
	.string "Do you like that combo?\n"
	.string "How about you and me join up?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlAccept:: @ 8246BB2
	.string "Why, thanks!\p"
	.string "I'll get the registration done\n"
	.string "right now!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlReject:: @ 8246BE9
	.string "With you, I thought we could form\n"
	.string "the ultimate tag team…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMIntro:: @ 8246C22
	.string "I'm TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon1:: @ 8246C35
	.string "I've been running with one {STR_VAR_2}\n"
	.string "that knows how to use {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon2Ask:: @ 8246C6C
	.string "and one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "We could be in a tag team.\n"
	.string "Wouldn't that be great?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMAccept:: @ 8246CB3
	.string "Thank you!\p"
	.string "I'll go register us, and that's\n"
	.string "right now!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMReject:: @ 8246CE9
	.string "Aww, that's too bad. We would've been\n"
	.string "the toughest tag team around!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMIntro:: @ 8246D2D
	.string "Me?\n"
	.string "I'm TUBER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon1:: @ 8246D3F
	.string "What do I have with me?\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon2Ask:: @ 8246D6A
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "Hey?\n"
	.string "You'll team up with me, right?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMAccept:: @ 8246D9E
	.string "Okay!\p"
	.string "I'll go register!\n"
	.string "Let's be excellent together!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMReject:: @ 8246DD3
	.string "My POKéMON are tough for sure…\n"
	.string "It's too bad you don't want to team up.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristIntro:: @ 8246E1A
	.string "Yay-hey!\n"
	.string "Call me GUITARIST {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon1:: @ 8246E39
	.string "Check out my entourage!\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon2Ask:: @ 8246E64
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "Yay-hey! Pretty wild, huh?\n"
	.string "We'll have to do a duet in a tag team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristAccept:: @ 8246EB6
	.string "Yay-hey! Right on!\n"
	.string "I'll do that registration stuff now!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristReject:: @ 8246EEE
	.string "My POKéMON rock hard!\n"
	.string "You'll be sorry, I tell you!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanIntro:: @ 8246F21
	.string "Pleased to meet you.\n"
	.string "I am {STR_VAR_1}, a GENTLEMAN.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon1:: @ 8246F4C
	.string "I am accompanied by my trusted\n"
	.string "{STR_VAR_1}-using {STR_VAR_2} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon2Ask:: @ 8246F7B
	.string "one {STR_VAR_1}-using {STR_VAR_2}.\p"
	.string "May I ask you to join me in a tag-team\n"
	.string "partnership arrangement?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanAccept:: @ 8246FCC
	.string "Ah, I thank you for your trust.\n"
	.string "I shall be done with the registration.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanReject:: @ 8247013
	.string "That is most unfortunate…\p"
	.string "I shall look forward to the next\n"
	.string "opportunity…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMIntro:: @ 824705B
	.string "Hello, I'm {STR_VAR_1},\n"
	.string "and I'm a POKéFAN.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon1:: @ 824707D
	.string "I have with me now one {STR_VAR_2}\n"
	.string "that knows the move {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon2Ask:: @ 82470B2
	.string "one {STR_VAR_2} with {STR_VAR_1}.\p"
	.string "Do you like what you see?\n"
	.string "Why don't you be my tag partner?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMAccept:: @ 82470FD
	.string "Thank you!\n"
	.string "I'll look after the registration!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMReject:: @ 824712A
	.string "My POKéMON are top grade…\n"
	.string "It's too bad you can't appreciate that.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMIntro:: @ 824716C
	.string "Hm!\n"
	.string "I am {STR_VAR_1}, and an EXPERT am I!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon1:: @ 824718D
	.string "The POKéMON that I've toughened up are\n"
	.string "one {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon2Ask:: @ 82471C7
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "What say you to a tag team with me?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMAccept:: @ 82471FB
	.string "Hm!\n"
	.string "I shall register us right away!\l"
	.string "Let us both do our best!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMReject:: @ 8247238
	.string "I will hope that your choice is\n"
	.string "indeed correct…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFIntro:: @ 8247268
	.string "Hello, hello.\n"
	.string "I'm {STR_VAR_1}, and I'm an EXPERT.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon1:: @ 8247291
	.string "I've raised my POKéMON thoroughly.\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon2Ask:: @ 82472C7
	.string "one {STR_VAR_2} with {STR_VAR_1}--\n"
	.string "they're what I have.\p"
	.string "Wouldn't you like to team up with me?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFAccept:: @ 8247313
	.string "Good, good.\n"
	.string "I'll see to the registration right away.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFReject:: @ 8247348
	.string "Perhaps we can form a team the next\n"
	.string "time we meet.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerIntro:: @ 824737A
	.string "I'm DRAGON TAMER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon1:: @ 824738F
	.string "The team I've been toughening up is\n"
	.string "one {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon2Ask:: @ 82473C6
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "How about it?\n"
	.string "Want to be my partner?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerAccept:: @ 82473FB
	.string "Okay, I'll give it my best!\n"
	.string "I'll go register now, all right?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerReject:: @ 8247438
	.string "You're not going to find many tougher\n"
	.string "partners than me!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperIntro:: @ 8247470
	.string "I'm BIRD KEEPER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon1:: @ 8247484
	.string "What POKéMON do I have?\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon2Ask:: @ 82474AF
	.string "one {STR_VAR_2} with {STR_VAR_1}.\p"
	.string "Don't you think we'd make a decent\n"
	.string "tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperAccept:: @ 82474EC
	.string "Great, thanks!\n"
	.string "I'll look after the registration!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperReject:: @ 824751D
	.string "My POKéMON and I are strong.\n"
	.string "What a letdown.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyIntro:: @ 824754A
	.string "I'm NINJA BOY {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon1:: @ 824755C
	.string "My POKéMON team consists of one\n"
	.string "{STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon2Ask:: @ 824758B
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "Let's be in a tag team together!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyAccept:: @ 82475BC
	.string "Yay!\n"
	.string "Let me go register!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyReject:: @ 82475D5
	.string "You'll regret not having my tough\n"
	.string "POKéMON on your side!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyIntro:: @ 824760D
	.string "Hello!\n"
	.string "I'm PARASOL LADY {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon1:: @ 8247629
	.string "Escorting me now are my {STR_VAR_2}\n"
	.string "that uses {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon2Ask:: @ 8247655
	.string "one {STR_VAR_2} that uses\n"
	.string "{STR_VAR_1}.\p"
	.string "Aren't they nice?\n"
	.string "Care to join us in a tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyAccept:: @ 824769B
	.string "Thanks a bunch!\p"
	.string "I'll go register at the counter.\n"
	.string "Let's not disappoint each other!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyReject:: @ 82476ED
	.string "My POKéMON are tremendously strong.\n"
	.string "How disappointing…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacIntro:: @ 8247724
	.string "Hello.\n"
	.string "I'm {STR_VAR_1}, and I'm a BUG MANIAC!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon1:: @ 8247749
	.string "I have found my POKéMON, yes.\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon2Ask:: @ 824777A
	.string "one {STR_VAR_2} with {STR_VAR_1}--\n"
	.string "they are what I found.\p"
	.string "Could I interest you in forming\n"
	.string "a tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacAccept:: @ 82477CE
	.string "Okay!\n"
	.string "Understood!\p"
	.string "I won't be long with the registration!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacReject:: @ 8247807
	.string "With the POKéMON I found, we wouldn't\n"
	.string "have lost…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorIntro:: @ 8247838
	.string "Ahoy, there!\n"
	.string "I'm SAILOR {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon1:: @ 8247854
	.string "Let me show you my pride and joy!\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon2Ask:: @ 8247889
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "Of course you're not going to turn\n"
	.string "me down. We will team up, right?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorAccept:: @ 82478DD
	.string "I didn't expect any less!\n"
	.string "I'll go register now.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorReject:: @ 824790D
	.string "We would've stormed through\n"
	.string "the opposition! Too bad!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorIntro:: @ 8247942
	.string "Hi, I'm {STR_VAR_1}.\n"
	.string "I'm a COLLECTOR.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon1:: @ 824795F
	.string "The jewels in my collection are\n"
	.string "my {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon2Ask:: @ 8247991
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "Swell, huh?\n"
	.string "We should be in a team together.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorAccept:: @ 82479CE
	.string "Oh, yeah!\p"
	.string "Well, let's not waste any time.\n"
	.string "I'll go register the two of us.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorReject:: @ 8247A18
	.string "Well, that's upsetting.\n"
	.string "You don't appreciate my POKéMON.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMIntro:: @ 8247A51
	.string "Howdy, I'm {STR_VAR_1}.\n"
	.string "I'm a POKéMON RANGER.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon1:: @ 8247A76
	.string "Keeping me company are one\n"
	.string "{STR_VAR_1}-using {STR_VAR_2} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon2Ask:: @ 8247AA1
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "Don't you think we'd make an impressive\n"
	.string "tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMAccept:: @ 8247AE3
	.string "That's super!\n"
	.string "I'll deal with the registration now.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMReject:: @ 8247B16
	.string "Next time, choose my POKéMON,\n"
	.string "will you?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFIntro:: @ 8247B3E
	.string "My name's {STR_VAR_1}.\n"
	.string "I'm a POKéMON RANGER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon1:: @ 8247B62
	.string "Let me tell you about my team. I have\n"
	.string "one {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon2Ask:: @ 8247B9B
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "How would you like to form a tag team\n"
	.string "with my little posse?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFAccept:: @ 8247BE7
	.string "We'll be at our best!\n"
	.string "I'll get the registration done quick!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFReject:: @ 8247C23
	.string "I hope you'll choose my POKéMON\n"
	.string "next time.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyIntro:: @ 8247C4E
	.string "Pleased to meet you. I'm {STR_VAR_1}.\n"
	.string "I consider myself an AROMA LADY.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon1:: @ 8247C8C
	.string "I travel with one {STR_VAR_2}\n"
	.string "that uses {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon2Ask:: @ 8247CB2
	.string "one {STR_VAR_2} that uses\n"
	.string "{STR_VAR_1}.\p"
	.string "I hope they strike your fancy.\n"
	.string "Would you care to be my partner?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyAccept:: @ 8247D07
	.string "I'm honored by your acceptance.\n"
	.string "I will go register right this instant.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyReject:: @ 8247D4E
	.string "It would be wonderful if we could form\n"
	.string "a tag team the next time we meet.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacIntro:: @ 8247D97
	.string "Want to know who I am?\n"
	.string "I'm {STR_VAR_1}, the RUIN MANIAC!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon1:: @ 8247DC7
	.string "The POKéMON that I have with me are\n"
	.string "one {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon2Ask:: @ 8247DFE
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "Intriguing, eh?\n"
	.string "How about you and I partner up?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacAccept:: @ 8247E3E
	.string "That's a sound decision!\n"
	.string "I'll go do the registration paperwork.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacReject:: @ 8247E7E
	.string "Hmm…\n"
	.string "I think my POKéMON are tough…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMIntro:: @ 8247EA1
	.string "I'm COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon1:: @ 8247EB5
	.string "The POKéMON I have right now are one\n"
	.string "{STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon2Ask:: @ 8247EE9
	.string "one {STR_VAR_2} with {STR_VAR_1}.\n"
	.string "Cool, huh?\p"
	.string "Don't you think it'd be pretty cool\n"
	.string "if we made a tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMAccept:: @ 8247F3F
	.string "Cool!\n"
	.string "I'll go do the registration in a flash!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMReject:: @ 8247F6D
	.string "I thought that we'd make just\n"
	.string "the greatest team ever.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFIntro:: @ 8247FA3
	.string "I'm COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon1:: @ 8247FB7
	.string "The team I've been raising has one\n"
	.string "{STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon2Ask:: @ 8247FE9
	.string "one {STR_VAR_2} with {STR_VAR_1}.\p"
	.string "Does that sound okay?\n"
	.string "How about we become tag partners?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFAccept:: @ 8248031
	.string "Sounds A-OK!\n"
	.string "I'd better do the registration.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFReject:: @ 824805E
	.string "I was thinking how we would be\n"
	.string "one tough team…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacIntro:: @ 824808D
	.string "Heyo!\n"
	.string "I'm {STR_VAR_1}, the POKéMANIAC!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon1:: @ 82480AB
	.string "What does a guy like me have?\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon2Ask:: @ 82480DC
	.string "one {STR_VAR_2} with {STR_VAR_1},\n"
	.string "that's what!\p"
	.string "Let's do it!\n"
	.string "We'll stomp around as a tag team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacAccept:: @ 8248128
	.string "Good call!\n"
	.string "I'll register the both of us!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacReject:: @ 8248151
	.string "My POKéMON are brutal!\n"
	.string "It's not my fault if you regret this!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerIntro:: @ 824818E
	.string "Yo, there!\n"
	.string "I'm KINDLER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon1:: @ 82481A9
	.string "You know what my training cooked up?\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon2Ask:: @ 82481E1
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "Well, what do you say?\n"
	.string "Want to form a tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerAccept:: @ 8248221
	.string "All right!\n"
	.string "I'll get on with the registration.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerReject:: @ 824824F
	.string "Promise you'll partner up with me\n"
	.string "the next time we run into each other.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperIntro:: @ 8248297
	.string "I'm {STR_VAR_1}, and I'm a CAMPER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon1:: @ 82482B1
	.string "I've been raising one {STR_VAR_1}-\n"
	.string "using {STR_VAR_2} and one$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon2Ask:: @ 82482DC
	.string "{STR_VAR_1}-using {STR_VAR_2}.\p"
	.string "Do you think it'd be fun to team up?\n"
	.string "I bet it would be!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperAccept:: @ 8248321
	.string "Yeah!\n"
	.string "Off I go to register!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperReject:: @ 824833D
	.string "Next time, okay?\n"
	.string "I want to be on your team.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerIntro:: @ 8248369
	.string "Hello!\n"
	.string "I'm {STR_VAR_1}, and I'm a PICNICKER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon1:: @ 824838D
	.string "The POKéMON I've been taking are\n"
	.string "one {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon2Ask:: @ 82483C1
	.string "one {STR_VAR_2} with {STR_VAR_1}.\p"
	.string "Are you interested in joining me\n"
	.string "on a tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerAccept:: @ 8248401
	.string "Why, thank you!\n"
	.string "I will do the registration now.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerReject:: @ 8248431
	.string "It would be nice if I could join you\n"
	.string "some other time.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMIntro:: @ 8248467
	.string "I'm PSYCHIC {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon1:: @ 8248477
	.string "The twosome I've been raising are\n"
	.string "one {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon2Ask:: @ 82484AC
	.string "one {STR_VAR_2} with {STR_VAR_1}.\p"
	.string "Would you like to form a tag team\n"
	.string "with me?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMAccept:: @ 82484E7
	.string "Sure thing!\n"
	.string "I'll take care of the registration!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMReject:: @ 8248517
	.string "If we meet again, that's when I'd like\n"
	.string "to team up with you.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFIntro:: @ 8248553
	.string "I'm {STR_VAR_1}.\n"
	.string "I'm a PSYCHIC.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon1:: @ 824856A
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon2Ask:: @ 824857D
	.string "one {STR_VAR_2} with {STR_VAR_1}--\n"
	.string "they're my disciples.\p"
	.string "Doesn't the idea of forming a tag-team\n"
	.string "partnership intrigue you?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFAccept:: @ 82485E5
	.string "Thank you.\n"
	.string "I'll go deal with the registration.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFReject:: @ 8248614
	.string "I hope there will be another chance\n"
	.string "to forge an alliance.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFIntro:: @ 824864E
	.string "I'm SCHOOL KID {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon1:: @ 8248661
	.string "One {STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon2Ask:: @ 8248671
	.string "and one {STR_VAR_1}-using\n"
	.string "{STR_VAR_2} are my POKéMON pair.\p"
	.string "May I please be your partner on\n"
	.string "a tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFAccept:: @ 82486C6
	.string "Ooh, thank you!\n"
	.string "I'll register at the counter right away!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFReject:: @ 82486FF
	.string "Please?\n"
	.string "May I join you the next time?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFIntro:: @ 8248725
	.string "Hiya! The name's {STR_VAR_1}!\n"
	.string "I'm a POKéMON BREEDER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon1:: @ 8248751
	.string "The POKéMON I've raised are one\n"
	.string "{STR_VAR_1}-using {STR_VAR_2} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon2Ask:: @ 8248781
	.string "one {STR_VAR_1}-using {STR_VAR_2}.\p"
	.string "Sound interesting?\n"
	.string "How about we form a tag team, then?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFAccept:: @ 82487C9
	.string "All righty!\n"
	.string "You leave the registration to me!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFReject:: @ 82487F7
	.string "You have to team up with me next time,\n"
	.string "all right?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFIntro:: @ 8248829
	.string "I'm {STR_VAR_1}, and I'm proud to say\n"
	.string "that I am a POKéFAN.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon1:: @ 824885B
	.string "The darling POKéMON I've raised are\n"
	.string "one {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon2Ask:: @ 8248892
	.string "one {STR_VAR_2} with {STR_VAR_1}.\p"
	.string "Aren't they just the cutest?\n"
	.string "We ought to make a team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFAccept:: @ 82488D8
	.string "Thank you, dear!\n"
	.string "I'll be on my way to register!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFReject:: @ 8248908
	.string "My darling POKéMON are the best,\n"
	.string "I'll have you know. How annoying!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFIntro:: @ 824894B
	.string "Hi, I'm SWIMMER {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon1:: @ 824895F
	.string "One {STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon2Ask:: @ 824896F
	.string "and one {STR_VAR_1}-using\n"
	.string "{STR_VAR_2} are what I've trained.\p"
	.string "You and me, let's make a tag team.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFAccept:: @ 82489BD
	.string "That's cool!\n"
	.string "I'll register the two of us.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFReject:: @ 82489E7
	.string "If we meet again, you owe me\n"
	.string "a tag team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMIntro:: @ 8248A10
	.string "What's happening?\n"
	.string "I'm {STR_VAR_1}, and I'm a TRIATHLETE.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon1:: @ 8248A40
	.string "I got a couple decent POKéMON.\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon2Ask:: @ 8248A72
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "It'd be neat if we made a tag team\n"
	.string "together, so how about it?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMAccept:: @ 8248AC0
	.string "Right on!\n"
	.string "You wait while I register, okay?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMReject:: @ 8248AEB
	.string "I expect you'll let me join you\n"
	.string "next time, how's that?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFIntro:: @ 8248B22
	.string "I'm the TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon1:: @ 8248B39
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon2Ask:: @ 8248B4C
	.string "another {STR_VAR_2} that knows how\n"
	.string "to use {STR_VAR_1}. That's my pair.\p"
	.string "What do you think?\n"
	.string "We'd make a good team, I'd say.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFAccept:: @ 8248BB4
	.string "I like that answer!\n"
	.string "I'll get done with registration fast!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFReject:: @ 8248BEE
	.string "You'll give me another chance to form\n"
	.string "a partnership, won't you?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMIntro:: @ 8248C2E
	.string "Hi, there! Hello!\n"
	.string "I'm {STR_VAR_1}, and I'm a SWIMMER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon1:: @ 8248C5B
	.string "Check out what I've been raising!\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon2Ask:: @ 8248C90
	.string "one {STR_VAR_2} with {STR_VAR_1}!\p"
	.string "Sweet, huh?\n"
	.string "It'd be sweet to form a team, too!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMAccept:: @ 8248CCF
	.string "Much obliged!\n"
	.string "I'll get this registration thing done!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMReject:: @ 8248D04
	.string "If we meet again, you have to team up\n"
	.string "with me. You'll do that, right?$"

