LilycoveCity_CoveLilyMotel_2F_MapScripts:: @ 82186D2
	.byte 0

LilycoveCity_CoveLilyMotel_2F_EventScript_GameDesigner:: @ 82186D3
	lock
	faceplayer
	call_if_unset FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex
	call_if_set FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	specialvar VAR_RESULT, HasAllHoennMons
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex:: @ 82186F9
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex, MSGBOX_DEFAULT
	return

LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare:: @ 8218702
	setflag FLAG_TEMP_2
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	goto LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma:: @ 821870F
	message LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	special Special_ShowDiploma
	waitstate
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Programmer:: @ 8218720
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GraphicArtist:: @ 8218729
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_FatMan:: @ 8218732
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Woman:: @ 821873B
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GameBoyKid:: @ 8218744
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Scott:: @ 821874D
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_IN_LILYCOVE, LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_IN_LILYCOVE
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott:: @ 821876A
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy, MSGBOX_DEFAULT
	release
	end

LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex: @ 8218774
	.string "저는 게임 디자이너입니다\p"
	.string "헤에-\n"
	.string "포켓몬 도감 채우고 계시는 군요?\p"
	.string "전부 모으는 건\n"
	.string "어렵겠지만 힘내세요!\p"
	.string "혹시 전부 채우신다면 알려주세요!$"

LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis: @ 821881C
	.string "대단하네요-!\n"
	.string "이야- 당신 대단해요!!\p"
	.string "이 포켓몬 도감\n"
	.string "전부 채워져 있네요!\l"
	.string "그만큼 포켓몬을 사랑하는 거군요!\p"
	.string "감동했습니다!\n"
	.string "표창하게 해 주세요!$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer: @ 82188D6
	.string "이 몸?\p"
	.string "프로그래머라고! 이쪽의\n"
	.string "슬롯은 왠지 즐겁네!$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist: @ 821892B
	.string "나는 그래픽 담당!\n"
	.string "호연의 포켓몬은 재미있지$"

LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute: @ 821896C
	.string "튜브걸 너무 귀엽지 않아?\n"
	.string "그 튜브걸과 승부할 수 있다니...\p"
	.string "우와-! 정말 최고야!\p"
	.string "쌍둥이도 무지 귀엽지!\n"
	.string "그런 쌍둥이와 2대2로\l"
	.string "승부할 수 있다니...\p"
	.string "이야-! 정말 최고야!$"

LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart: @ 8218A21
	.string "바닷바람이 상쾌해서\n"
	.string "기분이 좋아요!$"

LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy: @ 8218A5B
	.string "언제 어디서든 대전이나 승부를\n"
	.string "받을지 모르니까\p"
	.string "게임보이 어드밴스는\n"
	.string "놓고 나갈 수 없지!$"

LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles: @ 8218ACF
	.string "SCOTT: … … … … …\n"
	.string "… … … … … Zzz…\p"
	.string "… … … … … Huh?!\n"
	.string "Oh, sorry, sorry! I was snoozing!\p"
	.string "I came to check out this POKéMON\n"
	.string "CONTEST thing.\p"
	.string "I have to admit, it does look quite\n"
	.string "entertaining, but…\p"
	.string "Consider me a purist--I prefer\n"
	.string "battles and tough TRAINERS.\p"
	.string "But that's just me.\p"
	.string "{PLAYER}{KUN}, I hope you'll enjoy everything\n"
	.string "like the GYMS, CONTESTS, BATTLE TENT,\l"
	.string "the whole works!$"

LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy: @ 8218C33
	.string "SCOTT: I think it does take strategy\n"
	.string "to win a CONTEST.\p"
	.string "Devising CONTEST strategies is one way\n"
	.string "of becoming a better TRAINER, I'd say.$"

