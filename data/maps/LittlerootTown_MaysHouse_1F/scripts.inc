.set LOCALID_MOM, 1
.set LOCALID_RIVAL_MOM, 4
.set LOCALID_RIVAL, 7

LittlerootTown_MaysHouse_1F_MapScripts:: @ 81F88A5
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_MaysHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_MaysHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_MaysHouse_1F_OnFrame
	.byte 0

LittlerootTown_MaysHouse_1F_OnLoad: @ 81F88B5
	compare VAR_LITTLEROOT_INTRO_STATE, 6
	call_if_lt LittlerootTown_MaysHouse_1F_EventScript_SetMovingBoxes
	call_if_set FLAG_RECEIVED_RUNNING_SHOES, LittlerootTown_MaysHouse_1F_EventScript_CheckShowShoesManual
	end

LittlerootTown_MaysHouse_1F_EventScript_SetMovingBoxes:: @ 81F88CA
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, 1
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, 1
	return

LittlerootTown_MaysHouse_1F_EventScript_CheckShowShoesManual:: @ 81F88DD
	checkplayergender
	compare VAR_RESULT, FEMALE
	goto_if_eq LittlerootTown_MaysHouse_1F_EventScript_ShowRunningShoesManual
	return

LittlerootTown_MaysHouse_1F_EventScript_ShowRunningShoesManual:: @ 81F88EA
	setmetatile 6, 7, METATILE_BrendansMaysHouse_BookOnTable, 1
	return

LittlerootTown_MaysHouse_1F_OnTransition: @ 81F88F4
	compare VAR_LITTLEROOT_INTRO_STATE, 3
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MoveMomToDoor
	compare VAR_LITTLEROOT_INTRO_STATE, 5
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MoveMomToStairs
	compare VAR_LITTLEROOT_INTRO_STATE, 6
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MoveMomToTV
	end

LittlerootTown_MaysHouse_1F_EventScript_MoveMomToStairs:: @ 81F8916
	setobjectxyperm LOCALID_MOM, 2, 4
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_MaysHouse_1F_EventScript_MoveMomToTV:: @ 81F8922
	setobjectxyperm LOCALID_MOM, 6, 5
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_MaysHouse_1F_EventScript_MoveMomToDoor:: @ 81F892E
	setobjectxyperm LOCALID_MOM, 1, 8
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

@ Many of the below scripts have no gender check because they assume youre in the correct house
LittlerootTown_MaysHouse_1F_OnFrame: @ 81F893A
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_MaysHouse_1F_EventScript_EnterHouseMovingIn
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_MaysHouse_1F_EventScript_GoUpstairsToSetClock
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_MaysHouse_1F_EventScript_PetalburgGymReport
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 1, LittlerootTown_MaysHouse_1F_EventScript_YoureNewNeighbor
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 3, PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV
	.2byte 0

LittlerootTown_MaysHouse_1F_EventScript_GoUpstairsToSetClock:: @ 81F8964
	lockall
	msgbox PlayersHouse_1F_Text_GoSetTheClock, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_1F_Movement_PushTowardStairs
	applymovement LOCALID_MOM, LittlerootTown_MaysHouse_1F_Movement_PushTowardStairs
	waitmovement 0
	warp MAP_LITTLEROOT_TOWN_MAYS_HOUSE_2F, 255, 1, 1
	waitstate
	releaseall
	end

LittlerootTown_MaysHouse_1F_Movement_PushTowardStairs: @ 81F898A
	walk_up
	step_end

LittlerootTown_MaysHouse_1F_EventScript_EnterHouseMovingIn:: @ 81F898C
	lockall
	setvar VAR_0x8004, LOCALID_MOM
	setvar VAR_0x8005, FEMALE
	goto PlayersHouse_1F_EventScript_EnterHouseMovingIn
	end

