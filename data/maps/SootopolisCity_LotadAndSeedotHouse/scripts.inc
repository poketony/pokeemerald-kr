SootopolisCity_LotadAndSeedotHouse_MapScripts:: @ 822722A
	.byte 0

SootopolisCity_LotadAndSeedotHouse_EventScript_SeedotBrother:: @ 822722B
	special GetSeedotSizeRecordInfo
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigSeedot, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	compare VAR_RESULT, 255
	goto_if_eq SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowSeedot
	special CompareSeedotSize
	compare VAR_RESULT, 1
	goto_if_eq SootopolisCity_LotadAndSeedotHouse_EventScript_NotSeedot
	compare VAR_RESULT, 2
	goto_if_eq SootopolisCity_LotadAndSeedotHouse_EventScript_SmallSeedot
	compare VAR_RESULT, 3
	goto_if_eq SootopolisCity_LotadAndSeedotHouse_EventScript_BigSeedot
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowSeedot:: @ 8227272
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NotSeedot:: @ 822727C
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SmallSeedot:: @ 8227286
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_BigSeedot:: @ 8227290
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_GoshMightBeBiggerThanLotad, MSGBOX_DEFAULT
	giveitem ITEM_ELIXIR
	compare VAR_RESULT, FALSE
	goto_if_eq SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir1
	closemessage
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir1:: @ 82272B2
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull1, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_LotadBrother:: @ 82272BC
	special GetLotadSizeRecordInfo
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigLotad, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	compare VAR_RESULT, 255
	goto_if_eq SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowLotad
	special CompareLotadSize
	compare VAR_RESULT, 1
	goto_if_eq SootopolisCity_LotadAndSeedotHouse_EventScript_NotLotad
	compare VAR_RESULT, 2
	goto_if_eq SootopolisCity_LotadAndSeedotHouse_EventScript_SmallLotad
	compare VAR_RESULT, 3
	goto_if_eq SootopolisCity_LotadAndSeedotHouse_EventScript_BigLotad
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowLotad:: @ 8227303
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NotLotad:: @ 822730D
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SmallLotad:: @ 8227317
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_BigLotad:: @ 8227321
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_WowMightBeBiggerThanSeedot, MSGBOX_DEFAULT
	giveitem ITEM_ELIXIR
	compare VAR_RESULT, FALSE
	goto_if_eq SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir2
	closemessage
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir2:: @ 8227343
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull2, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SeedotSizeRecord:: @ 822734D
	special GetSeedotSizeRecordInfo
	lockall
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BiggestSeedotInHistory, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_LotadSizeRecord:: @ 822735B
	special GetLotadSizeRecordInfo
	lockall
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BiggestLotadInHistory, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigSeedot: @ 8227369
	.string "너 도토링이라는 포켓몬 알아?\n"
	.string "루네시티에선 좀처럼 보기 힘들지만\p"
	.string "나 커다란 도토링이\n"
	.string "무지무지 좋아!\p"
	.string "동생은 연꽃몬이 더\n"
	.string "크다고 하는데 말야\p"
	.string "당연히 도토링이 더\n"
	.string "크지 않아!?\p"
	.string "응? 너 도토링 가지고 있어?\n"
	.string "자 자 잠깐...\l"
	.string "아저씨한테 좀 보여 줘!$"
	@ きみ タネボ-って ポケモン しってる?ｎ
	@ ルネでは めったに みられないん だけどねｐ
	@ わし おおきな タネボ-がｎ
	@ めちゃめちゃ だいすき なのよ!ｐ
	@ おとうとは ハスボ-の ほうがｎ
	@ おおきいって いうんだけどｐ
	@ タネボ-の ほうがｎ
	@ おおきいに きまってる よね!ｐ
	@ ん? きみ タネボ- もってるの?ｎ
	@ ちょ ちょ ちょっと……ｌ
	@ おじさんに みせて おくれ!

