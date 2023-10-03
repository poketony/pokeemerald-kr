.set LOCALID_ARCHIE, 1
.set LOCALID_MAXIE, 2
.set LOCALID_TABITHA, 3
.set LOCALID_MAGMA_GRUNT_2, 22
.set LOCALID_MAGMA_GRUNT_1, 29


MtChimney_MapScripts:: @ 822EDC1
	map_script MAP_SCRIPT_ON_RESUME, MtChimney_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MtChimney_OnTransition
	.byte 0

MtChimney_OnTransition: @ 822EDCC
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 1
	end

MtChimney_OnResume: @ 822EDD2
	setstepcallback STEP_CB_ASH
	end

MtChimney_EventScript_Archie:: @ 822EDD5
	lock
	faceplayer
	call_if_unset FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieGoStopTeamMagma
	call_if_set FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieBusyFighting
	closemessage
	applymovement LOCALID_ARCHIE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_EVIL_LEADER_PLEASE_STOP
	release
	end

MtChimney_EventScript_ArchieGoStopTeamMagma:: @ 822EDF9
	msgbox MtChimney_Text_ArchieGoStopTeamMagma, MSGBOX_DEFAULT
	return

MtChimney_EventScript_ArchieBusyFighting:: @ 822EE02
	msgbox MtChimney_Text_ArchieIHaveMyHandsFull, MSGBOX_DEFAULT
	return

MtChimney_EventScript_Maxie:: @ 822EE0B
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, 0
	msgbox MtChimney_Text_MeteoriteWillActivateVolcano, MSGBOX_DEFAULT
	applymovement LOCALID_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAXIE, Common_Movement_Delay48
	waitmovement 0
	msgbox MtChimney_Text_MaxieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat
	msgbox MtChimney_Text_MaxieYouHaventSeenLastOfMagma, MSGBOX_DEFAULT
	closemessage
	delay 30
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAXIE
	removeobject LOCALID_MAGMA_GRUNT_1
	removeobject LOCALID_TABITHA
	removeobject LOCALID_MAGMA_GRUNT_2
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA
	fadescreen FADE_FROM_BLACK
	setobjectxyperm LOCALID_ARCHIE, 10, 12
	addobject LOCALID_ARCHIE
	compare VAR_FACING, DIR_EAST
	call_if_eq MtChimney_EventScript_ArchieApproachPlayerEast
	compare VAR_FACING, DIR_NORTH
	call_if_eq MtChimney_EventScript_ArchieApproachPlayerNorth
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox MtChimney_Text_ArchieThankYou, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_EAST
	call_if_eq MtChimney_EventScript_ArchieExitEast
	compare VAR_FACING, DIR_NORTH
	call_if_eq MtChimney_EventScript_ArchieExitNorth
	removeobject LOCALID_ARCHIE
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
	setflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
	setflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
	clearflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY
	releaseall
	end

MtChimney_EventScript_ArchieApproachPlayerEast:: @ 822EEC7
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieApproachPlayerEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieApproachPlayerNorth:: @ 822EED2
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieApproachPlayerNorth
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitEast:: @ 822EEDD
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieExitEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitNorth:: @ 822EEE8
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieExitNorth
	waitmovement 0
	return

MtChimney_EventScript_LavaCookieLady:: @ 822EEF3
	lock
	faceplayer
	showmoneybox 0, 0, 0
	msgbox MtChimney_Text_LavaCookiesJust200, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MtChimney_EventScript_DeclineLavaCookie
	checkmoney 200, 0
	compare VAR_RESULT, FALSE
	goto_if_eq MtChimney_EventScript_NotEnoughMoney
	msgbox MtChimney_Text_ThankYouDear, MSGBOX_DEFAULT
	checkitemspace ITEM_LAVA_COOKIE, 1
	compare VAR_RESULT, TRUE
	call_if_eq MtChimney_EventScript_RemoveMoney
	giveitem ITEM_LAVA_COOKIE
	compare VAR_RESULT, FALSE
	goto_if_eq MtChimney_EventScript_BagIsFull
	hidemoneybox
	release
	end

MtChimney_EventScript_BagIsFull:: @ 822EF51
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_RemoveMoney:: @ 822EF5E
	removemoney 200, 0
	updatemoneybox 0, 0
	return

