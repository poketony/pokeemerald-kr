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
	.string "음...\n"
	.string "안 보이네...$"

PetalburgWoods_Text_HaveYouSeenShroomish: @ 822E34F
	.string "어이 자네 이 근처에서\n"
	.string "버섯꼬라는 포켓몬 본 적 없나?\p"
	.string "내가 그 포켓몬을 정말 좋아하거든$"

PetalburgWoods_Text_IWasGoingToAmbushYou: @ 822E3AA
	.string "계속 기다리고 있었어\n"
	.string "등화숲에서\l"
	.string "어슬렁어슬렁하면서...\p"
	.string "그러다가 지쳐서 그냥 내가 왔다!$"

PetalburgWoods_Text_HandOverThosePapers: @ 822E428
	.string "어이! 데봉의 연구원!\p"
	.string "그 서류, 일로 내놔!$"

PetalburgWoods_Text_YouHaveToHelpMe: @ 822E457
	.string "으에-!\p"
	.string "자네 포켓몬 트레이너지?\n"
	.string "나 좀 살려줘$"

PetalburgWoods_Text_NoOneCrossesTeamAqua: @ 822E4A5
	.string "...응? 뭐야 넌?\n"
	.string "그 녀석을 도와주려고?\p"
	.string "아쿠아단을 방해하는 녀석은\n"
	.string "설령 아이라도 봐주지 않는다!\l"
	.string "한번 덤벼봐!$"

PetalburgWoods_Text_YoureKiddingMe: @ 822E542
	.string "...가, 강하잖아!$"

PetalburgWoods_Text_YouveGotSomeNerve: @ 822E563
	.string "에이...아쿠아단을\n"
	.string "방해하다니 이 건방진 녀석!\l"
	.string "다시 한 번 더 덤벼!\p"
	.string "...라고 하고 싶지만\n"
	.string "더 이상 지닌 포켓몬이 없어...\p"
	.string "게다가 금탄도시에도 아쿠아단이\n"
	.string "노리고 있는 게 있으니까!\p"
	.string "오늘은 이 정도로 봐준다!$"

PetalburgWoods_Text_ThatWasAwfullyClose: @ 822E63D
	.string "...휴우\n"
	.string "위험했다!\p"
	.string "자네 덕분에 중요한 서류를\n"
	.string "지킬 수 있었어!\p"
	.string "...아 그래! 감사의 표시로\n"
	.string "이 수퍼볼을 주도록 하지!$"

PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro: @ 822E6C7
	.string "...아!? 그러고 보니\n"
	.string "아까 아쿠아단이\p"
	.string "“금탄도시에도\n"
    .string "노리고 있는 게 있다”\l"	
	.string "라고 했었지...?$"

PetalburgWoods_Text_ICantBeWastingTime: @ 822E712
	.string "큰일 났다!!\n"
	.string "이러고 있을 시간이 없어!$"

PetalburgWoods_Text_YoureLoadedWithItems: @ 822E741
	.string "가방이 가득 찼구나\n"
	.string "그럼 이 수퍼볼을 줄 수 없겠네$"

PetalburgWoods_Text_GoBugPokemonTeam: @ 822E77D
	.string "포켓몬을 왕창 잡았어!\p"
	.string "자 가랏!\n"
	.string "나의 벌레포켓몬 팀!$"

PetalburgWoods_Text_ICouldntWin: @ 822E7C1
	.string "포켓몬이 이렇게 많은데\n"
	.string "이길 수 없다니...$"

PetalburgWoods_Text_ImOutOfPokeBalls: @ 822E7EF
	.string "포켓몬을 많이 잡았더니\n"
	.string "몬스터볼이 부족해졌어$"

PetalburgWoods_Text_InstantlyPopularWithBugPokemon: @ 822E827
	.string "벌레포켓몬을 학교에 가지고 가면\n"
	.string "완전 인기쟁이가 되겠지?!$"

