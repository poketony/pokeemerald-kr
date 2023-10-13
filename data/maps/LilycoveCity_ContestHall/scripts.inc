@ VAR_LAST_TALKED would have made all these direct references unnecessary
.set LOCALID_SMART_MC, 4
.set LOCALID_SMART_JUDGE, 5
.set LOCALID_SMART_CONTESTANT_1, 6
.set LOCALID_SMART_CONTESTANT_2, 7
.set LOCALID_SMART_CONTESTANT_3, 8
.set LOCALID_SMART_CONTESTANT_4, 9
.set LOCALID_SMART_AUDIENCE_4, 11
.set LOCALID_SMART_AUDIENCE_2, 12
.set LOCALID_BEAUTY_MC, 13
.set LOCALID_BEAUTY_JUDGE, 14
.set LOCALID_BEAUTY_CONTESTANT_1, 15
.set LOCALID_BEAUTY_CONTESTANT_2, 16
.set LOCALID_BEAUTY_CONTESTANT_3, 17
.set LOCALID_BEAUTY_CONTESTANT_4, 18
.set LOCALID_BEAUTY_AUDIENCE_1, 19
.set LOCALID_BEAUTY_AUDIENCE_3, 20
.set LOCALID_BEAUTY_AUDIENCE_2, 21
.set LOCALID_SMART_AUDIENCE_3, 22
.set LOCALID_CUTE_MC, 23
.set LOCALID_CUTE_JUDGE, 24
.set LOCALID_CUTE_CONTESTANT_1, 25
.set LOCALID_CUTE_CONTESTANT_2, 26
.set LOCALID_CUTE_CONTESTANT_3, 27
.set LOCALID_CUTE_CONTESTANT_4, 28
.set LOCALID_CUTE_AUDIENCE_1, 29
.set LOCALID_CUTE_AUDIENCE_3, 30
.set LOCALID_CUTE_AUDIENCE_2, 31

LilycoveCity_ContestHall_MapScripts:: @ 821B484
	.byte 0

LilycoveCity_ContestHall_EventScript_Boy1:: @ 821B485
	msgbox LilycoveCity_ContestHall_Text_TodayWonSmartnessContest, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Boy2:: @ 821B48E
	msgbox LilycoveCity_ContestHall_Text_EnteredBunchOfContests, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Girl:: @ 821B497
	msgbox LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Sailor:: @ 821B4A0
	msgbox LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_SmartContestMC:: @ 821B4A9
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestJudge:: @ 821B4C0
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant1:: @ 821B4D7
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EnteredWrongContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant2:: @ 821B4EE
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_RaisedMonToBeSmart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant3:: @ 821B505
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant4:: @ 821B51C
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience1:: @ 821B533
	msgbox LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience2:: @ 821B53C
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience3:: @ 821B553
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience4:: @ 821B56A
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_StillLoveSmartnessContests, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestMC:: @ 821B581
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestJudge:: @ 821B598
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant1:: @ 821B5AF
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant2:: @ 821B5C6
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_OverdidGrooming, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant3:: @ 821B5DD
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant4:: @ 821B5F4
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience1:: @ 821B60B
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience2:: @ 821B622
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience3:: @ 821B639
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestMC:: @ 821B650
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_InTheMiddleOfContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestJudge:: @ 821B667
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant1:: @ 821B67E
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyAzurillWasDistracted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant2:: @ 821B695
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_NeverWonBattleButContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant3:: @ 821B6AC
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PetalDanceIsMarvel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant4:: @ 821B6C3
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience1:: @ 821B6DA
	lockall
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_ContestHall_Text_MyChildIsInContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	delay 25
	msgbox LilycoveCity_ContestHall_Text_ComeOnDear, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience2:: @ 821B705
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience3:: @ 821B71C
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyStageSign:: @ 821B733
	msgbox LilycoveCity_ContestHall_Text_BeautyContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_CuteStageSign:: @ 821B73C
	msgbox LilycoveCity_ContestHall_Text_CuteContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartStageSign:: @ 821B745
	msgbox LilycoveCity_ContestHall_Text_SmartContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_Text_TodayWonSmartnessContest: @ 821B74E
	.string "아름다움콘테스트에서\n"
	.string "우승한 이 포켓몬을\l"
	.string "오늘은 슬기로움 콘테스트에서\l"
	.string "우승시켰다고!\p"
	.string "아아 내 재능이 무섭다...$"
	// つくしさ コンテストでｎ
	// ゆうしょうした この ポケモンをｌ
	// きょうは かしこさ コンテストでｌ
	// ゆうしょう させたんだぜ!ｐ
	// ああ じぶんの さいのうが こわい……

