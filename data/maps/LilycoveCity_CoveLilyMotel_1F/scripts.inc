.set LOCALID_OWNER, 1

LilycoveCity_CoveLilyMotel_1F_MapScripts:: @ 8218188
	.byte 0

LilycoveCity_CoveLilyMotel_1F_EventScript_MotelOwner:: @ 8218189
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_CoveLilyMotel_1F_EventScript_GameClear
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot, MSGBOX_DEFAULT
	applymovement LOCALID_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted:: @ 82181C3
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem, MSGBOX_DEFAULT
	applymovement LOCALID_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_GameClear:: @ 82181EA
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar, MSGBOX_DEFAULT
	applymovement LOCALID_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_BlockingTV:: @ 8218211
	lockall
	playse SE_PIN
	applymovement LOCALID_OWNER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_OWNER, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV
	applymovement LOCALID_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer
	waitmovement 0
	applymovement LOCALID_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn
	waitmovement 0
	release
	end

LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV: @ 8218259
	face_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer: @ 821825E
	walk_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn: @ 8218260
	face_down
	walk_down
	face_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot: @ 8218264
	.string "흠흠 포켓몬의 매력으로\n"
	.string "손님들이 급격히 늘어났다고!?\p"
	.string "그렇구나 그럼 우리도 귀여운 포켓몬을\n"
	.string "민박의 마스코트로 삼으면\p"
	.string "더 많은 손님이\n"
	.string "찾아와 주려나?$"
	// ほほう ポケモンの みりょくでｎ
	// おきゃくさまが ばいぞう したって!?ｐ
	// そうかあ うちも かわいい ポケモンをｎ
	// りょかんの マスコットに すればｐ
	// もっと たくさんの おきゃくさまがｎ
	// とまりに きてくれるように なるかな?

LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua: @ 821831E
	.string "아 미안 미안!\n"
	.string "TV 보는 데 집중하고 있어서!\p"
	.string "아쿠아단이라고 하는 녀석들이\n"
	.string "마을에 오는 바람에\l"
	.string "관광객의 발길도 끊겼어$"
	// あ ごめん ごめん!ｎ
	// テレビに むちゅう だったもんで!ｐ
	// アクアだん とかいう れんちゅうがｎ
	// まちに やってきた おかげでｌ
	// かんこうきゃくも さっぱり なんだよね

LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV: @ 821839B
	.string "아- 방해하지 말아줄래!\n"
	.string "TV가 안 보이잖아!$"
	// あ- ちょっと じゃま しないで!ｎ
	// テレビが みえない じゃないか!

LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem: @ 82183C3
	.string "뭐라고! 잃어버린 도구를\n"
	.string "포켓몬이 주워줬다고!?\p"
	.string "그렇군 우리 집에도 그런\n"
	.string "똑똑한 포켓몬이 있다면\p"
	.string "손님들의 잃어버린 물건도\n"
	.string "금세 찾을 수 있을 텐데...$"
	// なんと! なくした どうぐをｎ
	// ポケモンが ひろって きたって!?ｐ
	// そうかあ うちも そんなｎ
	// かしこい ポケモンが いてくれればｐ
	// おきゃくさまの なくした ものもｎ
	// すぐに みつかるのになぁ……

LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted: @ 8218470
	.string "아 미안 미안!\n"
	.string "TV 보는 데 집중하고 있어서!\p"
	.string "그러고 보니 누군가가 아쿠아단의\n"
	.string "아지트를 괴멸시켰대!\p"
	.string "덕분에 아까 단체 손님의\n"
	.string "숙박 예약이 들어왔어!\p"
	.string "뭐더라... GAME 어쩌고 라는\n"
	.string "회사였던 거 같은데...$"
	// あ ごめん ごめん!ｎ
	// テレビに むちゅう だったもんで!ｐ
	// そういえば だれかが アクアだんのｎ
	// アジトを かいめつ させた らしいね!ｐ
	// おかげで さっき だんたいさん からのｎ
	// しゅくはく よやくが はいったよ!ｐ
	// たしか…… ゲ-ムなんとか っていうｎ
	// かいしゃ だったかな……

LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar: @ 8218544
	.string "뭐라고! 숨어 들어온 도둑을\n"
	.string "집을 보던 포켓몬이 잡았다고!?\p"
	.string "그렇군 우리 집에도 경비원 대신\n"
	.string "강한 포켓몬이 있다면\p"
	.string "손님을 안전하게\n"
	.string "지켜드릴 수 있을 텐데...$"
	// なんと! しのびこんだ どろぼうをｎ
	// るすばんの ポケモンが つかまえたって!?ｐ
	// そうかあ うちも ガ-ドマンの かわりにｎ
	// つよい ポケモンが いてくれればｐ
	// おきゃくさまの あんぜんをｎ
	// まもることが できそうだなぁ……

LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner: @ 82185F4
	.string "아 미안 미안!\n"
	.string "TV 보는 데 집중하고 있어서!\p"
	.string "그러고 보니까 아까\n"
	.string "단체 손님이 도착했어!\p"
	.string "GAME FREAK라고 하던데\n"
	.string "게임 회사 사람들인가?\l"
	.string "아 식사 준비를 해야겠다...$"
	// あ ごめん ごめん!ｎ
	// テレビに むちゅう だったもんで!ｐ
	// そういえば さっきｎ
	// だんたいさん が とうちゃく したよ!ｐ
	// ゲ-ムフリ-クって いうからｎ
	// ゲ-ムの かいしゃの ひとたち かなぁ?ｌ
	// ああ ごはんの じゅんびを しなくちゃ……

