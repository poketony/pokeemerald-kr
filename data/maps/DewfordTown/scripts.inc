@ Sailing to and from Dewford uses local IDs from different maps
@ e.g. Route 104's sail to Dewford script references local IDs from Dewford's map
@ All of these local IDs are labeled here
.equ LOCALID_BRINEY_DEWFORD, 2
.equ LOCALID_BOAT_DEWFORD, 4

.equ LOCALID_BOAT_R109, 1 
.equ LOCALID_BRINEY_R109, 2

.equ LOCALID_BOAT_R104, 7
.equ LOCALID_BRINEY_R104, 8

DewfordTown_MapScripts:: @ 81E9507
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_OnTransition
	.byte 0

DewfordTown_OnTransition: @ 81E950D
	setflag FLAG_VISITED_DEWFORD_TOWN
	end

DewfordTown_EventScript_Briney:: @ 81E9511
	lock
	faceplayer
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, DewfordTown_EventScript_ReturnToPetalburgPrompt
	message DewfordTown_Text_WhereAreWeBound
	waitmessage
	multichoicedefault 21, 6, MULTI_BRINEY_ON_DEWFORD, 2, 0
	switch VAR_RESULT
	case 0, DewfordTown_EventScript_ChoosePetalburg
	case 1, DewfordTown_EventScript_ChooseSlateport
	case 2, DewfordTown_EventScript_CancelSailSelect
	case MULTI_B_PRESSED, DewfordTown_EventScript_CancelSailSelect
	end

DewfordTown_EventScript_ChoosePetalburg:: @ 81E955A
	msgbox DewfordTown_Text_PetalburgWereSettingSail, MSGBOX_DEFAULT
	closemessage
	goto DewfordTown_EventScript_SailToPetalburg
	release
	end

DewfordTown_EventScript_ChooseSlateport:: @ 81E956A
	msgbox DewfordTown_Text_SlateportWereSettingSail, MSGBOX_DEFAULT
	closemessage
	goto DewfordTown_EventScript_SailToSlateport
	release
	end

DewfordTown_EventScript_CancelSailSelect:: @ 81E957A
	msgbox DewfordTown_Text_JustTellMeWhenYouNeedToSetSail, MSGBOX_DEFAULT
	closemessage
	release
	end

DewfordTown_EventScript_ReturnToPetalburgPrompt:: @ 81E9585
	msgbox DewfordTown_Text_SetSailBackToPetalburg, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq DewfordTown_EventScript_SailBackToPetalburg
	msgbox DewfordTown_Text_GoDeliverIllBeWaiting, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_SailBackToPetalburg:: @ 81E95A2
	msgbox DewfordTown_Text_PetalburgWereSettingSail2, MSGBOX_DEFAULT
	closemessage
	goto DewfordTown_EventScript_SailToPetalburg
	end

DewfordTown_EventScript_Woman:: @ 81E95B1
	msgbox DewfordTown_Text_TinyIslandCommunity, MSGBOX_NPC
	end

DewfordTown_EventScript_TownSign:: @ 81E95BA
	msgbox DewfordTown_Text_TownSign, MSGBOX_SIGN
	end

DewfordTown_EventScript_GymSign:: @ 81E95C3
	msgbox DewfordTown_Text_GymSign, MSGBOX_SIGN
	end

DewfordTown_EventScript_HallSign:: @ 81E95CC
	msgbox DewfordTown_Text_HallSign, MSGBOX_SIGN
	end

DewfordTown_EventScript_OldRodFisherman:: @ 81E95D5
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_OLD_ROD, DewfordTown_EventScript_HowsFishing
	msgbox DewfordTown_Text_GettingItchToFish, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq DewfordTown_EventScript_GiveOldRod
	compare VAR_RESULT, NO
	goto_if_eq DewfordTown_EventScript_NotGettingItchToFish
	end

