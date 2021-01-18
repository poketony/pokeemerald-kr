RustboroCity_PokemonSchool_MapScripts:: @ 8213EA8
	.byte 0

RustboroCity_PokemonSchool_EventScript_Blackboard:: @ 8213EA9
	lockall
	msgbox RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic:: @ 8213EB8
	message RustboroCity_PokemonSchool_Text_ReadWhichTopic
	waitmessage
	multichoicegrid 8, 1, MULTI_STATUS_INFO, 3, 0
	switch VAR_RESULT
	case 0, RustboroCity_PokemonSchool_EventScript_Poison
	case 1, RustboroCity_PokemonSchool_EventScript_Paralysis
	case 2, RustboroCity_PokemonSchool_EventScript_Sleep
	case 3, RustboroCity_PokemonSchool_EventScript_Burn
	case 4, RustboroCity_PokemonSchool_EventScript_Freeze
	case 5, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	case MULTI_B_PRESSED, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	end

RustboroCity_PokemonSchool_EventScript_Poison:: @ 8213F17
	msgbox RustboroCity_PokemonSchool_Text_ExplainPoison, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Paralysis:: @ 8213F25
	msgbox RustboroCity_PokemonSchool_Text_ExplainParalysis, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Sleep:: @ 8213F33
	msgbox RustboroCity_PokemonSchool_Text_ExplainSleep, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Burn:: @ 8213F41
	msgbox RustboroCity_PokemonSchool_Text_ExplainBurn, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Freeze:: @ 8213F4F
	msgbox RustboroCity_PokemonSchool_Text_ExplainFreeze, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ExitTopicSelect:: @ 8213F5D
	releaseall
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid1:: @ 8213F5F
	msgbox RustboroCity_PokemonSchool_Text_TradingRightNow, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid2:: @ 8213F68
	msgbox RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_RichBoy:: @ 8213F71
	msgbox RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_Lass:: @ 8213F7A
	msgbox RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_SchoolKidM:: @ 8213F83
	msgbox RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_StudentNotebook:: @ 8213F8C
	msgbox RustboroCity_PokemonSchool_Text_StudentsNotes, MSGBOX_SIGN
	end

RustboroCity_PokemonSchool_EventScript_Teacher:: @ 8213F95
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_QUICK_CLAW, RustboroCity_PokemonSchool_EventScript_GaveQuickClaw
	compare VAR_FACING, DIR_EAST
	call_if_eq RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast
	compare VAR_FACING, DIR_WEST
	call_if_eq RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest
	msgbox RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	compare VAR_RESULT, 0
	goto_if_eq Common_EventScript_ShowBagIsFull
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	setflag FLAG_RECEIVED_QUICK_CLAW
	release
	end

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast:: @ 8213FE5
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest:: @ 8213FF0
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_GaveQuickClaw:: @ 8213FFB
	msgbox RustboroCity_PokemonSchool_Text_ExplainQuickClaw, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	release
	end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest: @ 8214010
	walk_left
	walk_down
	walk_down
	walk_right
	walk_in_place_fastest_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_fastest_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	walk_right
	step_end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast: @ 8214027
	walk_right
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_in_place_fastest_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_fastest_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_right
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

RustboroCity_PokemonSchool_EventScript_Scott:: @ 8214040
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE, RustboroCity_PokemonSchool_EventScript_ScottWatchStudents
	goto_if_set FLAG_MET_SCOTT_RUSTBORO, RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_RUSTBORO
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready:: @ 821406F
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge:: @ 8214082
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge:: @ 8214090
	msgbox RustboroCity_PokemonSchool_Text_ScottStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge:: @ 821409E
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottWatchStudents:: @ 82140A8
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges: @ 82140B2
	.string "칠판에\n"
	.string "포켓몬이 배틀할 때 일어나는\l"
	.string "컨디션 변화에 대한 내용이 쓰여 있다$"

RustboroCity_PokemonSchool_Text_ReadWhichTopic: @ 82140F9
	.string "어느 항목을 읽겠습니까?$"

