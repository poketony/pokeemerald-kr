BattleFrontier_BattlePyramidFloor_MapScripts:: @ 8252A33
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattlePyramidFloor_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidFloor_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePyramidFloor_OnTransition
	.byte 0

BattleFrontier_BattlePyramidFloor_OnFrame: @ 8252A43
	map_script_2 VAR_TEMP_D, 1, BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight
	map_script_2 VAR_TEMP_E, 0, BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic
	map_script_2 VAR_TEMP_F, 1, BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName
	.2byte 0

BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight:: @ 8252A5D
	lockall
	@ pyramid_updatelight, cant use macro because it straddles the loop
	setvar VAR_0x8004, BATTLE_PYRAMID_FUNC_UPDATE_LIGHT
	setvar VAR_0x8005, 4
	setvar VAR_0x8006, PYRAMID_LIGHT_INCR_RADIUS
	setvar VAR_0x8007, SE_SAVE
	setvar VAR_RESULT, 0
BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop:: @ 8252A77
	special CallBattlePyramidFunction
	delay 2
	compare VAR_RESULT, 2
	goto_if_ne BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop
	setvar VAR_TEMP_D, 0
	releaseall
	end

BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName:: @ 8252A8F
	special ShowMapNamePopup
	setvar VAR_TEMP_F, 0
	end

BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic:: @ 8252A98
	playbgm MUS_B_PYRAMID, 0
	setvar VAR_TEMP_E, 1
	end

BattleFrontier_BattlePyramidFloor_OnResume: @ 8252AA2
	pyramid_setfloorpal
	frontier_getstatus
	switch VAR_TEMP_0
	case 0, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	case CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramid_EventScript_WarpToLobby
	case CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	compare VAR_RESULT, B_OUTCOME_DREW
	goto_if_eq BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	compare VAR_RESULT, B_OUTCOME_FORFEITED
	goto_if_eq BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	frontier_isbattletype BATTLE_TYPE_TRAINER  @ VAR_RESULT seems to be ignored here
	setvar VAR_TEMP_D, 1
BattleFrontier_BattlePyramidFloor_EventScript_ResetParty:: @ 8252B39
	pyramid_resetparty
	end

BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost:: @ 8252B42
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	pyramid_set PYRAMID_DATA_TRAINER_FLAGS, 255
BattleFrontier_BattlePyramid_EventScript_WarpToLobby:: @ 8252B66
	pyramid_updatelight 0, PYRAMID_LIGHT_SET_RADIUS
	pyramid_clearhelditems
	special HealPlayerParty
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY, 255, 7, 13
	waitstate
	end

BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge:: @ 8252B8D
	pyramid_save CHALLENGE_STATUS_SAVING
	special SavePlayerParty
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	pyramid_settrainers
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_OnTransition: @ 8252BCA
	call BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius:: @ 8252BD5
	pyramid_updatelight 32, PYRAMID_LIGHT_SET_RADIUS
	return

BattlePyramid_WarpToNextFloor:: @ 8252BE8
	call BattleFrontier_EventScript_IncrementWinStreak
	frontier_get FRONTIER_DATA_BATTLE_NUM  @ Floor number
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	compare VAR_RESULT, 7
	goto_if_eq BattlePyramid_WarpToTop
	pyramid_seedfloor
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 255, 1, 1
	waitstate
	end

BattlePyramid_WarpToTop:: @ 8252C45
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_TOP, 255, 17, 17
	waitstate
	end

@ TRAINER_PHILLIP is used as a placeholder
BattlePyramid_TrainerBattle:: @ 8252C4F
	trainerbattle TRAINER_BATTLE_PYRAMID, TRAINER_PHILLIP, 0, BattleFacility_TrainerBattle_PlaceholderText, BattleFacility_TrainerBattle_PlaceholderText
	pyramid_showhint
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattlePyramid_FindItemBall:: @ 8252C6A
	pyramid_setitem
	callstd STD_FIND_ITEM
	compare VAR_0x8007, 0
	goto_if_eq BattlePyramid_FindItemBallEnd
	pyramid_hideitem
BattlePyramid_FindItemBallEnd:: @ 8252C87
	end

BattlePyramid_Retire:: @ 8252C88
	goto BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost

@ Also used by Trainer Hill
BattleFacility_TrainerBattle_PlaceholderText: @ 8252C8D
	.string "테스트 메시지입니다$"
	// テストメッセ-ジ です

gText_BattlePyramidConfirmRest:: @ 8252CA7
	.string "배틀피라미드의 상황을\n"
	.string "리포트에 작성하고 중단합니다\l"
	.string "괜찮겠습니까?$"
	// バトルピラミッドの できごとをｎ
	// レポ-トに かいて ちゅうだん しますｌ
	// よろしいですか?

gText_BattlePyramidConfirmRetire:: @ 8252CFB
	.string "배틀피라미드의 도전을\n"
	.string "중지해도 정말 괜찮겠습니까?$"
	// バトルピラミッドの ちょうせんをｎ
	// やめて ほんとうに よろしいですか?

BattlePyramid_Text_ExitHintUp1:: @ 8252D2D
	.string "이 층의 출구는\n"
	.string "{UP_ARROW} 방향에 있어$"
	// この だんの でぐちはｎ
	// し の ほうこうに あるんだよ

BattlePyramid_Text_ExitHintLeft1:: @ 8252D57
	.string "이 층의 출구는\n"
	.string "{LEFT_ARROW} 방향에 있어$"
	// この だんの でぐちはｎ
	// しいの ほうこうに あるんだよ

