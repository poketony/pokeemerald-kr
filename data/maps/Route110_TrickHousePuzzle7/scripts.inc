Route110_TrickHousePuzzle7_MapScripts:: @ 826E091
	map_script MAP_SCRIPT_ON_RESUME, Route110_TrickHousePuzzle7_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHousePuzzle7_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route110_TrickHousePuzzle7_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route110_TrickHousePuzzle7_OnFrame
	.byte 0

@ Puzzle Room 7 in RSE uses whatever puzzle Mossdeep Gym uses
@ Because Mossdeep Gym was redesigned for Emerald, theres a good deal of leftover script from the old R/S puzzle

Route110_TrickHousePuzzle7_OnResume: @ 826E0A6
	call Route110_TrickHousePuzzle7_EventScript_UpdateSwitchMetatiles
	end

Route110_TrickHousePuzzle7_EventScript_UpdateSwitchMetatiles:: @ 826E0AC
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1, Route110_TrickHousePuzzle7_EventScript_SetSwitch1MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2, Route110_TrickHousePuzzle7_EventScript_SetSwitch2MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3, Route110_TrickHousePuzzle7_EventScript_SetSwitch3MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4, Route110_TrickHousePuzzle7_EventScript_SetSwitch4MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5, Route110_TrickHousePuzzle7_EventScript_SetSwitch5MetatilesOn
	return

@ Leftover from R/S, none of the below metatile scripts are ever called
Route110_TrickHousePuzzle7_EventScript_SetSwitch1MetatilesOn:: @ 826E0DA
	setmetatile 13, 17, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Up, 0
	setmetatile 12, 16, METATILE_TrickHousePuzzle_Lever_On, 1
	return

Route110_TrickHousePuzzle7_EventScript_SetSwitch2MetatilesOn:: @ 826E0ED
	setmetatile 12, 13, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Up, 0
	setmetatile 12, 11, METATILE_TrickHousePuzzle_Lever_On, 1
	return

Route110_TrickHousePuzzle7_EventScript_SetSwitch3MetatilesOn:: @ 826E100
	setmetatile 7, 12, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Up, 0
	setmetatile 5, 10, METATILE_TrickHousePuzzle_Lever_On, 1
	return

Route110_TrickHousePuzzle7_EventScript_SetSwitch4MetatilesOn:: @ 826E113
	setmetatile 6, 6, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Right_Alt, 0
	setmetatile 4, 4, METATILE_TrickHousePuzzle_Lever_On, 1
	return

Route110_TrickHousePuzzle7_EventScript_SetSwitch5MetatilesOn:: @ 826E126
	setmetatile 8, 4, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Left, 0
	setmetatile 7, 5, METATILE_TrickHousePuzzle_Lever_On, 1
	return

Route110_TrickHousePuzzle7_EventScript_SetSwitch1MetatilesOff:: @ 826E139
	setmetatile 13, 17, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Down, 0
	setmetatile 12, 16, METATILE_TrickHousePuzzle_Lever_Off, 1
	return

Route110_TrickHousePuzzle7_EventScript_SetSwitch2MetatilesOff:: @ 826E14C
	setmetatile 12, 13, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Left, 0
	setmetatile 12, 11, METATILE_TrickHousePuzzle_Lever_Off, 1
	return

Route110_TrickHousePuzzle7_EventScript_SetSwitch3MetatilesOff:: @ 826E15F
	setmetatile 7, 12, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Down, 0
	setmetatile 5, 10, METATILE_TrickHousePuzzle_Lever_Off, 1
	return

Route110_TrickHousePuzzle7_EventScript_SetSwitch4MetatilesOff:: @ 826E172
	setmetatile 6, 6, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Left_Alt, 0
	setmetatile 4, 4, METATILE_TrickHousePuzzle_Lever_Off, 1
	return

Route110_TrickHousePuzzle7_EventScript_SetSwitch5MetatilesOff:: @ 826E185
	setmetatile 8, 4, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Right, 0
	setmetatile 7, 5, METATILE_TrickHousePuzzle_Lever_Off, 1
	return

Route110_TrickHousePuzzle7_OnTransition: @ 826E198
	compare VAR_TRICK_HOUSE_PUZZLE_7_STATE_2, 1
	goto_if_eq Route110_TrickHousePuzzle7_EventScript_TeleportedTransition
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5
	end

Route110_TrickHousePuzzle7_EventScript_TeleportedTransition:: @ 826E1B3
	end

