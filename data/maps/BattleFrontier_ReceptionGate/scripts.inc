.set LOCALID_GREETER, 1
.set LOCALID_GUIDE, 2
.set LOCALID_SCOTT, 4

BattleFrontier_ReceptionGate_MapScripts:: @ 82661DA
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_ReceptionGate_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_ReceptionGate_OnTransition
	.byte 0

BattleFrontier_ReceptionGate_OnTransition: @ 82661E5
	setflag FLAG_LANDMARK_BATTLE_FRONTIER
	end

BattleFrontier_ReceptionGate_OnFrame: @ 82661E9
	map_script_2 VAR_HAS_ENTERED_BATTLE_FRONTIER, 0, BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering
	.2byte 0

BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering:: @ 82661F3
	lockall
	setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1
	playse SE_PIN
	applymovement LOCALID_GREETER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_GREETER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter
	waitmovement 0
	goto BattleFrontier_ReceptionGate_EventScript_ScottScene
	end

BattleFrontier_ReceptionGate_EventScript_ScottScene:: @ 8266229
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IssueFrontierPass, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass
	waitfanfare
	waitmessage
	msgbox BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass, MSGBOX_DEFAULT
	setflag FLAG_SYS_FRONTIER_PASS
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GREETER, Common_Movement_WalkInPlaceFastestUp
	applymovement LOCALID_GUIDE, Common_Movement_WalkInPlaceFastestUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_GREETER, Common_Movement_ExclamationMark
	applymovement LOCALID_GUIDE, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GREETER, BattleFrontier_ReceptionGate_Movement_GreeterFaceScott
	applymovement LOCALID_GUIDE, BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerFaceScott
	applymovement LOCALID_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottEnter
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_SCOTT
	releaseall
	end

BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter: @ 82662D2
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_PlayerFaceScott: @ 82662D7
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_fastest_right
	step_end

@ Unused
BattleFrontier_ReceptionGate_Movement_WalkDown: @ 82662DD
	walk_down
	walk_down
	step_end

BattleFrontier_ReceptionGate_Movement_ScottEnter: @ 82662E0
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_ScottExit: @ 82662E8
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_ReceptionGate_Movement_GreeterFaceScott: @ 82662F0
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_fastest_right
	step_end

BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott: @ 82662F6
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_fastest_left
	step_end

BattleFrontier_ReceptionGate_EventScript_Greeter:: @ 82662FC
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FacilityGuide:: @ 8266310
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFacilities, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout:: @ 8266320
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich2
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BF_RECEPTIONIST
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_BattleTower
	case 1, BattleFrontier_ReceptionGate_EventScript_BattleDome
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePalace
	case 3, BattleFrontier_ReceptionGate_EventScript_BattleArena
	case 4, BattleFrontier_ReceptionGate_EventScript_BattleFactory
	case 5, BattleFrontier_ReceptionGate_EventScript_BattlePike
	case 6, BattleFrontier_ReceptionGate_EventScript_BattlePyramid
	case 7, BattleFrontier_ReceptionGate_EventScript_RankingHall
	case 8, BattleFrontier_ReceptionGate_EventScript_ExchangeCorner
	case 9, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	end

BattleFrontier_ReceptionGate_EventScript_BattleTower:: @ 82663AE
	msgbox BattleFrontier_ReceptionGate_Text_BattleTowerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleDome:: @ 82663BC
	msgbox BattleFrontier_ReceptionGate_Text_BattleDomeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePalace:: @ 82663CA
	msgbox BattleFrontier_ReceptionGate_Text_BattlePalaceInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleArena:: @ 82663D8
	msgbox BattleFrontier_ReceptionGate_Text_BattleArenaInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleFactory:: @ 82663E6
	msgbox BattleFrontier_ReceptionGate_Text_BattleFactoryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePike:: @ 82663F4
	msgbox BattleFrontier_ReceptionGate_Text_BattlePikeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePyramid:: @ 8266402
	msgbox BattleFrontier_ReceptionGate_Text_BattlePyramidInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RankingHall:: @ 8266410
	msgbox BattleFrontier_ReceptionGate_Text_RankingHallInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExchangeCorner:: @ 826641E
	msgbox BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide:: @ 826642C
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_RulesGuide:: @ 8266436
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToRules, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout:: @ 8266446
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhat
	waitmessage
	multichoice 15, 0, MULTI_FRONTIER_RULES, 0
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_LevelMode
	case 1, BattleFrontier_ReceptionGate_EventScript_Level50
	case 2, BattleFrontier_ReceptionGate_EventScript_OpenLevel
	case 3, BattleFrontier_ReceptionGate_EventScript_MonEntry
	case 4, BattleFrontier_ReceptionGate_EventScript_HoldItems
	case 5, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	end

