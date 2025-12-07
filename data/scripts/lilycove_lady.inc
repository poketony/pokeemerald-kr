.set LOCALID_LILYCOVE_LADY, 4
.set LOCALID_LADYS_MON, 5

LilycoveCity_PokemonCenter_1F_EventScript_LilycoveLady:: @ 82A836B
    special Script_GetLilycoveLadyId
    switch VAR_RESULT
    case LILYCOVE_LADY_QUIZ, LilycoveCity_PokemonCenter_1F_EventScript_QuizLady
    case LILYCOVE_LADY_FAVOR, LilycoveCity_PokemonCenter_1F_EventScript_FavorLady
    case LILYCOVE_LADY_CONTEST, LilycoveCity_PokemonCenter_1F_EventScript_ContestLady
    end

LilycoveCity_PokemonCenter_1F_EventScript_FavorLady:: @ 82A8395
    lock
    faceplayer
    msgbox LilycoveCity_PokemonCenter_1F_Text_ImTheFavorLady, MSGBOX_DEFAULT
    specialvar VAR_RESULT, GetFavorLadyState
    compare VAR_RESULT, LILYCOVE_LADY_STATE_READY
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyReady
    compare VAR_RESULT, LILYCOVE_LADY_STATE_COMPLETED
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyCompleted
    compare VAR_RESULT, LILYCOVE_LADY_STATE_PRIZE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyPrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyCompleted:: @ 82A83C6
    msgbox LilycoveCity_PokemonCenter_1F_Text_ThankYouForLastTime, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyReady:: @ 82A83D0
    special BufferFavorLadyRequest
    msgbox LilycoveCity_PokemonCenter_1F_Text_ObsessedWithThing, MSGBOX_DEFAULT
    specialvar VAR_RESULT, HasAnotherPlayerGivenFavorLadyItem
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_RequestItem
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_TellAboutPlayersItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_TellAboutPlayersItem:: @ 82A83F7
    special BufferFavorLadyItemName
    special BufferFavorLadyPlayerName
    specialvar VAR_RESULT, DidFavorLadyLikeItem
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_PlayerGaveBadThing
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_PlayerGaveGreatThing
    end

LilycoveCity_PokemonCenter_1F_EventScript_PlayerGaveBadThing:: @ 82A8419
    msgbox LilycoveCity_PokemonCenter_1F_Text_PlayerGaveMeBadThing, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_RequestItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_PlayerGaveGreatThing:: @ 82A8427
    msgbox LilycoveCity_PokemonCenter_1F_Text_PlayerGaveMeGreatThing, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_RequestItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_RequestItem:: @ 82A8435
    msgbox LilycoveCity_PokemonCenter_1F_Text_WillYouShareThing, MSGBOX_YESNO
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineFavor
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AcceptFavor
    end

LilycoveCity_PokemonCenter_1F_EventScript_DeclineFavor:: @ 82A8454
    msgbox LilycoveCity_PokemonCenter_1F_Text_IsThatSoGoodbye, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_AcceptFavor:: @ 82A845E
    msgbox LilycoveCity_PokemonCenter_1F_Text_WhatWillYouGiveMe, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_ChooseFavorItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_ChooseFavorItem:: @ 82A846C
    fadescreen FADE_TO_BLACK
    setvar VAR_RESULT, 0
    special Script_FavorLadyOpenBagMenu
    waitstate
    compare VAR_RESULT, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskQuitChooseFavorItem
    compare VAR_RESULT, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_GiveFavorItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskQuitChooseFavorItem:: @ 82A848E
    msgbox LilycoveCity_PokemonCenter_1F_Text_NotWillingToShare, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineFavor
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_ChooseFavorItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_GiveFavorItem:: @ 82A84AD
    specialvar VAR_RESULT, Script_DoesFavorLadyLikeItem
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DidntLikeFavorItem
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_CheckLovedItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_DidntLikeFavorItem:: @ 82A84C9
    special BufferFavorLadyRequest
    msgbox LilycoveCity_PokemonCenter_1F_Text_IllTryToCherishIt, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_CheckLovedItem:: @ 82A84D6
    specialvar VAR_RESULT, IsFavorLadyThresholdMet
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_LikedFavorItem
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_LovedFavorItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_LikedFavorItem:: @ 82A84F2
    special BufferFavorLadyRequest
    msgbox LilycoveCity_PokemonCenter_1F_Text_IWillCherishThis, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_LovedFavorItem:: @ 82A84FF
    special BufferFavorLadyRequest
    msgbox LilycoveCity_PokemonCenter_1F_Text_IWillTreasureThis, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyPrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyPrize:: @ 82A8510
    setvar VAR_0x8004, 0
    specialvar VAR_0x8004, FavorLadyGetPrize
    msgbox LilycoveCity_PokemonCenter_1F_Text_IllGiveYouThisInReturn, MSGBOX_DEFAULT
    giveitem VAR_0x8004
    compare VAR_RESULT, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_NoRoomForFavorPrize
    compare VAR_RESULT, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_ReceivedFavorPrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_NoRoomForFavorPrize:: @ 82A8545
    msgbox LilycoveCity_PokemonCenter_1F_Text_YouDontHaveSpaceForIt, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_ReceivedFavorPrize:: @ 82A854F
    special SetFavorLadyState_Complete
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_QuizLady:: @ 82A8554
    lock
    faceplayer
    msgbox LilycoveCity_PokemonCenter_1F_Text_ImTheQuizLady, MSGBOX_DEFAULT
    specialvar VAR_RESULT, GetQuizLadyState
    compare VAR_RESULT, LILYCOVE_LADY_STATE_READY
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_HasQuiz
    compare VAR_RESULT, LILYCOVE_LADY_STATE_COMPLETED
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_CheckMadeQuiz
    compare VAR_RESULT, LILYCOVE_LADY_STATE_PRIZE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_ReadyGivePrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_HasQuiz:: @ 82A8585
    specialvar VAR_RESULT, GetQuizAuthor
    compare VAR_RESULT, QUIZ_AUTHOR_PLAYER
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_WaitingToTakeYourQuiz
    compare VAR_RESULT, QUIZ_AUTHOR_OTHER_PLAYER
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_PlayerQuizReady
    compare VAR_RESULT, QUIZ_AUTHOR_LADY
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_LadyQuizReady
    end