LilycoveCity_ContestHall_Text_EnteredBunchOfContests: @ 821B7D7
	.string "몇 번이나 콘테스트에 나가서\n"
	.string "어쩌다 보니 알았는데\p"
	.string "예를 들어 근사함콘테스트에서\n"
	.string "근사한 기술을 쓰면 반응이 좋지만\l"
	.string "슬기로운 어필이나 귀여운 어필은\l"
	.string "왠지 반응이 나쁘단 말이지...$"
	// なんども コンテストに でていてｎ
	// なんとなく わかって きたんだけどｐ
	// たとえば かっこいいコンテストでｎ
	// かっこいいわざを だすと うけるけどｌ
	// かしこいアピ-ルや かわいいアピ-ルはｌ
	// なぜか うけが わるいんだよな……

LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks: @ 821B899
	.string "방금 우승했던 오빠\n"
	.string "굉장히 많은 종류의\l"
	.string "포켓몬스넥을 가지고 있었어!\p"
	.string "저만큼 가지고 있으면\n"
	.string "우승할 수 있는 걸까?$"
	// さっき ゆうしょう した おにいさんｎ
	// すっごい たくさんの しゅるいのｌ
	// ポロックを もってた!ｐ
	// れだけ もってればｎ
	// ゆうしょう できるのかな?

LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous: @ 821B911
	.string "우와 넓네 여기는!\n"
	.string "시골의 콘테스트 회장과는\l"
	.string "긴장감이 다르네!$"
	// か-っ ひろいね ここは!ｎ
	// いなかの コンテスト かいじょう とはｌ
	// きんちょうかんが ちがうね!

LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal: @ 821B977
	.string "사회자: 네에 근사한 포켓몬과\n"
	.string "트레이너 여러부-운!\l"
	.string "열심히 해주세요--오!\l"
	.string "렛츠! 어필!!$"
	// しかい『はあい かしこい ポケモンとｎ
	// そして トレ-ナ-の みなさ-ん!ｌ
	// がんばってくださ--い!ｌ
	// レッツ! アピ-ル!!

LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest: @ 821B9DC
	.string "심사위원: 콘테스트 즐기고 계십니까?\p"
	.string "친구를 3명 데리고 오면\n"
	.string "4명 같이 참가할 수 있답니다!$"
	// しんさいん『コンテスト たのしんでますか?ｐ
	// おともだちを 3にん つれてくればｎ
	// 4にん いっしょに さんか できますよ!

LilycoveCity_ContestHall_Text_EnteredWrongContest: @ 821BA44
	.string "어버버버...\n"
	.string "나갈 콘테스트를 착각했어...\p"
	.string "강인한 포켓몬을\n"
	.string "슬기로움콘테스트에...\p"
	.string "좋 좋앗\n"
	.string "슬기로운 바위깨기 부탁해!$"
	// あわわわ……ｎ
	// でる コンテスト まちがえた……ｐ
	// たくましい ポケモンをｎ
	// かしこさ コンテストに……ｐ
	// よ よしっｎ
	// かしこそうな いわくだき たのむぞ!

LilycoveCity_ContestHall_Text_RaisedMonToBeSmart: @ 821BAD5
	.string "내가 긴 세월 동안\n"
	.string "지식의 모든 걸 걸고서\l"
	.string "슬기롭게 키운 포켓몬!\p"
	.string "젊은 녀석들의 포켓몬 따위에\n"
	.string "그렇게 쉽게 지지는 않겠다!\p"
	.string "할멈 보고 계시오-!?$"
	// わしが ながねんｎ
	// ちしきの すべてを かけてｌ
	// かしこく そだてた ポケモン!ｐ
	// わかい やつらの ポケモン なんぞにｎ
	// そう やすやすと まけたりは せんぞ!ｐ
	// ばあさん みとるか-!?

LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext: @ 821BB84
	.string "좋아! 내 포켓몬이\n"
	.string "이 다음에 슬기로운 기술을 쓰면\l"
	.string "단숨에 회장이 익사이트해진다!$"
	// よし! おれの ポケモンがｎ
	// このつぎに かしこい わざをだせばｌ
	// いっきに かいじょうが エキサイトするぞ!

LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife: @ 821BBDD
	.string "싫다아!\p"
	.string "내 주뱃의\n"
	.string "흡혈이 정말 멋져서\l"
	.string "계속해서 몇 번이고 썼더니\l"
	.string "왠지 다들 실망하고 있어-!$"
	// やだあ!ｐ
	// わたしの ズバットちゃんのｎ
	// きゅうけつが あんまり すてきでｌ
	// つづけて なんども だしてたらｌ
	// なんか がっかり されちゃってる-!

LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa: @ 821BC65
	.string "캬-! 할아범 멋지시오-!$"
	// キャ-! おじいさん すてき-!

LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves: @ 821BC89
	.string "같은 포켓몬을 써도\n"
	.string "트레이너에 따라\l"
	.string "완전 다른 기술로\l"
	.string "어필한단 말이지\p"
	.string "이건 승부하고 마찬가지네!$"
	// おなじ ポケモンを つかっていてもｎ
	// トレ-ナ-に よってｌ
	// ぜんぜん ちがう わざでｌ
	// アピ-ルして くるんだよねｐ
	// それは しょうぶと いっしょだね!

LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers: @ 821BD30
	.string "트레이너보다 포켓몬 쪽이\n"
	.string "머리 좋아 보이네$"
	// トレ-ナ-より ポケモンの ほうがｎ
	// あたま よさそうに みえるなあ

LilycoveCity_ContestHall_Text_StillLoveSmartnessContests: @ 821BD70
	.string "역시 슬기로움콘테스트야!\p"
	.string "지혜로운 초록색이\n"
	.string "음- 멋지네-!$"
	// やっぱり かしこさ コンテストよ!ｐ
	// ちせいてきな みどりいろがｎ
	// う-ん ク-ルだわ-!

LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest: @ 821BDDD
	.string "사회자: 어라? 당신도\n"
	.string "아름다움콘테스트에 나오나요?\l"
	.string "열심히 하세요!$"
	// しかい『あら? あなたもｎ
	// うつくしさ コンテストに でるの?ｌ
	// がんばってね!

LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty: @ 821BE16
	.string "심사위원: 어느 포켓몬도\n"
	.string "실로 아름답군요!\p"
	.string "깜빡하고 점수를 안 매겼네요!$"
	// しんさいん『どの ポケモンもｎ
	// じつに うつくしい ですなぁ!ｐ
	// おもわず さいてんを わすれますよ!

LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty: @ 821BE77
	.string "이렇게 아름다운 포켓몬\n"
	.string "달리 없지\p"
	.string "모두의 눈을 사로잡아 버릴걸!$"
	// こんなに うつくしい ポケモンｎ
	// ほかに いないわよ ねえｐ
	// みんなの めを くぎづけに しちゃうわ!

LilycoveCity_ContestHall_Text_OverdidGrooming: @ 821BEDE
	.string "으아-앙!\p"
	.string "이 콘테스트를 위해서\n"
	.string "정말 열심히 털을 가꾸었는데\p"
	.string "너무 가꾸었는지 내 포켓몬\n"
	.string "부수수해졌어!\p"
	.string "어떡하지...$"
	// うわ-ん!ｐ
	// この コンテストの ためにｎ
	// いっしょけんめい けづくろい したらｐ
	// やりすぎて あたしの ポケモンｎ
	// ボサボサに なっちゃった!ｐ
	// どうしよう……

LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam: @ 821BF6E
	.string "이 엄청 눈부신 오로라빔은\n"
	.string "심사위원도 볼 수 없다!\p"
	.string "...어라?\n"
	.string "그럼 의미가 없나?$"
	// この まぶしすぎる オ-ロラビ-ムにｎ
	// しんさいんも めを あけられない!ｐ
	// ……あれ?ｎ
	// それじゃ いみが ないのか?

LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe: @ 821BFE3
	.string "이 예쁜 포켓몬\n"
	.string "내가 어렸을 때와 닮았어!\p"
	.string "라고 말했더니... 남편이\n"
	.string "마시던 차를 뿜었어\p"
	.string "내가 뭔가 이상한 말을 한 건가?$"
	// この きれいな ポケモンｎ
	// あたしの わかい ころに そっくり!ｐ
	// って いったら…… とうちゃんがｎ
	// のんでた おちゃを ふきだしたよｐ
	// あたし なんか へんなこと いったかね?

LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy: @ 821C07F
	.string "역시 여성으로서는\p"
	.string "아름다움콘테스트에서 이기면\n"
	.string "평소보다 좀 더 기쁘지-!$"
	// やっぱり じょせいと してはｐ
	// うつくしさコンテストで かてるとｎ
	// いつもより ちょっぴり うれしいのよね-!

LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon: @ 821C0D8
	.string "우와하핫!\p"
	.string "예쁜 포켓몬이\n"
	.string "가득 있다...\l"
	.string "이거 화려해서 좋구먼!$"
	// うわっはっは!ｐ
	// べっぴんな ポケモンちゃん がｎ
	// いっぱいだ……ｌ
	// こりゃ はなやかで ええのう!

LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone: @ 821C137
	.string "그저 아름다운 것만으로는\n"
	.string "좀처럼 이길 수 없어!\p"
	.string "내 포켓몬처럼\n"
	.string "손질되어 있고 반들반들해야지!$"
	// ただ うつくしい だけじゃｎ
	// なかなか かてないわよ!ｐ
	// あたしの ポケモンみたいにｎ
	// おていれして ツヤツヤ じゃなきゃ!

