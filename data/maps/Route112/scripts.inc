.set LOCALID_GRUNT_1, 1
.set LOCALID_GRUNT_2, 6

Route112_MapScripts:: @ 81F1DA8
	map_script MAP_SCRIPT_ON_TRANSITION, Route112_OnTransition
	.byte 0

Route112_OnTransition: @ 81F1DAE
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 0
	end

Route112_EventScript_MagmaGrunts:: @ 81F1DB7
	lockall
	delay 40
	applymovement LOCALID_GRUNT_1, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 20
	msgbox Route112_Text_LeaderGoingToAwakenThing, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	delay 40
	applymovement LOCALID_GRUNT_2, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 20
	msgbox Route112_Text_YeahWeNeedMeteorite, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	delay 40
	applymovement LOCALID_GRUNT_1, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 20
	msgbox Route112_Text_OhThatsWhyCrewWentToFallarbor, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	delay 40
	applymovement LOCALID_GRUNT_2, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 20
	msgbox Route112_Text_CantLetAnyonePassUntilTheyreBack, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

Route112_EventScript_MtChimneyCableCarSign:: @ 81F1E46
	msgbox Route112_Text_MtChimneyCableCarSign, MSGBOX_SIGN
	end

Route112_EventScript_MtChimneySign:: @ 81F1E4F
	msgbox Route112_Text_MtChimneySign, MSGBOX_SIGN
	end

Route112_EventScript_RouteSignLavaridge:: @ 81F1E58
	msgbox Route112_Text_RouteSignLavaridge, MSGBOX_SIGN
	end

Route112_EventScript_Hiker:: @ 81F1E61
	msgbox Route112_Text_NotEasyToGetBackToLavaridge, MSGBOX_NPC
	end

Route112_EventScript_Brice:: @ 81F1E6A
	trainerbattle_single TRAINER_BRICE, Route112_Text_BriceIntro, Route112_Text_BriceDefeat
	msgbox Route112_Text_BricePostBattle, MSGBOX_AUTOCLOSE
	end

Route112_EventScript_Trent:: @ 81F1E81
	trainerbattle_single TRAINER_TRENT_1, Route112_Text_TrentIntro, Route112_Text_TrentDefeat, Route112_EventScript_RegisterTrent
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route112_EventScript_RematchTrent
	msgbox Route112_Text_TrentPostBattle, MSGBOX_DEFAULT
	release
	end

Route112_EventScript_RegisterTrent:: @ 81F1EAD
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route112_Text_TrentRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_TRENT_1
	release
	end

Route112_EventScript_RematchTrent:: @ 81F1ECC
	trainerbattle_rematch TRAINER_TRENT_1, Route112_Text_TrentRematchIntro, Route112_Text_TrentRematchDefeat
	msgbox Route112_Text_TrentRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route112_EventScript_Larry:: @ 81F1EE3
	trainerbattle_single TRAINER_LARRY, Route112_Text_LarryIntro, Route112_Text_LarryDefeat
	msgbox Route112_Text_LarryPostBattle, MSGBOX_AUTOCLOSE
	end

Route112_EventScript_Carol:: @ 81F1EFA
	trainerbattle_single TRAINER_CAROL, Route112_Text_CarolIntro, Route112_Text_CarolDefeat
	msgbox Route112_Text_CarolPostBattle, MSGBOX_AUTOCLOSE
	end

Route112_EventScript_Bryant:: @ 81F1F11
	trainerbattle_single TRAINER_BRYANT, Route112_Text_BryantIntro, Route112_Text_BryantDefeat
	msgbox Route112_Text_BryantPostBattle, MSGBOX_AUTOCLOSE
	end

Route112_EventScript_Shayla:: @ 81F1F28
	trainerbattle_single TRAINER_SHAYLA, Route112_Text_ShaylaIntro, Route112_Text_ShaylaDefeat
	msgbox Route112_Text_ShaylaPostBattle, MSGBOX_AUTOCLOSE
	end

Route112_Text_LeaderGoingToAwakenThing: @ 81F1F3F
	.string "이봐 있잖아 리더는 정말로\n"
	.string "그 녀석을 깨울 생각인 거야?$"
	// なあ おい リ-ダ-は ほんとうにｎ
	// アイツを めざめさせる つもりか?

Route112_Text_YeahWeNeedMeteorite: @ 81F1F7A
	.string "그런 것 같던데... 하지만 그러려면\n"
	.string "운석이 필요하다고 했어$"
	// そうらしいな…… だが そのためにはｎ
	// いんせきが ひつよう なんだってよ

Route112_Text_OhThatsWhyCrewWentToFallarbor: @ 81F1FBA
	.string "오호 그래서 방금\n"
	.string "동료가 단풍마을로 간 거구만$"
	// はは-ん それで さっきｎ
	// なかまが ハジツゲに むかったのか

Route112_Text_CantLetAnyonePassUntilTheyreBack: @ 81F2003
	.string "맞아 그 녀석들이 돌아올 때까지는\n"
	.string "아무도 여기를 지나가게 하지 마라!\l"
	.string "라고 했잖아$"
	// ああ かれらが もどってくる まではｎ
	// だれも ここを とおすな! ってよ

Route112_Text_NotEasyToGetBackToLavaridge: @ 81F204E
	.string "끄응... 보라시티로 가고 싶은데...\n"
	.string "이 턱을 내려가면\l"
	.string "용암마을로 돌아가는 게 어렵다고...$"

Route112_Text_MtChimneyCableCarSign: @ 81F20C1
	.string "“굴뚝산 케이블카 승강장”\n"
	.string "{UP_ARROW} 바로 이 앞!$"

Route112_Text_MtChimneySign: @ 81F20ED
	.string "“굴뚝산”\p"
	.string "용암마을이나 정상으로 가려면\n"
	.string "케이블카를 이용해 주십시오$"

Route112_Text_RouteSignLavaridge: @ 81F2138
	.string "여기는 112번 도로\n"
	.string "{LEFT_ARROW} 용암마을$"

