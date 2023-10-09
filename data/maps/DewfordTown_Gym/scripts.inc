DewfordTown_Gym_MapScripts:: @ 81FC63C
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_Gym_OnTransition
	.byte 0

DewfordTown_Gym_OnTransition: @ 81FC642
	call DewfordTown_Gym_EventScript_SetFlashRadius
	end

DewfordTown_Gym_EventScript_SetFlashRadius:: @ 81FC648
	goto_if_defeated TRAINER_BRAWLY_1, DewfordTown_Gym_EventScript_SetLightsOn
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
	copyvar VAR_0x8001, VAR_0x8000
	compare VAR_0x8000, 0
	goto_if_eq DewfordTown_Gym_EventScript_SetFlashRadius7
	compare VAR_0x8000, 1
	goto_if_eq DewfordTown_Gym_EventScript_SetFlashRadius6
	compare VAR_0x8000, 2
	goto_if_eq DewfordTown_Gym_EventScript_SetFlashRadius5
	compare VAR_0x8000, 3
	goto_if_eq DewfordTown_Gym_EventScript_SetFlashRadius4
	compare VAR_0x8000, 4
	goto_if_eq DewfordTown_Gym_EventScript_SetFlashRadius3
	compare VAR_0x8000, 5
	goto_if_eq DewfordTown_Gym_EventScript_SetFlashRadius2
	goto DewfordTown_Gym_EventScript_SetFlashRadius1

DewfordTown_Gym_EventScript_SetLightsOn:: @ 81FC6A2
	setflashradius 0
	return

DewfordTown_Gym_EventScript_SetFlashRadius1:: @ 81FC6A6
	setflashradius 1
	return

DewfordTown_Gym_EventScript_SetFlashRadius2:: @ 81FC6AA
	setflashradius 2
	return

DewfordTown_Gym_EventScript_SetFlashRadius3:: @ 81FC6AE
	setflashradius 3
	return

DewfordTown_Gym_EventScript_SetFlashRadius4:: @ 81FC6B2
	setflashradius 4
	return

DewfordTown_Gym_EventScript_SetFlashRadius5:: @ 81FC6B6
	setflashradius 5
	return

DewfordTown_Gym_EventScript_SetFlashRadius6:: @ 81FC6BA
	setflashradius 6
	return

DewfordTown_Gym_EventScript_SetFlashRadius7:: @ 81FC6BE
	setflashradius 7
	return

DewfordTown_Gym_EventScript_BrightenRoom:: @ 81FC6C2
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
	nop1
	compare VAR_0x8000, VAR_0x8001
	goto_if_eq DewfordTown_Gym_EventScript_NoLightChange
	copyvar VAR_0x8001, VAR_0x8000
	compare VAR_0x8000, 1
	goto_if_eq DewfordTown_Gym_EventScript_AnimateFlash1Trainer
	compare VAR_0x8000, 2
	goto_if_eq DewfordTown_Gym_EventScript_AnimateFlash2Trainers
	compare VAR_0x8000, 3
	goto_if_eq DewfordTown_Gym_EventScript_AnimateFlash3Trainers
	compare VAR_0x8000, 4
	goto_if_eq DewfordTown_Gym_EventScript_AnimateFlash4Trainers
	compare VAR_0x8000, 5
	goto_if_eq DewfordTown_Gym_EventScript_AnimateFlash5Trainers
	compare VAR_0x8000, 6
	goto_if_eq DewfordTown_Gym_EventScript_AnimateFlash6Trainers

DewfordTown_Gym_EventScript_NoLightChange:: @ 81FC71A
	return

@ NOTE: A little confusingly, a larger animateflash param value is a smaller flash radius
DewfordTown_Gym_EventScript_AnimateFlash1Trainer:: @ 81FC71B
	playse SE_SWITCH
	animateflash 6
	call DewfordTown_Gym_EventScript_SetFlashRadius
	return

DewfordTown_Gym_EventScript_AnimateFlash2Trainers:: @ 81FC726
	playse SE_SWITCH
	animateflash 5
	call DewfordTown_Gym_EventScript_SetFlashRadius
	return

