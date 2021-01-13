MagmaHideout_3F_1R_MapScripts:: @ 823A1B2
	.byte 0

MagmaHideout_3F_1R_EventScript_Grunt9:: @ 823A1B3
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_9, MagmaHideout_3F_1R_Text_Grunt9Intro, MagmaHideout_3F_1R_Text_Grunt9Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt9PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_EventScript_Grunt16:: @ 823A1CA
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_16, MagmaHideout_3F_1R_Text_Grunt16Intro, MagmaHideout_3F_1R_Text_Grunt16Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt16PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_Text_Grunt9Intro: @ 823A1E1
	.string "왜 나는 이런 곳을\n"
	.string "담당하게 된 거야!\p"
	.string "왼쪽 귀가 뜨거워!$"
	// なんで オレは こんなところのｎ
	// たんとう なんだよ!ｐ
	// ひだりのみみ が あつい じゃね-か!

MagmaHideout_3F_1R_Text_Grunt9Defeat: @ 823A229
	.string "뜨거워서 맥빠진다...$"
	// あつくて ヘロヘロ……

MagmaHideout_3F_1R_Text_Grunt9PostBattle: @ 823A246
	.string "이런 마그마투성이인 화산 안에서\n"
	.string "후드를 쓴 우리들이 이상한 거지?$"
	// こんな マグマだらけの かざんの なかでｎ
	// フ-ドを かぶってる オレたち へん?

MagmaHideout_3F_1R_Text_Grunt16Intro: @ 823A293
	.string "우리들은 리더가 노리고 있는\n"
	.string "굉장한 목적을\l"
	.string "실현하기 위해 모였지!\p"
	.string "아쿠아단 따위나\n"
	.string "지나가던 꼬마가\l"
	.string "방해한다면 용서치 않겠어!$"
	// アタシたちは リ-ダ-が めざしているｎ
	// すばらしい もくてきをｌ
	// じつげん するために あつまったの!ｐ
	// アクアだん だろうがｎ
	// とおりすがりの おこさま だろうがｌ
	// じゃまを するなら ゆるさないわ!

MagmaHideout_3F_1R_Text_Grunt16Defeat: @ 823A353
	.string "헤에- 강하구나!$"
	// ひえ- あなどれない ひと!

MagmaHideout_3F_1R_Text_Grunt16PostBattle: @ 823A37C
	.string "알겠어? 옳은 건 마그마단이야!\n"
	.string "아쿠아단이 말하는 건\l"
	.string "거짓말밖에 없으니까 믿으면 안 돼!$"
	// いい? ただしいのは マグマだんよ!ｎ
	// アクアだんの いうことなんかｌ
	// うそ ばっかりだから しんじちゃ ダメよ!

