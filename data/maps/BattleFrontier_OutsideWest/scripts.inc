.set LOCALID_SS_TIDAL, 2
.set LOCALID_FERRY_ATTENDANT, 3
.set LOCALID_MANIAC_1, 9
.set LOCALID_MANIAC_2, 10
.set LOCALID_GIRL, 12
.set LOCALID_CAMPER, 14
.set LOCALID_FISHERMAN_2, 18
.set LOCALID_MAN_4, 23

BattleFrontier_OutsideWest_MapScripts:: @ 823D3E1
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideWest_OnTransition
	.byte 0

BattleFrontier_OutsideWest_OnTransition: @ 823D3E7
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	end

BattleFrontier_OutsideWest_EventScript_FerryAttendant:: @ 823D3F0
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_MayISeeYourTicket, MSGBOX_DEFAULT
	checkitem ITEM_SS_TICKET, 1
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_OutsideWest_EventScript_NoSSTicket
	message BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination:: @ 823D416
	multichoicedefault 18, 6, MULTI_SSTIDAL_BATTLE_FRONTIER, 2, 0
	switch VAR_RESULT
	case 0, BattleFrontier_OutsideWest_EventScript_FerryToSlateport
	case 1, BattleFrontier_OutsideWest_EventScript_FerryToLilycove
	case 2, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	case MULTI_B_PRESSED, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	end

BattleFrontier_OutsideWest_EventScript_NoSSTicket:: @ 823D44E
	msgbox BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToSlateport:: @ 823D458
	msgbox BattleFrontier_OutsideWest_Text_SlateportItIs, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_SLATEPORT_CITY_HARBOR, 255, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToLilycove:: @ 823D483
	msgbox BattleFrontier_OutsideWest_Text_LilycoveItIs, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_LILYCOVE_CITY_HARBOR, 255, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination:: @ 823D4AE
	message BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_BoardFerry:: @ 823D4BA
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_FERRY_ATTENDANT, MAP_BATTLE_FRONTIER_OUTSIDE_WEST
	setvar VAR_0x8004, LOCALID_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	return

BattleFrontier_OutsideWest_EventScript_CancelFerrySelect:: @ 823D4D8
	msgbox BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_BattleDomeSign:: @ 823D4E2
	msgbox BattleFrontier_OutsideWest_Text_BattleDomeSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattleFactorySign:: @ 823D4EB
	msgbox BattleFrontier_OutsideWest_Text_BattleFactorySign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign:: @ 823D4F4
	msgbox BattleFrontier_OutsideWest_Text_BattlePikeSign, MSGBOX_SIGN
	end

@ Unused. Of note, Battle Tower is in the East section in the final release
BattleFrontier_OutsideWest_EventScript_UnusedNPC1:: @ 823D4FD
	msgbox BattleFrontier_OutsideWest_Text_ThisIsBattleTower, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC2:: @ 823D4FD
	msgbox BattleFrontier_OutsideWest_Text_CantFindBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Boy1:: @ 823D50F
	msgbox BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Fisherman2:: @ 823D518
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere
	waitmessage
	applymovement LOCALID_FISHERMAN_2, Common_Movement_FaceAwayPlayer
	waitmovement 0
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_Man1:: @ 823D52D
	msgbox BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Maniac1:: @ 823D536
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_Maniac2:: @ 823D53D
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk:: @ 823D544
	applymovement LOCALID_MANIAC_1, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons, MSGBOX_DEFAULT
	applymovement LOCALID_MANIAC_2, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons, MSGBOX_DEFAULT
	closemessage
	delay 25
	applymovement LOCALID_MANIAC_1, Common_Movement_WalkInPlaceFastestUp
	applymovement LOCALID_MANIAC_2, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_Camper:: @ 823D57F
	lock
	faceplayer
	delay 20
	compare VAR_FACING, DIR_NORTH
	call_if_eq BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	compare VAR_FACING, DIR_SOUTH
	call_if_eq BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory
	compare VAR_FACING, DIR_WEST
	call_if_eq BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	compare VAR_FACING, DIR_EAST
	call_if_eq BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	msgbox BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_CamperFaceFactory:: @ 823D5BA
	applymovement LOCALID_CAMPER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory:: @ 823D5C5
	return