MtChimney_EventScript_DeclineLavaCookie:: @ 822EF69
	msgbox MtChimney_Text_OhFineThen, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_NotEnoughMoney:: @ 822EF76
	msgbox MtChimney_Text_YouveNotGotTheMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_Movement_ArchieApproachPlayerEast: @ 822EF83
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

MtChimney_Movement_ArchieExitEast: @ 822EF8B
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_ArchieApproachPlayerNorth: @ 822EF94
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

MtChimney_Movement_ArchieExitNorth: @ 822EF9C
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused1: @ 822EFA6
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused2: @ 822EFB8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused3: @ 822EFC1
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused4: @ 822EFD0
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused5: @ 822EFE9
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused6: @ 822EFF4
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused7: @ 822F004
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused8: @ 822F015
	delay_16
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_down
	step_end

MtChimney_Movement_Unused9: @ 822F01D
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused10: @ 822F02B
	walk_down
	step_end

MtChimney_Movement_Unused11: @ 822F02D
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused12: @ 822F035
	delay_16
	delay_16
	walk_in_place_fastest_left
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused13: @ 822F03F
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_fastest_left
	delay_16
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused14: @ 822F04A
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_right
	step_end

MtChimney_Movement_Unused15: @ 822F04F
	walk_left
	walk_in_place_fastest_right
	delay_16
	step_end

MtChimney_EventScript_BusyAquaGrunt1:: @ 822F053
	msgbox MtChimney_Text_MagmaOutnumbersUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt2:: @ 822F05C
	msgbox MtChimney_Text_LessHabitatForWaterPokemon, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt3:: @ 822F065
	msgbox MtChimney_Text_MagmasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_Tabitha:: @ 822F06E
	trainerbattle_single TRAINER_TABITHA_MT_CHIMNEY, MtChimney_Text_TabithaIntro, MtChimney_Text_TabithaDefeat
	msgbox MtChimney_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt2:: @ 822F085
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_2, MtChimney_Text_Grunt2Intro, MtChimney_Text_Grunt2Defeat
	msgbox MtChimney_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_BusyMagmaGrunt1:: @ 822F09C
	msgbox MtChimney_Text_TeamAquaAlwaysMessingWithPlans, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt2:: @ 822F0A5
	msgbox MtChimney_Text_MeteoritesPackAmazingPower, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt3:: @ 822F0AE
	msgbox MtChimney_Text_YouBetterNotMessWithUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt4:: @ 822F0B7
	msgbox MtChimney_Text_AquasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt5:: @ 822F0C0
	msgbox MtChimney_Text_DouseThemInFire, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt6:: @ 822F0C9
	msgbox MtChimney_Text_KeepMakingMoreLand, MSGBOX_SIGN
	end

MtChimney_EventScript_MagmaPoochyena:: @ 822F0D2
	msgbox MtChimney_Text_Bufoh, MSGBOX_SIGN
	end

MtChimney_EventScript_AquaPoochyena:: @ 822F0DB
	msgbox MtChimney_Text_Bushaa, MSGBOX_SIGN
	end

MtChimney_EventScript_MeteoriteMachine:: @ 822F0E4
	lockall
	goto_if_unset FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, MtChimney_EventScript_MachineOn
	goto_if_set FLAG_RECEIVED_METEORITE, MtChimney_EventScript_MachineOff
	msgbox MtChimney_Text_RemoveTheMeteorite, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MtChimney_EventScript_LeaveMeteoriteAlone
	msgbox MtChimney_Text_PlayerRemovedMeteorite, MSGBOX_DEFAULT
	giveitem ITEM_METEORITE
	setflag FLAG_RECEIVED_METEORITE
	releaseall
	end

MtChimney_EventScript_LeaveMeteoriteAlone:: @ 822F123
	msgbox MtChimney_Text_PlayerLeftMeteorite, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOff:: @ 822F12D
	msgbox MtChimney_Text_MachineMakesNoResponse, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOn:: @ 822F137
	msgbox MtChimney_Text_MetoriteFittedOnMachine, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_RouteSign:: @ 822F141
	msgbox MtChimney_Text_RouteSign, MSGBOX_SIGN
	end

MtChimney_EventScript_Shelby:: @ 822F14A
	trainerbattle_single TRAINER_SHELBY_1, MtChimney_Text_ShelbyIntro, MtChimney_Text_ShelbyDefeat, MtChimney_EventScript_DefeatedShelby
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq MtChimney_EventScript_RematchShelby
	msgbox MtChimney_Text_ShelbyPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_DefeatedShelby:: @ 822F176
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_ShelbyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SHELBY_1
	release
	end

