.set LOCALID_MOM, 1
.set LOCALID_RIVAL_MOM, 4
.set LOCALID_RIVAL, 7

LittlerootTown_BrendansHouse_1F_MapScripts:: @ 81F7755
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_BrendansHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_BrendansHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_BrendansHouse_1F_OnFrame
	.byte 0

LittlerootTown_BrendansHouse_1F_OnLoad: @ 81F7765
	compare VAR_LITTLEROOT_INTRO_STATE, 6
	call_if_lt LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes
	call_if_set FLAG_RECEIVED_RUNNING_SHOES, LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual
	end

LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes:: @ 81F777A
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, 1
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, 1
	return

LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual:: @ 81F778D
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual
	return

LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual:: @ 81F779A
	setmetatile 3, 7, METATILE_BrendansMaysHouse_BookOnTable, 1
	return

LittlerootTown_BrendansHouse_1F_OnTransition: @ 81F77A4
	compare VAR_LITTLEROOT_INTRO_STATE, 3
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor
	compare VAR_LITTLEROOT_INTRO_STATE, 5
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs
	compare VAR_LITTLEROOT_INTRO_STATE, 6
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV
	end

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs:: @ 81F77C6
	setobjectxyperm LOCALID_MOM, 8, 4
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV:: @ 81F77D2
	setobjectxyperm LOCALID_MOM, 4, 5
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor:: @ 81F77DE
	setobjectxyperm LOCALID_MOM, 9, 8
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

@ Many of the below scripts have no gender check because they assume youre in the correct house
@ The below SS Ticket script uses Mays house state by accident(?), but theyre both set identically after the intro
LittlerootTown_BrendansHouse_1F_OnFrame: @ 81F77EA
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 1, LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 3, PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV
	.2byte 0

LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock:: @ 81F7814
	lockall
	msgbox PlayersHouse_1F_Text_GoSetTheClock, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	applymovement LOCALID_MOM, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	waitmovement 0
	warp MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F, 255, 7, 1
	waitstate
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs: @ 81F783A
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn:: @ 81F783C
	lockall
	setvar VAR_0x8004, LOCALID_MOM
	setvar VAR_0x8005, MALE
	goto PlayersHouse_1F_EventScript_EnterHouseMovingIn
	end

LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport:: @ 81F784D
	lockall
	setvar VAR_0x8004, MALE
	setvar VAR_0x8005, LOCALID_MOM
	goto PlayersHouse_1F_EventScript_PetalburgGymReportMale
	end

LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor:: @ 81F785E
	lockall
	playse SE_PIN
	applymovement LOCALID_RIVAL_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL_MOM, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	applymovement LOCALID_RIVAL_MOM, LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach
	waitmovement 0
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_OhYoureTheNewNeighbor, MSGBOX_DEFAULT
	setflag FLAG_MET_RIVAL_MOM
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach: @ 81F789C
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_GoSeeRoom:: @ 81F78A3
	lockall
	setvar VAR_0x8004, LOCALID_MOM
	setvar VAR_0x8005, MALE
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	goto PlayersHouse_1F_EventScript_MomGoSeeRoom
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival0:: @ 81F78BE
	lockall
	setvar VAR_0x8008, 0
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival1:: @ 81F78CA
	lockall
	setvar VAR_0x8008, 1
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival2:: @ 81F78D6
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival:: @ 81F78E2
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
	call_if_ne LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan
	playbgm MUS_ENCOUNTER_BRENDAN, 1
	compare VAR_0x8008, 0
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0
	compare VAR_0x8008, 1
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1
	compare VAR_0x8008, 2
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2
	msgbox RivalsHouse_1F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 0
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0
	compare VAR_0x8008, 1
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1
	compare VAR_0x8008, 2
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2
	playse SE_EXIT
	removeobject LOCALID_RIVAL
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_BRENDAN
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	delay 30
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan:: @ 81F7981
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0:: @ 81F798C
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1:: @ 81F7997
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2:: @ 81F79A2
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0: @ 81F79AD
	walk_in_place_fastest_left
	walk_left
	walk_in_place_fastest_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1: @ 81F79B5
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2: @ 81F79B9
	walk_in_place_fastest_right
	walk_right
	walk_in_place_fastest_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0:: @ 81F79C1
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1:: @ 81F79D3
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2:: @ 81F79E5
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0: @ 81F79F7
	delay_16
	delay_8
	walk_in_place_fastest_right
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1: @ 81F79FB
	delay_16
	delay_8
	walk_in_place_fastest_right
	delay_16
	delay_16
	walk_in_place_fastest_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2: @ 81F7A02
	delay_16
	delay_8
	walk_in_place_fastest_left
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0: @ 81F7A06
	walk_in_place_fastest_right
	walk_right
	walk_in_place_fastest_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1: @ 81F7A0C
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

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2: @ 81F7A16
	walk_in_place_fastest_left
	walk_left
	walk_in_place_fastest_up
	walk_up
	walk_up
	step_end

