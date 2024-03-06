.set LOCALID_CURATOR, 1

LilycoveCity_LilycoveMuseum_2F_MapScripts:: @ 821973A
	map_script MAP_SCRIPT_ON_LOAD, LilycoveCity_LilycoveMuseum_2F_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LilycoveCity_LilycoveMuseum_2F_OnFrame
	.byte 0

LilycoveCity_LilycoveMuseum_2F_OnLoad: @ 8219745
	goto_if_set FLAG_COOL_PAINTING_MADE, LilycoveCity_LilycoveMuseum_2F_EventScript_SetCoolPainting
	goto LilycoveCity_LilycoveMuseum_2F_EventScript_CheckBeautyPainting
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_CheckBeautyPainting:: @ 8219754
	goto_if_set FLAG_BEAUTY_PAINTING_MADE, LilycoveCity_LilycoveMuseum_2F_EventScript_SetBeautyPainting
	goto LilycoveCity_LilycoveMuseum_2F_EventScript_CheckCutePainting
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_CheckCutePainting:: @ 8219763
	goto_if_set FLAG_CUTE_PAINTING_MADE, LilycoveCity_LilycoveMuseum_2F_EventScript_SetCutePainting
	goto LilycoveCity_LilycoveMuseum_2F_EventScript_CheckSmartPainting
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_CheckSmartPainting:: @ 8219772
	goto_if_set FLAG_SMART_PAINTING_MADE, LilycoveCity_LilycoveMuseum_2F_EventScript_SetSmartPainting
	goto LilycoveCity_LilycoveMuseum_2F_EventScript_CheckToughPainting
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_CheckToughPainting:: @ 8219781
	goto_if_set FLAG_TOUGH_PAINTING_MADE, LilycoveCity_LilycoveMuseum_2F_EventScript_SetToughPainting
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_SetCoolPainting:: @ 821978B
	setmetatile 10, 6, METATILE_LilycoveMuseum_Painting2_Left, 1
	setmetatile 11, 6, METATILE_LilycoveMuseum_Painting2_Right, 1
	goto LilycoveCity_LilycoveMuseum_2F_EventScript_CheckBeautyPainting
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_SetBeautyPainting:: @ 82197A3
	setmetatile 18, 6, METATILE_LilycoveMuseum_Painting1_Left, 1
	setmetatile 19, 6, METATILE_LilycoveMuseum_Painting1_Right, 1
	goto LilycoveCity_LilycoveMuseum_2F_EventScript_CheckCutePainting
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_SetCutePainting:: @ 82197BB
	setmetatile 14, 10, METATILE_LilycoveMuseum_Painting3_Left, 1
	setmetatile 15, 10, METATILE_LilycoveMuseum_Painting3_Right, 1
	goto LilycoveCity_LilycoveMuseum_2F_EventScript_CheckSmartPainting
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_SetSmartPainting:: @ 82197D3
	setmetatile 6, 10, METATILE_LilycoveMuseum_Painting0_Left, 1
	setmetatile 7, 10, METATILE_LilycoveMuseum_Painting0_Right, 1
	goto LilycoveCity_LilycoveMuseum_2F_EventScript_CheckToughPainting
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_SetToughPainting:: @ 82197EB
	setmetatile 2, 6, METATILE_LilycoveMuseum_Painting4_Left, 1
	setmetatile 3, 6, METATILE_LilycoveMuseum_Painting4_Right, 1
	end

LilycoveCity_LilycoveMuseum_2F_OnFrame: @ 82197FE
	map_script_2 VAR_LILYCOVE_MUSEUM_2F_STATE, 0, LilycoveCity_LilycoveMuseum_2F_EventScript_ShowExhibitHall
	.2byte 0

LilycoveCity_LilycoveMuseum_2F_EventScript_ShowExhibitHall:: @ 8219808
	lockall
	applymovement LOCALID_CURATOR, Common_Movement_FacePlayer
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_LilycoveMuseum_2F_Movement_PlayerWalkInPlaceLeft
	waitmovement 0
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ThisIsExhibitHall, MSGBOX_SIGN
	applymovement LOCALID_CURATOR, LilycoveCity_LilycoveMuseum_2F_Movement_FaceExhibitHall
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_LilycoveMuseum_2F_Movement_FaceExhibitHall
	waitmovement 0
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ExplainExhibitHall, MSGBOX_SIGN
	applymovement LOCALID_CURATOR, Common_Movement_FacePlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_LilycoveMuseum_2F_Movement_PlayerWalkInPlaceLeft
	waitmovement 0
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_PleaseObtainPaintingsForExhibit, MSGBOX_SIGN
	copyvar VAR_LILYCOVE_MUSEUM_2F_STATE, 1
	releaseall
	end

