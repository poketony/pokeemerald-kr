.set LOCALID_TRICK_MASTER, 1

Route110_TrickHouseEnd_MapScripts:: @ 826ACAF
	map_script MAP_SCRIPT_ON_RESUME, Route110_TrickHouseEnd_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHouseEnd_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route110_TrickHouseEnd_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route110_TrickHouseEnd_OnWarp
	.byte 0

Route110_TrickHouseEnd_OnResume: @ 826ACC4
	compare VAR_TEMP_1, 1
	call_if_eq Route110_TrickHouseEnd_EventScript_SetDoorClosedMetatile
	end

Route110_TrickHouseEnd_OnTransition: @ 826ACD0
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	special SetTrickHouseNuggetFlag
	end

Route110_TrickHouseEnd_OnWarp: @ 826ACDE
	map_script_2 VAR_TEMP_2, 0, Route110_TrickHouseEnd_EventScript_SetTrickMasterPos
	.2byte 0

Route110_TrickHouseEnd_EventScript_SetTrickMasterPos:: @ 826ACE8
	addobject LOCALID_TRICK_MASTER
	showobjectat LOCALID_TRICK_MASTER, MAP_ROUTE110_TRICK_HOUSE_END
	turnobject LOCALID_TRICK_MASTER, DIR_EAST
	end

Route110_TrickHouseEnd_OnFrame: @ 826ACF5
	map_script_2 VAR_TEMP_1, 0, Route110_TrickHouseEnd_EventScript_CloseDoor
	.2byte 0

Route110_TrickHouseEnd_EventScript_CloseDoor:: @ 826ACFF
	setvar VAR_TEMP_1, 1
	call Route110_TrickHouseEnd_EventScript_SetDoorClosedMetatile
	special DrawWholeMapView
	end

Route110_TrickHouseEnd_EventScript_SetDoorClosedMetatile:: @ 826AD0D
	setmetatile 10, 1, METATILE_GenericBuilding_TrickHouse_Door_Closed, 1
	return

Route110_TrickHouseEnd_EventScript_TrickMaster:: @ 826AD17
	lock
	faceplayer
	msgbox Route110_TrickHouseEnd_Text_YouveMadeItToMe, MSGBOX_DEFAULT
	setvar VAR_TEMP_2, 1
	switch VAR_TRICK_HOUSE_LEVEL
	case 0, Route110_TrickHouseEnd_EventScript_CompletedPuzzle1
	case 1, Route110_TrickHouseEnd_EventScript_CompletedPuzzle2
	case 2, Route110_TrickHouseEnd_EventScript_CompletedPuzzle3
	case 3, Route110_TrickHouseEnd_EventScript_CompletedPuzzle4
	case 4, Route110_TrickHouseEnd_EventScript_CompletedPuzzle5
	case 5, Route110_TrickHouseEnd_EventScript_CompletedPuzzle6
	case 6, Route110_TrickHouseEnd_EventScript_CompletedPuzzle7
	case 7, Route110_TrickHouseEnd_EventScript_CompletedPuzzle8
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle1:: @ 826AD84
	msgbox Route110_TrickHouseEnd_Text_AllNightToPlantTrees, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_RARE_CANDY
	compare VAR_RESULT, FALSE
	call_if_eq Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle2:: @ 826ADC0
	msgbox Route110_TrickHouseEnd_Text_AllNightToMakeMaze, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_TIMER_BALL
	compare VAR_RESULT, FALSE
	call_if_eq Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle3:: @ 826ADFC
	msgbox Route110_TrickHouseEnd_Text_AllNightToPreparePanels, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_HARD_STONE
	compare VAR_RESULT, FALSE
	call_if_eq Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle4:: @ 826AE38
	msgbox Route110_TrickHouseEnd_Text_AllNightToShoveBoulders, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_SMOKE_BALL
	compare VAR_RESULT, FALSE
	call_if_eq Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle5:: @ 826AE74
	msgbox Route110_TrickHouseEnd_Text_AllNightToMakeMechadolls, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_TM12
	compare VAR_RESULT, FALSE
	call_if_eq Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle6:: @ 826AEB0
	msgbox Route110_TrickHouseEnd_Text_AllNightToInstallDoors, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_MAGNET
	compare VAR_RESULT, FALSE
	call_if_eq Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle7:: @ 826AEEC
	msgbox Route110_TrickHouseEnd_Text_AllNightSettingUpArrows, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_PP_MAX
	compare VAR_RESULT, FALSE
	call_if_eq Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle8:: @ 826AF28
	msgbox Route110_TrickHouseEnd_Text_AllNightPolishingFloors, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_SOUTH
	call_if_eq Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwaySouth
	compare VAR_FACING, DIR_NORTH
	call_if_eq Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayNorth
	compare VAR_FACING, DIR_WEST
	call_if_eq Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayWest
	compare VAR_FACING, DIR_EAST
	call_if_eq Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayEast
	delay 30
	msgbox Route110_TrickHouseEnd_Text_FountainOfIdeasRunDry, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TRICK_MASTER, Common_Movement_FacePlayer
	waitmovement 0
	delay 30
	msgbox Route110_TrickHouseEnd_Text_DefeatedMePreferWhichTent, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	call Route110_TrickHouseEnd_EventScript_ChooseTent
	compare VAR_RESULT, FALSE
	call_if_eq Route110_TrickHouseEnd_EventScript_NoRoomForTent
	msgbox Route110_TrickHouseEnd_Text_LeavingOnJourney, MSGBOX_DEFAULT
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	special ResetTrickHouseNuggetFlag
	release
	end

