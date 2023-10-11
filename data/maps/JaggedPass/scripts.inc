.set LOCALID_HIDEOUT_GUARD, 5

JaggedPass_MapScripts:: @ 8230656
	map_script MAP_SCRIPT_ON_RESUME, JaggedPass_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, JaggedPass_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, JaggedPass_OnLoad
	.byte 0

JaggedPass_OnResume: @ 8230666
	setstepcallback STEP_CB_ASH
	compare VAR_JAGGED_PASS_STATE, 0
	call_if_eq JaggedPass_EventScript_CheckHasMagmaEmblem
	end

JaggedPass_EventScript_CheckHasMagmaEmblem:: @ 8230674
	checkitem ITEM_MAGMA_EMBLEM, 1
	compare VAR_RESULT, TRUE
	goto_if_eq JaggedPass_EventScript_SetReadyToOpenHideout
	return

JaggedPass_EventScript_SetReadyToOpenHideout:: @ 8230685
	setvar VAR_JAGGED_PASS_STATE, 1
	return

JaggedPass_OnTransition: @ 823068B
	compare VAR_JAGGED_PASS_ASH_WEATHER, 1
	call_if_eq JaggedPass_EventScript_SetWeatherAsh
	end

JaggedPass_EventScript_SetWeatherAsh:: @ 8230697
	setweather WEATHER_VOLCANIC_ASH
	doweather
	return

JaggedPass_OnLoad: @ 823069C
	compare VAR_JAGGED_PASS_STATE, 1
	goto_if_le JaggedPass_EventScript_ConcealHideoutEntrance
	end

JaggedPass_EventScript_ConcealHideoutEntrance:: @ 82306A8
	setmetatile 16, 17, METATILE_Lavaridge_RockWall, 1
	setmetatile 16, 18, METATILE_Lavaridge_RockWall, 1
	end

JaggedPass_EventScript_OpenMagmaHideout:: @ 82306BB
	lockall
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	msgbox JaggedPass_Text_BoulderShakingInResponseToEmblem, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 1   @ horizontal pan
	setvar VAR_0x8006, 16  @ num shakes
	setvar VAR_0x8007, 3   @ shake delay
	special ShakeCamera
	waitstate
	playse SE_EFFECTIVE
	setmetatile 16, 17, METATILE_Lavaridge_CaveEntrance_Top, 1
	setmetatile 16, 18, METATILE_Lavaridge_CaveEntrance_Bottom, 0
	special DrawWholeMapView
	delay 30
	setvar VAR_JAGGED_PASS_STATE, 2
	waitse
	releaseall
	end

JaggedPass_EventScript_MagmaHideoutGuard:: @ 8230718
	lockall
	goto_if_set FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS, JaggedPass_EventScript_GuardDefeated
	waitse
	playse SE_PIN
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GruntIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_GRUNT_JAGGED_PASS, JaggedPass_Text_GruntDefeat
	setflag FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_GuardDefeated:: @ 8230766
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GoWhereverYouWant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_Eric:: @ 8230785
	trainerbattle_single TRAINER_ERIC, JaggedPass_Text_EricIntro, JaggedPass_Text_EricDefeat
	msgbox JaggedPass_Text_EricPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Diana:: @ 823079C
	trainerbattle_single TRAINER_DIANA_1, JaggedPass_Text_DianaIntro, JaggedPass_Text_DianaDefeat, JaggedPass_EventScript_RegisterDiana
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq JaggedPass_EventScript_DianaRematch
	msgbox JaggedPass_Text_DianaPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterDiana:: @ 82307C8
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_DianaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DIANA_1
	release
	end

JaggedPass_EventScript_DianaRematch:: @ 82307E4
	trainerbattle_rematch TRAINER_DIANA_1, JaggedPass_Text_DianaRematchIntro, JaggedPass_Text_DianaRematchDefeat
	msgbox JaggedPass_Text_DianaPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Ethan:: @ 82307FB
	trainerbattle_single TRAINER_ETHAN_1, JaggedPass_Text_EthanIntro, JaggedPass_Text_EthanDefeat, JaggedPass_EventScript_RegisterEthan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq JaggedPass_EventScript_EthanRematch
	msgbox JaggedPass_Text_EthanPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterEthan:: @ 8230827
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_EthanRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ETHAN_1
	release
	end

