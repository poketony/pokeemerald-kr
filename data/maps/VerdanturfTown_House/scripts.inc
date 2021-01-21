VerdanturfTown_House_MapScripts:: @ 820335E
	.byte 0

VerdanturfTown_House_EventScript_Woman1:: @ 820335F
	msgbox VerdanturfTown_House_Text_TrainersGatherAtPokemonLeague, MSGBOX_NPC
	end

VerdanturfTown_House_EventScript_Woman2:: @ 8203368
	msgbox VerdanturfTown_House_Text_DefeatEliteFourInARow, MSGBOX_NPC
	end

VerdanturfTown_House_Text_TrainersGatherAtPokemonLeague: @ 8203371
	.string "멀리 떨어진\n"
	.string "그랜드시티의 오지에 있다고 하는\l"
	.string "포켓몬리그\p"
	.string "그곳에 모이는 건\n"
	.string "굉장한 실력의 트레이너들뿐이래!$"
	// とおく はなれたｎ
	// サイユウの おくちに ある というｌ
	// ポケモン リ-グｐ
	// そこに あつまるのはｎ
	// すごうでの トレ-ナ- ばかり ですって!

VerdanturfTown_House_Text_DefeatEliteFourInARow: @ 82033EE
	.string "포켓몬리그는\n"
	.string "사천왕 4명과 연달아서\l"
	.string "승부해야 하는 룰이래!\p"
	.string "중간에 져버리면 처음부터\n"
	.string "다시 시작해야 한다니 정말 혹독하다!$"
	// ポケモン リ-グはｎ
	// してんのう 4にん つづけてｌ
	// しょうぶする という ル-ルらしいの!ｐ
	// とちゅうで まけたら ひとりめ からｎ
	// やりなおし だなんて きびしいのね!

