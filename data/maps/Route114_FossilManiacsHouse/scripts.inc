Route114_FossilManiacsHouse_MapScripts:: @ 822AD30
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsHouse_OnTransition
	.byte 0

Route114_FossilManiacsHouse_OnTransition: @ 822AD36
	setflag FLAG_LANDMARK_FOSSIL_MANIACS_HOUSE
	end

Route114_FossilManiacsHouse_EventScript_FossilManiacsBrother:: @ 822AD3A
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM28, Route114_FossilManiacsHouse_EventScript_ReceivedDig
	msgbox Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother, MSGBOX_DEFAULT
	giveitem ITEM_TM28
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM28
	release
	end

Route114_FossilManiacsHouse_EventScript_ReceivedDig:: @ 822AD69
	msgbox Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsHouse_EventScript_RockDisplay:: @ 822AD73
	msgbox Route114_FossilManiacsHouse_Text_RocksFillDisplayCase, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_EventScript_Bookshelf:: @ 822AD7C
	msgbox Route114_FossilManiacsHouse_Text_CrammedWithBooks, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother: @ 822AD85
	.string "우리 형아는 화석마니아...\n"
	.string "화석을 좋아하는 나이스 가이지...\p"
	.string "참고로 구멍을 파는 것도 좋아해서...\n"
	.string "이 구멍도 자기가 직접 판 거야...\p"
	.string "이걸 줄 테니까...\n"
	.string "너도 우리 형아처럼\l"
	.string "구멍을 파봐...$"

Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance: @ 822AE48
	.string "참고로 포켓몬이 구멍파기를 쓰면\n"
	.string "동굴 입구까지\l"
	.string "단숨에 돌아갈 수 있어...$"

Route114_FossilManiacsHouse_Text_RocksFillDisplayCase: @ 822AE92
	.string "케이스 안에 독특한 모양의\n"
	.string "화석이 소중하게 장식되어 있다...$"

Route114_FossilManiacsHouse_Text_CrammedWithBooks: @ 822AEC2
	.string "“지층이 생기기까지”\n"
	.string "“비가 내려 땅이 굳다”\l"
	.string "“돌과 흙과 암석과”\p"
	.string "많은 책이 나열되어 있다!$"

