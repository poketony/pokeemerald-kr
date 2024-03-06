.set LOCALID_FOSSIL_SCIENTIST, 5

RustboroCity_DevonCorp_2F_MapScripts:: @ 8211857
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_2F_OnTransition
	.byte 0

RustboroCity_DevonCorp_2F_OnTransition: @ 821185D
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	end

RustboroCity_DevonCorp_2F_EventScript_SetFossilReady:: @ 8211869
	setvar VAR_FOSSIL_RESURRECTION_STATE, 2
	return

RustboroCity_DevonCorp_2F_EventScript_TalkToPokemonScientist:: @ 821186F
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_BallScientist:: @ 8211886
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls:: @ 82118A6
	msgbox RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokenavScientist:: @ 82118B0
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_RECEIVED_POKENAV, RustboroCity_DevonCorp_2F_EventScript_HasPokenav
	msgbox RustboroCity_DevonCorp_2F_Text_IMadePokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_HasPokenav:: @ 82118D0
	msgbox RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokemonDreamsScientist:: @ 82118DA
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilScientist:: @ 82118F1
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 2
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilMonReady
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_StillRegenerating
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils, MSGBOX_DEFAULT
	checkitem ITEM_ROOT_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeRootFossil
	checkitem ITEM_CLAW_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeClawFossil
	release
	end

@ This whole section has needless duplication and could be condensed considerably
RustboroCity_DevonCorp_2F_EventScript_NoticeRootFossil:: @ 8211933
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	checkitem ITEM_CLAW_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_ChooseFossil
	goto RustboroCity_DevonCorp_2F_EventScript_GiveRootFossil
	end

RustboroCity_DevonCorp_2F_EventScript_GiveRootFossil:: @ 8211974
	bufferitemname 0, ITEM_ROOT_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_ROOT_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 1
	release
	end

RustboroCity_DevonCorp_2F_EventScript_NoticeClawFossil:: @ 8211991
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	checkitem ITEM_ROOT_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_ChooseFossil
	goto RustboroCity_DevonCorp_2F_EventScript_GiveClawFossil
	end

RustboroCity_DevonCorp_2F_EventScript_GiveClawFossil:: @ 82119D2
	bufferitemname 0, ITEM_CLAW_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_CLAW_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 2
	release
	end

RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil:: @ 82119EF
	msgbox RustboroCity_DevonCorp_2F_Text_OhIsThatSo, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_StillRegenerating:: @ 82119F9
	msgbox RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilMonReady:: @ 8211A03
	compare VAR_WHICH_FOSSIL_REVIVED, 1
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_LileepReady
	compare VAR_WHICH_FOSSIL_REVIVED, 2
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_AnorithReady
	end

RustboroCity_DevonCorp_2F_EventScript_LileepReady:: @ 8211A1A
	bufferspeciesname 1, SPECIES_LILEEP
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_ReceiveLileep
	end

RustboroCity_DevonCorp_2F_EventScript_AnorithReady:: @ 8211A2C
	bufferspeciesname 1, SPECIES_ANORITH
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorith
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveLileep:: @ 8211A3E
	setvar VAR_TEMP_1, SPECIES_LILEEP
	givemon SPECIES_LILEEP, 20, ITEM_NONE
	compare VAR_RESULT, 0
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_ReceiveLileepParty
	compare VAR_RESULT, 1
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_ReceiveLileepPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveLileepParty:: @ 8211A6E
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedLileepFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FinishReceivingLileep
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingLileep
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveLileepPC:: @ 8211A96
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedLileepFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_TransferLileepToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferLileepToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferLileepToPC:: @ 8211AB9
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingLileep
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedLileepFanfare:: @ 8211AC4
	bufferspeciesname 1, SPECIES_LILEEP
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname 0, SPECIES_LILEEP
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingLileep:: @ 8211AD7
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorith:: @ 8211AE1
	setvar VAR_TEMP_1, SPECIES_ANORITH
	givemon SPECIES_ANORITH, 20, ITEM_NONE
	compare VAR_RESULT, 0
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithParty
	compare VAR_RESULT, 1
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithParty:: @ 8211B11
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedAnorithFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAnorith
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAnorith
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithPC:: @ 8211B39
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedAnorithFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_TransferAnorithToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferAnorithToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferAnorithToPC:: @ 8211B5C
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAnorith
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedAnorithFanfare:: @ 8211B67
	bufferspeciesname 1, SPECIES_ANORITH
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname 0, SPECIES_ANORITH
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAnorith:: @ 8211B7A
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseFossil:: @ 8211B84
	message RustboroCity_DevonCorp_2F_Text_TwoFossilsPickOne
	waitmessage
	multichoice 17, 6, MULTI_FOSSIL, 0
	switch VAR_RESULT
	case 0, RustboroCity_DevonCorp_2F_EventScript_ChooseClawFossil
	case 1, RustboroCity_DevonCorp_2F_EventScript_ChooseRootFossil
	case 2, RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect
	case MULTI_B_PRESSED, RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseClawFossil:: @ 8211BC1
	goto RustboroCity_DevonCorp_2F_EventScript_GiveClawFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseRootFossil:: @ 8211BC7
	goto RustboroCity_DevonCorp_2F_EventScript_GiveRootFossil
	end

RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect:: @ 8211BCD
	release
	end

RustboroCity_DevonCorp_2F_EventScript_MatchCallScientist:: @ 8211BCF
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	compare VAR_RUSTBORO_CITY_STATE, 6
	goto_if_ge RustboroCity_DevonCorp_2F_EventScript_WorkOnNext
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_WorkOnNext:: @ 8211BF1
	msgbox RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon: @ 8211BFB
	.string "포켓몬과 대화할 수 있게 해주는 도구를\n"
	.string "개발하고 있는데...\p"
	.string "이게 좀처럼 쉽지가 않네요$"
	@ ポケモンと はなせる どうぐをｎ
	@ かいはつ しているのですが……ｐ
	@ なかなか うまく いかないね

RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls: @ 8211C50
	.string "지금 신형 몬스터볼을\n"
	.string "개발하고 있는데...\p"
	.string "이게 좀처럼 쉽지가 않네요$"
	@ いま しんがたの モンスタ-ボ-ルをｎ
	@ かいはつ しているのですが……ｐ
	@ なかなか うまく いかないね

RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls: @ 8211C99
	.string "드디어 신형 몬스터볼\n"
	.string "개발에 성공했어요!\p"
	.string "리피드볼을 쓰면\n"
	.string "이미 잡았던 포켓몬을\l"
	.string "더 쉽게 잡을 수 있어요!\p"
	.string "타이마볼은 포켓몬과의\n"
	.string "배틀 시간이 길면 길어질수록\l"
	.string "더 쉽게 잡을 수 있어요!\p"
	.string "둘 다 우리 회사의 야심작이니\n"
	.string "많이 사용해 주세요!$"
	@ しんがたの モンスタ-ボ-ルがｎ
	@ ついに かんせい したのです!ｐ
	@ リピ-トボ-ルを つかうとｎ
	@ いちど つかまえた ポケモンがｌ
	@ つかまえやすく なります!ｐ
	@ タイマ-ボ-ルは ポケモンとのｎ
	@ たたかいが ながびけば ながびくほどｌ
	@ つかまえやすく なります!ｐ
	@ どちらも わがしゃの じしんさくｎ
	@ ぜひ つかって ください!

RustboroCity_DevonCorp_2F_Text_IMadePokenav: @ 8211D9F
	.string "포켓내비를 만든 건 접니다!\p"
	.string "이야- 그런 엄청난 걸 만들게 되다니\n"
	.string "개발자로서 영광이라구요!$"
	@ ポケナビを つくったのは わたし!ｐ
	@ いや- あんな すごいモノを つくれるとｎ
	@ かいはつしゃ みょうりに つきますね!

RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav: @ 8211DF3
	.string "오오! 그건 포켓내비!\p"
	.string "포켓몬의 기분을 알고 싶다는\n"
	.string "사장님의 아이디어를\l"
	.string "실현시킨 물건이에요!\p"
	.string "자세히 설명해 드릴까요?\p"
	.string "... 아니지\n"
	.string "쓰다 보면 알게 되실 거예요!\l"
	.string "포켓내비를 많이 사용해 주세요!$"
	@ おお! それは ポケナビ!ｐ
	@ ポケモンの きもちを しりたいｎ
	@ という しゃちょうの アイデアをｌ
	@ じつげん したのです!ｐ
	@ くわしい せつめいを しましょうか?ｐ
	@ …… いやいやｎ
	@ そのうちに わかるでしょう!ｌ
	@ どんどん ポケナビを つかってくださいね!

RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams: @ 8211EE0
	.string "지금 포켓몬이 꾸고 있는\n"
	.string "꿈을 볼 수 있게 해주는 도구를\l"
	.string "개발하고 있는데...\p"
	.string "이게 좀처럼 쉽지가 않네요$"
	@ いま ポケモンが みているｎ
	@ ゆめを うつしだす どうぐをｌ
	@ かいはつ しているのですが……ｐ
	@ なかなか うまく いかないね

RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils: @ 8211F48
	.string "지금 포켓몬의 화석을\n"
	.string "재생하는 장치를\l"
	.string "개발하고 있는데...\p"
	.string "그럭저럭 잘 되고 있어요!$"
	@ いま ポケモンの かせきをｎ
	@ さいせい する そうちをｌ
	@ かいはつ していたのですが……ｐ
	@ なかなか うまく いきましたよ!

RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife: @ 8211FA6
	.string "당신이 갖고 있는 그건\n"
	.string "포켓몬의 화석!?\p"
	.string "괜찮으시면 제가 만든\n"
	.string "화석 재생 머신으로\l"
	.string "화석을 복원시켜도 될까요?$"
	@ きみの もっている それはｎ
	@ ポケモンの かせき!?ｐ
	@ よければ わたしが つくったｎ
	@ カセキ さいせい マシンでｌ
	@ いきかえらせて みましょうか?

RustboroCity_DevonCorp_2F_Text_OhIsThatSo: @ 8212046
	.string "아- 그렇군요\p"
	.string "데봉의 기술력은 대단한데 말이죠...$"
	@ あ- そうですかｐ
	@ デボンの ぎじゅつは すごいのにな……

RustboroCity_DevonCorp_2F_Text_TwoFossilsPickOne: @ 8212092
	.string "이럴 수가!\n"
	.string "화석을 두 개나 가지고 있으시군요!\p"
	.string "하지만 제 머신으로는\n"
	.string "하나씩밖에 재생할 수 없습니다\p"
	.string "어느 화석을 빌려주실 건가요?$"
	@ なんとまあ!ｎ
	@ かせきを ふたつも もってるんですか!ｐ
	@ でも わたしの マシンではｎ
	@ ひとつづつ しか さいせい できませんｐ
	@ どちらの かせきを かして くれますか?

RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher: @ 8212153
	.string "알겠습니다!\n"
	.string "그럼 바로...\p"
	.string "{PLAYER}{K_EUNNEUN} 데봉의 연구원에게\n"
	.string "{STR_VAR_1}{K_EULREUL} 맡겼다!$"
	@ わかりました!ｎ
	@ では さっそく……ｐ
	@ §あは デボンの けんきゅういんにｎ
	@ §いを あずけた!

RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime: @ 82121A2
	.string "제가 만든\n"
	.string "화석 재생 머신은 굉장하지만\l"
	.string "시간이 조금 걸리는 게 단점이죠...\p"
	.string "잠깐 다른 곳을\n"
	.string "견학하시는 게 어떨까요?$"
	@ わたしが つくったｎ
	@ カセキ さいせい マシンは すごいのですがｌ
	@ じかんが かかるのが けってん……ｐ
	@ すこし そこらへんをｎ
	@ けんがく なされては いかがですか?

RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife: @ 8212251
	.string "오래 기다리셨습니다!\n"
	.string "화석이 되살아났습니다!\p"
	.string "복원된 화석은 고대의 포켓몬\n"
	.string "{STR_VAR_2}입니다!$"
	@ おまたせ しました!ｎ
	@ カセキが いきかえり ましたよ!ｐ
	@ カセキは おおむかしの ポケモンｎ
	@ §う でしたよ!

RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher: @ 82122CB
	.string "{PLAYER}{K_EUNNEUN} 데봉의 연구원에게\n"
	.string "{STR_VAR_2}{K_EULREUL} 받았다!$"
	@ §あは デボンの けんきゅういんからｎ
	@ §うを うけとった!

@ Unused
RustboroCity_DevonCorp_2F_Text_TooManyPokemon: @ 82122F5
	.string "아- 포켓몬이 가득해서\n"
	.string "드릴 수가 없군요$"
	@ あ- ポケモン いっぱいでｎ
	@ もてないですね

RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature: @ 8212338
	.string "지금 포켓내비에 추가할 기능을\n"
	.string "개발하고 있는데...\p"
	.string "이게 좀처럼 쉽지가 않네요$"
	@ いま ポケナビに ついかする きのうをｎ
	@ かいはつ しているのですが……ｐ
	@ なかなか うまく いかないね

RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext: @ 8212386
	.string "자- 그럼 다음엔 어떤 장치를\n"
	.string "개발해 볼까...\p"
	.string "우리 회사는 번뜩이는 아이디어를\n"
	.string "점점 실현시켜 주니까\l"
	.string "연구자로서는 더할 나위가 없죠!$"
	@ さ-て つぎは どんな そうちをｎ
	@ かいはつ しようかな……ｐ
	@ うちの かいしゃは ひらめいた アイデアをｎ
	@ どんどん じつげん させて くれるからｌ
	@ けんきゅうしゃ みょうりに つきますよ!