LilycoveCity_LilycoveMuseum_2F_Movement_PlayerWalkInPlaceLeft: @ 8219861
	walk_in_place_fastest_left
	step_end

LilycoveCity_LilycoveMuseum_2F_Movement_FaceExhibitHall: @ 8219863
	face_up
	delay_16
	step_end

LilycoveCity_LilycoveMuseum_2F_EventScript_Curator:: @ 8219866
	lockall
	goto_if_set FLAG_RECEIVED_GLASS_ORNAMENT, LilycoveCity_LilycoveMuseum_2F_EventScript_ReceivedGlassOrnament
	specialvar VAR_0x8004, CountPlayerContestPaintings
	switch VAR_0x8004
	case 1, LilycoveCity_LilycoveMuseum_2F_EventScript_AddedPainting
	case 2, LilycoveCity_LilycoveMuseum_2F_EventScript_AddedPainting
	case 3, LilycoveCity_LilycoveMuseum_2F_EventScript_AddedPainting
	case 4, LilycoveCity_LilycoveMuseum_2F_EventScript_AddedPainting
	case 5, LilycoveCity_LilycoveMuseum_2F_EventScript_ThankPlayer
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_WishToFillExhibit, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_AddedPainting:: @ 82198BA
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ThanksAddedNewPainting, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_ThankPlayer:: @ 82198C3
	applymovement LOCALID_CURATOR, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ItsYouPlayer, MSGBOX_DEFAULT
	applymovement LOCALID_CURATOR, LilycoveCity_LilycoveMuseum_2F_Movement_FaceExhibitHall
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_PaintingsAttractedMoreGuests, MSGBOX_DEFAULT
	goto LilycoveCity_LilycoveMuseum_2F_EventScript_GiveGlassOrnament
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_GiveGlassOrnament:: @ 82198EA
	applymovement LOCALID_CURATOR, Common_Movement_FacePlayer
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_TokenOfGratitude, MSGBOX_DEFAULT
	givedecoration DECOR_GLASS_ORNAMENT
	compare VAR_RESULT, FALSE
	goto_if_eq LilycoveCity_LilycoveMuseum_2F_EventScript_NoRoomForGlassOrnament
	setflag FLAG_RECEIVED_GLASS_ORNAMENT
	closemessage
	releaseall
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_NoRoomForGlassOrnament:: @ 8219911
	call Common_EventScript_NoRoomForDecor
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_KeepThisForYou, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_ReceivedGlassOrnament:: @ 8219921
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_HonorToHaveYouVisit, MSGBOX_NPC
	releaseall
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_CutePainting:: @ 821992B
	lockall
	goto_if_set FLAG_CUTE_PAINTING_MADE, LilycoveCity_LilycoveMuseum_2F_EventScript_ShowCutePainting
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ItsPinkPictureFrame, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_ToughPainting:: @ 821993E
	lockall
	goto_if_set FLAG_TOUGH_PAINTING_MADE, LilycoveCity_LilycoveMuseum_2F_EventScript_ShowToughPainting
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ItsYellowPictureFrame, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_CoolPainting:: @ 8219951
	lockall
	goto_if_set FLAG_COOL_PAINTING_MADE, LilycoveCity_LilycoveMuseum_2F_EventScript_ShowCoolPainting
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ItsRedPictureFrame, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_BeautyPainting:: @ 8219964
	lockall
	goto_if_set FLAG_BEAUTY_PAINTING_MADE, LilycoveCity_LilycoveMuseum_2F_EventScript_ShowBeautyPainting
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ItsBluePictureFrame, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_SmartPainting:: @ 8219977
	lockall
	goto_if_set FLAG_SMART_PAINTING_MADE, LilycoveCity_LilycoveMuseum_2F_EventScript_ShowSmartPainting
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ItsGreenPictureFrame, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_Girl:: @ 821998A
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_NewPaintingsSurprisedMe, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_ExpertM:: @ 8219993
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_NewPaintingsRatherAmusing, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_RichBoy:: @ 821999C
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ThesePaintingsOfYourPokemon, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_ShowCoolPainting:: @ 82199A5
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ItsPaintingOfPokemon, MSGBOX_SIGN
	fadescreen FADE_TO_BLACK
	showcontestwinner CONTEST_WINNER_MUSEUM_COOL
	releaseall
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_ShowBeautyPainting:: @ 82199B3
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ItsPaintingOfPokemon, MSGBOX_SIGN
	fadescreen FADE_TO_BLACK
	showcontestwinner CONTEST_WINNER_MUSEUM_BEAUTY
	releaseall
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_ShowCutePainting:: @ 82199C1
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ItsPaintingOfPokemon, MSGBOX_SIGN
	fadescreen FADE_TO_BLACK
	showcontestwinner CONTEST_WINNER_MUSEUM_CUTE
	releaseall
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_ShowSmartPainting:: @ 82199CF
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ItsPaintingOfPokemon, MSGBOX_SIGN
	fadescreen FADE_TO_BLACK
	showcontestwinner CONTEST_WINNER_MUSEUM_SMART
	releaseall
	end

