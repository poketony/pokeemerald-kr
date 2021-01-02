.set LOCALID_COLE, 2
.set LOCALID_GERALD, 3
.set LOCALID_AXLE, 4
.set LOCALID_DANIELLE, 5

LavaridgeTown_Gym_1F_MapScripts:: @ 81FE6F4
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_Gym_1F_OnTransition
	.byte 0

LavaridgeTown_Gym_1F_OnTransition: @ 81FE6FA
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	call LavaridgeTown_Gym_1F_EventScript_CheckHideTrainers
	end

@ Unclear where/if these temp vars are getting checked
LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars:: @ 81FE705
	setvar VAR_TEMP_B, 0
	setvar VAR_TEMP_C, 0
	setvar VAR_TEMP_D, 0
	setvar VAR_TEMP_E, 0
	setvar VAR_TEMP_F, 0
	goto_if_defeated TRAINER_COLE LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar
	setvar VAR_TEMP_B, 1
LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar:: @ 81FE72C
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar
	setvar VAR_TEMP_C, 1
LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar:: @ 81FE73A
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar
	setvar VAR_TEMP_D, 1
LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar:: @ 81FE748
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars
	setvar VAR_TEMP_E, 1
LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars:: @ 81FE756
	return

LavaridgeTown_Gym_1F_EventScript_CheckHideTrainers:: @ 81FE757
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_CheckHideGerald
	setobjectmovementtype LOCALID_COLE, MOVEMENT_TYPE_HIDDEN
LavaridgeTown_Gym_1F_EventScript_CheckHideGerald:: @ 81FE764
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_CheckHideAxle
	setobjectmovementtype LOCALID_GERALD, MOVEMENT_TYPE_HIDDEN
LavaridgeTown_Gym_1F_EventScript_CheckHideAxle:: @ 81FE771
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_CheckHideDanielle
	setobjectmovementtype LOCALID_AXLE, MOVEMENT_TYPE_HIDDEN
LavaridgeTown_Gym_1F_EventScript_CheckHideDanielle:: @ 81FE77E
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndCheckHideTrainers
	setobjectmovementtype LOCALID_DANIELLE, MOVEMENT_TYPE_HIDDEN
LavaridgeTown_Gym_1F_EventScript_EndCheckHideTrainers:: @ 81FE78B
	return

LavaridgeTown_Gym_1F_EventScript_Flannery:: @ 81FE78C
	trainerbattle_single TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryIntro, LavaridgeTown_Gym_1F_Text_FlanneryDefeat, LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq LavaridgeTown_Gym_1F_EventScript_FlanneryRematch
	goto_if_unset FLAG_RECEIVED_TM50, LavaridgeTown_Gym_1F_EventScript_GiveOverheat2
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostBattle, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated:: @ 81FE7C1
	message LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_WHITEOUT_TO_LAVARIDGE
	setflag FLAG_DEFEATED_LAVARIDGE_GYM
	setflag FLAG_BADGE04_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	compare VAR_PETALBURG_GYM_STATE, 6
	call_if_eq Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 4
	call Common_EventScript_SetGymTrainers
	setflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	setvar VAR_LAVARIDGE_TOWN_STATE, 1
	call LavaridgeTown_Gym_1F_EventScript_GiveOverheat
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox LavaridgeTown_Gym_1F_Text_RegisteredFlannery, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_FLANNERY_MATCH_CALL
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat2:: @ 81FE81D
	giveitem ITEM_TM50
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM50
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat:: @ 81FE841
	giveitem ITEM_TM50
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_BagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM50
	return

LavaridgeTown_Gym_1F_EventScript_FlanneryRematch:: @ 81FE864
	trainerbattle_rematch_double TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryPreRematch, LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat, LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostRematch, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Cole:: @ 81FE87F
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_COLE, LOCALID_COLE, LavaridgeTown_Gym_1F_Text_ColeIntro, LavaridgeTown_Gym_1F_Text_ColeDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_ColePostBattle MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_EventScript_CheckTrainerScript:: @ 81FE89A
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	release
	special ShouldTryGetTrainerScript
	compare VAR_RESULT, 1
	goto_if_eq EventScript_GotoTrainerScript
	end

