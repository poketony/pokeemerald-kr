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
	.string "{PLAYER}!$"
	// ???『やあ きて くれたんだねｎ
	// §あ§お!

BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay: @ 8266733
	.string "접수원: 앗 금작화님!\n"
	.string "안녕하십니까!$"
	// うけつけ『あっ エニシダさま!ｎ
	// おつかれさまです!

BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere: @ 8266764
	.string "금작화: It's great to see you here,\n"
	.string "it really is!\p"
	.string "I hope you'll take your time and\n"
	.string "explore everywhere.\p"
	.string "Naturally, I hope you'll also experience\n"
	.string "the pure essence of battling.\p"
	.string "I also have my quarters here, so feel\n"
	.string "free to visit if you have time.$"
	// エニシダ『きみが きてくれてｎ
	// とっても うれしいよ!ｐ
	// ぜひ ゆっくりと そして じっくりとｎ
	// ポケモンしょうぶの しんずいをｌ
	// あじわって いって くれ!ｐ
	// わたしの へやも あるからｎ
	// ひまが あるときに たずねて きてくれよ!

BattleFrontier_ReceptionGate_Text_YourGuideToFacilities: @ 8266857
	.string "I'm your guide to the various facilities\n"
	.string "here in the BATTLE FRONTIER.$"
	// こちらでは バトルフロンティアに あるｎ
	// さまざまな しせつのｌ
	// ごあんないを いたします!

BattleFrontier_ReceptionGate_Text_LearnAboutWhich2: @ 826689D
	.string "Which would you like to learn about?$"
	// どの せつめいが ききたいですか?

BattleFrontier_ReceptionGate_Text_BattleTowerInfo: @ 82668C2
	.string "It is the gigantic tower considered\n"
	.string "to be the BATTLE FRONTIER's symbol.\p"
	.string "There are four kinds of BATTLE ROOMS\n"
	.string "in the tower for SINGLE, DOUBLE, MULTI,\l"
	.string "and LINK MULTI BATTLES.$"
	// バトルフロンティアの シンボル ともｎ
	// いえる きょだいな とう ですｐ
	// こちらの たてもの では シングルｎ
	// ダブル マルチ つうしんマルチのｌ
	// 4つの バトルル-ムで たたかいをｌ
	// たのしむことが できます!

BattleFrontier_ReceptionGate_Text_BattleDomeInfo: @ 826696F
	.string "The BATTLE DOME is the large building\n"
	.string "shaped like a huge egg.\p"
	.string "Events named Battle Tourneys are held\n"
	.string "in this facility.\p"
	.string "The Battle Tourneys are offered in\n"
	.string "two courses--for SINGLE and DOUBLE\l"
	.string "BATTLES.$"
	// バトルド-ムは たまごの ようなｎ
	// かたちをした おおきな たてものですｐ
	// こちらでは バトルト-ナメント というｎ
	// イベントが かいさいされて いますｐ
	// なお バトルト-ナメントにはｎ
	// シングルバトルよう ダブルバトルようのｌ
	// 2つの コ-スが あります!

BattleFrontier_ReceptionGate_Text_BattlePalaceInfo: @ 8266A34
	.string "The BATTLE PALACE is the red building\n"
	.string "on the right of the BATTLE FRONTIER.\p"
	.string "There are two kinds of BATTLE HALLS\n"
	.string "for SINGLE and DOUBLE BATTLES.$"
	// バトルパレスは バトルフロンティアのｎ
	// みぎはじに ある あかい たてものですｐ
	// こちらの たてもの ではｎ
	// シングル ダブルの 2つのｌ
	// バトルホ-ルへの ちょうせんが できます

BattleFrontier_ReceptionGate_Text_BattleArenaInfo: @ 8266AC2
	.string "The BATTLE ARENA is the dojo-like\n"
	.string "building at the center-right of\l"
	.string "the BATTLE FRONTIER.\p"
	.string "An event called the Set KO Tourney\n"
	.string "takes place at the BATTLE ARENA.$"
	// バトルアリ-ナは バトルフロンティアのｎ
	// ちゅうおう みぎに いちするｌ
	// どうじょうの ような たてものですｐ
	// こちらでは かちぬきチ-ムバトル というｎ
	// イベントを かいさい しております!

