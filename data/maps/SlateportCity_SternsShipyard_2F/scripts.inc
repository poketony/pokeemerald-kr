SlateportCity_SternsShipyard_2F_MapScripts:: @ 820863D
	.byte 0

SlateportCity_SternsShipyard_2F_EventScript_Scientist1:: @ 820863E
	msgbox SlateportCity_SternsShipyard_2F_Text_ShipDesignMoreLikeBuilding, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_2F_EventScript_Scientist2:: @ 8208647
	msgbox SlateportCity_SternsShipyard_2F_Text_FloatsBecauseBuoyancy, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_2F_Text_ShipDesignMoreLikeBuilding: @ 8208650
	.string "거대한 배를 만든다는 건\n"
	.string "탈것을 만드는 것보다는\l"
	.string "큰 건물을 짓는 거랑 비슷해$"
	@ おおきな ふねを つくる というのはｎ
	@ のりものを つくる というよりもｌ
	@ たてものを つくるのに にているんだよ

SlateportCity_SternsShipyard_2F_Text_FloatsBecauseBuoyancy: @ 82086BA
	.string "쇠로 만들어진 무거운 배가\n"
	.string "물 위에 뜨는 게 신기하지?\p"
	.string "그건 “부력”이라는 원리를\n"
	.string "응용하고 있기 때문이야$"
	@ おもたい てつで できている ふねがｎ
	@ うみに うくなんて ふしぎ だろう?ｐ
	@ あれは 「ふりょく」 という げんりをｎ
	@ おうよう しているんだ

