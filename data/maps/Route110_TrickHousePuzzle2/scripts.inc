Route110_TrickHousePuzzle2_MapScripts:: @ 826BB73
	map_script MAP_SCRIPT_ON_RESUME, Route110_TrickHousePuzzle2_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHousePuzzle2_OnTransition
	.byte 0

Route110_TrickHousePuzzle2_OnResume: @ 826BB7E
	compare VAR_TEMP_1, 1
	call_if_eq Route110_TrickHousePuzzle2_EventScript_PressButton1
	compare VAR_TEMP_2, 1
	call_if_eq Route110_TrickHousePuzzle2_EventScript_PressButton2
	compare VAR_TEMP_3, 1
	call_if_eq Route110_TrickHousePuzzle2_EventScript_PressButton3
	compare VAR_TEMP_4, 1
	call_if_eq Route110_TrickHousePuzzle2_EventScript_PressButton4
	end

Route110_TrickHousePuzzle2_OnTransition: @ 826BBAB
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_4, 0
	end

Route110_TrickHousePuzzle2_EventScript_Scroll:: @ 826BBC0
	lockall
	compare VAR_TRICK_HOUSE_PUZZLE_2_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle2_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle2_EventScript_FoundScroll:: @ 826BBD2
	setvar VAR_TRICK_HOUSE_PUZZLE_2_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle2_EventScript_Button1:: @ 826BBDD
	lockall
	setvar VAR_TEMP_1, 1
	playse SE_PIN
	call Route110_TrickHousePuzzle2_EventScript_PressButton1
	special DrawWholeMapView
	releaseall
	end

Route110_TrickHousePuzzle2_EventScript_Button2:: @ 826BBF0
	lockall
	setvar VAR_TEMP_2, 1
	playse SE_PIN
	call Route110_TrickHousePuzzle2_EventScript_PressButton2
	special DrawWholeMapView
	releaseall
	end

Route110_TrickHousePuzzle2_EventScript_Button3:: @ 826BC03
	lockall
	setvar VAR_TEMP_3, 1
	playse SE_PIN
	call Route110_TrickHousePuzzle2_EventScript_PressButton3
	special DrawWholeMapView
	releaseall
	end

Route110_TrickHousePuzzle2_EventScript_Button4:: @ 826BC16
	lockall
	setvar VAR_TEMP_4, 1
	playse SE_PIN
	call Route110_TrickHousePuzzle2_EventScript_PressButton4
	special DrawWholeMapView
	releaseall
	end

Route110_TrickHousePuzzle2_EventScript_PressButton1:: @ 826BC29
	setmetatile 11, 12, METATILE_TrickHousePuzzle_Button_Pressed, 0
	setmetatile 1, 13, METATILE_TrickHousePuzzle_Door_Shuttered, 0
	return

Route110_TrickHousePuzzle2_EventScript_PressButton2:: @ 826BC3C
	setmetatile 0, 4, METATILE_TrickHousePuzzle_Button_Pressed, 0
	setmetatile 5, 6, METATILE_TrickHousePuzzle_Door_Shuttered, 0
	return

Route110_TrickHousePuzzle2_EventScript_PressButton3:: @ 826BC4F
	setmetatile 14, 5, METATILE_TrickHousePuzzle_Button_Pressed, 0
	setmetatile 7, 15, METATILE_TrickHousePuzzle_Door_Shuttered, 0
	return

Route110_TrickHousePuzzle2_EventScript_PressButton4:: @ 826BC62
	setmetatile 7, 11, METATILE_TrickHousePuzzle_Button_Pressed, 0
	setmetatile 14, 12, METATILE_TrickHousePuzzle_Door_Shuttered, 0
	return

