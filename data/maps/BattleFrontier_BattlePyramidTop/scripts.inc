.set LOCALID_ATTENDANT, 1
.set LOCALID_BRANDON, 2

BattleFrontier_BattlePyramidTop_MapScripts:: @ 82550A1
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattlePyramidTop_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidTop_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePyramidTop_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePyramidTop_OnWarp
	.byte 0

BattleFrontier_BattlePyramidTop_OnTransition: @ 82550B6
	pyramid_updatelight 200, PYRAMID_LIGHT_SET_RADIUS
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidTop_OnWarp: @ 82550CE
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePyramidTop_EventScript_SetUpObjects
	.2byte 0

BattleFrontier_BattlePyramidTop_EventScript_SetUpObjects:: @ 82550D8
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	compare VAR_TEMP_C, 0
	goto_if_ne BattleFrontier_BattlePyramidTop_EventScript_EndSetUpObjects
	setobjectxyperm LOCALID_BRANDON, 0, 0
BattleFrontier_BattlePyramidTop_EventScript_EndSetUpObjects:: @ 82550F3
	end

BattleFrontier_BattlePyramidTop_OnResume: @ 82550F4
	frontier_getbrainstatus
	compare VAR_RESULT, FRONTIER_BRAIN_NOT_READY
	goto_if_eq BattleFrontier_BattlePyramidTop_EventScript_CheckChallengeStatus
	call BattleFrontier_EventScript_SetBrainObjectGfx
BattleFrontier_BattlePyramidTop_EventScript_CheckChallengeStatus:: @ 825510C
	copyvar VAR_TEMP_C, VAR_RESULT
	frontier_getstatus
	switch VAR_TEMP_0
	case 0, BattleFrontier_BattlePyramidTop_EventScript_ReadyChallenge
	case CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramid_EventScript_WarpToLobby
	case CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidTop_EventScript_ReadyChallenge
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	compare VAR_RESULT, B_OUTCOME_DREW
	goto_if_eq BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	compare VAR_RESULT, B_OUTCOME_FORFEITED
	goto_if_eq BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattlePyramidTop_OnFrame: @ 825516E
	map_script_2 VAR_TEMP_E, 0, BattleFrontier_BattlePyramidTop_EventScript_PlayPyramidMusic
	map_script_2 VAR_TEMP_F, 1, BattleFrontier_BattlePyramidTop_EventScript_ShowMapName
	.2byte 0

BattleFrontier_BattlePyramidTop_EventScript_PlayPyramidMusic:: @ 8255180
	playbgm MUS_B_PYRAMID_TOP, 0
	setvar VAR_TEMP_E, 1
	end

BattleFrontier_BattlePyramidTop_EventScript_ShowMapName:: @ 825518A
	special ShowMapNamePopup
	setvar VAR_TEMP_F, 0
	end

BattleFrontier_BattlePyramidTop_EventScript_ReadyChallenge:: @ 8255193
	pyramid_save CHALLENGE_STATUS_SAVING
	special SavePlayerParty
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	pyramid_settrainers
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidTop_EventScript_Attendant:: @ 82551D0
	lock
	faceplayer
	compare VAR_TEMP_D, 0
	goto_if_ne BattleFrontier_BattlePyramidTop_EventScript_StepForwardWhenReady
	compare VAR_TEMP_C, FRONTIER_BRAIN_NOT_READY
	goto_if_ne BattleFrontier_BattlePyramidTop_EventScript_BrandonHereMoveAside
	msgbox BattleFrontier_BattlePyramidTop_Text_ReachedSummitUpYouGo, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidTop_Movement_AttendantMoveAside
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePyramidTop_Movement_PlayerClimbToTop
	waitmovement 0
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidTop_Movement_AttendantBlockPath
	waitmovement 0
	message BattleFrontier_BattlePyramidTop_Text_PlayerConqueredPyramid
	waitmessage
	playfanfare MUS_OBTAIN_B_POINTS
	waitfanfare
	closemessage
BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon:: @ 825521A
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_WON
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY, 255, 7, 13
	waitstate
	end

BattleFrontier_BattlePyramidTop_EventScript_StepForwardWhenReady:: @ 8255236
	msgbox BattleFrontier_BattlePyramidTop_Text_StepForwardWhenReady, MSGBOX_DEFAULT
	closemessage
	end

BattleFrontier_BattlePyramidTop_EventScript_BrandonHereMoveAside:: @ 8255240
	msgbox BattleFrontier_BattlePyramidTop_Text_ChiefBeatYouHere, MSGBOX_DEFAULT
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidTop_Movement_AttendantMoveAside
	setvar VAR_TEMP_D, 1
	closemessage
	end

