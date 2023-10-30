MtPyre_2F_MapScripts:: @ 82310FB
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, MtPyre_2F_SetHoleWarp
	.byte 0

MtPyre_2F_SetHoleWarp: @ 823110B
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_MT_PYRE_1F, 255, 0, 0
	end

MtPyre_2F_EventScript_Woman:: @ 8231116
	msgbox MtPyre_2F_Text_MemoriesOfSkitty, MSGBOX_NPC
	end

MtPyre_2F_EventScript_PokefanM:: @ 823111F
	msgbox MtPyre_2F_Text_TumbledFromFloorAbove, MSGBOX_NPC
	end

MtPyre_2F_EventScript_Mark:: @ 8231128
	trainerbattle_single TRAINER_MARK, MtPyre_2F_Text_MarkIntro, MtPyre_2F_Text_MarkDefeat
	msgbox MtPyre_2F_Text_MarkPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Luke:: @ 823113F
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_LukeIntro, MtPyre_2F_Text_LukeDefeat, MtPyre_2F_Text_LukeNotEnoughMons
	msgbox MtPyre_2F_Text_LukePostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Dez:: @ 823115A
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_DezIntro, MtPyre_2F_Text_DezDefeat, MtPyre_2F_Text_DezNotEnoughMons
	msgbox MtPyre_2F_Text_DezPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Leah:: @ 8231175
	trainerbattle_single TRAINER_LEAH, MtPyre_2F_Text_LeahIntro, MtPyre_2F_Text_LeahDefeat
	msgbox MtPyre_2F_Text_LeahPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Zander:: @ 823118C
	trainerbattle_single TRAINER_ZANDER, MtPyre_2F_Text_ZanderIntro, MtPyre_2F_Text_ZanderDefeat
	msgbox MtPyre_2F_Text_ZanderPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_Text_MemoriesOfSkitty: @ 82311A3
	.string "귀여웠던 에나비와의 추억...\n"
	.string "떠올리기만 해도 눈물이 흘러...$"
	// かわいかった エネコとの おもいで……ｎ
	// おもいだすだけで なみだが あふれる……

MtPyre_2F_Text_TumbledFromFloorAbove: @ 82311E6
	.string "아야야야야... 바닥의 여기저기에\n"
	.string "구멍이 뚫려 있는데 못 봐서\l"
	.string "아저씨 위에서 여기로 떨어져버렸어$"
	// アイタタタ…… ゆかの そこかしこにｎ
	// あなが あいているのに きづかないでｌ
	// おじさん うえから おちてしまったよ

MtPyre_2F_Text_MarkIntro: @ 8231258
	.string "너도 포켓몬을 찾으러 온 건가?\n"
	.string "나중에 온 주제에 건방지군!$"
	// おまえも ポケモン さがしに きたのか?ｎ
	// あとから きた くせに なまいきだ!

MtPyre_2F_Text_MarkDefeat: @ 82312A2
	.string "흐에에에에에엑!\n"
	.string "용서해 주십쇼-!$"
	// ふええええええっ!ｎ
	// ゆるして ください-っ!

MtPyre_2F_Text_MarkPostBattle: @ 82312CB
	.string "거의 사람이 드나들지 않는 산이니\n"
	.string "희귀한 포켓몬이 있을 것 같았어$"
	// めったに ひとが はいらない やま だからｎ
	// めずらしい ポケモンが いると おもってさ

MtPyre_2F_Text_LukeIntro: @ 823130F
	.string "테르: 담력 훈련을 하고 있어!\n"
	.string "멋진 내 모습을 보면\l"
	.string "여자친구가 나한테 더 반하겠지!?\p"
	.string "그래! 널 쓰러뜨리고\n"
	.string "멋진 모습을 보여주겠어!$"
	// テル『きもだめし するんだ!ｎ
	// ぼくの かっこいい ところ みればｌ
	// かのじょ もっと ほれるからね!ｐ
	// そうだ! きみを たおしてｎ
	// かっこいい ところ みせちゃおう!

MtPyre_2F_Text_LukeDefeat: @ 82313A1
	.string "테르: 이런-$"
	// テル『あっちゃ-

