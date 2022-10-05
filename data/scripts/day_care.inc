.set LOCALID_DAYCARE_LADY, 1

Route117_EventScript_DaycareMan:: @ 8291C18
	lock
	faceplayer
	special GetDaycareMonNicknames
	specialvar VAR_RESULT, GetDaycareState
	compare VAR_RESULT, DAYCARE_EGG_WAITING
	goto_if_eq Route117_EventScript_DaycareEggWaiting
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq Route117_EventScript_CheckOnOneMon
	compare VAR_RESULT, DAYCARE_TWO_MONS
	goto_if_eq Route117_EventScript_CheckOnTwoMons
	msgbox Route117_Text_SeeWifeIfYoudLikeMeToRaiseMon, MSGBOX_DEFAULT
	release
	end

Route117_EventScript_DaycareEggWaiting:: @ 8291C4D
	msgbox Route117_Text_DoYouWantEgg, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route117_EventScript_DaycareAcceptEgg
	msgbox Route117_Text_IWillKeepDoYouWantIt, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route117_EventScript_DaycareAcceptEgg
	msgbox Route117_Text_IllKeepIt, MSGBOX_DEFAULT
	clearflag FLAG_PENDING_DAYCARE_EGG
	special RejectEggFromDayCare
	release
	end

Route117_EventScript_DaycareAcceptEgg:: @ 8291C83
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	compare VAR_RESULT, PARTY_SIZE
	goto_if_ne Route117_EventScript_DaycareReceiveEgg
	msgbox Route117_Text_YouHaveNoRoomForIt, MSGBOX_DEFAULT
	release
	end

Route117_EventScript_DaycareReceiveEgg:: @ 8291C9D
	message Route117_Text_ReceivedEgg
	playfanfare MUS_LEVEL_UP
	waitfanfare
	waitbuttonpress
	msgbox Route117_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	special GiveEggFromDaycare
	clearflag FLAG_PENDING_DAYCARE_EGG
	release
	end

Route117_EventScript_CheckMonReceivedMail:: @ 8291CB7
	specialvar VAR_RESULT, CheckDaycareMonReceivedMail
	compare VAR_RESULT, 1
	call_if_eq Route117_EventScript_MonReceivedMail
	return

Route117_EventScript_MonReceivedMail:: @ 8291CC8
	msgbox Route117_Text_FriendlyWithOtherTrainersMon, MSGBOX_DEFAULT
	return

Route117_EventScript_CheckOnOneMon:: @ 8291CD1
	special GetDaycareMonNicknames
	msgbox Route117_Text_YourMonIsDoingFine, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route117_EventScript_CheckMonReceivedMail
	release
	end

Route117_EventScript_CheckOnTwoMons:: @ 8291CE8
	special GetDaycareMonNicknames
	msgbox Route117_Text_YourMonsAreDoingFine, MSGBOX_DEFAULT
	special SetDaycareCompatibilityString
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, 0
	call Route117_EventScript_CheckMonReceivedMail
	setvar VAR_0x8004, 1
	call Route117_EventScript_CheckMonReceivedMail
	release
	end

Route117_PokemonDayCare_EventScript_DaycareWoman:: @ 8291D11
	lock
	faceplayer
	specialvar VAR_RESULT, GetDaycareState
	compare VAR_RESULT, DAYCARE_EGG_WAITING
	goto_if_eq Route117_PokemonDayCare_EventScript_EggWaiting
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq Route117_PokemonDayCare_EventScript_OneMonInDaycare
	compare VAR_RESULT, DAYCARE_TWO_MONS
	goto_if_eq Route117_PokemonDayCare_EventScript_TwoMonsInDaycare
	msgbox Route117_PokemonDayCare_Text_WouldYouLikeUsToRaiseAMon, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route117_PokemonDayCare_EventScript_GiveMonToRaise
	msgbox Route117_PokemonDayCare_Text_FineThenComeAgain, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_GiveMonToRaise:: @ 8291D56
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, 1
	goto_if_eq Route117_PokemonDayCare_EventScript_OnlyOneMon
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	compare VAR_RESULT, 2
	goto_if_eq Route117_PokemonDayCare_EventScript_OnlyTwoAliveMons
	msgbox Route117_PokemonDayCare_Text_WhichMonShouldWeRaise, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseSendDaycareMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_eq Route117_PokemonDayCare_EventScript_ComeAgain
	specialvar VAR_RESULT, CountPartyAliveNonEggMons_IgnoreVar0x8004Slot
	compare VAR_RESULT, 0
	goto_if_eq Route117_PokemonDayCare_EventScript_OnlyOneAliveMon
	specialvar VAR_0x8005, GetSelectedMonNicknameAndSpecies
	waitse
	playmoncry VAR_0x8005, 0
	msgbox Route117_PokemonDayCare_Text_WellRaiseYourMon, MSGBOX_DEFAULT
	waitmoncry
	special StoreSelectedPokemonInDaycare
	incrementgamestat GAME_STAT_USED_DAYCARE
	specialvar VAR_RESULT, GetDaycareState
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq Route117_PokemonDayCare_EventScript_CanRaiseOneMore
	release
	end

