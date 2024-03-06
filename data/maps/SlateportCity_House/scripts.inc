SlateportCity_House_MapScripts:: @ 820D9AE
	.byte 0

SlateportCity_House_EventScript_PokefanM:: @ 820D9AF
	msgbox SlateportCity_House_Text_NatureToDoWithStatGains, MSGBOX_NPC
	end

SlateportCity_House_EventScript_Girl:: @ 820D9B8
	msgbox SlateportCity_House_Text_MustBeGoingToBattleTent, MSGBOX_NPC
	end

SlateportCity_House_Text_NatureToDoWithStatGains: @ 820D9C1
	.string "내 포켓몬은 성격이 성급해서\n"
	.string "다른 포켓몬에 비해\l"
	.string "스피드가 빨라\p"
	.string "성격에 따라 오르기 쉬운 능력이\n"
	.string "다른 걸까?$"
	@ わたしの ポケモン せっかちでねｎ
	@ ほかの ポケモンと くらべるとｌ
	@ すばやさが たかいんだわｐ
	@ せいかくで そだちやすい のうりょくにｎ
	@ ちがいが あるのかもな?

SlateportCity_House_Text_MustBeGoingToBattleTent: @ 820DA59
	.string "당신 포켓몬 트레이너구나\n"
	.string "잿빛도시에 왔다는 건\l"
	.string "당연히 배틀텐트에 갈 셈이겠지!$"
	@ あなた ポケモントレ-ナ-ねｎ
	@ カイナシティに きた っていうことはｌ
	@ とうぜん バトルテントに いくのね!