MtPyre_2F_Text_LukePostBattle: @ 82313B1
	.string "테르: 져버렸지만 괜찮아!\n"
	.string "내가 있으니까\l"
	.string "담력 훈련 같은 건 별거 아니라고!$"
	// テル『まけちゃったけど だいじょうぶ!ｎ
	// ぼくが いるからさｌ
	// きもだめし なんて へっちゃら だよ!

MtPyre_2F_Text_LukeNotEnoughMons: @ 8231414
	.string "테르: 나랑 승부하려면\n"
	.string "좀 더 포켓몬을 데려오라고!\p"
	.string "그래야 내가 여자친구 앞에서\n"
	.string "멋진 모습을 보일 수 있으니까!$"
	// テル『ぼくと しょうぶ するならｎ
	// もっと ポケモン つれてきなよ!ｐ
	// そうでないと かのじょの まえでｎ
	// いいところ みせられない じゃないか!

MtPyre_2F_Text_DezIntro: @ 8231492
	.string "마코: 남자친구랑 담력 훈련을 하러 왔어\n"
	.string "엄청 무섭지만\l"
	.string "남자친구가 있으니까 괜찮아!\p"
	.string "그래! 널 쓰러뜨리는\n"
	.string "남자친구의 멋진 모습을 보여줄게!$"
	// マコ『かれしと きもだめしに きたのｎ
	// すっごく こわいけどｌ
	// かれしが いるから だいじょうぶ!ｐ
	// そうだ! あなたを たおすｎ
	// かれしの かっこいい ところ みせて!

MtPyre_2F_Text_DezDefeat: @ 8231534
	.string "마코: 아-앙 무서워-!$"
	// マコ『あ-ん こわ-い!

MtPyre_2F_Text_DezPostBattle: @ 823154D
	.string "마코: 우리들은 러브러브니까\n"
	.string "져도 괜찮아!$"
	// マコ『あたしたち ラブラブだからｎ
	// まけても へいき なんだもん!

MtPyre_2F_Text_DezNotEnoughMons: @ 8231582
	.string "마코: 우리랑 승부하고 싶으면\n"
	.string "적어도 두 마리는 포켓몬이 있어야 해\p"
	.string "내 남자친구는 엄청 강하니까\n"
	.string "한 마리 가지고는 어림없어$"
	// マコ『あたしたちと たたかいたいならｎ
	// せめて 2ひきは ポケモン いないとｐ
	// あたしの かれし つよいんだからｎ
	// いっぴきじゃ はなしに ならないわ

MtPyre_2F_Text_LeahIntro: @ 8231604
	.string "본 적 없는 얼굴...\n"
	.string "무슨 일이 생기기 전에 돌아가!$"
	// みかけぬ かおね……ｎ
	// なにも おきない うちに かえりなさい!

MtPyre_2F_Text_LeahDefeat: @ 8231645
	.string "음... 강하네$"
	// むん…… てごわいのね

MtPyre_2F_Text_LeahPostBattle: @ 823165A
	.string "증조할머니 때부터\n"
	.string "여기서 트레이너를 하고 있어\l"
	.string "이 산을 지키고 있지...$"
	// ひい おばあさまの だい からｎ
	// ここで トレ-ナ-を やっているの……ｌ
	// この やまを まもっていくわ……

MtPyre_2F_Text_ZanderIntro: @ 82316C7
	.string "끼 꺄아아아악!\n"
	.string "나왔다아아아!$"
	// ぎっ ぎゃああああっ!ｎ
	// でたあああっ!

MtPyre_2F_Text_ZanderDefeat: @ 82316E1
	.string "져 져버렸다아아아아!$"
	// ま まけたああああっ!

MtPyre_2F_Text_ZanderPostBattle: @ 82316FB
	.string "뭐 뭔가가 움직일 때마다\n"
	.string "깜짝 놀라\l"
	.string "여기서 수행하는 게 아니었는데$"
	// な なにかが うごく たびにｎ
	// ビクっと するよｌ
	// ここで しゅぎょう するんじゃ なかったよ

