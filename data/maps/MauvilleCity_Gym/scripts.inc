MauvilleCity_Gym_MapScripts:: @ 820DD6E
	map_script MAP_SCRIPT_ON_LOAD, MauvilleCity_Gym_OnLoad
	.byte 0

MauvilleCity_Gym_OnLoad: @ 820DD74
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_DeactivatePuzzle
	switch VAR_MAUVILLE_GYM_STATE
	case 0, MauvilleCity_Gym_EventScript_UpdateBarriers
	case 1, MauvilleCity_Gym_EventScript_Switch1Pressed
	case 2, MauvilleCity_Gym_EventScript_Switch2Pressed
	case 3, MauvilleCity_Gym_EventScript_Switch3Pressed
	case 4, MauvilleCity_Gym_EventScript_Switch4Pressed
	end

MauvilleCity_Gym_EventScript_UpdateBarriers:: @ 820DDBA
	goto_if_set FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_SetAltBarriers
	end

MauvilleCity_Gym_EventScript_SetAltBarriers:: @ 820DDC4
	setmetatile 3, 11, METATILE_MauvilleGym_RedBeamV1_On, 1
	setmetatile 3, 12, METATILE_MauvilleGym_RedBeamV2_On, 1
	setmetatile 3, 13, METATILE_MauvilleGym_PoleTop_On, 1
	setmetatile 4, 10, METATILE_MauvilleGym_RedBeamH1_On, 0
	setmetatile 5, 10, METATILE_MauvilleGym_RedBeamH2_On, 0
	setmetatile 4, 11, METATILE_MauvilleGym_RedBeamH3_On, 1
	setmetatile 5, 11, METATILE_MauvilleGym_RedBeamH4_On, 1
	setmetatile 7, 10, METATILE_MauvilleGym_RedBeamH1_On, 0
	setmetatile 8, 10, METATILE_MauvilleGym_RedBeamH2_On, 0
	setmetatile 7, 11, METATILE_MauvilleGym_RedBeamH3_On, 1
	setmetatile 8, 11, METATILE_MauvilleGym_RedBeamH4_On, 1
	setmetatile 4, 13, METATILE_MauvilleGym_GreenBeamH1_Off, 0
	setmetatile 5, 13, METATILE_MauvilleGym_GreenBeamH2_Off, 0
	setmetatile 4, 14, METATILE_MauvilleGym_GreenBeamH3_Off, 0
	setmetatile 5, 14, METATILE_MauvilleGym_GreenBeamH4_Off, 0
	setmetatile 1, 10, METATILE_MauvilleGym_GreenBeamH1_Off, 0
	setmetatile 2, 10, METATILE_MauvilleGym_GreenBeamH2_Off, 0
	setmetatile 1, 11, METATILE_MauvilleGym_GreenBeamH3_Off, 0
	setmetatile 2, 11, METATILE_MauvilleGym_GreenBeamH4_Off, 0
	setmetatile 6, 8, METATILE_MauvilleGym_PoleBottom_On, 1
	setmetatile 6, 9, METATILE_MauvilleGym_FloorTile, 0
	setmetatile 6, 10, METATILE_MauvilleGym_PoleTop_Off, 0
	setmetatile 4, 6, METATILE_MauvilleGym_GreenBeamH1_Off, 0
	setmetatile 5, 6, METATILE_MauvilleGym_GreenBeamH2_Off, 0
	setmetatile 4, 7, METATILE_MauvilleGym_GreenBeamH3_Off, 0
	setmetatile 5, 7, METATILE_MauvilleGym_GreenBeamH4_Off, 0
	end

MauvilleCity_Gym_EventScript_Switch1Pressed:: @ 820DEAF
	setvar VAR_0x8004, 0
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch2Pressed:: @ 820DEBD
	setvar VAR_0x8004, 1
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch3Pressed:: @ 820DECB
	setvar VAR_0x8004, 2
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch4Pressed:: @ 820DED9
	setvar VAR_0x8004, 3
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_DeactivatePuzzle:: @ 820DEE7
	special MauvilleGymDeactivatePuzzle
	end

