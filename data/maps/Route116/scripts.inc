.set LOCALID_BRINEY, 11
.set LOCALID_WANDAS_BF_OUTSIDE, 21

Route116_MapScripts:: @ 81F2C0C
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route116_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route116_OnFrame
	.byte 0

Route116_OnTransition: @ 81F2C1C
	call_if_set FLAG_RECOVERED_DEVON_GOODS, Route116_EventScript_SetWandasBoyfriendPos
	compare VAR_SHOULD_END_ABNORMAL_WEATHER, 1
	call_if_eq AbnormalWeather_EventScript_HideMapNamePopup
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_NORTH
	call_if_eq AbnormalWeather_StartGroudonWeather
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_SOUTH
	call_if_eq AbnormalWeather_StartGroudonWeather
	end

Route116_EventScript_SetWandasBoyfriendPos:: @ 81F2C47
	setobjectxyperm LOCALID_WANDAS_BF_OUTSIDE, 38, 10
	return

Route116_OnLoad: @ 81F2C4F
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_NORTH
	call_if_eq AbnormalWeather_EventScript_PlaceTilesRoute116North
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_SOUTH
	call_if_eq AbnormalWeather_EventScript_PlaceTilesRoute116South
	end

Route116_OnFrame: @ 81F2C66
	map_script_2 VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_EndEventAndCleanup_1
	.2byte 0

Route116_EventScript_WandasBoyfriend:: @ 81F2C70
	lock
	faceplayer
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, Route116_EventScript_BoyfriendGruntLeftTunnel
	goto_if_set FLAG_DEVON_GOODS_STOLEN, Route116_EventScript_BoyfriendGruntInTunnel
	msgbox Route116_Text_WantToDigTunnel, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_BoyfriendGruntLeftTunnel:: @ 81F2C8E
	msgbox Route116_Text_GoonHightailedItOutOfTunnel, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_BoyfriendGruntInTunnel:: @ 81F2C98
	msgbox Route116_Text_DiggingTunnelWhenGoonOrderedMeOut, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_DevonEmployee:: @ 81F2CA2
	lock
	faceplayer
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, Route116_EventScript_TryGiveRepeatBallAgain
	msgbox Route116_Text_ThankYouTokenOfAppreciation, MSGBOX_DEFAULT
	goto Route116_EventScript_GiveRepeatBall
	end

Route116_EventScript_GiveRepeatBall:: @ 81F2CBB
	setflag FLAG_MET_DEVON_EMPLOYEE
	giveitem ITEM_REPEAT_BALL
	compare VAR_RESULT, FALSE
	goto_if_eq Route116_EventScript_NoRoomForRepeatBall
	msgbox Route116_Text_NewBallAvailableAtMart, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_NORTH
	call_if_eq Route116_EventScript_DevonEmployeeExit
	compare VAR_FACING, DIR_SOUTH
	call_if_eq Route116_EventScript_DevonEmployeeExit
	compare VAR_FACING, DIR_WEST
	call_if_eq Route116_EventScript_DevonEmployeeExit
	compare VAR_FACING, DIR_EAST
	call_if_eq Route116_EventScript_DevonEmployeeExitEast
	removeobject VAR_LAST_TALKED
	clearflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setflag FLAG_RECEIVED_REPEAT_BALL
	release
	end

Route116_EventScript_DevonEmployeeExit:: @ 81F2D15
	applymovement VAR_LAST_TALKED, Route116_Movement_DevonEmployeeExit
	waitmovement 0
	return

Route116_EventScript_DevonEmployeeExitEast:: @ 81F2D20
	applymovement VAR_LAST_TALKED, Route116_Movement_DevonEmployeeExitEast
	waitmovement 0
	return

Route116_EventScript_TryGiveRepeatBallAgain:: @ 81F2D2B
	msgbox Route116_Text_TokenOfAppreciation, MSGBOX_DEFAULT
	goto Route116_EventScript_GiveRepeatBall
	end

Route116_EventScript_NoRoomForRepeatBall:: @ 81F2D39
	msgbox Route116_Text_BagIsJamPacked, MSGBOX_DEFAULT
	release
	end

Route116_Movement_DevonEmployeeExit: @ 81F2D43
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route116_Movement_DevonEmployeeExitEast: @ 81F2D4C
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route116_EventScript_RouteSignRustboro:: @ 81F2D57
	msgbox Route116_Text_RouteSignRustboro, MSGBOX_SIGN
	end