BattlePyramid_Text_ExitHintRight1:: @ 8252D81
	.string "이 층의 출구는\n"
	.string "{RIGHT_ARROW} 방향에 있어$"
	// この だんの でぐちはｎ
	// しいの ほうこうに あるんだよ

BattlePyramid_Text_ExitHintDown1:: @ 8252DAB
	.string "이 층의 출구는\n"
	.string "{DOWN_ARROW} 방향에 있어$"
	// この だんの でぐちはｎ
	// しいの ほうこうに あるんだよ

BattlePyramid_Text_ExitHintUp2:: @ 8252DD5
	.string "이 층의 출구는\n"
	.string "{UP_ARROW} 방향에 있어$"
	// この だんの でぐちはｎ
	// し の ほうこうに あるの

BattlePyramid_Text_ExitHintLeft2:: @ 8252E03
	.string "이 층의 출구는\n"
	.string "{LEFT_ARROW} 방향에 있어$"
	// この だんの でぐちはｎ
	// し の ほうこうに あるの

BattlePyramid_Text_ExitHintRight2:: @ 8252E31
	.string "이 층의 출구는\n"
	.string "{RIGHT_ARROW} 방향에 있어$"
	// この だんの でぐちはｎ
	// し の ほうこうに あるの

BattlePyramid_Text_ExitHintDown2:: @ 8252E5F
	.string "이 층의 출구는\n"
	.string "{DOWN_ARROW} 방향에 있어$"
	// この だんの でぐちはｎ
	// し の ほうこうに あるの

BattlePyramid_Text_ExitHintUp3:: @ 8252E8D
	.string "출구는\n"
	.string "{UP_ARROW} 방향에 있어$"
	// でぐちはｎ
	// し の ほうこうに あるよ

BattlePyramid_Text_ExitHintLeft3:: @ 8252EAA
	.string "출구는\n"
	.string "{LEFT_ARROW} 방향에 있어$"
	// でぐちはｎ
	// し の ほうこうに あるよ

BattlePyramid_Text_ExitHintRight3:: @ 8252EC7
	.string "출구는\n"
	.string "{RIGHT_ARROW} 방향에 있어$"
	// でぐちはｎ
	// し の ほうこうに あるよ

BattlePyramid_Text_ExitHintDown3:: @ 8252EE4
	.string "출구는\n"
	.string "{DOWN_ARROW} 방향에 있어$"
	// でぐちはｎ
	// し の ほうこうに あるよ

BattlePyramid_Text_ExitHintUp4:: @ 8252F01
	.string "이 층의 출구는\n"
	.string "{UP_ARROW} 방향의 어딘가에 있어$"
	// この だんの でぐちはｎ
	// し の ほうこうの どこかに あるわ
BattlePyramid_Text_ExitHintLeft4:: @ 8252F3A
	.string "이 층의 출구는\n"
	.string "{LEFT_ARROW} 방향의 어딘가에 있어$"
	// この だんの でぐちはｎ
	// し の ほうこうの どこかに あるわ

BattlePyramid_Text_ExitHintRight4:: @ 8252F73
	.string "이 층의 출구는\n"
	.string "{RIGHT_ARROW} 방향의 어딘가에 있어$"
	// この だんの でぐちはｎ
	// し の ほうこうの どこかに あるわ

BattlePyramid_Text_ExitHintDown4:: @ 8252FAC
	.string "이 층의 출구는\n"
	.string "{DOWN_ARROW} 방향의 어딘가에 있어$"
	// この だんの でぐちはｎ
	// し の ほうこうの どこかに あるわ

BattlePyramid_Text_ExitHintUp5:: @ 8252FE5
	.string "출구는\n"
	.string "{UP_ARROW} 방향에 있어$"
	// でぐちはｎ
	// し の ほうこうに あるぞ

BattlePyramid_Text_ExitHintLeft5:: @ 8253000
	.string "출구는\n"
	.string "{LEFT_ARROW} 방향에 있어$"
	// でぐちはｎ
	// し の ほうこうに あるぞ

BattlePyramid_Text_ExitHintRight5:: @ 825301B
	.string "출구는\n"
	.string "{RIGHT_ARROW} 방향에 있어$"
	// でぐちはｎ
	// し の ほうこうに あるぞ

BattlePyramid_Text_ExitHintDown5:: @ 8253036
	.string "출구는\n"
	.string "{DOWN_ARROW} 방향에 있어$"
	// でぐちはｎ
	// し の ほうこうに あるぞ

BattlePyramid_Text_ExitHintUp6:: @ 8253051
	.string "출구는\n"
	.string "{UP_ARROW} 방향에 있어$"
	// でぐちはｎ
	// し の ほうこうに あるわね

BattlePyramid_Text_ExitHintLeft6:: @ 825307C
	.string "출구는\n"
	.string "{LEFT_ARROW} 방향에 있어$"
	// でぐちはｎ
	// し の ほうこうに あるわね

BattlePyramid_Text_ExitHintRight6:: @ 82530A7
	.string "출구는\n"
	.string "{RIGHT_ARROW} 방향에 있어$"
	// でぐちはｎ
	// し の ほうこうに あるわね

BattlePyramid_Text_ExitHintDown6:: @ 82530D2
	.string "출구는\n"
	.string "{DOWN_ARROW} 방향에 있어$"
	// でぐちはｎ
	// し の ほうこうに あるわね

BattlePyramid_Text_EightItemsRemaining1:: @ 82530FD
	.string "도구를 찾고 있니?\p"
	.string "도구는\n"
	.string "앞으로 8개 남았어!$"
	// どうぐを さがしているの?ｐ
	// どうぐはｎ
	// あと 8つ おちているんだよ!

