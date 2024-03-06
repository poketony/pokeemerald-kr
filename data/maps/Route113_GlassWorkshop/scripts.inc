Route113_GlassWorkshop_MapScripts:: @ 826ED03
	map_script MAP_SCRIPT_ON_TRANSITION, Route113_GlassWorkshop_OnTransition
	.byte 0

	.set BLUE_FLUTE_PRICE,   250
	.set YELLOW_FLUTE_PRICE, 500
	.set RED_FLUTE_PRICE,    500
	.set WHITE_FLUTE_PRICE,  1000
	.set BLACK_FLUTE_PRICE,  1000
	.set PRETTY_CHAIR_PRICE, 6000
	.set PRETTY_DESK_PRICE,  8000
	.set LOWEST_ASH_PRICE,   BLUE_FLUTE_PRICE

Route113_GlassWorkshop_OnTransition: @ 826ED09
	setflag FLAG_LANDMARK_GLASS_WORKSHOP
	compare VAR_GLASS_WORKSHOP_STATE, 1
	call_if_eq Route113_GlassWorkshop_EventScript_ReenterWorkshopAfterSootSack
	end

Route113_GlassWorkshop_EventScript_ReenterWorkshopAfterSootSack:: @ 826ED18
	setvar VAR_GLASS_WORKSHOP_STATE, 2
	return

Route113_GlassWorkshop_EventScript_GlassWorker:: @ 826ED1E
	lock
	faceplayer
	compare VAR_GLASS_WORKSHOP_STATE, 10
	goto_if_ge Route113_GlassWorkshop_EventScript_GiveItemAfterNoRoom
	compare VAR_GLASS_WORKSHOP_STATE, 2
	goto_if_eq Route113_GlassWorkshop_EventScript_CheckCollectedAsh
	compare VAR_GLASS_WORKSHOP_STATE, 1
	goto_if_eq Route113_GlassWorkshop_EventScript_ExplainSootSack
	msgbox Route113_GlassWorkshop_Text_GoCollectAshWithThis, MSGBOX_DEFAULT
	giveitem ITEM_SOOT_SACK
	setvar VAR_GLASS_WORKSHOP_STATE, 1
	msgbox Route113_GlassWorkshop_Text_ExplainSootSack, MSGBOX_DEFAULT
	release
	end

Route113_GlassWorkshop_EventScript_ExplainSootSack:: @ 826ED64
	msgbox Route113_GlassWorkshop_Text_ExplainSootSack, MSGBOX_DEFAULT
	release
	end

Route113_GlassWorkshop_EventScript_CheckCollectedAsh:: @ 826ED6E
	checkitem ITEM_SOOT_SACK, 1
	compare VAR_RESULT, FALSE
	goto_if_eq Route113_GlassWorkshop_EventScript_SootSackNotInBag
	msgbox Route113_GlassWorkshop_Text_LetsSeeCollectedAshes, MSGBOX_DEFAULT
	compare VAR_ASH_GATHER_COUNT, LOWEST_ASH_PRICE
	goto_if_lt Route113_GlassWorkshop_EventScript_NotEnoughAsh
	message Route113_GlassWorkshop_Text_WhichGlassItemWoudYouLike
	waitmessage
	goto Route113_GlassWorkshop_EventScript_ChooseGlassItem
	end

Route113_GlassWorkshop_EventScript_SootSackNotInBag:: @ 826ED9D
	msgbox Route113_GlassWorkshop_Text_HaventGotYourSootSack, MSGBOX_DEFAULT
	release
	end

Route113_GlassWorkshop_EventScript_ChooseGlassItem:: @ 826EDA7
	setvar VAR_0x8009, 0
	setvar VAR_0x8004, SCROLL_MULTI_GLASS_WORKSHOP_VENDOR
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, Route113_GlassWorkshop_EventScript_BlueFlute
	case 1, Route113_GlassWorkshop_EventScript_YellowFlute
	case 2, Route113_GlassWorkshop_EventScript_RedFlute
	case 3, Route113_GlassWorkshop_EventScript_WhiteFlute
	case 4, Route113_GlassWorkshop_EventScript_BlackFlute
	case 5, Route113_GlassWorkshop_EventScript_PrettyChair
	case 6, Route113_GlassWorkshop_EventScript_PrettyDesk
	case 7, Route113_GlassWorkshop_EventScript_CancelGlassItemSelect
	case MULTI_B_PRESSED, Route113_GlassWorkshop_EventScript_CancelGlassItemSelect
	end

