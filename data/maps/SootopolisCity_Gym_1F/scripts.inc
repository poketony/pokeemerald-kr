SootopolisCity_Gym_1F_MapScripts:: @ 8224E4C
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SootopolisCity_Gym_1F_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, SootopolisCity_Gym_1F_OnResume
	map_script MAP_SCRIPT_ON_LOAD, SootopolisCity_Gym_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_Gym_1F_OnTransition
	.byte 0

SootopolisCity_Gym_1F_OnTransition: @ 8224E61
	setvar VAR_ICE_STEP_COUNT, 1
	end

SootopolisCity_Gym_1F_OnResume: @ 8224E67
	setstepcallback STEP_CB_SOOTOPOLIS_ICE
	end

SootopolisCity_Gym_1F_OnLoad: @ 8224E6A
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special SetSootopolisGymCrackedIceMetatiles
	end

SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles:: @ 8224E73
	compare VAR_ICE_STEP_COUNT, 8
	goto_if_lt SootopolisCity_Gym_1F_EventScript_StopCheckingStairs  @ All stairs ice
	compare VAR_ICE_STEP_COUNT, 28
	goto_if_lt SootopolisCity_Gym_1F_EventScript_OpenFirstStairs
	compare VAR_ICE_STEP_COUNT, 67
	goto_if_lt SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs
	setmetatile 8, 4, METATILE_SootopolisGym_Stairs, 0
	setmetatile 8, 5, METATILE_SootopolisGym_Stairs, 0
SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs:: @ 8224EA6
	setmetatile 8, 10, METATILE_SootopolisGym_Stairs, 0
	setmetatile 8, 11, METATILE_SootopolisGym_Stairs, 0
SootopolisCity_Gym_1F_EventScript_OpenFirstStairs:: @ 8224EB8
	setmetatile 8, 15, METATILE_SootopolisGym_Stairs, 0
	setmetatile 8, 16, METATILE_SootopolisGym_Stairs, 0
SootopolisCity_Gym_1F_EventScript_StopCheckingStairs:: @ 8224ECA
	return

SootopolisCity_Gym_1F_OnFrame: @ 8224ECB
	map_script_2 VAR_ICE_STEP_COUNT, 8, SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs
	map_script_2 VAR_ICE_STEP_COUNT, 28, SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs
	map_script_2 VAR_ICE_STEP_COUNT, 67, SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs
	map_script_2 VAR_ICE_STEP_COUNT, 0, SootopolisCity_Gym_1F_EventScript_FallThroughIce
	.2byte 0

SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs:: @ 8224EED
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs:: @ 8224F01
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs:: @ 8224F15
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_FallThroughIce:: @ 8224F29
	lockall
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_Gym_1F_Movement_FallThroughIce
	waitmovement 0
	playse SE_FALL
	delay 60
	warphole MAP_SOOTOPOLIS_CITY_GYM_B1F
	waitstate
	end

SootopolisCity_Gym_1F_Movement_FallThroughIce: @ 8224F42
	set_invisible
	step_end

SootopolisCity_Gym_1F_EventScript_Juan:: @ 8224F44
	trainerbattle_single TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanIntro, SootopolisCity_Gym_1F_Text_JuanDefeat, SootopolisCity_Gym_1F_EventScript_JuanDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SootopolisCity_Gym_1F_EventScript_JuanRematch
	goto_if_unset FLAG_RECEIVED_TM03, SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2
	goto_if_unset FLAG_BADGE06_GET, SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge
	msgbox SootopolisCity_Gym_1F_Text_JuanPostBattle, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_JuanDefeated:: @ 8224F82
	message SootopolisCity_Gym_1F_Text_ReceivedRainBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_SOOTOPOLIS_GYM
	setflag FLAG_BADGE08_GET
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_RESIDENTS
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE
	setvar VAR_SOOTOPOLIS_CITY_STATE, 6
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_MAN_1
	setvar VAR_0x8008, 8
	call Common_EventScript_SetGymTrainers
	call SootopolisCity_Gym_1F_EventScript_GiveWaterPulse
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SootopolisCity_Gym_1F_Text_RegisteredJuan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_JUAN_MATCH_CALL
	release
	end

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse:: @ 8224FD4
	giveitem ITEM_TM03
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_BagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM03
	return

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2:: @ 8224FF7
	giveitem ITEM_TM03
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM03
	release
	end

SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge:: @ 822501B
	msgbox SootopolisCity_Gym_1F_Text_GoGetFortreeBadge, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_JuanRematch:: @ 8225025
	trainerbattle_rematch_double TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanPreRematch, SootopolisCity_Gym_1F_Text_JuanRematchDefeat, SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons
	msgbox SootopolisCity_Gym_1F_Text_JuanPostRematch, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_1F_EventScript_GymGuide:: @ 8225040
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SOOTOPOLIS_GYM, SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory
	msgbox SootopolisCity_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory:: @ 8225055
	msgbox SootopolisCity_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_LeftGymStatue:: @ 822505F
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_RightGymStatue:: @ 822506F
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_GymStatueCertified:: @ 822507F
	msgbox SootopolisCity_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_EventScript_GymStatue:: @ 8225089
	msgbox SootopolisCity_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_Text_GymGuideAdvice: @ 8225093
	.string "잘 있었나!!\n"
	.string "챔피언을 노리는 {PLAYER}!!\p"
	.string "루네시티 체육관 관장 아단은\n"
	.string "물타입 포켓몬을 사용한다!!\p"
	.string "그리고 아단이 있는 장소까지\n"
	.string "도달하기 위해서는 얼음 바닥을\l"
	.string "요령껏 건널 필요가 있지...\p"
	.string "미안해! 너에게 알려\n"
	.string "줄 수 있는 건 여기까지야...!\p"
	.string "나머지는 스스로 힘내보라고!$"
	// げんき しとぉや!!ｎ
	// チャンピオンを めざす §あ!!ｐ
	// ルネシティの ジムリ-ダ- アダンはｎ
	// みずタイプ ポケモンを つかいこなす!ｐ
	// そして アダンがいる ところ まではｎ
	// こおりの ゆかが ゆくてを さえぎる……ｐ
	// ごめんな! きみに おしえてｎ
	// あげられるのは ここまで なんだ……!ｐ
	// あとは じぶんで きばってくれッ!

SootopolisCity_Gym_1F_Text_GymGuidePostVictory: @ 82251AF
	.string "호연에서 가장 강하다고 알려져 있는\n"
	.string "아단까지 이겨버렸군!!\p"
	.string "좋아 너의\n"
	.string "트레이너카드를 보도록!\p"
	.string "모든 배지가 모였다면\n"
	.string "이제 드디어\n"
	.string "포켓몬리그에 도전할 수 있다!$"
	// ホウエンで いちばん つよいと いわれるｎ
	// アダンに かったのかあ!!ｐ
	// よし! きみのｎ
	// トレ-ナ-カ-ドを みたまえ!ｐ
	// すべての バッジが そろっているならｎ
	// いよいよ ポケモンリ-グ ちょうせんだ!

SootopolisCity_Gym_1F_Text_JuanIntro: @ 8225268
	.string "유는 알고 있습니까?\p"
	.string "윤진에게 포켓몬을 알려준 건\n"
	.string "무엇을 숨기리 이 아단...\l"
	.string "즉 저라는 것을 말이죠\p"
	.string "한 번 체육관 관장에서 벗어나\n"
	.string "이 체육관을 그에게 맡겼습니다만\l"
	.string "조금 리즌이 있어서...\l"
	.string "즉 이유가 생겨서 말이죠...\l"
	.string "다시 한 번 컴백했습니다\p"
	.string "...으음\n"
	.string "대화는 이 정도로 하고\l"
	.string "슬슬 승부를 시작할까요\p"
	.string "자 마음껏 보시죠\n"
	.string "저와 포켓몬이 만들어내는\l"
	.string "물의 일루전을!$"
	// ユ-は しっていますか?ｐ
	// ミクリに ポケモンを おしえたのはｎ
	// なにをかくそう このアダン……ｌ
	// すなわち わたくし だということをｐ
	// いちどは ジムリ-ダ-から みをひきｎ
	// このジムも かれに まかせて いましたがｌ
	// ちょっとした リ-ズン……ｌ
	// すなわち りゆうが できましてねｌ
	// もういちど カムバック したのですｐ
	// ……おっとｎ
	// おしゃべりは これくらいにしてｌ
	// そろそろ しょうぶを はじめましょうｐ
	// さあ ぞんぶんに ごらんなさいｎ
	// わたしと ポケモンが おりなすｌ
	// みずの イリュ-ジョンを!

