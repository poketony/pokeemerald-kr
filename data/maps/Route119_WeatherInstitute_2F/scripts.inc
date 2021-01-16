.set LOCALID_GRUNT_1, 1
.set LOCALID_GRUNT_2, 2
.set LOCALID_SHELLY, 3
.set LOCALID_SCIENTIST, 5
.set LOCALID_GRUNT_3, 7
.set LOCALID_GRUNT_4, 8

Route119_WeatherInstitute_2F_MapScripts:: @ 826FF1E
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_WeatherInstitute_2F_OnTransition
	.byte 0

Route119_WeatherInstitute_2F_OnTransition: @ 826FF24
	compare VAR_WEATHER_INSTITUTE_STATE, 0
	call_if_eq Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaHere
	compare VAR_WEATHER_INSTITUTE_STATE, 1
	call_if_eq Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaGone
	call_if_set FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_2F_EventScript_SetScientistPosGameClear
	end

Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaHere:: @ 826FF44
	setobjectxyperm LOCALID_SCIENTIST, 1, 6
	setobjectmovementtype LOCALID_SCIENTIST, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaGone:: @ 826FF50
	setobjectxyperm LOCALID_SCIENTIST, 4, 6
	setobjectmovementtype LOCALID_SCIENTIST, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_2F_EventScript_SetScientistPosGameClear:: @ 826FF5C
	setobjectxyperm LOCALID_SCIENTIST, 2, 2
	setobjectmovementtype LOCALID_SCIENTIST, MOVEMENT_TYPE_FACE_UP
	return

Route119_WeatherInstitute_2F_EventScript_Grunt5:: @ 826FF68
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_5, Route119_WeatherInstitute_2F_Text_Grunt5Intro, Route119_WeatherInstitute_2F_Text_Grunt5Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Grunt2:: @ 826FF7F
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_2, Route119_WeatherInstitute_2F_Text_Grunt2Intro, Route119_WeatherInstitute_2F_Text_Grunt2Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Grunt3:: @ 826FF96
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_3, Route119_WeatherInstitute_2F_Text_Grunt3Intro, Route119_WeatherInstitute_2F_Text_Grunt3Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Shelly:: @ 826FFAD
	trainerbattle_single TRAINER_SHELLY_WEATHER_INSTITUTE, Route119_WeatherInstitute_2F_Text_ShellyIntro, Route119_WeatherInstitute_2F_Text_ShellyDefeat, Route119_WeatherInstitute_2F_EventScript_ShellyDefeated
	msgbox Route119_WeatherInstitute_2F_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_ShellyDefeated:: @ 826FFC8
	msgbox Route119_WeatherInstitute_2F_Text_ShellyPostBattle, MSGBOX_DEFAULT
	closemessage
	addobject LOCALID_GRUNT_3
	applymovement LOCALID_GRUNT_3, Route119_WeatherInstitute_2F_Movement_GruntApproachShelly
	applymovement OBJ_EVENT_ID_PLAYER, Route119_WeatherInstitute_2F_Movement_ShovePlayerOutOfWay
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_Text_TeamMagmaJustPassedBy, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_SHELLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SHELLY, Common_Movement_Delay48
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_Text_WeHaveToHurryToMtPyre, MSGBOX_DEFAULT
	closemessage
	setvar VAR_WEATHER_INSTITUTE_STATE, 1
	clearflag FLAG_HIDE_WEATHER_INSTITUTE_2F_WORKERS
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_ROUTE_119_TEAM_AQUA
	setflag FLAG_HIDE_WEATHER_INSTITUTE_2F_AQUA_GRUNT_M
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_SHELLY
	removeobject LOCALID_GRUNT_4
	removeobject LOCALID_GRUNT_3
	applymovement OBJ_EVENT_ID_PLAYER, Route119_WeatherInstitute_2F_Movement_PlayerReturnToPosition
	waitmovement 0
	fadescreen FADE_FROM_BLACK
	applymovement LOCALID_SCIENTIST, Route119_WeatherInstitute_2F_Movement_ScientistApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_SCIENTIST
	goto Route119_WeatherInstitute_2F_EventScript_ReceiveCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastform:: @ 827004D
	msgbox Route119_WeatherInstitute_2F_Text_ThanksPleaseTakePokemon, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, SPECIES_CASTFORM
	givemon SPECIES_CASTFORM, 25, ITEM_MYSTIC_WATER
	compare VAR_RESULT, 0
	goto_if_eq Route119_WeatherInstitute_2F_EventScript_ReceiveCastformParty
	compare VAR_RESULT, 1
	goto_if_eq Route119_WeatherInstitute_2F_EventScript_ReceiveCastformPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastformParty:: @ 8270085
	call Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastformPC:: @ 82700AD
	call Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route119_WeatherInstitute_2F_EventScript_SendCastformToPC
	call Common_EventScript_NameReceivedBoxMon
	goto Route119_WeatherInstitute_2F_EventScript_SendCastformToPC
	end