BattleFrontier_BattlePyramidTop_EventScript_BattleBrandon:: @ 8255256
	lockall
	switch VAR_TEMP_C
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattlePyramidTop_EventScript_BrandonIntroGold
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardSilverSpeech
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardGoldSpeech
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardSilverSpeech
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleFrontier_BattlePyramidTop_Movement_CameraPanUp
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidTop_Text_ExplorationsAreGrandestAdventure, MSGBOX_DEFAULT
	closemessage
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
	applymovement LOCALID_BRANDON, BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidTop_Text_ImPyramidKingBrandon, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidTop_EventScript_BattleBrandonSilver
	end

BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardSilverSpeech:: @ 82552D0
	applymovement LOCALID_BRANDON, BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer
	waitmovement 0
BattleFrontier_BattlePyramidTop_EventScript_BattleBrandonSilver:: @ 82552DA
	msgbox BattleFrontier_BattlePyramidTop_Text_BringCourageToOurBattle, MSGBOX_DEFAULT
	call BattleFrontier_BattlePyramidTop_EventScript_DoBrandonBattle
	playbgm MUS_B_PYRAMID_TOP, 0
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattlePyramidTop_EventScript_DefeatedBrandonSilver
	goto BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost

BattleFrontier_BattlePyramidTop_EventScript_DefeatedBrandonSilver:: @ 82552FB
	frontier_getsymbols
	compare VAR_RESULT, 0
	goto_if_ne BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon
	msgbox BattleFrontier_BattlePyramidTop_Text_BrandonFrontierPassPlease, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattlePyramidTop_Text_ReceivedBraveSymbol
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattlePyramidTop_Text_LookForwardToNextMeeting, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon

BattleFrontier_BattlePyramidTop_EventScript_BrandonIntroGold:: @ 8255335
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	compare VAR_RESULT, FALSE
	goto_if_ne BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardGoldSpeech
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleFrontier_BattlePyramidTop_Movement_CameraPanUp
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidTop_Text_BrandonYouveReturned, MSGBOX_DEFAULT
	closemessage
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
	applymovement LOCALID_BRANDON, BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidTop_Text_MyCourageIsOffMeter, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidTop_EventScript_BattleBrandonGold
	end

BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardGoldSpeech:: @ 8255388
	applymovement LOCALID_BRANDON, BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer
	waitmovement 0
BattleFrontier_BattlePyramidTop_EventScript_BattleBrandonGold:: @ 8255392
	msgbox BattleFrontier_BattlePyramidTop_Text_EverythingYouHave, MSGBOX_DEFAULT
	call BattleFrontier_BattlePyramidTop_EventScript_DoBrandonBattle
	playbgm MUS_B_PYRAMID_TOP, 0
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattlePyramidTop_EventScript_DefeatedBrandonGold
	goto BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost

BattleFrontier_BattlePyramidTop_EventScript_DefeatedBrandonGold:: @ 82553B3
	frontier_getsymbols
	compare VAR_RESULT, 2
	goto_if_eq BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon
	msgbox BattleFrontier_BattlePyramidTop_Text_BrandonRemarkableHaveThis, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattlePyramidTop_Text_BraveSymbolTookGoldenShine
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattlePyramidTop_Text_FarewellForNow, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon

BattleFrontier_BattlePyramidTop_EventScript_DoBrandonBattle:: @ 82553ED
	closemessage
	setvar VAR_0x8004, SPECIAL_BATTLE_PYRAMID
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	return

BattleFrontier_BattlePyramidTop_Movement_AttendantMoveAside: @ 82553FD
	walk_right
	walk_in_place_fastest_left
	step_end

BattleFrontier_BattlePyramidTop_Movement_AttendantBlockPath: @ 8255400
	walk_left
	walk_in_place_fastest_up
	step_end

BattleFrontier_BattlePyramidTop_Movement_PlayerClimbToTop: @ 8255403
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer: @ 825540A
	walk_fast_down
	step_end

BattleFrontier_BattlePyramidTop_Movement_CameraPanUp: @ 825540C
	walk_slow_up
	walk_slow_up
	delay_16
	step_end