@ NOTE: This defeat text actually causes a buffer overflow. It's about 50 bytes too long for
@ the gDisplayedStringBattle buffer that it's put into, and it stomps all over the gBattleTextBuffs
@ after, as well as the otherwise unused array after that. One wonders if that's the reason for
@ the existence of that unused array of ints.
SootopolisCity_Gym_1F_Text_JuanDefeat: @ 8225432
	.string "앗하하하! 유 아 위너!\n"
	.string "즉 저의 패배군요\p"
	.string "유에게서 누구에게도 지지 않는\n"
	.string "재능의 반짝임이 느껴집니다!\p"
	.string "하지만 저나 윤진에 비교하면\n"
	.string "조금 화려함이 부족하군요!\p"
	.string "제 옷이라도\n"
	.string "빌려드릴까요?\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "핫핫핫 조크입니다!\n"
	.string "유에게는 옷 대신에\l"
	.string "이 레인배지를 드리도록 하죠!$"
	// たははは! ユ- ア- ウィナ-!ｎ
	// すなわち わたくしの まけですｐ
	// ユ-には だれにも まけないｎ
	// さいのうの きらめきが かんじられます!ｐ
	// しかし わたくしや ミクリに くらべるとｎ
	// ちょっと はなやかさが たりませんな!ｐ
	// わたしの ふくでもｎ
	// かして あげましょうか?ｐ
	// …… …… ……ｎ
	// …… …… ……ｐ
	// はっはっは ジョ-クですよ!ｎ
	// ユ-には ふくの かわりにｌ
	// この レインバッジを さしあげましょう!

SootopolisCity_Gym_1F_Text_ReceivedRainBadge: @ 8225598
	.string "{PLAYER}{K_EUNNEUN} 아단에게\n"
	.string "레인배지를 받았다!$"
	// §あは アダンからｎ
	// レインバッジを もらった!

SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis: @ 82255BE
	.string "레인배지를 가지고 있으면\n"
	.string "모든 포켓몬이\l"
	.string "유의 말을 잘 따르게 됩니다\p"
	.string "세차게 흐르는 폭포도\n"
	.string "비전기술 폭포오르기를 써서\l"
	.string "올라갈 수 있게 해줍니다\p"
	.string "그리고 저와의 승부를\n"
	.string "잊지 않도록 이걸...$"
	// レインバッジを もっているとｎ
	// すべての ポケモンがｌ
	// ユ-に たいして すなおに なるでしょうｐ
	// はげしく ながれる たきもｎ
	// ひでんわざ たきのぼりを つかってｌ
	// のぼれる ように してくれますｐ
	// それから わたくしとの しょうぶをｎ
	// わすれないように これを……

SootopolisCity_Gym_1F_Text_ExplainWaterPulse: @ 82256C1
	.string "유에게 드린 저의 기술머신의\n"
	.string "내용물은 물의파동\p"
	.string "사용하면 가끔씩 초음파로\n"
	.string "상대를 혼란시키지요!\p"
	.string "...... ...... ......$"
	// ユ-に わたした その わざマシンｎ
	// なかみは みずのはどうｐ
	// つかうと ときおり ちょうおんぱでｎ
	// あいてを こんらん させるのです!ｐ
	// …… …… ……

SootopolisCity_Gym_1F_Text_RegisteredJuan: @ 822574D
	.string "체육관 관장 아단을\n"
	.string "포켓내비에 등록했다!$"
	// ジムリ-ダ- アダンをｎ
	// ポケナビに とうろく した!

SootopolisCity_Gym_1F_Text_JuanPostBattle: @ 8225778
	.string "호연에서 모을 수 있는\n"
	.string "모든 체육관 배지를 손에 넣은\l"
	.string "트레이너가 가야 할 장소\p"
	.string "그것이 바로 포켓몬리그\p"
	.string "포켓몬리그에 가려면\n"
	.string "호연지방 끝에 있는\l"
	.string "그랜드시티라고 불리는 섬으로\l"
	.string "가면 될 겁니다$"
	// ホウエンで あつめられるｎ
	// すべての ジムバッジを てにいれたｌ
	// トレ-ナ-が いくべき ばしょｐ
	// それが ポケモンリ-グｐ
	// ポケモンリ-グに いくならばｎ
	// ホウエンちほうの さいはてｌ
	// サイユウという しまに むかうのです

