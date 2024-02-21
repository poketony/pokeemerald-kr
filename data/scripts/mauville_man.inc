MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan:: @ 828E066
	special ScrSpecial_GetCurrentMauvilleMan
	switch VAR_RESULT
	case MAUVILLE_MAN_BARD, MauvilleCity_PokemonCenter_1F_EventScript_Bard
	case MAUVILLE_MAN_HIPSTER, MauvilleCity_PokemonCenter_1F_EventScript_Hipster
	case MAUVILLE_MAN_TRADER, MauvilleCity_PokemonCenter_1F_EventScript_Trader
	case MAUVILLE_MAN_STORYTELLER, MauvilleCity_PokemonCenter_1F_EventScript_Storyteller
	case MAUVILLE_MAN_GIDDY, MauvilleCity_PokemonCenter_1F_EventScript_Giddy
	end

@ Bard
MauvilleCity_PokemonCenter_1F_EventScript_Bard:: @ 828E0A6
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_PlaySong
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong
	end

MauvilleCity_PokemonCenter_1F_EventScript_PlaySong:: @ 828E0C7
	setvar VAR_0x8004, 0
	special ScrSpecial_PlayBardSong
	delay 60
	special ScrSpecial_HasBardSongBeenChanged
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong:: @ 828E0EA
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics:: @ 828E0F4
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	end

MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics:: @ 828E113
	setvar VAR_0x8004, EASY_CHAT_TYPE_BARD_SONG
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 0
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 1
	special ScrSpecial_PlayBardSong
	delay 60
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	special ScrSpecial_SaveBardSongLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics:: @ 828E15D
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2, MSGBOX_DEFAULT
	release
	end

@ Hipster
MauvilleCity_PokemonCenter_1F_EventScript_Hipster:: @ 828E167
	lock
	faceplayer
	setflag FLAG_SYS_HIPSTER_MEET
	msgbox MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening, MSGBOX_DEFAULT
	special ScrSpecial_GetHipsterSpokenFlag
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord:: @ 828E18C
	special ScrSpecial_HipsterTeachWord
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_TeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TeachWord:: @ 828E1A4
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfPhrase, MSGBOX_DEFAULT
	special ScrSpecial_SetHipsterSpokenFlag
	release
	end

@ Trader
MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor: @ 828E1B1
	.string "난 굿즈교환아저씨\n"
	.string "나랑 굿즈 교환하지 않을래?$"

MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues: @ 828E1E8
	.string "그렇구나...\n"
	.string "아저씨 아쉽다...$"

MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded: @ 828E20E
	.string "하지만 너하고는 지난번에\n"
	.string "굿즈를 교환했는걸$"

MauvilleCity_PokemonCenter_1F_Text_PickADecorItem: @ 828E23F
	.string "이게 내가 가지고 있는 굿즈야\n"
	.string "가지고 싶은 거 있으면 말해$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything: @ 828E27F
	.string "갖고 싶은 굿즈 없어?\n"
	.string "아저씨 아쉽다...$"

MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt: @ 828E2A9
	.string "그건 {STR_VAR_1}{K_IGA}\n"
	.string "썼었던 굿즈야\p"
	.string "이걸로 할래?$"

MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor: @ 828E2E3
	.string "...엣 너 굿즈\n"
	.string "하나도 안 가지고 있잖아!$"

MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade: @ 828E323
	.string "그럼 교환에 내놓을\n"
	.string "굿즈를 선택해 줘!$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade: @ 828E356
	.string "교환 안 할 거야?\n"
	.string "아저씨 아쉽다...$"

MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis: @ 828E380
	.string "너 {STR_VAR_2}{K_IGA} 가득해서\n"
	.string "더 이상 지닐 수 없어$"

MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor: @ 828E3C4
	.string "그럼 내 {STR_VAR_3}{K_WAGWA}\n"
	.string "너의 {STR_VAR_2}{K_EULREUL} 교환할게?$"

MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse: @ 828E3EC
	.string "그 굿즈는 지금 장식되어 있네\n"
	.string "장식한 굿즈는 교환할 수 없어$"

MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC: @ 828E424
	.string "자 그럼 교환!\p"
	.string "네 PC에\n"
	.string "굿즈를 전송해둘게$"

MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne: @ 828E45A
	.string "아앗! 미안!\n"
	.string "그거 굉장히 희귀한 굿즈라서\l"
	.string "교환할 수 없어!\p"
	.string "그 밖에 원하는 굿즈 있어?$"

MauvilleCity_PokemonCenter_1F_EventScript_Trader:: @ 828E4D4
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade
	special ScrSpecial_GetTraderTradedFlag
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade:: @ 828E503
	msgbox MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded:: @ 828E50D
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive:: @ 828E517
	special ScrSpecial_TraderMenuGetDecoration
	waitstate
	compare VAR_0x8004, 0
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor
	compare VAR_0x8004, 0xFFFF
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor
	special ScrSpecial_DoesPlayerHaveNoDecorations
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor:: @ 828E558
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor:: @ 828E562
	message MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor:: @ 828E56E
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor:: @ 828E57A
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive:: @ 828E584
	msgbox MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade, MSGBOX_DEFAULT
	special ScrSpecial_TraderMenuGiveDecoration
	waitstate
	compare VAR_0x8006, 0
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor
	compare VAR_0x8006, 0xFFFF
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse
	special ScrSpecial_IsDecorationFull
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	special ScrSpecial_TraderDoDecorationTrade
	msgbox MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor:: @ 828E5D4
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse:: @ 828E5DE
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor:: @ 828E5EC
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis, MSGBOX_DEFAULT
	release
	end

@ Storyteller
MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale: @ 828E5F6
	.string "난 전설아저씨\n"
	.string "전설의 트레이너의 이야기를 하곤 해\p"
	.string "내 얘기 들어볼래?$"

MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues: @ 828E64D
	.string "그렇구나...\n"
	.string "아저씨 아쉽다...$"

MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell: @ 828E673
	.string "난 이런 전설들을 알고 있어\n"
	.string "어느 전설을 듣고 싶어?$"

MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales: @ 828E6AE
	.string "그렇지만 난...\n"
	.string "전설의 트레이너에 대한 이야기를\l"
	.string "하나도 알고 있지 않아\p"
	.string "어딘가에 전설로 남을 만한\n"
	.string "트레이너는 없는 걸까$"

MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes: @ 828E726
	.string "...뭐라고!!!\p"
	.string "너 {STR_VAR_1}번이나\n"
	.string "{STR_VAR_2}고!?\p"
	.string "...으음 그거 대단한데!\n"
	.string "새로운 전설의 시작이야!$"
	// ……え!!!ｐ
	// きみ §いかい もｎ
	// §う の!?ｐ
	// ……ううむ それは すごい!ｎ
	// あたらしい でんせつの はじまりだ!

MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends: @ 828E78A
	.string "이것보다 좀 더 대단한\n"
	.string "전설을 가진 트레이너는\l"
	.string "어디 없으려나...$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales: @ 828E7EE
	.string "...너 트레이너야?\p"
	.string "그럼 뭔가 전설 같은 이야기\n"
	.string "좀 들려줘!$"

@ Unused
MauvilleCity_PokemonCenter_1F_Text_HearAnotherLegendaryTale: @ 828E844
	.string "그런데...\n"
	.string "또 다른 전설 듣고 싶어?$"

MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend: @ 828E881
	.string "...으-음 어딘가 부족한걸\p"
	.string "좀 더 굉장한 이야기를\n"
	.string "들려줬으면 좋겠는데$"

MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested: @ 828E8D9
	.string "좀 더 많은 사람들이\n"
	.string "전설의 트레이너의 이야기를\l"
	.string "들어주면 좋을 텐데$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameTitle:: @ 828E930
	.string "리포트를 많이 작성한 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameAction:: @ 828E947
	.string "리포트를 작성했다$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameStory:: @ 828E956
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "{STR_VAR_1}번이나\n"
	.string "리포트를 작성했나 봐!\p"
	.string "{STR_VAR_3}{K_I}만큼 조심성 있는\n"
	.string "트레이너는 없을 거야!$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedTitle:: @ 828E9D7
	.string "유행 발신 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedAction:: @ 828E9EF
	.string "유행을 만들었다$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedStory:: @ 828E9FE
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "{STR_VAR_1}번이나\n"
	.string "유행을 새로 만들었나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 계속\n"
	.string "호연의 유행을 만들고 있어!$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedTitle:: @ 828EA7D
    .string "나무열매를 많이 심은 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedAction:: @ 828EA98
	.string "나무열매를 심었다$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedStory:: @ 828EAA8
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "{STR_VAR_1}번이나\n"
	.string "나무열매를 심었나 봐!\p"
	.string "{STR_VAR_3}만큼 열렬히\n"
	.string "나무열매를 좋아하는 사람은 없을 거야!$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesTitle:: @ 828EB19
	.string "자전거 애호가 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesAction:: @ 828EB31
	.string "자전거를 교환했다$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesStory:: @ 828EB3E
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "자전거를 교환했나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 어지간히도\n"
	.string "자전거를 좋아하는 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsTitle:: @ 828EBB5
	.string "인터뷰에 많이 응한 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsAction:: @ 828EBCD
	.string "인터뷰에 응했다$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsStory:: @ 828EBDD
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "인터뷰에 응했나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 정말\n"
	.string "주목받는 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesTitle:: @ 828EC60
	.string "승부 애호가 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesAction:: @ 828EC79
	.string "승부했다$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesStory:: @ 828EC81
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "포켓몬 승부를 했나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 트레이너를 보면\n"
	.string "승부를 해야 직성이 풀리는 거겠지!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtTitle:: @ 828ED04
	.string "많이 잡은 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtAction:: @ 828ED21
	.string "포켓몬을 잡았다$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtStory:: @ 828ED30
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}마리씩이나\n"
	.string "포켓몬을 잡았나 봐!\p"
	.string "{STR_VAR_3}{K_I}야말로 전설의\n"
	.string "포켓몬 잡기 달인일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtTitle:: @ 828EDA1
	.string "많이 낚은 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtAction:: @ 828EDB5
	.string "포켓몬을 낚았다$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtStory:: @ 828EDCF
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "포켓몬을 낚았나 봐!\p"
	.string "{STR_VAR_3}{K_I}야말로 전설의\n"
	.string "낚시 명인일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedTitle:: @ 828EE45
	.string "알을 많이 품은 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedAction:: @ 828EE5D
	.string "알을 부화시켰다$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedStory:: @ 828EE6A
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "{STR_VAR_1}개나 되는 알을\n"
	.string "부화시켰나 봐!\p"
	.string "{STR_VAR_3}{K_I}야말로 전설의\n"
	.string "알품기 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedTitle:: @ 828EEDD
	.string "진화를 많이 시킨 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedAction:: @ 828EEF1
	.string "포켓몬을 진화시켰다$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedStory:: @ 828EF01
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}마리씩이나\n"
	.string "포켓몬을 진화시켰나 봐!\p"
	.string "{STR_VAR_3}{K_I}야말로 최고의\n"
	.string "포켓몬 진화 마스터일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterTitle:: @ 828EF73
	.string "포켓몬센터 애호가 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterAction:: @ 828EF95
	.string "포켓몬센터에서 회복했다$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterStory:: @ 828EFAA
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "포켓몬센터에서 회복했나 봐!\p"
	.string "{STR_VAR_3}만큼 포켓몬센터를\n"
	.string "좋아하는 트레이너는 없겠지!$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeTitle:: @ 828F045
	.string "집 애호가 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeAction:: @ 828F05A
	.string "자신의 집에서 회복했다$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeStory:: @ 828F071
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "자신의 집에서 회복했대!\p"
	.string "{STR_VAR_3}만큼 집을\n"
	.string "좋아하는 트레이너는 없을 거야!$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesTitle:: @ 828F0F3
	.string "사파리존에 자주 가는 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesAction:: @ 828F10D
	.string "사파리존에 들어갔다$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesStory:: @ 828F125
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "사파리존에 들어갔나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 사파리존에서라면\n"
	.string "야생의 피가 끓는 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutTitle:: @ 828F1BE
	.string "풀베기를 많이 쓴 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutAction:: @ 828F1D5
	.string "풀베기를 썼다$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutStory:: @ 828F1DE
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "풀베기를 썼나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 풀베기가\n"
	.string "좋아서 참을 수 없는 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashTitle:: @ 828F24F
	.string "바위를 많이 깬 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashAction:: @ 828F269
	.string "바위깨기를 썼다$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashStory:: @ 828F277
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "바위깨기를 썼나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 바위를 봐도\n"
	.string "꺾이지 않는 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesTitle:: @ 828F2FC
	.string "이사를 좋아하는 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesAction:: @ 828F314
	.string "이사를 했다$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesStory:: @ 828F32A
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "비밀기지를 이사했나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 이사를\n"
	.string "무척 좋아하는 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashTitle:: @ 828F3AD
	.string "많이 튀게 한 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashAction:: @ 828F3C6
	.string "튀어오르기를 썼다$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashStory:: @ 828F3D2
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "튀어오르기를 썼나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 튀어오르기가\n"
	.string "무척 즐거운 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleTitle:: @ 828F44B
	.string "포기하지 않는 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleAction:: @ 828F461
	.string "발버둥을 썼다$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleStory:: @ 828F47C
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "발버둥을 썼나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 어떤 상황에서도\n"
	.string "결코 포기하지 않는 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsTitle:: @ 828F50C
	.string "슬롯의 명인$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsAction:: @ 828F51B
	.string "슬롯에서 대당첨되었다$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsStory:: @ 828F538
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "슬롯에서 대당첨됐다지 뭐야!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 슬롯머신을\n"
	.string "꿰고 있는 트레이너겠지!$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsTitle:: @ 828F5BE
	.string "룰렛의 명인$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsAction:: @ 828F5D1
	.string "룰렛을 연속으로 맞혔다$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsStory:: @ 828F5F2
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "룰렛을 연속으로 맞혔다지 뭐야!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 확실하게\n"
	.string "룰렛을 지켜보는 트레이너겠지!$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesTitle:: @ 828F678
	.string "배틀타워의 도전자$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesAction:: @ 828F694
	.string "배틀타워에 도전했다$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesStory:: @ 828F6B4
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "배틀타워에 도전했나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 배틀타워에\n"
	.string "집착을 지닌 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksTitle:: @ 828F751
	.string "블렌드 애호가 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksAction:: @ 828F76A
	.string "포켓몬스넥을 만들었다$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksStory:: @ 828F776
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "포켓몬스넥을 만들었나 봐!\p"
	.string "{STR_VAR_3}만큼 나무열매블렌더를\n"
	.string "잘 쓰는 사람은 없을 거야!$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsTitle:: @ 828F7F6
	.string "콘테스트 애호가 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsAction:: @ 828F811
	.string "콘테스트에 참가했다$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsStory:: @ 828F822
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "{STR_VAR_1}번이나\n"
	.string "콘테스트에 참가했나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 자신의 포켓몬을\n"
	.string "남들에게 보여주고 싶어하는 트레이너겠지!$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsTitle:: @ 828F89C
	.string "콘테스트의 달인$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsAction:: @ 828F8AF
	.string "콘테스트에서 우승했다$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsStory:: @ 828F8BC
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "콘테스트에서 우승했나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 엄청난\n"
	.string "콘테스트 마스터일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedTitle:: @ 828F92F
	.string "쇼핑 애호가 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedAction:: @ 828F941
	.string "쇼핑을 했다$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedStory:: @ 828F949
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "가게에서 쇼핑을 했대!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 가게에 들어가면\n"
	.string "어느새 사버리는 트레이너겠지!$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderTitle:: @ 828F9D1
	.string "다우징 애호가 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderAction:: @ 828F9EA
	.string "다우징머신을 썼다$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderStory:: @ 828F9FD
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "다우징머신을 썼대!\p"
	.string "{STR_VAR_3}{K_EUNNEUN}\n"
	.string "정말 물건 찾기를 좋아하는 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedTitle:: @ 828FA81
	.string "비에 젖은 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedAction:: @ 828FA99
	.string "비에 젖었다$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedStory:: @ 828FAA7
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "비에 흠뻑 젖었대!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 비도 끌리게 하는\n"
	.string "매력적인 트레이너일 거 같아!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexTitle:: @ 828FB1D
	.string "도감을 많이 본 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexAction:: @ 828FB35
	.string "도감을 봤다$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexStory:: @ 828FB47
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "도감을 봤나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 도감으로 포켓몬을\n"
	.string "조사하는 것을 좋아하는 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsTitle:: @ 828FBC4
	.string "리본을 잔뜩 모은 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsAction:: @ 828FBD9
	.string "리본을 받았다$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsStory:: @ 828FBEA
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "리본을 받았나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 리본을 모으는 걸\n"
	.string "무척 좋아하는 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedTitle:: @ 828FC6B
	.string "언덕을 많이 뛰어넘은 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedAction:: @ 828FC85
	.string "언덕을 뛰어넘었다$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedStory:: @ 828FC98
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "언덕을 뛰어넘었나 봐!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 언덕을 보면\n"
	.string "뛰어넘지 않곤 못 배기는 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedTitle:: @ 828FD1D
	.string "전설의 TV 시청자$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedAction:: @ 828FD35
	.string "TV를 봤다$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedStory:: @ 828FD40
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "TV를 봤다는 거야!\p"
	.string "{STR_VAR_3}{K_EUNNEUN}\n"
	.string "TV가 정말 좋은 트레이너겠지!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockTitle:: @ 828FDA2
	.string "시간을 신경 쓰는 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockAction:: @ 828FDBD
	.string "시계를 봤다$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockStory:: @ 828FDCE
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "시계를 봤대!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 시간을 신경 쓰는\n"
	.string "꼼꼼한 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryTitle:: @ 828FE57
	.string "ID 추첨에 당첨된 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryAction:: @ 828FE72
	.string "ID 추첨에 당첨됐다$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryStory:: @ 828FE88
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "ID 추첨에서 당첨됐대!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 포켓몬을 교환할\n"
	.string "친구가 엄청 많은 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareTitle:: @ 828FF0C
	.string "키우미집 단골 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareAction:: @ 828FF27
	.string "키우미집에 포켓몬을 맡겼다$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareStory:: @ 828FF44
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "키우미집에 포켓몬을 맡겼대!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 어쨌든 키우고 보는\n"
	.string "맹렬한 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarTitle:: @ 828FFDD
	.string "케이블카 애호가 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarAction:: @ 828FFFA
	.string "케이블카에 탔다$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarStory:: @ 829000D
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "케이블카를 탔대!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 위아래로 왔다 갔다 하는\n"
	.string "매우 바쁜 트레이너일 거야!$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsTitle:: @ 8290097
	.string "온천에 자주 다니는 트레이너$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsAction:: @ 82900B5
	.string "온천에 들어갔다$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsStory:: @ 82900CB
	.string "{STR_VAR_3}{K_I}라고 하는\n"
	.string "트레이너의 이야기인데...\p"
	.string "놀랍게도 {STR_VAR_1}번이나\n"
	.string "온천에 들어갔대!\p"
	.string "{STR_VAR_3}{K_EUNNEUN} 분명\n"
	.string "피부가 매끈매끈한 트레이너일 거야!$"


