PetalburgCity_House2_MapScripts:: @ 82078F2
	.byte 0

PetalburgCity_House2_EventScript_Woman:: @ 82078F3
	msgbox PetalburgCity_House2_Text_NormanBecameGymLeader, MSGBOX_NPC
	end

PetalburgCity_House2_EventScript_SchoolKid:: @ 82078FC
	msgbox PetalburgCity_House2_Text_BattledNormanOnce, MSGBOX_NPC
	end

PetalburgCity_House2_Text_NormanBecameGymLeader: @ 8207905
	.string "이 마을의 새로운\n"
	.string "체육관 관장이 되신 종길님은\p"
	.string "먼 곳에 살고 있던 가족을\n"
	.string "이리로 데려오셨나 봐$"

PetalburgCity_House2_Text_BattledNormanOnce: @ 8207969
	.string "전에 한번 승부해봤었는데\n"
	.string "역시 종길님은 진짜 강해!\p"
	.string "뭐랄까 음...\p"
	.string "“포켓몬을 위해 산다!”\n"
	.string "는 느낌이 마구마구 느껴진다니까?!$"

