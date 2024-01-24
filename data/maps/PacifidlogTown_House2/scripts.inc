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
	.string "제가 포켓몬애호가클럽에서\n"
	.string "제-일 높은 회장의...\p"
	.string "남동생입니다!\p"
	.string "뭐 여기에서 포켓몬과 같이\n"
	.string "바캉스를 즐기고 있지요!$"
	// ウォッホン!!ｐ
	// わしが ポケモン だいすきクラブでｎ
	// いちば-ん えらい かいちょうの……ｐ
	// おとうと ですぞ!ｐ
	// まあ ここで ポケモンと いっしょにｎ
	// バカンスを たのしんで おるのですな!

PacifidlogTown_House2_Text_AhYourPokemon: @ 820395B
	.string "호오!\n"
	.string "당신의 포켓몬...$"
	// ほう!ｎ
	// きみの ポケモン……

PacifidlogTown_House2_Text_AdoringPokemonTakeThis: @ 820396D
	.string "굉장히 잘 따르고 있군요\p"
	.string "이런 귀여운 포켓몬에게는\n"
	.string "이 기술머신이 어떨까요?$"
	// とっても なついて いますなあｐ
	// そんな かわいらしい ポケモンにはｎ
	// この わざマシン どうですかな?

PacifidlogTown_House2_Text_PutInSomeMoreEffort: @ 82039CE
	.string "흐음...\n"
	.string "나쁘지는 않지만 좋지도 않군요...\p"
	.string "어버이 트레이너인 당신의\n"
	.string "노력이 필요하겠습니다!$"
	// ふむう……ｎ
	// わるくは ないんだが よくもない……ｐ
	// おやの トレ-ナ-である きみのｎ
	// どりょくが ひつよう ですな!

PacifidlogTown_House2_Text_ViciousPokemonTakeThis: @ 8203A2F
	.string "왠지 눈매가 사나운데요\p"
	.string "이런 무서운 포켓몬에게는\n"
	.string "이 기술머신이 어떨까요?$"
	// なんだか めつきが わるいですのうｐ
	// そんな こわそうな ポケモンにはｎ
	// この わざマシン どうですかな?

PacifidlogTown_House2_Text_ExplainReturnFrustration: @ 8203A85
	.string "포켓몬이 많이 따를수록\n"
	.string "은혜갚기의 위력도 높아집니다\p"
	.string "별로 따르지 않으면\n"
	.string "화풀이의 위력이 높아지지요!$"
	// ポケモンの なつきぐあいが たかいとｎ
	// おんがえしの いりょくも たかくなるｐ
	// なつきぐあいが ひくいとｎ
	// やつあたりの いりょくが つよまるんだよ!

PacifidlogTown_House2_Text_GetGoodTMInXDays: @ 8203AF4
	.string "그래요 그래요 앞으로 {STR_VAR_1}일 지나면\n"
	.string "좋은 기술머신이 손에 들어온답니다!\p"
	.string "그때 다시 놀러오시지요!\n"
	.string "당신의 포켓몬에게 맞는\l"
	.string "근사한 기술머신을 드릴 테니까요$"
	// そうそう あと§いにち たてばｎ
	// いい わざマシンが てに はいるんだよ!ｐ
	// そのとき また あそびに きたまえ!ｎ
	// きみの ポケモンに あったｌ
	// すてきな わざマシンを あげるから

PacifidlogTown_House2_Text_Rurii: @ 8203B8D
	.string "루리리: 루리-$"
	// ルリリ『るり-

PacifidlogTown_House2_Text_VeryFriendlyWithTrainer: @ 8203B9D
	.string "굉장히 따르고 있는 듯하다$"
	// とっても なついて いるようだ

PacifidlogTown_House2_Text_Rururi: @ 8203BCE
	.string "루리리: 루리릿!!$"
	// ルリリ『ルルリッ!!

PacifidlogTown_House2_Text_DoesntLikeTrainerVeryMuch: @ 8203BDF
	.string "별로 안 따르는 듯하다...$"
	// あんまり なついて いないようだ……

