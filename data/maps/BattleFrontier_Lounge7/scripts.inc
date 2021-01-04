BattleFrontier_Lounge7_MapScripts:: @ 8265254
	.byte 0

BattleFrontier_Lounge7_EventScript_LeftMoveTutor:: @ 8265255
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_1
	goto_if_set FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor
	msgbox BattleFrontier_Lounge7_Text_LeftTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor:: @ 8265276
	msgbox BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove:: @ 8265284
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_E, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide
	case 7, BattleFrontier_Lounge7_EventScript_Counter
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove:: @ 826532F
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_E, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide
	case 7, BattleFrontier_Lounge7_EventScript_Counter
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_Softboiled:: @ 82653D7
	setvar VAR_0x8008, 16
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_SeismicToss:: @ 82653E2
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_DreamEater:: @ 82653ED
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MegaPunch:: @ 82653F8
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MegaKick:: @ 8265403
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_BodySlam:: @ 826540E
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_RockSlide:: @ 8265419
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Counter:: @ 8265424
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ThunderWave:: @ 826542F
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_SwordsDance:: @ 826543A
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_RightMoveTutor:: @ 8265445
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_2
	goto_if_set FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor
	msgbox BattleFrontier_Lounge7_Text_RightTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor:: @ 8265466
	msgbox BattleFrontier_Lounge7_Text_RightTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove:: @ 8265474
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_E, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind
	case 5, BattleFrontier_Lounge7_EventScript_Endure
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove:: @ 826551F
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_E, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind
	case 5, BattleFrontier_Lounge7_EventScript_Endure
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_DefenseCurl:: @ 82655C7
	setvar VAR_0x8008, 16
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Snore:: @ 82655D2
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MudSlap:: @ 82655DD
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Swift:: @ 82655E8
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_IcyWind:: @ 82655F3
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Endure:: @ 82655FE
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_PsychUp:: @ 8265609
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_IcePunch:: @ 8265614
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ThunderPunch:: @ 826561F
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_FirePunch:: @ 826562A
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect:: @ 8265635
	special CloseBattleFrontierTutorWindow
	special CloseBattlePointsWindow
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge7_EventScript_CancelChooseMon:: @ 8265645
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

@ VAR_0x8008 is the price
@ VAR_TEMP_C is the scroll multichoice ID
@ VAR_TEMP_D is the move selection
@ VAR_TEMP_E is which move tutor was spoken to
BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection:: @ 826564F
	copyvar VAR_0x8004, VAR_TEMP_D
	copyvar VAR_0x8005, VAR_TEMP_E
	special BufferBattleFrontierTutorMoveName
	buffernumberstring 1, VAR_0x8008
	copyvar VAR_0x8004, VAR_TEMP_C
	msgbox BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseNewMove
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	compare VAR_TEMP_1, VAR_0x8008
	goto_if_ge BattleFrontier_Lounge7_EventScript_TeachTutorMove
	msgbox BattleFrontier_Lounge7_Text_HaventGotEnoughPoints, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseNewMove
	end

BattleFrontier_Lounge7_EventScript_TeachTutorMove:: @ 8265696
	msgbox BattleFrontier_Lounge7_Text_TeachMoveToWhichMon, MSGBOX_DEFAULT
	special GetBattleFrontierTutorMoveIndex
	fadescreen FADE_TO_BLACK
	special CloseBattlePointsWindow
	special CloseBattleFrontierTutorWindow
	special ChooseMonForMoveTutor
	waitstate
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_Lounge7_EventScript_CancelChooseMon
	msgbox BattleFrontier_Lounge7_Text_IllTakeBattlePoints, MSGBOX_DEFAULT
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	release
	end

BattleFrontier_Lounge7_EventScript_ChooseNewMove:: @ 82656CA
	compare VAR_TEMP_E, 0
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove
	goto BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_Sailor:: @ 82656DB
	msgbox BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong, MSGBOX_NPC
	end

BattleFrontier_Lounge7_EventScript_Gentleman:: @ 82656E4
	msgbox BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful, MSGBOX_NPC
	end

