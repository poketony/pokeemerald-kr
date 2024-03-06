.set LOCALID_RIVAL, 2

Route103_MapScripts:: @ 81EC38E
	map_script MAP_SCRIPT_ON_TRANSITION, Route103_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route103_OnLoad
	.byte 0

Route103_OnTransition: @ 81EC399
	call Common_EventScript_SetupRivalGfxId
	call ProfBirch_EventScript_UpdateLocation
	end

Route103_OnLoad: @ 81EC3A4
	call_if_set FLAG_SYS_GAME_CLEAR, Route103_EventScript_OpenAlteringCave
	end

Route103_EventScript_OpenAlteringCave:: @ 81EC3AE
	setmetatile 45, 5, METATILE_General_CaveEntrance_Top, 1
	setmetatile 45, 6, METATILE_General_CaveEntrance_Bottom, 0
	return

Route103_EventScript_Rival:: @ 81EC3C1
	lockall
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq Route103_EventScript_RivalMay
	compare VAR_RESULT, FEMALE
	goto_if_eq Route103_EventScript_RivalBrendan
	end

Route103_EventScript_RivalMay:: @ 81EC3DA
	msgbox Route103_Text_MayRoute103Pokemon, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_MAY, 1
	applymovement LOCALID_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	msgbox Route103_Text_MayLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route103_EventScript_StartMayBattleTreecko
	case 1, Route103_EventScript_StartMayBattleTorchic
	case 2, Route103_EventScript_StartMayBattleMudkip
	end

Route103_EventScript_RivalBrendan:: @ 81EC434
	msgbox Route103_Text_BrendanRoute103Pokemon, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_BRENDAN, 1
	applymovement LOCALID_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	msgbox Route103_Text_BrendanLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route103_EventScript_StartBrendanBattleTreecko
	case 1, Route103_EventScript_StartBrendanBattleTorchic
	case 2, Route103_EventScript_StartBrendanBattleMudkip
	end

Route103_EventScript_StartMayBattleTreecko:: @ 81EC48E
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TREECKO, Route103_Text_MayDefeated
	goto Route103_EventScript_AfterMayBattle
	end

Route103_EventScript_StartMayBattleTorchic:: @ 81EC49E
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TORCHIC, Route103_Text_MayDefeated
	goto Route103_EventScript_AfterMayBattle
	end

Route103_EventScript_StartMayBattleMudkip:: @ 81EC4AE
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_MUDKIP, Route103_Text_MayDefeated
	goto Route103_EventScript_AfterMayBattle
	end

Route103_EventScript_StartBrendanBattleTreecko:: @ 81EC4BE
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TREECKO, Route103_Text_BrendanDefeated
	goto Route103_EventScript_AfterBrendanBattle
	end

Route103_EventScript_StartBrendanBattleTorchic:: @ 81EC4CE
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TORCHIC, Route103_Text_BrendanDefeated
	goto Route103_EventScript_AfterBrendanBattle
	end

Route103_EventScript_StartBrendanBattleMudkip:: @ 81EC4DE
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_MUDKIP, Route103_Text_BrendanDefeated
	goto Route103_EventScript_AfterBrendanBattle
	end

Route103_EventScript_AfterMayBattle:: @ 81EC4EE
	msgbox Route103_Text_MayTimeToHeadBack, MSGBOX_DEFAULT
	goto Route103_EventScript_RivalExit
	end

Route103_EventScript_AfterBrendanBattle:: @ 81EC4FC
	msgbox Route103_Text_BrendanTimeToHeadBack, MSGBOX_DEFAULT
	goto Route103_EventScript_RivalExit
	end

Route103_EventScript_RivalExit:: @ 81EC50A
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, Route103_EventScript_RivalExitFacingSouth
	case DIR_NORTH, Route103_EventScript_RivalExitFacingNorth
	case DIR_WEST, Route103_EventScript_RivalExitFacingEastOrWest
	case DIR_EAST, Route103_EventScript_RivalExitFacingEastOrWest
	end