DewfordTown_Gym_EventScript_AnimateFlash3Trainers:: @ 81FC731
	playse SE_SWITCH
	animateflash 4
	call DewfordTown_Gym_EventScript_SetFlashRadius
	return

DewfordTown_Gym_EventScript_AnimateFlash4Trainers:: @ 81FC73C
	playse SE_SWITCH
	animateflash 3
	call DewfordTown_Gym_EventScript_SetFlashRadius
	return

DewfordTown_Gym_EventScript_AnimateFlash5Trainers:: @ 81FC747
	playse SE_SWITCH
	animateflash 2
	call DewfordTown_Gym_EventScript_SetFlashRadius
	return

DewfordTown_Gym_EventScript_AnimateFlash6Trainers:: @ 81FC752
	playse SE_SWITCH
	animateflash 1
	call DewfordTown_Gym_EventScript_SetFlashRadius
	return

DewfordTown_Gym_EventScript_AnimateFlashFullBrightness:: @ 81FC75D
	playse SE_SWITCH
	animateflash 0
	call DewfordTown_Gym_EventScript_SetFlashRadius
	return

DewfordTown_Gym_EventScript_CountTrainersDefeated:: @ 81FC768
	setvar VAR_0x8000, 0
	goto_if_not_defeated TRAINER_TAKAO, DewfordTown_Gym_EventScript_CheckJocelyn
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckJocelyn:: @ 81FC77B
	goto_if_not_defeated TRAINER_JOCELYN, DewfordTown_Gym_EventScript_CheckLaura
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckLaura:: @ 81FC789
	goto_if_not_defeated TRAINER_LAURA, DewfordTown_Gym_EventScript_CheckBrenden
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckBrenden:: @ 81FC797
	goto_if_not_defeated TRAINER_BRENDEN, DewfordTown_Gym_EventScript_CheckCristian
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckCristian:: @ 81FC7A5
	goto_if_not_defeated TRAINER_CRISTIAN, DewfordTown_Gym_EventScript_CheckLilith
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckLilith:: @ 81FC7B3
	goto_if_not_defeated TRAINER_LILITH, DewfordTown_Gym_EventScript_StopCountingTrainers
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_StopCountingTrainers:: @ 81FC7C1
	return

DewfordTown_Gym_EventScript_Brawly:: @ 81FC7C2
	trainerbattle_single TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyIntro, DewfordTown_Gym_Text_BrawlyDefeat, DewfordTown_Gym_EventScript_BrawlyDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq DewfordTown_Gym_EventScript_BrawlyRematch
	goto_if_unset FLAG_RECEIVED_TM08, DewfordTown_Gym_EventScript_GiveBulkUp2
	msgbox DewfordTown_Gym_Text_BrawlyPostBattle, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_BrawlyDefeated:: @ 81FC7F7
	call DewfordTown_Gym_EventScript_AnimateFlashFullBrightness
	message DewfordTown_Gym_Text_ReceivedKnuckleBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_DEWFORD_GYM
	setflag FLAG_BADGE02_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	compare VAR_PETALBURG_GYM_STATE, 6
	call_if_eq Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 2
	call Common_EventScript_SetGymTrainers
	call DewfordTown_Gym_EventScript_GiveBulkUp
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox DewfordTown_Gym_Text_RegisteredBrawly, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_BRAWLY_MATCH_CALL
	setvar VAR_ROXANNE_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	release
	end

DewfordTown_Gym_EventScript_GiveBulkUp:: @ 81FC855
	giveitem ITEM_TM08
	compare VAR_RESULT, 0
	goto_if_eq Common_EventScript_BagIsFull
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM08
	return

DewfordTown_Gym_EventScript_GiveBulkUp2: @ 81FC878
	giveitem ITEM_TM08
	compare VAR_RESULT, 0
	goto_if_eq Common_EventScript_ShowBagIsFull
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM08
	release
	end