LavaridgeTown_Gym_1F_EventScript_Axle:: @ 81FE8AF
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_AXLE, LOCALID_AXLE, LavaridgeTown_Gym_1F_Text_AxleIntro, LavaridgeTown_Gym_1F_Text_AxleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_AxlePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Keegan:: @ 81FE8CA
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_KEEGAN, LOCALID_KEEGAN, LavaridgeTown_Gym_B1F_Text_KeeganIntro, LavaridgeTown_Gym_B1F_Text_KeeganDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_KeeganPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Danielle:: @ 81FE8E5
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_DANIELLE, LOCALID_DANIELLE, LavaridgeTown_Gym_1F_Text_DanielleIntro, LavaridgeTown_Gym_1F_Text_DanielleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_DaniellePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Gerald:: @ 81FE900
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_GERALD, LOCALID_GERALD, LavaridgeTown_Gym_1F_Text_GeraldIntro, LavaridgeTown_Gym_1F_Text_GeraldDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_GeraldPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jace:: @ 81FE91B
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_JACE, LOCALID_JACE, LavaridgeTown_Gym_B1F_Text_JaceIntro, LavaridgeTown_Gym_B1F_Text_JaceDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_JacePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jeff:: @ 81FE936
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_JEFF, LOCALID_JEFF, LavaridgeTown_Gym_B1F_Text_JeffIntro, LavaridgeTown_Gym_B1F_Text_JeffDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_JeffPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Eli:: @ 81FE951
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_ELI, LOCALID_ELI, LavaridgeTown_Gym_B1F_Text_EliIntro, LavaridgeTown_Gym_B1F_Text_EliDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_EliPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_GymGuide:: @ 81FE96C
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory
	msgbox LavaridgeTown_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory:: @ 81FE981
	msgbox LavaridgeTown_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_LeftGymStatue:: @ 81FE98B
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_RightGymStatue:: @ 81FE99B
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_GymStatueCertified:: @ 81FE9AB
	msgbox LavaridgeTown_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_EventScript_GymStatue:: @ 81FE9B5
	msgbox LavaridgeTown_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_Text_GymGuideAdvice: @ 81FE9BF
	.string "잘 있었나!!\n"
	.string "챔피언을 목표로 하는 {PLAYER}!!\p"
	.string "용암마을 체육관 관장 민지는\n"
	.string "불꽃타입 포켓몬 사용자다!\p"
	.string "포켓몬에 대한 정열은\n"
	.string "화산보다 격렬하고 뜨겁다!\p"
	.string "잘못해서 가까이라도 가면\n"
	.string "화상 입으니 물로 식히면서\l"
	.string "힘내라-구!!$"

LavaridgeTown_Gym_1F_Text_GymGuidePostVictory: @ 81FEAB8
	.string "아이고- 뜨거운 배틀이었다!$"

LavaridgeTown_Gym_1F_Text_ColeIntro: @ 81FEADE
	.string "아뜨뜨뜨뜨뜨거!\n"
	.string "으아-! 뜨거웠어-!$"

LavaridgeTown_Gym_1F_Text_ColeDefeat: @ 81FEAFB
	.string "눈에 땀방울이 들어갔어...$"

LavaridgeTown_Gym_1F_Text_ColePostBattle: @ 81FEB1C
	.string "목욕은 혈액순환을 도우니까\n"
	.string "관절 통증에 효과적이야!$"

LavaridgeTown_Gym_1F_Text_AxleIntro: @ 81FEB7B
	.string "내 소중한 스트레스 해소 시간을\n"
	.string "방해하지 마-!$"

LavaridgeTown_Gym_1F_Text_AxleDefeat: @ 81FEBC0
	.string "에잇! 민지님에게 져버려랏-!$"

LavaridgeTown_Gym_1F_Text_AxlePostBattle: @ 81FEBE1
	.string "하아... 후...\p"
	.string "목욕을 오래 하고 있으면\n"
	.string "꽤 피곤해져...$"

