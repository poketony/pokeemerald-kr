LilycoveCity_DepartmentStoreRooftop_MapScripts:: @ 8220207
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_DepartmentStoreRooftop_OnTransition
	.byte 0

LilycoveCity_DepartmentStoreRooftop_OnTransition: @ 822020D
	getpricereduction POKENEWS_LILYCOVE
	compare VAR_RESULT, TRUE
	call_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_ShowSaleWoman
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_HideSaleWoman
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_ShowSaleWoman:: @ 8220227
	clearflag FLAG_HIDE_LILYCOVE_DEPARTMENT_STORE_ROOFTOP_SALE_WOMAN
	return

LilycoveCity_DepartmentStoreRooftop_EventScript_HideSaleWoman:: @ 822022B
	setflag FLAG_HIDE_LILYCOVE_DEPARTMENT_STORE_ROOFTOP_SALE_WOMAN
	return

LilycoveCity_DepartmentStoreRooftop_EventScript_SaleWoman:: @ 822022F
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration LilycoveCity_DepartmentStoreRooftop_PokemartDecor_ClearOutSale
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStoreRooftop_PokemartDecor_ClearOutSale: @ 8220248
	.2byte DECOR_MUD_BALL
	.2byte DECOR_FENCE_LENGTH
	.2byte DECOR_FENCE_WIDTH
	.2byte DECOR_TIRE
	.2byte DECOR_BREAKABLE_DOOR
	.2byte DECOR_SOLID_BOARD
	.2byte DECOR_SAND_ORNAMENT
	.2byte DECOR_STAND
	.2byte DECOR_SLIDE
	.2byte DECOR_TV
	.2byte DECOR_ROUND_TV
	.2byte DECOR_CUTE_TV
	.2byte DECOR_WAILMER_DOLL
	.2byte DECOR_RHYDON_DOLL
	.2byte 0
	release
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_Man:: @ 8220268
	lock
	faceplayer
	getpricereduction POKENEWS_LILYCOVE
	compare VAR_RESULT, TRUE
	call_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_ManClearOutSale
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_SetDatesForClearOutSales, MSGBOX_DEFAULT
	release
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_ManClearOutSale:: @ 8220282
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_BeenWaitingForClearOutSale, MSGBOX_DEFAULT
	release
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_ThirstyMan:: @ 822028C
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_BoneDryThirsty, MSGBOX_NPC
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_VendingMachine:: @ 8220295
	lockall
	message LilycoveCity_DepartmentStoreRooftop_Text_WhichDrinkWouldYouLike
	waitmessage
	showmoneybox 0, 0, 0
	goto LilycoveCity_DepartmentStoreRooftop_EventScript_ChooseDrink
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_ChooseDrink:: @ 82202A6
	multichoice 16, 0, MULTI_VENDING_MACHINE, 0
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, LilycoveCity_DepartmentStoreRooftop_EventScript_FreshWater
	case 1, LilycoveCity_DepartmentStoreRooftop_EventScript_SodaPop
	case 2, LilycoveCity_DepartmentStoreRooftop_EventScript_Lemonade
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_DecidedAgainstBuyingDrink, MSGBOX_DEFAULT
	goto LilycoveCity_DepartmentStoreRooftop_EventScript_ExitVendingMachine
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_FreshWater:: @ 82202E4
	setvar VAR_TEMP_0, ITEM_FRESH_WATER
	goto LilycoveCity_DepartmentStoreRooftop_EventScript_TryBuyDrink
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_SodaPop:: @ 82202EF
	setvar VAR_TEMP_0, ITEM_SODA_POP
	goto LilycoveCity_DepartmentStoreRooftop_EventScript_TryBuyDrink
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_Lemonade:: @ 82202FA
	setvar VAR_TEMP_0, ITEM_LEMONADE
	goto LilycoveCity_DepartmentStoreRooftop_EventScript_TryBuyDrink
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_CheckMoneyFreshWater:: @ 8220305
	checkmoney 200, 0
	return

LilycoveCity_DepartmentStoreRooftop_EventScript_CheckMoneySodaPop:: @ 822030C
	checkmoney 300, 0
	return

LilycoveCity_DepartmentStoreRooftop_EventScript_CheckMoneyLemonade:: @ 8220313
	checkmoney 350, 0
	return

LilycoveCity_DepartmentStoreRooftop_EventScript_RemoveMoneyFreshWater:: @ 822031A
	removemoney 200, 0
	return

LilycoveCity_DepartmentStoreRooftop_EventScript_RemoveMoneySodaPop:: @ 8220321
	removemoney 300, 0
	return

LilycoveCity_DepartmentStoreRooftop_EventScript_RemoveMoneyLemonade:: @ 8220328
	removemoney 350, 0
	return