LilycoveCity_LilycoveMuseum_2F_EventScript_ShowToughPainting:: @ 82199DD
	msgbox LilycoveCity_LilycoveMuseum_2F_Text_ItsPaintingOfPokemon, MSGBOX_SIGN
	fadescreen FADE_TO_BLACK
	showcontestwinner CONTEST_WINNER_MUSEUM_TOUGH
	releaseall
	end

LilycoveCity_LilycoveMuseum_2F_Text_ThisIsExhibitHall: @ 82199EB
	.string "여기는 특별 전시실입니다$"
	@ ここは とくべつ てんじしつ です

LilycoveCity_LilycoveMuseum_2F_Text_ExplainExhibitHall: @ 8219A0D
	.string "보시는 대로 아직\n"
	.string "그림이 장식되어 있지 않습니다\p"
	.string "여기에는 1층에 있는\n"
	.string "소위 명화 같은 것과는\l"
	.string "다른 그림을 장식하고 싶어요!\p"
	.string "오래된 명화만이\n"
	.string "예술인 게 아니에요!\p"
	.string "이 전시실에는...\p"
	.string "지금이라도 포켓몬이 튀어나올 듯한\n"
	.string "모던하고 살아있는 듯한 작품을\l"
	.string "장식하고 싶습니다!$"
	@ ごらんの とおり まだｎ
	@ えが かざられて おりませんｐ
	@ ここには 1かいに あるようなｎ
	@ いわゆる めいが といった ものとはｌ
	@ ちがう えを かざりたいの ですよ!ｐ
	@ ふるい めいが ばかりがｎ
	@ げいじゅつ なのでは ありません!ｐ
	@ この てんじしつ には……ｐ
	@ いまにも ポケモンが とびだして きそうなｎ
	@ モダンで いきいきとした さくひんをｌ
	@ かざって みたいのです!

LilycoveCity_LilycoveMuseum_2F_Text_PleaseObtainPaintingsForExhibit: @ 8219BC4
	.string "무심코 오랫동안 실례했습니다\p"
	.string "당신은 아직 젊고\n"
	.string "여행을 하고 있으신 것 같으니\p"
	.string "활기찬 포켓몬이나\n"
	.string "그것을 그린 멋진 작품과\l"
	.string "마주칠지도 몰라요!\p"
	.string "만약 그런 작품과 마주친다면\n"
	.string "그 그림을 여기에 장식할 수 있도록\l"
	.string "당신이 부탁해 주신다면\l"
	.string "정말 기쁠 거예요$"
	@ つい ながながと しつれい しましたｐ
	@ あなたは まだ おわかいしｎ
	@ たびを なさって いる ようだからｐ
	@ いきいきとした ポケモンやｎ
	@ それを えがいた すてきな さくひんにｌ
	@ であわれる かも しれません!ｐ
	@ もし そんな さくひんに であったらｎ
	@ そのえを ここに かざれる ようにｌ
	@ あなたから おねがい して くださるとｌ
	@ たいへん うれしいです

LilycoveCity_LilycoveMuseum_2F_Text_WishToFillExhibit: @ 8219CF3
	.string "이 전시실에는\n"
	.string "현대의 생생한 포켓몬의\l"
	.string "그림을 장식하고 싶습니다$"
	@ この てんじしつ にはｎ
	@ げんだいの いきいき とした ポケモンのｌ
	@ えを かざりたい ものです

LilycoveCity_LilycoveMuseum_2F_Text_ThanksAddedNewPainting: @ 8219D42
	.string "덕분에 그림을\n"
	.string "장식할 수 있었어요!\p"
	.string "당신의 포켓몬이라 하더라고요!\n"
	.string "정말 굉장하군요!\p"
	.string "참으로 감사합니다...!$"
	@ おかげさまで えをｎ
	@ かざる ことが できましたよ!ｐ
	@ あなたの ポケモン なんですって ね!ｎ
	@ ほんとうに すばらしい です!ｐ
	@ どうも ありがとう……!

LilycoveCity_LilycoveMuseum_2F_Text_ItsYouPlayer: @ 8219DD4
	.string "앗! 당신은! {PLAYER}님!$"
	@ あ あなた! §あさん!

