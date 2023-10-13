MagmaHideout_3F_2R_MapScripts:: @ 823A3D4
	.byte 0

MagmaHideout_3F_2R_EventScript_Grunt10:: @ 823A3D5
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_10, MagmaHideout_3F_2R_Text_Grunt10Intro, MagmaHideout_3F_2R_Text_Grunt10Defeat
	msgbox MagmaHideout_3F_2R_Text_Grunt10PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_2R_Text_Grunt10Intro: @ 823A3EC
	.string "있잖아 리더가 말하는 건\n"
	.string "나도 잘 알겠지만\p"
	.string "초 고대포켓몬을 파내거나\n"
	.string "남의 운석을 가로채거나\l"
	.string "뭔가 좀 지나친 거\l"
	.string "같은 기분이 들어\p"
	.string "너는 어떻게 생각해?$"
	// あのな リ-ダ-の いうことはｎ
	// オレにも よく わかるんだけど なｐ
	// ちょうこだいポケモンを ほりだしたりｎ
	// ひとの いんせきを よこどりしたりｌ
	// なんか それって ちょっと やりすぎｌ
	// のような きもするんだよ なｐ
	// おまえ どう おもう?

MagmaHideout_3F_2R_Text_Grunt10Defeat: @ 823A4BB
	.string "역시 뭔가 잘못된 거 아닐까?$"
	// やっぱり なんか まちがってる よなあ?

MagmaHideout_3F_2R_Text_Grunt10PostBattle: @ 823A4EF
	.string "승부에서 져서 개운해졌어!\p"
	.string "나도 다음에 리더를 만나면\n"
	.string "실제로 어떤지 물어볼게!$"
	// しょうぶに まけて スッキリしたよ!ｐ
	// オレも こんど リ-ダ-に あったらｎ
	// じっさい どうなのか きいて みるよ!

