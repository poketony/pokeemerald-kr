.set LOCALID_GRUNT, 3
.set LOCALID_DEVON_EMPLOYEE, 4

PetalburgWoods_MapScripts:: @ 822DFD6
	.byte 0

PetalburgWoods_EventScript_DevonResearcherLeft:: @ 822DFD7
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, 0
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherLeft
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaApproachPlayer
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitLeft
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherRight:: @ 822E079
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, 0
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherRight
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitRight
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherIntro:: @ 822E124
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherLookAround
	waitmovement 0
	msgbox PetalburgWoods_Text_NotAOneToBeFound, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_DevonResearcherPostBattle:: @ 822E138
	msgbox PetalburgWoods_Text_YouveGotSomeNerve, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaRunAway
	waitmovement 0
	removeobject LOCALID_GRUNT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox PetalburgWoods_Text_ThatWasAwfullyClose, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL
	compare VAR_RESULT, FALSE
	goto_if_eq PetalburgWoods_EventScript_BagFull
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_BagFull:: @ 822E17D
	msgbox PetalburgWoods_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_DevonResearcherFinish:: @ 822E18B
	msgbox PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro, MSGBOX_DEFAULT
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherStartExit
	waitmovement 0
	msgbox PetalburgWoods_Text_ICantBeWastingTime, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_RemoveDevonResearcher:: @ 822E1A7
	removeobject LOCALID_DEVON_EMPLOYEE
	setvar VAR_PETALBURG_WOODS_STATE, 1
	releaseall
	end

PetalburgWoods_Movement_DevonResearcherLookAround: @ 822E1B1
	face_up
	delay_16
	delay_4
	face_right
	delay_16
	delay_8
	face_left
	delay_16
	delay_8
	face_down
	delay_16
	face_right
	delay_16
	delay_8
	face_up
	delay_16
	step_end

PetalburgWoods_Movement_DevonResearcherExitLeft: @ 822E1C2
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft: @ 822E1CB
	delay_16
	face_player
	walk_down
	walk_down
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerRight: @ 822E1D0
	delay_16
	face_player
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_right
	step_end

PetalburgWoods_Movement_DevonResearcherExitRight: @ 822E1D7
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_WatchResearcherLeave: @ 822E1E0
	delay_16
	delay_16
	walk_in_place_fastest_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft: @ 822E1E4
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_in_place_fastest_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight: @ 822E1EA
	walk_fast_down
	walk_fast_right
	walk_in_place_fastest_up
	step_end

PetalburgWoods_Movement_DevonResearcherStartExit: @ 822E1EE
	walk_in_place_fastest_down
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_up
	step_end

PetalburgWoods_Movement_AquaApproachResearcherLeft: @ 822E1F6
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaBackOff: @ 822E1F9
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

PetalburgWoods_Movement_AquaRunAway: @ 822E1FD
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachResearcherRight: @ 822E205
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaEntrance: @ 822E209
	walk_down
	walk_down
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachPlayer: @ 822E20E
	walk_down
	step_end

PetalburgWoods_EventScript_Boy1:: @ 822E210
	msgbox PetalburgWoods_Text_StayOutOfTallGrass, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Boy2:: @ 822E219
	msgbox PetalburgWoods_Text_HiddenItemsExplanation, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Girl:: @ 822E222
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MIRACLE_SEED, PetalburgWoods_EventScript_ExplainMiracleSeed
	msgbox PetalburgWoods_Text_TryUsingThisItem, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MIRACLE_SEED
	release
	end

PetalburgWoods_EventScript_ExplainMiracleSeed:: @ 822E251
	msgbox PetalburgWoods_Text_MiracleSeedExplanation, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_Sign1:: @ 822E25B
	msgbox PetalburgWoods_Text_TrainerTipsExperience, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Sign2:: @ 822E264
	msgbox PetalburgWoods_Text_TrainerTipsPP, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Lyle:: @ 822E26D
	trainerbattle_single TRAINER_LYLE, PetalburgWoods_Text_GoBugPokemonTeam, PetalburgWoods_Text_ICouldntWin
	msgbox PetalburgWoods_Text_ImOutOfPokeBalls, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_EventScript_James:: @ 822E284
	trainerbattle_single TRAINER_JAMES_1, PetalburgWoods_Text_InstantlyPopularWithBugPokemon, PetalburgWoods_Text_CantBePopularIfILose, PetalburgWoods_EventScript_TryRegisterJames
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq PetalburgWoods_EventScript_JamesRematch
	setvar VAR_0x8004, TRAINER_JAMES_1
	specialvar VAR_RESULT, IsTrainerRegistered
	compare VAR_RESULT, FALSE
	goto_if_eq PetalburgWoods_EventScript_TryRegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_TryRegisterJames:: @ 822E2C5
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames
	release
	end

