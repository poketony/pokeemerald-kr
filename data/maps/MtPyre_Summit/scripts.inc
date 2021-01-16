.set LOCALID_ARCHIE, 2
.set LOCALID_OLD_LADY, 3
.set LOCALID_GRUNT_1, 4
.set LOCALID_GRUNT_2, 5
.set LOCALID_GRUNT_3, 6
.set LOCALID_GRUNT_4, 7
.set LOCALID_MAXIE, 8

MtPyre_Summit_MapScripts:: @ 8231FF7
	map_script MAP_SCRIPT_ON_TRANSITION, MtPyre_Summit_OnTransition
	.byte 0

MtPyre_Summit_OnTransition: @ 8231FFD
	compare VAR_MT_PYRE_STATE, 2
	call_if_eq MtPyre_Summit_EventScript_SetArchieMaxiePositions
	end

MtPyre_Summit_EventScript_SetArchieMaxiePositions:: @ 8232009
	setobjectxyperm LOCALID_MAXIE, 23, 6
	setobjectxyperm LOCALID_ARCHIE, 22, 6
	end

MtPyre_Summit_EventScript_TeamAquaTrigger0:: @ 8232018
	lockall
	setvar VAR_0x8008, 0
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaTrigger1:: @ 8232024
	lockall
	setvar VAR_0x8008, 1
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaTrigger2:: @ 8232030
	lockall
	setvar VAR_0x8008, 2
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaExits:: @ 823203C
	playbgm MUS_ENCOUNTER_AQUA, 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 50
	compare VAR_0x8008, 0
	call_if_eq MtPyre_Summit_EventScript_ArchieFacePlayer0
	compare VAR_0x8008, 1
	call_if_eq MtPyre_Summit_EventScript_ArchieFacePlayer1
	compare VAR_0x8008, 2
	call_if_eq MtPyre_Summit_EventScript_ArchieFacePlayer2
	msgbox MtPyre_Summit_Text_ArchieWeGotTheOrbLetsGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_GRUNT_4
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_ARCHIE
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_TEAM_AQUA
	fadedefaultbgm
	fadescreen FADE_FROM_BLACK
	delay 20
	setvar VAR_MT_PYRE_STATE, 1
	compare VAR_0x8008, 0
	call_if_eq MtPyre_Summit_EventScript_OldLadyApproachPlayer0
	compare VAR_0x8008, 1
	call_if_eq MtPyre_Summit_EventScript_OldLadyApproachPlayer1
	compare VAR_0x8008, 2
	call_if_eq MtPyre_Summit_EventScript_OldLadyApproachPlayer2
	msgbox MtPyre_Summit_Text_BothOrbsTakenMagmaLeftThis, MSGBOX_DEFAULT
	giveitem ITEM_MAGMA_EMBLEM
	setflag FLAG_RECEIVED_RED_OR_BLUE_ORB
	setflag FLAG_HIDE_JAGGED_PASS_MAGMA_GUARD
	releaseall
	end

MtPyre_Summit_EventScript_ArchieFacePlayer0:: @ 82320E0
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieFacePlayer0
	waitmovement 0
	return

@ Archie is already facing player
MtPyre_Summit_EventScript_ArchieFacePlayer1:: @ 82320EB
	return

MtPyre_Summit_EventScript_ArchieFacePlayer2:: @ 82320EC
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieFacePlayer2
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer0:: @ 82320F7
	applymovement LOCALID_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer0
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer1:: @ 823210C
	applymovement LOCALID_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer1
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer2:: @ 8232117
	applymovement LOCALID_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

MtPyre_Summit_Movement_OldLadyApproachPlayer0: @ 823212C
	walk_down
	walk_down
	walk_in_place_fastest_left
	step_end

MtPyre_Summit_Movement_OldLadyApproachPlayer1: @ 8232130
	walk_down
	step_end

MtPyre_Summit_Movement_OldLadyApproachPlayer2: @ 8232132
	walk_down
	walk_down
	walk_in_place_fastest_right
	step_end

