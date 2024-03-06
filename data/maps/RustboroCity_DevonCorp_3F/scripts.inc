.set LOCALID_DEVON_EMPLOYEE, 2

RustboroCity_DevonCorp_3F_MapScripts:: @ 821242D
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_3F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, RustboroCity_DevonCorp_3F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_DevonCorp_3F_OnFrame
	.byte 0

RustboroCity_DevonCorp_3F_OnTransition: @ 821243D
	compare VAR_DEVON_CORP_3F_STATE, 0
	call_if_eq RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos
	end

RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos:: @ 8212449
	setobjectxyperm LOCALID_DEVON_EMPLOYEE, 3, 2
	setobjectmovementtype LOCALID_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_LEFT
	return

RustboroCity_DevonCorp_3F_OnWarp: @ 8212455
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast
	.2byte 0

RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast:: @ 821245F
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	end

RustboroCity_DevonCorp_3F_OnFrame: @ 8212464
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_MeetPresident
	.2byte 0

RustboroCity_DevonCorp_3F_EventScript_MeetPresident:: @ 821246E
	lockall
	msgbox RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen
	waitmovement 0
	delay 80
	applymovement LOCALID_DEVON_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_FOLLOW_ME, 0
	applymovement LOCALID_DEVON_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_PleaseGoAhead, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	applymovement LOCALID_DEVON_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor, MSGBOX_DEFAULT
	giveitem ITEM_LETTER
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_3F_Text_ReceivedPokenav
	waitfanfare
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_RECEIVED_POKENAV
	setflag FLAG_HIDE_RUSTBORO_CITY_POKEMON_SCHOOL_SCOTT
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare, MSGBOX_DEFAULT
	setflag FLAG_HIDE_ROUTE_116_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDA
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_BRINEY_LOCATION, 1
	clearflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setvar VAR_DEVON_CORP_3F_STATE, 1
	setvar VAR_RUSTBORO_CITY_STATE, 6
	releaseall
	end

RustboroCity_DevonCorp_3F_Movement_Unused: @ 821252F
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_left
	step_end

RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident: @ 8212534
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_left
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk: @ 8212543
	delay_16
	walk_in_place_fastest_down
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen: @ 8212546
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer: @ 821254F
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident: @ 8212558
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk: @ 8212566
	delay_16
	delay_16
	walk_down
	walk_down
	walk_in_place_fastest_right
	step_end

RustboroCity_DevonCorp_3F_EventScript_MrStone:: @ 821256C
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EXP_SHARE, RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor
	goto_if_set FLAG_DELIVERED_STEVEN_LETTER, RustboroCity_DevonCorp_3F_EventScript_GiveExpShare
	msgbox RustboroCity_DevonCorp_3F_Text_CountingOnYou, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_GiveExpShare:: @ 8212595
	msgbox RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter, MSGBOX_DEFAULT
	giveitem ITEM_EXP_SHARE
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EXP_SHARE
	msgbox RustboroCity_DevonCorp_3F_Text_ExplainExpShare, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor:: @ 82125CC
	msgbox RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_Employee:: @ 82125E1
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REPEAT_BALL, RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls
	msgbox RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls:: @ 82125F6
	msgbox RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_RareRocksDisplay:: @ 8212600
	msgbox RustboroCity_DevonCorp_3F_Text_RareRocksDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor: @ 8212609
	.string "내가 데봉 코포레이션\n"
	.string "사장인 나발명이다!\p"
	.string "자네에 대한 얘기는 아까 들었지!\p"
	.string "놀랍게도 우리 연구원을\n"
	.string "두 번이나 구해줬다면서?\p"
	.string "...그래서 그런 대단한 자네에게\n"
	.string "부탁을 하나 하고 싶네!\p"
	.string "자네가 화물을 가지고\n"
	.string "잿빛시티의 조선소로 전달하기로 했지?\p"
	.string "그런데 도중에\n"
	.string "무로마을에 들러줄 수 있겠나?\p"
	.string "무로마을에 있는\n"
	.string "성호라는 남자에게\l"
	.string "이 편지를 전해다오!$"
	@ わしが デボン コ-ポレ-ションｎ
	@ しゃちょうの ツワブキ だ!ｐ
	@ きみの ことは さっき きいたよ!ｐ
	@ なんでも うちの けんきゅういんをｎ
	@ 2ども たすけてくれた とかｐ
	@ ……で そんな すごい きみにｎ
	@ たのみごとを したいのだ!ｐ
	@ きみは にもつを とどけにｎ
	@ カイナの ぞうせんじょに いくんだろう?ｐ
	@ その とちゅうにｎ
	@ ムロタウンにも よって ほしいのだよ!ｐ
	@ いや- ムロタウンにｎ
	@ ダイゴという おとこが いるはずでねｌ
	@ ちょいと てがみを とどけてほしいのだ!

RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis: @ 821277C
	.string "나발명: 물론 나는\n"
	.string "굉-장히 훌륭한 사장이니까!\p"
	.string "답례도 없이 부탁하는\n"
	.string "인색한 짓은 하지 않는다!\p"
	.string "자네에게 이걸 선물하도록 하지!$"
	@ ツワブキ『もちろん わしはｎ
	@ すご-い しゃちょうで あるからな!ｐ
	@ ただで おねがいすると いうようなｎ
	@ ケチな まねは しないのだ!ｐ
	@ きみに こいつを プレゼントしよう!

RustboroCity_DevonCorp_3F_Text_ReceivedPokenav: @ 8212820
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "포켓내비를 손에 넣었다!$"
	@ §あはｎ
	@ ポケナビを てにいれた!

RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp: @ 8212837
	.string "나발명: 그건...\p"
	.string "포켓몬 내비게이터!\n"
	.string "줄여서 포켓내비라고도 하는데\p"
	.string "모험을 떠나는 트레이너의\n"
	.string "필수품이란다!\p"
	.string "그걸로 호연맵을 보면\n"
	.string "무로마을과 잿빛도시의 위치도\l"
	.string "간단히 확인할 수 있지!\p"
	.string "...최근 아쿠아인지 마그마인지\n"
	.string "하는 수상한 녀석들이\l"
	.string "여기저기서 못된 짓을 하는 것 같더군\p"
	.string "우선은 잠시 쉬고 가거라!$"
	@ ツワブキ『そいつは……ｐ
	@ ポケモン ナビゲ-タ-!ｎ
	@ りゃくして ポケナビ といってなｐ
	@ ぼうけんを する トレ-ナ-のｎ
	@ ひつじゅひん なのだよ!ｐ
	@ そいつで ホウエンマップを みればｎ
	@ ムロや カイナの ばしょ だってｌ
	@ ばっちり わかると いうものだ!ｐ
	@ ……さいきんは アクアだの マグマだのｎ
	@ といった あやしげな れんちゅうがｌ
	@ あちこちで わるさを してるらしいｐ
	@ まずは ひとやすみ していきなさい!

RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare: @ 82129D2
	.string "나발명: 그러면 {PLAYER}{K_AYA}\n"
	.string "조심해서 가거라!$"
	@ ツワブキ『それでは §あ§おｎ
	@ じゅうぶん きをつけて いくのだよ!

RustboroCity_DevonCorp_3F_Text_CountingOnYou: @ 8212A09
	.string "나발명: 잘 부탁한다!$"
	@ ツワブキ『よろしく たのむよ!

RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter: @ 8212A29
	.string "나발명: 편지를 무사히 전달해주었군\n"
	.string "정말로 고맙구나!\p"
	.string "이건 내 감사의 표시다\n"
	.string "트레이너인 자네에게 도움이 될 테지!$"
	@ ツワブキ『てがみを とどけて くれたんだねｎ
	@ いやいや ありがとう!ｐ
	@ こいつは おれい だよｎ
	@ トレ-ナ-の きみに やくだつ はずだ!

