Route109_SeashoreHouse_MapScripts:: @ 82693F4
	map_script MAP_SCRIPT_ON_TRANSITION, Route109_SeashoreHouse_OnTransition
	.byte 0

Route109_SeashoreHouse_OnTransition: @ 82693FA
	setflag FLAG_LANDMARK_SEASHORE_HOUSE
	end

Route109_SeashoreHouse_EventScript_Owner:: @ 82693FE
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_6_SODA_POP, Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop
	goto_if_set FLAG_DEFEATED_SEASHORE_HOUSE, Route109_SeashoreHouse_EventScript_DefeatedTrainers
	goto_if_set FLAG_TEMP_2, Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction
	msgbox Route109_SeashoreHouse_Text_SeashoreHouseIntro, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction:: @ 8269428
	msgbox Route109_SeashoreHouse_Text_ShowMeSomeHotMatches, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_DefeatedTrainers:: @ 8269432
	msgbox Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles, MSGBOX_DEFAULT
	giveitem ITEM_SODA_POP, 6
	compare VAR_RESULT, FALSE
	goto_if_eq Route109_SeashoreHouse_EventScript_BagFull
	setflag FLAG_RECEIVED_6_SODA_POP
	release
	end

Route109_SeashoreHouse_EventScript_BagFull:: @ 8269456
	msgbox Route109_SeashoreHouse_Text_BagFull, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop:: @ 8269460
	showmoneybox 0, 0, 0
	msgbox Route109_SeashoreHouse_Text_WantToBuySodaPop, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route109_SeashoreHouse_EventScript_BuySodaPop
	msgbox Route109_SeashoreHouse_Text_ThatsTooBad, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_BuySodaPop:: @ 8269484
	checkmoney 300, 0
	compare VAR_RESULT, FALSE
	goto_if_eq Route109_SeashoreHouse_EventScript_NotEnoughMoney
	checkitemspace ITEM_SODA_POP, 1
	compare VAR_RESULT, FALSE
	goto_if_eq Route109_SeashoreHouse_EventScript_NotEnoughSpace
	msgbox Route109_SeashoreHouse_Text_HereYouGo, MSGBOX_DEFAULT
	removemoney 300, 0
	updatemoneybox 0, 0
	giveitem ITEM_SODA_POP
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughMoney:: @ 82694C8
	msgbox Route109_SeashoreHouse_Text_NotEnoughMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughSpace:: @ 82694D5
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_Dwayne:: @ 82694E2
	trainerbattle_single TRAINER_DWAYNE, Route109_SeashoreHouse_Text_DwayneIntro, Route109_SeashoreHouse_Text_DwayneDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_DwaynePostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Johanna:: @ 82694FD
	trainerbattle_single TRAINER_JOHANNA, Route109_SeashoreHouse_Text_JohannaIntro, Route109_SeashoreHouse_Text_JohannaDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_JohannaPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Simon:: @ 8269518
	trainerbattle_single TRAINER_SIMON, Route109_SeashoreHouse_Text_SimonIntro, Route109_SeashoreHouse_Text_SimonDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_SimonPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_CheckTrainersCompletion:: @ 8269533
	goto_if_not_defeated TRAINER_DWAYNE, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_JOHANNA, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_SIMON, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	setflag FLAG_DEFEATED_SEASHORE_HOUSE
	release
	end

Route109_SeashoreHouse_EventScript_TrainersNotCompleted:: @ 8269553
	release
	end

Route109_SeashoreHouse_Text_SeashoreHouseIntro: @ 8269555
	.string "난 바다의 집 아저씨!\n"
	.string "사람들은 바다아저씨라고 부르지!\p"
	.string "어쨌든 뜨거운 포켓몬 승부를\n"
	.string "보는 걸 정말 좋아한다고-!\p"
	.string "자네도 말이야- 뜨-거운 하트로\n"
	.string "여기에 있는 트레이너를 상대로\l"
	.string "이기면 내가 좋은 걸 줄게-$"
	// わし うみのいえ の オヤジ!ｎ
	// ひとよんで うみサン!ｐ
	// とにかく あつい ポケモンしょうぶをｎ
	// みることが だいすき なんだよね-!ｐ
	// キミもね- あつ-い ハ-トでｎ
	// ここに いる トレ-ナ-ぜんいんにｌ
	// かてたら いいものを あげるよ-