Route110_TrickHouseEnd_EventScript_ChooseTent:: @ 826AFA5
	multichoice 0, 0, MULTI_TENT, 1
	switch VAR_RESULT
	case 0, Route110_TrickHouseEnd_EventScript_GiveRedTent
	goto Route110_TrickHouseEnd_EventScript_GiveBlueTent

Route110_TrickHouseEnd_EventScript_GiveRedTent:: @ 826AFBF
	givedecoration DECOR_RED_TENT
	return

Route110_TrickHouseEnd_EventScript_GiveBlueTent:: @ 826AFC7
	givedecoration DECOR_BLUE_TENT
	return

Route110_TrickHouseEnd_EventScript_TrickMasterExit:: @ 826AFCF
	applymovement LOCALID_TRICK_MASTER, Route110_TrickHouse_Movement_TrickMasterSpin
	waitmovement 0
	playse SE_M_EXPLOSION
	applymovement LOCALID_TRICK_MASTER, Route110_TrickHouse_Movement_TrickMasterJumpAway
	waitmovement 0
	removeobject LOCALID_TRICK_MASTER
	addvar VAR_TRICK_HOUSE_LEVEL, 1
	return

Route110_TrickHouseEnd_EventScript_BagFull:: @ 826AFEF
	call Common_EventScript_BagIsFull
	msgbox Route110_TrickHouseEnd_Text_NoRoomForThis, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 1
	return

Route110_TrickHouseEnd_EventScript_NoRoomForTent:: @ 826B002
	call Common_EventScript_NoRoomForDecor
	msgbox Route110_TrickHouseEnd_Text_NoRoomInPC, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 1
	return

Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwaySouth:: @ 826B015
	applymovement LOCALID_TRICK_MASTER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayNorth:: @ 826B020
	applymovement LOCALID_TRICK_MASTER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayWest:: @ 826B02B
	applymovement LOCALID_TRICK_MASTER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayEast:: @ 826B036
	applymovement LOCALID_TRICK_MASTER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

Route110_TrickHouseEnd_EventScript_TrickMasterExitTrigger:: @ 826B041
	lockall
	turnobject LOCALID_TRICK_MASTER, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_TRICK_MASTER, Common_Movement_ExclamationMark
	waitmovement 0
	delay 20
	applymovement LOCALID_TRICK_MASTER, Route110_TrickHouseEnd_Movement_TrickMasterSurprise
	waitmovement 0
	playse SE_M_EXPLOSION
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox Route110_TrickHouseEnd_Text_YoureIgnoringMe, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route110_TrickHouseEnd_Movement_KeepPlayerInRoom
	waitmovement 0
	delay 4
	turnobject LOCALID_TRICK_MASTER, DIR_EAST
	releaseall
	end

Route110_TrickHouseEnd_Movement_KeepPlayerInRoom: @ 826B089
	walk_down
	step_end

Route110_TrickHouseEnd_Movement_TrickMasterSurprise: @ 826B08B
	jump_in_place_left
	step_end

