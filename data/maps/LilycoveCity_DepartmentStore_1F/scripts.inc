.set LOCALID_LOTTERY_CLERK, 2

LilycoveCity_DepartmentStore_1F_MapScripts:: @ 821F692
	.byte 0

LilycoveCity_DepartmentStore_1F_EventScript_Greeter:: @ 821F693
	msgbox LilycoveCity_DepartmentStore_1F_Text_WelcomeToDeptStore, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_1F_EventScript_LotteryClerk:: @ 821F69C
	lock
	faceplayer
	dotimebasedevents
	compare VAR_POKELOT_PRIZE_ITEM, ITEM_NONE
	goto_if_ne LilycoveCity_DepartmentStore_1F_EventScript_GivePrizeFromEarlier
	goto_if_set FLAG_DAILY_PICKED_LOTO_TICKET, LilycoveCity_DepartmentStore_1F_EventScript_ComeBackTomorrow
	msgbox LilycoveCity_DepartmentStore_1F_Text_LotteryCornerDrawTicket, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq LilycoveCity_DepartmentStore_1F_EventScript_PleaseVisitAgain
	setflag FLAG_DAILY_PICKED_LOTO_TICKET
	message LilycoveCity_DepartmentStore_1F_Text_PleasePickTicket
	waitmessage
	special RetrieveLotteryNumber
	copyvar VAR_0x8008, VAR_RESULT
	special BufferLottoTicketNumber
	msgbox LilycoveCity_DepartmentStore_1F_Text_TicketNumberIsXPleaseWait, MSGBOX_DEFAULT
	applymovement LOCALID_LOTTERY_CLERK, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	playse SE_PC_ON
	special DoLotteryCornerComputerEffect
	special PickLotteryCornerTicket
	delay 220
	special EndLotteryCornerComputerEffect
	delay 10
	applymovement LOCALID_LOTTERY_CLERK, Common_Movement_FacePlayer
	waitmovement 0
	compare VAR_0x8004, 0
	goto_if_eq LilycoveCity_DepartmentStore_1F_EventScript_NoMatch
	incrementgamestat GAME_STAT_WON_POKEMON_LOTTERY
	compare VAR_0x8006, 0
	call_if_eq LilycoveCity_DepartmentStore_1F_EventScript_TicketMatchPartyMon
	compare VAR_0x8006, 1
	call_if_eq LilycoveCity_DepartmentStore_1F_EventScript_TicketMatchPCMon
	bufferitemname 0, VAR_0x8005
	compare VAR_0x8004, 1
	call_if_eq LilycoveCity_DepartmentStore_1F_EventScript_TwoDigitMatch
	compare VAR_0x8004, 2
	call_if_eq LilycoveCity_DepartmentStore_1F_EventScript_ThreeDigitMatch
	compare VAR_0x8004, 3
	call_if_eq LilycoveCity_DepartmentStore_1F_EventScript_FourDigitMatch
	compare VAR_0x8004, 4
	call_if_eq LilycoveCity_DepartmentStore_1F_EventScript_FullMatch
	giveitem VAR_0x8005
	compare VAR_RESULT, FALSE
	goto_if_eq LilycoveCity_DepartmentStore_1F_EventScript_RecordPrizeNoRoom
	special TryPutLotteryWinnerReportOnAir
	goto LilycoveCity_DepartmentStore_1F_EventScript_PleaseVisitAgain2
	end

LilycoveCity_DepartmentStore_1F_EventScript_TicketMatchPartyMon:: @ 821F77B
	msgbox LilycoveCity_DepartmentStore_1F_Text_TicketMatchesPartyMon, MSGBOX_DEFAULT
	return

LilycoveCity_DepartmentStore_1F_EventScript_TicketMatchPCMon:: @ 821F784
	msgbox LilycoveCity_DepartmentStore_1F_Text_TicketMatchesPCMon, MSGBOX_DEFAULT
	return

