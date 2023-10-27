.set LOCALID_ATTENDANT, 1
.set LOCALID_NURSE, 2
.set LOCALID_GIRL, 4
.set LOCALID_MAN, 5

TrainerHill_Entrance_MapScripts:: @ 82680AC
	map_script MAP_SCRIPT_ON_RESUME, TrainerHill_Entrance_OnResume
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, TrainerHill_Entrance_OnReturn
	map_script MAP_SCRIPT_ON_TRANSITION, TrainerHill_Entrance_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, TrainerHill_Entrance_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerHill_Entrance_OnFrame
	.byte 0

TrainerHill_Entrance_OnTransition: @ 82680C6
	setflag FLAG_LANDMARK_TRAINER_HILL
	getplayerxy VAR_TEMP_D, VAR_RESULT
	end

@ Unused
TrainerHill_Entrance_OnWarp: @ 82680CF
	end

TrainerHill_Entrance_OnResume: @ 82680D0
	trainerhill_resumetimer
	setvar VAR_TEMP_0, 0
	trainerhill_getusingereader
	compare VAR_RESULT, FALSE  @ VAR_RESULT always FALSE here
	goto_if_eq TrainerHill_Entrance_EventScript_TryFaceAttendant
	setobjectxy OBJ_EVENT_ID_PLAYER, 9, 6
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_TryFaceAttendant:: @ 82680FF
	trainerhill_getwon
	compare VAR_RESULT, TRUE
	goto_if_eq TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant:: @ 826811A
	end

TrainerHill_Entrance_OnReturn: @ 826811B
	addobject LOCALID_NURSE
	addobject LOCALID_ATTENDANT
	addobject LOCALID_MAN
	addobject LOCALID_GIRL
	end

TrainerHill_Entrance_OnLoad: @ 8268128
	compare VAR_TEMP_D, 17
	call_if_eq TrainerHill_Entrance_EventScript_OpenCounterDoor
	end

TrainerHill_Entrance_EventScript_OpenCounterDoor:: @ 8268134
	setmetatile 17, 10, METATILE_TrainerHill_GreenFloorTile, 0
	return

TrainerHill_Entrance_OnFrame: @ 826813E
	map_script_2 VAR_TEMP_0, 0, TrainerHill_Entrance_EventScript_ExitChallenge
	map_script_2 VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_ExitElevator
	map_script_2 VAR_TEMP_5, 1, TrainerHill_Entrance_EventScript_EntryTrigger
	map_script_2 VAR_TEMP_1, 1, TrainerHill_EventScript_WarpToEntranceCounter
	.2byte 0

TrainerHill_Entrance_EventScript_ExitElevator:: @ 8268160
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerExitElevator
	waitmovement 0
	setmetatile 17, 10, METATILE_TrainerHill_CounterDoor, 1
	special DrawWholeMapView
	playse SE_CLICK
	waitse
	setvar VAR_TEMP_D, 0
	releaseall
	end

TrainerHill_Entrance_EventScript_ExitChallenge:: @ 8268182
	setvar VAR_TEMP_0, 1
	trainerhill_getstatus
	switch VAR_RESULT
	case TRAINER_HILL_PLAYER_STATUS_LOST, TrainerHill_Entrance_EventScript_ExitChallengeLost
	case TRAINER_HILL_PLAYER_STATUS_ECARD_SCANNED, TrainerHill_Entrance_EventScript_ExitChallengeECard
	case TRAINER_HILL_PLAYER_STATUS_NORMAL, TrainerHill_Entrance_EventScript_EndExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeLost:: @ 82681B5
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_TooBadTremendousEffort, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_PlayerExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeECard:: @ 82681CA
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_MovedReceptionHereForSwitch, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_PlayerExitChallenge:: @ 82681DA
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 0
	special HealPlayerParty
	releaseall
TrainerHill_Entrance_EventScript_EndExitChallenge:: @ 82681EE
	end

TrainerHill_Entrance_EventScript_Nurse:: @ 82681EF
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