Route113_GlassWorkshop_EventScript_BlueFlute:: @ 826EE1E
	setvar VAR_0x8008, ITEM_BLUE_FLUTE
	bufferitemname 0, VAR_0x8008
	setvar VAR_0x800A, BLUE_FLUTE_PRICE
	compare VAR_ASH_GATHER_COUNT, BLUE_FLUTE_PRICE
	goto_if_lt Route113_GlassWorkshop_EventScript_NotEnoughAshForItem
	msgbox Route113_GlassWorkshop_Text_IsThatTheItemForYou, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route113_GlassWorkshop_EventScript_ChooseDifferentItem
	setvar VAR_GLASS_WORKSHOP_STATE, 10
	subvar VAR_ASH_GATHER_COUNT, BLUE_FLUTE_PRICE
	goto Route113_GlassWorkshop_EventScript_MakeGlassItem
	end

Route113_GlassWorkshop_EventScript_YellowFlute:: @ 826EE5A
	setvar VAR_0x8008, ITEM_YELLOW_FLUTE
	bufferitemname 0, VAR_0x8008
	setvar VAR_0x800A, YELLOW_FLUTE_PRICE
	compare VAR_ASH_GATHER_COUNT, YELLOW_FLUTE_PRICE
	goto_if_lt Route113_GlassWorkshop_EventScript_NotEnoughAshForItem
	msgbox Route113_GlassWorkshop_Text_IsThatTheItemForYou, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route113_GlassWorkshop_EventScript_ChooseDifferentItem
	setvar VAR_GLASS_WORKSHOP_STATE, 11
	subvar VAR_ASH_GATHER_COUNT, YELLOW_FLUTE_PRICE
	goto Route113_GlassWorkshop_EventScript_MakeGlassItem
	end

Route113_GlassWorkshop_EventScript_RedFlute:: @ 826EE96
	setvar VAR_0x8008, ITEM_RED_FLUTE
	bufferitemname 0, VAR_0x8008
	setvar VAR_0x800A, RED_FLUTE_PRICE
	compare VAR_ASH_GATHER_COUNT, RED_FLUTE_PRICE
	goto_if_lt Route113_GlassWorkshop_EventScript_NotEnoughAshForItem
	msgbox Route113_GlassWorkshop_Text_IsThatTheItemForYou, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route113_GlassWorkshop_EventScript_ChooseDifferentItem
	setvar VAR_GLASS_WORKSHOP_STATE, 12
	subvar VAR_ASH_GATHER_COUNT, RED_FLUTE_PRICE
	goto Route113_GlassWorkshop_EventScript_MakeGlassItem
	end

Route113_GlassWorkshop_EventScript_WhiteFlute:: @ 826EED2
	setvar VAR_0x8008, ITEM_WHITE_FLUTE
	bufferitemname 0, VAR_0x8008
	setvar VAR_0x800A, WHITE_FLUTE_PRICE
	compare VAR_ASH_GATHER_COUNT, WHITE_FLUTE_PRICE
	goto_if_lt Route113_GlassWorkshop_EventScript_NotEnoughAshForItem
	msgbox Route113_GlassWorkshop_Text_IsThatTheItemForYou, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route113_GlassWorkshop_EventScript_ChooseDifferentItem
	setvar VAR_GLASS_WORKSHOP_STATE, 13
	subvar VAR_ASH_GATHER_COUNT, WHITE_FLUTE_PRICE
	goto Route113_GlassWorkshop_EventScript_MakeGlassItem
	end

Route113_GlassWorkshop_EventScript_BlackFlute:: @ 826EF0E
	setvar VAR_0x8008, ITEM_BLACK_FLUTE
	bufferitemname 0, VAR_0x8008
	setvar VAR_0x800A, BLACK_FLUTE_PRICE
	compare VAR_ASH_GATHER_COUNT, BLACK_FLUTE_PRICE
	goto_if_lt Route113_GlassWorkshop_EventScript_NotEnoughAshForItem
	msgbox Route113_GlassWorkshop_Text_IsThatTheItemForYou, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route113_GlassWorkshop_EventScript_ChooseDifferentItem
	setvar VAR_GLASS_WORKSHOP_STATE, 14
	subvar VAR_ASH_GATHER_COUNT, BLACK_FLUTE_PRICE
	goto Route113_GlassWorkshop_EventScript_MakeGlassItem
	end

