FortreeCity_Gym_MapScripts:: @ 82165AB
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FortreeCity_Gym_OnWarp
	.byte 0

FortreeCity_Gym_OnTransition: @ 82165B6
	special RotatingGate_InitPuzzle
	end

FortreeCity_Gym_OnWarp: @ 82165BA
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, FortreeCity_Gym_EventScript_InitRotatingGates
	.2byte 0

FortreeCity_Gym_EventScript_InitRotatingGates:: @ 82165C4
	special RotatingGate_InitPuzzleAndGraphics
	end

FortreeCity_Gym_EventScript_Winona:: @ 82165C8
	trainerbattle_single TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaIntro, FortreeCity_Gym_Text_WinonaDefeat, FortreeCity_Gym_EventScript_WinonaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq FortreeCity_Gym_EventScript_WinonaRematch
	goto_if_unset FLAG_RECEIVED_TM40, FortreeCity_Gym_EventScript_GiveAerialAce2
	msgbox FortreeCity_Gym_Text_WinonaPostBattle, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_WinonaDefeated:: @ 82165FD
	message FortreeCity_Gym_Text_ReceivedFeatherBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_FORTREE_GYM
	setflag FLAG_BADGE06_GET
	setvar VAR_0x8008, 6
	call Common_EventScript_SetGymTrainers
	call FortreeCity_Gym_EventScript_GiveAerialAce
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox FortreeCity_Gym_Text_RegisteredWinona, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WINONA_MATCH_CALL
	setvar VAR_SCOTT_FORTREE_CALL_STEP_COUNTER, 0
	setflag FLAG_SCOTT_CALL_FORTREE_GYM
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce2:: @ 8216646
	giveitem ITEM_TM40
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM40
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce:: @ 821666A
	giveitem ITEM_TM40
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_BagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM40
	return

FortreeCity_Gym_EventScript_WinonaRematch:: @ 821668D
	trainerbattle_rematch_double TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaPreRematch, FortreeCity_Gym_Text_WinonaRematchDefeat, FortreeCity_Gym_Text_WinonaRematchNeedTwoMons
	msgbox FortreeCity_Gym_Text_WinonaPostRematch, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Jared:: @ 82166A8
	trainerbattle_single TRAINER_JARED, FortreeCity_Gym_Text_JaredIntro, FortreeCity_Gym_Text_JaredDefeat
	msgbox FortreeCity_Gym_Text_JaredPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Edwardo:: @ 82166BF
	trainerbattle_single TRAINER_EDWARDO, FortreeCity_Gym_Text_EdwardoIntro, FortreeCity_Gym_Text_EdwardoDefeat
	msgbox FortreeCity_Gym_Text_EdwardoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Flint:: @ 82166D6
	trainerbattle_single TRAINER_FLINT, FortreeCity_Gym_Text_FlintIntro, FortreeCity_Gym_Text_FlintDefeat
	msgbox FortreeCity_Gym_Text_FlintPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Ashley:: @ 82166ED
	trainerbattle_single TRAINER_ASHLEY, FortreeCity_Gym_Text_AshleyIntro, FortreeCity_Gym_Text_AshleyDefeat
	msgbox FortreeCity_Gym_Text_AshleyPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Humberto:: @ 8216704
	trainerbattle_single TRAINER_HUMBERTO, FortreeCity_Gym_Text_HumbertoIntro, FortreeCity_Gym_Text_HumbertoDefeat
	msgbox FortreeCity_Gym_Text_HumbertoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Darius:: @ 821671B
	trainerbattle_single TRAINER_DARIUS, FortreeCity_Gym_Text_DariusIntro, FortreeCity_Gym_Text_DariusDefeat
	msgbox FortreeCity_Gym_Text_DariusPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_GymGuide:: @ 8216732
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_FORTREE_GYM, FortreeCity_Gym_EventScript_GymGuidePostVictory
	msgbox FortreeCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_GymGuidePostVictory:: @ 8216747
	msgbox FortreeCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_LeftGymStatue:: @ 8216751
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_RightGymStatue:: @ 8216761
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_GymStatueCertified:: @ 8216771
	msgbox FortreeCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_EventScript_GymStatue:: @ 821677B
	msgbox FortreeCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_Text_GymGuideAdvice: @ 8216785
	.string "잘 있었나!!\n"
	.string "챔피언을 노리는 {PLAYER}!!\p"
	.string "검방울시티 체육관 관장 은송은\n"
	.string "비행타입의 포켓몬을 쓴다!\p"
	.string "이 회전문투성이인\n"
	.string "체육관 안에서\p"
	.string "그녀는 새로운 도전자가\n"
	.string "날아오르길 기다리고 있다!\p"
	.string "그럼 힘내라고-!!$"