TrainerHill_Entrance_EventScript_Attendant:: @ 82681FD
	lock
	faceplayer
	trainerhill_inchallenge
	compare VAR_RESULT, FALSE
	goto_if_eq TrainerHill_Entrance_EventScript_ThanksForPlaying
	msgbox TrainerHill_Entrance_Text_HopeYouGiveItYourBest, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AttendantEnd

TrainerHill_Entrance_EventScript_ThanksForPlaying:: @ 826821F
	msgbox TrainerHill_Entrance_Text_ThankYouForPlaying, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AttendantEnd:: @ 8268227
	release
	end

TrainerHill_Entrance_EventScript_EntryTrigger:: @ 8268229
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_Closed
	msgbox TrainerHill_Entrance_Text_WelcomeToTrainerHill, MSGBOX_DEFAULT
	trainerhill_getsaved
	compare VAR_RESULT, FALSE
	call_if_eq TrainerHill_Entrance_EventScript_SaveGame
	trainerhill_allfloorsused
	compare VAR_RESULT, TRUE
	goto_if_eq TrainerHill_Entrance_EventScript_AllFloorsUsed
	msgbox TrainerHill_Entrance_Text_TrainersUpToFloorX, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers

TrainerHill_Entrance_EventScript_AllFloorsUsed:: @ 8268275
	msgbox TrainerHill_Entrance_Text_TrainersInEveryRoom, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AskChallengeTrainers:: @ 826827D
	message TrainerHill_Entrance_Text_LikeToChallengeTrainers
	waitmessage
	multichoice 15, 6, MULTI_YESNOINFO, 0
	switch VAR_RESULT
	case 0, TrainerHill_Entrance_EventScript_ChooseChallenge
	case 1, TrainerHill_Entrance_EventScript_CancelEntry
	case 2, TrainerHill_Entrance_EventScript_Info
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Info:: @ 82682BA
	msgbox TrainerHill_Entrance_Text_ExplainTrainerHill, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers
	end

TrainerHill_Entrance_EventScript_ChooseChallenge:: @ 82682C8
	multichoice 13, 2, MULTI_TAG_MATCH_TYPE, 0
	switch VAR_RESULT
	case 4, TrainerHill_Entrance_EventScript_CancelEntry
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	trainerhill_settag VAR_RESULT
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 1
	setvar VAR_TEMP_5, 0
	special HealPlayerParty
	msgbox TrainerHill_Entrance_Text_TimeProgessGetSetGo, MSGBOX_DEFAULT
	trainerhill_start
	releaseall
	end

TrainerHill_Entrance_EventScript_CancelEntry:: @ 8268314
	setvar VAR_TEMP_5, 0
	msgbox TrainerHill_Entrance_Text_PleaseVisitUsAgain, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_EventScript_SaveGame:: @ 826832E
	msgbox TrainerHill_Entrance_Text_SaveGameBeforeEnter, MSGBOX_DEFAULT
	trainerhill_setsaved
	setvar VAR_TEMP_5, 1
	call Common_EventScript_SaveGame
	compare VAR_RESULT, FALSE
	goto_if_eq TrainerHill_Entrance_EventScript_SaveFailed
	trainerhill_setsaved
	return

TrainerHill_Entrance_EventScript_SaveFailed:: @ 826835C
	trainerhill_clearsaved
	goto TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Closed:: @ 826836A
	msgbox TrainerHill_Entrance_Text_StillGettingReady, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_Movement_PlayerFaceAttendant: @ 826837F
	face_right
	step_end

TrainerHill_Entrance_Movement_PushPlayerBackFromCounter: @ 8268381
	walk_down
	step_end

@ Unused
TrainerHill_Entrance_Movement_FaceUp: @ 8268383
	face_up
	step_end

TrainerHill_Entrance_Movement_PlayerExitElevator: @ 8268385
	walk_down
	walk_down
	step_end

TrainerHill_Entrance_EventScript_Records:: @ 8268388
	lockall
	fadescreen FADE_TO_BLACK
	special ShowTrainerHillRecords
	waitstate
	releaseall
	end