Route113_GlassWorkshop_EventScript_PrettyChair:: @ 826EF4A
	setvar VAR_0x8009, 1
	setvar VAR_0x8008, DECOR_PRETTY_CHAIR
	bufferdecorationname 0, VAR_0x8008
	setvar VAR_0x800A, PRETTY_CHAIR_PRICE
	compare VAR_ASH_GATHER_COUNT, PRETTY_CHAIR_PRICE
	goto_if_lt Route113_GlassWorkshop_EventScript_NotEnoughAshForItem
	msgbox Route113_GlassWorkshop_Text_IsThatTheItemForYou, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route113_GlassWorkshop_EventScript_ChooseDifferentItem
	setvar VAR_GLASS_WORKSHOP_STATE, 15
	subvar VAR_ASH_GATHER_COUNT, PRETTY_CHAIR_PRICE
	goto Route113_GlassWorkshop_EventScript_MakeGlassItem
	end

Route113_GlassWorkshop_EventScript_PrettyDesk:: @ 826EF8B
	setvar VAR_0x8009, 1
	setvar VAR_0x8008, DECOR_PRETTY_DESK
	bufferdecorationname 0, VAR_0x8008
	setvar VAR_0x800A, PRETTY_DESK_PRICE
	compare VAR_ASH_GATHER_COUNT, PRETTY_DESK_PRICE
	goto_if_lt Route113_GlassWorkshop_EventScript_NotEnoughAshForItem
	msgbox Route113_GlassWorkshop_Text_IsThatTheItemForYou, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route113_GlassWorkshop_EventScript_ChooseDifferentItem
	setvar VAR_GLASS_WORKSHOP_STATE, 16
	subvar VAR_ASH_GATHER_COUNT, PRETTY_DESK_PRICE
	goto Route113_GlassWorkshop_EventScript_MakeGlassItem
	end

Route113_GlassWorkshop_EventScript_CancelGlassItemSelect:: @ 826EFCC
	msgbox Route113_GlassWorkshop_Text_AllThatAshButDontWantAnything, MSGBOX_DEFAULT
	release
	end

Route113_GlassWorkshop_EventScript_NotEnoughAsh:: @ 826EFD6
	setvar VAR_0x800A, LOWEST_ASH_PRICE
	subvar VAR_0x800A, VAR_ASH_GATHER_COUNT
	buffernumberstring 0, VAR_0x800A
	msgbox Route113_GlassWorkshop_Text_NotEnoughAshNeedX, MSGBOX_DEFAULT
	release
	end

Route113_GlassWorkshop_EventScript_NotEnoughAshForItem:: @ 826EFEE
	subvar VAR_0x800A, VAR_ASH_GATHER_COUNT
	buffernumberstring 1, VAR_0x800A
	message Route113_GlassWorkshop_Text_NotEnoughAshToMakeItem
	waitmessage
	goto Route113_GlassWorkshop_EventScript_ChooseGlassItem
	end

Route113_GlassWorkshop_EventScript_ChooseDifferentItem:: @ 826F003
	message Route113_GlassWorkshop_Text_WhichWouldYouLike
	waitmessage
	goto Route113_GlassWorkshop_EventScript_ChooseGlassItem
	end

Route113_GlassWorkshop_EventScript_MakeGlassItem:: @ 826F00F
	msgbox Route113_GlassWorkshop_Text_IllMakeItemForYou, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playse SE_SELECT
	delay 30
	fadescreen FADE_FROM_BLACK
	msgbox Route113_GlassWorkshop_Text_IveFinishedGlassItem, MSGBOX_DEFAULT
	compare VAR_0x8009, 0
	call_if_eq Route113_GlassWorkshop_EventScript_GiveGlassFlute
	compare VAR_0x8009, 1
	call_if_eq Route113_GlassWorkshop_EventScript_GiveGlassDecor
	setvar VAR_GLASS_WORKSHOP_STATE, 2
	release
	end