MtChimney_EventScript_RematchShelby:: @ 822F195
	trainerbattle_rematch TRAINER_SHELBY_1, MtChimney_Text_ShelbyRematchIntro, MtChimney_Text_ShelbyRematchDefeat
	msgbox MtChimney_Text_ShelbyPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Melissa:: @ 822F1AC
	trainerbattle_single TRAINER_MELISSA, MtChimney_Text_MelissaIntro, MtChimney_Text_MelissaDefeat
	msgbox MtChimney_Text_MelissaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sheila:: @ 822F1C3
	trainerbattle_single TRAINER_SHEILA, MtChimney_Text_SheilaIntro, MtChimney_Text_SheilaDefeat
	msgbox MtChimney_Text_SheilaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Shirley:: @ 822F1DA
	trainerbattle_single TRAINER_SHIRLEY, MtChimney_Text_ShirleyIntro, MtChimney_Text_ShirleyDefeat
	msgbox MtChimney_Text_ShirleyPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt1:: @ 822F1F1
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_Grunt1Intro, MtChimney_Text_Grunt1Defeat
	msgbox MtChimney_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sawyer:: @ 822F208
	trainerbattle_single TRAINER_SAWYER_1, MtChimney_Text_SawyerIntro, MtChimney_Text_SawyerDefeat, MtChimney_EventScript_SawyerDefeated
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq MtChimney_EventScript_SawyerRematch
	msgbox MtChimney_Text_SawyerPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_SawyerDefeated:: @ 822F234
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_SawyerRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SAWYER_1
	release
	end

MtChimney_EventScript_SawyerRematch:: @ 822F253
	trainerbattle_rematch TRAINER_SAWYER_1, MtChimney_Text_SawyerRematchIntro, MtChimney_Text_SawyerRematchDefeat
	msgbox MtChimney_Text_SawyerPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_Text_MeteoriteWillActivateVolcano: @ 822F26A
	.string "운석에 숨겨진 힘...\p"
	.string "이 장치로 증폭된다면\n"
	.string "눈 깜짝할 사이에 굴뚝산의\l"
	.string "화산 활동은 활발해진다...\p"
	.string "그 에너지가\n"
	.string "분화구에 깊은 곳까지 작용하고\l"
	.string "그리고 후후후...$"
	// いんせきに ひめられた ちからｐ
	// この そうちで ぞうふく すればｎ
	// たちまちの うちに えんとつやまのｌ
	// かざん かつどうは かっぱつになる……ｐ
	// その エネルギ-がｎ
	// かこうの おくふかくに はたらきかけｌ
	// そして ふふふ……

MtChimney_Text_MaxieIntro: @ 822F32E
	.string "마적: 응? 넌 누구냐\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "최근 아쿠아단의 활동을\n"
	.string "방해하는 꼬마가 있다고\l"
	.string "아강 녀석이 투덜거리던데\l"
	.string "그게 너였던 거로군\p"
	.string "...흠!\n"
	.string "우리 마그마단의 방해도\l"
	.string "하러 온 건가!\p"
	.string "알겠나? 생명은 땅에서 태어나\n"
	.string "진화를 이루어간다\p"
	.string "그래 대지야말로 전부다!\p"
	.string "그래서 우리 마그마단은\n"
	.string "대지를 넓혀서\l"
	.string "사람과 포켓몬의 발전을 추구한다!\p"
	.string "그러기 위해 필요한 것은\n"
	.string "이 산에 잠든 그 녀석...\p"
	.string "이런! 그런 것까지\n"
	.string "네게 알려줄 필요는 없었지\p"
	.string "그것보다도\n"
	.string "우리들을 방해하면 어떻게 되는지\l"
	.string "네게 똑똑히 알려주마!$"
	// マツブサ『ん? だれだ おまえはｐ
	// …… …… ……ｎ
	// …… …… ……ｐ
	// さいきん アクアだんの かつどうをｎ
	// じゃまする こどもがいる とｌ
	// アオギリの やつが ぼやいて いたがｌ
	// それは おまえの ことかｐ
	// ……ふん!ｎ
	// われわれ マグマだんの じゃまもｌ
	// してくれようって わけだな!ｐ
	// いいか? いきものは りくちに あがりｎ
	// しんかを くりかえしてきたｐ
	// そう だいちこそが すべてなのだ!ｐ
	// だから われわれ マグマだんはｎ
	// だいちを ふやすことでｌ
	// ひとと ポケモンの はってんを めざす!ｐ
	// そのために ひつよう なのがｎ
	// このやまに ねむる アイツ……ｐ
	// おっと! そんなことまでｎ
	// おまえが しる ひつようは なかったなｐ
	// そんなことよりｎ
	// われわれの じゃまを したら どうなるかｌ
	// おまえに わからせて やろう!