FortreeCity_Gym_Text_GymGuidePostVictory: @ 821687D
	.string "해냈구나! 넌 날아올랐어!$"

FortreeCity_Gym_Text_JaredIntro: @ 82168A2
	.string "화려한 새포켓몬의 승부를\n"
	.string "보여주마!$"

FortreeCity_Gym_Text_JaredDefeat: @ 82168D3
	.string "너... 강하군...$"

FortreeCity_Gym_Text_JaredPostBattle: @ 82168E7
	.string "트레이너는 머리 회전도\n"
	.string "빠르지 않으면 안 된다!\p"
	.string "너는 체육관 관장이 있는 곳까지\n"
	.string "무사히 도착할 수 있을까?$"

FortreeCity_Gym_Text_EdwardoIntro: @ 821695A
	.string "새포켓몬을 사랑하는 사람은\n"
	.string "이 체육관을 목표로 삼고 있지!\p"
	.string "검방울체육관의 일원으로서\n"
	.string "패배할 수는 없다!$"

FortreeCity_Gym_Text_EdwardoDefeat: @ 82169C7
	.string "나에겐 너무 큰 짐이었나...!$"

FortreeCity_Gym_Text_EdwardoPostBattle: @ 82169F1
	.string "세계는 넓고\n"
	.string "강한 트레이너도 넘쳐나지\p"
	.string "나도 여기서 계속 수행해서\n"
	.string "강해지겠다!$"

FortreeCity_Gym_Text_FlintIntro: @ 8216A66
	.string "체육관 관장인 은송님이\n"
	.string "손쓰실 필요도 없어!\p"
	.string "네 상대는 나로 충분하다!$"

FortreeCity_Gym_Text_FlintDefeat: @ 8216AC4
	.string "은송님...! 제가 져버렸습니다...!$"

FortreeCity_Gym_Text_FlintPostBattle: @ 8216AD7
	.string "은송님은 귀여운 데다가 강하시다...\n"
	.string "정말 최고의 관장이지!\p"
	.string "...좀 부끄럽군$"

FortreeCity_Gym_Text_AshleyIntro: @ 8216B1A
	.string "은송님의 가르침을 받은 나를!\n"
	.string "그렇게 간단히 쓰러뜨릴 수는 없을걸?$"

FortreeCity_Gym_Text_AshleyDefeat: @ 8216B51
	.string "쓰러졌다...$"

FortreeCity_Gym_Text_AshleyPostBattle: @ 8216B5F
	.string "검방울시티 사람들은\n"
	.string "은송님이 계셔서\l"
	.string "안심하고 지낼 수 있어$"

FortreeCity_Gym_Text_HumbertoIntro: @ 8216B9E
	.string "When WINONA takes to battle, her face\n"
	.string "shines with beautiful determination…\p"
	.string "I'm not letting you witness that\n"
	.string "lovely sight!$"

FortreeCity_Gym_Text_HumbertoDefeat: @ 8216C18
	.string "Urk!\n"
	.string "I couldn't stop you.$"

FortreeCity_Gym_Text_HumbertoPostBattle: @ 8216C32
	.string "You'd better watch it!\n"
	.string "Don't get distracted staring at WINONA\l"
	.string "or you'll go crashing down in a heap!$"

FortreeCity_Gym_Text_DariusIntro: @ 8216C96
	.string "You'd better know that there are all\n"
	.string "sorts of FLYING-type POKéMON.\p"
	.string "You do know that, right?$"

FortreeCity_Gym_Text_DariusDefeat: @ 8216CF2
	.string "You seem to know your stuff!$"

