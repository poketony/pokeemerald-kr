SlateportCity_NameRatersHouse_MapScripts:: @ 8209AA4
	.byte 0

SlateportCity_NameRatersHouse_EventScript_NameRater:: @ 8209AA5
	lock
	faceplayer
	msgbox SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate
	compare VAR_RESULT, NO
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate:: @ 8209AC6
	msgbox SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_ne SlateportCity_NameRatersHouse_EventScript_RateMonNickname
	compare VAR_0x8004, 255
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_DeclineNameRate:: @ 8209AE9
	msgbox SlateportCity_NameRatersHouse_Text_DoVisitAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_RateMonNickname:: @ 8209AF3
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_CantRateEgg
	special BufferMonNickname
	special IsMonOTIDNotPlayers
	compare VAR_RESULT, TRUE
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	specialvar VAR_RESULT, MonOTNameNotPlayer
	special BufferMonNickname
	compare VAR_RESULT, TRUE
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	msgbox SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_ChangeNickname
	compare VAR_RESULT, NO
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_CantRateEgg:: @ 8209B46
	msgbox SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT:: @ 8209B50
	msgbox SlateportCity_NameRatersHouse_Text_MagnificentName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_ChangeNickname:: @ 8209B5A
	msgbox SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	compare VAR_RESULT, TRUE
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_NewNameDifferent
	msgbox SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_NewNameDifferent:: @ 8209B84
	msgbox SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname: @ 8209B8E
	.string "안녕 안녕!\n"
	.string "나는 이름 감정사\l"
	.string "이름으로 점을 보는 사람이지\p"
	.string "자! 자네 포켓몬의\n"
	.string "별명을 감정해 주겠네$"

SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname: @ 8209BFF
	.string "어떤 포켓몬의\n"
	.string "별명을 감정하겠나?$"

SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne: @ 8209C2B
	.string "음- {STR_VAR_1}{K_I}라...\p"
	.string "꽤 좋은 닉네임을 지었군\p"
	.string "그렇지만-\n"
	.string "내가 조금 더 좋은 이름을\l"
	.string "지어주고 싶은데, 어떤가?$"

SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe: @ 8209CA4
	.string "그래 그럼\n"
	.string "어떤 별명으로 해줄까?$"

SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName: @ 8209CD4
	.string "좋아 이제부터\n"
	.string "이 포켓몬은 {STR_VAR_1}{K_I}라네!\p"
	.string "전보다 좋은 이름이지 않은가\n"
	.string "잘됐군!$"

SlateportCity_NameRatersHouse_Text_DoVisitAgain: @ 8209D42
	.string "알았네\n"
	.string "그럼 또 오게나$"

SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior: @ 8209D5E
	.string "좋아 이제부터\n"
	.string "이 포켓몬은 {STR_VAR_1}{K_I}라네!\p"
	.string "전과 같아 보이지만\n"
	.string "이쪽이 당연히 더 좋다고!\l"
	.string "잘됐군!$"

SlateportCity_NameRatersHouse_Text_MagnificentName: @ 8209DF0
	.string "음- {STR_VAR_1}{K_I}라!\n"
	.string "정말 멋진 별명이군!\l"
	.string "흠잡을 데가 없어!\p"
	.string "앞으로도 {STR_VAR_1}{K_EULREUL}\n"
	.string "귀여워해 주게나!$"

SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg: @ 8209E74
	.string "이보게나...\n"
	.string "그것은 알이지 않은가!$"