Route110_TrickHousePuzzle7_OnLoad: @ 826E1B4
	compare VAR_TRICK_HOUSE_PUZZLE_7_STATE_2, 1
	call_if_eq Route110_TrickHousePuzzle7_EventScript_UpdateSwitchMetatiles
	end

Route110_TrickHousePuzzle7_OnFrame: @ 826E1C0
	map_script_2 VAR_TRICK_HOUSE_PUZZLE_7_STATE_2, 1, Route110_TrickHousePuzzle7_EventScript_ClearState2
	.2byte 0

Route110_TrickHousePuzzle7_EventScript_ClearState2:: @ 826E1CA
	setvar VAR_TRICK_HOUSE_PUZZLE_7_STATE_2, 0
	end

Route110_TrickHousePuzzle7_EventScript_Scroll:: @ 826E1D0
	lockall
	compare VAR_TRICK_HOUSE_PUZZLE_7_STATE, 0
	goto_if_eq Route110_TrickHousePuzzle7_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle7_EventScript_FoundScroll:: @ 826E1E2
	setvar VAR_TRICK_HOUSE_PUZZLE_7_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

@ Unused, leftover from R/S
Route110_TrickHousePuzzle7_EventScript_TeleportPad:: @ 826E1ED
	lockall
	setvar VAR_TRICK_HOUSE_PUZZLE_7_STATE_2, 1
	warpteleport MAP_ROUTE110_TRICK_HOUSE_PUZZLE7, 255, 3, 19
	waitstate
	releaseall
	end

@ All the below switch scripts are unused leftover from R/S
Route110_TrickHousePuzzle7_EventScript_Switch1:: @ 826E1FE
	lockall
	delay 32
	call_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1, Route110_TrickHousePuzzle7_EventScript_SetSwitch1MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1, Route110_TrickHousePuzzle7_EventScript_SetSwitch1MetatilesOff
	special DrawWholeMapView
	playse SE_CLICK
	goto_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1, Route110_TrickHousePuzzle7_EventScript_SetSwitch1On
	goto_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1, Route110_TrickHousePuzzle7_EventScript_SetSwitch1Off
	end

Route110_TrickHousePuzzle7_EventScript_Switch2:: @ 826E22D
	lockall
	delay 32
	call_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2, Route110_TrickHousePuzzle7_EventScript_SetSwitch2MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2, Route110_TrickHousePuzzle7_EventScript_SetSwitch2MetatilesOff
	special DrawWholeMapView
	playse SE_CLICK
	goto_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2, Route110_TrickHousePuzzle7_EventScript_SetSwitch2On
	goto_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2, Route110_TrickHousePuzzle7_EventScript_SetSwitch2Off
	end

Route110_TrickHousePuzzle7_EventScript_Switch3:: @ 826E25C
	lockall
	delay 32
	call_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3, Route110_TrickHousePuzzle7_EventScript_SetSwitch3MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3, Route110_TrickHousePuzzle7_EventScript_SetSwitch3MetatilesOff
	special DrawWholeMapView
	playse SE_CLICK
	goto_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3, Route110_TrickHousePuzzle7_EventScript_SetSwitch3On
	goto_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3, Route110_TrickHousePuzzle7_EventScript_SetSwitch3Off
	end

Route110_TrickHousePuzzle7_EventScript_Switch4:: @ 826E28B
	lockall
	delay 32
	call_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4, Route110_TrickHousePuzzle7_EventScript_SetSwitch4MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4, Route110_TrickHousePuzzle7_EventScript_SetSwitch4MetatilesOff
	special DrawWholeMapView
	playse SE_CLICK
	goto_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4, Route110_TrickHousePuzzle7_EventScript_SetSwitch4On
	goto_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4, Route110_TrickHousePuzzle7_EventScript_SetSwitch4Off
	end

Route110_TrickHousePuzzle7_EventScript_Switch5:: @ 826E2BA
	lockall
	delay 32
	call_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5, Route110_TrickHousePuzzle7_EventScript_SetSwitch5MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5, Route110_TrickHousePuzzle7_EventScript_SetSwitch5MetatilesOff
	special DrawWholeMapView
	playse SE_CLICK
	goto_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5, Route110_TrickHousePuzzle7_EventScript_SetSwitch5On
	goto_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5, Route110_TrickHousePuzzle7_EventScript_SetSwitch5Off
	end

@ All the below switch scripts are unused leftover from R/S
Route110_TrickHousePuzzle7_EventScript_SetSwitch1On:: @ 826E2E9
	setflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1
	releaseall
	end

Route110_TrickHousePuzzle7_EventScript_SetSwitch1Off:: @ 826E2EE
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1
	releaseall
	end