Route117_PokemonDayCare_EventScript_ComeAgain:: @ 8291DCA
	msgbox Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_CanRaiseOneMore:: @ 8291DD4
	msgbox Route117_PokemonDayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route117_PokemonDayCare_EventScript_GiveMonToRaise
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_OnlyOneMon:: @ 8291DED
	msgbox Route117_PokemonDayCare_Text_YouHaveJustOneMon, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_OnlyOneAliveMon:: @ 8291DF7
	msgbox Route117_PokemonDayCare_Text_WhatWillYouBattleWith, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_OnlyTwoAliveMons:: @ 8291E01
	msgbox Route117_PokemonDayCare_Text_YoullBeLeftWithJustOne, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_EggWaiting:: @ 8291E0B
	msgbox Route117_PokemonDayCare_Text_HusbandWasLookingForYou, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_YourMonHasGrownXLevels:: @ 8291E15
	msgbox Route117_PokemonDayCare_Text_YourMonHasGrownXLevels, MSGBOX_DEFAULT
	return

Route117_PokemonDayCare_EventScript_DisplayLevelsGained:: @ 8291E1E
	specialvar VAR_RESULT, GetNumLevelsGainedFromDaycare
	compare VAR_RESULT, 0
	call_if_ne Route117_PokemonDayCare_EventScript_YourMonHasGrownXLevels
	return

Route117_PokemonDayCare_EventScript_OneMonInDaycare:: @ 8291E2F
	msgbox Route117_PokemonDayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	msgbox Route117_PokemonDayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route117_PokemonDayCare_EventScript_GiveMonToRaise
	msgbox Route117_PokemonDayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route117_PokemonDayCare_EventScript_TryRetrieveMon
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_TryRetrieveMon:: @ 8291E6D
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq Route117_PokemonDayCare_EventScript_NoRoom
	specialvar VAR_RESULT, GetDaycareState
	setvar VAR_0x8004, 0
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq Route117_PokemonDayCare_EventScript_CostPrompt
	special ShowDaycareLevelMenu
	waitstate
	copyvar VAR_0x8004, VAR_RESULT
	compare VAR_RESULT, DAYCARE_EXITED_LEVEL_MENU
	goto_if_eq Route117_PokemonDayCare_EventScript_ComeAgain
	goto Route117_PokemonDayCare_EventScript_CostPrompt
	end

Route117_PokemonDayCare_EventScript_CostPrompt:: @ 8291EAC
	special GetDaycareCost
	msgbox Route117_PokemonDayCare_Text_ItWillCostX, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route117_PokemonDayCare_EventScript_CheckEnoughMoney
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_CheckEnoughMoney:: @ 8291EC8
	specialvar VAR_RESULT, IsEnoughForCostInVar0x8005
	compare VAR_RESULT, 1
	goto_if_eq Route117_PokemonDayCare_EventScript_RetrieveMon
	msgbox Route117_PokemonDayCare_Text_NotEnoughMoney, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_RetrieveMon:: @ 8291EE2
	applymovement LOCALID_DAYCARE_LADY, Route117_PokemonDayCare_Movement_RetrieveDaycareMon
	waitmovement 0
	specialvar VAR_RESULT, TakePokemonFromDaycare
	special SubtractMoneyFromVar0x8005
	playse SE_SHOP
	msgbox Route117_PokemonDayCare_Text_HeresYourMon, MSGBOX_DEFAULT
	waitse
	playmoncry VAR_RESULT, 0
	msgbox Route117_PokemonDayCare_Text_TookBackMon, MSGBOX_DEFAULT
	waitmoncry
	specialvar VAR_RESULT, GetDaycareState
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq Route117_PokemonDayCare_EventScript_AskRetrieveOtherMon
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_AskRetrieveOtherMon:: @ 8291F24
	msgbox Route117_PokemonDayCare_Text_TakeOtherOneBackToo, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route117_PokemonDayCare_EventScript_TryRetrieveMon
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_NoRoom:: @ 8291F3D
	msgbox Route117_PokemonDayCare_Text_YourTeamIsFull, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_Movement_RetrieveDaycareMon: @ 8291F47
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	face_right
	delay_16
	delay_16
	face_up
	walk_slow_up
	set_invisible
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_down
	set_visible
	walk_slow_down
	step_end

