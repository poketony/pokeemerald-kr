.set LOCALID_MOVE_DELETER, 1

LilycoveCity_MoveDeletersHouse_MapScripts:: @ 821EA0A
	.byte 0

LilycoveCity_MoveDeletersHouse_EventScript_MoveDeleter:: @ 821EA0B
	lockall
	applymovement LOCALID_MOVE_DELETER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_MoveDeletersHouse_Text_ICanMakeMonForgetMove, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, LilycoveCity_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget
	case NO, LilycoveCity_MoveDeletersHouse_EventScript_ComeAgain
	releaseall
	end

LilycoveCity_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget:: @ 821EA3B
	msgbox LilycoveCity_MoveDeletersHouse_Text_WhichMonShouldForget, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_eq LilycoveCity_MoveDeletersHouse_EventScript_ComeAgain
	special IsSelectedMonEgg
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_MoveDeletersHouse_EventScript_EggCantForgetMoves
	special GetNumMovesSelectedMonHas
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_MoveDeletersHouse_EventScript_MonOnlyKnowsOneMove
	msgbox LilycoveCity_MoveDeletersHouse_Text_WhichMoveShouldBeForgotten, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special MoveDeleterChooseMoveToForget
	fadescreen FADE_FROM_BLACK
	compare VAR_0x8005, MAX_MON_MOVES
	goto_if_eq LilycoveCity_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget
	special BufferMoveDeleterNicknameAndMove
	msgbox LilycoveCity_MoveDeletersHouse_Text_MonsMoveShouldBeForgotten, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, LilycoveCity_MoveDeletersHouse_EventScript_TryForgetMove
	case NO, LilycoveCity_MoveDeletersHouse_EventScript_ComeAgain
	releaseall
	end

LilycoveCity_MoveDeletersHouse_EventScript_TryForgetMove:: @ 821EAB0
	special IsLastMonThatKnowsSurf
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_MoveDeletersHouse_EventScript_LastMonWithSurf
	special MoveDeleterForgetMove
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	msgbox LilycoveCity_MoveDeletersHouse_Text_MonHasForgottenMove, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_MoveDeletersHouse_EventScript_MonOnlyKnowsOneMove:: @ 821EACF
	special BufferMoveDeleterNicknameAndMove
	msgbox LilycoveCity_MoveDeletersHouse_Text_MonOnlyKnowsOneMove, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_MoveDeletersHouse_EventScript_EggCantForgetMoves:: @ 821EADC
	msgbox LilycoveCity_MoveDeletersHouse_Text_EggCantForgetMoves, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_MoveDeletersHouse_EventScript_ComeAgain:: @ 821EAE6
	msgbox LilycoveCity_MoveDeletersHouse_Text_ComeAgain, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_MoveDeletersHouse_EventScript_LastMonWithSurf:: @ 821EAF0
	special BufferMoveDeleterNicknameAndMove
	msgbox LilycoveCity_MoveDeletersHouse_Text_CantForgetSurf, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_MoveDeletersHouse_Text_ICanMakeMonForgetMove: @ 821EAFD
	.string "그러니까...\n"
	.string "그렇지 나는 깜빡할아버지\p"
	.string "포켓몬의 기술을\n"
	.string "잊게 만들 수 있다네!\p"
	.string "기술을 잊게 할 텐가?$"
	// え-と……ｎ
	// そうじゃ わし わすれじいさんｐ
	// ポケモンの わざをｎ
	// わすれさせる ことが できるんじゃ!ｐ
	// わざを わすれ させるかね?

LilycoveCity_MoveDeletersHouse_Text_WhichMonShouldForget: @ 821EB65
	.string "어느 포켓몬으로 할 겐가?$"
	// どの ポケモンに するんじゃ?

LilycoveCity_MoveDeletersHouse_Text_WhichMoveShouldBeForgotten: @ 821EB89
	.string "어느 기술을\n"
	.string "잊게 할 겐가?$"
	// どの わざをｎ
	// わすれ させるんじゃ?

LilycoveCity_MoveDeletersHouse_Text_MonOnlyKnowsOneMove: @ 821EBA9
	.string "{STR_VAR_1}{K_EUNNEUN} 기술을 하나밖에\n"
	.string "배우지 않은 모양이다만...$"
	// §いは わざを 1つしかｎ
	// もってない ようじゃ……

LilycoveCity_MoveDeletersHouse_Text_MonsMoveShouldBeForgotten: @ 821EBDA
	.string "으음!\n"
	.string "{STR_VAR_1}의 {STR_VAR_2} 말이지?$"
	// むむ!ｎ
	// §いの §うじゃな?

LilycoveCity_MoveDeletersHouse_Text_MonHasForgottenMove: @ 821EC06
	.string "대성공이군!\p"
	.string "{STR_VAR_1}{K_EUNNEUN} {STR_VAR_2}{K_EULREUL}\n"
	.string "잊어버린 것 같구먼!$"
	// だいせいこう じゃ!ｐ
	// §いは §うをｎ
	// わすれた ようじゃ!

LilycoveCity_MoveDeletersHouse_Text_ComeAgain: @ 821EC3F
	.string "잊게 하고 싶은 기술이 있다면\n"
	.string "또 오게!$"
	// わすれさせたい わざが あったらｎ
	// また くるのじゃぞ!

LilycoveCity_MoveDeletersHouse_Text_EggCantForgetMoves: @ 821EC78
	.string "뭐야!? 알은\n"
	.string "배운 기술이 없는 모양인데...?$"
	// なぬ!? タマゴはｎ
	// わざを おぼえていない ようじゃが……?

LilycoveCity_MoveDeletersHouse_Text_CantForgetSurf: @ 821EC9C
	.string "으음!\p"
	.string "{STR_VAR_1}{K_EUNNEUN} 파도타기를\n"
	.string "잊고 싶지 않은 것 같구먼!$"
	// むむ!ｐ
	// {STR_VAR_1}は なみのりをｎ
	// わすれたくない ようじゃ!
