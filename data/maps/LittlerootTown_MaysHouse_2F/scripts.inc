.set LOCALID_RIVAL, 1

LittlerootTown_MaysHouse_2F_MapScripts:: @ 81F9296
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_MaysHouse_2F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_MaysHouse_2F_OnWarp
	.byte 0

LittlerootTown_MaysHouse_2F_OnTransition: @ 81F92A1
	compare VAR_LITTLEROOT_RIVAL_STATE, 2
	call_if_lt LittlerootTown_MaysHouse_2F_EventScript_CheckSetReadyToMeetMay
	compare VAR_LITTLEROOT_RIVAL_STATE, 3
	call_if_ge LittlerootTown_MaysHouse_2F_EventScript_CheckShouldUpdateMayPos
	compare VAR_LITTLEROOT_INTRO_STATE, 4
	call_if_eq PlayersHouse_2F_EventScript_BlockStairsUntilClockIsSet
	call SecretBase_EventScript_SetDecorationFlags
	setvar VAR_SECRET_BASE_INITIALIZED, 0
	end

LittlerootTown_MaysHouse_2F_EventScript_CheckShouldUpdateMayPos:: @ 81F92CD
	goto_if_set FLAG_MET_RIVAL_LILYCOVE, LittlerootTown_MaysHouse_2F_EventScript_TryUpdateMayPos
	compare VAR_BIRCH_LAB_STATE, 2
	goto_if_ge LittlerootTown_MaysHouse_2F_EventScript_Ret
	goto LittlerootTown_MaysHouse_2F_EventScript_TryUpdateMayPos

LittlerootTown_MaysHouse_2F_EventScript_TryUpdateMayPos:: @ 81F92E6
	checkplayergender
	compare VAR_RESULT, FEMALE
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_Ret
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2
	goto_if_ge LittlerootTown_MaysHouse_2F_EventScript_Ret
	setobjectxyperm LOCALID_RIVAL, 8, 2
	setobjectmovementtype LOCALID_RIVAL, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_MaysHouse_2F_EventScript_Ret:: @ 81F9309
	return

LittlerootTown_MaysHouse_2F_EventScript_CheckSetReadyToMeetMay:: @ 81F930A
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_SetReadyToMeetMay
	return

LittlerootTown_MaysHouse_2F_EventScript_SetReadyToMeetMay:: @ 81F9317
	setvar VAR_LITTLEROOT_RIVAL_STATE, 2
	return

LittlerootTown_MaysHouse_2F_OnWarp: @ 81F931D
	map_script_2 VAR_SECRET_BASE_INITIALIZED, 0, LittlerootTown_MaysHouse_2F_EventScript_CheckInitDecor
	.2byte 0

LittlerootTown_MaysHouse_2F_EventScript_CheckInitDecor:: @ 81F9327
	checkplayergender
	compare VAR_RESULT, FEMALE
	goto_if_eq SecretBase_EventScript_InitDecorations
	end

LittlerootTown_MaysHouse_2F_EventScript_RivalsPokeBall:: @ 81F9334
	lockall
	compare VAR_LITTLEROOT_RIVAL_STATE, 2
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_MeetMay
	msgbox RivalsHouse_2F_Text_ItsRivalsPokeBall, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_MaysHouse_2F_EventScript_MeetMay:: @ 81F934A
	delay 10
	addobject LOCALID_RIVAL
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_2F_Movement_MayEnters
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	delay 10
	playbgm MUS_ENCOUNTER_MAY, 1
	compare VAR_FACING, DIR_NORTH
	call_if_eq LittlerootTown_MaysHouse_2F_EventScript_MeetMayNorth
	compare VAR_FACING, DIR_SOUTH
	call_if_eq LittlerootTown_MaysHouse_2F_EventScript_MeetMaySouth
	compare VAR_FACING, DIR_WEST
	call_if_eq LittlerootTown_MaysHouse_2F_EventScript_MeetMayWest
	compare VAR_FACING, DIR_EAST
	call_if_eq LittlerootTown_MaysHouse_2F_EventScript_MeetMayEast
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_MaysHouse_2F_EventScript_MeetMayNorth:: @ 81F93BA
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerNorth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox RivalsHouse_2F_Text_MayWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMayNorth
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCNorth
	waitmovement 0
	return