PetalburgWoods_EventScript_RegisterJames:: @ 822E2D6
	msgbox PetalburgWoods_Text_IWantRematch1, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_TryRegisterJames2:: @ 822E2EF
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_RegisterJames2:: @ 822E302
	msgbox PetalburgWoods_Text_IWantRematch2, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_JamesRematch:: @ 822E31B
	trainerbattle_rematch TRAINER_JAMES_1, PetalburgWoods_Text_MyPokemonHaveGrown, PetalburgWoods_Text_CantBePopularIfLose
	msgbox PetalburgWoods_Text_IveBeenTrainingHard, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_Text_NotAOneToBeFound: @ 822E332
	.string "으-음...\n"
	.string "없네...$"
	@ う-んｎ
	@ いないなあ……

PetalburgWoods_Text_HaveYouSeenShroomish: @ 822E34F
	.string "저기 자네 이 근처에서\n"
	.string "버섯꼬라는 포켓몬 본 적 없나?\p"
	.string "내가 그 포켓몬을 정말 좋아하거든$"
	@ ねえ きみきみ このあたりでｎ
	@ キノココって ポケモン みなかった?ｐ
	@ おじさん あの ポケモン すき なのよね

PetalburgWoods_Text_IWasGoingToAmbushYou: @ 822E3AA
	.string "계속 숨어서 기다리고 있었는데\n"
	.string "언제까지 등화숲에서 어슬렁어슬렁...\p"
	.string "기다리다 지쳐서 그냥 내가 왔다!$"
	@ まちぶせ していたのにｎ
	@ いつまでも トウカのもりで うろうろと……ｐ
	@ まちくたびれたから きてやったぞ!

PetalburgWoods_Text_HandOverThosePapers: @ 822E428
	.string "야! 데봉의 연구원!\p"
	.string "그 서류 일로 내놔!$"
	@ やい! デボンの けんきゅういん!ｐ
	@ その しょるいを こっちに よこしやがれ!

PetalburgWoods_Text_YouHaveToHelpMe: @ 822E457
	.string "히엑-!\p"
	.string "자네 포켓몬 트레이너지?\n"
	.string "아저씨 좀 살려줘$"
	@ ひや-!ｐ
	@ きみ ポケモントレ-ナ- だよねｎ
	@ おじさんを たすけてよぉ

PetalburgWoods_Text_NoOneCrossesTeamAqua: @ 822E4A5
	.string "...응? 뭐야 넌?\n"
	.string "그 녀석을 도와주려고?\p"
	.string "아쿠아단을 방해하는 녀석은\n"
	.string "아이라도 봐주지 않는다!\l"
	.string "승부로 덤벼봐!$"
	@ ……ん? なんだ おまえ?ｎ
	@ そいつを かばおう ってのか?ｐ
	@ アクアだんの じゃまを する やつはｎ
	@ こどもでも ようしゃ しねえ!ｌ
	@ しょうぶ しやがれ!

PetalburgWoods_Text_YoureKiddingMe: @ 822E542
	.string "...가 강하잖아-!$"
	@ ……つ つよい じゃね-か!

PetalburgWoods_Text_YouveGotSomeNerve: @ 822E563
	.string "으으윽... 아쿠아단을\n"
	.string "방해하다니 이 건방진 녀석!\l"
	.string "다시 한 번 승부하자!\p"
	.string "...라고 하고 싶지만\n"
	.string "더 이상 지닌 포켓몬이 없어\p"
	.string "게다가 금탄도시에도 아쿠아단이\n"
	.string "노리고 있는 게 있거든!\p"
	.string "오늘은 이 정도로 봐준다!$"
	@ むむむ…… アクアだんのｎ
	@ じゃまを するとは なんて やつ!ｌ
	@ もう いっかい しょうぶ しろ!ｐ
	@ ……と いいたい ところ だがｎ
	@ もう てもちの ポケモンは いないｐ
	@ それに カナズミ シティにも アクアだんがｎ
	@ ねらっている ものが あるからな!ｐ
	@ きょうは これぐらいに しといてやらぁ!

