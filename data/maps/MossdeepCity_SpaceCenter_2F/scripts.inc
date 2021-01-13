.set LOCALID_RICH_BOY, 1
.set LOCALID_GENTLEMAN, 2
.set LOCALID_SCIENTIST, 3
.set LOCALID_STEVEN, 4
@ Grunt names numbered like their Trainer values (which are for the full Space Center)
.set LOCALID_GRUNT_6, 5
.set LOCALID_GRUNT_5, 6
.set LOCALID_GRUNT_7, 7
.set LOCALID_TABITHA, 8
.set LOCALID_MAXIE, 9

MossdeepCity_SpaceCenter_2F_MapScripts:: @ 8223D58
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_SpaceCenter_2F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MossdeepCity_SpaceCenter_2F_OnFrame
	.byte 0

MossdeepCity_SpaceCenter_2F_OnTransition: @ 8223D63
	compare VAR_MOSSDEEP_CITY_STATE, 2
	call_if_eq MossdeepCity_SpaceCenter_2F_EventScript_MoveCivilians
	compare VAR_MOSSDEEP_SPACE_CENTER_STATE, 2
	call_if_eq MossdeepCity_SpaceCenter_2F_EventScript_MoveDefeatedGrunts
	end

MossdeepCity_SpaceCenter_2F_EventScript_MoveCivilians:: @ 8223D7A
	clearflag FLAG_INTERACTED_WITH_STEVEN_SPACE_CENTER
	setobjectxyperm LOCALID_SCIENTIST, 5, 3
	setobjectmovementtype LOCALID_SCIENTIST, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_RICH_BOY, 3, 2
	setobjectmovementtype LOCALID_RICH_BOY, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_GENTLEMAN, 1, 3
	setobjectmovementtype LOCALID_GENTLEMAN, MOVEMENT_TYPE_FACE_RIGHT
	return

MossdeepCity_SpaceCenter_2F_EventScript_MoveDefeatedGrunts:: @ 8223D9F
	setobjectxyperm LOCALID_GRUNT_6, 11, 2
	setobjectxyperm LOCALID_GRUNT_7, 15, 2
	setobjectxyperm LOCALID_GRUNT_5, 13, 4
	return

MossdeepCity_SpaceCenter_2F_OnFrame: @ 8223DB5
	map_script_2 VAR_MOSSDEEP_SPACE_CENTER_STATE, 1, MossdeepCity_SpaceCenter_2F_EventScript_ThreeMagmaGrunts
	.2byte 0

MossdeepCity_SpaceCenter_2F_EventScript_ThreeMagmaGrunts:: @ 8223DBF
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	msgbox MossdeepCity_SpaceCenter_2F_Text_YoureOutnumberedTakeUsOn, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_BattleThreeMagmaGrunts
	msgbox MossdeepCity_SpaceCenter_2F_Text_GoodAnswer, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_SpaceCenter_2F_Movement_PlayerExit
	waitmovement 0
	warp MAP_MOSSDEEP_CITY_SPACE_CENTER_1F, 255, 13, 1
	waitstate
	releaseall
	end

MossdeepCity_SpaceCenter_2F_Movement_PlayerExit: @ 8223E07
	walk_up
	step_end

MossdeepCity_SpaceCenter_2F_EventScript_BattleThreeMagmaGrunts:: @ 8223E09
	msgbox MossdeepCity_SpaceCenter_2F_Text_Grunt5Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_SPACE_CENTER_5, MossdeepCity_SpaceCenter_2F_Text_Grunt5Defeat
	applymovement LOCALID_GRUNT_5, MossdeepCity_SpaceCenter_2F_Movement_Grunt5Defeated
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox MossdeepCity_SpaceCenter_2F_Text_Grunt6Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_SPACE_CENTER_6, MossdeepCity_SpaceCenter_2F_Text_Grunt6Defeat
	applymovement LOCALID_GRUNT_6, MossdeepCity_SpaceCenter_2F_Movement_Grunt6Defeated
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox MossdeepCity_SpaceCenter_2F_Text_Grunt7Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_SPACE_CENTER_7, MossdeepCity_SpaceCenter_2F_Text_Grunt7Defeat
	applymovement LOCALID_GRUNT_7, MossdeepCity_SpaceCenter_2F_Movement_Grunt7Defeated
	waitmovement 0
	setvar VAR_MOSSDEEP_SPACE_CENTER_STATE, 2
	copyobjectxytoperm LOCALID_GRUNT_6
	copyobjectxytoperm LOCALID_GRUNT_7
	copyobjectxytoperm LOCALID_GRUNT_5
	releaseall
	end