DewfordTown_Gym_EventScript_BrawlyRematch:: @ 81FC89C
	trainerbattle_rematch_double TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyPreRematch, DewfordTown_Gym_Text_BrawlyRematchDefeat, DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons
	msgbox DewfordTown_Gym_Text_BrawlyPostRematch, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_Takao:: @ 81FC8B7
	trainerbattle_single TRAINER_TAKAO, DewfordTown_Gym_Text_TakaoIntro, DewfordTown_Gym_Text_TakaoDefeat, DewfordTown_Gym_EventScript_TakaoBrightenRoom
	msgbox DewfordTown_Gym_Text_TakaoPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_TakaoBrightenRoom:: @ 81FC8D2
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Jocelyn:: @ 81FC8D9
	trainerbattle_single TRAINER_JOCELYN, DewfordTown_Gym_Text_JocelynIntro, DewfordTown_Gym_Text_JocelynDefeat, DewfordTown_Gym_EventScript_JocelynBrightenRoom
	msgbox DewfordTown_Gym_Text_JocelynPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_JocelynBrightenRoom:: @ 81FC8F4
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Laura:: @ 81FC8FB
	trainerbattle_single TRAINER_LAURA, DewfordTown_Gym_Text_LauraIntro, DewfordTown_Gym_Text_LauraDefeat, DewfordTown_Gym_EventScript_LauraBrightenRoom
	msgbox DewfordTown_Gym_Text_LauraPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_LauraBrightenRoom:: @ 81FC916
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Brenden:: @ 81FC91D
	trainerbattle_single TRAINER_BRENDEN, DewfordTown_Gym_Text_BrendenIntro, DewfordTown_Gym_Text_BrendenDefeat, DewfordTown_Gym_EventScript_BrendenBrightenRoom
	msgbox DewfordTown_Gym_Text_BrendenPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_BrendenBrightenRoom:: @ 81FC938
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Cristian:: @ 81FC93F
	trainerbattle_single TRAINER_CRISTIAN, DewfordTown_Gym_Text_CristianIntro, DewfordTown_Gym_Text_CristianDefeat, DewfordTown_Gym_EventScript_CristianBrightenRoom
	msgbox DewfordTown_Gym_Text_CristianPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_CristianBrightenRoom:: @ 81FC95A
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Lilith:: @ 81FC961
	trainerbattle_single TRAINER_LILITH, DewfordTown_Gym_Text_LilithIntro, DewfordTown_Gym_Text_LilithDefeat, DewfordTown_Gym_EventScript_LilithBrightenRoom
	msgbox DewfordTown_Gym_Text_LilithPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_LilithBrightenRoom:: @ 81FC97C
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_GymGuide:: @ 81FC983
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_DEWFORD_GYM, DewfordTown_Gym_EventScript_GymGuidePostVictory
	msgbox DewfordTown_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_GymGuidePostVictory:: @ 81FC998
	msgbox DewfordTown_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_LeftGymStatue:: @ 81FC9A2
	lockall
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
	goto DewfordTown_Gym_EventScript_GymStatue
	end

DewfordTown_Gym_EventScript_RightGymStatue:: @ 81FC9B2
	lockall
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
	goto DewfordTown_Gym_EventScript_GymStatue
	end

DewfordTown_Gym_EventScript_GymStatueCertified:: @ 81FC9C2
	msgbox DewfordTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Gym_EventScript_GymStatue:: @ 81FC9CC
	msgbox DewfordTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Gym_Text_GymGuideAdvice: @ 81FC9D6
	.string "잘 있었나!!\n"
	.string "챔피언을 노리는 {PLAYER}!!\p"
	.string "무로마을 체육관 관장 철구는\n"
	.string "격투타입 포켓몬을 쓴다!\p"
	.string "노말타입으로 도전하면\n"
	.string "뼈아픈 일격을 맞을 테니까\l"
	.string "조심하는 게 좋겠지!\p"
	.string "게다가! 이 체육관 안은\n"
	.string "바다 깊은 곳처럼 어둡다!\p"
	.string "하지만! 트레이너를 한 명씩 쓰러뜨릴수록\n"
	.string "점점 밝아지니까 괜찮을 거야!\p"
	.string "그럼 힘내라고-!!$"
	// げんき しとぉや!!ｎ
	// チャンピオンを めざす §あ!!ｐ
	// ムロタウン ジムの リ-ダ- トウキはｎ
	// かくとうタイプ ポケモンの つかいてだ!ｐ
	// ノ-マルタイプで むかうとｎ
	// きびしぃ- いちげきを くらうからｌ
	// きを つけたほうが いいぞ!ｐ
	// しかも! この ジムの なかはｎ
	// うみのそこ みたいに くらいんだ!ｐ
	// でも! トレ-ナ-を ひとり たおすごとにｎ
	// だんだん あかるく なって いくぞ!ｐ
	// じゃ きばってこォ-!!

