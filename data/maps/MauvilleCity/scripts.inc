.set LOCALID_WALLY, 6
.set LOCALID_WALLYS_UNCLE, 7
.set LOCALID_SCOTT, 11

MauvilleCity_MapScripts:: @ 81DF385
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_OnTransition
	.byte 0

MauvilleCity_OnTransition: @ 81DF38B
	setflag FLAG_VISITED_MAUVILLE_CITY
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	clearflag FLAG_HIDE_SLATEPORT_MUSEUM_POPULATION
	setflag FLAG_SYS_TV_START
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	setvar VAR_MAUVILLE_GYM_STATE, 0
	call_if_set FLAG_GOT_TM24_FROM_WATTSON, MauvilleCity_EventScript_MoveWattsonBackToGym
	end

MauvilleCity_EventScript_MoveWattsonBackToGym:: @ 81DF3A9
	clearflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	setflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setflag FLAG_WATTSON_REMATCH_AVAILABLE
	return

MauvilleCity_EventScript_Boy:: @ 81DF3B3
	msgbox MauvilleCity_Text_NurseHurtMonBackToHealth, MSGBOX_NPC
	end

MauvilleCity_EventScript_Maniac:: @ 81DF3BC
	msgbox MauvilleCity_Text_AllSortsOfPeopleComeThrough, MSGBOX_NPC
	end

MauvilleCity_EventScript_Woman:: @ 81DF3C5
	msgbox MauvilleCity_Text_RydelVeryGenerous, MSGBOX_NPC
	end

MauvilleCity_EventScript_RichBoy:: @ 81DF3CE
	msgbox MauvilleCity_Text_PokemonCanJumpYouOnBike, MSGBOX_NPC
	end

MauvilleCity_EventScript_CitySign:: @ 81DF3D7
	msgbox MauvilleCity_Text_CitySign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GymSign:: @ 81DF3E0
	msgbox MauvilleCity_Text_GymSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_BikeShopSign:: @ 81DF3E9
	msgbox MauvilleCity_Text_BikeShopSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GameCornerSign:: @ 81DF3F2
	msgbox MauvilleCity_Text_GameCornerSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_SchoolKidM:: @ 81DF3FB
	lock
	faceplayer
	goto_if_set FLAG_TV_EXPLAINED, MauvilleCity_EventScript_TVExplained
	msgbox MauvilleCity_Text_ExplainTV, MSGBOX_DEFAULT
	setflag FLAG_TV_EXPLAINED
	release
	end

MauvilleCity_EventScript_TVExplained:: @ 81DF413
	msgbox MauvilleCity_Text_BeenCheckingOutTV, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallysUncle:: @ 81DF41D
	lock
	faceplayer
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_UncleAskPlayerToBattleWally
	msgbox MauvilleCity_Text_UncleHesTooPeppy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_UncleAskPlayerToBattleWally:: @ 81DF43D
	msgbox MauvilleCity_Text_UncleCanYouBattleWally, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_Wally:: @ 81DF452
	lockall
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_WallyRequestBattleAgain
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWantToChallengeGym, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_UncleYourePushingIt, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_WallyWeCanBeatAnyone, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWillYouBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_EventScript_BattleWallyPrompt:: @ 81DF4AD
	compare VAR_RESULT, YES
	call_if_eq MauvilleCity_EventScript_BattleWally
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_EventScript_DeclineWallyBattle
	closemessage
	switch VAR_FACING
	case DIR_NORTH, MauvilleCity_EventScript_WallyAndUncleExitNorth
	case DIR_EAST, MauvilleCity_EventScript_WallyAndUncleExitEast
	end

MauvilleCity_EventScript_WallyAndUncleExitNorth:: @ 81DF4E0
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth1
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitNorth1
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth1
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerFaceUncleNorth
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerNorth
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth2
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth2
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitNorth2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_WallyAndUncleExitEast:: @ 81DF53D
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast1
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitEast1
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast1
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 30
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerEast
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast2
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast2
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitEast2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_DefeatedWally:: @ 81DF593
	removeobject LOCALID_WALLY
	removeobject LOCALID_WALLYS_UNCLE
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLYS_UNCLE
	setflag FLAG_DEFEATED_WALLY_MAUVILLE
	setvar VAR_WALLY_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	compare VAR_FACING, DIR_NORTH
	call_if_eq MauvilleCity_EventScript_ScottApproachPlayerNorth
	compare VAR_FACING, DIR_EAST
	call_if_eq MauvilleCity_EventScript_ScottApproachPlayerEast
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox MauvilleCity_Text_ScottYouDidntHoldBack, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SCOTT_STATE, 1
	compare VAR_FACING, DIR_NORTH
	call_if_eq MauvilleCity_EventScript_ScottExitNorth
	compare VAR_FACING, DIR_EAST
	call_if_eq MauvilleCity_EventScript_ScottExitEast
	removeobject LOCALID_SCOTT
	releaseall
	end

