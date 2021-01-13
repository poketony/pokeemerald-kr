MagmaHideout_2F_1R_MapScripts:: @ 8239B50
	.byte 0

MagmaHideout_2F_1R_EventScript_Grunt14:: @ 8239B51
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_14, MagmaHideout_2F_1R_Text_Grunt14Intro, MagmaHideout_2F_1R_Text_Grunt14Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt14PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt3:: @ 8239B68
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_3, MagmaHideout_2F_1R_Text_Grunt3Intro, MagmaHideout_2F_1R_Text_Grunt3Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt4:: @ 8239B7F
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_4, MagmaHideout_2F_1R_Text_Grunt4Intro, MagmaHideout_2F_1R_Text_Grunt4Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt5:: @ 8239B96
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_5, MagmaHideout_2F_1R_Text_Grunt5Intro, MagmaHideout_2F_1R_Text_Grunt5Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_Text_Grunt14Intro: @ 8239BAD
	.string "여기에 들어올 수 있는 건\n"
	.string "마그마단의 멤버뿐!\p"
	.string "하지만 너는\n"
	.string "마그마단 복장을 안 입었는데...\p"
	.string "에-이 수상한 녀석!\n"
	.string "나하고 승부해라!$"
	// ここに はいって これるのはｎ
	// マグマだんの メンバ- だけのはず!ｐ
	// なのに あなたはｎ
	// マグマだんの ふくを きていない……ｐ
	// え-い あやしい やつめ!ｎ
	// わたしと しょうぶ しなさい!

MagmaHideout_2F_1R_Text_Grunt14Defeat: @ 8239C4B
	.string "어버버버...\n"
	.string "마그마단의 프라이드가...$"
	// あわわわ……ｎ
	// マグマだんの プライドが……

MagmaHideout_2F_1R_Text_Grunt14PostBattle: @ 8239C74
	.string "추위를 잘 타는 사람은\n"
	.string "마그마단에 들어오는 편이 좋아$"
	// さむがりの ひとはｎ
	// マグマだんに はいると いいわよ

MagmaHideout_2F_1R_Text_Grunt3Intro: @ 8239CAB
	.string "이봐이봐!\p"
	.string "내 눈에 보인 주제에\n"
	.string "그대로 지나가려고 한 거냐!$"
	// こらこら!ｐ
	// オレの めのまえを だまってｎ
	// すどおり させる わけには いかね-ぞ!

MagmaHideout_2F_1R_Text_Grunt3Defeat: @ 8239D09
	.string "우왓! 져버렸다!$"
	// うはっ! まけましたっ!

MagmaHideout_2F_1R_Text_Grunt3PostBattle: @ 8239D1D
	.string "이럴 거였으면 그냥 지나가게\n"
	.string "놔둘 걸 그랬어...$"
	// こんなことなら すどおり していってｎ
	// もらうほうが よかったかも……

MagmaHideout_2F_1R_Text_Grunt4Intro: @ 8239D62
	.string "여어! 수상한 녀석!$"
	// やや! あやしい やつめ!

MagmaHideout_2F_1R_Text_Grunt4Defeat: @ 8239D75
	.string "으어억...$"
	// ぬおお……

MagmaHideout_2F_1R_Text_Grunt4PostBattle: @ 8239D7D
	.string "승부에서 졌는데\n"
	.string "계속 여기를 빙글빙글 돌\l"
	.string "이유가 있을까?$"
	// しょうぶに まけたのにｎ
	// まだ ここを ぐるぐる まわるｌ
	// ひつようが あるんだろうか?

MagmaHideout_2F_1R_Text_Grunt5Intro: @ 8239DC5
	.string "우우! 수상한 녀석!$"
	// むむ! あやしい やつめ!

MagmaHideout_2F_1R_Text_Grunt5Defeat: @ 8239DDA
	.string "으아악...$"
	// うぬぬ……

MagmaHideout_2F_1R_Text_Grunt5PostBattle: @ 8239DE2
	.string "나 사실은 포켓몬 승부\n"
	.string "많이 못하거든$"
	// オレ ほんとは ポケモンしょうぶｎ
	// あんまり とくいじゃ ないんだよね

