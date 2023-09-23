// const rom data

ALIGNED(4) static const u8 sText_EmptyString[] = _("");
ALIGNED(4) const u8 sText_Colon[] = _(":");
ALIGNED(4) const u8 sText_ID[] = _("{ID}");
ALIGNED(4) const u8 sText_PleaseStartOver[] = _("다시 한 번 처음부터\n절차를 밟아 주십시오");
ALIGNED(4) const u8 sText_WirelessSearchCanceled[] = _("조이스폿의 검색을\n중지했습니다");
ALIGNED(4) const u8 sText_AwaitingCommunucation2[] = _("친구로부터의 연락을\n기다리고 있습니다"); // Unused
ALIGNED(4) const u8 sText_AwaitingCommunication[] = _("{STR_VAR_1}! 친구로부터의\n연락을 기다리고 있습니다");
ALIGNED(4) const u8 sText_AwaitingLinkPressStart[] = _("{STR_VAR_1}! 연락 대기!\n인원수가 모이면 START 버튼");
ALIGNED(4) const u8 sJPText_SingleBattle[] = _("싱글배틀을 개최한다");
ALIGNED(4) const u8 sJPText_DoubleBattle[] = _("더블배틀을 개최한다");
ALIGNED(4) const u8 sJPText_MultiBattle[] = _("멀티배틀을 개최한다");
ALIGNED(4) const u8 sJPText_TradePokemon[] = _("포켓몬 교환을 개최한다");
ALIGNED(4) const u8 sJPText_Chat[] = _("채팅을 개최한다");
ALIGNED(4) const u8 sJPText_DistWonderCard[] = _("이상한 카드를 나눠준다");
ALIGNED(4) const u8 sJPText_DistWonderNews[] = _("이상한 뉴스를 나눠준다");
ALIGNED(4) const u8 sJPText_DistMysteryEvent[] = _("이상한 사건을 개최한다"); // Unused
ALIGNED(4) const u8 sJPText_HoldPokemonJump[] = _("줄넘기를 개최한다");
ALIGNED(4) const u8 sJPText_HoldBerryCrush[] = _("나무열매크러시를 개최한다");
ALIGNED(4) const u8 sJPText_HoldBerryPicking[] = _("나무열매먹기를 개최한다");
ALIGNED(4) const u8 sJPText_HoldSpinTrade[] = _("빙글빙글 교환을 개최한다");
ALIGNED(4) const u8 sJPText_HoldSpinShop[] = _("빙글빙글 숍을 개최한다");

// Unused
const u8 *const sJPLinkGroupActionTexts[] = {
    sJPText_SingleBattle,
    sJPText_DoubleBattle,
    sJPText_MultiBattle,
    sJPText_TradePokemon,
    sJPText_Chat,
    sJPText_DistWonderCard,
    sJPText_DistWonderNews,
    sJPText_DistWonderCard,
    sJPText_HoldPokemonJump,
    sJPText_HoldBerryCrush,
    sJPText_HoldBerryPicking,
    sJPText_HoldBerryPicking,
    sJPText_HoldSpinTrade,
    sJPText_HoldSpinShop
};

const u8 sText_1PlayerNeeded[] = _("앞으로 1명\n필요함");
const u8 sText_2PlayersNeeded[] = _("앞으로 2명\n필요함");
const u8 sText_3PlayersNeeded[] = _("앞으로 3명\n필요함");
const u8 sText_4PlayersNeeded[] = _("앞으로 4명\n필요함");
const u8 sText_2PlayerMode[] = _("2인용\n플레이");
const u8 sText_3PlayerMode[] = _("3인용\n플레이");
const u8 sText_4PlayerMode[] = _("4인용\n플레이");
const u8 sText_5PlayerMode[] = _("5인용\n플레이");

static const u8 *const sPlayersNeededOrModeTexts[][5] = {
    // 2 players required
    {
        sText_1PlayerNeeded,
        sText_2PlayerMode
    }, 
    // 4 players required
    {
        sText_3PlayersNeeded,
        sText_2PlayersNeeded,
        sText_1PlayerNeeded,
        sText_4PlayerMode
    }, 
    // 2-5 players required
    {
        sText_1PlayerNeeded,
        sText_2PlayerMode,
        sText_3PlayerMode,
        sText_4PlayerMode,
        sText_5PlayerMode
    }, 
    // 3-5 players required
    {
        sText_2PlayersNeeded,
        sText_1PlayerNeeded,
        sText_3PlayerMode,
        sText_4PlayerMode,
        sText_5PlayerMode
    }, 
    // 2-4 players required
    {
        sText_1PlayerNeeded,
        sText_2PlayerMode,
        sText_3PlayerMode,
        sText_4PlayerMode
    }
};

ALIGNED(4) const u8 sText_BButtonCancel[] = _("{B_BUTTON}그만둔다");
ALIGNED(4) const u8 sJPText_SearchingForParticipants[] = _("때문에\n참가자 모집 중입니다!"); // Unused, may have been cut off
ALIGNED(4) const u8 sText_PlayerContactedYouForXAccept[] = _("{STR_VAR_2}에게서 연락 있음!\n{STR_VAR_1}{K_EULREUL} 하시겠습니까?");
ALIGNED(4) const u8 sText_PlayerContactedYouShareX[] = _("{STR_VAR_2}에게서 연락 있음!\n{STR_VAR_1}{K_EULREUL} 나눠주겠습니까?");
ALIGNED(4) const u8 sText_PlayerContactedYouAddToMembers[] = _("{STR_VAR_2}에게서 연락 있음!\n멤버로 받아들이겠습니까?");
ALIGNED(4) const u8 sText_AreTheseMembersOK[] = _("{STR_VAR_1}!\n이 멤버로 괜찮겠습니까?");
ALIGNED(4) const u8 sText_CancelModeWithTheseMembers[] = _("이 멤버로 {STR_VAR_1}{K_EULREUL}\n하는 것을 관두겠습니까?");
ALIGNED(4) const u8 sText_AnOKWasSentToPlayer[] = _("{STR_VAR_1}에게 OK라고\n대답했습니다");
ALIGNED(4) const u8 sText_OtherTrainerUnavailableNow[] = _("상대의\n사정이 나쁜 것 같다...\p");
ALIGNED(4) const u8 sText_CantTransmitTrainerTooFar[] = _("아직 먼 지방 분과는\n통신을 할 수 없습니다\p");
ALIGNED(4) const u8 sText_TrainersNotReadyYet[] = _("상대의 준비가\n되지 않았습니다\p");

static const u8 *const sCantTransmitToTrainerTexts[] = {
    [UR_TRADE_PLAYER_NOT_READY - 1]  = sText_CantTransmitTrainerTooFar,
    [UR_TRADE_PARTNER_NOT_READY - 1] = sText_TrainersNotReadyYet
};

ALIGNED(4) const u8 sText_ModeWithTheseMembersWillBeCanceled[] = _("이 멤버로 {STR_VAR_1}{K_EULREUL}\n하는 것을 그만둡니다{PAUSE 60}");
ALIGNED(4) const u8 sText_MemberNoLongerAvailable[] = _("사정이 나빠진\n멤버가 있습니다\p");

static const u8 *const sPlayerUnavailableTexts[] = {
    sText_OtherTrainerUnavailableNow,
    sText_MemberNoLongerAvailable
};

ALIGNED(4) const u8 sText_TrainerAppearsUnavailable[] = _("사정이 나쁜 것 같다...\p");
ALIGNED(4) const u8 sText_PlayerSentBackOK[] = _("{STR_VAR_1}에게서 OK라는\n대답이 있었습니다!");
ALIGNED(4) const u8 sText_PlayerOKdRegistration[] = _("{STR_VAR_1}에게서 멤버 등록\nOK라는 연락이 왔습니다!");
ALIGNED(4) const u8 sText_PlayerRepliedNo[] = _("{STR_VAR_1}에게서 NG라는\n연락이 왔습니다...\p");
ALIGNED(4) const u8 sText_AwaitingOtherMembers[] = _("{STR_VAR_1}!\n다른 멤버를 기다리고 있습니다!");
ALIGNED(4) const u8 sText_QuitBeingMember[] = _("멤버에서 빠지겠습니까?");
ALIGNED(4) const u8 sText_StoppedBeingMember[] = _("멤버에서 빠졌습니다\p");