LilycoveCity_PokemonCenter_1F_EventScript_CheckMadeQuiz:: @ 82A85AC
    specialvar VAR_RESULT, IsQuizLadyWaitingForChallenger
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskMakeQuiz
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_WaitingToTakeYourQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_WaitingToTakeYourQuiz:: @ 82A85C8
    msgbox LilycoveCity_PokemonCenter_1F_Text_WaitingToTakeYourQuiz, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_PlayerQuizReady:: @ 82A85D2
    msgbox LilycoveCity_PokemonCenter_1F_Text_WaitingForChallenger, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_AskTakeQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_LadyQuizReady:: @ 82A85E0
    msgbox LilycoveCity_PokemonCenter_1F_Text_WaitingForChallenger, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_AskTakeQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskTakeQuiz:: @ 82A85EE
    setvar VAR_0x8004, 0
    msgbox LilycoveCity_PokemonCenter_1F_Text_TakeQuizChallenge, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_TakeQuiz
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_DeclineQuiz:: @ 82A8612
    msgbox LilycoveCity_PokemonCenter_1F_Text_HowBoringBye, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_TakeQuiz:: @ 82A861C
    special ClearQuizLadyPlayerAnswer
    compare VAR_0x8004, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_ShowQuestion
    compare VAR_0x8004, EASY_CHAT_TYPE_QUIZ_ANSWER
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_GetAnswer

LilycoveCity_PokemonCenter_1F_EventScript_CheckQuizTakingState:: @ 82A8635
    compare VAR_RESULT, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskQuitQuiz
    compare VAR_RESULT, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_SubmitQuizResponse
    end

LilycoveCity_PokemonCenter_1F_EventScript_ShowQuestion:: @ 82A864C
    special QuizLadyShowQuizQuestion
    waitstate
    goto LilycoveCity_PokemonCenter_1F_EventScript_CheckQuizTakingState
    end

LilycoveCity_PokemonCenter_1F_EventScript_GetAnswer:: @ 82A8656
    special QuizLadyGetPlayerAnswer
    waitstate
    goto LilycoveCity_PokemonCenter_1F_EventScript_CheckQuizTakingState
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskQuitQuiz:: @ 82A8660
    msgbox LilycoveCity_PokemonCenter_1F_Text_YoureGoingToQuit, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_QuitTakingQuiz
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_TakeQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_QuitTakingQuiz:: @ 82A867F
    msgbox LilycoveCity_PokemonCenter_1F_Text_TakeTheQuizAnotherTime, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_SubmitQuizResponse:: @ 82A8689
    special SetQuizLadyState_Complete
    msgbox LilycoveCity_PokemonCenter_1F_Text_WaitForAnswer, MSGBOX_DEFAULT
    specialvar VAR_RESULT, IsQuizAnswerCorrect
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_IncorrectResponse
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_CorrectResponse
    end

LilycoveCity_PokemonCenter_1F_EventScript_CorrectResponse:: @ 82A86B0
    playse SE_SUCCESS
    delay 10
    playse SE_SUCCESS
    msgbox LilycoveCity_PokemonCenter_1F_Text_YouGotItRight, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_ReadyGivePrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_IncorrectResponse:: @ 82A86C7
    special BufferQuizCorrectAnswer
    special BufferQuizPrizeName
    playse SE_FAILURE
    delay 10
    playse SE_FAILURE
    msgbox LilycoveCity_PokemonCenter_1F_Text_WrongTheCorrectAnswerIs, MSGBOX_DEFAULT
    msgbox LilycoveCity_PokemonCenter_1F_Text_IGetToKeepPrize, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_AskMakeQuiz
    end

@ VAR_RESULT is essentially ignored, both jumps are identical
LilycoveCity_PokemonCenter_1F_EventScript_ReadyGivePrize:: @ 82A86EC
    specialvar VAR_RESULT, BufferQuizAuthorNameAndCheckIfLady
    compare VAR_RESULT, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_GivePrize1
    compare VAR_RESULT, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_GivePrize0
    end

