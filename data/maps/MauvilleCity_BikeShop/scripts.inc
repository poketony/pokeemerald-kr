MauvilleCity_BikeShop_MapScripts:: @ 820EBBB
	.byte 0

MauvilleCity_BikeShop_EventScript_Rydel:: @ 820EBBC
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, MauvilleCity_BikeShop_EventScript_AskSwitchBikes
	goto_if_set FLAG_DECLINED_BIKE, MauvilleCity_BikeShop_EventScript_SkipGreeting
	msgbox MauvilleCity_BikeShop_Text_RydelGreeting, MSGBOX_DEFAULT
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MauvilleCity_BikeShop_EventScript_YesFar
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_SkipGreeting:: @ 820EBF7
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MauvilleCity_BikeShop_EventScript_YesFar
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_ChooseBike:: @ 820EC16
	message MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne
	waitmessage
	multichoice 21, 8, MULTI_BIKE, 1
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_GetMachBike
	case 1, MauvilleCity_BikeShop_EventScript_GetAcroBike
	end

MauvilleCity_BikeShop_EventScript_NotFar:: @ 820EC3D
	setflag FLAG_DECLINED_BIKE
	msgbox MauvilleCity_BikeShop_Text_GuessYouDontNeedBike, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_YesFar:: @ 820EC4A
	setflag FLAG_RECEIVED_BIKE
	goto MauvilleCity_BikeShop_EventScript_ChooseBike
	end

MauvilleCity_BikeShop_EventScript_GetMachBike:: @ 820EC53
	msgbox MauvilleCity_BikeShop_Text_ChoseMachBike, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_GetAcroBike:: @ 820EC6D
	msgbox MauvilleCity_BikeShop_Text_ChoseAcroBike, MSGBOX_DEFAULT
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes:: @ 820EC87
	msgbox MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes, MSGBOX_DEFAULT
	special SwapRegisteredBike
	release
	end

MauvilleCity_BikeShop_EventScript_AskSwitchBikes:: @ 820EC94
	msgbox MauvilleCity_BikeShop_Text_WantToSwitchBikes, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MauvilleCity_BikeShop_EventScript_SwitchBikes
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_BikeShop_EventScript_KeepBike
	end

@ If the player does not have a bike on them Rydel assumes its stored in the PC
MauvilleCity_BikeShop_EventScript_SwitchBikes:: @ 820ECB3
	msgbox MauvilleCity_BikeShop_Text_IllSwitchBikes, MSGBOX_DEFAULT
	checkitem ITEM_ACRO_BIKE, 1
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_BikeShop_EventScript_SwitchAcroForMach
	checkitem ITEM_MACH_BIKE, 1
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_BikeShop_EventScript_SwitchMachForAcro
	msgbox MauvilleCity_BikeShop_Text_OhYourBikeIsInPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_KeepBike:: @ 820ECE5
	msgbox MauvilleCity_BikeShop_Text_HappyYouLikeIt, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_SwitchAcroForMach:: @ 820ECEF
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedAcroForMach, MSGBOX_DEFAULT
	removeitem ITEM_ACRO_BIKE
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_SwitchMachForAcro:: @ 820ED10
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedMachForAcro, MSGBOX_DEFAULT
	removeitem ITEM_MACH_BIKE
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_Assistant:: @ 820ED31
	msgbox MauvilleCity_BikeShop_Text_HandbooksAreInBack, MSGBOX_NPC
	end

MauvilleCity_BikeShop_EventScript_MachBikeHandbook:: @ 820ED3A
	message MauvilleCity_BikeShop_Text_MachHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage:: @ 820ED46
	multichoice 0, 0, MULTI_MACH_BIKE_INFO, 0
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_HowToRide
	case 1, MauvilleCity_BikeShop_EventScript_HowToTurn
	case 2, MauvilleCity_BikeShop_EventScript_SandySlopes
	case 3, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	end

MauvilleCity_BikeShop_EventScript_HowToRide:: @ 820ED88
	message MauvilleCity_BikeShop_Text_HowToRideMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_HowToTurn:: @ 820ED94
	message MauvilleCity_BikeShop_Text_HowToTurnMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_SandySlopes:: @ 820EDA0
	message MauvilleCity_BikeShop_Text_SandySlopes
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitMachHandbook:: @ 820EDAC
	release
	end

MauvilleCity_BikeShop_EventScript_AcroBikeHandbook:: @ 820EDAE
	message MauvilleCity_BikeShop_Text_AcroHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage:: @ 820EDBA
	multichoice 0, 0, MULTI_ACRO_BIKE_INFO, 0
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_Wheelies
	case 1, MauvilleCity_BikeShop_EventScript_BunnyHops
	case 2, MauvilleCity_BikeShop_EventScript_Jumps
	case 3, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	end