Route113_GlassWorkshop_EventScript_GiveGlassFlute:: @ 826F047
	giveitem VAR_0x8008
	compare VAR_RESULT, FALSE
	goto_if_eq Route113_GlassWorkshop_EventScript_NoRoomForFlute
	return

Route113_GlassWorkshop_EventScript_GiveGlassDecor:: @ 826F05F
	givedecoration VAR_0x8008
	compare VAR_RESULT, FALSE
	goto_if_eq Route113_GlassWorkshop_EventScript_NoRoomForDecor
	return

Route113_GlassWorkshop_EventScript_NoRoomForFlute:: @ 826F072
	call Common_EventScript_BagIsFull
	msgbox Route113_GlassWorkshop_Text_NoRoomInBag, MSGBOX_DEFAULT
	release
	end

Route113_GlassWorkshop_EventScript_NoRoomForDecor:: @ 826F081
	call Common_EventScript_NoRoomForDecor
	msgbox Route113_GlassWorkshop_Text_NoRoomInPC, MSGBOX_DEFAULT
	release
	end

Route113_GlassWorkshop_EventScript_GiveItemAfterNoRoom:: @ 826F090
	switch VAR_GLASS_WORKSHOP_STATE
	case 10, Route113_GlassWorkshop_EventScript_GiveBlueFlute
	case 11, Route113_GlassWorkshop_EventScript_GiveYellowFlute
	case 12, Route113_GlassWorkshop_EventScript_GiveRedFlute
	case 13, Route113_GlassWorkshop_EventScript_GiveWhiteFlute
	case 14, Route113_GlassWorkshop_EventScript_GiveBlackFlute
	case 15, Route113_GlassWorkshop_EventScript_GivePrettyChair
	case 16, Route113_GlassWorkshop_EventScript_GivePrettyDesk
	end

Route113_GlassWorkshop_EventScript_GiveBlueFlute:: @ 826F0E3
	setvar VAR_0x8009, 0
	setvar VAR_0x8008, ITEM_BLUE_FLUTE
	bufferitemname 0, VAR_0x8008
	goto Route113_GlassWorkshop_EventScript_TryGiveItemAgain
	end

Route113_GlassWorkshop_EventScript_GiveYellowFlute:: @ 826F0F7
	setvar VAR_0x8009, 0
	setvar VAR_0x8008, ITEM_YELLOW_FLUTE
	bufferitemname 0, VAR_0x8008
	goto Route113_GlassWorkshop_EventScript_TryGiveItemAgain
	end

Route113_GlassWorkshop_EventScript_GiveRedFlute:: @ 826F10B
	setvar VAR_0x8009, 0
	setvar VAR_0x8008, ITEM_RED_FLUTE
	bufferitemname 0, VAR_0x8008
	goto Route113_GlassWorkshop_EventScript_TryGiveItemAgain
	end

Route113_GlassWorkshop_EventScript_GiveWhiteFlute:: @ 826F11F
	setvar VAR_0x8009, 0
	setvar VAR_0x8008, ITEM_WHITE_FLUTE
	bufferitemname 0, VAR_0x8008
	goto Route113_GlassWorkshop_EventScript_TryGiveItemAgain
	end

Route113_GlassWorkshop_EventScript_GiveBlackFlute:: @ 826F133
	setvar VAR_0x8009, 0
	setvar VAR_0x8008, ITEM_BLACK_FLUTE
	bufferitemname 0, VAR_0x8008
	goto Route113_GlassWorkshop_EventScript_TryGiveItemAgain
	end

Route113_GlassWorkshop_EventScript_GivePrettyChair:: @ 826F147
	setvar VAR_0x8009, 1
	setvar VAR_0x8008, DECOR_PRETTY_CHAIR
	bufferdecorationname 0, DECOR_PRETTY_CHAIR
	goto Route113_GlassWorkshop_EventScript_TryGiveItemAgain
	end

Route113_GlassWorkshop_EventScript_GivePrettyDesk:: @ 826F15B
	setvar VAR_0x8009, 1
	setvar VAR_0x8008, DECOR_PRETTY_DESK
	bufferdecorationname 0, DECOR_PRETTY_DESK
	goto Route113_GlassWorkshop_EventScript_TryGiveItemAgain
	end