BattleFrontier_ReceptionGate_EventScript_LevelMode:: @ 82664A4
	msgbox BattleFrontier_ReceptionGate_Text_LevelModeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_Level50:: @ 82664B2
	msgbox BattleFrontier_ReceptionGate_Text_Level50Info, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_OpenLevel:: @ 82664C0
	msgbox BattleFrontier_ReceptionGate_Text_OpenLevelInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_MonEntry:: @ 82664CE
	msgbox BattleFrontier_ReceptionGate_Text_MonEntryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_HoldItems:: @ 82664DC
	msgbox BattleFrontier_ReceptionGate_Text_HoldItemsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide:: @ 82664EA
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FrontierPassGuide:: @ 82664F4
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout:: @ 8266504
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich1
	waitmessage
	multichoice 16, 4, MULTI_FRONTIER_PASS_INFO, 0
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_Symbols
	case 1, BattleFrontier_ReceptionGate_EventScript_RecordBattle
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePoints
	case 3, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	end

BattleFrontier_ReceptionGate_EventScript_Symbols:: @ 826654C
	msgbox BattleFrontier_ReceptionGate_Text_SymbolsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RecordBattle:: @ 826655A
	msgbox BattleFrontier_ReceptionGate_Text_RecordedBattleInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePoints:: @ 8266568
	msgbox BattleFrontier_ReceptionGate_Text_BattlePointsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide:: @ 8266576
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay: @ 8266580
	.string "첫 방문이시군요!\n"
	.string "이쪽으로 와주세요!$"
	// はじめての おきゃくさまですね!ｎ
	// こちらへ どうぞ!

BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier: @ 82665B2
	.string "포켓몬 배틀의 최전선!\n"
	.string "배틀프런티어에 어서 오세요!$"
	// ポケモンバトルの さいぜんせん!ｎ
	// バトルフロンティアへ ようこそ!

BattleFrontier_ReceptionGate_Text_IssueFrontierPass: @ 82665F7
	.string "첫 방문이신 손님께\n"
	.string "배틀프런티어 안에서\l"
	.string "이용 가능한 프런티어패스를\l"
	.string "발행해 드립니다!\p"
	.string "부디 받아주세요!$"
	// はじめての おきゃくさまにはｎ
	// バトルフロンティアの なかでｌ
	// ごりよう いただける フロンティアパスをｌ
	// はっこうして おります!ｐ
	// どうぞ おうけとり ください!

BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass: @ 8266676
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "프런티어패스를 받았다!$"
	// §あはｎ
	// フロンティアパスを もらった!

BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass: @ 8266695
	.string "{PLAYER}{K_EUNNEUN} 트레이너카드를\n"
	.string "프런티어패스에 넣었다!$"
	// §あは トレ-ナ-カ-ドをｎ
	// フロンティアパスに いれかえた!

BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier: @ 82666C6
	.string "그럼 배틀프런티어를\n"
	.string "마음껏 즐겨 주십시오!$"
	// それでは バトルフロンティアをｎ
	// ぞんぶんに おたのしみ ください!

BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame: @ 8266703
	.string "???: 여어 와줬구나\n"
	.string "{PLAYER}{K_AYA}!$"
	// ???『やあ きて くれたんだねｎ
	// §あ§お!

BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay: @ 8266733
	.string "접수원: 앗 금작화님!\n"
	.string "안녕하십니까!$"
	// うけつけ『あっ エニシダさま!ｎ
	// おつかれさまです!

BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere: @ 8266764
	.string "금작화: 네가 와주다니\n"
	.string "엄청 기쁜걸!\p"
	.string "부디 차분하고 확실하게\n"
	.string "포켓몬 승부의 진수를\l"
	.string "맛봐주면 좋겠어!\p"
	.string "내 방도 있으니까\n"
	.string "한가할 때 찾아와 줘!$"
	// エニシダ『きみが きてくれてｎ
	// とっても うれしいよ!ｐ
	// ぜひ ゆっくりと そして じっくりとｎ
	// ポケモンしょうぶの しんずいをｌ
	// あじわって いって くれ!ｐ
	// わたしの へやも あるからｎ
	// ひまが あるときに たずねて きてくれよ!

BattleFrontier_ReceptionGate_Text_YourGuideToFacilities: @ 8266857
	.string "이쪽에서는 배틀프런티어에 있는\n"
	.string "여러 시설의\l"
	.string "안내를 하고 있습니다!$"
	// こちらでは バトルフロンティアに あるｎ
	// さまざまな しせつのｌ
	// ごあんないを いたします!

BattleFrontier_ReceptionGate_Text_LearnAboutWhich2: @ 826689D
	.string "어느 설명을 듣겠습니까?$"
	// どの せつめいが ききたいですか?

BattleFrontier_ReceptionGate_Text_BattleTowerInfo: @ 82668C2
	.string "배틀프런티어의 상징이라고도\n"
	.string "할 수 있는 거대한 탑입니다\p"
	.string "이쪽의 건물에서는 싱글\n"
	.string "더블 멀티 통신멀티\l"
	.string "4개의 배틀룸에서 배틀을\l"
	.string "즐길 수 있습니다!$"
	// バトルフロンティアの シンボル ともｎ
	// いえる きょだいな とう ですｐ
	// こちらの たてもの では シングルｎ
	// ダブル マルチ つうしんマルチのｌ
	// 4つの バトルル-ムで たたかいをｌ
	// たのしむことが できます!

BattleFrontier_ReceptionGate_Text_BattleDomeInfo: @ 826696F
	.string "배틀돔은 알 모양을\n"
	.string "한 커다란 건물입니다\p"
	.string "이쪽에서는 배틀토너먼트라고 하는\n"
	.string "이벤트가 개최되고 있습니다\p"
	.string "또한 배틀토너먼트에는\n"
	.string "싱글배틀용 더블배틀용\l"
	.string "2개의 코스가 있습니다!$"
	// バトルド-ムは たまごの ようなｎ
	// かたちをした おおきな たてものですｐ
	// こちらでは バトルト-ナメント というｎ
	// イベントが かいさいされて いますｐ
	// なお バトルト-ナメントにはｎ
	// シングルバトルよう ダブルバトルようのｌ
	// 2つの コ-スが あります!

BattleFrontier_ReceptionGate_Text_BattlePalaceInfo: @ 8266A34
	.string "배틀팰리스는 배틀프런티어의\n"
	.string "우측 하단에 있는 붉은 건물입니다\p"
	.string "이쪽의 건물에서는\n"
	.string "싱글 더블 2개의\l"
	.string "배틀홀 도전이 가능합니다$"
	// バトルパレスは バトルフロンティアのｎ
	// みぎはじに ある あかい たてものですｐ
	// こちらの たてもの ではｎ
	// シングル ダブルの 2つのｌ
	// バトルホ-ルへの ちょうせんが できます