BattleFrontier_ReceptionGate_Text_BattleFactoryInfo: @ 8266B5D
	.string "The BATTLE FACTORY is the large\n"
	.string "building that is the closest to us.\p"
	.string "An event called the Battle Swap\n"
	.string "is conducted there.\p"
	.string "The Battle Swap event is offered in\n"
	.string "two courses for SINGLE and DOUBLE\l"
	.string "BATTLES.$"
	// バトルファクトリ-は ここをでて いちばんｎ
	// ちかくにある おおきな ビルに なりますｐ
	// こちらでは バトルトレ-ド というｎ
	// イベントを かいさいして おりますｐ
	// なお バトルトレ-ドにはｎ
	// シングルバトルよう ダブルバトルようのｌ
	// 2つの コ-スが ようい されています!

BattleFrontier_ReceptionGate_Text_BattlePikeInfo: @ 8266C24
	.string "The BATTLE PIKE is the building shaped\n"
	.string "like a POKéMON at the center-left of\l"
	.string "the BATTLE FRONTIER.\p"
	.string "An event called the Battle Choice\n"
	.string "is conducted there.$"
	// バトルチュ-ブは バトルフロンティアのｎ
	// ちゅうおう ひだりに いちするｌ
	// ポケモンの かたちを した たてものですｐ
	// こちらでは バトルゲ-ム というｎ
	// イベントを かいさい しております!

BattleFrontier_ReceptionGate_Text_BattlePyramidInfo: @ 8266CBB
	.string "The BATTLE PYRAMID is the enormous\n"
	.string "pyramid.\p"
	.string "An event called the Battle Quest\n"
	.string "is conducted there.$"
	// バトルピラミッドは きょだいなｎ
	// ピラミッドの かたちをした たてものですｐ
	// こちらでは バトルアドベンチャ- というｎ
	// イベントを かいさい しております!

BattleFrontier_ReceptionGate_Text_RankingHallInfo: @ 8266D1C
	.string "The RANKING HALL is located near\n"
	.string "the BATTLE TOWER.\p"
	.string "There, you may see the most fantastic\n"
	.string "records left by the TRAINERS that\l"
	.string "took on the many challenges of\l"
	.string "the BATTLE FRONTIER.$"
	// ランキングホ-ルはｎ
	// バトルタワ-の ちかくに ありますｐ
	// こちらは バトルフロンティアでｎ
	// たたかった トレ-ナ-たちのｌ
	// もっとも すばらしい きろくをｌ
	// みることが できます

BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo: @ 8266DCB
	.string "The EXCHANGE SERVICE CORNER is near\n"
	.string "the BATTLE TOWER.\p"
	.string "The Battle Points you have earned in\n"
	.string "the BATTLE FRONTIER may be exchanged\l"
	.string "for fabulous prizes there.$"
	// ひきかえサ-ビス コ-ナ-はｎ
	// バトルタワ-の ちかくに ありますｐ
	// こちらでは バトルフロンティアのｎ
	// なかで ためた バトルポイントをｌ
	// すてきな けいひんとｌ
	// こうかんする ことが できます!

BattleFrontier_ReceptionGate_Text_YourGuideToRules: @ 8266E66
	.string "I'm your guide to the basic rules that\n"
	.string "are common to all the challenges\l"
	.string "offered by the facilities in the BATTLE\l"
	.string "FRONTIER.$"
	// こちらでは バトルフロンティアに あるｎ
	// すべての しせつに きょうつう したｌ
	// ちょうせんの ための きほんてきなｌ
	// ル-ルを せつめい いたします!

BattleFrontier_ReceptionGate_Text_LearnAboutWhat: @ 8266EE0
	.string "What would you like to learn about?$"
	// どの せつめいが ききたいですか?

BattleFrontier_ReceptionGate_Text_LevelModeInfo: @ 8266F04
	.string "All the challenges at the BATTLE\n"
	.string "FRONTIER's facilities come in\l"
	.string "two courses--Level 50 and Open Level.$"
	// バトルフロンティアに あるｎ
	// すべての しせつの ちょうせんはｌ
	// おおきく レベル50の コ-スとｌ
	// オ-プンレベルの コ-スに わかれています