MauvilleCity_Gym_EventScript_Wattson:: @ 820DEEB
	trainerbattle_single TRAINER_WATTSON_1, MauvilleCity_Gym_Text_WattsonIntro, MauvilleCity_Gym_Text_WattsonDefeat, MauvilleCity_Gym_EventScript_WattsonDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_Gym_EventScript_WattsonRematch
	goto_if_unset FLAG_RECEIVED_TM34, MauvilleCity_Gym_EventScript_GiveShockWave2
	compare VAR_NEW_MAUVILLE_STATE, 2
	goto_if_eq MauvilleCity_Gym_EventScript_CompletedNewMauville
	msgbox MauvilleCity_Gym_Text_WattsonPostBattle, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_WattsonDefeated:: @ 820DF2B
	message MauvilleCity_Gym_Text_ReceivedDynamoBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MauvilleCity_Gym_Text_ExplainDynamoBadgeTakeThis, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 3
	clearflag FLAG_HIDE_VERDANTURF_TOWN_SCOTT
	setflag FLAG_DEFEATED_MAUVILLE_GYM
	setflag FLAG_BADGE03_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	compare VAR_PETALBURG_GYM_STATE, 6
	call_if_eq Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 3
	call Common_EventScript_SetGymTrainers
	special MauvilleGymDeactivatePuzzle
	special DrawWholeMapView
	playse SE_UNLOCK
	call MauvilleCity_Gym_EventScript_GiveShockWave
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Gym_Text_RegisteredWattson, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WATTSON_MATCH_CALL
	release
	end

MauvilleCity_Gym_EventScript_GiveShockWave2:: @ 820DF8D
	giveitem ITEM_TM34
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	msgbox MauvilleCity_Gym_Text_ExplainShockWave, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM34
	release
	end

MauvilleCity_Gym_EventScript_GiveShockWave:: @ 820DFB1
	giveitem ITEM_TM34
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_BagIsFull
	msgbox MauvilleCity_Gym_Text_ExplainShockWave, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM34
	return

MauvilleCity_Gym_EventScript_CompletedNewMauville:: @ 820DFD4
	msgbox MauvilleCity_Gym_Text_WattsonGoForthAndEndeavor, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_WattsonRematch:: @ 820DFDE
	trainerbattle_rematch_double TRAINER_WATTSON_1, MauvilleCity_Gym_Text_WattsonPreRematch, MauvilleCity_Gym_Text_WattsonRematchDefeat, MauvilleCity_Gym_Text_WattsonRematchNeedTwoMons
	msgbox MauvilleCity_Gym_Text_WattsonPostRematch, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Switch1:: @ 820DFF9
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	compare VAR_MAUVILLE_GYM_STATE, 1
	goto_if_eq MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 1
	setvar VAR_0x8004, 0
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch2:: @ 820E01E
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	compare VAR_MAUVILLE_GYM_STATE, 2
	goto_if_eq MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 2
	setvar VAR_0x8004, 1
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch3:: @ 820E043
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	compare VAR_MAUVILLE_GYM_STATE, 3
	goto_if_eq MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 3
	setvar VAR_0x8004, 2
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch4:: @ 820E068
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	compare VAR_MAUVILLE_GYM_STATE, 4
	goto_if_eq MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 4
	setvar VAR_0x8004, 3
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_PressFloorSwitch:: @ 820E08D
	special MauvilleGymSetDefaultBarriers
	special MauvilleGymPressSwitch
	special DrawWholeMapView
	playse SE_UNLOCK
	goto_if_set FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_ClearBarriersAltState
	goto_if_unset FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_SetBarriersAltState
	releaseall
	end

