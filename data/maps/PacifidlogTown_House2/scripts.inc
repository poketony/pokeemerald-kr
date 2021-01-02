PacifidlogTown_House2_MapScripts:: @ 8203791
	.byte 0

PacifidlogTown_House2_EventScript_FanClubYoungerBrother:: @ 8203792
	lock
	faceplayer
	dotimebasedevents
	call PacifidlogTown_House2_EventScript_UpdateFanClubTMFlag
	goto_if_set FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK, PacifidlogTown_House2_EventScript_ComeBackInXDays
	call_if_set FLAG_MET_FANCLUB_YOUNGER_BROTHER, PacifidlogTown_House2_EventScript_MonAssessment
	call_if_unset FLAG_MET_FANCLUB_YOUNGER_BROTHER, PacifidlogTown_House2_EventScript_FirstMonAssessment
	setflag FLAG_MET_FANCLUB_YOUNGER_BROTHER
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	compare VAR_RESULT, 4
	goto_if_ge PacifidlogTown_House2_EventScript_GiveReturn
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	compare VAR_RESULT, 2
	goto_if_ge PacifidlogTown_House2_EventScript_PutInEffort
	goto PacifidlogTown_House2_EventScript_GiveFrustration
	end

PacifidlogTown_House2_EventScript_UpdateFanClubTMFlag:: @ 82037DE
	goto_if_unset FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK, Common_EventScript_NopReturn
	specialvar VAR_RESULT, GetDaysUntilPacifidlogTMAvailable
	compare VAR_RESULT, 0
	call_if_eq PacifidlogTown_House2_EventScript_ClearReceivedFanClubTM
	return

PacifidlogTown_House2_EventScript_MonAssessment:: @ 82037F8
	msgbox PacifidlogTown_House2_Text_AhYourPokemon, MSGBOX_DEFAULT
	return

PacifidlogTown_House2_EventScript_FirstMonAssessment:: @ 8203801
	msgbox PacifidlogTown_House2_Text_ChairmansYoungerBrotherOnVacation, MSGBOX_DEFAULT
	msgbox PacifidlogTown_House2_Text_AhYourPokemon, MSGBOX_DEFAULT
	return

PacifidlogTown_House2_EventScript_ClearReceivedFanClubTM:: @ 8203812
	clearflag FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK
	return

PacifidlogTown_House2_EventScript_GiveReturn:: @ 8203816
	msgbox PacifidlogTown_House2_Text_AdoringPokemonTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM27
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK
	special SetPacifidlogTMReceivedDay
	msgbox PacifidlogTown_House2_Text_ExplainReturnFrustration, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_PutInEffort:: @ 8203845
	msgbox PacifidlogTown_House2_Text_PutInSomeMoreEffort, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_GiveFrustration:: @ 820384F
	msgbox PacifidlogTown_House2_Text_ViciousPokemonTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM21
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK
	special SetPacifidlogTMReceivedDay
	msgbox PacifidlogTown_House2_Text_ExplainReturnFrustration, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_ComeBackInXDays:: @ 820387E
	specialvar VAR_RESULT, GetDaysUntilPacifidlogTMAvailable
	buffernumberstring 0, VAR_RESULT
	msgbox PacifidlogTown_House2_Text_GetGoodTMInXDays, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_HappyAzurill:: @ 8203891
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, 0
	msgbox PacifidlogTown_House2_Text_Rurii, MSGBOX_DEFAULT
	waitmoncry
	msgbox PacifidlogTown_House2_Text_VeryFriendlyWithTrainer, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_UnhappyAzurill:: @ 82038AC
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, 2
	msgbox PacifidlogTown_House2_Text_Rururi, MSGBOX_DEFAULT
	waitmoncry
	msgbox PacifidlogTown_House2_Text_DoesntLikeTrainerVeryMuch, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_Text_ChairmansYoungerBrotherOnVacation: @ 82038C7
	.string "엣헴!!\p"
	.string "내가 포켓몬애호가클럽에서\n"
	.string "제-일 높은 회장의...\p"
	.string "남동생입니다!\p"
	.string "뭐 여기에서 포켓몬과 같이\n"
	.string "바캉스를 즐기고 있답니다!$"

PacifidlogTown_House2_Text_AhYourPokemon: @ 820395B
	.string "오호!\n"
	.string "당신의 포켓몬...$"

PacifidlogTown_House2_Text_AdoringPokemonTakeThis: @ 820396D
	.string "굉장히 잘 따르고 있군요\p"
	.string "이런 귀여운 포켓몬에게는\n"
	.string "이 기술머신이 어떨까요?$"

PacifidlogTown_House2_Text_PutInSomeMoreEffort: @ 82039CE
	.string "흐음...\n"
	.string "나쁘지는 않지만 좋지도 않아...\p"
	.string "어버이 트레이너인 당신의\n"
	.string "노력이 필요하겠군요!$"

PacifidlogTown_House2_Text_ViciousPokemonTakeThis: @ 8203A2F
	.string "왠지 눈매가 사나운데요\p"
	.string "이런 무서운 포켓몬에게는\n"
	.string "이 기술머신이 어떨까요?$"

PacifidlogTown_House2_Text_ExplainReturnFrustration: @ 8203A85
	.string "포켓몬이 많이 따를수록\n"
	.string "은혜갚기의 위력도 높아진다\p"
	.string "별로 따르지 않으면\n"
	.string "화풀이의 위력이 높아진다고!$"

PacifidlogTown_House2_Text_GetGoodTMInXDays: @ 8203AF4
	.string "그래그래 앞으로 {STR_VAR_1}일 지나면\n"
	.string "좋은 기술머신이 손에 들어와!\p"
	.string "그때 다시 놀러오도록 해!\n"
	.string "네 포켓몬에게 맞는\l"
	.string "근사한 기술머신을 줄 테니까$"

PacifidlogTown_House2_Text_Rurii: @ 8203B8D
	.string "루리리: 루리-$"

PacifidlogTown_House2_Text_VeryFriendlyWithTrainer: @ 8203B9D
	.string "굉장히 따르고 있는 듯하다$"

PacifidlogTown_House2_Text_Rururi: @ 8203BCE
	.string "루리리: 루리리!!$"

PacifidlogTown_House2_Text_DoesntLikeTrainerVeryMuch: @ 8203BDF
	.string "별로 안 따르는 듯하다...$"

