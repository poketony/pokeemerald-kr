.set LOCALID_FOSSIL_MANIAC, 1

Route114_FossilManiacsTunnel_MapScripts:: @ 822AF28
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsTunnel_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route114_FossilManiacsTunnel_OnLoad
	.byte 0

Route114_FossilManiacsTunnel_OnTransition: @ 822AF33
	call_if_set FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac
	end

Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac:: @ 822AF3D
	setobjectxyperm LOCALID_FOSSIL_MANIAC, 6, 5
	setobjectmovementtype LOCALID_FOSSIL_MANIAC, MOVEMENT_TYPE_FACE_DOWN
	return

Route114_FossilManiacsTunnel_OnLoad: @ 822AF49
	call_if_unset FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass
	end

Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass:: @ 822AF53
	setmetatile 6, 1, METATILE_Fallarbor_RedRockWall, 1
	setmetatile 6, 2, METATILE_Fallarbor_RedRockWall, 1
	return

Route114_FossilManiacsTunnel_EventScript_ManiacMentionCaveIn:: @ 822AF66
	lockall
	applymovement LOCALID_FOSSIL_MANIAC, Common_Movement_WalkInPlaceFastestUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox Route114_FossilManiacsTunnel_Text_NotSafeThatWay, MSGBOX_DEFAULT
	setvar VAR_FOSSIL_MANIAC_STATE, 2
	releaseall
	end

Route114_FossilManiacsTunnel_EventScript_FossilManiac:: @ 822AF87
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REVIVED_FOSSIL_MON, Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil
	checkitem ITEM_ROOT_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
	checkitem ITEM_CLAW_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
	msgbox Route114_FossilManiacsTunnel_Text_LookInDesertForFossils, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil:: @ 822AFBC
	msgbox Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil:: @ 822AFC6
	msgbox Route114_FossilManiacsTunnel_Text_FossilsAreWonderful, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_Text_LookInDesertForFossils: @ 822AFD0
	.string "나는 화석마니아...\n"
	.string "화석을 좋아하는 나이스 가이야...\p"
	.string "너도 화석을 가지고 싶니...?\p"
	.string "여기서 발견되는 화석은\n"
	.string "모두 내 거라서 줄 수가 없어...\p"
	.string "어떻게든 가지고 싶으면\n"
	.string "화석이 있을 만한\l"
	.string "바위나 모래가 많은 사막에라도\l"
	.string "가보도록 해...$"
	// ぼく かせきマニア……ｎ
	// かせき だいすき ナイスガイ さ……ｐ
	// きみも カセキが ほしいの……?ｐ
	// ここで みつかる カセキはｎ
	// ぜんぶ ぼくの ものだから あげないよ……ｐ
	// どうしても ほしければｎ
	// カセキの みつかりそうなｌ
	// いわや すなが おおい さばくでもｌ
	// さがして みなよ……

Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils: @ 822B0D6
	.string "너도 화석을 발견했구나...\n"
	.string "멋져... 나도 모르게\l"
	.string "멍하니 바라보게 돼...\p"
	.string "너 그 화석 어떻게 할 거니...?\p"
	.string "내가 들은 이야기로는 데봉에서\n"
	.string "화석을 포켓몬으로 부활시키는\l"
	.string "연구를 하고 있대...\p"
	.string "나는 화석이 더 좋으니까\n"
	.string "그런 건 안 할 거지만...$"
	// きみも カセキを みつけたんだね……ｎ
	// すてき…… うっとり しちゃうよ……ｐ
	// きみ その カセキ どうするの……?ｐ
	// きいた はなしでは デボンではｎ
	// カセキを ポケモンに いきかえらせるｌ
	// けんきゅうを している そうだよ……ｐ
	// ぼくは カセキが すきだからｎ
	// そんなこと しないけどね……

Route114_FossilManiacsTunnel_Text_FossilsAreWonderful: @ 822B1CC
	.string "화석은...\n"
	.string "정말 멋져...\l"
	.string "넋을 놓고 바라보게 돼...$"
	// カセキって……ｎ
	// すてき…… うっとり しちゃうよ……

Route114_FossilManiacsTunnel_Text_NotSafeThatWay: @ 822B1F7
	.string "아...\n"
	.string "그쪽으로 가면 위험해...\p"
	.string "계속 팠더니\n"
	.string "벽이 무너져 버렸거든...\p"
	.string "아래쪽에 커다란 동혈이\n"
	.string "있나 봐...\l"
	.string "화석도 없을 것 같으니까\l"
	.string "그대로 놔두려고 해...$"
	// あ……ｎ
	// そっちに いくと あぶないよ……ｐ
	// ほりまくって いたらｎ
	// カベが くずれて しまったんだ……ｐ
	// したに おおきな くうどうがｎ
	// あるみたい だけど……ｌ
	// カセキも なさそう だからｌ
	// そのままに してあるんだ……

