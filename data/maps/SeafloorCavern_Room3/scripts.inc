SeafloorCavern_Room3_MapScripts:: @ 8234937
	.byte 0

SeafloorCavern_Room3_EventScript_Shelly:: @ 8234938
	trainerbattle_single TRAINER_SHELLY_SEAFLOOR_CAVERN, SeafloorCavern_Room3_Text_ShellyIntro, SeafloorCavern_Room3_Text_ShellyDefeat
	msgbox SeafloorCavern_Room3_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_EventScript_Grunt5:: @ 823494F
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_5, SeafloorCavern_Room3_Text_Grunt5Intro, SeafloorCavern_Room3_Text_Grunt5Defeat
	msgbox SeafloorCavern_Room3_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_Text_ShellyIntro: @ 8234966
	.string "오호호!\p"
	.string "잠수정도 없는데\n"
	.string "잘도 여기까지 쫓아왔네!\l"
	.string "대단한 꼬맹이네!\p"
	.string "하지만 말야...\n"
	.string "방해받는 건 싫단 말이지\p"
	.string "날씨 연구소에서의\n"
	.string "빚도 갚아주고 싶고...\p"
	.string "살짝 괴로운 기분이 들 테니까\n"
	.string "각오하도록 해-!!$"
	// オ-ッホッホ!ｐ
	// せんすいていも ないのにｎ
	// よく ここまで おいかけて きたわね!ｌ
	// たいした おこさま だわ!ｐ
	// でもね……ｎ
	// ジャマされると めんどう なのよねｐ
	// てんき けんきゅうじょ でのｎ
	// かりも かえしたいし……ｐ
	// ちょっと いたい おもい させちゃうからｎ
	// かくご しなさ-い!!

SeafloorCavern_Room3_Text_ShellyDefeat: @ 8234A79
	.string "오호호!\p"
	.string "괴로워-!$"
	// オ-ッホッホ!ｐ
	// いった-い!

SeafloorCavern_Room3_Text_ShellyPostBattle: @ 8234A8A
	.string "오호호!\p"
	.string "너 그렇게 강한데\n"
	.string "아쿠아단의 동료가 아니라서\l"
	.string "무척 유감이야\p"
	.string "리더가 실현해줄\n"
	.string "멋진 세계를\l"
	.string "같이 즐길 수 있었을 텐데$"
	// オ-ッホッホ!ｐ
	// あなた そんなに つよいんだものｎ
	// アクアだんの なかま じゃなくてｌ
	// とっても ざんねんだわｐ
	// リ-ダ-が じつげん してくれるｎ
	// すばらしい せかいをｌ
	// いっしょに たのしむことが できたのに

SeafloorCavern_Room3_Text_Grunt5Intro: @ 8234B3A
	.string "우리들의 야망을 위해서는\n"
	.string "포켓몬이 필요한데\p"
	.string "포켓몬의 힘을 빌리는\n"
	.string "너 같은 녀석이\l"
	.string "이런 곳까지 방해하러 오다니!\p"
	.string "잘되는 일이 없구만!$"
	// オレたちの やぼうの ためにｎ
	// ポケモンは ひつような ものだがｐ
	// ポケモンの ちからを かりてｎ
	// おまえの ような やつがｌ
	// こんな ところまで ジャマしに くる!ｐ
	// よのなか うまく いかない もんだ!

SeafloorCavern_Room3_Text_Grunt5Defeat: @ 8234BFE
	.string "크악!$"
	// ぐはっ!

SeafloorCavern_Room3_Text_Grunt5PostBattle: @ 8234C04
	.string "우리 머리로는 이해할 수 없는\n"
	.string "그 리더에게\p"
	.string "잘도 너 같은\n"
	.string "꼬맹이가 거스르는구만!\p"
	.string "혹시 너\n"
	.string "엄청난 녀석... 인 거냐?$"
	// オレたちが あたまの あがらないｎ
	// あの リ-ダ-にｐ
	// よくも まあ おまえの ようなｎ
	// こどもが さからえる もんだよな!ｐ
	// もしかして おまえってｎ
	// とんでもないやつ…… なのか?