Route110_TrickHousePuzzle7_EventScript_SetSwitch2On:: @ 826E2F3
	setflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2
	releaseall
	end

Route110_TrickHousePuzzle7_EventScript_SetSwitch2Off:: @ 826E2F8
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2
	releaseall
	end

Route110_TrickHousePuzzle7_EventScript_SetSwitch3On:: @ 826E2FD
	setflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3
	releaseall
	end

Route110_TrickHousePuzzle7_EventScript_SetSwitch3Off:: @ 826E302
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3
	releaseall
	end

Route110_TrickHousePuzzle7_EventScript_SetSwitch4On:: @ 826E307
	setflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4
	releaseall
	end

Route110_TrickHousePuzzle7_EventScript_SetSwitch4Off:: @ 826E30C
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4
	releaseall
	end

Route110_TrickHousePuzzle7_EventScript_SetSwitch5On:: @ 826E311
	setflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5
	releaseall
	end

Route110_TrickHousePuzzle7_EventScript_SetSwitch5Off:: @ 826E316
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5
	releaseall
	end

@ From here is where the new, actually used puzzle scripts begin
Route110_TrickHousePuzzle7_EventScript_YellowButton:: @ 826E31B
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle TRUE
	moverotatingtileobjects 0
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

Route110_TrickHousePuzzle7_EventScript_BlueButton:: @ 826E331
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle TRUE
	moverotatingtileobjects 1
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

Route110_TrickHousePuzzle7_EventScript_GreenButton:: @ 826E347
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle TRUE
	moverotatingtileobjects 2
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

Route110_TrickHousePuzzle7_EventScript_PurpleButton:: @ 826E35D
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle TRUE
	moverotatingtileobjects 3
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

@ Unused
Route110_TrickHousePuzzle7_EventScript_RedButton:: @ 826E373
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle TRUE
	moverotatingtileobjects 4
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

Route110_TrickHousePuzzle7_EventScript_Joshua:: @ 826E389
	trainerbattle_single TRAINER_JOSHUA, Route110_TrickHousePuzzle7_Text_JoshuaIntro, Route110_TrickHousePuzzle7_Text_JoshuaDefeat
	msgbox Route110_TrickHousePuzzle7_Text_JoshuaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle7_EventScript_Patricia:: @ 826E3A0
	trainerbattle_single TRAINER_PATRICIA, Route110_TrickHousePuzzle7_Text_PatriciaIntro, Route110_TrickHousePuzzle7_Text_PatriciaDefeat
	msgbox Route110_TrickHousePuzzle7_Text_PatriciaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle7_EventScript_Alexis:: @ 826E3B7
	trainerbattle_single TRAINER_ALEXIS, Route110_TrickHousePuzzle7_Text_AlexisIntro, Route110_TrickHousePuzzle7_Text_AlexisDefeat
	msgbox Route110_TrickHousePuzzle7_Text_AlexisPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle7_EventScript_Mariela:: @ 826E3CE
	trainerbattle_single TRAINER_MARIELA, Route110_TrickHousePuzzle7_Text_MarielaIntro, Route110_TrickHousePuzzle7_Text_MarielaDefeat
	msgbox Route110_TrickHousePuzzle7_Text_MarielaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle7_EventScript_Alvaro:: @ 826E3E5
	trainerbattle_single TRAINER_ALVARO, Route110_TrickHousePuzzle7_Text_AlvaroIntro, Route110_TrickHousePuzzle7_Text_AlvaroDefeat
	msgbox Route110_TrickHousePuzzle7_Text_AlvaroPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle7_EventScript_Everett:: @ 826E3FC
	trainerbattle_single TRAINER_EVERETT, Route110_TrickHousePuzzle7_Text_EverettIntro, Route110_TrickHousePuzzle7_Text_EverettDefeat
	msgbox Route110_TrickHousePuzzle7_Text_EverettPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle7_EventScript_WroteSecretCodeLockOpened:: @ 826E413
	.string "{PLAYER}{K_EUNNEUN} 암호를\n"
	.string "문에 적었다!\p"
	.string "“미궁대왕님 껴안고 싶어”\p"
	.string "...... ...... ......\p"
	.string "문의 자물쇠가 풀렸다!$"
	@ §あは あいことばをｎ
	@ とびらに かきつけた!ｐ
	@ 「カラクリだいおう さま だきしめたい」ｐ
	@ …… …… ……ｐ
	@ かぎの はずれる おとがした!

Route110_TrickHousePuzzle7_Text_JoshuaIntro: @ 826E481
	.string "항상 미궁대왕은 팟 하고\n"
	.string "사라지던데 어떻게 하는 걸까?$"
	@ いつも カラクリだいおうは パッとｎ
	@ きえちゃうけど どう やってるんだろ?

