MtPyre_4F_MapScripts:: @ 8231BC8
	.byte 0

@ Seems like the scripts for the 4F and 5F were swapped

MtPyre_5F_EventScript_Atsushi:: @ 8231BC9
	trainerbattle_single TRAINER_ATSUSHI, MtPyre_5F_Text_AtsushiIntro, MtPyre_5F_Text_AtsushiDefeat
	msgbox MtPyre_5F_Text_AtsushiPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_5F_Text_AtsushiIntro: @ 8231BE0
	.string "스승님...\n"
	.string "지금의 제 실력을\l"
	.string "지켜봐 주세요!$"
	// おししょうさま……ｎ
	// いまの わたしの じつりょくｌ
	// みていて ください!

MtPyre_5F_Text_AtsushiDefeat: @ 8231C08
	.string "스승님...\n"
	.string "죄송합니다...$"
	// おししょうさま……ｎ
	// すんません……

MtPyre_5F_Text_AtsushiPostBattle: @ 8231C24
	.string "더욱 강해지지 않으면\n"
	.string "이곳에 잠들어 계신 스승님도\l"
	.string "안심하실 수 없겠지...$"
	// もっと つよくならないとｎ
	// ここに ねむる おししょうさまもｌ
	// あんしん できないよな……