Route119_WeatherInstitute_2F_EventScript_SendCastformToPC:: @ 82700D0
	call Common_EventScript_TransferredToPC
	goto Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare:: @ 82700DB
	playfanfare MUS_OBTAIN_ITEM
	message Route119_WeatherInstitute_2F_Text_PlayerReceivedCastform
	waitmessage
	waitfanfare
	bufferspeciesname 0, SPECIES_CASTFORM
	return

Route119_WeatherInstitute_2F_EventScript_ExplainCastform:: @ 82700EA
	msgbox Route119_WeatherInstitute_2F_Text_PokemonChangesWithWeather, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_CASTFORM
	release
	end

Route119_WeatherInstitute_2F_EventScript_ScientistMentionWeather:: @ 82700F7
	goto_if_set FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_2F_EventScript_TryStartAbnormalWeather
	msgbox Route119_WeatherInstitute_2F_Text_ChangingWeatherRidiculous, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_TryStartAbnormalWeather:: @ 827010A
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated
	call_if_set FLAG_DEFEATED_GROUDON, Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated
	compare VAR_0x8004, 2  @ Both defeated
	goto_if_eq Route119_WeatherInstitute_2F_EventScript_NoAbnormalWeather
	call_if_unset FLAG_TEMP_2, Route119_WeatherInstitute_2F_EventScript_CreateAbnormalWeather
	specialvar VAR_RESULT, GetAbnormalWeatherMapNameAndType
	compare VAR_RESULT, 1
	goto_if_eq Route119_WeatherInstitute_2F_EventScript_KyogreWeather
	msgbox Route119_WeatherInstitute_2F_Text_GroudonWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_KyogreWeather:: @ 827014F
	msgbox Route119_WeatherInstitute_2F_Text_KyogreWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_CreateAbnormalWeather:: @ 8270159
	special CreateAbnormalWeatherEvent
	setflag FLAG_TEMP_2
	return

Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated:: @ 8270160
	addvar VAR_0x8004, 1
	return

Route119_WeatherInstitute_2F_EventScript_NoAbnormalWeather:: @ 8270166
	msgbox Route119_WeatherInstitute_2F_Text_NoAbnormalWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_Movement_GruntApproachShelly: @ 8270170
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route119_WeatherInstitute_2F_Movement_ShovePlayerOutOfWay: @ 827017C
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	ride_water_current_up
	walk_in_place_fastest_down
	step_end

Route119_WeatherInstitute_2F_Movement_PlayerReturnToPosition: @ 8270184
	slide_down
	walk_in_place_fastest_left
	step_end

Route119_WeatherInstitute_2F_Movement_ScientistApproachPlayer: @ 8270187
	walk_right
	walk_right
	walk_right
	step_end

Route119_WeatherInstitute_2F_EventScript_WeatherScientist:: @ 827018B
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CASTFORM, Route119_WeatherInstitute_2F_EventScript_ScientistMentionWeather
	goto Route119_WeatherInstitute_2F_EventScript_ReceiveCastform
	end

Route119_WeatherInstitute_2F_Text_Grunt2Intro: @ 827019C
	.string "이 연구소에서 만들어진\n"
	.string "포켓몬은 날씨와 관계가 있대서\l"
	.string "받아 가려고 온 거야!$"
	// この けんきゅうじょで うみだされたｎ
	// ポケモンは てんきと かんけいある ってｌ
	// きいたから いただきに きたのさ!

Route119_WeatherInstitute_2F_Text_Grunt2Defeat: @ 8270208
	.string "이런 꼬맹이에게 방해당한 건가?!$"
	// こんな こどもに じゃま されるのか!?