MtChimney_Text_MaxieDefeat: @ 822F5CF
	.string "뭣이!?\p"
	.string "이 마적이\n"
	.string "방심한 건가!?$"
	// なに!?ｐ
	// この マツブサとも あろう ものがｎ
	// ゆだん したか!?

MtChimney_Text_MaxieYouHaventSeenLastOfMagma: @ 822F5F7
	.string "마적: 뭐 좋다\n"
	.string "이 굴뚝산은 일단 포기하도록 하지...\p"
	.string "하지만 마그마단의 활동은\n"
	.string "이걸로 끝난 게 아니다!\p"
	.string "후후후...\p"
	.string "운석을 쓰지 못해도\n"
	.string "그 구슬만 손에 넣는다면 후후후...$"
	// マツブサ『まあ いいｎ
	// このばは ひとまず あきらめよう……ｐ
	// だが マグマだんの かつどうはｎ
	// これで おわったわけでは ないのだ!ｐ
	// ふふふ……ｐ
	// いんせきなど つかわなくともｎ
	// あの たまが てにはいれば ふふふ……

MtChimney_Text_TabithaIntro: @ 822F6AA
	.string "우효효!\p"
	.string "너 여기까지 온 건가!\p"
	.string "하지만 늦었다고\n"
	.string "유성의 폭포에서 찾은\l"
	.string "운석은 리더에게 넘겼으니까 말이야!$"
	// ウヒョヒョ!ｐ
	// おまえ ここまで きたのか!ｐ
	// だけど おそかったぜｎ
	// りゅうせいのたきで みつけたｌ
	// いんせきは リ-ダ-に わたしたからな!

MtChimney_Text_TabithaDefeat: @ 822F72C
	.string "우효효...\p"
	.string "내가 져도 리더가 제대로\n"
	.string "그 녀석을 깨우실 거야...$"
	// ウヒョヒョ……ｐ
	// オレが まけても リ-ダ-が ちゃんとｎ
	// アイツを めざめさせて……

MtChimney_Text_TabithaPostBattle: @ 822F76D
	.string "리더! 빨리!\n"
	.string "운석의 파워를 그 녀석에게!\p"
	.string "우효효...!$"
	// リ-ダ-! はやく!ｎ
	// いんせきの パワ-を アイツに!ｐ
	// ウヒョヒョ……!

MtChimney_Text_Grunt2Intro: @ 822F7A2
	.string "우리 마그마단은\n"
	.string "모두를 위해 노력하고 있는 거다!\p"
	.string "그 녀석의 힘으로\n"
	.string "대지가 넓어지면 모두가\l"
	.string "살 수 있는 곳이 늘어서 좋잖아!$"
	// オレら マグマだんはｎ
	// みんなの ために がんばってるんだ!ｐ
	// だって アイツの ちからでｎ
	// だいちが ふえれば みんなもｌ
	// すむところが ふえて うれしいだろ?

MtChimney_Text_Grunt2Defeat: @ 822F83A
	.string "어라-?\n"
	.string "나 진 건가-?$"
	// あれ-?ｎ
	// オレ まけたの-!?

MtChimney_Text_Grunt2PostBattle: @ 822F859
	.string "우리들의 리더가\n"
	.string "“모두를 위한 일”이라고\l"
	.string "했단 말이다!\p"
	.string "근데 왜 다들 방해하는 거지?$"
	// オレらの リ-ダ-はｎ
	// 「みんなが よろこぶ ことだ」ってｌ
	// いってるんだ!ｐ
	// なのに なんで みんな ジャマするんだ?