MauvilleCity_EventScript_ScottApproachPlayerNorth:: @ 81DF5F3
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottApproachPlayerNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottApproachPlayerEast:: @ 81DF601
	setobjectxyperm LOCALID_SCOTT, 12, 13
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottApproachPlayerEast
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitNorth:: @ 81DF616
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitNorth
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottExitNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitEast:: @ 81DF628
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitEast
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottExitEast
	waitmovement 0
	return

MauvilleCity_EventScript_BattleWally:: @ 81DF63A
	msgbox MauvilleCity_Text_WallyHereICome, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_MAUVILLE, MauvilleCity_Text_WallyDefeat
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyIllGoBackToVerdanturf, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_ThankYouNotEnoughToBattle, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox MauvilleCity_Text_UncleNoNeedToBeDown, MSGBOX_DEFAULT
	return

MauvilleCity_EventScript_DeclineWallyBattle:: @ 81DF683
	setflag FLAG_DECLINED_WALLY_BATTLE_MAUVILLE
	msgbox MauvilleCity_Text_WallyMyUncleWontKnowImStrong, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallyRequestBattleAgain:: @ 81DF690
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_WallyPleaseBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_Movement_WallyExitNorth1: @ 81DF6A8
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

MauvilleCity_Movement_WallyExitEast1: @ 81DF6AE
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallyExitNorth2: @ 81DF6B4
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_WallyExitEast2: @ 81DF6C0
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth2: @ 81DF6CC
	delay_16
	delay_8
	walk_in_place_fastest_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast2: @ 81DF6D0
	delay_16
	delay_16
	delay_16
	walk_in_place_fastest_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitNorth: @ 81DF6D5
	delay_16
	walk_in_place_fastest_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitEast: @ 81DF6D8
	delay_16
	delay_16
	walk_in_place_fastest_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast1: @ 81DF6DC
	delay_16
	walk_in_place_fastest_down
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth1: @ 81DF6DF
	delay_16
	walk_in_place_fastest_left
	step_end

MauvilleCity_Movement_WallysUncleExitNorth1: @ 81DF6E2
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

MauvilleCity_Movement_WallysUncleExitEast1: @ 81DF6E8
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_PlayerFaceUncleNorth: @ 81DF6EE
	delay_16
	delay_8
	delay_4
	walk_in_place_fastest_down
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerNorth: @ 81DF6F3
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerEast: @ 81DF6F7
	walk_right
	walk_up
	step_end

MauvilleCity_Movement_WallysUncleExitNorth2: @ 81DF6FA
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallysUncleExitEast2: @ 81DF703
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottApproachPlayerNorth: @ 81DF70D
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_up
	step_end

MauvilleCity_Movement_ScottApproachPlayerEast: @ 81DF719
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

MauvilleCity_Movement_ScottExitNorth: @ 81DF725
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottExitEast: @ 81DF72F
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_EventScript_Wattson:: @ 81DF73A
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM24_FROM_WATTSON, MauvilleCity_EventScript_ReceivedThunderbolt
	compare VAR_NEW_MAUVILLE_STATE, 2
	goto_if_eq MauvilleCity_EventScript_CompletedNewMauville
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, MauvilleCity_EventScript_BegunNewMauville
	msgbox MauvilleCity_Text_WattsonNeedFavorTakeKey, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_BegunNewMauville:: @ 81DF77A
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CompletedNewMauville:: @ 81DF784
	msgbox MauvilleCity_Text_WattsonThanksTakeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM24
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM24_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_ReceivedThunderbolt:: @ 81DF7B0
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_RegisterWallyCall:: @ 81DF7BA
	lockall
	pokenavcall MauvilleCity_Text_WallyPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Text_RegisteredWally, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WALLY_MATCH_CALL
	clearflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	releaseall
	end

