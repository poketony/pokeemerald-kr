.set LOCALID_TWIN, 2

VerdanturfTown_MapScripts:: @ 81EB566
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition: @ 81EB56C
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	end

VerdanturfTown_EventScript_Twin:: @ 81EB575
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_TwinTunnelOpen
	msgbox VerdanturfTown_Text_ManTryingToDigTunnel, MSGBOX_DEFAULT
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen:: @ 81EB594
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_Man:: @ 81EB5A8
	msgbox VerdanturfTown_Text_AirCleanHere, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Camper:: @ 81EB5B1
	msgbox VerdanturfTown_Text_MakeBattleTentDebut, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Boy:: @ 81EB5BA
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_BoyTunnelOpen
	msgbox VerdanturfTown_Text_GuyTryingToBustThroughCave, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_BoyTunnelOpen:: @ 81EB5CF
	msgbox VerdanturfTown_Text_EasyToGetToRustboroNow, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TownSign:: @ 81EB5D9
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign:: @ 81EB5E2
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign:: @ 81EB5EB
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign:: @ 81EB5F4
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

VerdanturfTown_Text_ManTryingToDigTunnel: @ 81EB5FD
	.string "우리 아빠가 말씀하셨어\p"
	.string "이 터널에는 큰- 소리에\n"
	.string "반응해서 소란 피우는\l"
	.string "겁쟁이 포켓몬이 가득하대!\p"
	.string "그래서 개발 공사를 그만뒀는데\n"
	.string "어떤 남자가 혼자서\l"
	.string "터널을 파려고 한다나 봐!$"
	// わたしの パパが いってたのｐ
	// この トンネルって お-きな おとにｎ
	// はんのうして さわぎだす おくびょうなｌ
	// ポケモンが いっぱい なんだって!ｐ
	// だから かいはつ こうじ やめたんだけどｎ
	// おとこの ひとが ひとりでｌ
	// トンネルを ほろうと してるんだって!

VerdanturfTown_Text_ManDugTunnelForLove: @ 81EB6E0
	.string "사랑하는 사람을 위해\n"
	.string "동굴을 팠던 사람이 있어!\p"
	.string "왠지 굉-장해!$"
	// あいする ひとの ためにｎ
	// どうくつを ほっていた ひとが いるの!ｐ
	// なんだか すご-い!

VerdanturfTown_Text_AirCleanHere: @ 81EB736
	.string "바람의 방향 때문에 이 마을에는\n"
	.string "화산재가 날아오지 않아!\p"
	.string "공기가 맑은 이 마을에서 살면\n"
	.string "몸이 튼튼하지 않은 사람도\l"
	.string "반드시 건강해질 거야!$"
	// かざむきの かんけいで このまち にはｎ
	// かざんばいが とんでくることは ない!ｐ
	// くうきの おいしい このまちで くらせばｎ
	// からだが じょうぶでない ひとでもｌ
	// きっと げんきに なれる はずさ!

VerdanturfTown_Text_MakeBattleTentDebut: @ 81EB7E2
	.string "나와 내 포켓몬\n"
	.string "요즘 엄청 상태가 좋거든\p"
	.string "배틀텐트에 데뷔하기로 결정해서\n"
	.string "이 마을에 온 거야!$"
	// ぼくと ぼくの ポケモンｎ
	// さいきん すごく ちょうしが よくてねｐ
	// バトルテント デビュ- させたくてｎ
	// この まちに きたんだ!

VerdanturfTown_Text_GuyTryingToBustThroughCave: @ 81EB854
	.string "프렌들리숍 옆에\n"
	.string "동굴이 있지?\p"
	.string "안을 막고 있는 바위를 부수고\n"
	.string "지나갈 수 있게 하려고 노력하는\l"
	.string "사람이 있다고 하더라!\p"
	.string "잘 됐으면 해...\n"
	.string "금탄도시에도 가기 쉬워지니까!$"
	// フレンドリィ ショップの となりにｎ
	// どうくつが あるだろ?ｐ
	// なかを ふさいでいる いわを こわしｎ
	// とおれるように しようと がんばっているｌ
	// やつが いるらしいんだ!ｐ
	// とおれるように なると いいのに……ｎ
	// カナズミにも いきやすく なるから!

VerdanturfTown_Text_EasyToGetToRustboroNow: @ 81EB935
	.string "프렌들리숍 옆의 동굴 말이야\n"
	.string "지나갈 수 있게 되었지?\p"
	.string "금탄도시까지 데봉의 신제품을\n"
	.string "사러 가기 쉬워져서 기뻐!$"
	// フレンドリィ ショップの となりのｎ
	// どうくつが とおれるように なっただろ!ｐ
	// カナズミまで デボンの しんせいひんをｎ
	// かいに いきやすくなって うれしいよ!

VerdanturfTown_Text_TownSign: @ 81EB9C4
	.string "여기는 잔디마을\n"
	.string "풀 내음의 바람이 부는 고원$"
	// ここは シダケ タウンｎ
	// くさの においの かぜふく こうげん

VerdanturfTown_Text_WandasHouse: @ 81EBA11
	.string "“미진의 집”$"
	// 「ミチルの いえ」

VerdanturfTown_Text_BattleTentSign: @ 81EBA1F
	.string "배틀텐트 잔디마을 회장\n"
	.string "지켜봐라! 포켓몬 배틀$"
	// バトルテント シダケタウン かいじょうｎ
	// みまもれ! ポケモンバトル

VerdanturfTown_Text_RusturfTunnelSign: @ 81EBA59
	.string "금탄도시와 잔디마을을 연결하는\n"
	.string "“금잔터널”\p"
	.string "개통 공사는 중단되었습니다$"
	// カナズミと シダケを むすぶｎ
	// 「カナシダ トンネル」ｐ
	// かいつう こうじは ちゅうしに なりました

