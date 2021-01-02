RustboroCity_Flat2_3F_MapScripts:: @ 8216116
	.byte 0

RustboroCity_Flat2_3F_EventScript_DevonEmployee:: @ 8216117
	msgbox RustboroCity_Flat2_3F_Text_PresidentCollectsRareStones, MSGBOX_NPC
	end

RustboroCity_Flat2_3F_EventScript_Woman:: @ 8216120
	msgbox RustboroCity_Flat2_3F_Text_PresidentsSonAlsoCollectsRareStones, MSGBOX_NPC
	end

RustboroCity_Flat2_3F_Text_PresidentCollectsRareStones: @ 8216129
	.string "데봉의 사장님은\n"
	.string "희귀한 돌을 모으는 게\l"
	.string "취미시지$"

RustboroCity_Flat2_3F_Text_PresidentsSonAlsoCollectsRareStones: @ 8216159
	.string "아마 아드님도\n"
	.string "희귀한 돌을 모으는 게\l"
	.string "취미였을걸...?$"