BattleFrontier_BattlePyramidTop_Text_ReachedSummitUpYouGo: @ 8255410
	.string "도착하셨군요!\n"
	.string "여기가 배틀피라미드의 정상!\p"
	.string "이 위에 있는 것이\n"
	.string "피라미드의 꼭대기입니다!\p"
	.string "배틀피라미드를 제패한 자만이\n"
	.string "이 위로 갈 수 있습니다!\p"
	.string "자! 올라가 주십시오!$"
	// まいられましたぞ!ｎ
	// ここは バトルピラミッドの ちょうじょう!ｐ
	// この うえに あるのがｎ
	// ピラミッドのいただき ですぞ!ｐ
	// バトルピラミッドを せいはした もののみｎ
	// この うえに たつことが できるのですぞ!ｐ
	// さあ! のぼってくだされ!

BattleFrontier_BattlePyramidTop_Text_PlayerConqueredPyramid: @ 82554E8
	.string "새로운 피라미드 제패자!\n"
	.string "그 이름은 {PLAYER}!$"
	// あらたなる ピラミッド せいはしゃ!ｎ
	// そのなは {PLAYER}!

BattleFrontier_BattlePyramidTop_Text_ChiefBeatYouHere: @ 825551F
	.string "도착하셨군요!\p"
	.string "...... ...라고 말하려 했지만\n"
	.string "조금 늦으셨습니다!!\p"
	.string "이미 저희 대장님께서\n"
	.string "피라미드를 제패하셨습니다!!\p"
	.string "하지만 모험자여!!\p"
	.string "당신도 트레이너라면\n"
	.string "그 힘으로 대장님에게서\l"
	.string "영광의 정상을 쟁취할 수 있을 터!\p"
	.string "자! 준비가 되었다면\n"
	.string "용기의 한 걸음을 내딛는 겁니다!$"
	// まいられましたぞ!ｐ
	// …… …… と いいたい ところ ですがｎ
	// わずかに おそかった ですな!!ｐ
	// すでに われらが たいちょうがｎ
	// ピラミッドを せいは されましたぞ!!ｐ
	// しかし ぼうけんしゃよ!ｐ
	// あなたも トレ-ナ- ならばｎ
	// その ちからで たいちょうからｌ
	// えいこうの いただきを かちとるのです!ｐ
	// さあ! じゅんびが できたらｎ
	// ゆうきの いっぽを ふみだすの ですぞ!

BattleFrontier_BattlePyramidTop_Text_ExplorationsAreGrandestAdventure: @ 8255669
	.string "젊은 모험자여...\n"
	.string "모험은 좋지 않은가...\p"
	.string "그대의 지혜!\p"
	.string "그대의 힘!\p"
	.string "그대의 포켓몬!\p"
	.string "그리고 무엇보다도\n"
	.string "자신의 용기를 쥐어짜\l"
	.string "미지의 세계로 나아가게 만들지...$"
	// わかき ぼうけんしゃよ……ｎ
	// ぼうけんとは いいもの だな……ｐ
	// おのれの ちえ!ｐ
	// おのれの ちから!ｐ
	// おのれの ポケモン!ｐ
	// そして なによりｎ
	// おのれの ゆうきを ふりしぼってｌ
	// みちなる せかいへと つきすすむ……

BattleFrontier_BattlePyramidTop_Text_ImPyramidKingBrandon: @ 825573E
	.string "이거 정말 끝내주지 않나?\n"
	.string "끝내주지! 안 그래?!\p"
	.string "나는 기선!\p"
	.string "이곳의 책임자인\n"
	.string "피라미드킹이지만 모두에게는\l"
	.string "대장이라고 불리고 있지!\p"
	.string "너도 여기까지 왔다는 건\n"
	.string "그만큼 자신이 있다는 거겠지?\l"
	.string "하하하! 이거 정말 재밌는데!$"
	// いやぁ- じつに たまらない!ｎ
	// たまらないじゃ ないか! なあっ!?ｐ
	// わたしは ジンダイ!ｐ
	// ここの せきにんしゃで あるｎ
	// ピラミッドキングだが みんなにはｌ
	// たいちょうと よばれて いるぞ!ｐ
	// きみも ここまで きたと いうことはｎ
	// それなりの じしんが あるの だろう?ｌ
	// はっはっは! いやぁ- じつに たのしみだ!

BattleFrontier_BattlePyramidTop_Text_BringCourageToOurBattle: @ 8255846
	.string "자! 네 뜨거운 용기를\n"
	.string "부딪쳐 보라고!$"
	// さあ! きみの あつい ゆうきをｎ
	// ぶつけて きたまえ!