MauvilleCity_Text_UncleHesTooPeppy: @ 81DF7DC
	.string "작은아버지: 이 애는 포켓몬 덕분에\n"
	.string "건강해진 모양이지만\l"
	.string "너무 건강해진 걸지도 몰라...$"
	// おじさん『このこは ポケモンの おかげでｎ
	// げんきに なれたような もんだけどｌ
	// ちょっと げんきに なりすぎ なんだ……

MauvilleCity_Text_WallyWantToChallengeGym: @ 81DF845
	.string "민진: 작은아버지 부탁이에요!\p"
	.string "제가 얼마나 강해졌는지\n"
	.string "이 체육관에서 확인하고 싶어요!\p"
	.string "네 네 괜찮죠!?$"
	// ミツル『おじさん おねがい だから!ｐ
	// じぶんが どれくらい つよくなったかｎ
	// このジムで ためして みたいんだ!ｐ
	// ね ね いいでしょう!?

MauvilleCity_Text_UncleYourePushingIt: @ 81DF8B9
	.string "작은아버지: 이것 참 민진아!\p"
	.string "확실히 포켓몬과 같이\n"
	.string "살게 되면서\l"
	.string "너는 꽤나 건강해졌어!\p"
	.string "그렇다고 갑자기 포켓몬체육관에\n"
	.string "도전하는 건 무리 아니냐?$"
	// おじさん『まあまあ ミツルくん!ｐ
	// たしかに ポケモンと いっしょにｎ
	// くらすように なってからｌ
	// きみは ずいぶん げんきに なった!ｐ
	// だからって いきなり ポケモンジムにｎ
	// ちょうせん なんて むり してないかい?

MauvilleCity_Text_WallyWeCanBeatAnyone: @ 81DF963
	.string "민진: 무리가 아니에요\p"
	.string "저와 랄토스가 힘을 합치면\n"
	.string "누구든지 이길 수 있다구요!$"
	// ミツル『むり なんか してませんｐ
	// ぼくと ラルトスが ちからを あわせればｎ
	// だれにだって かてる はずです!

MauvilleCity_Text_WallyWillYouBattleMe: @ 81DF9B2
	.string "민진: 앗! {PLAYER}님!\p"
	.string "저 그때보다 강해졌어요!\p"
	.string "그걸 {PLAYER}님도\n"
	.string "작은아버지도\l"
	.string "알아주셨으면 좋겠어요!\p"
	.string "{PLAYER}님 부탁입니다!\n"
	.string "저와 포켓몬 승부해주세요$"
	// ミツル『あっ! §あさん!ｐ
	// ぼく あれから つよくなったんだ!ｐ
	// それを §あさんにもｎ
	// おじさんにも わかって もらいたいんです!ｐ
	// §あさん おねがいです!ｎ
	// ぼくと しょうぶ してください

MauvilleCity_Text_WallyMyUncleWontKnowImStrong: @ 81DFA4A
	.string "민진: {PLAYER}님이\n"
	.string "저와 승부해주지 않으면...\p"
	.string "작은아버지는 제가 강해졌다는 걸\n"
	.string "알아주지 않을 거라구요...$"
	// ミツル『§あさんがｎ
	// ぼくと しょうぶ してくれないと……ｐ
	// おじさんに ぼくが つよくなったことｎ
	// わかって もらえないよ……

MauvilleCity_Text_UncleCanYouBattleWally: @ 81DFAA5
	.string "작은아버지: 너...\n"
	.string "{PLAYER}{K_I}라고 했니?\p"
	.string "미안하지만 민진과\n"
	.string "승부해주지 않을래?\p"
	.string "이대로라면 무슨 말을 해도\n"
	.string "안 들을 것 같아...$"
	// おじさん『§あ§おとやらｎ
	// わるいけど ミツルくんとｌ
	// しょうぶ してあげて くれないかな?ｐ
	// このままだと なにを いってもｎ
	// きいて もらえそうに ないよ

MauvilleCity_Text_WallyPleaseBattleMe: @ 81DFB42
	.string "민진: {PLAYER}님 부탁입니다!\n"
	.string "저와 승부해주세요$"
	// ミツル『§あさん おねがいです!ｎ
	// ぼくと しょうぶ してください

MauvilleCity_Text_WallyHereICome: @ 81DFB6D
	.string "민진: 고맙습니다 {PLAYER}님\p"
	.string "그럼... 시작할게요!$"
	// ミツル『ありがとう §あさんｐ
	// それでは…… いきますね!

