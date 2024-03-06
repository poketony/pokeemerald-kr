MauvilleCity_GameCorner_MapScripts:: @ 820FBB8
	.byte 0

    @ Game Corner prices
	.set TM32_COINS,  1500
	.set TM29_COINS,  3500
	.set TM35_COINS,  4000
	.set TM24_COINS,  4000
	.set TM13_COINS,  4000
	.set DOLL_COINS,  1000

	.set COINS_PRICE_50,  1000
	.set COINS_PRICE_500, 10000

MauvilleCity_GameCorner_EventScript_CoinsClerk:: @ 820FBB9
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ThisIsMauvilleGameCorner, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NeedCoinCase
	message MauvilleCity_GameCorner_Text_WereYouLookingForCoins
	waitmessage
	showmoneybox 0, 0, 0
	showcoinsbox 1, 6
	goto MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault50

MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault50:: @ 820FBE5
	multichoicedefault 15, 0, MULTI_GAME_CORNER_COINS, 0, 0
	switch VAR_RESULT
	case 0, MauvilleCity_GameCorner_EventScript_Buy50Coins
	case 1, MauvilleCity_GameCorner_EventScript_Buy500Coins
	goto MauvilleCity_GameCorner_EventScript_CancelBuyCoins
	end

@ Unused
MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault500:: @ 820FC0C
	multichoicedefault 15, 0, MULTI_GAME_CORNER_COINS, 1, 0
	switch VAR_RESULT
	case 0, MauvilleCity_GameCorner_EventScript_Buy50Coins
	case 1, MauvilleCity_GameCorner_EventScript_Buy500Coins
	goto MauvilleCity_GameCorner_EventScript_CancelBuyCoins
	end

MauvilleCity_GameCorner_EventScript_Buy50Coins:: @ 820FC33
	checkcoins VAR_TEMP_1
	compare VAR_TEMP_1, (MAX_COINS + 1 - 50)
	goto_if_ge MauvilleCity_GameCorner_EventScript_NoRoomForCoins
	checkmoney COINS_PRICE_50, 0
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NotEnoughMoney
	addcoins 50
	removemoney COINS_PRICE_50, 0
	updatemoneybox 0, 0
	updatecoinsbox 1, 6
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox 0, 5
	release
	end

MauvilleCity_GameCorner_EventScript_Buy500Coins:: @ 820FC75
	checkcoins VAR_TEMP_1
	compare VAR_TEMP_1, (MAX_COINS + 1 - 500)
	goto_if_ge MauvilleCity_GameCorner_EventScript_NoRoomForCoins
	checkmoney COINS_PRICE_500, 0
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NotEnoughMoney
	addcoins 500
	removemoney COINS_PRICE_500, 0
	updatemoneybox 0, 0
	updatecoinsbox 1, 6
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox 0, 5
	release
	end

MauvilleCity_GameCorner_EventScript_NeedCoinCase:: @ 820FCB7
	msgbox MauvilleCity_GameCorner_Text_NeedCoinCaseForCoins, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_NotEnoughMoney:: @ 820FCC1
	msgbox MauvilleCity_GameCorner_Text_DontHaveEnoughMoney, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox 0, 5
	release
	end

MauvilleCity_GameCorner_EventScript_CancelBuyCoins:: @ 820FCD1
	msgbox MauvilleCity_GameCorner_Text_DontNeedCoinsThen, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox 0, 5
	release
	end

MauvilleCity_GameCorner_EventScript_NoRoomForCoins:: @ 820FCE1
	msgbox MauvilleCity_GameCorner_Text_CoinCaseIsFull, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox 0, 5
	release
	end

MauvilleCity_GameCorner_EventScript_PrizeCornerDolls:: @ 820FCF1
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_GameCorner_EventScript_ChooseDollPrizeMessage
	release
	end

MauvilleCity_GameCorner_EventScript_ChooseDollPrizeMessage:: @ 820FD0D
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	setvar VAR_TEMP_1, 0
	showcoinsbox 1, 1
	goto MauvilleCity_GameCorner_EventScript_ChooseDollPrize

MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize:: @ 820FD20
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	goto MauvilleCity_GameCorner_EventScript_ChooseDollPrize

MauvilleCity_GameCorner_EventScript_ChooseDollPrize:: @ 820FD2B
	multichoice 12, 0, MULTI_GAME_CORNER_DOLLS, 0
	switch VAR_RESULT
	case 0, MauvilleCity_GameCorner_EventScript_TreeckoDoll
	case 1, MauvilleCity_GameCorner_EventScript_TorchicDoll
	case 2, MauvilleCity_GameCorner_EventScript_MudkipDoll
	case 3, MauvilleCity_GameCorner_EventScript_CancelDollSelect
	goto MauvilleCity_GameCorner_EventScript_CancelDollSelect
	end

MauvilleCity_GameCorner_EventScript_TreeckoDoll:: @ 820FD67
	setvar VAR_TEMP_1, 1
	bufferdecorationname 0, DECOR_TREECKO_DOLL
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize

MauvilleCity_GameCorner_EventScript_TorchicDoll:: @ 820FD75
	setvar VAR_TEMP_1, 2
	bufferdecorationname 0, DECOR_TORCHIC_DOLL
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize

MauvilleCity_GameCorner_EventScript_MudkipDoll:: @ 820FD83
	setvar VAR_TEMP_1, 3
	bufferdecorationname 0, DECOR_MUDKIP_DOLL
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize

MauvilleCity_GameCorner_EventScript_ConfirmDollPrize:: @ 820FD91
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsX, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_GameCorner_EventScript_CancelDollSelect
	switch VAR_TEMP_1
	case 1, MauvilleCity_GameCorner_EventScript_BuyTreeckoDoll
	case 2, MauvilleCity_GameCorner_EventScript_BuyTorchicDoll
	case 3, MauvilleCity_GameCorner_EventScript_BuyMudkipDoll
	end

MauvilleCity_GameCorner_EventScript_BuyTreeckoDoll:: @ 820FDCB
	checkcoins VAR_TEMP_2
	compare VAR_TEMP_2, DOLL_COINS
	goto_if_lt MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
	bufferdecorationname 1, DECOR_TREECKO_DOLL
	checkdecorspace DECOR_TREECKO_DOLL
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoRoomForDoll
	removecoins DOLL_COINS
	adddecoration DECOR_TREECKO_DOLL
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTorchicDoll:: @ 820FE05
	checkcoins VAR_TEMP_2
	compare VAR_TEMP_2, DOLL_COINS
	goto_if_lt MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
	bufferdecorationname 1, DECOR_TORCHIC_DOLL
	checkdecorspace DECOR_TORCHIC_DOLL
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoRoomForDoll
	removecoins DOLL_COINS
	adddecoration DECOR_TORCHIC_DOLL
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_BuyMudkipDoll:: @ 820FE3F
	checkcoins VAR_TEMP_2
	compare VAR_TEMP_2, DOLL_COINS
	goto_if_lt MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
	bufferdecorationname 1, DECOR_MUDKIP_DOLL
	checkdecorspace DECOR_MUDKIP_DOLL
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoRoomForDoll
	removecoins DOLL_COINS
	adddecoration DECOR_MUDKIP_DOLL
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll:: @ 820FE79
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_NoRoomForDoll:: @ 820FE87
	call Common_EventScript_NoRoomForDecor
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_CancelDollSelect:: @ 820FE92
	msgbox MauvilleCity_GameCorner_Text_OhIsThatSo, MSGBOX_DEFAULT
	hidecoinsbox 0, 0
	release
	end

MauvilleCity_GameCorner_EventScript_PrizeCornerTMs:: @ 820FE9F
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_GameCorner_EventScript_ChooseTMPrizeMessage
	release
	end

MauvilleCity_GameCorner_EventScript_ChooseTMPrizeMessage:: @ 820FEBB
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	setvar VAR_TEMP_1, 0
	showcoinsbox 1, 1
	goto MauvilleCity_GameCorner_EventScript_ChooseTMPrize

MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize:: @ 820FECE
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	goto MauvilleCity_GameCorner_EventScript_ChooseTMPrize

MauvilleCity_GameCorner_EventScript_ChooseTMPrize:: @ 820FED9
	multichoice 12, 0, MULTI_GAME_CORNER_TMS, 0
	switch VAR_RESULT
	case 0, MauvilleCity_GameCorner_EventScript_TM32
	case 1, MauvilleCity_GameCorner_EventScript_TM29
	case 2, MauvilleCity_GameCorner_EventScript_TM35
	case 3, MauvilleCity_GameCorner_EventScript_TM24
	case 4, MauvilleCity_GameCorner_EventScript_TM13
	case 5, MauvilleCity_GameCorner_EventScript_CancelTMSelect
	goto MauvilleCity_GameCorner_EventScript_CancelTMSelect
	end

MauvilleCity_GameCorner_EventScript_TM32:: @ 820FF2B
	setvar VAR_TEMP_1, 1
	bufferitemname 0, ITEM_TM32
	setvar VAR_0x8004, ITEM_TM32
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TM29:: @ 820FF3E
	setvar VAR_TEMP_1, 2
	bufferitemname 0, ITEM_TM29
	setvar VAR_0x8004, ITEM_TM29
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TM35:: @ 820FF51
	setvar VAR_TEMP_1, 3
	bufferitemname 0, ITEM_TM35
	setvar VAR_0x8004, ITEM_TM35
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TM24:: @ 820FF64
	setvar VAR_TEMP_1, 4
	bufferitemname 0, ITEM_TM24
	setvar VAR_0x8004, ITEM_TM24
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TM13:: @ 820FF77
	setvar VAR_TEMP_1, 5
	bufferitemname 0, ITEM_TM13
	setvar VAR_0x8004, ITEM_TM13
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_ConfirmTMPrize:: @ 820FF8A
	special BufferTMHMMoveName
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsTheTMX, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_GameCorner_EventScript_CancelTMSelect
	switch VAR_TEMP_1
	case 1, MauvilleCity_GameCorner_EventScript_BuyTM32
	case 2, MauvilleCity_GameCorner_EventScript_BuyTM29
	case 3, MauvilleCity_GameCorner_EventScript_BuyTM35
	case 4, MauvilleCity_GameCorner_EventScript_BuyTM24
	case 5, MauvilleCity_GameCorner_EventScript_BuyTM13
	end

MauvilleCity_GameCorner_EventScript_BuyTM32:: @ 820FFDD
	checkcoins VAR_TEMP_2
	compare VAR_TEMP_2, TM32_COINS
	goto_if_lt MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM32, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM32_COINS
	additem ITEM_TM32
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTM29:: @ 8210017
	checkcoins VAR_TEMP_2
	compare VAR_TEMP_2, TM29_COINS
	goto_if_lt MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM29, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM29_COINS
	additem ITEM_TM29
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTM35:: @ 8210051
	checkcoins VAR_TEMP_2
	compare VAR_TEMP_2, TM35_COINS
	goto_if_lt MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM35, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM35_COINS
	additem ITEM_TM35
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTM24:: @ 821008B
	checkcoins VAR_TEMP_2
	compare VAR_TEMP_2, TM24_COINS
	goto_if_lt MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM24, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM24_COINS
	additem ITEM_TM24
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTM13:: @ 82100C5
	checkcoins VAR_TEMP_2
	compare VAR_TEMP_2, TM13_COINS
	goto_if_lt MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM13, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM13_COINS
	additem ITEM_TM13
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM:: @ 82100FF
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_NoRoomForTM:: @ 821010D
	call Common_EventScript_BagIsFull
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_CancelTMSelect:: @ 8210118
	msgbox MauvilleCity_GameCorner_Text_OhIsThatSo, MSGBOX_DEFAULT
	hidecoinsbox 0, 0
	release
	end