LilycoveCity_PokemonCenter_1F_EventScript_GivePrize1:: @ 82A8708
    msgbox LilycoveCity_PokemonCenter_1F_Text_YouGotItRightYouveWonPersonsPrize, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_GivePrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_GivePrize0:: @ 82A8716
    msgbox LilycoveCity_PokemonCenter_1F_Text_YouGotItRightYouveWonPersonsPrize, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_GivePrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_GivePrize:: @ 82A8724
    setvar VAR_0x8005, 0
    special BufferQuizPrizeItem
    special SetQuizLadyState_Complete
    giveitem VAR_0x8005
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_NoSpaceForQuizPrize
    goto LilycoveCity_PokemonCenter_1F_EventScript_AskMakeQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_NoSpaceForQuizPrize:: @ 82A874C
    msgbox LilycoveCity_PokemonCenter_1F_Text_YourBagIsFilledUp, MSGBOX_DEFAULT
    special SetQuizLadyState_GivePrize
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskMakeQuiz:: @ 82A8759
    msgbox LilycoveCity_PokemonCenter_1F_Text_MakeYourOwnQuiz, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_MakeQuiz
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineMakeQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_DeclineMakeQuiz:: @ 82A8778
    special QuizLadyPickNewQuestion
    msgbox LilycoveCity_PokemonCenter_1F_Text_MaybeNextTime, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_MakeQuiz:: @ 82A8785
    msgbox LilycoveCity_PokemonCenter_1F_Text_PickYourPrize, MSGBOX_DEFAULT
LilycoveCity_PokemonCenter_1F_EventScript_PickPrize:: @ 82A878D
    fadescreen FADE_TO_BLACK
    setvar VAR_RESULT, 0
    special Script_QuizLadyOpenBagMenu
    waitstate
    compare VAR_RESULT, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskQuitChoosingPrize
    compare VAR_RESULT, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_WriteQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskQuitChoosingPrize:: @ 82A87AF
    msgbox LilycoveCity_PokemonCenter_1F_Text_QuitChoosingPrize, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineMakeQuiz
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_PickPrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_WriteQuiz:: @ 82A87CE
    msgbox LilycoveCity_PokemonCenter_1F_Text_WriteYourQuiz, MSGBOX_DEFAULT
    special ClearQuizLadyQuestionAndAnswer
    special ClearQuizLadyPlayerAnswer
    setvar VAR_0x8004, EASY_CHAT_TYPE_QUIZ_QUESTION
LilycoveCity_PokemonCenter_1F_EventScript_WriteQuizQuestion:: @ 82A87E1
    fadescreen FADE_TO_BLACK
    special QuizLadySetCustomQuestion
    waitstate
    compare VAR_RESULT, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskQuitWritingQuizQuestion
    goto LilycoveCity_PokemonCenter_1F_EventScript_FinishMakingQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskQuitWritingQuizQuestion:: @ 82A87F8
    msgbox LilycoveCity_PokemonCenter_1F_Text_QuitWritingQuizQuestion, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineMakeQuiz
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_WriteQuizQuestion
    end

LilycoveCity_PokemonCenter_1F_EventScript_FinishMakingQuiz:: @ 82A8817
    special QuizLadyTakePrizeForCustomQuiz
    special QuizLadyRecordCustomQuizData
    special QuizLadySetWaitingForChallenger
    msgbox LilycoveCity_PokemonCenter_1F_Text_IllLookForAChallenger, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_ContestLady:: @ 82A882A
    lock
    faceplayer
    msgbox LilycoveCity_PokemonCenter_1F_Text_ImTheContestLady, MSGBOX_DEFAULT
    specialvar VAR_RESULT, HasPlayerGivenContestLadyPokeblock
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_NotGivenPokeblock
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_GivenPokeblock
    end

@ Redundant with above script, VAR_RESULT will always be FALSE here
LilycoveCity_PokemonCenter_1F_EventScript_NotGivenPokeblock:: @ 82A8850
    specialvar VAR_RESULT, ShouldContestLadyShowGoOnAir
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskForPokeblock
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_GivenPokeblock
    end

LilycoveCity_PokemonCenter_1F_EventScript_GivenPokeblock:: @ 82A886C
    msgbox LilycoveCity_PokemonCenter_1F_Text_ThankForPokeblock, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskForPokeblock:: @ 82A8876
    special Script_BufferContestLadyCategoryAndMonName
    msgbox LilycoveCity_PokemonCenter_1F_Text_MyFriendDisplaysQuality, MSGBOX_DEFAULT
    checkitem ITEM_POKEBLOCK_CASE, 1
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_NoPokeblockCase
    msgbox LilycoveCity_PokemonCenter_1F_Text_AskingForOnePokeblock, MSGBOX_YESNO
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineGivePokeblock
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_ChoosePokeblock
    end