LilycoveCity_DepartmentStore_1F_EventScript_ComeBackTomorrow:: @ 821F78D
	msgbox LilycoveCity_DepartmentStore_1F_Text_ComeBackTomorrow, MSGBOX_DEFAULT
	release
	end

LilycoveCity_DepartmentStore_1F_EventScript_PleaseVisitAgain:: @ 821F797
	msgbox LilycoveCity_DepartmentStore_1F_Text_PleaseVisitAgain, MSGBOX_DEFAULT
	release
	end

LilycoveCity_DepartmentStore_1F_EventScript_NoMatch:: @ 821F7A1
	msgbox LilycoveCity_DepartmentStore_1F_Text_NoNumbersMatched, MSGBOX_DEFAULT
	goto LilycoveCity_DepartmentStore_1F_EventScript_PleaseVisitAgain2
	end

LilycoveCity_DepartmentStore_1F_EventScript_PleaseVisitAgain2:: @ 821F7AF
	msgbox LilycoveCity_DepartmentStore_1F_Text_PleaseVisitAgain2, MSGBOX_DEFAULT
	release
	end

LilycoveCity_DepartmentStore_1F_EventScript_TwoDigitMatch:: @ 821F7B9
	msgbox LilycoveCity_DepartmentStore_1F_Text_TwoDigitsMatched, MSGBOX_DEFAULT
	return

LilycoveCity_DepartmentStore_1F_EventScript_ThreeDigitMatch:: @ 821F7C2
	msgbox LilycoveCity_DepartmentStore_1F_Text_ThreeDigitsMatched, MSGBOX_DEFAULT
	return

LilycoveCity_DepartmentStore_1F_EventScript_FourDigitMatch:: @ 821F7CB
	msgbox LilycoveCity_DepartmentStore_1F_Text_FourDigitsMatched, MSGBOX_DEFAULT
	return

LilycoveCity_DepartmentStore_1F_EventScript_FullMatch:: @ 821F7D4
	msgbox LilycoveCity_DepartmentStore_1F_Text_AllFiveDigitsMatched, MSGBOX_DEFAULT
	return

LilycoveCity_DepartmentStore_1F_EventScript_RecordPrizeNoRoom:: @ 821F7DD
	copyvar VAR_POKELOT_PRIZE_PLACE, VAR_0x8004
	copyvar VAR_POKELOT_PRIZE_ITEM, VAR_0x8005
	goto LilycoveCity_DepartmentStore_1F_EventScript_NoRoomForPrize
	end

LilycoveCity_DepartmentStore_1F_EventScript_NoRoomForPrize:: @ 821F7ED
	msgbox LilycoveCity_DepartmentStore_1F_Text_NoRoomForThis, MSGBOX_DEFAULT
	release
	end

LilycoveCity_DepartmentStore_1F_EventScript_GivePrizeFromEarlier:: @ 821F7F7
	msgbox LilycoveCity_DepartmentStore_1F_Text_PrizeWeveBeenHolding, MSGBOX_DEFAULT
	giveitem VAR_POKELOT_PRIZE_ITEM
	compare VAR_RESULT, FALSE
	goto_if_eq LilycoveCity_DepartmentStore_1F_EventScript_NoRoomForPrize
	copyvar VAR_0x8004, VAR_POKELOT_PRIZE_PLACE
	copyvar VAR_0x8005, VAR_POKELOT_PRIZE_ITEM
	special TryPutLotteryWinnerReportOnAir
	setvar VAR_POKELOT_PRIZE_ITEM, ITEM_NONE
	setvar VAR_POKELOT_PRIZE_PLACE, 0
	release
	end

