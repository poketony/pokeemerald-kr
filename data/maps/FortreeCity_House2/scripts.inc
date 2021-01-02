FortreeCity_House2_MapScripts:: @ 82177CA
	.byte 0

FortreeCity_House2_EventScript_HiddenPowerGiver:: @ 82177CB
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM10, FortreeCity_House2_EventScript_ExplainHiddenPower
	call_if_unset FLAG_MET_HIDDEN_POWER_GIVER, FortreeCity_House2_EventScript_Greeting
	msgbox FortreeCity_House2_Text_CoinInWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, 1
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, 1
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand2, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, 1
	switch VAR_RESULT
	case 0, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_YourHiddenPowerHasAwoken, MSGBOX_DEFAULT
	giveitem ITEM_TM10
	compare VAR_RESULT, 0
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM10
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_Greeting:: @ 8217862
	msgbox FortreeCity_House2_Text_HiddenPowersArousedByNature, MSGBOX_DEFAULT
	setflag FLAG_MET_HIDDEN_POWER_GIVER
	return

FortreeCity_House2_EventScript_ExplainHiddenPower:: @ 821786E
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_WrongGuess:: @ 8217878
	msgbox FortreeCity_House2_Text_YouGuessedWrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_Text_HiddenPowersArousedByNature: @ 8217882
	.string "사람도 포켓몬도\n"
	.string "자연 속에서 살아가는 것으로\l"
	.string "본연의 힘이 깨어난다...$"

FortreeCity_House2_Text_CoinInWhichHand: @ 82178D6
	.string "자네의 힘이 깨어 있는지\n"
	.string "확인해보도록 하지...\p"
	.string "어디 보자... 내 오른손과 왼손\n"
	.string "어느 쪽에 코인이 있는지\l"
	.string "직감으로 선택해봐$"

FortreeCity_House2_Text_CorrectTryAgainWhichHand: @ 821796A
	.string "오오! 정답이다!\p"
	.string "오른손과 왼손\n"
	.string "어느 쪽에 코인이 있는지\l"
	.string "직감으로 선택해봐$"

FortreeCity_House2_Text_CorrectTryAgainWhichHand2: @ 82179C9
	.string "오오! 정답이다!\p"
	.string "오른손과 왼손\n"
	.string "어느 쪽에 코인이 있는지\l"
	.string "직감으로 선택해봐$"

FortreeCity_House2_Text_YourHiddenPowerHasAwoken: @ 8217A28
	.string "오옷! 대단하군!\n"
	.string "자네의 힘은 깨어 있어!\p"
	.string "이것을 줄 테니\n"
	.string "자네의 포켓몬이 가진 힘을\l"
	.string "깨우도록 하게!$"

FortreeCity_House2_Text_ExplainHiddenPower: @ 8217A91
	.string "잠재파워는 포켓몬에 따라\n"
	.string "위력이 달라지는 기술이라네!$"

FortreeCity_House2_Text_YouGuessedWrong: @ 8217AC7
	.string "이런...\n"
	.string "꽝이라네...$"