LilycoveCity_PokemonCenter_1F_EventScript_DeclineGivePokeblock:: @ 82A88B0
    msgbox LilycoveCity_PokemonCenter_1F_Text_WhatACheapskate, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_ChoosePokeblock:: @ 82A88BA
    fadescreen FADE_TO_BLACK
    special OpenPokeblockCaseForContestLady
    waitstate
    compare VAR_RESULT, 0xFFFF
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskQuitGivingPokeblock
    compare VAR_RESULT, 0xFFFF
    goto_if_ne LilycoveCity_PokemonCenter_1F_EventScript_GivePokeblock
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskQuitGivingPokeblock:: @ 82A88D7
    msgbox LilycoveCity_PokemonCenter_1F_Text_ICantHaveOnePokeblock, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineGivePokeblock
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_ChoosePokeblock
    end

LilycoveCity_PokemonCenter_1F_EventScript_GivePokeblock:: @ 82A88F6
    msgbox LilycoveCity_PokemonCenter_1F_Text_IllUseYourPokeblock, MSGBOX_DEFAULT
    special SetContestLadyGivenPokeblock
    special GetContestLadyMonSpecies
    goto LilycoveCity_PokemonCenter_1F_EventScript_FeedPokeblock
    end

@ VAR_0x8004 here is the return value from GivePokeblockToContestLady
LilycoveCity_PokemonCenter_1F_EventScript_FeedPokeblock:: @ 82A890A
    applymovement LOCALID_LILYCOVE_LADY, LilycoveCity_PokemonCenter_1F_Movement_LadyFaceMon
    waitmovement 0
    delay 60
    applymovement LOCALID_LADYS_MON, LilycoveCity_PokemonCenter_1F_Movement_MonFaceLady
    waitmovement 0
    delay 60
    waitse
    playmoncry VAR_0x8005, 0
    delay 120
    waitmoncry
    compare VAR_0x8004, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_MonEnjoyPokeblock
    goto LilycoveCity_PokemonCenter_1F_EventScript_FinishFeedPokeblock
    end

@ VAR_0x8004 here is the return value from GivePokeblockToContestLady
LilycoveCity_PokemonCenter_1F_EventScript_MonEnjoyPokeblock:: @ 82A893F
    applymovement LOCALID_LADYS_MON, LilycoveCity_PokemonCenter_1F_Movement_MonJump
    waitmovement 0
    delay 60
LilycoveCity_PokemonCenter_1F_EventScript_FinishFeedPokeblock:: @ 82A894C
    applymovement LOCALID_LILYCOVE_LADY, LilycoveCity_PokemonCenter_1F_Movement_LadyFacePlayer
    waitmovement 0
    delay 60
    compare VAR_0x8004, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_MonDislikedPokeblock
    compare VAR_0x8004, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_MonLikedPokeblock
    end

LilycoveCity_PokemonCenter_1F_EventScript_MonDislikedPokeblock:: @ 82A8970
    msgbox LilycoveCity_PokemonCenter_1F_Text_NoChangeThanks, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_CheckAirContestLadyShow
    end

LilycoveCity_PokemonCenter_1F_EventScript_MonLikedPokeblock:: @ 82A897E
    special Script_BufferContestLadyCategoryAndMonName
    msgbox LilycoveCity_PokemonCenter_1F_Text_ReallyImprovedThanks, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_CheckAirContestLadyShow
    end

LilycoveCity_PokemonCenter_1F_EventScript_CheckAirContestLadyShow:: @ 82A898F
    specialvar VAR_RESULT, ShouldContestLadyShowGoOnAir
    compare VAR_RESULT, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AirContestLadyShow
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_AirContestLadyShow:: @ 82A89A1
    msgbox LilycoveCity_PokemonCenter_1F_Text_ReadyToEnterContests, MSGBOX_DEFAULT
    special PutLilycoveContestLadyShowOnTheAir
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_NoPokeblockCase:: @ 82A89AE
    msgbox LilycoveCity_PokemonCenter_1F_Text_DontHaveAPokeblockCase, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_Movement_LadyFaceMon: @ 82A89B8
    face_right
    delay_8
    step_end

LilycoveCity_PokemonCenter_1F_Movement_MonFaceLady: @ 82A89BB
    face_left
    delay_8
    step_end

@ Unused
LilycoveCity_PokemonCenter_1F_Movement_MonFaceDown: @ 82A89BE
    face_down
    step_end

LilycoveCity_PokemonCenter_1F_Movement_LadyFacePlayer: @ 82A89C0
    face_player
    step_end

LilycoveCity_PokemonCenter_1F_Movement_MonJump: @ 82A89C2
    disable_jump_landing_ground_effect
    jump_in_place_left
    disable_jump_landing_ground_effect
    jump_in_place_left
    step_end

LilycoveCity_PokemonCenter_1F_EventScript_ContestLadyMon:: @ 82A89C7
    specialvar VAR_RESULT, GetContestLadyCategory
    special Script_BufferContestLadyCategoryAndMonName
    special GetContestLadyMonSpecies
    compare VAR_RESULT, CONTEST_CATEGORY_COOL
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_Zigzagoon
    compare VAR_RESULT, CONTEST_CATEGORY_BEAUTY
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_Skitty
    compare VAR_RESULT, CONTEST_CATEGORY_CUTE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_Poochyena
    compare VAR_RESULT, CONTEST_CATEGORY_SMART
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_Kecleon
    compare VAR_RESULT, CONTEST_CATEGORY_TOUGH
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_Pikachu
    end