MauvilleCity_Text_WallyDefeat: @ 81DFB96
	.string "민진: ...... ...... ...... ......\p"
	.string "...... ...... ...... ......\p"
	.string "제 패배입니다...$"
	// ミツル『…… …… …… ……ｐ
	// …… …… …… ……ｐ
	// ぼくの まけ です……

MauvilleCity_Text_WallyIllGoBackToVerdanturf: @ 81DFBC3
	.string "민진: 작은아버지...\n"
	.string "저 잔디마을로 돌아갈게요$"
	// ミツル『おじさん……ｎ
	// ぼく シダケに もどります

MauvilleCity_Text_ThankYouNotEnoughToBattle: @ 81DFBED
	.string "{PLAYER}님 고맙습니다\n"
	.string "역시 트레이너란 대단하네요\p"
	.string "단지 포켓몬과 같이 배틀하는 걸로는\n"
	.string "안 되는군요...\p"
	.string "진정한 의미의 트레이너는\n"
	.string "될 수 없는 걸까요...$"

MauvilleCity_Text_UncleNoNeedToBeDown: @ 81DFC8A
	.string "작은아버지: 민진아\n"
	.string "그렇게 기죽을 필요는 없단다\p"
	.string "앞으로 더욱더\n"
	.string "강해지면 되잖니!\p"
	.string "자 집으로 가자\n"
	.string "다들 기다리고 있어$"

MauvilleCity_Text_UncleVisitUsSometime: @ 81DFD34
	.string "작은아버지: 그렇군 민진이\n"
	.string "포켓몬을 잡는 걸\l"
	.string "지켜봐 준 것은\p"
	.string "{PLAYER}!\n"
	.string "너였구나\p"
	.string "시간이 나면 잔디마을에 있는\n"
	.string "우리 집에 놀러와줬으면 좋겠어\l"
	.string "민진이도 반드시 기뻐할 거야$"

MauvilleCity_Text_WallyPokenavCall: @ 81DFDFB
	.string "...... ...... ......\n"
	.string "...... ...... ...... 삑!\p"
	.string "민진: 앗 {PLAYER}님!\n"
	.string "있죠 작은아버지 저를 위해서\l"
	.string "포켓내비를 손에 넣어주셨어요!\p"
	.string "이걸로 언제든지 {PLAYER}님과\n"
	.string "연락할 수 있겠네요!\p"
	.string "...... ...... ......\n"
	.string "...... ...... ...... 삐-$"
	// …… …… ……ｎ
	// …… …… …… ピッ!ｐ
	// ミツル『あっ §あさん!ｎ
	// あのね おじさんが ぼくのためにｌ
	// ポケナビを てにいれて くれたんです!ｐ
	// これで いつでも §あさんとｎ
	// れんらくが とれますね!ｐ
	// …… …… ……ｎ
	// …… …… …… ツ-
	
MauvilleCity_Text_RegisteredWally: @ 81DFEB4
	.string "민진을\n"
	.string "포켓내비에 등록했다!$"
	// ミツルをｎ
	// ポケナビに とうろく した!

MauvilleCity_Text_ScottYouDidntHoldBack: @ 81DFED5
	.string "금작화: 헤헤...\n"
	.string "지금의 승부 보고 있었어!\p"
	.string "너는 그 민진이라고 하는\n"
	.string "소년과 친구인 거지?\p"
	.string "그런데도 봐주지 않고 싸워\n"
	.string "훌륭하게 완승하다니...\p"
	.string "음! 그래야말로 진정한\n"
	.string "포켓몬 승부라고 할 수 있지!\p"
	.string "나는 그런 트레이너가\n"
	.string "엄청 좋아-!\p"
	.string "...... ...... ......\n"
	.string "앞으로도 응원하고 있을게!$"
	// エニシダ『へへ……ｎ
	// いまの しょうぶ みていたよ!ｐ
	// きみは あの ミツルくん とかいうｎ
	// しょうねんと ともだち なんだろう?ｐ
	// それなのに てかげん せずに たたかいｎ
	// みごとに うちまかした……ｐ
	// うん! それでこそ ほんとうのｎ
	// ポケモン しょうぶ と いうものだ!ｐ
	// わたしは そういう トレ-ナ-がｎ
	// だいすきだな-!ｐ
	// …… …… ……ｎ
	// これからも おうえん しているよ!

