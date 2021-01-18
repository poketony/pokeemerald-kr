.set LOCALID_STEVEN, 3
.set LOCALID_ARCHIE, 4
.set LOCALID_MAXIE, 5

Route128_MapScripts:: @ 81F6B38
	map_script MAP_SCRIPT_ON_TRANSITION, Route128_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route128_OnFrame
	.byte 0

Route128_OnTransition: @ 81F6B43
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

Route128_OnFrame: @ 81F6B4D
	map_script_2 VAR_ROUTE128_STATE, 1, Route128_EventScript_KyogreAwakenedScene
	.2byte 0

Route128_EventScript_KyogreAwakenedScene:: @ 81F6B57
	lockall
	delay 20
	applymovement LOCALID_ARCHIE, Route128_Movement_ArchieLookAround
	waitmovement 0
	msgbox Route128_Text_ArchieWhatHappened, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, Route128_Movement_ArchieBackUp
	waitmovement 0
	msgbox Route128_Text_ArchieIOnlyWanted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAXIE, Route128_Movement_MaxieApproachArchie
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox Route128_Text_MaxieDoYouUnderstandNow, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAXIE, Route128_Movement_MaxieApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox Route128_Text_MaxieResposibilityFallsToArchieAndMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, Route128_Movement_ArchieRunLeft
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	applymovement LOCALID_MAXIE, Route128_Movement_MaxieWalkLeft
	waitmovement 0
	msgbox Route128_Text_MaxieThisDefiesBelief, MSGBOX_DEFAULT
	closemessage
	delay 40
	applymovement LOCALID_MAXIE, Route128_Movement_MaxieExit
	applymovement LOCALID_ARCHIE, Route128_Movement_ArchieExit
	waitmovement 0
	removeobject LOCALID_MAXIE
	removeobject LOCALID_ARCHIE
	delay 100
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	waitfieldeffect FLDEFF_NPCFLY_OUT
	addobject LOCALID_STEVEN
	applymovement LOCALID_STEVEN, Route128_Movement_StevenApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox Route128_Text_StevenWhatIsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_STEVEN, Route128_Movement_StevenWalkUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox Route128_Text_StevenWholeWorldWillDrown, MSGBOX_DEFAULT
	applymovement LOCALID_STEVEN, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox Route128_Text_StevenImGoingToSootopolis, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_STEVEN, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_STEVEN
	waitfieldeffect FLDEFF_NPCFLY_OUT
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_ROUTE128_STATE, 2
	releaseall
	end

Route128_Movement_Unused1: @ 81F6C76
	walk_fast_left
	step_end

Route128_Movement_Unused2: @ 81F6C78
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route128_Movement_StevenWalkUp: @ 81F6C85
	walk_up
	step_end

Route128_Movement_StevenApproachPlayer: @ 81F6C87
	walk_fast_left
	step_end

Route128_Movement_ArchieLookAround: @ 81F6C89
	walk_fast_down
	walk_in_place_fastest_left
	delay_16
	walk_in_place_fastest_right
	delay_16
	delay_16
	walk_in_place_fastest_down
	step_end

Route128_Movement_ArchieBackUp: @ 81F6C91
	lock_facing_direction
	walk_slow_up
	delay_16
	unlock_facing_direction
	step_end

Route128_Movement_ArchieRunLeft: @ 81F6C96
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_in_place_fastest_right
	step_end

Route128_Movement_ArchieExit: @ 81F6C9B
	delay_16
	delay_16
	walk_fast_up
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route128_Movement_MaxieWalkLeft: @ 81F6CA8
	walk_left
	walk_left
	delay_8
	delay_4
	step_end

Route128_Movement_MaxieApproachArchie: @ 81F6CAD
	walk_left
	walk_in_place_fastest_down
	step_end

Route128_Movement_MaxieExit: @ 81F6CB0
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route128_Movement_MaxieApproachPlayer: @ 81F6CBB
	walk_right
	walk_in_place_fastest_down
	step_end