Route116_EventScript_RusturfTunnelSign:: @ 81F2D60
	msgbox Route116_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

Route116_EventScript_TunnelersRestHouseSign:: @ 81F2D69
	msgbox Route116_Text_TunnelersRestHouse, MSGBOX_SIGN
	end

Route116_EventScript_TrainerTipsBToStopEvolution:: @ 81F2D72
	msgbox Route116_Text_TrainerTipsBToStopEvolution, MSGBOX_SIGN
	end

Route116_EventScript_TrainerTipsBagHasPockets:: @ 81F2D7B
	msgbox Route116_Text_TrainerTipsBagHasPockets, MSGBOX_SIGN
	end

Route116_EventScript_Briney:: @ 81F2D84
	lock
	faceplayer
	msgbox Route116_Text_ScoundrelMadeOffWithPeeko, MSGBOX_DEFAULT
	setvar VAR_ROUTE116_STATE, 2
	release
	end

Route116_EventScript_BrineyTrigger:: @ 81F2D95
	lockall
	applymovement LOCALID_BRINEY, Common_Movement_WalkInPlaceFastestRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox Route116_Text_ScoundrelMadeOffWithPeeko, MSGBOX_DEFAULT
	setvar VAR_ROUTE116_STATE, 2
	releaseall
	end

Route116_EventScript_GlassesMan:: @ 81F2DB6
	lock
	faceplayer
	checkitem ITEM_BLACK_GLASSES, 1
	compare VAR_RESULT, TRUE
	goto_if_eq Route116_EventScript_PlayerHasGlasses
	specialvar VAR_RESULT, FoundBlackGlasses
	compare VAR_RESULT, TRUE
	goto_if_eq Route116_EventScript_FoundGlassesNotOnPlayer
	msgbox Route116_Text_CanYouHelpMeFindGlasses, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_FoundGlassesNotOnPlayer:: @ 81F2DE2
	msgbox Route116_Text_CantFindGlassesNotHere, MSGBOX_DEFAULT
	closemessage
	goto Route116_EventScript_GlassesManExit
	end

Route116_EventScript_PlayerHasGlasses:: @ 81F2DF1
	msgbox Route116_Text_CanYouHelpMeFindGlasses, MSGBOX_DEFAULT
	msgbox Route116_Text_MayISeeThoseGlasses, MSGBOX_DEFAULT
	specialvar VAR_RESULT, FoundBlackGlasses
	compare VAR_RESULT, TRUE
	goto_if_eq Route116_EventScript_FoundGlassesOnPlayer
	msgbox Route116_Text_NotWhatImLookingFor, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_FoundGlassesOnPlayer:: @ 81F2E1B
	msgbox Route116_Text_NotWhatImLookingForMaybeTheyArentHere, MSGBOX_DEFAULT
	closemessage
	goto Route116_EventScript_GlassesManExit
	end

Route116_EventScript_GlassesManExit:: @ 81F2E2A
	delay 20
	compare VAR_FACING, DIR_NORTH
	call_if_eq Route116_EventScript_GlassesManExitNormal
	compare VAR_FACING, DIR_SOUTH
	call_if_eq Route116_EventScript_GlassesManExitNormal
	compare VAR_FACING, DIR_WEST
	call_if_eq Route116_EventScript_GlassesManExitNormal
	compare VAR_FACING, DIR_EAST
	call_if_eq Route116_EventScript_GlassesManExitEast
	removeobject VAR_LAST_TALKED
	release
	end

Route116_EventScript_GlassesManExitNormal:: @ 81F2E5E
	applymovement VAR_LAST_TALKED, Route116_Movement_GlassesManExit
	waitmovement 0
	return

Route116_EventScript_GlassesManExitEast:: @ 81F2E69
	applymovement VAR_LAST_TALKED, Route116_Movement_GlassesManExitEast
	waitmovement 0
	return

Route116_Movement_GlassesManExit: @ 81F2E74
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route116_Movement_GlassesManExitEast: @ 81F2E7E
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route116_EventScript_Joey:: @ 81F2E89
	trainerbattle_single TRAINER_JOEY, Route116_Text_JoeyIntro, Route116_Text_JoeyDefeat
	msgbox Route116_Text_JoeyPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Jose:: @ 81F2EA0
	trainerbattle_single TRAINER_JOSE, Route116_Text_JoseIntro, Route116_Text_JoseDefeat
	msgbox Route116_Text_JosePostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Jerry:: @ 81F2EB7
	trainerbattle_single TRAINER_JERRY_1, Route116_Text_JerryIntro, Route116_Text_JerryDefeat, Route116_EventScript_TryRegisterJerryAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route116_EventScript_RematchJerry
	setvar VAR_0x8004, TRAINER_JERRY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	compare VAR_RESULT, FALSE
	goto_if_eq Route116_EventScript_TryRegisterJerry
	msgbox Route116_Text_JerryPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_TryRegisterJerryAfterBattle:: @ 81F2EF8
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterJerryAfterBattle
	release
	end

