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
	.string "You're a POKéMON TRAINER, aren't you?\p"
	.string "SOOTOPOLIS's JUAN has many fans.\n"
	.string "Even more than his student WALLACE!\p"
	.string "Do you have any?$"

SootopolisCity_House3_Text_YouMustBePrettyStrong: @ 8226C20
	.string "흐-응\n"
	.string "그럼 꽤 강하신가 보군요?!$"

SootopolisCity_House3_Text_LonesomeTryWorkingHarder: @ 8226C44
	.string "어머머...\n"
	.string "그건 좀 슬프네요\p"
	.string "팬이 많이 생기도록 열심히 해보세요!$"

SootopolisCity_House3_Text_TrainerFanClubWasWild: @ 8226C9C
	.string "Dedicated fans come over from even\n"
	.string "outside of HOENN.\p"
	.string "It was really wild when I went to the\n"
	.string "TRAINER FAN CLUB in LILYCOVE.$"