MauvilleCity_GameCorner_EventScript_Woman2:: @ 8210125
	msgbox MauvilleCity_GameCorner_Text_CoinsAreNeededToPlay, MSGBOX_NPC
	end

MauvilleCity_GameCorner_EventScript_Gentleman:: @ 821012E
	msgbox MauvilleCity_GameCorner_Text_RouletteOnlyLuck, MSGBOX_NPC
	end

MauvilleCity_GameCorner_EventScript_Girl:: @ 8210137
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_STARTER_DOLL, MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
	msgbox MauvilleCity_GameCorner_Text_GotTwoOfSameDollWantOne, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_GameCorner_EventScript_DeclineStarterDoll
	switch VAR_STARTER_MON
	case 0, MauvilleCity_GameCorner_EventScript_GiveTreeckoDoll
	case 1, MauvilleCity_GameCorner_EventScript_GiveTorchicDoll
	case 2, MauvilleCity_GameCorner_EventScript_GiveMudkipDoll
	end

MauvilleCity_GameCorner_EventScript_GiveTreeckoDoll:: @ 821017C
	bufferdecorationname 1, DECOR_TREECKO_DOLL
	checkdecorspace DECOR_TREECKO_DOLL
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
	givedecoration DECOR_TREECKO_DOLL
	setflag FLAG_RECEIVED_STARTER_DOLL
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
	end

MauvilleCity_GameCorner_EventScript_GiveTorchicDoll:: @ 82101A6
	bufferdecorationname 1, DECOR_TORCHIC_DOLL
	checkdecorspace DECOR_TORCHIC_DOLL
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
	givedecoration DECOR_TORCHIC_DOLL
	setflag FLAG_RECEIVED_STARTER_DOLL
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
	end

MauvilleCity_GameCorner_EventScript_GiveMudkipDoll:: @ 82101D0
	bufferdecorationname 1, DECOR_MUDKIP_DOLL
	checkdecorspace DECOR_MUDKIP_DOLL
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
	givedecoration DECOR_MUDKIP_DOLL
	setflag FLAG_RECEIVED_STARTER_DOLL
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
	end

MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll:: @ 82101FA
	call Common_EventScript_NoRoomForDecor
	msgbox MauvilleCity_GameCorner_Text_YouWantItButNotNow, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_DeclineStarterDoll:: @ 8210209
	msgbox MauvilleCity_GameCorner_Text_DontBeNegative, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll:: @ 8210213
	msgbox MauvilleCity_GameCorner_Text_CantWinJackpot, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_PokefanM:: @ 821021D
	lock
	faceplayer
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_GameCorner_EventScript_TryGive20Coins
	msgbox MauvilleCity_GameCorner_Text_NeedCoinCaseGoNextDoor, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_TryGive20Coins:: @ 821023D
	goto_if_set FLAG_RECEIVED_20_COINS, MauvilleCity_GameCorner_EventScript_PokefanMNormal
	checkcoins VAR_TEMP_1
	compare VAR_TEMP_1, 1  @ Only give 20 coins if player has no coins
	goto_if_ge MauvilleCity_GameCorner_EventScript_PokefanMNormal
	setflag FLAG_RECEIVED_20_COINS
	addcoins 20
	msgbox MauvilleCity_GameCorner_Text_LuckOnlyLastSoLongTakeCoins, MSGBOX_DEFAULT
	playse SE_SHOP
	goto MauvilleCity_GameCorner_EventScript_PokefanMNormal
	end

