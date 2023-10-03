.set LOCALID_CAPT_STERN, 4
.set LOCALID_SS_TIDAL, 5
.set LOCALID_GRUNT, 6
.set LOCALID_ARCHIE, 7
.set LOCALID_SUBMARINE, 8

SlateportCity_Harbor_MapScripts:: @ 820C97D
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_Harbor_OnTransition
	.byte 0

SlateportCity_Harbor_OnTransition: @ 820C983
	setescapewarp MAP_SLATEPORT_CITY, 255, 28, 13
	setvar VAR_TEMP_1, 0
	compare VAR_SLATEPORT_HARBOR_STATE, 1
	call_if_eq SlateportCity_Harbor_EventScript_ReadyAquaEscapeScene
	call_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_Harbor_EventScript_ShowSSTidal
	end

SlateportCity_Harbor_EventScript_ShowSSTidal:: @ 820C9A5
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_SS_TIDAL
	return

SlateportCity_Harbor_EventScript_ReadyAquaEscapeScene:: @ 820C9A9
	savebgm MUS_ENCOUNTER_AQUA
	setobjectxyperm LOCALID_CAPT_STERN, 12, 13
	setobjectmovementtype LOCALID_CAPT_STERN, MOVEMENT_TYPE_FACE_LEFT
	setflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_PATRONS
	return

SlateportCity_Harbor_EventScript_AquaEscapeTrigger0:: @ 820C9BB
	lockall
	setvar VAR_0x8008, 0
	goto SlateportCity_Harbor_EventScript_AquaEscapeScene
	end

SlateportCity_Harbor_EventScript_AquaEscapeTrigger1:: @ 820C9C7
	lockall
	setvar VAR_0x8008, 1
	goto SlateportCity_Harbor_EventScript_AquaEscapeScene
	end

SlateportCity_Harbor_EventScript_AquaEscapeTrigger2:: @ 820C9D3
	lockall
	setvar VAR_0x8008, 2
	goto SlateportCity_Harbor_EventScript_AquaEscapeScene
	end

SlateportCity_Harbor_EventScript_AquaEscapeTrigger3:: @ 820C9DF
	lockall
	setvar VAR_0x8008, 3
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_Harbor_Movement_PlayerWalkUp
	waitmovement 0
	goto SlateportCity_Harbor_EventScript_AquaEscapeScene
	end

SlateportCity_Harbor_EventScript_AquaEscapeScene:: @ 820C9F5
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	applymovement LOCALID_GRUNT, Common_Movement_WalkInPlaceFastestDown
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox SlateportCity_Harbor_Text_ArchieYouAgainHideoutInLilycove, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, SlateportCity_Harbor_Movement_AquaBoardSub
	applymovement LOCALID_ARCHIE, SlateportCity_Harbor_Movement_AquaBoardSub
	applymovement LOCALID_SUBMARINE, SlateportCity_Harbor_Movement_SubmarineExit
	waitmovement 0
	removeobject LOCALID_GRUNT
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_SUBMARINE
	setvar VAR_SLATEPORT_HARBOR_STATE, 2
	setflag FLAG_MET_TEAM_AQUA_HARBOR
	setflag FLAG_HIDE_LILCOVE_MOTEL_SCOTT
	compare VAR_0x8008, 0
	call_if_eq SlateportCity_Harbor_EventScript_SternApproachPlayer0
	compare VAR_0x8008, 1
	call_if_eq SlateportCity_Harbor_EventScript_SternApproachPlayer1
	compare VAR_0x8008, 2
	call_if_eq SlateportCity_Harbor_EventScript_SternApproachPlayer
	compare VAR_0x8008, 3
	call_if_eq SlateportCity_Harbor_EventScript_SternApproachPlayer
	msgbox SlateportCity_Harbor_Text_CaptSternWhyStealMySubmarine, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HIDE_AQUA_HIDEOUT_1F_GRUNT_1_BLOCKING_ENTRANCE
	setflag FLAG_HIDE_AQUA_HIDEOUT_1F_GRUNT_2_BLOCKING_ENTRANCE
	copyobjectxytoperm LOCALID_CAPT_STERN
	setobjectmovementtype LOCALID_CAPT_STERN, MOVEMENT_TYPE_FACE_RIGHT
	releaseall
	end

