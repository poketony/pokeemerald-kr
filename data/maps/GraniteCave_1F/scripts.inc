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
	.string "이봐 너\n"
	.string "이 앞은 어두워서\l"
	.string "탐험하는 것도 힘들어!\p"
	.string "방금 전의 남자...\n"
	.string "성호라고 했었나?\p"
	.string "그 녀석은 플래시를 쓸 줄 아니까\n"
	.string "괜찮을 테지...\p"
	.string "음! 등산가는 만난 사람에게\n"
	.string "상냥하게 대하는 것이 신조!\l"
	.string "이걸 너한테 주마!$"
	@ おい おまえｎ
	@ このさきは くらいからｌ
	@ たんけん するのも たいへん だぞ!ｐ
	@ さっきの おとこ……ｎ
	@ ダイゴって いったっけか?ｐ
	@ あいつは フラッシュが つかえたからｎ
	@ だいじょうぶ だろうが……ｐ
	@ うむ! やまおとこは であったｎ
	@ あいてに やさしく するのが モット-!ｌ
	@ これを ゆずってやると するか!

GraniteCave_1F_Text_ExplainFlash: @ 822DBB7
	.string "비전기술 플래시를\n"
	.string "포켓몬한테 배우게 해서 사용하면 말이지\p"
	.string "깜깜한 동굴을\n"
	.string "밝게 비춰줘!\p"
	.string "뭐 사용하려면 무로체육관의\n"
	.string "체육관 배지가 필요하지만 말이야$"
	@ ひでん フラッシュをｎ
	@ ポケモンに おぼえさせて つかうとだなｐ
	@ まっくらな どうくつもｎ
	@ あかるく てらせるんだぞ!ｐ
	@ まあ つかうには ムロ ポケモンジムのｎ
	@ ジムバッジが ひつよう だがな

