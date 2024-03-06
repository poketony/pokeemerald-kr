.set LOCALID_SCIENTIST_1, 1
.set LOCALID_SCIENTIST_2, 2
.set LOCALID_SAILOR, 3
.set LOCALID_OLD_MAN, 4
.set LOCALID_WOMAN, 5
.set LOCALID_STAIR_GRUNT, 9

MossdeepCity_SpaceCenter_1F_MapScripts:: @ 8222F41
	map_script MAP_SCRIPT_ON_LOAD, MossdeepCity_SpaceCenter_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_SpaceCenter_1F_OnTransition
	.byte 0

MossdeepCity_SpaceCenter_1F_OnTransition: @ 8222F4C
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_MoveObjectsForTeamMagma
	end

MossdeepCity_SpaceCenter_1F_EventScript_MoveObjectsForTeamMagma:: @ 8222F58
	setobjectxyperm LOCALID_SAILOR, 1, 9
	setobjectmovementtype LOCALID_SAILOR, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_WOMAN, 0, 8
	setobjectmovementtype LOCALID_WOMAN, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_OLD_MAN, 1, 6
	setobjectmovementtype LOCALID_OLD_MAN, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_SCIENTIST_1, 3, 4
	setobjectmovementtype LOCALID_SCIENTIST_1, MOVEMENT_TYPE_FACE_RIGHT
	setobjectmovementtype LOCALID_SCIENTIST_2, MOVEMENT_TYPE_FACE_RIGHT
	compare VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE, 1
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_MoveStairGuardLeft
	compare VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE, 2
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_MoveStairGuardDown
	compare VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE, 3
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_MoveStairGuardRight
	end

MossdeepCity_SpaceCenter_1F_EventScript_MoveStairGuardLeft:: @ 8222FAA
	setobjectxyperm LOCALID_STAIR_GRUNT, 12, 2
	end

MossdeepCity_SpaceCenter_1F_EventScript_MoveStairGuardDown:: @ 8222FB2
	setobjectxyperm LOCALID_STAIR_GRUNT, 13, 3
	end

@ Functionally unused. See comment on MossdeepCity_SpaceCenter_1F_EventScript_MoveGruntFromStairsEast
MossdeepCity_SpaceCenter_1F_EventScript_MoveStairGuardRight:: @ 8222FBA
	setobjectxyperm LOCALID_STAIR_GRUNT, 14, 2
	end

MossdeepCity_SpaceCenter_1F_OnLoad: @ 8222FC2
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_le MossdeepCity_SpaceCenter_1F_EventScript_SetMagmaNote
	end

MossdeepCity_SpaceCenter_1F_EventScript_SetMagmaNote:: @ 8222FCE
	setmetatile 2, 5, METATILE_Facility_DataPad, 1
	return

MossdeepCity_SpaceCenter_1F_EventScript_RocketLaunchCounter:: @ 8222FD8
	lock
	faceplayer
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_RocketLaunchCounterMagma
	dotimebasedevents
	specialvar VAR_RESULT, GetWeekCount
	buffernumberstring 0, VAR_RESULT
	compare VAR_RESULT, 0
	call_if_eq MossdeepCity_SpaceCenter_1F_EventScript_NoLaunchesYet
	compare VAR_RESULT, 1
	call_if_ge MossdeepCity_SpaceCenter_1F_EventScript_ShowLaunchNumber
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_NoLaunchesYet:: @ 8223012
	msgbox MossdeepCity_SpaceCenter_1F_Text_RocketLaunchImminent, MSGBOX_DEFAULT
	return

MossdeepCity_SpaceCenter_1F_EventScript_ShowLaunchNumber:: @ 822301B
	msgbox MossdeepCity_SpaceCenter_1F_Text_SuccessfulLaunchNumber, MSGBOX_DEFAULT
	return