TrainerHill_Entrance_EventScript_Man:: @ 8268391
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ManTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_ManTrainerHillClosed:: @ 82683A3
	msgbox TrainerHill_Entrance_Text_CantWaitToTestTheWaters, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Girl:: @ 82683AC
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_GirlTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_GirlTrainerHillClosed:: @ 82683BE
	msgbox TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Clerk:: @ 82683C7
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ExpandedPokemart
	pokemart TrainerHill_Entrance_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Basic: @ 82683E8
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_NONE
	release
	end

TrainerHill_Entrance_EventScript_ExpandedPokemart:: @ 8268402
	pokemart TrainerHill_Entrance_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Expanded: @ 8268414
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_NONE
	release
	end

TrainerHill_Entrance_Text_StillGettingReady: @ 8268430
	.string "여기는 여러 트레이너분들과\n"
	.string "태그배틀을 즐길 수 있는\l"
	.string "트레이너힐입니다!\p"
	.string "현재 이곳은 공사 중입니다\n"
	.string "나중에 다시 와주세요$"

TrainerHill_Entrance_Text_WelcomeToTrainerHill: @ 82684C6
	.string "어서 오세요!\p"
	.string "여기는 여러 트레이너분들과\n"
	.string "태그배틀을 즐길 수 있는\l"
	.string "트레이너힐입니다!$"
	// ようこそ いらっしゃいました!ｐ
	// ここは さまざまな トレ-ナ-さんとのｎ
	// タッグバトルが たのしめるｌ
	// トレ-ナ-ヒルです!

TrainerHill_Entrance_Text_SaveGameBeforeEnter: @ 826851C
	.string "처음 방문하신\n"
	.string "트레이너님이시군요\p"
	.string "이용하시기 전에 리포트를\n"
	.string "작성하도록 하겠습니다$"
	// はじめて ごりようになるｎ
	// トレ-ナ-さん ですねｐ
	// ごりように なるまえに レポ-トをｎ
	// おかきくださいませ

TrainerHill_Entrance_Text_TrainersUpToFloorX: @ 8268564
	.string "지금 모여 있는\n"
	.string "트레이너님은...\p"
	.string "{STR_VAR_1}층까지인 것 같습니다$"
	// ただいま あつまっているｎ
	// トレ-ナ-さんは ……ｐ
	// §いかい までの ようですね

TrainerHill_Entrance_Text_TrainersInEveryRoom: @ 826859E
	.string "지금 모여 있는\n"
	.string "트레이너님은 ......\p"
	.string "모든 방에 트레이너님이\n"
	.string "모여 있는 것 같습니다!$"
	// ただいま あつまっているｎ
	// トレ-ナ-さんは ……ｐ
	// すべての へやに トレ-ナ-さんがｎ
	// あつまっている みたいですね!

TrainerHill_Entrance_Text_LikeToChallengeTrainers: @ 82685F8
	.string "트레이너님들과\n"
	.string "승부하겠습니까?$"
	// トレ-ナ-さんたちとｎ
	// しょうぶ しますか?

TrainerHill_Entrance_Text_TimeProgessGetSetGo: @ 826862A
	.string "그럼 시간을 잴 테니\n"
	.string "열심히 해주세요!\p"
	.string "자리에 서서.........\p"
	.string "준비...\p"
	.string "땅!!$"
	// それでは じかんを はかりますのでｎ
	// がんばってくださいね!ｐ
	// いちについて…………………ｐ
	// ようい……ｐ
	// ドン!!

TrainerHill_Entrance_Text_PleaseVisitUsAgain: @ 826866F
	.string "다음번 방문을 기다리고 있겠습니다!$"
	// また おこしくださいね!

TrainerHill_Entrance_Text_TooBadTremendousEffort: @ 8268689
	.string "아쉽게 됐군요!\p"
	.string "정말 좋은 승부였다고\n"
	.string "생각합니다\p"
	.string "또 와주세요!$"
	// ざんねん でしたね!ｐ
	// とっても いい しょうぶｎ
	// だったと おもいますｐ
	// また きてくださいね!

TrainerHill_Entrance_Text_HopeYouGiveItYourBest: @ 82686F4
	.string "열심히 해주세요!$"
	// がんばってくださいね!