MauvilleCity_PokemonCenter_1F_EventScript_Storyteller:: @ 829014A
	lock
	faceplayer
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, 0
	setvar VAR_0x800A, 0
	setvar VAR_0x800B, 0
	msgbox MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, ScrSpecial_StorytellerGetFreeStorySlot
	compare VAR_RESULT, 0
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales
	message MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell
	waitmessage
	special ScrSpecial_StorytellerStoryListMenu
	waitstate
	compare VAR_RESULT, 0
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection
	setvar VAR_0x8008, 1
	special ScrSpecial_StorytellerDisplayStory
	waitmessage
	waitbuttonpress
	specialvar VAR_RESULT, ScrSpecial_StorytellerUpdateStat
	compare VAR_RESULT, 0
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales
	goto MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale

MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection:: @ 82901B7
	goto MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	end

MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales:: @ 82901BD
	msgbox MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends, MSGBOX_DEFAULT
	specialvar VAR_RESULT, ScrSpecial_HasStorytellerAlreadyRecorded
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd
	goto MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales

MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales:: @ 82901DA
	msgbox MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales, MSGBOX_DEFAULT
MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales:: @ 82901E2
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, ScrSpecial_StorytellerInitializeRandomStat
	compare VAR_RESULT, 1
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale
	msgbox MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale:: @ 829020F
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller:: @ 8290219
	msgbox MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