MauvilleCity_GameCorner_EventScript_PokefanMNormal:: @ 821026B
	msgbox MauvilleCity_GameCorner_Text_MauvilleSomethingForEveryone, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_OldMan:: @ 8210279
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_RouletteTablesDifferentRates, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_Cook:: @ 8210289
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_EasyToLoseTrackOfTime, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_Man:: @ 8210299
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_UpTo3CoinsCanBeUsed, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_NPCReturnToSlots:: @ 82102A9
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_GameCorner_EventScript_Maniac:: @ 82102B6
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_DifficultToStopOn7, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_Woman:: @ 82102C6
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_HeresSomeSlotsInfo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_SlotMachine0:: @ 82102D6
	lockall
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine1:: @ 82102F6
	lockall
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine2:: @ 8210316
	lockall
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 2
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine3:: @ 8210336
	lockall
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 3
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine4:: @ 8210356
	lockall
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 4
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine5:: @ 8210376
	lockall
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 5
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine6:: @ 8210396
	lockall
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 6
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine7:: @ 82103B6
	lockall
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 7
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine8:: @ 82103D6
	lockall
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 8
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine9:: @ 82103F6
	lockall
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 9
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine10:: @ 8210416
	lockall
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 10
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine11:: @ 8210436
	lockall
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 11
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_NoCoinCase:: @ 8210456
	msgbox MauvilleCity_GameCorner_Text_CantPlayWithNoCoinCase, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_GameCorner_Text_ThisIsMauvilleGameCorner: @ 8210460
	.string "어서 오세요!\n"
	.string "보라시티 게임코너입니다!$"
	@ いらっしゃいませ!ｎ
	@ キンセツ ゲ-ムコ-ナ- です!

MauvilleCity_GameCorner_Text_NeedCoinCaseForCoins: @ 821047E
	.string "게임용 동전 말이죠?\p"
	.string "어머? 동전을 넣는\n"
	.string "동전케이스가 없네요$"
	@ ゲ-ムよう コイン ですね?ｐ
	@ あら? コインを いれるｎ
	@ コインケ-スが ありませんよ

MauvilleCity_GameCorner_Text_WereYouLookingForCoins: @ 82104DF
	.string "게임용 동전 말이죠?\p"
	.string "50개에 1000원입니다!\n"
	.string "동전을 사시겠습니까?$"
	@ ゲ-ムよう コイン ですね?ｐ
	@ 50まい 1000えんに なります!ｎ
	@ コインを かいますか?

MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins: @ 8210529
	.string "네 감사합니다!\n"
	.string "동전입니다! 여기 있습니다!$"
	@ はい ありがとう ございます!ｎ
	@ コイン です! どうぞ!

MauvilleCity_GameCorner_Text_DontHaveEnoughMoney: @ 8210553
	.string "저기...\n"
	.string "돈이 부족한 것 같아요$"
	@ あの……ｎ
	@ おかねが たりないようです

MauvilleCity_GameCorner_Text_CoinCaseIsFull: @ 821057E
	.string "어머?\n"
	.string "동전케이스가 가득 찼네요$"
	@ あら?ｎ
	@ コインケ-スが まんたん ですね

MauvilleCity_GameCorner_Text_DontNeedCoinsThen: @ 821059A
	.string "... 필요 없으시군요!\n"
	.string "그럼 또 와주세요!$"
	@ …… いりませんか!ｎ
	@ それでは また きてくださいね!

MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes: @ 82105D7
	.string "어서 오세요!\p"
	.string "여기서는 게임으로 쌓은 동전을\n"
	.string "마음에 드는 경품과 교환합니다!$"
	@ いらっしゃいませ!ｐ
	@ こちらでは ゲ-ムで ためた コインをｎ
	@ おすきな けいひんと こうかん します!

MauvilleCity_GameCorner_Text_WhichPrize: @ 821060D
	.string "어느 것이 좋으세요?$"
	@ どれが いいですか?

MauvilleCity_GameCorner_Text_SoYourChoiceIsTheTMX: @ 8210629
	.string "{STR_VAR_1} {STR_VAR_2}{K_EU}로\n"
	.string "괜찮으신 거죠?$"
	@ §い「§う」でｎ
	@ いいですね?

MauvilleCity_GameCorner_Text_SendToYourHomePC: @ 8210646
	.string "감사합니다!\n"
	.string "집에 있는 PC에 보내둘게요!$"
	@ どうも ありがとう!ｎ
	@ じたくの パソコンに おくって おきますね!