Route110_TrickHousePuzzle2_EventScript_Ted:: @ 826BC75
	trainerbattle_single TRAINER_TED, Route110_TrickHousePuzzle2_Text_TedIntro, Route110_TrickHousePuzzle2_Text_TedDefeat
	msgbox Route110_TrickHousePuzzle2_Text_TedPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle2_EventScript_Paul:: @ 826BC8C
	trainerbattle_single TRAINER_PAUL, Route110_TrickHousePuzzle2_Text_PaulIntro, Route110_TrickHousePuzzle2_Text_PaulDefeat
	msgbox Route110_TrickHousePuzzle2_Text_PaulPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle2_EventScript_Georgia:: @ 826BCA3
	trainerbattle_single TRAINER_GEORGIA, Route110_TrickHousePuzzle2_Text_GeorgiaIntro, Route110_TrickHousePuzzle2_Text_GeorgiaDefeat
	msgbox Route110_TrickHousePuzzle2_Text_GeorgiaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle2_Text_WroteSecretCodeLockOpened: @ 826BCBA
	.string "{PLAYER}{K_EUNNEUN} 암호를\n"
	.string "문에 적었다!\p"
	.string "“미궁대왕님 똑똑해”\p"
	.string "...... ...... ......\p"
	.string "문의 자물쇠가 풀렸다!$"
	@ §あは あいことばをｎ
	@ とびらに かきつけた!ｐ
	@ 「カラクリだいおう さま かしこい」ｐ
	@ …… …… ……ｐ
	@ かぎの はずれる おとがした!

Route110_TrickHousePuzzle2_Text_TedIntro: @ 826BD25
	.string "어느 스위치로\n"
	.string "어느 구멍이 닫히는 거지?$"
	@ どの スイッチでｎ
	@ どの あなが ふさがるんだ?

Route110_TrickHousePuzzle2_Text_TedDefeat: @ 826BD45
	.string "승부했더니\n"
	.string "더 알 수 없게 됐어!$"
	@ しょうぶ してたらｎ
	@ よけい わかんなくなった!

Route110_TrickHousePuzzle2_Text_TedPostBattle: @ 826BD70
	.string "너 나 대신에\n"
	.string "스위치 전부 눌러주라!$"
	@ きみ ぼくの かわりにｎ
	@ スイッチ ぜんぶ おしてきてよ!

Route110_TrickHousePuzzle2_Text_PaulIntro: @ 826BD9E
	.string "오옷! 미궁의 대저택에서의\n"
	.string "2번째 챌린지구나!$"
	@ おっ! カラクリやしきｎ
	@ 2どめの チャレンジだね!

Route110_TrickHousePuzzle2_Text_PaulDefeat: @ 826BDCF
	.string "포켓몬 승부도\n"
	.string "잘하는 거야?$"
	@ ポケモンしょうぶもｎ
	@ そんなに つよいの?

Route110_TrickHousePuzzle2_Text_PaulPostBattle: @ 826BDEC
	.string "미궁대왕이 혼자서\n"
	.string "이 장치들을 만들었대!$"
	@ カラクリだいおうが ひとりでｎ
	@ この しかけを つくってるんだって!

Route110_TrickHousePuzzle2_Text_GeorgiaIntro: @ 826BE31
	.string "언젠가 내 체육관을 만들고 싶어서\n"
	.string "이곳의 장치들을 연구하고 있어!$"
	@ いつか わたしの ジムを つくりたくてｎ
	@ しかけを けんきゅうしてるの!

Route110_TrickHousePuzzle2_Text_GeorgiaDefeat: @ 826BE77
	.string "포켓몬 승부는\n"
	.string "연구가 부족했어-!$"
	@ ポケモンしょうぶはｎ
	@ けんきゅう ぶそく だったわ-っ!

Route110_TrickHousePuzzle2_Text_GeorgiaPostBattle: @ 826BE97
	.string "너 강하구나...\n"
	.string "체육관 관장이 될 수 있을 거 같은데?$"
	@ あなた つよいのね…ｎ
	@ ジムリ-ダ-に なれるんじゃない?

