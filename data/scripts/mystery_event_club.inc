MysteryEventClub_EventScript_Man:: @ 8291539
	lock
	faceplayer
	goto_if_set FLAG_SYS_CHAT_USED, MysteryEventClub_EventScript_GivenProfileBefore
	msgbox MysteryEventClub_Text_CollectTrainerProfiles, MSGBOX_DEFAULT
	goto MysteryEventClub_EventScript_AskToSeeProfile
	end

MysteryEventClub_EventScript_AskToSeeProfile:: @ 8291552
	msgbox MysteryEventClub_Text_MayISeeYourProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, 0
	switch VAR_RESULT
	case 0, MysteryEventClub_EventScript_CreateProfile
	case 1, MysteryEventClub_EventScript_DeclineShowProfile
	case 2, MysteryEventClub_EventScript_Info
	case MULTI_B_PRESSED, MysteryEventClub_EventScript_DeclineShowProfile
	end

MysteryEventClub_EventScript_Info:: @ 8291591
	msgbox MysteryEventClub_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto MysteryEventClub_EventScript_AskToSeeProfile
	end

MysteryEventClub_EventScript_CreateProfile:: @ 829159F
	msgbox MysteryEventClub_Text_LetsSeeItThen, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 0
	goto_if_eq MysteryEventClub_EventScript_CancelShowProfile
	compare VAR_RESULT, 1
	goto_if_eq MysteryEventClub_EventScript_ShowProfile
	end

MysteryEventClub_EventScript_CancelShowProfile:: @ 82915CB
	msgbox MysteryEventClub_Text_NotIntoItRightNow, MSGBOX_DEFAULT
	release
	end

MysteryEventClub_EventScript_ShowProfile:: @ 82915D5
	setvar VAR_0x8004, 0
	special ShowEasyChatProfile
	waitmessage
	delay 80
	msgbox MysteryEventClub_Text_FantasticProfile, MSGBOX_DEFAULT
	release
	end

MysteryEventClub_EventScript_DeclineShowProfile:: @ 82915EB
	msgbox MysteryEventClub_Text_ImagineYouWouldHaveWonderfulProfile, MSGBOX_DEFAULT
	release
	end

MysteryEventClub_EventScript_GivenProfileBefore:: @ 82915F5
	msgbox MysteryEventClub_Text_YouHaveWonderfulSmile, MSGBOX_DEFAULT
	goto MysteryEventClub_EventScript_AskToSeeNewProfile
	end

MysteryEventClub_EventScript_AskToSeeNewProfile:: @ 8291603
	msgbox MysteryEventClub_Text_MayISeeYourNewProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, 0
	switch VAR_RESULT
	case 0, MysteryEventClub_EventScript_CreateNewProfile
	case 1, MysteryEventClub_EventScript_DeclineNewProfile
	case 2, MysteryEventClub_EventScript_InfoNewProfile
	case MULTI_B_PRESSED, MysteryEventClub_EventScript_DeclineNewProfile
	end

MysteryEventClub_EventScript_InfoNewProfile:: @ 8291642
	msgbox MysteryEventClub_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto MysteryEventClub_EventScript_AskToSeeNewProfile
	end

MysteryEventClub_EventScript_CreateNewProfile:: @ 8291650
	msgbox MysteryEventClub_Text_EvenBetterThanLastProfile, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 0
	goto_if_eq MysteryEventClub_EventScript_CancelShowProfile
	compare VAR_RESULT, 1
	goto_if_eq MysteryEventClub_EventScript_ShowProfile
	end

MysteryEventClub_EventScript_DeclineNewProfile:: @ 829167C
	msgbox MysteryEventClub_Text_LikeProfileWayItIs, MSGBOX_DEFAULT
	release
	end

@ Unused
MysteryEventClub_EventScript_Ret:: @ 8291686
	return

MysteryEventClub_Text_CollectTrainerProfiles: @ 8291687
	.string "안녕하세요\n"
	.string "미소가 멋진 트레이너님!\p"
	.string "저는 포켓몬 트레이너들의\n"
	.string "프로필을 모으는 게\l"
	.string "취미인데요...$"
	// こんにちはｎ
	// えがおの すてきな トレ-ナ-さん!ｐ
	// ぼくは ポケモントレ-ナ-さん たちのｎ
	// プロフィ-ルを あつめるのがｌ
	// しゅみ なんだけど……

MysteryEventClub_Text_MayISeeYourProfile: @ 82916FF
	.string "어때요? 당신의 프로필을\n"
	.string "제게 알려 주실 수 있나요?$"
	// どうかな? きみの プロフィ-ルｎ
	// ぼくに おしえて もらえないかな?