MtPyre_Summit_Movement_ArchieFacePlayer0: @ 8232136
	walk_left
	walk_in_place_fastest_down
	step_end

MtPyre_Summit_Movement_ArchieFacePlayer2: @ 8232139
	walk_right
	walk_in_place_fastest_down
	step_end

MtPyre_Summit_EventScript_OldMan:: @ 823213C
	lock
	faceplayer
	goto_if_set FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE, MtPyre_Summit_EventScript_OldManAfterRayquaza
	msgbox MtPyre_Summit_Text_WillYouHearOutMyTale, MSGBOX_YESNO
	compare VAR_RESULT, YES
	call_if_eq MtPyre_Summit_EventScript_OldManTale
	compare VAR_RESULT, NO
	call_if_eq MtPyre_Summit_EventScript_DeclineOldManTale
	release
	end

MtPyre_Summit_EventScript_OldManAfterRayquaza:: @ 8232167
	msgbox MtPyre_Summit_Text_HearTheNewLegendOfHoenn, MSGBOX_YESNO
	compare VAR_RESULT, YES
	call_if_eq MtPyre_Summit_EventScript_OldManNewTale
	compare VAR_RESULT, NO
	call_if_eq MtPyre_Summit_EventScript_DeclineOldManTale
	release
	end

MtPyre_Summit_EventScript_OldManTale:: @ 8232187
	msgbox MtPyre_Summit_Text_GroudonKyogreTale, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_DeclineOldManTale:: @ 8232190
	msgbox MtPyre_Summit_Text_WellThatTooIsFine, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_OldManNewTale:: @ 8232199
	msgbox MtPyre_Summit_Text_HoennTrioTale, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_OldLady:: @ 82321A2
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_RED_OR_BLUE_ORB, MtPyre_Summit_EventScript_OldLadyAfterOrbsReturned
	compare VAR_MT_PYRE_STATE, 3
	call_if_ge MtPyre_Summit_EventScript_OldLadyOrbsReturned
	goto_if_set FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, MtPyre_Summit_EventScript_OldLadyLegendariesAwake
	msgbox MtPyre_Summit_Text_OrbsHaveBeenTaken, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_OldLadyOrbsReturned:: @ 82321CB
	msgbox MtPyre_Summit_Text_ThoseTwoMenReturnedOrbs, MSGBOX_DEFAULT
	setflag FLAG_RETURNED_RED_OR_BLUE_ORB
	release
	end

MtPyre_Summit_EventScript_OldLadyLegendariesAwake:: @ 82321D8
	msgbox MtPyre_Summit_Text_GroudonKyogreAwakened, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_OldLadyAfterOrbsReturned:: @ 82321E2
	msgbox MtPyre_Summit_Text_SuperAncientPokemonTaughtUs, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger0:: @ 82321EC
	lockall
	setvar VAR_0x8008, 0
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger1:: @ 82321F8
	lockall
	setvar VAR_0x8008, 1
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger2:: @ 8232204
	lockall
	setvar VAR_0x8008, 2
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs:: @ 8232210
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 60
	compare VAR_0x8008, 0
	call_if_eq MtPyre_Summit_EventScript_ArchieMaxieBeginExit0
	compare VAR_0x8008, 1
	call_if_eq MtPyre_Summit_EventScript_ArchieMaxieBeginExit1
	compare VAR_0x8008, 2
	call_if_eq MtPyre_Summit_EventScript_ArchieMaxieBeginExit2
	playse SE_PIN
	applymovement LOCALID_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAXIE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	compare VAR_0x8008, 0
	call_if_eq MtPyre_Summit_EventScript_MaxieApproachPlayer0
	compare VAR_0x8008, 1
	call_if_eq MtPyre_Summit_EventScript_MaxieApproachPlayer1
	compare VAR_0x8008, 2
	call_if_eq MtPyre_Summit_EventScript_MaxieApproachPlayer2
	msgbox MtPyre_Summit_Text_MaxieSilence, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 0
	call_if_eq MtPyre_Summit_EventScript_MaxieApproachArchie0
	compare VAR_0x8008, 1
	call_if_eq MtPyre_Summit_EventScript_MaxieApproachArchie1
	compare VAR_0x8008, 2
	call_if_eq MtPyre_Summit_EventScript_MaxieApproachArchie2
	delay 30
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_MAXIE
	setvar VAR_MT_PYRE_STATE, 3
	releaseall
	end