DewfordTown_EventScript_GiveOldRod:: @ 81E95FF
	msgbox DewfordTown_Text_GiveYouOneOfMyRods, MSGBOX_DEFAULT
	giveitem ITEM_OLD_ROD
	setflag FLAG_RECEIVED_OLD_ROD
	msgbox DewfordTown_Text_ThrowInFishingAdvice, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_NotGettingItchToFish:: @ 81E9620
	msgbox DewfordTown_Text_ThatsTooBadThen, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_HowsFishing:: @ 81E962A
	message DewfordTown_Text_HowsYourFishing
	waitmessage
	multichoice 20, 8, MULTI_HOWS_FISHING, 1
	compare VAR_RESULT, 0
	goto_if_eq DewfordTown_EventScript_FishingExcellent
	compare VAR_RESULT, 1
	goto_if_eq DewfordTown_EventScript_FishingNotSoGood
	end

DewfordTown_EventScript_FishingExcellent:: @ 81E964C
	msgbox DewfordTown_Text_GreatHaulInSomeBigOnes, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_FishingNotSoGood:: @ 81E9656
	msgbox DewfordTown_Text_FishingAdvice, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_SailToPetalburg:: @ 81E9660
	call EventScript_BackupMrBrineyLocation
	setobjectpriority LOCALID_BRINEY_DEWFORD, MAP_DEWFORD_TOWN, 0
	setobjectpriority OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN, 0
	applymovement LOCALID_BRINEY_DEWFORD, DewfordTown_Movement_BrineyBoardBoat
	waitmovement 0
	removeobject LOCALID_BRINEY_DEWFORD
	applymovement OBJ_EVENT_ID_PLAYER, DewfordTown_Movement_PlayerBoardBoat
	waitmovement 0
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN
	call Common_EventScript_PlayBrineysBoatMusic
	applymovement LOCALID_BOAT_DEWFORD, DewfordTown_Movement_SailToPetalburg
	applymovement OBJ_EVENT_ID_PLAYER, DewfordTown_Movement_SailToPetalburg
	waitmovement 0
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_ROUTE104
	call Common_EventScript_StopBrineysBoatMusic
	applymovement OBJ_EVENT_ID_PLAYER, DewfordTown_Movement_ExitBoatPetalburg
	waitmovement 0
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_ROUTE104
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	clearflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	hideobjectat LOCALID_BOAT_DEWFORD, MAP_DEWFORD_TOWN
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 2
	resetobjectpriority OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN
	warp MAP_ROUTE104_MR_BRINEYS_HOUSE, 255, 5, 4
	copyvar VAR_BRINEY_LOCATION, VAR_0x8008
	waitstate
	release
	end

DewfordTown_EventScript_SailToSlateport:: @ 81E96E7
	call EventScript_BackupMrBrineyLocation
	setobjectpriority LOCALID_BRINEY_DEWFORD, MAP_DEWFORD_TOWN, 0
	setobjectpriority OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN, 1
	applymovement LOCALID_BRINEY_DEWFORD, DewfordTown_Movement_BrineyBoardBoat
	waitmovement 0
	removeobject LOCALID_BRINEY_DEWFORD
	applymovement OBJ_EVENT_ID_PLAYER, DewfordTown_Movement_PlayerBoardBoat
	waitmovement 0
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN
	call Common_EventScript_PlayBrineysBoatMusic
	applymovement LOCALID_BOAT_DEWFORD, DewfordTown_Movement_SailToSlateport
	applymovement OBJ_EVENT_ID_PLAYER, DewfordTown_Movement_SailToSlateport
	waitmovement 0
	call Common_EventScript_StopBrineysBoatMusic
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_ROUTE109
	applymovement OBJ_EVENT_ID_PLAYER, DewfordTown_Movement_ExitBoatSlateport
	waitmovement 0
	setobjectxyperm LOCALID_BRINEY_R109, 21, 26
	addobject LOCALID_BRINEY_R109
	setobjectpriority LOCALID_BRINEY_R109, MAP_ROUTE109, 0
	applymovement LOCALID_BRINEY_R109, DewfordTown_Movement_BrineyExitBoat
	waitmovement 0
	clearflag FLAG_HIDE_ROUTE_109_MR_BRINEY
	addobject LOCALID_BOAT_R109
	clearflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	hideobjectat LOCALID_BOAT_DEWFORD, MAP_DEWFORD_TOWN
	call_if_unset FLAG_DELIVERED_DEVON_GOODS, DewfordTown_EventScript_LandedSlateportDeliverGoods
	call_if_set FLAG_DELIVERED_DEVON_GOODS, DewfordTown_EventScript_LandedSlateport
	closemessage
	copyvar VAR_BRINEY_LOCATION, VAR_0x8008
	resetobjectpriority OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN
	resetobjectpriority LOCALID_BRINEY_R109, MAP_ROUTE109
	copyobjectxytoperm LOCALID_BRINEY_R109
	release
	end

