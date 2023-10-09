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
	.string "견학을 하고 있지요\p"
	.string "흠흠...\n"
	.string "다른 방도 있는 것 같군요$"
	// こういった ふねは めずらしいのでｎ
	// けんがく しておるのですよｐ
	// フムフム……ｎ
	// ほかにも へやが ありそうですな

AbandonedShip_Rooms_1F_Text_ThaliaIntro:
	.string "어라 이런 곳까지 오다니\n"
	.string "너는 참 호기심이 많구나!$"
	// あら こんな ところまで きてｎ
	// キミも ものずきね!

AbandonedShip_Rooms_1F_Text_ThaliaDefeat:
	.string "호기심이 많을 뿐만 아니라\n"
	.string "강하기까지 하네...$"
	// ものずき だけじゃ なくてｎ
	// つよいのか……

AbandonedShip_Rooms_1F_Text_ThaliaPostBattle:
	.string "옆 방에 있는 아저씨\n"
	.string "견학하러 왔다는데 수상해\p"
	.string "나한테 무슨 짓을 할 속셈인가?$"
	// となりのへやの おじさんｎ
	// けんがく だなんて あやしいわｐ
	// わたしに きが あるんじゃない かしら

AbandonedShip_Rooms_1F_Text_ThaliaRegister:
	.string "강한 트레이너인 너를 만난\n"
	.string "기념으로 등록하게 해줘!$"
	// つよい トレ-ナ-の キミをｎ
	// きねんに とうろく させて ちょうだいね!

AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro:
	.string "이런 곳까지 계속 오다니\n"
	.string "정말로 호기심이 많구나 넌!$"
	// こんな ところまで なんども きてｎ
	// ほんとに ものずきね キミって!

AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat:
	.string "잠깐만 너무 강한데?$"
	// ちょっと つよすぎない?

AbandonedShip_Rooms_1F_Text_ThaliaPostRematch:
	.string "저 아저씨 분명\n"
	.string "날 보고 있는 걸 거야!\l"
	.string "너무 수상하게 행동한다니까!$"
	// あの おじさん ぜったいｎ
	// わたしの ことを みているのよ!ｌ
	// わざとらしすぎるわ!

AbandonedShip_Rooms_1F_Text_DemetriusIntro:
	.string "와-아!\n"
	.string "찾았다... 아니 잠깐만?$"
	// わ-っ!ｎ
	// みつかった…… って あれ?

AbandonedShip_Rooms_1F_Text_DemetriusDefeat:
	.string "뭐야\n"
	.string "엄마가 아니잖아$"
	// なんだｎ
	// かあちゃん じゃ なかったのか

AbandonedShip_Rooms_1F_Text_DemetriusPostBattle:
	.string "엄마한테 혼나서\n"
	.string "여기까지 도망쳐온 거야\l"
	.string "내가 여기 있는 건 비밀로 해줘!$"
	// かあちゃんに しかられてｎ
	// ここまで にげて きたんだｌ
	// ボクが ここに いるのは ないしょだぞ!