SootopolisCity_Gym_1F_Text_GoGetFortreeBadge: @ 8225865
	.string "호연에서 모을 수 있는\n"
	.string "체육관 배지는 앞으로 하나\p"
	.string "유가 포켓몬리그에 도전할 거라면\n"
	.string "검방울시티의 포켓몬체육관에서\l"
	.string "남은 배지를 손에 넣어야 할 겁니다$"
	// ホウエンで あつめられるｎ
	// ジムバッジは あと ひとつｐ
	// ユ-が ポケモンリ-グに いどむ つもりならｎ
	// ヒワマキの ポケモンジムでｌ
	// のこりの バッジを てにいれるのです

SootopolisCity_Gym_1F_Text_GymStatue: @ 82258FA
	.string "루네시티 포켓몬체육관$"
	// ルネシティ ポケモンジム

SootopolisCity_Gym_1F_Text_GymStatueCertified: @ 8225916
	.string "루네시티 포켓몬체육관\p"
	.string "체육관 관장 아단\n"
	.string "인정 트레이너!\l"
	.string "{PLAYER}$"
	// ルネシティ ポケモンジムｐ
	// アダン にんてい トレ-ナ-!ｎ§あ

SootopolisCity_Gym_1F_Text_JuanPreRematch: @ 8225950
	.string "아단: 언제나의 사일런스...\n"
	.string "조용함을 되찾은 이 체육관에\p"
	.string "또다시 젊은 타이푼이\n"
	.string "실력을 시험하러 나타났군요!\p"
	.string "물론 좋습니다!\p"
	.string "몇 번이든 유의 상대를\n"
	.string "해드리도록 하죠!$"
	// アダン『いつもの サイレンス……ｎ
	// しずけさを とりもどした このジムにｐ
	// またもや わかき タイフ-ンがｎ
	// うでだめしに あらわれましたね!ｐ
	// いいですとも!ｐ
	// なんどでも ユ-の あいてをｎ
	// して さしあげましょう!

SootopolisCity_Gym_1F_Text_JuanRematchDefeat: @ 8225A2E
	.string "앗하하하! 유 아 위너!\n"
	.string "또 저의 패배군요$"
	// たははは! ユ- ア- ウィナ-!ｎ
	// またしても わたくしの まけです

SootopolisCity_Gym_1F_Text_JuanPostRematch: @ 8225A67
	.string "아단: 저의 제자가 되어달라고 해도\n"
	.string "분명 유는 거절할 테죠\p"
	.string "적어도 제가 입고 있는 코트를\n"
	.string "선물하고 싶지만...\l"
	.string "아마 유는 받지 않을 겁니다\p"
	.string "그것이 젠틀맨이니까요\n"
	.string "홋홋홋호!$"
	// アダン『わたしの でしに なれと いってもｎ
	// きっと ユ-は ことわる でしょうねｐ
	// せめて わたしが きている コ-トをｎ
	// プレゼント したいの ですが……ｌ
	// おそらく ユ-は うけとらない でしょうｐ
	// それが ジェントルマン というものですｎ
	// ほっほっほっほ!

SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons: @ 8225B48
	.string "아단: 언제나의 사일런스...\n"
	.string "조용함을 되찾은 이 체육관에\p"
	.string "또다시 젊은 타이푼이\n"
	.string "실력을 시험하러 나타났군요!\p"
	.string "물론 좋습니다!\n"
	.string "몇 번이든 유의 상대를...\p"
	.string "...아하?\n"
	.string "유는 싸울 수 있는 포켓몬을\l"
	.string "한 마리만 데리고 있군요\p"
	.string "부디 두 마리 이상\n"
	.string "포켓몬을 데려오세요 플리즈$"
	// アダン『いつもの サイレンス……ｎ
	// しずけさを とりもどした このジムにｐ
	// またもや わかき タイフ-ンがｎ
	// うでだめしに あらわれましたね!ｐ
	// いいですとも!ｎ
	// なんどでも ユ-の あいてを……ｐ
	// ……アハン?ｎ
	// ユ-は たたかえる ポケモンをｌ
	// 1ひきしか もっていない ようですねｐ
	// ねがわくば 2ひき いじょうのｎ
	// ポケモンを もってきて プリ-ズ