LavaridgeTown_Gym_B1F_Text_KeeganIntro: @ 81FEC31
	.string "너도 이제 슬슬 지친 것 같군?\n"
	.string "목욕하면서 한숨 쉬었다 가고 싶지?\p"
	.string "하지만 기력을 유지하는 것도\n"
	.string "트레이너에게 필요한 능력 중 하나다$"

LavaridgeTown_Gym_B1F_Text_KeeganDefeat: @ 81FECE3
	.string "불장난이 부상의 원인인 건가...$"

LavaridgeTown_Gym_B1F_Text_KeeganPostBattle: @ 81FED02
	.string "네 실력은 진짜다...\n"
	.string "하지만 체육관 관장인 민지님은\l"
	.string "더 강해!\p"
	.string "방심하면 뜨거운 맛을 보게 될 거다!$"

LavaridgeTown_Gym_1F_Text_GeraldIntro: @ 81FED72
	.string "너의 포켓몬은\n"
	.string "200도의 열기를 이겨낼 수 있는가?!$"

LavaridgeTown_Gym_1F_Text_GeraldDefeat: @ 81FED9E
	.string "다 태워버렸어야 했거늘...$"

LavaridgeTown_Gym_1F_Text_GeraldPostBattle: @ 81FEDBB
	.string "200도의 열기라는 건\n"
	.string "용암의 온도!\p"
	.string "너의 포켓몬은 나를 이겼으니까\n"
	.string "용암 속에서도 문제없겠군!$"

LavaridgeTown_Gym_1F_Text_DanielleIntro: @ 81FEE22
	.string "자-!\n"
	.string "그럼 상대해 줄게!$"

LavaridgeTown_Gym_1F_Text_DanielleDefeat: @ 81FEE42
	.string "어떻게 그렇게 강할 수가 있지?$"

LavaridgeTown_Gym_1F_Text_DaniellePostBattle: @ 81FEE5D
	.string "나도 민지님처럼\n"
	.string "아름답고 강한 트레이너가 될 거야!$"

LavaridgeTown_Gym_B1F_Text_JaceIntro: @ 81FEE9D
	.string "Come on, get with it!\n"
	.string "Let's go before my feelings cool!$"

LavaridgeTown_Gym_B1F_Text_JaceDefeat: @ 81FEED5
	.string "It's so hot, and yet my heart is\n"
	.string "clutched by ice…$"

LavaridgeTown_Gym_B1F_Text_JacePostBattle: @ 81FEF07
	.string "The way the battling spirit burns\n"
	.string "within you, you may stand a chance\l"
	.string "against our LEADER.$"

LavaridgeTown_Gym_B1F_Text_JeffIntro: @ 81FEF60
	.string "See how the flames blaze wildly?\n"
	.string "They flare in anticipation of my win!$"

LavaridgeTown_Gym_B1F_Text_JeffDefeat: @ 81FEFA7
	.string "Something didn't go right.$"

LavaridgeTown_Gym_B1F_Text_JeffPostBattle: @ 81FEFC2
	.string "Well, so what? I say so what?\n"
	.string "I can walk on hot coals barefoot!\p"
	.string "…Don't even think about trying it!$"

LavaridgeTown_Gym_B1F_Text_EliIntro: @ 81FF025
	.string "As much as I love mountains,\n"
	.string "I especially love volcanoes.$"

LavaridgeTown_Gym_B1F_Text_EliDefeat: @ 81FF05F
	.string "Well, it seems to me I lost without\n"
	.string "ever being in control.$"

LavaridgeTown_Gym_B1F_Text_EliPostBattle: @ 81FF09A
	.string "I stay here because I became a fan\n"
	.string "of FLANNERY's power.\p"
	.string "Hehehehe.$"

LavaridgeTown_Gym_1F_Text_FlanneryIntro: @ 81FF0DC
	.string "어서 오세요 ...가 아니라\p"
	.string "여기까지 잘도 왔구나!\p"
	.string "전 여기 체육관 관장을\n"
	.string "맡게 된 ...이 아니라\p"
	.string "체육관 관장을 맡은 민지다!\p"
	.string "끙...\n"
	.string "체육관 관장 된 지 얼마 안 됐다고\l"
	.string "방심하지 말라고!\p"
	.string "할아버지에게 물려받은 재능과\n"
	.string "이 땅에서 갈고닦은 핫한 기술\l"
	.string "너에게 보여주겠어!$"