BattleFrontier_OutsideWest_EventScript_Girl:: @ 823D5C6
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper
	waitmessage
	compare VAR_FACING, DIR_NORTH
	call_if_eq BattleFrontier_OutsideWest_EventScript_GirlShudderNorth
	compare VAR_FACING, DIR_SOUTH
	call_if_eq BattleFrontier_OutsideWest_EventScript_GirlShudderSouth
	compare VAR_FACING, DIR_WEST
	call_if_eq BattleFrontier_OutsideWest_EventScript_GirlShudderWest
	compare VAR_FACING, DIR_EAST
	call_if_eq BattleFrontier_OutsideWest_EventScript_GirlShudderEast
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_GirlShudderNorth:: @ 823D5FD
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderNorth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderSouth:: @ 823D608
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderSouth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderWest:: @ 823D613
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderWest
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderEast:: @ 823D61E
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderEast
	waitmovement 0
	return

BattleFrontier_OutsideWest_Movement_GirlShudderNorth: @ 823D629
	walk_in_place_fastest_down
	walk_in_place_fastest_down
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderSouth: @ 823D62C
	walk_in_place_fastest_up
	walk_in_place_fastest_up
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderWest: @ 823D62F
	walk_in_place_fastest_right
	walk_in_place_fastest_right
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderEast: @ 823D632
	walk_in_place_fastest_left
	walk_in_place_fastest_left
	step_end

BattleFrontier_OutsideWest_EventScript_Woman2:: @ 823D635
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors, MSGBOX_DEFAULT
	random 2
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors
	goto BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors
	end

BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors:: @ 823D653
	msgbox BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors:: @ 823D65D
	msgbox BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Fisherman1:: @ 823D667
	msgbox BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC3:: @ 823D670
	msgbox BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Gentleman:: @ 823D679
	msgbox BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Lass:: @ 823D682
	msgbox BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_ExpertM:: @ 823D68B
	msgbox BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man2:: @ 823D694
	msgbox BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman1:: @ 823D69D
	msgbox BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan1:: @ 823D6A6
	msgbox BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan2:: @ 823D6AF
	msgbox BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman3:: @ 823D6B8
	lock
	msgbox BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Boy2:: @ 823D6C3
	lock
	msgbox BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_OldMan:: @ 823D6CE
	msgbox BattleFrontier_OutsideWest_Text_DomeAceIsMine, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man4:: @ 823D6D7
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAN_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_PokefanF:: @ 823D6EE
	msgbox BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Text_BattleDomeSign: @ 823D6F7
	.string "여기는 배틀돔!\n"
	.string "노려라! 무적의 슈퍼스타!$"
	// ここは バトルド-ム!ｎ
	// めざせ! むてきの ス-パ-スタ-!

BattleFrontier_OutsideWest_Text_BattleFactorySign: @ 823D737
	.string "여기는 배틀팩토리!\n"
	.string "찾아라! 최강 포켓몬$"
	// ここは バトルファクトリ-!ｎ
	// さがせ! さいきょう ポケモン!

BattleFrontier_OutsideWest_Text_BattlePikeSign: @ 823D772
	.string "여기는 배틀튜브!\n"
	.string "선택하라! 3개의 길!$"
	// ここは バトルチュ-ブ!ｎ
	// えらべ! 3つの みち!

BattleFrontier_OutsideWest_Text_ThisIsBattleTower: @ 823D7A6
	.string "여기는 배틀타워야!\p"
	.string "트레이너는 단련한 포켓몬으로\n"
	.string "오직 연승해 나가지!$"
	// ここは バトルタワ- さ!ｐ
	// トレ-ナ-は きたえあげた ポケモンでｎ
	// ひたすら かちぬいて いくのさ!

BattleFrontier_OutsideWest_Text_MayISeeYourTicket: @ 823D808
	.string "연락선을 이용하시려는 거군요!\n"
	.string "티켓은 가지고 계신가요?$"
	// れんらくせんを ごりよう ですね!ｎ
	// チケットは おもち でしょうか?

BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard: @ 823D842
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "티켓이 없다!\p"
	.string "...죄송합니다!\p"
	.string "배에는 티켓을 가진 분들만\n"
	.string "탑승하실 수 있습니다$"
	// あはｎ
	// チケットを もっていない!ｐ
	// ……もうしわけ ありません!ｐ
	// ふねに のれるのはｎ
	// チケットの ある かた だけです

BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo: @ 823D89D
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "승선티켓을 보여줬다!\p"
	.string "네! 확인했습니다!\p"
	.string "어디로 가시겠어요?$"
	// あはｎ
	// ふねのチケットを みせた!ｐ
	// はい! けっこう です!ｐ
	// いきさきは どちら でしょう?

BattleFrontier_OutsideWest_Text_SlateportItIs: @ 823D8F2
	.string "잿빛도시 말씀이시군요!$"
	// カイナシティ ですね!

BattleFrontier_OutsideWest_Text_LilycoveItIs: @ 823D90E
	.string "해안시티 말씀이시군요!$"
	// ミナモシティ ですね!

BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime: @ 823D929
	.string "또 이용해 주십시오!$"
	// また ごりよう ください!

BattleFrontier_OutsideWest_Text_PleaseBoardFerry: @ 823D94B
	.string "연락선에서 잠시 기다려 주십시오$"
	// れんらくせんに のって おまちください

BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo: @ 823D97A
	.string "어디로 가시겠어요?$"
	// いきさきは どちら でしょう?

BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends: @ 823D99C
	.string "나 친구들 중에서는\n"
	.string "제일 강했는데\l"
	.string "여기에 오니까 전혀 안되겠어!$"
	// ぼく ともだちの なかではｎ
	// いちばん つよいのにｌ
	// ここに きてみたら てんで ダメ!

BattleFrontier_OutsideWest_Text_CantFindBattleTower: @ 823D9DD
	.string "배틀타워에 가고 싶은데\n"
	.string "프런티어패스의 맵을 봐도\l"
	.string "뭐가 뭔지... 너무 넓어...$"
	// バトルタワ-に いきたいのにｎ
	// フロンティアパスの マップを みてもｌ
	// なにが なんだか…… ひろすぎる……

BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere: @ 823DA60
	.string "바로 도전하고 싶은데\n"
	.string "오는 도중에 뱃멀미가 나버렸어\p"
	.string "우웁...$"
	// すぐに チャレンジ したいのにｎ
	// くる とちゅうで ふなよい して しまったｐ
	// うっぷ……

BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere: @ 823DABF
	.string "여기에는 누구나\n"
	.string "올 수 있는 게 아냐\p"
	.string "강함을 인정받은 트레이너가\n"
	.string "올 수 있는 곳이라고!\p"
	.string "그래서... 배틀프런티어를\n"
	.string "모르는 트레이너도 많은 거지$"
	// ここには だれでもｎ
	// こられるって わけじゃ ないんだぜｐ
	// つよさを みとめられた トレ-ナ-がｎ
	// つれてきて もらえる ところなんだ!ｐ
	// だから…… バトルフロンティアの ことをｎ
	// しらない トレ-ナ-も おおいんだ

BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons: @ 823DB7D
	.string "있잖아 형...\p"
	.string "정말로 자신의 포켓몬이 없어도\n"
	.string "도전할 수 있어? 괜찮은 거야?$"
	// なぁなぁ にいちゃん……ｐ
	// ほんとに じぶんの ポケモン いなくてもｎ
	// ちょうせん できるの? だいじょうぶ?

BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons: @ 823DBCE
	.string "괘 괜찮을 거야!\p"
	.string "분명...\p"
	.string "뭔가 무서운 아저씨였는데\n"
	.string "“포켓몬을 빌려주마!”라고\l"
	.string "말했거든...$"
	// だ だいじょうぶ だよ!ｐ
	// きっと……ｐ
	// なんだか おっかない おっさん だったけどｎ
	// 「ポケモン かして やるぜ!」 ってｌ
	// いってた じゃん か……

BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons: @ 823DC36
	.string "저기에 있는 건 배틀팩토리\n"
	.string "강한 포켓몬을 대여할 수 있어!\p"
	.string "근데 대여 포켓몬은\n"
	.string "대체 누가 키우고 있는 걸까?$"
	// あそこに あるのが バトルファクトリ-ｎ
	// つよいポケモンを レンタル できるんだ!ｐ
	// でもさ レンタル ポケモンってｎ
	// いったい だれが そだてて いるんだろう?

BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper: @ 823DCB0
	.string "세비퍼가 무서워서\n"
	.string "배틀튜브에 못 들어가겠어...\p"
	.string "하 하지만 모처럼 왔으니까\n"
	.string "힘내서 제패해야지...! 부들부들$"
	// ハブネ-クが こわくてｎ
	// バトルチュ-ブに はいれないの……ｐ
	// で でも せっかく きたんだからｎ
	// がんばって せいは するわ……! ブルブル

BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors: @ 823DD3B
	.string "저기! 나하고 가위바위보 하자!\n"
	.string "가위 바위 보!\p"
	.string "...... ...... ......$"
	// ね! わたしと ジャンケンしよ!ｎ
	// じゃ-ん け-ん ぽん!ｐ
	// …… …… ……

BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge: @ 823DD7A
	.string "와! 이겼다!\n"
	.string "좋아 배틀튜브에 도전해야지!$"
	// わ-い かっちゃった!ｎ
	// よし バトルチュ-ブに ちょうせん しよ!

BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge: @ 823DDAD
	.string "아-아 져버렸다...\p"
	.string "지금은 운이 나쁜가봐\n"
	.string "배틀튜브는 내일 가야겠다$"
	// あ-あ まけちゃったあ……ｐ
	// いまは うんが わるいみたいｎ
	// バトルチュ-ブは また あしたにしよ

BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling: @ 823DE15
	.string "이 근처에서 어째선가 낚시를\n"
	.string "하려고 하는 사람은\l"
	.string "나밖에 없는 거겠지!\p"
	.string "...... 에 아무것도 안 잡힌다고?\n"
	.string "실망이네$"
	// この かいわいで なぜか つりをｎ
	// たのしもうと して いるのはｌ
	// おれ くらいの ものだろうな!ｐ
	// …… え なんにも つれないの?ｎ
	// がっ かり

BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol: @ 823DEB4
	.string "오늘은 심볼을 받을 때까지\n"
	.string "절대로 포기하지 않고 힘내야지!$"
	// きょうは シンボルを もらえる まではｎ
	// ぜったいに あきらめないで がんばろっと!

BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome: @ 823DEFD
	.string "어라... 배틀돔에\n"
	.string "도전하려고요?\p"
	.string "그럼 서로 이겨서\n"
	.string "만날 수 있도록 힘냅시다$"
	// おや…… バトルド-ムにｎ
	// ちょうせん されますか?ｐ
	// では おたがい かちあがってｎ
	// おあい できるように がんばりましょう

BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa: @ 823DF7D
	.string "봐봐 할아버지 여기 여기!\n"
	.string "여기가 배틀돔이야! 힘내!$"
	// ほら じいちゃん こっち こっち!ｎ
	// ここが バトルド-ムよっ! がんばって!

BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe: @ 823DFBF
	.string "허허 여기가 배틀돔인가...\n"
	.string "좋아 신사에게는 지지 않겠다!\p"
	.string "...근데 입구는 어디에 있지?$"
	// ほほおぉ ここが バトルド-ムか……ｎ
	// よし ジェントルマンには まけんぞ!ｐ
	// ……で いりぐちは どこ なんじゃろ?

BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo: @ 823E01E
	.string "얼마 전까지는\n"
	.string "아무것도 없었던 토지였는데...\p"
	.string "굉-장한 곳이 되어버렸네!\n"
	.string "다음엔 엄마도 데리고 올까$"
	// ちょっと まえ まではｎ
	// なんも なかった とち なのに……ｐ
	// すっげ- ところに なっちゃったなあ!ｎ
	// こんど か-ちゃんも つれて きてやるか

BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier: @ 823E09F
	.string "드디어 배틀프런티어에 왔어!\p"
	.string "모두 내 강함과 아름다움에\n"
	.string "꼼짝도 못하게 될 거야!$"
	// とうとう バトルフロンティアに きたわ!ｐ
	// みんな あたしの つよさと うつくしさにｎ
	// くぎづけに なるわね!

BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople: @ 823E102
	.string "우물 우물\p"
	.string "이 광장에는\n"
	.string "강한 사람이 많이 있는 것 같네\l"
	.string "우물 우물$"
	// もぐ もぐｐ
	// この ひろば にはｎ
	// つよいひと いっぱい らしいねえｌ
	// もぐ もぐ

BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike: @ 823E154
	.string "와구 와구\p"
	.string "지난번에 배틀튜브에서\n"
	.string "눈매가 나빠서 무서워 보이는\l"
	.string "누님을 만났어\l"
	.string "와구 와구\p"
	.string "그러더니 “언제까지 먹을 거야!”라고\n"
	.string "화내서 엉망진창으로 당해버렸어\p"
	.string "이야 무서웠지\p"
	.string "와구 와구$"
	// ぱく ぱくｐ
	// このまえ バトルチュ-ブでｎ
	// めつきが わるくて こわそうなｌ
	// おねえさんに あったんだよｌ
	// ぱく ぱくｐ
	// そしたら 「いつまで くってるの!」ってｎ
	// おこられて ボコボコに やられちったよｐ
	// いやあ こわかったな-ｐ
	// ぱく ぱく

BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet: @ 823E273
	.string "뭐?!\n"
	.string "너 뭘 말하는 거야?\p"
	.string "나 왠지\n"
	.string "지난번에 응원하고 있을 때\l"
	.string "찌-릿하고 눈이 맞았다니까!$"
	// はあっ!?ｎ
	// あなた なに いって くれちゃってるの?ｐ
	// わたし なんかｎ
	// こないだ おうえん してたらｌ
	// ば---っちり めが あったんだからっ!

BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering: @ 823E2E9
	.string "뭐라고-?!\p"
	.string "그건 옆에 있었던 내가\n"
	.string "있어서 그런 거잖아!\p"
	.string "그 사람은 내 응원을\n"
	.string "듣고 쳐다본 거라고-오!$"
	// なんだとぉ-!?ｐ
	// それは となりに ぼくがｎ
	// いたから でしょっ!ｐ
	// あのひとは ぼくの おうえんをｎ
	// きいて ふりむいて くれたんだ っつ-の!

BattleFrontier_OutsideWest_Text_DomeAceIsMine: @ 823E37E
	.string "아아 시끄러워! 시끄러워!\p"
	.string "너희같은 애들은\n"
	.string "어딘가의 체육관 관장이나\l"
	.string "응원하라고!!\p"
	.string "돔슈퍼스타는 나만의!\n"
	.string "나만의 아이돌이라고!!$"
	// ああ うるさいっ! うるさいわっ!ｐ
	// おみゃ-ら みたいな おこさまはｎ
	// どこぞの ジムリ-ダ-でもｌ
	// おうえん しとけっ!!ｐ
	// ド-ムス-パ-スタ-は わしだけっ!ｎ
	// わしだけの アイドルなのっ!!

BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers: @ 823E410
	.string "저기서 싸우고 있는 사람들...\p"
	.string "저래 봬도 원래는 엄청 강하고\n"
	.string "유명한 트레이너였어\p"
	.string "하지만 배틀돔에서\n"
	.string "어떤 트레이너에게 엉망으로 져서\l"
	.string "모두 그 트레이너의\l"
	.string "엄청난 팬이 되어버렸지\p"
	.string "지금은 매일 도전하지도 않고\n"
	.string "배틀돔에 응원하러 다니고 있어$"
	// あそこで けんか してる ひとたち……ｐ
	// あれでも もともとは すごく つよくてｎ
	// ゆうめいな トレ-ナ- だったんだよｐ
	// だけど バトルト-ナメントでｎ
	// あるトレ-ナ-に ボコボコに まけてからｌ
	// みんな そのトレ-ナ-のｌ
	// だいファンに なっちゃったんだｐ
	// いまじゃ まいにち ちょうせんも しないでｎ
	// バトルド-ムに おうえんに かよってるよ

BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier: @ 823E5A5
	.string "배틀프런티어의 어딘가에서\n"
	.string "엄청 꼬리가 긴 포켓몬을\l"
	.string "봤다고 들었어-!\p"
	.string "아아 귀여운 포켓몬일 거야 분명...\p"
	.string "이젠 도전보다도\n"
	.string "그 애를 찾으러 가고 싶네-$"
	// バトルフロンティアの どっかでｎ
	// えらく しっぽの なが-い ポケモンをｌ
	// みたって きいたわ-!ｐ
	// ああ かわいい ポケモンに ちがいない……ｐ
	// もう- ちょうせん よりもｎ
	// そのこ さがしに いきたいわぁ-

