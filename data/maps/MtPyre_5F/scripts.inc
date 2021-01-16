MtPyre_5F_MapScripts:: @ 8231C6D
	.byte 0

@ Seems like the scripts for the 4F and 5F were swapped

MtPyre_4F_EventScript_Tasha:: @ 8231C6E
	trainerbattle_single TRAINER_TASHA, MtPyre_4F_Text_TashaIntro, MtPyre_4F_Text_TashaDefeat
	msgbox MtPyre_4F_Text_TashaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_4F_Text_TashaIntro: @ 8231C85
	.string "무서운 게 좋아서...\n"
	.string "너무너무 좋아서 참을 수가 없어...\p"
	.string "난 여기에 있으면\n"
	.string "무서워서 떨려...$"

MtPyre_4F_Text_TashaDefeat: @ 8231CDB
	.string "지는 건 싫어...$"

MtPyre_4F_Text_TashaPostBattle: @ 8231CEE
	.string "무서운 걸 보고 싶어서\n"
	.string "여기서 떠날 수 없어...\p"
	.string "저기...\n"
	.string "너도 같이 있을래...?$"

