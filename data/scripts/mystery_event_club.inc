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
	.string "저는 트레이너들의 프로필을\n"
	.string "모으고 있습니다$"

MysteryEventClub_Text_MayISeeYourProfile: @ 82916FF
	.string "혹시 당신의 프로필을\n"
	.string "한번 봐도 될까요?$"

MysteryEventClub_Text_EasyChatExplanation: @ 8291729
	.string "4개의 단어를 적절히 이용해서\n"
	.string "자신의 트레이너카드에\p"
	.string "적고 싶은 말을\n"
	.string "작성하시면 됩니다!\p"
	.string "여기 제가 4개의 단어로\n"
	.string "적은 프로필을 보여드릴테니\p"
	.string "4개의 단어를 각각 바꿔서\l"
	.string "자신만의 프로필을 만들면 됩니다\p"
	.string "쓸 수 있는 단어들은 많이 있으니\n"
	.string "한번 멋진 프로필을 만들어보세요!\p"
	.string "또한 그룹별로 포켓몬, 생활,\n"
	.string "취미 등으로 나누어져 있으니\l"
	.string "쉽게 만드실 수 있을 거예요!\p"
	.string "제일 먼저 그룹을 고르시면\n"
	.string "해당 그룹의\l"
	.string "단어 리스트가 나옵니다!\p"
	.string "그중에서\n"
	.string "마음에 드는 것을 고르세요!\p"
	.string "그렇게 4개의 단어를 모두 다 바꾸면\n"
	.string "자신만의 프로필이 완성됩니다!$"

MysteryEventClub_Text_LetsSeeItThen: @ 8291969
	.string "네 감사합니다!\n"
	.string "그럼 당신의 프로필을 알려 주세요!$"

MysteryEventClub_Text_ImagineYouWouldHaveWonderfulProfile: @ 8291991
	.string "음 그런가요?\p"
	.string "당신의 프로필은 무척\n"
	.string "멋질 것 같았는데...$"

MysteryEventClub_Text_NotIntoItRightNow: @ 82919DC
	.string "음? 지금은 프로필이\n" 
	.string "생각나지 않으신가요?\p"
	.string "뭐 언제든 괜찮습니다!$"

MysteryEventClub_Text_YouHaveWonderfulSmile: @ 8291A1B
	.string "안녕하세요\n"
	.string "미소가 멋진 트레이너님!$"

MysteryEventClub_Text_MayISeeYourNewProfile: @ 8291A4F
	.string "그럼 당신의\n"
	.string "새로운 프로필을 봐도 될까요?$"

MysteryEventClub_Text_EvenBetterThanLastProfile: @ 8291A6B
	.string "네 감사합니다!\p"
	.string "전보다 더 멋진 프로필을\n"
	.string "기대할게요!$"

MysteryEventClub_Text_LikeProfileWayItIs: @ 8291ABA
	.string "음?\n"
	.string "지금의 프로필로 괜찮으신가요?\p"
	.string "아니아니 싫다고 하는게 아니에요!\n"
	.string "지금도 충분히 멋진\l"
	.string "프로필이라고 생각한답니다!$"

MysteryEventClub_Text_FantasticProfile: @ 8291B22
	.string "후-훌룡합니다!\p"
	.string "정말로 멋진 프로필이에요!!\n"
	.string "당신 그 자체의 프로필...\p"
	.string "듣는 사람은 누구든지\n"
	.string "당신에게 빠져버릴 겁니다!\p"
	.string "멋진 프로필을 알려주셔서\n"
	.string "감사드려요!$"

@ Unused
MysteryEventClub_Text_YouKnowSecretSaying: @ 8291BB7
	.string "음? 당신\n"
	.string "비밀의 말을 알고 있군요!\p"
	.string "그건 이제 당신이\n"
	.string "이상한 사건 클럽의\l"
	.string "회원이라는 뜻이죠!$"