BattlePyramid_Text_SevenItemsRemaining1:: @ 8253140
	.string "도구를 찾고 있니?\p"
	.string "도구는\n"
	.string "앞으로 7개 남았어!$"
	// どうぐを さがしているの?ｐ
	// どうぐはｎ
	// あと 7つ おちているんだよ!

BattlePyramid_Text_SixItemsRemaining1:: @ 8253183
	.string "도구를 찾고 있니?\p"
	.string "도구는\n"
	.string "앞으로 6개 남았어!$"
	// どうぐを さがしているの?ｐ
	// どうぐはｎ
	// あと 6つ おちているんだよ!

BattlePyramid_Text_FiveItemsRemaining1:: @ 82531C4
	.string "도구를 찾고 있니?\p"
	.string "도구는\n"
	.string "앞으로 5개 남았어!$"
	// どうぐを さがしているの?ｐ
	// どうぐはｎ
	// あと 5つ おちているんだよ!

BattlePyramid_Text_FourItemsRemaining1:: @ 8253206
	.string "도구를 찾고 있니?\p"
	.string "도구는\n"
	.string "앞으로 4개 남았어!$"
	// どうぐを さがしているの?ｐ
	// どうぐはｎ
	// あと 4つ おちているんだよ!

BattlePyramid_Text_ThreeItemsRemaining1:: @ 8253248
	.string "도구를 찾고 있니?\p"
	.string "도구는\n"
	.string "앞으로 3개 남았어!$"
	// どうぐを さがしているの?ｐ
	// どうぐはｎ
	// あと 3つ おちているんだよ!

BattlePyramid_Text_TwoItemsRemaining1:: @ 825328B
	.string "도구를 찾고 있니?\p"
	.string "도구는\n"
	.string "앞으로 2개 남았어!$"
	// どうぐを さがしているの?ｐ
	// どうぐはｎ
	// あと 2つ おちているんだよ!

BattlePyramid_Text_OneItemRemaining1:: @ 82532CC
	.string "도구를 찾고 있니?\p"
	.string "도구는\n"
	.string "앞으로 1개 남았어!$"
	// どうぐを さがしているの?ｐ
	// どうぐはｎ
	// あと 1つ おちているんだよ!

BattlePyramid_Text_ZeroItemsRemaining1:: @ 825330B
	.string "도구를 찾고 있니?\p"
	.string "도구는\n"
	.string "이제 어디에도 없어!$"
	// どうぐを さがしているの?ｐ
	// どうぐはｎ
	// もう おちていないんだよ!

BattlePyramid_Text_EightItemsRemaining2:: @ 825334D
	.string "이긴 기념으로\n"
	.string "힌트를 알려 줄게!\p"
	.string "여기에는 도구가\n"
	.string "앞으로 8개 남았어$"
	// かった ごほうびにｎ
	// ヒミツを おしえて あげちゃう!ｐ
	// ここには どうぐがｎ
	// あと 8つ おちているの

BattlePyramid_Text_SevenItemsRemaining2:: @ 82533A6
	.string "이긴 기념으로\n"
	.string "힌트를 알려 줄게!\p"
	.string "여기에는 도구가\n"
	.string "앞으로 7개 남았어$"
	// かった ごほうびにｎ
	// ヒミツを おしえて あげちゃう!ｐ
	// ここには どうぐがｎ
	// あと 7つ おちているの

BattlePyramid_Text_SixItemsRemaining2:: @ 8253404
	.string "이긴 기념으로\n"
	.string "힌트를 알려 줄게!\p"
	.string "여기에는 도구가\n"
	.string "앞으로 6개 남았어$"
	// かった ごほうびにｎ
	// ヒミツを おしえて あげちゃう!ｐ
	// ここには どうぐがｎ
	// あと 6つ おちているの

BattlePyramid_Text_FiveItemsRemaining2:: @ 8253460
	.string "이긴 기념으로\n"
	.string "힌트를 알려 줄게!\p"
	.string "여기에는 도구가\n"
	.string "앞으로 5개 남았어$"
	// かった ごほうびにｎ
	// ヒミツを おしえて あげちゃう!ｐ
	// ここには どうぐがｎ
	// あと 5つ おちているの

BattlePyramid_Text_FourItemsRemaining2:: @ 82534BD
	.string "이긴 기념으로\n"
	.string "힌트를 알려 줄게!\p"
	.string "여기에는 도구가\n"
	.string "앞으로 4개 남았어$"
	// かった ごほうびにｎ
	// ヒミツを おしえて あげちゃう!ｐ
	// ここには どうぐがｎ
	// あと 4つ おちているの

BattlePyramid_Text_ThreeItemsRemaining2:: @ 825351A
	.string "이긴 기념으로\n"
	.string "힌트를 알려 줄게!\p"
	.string "여기에는 도구가\n"
	.string "앞으로 3개 남았어$"
	// かった ごほうびにｎ
	// ヒミツを おしえて あげちゃう!ｐ
	// ここには どうぐがｎ
	// あと 3つ おちているの

BattlePyramid_Text_TwoItemsRemaining2:: @ 8253578
	.string "이긴 기념으로\n"
	.string "힌트를 알려 줄게!\p"
	.string "여기에는 도구가\n"
	.string "앞으로 2개 남았어$"
	// かった ごほうびにｎ
	// ヒミツを おしえて あげちゃう!ｐ
	// ここには どうぐがｎ
	// あと 2つ おちているの

