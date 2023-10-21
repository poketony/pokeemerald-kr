.set LOCALID_LITTLE_BOY, 5

Route119_WeatherInstitute_1F_MapScripts:: @ 826FA86
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_WeatherInstitute_1F_OnTransition
	.byte 0

Route119_WeatherInstitute_1F_OnTransition: @ 826FA8C
	compare VAR_WEATHER_INSTITUTE_STATE, 0
	call_if_eq Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos
	end

Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos:: @ 826FA98
	setobjectxyperm LOCALID_LITTLE_BOY, 0, 5
	setobjectmovementtype LOCALID_LITTLE_BOY, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_1F_EventScript_LittleBoy:: @ 826FAA4
	lock
	faceplayer
	special GetPlayerBigGuyGirlString
	compare VAR_WEATHER_INSTITUTE_STATE, 0
	goto_if_eq Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere
	msgbox Route119_WeatherInstitute_1F_Text_WowYoureStrong, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere:: @ 826FABE
	msgbox Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker1:: @ 826FAC8
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_1F_EventScript_StudyingRain
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	call_if_set FLAG_DEFEATED_GROUDON, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	compare VAR_0x8004, 2  @ Both defeated
	goto_if_eq Route119_WeatherInstitute_1F_EventScript_StudyingRain
	msgbox Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated:: @ 826FAFF
	addvar VAR_0x8004, 1
	return

Route119_WeatherInstitute_1F_EventScript_StudyingRain:: @ 826FB05
	msgbox Route119_WeatherInstitute_1F_Text_ProfStudyingRain, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker2:: @ 826FB0F
	msgbox Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo, MSGBOX_NPC
	end

Route119_WeatherInstitute_1F_EventScript_Bed:: @ 826FB18
	lockall
	msgbox Route119_WeatherInstitute_1F_Text_TakeRestInBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	releaseall
	end

Route119_WeatherInstitute_1F_EventScript_Grunt1:: @ 826FB29
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_1, Route119_WeatherInstitute_1F_Text_Grunt1Intro, Route119_WeatherInstitute_1F_Text_Grunt1Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_EventScript_Grunt4:: @ 826FB40
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_4, Route119_WeatherInstitute_1F_Text_Grunt4Intro, Route119_WeatherInstitute_1F_Text_Grunt4Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_Text_Grunt1Intro: @ 826FB57
	.string "리더가 이곳의 연구에\n"
	.string "흥미가 있으셔서\l"
	.string "우리들을 보낸 거다! 방해하지 마!$"
	// リ-ダ-が ここでの けんきゅうにｎ
	// きょうみを もったらしくてｌ
	// おれらを よこしたんだ! ジャマするな!

Route119_WeatherInstitute_1F_Text_Grunt1Defeat: @ 826FBBB
	.string "젠장-\n"
	.string "어린애한테 졌다...$"
	// くそ-ｎ
	// こどもに まけた……

Route119_WeatherInstitute_1F_Text_Grunt1PostBattle: @ 826FBD7
	.string "리더는 뭐든지 알고 있어...\p"
	.string "하지만 뭘 생각하고 있는 건지\n"
	.string "조무래기인 우리한텐 상상도 안 가$"
	// リ-ダ-は なんでも しっている……ｐ
	// しかし なにを かんがえて いるのかｎ
	// したっぱの おれらには さっぱりだ

Route119_WeatherInstitute_1F_Text_Grunt4Intro: @ 826FC34
	.string "어라?\n"
	.string "왜 여기에 어린애가 있는 거지?$"
	// あら?ｎ
	// どうして ここに こどもが いるのかしら?

Route119_WeatherInstitute_1F_Text_Grunt4Defeat: @ 826FC52
	.string "어라-\n"
	.string "져버린 건가-!?$"
	// あら-ｎ
	// まけちゃった-!?$

Route119_WeatherInstitute_1F_Text_Grunt4PostBattle: @ 826FC60
	.string "어라라...\n"
	.string "어린애한테 진 걸 들키면 혼날 거야...\p"
	.string "침대에서 자는 척이라도 할까?$"
	// あらら……ｎ
	// こどもに まけたら おこられちゃう……ｐ
	// ベッドで ねてようかしら?

Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs: @ 826FCB7
	.string "내가 침대에서 자는 동안\n"
	.string "모두 2층으로 가버렸어$"
	// ぼくが ベッドで ねてる あいだにｎ
	// みんな 2かいに いっちゃったよ

Route119_WeatherInstitute_1F_Text_WowYoureStrong: @ 826FCE5
	.string "{K_BOY_CALL} 강하네!\p"
	.string "나도 {K_BOY_CALL} 같은\n"
	.string "포켓몬 트레이너가 되고 싶어!$"
	// §い つよいんだね!ｐ
	// ぼくも §い みたいなｎ
	// ポケモントレ-ナ-に なりたいや!

Route119_WeatherInstitute_1F_Text_ProfStudyingRain: @ 826FD2E
	.string "박사님은 비를 정말 좋아해요\p"
	.string "그렇지만 계속 비가 내리면\n"
	.string "곤란해지는 사람도 있죠\p"
	.string "그래서 박사님은\n"
	.string "이 비를 무언가로\l"
	.string "바꿔 쓸 수 없을까 하고\l"
	.string "연구하고 있어요$"
	// はかせは あめが だいすき なのですｐ
	// ですが あめが ふりつづくとｎ
	// こまってしまう ひとも いるわけですｐ
	// そこで はかせはｎ
	// この あめを なにかに つかえないかｌ
	// けんきゅう なさっているのです

Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather: @ 826FDE8
	.string "이 연구소의 2층에서는\n"
	.string "호연지방의 날씨\l"
	.string "변화를 조사하고 있습니다\p"
	.string "최근에 다시 이곳저곳에서\n"
	.string "일시적인 가뭄이나 폭우가\l"
	.string "관측되고 있는 듯합니다만...$"
	// この けんきゅうじょの 2かいではｎ
	// ホウエンちほうの てんきのｌ
	// うつりかわりを しらべていますｐ
	// さいきん また あちこちでｎ
	// いちじてきな ひでりや おおあめがｌ
	// かんそく されている ようですが……

Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo: @ 826FE94
	.string "안녕하세요!\n"
	.string "당신 덕분에 살았습니다!\l"
	.string "그건 그렇고...\p"
	.string "아쿠아단 녀석들은\n"
	.string "무슨 짓을 하려고 했던 걸까요?$"
	// やあ!ｎ
	// あなたの おかげで たすかりましたよ!ｌ
	// それにしても……ｐ
	// アクアだんの れんちゅうはｎ
	// なにを するつもり だったのでしょう?

Route119_WeatherInstitute_1F_Text_TakeRestInBed: @ 826FEFC
	.string "침대가 있다...\n"
	.string "조금 쉬었다 가자$"
	// ベッドが ある……ｎ
	// やすんでいこう