BattleFrontier_ReceptionGate_Text_BattleArenaInfo: @ 8266AC2
	.string "배틀아레나는 배틀프런티어의\n"
	.string "중앙에서 오른쪽에 위치한\l"
	.string "도장과 닮은 건물입니다\p"
	.string "이쪽에서는 연승팀배틀이라고 하는\n"
	.string "이벤트가 개최되고 있습니다!$"
	// バトルアリ-ナは バトルフロンティアのｎ
	// ちゅうおう みぎに いちするｌ
	// どうじょうの ような たてものですｐ
	// こちらでは かちぬきチ-ムバトル というｎ
	// イベントを かいさい しております!

BattleFrontier_ReceptionGate_Text_BattleFactoryInfo: @ 8266B5D
	.string "배틀팩토리는 이곳을 나가서 가장\n"
	.string "가까이에 있는 커다란 빌딩입니다\p"
	.string "이쪽에서는 배틀트레이드라고 하는\n"
	.string "이벤트가 개최되고 있습니다\p"
	.string "또한 배틀트레이드에는\n"
	.string "싱글배틀용 더블배틀용\l"
	.string "2개의 코스가 준비되어 있습니다!$"
	// バトルファクトリ-は ここをでて いちばんｎ
	// ちかくにある おおきな ビルに なりますｐ
	// こちらでは バトルトレ-ド というｎ
	// イベントを かいさいして おりますｐ
	// なお バトルトレ-ドにはｎ
	// シングルバトルよう ダブルバトルようのｌ
	// 2つの コ-スが ようい されています!

BattleFrontier_ReceptionGate_Text_BattlePikeInfo: @ 8266C24
	.string "배틀튜브는 배틀프런티어의\n"
	.string "중앙에서 왼쪽에 위치한\l"
	.string "포켓몬 모양의 건물입니다\p"
	.string "이쪽에서는 배틀게임이라고 하는\n"
	.string "이벤트가 개최되고 있습니다!$"
	// バトルチュ-ブは バトルフロンティアのｎ
	// ちゅうおう ひだりに いちするｌ
	// ポケモンの かたちを した たてものですｐ
	// こちらでは バトルゲ-ム というｎ
	// イベントを かいさい しております!

BattleFrontier_ReceptionGate_Text_BattlePyramidInfo: @ 8266CBB
	.string "배틀피라미드는 거대한\n"
	.string "피라미드 모양의 건물입니다\p"
	.string "이쪽에서는 배틀어드벤처라고 하는\n"
	.string "이벤트가 개최되고 있습니다!$"
	// バトルピラミッドは きょだいなｎ
	// ピラミッドの かたちをした たてものですｐ
	// こちらでは バトルアドベンチャ- というｎ
	// イベントを かいさい しております!

BattleFrontier_ReceptionGate_Text_RankingHallInfo: @ 8266D1C
	.string "랭킹홀은\n"
	.string "배틀타워 근처에 있습니다\p"
	.string "이쪽은 배틀프런티어에서\n"
	.string "배틀한 트레이너의\l"
	.string "가장 뛰어난 기록을\l"
	.string "볼 수 있습니다$"
	// ランキングホ-ルはｎ
	// バトルタワ-の ちかくに ありますｐ
	// こちらは バトルフロンティアでｎ
	// たたかった トレ-ナ-たちのｌ
	// もっとも すばらしい きろくをｌ
	// みることが できます

BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo: @ 8266DCB
	.string "교환 서비스 코너는\n"
	.string "배틀타워 근처에 있습니다\p"
	.string "이쪽에서는 배틀프런티어\n"
	.string "안에서 모은 배틀포인트를\l"
	.string "멋진 경품과\l"
	.string "교환할 수 있습니다!$"
	// ひきかえサ-ビス コ-ナ-はｎ
	// バトルタワ-の ちかくに ありますｐ
	// こちらでは バトルフロンティアのｎ
	// なかで ためた バトルポイントをｌ
	// すてきな けいひんとｌ
	// こうかんする ことが できます!

BattleFrontier_ReceptionGate_Text_YourGuideToRules: @ 8266E66
	.string "이쪽에서는 배틀프런티어에 있는\n"
	.string "모든 시설에서 공통된\l"
	.string "도전을 위해 기본적인\l"
	.string "규칙을 설명합니다!$"
	// こちらでは バトルフロンティアに あるｎ
	// すべての しせつに きょうつう したｌ
	// ちょうせんの ための きほんてきなｌ
	// ル-ルを せつめい いたします!