MtPyre_Summit_EventScript_ArchieMaxieBeginExit0:: @ 82322C4
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit0
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_ArchieMaxieBeginExit1:: @ 82322DD
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit1
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_ArchieMaxieBeginExit2:: @ 82322F6
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit2
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer0:: @ 823230F
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie0
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer0
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer1:: @ 8232328
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer1
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer2:: @ 8232341
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer2
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie0:: @ 823235A
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie0
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie1:: @ 8232376
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie1
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie2:: @ 8232392
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie2
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

MtPyre_Summit_Movement_PlayerFaceMaxie0: @ 82323AE
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

MtPyre_Summit_Movement_PlayerFaceMaxie: @ 82323B2
	delay_16
	delay_16
	walk_in_place_fastest_left
	step_end

MtPyre_Summit_Movement_ArchieExit: @ 82323B6
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_MaxieExit: @ 82323BD
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit0: @ 82323C4
	delay_16
	delay_8
	walk_left
	walk_in_place_fastest_right
	delay_16
	walk_in_place_fastest_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit1: @ 82323CB
	delay_16
	delay_8
	walk_right
	walk_in_place_fastest_left
	delay_16
	walk_in_place_fastest_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit2: @ 82323D2
	delay_16
	delay_8
	walk_in_place_fastest_left
	delay_16
	walk_in_place_fastest_down
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer0: @ 82323D8
	walk_up
	walk_up
	walk_up
	walk_left
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer1: @ 82323DD
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_right
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer2: @ 82323E2
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_right
	step_end

MtPyre_Summit_Movement_ArchieWatchMaxie: @ 82323E7
	delay_16
	walk_in_place_fastest_up
	step_end

MtPyre_Summit_Movement_PlayerWatchMaxie: @ 82323EA
	delay_16
	walk_in_place_fastest_down
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie0: @ 82323ED
	walk_down
	walk_right
	walk_down
	walk_down
	walk_in_place_fastest_left
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie1: @ 82323F3
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_left
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie2: @ 82323F8
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_left
	step_end

MtPyre_Summit_EventScript_Grunt1:: @ 82323FD
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_1, MtPyre_Summit_Text_Grunt1Intro, MtPyre_Summit_Text_Grunt1Defeat
	msgbox MtPyre_Summit_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt2:: @ 8232414
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_2, MtPyre_Summit_Text_Grunt2Intro, MtPyre_Summit_Text_Grunt2Defeat
	msgbox MtPyre_Summit_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt3:: @ 823242B
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_3, MtPyre_Summit_Text_Grunt3Intro, MtPyre_Summit_Text_Grunt3Defeat
	msgbox MtPyre_Summit_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt4:: @ 8232442
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_4, MtPyre_Summit_Text_Grunt4Intro, MtPyre_Summit_Text_Grunt4Defeat
	msgbox MtPyre_Summit_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_Text_Grunt1Intro: @ 8232459
	.string "젠장-! 마그마단 녀석들\n"
	.string "먼저 가버린 건가\p"
	.string "우리들도 질 순 없지!$"
	// くっそ-! マグマだんの れんちゅうにｎ
	// さきを こされて しまったがｐ
	// オレたちだって まけちゃ いないぜ!

MtPyre_Summit_Text_Grunt1Defeat: @ 82324A0
	.string "너... 도망치고 있던\n"
	.string "마그마단이라고 생각했는데$"
	// おまえ…… にげていった マグマだんがｎ
	// もどって きたのかと おもったんだよ

MtPyre_Summit_Text_Grunt1PostBattle: @ 82324E0
	.string "넌 확실히 강하군...\n"
	.string "하지만 우리들은 아주 많다!$"
	// たしかに おまえは つよいな……ｎ
	// だけど おれたちは たくさん いるんだぞ!

