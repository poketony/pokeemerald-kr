AbandonedShip_Rooms_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms_1F_EventScript_Gentleman::
	msgbox AbandonedShip_Rooms_1F_Text_TakingALookAround, MSGBOX_NPC
	end

AbandonedShip_Rooms_1F_EventScript_Demetrius::
	trainerbattle_single TRAINER_DEMETRIUS, AbandonedShip_Rooms_1F_Text_DemetriusIntro, AbandonedShip_Rooms_1F_Text_DemetriusDefeat
	msgbox AbandonedShip_Rooms_1F_Text_DemetriusPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_EventScript_Thalia::
	trainerbattle_single TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaIntro, AbandonedShip_Rooms_1F_Text_ThaliaDefeat, AbandonedShip_Rooms_1F_EventScript_RegisterThalia
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AbandonedShip_Rooms_1F_EventScript_ThaliaRematch
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms_1F_EventScript_RegisterThalia::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_THALIA_1
	release
	end

AbandonedShip_Rooms_1F_EventScript_ThaliaRematch::
	trainerbattle_rematch TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro, AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_Text_TakingALookAround:
	.string "이런 장소는 희귀하니\n"
	.string "견학을 하고 있다네\p"
	.string "흠흠...\n"
	.string "다른 방도 있는 것 같군$"

AbandonedShip_Rooms_1F_Text_ThaliaIntro:
	.string "여기서 뭐 하는 거지?\n"
	.string "호기심이 많은 아이구나!$"

AbandonedShip_Rooms_1F_Text_ThaliaDefeat:
	.string "호기심도 많고 강하잖아...$"

AbandonedShip_Rooms_1F_Text_ThaliaPostBattle:
	.string "문 옆에 계신 신사분...\p"
	.string "견학하러 왔다곤 하는데\n"
	.string "아무래도 꿍꿍이가 있는 것 같아$"

AbandonedShip_Rooms_1F_Text_ThaliaRegister:
	.string "넌 정말 강한 트레이너구나!\n"
	.string "기념으로 등록해줘!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro:
	.string "여기서 또 뭐 하는 거지?\n"
	.string "여전히 호기심이 많은 아이구나!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat:
	.string "여전히 호기심도 많고 강하잖아$"

AbandonedShip_Rooms_1F_Text_ThaliaPostRematch:
	.string "저 신사분 확실히 꿍꿍이가 있어!\n"
	.string "너무 수상하게 행동한다니까!$"

AbandonedShip_Rooms_1F_Text_DemetriusIntro:
	.string "으악!\n"
	.string "걸렸다! ...응?$"

AbandonedShip_Rooms_1F_Text_DemetriusDefeat:
	.string "우리 엄마가 아니잖아$"

AbandonedShip_Rooms_1F_Text_DemetriusPostBattle:
	.string "사고 쳐서 도망쳐온 거니까\n"
	.string "우리 엄마한테는 비밀이야$"
