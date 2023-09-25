SootopolisCity_House6_MapScripts:: @ 8226F5B
	.byte 0

SootopolisCity_House6_EventScript_Woman:: @ 8226F5C
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WAILMER_DOLL, SootopolisCity_House6_EventScript_ReceivedWailmerDoll
	msgbox SootopolisCity_House6_Text_FirstGuestInWhileTakeDoll, MSGBOX_YESNO
	compare VAR_RESULT, NO
	call_if_eq SootopolisCity_House6_EventScript_DeclineWailmerDoll
	msgbox SootopolisCity_House6_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	givedecoration DECOR_WAILMER_DOLL
	compare VAR_RESULT, FALSE
	goto_if_eq SootopolisCity_House6_EventScript_NoRoomForWailmerDoll
	setflag FLAG_RECEIVED_WAILMER_DOLL
	release
	end

SootopolisCity_House6_EventScript_DeclineWailmerDoll:: @ 8226F99
	msgbox SootopolisCity_House6_Text_DontWantThisDoll, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_EventScript_ReceivedWailmerDoll:: @ 8226FA3
	msgbox SootopolisCity_House6_Text_LovePlushDolls, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_EventScript_NoRoomForWailmerDoll:: @ 8226FAD
	bufferdecorationname 1, DECOR_WAILMER_DOLL
	msgbox gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	msgbox SootopolisCity_House6_Text_IllHoldItForYou, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_Text_FirstGuestInWhileTakeDoll: @ 8226FC3
	.string "와- 이게 얼마 만에 오신 손님이야!?\p"
	.string "너-무 기쁘니까\n"
	.string "커다란 고래왕자인형을 줄게!$"

SootopolisCity_House6_Text_TakeGoodCareOfIt: @ 8227034
	.string "소중히 해줘!$"

SootopolisCity_House6_Text_IllHoldItForYou: @ 822704A
	.string "필요하지만 지금은 안 돼?\n"
	.string "그럼 가지고 있을게$"

SootopolisCity_House6_Text_DontWantThisDoll: @ 822708F
	.string "그래?\n"
	.string "인형 필요 없니?$"

SootopolisCity_House6_Text_LovePlushDolls: @ 82270B7
	.string "난 인형이 너무 좋아!$"