static const u8 *const sPlayerDisconnectedTexts[] = {
    [RFU_STATUS_OK]                  = NULL,
    [RFU_STATUS_FATAL_ERROR]         = sText_MemberNoLongerAvailable,
    [RFU_STATUS_CONNECTION_ERROR]    = sText_TrainerAppearsUnavailable,
    [RFU_STATUS_CHILD_SEND_COMPLETE] = NULL,
    [RFU_STATUS_NEW_CHILD_DETECTED]  = NULL,
    [RFU_STATUS_JOIN_GROUP_OK]       = NULL,
    [RFU_STATUS_JOIN_GROUP_NO]       = sText_PlayerRepliedNo,
    [RFU_STATUS_WAIT_ACK_JOIN_GROUP] = NULL,
    [RFU_STATUS_LEAVE_GROUP_NOTICE]  = NULL,
    [RFU_STATUS_LEAVE_GROUP]         = sText_StoppedBeingMember
};

ALIGNED(4) const u8 sText_WirelessLinkEstablished[] = _("조이스폿과의 접속에\n성공했습니다!");
ALIGNED(4) const u8 sText_WirelessLinkDropped[] = _("조이스폿과의 접속이\n끊겼습니다...");
ALIGNED(4) const u8 sText_LinkWithFriendDropped[] = _("친구와의 통신이\n끊겼습니다...");
ALIGNED(4) const u8 sText_PlayerRepliedNo2[] = _("{STR_VAR_1}에게서 NG라는\n대답이 왔습니다...");

const u8 *const sLinkDroppedTexts[] = {
    [RFU_STATUS_OK]                  = NULL,
    [RFU_STATUS_FATAL_ERROR]         = sText_LinkWithFriendDropped,
    [RFU_STATUS_CONNECTION_ERROR]    = sText_LinkWithFriendDropped,
    [RFU_STATUS_CHILD_SEND_COMPLETE] = NULL,
    [RFU_STATUS_NEW_CHILD_DETECTED]  = NULL,
    [RFU_STATUS_JOIN_GROUP_OK]       = NULL,
    [RFU_STATUS_JOIN_GROUP_NO]       = sText_PlayerRepliedNo2,
    [RFU_STATUS_WAIT_ACK_JOIN_GROUP] = NULL,
    [RFU_STATUS_LEAVE_GROUP_NOTICE]  = NULL,
    [RFU_STATUS_LEAVE_GROUP]         = NULL
};

ALIGNED(4) const u8 sText_DoYouWantXMode[] = _("{STR_VAR_2}{K_EULREUL} 하고 싶니?");
ALIGNED(4) const u8 sText_DoYouWantXMode2[] = _("{STR_VAR_2}{K_EULREUL} 하고 싶어?");

// Unused
static const u8 *const sDoYouWantModeTexts[] = {
    sText_DoYouWantXMode,
    sText_DoYouWantXMode2
};

ALIGNED(4) const u8 sText_CommunicatingPleaseWait[] = _("말을 걸고 있습니다...\n잠시 기다려 주십시오"); // Unused
ALIGNED(4) const u8 sText_AwaitingPlayersResponseAboutTrade[] = _("{STR_VAR_1}에게서 교환에 대한\n대답을 기다리고 있습니다...");
ALIGNED(4) const u8 sText_Communicating[] = _("말을 걸고 있습니다{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\n{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.");
ALIGNED(4) const u8 sText_CommunicatingWithPlayer[] = _("{STR_VAR_1}에게 말을 걸고 있습니다{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\n{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.");
ALIGNED(4) const u8 sText_PleaseWaitAWhile[] = _("잠시 기다려 주십시오{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\n{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.");

static const u8 *const sCommunicatingWaitTexts[] = {
    sText_Communicating,
    sText_CommunicatingWithPlayer,
    sText_PleaseWaitAWhile
};

ALIGNED(4) const u8 sText_HiDoSomethingMale[] = _("안녕!\n뭔가 할 거니?");
ALIGNED(4) const u8 sText_HiDoSomethingFemale[] = _("안녕!\n뭔가 할래?");
ALIGNED(4) const u8 sText_HiDoSomethingAgainMale[] = _("{STR_VAR_1}: 안녕 또 만났네!\n이번엔 뭘 할래?");
ALIGNED(4) const u8 sText_HiDoSomethingAgainFemale[] = _("{STR_VAR_1}: 아! {PLAYER}\n안녕! 또 뭔가 할래?");

static const u8 *const sHiDoSomethingTexts[][GENDER_COUNT] = {
    {
        sText_HiDoSomethingMale,
        sText_HiDoSomethingFemale
    }, {
        sText_HiDoSomethingAgainMale,
        sText_HiDoSomethingAgainFemale
    }
};

ALIGNED(4) const u8 sText_DoSomethingMale[] = _("뭔가 할 거니?");
ALIGNED(4) const u8 sText_DoSomethingFemale[] = _("뭔가 할래?");
ALIGNED(4) const u8 sText_DoSomethingAgainMale[] = _("{STR_VAR_1}: 이번엔 뭘 할 거니?");
ALIGNED(4) const u8 sText_DoSomethingAgainFemale[] = _("{STR_VAR_1}: 또 뭔가 할래?"); // Unused

// Unused
static const u8 *const sDoSomethingTexts[][GENDER_COUNT] = {
    {
        sText_DoSomethingMale,
        sText_DoSomethingFemale
    }, {
        sText_DoSomethingAgainMale,
        sText_DoSomethingAgainMale // was probably supposed to be sText_DoSomethingAgainFemale
    }
};

ALIGNED(4) const u8 sText_SomebodyHasContactedYou[] = _("누군가가\n말을 걸어 왔습니다{PAUSE 60}");
ALIGNED(4) const u8 sText_PlayerHasContactedYou[] = _("{STR_VAR_1}{K_IGA}\n말을 걸어 왔습니다{PAUSE 60}");

static const u8 *const sPlayerContactedYouTexts[] = {
    sText_SomebodyHasContactedYou,
    sText_PlayerHasContactedYou
};

ALIGNED(4) const u8 sText_AwaitingResponseFromTrainer[] = _("상대의 대답을\n기다리고 있습니다");
ALIGNED(4) const u8 sText_AwaitingResponseFromPlayer[] = _("{STR_VAR_1}의 대답을\n기다리고 있습니다");

static const u8 *const sAwaitingResponseTexts[] = {
    sText_AwaitingResponseFromTrainer,
    sText_AwaitingResponseFromPlayer
};

ALIGNED(4) const u8 sText_ShowTrainerCard[] = _("상대가 트레이너카드를\n보여줬습니다\p이쪽도 트레이너카드를\n보여줄까요?");
ALIGNED(4) const u8 sText_BattleChallenge[] = _("상대가 대전을\n신청했습니다\p대전하겠습니까?");
ALIGNED(4) const u8 sText_ChatInvitation[] = _("상대가 채팅을\n제안했습니다\p같이 채팅을\n하시겠습니까?");
ALIGNED(4) const u8 sText_OfferToTradeMon[] = _("등록했던\nLV{DYNAMIC 0}인 {DYNAMIC 1}{K_WAGWA}\pLV{DYNAMIC 2}인 {DYNAMIC 3}의\n교환 신청이 들어왔습니다\p교환하겠습니까?");
ALIGNED(4) const u8 sText_OfferToTradeEgg[] = _("등록했던 알의\n교환 신청이 들어왔습니다\l교환하겠습니까?");
ALIGNED(4) const u8 sText_ChatDropped[] = _("대화가 끊겼습니다\p");
ALIGNED(4) const u8 sText_OfferDeclined1[] = _("신청을\n거절했습니다\p");
ALIGNED(4) const u8 sText_OfferDeclined2[] = _("제안을\n거절했습니다\p");
ALIGNED(4) const u8 sText_ChatEnded[] = _("대화를 끊었습니다\p");

// Unused
static const u8 *const sInvitationTexts[] = {
    sText_ShowTrainerCard,
    sText_BattleChallenge,
    sText_ChatInvitation,
    sText_OfferToTradeMon
};

ALIGNED(4) const u8 sText_JoinChatMale[] = _("오! 지금 우린 채팅 중이야!\l괜찮다면 같이 할래?");
ALIGNED(4) const u8 sText_PlayerJoinChatMale[] = _("{STR_VAR_1}: 오! {PLAYER}!\n지금 채팅 중이야!\l괜찮다면 같이 할래?");
ALIGNED(4) const u8 sText_JoinChatFemale[] = _("아! 지금 우린 채팅 중이야\p괜찮다면 같이 하지 않을래?");
ALIGNED(4) const u8 sText_PlayerJoinChatFemale[] = _("{STR_VAR_1}: 아! {PLAYER}!\n지금 채팅 중이야\l괜찮다면 같이 하지 않을래?");