Route103_EventScript_RivalExitFacingNorth:: @ 81EC53D
	applymovement OBJ_EVENT_ID_PLAYER, Route103_Movement_WatchRivalExitFacingNorth
	applymovement LOCALID_RIVAL, Route103_Movement_RivalExitFacingNorth1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_RIVAL, Route103_EventScript_RivalExitFacingNorth2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalExitFacingEastOrWest:: @ 81EC561
	applymovement OBJ_EVENT_ID_PLAYER, Route103_Movement_WatchRivalExitFacingEastOrWest
	applymovement LOCALID_RIVAL, Route103_Movement_RivalExit1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_RIVAL, Route103_Movement_RivalExit2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalExitFacingSouth:: @ 81EC585
	applymovement LOCALID_RIVAL, Route103_Movement_RivalExit1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_RIVAL, Route103_Movement_RivalExit2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalEnd:: @ 81EC5A2
	removeobject LOCALID_RIVAL
	setvar VAR_BIRCH_LAB_STATE, 4
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	setflag FLAG_DEFEATED_RIVAL_ROUTE103
	setvar VAR_OLDALE_RIVAL_STATE, 1
	clearflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Route103_Movement_RivalExitFacingNorth1: @ 81EC5BE
	walk_left
	walk_down
	step_end

Route103_EventScript_RivalExitFacingNorth2: @ 81EC5C1
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route103_Movement_WatchRivalExitFacingNorth: @ 81EC5C8
	delay_16
	delay_4
	walk_in_place_fastest_left
	delay_16
	walk_in_place_fastest_down
	step_end

Route103_Movement_RivalExit1: @ 81EC5CE
	walk_down
	step_end

Route103_Movement_RivalExit2: @ 81EC5D0
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	step_end

Route103_Movement_WatchRivalExitFacingEastOrWest: @ 81EC5D6
	delay_16
	walk_in_place_fastest_down
	step_end

Route103_EventScript_Boy:: @ 81EC5D9
	msgbox Route103_Text_ShouldHaveBroughtPotion, MSGBOX_NPC
	end

Route103_EventScript_Man:: @ 81EC5E2
	msgbox Route103_Text_ShortcutToOldale, MSGBOX_NPC
	end

Route103_EventScript_RouteSign:: @ 81EC5EB
	msgbox Route103_Text_RouteSign, MSGBOX_SIGN
	end

Route103_EventScript_Daisy:: @ 81EC5F4
	trainerbattle_single TRAINER_DAISY, Route103_Text_DaisyIntro, Route103_Text_DaisyDefeated
	msgbox Route103_Text_DaisyPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Amy:: @ 81EC60B
	trainerbattle_double TRAINER_AMY_AND_LIV_1, Route103_Text_AmyIntro, Route103_Text_AmyDefeated, Route103_Text_AmyNotEnoughPokemon, Route102_EventScript_AmyRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route102_EventScript_AmyRematch
	msgbox Route103_Text_AmyPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_AmyRegisterMatchCallAfterBattle:: @ 81EC63A
	msgbox Route103_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

Route102_EventScript_AmyRematch:: @ 81EC653
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, Route103_Text_AmyRematchIntro, Route103_Text_AmyRematchDefeated, Route103_Text_AmyRematchNotEnoughPokemon
	msgbox Route103_Text_AmyRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Liv:: @ 81EC66E
	trainerbattle_double TRAINER_AMY_AND_LIV_1, Route103_Text_LivIntro, Route103_Text_LivDefeated, Route103_Text_LivNotEnoughPokemon, Route102_EventScript_LivRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route102_EventScript_LivRematch
	msgbox Route103_Text_LivPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_LivRegisterMatchCallAfterBattle:: @ 81EC69D
	msgbox Route103_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