LilycoveCity_PokemonCenter_1F_EventScript_Zigzagoon:: @ 82A8A0A
    lock
    faceplayer
    waitse
    playmoncry VAR_0x8005, 0
    msgbox LilycoveCity_PokemonCenter_1F_Text_Zigzagoon, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_Skitty:: @ 82A8A1D
    lock
    faceplayer
    waitse
    playmoncry VAR_0x8005, 0
    msgbox LilycoveCity_PokemonCenter_1F_Text_Skitty, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_Poochyena:: @ 82A8A30
    lock
    faceplayer
    waitse
    playmoncry VAR_0x8005, 0
    msgbox LilycoveCity_PokemonCenter_1F_Text_Poochyena, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_Kecleon:: @ 82A8A43
    lock
    faceplayer
    waitse
    playmoncry VAR_0x8005, 0
    msgbox LilycoveCity_PokemonCenter_1F_Text_Kecleon, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_Pikachu:: @ 82A8A56
    lock
    faceplayer
    waitse
    playmoncry VAR_0x8005, 0
    msgbox LilycoveCity_PokemonCenter_1F_Text_Pikachu, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_PokemonCenter_1F_Text_ImTheFavorLady: @ 82A8A69
    .string "난 조르기아가씨야...$"
	@ わたし おねだり おねえさん……

LilycoveCity_PokemonCenter_1F_Text_ObsessedWithThing: @ 82A8A7D
    .string "난 최근\n"
    .string "{STR_VAR_1}한 것들에 관심이 많아...$"
	@ わたし さいきんｎ
	@ §いした ものに むちゅうなの……

LilycoveCity_PokemonCenter_1F_Text_ThankYouForLastTime: @ 82A8AB1
    .string "어머...\n"
    .string "지난번에 고마웠어...$"
	@ あら……ｎ
	@ このまえは どうも……

LilycoveCity_PokemonCenter_1F_Text_PlayerGaveMeBadThing: @ 82A8ACE
    .string "전에 말이지...\n"
    .string "{STR_VAR_3}씨라고 했었나...\p"
    .string "{STR_VAR_1}하다면서\n"
    .string "{STR_VAR_2}{K_EULREUL} 줬었거든\p"
	.string "하지만 전혀\n"
    .string "{STR_VAR_1}하지 않았어!$"
	@ まえにね……ｎ
	@ §えさん だった かしら……ｐ
	@ §い だからってｎ
	@ §うを くれたのよｐ
	@ だけど ちっともｎ
	@ §いじゃ なかったのよ!

LilycoveCity_PokemonCenter_1F_Text_PlayerGaveMeGreatThing: @ 82A8B36
    .string "전에 말이지 {STR_VAR_3}씨가\n"
    .string "엄청 {STR_VAR_1}한 {STR_VAR_2}{K_EULREUL}\l"
    .string "나한테 줬었어\p"
    .string "엄청 소중히 하고 있지$"
	@ まえにね §えさんがｎ
	@ とても §いな §うをｌ
	@ わたしに くれたのｐ
	@ すごく たいせつに してるのよ

LilycoveCity_PokemonCenter_1F_Text_WillYouShareThing: @ 82A8B69
    .string "있지... 만약 괜찮다면\n"
    .string "네가 가지고 있는 {STR_VAR_1}한 걸\l"
    .string "나한테 나눠주지 않을래?$"
	@ ねえ…… もし よかったらｎ
	@ あなたの もってる §いな ものｌ
	@ わたしに わけて くれない かしら?

LilycoveCity_PokemonCenter_1F_Text_WhatWillYouGiveMe: @ 82A8BAD
    .string "...정말? 뭘 줄 거야?$"
	@ ……ほんと? なにを いただけるの?

LilycoveCity_PokemonCenter_1F_Text_IsThatSoGoodbye: @ 82A8BCD
    .string "앗 그래...\n"
    .string "그럼 안녕...$"
	@ あっ そう……ｎ
	@ じゃあ さよならね……

LilycoveCity_PokemonCenter_1F_Text_NotWillingToShare: @ 82A8BEE
    .string "어라... 안 줄 거야?$"
	@ あら…… いただけないの?

LilycoveCity_PokemonCenter_1F_Text_IllTryToCherishIt: @ 82A8C0F
    .string "엣...\n"
    .string "{STR_VAR_2}{K_IGA} {STR_VAR_1}하다고?\p"
    .string "...헤에에 그런가...\p"
    .string "일단 고마워...\n"
    .string "꼭 소중히 할게...$"
	@ えっ……ｎ
	@ §うって §い?ｐ
	@ ……へえぇ そうなの かしらねぇ……ｐ
	@ とりあえず ありがとう……ｎ
	@ きっと たいせつに するわね……

