MysteryEventScript_StampCard:: @ 8674CB0
	setvaddress MysteryEventScript_StampCard
	setorcopyvar VAR_RESULT, GET_MAX_STAMPS
	specialvar VAR_0x8008, GetMysteryEventCardVal
	setorcopyvar VAR_RESULT, GET_NUM_STAMPS
	specialvar VAR_0x8009, GetMysteryEventCardVal
	subvar VAR_0x8008, VAR_0x8009
	buffernumberstring 0, VAR_0x8008
	lock
	faceplayer
	vmessage sText_MysteryGiftStampCard
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftStampCard:
	.string "스탬프 카드를 이용해주셔서\n"
	.string "감사합니다\p"
	.string "앞으로 남은 {STR_VAR_1}개도\n"
	.string "힘내서 모아주세요!$"
	// スタンプカ-ドの ごりようｎ
	// ありがとう ございますｐ
	// のこり あと §いつｎ
	// がんばって あつめて ください!