SlateportCity_Harbor_EventScript_SternApproachPlayer0:: @ 820CA89
	applymovement LOCALID_CAPT_STERN, SlateportCity_Harbor_Movement_SternApproachPlayer0
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

SlateportCity_Harbor_EventScript_SternApproachPlayer1:: @ 820CA9E
	applymovement LOCALID_CAPT_STERN, SlateportCity_Harbor_Movement_SternApproachPlayer1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

SlateportCity_Harbor_EventScript_SternApproachPlayer:: @ 820CAB3
	applymovement LOCALID_CAPT_STERN, SlateportCity_Harbor_Movement_SternApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

SlateportCity_Harbor_Movement_AquaBoardSub: @ 820CAC8
	delay_16
	delay_16
	jump_up
	set_invisible
	step_end

@ Unused, Archie instead shares above identical movement script with Grunt
SlateportCity_Harbor_Movement_ArchieBoardSub: @ 820CACD
	delay_16
	delay_16
	jump_up
	set_invisible
	step_end

SlateportCity_Harbor_Movement_SubmarineExit: @ 820CAD2
	delay_16
	delay_16
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

SlateportCity_Harbor_Movement_SternApproachPlayer0: @ 820CAE0
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

SlateportCity_Harbor_Movement_SternApproachPlayer1: @ 820CAE6
	walk_left
	walk_left
	walk_up
	walk_left
	step_end

SlateportCity_Harbor_Movement_SternApproachPlayer: @ 820CAEB
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_Harbor_Movement_PlayerWalkUp: @ 820CAEF
	walk_up
	step_end

SlateportCity_Harbor_EventScript_FerryAttendant:: @ 820CAF1
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_Harbor_EventScript_AskForTicket
	msgbox SlateportCity_Harbor_Text_FerryServiceUnavailable, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_AskForTicket:: @ 820CB06
	msgbox SlateportCity_Harbor_Text_MayISeeYourTicket, MSGBOX_DEFAULT
	message SlateportCity_Harbor_Text_FlashedTicketWhereTo
	waitmessage
	goto SlateportCity_Harbor_EventScript_ChooseDestination
	end

SlateportCity_Harbor_EventScript_ChooseDestination:: @ 820CB1A
	goto_if_set FLAG_MET_SCOTT_ON_SS_TIDAL, SlateportCity_Harbor_EventScript_ChooseDestinationWithBattleFrontier
	multichoicedefault 18, 8, MULTI_SSTIDAL_SLATEPORT_NO_BF, 2, 0
	switch VAR_RESULT
	case 0, SlateportCity_Harbor_EventScript_Lilycove
	case 1, SlateportCity_Harbor_EventScript_CancelDestinationSelect
	case MULTI_B_PRESSED, SlateportCity_Harbor_EventScript_CancelDestinationSelect
	end

SlateportCity_Harbor_EventScript_ChooseDestinationWithBattleFrontier:: @ 820CB50
	multichoicedefault 17, 6, MULTI_SSTIDAL_SLATEPORT_WITH_BF, 2, 0
	switch VAR_RESULT
	case 0, SlateportCity_Harbor_EventScript_Lilycove
	case 1, SlateportCity_Harbor_EventScript_BattleFrontier
	case 2, SlateportCity_Harbor_EventScript_CancelDestinationSelect
	case MULTI_B_PRESSED, SlateportCity_Harbor_EventScript_CancelDestinationSelect
	end

@ Unused. Should be impossible for player to reach Ferry without having received SS Tidal ticket
SlateportCity_Harbor_EventScript_NoTicket:: @ 820CB88
	msgbox SlateportCity_Harbor_Text_YouMustHaveTicket, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_Lilycove:: @ 820CB92
	msgbox SlateportCity_Harbor_Text_LilycoveItIs, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SlateportCity_Harbor_EventScript_ChooseNewDestination
	setvar VAR_SS_TIDAL_STATE, SS_TIDAL_BOARD_SLATEPORT
	call SlateportCity_Harbor_EventScript_BoardFerry
	warp MAP_SS_TIDAL_CORRIDOR, 255, 1, 10
	waitstate
	release
	end