DewfordTown_Gym_Text_GymGuidePostVictory: @ 81FCB5C
	.string "오오! 제법 밝아졌구나!\p"
	.string "네 미래도 밝겠지!$"
	// うおォ! ずいぶん あかるく なったな!ｐ
	// きみの みらいも あかるいぞ!

DewfordTown_Gym_Text_TakaoIntro: @ 81FCB9F
	.string "힘이야말로 정의다!\n"
	.string "이야아아-압!!$"
	// ちから こそ せいぎっ!ｎ
	// ドリャ-ッ!!

DewfordTown_Gym_Text_TakaoDefeat: @ 81FCBB8
	.string "힘이 부족했다...!$"
	// ちからぶそく だった……!

DewfordTown_Gym_Text_TakaoPostBattle: @ 81FCBCA
	.string "부드러움이 강함을 제압한다!\n"
	.string "훌륭한 배틀이었다!$"
	// じゅう よく ごうを せいす!ｎ
	// みごとな たたかいぶり だった!

DewfordTown_Gym_Text_JocelynIntro: @ 81FCC0A
	.string "철구님과 배틀할 것까지도 없어!\n"
	.string "내가 널 쓰러뜨릴 거니까!$"
	// トウキさまと たたかうまでも ないわ!ｎ
	// わたしが たおして あげる!

DewfordTown_Gym_Text_JocelynDefeat: @ 81FCC45
	.string "이럴 수가...\n"
	.string "이렇게 간단히 당하다니$"
	// まさか……ｎ
	// こんなに かんたんに やられるなんて

DewfordTown_Gym_Text_JocelynPostBattle: @ 81FCC6B
	.string "이 패배가 헛되지 않도록\n"
	.string "더욱 특훈하겠어!\p"
	.string "그리고 언젠가 체육관 관장이...\p"
	.string "아니 포켓몬리그의\n"
	.string "챔피언이 될 거야!$"
	// この まけを むだに しないためｎ
	// もっと とっくん する!ｐ
	// そして いつかは ジムリ-ダ-に……ｐ
	// いえ ポケモンリ-グのｎ
	// チャンピオンに なるわよ!

DewfordTown_Gym_Text_LauraIntro: @ 81FCD01
	.string "날 쉽게 보지 마!\n"
	.string "엉엉 울게 돼도 난 모른다!$"
	// あたしを あまく みない ことね!ｎ
	// ないても しらないわよ!

DewfordTown_Gym_Text_LauraDefeat: @ 81FCD3C
	.string "으아---앙!\n"
	.string "져버렸어---엉!$"
	// わぁ---ん!ｎ
	// まけた---っ!

DewfordTown_Gym_Text_LauraPostBattle: @ 81FCD4F
	.string "어둠 속에서 배틀함으로써\n"
	.string "정신을 단련하고 있어\p"
	.string "하지만 너무 어두워서\n"
	.string "철구님의 얼굴을 못 봐...$"
	// くらやみの なかで たたかうことでｎ
	// こころを きたえるのｐ
	// でも まっくら だからｎ
	// トウキさまの おかおを みられない……

DewfordTown_Gym_Text_LilithIntro: @ 81FCDB8
	.string "우후후...!\n"
	.string "어두워서 헤메고 있니?$"
	// うふふ……!ｎ
	// くらくて まよっているの かな?

DewfordTown_Gym_Text_LilithDefeat: @ 81FCDE5
	.string "뭐야 정말\n"
	.string "난 몰라!$"
	// なによ もうｎ
	// しらない!