Route113_GlassWorkshop_EventScript_TryGiveItemAgain:: @ 826F16F
	msgbox Route113_GlassWorkshop_Text_IveFinishedGlassItem, MSGBOX_DEFAULT
	compare VAR_0x8009, 0
	call_if_eq Route113_GlassWorkshop_EventScript_GiveGlassFlute
	compare VAR_0x8009, 1
	call_if_eq Route113_GlassWorkshop_EventScript_GiveGlassDecor
	setvar VAR_GLASS_WORKSHOP_STATE, 2
	release
	end

Route113_GlassWorkshop_EventScript_NinjaBoy:: @ 826F194
	msgbox Route113_GlassWorkshop_Text_FunToBlowGlassFlute, MSGBOX_NPC
	end

Route113_GlassWorkshop_Text_GoCollectAshWithThis: @ 826F19D
	.string "요 주변에는\n"
	.string "온통 화산재뿐이야 콜록콜록!\p"
	.string "그리고 난 대단해 콜록콜록\p"
	.string "화산재를 유리로 만들어서\n"
	.string "그걸로 도구를 만들 수 있어 콜록콜록!\p"
	.string "너도 이걸로\n"
	.string "화산재를 모아 봐 콜록콜록!$"
	@ この あたりはｎ
	@ かざんばい だらけ ペコペコ!ｐ
	@ わたし すごいよ ペコペコｐ
	@ かざんばいを ガラスに してねｎ
	@ それで どうぐ つくるよ ペコペコ!ｐ
	@ きみも これでｎ
	@ かざんばいを あつめなさい ペコペコ!

Route113_GlassWorkshop_Text_ExplainSootSack: @ 826F252
	.string "그 주머니를 가지고\n"
	.string "재가 쌓여 있는 곳에 들어가면\l"
	.string "어머 신기해라!\p"
	.string "주머니 속에 화산재가\n"
	.string "점점 모일 거야 콜록콜록!\p"
	.string "화산재가 많이 모였다고 생각되면\n"
	.string "나한테 와 봐 콜록콜록!$"
	@ その ふくろを もってｎ
	@ はいの つもった ところを あるくとｌ
	@ あら ふしぎ!ｐ
	@ ふくろの なかに かざんばいがｎ
	@ どんどん たまっていくよ ペコペコ!ｐ
	@ かざんばいが たまったと おもったらｎ
	@ わたしの ところに きなさい ペコペコ!

Route113_GlassWorkshop_Text_LetsSeeCollectedAshes: @ 826F312
	.string "화산재 있으려나 콜록콜록!\n"
	.string "어디 어디 한번 보여 줘 콜록쿨럭!$"
	@ かざんばい あるのかね ペコペコ!ｎ
	@ どれどれ みせてごらん ペコポコ!

Route113_GlassWorkshop_Text_NotEnoughAshNeedX: @ 826F34E
	.string "으-음...\n"
	.string "화산재가 얼마 없어 콜록콜록!\l"
	.string "유리 도구를 만들 수 없어 콜록콜록!\p"
	.string "앞으로 {STR_VAR_1}걸음 더 걸으면\n"
	.string "파랑비드로를 만들 수 있어 콜록콜록!$"
	@ う-ん……ｎ
	@ かざんばいが すくないよ ペコペコ!ｌ
	@ ガラスのどうぐ できないよ ペコペコ!ｐ
	@ あと §いほ あるけばｎ
	@ あおいビ-ドロ つくれるよ ペコペコ!

Route113_GlassWorkshop_Text_WhichGlassItemWoudYouLike: @ 826F40A
	.string "오오!\n"
	.string "화산재 모여 있어 콜록콜록!\l"
	.string "유리 도구 만들 수 있어 콜록콜록!\p"
	.string "어떤 게 좋을까 콜록콜록$"
	@ おほっｎ
	@ かざんばい あつまってるよ ペコペコ!ｌ
	@ ガラスのどうぐ つくるよ ペコペコ!ｐ
	@ どれが いいかね ペコペコ

