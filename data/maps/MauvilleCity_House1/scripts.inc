MauvilleCity_House1_MapScripts:: @ 820F975
	.byte 0

MauvilleCity_House1_EventScript_RockSmashDude:: @ 820F976
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM06, MauvilleCity_House1_EventScript_ReceivedRockSmash
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_HM06
	setflag FLAG_RECEIVED_HM06
	setflag FLAG_HIDE_ROUTE_111_ROCK_SMASH_TIP_GUY
	msgbox MauvilleCity_House1_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_ReceivedRockSmash:: @ 820F9A5
	msgbox MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis: @ 820F9AF
	.string "허허!\p"
	.string "나를 바위깨기아저씨라고\n"
	.string "부르는 사람들이 있는 모양인데\l"
	.string "실례라고!\p"
	.string "나는 아직 아저씨가 아니야\n"
	.string "적어도 바위깨기형님이라고\l"
	.string "불러주면 좋겠어!\p"
	.string "허허!\p"
	.string "그건 그렇고 네 포켓몬은\n"
	.string "꽤 강해 보이는구나!\p"
	.string "좋아 마음에 들었어!\n"
	.string "이 비전머신을 주지!$"
	// ほっほう!ｐ
	// ぼくのことを いわくだきオヤジｎ
	// なんて よぶひとが いるらしいけどｌ
	// しつれい しちゃうね!ｐ
	// ぼくは まだ オヤジ じゃないよｎ
	// せめて いわくだきにいさん とｌ
	// よんでほしい ものだね!ｐ
	// ほっほう!ｐ
	// それはそれとして きみの ポケモンｎ
	// なかなか つよそうだな!ｐ
	// よし きにいった!ｎ
	// この ひでんマシンを あげよう!

MauvilleCity_House1_Text_ExplainRockSmash: @ 820FAA9
	.string "그것은 비전머신 “바위깨기”!\p"
	.string "너의 앞길을\n"
	.string "큰 바위가 막아도\p"
	.string "그 비전기술을 쓰면\n"
	.string "부술 수 있을 거야!\p"
	.string "힘내서 바위를 부수도록!\n"
	.string "허허!$"
	// それは ひでんマシン「いわくだき」!ｐ
	// きみの いくてを ふさぐｎ
	// じゃまな おおいわが あってもｐ
	// その ひでんを つかうことでｎ
	// くだいて しまえるのだ!ｐ
	// がんばって いわを くだきたまえ!ｎ
	// ほっほう!

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock: @ 820FB67
	.string "그래그래\n"
	.string "바위를 부수면 숨어 있던\l"
	.string "포켓몬이 튀어나올 수도 있어!\p"
	.string "허허!$"
	// そうそうｎ
	// いわを くだくと かくれていたｌ
	// ポケモンが とびでることも あるからね!ｐ
	// ほっほう!