LittlerootTown_MaysHouse_1F_EventScript_PetalburgGymReport:: @ 81F899D
	lockall
	setvar VAR_0x8004, FEMALE
	setvar VAR_0x8005, LOCALID_MOM
	goto PlayersHouse_1F_EventScript_PetalburgGymReportFemale
	end

LittlerootTown_MaysHouse_1F_EventScript_YoureNewNeighbor:: @ 81F89AE
	lockall
	playse SE_PIN
	applymovement LOCALID_RIVAL_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL_MOM, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	applymovement LOCALID_RIVAL_MOM, LittlerootTown_MaysHouse_1F_Movement_RivalMomApproach
	waitmovement 0
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_OhYoureTheNewNeighbor, MSGBOX_DEFAULT
	setflag FLAG_MET_RIVAL_MOM
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 2
	releaseall
	end

LittlerootTown_MaysHouse_1F_Movement_RivalMomApproach: @ 81F89EC
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RivalsHouse_1F_EventScript_RivalMom:: @ 81F89F3
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE103, RivalsHouse_1F_EventScript_GoHomeEverySoOften
	goto_if_set FLAG_SYS_POKEMON_GET, RivalsHouse_1F_EventScript_RivalIsOnRoute103
	compare VAR_LITTLEROOT_RIVAL_STATE, 3
	goto_if_eq RivalsHouse_1F_EventScript_RivalTooBusy
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_LikeChildLikeFather, MSGBOX_DEFAULT
	release
	end

RivalsHouse_1F_EventScript_RivalTooBusy:: @ 81F8A1F
	msgbox RivalsHouse_1F_Text_TooBusyToNoticeVisit, MSGBOX_DEFAULT
	release
	end

RivalsHouse_1F_EventScript_RivalIsOnRoute103:: @ 81F8A29
	msgbox RivalsHouse_1F_Text_WentOutToRoute103, MSGBOX_DEFAULT
	release
	end

RivalsHouse_1F_EventScript_GoHomeEverySoOften:: @ 81F8A33
	msgbox RivalsHouse_1F_Text_ShouldGoHomeEverySoOften, MSGBOX_DEFAULT
	release
	end

RivalsHouse_1F_EventScript_RivalSibling:: @ 81F8A3D
	lock
	faceplayer
	special GetPlayerBigGuyGirlString
	msgbox RivalsHouse_1F_Text_DoYouHavePokemon, MSGBOX_DEFAULT
	release
	end

LittlerootTown_MaysHouse_1F_EventScript_GoSeeRoom:: @ 81F8A4C
	lockall
	setvar VAR_0x8004, LOCALID_MOM
	setvar VAR_0x8005, FEMALE
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	goto PlayersHouse_1F_EventScript_MomGoSeeRoom
	end

LittlerootTown_MaysHouse_1F_EventScript_MeetRival0:: @ 81F8A67
	lockall
	setvar VAR_0x8008, 0
	goto LittlerootTown_MaysHouse_1F_EventScript_MeetRival
	end

LittlerootTown_MaysHouse_1F_EventScript_MeetRival1:: @ 81F8A73
	lockall
	setvar VAR_0x8008, 1
	goto LittlerootTown_MaysHouse_1F_EventScript_MeetRival
	end

LittlerootTown_MaysHouse_1F_EventScript_MeetRival2:: @ 81F8A7F
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_MaysHouse_1F_EventScript_MeetRival
	end