LittlerootTown_MaysHouse_2F_EventScript_MeetMaySouth:: @ 81F93E9
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerSouth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox RivalsHouse_2F_Text_MayWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMaySouth
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCSouth
	waitmovement 0
	return

LittlerootTown_MaysHouse_2F_EventScript_MeetMayWest:: @ 81F9418
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerWest
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox RivalsHouse_2F_Text_MayWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCWest
	waitmovement 0
	return

LittlerootTown_MaysHouse_2F_EventScript_MeetMayEast:: @ 81F9440
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerEast
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox RivalsHouse_2F_Text_MayWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMayEast
	applymovement LOCALID_RIVAL, LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCEast
	waitmovement 0
	return

LittlerootTown_MaysHouse_2F_Movement_MayEnters: @ 81F946F
	walk_down
	walk_down
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerNorth: @ 81F9473
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCNorth: @ 81F9479
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMayNorth: @ 81F9483
	delay_16
	walk_in_place_fastest_up
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerSouth: @ 81F948B
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCSouth: @ 81F948F
	walk_up
	walk_in_place_fastest_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMaySouth: @ 81F9497
	delay_16
	walk_in_place_fastest_up
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerWest: @ 81F949D
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_down
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCWest: @ 81F94A4
	walk_up
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

@ Unused, the player is already facing this direction so its unneeded
LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMayWest: @ 81F94A9
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerEast: @ 81F94AD
	walk_right
	walk_right
	walk_down
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCEast: @ 81F94B2
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMayEast: @ 81F94BB
	delay_16
	walk_in_place_fastest_up
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

RivalsHouse_2F_EventScript_Rival:: @ 81F94C1
	lockall
	goto_if_set FLAG_MET_RIVAL_LILYCOVE, RivalsHouse_2F_EventScript_RivalPostLilycove
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq RivalsHouse_2F_EventScript_May
	compare VAR_RESULT, FEMALE
	goto_if_eq RivalsHouse_2F_EventScript_Brendan
	end

RivalsHouse_2F_EventScript_May:: @ 81F94E3
	msgbox RivalsHouse_2F_Text_MayGettingReady, MSGBOX_DEFAULT
	releaseall
	end

RivalsHouse_2F_EventScript_Brendan:: @ 81F94ED
	msgbox RivalsHouse_2F_Text_BrendanGettingReady, MSGBOX_DEFAULT
	releaseall
	end

RivalsHouse_2F_EventScript_RivalPostLilycove:: @ 81F94F7
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq RivalsHouse_2F_EventScript_MayPostLilycove
	compare VAR_RESULT, FEMALE
	call_if_eq RivalsHouse_2F_EventScript_BrendanPostLilycove
	setflag FLAG_MET_RIVAL_IN_HOUSE_AFTER_LILYCOVE
	releaseall
	end

RivalsHouse_2F_EventScript_MayPostLilycove:: @ 81F951D
	goto_if_set FLAG_MET_RIVAL_IN_HOUSE_AFTER_LILYCOVE, RivalsHouse_2F_EventScript_MayWhereShouldIGoNext
	msgbox RivalsHouse_2F_Text_MayJustCheckingMyPokedex, MSGBOX_DEFAULT
	return

RivalsHouse_2F_EventScript_BrendanPostLilycove:: @ 81F952F
	goto_if_set FLAG_MET_RIVAL_IN_HOUSE_AFTER_LILYCOVE, RivalsHouse_2F_EventScript_BrendanWhereShouldIGoNext
	msgbox RivalsHouse_2F_Text_BrendanJustCheckingMyPokedex, MSGBOX_DEFAULT
	return

