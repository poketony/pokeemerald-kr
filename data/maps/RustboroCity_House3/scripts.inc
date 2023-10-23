RustboroCity_House3_MapScripts:: @ 8216190
	.byte 0

RustboroCity_House3_EventScript_OldMan:: @ 8216191
	msgbox RustboroCity_House3_Text_IGivePerfectlySuitedNicknames, MSGBOX_NPC
	end

RustboroCity_House3_EventScript_OldWoman:: @ 821619A
	msgbox RustboroCity_House3_Text_NamingPikachuPekachu, MSGBOX_NPC
	end

@ Misspelling on purpose, see nickname
RustboroCity_House3_EventScript_Pekachu:: @ 82161A3
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, 0
	msgbox RustboroCity_House3_Text_Pekachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RustboroCity_House3_Text_IGivePerfectlySuitedNicknames: @ 82161B6
	.string "자신의 포켓몬에게\n"
	.string "딱 어울리는 닉네임을 지어주게나\l"
	.string "이른바 오리지널리티라는 게지!$"
	// じぶんの ポケモンにはｎ
	// ぴったりの ニックネ-ムを つけるんじゃｌ
	// いわゆる おりじなりてぃ じゃ!

RustboroCity_House3_Text_NamingPikachuPekachu: @ 821622A
	.string "그렇다고 피카츄에게\n"
	.string "“페카츄”라는 이름을 붙여도\l"
	.string "바뀐 게 거의 없는데 말이지...\p"
	.string "뭐 이해하기 쉽게 짓는 것도\n"
	.string "닉네임의 중요한 점이지만$"
	// だからって ピカチュウにｎ
	// 「ペカチュウ」って つけてもｌ
	// ほとんど かわって ないでしょうに……ｐ
	// まあ わかりやすいのもｎ
	// ニックネ-ムには だいじ ですけどねぇ

RustboroCity_House3_Text_Pekachu: @ 82162AB
	.string "페카츄: 페카-!$"
	// ペカチュウ『ぺか-!

