MagmaHideout_1F_MapScripts:: @ 8239880
	map_script MAP_SCRIPT_ON_TRANSITION, MagmaHideout_1F_OnTransition
	.byte 0

MagmaHideout_1F_OnTransition: @ 8239886
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 0
	end

MagmaHideout_1F_EventScript_Grunt1:: @ 823988C
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_1, MagmaHideout_1F_Text_Grunt1Intro, MagmaHideout_1F_Text_Grunt1Defeat
	msgbox MagmaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_EventScript_Grunt2:: @ 82398A3
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_2, MagmaHideout_1F_Text_Grunt2Intro, MagmaHideout_1F_Text_Grunt2Defeat
	msgbox MagmaHideout_1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_Text_Grunt1Intro: @ 82398BA
	.string "마그마단은 명령을 받았을 때\n"
	.string "빨리 줄을 선 순서대로\l"
	.string "중요한 장소의\l"
	.string "경비를 맡는다고!\p"
	.string "내가 이런 후미진 곳에 있는 건\n"
	.string "허구한 날 지각만 하기 때문이지!$"
	// マグマだんは ごうれいが かかったときｎ
	// はやく せいれつした じゅんばんでｌ
	// じゅうような ばしょのｌ
	// けいびを まかせて もらえるんだぜ!ｐ
	// オレが こんな すみっこに いるのはｎ
	// ちこく ばっかり してるからさ!

MagmaHideout_1F_Text_Grunt1Defeat: @ 8239964
	.string "트레이닝에도 지각하는 나!\n"
	.string "내가 봐도 난 약하구나...$"
	// トレ-ニングにも ちこくする オレだ!ｎ
	// われながら よわいぜ……

MagmaHideout_1F_Text_Grunt1PostBattle: @ 82399B1
	.string "알았어 다음부터는 좀 더\n"
	.string "힘내보도록 할게$"
	// わかったよ こんどから もうすこしｎ
	// がんばって みるよ……

MagmaHideout_1F_Text_Grunt2Intro: @ 82399F5
	.string "리더에게 들은 대로\n"
	.string "굴뚝산을 점점 파고 들어갔더니\l"
	.string "말도 안되는 게 나와버렸어!\p"
	.string "뭐가 나왔냐고?\p"
	.string "우하하하!\n"
	.string "나를 쓰러뜨리면 알려줄게!$"
	// リ-ダ-に いわれた とおりｎ
	// えんとつやまを どんどん ほっていたらｌ
	// とんでもねえモンが でちまった!ｐ
	// なにが でたかって?ｐ
	// ふははは!ｎ
	// オレを たおせたら おしえて やるよ!

MagmaHideout_1F_Text_Grunt2Defeat: @ 8239ABA
	.string "으윽... 쓰러뜨려졌다!$"
	// むぐぅ…… たおされちまった!

MagmaHideout_1F_Text_Grunt2PostBattle: @ 8239ACD
	.string "역시 알려주지 않을래!\n"
	.string "어차피 안쪽까지 가면 알게 될걸!\p"
	.string "너도 즐거움을 위해\n"
	.string "그때 가서 보는 게 낫지 않겠어?$"
	// やっぱり おしえるの や-めた!ｎ
	// どうせ おくまで いけば わかることさ!ｐ
	// おまえも あとに おたのしみをｎ
	// のこして おいたほうが いいだろ?

