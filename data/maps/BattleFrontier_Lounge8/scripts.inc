BattleFrontier_Lounge8_MapScripts:: @ 82676C9
	.byte 0

BattleFrontier_Lounge8_EventScript_Man:: @ 82676CA
	msgbox BattleFrontier_Lounge8_Text_WhatATrainerNeeds, MSGBOX_NPC
	end

BattleFrontier_Lounge8_EventScript_Woman:: @ 82676D3
	msgbox BattleFrontier_Lounge8_Text_KnowAboutFrontierBrains, MSGBOX_NPC
	end

BattleFrontier_Lounge8_EventScript_NinjaBoy:: @ 82676DC
	msgbox BattleFrontier_Lounge8_Text_ToldMeIHaveTalentForBattling, MSGBOX_NPC
	end

BattleFrontier_Lounge8_Text_WhatATrainerNeeds: @ 82676E5
	.string "트레이너에게 필요한 것...\p"
	.string "지식...\n"
	.string "전략...\l"
	.string "운...\l"
	.string "투지...\l"
	.string "마음...\l"
	.string "용기...\l"
	.string "그리고 재능인가...\p"
	.string "전부 나한테 있는 거네!\n"
	.string "어느 시설이든 쉽겠어\p"
	.string "응? 포켓몬? 뭐야 그게?$"
	// トレ-ナ-に ひつような もの……ｐ
	// ちしき…ｎ
	// せんりゃく…ｌ
	// うん…ｌ
	// とうし…ｌ
	// こころ…ｌ
	// ゆうき…ｌ
	// そして さいのう か……ｐ
	// ぼく ぜんぶ バッチリ じゃん!ｎ
	// どこの しせつでも らくしょ- だねｐ
	// えっ? ポケモン? なんのことだい?

BattleFrontier_Lounge8_Text_KnowAboutFrontierBrains: @ 826779C
	.string "프런티어브레인이라고 알아?\p"
	.string "배틀프런티어에 있는\n"
	.string "7개의 시설을 관리하는\l"
	.string "특별한 트레이너들을\l"
	.string "금작화가 그렇게 부르나 봐$"
	// フロンティアブレ-ンって しってる?ｐ
	// バトルフロンティアに あるｎ
	// 7つの しせつを かんりするｌ
	// とくべつな トレ-ナ-たちの ことをｌ
	// エニシダは そうよんでる らしいわ

BattleFrontier_Lounge8_Text_ToldMeIHaveTalentForBattling: @ 826782C
	.string "나 배틀타워에서 어떤 누나한테\n"
	.string "배틀의 재능이 있다고\l"
	.string "엄청 칭찬받았어-!\p"
	.string "하지만 난 포켓몬 콘테스트가\n"
	.string "더 좋은걸!\p"
	.string "그치만 포켓몬 콘테스트는\n"
	.string "엄청 못해!\p"
	.string "재능과 좋아하는 건 다른 거야?$"
	// ぼく バトルタワ-で おねえちゃんにｎ
	// たたかいの さいのうが あるねってｌ
	// すごく ほめられたの-!ｐ
	// でも ぼく ポケモン コンテストのｎ
	// ほ-が すき なの!ｐ
	// でも ポケモン コンテストはｎ
	// ぜんぜん だめだよ!ｐ
	// さいのうって すきとは ちがうの?