TrainerHill_Entrance_Text_MovedReceptionHereForSwitch: @ 8268712
	.string "트레이너님이 자리를 바꾸면\n"
	.string "위험하므로\p"
	.string "이쪽으로 이동하게\n"
	.string "되었습니다!\p"
	.string "죄송합니다!$"
	// トレ-ナ-さんたちが いれかわってｎ
	// あぶないのでｐ
	// こちらに いどう させてｎ
	// いただきました!ｐ
	// ごめんなさい!

TrainerHill_Entrance_Text_ThankYouForPlaying: @ 82687AC
	.string "수고하셨습니다!$"
	// おつかれさまでした!

TrainerHill_Entrance_Text_ExplainTrainerHill: @ 82687C3
	.string "이곳 트레이너힐에서는\n"
	.string "타임어택이라고 하는 경기가\l"
	.string "치뤄지고 있습니다\p"
	.string "빠른 시간은 타임보드에\n"
	.string "적히므로 친구와 시간을\l"
	.string "비교해보세요\p"
	.string "접수처부터 옥상에 있는\n"
	.string "오너에게 말을 걸 때까지의\l"
	.string "시간이 측정됩니다\p"
	.string "또한 트레이너와의 승부에서\n"
	.string "이겨도 경험치나 돈은\l"
	.string "얻을 수 없습니다$"
	// ここ トレ-ナ-ヒルではｎ
	// タイムアタックという きょうぎがｌ
	// おこなわれますｐ
	// はやい じかんは タイムボ-ドにｎ
	// のりますので ともだちと じかんをｌ
	// くらべて みてくださいｐ
	// うけつけから おくじょうにいるｎ
	// オ-ナ-に はなしかけるまでのｌ
	// じかんが はかられますｐ
	// また トレ-ナ-との しょうぶでｎ
	// かっても けいけんちや おかねのｌ
	// やりとりは おこなわれません

@ Unused
TrainerHill_Entrance_Text_NeedAtLeastTwoPokemon: @ 826890D
	.string "어라?\n"
	.string "한 마리밖에 없으시군요\p"
	.string "두 마리 이상 데리고\n"
	.string "다시 방문해 주십시오$"
	// おや?ｎ
	// てもちが 1ぴきしか いないようですねｐ
	// てもちを 2ひき いじょうに してからｎ
	// またおこし くださいませ

TrainerHill_Roof_Text_YouFinallyCameBravo: @ 8268986
	.string "으음!\p"
	.string "마침내 온 건가!\n"
	.string "와버린 건가!\p"
	.string "응 알고 있다네!\n"
	.string "왜 자네가 이런 곳까지\l"
	.string "혼자서 온 건지!\p"
	.string "이곳의 오너인\n"
	.string "이 몸과...\p"
	.string "태그를 맺기 위해서지-!\n"
	.string "와우!\p"
	.string "...아\n"
	.string "아닌가?\p"
	.string "어쨌든 자네의 배틀은 잘 봤네\n"
	.string "실로 굉장했었네! 브라보!$"
	// ムム!ｐ
	// ついに きたね!ｎ
	// きてしまったね!ｐ
	// ン- わかっているさ-!ｎ
	// なんで きみが こんなところまでｌ
	// ひとりで きてしまったのか!ｐ
	// ここの オ-ナ-であるｎ
	// この わたくしと……ｐ
	// タッグを くみにきたんだろ-!ｎ
	// ワオ!ｐ
	// ……あｎ
	// ちがうの?ｐ
	// いや きみの たたかい みせてもらったよｎ
	// じつに すばらしかった! ブラボ-!

TrainerHill_Roof_Text_HaveTheMostMarvelousGift: @ 8268AC5
	.string "그런 굉장한 자네에게는\n"
	.string "이것을 선물하지-!$"
	// そんな すばらしい キミにはｎ
	// これを プレゼントだ-!

TrainerHill_Roof_Text_FullUpBeBackLaterForThis: @ 8268B07
	.string "지닌 물건이 가득한 건가-\n"
	.string "나중에 가지러 오게-!$"
	// もちものが いっぱいだね-ｎ
	// あとで とりにきて-!

