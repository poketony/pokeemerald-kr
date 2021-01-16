Route110_TrickHousePuzzle6_MapScripts:: @ 826DDA7
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHousePuzzle6_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route110_TrickHousePuzzle6_OnWarp
	.byte 0

Route110_TrickHousePuzzle6_OnTransition: @ 826DDB2
	special RotatingGate_InitPuzzle
	end

Route110_TrickHousePuzzle6_OnWarp: @ 826DDB6
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, Route110_TrickHousePuzzle6_EventScript_InitPuzzle
	.2byte 0

Route110_TrickHousePuzzle6_EventScript_InitPuzzle:: @ 826DDC0
	special RotatingGate_InitPuzzleAndGraphics
	end

Route110_TrickHousePuzzle6_EventScript_Scroll:: @ 826DDC4
	lockall
	compare VAR_TRICK_HOUSE_PUZZLE_6_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle6_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle6_EventScript_FoundScroll:: @ 826DDD6
	setvar VAR_TRICK_HOUSE_PUZZLE_6_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle6_EventScript_Sophia:: @ 826DDE1
	trainerbattle_single TRAINER_SOPHIA, Route110_TrickHousePuzzle6_Text_SophiaIntro, Route110_TrickHousePuzzle6_Text_SophiaDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SophiaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Benny:: @ 826DDF8
	trainerbattle_single TRAINER_BENNY, Route110_TrickHousePuzzle6_Text_BennyIntro, Route110_TrickHousePuzzle6_Text_BennyDefeat
	msgbox Route110_TrickHousePuzzle6_Text_BennyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Sebastian:: @ 826DE0F
	trainerbattle_single TRAINER_SEBASTIAN, Route110_TrickHousePuzzle6_Text_SebastianIntro, Route110_TrickHousePuzzle6_Text_SebastianDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SebastianPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_Text_WroteSecretCodeLockOpened: @ 826DE26
	.string "{PLAYER}{K_EUNNEUN} 암호를\n"
	.string "문에 적었다!\p"
	.string "“미궁대왕님 소중해”\p"
	.string "...... ...... ......\p"
	.string "문의 자물쇠가 풀렸다!$"

Route110_TrickHousePuzzle6_Text_SophiaIntro: @ 826DE93
	.string "최근에 이상한 저택이 생겼다는\n"
	.string "소문을 듣고 조사하러 왔어!$"

Route110_TrickHousePuzzle6_Text_SophiaDefeat: @ 826DED2
	.string "강한 트레이너를 발견했다!$"

Route110_TrickHousePuzzle6_Text_SophiaPostBattle: @ 826DEF3
	.string "저택을 조사하고 있는데 재미있어서\n"
	.string "몇 번이고 도전하고 있어!$"

Route110_TrickHousePuzzle6_Text_BennyIntro: @ 826DF55
	.string "나의 새포켓몬으로\n"
	.string "벽을 뛰어넘어 버릴까...?$"

Route110_TrickHousePuzzle6_Text_BennyDefeat: @ 826DF8D
	.string "와앗 져버렸다!$"

Route110_TrickHousePuzzle6_Text_BennyPostBattle: @ 826DFA0
	.string "데헤헤... 잔꾀를 부려서\n"
	.string "져버린 건가...$"

Route110_TrickHousePuzzle6_Text_SebastianIntro: @ 826DFD7
	.string "회전하는 문 때문에\n"
	.string "눈이 돌아간다...$"

Route110_TrickHousePuzzle6_Text_SebastianDefeat: @ 826E004
	.string "빙글빙글 빙글빙글\n"
	.string "난 더 이상은 못한다...$"

Route110_TrickHousePuzzle6_Text_SebastianPostBattle: @ 826E048
	.string "너는 전혀 아무렇지도 않은 모양이네\n"
	.string "그게 아니면 무표정이란 거니?$"