MysteryEventClub_Text_EasyChatExplanation: @ 8291729
	.string "프로필은 좋아하는 말을\n"
	.string "4개 조합해서 만들면 돼요!\p"
	.string "지금부터 제가\n"
	.string "적당한 4개의 말로 만든\l"
	.string "프로필을 보여드릴 테니\p"
	.string "당신은 그 말을\n"
	.string "원하는 대로 바꿔서\l"
	.string "자신만의 프로필을 만들면 됩니다!\p"
	.string "쓸 수 있는 말들은\n"
	.string "굉장히 많이 있어요\l"
	.string "그룹별로 나뉘어 있답니다\l"
	.string "포켓몬 생활 취미...\l"
	.string "같은 식으로 말이죠!\p"
	.string "그러니 우선\n"
	.string "그룹을 선택하고...\l"
	.string "그 뒤에 선택한 그룹 안에 있는\l"
	.string "수많은 말들 중에서\l"
	.string "마음에 드는 것을\l"
	.string "고르시면 됩니다!$"
	// プロフィ-ルは すきな ことばをｎ
	// 4つ くみあわせて つくるんだよ!ｐ
	// これから ぼくがｎ
	// てきとうな 4つの ことばで つくったｌ
	// プロフィ-ルを みせるからｐ
	// きみは その ことばをｎ
	// すきなものに いれかえてｌ
	// きみだけの プロフィ-ルに してね!ｐ
	// えらべる ことばはｎ
	// すごく たくさん あるからｌ
	// グル-プに わかれて いるんだｌ
	// ポケモン とか せいかつ とか しゅみ…ｌ
	// という ぐあいにね!ｐ
	// だから まずはｎ
	// グル-プを えらんで……ｌ
	// そのあとに えらんだ グル-プのｌ
	// ことばが いくつも でてくるからｌ
	// そこから すきな ことばをｌ
	// みつけてね!

MysteryEventClub_Text_LetsSeeItThen: @ 8291969
	.string "앗싸! 감사합니다!\n"
	.string "그럼 바로 알려 주세요!$"
	// やった! ありがとう!ｎ
	// じゃ さっそく きかせてよ!

MysteryEventClub_Text_ImagineYouWouldHaveWonderfulProfile: @ 8291991
	.string "그럴 수가...\p"
	.string "당신의 프로필은 무척\n"
	.string "멋질 것 같았는데...$"
	// そんなあ……ｐ
	// きみの プロフィ-ルは さぞかしｎ
	// すてきだと おもうんだけど なぁ……

MysteryEventClub_Text_NotIntoItRightNow: @ 82919DC
	.string "어라? 지금은 내키지 않으신가요?\p"
	.string "뭐 언제든 괜찮습니다!$"
	// あれ? いまは きが のらないんだね?ｐ
	// だったら いつでも いいよ!

MysteryEventClub_Text_YouHaveWonderfulSmile: @ 8291A1B
	.string "안녕하세요\n"
	.string "미소가 멋진 트레이너님!$"
	// こんにちはｎ
	// えがおの すてきな トレ-ナ-さん!

MysteryEventClub_Text_MayISeeYourNewProfile: @ 8291A4F
	.string "당신의 새로운 프로필을\n"
	.string "알려 주실 수 있나요?$"
	// きみの あたらしい プロフィ-ルをｎ
	// おしえて くれるのかな?

MysteryEventClub_Text_EvenBetterThanLastProfile: @ 8291A6B
	.string "앗싸! 감사합니다!\p"
	.string "그럼 전보다 더\n"
	.string "멋진 프로필을 기대할게요!$"
	// やった! ありがとう!ｐ
	// じゃあ まえにも ましてｎ
	// すてきな やつを きたい してるよ!

MysteryEventClub_Text_LikeProfileWayItIs: @ 8291ABA
	.string "지금 그대로도 괜찮으신가요?\p"
	.string "그렇겠죠 무척이나 멋진\n"
	.string "프로필이니까요!$"
	// いまの ままが いいんだね?ｐ
	// そうだよね とても すてきなｎ
	// プロフィ-ル だもの!

MysteryEventClub_Text_FantasticProfile: @ 8291B22
	.string "후 훌륭합니다!\p"
	.string "정말 당신 그 자체의 느낌이 담긴\n"
	.string "멋진 프로필이에요!\p"
	.string "이걸 들은 사람은\n"
	.string "누구든지 당신에게 푹 빠져버리겠죠!\p"
	.string "알려 주셔서 감사합니다!$"
	// すっ すばらしい!ｐ
	// まさに きみ そのもの って かんじのｎ
	// すてきな プロフィ-ル!ｐ
	// これを きいた ひとはｎ
	// だれもが きみの とりこに なるだろうね!ｐ
	// どうも ありがとう!

@ Unused
MysteryEventClub_Text_YouKnowSecretSaying: @ 8291BB7
	.string "이럴 수가!\n"
	.string "그 말을 알고 있을 줄이야...\p"
	.string "그렇다는 건 당신도\n"
	.string "이상한 사건 클럽의 동료란 거군요!$"
	// ややっ!ｎ
	// その ことばを しっている とは……ｐ
	// という ことは きみもｎ
	// ふしぎな できごと クラブの なかま だね!