MauvilleCity_Text_WattsonNeedFavorTakeKey: @ 81DFFE4
	.string "암페어: 오오 {PLAYER}!\n"
	.string "건강해 보이는구나!\l"
	.string "와하하하핫! 좋은데!\p"
	.string "좋아! 결정했다!\n"
	.string "{PLAYER}에게 부탁을 하마!\p"
	.string "사실 이 보라시티에는\n"
	.string "뉴보라라고 하는 지하 도시가 있단다\p"
	.string "그래서 {PLAYER}에게는\n"
	.string "그곳의 발전 장치의 스위치를\l"
	.string "꺼주었으면 한다!\p"
	.string "요즘 발전 장치가\n"
	.string "폭주해서 위험하니까 말이다\p"
	.string "여기 뉴보라의\n"
	.string "문을 여는 열쇠를 주마!$"

MauvilleCity_Text_WattsonWontBeChallenge: @ 81E0154
	.string "암페어: 음?\n"
	.string "자네라면 괜찮을 거다!\p"
	.string "참고로 뉴보라의 입구는\n"
	.string "110번 도로에서 파도타기로\l"
	.string "금방 갈 수 있단다\p"
	.string "그럼 잘 부탁하마!\n"
	.string "와하하하핫!$"

MauvilleCity_Text_WattsonThanksTakeTM: @ 81E020E
	.string "암페어: 와하하하핫!\p"
	.string "역시 {PLAYER}! 자네에게\n"
	.string "부탁한게 정답이었어!\p"
	.string "이건 답례라네\n"
	.string "기술머신 10만볼트다\p"
	.string "사양 말고 가져가게나!$"

MauvilleCity_Text_WattsonYoungTakeCharge: @ 81E02AA
	.string "암페어: 와하하하핫!\p"
	.string "젊은이들의 모습을 보는 건\n"
	.string "즐거운걸!$"

MauvilleCity_Text_NurseHurtMonBackToHealth: @ 81E0301
	.string "포켓몬 승부도 좋지만\p"
	.string "만약 자기 포켓몬이\n"
	.string "배틀에서 다쳤다면\l"
	.string "상냥하게 돌봐줘야지!$"

MauvilleCity_Text_AllSortsOfPeopleComeThrough: @ 81E037C
	.string "이 마을은 동서남북으로\n"
	.string "길이 뻗어 있어서\l"
	.string "다양한 사람이 찾아오죠!$"

MauvilleCity_Text_RydelVeryGenerous: @ 81E03FB
	.string "너 사이클숍에는\n"
	.string "벌써 가봤니?\p"
	.string "그곳의 주인인 카제노님은\n"
	.string "정말 인심이 좋단다!$"

MauvilleCity_Text_PokemonCanJumpYouOnBike: @ 81E044A
	.string "자전거에 타고 있어도\n"
	.string "야생 포켓몬은 튀어나오지!$"

MauvilleCity_Text_CitySign: @ 81E0485
	.string "여기는 보라시티\n"
	.string "밝게 빛나는 즐거운 마을$"

MauvilleCity_Text_GymSign: @ 81E04B7
	.string "보라시티 포켓몬체육관\n"
	.string "관장 암페어\l"
	.string "밝은 전격 아저씨!$"

MauvilleCity_Text_BikeShopSign: @ 81E0504
	.string "자갈길 달리면 마음도 즐거워진다!\n"
	.string "“카제노 사이클숍”$"

MauvilleCity_Text_GameCornerSign: @ 81E053C
	.string "누구나 놀 수 있는 근사한 장소!\n"
	.string "“보라시티 게임코너”$"

MauvilleCity_Text_ExplainTV: @ 81E056A
	.string "있지 너\n"
	.string "TV 확인하고 있니?\p"
	.string "최근 재미있는\n"
	.string "방송이 갑자기 늘어났어!\p"
	.string "TV는 좋은 것 같아!\p"
	.string "갑자기 친구가\n"
	.string "소개되거나\p"
	.string "모르는 새 자기가\n"
	.string "방송에 나오기도 해\p"
	.string "언젠가 나도\n"
	.string "방송에 나가 보고 싶어-\p"
	.string "너도 자주 확인하도록 해!$"

MauvilleCity_Text_BeenCheckingOutTV: @ 81E0699
	.string "안녕!\n"
	.string "TV 제대로 확인하고 있니?$"