LittlerootTown_MaysHouse_1F_EventScript_MeetRival:: @ 81F8A8B
	playse SE_EXIT
	delay 10
	addobject LOCALID_RIVAL
	delay 30
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	compare VAR_0x8008, 1
	call_if_ne LittlerootTown_MaysHouse_1F_EventScript_PlayerFaceMay
	playbgm MUS_ENCOUNTER_MAY, 1
	compare VAR_0x8008, 0
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MayApproachPlayer0
	compare VAR_0x8008, 1
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MayApproachPlayer1
	compare VAR_0x8008, 2
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MayApproachPlayer2
	msgbox RivalsHouse_1F_Text_MayWhoAreYou, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 0
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MayGoUpstairs0
	compare VAR_0x8008, 1
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MayGoUpstairs1
	compare VAR_0x8008, 2
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MayGoUpstairs2
	playse SE_EXIT
	removeobject LOCALID_RIVAL
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_MAY
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	delay 30
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_MaysHouse_1F_EventScript_PlayerFaceMay:: @ 81F8B2A
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_EventScript_MayApproachPlayer0:: @ 81F8B35
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_1F_Movement_MayApproachPlayer0
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_EventScript_MayApproachPlayer1:: @ 81F8B40
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_1F_Movement_MayApproachPlayer1
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_EventScript_MayApproachPlayer2:: @ 81F8B4B
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_1F_Movement_MayApproachPlayer2
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_Movement_MayApproachPlayer0: @ 81F8B56
	walk_in_place_fastest_left
	walk_left
	walk_in_place_fastest_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_MaysHouse_1F_Movement_MayApproachPlayer1: @ 81F8B5E
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_MaysHouse_1F_Movement_MayApproachPlayer2: @ 81F8B62
	walk_in_place_fastest_right
	walk_right
	walk_in_place_fastest_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_MaysHouse_1F_EventScript_MayGoUpstairs0:: @ 81F8B6A
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_1F_Movement_PlayerWatchMayExit0
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_1F_Movement_MayGoUpstairs0
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_EventScript_MayGoUpstairs1:: @ 81F8B7C
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_1F_Movement_PlayerWatchMayExit1
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_1F_Movement_MayGoUpstairs1
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_EventScript_MayGoUpstairs2:: @ 81F8B8E
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_1F_Movement_PlayerWatchMayExit2
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_1F_Movement_MayGoUpstairs2
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_Movement_PlayerWatchMayExit0: @ 81F8BA0
	delay_16
	delay_8
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_1F_Movement_PlayerWatchMayExit1: @ 81F8BA4
	delay_16
	delay_8
	walk_in_place_fastest_right
	delay_16
	delay_16
	walk_in_place_fastest_up
	step_end

LittlerootTown_MaysHouse_1F_Movement_PlayerWatchMayExit2: @ 81F8BAB
	delay_16
	delay_8
	walk_in_place_fastest_left
	step_end

LittlerootTown_MaysHouse_1F_Movement_MayGoUpstairs0: @ 81F8BAF
	walk_in_place_fastest_right
	walk_right
	walk_in_place_fastest_up
	walk_up
	walk_up
	step_end

LittlerootTown_MaysHouse_1F_Movement_MayGoUpstairs1: @ 81F8BB5
	walk_in_place_fastest_right
	walk_right
	walk_in_place_fastest_up
	walk_up
	walk_up
	walk_in_place_fastest_left
	walk_left
	walk_in_place_fastest_up
	walk_up
	step_end

LittlerootTown_MaysHouse_1F_Movement_MayGoUpstairs2: @ 81F8BBF
	walk_in_place_fastest_left
	walk_left
	walk_in_place_fastest_up
	walk_up
	walk_up
	step_end

RivalsHouse_1F_Text_OhYoureTheNewNeighbor: @ 81F8BC5
	.string "으-음 누구니?\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "그래 네가 옆집으로\n"
	.string "이사 온 {PLAYER}{K_I}구나!\p"
	.string "우리 집에도 너와 비슷한 또래의\n"
	.string "{STR_VAR_1}이 있단다!\p"
	.string "“새 친구가 생기겠네!”\n"
	.string "라고 하면서\l"
	.string "무척 기대하고 있었어!$"
	// え-と どなた かしら?ｐ
	// …… …… ……ｎ
	// …… …… ……ｐ
	// そうか あなたが おとなりにｎ
	// ひっこしてきた {PLAYER}{KUN} ね!ｐ
	// うちにも あなたと おなじ としごろのｎ
	// {STR_VAR_1}が いるのよ!ｐ
	// 「あたらしい おともだちが できる!」ｎ
	// なんて いってｌ
	// とっても たのしみに してたの!