BattlePyramid_Text_OneItemRemaining2:: @ 82535D4
	.string "이긴 기념으로\n"
	.string "힌트를 알려 줄게!\p"
	.string "여기에는 도구가\n"
	.string "앞으로 1개 남았어$"
	// かった ごほうびにｎ
	// ヒミツを おしえて あげちゃう!ｐ
	// ここには どうぐがｎ
	// あと 1つ おちているの

BattlePyramid_Text_ZeroItemsRemaining2:: @ 825362E
	.string "이긴 기념으로\n"
	.string "힌트를 알려 줄게!\p"
	.string "여기에는 도구가\n"
	.string "이제 없어$"
	// かった ごほうびにｎ
	// ヒミツを おしえて あげちゃう!ｐ
	// ここには どうぐがｎ
	// もう おちていないの

BattlePyramid_Text_EightItemsRemaining3:: @ 825368B
	.string "도구가 부족해?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 8개 정도 있나 봐!$"
	// どうぐは たりている?ｐ
	// この だんにはｎ
	// どうぐが あと 8つほど あるそうだよ!

BattlePyramid_Text_SevenItemsRemaining3:: @ 82536F8
	.string "도구가 부족해?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 7개 정도 있나 봐!$"
	// どうぐは たりている?ｐ
	// この だんにはｎ
	// どうぐが あと 7つほど あるそうだよ!

BattlePyramid_Text_SixItemsRemaining3:: @ 8253765
	.string "도구가 부족해?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 6개 정도 있나 봐!$"
	// どうぐは たりている?ｐ
	// この だんにはｎ
	// どうぐが あと 6つほど あるそうだよ!

BattlePyramid_Text_FiveItemsRemaining3:: @ 82537D0
	.string "도구가 부족해?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 5개 정도 있나 봐!$"
	// どうぐは たりている?ｐ
	// この だんにはｎ
	// どうぐが あと 5つほど あるそうだよ!

BattlePyramid_Text_FourItemsRemaining3:: @ 825383C
	.string "도구가 부족해?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 4개 정도 있나 봐!$"
	// どうぐは たりている?ｐ
	// この だんにはｎ
	// どうぐが あと 4つほど あるそうだよ!

BattlePyramid_Text_ThreeItemsRemaining3:: @ 82538A8
	.string "도구가 부족해?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 3개 정도 있나 봐!$"
	// どうぐは たりている?ｐ
	// この だんにはｎ
	// どうぐが あと 3つほど あるそうだよ!

BattlePyramid_Text_TwoItemsRemaining3:: @ 8253915
	.string "도구가 부족해?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 2개 정도 있나 봐!$"
	// どうぐは たりている?ｐ
	// この だんにはｎ
	// どうぐが あと 2つほど あるそうだよ!

BattlePyramid_Text_OneItemRemaining3:: @ 8253980
	.string "도구가 부족해?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 1개 정도 있나 봐!$"
	// どうぐは たりている?ｐ
	// この だんにはｎ
	// どうぐが あと 1つほど あるそうだよ!

BattlePyramid_Text_ZeroItemsRemaining3:: @ 82539EC
	.string "도구가 부족해?\p"
	.string "이 층에는\n"
	.string "이제 도구가 없으니까\l"
	.string "조심해!$"
	// どうぐは たりている?ｐ
	// この だんにはｎ
	// もう どうぐが ないらしいからｌ
	// きを つけてね!

BattlePyramid_Text_EightItemsRemaining4:: @ 8253A69
	.string "강한 당신에게 힌트를 줄게!\p"
	.string "도구는\n"
	.string "앞으로 8개 떨어져 있나 봐!$"
	// つよい あなたに ヒントを あげる!ｐ
	// どうぐはｎ
	// あと 8つ おちているらしいわ!

BattlePyramid_Text_SevenItemsRemaining4:: @ 8253AC4
	.string "강한 당신에게 힌트를 줄게!\p"
	.string "도구는\n"
	.string "앞으로 7개 떨어져 있나 봐!$"
	// つよい あなたに ヒントを あげる!ｐ
	// どうぐはｎ
	// あと 7つ おちているらしいわ!

BattlePyramid_Text_SixItemsRemaining4:: @ 8253B1F
	.string "강한 당신에게 힌트를 줄게!\p"
	.string "도구는\n"
	.string "앞으로 6개 떨어져 있나 봐!$"
	// つよい あなたに ヒントを あげる!ｐ
	// どうぐはｎ
	// あと 6つ おちているらしいわ!

BattlePyramid_Text_FiveItemsRemaining4:: @ 8253B78
	.string "강한 당신에게 힌트를 줄게!\p"
	.string "도구는\n"
	.string "앞으로 5개 떨어져 있나 봐!$"
	// つよい あなたに ヒントを あげる!ｐ
	// どうぐはｎ
	// あと 5つ おちているらしいわ!

BattlePyramid_Text_FourItemsRemaining4:: @ 8253BD2
	.string "강한 당신에게 힌트를 줄게!\p"
	.string "도구는\n"
	.string "앞으로 4개 떨어져 있나 봐!$"
	// つよい あなたに ヒントを あげる!ｐ
	// どうぐはｎ
	// あと 4つ おちているらしいわ!

BattlePyramid_Text_ThreeItemsRemaining4:: @ 8253C2C
	.string "강한 당신에게 힌트를 줄게!\p"
	.string "도구는\n"
	.string "앞으로 3개 떨어져 있나 봐!$"
	// つよい あなたに ヒントを あげる!ｐ
	// どうぐはｎ
	// あと 3つ おちているらしいわ!

BattlePyramid_Text_TwoItemsRemaining4:: @ 8253C87
	.string "강한 당신에게 힌트를 줄게!\p"
	.string "도구는\n"
	.string "앞으로 2개 떨어져 있나 봐!$"
	// つよい あなたに ヒントを あげる!ｐ
	// どうぐはｎ
	// あと 2つ おちているらしいわ!

