.set LOCALID_WALDAS_DAD, 6

RustboroCity_Flat1_2F_MapScripts:: @ 8215139
	.byte 0

RustboroCity_Flat1_2F_EventScript_WaldasDad:: @ 821513A
	lock
	faceplayer
	specialvar VAR_RESULT, TryBufferWaldaPhrase
	compare VAR_RESULT, FALSE
	goto_if_eq RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase

RustboroCity_Flat1_2F_EventScript_GivePhrase:: @ 8215157
	special DoWaldaNamingScreen
	waitstate
	compare VAR_0x8004, 1
	goto_if_eq RustboroCity_Flat1_2F_EventScript_CancelGivePhrase
	compare VAR_0x8004, 2
	goto_if_eq RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase
	specialvar VAR_RESULT, TryGetWallpaperWithWaldaPhrase
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase
	compare VAR_RESULT, FALSE
	goto_if_eq RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase:: @ 821518D
	msgbox RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase:: @ 82151AD
	msgbox RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase:: @ 82151CD
	msgbox RustboroCity_Flat1_2F_Text_OhIsThatRight, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGivePhrase:: @ 82151D7
	msgbox RustboroCity_Flat1_2F_Text_OhYouDontKnowAny, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase:: @ 82151E1
	msgbox RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase:: @ 82151F8
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry2, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_OhShesLaughing, MSGBOX_DEFAULT
	applymovement LOCALID_WALDAS_DAD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase:: @ 8215221
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda:: @ 8215238
	turnobject LOCALID_WALDAS_DAD, DIR_EAST
	return

RustboroCity_Flat1_2F_EventScript_WaldasMom:: @ 821523D
	msgbox RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard, MSGBOX_NPC
	end

RustboroCity_Flat1_2F_EventScript_PokeDoll:: @ 8215246
	msgbox RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll, MSGBOX_SIGN
	end

RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard: @ 821524F
	.string "정말 큰일이야!\p"
	.string "뭐가 큰일이냐니?\n"
	.string "당연하잖아!?\p"
	.string "매일매일 먹을 반찬거리를\p"
	.string "매일매일 고민해야 되니\n"
	.string "이만저만 큰일이 아니라구!$"
	// もうね たいへん なのよ!ｐ
	// なにが たいへんってｎ
	// そんなの きまってるでしょ!ｐ
	// まいにちの おこんだて よッ!ｐ
	// まいにち まいにち かんがえるのってｎ
	// ほんとうに たいへん なんだからッ!

RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase: @ 82152FA
	.string "여어 어서 와\n"
	.string "벽지 가문의 집에!\p"
	.string "하나 물어보고 싶은 게 있는데\n"
	.string "너 아이를 돌본 적 있어?\p"
	.string "아저씨가 처음으로\n"
	.string "육아를 하고 있는데 말야\p"
	.string "우리 채령이가\n"
	.string "좀처럼 웃질 않아서\p"
	.string "재밌는 말로\n"
	.string "웃길 수 있지 않을까\l"
	.string "생각하고 있었거든\l"
	.string "재밌는 말을 알려주지 않을래?$"
	// やあ いらっしゃいｎ
	// ハコガミけ へ ようこそ!ｐ
	// ちょっと しつもんが あるんだけどｎ
	// きみ こもり したこと ある?ｐ
	// おじさん はじめてｎ
	// いくじ してるんだけどさｐ
	// うちの アヤノｎ
	// なかなか わらって くれないんだよねｐ
	// おもしろ-い ことば でｎ
	// わらって くれないかな-ってｌ
	// おもうんだけどｌ
	// おもしろ-い ことば おしえて くれない?

RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase: @ 8215448
	.string "지금은 “{STR_VAR_1}”{K_I}라는\n"
	.string "말을 들려주고 있는데\p"
	.string "재밌을 것 같은 말\n"
	.string "알아봐준 거니?$"
	// いまは §い ってｎ
	// ことばを つかってるんだけどｐ
	// おもしろそうな ことばｎ
	// みつけて きたの?

RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion: @ 82154AD
	.string "그렇구나 그렇구나\n"
	.string "그럼 바로 알려줘$"
	// そうか そうかｎ
	// じゃあ さっそく おしえて くれよ

