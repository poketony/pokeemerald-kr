SootopolisCity_House7_MapScripts:: @ 82270CB
	.byte 0

SootopolisCity_House7_EventScript_OldMan:: @ 82270CC
	msgbox SootopolisCity_House7_Text_CityFromEruptedVolcano, MSGBOX_NPC
	end

SootopolisCity_House7_EventScript_PokefanF:: @ 82270D5
	msgbox SootopolisCity_House7_Text_CaveMadeToKeepSomething, MSGBOX_NPC
	end

SootopolisCity_House7_Text_CityFromEruptedVolcano: @ 82270DE
	.string "해저에 있던 화산이 분화해서\n"
	.string "바다 위까지 올라왔지\p"
	.string "그리고 분화구에 빗물이 차서\n"
	.string "생긴 게 바로 여기 루네시티야$"
	// かいていに あった かざんが ふんかしてｎ
	// うみの うえまで もりあがるｐ
	// そして ふんかこうに あめが たまってｎ
	// できたのが この ルネシティ なんだよ

SootopolisCity_House7_Text_CaveMadeToKeepSomething: @ 8227190
	.string "루네시티와 바깥세상을 이어주는 동굴\p"
	.string "마치 무언가가 이곳에서 못 나가게\n"
	.string "하려고 만들어진 것 같아...\p"
	.string "...너무 깊게 생각했나?$"
	// ルネと そとのせかいを つなぐ どうくつｐ
	// まるで なにかを ここから ださないようにｎ
	// つくられた みたい だわ……ｐ
	// ……かんがえすぎ かしら?