DewfordTown_Gym_Text_LilithPostBattle: @ 81FCE08
	.string "너 같은 건 이대로 헤매서\n"
	.string "입구로 돌아가 버리라고!$"
	// あなた なんて このまま まよってｎ
	// いりぐちに もどっちゃえば い-のよ!

DewfordTown_Gym_Text_BrendenIntro: @ 81FCE48
	.string "바다 사나이의 의지를\n"
	.string "보여주마!$"
	// うみの おとこの いじをｎ
	// みせつけて やるぜぃ!

DewfordTown_Gym_Text_BrendenDefeat: @ 81FCE75
	.string "어떻게 된 거지!\n"
	.string "딴 사람도 아닌 내가...$"
	// どうしたぃ!ｎ
	// おれと した ことが……

DewfordTown_Gym_Text_BrendenPostBattle: @ 81FCEAB
	.string "오우! 너라면\n"
	.string "체육관 관장한테 도전해도 되겠는데!$"
	// おう! あんたならｎ
	// ジムリ-ダ-に いどむに ふさわしいぜぃ!

DewfordTown_Gym_Text_CristianIntro: @ 81FCEDC
	.string "여길 지나가려면\n"
	.string "날 쓰러뜨려라!$"
	// ここを とおる ならｎ
	// この わしを たおしてから じゃ!

DewfordTown_Gym_Text_CristianDefeat: @ 81FCF0A
	.string "으-음!\n"
	.string "엄청 강하군...!$"
	// むう-ん!ｎ
	// すごく つよい……!

DewfordTown_Gym_Text_CristianPostBattle: @ 81FCF26
	.string "내가 졌다!\n"
	.string "힘내서 배지까지 얻어가라고!$"
	// わしの まけじゃ!ｎ
	// がんばって バッジ とってこいよ!

DewfordTown_Gym_Text_BrawlyIntro: @ 81FCF44
	.string "난 무로마을 포켓몬체육관\n"
	.string "관장 철구!\p"
	.string "이 주변의\n"
	.string "거친 파도를 버티면서...\p"
	.string "어두운 동굴에서\n"
	.string "수행하고 있지!\p"
	.string "나에게 도전하려고 하는\n"
	.string "너의 실력...\l"
	.string "어느 정도인지 보여줘야겠어!$"
	// ボクは ムロ ポケモンジムｎ
	// リ-ダ-の トウキ!ｐ
	// この あたりのｎ
	// はげしい なみに もまれ……ｐ
	// くらい どうくつでｎ
	// しゅぎょう して いるのさ!ｐ
	// ボクに ちょうせん しよう というｎ
	// キミの じつりょく……ｌ
	// どれほどの ものか みせて もらうよ!

DewfordTown_Gym_Text_BrawlyDefeat: @ 81FD008
	.string "으-음 예상했던 것보다\n"
	.string "넌 빅 웨이브구나!\p"
	.string "알았어!\n"
	.string "이 배지를 가지고 가!$"
	// うう-ん よそう していたよりｎ
	// キミは ビッグウェ-ブ!ｐ
	// わかった!ｎ
	// この バッジを もっていきな!

DewfordTown_Gym_Text_ReceivedKnuckleBadge: @ 81FD07D
	.string "{PLAYER}{K_EUNNEUN} 철구에게\n"
	.string "너클배지를 받았다!$"
	// §あは トウキからｎ
	// ナックルバッジを もらった!

DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis: @ 81FD0A8
	.string "너클배지에는\n"
	.string "레벨 30까지의 포켓몬이라면\p"
	.string "다른 사람에게 받은 포켓몬이라도\n"
	.string "얌전하게 만드는 효과가 있어!\p"
	.string "그리고 배틀 외에서도\n"
	.string "비전기술인 플래시를 쓸 수 있지!\p"
	.string "이 기술머신\n"
	.string "괜찮으면 써봐!$"
	// ナックルバッジにはｎ
	// レベル30までの ポケモンならｌ
	// ひとから もらった ポケモンでもｌ
	// すなおに する こうかが ある!ｐ
	// それに たたかって いなくてもｎ
	// ひでんわざの フラッシュを つかえる!ｐ
	// この わざマシンｎ
	// よかったら つかいな!

