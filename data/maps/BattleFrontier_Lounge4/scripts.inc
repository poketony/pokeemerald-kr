BattleFrontier_Lounge4_MapScripts:: @ 826358C
	.byte 0

BattleFrontier_Lounge4_EventScript_Woman:: @ 826358D
	msgbox BattleFrontier_Lounge4_Text_WonderIfInterviewsAiring, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Cook:: @ 8263596
	msgbox BattleFrontier_Lounge4_Text_IfIOpenedRestaurantHere, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Man:: @ 826359F
	msgbox BattleFrontier_Lounge4_Text_NeedBreatherAfterBattles, MSGBOX_NPC
	end

BattleFrontier_Lounge4_Text_WonderIfInterviewsAiring: @ 82635A8
	.string "강한 트레이너와의 인터뷰\n"
	.string "오늘은 방송하려나?$"
	// つよい トレ-ナ-の インタビュ-ｎ
	// きょうは やって いるかな-?

BattleFrontier_Lounge4_Text_IfIOpenedRestaurantHere: @ 82635EC
	.string "여기에 맛있는 레스토랑이라도\n"
	.string "차린다면 더 벌 수 있을 거 같아$"
	// ここで おいしい レストランでもｎ
	// やったら もうかりそうやな

BattleFrontier_Lounge4_Text_NeedBreatherAfterBattles: @ 8263625
	.string "휴우\p"
	.string "배틀하는 도중에\n"
	.string "잠깐 휴식 중...\p"
	.string "이라고 말해도\l"
	.string "내 머릿속은\n"
	.string "쉬지 않고 전략을 세우는 중이지!$"
	// ふうｐ
	// たたかいの あいまにｎ
	// ちょっと ひとやすみ……ｐ
	// と いってもｎ
	// おれの あたまの なかではｌ
	// やすみなく せんりゃくが ねられているぜ!