BattleFrontier_ReceptionGate_Text_LearnAboutWhat: @ 8266EE0
	.string "어느 설명을 듣겠습니까?$"
	// どの せつめいが ききたいですか?

BattleFrontier_ReceptionGate_Text_LevelModeInfo: @ 8266F04
	.string "배틀프런티어에 있는\n"
	.string "모든 시설의 도전은\l"
	.string "크게 레벨 50의 코스와\l"
	.string "오픈 레벨의 코스로 나눠집니다$"
	// バトルフロンティアに あるｎ
	// すべての しせつの ちょうせんはｌ
	// おおきく レベル50の コ-スとｌ
	// オ-プンレベルの コ-スに わかれています

BattleFrontier_ReceptionGate_Text_Level50Info: @ 8266F69
	.string "레벨 50의 코스에는 이름대로\n"
	.string "레벨 50까지의 포켓몬으로\l"
	.string "도전할 수 있습니다\p"
	.string "다만 레벨 50보다 높은 레벨의\n"
	.string "포켓몬을 지닌 트레이너가\l"
	.string "등장하는 일은 없습니다\l"
	.string "아무쪼록 주의해 주십시오\p"
	.string "또한 이 코스가 배틀프런티어의\n"
	.string "배틀의 기본이 되므로\l"
	.string "꼭 도전해 보는 것을 추천합니다$"
	// レベル50の コ-スでは なまえの とおりｎ
	// レベル50までの ポケモンをｌ
	// ちょうせん させることが できますｐ
	// ただし レベル50より ひくい レベルのｎ
	// ポケモンを つれた トレ-ナ-がｌ
	// とうじょう することは ありませんｌ
	// くれぐれも ごちゅうい くださいｐ
	// なお このコ-スが バトルフロンティアのｎ
	// たたかいの きほんと なって いますのでｌ
	// ぜひ チャレンジして みてください

BattleFrontier_ReceptionGate_Text_OpenLevelInfo: @ 8267080
	.string "오픈 레벨의 코스에는\n"
	.string "도전에 참가하는 포켓몬의\l"
	.string "레벨 제한이 없습니다\p"
	.string "당신의 포켓몬의 레벨에 맞춰\n"
	.string "대전하는 트레이너의 포켓몬의\l"
	.string "레벨이 바뀝니다\p"
	.string "다만 레벨 60보다 낮은 레벨의\n"
	.string "포켓몬을 데리고 있는 트레이너는\l"
	.string "등장하지 않습니다$"
	// オ-プンレベルの コ-スではｎ
	// ちょうせんに さんかする ポケモンのｌ
	// レベルに せいげんが ありませんｐ
	// あなたの ポケモンの レベルに あわせてｎ
	// たいせんする トレ-ナ-の ポケモンのｌ
	// レベルが かわりますｐ
	// ただし レベル60より ひくい レベルのｎ
	// ポケモンを つれた トレ-ナ-がｌ
	// とうじょう することは ありません

BattleFrontier_ReceptionGate_Text_MonEntryInfo: @ 826716A
	.string "알이나 일부 예외를\n"
	.string "제외한 대부분의 포켓몬이\l"
	.string "모든 시설에 도전 가능합니다\p"
	.string "도전을 위해\n"
	.string "필요한 포켓몬의 수는\l"
	.string "시설에 따라 다릅니다\p"
	.string "다만 어느 시설에서도\n"
	.string "같은 종류의 포켓몬을\l"
	.string "2마리 이상 참가시킬 수는\l"
	.string "없기에 주의해 주십시오$"
	// タマゴや いちぶの れいがいをｎ
	// のぞいて ほとんどの ポケモンがｌ
	// すべての しせつに ちょうせん できますｐ
	// ちょうせんの ためにｎ
	// ひつような ポケモンの かずはｌ
	// しせつに よって ちがいますｐ
	// ただし どの しせつでもｎ
	// おなじ しゅるいの ポケモンをｌ
	// 2ひき いじょう さんか させることはｌ
	// できませんので ごちゅうい ください