Route116_EventScript_RegisterJerryAfterBattle:: @ 81F2F03
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route116_Text_JerryRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_JERRY_1
	release
	end

Route116_EventScript_TryRegisterJerry:: @ 81F2F22
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterJerry
	msgbox Route116_Text_JerryPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_RegisterJerry:: @ 81F2F35
	msgbox Route116_Text_JerryRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_JERRY_1
	release
	end

Route116_EventScript_RematchJerry:: @ 81F2F4E
	trainerbattle_rematch TRAINER_JERRY_1, Route116_Text_JerryRematchIntro, Route116_Text_JerryRematchDefeat
	msgbox Route116_Text_JerryPostRematch, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Clark:: @ 81F2F65
	trainerbattle_single TRAINER_CLARK, Route116_Text_ClarkIntro, Route116_Text_ClarkDefeat
	msgbox Route116_Text_ClarkPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Janice:: @ 81F2F7C
	trainerbattle_single TRAINER_JANICE, Route116_Text_JaniceIntro, Route116_Text_JaniceDefeat
	msgbox Route116_Text_JanicePostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Karen:: @ 81F2F93
	trainerbattle_single TRAINER_KAREN_1, Route116_Text_KarenIntro, Route116_Text_KarenDefeat, Route116_EventScript_TryRegisterKarenAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route116_EventScript_RematchKaren
	setvar VAR_0x8004, TRAINER_KAREN_1
	specialvar VAR_RESULT, IsTrainerRegistered
	compare VAR_RESULT, FALSE
	goto_if_eq Route116_EventScript_TryRegisterKaren
	msgbox Route116_Text_KarenPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_TryRegisterKarenAfterBattle:: @ 81F2FD4
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterKarenAfterBattle
	release
	end

Route116_EventScript_RegisterKarenAfterBattle:: @ 81F2FDF
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route116_Text_KarenRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_KAREN_1
	release
	end

Route116_EventScript_TryRegisterKaren:: @ 81F2FFE
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterKaren
	msgbox Route116_Text_KarenPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_RegisterKaren:: @ 81F3011
	msgbox Route116_Text_KarenRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_KAREN_1
	release
	end

Route116_EventScript_RematchKaren:: @ 81F302A
	trainerbattle_rematch TRAINER_KAREN_1, Route116_Text_KarenRematchIntro, Route116_Text_KarenRematchDefeat
	msgbox Route116_Text_KarenPostRematch, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Sarah:: @ 81F3041
	trainerbattle_single TRAINER_SARAH, Route116_Text_SarahIntro, Route116_Text_SarahDefeat
	msgbox Route116_Text_SarahPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Dawson:: @ 81F3058
	trainerbattle_single TRAINER_DAWSON, Route116_Text_DawsonIntro, Route116_Text_DawsonDefeat
	msgbox Route116_Text_DawsonPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Devan:: @ 81F306F
	trainerbattle_single TRAINER_DEVAN, Route116_Text_DevanIntro, Route116_Text_DevanDefeat
	msgbox Route116_Text_DevanPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Johnson:: @ 81F3086
	trainerbattle_single TRAINER_JOHNSON, Route116_Text_JohnsonIntro, Route116_Text_JohnsonDefeat
	msgbox Route116_Text_JohnsonPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_Text_ScoundrelMadeOffWithPeeko: @ 81F309D
	.string "아아아 이거 어쩌지!\p"
	.string "피코랑 같이 산책하고 있었는데\n"
	.string "갑자기 이상한 녀석이 와서\p"
	.string "내 귀여운 피코를\n"
	.string "뺏어 갔다네!\p"
	.string "오오-! 피코야-!$"
	// あああ なんという ことだ!ｐ
	// ピ-コちゃんと さんぽを していたらｎ
	// いきなり おかしな やつが やってきてｐ
	// わしの かわいい ピ-コちゃんがｎ
	// うばわれて しまったのじゃ!ｐ
	// うお-! ピ-コちゃ-ん!