PetalburgWoods_Text_ThatWasAwfullyClose: @ 822E63D
	.string "...휴우\n"
	.string "큰일 날 뻔했네!\p"
	.string "자네 덕분에 중요한 서류를\n"
	.string "빼앗기지 않을 수 있었어!\p"
	.string "...그래! 감사의 표시로\n"
	.string "수퍼볼을 줄게!$"
	@ ……ふぅｎ
	@ あぶない ところ だった!ｐ
	@ きみの おかげで だいじな しょるいをｎ
	@ うばわれないで すんだよ!ｐ
	@ ……そうだ! おれいにｎ
	@ ス-パ-ボ-ルを あげちゃおう!

PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro: @ 822E6C7
	.string "...그러고 보니 아까 아쿠아단이\n"
	.string "“금탄도시에도 노리고 있는 게 있다”\l"	
	.string "라고 말했었지...?$"
	@ ……そういえば さっき アクアだんはｎ
	@ 「カナズミにも ねらっている ものがある」ｌ
	@ とか いってたよね……?

PetalburgWoods_Text_ICantBeWastingTime: @ 822E712
	.string "큰일 났다!!\n"
	.string "이러고 있을 때가 아냐!$"
	@ たいへんだ!!ｎ
	@ こうしちゃ いられない!

PetalburgWoods_Text_YoureLoadedWithItems: @ 822E741
	.string "가방이 가득 차서\n"
	.string "수퍼볼은 줄 수 없겠네$"
	@ どうぐ いっぱいでｎ
	@ ス-パ-ボ-ル あげられないね

PetalburgWoods_Text_GoBugPokemonTeam: @ 822E77D
	.string "포켓몬을 잔뜩 잡았어!\p"
	.string "자 가랏!\n"
	.string "나의 벌레포켓몬 팀!$"
	@ ポケモン いっぱい つかまえた!ｐ
	@ そら いけ!ｎ
	@ ぼくの むしポケモン チ-ム!

PetalburgWoods_Text_ICouldntWin: @ 822E7C1
	.string "이렇게 포켓몬이 많은데\n"
	.string "이길 수 없다니...$"
	@ こんなに ポケモン いるのにｎ
	@ かてなかったのか……

PetalburgWoods_Text_ImOutOfPokeBalls: @ 822E7EF
	.string "잔뜩 포켓몬을 잡았더니\n"
	.string "몬스터볼이 부족해졌어$"
	@ たくさん ポケモン つかまえたらｎ
	@ モンスタ-ボ-ル なくなっちゃったよ

PetalburgWoods_Text_InstantlyPopularWithBugPokemon: @ 822E827
	.string "벌레포켓몬을 학교에 가지고 가면\n"
	.string "그만큼 인기쟁이가 되겠지!?$"
	@ むしポケモンを がっこうに もっていくとｎ
	@ それだけで にんきもの だろ!?

PetalburgWoods_Text_CantBePopularIfILose: @ 822E86B
	.string "져버리면 인기쟁이가 될 수 없어$"
	@ まけると にんきものに なれないや

PetalburgWoods_Text_PeopleRespectYou: @ 822E889
	.string "커다란 벌레포켓몬을 가지고 있으면\n"
	.string "그만큼 존경받지 않을까!?$"
	@ でかい むしポケモン もってるとｎ
	@ それだけで そんけ- されるだろ!?

PetalburgWoods_Text_IWantRematch1: @ 822E8C3
	.string "벌레포켓몬이 자라면 다시 승부하자!\n"
	.string "포켓내비에 등록할게!$"
	@ むしポケモン そだったら また しょうぶだ!ｎ
	@ ポケナビに とうろく するぞ

PetalburgWoods_Text_IWantRematch2: @ 822E914
	.string "벌레포켓몬이 자라면 다시 승부하자!\n"
	.string "포켓내비에 등록할게!$"
	@ むしポケモン そだったら また しょうぶだ!ｎ
	@ ポケナビに とうろく するぞ

PetalburgWoods_Text_MyPokemonHaveGrown: @ 822E966
	.string "내 벌레포켓몬 많이 컸어!\n"
	.string "이걸로 또 인기쟁이가 될 거야!$"
	@ ぼくの むしポケモン そだったぞ!ｎ
	@ これで また にんきもの だぜ!

