SafariZone_EventScript_OutOfBallsMidBattle:: @ 82A4B4C
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	setwarp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 255, 2, 5
	end

SafariZone_EventScript_Exit:: @ 82A4B5D
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	warp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 255, 2, 5
	waitstate
	end

SafariZone_EventScript_RetirePrompt:: @ 82A4B6F
	lockall
	msgbox SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SafariZone_EventScript_Retire
	releaseall
	end

SafariZone_EventScript_Retire:: @ 82A4B85
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_TimesUp:: @ 82A4B8A
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_TimesUp
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_OutOfBalls:: @ 82A4B9B
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_OutOfBalls
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

EventScript_PokeBlockFeeder:: @ 82A4BAC
	lockall
	special GetPokeblockFeederInFront
	compare VAR_RESULT, 0xFFFF
	goto_if_ne SafariZone_EventScript_PokeblockPresent
	msgbox SafariZone_Text_PlacePokeblockOnFeeder, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SafariZone_EventScript_ChoosePokeblock
	releaseall
	end

SafariZone_EventScript_ChoosePokeblock:: @ 82A4BD0
	fadescreen FADE_TO_BLACK
	special OpenPokeblockCaseOnFeeder
	waitstate
	compare VAR_RESULT, 0xFFFF
	goto_if_ne SafariZone_EventScript_PokeblockPlaced
	end

SafariZone_EventScript_PokeblockPlaced:: @ 82A4BE2
	message SafariZone_Text_PokeblockWasPlaced
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_EventScript_PokeblockPresent:: @ 82A4BEB
	message SafariZone_Text_PokeblockStillHere
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_Text_WouldYouLikeToExit: @ 82A4BF4
	.string "사파리존을\n"
	.string "이대로 종료하시겠습니까?$"
	@ サファリゾ-ンをｎ
	@ このまま しゅうりょう しますか?

SafariZone_Text_TimesUp: @ 82A4C26
	.string "딩동! 시간이 다 되었습니다!\n"
	.string "사파리게임을 종료합니다$"
	@ ピンポ-ン! じかん で-す!ｎ
	@ サファリゲ-ムを しゅうりょう します

SafariZone_Text_OutOfBalls: @ 82A4C56
	.string "사파리볼이 다 떨어졌으므로\n"
	.string "사파리게임을 종료합니다$"
	@ サファリボ-ルを つかいきったのでｎ
	@ サファリゲ-ムを しゅうりょう します

SafariZone_Text_PlacePokeblockOnFeeder: @ 82A4C90
	.string "포켓몬스넥먹이통에\n"
	.string "포켓몬스넥을 놓겠습니까?$"
	@ ポロックおきばに ポロックを おきますか?

SafariZone_Text_PokeblockStillHere: @ 82A4CC5
	.string "아직 {STR_VAR_1}{K_IGA} 남아있습니다$"
	@ まだ §いが のこっています

SafariZone_Text_PokeblockWasPlaced: @ 82A4CEB
	.string "{STR_VAR_1}{K_EULREUL}\n"
	.string "놓았습니다!$"
	@ §いをｎ
	@ おきました!

Route121_SafariZoneEntrance_Text_WelcomeToSafariZone: @ 82A4D12
	.string "사파리존에 어서 오세요!\p"
	.string "여기에서는 호연에서는 좀처럼\n"
	.string "볼 수 없는 포켓몬을\p"
	.string "자연의 모습 그대로\n"
	.string "볼 수 있습니다\p"
	.string "게다가 포켓몬 트레이너의\n"
	.string "요구를 반영해서\p"
	.string "포켓몬을\n"
	.string "잡을 수 있게 되었습니다!\p"
	.string "사파리존을 즐겨 주세요!$"
	@ サファリゾ-ンへ ようこそ!ｐ
	@ ここでは ホウエンでは なかなかｎ
	@ みることの できない ポケモンをｐ
	@ しぜんの すがたの ままｎ
	@ めに することが できますｐ
	@ また ポケモントレ-ナ-のｎ
	@ ようぼうに おこたえ してｐ
	@ ポケモンをｎ
	@ つかまえる ことも できます!ｐ
	@ サファリゾ-ンを たのしんで いってね!

Route121_SafariZoneEntrance_Text_WelcomeFirstTime: @ 82A4E46
	.string "사파리존에 어서 오세요!\n"
	.string "사파리존은 처음입니까?$"
	@ サファリゾ-ンへ ようこそ!ｎ
	@ サファリゾ-ンは はじめて ですか?

Route121_SafariZoneEntrance_Text_ComeInAndEnjoy: @ 82A4E7E
	.string "사파리존을 즐겨 주세요!$"
	@ サファリゾ-ンを たのしんで いってね!