JaggedPass_EventScript_EthanRematch:: @ 8230843
	trainerbattle_rematch TRAINER_ETHAN_1, JaggedPass_Text_EthanRematchIntro, JaggedPass_Text_EthanRematchDefeat
	msgbox JaggedPass_Text_EthanPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Julio:: @ 823085A
	trainerbattle_single TRAINER_JULIO, JaggedPass_Text_JulioIntro, JaggedPass_Text_JulioDefeat
	msgbox JaggedPass_Text_JulioPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Autumn:: @ 8230871
	trainerbattle_single TRAINER_AUTUMN, JaggedPass_Text_AutumnIntro, JaggedPass_Text_AutumnDefeat
	msgbox JaggedPass_Text_AutumnPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_Text_EricIntro: @ 8230888
	.string "굴뚝산의 울퉁불퉁 산길은\n"
	.string "그야말로 내가 꿈에 그리던 산이야!\l"
	.string "이 울퉁불퉁함이 너무 좋아서 참을 수 없어!$"
	// えんとつやまの デコボコさんどうｎ
	// まさに わたしが もとめていた やま!ｌ
	// この デコボコした ところが たまらん!

JaggedPass_Text_EricDefeat: @ 82308FF
	.string "져버려서 분해!$"
	// まけて くやしいぞ!

JaggedPass_Text_EricPostBattle: @ 8230916
	.string "확실히 포켓몬 승부에서는 졌다...\p"
	.string "하지만 산을 사랑하는 마음만큼은\n"
	.string "나의 승리겠지!$"
	// たしかに ポケモンでは まけた……ｐ
	// だが やまを あいする きもちならｎ
	// わたしの ほうが まさっているだろ!

JaggedPass_Text_DianaIntro: @ 8230974
	.string "여긴 가벼운 마음으로 오르면 안 되겠다\n"
	.string "피크닉엔 좀 안 어울려$"
	// ここは きがるに のぼって いけないものｎ
	// ちょっと ピクニックむき じゃないわ

JaggedPass_Text_DianaDefeat: @ 82309B5
	.string "아-잉! 정말!\n"
	.string "발밑이 울퉁불퉁하니까...$"
	// あ-ん もう!ｎ
	// したが デコボコだから……

JaggedPass_Text_DianaPostBattle: @ 82309D8
	.string "이렇게 울퉁불퉁한 곳을\n"
	.string "자전거로 잘 올라가는\l"
	.string "사람도 있어!$"
	// こんな デコボコしたところｎ
	// じてんしゃで じょうずに のぼっていくｌ
	// ひとも いるのよ!

JaggedPass_Text_DianaRegister: @ 8230A2C
	.string "또 여기에 오려나?\n"
	.string "그렇게 되면 나와 승부해줘!$"
	// また ここに くることって あるかな?ｎ
	// そしたら わたしと しょうぶしてね!

JaggedPass_Text_DianaRematchIntro: @ 8230A76
	.string "어떤 길이라도 피크닉은 즐거워!\n"
	.string "포켓몬도 같이 있고 말이야!$"
	// どんな みちも ピクニックは たのしい!ｎ
	// ポケモンも いっしょ だしね!

JaggedPass_Text_DianaRematchDefeat: @ 8230AAA
	.string "발밑이 울퉁불퉁해서\n"
	.string "져버린 거야!$"
	// まけたのはｎ
	// したが デコボコだからよ!

JaggedPass_Text_DianaPostRematch: @ 8230AD7
	.string "패배한 건 얼른 잊어버리고\n"
	.string "이 울퉁불퉁한 길을 실컷 즐겨야지!$"
	// まけたことは さっさと わすれてｎ
	// この デコボコみちを たのしんじゃお!

JaggedPass_Text_EthanIntro: @ 8230B10
	.string "이 울퉁불퉁 산길은 걷기가 무척 힘들지!\n"
	.string "포켓몬을 단련시키기에 딱 좋은 곳이다!$"
	// この デコボコさんどうは あるきにくい!ｎ
	// ポケモンを きたえるのに むいてるよ!

JaggedPass_Text_EthanDefeat: @ 8230B50
	.string "발밑을 신경 쓰는 사이에\n"
	.string "끝나버린 모양이군...$"
	// あしばを きにしてる うちにｎ
	// おわっちゃった かんじだ……

JaggedPass_Text_EthanPostBattle: @ 8230B93
	.string "나도 더트자전거가 있으면\n"
	.string "턱을 뛰어넘을 수 있을 텐데$"
	// ぼくも ダ-トじてんしゃ もっていればｎ
	// だんさを とびこえて いけるのにな