PlayersHouse_1F_Text_IsntItNiceInHere: @ 81F7A1C
	.string "엄마: 봐봐 {PLAYER}{K_AYA}!\n"
	.string "집 안도 멋지지!$"
	@ ママ『ほら §あ!ｎ
	@ おうちの なかも すてき でしょ!

PlayersHouse_1F_Text_MoversPokemonGoSetClock: @ 81F7A46
	.string "집 정리를\n"
	.string "이삿짐센터 포켓몬이\l"
	.string "도와주니까 정말 편해!\p"
	.string "{PLAYER}도 2층에 있는\n"
	.string "네 방에 한번 가보렴!\p"
	.string "아빠가 이사 기념으로\n"
	.string "사 주신 시계가 있을 테니까\l"
	.string "시간 좀 맞춰 둬$"
	@ おうちの かたづけはｎ
	@ ひっこしやさんの ポケモンがｌ
	@ てつだって くれるから らくちんね!ｐ
	@ §あも 2かいに あるｎ
	@ じぶんの おへやに いってごらん!ｐ
	@ パパが ひっこしの おいわいにｎ
	@ かってくれた とけいが あるからｌ
	@ じかんを あわせて おきなさいよ

PlayersHouse_1F_Text_ArentYouInterestedInRoom: @ 81F7B24
	.string "엄마: {PLAYER}{K_AYA}\p"
	.string "네 방은 안 봐도 되니?$"
	@ ママ『§あｐ
	@ じぶんの へやを みてこないの?

PlayersHouse_1F_Text_GoSetTheClock: @ 81F7B67
	.string "엄마: {PLAYER}{K_AYA}\n"
	.string "방 안에 있는 시계 맞춰 두렴$"
	@ ママ『§あｐ
	@ おへやの とけい あわせてきて

PlayersHouse_1F_Text_OhComeQuickly: @ 81F7B96
	.string "엄마: ...아! {PLAYER}{K_AYA}! {PLAYER}{K_AYA}!\n"
	.string "빨리 여기로 와보렴!$"
	@ ママ『……あ! §あ! §あ!ｎ
	@ はやく こっちに いらっしゃい!

PlayersHouse_1F_Text_MaybeDadWillBeOn: @ 81F7BBC
	.string "엄마: 등화도시 체육관이 나오고 있어\n"
	.string "아빠가 나올지도 몰라!!$"
	@ ママ『トウカの ジムが うつってるわｎ
	@ パパが でるかもよ!!

PlayersHouse_1F_Text_ItsOverWeMissedHim: @ 81F7BF1
	.string "엄마: 어머머... 끝나버렸네\p"
	.string "아빠가 나왔던 거 같은데 아쉽다$"
	@ ママ『あらら…… おわっちゃったｐ
	@ パパが でてたみたい だったのに ざんねんね

PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor: @ 81F7C35
	.string "...아 맞다 맞다! 이 마을에\n"
	.string "털보박사님이라고 하시는\l"
	.string "아빠 친구분이 계시거든\p"
	.string "박사님 집은 옆집이니까\n"
	.string "얼른 인사 드리고 오렴!$"
	@ ……あ そうそう! このまち にはｎ
	@ オダマキはかせ っていうｌ
	@ パパの おともだちが いるのｐ
	@ はかせの いえは おとなり だからｎ
	@ きちんと あいさつ してくると いいわ!