MossdeepCity_SpaceCenter_2F_Movement_Grunt6Defeated: @ 8223E81
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

MossdeepCity_SpaceCenter_2F_Movement_Grunt5Defeated: @ 8223E85
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

MossdeepCity_SpaceCenter_2F_Movement_Grunt7Defeated: @ 8223E89
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

MossdeepCity_SpaceCenter_2F_EventScript_Scientist:: @ 8223E8D
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_SpaceCenter_2F_EventScript_ScientistNormal
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_ScientistMagma
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_lt MossdeepCity_SpaceCenter_2F_EventScript_ScientistNormal
	goto MossdeepCity_SpaceCenter_2F_EventScript_ScientistMagma
	end

MossdeepCity_SpaceCenter_2F_EventScript_ScientistNormal:: @ 8223EB4
	msgbox MossdeepCity_SpaceCenter_2F_Text_MossdeepIdealForRockets, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_2F_EventScript_ScientistMagma:: @ 8223EBE
	msgbox MossdeepCity_SpaceCenter_2F_Text_WhyWouldMagmaStealRocketFuel, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_2F_EventScript_Gentleman:: @ 8223EC8
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_SpaceCenter_2F_EventScript_GentlemanNormal
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_GentlemanMagma
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_lt MossdeepCity_SpaceCenter_2F_EventScript_GentlemanNormal
	goto MossdeepCity_SpaceCenter_2F_EventScript_GentlemanMagma
	end

MossdeepCity_SpaceCenter_2F_EventScript_GentlemanNormal:: @ 8223EEF
	msgbox MossdeepCity_SpaceCenter_2F_Text_WouldveLikedToBeAstronaut, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_2F_EventScript_GentlemanMagma:: @ 8223EF9
	msgbox MossdeepCity_SpaceCenter_2F_Text_MagmaCantGetAwayWithThis, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_2F_EventScript_RichBoy:: @ 8223F03
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_SpaceCenter_2F_EventScript_RichBoyNormal
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_RichBoyMagma
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_lt MossdeepCity_SpaceCenter_2F_EventScript_RichBoyNormal
	goto MossdeepCity_SpaceCenter_2F_EventScript_RichBoyMagma
	end

MossdeepCity_SpaceCenter_2F_EventScript_RichBoyNormal:: @ 8223F2A
	msgbox MossdeepCity_SpaceCenter_2F_Text_WishOrdinaryPeopleCouldGoIntoSpace, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_2F_EventScript_RichBoyMagma:: @ 8223F34
	msgbox MossdeepCity_SpaceCenter_2F_Text_DoesMagmaWantToGoToSpace, MSGBOX_DEFAULT
	release
	end

@ Battle for the below 3 grunts is handled in MossdeepCity_SpaceCenter_2F_EventScript_BattleThreeMagmaGrunts
MossdeepCity_SpaceCenter_2F_EventScript_Grunt6:: @ 8223F3E
	msgbox MossdeepCity_SpaceCenter_2F_Text_Grunt6PostBattle, MSGBOX_NPC
	end

MossdeepCity_SpaceCenter_2F_EventScript_Grunt7:: @ 8223F47
	msgbox MossdeepCity_SpaceCenter_2F_Text_Grunt7PostBattle, MSGBOX_NPC
	end

