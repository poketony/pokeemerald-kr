MysteryEventScript_VisitingTrainer:: @ 8674EC1
	setvaddress MysteryEventScript_VisitingTrainer
	special ValidateEReaderTrainer
	compare VAR_RESULT, 0
	vgoto_if_eq MysteryEventScript_VisitingTrainerArrived
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerInstructions
	waitmessage
	waitbuttonpress
	release
	end

MysteryEventScript_VisitingTrainerArrived: @ 8674EDF
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerArrived
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftVisitingTrainerInstructions:
	.string "이상한 소포를 이용해\n"
	.string "주셔서 감사합니다\p"
	.string "이 이상한 카드를 가지고 있으면\n"
	.string "프렌들리숍의 설문 조사로\p"
	.string "여러 트레이너들을 루네시티에\n"
	.string "부를 수 있게 됩니다!\p"
	.string "...비밀을 하나 알려드리자면\n"
	.string "설문 조사에 이렇게 응답하면 됩니다\p"
	.string "“굉장한 트레이너\n"
	.string " 주세요 주세요”\p"
	.string "이 말을 설문 조사에 적고서\n"
	.string "꼭 조이스폿과\l"
	.string "통신해 보세요!$"
	@ ふしぎなおくりもの を ごりようｎ
	@ いただき ありがとう ございますｐ
	@ この ふしぎなカ-ドを もっているとｎ
	@ フレンドリ-ショップの アンケ-トでｐ
	@ いろいろな トレ-ナ-を ルネシティにｎ
	@ よぶことが できますよ!ｐ
	@ ……ないしょで ひとつ アンケ-トのｎ
	@ あいことばを おしえて あげましょうｐ
	@ 「すごい トレ-ナ-ｎ
	//	くれ くれ」ｐ
	@ このことばを アンケ-トに かいてｎ
	@ ぜひ ジョイスポットとｌ
	@ つうしんして みてください!

sText_MysteryGiftVisitingTrainerArrived:
	.string "이상한 소포를 이용해\n"
	.string "주셔서 감사합니다\p"
	.string "루네시티에 트레이너가\n"
	.string "와 있는 모양입니다\p"
	.string "꼭 대전을\n"
	.string "즐겨주시길 바랍니다!\p"
	.string "다른 말을 통해서\n"
	.string "그 외의 트레이너를 불러낼 수 있으니\p"
	.string "다양한 말을\n"
	.string "찾아봐 주십시오$"
	@ ふしぎなおくりもの を ごりようｎ
	@ いただき ありがとう ございますｐ
	@ ルネシティに トレ-ナ-がｎ
	@ きている ようですよｐ
	@ ぜひ たいせんをｎ
	@ たのしんで くださいませ!ｐ
	@ ほかの あいことば でもｎ
	@ べつの トレ-ナ-が よべますのでｐ
	@ あいことばを いろいろとｎ
	@ さがして みて ください
