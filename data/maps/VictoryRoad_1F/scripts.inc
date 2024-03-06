.set LOCALID_WALLY_ENTRANCE, 4

VictoryRoad_1F_MapScripts:: @ 8235D7A
	map_script MAP_SCRIPT_ON_TRANSITION, VictoryRoad_1F_OnTransition
	.byte 0

VictoryRoad_1F_OnTransition: @ 8235D80
	compare VAR_VICTORY_ROAD_1F_STATE, 1
	call_if_eq VictoryRoad_1F_EventScript_SetEntranceWallyPos1
	compare VAR_VICTORY_ROAD_1F_STATE, 2
	call_if_eq VictoryRoad_1F_EventScript_SetEntranceWallyPos2
	end

VictoryRoad_1F_EventScript_SetEntranceWallyPos1:: @ 8235D97
	setobjectxyperm LOCALID_WALLY_ENTRANCE, 2, 24
	setobjectmovementtype LOCALID_WALLY_ENTRANCE, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_SetEntranceWallyPos2:: @ 8235DA3
	setobjectxyperm LOCALID_WALLY_ENTRANCE, 3, 24
	setobjectmovementtype LOCALID_WALLY_ENTRANCE, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_WallyBattleTrigger1:: @ 8235DAF
	lockall
	setvar VAR_0x8008, 1
	addobject LOCALID_WALLY_ENTRANCE
	applymovement LOCALID_WALLY_ENTRANCE, VictoryRoad_1F_Movement_WallyApproachPlayer1
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyBattleTrigger2:: @ 8235DC8
	lockall
	setvar VAR_0x8008, 2
	addobject LOCALID_WALLY_ENTRANCE
	applymovement LOCALID_WALLY_ENTRANCE, VictoryRoad_1F_Movement_WallyApproachPlayer2
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyEntranceBattle:: @ 8235DE1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_VR_1, VictoryRoad_1F_Text_WallyEntranceDefeat
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	copyobjectxytoperm LOCALID_WALLY_ENTRANCE
	setflag FLAG_DEFEATED_WALLY_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_Movement_WallyApproachPlayer1: @ 8235E15
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

VictoryRoad_1F_Movement_WallyApproachPlayer2: @ 8235E21
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

@ This Wally appears near the entrance once his battle is triggered and remains there until the Hall of Fame is entered
VictoryRoad_1F_EventScript_EntranceWally:: @ 8235E2C
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_NPC
	end

@ This Wally appears and remains at the exit after the Hall of Fame is entered 
VictoryRoad_1F_EventScript_ExitWally:: @ 8235E35
	trainerbattle_single TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq VictoryRoad_1F_EventScript_RematchWally
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_RematchWally:: @ 8235E5C
	trainerbattle_rematch TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Edgar:: @ 8235E73
	trainerbattle_single TRAINER_EDGAR, VictoryRoad_1F_Text_EdgarIntro, VictoryRoad_1F_Text_EdgarDefeat
	msgbox VictoryRoad_1F_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Albert:: @ 8235E8A
	trainerbattle_single TRAINER_ALBERT, VictoryRoad_1F_Text_AlbertIntro, VictoryRoad_1F_Text_AlbertDefeat
	msgbox VictoryRoad_1F_Text_AlbertPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Hope:: @ 8235EA1
	trainerbattle_single TRAINER_HOPE, VictoryRoad_1F_Text_HopeIntro, VictoryRoad_1F_Text_HopeDefeat
	msgbox VictoryRoad_1F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Quincy:: @ 8235EB8
	trainerbattle_single TRAINER_QUINCY, VictoryRoad_1F_Text_QuincyIntro, VictoryRoad_1F_Text_QuincyDefeat
	msgbox VictoryRoad_1F_Text_QuincyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Katelynn:: @ 8235ECF
	trainerbattle_single TRAINER_KATELYNN, VictoryRoad_1F_Text_KatelynnIntro, VictoryRoad_1F_Text_KatelynnDefeat
	msgbox VictoryRoad_1F_Text_KatelynnPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore: @ 8235EE6
	.string "민진: 앗! {PLAYER}님!\p"
	.string "제가 이런 곳에 있어서\n"
	.string "놀라셨죠!\p"
	.string "제가 여기까지 올 수 있었던 건\n"
	.string "{PLAYER}님 덕분이에요!\p"
	.string "그때 {PLAYER}님에게 져서\n"
	.string "전 강해질 수 있었으니까요!\p"
	.string "...하지만!\n"
	.string "전 이제 안 질 거예요\p"
	.string "제게 용기와 건강을 준\n"
	.string "포켓몬을 위해서라도 이기겠어요!\p"
	.string "그럼... 갑니다!$"
	@ ミツル『あっ! §あさん!ｐ
	@ ぼくが こんな ところに いるなんてｎ
	@ おどろいた でしょ!ｐ
	@ ぼくが ここまで これたのはｎ
	@ §あさんの おかげだよ!ｐ
	@ あのとき §あさんに まけたからｎ
	@ ぼくは つよく なれたんだ!ｐ
	@ ……だけど!ｎ
	@ ぼくは もう まけないｐ
	@ ぼくに ゆうきと げんきを くれたｎ
	@ ポケモンの ためにも かつんだ!ｐ
	@ それでは…… いきますよ!

VictoryRoad_1F_Text_WallyEntranceDefeat: @ 8235FFC
	.string "우와아!\n"
	.string "역시 {PLAYER}님은 강하네요!$"
	@ うわぁ!ｎ
	@ やっぱり §あさんは つよいよ!