LilycoveCity_PokemonCenter_1F_Text_IWillCherishThis: @ 82A8C6F
    .string "어머...\p"
    .string "제법 {STR_VAR_1}한 {STR_VAR_2}{K_I}네\n"
    .string "멋지다... 황홀해...\p"
    .string "고마워...\n"
    .string "소중히 할게...$"
	@ まぁ……ｐ
	@ なかなか §いな §うねｎ
	@ すてき じゃない…… うっとり するわ……ｐ
	@ ありがとう……ｎ
	@ たいせつに するわね……

LilycoveCity_PokemonCenter_1F_Text_IWillTreasureThis: @ 82A8CC8
    .string "...괴 괴 괴\p"
    .string "굉장해-!\n"
    .string "엄청 {STR_VAR_1}해! {STR_VAR_1}하다고!\p"
    .string "이렇게까지 {STR_VAR_1}한 {STR_VAR_2}{K_IGA}\n"
    .string "세상에 있을 줄은 몰랐어!\p"
    .string "고마워!\p"
    .string "평생 내\n"
    .string "보물처럼 여길게!$"
	@ ……す す すっｐ
	@ すっご-いっ!ｎ
	@ なんて §い! §いなのっ!ｐ
	@ ここまで §いな §うがｎ
	@ よのなかに あるなんて!ｐ
	@ ありがとう!ｐ
	@ いっしょう わたしのｎ
	@ たからものに するわ!

LilycoveCity_PokemonCenter_1F_Text_IllGiveYouThisInReturn: @ 82A8D5D
    .string "멋진 걸 준 답례로\n"
    .string "엄청난 선물을 주.울.게!\p"
    .string "소중히 해줘...$"
	@ すてきな ものを くれた おれいにｎ
	@ とっておきの プレゼントを あ®げ®る!ｌ
	@ だいじにして ちょうだいね……

LilycoveCity_PokemonCenter_1F_Text_YouDontHaveSpaceForIt: @ 82A8DBD
    .string "어머 이미 가득하네...\p"
    .string "도구를 정리하고 나서\n"
    .string "또 오렴...$"
	@ あら もちきれない じゃないの……ｐ
	@ どうぐを せいり してからｎ
	@ また いらっしゃい……

LilycoveCity_PokemonCenter_1F_Text_ImTheQuizLady: @ 82A8E2B
    .string "난 퀴즈아가씨!\n"
    .string "퀴즈가 너-무 좋아!$"
	@ あたし クイズ おねえさん!ｎ
	@ クイズ だ-いすき!

LilycoveCity_PokemonCenter_1F_Text_WaitingToTakeYourQuiz: @ 82A8E4E
    .string "어라?\p"
    .string "지금은 네가 생각한 퀴즈에\n"
    .string "도전할 사람을 찾고 있어!\l"
    .string "그러니까 다음에 얘기하자!$"
	@ あれっ?ｐ
	@ いまは あなたの かんがえた クイズにｎ
	@ チャレンジする ひとを さがしてるの!ｌ
	@ だから また こんどね!

LilycoveCity_PokemonCenter_1F_Text_WaitingForChallenger: @ 82A8EAC
    .string "지금 {STR_VAR_1}{K_IGA} 생각한 퀴즈에\n"
    .string "대답해줄 사람을 찾고 있어!$"
	@ いま §いさんの かんがえた クイズにｎ
	@ こたえて くれる ひとを さがしてるの!

LilycoveCity_PokemonCenter_1F_Text_TakeQuizChallenge: @ 82A8EEC
    .string "정답을 맞추면\n"
    .string "상품을 줄게!\l"
    .string "너 도전해보지 않을래?$"
	@ せいかい したらｎ
	@ しょうひんも あるよ-!ｌ
	@ あなた チャレンジ して みない?

LilycoveCity_PokemonCenter_1F_Text_WaitForAnswer: @ 82A8F4D
    .string "...... ...... ...... ......\n"
    .string "...... ...... ...... ......$"
	@ …… …… …… ……ｎ
	@ …… …… …… ……

LilycoveCity_PokemonCenter_1F_Text_HowBoringBye: @ 82A8F65
    .string "재미없게! 바이바이!$"
	@ つまんないの! バイバイ!

LilycoveCity_PokemonCenter_1F_Text_YoureGoingToQuit: @ 82A8F7E
    .string "엣-! 포기하려고?$"
	@ えっ-! あきらめちゃうの?

LilycoveCity_PokemonCenter_1F_Text_TakeTheQuizAnotherTime: @ 82A8F9A
    .string "다음에 도전해줘!$"
	@ また チャレンジ してね-!

LilycoveCity_PokemonCenter_1F_Text_YouGotItRight: @ 82A8FC7
    .string "굉장해! 정답이야!\n"
    .string "꺄-! 너 센스 있구나-!$"
	@ すっごい! せいかい!ｎ
	@ きゃ-! あなたって センス あるね-!

LilycoveCity_PokemonCenter_1F_Text_YouGotItRightYouveWonPersonsPrize: @ 82A9007
    .string "퀴즈를 맞춘 걸 축하해-!\n"
    .string "{STR_VAR_1}씨로부터의\l"
    .string "보상이 있어-!$"
	@ クイズ せいかい おめでと-!ｎ
	@ §いさん からのｌ
	@ ごほうびが ありま-す!