MossdeepCity_SpaceCenter_1F_EventScript_RocketLaunchCounterMagma:: @ 8223024
	dotimebasedevents
	specialvar VAR_RESULT, GetWeekCount
	buffernumberstring 0, VAR_RESULT
	compare VAR_RESULT, 0
	call_if_eq MossdeepCity_SpaceCenter_1F_EventScript_NoLaunchesYetMagma
	compare VAR_RESULT, 1
	call_if_ge MossdeepCity_SpaceCenter_1F_EventScript_ShowLaunchNumberMagma
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_NoLaunchesYetMagma:: @ 8223051
	msgbox MossdeepCity_SpaceCenter_1F_Text_HaywireButRocketLaunchImminent, MSGBOX_DEFAULT
	return

MossdeepCity_SpaceCenter_1F_EventScript_ShowLaunchNumberMagma:: @ 822305A
	msgbox MossdeepCity_SpaceCenter_1F_Text_HaywireButSuccessfulLaunchNumber, MSGBOX_DEFAULT
	return

MossdeepCity_SpaceCenter_1F_EventScript_Scientist:: @ 8223063
	lock
	faceplayer
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_ScientistMagma
	msgbox MossdeepCity_SpaceCenter_1F_Text_RocketLaunchDemandsPerfection, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_ScientistMagma:: @ 822307A
	msgbox MossdeepCity_SpaceCenter_1F_Text_MagmaHaveSightsOnSpaceCenter, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_SunStoneMan:: @ 822308E
	lock
	faceplayer
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_SunStoneManMagma
	goto_if_set FLAG_RECEIVED_SUN_STONE_MOSSDEEP, MossdeepCity_SpaceCenter_1F_EventScript_GaveSunStone
	msgbox MossdeepCity_SpaceCenter_1F_Text_FoundThisYouCanHaveIt, MSGBOX_DEFAULT
	giveitem ITEM_SUN_STONE
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SUN_STONE_MOSSDEEP
	msgbox MossdeepCity_SpaceCenter_1F_Text_HoennFamousForMeteorShowers, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_GaveSunStone:: @ 82230D0
	msgbox MossdeepCity_SpaceCenter_1F_Text_HoennFamousForMeteorShowers, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_SunStoneManMagma:: @ 82230DA
	goto_if_set FLAG_RECEIVED_SUN_STONE_MOSSDEEP, MossdeepCity_SpaceCenter_1F_EventScript_GaveSunStoneMagma
	msgbox MossdeepCity_SpaceCenter_1F_Text_MagmaCantStealFuelTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_SUN_STONE
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SUN_STONE_MOSSDEEP
	msgbox MossdeepCity_SpaceCenter_1F_Text_CantStrollOnBeachWithMagma, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_GaveSunStoneMagma:: @ 8223119
	msgbox MossdeepCity_SpaceCenter_1F_Text_CantStrollOnBeachWithMagma, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_Woman:: @ 822312D
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_SpaceCenter_1F_EventScript_WomanNormal
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_WomanMagma
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_lt MossdeepCity_SpaceCenter_1F_EventScript_WomanNormal
	goto MossdeepCity_SpaceCenter_1F_EventScript_WomanMagma
	end

MossdeepCity_SpaceCenter_1F_EventScript_WomanNormal:: @ 8223154
	msgbox MossdeepCity_SpaceCenter_1F_Text_DidPokemonComeFromSpace, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_WomanMagma:: @ 822315E
	msgbox MossdeepCity_SpaceCenter_1F_Text_AquaShouldBeatMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_OldMan:: @ 8223168
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_SpaceCenter_1F_EventScript_OldManNormal
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_eq MossdeepCity_SpaceCenter_1F_EventScript_OldManMagma
	compare VAR_MOSSDEEP_CITY_STATE, 2
	goto_if_lt MossdeepCity_SpaceCenter_1F_EventScript_OldManNormal
	goto MossdeepCity_SpaceCenter_1F_EventScript_OldManMagma
	end