BattlePyramid_Text_OneItemRemaining4:: @ 8253CE0
	.string "강한 당신에게 힌트를 줄게!\p"
	.string "도구는\n"
	.string "앞으로 1개 떨어져 있나 봐!$"
	// つよい あなたに ヒントを あげる!ｐ
	// どうぐはｎ
	// あと 1つ おちているらしいわ!

BattlePyramid_Text_ZeroItemsRemaining4:: @ 8253D3E
	.string "강한 당신에게 힌트를 줄게!\p"
	.string "도구는\n"
	.string "이제 하나도 없나 봐!$"
	// つよい あなたに ヒントを あげる!ｐ
	// どうぐはｎ
	// もう 1つも おちてないらしいわ!

BattlePyramid_Text_EightItemsRemaining5:: @ 8253D96
	.string "피라미드의 이 층에는\n"
	.string "도구가 8개 있는 듯해...$"
	// ピラミッドの この だんにはｎ
	// どうぐが 8つは あるそうだ……

BattlePyramid_Text_SevenItemsRemaining5:: @ 8253DD2
	.string "피라미드의 이 층에는\n"
	.string "도구가 7개 있는 듯해...$"
	// ピラミッドの この だんにはｎ
	// どうぐが 7つは あるそうだ……

BattlePyramid_Text_SixItemsRemaining5:: @ 8253E0E
	.string "피라미드의 이 층에는\n"
	.string "도구가 6개 있는 듯해...$"
	// ピラミッドの この だんにはｎ
	// どうぐが 6つは あるそうだ……

BattlePyramid_Text_FiveItemsRemaining5:: @ 8253E48
	.string "피라미드의 이 층에는\n"
	.string "도구가 5개 있는 듯해...$"
	// ピラミッドの この だんにはｎ
	// どうぐが 5つは あるそうだ……

BattlePyramid_Text_FourItemsRemaining5:: @ 8253E83
	.string "피라미드의 이 층에는\n"
	.string "도구가 4개 있는 듯해...$"
	// ピラミッドの この だんにはｎ
	// どうぐが 4つは あるそうだ……

BattlePyramid_Text_ThreeItemsRemaining5:: @ 8253EBE
	.string "피라미드의 이 층에는\n"
	.string "도구가 3개 있는 듯해...$"
	// ピラミッドの この だんにはｎ
	// どうぐが 3つは あるそうだ……

BattlePyramid_Text_TwoItemsRemaining5:: @ 8253EFA
	.string "피라미드의 이 층에는\n"
	.string "도구가 2개 있는 듯해...$"
	// ピラミッドの この だんにはｎ
	// どうぐが 2つは あるそうだ……

BattlePyramid_Text_OneItemRemaining5:: @ 8253F34
	.string "피라미드의 이 층에는\n"
	.string "도구가 1개 있는 듯해...$"
	// ピラミッドの この だんにはｎ
	// どうぐが 1つは あるそうだ……

BattlePyramid_Text_ZeroItemsRemaining5:: @ 8253F6C
	.string "피라미드의 이 층에는\n"
	.string "도구가 없는 듯해...$"
	// ピラミッドの この だんにはｎ
	// どうぐは ないそうだ……

BattlePyramid_Text_EightItemsRemaining6:: @ 8253FA5
	.string "도구는 가지고 있어?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 8개 있나 봐$"
	// どうぐは もっているかい?ｐ
	// この だんにはｎ
	// どうぐが あと 8つは あるそうだよ

BattlePyramid_Text_SevenItemsRemaining6:: @ 8253FF7
	.string "도구는 가지고 있어?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 7개 있나 봐$"
	// どうぐは もっているかい?ｐ
	// この だんにはｎ
	// どうぐが あと 7つは あるそうだよ

BattlePyramid_Text_SixItemsRemaining6:: @ 8254049
	.string "도구는 가지고 있어?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 6개 있나 봐$"
	// どうぐは もっているかい?ｐ
	// この だんにはｎ
	// どうぐが あと 6つは あるそうだよ

BattlePyramid_Text_FiveItemsRemaining6:: @ 8254099
	.string "도구는 가지고 있어?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 5개 있나 봐$"
	// どうぐは もっているかい?ｐ
	// この だんにはｎ
	// どうぐが あと 5つは あるそうだよ

BattlePyramid_Text_FourItemsRemaining6:: @ 82540EA
	.string "도구는 가지고 있어?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 4개 있나 봐$"
	// どうぐは もっているかい?ｐ
	// この だんにはｎ
	// どうぐが あと 4つは あるそうだよ

BattlePyramid_Text_ThreeItemsRemaining6:: @ 825413B
	.string "도구는 가지고 있어?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 3개 있나 봐$"
	// どうぐは もっているかい?ｐ
	// この だんにはｎ
	// どうぐが あと 3つは あるそうだよ

BattlePyramid_Text_TwoItemsRemaining6:: @ 825418D
	.string "도구는 가지고 있어?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 2개 있나 봐$"
	// どうぐは もっているかい?ｐ
	// この だんにはｎ
	// どうぐが あと 2つは あるそうだよ

BattlePyramid_Text_OneItemRemaining6:: @ 82541DD
	.string "도구는 가지고 있어?\p"
	.string "이 층에는\n"
	.string "도구가 앞으로 1개 있나 봐$"
	// どうぐは もっているかい?ｐ
	// この だんにはｎ
	// どうぐが あと 1つは あるそうだよ