Route119_WeatherInstitute_2F_Text_Grunt2PostBattle: @ 827022B
	.string "여기서 만들어진 포켓몬이\n"
	.string "날씨를 자유롭게 조종할 수 있다면\l"
	.string "아쿠아단에게 반드시 필요하다!$"
	// ここで うみだされた ポケモンがｎ
	// もし てんきを じゆうに あやつれるならｌ
	// ぜったい アクアだんに ひつよう だぜ!

Route119_WeatherInstitute_2F_Text_Grunt3Intro: @ 8270292
	.string "우리들은 아쿠아단!\n"
	.string "희귀한 게 있는 곳이라면\l"
	.string "어디든 나타난다!$"
	// おれたち アクアだん!ｎ
	// めずらしい ものが ある ところならｌ
	// どこにでも あらわれる!

Route119_WeatherInstitute_2F_Text_Grunt3Defeat: @ 82702CE
	.string "이거 큰일이군!$"
	// こいつは まいった!

Route119_WeatherInstitute_2F_Text_Grunt3PostBattle: @ 82702DA
	.string "아쿠아단의 이상도 모르면서\n"
	.string "방해하지 말라고!$"
	// アクアだんの りそうを しらないくせにｎ
	// じゃま するんじゃ ないよ!

Route119_WeatherInstitute_2F_Text_Grunt5Intro: @ 8270335
	.string "당신도 날씨와 관계있는\n"
	.string "포켓몬을 찾으러 온 거야?\p"
	.string "안 돼!\n"
	.string "우리들이 먼저 가져갈 거야!$"
	// あなたも てんきに かんけいのあるｎ
	// ポケモンを さがしに きたの?ｐ
	// だめよ!ｎ
	// あたしたちが さきに いただくんだから!

Route119_WeatherInstitute_2F_Text_Grunt5Defeat: @ 827039F
	.string "음- 더 이상 포켓몬이-$"
	// んも- ポケモンが-

Route119_WeatherInstitute_2F_Text_Grunt5PostBattle: @ 82703C0
	.string "흥 좋아!\p"
	.string "우리들이 정말로 노리는 건\n"
	.string "다른 곳에... 이히히히$"
	// ふん いいさ!ｐ
	// あたしたちが ほんとうに ほしいのはｎ
	// もっと ほかに…… イヒヒヒ

Route119_WeatherInstitute_2F_Text_ShellyIntro: @ 8270409
	.string "오-호호!\p"
	.string "우리들 아쿠아단의\n"
	.string "방해를 할 셈이야?!\p"
	.string "정말 무서운 걸 모르는 건지\n"
	.string "그냥 어리석은 건지...\p"
	.string "너무 귀여워서 얄미워!\n"
	.string "해치워 줄게!$"
	// オ-ッホッホ!ｐ
	// われわれ アクアだんのｎ
	// じゃまを しようと いうの!?ｐ
	// もう こわいものしらず といおうかｎ
	// ただの おろかものと いおうか……ｐ
	// かわいすぎて にくらしく なっちゃう!ｎ
	// やっつけて あげるわね!

Route119_WeatherInstitute_2F_Text_ShellyDefeat: @ 82704BD
	.string "오-호호!\n"
	.string "너무 강해서 얄미운 걸!$"
	// オ-ッホッホ!ｎ
	// つよくて にくらしく なっちゃうわ!

Route119_WeatherInstitute_2F_Text_ShellyPostBattle: @ 82704E4
	.string "마그마단만으로도 귀찮은데\n"
	.string "넌 또 왜 우리 주변을\l"
	.string "서성거리고 있는 거야!$"
	// マグマだん だけでも めざわり なのにｎ
	// あなた どうして わたしたちの まわりをｌ
	// チョロチョロ かぎまわって いるの!

Route119_WeatherInstitute_2F_Text_TeamMagmaJustPassedBy: @ 8270568
	.string "큰일입니다!\p"
	.string "지금 막 마그마단 녀석들이\n"
	.string "날씨 연구소를 지나\p"
	.string "송화산 쪽으로\n"
	.string "향하고 있습니다!$"
	// たいへんです!ｐ
	// たったいま マグマだんの れんちゅうがｎ
	// てんきけんきゅうじょを つうかしてｌ
	// おくりびやま ほうめんにｌ
	// むかって いきました!