JaggedPass_Text_EthanRegister: @ 8230BC6
	.string "좀 더 울퉁불퉁한 길에 익숙해지면\n"
	.string "이번에야말로 이길 수 있어!\l"
	.string "나를 포켓내비에 등록해둬$"
	// もうちょっと デコボコに なれたらｎ
	// こんどこそ かつぞ!ｌ
	// ぼくを ポケナビに とうろく しといてよ

JaggedPass_Text_EthanRematchIntro: @ 8230C28
	.string "울퉁불퉁한 길에 익숙해져서\n"
	.string "요즘엔 노래를 부르면서 올라갈 정도야!$"
	// デコボコに なれちゃったからｎ
	// ちかごろだと うたいながら のぼるのさ!

JaggedPass_Text_EthanRematchDefeat: @ 8230C60
	.string "역시 울퉁불퉁하니까\n"
	.string "배틀하기 힘들어...$"
	// やっぱり デコボコだとｎ
	// たたかいにくいよ……

JaggedPass_Text_EthanPostRematch: @ 8230C94
	.string "나도 보라시티에 있는 카제노님에게\n"
	.string "더트자전거를 달라고 해볼까$"
	// ぼくも キンセツで カゼノさんからｎ
	// ダ-トじてんしゃ もらおうかな

JaggedPass_Text_GruntIntro: @ 8230CCB
	.string "우왓!? ...뭐야 너!\p"
	.string "내가\n"
	.string "  이런\l"
	.string "    곳에서\l"
	.string "뭘 하고\l"
	.string "  있는지\l"
	.string "    같은 건\l"
	.string "너하고는 하나도\l"
	.string "관 계 없 잖 아!$"
	// うわっ!? ……なんだ おまえ!ｐ
	// オレがｎ
	//   こんなｌ
	//     ところでｌ
	// なにをｌ
	//   してるかｌ
	//     なんてｌ
	// おまえにゃ カンケ-ｌ
	// な い だ ろ が!

JaggedPass_Text_GruntDefeat: @ 8230D2D
	.string "으그극...\p"
	.string "빨리\n"
	.string "  아지트로\l"
	.string "    도망쳐야\l"
	.string "      했는데...$"
	// うぐぐ……ｐ
	// はやくｎ
	//   アジトにｌ
	//     にげこめばｌ
	//       よかった……

JaggedPass_Text_GoWhereverYouWant: @ 8230D65
	.string "알았어 알았어!\n"
	.string "네가 강한 건 인정해 줄게!\p"
	.string "난 신경 쓰지 말고\n"
	.string "가고 싶은 곳이나 가라고!$"
	// わかった わかった!ｎ
	// キミが つよいのは みとめて やるよ!ｐ
	// オレのことは きにせずｎ
	// すきな ところへ いきな!

JaggedPass_Text_BoulderShakingInResponseToEmblem: @ 8230DBA
	.string "앗! 마그마의증표에 반응해서...\n"
	.string "커다란 바위가...\l"
	.string "부들부들 진동하고 있다!$"
	// あ! マグマのしるしに はんのうして……ｎ
	// おおきな いわが……ｌ
	// ブルブルと しんどう している!

JaggedPass_Text_JulioIntro: @ 8230DF7
	.string "자전거로 단숨에\n"
	.string "내려오면 무서워어어!$"
	// じてんしゃで いっきにｎ
	// おりて くると こわいぃぃ!

JaggedPass_Text_JulioDefeat: @ 8230E38
	.string "덜덜덜덜$"
	// ガッタガタ

JaggedPass_Text_JulioPostBattle: @ 8230E57
	.string "자전거가 엄청\n"
	.string "튀어서 엉덩이가 아파...$"
	// じてんしゃが おもいっきりｎ
	// バウンド して おしりが イタイ……

JaggedPass_Text_AutumnIntro: @ 8230E8E
	.string "매일 여기를 오르고 있어\n"
	.string "힘에는 자신이 있거든!$"
	// まいにち ここを のぼっているわｎ
	// パワ-には じしん あるんだから!

JaggedPass_Text_AutumnDefeat: @ 8230ECD
	.string "음- 이상하네...$"
	// ん- おっかしいな……

JaggedPass_Text_AutumnPostBattle: @ 8230EE3
	.string "조금 올라가면 있는\n"
	.string "이상한 튀어나온 부분은 뭘까...?$"
	// すこし のぼった ところにあるｎ
	// おかしな でっぱりは なにかしら……?