Route121_SafariZoneEntrance_Text_FirstTimeInfo: @ 82A4EA1
	.string "사파리존에서는\n"
	.string "30개의 사파리볼을 사용해서\l"
	.string "포켓몬을 잡을 수 있습니다\p"
	.string "사파리볼을 다 쓰거나\n"
	.string "500걸음 걸으면\p"
	.string "게임은 종료됩니다\p"
	.string "사파리존을 즐겨 주세요!$"
	@ サファリゾ-ンではｎ
	@ 30この サファリボ-ルを つかってｌ
	@ ポケモンを つかまえる ことが できますｐ
	@ サファリボ-ルを つかいきるかｎ
	@ 500ぽ あるくとｐ
	@ ゲ-ムは しゅうりょう ですｐ
	@ サファリゾ-ンを たのしんで いってね!

Route121_SafariZoneEntrance_Text_WouldYouLikeToPlay: @ 82A4F74
	.string "사파리존에 어서 오세요!\p"
	.string "500원으로 포켓몬 무제한 잡기!\n"
	.string "사파리게임에 참가하시겠습니까?$"
	@ サファリゾ-ンへ ようこそ!ｐ
	@ 500えんで ポケモン つかまえほうだい!ｎ
	@ サファリゲ-ムに さんか しますか?

Route121_SafariZoneEntrance_Text_PlayAnotherTime: @ 82A4FD7
	.string "그렇군요\n"
	.string "다음번에는 꼭 참가해 주십시오!$"
	@ そうですかｎ
	@ こんど ぜひ さんか してください!

Route121_SafariZoneEntrance_Text_NotEnoughMoney: @ 82A4FF7
	.string "돈이 부족합니다!$"
	@ おかねが たりませんよ!

Route121_SafariZoneEntrance_Text_ThatWillBe500Please: @ 82A501B
	.string "그럼 500원 받겠습니다$"
	@ それでは 500えん いただきます

Route121_SafariZoneEntrance_Text_HereAreYourSafariBalls: @ 82A5036
	.string "여기 사파리볼 받으세요!$"
	@ では サファリボ-ルを どうぞ!

Route121_SafariZoneEntrance_Text_Received30SafariBalls: @ 82A5052
	.string "{PLAYER}{K_EUNNEUN} 사파리볼을\n"
	.string "30개 받았다!$"
	@ §あは サファリボ-ルをｎ
	@ 30こ うけとった!

Route121_SafariZoneEntrance_Text_PleaseEnjoyYourself: @ 82A506F
	.string "시간이 다 되면\n"
	.string "이쪽에서 알려드리므로\p"
	.string "충분히 즐겨 주십시오!\n"
	.string "그럼 다녀오세요!$"
	@ じかんに なりましたらｎ
	@ こちらから おしらせ しますのでｐ
	@ ぞんぶんに おたのしみ ください!ｎ
	@ では いってらっしゃい!

Route121_SafariZoneEntrance_Text_PCIsFull: @ 82A50E5
	.string "손님!\n"
	.string "박스가 가득합니다!$"
	@ おきゃくさん!ｎ
	@ ボックスが いっぱい ですよ!

Route121_SafariZoneEntrance_Text_YouNeedPokeblockCase: @ 82A5105
	.string "아! 손님\n"
	.string "포켓몬스넥케이스를 안 갖고 계시는군요?\p"
	.string "사파리존은 포켓몬스넥을 쓰면\n"
	.string "보다 재밌게 즐길 수 있으니\p"
	.string "꼭 포켓몬스넥케이스를\n"
	.string "가지고 와주십시오\p"
	.string "포켓몬스넥케이스는\n"
	.string "해안시티의 콘테스트 회장에서\l"
	.string "받을 수 있답니다$"
	@ あ! おきゃくさんｎ
	@ ポロックケ-スを おもちで ないですね?ｐ
	@ サファリゾ-ンは ポロックを つかうとｎ
	@ より おたのしみ いただけますのでｐ
	@ ぜひ ポロックケ-スをｎ
	@ おもちに なって おこし くださいｐ
	@ ポロックケ-スはｎ
	@ ミナモシティの コンテストかいじょうでｌ
	@ うけとることが できますよ

SafariZone_South_Text_StillHaveTimeExit: @ 82A51D4
	.string "아직 시간이 남아 있습니다만\n"
	.string "사파리존을 그만두시겠습니까?$"
	@ まだ じかんが のこっていますがｎ
	@ サファリゾ-ンを やめますか?

SafariZone_South_Text_EnjoyTheRestOfYourAdventure: @ 82A521A
	.string "그럼 계속해서 즐겨 주세요!$"
	@ では ひきつづき おたのしみ ください!