PetalburgWoods_Text_CantBePopularIfLose: @ 822E998
	.string "져버리면 인기쟁이가 될 수 없어$"
	@ まけると にんきものに なれないや

PetalburgWoods_Text_IveBeenTrainingHard: @ 822E9B6
	.string "강한 포켓몬을 가지고 있으면\n"
	.string "인기쟁이가 될 수 있겠지?\l"
	.string "그래서 열심히 키우고 있는 거야!$"
	@ つよい ポケモン もってるとｎ
	@ にんきものに なれるだろ?ｌ
	@ だから がんばって そだててるのさ!

PetalburgWoods_Text_StayOutOfTallGrass: @ 822EA0C
	.string "여어! 네 포켓몬 괜찮아?\p"
	.string "지닌 포켓몬이 약해져서\n"
	.string "배틀시키고 싶지 않을 때는 되도록이면\l"
	.string "풀숲을 피해서 움직이는 게 좋을 거야!$"
	@ よお! おまえの ポケモン げんき?ｐ
	@ てもちの ポケモンが よわっていてｎ
	@ たたかわせたく ないときは なるべくｌ
	@ くさむらを よけて あるくと いいよ!

PetalburgWoods_Text_HiddenItemsExplanation: @ 822EA8B
	.string "보이진 않아도\n"
	.string "도구가 떨어져 있을 때가 있어서\l"
	.string "발밑을 살펴보고 있어!$"
	@ みえて いなくてもｎ
	@ どうぐが おちてることが あるからｌ
	@ あしもとを しらべて いるんだ!

PetalburgWoods_Text_TryUsingThisItem: @ 822EAFE
	.string "그건 금탄도시의 체육관 배지!\p"
	.string "너 트레이너구나\n"
	.string "이 도구 한번 써보는 건 어때?$"
	@ それって カナズミの ジムバッジ!ｐ
	@ あなた トレ-ナ-なのねｎ
	@ この どうぐ つかってみたら どうかしら?

PetalburgWoods_Text_MiracleSeedExplanation: @ 822EB63
	.string "기적의씨를\n"
	.string "포켓몬에게 지니게 하면 풀타입\l"
	.string "기술의 위력이 올라가\p"
	.string "기적의씨 외에도\n"
	.string "포켓몬에게 지니게 하면 편리한\l"
	.string "도구가 있다고 하더라고$"
	@ きせきのタネをｎ
	@ ポケモンに もたせてあげると くさタイプのｌ
	@ わざの いりょくが あがるのよｐ
	@ きせきのタネの ほかにもｎ
	@ ポケモンに もたせると べんりなｌ
	@ どうぐが あるらしいわね

PetalburgWoods_Text_TrainerTipsExperience: @ 822EC10
	.string "정보 나눔 게시판!!\p"
	.string "승부할 때\n"
	.string "한 번이라도 배틀에 나온 포켓몬은\l"
	.string "경험치를 받을 수 있습니다!\p"
	.string "약한 포켓몬을 리스트의 왼쪽에 놓고\n"
	.string "승부할 때 바로 교체!\l"
	.string "이러면 약한 포켓몬도 키울 수 있어요!$"
	@ おとくな けいじばん!!ｐ
	@ しょうぶの ときｎ
	@ いちど でも かおをだした ポケモンはｌ
	@ けいけんちが もらえます!ｐ
	@ よわい ポケモンを リストの ひだりにしてｎ
	@ しょうぶのとき すぐに こうたい!ｌ
	@ これで よわい ポケモンも そだちます!

PetalburgWoods_Text_TrainerTipsPP: @ 822ED07
	.string "정보 나눔 게시판!!\p"
	.string "포켓몬에겐 히트포인트 말고도\n"
	.string "기술을 사용하기 위한 힘의 근원인\l"
	.string "파워포인트라는 것이 있습니다\p"
	.string "기술의 파워포인트를 다 썼을 때도\n"
	.string "포켓몬센터로 갑시다!$"
	@ おとくな けいじばん!!ｐ
	@ ポケモンには ヒットポイントの ほかにｎ
	@ わざを くりだす ちからの もとｌ
	@ パワ-ポイント というものが ありますｐ
	@ わざの パワ-ポイントが なくなったときもｎ
	@ ポケモンセンタ-に いきましょう!