Route113_GlassWorkshop_Text_IsThatTheItemForYou: @ 826F480
	.string "{STR_VAR_1} 말이지 콜록콜록!\n"
	.string "정말 이걸로 할 거지? 콜록콜록$"
	@ §い だね ペコペコ!ｎ
	@ ほんとうに それで いいんだね? ペコペコ

Route113_GlassWorkshop_Text_WhichWouldYouLike: @ 826F4B5
	.string "어떤 게 좋을까 콜록콜록$"
	@ どれが いいかね ペコペコ

Route113_GlassWorkshop_Text_IllMakeItemForYou: @ 826F4DA
	.string "{STR_VAR_1} 말이지 콜록콜록!\p"
	.string "좋아! 도구 만들게 콜록콜록!\n"
	.string "잠깐 기다리고 있어 콜록콜록$"
	@ §い だね ペコペコ!ｐ
	@ よしっ! どうぐを つくるよ ペコペコ!ｎ
	@ ちょっと まってなさいよ ペコペコ

Route113_GlassWorkshop_Text_NotEnoughAshToMakeItem: @ 826F543
	.string "{STR_VAR_1} 말이지 콜록콜록!\p"
	.string "그치만 그걸 만들기 위해선\n"
	.string "아직 화산재가 부족해 콜록콜록!\p"
	.string "화산재가 쌓여 있는 곳을\n"
	.string "앞으로 {STR_VAR_2}걸음 더 걸어야 해 콜록콜록!\p"
	.string "어떤 게 좋을까 콜록콜록$"
	@ §い だね ペコペコ!ｐ
	@ だけど それを つくるにはｎ
	@ かざんばいが たりないよ ペコペコ!ｐ
	@ かざんばいの つもっている ところをｎ
	@ あと §うほ あるかないと ペコペコ!ｐ
	@ どれが いいかね ペコペコ

Route113_GlassWorkshop_Text_AllThatAshButDontWantAnything: @ 826F641
	.string "기껏 화산재를 모아 왔는데\n"
	.string "갖고 싶은 건 없나 콜록콜록...$"
	@ せっかく かざんばいを あつめたのにｎ
	@ ほしい ものは ないのかね ペコペコ……

Route113_GlassWorkshop_Text_IveFinishedGlassItem: @ 826F688
	.string "오오 {STR_VAR_1} 다 만들었어\n"
	.string "가져가 콜록콜록$"
	@ おお §い できたよｎ
	@ もって いきなさいよ ペコペコ

Route113_GlassWorkshop_Text_NoRoomInBag: @ 826F6B7
	.string "어라?\n"
	.string "그 이상은 가지고 다닐 수 없어 콜록콜록\p"
	.string "맡아 둘 테니까\n"
	.string "다음에 와 콜록콜록$"
	@ あら?ｎ
	@ それいじょう もてないよ ペコペコｐ
	@ あずかって おくからｎ
	@ こんど きなさい ペコペコ

Route113_GlassWorkshop_Text_NoRoomInPC: @ 826F715
	.string "어라?\n"
	.string "PC가 가득 찼네 콜록콜록\p"
	.string "맡아 둘 테니까\n"
	.string "다음에 와 콜록콜록$"
	@ あら?ｎ
	@ パソコン いっぱい なのか ペコペコｐ
	@ あずかって おくからｎ
	@ こんど きなさい ペコペコ

Route113_GlassWorkshop_Text_HaventGotYourSootSack: @ 826F772
	.string "어라?\n"
	.string "재주머니가 없네 콜록콜록\p"
	.string "가지고 다니지 않으면\n"
	.string "화산재를 모을 수 없어 콜록콜록$"
	@ あら?ｎ
	@ はいぶくろ もっていないのか ペコペコｐ
	@ もちあるかないとｎ
	@ かざんばい たまらないよ ペコペコ

Route113_GlassWorkshop_Text_FunToBlowGlassFlute: @ 826F7EC
	.string "스승님이 말씀하시는 거에 맞춰서\n"
	.string "비드로를 불면 즐거워!\p"
	.string "콜록콜록! 콜록쿨럭!$"
	@ おやかたが はなすのに あわせてｎ
	@ ビ-ドロ ふくと たのしか!ｐ
	@ ペコペコ! ペコポコ!