MossdeepCity_SpaceCenter_2F_EventScript_Grunt5:: @ 8223F50
	msgbox MossdeepCity_SpaceCenter_2F_Text_Grunt5PostBattle, MSGBOX_NPC
	end

MossdeepCity_SpaceCenter_2F_EventScript_Tabitha:: @ 8223F59
	lock
	faceplayer
	msgbox MossdeepCity_SpaceCenter_2F_Text_WellTakeCareOfYou, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_2F_EventScript_Maxie:: @ 8223F6F
	lockall
	msgbox MossdeepCity_SpaceCenter_2F_Text_MaxieDontInterfere, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_SpaceCenter_2F_EventScript_Steven:: @ 8223F7A
	lockall
	goto_if_set FLAG_INTERACTED_WITH_STEVEN_SPACE_CENTER, MossdeepCity_SpaceCenter_2F_EventScript_ReadyForBattlePrompt
	setflag FLAG_INTERACTED_WITH_STEVEN_SPACE_CENTER
	msgbox MossdeepCity_SpaceCenter_2F_Text_StevenWhyStealRocketFuel, MSGBOX_DEFAULT
	msgbox MossdeepCity_SpaceCenter_2F_Text_MaxieUseFuelToEruptVolcano, MSGBOX_DEFAULT
	closemessage
	delay 30
	playse SE_NOT_EFFECTIVE
	switch VAR_FACING
	case DIR_SOUTH, MossdeepCity_SpaceCenter_2F_EventScript_StevenFightMovementSouth
	applymovement LOCALID_STEVEN, MossdeepCity_SpaceCenter_2F_Movement_StevenFight
	waitmovement 0
	releaseall
	end

MossdeepCity_SpaceCenter_2F_EventScript_StevenFightMovementSouth:: @ 8223FBA
	applymovement LOCALID_STEVEN, MossdeepCity_SpaceCenter_2F_Movement_StevenFightSouth
	waitmovement 0
	releaseall
	end

MossdeepCity_SpaceCenter_2F_Movement_StevenFight: @ 8223FC6
	lock_facing_direction
	walk_fast_up
	walk_fast_up
	unlock_facing_direction
	delay_16
	delay_16
	walk_slow_down
	walk_slow_down
	step_end

MossdeepCity_SpaceCenter_2F_Movement_StevenFightSouth: @ 8223FCF
	face_left
	lock_facing_direction
	walk_fast_right
	walk_fast_right
	unlock_facing_direction
	delay_16
	delay_16
	walk_slow_left
	walk_slow_left
	face_down
	step_end

MossdeepCity_SpaceCenter_2F_EventScript_ReadyForBattlePrompt:: @ 8223FDA
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MossdeepCity_SpaceCenter_2F_Text_StevenAreYouReadyToBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MossdeepCity_SpaceCenter_2F_EventScript_ChoosePartyForMultiBattle
	msgbox MossdeepCity_SpaceCenter_2F_Text_StevenHurryGetReadyQuickly, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	releaseall
	end

MossdeepCity_SpaceCenter_2F_EventScript_ChoosePartyForMultiBattle:: @ 822400C
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	waitstate
	compare VAR_RESULT, 0
	goto_if_ne MossdeepCity_SpaceCenter_2F_EventScript_DoStevenMultiBattle
	special LoadPlayerParty
	goto MossdeepCity_SpaceCenter_2F_EventScript_ReadyForBattlePrompt

MossdeepCity_SpaceCenter_2F_EventScript_DoStevenMultiBattle:: @ 8224032
	special ReducePlayerPartyToSelectedMons
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	setvar VAR_0x8004, SPECIAL_BATTLE_STEVEN
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	frontier_saveparty
	special LoadPlayerParty
	switch VAR_RESULT
	case 1, MossdeepCity_SpaceCenter_2F_EventScript_DefeatedMaxieTabitha
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	waitstate