MossdeepCity_SpaceCenter_1F_EventScript_OldManNormal:: @ 822318F
	msgbox MossdeepCity_SpaceCenter_1F_Text_RocketsBoggleMyMind, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_OldManMagma:: @ 82231A4
	msgbox MossdeepCity_SpaceCenter_1F_Text_MagmaWantsToSpoilMyDream, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_Steven:: @ 82231B9
	lock
	faceplayer
	msgbox MossdeepCity_SpaceCenter_1F_Text_StevenMagmaCantBeAllowedToTakeFuel, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_MagmaNote:: @ 82231CF
	lockall
	msgbox MossdeepCity_SpaceCenter_1F_Text_MagmaIntentToStealNotice, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_SpaceCenter_1F_EventScript_Grunt3:: @ 82231DA
	trainerbattle_single TRAINER_GRUNT_SPACE_CENTER_3, MossdeepCity_SpaceCenter_1F_Text_Grunt3Intro, MossdeepCity_SpaceCenter_1F_Text_Grunt3Defeat
	msgbox MossdeepCity_SpaceCenter_1F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_SpaceCenter_1F_EventScript_Grunt1:: @ 82231F1
	trainerbattle_single TRAINER_GRUNT_SPACE_CENTER_1, MossdeepCity_SpaceCenter_1F_Text_Grunt1Intro, MossdeepCity_SpaceCenter_1F_Text_Grunt1Defeat
	msgbox MossdeepCity_SpaceCenter_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_SpaceCenter_1F_EventScript_Grunt4:: @ 8223208
	trainerbattle_single TRAINER_GRUNT_SPACE_CENTER_4, MossdeepCity_SpaceCenter_1F_Text_Grunt4Intro, MossdeepCity_SpaceCenter_1F_Text_Grunt4Defeat
	msgbox MossdeepCity_SpaceCenter_1F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_SpaceCenter_1F_EventScript_Grunt2:: @ 822321F
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_GRUNT_SPACE_CENTER_1F, MossdeepCity_SpaceCenter_1F_EventScript_Grunt2Defeated
	msgbox MossdeepCity_SpaceCenter_1F_Text_Grunt2Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_SPACE_CENTER_2, MossdeepCity_SpaceCenter_1F_Text_Grunt2Defeat
	setflag FLAG_DEFEATED_GRUNT_SPACE_CENTER_1F
	copyobjectxytoperm LOCALID_STAIR_GRUNT
	switch VAR_FACING
	case DIR_WEST, MossdeepCity_SpaceCenter_1F_EventScript_MoveGruntFromStairsWest
	#ifdef BUGFIX
	case DIR_EAST, MossdeepCity_SpaceCenter_1F_EventScript_MoveGruntFromStairsEast
	#else
	case DIR_WEST, MossdeepCity_SpaceCenter_1F_EventScript_MoveGruntFromStairsEast
	#endif
	applymovement LOCALID_STAIR_GRUNT, MossdeepCity_SpaceCenter_1F_Movement_MoveGruntFromStairs
	waitmovement 0
	setvar VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE, 2
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_Grunt2Defeated:: @ 822326E
	msgbox MossdeepCity_SpaceCenter_1F_Text_Grunt2PostBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_SpaceCenter_1F_EventScript_MoveGruntFromStairsWest:: @ 8223278
	applymovement LOCALID_STAIR_GRUNT, MossdeepCity_SpaceCenter_1F_Movement_MoveGruntFromStairsWest
	waitmovement 0
	setvar VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE, 1
	release
	end

@ Functionally unused by mistake. The movement is handled anyway after the switch (see above)
@ This also means VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE can never be 3
MossdeepCity_SpaceCenter_1F_EventScript_MoveGruntFromStairsEast:: @ 8223289
	applymovement LOCALID_STAIR_GRUNT, MossdeepCity_SpaceCenter_1F_Movement_MoveGruntFromStairsEast
	waitmovement 0
	setvar VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE, 3
	release
	end

MossdeepCity_SpaceCenter_1F_Movement_MoveGruntFromStairsWest: @ 822329A
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

@ Functionally unused. See above
MossdeepCity_SpaceCenter_1F_Movement_MoveGruntFromStairsEast: @ 822329E
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

@ This was meant to only handle the player facing North, but by mistake(?) it also handles the player facing East
MossdeepCity_SpaceCenter_1F_Movement_MoveGruntFromStairs: @ 82232A2
	face_left
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