BattleFrontier_Lounge7_Text_LeftTutorIntro: @ 82656ED
	.string "부하하핫!\p"
	.string "난 이래 봬도 젊었을 때\n"
	.string "꽤 강한 트레이너였다네-\p"
	.string "최강의 누님으로서\n"
	.string "엄청 활약했었지!\p"
	.string "...... ... ...응?\p"
	.string "뭔가 자네 못 믿는 겐가?!\p"
	.string "난 저쪽의 입만 산 할멈과는\n"
	.string "재능이 다르다네!\p"
	.string "그 증거로 자네의 포켓몬에게\n"
	.string "스페셜하고 큐트한 기술을\l"
	.string "가르쳐 주도록 하지!!\p"
	.string "뭐 수업료는 필요하니\n"
	.string "조금 배틀포인트를\l"
	.string "받아가겠지만 말일세!$"
	// ぶはははっ!ｐ
	// あたしゃ こうみえても わかいころはｎ
	// そりゃ- つよい トレ-ナ-でよ-ｐ
	// さいきょうの おとなの おねえさんと してｎ
	// も- バリバリ いわしとったわ!ｐ
	// …… … ……ん?ｐ
	// なんじゃ あんた しんじとらんのかっ!?ｐ
	// あたしゃ むこうの くちだけ ばあさんとはｎ
	// さいのうが ちがうんじゃっ!ｐ
	// しょうこに あんたの ポケモンにｎ
	// すぺしゃる かつ きゅ-とな わざのｌ
	// かずかずを おしえたろうかいなっ!!ｐ
	// まあ じゅぎょうりょう ちゅう ことでｎ
	// ちいと ばかし バトルポイントをｌ
	// いただくがのう!

BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack: @ 82658AB
	.string "부하하핫!\p"
	.string "나의\n"
	.string "스페셜하고 큐트한 기술을\l"
	.string "다시 배우러 온 겐가-?!$"
	// ぶはははっ!ｐ
	// あたしゃのｎ
	// すぺしゃる かつ きゅ-とな わざをｌ
	// おそわりに きたんか-!?

BattleFrontier_Lounge7_Text_TeachWhichMove: @ 82658EF
	.string "그럼그럼- 어느 기술을\n"
	.string "배우게 할 텐가?$"
	// ほれほれ- どのわざを おぼえたいんじゃ?

BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints: @ 8265921
	.string "{STR_VAR_1}{K_IGA} 마음에 든 건가!\n"
	.string "{STR_VAR_2}BP로 괜찮겠나?!$"
	// §い が ええのんか!ｎ
	// §う BP じゃが ええんじゃの!?

BattleFrontier_Lounge7_Text_TeachMoveToWhichMon: @ 826595A
	.string "그럼 기술을 배우게 할\n"
	.string "포켓몬을 선택해 주게!$"
	// ほいじゃあ わざを おぼえさせるｎ
	// ポケモンを きめて おくれ!

BattleFrontier_Lounge7_Text_HaventGotEnoughPoints: @ 8265997
	.string "이런...\n"
	.string "자네 배틀포인트가 부족하구먼!$"
	// なんじゃ……ｎ
	// あんた バトルポイントが たりんぞ!

BattleFrontier_Lounge7_Text_IllTakeBattlePoints: @ 82659C7
	.string "나의 대단함을 알았겠지!!\n"
	.string "그럼 배틀포인트를 받아가겠네!$"
	// あたしゃの すごさが わかったかいっ!!ｎ
	// じゃあ バトルポイントは いただくぞぃ!

BattleFrontier_Lounge7_Text_YouDontWantTo: @ 8265A0E
	.string "뭔가? 관두는 겐가...\p"
	.string "나의 대단함을 알고 싶다면\n"
	.string "언제든지 와도 좋네!$"
	// なんじゃ? やめるんか……ｐ
	// あたしゃの すごさを しりたかったらｎ
	// いつでも くるが ええぞぃ!