MossdeepCity_SpaceCenter_2F_EventScript_DefeatedMaxieTabitha:: @ 8224071
	msgbox MossdeepCity_SpaceCenter_2F_Text_MaxieWeFailedIsAquaAlsoMisguided, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement LOCALID_MAXIE, Common_Movement_WalkInPlaceFastestLeft
	applymovement LOCALID_TABITHA, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 60
	applymovement LOCALID_MAXIE, Common_Movement_WalkInPlaceFastestUp
	applymovement LOCALID_TABITHA, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 20
	msgbox MossdeepCity_SpaceCenter_2F_Text_MaxieWeWillGiveUp, MSGBOX_DEFAULT
	closemessage
	setvar VAR_MOSSDEEP_CITY_STATE, 3
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	setvar VAR_MOSSDEEP_SPACE_CENTER_STATE, 3
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_TEAM_MAGMA
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_TEAM_MAGMA
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	removeobject LOCALID_GRUNT_6
	removeobject LOCALID_GRUNT_7
	removeobject LOCALID_GRUNT_5
	removeobject LOCALID_TABITHA
	removeobject LOCALID_MAXIE
	setobjectxy LOCALID_SCIENTIST, 5, 6
	turnobject LOCALID_SCIENTIST, DIR_SOUTH
	setobjectxy LOCALID_GENTLEMAN, 11, 8
	turnobject LOCALID_GENTLEMAN, DIR_NORTH
	setobjectxy LOCALID_RICH_BOY, 6, 2
	turnobject LOCALID_RICH_BOY, DIR_NORTH
	call MossdeepCity_SpaceCenter_2F_EventScript_StevenFacePlayer
	fadescreen FADE_FROM_BLACK
	msgbox MossdeepCity_SpaceCenter_2F_Text_StevenThankYouComeSeeMeAtHome, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_DEFEATED_MAGMA_SPACE_CENTER
	setflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_STEVEN
	removeobject LOCALID_STEVEN
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_MAGMA_NOTE
	clearflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_STEVEN
	setvar VAR_STEVENS_HOUSE_STATE, 1
	setflag FLAG_HIDE_MOSSDEEP_CITY_SCOTT
	removeobject LOCALID_SCIENTIST
	setobjectxyperm LOCALID_SCIENTIST, 5, 6
	setobjectmovementtype LOCALID_SCIENTIST, MOVEMENT_TYPE_WANDER_AROUND
	addobject LOCALID_SCIENTIST
	fadescreen FADE_FROM_BLACK
	end

MossdeepCity_SpaceCenter_2F_EventScript_StevenFacePlayer:: @ 8224131
	switch VAR_FACING
	case DIR_SOUTH, MossdeepCity_SpaceCenter_2F_EventScript_StevenFacePlayerSouth
	case DIR_WEST, MossdeepCity_SpaceCenter_2F_EventScript_StevenFacePlayerWest
	return

MossdeepCity_SpaceCenter_2F_EventScript_StevenFacePlayerSouth:: @ 822414D
	turnobject LOCALID_STEVEN, DIR_NORTH
	return

MossdeepCity_SpaceCenter_2F_EventScript_StevenFacePlayerWest:: @ 8224152
	turnobject LOCALID_STEVEN, DIR_EAST
	return

MossdeepCity_SpaceCenter_2F_EventScript_MaxieTrainer:: @ 8224157
	trainerbattle TRAINER_BATTLE_SET_TRAINER_A, TRAINER_MAXIE_MOSSDEEP, 0, MossdeepCity_SpaceCenter_2F_Text_JustWantToExpandLand, MossdeepCity_SpaceCenter_2F_Text_JustWantToExpandLand
	end

MossdeepCity_SpaceCenter_2F_EventScript_TabithaTrainer:: @ 8224166
	trainerbattle TRAINER_BATTLE_SET_TRAINER_B, TRAINER_TABITHA_MOSSDEEP, 0, MossdeepCity_SpaceCenter_Text_TabithaDefeat, MossdeepCity_SpaceCenter_Text_TabithaDefeat
	end