@ Unused. Possibly a commented script, or a typo end added to the above Movement script
Route117_PokemonDayCare_EventScript_UnusedEnd:: @ 8291F5B
	end

Route117_PokemonDayCare_EventScript_TwoMonsInDaycare:: @ 8291F5C
	msgbox Route117_PokemonDayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	setvar VAR_0x8004, 1
	call Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	msgbox Route117_PokemonDayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route117_PokemonDayCare_EventScript_TryRetrieveMon
	msgbox Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

@ Unused
Route117_PokemonDayCare_EventScript_UnusedRetrieveMon:: @ 8291F95
	special ShowDaycareLevelMenu
	waitstate
	compare VAR_RESULT, 2
	goto_if_eq Route117_PokemonDayCare_EventScript_ComeAgain
	copyvar VAR_0x8004, VAR_RESULT
	specialvar VAR_RESULT, TakePokemonFromDaycare
	msgbox Route117_PokemonDayCare_Text_HeresYourMon, MSGBOX_DEFAULT
	msgbox Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

EventScript_EggHatch:: @ 8291FC0
	lockall
	msgbox Text_EggHatchHuh, MSGBOX_DEFAULT
	special EggHatch
	waitstate
	releaseall
	end

Route117_Text_SeeWifeIfYoudLikeMeToRaiseMon: @ 8291FCF
	.string "나는 키우미집 할아버지라네\p"
	.string "여기서 모두의 소중한\n"
	.string "포켓몬을 돌보고 있지\p"
	.string "뭔가 키우고 싶다면\n"
	.string "할머니에게 부탁하게나$"

Route117_Text_DoYouWantEgg: @ 829205D
	.string "오오! 자네구먼\p"
	.string "맡고 있던 포켓몬을\n"
	.string "키우고 있었더니... 글쎄!\p"
	.string "포켓몬이 알을\n"
	.string "가지고 있었구먼!\p"
	.string "어디서 가져왔는지 모르겠지만\n"
	.string "자네의 포켓몬이 가지고 있던\l"
	.string "알이구먼\p"
	.string "역시 갖고 싶겠지?$"

Route117_Text_YourMonIsDoingFine: @ 8292114
	.string "오오 자네구먼! 잘 왔네\n"
	.string "{STR_VAR_1}{K_EUNNEUN} 잘 있구먼$"

Route117_Text_IllKeepIt: @ 8292149
	.string "그럼 내가 갖겠네\n"
	.string "고맙구먼$"

Route117_Text_YouHaveNoRoomForIt: @ 829216A
	.string "포켓몬이 가득하구먼...\n"
	.string "지닌 포켓몬을 정리하고\l"
	.string "다시 오게나$"

Route117_Text_ReceivedEgg: @ 82921A4
	.string "{PLAYER}{K_EUNNEUN} 키우미집 할아버지에게서\n"
	.string "알을 받았다!$"

Route117_Text_TakeGoodCareOfIt: @ 82921CF
	.string "소중히 키우게!$"

Route117_Text_FriendlyWithOtherTrainersMon: @ 82921E5
	.string "그런데 자네의 {STR_VAR_1}{K_IGA}\p"
	.string "왠지 {STR_VAR_2}의 {STR_VAR_3}{K_WAGWA}\n"
	.string "사이좋게 놀고 있었네\p"
	.string "게다가 아무래도 메일을\n"
	.string "받은 모양이구먼$"
	// ところで あんたの §いじゃがｐ
	// なんか §うとこの §えとｎ
	// なかよく あそんで おったぞｐ
	// しかも なにやら メ-ルをｎ
	// もらっておった ようじゃ

@ Unused
Route117_Text_SeeWifeIfYouWantToPickUpMon: @ 829225A
	.string "포켓몬을 데려가고 싶을 때는\n"
	.string "할머니에게 말해주게$"

Route117_Text_YourMonsAreDoingFine: @ 8292299
	.string "오오 자네구먼! 잘 왔네\n"
	.string "{STR_VAR_1}{K_WAGWA}\l"
	.string "{STR_VAR_2}{K_EUNNEUN} 잘 있구먼!$"

Route117_Text_IWillKeepDoYouWantIt: @ 82922C6
	.string "내가 가져갈지도 모른다네\n"
	.string "사실은 갖고 싶지?$"