@ Unused
LilycoveCity_PokemonCenter_1F_Text_XReceivedOneY: @ 82A9056
    .string "{STR_VAR_1}{K_EUNNEUN}\n"
    .string "{STR_VAR_2}{K_EULREUL} 받았다!$"
	@ §いはｎ
	@ §うを もらった!

LilycoveCity_PokemonCenter_1F_Text_YourBagIsFilledUp: @ 82A906A
    .string "어라-? 도구가 가득한 모양이네!\n"
    .string "가방을 정리하고 나서 다시 와줘!$"
	@ あれ-? どうぐが いっぱい みたいだよ!ｎ
	@ バッグを せいり してから また きてね!

LilycoveCity_PokemonCenter_1F_Text_WrongTheCorrectAnswerIs: @ 82A90A5
    .string "으-음… 틀.렸.어!\n"
    .string "정답은 “{STR_VAR_3}”{K_I}야!$"
	@ う-ん…… は®ず®れ!ｎ
	@ せいかいは §えでした!

LilycoveCity_PokemonCenter_1F_Text_IGetToKeepPrize: @ 82A90CD
    .string "아깝네-!\p"
    .string "퀴즈를 맞춘 보상인\n"
	.string "{STR_VAR_1}{K_EUNNEUN}\l"
    .string "내가 가져갈게-!$"
	@ ざんねん でした-!ｐ
	@ クイズ せいかいの しょうひんのｎ
	@ §いはｌ
	@ おねえさんが もらっちゃいま-す!

LilycoveCity_PokemonCenter_1F_Text_MakeYourOwnQuiz: @ 82A90FB
    .string "있지! 있지!\n"
    .string "퀴즈 만들어보지 않을래?$"
	@ ねえ! ねえ! あなたもｎ
	@ クイズ つくって みない?

LilycoveCity_PokemonCenter_1F_Text_MaybeNextTime: @ 82A9131
    .string "그렇구나...\n"
    .string "그럼 다음에 보자!$"
	@ そっか……ｎ
	@ じゃあ- また こんどね!

LilycoveCity_PokemonCenter_1F_Text_PickYourPrize: @ 82A9153
    .string "그럼- 우선\n"
    .string "퀴즈를 맞춘 사람에게\l"
    .string "줄 상품을 정해줘!\p"
    .string "단 퀴즈에 도전한 사람이\n"
    .string "답을 못 맞췄을 때는\l"
	.string "내가 가져갈 거야!\l"
    .string "주의해줘!$"
	@ じゃあ- まずｎ
	@ クイズに せいかいした ひとにｌ
	@ あげる しょうひんを きめてね!ｐ
	@ ただし クイズに チャレンジした ひとがｎ
	@ こたえを はずしちゃった ときはｌ
	@ おねえさんが しょうひん もらっちゃうよ!ｌ
	@ ちゅうい してね!

LilycoveCity_PokemonCenter_1F_Text_QuitChoosingPrize: @ 82A9212
    .string "상품을 정하지 않으면\n"
    .string "퀴즈는 만들 수 없어!\l"
    .string "그만 만들래?$"
	@ しょうひんを きめないとｎ
	@ クイズは できないよ!ｌ
	@ つくるの やめちゃうの?

LilycoveCity_PokemonCenter_1F_Text_WriteYourQuiz: @ 82A9270
    .string "근사한 상품이네!\p"
    .string "그럼 다음으로 퀴즈의\n"
    .string "내용과 답을 생각해줘!$"
	@ すてきな しょうひんだね!ｐ
	@ じゃあ つぎに クイズのｎ
	@ もんだいと こたえを かんがえてね!

LilycoveCity_PokemonCenter_1F_Text_QuitWritingQuizQuestion: @ 82A92D3
    .string "퀴즈의 내용을 안 만들 거야?$"
	@ クイズの もんだい つくるの やめる?

@ Unused
LilycoveCity_PokemonCenter_1F_Text_QuitWritingQuizAnswer: @ 82A9305
    .string "퀴즈의 답을 안 정할 거야?$"
	@ クイズの こたえ きめるの やめる?

LilycoveCity_PokemonCenter_1F_Text_IllLookForAChallenger: @ 82A9336
    .string "수고했어-!\p"
	.string "근사한 퀴즈가 완성됐네!\p"
    .string "바로 도전할 사람을\n"
    .string "찾으러 갔다 올게!$"
	@ おつかれさま-!ｐ
	@ すてきな クイズが できたね!ｐ
	@ さっそく チャレンジ してくれる ひとをｎ
	@ さがしに いって くるね!

LilycoveCity_PokemonCenter_1F_Text_ImTheContestLady: @ 82A93A7
    .string "난 콘테스트아가씨!\n"
    .string "콘테스트가 너무 좋아-!$"
	@ あたし コンテスト おねえさん!ｎ
	@ コンテスト だいすき-!

LilycoveCity_PokemonCenter_1F_Text_ThankForPokeblock: @ 82A93D6
    .string "지난번 포켓몬스넥 고마웠어-!$"
	@ このまえは ポロック ありがと-!