Route110_TrickHousePuzzle7_Text_JoshuaDefeat: @ 826E4C1
	.string "히엑-\n"
	.string "왜 그렇게 강한 거야?$"
	@ ひえ-ｎ
	@ なんで そんなに つよいの?

Route110_TrickHousePuzzle7_Text_JoshuaPostBattle: @ 826E4F4
	.string "나도 자유자재로\n"
	.string "사라졌다가 나타났다가 하고 싶다$"
	@ ぼくも じゆう じざいにｎ
	@ きえたり あらわれたり してみたいな

Route110_TrickHousePuzzle7_Text_PatriciaIntro: @ 826E531
	.string "같은 곳을 계속해서\n"
	.string "몇 번이고 맴돌고 있어서 불길해...$"
	@ おなじところを つづけてｎ
	@ なんども まわると ふきつなのよ……

Route110_TrickHousePuzzle7_Text_PatriciaDefeat: @ 826E564
	.string "졌다...!\n"
	.string "재수가 안 좋아...!$"
	@ まけた……!ｎ
	@ えんぎが わるいわ……!

Route110_TrickHousePuzzle7_Text_PatriciaPostBattle: @ 826E57F
	.string "나는 벌써 10번 이상\n"
	.string "맴돌고 말았어... 불길한데...$"
	@ わたしは もう 10かい いじょうｎ
	@ まわってしまった…… ふきつだわ……

Route110_TrickHousePuzzle7_Text_AlexisIntro: @ 826E5C0
	.string "이긴 쪽이 먼저 이 장치를\n"
	.string "빠져나갈 거 같은 예감이 들어!$"
	@ かった ほうが さきに このしかけをｎ
	@ ぬけられる よかんが するわ!

Route110_TrickHousePuzzle7_Text_AlexisDefeat: @ 826E604
	.string "어라!\n"
	.string "자 그럼 먼저 나가!$"
	@ あら!ｎ
	@ じゃあ おさきに どうぞ!

Route110_TrickHousePuzzle7_Text_AlexisPostBattle: @ 826E61E
	.string "너는 미궁의 대저택의 장치를\n"
	.string "전부 풀 거 같은 예감이 들어!$"
	@ あなたは カラクリやしきの しかけをｎ
	@ すべて とく って よかんが するわ!

Route110_TrickHousePuzzle7_Text_MarielaIntro: @ 826E66B
	.string "으흐흐흐 왔구나\n"
	.string "자 승부하자!$"
	@ んっふっふっふ きたわねっｎ
	@ さあ しょうぶよ!

Route110_TrickHousePuzzle7_Text_MarielaDefeat: @ 826E69C
	.string "간단하게 져버리다니!$"
	@ あっさり かってくれちゃって!

Route110_TrickHousePuzzle7_Text_MarielaPostBattle: @ 826E6BC
	.string "흥 딱히 분하진 않아!\n"
	.string "정말로!$"
	@ ふん べつに くやしく ないから!ｎ
	@ わたし!

Route110_TrickHousePuzzle7_Text_AlvaroIntro: @ 826E6DA
	.string "네가 점점\n"
	.string "다가오는 걸 보고 있었어!$"
	@ きみが どんどんｎ
	@ ちかづいて くるのを みていたぜ!

Route110_TrickHousePuzzle7_Text_AlvaroDefeat: @ 826E700
	.string "이런 결과는\n"
	.string "보이지 않았는데$"
	@ こんな けっかはｎ
	@ みえなかった

Route110_TrickHousePuzzle7_Text_AlvaroPostBattle: @ 826E722
	.string "뭐 이런 곳에 왔으니까\n"
	.string "별난 사람끼리 서로 잘해보자고!$"
	@ ま こんな ところで あったんだｎ
	@ ものずき どうし おたがい がんばろうぜ!

Route110_TrickHousePuzzle7_Text_EverettIntro: @ 826E78D
	.string "조 좁네...\n"
	.string "여기...$"
	@ せ せまいな……ｎ
	@ ここは……

Route110_TrickHousePuzzle7_Text_EverettDefeat: @ 826E7AB
	.string "오오 강해 강해$"
	@ おお つよいつよい

Route110_TrickHousePuzzle7_Text_EverettPostBattle: @ 826E7C4
	.string "만약 이긴다면 바꿔달라고\n"
	.string "할 생각이었는데$"
	@ もし かったら いれかわって やれとｎ
	@ おもって いたんだけどね