RivalsHouse_1F_Text_LikeChildLikeFather: @ 81F8CA5
	.string "아빠도 그 애에게 지지 않도록\n"
	.string "포켓몬에 열중하고 있단다\p"
	.string "연구소에 없다면\n"
	.string "분명 어딘가의 풀숲이라도\l"
	.string "뒤지고 있는 거 아닐까...$"
	// おとうさんも あのこに まけずｎ
	// ポケモンに むちゅう なのよｐ
	// けんきゅうじょに いなければｎ
	// きっと どこかの くさむらにでもｌ
	// もぐりに いってるんじゃ ないかしら……

RivalsHouse_1F_Text_TooBusyToNoticeVisit: @ 81F8D37
	.string "{RIVAL}{K_I}도 참 모처럼 {PLAYER}{K_IGA}\n"
	.string "인사하러 왔는데\l"
	.string "포켓몬에 열심인가 봐$"
	// {RIVAL}ったら せっかく §あ§おがｎ
	// ごあいさつに きてくれたって いうのにｌ
	// ポケモンに むちゅう みたいね

RivalsHouse_1F_Text_WentOutToRoute103: @ 81F8D93
	.string "어머 {RIVAL}{K_I}라면\n"
	.string "지금 막 103번 도로 쪽으로\l"
	.string "나간다고 했어!\p"
	.string "정말 아빠를 닮아서 그런지\n"
	.string "집에서 가만히 있지를 못한다니까$"
	// あら §か だったらｎ
	// ついさっき 103ばんどうろの ほうへｌ
	// でかけて いったわよ!ｐ
	// まったく おとうさんに にてｎ
	// おうちで じっとして いられないのよね
	
RivalsHouse_1F_Text_ShouldGoHomeEverySoOften: @ 81F8E01
	.string "포켓몬이랑 같이\n"
	.string "모험하는 것도 좋지만\p"
	.string "가끔은 집에 돌아와서 엄마한테\n"
	.string "건강한 모습 좀 보여주고 그러렴!\p"
	.string "마음속으로는 분명\n"
	.string "{PLAYER}{K_EULREUL}\l"
	.string "걱정하고 있으실 테니까...$"
	// ポケモンと いっしょにｎ
	// ぼうけん するのも いいけどｐ
	// たまには おうちに かえって おかあさんにｎ
	// げんきな かおを みせてあげてね!ｐ
	// こころの なかでは きっとｎ
	// §あ§おの ことｌ
	// しんぱい してる はずだから……