Route116_Text_WantToDigTunnel: @ 81F3140
	.string "우오-!!\p"
	.string "터널 파고 싶어-!!$"
	// ぬぉ-!!ｐ
	// トンネル ほりて-!!

Route116_Text_DiggingTunnelWhenGoonOrderedMeOut: @ 81F3166
	.string "우오-!!\n"
	.string "뭐가 어떻게 된 거지!?\p"
	.string "도구고 뭐고 안 쓰고\n"
	.string "터널을 파고 있었는데\l"
	.string "이상한 남자한테 쫓겨났어!\p"
	.string "저 터널에는\n"
	.string "큰 소리에 반응해서\l"
	.string "동요하는 포켓몬이 있어\p"
	.string "그래서 기계를 사용한\n"
	.string "개발 공사도 중지했는데...\p"
	.string "괜한 소란을 피워서\n"
	.string "포켓몬이 겁먹지 않을까 걱정이야!$"
	// ぬぉ-!!ｎ
	// なんて ことだ!?ｐ
	// どうぐも なにも つかわずにｎ
	// トンネルを ほっていたのにｌ
	// へんな おとこに おいだされた!ｐ
	// あの トンネルにはｎ
	// おおきな ものおとに はんのう してｌ
	// さわぎだす ポケモンが いるｐ
	// だから きかいを つかってのｎ
	// かいはつ こうじを やめたのに……ｐ
	// へんに さわぎを おこされるとｎ
	// ポケモンが おびえないか しんぱいだ!

Route116_Text_GoonHightailedItOutOfTunnel: @ 81F32C1
	.string "우오-!!\p"
	.string "이상한 남자가 뛰쳐나왔어!\n"
	.string "이제 다시 터널을 팔 수 있어!$"
	// ぬぉ-!!ｐ
	// へんな おとこが とびだしていった!ｎ
	// これで トンネルを ほれるよ!

Route116_Text_ThankYouTokenOfAppreciation: @ 81F3317
	.string "아앗!\n"
	.string "당신은!!\p"
	.string "등화숲에서 도와준 것뿐만 아니라\n"
	.string "도둑맞은 짐도 되찾아주고\l"
	.string "거기다가 잿빛도시로의 물건 배달도\l"
	.string "흔쾌히 해준 사람!!\p"
	.string "해양관장에게\n"
	.string "“짐은 잘 도착했다”고\l"
	.string "연락이 왔었어요!\p"
	.string "정말 감사합니다!\n"
	.string "너무 감사해서 눈물이 날 정도예요\p"
	.string "그런 멋진 트레이너님에게\n"
	.string "아주 좋은 뉴스!\p"
	.string "최근 저희 회사에서\n"
	.string "새로운 몬스터볼의\l"
	.string "개발에 성공했어요!\p"
	.string "감사의 마음을 담아서\n"
	.string "트레이너님께도 선물할게요!$"
	// ああっ!ｎ
	// きみは!!ｐ
	// トウカのもりで たすけてくれた だけでなくｎ
	// ぬすまれた にもつを とりかえしｌ
	// はたまた カイナへの とどけものをｌ
	// こころよく ひきうけてくれた ひと!!ｐ
	// クスノキかんちょう からｎ
	// 「にもつが とどいた」とｌ
	// れんらくが ありましたよ!ｐ
	// どうも ありがとう なのです!ｎ
	// かんしゃ かんげき あめ あられ なのですｐ
	// そんな すてきな トレ-ナ-さんにｎ
	// グッド ニュ-ス!ｐ
	// さいきん わがしゃ ではｎ
	// あたらしい モンスタ-ボ-ルのｌ
	// かいはつに せいこう したのです!ｐ
	// かんしゃの きもちとしてｎ
	// トレ-ナ-さんにも プレゼント なのよね!

Route116_Text_NewBallAvailableAtMart: @ 81F3521
	.string "새로운 몬스터볼은\n"
	.string "금탄도시의 프렌들리숍에서도\l"
	.string "팔고 있습니다!\p"
	.string "부디 한번 사용해 보세요!\n"
	.string "그럼 이만...$"
	// あたらしい モンスタ-ボ-ルはｎ
	// カナズミの フレンドリィ ショップでｌ
	// うってますからね!ｐ
	// ぜひ つかって みてください!ｎ
	// ではでは……