DewfordTown_EventScript_LandedSlateportDeliverGoods:: @ 81E9790
	msgbox DewfordTown_Text_BrineyLandedInSlateportDeliverGoods, MSGBOX_DEFAULT
	return

DewfordTown_EventScript_LandedSlateport:: @ 81E9799
	msgbox DewfordTown_Text_BrineyLandedInSlateport, MSGBOX_DEFAULT
	return

DewfordTown_Movement_SailToPetalburg: @ 81E97A2
	walk_up
	walk_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DewfordTown_Movement_SailToSlateport: @ 81E9865
	walk_right
	walk_fast_right
	walk_fast_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

DewfordTown_Movement_PlayerBoardBoat: @ 81E9911
	walk_right
	walk_up
	step_end

DewfordTown_Movement_ExitBoatPetalburg: @ 81E9914
	walk_up
	walk_up
	walk_up
	step_end

DewfordTown_Movement_ExitBoatSlateport: @ 81E9918
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

DewfordTown_Movement_BrineyBoardBoat: @ 81E991D
	walk_up
	step_end

DewfordTown_Movement_BrineyExitBoat: @ 81E991F
	walk_up
	walk_up
	step_end

DewfordTown_EventScript_TrendyPhraseBoy:: @ 81E9922
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Text_XIsTheBiggestHappeningThingRight, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq DewfordTown_EventScript_ConfirmTrendyPhrase
	compare VAR_RESULT, NO
	goto_if_eq DewfordTown_EventScript_RejectTrendyPhrase
	end

DewfordTown_EventScript_ConfirmTrendyPhrase:: @ 81E9948
	msgbox DewfordTown_Text_YeahDefinitionOfInRightNow, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_RejectTrendyPhrase:: @ 81E9952
	msgbox DewfordTown_Text_TellMeWhatsNewAndIn, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_TRENDY_PHRASE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 1
	goto_if_eq DewfordTown_EventScript_GiveNewTrendyPhrase
	compare VAR_RESULT, 0
	goto_if_eq DewfordTown_EventScript_CancelNewTrendyPhrase
	end

DewfordTown_EventScript_GiveNewTrendyPhrase:: @ 81E997D
	incrementgamestat GAME_STAT_STARTED_TRENDS
	compare VAR_0x8004, 0
	goto_if_eq DewfordTown_EventScript_PhraseNotTrendyEnough
	msgbox DewfordTown_Text_OfCourseIKnowAboutThat, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_CancelNewTrendyPhrase:: @ 81E9994
	msgbox DewfordTown_Text_HearOfAnyTrendsComeShareWithMe, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_PhraseNotTrendyEnough:: @ 81E999E
	msgbox DewfordTown_Text_XHuhIThinkYIsCool, MSGBOX_DEFAULT
	release
	end

