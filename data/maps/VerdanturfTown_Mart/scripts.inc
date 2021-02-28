VerdanturfTown_Mart_MapScripts:: @ 8202586
	.byte 0

VerdanturfTown_Mart_EventScript_Clerk:: @ 8202587
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart VerdanturfTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
VerdanturfTown_Mart_Pokemart: @ 82025A0
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_FLUFFY_TAIL
	.2byte ITEM_NONE
	release
	end

VerdanturfTown_Mart_EventScript_Boy:: @ 82025BA
	msgbox VerdanturfTown_Mart_Text_XSpecialIsCrucial, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_ExpertF:: @ 82025C3
	msgbox VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_Lass:: @ 82025CC
	msgbox VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon, MSGBOX_NPC
	end

VerdanturfTown_Mart_Text_XSpecialIsCrucial: @ 82025D5
	.string "포켓몬 승부에\n"
	.string "스페셜업은 빠질 수 없지!\p"
	.string "배틀 때만이라고는 해도\n"
	.string "기술의 위력이 올라간다고!$"
	// ポケモン しょうぶにｎ
	// スペシャルアップは かかせない!ｐ
	// たたかいの ときだけ とはいえｎ
	// わざの いりょくが あがるんだからな!

VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent: @ 820264C
	.string "배틀텐트 필승\n"
	.string "공략본 같은 건\l"
	.string "팔지 않는 건가...\p"
	.string "역시 직접 힘내서\n"
	.string "해내지 않으면 안 되겠구먼$"
	// バトルテント ひっしょうｎ
	// こうりゃくぼん というのはｌ
	// うってない ですねえ……ｐ
	// やはり じぶんでｎ
	// がんばらないと ダメなんですねえ

VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon: @ 82026C9
	.string "잔디마을에서밖에 살 수 없는\n"
	.string "네스트볼은\l"
	.string "약한 포켓몬일수록 잡기 쉬워져$"
	// シダケでしか かえない ネストボ-ルｎ
	// よわい ポケモンほど つかまえ やすくなるの