static const u8 *const sJoinChatTexts[][GENDER_COUNT] = {
    {
        sText_JoinChatMale,
        sText_JoinChatFemale
    }, {
        sText_PlayerJoinChatMale,
        sText_PlayerJoinChatFemale
    }
};

ALIGNED(4) const u8 sText_TrainerAppearsBusy[] = _("......\n지금은 바쁜 것 같다\p");
ALIGNED(4) const u8 sText_WaitForBattleMale[] = _("대전이구나!\n좋-아 조금만 기다려!");
ALIGNED(4) const u8 sText_WaitForChatMale[] = _("채팅이구나!\n알았어 조금만 기다려!");
ALIGNED(4) const u8 sText_ShowTrainerCardMale[] = _("알았어! 그럼 인사 대신에\n트레이너카드를 보여줄게");
ALIGNED(4) const u8 sText_WaitForBattleFemale[] = _("대전이구나!\n좋-아 조금만 기다려!");
ALIGNED(4) const u8 sText_WaitForChatFemale[] = _("채팅이구나!\n알았어 조금만 기다려!");
ALIGNED(4) const u8 sText_ShowTrainerCardFemale[] = _("그럼 인사 대신에\n트레이너카드를 보여줄게");

static const u8 *const sText_WaitOrShowCardTexts[GENDER_COUNT][4] = {
    {
        sText_WaitForBattleMale,
        sText_WaitForChatMale,
        NULL,
        sText_ShowTrainerCardMale
    }, {
        sText_WaitForBattleFemale,
        sText_WaitForChatFemale,
        NULL,
        sText_ShowTrainerCardFemale
    }
};

ALIGNED(4) const u8 sText_WaitForChatMale2[] = _("채팅이구나!\n알았어 조금만 기다려!"); // Unused
ALIGNED(4) const u8 sText_DoneWaitingBattleMale[] = _("기다리게 했구나!\n그럼 대전을 해볼까!{PAUSE 60}");
ALIGNED(4) const u8 sText_DoneWaitingChatMale[] = _("좋아! 그럼 같이\n채팅하자!{PAUSE 60}");
ALIGNED(4) const u8 sText_DoneWaitingBattleFemale[] = _("기다렸지!\n그럼 시작하자!{PAUSE 60}");
ALIGNED(4) const u8 sText_DoneWaitingChatFemale[] = _("기다렸지! 그럼 같이\n채팅하자!{PAUSE 60}");
ALIGNED(4) const u8 sText_TradeWillBeStarted[] = _("교환을 시작합니다{PAUSE 60}");
ALIGNED(4) const u8 sText_BattleWillBeStarted[] = _("대전을 시작합니다{PAUSE 60}");
ALIGNED(4) const u8 sText_EnteringChat[] = _("채팅을 시작합니다{PAUSE 60}");

static const u8 *const sStartActivityTexts[][GENDER_COUNT][3] = {
    {
        {
            sText_BattleWillBeStarted,
            sText_EnteringChat,
            sText_TradeWillBeStarted
        }, {
            sText_BattleWillBeStarted,
            sText_EnteringChat,
            sText_TradeWillBeStarted
        }
    }, {
        {
            sText_DoneWaitingBattleMale,
            sText_DoneWaitingChatMale,
            sText_TradeWillBeStarted
        }, {
            sText_DoneWaitingBattleFemale,
            sText_DoneWaitingChatFemale,
            sText_TradeWillBeStarted
        }
    }
};

ALIGNED(4) const u8 sText_BattleDeclinedMale[] = _("미안! 포켓몬의 상태가 나쁜 것 같아\l다음에 또 대전하자\p");
ALIGNED(4) const u8 sText_BattleDeclinedFemale[] = _("미안해!\n포켓몬의 상태가 나쁜 것 같아...\p다음에 또 대전하자\p");

const u8 *const sBattleDeclinedTexts[GENDER_COUNT] = {
    sText_BattleDeclinedMale,
    sText_BattleDeclinedFemale
};

ALIGNED(4) const u8 sText_ShowTrainerCardDeclinedMale[] = _("어라!? 트레이너카드가 안 보이네\l미안! 나중에 보여줄게\p");
ALIGNED(4) const u8 sText_ShowTrainerCardDeclinedFemale[] = _("어머!? 트레이너카드가 어디 갔지...?\l미안! 나중에 보여줄게\p");

const u8 *const sShowTrainerCardDeclinedTexts[GENDER_COUNT] = {
    sText_ShowTrainerCardDeclinedMale,
    sText_ShowTrainerCardDeclinedFemale
};

ALIGNED(4) const u8 sText_IfYouWantToDoSomethingMale[] = _("또 볼일이 있으면\n다시 말을 걸어줘\p");
ALIGNED(4) const u8 sText_IfYouWantToDoSomethingFemale[] = _("또 볼일이 있으면\n다시 말을 걸어줘!");

const u8 *const sIfYouWantToDoSomethingTexts[GENDER_COUNT] = {
    sText_IfYouWantToDoSomethingMale,
    sText_IfYouWantToDoSomethingFemale
};

ALIGNED(4) const u8 sText_TrainerBattleBusy[] = _("미안\n따로 할 일이 있으니까\n다음에 다시 하자\p");
ALIGNED(4) const u8 sText_NeedTwoMonsOfLevel30OrLower1[] = _("대전을 하기 위해서는\n레벨 30 이하의 포켓몬이\l2마리 필요해\p");
ALIGNED(4) const u8 sText_NeedTwoMonsOfLevel30OrLower2[] = _("대전을 하기 위해서는\n레벨 30 이하의 포켓몬이\l2마리 필요합니다\p");

ALIGNED(4) const u8 sText_DeclineChatMale[] = _("그래\n언제든지 또 와!\p");
ALIGNED(4) const u8 stext_DeclineChatFemale[] = _("그래...\n언제든지 또 와줘!\p");

// Response from partner when player declines chat
static const u8 *const sDeclineChatTexts[GENDER_COUNT] = {
    sText_DeclineChatMale,
    stext_DeclineChatFemale
};

ALIGNED(4) const u8 sText_ChatDeclinedMale[] = _("미안!\n역시 지금은 사정이 나빠\n나중에 다시 채팅하자\p");
ALIGNED(4) const u8 sText_ChatDeclinedFemale[] = _("미안!\n역시 지금은 사정이 나쁘거든\n나중에 다시 채팅하자\p");

// Response from partner when they decline chat
static const u8 *const sChatDeclinedTexts[GENDER_COUNT] = {
    sText_ChatDeclinedMale,
    sText_ChatDeclinedFemale
};

ALIGNED(4) const u8 sText_YoureToughMale[] = _("오-!\n만만치 않은데!\p");
ALIGNED(4) const u8 sText_UsedGoodMoveMale[] = _("여기서 그런 기술을\n쓰다니 꽤 하는구나!\p");
ALIGNED(4) const u8 sText_BattleSurpriseMale[] = _("굉장해!\n그런 배틀 방식도 있구나!\p");
ALIGNED(4) const u8 sText_SwitchedMonsMale[] = _("이 포켓몬을\n이런 상황에 쓸 줄이야!\p");
ALIGNED(4) const u8 sText_YoureToughFemale[] = _("그 포켓몬\n굉장히 잘 키웠구나!\p");
ALIGNED(4) const u8 sText_UsedGoodMoveFemale[] = _("그래!\n거기서 이 기술이야!\p");
ALIGNED(4) const u8 sText_BattleSurpriseFemale[] = _("굉장해!\n그런 배틀 방식도 있구나!\p");
ALIGNED(4) const u8 sText_SwitchedMonsFemale[] = _("포켓몬 교대하기의 타이밍이\n절묘하네!\p");

const u8 *const sBattleReactionTexts[GENDER_COUNT][4] = {
    {
        sText_YoureToughMale,
        sText_UsedGoodMoveMale,
        sText_BattleSurpriseMale,
        sText_SwitchedMonsMale
    }, 
    {
        sText_YoureToughFemale,
        sText_UsedGoodMoveFemale,
        sText_BattleSurpriseFemale,
        sText_SwitchedMonsFemale
    }
};

