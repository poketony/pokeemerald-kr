Route110_TrickHousePuzzle8_MapScripts:: @ 826E801
	.byte 0

Route110_TrickHousePuzzle8_EventScript_Scroll:: @ 826E802
	lockall
	compare VAR_TRICK_HOUSE_PUZZLE_8_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle8_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle8_EventScript_FoundScroll:: @ 826E814
	setvar VAR_TRICK_HOUSE_PUZZLE_8_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle8_EventScript_Vincent:: @ 826E81F
	trainerbattle_single TRAINER_VINCENT, Route110_TrickHousePuzzle8_Text_VincentIntro, Route110_TrickHousePuzzle8_Text_VincentDefeat
	msgbox Route110_TrickHousePuzzle8_Text_VincentPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Keira:: @ 826E836
	trainerbattle_single TRAINER_KEIRA, Route110_TrickHousePuzzle8_Text_KeiraIntro, Route110_TrickHousePuzzle8_Text_KeiraDefeat
	msgbox Route110_TrickHousePuzzle8_Text_KeiraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Leroy:: @ 826E84D
	trainerbattle_single TRAINER_LEROY, Route110_TrickHousePuzzle8_Text_LeroyIntro, Route110_TrickHousePuzzle8_Text_LeroyDefeat
	msgbox Route110_TrickHousePuzzle8_Text_LeroyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_WroteSecretCodeLockOpened:: @ 826E864
	.string "{PLAYER}{K_EUNNEUN} 암호를\n"
	.string "문에 적었다!\p"
	.string "“미궁대왕님 사랑해요”\p"
	.string "...... ...... ......\p"
	.string "문의 자물쇠가 풀렸다!$"
	// §あは あいことばをｎ
	// とびらに かきつけた!ｐ
	// 「カラクリだいおう さま あいしてる」ｐ
	// …… …… ……ｐ
	// かぎの はずれる おとがした!

Route110_TrickHousePuzzle8_Text_VincentIntro: @ 826E8CD
	.string "여기까지 올 수 있는 트레이너는\n"
	.string "그렇게 많지 않네!$"
	// ここまで こられる トレ-ナ-はｎ
	// そうは いないよな!

Route110_TrickHousePuzzle8_Text_VincentDefeat: @ 826E8F6
	.string "즉 너도\n"
	.string "대단하다는 거겠지...$"
	// つまり キミもｎ
	// すごいって ことだよな…

Route110_TrickHousePuzzle8_Text_VincentPostBattle: @ 826E918
	.string "뭣 포켓몬리그의 챔피언을\n"
	.string "이겼다고? 대 대단해...!$"
	// えっ ポケモンリ-グの チャンピオンにｎ
	// かったって? す すごい……!

Route110_TrickHousePuzzle8_Text_KeiraIntro: @ 826E954
	.string "나와 승부하다니\n"
	.string "당신 행복하겠구나!$"
	// わたしと しょうぶ できるなんてｎ
	// あなた しあわせよ!

Route110_TrickHousePuzzle8_Text_KeiraDefeat: @ 826E97F
	.string "이럴 수가 내가\n"
	.string "져버리다니...!$"
	// そんな わたしがｎ
	// まけるなんて……!

Route110_TrickHousePuzzle8_Text_KeiraPostBattle: @ 826E99F
	.string "나를 이긴 건 기적이야!\n"
	.string "자랑스러워할 일이라고!$"
	// わたしに かつなんて きせきよ!ｎ
	// じまん できる ことだわ!

Route110_TrickHousePuzzle8_Text_LeroyIntro: @ 826E9D7
	.string "당신도 미궁의 대저택에\n"
	.string "계속해서 도전하고 있군요!$"
	// あなたも カラクリやしきにｎ
	// ちょうせん しつづけて いるんですね!

Route110_TrickHousePuzzle8_Text_LeroyDefeat: @ 826EA14
	.string "과연...\n"
	.string "놀라운 센스로군요!$"
	// なるほど……ｎ
	// すばらしい センスですね!

Route110_TrickHousePuzzle8_Text_LeroyPostBattle: @ 826EA3F
	.string "당신 같은 사람이 와 줘서\n"
	.string "미궁대왕도 만족하겠죠!$"
	// あなた みたいな ひとが きてくれてｎ
	// カラクリだいおうも まんぞく でしょうね!