BattlePyramid_Text_ZeroItemsRemaining6:: @ 825422B
	.string "도구는 가지고 있어?\p"
	.string "이 층에는\n"
	.string "도구가 이제 없나 봐$"
	// どうぐは もっているかい?ｐ
	// この だんにはｎ
	// どうぐが もう ないそうだよ

BattlePyramid_Text_SevenTrainersRemaining1:: @ 825427A
	.string "엄청 강하구나-!!\p"
	.string "하지만 강한 트레이너는\n"
	.string "아직 7명이나 있다고-!$"
	// とっても つよかったよ-!!ｐ
	// でも つよい トレ-ナ-はｎ
	// まだまだ 7にんも いるからね-!

BattlePyramid_Text_SixTrainersRemaining1:: @ 82542CB
	.string "엄청 강하구나-!!\p"
	.string "하지만 강한 트레이너는\n"
	.string "아직 6명이나 있다고-!$"
	// とっても つよかったよ-!!ｐ
	// でも つよい トレ-ナ-はｎ
	// まだまだ 6にんも いるからね-!

BattlePyramid_Text_FiveTrainersRemaining1:: @ 825431A
	.string "엄청 강하구나-!!\p"
	.string "하지만 강한 트레이너는\n"
	.string "아직 5명이나 있다고-!$"
	// とっても つよかったよ-!!ｐ
	// でも つよい トレ-ナ-はｎ
	// まだまだ 5にんも いるからね-!

BattlePyramid_Text_FourTrainersRemaining1:: @ 825436A
	.string "엄청 강하구나-!!\p"
	.string "하지만 강한 트레이너는\n"
	.string "아직 4명이나 있다고-!$"
	// とっても つよかったよ-!!ｐ
	// でも つよい トレ-ナ-はｎ
	// まだまだ 4にんも いるからね-!

BattlePyramid_Text_ThreeTrainersRemaining1:: @ 82543BA
	.string "엄청 강하구나-!!\p"
	.string "하지만 강한 트레이너는\n"
	.string "아직 3명이나 있다고-!$"
	// とっても つよかったよ-!!ｐ
	// でも つよい トレ-ナ-はｎ
	// まだまだ 3にんも いるからね-!

BattlePyramid_Text_TwoTrainersRemaining1:: @ 825440B
	.string "엄청 강하구나-!!\p"
	.string "하지만 강한 트레이너는\n"
	.string "아직 2명이나 있다고-!$"
	// とっても つよかったよ-!!ｐ
	// でも つよい トレ-ナ-はｎ
	// まだまだ 2にんも いるからね-!

BattlePyramid_Text_OneTrainersRemaining1:: @ 825445A
	.string "엄청 강하구나-!!\p"
	.string "하지만 강한 트레이너는\n"
	.string "아직 1명이나 있다고-!$"
	// とっても つよかったよ-!!ｐ
	// でも つよい トレ-ナ-はｎ
	// まだまだ 1にんも いるからね-!

BattlePyramid_Text_ZeroTrainersRemaining1:: @ 82544A6
	.string "엄청 강하구나-!!\p"
	.string "이제 아무도\n"
	.string "널 이길 사람은 없어-!!$"
	// とっても つよかったよ-!!ｐ
	// もう だれもｎ
	// かてる ひとは いないよ-!!

BattlePyramid_Text_SevenTrainersRemaining2:: @ 82544E6
	.string "분하다-!\p"
	.string "하지만 남은 7명의 트레이너가\n"
	.string "분명 널 쓰러뜨려 줄 거야$"
	// くやしい-!ｐ
	// でも あと 7にん いる トレ-ナ-がｎ
	// きっと たおしてくれるわ

BattlePyramid_Text_SixTrainersRemaining2:: @ 8254538
	.string "분하다-!\p"
	.string "하지만 남은 6명의 트레이너가\n"
	.string "분명 널 쓰러뜨려 줄 거야$"
	// くやしい-!ｐ
	// でも あと 6にん いる トレ-ナ-がｎ
	// きっと たおしてくれるわ

BattlePyramid_Text_FiveTrainersRemaining2:: @ 8254588
	.string "분하다-!\p"
	.string "하지만 남은 5명의 트레이너가\n"
	.string "분명 널 쓰러뜨려 줄 거야$"
	// くやしい-!ｐ
	// でも あと 5にん いる トレ-ナ-がｎ
	// きっと たおしてくれるわ

BattlePyramid_Text_FourTrainersRemaining2:: @ 82545D9
	.string "분하다-!\p"
	.string "하지만 남은 4명의 트레이너가\n"
	.string "분명 널 쓰러뜨려 줄 거야$"
	// くやしい-!ｐ
	// でも あと 4にん いる トレ-ナ-がｎ
	// きっと たおしてくれるわ

BattlePyramid_Text_ThreeTrainersRemaining2:: @ 825462A
	.string "분하다-!\p"
	.string "하지만 남은 3명의 트레이너가\n"
	.string "분명 널 쓰러뜨려 줄 거야$"
	// くやしい-!ｐ
	// でも あと 3にん いる トレ-ナ-がｎ
	// きっと たおしてくれるわ

BattlePyramid_Text_TwoTrainersRemaining2:: @ 825467C
	.string "분하다-!\p"
	.string "하지만 남은 2명의 트레이너가\n"
	.string "분명 널 쓰러뜨려 줄 거야$"
	// くやしい-!ｐ
	// でも あと 2にん いる トレ-ナ-がｎ
	// きっと たおしてくれるわ

BattlePyramid_Text_OneTrainersRemaining2:: @ 82546CC
	.string "분하다-!\p"
	.string "하지만 남은 1명의 트레이너가\n"
	.string "분명 널 쓰러뜨려 줄 거야$"
	// くやしい-!ｐ
	// でも あと 1にん いる トレ-ナ-がｎ
	// きっと たおしてくれるわ