SafariZone_South_Text_ExitEarlyThankYouForPlaying: @ 82A5248
	.string "알겠습니다\p"
	.string "그럼 남은 사파리볼은\n"
	.string "이쪽으로 주세요\p"
	.string "수고하셨습니다\n"
	.string "또 이용해 주세요$"
	@ わかりましたｐ
	@ それでは のこりの サファリボ-ルをｎ
	@ おあずかり しますｐ
	@ おつかれさまでしたｎ
	@ また ごりよう ください

SafariZone_South_Text_GoodLuck: @ 82A52AB
	.string "그럼 다녀오세요!\p"
	.string "무슨 일이 있으면\n"
	.string "제게 말을 걸어 주세요$"
	@ それでは いってらっしゃい!ｌ
	@ なにか ありましたらｎ
	@ わたしに こえを かけて くださいね

SafariZone_South_Text_Boy: @ 82A52EF
	.string "알고 있었어?\p"
	.string "저 네모난 상자에 포켓몬스넥을 놓으면\n"
	.string "포켓몬이 모여들어!$"
	@ しってた?ｐ
	@ あの しかくい はこに ポロックを おくとｎ
	@ ポケモンが あつまって くるんだよ!

SafariZone_South_Text_Man: @ 82A533B
	.string "이 앞으로 가고 싶지만\n"
	.string "자전거 갖고 오는 걸 까먹었어...\p"
	.string "깊숙한 곳에 희귀한 포켓몬이\n"
	.string "있을 것 같은데 말이지!$"
	@ この さきに いきたい けどｎ
	@ じてんしゃ もって くるの わすれた……ｐ
	@ おくに めずらしい ポケモンがｎ
	@ いそうな きが するのに!

SafariZone_Southwest_Text_Woman: @ 82A53B7
	.string "포켓몬에게 포켓몬스넥을 던져도\n"
	.string "무시당할 때가 있어\p"
	.string "포켓몬에게도 취향이 있는 걸까?$"
	@ ポケモンに ポロックを なげてもｎ
	@ しらんぷり される ときが あるのよｐ
	@ ポケモンにも すききらいが あるのかしら?

SafariZone_Northwest_Text_Man: @ 82A542C
	.string "허억... 허억...\n"
	.string "드디어 여기까지 왔지만...\p"
	.string "지쳐버려서 포켓몬을 잡을\n"
	.string "기운이 없어...$"
	@ ぜぇ…… ぜぇ……ｎ
	@ やっと ここまで きたけど……ｐ
	@ つかれちゃって ポケモン つかまえるｎ
	@ げんきも のこって ないよ……

SafariZone_North_Text_Fisherman: @ 82A5489
	.string "호연에는 없는 물포켓몬을\n"
	.string "찾으러 왔는데...\p"
	.string "호수가 어디에 있는지\n"
	.string "너 알고 있니?$"
	@ ホウエンに いない みずポケモンをｎ
	@ さがしに きたんだけど……ｐ
	@ みずうみは どこにあるのかｎ
	@ きみ しってるかい?

SafariZone_North_Text_Man: @ 82A54F0
	.string "여기서 희귀한 포켓몬을\n"
	.string "잔뜩 잡아서\l"
	.string "친구와 교환할 거야!$"
	@ ここで めずらしい ポケモンをｎ
	@ たくさん つかまえてｌ
	@ ともだちと こうかん するんだ!

SafariZone_South_Text_Youngster: @ 82A553E
	.string "포켓몬스넥먹이통에 놓은 포켓몬스넥이\n"
	.string "어느새 없어져 있었다...\p"
	.string "모르는 사이에\n"
	.string "포켓몬이 먹어버린 걸까?$"
	@ ポロックおきばに おいた ポロックがｎ
	@ いつのまにか なくなっていた……ｐ
	@ しらない うちにｎ
	@ ポケモンが たべちゃったのかな?

Route121_SafariZoneEntrance_Text_TrainerTip: @ 82A55BB
	.string "사파리존 정보 나눔!\p"
	.string "마주친 포켓몬에게\n"
	.string "포켓몬스넥을 던지면 잘 안 도망갑니다!$"
	@ サファリゾ-ンの おとくな じょうほう!ｐ
	@ であった ポケモンにｎ
	@ ポロックを なげると にげにくく なります!

SafariZone_Southwest_Text_RestHouseSign: @ 82A5613
	.string "걷느라 지쳤다면 잠시 한숨 돌리자!\n"
	.string "“모두의 휴게소”$"
	@ あるき つかれたら ちょっと ひといき!ｎ
	@ 「みんなの きゅうけいじょ」