DewfordTown_Text_TinyIslandCommunity: @ 81E99A8
	.string "무로마을은 작은 섬이라서\n"
	.string "뭔가가 유행하기 시작하면\l"
	.string "다들 금방 그걸 따라하려고 해$"
	// ムロタウンって ちいさな しま だからｎ
	// なにかが はやりだすとｌ
	// みんな すぐに まねを するのよね

DewfordTown_Text_TownSign: @ 81E9A0F
	.string "여기는 무로마을\n"
	.string "푸른 바다에 떠 있는 작은 섬$"
	// ここは ムロ タウンｎ
	// あおい うみに うかぶ ちいさな しま

DewfordTown_Text_GymSign: @ 81E9A3D
	.string "무로마을 포켓몬체육관\n"
	.string "관장 철구\l"
	.string "격투의 빅 웨이브!$"
	// ムロ タウン ポケモンジムｎ
	// リ-ダ- トウキｌ
	// かくとう ビッグウェ-ブ!

DewfordTown_Text_HallSign: @ 81E9A7F
	.string "“무로집회소”\n"
	.string "모두의 정보교환 장소$"
	// 「ムロの しゅうかいじょ」ｎ
	// みんなの じょうほう こうかんの ばしょ

Route104_Text_LandedInDewfordDeliverLetter: @ 81E9AAF
	.string "하기: 호이! 무로마을에 도착!\p"
	.string "분명 성호라는 남자한테\n"
	.string "편지를 전해준다고 했었지!$"
	// ハギ『ほい! ムロに とうちゃく!ｐ
	// たしか ダイゴとやらにｎ
	// てがみを とどけるんだったな!

DewfordTown_Text_SetSailBackToPetalburg: @ 81E9B24
	.string "하기: 편지는 전달했나?\p"
	.string "아니면 등화도시로 돌아갈 겐가?$"
	// ハギ『てがみは とどけたのかい?ｐ
	// それとも トウカに もどるのかね?

DewfordTown_Text_PetalburgWereSettingSail2: @ 81E9B7F
	.string "하기: 그럼 등화도시로 돌아가겠네!\p"
	.string "좋다! 가자 피코!$"
	// ハギ『では トウカに もどると しよう!ｐ
	// よっしゃ! いくぞ ピ-コちゃん!

DewfordTown_Text_GoDeliverIllBeWaiting: @ 81E9BD9
	.string "하기: 그럼 편지를 전달하고 오게\n"
	.string "나는 여기서 기다리겠네$"
	// ハギ『では てがみを とどけておいでｎ
	// わしは ここで まっておるから

DewfordTown_Text_BrineyLandedInDewford: @ 81E9C1D
	.string "하기: 호이! 무로마을에 도착!\p"
	.string "배를 타고 싶어지면\n"
	.string "언제든 나한테 말하게나!$"
	// ハギ『ほい! ムロタウンに とうちゃく!ｐ
	// ふねに のりたくなったらｎ
	// また わしに こえを かけておくれ!

DewfordTown_Text_WhereAreWeBound: @ 81E9C8A
	.string "하기: 여어! 자네가 원한다면\n"
	.string "언제든지 배를 준비시키겠네!\p"
	.string "자네가 가고 싶은 곳은 어디인가?$"
	// ハギ『やあ! きみのため ならｎ
	// いつでも ふねを だそう!ｐ
	// きみが いきたいのは どこ かな?

DewfordTown_Text_PetalburgWereSettingSail: @ 81E9CE5
	.string "하기: 등화도시 말이지\p"
	.string "좋다! 가자 피코!$"
	// ハギ『トウカシティ かｐ
	// よっしゃ! いくぞ ピ-コちゃん!

DewfordTown_Text_SlateportWereSettingSail: @ 81E9D3A
	.string "하기: 잿빛도시 말이지\p"
	.string "좋다! 가자 피코!$"
	// ハギ『カイナシティ かｐ
	// よっしゃ! いくぞ ピ-コちゃん!