Route128_EventScript_Isaiah:: @ 81F6CBE
	trainerbattle_single TRAINER_ISAIAH_1, Route128_Text_IsaiahIntro, Route128_Text_IsaiahDefeat, Route128_EventScript_RegisterIsaiah
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route128_EventScript_RematchIsaiah
	msgbox Route128_Text_IsaiahPostBattle, MSGBOX_DEFAULT
	release
	end

Route128_EventScript_RegisterIsaiah:: @ 81F6CEA
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route128_Text_IsaiahRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ISAIAH_1
	release
	end

Route128_EventScript_RematchIsaiah:: @ 81F6D09
	trainerbattle_rematch TRAINER_ISAIAH_1, Route128_Text_IsaiahRematchIntro, Route128_Text_IsaiahRematchDefeat
	msgbox Route128_Text_IsaiahPostRematch, MSGBOX_AUTOCLOSE
	end

Route128_EventScript_Katelyn:: @ 81F6D20
	trainerbattle_single TRAINER_KATELYN_1, Route128_Text_KatelynIntro, Route128_Text_KatelynDefeat, Route128_EventScript_RegisterKatelyn
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route128_EventScript_RematchKatelyn
	msgbox Route128_Text_KatelynPostBattle, MSGBOX_DEFAULT
	release
	end

Route128_EventScript_RegisterKatelyn:: @ 81F6D4C
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route128_Text_KatelynRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KATELYN_1
	release
	end

Route128_EventScript_RematchKatelyn:: @ 81F6D6B
	trainerbattle_rematch TRAINER_KATELYN_1, Route128_Text_KatelynRematchIntro, Route128_Text_KatelynRematchDefeat
	msgbox Route128_Text_KatelynPostRematch, MSGBOX_AUTOCLOSE
	end

Route128_EventScript_Alexa:: @ 81F6D82
	trainerbattle_single TRAINER_ALEXA, Route128_Text_AlexaIntro, Route128_Text_AlexaDefeat
	msgbox Route128_Text_AlexaPostBattle, MSGBOX_AUTOCLOSE
	end

Route128_EventScript_Ruben:: @ 81F6D99
	trainerbattle_single TRAINER_RUBEN, Route128_Text_RubenIntro, Route128_Text_RubenDefeat
	msgbox Route128_Text_RubenPostBattle, MSGBOX_AUTOCLOSE
	end

Route128_EventScript_Wayne:: @ 81F6DB0
	trainerbattle_single TRAINER_WAYNE, Route128_Text_WayneIntro, Route128_Text_WayneDefeat
	msgbox Route128_Text_WaynePostBattle, MSGBOX_AUTOCLOSE
	end

Route128_EventScript_Harrison:: @ 81F6DC7
	trainerbattle_single TRAINER_HARRISON, Route128_Text_HarrisonIntro, Route128_Text_HarrisonDefeat
	msgbox Route128_Text_HarrisonPostBattle, MSGBOX_AUTOCLOSE
	end

Route128_EventScript_Carlee:: @ 81F6DDE
	trainerbattle_single TRAINER_CARLEE, Route128_Text_CarleeIntro, Route128_Text_CarleeDefeat
	msgbox Route128_Text_CarleePostBattle, MSGBOX_AUTOCLOSE
	end

Route128_Text_ArchieWhatHappened: @ 81F6DF5
	.string "아강: 뭐야...\n"
	.string "이 끔찍한 광경은...?\p"
	.string "나는...\n"
	.string "터무니없는 잘못을...$"
	// アオギリ『なんだ……ｎ
	// この ひどい ありさまは……?ｐ
	// おれは……ｎ
	// とんでもない まちがいを……

Route128_Text_ArchieIOnlyWanted: @ 81F6E48
	.string "나는...\n"
	.string "그저...$"
	// おれは……ｎ
	// ただ……