@ Unused
MauvilleCity_PokemonCenter_1F_EventScript_WaitingForRecordMix:: @ 8290223
	msgbox MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd:: @ 829022D
	release
	end

@ Giddy
MauvilleCity_PokemonCenter_1F_Text_HearMyStory: @ 829022F
	.string "난 메르헨아저씨\n"
	.string "엄청 재밌는 이야기를 하곤 해\p"
	.string "내 얘기 들어볼래?$"

MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues: @ 8290281
	.string "그렇구나...\n"
	.string "아저씨 아쉽다...$"

MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking: @ 82902A7
	.string "그리고 생각해 봤는데...$"

MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain: @ 82902BD
	.string "이 정도려나...\p"
	.string "들어줘서 고마워!\n"
	.string "바이바이!$"

MauvilleCity_PokemonCenter_1F_EventScript_Giddy:: @ 82902F6
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_HearMyStory, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale:: @ 8290317
	special ScrSpecial_GiddyShouldTellAnotherTale
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale:: @ 8290331
	special ScrSpecial_GiddyShouldTellAnotherTale
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale:: @ 829034B
	msgbox MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	end

@ Regardless of whether yes or no is selected below, Giddy will continue to tell stories until he's told 10
MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale:: @ 8290359
	special ScrSpecial_GenerateGiddyLine
	special ShowFieldMessageStringVar4
	waitmessage
	yesnobox 20, 8
	compare VAR_RESULT, 1
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	compare VAR_RESULT, 0
	goto_if_eq MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy:: @ 829037A
	msgbox MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales:: @ 8290384
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong: @ 829038E
	.string "난 싱어송아저씨\n"
	.string "내 노래 들어볼래?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1: @ 82903C0
	.string "그렇구나...\n"
	.string "아저씨 아쉽다...$"

MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers: @ 82903E6
	.string "아아 좋은 노래구나...\n"
	.string "다른 사람에게도 들려주고 싶다$"

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics: @ 8290421
	.string "내 노래 어때?\p"
	.string "근데 가사가 좀 마음에 안 들어\p"
	.string "그러니까 네가 좀 써줄래?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2: @ 829049B
	.string "그렇구나...\n"
	.string "아저씨 아쉽다...$"

MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou: @ 82904C1
	.string "고마워!\n"
	.string "그럼 불러본다!$"

MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo: @ 82904EB
	.string "이런 느낌이면 되니?$"

MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile: @ 8290514
	.string "좋아 알았어!\n"
	.string "당분간 이 노래를 불러볼게!$"

MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening: @ 829054C
	.string "난 지금유행아저씨\n"
	.string "요즘 유행하는 유행어를 알려줄게$"

MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou: @ 8290598
	.string "하지만 네게는 지난번에 알려줬었지\p"
	.string "이번에는 다른 사람에게도 알려주고 싶어$"

MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach: @ 8290602
	.string "근데 너 유행어 많이 알고 있잖아\n"
	.string "알려줄 건 이제 전혀 없어$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfPhrase: @ 8290666
	.string "너 “{STR_VAR_1}”라는\n"
	.string "말 알고 있어?\p"
	.string "의미? 그건 말이지...\n"
	.string "아빠나 엄마한테 한번 물어봐$"