PlayersHouse_1F_Text_SeeYouHoney: @ 81F7CC3
	.string "엄마: 그럼 다녀오렴!$"
	@ ママ『いってらっしゃい!

PlayersHouse_1F_Text_DidYouMeetProfBirch: @ 81F7CD8
	.string "엄마: 털보박사님은 만나고 왔니?$"
	@ ママ『オダマキはかせ には あえたの?

PlayersHouse_1F_Text_YouShouldRestABit: @ 81F7D08
	.string "엄마: {PLAYER}{K_AYA} 잘 있었니?\n"
	.string "조금 지쳐 보이네?\p"
	.string "집에서 좀 쉬다 가렴$"
	@ ママ『どう? §あｎ
	@ すこし つかれたんじゃ ないかしら?ｐ
	@ おうちで やすんでいくと いいわ

PlayersHouse_1F_Text_TakeCareHoney: @ 81F7D5C
	.string "엄마: 그럼 조심하고!$"
	@ ママ『じゃあ きをつけてね!

PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom: @ 81F7D73
	.string "엄마: 어머\n"
	.string "그 배지 아빠한테 받은 거니!?\p"
	.string "그럼 엄마도 이거 줘야겠다$"
	@ ママ『あらｎ
	@ その バッジ パパから もらったの!?ｐ
	@ じゃあ ママも これ あげようかな

PlayersHouse_1F_Text_DontPushYourselfTooHard: @ 81F7DBE
	.string "너무 무리하지는 마렴\n"
	.string "언제든지 집에 와도 돼\p"
	.string "그럼 힘내!$"
	@ あんまり むりは しないでねｎ
	@ なにか あれば かえって くればいいからｐ
	@ じゃあ がんばってね!

PlayersHouse_1F_Text_IsThatAPokenav: @ 81F7E0E
	.string "엄마: 그건 뭐니? 포켓내비?\n"
	.string "데봉의 직원에게서 받은 거야?\p"
	.string "그럼 엄마도\n"
	.string "등록해 주려무나!\p"
	.string "...... ...... ......$"
	@ ママ『なあに それ? ポケナビ?ｎ
	@ デボンの ひとから いただいたの?ｐ
	@ じゃあ ママの こともｎ
	@ とうろくして もらっちゃおうかな!ｐ
	@ …… …… ……

PlayersHouse_1F_Text_RegisteredMom: @ 81F7E89
	.string "엄마를\n"
	.string "포켓내비에 등록했다!$"
	@ ママをｎ
	@ ポケナビに とうろく した!

PlayersHouse_1F_Text_Vigoroth1: @ 81F7EA8
	.string "후기-잇$"
	@ ふぎ-っ

PlayersHouse_1F_Text_Vigoroth2: @ 81F7EB3
	.string "후곳 후고 후고...$"
	@ ふごっ ふご ふご……

PlayersHouse_1F_Text_ReportFromPetalburgGym: @ 81F7EC6
	.string "인터뷰어: ... 이상으로\n"
	.string "등화체육관 앞에서 전해드렸습니다!$"
	@ インタビュア-『…… いじょうｎ
	@ トウカジムの まえ からでした!

PlayersHouse_1F_Text_TheresAMovieOnTV: @ 81F7F0F
	.string "TV에서 영화를 하고 있다!\p"
	.string "어른과 아이가 둘이서 나란히\n"
	.string "커다란 피아노 위에서 춤추고 있다!\p"
	.string "빨리 가자!$"
	@ テレビで えいがを やってる!ｐ
	@ おとなと こどもが ふたり ならんでｎ
	@ おおきな ピアノの うえで おどってる!ｐ
	@ もう いかなきゃ!

PlayersHouse_1F_Text_RunningShoesManual: @ 81F7F66
	.string "러닝슈즈의\n"
	.string "사용설명서가 있다!\p"
	.string "“러닝슈즈는\n"
	.string "  B 버튼을 누르면 지금보다\l"
	.string "  빨리 달릴 수 있게 해줍니다!\p"
	.string "  러닝슈즈를 신고\n"
	.string "  마음껏 달립시다!”$"
	@ ランニングシュ-ズのｎ
	@ せつめいしょが ある!ｐ
	@ 「ランニングシュ-ズはｎ
	@  Bボタンを おすことで いままでよりもｌ
	@  はやく はしれるように なります!ｐ
	@  ランニングシュ-ズを はいてｎ
	@  おもいっきり そとを はしろう!」

