.set LOCALID_WALLACE, 1
.set LOCALID_RIVAL, 2
.set LOCALID_BIRCH, 3

EverGrandeCity_ChampionsRoom_MapScripts:: @ 82289EF
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_ChampionsRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_ChampionsRoom_OnFrame
	.byte 0

EverGrandeCity_ChampionsRoom_OnTransition: @ 82289FF
	call Common_EventScript_SetupRivalGfxId
	end

EverGrandeCity_ChampionsRoom_OnWarp: @ 8228A05
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth:: @ 8228A0F
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_ChampionsRoom_OnFrame: @ 8228A14
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_EnterRoom
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_EnterRoom:: @ 8228A1E
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace
	waitmovement 0
	setvar VAR_TEMP_1, 1
	goto EverGrandeCity_ChampionsRoom_EventScript_Wallace
    releaseall
    end

EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace: @ 8228A42
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_EventScript_Wallace:: @ 8228A45
	playbgm MUS_ENCOUNTER_CHAMPION, 0
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLACE, EverGrandeCity_ChampionsRoom_Text_Defeat
	goto EverGrandeCity_ChampionsRoom_EventScript_Defeated
	end

EverGrandeCity_ChampionsRoom_EventScript_Defeated:: @ 8228A61
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, 0
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, 0
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	compare VAR_RESULT, FEMALE
	call_if_eq EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq EverGrandeCity_ChampionsRoom_EventScript_MayAdvice
	compare VAR_RESULT, FEMALE
	goto_if_eq EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic:: @ 8228ABC
	playbgm MUS_ENCOUNTER_MAY, 0
	return

EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic:: @ 8228AC1
	playbgm MUS_ENCOUNTER_BRENDAN, 0
	return

EverGrandeCity_ChampionsRoom_EventScript_MayAdvice:: @ 8228AC6
	msgbox EverGrandeCity_ChampionsRoom_Text_MayAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice:: @ 8228AFB
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF:: @ 8228B30
	closemessage
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchCongratulations, MSGBOX_DEFAULT
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 20
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFastestUp
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside, MSGBOX_DEFAULT
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations
	compare VAR_RESULT, FEMALE
	call_if_eq EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations
	closemessage
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 255, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations:: @ 8228BEB
	msgbox EverGrandeCity_ChampionsRoom_Text_MayCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations:: @ 8228BF4
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer:: @ 8228BFD
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth:: @ 8228C12
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart: @ 8228C1D
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExit: @ 8228C20
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer: @ 8228C26
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_in_place_fastest_right
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth: @ 8228C2F
	walk_in_place_fastest_up
	delay_16
	walk_in_place_fastest_right
	delay_16
	walk_in_place_fastest_up
	delay_8
	walk_in_place_fastest_right
	delay_16
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalFollows: @ 8228C38
	walk_right
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart: @ 8228C3B
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExit: @ 8228C3F
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_BirchArrives: @ 8228C43
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_in_place_fastest_left
	step_end

EverGrandeCity_ChampionsRoom_Text_IntroSpeech: @ 8228C4C
	.string "윤진: 잘 왔어 {PLAYER}\p"
	.string "루네시티에서 일어난 대사건을\n"
	.string "네가 혼자서 해결한 건\l"
	.string "꽤나 훌륭했어\p"
	.string "...이런!\p"
	.string "너 혼자의 힘으로\n"
	.string "해결한 건 아니었지\p"
	.string "너와... 너의 포켓몬이\n"
	.string "힘을 합쳤기에 비로소\l"
	.string "고난을 뛰어넘을 수 있었던 거야\p"
	.string "우리들 트레이너는\n"
	.string "여러 도구를 주거나\l"
	.string "여러 기술을 배우게 해서\l"
	.string "포켓몬을 키우고 있지...\p"
	.string "하지만 우리들 자신도\n"
	.string "포켓몬에게서 많은 것들을\l"
	.string "배우고 있어\p"
	.string "그리고 여긴...\n"
	.string "그 성과를 부딪치는 장소\p"
	.string "자!\p"
	.string "호연지방에서 제일 화려하게\n"
	.string "포켓몬과 춤추는 것은 누구인지!\p"
	.string "지금 여기서 보여줄게!$"
	// ミクリ『ようこそ §あ§おｐ
	// ルネシティで おこった だいじけんをｎ
	// きみが ひとりで かいけつ したのはｌ
	// なかなか みごと だったよｐ
	// ……おっと!ｐ
	// きみひとりの ちからでｎ
	// かいけつ したわけでは なかったなｐ
	// きみと…… きみの ポケモンがｎ
	// ちからを あわせたからこそｌ
	// こんなんを のりこえ られたんだｐ
	// わたしたち トレ-ナ-はｎ
	// いろんな どうぐを あたえたりｌ
	// いろんな わざを おしえたり してｌ
	// ポケモンを そだてている……ｐ
	// けれど わたしたち じしんもｎ
	// ポケモンから たくさんの ことをｌ
	// おしえられて いるのさｐ
	// そして ここは……ｎ
	// その せいかを ぶつけあう ばしょｐ
	// さあ!ｐ
	// ホウエンで いちばん かれいにｎ
	// ポケモンと おどれるのは だれなのか!ｐ
	// いま ここで みせて もらおう!