BattleFrontier_ReceptionGate_Text_Level50Info: @ 8266F69
	.string "The Level 50 course is open to POKéMON\n"
	.string "up to and including Level 50.\p"
	.string "Please keep in mind, however, that\n"
	.string "no TRAINER you face will have any\l"
	.string "POKéMON below Level 50.\p"
	.string "This course is the entry level for\n"
	.string "battles at the BATTLE FRONTIER.\p"
	.string "To begin, we hope you will challenge\n"
	.string "this course.$"
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
	.string "The Open Level course places no limit\n"
	.string "on the levels of POKéMON entering\l"
	.string "challenges.\p"
	.string "The levels of your opponents will\n"
	.string "be adjusted to match the levels of\l"
	.string "your POKéMON.\p"
	.string "However, no TRAINER you face will\n"
	.string "have any POKéMON below Level 60.$"
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
	.string "Virtually any kind of POKéMON may take\n"
	.string "on the challenges at all facilities.\p"
	.string "EGGS and certain kinds of POKéMON,\n"
	.string "however, are not permitted.\p"
	.string "The numbers of POKéMON required for\n"
	.string "challenges will depend on the facility.\p"
	.string "At all facilities, however, two or more\n"
	.string "of the same kind of POKéMON are not\l"
	.string "permitted.$"
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
	.string "When entering a challenge at a BATTLE\n"
	.string "FRONTIER facility, POKéMON may not\l"
	.string "be holding the same kind of item.\p"
	.string "Please make sure that all POKéMON\n"
	.string "entering a challenge are holding\l"
	.string "different items.$"
	// バトルフロンティアの しせつにｎ
	// ポケモンを ちょうせん させるときｐ
	// それぞれの ポケモンがｎ
	// おなじ どうぐを もつことは できませんｐ
	// ちょうせん させる ポケモンにはｎ
	// すべて ちがう どうぐをｌ
	// もたせて おくように してください

BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass: @ 8267357
	.string "I'm your guide to the FRONTIER PASS.$"
	// こちらでは フロンティアパスのｎ
	// せつめいを いたします!

BattleFrontier_ReceptionGate_Text_LearnAboutWhich1: @ 826737C
	.string "Which would you like to learn about?$"
	// どの せつめいが ききたいですか?

BattleFrontier_ReceptionGate_Text_SymbolsInfo: @ 82673A1
	.string "There are seven facilities at\n"
	.string "the BATTLE FRONTIER.\p"
	.string "TRAINERS who gain recognition for\n"
	.string "their abilities may be rewarded with\l"
	.string "symbols from each of the facilities.\p"
	.string "To earn a symbol, TRAINERS may need\n"
	.string "to defeat other TRAINERS in a row,\l"
	.string "and may need to win events repeatedly.\p"
	.string "It's certainly not easy to win symbols.\n"
	.string "I wish you the best of luck!$"
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
	.string "It is possible to record one battle\n"
	.string "on your FRONTIER PASS.\p"
	.string "You may record a battle you had with\n"
	.string "a friend or friends.\p"
	.string "Or you may record a battle conducted\n"
	.string "at the BATTLE FRONTIER excluding\l"
	.string "matches at the BATTLE PIKE or\l"
	.string "the BATTLE PYRAMID.\p"
	.string "You may choose to record your match\n"
	.string "at the end of a battle.$"
	// あなたの たいせんを ひとつだけｎ
	// パスに きろくする ことが できますｐ
	// おともだち との たいせんかｎ
	// バトルチュ-ブ バトルピラミッド いがいのｌ
	// バトルフロンティアでのｌ
	// たいせんが きろくできますｐ
	// たいせんが おわった ときにｎ
	// きろく するか どうかを きめられます

BattleFrontier_ReceptionGate_Text_BattlePointsInfo: @ 826761C
	.string "Battle Points are rewards given to\n"
	.string "TRAINERS who battled outstandingly\l"
	.string "at the BATTLE FRONTIER.\p"
	.string "You may trade in your Battle Points\n"
	.string "for prizes at the EXCHANGE SERVICE\l"
	.string "CORNER.$"
	// バトルポイントはｎ
	// バトルフロンティアで すばらしいｌ
	// たたかいを した トレ-ナ-にｌ
	// あたえられる ごほうびですｐ
	// ためた ポイントは ひきかえサ-ビスでｎ
	// しょうひんと ひきかえることが できます