BattleFrontier_Lounge7_Text_RightTutorIntro: @ 8265A6C
	.string "이히히힛!\p"
	.string "난 이래 봬도 젊었을 때\n"
	.string "꽤 강한 트레이너였다네-\p"
	.string "무적의 비키니 누님으로서\n"
	.string "인기가 굉장했었지!\p"
	.string "...... ... ...응?\p"
	.string "뭔가 자네 못 믿는 겐가?!\p"
	.string "난 저쪽의 입만 산 할멈과는\n"
	.string "다르게 실력이 있다네!\p"
	.string "그 증거로 자네의 포켓몬에게\n"
	.string "하드하고 프리티한 기술을\l"
	.string "가르쳐 주도록 하지!!\p"
	.string "뭐 수업료는 필요하니\n"
	.string "조금 배틀포인트를\l"
	.string "받아가겠지만 말일세!$"
	// いひひひっ!ｐ
	// あたしゃ こうみえても わかいころはｎ
	// そりゃ- つよい トレ-ナ-でよ-ｐ
	// むてきの ビキニの おねえさんと してｎ
	// も- ブイブイ いわしとったわ!ｐ
	// …… …… ……ん?ｐ
	// なんじゃ あんた しんじとらんのかっ!?ｐ
	// あたしゃ むこうの くちだけ ばあさんとｎ
	// ちがって じつりょくが あるんじゃっ!ｐ
	// しょうこに あんたの ポケモンにｎ
	// は-ど かつ ぷりてぃな わざのｌ
	// かずかずを おしえたろうかいなっ!ｐ
	// まあ じゅぎょうりょう ちゅう ことでｎ
	// ちいと ばかし バトルポイントをｌ
	// いただくがのう!

BattleFrontier_Lounge7_Text_RightTutorWelcomeBack: @ 8265C2C
	.string "이히히힛!\p"
	.string "나의\n"
	.string "하드하고 프리티한 기술을\l"
	.string "다시 배우러 온 겐가-?!$"
	// いひひひっ!ｐ
	// あたしゃのｎ
	// は-ど かつ ぷりてぃな わざをｌ
	// おそわりに きたんか-!?

BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong: @ 8265C6F
	.string "저 두 할멈은 서로에\n"
	.string "대해 나쁘게 말해서\l"
	.string "사이가 안 좋다고 생각하지?\p"
	.string "하지만 정말로 그렇다면 같이\n"
	.string "이런 곳에 있지는 않겠지$"
	// あの ふたりって おたがいのｎ
	// わるぐち いい あってる からｌ
	// なかが わるいとか おもって ないか?ｐ
	// でも ほんとに そう だったら いっしょにｎ
	// こんなところに いたり しないよな

BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful: @ 8265D17
	.string "내가 반바지 꼬마였을 때\n"
	.string "강하고 아름다운 그녀들은\l"
	.string "모든 트레이너의 아이돌이었죠\p"
	.string "지금도 그 기술의 아름다움은\n"
	.string "아주 놀랍게도\l"
	.string "점점 갈고닦아져 빛나고 있답니다\p"
	.string "하지만... 왠지 이런 생각이 듭니다\p"
	.string "시간이란 것은 참으로\n"
	.string "잔혹하군요...$"
	// わたしが まだ たんぱんこぞう だったころｎ
	// つよく うつくしい かのじょ たちはｌ
	// トレ-ナ- みんなの アイドル でしたｐ
	// いまも その わざの キレはｎ
	// おとろえる どころかｌ
	// ますます みがきが かかっている ようですｐ
	// だが…… なぜか こう おもうのです……ｐ
	// じかんと いうものはｎ
	// ざんこくな もの ですね……

BattleFrontier_Lounge7_Text_SoftboiledDesc:: @ 8265E30
	.string "상처 입은 몸을\n"
	.string "체력의\n"
	.string "절반만큼 회복한다$"
	// キズついた からだをｎ
	// たいりょくのｎ
	// はんぶん かいふく

BattleFrontier_Lounge7_Text_SeismicTossDesc:: @ 8265E5B
	.string "인력을 이용해\n"
	.string "레벨만큼의\n"
	.string "데미지를 준다$"
	// いんりょくを りようｎ
	// レベル ぶんのｎ
	// ダメ-ジを あたえる

BattleFrontier_Lounge7_Text_DreamEaterDesc:: @ 8265E8A
	.string "잠자고 있는 적에게\n"
	.string "준 데미지의\n"
	.string "절반만큼 회복한다$"
	// ねている てきにｎ
	// あたえた ダメ-ジのｎ
	// はんぶんを かいふく

BattleFrontier_Lounge7_Text_MegaPunchDesc:: @ 8265EC0
	.string "굉장한 힘을\n"
	.string "담은 펀치로\n"
	.string "적을 공격$"
	// ものすごい ちからをｎ
	// こめた パンチでｎ
	// てきを こうげき

BattleFrontier_Lounge7_Text_MegaKickDesc:: @ 8265EED
	.string "굉장한 힘을\n"
	.string "담은 킥으로\n"
	.string "적을 공격$"
	// ものすごい ちからをｎ
	// こめた キックでｎ
	// てきを こうげき