MauvilleCity_BikeShop_EventScript_Wheelies:: @ 820EDFC
	message MauvilleCity_BikeShop_Text_Wheelies
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_BunnyHops:: @ 820EE08
	message MauvilleCity_BikeShop_Text_BunnyHops
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_Jumps:: @ 820EE14
	message MauvilleCity_BikeShop_Text_Jumps
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitAcroHandbook:: @ 820EE20
	release
	end

MauvilleCity_BikeShop_Text_RydelGreeting: @ 820EE22
	.string "...어라? 이거 참 꽤나\n"
	.string "활기찬 손님이 오셨군!\p"
	.string "사람들은 날 미스터 카제노라 부르지\n"
	.string "이 사이클숍의 오너란다!$"
	// ……おや? こりゃまた ずいぶんｎ
	// げんきそうな おきゃくさんが きたのう!ｐ
	// わたしは ひとよんで ミスタ-カゼノｎ
	// この サイクルショップの オ-ナ-さ!

MauvilleCity_BikeShop_Text_DidYouComeFromFarAway: @ 820EE99
	.string "카제노: 네 러닝슈즈...\n"
	.string "굉장히 지저분한데\l"
	.string "어디 멀리서 왔니?$"
	// カゼノ『きみの ランニングシュ-ズｎ
	// ものすごく よごれて いるけどｌ
	// どこか とおくから やってきたのかい?

MauvilleCity_BikeShop_Text_GuessYouDontNeedBike: @ 820EEE8
	.string "카제노: 그러니?\n"
	.string "그럼 내 자전거는\l"
	.string "필요 없을 것 같구나$"
	// カゼノ『そうかい?ｎ
	// じゃあ わたしの じてんしゃはｌ
	// ひつよう なさそうだね

MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne: @ 820EF32
	.string "카제노: 흠흠...\n"
	.string "뭐라고 미로마을에서 이곳까지!?\n"
	.string "굉장히 먼 곳이잖아!\p"
	.string "내 자전거가 있으면\n"
	.string "기분 좋은 바람을 느끼며\l"
	.string "여러 곳에 편하게 갈 수 있을 텐데!\p"
	.string "좋-아!\n"
	.string "너에게 자전거를 줄게!\p"
	.string "아니 잠깐만 기다려!\p"
	.string "자전거에는 두 가지\n"
	.string "타입이 있다는 걸 잊고 있었군!\p"
	.string "그건 말이지...\n"
	.string "마하자전거와 더트자전거야!\p"
	.string "마하자전거는\n"
	.string "온몸으로 바람을 느끼고 싶은 사람에게!\p"
	.string "더트자전거는\n"
	.string "테크닉을 즐기고 싶은 사람에게!\p"
	.string "아저씨는 친절한 사람이니까\n"
	.string "네가 좋아하는 쪽을 주겠어!\p"
	.string "자! 어느 쪽을 선택할래?$"
	// カゼノ『フムフム……ｐ
	// なんと ミシロタウンから はるばると!?ｎ
	// すごい とおく じゃないか?ｐ
	// わたしの じてんしゃが あればｎ
	// ここちよい かぜを かんじながらｌ
	// らくに いろんな ところへ いけるのに!ｐ
	// よ-し!ｎ
	// きみに じてんしゃを あげよう!ｐ
	// いや ちょっと まて!ｐ
	// じてんしゃ には 2しゅるいのｎ
	// タイプが あるのを わすれとった!ｐ
	// それはな……ｎ
	// マッハじてんしゃと ダ-トじてんしゃだ!ｐ
	// マッハじてんしゃはｎ
	// ぜんしんで かぜを かんじたい ひとに!ｐ
	// ダ-トじてんしゃはｎ
	// テクニックを たのしみたい ひとに!ｐ
	// おじさん しんせつ だからｎ
	// きみの すきな ほうを あげちゃうよ!ｐ
	// さあ! どちらを えらぶ?

MauvilleCity_BikeShop_Text_ChoseMachBike: @ 820F18D
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "마하자전거를 선택했다!$"
	// §あはｎ
	// マッハじてんしゃを えらんだ!

MauvilleCity_BikeShop_Text_ChoseAcroBike: @ 820F1A5
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "더트자전거를 선택했다!$"
	// §あはｎ
	// ダ-トじてんしゃを えらんだ!

MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes: @ 820F1BD
	.string "카제노: 만일 다른 타입으로\n"
	.string "교환하고 싶을 때는\l"
	.string "언제든지 내게 말을 걸어 주렴!$"
	// カゼノ『もしも べつの タイプとｎ
	// こうかん したくなった ときにはｌ
	// いつでも わたしに こえを かけてくれ!