Route116_Text_BagIsJamPacked: @ 81F3593
	.string "가방이 가득 차서\n"
	.string "리피드볼은 드릴 수 없겠네요$"
	// どうぐ いっぱいでｎ
	// リピ-トボ-ル あげられないね

Route116_Text_TokenOfAppreciation: @ 81F35CE
	.string "화물을 전달해주신 것에 대한\n"
	.string "감사의 표시로\l"
	.string "트레이너님께 새로운\l"
	.string "몬스터볼을 선물할게요!$"
	// にもつを とどけてくれた ことへのｎ
	// かんしゃの きもちとしてｌ
	// トレ-ナ-さん にも あたらしいｌ
	// モンスタ-ボ-ルを プレゼント なのよね!

Route116_Text_CanYouHelpMeFindGlasses: @ 81F3657
	.string "안경을 떨어뜨렸어...\n"
	.string "너도 찾는 것 좀 도와줘$"
	// メガネを おとしたんだ……ｎ
	// きみも さがすの てつだってよ

Route116_Text_MayISeeThoseGlasses: @ 81F3688
	.string "그 안경...?\n"
	.string "잠깐 좀 보여줘 봐!$"
	// その メガネ……?ｎ
	// ちょっと みせてよ!

Route116_Text_NotWhatImLookingForMaybeTheyArentHere: @ 81F36B4
	.string "으-음...\n"
	.string "이건 검은안경이네\l"
	.string "내가 찾는 게 아니야...\p"
	.string "여기엔 내 안경이 없는 걸까$"
	// う-む……ｎ
	// これは くろいメガネ だねｌ
	// ぼくが さがしているのと ちがうなあ……ｐ
	// ここには ぼくの メガネ ないのかなあ

Route116_Text_CantFindGlassesNotHere: @ 81F3718
	.string "으-음...\n"
	.string "아무리 봐도 안경을 못 찾겠어\l"
	.string "여기에는 내 안경이 없는 걸까$"
	// う-む……ｎ
	// どうにも メガネが みつからないんだｌ
	// ここには ぼくの メガネ ないのかなあ

Route116_Text_NotWhatImLookingFor: @ 81F375E
	.string "으-음...\n"
	.string "이건 검은안경이네\l"
	.string "내가 찾는 게 아니야...$"
	// う-む……ｎ
	// これは くろいメガネ だねｌ
	// ぼくが さがしているのと ちがうなあ……

Route116_Text_RouteSignRustboro: @ 81F379D
	.string "여기는 116번 도로\n"
	.string "{LEFT_ARROW} 금탄도시$"
	// ここは 116ばん どうろｎ
	// ©しい カナズミシティ

Route116_Text_RusturfTunnelSign: @ 81F37B7
	.string "금탄도시와 잔디마을을 연결하는\n"
	.string "“금잔터널”\p"
	.string "개통 공사는 중지되었습니다$"
	// カナズミと シダケを むすぶｎ
	// 「カナシダ トンネル」ｐ
	// かいつう こうじは ちゅうしに なりました

Route116_Text_TunnelersRestHouse: @ 81F380F
	.string "터널공사 작업원 대기실$"
	// トンネルこうじ さぎょういん つめしょ

Route116_Text_TrainerTipsBToStopEvolution: @ 81F3825
	.string "정보 나눔 게시판!!\p"
	.string "포켓몬이 진화할 것 같을 때\n"
	.string "B 버튼을 누르면\l"
	.string "놀라서 진화를 멈춰버려요!\p"
	.string "이걸 진화캔슬이라고 해요$"
	// おとくな けいじばん!ｐ
	// ポケモンが しんか しそうなときｎ
	// Bボタンを おすとｌ
	// びっくりして しんかを やめます!ｐ
	// これを しんかキャンセルと いいます

Route116_Text_TrainerTipsBagHasPockets: @ 81F38D4
	.string "정보 나눔 게시판!!\p"
	.string "가방에는 몇 개의 포켓이 있고\n"
	.string "넣는 도구의 종류에 따라\l"
	.string "각 포켓에\l"
	.string "자동으로 분류됩니다\p"
	.string "정말 트레이너의 필수품이에요!$"
	// おとくな けいじばん!!ｐ
	// バッグには いくつかの ポケットが ありｎ
	// いれる どうぐの しゅるい によってｌ
	// それぞれの ポケットにｌ
	// オ-トで ぶんるい されますｐ
	// まさに トレ-ナ-の ひつじゅひん です!

