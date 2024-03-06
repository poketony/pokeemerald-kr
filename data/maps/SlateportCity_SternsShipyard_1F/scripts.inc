.set LOCALID_DOCK, 1

SlateportCity_SternsShipyard_1F_MapScripts:: @ 8207F3F
	.byte 0

SlateportCity_SternsShipyard_1F_EventScript_Dock:: @ 8207F40
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_SternsShipyard_1F_EventScript_FerryReady
	goto_if_set FLAG_BADGE07_GET, SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_GoFindStern
	msgbox SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails, MSGBOX_DEFAULT
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_DOCK_REJECTED_DEVON_GOODS
	setflag FLAG_HIDE_SLATEPORT_CITY_TEAM_AQUA
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_FerryReady:: @ 8207F92
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_FerryIsReady, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined:: @ 8207FA6
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_GoFindStern:: @ 8207FBA
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran:: @ 8207FD9
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist1:: @ 8207FED
	msgbox SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist2:: @ 8207FF6
	msgbox SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Briney:: @ 8207FFF
	msgbox SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails: @ 8208008
	.string "으-음... 이게 이렇게 되고\n"
	.string "그래서 저게 저렇게 되는데\l"
	.string "아니 그럼 저거랑 이건 뭔데?\p"
	.string "아 진짜 뭐가 뭔지 모르겠네!$"
	@ え-と…… これが こ-なってｎ
	@ そいでもって あれが あ-なってｌ
	@ と いうことは それと これは どれ?ｐ
	@ ああ もう わけが わからん!

SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern: @ 82080A5
	.string "...응?\p"
	.string "난 해양관장의 지시로\n"
	.string "연락선의 설계를 맡게 된\l"
	.string "솔방울이라고 하는데...\p"
	.string "앗!?\n"
	.string "그건 데봉화물!\p"
	.string "음...\n"
	.string "곤란한데 이거...\p"
	.string "해양관장\n"
	.string "다른 할 일이 있다면서\l"
	.string "어딘가로 가 버렸어\p"
	.string "미안한데 네가 해양관장을\n"
	.string "찾아서 그 화물 좀 전달해주라!$"
	@ ……ん?ｐ
	@ ぼくは クスノキかんちょう からｎ
	@ れんらくせんの せっけいを まかされたｌ
	@ ツガという ものだけど……ｐ
	@ あっ!?ｎ
	@ それは デボンのにもつ!ｐ
	@ う-ん……ｎ
	@ こまったな……ｐ
	@ クスノキかんちょうｎ
	@ ほかにも しごとが あるからってｌ
	@ どこかに いっちゃったんだｐ
	@ わるいけど きみ クスノキかんちょうｎ
	@ さがして にもつを わたしてあげてよ!

SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern: @ 82081A5
	.string "솔방울: 해양관장은\n"
	.string "어디로 간 거지?\p"
	.string "미안한데 네가 해양관장을\n"
	.string "찾아서 그 화물 좀 전달해주라!$"
	@ ツガ『クスノキかんちょうｎ
	@ どこに いっちゃったのかな?ｐ
	@ わるいけど きみ クスノキかんちょうｎ
	@ さがして にもつを わたしてあげてよ!

SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran: @ 8208213
	.string "솔방울: 배를 만드는 건\n"
	.string "책상 위에서 하는 계산만으로는\l"
	.string "알 수 없는 것도 많아서 말이지\p"
	.string "역시 바다에 대해 자세히 알고 있는\n"
	.string "베테랑의 지혜가 필요해...$"
	@ ツガ『ふねをつくる っていうのはｎ
	@ つくえの うえでの けいさん だけではｌ
	@ わからないことも おおくてねｐ
	@ やっぱり うみのことを しりつくしたｎ
	@ ベテランの ちえが ほしいところだよ……

SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs: @ 82082A8
	.string "솔방울: 안녕! 하기노인이 여기서\n"
	.string "도와주게 됐어!\p"
	.string "전설의 선원이 도와줘서\n"
	.string "연락선은 순조롭게\l"
	.string "완성되어 가고 있다고!$"
	@ ツガ『やあ! ハギろうじんが ここでｎ
	@ てつだって くれるように なったよ!ｐ
	@ でんせつの ふなのりに てつだってもらえてｎ
	@ れんらくせんは ちゃくちゃくとｌ
	@ かんせいに むかっているよ!

SlateportCity_SternsShipyard_1F_Text_FerryIsReady: @ 8208323
	.string "솔방울: 드디어 배가 완성됐어!\p"
	.string "완성된 연락선 타이드립호는\n"
	.string "그야말로 최고의 걸작이야!\p"
	.string "근데 더 잘 만들 수 있을 듯한...\n"
	.string "생각도 들어\p"
	.string "그래...\n"
	.string "뭔가를 만드는 데 끝은 없으니까!$"
	@ ツガ『ついに ふねは かんせいしたよ!ｐ
	@ できた れんらくせん タイドリップごうはｎ
	@ まさに さいこう けっさく!ｐ
	@ だけど もっと いいものが できそうな……ｎ
	@ そんな きも するんだよｐ
	@ そう……ｎ
	@ ものづくりに おわりは ないのさ!

SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock: @ 82083EE
	.string "하기: 오오! {PLAYER}!\n"
	.string "오랜만이구나!\p"
	.string "아니 자네랑 만난 뒤로\n"
	.string "선원의 피가 끓어올라서 말이지...\p"
	.string "솔방울이랑 협력해서\n"
	.string "연락선을 만들고 싶어졌지 뭔가!\p"
	.string "연락선이 완성되면 많은\n"
	.string "사람들을 옮길 수 있게 되니 말이지\p"
	.string "그나저나... 흐음...\n"
	.string "솔방울은 정말 대단하더군...\p"
	.string "그의 기술과 내 경험을\n"
	.string "하나로 합친다면 분명\l"
	.string "엄청난 배가 만들어질 걸세!$"
	@ ハギ『おお! §あ§お!ｎ
	@ ひさしぶり じゃのう!ｐ
	@ いやあ きみと であってからｎ
	@ ふなのりの ちが さわいでな……ｐ
	@ ツガくんに きょうりょく してｎ
	@ れんらくせんを つくりたく なったんじゃ!ｐ
	@ れんらくせんが できると おおくのｎ
	@ ひとを はこべるように なるからのうｐ
	@ しかし…… ふむう……ｎ
	@ ツガくんは すごいのう……ｐ
	@ かれの ぎじゅつと わしの けいけんをｎ
	@ がったい させれば かならずやｌ
	@ すごい ふねが できるに ちがいない!

SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing: @ 8208558
	.string "계절이나 날씨, 달의 위치 등\n"
	.string "여러 가지 조건에 따라\l"
	.string "바다는 항상 모습이 바뀐답니다\p"
	.string "그렇죠! 바다는 바로\n"
	.string "살아 있는 생물 같은 거예요!$"
	@ きせつや てんきや つきのいち などｎ
	@ さまざまな じょうけん によってｌ
	@ うみは つねに すがたを かえていきますｐ
	@ そう! うみ というのはｎ
	@ いきもの のような もの なんですよ!

SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily: @ 82085FF
	.string "난 곧잘 뱃멀미를 한단 말이지\n"
	.string "그래서 여기서 일하고 있는 거야$"
	@ ぼくは すぐに ふなよい するのよねｎ
	@ だから ここで おてつだい してるのよね

