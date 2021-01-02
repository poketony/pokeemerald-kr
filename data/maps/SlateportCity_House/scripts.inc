SlateportCity_House_MapScripts:: @ 820D9AE
	.byte 0

SlateportCity_House_EventScript_PokefanM:: @ 820D9AF
	msgbox SlateportCity_House_Text_NatureToDoWithStatGains, MSGBOX_NPC
	end

SlateportCity_House_EventScript_Girl:: @ 820D9B8
	msgbox SlateportCity_House_Text_MustBeGoingToBattleTent, MSGBOX_NPC
	end

SlateportCity_House_Text_NatureToDoWithStatGains: @ 820D9C1
	.string "내 포켓몬은 성격이 “성급”이라\n"
	.string "다른 포켓몬에 비해\l"
	.string "스피드가 빠르더군\p"
	.string "성격에 따라 오르기 쉬운 능력이\n"
	.string "다른 건가?$"

SlateportCity_House_Text_MustBeGoingToBattleTent: @ 820DA59
	.string "You're a TRAINER, aren't you?\p"
	.string "Since you came to SLATEPORT CITY,\n"
	.string "you must be going to the BATTLE TENT.$"

