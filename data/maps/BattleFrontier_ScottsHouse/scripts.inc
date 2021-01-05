.set LOCALID_SCOTT, 1

BattleFrontier_ScottsHouse_MapScripts:: @ 82636A7
	.byte 0

BattleFrontier_ScottsHouse_EventScript_Scott:: @ 82636A8
	lock
	faceplayer
	goto_if_set FLAG_TEMP_4, BattleFrontier_ScottsHouse_EventScript_GivenBerry
	goto_if_set FLAG_TEMP_3, BattleFrontier_ScottsHouse_EventScript_GivenShield
	goto_if_set FLAG_TEMP_2, BattleFrontier_ScottsHouse_EventScript_GivenBattlePoints
	goto BattleFrontier_ScottsHouse_EventScript_CheckGiveItems
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveItems:: @ 82636CB
	goto_if_unset FLAG_SCOTT_GIVES_BATTLE_POINTS, BattleFrontier_ScottsHouse_EventScript_WelcomeToFrontier
	goto_if_unset FLAG_COLLECTED_ALL_SILVER_SYMBOLS, BattleFrontier_ScottsHouse_EventScript_CheckSilverSymbols
	goto_if_unset FLAG_COLLECTED_ALL_GOLD_SYMBOLS, BattleFrontier_ScottsHouse_EventScript_CheckGoldSymbols
	goto BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveShield:: @ 82636EC
	goto_if_unset FLAG_RECEIVED_SILVER_SHIELD, BattleFrontier_ScottsHouse_EventScript_CheckGiveSilverShield
	goto_if_unset FLAG_RECEIVED_GOLD_SHIELD, BattleFrontier_ScottsHouse_EventScript_CheckGiveGoldShield
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment
	end

BattleFrontier_ScottsHouse_EventScript_CheckSilverSymbols:: @ 8263704
	goto_if_unset FLAG_SYS_TOWER_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_DOME_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PALACE_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_ARENA_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_FACTORY_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PIKE_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PYRAMID_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	msgbox BattleFrontier_ScottsHouse_Text_YouveCollectedAllSilverSymbols, MSGBOX_DEFAULT
	giveitem ITEM_LANSAT_BERRY
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_ScottsHouse_EventScript_BerryPocketFull
	setflag FLAG_COLLECTED_ALL_SILVER_SYMBOLS
	setflag FLAG_TEMP_4
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGoldSymbols:: @ 826376A
	goto_if_unset FLAG_SYS_TOWER_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_DOME_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PALACE_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_ARENA_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_FACTORY_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PIKE_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PYRAMID_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	msgbox BattleFrontier_ScottsHouse_Text_YouveCollectedAllGoldSymbols, MSGBOX_DEFAULT
	giveitem ITEM_STARF_BERRY
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_ScottsHouse_EventScript_BerryPocketFull
	setflag FLAG_COLLECTED_ALL_GOLD_SYMBOLS
	setflag FLAG_TEMP_4
	release
	end

BattleFrontier_ScottsHouse_EventScript_BerryPocketFull:: @ 82637D0
	msgbox BattleFrontier_ScottsHouse_Text_BerryPocketStuffed, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_GivenBerry:: @ 82637DA
	msgbox BattleFrontier_ScottsHouse_Text_SoGladIBroughtYouHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_RandomComment:: @ 82637E4
	random 3
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_ScottsHouse_EventScript_FrontierBrainComment
	compare VAR_RESULT, 2
	goto_if_eq BattleFrontier_ScottsHouse_EventScript_ArtisanCaveComment
	msgbox BattleFrontier_ScottsHouse_Text_WhyIGoSeekingTrainers, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_FrontierBrainComment:: @ 8263807
	msgbox BattleFrontier_ScottsHouse_Text_HaveYouMetFrontierBrain, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_ArtisanCaveComment:: @ 8263811
	msgbox BattleFrontier_ScottsHouse_Text_MayFindWildMonsInFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveSilverShield:: @ 826381B
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	tower_get TOWER_DATA_WIN_STREAK
	compare VAR_RESULT, 50
	goto_if_ge BattleFrontier_ScottsHouse_EventScript_GiveSilverShield
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_OPEN
	tower_get TOWER_DATA_WIN_STREAK
	compare VAR_RESULT, 50
	goto_if_ge BattleFrontier_ScottsHouse_EventScript_GiveSilverShield
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment
	end

