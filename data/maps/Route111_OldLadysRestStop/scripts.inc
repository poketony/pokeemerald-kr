Route111_OldLadysRestStop_MapScripts:: @ 822A916
	map_script MAP_SCRIPT_ON_TRANSITION, Route111_OldLadysRestStop_OnTransition
	.byte 0

Route111_OldLadysRestStop_OnTransition: @ 822A91C
	setflag FLAG_LANDMARK_OLD_LADY_REST_SHOP
	end

Route111_OldLadysRestStop_EventScript_OldLady:: @ 822A920
	lock
	faceplayer
	msgbox Route111_OldLadysRestStop_Text_RestUpHere, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route111_OldLadysRestStop_EventScript_Rest
	compare VAR_RESULT, NO
	goto_if_eq Route111_OldLadysRestStop_EventScript_DeclineRest
	end

Route111_OldLadysRestStop_EventScript_Rest:: @ 822A941
	msgbox Route111_OldLadysRestStop_Text_TakeYourTimeRestUp, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox Route111_OldLadysRestStop_Text_StillTiredTakeAnotherRest, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route111_OldLadysRestStop_EventScript_Rest
	compare VAR_RESULT, NO
	goto_if_eq Route111_OldLadysRestStop_EventScript_DeclineRest
	end

Route111_OldLadysRestStop_EventScript_DeclineRest:: @ 822A96E
	msgbox Route111_OldLadysRestStop_Text_DontNeedToBeShy, MSGBOX_DEFAULT
	release
	end

Route111_OldLadysRestStop_Text_RestUpHere: @ 822A978
	.string "아니 아니 자네의 포켓몬\n"
	.string "지쳐 있는 것 같구먼\p"
	.string "괜찮으면 쉬었다가 가시게나!\n"
	.string "그래! 쉴 땐 쉬어야지!$"

Route111_OldLadysRestStop_Text_TakeYourTimeRestUp: @ 822A9EC
	.string "그래그래\n"
	.string "여기서 푹 쉬고 가시게!$"

Route111_OldLadysRestStop_Text_StillTiredTakeAnotherRest: @ 822AA16
	.string "아니 아니\n"
	.string "아직 지쳐 있구먼?\p"
	.string "좀 더 쉬었다 가시게나!\n"
	.string "그래! 쉴 땐 쉬어야지!$"

Route111_OldLadysRestStop_Text_DontNeedToBeShy: @ 822AA8F
	.string "그려...?\n"
	.string "정말 괜찮은 겐가?\l"
	.string "사양 말게나$"

