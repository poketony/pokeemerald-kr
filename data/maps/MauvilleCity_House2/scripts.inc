MauvilleCity_House2_MapScripts:: @ 8210C5C
	.byte 0

MauvilleCity_House2_EventScript_Woman:: @ 8210C5D
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_COIN_CASE, MauvilleCity_House2_EventScript_ReceivedCoinCase
	msgbox MauvilleCity_House2_Text_BuyHarborMailAtSlateport, MSGBOX_DEFAULT
	checkitem ITEM_HARBOR_MAIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_House2_EventScript_AskToTradeForHarborMail
	release
	end

MauvilleCity_House2_EventScript_AskToTradeForHarborMail:: @ 8210C82
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_House2_Text_TradeHarborMailForCoinCase, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MauvilleCity_House2_EventScript_AcceptTrade
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_House2_EventScript_DeclineTrade
	end

MauvilleCity_House2_EventScript_AcceptTrade:: @ 8210CB8
	msgbox MauvilleCity_House2_Text_IllTradeYouCoinCase, MSGBOX_DEFAULT
	removeitem ITEM_HARBOR_MAIL
	giveitem ITEM_COIN_CASE
	setflag FLAG_RECEIVED_COIN_CASE
	goto MauvilleCity_House2_EventScript_ReceivedCoinCase
	end

MauvilleCity_House2_EventScript_ReceivedCoinCase:: @ 8210CDA
	msgbox MauvilleCity_House2_Text_UseCoinCaseAtGameCorner, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_EventScript_DeclineTrade:: @ 8210CE4
	msgbox MauvilleCity_House2_Text_ThatsDisappointing, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_Text_BuyHarborMailAtSlateport: @ 8210CEE
	.string "자전거에 타면\n"
	.string "잿빛도시에 금방 갈 텐데...\p"
	.string "그리고 잿빛도시의 프렌들리숍에서\n"
	.string "항구메일을 살 수 있을 텐데...$"
	// あたしが じてんしゃに のれたらｎ
	// カイナに いくのも すぐなのに……ｐ
	// そして カイナの フレンドリィショップでｎ
	// ハ-バ-メ-ルを かえるのに……

MauvilleCity_House2_Text_TradeHarborMailForCoinCase: @ 8210D76
	.string "그거! 항구메일 맞지!\n"
	.string "동전케이스랑 교환하지 않을래?$"
	// それ! ハ-バ-メ-ルでしょ!ｎ
	// コインケ-スと こうかん してくれない?

MauvilleCity_House2_Text_IllTradeYouCoinCase: @ 8210DB3
	.string "정말 기뻐!\n"
	.string "그럼 동전케이스랑 교환하자!$"
	// うれしい!ｎ
	// じゃ コインケ-スと こうかんね!

MauvilleCity_House2_Text_UseCoinCaseAtGameCorner: @ 8210DE7
	.string "동전케이스가 있으면 게임코너에서\n"
	.string "룰렛과 슬롯을 즐길 수 있어!$"
	// コインケ-スが あれば ゲ-ムコ-ナ-でｎ
	// ル-レットや スロットを たのしめるわ!

MauvilleCity_House2_Text_ThatsDisappointing: @ 8210E16
	.string "그렇구나... 아쉽네\p"
	.string "동전케이스가 있으면 게임코너에서\n"
	.string "룰렛과 슬롯을 즐길 수 있을 텐데...$"
	// そう…… ざんねん ねｐ
	// コインケ-スが あれば ゲ-ムコ-ナ-でｎ
	// ル-レットや スロットを たのしめるのに……