MossdeepCity_SpaceCenter_1F_Text_RocketLaunchImminent: @ 82232A7
	.string "이제 곧 로켓 발사할 거야!$"
	@ もうすぐ ロケットが はっしゃ するぞ!

MossdeepCity_SpaceCenter_1F_Text_SuccessfulLaunchNumber: @ 82232C8
	.string "로켓이 발사됐어!\n"
	.string "이걸로 {STR_VAR_1}번째 발사 성공이야!$"
	@ ロケットが はっしゃ したよ!ｎ
	@ これで §いかい うちあげ せいこうだ!

MossdeepCity_SpaceCenter_1F_Text_HaywireButRocketLaunchImminent: @ 8223305
	.string "이런 소란 중에도...\p"
	.string "이제 곧 로켓 발사할 거야!$"
	@ こんな さわぎの とちゅう だけど……ｐ
	@ もうすぐ ロケットが はっしゃ するぞ!

MossdeepCity_SpaceCenter_1F_Text_HaywireButSuccessfulLaunchNumber: @ 822335E
	.string "이런 소란 중에도...\p"
	.string "로켓이 발사됐어!\n"
	.string "이걸로 {STR_VAR_1}번째 발사 성공이야!$"
	@ こんな さわぎの とちゅう だけど……ｐ
	@ ロケットが はっしゃ したよ!ｎ
	@ これで §いかい うちあげ せいこうだ!

MossdeepCity_SpaceCenter_1F_Text_RocketLaunchDemandsPerfection: @ 82233D3
	.string "로켓을 발사하는 데에는\n"
	.string "1퍼센트의 실수도 용납되지 않아\p"
	.string "99퍼센트 문제가 없다고 해도\n"
	.string "1퍼센트의 실수로\l"
	.string "모든 게 실패하게 되는 혹독한 세계지\p"
	.string "그럼에도 반드시 성공시키려는 건\n"
	.string "거기에 로망이 가득 차 있기 때문이야$"
	@ ロケットを はっしゃ するにはｎ
	@ 1パ-セントの ミスも ゆるされないｐ
	@ 99パ-セント だいじょうぶ でもｎ
	@ 1パ-セント ダメならｌ
	@ すべてが ダメになる きびしい ものだｐ
	@ それでも やりとげようと するのはｎ
	@ そこに ロマンが つまっている からだな

MossdeepCity_SpaceCenter_1F_Text_MagmaHaveSightsOnSpaceCenter: @ 82234B7
	.string "마그마단 녀석들이\n"
	.string "이 우주센터를 노리고 있어\p"
	.string "하지만 그 정도 일로\n"
	.string "로켓 발사를\l"
	.string "멈출 생각은 없다고!$"
	@ マグマだんの やつらがｎ
	@ この うちゅうセンタ-を ねらっているｐ
	@ だが そんなこと ぐらいでｎ
	@ ロケットの はっしゃをｌ
	@ やめるわけには いかないんだ!

MossdeepCity_SpaceCenter_1F_Text_FoundThisYouCanHaveIt: @ 8223540
	.string "해안에서 산책하면서\n"
	.string "이걸 발견했는데\l"
	.string "난 필요 없으니까 너 줄게!$"
	@ かいがんを さんぽ していてｎ
	@ これを みつけたんだけどｌ
	@ ぼくは いらないから きみに あげる!

MossdeepCity_SpaceCenter_1F_Text_HoennFamousForMeteorShowers: @ 82235A6
	.string "예로부터 호연지방은\n"
	.string "운석이 많은 곳으로\l"
	.string "유명하단 말이지$"
	@ むかしから ホウエンちほうはｎ
	@ いんせきの おおい ばしょ としてｌ
	@ ゆうめい なんだよね

MossdeepCity_SpaceCenter_1F_Text_MagmaCantStealFuelTakeThis: @ 82235F0
	.string "마그마단에게 로켓연료를\n"
	.string "빼앗기면 안 돼!\p"
	.string "그나저나 해안에서 주운 이 돌을\n"
	.string "너에게 줄게!$"
	@ マグマだんに ロケットねんりょうをｎ
	@ うばわれる わけには いかない!ｐ
	@ でも かいがんで みつけた このいしはｎ
	@ きみに あげるよ!