MossdeepCity_SpaceCenter_2F_EventScript_RivalRayquazaCall:: @ 8224175
	lockall
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq MossdeepCity_SpaceCenter_2F_EventScript_MayRayquazaCall
	compare VAR_RESULT, FEMALE
	call_if_eq MossdeepCity_SpaceCenter_2F_EventScript_BrendanRayquazaCall
	closemessage
	clearflag FLAG_DEFEATED_MAGMA_SPACE_CENTER
	releaseall
	end

MossdeepCity_SpaceCenter_2F_EventScript_MayRayquazaCall:: @ 8224193
	pokenavcall MatchCall_Text_MayRayquazaCall
	waitmessage
	return

MossdeepCity_SpaceCenter_2F_EventScript_BrendanRayquazaCall:: @ 822419A
	pokenavcall MatchCall_Text_BrendanRayquazaCall
	waitmessage
	return

MossdeepCity_SpaceCenter_2F_Text_MossdeepIdealForRockets: @ 82241A1
	.string "이끼시티는 날씨가 좋은 날이 많고\n"
	.string "바람의 방향도 안정적이지\p"
	.string "로켓을 쏘아 올리기에\n"
	.string "안성맞춤인 장소로군$"

MossdeepCity_SpaceCenter_2F_Text_WhyWouldMagmaStealRocketFuel: @ 822420C
	.string "로켓의 연료 같은 걸 빼앗아서\n"
	.string "마그마단은 뭘 할 셈이지?$"
	// ロケットの ねんりょうなんか うばってｎ
	// マグマだんは なにする つもりだ!?

MossdeepCity_SpaceCenter_2F_Text_WouldveLikedToBeAstronaut: @ 8224253
	.string "나도 조금만 더 젊었더라면\n"
	.string "우주 비행사를 꿈꿔 볼 텐데...\p"
	.string "아니지 지금부터라도 늦지 않아!\n"
	.string "좋-아 힘내자-!!$"

MossdeepCity_SpaceCenter_2F_Text_MagmaCantGetAwayWithThis: @ 82242C5
	.string "마그마단한테 연료를 빼앗기면\n"
	.string "내가 우주에 갈 수 없게 된다!\p"
	.string "그렇게 놔둘까 보냐-!$"
	// マグマだんに ねんりょうを うばわれたらｎ
	// わしが うちゅうに いけなくなる!ｐ
	// そんなこと させて たまるか-!

MossdeepCity_SpaceCenter_2F_Text_WishOrdinaryPeopleCouldGoIntoSpace: @ 8224342
	.string "언젠가 평범한 사람들도\n"
	.string "우주에 갈 수 있게 되면 좋겠다...$"

MossdeepCity_SpaceCenter_2F_Text_DoesMagmaWantToGoToSpace: @ 8224376
	.string "마그마단...\n"
	.string "우주에 가고 싶어하는 걸까?$"
	// マグマだんも……ｎ
	// うちゅうに いきたいの かな?

MossdeepCity_SpaceCenter_2F_Text_YoureOutnumberedTakeUsOn: @ 82243A4
	.string "뭐야 너!\p"
	.string "우리 3명한테 둘러싸여 있으면서\n"
	.string "해보자는 거냐?!$"
	// なんだ おまえ!ｐ
	// おれたち 3にんに かこまれてるのにｎ
	// やろうってのか!?

MossdeepCity_SpaceCenter_2F_Text_GoodAnswer: @ 82243FE
	.string "그렇지!\n"
	.string "그래야 착한 아이지!$"
	// だよな!ｎ
	// そのほうが おりこうさん だぜ!

MossdeepCity_SpaceCenter_2F_Text_Grunt5Intro: @ 822442D
	.string "무모한 녀석...\n"
	.string "그럼 나부터 간다!$"
	// むてっぽうな やつめ……ｎ
	// まずは オレからだ!

MossdeepCity_SpaceCenter_2F_Text_Grunt5Defeat: @ 8224461
	.string "난 졌어 하지만!$"
	// オレは まけたが しかし!

