AbandonedShip_Rooms2_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms2_1F_EventScript_Dan::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanIntro, AbandonedShip_Rooms2_1F_Text_DanDefeat, AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterDan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AbandonedShip_Rooms2_1F_EventScript_DanRematch
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterDan::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT 
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_DanRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanRematchIntro, AbandonedShip_Rooms2_1F_Text_DanRematchDefeat, AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Kira::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraIntro, AbandonedShip_Rooms2_1F_Text_KiraDefeat, AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterKira
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AbandonedShip_Rooms2_1F_EventScript_KiraRematch
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterKira::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_KiraRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraRematchIntro, AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat, AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Jani::
	trainerbattle_single TRAINER_JANI, AbandonedShip_Rooms2_1F_Text_JaniIntro, AbandonedShip_Rooms2_1F_Text_JaniDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_JaniPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Garrison::
	trainerbattle_single TRAINER_GARRISON, AbandonedShip_Rooms2_1F_Text_GarrisonIntro, AbandonedShip_Rooms2_1F_Text_GarrisonDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_Text_DanIntro:
	.string "중문: 보물을 찾고 있었더니\n"
	.string "트레이너를 발견!$"

AbandonedShip_Rooms2_1F_Text_DanDefeat:
	.string "중문: 보물을 찾고 있었더니\n"
	.string "트레이너를 발견!$"

AbandonedShip_Rooms2_1F_Text_DanPostBattle:
	.string "중문: 여기에 있다는 소문을 들었는데\n"
	.string "보물을 찾을 수 없네...\l"
	.string "벌써 누가 가져간 거 아닌가?$"

AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons:
	.string "중문: 포켓몬 2마리가 없구나\n"
	.string "그럼 우리를 이길 수 없어!$"

AbandonedShip_Rooms2_1F_Text_KiraIntro:
	.string "소영: 어머? 보물을 찾고 있었는데\n"
	.string "트레이너를 발견했어요!$"

AbandonedShip_Rooms2_1F_Text_KiraDefeat:
	.string "소영: 강하군요!$"

AbandonedShip_Rooms2_1F_Text_KiraPostBattle:
	.string "소영: 이런 낡은 장소에 있는\n"
	.string "보물이란 무엇일까요?\l"
	.string "어쨌든 뭘 살지 정하고 있어요$"

AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons:
	.string "소영: 어머?\n"
	.string "포켓몬 2마리가 아니군요?\l"
	.string "그럼 승부는 다음에 해야겠네요!$"

AbandonedShip_Rooms2_1F_Text_KiraRegister:
	.string "소영: 당신, 사람 짜증나게 하는 데\n"
	.string "재능이 있군요\p"
	.string "그러니 절 포켓내비에\n"
	.string "등록해 주셔야겠어요$"

AbandonedShip_Rooms2_1F_Text_DanRematchIntro:
	.string "중문: 계속 보물을 찾다 보니\n"
	.string "포켓몬도 강해졌다고-!\p"
	.string "잠깐 상대해 줘$"

AbandonedShip_Rooms2_1F_Text_DanRematchDefeat:
	.string "중문: 변함없이 강하군!$"

AbandonedShip_Rooms2_1F_Text_DanPostRematch:
	.string "중문: 보물도 못 찾겠고\n"
	.string "포켓몬 승부도 져버렸으니\l"
	.string "이제 집에 돌아가고 싶다\p"
	.string "하지만 그런 말을 하면\n"
	.string "여자친구가 화를 내니까...$"

AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons:
	.string "중문: 포켓몬 2마리가 없구나\n"
	.string "그럼 우리를 이길 수 없어!$"

AbandonedShip_Rooms2_1F_Text_KiraRematchIntro:
	.string "소영: 어머? 또 만났군요?!\n"
	.string "우리처럼 포기하지 않고\l"
	.string "보물을 찾고 있나보죠?!\p"
	.string "승부해서 진 쪽이\n"
	.string "먼저 포기하는 걸로 하지 않을래요?$"

AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat:
	.string "소영: 또 져버렸어...$"

AbandonedShip_Rooms2_1F_Text_KiraPostRematch:
	.string "소영: 더욱 포켓몬을 키워서\p"
	.string "보물을 찾아낼 때까지\n"
	.string "돌아가지 않을 거예요!$"

AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons:
	.string "소영: 어머?\n"
	.string "포켓몬 2마리가 아니군요?\l"
	.string "그럼 승부는 다음에 해야겠네요!$"

AbandonedShip_Rooms2_1F_Text_JaniIntro:
	.string "난 수영은 잘 못하지만\n"
	.string "포켓몬 배틀은 잘하지!$"

AbandonedShip_Rooms2_1F_Text_JaniDefeat:
	.string "이런\n"
	.string "포켓몬 배틀도 못하잖아$"

AbandonedShip_Rooms2_1F_Text_JaniPostBattle:
	.string "이 배에서\n"
	.string "맨발로 돌아다니는 건 좀 그래$"

AbandonedShip_Rooms2_1F_Text_GarrisonIntro:
	.string "강인함과 상대를 향한 배려...\n"
	.string "그게 트레이너의 보물이다!$"

AbandonedShip_Rooms2_1F_Text_GarrisonDefeat:
	.string "넌 이미\n"
	.string "알고 있는 듯하구나$"

AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle:
	.string "이 배의 한 선원실에서\n"
	.string "반짝거리는 물건을 본 것 같은데$"