BattleFrontier_ScottsHouse_EventScript_GiveSilverShield:: @ 826387A
	msgbox BattleFrontier_ScottsHouse_Text_Beat50TrainersInARow, MSGBOX_DEFAULT
	givedecoration DECOR_SILVER_SHIELD
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_ScottsHouse_EventScript_NoRoomForShield
	setflag FLAG_RECEIVED_SILVER_SHIELD
	setflag FLAG_TEMP_3
	goto BattleFrontier_ScottsHouse_EventScript_GivenShield
	end

BattleFrontier_ScottsHouse_EventScript_NoRoomForShield:: @ 82638A0
	msgbox BattleFrontier_ScottsHouse_Text_ComeBackForThisLater, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_GivenShield:: @ 82638AA
	msgbox BattleFrontier_ScottsHouse_Text_ExpectingToHearEvenGreaterThings, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveGoldShield:: @ 82638B4
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	tower_get TOWER_DATA_WIN_STREAK
	compare VAR_RESULT, 100
	goto_if_ge BattleFrontier_ScottsHouse_EventScript_GiveGoldShield
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_OPEN
	tower_get TOWER_DATA_WIN_STREAK
	compare VAR_RESULT, 100
	goto_if_ge BattleFrontier_ScottsHouse_EventScript_GiveGoldShield
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment
	end

BattleFrontier_ScottsHouse_EventScript_GiveGoldShield:: @ 8263913
	msgbox BattleFrontier_ScottsHouse_Text_Beat100TrainersInARow, MSGBOX_DEFAULT
	givedecoration DECOR_GOLD_SHIELD
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_ScottsHouse_EventScript_NoRoomForShield
	setflag FLAG_RECEIVED_GOLD_SHIELD
	setflag FLAG_TEMP_3
	goto BattleFrontier_ScottsHouse_EventScript_GivenShield
	end

BattleFrontier_ScottsHouse_EventScript_GivenBattlePoints:: @ 8263939
	msgbox BattleFrontier_ScottsHouse_Text_ExpectingGreatThings, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_WelcomeToFrontier:: @ 8263943
	msgbox BattleFrontier_ScottsHouse_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	closemessage
	delay 30
	compare VAR_FACING, DIR_NORTH
	call_if_eq BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayNorth
	compare VAR_FACING, DIR_SOUTH
	call_if_eq BattleFrontier_ScottsHouse_EventScript_ScottFaceAwaySouth
	compare VAR_FACING, DIR_EAST
	call_if_eq BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayEast
	compare VAR_FACING, DIR_WEST
	call_if_eq BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayWest
	msgbox BattleFrontier_ScottsHouse_Text_HowMuchEffortItTookToMakeReal, MSGBOX_DEFAULT
	applymovement LOCALID_SCOTT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_ScottsHouse_Text_HaveThisAsMementoOfOurPathsCrossing, MSGBOX_DEFAULT
	compare VAR_SCOTT_STATE, 13
	goto_if_eq BattleFrontier_ScottsHouse_EventScript_Give4BattlePoints
	compare VAR_SCOTT_STATE, 9
	goto_if_ge BattleFrontier_ScottsHouse_EventScript_Give3BattlePoints
	compare VAR_SCOTT_STATE, 6
	goto_if_ge BattleFrontier_ScottsHouse_EventScript_Give2BattlePoints
	goto BattleFrontier_ScottsHouse_EventScript_Give1BattlePoint
	end

