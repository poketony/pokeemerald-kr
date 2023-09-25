.set LOCALID_WALLACE, 1

CaveOfOrigin_B1F_MapScripts:: @ 82357A8
	.byte 0

CaveOfOrigin_B1F_EventScript_Wallace:: @ 82357A9
	lock
	faceplayer
	msgbox CaveOfOrigin_B1F_Text_WallaceStory, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 60
	playse SE_PIN
	applymovement LOCALID_WALLACE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLACE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
	message CaveOfOrigin_B1F_Text_WhereIsRayquaza
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_WheresRayquaza:: @ 82357F0
	multichoice 0, 0, MULTI_WHERES_RAYQUAZA, 0
	switch VAR_RESULT
	case 0, CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin
	case 1, CaveOfOrigin_B1F_EventScript_AtMtPyre
	case 2, CaveOfOrigin_B1F_EventScript_AtSkyPillar
	case 3, CaveOfOrigin_B1F_EventScript_DontRemember
	goto CaveOfOrigin_B1F_EventScript_DontRemember
	end

CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin:: @ 823582C
	message CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtMtPyre:: @ 8235837
	message CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_DontRemember:: @ 8235842
	message CaveOfOrigin_B1F_Text_CantYouRememberSomehow
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtSkyPillar:: @ 823584D
	msgbox CaveOfOrigin_B1F_Text_WellHeadToSkyPillar, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreenspeed FADE_TO_BLACK, 4
	setflag FLAG_WALLACE_GOES_TO_SKY_PILLAR
	setvar VAR_SOOTOPOLIS_CITY_STATE, 3
	removeobject LOCALID_WALLACE
	clearflag FLAG_HIDE_SKY_PILLAR_WALLACE
	fadescreen FADE_FROM_BLACK
	release
	end

CaveOfOrigin_B1F_Text_WallaceStory: @ 823586E
	.string "그렇군 네가 {PLAYER}...\n"
	.string "네 활약은 들었어\p"
	.string "내 이름은 윤진\n"
	.string "루네시티의 체육관 관장이었는데\l"
	.string "조금 사정이 있어서\p"
	.string "지금은 스승이신 아단님께\n"
	.string "체육관 일을 맡겼지\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "지금 이 마을에서 날뛰고 있는\n"
	.string "그란돈과 가이오가는\l"
	.string "초 고대포켓몬이라고 전해져\p"
	.string "하지만 초 고대포켓몬은\n"
	.string "저 2마리만이 아니야...\l"
	.string "어딘가에 1마리 더\p"
	.string "그래... 레쿠쟈라고 하는\n"
	.string "초 고대포켓몬이 있어\p"
	.string "먼 옛날에\n"
	.string "저 2마리의 싸움을 잠재운 것도\l"
	.string "레쿠쟈라고 전해지고 있지\p"
	.string "하지만 레쿠쟈가 어디에 있는지는\n"
	.string "나도 모르겠군...$"
	// そうか きみが {PLAYER}{KUN}……ｎ
	// きみの かつやくは きいているよｐ
	// わたしの なまえは ミクリｎ
	// ルネの ジムリ-ダ-を していたけれどｌ
	// ちょっと わけが あってねｐ
	// いまは ししょうの アダンさんにｎ
	// ジムのことは おまかせして いるのさｐ
	// …… …… ……ｎ
	// …… …… ……ｐ
	// いま このまちで あばれているｎ
	// グラ-ドンと カイオ-ガはｌ
	// ちょうこだい ポケモンと いわれているｐ
	// けれど ちょうこだい ポケモンはｎ
	// あの2ひき だけじゃ なかった……ｌ
	// どこかに もう1ひきｐ
	// そう…… レックウザと よばれるｎ
	// ちょうこだい ポケモンが いるんだよｐ
	// とおい むかしにｎ
	// あの2ひきの たたかいを しずめたのもｌ
	// レックウザ だと いわれているｐ
	// だが レックウザが どこに いるかはｎ
	// わたしにも わからない……

CaveOfOrigin_B1F_Text_WhereIsRayquaza: @ 8235ACE
	.string "윤진: {PLAYER} 혹시\n"
	.string "너는 레쿠쟈가 어디에 있는지\l"
	.string "알고 있니?\p"
	.string "괜찮다면 알려주지 않겠어...$"
	// ミクリ『{PLAYER}{KUN}ひょっとしてｎ
	// きみは レックウザが どこに いるかｌ
	// しっているのかい?ｐ
	// よかったら おしえて くれないか……

CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin: @ 8235B23
	.string "윤진: 각성의 사당...\p"
	.string "이라니 그건 바로 이곳이잖아\n"
	.string "부탁이야 제대로 해줘!\p"
	.string "레쿠쟈가 어디에 있는지\n"
	.string "다시 한 번 생각해줘...$"
	// ミクリ『めざめのほこらか……ｐ
	// って それは ここのこと じゃないかｎ
	// たのむよ しっかり してくれ!ｐ
	// レックウザが どこに いるかｎ
	// もういちど かんがえて みてくれ……

CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat: @ 8235BBF
	.string "윤진: 송화산인가...\p"
	.string "하지만 이전에 할머니께\n"
	.string "갔을 때는 아무 말도 안 하셨어\p"
	.string "그분이 내게 거짓말을 하셨다고\n"
	.string "생각할 수도 없고...\p"
	.string "{PLAYER} 다시 한 번\n"
	.string "잘 생각해줘...$"
	// ミクリ『おくりびやまか……ｐ
	// しかし このまえ オババさまにｎ
	// あったときは なにも いってなかったｐ
	// あのひとが わたしにｎ
	// うそを つくとも おもえないし……ｐ
	// {PLAYER}{KUN} もういちどｎ
	// よく かんがえて くれないか……

CaveOfOrigin_B1F_Text_CantYouRememberSomehow: @ 8235C99
	.string "윤진: 앗 기억나지 않는다고!?\n"
	.string "으-음 그건 곤란한데...\p"
	.string "어떻게든\n"
	.string "떠올려 줄 수 없을까...$"
	// ミクリ『えっ おぼえてない って!?ｎ
	// う-ん それは こまったな……ｐ
	// なんとかｎ
	// おもいだして もらえない だろうか……

CaveOfOrigin_B1F_Text_WellHeadToSkyPillar: @ 8235CEE
	.string "윤진: 하늘기둥...?\p"
	.string "그렇군! 하늘기둥이었어!\p"
	.string "좋아 {PLAYER}\n"
	.string "이렇게 있을 수는 없지\l"
	.string "지금 바로 하늘기둥으로 가자!$"
	// ミクリ『そらのはしら……?ｐ
	// そうか! そらのはしら だったか!ｐ
	// よし {PLAYER}{KUN}ｎ
	// こうしては いられないｌ
	// いますぐ そらのはしらへ いくぞ!