RivalsHouse_1F_Text_MayWhoAreYou: @ 81F8EC6
	.string "어라? 너... 누구야?\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "네가 {PLAYER}...\n"
	.string "그래 오늘 이사 왔구나...\p"
	.string "나 난 봄이야!\n"
	.string "자 잘 부탁해\p"
	.string "난...\n"
	.string "온 세상 포켓몬들과\l"
	.string "친구가 되는 게 꿈이야...\p"
	.string "그 그래서\n"
	.string "아빠... 털보박사님한테\l"
	.string "{PLAYER}의 얘기를 듣고\p"
	.string "나 {PLAYER}{K_I}랑도\n"
	.string "친구가 됐으면 좋겠다고...\l"
	.string "생각하고 있었어...\p"
	.string "앗 나도 참 {PLAYER}{K_I}랑\n"
	.string "처음 만나서 얘기하는 건데\l"
	.string "무슨 얘길 하는 건지...\p"
	.string "에헤헤...\p"
	.string "앗 이런!\p"
	.string "나 아빠 심부름으로\n"
	.string "야생 포켓몬\l"
	.string "잡으러 가려던 참이었어!\p"
	.string "나갈 준비를 해야 하니까\n"
	.string "{PLAYER}{K_AYA} 그럼 나중에 또 보자!$"
	// あら? あなた……だれ?ｐ
	// …… …… ……ｎ
	// …… …… ……ｐ
	// あなたが §あ§お……ｎ
	// そうか きょう ひっこし だったんだ……ｐ
	// あ あたし ハルカ!ｎ
	// よ よろしくねｐ
	// あたし……ｎ
	// せかいじゅうの ポケモンとｌ
	// ともだちに なるのが ゆめ なの……ｐ
	// で でねｎ
	// おとうさん…… オダマキはかせ からｌ
	// §あ§おの おはなし きいてｐ
	// あたし §あ§お ともｎ
	// おともだちに なれたらなあ……ｌ
	// なんて おもってたの……ｐ
	// あっ あたしったら §あ§おとｎ
	// はじめて おはなし してるのにｌ
	// なに いってんだろ……ｐ
	// てへへ……ｐ
	// あっ いけない!ｐ
	// あたし おとうさんの おてつだいでｎ
	// やせいの ポケモンｌ
	// つかまえに いくところ だったんだ!ｐ
	// でかける したくを するからｎ
	// §あ§お また あとでね!

RivalsHouse_1F_Text_BrendanWhoAreYou: @ 81F90B4
	.string "너...\p"
	.string "누구야?\p"
	.string "앗 네가 옆집에\n"
	.string "이사 온 {PLAYER}{K_I}구나...\p"
	.string "흐음\n"
	.string "여자애였구나...\p"
	.string "아빠... 털보박사님한테\n"
	.string "옆집으로 이사 오는 건\l"
	.string "체육관 관장의 아이라고 들어서\l"
	.string "멋대로 남자애라고 생각하고 있었어\p"
	.string "난 휘웅이야\n"
	.string "뭐 이웃이 됐으니\l"
	.string "앞으로 잘 부탁할게\p"
	.string "응? {PLAYER} 너\n"
	.string "포켓몬 없어?\p"
	.string "괜찮으면 내가\n"
	.string "잡아줄까?\p"
	.string "아 맞다 까먹고 있었네...\p"
	.string "나 아빠 심부름으로\n"
	.string "야생 포켓몬\l"
	.string "잡으러 가려고 하던 중이었어\p"
	.string "나갈 준비를 해야 하니까\n"
	.string "{PLAYER}{K_AYA} 다음에 또 보자!$"
	// おまえ……ｐ
	// だれ?ｐ
	// あっ おまえが となりにｎ
	// ひっこして きた §あか……ｐ
	// ふうんｎ
	// おんなのこ だったんだ……ｐ
	// とうさん…… オダマキはかせ からｎ
	// となりに ひっこして くるのはｌ
	// ジムリ-ダ-の こども って きいてたからｌ
	// かってに おとこ だと おもってたよｐ
	// オレは ユウキｎ
	// まあ おとなりさんに なったことだしｌ
	// これから よろしくなｐ
	// おや? §あはｎ
	// ポケモン もってないのか?ｐ
	// よかったら オレがｎ
	// つかまえてきて やろうか?ｐ
	// って わすれてた……ｐ
	// オレ とうさんの てつだいでｎ
	// やせいの ポケモンｌ
	// つかまえに いく ところ だったんだｐ
	// でかける したくを するからｎ
	// §あ また こんどな!

RivalsHouse_1F_Text_DoYouHavePokemon: @ 81F9262
	.string "와-아 이웃이다!\p"
	.string "{K_BOY_CALL}{K_EUNNEUN} 벌써\n"
	.string "자기 포켓몬을 가지고 있어?$"
	// わ-い おとなりさんだ!ｐ
	// §いは もうｎ
	// じぶんの ポケモン もってるの?
