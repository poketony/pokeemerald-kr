.set LOCALID_GRUNT_1, 10
.set LOCALID_GRUNT_2, 11
.set LOCALID_GRUNT_3, 12
.set LOCALID_GRUNT_4, 13
.set LOCALID_MAXIE, 14
.set LOCALID_SCOTT, 16

MossdeepCity_MapScripts:: @ 81E4A96
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_OnTransition
	.byte 0

MossdeepCity_OnTransition: @ 81E4A9C
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

MossdeepCity_EventScript_PokefanF:: @ 81E4AB2
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM08, MossdeepCity_EventScript_PokefanFMagmaGone
	msgbox MossdeepCity_Text_SpaceCenterReceivedLetter, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_PokefanFMagmaGone:: @ 81E4AC7
	msgbox MossdeepCity_Text_SpaceCenterLaunchingRockets, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_Sailor:: @ 81E4AD1
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM08, MossdeepCity_EventScript_SailorMagmaGone
	msgbox MossdeepCity_Text_MossdeepTargetedByMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_SailorMagmaGone:: @ 81E4AE6
	msgbox MossdeepCity_Text_FeelReliefOnLand, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_NinjaBoy:: @ 81E4AF0
	msgbox MossdeepCity_Text_WailmerWatching, MSGBOX_NPC
	end

MossdeepCity_EventScript_ExpertM:: @ 81E4AF9
	msgbox MossdeepCity_Text_LifeNeedsSeaToLive, MSGBOX_NPC
	end

MossdeepCity_EventScript_Girl:: @ 81E4B02
	msgbox MossdeepCity_Text_NiceIfWorldCoveredByFlowers, MSGBOX_NPC
	end

MossdeepCity_EventScript_Woman:: @ 81E4B0B
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock, MSGBOX_NPC
	end

MossdeepCity_EventScript_WhiteRock:: @ 81E4B14
	msgbox MossdeepCity_Text_ItsAWhiteRock, MSGBOX_SIGN
	end

MossdeepCity_EventScript_GymSign:: @ 81E4B1D
	msgbox MossdeepCity_Text_GymSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_CitySign:: @ 81E4B26
	msgbox MossdeepCity_Text_CitySign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_SpaceCenterSign:: @ 81E4B2F
	msgbox MossdeepCity_Text_SpaceCenterSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_VisitedMossdeep:: @ 81E4B38
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setvar VAR_TEMP_1, 1
	end

MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter:: @ 81E4B41
	lockall
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieGestureToSpaceCenter
	waitmovement 0
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_GruntFaceSpaceCenter
	waitmovement 0
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieEnterSpaceCenter
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_Grunt1EnterSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_Grunt2EnterSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_Grunt3EnterSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_Grunt4EnterSpaceCenter
	waitmovement 0
	removeobject LOCALID_MAXIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_GRUNT_4
	delay 30
	setvar VAR_MOSSDEEP_CITY_STATE, 2
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	releaseall
	end

MossdeepCity_Movement_MaxieGestureToSpaceCenter: @ 81E4BAD
	delay_16
	face_right
	delay_16
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_GruntFaceSpaceCenter: @ 81E4BB7
	face_right
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_MaxieEnterSpaceCenter: @ 81E4BBC
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt1EnterSpaceCenter: @ 81E4BCA
	delay_16
	delay_8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt2EnterSpaceCenter: @ 81E4BDD
	delay_16
	delay_8
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt3EnterSpaceCenter: @ 81E4BEF
	delay_16
	delay_8
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt4EnterSpaceCenter: @ 81E4C00
	delay_16
	delay_8
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_EventScript_Man:: @ 81E4C10
	lock
	faceplayer
	msgbox MossdeepCity_Text_SurfExhilarating, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_EventScript_KingsRockBoy:: @ 81E4C26
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_KINGS_ROCK, MossdeepCity_EventScript_ReceivedKingsRock
	msgbox MossdeepCity_Text_WantKingsRockStevenGaveMe, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MossdeepCity_EventScript_DeclineKingsRock
	msgbox MossdeepCity_Text_YouCanKeepIt, MSGBOX_DEFAULT
	giveitem ITEM_KINGS_ROCK
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_KINGS_ROCK
	release
	end

