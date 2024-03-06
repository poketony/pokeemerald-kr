MysteryEventScript_AlteringCave:: @ 86756E3
	setvaddress MysteryEventScript_AlteringCave
	addvar VAR_ALTERING_CAVE_WILD_SET, 1
	compare VAR_ALTERING_CAVE_WILD_SET, 10
	vgoto_if_ne MysteryEventScript_AlteringCave_
	setvar VAR_ALTERING_CAVE_WILD_SET, 0
MysteryEventScript_AlteringCave_: @ 86756FD
	lock
	faceplayer
	vmessage sText_MysteryGiftAlteringCave
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftAlteringCave::
	.string "이상한 소포를 이용해\n"
	.string "주셔서 감사합니다!\p"
	.string "최근 103번 도로에 있는\n"
	.string "변형동굴에\p"
	.string "희귀한 포켓몬이 있다는\n"
	.string "소문이 돌고 있는 모양입니다\p"
	.string "한번 가서 확인해 보시는 게\n"
	.string "어떻겠습니까?$"
	@ ふしぎなおくりもの を ごりようｎ
	@ いただき ありがとう ございます!ｐ
	@ さいきん 103ばんどうろ にあるｎ
	@ へんげのどうくつ でｐ
	@ めずらしい ポケモンが でる というｎ
	@ うわさが ながれてる ようですｐ
	@ ぜひ いって たしかめて みてはｎ
	@ いかがで しょうか?
