MossdeepCity_GameCorner_1F_MapScripts:: @ 8224B27
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MossdeepCity_GameCorner_1F_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MossdeepCity_GameCorner_1F_OnWarp
	map_script MAP_SCRIPT_ON_LOAD, CableClub_OnLoad
	.byte 0

MossdeepCity_GameCorner_1F_OnWarp: @ 8224B37
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_CheckTurnAttendant
	.2byte 0

MossdeepCity_GameCorner_1F_OnFrame: @ 8224B41
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_ExitMinigameRoom
	.2byte 0

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_InfoMan:: @ 8224B4B
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_InfoMan2
	release
	end

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_OldMan:: @ 8224B54
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_OldMan2
	release
	end


@ Everything below is leftover from RS
@ The house that was here in RS was moved to Sootopolis and replaced by the Game Corner
@ The text below is unused and duplicated in its replacement in Sootopolis City
@ And the BG Door event was moved inaccessibly into a wall

RS_MysteryEventsHouse_EventScript_Door:: @ 8224B5D
	msgbox RS_MysteryEventsHouse_Text_DoorIsLocked, MSGBOX_SIGN
	end

RS_MysteryEventsHouse_Text_OldManGreeting: @ 8224B66
	.string "나도 젊었을 때는\n"
	.string "포켓몬 트레이너로서\l"
	.string "전 세계를 여행했었지\p"
	.string "할아버지가 되어 버린 지금은\n"
	.string "젊은 트레이너의 승부를 보는 게\l"
	.string "유일한 낙이라네$"

RS_MysteryEventsHouse_Text_DoorIsLocked: @ 8224BFD
	.string "문이 잠겨 있는 것 같다!$"

RS_MysteryEventsHouse_Text_ChallengeVisitingTrainer: @ 8224C1C
	.string "지금 {STR_VAR_1}{K_I}라는 트레이너가\n"
	.string "내 집에 와 있네!\p"
	.string "{STR_VAR_1}{K_WAGWA} 승부하지 않겠나?$"

RS_MysteryEventsHouse_Text_YouWontBattle: @ 8224C64
	.string "승부하지 않는 겐가...\n"
	.string "승부를 볼 수 없어서 실망이구먼...$"

RS_MysteryEventsHouse_Text_KeepItToA3On3: @ 8224CA4
	.string "오오 그래그래!\p"
	.string "헌데 이 집은\n"
	.string "그다지 튼튼하지 않으니까\p"
	.string "많아도 3대3\n"
	.string "승부로 해 주지 않겠나?$"

RS_MysteryEventsHouse_Text_SaveYourProgress: @ 8224D0B
	.string "그럼 승부 전에\n"
	.string "리포트를 해 두는 편이 좋네$"

RS_MysteryEventsHouse_Text_HopeToSeeAGoodMatch: @ 8224D41
	.string "좋은 승부를 기대하고 있겠네!$"

RS_MysteryEventsHouse_Text_BattleTie: @ 8224D5D
	.string "무승부였나!\p"
	.string "서로 한방도 용납하지 않는\n"
	.string "굉장한 승부였다네!$"

RS_MysteryEventsHouse_Text_BattleWon: @ 8224DB7
	.string "훌륭했네!\p"
	.string "마치 내 젊은 시절을\n"
	.string "보는 것 같구먼!$"

RS_MysteryEventsHouse_Text_BattleLost: @ 8224DFF
	.string "유감이구먼\n"
	.string "하지만 좋은 승부였네!\l"
	.string "다음 번은 이기면 좋겠구먼!$"