Route109_SeashoreHouse_Text_ShowMeSomeHotMatches: @ 8269635
	.string "뜨-거운 승부를 보여줘!\p"
	.string "난 그거 하나만 보고\n"
	.string "이 바다의 집을 열고 있는 거라고-!$"
	// あつ-い しょうぶ みせてくれ-!ｐ
	// そのためだけに わしｎ
	// この うみのいえを やってるんだね-!

Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles: @ 8269685
	.string "자네 대단한데-!\n"
	.string "뜨거운 포켓몬 승부였어-\l"
	.string "나 정말 대만족했다고-!\p"
	.string "이건 뜨거운 승부를 보여 준\n"
	.string "자네에게 주는 감사의 표시야\p"
	.string "미네랄사이다 반 세트 가져가-$"
	// きみ すごいね-!ｎ
	// あつい ポケモンしょうぶ だった-ｌ
	// わし だいまんぞく だよ-!ｐ
	// これは あつい しょうぶを みせてくれたｎ
	// きみへの おれい だよ-ｐ
	// サイコソ-ダ はんダ-ス もっていきなよ-

Route109_SeashoreHouse_Text_BagFull: @ 826973A
	.string "주려고 했는데 가방이 가득 찼네-\n"
	.string "그럼 맡아 둘게$"
	// と おもったけど バッグ いっぱいか-ｎ
	// じゃあ あずかっておくよ-

Route109_SeashoreHouse_Text_WantToBuySodaPop: @ 826977E
	.string "포켓몬도 정말 좋아하는 미네랄사이다\n"
	.string "한 병에 300원이야-\l"
	.string "사 가라구-!$"
	// ポケモンも だいすき サイコソ-ダｎ
	// いっぽん 300えん だよ-ｌ
	// かって いきなよ-!

Route109_SeashoreHouse_Text_HereYouGo: @ 82697C8
	.string "자 여기-$"
	// はいよ-

Route109_SeashoreHouse_Text_NotEnoughMoney: @ 82697D5
	.string "돈이 부족해-$"
	// おかねが ないよ-

Route109_SeashoreHouse_Text_ThatsTooBad: @ 82697EF
	.string "그거 아쉽네-$"
	// それは ざんねん だね-

Route109_SeashoreHouse_Text_DwayneIntro: @ 8269803
	.string "이 바다의 집에서 가장\n"
	.string "뜨거운 포켓몬 승부를 할 수 있는 건\l"
	.string "바로 이 몸이시라고!!$"
	// この うみのいえで いちばんｎ
	// あつい ポケモンしょうぶが できるのはｌ
	// この オレさま だぜ!!

Route109_SeashoreHouse_Text_DwayneDefeated: @ 8269867
	.string "확실히 뜨거운 승부였다\n"
	.string "패배를 납득할 수밖에 없는 느낌이군!$"
	// たしかに あつい しょうぶ だったｎ
	// まけて なっとく って かんじ だぜ!

Route109_SeashoreHouse_Text_DwaynePostBattle: @ 826989D
	.string "나는 잿빛도시에 올 때마다\n"
	.string "이곳의 뜨거운 승부와\l"
	.string "시원한 미네랄사이다를 즐기지!$"
	// オレは カイナに くるたびにｎ
	// ここで あつい しょうぶとｌ
	// つめたい サイコソ-ダを たのしむんだ!

Route109_SeashoreHouse_Text_JohannaIntro: @ 82698E3
	.string "따분한 승부는 필요 없어!\p"
	.string "타오르는 듯한 승부야말로\n"
	.string "트레이너와 포켓몬을 강하게 만들지!$"
	// たいくつな しょうぶ なんて ムダ!ｐ
	// もえあがるような しょうぶ こそｎ
	// トレ-ナ-と ポケモンを きたえるのよ!

Route109_SeashoreHouse_Text_JohannaDefeated: @ 8269947
	.string "너무 뜨겁잖아!$"
	// あつい じゃない!

Route109_SeashoreHouse_Text_JohannaPostBattle: @ 8269953
	.string "아-아 목마르다\n"
	.string "미네랄사이다나 마실까?$"
	// あ-あ のどが かわいちゃったｎ
	// サイコソ-ダ のもうかな?

Route109_SeashoreHouse_Text_SimonIntro: @ 8269986
	.string "내 포켓몬의 굉장함을\n"
	.string "똑똑히 보여줄 테니까 울지 말라고!$"
	// ぼくの ポケモンの すごいところｎ
	// みせちゃうけど なかないでよ!

Route109_SeashoreHouse_Text_SimonDefeated: @ 82699C5
	.string "...졌지만 울지 않겠어$"
	// ……まけたけど なかないぞ

Route109_SeashoreHouse_Text_SimonPostBattle: @ 82699DF
	.string "포켓몬이 날 태우고\n"
	.string "물 위를 나아가는 기술을 쓸 수 있다면\l"
	.string "튜브도 필요 없을 텐데$"
	// ポケモンが ぼくを のせてｎ
	// みずの うえを すすむ わざを つかえたらｌ
	// うきわも いらなくなるのに