RustboroCity_Flat1_2F_Text_OhIsThatRight: @ 82154E7
	.string "그렇구나 그렇구나\n"
	.string "재밌을 것 같을 말을\l"
	.string "알게 된다면 알려줘$"
	// そうか そうかｎ
	// なにか おもしろそうな ことばをｌ
	// みつけたら おしえて くれよ

RustboroCity_Flat1_2F_Text_LetsGiveItATry2: @ 8215535
	.string "과연-\n"
	.string "그럼 시험해 볼게$"
	// なるほど-ｎ
	// じゃあ ためして みようかな

RustboroCity_Flat1_2F_Text_OhShesLaughing: @ 8215565
	.string "{STR_VAR_1}\n"
	.string "{STR_VAR_1}\p"
	.string "웃는다 웃는다!\n"
	.string "왠지 기쁜걸$"
	// §いｎ
	// §いｐ
	// わらってる わらってる!ｎ
	// なんだか うれしいなあ

RustboroCity_Flat1_2F_Text_LetsGiveItATry: @ 82155A4
	.string "과연-\n"
	.string "그럼 시험해 볼게$"
	// なるほど-ｎ
	// じゃあ ためして みようかな

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll: @ 82155D4
	.string "{STR_VAR_1}\n"
	.string "{STR_VAR_1}\p"
	.string "으-음 웃질 않네\n"
	.string "이 애 쿨한가 봐$"
	// §いｎ
	// §いｐ
	// う-ん わらわないなあｎ
	// このこ ク-ル なのかな

RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase: @ 821561E
	.string "좋은 말을 모르는구나-\n"
	.string "그럼 혼자서 생각해야겠네-\p"
	.string "으-음\n"
	.string "“{STR_VAR_1}”{K_I}라면 어떨까\l"
	.string "좋아! 시험해 봐야지$"
	// いい ことば しらないか-ｎ
	// じゃあ じぶんで かんがえるか-ｐ
	// う-んｎ
	// §い とか どうかなｌ
	// よし! ためしてみよう

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2: @ 8215699
	.string "{STR_VAR_1}\n"
	.string "{STR_VAR_1}\p"
	.string "으-음 웃질 않네\n"
	.string "이 애 쿨한가봐$"
	// §いｎ
	// §いｐ
	// う-ん わらわないなあｎ
	// このこ ク-ル なのかな

RustboroCity_Flat1_2F_Text_OhYouDontKnowAny: @ 82156E3
	.string "좋은 말을 모르는구나-\n"
	.string "그럼 지난번의 말로\l"
	.string "웃겨봐야겠네-\p"
	.string "재밌을 거 같은 말을 찾는다면\n"
	.string "아저씨한테 알려주렴$"
	// いい ことば しらないか-ｎ
	// じゃあ まえの ことばでｌ
	// がんばって あやすか-ｐ
	// おもしろそうな ことば みつけたらｎ
	// おじさんに おしえてね

RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper: @ 8215792
	.string "고마워!\p"
	.string "네 덕분에 채령이가\n"
	.string "웃어줬어!\p"
	.string "사실 아저씨\n"
	.string "이래 봬도\p"
	.string "데봉 코포레이션의\n"
	.string "굉장한 연구원이거든\p"
	.string "그렇지- 그럼 답례로\n"
	.string "네가 포켓몬을 맡기는\l"
	.string "박스의 벽지를\l"
	.string "늘려줄게!\p"
	.string "벽지 중에서\n"
	.string "“애호가”를 선택하면\l"
	.string "새로운 벽지가 나올 거야!$"
	// ありがとう!ｐ
	// きみの おかげで アヤノがｎ
	// わらって くれたよ!ｐ
	// じつは おじさんｎ
	// こう みえてもｐ
	// デボンコ-ポレ-ションのｎ
	// すごうで けんきゅういん なんだよｐ
	// そうだな- じゃあ おれいにｎ
	// きみが ポケモンを あずけているｌ
	// ボックスの かべがみをｌ
	// ふやして あげよう!ｐ
	// かべがみの なかからｎ
	// 「だいすき」って いうのを えらぶとｌ
	// あたらしい かべがみが えらべるよ!

RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll: @ 8215923
	.string "포켓몬 봉제인형이다!$"
	// ポケモンの ぬいぐるみ だ!