PetalburgWoods_Text_CantBePopularIfILose: @ 822E86B
	.string "져버리면 인기쟁이가 될 수 없어...$"

PetalburgWoods_Text_PeopleRespectYou: @ 822E889
	.string "큰 벌레포켓몬을 가지고 있기만 해도\n"
	.string "존경받지 않을까?!$"

PetalburgWoods_Text_IWantRematch1: @ 822E8C3
	.string "I want a rematch when my BUG\n"
	.string "POKéMON grow up!\p"
	.string "I'm registering you in my POKéNAV!$"

PetalburgWoods_Text_IWantRematch2: @ 822E914
	.string "I want a rematch when my BUG \n"
	.string "POKéMON grow up!\p"
	.string "I'm registering you in my POKéNAV!$"

PetalburgWoods_Text_MyPokemonHaveGrown: @ 822E966
	.string "내 벌레포켓몬 짱 많이 컸어!\n"
	.string "이제 이걸로 또 인기쟁이가 될 거야!$"

PetalburgWoods_Text_CantBePopularIfLose: @ 822E998
	.string "져버리면 인기쟁이가 될 수 없어...$"

PetalburgWoods_Text_IveBeenTrainingHard: @ 822E9B6
	.string "강한 포켓몬을 가지고 있으면\n"
	.string "인기쟁이가 될 수 있겠지?\l"
	.string "그래서 열심히 키우고 있는 거야!$"

PetalburgWoods_Text_StayOutOfTallGrass: @ 822EA0C
	.string "여어! 네 포켓몬 괜찮아?\p"
	.string "지닌 포켓몬이 약해져서\n"
	.string "배틀에 내보내고 싶지 않을 때는\p"
	.string "되도록이면 풀숲을 피해서\n"
	.string "움직이는 게 좋을 거야!$"

PetalburgWoods_Text_HiddenItemsExplanation: @ 822EA8B
	.string "눈에 보이진 않아도\n"
	.string "도구가 떨어져 있을 때가 있어서\l"
	.string "발밑을 찾아보고 있어!$"

PetalburgWoods_Text_TryUsingThisItem: @ 822EAFE
	.string "어머! 네가 갖고 있는 그거!\n"
	.string "금탄체육관의 배지!\p"
	.string "그걸 가지고 있다는 건\n"
	.string "너 포켓몬 트레이너구나\p"
	.string "그럼\n"
	.string "이 도구 한번 사용해 보는 건 어때?$"

PetalburgWoods_Text_MiracleSeedExplanation: @ 822EB63
	.string "기적의씨를\n"
	.string "지니게 하면 풀타입\l"
	.string "기술의 위력이 올라가\p"
	.string "기적의씨 외에도\n"
	.string "포켓몬에게 지니게 하면 편리한\l"
	.string "도구가 있다고 하더라고$"

PetalburgWoods_Text_TrainerTipsExperience: @ 822EC10
	.string "정보 나눔 게시판!!\p"
	.string "승부할 때\n"
	.string "한 번이라도 배틀에 나온 포켓몬은\l"
	.string "경험치를 받을 수 있습니다!\p"
	.string "약한 포켓몬을\n"
	.string "지닌 포켓몬 리스트의\l"
	.string "왼쪽 위에 놓고\l"
	.string "승부할 때 바로 교체!\p"
	.string "이렇게 하면 약한 포켓몬도\n"
	.string "키울 수 있어요!$"

PetalburgWoods_Text_TrainerTipsPP: @ 822ED07
	.string "정보 나눔 게시판!!\p"
	.string "포켓몬에게는 히트포인트 외에\n"
	.string "기술을 사용하기 위한 힘의 근원인\l"
	.string "파워포인트가 있습니다\p"
	.string "기술의 파워포인트를\n"
	.string "모두 사용했을 때도\l"
	.string "포켓몬센터로 갑시다!$"

