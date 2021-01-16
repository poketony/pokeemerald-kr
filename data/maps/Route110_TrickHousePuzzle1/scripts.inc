Route110_TrickHousePuzzle1_MapScripts:: @ 826B90F
	map_script MAP_SCRIPT_ON_LOAD, Route110_TrickHousePuzzle1_OnLoad
	.byte 0

Route110_TrickHousePuzzle1_OnLoad: @ 826B915
	compare VAR_TRICK_HOUSE_PUZZLE_1_STATE, 2
	goto_if_eq Route110_TrickHousePuzzle1_EventScript_OpenDoor
	end

Route110_TrickHousePuzzle1_EventScript_OpenDoor:: @ 826B921
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, 0
	end

Route110_TrickHousePuzzle1_EventScript_Scroll:: @ 826B92B
	lockall
	compare VAR_TRICK_HOUSE_PUZZLE_1_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle1_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle1_EventScript_FoundScroll:: @ 826B93D
	setvar VAR_TRICK_HOUSE_PUZZLE_1_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle1_EventScript_Sally:: @ 826B948
	trainerbattle_single TRAINER_SALLY, Route110_TrickHousePuzzle1_Text_SallyIntro, Route110_TrickHousePuzzle1_Text_SallyDefeat
	msgbox Route110_TrickHousePuzzle1_Text_SallyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_EventScript_Eddie:: @ 826B95F
	trainerbattle_single TRAINER_EDDIE, Route110_TrickHousePuzzle1_Text_EddieIntro, Route110_TrickHousePuzzle1_Text_EddieDefeat
	msgbox Route110_TrickHousePuzzle1_Text_EddiePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_EventScript_Robin:: @ 826B976
	trainerbattle_single TRAINER_ROBIN, Route110_TrickHousePuzzle1_Text_RobinIntro, Route110_TrickHousePuzzle1_Text_RobinDefeat
	msgbox Route110_TrickHousePuzzle1_Text_RobinPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_Text_WroteSecretCodeLockOpened:: @ 826B98D
	.string "{PLAYER}{K_EUNNEUN} 암호를\n"
	.string "문에 적었다!\p"
	.string "“미궁대왕님 짱”\p"
	.string "...... ...... ......\p"
	.string "문의 자물쇠가 풀렸다!$"

Route110_TrickHousePuzzle1_Text_SallyIntro: @ 826B9FB
	.string "방금 막 배우게 한 풀베기로\n"
	.string "자르고 자르고 또 자를 거야!$"

Route110_TrickHousePuzzle1_Text_SallyDefeat: @ 826BA3F
	.string "진짜 실력을 몽땅 발휘하지 말아줘-!$"

Route110_TrickHousePuzzle1_Text_SallyPostBattle: @ 826BA57
	.string "자르고 잘라도 질리지가 않아!$"

Route110_TrickHousePuzzle1_Text_EddieIntro: @ 826BA82
	.string "길을 헤매다가\n"
	.string "이상한 저택에 들어와 버렸다...$"

Route110_TrickHousePuzzle1_Text_EddieDefeat: @ 826BAB0
	.string "게다가 져버렸다...$"

Route110_TrickHousePuzzle1_Text_EddiePostBattle: @ 826BAC3
	.string "심지어 길도 잃었다...\n"
	.string "나갈 수가 없어...$"

Route110_TrickHousePuzzle1_Text_RobinIntro: @ 826BB10
	.string "미궁대왕이란 사람은\n"
	.string "도대체 누굴까?$"

Route110_TrickHousePuzzle1_Text_RobinDefeat: @ 826BB2E
	.string "미궁대왕에 정신이 팔려 있는 동안\n"
	.string "져버렸어!$"

Route110_TrickHousePuzzle1_Text_RobinPostBattle: @ 826BB52
	.string "강하다!\n"
	.string "넌 또 정체가 뭐니?$"

