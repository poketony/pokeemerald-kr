.set LOCALID_STEVEN, 1

GraniteCave_StevensRoom_MapScripts:: @ 822DC7A
	.byte 0

GraniteCave_StevensRoom_EventScript_Steven:: @ 822DC7B
	lock
	faceplayer
	msgbox GraniteCave_StevensRoom_Text_ImStevenLetterForMe, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_LETTER
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_DELIVERED_STEVEN_LETTER
	msgbox GraniteCave_StevensRoom_Text_ThankYouTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM47
	compare VAR_RESULT, FALSE
	call_if_eq GraniteCave_StevensRoom_EventScript_BagFull
	msgbox GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox GraniteCave_StevensRoom_Text_RegisteredSteven, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_REGISTERED_STEVEN_POKENAV
	msgbox GraniteCave_StevensRoom_Text_IveGotToHurryAlong, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_NORTH
	call_if_eq GraniteCave_StevensRoom_EventScript_StevenExitNorth
	compare VAR_FACING, DIR_SOUTH
	call_if_eq GraniteCave_StevensRoom_EventScript_StevenExitSouth
	compare VAR_FACING, DIR_WEST
	call_if_eq GraniteCave_StevensRoom_EventScript_StevenExitWestEast
	compare VAR_FACING, DIR_EAST
	call_if_eq GraniteCave_StevensRoom_EventScript_StevenExitWestEast
	playse SE_EXIT
	removeobject LOCALID_STEVEN
	release
	end

GraniteCave_StevensRoom_EventScript_StevenExitNorth:: @ 822DD0D
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_StevenExitWestEast:: @ 822DD18
	applymovement OBJ_EVENT_ID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_StevenExitSouth:: @ 822DD2A
	applymovement OBJ_EVENT_ID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_StevenExitSouth
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_BagFull:: @ 822DD3C
	msgbox GraniteCave_StevensRoom_Text_OhBagIsFull, MSGBOX_DEFAULT
	return

GraniteCave_StevensRoom_Movement_StevenExit: @ 822DD45
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	step_end

GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit: @ 822DD4C
	delay_16
	delay_16
	delay_16
	walk_in_place_fastest_up
	step_end

GraniteCave_StevensRoom_Movement_StevenExitSouth: @ 822DD51
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	delay_8
	step_end

GraniteCave_StevensRoom_Text_ImStevenLetterForMe: @ 822DD5A
	.string "내 이름은 성호\p"
	.string "희귀한 돌에 흥미가 있어서\n"
	.string "이곳저곳을 여행하고 있어\p"
	.string "어?\n"
	.string "나한테 편지...?$"
	// ボクの なまえは ダイゴｐ
	// めずらしい いしに きょうみが あってｎ
	// あちこち たび してるんだよｐ
	// えっ?ｎ
	// ボクに てがみ……?

GraniteCave_StevensRoom_Text_ThankYouTakeThis: @ 822DDBD
	.string "성호: 응 고마워\p"
	.string "일부러 전해주러 온 거구나\n"
	.string "뭔가 사례를 해 줘야겠는데\p"
	.string "그래\n"
	.string "이 기술머신을 너한테 줄게\p"
	.string "강철날개라고 해서\n"
	.string "내가 좋아하는 기술이야$"
	// ダイゴ『うん ありがとうｐ
	// わざわざ とどけて くれたんだｎ
	// なにか おれいを させてもらうよｐ
	// そうだねｎ
	// この わざマシンを あげようｐ
	// はがねのつばさ といってｎ
	// ボクの おきにいりの わざ だから

GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister: @ 822DE6B
	.string "성호: 네 포켓몬들\n"
	.string "꽤 좋은 느낌이네\p"
	.string "수행을 계속해 나가면\n"
	.string "언젠가 포켓몬리그의\l"
	.string "챔피언도 될 수 있을 거 같은\l"
	.string "그런 생각이 드네 난\p"
	.string "그래!\n"
	.string "모처럼 너하고 만났으니까\l"
	.string "서로 포켓내비에\l"
	.string "이름을 등록해놓자!\p"
	.string "...... ...... ......$"
	// ダイゴ『きみの ポケモンｎ
	// なかなか いい かんじ だねｐ
	// しゅぎょうを つづければｎ
	// いつかは ポケモンリ-グのｌ
	// チャンピオンに だって なれるｌ
	// ボクは そう おもうなｐ
	// そうだ!ｎ
	// せっかく きみと しりあえたんだｌ
	// おたがい ポケナビにｌ
	// なまえを とうろく しておこう!ｐ
	// …… …… ……

GraniteCave_StevensRoom_Text_RegisteredSteven: @ 822DF6A
	.string "성호를\n"
	.string "포켓내비에 등록했다!$"
	// ダイゴをｎ
	// ポケナビに とうろく した!

GraniteCave_StevensRoom_Text_IveGotToHurryAlong: @ 822DF8C
	.string "...그럼\n"
	.string "난 급히 가봐야 돼서$"
	// ……じゃあｎ
	// ボクは さきを いそぐから

GraniteCave_StevensRoom_Text_OhBagIsFull: @ 822DFAA
	.string "가방이 가득 찼구나...\n"
	.string "그럼 어쩔 수 없지$"
	// バッグが いっぱい なのか……ｎ
	// じゃあ しかたないね