MossdeepCity_SpaceCenter_2F_Text_Grunt6Intro: @ 822446E
	.string "아직 안심하긴 일러\n"
	.string "다음 상대는 나다!$"
	// あんしん するのは まだ はやいｎ
	// つぎは オレが あいてだ!

MossdeepCity_SpaceCenter_2F_Text_Grunt6Defeat: @ 8224499
	.string "난 졌어 그치만!$"
	// オレも まけたが だけど!

MossdeepCity_SpaceCenter_2F_Text_Grunt7Intro: @ 82244AB
	.string "한숨 돌리고 싶을 테지만\n"
	.string "그렇게 놔두진 않겠어!$"
	// ひとやすみ したいだろう けどｎ
	// そんな わけには いきませ-ん!

MossdeepCity_SpaceCenter_2F_Text_Grunt7Defeat: @ 82244F1
	.string "우리들이 한숨을\n"
	.string "돌렸어야... 했는데...$"
	// オレたちが ひとやすみｎ
	// しておけば…… よかった……

MossdeepCity_SpaceCenter_2F_Text_Grunt6PostBattle: @ 822452C
	.string "3명이서 덤볐는데 이 꼴이라니!$"
	// 3にんも いて このザマか!

MossdeepCity_SpaceCenter_2F_Text_Grunt7PostBattle: @ 8224570
	.string "3명이서 지면\n"
	.string "부끄러움도 3배!$"
	// 3にんがかりで まけるとｎ
	// いつもの 3ばい かっこわるいぜ!

MossdeepCity_SpaceCenter_2F_Text_Grunt5PostBattle: @ 82245AF
	.string "우리들의 리더에\n"
	.string "어울릴 거 같은데...?$"
	// オレたち リ-ダ-のｎ
	// やくに たってるのかな……?

MossdeepCity_SpaceCenter_2F_Text_WellTakeCareOfYou: @ 82245D9
	.string "우효효! 모처럼\n"
	.string "연료를 가지러 왔는데\l"
	.string "방해가 들어왔군!\p"
	.string "너도 우리들을 방해하겠다면\n"
	.string "같이 정리해 주마!$"
	// ウヒョヒョ! せっかくｎ
	// ねんりょうを いただきに きたのにｌ
	// ジャマが はいっちまった!ｐ
	// おまえも オレたちの ジャマを するならｎ
	// いっしょに かたづけて やろうか!

MossdeepCity_SpaceCenter_2F_Text_MaxieDontInterfere: @ 822467B
	.string "마적! 에-잇 거기를 비켜라!\n"
	.string "우리들을 방해하지 말란 말이다!$"
	// マツブサ『え-い そこをどけ!ｎ
	// われわれの ジャマを するんじゃない!

MossdeepCity_SpaceCenter_2F_Text_StevenWhyStealRocketFuel: @ 82246B2
	.string "성호: 마그마단...\n"
	.string "로켓의 연료를 훔쳐서\l"
	.string "대체 뭘 할 셈이야!$"
	// ダイゴ『マグマだん……ｎ
	// ロケットの ねんりょうなんか ぬすんでｌ
	// いったい なにをする つもりなんだ!

MossdeepCity_SpaceCenter_2F_Text_MaxieUseFuelToEruptVolcano: @ 82246F0
	.string "마적: 후후후...\n"
	.string "그렇게 알고 싶다면 가르쳐주지\p"
	.string "굴뚝산의 분화구에\n"
	.string "전부 쏟아넣을 것이다!\p"
	.string "그란돈도 사라져버렸고\n"
	.string "이제 그런 산에 볼일은 없지\p"
	.string "그러니 연료의 힘을 이용해서\n"
	.string "화산을 분화시킬 것이다\l"
	.string "콰과광 하고 말이다!$"
	// マツブサ『ふふふ……ｎ
	// そんなに しりたけりゃ おしえてやろうｐ
	// えんとつやまの かこうにｎ
	// ぜんぶ なげこんで やるのさ!ｐ
	// グラ-ドンも きえてしまった ことだしｎ
	// もう あんなやまに ようはないｐ
	// だから ねんりょうの ちからを りようしてｎ
	// かざんを ふんか させて やるのさｌ
	// ズドド-ン とな!

