.set LOCALID_ATTENDANT, 1

FallarborTown_BattleTentLobby_MapScripts:: @ 81FFE66
	map_script MAP_SCRIPT_ON_FRAME_TABLE, FallarborTown_BattleTentLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FallarborTown_BattleTentLobby_OnWarp
	.byte 0

FallarborTown_BattleTentLobby_OnWarp: @ 81FFE71
	map_script_2 VAR_TEMP_1, 0, FallarborTown_BattleTentLobby_EventScript_TurnPlayerNorth
	.2byte 0

FallarborTown_BattleTentLobby_EventScript_TurnPlayerNorth:: @ 81FFE7B
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

FallarborTown_BattleTentLobby_OnFrame: @ 81FFE85
	map_script_2 VAR_TEMP_0, 0, FallarborTown_BattleTentLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_SAVING, FallarborTown_BattleTentLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_PAUSED, FallarborTown_BattleTentLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_WON, FallarborTown_BattleTentLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_LOST, FallarborTown_BattleTentLobby_EventScript_LostChallenge
	.2byte 0

FallarborTown_BattleTentLobby_EventScript_GetChallengeStatus:: @ 81FFEAF
	frontier_getstatus
	end

FallarborTown_BattleTentLobby_EventScript_QuitWithoutSaving:: @ 81FFEB8
	lockall
	msgbox FallarborTown_BattleTentLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_0, 255
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	releaseall
	end

FallarborTown_BattleTentLobby_EventScript_WonChallenge:: @ 81FFEED
	lockall
	msgbox FallarborTown_BattleTentLobby_Text_BeatThreeTrainers, MSGBOX_DEFAULT
	message FallarborTown_BattleTentLobby_Text_WaitWhileSaveGame
	waitmessage
	fallarbortent_setrandomprize
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	fallarbortent_save 0
	playse SE_SAVE
	waitse

FallarborTown_BattleTentLobby_EventScript_GivePrize:: @ 81FFF27
	msgbox FallarborTown_BattleTentLobby_Text_PresentYouWithPrize, MSGBOX_DEFAULT
	fallarbortent_giveprize
	switch VAR_RESULT
	case FALSE, FallarborTown_BattleTentLobby_EventScript_NoRoomForPrize
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	message FallarborTown_BattleTentLobby_Text_ReceivedPrize
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox FallarborTown_BattleTentLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

FallarborTown_BattleTentLobby_EventScript_NoRoomForPrize:: @ 81FFF73
	msgbox FallarborTown_BattleTentLobby_Text_BagFullReturnForPrize, MSGBOX_DEFAULT
	waitmessage
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

FallarborTown_BattleTentLobby_EventScript_PrizeWaiting:: @ 81FFF84
	lockall
	msgbox FallarborTown_BattleTentLobby_Text_BeatThreeTrainers, MSGBOX_DEFAULT
	goto FallarborTown_BattleTentLobby_EventScript_GivePrize
	end

FallarborTown_BattleTentLobby_EventScript_LostChallenge:: @ 81FFF93
	lockall
	message FallarborTown_BattleTentLobby_Text_ThankYouWaitWhileSaving
	waitmessage
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	fallarbortent_save 0
	playse SE_SAVE
	waitse
	msgbox FallarborTown_BattleTentLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

FallarborTown_BattleTentLobby_EventScript_ResumeChallenge:: @ 81FFFCD
	lockall
	message FallarborTown_BattleTentLobby_Text_LookingForwardToArrival
	waitmessage
	fallarbortent_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_0, 255
	goto FallarborTown_BattleTentLobby_EventScript_EnterChallenge

FallarborTown_BattleTentLobby_EventScript_Attendant:: @ 8200001
	lock
	faceplayer
	fallarbortent_getprize
	compare VAR_RESULT, ITEM_NONE
	goto_if_ne FallarborTown_BattleTentLobby_EventScript_PrizeWaiting
	special SavePlayerParty
	msgbox FallarborTown_BattleTentLobby_Text_WelcomeToBattleTent, MSGBOX_DEFAULT
