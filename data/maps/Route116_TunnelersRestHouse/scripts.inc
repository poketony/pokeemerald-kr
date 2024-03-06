Route116_TunnelersRestHouse_MapScripts:: @ 822B850
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_TunnelersRestHouse_OnTransition
	.byte 0

Route116_TunnelersRestHouse_OnTransition: @ 822B856
	setflag FLAG_LANDMARK_TUNNELERS_REST_HOUSE
	end

Route116_TunnelersRestHouse_EventScript_Tunneler1:: @ 822B85A
	msgbox Route116_TunnelersRestHouse_Text_WeHadToStopBoring, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler2:: @ 822B863
	msgbox Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler3:: @ 822B86C
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, Route116_TunnelersRestHouse_EventScript_TunnelOpened
	msgbox Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_EventScript_TunnelOpened:: @ 822B881
	msgbox Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_Text_WeHadToStopBoring: @ 822B88B
	.string "저 금잔터널은...\p"
	.string "처음엔 수많은 사람들과\n"
	.string "최신식 기계로 파 나갔지\p"
	.string "하지만 그대로 계속 파면\n"
	.string "주변의 포켓몬에게\l"
	.string "악영향을 끼친다는군\p"
	.string "그래서 우리들은 어쩌지도 못하고\n"
	.string "여기서 멍하니 있는 거야$"
	@ あの カナシダトンネル……ｐ
	@ はじめは たくさんの にんげんとｎ
	@ さいしんの キカイで ほりすすんでいたｐ
	@ だが そのまま ほりすすむとｎ
	@ あたりの ポケモンにｌ
	@ あくえいきょうを あたえる らしくてねｐ
	@ で おれら どうしようもなくｎ
	@ ここで ぼんやりと しているわけさ

Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf: @ 822B99F
	.string "어떻게 해서든 잔디마을에\n"
	.string "가고 싶어 하는 녀석이\l"
	.string "혼자서 터널을 파왔어\p"
	.string "사람의 힘으로 조금씩 파내면\n"
	.string "포켓몬을 놀라게 하지도 않고\l"
	.string "주변 자연환경에도 나쁜 영향을\l"
	.string "끼치지 않을 거라면서 말이야$"
	@ どうしても シダケに いきたいｎ
	@ やつが じぶんの ちから だけでｌ
	@ トンネルを ほっているよｐ
	@ にんげんの ちからで すこしずつ ほればｎ
	@ ポケモンを おどろかせなくて すむしｌ
	@ まわりの しぜんにも わるい えいきょうをｌ
	@ あたえないで すむって いってな
	
Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel: @ 822BAAF
	.string "여기서 터널을 지나지 않고\n"
	.string "잔디마을로 가려면 바다를 건너\l"
	.string "무로마을에서 잿빛도시로 간 다음\l"
	.string "보라시티를 통해서 가는 수밖에 없군!$"
	@ トンネルを つかわずに ここからｎ
	@ シダケに いくなら うみを わたりｌ
	@ ムロから カイナ そしてｌ
	@ キンセツを とおって いくしか ないな!

Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough: @ 822BB3B
	.string "결국엔 잔디마을까지 가는\n"
	.string "터널이 뚫린 모양이야!\p"
	.string "이거야말로\n"
	.string "“꿈은 이루어진다”로구만!$"
	@ なんでも シダケ までのｎ
	@ トンネルが つうじた らしいぞ!ｐ
	@ ねがい つづければｎ
	@ いつかは かなう って ことなんだな!