MossdeepCity_SpaceCenter_2F_Text_StevenAreYouReadyToBattle: @ 82247FF
	.string "성호: {PLAYER}!\n"
	.string "힘을 빌려줄 수 있어?!\p"
	.string "나와 함께 싸우자!\n"
	.string "준비는 됐어?$"
	// ダイゴ『§あ§お!ｎ
	// ちからを かして くれるのかい!?ｐ
	// ボクと いっしょに たたかおう!ｎ
	// じゅんびは いいね?

MossdeepCity_SpaceCenter_2F_Text_StevenHurryGetReadyQuickly: @ 8224854
	.string "성호: 그럼 서둘러\n"
	.string "준비를 해줘!$"
	// ダイゴ『じゃあ いそいでｎ
	// じゅんびを ととのえて くるんだ!

MossdeepCity_SpaceCenter_2F_Text_JustWantToExpandLand: @ 822487C
	.string "나는 단지...\n"
	.string "땅을 넓히고 싶을 뿐이었는데...$"
	// わたしは ただ……ｎ
	// りくちを ふやしたい だけなのに……

MossdeepCity_SpaceCenter_Text_TabithaDefeat: @ 82248AD
	.string "동감입니다...$"
	// みぎに おなじ だ……

MossdeepCity_SpaceCenter_2F_Text_MaxieWeFailedIsAquaAlsoMisguided: @ 82248C2
	.string "마적: 우리들은 화산을\n"
	.string "분화시키지 못했다...\p"
	.string "잠에서 깨어난 그란돈도\n"
	.string "컨트롤하지 못했다...\p"
	.string "땅을 넓히려는 생각은\n"
	.string "잘못되었다는 말인가?\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "만약... 우리 마그마단이\n"
	.string "잘못되었다고 한다면\l"
	.string "...... ...... ......\p"
	.string "설마 아쿠아단의\n"
	.string "바다를 넓히려는 생각도...$"
	// マツブサ『われわれは かざんをｎ
	// ふんか させられ なかった……ｐ
	// ねむりから めざめた グラ-ドンもｎ
	// コントロ-ル できなかった……ｐ
	// りくちをふやす という かんがえはｎ
	// まちがって いるのか?ｐ
	// …… …… ……ｎ
	// …… …… ……ｐ
	// もしも…… われわれ マグマだんがｎ
	// まちがっていると いうのならｌ
	// …… …… ……ｐ
	// まさか アクアだんのｎ
	// うみをふやす という かんがえも……

MossdeepCity_SpaceCenter_2F_Text_MaxieWeWillGiveUp: @ 82249DC
	.string "마적: 알았다...\n"
	.string "연료는 포기하지...\p"
	.string "나에게는 따로 확인해야만\n"
	.string "하는 일이 있으니까 말이다...$"
	// マツブサ『わかった……ｎ
	// ねんりょうは あきらめよう……ｐ
	// わたしには ほかに たしかめ なければｎ
	// ならない ことが あるようだ……

MossdeepCity_SpaceCenter_2F_Text_StevenThankYouComeSeeMeAtHome: @ 8224A4A
	.string "성호: 휴우 위험했어\n"
	.string "고마워 {PLAYER}\p"
	.string "힘을 빌려준 보답으로\n"
	.string "좋은 걸 선물할게\l"
	.string "나중에 집으로 와줘\p"
	.string "내 집은 금탄도시가 아니라\n"
	.string "이 섬에 있어$"
	// ダイゴ『ふう あぶない ところ だったｎ
	// §あ§お ありがとうｐ
	// ちからを かしてくれた おれいにｎ
	// いいものを あげるからｌ
	// あとで いえまで きておくれｐ
	// ボクのいえは カナズミ じゃないよｎ
	// このしまに あるんだ
