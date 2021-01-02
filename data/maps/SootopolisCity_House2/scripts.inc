SootopolisCity_House2_MapScripts:: @ 8226A76
	.byte 0

SootopolisCity_House2_EventScript_ExpertF:: @ 8226A77
	lock
	faceplayer
	msgbox SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs, MSGBOX_YESNO
	compare VAR_RESULT, YES
	call_if_eq SootopolisCity_House2_EventScript_KnowAboutOrbs
	compare VAR_RESULT, NO
	call_if_eq SootopolisCity_House2_EventScript_DontKnowAboutOrbs
	release
	end

SootopolisCity_House2_EventScript_KnowAboutOrbs:: @ 8226A99
	msgbox SootopolisCity_House2_Text_YesTwoOrbsSideBySide, MSGBOX_DEFAULT
	return

SootopolisCity_House2_EventScript_DontKnowAboutOrbs:: @ 8226AA2
	msgbox SootopolisCity_House2_Text_OughtToVisitAndSee, MSGBOX_DEFAULT
	return

SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs: @ 8226AAB
	.string "송화산...\p"
	.string "정상에 두 개의 구슬이\n"
	.string "놓여져 있다는 걸 알고 계신지...?$"

SootopolisCity_House2_Text_YesTwoOrbsSideBySide: @ 8226AF1
	.string "그래요...\p"
	.string "두 개의 구슬이 이웃한 모습은\n"
	.string "뭔가 마음이 편해지지요...$"

SootopolisCity_House2_Text_OughtToVisitAndSee: @ 8226B41
	.string "그렇군요...\n"
	.string "한번 가보는 건 어떨까요...$"