LilycoveCity_ContestHall_Text_InTheMiddleOfContest: @ 821C1A4
	.string "사회자: 어머 어머-!\n"
	.string "지금은 콘테스트 중이에요-!\p"
	.string "접수처에서 참가하고 나서\n"
	.string "나와 주세요-! 알겠죠!$"
	// しかい『あら あら-!ｎ
	// いまは コンテスト ちゅう ですよ-!ｐ
	// うけつけで エントリ- してからｎ
	// でて くださ-い! ねっ!

LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals: @ 821C215
	.string "심사위원: 오오\n"
	.string "모두 귀여운 어필이군!\p"
	.string "오옷 얼마나 아름다운\n"
	.string "물놀이 어필인가!$"
	// しんさいん『おおｎ
	// みんな かわいい アピ-ルだなあ!ｐ
	// おおっ なんて かわいいｎ
	// みずあそびの アピ-ルなんだろう!

LilycoveCity_ContestHall_Text_MyAzurillWasDistracted: @ 821C27F
	.string "아아 내 루리리가\n"
	.string "다른 포켓몬에게 시선을 뺏겼어!$"
	// ああ ぼくの ルリリちゃんがｎ
	// ほかの ポケモンに きを とられちゃった!

LilycoveCity_ContestHall_Text_NeverWonBattleButContest: @ 821C2BB
	.string "내 포켓몬은 승부에서\n"
	.string "한 번도 이긴 적이 없지만\l"
	.string "콘테스트는 특기란다!$"
	// わたしの ポケモンって しょうぶだとｎ
	// 1ども かった こと ないけどｌ
	// コンテストは おとくい なのよ!

LilycoveCity_ContestHall_Text_PetalDanceIsMarvel: @ 821C307
	.string "내 포켓몬의 우아한\n"
	.string "꽃잎댄스...\l"
	.string "누구도 방해하게 두진 않아!$"
	// ぼくの ポケモンの かれいなｎ
	// はなびらのまい……ｌ
	// だれにも じゃまは させないぞ!

LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter: @ 821C365
	.string "어느 포켓몬도\n"
	.string "정말로 귀엽네\p"
	.string "하지만 내 포켓몬이\n"
	.string "귀여운 어필을 하면...\p"
	.string "분명 더 귀여울 거야$"
	// どなたの ポケモンもｎ
	// ほんとうに かわいいわねえｐ
	// でも わたしの ポケモンがｎ
	// かわいく アピ-ル すれば……ｐ
	// きっと もっと かわいい はずよ

LilycoveCity_ContestHall_Text_MyChildIsInContest: @ 821C3F4
	.string "우리 애가 콘테스트에 나와 있어요$"
	// うちのこが コンテストに でてるんですよ

LilycoveCity_ContestHall_Text_ComeOnDear: @ 821C411
	.string "자 힘내렴!\n"
	.string "네 포켓몬이 최고란다!$"
	// ほらっ がんばって!ｎ
	// あなたの ポケモンが いちばんよっ!

LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest: @ 821C445
	.string "나는 저 여자아이가\n"
	.string "가장 귀엽다고 생각하네...\p"
	.string "엣? 포켓몬의 모습을\n"
	.string "비교하는 거라고!?$"
	// ワシは あの おんなのこがｎ
	// いちばん かわいいと おもうな……ｐ
	// えっ? ポケモンの みためをｎ
	// くらべてるんか!?

LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn: @ 821C4B1
	.string "아아 보고 나서\n"
	.string "저 포켓몬 가지고 싶어졌어\l"
	.string "잡으러 가야지!$"
	// ああん みてたらｎ
	// あの ポケモン ほしく なっちゃったｌ
	// つかまえに いこっと!

LilycoveCity_ContestHall_Text_BeautyContestStage: @ 821C512
	.string "아름다움콘테스트 스테이지\n"
	.string "뷰티풀 포켓몬에 어질어질!$"
	// うつくしさコンテスト ステ-ジｎ
	// ビュ-ティフル ポケモンに クラクラ!

LilycoveCity_ContestHall_Text_CuteContestStage: @ 821C548
	.string "귀여움콘테스트 스테이지\n"
	.string "큐트한 포켓몬에 싱숭생숭!$"
	// かわいさコンテスト ステ-ジｎ
	// キュ-トな ポケモンに ウキウキ!

LilycoveCity_ContestHall_Text_SmartContestStage: @ 821C57B
	.string "슬기로움콘테스트 스테이지\n"
	.string "인텔리 포켓몬에 녹아녹아!$"
	// かしこさコンテスト ステ-ジｎ
	// インテリ ポケモンに トロトロ!