DewfordTown_Gym_Text_ExplainBulkUp: @ 81FD181
	.string "그 기술머신08에는\n"
	.string "벌크업이 들어 있어!\p"
	.string "공격력과 방어력을\n"
	.string "올려주는 기술이지!\p"
	.string "...... ...... ......$"
	// その わざマシン08 にはｎ
	// ビルドアップが はいっている!ｐ
	// こうげきりょくと ぼうぎょりょくをｎ
	// あげる わざ なのさ!ｐ
	// …… …… ……

DewfordTown_Gym_Text_RegisteredBrawly: @ 81FD1E0
	.string "체육관 관장 철구를\n"
	.string "포켓내비에 등록했다!$"
	// ジムリ-ダ- トウキをｎ
	// ポケナビに とうろく した!

DewfordTown_Gym_Text_BrawlyPostBattle: @ 81FD20D
	.string "네 재능은\n"
	.string "언젠가 거대한 파도가 되어\p"
	.string "포켓몬 트레이너들 사이에서\n"
	.string "놀라움의 태풍을 불러일으키겠지!$"
	// キミの さいのうはｎ
	// いつのひか おおきな なみと なってｐ
	// ポケモン トレ-ナ-たちの あいだにｎ
	// おどろきの あらしを まきおこすだろう!

DewfordTown_Gym_Text_GymStatue: @ 81FD272
	.string "무로마을 포켓몬체육관$"
	// ムロタウン ポケモンジム

DewfordTown_Gym_Text_GymStatueCertified: @ 81FD28B
	.string "무로마을 포켓몬체육관\p"
	.string "철구 인정 트레이너!\n"
	.string "{PLAYER}$"
	// ムロタウン ポケモンジムｐ
	// トウキ にんてい トレ-ナ-!ｎ
	// §あ

DewfordTown_Gym_Text_BrawlyPreRematch: @ 81FD2C4
	.string "철구: 파도는 한번 물러나도\n"
	.string "언젠가 반드시 바닷가로 돌아와\p"
	.string "넌 빅 웨이브니까\n"
	.string "분명 다시 올 줄 알았어!\p"
	.string "자 얼마나 강해졌는지\n"
	.string "나한테 보여 봐!$"
	// トウキ『なみというのは いちど ひいてもｎ
	// いつか かならず はまべに もどってくるｐ
	// キミほどの ビッグウェ-ブだｎ
	// きっと また くると おもっていたよ!ｐ
	// さあ どれほど たかさを ましたのかｎ
	// ボクに みせてくれ!

DewfordTown_Gym_Text_BrawlyRematchDefeat: @ 81FD367
	.string "와-우!\n"
	.string "네게 삼켜져 버렸는걸!$"
	// わ-おっ!ｎ
	// キミに のみこまれそうだ!

DewfordTown_Gym_Text_BrawlyPostRematch: @ 81FD37B
	.string "철구: 역시 포켓몬 승부는\n"
	.string "끝을 알 수 없을 정도로 심오해!\l"
	.string "마치 호연지방의 바다 같지!$"
	// トウキ『やっぱり ポケモン しょうぶはｎ
	// そこが みえないほど ふかく ひろい!ｌ
	// まるで ホウエンの うみの ようだね!

DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons: @ 81FD3DE
	.string "철구: 파도는 한번 물러나도\n"
	.string "언젠가 반드시 바닷가로 돌아오지\p"
	.string "넌 빅 웨이브니까\n"
	.string "분명 다시 올 줄 알았어!\p"
	.string "...어라? 싸울 수 있는 포켓몬이\n"
	.string "한 마리밖에 없구나\p"
	.string "미안하지만 두 마리 이상의\n"
	.string "포켓몬을 데리고 다시 와줘$"
	// トウキ『なみというのは いちど ひいてもｎ
	// いつか かならず はまべに もどってくるｐ
	// キミほどの ビッグウェ-ブだｎ
	// きっと また くると おもっていたよ!ｐ
	// ……あれ? たたかえる ポケモンをｎ
	// 1ひきしか もっていないんだねｐ
	// すまないけど 2ひき いじょうのｎ
	// ポケモンを もって また きてくれよ