BattleFrontier_ScottsHouse_EventScript_Give4BattlePoints:: @ 82639BC
	buffernumberstring 0, 4
	setvar VAR_0x8004, 4
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_Give3BattlePoints:: @ 82639CB
	buffernumberstring 0, 3
	setvar VAR_0x8004, 3
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_Give2BattlePoints:: @ 82639DA
	buffernumberstring 0, 2
	setvar VAR_0x8004, 2
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_Give1BattlePoint:: @ 82639E9
	buffernumberstring 0, 1
	setvar VAR_0x8004, 1
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints:: @ 82639F8
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_ScottsHouse_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	msgbox BattleFrontier_ScottsHouse_Text_ExplainBattlePoints, MSGBOX_DEFAULT
	setflag FLAG_SCOTT_GIVES_BATTLE_POINTS
	setflag FLAG_TEMP_2
	release
	end

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayNorth:: @ 8263A13
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwaySouth:: @ 8263A1E
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayEast:: @ 8263A29
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayWest:: @ 8263A34
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

BattleFrontier_ScottsHouse_Text_WelcomeToBattleFrontier: @ 8263A3F
	.string "금작화: 아아 어서 와\n"
	.string "헤헤... 좁은 곳이라서 미안해\p"
	.string "그럼 다시 한 번 {PLAYER}\n"
	.string "잘 왔어 배틀프런티어에!\p"
	.string "여기는 내 꿈의 결정체!\n"
	.string "몇 년씩이나 걸렸지만 겨우\l"
	.string "만들 수 있었지!$"
	// エニシダ『ああ いらっしゃいｎ
	// へへ…… せまい ところで ごめんよｐ
	// では あらためて §あ§おｎ
	// ようこそ バトルフロンティアへ!ｐ
	// ここは わたしの ゆめの けっしょう!ｎ
	// なんねんも かかって やっとｌ
	// かたちに することが できたんだ!

BattleFrontier_ScottsHouse_Text_HowMuchEffortItTookToMakeReal: @ 8263B29
	.string "생각해 보면 긴 여정이었어...\n"
	.string "강한 트레이너를 찾아서\l"
	.string "혼자서 여행하고...\l"
	.string "여기까지 오는 데에 얼마나\l"
	.string "많은 노력과 시간을 들였는지...$"
	// おもえば ながい みちのりだった……ｎ
	// つよい トレ-ナ-を もとめてｌ
	// ただひとり たびだち……ｌ
	// ここまで くるのに どれだけのｌ
	// どりょくと じかんが ひつようだったか……

BattleFrontier_ScottsHouse_Text_HaveThisAsMementoOfOurPathsCrossing: @ 8263BD4
	.string "아니 이런 옛날 이야기로는\n"
	.string "진행이 안 되지!\p"
	.string "어쨌든 마음껏\n"
	.string "포켓몬 승부를 즐겨줘!\p"
	.string "이건 나와 {PLAYER}{K_IGA}\n"
	.string "여행하면서 몇 번이고 만났던\l"
	.string "기념으로 줄게!$"
	// いや こんな むかしばなしをｎ
	// していても はじまらないな!ｐ
	// とにかく こころ ゆくまでｎ
	// ポケモンしょうぶを たのしんで くれ!ｐ
	// これは わたしと §あ§おがｎ
	// なんども たびさきで であったｌ
	// きねんだよ!

BattleFrontier_ScottsHouse_Text_ObtainedXBattlePoints: @ 8263CB0
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "{STR_VAR_1}BP를 받았다!$"
	// §あは バトルポイントをｎ
	// §い BP もらった!

BattleFrontier_ScottsHouse_Text_ExplainBattlePoints: @ 8263CD0
	.string "금작화: 배틀포인트는\n"
	.string "프런티어패스로 볼 수 있어!\p"
	.string "포인트는 이 프런티어에서\n"
	.string "활약하면 활약할수록\l"
	.string "모이게 되지!\p"
	.string "원하는 것과 교환하거나\n"
	.string "마음대로 쓰도록 해!$"
	// エニシダ『バトルポイントはｎ
	// フロンティアパスで みられるからね!ｌ
	// ポイントは この フロンティアでｌ
	// かつやく すれば するほどｌ
	// たまっていく ものなんだ!ｐ
	// ほしい ものと ひきかえたりｎ
	// すきなように かつようして くれ!