MtPyre_Summit_Text_Grunt2Intro: @ 8232513
	.string "앗 아쉽게 됐네!\p"
	.string "조금만 더 빨리 여기에\n"
	.string "왔다면 약해빠진 마그마단하고\l"
	.string "승부를 했을 텐데\p"
	.string "지금 와버린 탓에\n"
	.string "강한 우리들이 상대니까!$"
	// おっ ざんねん だったな!ｐ
	// もうすこし はやく ここにくればｎ
	// あの よわっちょろい マグマだんとのｌ
	// しょうぶで すんだ はずなのにｐ
	// いまごろ きた おかげでｎ
	// つよい オレたちが あいてだぜ!

MtPyre_Summit_Text_Grunt2Defeat: @ 82325B0
	.string "으-음 마그마단이\n"
	.string "상대가 되는 게 나았을지도...$"
	// う-む…… マグマだんにｎ
	// あいてを させれば よかった……

MtPyre_Summit_Text_Grunt2PostBattle: @ 82325E4
	.string "아무것도 모르는 주제에\n"
	.string "우리를 방해하지 마라!$"
	// なにも しらないくせにｎ
	// オレたちの じゃまを するんじゃないぜ!

MtPyre_Summit_Text_Grunt3Intro: @ 823261D
	.string "너... 굴뚝산에서 만났던!\p"
	.string "어느 쪽 단원도 아닌데\n"
	.string "왜 여기에 있는 거야?$"
	// おまえ…… えんとつやまで あったな!ｐ
	// どっちの だんいん でもないのにｎ
	// なぜ こんな ところに いるんだ!?

MtPyre_Summit_Text_Grunt3Defeat: @ 8232678
	.string "으으으...\n"
	.string "방해할 거면 마그마단한테 하라고...$"
	// ぐぐぐ……ｎ
	// じゃまを するなら マグマだんに しろ……

MtPyre_Summit_Text_Grunt3PostBattle: @ 82326B3
	.string "뭐 됐어 시간은 벌었다!\n"
	.string "지금쯤 리더가 원하는 걸\n"
	.string "빼앗았을 거다!$"
	// まあいいさ じかんは かせげた!ｐ
	// リ-ダ-の もくてきの ものｎ
	// うばえた はずだぜ!

MtPyre_Summit_Text_Grunt4Intro: @ 823271B
	.string "앗 알겠다!\n"
	.string "너 마그마단에 들어가려고 했는데\l"
	.string "거절당한 거지!\p"
	.string "하! 우리 아쿠아단도\n"
	.string "받아주지 않을 거거든!$"
	// あっ わかった!ｎ
	// あんた マグマだんに はいろうと したけどｌ
	// いれて もらえなかったんでしょ!ｐ
	// はん! うちら アクアだんに だってｎ
	// いれてやんないよ!

MtPyre_Summit_Text_Grunt4Defeat: @ 823279A
	.string "그렇게 원한다면 아쿠아단에\n"
	.string "넣어줄 수도 있어...$"
	// そうしたら アクアだんに いれてｎ
	// やらない ことも ないよ……

MtPyre_Summit_Text_Grunt4PostBattle: @ 82327D8
	.string "리더와 우리 단원 사이에는\n"
	.string "훌륭한 콤비네이션이 있다고!$"
	// リ-ダ-と あたしたち だんいんとのｎ
	// みごとな コンビネ-ション ってわけさ!

MtPyre_Summit_Text_ArchieWeGotTheOrbLetsGo: @ 823281A
	.string "아강: 마그마단의 마적이\n"
	.string "먼저 앞질러 가버린 건가\l"
	.string "우리도 볼일은 다 봤지!\p"
	.string "송화산에 모셔져 있던\n"
	.string "주홍구슬...\l"
	.string "이 아강이 받아가도록 하겠다!\p"
	.string "후후후...\n"
	.string "이걸로 우리들의 목적도\l"
	.string "이루어질 터...\p"
	.string "자!\n"
	.string "여기서 철수한다!$"
	// アオギリ『マグマだんの マツブサにｎ
	// さきを こされて しまったがｌ
	// われわれも ようじは すませたぜ!ｐ
	// おくりびやまに まつられて いたｎ
	// べにいろのたま……ｌ
	// たしかに アオギリが いただいた!ｐ
	// ふふふ……ｎ
	// これで われわれの もくてきもｌ
	// はたせると いうものだ……ｐ
	// さあ!ｎ
	// ここは ひきあげるぞ!