VictoryRoad_1F_Text_WallyPostEntranceBattle: @ 8236020
	.string "민진: ...이번에는\n"
	.string "{PLAYER}님을 이기지 못했지만\l"
	.string "언젠가 반드시 뒤쫓아 갈 거예요!$"
	@ ミツル『…… こんかいはｎ
	@ §あさんに かてなかった けどｌ
	@ いつか きっと おいついて みせるからね!

VictoryRoad_1F_Text_WallyIntro: @ 8236073
	.string "민진: 앗! {PLAYER}님!\p"
	.string "저 그때보다 강해졌어요!\n"
	.string "그걸 {PLAYER}님에게\l"
	.string "보여 주고 싶어요!\p"
	.string "그럼... 갑니다!$"
	@ ミツル『あっ! §あさん!ｐ
	@ ぼく あれから つよくなった はずだよ!ｎ
	@ それを §あさんにｌ
	@ みてもらいたいんだ!ｐ
	@ それでは…… いきますよ!

VictoryRoad_1F_Text_WallyDefeat: @ 82360DA
	.string "우와아!\n"
	.string "역시 {PLAYER}님은 강하네요!$"
	@ うわぁ!ｎ
	@ やっぱり §あさんは つよいよ!

VictoryRoad_1F_Text_WallyPostBattle: @ 82360FE
	.string "민진: ...이번에는\n"
	.string "{PLAYER}님을 이기지 못했지만\l"
	.string "언젠가 반드시 뒤쫓아 가서...\p"
	.string "포켓몬리그에 도전할 거예요!$"
	@ ミツル『…… こんかいもｎ
	@ §あさんに かてなかった けどｌ
	@ いつか きっと おいついて……ｐ
	@ ポケモンリ-グに ちょうせん するんだ!

VictoryRoad_1F_Text_EdgarIntro: @ 8236184
	.string "여기까지는 어떻게든 왔지만\n"
	.string "앞으로가 엄청 멀어...$"
	@ ここまでは なんとか これたがｎ
	@ あと すこしが とても とおいよ……

VictoryRoad_1F_Text_EdgarDefeat: @ 82361CB
	.string "여기서 끝난 건가...$"
	@ ここで おわったか……

VictoryRoad_1F_Text_EdgarPostBattle: @ 82361E5
	.string "여기까지 왔으면\n"
	.string "기세를 몰아서 챔피언이 되라고!\l"
	.string "너라면 할 수 있을 거야!$"
	@ ここまで きたならｎ
	@ いきおいで チャンピオンに なれよ!ｌ
	@ きみなら できるさ!

VictoryRoad_1F_Text_AlbertIntro: @ 8236248
	.string "모처럼 여기까지 왔는데\n"
	.string "이제 와서 진다는 건 말이 안 되지!$"
	@ せっかく ここまで きたんだｎ
	@ いまさら まけるなんて ありえないよ!

VictoryRoad_1F_Text_AlbertDefeat: @ 8236290
	.string "설마...\n"
	.string "진 건가...?$"
	@ まさか……ｎ
	@ まけたのか……?

VictoryRoad_1F_Text_AlbertPostBattle: @ 82362A4
	.string "여기서 졌다...\p"
	.string "졌다는 것은 아직 챔피언이 될\n"
	.string "자격이 없다는 건가...$"
	@ ここで まけた……ｐ
	@ ということは まだ チャンピオンに なるｎ
	@ しかくが なかったと いうことか……

VictoryRoad_1F_Text_HopeIntro: @ 82362EE
	.string "이 끝없이 험한 길이야말로\n"
	.string "바로 챔피언으로 향하는 길인 거야!$"
	@ この はてしなく けわしい みち こそｎ
	@ まさに チャンピオンへの みち なのよ!

VictoryRoad_1F_Text_HopeDefeat: @ 8236336
	.string "멋진 실력이야...$"
	@ すばらしい たたかいかた ね……

VictoryRoad_1F_Text_HopePostBattle: @ 8236356
	.string "너에겐 챔피언이 될\n"
	.string "가능성이 있는 것 같구나$"
	@ あなたには チャンピオンに なれるｎ
	@ かのうせいが あるみたいね

VictoryRoad_1F_Text_QuincyIntro: @ 8236390
	.string "챔피언로드란 뭘까?\n"
	.string "이기면 알려 주도록 하지!$"
	@ チャンピオンロ-ド とは なにか?ｎ
	@ かてたら おしえてやろう!

VictoryRoad_1F_Text_QuincyDefeat: @ 82363C4
	.string "음 좋다!$"
	@ うん いいだろう!

VictoryRoad_1F_Text_QuincyPostBattle: @ 82363D5
	.string "여기를 무사히 빠져나가는 것이\n"
	.string "포켓몬 챔피언을 노리는 자들의\l"
	.string "마지막 시련인 거다!\p"
	.string "그게 챔피언로드라고\n"
	.string "불리는 이유인 거고$"
	@ ここを ぶじに ぬけきるって ことがｎ
	@ ポケモンチャンピオンを めざす やつのｌ
	@ さいごの しれん なんだ!ｐ
	@ だから チャンピオンロ-ドとｎ
	@ よばれて いるのさ

VictoryRoad_1F_Text_KatelynnIntro: @ 8236468
	.string "여기까지 온 사람에게\n"
	.string "아무것도 할 말은 없어... 간다!$"
	@ ここまで きた ひとにｎ
	@ なにも いうことは ない…… いくわよ!

VictoryRoad_1F_Text_KatelynnDefeat: @ 82364A7
	.string "분해...!$"
	@ くやしいわ……!

VictoryRoad_1F_Text_KatelynnPostBattle: @ 82364BB
	.string "흥... 좋아\n"
	.string "너부터 먼저 가도록 해$"
	@ ふん…… いいわよｎ
	@ あなた から さきに いきなさいよ