RivalsHouse_2F_EventScript_MayWhereShouldIGoNext:: @ 81F9541
	msgbox RivalsHouse_2F_Text_MayWhereShouldIGoNext, MSGBOX_DEFAULT
	return

RivalsHouse_2F_EventScript_BrendanWhereShouldIGoNext:: @ 81F954A
	msgbox RivalsHouse_2F_Text_BrendanWhereShouldIGoNext, MSGBOX_DEFAULT
	return

LittlerootTown_MaysHouse_2F_EventScript_PC:: @ 81F9553
	lockall
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_CheckRivalsPC
	compare VAR_RESULT, FEMALE
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_CheckPlayersPC
	end

LittlerootTown_MaysHouse_2F_EventScript_CheckRivalsPC:: @ 81F956C
	msgbox gText_PokemonTrainerSchoolEmail, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_MaysHouse_2F_EventScript_CheckPlayersPC:: @ 81F9576
	setvar VAR_0x8004, 2
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
	special BedroomPC
	waitstate
	releaseall
	end

LittlerootTown_MaysHouse_2F_EventScript_TurnOffPlayerPC:: @ 81F958F
	setvar VAR_0x8004, 2
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

RivalsHouse_2F_Text_MayWhoAreYou: @ 81F959C
	.string "에...!?\n"
	.string "너 누...구야?\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "네가 {PLAYER}...\n"
	.string "아 오늘 이사 오는 거였구나...\p"
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
	@ えっ……!?ｎ
	@ あなた だれ…… なの?ｐ
	@ …… …… ……ｎ
	@ …… …… ……ｐ
	@ あなたが §あ§お……ｎ
	@ そうか きょう ひっこし だったんだ……ｐ
	@ あ あたし ハルカ!ｎ
	@ よ よろしくねｐ
	@ あたし……ｎ
	@ せかいじゅうの ポケモンとｌ
	@ ともだちに なるのが ゆめ なの……ｐ
	@ で でねｎ
	@ おとうさん…… オダマキはかせ からｌ
	@ §あ§おの おはなし きいてｐ
	@ あたし §あ§お ともｎ
	@ おともだちに なれたらなあ……ｌ
	@ なんて おもってたの……ｐ
	@ あっ あたしったら §あ§おとｎ
	@ はじめて おはなし してるのにｌ
	@ なに いってんだろ……ｐ
	@ てへへ……ｐ
	@ あっ いけない!ｐ
	@ あたし おとうさんの おてつだいでｎ
	@ やせいの ポケモンｌ
	@ つかまえに いくところ だったんだ!ｐ
	@ でかける したくを するからｎ
	@ §あ§お また あとでね!

RivalsHouse_2F_Text_MayGettingReady: @ 81F978A
	.string "포켓몬 체력 가득 찼고!\n"
	.string "도구도 이걸로... 됐다!$"
	@ ポケモンは たいりょく まんたん!ｎ
	@ どうぐも これで よし……と!

RivalsHouse_2F_Text_BrendanWhoAreYou: @ 81F97B4
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
	@ おまえ……ｐ
	@ だれ?ｐ
	@ あっ おまえが となりにｎ
	@ ひっこして きた §あか……ｐ
	@ ふうんｎ
	@ おんなのこ だったんだ……ｐ
	@ とうさん…… オダマキはかせ からｎ
	@ となりに ひっこして くるのはｌ
	@ ジムリ-ダ-の こども って きいてたからｌ
	@ かってに おとこ だと おもってたよｐ
	@ オレは ユウキｎ
	@ まあ おとなりさんに なったことだしｌ
	@ これから よろしくなｐ
	@ おや? §あはｎ
	@ ポケモン もってないのか?ｐ
	@ よかったら オレがｎ
	@ つかまえてきて やろうか?ｐ
	@ って わすれてた……ｐ
	@ オレ とうさんの てつだいでｎ
	@ やせいの ポケモンｌ
	@ つかまえに いく ところ だったんだｐ
	@ でかける したくを するからｎ
	@ §あ また こんどな!