SlateportCity_Harbor_EventScript_BattleFrontier:: @ 820CBBA
	msgbox SlateportCity_Harbor_Text_BattleFrontierItIs, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SlateportCity_Harbor_EventScript_ChooseNewDestination
	call SlateportCity_Harbor_EventScript_BoardFerry
	warp MAP_BATTLE_FRONTIER_OUTSIDE_WEST, 255, 19, 67
	waitstate
	release
	end

SlateportCity_Harbor_EventScript_ChooseNewDestination:: @ 820CBDD
	message SlateportCity_Harbor_Text_WhereWouldYouLikeToGo
	waitmessage
	goto SlateportCity_Harbor_EventScript_ChooseDestination
	end

SlateportCity_Harbor_EventScript_BoardFerry:: @ 820CBE9
	msgbox SlateportCity_Harbor_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 30
	hideobjectat VAR_LAST_TALKED, MAP_SLATEPORT_CITY_HARBOR
	compare VAR_FACING, DIR_NORTH
	call_if_eq SlateportCity_Harbor_EventScript_BoardFerryNorth
	compare VAR_FACING, DIR_EAST
	call_if_eq SlateportCity_Harbor_EventScript_BoardFerryEast
	delay 30
	hideobjectat OBJ_EVENT_ID_PLAYER, 0
	setvar VAR_0x8004, LOCALID_SS_TIDAL
	call Common_EventScript_FerryDepart
	return

SlateportCity_Harbor_EventScript_CancelDestinationSelect:: @ 820CC2D
	msgbox SlateportCity_Harbor_Text_SailAnotherTime, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_BoardFerryEast:: @ 820CC37
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_Harbor_Movement_BoardFerryEast
	waitmovement 0
	return

SlateportCity_Harbor_EventScript_BoardFerryNorth:: @ 820CC42
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_Harbor_Movement_BoardFerryNorth
	waitmovement 0
	return

SlateportCity_Harbor_Movement_BoardFerryEast: @ 820CC4D
	walk_right
	walk_in_place_fastest_up
	step_end

SlateportCity_Harbor_Movement_BoardFerryNorth: @ 820CC50
	walk_up
	step_end

SlateportCity_Harbor_EventScript_Sailor:: @ 820CC52
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, SlateportCity_Harbor_EventScript_SailorNoAbnormalWeather
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, SlateportCity_Harbor_EventScript_CountDefeatedLegendary
	call_if_set FLAG_DEFEATED_GROUDON, SlateportCity_Harbor_EventScript_CountDefeatedLegendary
	compare VAR_0x8004, 2  @ Defeated both
	goto_if_eq SlateportCity_Harbor_EventScript_SailorNoAbnormalWeather
	msgbox SlateportCity_Harbor_Text_AbnormalWeather, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_SailorNoAbnormalWeather:: @ 820CC89
	msgbox SlateportCity_Harbor_Text_LoveToGoDeepUnderwaterSomeday, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_CountDefeatedLegendary:: @ 820CC93
	addvar VAR_0x8004, 1
	return

SlateportCity_Harbor_EventScript_FatMan:: @ 820CC99
	msgbox SlateportCity_Harbor_Text_SubTooSmallForMe, MSGBOX_NPC
	end