MtPyre_Summit_Text_BothOrbsTakenMagmaLeftThis: @ 823290E
	.string "아아 이거 어쩌면 좋을꼬...!\p"
	.string "쪽빛구슬뿐만이 아니라\n"
	.string "주홍구슬까지\l"
	.string "빼앗겨 버리다니...\p"
	.string "쪽빛구슬과 주홍구슬이\n"
	.string "서로 떨어져 버리다니\l"
	.string "결코 있어서는 안 될 일이거늘...\p"
	.string "그 남자들은 두 구슬로\n"
	.string "대체 뭘 하려는 건가...\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "그러고 보니 처음에 나타난\n"
	.string "쪽빛구슬을 가져간\l"
	.string "마그마단 녀석이\l"
	.string "이런 걸 두고 갔었단다...\p"
	.string "이게 뭔지는 나도 모르겠다만\p"
	.string "너 괜찮다면 이걸\n"
	.string "받도록 하거라...\p"
	.string "혹시나 도움이 될 수도\n"
	.string "있으니까 말이지...!$"
	// ああ なんという ことだ……!ｐ
	// あいいろのたま だけではなくｎ
	// べにいろのたま までもがｌ
	// うばわれて しまうとは……ｐ
	// あいいろのたまと べにいろのたまがｎ
	// はなればなれに なって しまうなどｌ
	// けっして あっては ならないこと……ｐ
	// あの おとこたちは ふたつのたまでｎ
	// いったい なにを するきなのか……ｐ
	// …… …… ……ｎ
	// …… …… ……ｐ
	// そういえば さいしょに あらわれてｎ
	// あいいろのたまを うばって いったｌ
	// マグマだん とやらがｌ
	// こんなものを おとしていった……ｐ
	// これが なんなのか わたしには わからんｐ
	// おまえさん よかったら こいつをｎ
	// もらって おくれ……ｐ
	// もしかすると なにかの やくにｎ
	// たつのでは ないだろうか……!

MtPyre_Summit_Text_OrbsHaveBeenTaken: @ 8232AD8
	.string "수상한 두 남자가 가져간\n"
	.string "쪽빛구슬과 주홍구슬...\p"
	.string "따로 떨어져 있으면\n"
	.string "분명 좋지 않은 일이 일어날 거야...$"
	// あやしげな ふたりの おとこに うばわれたｎ
	// あいいろのたまと べにいろのたま……ｐ
	// ふたつが はなればなれ ではｎ
	// きっと よくないことが おこる……

MtPyre_Summit_Text_GroudonKyogreAwakened: @ 8232B4F
	.string "뭐라고...\n"
	.string "그란돈과 가이오가가\l"
	.string "눈을 떠버렸다는 건가...\p"
	.string "일찍이 두 마리의 포켓몬의\n"
	.string "분노를 잠재우는 것이\l"
	.string "쪽빛구슬과 주홍구슬이라고\l"
	.string "전해져 왔었지...\p"
	.string "그리고 그 구슬의 진정한 주인이\n"
	.string "어딘가에 있다는 것도...\p"
	.string "그것이 사람인지\n"
	.string "아니면 포켓몬인지\p"
	.string "이것만은\n"
	.string "그 누구도 알지 못한다네...$"
	// なんと……ｎ
	// グラ-ドンと カイオ-ガがｌ
	// めざめて しまったと いうのか……ｐ
	// かつて 2ひきの ポケモンのｎ
	// いかりを しずめたのがｌ
	// あいいろのたまと べにいろのたまだとｌ
	// そう いわれておる……ｐ
	// そして そのたまの しんの もちぬしがｎ
	// どこかに いると いうのだが……ｐ
	// それが ひと なのかｎ
	// あるいは ポケモン なのかｐ
	// こればっかりはｎ
	// だれにも わからんのだよ……