LavaridgeTown_Gym_1F_Text_FlanneryDefeat: @ 81FF233
	.string "크윽...\n"
	.string "어깨에 힘이 들어가고 말았어...\p"
	.string "나...\n"
	.string "체육관 관장 된 지 얼마 안 됐다고\l"
	.string "좀 무리한 걸까...\p"
	.string "역시 나는 나답게 싸워야지\n"
	.string "그게 아니라면 함께 싸워주는\l"
	.string "포켓몬도 힘들 거야!\p"
	.string "그걸 가르쳐준\n"
	.string "당신에게 이걸 줄게!$"

LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge: @ 81FF32F
	.string "{PLAYER}{K_EUNNEUN} 민지로부터\n"
	.string "히트배지를 받았다!$"

LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis: @ 81FF359
	.string "히트배지가 있으면\n"
	.string "다른 사람에게 받은 포켓몬이라도\l"
	.string "레벨 50까지는\l"
	.string "말을 잘 들어줘!\p"
	.string "그리고 비전기술 괴력을\n"
	.string "사용할 수 있게 돼!\p"
	.string "이건 감사의 마음\n"
	.string "사양하지 말고 받아줘!$"

LavaridgeTown_Gym_1F_Text_ExplainOverheat: @ 81FF45C
	.string "기술머신50에는\n"
	.string "오버히트가 들어 있어!\p"
	.string "그 기술은 상대에게\n"
	.string "큰 데미지를 줘!\p"
	.string "하지만 특수공격이\n"
	.string "크게 떨어지니까\l"
	.string "긴 승부에는 안 맞을지도...\p"
	.string "...... ...... ......$"

LavaridgeTown_Gym_1F_Text_RegisteredFlannery: @ 81FF517
	.string "체육관 관장 민지를\n"
	.string "포켓내비에 등록했다!$"

LavaridgeTown_Gym_1F_Text_FlanneryPostBattle: @ 81FF546
	.string "Your power reminds me of someone…\p"
	.string "Oh! I know! You battle like NORMAN,\n"
	.string "the GYM LEADER of PETALBURG.$"

LavaridgeTown_Gym_1F_Text_GymStatue: @ 81FF5A9
	.string "용암마을 포켓몬체육관$"

LavaridgeTown_Gym_1F_Text_GymStatueCertified: @ 81FF5C4
	.string "용암마을 포켓몬체육관\p"
	.string "민지 인정 트레이너!\n"
	.string "{PLAYER}$"

LavaridgeTown_Gym_1F_Text_FlanneryPreRematch: @ 81FF601
	.string "FLANNERY: Losing a battle isn't going\n"
	.string "to deflate me.\p"
	.string "I love POKéMON.\n"
	.string "I love to battle.\l"
	.string "And… I love this GYM!\p"
	.string "Let's exchange superhot moves\n"
	.string "in another battle!$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat: @ 81FF69F
	.string "Whew!\n"
	.string "On the verge of eruption!$"

LavaridgeTown_Gym_1F_Text_FlanneryPostRematch: @ 81FF6BF
	.string "FLANNERY: I lost the match,\n"
	.string "but I'm completely satisfied.\p"
	.string "It's not often I get to enjoy a battle\n"
	.string "this heated.\p"
	.string "Let's have another one like this\n"
	.string "again sometime!$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons: @ 81FF75E
	.string "FLANNERY: Losing a battle isn't going\n"
	.string "to deflate me.\p"
	.string "I love POKéMON.\n"
	.string "I love to battle.\l"
	.string "And… I love this GYM!\p"
	.string "Let's exchange superhot moves\n"
	.string "in another battle!\p"
	.string "Oh, wait. Do you only have one POKéMON\n"
	.string "that can battle?\p"
	.string "I hate to say this, but when you come\n"
	.string "see me, bring at least two POKéMON.$"
