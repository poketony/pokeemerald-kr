Route110_TrickHousePuzzle4_MapScripts:: @ 826C860
	.byte 0

Route110_TrickHousePuzzle4_EventScript_Scroll:: @ 826C861
	lockall
	compare VAR_TRICK_HOUSE_PUZZLE_4_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle4_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle4_EventScript_FoundScroll:: @ 826C873
	setvar VAR_TRICK_HOUSE_PUZZLE_4_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle4_EventScript_Cora:: @ 826C87E
	trainerbattle_single TRAINER_CORA, Route110_TrickHousePuzzle4_Text_CoraIntro, Route110_TrickHousePuzzle4_Text_CoraDefeat
	msgbox Route110_TrickHousePuzzle4_Text_CoraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Yuji:: @ 826C895
	trainerbattle_single TRAINER_YUJI, Route110_TrickHousePuzzle4_Text_YujiIntro, Route110_TrickHousePuzzle4_Text_YujiDefeat
	msgbox Route110_TrickHousePuzzle4_Text_YujiPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Paula:: @ 826C8AC
	trainerbattle_single TRAINER_PAULA, Route110_TrickHousePuzzle4_Text_PaulaIntro, Route110_TrickHousePuzzle4_Text_PaulaDefeat
	msgbox Route110_TrickHousePuzzle4_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_Text_WroteSecretCodeLockOpened: @ 826C8C3
	.string "{PLAYER}{K_EUNNEUN} 암호를\n"
	.string "문에 적었다!\p"
	.string "“미궁대왕님 멋있어”\p"
	.string "...... ...... ......\p"
	.string "문의 자물쇠가 풀렸다!$"
	@ §あは あいことばをｎ
	@ とびらに かきつけた!ｐ
	@ 「カラクリだいおう さま かっこいい」ｐ
	@ …… …… ……ｐ
	@ かぎの はずれる おとがした!

Route110_TrickHousePuzzle4_Text_CoraIntro: @ 826C92D
	.string "이런 걸 생각해야 한다니 귀찮아!\n"
	.string "난 승부만 하고 싶은데-!$"
	@ こういうの かんがえるのって めんどう!ｎ
	@ わたしは しょうぶだけ したいのに-!

Route110_TrickHousePuzzle4_Text_CoraDefeat: @ 826C96E
	.string "져버렸지만 역시\n"
	.string "승부가 제일 즐거워!$"
	@ まけちゃった けど やっぱりｎ
	@ しょうぶが いちばん たのしい!

Route110_TrickHousePuzzle4_Text_CoraPostBattle: @ 826C9A2
	.string "트레이너가 있을 것 같은 곳이라면\n"
	.string "어디든 가고 싶어져!$"
	@ トレ-ナ-が いそうな ところはｎ
	@ どこにでも いきたく なるわよね!

Route110_TrickHousePuzzle4_Text_YujiIntro: @ 826C9E4
	.string "이 정도 바위는\n"
	.string "손가락 하나로도 껌이라고!$"
	@ このくらいの いわはｎ
	@ ゆび いっぽんで らくしょう だぜ!

Route110_TrickHousePuzzle4_Text_YujiDefeat: @ 826CA20
	.string "바위를 밀어도\n"
	.string "퍼즐이 풀리지 않아...$"
	@ いわが おせてもｎ
	@ パズルが とけない……

Route110_TrickHousePuzzle4_Text_YujiPostBattle: @ 826CA53
	.string "힘만 세다고 되는 게 아니군...\n"
	.string "머리를 써야 하는 건가$"
	@ ちからが つよいだけじゃ ダメだね……ｎ
	@ アタマ つかわないと

Route110_TrickHousePuzzle4_Text_PaulaIntro: @ 826CA9C
	.string "미궁의 대저택도 점점\n"
	.string "어려워지기 시작했네!$"
	@ カラクリやしきも だんだんｎ
	@ むずかしく なってきたわね!

Route110_TrickHousePuzzle4_Text_PaulaDefeat: @ 826CACB
	.string "아앗!$"
	@ ああっ!

Route110_TrickHousePuzzle4_Text_PaulaPostBattle: @ 826CAD1
	.string "마지막까지 남을\n"
	.string "사람이 있을지 모르겠네?$"
	@ さいごまで いったｎ
	@ ひとって いるのかしらね?

