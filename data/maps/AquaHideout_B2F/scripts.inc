.set LOCALID_MATT, 1
.set LOCALID_SUBMARINE, 4

AquaHideout_B2F_MapScripts:: @ 8233DCF
	map_script MAP_SCRIPT_ON_TRANSITION, AquaHideout_B2F_OnTransition
	.byte 0

AquaHideout_B2F_OnTransition:
	call_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, AquaHideout_B2F_EventScript_PreventMattNoticing
	end

AquaHideout_B2F_EventScript_PreventMattNoticing::
	setvar VAR_TEMP_1, 1
	return

AquaHideout_B2F_EventScript_MattNoticePlayer::
	lockall
	setvar VAR_0x8008, LOCALID_MATT
	playse SE_PIN
	applymovement VAR_0x8008, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_TEMP_1, 1
	releaseall
	end

AquaHideout_B2F_EventScript_Matt::
	trainerbattle_single TRAINER_MATT, AquaHideout_B2F_Text_MattIntro, AquaHideout_B2F_Text_MattDefeat, AquaHideout_B2F_EventScript_SubmarineEscape
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_SubmarineEscape:: @ 8233E25
	setvar VAR_0x8008, LOCALID_MATT
	setvar VAR_0x8009, LOCALID_SUBMARINE
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_OurBossGotThroughHisPreparations, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFastestLeft
	applymovement VAR_0x8009, AquaHideout_B2F_Movement_SumbarineDepartLeft
	waitmovement 0
	removeobject VAR_0x8009
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	setflag FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE
	setflag FLAG_HIDE_LILYCOVE_CITY_AQUA_GRUNTS
	release
	end

AquaHideout_B2F_Movement_SumbarineDepartLeft:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

@ Unused
AquaHideout_B2F_Movement_SumbarineDepartRight:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

AquaHideout_B2F_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_4, AquaHideout_B2F_Text_Grunt4Intro, AquaHideout_B2F_Text_Grunt4Defeat, AquaHideout_B2F_EventScript_Grunt4Defeated
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt4Defeated::
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_6, AquaHideout_B2F_Text_Grunt6Intro, AquaHideout_B2F_Text_Grunt6Defeat
	msgbox AquaHideout_B2F_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_8, AquaHideout_B2F_Text_Grunt8Intro, AquaHideout_B2F_Text_Grunt8Defeat
	msgbox AquaHideout_B2F_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_Text_MattIntro:
	.string "우효효...\p"
	.string "벌써 여기까지 온 건가!\n"
	.string "생각한 것보다 강하군!\p"
	.string "하지만 여기까지다!\n"
	.string "난 여태까지의 조무래기들과는\l"
	.string "차원이 달라!\p"
	.string "시간벌기 따윈 하지 않고\n"
	.string "널 짓밟아 주지!$"
	// ウヒョヒョ……ｐ
	// もう ここまで きたのか!ｎ
	// おもって いたより やるな!ｐ
	// だが ここまでだ!ｎ
	// おれは これまでの したっぱども とはｌ
	// ひとあじ ちがう!ｐ
	// じかんかせぎ なんか しねえでｎ
	// おまえを コテンパンに してやるぜ!

AquaHideout_B2F_Text_MattDefeat:
	.string "우효효...\n"
	.string "져버렸나...$"
	// ウヒョヒョ……ｎ
	// まけちまったか……

AquaHideout_B2F_Text_OurBossGotThroughHisPreparations:
	.string "우효효...!\p"
	.string "내가 너하고\n"
	.string "놀아준 사이에\l"
	.string "리더는 준비를 끝내셨을 거다!$"
	// ウヒョヒョ……!ｐ
	// おれが おまえとｎ
	// あそんで やっている あいだにｌ
	// リ-ダ-の じゅんびが ととのったぜ!

AquaHideout_B2F_Text_MattPostBattle:
	.string "우효효...!\p"
	.string "리더는 어딘가의 해저에 있는\n"
	.string "동굴로 출발하셨을 거다!\p"
	.string "쫓아가려면 해안시티 너머에\n"
	.string "펼쳐진 거대한 바다를\l"
	.string "마구 돌아다녀 보라고!\p"
	.string "그렇게 해서 찾을 수 있다면 말이지...\n"
	.string "우효효!$"
	// ウヒョヒョ……!ｐ
	// リ-ダ-は どこかの かいていにあるｎ
	// どうくつへ しゅっぱつ したぜ!ｐ
	// おいかける つもりなら ミナモの さきにｎ
	// ひろがる でっかい うみをｌ
	// さがしまわって みるが いいぜ!ｐ
	// それで みつかれば いいけどな……ｎ
	// ウヒョヒョヒョ!

AquaHideout_B2F_Text_Grunt4Intro:
	.string "왓핫핫 목이 빠지는 줄 알았다!\n"
	.string "나랑도 승부해 주실까!$"
	// わっはっは まちくたびれたぞ!ｎ
	// おいらとも しょうぶ してもらおうか!

AquaHideout_B2F_Text_Grunt4Defeat:
	.string "기다리다 너무 지쳐서\n"
	.string "져버렸다...$"
	// まちくたびれてｎ
	// まけて やぶれて……

AquaHideout_B2F_Text_Grunt4PostBattle:
	.string "리더어...\n"
	.string "이 정도면 된 거겠죠-!$"
	// リ-ダ-ぁ……ｎ
	// こんなもんで どうでしょ-!

AquaHideout_B2F_Text_Grunt6Intro:
	.string "아지트의 명물인 워프패널!\p"
	.string "지금 자신이 어디에 있는지\n"
	.string "하나도 모르겠지?\p"
	.string "그렇게 지치게 만들어서 상대를\n"
	.string "쓰러뜨리는 게 작전인 거야!$"
	// アジト じまんの ワ-プパネル!ｐ
	// いま じぶんが どこに いるのかｎ
	// わかって ないでしょ!ｐ
	// そうやって つかれはてた あいてをｎ
	// たおすのが さくせん なのよ!

AquaHideout_B2F_Text_Grunt6Defeat:
	.string "뭐얏!\n"
	.string "하나도 안 지쳐 있잖아!$"
	// なによっ!ｎ
	// ちっとも つかれてない じゃない!

AquaHideout_B2F_Text_Grunt6PostBattle:
	.string "그러고 보니... 마스터볼을\n"
	.string "어디에 뒀었는지 잊어버렸어\p"
	.string "그걸 지키고 있지 않으면\n"
	.string "리더에게 혼이 날 텐데...$"
	// そういえば…… マスタ-ボ-ルをｎ
	// どこに おいたのか わすれちゃったわｐ
	// あれを まもっていないとｎ
	// リ-ダ-に おこられるのよ……

AquaHideout_B2F_Text_Grunt8Intro:
	.string "내가 아쿠아단에 들어와서\n"
	.string "가장 먼저 배운 게\l"
	.string "이 워프패널의 배열이다!$"
	// オレが アクアだんに はいってｎ
	// まっさきに おぼえ させられたのがｌ
	// この ワ-プパネルの はいれつだ!

AquaHideout_B2F_Text_Grunt8Defeat:
	.string "워프패널에 대한 걸로\n"
	.string "머리가 가득 차서...$"
	// ワ-プパネルの ことでｎ
	// あたまが いっぱい だったから……

AquaHideout_B2F_Text_Grunt8PostBattle:
	.string "이제부턴 포켓몬 승부의\n"
	.string "요령도 배워둬야겠다...$"
	// これからは ポケモンしょうぶのｎ
	// コツも おぼえて おかないと なあ……