MtPyre_Summit_Text_ThoseTwoMenReturnedOrbs: @ 8232CA6
	.string "두 구슬을 가져간 남자들이\n"
	.string "스스로 돌려주러 오다니...\p"
	.string "그 둘... 생각보다\n"
	.string "나쁜 녀석들은 아닌가 보구먼$"
	// ふたつのたまを うばった おとこたちがｎ
	// みずから かえしに くるとは……ｐ
	// あの ふたり……ｎ
	// あんがい わるいやつでは ないのかもな

MtPyre_Summit_Text_SuperAncientPokemonTaughtUs: @ 8232D1E
	.string "대지와 바다와 창공의 화신...\p"
	.string "그것이 초 고대포켓몬의\n"
	.string "정체라고 전해지고 있단다...\p"
	.string "우리들 인간이나 포켓몬에게\n"
	.string "생명이 있는 것처럼\l"
	.string "이 대지 역시 살아있단다...\p"
	.string "초 고대포켓몬은 우리들에게 그것을\n"
	.string "알려주려 했던 거겠지...$"
	// だいちと うみと おおぞらの けしん……ｐ
	// それが ちょうこだいポケモンのｎ
	// しょうたい とも いわれておる……ｐ
	// わしら にんげんや ポケモンにｎ
	// いのちが あるようにｌ
	// この せかいだって いきている……ｐ
	// ちょうこだいポケモンは わしたちにｎ
	// そのことを おしえて くれたのさ……

MtPyre_Summit_Text_WillYouHearOutMyTale: @ 8232E0C
	.string "송화산은 포켓몬의 영혼을\n"
	.string "위로하기 위한 곳...\p"
	.string "여기는 높은 곳에 있기 때문에\n"
	.string "호연지방을 한눈에 볼 수 있어서\l"
	.string "포켓몬들의 영혼도\l"
	.string "평온함을 느낄 수 있는 거겠지...\p"
	.string "자네가 여기로 온 것도\n"
	.string "하나의 인연...\p"
	.string "호연지방에서 전해지고 있는\n"
	.string "이야기를 듣고 가게나...$"
	// おくりびやまは ポケモンの たましいをｎ
	// なぐさめる ための ところ……ｐ
	// ここは たかい ばしょに あってｎ
	// ホウエンを みわたす ことが できるからｌ
	// ポケモンたちの たましいもｌ
	// やすらぎを おぼえるの じゃろう……ｐ
	// おまえさんが ここに きたのもｎ
	// なにかの えん……ｐ
	// ホウエンちほうに つたわる はなしをｎ
	// きいて いきなされ……

MtPyre_Summit_Text_GroudonKyogreTale: @ 8232F27
	.string "멀고도 먼 옛날...\p"
	.string "세계는 육지와 바다의 포켓몬이\n"
	.string "격렬한 싸움을 벌이고 있었지\p"
	.string "육지의 포켓몬은\n"
	.string "대지를 일으켜 세워 땅을 넓히고\p"
	.string "바다의 포켓몬은\n"
	.string "거센 파도를 일으켜 바다를 넓혔지\p"
	.string "두 마리의 싸움은 끝나지 않고\p"
	.string "이 세계는 활활 타오르는 불꽃과\n"
	.string "휘몰아치는 폭풍으로 휩싸였지\p"
	.string "그것을 잠재운 것이\n"
	.string "주홍구슬과 쪽빛구슬...\p"
	.string "두 구슬에서 퍼진 빛이\n"
	.string "두 마리의 분노를 잠재웠다\p"
	.string "그리고 얌전해진 두 마리는\n"
	.string "해저 깊은 곳으로 들어가\l"
	.string "머지않아 그 모습을 감추었다는군....$"
	// とおい とおい おおむかしの こと……ｐ
	// せかいでは りくと うみの ポケモンがｎ
	// はげしい たたかいを くりひろげていたｐ
	// りくの ポケモンはｎ
	// だいちを もりあげ じめんを ひろげｐ
	// うみの ポケモンはｎ
	// あらなみを おこして うみを ひろげたｐ
	// 2ひきの たたかいは おわることなくｎ
	// この せかいは もえさかる ほのおとｌ
	// ふきあれる あらしで うめつくされたｐ
	// それを しずめたのがｎ
	// あいいろのたま と べにいろのたま……ｐ
	// ふたつの たまから ひろがる ひかりがｎ
	// 2ひきの いかりを しずめたｐ
	// そして おとなしくなった 2ひきはｎ
	// かいてい ふかく もぐっていきｌ
	// やがて そのすがたを けしたのじゃ……