MossdeepCity_SpaceCenter_1F_Text_CantStrollOnBeachWithMagma: @ 8223664
	.string "마그마단을 쫓아내야 해\n"
	.string "해안에서 산책할 때가 아냐!$"
	@ マグマだんを おっぱらわなきゃｎ
	@ かいがんの さんぽ どころじゃないね!

MossdeepCity_SpaceCenter_1F_Text_DidPokemonComeFromSpace: @ 82236A6
	.string "사람에 따라선\n"
	.string "포켓몬은 우주에서 왔다!\l"
	.string "라고도 하던데 진짜일까-?$"
	@ ひとに よってはｎ
	@ ポケモンは うちゅうから やってきた!ｌ
	@ って いうよね! ほんとう かな-?

MossdeepCity_SpaceCenter_1F_Text_AquaShouldBeatMagma: @ 82236E8
	.string "마그마단 같은 건\n"
	.string "아쿠아단이 해치우면 좋을 텐데!\p"
	.string "하지만 그렇게 되면 그때는\n"
	.string "아쿠아단이 날뛰게 되겠지$"
	@ マグマだん なんてｎ
	@ アクアだんが やっつければ いいのよ!ｐ
	@ でも そうすると こんどはｎ
	@ アクアだんが おおきなかおを するのよね

MossdeepCity_SpaceCenter_1F_Text_RocketsBoggleMyMind: @ 822375B
	.string "거대한 철 덩어리가\n"
	.string "창공을 뚫고\l"
	.string "우주까지 날아간다...\p"
	.string "정말 끝내주지$"
	@ でっかい てつの かたまりがｎ
	@ おおぞらを つきぬけｌ
	@ うちゅうまで とんで いく……ｐ
	@ たまげた もん だわい

MossdeepCity_SpaceCenter_1F_Text_MagmaWantsToSpoilMyDream: @ 82237B5
	.string "거대한 철 덩어리가\n"
	.string "창공을 뚫고\l"
	.string "우주까지 날아간다...\p"
	.string "그런 내 꿈을 방해하다니\n"
	.string "마그마단 놈들! 으으으 용서 못 해!$"
	@ でっかい てつの かたまりがｎ
	@ おおぞらを つきぬけｌ
	@ うちゅうまで とんで いく……ｐ
	@ そんな わしのゆめを ジャマするｎ
	@ マグマだんめ! ぬぬぬ ゆるさん!

MossdeepCity_SpaceCenter_1F_Text_StevenMagmaCantBeAllowedToTakeFuel: @ 8223849
	.string "성호: {PLAYER}{K_AYA} 거기에 있는\n"
	.string "예고장은 이미 읽었어?\p"
	.string "마그마단은 이 섬에 있는\n"
	.string "로켓연료를 빼앗으려고 해!\p"
	.string "뭐에 쓰려고 하는지는 모르겠지만\n"
	.string "녀석들한테 넘길 순 없지!\p"
	.string "나는 여기서 조금 더\n"
	.string "망을 볼 테니까 너는 마을이라도\l"
	.string "견학하고 있는 게 어때$"
	@ ダイゴ『§あ§お そこにあるｎ
	@ よこくじょうは もう よんだかい?ｐ
	@ マグマだんは このしまに あるｎ
	@ ロケットねんりょうを ねらっている!ｐ
	@ なにに つかうのか しらないけどｎ
	@ かれらに わたす わけには いかないよ!ｐ
	@ ボクは もうすこし ここでｎ
	@ みはって いるから きみは まちでもｌ
	@ けんぶつ してきたら どうかな

MossdeepCity_SpaceCenter_1F_Text_Grunt3Intro: @ 822396C
	.string "약속대로 로켓연료를\n"
	.string "받으러 왔다!$"
	@ やくそく どおり ロケットねんりょうをｎ
	@ ちょうだいしに きたわよ!

MossdeepCity_SpaceCenter_1F_Text_Grunt3Defeat: @ 8223999
	.string "연료가 떨어졌어...$"
	@ ねんりょうぎれ……

