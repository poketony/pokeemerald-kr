Route110_SeasideCyclingRoadSouthEntrance_MapScripts:: @ 826EBA1
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_SeasideCyclingRoadSouthEntrance_OnTransition
	.byte 0

Route110_SeasideCyclingRoadSouthEntrance_OnTransition: @ 826EBA7
	compare VAR_CYCLING_CHALLENGE_STATE, 3
	call_if_eq Route110_SeasideCyclingRoadSouthEntrance_EventScript_RestartChallenge
	compare VAR_CYCLING_CHALLENGE_STATE, 2
	call_if_eq Route110_SeasideCyclingRoadSouthEntrance_EventScript_RestartChallenge
	end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_RestartChallenge:: @ 826EBBE
	setvar VAR_CYCLING_CHALLENGE_STATE, 1
	return

Route110_SeasideCyclingRoadSouthEntrance_EventScript_Clerk:: @ 826EBC4
	lock
	faceplayer
	msgbox Route110_SeasideCyclingRoadSouthEntrance_Text_GoAllOutOnCyclingRoad, MSGBOX_DEFAULT
	release
	end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_BikeCheck:: @ 826EBD0
	lockall
	specialvar VAR_RESULT, GetPlayerAvatarBike
	compare VAR_RESULT, 2
	call_if_eq Route110_SeasideCyclingRoadSouthEntrance_EventScript_OnMachBike
	compare VAR_RESULT, 0
	goto_if_eq Route110_SeasideCyclingRoadSouthEntrance_EventScript_NoBike
	setflag FLAG_SYS_CYCLING_ROAD
	setvar VAR_TEMP_1, 1
	releaseall
	end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_OnMachBike:: @ 826EBF6
	setvar VAR_CYCLING_CHALLENGE_STATE, 1
	return

Route110_SeasideCyclingRoadSouthEntrance_EventScript_NoBike:: @ 826EBFC
	msgbox Route110_SeasideCyclingRoadSouthEntrance_Text_TooDangerousToWalk, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route110_SeasideCyclingRoadSouthEntrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

Route110_SeasideCyclingRoadSouthEntrance_Movement_PushPlayerBackFromCounter: @ 826EC11
	walk_left
	step_end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_ClearCyclingRoad:: @ 826EC13
	lockall
	setvar VAR_CYCLING_CHALLENGE_STATE, 0
	clearflag FLAG_SYS_CYCLING_ROAD
	setvar VAR_TEMP_1, 0
	releaseall
	end

Route110_SeasideCyclingRoadSouthEntrance_Text_GoAllOutOnCyclingRoad: @ 826EC23
	.string "사이클링 로드에서는\n"
	.string "마음껏 스피드를 낼 수 있어!\p"
	.string "아무에게도 부딪히지 않고 달리면\n"
	.string "엄청 기분이 좋아!$"
	// サイクリング ロ-ドではｎ
	// おもいっきり スピ-ドを だせるんだ!ｐ
	// だれにも ぶつからずに かけぬけるとｎ
	// すごく きもち いいよ!

Route110_SeasideCyclingRoadSouthEntrance_Text_TooDangerousToWalk: @ 826ECAA
	.string "사이클링 로드를\n"
	.string "걸어가는 건 위험해요!\l"
	.string "자전거를 타고 와주세요$"
	// サイクリング ロ-ドをｎ
	// あるいて すすむのは あぶない です!ｌ
	// じてんしゃに のって きてください

