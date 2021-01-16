.set LOCALID_BRINEY, 1
.set LOCALID_PEEKO, 2

Route104_MrBrineysHouse_MapScripts:: @ 8229D2E
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_MrBrineysHouse_OnTransition
	.byte 0

Route104_MrBrineysHouse_OnTransition: @ 8229D34
	setflag FLAG_LANDMARK_MR_BRINEY_HOUSE
	compare VAR_BRINEY_HOUSE_STATE, 1
	call_if_eq Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos
	call_if_set FLAG_RECEIVED_POKENAV, Route104_MrBrineysHouse_EventScript_HideRustboroRival
	end

Route104_MrBrineysHouse_EventScript_HideRustboroRival:: @ 8229D4C
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	return

Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos:: @ 8229D50
	setobjectxyperm LOCALID_BRINEY, 9, 3
	setobjectmovementtype LOCALID_BRINEY, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT
	setobjectxyperm LOCALID_PEEKO, 9, 6
	setobjectmovementtype LOCALID_PEEKO, MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN
	return

Route104_MrBrineysHouse_EventScript_Briney:: @ 8229D67
	lock
	faceplayer
	call_if_unset FLAG_MR_BRINEY_SAILING_INTRO, Route104_MrBrineysHouse_EventScript_SailingIntro
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, Route104_MrBrineysHouse_EventScript_SailBothDeliveries
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, Route104_MrBrineysHouse_EventScript_SailDeliverPackage
	goto Route104_MrBrineysHouse_EventScript_WhereAreWeBound
	end

Route104_MrBrineysHouse_EventScript_SailingIntro:: @ 8229D8A
	setflag FLAG_MR_BRINEY_SAILING_INTRO
	msgbox Route104_MrBrineysHouse_Text_WaitUpPeeko, MSGBOX_DEFAULT
	msgbox Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_WhereAreWeBound:: @ 8229DAE
	message Route104_MrBrineysHouse_Text_WhereAreWeBound
	waitmessage
	multichoicedefault 20, 8, MULTI_BRINEY_OFF_DEWFORD, 1, 0
	switch VAR_RESULT
	case 0, Route104_MrBrineysHouse_EventScript_SailToDewford
	case 1, Route104_MrBrineysHouse_EventScript_DeclineSailing
	case MULTI_B_PRESSED, Route104_MrBrineysHouse_EventScript_DeclineSailing
	end

Route104_MrBrineysHouse_EventScript_SailBothDeliveries:: @ 8229DE1
	msgbox Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_SailDeliverPackage:: @ 8229DFA
	msgbox Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing:: @ 8229E13
	msgbox Route104_MrBrineysHouse_Text_DeclineDeliverySail, MSGBOX_DEFAULT
	release
	end

Route104_MrBrineysHouse_EventScript_DeclineSailing:: @ 8229E1D
	msgbox Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail, MSGBOX_DEFAULT
	release
	end

Route104_MrBrineysHouse_EventScript_SailToDewford:: @ 8229E27
	msgbox Route104_MrBrineysHouse_Text_SetSailForDewford, MSGBOX_DEFAULT
	call EventScript_BackupMrBrineyLocation
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 1
	clearflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_RUSTBORO_CITY_STATE, 8
	setvar VAR_ROUTE104_STATE, 2
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setflag FLAG_HIDE_ROUTE_104_RIVAL
	warp MAP_ROUTE104, 255, 13, 51
	waitstate
	releaseall
	end

Route104_MrBrineysHouse_EventScript_Peeko:: @ 8229E5D
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, 0
	msgbox Route104_MrBrineysHouse_Text_Peeko, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route104_MrBrineysHouse_Text_WaitUpPeeko: @ 8229E70
	.string "하기: 이 녀석!\n"
	.string "거기 서라 피코!$"

Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford: @ 8229E9B
	.string "응? 자네는 저번에\n"
	.string "피코를 구해준 {PLAYER} 아니더냐!\l"
	.string "그때는 정말 신세 졌구먼!\p"
	.string "...뭐라고?\n"
	.string "배를 타고 싶다고?\p"
	.string "흠?\p"
	.string "무로마을까지 편지와\n"
	.string "잿빛도시에 화물을\l"
	.string "전달해야 한다고...\p"
	.string "그 정도야 식은 죽 먹기다!\n"
	.string "나에게 맡기게나!\l"
	.string "그럼 바로 무로마을로 가볼까!$"

Route104_MrBrineysHouse_Text_SetSailForDewford: @ 8229FE9
	.string "하기: 무로마을 말이지\p"
	.string "좋아! 가자 피코!$"

Route104_MrBrineysHouse_Text_DeclineDeliverySail: @ 822A041
	.string "하기: 그러냐\n"
	.string "부탁받은 일은 괜찮나?\p"
	.string "뭐 배를 타야 할 때는\n"
	.string "언제든지 사양 말고 말해 주게나!$"

Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford: @ 822A0AD
	.string "하기: 자네가 무슨 말을\n"
	.string "하고 싶은지는 알고 있어!\p"
	.string "무로마을로 편지를 전달하고\n"
	.string "잿빛도시에 화물을 갖다 줘야\l"
	.string "하는 게지?\p"
	.string "그 정도야 식은 죽 먹기다!\n"
	.string "나에게 맡기게나!\p"
	.string "우선 무로마을로 출발하자꾸나$"

Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford: @ 822A18F
	.string "하기: 자네가 무슨 말을\n"
	.string "하고 싶은지는 알고 있어!\p"
	.string "잿빛도시에 있는 해양씨한테\n"
	.string "화물을 전달해야 하는 게지?\p"
	.string "그 정도야 식은 죽 먹기다!\n"
	.string "나에게 맡기게나!\p"
	.string "우선 무로마을로 출발하자꾸나$"

Route104_MrBrineysHouse_Text_WhereAreWeBound: @ 822A268
	.string "하기: 여어! 자네가 원한다면\n"
	.string "언제든지 배를 준비시키지!\p"
	.string "자네가 가고 싶은 곳은 어딘가?$"

Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail: @ 822A2C3
	.string "하기: 그런가... 자네는\n"
	.string "피코의 생명의 은인이다\p"
	.string "배를 타야 할 때는\n"
	.string "언제든지 사양 말고 말해 주게나!$"

Route104_MrBrineysHouse_Text_Peeko: @ 822A337
	.string "피코: 피- 피피-!$"