RustboroCity_PokemonSchool_Text_ExplainPoison: @ 821411A
	.string "독에 중독되면\n"
	.string "체력이 줄어듭니다\p"
	.string "배틀 후에도 독 상태는\n"
	.string "그대로 남아서\l"
	.string "이동할 때 체력이 줍니다\p"
	.string "해독제로 치료해줍시다$"

RustboroCity_PokemonSchool_Text_ExplainParalysis: @ 82141D8
	.string "마비가 되면 스피드가 떨어지고\n"
	.string "가끔 기술을\l"
	.string "쓸 수 없게 됩니다\p"
	.string "배틀이 끝난 뒤라도\n"
	.string "마비된 상태는 그대로 남습니다\p"
	.string "마비치료제로 치료해줍시다$"

RustboroCity_PokemonSchool_Text_ExplainSleep: @ 821427D
	.string "잠들어버리면\n"
	.string "그동안에는 공격할 수 없습니다\p"
	.string "스스로 일어나는 경우도 있지만\n"
	.string "잠든 채로 배틀이 끝나면\l"
	.string "계속 잠든 상태로 있습니다\p"
	.string "잠깨는약으로 깨워줍시다$"

RustboroCity_PokemonSchool_Text_ExplainBurn: @ 8214336
	.string "화상을 입으면 공격력이\n"
	.string "떨어질 뿐만 아니라\l"
	.string "체력도 점점 줄어듭니다\p"
	.string "배틀이 끝나도\n"
	.string "화상을 입은 채로 있게 됩니다\p"
	.string "화상치료제로 치료해줍시다$"

RustboroCity_PokemonSchool_Text_ExplainFreeze: @ 82143B8
	.string "얼어버리면\n"
	.string "아무것도 할 수 없게 됩니다\p"
	.string "배틀이 끝나도\n"
	.string "얼어붙은 그대로 있게 됩니다\p"
	.string "얼음상태치료제로 녹여줍시다$"

RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw: @ 8214433
	.string "공부를 하지 않은 학생에게는\n"
	.string "내 손톱의 때를\l"
	.string "달여서 마시게 하겠어!\p"
	.string "네가 공부하는지 안 하는지는\n"
	.string "이 도구를 능숙하게 다룰 수\l"
	.string "있는지를 보면 알 수 있겠지!$"

RustboroCity_PokemonSchool_Text_ExplainQuickClaw: @ 82144C8
	.string "포켓몬에게 선제공격손톱을\n"
	.string "지니게 하면 가끔 빨라져서\l"
	.string "선제공격을 할 때가 있어!\p"
	.string "이렇게 포켓몬에게\n"
	.string "지니게 하는 도구만 해도\l"
	.string "공부할 게 엄청 많다고!$"

RustboroCity_PokemonSchool_Text_TradingRightNow: @ 821459F
	.string "지금 친구와\n"
	.string "포켓몬을 교환하고 있어!$"

RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot: @ 82145CD
	.string "갖고 싶었던 도토링을\n"
	.string "이제야 손에 넣을 수 있어!$"

RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems: @ 8214604
	.string "포켓몬도\n"
	.string "도구를 지닐 수 있지만\p"
	.string "상처약이나 해독제 같은\n"
	.string "사람이 만든 도구는\l"
	.string "사용법을 잘 모르는 것 같아$"

RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself: @ 8214669
	.string "포켓몬의 기술로\n"
	.string "혼란이 될 때가 있잖아?\p"
	.string "혼란이 되면 가끔 착각해서\n"
	.string "자신을 공격해버려...\p"
	.string "하지만 한 번이라도\n"
	.string "배틀에서 멀어지면\l"
	.string "원래대로 돌아와!$"

RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry: @ 8214719
	.string "...포켓몬에게\n"
	.string "나무열매를 지니게 하면\l"
	.string "스스로 체력을 회복한다\p"
	.string "포켓몬이 지닐 수 있는 도구는\n"
	.string "그 밖에도 많다...\p"
	.string "노트에 제대로 기록하는 건\n"
	.string "참 힘들어....$"