TrainerHill_Roof_Text_GotHereMarvelouslyQuickly: @ 8268B43
	.string "오-! 설마 이렇게 빨리\n"
	.string "여기까지 올 줄이야-!?\p"
	.string "이 몸을 만나기 위해 그렇게\n"
	.string "열심히 해주다니-!\p"
	.string "기쁘니 접수처의\n"
	.string "타임보드에 기록해두겠네!$"
	// オ-! もしかして すごく はやくｎ
	// ここまで きたんじゃない-!?ｐ
	// この わたくしに あうために そんなにｎ
	// がんばって くれたんだね-!ｐ
	// うれしすぎるから うけつけのｎ
	// タイムボ-ドに きろく しておくぜ-!

TrainerHill_Roof_Text_YouWerentVeryQuick: @ 8268C03
	.string "오-...\n"
	.string "하지만 그렇게 빠르진 않았네-$"
	// オ-……ｎ
	// でも あんまり はやく なかったね-

TrainerHill_Roof_Text_ArriveZippierNextTime: @ 8268C31
	.string "다음엔 더 빨리 이 몸을\n"
	.string "만나러 와주면 좋겠어!\p"
	.string "그러면 그때야말로\n"
	.string "태그를 맺도록 하지!\p"
	.string "그럼 또 보세! 아미고!$"
	// つぎは もっと はやく このわたくしにｎ
	// あいにきてくれると いいかもね!ｐ
	// そしたら こんどこそｎ
	// タッグを くもうな-!ｐ
	// じゃあ またな! アミ-ゴ!

@ Unused
TrainerHill_Roof_Text_BuiltTrainerHillToFindPartner: @ 8268CC6
	.string "이 나와 태그를 맺어줄\n"
	.string "파트너를 찾기 위해\p"
	.string "이 트레이너힐을\n"
	.string "만들었다네!$"
	// このわたくしと タッグを くんでくれるｎ
	// パ-トナ-を みつけるためｐ
	// この トレ-ナ-ヒルをｎ
	// つくったんだぜい!

TrainerHill_Entrance_Text_ChallengeTime: @ 8268D47
	.string "{STR_VAR_1}분 {STR_VAR_2}.{STR_VAR_3}초$"
	// §いふん §うびょう §え

TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead: @ 8268D5A
	.string "어떤 조합의 트레이너가\n"
	.string "기다리고 있는 걸까!\p"
	.string "어떤 녀석이 와도\n"
	.string "내가 쓰러뜨려 주겠어!$"
	// どんな くみあわせの トレ-ナ-がｎ
	// まっているのか!ｐ
	// どんな やつがきてもｎ
	// おれが たおしてみせるぜ!

TrainerHill_Entrance_Text_CantWaitToTestTheWaters: @ 8268DDA
	.string "강한 트레이너들이 이 트레이너힐로\n"
	.string "모여든다고 들었어!\p"
	.string "빨리 배틀해보고 싶어!\p"
	.string "내 앞길을 막는 녀석은\n"
	.string "누구든지 날려버릴 거야!$"

TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop: @ 8268E6A
	.string "저기에 타임보드가\n"
	.string "있는 거 보이지?\p"
	.string "나는 친구들과 누가 더\n"
	.string "빠르고 높게 갈 수 있는지\l"
	.string "시간을 재서 경쟁하고 있어!$"
	// あそこに タイムボ-ドがｎ
	// あるでしょ?ｐ
	// わたしは ともだちと どっちがはやくｎ
	// いちばん うえまで いけるかｌ
	// タイムを きそってるのよ!

TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen: @ 8268EDC
	.string "여기 언제 여는지\n"
	.string "알고 있어?\p"
	.string "첫 번째 도전자가 되려고\n"
	.string "여기서 기다리고 있거든!$"

TrainerHill_Elevator_Text_ReturnToReception: @ 8268F3E
	.string "접수처로 돌아가겠습니까?$"
	// うけつけに もどりますか?