Route119_WeatherInstitute_2F_Text_WeHaveToHurryToMtPyre: @ 82705DD
	.string "뭐라고?!\p"
	.string "이러고 있을 때가 아냐\n"
	.string "우리들도 송화산으로 서둘러 가자!\p"
	.string "오-호호!\n"
	.string "마그마단 놈들 기다려라-!$"
	// なんですって!ｐ
	// え-い こうしちゃ いられないｎ
	// われわれも おくりびやまに いそぐわよ!ｐ
	// オ-ッホッホ!ｎ
	// マグマだんめ まってなさ-い!

Route119_WeatherInstitute_2F_Text_ThanksPleaseTakePokemon: @ 8270650
	.string "고맙다\n"
	.string "자네 덕분에 살았어\p"
	.string "감사의 표시라고 하기엔 좀 그렇다만\n"
	.string "이 포켓몬을 받아주게나$"
	// ありがとうよｎ
	// きみの おかげで たすかったよｐ
	// おれいと いっては なんだがｎ
	// この ポケモンを もらって おくれ

@ Unused
Route119_WeatherInstitute_2F_Text_NoRoomForPokemon: @ 82706B2
	.string "그 이상\n"
	.string "포켓몬을 지닐 수 없나 보구나$"
	// あら? それいじょうｎ
	// ポケモンを もてないようだよ

Route119_WeatherInstitute_2F_Text_PlayerReceivedCastform: @ 82706E8
	.string "{PLAYER}{K_EUNNEUN}"
	.string "캐스퐁을 받았다!$"
	// §あはｎ
	// ポワルンを もらった!

Route119_WeatherInstitute_2F_Text_PokemonChangesWithWeather: @ 82706FE
	.string "그 녀석은 그 당시의 날씨에 따라\n"
	.string "모습을 바꾸는 포켓몬이란다\p"
	.string "연구소에는 많이 있으니까\n"
	.string "사양 말고 받아주렴$"
	// そいつは そのときの てんきに よってｎ
	// すがたを かえる ポケモン なんだよｐ
	// けんきゅうじょ には たくさん いるからｎ
	// えんりょせずに もらって おくれよ

Route119_WeatherInstitute_2F_Text_ChangingWeatherRidiculous: @ 827077E
	.string "나도 오랫동안\n"
	.string "비를 연구하고 있지만\l"
	.string "날씨를 자유자재로 바꾼다니\l"
	.string "인간에게는 무리야$"
	// わたしも ながい あいだｎ
	// あめの けんきゅうを してるがｌ
	// てんきを じゆうじざいに かえるだなんてｌ
	// にんげんには むりな はなし だよ

Route119_WeatherInstitute_2F_Text_GroudonWeather: @ 82707F1
	.string "저는 호연지방의 날씨를\n"
	.string "관측하고 있습니다\p"
	.string "현재 {STR_VAR_1}에서\n"
	.string "가뭄이 발생 중입니다!\p"
	.string "그렇다는 건\n"
	.string "{STR_VAR_1}의 어딘가에...?$"
	// わたしは ホウエンちほうの てんきをｎ
	// かんそく していますｐ
	// げんざい §いでｎ
	// ひでりが はっせい しています!ｐ
	// ということはｎ
	// §いの どこかに……?

Route119_WeatherInstitute_2F_Text_KyogreWeather: @ 8270873
	.string "저는 호연지방의 날씨를\n"
	.string "관측하고 있습니다\p"
	.string "현재 {STR_VAR_1}에서\n"
	.string "폭우가 발생 중입니다!\p"
	.string "그렇다는 건\n"
	.string "{STR_VAR_1}의 어딘가에...?$"
	// わたしは ホウエンちほうの てんきをｎ
	// かんそく していますｐ
	// げんざい §いでｎ
	// はげしい おおあめが ふっています!ｐ
	// ということはｎ
	// §いの どこかに……?

Route119_WeatherInstitute_2F_Text_NoAbnormalWeather: @ 82708FC
	.string "이상 기후는\n"
	.string "이제 관측되지 않습니다\p"
	.string "가끔씩 비가 내리지만\n"
	.string "그건 단비라고 할 수 있겠죠!$"
	// いじょう きしょうはｎ
	// もう かんそく されなく なりましたｐ
	// たまに あめが ふってもｎ
	// それは めぐみのあめと いえるでしょう!