BattleFrontier_Lounge7_Text_BodySlamDesc:: @ 8265F1C
	.string "몸째로 자빠져서 공격\n"
	.string "적을 마비시킬\n"
	.string "때가 있다$"
	// たおれこみ こうげきｎ
	// てきを まひ させるｎ
	// ことが ある

BattleFrontier_Lounge7_Text_RockSlideDesc:: @ 8265F47
	.string "큰 바위로 공격\n"
	.string "적을 풀죽게 만들\n"
	.string "때가 있다$"
	// いわで こうげきｎ
	// てきを ひるませるｎ
	// ことが ある

BattleFrontier_Lounge7_Text_CounterDesc:: @ 8265F77
	.string "물리공격의\n"
	.string "데미지를\n"
	.string "배로 만들어 돌려준다$"
	// ぶつりこうげきのｎ
	// ダメ-ジをｎ
	// ばいにして かえす

BattleFrontier_Lounge7_Text_ThunderWaveDesc:: @ 8265FAA
	.string "약한 전격을\n"
	.string "던져서 상대를\n"
	.string "마비시킨다$"
	// よわい でんげきをｎ
	// ぶつけて あいてをｎ
	// まひ させる

BattleFrontier_Lounge7_Text_SwordsDanceDesc:: @ 8265FDD
	.string "싸움의 춤으로\n"
	.string "공격을 크게\n"
	.string "올린다$"
	// たたかいの おどりでｎ
	// こうげきを グ-ンとｎ
	// あげる

BattleFrontier_Lounge7_Text_DefenseCurlDesc:: @ 826600A
	.string "몸을 둥글게 해\n"
	.string "방어를 올린다$"
	// からだを まるめてｎ
	// ぼうぎょを あげる

BattleFrontier_Lounge7_Text_SnoreDesc:: @ 826603E
	.string "잠들어 있을 때만\n"
	.string "쓸 수 있는 기술\n"
	.string "코골기로 공격$"
	// ねている とき だけｎ
	// つかえる わざｎ
	// いびきで こうげき

BattleFrontier_Lounge7_Text_MudSlapDesc:: @ 8266070
	.string "진흙을 끼얹어\n"
	.string "명중률을\n"
	.string "내린다$"
	// ドロを かけてｎ
	// めいちゅうりつをｎ
	// さげる

BattleFrontier_Lounge7_Text_SwiftDesc:: @ 82660A6
	.string "누구도 피할 수\n"
	.string "없는 별 모양의\n"
	.string "광선으로 공격$"
	// だれも よけることのｎ
	// できない ほしがたのｎ
	// こうせんで こうげき

BattleFrontier_Lounge7_Text_IcyWindDesc:: @ 82660D0
	.string "굉장한 냉기로\n"
	.string "공격\n"
	.string "스피드를 떨어뜨린다$"
	// すごい れいきでｎ
	// こうげきｎ
	// すばやさを さげる

BattleFrontier_Lounge7_Text_EndureDesc:: @ 82660FF
	.string "그 턴에\n"
	.string "공격을 받아도\n"
	.string "체력이 1 남는다$"
	// そのタ-ンでｎ
	// こうげき されてもｎ
	// たいりょくが1のこる

BattleFrontier_Lounge7_Text_PsychUpDesc:: @ 826612D
	.string "상대의\n"
	.string "보조 효과를\n"
	.string "자신에게 복사한다$"
	// あいてのｎ
	// ほじょこうかをｎ
	// じぶんに コピ-する

BattleFrontier_Lounge7_Text_IcePunchDesc:: @ 826615F
	.string "차가운 펀치로\n"
	.string "적을 얼릴\n"
	.string "때가 있다$"
	// つめたい パンチでｎ
	// てきを こおらせるｎ
	// ことが ある

BattleFrontier_Lounge7_Text_ThunderPunchDesc:: @ 8266185
	.string "전격 펀치로\n"
	.string "적을 마비시킬\n"
	.string "때가 있다$"
	// でんげき パンチでｎ
	// てきを まひさせるｎ
	// ことが ある

BattleFrontier_Lounge7_Text_FirePunchDesc:: @ 82661B5
	.string "불꽃의 펀치로\n"
	.string "적을 화상 입힐\n"
	.string "때가 있다$"
	// ほのおの パンチでｎ
	// てきを やけどさせるｎ
	// ことが ある