MossdeepCity_SpaceCenter_1F_Text_Grunt3PostBattle: @ 82239AA
	.string "나한테 이긴 정도로\n"
	.string "우쭐해지면 안 된다고!$"
	@ わたしに かった ぐらいでｎ
	@ ちょうしに のってちゃ ダメよ!

MossdeepCity_SpaceCenter_1F_Text_Grunt1Intro: @ 82239E6
	.string "제대로 예고를 하고 왔어!\n"
	.string "우린 비겁하지 않아!$"
	@ ちゃんと よこく してから きたんだ!ｎ
	@ オレたちゃ ひきょうものじゃ ないぜ!

MossdeepCity_SpaceCenter_1F_Text_Grunt1Defeat: @ 8223A21
	.string "으-음... 비겁한 수를\n"
	.string "쓸 걸 그랬나...$"
	@ う-む…… ひきょうな てをｎ
	@ つかえば よかった……

MossdeepCity_SpaceCenter_1F_Text_Grunt1PostBattle: @ 8223A4B
	.string "알았어 다음에 올 때는\n"
	.string "갑자기 쳐들어오도록 할게...$"
	@ わかったよ こんど くるときはｎ
	@ いきなり くるように するよ……

MossdeepCity_SpaceCenter_1F_Text_Grunt4Intro: @ 8223A8A
	.string "우주센터에 저장되어 있는\n"
	.string "로켓의 연료는\l"
	.string "전부 우리가 받아가겠어!$"
	@ うちゅうセンタ-に ちょぞう してあるｎ
	@ ロケットの ねんりょうはｌ
	@ ぜんぶ オレたちが いただいて いくぜ!

MossdeepCity_SpaceCenter_1F_Text_Grunt4Defeat: @ 8223AFA
	.string "컵이라도 좋으니까\n"
	.string "연료를 주면 안 될까?$"
	@ コップいっぱいで いいからｎ
	@ ねんりょう くれない?

MossdeepCity_SpaceCenter_1F_Text_Grunt4PostBattle: @ 8223B37
	.string "연료를 어디에 쓸 거냐고?\n"
	.string "그런 걸 내가 어떻게 알아!\l"
	.string "2층에 있는 리더한테 물어봐!$"
	@ ねんりょうの つかいみち?ｎ
	@ そんなこと オレは しらん!ｌ
	@ 2かいに いる リ-ダ-に きいてくれ!

MossdeepCity_SpaceCenter_1F_Text_Grunt2Intro: @ 8223B90
	.string "리더한테 아무도 지나가지\n"
	.string "못하게 하라고 들었는데!$"
	@ リ-ダ-から だれも ここを とおすなｎ
	@ って いわれてるんだよ!

MossdeepCity_SpaceCenter_1F_Text_Grunt2Defeat: @ 8223BC2
	.string "앗 앗 앗$"
	@ あっ あっ あっ

MossdeepCity_SpaceCenter_1F_Text_Grunt2PostBattle: @ 8223BD3
	.string "리더에게 내가 마지막까지\n"
	.string "자리를 지켰다고\l"
	.string "말해두는 거 잊지 마!$"
	@ リ-ダ-には オレが さいごまでｎ
	@ もちばを はなれなかった ってｌ
	@ いっといて くれよ!

MossdeepCity_SpaceCenter_1F_Text_MagmaIntentToStealNotice: @ 8223C2C
	.string "이건...\n"
	.string "범행 예고장?\p"
	.string "“우주센터 여러분\n"
	.string "  잘 지내고 계십니까\p"
	.string "  로켓의 연료는\n"
	.string "  곧 저희가 받아가겠습니다\l"
	.string "  거절해도 어쩔 수 없답니다\p"
	.string "  더 많은 땅을!\n"
	.string "                           마그마단”$"
	@ これは……ｎ
	@ はんこう よこくじょう?ｐ
	@ 「うちゅうセンタ-の みなさんｎ
	@  いかが おすごしで しょうかｐ
	@  ロケットの ねんりょうはｎ
	@  まもなく われわれが いただきますｌ
	@  イヤだと いっても ムダなので-すｐ
	@  もっと りくちを!ｎ
	@               マグマだん