BattleFrontier_BattlePyramidTop_Text_BrandonFrontierPassPlease: @ 8255873
	.string "기선: 하하하!\n"
	.string "이거 정말 굉장하구만!\p"
	.string "좋아! 너를 인정해 주지!!\n"
	.string "프런티어패스를 줘봐!$"
	// ジンダイ『はっはっは!ｎ
	// いやぁ- じつに すばらしい!ｐ
	// いいぞ! きみを みとめようじゃ ないか!!ｎ
	// フロンティアパスを かすんだ!

BattleFrontier_BattlePyramidTop_Text_ReceivedBraveSymbol: @ 82558E9
	.string "프런티어패스에\n"
	.string "브레이브심볼이 새겨졌다!$"
	// フロンティアパスにｎ
	// ブレイブシンボルが きざまれた!

BattleFrontier_BattlePyramidTop_Text_LookForwardToNextMeeting: @ 825591D
	.string "젊은 모험자여!\n"
	.string "다시 만날 날을 기대하지!!$"
	// わかき ぼうけんしゃよ!ｎ
	// また あえる ときを まっているぞ!!

BattleFrontier_BattlePyramidTop_Text_BrandonYouveReturned: @ 8255951
	.string "기선: ...여기까지 온 건가\n"
	.string "젊은 모험자여...\p"
	.string "너는 정말 마음에서부터\n"
	.string "모험을 사랑하고 있는 것 같군...\p"
	.string "그래... 마치 젊은 날의\n"
	.string "나와 닮았어...\p"
	.string "뜨겁고!!\p"
	.string "위험하고!!\p"
	.string "괴로운!!\p"
	.string "그 목숨을 건 모험의 날들이\n"
	.string "되살아나는 것 같아...$"
	// ジンダイ『…… ここまで たどりついたかｎ
	// わかき ぼうけんしゃよ……ｐ
	// きみは ほんとうに こころからｎ
	// ぼうけんを あいして いるようだな……ｐ
	// そう…… まるで わかき ひのｎ
	// わたし そっくりじゃ ないか……ｐ
	// …… …… …… おお……ｐ
	// あつく!!ｐ
	// きけんで!!ｐ
	// くるしい!!ｐ
	// あの いのちがけの ぼうけんの ひびがｎ
	// よみがえって きたぞ……

BattleFrontier_BattlePyramidTop_Text_MyCourageIsOffMeter: @ 8255A6D
	.string "좋---앗!\p"
	.string "내 용기센서도\n"
	.string "최고치구만!!$"
	// よ---しっ!!ｐ
	// わたしの ゆうきセンサ-もｎ
	// ぜっこうちょう!!

BattleFrontier_BattlePyramidTop_Text_EverythingYouHave: @ 8255AA1
	.string "네가 가진 전부를!\n"
	.string "내가 받아내 주마!!$"
	// きみの すべて!ｎ
	// わたしが うけとめよう じゃないか!!

BattleFrontier_BattlePyramidTop_Text_BrandonRemarkableHaveThis: @ 8255ACD
	.string "기선: 하하하!\n"
	.string "이거 정말 굉장하구만!\l"
	.string "정말 최고야!!\p"
	.string "젊은 모험자여!!\p"
	.string "네게는 당해낼 수가 없구만!\n"
	.string "자! 이걸 받아줘!$"
	// ジンダイ『はっはっはっ!ｎ
	// いやぁ- じつに すばらしい!ｌ
	// まったく さいこうじゃ ないか!!ｐ
	// わかき ぼうけんしゃよ!!ｐ
	// きみには かんぱい だよ!ｎ
	// さあ! こいつを うけとって くれ!!

BattleFrontier_BattlePyramidTop_Text_BraveSymbolTookGoldenShine: @ 8255B59
	.string "브레이브심볼이\n"
	.string "금색으로 빛났다!$"
	// ブレイブシンボルがｎ
	// きんいろに かがやいた!

BattleFrontier_BattlePyramidTop_Text_FarewellForNow: @ 8255B82
	.string "이거 정말 나도\n"
	.string "아직 멀었다는 건가!!\p"
	.string "인연이 있으면 다시 만나자!\n"
	.string "작별이다! 젊은 모험자여!!$"
	// いやぁ- わたしもｎ
	// まだまだと いうこと らしいな!!ｐ
	// えんが あったら また あおう!ｎ
	// さらばだ! わかき ぼうけんしゃよ!!

BattleFrontier_BattlePyramidTop_Text_StepForwardWhenReady: @ 8255BFE
	.string "자! 준비가 되었다면\n"
	.string "용기의 한 걸음을 내딛는 겁니다!$"
	// さあ! じゅんびが できたらｎ
	// ゆうきの いっぽを ふみだすの ですぞ!