MtChimney_Text_Grunt1Intro: @ 822F8B6
	.string "땅이 넓어지게 되면\n"
	.string "커다란 마이홈을 지을 거야!\p"
	.string "용암 위에 이사해서 말이지!$"
	// りくちが ふえて くれたらｎ
	// おおきな マイホ-ム だって もてるわ!ｐ
	// ようがんの うえに ひっこし するのよ!

MtChimney_Text_Grunt1Defeat: @ 822F921
	.string "내 마이홈의 꿈이...$"
	// わたしの マイホ-ムの ゆめが……

MtChimney_Text_Grunt1PostBattle: @ 822F93A
	.string "너 같은 건 바다에 둥둥\n"
	.string "떠내려가면 좋을 텐데!$"
	// あんた なんか うみに プカプカｎ
	// うかんで いれば いいのよ!

MtChimney_Text_TeamAquaAlwaysMessingWithPlans: @ 822F978
	.string "아쿠아단 녀석들...\n"
	.string "일일이 우리 방해나 해대고 말야!$"
	// アクアだんの やつらめ……ｎ
	// いちいち オレたちの じゃまを しやがって!

MtChimney_Text_MeteoritesPackAmazingPower: @ 822F9B2
	.string "운석에는 엄청난 파워가 있어!$"
	// いんせきには すごい パワ-が あるのだ!

MtChimney_Text_YouBetterNotMessWithUs: @ 822F9D1
	.string "우리 방해하지 마라! 알겠어?\p"
	.string "그 녀석을 부활시키는 건\n"
	.string "모두를 위한 거니까!$"
	// オレたちの じゃまを するな!ｐ
	// アイツを ふっかつ させるのはｎ
	// みんなの ために やってること なんだ!

MtChimney_Text_AquasNameSimilar: @ 822FA2F
	.string "우리들은 마그마단!\p"
	.string "녀석들은 아쿠아단!\p"
	.string "비슷한 이름을 쓰다니\n"
	.string "열받는 녀석들이군!$"
	// オレたちは マグマだん!ｐ
	// やつらは アクアだん!ｐ
	// にたような なまえを つけやがってｎ
	// いまいましい やつらだ!

MtChimney_Text_DouseThemInFire: @ 822FA8B
	.string "좋아!\n"
	.string "불꽃을 퍼부어버려-!!$"
	// よ-し!ｎ
	// ほのおを ぶっかけてやれ-!!

MtChimney_Text_KeepMakingMoreLand: @ 822FAA5
	.string "좀 더 좀 더 대지를 넓히자고!$"
	// もっと もっと だいちを ふやすぜ!!

MtChimney_Text_Bufoh: @ 822FACB
	.string "부와-!!$"
	// ぶふぉ-!!

MtChimney_Text_ArchieGoStopTeamMagma: @ 822FAD2
	.string "아강: 크으윽 {PLAYER}!\n"
	.string "역시 여기에도 온 건가!\p"
	.string "봐라! 마그마단 녀석들이\n"
	.string "무슨 짓을 꾸미고 있는지!\p"
	.string "녀석들은 빼앗은 운석의 파워를\n"
	.string "화산에 흘려보내려고 하는 거다!\p"
	.string "그런 짓을 했다가는\n"
	.string "화산이 대분화할 거라고!$"
	// アオギリ『むむむ §あ!ｎ
	// やっぱり ここにも あらわれたか!ｐ
	// ほら! マグマだんの れんちゅうがｎ
	// なにを たくらんで いるのか みてみろ!ｐ
	// やつらは うばった いんせきの パワ-をｎ
	// かざんに ながしこもうと しているんだ!ｐ
	// そんなことを したらｎ
	// かざんが だいふんか するじゃないか!

MtChimney_Text_ArchieIHaveMyHandsFull: @ 822FBC7
	.string "아강: 으-음 크으윽!\p"
	.string "마적 녀석을 막으러 가고 싶지만\n"
	.string "아무리 나라도\l"
	.string "3명을 동시에 상대하다보니\l"
	.string "서둘러 갈 수가 없다!$"
	// アオギリ『う-む むむむ!ｐ
	// マツブサの やつを とめに いきたいがｎ
	// さすがの おれもｌ
	// 3にん どうじに あいてを していてはｌ
	// てが はなせない!