MauvilleCity_BikeShop_Text_WantToSwitchBikes: @ 820F1FB
	.string "카제노: 응? 다른 타입의\n"
	.string "자전거로 갈아타고 싶어진 거냐?$"
	// カゼノ『おや? ちがう タイプのｎ
	// じてんしゃに のりかえたく なったのかな?

MauvilleCity_BikeShop_Text_IllSwitchBikes: @ 820F22F
	.string "카제노: 그럼 네가 지금 가지고 있는\n"
	.string "자전거와 교환해주지!$"
	// カゼノ『じゃあ きみが いま もっているｎ
	// じてんしゃを こうかん してあげよう!

MauvilleCity_BikeShop_Text_ExchangedMachForAcro: @ 820F263
	.string "{PLAYER}{K_EUNNEUN} 마하자전거를\n"
	.string "더트자전거로 교환 받았다!$"
	// §あは マッハじてんしゃをｎ
	// ダ-トじてんしゃに かえてもらった!

MauvilleCity_BikeShop_Text_ExchangedAcroForMach: @ 820F294
	.string "{PLAYER}{K_EUNNEUN} 더트자전거를\n"
	.string "마하자전거로 교환 받았다!$"
	// §あは ダ-トじてんしゃをｎ
	// マッハじてんしゃに かえてもらった!

MauvilleCity_BikeShop_Text_HappyYouLikeIt: @ 820F2C4
	.string "카제노: 그래 그래!\n"
	.string "맘에 들어하니 기쁘구나!$"
	// カゼノ『そうか そうか!ｎ
	// きにいってくれて うれしいぞ!

MauvilleCity_BikeShop_Text_OhYourBikeIsInPC: @ 820F2F3
	.string "응?\n"
	.string "너에게 주었던 자전거는 어쨌니?\p"
	.string "그렇군 PC에 맡겨놓았구나\p"
	.string "PC에서 꺼내서 가지고 오면\n"
	.string "교환해줄게!\p"
	.string "너의 모험이...\n"
	.string "순조롭게 풀리길 기원하마!$"
	// ……おや?ｎ
	// きみに あげた じてんしゃ どうした?ｐ
	// そうか パソコンに あずけてあるのかｐ
	// パソコンから とりだして もってきたらｎ
	// こうかんして あげる からな!ｐ
	// きみの ぼうけんに……ｎ
	// おいかぜが ふくことを いのってるよ!

MauvilleCity_BikeShop_Text_HandbooksAreInBack: @ 820F3C3
	.string "나는 여기에서 일하면서\n"
	.string "자전거를 공부하고 있어\p"
	.string "자전거 타는 방법 중에\n"
	.string "잘 모르는 것이 있으면\p"
	.string "안쪽 방에 설명서가 있으니까\n"
	.string "그걸 읽어보는 게 좋아!$"
	// ぼくは ここで はたらき ながらｎ
	// じてんしゃの べんきょうを してるんだｐ
	// じてんしゃの のりかたでｎ
	// なにか わからないことが あったらｐ
	// おくのへやに かいせつしょが あるからｎ
	// それを よんでみると いいよ!

MauvilleCity_BikeShop_Text_MachHandbookWhichPage: @ 820F445
	.string "마하자전거의\n"
	.string "설명서가 놓여 있다!\p"
	.string "어느 페이지를 읽어볼까?$"
	// マッハじてんしゃのｎ
	// かいせつしょが おいてある!ｐ
	// どの ペ-ジを よもうかな?

MauvilleCity_BikeShop_Text_HowToRideMachBike: @ 820F487
	.string "자전거에 타서 십자 버튼을\n"
	.string "조작하는 방향으로\l"
	.string "자전거가 달립니다!\p"
	.string "달리는 동안에 조금씩\n"
	.string "속도가 빨라질 겁니다!\p"
	.string "멈추고 싶을 때는 십자 버튼에서\n"
	.string "손을 떼면 속도가 느려져\l"
	.string "자연스레 멈추게 됩니다!\p"
	.string "...다른 페이지를 읽겠습니까?$"
	// じてんしゃに のって じゅうじボタンをｎ
	// おしたほうに じてんしゃは はしります!ｐ
	// すこし はしっていく うちにｎ
	// スピ-ドが あがっていく でしょう!ｐ
	// とまりたいときは じゅうじボタンからｎ
	// てを はなせば スピ-ドが おちてｌ
	// しぜんに とまって くれるはずです!ｐ
	// ……べつの ペ-ジを よみますか?