DewfordTown_Text_JustTellMeWhenYouNeedToSetSail: @ 81E9D8F
	.string "하기: 배를 타야 할 때는\n"
	.string "언제든지 말을 걸어주게나$"
	// ハギ『ふねに のる ひつようが あるときはｎ
	// いつでも こえを かけておくれ

DewfordTown_Text_GettingItchToFish: @ 81E9DD1
	.string "요 근처는 낚시의 명소야\n"
	.string "너도 낚시하고 싶어졌지?$"
	// このへんは つりの めいしょ なんだｎ
	// きみも つりが したくなった?

DewfordTown_Text_GiveYouOneOfMyRods: @ 81E9E14
	.string "응응 기쁜걸\n"
	.string "나한테 있는 낚싯대 나눠줄게!$"
	// うんうん うれしいなｎ
	// わたしの つりざお わけてあげよう!

DewfordTown_Text_ThrowInFishingAdvice: @ 81E9E65
	.string "좋-아 서비스로\n"
	.string "낚시 잘하는 방법도 알려줄게!\p"
	.string "먼저 수면을 향해\n"
	.string "낚싯대를 써!\p"
	.string "그리고 정신을 집중하다가...\n"
	.string "물었다 물었어!! 하는 느낌이 오면\l"
	.string "재빠르게 낚싯대를 잡아당기는 거야!\p"
	.string "바로 잡아당기면 될 때도 있지만\n"
	.string "월척은 몇 번이나 타이밍을\l"
	.string "맞출 필요가 있어!$"
	// よ-しっ だいサ-ビス!ｎ
	// つりの コツも せつめい しておくよ!ｐ
	// まずは すいめんに むかってｎ
	// つりざおを つかう!ｐ
	// そして きもちを しゅうちゅう させ……ｎ
	// ひいてる ひいてる!! となったらｌ
	// すばやく つりざおを ひくんだ!ｐ
	// すぐに ひきあげられる ときも あるけどｎ
	// おおものは なんども タイミングをｌ
	// あわせる ひつようが あるんだよ!

DewfordTown_Text_ThatsTooBadThen: @ 81E9F92
	.string "어라라...\n"
	.string "그거 안타깝네$"
	// あらら……ｎ
	// それは ざんねん

DewfordTown_Text_HowsYourFishing: @ 81E9FB8
	.string "어때!\n"
	.string "낚시는 잘하고 있어?$"
	// よっ!ｎ
	// つりの ちょうしは どう?

DewfordTown_Text_GreatHaulInSomeBigOnes: @ 81E9FD0
	.string "그렇구나! 그거 대단한데!\n"
	.string "월척을 한번 잡아 보라고!$"
	// そうか! そりゃ すごい!ｎ
	// おおものを つりあげて くれよ!

DewfordTown_Text_FishingAdvice: @ 81EA004
	.string "뭐야 실망하지 마!\n"
	.string "낚시 잘하는 방법을 알려줄 테니까!\p"
	.string "먼저 수면을 향해\n"
	.string "낚싯대를 써!\p"
	.string "그리고 정신을 집중하다가...\n"
	.string "물었다 물었어!! 하는 느낌이 오면\l"
	.string "재빠르게 낚싯대를 잡아당기는 거야!\p"
	.string "바로 잡아당기면 될 때도 있지만\n"
	.string "월척은 몇 번이나 타이밍을\l"
	.string "맞출 필요가 있어!$"
	// なんだよ ガッカリ しないでよ!ｎ
	// つりの コツを おしえて あげるから!ｐ
	// まずは すいめんに むかってｎ
	// つりざおを つかう!ｐ
	// そして きもちを しゅうちゅう させ……ｎ
	// ひいてる ひいてる!! となったらｌ
	// すばやく つりざおを ひくんだ!ｐ
	// すぐに ひきあげられる ときも あるけどｎ
	// おおものは なんども タイミングをｌ
	// あわせる ひつようが あるんだよ!