FallarborTown_BattleTentLobby_EventScript_AskEnterChallenge:: @ 8200021
	message FallarborTown_BattleTentLobby_Text_TakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, 0
	switch VAR_RESULT
	case 0, FallarborTown_BattleTentLobby_EventScript_TryEnterChallenge
	case 1, FallarborTown_BattleTentLobby_EventScript_ExplainChallenge
	case 2, FallarborTown_BattleTentLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, FallarborTown_BattleTentLobby_EventScript_CancelChallenge

FallarborTown_BattleTentLobby_EventScript_TryEnterChallenge:: @ 820005D
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARENA
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	setvar VAR_RESULT, 2
	frontier_checkineligible
	compare VAR_0x8004, TRUE
	goto_if_eq FallarborTown_BattleTentLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_TENT
	msgbox FallarborTown_BattleTentLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	compare VAR_RESULT, 0
	goto_if_eq FallarborTown_BattleTentLobby_EventScript_LoadPartyCancelChallenge
	msgbox FallarborTown_BattleTentLobby_Text_SaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, FallarborTown_BattleTentLobby_EventScript_LoadPartyCancelChallenge
	case YES, FallarborTown_BattleTentLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, FallarborTown_BattleTentLobby_EventScript_LoadPartyCancelChallenge

FallarborTown_BattleTentLobby_EventScript_SaveBeforeChallenge:: @ 82000E2
	setvar VAR_TEMP_0, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	fallarbortent_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_0, 255
	compare VAR_RESULT, 0
	goto_if_eq FallarborTown_BattleTentLobby_EventScript_CancelChallengeSaveFailed
FallarborTown_BattleTentLobby_EventScript_EnterChallenge:: @ 820013C
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox FallarborTown_BattleTentLobby_Text_GuideYouToBattleTent, MSGBOX_DEFAULT
	closemessage
	call FallarborTown_BattleTentLobby_EventScript_WalkToDoor
	warp MAP_FALLARBOR_TOWN_BATTLE_TENT_CORRIDOR, 255, 2, 7
	setvar VAR_TEMP_0, 0
	waitstate
	end

FallarborTown_BattleTentLobby_EventScript_ExplainChallenge:: @ 8200169
	msgbox FallarborTown_BattleTentLobby_Text_ExplainFallarborTent, MSGBOX_DEFAULT
	goto FallarborTown_BattleTentLobby_EventScript_AskEnterChallenge

FallarborTown_BattleTentLobby_EventScript_NotEnoughValidMons:: @ 8200176
	switch VAR_RESULT
	case FRONTIER_LVL_50, FallarborTown_BattleTentLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, FallarborTown_BattleTentLobby_EventScript_NotEnoughValidMonsLvOpen
FallarborTown_BattleTentLobby_EventScript_NotEnoughValidMonsLv50:: @ 8200191
	msgbox FallarborTown_BattleTentLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto FallarborTown_BattleTentLobby_EventScript_EndCancelChallenge

FallarborTown_BattleTentLobby_EventScript_NotEnoughValidMonsLvOpen:: @ 820019E
	msgbox FallarborTown_BattleTentLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto FallarborTown_BattleTentLobby_EventScript_EndCancelChallenge

FallarborTown_BattleTentLobby_EventScript_CancelChallengeSaveFailed:: @ 82001AB
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto FallarborTown_BattleTentLobby_EventScript_CancelChallenge

FallarborTown_BattleTentLobby_EventScript_LoadPartyCancelChallenge:: @ 82001C2
	special LoadPlayerParty
FallarborTown_BattleTentLobby_EventScript_CancelChallenge:: @ 82001C5
	msgbox FallarborTown_BattleTentLobby_Text_AwaitAnotherChallenge, MSGBOX_DEFAULT
FallarborTown_BattleTentLobby_EventScript_EndCancelChallenge:: @ 82001CD
	release
	end