MauvilleCity_BikeShop_Text_HowToTurnMachBike: @ 820F550
	.string "마하자전거는 스피드가 빨라\n"
	.string "갑자기 멈출 수는 없습니다\p"
	.string "그래서 모퉁이를 돌기 위해서는\n"
	.string "약간의 요령이 필요합니다\p"
	.string "돌고 싶은 모퉁이보다 조금 앞에서\n"
	.string "십자 버튼에서 손을 떼서\l"
	.string "속도를 떨어뜨려\l"
	.string "돌 수 있을 겁니다!\p"
	.string "...다른 페이지를 읽겠습니까?$"
	// マッハじてんしゃは スピ-ドが はやくてｎ
	// きゅうに とまることは できませんｐ
	// だから かどを まがるときにはｎ
	// ちょっとした コツが ひつようです!ｐ
	// まがりたい かどの すこし てまえでｎ
	// じゅうじボタンから てを はなしてｌ
	// スピ-ドを おとして まがりましょう!ｐ
	// ……べつの ペ-ジを よみますか?

MauvilleCity_BikeShop_Text_SandySlopes: @ 820F61A
	.string "호연지방에는 여기저기에\n"
	.string "모래 비탈길이 있습니다!\p"
	.string "그곳은 모래가 무너지기 쉬워서\n"
	.string "일반적으로는 넘어갈 수 없지만\l"
	.string "마하자전거를 타고 있으면\l"
	.string "놀랍게도 넘어갈 수 있습니다!\p"
	.string "...다른 페이지를 읽겠습니까?$"
	// ホウエンちほうには ところどころにｎ
	// ちいさな すなのさかが あります!ｐ
	// そこは すなが くずれやすい ためにｎ
	// ふつうは のぼることが できませんがｐ
	// マッハじてんしゃに のっていればｎ
	// のぼることが できるのです!ｐ
	// ……べつの ペ-ジを よみますか?

MauvilleCity_BikeShop_Text_AcroHandbookWhichPage: @ 820F6ED
	.string "더트자전거의\n"
	.string "설명서가 놓여 있다!\p"
	.string "어느 페이지를 읽어볼까?$"
	// ダ-トじてんしゃのｎ
	// かいせつしょが おいてある!ｐ
	// どの ペ-ジを よもうかな?

MauvilleCity_BikeShop_Text_Wheelies: @ 820F72F
	.string "자전거를 타고 B 버튼을 누르면\n"
	.string "그 장소에서 앞바퀴가 들립니다!\p"
	.string "그 상태에서 십자 버튼을\n"
	.string "조작하면\l"
	.string "앞바퀴를 든 상태로\l"
	.string "달릴 수 있습니다!\p"
	.string "이것이 윌리라고\n"
	.string "불리는 테크닉입니다!\p"
	.string "...다른 페이지를 읽겠습니까?$"
	// じてんしゃに のって ビ-ボタンを おすとｎ
	// そのばで ぜんりんが もちあがります!ｐ
	// そのままで じゅうじボタンを おせばｎ
	// ぜんりんを あげた じょうたいでｌ
	// はしることが できるのです!ｐ
	// それが ウイリ-という テクニック!ｐ
	// ……べつの ペ-ジを よみますか?

MauvilleCity_BikeShop_Text_BunnyHops: @ 820F7F5
	.string "B 버튼을 누른 채로 있으면\n"
	.string "윌리를 하며 그 장소에서 뿅뿅\l"
	.string "튀어 오를 수 있습니다!\p"
	.string "이것이 다니엘이라\n"
	.string "불리는 테크닉입니다!\p"
	.string "다니엘 상태에서\n"
	.string "달리는 것도 가능합니다!\p"
	.string "...다른 페이지를 읽겠습니까?$"
	// ビ-ボタンを おしたままに しているとｎ
	// ウイリ-しながら そのばで ピョンピョンｌ
	// とびはねることが できます!ｐ
	// それが ダニエルという テクニック!ｐ
	// ダニエルのまま はしることも できます!ｐ
	// ……べつの ペ-ジを よみますか?

MauvilleCity_BikeShop_Text_Jumps: @ 820F898
	.string "더트자전거를 탔을 때\n"
	.string "B 버튼과 십자 버튼을\l"
	.string "동시에 조작하면 점프합니다!\p"
	.string "옆쪽으로 조작하면 옆으로 점프!\p"
	.string "뒤쪽으로 조작하면 점프하면서\n"
	.string "방향을 바꿀 수 있습니다!\p"
	.string "...다른 페이지를 읽겠습니까?$"
	// ダ-トじてんしゃに のっているときｎ
	// じゅうじボタンと ビ-ボタンをｌ
	// どうじに おすと ジャンプします!ｐ
	// よこへ おせば よこに ジャンプ!ｐ
	// うしろへ おせば ジャンプしながらｎ
	// ほうこうを かえることが できます!ｐ
	// ……べつの ペ-ジを よみますか?