Route102_EventScript_LivRematch:: @ 81EC6B6
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, Route103_Text_LivRematchIntro, Route103_Text_LivRematchDefeated, Route103_Text_LivRematchNotEnoughPokemon
	msgbox Route103_Text_LivRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Andrew:: @ 81EC6D1
	trainerbattle_single TRAINER_ANDREW, Route103_Text_AndrewIntro, Route103_Text_AndrewDefeated
	msgbox Route103_Text_AndrewPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Miguel:: @ 81EC6E8
	trainerbattle_single TRAINER_MIGUEL_1, Route103_Text_MiguelIntro, Route103_Text_MiguelDefeated, Route102_EventScript_MiguelRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route103_EventScript_MiguelRematch
	msgbox Route103_Text_MiguelPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_MiguelRegisterMatchCallAfterBattle:: @ 81EC714
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route103_Text_MiguelRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_MIGUEL_1
	release
	end

Route103_EventScript_MiguelRematch:: @ 81EC733
	trainerbattle_rematch TRAINER_MIGUEL_1, Route103_Text_MiguelRematchIntro, Route103_Text_MiguelRematchDefeated
	msgbox Route103_Text_MiguelRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Marcos:: @ 81EC74A
	trainerbattle_single TRAINER_MARCOS, Route103_Text_MarcosIntro, Route103_Text_MarcosDefeated
	msgbox Route103_Text_MarcosPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Rhett:: @ 81EC761
	trainerbattle_single TRAINER_RHETT, Route103_Text_RhettIntro, Route103_Text_RhettDefeated
	msgbox Route103_Text_RhettPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Pete:: @ 81EC778
	trainerbattle_single TRAINER_PETE, Route103_Text_PeteIntro, Route103_Text_PeteDefeated
	msgbox Route103_Text_PetePostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Isabelle:: @ 81EC78F
	trainerbattle_single TRAINER_ISABELLE, Route103_Text_IsabelleIntro, Route103_Text_IsabelleDefeated
	msgbox Route103_Text_IsabellePostBattle, MSGBOX_AUTOCLOSE
	end

Route103_Text_MayRoute103Pokemon: @ 81EC7A6
	.string "봄이: 음- 103번 도로에 있는\n"
	.string "포켓몬은 저거랑 저거고...$"
	@ ハルカ『え-と 103ばん どうろに いるｎ
	@ ポケモンは あれと あれね……

Route103_Text_MayLetsBattle: @ 81EC7DE
	.string "어라 {PLAYER}{K_AYA}!\p"
	.string "...아! 아빠한테\n"
	.string "포켓몬을 선물받은 거구나!\p"
	.string "모처럼이니까 잠깐\n"
	.string "포켓몬 승부를 해보자!\p"
	.string "트레이너가 어떤 건지\n"
	.string "내가 알려 줄게!$"
	@ あら §あ§お!ｐ
	@ ……そうか! おとうさん からｎ
	@ ポケモンを プレゼントして もらったのね!ｐ
	@ せっかくだから ちょっとｎ
	@ ポケモンしょうぶ しようよ!ｐ
	@ トレ-ナ-って どんな ものかｎ
	@ あたしが おしえて あげるから!

Route103_Text_MayDefeated: @ 81EC881
	.string "우와! 굉장해 굉장해!\n"
	.string "{PLAYER}{K_EUNNEUN} 강하구나!$"
	@ うわっ! すごい すごい!ｎ
	@ §あ§お つよい じゃない!

