AbandonedShip_CaptainsOffice_MapScripts::
	.byte 0

AbandonedShip_CaptainsOffice_EventScript_CaptSternAide::
	lock
	faceplayer
	goto_if_set FLAG_EXCHANGED_SCANNER, AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus
	checkitem ITEM_SCANNER, 1
	compare VAR_RESULT, TRUE
	goto_if_eq AbandonedShip_CaptainsOffice_EventScript_CanYouDeliverScanner
	goto_if_set FLAG_ITEM_ABANDONED_SHIP_HIDDEN_FLOOR_ROOM_4_SCANNER, AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus
	msgbox AbandonedShip_CaptainsOffice_Text_NoSuccessFindingScanner, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_EventScript_CanYouDeliverScanner::
	msgbox AbandonedShip_CaptainsOffice_Text_OhCanYouDeliverScanner, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus::
	msgbox AbandonedShip_CaptainsOffice_Text_ThisIsSSCactus, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_Text_NoSuccessFindingScanner:
	.string "해양관장님의 부탁으로\n"
	.string "이 배를 조사하고 있었어\p"
	.string "조사하는 김에 탐지기를\n"
	.string "찾아 달라고 하셨는데\l"
	.string "찾을 수가 없었어...$"

AbandonedShip_CaptainsOffice_Text_OhCanYouDeliverScanner:
	.string "앗! 탐지기잖아!\p"
	.string "...괜찮으면 그거\n"
	.string "해양관장님에게\l"
	.string "전해 주지 않을래?\p"
	.string "난 좀 더 여기를 조사하려고$"

AbandonedShip_CaptainsOffice_Text_ThisIsSSCactus:
	.string "이 배는 캑터스호라고 불리고 있어\n"
	.string "조금 오래된 배인 것 같아$"