LilycoveCity_LilycoveMuseum_2F_Text_PaintingsAttractedMoreGuests: @ 8219DE6
	.string "어떻습니까 봐 주십시오!\n"
	.string "이 굉장한 작품들을!\p"
	.string "어느 것도 서로에게\n"
	.string "꿇리지 않는 굉장함!\p"
	.string "이 그림 덕분에게 미술관에\n"
	.string "오시는 분도 늘었어요!\p"
	.string "정말로 감사합니다 {PLAYER}님!\n"
	.string "제 꿈이 이루어졌어요!$"
	@ どうです みて ください!ｎ
	@ この すばらしい さくひん たちを!ｐ
	@ どれも おたがいにｎ
	@ ひけをとらない すばらしさ!ｐ
	@ この えの おかげで びじゅつかんにｎ
	@ こられる かたも ふえたんです!ｐ
	@ ほんとうに ありがとう §あさん!ｎ
	@ わたしの ゆめが かないました!

LilycoveCity_LilycoveMuseum_2F_Text_TokenOfGratitude: @ 8219EC5
	.string "...이건 제가 드리는\n"
	.string "감사의 마음입니다!$"
	@ ……これは わたしからのｎ
	@ おれいの きもち です!

LilycoveCity_LilycoveMuseum_2F_Text_KeepThisForYou: @ 8219EED
	.string "그럼 또 오셨을 때\n"
	.string "드리도록 하죠$"
	@ それでは また いらした ときにｎ
	@ さしあげましょう

LilycoveCity_LilycoveMuseum_2F_Text_HonorToHaveYouVisit: @ 8219F1B
	.string "오 이거 {PLAYER}님!\p"
	.string "바쁜 여행 도중에\n"
	.string "와 주시다니 영광입니다!\p"
	.string "그럼 천천히 있다 가세요$"
	@ やあ これは §あさん!ｐ
	@ おいそがしい たびの あいまにｎ
	@ おたちより くださって こうえいです!ｐ
	@ どうぞ ごゆっくり おすごしくださいね

LilycoveCity_LilycoveMuseum_2F_Text_ItsPinkPictureFrame: @ 8219FA0
	.string "분홍색 장식이 달린 액자다!$"
	@ ももいろの かざりが ついた がくぶちだ!

LilycoveCity_LilycoveMuseum_2F_Text_ItsYellowPictureFrame: @ 8219FD3
	.string "노란색 장식이 달린 액자다!$"
	@ きいろの かざりが ついた がくぶちだ!

LilycoveCity_LilycoveMuseum_2F_Text_ItsBluePictureFrame: @ 821A008
	.string "파란색 장식이 달린 액자다!$"
	@ あおい かざりが ついた がくぶちだ!

LilycoveCity_LilycoveMuseum_2F_Text_ItsRedPictureFrame: @ 821A03B
	.string "빨간색 장식이 달린 액자다!$"
	@ あかい かざりが ついた がくぶちだ!

LilycoveCity_LilycoveMuseum_2F_Text_ItsGreenPictureFrame: @ 821A06D
	.string "초록색 장식이 달린 액자다!$"
	@ みどりいろの かざりが ついた がくぶちだ!

LilycoveCity_LilycoveMuseum_2F_Text_ItsPaintingOfPokemon: @ 821A0A1
	.string "포켓몬 그림이 장식되어 있다!$"
	@ ポケモンの えが かざってある!

LilycoveCity_LilycoveMuseum_2F_Text_NewPaintingsSurprisedMe: @ 821A0BD
	.string "오랜만에 와 봤는데 2층에도\n"
	.string "전시가 되어 있어서 깜짝 놀랐어!\p"
	.string "좋겠다 내 포켓몬도\n"
	.string "이렇게 멋지게 그려진다면 좋겠네$"
	@ ひさしぶりに きて みたら 2かいにもｎ
	@ えが かざって あって びっくり!ｐ
	@ いいなあ あたしの ポケモンもｎ
	@ こんなふうに すてきに かいて ほしいな

LilycoveCity_LilycoveMuseum_2F_Text_NewPaintingsRatherAmusing: @ 821A132
	.string "호오... 여기가 최근 화제가 되고 있는\n"
	.string "포켓몬 그림이 있는 곳인가...\p"
	.string "과연 새로운 그림이 가득해서\n"
	.string "꽤나 재미있구먼...$"
	@ ほう…… ここが さいきん わだいのｎ
	@ ポケモンの えが ある ところか……ｐ
	@ なるほど あたらしい えが いっぱいでｎ
	@ なかなか おもしろい のう……

LilycoveCity_LilycoveMuseum_2F_Text_ThesePaintingsOfYourPokemon: @ 821A1A8
	.string "우와-! 이거\n"
	.string "네 포켓몬의 그림이구나!\p"
	.string "그거야말로 트레이너로서\n"
	.string "정말 최고의 행복이지!$"
	@ へえ-! これってｎ
	@ きみの ポケモンの えなんだ!ｐ
	@ それって トレ-ナ- としてｎ
	@ さいこうの しあわせ だよな!