ALIGNED(4) const u8 sText_LearnedSomethingMale[] = _("그렇구나!\n흐음- 음음\p");
ALIGNED(4) const u8 sText_ThatsFunnyMale[] = _("또 이상한 말 해서\n웃게 만들지 마!\p");
ALIGNED(4) const u8 sText_RandomChatMale1[] = _("흐음-\n그런 일이 있었구나\p");
ALIGNED(4) const u8 sText_RandomChatMale2[] = _("...흠흠 뭐야?\n그건 이렇다는 뜻이야?\p");
ALIGNED(4) const u8 sText_LearnedSomethingFemale[] = _("...어?\n그건 몰랐어!\p");
ALIGNED(4) const u8 sText_ThatsFunnyFemale[] = _("아하하!\n그게 뭐야!\p");
ALIGNED(4) const u8 sText_RandomChatFemale1[] = _("아 그래 맞아!\n그거 말이야!\p");
ALIGNED(4) const u8 sText_RandomChatFemale2[] = _("그러니까...\n응! 그거야 그거!\p");

const u8 *const sChatReactionTexts[GENDER_COUNT][4] = {
    {
        sText_LearnedSomethingMale,
        sText_ThatsFunnyMale,
        sText_RandomChatMale1,
        sText_RandomChatMale2
    }, 
    {
        sText_LearnedSomethingFemale,
        sText_ThatsFunnyFemale,
        sText_RandomChatFemale1,
        sText_RandomChatFemale2
    }
};

ALIGNED(4) const u8 sText_ShowedTrainerCardMale1[] = _("지금 인사 대신에\n트레이너카드를 보여주고 있어\p");
ALIGNED(4) const u8 sText_ShowedTrainerCardMale2[] = _("앞으로도 잘 부탁해!\p");
ALIGNED(4) const u8 sText_ShowedTrainerCardFemale1[] = _("지금 인사 대신에\n트레이너카드를 서로 보여주고 있어\p");
ALIGNED(4) const u8 sText_ShowedTrainerCardFemale2[] = _("앞으로도 잘 부탁해!\p");

const u8 *const sTrainerCardReactionTexts[GENDER_COUNT][2] = {
    {
        sText_ShowedTrainerCardMale1,
        sText_ShowedTrainerCardMale2
    }, 
    {
        sText_ShowedTrainerCardFemale1,
        sText_ShowedTrainerCardFemale2
    }
};

ALIGNED(4) const u8 sText_MaleTraded1[] = _("신난다!\n이 포켓몬 가지고 싶었다구!\p");
ALIGNED(4) const u8 sText_MaleTraded2[] = _("찾고 있었던 포켓몬을\n겨우 교환해서 받았어\p");
ALIGNED(4) const u8 sText_FemaleTraded1[] = _("지금 포켓몬\n교환을 하고 있어!\p");
ALIGNED(4) const u8 sText_FemaleTraded2[] = _("갖고 싶은 포켓몬을\n겨우 교환해서 받았어!\p");

const u8 *const sTradeReactionTexts[GENDER_COUNT][4] = {
    {
        sText_MaleTraded1,
        sText_MaleTraded2
    }, 
    {
        sText_FemaleTraded1,
        sText_FemaleTraded2
    }
};

ALIGNED(4) const u8 sText_XCheckedTradingBoard[] = _("{STR_VAR_1}{K_EUNNEUN}\n교환 게시판을 봤다!\p");
ALIGNED(4) const u8 sText_RegisterMonAtTradingBoard[] = _("환영합니다\n여기서는 교환 게시판에\p자신의 포켓몬을\n등록할 수 있습니다\p등록하겠습니까?");
ALIGNED(4) const u8 sText_TradingBoardInfo[] = _("이 교환 게시판에\n포켓몬을 등록해 두면\p게시판을 본 트레이너가\n등록된 포켓몬과\n지닌 포켓몬을\n교환할 수 있습니다\p부디 포켓몬을 등록해서\n여러 트레이너와\l교환을 즐겨 주십시오\p등록하겠습니까?");
ALIGNED(4) const u8 sText_ThankYouForRegistering[] = _("교환 게시판의 등록이\n완료됐습니다\p이용해 주셔서\n정말 감사합니다!\p"); // unused
ALIGNED(4) const u8 sText_NobodyHasRegistered[] = _("게시판에 아무도 포켓몬을\n등록하지 않았습니다\p\n"); // unused
ALIGNED(4) const u8 sText_ChooseRequestedMonType[] = _("가지고 싶은 포켓몬의 타입을\n선택해 주십시오\n");
ALIGNED(4) const u8 sText_WhichMonWillYouOffer[] = _("교환에 내보낼 포켓몬을\n지닌 포켓몬에서 선택해 주십시오\p");
ALIGNED(4) const u8 sText_RegistrationCanceled[] = _("등록을 중지했습니다\p");
ALIGNED(4) const u8 sText_RegistraionCompleted[] = _("등록이 완료됐습니다!\p");
ALIGNED(4) const u8 sText_TradeCanceled[] = _("교환을 취소했습니다!\p");
ALIGNED(4) const u8 sText_CancelRegistrationOfMon[] = _("등록되어 있는 {STR_VAR_1}\n레벨{STR_VAR_2}{K_EULREUL} 해제하겠습니까?");
ALIGNED(4) const u8 sText_CancelRegistrationOfEgg[] = _("등록된 알을\n해제하겠습니까?");
ALIGNED(4) const u8 sText_RegistrationCanceled2[] = _("등록을 해제했습니다\p");
ALIGNED(4) const u8 sText_TradeTrainersWillBeListed[] = _("교환을 원하는 사람을\n표시합니다"); // unused
ALIGNED(4) const u8 sText_ChooseTrainerToTradeWith2[] = _("교환하고 싶은 트레이너를\n선택해 주십시오"); // unused
ALIGNED(4) const u8 sText_AskTrainerToMakeTrade[] = _("{STR_VAR_1}에게 교환을\n신청하겠습니까?");
ALIGNED(4) const u8 sText_AwaitingResponseFromTrainer2[] = _("......\n상대의 응답을 기다리고 있습니다"); // unused
ALIGNED(4) const u8 sText_NotRegisteredAMonForTrade[] = _("당신이 교환에 내보낸\n포켓몬이 등록되어 있지 않습니다\p"); // unused
ALIGNED(4) const u8 sText_DontHaveTypeTrainerWants[] = _("지닌 포켓몬에\n{STR_VAR_1}{K_IGA} 가지고 싶은\l{STR_VAR_2}포켓몬이 없습니다\p");
ALIGNED(4) const u8 sText_DontHaveEggTrainerWants[] = _("{STR_VAR_1}{K_IGA} 가지고 싶은\n알을 지니고 있지 않습니다\p");
ALIGNED(4) const u8 sText_PlayerCantTradeForYourMon[] = _("지금의 {STR_VAR_1}{K_EUNNEUN} 당신의\n포켓몬과 교환할 수 없습니다\p");
ALIGNED(4) const u8 sText_CantTradeForPartnersMon[] = _("{STR_VAR_1}의 포켓몬과는\n현재 교환할 수 없습니다\p");

// Unused
const u8 *const sCantTradeMonTexts[] = {
    sText_PlayerCantTradeForYourMon,
    sText_CantTradeForPartnersMon
};