SlateportCity_Harbor_EventScript_CaptStern:: @ 820CCA2
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, SlateportCity_Harbor_EventScript_CaptSternFerryOrScannerComment
	goto_if_set FLAG_EVIL_TEAM_ESCAPED_STERN_SPOKE, SlateportCity_Harbor_EventScript_NeedDive
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, SlateportCity_Harbor_EventScript_TeamAquaLeftNeedDive
	compare VAR_SLATEPORT_HARBOR_STATE, 2
	goto_if_eq SlateportCity_Harbor_EventScript_WhyStealSubmarine
	msgbox SlateportCity_Harbor_Text_SameThugsTriedToRobAtMuseum, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_Harbor_EventScript_WhyStealSubmarine:: @ 820CCDF
	msgbox SlateportCity_Harbor_Text_CaptSternWhyStealMySubmarine, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_TeamAquaLeftNeedDive:: @ 820CCE9
	setflag FLAG_EVIL_TEAM_ESCAPED_STERN_SPOKE
	msgbox SlateportCity_Harbor_Text_TeamAquaLeftNeedDive, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_NeedDive:: @ 820CCF6
	msgbox SlateportCity_Harbor_Text_NeedDiveToCatchSub, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_CaptSternFerryOrScannerComment:: @ 820CD00
	compare VAR_TEMP_1, 1
	goto_if_eq SlateportCity_Harbor_EventScript_TradedScanner
	checkitem ITEM_SCANNER, 1
	compare VAR_RESULT, TRUE
	goto_if_eq SlateportCity_Harbor_EventScript_AskToTradeScanner
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_Harbor_EventScript_FerryFinished
	msgbox SlateportCity_Harbor_Text_WontBeLongBeforeWeFinishFerry, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_FerryFinished:: @ 820CD2E
	msgbox SlateportCity_Harbor_Text_FinishedMakingFerry, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_AskToTradeScanner:: @ 820CD38
	message SlateportCity_Harbor_Text_WouldYouTradeScanner
	waitmessage
	goto SlateportCity_Harbor_EventScript_ChooseScannerTrade
	end

SlateportCity_Harbor_EventScript_ChooseScannerTrade:: @ 820CD44
	multichoice 0, 0, MULTI_STERN_DEEPSEA, 0
	switch VAR_RESULT
	case 0, SlateportCity_Harbor_EventScript_DeepSeaTooth
	case 1, SlateportCity_Harbor_EventScript_DeepSeaScale
	case 2, SlateportCity_Harbor_EventScript_DeclineTrade
	case MULTI_B_PRESSED, SlateportCity_Harbor_EventScript_DeclineTrade
	end

SlateportCity_Harbor_EventScript_DeepSeaTooth:: @ 820CD7B
	msgbox SlateportCity_Harbor_Text_TradeForDeepSeaTooth, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SlateportCity_Harbor_EventScript_ChooseDifferentTrade
	giveitem ITEM_DEEP_SEA_TOOTH
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	removeitem ITEM_SCANNER
	msgbox SlateportCity_Harbor_Text_HandedScannerToStern, MSGBOX_DEFAULT
	setflag FLAG_EXCHANGED_SCANNER
	goto SlateportCity_Harbor_EventScript_TradedScanner
	end

SlateportCity_Harbor_EventScript_DeepSeaScale:: @ 820CDBB
	msgbox SlateportCity_Harbor_Text_TradeForDeepSeaScale, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SlateportCity_Harbor_EventScript_ChooseDifferentTrade
	giveitem ITEM_DEEP_SEA_SCALE
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	removeitem ITEM_SCANNER
	msgbox SlateportCity_Harbor_Text_HandedScannerToStern, MSGBOX_DEFAULT
	setflag FLAG_EXCHANGED_SCANNER
	goto SlateportCity_Harbor_EventScript_TradedScanner
	end

SlateportCity_Harbor_EventScript_DeclineTrade:: @ 820CDFB
	msgbox SlateportCity_Harbor_Text_IfYouWantToTradeLetMeKnow, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_ChooseDifferentTrade:: @ 820CE05
	message SlateportCity_Harbor_Text_WhichOneDoYouWant
	waitmessage
	goto SlateportCity_Harbor_EventScript_ChooseScannerTrade
	end

SlateportCity_Harbor_EventScript_TradedScanner:: @ 820CE11
	setvar VAR_TEMP_1, 1
	msgbox SlateportCity_Harbor_Text_ThisWillHelpResearch, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_Text_FerryServiceUnavailable: @ 820CE20
	.string "에? 배 말입니까?\p"
	.string "죄송합니다만 현재\n"
	.string "연락선은 없습니다...$"

SlateportCity_Harbor_Text_MayISeeYourTicket: @ 820CE87
	.string "연락선을 이용하시려는 거군요!\n"
	.string "티켓은 가지고 계신가요?$"

SlateportCity_Harbor_Text_YouMustHaveTicket: @ 820CEC1
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "티켓이 없다!\p"
	.string "...죄송합니다!\p"
	.string "배에는 티켓을 가진 분들만\n"
	.string "탑승하실 수 있습니다$"

SlateportCity_Harbor_Text_FlashedTicketWhereTo: @ 820CF1C
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "승선티켓을 보여줬다!\p"
	.string "네! 확인했습니다!\p"
	.string "어디로 가시겠어요?$"