Route110_TrickHouseEnd_Text_YouveMadeItToMe: @ 826B08D
	.string "앗!\n"
	.string "자네 여기까지 온 건가!\l"
	.string "으-음... 대단한데!$"
	@ あっ!ｎ
	@ あんた ここまで こられたのか!ｌ
	@ う-む…… できる!

Route110_TrickHouseEnd_Text_AllNightToPlantTrees: @ 826B0BC
	.string "밤을 새서 나무를 심었는데...\p"
	.string "이 몸 다음 다음 다음 다음\n"
	.string "다음 다음으로 대단하군!$"
	@ てつやで きを うえたのに……ｐ
	@ わがはいの つぎの つぎの つぎの つぎのｎ
	@ つぎの つぎ くらいに すごい!

Route110_TrickHouseEnd_Text_AllNightToMakeMaze: @ 826B13B
	.string "밤을 새서 미로를 만들었는데...\p"
	.string "이 몸 다음 다음 다음 다음\n"
	.string "다음으로 대단하군!$"
	@ てつやで めいろを つくったのに……ｐ
	@ わがはいの つぎの つぎの つぎの つぎのｎ
	@ つぎ くらいに すごい!

Route110_TrickHouseEnd_Text_AllNightToPreparePanels: @ 826B1AD
	.string "밤을 새서 문을 갈아 끼웠는데...\p"
	.string "이 몸 다음 다음 다음 다음으로\n"
	.string "대단하군!$"
	@ てつやで ふすまを はりかえたのに……ｐ
	@ わがはいの つぎの つぎの つぎの つぎｎ
	@ くらいに すごい!

Route110_TrickHouseEnd_Text_AllNightToShoveBoulders: @ 826B223
	.string "밤을 새서 바위를 밀어 놨는데...\p"
	.string "이 몸 다음 다음 다음으로\n"
	.string "대단하군!$"
	@ てつやで いわを おして きたのに……ｐ
	@ わがはいの つぎの つぎの つぎｎ
	@ くらいに すごい!

Route110_TrickHouseEnd_Text_AllNightToMakeMechadolls: @ 826B293
	.string "밤을 새서 인형을 만들고\n"
	.string "밤을 새서 퀴즈도 생각했는데...\p"
	.string "이 몸 다음 다음으로\n"
	.string "대단하군!$"
	@ てつやで にんぎょう つくってｎ
	@ てつやで クイズも かんがえたのに……ｐ
	@ わがはいの つぎの つぎｎ
	@ くらいに すごい!

Route110_TrickHouseEnd_Text_AllNightToInstallDoors: @ 826B315
	.string "밤을 새서 문을 설치해 놓았는데...\p"
	.string "이 몸 다음으로\n"
	.string "대단하군!$"
	@ てつやで とびらを とりつけたのに……ｐ
	@ わがはいの つぎｎ
	@ くらいに すごい!

Route110_TrickHouseEnd_Text_AllNightSettingUpArrows: @ 826B365
	.string "밤을 새서 화살표를 정렬해 놨는데...\p"
	.string "이 몸과 동급으로 대단하군!$"
	@ てつやで やじるしを ならべたのに……ｐ
	@ わがはいと おなじ くらい すごい!

Route110_TrickHouseEnd_Text_AllNightPolishingFloors: @ 826B3AB
	.string "밤을 새서 바닥을 닦아 놨는데...\p"
	.string "이 몸보다 더 대단! 할지도...$"
	@ てつやで ゆかを みがいたのに……ｐ
	@ わがはい より すごい! のかも……

Route110_TrickHouseEnd_Text_FountainOfIdeasRunDry: @ 826B3FA
	.string "어 어쩌지...\n"
	.string "숨겨진 장치를 만들 만한\l"
	.string "아이디어가 다 떨어져버렸어...\l"
	.string "또 전국 각지를 돌면서\l"
	.string "새로운 장치를 생각해 와야겠다...$"
	@ ど どうしよう……ｎ
	@ もう カラクリの ネタがｌ
	@ つきて しまった……ｌ
	@ また ぜんこく かくちを まわってｌ
	@ しかけを いろいろ かんがえて くるか……