MossdeepCity_EventScript_ReceivedKingsRock:: @ 81E4C68
	msgbox MossdeepCity_Text_StevensHouseOverThere, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_DeclineKingsRock:: @ 81E4C72
	msgbox MossdeepCity_Text_WhatToDoWithWeirdRock, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_BlackBelt:: @ 81E4C7C
	msgbox MossdeepCity_Text_SootopolisNewGymLeader, MSGBOX_NPC
	end

MossdeepCity_EventScript_Scott:: @ 81E4C85
	lock
	faceplayer
	msgbox MossdeepCity_Text_ScottSomethingWrongWithTown, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_NORTH
	call_if_eq MossdeepCity_EventScript_ScottExitNorth
	compare VAR_FACING, DIR_EAST
	call_if_eq MossdeepCity_EventScript_ScottExitEast
	addvar VAR_SCOTT_STATE, 1
	removeobject LOCALID_SCOTT
	release
	end

MossdeepCity_EventScript_ScottExitNorth:: @ 81E4CB0
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitNorth
	waitmovement 0
	return

MossdeepCity_EventScript_ScottExitEast:: @ 81E4CC2
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitEast
	waitmovement 0
	return

MossdeepCity_Movement_PlayerWatchScottExit: @ 81E4CD4
	delay_16
	delay_16
	walk_in_place_fastest_left
	step_end

MossdeepCity_Movement_ScottExitNorth: @ 81E4CD8
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Movement_ScottExitEast: @ 81E4CE2
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Text_WantKingsRockStevenGaveMe: @ 81E4CED
	.string "이거... 성호님한테 받은 건데\n"
	.string "뭔지 잘 모르겠어!\p"
	.string "왕의징표석이라고 하는 거 같은데\n"
	.string "너 가질래?$"
	// これ…… ダイゴさんに もらったけどｎ
	// なんだか よく わかんないや!ｐ
	// おうじゃのしるし って いうらしいけどｎ
	// おまえ ほしい?

MossdeepCity_Text_YouCanKeepIt: @ 81E4D5B
	.string "이걸 가지고 싶어 하다니\n"
	.string "너도 참 별나구나!\p"
	.string "줄 순 있는데 그 대신\n"
	.string "성호님한테는 비밀이야!$"
	// これが ほしいなんてｎ
	// おまえも かわってるよな!ｐ
	// やるけど そのかわりｎ
	// ダイゴさんには ないしょ だぜ!

MossdeepCity_Text_StevensHouseOverThere: @ 81E4DB3
	.string "성호님의 집이라면 바로 저기야!$"
	// ダイゴさんの いえなら すぐそこだよ!

MossdeepCity_Text_WhatToDoWithWeirdRock: @ 81E4DD7
	.string "그치! 이런 이상한 돌을 받아도\n"
	.string "어떻게 해야 할지 모르겠다니까!$"
	// そうだろ! へんてこな いしをｎ
	// もらっても こまっちゃうよな!

MossdeepCity_Text_WailmerWatching: @ 81E4E22
	.string "이 이끼시티 주변에서는\n"
	.string "야생 고래왕자를 볼 수 있어\p"
	.string "그걸 음...\n"
	.string "뭐라고 하더라...\p"
	.string "고래 고래 고래...\p"
	.string "고래왕자 워칭이라고 했었어!$"
	// この トクサネの しゅうへん ではｎ
	// やせいの ホエルコが けんぶつ できるんだｐ
	// そ-いうのを え-と……ｎ
	// なんて いったっけ かな……ｐ
	// ホエ ホエ ホエ……ｐ
	// ホエルコ ウオッチング だ!