MauvilleCity_GameCorner_Text_NotEnoughCoins: @ 8210673
	.string "동전이 모자라네요$"
	@ コインが たりませんね

@ Unused
MauvilleCity_GameCorner_Text_NoRoomForPlacingDecor: @ 8210690
	.string "{STR_VAR_1}{K_EULREUL}\n"
	.string "놓을 장소가 없습니다$"
	@ §い をｎ
	@ いれる ばしょが いっぱいですよ

MauvilleCity_GameCorner_Text_OhIsThatSo: @ 82106BF
	.string "어머 그렇군요\n"
	.string "동전 모아서 와주세요!$"
	@ あら そうですかｎ
	@ コイン ためて きてくださいね!

MauvilleCity_GameCorner_Text_SoYourChoiceIsX: @ 8210705
	.string "{STR_VAR_1}{K_EU}로\n"
	.string "괜찮으신 거죠?$"
	@ §いでｎ
	@ いいですね?$

MauvilleCity_GameCorner_Text_HereYouGo: @ 821071B
	.string "네 여기 있습니다!$"
	@ はい どうぞ!

@ Unused
MauvilleCity_GameCorner_Text_CantCarryAnyMore: @ 8210728
	.string "그 이상 가지실 수 없습니다$"
	@ それいじょう もてない ですよ

MauvilleCity_GameCorner_Text_GotTwoOfSameDollWantOne: @ 8210750
	.string "실수로 같은 인형을\n"
	.string "2개씩이나 사고 말았어!\p"
	.string "너한테 하나 줄까?$"
	@ うっかり おんなじｎ
	@ ぬいぐるみを もらっちゃった!ｐ
	@ ひとつ あなたに わけてあげようか?

MauvilleCity_GameCorner_Text_HereYouGo2: @ 821079C
	.string "자 여기 받아!$"
	@ はい どうぞ!

MauvilleCity_GameCorner_Text_YouWantItButNotNow: @ 82107A9
	.string "음? 갖고 싶지만\n"
	.string "지금은 안 되는 거야-?$"
	@ え- ほしいけどｎ
	@ いまは ダメなの-?

MauvilleCity_GameCorner_Text_DontBeNegative: @ 82107CE
	.string "그런 말 하지 말고 받아!$"
	@ そんなこと いわずに もらってよ!

MauvilleCity_GameCorner_Text_CantWinJackpot: @ 82107FB
	.string "갖고 싶은 경품이 있어서\n"
	.string "당첨을 노리고 있어!$"
	@ ほしい けいひんが あるからｎ
	@ おおあたり ねらってるのよ!

MauvilleCity_GameCorner_Text_NeedCoinCaseGoNextDoor: @ 8210830
	.string "여기서 놀려면\n"
	.string "동전케이스가 필요하다고!\p"
	.string "갖고 싶으면 옆집의\n"
	.string "누나한테 가보는 건 어때?$"
	@ ここで あそぶにはｎ
	@ コインケ-スが ひつよう だぞ!ｐ
	@ ほしかったら となりの いえのｎ
	@ おねえさんに いってみたら どうだ?

MauvilleCity_GameCorner_Text_LuckOnlyLastSoLongTakeCoins: @ 82108A0
	.string "오늘은 계속 이겼단 말이지!\n"
	.string "네게도 동전을 나눠주마!$"
	@ きょうは かちまくって いるからな!ｎ
	@ きみにも コインを わけて あげよう!

MauvilleCity_GameCorner_Text_MauvilleSomethingForEveryone: @ 82108EF
	.string "아저씨는 보라시티에 오면\n"
	.string "항상 게임코너에서 논단다\p"
	.string "뭔가 다른 곳과 비교해서\n"
	.string "접하기 쉬운 느낌이 들지$"
	@ おじさんは キンセツに くるとｎ
	@ いつも ゲ-ムコ-ナ-で あそぶんだｐ
	@ なんだか ほかに くらべてｎ
	@ でやすいような きが するんだな