EverGrandeCity_ChampionsRoom_Text_Defeat: @ 8228EAC
	.string "챔피언인\n"
	.string "나를 쓰러뜨릴 줄이야...\p"
	.string "정말 원더풀하고\n"
	.string "얄미울 정도로 엘레강트!\l" 
	.string "하지만 매우 글로리어스!\p"
	.string "너는 정말로 멋진\n"
	.string "포켓몬 트레이너야!$"
	// チャンピオンであるｎ
	// わたしを うちまかす とは……ｐ
	// なんと ワンダフル!ｎ
	// にくらしいほど エレガント!ｌ
	// だけど とっても グロリアス!ｐ
	// さすがだよ §あ§お!ｐ
	// きみは ほんとうに すばらしいｎ
	// ポケモン トレ-ナ-だ!

EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech: @ 8228F66
	.string "윤진: 네가 내보내온\n"
	.string "여러 포켓몬들...\p"
	.string "때로는 봄바람처럼 춤추고\n"
	.string "어떤 때에는 번개처럼 찌르지\p"
	.string "그런 포켓몬들을\n"
	.string "부드럽게 다루는 너의 모습\p"
	.string "이 나조차도\n"
	.string "홀딱 반해버릴 정도였어!\p"
	.string "이 포켓몬리그에서\n"
	.string "훌륭히 정점에 선 너야말로\l"
	.string "호연지방의 새로운...$"
	// ミクリ『きみが くりだしてきたｎ
	// ポケモンの かずかず……ｐ
	// ときに はるかぜの ように まいｎ
	// あるいは いなづまの ように さすｐ
	// そんな ポケモンたちをｎ
	// かろやかに あやつる きみの すがたｐ
	// この わたしで さえもｎ
	// ほれぼれ するほど だったよ!ｐ
	// この ポケモンリ-グでｎ
	// みごと ちょうてんに たった きみこそｌ
	// ホウエンちほうの あたらしい……

EverGrandeCity_ChampionsRoom_Text_MayAdvice: @ 82290CA
	.string "봄이: {PLAYER}{K_AYA}!\p"
	.string "챔피언한테 도전하기 전에\n"
	.string "어드바이스를...!$"
	// ハルカ『§あ§お!ｐ
	// チャンピオンに ちょうせん するまえにｎ
	// アドバイス……!

EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver: @ 822910B
	.string "봄이: 응? 으응??\p"
	.string "{PLAYER}...\n"
	.string "설마...\l"
	.string "이미 끝난 거야...?$"
	// ハルカ『あれ? あれれ?ｐ
	// §あ§お……ｎ
	// ひょっとして……ｌ
	// もう おわっちゃった……?

EverGrandeCity_ChampionsRoom_Text_BrendanAdvice: @ 8229152
	.string "휘웅: {PLAYER}{K_AYA}!\p"
	.string "챔피언한테 도전하기 전에\n"
	.string "내가 어드바이스를 해줄 테니까...$"
	// ユウキ『§あ!ｐ
	// チャンピオンに ちょうせん するまえにｎ
	// オレが アドバイス してやろうか……

EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon: @ 82291A2
	.string "휘웅: {PLAYER}...\p"
	.string "너 설마\n"
	.string "챔피언한테 이긴 거야?$"
	// ユウキ『§あ……ｐ
	// おまえ ひょっとしてｎ
	// チャンピオンに かったのか?

EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex: @ 82291E6
	.string "털보박사: 거봐라 {RIVAL}{K_AYA}!\p"
	.string "{PLAYER}{K_I}라면 걱정할 필요 없다고\n"
	.string "내가 말하지 않았더냐!\p"
	.string "...... ...... ......\n"
	.string "{PLAYER} 드디어 해냈구나\p"
	.string "네가 등화체육관에 있는 아빠한테\n"
	.string "이겼다고 들었을 때부터\l"
	.string "혹시나...하는 생각은 있었다만\p"
	.string "설마 진짜 챔피언이\n"
	.string "될 줄이야!\p"
	.string "...오오 맞다!\p"
	.string "너의 포켓몬 도감은 어떻게 되었니?\n"
	.string "나에게 보여다오!$"
	// オダマキ『ほれみろ §か!ｐ
	// §あ§おなら しんぱい いらんとｎ
	// わたしが いったとおり だろう!ｐ
	// …… …… ……ｎ
	// §あ§お とうとう やりとげたなｐ
	// きみが トウカ ジムの おとうさんにｎ
	// かちぬいたと きいた ときにｌ
	// もしや…… とは おもったがｐ
	// まさか ほんとうに チャンピオンにｎ
	// なってしまうとは な!ｐ
	// ……おお そうだ!ｐ
	// きみの ポケモンずかんは どうなった?ｎ
	// わたしに みせて ごらん!

EverGrandeCity_ChampionsRoom_Text_BirchCongratulations: @ 822934D
	.string "털보박사: 어쨌든 축하한다!\p"
	.string "자 그럼 당당하게 안쪽 방에\n"
	.string "갔다 오너라!$"
	// オダマキ『とにかく おめでとう!ｐ
	// さあ むねをはって おくの へやにｎ
	// いってくるが いいよ!

EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe: @ 8229399
	.string "윤진: {PLAYER}\p"
	.string "...아니 다시 말하지\p"
	.string "새로운 챔피언!\p"
	.string "자 나를 따라와줘$"
	// ミクリ『§あ§おｐ
	// ……いや あらためて よびなおそうｐ
	// あたらしい チャンピオン!ｐ
	// さあ わたしに ついて きたまえ

EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside: @ 82293EB
	.string "윤진: 미안하게 됐지만...\p"
	.string "이 앞의 방은\n"
	.string "챔피언이 된 트레이너만이\l"
	.string "들어갈 수 있는 장소\p"
	.string "너는 거기서 털보박사와\n"
	.string "함께 기다리고 있어줘$"
	// ミクリ『もうしわけ ないが……ｐ
	// ここから さきの へやはｎ
	// チャンピオンに なった トレ-ナ- だけがｌ
	// はいることの できる ばしょｐ
	// きみは そこで オダマキはかせとｎ
	// いっしょに まっていて くれたまえ

EverGrandeCity_ChampionsRoom_Text_MayCongratulations: @ 8229479
	.string "봄이: ...힝!\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "장난이야! 괜찮아 괜찮아!\n"
	.string "그게 룰이니까 지켜야지!\p"
	.string "{PLAYER}{K_AYA}!\n"
	.string "정말 축하해!!$"
	// ハルカ『……が-ん!ｐ
	// …… …… ……ｎ
	// …… …… ……ｐ
	// な-んてね いいの いいの!ｎ
	// だって そういう きまり だもんね!ｐ
	// §あ§お!ｎ
	// ほんとうに おめでとう!!

EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations: @ 82294F5
	.string "휘웅: !\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "어쩔 수 없지\n"
	.string "룰이 그런 거니까\p"
	.string "{PLAYER}{K_AYA}!\n"
	.string "정말 축하해!!$"
	// ユウキ『……え-っ!ｎ
	// …… …… ……ｎ
	// …… …… ……ｐ
	// ま しかたないかｎ
	// そういう きまり だもんなｐ
	// §あ! よかったなｎ
	// おめでとう!!