SafariZone_RestHouse_Text_Youngster: @ 82A5639
	.string "난 포켓몬스넥을 가지고 있지 않지만\n"
	.string "포켓몬을 잔뜩 잡았어\p"
	.string "가까이 다가가서 볼을 던졌을 뿐인데\n"
	.string "제법 잡을 수 있었단 말이지!$"
	@ おれ ポロック もってないけどｎ
	@ ポケモン たくさん つかまえたよｐ
	@ ちかづいて ボ-ルを なげる だけでｎ
	@ けっこう つかまえられる もんだよ!

SafariZone_RestHouse_Text_PsychicM: @ 82A56E1
	.string "포켓몬스넥을 쓰면 여느 때보다\n"
	.string "잘 도망치지 않게 되는 것 같아\p"
	.string "그러니까 잘 안 도망가는 포켓몬에게 쓰면\n"
	.string "별로 의미가 없을지도 몰라$"
	@ ポロックを つかうと いつもよりｎ
	@ ちょっぴり にげにくく なるみたいｐ
	@ だから にげにくい ポケモンに つかってもｎ
	@ あんまり いみが ないかもね

SafariZone_RestHouse_Text_FatMan: @ 82A5764
	.string "포켓몬스넥먹이통에 포켓몬스넥을 놓고\n"
	.string "포켓몬을 잡으면\p"
	.string "같은 성격의 포켓몬이\n"
	.string "잡히는 것 같은 기분이 들어$"
	@ ポロックおきばに ポロック おいてｎ
	@ ポケモンを つかまえるとｐ
	@ おなじ ような せいかくの ポケモンがｎ
	@ あつまる きが するなあ

SafariZone_South_Text_AreaOffLimits1: @ 82A57EE
	.string "이 앞은 지금 공사 중이라\n"
	.string "출입이 금지되어 있습니다$"
	@ このさきは ただいま こうじちゅう のためｎ
	@ たちいり きんしに なっています

SafariZone_Southeast_Text_ExpansionIsFinished: @ 82A582D
	.string "사파리존의 확장 공사가\n"
	.string "종료되었습니다\p"
	.string "새로운 에리어도\n"
	.string "즐겨주세요!$"
	@ サファリゾ-ンの かくちょう こうじがｎ
	@ しゅうりょう しましたｐ
	@ あたらしい エリアもｎ
	@ たのしんで くださいね!

SafariZone_South_Text_AreaOffLimits2: @ 82A5887
	.string "이 앞은 지금 공사 중이라\n"
	.string "출입이 금지되어 있습니다$"
	@ このさきは ただいま こうじちゅう のためｎ
	@ たちいり きんしに なっています

SafariZone_Southeast_Text_LittleGirl: @ 82A58C6
	.string "와아-! 와아-!\n"
	.string "처음 보는 포켓몬이 잔뜩 있어!$"
	@ わ-い わ-い!ｎ
	@ はじめて みる ポケモンが いっぱい!

SafariZone_Southeast_Text_FatMan: @ 82A58FD
	.string "이 주변에 있는 포켓몬은\n"
	.string "처음 보는 녀석들뿐이야!\p"
	.string "이런 희귀한 포켓몬을\n"
	.string "잡을 수 있다니 굉장한걸-!$"
	@ このへんに いる ポケモンはｎ
	@ はじめて みるやつ ばっかりだ!ｐ
	@ そんな めずらしい ポケモンがｎ
	@ つかまえ ほうだい だなんて すげ-!

SafariZone_Southeast_Text_RichBoy: @ 82A5960
	.string "이 주변에 있는 포켓몬은\n"
	.string "호연지방 밖에 있는 땅에서\l"
	.string "살고 있는 포켓몬이래$"
	@ このへんに いる ポケモンはｎ
	@ ホウエンちほう いがいの とちにｌ
	@ すんでる ポケモン らしいぜ

SafariZone_Northeast_Text_Boy: @ 82A59A4
	.string "사파리볼이 이제 조금밖에\n"
	.string "안 남았어\l"
	.string "뭘 잡을지 고민되네$"
	@ サファリボ-ルが あと すこししかｎ
	@ のこって ないんだよｌ
	@ なにを つかまえるか まよっちゃうなあ

SafariZone_Northeast_Text_Woman: @ 82A5A09
	.string "피카츄를 여기서 봤다고\n"
	.string "들었는데 어디 있는 걸까$"
	@ ピカチュウが ここで みられるってｎ
	@ きいたんだけど どこに いるのかしら

SafariZone_Northeast_Text_Girl: @ 82A5A44
	.string "아-앙 포켓몬이\n"
	.string "좀처럼 잡히질 않아!\p"
	.string "이대로는 입장료가\n"
	.string "아까워질 거라구!$"
	@ あ-ん ポケモンがｎ
	@ なかなか つかまらないわっ!ｐ
	@ このままじゃ にゅうじょうりょうのｎ
	@ モトが とれないわっ!
