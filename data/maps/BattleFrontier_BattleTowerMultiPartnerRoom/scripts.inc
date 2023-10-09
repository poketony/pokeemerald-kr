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
	.string "파트너를 찾아주세요!$"
	// こちらに いる トレ-ナ-の なかからｎ
	// パ-トナ-を おさがしください!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner: @ 8244094
	.string "{PLAYER}님은\n"
	.string "아직 파트너를 찾지 못했습니다!\p"
	.string "파트너 찾기를 중지하고\n"
	.string "접수처로 되돌아갈까요?$"
	// あさんはｎ
	// まだ パ-トナ-を みつけていません!ｐ
	// パ-トナ-を さがすのを やめてｎ
	// うけつけへ もどりますか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2: @ 824410C
	.string "그럼\n"
	.string "여기에 있는 트레이너 중에서\l"
	.string "파트너를 찾아주세요!$"
	// それではｎ
	// こちらに いる トレ-ナ-の なかからｌ
	// パ-トナ-を おさがしください!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner:: @ 8244149
	.string "파트너 찾기\n"
	.string "수고하셨습니다!\p"
	.string "그럼 멀티 배틀룸으로\n"
	.string "안내하겠습니다$"
	// パ-トナ-さがしｎ
	// おつかれさまでした!ｐ
	// それでは マルチ バトルル-ムへｎ
	// おつれいたします

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Intro:: @ 824419A
	.string "나는\n"
	.string "{STR_VAR_1}님의 {STR_VAR_2}번째 제자\l"
	.string "그 이름은 {STR_VAR_3}!$"
	// ぼくはｎ
	// いさんの うばん でしｌ
	// そのなも え!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon1:: @ 82441CA
	.string "{STR_VAR_1}의 어드바이스를 받아서\n"
	.string "{STR_VAR_2}{K_EULREUL} 지닌 {STR_VAR_3}{K_WAGWA}...$"
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
	.string "여어!\p"
	.string "난\n"
	.string "도련님 {STR_VAR_1}{K_I}야!$"
	// よう!ｐ
	// オレｎ
	// おぼっちゃま §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon1:: @ 8246478
	.string "나는\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// オレｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon2Ask:: @ 824649D
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "가지고 있다고!\p"
	.string "나랑 같이\n"
	.string "태그를 맺는 걸 허락해줄까?$"
	// §いを もつ §うをｎ
	// もっているんだぜ!ｐ
	// オレ いっしょにｎ
	// タッグを くんでもいいぜ?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyAccept:: @ 82464EE
	.string "좋아!\p"
	.string "그럼 지금부터\n"
	.string "접수처에 등록하고 온다!$"
	// よし!ｐ
	// じゃあ いまからｎ
	// うけつけで とうろくを すませてくるぜ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyReject:: @ 8246529
	.string "나와 태그를 맺지 않다니\n"
	.string "분명 후회하게 될걸!$"
	// オレと タッグを くまない なんてｎ
	// きっと こうかい するぜ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltIntro:: @ 8246571
	.string "안녕하십니까!\p"
	.string "태권왕\n"
	.string "{STR_VAR_1}{K_I}라고 합니다$"
	// オッス!ｐ
	// カラテおう §いｎ
	// と もうします

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon1:: @ 824658C
	.string "지금 전\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// いま わたくしｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon2Ask:: @ 82465B5
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있습니다!\p"
	.string "부탁드립니다!\n"
	.string "저와\n"
	.string "태그를 맺어주시지 않겠습니까?$"
	// §いを もつ §うをｎ
	// つれております!ｐ
	// おねがいします!ｐ
	// わたくしとｎ
	// タッグを くんで くれませんか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltAccept:: @ 8246605
	.string "감사합니다!\p"
	.string "바로\n"
	.string "접수처에 등록하고 오겠습니다!$"
	// オッス!ｐ
	// さっそくｎ
	// うけつけに とうろく してまいります!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltReject:: @ 824662A
	.string "그렇습니까...\p"
	.string "다음 기회에는\n"
	.string "꼭 태그를 맺어주십시오...$"
	// オッス……ｐ
	// つぎの きかいはｎ
	// ぜひ タッグを くんでください……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFIntro:: @ 8246662
	.string "안녕!\p"
	.string "난\n"
	.string "튜브걸 {STR_VAR_1}{K_I}야!$"
	// こんにちは!ｐ
	// わたしｎ
	// うきわガ-ル §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon1:: @ 8246686
	.string "나는\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// わたしｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon2Ask:: @ 82466B4
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있어!\p"
	.string "저기\p"
	.string "같이\n"
	.string "태그 맺지 않을래?$"
	// §いを もつ §うをｎ
	// つれているの!ｐ
	// ねぇ?ｐ
	// いっしょにｎ
	// タッグを くんでよ-?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFAccept:: @ 82466E6
	.string "고마워-!\p"
	.string "그럼 지금\n"
	.string "접수처에 등록하고 올게!$"
	// ありがとう-!ｐ
	// じゃあ いまからｎ
	// うけつけで とうろくを すませてくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFReject:: @ 824670A
	.string "나하고 태그를 맺으면\n"
	.string "무척 강할 텐데-!$"
	// わたしと タッグを くんだらｎ
	// とっても つよかったのに-!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacIntro:: @ 8246741
	.string "안녕하세요...\p"
	.string "오컬트마니아\n"
	.string "{STR_VAR_1}{K_I}라고 합니다...$"
	// こんにちは……ｐ
	// オカルトマニア §いとｎ
	// もうします……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon1:: @ 8246760
	.string "저...\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// わたくし……ｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon2Ask:: @ 8246791
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있습니다...\p"
	.string "부디 저와\n"
	.string "태그를 맺어주시면 안 될까요?$"
	// §いを もつ §うをｎ
	// もっております……ｐ
	// どうか わたくしとｎ
	// タッグを くんでいただけませんか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacAccept:: @ 82467C4
	.string "감사합니다...\n"
	.string "접수처에 등록하고 올게요...$"
	// ありがとうございます……ｎ
	// うけつけで とうろくを してきます……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacReject:: @ 82467E6
	.string "당신과 태그를\n"
	.string "맺고 싶었어요...$"
	// あなたと タッグをｎ
	// くみたかったです……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMIntro:: @ 82467FF
	.string "여어!\p"
	.string "난\n"
	.string "포켓몬 브리더 {STR_VAR_1}{K_I}야!$"
	// やあ!ｐ
	// ぼくｎ
	// ポケモンブリ-ダ- §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon1:: @ 8246831
	.string "난 지금\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// ぼくは いまｎ
	// §いを もつ §うとね……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon2Ask:: @ 8246864
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "키우고 있어!\p"
	.string "어때?\p"
	.string "나하고\n"
	.string "같이 태그를 맺지 않을래?$"
	// §いを もつ §うをｎ
	// そだてているんだ!ｐ
	// どう?ｐ
	// ぼくとｎ
	// いっしょに タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMAccept:: @ 82468A7
	.string "고마워!\p"
	.string "그럼 바로\n"
	.string "접수처에 등록하고 올게!$"
	// ありがとう!ｐ
	// では さっそくｎ
	// うけつけで とうろくを すませてきますね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMReject:: @ 82468FE
	.string "너와 같이 태그를\n"
	.string "맺고 싶었어...$"
	// きみと いっしょに タッグをｎ
	// くみたかったよ……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFIntro:: @ 824692B
	.string "안녕!\p"
	.string "난\n"
	.string "트라이애슬리트 {STR_VAR_1}{K_I}야!$"
	// こんにちは!ｐ
	// わたしｎ
	// トライアスリ-ト §いよ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon1:: @ 824694B
	.string "나는\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// わたしはｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon2Ask:: @ 824697C
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 달리고 있지!\p"
	.string "어때?\n"
	.string "나와 태그를 맺지 않을래?$"
	// §いを もつ §うをｎ
	// つれて はしっているの!ｐ
	// どう?ｎ
	// わたしと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFAccept:: @ 82469B4
	.string "해냈다!\p"
	.string "그럼 바로 접수처에서\n"
	.string "등록하고 올게-!$"
	// やったね!ｐ
	// じゃ さっそく うけつけでｎ
	// とうろくを すませてくるわ-!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFReject:: @ 82469F1
	.string "나와 태그를 맺는다면\n"
	.string "최고일 텐데 아쉽네...$"
	// わたしと タッグを くんだらｎ
	// さいこうなのに ざんねんね……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMIntro:: @ 8246A22
	.string "여어!\p"
	.string "난\n"
	.string "트라이애슬리트 {STR_VAR_1}{K_I}야!$"
	// やあ!ｐ
	// ぼくｎ
	// トライアスリ-ト §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon1:: @ 8246A4E
	.string "나는\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// ぼくｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon2Ask:: @ 8246A85
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 달리고 있지!\p"
	.string "어때?\n"
	.string "나와 태그를 맺어보지 않을래?$"
	// §いを もつ §うをｎ
	// つれて はしっているんだ!ｐ
	// どうだい?ｎ
	// ぼくと タッグを くんでみないかい?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMAccept:: @ 8246ACF
	.string "해냈다-!\p"
	.string "지금 접수처에서\n"
	.string "등록하고 올게-!$"
	// やった-!ｐ
	// いま うけつけでｎ
	// とうろくを すませてくるよ-!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMReject:: @ 8246AF7
	.string "너와 태그를 맺어서\n"
	.string "함께 배틀하고 싶었어...$"
	// きみと タッグを くんでｎ
	// いっしょに たたかいたかったよ……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlIntro:: @ 8246B2B
	.string "난\n"
	.string "배틀걸 {STR_VAR_1}!$"
	// わたしｎ
	// バトルガ-ル §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon1:: @ 8246B3F
	.string "나는\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// わたしｎ
	// §いを もつ §う……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon2Ask:: @ 8246B6B
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "단련시키고 있어!\p"
	.string "어때?\n"
	.string "나와 태그를 맺지 않을래?$"
	// §いを もつ §うをｎ
	// きたえているの!ｐ
	// どう?ｎ
	// わたしと タッグを くまない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlAccept:: @ 8246BB2
	.string "고마워!\p"
	.string "지금 접수처에서\n"
	.string "등록하고 올게-!$"
	// ありがとう!ｐ
	// いまから うけつけでｎ
	// とうろくを すませてくるからね-!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlReject:: @ 8246BE9
	.string "너와 함께라면 최강의 태그를\n"
	.string "만들 수 있을 거라 생각했는데...$"
	// あなたとなら さいきょうの タッグをｎ
	// くめると おもったのに……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMIntro:: @ 8246C22
	.string "난\n"
	.string "트라이애슬리트 {STR_VAR_1}{K_I}야!$"
	// オレｎ
	// トライアスリ-ト §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon1:: @ 8246C35
	.string "나는\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// オレｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon2Ask:: @ 8246C6C
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 달리고 있지!\p"
	.string "어때?\n"
	.string "나와 같이 태그를 맺지 않을래?$"
	// §いを もつ §うをｎ
	// つれて はしっているんだぜ!ｐ
	// どうだい?ｎ
	// オレと いっしょに タッグを くまない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMAccept:: @ 8246CB3
	.string "땡큐!\p"
	.string "지금 접수처에서\n"
	.string "등록하고 올게!$"
	// サンキュ-!ｐ
	// いまから うけつけでｎ
	// とうろくを すませてくるぜ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMReject:: @ 8246CE9
	.string "너와 함께라면 최강의 태그를\n"
	.string "만들 수 있을 텐데 유감이야!$"
	// きみとなら さいきょうの タッグをｎ
	// くめたのに ざんねんだよ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMIntro:: @ 8246D2D
	.string "난 말이지...\n"
	.string "튜브보이 {STR_VAR_1}{K_I}야!$"
	// ぼくはね……ｎ
	// うきわボ-イ §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon1:: @ 8246D3F
	.string "나는\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// ぼくはｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon2Ask:: @ 8246D6A
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있어!\p"
	.string "저기\n"
	.string "나랑 같이 태그 맺을래?$"
	// §いを もつ §うをｎ
	// つれているんだよ!ｐ
	// ねぇ?ｎ
	// ぼくと いっしょに タッグを くもうよ?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMAccept:: @ 8246D9E
	.string "앗싸-!\p"
	.string "접수처에서 등록하고 올게-!\n"
	.string "열심히 하자!$"
	// やったね-!ｐ
	// うけつけで とうろく してくるよ-!ｎ
	// がんばろうね-!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMReject:: @ 8246DD3
	.string "내 포켓몬 엄청 강한데...\n"
	.string "태그를 못 해서 유감이야!$"
	// ぼくの ポケモン とっても つよいのに……ｎ
	// タッグに なれなくて ざんねん!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristIntro:: @ 8246E1A
	.string "이-예이!\p"
	.string "난\n"
	.string "기타리스트 {STR_VAR_1}!$"
	// イエ-イ!ｐ
	// オレはｎ
	// ギタリスト §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon1:: @ 8246E39
	.string "이 몸은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// オレはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon2Ask:: @ 8246E64
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있다고-!\p"
	.string "이-예이?\n"
	.string "나와 같이 태그 맺을래?$"
	// §いを つかう §うをｎ
	// つれているんだぜ-!ｐ
	// イエ-イ?ｎ
	// オレと いっしょに タッグを くもうぜ?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristAccept:: @ 8246EB6
	.string "이-예이!\p"
	.string "지금\n"
	.string "접수처에서 등록하고 올게-!$"
	// イエ-イ!ｐ
	// いまからｎ
	// うけつけで とうろく してくるぜ-!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristReject:: @ 8246EEE
	.string "내 포켓몬은 무척 강하다고-!\n"
	.string "후회하지나 마셔-!$"
	// オレの ポケモン とっても つよいぜ-!ｎ
	// こうかい しないように するんだぜ-!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanIntro:: @ 8246F21
	.string "안녕하신지요\p"
	.string "신사\n"
	.string "{STR_VAR_1}{K_I}라고 합니다$"
	// こんにちはｐ
	// ジェントルマン §いとｎ
	// もうします

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon1:: @ 8246F4C
	.string "저는\n"
	.string "{STR_VAR_1}{K_EULREUL} 가진 {STR_VAR_2}{K_WAGWA}...$"
	// わたくしｎ
	// §いを もった §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon2Ask:: @ 8246F7B
	.string "{STR_VAR_1}{K_EULREUL} 가진 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있지요!\p"
	.string "어떻습니까?\n"
	.string "제 파트너가 되시지 않겠습니까?$"
	// §いを もった §うをｎ
	// つれておりますぞ!ｐ
	// どうですかな?ｎ
	// わたくしの パ-トナ-に なりませんかな?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanAccept:: @ 8246FCC
	.string "잘 부탁드리지요!\p"
	.string "그럼\n"
	.string "접수처에서 등록하고 오겠습니다!$"
	// よろしく おねがいしますぞ!ｐ
	// ではｎ
	// うけつけで とうろく してきます!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanReject:: @ 8247013
	.string "유감이군요...\n"
	.string "다음 기회를 기대하고 있겠습니다$"
	// ざんねん ですな……ｎ
	// つぎの きかいを きたいして おりますぞ

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMIntro:: @ 824705B
	.string "저는\n"
	.string "애호가클럽\l"
	.string "{STR_VAR_1}{K_I}라고 합니다$"
	// わたくしｎ
	// だいすきクラブの §いとｌ
	// もうします

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon1:: @ 824707D
	.string "전 지금\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// わたくしは いまｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon2Ask:: @ 82470B2
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있어요!\p"
	.string "어떤가요?\n"
	.string "저와 태그를 맺지 않겠습니까?$"
	// §いを もつ §うをｎ
	// つれて おります!ｐ
	// どうでしょう?ｎ
	// わたくしと タッグを くみませんかな?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMAccept:: @ 82470FD
	.string "고맙습니다!\n"
	.string "그럼 등록하러 갔다 올게요!$"
	// ありがとう ございます!ｎ
	// それでは とうろくに いってまいります!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMReject:: @ 824712A
	.string "제 포켓몬\n"
	.string "최고인데 유감이군요...$"
	// わたくしの ポケモンｎ
	// さいこうなのに ざんねんです……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMIntro:: @ 824716C
	.string "흐음!\p"
	.string "나는\n"
	.string "달인 {STR_VAR_1}일세!$"
	// うむ!ｐ
	// わしはｎ
	// たつじん §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon1:: @ 824718D
	.string "내가 단련시킨 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わしの きたえあげた ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon2Ask:: @ 82471C7
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}라네\p"
	.string "어떤가?\n"
	.string "나와 태그를 맺지 않겠나?$"
	// §いを つかう §うじゃｐ
	// どうじゃ?ｎ
	// わしと タッグを くまぬか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMAccept:: @ 82471FB
	.string "흐음!\p"
	.string "지금부터 등록하고 오겠네!\n"
	.string "서로 힘내보세!$"
	// うむ!ｐ
	// いまから とうろくを すませてくるぞ!ｎ
	// おたがい がんばろうぞ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMReject:: @ 8247238
	.string "자네의 선택이\n"
	.string "옳았기를 빌겠네...$"
	// おぬしの せんたくがｎ
	// ただしいことを いのっておるぞ……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFIntro:: @ 8247268
	.string "...그래요 그래요\p"
	.string "저는\n"
	.string "달인 {STR_VAR_1}{K_I}랍니다!$"
	// ……はいはいｐ
	// わたしはｎ
	// たつじん §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon1:: @ 8247291
	.string "제가 단련시켜 온 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わたしの きたえあげた ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon2Ask:: @ 82472C7
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}지요\p"
	.string "어떤가요?\n"
	.string "저와 태그를 맺으시겠나요?$"
	// §いを つかう §う ですよｐ
	// どうですかね?ｎ
	// わたしと タッグを くみませんか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFAccept:: @ 8247313
	.string "...그래요 그래요\n"
	.string "지금 등록하고 오겠습니다...$"
	// ……はいはいｎ
	// いまから とうろくを してきますよ……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFReject:: @ 8247348
	.string "다음에 만났을 때는\n"
	.string "태그를 맺어주었으면 하네요...$"
	// つぎに あったときにはｎ
	// タッグを くみたいものですね……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerIntro:: @ 824737A
	.string "나는\n"
	.string "드래곤 조련사 {STR_VAR_1}!$"
	// オレはｎ
	// ドラゴンつかい §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon1:: @ 824738F
	.string "내가 단련시켜 온 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// オレの きたえあげた ポケモンはｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon2Ask:: @ 82473C6
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_I}다!\p"
	.string "어때?\n"
	.string "나와 태그를 맺지 않겠어?$"
	// §いを もつ §う だ!ｐ
	// どうだ?ｎ
	// オレと タッグを くんでみないか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerAccept:: @ 82473FB
	.string "...좋았어! 열심히 해야지-!\n"
	.string "바로 등록하고 온다!$"
	// ……よしっ! がんばるぜ-!ｐ
	// すぐに とうろくを すませて くるからな!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerReject:: @ 8247438
	.string "나보다 강한 파트너는\n"
	.string "좀처럼 없다고!$"
	// オレより つよい パ-トナ-はｎ
	// そうそう いないぜ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperIntro:: @ 8247470
	.string "나는\n"
	.string "새 조련사 {STR_VAR_1}!$"
	// ぼくはｎ
	// とりつかい §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon1:: @ 8247484
	.string "내 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}랑...$"
	// ぼくの ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon2Ask:: @ 82474AF
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}야\p"
	.string "어때?\n"
	.string "나하고 태그를 맺을래?$"
	// §いを つかう §う だねｐ
	// どうだい?ｎ
	// ボクと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperAccept:: @ 82474EC
	.string "고마워-!\n"
	.string "지금 등록하고 올게!$"
	// ありがと-!ｐ
	// いまから とうろくを してくるよ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperReject:: @ 824751D
	.string "내 포켓몬\n"
	.string "정말로 강한데 아쉽게 됐네!$"
	// ぼくの ポケモンｎ
	// ほんとに つよいのに ざんねんだよ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyIntro:: @ 824754A
	.string "난\n"
	.string "닌자놀이 {STR_VAR_1}!$"
	// ぼくｎ
	// にんじゃごっこ §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon1:: @ 824755C
	.string "내가 지니고 있는 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}랑...$"
	// ぼくの もっている ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon2Ask:: @ 824758B
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}야\p"
	.string "저기\n"
	.string "나하고 태그 맺을래?$"
	// §いを つかう §うだよｐ
	// ね-?ｎ
	// ぼくと タッグを くもうよ?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyAccept:: @ 82475BC
	.string "앗싸-!\n"
	.string "바로 등록하고 올게!$"
	// やった-!ｎ
	// すぐ とうろくを してくるね-!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyReject:: @ 82475D5
	.string "내 포켓몬의 강함에\n"
	.string "분명 후회하게 될 거야-$"
	// ぼくの ポケモンの つよさにｎ
	// きっと こうかい するよ-

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyIntro:: @ 824760D
	.string "안녕!\p"
	.string "난\n"
	.string "파라솔 아가씨 {STR_VAR_1}{K_I}야!$"
	// こんにちは!ｐ
	// わたしｎ
	// パラソルおねえさん §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon1:: @ 8247629
	.string "나는 지금\n"
	.string "{STR_VAR_1}{K_EULREUL} 가진 {STR_VAR_2}{K_WAGWA}...$"
	// わたしは いまｎ
	// §いを もった §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon2Ask:: @ 8247655
	.string "{STR_VAR_1}{K_EULREUL} 가진 {STR_VAR_2}{K_EULREUL}\n"
	.string "데리고 있어!\p"
	.string "어때?\n"
	.string "내 포켓몬과 태그 맺지 않을래?$"
	// §いを もった §うをｎ
	// つれているの!ｐ
	// どう?ｎ
	// わたしの ポケモンと タッグを くまない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyAccept:: @ 824769B
	.string "고마워-!\p"
	.string "지금 접수처에서 등록하고 올 테니까\n"
	.string "열심히 하자-!$"
	// ありがとうね-!ｐ
	// いま うけつけで とうろく してくるからｎ
	// がんばろうね-!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyReject:: @ 82476ED
	.string "내 포켓몬 엄청 강한데\n"
	.string "아쉽네...$"
	// あたしの ポケモン とっても つよいのにｎ
	// ざんねんよ……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacIntro:: @ 8247724
	.string "저는\n"
	.string "곤충마니아 {STR_VAR_1}!$"
	// わたしはｎ
	// こんちゅうマニア §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon1:: @ 8247749
	.string "제가 발견한 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// わたしの みつけた ポケモンはｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon2Ask:: @ 824777A
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}입니다!\p"
	.string "어떻습니까?\n"
	.string "저와 태그를 맺지 않겠습니까?$"
	// §いを もつ §う ですよ!ｐ
	// どうですか?ｎ
	// わたしと タッグを くみませんか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacAccept:: @ 82477CE
	.string "네!\n"
	.string "알겠습니다\p"
	.string "지금 등록하고 올게요$"
	// はい!ｎ
	// りょうかい しましたｐ
	// いま とうろくを してきますからね

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacReject:: @ 8247807
	.string "제가 발견한 포켓몬과 팀을 짜면\n"
	.string "지지 않을 텐데$"
	// わたしが みつけた ポケモンと くめばｎ
	// まけないのに……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorIntro:: @ 8247838
	.string "안녕하신가!\p"
	.string "나는\n"
	.string "선원 {STR_VAR_1}!$"
	// オッス!ｐ
	// オレはｎ
	// ふなのり §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon1:: @ 8247854
	.string "내가 자랑하는 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// オレの じまんの ポケモンはｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon2Ask:: @ 8247889
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_I}야!\p"
	.string "저기!\n"
	.string "당연히 나하고 태그 맺을 거지?$"
	// §いを もつ §う だ!ｐ
	// なあ! ｎ
	// もちろん オレと タッグを くむだろう?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorAccept:: @ 82478DD
	.string "당연히 그렇게 나와야지!\n"
	.string "지금 등록하고 온다!$"
	// とうぜん だよな!ｎ
	// いまから とうろく してくるぜ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorReject:: @ 824790D
	.string "나와 한 팀이 되면 쉽게 이길 텐데\n"
	.string "아쉬운걸!$"
	// オレと くんだら らくしょう なのにｎ
	// ざんねん だぜ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorIntro:: @ 8247942
	.string "안녕\p"
	.string "나는\n"
	.string "포켓몬 컬렉터 {STR_VAR_1}{K_I}야!$"
	// やあｐ
	// ぼくはｎ
	// ポケモンコレクタ- §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon1:: @ 824795F
	.string "내 자랑스러운 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 가진 {STR_VAR_2}{K_WAGWA}...$"
	// ぼくの じまんの ポケモンはｎ
	// §いを もった §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon2Ask:: @ 8247991
	.string "{STR_VAR_1}{K_EULREUL} 가진 {STR_VAR_2}{K_I}야\p"
	.string "어때?\n"
	.string "나와 태그를 맺지 않을래?$"
	// §いを もった §うだよｐ
	// どうだい?ｎ
	// ぼくと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorAccept:: @ 82479CE
	.string "오오-!\p"
	.string "그럼 바로 접수처에서\n"
	.string "등록하고 올게!$"
	// おお-!ｐ
	// じゃあ さっそく うけつけでｎ
	// とうろく してくるよ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorReject:: @ 8247A18
	.string "내 포켓몬의 매력을\n"
	.string "몰라주다니 실망이야...$"
	// ぼくの ポケモンの みりょくにｎ
	// きが つかないなんて ガッカリだよ……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMIntro:: @ 8247A51
	.string "나는\n"
	.string "포켓몬 레인저 {STR_VAR_1}!$"
	// ぼくはｎ
	// ポケモンレンジャ- §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon1:: @ 8247A76
	.string "내가 데리고 있는 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// ぼくの つれている ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon2Ask:: @ 8247AA1
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}야!\p"
	.string "어때?\n"
	.string "나와 태그를 맺지 않을래?$"
	// §いを つかう §うだ!ｐ
	// どうだい?ｎ
	// ぼくと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMAccept:: @ 8247AE3
	.string "좋았어-!\n"
	.string "바로 접수처에서 등록하고 올게!$"
	// よし-!ｎ
	// すぐ うけつけで とうろく してくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMReject:: @ 8247B16
	.string "다음에 만났을 때는\n"
	.string "내 포켓몬 선택해줘!$"
	// つぎに あったときはｎ
	// ぼくの ポケモン えらんでくれよ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFIntro:: @ 8247B3E
	.string "나는\n"
	.string "포켓몬 레인저 {STR_VAR_1}{K_I}야!$"
	// わたしはｎ
	// ポケモンレンジャ- §いよ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon1:: @ 8247B62
	.string "내가 데리고 있는 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わたしが つれている ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon2Ask:: @ 8247B9B
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}야!\p"
	.string "어때?\n"
	.string "나와 태그 맺지 않을래?$"
	// §いを つかう §うよ!ｐ
	// どう?ｎ
	// わたしと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFAccept:: @ 8247BE7
	.string "열심히 할 거야-!\n"
	.string "바로 접수처에서 등록하고 올게!$"
	// がんばるわよ-!ｎ
	// すぐ うけつけで とうろく してくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFReject:: @ 8247C23
	.string "다음에는 꼭\n"
	.string "내 포켓몬을 선택해줘!$"
	// つぎこそｎ
	// わたしの ポケモンを えらんでよね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyIntro:: @ 8247C4E
	.string "저는\n"
	.string "아로마 아가씨\l"
	.string "{STR_VAR_1}{K_I}라고 합니다$"
	// わたくしｎ
	// アロマなおねえさん §いとｌ
	// もうします

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon1:: @ 8247C8C
	.string "제가 데리고 있는 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わたくしの つれている ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon2Ask:: @ 8247CB2
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}입니다\p"
	.string "어떤가요?\n"
	.string "저와 태그를 맺지 않으실래요?$"
	// §いを つかう §うですｐ
	// どうでしょう?ｎ
	// わたくしと タッグを くんでみませんか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyAccept:: @ 8247D07
	.string "영광이네요\n"
	.string "바로 접수처에서 등록하고 올게요!$"
	// こうえいですｎ
	// すぐ うけつけで とうろく してきますね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyReject:: @ 8247D4E
	.string "다음에 만났을 때는\n"
	.string "태그를 맺어주세요...$"
	// つぎに おあいした ときにはｎ
	// タッグを くみたいものですね……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacIntro:: @ 8247D97
	.string "난\n"
	.string "유적마니아 {STR_VAR_1}일세!$"
	// わしｎ
	// いせきマニア §いじゃ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon1:: @ 8247DC7
	.string "내가 지니고 있는 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わしの もっている ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon2Ask:: @ 8247DFE
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}일세!\p"
	.string "어떤가?\n"
	.string "나와 태그를 맺지 않겠나?$"
	// §いを つかう §うじゃ!ｐ
	// どうじゃ?ｎ
	// わしと タッグを くんでみないか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacAccept:: @ 8247E3E
	.string "좋아 좋아!\n"
	.string "바로 접수처에서 등록하고 오겠네!$"
	// よしよし!ｎ
	// すぐ うけつけで とうろく してくるぞい!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacReject:: @ 8247E7E
	.string "흐-음...\n"
	.string "내 포켓몬은 강하다고 생각하는데...$"
	// う-む……ｎ
	// わしの ポケモン つよいと おもうぞ……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMIntro:: @ 8247EA1
	.string "난\n"
	.string "엘리트 트레이너 {STR_VAR_1}!$"
	// ぼくｎ
	// エリ-トトレ-ナ- §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon1:: @ 8247EB5
	.string "내가 데리고 있는 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// ぼくの つれている ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon2Ask:: @ 8247EE9
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}야\p"
	.string "어때?\n"
	.string "나와 태그 맺지 않을래?$"
	// §いを つかう §うだよｐ
	// どう?ｎ
	// ぼくと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMAccept:: @ 8247F3F
	.string "좋았어!\n"
	.string "바로 접수처에서 등록하고 올게!$"
	// よしっ!ｎ
	// すぐ うけつけで とうろく してくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMReject:: @ 8247F6D
	.string "너와 함께라면 최강의 팀이 될 거라고\n"
	.string "생각했는데 말이지...$"
	// きみとなら さいきょうの チ-ムに なるとｎ
	// おもったんだけどな……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFIntro:: @ 8247FA3
	.string "난\n"
	.string "엘리트 트레이너 {STR_VAR_1}!$"
	// わたしはｎ
	// エリ-トトレ-ナ- §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon1:: @ 8247FB7
	.string "내가 키운 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わたしの そだてた ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon2Ask:: @ 8247FE9
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}야\p"
	.string "어때?\n"
	.string "나하고 태그를 맺어보지 않을래?$"
	// §いを つかう §う だよｐ
	// どう?ｎ
	// わたしと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFAccept:: @ 8248031
	.string "해냈다!\n"
	.string "바로 접수처에서 등록하고 올게!$"
	// やったわ!ｎ
	// すぐ うけつけで とうろく してくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFReject:: @ 824805E
	.string "너하고 함께라면 강한 태그팀이\n"
	.string "될 거라고 생각했는데...$"
	// あなたとなら つよい タッグチ-ムがｎ
	// できると おもったのに……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacIntro:: @ 824808D
	.string "나는\n"
	.string "포켓몬 매니아 {STR_VAR_1}{K_I}야!$"
	// オレはｎ
	// かいじゅうマニア §いだ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon1:: @ 82480AB
	.string "내가 지니고 있는 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 가진 {STR_VAR_2}{K_WAGWA}...$"
	// オレの もっている ポケモンはｎ
	// §いを もった §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon2Ask:: @ 82480DC
	.string "{STR_VAR_1}{K_EULREUL} 가진 {STR_VAR_2}{K_I}라고!\p"
	.string "어때?\n"
	.string "나와 태그를 맺지 않을래?$"
	// §いを もった §うだ!ｐ
	// どうだ?ｎ
	// オレと タッグを くんでみないか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacAccept:: @ 8248128
	.string "해냈어!\n"
	.string "바로 접수처에서 등록하고 올게!$"
	// やったぜ!ｎ
	// すぐ うけつけで とうろく してくるぜ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacReject:: @ 8248151
	.string "내 포켓몬 강하다고!\n"
	.string "후회해도 모른다!$"
	// オレの ポケモン つよいぞ!ｎ
	// こうかい しても しらないぞ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerIntro:: @ 824818E
	.string "난\n"
	.string "캠프파이어 {STR_VAR_1}!$"
	// オレｎ
	// キャンプファイヤ- §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon1:: @ 82481A9
	.string "내가 키운 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 가진 {STR_VAR_2}{K_WAGWA}...$"
	// オレの そだてあげた ポケモンはｎ
	// §いを もった §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon2Ask:: @ 82481E1
	.string "{STR_VAR_1}{K_EULREUL} 가진 {STR_VAR_2}{K_I}야\p"
	.string "어때?\n"
	.string "나와 태그를 맺어볼래?$"
	// §いを もった §う だよｐ
	// どうだい?ｎ
	// オレと タッグを くんでみないか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerAccept:: @ 8248221
	.string "좋았어-!\n"
	.string "지금 접수처에 등록하고 온다!$"
	// やった-!ｎ
	// いま うけつけで とうろく してくるからな!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerReject:: @ 824824F
	.string "다음에 만날 때는\n"
	.string "태그를 맺어줘!$"
	// つぎに あったときにはｎ
	// タッグを くんでくれよな!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperIntro:: @ 8248297
	.string "나는\n"
	.string "캠프보이 {STR_VAR_1}!$"
	// ぼくはｎ
	// キャンプボ-イ §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon1:: @ 82482B1
	.string "내가 키운 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// ぼくの そだてた ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon2Ask:: @ 82482DC
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}야\p"
	.string "어때?\n"
	.string "나와 태그를 맺지 않을래?$"
	// §いを つかう §う だよｐ
	// どう?ｎ
	// ぼくと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperAccept:: @ 8248321
	.string "앗싸!\n"
	.string "바로 접수처에 등록하고 올게!$"
	// やったね!ｎ
	// すぐ うけつけで とうろく してくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperReject:: @ 824833D
	.string "다음에 만났을 때는\n"
	.string "태그를 맺어줘!$"
	// つぎに あったときにはｎ
	// タッグを くんでよね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerIntro:: @ 8248369
	.string "저는\n"
	.string "피크닉걸 {STR_VAR_1}입니다!$"
	// わたしはｎ
	// ピクニックガ-ル §いです!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon1:: @ 824838D
	.string "제가 데리고 있는 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わたしの つれている ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon2Ask:: @ 82483C1
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}입니다\p"
	.string "어떤가요?\n"
	.string "저와 태그를 맺지 않으실래요?$"
	// §いを つかう §うですｐ
	// どうすか?ｎ
	// わたしと タッグを くんでみませんか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerAccept:: @ 8248401
	.string "감사합니다!\n"
	.string "바로 접수처에 등록하고 올게요!$"
	// ありがとうございます!ｎ
	// すぐ うけつけで とうろく してきます!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerReject:: @ 8248431
	.string "다음에 만났을 때는\n"
	.string "태그를 맺어주세요$"
	// つぎに あったときにはｎ
	// タッグを くんでくださいね

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMIntro:: @ 8248467
	.string "나는\n"
	.string "초능력자 {STR_VAR_1}!$"
	// ぼくはｎ
	// サイキッカ- §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon1:: @ 8248477
	.string "내가 키운 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// ぼくの そだてた ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon2Ask:: @ 82484AC
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}야\p"
	.string "어때?\n"
	.string "나와 태그를 맺지 않을래?$"
	// §いを つかう §う だよｐ
	// どう?ｎ
	// ぼくと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMAccept:: @ 82484E7
	.string "해냈다!\n"
	.string "바로 접수처에서 등록하고 올게!$"
	// やったね!ｎ
	// すぐ うけつけで とうろく してくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMReject:: @ 8248517
	.string "다음에 만났을 때는\n"
	.string "태그 맺어줬으면 좋겠다...$"
	// つぎに あったときにはｎ
	// タッグを くみたいね……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFIntro:: @ 8248553
	.string "난\n"
	.string "초능력자 {STR_VAR_1}!$"
	// わたしｎ
	// サイキッカ- §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon1:: @ 824856A
	.string "내가 데리고 있는 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わたしが つれている ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon2Ask:: @ 824857D
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}야!\p"
	.string "어때?\n"
	.string "나하고 태그 맺을래?$"
	// §いを つかう §うよ!ｐ
	// どう?ｎ
	// わたしと タッグを くまない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFAccept:: @ 82485E5
	.string "고마워!\n"
	.string "바로 접수처에서 등록하고 올게!$"
	// ありがとう!ｎ
	// すぐ うけつけで とうろく してくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFReject:: @ 8248614
	.string "다음에 만났을 때는\n"
	.string "태그를 맺어줬으면 좋겠다!$"
	// つぎに あったときにはｎ
	// タッグを くみたいわね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFIntro:: @ 824864E
	.string "전\n"
	.string "학원 끝난 아이 {STR_VAR_1}예요!$"
	// わたしｎ
	// じゅくがえり §いです!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon1:: @ 8248661
	.string "제가 데리고 있는 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わたしの つれている ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon2Ask:: @ 8248671
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}입니다!\p"
	.string "어떤가요?\n"
	.string "저하고 태그를 맺지 않으실래요?$"
	// §いを つかう §うです!ｐ
	// どうですか?ｎ
	// わたしと タッグを くんでくれませんか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFAccept:: @ 82486C6
	.string "감사합니다!\n"
	.string "바로 접수처에서 등록하고 올게요!$"
	// ありがとうございます!ｎ
	// すぐ うけつけで とうろく してきます!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFReject:: @ 82486FF
	.string "다음에 만났을 때는\n"
	.string "태그를 맺어주세요...$"
	// つぎに あったときにはｎ
	// タッグを くんでくださいね……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFIntro:: @ 8248725
	.string "난\n"
	.string "포켓몬 브리더 {STR_VAR_1}{K_I}야!$"
	// わたしｎ
	// ポケモンブリ-ダ- §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon1:: @ 8248751
	.string "내가 키운 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わたしの そだてた ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon2Ask:: @ 8248781
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}야\p"
	.string "어때?\n"
	.string "나와 태그를 맺어보지 않을래?$"
	// §いを つかう §う なのｐ
	// どう?ｎ
	// わたしと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFAccept:: @ 82487C9
	.string "해냈다!\n"
	.string "바로 접수처에서 등록하고 올게!$"
	// やったね!ｎ
	// すぐ うけつけで とうろく してくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFReject:: @ 82487F7
	.string "다음에 만났을 때는\n"
	.string "꼭 태그를 맺어줘!$"
	// つぎに あったときにはｎ
	// ぜったいに タッグを くんでよね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFIntro:: @ 8248829
	.string "전\n"
	.string "애호가클럽\l"
	.string "{STR_VAR_1}{K_I}라고 해요$"
	// わたくしｎ
	// だいすきクラブ §いとｌ
	// もうしますのよ

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon1:: @ 824885B
	.string "제가 키운 사랑스러운 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// わたくしの そだてた ポケモンちゃんはｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon2Ask:: @ 8248892
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_I}랍니다\p"
	.string "어떤가요?\n"
	.string "저와 태그를 맺지 않으시겠어요?$"
	// §いを もつ §う ですのｐ
	// どうでしょう?ｎ
	// わたくしと タッグを くみませんか?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFAccept:: @ 82488D8
	.string "감사합니다!\p"
	.string "저 바로\n"
	.string "접수처에 등록하러 갔다 올게요$"
	// ありがとうございます!ｐ
	// わたくし さっそくｎ
	// うけつけで とうろく してきますわ

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFReject:: @ 8248908
	.string "제 사랑스러운 포켓몬\n"
	.string "최고인데 유감이에요...$"
	// わたくしの ポケモンちゃんｎ
	// さいこうなのに ざんねんです……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFIntro:: @ 824894B
	.string "난\n"
	.string "비키니 아가씨 {STR_VAR_1}!$"
	// わたしｎ
	// ビキニのおねえさん §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon1:: @ 824895F
	.string "내가 키운 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 가진 {STR_VAR_2}{K_WAGWA}...$"
	// わたしの そだてた ポケモンはｎ
	// §いを もった §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon2Ask:: @ 824896F
	.string "{STR_VAR_1}{K_EULREUL} 가진 {STR_VAR_2}{K_I}야\p"
	.string "어때?\n"
	.string "나하고 태그 맺어볼래?$"
	// §いを もった §うよっｐ
	// どう?ｎ
	// わたしと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFAccept:: @ 82489BD
	.string "해냈다!\n"
	.string "바로 접수처에서 등록하고 올게!$"
	// やったねっ!ｎ
	// すぐ うけつけで とうろく してくるねっ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFReject:: @ 82489E7
	.string "다음에 만났을 때는\n"
	.string "태그를 맺어줘!$"
	// つぎに あったときにはｎ
	// タッグを くんでよねっ!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMIntro:: @ 8248A10
	.string "난\n"
	.string "트라이애슬리트 {STR_VAR_1}!$"
	// オレｎ
	// トライアスリ-ト §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon1:: @ 8248A40
	.string "내가 키운 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// オレの そだてた ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon2Ask:: @ 8248A72
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}야\p"
	.string "어때?\n"
	.string "나와 태그 맺어볼래?$"
	// §いを つかう §う だよｐ
	// どう?ｎ
	// オレと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMAccept:: @ 8248AC0
	.string "해냈다!\n"
	.string "바로 접수처에서 등록하고 올게!$"
	// やったね!ｎ
	// すぐ うけつけで とうろく してくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMReject:: @ 8248AEB
	.string "다음에 만났을 때는\n"
	.string "태그 맺어줘야 돼!$"
	// つぎに あったときにはｎ
	// タッグを くんでくれよな!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFIntro:: @ 8248B22
	.string "난\n"
	.string "트라이애슬리트 {STR_VAR_1}!$"
	// わたしｎ
	// トライアスリ-ト §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon1:: @ 8248B39
	.string "내가 키운 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_WAGWA}...$"
	// わたしの そだてた ポケモンはｎ
	// §いを つかう §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon2Ask:: @ 8248B4C
	.string "{STR_VAR_1}{K_EULREUL} 쓰는 {STR_VAR_2}{K_I}야\p"
	.string "어때?\n"
	.string "나하고 태그 맺어볼래?$"
	// §いを つかう §うよｐ
	// どう?ｎ
	// わたしと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFAccept:: @ 8248BB4
	.string "해냈다!\n"
	.string "바로 접수처에서 등록하고 올게!$"
	// やったね!ｎ
	// すぐ うけつけで とうろく してくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFReject:: @ 8248BEE
	.string "다음에 만났을 때는\n"
	.string "태그 맺어줘!$"
	// つぎに あったときにはｎ
	// タッグを くんでよね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMIntro:: @ 8248C2E
	.string "난\n"
	.string "수영팬티소년 {STR_VAR_1}!$"
	// オレｎ
	// かいパンやろう §い!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon1:: @ 8248C5B
	.string "내가 키운 포켓몬은\n"
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_WAGWA}...$"
	// オレが そだてた ポケモンはｎ
	// §いを もつ §うと……

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon2Ask:: @ 8248C90
	.string "{STR_VAR_1}{K_EULREUL} 지닌 {STR_VAR_2}{K_I}야\p"
	.string "어때?\n"
	.string "나하고 태그 맺어볼래?$"
	// §いを もつ §うだよｐ
	// どう?ｎ
	// オレと タッグを くんでみない?

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMAccept:: @ 8248CCF
	.string "해냈어!\n"
	.string "바로 접수처에 등록하고 올게!$"
	// やったね!ｎ
	// すぐ うけつけで とうろく してくるね!

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMReject:: @ 8248D04
	.string "다음에 만났을 때는\n"
	.string "태그 맺어주라!$"
	// つぎに あったときにはｎ
	// タッグを くんでくれよな!