ALIGNED(4) const u8 sText_TradeOfferRejected[] = _("교환을\n거절당했습니다\p");
ALIGNED(4) const u8 sText_EggTrade[] = _("알 교환");
ALIGNED(4) const u8 sText_ChooseJoinCancel[] = _("{DPAD_UPDOWN}선택:{A_BUTTON}참가한다:{B_BUTTON}그만둔다");
ALIGNED(4) const u8 sText_ChooseTrainer[] = _("친구를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseTrainerSingleBattle[] = _("싱글배틀할 친구를\n선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseTrainerDoubleBattle[] = _("더블배틀할 친구를\n선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseLeaderMultiBattle[] = _("멀티배틀!\n리더를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseTrainerToTradeWith[] = _("포켓몬을 교환할\n친구를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseTrainerToShareWonderCards[] = _("이상한 카드를 나눠주고 있는\n친구를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseTrainerToShareWonderNews[] = _("이상한 뉴스를 나눠주고 있는\n친구를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseLeaderPokemonJump[] = _("미니 포켓몬 점프!\n리더를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseLeaderBerryCrush[] = _("나무열매크러시!\n리더를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseLeaderBerryPicking[] = _("두트리오 나무열매먹기!\n리더를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseLeaderBerryBlender[] = _("나무열매블렌더!\n리더를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseLeaderRecordCorner[] = _("레코드코너!\n리더를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseLeaderCoolContest[] = _("근사함콘테스트!\n리더를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseLeaderBeautyContest[] = _("아름다움콘테스트!\n리더를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseLeaderCuteContest[] = _("귀여움콘테스트!\n리더를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseLeaderSmartContest[] = _("슬기로움콘테스트!\n리더를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseLeaderToughContest[] = _("강인함콘테스트!\n리더를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseLeaderBattleTowerLv50[] = _("배틀타워 레벨 50!\n리더를 선택해 주십시오");
ALIGNED(4) const u8 sText_ChooseLeaderBattleTowerOpenLv[] = _("배틀타워 오픈 레벨!\n리더를 선택해 주십시오");

static const u8 *const sChooseTrainerTexts[NUM_LINK_GROUP_TYPES] = 
{
    [LINK_GROUP_SINGLE_BATTLE]     = sText_ChooseTrainerSingleBattle,
    [LINK_GROUP_DOUBLE_BATTLE]     = sText_ChooseTrainerDoubleBattle,
    [LINK_GROUP_MULTI_BATTLE]      = sText_ChooseLeaderMultiBattle,
    [LINK_GROUP_TRADE]             = sText_ChooseTrainerToTradeWith,
    [LINK_GROUP_POKEMON_JUMP]      = sText_ChooseLeaderPokemonJump,
    [LINK_GROUP_BERRY_CRUSH]       = sText_ChooseLeaderBerryCrush,
    [LINK_GROUP_BERRY_PICKING]     = sText_ChooseLeaderBerryPicking,
    [LINK_GROUP_WONDER_CARD]       = sText_ChooseTrainerToShareWonderCards,
    [LINK_GROUP_WONDER_NEWS]       = sText_ChooseTrainerToShareWonderNews,
    [LINK_GROUP_UNION_ROOM_RESUME] = NULL,
    [LINK_GROUP_UNION_ROOM_INIT]   = NULL,
    [LINK_GROUP_UNK_11]            = NULL,
    [LINK_GROUP_RECORD_CORNER]     = sText_ChooseLeaderRecordCorner,
    [LINK_GROUP_BERRY_BLENDER]     = sText_ChooseLeaderBerryBlender,
    [LINK_GROUP_UNK_14]            = NULL,
    [LINK_GROUP_COOL_CONTEST]      = sText_ChooseLeaderCoolContest,
    [LINK_GROUP_BEAUTY_CONTEST]    = sText_ChooseLeaderBeautyContest,
    [LINK_GROUP_CUTE_CONTEST]      = sText_ChooseLeaderCuteContest,
    [LINK_GROUP_SMART_CONTEST]     = sText_ChooseLeaderSmartContest,
    [LINK_GROUP_TOUGH_CONTEST]     = sText_ChooseLeaderToughContest,
    [LINK_GROUP_BATTLE_TOWER]      = sText_ChooseLeaderBattleTowerLv50,
    [LINK_GROUP_BATTLE_TOWER_OPEN] = sText_ChooseLeaderBattleTowerOpenLv
};

ALIGNED(4) const u8 sText_SearchingForWirelessSystemWait[] = _("조이스폿을 찾고 있습니다\n잠시만 기다려 주십시오");
ALIGNED(4) const u8 sText_MustHaveTwoMonsForDoubleBattle[] = _("더블배틀에서는 2마리 이상의\n포켓몬이 필요합니다\p"); // Unused
ALIGNED(4) const u8 sText_AwaitingPlayersResponse[] = _("{STR_VAR_1}{K_EU}로부터의\n대답을 기다리고 있습니다");
ALIGNED(4) const u8 sText_PlayerHasBeenAskedToRegisterYouPleaseWait[] = _("{STR_VAR_1}에게 멤버 등록을\n부탁하고 있습니다! 기다려 주십시오");
ALIGNED(4) const u8 sText_AwaitingResponseFromWirelessSystem[] = _("조이스폿으로부터의\n대답을 기다리고 있습니다");
ALIGNED(4) const u8 sText_PleaseWaitForOtherTrainersToGather[] = _("다른 참가자가 모일 때까지\n잠시 기다려 주십시오"); // Unused
ALIGNED(4) const u8 sText_NoCardsSharedRightNow[] = _("지금 카드의 배포는\n하고 있지 않은 것 같습니다...");
ALIGNED(4) const u8 sText_NoNewsSharedRightNow[] = _("지금 뉴스의 배포는\n하고 있지 않은 것 같습니다...");

const u8 *const sNoWonderSharedTexts[] = {
    sText_NoCardsSharedRightNow,
    sText_NoNewsSharedRightNow
};

ALIGNED(4) const u8 sText_Battle[] = _("대전");
ALIGNED(4) const u8 sText_Chat2[] = _("채팅");
ALIGNED(4) const u8 sText_Greetings[] = _("인사");
ALIGNED(4) const u8 sText_Exit[] = _("그만둔다");
ALIGNED(4) const u8 sText_Exit2[] = _("닫는다");
ALIGNED(4) const u8 sText_Info[] = _("설명을 듣는다");
ALIGNED(4) const u8 sText_NameWantedOfferLv[] = _("이름{CLEAR_TO 0x3C}원하는 타입{CLEAR_TO 0x6E}줄 포켓몬{CLEAR_TO 0xC6}레벨");
ALIGNED(4) const u8 sText_SingleBattle[] = _("싱글배틀");
ALIGNED(4) const u8 sText_DoubleBattle[] = _("더블배틀");
ALIGNED(4) const u8 sText_MultiBattle[] = _("멀티배틀");
ALIGNED(4) const u8 sText_PokemonTrades[] = _("포켓몬 교환");
ALIGNED(4) const u8 sText_Chat[] = _("채팅");
ALIGNED(4) const u8 sText_Cards[] = _("카드");
ALIGNED(4) const u8 sText_WonderCards[] = _("이상한 카드");
ALIGNED(4) const u8 sText_WonderNews[] = _("이상한 뉴스");
ALIGNED(4) const u8 sText_PokemonJump[] = _("포켓몬점프");
ALIGNED(4) const u8 sText_BerryCrush[] = _("나무열매크러시");
ALIGNED(4) const u8 sText_BerryPicking[] = _("나무열매먹기");
ALIGNED(4) const u8 sText_Search[] = _("서치");
ALIGNED(4) const u8 sText_BerryBlender[] = _("나무열매블렌더");
ALIGNED(4) const u8 sText_RecordCorner[] = _("레코드코너");
ALIGNED(4) const u8 sText_CoolContest[] = _("근사함콘테스트");
ALIGNED(4) const u8 sText_BeautyContest[] = _("아름다움콘테스트");
ALIGNED(4) const u8 sText_CuteContest[] = _("귀여움콘테스트");
ALIGNED(4) const u8 sText_SmartContest[] = _("슬기로움콘테스트");
ALIGNED(4) const u8 sText_ToughContest[] = _("강인함콘테스트");
ALIGNED(4) const u8 sText_BattleTowerLv50[] = _("배틀타워 레벨 50");
ALIGNED(4) const u8 sText_BattleTowerOpenLv[] = _("배틀타워 오픈 레벨");
ALIGNED(4) const u8 sText_ItsNormalCard[] = _("노말카드다!");
ALIGNED(4) const u8 sText_ItsBronzeCard[] = _("브론즈카드다!");
ALIGNED(4) const u8 sText_ItsCopperCard[] = _("코퍼카드다!");
ALIGNED(4) const u8 sText_ItsSilverCard[] = _("실버카드다!");
ALIGNED(4) const u8 sText_ItsGoldCard[] = _("골드카드다!");

static const u8 *const sCardColorTexts[] = {
    sText_ItsNormalCard,
    sText_ItsBronzeCard,
    sText_ItsCopperCard,
    sText_ItsSilverCard,
    sText_ItsGoldCard
};

ALIGNED(4) const u8 sText_TrainerCardInfoPage1[] = _("{DYNAMIC 0} {DYNAMIC 1}의\n트레이너카드를 봤다\l{DYNAMIC 2}\p포켓몬 도감 {DYNAMIC 3}\n플레이 시간 {DYNAMIC 4}:{DYNAMIC 5}\p");
ALIGNED(4) const u8 sText_TrainerCardInfoPage2[] = _("대전 {DYNAMIC 0}승 {DYNAMIC 2}패\n교환 {DYNAMIC 3}회\p“{DYNAMIC 4} {DYNAMIC 5}\n {DYNAMIC 6} {DYNAMIC 7}”\p");
ALIGNED(4) const u8 sText_GladToMeetYouMale[] = _("{DYNAMIC 1}: 앞으로도 잘 부탁해!{PAUSE 60}");
ALIGNED(4) const u8 sText_GladToMeetYouFemale[] = _("{DYNAMIC 1}: 앞으로도 잘 부탁할게!{PAUSE 60}");

const u8 *const sGladToMeetYouTexts[GENDER_COUNT] = {
    sText_GladToMeetYouMale,
    sText_GladToMeetYouFemale
};

ALIGNED(4) const u8 sText_FinishedCheckingPlayersTrainerCard[] = _("{DYNAMIC 1}의 트레이너카드를\n전부 봤다!{PAUSE 60}");

static const u8 *const sLinkGroupActivityNameTexts[] = {
    [ACTIVITY_NONE]              = sText_EmptyString,
    [ACTIVITY_BATTLE_SINGLE]     = sText_SingleBattle,
    [ACTIVITY_BATTLE_DOUBLE]     = sText_DoubleBattle,
    [ACTIVITY_BATTLE_MULTI]      = sText_MultiBattle,
    [ACTIVITY_TRADE]             = sText_PokemonTrades,
    [ACTIVITY_CHAT]              = sText_Chat,
    [ACTIVITY_WONDER_CARD]       = sText_WonderCards,
    [ACTIVITY_WONDER_NEWS]       = sText_WonderNews,
    [ACTIVITY_CARD]              = sText_Cards,
    [ACTIVITY_POKEMON_JUMP]      = sText_PokemonJump,
    [ACTIVITY_BERRY_CRUSH]       = sText_BerryCrush,
    [ACTIVITY_BERRY_PICK]        = sText_BerryPicking,
    [ACTIVITY_SEARCH]            = sText_Search,
    [ACTIVITY_SPIN_TRADE]        = sText_EmptyString,
    [ACTIVITY_BATTLE_TOWER_OPEN] = sText_BattleTowerOpenLv,
    [ACTIVITY_RECORD_CORNER]     = sText_RecordCorner,
    [ACTIVITY_BERRY_BLENDER]     = sText_BerryBlender,
    [ACTIVITY_ACCEPT]            = sText_EmptyString,
    [ACTIVITY_DECLINE]           = sText_EmptyString,
    [ACTIVITY_NPCTALK]           = sText_EmptyString,
    [ACTIVITY_PLYRTALK]          = sText_EmptyString,
    [ACTIVITY_WONDER_CARD2]      = sText_WonderCards,
    [ACTIVITY_WONDER_NEWS2]      = sText_WonderNews,
    [ACTIVITY_CONTEST_COOL]      = sText_CoolContest,
    [ACTIVITY_CONTEST_BEAUTY]    = sText_BeautyContest,
    [ACTIVITY_CONTEST_CUTE]      = sText_CuteContest,
    [ACTIVITY_CONTEST_SMART]     = sText_SmartContest,
    [ACTIVITY_CONTEST_TOUGH]     = sText_ToughContest,
    [ACTIVITY_BATTLE_TOWER]      = sText_BattleTowerLv50
};

static const struct WindowTemplate sWindowTemplate_BButtonCancel = {
    .bg = 0x00,
    .tilemapLeft = 0x00,
    .tilemapTop = 0x00,
    .width = 0x1E,
    .height = 0x02,
    .paletteNum = 0x0F,
    .baseBlock = 0x0008
};

// Minimum and maximum number of players for a link group
// A minimum of 0 means the min and max are equal
#define LINK_GROUP_CAPACITY(min, max)(((min) << 12) | ((max) << 8))
#define GROUP_MAX(capacity)(capacity & 0x0F)
#define GROUP_MIN(capacity)(capacity >> 4)
#define GROUP_MIN2(capacity)(capacity & 0xF0) // Unnecessary to have both, but needed to match

static const u32 sLinkGroupToActivityAndCapacity[NUM_LINK_GROUP_TYPES] = {
    [LINK_GROUP_SINGLE_BATTLE]     = ACTIVITY_BATTLE_SINGLE     | LINK_GROUP_CAPACITY(0, 2),
    [LINK_GROUP_DOUBLE_BATTLE]     = ACTIVITY_BATTLE_DOUBLE     | LINK_GROUP_CAPACITY(0, 2),
    [LINK_GROUP_MULTI_BATTLE]      = ACTIVITY_BATTLE_MULTI      | LINK_GROUP_CAPACITY(0, 4),
    [LINK_GROUP_TRADE]             = ACTIVITY_TRADE             | LINK_GROUP_CAPACITY(0, 2),
    [LINK_GROUP_POKEMON_JUMP]      = ACTIVITY_POKEMON_JUMP      | LINK_GROUP_CAPACITY(2, 5),
    [LINK_GROUP_BERRY_CRUSH]       = ACTIVITY_BERRY_CRUSH       | LINK_GROUP_CAPACITY(2, 5),
    [LINK_GROUP_BERRY_PICKING]     = ACTIVITY_BERRY_PICK        | LINK_GROUP_CAPACITY(3, 5),
    [LINK_GROUP_WONDER_CARD]       = ACTIVITY_NONE              | LINK_GROUP_CAPACITY(0, 0),
    [LINK_GROUP_WONDER_NEWS]       = ACTIVITY_NONE              | LINK_GROUP_CAPACITY(0, 0),
    [LINK_GROUP_UNION_ROOM_RESUME] = ACTIVITY_NONE              | LINK_GROUP_CAPACITY(0, 0),
    [LINK_GROUP_UNION_ROOM_INIT]   = ACTIVITY_NONE              | LINK_GROUP_CAPACITY(0, 0),
    [LINK_GROUP_UNK_11]            = ACTIVITY_NONE              | LINK_GROUP_CAPACITY(0, 0),
    [LINK_GROUP_RECORD_CORNER]     = ACTIVITY_RECORD_CORNER     | LINK_GROUP_CAPACITY(2, 4),
    [LINK_GROUP_BERRY_BLENDER]     = ACTIVITY_BERRY_BLENDER     | LINK_GROUP_CAPACITY(2, 4),
    [LINK_GROUP_UNK_14]            = ACTIVITY_NONE              | LINK_GROUP_CAPACITY(0, 0),
    [LINK_GROUP_COOL_CONTEST]      = ACTIVITY_CONTEST_COOL      | LINK_GROUP_CAPACITY(2, 4),
    [LINK_GROUP_BEAUTY_CONTEST]    = ACTIVITY_CONTEST_BEAUTY    | LINK_GROUP_CAPACITY(2, 4),
    [LINK_GROUP_CUTE_CONTEST]      = ACTIVITY_CONTEST_CUTE      | LINK_GROUP_CAPACITY(2, 4),
    [LINK_GROUP_SMART_CONTEST]     = ACTIVITY_CONTEST_SMART     | LINK_GROUP_CAPACITY(2, 4),
    [LINK_GROUP_TOUGH_CONTEST]     = ACTIVITY_CONTEST_TOUGH     | LINK_GROUP_CAPACITY(2, 4),
    [LINK_GROUP_BATTLE_TOWER]      = ACTIVITY_BATTLE_TOWER      | LINK_GROUP_CAPACITY(0, 2),
    [LINK_GROUP_BATTLE_TOWER_OPEN] = ACTIVITY_BATTLE_TOWER_OPEN | LINK_GROUP_CAPACITY(0, 2)
};

static const struct WindowTemplate sWindowTemplate_PlayerList = {
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 3,
    .width = 13,
    .height = 8,
    .paletteNum = 15,
    .baseBlock = 0x0044
};

static const struct WindowTemplate sWindowTemplate_5PlayerList = {
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 3,
    .width = 13,
    .height = 10,
    .paletteNum = 15,
    .baseBlock = 0x0044
};

static const struct WindowTemplate sWindowTemplate_NumPlayerMode = {
    .bg = 0,
    .tilemapLeft = 16,
    .tilemapTop = 3,
    .width = 7,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = 0x00c6
};

static const struct ListMenuItem sPossibleGroupMembersListMenuItems[] = {
    { sText_EmptyString, 0 },
    { sText_EmptyString, 1 },
    { sText_EmptyString, 2 },
    { sText_EmptyString, 3 },
    { sText_EmptyString, 4 }
};

static const struct ListMenuTemplate sListMenuTemplate_PossibleGroupMembers = {
    .items = sPossibleGroupMembersListMenuItems,
    .moveCursorFunc = NULL,
    .itemPrintFunc = ItemPrintFunc_PossibleGroupMembers,
    .totalItems = ARRAY_COUNT(sPossibleGroupMembersListMenuItems),
    .maxShowed = 5,
    .windowId = 0,
    .header_X = 0,
    .item_X = 0,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = 1,
    .cursorKind = 1
};

const struct WindowTemplate gUnknown_082F0174 = {
    .bg = 0x00,
    .tilemapLeft = 0x01,
    .tilemapTop = 0x03,
    .width = 0x11,
    .height = 0x0a,
    .paletteNum = 0x0f,
    .baseBlock = 0x0044
};

const struct WindowTemplate gUnknown_082F017C = {
    .bg = 0x00,
    .tilemapLeft = 0x14,
    .tilemapTop = 0x03,
    .width = 0x07,
    .height = 0x04,
    .paletteNum = 0x0f,
    .baseBlock = 0x00ee
};

const struct ListMenuItem gUnknown_082F0184[] = {
    { sText_EmptyString,  0 },
    { sText_EmptyString,  1 },
    { sText_EmptyString,  2 },
    { sText_EmptyString,  3 },
    { sText_EmptyString,  4 },
    { sText_EmptyString,  5 },
    { sText_EmptyString,  6 },
    { sText_EmptyString,  7 },
    { sText_EmptyString,  8 },
    { sText_EmptyString,  9 },
    { sText_EmptyString, 10 },
    { sText_EmptyString, 11 },
    { sText_EmptyString, 12 },
    { sText_EmptyString, 13 },
    { sText_EmptyString, 14 },
    { sText_EmptyString, 15 }
};

static const struct ListMenuTemplate sListMenuTemplate_UnionRoomGroups = {
    .items = gUnknown_082F0184,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = ListMenuItemPrintFunc_UnionRoomGroups,
    .totalItems = ARRAY_COUNT(gUnknown_082F0184),
    .maxShowed = 5,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 1,
    .fontId = 1,
    .cursorKind = 0
};

static const struct WindowTemplate sWindowTemplate_InviteToActivity = {
    .bg = 0x00,
    .tilemapLeft = 0x14,
    .tilemapTop = 0x05,
    .width = 0x10,
    .height = 0x08,
    .paletteNum = 0x0f,
    .baseBlock = 0x0001
};

const struct ListMenuItem gUnknown_082F0224[] = {
    { sText_Greetings, 0x208 },
    { sText_Battle, 0x241 },
    { sText_Chat2, 0x245 },
    { sText_Exit, 0x040 }
};

static const struct ListMenuTemplate sListMenuTemplate_InviteToActivity = {
    .items = gUnknown_082F0224,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = NULL,
    .totalItems = ARRAY_COUNT(gUnknown_082F0224),
    .maxShowed = 4,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = 1,
    .cursorKind = 0
};

static const struct WindowTemplate sWindowTemplate_RegisterForTrade = {
    .bg = 0x00,
    .tilemapLeft = 0x12,
    .tilemapTop = 0x07,
    .width = 0x10,
    .height = 0x06,
    .paletteNum = 0x0f,
    .baseBlock = 0x0001
};

static const struct ListMenuItem sRegisterForTradeListMenuItems[] = {
    { gText_Register, 1 },
    { sText_Info, 2 },
    { sText_Exit, 3 }
};

static const struct ListMenuTemplate sListMenuTemplate_RegisterForTrade = {
    .items = sRegisterForTradeListMenuItems,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = NULL,
    .totalItems = ARRAY_COUNT(sRegisterForTradeListMenuItems),
    .maxShowed = 3,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = 1,
    .cursorKind = 0
};

const struct WindowTemplate gUnknown_082F0294 = {
    .bg = 0x00,
    .tilemapLeft = 0x14,
    .tilemapTop = 0x01,
    .width = 0x10,
    .height = 0x0c,
    .paletteNum = 0x0f,
    .baseBlock = 0x0001
};

static const struct ListMenuItem sTradingBoardTypes[NUMBER_OF_MON_TYPES] = {
    { gTypeNames[TYPE_NORMAL],   TYPE_NORMAL         },
    { gTypeNames[TYPE_FIRE],     TYPE_FIRE           },
    { gTypeNames[TYPE_WATER],    TYPE_WATER          },
    { gTypeNames[TYPE_ELECTRIC], TYPE_ELECTRIC       },
    { gTypeNames[TYPE_GRASS],    TYPE_GRASS          },
    { gTypeNames[TYPE_ICE],      TYPE_ICE            },
    { gTypeNames[TYPE_GROUND],   TYPE_GROUND         },
    { gTypeNames[TYPE_ROCK],     TYPE_ROCK           },
    { gTypeNames[TYPE_FLYING],   TYPE_FLYING         },
    { gTypeNames[TYPE_PSYCHIC],  TYPE_PSYCHIC        },
    { gTypeNames[TYPE_FIGHTING], TYPE_FIGHTING       },
    { gTypeNames[TYPE_POISON],   TYPE_POISON         },
    { gTypeNames[TYPE_BUG],      TYPE_BUG            },
    { gTypeNames[TYPE_GHOST],    TYPE_GHOST          },
    { gTypeNames[TYPE_DRAGON],   TYPE_DRAGON         },
    { gTypeNames[TYPE_STEEL],    TYPE_STEEL          },
    { gTypeNames[TYPE_DARK],     TYPE_DARK           },
    { sText_Exit,                NUMBER_OF_MON_TYPES }
};

static const struct ListMenuTemplate sMenuTemplate_TradingBoardRequestType = {
    .items = sTradingBoardTypes,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = NULL,
    .totalItems = ARRAY_COUNT(sTradingBoardTypes),
    .maxShowed = 6,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = 1,
    .cursorKind = 0
};

static const struct WindowTemplate sWindowTemplate_TradingBoard = {
    .bg = 0x00,
    .tilemapLeft = 0x01,
    .tilemapTop = 0x01,
    .width = 0x1c,
    .height = 0x02,
    .paletteNum = 0x0d,
    .baseBlock = 0x0001
};

const struct WindowTemplate gUnknown_082F034C = {
    .bg = 0x00,
    .tilemapLeft = 0x01,
    .tilemapTop = 0x05,
    .width = 0x1c,
    .height = 0x0c,
    .paletteNum = 0x0d,
    .baseBlock = 0x0039
};

static const struct ListMenuItem sTradeBoardListMenuItems[] = {
    { sText_EmptyString, -3 },
    { sText_EmptyString,  0 },
    { sText_EmptyString,  1 },
    { sText_EmptyString,  2 },
    { sText_EmptyString,  3 },
    { sText_EmptyString,  4 },
    { sText_EmptyString,  5 },
    { sText_EmptyString,  6 },
    { sText_EmptyString,  7 },
    { sText_Exit2,  8 }
};

static const struct ListMenuTemplate sTradeBoardListMenuTemplate = {
    .items = sTradeBoardListMenuItems,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = TradeBoardListMenuItemPrintFunc,
    .totalItems = ARRAY_COUNT(sTradeBoardListMenuItems),
    .maxShowed = 6,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 14,
    .fillValue = 15,
    .cursorShadowPal = 13,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = 1,
    .cursorKind = 0
};

const struct WindowTemplate UnrefWindowTemplate_082F03B4 = {
    .bg = 0x00,
    .tilemapLeft = 0x01,
    .tilemapTop = 0x05,
    .width = 0x1c,
    .height = 0x0c,
    .paletteNum = 0x0d,
    .baseBlock = 0x0039
};

static const struct ListMenuItem sEmptyListMenuItems[] = {
    { sText_EmptyString,  0 },
    { sText_EmptyString,  1 },
    { sText_EmptyString,  2 },
    { sText_EmptyString,  3 },
    { sText_EmptyString,  4 },
    { sText_EmptyString,  5 },
    { sText_EmptyString,  6 },
    { sText_EmptyString,  7 },
    { sText_EmptyString,  8 },
    { sText_EmptyString,  9 },
    { sText_EmptyString, 10 },
    { sText_EmptyString, 11 },
    { sText_EmptyString, 12 },
    { sText_EmptyString, 13 },
    { sText_EmptyString, 14 },
    { sText_EmptyString, 15 }
};

// Unused
static const struct ListMenuTemplate sUnknownListMenuTemplate = {
    .items = sEmptyListMenuItems,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = nullsub_14,
    .totalItems = ARRAY_COUNT(sEmptyListMenuItems),
    .maxShowed = 4,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 1,
    .fontId = 1,
    .cursorKind = 0
};

const struct WirelessGnameUnamePair sWirelessGnameUnamePair_Dummy = {0};

ALIGNED(4) const u8 sAcceptedActivityIds_SingleBattle[]    = {ACTIVITY_BATTLE_SINGLE, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_DoubleBattle[]    = {ACTIVITY_BATTLE_DOUBLE, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_MultiBattle[]     = {ACTIVITY_BATTLE_MULTI, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_Trade[]           = {ACTIVITY_TRADE, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_PokemonJump[]     = {ACTIVITY_POKEMON_JUMP, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_BerryCrush[]      = {ACTIVITY_BERRY_CRUSH, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_BerryPicking[]    = {ACTIVITY_BERRY_PICK, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_WonderCard[]      = {ACTIVITY_WONDER_CARD2, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_WonderNews[]      = {ACTIVITY_WONDER_NEWS2, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_Resume[]          = {
    IN_UNION_ROOM | ACTIVITY_NONE, 
    IN_UNION_ROOM | ACTIVITY_BATTLE_SINGLE, 
    IN_UNION_ROOM | ACTIVITY_TRADE, 
    IN_UNION_ROOM | ACTIVITY_CHAT, 
    IN_UNION_ROOM | ACTIVITY_CARD, 
    IN_UNION_ROOM | ACTIVITY_ACCEPT, 
    IN_UNION_ROOM | ACTIVITY_DECLINE, 
    IN_UNION_ROOM | ACTIVITY_NPCTALK, 
    IN_UNION_ROOM | ACTIVITY_PLYRTALK, 
    0xff
};
ALIGNED(4) const u8 sAcceptedActivityIds_Init[]            = {ACTIVITY_SEARCH, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_Unk11[]           = {
    ACTIVITY_BATTLE_SINGLE, 
    ACTIVITY_BATTLE_DOUBLE, 
    ACTIVITY_BATTLE_MULTI, 
    ACTIVITY_TRADE, 
    ACTIVITY_POKEMON_JUMP, 
    ACTIVITY_BERRY_CRUSH, 
    ACTIVITY_BERRY_PICK, 
    ACTIVITY_WONDER_CARD2, 
    ACTIVITY_WONDER_NEWS2, 
    ACTIVITY_SPIN_TRADE, 
    0xff
};
ALIGNED(4) const u8 sAcceptedActivityIds_RecordCorner[]    = {ACTIVITY_RECORD_CORNER, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_BerryBlender[]    = {ACTIVITY_BERRY_BLENDER, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_CoolContest[]     = {ACTIVITY_CONTEST_COOL, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_BeautyContest[]   = {ACTIVITY_CONTEST_BEAUTY, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_CuteContest[]     = {ACTIVITY_CONTEST_CUTE, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_SmartContest[]    = {ACTIVITY_CONTEST_SMART, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_ToughContest[]    = {ACTIVITY_CONTEST_TOUGH, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_BattleTower[]     = {ACTIVITY_BATTLE_TOWER, 0xff};
ALIGNED(4) const u8 sAcceptedActivityIds_BattleTowerOpen[] = {ACTIVITY_BATTLE_TOWER_OPEN, 0xff};

const u8 *const sAcceptedActivityIds[NUM_LINK_GROUP_TYPES] = {
    [LINK_GROUP_SINGLE_BATTLE]     = sAcceptedActivityIds_SingleBattle,
    [LINK_GROUP_DOUBLE_BATTLE]     = sAcceptedActivityIds_DoubleBattle,
    [LINK_GROUP_MULTI_BATTLE]      = sAcceptedActivityIds_MultiBattle,
    [LINK_GROUP_TRADE]             = sAcceptedActivityIds_Trade,
    [LINK_GROUP_POKEMON_JUMP]      = sAcceptedActivityIds_PokemonJump,
    [LINK_GROUP_BERRY_CRUSH]       = sAcceptedActivityIds_BerryCrush,
    [LINK_GROUP_BERRY_PICKING]     = sAcceptedActivityIds_BerryPicking,
    [LINK_GROUP_WONDER_CARD]       = sAcceptedActivityIds_WonderCard,
    [LINK_GROUP_WONDER_NEWS]       = sAcceptedActivityIds_WonderNews,
    [LINK_GROUP_UNION_ROOM_RESUME] = sAcceptedActivityIds_Resume,
    [LINK_GROUP_UNION_ROOM_INIT]   = sAcceptedActivityIds_Init,
    [LINK_GROUP_UNK_11]            = sAcceptedActivityIds_Unk11,
    [LINK_GROUP_RECORD_CORNER]     = sAcceptedActivityIds_RecordCorner,
    [LINK_GROUP_BERRY_BLENDER]     = sAcceptedActivityIds_BerryBlender,
    [LINK_GROUP_UNK_14]            = NULL,
    [LINK_GROUP_COOL_CONTEST]      = sAcceptedActivityIds_CoolContest,
    [LINK_GROUP_BEAUTY_CONTEST]    = sAcceptedActivityIds_BeautyContest,
    [LINK_GROUP_CUTE_CONTEST]      = sAcceptedActivityIds_CuteContest,
    [LINK_GROUP_SMART_CONTEST]     = sAcceptedActivityIds_SmartContest,
    [LINK_GROUP_TOUGH_CONTEST]     = sAcceptedActivityIds_ToughContest,
    [LINK_GROUP_BATTLE_TOWER]      = sAcceptedActivityIds_BattleTower,
    [LINK_GROUP_BATTLE_TOWER_OPEN] = sAcceptedActivityIds_BattleTowerOpen
};

static const u8 sLinkGroupToURoomActivity[NUM_LINK_GROUP_TYPES + 2] = 
{
    [LINK_GROUP_SINGLE_BATTLE]     = ACTIVITY_BATTLE_SINGLE, 
    [LINK_GROUP_DOUBLE_BATTLE]     = ACTIVITY_BATTLE_DOUBLE, 
    [LINK_GROUP_MULTI_BATTLE]      = ACTIVITY_BATTLE_MULTI, 
    [LINK_GROUP_TRADE]             = ACTIVITY_TRADE, 
    [LINK_GROUP_POKEMON_JUMP]      = ACTIVITY_POKEMON_JUMP, 
    [LINK_GROUP_BERRY_CRUSH]       = ACTIVITY_BERRY_CRUSH, 
    [LINK_GROUP_BERRY_PICKING]     = ACTIVITY_BERRY_PICK, 
    [LINK_GROUP_WONDER_CARD]       = ACTIVITY_WONDER_CARD2,
    [LINK_GROUP_WONDER_NEWS]       = ACTIVITY_WONDER_NEWS2, 
    [LINK_GROUP_UNION_ROOM_RESUME] = ACTIVITY_NONE, 
    [LINK_GROUP_UNION_ROOM_INIT]   = ACTIVITY_NONE, 
    [LINK_GROUP_UNK_11]            = ACTIVITY_NONE, 
    [LINK_GROUP_RECORD_CORNER]     = ACTIVITY_RECORD_CORNER, 
    [LINK_GROUP_BERRY_BLENDER]     = ACTIVITY_BERRY_BLENDER, 
    [LINK_GROUP_UNK_14]            = ACTIVITY_NONE, 
    [LINK_GROUP_COOL_CONTEST]      = ACTIVITY_CONTEST_COOL,
    [LINK_GROUP_BEAUTY_CONTEST]    = ACTIVITY_CONTEST_BEAUTY, 
    [LINK_GROUP_CUTE_CONTEST]      = ACTIVITY_CONTEST_CUTE, 
    [LINK_GROUP_SMART_CONTEST]     = ACTIVITY_CONTEST_SMART, 
    [LINK_GROUP_TOUGH_CONTEST]     = ACTIVITY_CONTEST_TOUGH, 
    [LINK_GROUP_BATTLE_TOWER]      = ACTIVITY_BATTLE_TOWER, 
    [LINK_GROUP_BATTLE_TOWER_OPEN] = ACTIVITY_BATTLE_TOWER_OPEN
};
