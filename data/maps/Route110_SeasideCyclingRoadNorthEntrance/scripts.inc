Route110_SeasideCyclingRoadNorthEntrance_MapScripts:: @ 826EA77
	.byte 0

Route110_SeasideCyclingRoadNorthEntrance_EventScript_Clerk:: @ 826EA78
	lock
	faceplayer
	msgbox Route110_SeasideCyclingRoadNorthEntrance_Text_GoAllOutOnCyclingRoad, MSGBOX_DEFAULT
	release
	end

Route110_SeasideCyclingRoadNorthEntrance_EventScript_BikeCheck:: @ 826EA84
	lockall
	specialvar VAR_RESULT, GetPlayerAvatarBike
	compare VAR_RESULT, 0
	goto_if_eq Route110_SeasideCyclingRoadNorthEntrance_EventScript_NoBike
	setflag FLAG_SYS_CYCLING_ROAD
	setvar VAR_TEMP_1, 1
	releaseall
	end

Route110_SeasideCyclingRoadNorthEntrance_EventScript_NoBike:: @ 826EA9F
	msgbox Route110_SeasideCyclingRoadNorthEntrance_Text_TooDangerousToWalk, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route110_SeasideCyclingRoadNorthEntrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

Route110_SeasideCyclingRoadNorthEntrance_Movement_PushPlayerBackFromCounter: @ 826EAB4
	walk_left
	step_end

Route110_SeasideCyclingRoadNorthEntrance_EventScript_ClearCyclingRoad:: @ 826EAB6
	lockall
	clearflag FLAG_SYS_CYCLING_ROAD
	setvar VAR_TEMP_1, 0
	releaseall
	end

Route110_SeasideCyclingRoadNorthEntrance_Text_GoAllOutOnCyclingRoad: @ 826EAC1
	.string "사이클링 로드에서는\n"
	.string "마음껏 스피드를 낼 수 있어!\p"
	.string "아무에게도 부딪히지 않고 달리면\n"
	.string "엄청 기분이 좋아!$"
	// サイクリング ロ-ドではｎ
	// おもいっきり スピ-ドを だせるんだ!ｐ
	// だれにも ぶつからずに かけぬけるとｎ
	// すごく きもち いいよ!

Route110_SeasideCyclingRoadNorthEntrance_Text_TooDangerousToWalk: @ 826EB48
	.string "사이클링 로드를\n"
	.string "걸어가는 건 위험해요!\l"
	.string "자전거를 타고 와주세요$"
	// サイクリング ロ-ドをｎ
	// あるいて すすむのは あぶない です!ｌ
	// じてんしゃに のって きてください