BattleFrontier_ReceptionGate_Text_HoldItemsInfo: @ 8267298
	.string "배틀프런티어의 시설에\n"
	.string "포켓몬을 참가시킬 때\p"
	.string "각각의 포켓몬은\n"
	.string "같은 아이템을 지닐 수 없습니다\p"
	.string "참가시킬 포켓몬이\n"
	.string "모두 다른 도구를\l"
	.string "지니도록 해주십시오$"
	// バトルフロンティアの しせつにｎ
	// ポケモンを ちょうせん させるときｐ
	// それぞれの ポケモンがｎ
	// おなじ どうぐを もつことは できませんｐ
	// ちょうせん させる ポケモンにはｎ
	// すべて ちがう どうぐをｌ
	// もたせて おくように してください

BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass: @ 8267357
	.string "이쪽에서는 프런티어패스의\n"
	.string "설명을 하고 있습니다!$"
	// こちらでは フロンティアパスのｎ
	// せつめいを いたします!

BattleFrontier_ReceptionGate_Text_LearnAboutWhich1: @ 826737C
	.string "어느 설명을 듣겠습니까?$"
	// どの せつめいが ききたいですか?

BattleFrontier_ReceptionGate_Text_SymbolsInfo: @ 82673A1
	.string "배틀프런티어의 7개의 시설에서\n"
	.string "강함을 인정받은 트레이너가\l"
	.string "각각의 시설의 심볼을\l"
	.string "받는 경우가 있습니다\p"
	.string "심볼을 받기 위해서는\n"
	.string "계속 트레이너를 이겨나가거나\l"
	.string "계속 제패하거나...\p"
	.string "꽤나 힘든 조건이지만\n"
	.string "부디 힘내주세요!$"
	// バトルフロンティアの 7つの しせつでｎ
	// つよさを みとめられた トレ-ナ-がｌ
	// それぞれの しせつの シンボルをｌ
	// もらえることが ありますｐ
	// シンボルを もらう ためにはｎ
	// なんにんも トレ-ナ-を かちぬいたりｌ
	// なんども せいは したり……ｐ
	// なかなか たいへんな みちのりですがｎ
	// ぜひ がんばって くださいね!

BattleFrontier_ReceptionGate_Text_RecordedBattleInfo: @ 82674F3
	.string "당신의 대전을 하나만\n"
	.string "패스에 기록할 수 있습니다\p"
	.string "친구와의 대전이나\n"
	.string "배틀튜브 배틀팰리스 이외의\l"
	.string "배틀프런티어에서의\l"
	.string "대전을 기록할 수 있습니다\p"
	.string "대전이 끝났을 때\n"
	.string "기록 여부를 결정합니다$"
	// あなたの たいせんを ひとつだけｎ
	// パスに きろくする ことが できますｐ
	// おともだち との たいせんかｎ
	// バトルチュ-ブ バトルピラミッド いがいのｌ
	// バトルフロンティアでのｌ
	// たいせんが きろくできますｐ
	// たいせんが おわった ときにｎ
	// きろく するか どうかを きめられます

BattleFrontier_ReceptionGate_Text_BattlePointsInfo: @ 826761C
	.string "배틀포인트는\n"
	.string "배틀프런티어에서 굉장한\l"
	.string "배틀을 한 트레이너에게\l"
	.string "주어지는 보상입니다\p"
	.string "모은 포인트는 교환 서비스로\n"
	.string "상품과 교환할 수 있습니다$"
	// バトルポイントはｎ
	// バトルフロンティアで すばらしいｌ
	// たたかいを した トレ-ナ-にｌ
	// あたえられる ごほうびですｐ
	// ためた ポイントは ひきかえサ-ビスでｎ
	// しょうひんと ひきかえることが できます

