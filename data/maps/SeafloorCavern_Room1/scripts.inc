SeafloorCavern_Room1_MapScripts:: @ 82347EB
	.byte 0

SeafloorCavern_Room1_EventScript_Grunt1:: @ 82347EC
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_1, SeafloorCavern_Room1_Text_Grunt1Intro, SeafloorCavern_Room1_Text_Grunt1Defeat
	msgbox SeafloorCavern_Room1_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room1_EventScript_Grunt2:: @ 8234803
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_2, SeafloorCavern_Room1_Text_Grunt2Intro, SeafloorCavern_Room1_Text_Grunt2Defeat
	msgbox SeafloorCavern_Room1_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room1_Text_Grunt1Intro: @ 823481A
	.string "꼬마에게 볼일은 없다\n"
	.string "자 얼른 돌아가!$"
	// こどもに ようは ね-んだｎ
	// ほら さっさと かえれよ!

SeafloorCavern_Room1_Text_Grunt1Defeat: @ 823484A
	.string "내가 돌아가고 싶어-!$"
	// おれが かえりたいよ-!

SeafloorCavern_Room1_Text_Grunt1PostBattle: @ 823485D
	.string "빨리 간부가 돼서\n"
	.string "조무래기들을 괴롭혀주고 싶다...$"
	// はやく かんぶに なってｎ
	// したっぱを しごいて やりたい……

SeafloorCavern_Room1_Text_Grunt2Intro: @ 8234898
	.string "잠수정이 너무 좁아서-\n"
	.string "몸 여기저기가 아프단 말이지-!$"
	// せんすいてい ちっちゃいからよ-ｎ
	// からだの あちこちが いたい じゃね-か!

SeafloorCavern_Room1_Text_Grunt2Defeat: @ 82348CD
	.string "지면\n"
	.string "마음이 아프단 말이지-!$"
	// まけたらｎ
	// いたい じゃね-か!

SeafloorCavern_Room1_Text_Grunt2PostBattle: @ 82348E3
	.string "빼앗은 잠수정의 승차감은\n"
	.string "완전 최악이야!\l"
	.string "일단 너무 좁단 말이지-!$"
	// うばった せんすいていの のりごこちｎ
	// ありゃ さいあく だな!ｌ
	// とにかく せますぎ じゃね-か!