FallarborTown_BattleTentLobby_EventScript_WalkToDoor:: @ 82001CF
	applymovement LOCALID_ATTENDANT, FallarborTown_BattleTentLobby_Movement_AttendantWalkToDoor
	applymovement OBJ_EVENT_ID_PLAYER, FallarborTown_BattleTentLobby_Movement_PlayerWalkToDoor
	waitmovement 0
	opendoor 6, 1
	waitdooranim
	applymovement LOCALID_ATTENDANT, FallarborTown_BattleTentLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, FallarborTown_BattleTentLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 6, 1
	waitdooranim
	return

FallarborTown_BattleTentLobby_Movement_AttendantWalkToDoor: @ 82001FE
	walk_up
	walk_up
	walk_up
	step_end

FallarborTown_BattleTentLobby_Movement_AttendantEnterDoor: @ 8200202
	walk_up
	set_invisible
	step_end

FallarborTown_BattleTentLobby_Movement_PlayerWalkToDoor: @ 8200205
	walk_up
	walk_up
	walk_up
	step_end

FallarborTown_BattleTentLobby_Movement_PlayerEnterDoor: @ 8200209
	walk_up
	walk_up
	set_invisible
	step_end

FallarborTown_BattleTentLobby_EventScript_Hiker:: @ 820020D
	msgbox FallarborTown_BattleTentLobby_Text_CameToCampOut, MSGBOX_NPC
	end

FallarborTown_BattleTentLobby_EventScript_LittleBoy:: @ 8200216
	msgbox FallarborTown_BattleTentLobby_Text_MakeThinkImJustKid, MSGBOX_NPC
	end

FallarborTown_BattleTentLobby_EventScript_Lass:: @ 820021F
	msgbox FallarborTown_BattleTentLobby_Text_FallarborTentMyFavorite, MSGBOX_NPC
	end

FallarborTown_BattleTentLobby_EventScript_Scott:: @ 8200228
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_IN_FALLARBOR, FallarborTown_BattleTentLobby_EventScript_ScottAlreadySpokenTo
	msgbox FallarborTown_BattleTentLobby_Text_ScottLookingForSomeone, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_IN_FALLARBOR
	release
	end

FallarborTown_BattleTentLobby_EventScript_ScottAlreadySpokenTo:: @ 8200245
	msgbox FallarborTown_BattleTentLobby_Text_ScottMakeChallenge, MSGBOX_DEFAULT
	release
	end

FallarborTown_BattleTentLobby_EventScript_RulesBoard:: @ 820024F
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto FallarborTown_BattleTentLobby_EventScript_ReadRulesBoard
	end

FallarborTown_BattleTentLobby_EventScript_ReadRulesBoard:: @ 820025E
	message BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 0, MULTI_FALLARBOR_TENT_RULES, 0
	switch VAR_RESULT
	case 0, FallarborTown_BattleTentLobby_EventScript_RulesLevel
	case 1, FallarborTown_BattleTentLobby_EventScript_RulesBattle
	case 2, FallarborTown_BattleTentLobby_EventScript_RulesMind
	case 3, FallarborTown_BattleTentLobby_EventScript_RulesSkill
	case 4, FallarborTown_BattleTentLobby_EventScript_RulesBody
	case 5, FallarborTown_BattleTentLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, FallarborTown_BattleTentLobby_EventScript_ExitRules
	end

FallarborTown_BattleTentLobby_EventScript_RulesLevel:: @ 82002BC
	msgbox BattleTentLobby_Text_ExplainLevelRules, MSGBOX_DEFAULT
	goto FallarborTown_BattleTentLobby_EventScript_ReadRulesBoard
	end

FallarborTown_BattleTentLobby_EventScript_RulesBattle:: @ 82002CA
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules, MSGBOX_DEFAULT
	goto FallarborTown_BattleTentLobby_EventScript_ReadRulesBoard
	end

FallarborTown_BattleTentLobby_EventScript_RulesMind:: @ 82002D8
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainMindRules, MSGBOX_DEFAULT
	goto FallarborTown_BattleTentLobby_EventScript_ReadRulesBoard
	end

