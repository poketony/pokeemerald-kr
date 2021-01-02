RustboroCity_CuttersHouse_MapScripts:: @ 8215BD3
	.byte 0

RustboroCity_CuttersHouse_EventScript_Cutter:: @ 8215BD4
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM01, RustboroCity_CuttersHouse_EventScript_ExplainCut
	msgbox RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse, MSGBOX_DEFAULT
	giveitem ITEM_HM01
	setflag FLAG_RECEIVED_HM01
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_ExplainCut:: @ 8215C00
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_Lass:: @ 8215C0A
	msgbox RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees, MSGBOX_NPC
	end

RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse: @ 8215C13
	.string "그 눈매\n"
	.string "유연한 몸놀림...\l"
	.string "그리고 단련된 포켓몬...\l"
	.string "너는 제법 하는 트레이너구나!\p"
	.string "아무 말 하지 않아도 된다\n"
	.string "난 알 수 있어 알 수 있다고!\p"
	.string "너라면 이 비전머신\n"
	.string "능숙히 쓸 수 있을 거다\l"
	.string "자 사양하지 말고 가지고 가거라!$"

RustboroCity_CuttersHouse_Text_ExplainCut: @ 8215D33
	.string "그 비전머신은 풀베기!\p"
	.string "비전기술은 싸우고 있지 않을 때도\n"
	.string "쓸 수 있다!\p"
	.string "풀베기를 배운 포켓몬은\n"
	.string "스톤배지를 가지고 있으면\p"
	.string "얇은 나무를\n"
	.string "자를 수 있게 된다!\p"
	.string "그리고 기술머신과는 달리\n"
	.string "비전머신은 여러 번 쓸 수 있다!$"

RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees: @ 8215E39
	.string "이 금탄도시가\n"
	.string "그리 크지 않던 때에\p"
	.string "아빠가 모두를 위해\n"
	.string "풀베기를 써서\l"
	.string "이 주변을 개간했어!$"