SlateportCity_Harbor_Text_SailAnotherTime: @ 820CF71
	.string "또 이용해 주십시오!$"

SlateportCity_Harbor_Text_LilycoveItIs: @ 820CF93
	.string "해안시티 말씀이시군요!$"

SlateportCity_Harbor_Text_BattleFrontierItIs: @ 820CFAE
	.string "배틀프런티어 말씀이시군요!$"

SlateportCity_Harbor_Text_PleaseBoardFerry: @ 820CFCB
	.string "연락선에서 잠시 기다려 주십시오$"

SlateportCity_Harbor_Text_WhereWouldYouLikeToGo: @ 820CFFA
	.string "어디로 가시겠어요?$"

SlateportCity_Harbor_Text_LoveToGoDeepUnderwaterSomeday: @ 820D01C
	.string "바닷속 깊은 곳이라...\n"
	.string "과연 어떤 모습일까?\p"
	.string "나도 언젠가 들어가 보고 싶어!$"

SlateportCity_Harbor_Text_AbnormalWeather: @ 820D08E
	.string "배로 안전하게 항해하려면\n"
	.string "날씨를 이해할 필요가 있지!\p"
	.string "그러고 보니 날씨 연구소에서 일하는\n"
	.string "사람이 말했는데\p"
	.string "최근 각지에서 이상 기후가\n"
	.string "관측되고 있대!\p"
	.string "너도 연구소에 가서\n"
	.string "얘기를 들어보도록 해!$"
	// ふねを あんぜんに すすめる ためにはｎ
	// てんきを りかいする ひつようが ある!ｐ
	// そういえば てんきけんきゅうじょのｎ
	// ひとが いってたけどｐ
	// さいきん かくちで いじょうきしょうがｎ
	// かんそく されている らしいな!ｐ
	// きみも けんきゅうじょに いってｎ
	// はなしを きいてみると いいぞ!

SlateportCity_Harbor_Text_SubTooSmallForMe: @ 820D194
	.string "나도 해양관장과 같이\n"
	.string "해저 조사하러 가고 싶었어!\p"
	.string "그렇지만 잠수정 안은 좁으니까\n"
	.string "내가 타 버리면 관장이\l"
	.string "못 타게 될 거야...$"

SlateportCity_Harbor_Text_SameThugsTriedToRobAtMuseum: @ 820D232
	.string "해양: 저 녀석들은...\p"
	.string "예전에 박물관에서\n"
	.string "데봉화물을 빼앗아 가려고 했던...$"

SlateportCity_Harbor_Text_ArchieYouAgainHideoutInLilycove: @ 820D291
	.string "아강: 으음? 또 네 녀석인가...\p"
	.string "일부러 여기까지 오다니\n"
	.string "꽤나 고생했겠군...\p"
	.string "하지만 더 이상 누구도\n"
	.string "우리를 막을 수 없다\p"
	.string "막을 수 있다고 생각한다면\n"
	.string "해안시티의 아지트까지 와봐라\l"
	.string "후후후...$"
	// アオギリ『おや? また きみか……ｐ
	// わざわざ ここまで おいかけて くるとはｎ
	// ごくろうな ことだな……ｐ
	// だが もう だれにもｎ
	// われわれを とめられないｐ
	// とめられると おもうならｎ
	// ミナモの アジトまで くるかね?ｌ
	// フフフ……

SlateportCity_Harbor_Text_CaptSternWhyStealMySubmarine: @ 820D35A
	.string "해양: 어째서...\p"
	.string "아쿠아단 녀석들이\n"
	.string "내 잠수정\l"
	.string "“해연 1호”를 빼앗은 거지?\p"
	.string "설마 그 녀석들도\n"
	.string "해저에 잠들어 있는 포켓몬을...\p"
	.string "하지만 나는 쫓아가도\n"
	.string "그 녀석들을 상대할 수 없을 텐데...$"
	// クスノキ『なぜ……ｐ
	// アクアだんの れんちゅうがｎ
	// わたしの せんすいていｌ
	// 「かいえん 1ごう」を うばうのだろう?ｐ
	// まさか かれらもｎ
	// かいていに ねむる ポケモンを……ｐ
	// だが わたしが おいかけてもｎ
	// あんな れんちゅうに かてる わけない……