DewfordTown_Text_XIsTheBiggestHappeningThingRight: @ 81EA136
	.string "난 유행에 관심이 있어서\n"
	.string "항상 체크하고 있어\p"
	.string "혹시 “{STR_VAR_1}”{K_I}라고\n"
	.string "들어본 적 있어?\p"
	.string "당연히 들어본 적 있겠지!\p"
	.string "왜냐면 요즘\n"
	.string "“{STR_VAR_1}”{K_IGA}\l"
	.string "대유행하고 있잖아!\p"
	.string "네 주변에서도\n"
	.string "“{STR_VAR_1}”{K_IGA}\l"
	.string "유행하고 있지?$"
	// ぼく はやってる ものが すきでｎ
	// いつも チェック してるんだｐ
	// ねぇ 『§い』ってｎ
	// しってるかい?ｐ
	// もちろん しってるよね!ｐ
	// だって いまｎ
	// 『§い』がｌ
	// だいりゅうこう してるからね!ｐ
	// きみの まわりでもｎ
	// 『§い』がｌ
	// はやってる だろ?

DewfordTown_Text_TellMeWhatsNewAndIn: @ 81EA242
	.string "뭐?\n"
	.string "유행하지 않는다고!?\p"
	.string "그럼 요즘 뭐가 유행하고 있는지\n"
	.string "알려줘!$"
	// え?ｎ
	// はやって ないの!?ｐ
	// じゃあ いま なにが はやってるかｎ
	// きかせてよ!

DewfordTown_Text_OfCourseIKnowAboutThat: @ 81EA2AA
	.string "어? “{STR_VAR_2}”?\p"
	.string "......\p"
	.string "...아! 어어!\n"
	.string "알지 알지!\p"
	.string "다 당연히 알고 있다고!\n"
	.string "“{STR_VAR_2}” 말이지?\p"
	.string "그거 좋지!\n"
	.string "“{STR_VAR_2}”!\p"
	.string "지금 완전 유행 중이잖아\n"
	.string "내가 그걸 모를 리가 있나!\p"
	.string "“{STR_VAR_1}” 같은 건\n"
	.string "이미 한물갔지\p"
	.string "요즘은 “{STR_VAR_2}”의\n"
	.string "시대야!$"
	// え? 『§う』?ｐ
	// ……ｐ
	// …あ! あぁ!ｎ
	// しってる しってるよ!ｐ
	// もっ もちろん しってるさ!ｎ
	// 『§う』 だろ?ｐ
	// いいよね!ｎ
	// 『§う』 って!ｐ
	// いま すごく はやってる よねｎ
	// ぼくが しらないはず ないじゃ ないか!ｐ
	// 『§い』 なんてｎ
	// もう じだいおくれｐ
	// いまは 『§う』のｎ
	// じだい だね!

DewfordTown_Text_XHuhIThinkYIsCool: @ 81EA3FE
	.string "으-음...\n"
	.string "“{STR_VAR_2}”인가...\p"
	.string "하지만 난\n"
	.string "“{STR_VAR_1}” 쪽이\l"
	.string "멋지다고 생각해$"
	// ふ-んｎ
	// 『§う』 か…ｐ
	// でも ぼくはｎ
	// 『§い』 のほうがｌ
	// いいと おもうけどね

DewfordTown_Text_HearOfAnyTrendsComeShareWithMe: @ 81EA443
	.string "새로운 유행을 알게 되면\n"
	.string "나한테 꼭 알려줘!$"
	// じゃあ あたらしい りゅうこうが あったらｎ
	// また きかせて くれよ!

DewfordTown_Text_YeahDefinitionOfInRightNow: @ 81EA491
	.string "그치!\p"
	.string "역시 요즘은\n"
	.string "“{STR_VAR_1}” 시대지!$"
	// そうだろ!ｐ
	// やっぱり いまはｎ
	// 『§い』 だよね!