RustboroCity_DevonCorp_3F_Text_ExplainExpShare: @ 8212A9E
	.string "나발명: 학습장치를 지닌\n"
	.string "포켓몬은 승부를 하지 않아도\l"
	.string "경험치를 전달받게 된다!\p"
	.string "약한 포켓몬을 키우는 데\n"
	.string "제법 편리한 도구지!$"
	@ ツワブキ『がくしゅうそうちを もたせたｎ
	@ ポケモンは しょうぶを しなくてもｌ
	@ けいけんちを わけて もらえる!ｐ
	@ よわい ポケモンを そだてるのにｎ
	@ なかなか べんりな どうぐ なのだよ!

RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends: @ 8212B78
	.string "나발명: 나는 젊었을 때부터\n"
	.string "일만 해 왔기 때문에\l"
	.string "잘 모르네만...\p"
	.string "젊은 사람들은 역시 트레이너가 되어\n"
	.string "포켓몬리그에 나가는 게 목표인가?$"
	@ ツワブキ『わたしは わかいころ からｎ
	@ しごと ばかり だったからｌ
	@ いまいち わからんのだが……ｐ
	@ わかものは やはり トレ-ナ-としてｎ
	@ ポケモンリ-グを めざす もの なのかね

RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere: @ 8212C37
	.string "여기가 데봉 코포레이션 3층\n"
	.string "사장실입니다!\p"
	.string "이야-! 당신에겐\n"
	.string "진심으로 감사드립니다\p"
	.string "그런데... 되찾아주신\n"
	.string "화물 말인데요\p"
	.string "그걸 잿빛도시의 조선소\n"
	.string "그러니까 배 공장까지\l"
	.string "운반해 주셨으면 좋겠습니다!\p"
	.string "또 이상한 놈들에게\n"
	.string "빼앗기는 건 정말 싫을 것 같거든요\p"
	.string "에헤헤...\n"
	.string "잘 부탁드리겠습니다\p"
	.string "잠깐 기다려 주세요$"
	@ ここが デボン コ-ポレ-ション 3かいｎ
	@ しゃちょうの おへや なのよね!ｐ
	@ いや-! きみにはｎ
	@ かんしゃ かんげき あめ あられ なのですｐ
	@ ところで…… きみがｎ
	@ とりもどしてくれた にもつｐ
	@ そいつを カイナシティの ぞうせんじょｎ
	@ つまり ふねの こうじょうへｌ
	@ とどけて ほしいのです!ｐ
	@ また おかしな やつらにｎ
	@ うばわれては たまりません からねｐ
	@ えへへ……ｎ
	@ よろしく おねがい しますよｐ
	@ ちょっと まっていて くださいね

RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe: @ 8212DE8
	.string "사장님께서 꼭 좀\n"
	.string "이야기를 나누고 싶어하십니다\p"
	.string "저를 따라와 주세요$"
	@ しゃちょうが ぜひｎ
	@ おはなし したいそうですｐ
	@ わたしに ついて きてください

RustboroCity_DevonCorp_3F_Text_PleaseGoAhead: @ 8212E2F
	.string "자자 이쪽으로 오세요!$"
	@ ささ どうぞ!

RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard: @ 8212E41
	.string "잿빛도시의 조선소에는\n"
	.string "해양관장이라는 사람이 있으니까\l"
	.string "그 사람에게 가 보시면 될 겁니다!$"
	@ カイナの ぞうせんじょ にはｎ
	@ クスノキさん という ひとが いるからｌ
	@ かれを たずねていくと いいですよ!

RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular: @ 8212E88
	.string "데봉의 신상품\n"
	.string "리피드볼과 타이마볼\l"
	.string "지금 트레이너들에게 대인기랍니다!$"
	@ デボンの しんせいひんｎ
	@ リピ-トボ-ルと タイマ-ボ-ルｌ
	@ トレ-ナ-に だいにんき なのよね!

RustboroCity_DevonCorp_3F_Text_RareRocksDisplay: @ 8212EE9
	.string "사장이 수집한\n"
	.string "희귀한 돌이 장식되어 있다!$"
	@ しゃちょうの あつめたｎ
	@ めずらしい いしが かざってある!