MtChimney_Text_ArchieThankYou: @ 822FC3D
	.string "아강: {PLAYER}... 역시나로군\n"
	.string "네 덕분에 마그마단의\l"
	.string "파괴활동을 막을 수 있었다\p"
	.string "하지만 너는...\n"
	.string "어느 쪽의 편인 거냐...\p"
	.string "뭐 됐다\p"
	.string "우리는 계속해서\n"
	.string "마그마단을 쫓아가도록 하겠다!\p"
	.string "{PLAYER} 너도 다음에\n"
	.string "어딘가에서 만나게 될 것 같군...$"
	// アオギリ『§あ…… たすかったよｎ
	// おまえの おかげで マグマだんのｌ
	// はかいかつどうを ふせぐことが できたｐ
	// だが おまえは……ｎ
	// どちらの みかた なんだ……ｐ
	// まあ いいｐ
	// われわれは ひきつづきｎ
	// マグマだんを おいかけると しよう!ｐ
	// §あ おまえとは またｎ
	// どこかで あうことに なりそうだな……

MtChimney_Text_MagmaOutnumbersUs: @ 822FD1F
	.string "제길 마그마단이 너무 많아...\n"
	.string "이대로라면 위험해!$"
	// くそう マグマだんが おおすぎる……ｎ
	// このままでは まずいぞ!

MtChimney_Text_LessHabitatForWaterPokemon: @ 822FD5B
	.string "대지를 늘려버리면\n"
	.string "물포켓몬이 살 수 있는 곳이\l"
	.string "적어지잖아!$"
	// だいちを ふやしたらｎ
	// みずポケモンが すむ ばしょがｌ
	// へってしまう じゃね-か!

MtChimney_Text_MagmasNameSimilar: @ 822FDA1
	.string "우리들은 아쿠아단!\p"
	.string "녀석들은 마그마단!\p"
	.string "헷갈리기 쉬운 이름을 쓰다니\n"
	.string "열받는 녀석들이야!$"
	// オレたちは アクアだん!ｐ
	// やつらは マグマだん!ｐ
	// まぎらわしい なまえを つけやがってｎ
	// しゃくにさわる やつらだ!

MtChimney_Text_Bushaa: @ 822FDFC
	.string "후샤-!!$"
	// ぷしゃ-!!

MtChimney_Text_LavaCookiesJust200: @ 822FE04
	.string "굴뚝산 명물\n"
	.string "용암전병이 하나에 200원!\l"
	.string "하나 사가렴$"

MtChimney_Text_ThankYouDear: @ 822FE4D
	.string "고마워$"

MtChimney_Text_YouveNotGotTheMoney: @ 822FE5E
	.string "어머 돈이 없으면\n"
	.string "물건을 살 수 없어$"

MtChimney_Text_OhFineThen: @ 822FE9B
	.string "어머 그래$"

MtChimney_Text_MetoriteFittedOnMachine: @ 822FEAA
	.string "수수께끼 장치에\n"
	.string "운석이 박혀 있다...\p"
	.string "뭔가의 에너지를\n"
	.string "모으고 있는 듯하다$"

MtChimney_Text_RemoveTheMeteorite: @ 822FF12
	.string "수수께끼 장치에\n"
	.string "운석이 박혀 있다...\p"
	.string "운석을 빼겠습니까?$"

MtChimney_Text_PlayerRemovedMeteorite: @ 822FF66
	.string "{PLAYER}{K_EUNNEUN} 운석을\n"
	.string "장치에서 빼냈다!$"

MtChimney_Text_PlayerLeftMeteorite: @ 822FF9C
	.string "{PLAYER}{K_EUNNEUN} 운석을\n"
	.string "그대로 두었다$"

MtChimney_Text_MachineMakesNoResponse: @ 822FFC0
	.string "수수께끼 장치...\n"
	.string "전혀 반응하지 않는다...$"

MtChimney_Text_RouteSign: @ 822FFFA
	.string "{DOWN_ARROW} 울퉁불퉁 산길\n"
	.string "빠져나가면 용암마을$"

MtChimney_Text_ShelbyIntro: @ 823001D
	.string "온천욕으로\n"
	.string "리프레쉬하고 왔으니\l"
	.string "나는 지금 누구에게도 지지 않는다네!$"

MtChimney_Text_ShelbyDefeat: @ 8230076
	.string "흠- 이건 뭐-\n"
	.string "대단하구만-$"

MtChimney_Text_ShelbyPostBattle: @ 82300A2
	.string "져버렸구먼... 이래서는\n"
	.string "어디 가서 달인이라고 못 하겠어...$"