Route103_Text_MayTimeToHeadBack: @ 81EC8AE
	.string "봄이: 나 왜 아빠가\n"
	.string "너를 주목하는지\l"
	.string "알 거 같아!\p"
	.string "왜냐하면 받은 지 얼마 안 된 포켓몬이\n"
	.string "벌써 널 따르고 있잖아!\p"
	.string "너라면 어떤 포켓몬이랑도\n"
	.string "친해질 수 있을 것 같아!\p"
	.string "그럼\n"
	.string "연구소로 같이 돌아가자!$"
	@ ハルカ『あたし おとうさんがｎ
	@ あなたの ことを ちゅうもく するのもｌ
	@ わかるような きが する!ｐ
	@ だって もらって すぐの ポケモンがｎ
	@ もう あなたに なついているもの!ｐ
	@ あなたなら どんな ポケモンとでもｎ
	@ なかよく なれるかも!ｐ
	@ じゃあｎ
	@ けんきゅうじょに かえろっか!

Route103_Text_BrendanRoute103Pokemon: @ 81EC989
	.string "휘웅: 그렇구나 쟤랑 쟤가\n"
	.string "103번 도로에 있는 포켓몬이군...$"
	@ ユウキ『そうか あいつと あいつがｎ
	@ 103ばん どうろに いる ポケモンか……

Route103_Text_BrendanLetsBattle: @ 81EC9CE
	.string "으응? {PLAYER}{K_AYA}!\p"
	.string "...그렇구나 아빠한테서\n"
	.string "포켓몬을 받았다고\p"
	.string "그럼 마침 잘됐다\n"
	.string "포켓몬 승부 한번 해볼래?\p"
	.string "트레이너라는 게 어떤 건지\n"
	.string "내가 알려 줄게!$"
	@ おや? §あ!ｐ
	@ ……そうか とうさん からｎ
	@ ポケモンを もらったのかｐ
	@ じゃあ ついでだｎ
	@ ポケモンしょうぶ してやろうか?ｐ
	@ トレ-ナ-って どんな ものかｎ
	@ オレが おしえてやるよ!

Route103_Text_BrendanDefeated: @ 81ECA59
	.string "흐음\n"
	.string "{PLAYER}{K_EUNNEUN} 강하구나$"
	@ ふうんｎ
	@ §あって つよいんだね

Route103_Text_BrendanTimeToHeadBack: @ 81ECA79
	.string "휘웅: 아빠가 왜\n"
	.string "{PLAYER}{K_EULREUL} 주목하는지\l"
	.string "알 거 같아...\p"
	.string "받은 지 얼마 안 된 포켓몬이\n"
	.string "벌써 이렇게 잘 따르고 있잖아\p"
	.string "{PLAYER} 너라면 어떤 포켓몬이랑도\n"
	.string "친해질 수 있겠다\p"
	.string "자 그럼\n"
	.string "연구소로 같이 돌아가자$"
	@ ユウキ『とうさんがｎ
	@ §あの ことを ちゅうもく するのもｌ
	@ わかったような きが する……ｐ
	@ もらって すぐの ポケモンがｎ
	@ もう なついているよｐ
	@ §あなら どんな ポケモンとでもｎ
	@ なかよく なれるかも しれないなｐ
	@ じゃｎ
	@ けんきゅうじょに もどろうか

Route103_Text_ShouldHaveBroughtPotion: @ 81ECB73
	.string "내 포켓몬 휘청휘청거려...\n"
	.string "상처약 챙겨 올 걸 그랬어...$"
	@ ぼくの ポケモン もう へろへろ……ｎ
	@ キズぐすり もってくれば よかった……

Route103_Text_ShortcutToOldale: @ 81ECBB5
	.string "여기에서 바다를 건너면\n"
	.string "고도마을까지 가는 지름길이야!\p"
	.string "후후후 꽤 쓸만한 정보지?$"
	@ ここから うみを わたっていけばｎ
	@ コトキタウンまで ちかみちが できるぞ!ｐ
	@ ふふふ おとくな じょうほう だろ?

Route103_Text_RouteSign: @ 81ECC1A
	.string "여기는 103번 도로\n"
	.string "{DOWN_ARROW} 고도마을$"
	@ ここは 103ばん どうろｎ
	@ ©しあ コトキタウン