MtPyre_Summit_Text_WellThatTooIsFine: @ 8233162
	.string "그러냐...\n"
	.string "뭐 그것도 좋겠지...$"
	// そうかね……ｎ
	// まあ それも よいじゃろう……

MtPyre_Summit_Text_MaxieSilence: @ 8233183
	.string "마적: {PLAYER}...\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......$"
	// マツブサ『§あ……ｐ
	// …… …… ……ｎ
	// …… …… ……

MtPyre_Summit_Text_HearTheNewLegendOfHoenn: @ 82331A6
	.string "호연지방에 남겨진 전설을\n"
	.string "전하는 것이 내 사명\p"
	.string "그리고 지금\n"
	.string "루네시티에서 일어난 사건은\l"
	.string "막을 내리고\l"
	.string "전설은 새롭게 다시 써졌다...\p"
	.string "새로운 호연지방의 전설을\n"
	.string "듣고 가게나...$"
	// ホウエンに のこされた いいつたえをｎ
	// かたりつぐのが わたしの やくめｐ
	// そして いまｎ
	// ルネで おこった じけんは まくを とじｌ
	// いいつたえは また ぬりかえられた……ｐ
	// あらたな ホウエンの いいつたえをｎ
	// きいて いきなされ……

MtPyre_Summit_Text_HoennTrioTale: @ 823325D
	.string "멀고도 먼 옛날...\p"
	.string "세계는 육지와 바다의 포켓몬이\n"
	.string "격렬한 싸움을 벌이고 있었지\p"
	.string "육지의 포켓몬은\n"
	.string "대지를 일으켜 세워 땅을 넓히고\p"
	.string "바다의 포켓몬은\n"
	.string "거센 파도를 일으켜 바다를 넓혔지\p"
	.string "두 마리의 싸움은 끝나지 않고\p"
	.string "이 세계는 활활 타오르는 불꽃과\n"
	.string "휘몰아치는 폭풍으로 휩싸였지\p"
	.string "그때!\n"
	.string "폭풍 속에서 내려온 것이\l"
	.string "창공의 포켓몬...\p"
	.string "그 초록색으로 빛나는 포켓몬은\n"
	.string "두 마리의 분노를 잠재우고\l"
	.string "또다시 어딘가로 날아가버렸다\p"
	.string "어딘가 멀리 있는\l"
	.string "하늘 저편으로...$"
	// とおい とおい おおむかしの こと……ｐ
	// せかいでは りくと うみの ポケモンがｎ
	// はげしい たたかいを くりひろげていたｐ
	// りくの ポケモンはｎ
	// だいちを もりあげ じめんを ひろげｐ
	// うみの ポケモンはｎ
	// あらなみを おこして うみを ひろげたｐ
	// 2ひきの たたかいは おわることなくｎ
	// この せかいは もえさかる ほのおとｌ
	// ふきあれる あらしで うめつくされたｐ
	// そのとき!ｎ
	// あらしの なかから まいおりて きたのがｌ
	// おおぞらの ポケモン……ｐ
	// その みどりに かがやく ポケモンはｎ
	// 2ひきの いかりを しずめるとｌ
	// また どこかへと とびさって いったｐ
	// どこか とおいｎ
	// そらの かなたへ……