LilycoveCity_DepartmentStore_1F_EventScript_PokefanF:: @ 821F82F
	msgbox LilycoveCity_DepartmentStore_1F_Text_IBuyAllSortsOfThings, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_1F_EventScript_LittleGirl:: @ 821F838
	msgbox LilycoveCity_DepartmentStore_1F_Text_MomBuyingMeFurniture, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_1F_EventScript_PokefanM:: @ 821F841
	msgbox LilycoveCity_DepartmentStore_1F_Text_BuyingSomethingForAzumarill, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_1F_EventScript_Azumarill:: @ 821F84A
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, 0
	msgbox LilycoveCity_DepartmentStore_1F_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LilycoveCity_DepartmentStore_1F_EventScript_FloorNamesSign:: @ 821F85D
	msgbox LilycoveCity_DepartmentStore_1F_Text_FloorNamesSign, MSGBOX_SIGN
	end

LilycoveCity_DepartmentStore_1F_Text_WelcomeToDeptStore: @ 821F866
	.string "어서 오세요!\n"
	.string "해안백화점입니다$"
	@ いらっしゃいませ!ｎ
	@ ミナモ デパ-ト です

LilycoveCity_DepartmentStore_1F_Text_IBuyAllSortsOfThings: @ 821F88C
	.string "백화점에 오면 즐거워서\n"
	.string "여러 물건을 사게 돼$"
	@ デパ-トに くると たのしくなってｎ
	@ いろんな ものを かっちゃうのよ

LilycoveCity_DepartmentStore_1F_Text_MomBuyingMeFurniture: @ 821F8F5
	.string "오늘은 엄마가\n"
	.string "멋진 가구를 사 주신대$"
	@ きょうは すてきな かぐをｎ
	@ おかあさんに かって もらうの

LilycoveCity_DepartmentStore_1F_Text_BuyingSomethingForAzumarill: @ 821F92B
	.string "콘테스트에서 우승한 기념으로\n"
	.string "마릴리한테 뭔가 사줄 거야!$"
	@ コンテストで ゆうしょうした ごほうびにｎ
	@ マリルリに なにか かって あげるんだよ!

LilycoveCity_DepartmentStore_1F_Text_Azumarill: @ 821F974
	.string "마릴리: 마리리루-!$"
	@ マリルリ『まりりるぅ-!

LilycoveCity_DepartmentStore_1F_Text_FloorNamesSign: @ 821F98A
	.string "1층 ... 서비스 카운터\n"
	.string "       추첨 회장\p"
	.string "2층 ... 트레이너즈 존\p"
	.string "3층 ... 배틀 컬렉션\p"
	.string "4층 ... 기술머신코너\p"
	.string "5층 ... 모양바꾸기 굿즈 플로어\p"
	.string "옥상 ... 휴식의 장$"
	@ 1かい …… サ-ビス カウンタ-ｎ
	@        ちゅうせん かいじょうｐ
	@ 2かい …… トレ-ナ-ズ ゾ-ンｐ
	@ 3かい …… バトル コレクションｐ
	@ 4かい …… わざマシン コ-ナ-ｐ
	@ 5かい …… ぬいぐるみ フロア-ｐ
	@ おくじょう …… いこいの ひろば

@ Unused
LilycoveCity_DepartmentStore_1F_Text_WirelessCommIsFun: @ 821FA13
	.string "무선 통신은\n"
	.string "참 즐겁지!\p"
	.string "여태까지 할 수 없었던 걸\n"
	.string "할 수 있게 된 느낌이 들어!\p"
	.string "무선으로 교환할 수 없었던\n"
	.string "친구와도 팍 할 수 있게 됐고!\p"
	.string "왠지 엄청\n"
	.string "두근두근거려!$"
	@ むせん つうしん ってｎ
	@ たのしい よね!ｐ
	@ いままで できなかった ことがｎ
	@ できるようになる きが するの!ｐ
	@ むせんで こうかん できなかったｎ
	@ ともだちも ブ-ッと できたり!ｐ
	@ なんだか とってもｎ
	@ わくわく しちゃう!

@ Unused
LilycoveCity_DepartmentStore_1F_Text_SpreadWordAboutWirelessComm: @ 821FAE5
	.string "무선 통신의 즐거움을\n"
	.string "잔뜩 남에게 알려주고 싶어-$"
	@ むせん つうしんの たのしさをｎ
	@ たくさんの ひとに つたえたいな-

