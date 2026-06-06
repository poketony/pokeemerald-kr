#include "global.h"
#include "malloc.h"
#include "battle.h"
#include "battle_tower.h"
#include "battle_setup.h"
#include "ereader_helpers.h"
#include "event_data.h"
#include "event_scripts.h"
#include "fieldmap.h"
#include "field_message_box.h"
#include "international_string_util.h"
#include "item.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "pokemon.h"
#include "script.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "trainer_hill.h"
#include "window.h"
#include "util.h"
#include "constants/battle_ai.h"
#include "constants/event_object_movement.h"
#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/layouts.h"
#include "constants/moves.h"
#include "constants/maps.h"
#include "constants/trainers.h"
#include "constants/easy_chat.h"
#include "constants/trainer_hill.h"
#include "constants/trainer_types.h"

#define HILL_TAG_NORMAL 0
#define HILL_TAG_VARIETY 1
#define HILL_TAG_UNIQUE 2
#define HILL_TAG_EXPERT 3

#define HILL_MAX_TIME 215999 // 60 * 60 * 60 - 1

// EWRAM
struct TrHillStruct2
{
    u8 floorId;
    struct TrHillTag tag;
    struct TrHillFloor floors[NUM_TRAINER_HILL_FLOORS];
};

static EWRAM_DATA struct TrHillStruct2 *sHillData = NULL;
static EWRAM_DATA struct TrHillRoomTrainers *sRoomTrainers = NULL;
EWRAM_DATA u32 *gTrainerHillVBlankCounter = NULL;

// This file's functions.
static void TrainerHillStartChallenge(void);
static void GetOwnerState(void);
static void GiveChallengePrize(void);
static void CheckFinalTime(void);
static void TrainerHillResumeTimer(void);
static void TrainerHillSetPlayerLost(void);
static void TrainerHillGetChallengeStatus(void);
static void BufferChallengeTime(void);
static void GetAllFloorsUsed(void);
static void GetInEReaderMode(void);
static void IsTrainerHillChallengeActive(void);
static void ShowTrainerHillPostBattleText(void);
static void SetAllTrainerFlags(void);
static void GetGameSaved(void);
static void SetGameSaved(void);
static void ClearGameSaved(void);
static void GetChallengeWon(void);
static void TrainerHillSetTag(void);
static void SetUpDataStruct(void);
static void FreeDataStruct(void);
static void nullsub_2(void);
static void SetTimerValue(u32 *dst, u32 val);
static u32 GetTimerValue(u32 *src);
static void SetTrainerHillMonLevel(struct Pokemon *mon, u8 level);
static u16 GetPrizeItemId(void);

// const data
#include "data/battle_frontier/trainer_hill.h"

struct
{
    u8 trainerClass;
    u8 musicId;
} static const sTrainerClassesAndMusic[] =
{
    {TRAINER_CLASS_TEAM_AQUA, TRAINER_ENCOUNTER_MUSIC_AQUA},
    {TRAINER_CLASS_AQUA_ADMIN, TRAINER_ENCOUNTER_MUSIC_AQUA},
    {TRAINER_CLASS_AQUA_LEADER, TRAINER_ENCOUNTER_MUSIC_AQUA},
    {TRAINER_CLASS_AROMA_LADY, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_BATTLE_GIRL, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_SWIMMER_F, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_POKEFAN, TRAINER_ENCOUNTER_MUSIC_TWINS},
    {TRAINER_CLASS_DRAGON_TAMER, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_COOLTRAINER, TRAINER_ENCOUNTER_MUSIC_COOL},
    {TRAINER_CLASS_GUITARIST, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_SAILOR, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_TWINS, TRAINER_ENCOUNTER_MUSIC_TWINS},
    {TRAINER_CLASS_INTERVIEWER, TRAINER_ENCOUNTER_MUSIC_INTERVIEWER},
    {TRAINER_CLASS_RUIN_MANIAC, TRAINER_ENCOUNTER_MUSIC_HIKER},
    {TRAINER_CLASS_GENTLEMAN, TRAINER_ENCOUNTER_MUSIC_RICH},
    {TRAINER_CLASS_SWIMMER_M, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_POKEMANIAC, TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS},
    {TRAINER_CLASS_BLACK_BELT, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_OLD_COUPLE, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_BUG_MANIAC, TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS},
    {TRAINER_CLASS_CAMPER, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_KINDLER, TRAINER_ENCOUNTER_MUSIC_HIKER},
    {TRAINER_CLASS_TEAM_MAGMA, TRAINER_ENCOUNTER_MUSIC_MAGMA},
    {TRAINER_CLASS_MAGMA_ADMIN, TRAINER_ENCOUNTER_MUSIC_MAGMA},
    {TRAINER_CLASS_MAGMA_LEADER, TRAINER_ENCOUNTER_MUSIC_MAGMA},
    {TRAINER_CLASS_LASS, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_BUG_CATCHER, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_NINJA_BOY, TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS},
    {TRAINER_CLASS_RICH_BOY, TRAINER_ENCOUNTER_MUSIC_RICH},
    {TRAINER_CLASS_HEX_MANIAC, TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS},
    {TRAINER_CLASS_BEAUTY, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_LADY, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_PARASOL_LADY, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_PICNICKER, TRAINER_ENCOUNTER_MUSIC_GIRL},
    {TRAINER_CLASS_PKMN_BREEDER, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_COLLECTOR, TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS},
    {TRAINER_CLASS_PKMN_RANGER, TRAINER_ENCOUNTER_MUSIC_COOL},
    {TRAINER_CLASS_PKMN_TRAINER_3, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_YOUNG_COUPLE, TRAINER_ENCOUNTER_MUSIC_GIRL},
    {TRAINER_CLASS_PSYCHIC, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_SR_AND_JR, TRAINER_ENCOUNTER_MUSIC_TWINS},
    {TRAINER_CLASS_ELITE_FOUR, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_YOUNGSTER, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_EXPERT, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_TRIATHLETE, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_BIRD_KEEPER, TRAINER_ENCOUNTER_MUSIC_COOL},
    {TRAINER_CLASS_FISHERMAN, TRAINER_ENCOUNTER_MUSIC_HIKER},
    {TRAINER_CLASS_CHAMPION, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_TUBER_M, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_TUBER_F, TRAINER_ENCOUNTER_MUSIC_GIRL},
    {TRAINER_CLASS_SIS_AND_BRO, TRAINER_ENCOUNTER_MUSIC_SWIMMER},
    {TRAINER_CLASS_HIKER, TRAINER_ENCOUNTER_MUSIC_HIKER},
    {TRAINER_CLASS_LEADER, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_SCHOOL_KID, TRAINER_ENCOUNTER_MUSIC_MALE},
};