BattleFrontier_ScottsHouse_Text_ExpectingGreatThings: @ 8263DB8
	.string "네 활약을\n"
	.string "많이 기대하고 있어!$"
	// きみの かつやくｎ
	// おおいに きたい しているからね!

BattleFrontier_ScottsHouse_Text_WhyIGoSeekingTrainers: @ 8263DDD
	.string "금작화: 어느 트레이너나\n"
	.string "각자의 인생이 있지?\p"
	.string "하지만 배틀할 때는\n"
	.string "그런 거에 전혀 관계없이\l"
	.string "모두 똑같아져!\p"
	.string "나는 그런\n"
	.string "배틀의 순수함이\l"
	.string "너무나도 좋아\p"
	.string "그래서 여러 곳에 다니면서\n"
	.string "진심으로 배틀하는 트레이너를\l"
	.string "잔뜩 초대한 거야!$"
	// エニシダ『どの トレ-ナ-にもｎ
	// それぞれの じんせいが あるだろ?ｐ
	// でも たたかう ときはｎ
	// そんなこと ぜんぜん かんけいないｌ
	// みんな いっしょ なんだよね!ｐ
	// わたしは そういうｎ
	// たたかいの じゅんすいさ ってのがｌ
	// とても すきなんだよｐ
	// だから いろんな ところに でかけてｎ
	// しんけんに たたかってる トレ-ナ-をｌ
	// いっぱい しょうたい してくるのさ!

BattleFrontier_ScottsHouse_Text_HaveYouMetFrontierBrain: @ 8263F12
	.string "금작화: 내 브레인들한테서\n"
	.string "프런티어패스의 심볼을\l"
	.string "이미 받았으려나?\p"
	.string "내가 발견한\n"
	.string "최강의 프런티어브레인도\l"
	.string "네 강함을 본다면\l"
	.string "아마도 놀랄 테지!$"
	// エニシダ『わが ブレ-ンたち からｎ
	// フロンティアパスの シンボルはｌ
	// もう もらったかな?ｐ
	// わたしが みいだしたｎ
	// さいきょうの フロンティアブレ-ンもｌ
	// きみの つよさを みたらｌ
	// おそらく おどろく だろうね!

BattleFrontier_ScottsHouse_Text_MayFindWildMonsInFrontier: @ 8263FFE
	.string "금작화: 너는 분명\n"
	.string "승부만이 아니라\l"
	.string "포켓몬 도감도 모으고 있었지!\p"
	.string "어쩌면 배틀프런티어에도\n"
	.string "포켓몬과 만날 수 있는 장소가\l"
	.string "있을지도 모르지? 우후후...$"
	// エニシダ『きみは たしかｎ
	// しょうぶ だけでは なくてｌ
	// ポケモンずかんも つくって いたね!ｐ
	// もしかしたら バトルフロンティア にもｎ
	// ポケモンと であえる ばしょがｌ
	// あるかも しれないよ? うふふ……

BattleFrontier_ScottsHouse_Text_YouveCollectedAllSilverSymbols: @ 82640BC
	.string "금작화: 배틀프런티어는\n"
	.string "즐기고 있어?\p"
	.string "...잠깐 오옷!\p"
	.string "네 프런티어패스!\n"
	.string "은심볼이 모두\l"
	.string "모여 있잖아!\p"
	.string "굉장하구나 너는 생각대로\n"
	.string "강한 트레이너였어!\p"
	.string "보통 이런 일은 안하지만\n"
	.string "부디 기념으로 이걸 받아줘!\l"
	.string "너라면 잘 쓸 수 있을 거야...!$"
	// エニシダ『バトルフロンティアをｎ
	// たのしんで くれて いるかな?ｐ
	// ……って おおっっ!ｐ
	// きみの フロンティアパスっ!ｎ
	// ぎんのシンボルが すべてｌ
	// そろって いるじゃ ないか!ｐ
	// すごいなあ きみは おもったとおりｎ
	// つよい トレ-ナ- だったんだなあ!ｐ
	// ふつうは こんな ことは しないんだがｎ
	// ぜひ きねんに これを もらってくれ!ｌ
	// きみなら つかいこなせる はずだよ……!