SlateportCity_Harbor_Text_TeamAquaLeftNeedDive: @ 820D42B
	.string "해양: 아아 {PLAYER}{K_AYA}...\p"
	.string "그래... 아쿠아단은\n"
	.string "이미 출발해버렸구나...\p"
	.string "아니야 신경쓰지 않아도 돼\n"
	.string "네 책임이 아니니까\p"
	.string "잠수정을 따라간다는 거 자체가\n"
	.string "보통 인간에게는\l"
	.string "말도 안되는 일이지\p"
	.string "포켓몬에게 다이빙이라고 하는\n"
	.string "바닷속으로 들어갈 수 있는 기술을\l"
	.string "가르치면 또 모를까...\p"
	.string "이끼시티에 가면\n"
	.string "다이빙을 하는 사람이\l"
	.string "많이 있으니까 가르쳐줄 사람이\l"
	.string "있을지도 모르겠다$"

SlateportCity_Harbor_Text_NeedDiveToCatchSub: @ 820D58A
	.string "해양: 잠수정을 따라간다는 거 자체가\n"
	.string "보통 인간에게는\l"
	.string "말도 안되는 일이지\p"
	.string "포켓몬에게 다이빙이라고 하는\n"
	.string "바닷속으로 들어갈 수 있는 기술을\l"
	.string "가르치면 또 모를까...\p"
	.string "이끼시티에 가면\n"
	.string "다이빙을 하는 사람이\l"
	.string "많이 있으니까 가르쳐줄 사람이\n"
	.string "있을지도 모르겠다$"

SlateportCity_Harbor_Text_WontBeLongBeforeWeFinishFerry: @ 820D65C
	.string "해양: 맞다! 하기노인이\n"
	.string "조선소에 와 주었어!\p"
	.string "좋-아! 이걸로 연락선이\n"
	.string "완성되는 것도 얼마 안 남았어!$"

SlateportCity_Harbor_Text_FinishedMakingFerry: @ 820D6CB
	.string "해양: {PLAYER}!\p"
	.string "연락선 타이드립호가\n"
	.string "드디어 완성됐어!\p"
	.string "네 지인인 하기노인이\n"
	.string "도와준 덕분이야\p"
	.string "한번 타 보도록 해$"

SlateportCity_Harbor_Text_WouldYouTradeScanner: @ 820D76C
	.string "해양: 으음?\n"
	.string "{PLAYER}{K_I} 가지고 있는 그거...\p"
	.string "탐지기잖아!\n"
	.string "그게 있으면 조사가\l"
	.string "더욱 진전될 것 같아\p"
	.string "{PLAYER}! 내가 가지고 있는\n"
	.string "심해의이빨과 심해의비늘 중\l"
	.string "하나랑 탐지기를 교환하지 않을래?$"

SlateportCity_Harbor_Text_IfYouWantToTradeLetMeKnow: @ 820D841
	.string "해양: 그래?\n"
	.string "{PLAYER}{K_IGA} 가지고 있어도\l"
	.string "쓸데는 없을 거라고 생각하지만...\p"
	.string "뭐 괜찮아\n"
	.string "탐지기를 교환하고 싶어지면\l"
	.string "다시 또 말 걸어줘!$"

SlateportCity_Harbor_Text_TradeForDeepSeaTooth: @ 820D8BC
	.string "해양: 심해의이빨과 교환할 거지?$"

SlateportCity_Harbor_Text_TradeForDeepSeaScale: @ 820D8F1
	.string "해양: 심해의비늘과 교환할 거지?$"

SlateportCity_Harbor_Text_WhichOneDoYouWant: @ 820D926
	.string "해양: 어느 쪽이랑 교환할래?$"

SlateportCity_Harbor_Text_HandedScannerToStern: @ 820D94A
	.string "{PLAYER}{K_EUNNEUN} 해양관장에게\n"
	.string "탐지기를 전달했다!$"

SlateportCity_Harbor_Text_ThisWillHelpResearch: @ 820D970
	.string "해양: 고마워 {PLAYER}!\n"
	.string "이걸로 연구가 더 진전되겠어$"