MauvilleCity_Gym_EventScript_SwitchDoNothing:: @ 820E0AD
	releaseall
	end

MauvilleCity_Gym_EventScript_SetBarriersAltState:: @ 820E0AF
	setflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	releaseall
	end

MauvilleCity_Gym_EventScript_ClearBarriersAltState:: @ 820E0B4
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	releaseall
	end

MauvilleCity_Gym_EventScript_Kirk:: @ 820E0B9
	trainerbattle_single TRAINER_KIRK, MauvilleCity_Gym_Text_KirkIntro, MauvilleCity_Gym_Text_KirkDefeat
	msgbox MauvilleCity_Gym_Text_KirkPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Shawn:: @ 820E0D0
	trainerbattle_single TRAINER_SHAWN, MauvilleCity_Gym_Text_ShawnIntro, MauvilleCity_Gym_Text_ShawnDefeat
	msgbox MauvilleCity_Gym_Text_ShawnPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Ben:: @ 820E0E7
	trainerbattle_single TRAINER_BEN, MauvilleCity_Gym_Text_BenIntro, MauvilleCity_Gym_Text_BenDefeat
	msgbox MauvilleCity_Gym_Text_BenPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Vivian:: @ 820E0FE
	trainerbattle_single TRAINER_VIVIAN, MauvilleCity_Gym_Text_VivianIntro, MauvilleCity_Gym_Text_VivianDefeat
	msgbox MauvilleCity_Gym_Text_VivianPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Angelo:: @ 820E115
	trainerbattle_single TRAINER_ANGELO, MauvilleCity_Gym_Text_AngeloIntro, MauvilleCity_Gym_Text_AngeloDefeat
	msgbox MauvilleCity_Gym_Text_AngeloPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_GymGuide:: @ 820E12C
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_GymGuidePostVictory
	msgbox MauvilleCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_GymGuidePostVictory:: @ 820E141
	msgbox MauvilleCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_LeftGymStatue:: @ 820E14B
	lockall
	goto_if_set FLAG_BADGE03_GET, MauvilleCity_Gym_EventScript_GymStatueCertified
	goto MauvilleCity_Gym_EventScript_GymStatue
	end

MauvilleCity_Gym_EventScript_RightGymStatue:: @ 820E15B
	lockall
	goto_if_set FLAG_BADGE03_GET, MauvilleCity_Gym_EventScript_GymStatueCertified
	goto MauvilleCity_Gym_EventScript_GymStatue
	end

MauvilleCity_Gym_EventScript_GymStatueCertified:: @ 820E16B
	msgbox MauvilleCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_Gym_EventScript_GymStatue:: @ 820E175
	msgbox MauvilleCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_Gym_Text_GymGuideAdvice: @ 820E17F
	.string "잘 있었나!!\n"
	.string "챔피언을 노리는 {PLAYER}!!\p"
	.string "보라시티의 체육관 관장 암페어는\n"
	.string "전기타입 포켓몬 사용자다!\p"
	.string "물타입의 포켓몬으로 대항하면\n"
	.string "찌릿찌릿 마비가 올지도 몰라!\p"
	.string "게다가 스위치로 여는\n"
	.string "묘한 문의 장치를\l"
	.string "체육관에 만들어버렸어!\p"
	.string "그럼 힘내-!$"
	@ げんき しとぉや!!ｎ
	@ チャンピオンを めざす §あ!!ｐ
	@ キンセツシティの ジムリ-ダ- テッセンはｎ
	@ でんきタイプ ポケモンの つかいてだ!ｐ
	@ みずタイプの ポケモンで むかうとｎ
	@ ビリビリ しびれさせられるぞ!ｐ
	@ しかも スイッチで あけたり するｎ
	@ けったいな とびらをｌ
	@ ジムに つくって しまったんだ!ｐ
	@ きばってこ- な!