MtChimney_Text_ShelbyRegister: @ 82300E3
	.string "진심으로 싸워서 즐거웠다네\n"
	.string "괜찮다면 다시 상대해 줄 수 있겠나!$"
	// マゴと たたかってる ようで たのしかったｎ
	// よかったら また あいてを しておくれ!

MtChimney_Text_ShelbyRematchIntro: @ 8230153
	.string "포켓몬과 한마음이 된다면\n"
	.string "아주 멋진 일을 할 수 있을 것 같군$"

MtChimney_Text_ShelbyRematchDefeat: @ 82301BB
	.string "흠냐- 이건 뭐-\n"
	.string "대단하구만-$"

MtChimney_Text_ShelbyPostRematch: @ 82301E7
	.string "자네와 포켓몬은\n"
	.string "한마음인 것 같군$"

MtChimney_Text_MelissaIntro: @ 823022A
	.string "왠지 불타올라서\n"
	.string "승부하고 싶어 참을 수 없어!$"

MtChimney_Text_MelissaDefeat: @ 823026D
	.string "뜨거운 승부였어$"

MtChimney_Text_MelissaPostBattle: @ 8230292
	.string "굴뚝산의 열기가\n"
	.string "여자를 불태우지$"

MtChimney_Text_SheilaIntro: @ 82302BD
	.string "모처럼 굴뚝산에 왔으니\n"
	.string "여기서도 포켓몬을 단련시키고 싶어!$"

MtChimney_Text_SheilaDefeat: @ 8230304
	.string "네 배틀 실력은\n"
	.string "마치 분화하는 굴뚝산 같아!$"

MtChimney_Text_SheilaPostBattle: @ 823033A
	.string "모처럼 굴뚝산에 왔는데\n"
	.string "관광만 하고 가기엔 너무 아까워\p"
	.string "배틀도 즐기고 싶고\n"
	.string "선물로 전병도 꼭 사 가야지!$"

MtChimney_Text_ShirleyIntro: @ 82303DF
	.string "온천에 들어갔다 나왔더니\n"
	.string "난 지금 완전 최고의 컨디션이야!\l"
	.string "이길 확률 100%라니까!$"

MtChimney_Text_ShirleyDefeat: @ 8230436
	.string "으-응? 벌써 몸이 식었나?$"

MtChimney_Text_ShirleyPostBattle: @ 8230463
	.string "한번 더 온천에 들어가야지!\n"
	.string "너도 같이 들어갈래?\p"
	.string "농담이야!$"

MtChimney_Text_SawyerIntro: @ 82304B3
	.string "여기는 좋은 산이야!\n"
	.string "뜨거운 누님들이 가득하니까!$"
	// ここは いい やまだ!ｎ
	// あっつい おねいさんたちが いっぱいだあ!

MtChimney_Text_SawyerDefeat: @ 82304F7
	.string "오옷 너도 뜨겁구나!$"
	// おおっ あんたも あついねぇ!

MtChimney_Text_SawyerPostBattle: @ 8230519
	.string "지금부터 뜨거운 누님들을 데리고\n"
	.string "용암온천에라도 가볼까 해$"
	// いまから あつい おねいさんたちを つれてｎ
	// フエンおんせん でも いこうかな

MtChimney_Text_SawyerRegister: @ 8230557
	.string "뜨거운 트레이너는 좋아해!\n"
	.string "포켓내비에 등록해주면 좋겠어$"
	// あつい トレ-ナ-は すきだなあ!ｎ
	// ポケナビに とうろくしても いいかい

MtChimney_Text_SawyerRematchIntro: @ 823059C
	.string "뜨거운 누님들에게\n"
	.string "둘러싸여 행복한 나는 지지 않아!$"
	// あっつい おねいさん たちにｎ
	// かこまれて しあわせな おれは まけんぜ!

MtChimney_Text_SawyerRematchDefeat: @ 82305E3
	.string "오옷 역시\n"
	.string "네가 더 뜨겁구나!$"
	// おおっ やっぱりｎ
	// あんたの ほうが あついねぇ!

MtChimney_Text_SawyerPostRematch: @ 8230614
	.string "사실 정말로 뜨거워...\n"
	.string "옷을 너무 많이 입고 왔나 봐$"
	// しかし ほんとに あついや……ｎ
	// ふく いっぱい きすぎちゃった かな