LilycoveCity_PokemonCenter_1F_Text_MyFriendDisplaysQuality: @ 82A93F4
    .string "이쪽은 친구인 {STR_VAR_1}{K_I}야!\n"
    .string "엄-청 {STR_VAR_2}{K_IGA} 넘치지!\p"
    .string "하지만- 좀 더 좀 더\n"
    .string "{STR_VAR_2}{K_EULREUL} 가지고 싶대-!$"
	@ こっちは おともだちの §いだよ!ｎ
	@ と-っても §うい のよ!ｐ
	@ でもね- もっと もっとｎ
	@ §うく なると おもうんだ-!

LilycoveCity_PokemonCenter_1F_Text_DontHaveAPokeblockCase: @ 82A9451
    .string "그러니까 부탁이야-!\p"
    .string "네 포켓몬스넥을 하나라도 좋으니까\n"
    .string "나한테 줘!\p"
    .string "...아니 잠깐만?\n"
    .string "너 포켓몬스넥케이스 없어?\l"
    .string "어쩔 수 없지- 그럼 다음에 봐-!$"
	@ だから おねがい-!ｐ
	@ あなたの ポロック- ひとつで いいからｎ
	@ あたしたちに ちょうだい!ｐ
	@ …… って あれ-?ｎ
	@ あなた ポロックケ-ス もってないじゃん?ｌ
	@ しかたないな- じゃあ また こんどね-!

LilycoveCity_PokemonCenter_1F_Text_AskingForOnePokeblock: @ 82A94E8
    .string "그러니까 부탁이야-!\p"
    .string "네 포켓몬스넥을 하나라도 좋으니까\n"
    .string "나한테 줘!$"
	@ だから おねがい!ｐ
	@ あなたの ポロック ひとつで いいからｎ
	@ あたしたちに ちょうだい!

LilycoveCity_PokemonCenter_1F_Text_ICantHaveOnePokeblock: @ 82A9537
    .string "에-! 포켓몬스넥 안 줄 거야?$"
	@ え-! ポロック くれないの?

LilycoveCity_PokemonCenter_1F_Text_WhatACheapskate: @ 82A9556
    .string "쳇! 이 구두쇠-!$"
	@ ちぇっ! けち-!

LilycoveCity_PokemonCenter_1F_Text_IllUseYourPokeblock: @ 82A9571
    .string "와-아! 해냈다!\p"
    .string "바로 먹여봐야지-!$"
	@ わ-い! やった-!ｐ
	@ さっそく たべさせて みよ-っと!

LilycoveCity_PokemonCenter_1F_Text_NoChangeThanks: @ 82A95AD
    .string "...왠지 전혀\n"
    .string "바뀌지 않은 것 같은데...\p"
    .string "으-음...\p"
    .string "뭐 상관없지!\n"
    .string "정말 고마워-$"
	@ ……なんか ぜんぜんｎ
	@ かわってない ような……ｐ
	@ う-ん……ｐ
	@ まあ いっか!ｎ
	@ どうも ありがと-

LilycoveCity_PokemonCenter_1F_Text_ReallyImprovedThanks: @ 82A9605
    .string "와-아! 엄청 기뻐하고 있어-!\p"
    .string "게다가 {STR_VAR_1}의 {STR_VAR_2}이\n"
    .string "더욱 갈고닦아진 것 같아!\l"
    .string "정말 고마워-!$"
	@ わ-っ! すっごく よろこんでるよ-!ｐ
	@ それに §いの §うさにｎ
	@ みがきが かかった みたい!ｌ
	@ どうも ありがと-!

LilycoveCity_PokemonCenter_1F_Text_ReadyToEnterContests: @ 82A9669
    .string "으-음...\p"
    .string "슬슬 콘테스트에\n"
    .string "참가해볼까-?\p"
    .string "만약 어딘가에서 우리를\n"
    .string "본다면 꼭 응원해줘-!$"
	@ う-ん……ｐ
	@ そろそろ コンテストにｎ
	@ さんかして みようかな-?ｐ
	@ もしも どこかで あたし たちをｎ
	@ みかけたら ぜったい おうえん してね-!

LilycoveCity_PokemonCenter_1F_Text_Zigzagoon: @ 82A96DA
    .string "{STR_VAR_1}: 구우구우!$"
	@ §い『ぐうぐぅ!

LilycoveCity_PokemonCenter_1F_Text_Kecleon: @ 82A96E6
    .string "{STR_VAR_1}: 이기기기이!$"
	@ $§い『いぎぎぎぃ!!

LilycoveCity_PokemonCenter_1F_Text_Poochyena: @ 82A96F6
    .string "{STR_VAR_1}: 바아-앙$"
	@ §い『バア-ゥン ……

LilycoveCity_PokemonCenter_1F_Text_Pikachu: @ 82A9703
    .string "{STR_VAR_1}: 피카!$"
	@ §い『ぴっか!

LilycoveCity_PokemonCenter_1F_Text_Skitty: @ 82A970E
    .string "{STR_VAR_1}: 우뮤아아앙!$"
	@ §い『うみゅぁぁぁん!!