static const u16 sPrizeListRareCandy1[]  = {ITEM_RARE_CANDY,       ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListLuxuryBall1[] = {ITEM_LUXURY_BALL,      ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListMaxRevive1[]  = {ITEM_MAX_REVIVE,       ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListMaxEther1[]   = {ITEM_MAX_ETHER,        ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListElixir1[]     = {ITEM_ELIXIR,           ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListRoar[]        = {ITEM_TM05_ROAR,        ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListSludgeBomb[]  = {ITEM_TM36_SLUDGE_BOMB, ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListToxic[]       = {ITEM_TM06_TOXIC,       ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListSunnyDay[]    = {ITEM_TM11_SUNNY_DAY,   ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListEarthQuake[]  = {ITEM_TM26_EARTHQUAKE,  ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};

static const u16 sPrizeListRareCandy2[]  = {ITEM_RARE_CANDY,       ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListLuxuryBall2[] = {ITEM_LUXURY_BALL,      ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListMaxRevive2[]  = {ITEM_MAX_REVIVE,       ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListMaxEther2[]   = {ITEM_MAX_ETHER,        ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListElixir2[]     = {ITEM_ELIXIR,           ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListBrickBreak[]  = {ITEM_TM31_BRICK_BREAK, ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListTorment[]     = {ITEM_TM41_TORMENT,     ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListSkillSwap[]   = {ITEM_TM48_SKILL_SWAP,  ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListGigaDrain[]   = {ITEM_TM19_GIGA_DRAIN,  ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListAttract[]     = {ITEM_TM45_ATTRACT,     ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};

static const u16 *const sPrizeLists1[NUM_TRAINER_HILL_PRIZE_LISTS] =
{
    sPrizeListRareCandy1,
    sPrizeListLuxuryBall1,
    sPrizeListMaxRevive1,
    sPrizeListMaxEther1,
    sPrizeListElixir1,
    sPrizeListRoar,
    sPrizeListSludgeBomb,
    sPrizeListToxic,
    sPrizeListSunnyDay,
    sPrizeListEarthQuake
};

static const u16 *const sPrizeLists2[NUM_TRAINER_HILL_PRIZE_LISTS] =
{
    sPrizeListRareCandy2,
    sPrizeListLuxuryBall2,
    sPrizeListMaxRevive2,
    sPrizeListMaxEther2,
    sPrizeListElixir2,
    sPrizeListBrickBreak,
    sPrizeListTorment,
    sPrizeListSkillSwap,
    sPrizeListGigaDrain,
    sPrizeListAttract
};

static const u16 *const *const sPrizeListSets[] =
{
    sPrizeLists1,
    sPrizeLists2
};

static const u16 sEReader_Pal[] = INCBIN_U16("graphics/misc/trainer_hill_ereader.gbapal");
static const u8 sRecordWinColors[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GREY, TEXT_COLOR_LIGHT_GREY};

static const struct TrHillTag *const sDataPerTag[] =
{
    &sDataTagNormal,
    &sDataTagVariety,
    &sDataTagUnique,
    &sDataTagExpert,
};

/* Generated from fixed Trainer Hill easy chat speeches so built-in modes can use normal strings. */
#define TRAINER_HILL_STRING_TEXT_COUNT 4

static const u8 sTrainerHillTextNormal00Intro[] = _("믿고 덤벼봐!\n선택은 네 몫이야");
static const u8 sTrainerHillTextNormal00PlayerLost[] = _("슈퍼파워가 솟아난다");
static const u8 sTrainerHillTextNormal00PlayerWon[] = _("이건 분명 악몽이야!");
static const u8 sTrainerHillTextNormal00After[] = _("난 어둠 속으로 사라질게");
static const u8 sTrainerHillTextNormal01Intro[] = _("난 기차 같은 건\n안 탈 거야");
static const u8 sTrainerHillTextNormal01PlayerLost[] = _("자전거를 타면\n기분이 초음파처럼 올라가");
static const u8 sTrainerHillTextNormal01PlayerWon[] = _("내 자전거를 망가뜨렸어!");
static const u8 sTrainerHillTextNormal01After[] = _("역시 자전거보다\n기차가 낫나?");
static const u8 sTrainerHillTextNormal10Intro[] = _("내 힘으로\n널 짓밟아주지!");
static const u8 sTrainerHillTextNormal10PlayerLost[] = _("으하하! 이겼다!");
static const u8 sTrainerHillTextNormal10PlayerWon[] = _("너무 힘을 줬나봐");
static const u8 sTrainerHillTextNormal10After[] = _("좋은데?\n너 제법 끈기가 있는걸");
static const u8 sTrainerHillTextNormal11Intro[] = _("혼자서는 못 하는 일도 있어");
static const u8 sTrainerHillTextNormal11PlayerLost[] = _("우리는 함께 이겨");
static const u8 sTrainerHillTextNormal11PlayerWon[] = _("함께했는데도\n못 이겼다고?");
static const u8 sTrainerHillTextNormal11After[] = _("나도 남자친구가 필요할지도");
static const u8 sTrainerHillTextNormal20Intro[] = _("여기서 일을 마무리하자");
static const u8 sTrainerHillTextNormal20PlayerLost[] = _("집에 가고 싶어졌지?");
static const u8 sTrainerHillTextNormal20PlayerWon[] = _("널 미안하게 만들겠어");
static const u8 sTrainerHillTextNormal20After[] = _("충분히 하지 않았어?");
static const u8 sTrainerHillTextNormal21Intro[] = _("이 구역\n최고의 미인은 나야");
static const u8 sTrainerHillTextNormal21PlayerLost[] = _("내가 강한 데는\n이유가 있지");
static const u8 sTrainerHillTextNormal21PlayerWon[] = _("오늘은 피곤해서 그래");
static const u8 sTrainerHillTextNormal21After[] = _("그래! 나 지금 화났어\n물어봐줘서 고맙네요!");
static const u8 sTrainerHillTextNormal30Intro[] = _("너 꽤 서두르나봐?");
static const u8 sTrainerHillTextNormal30PlayerLost[] = _("안됐지만 타임 오버야");
static const u8 sTrainerHillTextNormal30PlayerWon[] = _("시간이 그렇게\n신경 쓰여?");
static const u8 sTrainerHillTextNormal30After[] = _("잡담할 시간은 없어");
static const u8 sTrainerHillTextNormal31Intro[] = _("덥다...\n이 냄새는 뭐야?");
static const u8 sTrainerHillTextNormal31PlayerLost[] = _("난 지독한 냄새가 좋아");
static const u8 sTrainerHillTextNormal31PlayerWon[] = _("강한 냄새라면 뭐든 탐나");
static const u8 sTrainerHillTextNormal31After[] = _("내 후각은 평범하지 않아");

static const u8 *const sTrainerHillTextNormal[NUM_TRAINER_HILL_FLOORS][2][TRAINER_HILL_STRING_TEXT_COUNT] =
{
    {
        {sTrainerHillTextNormal00Intro, sTrainerHillTextNormal00PlayerLost, sTrainerHillTextNormal00PlayerWon, sTrainerHillTextNormal00After},
        {sTrainerHillTextNormal01Intro, sTrainerHillTextNormal01PlayerLost, sTrainerHillTextNormal01PlayerWon, sTrainerHillTextNormal01After},
    },
    {
        {sTrainerHillTextNormal10Intro, sTrainerHillTextNormal10PlayerLost, sTrainerHillTextNormal10PlayerWon, sTrainerHillTextNormal10After},
        {sTrainerHillTextNormal11Intro, sTrainerHillTextNormal11PlayerLost, sTrainerHillTextNormal11PlayerWon, sTrainerHillTextNormal11After},
    },
    {
        {sTrainerHillTextNormal20Intro, sTrainerHillTextNormal20PlayerLost, sTrainerHillTextNormal20PlayerWon, sTrainerHillTextNormal20After},
        {sTrainerHillTextNormal21Intro, sTrainerHillTextNormal21PlayerLost, sTrainerHillTextNormal21PlayerWon, sTrainerHillTextNormal21After},
    },
    {
        {sTrainerHillTextNormal30Intro, sTrainerHillTextNormal30PlayerLost, sTrainerHillTextNormal30PlayerWon, sTrainerHillTextNormal30After},
        {sTrainerHillTextNormal31Intro, sTrainerHillTextNormal31PlayerLost, sTrainerHillTextNormal31PlayerWon, sTrainerHillTextNormal31After},
    },
};

static const u8 sTrainerHillTextVariety00Intro[] = _("착한 아이에겐 선물이 있지");
static const u8 sTrainerHillTextVariety00PlayerLost[] = _("이 승리는\n네가 준 선물이야");
static const u8 sTrainerHillTextVariety00PlayerWon[] = _("이 패배는\n네게 주는 선물이야");
static const u8 sTrainerHillTextVariety00After[] = _("그럼 이만\n축하해 친구");
static const u8 sTrainerHillTextVariety01Intro[] = _("내 기합이 느껴져?");
static const u8 sTrainerHillTextVariety01PlayerLost[] = _("이거지!\n내가 생각한 대로야");
static const u8 sTrainerHillTextVariety01PlayerWon[] = _("일이 늘 생각대로\n풀리진 않네");
static const u8 sTrainerHillTextVariety01After[] = _("지금은 외롭고 슬퍼졌어");
static const u8 sTrainerHillTextVariety10Intro[] = _("안녕!\n기분 최고야?");
static const u8 sTrainerHillTextVariety10PlayerLost[] = _("너도 기분 괜찮지?");
static const u8 sTrainerHillTextVariety10PlayerWon[] = _("너 기분 좋아보이네");
static const u8 sTrainerHillTextVariety10After[] = _("네 포켓몬도\n의욕이 넘치네");
static const u8 sTrainerHillTextVariety11Intro[] = _("내 아이돌이 될 사람을\n찾고 있어");
static const u8 sTrainerHillTextVariety11PlayerLost[] = _("내 아이돌이\n이걸 봤을까?");
static const u8 sTrainerHillTextVariety11PlayerWon[] = _("넌 나에게\n치료방울 같은 존재야!");
static const u8 sTrainerHillTextVariety11After[] = _("너를 내 아이돌로 정했어");
static const u8 sTrainerHillTextVariety20Intro[] = _("굉장한 시간을\n보낼 준비는 됐어?");
static const u8 sTrainerHillTextVariety20PlayerLost[] = _("헤이 헤이!\n무슨 일이야?");
static const u8 sTrainerHillTextVariety20PlayerWon[] = _("져줄 수는 없었어?");
static const u8 sTrainerHillTextVariety20After[] = _("내 실력 봤지?");
static const u8 sTrainerHillTextVariety21Intro[] = _("바위처럼 굴러 보자고");
static const u8 sTrainerHillTextVariety21PlayerLost[] = _("바위 같은 승리가\n마음에 들어!");
static const u8 sTrainerHillTextVariety21PlayerWon[] = _("내 꿈을 깨부수다니...");
static const u8 sTrainerHillTextVariety21After[] = _("언젠가 거칠게\n굴러가고 싶어");
static const u8 sTrainerHillTextVariety30Intro[] = _("난 마이페이스로 움직여");
static const u8 sTrainerHillTextVariety30PlayerLost[] = _("어?\n내가 이긴 거야?");
static const u8 sTrainerHillTextVariety30PlayerWon[] = _("넌 심술궂은 아이 같아");
static const u8 sTrainerHillTextVariety30After[] = _("마이페이스가 딱 맞아");
static const u8 sTrainerHillTextVariety31Intro[] = _("나 매일 공부해");
static const u8 sTrainerHillTextVariety31PlayerLost[] = _("그래서 네가 지는 거야");
static const u8 sTrainerHillTextVariety31PlayerWon[] = _("널 못 이긴 것도\n무리는 아니네");
static const u8 sTrainerHillTextVariety31After[] = _("그래... 고마워");

static const u8 *const sTrainerHillTextVariety[NUM_TRAINER_HILL_FLOORS][2][TRAINER_HILL_STRING_TEXT_COUNT] =
{
    {
        {sTrainerHillTextVariety00Intro, sTrainerHillTextVariety00PlayerLost, sTrainerHillTextVariety00PlayerWon, sTrainerHillTextVariety00After},
        {sTrainerHillTextVariety01Intro, sTrainerHillTextVariety01PlayerLost, sTrainerHillTextVariety01PlayerWon, sTrainerHillTextVariety01After},
    },
    {
        {sTrainerHillTextVariety10Intro, sTrainerHillTextVariety10PlayerLost, sTrainerHillTextVariety10PlayerWon, sTrainerHillTextVariety10After},
        {sTrainerHillTextVariety11Intro, sTrainerHillTextVariety11PlayerLost, sTrainerHillTextVariety11PlayerWon, sTrainerHillTextVariety11After},
    },
    {
        {sTrainerHillTextVariety20Intro, sTrainerHillTextVariety20PlayerLost, sTrainerHillTextVariety20PlayerWon, sTrainerHillTextVariety20After},
        {sTrainerHillTextVariety21Intro, sTrainerHillTextVariety21PlayerLost, sTrainerHillTextVariety21PlayerWon, sTrainerHillTextVariety21After},
    },
    {
        {sTrainerHillTextVariety30Intro, sTrainerHillTextVariety30PlayerLost, sTrainerHillTextVariety30PlayerWon, sTrainerHillTextVariety30After},
        {sTrainerHillTextVariety31Intro, sTrainerHillTextVariety31PlayerLost, sTrainerHillTextVariety31PlayerWon, sTrainerHillTextVariety31After},
    },
};

static const u8 sTrainerHillTextUnique00Intro[] = _("음... 나...");
static const u8 sTrainerHillTextUnique00PlayerLost[] = _("오!\n음... 좋았어");
static const u8 sTrainerHillTextUnique00PlayerWon[] = _("음... 으아앙...");
static const u8 sTrainerHillTextUnique00After[] = _("음... 나 슬퍼...");
static const u8 sTrainerHillTextUnique01Intro[] = _("뜨거운 배틀에서\n질 순 없지");
static const u8 sTrainerHillTextUnique01PlayerLost[] = _("내가 널 식혀줬나?");
static const u8 sTrainerHillTextUnique01PlayerWon[] = _("히익!\n너 정말 무서운 사람이구나");
static const u8 sTrainerHillTextUnique01After[] = _("네 마음은\n얼음처럼 차갑구나...");
static const u8 sTrainerHillTextUnique10Intro[] = _("난 이 포켓몬이\n제일 좋아");
static const u8 sTrainerHillTextUnique10PlayerLost[] = _("정말 훌륭한 포켓몬이지");
static const u8 sTrainerHillTextUnique10PlayerWon[] = _("기술 때문에 헷갈렸어");
static const u8 sTrainerHillTextUnique10After[] = _("너를 스케치 하고 싶어");
static const u8 sTrainerHillTextUnique11Intro[] = _("나에겐 멋지고\n희귀한 기술이 있어");
static const u8 sTrainerHillTextUnique11PlayerLost[] = _("내 희귀한 기술\n멋지지?");
static const u8 sTrainerHillTextUnique11PlayerWon[] = _("내 기술 못 봤어?");
static const u8 sTrainerHillTextUnique11After[] = _("난 똑똑하지만\n약하기도 해...");
static const u8 sTrainerHillTextUnique20Intro[] = _("난 내 포켓몬을\n정말 아껴");
static const u8 sTrainerHillTextUnique20PlayerLost[] = _("내 포켓몬은\n뭐든 할 수 있어");
static const u8 sTrainerHillTextUnique20PlayerWon[] = _("늘 이길 수만은 없지");
static const u8 sTrainerHillTextUnique20After[] = _("처음 만난 포켓몬이\n제일 좋아");
static const u8 sTrainerHillTextUnique21Intro[] = _("누가 나한테\n포켓몬알을 줬어");
static const u8 sTrainerHillTextUnique21PlayerLost[] = _("나 초보 아니거든!");
static const u8 sTrainerHillTextUnique21PlayerWon[] = _("아 잠깐만...\n왜 진 거지!?");
static const u8 sTrainerHillTextUnique21After[] = _("바빠도 포기하지 마!");
static const u8 sTrainerHillTextUnique30Intro[] = _("포켓몬과 휴가를 왔어");
static const u8 sTrainerHillTextUnique30PlayerLost[] = _("여행하면서\n배틀하는 건 멋져");
static const u8 sTrainerHillTextUnique30PlayerWon[] = _("으아앙!\n내 희귀한 포켓몬이!");
static const u8 sTrainerHillTextUnique30After[] = _("또 다른 휴가를 떠나야지");
static const u8 sTrainerHillTextUnique31Intro[] = _("이기는 방법을 보여줄게!");
static const u8 sTrainerHillTextUnique31PlayerLost[] = _("이제 어떻게 하는지\n알겠지?");
static const u8 sTrainerHillTextUnique31PlayerWon[] = _("그래\n그렇게 하는 거야");
static const u8 sTrainerHillTextUnique31After[] = _("날 이겼구나?\n잘했어");

static const u8 *const sTrainerHillTextUnique[NUM_TRAINER_HILL_FLOORS][2][TRAINER_HILL_STRING_TEXT_COUNT] =
{
    {
        {sTrainerHillTextUnique00Intro, sTrainerHillTextUnique00PlayerLost, sTrainerHillTextUnique00PlayerWon, sTrainerHillTextUnique00After},
        {sTrainerHillTextUnique01Intro, sTrainerHillTextUnique01PlayerLost, sTrainerHillTextUnique01PlayerWon, sTrainerHillTextUnique01After},
    },
    {
        {sTrainerHillTextUnique10Intro, sTrainerHillTextUnique10PlayerLost, sTrainerHillTextUnique10PlayerWon, sTrainerHillTextUnique10After},
        {sTrainerHillTextUnique11Intro, sTrainerHillTextUnique11PlayerLost, sTrainerHillTextUnique11PlayerWon, sTrainerHillTextUnique11After},
    },
    {
        {sTrainerHillTextUnique20Intro, sTrainerHillTextUnique20PlayerLost, sTrainerHillTextUnique20PlayerWon, sTrainerHillTextUnique20After},
        {sTrainerHillTextUnique21Intro, sTrainerHillTextUnique21PlayerLost, sTrainerHillTextUnique21PlayerWon, sTrainerHillTextUnique21After},
    },
    {
        {sTrainerHillTextUnique30Intro, sTrainerHillTextUnique30PlayerLost, sTrainerHillTextUnique30PlayerWon, sTrainerHillTextUnique30After},
        {sTrainerHillTextUnique31Intro, sTrainerHillTextUnique31PlayerLost, sTrainerHillTextUnique31PlayerWon, sTrainerHillTextUnique31After},
    },
};

static const u8 sTrainerHillTextExpert00Intro[] = _("우린 어떤 타입도\n상대할 수 있어");
static const u8 sTrainerHillTextExpert00PlayerLost[] = _("제법 괜찮게 했지!?");
static const u8 sTrainerHillTextExpert00PlayerWon[] = _("우리 작전이\n별로였나 봐...");
static const u8 sTrainerHillTextExpert00After[] = _("우린 훨씬 더\n단련해야 해");
static const u8 sTrainerHillTextExpert01Intro[] = _("어떤 트레이너의\n도전도 받겠어");
static const u8 sTrainerHillTextExpert01PlayerLost[] = _("내 작전은\n완벽하게 먹힐 거야!");
static const u8 sTrainerHillTextExpert01PlayerWon[] = _("아냐\n이게 아닌데...");
static const u8 sTrainerHillTextExpert01After[] = _("트레이너스쿨에\n가야 할지도");
static const u8 sTrainerHillTextExpert10Intro[] = _("도움 없이도\n이길 수 있어");
static const u8 sTrainerHillTextExpert10PlayerLost[] = _("당연히 내가 이기지");
static const u8 sTrainerHillTextExpert10PlayerWon[] = _("지니까\n작아지기를 쓴 기분이야...");
static const u8 sTrainerHillTextExpert10After[] = _("좋은 선생님이 있니?");
static const u8 sTrainerHillTextExpert11Intro[] = _("난 도우미 같은 건\n필요 없어!");
static const u8 sTrainerHillTextExpert11PlayerLost[] = _("미안!\n네겐 안됐네");
static const u8 sTrainerHillTextExpert11PlayerWon[] = _("정말 믿을 수 없는\n발버둥이었어!");
static const u8 sTrainerHillTextExpert11After[] = _("네 포켓몬 선생님이\n되어줄까?");
static const u8 sTrainerHillTextExpert20Intro[] = _("저런\n이 승부는 널 위한 거야");
static const u8 sTrainerHillTextExpert20PlayerLost[] = _("저런\n봤니?");
static const u8 sTrainerHillTextExpert20PlayerWon[] = _("저런\n미안");
static const u8 sTrainerHillTextExpert20After[] = _("네 할머니도 강하시니?");
static const u8 sTrainerHillTextExpert21Intro[] = _("저런\n널 위해 이겨줄게");
static const u8 sTrainerHillTextExpert21PlayerLost[] = _("저런\n나중에 파티를 열자");
static const u8 sTrainerHillTextExpert21PlayerWon[] = _("저런\n실망시켜서 미안해");
static const u8 sTrainerHillTextExpert21After[] = _("네 할아버지도 멋지시니?");
static const u8 sTrainerHillTextExpert30Intro[] = _("으아앙!\n너무 신나!");
static const u8 sTrainerHillTextExpert30PlayerLost[] = _("으아앙!\n이겨서 기뻐!");
static const u8 sTrainerHillTextExpert30PlayerWon[] = _("으아앙!\n져서 슬퍼!");
static const u8 sTrainerHillTextExpert30After[] = _("으아앙!\n저리 가!");
static const u8 sTrainerHillTextExpert31Intro[] = _("와하하하!\n넌 날 막을 수 없다!");
static const u8 sTrainerHillTextExpert31PlayerLost[] = _("와우!\n나 멋지고 끝내주지?");
static const u8 sTrainerHillTextExpert31PlayerWon[] = _("난 전혀 멋지지 않아...");
static const u8 sTrainerHillTextExpert31After[] = _("헤헤헤\n굉장한 배틀이었어!");

static const u8 *const sTrainerHillTextExpert[NUM_TRAINER_HILL_FLOORS][2][TRAINER_HILL_STRING_TEXT_COUNT] =
{
    {
        {sTrainerHillTextExpert00Intro, sTrainerHillTextExpert00PlayerLost, sTrainerHillTextExpert00PlayerWon, sTrainerHillTextExpert00After},
        {sTrainerHillTextExpert01Intro, sTrainerHillTextExpert01PlayerLost, sTrainerHillTextExpert01PlayerWon, sTrainerHillTextExpert01After},
    },
    {
        {sTrainerHillTextExpert10Intro, sTrainerHillTextExpert10PlayerLost, sTrainerHillTextExpert10PlayerWon, sTrainerHillTextExpert10After},
        {sTrainerHillTextExpert11Intro, sTrainerHillTextExpert11PlayerLost, sTrainerHillTextExpert11PlayerWon, sTrainerHillTextExpert11After},
    },
    {
        {sTrainerHillTextExpert20Intro, sTrainerHillTextExpert20PlayerLost, sTrainerHillTextExpert20PlayerWon, sTrainerHillTextExpert20After},
        {sTrainerHillTextExpert21Intro, sTrainerHillTextExpert21PlayerLost, sTrainerHillTextExpert21PlayerWon, sTrainerHillTextExpert21After},
    },
    {
        {sTrainerHillTextExpert30Intro, sTrainerHillTextExpert30PlayerLost, sTrainerHillTextExpert30PlayerWon, sTrainerHillTextExpert30After},
        {sTrainerHillTextExpert31Intro, sTrainerHillTextExpert31PlayerLost, sTrainerHillTextExpert31PlayerWon, sTrainerHillTextExpert31After},
    },
};

static const u8 *const (*const sTrainerHillTextTables[])[2][TRAINER_HILL_STRING_TEXT_COUNT] =
{
    sTrainerHillTextNormal,
    sTrainerHillTextVariety,
    sTrainerHillTextUnique,
    sTrainerHillTextExpert,
};

/* End generated Trainer Hill string text tables. */

// Unused.
static const u8 *const sFloorStrings[] =
{
    gText_TrainerHill1F,
    gText_TrainerHill2F,
    gText_TrainerHill3F,
    gText_TrainerHill4F,
};

static void (* const sHillFunctions[])(void) =
{
    [TRAINER_HILL_FUNC_START]                 = TrainerHillStartChallenge,
    [TRAINER_HILL_FUNC_GET_OWNER_STATE]       = GetOwnerState,
    [TRAINER_HILL_FUNC_GIVE_PRIZE]            = GiveChallengePrize,
    [TRAINER_HILL_FUNC_CHECK_FINAL_TIME]      = CheckFinalTime,
    [TRAINER_HILL_FUNC_RESUME_TIMER]          = TrainerHillResumeTimer,
    [TRAINER_HILL_FUNC_SET_LOST]              = TrainerHillSetPlayerLost,
    [TRAINER_HILL_FUNC_GET_CHALLENGE_STATUS]  = TrainerHillGetChallengeStatus,
    [TRAINER_HILL_FUNC_GET_CHALLENGE_TIME]    = BufferChallengeTime,
    [TRAINER_HILL_FUNC_GET_ALL_FLOORS_USED]   = GetAllFloorsUsed,
    [TRAINER_HILL_FUNC_GET_IN_EREADER_MODE]   = GetInEReaderMode,
    [TRAINER_HILL_FUNC_IN_CHALLENGE]          = IsTrainerHillChallengeActive,
    [TRAINER_HILL_FUNC_POST_BATTLE_TEXT]      = ShowTrainerHillPostBattleText,
    [TRAINER_HILL_FUNC_SET_ALL_TRAINER_FLAGS] = SetAllTrainerFlags,
    [TRAINER_HILL_FUNC_GET_GAME_SAVED]        = GetGameSaved,
    [TRAINER_HILL_FUNC_SET_GAME_SAVED]        = SetGameSaved,
    [TRAINER_HILL_FUNC_CLEAR_GAME_SAVED]      = ClearGameSaved,
    [TRAINER_HILL_FUNC_GET_WON]               = GetChallengeWon,
    [TRAINER_HILL_FUNC_SET_TAG]               = TrainerHillSetTag,
};

static const u8 *const sTagMatchStrings[] =
{
    gText_NormalTagMatch,
    gText_VarietyTagMatch,
    gText_UniqueTagMatch,
    gText_ExpertTagMatch,
};

static const struct ObjectEventTemplate sTrainerObjectEventTemplate =
{
    .graphicsId = OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL,
    .elevation = 3,
    .movementType = MOVEMENT_TYPE_LOOK_AROUND,
    .movementRangeX = 1,
    .movementRangeY = 1,
    .trainerType = TRAINER_TYPE_NORMAL,
};

static const u32 sNextFloorMapNum[NUM_TRAINER_HILL_FLOORS] = 
{
    MAP_NUM(TRAINER_HILL_2F), 
    MAP_NUM(TRAINER_HILL_3F), 
    MAP_NUM(TRAINER_HILL_4F), 
    MAP_NUM(TRAINER_HILL_ROOF)
};
static const u8 sTrainerPartySlots[][PARTY_SIZE / 2] = 
{
    {0, 1, 2}, 
    {3, 4, 5}
};

// code
void CallTrainerHillFunction(void)
{
    SetUpDataStruct();
    sHillFunctions[gSpecialVar_0x8004]();
    FreeDataStruct();
}

void ResetTrainerHillResults(void)
{
    s32 i;

    gSaveBlock2Ptr->frontier.savedGame = 0;
    gSaveBlock2Ptr->frontier.unk_EF9 = 0;
    gSaveBlock1Ptr->trainerHill.bestTime = 0;
    for (i = 0; i < 4; i++)
        SetTimerValue(&gSaveBlock1Ptr->trainerHillTimes[i], HILL_MAX_TIME);
}

static u8 GetFloorId(void)
{
    return gMapHeader.mapLayoutId - LAYOUT_TRAINER_HILL_1F;
}

u8 GetTrainerHillOpponentClass(u16 trainerId)
{
    u8 id = trainerId - 1;

    return gFacilityClassToTrainerClass[sRoomTrainers->facilityClass[id]];
}

void GetTrainerHillTrainerName(u8 *dst, u16 trainerId)
{
    s32 i;
    u8 id = trainerId - 1;

    for (i = 0; i < HILL_TRAINER_NAME_LENGTH; i++)
        dst[i] = sRoomTrainers->name[id][i];
}

u8 GetTrainerHillTrainerFrontSpriteId(u16 trainerId)
{
    u8 id, facilityClass;

    SetUpDataStruct();
    id = trainerId - 1;
    facilityClass = sHillData->floors[sHillData->floorId].trainers[id].facilityClass;
    FreeDataStruct();

    return gFacilityClassToPicIndex[facilityClass];
}

void InitTrainerHillBattleStruct(void)
{
    s32 i, j;

    SetUpDataStruct();
    sRoomTrainers = AllocZeroed(sizeof(*sRoomTrainers));

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < HILL_TRAINER_NAME_LENGTH; j++)
        {
            sRoomTrainers->name[i][j] = sHillData->floors[sHillData->floorId].trainers[i].name[j];
        }
        sRoomTrainers->facilityClass[i] = sHillData->floors[sHillData->floorId].trainers[i].facilityClass;
    }
    SetTrainerHillVBlankCounter(&gSaveBlock1Ptr->trainerHill.timer);
    FreeDataStruct();
}

void FreeTrainerHillBattleStruct(void)
{
    if (sRoomTrainers != NULL)
        FREE_AND_SET_NULL(sRoomTrainers);
}

static void SetUpDataStruct(void)
{
    if (sHillData == NULL)
    {
        sHillData = AllocZeroed(sizeof(*sHillData));
        sHillData->floorId = gMapHeader.mapLayoutId - LAYOUT_TRAINER_HILL_1F;
        CpuCopy32(sDataPerTag[gSaveBlock1Ptr->trainerHill.tag], &sHillData->tag, sizeof(sHillData->tag) + 4 * sizeof(struct TrHillFloor));
        nullsub_2();
    }
}

static void FreeDataStruct(void)
{
    if (sHillData != NULL)
        FREE_AND_SET_NULL(sHillData);
}


static const u8 *GetTrainerHillTrainerTextString(u8 which, u8 floorId, u8 trainerId)
{
    u8 textId;

    switch (which)
    {
    case TRAINER_HILL_TEXT_INTRO:
        textId = 0;
        break;
    case TRAINER_HILL_TEXT_PLAYER_LOST:
        textId = 1;
        break;
    case TRAINER_HILL_TEXT_PLAYER_WON:
        textId = 2;
        break;
    case TRAINER_HILL_TEXT_AFTER:
        textId = 3;
        break;
    default:
        return NULL;
    }

    if (gSaveBlock1Ptr->trainerHill.tag >= ARRAY_COUNT(sTrainerHillTextTables))
        return NULL;
    if (floorId >= NUM_TRAINER_HILL_FLOORS || trainerId >= 2)
        return NULL;

    return sTrainerHillTextTables[gSaveBlock1Ptr->trainerHill.tag][floorId][trainerId][textId];
}

void CopyTrainerHillTrainerText(u8 which, u16 trainerId)
{
    u8 id, floorId;
    const u8 *text;

    SetUpDataStruct();
    floorId = GetFloorId();
    id = trainerId - 1;
    text = GetTrainerHillTrainerTextString(which, floorId, id);

    if (text != NULL)
    {
        StringCopy(gStringVar4, text);
    }
    else
    {
        switch (which)
        {
        case TRAINER_HILL_TEXT_INTRO:
            FrontierSpeechToString(sHillData->floors[floorId].trainers[id].speechBefore);
            break;
        case TRAINER_HILL_TEXT_PLAYER_LOST:
            FrontierSpeechToString(sHillData->floors[floorId].trainers[id].speechWin);
            break;
        case TRAINER_HILL_TEXT_PLAYER_WON:
            FrontierSpeechToString(sHillData->floors[floorId].trainers[id].speechLose);
            break;
        case TRAINER_HILL_TEXT_AFTER:
            FrontierSpeechToString(sHillData->floors[floorId].trainers[id].speechAfter);
            break;
        }
    }

    FreeDataStruct();
}

static void TrainerHillStartChallenge(void)
{
    nullsub_2();
    if (!ReadTrainerHillAndValidate())
        gSaveBlock1Ptr->trainerHill.field_3D6E_0f = 1;
    else
        gSaveBlock1Ptr->trainerHill.field_3D6E_0f = 0;

    gSaveBlock1Ptr->trainerHill.unk_3D6C = 0;
    SetTrainerHillVBlankCounter(&gSaveBlock1Ptr->trainerHill.timer);
    gSaveBlock1Ptr->trainerHill.timer = 0;
    gSaveBlock1Ptr->trainerHill.spokeToOwner = 0;
    gSaveBlock1Ptr->trainerHill.checkedFinalTime = 0;
    gSaveBlock1Ptr->trainerHill.maybeECardScanDuringChallenge = 0;
    gSaveBlock2Ptr->frontier.trainerFlags = 0;
    gBattleOutcome = 0;
    gSaveBlock1Ptr->trainerHill.receivedPrize = 0;
}

static void GetOwnerState(void)
{
    ClearTrainerHillVBlankCounter();
    gSpecialVar_Result = 0;
    if (gSaveBlock1Ptr->trainerHill.spokeToOwner)
        gSpecialVar_Result++;
    if (gSaveBlock1Ptr->trainerHill.receivedPrize && gSaveBlock1Ptr->trainerHill.checkedFinalTime)
        gSpecialVar_Result++;

    gSaveBlock1Ptr->trainerHill.spokeToOwner = TRUE;
}

static void GiveChallengePrize(void)
{
    u16 itemId = GetPrizeItemId();

    if (sHillData->tag.numFloors != NUM_TRAINER_HILL_FLOORS || gSaveBlock1Ptr->trainerHill.receivedPrize)
    {
        gSpecialVar_Result = 2;
    }
    else if (AddBagItem(itemId, 1) == TRUE)
    {
        CopyItemName(itemId, gStringVar2);
        gSaveBlock1Ptr->trainerHill.receivedPrize = TRUE;
        gSaveBlock2Ptr->frontier.unk_EF9 = 0;
        gSpecialVar_Result = 0;
    }
    else
    {
        gSpecialVar_Result = 1;
    }
}

// If bestTime > timer, the challenge was completed faster and its a new record
// Otherwise the owner says it was a slow time and to complete it faster next time
static void CheckFinalTime(void)
{
    if (gSaveBlock1Ptr->trainerHill.checkedFinalTime)
    {
        gSpecialVar_Result = 2;
    }
    else if (GetTimerValue(&gSaveBlock1Ptr->trainerHill.bestTime) > gSaveBlock1Ptr->trainerHill.timer)
    {
        SetTimerValue(&gSaveBlock1Ptr->trainerHill.bestTime, gSaveBlock1Ptr->trainerHill.timer);
        gSaveBlock1Ptr->trainerHillTimes[gSaveBlock1Ptr->trainerHill.tag] = gSaveBlock1Ptr->trainerHill.bestTime;
        gSpecialVar_Result = 0;
    }
    else
    {
        gSpecialVar_Result = 1;
    }

    gSaveBlock1Ptr->trainerHill.checkedFinalTime = TRUE;
}

static void TrainerHillResumeTimer(void)
{
    if (!gSaveBlock1Ptr->trainerHill.spokeToOwner)
    {
        if (gSaveBlock1Ptr->trainerHill.timer >= HILL_MAX_TIME)
            gSaveBlock1Ptr->trainerHill.timer = HILL_MAX_TIME;
        else
            SetTrainerHillVBlankCounter(&gSaveBlock1Ptr->trainerHill.timer);
    }
}

static void TrainerHillSetPlayerLost(void)
{
    gSaveBlock1Ptr->trainerHill.hasLost = TRUE;
}

static void TrainerHillGetChallengeStatus(void)
{
    if (gSaveBlock1Ptr->trainerHill.hasLost)
    {
        // The player lost their last match.
        gSaveBlock1Ptr->trainerHill.hasLost = FALSE;
        gSpecialVar_Result = TRAINER_HILL_PLAYER_STATUS_LOST;
    }
    else if (gSaveBlock1Ptr->trainerHill.maybeECardScanDuringChallenge)
    {
        // Unreachable code. Something relating to eCards?
        gSaveBlock1Ptr->trainerHill.maybeECardScanDuringChallenge = 0;
        gSpecialVar_Result = TRAINER_HILL_PLAYER_STATUS_ECARD_SCANNED;
    }
    else
    {
        // Continue playing.
        gSpecialVar_Result = TRAINER_HILL_PLAYER_STATUS_NORMAL;
    }
}

static void BufferChallengeTime(void)
{
    s32 total, minutes, secondsWhole, secondsFraction;

    total = gSaveBlock1Ptr->trainerHill.timer;
    if (total >= HILL_MAX_TIME)
        total = HILL_MAX_TIME;

    minutes = total / (60 * 60);
    total %= (60 * 60);
    secondsWhole = total / 60;
    total %= 60;
    secondsFraction = (total * 168) / 100;

    ConvertIntToDecimalStringN(gStringVar1, minutes, STR_CONV_MODE_RIGHT_ALIGN, 2);
    ConvertIntToDecimalStringN(gStringVar2, secondsWhole, STR_CONV_MODE_RIGHT_ALIGN, 2);
    ConvertIntToDecimalStringN(gStringVar3, secondsFraction, STR_CONV_MODE_LEADING_ZEROS, 2);
}

// Returns TRUE if all 4 floors are used
// Returns FALSE otherwise, and buffers the number of floors used
// The only time fewer than all 4 floors are used is for the JP-exclusive E-Reader and Default modes
static void GetAllFloorsUsed(void)
{
    SetUpDataStruct();
    if (sHillData->tag.numFloors != NUM_TRAINER_HILL_FLOORS)
    {
        ConvertIntToDecimalStringN(gStringVar1, sHillData->tag.numFloors, STR_CONV_MODE_LEFT_ALIGN, 1);
        gSpecialVar_Result = FALSE;
    }
    else
    {
        gSpecialVar_Result = TRUE;
    }

    FreeDataStruct();
}

// May have been dummied. Every time this is called a conditional for var result occurs afterwards
// Relation to E-Reader is an assumption, most dummied Trainer Hill code seems to be JP E-Reader mode related
static void GetInEReaderMode(void)
{
    SetUpDataStruct();
    gSpecialVar_Result = FALSE;
    FreeDataStruct();
}

bool8 InTrainerHillChallenge(void)
{
    if (VarGet(VAR_TRAINER_HILL_IS_ACTIVE) == 0)
        return FALSE;
    else if (gSaveBlock1Ptr->trainerHill.spokeToOwner)
        return FALSE;
    else if (GetCurrentTrainerHillMapId() != 0)
        return TRUE;
    else
        return FALSE;
}

static void IsTrainerHillChallengeActive(void)
{
    if (!InTrainerHillChallenge())
        gSpecialVar_Result = FALSE;
    else
        gSpecialVar_Result = TRUE;
}

void nullsub_129(void)
{

}

static void nullsub_2(void)
{

}

void PrintOnTrainerHillRecordsWindow(void)
{
    s32 i, x, y;
    u32 total, minutes, secondsWhole, secondsFraction;

    SetUpDataStruct();
    FillWindowPixelBuffer(0, PIXEL_FILL(0));
    x = GetStringCenterAlignXOffset(1, gText_TimeBoard, 0xD0);
    AddTextPrinterParameterized3(0, 1, x, 2, sRecordWinColors, TEXT_SPEED_FF, gText_TimeBoard);

    y = 18;
    for (i = 0; i < 4; i++)
    {
        AddTextPrinterParameterized3(0, 1, 0, y, sRecordWinColors, TEXT_SPEED_FF, sTagMatchStrings[i]);
        y += 15;
        total = GetTimerValue(&gSaveBlock1Ptr->trainerHillTimes[i]);
        minutes = total / (60 * 60);
        total %= (60 * 60);
        ConvertIntToDecimalStringN(gStringVar1, minutes, STR_CONV_MODE_RIGHT_ALIGN, 2);
        secondsWhole = total / 60;
        total %= 60;
        ConvertIntToDecimalStringN(gStringVar2, secondsWhole, STR_CONV_MODE_RIGHT_ALIGN, 2);
        secondsFraction = (total * 168) / 100;
        ConvertIntToDecimalStringN(gStringVar3, secondsFraction, STR_CONV_MODE_LEADING_ZEROS, 2);
        StringExpandPlaceholders(StringCopy(gStringVar4, gText_TimeCleared), gText_XMinYDotZSec);
        x = GetStringRightAlignXOffset(1, gStringVar4, 0xD0);
        AddTextPrinterParameterized3(0, 1, x, y, sRecordWinColors, TEXT_SPEED_FF, gStringVar4);
        y += 17;
    }

    PutWindowTilemap(0);
    CopyWindowToVram(0, 3);
    FreeDataStruct();
}

// Leftover from Fire Red / Leaf Green as in these games,
// the timer had to be xored by the encryption key in Sav2.
static u32 GetTimerValue(u32 *src)
{
    return *src;
}

static void SetTimerValue(u32 *dst, u32 val)
{
    *dst = val;
}

void LoadTrainerHillObjectEventTemplates(void)
{
    u8 i, floorId;
    struct ObjectEventTemplate *eventTemplates = gSaveBlock1Ptr->objectEventTemplates;

    if (!LoadTrainerHillFloorObjectEventScripts())
        return;

    SetUpDataStruct();
    for (i = 0; i < 2; i++)
        gSaveBlock2Ptr->frontier.trainerIds[i] = 0xFFFF;
    CpuFill32(0, gSaveBlock1Ptr->objectEventTemplates, sizeof(gSaveBlock1Ptr->objectEventTemplates));

    floorId = GetFloorId();
    for (i = 0; i < 2; i++)
    {
        u8 bits;

        eventTemplates[i] = sTrainerObjectEventTemplate;
        eventTemplates[i].localId = i + 1;
        eventTemplates[i].graphicsId = FacilityClassToGraphicsId(sHillData->floors[floorId].trainers[i].facilityClass);
        eventTemplates[i].x = sHillData->floors[floorId].display.coords[i] & 0xF;
        eventTemplates[i].y = ((sHillData->floors[floorId].display.coords[i] >> 4) & 0xF) + 5;
        bits = i << 2;
        eventTemplates[i].movementType = ((sHillData->floors[floorId].display.direction >> bits) & 0xF) + MOVEMENT_TYPE_FACE_UP;
        eventTemplates[i].trainerRange_berryTreeId = (sHillData->floors[floorId].display.range >> bits) & 0xF;
        eventTemplates[i].script = TrainerHill_EventScript_TrainerBattle;
        gSaveBlock2Ptr->frontier.trainerIds[i] = i + 1;
    }

    FreeDataStruct();
}

bool32 LoadTrainerHillFloorObjectEventScripts(void)
{
    SetUpDataStruct();
    // Something may have been dummied here
    FreeDataStruct();
    return TRUE;
}

static u16 GetMetatileForFloor(u8 floorId, u32 x, u32 y, u32 stride) // stride is always 16
{
    bool8 impassable;
    u16 metatile;
    u16 elevation;

    impassable = (sHillData->floors[floorId].display.collisionData[y] >> (15 - x) & 1);
    metatile = sHillData->floors[floorId].display.metatileData[stride * y + x] + 0x200;
    elevation = 0x3000;

    return (((impassable << 10) & METATILE_COLLISION_MASK) | elevation) | (metatile & METATILE_ID_MASK);
}

void GenerateTrainerHillFloorLayout(u16 *mapArg)
{
    s32 i, j;
    u16 *src, *dst;
    u8 mapId = GetCurrentTrainerHillMapId();

    if (mapId == TRAINER_HILL_ENTRANCE)
    {
        InitMapFromSavedGame();
        return;
    }

    SetUpDataStruct();
    if (mapId == TRAINER_HILL_ROOF)
    {
        InitMapFromSavedGame();
        FreeDataStruct();
        return;
    }

    mapId = GetFloorId();
    src = gMapHeader.mapLayout->map;
    gBackupMapLayout.map = mapArg;
    gBackupMapLayout.width = 31;
    gBackupMapLayout.height = 35;
    dst = mapArg + 224;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 16; j++)
            dst[j] = src[j];
        dst += 31;
        src += 16;
    }

    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 16; j++)
            dst[j] = GetMetatileForFloor(mapId, j, i, 0x10);
        dst += 31;
    }

    RunOnLoadMapScript();
    FreeDataStruct();
}

bool32 InTrainerHill(void)
{
    bool32 ret;

    if (gMapHeader.mapLayoutId == LAYOUT_TRAINER_HILL_1F
        || gMapHeader.mapLayoutId == LAYOUT_TRAINER_HILL_2F
        || gMapHeader.mapLayoutId == LAYOUT_TRAINER_HILL_3F
        || gMapHeader.mapLayoutId == LAYOUT_TRAINER_HILL_4F)
        ret = TRUE;
    else
        ret = FALSE;

    return ret;
}

u8 GetCurrentTrainerHillMapId(void)
{
    u8 mapId;

    if (gMapHeader.mapLayoutId == LAYOUT_TRAINER_HILL_1F)
        mapId = TRAINER_HILL_1F;
    else if (gMapHeader.mapLayoutId == LAYOUT_TRAINER_HILL_2F)
        mapId = TRAINER_HILL_2F;
    else if (gMapHeader.mapLayoutId == LAYOUT_TRAINER_HILL_3F)
        mapId = TRAINER_HILL_3F;
    else if (gMapHeader.mapLayoutId == LAYOUT_TRAINER_HILL_4F)
        mapId = TRAINER_HILL_4F;
    else if (gMapHeader.mapLayoutId == LAYOUT_TRAINER_HILL_ROOF)
        mapId = TRAINER_HILL_ROOF;
    else if (gMapHeader.mapLayoutId == LAYOUT_TRAINER_HILL_ENTRANCE)
        mapId = TRAINER_HILL_ENTRANCE;
    else
        mapId = 0;

    return mapId;
}

// Unused
static bool32 OnTrainerHillRoof(void)
{
    bool32 onRoof;

    if (gMapHeader.mapLayoutId == LAYOUT_TRAINER_HILL_ROOF)
        onRoof = TRUE;
    else
        onRoof = FALSE;

    return onRoof;
}

const struct WarpEvent* SetWarpDestinationTrainerHill4F(void)
{
    const struct MapHeader *header = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(TRAINER_HILL_4F), MAP_NUM(TRAINER_HILL_4F));

    return &header->events->warps[1];
}

// For warping from the roof in challenges where the 4F is not the final challenge floor
// This would only occur in the JP-exclusive Default and E-Reader challenges
const struct WarpEvent* SetWarpDestinationTrainerHillFinalFloor(u8 warpEventId)
{
    u8 numFloors;
    const struct MapHeader *header;

    if (warpEventId == 1)
        return &gMapHeader.events->warps[1];

    numFloors = GetNumFloorsInTrainerHillChallenge();
    if (numFloors == 0 || numFloors > NUM_TRAINER_HILL_FLOORS)
        numFloors = NUM_TRAINER_HILL_FLOORS;

    header = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(TRAINER_HILL_4F), sNextFloorMapNum[numFloors - 1]);
    return &header->events->warps[0];
}

u16 LocalIdToHillTrainerId(u8 localId)
{
    return gSaveBlock2Ptr->frontier.trainerIds[localId - 1];
}

bool8 GetHillTrainerFlag(u8 objectEventId)
{
    u32 floorId = GetFloorId() * 2;
    u8 bitId = gObjectEvents[objectEventId].localId - 1 + floorId;

    return gSaveBlock2Ptr->frontier.trainerFlags & gBitTable[bitId];
}

void SetHillTrainerFlag(void)
{
    u8 i;
    u8 floorId = GetFloorId() * 2;

    for (i = 0; i < 2; i++)
    {
        if (gSaveBlock2Ptr->frontier.trainerIds[i] == gTrainerBattleOpponent_A)
        {
            gSaveBlock2Ptr->frontier.trainerFlags |= gBitTable[floorId + i];
            break;
        }
    }

    if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
    {
        for (i = 0; i < 2; i++)
        {
            if (gSaveBlock2Ptr->frontier.trainerIds[i] == gTrainerBattleOpponent_B)
            {
                gSaveBlock2Ptr->frontier.trainerFlags |= gBitTable[floorId + i];
                break;
            }
        }
    }
}

const u8 *GetTrainerHillTrainerScript(void)
{
    return TrainerHill_EventScript_TrainerBattle;
}

static void ShowTrainerHillPostBattleText(void)
{
    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_AFTER, gSpecialVar_LastTalked);
    ShowFieldMessageFromBuffer();
}

static void CreateNPCTrainerHillParty(u16 trainerId, u8 firstMonId)
{
    u8 trId, level;
    s32 i, floorId, partySlot;

    if (trainerId == 0 || trainerId > 2)
        return;

    trId = trainerId - 1;
    SetUpDataStruct();
    level = GetHighestLevelInPlayerParty();
    floorId = GetFloorId();
    for (i = firstMonId, partySlot = 0; i < firstMonId + 3; i++, partySlot++)
    {
        u8 id = sTrainerPartySlots[trId][partySlot];
        struct Pokemon *mon = &gEnemyParty[i];

        CreateBattleTowerMon(mon, &sHillData->floors[floorId].trainers[trId].mons[id]);
        SetTrainerHillMonLevel(mon, level);
    }

    FreeDataStruct();
}

void FillHillTrainerParty(void)
{
    ZeroEnemyPartyMons();
    CreateNPCTrainerHillParty(gTrainerBattleOpponent_A, 0);
}

void FillHillTrainersParties(void)
{
    ZeroEnemyPartyMons();
    CreateNPCTrainerHillParty(gTrainerBattleOpponent_A, 0);
    CreateNPCTrainerHillParty(gTrainerBattleOpponent_B, 3);
}

// This function is unused, but my best guess is
// it was supposed to return AI scripts for trainer
// hill trainers.
u32 GetTrainerHillAIFlags(void)
{
    return (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY);
}

u8 GetTrainerEncounterMusicIdInTrainerHill(u16 trainerId)
{
    s32 i;
    u8 trId, facilityClass;

    SetUpDataStruct();
    trId = trainerId - 1;
    facilityClass = sHillData->floors[sHillData->floorId].trainers[trId].facilityClass;
    FreeDataStruct();

    for (i = 0; i < ARRAY_COUNT(sTrainerClassesAndMusic); i++)
    {
        if (sTrainerClassesAndMusic[i].trainerClass == gFacilityClassToTrainerClass[facilityClass])
            return sTrainerClassesAndMusic[i].musicId;
    }

    return 0;
}

static void SetTrainerHillMonLevel(struct Pokemon *mon, u8 level)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    u32 exp = gExperienceTables[gBaseStats[species].growthRate][level];

    SetMonData(mon, MON_DATA_EXP, &exp);
    SetMonData(mon, MON_DATA_LEVEL, &level);
    CalculateMonStats(mon);
}

u8 GetNumFloorsInTrainerHillChallenge(void)
{
    u8 floors;

    SetUpDataStruct();
    floors = sHillData->tag.numFloors;
    FreeDataStruct();

    return floors;
}

static void SetAllTrainerFlags(void)
{
    gSaveBlock2Ptr->frontier.trainerFlags = 0xFF;
}

// Palette never loaded, OnTrainerHillEReaderChallengeFloor always FALSE
void TryLoadTrainerHillEReaderPalette(void)
{
    if (OnTrainerHillEReaderChallengeFloor() == TRUE)
        LoadPalette(sEReader_Pal, 0x70, 0x20);
}

static void GetGameSaved(void)
{
    gSpecialVar_Result = gSaveBlock2Ptr->frontier.savedGame;
}

static void SetGameSaved(void)
{
    gSaveBlock2Ptr->frontier.savedGame = TRUE;
}

static void ClearGameSaved(void)
{
    gSaveBlock2Ptr->frontier.savedGame = FALSE;
}

// Always FALSE
bool32 OnTrainerHillEReaderChallengeFloor(void)
{
    if (!InTrainerHillChallenge() || GetCurrentTrainerHillMapId() == TRAINER_HILL_ENTRANCE)
        return FALSE;

    GetInEReaderMode();
    if (gSpecialVar_Result == FALSE)
        return FALSE;
    else
        return TRUE;
}

static void GetChallengeWon(void)
{
    if (gSaveBlock1Ptr->trainerHill.hasLost)
        gSpecialVar_Result = FALSE;
    else
        gSpecialVar_Result = TRUE;
}

static void TrainerHillSetTag(void)
{
    gSaveBlock1Ptr->trainerHill.tag = gSpecialVar_0x8005;
    gSaveBlock1Ptr->trainerHill.bestTime = gSaveBlock1Ptr->trainerHillTimes[gSpecialVar_0x8005];
}

static u8 GetPrizeListId(bool8 maxTrainers)
{
    u8 prizeListId, i, modBy;

    prizeListId = 0;
    for (i = 0; i < NUM_TRAINER_HILL_FLOORS; i++)
    {
        prizeListId ^= sHillData->floors[i].trainerNum1 & 0x1F;
        prizeListId ^= sHillData->floors[i].trainerNum2 & 0x1F;
    }

    // Not possible to win TMs with fewer than 8 trainers
    if (maxTrainers)
        modBy = NUM_TRAINER_HILL_PRIZE_LISTS;
    else
        modBy = NUM_TRAINER_HILL_PRIZE_LISTS / 2;

    prizeListId %= modBy;
    return prizeListId;
}

static u16 GetPrizeItemId(void)
{
    u8 i;
    const u16 *prizeList;
    s32 var = 0, prizeListSetId, minutes, id;

    for (i = 0; i < NUM_TRAINER_HILL_FLOORS; i++)
    {
        var += sHillData->floors[i].trainerNum1;
        var += sHillData->floors[i].trainerNum2;
    }

    prizeListSetId = var / 256;
    prizeListSetId %= 2;
    if (FlagGet(FLAG_SYS_GAME_CLEAR) && sHillData->tag.numTrainers == NUM_TRAINER_HILL_TRAINERS)
        i = GetPrizeListId(TRUE);
    else
        i = GetPrizeListId(FALSE);

    if (gSaveBlock1Ptr->trainerHill.tag == HILL_TAG_EXPERT)
        i = (i + 1) % NUM_TRAINER_HILL_PRIZE_LISTS;

    prizeList = sPrizeListSets[prizeListSetId][i];
    minutes = (signed)(gSaveBlock1Ptr->trainerHill.timer) / (60 * 60);
    if (minutes < 12)
        id = 0;
    else if (minutes < 13)
        id = 1;
    else if (minutes < 14)
        id = 2;
    else if (minutes < 16)
        id = 3;
    else if (minutes < 18)
        id = 4;
    else
        id = 5;

    return prizeList[id];
}