MossdeepCity_Text_SpaceCenterReceivedLetter: @ 81E4E90
	.string "섬의 우주센터에는\n"
	.string "엄청난 로켓을 날리고 있는데...\p"
	.string "최근 그곳에\n"
	.string "이상한 편지가 도착해서\l"
	.string "조금 소란이 났었대$"
	// しまの うちゅうセンタ- ではｎ
	// すんごい ロケット とばしとるけど……ｐ
	// さいきん あそこにｎ
	// おかしなてがみ が とどいた とかでｌ
	// ちょっとした さわぎに なっとるのよ

MossdeepCity_Text_SpaceCenterLaunchingRockets: @ 81E4F15
	.string "섬에 있는 우주센터에서는\n"
	.string "엄청난 로켓을 날리고 있어!$"
	// しまの うちゅうセンタ- ではｎ
	// すんごい ロケット とばしとるのよ!

MossdeepCity_Text_MossdeepTargetedByMagma: @ 81E4F50
	.string "선원인 동료로부터 들었는데\n"
	.string "해안시티에 정착해 있던 아쿠아단을\l"
	.string "누군가가 혼내줬나 봐!\p"
	.string "하지만 이쪽 이끼시티는\n"
	.string "마그마단에게 노려지고 있어...\p"
	.string "그 녀석들이 뭘 하려고 하는 건지는\n"
	.string "우주센터에 가면 알 수 있을 거야$"
	// ふなのりの なかまから きいたんだけどｎ
	// ミナモに すみついていた アクアだんｌ
	// だれかが やっつけたんだってな!ｐ
	// でも こっちの トクサネはｎ
	// マグマだんに ねらわれてるんだよ……ｐ
	// あいつらが なにをするき なのかはｎ
	// うちゅうセンタ-に いけば わかるさ

MossdeepCity_Text_FeelReliefOnLand: @ 81E5051
	.string "나는 선원이라서\n"
	.string "역시 바다가 더 좋아!\p"
	.string "그래도 오랜만에 육지에 올라오니\n"
	.string "역시 안심이 되네!$"
	// おれは ふなのり だからｎ
	// やっぱり うみのほうが だいじさ!ｐ
	// でも ひさしぶりに りくに あがるとｎ
	// やっぱり ホッと するんだよな!

MossdeepCity_Text_NiceIfWorldCoveredByFlowers: @ 81E50D9
	.string "전 세계가!\p"
	.string "이 섬처럼 풀과 꽃으로\n"
	.string "가득 차면 좋을 텐데!$"
	// せかいじゅうの すべてが!ｐ
	// このしま みたいに くさばなでｎ
	// いっぱいに なれば いいのにね!

MossdeepCity_Text_LifeNeedsSeaToLive: @ 81E5135
	.string "생명의 근원은 모두 바다에서 태어나\n"
	.string "육지로 올라왔다\p"
	.string "역할을 마친 생명은\n"
	.string "흙이 되어 대지로 돌아가지\p"
	.string "그리고 바다와 대지는\n"
	.string "언제나 이어져 있어...\p"
	.string "그래 저 해안선처럼$"
	// いのちの みなもとは うみから うまれてｎ
	// りくに あがって きたｐ
	// やくめを おえた いのちはｎ
	// つち となって だいちに かえって いくｐ
	// そして うみと だいちはｎ
	// いつでも つながって いる……ｐ
	// そう この かいがんせんの ようにな

MossdeepCity_Text_SurfExhilarating: @ 81E5213
	.string "배 여행도 좋지만 말이지\p"
	.string "포켓몬과 함께 파도타기로\n"
	.string "바다를 이동하면 말로 표현하기 힘든\l"
	.string "상쾌함을 느낄 수 있다네...\p"
	.string "그렇게 생각 안 하나? 젊은이$"
	// ふねのたびも いいけどなｐ
	// ポケモンと ともに なみのりでｎ
	// うみを わたるのは なんとも いえないｌ
	// きもちよさが あるよな……ｐ
	// そう おもわないか? わかものよ

