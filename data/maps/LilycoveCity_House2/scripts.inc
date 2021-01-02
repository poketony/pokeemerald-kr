LilycoveCity_House2_MapScripts:: @ 821ED74
	.byte 0

LilycoveCity_House2_EventScript_FatMan:: @ 821ED75
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM44, LilycoveCity_House2_EventScript_ReceivedRest
	msgbox LilycoveCity_House2_Text_NotAwakeYetHaveThis, MSGBOX_DEFAULT
	giveitem ITEM_TM44
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM44
	msgbox LilycoveCity_House2_Text_SleepIsEssential, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House2_EventScript_ReceivedRest:: @ 821EDAC
	msgbox LilycoveCity_House2_Text_SleepIsEssential, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House2_Text_NotAwakeYetHaveThis: @ 821EDB6
	.string "음냐음냐...\p"
	.string "나 지금 잠이 덜 깼으니까\n"
	.string "이거 줄게...$"

LilycoveCity_House2_Text_SleepIsEssential: @ 821EDF9
	.string "음냐음냐...\p"
	.string "잘 자는 아이는 건강하게 큰다고...\n"
	.string "자면 HP도 회복되고...$"