FortreeCity_Gym_Text_DariusPostBattle: @ 8216D0F
	.string "Sure, you beat me all right.\n"
	.string "But you'd better watch it! Our LEADER\l"
	.string "WINONA's POKéMON are all business.$"

FortreeCity_Gym_Text_WinonaIntro: @ 8216D75
	.string "저는 이 검방울시티 체육관에서\n"
	.string "관장을 맡고 있는 은송...\p"
	.string "새포켓몬과 마음을 나누며\n"
	.string "같이 드넓은 하늘을 날아...\p"
	.string "어떠한 괴로운 승부에서도\n"
	.string "우아하게 이겨 보이죠...\p"
	.string "자 저와 포켓몬이 만들어내는\n"
	.string "화려한 춤을 보세요!$"

FortreeCity_Gym_Text_WinonaDefeat: @ 8216E60
	.string "저보다 화려하게\n"
	.string "포켓몬을 다루는 사람은...\l"
	.string "처음 봤어요...\p"
	.string "그 실력을 인정하여\n"
	.string "이 체육관 배지를 드리겠습니다!$"

FortreeCity_Gym_Text_ReceivedFeatherBadge: @ 8216EEC
	.string "{PLAYER}{K_EUNNEUN} 은송에게\n"
	.string "깃털배지를 받았다!$"

FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis: @ 8216F17
	.string "깃털배지를 달고 있으면\n"
	.string "다른 사람에게 받은 포켓몬일지라도\l"
	.string "레벨 70까지의 포켓몬이라면\l"
	.string "명령에 잘 따라줍니다!\p"
	.string "비전기술 공중날기도\n"
	.string "사용할 수 있게 됩니다!\p"
	.string "그리고 이걸\n"
	.string "당신에게 선물하죠$"

FortreeCity_Gym_Text_ExplainAerialAce: @ 8216FEC
	.string "기술머신40의 내용물은\n"
	.string "제비반환!\p"
	.string "그 스피드는...\n"
	.string "어떤 포켓몬도\l"
	.string "피할 수 없겠지요!\p"
	.string "... ... ...$"

FortreeCity_Gym_Text_RegisteredWinona: @ 8217044
	.string "체육관 관장 은송을\n"
	.string "포켓내비에 등록했다!$"

FortreeCity_Gym_Text_WinonaPostBattle: @ 8217071
	.string "당신에게는 져버렸지만\p"
	.string "저는 앞으로도\n"
	.string "새포켓몬만을 사용할 거예요$"

FortreeCity_Gym_Text_GymStatue: @ 82170AE
	.string "검방울시티 포켓몬체육관$"

FortreeCity_Gym_Text_GymStatueCertified: @ 82170C7
	.string "검방울시티 포켓몬체육관\p"
	.string "은송 인정 트레이너!\n"
	.string "{PLAYER}$"

FortreeCity_Gym_Text_WinonaPreRematch: @ 8217100
	.string "WINONA: We humans can never escape\n"
	.string "gravity's pull on the ground.\p"
	.string "But by striving for excellence,\n"
	.string "we have the power to soar!\p"
	.string "You have scaled the pinnacle as\n"
	.string "the reigning CHAMPION.\p"
	.string "Please, allow me to see your power\n"
	.string "at full flight!$"

FortreeCity_Gym_Text_WinonaRematchDefeat: @ 82171E6
	.string "I failed to reach your height again…$"

FortreeCity_Gym_Text_WinonaPostRematch: @ 821720B
	.string "WINONA: Even though I have lost,\n"
	.string "the wings of my heart remain unbroken.\p"
	.string "I can rise and soar again and\n"
	.string "yet again.\p"
	.string "I am convinced of it!$"

FortreeCity_Gym_Text_WinonaRematchNeedTwoMons: @ 8217292
	.string "WINONA: We humans can never escape\n"
	.string "gravity's pull on the ground.\p"
	.string "But by striving for excellence,\n"
	.string "we have the power to soar!\p"
	.string "You have scaled the pinnacle as\n"
	.string "the reigning CHAMPION.\p"
	.string "Please, allow me to see your power\n"
	.string "at full flight!\p"
	.string "Oh, no… Do you have but one\n"
	.string "POKéMON with you?\p"
	.string "Please return with two POKéMON\n"
	.string "at the very least.$"