LilycoveCity_DepartmentStoreRooftop_EventScript_TryBuyDrink:: @ 822032F
	compare VAR_TEMP_1, 0
	call_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_CheckMoneyFreshWater
	compare VAR_TEMP_1, 1
	call_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_CheckMoneySodaPop
	compare VAR_TEMP_1, 2
	call_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_CheckMoneyLemonade
	compare VAR_RESULT, FALSE
	goto_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_NotEnoughMoneyForDrink
	checkitemspace VAR_TEMP_0, 1
	compare VAR_RESULT, FALSE
	goto_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_NoRoomForDrink
	compare VAR_TEMP_1, 0
	call_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_RemoveMoneyFreshWater
	compare VAR_TEMP_1, 1
	call_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_RemoveMoneySodaPop
	compare VAR_TEMP_1, 2
	call_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_RemoveMoneyLemonade
	updatemoneybox 0, 0
	bufferitemname 0, VAR_TEMP_0
	playse SE_VEND
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_CanOfDrinkDroppedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname 1, VAR_TEMP_0
	bufferstdstring 2, STDSTRING_ITEMS
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	random 64  @ 1/64 chance of an additional drink dropping
	compare VAR_RESULT, 0
	goto_if_ne LilycoveCity_DepartmentStoreRooftop_EventScript_ChooseNewDrink
	checkitemspace VAR_TEMP_0, 1
	compare VAR_RESULT, FALSE
	goto_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_NoRoomForDrink
	playse SE_VEND
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_ExtraCanOfDrinkDroppedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname 1, VAR_TEMP_0
	bufferstdstring 2, STDSTRING_ITEMS
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	random 64  @ 1/64 * the prev 1/64 chance of a third additional drink dropping, ~ 0.02% chance
	compare VAR_RESULT, 0
	goto_if_ne LilycoveCity_DepartmentStoreRooftop_EventScript_ChooseNewDrink
	checkitemspace VAR_TEMP_0, 1
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_NoRoomForDrink
	playse SE_VEND
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_ExtraCanOfDrinkDroppedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname 1, VAR_TEMP_0
	bufferstdstring 2, STDSTRING_ITEMS
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	goto LilycoveCity_DepartmentStoreRooftop_EventScript_ChooseNewDrink
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_ChooseNewDrink:: @ 8220436
	message LilycoveCity_DepartmentStoreRooftop_Text_WhichDrinkWouldYouLike
	waitmessage
	goto LilycoveCity_DepartmentStoreRooftop_EventScript_ChooseDrink
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_NotEnoughMoneyForDrink:: @ 8220442
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_NotEnoughMoney, MSGBOX_DEFAULT
	goto LilycoveCity_DepartmentStoreRooftop_EventScript_ExitVendingMachine
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_NoRoomForDrink:: @ 8220450
	msgbox gText_TheBagIsFull, MSGBOX_DEFAULT
	goto LilycoveCity_DepartmentStoreRooftop_EventScript_ExitVendingMachine
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_ExitVendingMachine:: @ 822045E
	hidemoneybox
	releaseall
	end

LilycoveCity_DepartmentStoreRooftop_Text_SetDatesForClearOutSales: @ 8220463
	.string "득템 가게...\n"
	.string "언제 열 건지 안 정해진 걸까?\p"
	.string "TV를 봐도\n"
	.string "전혀 광고가 없단 말이지$"
	@ ほりだしものいち……ｎ
	@ いつ やるのか きまって ないのかな?ｐ
	@ テレビ みててもｎ
	@ ぜんぜん コマ-シャル ないんだよね

LilycoveCity_DepartmentStoreRooftop_Text_BeenWaitingForClearOutSale: @ 82204C9
	.string "기다리고 기다리던 득템 가게!\n"
	.string "이곳에서만 살 수 있는 것들이 잔뜩!\l"
	.string "좋-았어 마음껏 사야지!$"
	@ まちに まった ほりだしものいち!ｎ
	@ ここでしか かえないもの ばかり!ｌ
	@ よ-し たくさん かっちゃうぞお!

LilycoveCity_DepartmentStoreRooftop_Text_BoneDryThirsty: @ 8220552
	.string "아아 목이 말라$"
	@ ああ のどが かわいたなあ

LilycoveCity_DepartmentStoreRooftop_Text_WhichDrinkWouldYouLike: @ 822056D
	.string "자동 판매기가 있다!\n"
	.string "마시고 싶은 음료수는...$"
	@ じどう はんばいき がある!ｎ
	@ ほしい のみもの は……

LilycoveCity_DepartmentStoreRooftop_Text_CanOfDrinkDroppedDown: @ 82205A1
	.string "덜컹!\p"
	.string "{STR_VAR_1}{K_IGA} 나왔다!$"
	@ ガゴン!ｐ
	@ §いが でてきた!

LilycoveCity_DepartmentStoreRooftop_Text_ExtraCanOfDrinkDroppedDown: @ 82205C2
	.string "덜컹!\p"
	.string "당첨이다! 하나 더\n"
	.string "{STR_VAR_1}{K_IGA} 나왔다!$"
	@ ガゴン!ｐ
	@ あたりだ! もういっぽんｎ
	@ §いが でてきた!

LilycoveCity_DepartmentStoreRooftop_Text_NotEnoughMoney: @ 82205F1
	.string "돈이 모자라!$"
	@ おかねが たりない!

LilycoveCity_DepartmentStoreRooftop_Text_DecidedAgainstBuyingDrink: @ 8220603
	.string "...역시 그만뒀다!$"
	@ ……やっぱり やめた!