BattlePyramid_Text_ZeroTrainersRemaining2:: @ 825471E
	.string "분하다-!\p"
	.string "하지만 이제 싸울 수 있는\n"
	.string "트레이너가 없네-$"
	// くやしい-!ｐ
	// でも もう たたかえるｎ
	// トレ-ナ-が いないの-

BattlePyramid_Text_SevenTrainersRemaining3:: @ 8254767
	.string "꽤 잘하는데-!\p"
	.string "하지만 이 층에 있는 7명의\n"
	.string "트레이너를 쓰러뜨릴 수 있을까?$"
	// やるね-!ｐ
	// でも この だんに あと 7にんも いるｎ
	// トレ-ナ-を たおせるかな?

BattlePyramid_Text_SixTrainersRemaining3:: @ 82547C9
	.string "꽤 잘하는데-!\p"
	.string "하지만 이 층에 있는 6명의\n"
	.string "트레이너를 쓰러뜨릴 수 있을까?$"
	// やるね-!ｐ
	// でも この だんに あと 6にんも いるｎ
	// トレ-ナ-を たおせるかな?

BattlePyramid_Text_FiveTrainersRemaining3:: @ 8254829
	.string "꽤 잘하는데-!\p"
	.string "하지만 이 층에 있는 5명의\n"
	.string "트레이너를 쓰러뜨릴 수 있을까?$"
	// やるね-!ｐ
	// でも この だんに あと 5にんも いるｎ
	// トレ-ナ-を たおせるかな?

BattlePyramid_Text_FourTrainersRemaining3:: @ 825488A
	.string "꽤 잘하는데-!\p"
	.string "하지만 이 층에 있는 4명의\n"
	.string "트레이너를 쓰러뜨릴 수 있을까?$"
	// やるね-!ｐ
	// でも この だんに あと 4にん いるｎ
	// トレ-ナ-を たおせるかな?

BattlePyramid_Text_ThreeTrainersRemaining3:: @ 82548EB
	.string "꽤 잘하는데-!\p"
	.string "하지만 이 층에 있는 3명의\n"
	.string "트레이너를 쓰러뜨릴 수 있을까?$"
	// やるね-!ｐ
	// でも この だんに あと 3にん いるｎ
	// トレ-ナ-を たおせるかな?

BattlePyramid_Text_TwoTrainersRemaining3:: @ 825494D
	.string "꽤 잘하는데-!\p"
	.string "하지만 이 층에 있는 2명의\n"
	.string "트레이너를 쓰러뜨릴 수 있을까?$"
	// やるね-!ｐ
	// でも この だんに あと 2にん いるｎ
	// トレ-ナ-を たおせるかな?

BattlePyramid_Text_OneTrainersRemaining3:: @ 82549AE
	.string "꽤 잘하는데-!\p"
	.string "하지만 이 층에 있는 1명의\n"
	.string "트레이너를 쓰러뜨릴 수 있을까?$"
	// やるね-!ｐ
	// でも この だんに あと 1にん いるｎ
	// トレ-ナ-を たおせるかな?

BattlePyramid_Text_ZeroTrainersRemaining3:: @ 8254A0B
	.string "꽤 잘하는데-!\p"
	.string "이 층에 싸울 수 있는 트레이너는\n"
	.string "이제 아무도 없어$"
	// やるね-!ｐ
	// この だんには たたかえる トレ-ナ-はｎ
	// もう だれも いないよ

BattlePyramid_Text_SevenTrainersRemaining4:: @ 8254A59
	.string "당신이라면 아직 싸우지 않은\n"
	.string "7명의 트레이너를 쓰러뜨릴지도...$"
	// あなたなら まだ たたかっていないｎ
	// 7にんの トレ-ナ-を たおせるかも……

BattlePyramid_Text_SixTrainersRemaining4:: @ 8254A9E
	.string "당신이라면 아직 싸우지 않은\n"
	.string "6명의 트레이너를 쓰러뜨릴지도...$"
	// あなたなら まだ たたかっていないｎ
	// 6にんの トレ-ナ-を たおせるかも……

BattlePyramid_Text_FiveTrainersRemaining4:: @ 8254AE1
	.string "당신이라면 아직 싸우지 않은\n"
	.string "5명의 트레이너를 쓰러뜨릴지도...$"
	// あなたなら まだ たたかっていないｎ
	// 5にんの トレ-ナ-を たおせるかも……

BattlePyramid_Text_FourTrainersRemaining4:: @ 8254B25
	.string "당신이라면 아직 싸우지 않은\n"
	.string "4명의 트레이너를 쓰러뜨릴지도...$"
	// あなたなら まだ たたかっていないｎ
	// 4にんの トレ-ナ-を たおせるかも……

BattlePyramid_Text_ThreeTrainersRemaining4:: @ 8254B69
	.string "당신이라면 아직 싸우지 않은\n"
	.string "3명의 트레이너를 쓰러뜨릴지도...$"
	// あなたなら まだ たたかっていないｎ
	// 3にんの トレ-ナ-を たおせるかも……

BattlePyramid_Text_TwoTrainersRemaining4:: @ 8254BAE
	.string "당신이라면 아직 싸우지 않은\n"
	.string "2명의 트레이너를 쓰러뜨릴지도...$"
	// あなたなら まだ たたかっていないｎ
	// 2にんの トレ-ナ-を たおせるかも……