MossdeepCity_Text_SpecialSpaceCenterRock: @ 81E529D
	.string "이 바위는 있지\n"
	.string "우주센터 사람들에게\l"
	.string "정말 소중한 바위야\p"
	.string "로켓이 무사히 날아가길 빌며\n"
	.string "여기에 놓아두었대!\p"
	.string "너는 소원을 이루고 싶을 때\n"
	.string "어떻게 해?\l"
	.string "별똥별을 보고 빌어?\p"
	.string "나라면 역시 큰 종이에\n"
	.string "소원을 적어 놓을 거 같아!$"
	// この いわ ってｎ
	// うちゅうセンタ-の みんなに とってｌ
	// だいじな いわ なのｐ
	// ロケットが ぶじに とぶように ねがってｎ
	// ここに おいたんだって!ｐ
	// あなたは ねがいごとを かなえたいときｎ
	// どうするの?ｌ
	// ながれぼしに ねがうの?ｐ
	// あたしなら たんざくにｎ
	// おねがいごとを かくかな やっぱ!

MossdeepCity_Text_ItsAWhiteRock: @ 81E5396
	.string "하얀 바위다!$"
	// しろい いわ だ!

MossdeepCity_Text_GymSign: @ 81E53A9
	.string "이끼시티 포켓몬체육관\n"
	.string "관장 풍 란\l"
	.string "신비의 콤비네이션!!$"
	// トクサネ シティ ポケモンジムｎ
	// リ-ダ- フウ ランｌ
	// しんぴの コンビネ-ション!!

MossdeepCity_Text_CitySign: @ 81E53F2
	.string "여기는 이끼시티\n"
	.string "신조는 “포켓몬을 소중히!”$"
	// ここは トクサネ シティｎ
	// 「ポケモンを たいせつに!」が あいことば

MossdeepCity_Text_SpaceCenterSign: @ 81E541F
	.string "“이끼 우주센터”\n"
	.string "우주와 가장 가까운 곳$"
	// 「トクサネ うちゅうセンタ-」ｎ
	// うちゅうに いちばん ちかい ばしょ

MossdeepCity_Text_ScottSomethingWrongWithTown: @ 81E5453
	.string "금작화: {PLAYER}{K_AYA} 잘 지냈어?\n"
	.string "나는 잘 지냈지!\p"
	.string "이끼시티의 체육관 관장이\n"
	.string "상당히 강하다고 들어서 말야\l"
	.string "들여다 보려고 와 보니\l"
	.string "마을의 상태가 뭔가 이상해\p"
	.string "예고장이 어떻다든가\n"
	.string "우주센터가 어떻다든가...\p"
	.string "나하고 관계는 없는 것 같지만$"
	// エニシダ『§あ§お げんき?ｎ
	// わたしは げんきさ!ｐ
	// トクサネシティの ジムリ-ダ-がｎ
	// かなり つよいって きいてねｌ
	// のぞいてみようと きて みたらｌ
	// まちの ようすが なんだか ヘンなんだｐ
	// よこくじょうが どうした とかｎ
	// うちゅうセンタ-が どうした とか……ｐ
	// わたしには かんけい なさそうだなあ

MossdeepCity_Text_SootopolisNewGymLeader: @ 81E5581
	.string "아- 발밑이 철렁철렁해서\n"
	.string "기분이 좋군...\p"
	.string "맞다! 철렁철렁하다고 하니\n"
	.string "루네시티에 대해서 말인데\p"
	.string "거기 체육관\n"
	.string "관장이 바뀌었나 봐\p"
	.string "아무래도 윤진님의\n"
	.string "스승님이라는 듯해...$"
	// あ- あしもとが じゃぶじゃぶしてｎ
	// きもちが いい……ｐ
	// そうだ! じゃぶじゃぶ といえばｎ
	// ルネシティ だけどｐ
	// あそこの ジムｎ
	// リ-ダ-が かわった らしいねｐ
	// なんでも ミクリさんのｎ
	// おししょうさん だとか……