MauvilleCity_Gym_Text_GymGuidePostVictory: @ 820E283
	.string "이거 깜짝 놀랐구나!\n"
	.string "네 덕분에 문이 열렸어!$"
	@ こりゃ びっくり たまげたッ!ｎ
	@ きみの おかげで とびらは ひらかれた!

MauvilleCity_Gym_Text_KirkIntro: @ 820E2BC
	.string "짜릿한 내 하트로\n"
	.string "네 야망을 산산조각 내주마!$"
	@ しびれる オレの ハ-トがｎ
	@ きみの やぼうを ふんさい するっ!

MauvilleCity_Gym_Text_KirkDefeat: @ 820E2FC
	.string "짜릿한 승부였다...$"
	@ しびれる たたかい だったぜ……

MauvilleCity_Gym_Text_KirkPostBattle: @ 820E336
	.string "포켓몬도 록도 하트가 전부다\n"
	.string "이예-이!$"
	@ ポケモンも ロックも ハ-トが すべてｎ
	@ いぇ-い!

MauvilleCity_Gym_Text_ShawnIntro: @ 820E369
	.string "암페어님 밑에서 수련한 이 몸을\n"
	.string "간단히 쓰러뜨릴 순 없을 거다!$"
	@ テッセンさんに きたえられた この オレがｎ
	@ そう かんたんに まける はずがねえ!

MauvilleCity_Gym_Text_ShawnDefeat: @ 820E3A7
	.string "징 징리징징지잉...$"
	@ キュ キュイィィィン……

MauvilleCity_Gym_Text_ShawnPostBattle: @ 820E3C1
	.string "이 체육관의 관장인 암페어님은\n"
	.string "네 아버지가 태어나기도 전부터\l"
	.string "포켓몬과 배틀해온 강자라고!$"
	@ このジムの リ-ダ- テッセンさんはｎ
	@ きみの おやじが うまれる まえからｌ
	@ ポケモンと たたかってきた つわものさ!

MauvilleCity_Gym_Text_BenIntro: @ 820E443
	.string "이 포켓몬체육관엔\n"
	.string "장치가 있어서 재밌네!$"
	@ この ポケモンジムはｎ
	@ しかけが あって たのしいな!

MauvilleCity_Gym_Text_BenDefeat: @ 820E469
	.string "지는 건 재미없어$"
	@ まけると たのしくないよ

MauvilleCity_Gym_Text_BenPostBattle: @ 820E47E
	.string "암페어님은 스위치를 이용한\n"
	.string "장치를 만드는 게 취미래!$"
	@ テッセンさんは スイッチを つかったｎ
	@ しかけを つくるのが しゅみ なんだって!

MauvilleCity_Gym_Text_VivianIntro: @ 820E4BB
	.string "나의 매력과\n"
	.string "포켓몬의 기술로 짜릿하게 만들어 줄게!$"
	@ あたしの みりょくとｎ
	@ ポケモンの わざで しびれさせちゃう!

MauvilleCity_Gym_Text_VivianDefeat: @ 820E4F4
	.string "네 강함에 짜릿했어!$"
	@ あなたの つよさに しびれたわ!

MauvilleCity_Gym_Text_VivianPostBattle: @ 820E50F
	.string "이곳 보라시티는\n"
	.string "암페어님이 만들었다고 해\p"
	.string "너하고 내가\n"
	.string "태어나기 전부터 트레이너셨으니까\l"
	.string "분명 알고 계신 게 많겠지$"
	@ この キンセツシティはｎ
	@ テッセンさんが つくったって はなしｐ
	@ あなたや わたしがｎ
	@ うまれる まえからの トレ-ナ-だものｌ
	@ きっと いろんな ことを しってるわ

MauvilleCity_Gym_Text_AngeloIntro: @ 820E593
	.string "나 빛나는 거 엄-청 좋아해!$"
	@ ぼく ひかるもの だ-いすき なんだ!