RustboroCity_PokemonSchool_Text_StudentsNotes: @ 82147A2
	.string "이 아이의 노트다...\p"
	.string "포켓몬은 몬스터볼로 잡아서\n"
	.string "동시에 6마리 지닐 수 있다\p"
	.string "그렇게 잡은 포켓몬을\n"
	.string "키워서 배틀시키는 사람을\l"
	.string "포켓몬 트레이너라고 한다\p"
	.string "각 지역의\n"
	.string "포켓몬체육관에 있는\l"
	.string "강한 트레이너를 이기는 것!\p"
	.string "그것이 포켓몬 트레이너의\n"
	.string "목표라고 할 수 있다$"

RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut: @ 82148C0
	.string "응? 너하고는 확실히\n"
	.string "등화도시에서 만났었던가\p"
	.string "내 이름은 금작화\p"
	.string "포켓몬 승부의 재능을 가진\n"
	.string "우수한 인재를 찾아\l"
	.string "각지를 여행하고 있지\p"
	.string "스쿨에 견학하러 왔다는 건\n"
	.string "너도 트레이너인 거지?\p"
	.string "그렇다면 일단 풀베기를\n"
	.string "포켓몬에게 가르쳐야겠네!\p"
	.string "풀베기는 분명 이 마을의\n"
	.string "누군가가 가지고 있었지$"
	// おや? きみとは たしかｎ
	// トウカシティで あった きがするねｐ
	// わたしの なまえは エニシダｐ
	// ポケモンしょうぶの さいのうを もったｎ
	// ゆうしゅうな じんざいを もとめてｌ
	// かくちを たびして いるのさｐ
	// スク-ルを のぞきにきた ということはｎ
	// きみも トレ-ナ-?ｐ
	// ならば まずは いあいぎりをｎ
	// ポケモンに おぼえさせると いいね!ｐ
	// いあいぎりは たしか このまちのｎ
	// だれかが もっていた はずだよ

RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown: @ 8214A5F
	.string "금작화: 으-음 여기에 있는\p"
	.string "학생들의 재능은\n"
	.string "아직 알 수 없어! 이제부터 시작이지!$"
	// エニシダ『う-ん ここに いるｎ
	// せいとさん たちの さいのうはｌ
	// まだまだ みちすう! これから だな!

RustboroCity_PokemonSchool_Text_ScottStoneBadge: @ 8214AB6
	.string "금작화: 음 그건...\n"
	.string "스톤배지구나\l"
	.string "꽤 실력이 좋은데!\p"
	.string "하지만 되도록이면\n"
	.string "싸우는 모습을 보고 싶었어\l"
	.string "리그배지만으로는 네가\l"
	.string "어떤 트레이너인지\l"
	.string "잘 모르니까 말야$"
	// エニシダ『ん それは……ｎ
	// スト-ンバッジ だねｌ
	// なかなか やるじゃ ないか!ｐ
	// だけど できればｎ
	// たたかっている ところを みたかったなｌ
	// リ-グバッジ だけでは きみがｌ
	// どんな トレ-ナ- なのかはｌ
	// よく わからない からね

RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge: @ 8214B8A
	.string "응? 너하고는 확실히\n"
	.string "등화도시에서 만났었던가\p"
	.string "내 이름은 금작화\p"
	.string "포켓몬 승부의 재능을 가진\n"
	.string "우수한 인재를 찾아\l"
	.string "각지를 여행하고 있지\p"
	.string "네가 가진 그건...\n"
	.string "스톤배지구나\l"
	.string "신참 트레이너치고는 실력이 좋네\p"
	.string "하지만 되도록이면\n"
	.string "싸우는 모습을 보고 싶었어\l"
	.string "리그배지만으로는 네가\l"
	.string "어떤 트레이너인지\l"
	.string "잘 모르니까 말야$"
	// おや? きみとは たしかｎ
	// トウカシティで あった きがするねｐ
	// わたしの なまえは エニシダｐ
	// ポケモンしょうぶの さいのうを もったｎ
	// ゆうしゅうな じんざいを もとめてｌ
	// かくちを たびして いるのさｐ
	// きみの それは……ｎ
	// スト-ンバッジ だねｌ
	// トレ-ナ-に なりたてに しては やるねｐ
	// だけど できればｎ
	// たたかっている ところを みたかったなｌ
	// リ-グバッジ だけでは きみがｌ
	// どんな トレ-ナ- なのかはｌ
	// よく わからない からね

