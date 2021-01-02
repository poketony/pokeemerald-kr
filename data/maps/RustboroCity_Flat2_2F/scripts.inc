RustboroCity_Flat2_2F_MapScripts:: @ 8215FD7
	.byte 0

RustboroCity_Flat2_2F_EventScript_OldMan:: @ 8215FD8
	msgbox RustboroCity_Flat2_2F_Text_DevonWasTinyInOldDays, MSGBOX_NPC
	end

RustboroCity_Flat2_2F_EventScript_NinjaBoy:: @ 8215FE1
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_PREMIER_BALL_RUSTBORO, RustboroCity_Flat2_2F_EventScript_GavePremierBall
	msgbox RustboroCity_Flat2_2F_Text_MyDaddyMadeThisYouCanHaveIt, MSGBOX_DEFAULT
	giveitem ITEM_PREMIER_BALL
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_PREMIER_BALL_RUSTBORO
	release
	end

RustboroCity_Flat2_2F_EventScript_GavePremierBall:: @ 8216010
	msgbox RustboroCity_Flat2_2F_Text_GoingToWorkAtDevonToo, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat2_2F_Text_DevonWasTinyInOldDays: @ 821601A
	.string "데봉도 말이지 옛날에는\n"
	.string "작고 작은 회사였어$"

RustboroCity_Flat2_2F_Text_MyDaddyMadeThisYouCanHaveIt: @ 821605A
	.string "아빠는 회사에서 일해!\p"
	.string "이거 아빠가 만든 거야!\n"
	.string "하지만 난 아직 쓸 수 없으니까 줄게$"

RustboroCity_Flat2_2F_Text_GoingToWorkAtDevonToo: @ 82160BD
	.string "아빠는 회사에서 일해!\p"
	.string "나도 어른이 되면\n"
	.string "데봉에서 일할 거야!$"