SootopolisCity_LotadAndSeedotHouse_Text_GoshMightBeBiggerThanLotad: @ 8227480
	.string "{STR_VAR_2}cm!\n"
	.string "오오! 이 녀석 커!\p"
	.string "동생이 본 커다란 연꽃몬에\n"
	.string "지지 않는 크기일지도 몰라!\p"
	.string "보여 줘서 고마워\n"
	.string "답례로 이걸 줄게!$"
	@ §うcm!!ｎ
	@ おお! こいつは でかい!ｐ
	@ おとうとが みた でかい ハスボ-にｎ
	@ まけない おおきさ かも!ｐ
	@ みせて くれて ありがとうｎ
	@ おれいに これを あげるよ!

@ Unused
SootopolisCity_LotadAndSeedotHouse_Text_ReceivedPotion1: @ 822750E
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "상처약을 받았다!$"

SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull1: @ 8227524
	.string "어라?\n"
	.string "너 지닌물건이 가득 찼네$"

SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerSeedot: @ 8227544
	.string "{STR_VAR_2}cm인가...\p"
	.string "으음 난 이것보다 큰\n"
	.string "도토링을 본 적이 있어...$"

SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotSeedot: @ 8227584
	.string "오오 이 녀석 꽤... 아니\n"
	.string "이거 도토링이 아니잖아!$"

SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigSeedot: @ 82275BC
	.string "커다란 도토링 없어?\n"
	.string "그거 안타깝네...\p"
	.string "다음에 커다란 도토링 보여 줘$"

SootopolisCity_LotadAndSeedotHouse_Text_BiggestSeedotInHistory: @ 8227617
	.string "사상 최대의 도토링!\n"
	.string "{STR_VAR_2}의 {STR_VAR_3}cm인 녀석!\p"
	.string "연꽃몬보다 커다란 도토링\n"
	.string "언제나 모집 중!$"

SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigLotad: @ 8227676
	.string "너 혹시 연꽃몬이라는 포켓몬 알아?\n"
	.string "루네시티에서는 좀처럼 보기 힘들지만\p"
	.string "나 커다란 연꽃몬이\n"
	.string "무지무지 좋아!\p"
	.string "형은 도토링이 더\n"
	.string "크다고 하는데 말야\p"
	.string "당연히 연꽃몬이 더\n"
	.string "크지 않아!?\p"
	.string "응? 너 연꽃몬 가지고 있어?\n"
	.string "자 자 잠깐...\l"
	.string "아저씨한테 좀 보여 줘!$"

SootopolisCity_LotadAndSeedotHouse_Text_WowMightBeBiggerThanSeedot: @ 822776C
	.string "{STR_VAR_2}cm!\n"
	.string "오오! 이 녀석 커!\p"
	.string "형이 본 커다란 도토링에\n"
	.string "지지 않는 크기일지도 몰라!\p"
	.string "보여 줘서 고마워\n"
	.string "보답으로 이걸 줄게!$"

@ Unused
SootopolisCity_LotadAndSeedotHouse_Text_ReceivedPotion2: @ 82277F4
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "상처약을 받았다!$"

SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull2: @ 822780A
	.string "어라?\n"
	.string "너 지닌물건이 가득 찼네$"

SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerLotad: @ 822782A
	.string "{STR_VAR_2}cm인가...\p"
	.string "으음 난 이것보다 큰\n"
	.string "연꽃몬을 본 적이 있어...$"

SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotLotad: @ 8227867
	.string "오오 이 녀석 꽤... 아니\n"
	.string "이거 연꽃몬이 아니잖아!$"

SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigLotad: @ 8227896
	.string "커다란 연꽃몬 없어?\n"
	.string "그거 안타깝네...\p"
	.string "다음에 커다란 연꽃몬 보여 줘$"

SootopolisCity_LotadAndSeedotHouse_Text_BiggestLotadInHistory: @ 82278F2
	.string "사상 최대의 연꽃몬!\n"
	.string "{STR_VAR_2}의 {STR_VAR_3}cm인 녀석!\p"
	.string "도토링보다 커다란 연꽃몬\n"
	.string "언제나 모집 중!$"