BattlePyramid_Text_OneTrainersRemaining4:: @ 8254BF1
	.string "당신이라면 아직 싸우지 않은\n"
	.string "1명의 트레이너를 쓰러뜨릴지도...$"
	// あなたなら まだ たたかっていないｎ
	// 1にんの トレ-ナ-を たおせるかも……

BattlePyramid_Text_ZeroTrainersRemaining4:: @ 8254C3E
	.string "당신이 쓰러뜨릴 트레이너는\n"
	.string "이제 아무도 없어...$"
	// あなたを たおせる トレ-ナ-はｎ
	// もう だれも いないわ……

BattlePyramid_Text_SevenTrainersRemaining5:: @ 8254C77
	.string "너라면\n"
	.string "앞으로 7명 남은 대단한 트레이너를\l"
	.string "쓰러뜨릴지도 몰라$"
	// きみならばｎ
	// あと 7にん いる すごうで トレ-ナ-をｌ
	// たおせるかも しれないな

BattlePyramid_Text_SixTrainersRemaining5:: @ 8254CC0
	.string "너라면\n"
	.string "앞으로 6명 남은 대단한 트레이너를\l"
	.string "쓰러뜨릴지도 몰라$"
	// きみならばｎ
	// あと 6にん いる すごうで トレ-ナ-をｌ
	// たおせるかも しれないな

BattlePyramid_Text_FiveTrainersRemaining5:: @ 8254D07
	.string "너라면\n"
	.string "앞으로 5명 남은 대단한 트레이너를\l"
	.string "쓰러뜨릴지도 몰라$"
	// きみならばｎ
	// あと 5にん いる すごうで トレ-ナ-をｌ
	// たおせるかも しれないな

BattlePyramid_Text_FourTrainersRemaining5:: @ 8254D4F
	.string "너라면\n"
	.string "앞으로 4명 남은 대단한 트레이너를\l"
	.string "쓰러뜨릴지도 몰라$"
	// きみならばｎ
	// あと 4にん いる すごうで トレ-ナ-をｌ
	// たおせるかも しれないな

BattlePyramid_Text_ThreeTrainersRemaining5:: @ 8254D97
	.string "너라면\n"
	.string "앞으로 3명 남은 대단한 트레이너를\l"
	.string "쓰러뜨릴지도 몰라$"
	// きみならばｎ
	// あと 3にん いる すごうで トレ-ナ-をｌ
	// たおせるかも しれないな

BattlePyramid_Text_TwoTrainersRemaining5:: @ 8254DE0
	.string "너라면\n"
	.string "앞으로 2명 남은 대단한 트레이너를\l"
	.string "쓰러뜨릴지도 몰라$"
	// きみならばｎ
	// あと 2にん いる すごうで トレ-ナ-をｌ
	// たおせるかも しれないな

BattlePyramid_Text_OneTrainersRemaining5:: @ 8254E27
	.string "너라면\n"
	.string "앞으로 1명 남은 대단한 트레이너를\l"
	.string "쓰러뜨릴지도 몰라$"
	// きみならばｎ
	// あと 1にん いる すごうで トレ-ナ-をｌ
	// たおせるかも しれないな

BattlePyramid_Text_ZeroTrainersRemaining5:: @ 8254E6E
	.string "너는 정말로 강하구나\p"
	.string "이제 여기에는 어디에도\n"
	.string "너를 쓰러뜨릴 트레이너가 없어$"
	// きみは ほんとうに つよいｐ
	// もう ここには どこにもｎ
	// きみを たおせる トレ-ナ-は おらんよ

BattlePyramid_Text_SevenTrainersRemaining6:: @ 8254ED3
	.string "남은 7명의\n"
	.string "트레이너를 쓰러뜨릴 수 있겠어?$"
	// のこり 7にんのｎ
	// トレ-ナ-を たおせるかい?

BattlePyramid_Text_SixTrainersRemaining6:: @ 8254F0E
	.string "남은 6명의\n"
	.string "트레이너를 쓰러뜨릴 수 있겠어?$"
	// のこり 6にんのｎ
	// トレ-ナ-を たおせるかい?

BattlePyramid_Text_FiveTrainersRemaining6:: @ 8254F47
	.string "남은 5명의\n"
	.string "트레이너를 쓰러뜨릴 수 있겠어?$"
	// のこり 5にんのｎ
	// トレ-ナ-を たおせるかい?

BattlePyramid_Text_FourTrainersRemaining6:: @ 8254F81
	.string "남은 4명의\n"
	.string "트레이너를 쓰러뜨릴 수 있겠어?$"
	// のこり 4にんのｎ
	// トレ-ナ-を たおせるかい?

BattlePyramid_Text_ThreeTrainersRemaining6:: @ 8254FBB
	.string "남은 3명의\n"
	.string "트레이너를 쓰러뜨릴 수 있겠어?$"
	// のこり 3にんのｎ
	// トレ-ナ-を たおせるかい?

BattlePyramid_Text_TwoTrainersRemaining6:: @ 8254FF6
	.string "남은 2명의\n"
	.string "트레이너를 쓰러뜨릴 수 있겠어?$"
	// のこり 2にんのｎ
	// トレ-ナ-を たおせるかい?

BattlePyramid_Text_OneTrainersRemaining6:: @ 825502F
	.string "남은 1명의\n"
	.string "트레이너를 쓰러뜨릴 수 있겠어?$"
	// のこり 1にんのｎ
	// トレ-ナ-を たおせるかい?

BattlePyramid_Text_ZeroTrainersRemaining6:: @ 8255068
	.string "여기에는 당신과 싸울 수 있는\n"
	.string "트레이너가 이제 없어...$"
	// ここには あんたと たたかえるｎ
	// トレ-ナ-は もう いないよ……