MauvilleCity_GameCorner_Text_RouletteTablesDifferentRates: @ 8210932
	.string "룰렛은 노는 테이블마다\n"
	.string "내는 동전의 개수가 다르단다\p"
	.string "가지고 있는 동전을 세서\n"
	.string "놀 테이블을 고르도록 해라!$"
	@ ル-レットは あそぶ テ-ブルでｎ
	@ レ-トが ちがうんじゃよｐ
	@ もっている コインの かずでｎ
	@ あそぶ テ-ブルを えらぶと いいぞ!

MauvilleCity_GameCorner_Text_EasyToLoseTrackOfTime: @ 821098E
	.string "히익- 슬롯을 하다 보면\n"
	.string "할 일을 잊어버린다니까-$"
	@ ひ- スロットを してるとｎ
	@ しごとを わすれてしまう-

MauvilleCity_GameCorner_Text_CoinsAreNeededToPlay: @ 82109D3
	.string "이 게임코너에서는\n"
	.string "동전을 써서 놀아$"
	@ この ゲ-ムコ-ナ-ではｎ
	@ コインを つかって あそぶのよ

MauvilleCity_GameCorner_Text_RouletteOnlyLuck: @ 8210A05
	.string "이 룰렛은\n"
	.string "큰 걸 터뜨리려고 하면\l"
	.string "꽤 이기기 힘든데\l"
	.string "꽤 그만두기가 힘들단 말이지$"
	@ この ル-レット という やつはｎ
	@ おおきく ねらおうと するとｌ
	@ なかなか かてないくせにｌ
	@ なかなか やめられない こまった やつだよ

MauvilleCity_GameCorner_Text_UpTo3CoinsCanBeUsed: @ 8210A51
	.string "슬롯은 동전 1개만 있어도 할 수 있지만\n"
	.string "3개를 거는 게 좋지 않을까?\p"
	.string "당첨될 확률이 높아지거든!$"
	@ スロットは コイン 1まいから あそべるけどｎ
	@ 3まい かけた ほうが いいんじゃない?ｐ
	@ おおあたりの かくりつが アップするからね!

MauvilleCity_GameCorner_Text_DifficultToStopOn7: @ 8210A82
	.string "너는 “7”을 노려서 멈출 수 있니?\p"
	.string "BD 타임에서 “7”을 노려서\n"
	.string "딱 멈출 수 있으면\l"
	.string "동전이 잔뜩 불어나게 돼$"
	@ キミは 「7」を ねらって とめられる?ｐ
	@ BDタイム っていう チャンスゲ-ムのときｎ
	@ 「7」を ねらって ばっちり とめられればｌ
	@ コインを たくさん ふやせるよ

MauvilleCity_GameCorner_Text_HeresSomeSlotsInfo: @ 8210B04
	.string "슬롯에 대해 도움되는 정보를\n"
	.string "너에게 알려줄게!\p"
	.string "번개가 많이 붙어 있을수록\n"
	.string "BD 타임의 횟수가 늘어나!\p"
	.string "최대 5번까지의 BD 타임 게임으로\n"
	.string "레귤러 보너스를 4번 받고\p"
	.string "빅 보너스를 맞추게 되면\n"
	.string "동전을 660개나 얻을 수 있어!$"
	@ スロットの おとくな じょうほうｎ
	@ あなたに おしえて あげるわね!ｐ
	@ イナズマが たくさん たまっているほどｎ
	@ BDタイムの かいすうが ふえやすいの!ｐ
	@ さいこう 5かいの BDタイムの ゲ-ムでｎ
	@ レギュラ-ボ-ナスを 4かい あててからｐ
	@ ビッグボ-ナスを あてることが できればｎ
	@ コインを 660まいも かせげるわ!

MauvilleCity_GameCorner_Text_CantPlayWithNoCoinCase: @ 8210C2E
	.string "동전케이스를\n"
	.string "가지고 있지 않으면 놀 수 없어요!$"
	@ コインケ-スをｎ
	@ もっていないので あそべません!