PlayersHouse_1F_Text_TicketFromBrineyCameForYou: @ 81F800E
	.string "아빠: 응?\n"
	.string "{PLAYER}{K_I} 아니냐!\p"
	.string "오랜만에 보는데\n"
	.string "어딘가 늠름해진 거 같은...\l"
	.string "그런 느낌이 드는구나\p"
	.string "...아 그래 맞다\n"
	.string "하기라는 사람한테서\l"
	.string "네 앞으로 뭔가가 왔단다!$"
	@ パパ『ん?ｎ
	@ §あじゃ ないか!ｐ
	@ ひさしぶりに かおを みたがｎ
	@ どこか たくましくなった……ｌ
	@ そんな かんじ だなｐ
	@ ……おっと そうだったｎ
	@ ハギさん という ひとからｌ
	@ おまえあてに なにか とどいていたぞ!

PlayersHouse_1F_Text_PortsInSlateportLilycove: @ 81F80FE
	.string "아빠: 승선티켓이구나...\p"
	.string "배를 탈 거라면 잿빛도시나 해안시티의\n"
	.string "선착장에서 타렴$"
	@ パパ『ふねのチケットか……ｐ
	@ ふねに のるなら カイナか ミナモにｎ
	@ ふねのりばが あったよな

PlayersHouse_1F_Text_BetterGetBackToGym: @ 81F815B
	.string "그럼 난\n"
	.string "등화도시 체육관으로 돌아가마\p"
	.string "여보\n"
	.string "그럼 다녀올게$"
	@ では わたしはｎ
	@ トウカの ジムに もどるよｐ
	@ ママｎ
	@ いえのこと たのんだよ

PlayersHouse_1F_Text_DadShouldStayLonger: @ 81F81B9
	.string "엄마: 네 아빠도 참\n"
	.string "오랜만에 집에 왔는데\l"
	.string "포켓몬 얘기만 하고!\p"
	.string "좀 더 천천히 쉬었다 가지!$"
	@ ママ『パパったらｎ
	@ ひさしぶりに かえって きたのにｌ
	@ ポケモンの はなし ばっかり!ｐ
	@ もっと ゆっくり すれば いいのにね!

PlayersHouse_1F_Text_IsThatABreakingStory: @ 81F824B
	.string "엄마: 무슨 뉴스지?$"
	@ ママ『なにかの ニュ-ス かしら?

PlayersHouse_1F_Text_LatiEmergencyNewsFlash: @ 81F826F
	.string "임시 뉴스입니다\p"
	.string "호연지방 각지에서\n"
	.string "...색의 포켓몬이 날아다니는 걸\l"
	.string "봤다는 정보가 들어왔습니다\p"
	.string "아직까지 정체는\n"
	.string "확인하지 못했다고 합니다...\p"
	.string "그럼 계속 이어지는\n"
	.string "영화를 즐겨 주십시오$"
	@ りんじ ニュ-ス ですｐ
	@ ホウエンちほうの かくちでｎ
	@ ……いろの ポケモンが とんでいたｌ
	@ という じょうほうが よせられていますｐ
	@ いまのところ しょうたいはｎ
	@ わかって いない ようです……ｐ
	@ では ひきつづきｎ
	@ えいがを おたのしみ ください

PlayersHouse_1F_Text_WhatColorDidTheySay: @ 81F8351
	.string "엄마: 저기 저기 {PLAYER}{K_AYA}\n"
	.string "지금 뉴스\l"
	.string "무슨 색의 포켓몬에 대해 말했었니?$"
	@ ママ『ねえ ねえ {PLAYER}ｎ
	@ いまの ニュ-スｌ
	@ なにいろの ポケモンって いってたの?

PlayersHouse_1F_Text_StillUnknownPokemon: @ 81F83A1
	.string "엄마: 흐음- 아직도\n"
	.string "알려지지 않은 포켓몬이 있는 거구나$"
	@ ママ『へえ- まだまだｎ
	@ しられていない ポケモンは いるのねえ