Route110_TrickHouseEnd_Text_DefeatedMePreferWhichTent: @ 826B485
	.string "인정하고 싶진 않지만\n"
	.string "자네한테 졌다...!\p"
	.string "뭐 몇 번이나 와준 걸 보면\n"
	.string "그만큼 이 몸이\l"
	.string "매력 있었단 소리겠지만 말야\p"
	.string "그거랑 이 몸이 진 거랑은\n"
	.string "관계없어!\p"
	.string "아 그래! 자네와 이 몸의\n"
	.string "우정을 기념해서\l"
	.string "좋은 걸 주도록 하지!\p"
	.string "“빨강텐트”와 “파랑텐트”\n"
	.string "둘 중에 어느 걸 가지고 싶어?$"
	@ みとめたくは ないんだがｎ
	@ あんたには まけた……!ｐ
	@ まあ なんども きてくれた あたりｎ
	@ よっぽど わがはいにｌ
	@ みりょくを かんじたの だろうけどなｐ
	@ そのことと わがはいが まけたこととはｎ
	@ かんけいなし!ｐ
	@ そうだ! あんたと わがはいのｎ
	@ ゆうじょうを きねんしてｌ
	@ いいものを プレゼント しよう!ｐ
	@ 「あかいテント」と「あおいテント」ｎ
	@ ふたつ あるんだが どっちが ほしい?

Route110_TrickHouseEnd_Text_NoRoomInPC: @ 826B615
	.string "뭐 PC에 들어가지 않는다고?\n"
	.string "그런 건 내 알 바 아냐!\p"
	.string "...라고 말하고 싶지만\n"
	.string "이 몸은 착하니까 맡아주지!$"
	@ なに パソコンに はいりきらない?ｎ
	@ そんなの わがはいが しるか!ｐ
	@ ……と いいたい ところだけどｎ
	@ わがはいは やさしいので あとで やろう!

Route110_TrickHouseEnd_Text_LeavingOnJourney: @ 826B69A
	.string "...... ...... ......\p"
	.string "이 몸은 이제부터\n"
	.string "새로운 아이디어를 찾으러\l"
	.string "여행을 떠날까 해...\l"
	.string "자네도 언젠가 여기 와서\l"
	.string "또 놀다 가도록 해!\p"
	.string "그럼 안녕...!$"
	@ …… …… ……ｐ
	@ わがはいは これからｎ
	@ あらたな しかけを もとめてｌ
	@ たびに でる ことに する……ｌ
	@ あんたも いつか ここにきてｌ
	@ また あそんで いってくれ!ｐ
	@ それでは さらば…!

Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward: @ 826B73D
	.string "좋아 자네에게\n"
	.string "선물을 주지!$"
	@ よしっ あんたにｎ
	@ ほうびを やろう!

Route110_TrickHouseEnd_Text_NoRoomForThis: @ 826B760
	.string "뭣 지닐 수가 없다고?\n"
	.string "뭘 그렇게 많이 들고 있길래?\l"
	.string "뭐 그래도 여기까지 와주었으니까\l"
	.string "상품은 다음에 주도록 하지!$"
	@ なにっ もちきれない?ｎ
	@ そんなに なにを もちあるいてるんだ?ｌ
	@ まあ せっかく ここまで こられたんだしｌ
	@ ほうびは あとで やろう!

Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou: @ 826B7EF
	.string "뭘 그렇게 자신만만해\n"
	.string "이 몸을 완전히 이기려면\l"
	.string "아직 멀었다고!\l"
	.string "앞으로 또 새로운 장치를 만들 테니\l"
	.string "그거나 끝낸 다음에 날 비웃어 봐!\p"
	.string "그럼 다음을 기대하도록!$"
	@ なんだ とくいそうな かお してからにｎ
	@ わがはいに かった きに なるのはｌ
	@ まだ はやいわ!ｌ
	@ このあとも また しかけを つくるからｌ
	@ それが おわってから わがはいを わらえ!ｐ
	@ それでは じかいを おたのしみに!

Route110_TrickHouseEnd_Text_YoureIgnoringMe: @ 826B8BD
	.string "어이어이\n"
	.string "이 몸을 무시하는 거냐고!\l"
	.string "그것참 서러운걸$"
	@ おいおいｎ
	@ わがはいの ことは むし か!ｌ
	@ ずいぶん さみしい じゃないか