MauvilleCity_Gym_Text_AngeloDefeat: @ 820E5A8
	.string "아아...\n"
	.string "눈이 따끔따끔해$"
	@ ああ…ｎ
	@ めのまえが チカ チカ

MauvilleCity_Gym_Text_AngeloPostBattle: @ 820E5C2
	.string "보라체육관도 암페어님의 이마도\n"
	.string "번쩍번쩍 빛나서 기뻐!$"
	@ キンセツジムも テッセンさんの おデコもｎ
	@ ピカピカ ひかってて うれしいな!

MauvilleCity_Gym_Text_WattsonIntro: @ 820E602
	.string "나는 마을을 개조하는 계획은\n"
	.string "포기했지만\p"
	.string "지금은 이 체육관의 문의 장치를\n"
	.string "만드는 데 몰두하고 있지!\p"
	.string "...어라? 너\n"
	.string "왜 내 앞에 있는 거냐?\p"
	.string "뭐라-! 문의 장치를\n"
	.string "통과해서 왔다는 건가!\p"
	.string "와하하하핫! 이거 재밌구만!\p"
	.string "보라시티 체육관의\n"
	.string "관장 암페어가\l"
	.string "포켓몬 승부로 찌릿찌릿하게 해주마!$"
	@ まちを かいぞうする けいかくはｎ
	@ あきらめた わし じゃがｐ
	@ いまは このジムの とびらの しかけをｎ
	@ つくることに うちこんで おるのじゃ!ｐ
	@ ……あれ? おまえさんｎ
	@ なんで わしの まえに いるんじゃ?ｐ
	@ なに-! とびらの しかけをｎ
	@ くぐりぬけて きたと いうのかっ!ｐ
	@ わっはははは! こりゃ おもしろい!ｐ
	@ ならば この キンセツ ポケモン ジムのｎ
	@ リ-ダ- テッセンがｌ
	@ ポケモンで しびれさせて やるぞい!

MauvilleCity_Gym_Text_WattsonDefeat: @ 820E734
	.string "와하하하핫! 내가 졌다!\n"
	.string "너에게 내가 마비되었군\l"
	.string "이 배지를 가져가도록 하게나!$"
	@ わっはははは! わしの まけじゃ!ｎ
	@ おまえさんには しびれた わいｌ
	@ この バッジ もっていくが いいぞ!

MauvilleCity_Gym_Text_ReceivedDynamoBadge: @ 820E77F
	.string "{PLAYER}{K_EUNNEUN} 암페어에게서\n"
	.string "다이나모배지를 받았다!$"
	@ §あは テッセンからｎ
	@ ダイナモバッジを もらった!

MauvilleCity_Gym_Text_ExplainDynamoBadgeTakeThis: @ 820E7AA
	.string "다이나모배지를 가지고 있으면\n"
	.string "비전기술인 바위깨기를\l"
	.string "사용할 수 있게 된다네!\p"
	.string "게다가 자네의 포켓몬이\n"
	.string "조금 빨라질 거라네!\p"
	.string "음...\n"
	.string "이것도 가져가면 좋을 걸세!$"
	@ ダイナモバッジを もっておるとｎ
	@ ひでんの いわくだきがｌ
	@ つかえるように なるんじゃ!ｐ
	@ それに おまえさんの ポケモンｎ
	@ いっそう すばやく なるぞい!ｐ
	@ うむ……ｎ
	@ これも もっていくが いいぞ!

MauvilleCity_Gym_Text_ExplainShockWave: @ 820E844
	.string "그 기술머신34에는\n"
	.string "전격파가 들어 있지!\p"
	.string "반드시 명중하는\n"
	.string "믿음직한 기술이라고!\p"
	.string "...... ...... ......$"
	@ その わざマシン34 にはｎ
	@ でんげきは が はいっておる!ｐ
	@ かならず めいちゅう するｎ
	@ たのもしい わざ なんじゃよ!ｐ
	@ …… …… ……

