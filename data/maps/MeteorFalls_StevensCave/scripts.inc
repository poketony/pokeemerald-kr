.set LOCALID_STEVEN, 1

MeteorFalls_StevensCave_MapScripts:: @ 823B181
	.byte 0

MeteorFalls_StevensCave_EventScript_Steven:: @ 823B182
	lock
	goto_if_set FLAG_DEFEATED_METEOR_FALLS_STEVEN, MeteorFalls_StevensCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN, MeteorFalls_StevensCave_Text_StevenDefeat
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_METEOR_FALLS_STEVEN
	release
	end

MeteorFalls_StevensCave_EventScript_Defeated:: @ 823B1CD
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst: @ 823B1E1
	.string "성호: 호오 {PLAYER}\n"
	.string "내가 여기 있는 걸 잘도 알았네\p"
	.string "설마 너... 나를\n"
	.string "평범한 돌마니아라고 생각하는 거야?\p"
	.string "...아니 이끼시티의 우주센터에서\n"
	.string "같이 싸웠었으니까\p"
	.string "내가 얼마나 강한지는\n"
	.string "너도 알고 있겠지\p"
	.string "좋아 {PLAYER}\p"
	.string "진심으로 승부할 거라면\n"
	.string "각오하고 덤벼봐!$"
	// ダイゴ『へぇ §あ§おｎ
	// ボクが ここにいるって よく わかったねｐ
	// もしかして きみ…… ボクをｎ
	// ただの いしマニアだと おもってる?ｐ
	// ……いや トクサネの うちゅうセンタ-でｎ
	// いっしょに たたかったからｐ
	// ボクが どれくらい つよいのかｎ
	// きみだって しってるはず だよねｐ
	// よし §あ§おｐ
	// ほんきで しょうぶ するならｎ
	// かくごして くれよな!

MeteorFalls_StevensCave_Text_StevenDefeat: @ 823B32D
	.string "너는...\n"
	.string "이 정도로 강해져 있었구나$"
	// きみは……ｎ
	// これほどまでに つよくなって いたのか

MeteorFalls_StevensCave_Text_MyPredictionCameTrue: @ 823B358
	.string "성호: 그러고 보니...\n"
	.string "무로마을의 바위 동굴에서\l"
	.string "처음으로 만났을 때부터\p"
	.string "언젠가 네가 챔피언이\n"
	.string "될 거 같다는 느낌이 들었어\p"
	.string "내 예상은\n"
	.string "대체로 잘 맞거든\p"
	.string "그럼...\n"
	.string "다음으로 네가 향할 곳은...\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "후후후 아무리 나라도\n"
	.string "그런 것까진 모르겠다$"
	// ダイゴ『そういえば……ｎ
	// ムロ タウンの いしのどうくつでｌ
	// はじめて あった ときからｐ
	// いずれ きみは チャンピオンにｎ
	// なるような きが していたｐ
	// ボクの よそうはｎ
	// だいたい いつも あたるんだよｐ
	// じゃあ……ｎ
	// つぎに きみが むかうのは……ｐ
	// …… …… ……ｎ
	// …… …… ……ｐ
	// ふふふ さすがの ボクもｎ
	// そんなこと までは わからないな