RivalsHouse_2F_Text_BrendanGettingReady: @ 81F9962
	.string "포켓몬 체력 가득 찼고\n"
	.string "도구도 이거면... 괜찮겠다$"
	@ ポケモンは たいりょく まんたんｎ
	@ どうぐも これで だいじょうぶ ……か

RivalsHouse_2F_Text_ItsRivalsPokeBall: @ 81F9991
	.string "{RIVAL}의 몬스터볼이다!\p"
	.string "이대로 놔두자...$"
	@ §かの モンスタ-ボ-ルだ!ｐ
	@ このままに しておこう……

RivalsHouse_2F_Text_MayJustCheckingMyPokedex: @ 81F99C9
	.string "봄이: {PLAYER}{K_AYA}!\p"
	.string "나 지금 있지\n" 
	.string "포켓몬 도감 보고 있었어\p"
	.string "발견만 하고\n"
	.string "잡지 못한 포켓몬이랑\l"
	.string "곧 진화할 거 같은 포켓몬이\l"
	.string "아직 많이 남아 있어\p"
	.string "이번엔 어디로\n"
	.string "포켓몬 잡으러 갈까?$"
	@ ハルカ『§あ§お!ｐ
	@ あたし いまねｎ
	@ ポケモンずかんを ながめていたのｐ
	@ みつけた だけでｎ
	@ つかまえていない ポケモンやｌ
	@ しんか しそうな ポケモンｌ
	@ まだまだ いっぱい いるんだよねｐ
	@ こんどは どこにｎ
	@ ポケモン つかまえに いこうかな?

RivalsHouse_2F_Text_MayWhereShouldIGoNext: @ 81F9A9E
	.string "봄이: 이번엔 어디로\n"
	.string "포켓몬 잡으러 갈까?\p"
	.string "간 곳에서 또\n"
	.string "{PLAYER}{K_I}랑 만나는 거 아냐!?$"
	@ ハルカ『こんどは どこにｎ
	@ ポケモン つかまえに いこうかな?ｐ
	@ いった さきで またｎ
	@ §あ§おと であったりして!?

RivalsHouse_2F_Text_BrendanJustCheckingMyPokedex: @ 81F9B0D
	.string "휘웅: {PLAYER}{K_I}구나\p"
	.string "지금 포켓몬 도감을\n"
	.string "체크하고 있었어\p"
	.string "아직 잡지 못한\n"
	.string "포켓몬도 있긴 한데\l"
	.string "꽤 괜찮은 느낌이지 않아?\p"
	.string "이렇게 도감을 보고 있으면\n"
	.string "또 모험하러 떠나고 싶어져$"
	@ ユウキ『§あかｐ
	@ いま ポケモンずかんをｎ
	@ チェック してたんだｐ
	@ まだまだ つかまえていないｎ
	@ ポケモンも いるけどｌ
	@ かなり いい かんじだろ?ｐ
	@ こうして ずかんを みているとｎ
	@ また ぼうけんに いきたくなるな

RivalsHouse_2F_Text_BrendanWhereShouldIGoNext: @ 81F9BE7
	.string "휘웅: 이번엔 어디서\n"
	.string "포켓몬 잡을지 고민되네...\p"
	.string "만약 포켓몬 잡을 때\n"
	.string "{PLAYER}{K_EULREUL} 만나게 되면\l"
	.string "승부해 줄래?$"
	@ ユウキ『こんどは どこでｎ
	@ ポケモン つかまえるか なやむな……ｐ
	@ もし ポケモン つかまえているときｎ
	@ §あと であったらｌ
	@ しょうぶ してやろうか?
