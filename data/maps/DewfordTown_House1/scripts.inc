DewfordTown_House1_MapScripts:: @ 81FC3CD
	.byte 0

DewfordTown_House1_EventScript_Man:: @ 81FC3CE
	msgbox DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Woman:: @ 81FC3D7
	msgbox DewfordTown_House1_Text_LifeGoesSlowlyOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Zigzagoon:: @ 81FC3E0
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, 0
	msgbox DewfordTown_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland: @ 81FC3F3
	.string "이런 작은 섬에서\n"
	.string "포켓몬과 가족과 사이좋게 사는 것도\l"
	.string "제법 행복하답니다$"
	// こういう ちいさな しまでｎ
	// ポケモンと かぞく なかよく くらすのもｌ
	// なかなか いい もんですよ

DewfordTown_House1_Text_LifeGoesSlowlyOnIsland: @ 81FC45B
	.string "나는 잿빛도시라고 하는\n"
	.string "커다란 항구도시에서\l"
	.string "시집을 왔어\p"
	.string "할 것 없는 느긋한 섬이지만\n"
	.string "아름다운 바다에 둘러싸여 있으면\l"
	.string "그것만으로도 행복하단 말이지$"
	// わたしは カイナシティ というｎ
	// おおきな みなとまち からｌ
	// およめさんに きたのよｐ
	// のんびりとした しま だけれどｎ
	// きれいな うみに かこまれて いればｌ
	// それだけで しあわせ なんだね

DewfordTown_House1_Text_Zigzagoon: @ 81FC510
	.string "지그제구리: 킁킁!$"
	// ジグザグマ『ぐぐう!

