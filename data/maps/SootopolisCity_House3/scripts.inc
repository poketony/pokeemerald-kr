SootopolisCity_House3_MapScripts:: @ 8226B71
	.byte 0

SootopolisCity_House3_EventScript_Woman:: @ 8226B72
	lock
	faceplayer
	msgbox SootopolisCity_House3_Text_JuanHasManyFansDoYou, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SootopolisCity_House3_EventScript_HaveFans
	msgbox SootopolisCity_House3_Text_LonesomeTryWorkingHarder, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_HaveFans:: @ 8226B91
	msgbox SootopolisCity_House3_Text_YouMustBePrettyStrong, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_Girl:: @ 8226B9B
	msgbox SootopolisCity_House3_Text_TrainerFanClubWasWild, MSGBOX_NPC
	end

SootopolisCity_House3_Text_JuanHasManyFansDoYou: @ 8226BA4
	.string "당신은 포켓몬 트레이너시군요?\p"
	.string "루네시티의 아단님은\n"
	.string "제자인 윤진님보다\l"
	.string "더 팬이 많아!\p"
	.string "당신은 팬이 있나요?$"
	// あなた ポケモン トレ-ナ-ね?ｐ
	// ルネシティの アダンさまはｎ
	// おでしさんの ミクリさま よりｌ
	// さらに たくさんの ファンが いるのよ!ｐ
	// あなたに ファンは いるのかしら?

SootopolisCity_House3_Text_YouMustBePrettyStrong: @ 8226C20
	.string "흐-응\n"
	.string "그럼 꽤 강하신가 보군요?!$"
	// へえ-ｎ
	// じゃあ けっこう つよいのね!

SootopolisCity_House3_Text_LonesomeTryWorkingHarder: @ 8226C44
	.string "어머머...\n"
	.string "그건 좀 슬프네요\p"
	.string "팬이 많이 생기도록 열심히 해보세요!$"
	// あららん……ｎ
	// それは ちょっと さみしいわねｐ
	// ファンが できるよう がんばりなさいよ!

SootopolisCity_House3_Text_TrainerFanClubWasWild: @ 8226C9C
	.string "열성적인 팬들은 호연지방 밖의\n"
	.string "지역에서도 찾아와!\p"
	.string "내가 해안시티의\n"
	.string "트레이너 팬클럽에 갔었을 때도\l"
	.string "엄청 굉장했어!$"
	// ねっしんな ファンは ホウエン いがいのｎ
	// ちいきからも やってくるの!ｐ
	// あたしが ミナモのｎ
	// トレ-ナ- ファンクラブに いったときもｌ
	// とっても すごかったもの!