MauvilleCity_Gym_Text_RegisteredWattson: @ 820E8B5
	.string "체육관 관장 암페어를\n"
	.string "포켓내비에 등록했다!$"
	@ ジムリ-ダ- テッセンをｎ
	@ ポケナビに とうろく した!

MauvilleCity_Gym_Text_WattsonPostBattle: @ 820E8E3
	.string "장래성이 있는 젊은이의 출현\n"
	.string "정말로 기대가 되는군!$"
	@ みどころの ある わかものの しゅつげんｎ
	@ じつに たのもしい ことじゃ!

MauvilleCity_Gym_Text_WattsonGoForthAndEndeavor: @ 820E925
	.string "와하하하하!\n"
	.string "젊은이여 더욱더 힘내거라!$"
	@ わっはははは!ｎ
	@ わかものよ もっともっと がんばるんじゃ!

MauvilleCity_Gym_Text_GymStatue: @ 820E952
	.string "보라시티 포켓몬체육관$"
	@ キンセツシティ ポケモンジム

MauvilleCity_Gym_Text_GymStatueCertified: @ 820E96C
	.string "보라시티 포켓몬체육관\p"
	.string "암페어 인정 트레이너!\n"
	.string "{PLAYER}$"
	@ キンセツシティ ポケモンジムｐ
	@ テッセン にんてい トレ-ナ-!ｎ
	@ §あ

MauvilleCity_Gym_Text_WattsonPreRematch: @ 820E9A7
	.string "암페어: 어이쿠 찾아온 건가!\n"
	.string "알았네! 나하고 포켓몬\l"
	.string "승부를 하고 싶은 게지!?\p"
	.string "와하하하핫!\p"
	.string "스파크로 파지지직하게\n"
	.string "만들어 줄 테니 각오하게나!$"
	@ テッセン『お-っと あらわれたな!ｎ
	@ わかっとる! わしと ポケモンのｌ
	@ しょうぶを したいんじゃろう!?ｐ
	@ わっはははは!ｐ
	@ ひばな バチバチ いわせて やるからｎ
	@ かくご するんじゃぞ!

MauvilleCity_Gym_Text_WattsonRematchDefeat: @ 820EA42
	.string "후우 배터리가 다 됐구먼...$"
	@ ふぅ バッテリ-ぎれ じゃ……

MauvilleCity_Gym_Text_WattsonPostRematch: @ 820EA5E
	.string "암페어: 나는 재충전 중이라네\p"
	.string "준비를 마치고 나서\n"
	.string "다시 네 도전을 받을 테니\l"
	.string "시간이 지나면 와주게...$"
	@ テッセン『わしゃ じゅうでんの しなおしだｐ
	@ たいせいを たてなおしたらｎ
	@ また きみの ちょうせんを うけるからｌ
	@ しばらく してから きておくれ……

MauvilleCity_Gym_Text_WattsonRematchNeedTwoMons: @ 820EAFD
	.string "암페어: 어이쿠 찾아온 건가!\n"
	.string "알았네! 나하고 포켓몬\l"
	.string "승부를 하고 싶은 게지!?\p"
	.string "와하하하핫!\p"
	.string "...으음? 싸울 수 있는 포켓몬이\n"
	.string "한 마리밖에 없는 모양이구먼\p"
	.string "미안하지만 두 마리 이상\n"
	.string "포켓몬을 데리고 와주게!$"
	@ テッセン『お-っと あらわれたな!ｎ
	@ わかっとる! わしと ポケモンのｌ
	@ しょうぶを したいんじゃろう!?ｐ
	@ わっはははは!ｐ
	@ ……ありゃ? たたかえる ポケモンをｎ
	@ 1ひきしか もっておらん ようだなｐ
	@ すまんが 2ひき いじょうのｎ
	@ ポケモンを もって きておくれ!

