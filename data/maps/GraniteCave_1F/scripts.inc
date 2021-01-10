GraniteCave_1F_MapScripts:: @ 822DA5D
	.byte 0

GraniteCave_1F_EventScript_Hiker:: @ 822DA5E
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM05, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM05
	setflag FLAG_RECEIVED_HM05
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash:: @ 822DA8A
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo: @ 822DA94
	.string "어이 거기 너\n"
	.string "이 앞은 어두워서\l"
	.string "탐험하는 것도 힘들어!\p"
	.string "방금 전에 여기 온 남자...\n"
	.string "성호라고 했었나?\p"
	.string "플래시의 사용법을 알고 있어서\n"
	.string "괜찮을 거라고 생각해\p"
	.string "음! 등산가는 만난 사람에게\n"
	.string "상냥하게 대하는 것이 신조!\p"
	.string "이걸 너한테 줄게!$"

GraniteCave_1F_Text_ExplainFlash: @ 822DBB7
	.string "비전기술 플래시를 포켓몬한테\n"
	.string "배우게 해서 사용하면 말이지\p"
	.string "깜깜한 동굴을\n"
	.string "밝게 비춰줘!\p"
	.string "뭐 사용하려면 무로의\n"
	.string "체육관 배지가 필요하지만$"

