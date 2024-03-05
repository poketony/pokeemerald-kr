PacifidlogTown_House5_MapScripts:: @ 8204110
	.byte 0

PacifidlogTown_House5_EventScript_MirageIslandWatcher:: @ 8204111
	lock
	faceplayer
	specialvar VAR_RESULT, IsMirageIslandPresent
	compare VAR_RESULT, TRUE
	goto_if_eq PacifidlogTown_House5_EventScript_MirageIslandPresent
	msgbox PacifidlogTown_House5_Text_CantSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_MirageIslandPresent:: @ 820412D
	msgbox PacifidlogTown_House5_Text_CanSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_Gentleman:: @ 8204137
	msgbox PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather, MSGBOX_NPC
	end

PacifidlogTown_House5_Text_CantSeeMirageIslandToday: @ 8204140
	.string "오늘은 환상섬이 보이지 않는구먼...$"
	// きょうは マボロシじま みえんのう……

PacifidlogTown_House5_Text_CanSeeMirageIslandToday: @ 8204161
	.string "이 이럴 수가!\n"
	.string "오늘은 환상섬이 보이는구먼!$"
	// なっ なんと!ｎ
	// きょうは マボロシじま みえるのじゃ!

PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather: @ 820418B
	.string "환상섬...\n"
	.string "아마도 신기루 때문에\l"
	.string "보였다 안 보였다 하는 것 같군\p"
	.string "아니 어쩌면 진짜로\n"
	.string "나타났다 사라졌다 하는 건가...?$"
	// マボロシじま……ｎ
	// おそらく しんきろうの かんけいでｌ
	// みえたり みえなかったり するんだろうｐ
	// いや ひょっとしたら ほんとうにｎ
	// あらわれたり きえたり しているのか……?