BattleFrontier_ScottsHouse_Text_YouveCollectedAllGoldSymbols: @ 8264216
	.string "금작화: 배틀프런티어는\n"
	.string "즐기고 있어?\p"
	.string "...잠깐 우와아아앗!\p"
	.string "네 프런티어패스!\n"
	.string "금심볼이 모두\l"
	.string "모여 있잖아!\p"
	.string "이건 정말 대단해!\n"
	.string "역시 너는 생각대로\l"
	.string "굉장한 트레이너였어!\p"
	.string "...... ...... ......\p"
	.string "{PLAYER}! 부디 네게\n"
	.string "이걸 선물하게 해줘!\p"
	.string "너라면 이것의 가치를\n"
	.string "알아줄 거라고 생각해!$"
	// エニシダ『バトルフロンティアはｎ
	// まんきつ してるかな?ｐ
	// ……って うひょおおっっ!ｐ
	// きみの フロンティアパス-っ!ｎ
	// きんのシンボルが すべてｌ
	// そろって いるじゃ ないか!ｐ
	// これはすごいっ!ｎ
	// やっぱり きみは おもったとおりｌ
	// すごい トレ-ナ- だったんだなあ!ｐ
	// …… …… ……ｐ
	// §あ§お! ぜひ きみにｎ
	// これを プレゼント させて くれ!ｐ
	// きみならば これの かちをｎ
	// わかって くれると おもうんだ!

BattleFrontier_ScottsHouse_Text_SoGladIBroughtYouHere: @ 8264373
	.string "이야- 내가 생각해도\n"
	.string "난 트레이너를 보는 눈이 있나 봐\l"
	.string "너를 데리고 와서 정말 다행이야!\l"
	.string "하하하$"
	// いや- われながらｎ
	// トレ-ナ-を みるめが さえてるな-ｌ
	// きみを つれてきて ほんと よかった!ｌ
	// ほく ほく

BattleFrontier_ScottsHouse_Text_BerryPocketStuffed: @ 82643EB
	.string "나무열매 포켓이 가득찬 모양이네$"
	// きのみポケットが いっぱい みたいね

BattleFrontier_ScottsHouse_Text_Beat50TrainersInARow: @ 8264412
	.string "금작화: 오옷 들었어!\n"
	.string "배틀타워에서 활약했다며!\l"
	.string "50연승을 달성한 거지?\p"
	.string "굉장하구만 기념으로\n"
	.string "이걸 받아줘!$"
	// エニシダ『おっ きいたよ!ｎ
	// バトルタワ-での かつやく!ｌ
	// 50にん いじょう かちぬいたって?ｐ
	// すごいなあ きねんにｎ
	// これを うけとって くれよ!

BattleFrontier_ScottsHouse_Text_Beat100TrainersInARow: @ 826449F
	.string "금작화: 오옷 들었어!\n"
	.string "배틀타워에서 활약했다며!\l"
	.string "100연승을 달성한 거지?\p"
	.string "엄청 대단한데-!\n"
	.string "부디 이걸 기념으로 받아줘!$"
	// エニシダ『おおうっ きいたよ!ｎ
	// バトルタワ-での だいかつやく!ｌ
	// 100にん いじょう かちぬいたって?ｐ
	// すごすぎるな-!ｎ
	// ぜひ これを きねんに うけとってくれ!

BattleFrontier_ScottsHouse_Text_ExpectingToHearEvenGreaterThings: @ 8264546
	.string "앞으로도 더욱더\n"
	.string "기대하고 있을게!$"
	// これからも ますますｎ
	// きたい しているよ!

BattleFrontier_ScottsHouse_Text_ComeBackForThisLater: @ 8264583
	.string "...잠깐 지닌 물건이 가득하다면\n"
	.string "정리하고 나서 다시 와줘!$"
	// ……って にもつが いっぱいならｎ
	// とって おくから またおいで!