Route117_PokemonDayCare_Text_WouldYouLikeUsToRaiseAMon: @ 82922F4
	.string "나는 키우미집 할머니라네\p"
	.string "자네를 대신해서\n"
	.string "포켓몬을 키워주지\p"
	.string "뭔가 키우고 싶은가?$"

Route117_PokemonDayCare_Text_WhichMonShouldWeRaise: @ 8292349
	.string "어느 아이를 키워 볼 텐가?$"

Route117_PokemonDayCare_Text_WellRaiseYourMon: @ 8292370
	.string "그럼 {STR_VAR_1}{K_EULREUL}\n"
	.string "당분간 맡아주겠네\p"
	.string "적당히 시간이\n"
	.string "지나면 다시 오게나$"

Route117_PokemonDayCare_Text_WeCanRaiseOneMore: @ 82923AF
	.string "2마리까지 맡을 수 있는데\n"
	.string "다른 1마리도 키워 볼 텐가?$"

Route117_PokemonDayCare_Text_HusbandWasLookingForYou: @ 82923F6
	.string "할아버지가 자네를\n"
	.string "찾고 있다네$"

Route117_PokemonDayCare_Text_FineThenComeAgain: @ 8292416
	.string "그래\n"
	.string "그럼 또 오게나$"

Route117_PokemonDayCare_Text_NotEnoughMoney: @ 8292432
	.string "돈이 부족한 것 같은데...$"

Route117_PokemonDayCare_Text_TakeOtherOneBackToo: @ 829244F
	.string "다른 1마리도 데리고 갈 텐가?$"

Route117_PokemonDayCare_Text_ComeAgain: @ 8292476
	.string "그럼 또 오게나$"

Route117_PokemonDayCare_Text_GoodToSeeYou: @ 8292488
	.string "오오 자넨가! 잘 왔구먼\n"
	.string "자네 포켓몬은\l"
	.string "잘 있네$"

Route117_PokemonDayCare_Text_YourMonHasGrownXLevels: @ 82924CC
	.string "{STR_VAR_1}{K_EUNNEUN} 레벨로 말하면\n"
	.string "{STR_VAR_2} 정도 자랐구먼$"

Route117_PokemonDayCare_Text_YourTeamIsFull: @ 82924EF
	.string "지닌 포켓몬이 가득이네!\n"
	.string "지닌 포켓몬을 정리하고\l"
	.string "다시 와 주구려$"

@ Unused
Route117_PokemonDayCare_Text_TakeBackWhichMon: @ 8292527
	.string "어느 포켓몬을 데리고 갈 텐가?$"

Route117_PokemonDayCare_Text_ItWillCostX: @ 8292549
	.string "{STR_VAR_1}{K_EULREUL} 데리고 갈 거면\n"
	.string "요금은 {STR_VAR_2}원이구먼$"

Route117_PokemonDayCare_Text_HeresYourMon: @ 8292575
	.string "잘 받았네!\n"
	.string "그럼 데리고 가게나!$"

Route117_PokemonDayCare_Text_TookBackMon: @ 8292593
	.string "{PLAYER}{K_EUNNEUN} 키우미집 할머니한테서\n"
	.string "{STR_VAR_1}{K_EULREUL} 데리고 왔다!$"

Route117_PokemonDayCare_Text_YouHaveJustOneMon: @ 82925BB
	.string "어라? 포켓몬이\n"
	.string "1마리밖에 없구먼\p"
	.string "또 오게나$"

Route117_PokemonDayCare_Text_TakeYourMonBack: @ 82925F6
	.string "포켓몬을 찾아갈 텐가?$"

Route117_PokemonDayCare_Text_WhatWillYouBattleWith: @ 8292617
	.string "그 포켓몬을 맡기면\n"
	.string "싸울 수 없게 되네\p"
	.string "또 오게나$"

Text_EggHatchHuh: @ 8292668
	.string "어라...?$"

Route117_PokemonDayCare_Text_YoullBeLeftWithJustOne: @ 829266D
	.string "어라? 자네\n"
	.string "그 포켓몬을 맡기면\l"
	.string "전부 포켓몬이 1마리밖에\l"
	.string "남지 않게 되는 것 같구먼\p"
	.string "좀 더 포켓몬을 잔뜩 잡고서\n"
	.string "오는 게 어떤가?$"
	// おや? おまえさんｎ
	// その ポケモンを あずけるとｌ
	// ぜんぶで ポケモンが 1ぴき だけにｌ
	// なって しまう みたいじゃなｐ
	// もうちょっと たくさん つかまえてからｎ
	// きてみては どうじゃ?