Route128_Text_MaxieDoYouUnderstandNow: @ 81F6E5A
	.string "마적: 알겠나 아강!\p"
	.string "네가...\n"
	.string "아니 우리가 한 일이\l"
	.string "얼마나 어리석은 것인지를...\p"
	.string "어쨌든 서두르자!\n"
	.string "이 이상 심각해지기 전에\l"
	.string "뭐라도 하지 않으면 안되니까!$"
	// マツブサ『わかったか アオギリ!ｐ
	// おまえの……ｎ
	// いや われわれの したことがｌ
	// どれほど おろか だったのか……ｐ
	// とにかく いそぐんだ!ｎ
	// これいじょう ひどく ならぬうちにｌ
	// なんとか しないとな!

Route128_Text_MaxieResposibilityFallsToArchieAndMe: @ 81F6F1E
	.string "마적: {PLAYER} 아무 말도 하지 마라\p"
	.string "나에게 아강을 꾸짖을\n"
	.string "자격이 없는 건 알고 있다...\p"
	.string "일이 이렇게 된 이상\n"
	.string "이제 인간의 힘으로는\l"
	.string "아무것도 할 수 없을 테지\p"
	.string "하지만 그렇다고 해서\n"
	.string "잠자코 보고 있을 수도 없다\p"
	.string "이 일의 뒤처리를 하는 건\n"
	.string "나와 아강의 책임이니... 까...$"
	// マツブサ『§あ なにも いうなｐ
	// わたしに アオギリを せめるｎ
	// しかくが ないことは わかっている……ｐ
	// こんな ことに なった いじょうｎ
	// もう にんげんの ちからではｌ
	// どうする ことも できない だろうｐ
	// しかし だから といってｎ
	// だまって みている わけにも いかないｐ
	// この あとしまつを つけるのはｎ
	// わたしと アオギリの やくめ…… か……

Route128_Text_MaxieThisDefiesBelief: @ 81F704F
	.string "마적: 그건 그렇고...\p"
	.string "초 고대포켓몬...\n"
	.string "엄청난 파워다\l"
	.string "모든 균형이 무너졌어...$"
	// マツブサ『それにしても……ｐ
	// ちょう こだいポケモン……ｎ
	// なんという パワ-だｌ
	// すべての バランスが くずれたぞ……

Route128_Text_StevenWhatIsHappening: @ 81F70C9
	.string "성호: {PLAYER}!\n"
	.string "이건 대체...?$"
	// ダイゴ『§あ§お!ｎ
	// これは いったい……?

Route128_Text_StevenWholeWorldWillDrown: @ 81F70EA
	.string "...이건 좀 심한걸\p"
	.string "아까는 엄청난 가뭄이었는데\n"
	.string "지금은 폭우가 내리기 시작했어\p"
	.string "이대로라면 호연지방...\n"
	.string "아니 전 세계가 잠길 거야!\p"
	.string "이 비를 내리게 하고 있는 구름은\n"
	.string "루네시티의 상공을 중심으로\l"
	.string "퍼져 있는 건가...\p"
	.string "대체 저기서\n"
	.string "뭐가 일어나는 거지?!\p"
	.string "여기서 이것저것 생각할 게 아니고\n"
	.string "루네시티로 직접 가면 알겠네...$"
	// ……ひどいなｐ
	// さっきは はげしい ひでり だったのにｎ
	// また おおあめが ふりはじめているｐ
	// このまま では ホウエンちほう……ｎ
	// いや せかいじゅうが しずむ!ｐ
	// この あめを ふらせている くもはｎ
	// ルネの じょうくうを ちゅうしんにｌ
	// ひろがって いるのか……ｐ
	// いったい あそこでｎ
	// なにが おきている!?ｐ
	// ここで あれこれ かんがえるよりｎ
	// ルネに いけば わかるか……

Route128_Text_StevenImGoingToSootopolis: @ 81F721B
	.string "{PLAYER}...\n"
	.string "네가 뭘 할 생각인지는\l"
	.string "모르겠지만 무리만은 하지 마\p"
	.string "...그럼\n"
	.string "나는 루네시티로 갈게$"
	// §あ§お……ｎ
	// きみが なにを する つもりかｌ
	// わからないけど ムリだけは するなよｐ
	// ……じゃあｎ
	// ボクは ルネに いくから