FallarborTown_BattleTentLobby_EventScript_RulesSkill:: @ 82002E6
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules, MSGBOX_DEFAULT
	goto FallarborTown_BattleTentLobby_EventScript_ReadRulesBoard
	end

FallarborTown_BattleTentLobby_EventScript_RulesBody:: @ 82002F4
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules, MSGBOX_DEFAULT
	goto FallarborTown_BattleTentLobby_EventScript_ReadRulesBoard
	end

FallarborTown_BattleTentLobby_EventScript_ExitRules:: @ 8200302
	releaseall
	end

FallarborTown_BattleTentLobby_Text_MakeThinkImJustKid: @ 8200304
	.string "후후후후후후\p"
	.string "평범한 어린애라고 생각하게 해서\n"
	.string "모두를 방심시키고\l"
	.string "내가 우승하는 거야!$"
	@ ふふふふふふｐ
	@ ほんの こどもだと おもわせてｎ
	@ みんなを ゆだん させてｌ
	@ ボクは ゆうしょう するのだ!

FallarborTown_BattleTentLobby_Text_FallarborTentMyFavorite: @ 8200382
	.string "배틀텐트는 마을에 따라\n"
	.string "도전할 수 있는 종목이 다르지?\l"
	.string "나는 당연히 단풍마을의\l"
	.string "배틀텐트가 좋아!\p"
	.string "믿고 있는 포켓몬들과 이겨나간다니\n"
	.string "엄청 멋지지 않아?$"
	@ バトルテントって まちに よってｎ
	@ ちょうせん できる ことが ちがうでしょ?ｌ
	@ あたしは だんぜん ハジツゲのｌ
	@ バトルテントが すきなのよね!ｐ
	@ しんじてる ポケモンたちと かちぬくってｎ
	@ すごく かっこいいじゃない?

FallarborTown_BattleTentLobby_Text_CameToCampOut: @ 820045A
	.string "텐트라고 해서 캠핑하러 왔는데...\p"
	.string "요즘 텐트는\n"
	.string "호화로운 모양이네\l"
	.string "좋아 온 김에 도전해볼까?$"
	@ テントというから キャンプ しにきたら…ｐ
	@ さいきんの テント というのはｎ
	@ ごうかな もん だなあｌ
	@ よし ついでに ちょうせん してみるか?

FallarborTown_BattleTentLobby_Text_ScottLookingForSomeone: @ 8200501
	.string "금작화: 여어 {PLAYER}{K_AYA}\n"
	.string "왔구나 배틀텐트에!\p"
	.string "정말 이 지방은\n"
	.string "태평한 사람이 많구나\l"
	.string "나는 좀 더 이런...\l"
	.string "이기고 싶은 파워가 넘쳐흐르는\l"
	.string "사람을 원하는데 말이지!\l"
	.string "그런 트레이너가 있다면 바로\p"
	.string "...아니 아냐 아무것도\n"
	.string "그럼 힘내!$"
	@ エニシダ『やあ §あ§おｎ
	@ きたんだね バトルテントに!ｐ
	@ どうも この ちほうはｎ
	@ ノンビリ した ひとが おおくてねｌ
	@ もっと こう……ｌ
	@ かちたい パワ-の ありまくりなｌ
	@ ひとを わたしは もとめて いるんだよ!ｌ
	@ そういう トレ-ナ-が いれば すぐにでもｐ
	@ ……って いや なんでもないよｎ
	@ じゃ がんばってね!

FallarborTown_BattleTentLobby_Text_ScottMakeChallenge: @ 8200653
	.string "금작화: 나한테\n"
	.string "자꾸 말 걸지 말고\l"
	.string "빨리 챌린지를\l"
	.string "해보는 건 어때?$"
	@ エニシダ『わたし なんかにｎ
	@ いつまでも かまって いないでｌ
	@ さっそく チャレンジｌ
	@ して みたら どうだい?

