.set LOCALID_FAMILIAR_GRUNT, 13

SlateportCity_OceanicMuseum_1F_MapScripts:: @ 820AD95
	.byte 0

SlateportCity_OceanicMuseum_1F_EventScript_EntranceAttendant:: @ 820AD96
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeLeft:: @ 820AD9F
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeRight:: @ 820ADB0
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee:: @ 820ADC1
	showmoneybox 0, 0, 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee
	closemessage
	hidemoneybox
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee:: @ 820ADE8
	checkmoney 50, 0
	compare VAR_RESULT, FALSE
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 50, 0
	updatemoneybox 0, 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney:: @ 820AE18
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway
	msgbox SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway:: @ 820AE39
	msgbox SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter: @ 820AE4B
	walk_down
	step_end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt1:: @ 820AE4D
	msgbox SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt2:: @ 820AE56
	msgbox SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt3:: @ 820AE5F
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt4:: @ 820AE68
	msgbox SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt5:: @ 820AE71
	msgbox SlateportCity_OceanicMuseum_1F_Text_RustboroBungled, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt6:: @ 820AE7A
	msgbox SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_WhirlpoolExperiment:: @ 820AE83
	msgbox SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_WaterfallExperiment:: @ 820AE8C
	msgbox SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanSoilDisplay:: @ 820AE95
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_BeachSandDisplay:: @ 820AE9E
	msgbox SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact1:: @ 820AEA7
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact2:: @ 820AEB0
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact3:: @ 820AEB9
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_FossilDisplay:: @ 820AEC2
	msgbox SlateportCity_OceanicMuseum_1F_Text_FossilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_DepthMeasuringMachine:: @ 820AECB
	msgbox SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron1:: @ 820AED4
	msgbox SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron2:: @ 820AEDD
	msgbox SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron3:: @ 820AEE6
	msgbox SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron4:: @ 820AEEF
	msgbox SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGrunt:: @ 820AEF8
	lock
	faceplayer
	delay 8
	playse SE_PIN
	applymovement LOCALID_FAMILIAR_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FAMILIAR_GRUNT, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM46
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief
	setflag FLAG_RECEIVED_TM46
	msgbox SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_NORTH
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth
	compare VAR_FACING, DIR_SOUTH
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth
	compare VAR_FACING, DIR_WEST
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	compare VAR_FACING, DIR_EAST
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth:: @ 820AF6C
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth
	applymovement LOCALID_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth:: @ 820AF83
	applymovement LOCALID_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast:: @ 820AF93
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast
	applymovement LOCALID_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited:: @ 820AFAA
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_FAMILIAR_AQUA_GRUNT
	playse SE_EXIT
	removeobject LOCALID_FAMILIAR_GRUNT
	release
	end

SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief:: @ 820AFB5
	msgbox SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis, MSGBOX_DEFAULT
	release
	end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth: @ 820AFBF
	delay_16
	delay_8
	delay_4
	walk_in_place_fastest_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast: @ 820AFC4
	delay_16
	walk_in_place_fastest_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit: @ 820AFC7
	face_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth: @ 820AFCE
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter: @ 820AFD5
	.string "바다의 과학박물관에\n"
	.string "어서 오세요 환영합니다!\p"
	.string "입장료는 50원입니다\n"
	.string "견학하시겠습니까?$"
	// うみの かがく はくぶつかんへｎ
	// ようこそ いらっしゃいませ!ｐ
	// にゅうじょうりょう 50えんに なりますｎ
	// けんがく して いきますか?

SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself: @ 820B026
	.string "여유롭게 구경하세요!$"
	// ごゆっくり どうぞ!

SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney: @ 820B03D
	.string "...어머 돈이 부족하네요$"
	// ……あら おかねが たりませんわ

SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup: @ 820B075
	.string "...어머 아까 그 단체의 일행이신가요?\n"
	.string "고객님만 뒤처지셨다니 어쩔 수 없네요\l"
	.string "빨리 들어가세요!$"
	// ……あら さっきの だんたいさん?ｎ
	// あなただけ おくれちゃって しかたないわねｌ
	// はやく とおっちゃって!

SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll: @ 820B0E8
	.string "모두를 위해서\n"
	.string "우리 아쿠아단이 있는 거야!$"
	// みんなの ためにｎ
	// われわれ アクアだんは いるのよ!

SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere: @ 820B112
	.string "현장에서 집합하라는 얘길 듣고\n"
	.string "여기로 모인 건 좋은데...\p"
	.string "정작 리더가 아직 오시지 않았어$"
	// げんちしゅうごう でｎ
	// ここに あつまったのは いいけど……ｐ
	// かんじんの リ-ダ-が まだ こないんだ

SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich: @ 820B165
	.string "여기에 놓여 있는 것들\n"
	.string "모두 훔쳐 가면 벌이 좀 되려나?$"
	// ここに おいてある ものｎ
	// かっぱらうと もうかるかな?

SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds: @ 820B19C
	.string "이 지식을 이용해서\n"
	.string "나쁜 짓이나 해볼까...$"
	// この ちしきを いかしてｎ
	// わるいこと してやるか……

SlateportCity_OceanicMuseum_1F_Text_RustboroBungled: @ 820B1D4
	.string "동료가 금탄도시에서 실수만 안 했으면\n"
	.string "여기에 올 일도 없었을 텐데!$"
	// なかまが カナズミで ドジらなければｎ
	// ここに こなくて すんだのによ!

SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney: @ 820B218
	.string "아까 50원이 없어서\n"
	.string "접수처에서 엄청 시간 잡아먹었어...$"
	// さっき 50えんが なくてｎ
	// うけつけで すごい じかん かかったよ……

SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling: @ 820B25F
	.string "바다에 대해 공부해서\n"
	.string "포켓몬 승부 때 써먹을 거야$"
	// うみのこと べんきょう してｎ
	// ポケモンしょうぶに やくだてたいの

SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel: @ 820B2A2
	.string "저 말이죠\n"
	.string "바다를 보면 흥분돼요!\p"
	.string "이런 저한테 있어서\n"
	.string "해양관장은 동경하는 사람\l"
	.string "넘버1에 속하는 사람이에요!$"
	// わたくしッｎ
	// うみを みると こうふん するのですッ!ｐ
	// そんな わたくしに とってｎ
	// クスノキかんちょうはｌ
	// あこがれの ひと ナンバ-1 なのですッ!

SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow: @ 820B302
	.string "바다는 끝없이 넓고\n"
	.string "끝없이 깊어...\p"
	.string "분명히 우리가 모르는 포켓몬도\n"
	.string "많이 있을 거야$"
	// うみは はてしなく ひろくｎ
	// どこまでも ふかい……ｐ
	// きっと われわれが しらない ポケモンもｎ
	// いっぱい いるのだろうね

SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon: @ 820B369
	.string "나 바다의 포켓몬 가지고 싶어\p"
	.string "왜냐면 서늘한 느낌이 들어서\n"
	.string "껴안으면 기분 좋을 거 같거든$"
	// あたし うみの ポケモンが ほしいのｐ
	// だって ひんやりと しててｎ
	// だきしめたら きもちよさそう だもの

SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis: @ 820B3AB
	.string "히익-!!\n"
	.string "왜 네가 여기 있는 거야!?\p"
	.string "나? 난 금잔터널에서\n"
	.string "네게 손도 발도 못 쓰고 당한\l"
	.string "아쿠아단이야\p"
	.string "이거 줄 테니까 봐줘!$"
	// ひえ-!!ｎ
	// なんで おまえ ここに いるんだよ!?ｐ
	// おれ? おれは カナシダ トンネルでｎ
	// おまえに コテンパンに されたｌ
	// アクアだん だよｐ
	// これを やるから ゆるしてくれよ!

SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain: @ 820B449
	.string "그 기술머신\n"
	.string "나보다 네가 가지는 게 어울려!\p"
	.string "그럼 이만 으하하하-!$"
	// その わざマシンｎ
	// おれより おまえのほうが にあうぜ!ｐ
	// じゃあな わははは-!

SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis: @ 820B49B
	.string "부탁이니까\n"
	.string "어떻게든 받아줘!$"
	// たのむからｎ
	// なんとかして うけとってくれよ!

SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment: @ 820B4CF
	.string "유리 안에서 파란 물이\n"
	.string "빙글빙글 돌고 있다!\p"
	.string "“이것은 바람의 힘을 이용해 인공적으로\n"
	.string "  바다회오리를 일으키는 실험입니다”$"
	// ガラスの なかで あおい みずがｎ
	// くるくると まわって いる!ｐ
	// 「これは かぜの ちからで じんこうてきにｎ
	//  うずしおを おこす じっけん です」

SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment: @ 820B547
	.string "유리 안에서 빨간 공이 떠올랐다\n"
	.string "가라앉기를 반복하고 있다!\p"
	.string "“이것은 공의 부력을 이용한\n"
	.string "  폭포오르기의 원리 실험입니다”$"
	// ガラスの なかで あかい ボ-ルがｎ
	// うかんだり しずんだり している!ｐ
	// 「これは ボ-ルの ふりょくを りようしたｎ
	//  たきのぼりの げんりの じっけん です」

SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay: @ 820B5CA
	.string "바다 밑바닥 흙의 표본이다!\p"
	.string "“바다 밑바닥에는 오랜 세월에 걸쳐\n"
	.string "  생물의 사체가 쌓여\l"
	.string "  지층이 형성되어 있습니다”\p"
	.string "“이 지층을 분석함으로써\n"
	.string "  먼 옛날에 대해 알 수 있는 것입니다”$"
	// うみの そこの つちの みほんだ!ｐ
	// 「かいていには ながい ねんげつを かけてｎ
	//  せいぶつの しがいが ふりつもりｌ
	//  ちそうが かたち づくられて いきます」ｐ
	// 「これらを ぶんせき することでｎ
	//  とおい むかしの ことが わかるのです」

SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay: @ 820B699
	.string "바닷가 모래의 표본이다!\p"
	.string "“산에서 강을 타고 떠내려온 돌은\n"
	.string "  물속에서 구르는 동안\l"
	.string "  부서지고 깎여갑니다”\p"
	.string "“그 돌들이 작은 알갱이가 되어\n"
	.string "  바닷가의 모래가 되는 것입니다”$"
	// うみべの すなの みほんだ!ｐ
	// 「やまから かわを つたって きた いしはｎ
	//  みずの なかで ころがる うちにｌ
	//  くだかれたり けずれたり していきます」ｐ
	// 「それらが ちいさな つぶに なってｎ
	//  うみべの すなが できて いくのです」

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1: @ 820B74B
	.string "“바다 미니 정보 1\n"
	.string "  왜 바닷물은 파란색인가요?”\p"
	.string "“빛에는 다양한 색이 있고\n"
	.string "  대부분의 빛은 물에 들어가면\l"
	.string "  그 색 자체를 잃게 됩니다”\p"
	.string "“그렇지만 파란빛만은\n"
	.string "  그 색 그대로 유지되기 때문에\l"
	.string "  바다는 파랗게 보이는 것입니다”$"
	// 「うみの まめちしき その1ｎ
	//  なぜ うみの みずは あおいの?」ｐ
	// 「ひかりには いくつもの いろが あってｎ
	//  ほとんどの ひかりは みずに はいるとｌ
	//  その いろが なくなって いきます」ｐ
	// 「けれど あおい ひかり だけはｎ
	//  そのままの いろで のこる ためｌ
	//  うみは あおく みえるのです」

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2: @ 820B81F
	.string "“바다 미니 정보 2\n"
	.string "  어째서 바닷물은 짠가요?”\p"
	.string "“해수에는 바위에서 나오는\p"
	.string "  소금의 근본인\n"
	.string "  나트륨 이온과 염소 이온이라는\l"
	.string "  물질이 많은 양 포함되어 있습니다\l"
	.string "  그래서 핥으면 짠 것입니다”$"
	// 「うみの まめちしき その2ｎ
	//  なぜ うみの みずは しょっぱいの?」ｐ
	// 「かいすい には いわから にじみでたｐ
	//  しおの もとに なるｎ
	//  ナトリウムイオン と えんそイオンｌ
	//  という ぶっしつが おおく ふくまれｌ
	//  だから なめると しょっぱいのです」

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3: @ 820B912
	.string "“바다 미니 정보 3\n"
	.string "  바다와 육지 중 어느 쪽이 더 넓은가요?”\p"
	.string "“대략 바다가 70퍼센트고\n"
	.string "  육지가 30퍼센트 정도입니다\p"
	.string "  육지에 비해 바다는\n"
	.string "  그 두 배 이상인 것이죠”$"
	// 「うみの まめちしき その3ｎ
	//  うみと りくは どちらが ひろいの?」ｐ
	// 「だいたい うみが 70パ-セントでｎ
	//  りくが 30パ-セント くらいですｐ
	//  りくちに くらべて うみはｎ
	//  その 2ばい いじょうも あるのです」

SlateportCity_OceanicMuseum_1F_Text_FossilDisplay: @ 820B9C0
	.string "울퉁불퉁한 물결 모양의 화석이 있다!\p"
	.string "“바다 밑바닥에 가라앉아 있는 흙에는\n"
	.string "  해수의 흐름에 의해\l"
	.string "  파도와 같은 문양이 생깁니다”\p"
	.string "“그 모습 그대로 화석이 된 것을\n"
	.string "  연흔이라고 부르고 있습니다”$"
	// デコボコに なみうった かせきが ある!ｐ
	// 「うみの そこに たまった つちにはｎ
	//  かいすいが ながれる えいきょうでｌ
	//  なみの ような もようが できます」ｐ
	// 「それが そのまま かせきに なったものをｎ
	//  リップルマ-クと よんでいます」

SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine: @ 820BA9C
	.string "동그란 돔 안에서\n"
	.string "알 수 없는 기계가 돌아가고 있다!\p"
	.string "무언가의 깊이를 조사하고 있는 걸까?$"
	// まるい ド-ムの なかで なんだかｎ
	// よく わからない きかいが まわってる!ｐ
	// なにかの ふかさを しらべるのかな?

