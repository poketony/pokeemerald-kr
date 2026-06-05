#include "global.h"
#include "battle_tower.h"
#include "apprentice.h"
#include "event_data.h"
#include "battle_setup.h"
#include "overworld.h"
#include "random.h"
#include "text.h"
#include "main.h"
#include "international_string_util.h"
#include "battle.h"
#include "frontier_util.h"
#include "strings.h"
#include "recorded_battle.h"
#include "easy_chat.h"
#include "gym_leader_rematch.h"
#include "battle_transition.h"
#include "trainer_see.h"
#include "new_game.h"
#include "string_util.h"
#include "data.h"
#include "link.h"
#include "field_message_box.h"
#include "tv.h"
#include "battle_factory.h"
#include "constants/apprentice.h"
#include "constants/battle_dome.h"
#include "constants/battle_frontier.h"
#include "constants/battle_frontier_mons.h"
#include "constants/battle_tent_mons.h"
#include "constants/battle_tent_trainers.h"
#include "constants/battle_tower.h"
#include "constants/frontier_util.h"
#include "constants/items.h"
#include "constants/trainers.h"
#include "constants/event_objects.h"
#include "constants/moves.h"
#include "constants/easy_chat.h"
#include "constants/tv.h"

extern const u8 MossdeepCity_SpaceCenter_2F_EventScript_MaxieTrainer[];
extern const u8 MossdeepCity_SpaceCenter_2F_EventScript_TabithaTrainer[];

// EWRAM vars.
EWRAM_DATA const struct BattleFrontierTrainer *gFacilityTrainers = NULL;
EWRAM_DATA const struct FacilityMon *gFacilityTrainerMons = NULL;

// IWRAM common
u16 gFrontierTempParty[MAX_FRONTIER_PARTY_SIZE];

// This file's functions.
static void InitTowerChallenge(void);
static void GetTowerData(void);
static void SetTowerData(void);
static void SetNextFacilityOpponent(void);
static void SetTowerBattleWon(void);
static void AwardBattleTowerRibbons(void);
static void SaveTowerChallenge(void);
static void GetOpponentIntroSpeech(void);
static void BattleTowerNop1(void);
static void BattleTowerNop2(void);
static void LoadMultiPartnerCandidatesData(void);
static void ShowPartnerCandidateMessage(void);
static void LoadLinkMultiOpponentsData(void);
static void TowerTryCloseLink(void);
static void SetMultiPartnerGfx(void);
static void SetTowerInterviewData(void);
static void ValidateBattleTowerRecordChecksums(void);
static void SaveCurrentWinStreak(void);
static void ValidateApprenticesChecksums(void);
static void SetNextBattleTentOpponent(void);
static void CopyEReaderTrainerFarewellMessage(void);
static void ClearBattleTowerRecord(struct EmeraldBattleTowerRecord *record);
static void FillTrainerParty(u16 trainerId, u8 firstMonId, u8 monCount);
static void FillTentTrainerParty_(u16 trainerId, u8 firstMonId, u8 monCount);
static void FillFactoryFrontierTrainerParty(u16 trainerId, u8 firstMonId);
static void FillFactoryTentTrainerParty(u16 trainerId, u8 firstMonId);
static u8 GetFrontierTrainerFixedIvs(u16 trainerId);
static void FillPartnerParty(u16 trainerId);
static void SetEReaderTrainerChecksum(struct BattleTowerEReaderTrainer *ereaderTrainer);
static u8 SetTentPtrsGetLevel(void);

// Const rom data.
const u16 gBattleFrontierHeldItems[] =
{
    ITEM_NONE,
    ITEM_KINGS_ROCK,
    ITEM_SITRUS_BERRY,
    ITEM_ORAN_BERRY,
    ITEM_CHESTO_BERRY,
    ITEM_HARD_STONE,
    ITEM_FOCUS_BAND,
    ITEM_PERSIM_BERRY,
    ITEM_MIRACLE_SEED,
    ITEM_BERRY_JUICE,
    ITEM_MACHO_BRACE,
    ITEM_SILVER_POWDER,
    ITEM_CHERI_BERRY,
    ITEM_BLACK_GLASSES,
    ITEM_BLACK_BELT,
    ITEM_SOUL_DEW,
    ITEM_CHOICE_BAND,
    ITEM_MAGNET,
    ITEM_SILK_SCARF,
    ITEM_WHITE_HERB,
    ITEM_DEEP_SEA_SCALE,
    ITEM_DEEP_SEA_TOOTH,
    ITEM_MYSTIC_WATER,
    ITEM_SHARP_BEAK,
    ITEM_QUICK_CLAW,
    ITEM_LEFTOVERS,
    ITEM_RAWST_BERRY,
    ITEM_LIGHT_BALL,
    ITEM_POISON_BARB,
    ITEM_NEVER_MELT_ICE,
    ITEM_ASPEAR_BERRY,
    ITEM_SPELL_TAG,
    ITEM_BRIGHT_POWDER,
    ITEM_LEPPA_BERRY,
    ITEM_SCOPE_LENS,
    ITEM_TWISTED_SPOON,
    ITEM_METAL_COAT,
    ITEM_MENTAL_HERB,
    ITEM_CHARCOAL,
    ITEM_PECHA_BERRY,
    ITEM_SOFT_SAND,
    ITEM_LUM_BERRY,
    ITEM_DRAGON_SCALE,
    ITEM_DRAGON_FANG,
    ITEM_IAPAPA_BERRY,
    ITEM_WIKI_BERRY,
    ITEM_SEA_INCENSE,
    ITEM_SHELL_BELL,
    ITEM_SALAC_BERRY,
    ITEM_LANSAT_BERRY,
    ITEM_APICOT_BERRY,
    ITEM_STARF_BERRY,
    ITEM_LIECHI_BERRY,
    ITEM_STICK,
    ITEM_LAX_INCENSE,
    ITEM_AGUAV_BERRY,
    ITEM_FIGY_BERRY,
    ITEM_THICK_CLUB,
    ITEM_MAGO_BERRY,
    ITEM_METAL_POWDER,
    ITEM_PETAYA_BERRY,
    ITEM_LUCKY_PUNCH,
    ITEM_GANLON_BERRY
};

#include "data/battle_frontier/battle_frontier_trainer_mons.h"
#include "data/battle_frontier/battle_frontier_trainers.h"
#include "data/battle_frontier/battle_frontier_mons.h"

const u8 gTowerMaleFacilityClasses[30] =
{
    FACILITY_CLASS_RUIN_MANIAC,
    FACILITY_CLASS_TUBER_M,
    FACILITY_CLASS_COOLTRAINER_M,
    FACILITY_CLASS_RICH_BOY,
    FACILITY_CLASS_POKEMANIAC,
    FACILITY_CLASS_SWIMMER_M,
    FACILITY_CLASS_BLACK_BELT,
    FACILITY_CLASS_GUITARIST,
    FACILITY_CLASS_KINDLER,
    FACILITY_CLASS_CAMPER,
    FACILITY_CLASS_BUG_MANIAC,
    FACILITY_CLASS_PSYCHIC_M,
    FACILITY_CLASS_GENTLEMAN,
    FACILITY_CLASS_SCHOOL_KID_M,
    FACILITY_CLASS_POKEFAN_M,
    FACILITY_CLASS_EXPERT_M,
    FACILITY_CLASS_YOUNGSTER,
    FACILITY_CLASS_FISHERMAN,
    FACILITY_CLASS_CYCLING_TRIATHLETE_M,
    FACILITY_CLASS_RUNNING_TRIATHLETE_M,
    FACILITY_CLASS_SWIMMING_TRIATHLETE_M,
    FACILITY_CLASS_DRAGON_TAMER,
    FACILITY_CLASS_BIRD_KEEPER,
    FACILITY_CLASS_NINJA_BOY,
    FACILITY_CLASS_SAILOR,
    FACILITY_CLASS_COLLECTOR,
    FACILITY_CLASS_PKMN_BREEDER_M,
    FACILITY_CLASS_PKMN_RANGER_M,
    FACILITY_CLASS_BUG_CATCHER,
    FACILITY_CLASS_HIKER
};

const u8 gTowerFemaleFacilityClasses[20] =
{
    FACILITY_CLASS_AROMA_LADY,
    FACILITY_CLASS_TUBER_F,
    FACILITY_CLASS_COOLTRAINER_F,
    FACILITY_CLASS_HEX_MANIAC,
    FACILITY_CLASS_LADY,
    FACILITY_CLASS_BEAUTY,
    FACILITY_CLASS_PSYCHIC_F,
    FACILITY_CLASS_SCHOOL_KID_F,
    FACILITY_CLASS_POKEFAN_F,
    FACILITY_CLASS_EXPERT_F,
    FACILITY_CLASS_CYCLING_TRIATHLETE_F,
    FACILITY_CLASS_RUNNING_TRIATHLETE_F,
    FACILITY_CLASS_SWIMMING_TRIATHLETE_F,
    FACILITY_CLASS_BATTLE_GIRL,
    FACILITY_CLASS_PARASOL_LADY,
    FACILITY_CLASS_SWIMMER_F,
    FACILITY_CLASS_PICNICKER,
    FACILITY_CLASS_PKMN_BREEDER_F,
    FACILITY_CLASS_PKMN_RANGER_F,
    FACILITY_CLASS_LASS
};

const u8 gTowerMaleTrainerGfxIds[30] =
{
    OBJ_EVENT_GFX_HIKER,
    OBJ_EVENT_GFX_TUBER_M,
    OBJ_EVENT_GFX_MAN_3,
    OBJ_EVENT_GFX_RICH_BOY,
    OBJ_EVENT_GFX_MANIAC,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M,
    OBJ_EVENT_GFX_BLACK_BELT,
    OBJ_EVENT_GFX_MAN_5,
    OBJ_EVENT_GFX_MAN_5,
    OBJ_EVENT_GFX_CAMPER,
    OBJ_EVENT_GFX_MANIAC,
    OBJ_EVENT_GFX_PSYCHIC_M,
    OBJ_EVENT_GFX_GENTLEMAN,
    OBJ_EVENT_GFX_SCHOOL_KID_M,
    OBJ_EVENT_GFX_POKEFAN_M,
    OBJ_EVENT_GFX_EXPERT_M,
    OBJ_EVENT_GFX_YOUNGSTER,
    OBJ_EVENT_GFX_FISHERMAN,
    OBJ_EVENT_GFX_CYCLING_TRIATHLETE_M,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M,
    OBJ_EVENT_GFX_MAN_3,
    OBJ_EVENT_GFX_MAN_5,
    OBJ_EVENT_GFX_NINJA_BOY,
    OBJ_EVENT_GFX_SAILOR,
    OBJ_EVENT_GFX_MANIAC,
    OBJ_EVENT_GFX_MAN_4,
    OBJ_EVENT_GFX_CAMPER,
    OBJ_EVENT_GFX_BUG_CATCHER,
    OBJ_EVENT_GFX_HIKER
};

const u8 gTowerFemaleTrainerGfxIds[20] =
{
    OBJ_EVENT_GFX_WOMAN_2,
    OBJ_EVENT_GFX_TUBER_F,
    OBJ_EVENT_GFX_WOMAN_5,
    OBJ_EVENT_GFX_HEX_MANIAC,
    OBJ_EVENT_GFX_WOMAN_2,
    OBJ_EVENT_GFX_BEAUTY,
    OBJ_EVENT_GFX_LASS,
    OBJ_EVENT_GFX_GIRL_3,
    OBJ_EVENT_GFX_POKEFAN_F,
    OBJ_EVENT_GFX_EXPERT_F,
    OBJ_EVENT_GFX_CYCLING_TRIATHLETE_F,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_F,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_F,
    OBJ_EVENT_GFX_GIRL_3,
    OBJ_EVENT_GFX_WOMAN_5,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_F,
    OBJ_EVENT_GFX_PICNICKER,
    OBJ_EVENT_GFX_WOMAN_2,
    OBJ_EVENT_GFX_PICNICKER,
    OBJ_EVENT_GFX_LASS
};

// Excludes the unused RS_FACILITY_CLASS_BOARDER_1 and _2
static const u8 sRubyFacilityClassToEmerald[RS_FACILITY_CLASSES_COUNT - 2][2] =
{
    {RS_FACILITY_CLASS_AQUA_LEADER_ARCHIE, FACILITY_CLASS_AQUA_LEADER_ARCHIE},
    {RS_FACILITY_CLASS_AQUA_GRUNT_M, FACILITY_CLASS_AQUA_GRUNT_M},
    {RS_FACILITY_CLASS_AQUA_GRUNT_F, FACILITY_CLASS_AQUA_GRUNT_F},
    {RS_FACILITY_CLASS_AROMA_LADY, FACILITY_CLASS_AROMA_LADY},
    {RS_FACILITY_CLASS_RUIN_MANIAC, FACILITY_CLASS_RUIN_MANIAC},
    {RS_FACILITY_CLASS_INTERVIEWER, FACILITY_CLASS_INTERVIEWER},
    {RS_FACILITY_CLASS_TUBER_F, FACILITY_CLASS_TUBER_F},
    {RS_FACILITY_CLASS_TUBER_M, FACILITY_CLASS_TUBER_M},
    {RS_FACILITY_CLASS_COOLTRAINER_M, FACILITY_CLASS_COOLTRAINER_M},
    {RS_FACILITY_CLASS_COOLTRAINER_F, FACILITY_CLASS_COOLTRAINER_F},
    {RS_FACILITY_CLASS_HEX_MANIAC, FACILITY_CLASS_HEX_MANIAC},
    {RS_FACILITY_CLASS_LADY, FACILITY_CLASS_LADY},
    {RS_FACILITY_CLASS_BEAUTY, FACILITY_CLASS_BEAUTY},
    {RS_FACILITY_CLASS_RICH_BOY, FACILITY_CLASS_RICH_BOY},
    {RS_FACILITY_CLASS_POKEMANIAC, FACILITY_CLASS_POKEMANIAC},
    {RS_FACILITY_CLASS_SWIMMER_M, FACILITY_CLASS_SWIMMER_M},
    {RS_FACILITY_CLASS_BLACK_BELT, FACILITY_CLASS_BLACK_BELT},
    {RS_FACILITY_CLASS_GUITARIST, FACILITY_CLASS_GUITARIST},
    {RS_FACILITY_CLASS_KINDLER, FACILITY_CLASS_KINDLER},
    {RS_FACILITY_CLASS_CAMPER, FACILITY_CLASS_CAMPER},
    {RS_FACILITY_CLASS_BUG_MANIAC, FACILITY_CLASS_BUG_MANIAC},
    {RS_FACILITY_CLASS_PSYCHIC_M, FACILITY_CLASS_PSYCHIC_M},
    {RS_FACILITY_CLASS_PSYCHIC_F, FACILITY_CLASS_PSYCHIC_F},
    {RS_FACILITY_CLASS_GENTLEMAN, FACILITY_CLASS_GENTLEMAN},
    {RS_FACILITY_CLASS_ELITE_FOUR_M, FACILITY_CLASS_ELITE_FOUR_SIDNEY},
    {RS_FACILITY_CLASS_ELITE_FOUR_F, FACILITY_CLASS_ELITE_FOUR_PHOEBE},
    {RS_FACILITY_CLASS_LEADER_F, FACILITY_CLASS_LEADER_ROXANNE},
    {RS_FACILITY_CLASS_LEADER_M, FACILITY_CLASS_LEADER_BRAWLY},
    {RS_FACILITY_CLASS_LEADER_MF, FACILITY_CLASS_LEADER_TATE_AND_LIZA},
    {RS_FACILITY_CLASS_SCHOOL_KID_M, FACILITY_CLASS_SCHOOL_KID_M},
    {RS_FACILITY_CLASS_SCHOOL_KID_F, FACILITY_CLASS_SCHOOL_KID_F},
    {RS_FACILITY_CLASS_SR_AND_JR, FACILITY_CLASS_SR_AND_JR},
    {RS_FACILITY_CLASS_POKEFAN_M, FACILITY_CLASS_POKEFAN_M},
    {RS_FACILITY_CLASS_POKEFAN_F, FACILITY_CLASS_POKEFAN_F},
    {RS_FACILITY_CLASS_EXPERT_M, FACILITY_CLASS_EXPERT_M},
    {RS_FACILITY_CLASS_EXPERT_F, FACILITY_CLASS_EXPERT_F},
    {RS_FACILITY_CLASS_YOUNGSTER, FACILITY_CLASS_YOUNGSTER},
    {RS_FACILITY_CLASS_CHAMPION, FACILITY_CLASS_CHAMPION_WALLACE},
    {RS_FACILITY_CLASS_FISHERMAN, FACILITY_CLASS_FISHERMAN},
    {RS_FACILITY_CLASS_CYCLING_TRIATHLETE_M, FACILITY_CLASS_CYCLING_TRIATHLETE_M},
    {RS_FACILITY_CLASS_CYCLING_TRIATHLETE_F, FACILITY_CLASS_CYCLING_TRIATHLETE_F},
    {RS_FACILITY_CLASS_RUNNING_TRIATHLETE_M, FACILITY_CLASS_RUNNING_TRIATHLETE_M},
    {RS_FACILITY_CLASS_RUNNING_TRIATHLETE_F, FACILITY_CLASS_RUNNING_TRIATHLETE_F},
    {RS_FACILITY_CLASS_SWIMMING_TRIATHLETE_M, FACILITY_CLASS_SWIMMING_TRIATHLETE_M},
    {RS_FACILITY_CLASS_SWIMMING_TRIATHLETE_F, FACILITY_CLASS_SWIMMING_TRIATHLETE_F},
    {RS_FACILITY_CLASS_DRAGON_TAMER, FACILITY_CLASS_DRAGON_TAMER},
    {RS_FACILITY_CLASS_BIRD_KEEPER, FACILITY_CLASS_BIRD_KEEPER},
    {RS_FACILITY_CLASS_NINJA_BOY, FACILITY_CLASS_NINJA_BOY},
    {RS_FACILITY_CLASS_BATTLE_GIRL, FACILITY_CLASS_BATTLE_GIRL},
    {RS_FACILITY_CLASS_PARASOL_LADY, FACILITY_CLASS_PARASOL_LADY},
    {RS_FACILITY_CLASS_SWIMMER_F, FACILITY_CLASS_SWIMMER_F},
    {RS_FACILITY_CLASS_PICNICKER, FACILITY_CLASS_PICNICKER},
    {RS_FACILITY_CLASS_TWINS, FACILITY_CLASS_TWINS},
    {RS_FACILITY_CLASS_SAILOR, FACILITY_CLASS_SAILOR},
    {RS_FACILITY_CLASS_COLLECTOR, FACILITY_CLASS_COLLECTOR},
    {RS_FACILITY_CLASS_WALLY, FACILITY_CLASS_WALLY},
    {RS_FACILITY_CLASS_BRENDAN_1, FACILITY_CLASS_BRENDAN},
    {RS_FACILITY_CLASS_BRENDAN_2, FACILITY_CLASS_BRENDAN_2},
    {RS_FACILITY_CLASS_BRENDAN_3, FACILITY_CLASS_BRENDAN_3},
    {RS_FACILITY_CLASS_MAY_1, FACILITY_CLASS_MAY},
    {RS_FACILITY_CLASS_MAY_2, FACILITY_CLASS_MAY_2},
    {RS_FACILITY_CLASS_MAY_3, FACILITY_CLASS_MAY_3},
    {RS_FACILITY_CLASS_PKMN_BREEDER_M, FACILITY_CLASS_PKMN_BREEDER_M},
    {RS_FACILITY_CLASS_PKMN_BREEDER_F, FACILITY_CLASS_PKMN_BREEDER_F},
    {RS_FACILITY_CLASS_PKMN_RANGER_M, FACILITY_CLASS_PKMN_RANGER_M},
    {RS_FACILITY_CLASS_PKMN_RANGER_F, FACILITY_CLASS_PKMN_RANGER_F},
    {RS_FACILITY_CLASS_MAGMA_LEADER, FACILITY_CLASS_MAGMA_LEADER_MAXIE},
    {RS_FACILITY_CLASS_MAGMA_GRUNT_M, FACILITY_CLASS_MAGMA_GRUNT_M},
    {RS_FACILITY_CLASS_MAGMA_GRUNT_F, FACILITY_CLASS_MAGMA_GRUNT_F},
    {RS_FACILITY_CLASS_LASS, FACILITY_CLASS_LASS},
    {RS_FACILITY_CLASS_BUG_CATCHER, FACILITY_CLASS_BUG_CATCHER},
    {RS_FACILITY_CLASS_HIKER, FACILITY_CLASS_HIKER},
    {RS_FACILITY_CLASS_YOUNG_COUPLE, FACILITY_CLASS_YOUNG_COUPLE},
    {RS_FACILITY_CLASS_OLD_COUPLE, FACILITY_CLASS_OLD_COUPLE},
    {RS_FACILITY_CLASS_SIS_AND_BRO, FACILITY_CLASS_SIS_AND_BRO},
};

#define PARTNER_TEXTS(name)                                             \
    BattleFrontier_BattleTowerMultiPartnerRoom_Text_##name##Intro,      \
    BattleFrontier_BattleTowerMultiPartnerRoom_Text_##name##Mon1,       \
    BattleFrontier_BattleTowerMultiPartnerRoom_Text_##name##Mon2Ask,    \
    BattleFrontier_BattleTowerMultiPartnerRoom_Text_##name##Accept,     \
    BattleFrontier_BattleTowerMultiPartnerRoom_Text_##name##Reject

static const u8 *const sPartnerApprenticeTexts1[] =
{
    PARTNER_TEXTS(Apprentice1)
};

static const u8 *const sPartnerApprenticeTexts2[] =
{
    PARTNER_TEXTS(Apprentice2)
};

static const u8 *const sPartnerApprenticeTexts3[] =
{
    PARTNER_TEXTS(Apprentice3)
};

static const u8 *const sPartnerApprenticeTexts4[] =
{
    PARTNER_TEXTS(Apprentice4)
};

static const u8 *const sPartnerApprenticeTexts5[] =
{
    PARTNER_TEXTS(Apprentice5)
};

static const u8 *const sPartnerApprenticeTexts6[] =
{
     PARTNER_TEXTS(Apprentice6)
};

static const u8 *const sPartnerApprenticeTexts7[] =
{
     PARTNER_TEXTS(Apprentice7)
};

static const u8 *const sPartnerApprenticeTexts8[] =
{
     PARTNER_TEXTS(Apprentice8)
};

static const u8 *const sPartnerApprenticeTexts9[] =
{
     PARTNER_TEXTS(Apprentice9)
};

static const u8 *const sPartnerApprenticeTexts10[] =
{
     PARTNER_TEXTS(Apprentice10)
};

static const u8 *const sPartnerApprenticeTexts11[] =
{
     PARTNER_TEXTS(Apprentice11)
};

static const u8 *const sPartnerApprenticeTexts12[] =
{
     PARTNER_TEXTS(Apprentice12)
};

static const u8 *const sPartnerApprenticeTexts13[] =
{
     PARTNER_TEXTS(Apprentice13)
};

static const u8 *const sPartnerApprenticeTexts14[] =
{
     PARTNER_TEXTS(Apprentice14)
};

static const u8 *const sPartnerApprenticeTexts15[] =
{
     PARTNER_TEXTS(Apprentice15)
};

static const u8 *const sPartnerApprenticeTexts16[] =
{
     PARTNER_TEXTS(Apprentice16)
};

static const u8 *const sPartnerTextsLass[] =
{
    PARTNER_TEXTS(Lass)
};

static const u8 *const sPartnerTextsYoungster[] =
{
    PARTNER_TEXTS(Youngster)
};

static const u8 *const sPartnerTextsHiker[] =
{
    PARTNER_TEXTS(Hiker)
};

static const u8 *const sPartnerTextsBeauty[] =
{
    PARTNER_TEXTS(Beauty)
};

static const u8 *const sPartnerTextsFisherman[] =
{
    PARTNER_TEXTS(Fisherman)
};

static const u8 *const sPartnerTextsLady[] =
{
    PARTNER_TEXTS(Lady)
};

static const u8 *const sPartnerTextsCyclingTriathleteF[] =
{
    PARTNER_TEXTS(CyclingTriathleteF)
};

static const u8 *const sPartnerTextsBugCatcher[] =
{
    PARTNER_TEXTS(BugCatcher)
};

static const u8 *const sPartnerTextsSchoolKidM[] =
{
    PARTNER_TEXTS(SchoolKidM)
};

static const u8 *const sPartnerTextsRichBoy[] =
{
    PARTNER_TEXTS(RichBoy)
};

static const u8 *const sPartnerTextsBlackBelt[] =
{
    PARTNER_TEXTS(BlackBelt)
};

static const u8 *const sPartnerTextsTuberF[] =
{
    PARTNER_TEXTS(TuberF)
};

static const u8 *const sPartnerTextsHexManiac[] =
{
    PARTNER_TEXTS(HexManiac)
};

static const u8 *const sPartnerTextsPkmnBreederM[] =
{
    PARTNER_TEXTS(PkmnBreederM)
};

static const u8 *const sPartnerTextsRunningTriathleteF[] =
{
    PARTNER_TEXTS(RunningTriathleteF)
};

static const u8 *const sPartnerTextsRunningTriathleteM[] =
{
    PARTNER_TEXTS(RunningTriathleteM)
};

static const u8 *const sPartnerTextsBattleGirl[] =
{
    PARTNER_TEXTS(BattleGirl)
};

static const u8 *const sPartnerTextsCyclingTriathleteM[] =
{
    PARTNER_TEXTS(CyclingTriathleteM)
};

static const u8 *const sPartnerTextsTuberM[] =
{
    PARTNER_TEXTS(TuberM)
};

static const u8 *const sPartnerTextsGuitarist[] =
{
    PARTNER_TEXTS(Guitarist)
};

static const u8 *const sPartnerTextsGentleman[] =
{
    PARTNER_TEXTS(Gentleman)
};

static const u8 *const sPartnerTextsPokefanM[] =
{
    PARTNER_TEXTS(PokefanM)
};

static const u8 *const sPartnerTextsExpertM[] =
{
    PARTNER_TEXTS(ExpertM)
};

static const u8 *const sPartnerTextsExpertF[] =
{
    PARTNER_TEXTS(ExpertF)
};

static const u8 *const sPartnerTextsDragonTamer[] =
{
    PARTNER_TEXTS(DragonTamer)
};

static const u8 *const sPartnerTextsBirdKeeper[] =
{
    PARTNER_TEXTS(BirdKeeper)
};

static const u8 *const sPartnerTextsNinjaBoy[] =
{
    PARTNER_TEXTS(NinjaBoy)
};

static const u8 *const sPartnerTextsParasolLady[] =
{
    PARTNER_TEXTS(ParasolLady)
};

static const u8 *const sPartnerTextsBugManiac[] =
{
    PARTNER_TEXTS(BugManiac)
};

static const u8 *const sPartnerTextsSailor[] =
{
    PARTNER_TEXTS(Sailor)
};

static const u8 *const sPartnerTextsCollector[] =
{
    PARTNER_TEXTS(Collector)
};

static const u8 *const sPartnerTextsPkmnRangerM[] =
{
    PARTNER_TEXTS(PkmnRangerM)
};

static const u8 *const sPartnerTextsPkmnRangerF[] =
{
    PARTNER_TEXTS(PkmnRangerF)
};

static const u8 *const sPartnerTextsAromaLady[] =
{
    PARTNER_TEXTS(AromaLady)
};

static const u8 *const sPartnerTextsRuinManiac[] =
{
    PARTNER_TEXTS(RuinManiac)
};

static const u8 *const sPartnerTextsCoolTrainerM[] =
{
    PARTNER_TEXTS(CoolTrainerM)
};

static const u8 *const sPartnerTextsCoolTrainerF[] =
{
    PARTNER_TEXTS(CoolTrainerF)
};

static const u8 *const sPartnerTextsPokemaniac[] =
{
    PARTNER_TEXTS(Pokemaniac)
};

static const u8 *const sPartnerTextsKindler[] =
{
    PARTNER_TEXTS(Kindler)
};

static const u8 *const sPartnerTextsCamper[] =
{
    PARTNER_TEXTS(Camper)
};

static const u8 *const sPartnerTextsPicnicker[] =
{
    PARTNER_TEXTS(Picnicker)
};

static const u8 *const sPartnerTextsPsychicM[] =
{
    PARTNER_TEXTS(PsychicM)
};

static const u8 *const sPartnerTextsPsychicF[] =
{
    PARTNER_TEXTS(PsychicF)
};

static const u8 *const sPartnerTextsSchoolKidF[] =
{
    PARTNER_TEXTS(SchoolKidF)
};

static const u8 *const sPartnerTextsPkmnBreederF[] =
{
    PARTNER_TEXTS(PkmnBreederF)
};

static const u8 *const sPartnerTextsPokefanF[] =
{
    PARTNER_TEXTS(PokefanF)
};

static const u8 *const sPartnerTextsSwimmerF[] =
{
    PARTNER_TEXTS(SwimmerF)
};

static const u8 *const sPartnerTextsSwimmingTriathleteM[] =
{
    PARTNER_TEXTS(SwimmingTriathleteM)
};

static const u8 *const sPartnerTextsSwimmingTriathleteF[] =
{
    PARTNER_TEXTS(SwimmingTriathleteF)
};

static const u8 *const sPartnerTextsSwimmerM[] =
{
    PARTNER_TEXTS(SwimmerM)
};

struct
{
    u32 facilityClass;
    const u8 *const *strings;
} const sPartnerTrainerTextTables[] =
{
    {FACILITY_CLASS_LASS,                  sPartnerTextsLass},
    {FACILITY_CLASS_YOUNGSTER,             sPartnerTextsYoungster},
    {FACILITY_CLASS_HIKER,                 sPartnerTextsHiker},
    {FACILITY_CLASS_BEAUTY,                sPartnerTextsBeauty},
    {FACILITY_CLASS_FISHERMAN,             sPartnerTextsFisherman},
    {FACILITY_CLASS_LADY,                  sPartnerTextsLady},
    {FACILITY_CLASS_CYCLING_TRIATHLETE_F,  sPartnerTextsCyclingTriathleteF},
    {FACILITY_CLASS_BUG_CATCHER,           sPartnerTextsBugCatcher},
    {FACILITY_CLASS_SCHOOL_KID_M,          sPartnerTextsSchoolKidM},
    {FACILITY_CLASS_RICH_BOY,              sPartnerTextsRichBoy},
    {FACILITY_CLASS_BLACK_BELT,            sPartnerTextsBlackBelt},
    {FACILITY_CLASS_TUBER_F,               sPartnerTextsTuberF},
    {FACILITY_CLASS_HEX_MANIAC,            sPartnerTextsHexManiac},
    {FACILITY_CLASS_PKMN_BREEDER_M,        sPartnerTextsPkmnBreederM},
    {FACILITY_CLASS_RUNNING_TRIATHLETE_F,  sPartnerTextsRunningTriathleteF},
    {FACILITY_CLASS_RUNNING_TRIATHLETE_M,  sPartnerTextsRunningTriathleteM},
    {FACILITY_CLASS_BATTLE_GIRL,           sPartnerTextsBattleGirl},
    {FACILITY_CLASS_CYCLING_TRIATHLETE_M,  sPartnerTextsCyclingTriathleteM},
    {FACILITY_CLASS_TUBER_M,               sPartnerTextsTuberM},
    {FACILITY_CLASS_GUITARIST,             sPartnerTextsGuitarist},
    {FACILITY_CLASS_GENTLEMAN,             sPartnerTextsGentleman},
    {FACILITY_CLASS_POKEFAN_M,             sPartnerTextsPokefanM},
    {FACILITY_CLASS_EXPERT_M,              sPartnerTextsExpertM},
    {FACILITY_CLASS_EXPERT_F,              sPartnerTextsExpertF},
    {FACILITY_CLASS_DRAGON_TAMER,          sPartnerTextsDragonTamer},
    {FACILITY_CLASS_BIRD_KEEPER,           sPartnerTextsBirdKeeper},
    {FACILITY_CLASS_NINJA_BOY,             sPartnerTextsNinjaBoy},
    {FACILITY_CLASS_PARASOL_LADY,          sPartnerTextsParasolLady},
    {FACILITY_CLASS_BUG_MANIAC,            sPartnerTextsBugManiac},
    {FACILITY_CLASS_SAILOR,                sPartnerTextsSailor},
    {FACILITY_CLASS_COLLECTOR,             sPartnerTextsCollector},
    {FACILITY_CLASS_PKMN_RANGER_M,         sPartnerTextsPkmnRangerM},
    {FACILITY_CLASS_PKMN_RANGER_F,         sPartnerTextsPkmnRangerF},
    {FACILITY_CLASS_AROMA_LADY,            sPartnerTextsAromaLady},
    {FACILITY_CLASS_RUIN_MANIAC,           sPartnerTextsRuinManiac},
    {FACILITY_CLASS_COOLTRAINER_M,         sPartnerTextsCoolTrainerM},
    {FACILITY_CLASS_COOLTRAINER_F,         sPartnerTextsCoolTrainerF},
    {FACILITY_CLASS_POKEMANIAC,            sPartnerTextsPokemaniac},
    {FACILITY_CLASS_KINDLER,               sPartnerTextsKindler},
    {FACILITY_CLASS_CAMPER,                sPartnerTextsCamper},
    {FACILITY_CLASS_PICNICKER,             sPartnerTextsPicnicker},
    {FACILITY_CLASS_PSYCHIC_M,             sPartnerTextsPsychicM},
    {FACILITY_CLASS_PSYCHIC_F,             sPartnerTextsPsychicF},
    {FACILITY_CLASS_SCHOOL_KID_F,          sPartnerTextsSchoolKidF},
    {FACILITY_CLASS_PKMN_BREEDER_F,        sPartnerTextsPkmnBreederF},
    {FACILITY_CLASS_POKEFAN_F,             sPartnerTextsPokefanF},
    {FACILITY_CLASS_SWIMMER_F,             sPartnerTextsSwimmerF},
    {FACILITY_CLASS_SWIMMING_TRIATHLETE_M, sPartnerTextsSwimmingTriathleteM},
    {FACILITY_CLASS_SWIMMING_TRIATHLETE_F, sPartnerTextsSwimmingTriathleteF},
    {FACILITY_CLASS_SWIMMER_M,             sPartnerTextsSwimmerM}
};

static const u8 *const *const sPartnerApprenticeTextTables[NUM_APPRENTICES] =
{
    sPartnerApprenticeTexts1,
    sPartnerApprenticeTexts2,
    sPartnerApprenticeTexts3,
    sPartnerApprenticeTexts4,
    sPartnerApprenticeTexts5,
    sPartnerApprenticeTexts6,
    sPartnerApprenticeTexts7,
    sPartnerApprenticeTexts8,
    sPartnerApprenticeTexts9,
    sPartnerApprenticeTexts10,
    sPartnerApprenticeTexts11,
    sPartnerApprenticeTexts12,
    sPartnerApprenticeTexts13,
    sPartnerApprenticeTexts14,
    sPartnerApprenticeTexts15,
    sPartnerApprenticeTexts16
};

struct
{
    u16 species;
    u8 fixedIV;
    u8 level;
    u8 nature;
    u8 evs[NUM_STATS];
    u16 moves[MAX_MON_MOVES];
} const sStevenMons[MULTI_PARTY_SIZE] =
{
    {
        .species = SPECIES_METANG,
        .fixedIV = 31,
        .level = 42,
        .nature = NATURE_BRAVE,
        .evs = {0, 252, 252, 0, 6, 0},
        .moves = {MOVE_LIGHT_SCREEN, MOVE_PSYCHIC, MOVE_REFLECT, MOVE_METAL_CLAW}
    },
    {
        .species = SPECIES_SKARMORY,
        .fixedIV = 31,
        .level = 43,
        .nature = NATURE_IMPISH,
        .evs = {252, 0, 0, 0, 6, 252},
        .moves = {MOVE_TOXIC, MOVE_AERIAL_ACE, MOVE_PROTECT, MOVE_STEEL_WING}
    },
    {
        .species = SPECIES_AGGRON,
        .fixedIV = 31,
        .level = 44,
        .nature = NATURE_ADAMANT,
        .evs = {0, 252, 0, 0, 252, 6},
        .moves = {MOVE_THUNDER, MOVE_PROTECT, MOVE_SOLAR_BEAM, MOVE_DRAGON_CLAW}
    }
};

#include "data/battle_frontier/battle_tent.h"

static void (* const sBattleTowerFuncs[])(void) =
{
    [BATTLE_TOWER_FUNC_INIT]                = InitTowerChallenge,
    [BATTLE_TOWER_FUNC_GET_DATA]            = GetTowerData,
    [BATTLE_TOWER_FUNC_SET_DATA]            = SetTowerData,
    [BATTLE_TOWER_FUNC_SET_OPPONENT]        = SetNextFacilityOpponent,
    [BATTLE_TOWER_FUNC_SET_BATTLE_WON]      = SetTowerBattleWon,
    [BATTLE_TOWER_FUNC_GIVE_RIBBONS]        = AwardBattleTowerRibbons,
    [BATTLE_TOWER_FUNC_SAVE]                = SaveTowerChallenge,
    [BATTLE_TOWER_FUNC_GET_OPPONENT_INTRO]  = GetOpponentIntroSpeech,
    [BATTLE_TOWER_FUNC_NOP]                 = BattleTowerNop1,
    [BATTLE_TOWER_FUNC_NOP2]                = BattleTowerNop2,
    [BATTLE_TOWER_FUNC_LOAD_PARTNERS]       = LoadMultiPartnerCandidatesData,
    [BATTLE_TOWER_FUNC_PARTNER_MSG]         = ShowPartnerCandidateMessage,
    [BATTLE_TOWER_FUNC_LOAD_LINK_OPPONENTS] = LoadLinkMultiOpponentsData,
    [BATTLE_TOWER_FUNC_TRY_CLOSE_LINK]      = TowerTryCloseLink,
    [BATTLE_TOWER_FUNC_SET_PARTNER_GFX]     = SetMultiPartnerGfx,
    [BATTLE_TOWER_FUNC_SET_INTERVIEW_DATA]  = SetTowerInterviewData,
};

static const u32 sWinStreakFlags[][2] =
{
    {STREAK_TOWER_SINGLES_50,     STREAK_TOWER_SINGLES_OPEN},
    {STREAK_TOWER_DOUBLES_50,     STREAK_TOWER_DOUBLES_OPEN},
    {STREAK_TOWER_MULTIS_50,      STREAK_TOWER_MULTIS_OPEN},
    {STREAK_TOWER_LINK_MULTIS_50, STREAK_TOWER_LINK_MULTIS_OPEN},
};

static const u32 sWinStreakMasks[][2] =
{
    {~(STREAK_TOWER_SINGLES_50),     ~(STREAK_TOWER_SINGLES_OPEN)},
    {~(STREAK_TOWER_DOUBLES_50),     ~(STREAK_TOWER_DOUBLES_OPEN)},
    {~(STREAK_TOWER_MULTIS_50),      ~(STREAK_TOWER_MULTIS_OPEN)},
    {~(STREAK_TOWER_LINK_MULTIS_50), ~(STREAK_TOWER_LINK_MULTIS_OPEN)},
};

// The challenge number at which an Apprentice can appear, depending on how many of their questions were answered
static const u8 sApprenticeChallengeThreshold[MAX_APPRENTICE_QUESTIONS] =
{
    1, 2, 3, 4, 5, 8, 9, 10, 11, 12
};

// Unclear why this was duplicated
static const u8 sBattleTowerPartySizes2[] =
{
    [FRONTIER_MODE_SINGLES]     = FRONTIER_PARTY_SIZE,
    [FRONTIER_MODE_DOUBLES]     = FRONTIER_DOUBLES_PARTY_SIZE,
    [FRONTIER_MODE_MULTIS]      = FRONTIER_MULTI_PARTY_SIZE,
    [FRONTIER_MODE_LINK_MULTIS] = FRONTIER_MULTI_PARTY_SIZE,
};

// Trainer ID ranges for possible frontier trainers to encounter on particular challenges
// Trainers are scaled by difficulty, so higher trainer IDs have better teams
static const u16 sFrontierTrainerIdRanges[][2] =
{
    {FRONTIER_TRAINER_BRADY,   FRONTIER_TRAINER_JILL},   //   0 -  99
    {FRONTIER_TRAINER_TREVIN,  FRONTIER_TRAINER_CHLOE},  //  80 - 119
    {FRONTIER_TRAINER_ERIK,    FRONTIER_TRAINER_SOFIA},  // 100 - 139
    {FRONTIER_TRAINER_NORTON,  FRONTIER_TRAINER_JAZLYN}, // 120 - 159
    {FRONTIER_TRAINER_BRADEN,  FRONTIER_TRAINER_ALISON}, // 140 - 179
    {FRONTIER_TRAINER_ZACHERY, FRONTIER_TRAINER_LAMAR},  // 160 - 199
    {FRONTIER_TRAINER_HANK,    FRONTIER_TRAINER_TESS},   // 180 - 219
    {FRONTIER_TRAINER_JAXON,   FRONTIER_TRAINER_GRETEL}, // 200 - 299
};

static const u16 sFrontierTrainerIdRangesHard[][2] =
{
    {FRONTIER_TRAINER_ERIK,    FRONTIER_TRAINER_CHLOE},  // 100 - 119
    {FRONTIER_TRAINER_NORTON,  FRONTIER_TRAINER_SOFIA},  // 120 - 139
    {FRONTIER_TRAINER_BRADEN,  FRONTIER_TRAINER_JAZLYN}, // 140 - 159
    {FRONTIER_TRAINER_ZACHERY, FRONTIER_TRAINER_ALISON}, // 160 - 179
    {FRONTIER_TRAINER_HANK,    FRONTIER_TRAINER_LAMAR},  // 180 - 199
    {FRONTIER_TRAINER_JAXON,   FRONTIER_TRAINER_TESS},   // 200 - 219
    {FRONTIER_TRAINER_LEON,    FRONTIER_TRAINER_RAUL},   // 220 - 239
    {FRONTIER_TRAINER_JAXON,   FRONTIER_TRAINER_GRETEL}, // 200 - 299
};

// Trainer IDs? Don't make sense as part of previous array, min/max relationship reversed and never accessed
static const u16 sUnused_085DFA1A[][2] =
{
    {179, 141}, // FRONTIER_TRAINER_ALISON - FRONTIER_TRAINER_KAYDEN
    {200, 183}, // FRONTIER_TRAINER_JAXON  - FRONTIER_TRAINER_HUNTER
};

static const u8 sBattleTowerPartySizes[FRONTIER_MODE_COUNT] =
{
    [FRONTIER_MODE_SINGLES]     = FRONTIER_PARTY_SIZE,
    [FRONTIER_MODE_DOUBLES]     = FRONTIER_DOUBLES_PARTY_SIZE,
    [FRONTIER_MODE_MULTIS]      = FRONTIER_MULTI_PARTY_SIZE,
    [FRONTIER_MODE_LINK_MULTIS] = FRONTIER_MULTI_PARTY_SIZE,
};

static const u16 sRecordTrainerSpeechWon[] =
{
    EC_WORD_YAY, EC_WORD_YAY, EC_WORD_EXCL_EXCL, EC_WORD_I_VE, EC_WORD_WON, EC_WORD_EXCL_EXCL
};

static const u16 sRecordTrainerSpeechLost[] =
{
    EC_WORD_TOO, EC_WORD_BAD, EC_WORD_ELLIPSIS, EC_WORD_WE, EC_WORD_LOST, EC_WORD_ELLIPSIS
};

// code
void CallBattleTowerFunc(void)
{
    sBattleTowerFuncs[gSpecialVar_0x8004]();
}

static void InitTowerChallenge(void)
{
    u32 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    gSaveBlock2Ptr->frontier.challengeStatus = CHALLENGE_STATUS_SAVING;
    gSaveBlock2Ptr->frontier.curChallengeBattleNum = 0;
    gSaveBlock2Ptr->frontier.challengePaused = FALSE;
    gSaveBlock2Ptr->frontier.disableRecordBattle = FALSE;
    ResetFrontierTrainerIds();
    if (!(gSaveBlock2Ptr->frontier.winStreakActiveFlags & sWinStreakFlags[battleMode][lvlMode]))
        gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][lvlMode] = 0;

    ValidateBattleTowerRecordChecksums();
    SetDynamicWarp(0, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, -1);
    gTrainerBattleOpponent_A = 0;
}

static void GetTowerData(void)
{
    u32 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    switch (gSpecialVar_0x8005)
    {
    case 0:
        break;
    case TOWER_DATA_WIN_STREAK:
        gSpecialVar_Result = GetCurrentBattleTowerWinStreak(lvlMode, battleMode);
        break;
    case TOWER_DATA_WIN_STREAK_ACTIVE:
        gSpecialVar_Result = ((gSaveBlock2Ptr->frontier.winStreakActiveFlags & sWinStreakFlags[battleMode][lvlMode]) != 0);
        break;
    case TOWER_DATA_LVL_MODE:
        gSaveBlock2Ptr->frontier.towerLvlMode = gSaveBlock2Ptr->frontier.lvlMode;
        break;
    }
}

static void SetTowerData(void)
{
    u32 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    switch (gSpecialVar_0x8005)
    {
    case 0:
        break;
    case TOWER_DATA_WIN_STREAK:
        gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][lvlMode] = gSpecialVar_0x8006;
        break;
    case TOWER_DATA_WIN_STREAK_ACTIVE:
        if (gSpecialVar_0x8006)
            gSaveBlock2Ptr->frontier.winStreakActiveFlags |= sWinStreakFlags[battleMode][lvlMode];
        else
            gSaveBlock2Ptr->frontier.winStreakActiveFlags &= sWinStreakMasks[battleMode][lvlMode];
        break;
    case TOWER_DATA_LVL_MODE:
        gSaveBlock2Ptr->frontier.towerLvlMode = gSaveBlock2Ptr->frontier.lvlMode;
        break;
    }
}

static void SetTowerBattleWon(void)
{
    if (gTrainerBattleOpponent_A == TRAINER_EREADER)
        ClearEReaderTrainer(&gSaveBlock2Ptr->frontier.ereaderTrainer);

    // towerNumWins is never read outside this conditional
    if (gSaveBlock2Ptr->frontier.towerNumWins < MAX_STREAK)
        gSaveBlock2Ptr->frontier.towerNumWins++;

    gSaveBlock2Ptr->frontier.curChallengeBattleNum++;
    SaveCurrentWinStreak();
    gSpecialVar_Result = gSaveBlock2Ptr->frontier.curChallengeBattleNum;
}

static bool8 ChooseSpecialBattleTowerTrainer(void)
{
    s32 i, j, validMons;
    s32 trainerIds[9];
    s32 idsCount = 0;
    s32 winStreak = 0;
    u8 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u8 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    if (VarGet(VAR_FRONTIER_FACILITY) != FRONTIER_FACILITY_TOWER)
        return FALSE;

    winStreak = GetCurrentBattleTowerWinStreak(lvlMode, battleMode);
    for (i = 0; i < BATTLE_TOWER_RECORD_COUNT; i++)
    {
        u32 *record = (u32*)(&gSaveBlock2Ptr->frontier.towerRecords[i]);
        u32 recordHasData = 0;
        u32 checksum = 0;
        for (j = 0; j < (sizeof(struct EmeraldBattleTowerRecord) - 4) / 4; j++) // - 4, because of the last field being the checksum itself.
        {
            recordHasData |= record[j];
            checksum += record[j];
        }
        validMons = 0;
        for (j = 0; j < MAX_FRONTIER_PARTY_SIZE; j++)
        {
            if (gSaveBlock2Ptr->frontier.towerRecords[i].party[j].species != 0
                && gSaveBlock2Ptr->frontier.towerRecords[i].party[j].level <= GetFrontierEnemyMonLevel(lvlMode))
                validMons++;
        }

        if (validMons >= sBattleTowerPartySizes2[battleMode]
            && gSaveBlock2Ptr->frontier.towerRecords[i].winStreak == winStreak
            && gSaveBlock2Ptr->frontier.towerRecords[i].lvlMode == lvlMode
            && recordHasData
            && gSaveBlock2Ptr->frontier.towerRecords[i].checksum == checksum)
        {
            trainerIds[idsCount] = i + TRAINER_RECORD_MIXING_FRIEND;
            idsCount++;
        }
    }

    if (battleMode == FRONTIER_MODE_SINGLES)
    {
        ValidateApprenticesChecksums();
        for (i = 0; i < APPRENTICE_COUNT; i++)
        {
            if (gSaveBlock2Ptr->apprentices[i].lvlMode != 0
                && sApprenticeChallengeThreshold[gSaveBlock2Ptr->apprentices[i].numQuestions] == winStreak
                && gSaveBlock2Ptr->apprentices[i].lvlMode - 1 == lvlMode)
            {
                trainerIds[idsCount] = i + TRAINER_RECORD_MIXING_APPRENTICE;
                idsCount++;
            }
        }
    }

    if (idsCount != 0)
    {
        gTrainerBattleOpponent_A = trainerIds[Random() % idsCount];
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static void SetNextFacilityOpponent(void)
{
    u32 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    if (lvlMode == FRONTIER_LVL_TENT)
    {
        SetNextBattleTentOpponent();
    }
    else
    {
        u16 id;
        u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
        u16 winStreak = GetCurrentFacilityWinStreak();
        u32 challengeNum = winStreak / 7;
        SetFacilityPtrsGetLevel();

        if (battleMode == FRONTIER_MODE_MULTIS || battleMode == FRONTIER_MODE_LINK_MULTIS)
        {
            id = gSaveBlock2Ptr->frontier.curChallengeBattleNum;
            gTrainerBattleOpponent_A = gSaveBlock2Ptr->frontier.trainerIds[id * 2];
            gTrainerBattleOpponent_B = gSaveBlock2Ptr->frontier.trainerIds[id * 2 + 1];
            SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
            SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_B, 1);
        }
        else if (ChooseSpecialBattleTowerTrainer())
        {
            SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
            gSaveBlock2Ptr->frontier.trainerIds[gSaveBlock2Ptr->frontier.curChallengeBattleNum] = gTrainerBattleOpponent_A;
        }
        else
        {
            s32 i;
            while (1)
            {
                id = GetRandomScaledFrontierTrainerId(challengeNum, gSaveBlock2Ptr->frontier.curChallengeBattleNum);

                // Ensure trainer wasn't previously fought in this challenge.
                for (i = 0; i < gSaveBlock2Ptr->frontier.curChallengeBattleNum; i++)
                {
                    if (gSaveBlock2Ptr->frontier.trainerIds[i] == id)
                        break;
                }
                if (i == gSaveBlock2Ptr->frontier.curChallengeBattleNum)
                    break;
            }

            gTrainerBattleOpponent_A = id;
            SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
            if (gSaveBlock2Ptr->frontier.curChallengeBattleNum + 1 < 7)
                gSaveBlock2Ptr->frontier.trainerIds[gSaveBlock2Ptr->frontier.curChallengeBattleNum] = gTrainerBattleOpponent_A;
        }
    }
}

u16 GetRandomScaledFrontierTrainerId(u8 challengeNum, u8 battleNum)
{
    u16 trainerId;

    if (challengeNum <= 7)
    {
        if (battleNum == 6)
        {
            // The last battle in each challenge has a jump in difficulty, pulls from a table with higher ranges
            trainerId = (sFrontierTrainerIdRangesHard[challengeNum][1] - sFrontierTrainerIdRangesHard[challengeNum][0]) + 1;
            trainerId = sFrontierTrainerIdRangesHard[challengeNum][0] + (Random() % trainerId);
        }
        else
        {
            trainerId = (sFrontierTrainerIdRanges[challengeNum][1] - sFrontierTrainerIdRanges[challengeNum][0]) + 1;
            trainerId = sFrontierTrainerIdRanges[challengeNum][0] + (Random() % trainerId);
        }
    }
    else
    {
        // After challenge 7, trainer IDs always come from the last, hardest range, which is the same for both trainer ID tables
        trainerId = (sFrontierTrainerIdRanges[7][1] - sFrontierTrainerIdRanges[7][0]) + 1;
        trainerId = sFrontierTrainerIdRanges[7][0] + (Random() % trainerId);
    }

    return trainerId;
}

// Unused
static void GetRandomScaledFrontierTrainerIdRange(u8 challengeNum, u8 battleNum, u16 *trainerIdPtr, u8 *rangePtr)
{
    u16 trainerId, range;

    if (challengeNum <= 7)
    {
        if (battleNum == 6)
        {
            // The last battle in each challenge has a jump in difficulty, pulls from a table with higher ranges
            range = (sFrontierTrainerIdRangesHard[challengeNum][1] - sFrontierTrainerIdRangesHard[challengeNum][0]) + 1;
            trainerId = sFrontierTrainerIdRangesHard[challengeNum][0];
        }
        else
        {
            range = (sFrontierTrainerIdRanges[challengeNum][1] - sFrontierTrainerIdRanges[challengeNum][0]) + 1;
            trainerId = sFrontierTrainerIdRanges[challengeNum][0];
        }
    }
    else
    {
        // After challenge 7, trainer IDs always come from the last, hardest range, which is the same for both trainer ID tables
        range = (sFrontierTrainerIdRanges[7][1] - sFrontierTrainerIdRanges[7][0]) + 1;
        trainerId = sFrontierTrainerIdRanges[7][0];
    }

    *trainerIdPtr = trainerId;
    *rangePtr = range;
}

void SetBattleFacilityTrainerGfxId(u16 trainerId, u8 tempVarId)
{
    u32 i;
    u8 facilityClass;
    u8 trainerObjectGfxId;

    SetFacilityPtrsGetLevel();
    if (trainerId == TRAINER_EREADER)
    {
        facilityClass = gSaveBlock2Ptr->frontier.ereaderTrainer.facilityClass;
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        SetFrontierBrainObjEventGfx_2();
        return;
    }
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        facilityClass = gFacilityTrainers[trainerId].facilityClass;
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        facilityClass = gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].facilityClass;
    }
    else
    {
        facilityClass = gApprentices[gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id].facilityClass;
    }

    // Search male classes.
    for (i = 0; i < ARRAY_COUNT(gTowerMaleFacilityClasses); i++)
    {
        if (gTowerMaleFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gTowerMaleFacilityClasses))
    {
        trainerObjectGfxId = gTowerMaleTrainerGfxIds[i];
        switch (tempVarId)
        {
        case 0:
        default:
            VarSet(VAR_OBJ_GFX_ID_0, trainerObjectGfxId);
            return;
        case 1:
            VarSet(VAR_OBJ_GFX_ID_1, trainerObjectGfxId);
            return;
        case 15:
            VarSet(VAR_OBJ_GFX_ID_E, trainerObjectGfxId);
            return;
        }
    }

    // Search female classes.
    for (i = 0; i < ARRAY_COUNT(gTowerFemaleFacilityClasses); i++)
    {
        if (gTowerFemaleFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gTowerFemaleFacilityClasses))
    {
        trainerObjectGfxId = gTowerFemaleTrainerGfxIds[i];
        switch (tempVarId)
        {
        case 0:
        default:
            VarSet(VAR_OBJ_GFX_ID_0, trainerObjectGfxId);
            return;
        case 1:
            VarSet(VAR_OBJ_GFX_ID_1, trainerObjectGfxId);
            return;
        case 15:
            VarSet(VAR_OBJ_GFX_ID_E, trainerObjectGfxId);
            return;
        }
    }

    switch (tempVarId)
    {
    case 0:
    default:
        VarSet(VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BOY_1);
        return;
    case 1:
        VarSet(VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_BOY_1);
        return;
    case 15:
        VarSet(VAR_OBJ_GFX_ID_E, OBJ_EVENT_GFX_BOY_1);
        return;
    }
}

void SetEReaderTrainerGfxId(void)
{
    SetBattleFacilityTrainerGfxId(TRAINER_EREADER, 0);
}

u8 GetBattleFacilityTrainerGfxId(u16 trainerId)
{
    u32 i;
    u8 facilityClass;
    u8 trainerObjectGfxId;

    SetFacilityPtrsGetLevel();
    if (trainerId == TRAINER_EREADER)
    {
        facilityClass = gSaveBlock2Ptr->frontier.ereaderTrainer.facilityClass;
    }
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        facilityClass = gFacilityTrainers[trainerId].facilityClass;
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        facilityClass = gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].facilityClass;
    }
    else
    {
        facilityClass = gApprentices[gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id].facilityClass;
    }

    // Search male classes.
    for (i = 0; i < ARRAY_COUNT(gTowerMaleFacilityClasses); i++)
    {
        if (gTowerMaleFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gTowerMaleFacilityClasses))
    {
        trainerObjectGfxId = gTowerMaleTrainerGfxIds[i];
        return trainerObjectGfxId;
    }

    // Search female classes.
    for (i = 0; i < ARRAY_COUNT(gTowerFemaleFacilityClasses); i++)
    {
        if (gTowerFemaleFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gTowerFemaleFacilityClasses))
    {
        trainerObjectGfxId = gTowerFemaleTrainerGfxIds[i];
        return trainerObjectGfxId;
    }
    else
    {
        return OBJ_EVENT_GFX_BOY_1;
    }
}

void PutNewBattleTowerRecord(struct EmeraldBattleTowerRecord *newRecordEm)
{
    u16 slotValues[6];
    u16 slotIds[6];
    s32 i, j, k;
    s32 slotsCount = 0;
    struct EmeraldBattleTowerRecord *newRecord = newRecordEm; // Needed to match.

    // Find a record slot of the same player and replace it.
    for (i = 0; i < BATTLE_TOWER_RECORD_COUNT; i++)
    {
        k = 0;
        for (j = 0; j < TRAINER_ID_LENGTH; j++)
        {
            if (gSaveBlock2Ptr->frontier.towerRecords[i].trainerId[j] != newRecord->trainerId[j])
                break;
        }
        if (j == 4)
        {
            for (k = 0; k < PLAYER_NAME_LENGTH; k++)
            {
                #ifdef BUGFIX
                if (gSaveBlock2Ptr->frontier.towerRecords[i].name[k] != newRecord->name[k])
                    break;
                if (newRecord->name[k] == EOS)
                #else
                if (gSaveBlock2Ptr->frontier.towerRecords[i].name[j] != newRecord->name[j])
                    break;
                if (newRecord->name[j] == EOS)
                #endif  
                {
                    k = PLAYER_NAME_LENGTH;
                    break;
                }
            }
        }

        if (k == PLAYER_NAME_LENGTH)
            break;
    }
    if (i < BATTLE_TOWER_RECORD_COUNT)
    {
        gSaveBlock2Ptr->frontier.towerRecords[i] = *newRecord;
        return;
    }

    // Find an empty record slot.
    for (i = 0; i < BATTLE_TOWER_RECORD_COUNT; i++)
    {
        if (gSaveBlock2Ptr->frontier.towerRecords[i].winStreak == 0)
            break;
    }
    if (i < BATTLE_TOWER_RECORD_COUNT)
    {
        gSaveBlock2Ptr->frontier.towerRecords[i] = *newRecord;
        return;
    }

    // Find possible slots to replace the record.
    slotValues[0] = gSaveBlock2Ptr->frontier.towerRecords[0].winStreak;
    slotIds[0] = 0;
    slotsCount++;

    for (i = 1; i < BATTLE_TOWER_RECORD_COUNT; i++)
    {
        for (j = 0; j < slotsCount; j++)
        {
            if (gSaveBlock2Ptr->frontier.towerRecords[i].winStreak < slotValues[j])
            {
                j = 0;
                slotsCount = 1;
                slotValues[0] = gSaveBlock2Ptr->frontier.towerRecords[i].winStreak;
                slotIds[0] = i;
                break;
            }
            else if (gSaveBlock2Ptr->frontier.towerRecords[i].winStreak > slotValues[j])
            {
                break;
            }
        }

        if (j == slotsCount)
        {
            slotValues[slotsCount] = gSaveBlock2Ptr->frontier.towerRecords[i].winStreak;
            slotIds[slotsCount] = i;
            slotsCount++;
        }
    }

    i = Random() % slotsCount;
    gSaveBlock2Ptr->frontier.towerRecords[slotIds[i]] = *newRecord;
}

u8 GetFrontierTrainerFrontSpriteId(u16 trainerId)
{
    SetFacilityPtrsGetLevel();

    if (trainerId == TRAINER_EREADER)
    {
        return gFacilityClassToPicIndex[gSaveBlock2Ptr->frontier.ereaderTrainer.facilityClass];
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        return GetFrontierBrainTrainerPicIndex();
    }
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        return gFacilityClassToPicIndex[gFacilityTrainers[trainerId].facilityClass];
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            return gFacilityClassToPicIndex[GetRecordedBattleRecordMixFriendClass()];
        else
            return gFacilityClassToPicIndex[gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].facilityClass];
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            return gFacilityClassToPicIndex[gApprentices[GetRecordedBattleApprenticeId()].facilityClass];
        else
            return gFacilityClassToPicIndex[gApprentices[gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id].facilityClass];
    }
}

u8 GetFrontierOpponentClass(u16 trainerId)
{
    u8 trainerClass = 0;
    SetFacilityPtrsGetLevel();

    if (trainerId == TRAINER_EREADER)
    {
        trainerClass = gFacilityClassToTrainerClass[gSaveBlock2Ptr->frontier.ereaderTrainer.facilityClass];
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        return GetFrontierBrainTrainerClass();
    }
    else if (trainerId == TRAINER_STEVEN_PARTNER)
    {
        trainerClass = gTrainers[TRAINER_STEVEN].trainerClass;
    }
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        trainerClass = gFacilityClassToTrainerClass[gFacilityTrainers[trainerId].facilityClass];
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        {
            trainerClass = gFacilityClassToTrainerClass[GetRecordedBattleRecordMixFriendClass()];
        }
        else
        {
            trainerClass = gFacilityClassToTrainerClass[gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].facilityClass];
        }
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        {
            trainerClass = gFacilityClassToTrainerClass[gApprentices[GetRecordedBattleApprenticeId()].facilityClass];
        }
        else
        {
            trainerClass = gFacilityClassToTrainerClass[gApprentices[gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id].facilityClass];
        }
    }

    return trainerClass;
}

static u8 GetFrontierTrainerFacilityClass(u16 trainerId)
{
    u8 facilityClass;
    SetFacilityPtrsGetLevel();

    if (trainerId == TRAINER_EREADER)
    {
        facilityClass = gSaveBlock2Ptr->frontier.ereaderTrainer.facilityClass;
    }
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        facilityClass = gFacilityTrainers[trainerId].facilityClass;
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            facilityClass = GetRecordedBattleRecordMixFriendClass();
        else
            facilityClass = gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].facilityClass;
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            facilityClass = gApprentices[GetRecordedBattleApprenticeId()].facilityClass;
        else
            facilityClass = gApprentices[gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id].facilityClass;
    }

    return facilityClass;
}

void GetFrontierTrainerName(u8 *dst, u16 trainerId)
{
    s32 i = 0;
    SetFacilityPtrsGetLevel();

    if (trainerId == TRAINER_EREADER)
    {
        for (i = 0; i < PLAYER_NAME_LENGTH; i++)
            dst[i] = gSaveBlock2Ptr->frontier.ereaderTrainer.name[i];
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        CopyFrontierBrainTrainerName(dst);
        return;
    }
    else if (trainerId == TRAINER_STEVEN_PARTNER)
    {
        for (i = 0; i < PLAYER_NAME_LENGTH; i++)
            dst[i] = gTrainers[TRAINER_STEVEN].trainerName[i];
    }
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        for (i = 0; i < PLAYER_NAME_LENGTH; i++)
            dst[i] = gFacilityTrainers[trainerId].trainerName[i];
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        {
            GetRecordedBattleRecordMixFriendName(dst);
            return;
        }
        else
        {
            struct EmeraldBattleTowerRecord *record = &gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND];
            TVShowConvertInternationalString(dst, record->name, record->language);
            return;
        }
    }
    else
    {
        u8 id, language;

        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        {
            id = GetRecordedBattleApprenticeId();
            language = GetRecordedBattleApprenticeLanguage();
        }
        else
        {
            struct Apprentice *apprentice = &gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE];
            id = apprentice->id;
            language = apprentice->language;
        }
        TVShowConvertInternationalString(dst, GetApprenticeNameInLanguage(id, language), language);
        return;
    }

    dst[i] = EOS;
}

static bool8 IsFrontierTrainerFemale(u16 trainerId)
{
    u32 i;
    u8 facilityClass;

    SetFacilityPtrsGetLevel();
    if (trainerId == TRAINER_EREADER)
    {
        facilityClass = gSaveBlock2Ptr->frontier.ereaderTrainer.facilityClass;
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        return IsFrontierBrainFemale();
    }
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        facilityClass = gFacilityTrainers[trainerId].facilityClass;
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        facilityClass = gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].facilityClass;
    }
    else
    {
        facilityClass = gApprentices[gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id].facilityClass;
    }

    // Search female classes.
    for (i = 0; i < ARRAY_COUNT(gTowerFemaleFacilityClasses); i++)
    {
        if (gTowerFemaleFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gTowerFemaleFacilityClasses))
        return TRUE;
    else
        return FALSE;
}

void FillFrontierTrainerParty(u8 monsCount)
{
    ZeroEnemyPartyMons();
    FillTrainerParty(gTrainerBattleOpponent_A, 0, monsCount);
}

void FillFrontierTrainersParties(u8 monsCount)
{
    ZeroEnemyPartyMons();
    FillTrainerParty(gTrainerBattleOpponent_A, 0, monsCount);
    FillTrainerParty(gTrainerBattleOpponent_B, 3, monsCount);
}

static void FillTentTrainerParty(u8 monsCount)
{
    ZeroEnemyPartyMons();
    FillTentTrainerParty_(gTrainerBattleOpponent_A, 0, monsCount);
}

static void FillTrainerParty(u16 trainerId, u8 firstMonId, u8 monCount)
{
    s32 i, j;
    u16 chosenMonIndices[4];
    u8 friendship = MAX_FRIENDSHIP;
    u8 level = SetFacilityPtrsGetLevel();
    u8 fixedIV = 0;
    u8 bfMonCount;
    const u16 *monSet = NULL;
    u32 otID = 0;

    if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        // Normal battle frontier trainer.
        fixedIV = GetFrontierTrainerFixedIvs(trainerId);
        monSet = gFacilityTrainers[gTrainerBattleOpponent_A].monSet;
    }
    else if (trainerId == TRAINER_EREADER)
    {
        for (i = firstMonId; i < firstMonId + 3; i++)
            CreateBattleTowerMon(&gEnemyParty[i], &gSaveBlock2Ptr->frontier.ereaderTrainer.party[i - firstMonId]);
        return;
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        CreateFrontierBrainPokemon();
        return;
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        // Record mixed player.
        for (j = 0, i = firstMonId; i < firstMonId + monCount; j++, i++)
        {
            if (gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[j].species != 0
                && gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[j].level <= level)
            {
                CreateBattleTowerMon2(&gEnemyParty[i], &gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[j], FALSE);
            }
        }
        return;
    }
    else
    {
        // Apprentice.
        for (i = firstMonId; i < firstMonId + 3; i++)
            CreateApprenticeMon(&gEnemyParty[i], &gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE], i - firstMonId);
        return;
    }

    // Regular battle frontier trainer.
    // Attempt to fill the trainer's party with random Pokemon until 3 have been
    // successfully chosen. The trainer's party may not have duplicate pokemon species
    // or duplicate held items.
    for (bfMonCount = 0; monSet[bfMonCount] != 0xFFFF; bfMonCount++)
        ;
    i = 0;
    otID = Random32();
    while (i != monCount)
    {
        u16 monId = monSet[Random() % bfMonCount];
        if ((level == 50 || level == 20) && monId > FRONTIER_MONS_HIGH_TIER)
            continue;

        // Ensure this pokemon species isn't a duplicate.
        for (j = 0; j < i + firstMonId; j++)
        {
            if (GetMonData(&gEnemyParty[j], MON_DATA_SPECIES, NULL) == gFacilityTrainerMons[monId].species)
                break;
        }
        if (j != i + firstMonId)
            continue;

        // Ensure this Pokemon's held item isn't a duplicate.
        for (j = 0; j < i + firstMonId; j++)
        {
            if (GetMonData(&gEnemyParty[j], MON_DATA_HELD_ITEM, NULL) != 0
             && GetMonData(&gEnemyParty[j], MON_DATA_HELD_ITEM, NULL) == gBattleFrontierHeldItems[gFacilityTrainerMons[monId].itemTableId])
                break;
        }
        if (j != i + firstMonId)
            continue;

        // Ensure this exact pokemon index isn't a duplicate. This check doesn't seem necessary
        // because the species and held items were already checked directly above.
        for (j = 0; j < i; j++)
        {
            if (chosenMonIndices[j] == monId)
                break;
        }
        if (j != i)
            continue;

        chosenMonIndices[i] = monId;

        // Place the chosen pokemon into the trainer's party.
        CreateMonWithEVSpreadNatureOTID(&gEnemyParty[i + firstMonId],
                                             gFacilityTrainerMons[monId].species,
                                             level,
                                             gFacilityTrainerMons[monId].nature,
                                             fixedIV,
                                             gFacilityTrainerMons[monId].evSpread,
                                             otID);

        friendship = MAX_FRIENDSHIP;
        // Give the chosen pokemon its specified moves.
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            SetMonMoveSlot(&gEnemyParty[i + firstMonId], gFacilityTrainerMons[monId].moves[j], j);
            if (gFacilityTrainerMons[monId].moves[j] == MOVE_FRUSTRATION)
                friendship = 0;  // Frustration is more powerful the lower the pokemon's friendship is.
        }

        SetMonData(&gEnemyParty[i + firstMonId], MON_DATA_FRIENDSHIP, &friendship);
        SetMonData(&gEnemyParty[i + firstMonId], MON_DATA_HELD_ITEM, &gBattleFrontierHeldItems[gFacilityTrainerMons[monId].itemTableId]);

        // The pokemon was successfully added to the trainer's party, so it's safe to move on to
        // the next party slot.
        i++;
    }
}

// Probably an early draft before the 'CreateApprenticeMon' was written.
static void Unused_CreateApprenticeMons(u16 trainerId, u8 firstMonId)
{
    s32 i, j;
    u8 friendship = MAX_FRIENDSHIP;
    u8 level = 0;
    u8 fixedIV = 0;
    struct Apprentice *apprentice = &gSaveBlock2Ptr->apprentices[0];

    if (apprentice->numQuestions < 5)
        fixedIV = 6;
    else
        fixedIV = 9;

    if (gSaveBlock2Ptr->frontier.lvlMode != FRONTIER_LVL_50)
        level = 100;
    else
        level = 50;

    for (i = 0; i != 3; i++)
    {
        CreateMonWithEVSpread(&gEnemyParty[firstMonId + i], apprentice->party[i].species, level, fixedIV, 8);
        friendship = MAX_FRIENDSHIP;
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            if (apprentice->party[i].moves[j] == MOVE_FRUSTRATION)
                friendship = 0;
        }
        SetMonData(&gEnemyParty[firstMonId + i], MON_DATA_FRIENDSHIP, &friendship);
        SetMonData(&gEnemyParty[firstMonId + i], MON_DATA_HELD_ITEM, &apprentice->party[i].item);
    }
}

u16 GetRandomFrontierMonFromSet(u16 trainerId)
{
    u8 level = SetFacilityPtrsGetLevel();
    const u16 *monSet = gFacilityTrainers[trainerId].monSet;
    u8 numMons = 0;
    u32 monId = monSet[numMons];

    while (monId != 0xFFFF)
    {
        numMons++;
        monId = monSet[numMons];
        if (monId == 0xFFFF)
            break;
    }

    do
    {
        monId = monSet[Random() % numMons];
    } while((level == 50 || level == 20) && monId > FRONTIER_MONS_HIGH_TIER);

    return monId;
}

static void FillFactoryTrainerParty(void)
{
    ZeroEnemyPartyMons();
    if (gSaveBlock2Ptr->frontier.lvlMode != FRONTIER_LVL_TENT)
        FillFactoryFrontierTrainerParty(gTrainerBattleOpponent_A, 0);
    else
        FillFactoryTentTrainerParty(gTrainerBattleOpponent_A, 0);
}

static void FillFactoryFrontierTrainerParty(u16 trainerId, u8 firstMonId)
{
    u8 i, j;
    u8 friendship;
    u8 level;
    u8 fixedIV;
    u32 otID;

    if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        u8 lvlMode = gSaveBlock2Ptr->frontier.lvlMode; // Unused variable.
        u8 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
        u8 challengeNum = gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][0] / 7;
        if (gSaveBlock2Ptr->frontier.curChallengeBattleNum < 6)
            fixedIV = GetFactoryMonFixedIV(challengeNum, 0);
        else
            fixedIV = GetFactoryMonFixedIV(challengeNum, 1);
    }
    else if (trainerId == TRAINER_EREADER)
    {
        for (i = firstMonId; i < firstMonId + 3; i++)
            CreateBattleTowerMon(&gEnemyParty[i], &gSaveBlock2Ptr->frontier.ereaderTrainer.party[i - firstMonId]);
        return;
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        FillFactoryBrainParty();
        return;
    }
    else
    {
        fixedIV = 31;
    }

    level = SetFacilityPtrsGetLevel();
    otID = T1_READ_32(gSaveBlock2Ptr->playerTrainerId);
    for (i = 0; i < FRONTIER_PARTY_SIZE; i++)
    {
        u16 monId = gFrontierTempParty[i];
        CreateMonWithEVSpreadNatureOTID(&gEnemyParty[firstMonId + i],
                                             gFacilityTrainerMons[monId].species,
                                             level,
                                             gFacilityTrainerMons[monId].nature,
                                             fixedIV,
                                             gFacilityTrainerMons[monId].evSpread,
                                             otID);

        friendship = 0;
        for (j = 0; j < MAX_MON_MOVES; j++)
            SetMonMoveAvoidReturn(&gEnemyParty[firstMonId + i], gFacilityTrainerMons[monId].moves[j], j);

        SetMonData(&gEnemyParty[firstMonId + i], MON_DATA_FRIENDSHIP, &friendship);
        SetMonData(&gEnemyParty[firstMonId + i], MON_DATA_HELD_ITEM, &gBattleFrontierHeldItems[gFacilityTrainerMons[monId].itemTableId]);
    }
}

static void FillFactoryTentTrainerParty(u16 trainerId, u8 firstMonId)
{
    u8 i, j;
    u8 friendship;
    u8 level = 30;
    u8 fixedIV = 0;
    u32 otID = T1_READ_32(gSaveBlock2Ptr->playerTrainerId);

    for (i = 0; i < FRONTIER_PARTY_SIZE; i++)
    {
        u16 monId = gFrontierTempParty[i];
        CreateMonWithEVSpreadNatureOTID(&gEnemyParty[firstMonId + i],
                                             gFacilityTrainerMons[monId].species,
                                             level,
                                             gFacilityTrainerMons[monId].nature,
                                             fixedIV,
                                             gFacilityTrainerMons[monId].evSpread,
                                             otID);

        friendship = 0;
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            SetMonMoveAvoidReturn(&gEnemyParty[firstMonId + i], gFacilityTrainerMons[monId].moves[j], j);
            if (gFacilityTrainerMons[monId].moves[j] == MOVE_FRUSTRATION)
                friendship = 0;
        }

        SetMonData(&gEnemyParty[firstMonId + i], MON_DATA_FRIENDSHIP, &friendship);
        SetMonData(&gEnemyParty[firstMonId + i], MON_DATA_HELD_ITEM, &gBattleFrontierHeldItems[gFacilityTrainerMons[monId].itemTableId]);
    }
}

void FrontierSpeechToString(const u16 *words)
{
    ConvertEasyChatWordsToString(gStringVar4, words, 3, 2);
    if (GetStringWidth(1, gStringVar4, -1) > 204u)
    {
        s32 i = 0;

        ConvertEasyChatWordsToString(gStringVar4, words, 2, 3);
        while (gStringVar4[i++] != CHAR_NEWLINE)
            ;
        while (gStringVar4[i] != CHAR_NEWLINE)
            i++;

        gStringVar4[i] = CHAR_PROMPT_SCROLL;
    }
}

/* Begin generated frontier trainer text tables. */
/* Generated by codex-lab/refresh_frontier_text_from_original.py. */

static const u8 sFrontierTrainerText000Before[] = _("난 절대 지지 않아!");
static const u8 sFrontierTrainerText000PlayerLost[] = _("나 강하지?");
static const u8 sFrontierTrainerText000PlayerWon[] = _("뭐? 대체 어떻게?");
static const u8 sFrontierTrainerText001Before[] = _("져도 신경 안 써");
static const u8 sFrontierTrainerText001PlayerLost[] = _("이기면 좋긴 하지");
static const u8 sFrontierTrainerText001PlayerWon[] = _("제길... 지니까 신경 쓰이네");
static const u8 sFrontierTrainerText002Before[] = _("어이! 오늘 내 상대는 너야");
static const u8 sFrontierTrainerText002PlayerLost[] = _("하하하! 다음에 보자!");
static const u8 sFrontierTrainerText002PlayerWon[] = _("진짜 승부는 내일이라고");
static const u8 sFrontierTrainerText003Before[] = _("너 하나도 안 무섭네");
static const u8 sFrontierTrainerText003PlayerLost[] = _("네가 발버둥을\n치는 걸 보니 안타깝네");
static const u8 sFrontierTrainerText003PlayerWon[] = _("나한테 이런 일이 일어나다니!");
static const u8 sFrontierTrainerText004Before[] = _("오 이거 정말 신나는데!");
static const u8 sFrontierTrainerText004PlayerLost[] = _("내가 얼마나 강한지 안 믿기지!");
static const u8 sFrontierTrainerText004PlayerWon[] = _("저런... 영 별로네");
static const u8 sFrontierTrainerText005Before[] = _("박살날 준비나 하셔!");
static const u8 sFrontierTrainerText005PlayerLost[] = _("하하하!! 웃겨 죽겠네!");
static const u8 sFrontierTrainerText005PlayerWon[] = _("너 때문에 슬퍼졌어");
static const u8 sFrontierTrainerText006Before[] = _("난 공부만 하는 애가 아니야");
static const u8 sFrontierTrainerText006PlayerLost[] = _("너 공부가 부족해...");
static const u8 sFrontierTrainerText006PlayerWon[] = _("나 공부를 더 해야겠네...");
static const u8 sFrontierTrainerText007Before[] = _("포켓몬 배틀은 장난이 아니야!");
static const u8 sFrontierTrainerText007PlayerLost[] = _("너 제법인데?");
static const u8 sFrontierTrainerText007PlayerWon[] = _("우린 네 장난감 같았어");
static const u8 sFrontierTrainerText008Before[] = _("내가 이기면 멋져 보이겠지?");
static const u8 sFrontierTrainerText008PlayerLost[] = _("멋져! 그게 바로 나야");
static const u8 sFrontierTrainerText008PlayerWon[] = _("멋져 보이긴 글렀네");
static const u8 sFrontierTrainerText009Before[] = _("이길 때까지 포기하지 않아!");
static const u8 sFrontierTrainerText009PlayerLost[] = _("나한테 항복은 없어");
static const u8 sFrontierTrainerText009PlayerWon[] = _("끝이야... 포기할래...");
static const u8 sFrontierTrainerText010Before[] = _("내 작전은 아빠한테 배웠어");
static const u8 sFrontierTrainerText010PlayerLost[] = _("내가 이겼다! 아빠 저 이겼어요");
static const u8 sFrontierTrainerText010PlayerWon[] = _("졌어요 아빠... 용서해 주세요");
static const u8 sFrontierTrainerText011Before[] = _("부탁이니까 진심으로 배틀해 줘");
static const u8 sFrontierTrainerText011PlayerLost[] = _("고마워!! 정말 고마워");
static const u8 sFrontierTrainerText011PlayerWon[] = _("너 정말 진심이었어?");
static const u8 sFrontierTrainerText012Before[] = _("내가 진다고? 말도 안 돼!");
static const u8 sFrontierTrainerText012PlayerLost[] = _("당연히 내가 이기지");
static const u8 sFrontierTrainerText012PlayerWon[] = _("으아앙! 엄마 나 졌어");
static const u8 sFrontierTrainerText013Before[] = _("다들 내 멋진 포켓몬을 원해");
static const u8 sFrontierTrainerText013PlayerLost[] = _("포켓몬 파티를 열 거야");
static const u8 sFrontierTrainerText013PlayerWon[] = _("어떻게 그런 짓을?");
static const u8 sFrontierTrainerText014Before[] = _("난 멋진 포켓몬이 정말 좋아");
static const u8 sFrontierTrainerText014PlayerLost[] = _("이길 때의 내가 좋아!");
static const u8 sFrontierTrainerText014PlayerWon[] = _("질 때의 나도 좋아");
static const u8 sFrontierTrainerText015Before[] = _("내가 이기면 기술 하나 줄게");
static const u8 sFrontierTrainerText015PlayerLost[] = _("내 포켓몬의 기술 맛이 어때?");
static const u8 sFrontierTrainerText015PlayerWon[] = _("졌지만 안 줄 거야");
static const u8 sFrontierTrainerText016Before[] = _("미식가 타령은 이제 한물갔어");
static const u8 sFrontierTrainerText016PlayerLost[] = _("포켓몬은 절대 유행을 타지 않아");
static const u8 sFrontierTrainerText016PlayerWon[] = _("져도 실망하지 않겠어");
static const u8 sFrontierTrainerText017Before[] = _("난 걱정 하나 없어");
static const u8 sFrontierTrainerText017PlayerLost[] = _("인생은 언제나 내 편이야");
static const u8 sFrontierTrainerText017PlayerWon[] = _("내 포켓몬 실력이 걱정되는걸");
static const u8 sFrontierTrainerText018Before[] = _("오늘 제대로 날뛸 준비가 됐다고!");
static const u8 sFrontierTrainerText018PlayerLost[] = _("이 기세로 계속 가야지!");
static const u8 sFrontierTrainerText018PlayerWon[] = _("기합도 강인함도 잃었어");
static const u8 sFrontierTrainerText019Before[] = _("표정을 보니 너 꽤 강하구나");
static const u8 sFrontierTrainerText019PlayerLost[] = _("진짜로 강한 건 나라고");
static const u8 sFrontierTrainerText019PlayerWon[] = _("내 말이 맞았어! 너 정말 강하네");
static const u8 sFrontierTrainerText020Before[] = _("대자연은 내 편이야!");
static const u8 sFrontierTrainerText020PlayerLost[] = _("이 정도면 충분했지?");
static const u8 sFrontierTrainerText020PlayerWon[] = _("대자연이 날 등졌다고?");
static const u8 sFrontierTrainerText021Before[] = _("못 기다리겠어! 당장 배틀하자");
static const u8 sFrontierTrainerText021PlayerLost[] = _("행복이 벅차올라!");
static const u8 sFrontierTrainerText021PlayerWon[] = _("네가 내 행복을 박살냈어...");
static const u8 sFrontierTrainerText022Before[] = _("귀엽고 엄청 강한 게 바로 나야");
static const u8 sFrontierTrainerText022PlayerLost[] = _("응! 난 귀엽고 엄청 강해");
static const u8 sFrontierTrainerText022PlayerWon[] = _("나는 약해...\n하지만 귀여워");
static const u8 sFrontierTrainerText023Before[] = _("나이는 들었지만 실력은 좋다네");
static const u8 sFrontierTrainerText023PlayerLost[] = _("나이 들었어도\n실력이 좋다고 하지 않았는가");
static const u8 sFrontierTrainerText023PlayerWon[] = _("나이가 들어서 그런가...");
static const u8 sFrontierTrainerText024Before[] = _("이기면 파도타기하러 가야지");
static const u8 sFrontierTrainerText024PlayerLost[] = _("좋았어! 파도타기하러 간다");
static const u8 sFrontierTrainerText024PlayerWon[] = _("젠장 너 바다회오리였구나!");
static const u8 sFrontierTrainerText025Before[] = _("좋은 작전 좀 가르쳐 줘");
static const u8 sFrontierTrainerText025PlayerLost[] = _("그게 네 좋은 작전이었어!?");
static const u8 sFrontierTrainerText025PlayerWon[] = _("와 굉장한 작전인데!?");
static const u8 sFrontierTrainerText026Before[] = _("나 신참 트레이너야");
static const u8 sFrontierTrainerText026PlayerLost[] = _("신참이지만 내가 이겼어!");
static const u8 sFrontierTrainerText026PlayerWon[] = _("신참인데 좀 지면 어때?");
static const u8 sFrontierTrainerText027Before[] = _("정말 신난다! 진짜로");
static const u8 sFrontierTrainerText027PlayerLost[] = _("기뻐서 울 것 같아");
static const u8 sFrontierTrainerText027PlayerWon[] = _("슬퍼서 울 것 같아");
static const u8 sFrontierTrainerText028Before[] = _("나 어른인 척해도 되지?");
static const u8 sFrontierTrainerText028PlayerLost[] = _("이게 어른의 기분이구나");
static const u8 sFrontierTrainerText028PlayerWon[] = _("어른도 널 못 이기네?");
static const u8 sFrontierTrainerText029Before[] = _("내 여름방학은 포켓몬을 위한 거야!");
static const u8 sFrontierTrainerText029PlayerLost[] = _("내 여름방학은 끝내줄 거야!");
static const u8 sFrontierTrainerText029PlayerWon[] = _("여름방학 동안 특훈해야 되나...");
static const u8 sFrontierTrainerText030Before[] = _("장담하는데 내가 이겨!");
static const u8 sFrontierTrainerText030PlayerLost[] = _("좋았어! 정말로 이겼다");
static const u8 sFrontierTrainerText030PlayerWon[] = _("되는 일이 하나도 없네");
static const u8 sFrontierTrainerText031Before[] = _("덤벼! 뜨거운 배틀이 필요해");
static const u8 sFrontierTrainerText031PlayerLost[] = _("식히려면 물이 필요해");
static const u8 sFrontierTrainerText031PlayerWon[] = _("너 때문에 얼음처럼 식었어");
static const u8 sFrontierTrainerText032Before[] = _("난 겨울에도 파도타기를 해");
static const u8 sFrontierTrainerText032PlayerLost[] = _("지금 바로 파도타기하러 갈 거야");
static const u8 sFrontierTrainerText032PlayerWon[] = _("내 파도타기 보드를\n집단구타해 버릴 거야");
static const u8 sFrontierTrainerText033Before[] = _("너 나와 싱크로해라");
static const u8 sFrontierTrainerText033PlayerLost[] = _("나와 포켓몬의 싱크로를\n따라오지 못했구나");
static const u8 sFrontierTrainerText033PlayerWon[] = _("싱크로를 더 잘 맞춰야겠어...");
static const u8 sFrontierTrainerText034Before[] = _("내가 한 방 넣으면 너는 추방!");
static const u8 sFrontierTrainerText034PlayerLost[] = _("역시 한 방에 가네!");
static const u8 sFrontierTrainerText034PlayerWon[] = _("한 방에 갔다...");
static const u8 sFrontierTrainerText035Before[] = _("오늘 승부는 전부 이겼어!");
static const u8 sFrontierTrainerText035PlayerLost[] = _("이기니까 정말 좋다!");
static const u8 sFrontierTrainerText035PlayerWon[] = _("어? 지면 안 되는데");
static const u8 sFrontierTrainerText036Before[] = _("난 내 포켓몬에게\n절대 실망하지 않아");
static const u8 sFrontierTrainerText036PlayerLost[] = _("함께 이기면 난 기뻐");
static const u8 sFrontierTrainerText036PlayerWon[] = _("져도 내 포켓몬이 더 소중해져");
static const u8 sFrontierTrainerText037Before[] = _("너도 네 포켓몬을 아끼지?");
static const u8 sFrontierTrainerText037PlayerLost[] = _("넌 전혀 상대가 안 돼");
static const u8 sFrontierTrainerText037PlayerWon[] = _("역시 너도\n네 포켓몬을 아끼는구나!");
static const u8 sFrontierTrainerText038Before[] = _("내 포켓몬은 꿈같은 존재야");
static const u8 sFrontierTrainerText038PlayerLost[] = _("이건 아름다운 꿈이야!");
static const u8 sFrontierTrainerText038PlayerWon[] = _("이건 끔찍한 악몽이야!");
static const u8 sFrontierTrainerText039Before[] = _("내 기분을 나도 모르겠어");
static const u8 sFrontierTrainerText039PlayerLost[] = _("기쁨이 벅차올라");
static const u8 sFrontierTrainerText039PlayerWon[] = _("완전히 박살난 기분이야");
static const u8 sFrontierTrainerText040Before[] = _("난 트레이너 가문 출신이야");
static const u8 sFrontierTrainerText040PlayerLost[] = _("이 승리는 소중히 간직할게");
static const u8 sFrontierTrainerText040PlayerWon[] = _("지금 당장 집에 가고 싶어");
static const u8 sFrontierTrainerText041Before[] = _("모든 포켓몬에겐\n저마다의 매력이 있어");
static const u8 sFrontierTrainerText041PlayerLost[] = _("내 말이 뭔지 알겠지?");
static const u8 sFrontierTrainerText041PlayerWon[] = _("포켓몬을 아끼지 않을 수 있겠어?");
static const u8 sFrontierTrainerText042Before[] = _("덤벼! 기합 좀 보여 줘");
static const u8 sFrontierTrainerText042PlayerLost[] = _("그거야! 그게 기합이지!");
static const u8 sFrontierTrainerText042PlayerWon[] = _("우리 기합도 여기까지였네");
static const u8 sFrontierTrainerText043Before[] = _("천재는 바로\n날 두고 하는 말이라고!");
static const u8 sFrontierTrainerText043PlayerLost[] = _("봤지? 천재의 배틀을!");
static const u8 sFrontierTrainerText043PlayerWon[] = _("네가 나보다 더 천재구나");
static const u8 sFrontierTrainerText044Before[] = _("알 때부터 단련시킨 포켓몬...");
static const u8 sFrontierTrainerText044PlayerLost[] = _("제법이네!");
static const u8 sFrontierTrainerText044PlayerWon[] = _("다시 알부터 키울까...");
static const u8 sFrontierTrainerText045Before[] = _("모든 포켓몬은 다정한\n트레이너를 좋아해");
static const u8 sFrontierTrainerText045PlayerLost[] = _("네가 져서 안됐네");
static const u8 sFrontierTrainerText045PlayerWon[] = _("넌 다정하고 강하기까지 하네");
static const u8 sFrontierTrainerText046Before[] = _("난 포켓몬을 내 아이처럼 아껴");
static const u8 sFrontierTrainerText046PlayerLost[] = _("내 포켓몬이 자랑스러워");
static const u8 sFrontierTrainerText046PlayerWon[] = _("이런... 포켓몬에게 미안하네");
static const u8 sFrontierTrainerText047Before[] = _("진지하게 배틀하겠다고 약속할게");
static const u8 sFrontierTrainerText047PlayerLost[] = _("다음엔 더 잘하겠다고 약속해");
static const u8 sFrontierTrainerText047PlayerWon[] = _("또 배틀해 주겠다고 약속해줘!");
static const u8 sFrontierTrainerText048Before[] = _("작은 벌레도 무섭지? 하하하");
static const u8 sFrontierTrainerText048PlayerLost[] = _("잘 봐! 무서운 벌레야");
static const u8 sFrontierTrainerText048PlayerWon[] = _("오... 벌레가 안 무섭나 봐...?");
static const u8 sFrontierTrainerText049Before[] = _("벌레포켓몬을 보면 마음이 설레");
static const u8 sFrontierTrainerText049PlayerLost[] = _("벌레포켓몬이 최고야!");
static const u8 sFrontierTrainerText049PlayerWon[] = _("넌 벌레포켓몬을 몰라");
static const u8 sFrontierTrainerText050Before[] = _("여긴 너무 더워");
static const u8 sFrontierTrainerText050PlayerLost[] = _("이제 오버히트 될 참이었어");
static const u8 sFrontierTrainerText050PlayerWon[] = _("누가 잔비 좀 내려줘");
static const u8 sFrontierTrainerText051Before[] = _("미안하지만 간다!");
static const u8 sFrontierTrainerText051PlayerLost[] = _("내 압도적인 힘을 용서해줘");
static const u8 sFrontierTrainerText051PlayerWon[] = _("미안해...");
static const u8 sFrontierTrainerText052Before[] = _("뜨거운 배틀을 약속할게");
static const u8 sFrontierTrainerText052PlayerLost[] = _("멋의 달인! 그게 나야");
static const u8 sFrontierTrainerText052PlayerWon[] = _("나 그렇게 안 멋진가...?");
static const u8 sFrontierTrainerText053Before[] = _("정말 매끄러운 기술을 보여줘");
static const u8 sFrontierTrainerText053PlayerLost[] = _("하나도 매끄럽지 않았어");
static const u8 sFrontierTrainerText053PlayerWon[] = _("너 정말 매끄럽네!");
static const u8 sFrontierTrainerText054Before[] = _("나처럼 요가포즈하는 걸 보여줘");
static const u8 sFrontierTrainerText054PlayerLost[] = _("내 요가포즈 아름답지?");
static const u8 sFrontierTrainerText054PlayerWon[] = _("요가포즈가 흐트러졌어...");
static const u8 sFrontierTrainerText055Before[] = _("우리의 독가루 기술엔\n목화포자가 담겨 있지");
static const u8 sFrontierTrainerText055PlayerLost[] = _("우리의 독가루 어땠어?");
static const u8 sFrontierTrainerText055PlayerWon[] = _("목화포자가 소용없었어...");
static const u8 sFrontierTrainerText056Before[] = _("어? 어디 있지");
static const u8 sFrontierTrainerText056PlayerLost[] = _("어디 있지?\n내 포켓내비를 잃어버렸어");
static const u8 sFrontierTrainerText056PlayerWon[] = _("어디 갔지? 내 감을 잃어버렸어");
static const u8 sFrontierTrainerText057Before[] = _("맛있는물 좀 마시러 와");
static const u8 sFrontierTrainerText057PlayerLost[] = _("음! 너도 좀 마실래?");
static const u8 sFrontierTrainerText057PlayerWon[] = _("쇼핑하다가 이 맛있는물을 샀어");
static const u8 sFrontierTrainerText058Before[] = _("내 포켓몬이 널\n풀죽게 만들 거야");
static const u8 sFrontierTrainerText058PlayerLost[] = _("풀죽은 채로 풀베기나 쓰셔!");
static const u8 sFrontierTrainerText058PlayerWon[] = _("풀이 죽은 트레이너...\n그건 바로 나");
static const u8 sFrontierTrainerText059Before[] = _("냐옹 하면서 울 거야");
static const u8 sFrontierTrainerText059PlayerLost[] = _("나 귀엽지? 냐옹-");
static const u8 sFrontierTrainerText059PlayerWon[] = _("냐옹! 냐옹!! 냐옹!!!");
static const u8 sFrontierTrainerText060Before[] = _("내 난동부리기를\n받을 준비나 하시지!");
static const u8 sFrontierTrainerText060PlayerLost[] = _("와하하하!\n이거 미안하게 됐는걸!");
static const u8 sFrontierTrainerText060PlayerWon[] = _("넌 차분한 성격이구나");
static const u8 sFrontierTrainerText061Before[] = _("마음만은 젊다고!");
static const u8 sFrontierTrainerText061PlayerLost[] = _("전혀 멋지지 않아!");
static const u8 sFrontierTrainerText061PlayerWon[] = _("나이 들고 몸도 떨리네...");
static const u8 sFrontierTrainerText062Before[] = _("내 포켓몬들은 날뛸 준비가 됐어!");
static const u8 sFrontierTrainerText062PlayerLost[] = _("내 포켓몬들은 정말 굉장해!");
static const u8 sFrontierTrainerText062PlayerWon[] = _("내 포켓몬들이 안타까워서 울겠어...");
static const u8 sFrontierTrainerText063Before[] = _("난 최고야! 라이벌도 없다고");
static const u8 sFrontierTrainerText063PlayerLost[] = _("봤지? 난 질 수가 없다니까");
static const u8 sFrontierTrainerText063PlayerWon[] = _("안 돼! 납득 못 한다고!");
static const u8 sFrontierTrainerText064Before[] = _("야호! 야호!!");
static const u8 sFrontierTrainerText064PlayerLost[] = _("고마워! 고마워!!");
static const u8 sFrontierTrainerText064PlayerWon[] = _("안녕! 안녕!!");
static const u8 sFrontierTrainerText065Before[] = _("헷갈려? 난 천재라고");
static const u8 sFrontierTrainerText065PlayerLost[] = _("봤지? 난 천재라고");
static const u8 sFrontierTrainerText065PlayerWon[] = _("배틀에선 천재가 아니었네");
static const u8 sFrontierTrainerText066Before[] = _("나 쇼핑을 너무 많이 하나 봐");
static const u8 sFrontierTrainerText066PlayerLost[] = _("그래도 포켓몬\n봉제인형을 갖고 싶어");
static const u8 sFrontierTrainerText066PlayerWon[] = _("포켓몬 봉제인형을\n하나 더 갖고 싶어");
static const u8 sFrontierTrainerText067Before[] = _("네 근성을 보여 줘");
static const u8 sFrontierTrainerText067PlayerLost[] = _("잘 가! 넌 근성이 없네");
static const u8 sFrontierTrainerText067PlayerWon[] = _("근성 있네... 너 꽤 대단한걸");
static const u8 sFrontierTrainerText068Before[] = _("진심으로 이길 거야!");
static const u8 sFrontierTrainerText068PlayerLost[] = _("내 의욕을 뼈저리게 느꼈지?");
static const u8 sFrontierTrainerText068PlayerWon[] = _("너 의욕이 너무 센 거 아냐?");
static const u8 sFrontierTrainerText069Before[] = _("이번 내 상대는 너구나!");
static const u8 sFrontierTrainerText069PlayerLost[] = _("저런 너무 약하네!\n포기하지는 마!");
static const u8 sFrontierTrainerText069PlayerWon[] = _("좋은 승부였어! 그럼 안녕");
static const u8 sFrontierTrainerText070Before[] = _("내가 지면 프레젠트를 줄게");
static const u8 sFrontierTrainerText070PlayerLost[] = _("자! 프레젠트 대신\n약간 칭찬해 줄게");
static const u8 sFrontierTrainerText070PlayerWon[] = _("뭐 프레젠트!?\n여기 연속뺨치기를 받아랏!");
static const u8 sFrontierTrainerText071Before[] = _("난 귀여운 패션의 힘을 믿어");
static const u8 sFrontierTrainerText071PlayerLost[] = _("네 패션 감각은 재앙이야");
static const u8 sFrontierTrainerText071PlayerWon[] = _("끔찍했어! 나 집에 갈래");
static const u8 sFrontierTrainerText072Before[] = _("이 냄새는 뭐지?");
static const u8 sFrontierTrainerText072PlayerLost[] = _("맛있는물의 달콤한향기였구나");
static const u8 sFrontierTrainerText072PlayerWon[] = _("네 지독한 악취였구나");
static const u8 sFrontierTrainerText073Before[] = _("내 비밀 아로마테라피를 받아볼래?");
static const u8 sFrontierTrainerText073PlayerLost[] = _("내 아로마테라피는\n너한테 끔찍할 거야");
static const u8 sFrontierTrainerText073PlayerWon[] = _("너 아무 냄새도 못 맡았니!?");
static const u8 sFrontierTrainerText074Before[] = _("내 남자친구는\n일을 너무 많이 해");
static const u8 sFrontierTrainerText074PlayerLost[] = _("그 사람이 더\n그리워질 뿐이야...");
static const u8 sFrontierTrainerText074PlayerWon[] = _("그 사람이 없으니\n너무 외로워...");
static const u8 sFrontierTrainerText075Before[] = _("난 꽃잎댄스를 출 줄 알아");
static const u8 sFrontierTrainerText075PlayerLost[] = _("하지만 춤추는 건 별로야");
static const u8 sFrontierTrainerText075PlayerWon[] = _("댄스고 나발이고\n그냥 바둥바둥할래");
static const u8 sFrontierTrainerText076Before[] = _("안녕!\n너 마음에 드는데?");
static const u8 sFrontierTrainerText076PlayerLost[] = _("너 때문에 난동부리기를\n쓰고 싶은 기분이야");
static const u8 sFrontierTrainerText076PlayerWon[] = _("이걸로 끝이야!\n영원히 안녕!");
static const u8 sFrontierTrainerText077Before[] = _("힘차게 춤춰야 해");
static const u8 sFrontierTrainerText077PlayerLost[] = _("알겠지? 힘차게 춤추는 거야");
static const u8 sFrontierTrainerText077PlayerWon[] = _("좋았어! 이제 알겠지!");
static const u8 sFrontierTrainerText078Before[] = _("변색된 포켓몬은\n필요없어!");
static const u8 sFrontierTrainerText078PlayerLost[] = _("난 멀쩡한 색 포켓몬만\n모은다고");
static const u8 sFrontierTrainerText078PlayerWon[] = _("변색된 포켓몬에\n헤롱헤롱...");
static const u8 sFrontierTrainerText079Before[] = _("너한테 집단구타를\n먹일 차례야");
static const u8 sFrontierTrainerText079PlayerLost[] = _("너무 쉬워!\n난 정말 멋져");
static const u8 sFrontierTrainerText079PlayerWon[] = _("왜 진 거지?!\n저주해 주맛!!");
static const u8 sFrontierTrainerText080Before[] = _("좋아 승부하자!");
static const u8 sFrontierTrainerText080PlayerLost[] = _("예이! 내가 최고야");
static const u8 sFrontierTrainerText080PlayerWon[] = _("진짜로!?");
static const u8 sFrontierTrainerText081Before[] = _("난 완벽하니까\n지금 포기해!");
static const u8 sFrontierTrainerText081PlayerLost[] = _("좋아 내 승리!");
static const u8 sFrontierTrainerText081PlayerWon[] = _("대체 어떻게?\n난 완벽한데...");
static const u8 sFrontierTrainerText082Before[] = _("한판 붙어보자!");
static const u8 sFrontierTrainerText082PlayerLost[] = _("이 정도면 충분했지?");
static const u8 sFrontierTrainerText082PlayerWon[] = _("인정할게!\n네가 이겼어");
static const u8 sFrontierTrainerText083Before[] = _("내 라이벌 시켜줄까?");
static const u8 sFrontierTrainerText083PlayerLost[] = _("역시 내가 한 수 위야!");
static const u8 sFrontierTrainerText083PlayerWon[] = _("아쉽지만 완패야...");
static const u8 sFrontierTrainerText084Before[] = _("난 충전하는 법만 알아");
static const u8 sFrontierTrainerText084PlayerLost[] = _("압도적인 승리로\n완전 충전!");
static const u8 sFrontierTrainerText084PlayerWon[] = _("압도적인 패배로\n완전 방전...");
static const u8 sFrontierTrainerText085Before[] = _("태만함만 믿고 간다!");
static const u8 sFrontierTrainerText085PlayerLost[] = _("난 역시 위협적이야");
static const u8 sFrontierTrainerText085PlayerWon[] = _("미안해...");
static const u8 sFrontierTrainerText086Before[] = _("객기 한 방이면 충분해!");
static const u8 sFrontierTrainerText086PlayerLost[] = _("너 정말 진심이야?");
static const u8 sFrontierTrainerText086PlayerWon[] = _("너 정말 강하네.");
static const u8 sFrontierTrainerText087Before[] = _("제대로 상대해 줄게!");
static const u8 sFrontierTrainerText087PlayerLost[] = _("불! 불!!");
static const u8 sFrontierTrainerText087PlayerWon[] = _("좋은 승부였어");
static const u8 sFrontierTrainerText088Before[] = _("포켓몬 도감의 힘을\n보여줄게!");
static const u8 sFrontierTrainerText088PlayerLost[] = _("봤지?\n내가 이겼어!");
static const u8 sFrontierTrainerText088PlayerWon[] = _("포켓내비도\n써야 하나...");
static const u8 sFrontierTrainerText089Before[] = _("불타오른다!");
static const u8 sFrontierTrainerText089PlayerLost[] = _("너한텐 불꽃세례만\n써도 이겨");
static const u8 sFrontierTrainerText089PlayerWon[] = _("꺄악!!\n물은 제발 안 돼");
static const u8 sFrontierTrainerText090Before[] = _("하하하!\n만나서 반가워!");
static const u8 sFrontierTrainerText090PlayerLost[] = _("봤지?\n이게 바로 하늘의은총이라고!");
static const u8 sFrontierTrainerText090PlayerWon[] = _("난동부리기 할 거야...");
static const u8 sFrontierTrainerText091Before[] = _("이번 승부수는 순간이동!");
static const u8 sFrontierTrainerText091PlayerLost[] = _("넌 여기 밖으로 순간이동!");
static const u8 sFrontierTrainerText091PlayerWon[] = _("순간이동도 안 통하다니...");
static const u8 sFrontierTrainerText092Before[] = _("난 수행을 잘한단 말이지");
static const u8 sFrontierTrainerText092PlayerLost[] = _("막기 어려웠지?");
static const u8 sFrontierTrainerText092PlayerWon[] = _("이번엔 내가 졌네");
static const u8 sFrontierTrainerText093Before[] = _("쉽게 이길 생각은 하지 마!");
static const u8 sFrontierTrainerText093PlayerLost[] = _("앗싸! 내가 이겼어!");
static const u8 sFrontierTrainerText093PlayerWon[] = _("너 정말 강하네.");
static const u8 sFrontierTrainerText094Before[] = _("좋았어!! 이번엔 완벽해");
static const u8 sFrontierTrainerText094PlayerLost[] = _("좋았어!! 내가 이겼어");
static const u8 sFrontierTrainerText094PlayerWon[] = _("으... 생각보다 강하잖아...");
static const u8 sFrontierTrainerText095Before[] = _("제대로 상대해줄게!");
static const u8 sFrontierTrainerText095PlayerLost[] = _("바로 이거야! 멋져!");
static const u8 sFrontierTrainerText095PlayerWon[] = _("뭐야 어떻게 된 거지?");
static const u8 sFrontierTrainerText096Before[] = _("좋아 승부하자!");
static const u8 sFrontierTrainerText096PlayerLost[] = _("승리를 향해 다이빙!");
static const u8 sFrontierTrainerText096PlayerWon[] = _("부끄러운 나머지 다이빙...");
static const u8 sFrontierTrainerText097Before[] = _("와봐랏!");
static const u8 sFrontierTrainerText097PlayerLost[] = _("좋아 내 승리야!");
static const u8 sFrontierTrainerText097PlayerWon[] = _("집단구타 당한 기분이야");
static const u8 sFrontierTrainerText098Before[] = _("승부수는 배틀!");
static const u8 sFrontierTrainerText098PlayerLost[] = _("드디어 이겼어...\n나 피곤해");
static const u8 sFrontierTrainerText098PlayerWon[] = _("드디어 졌어...\n나 피곤해");
static const u8 sFrontierTrainerText099Before[] = _("나는야 전광석화 트레이너!");
static const u8 sFrontierTrainerText099PlayerLost[] = _("전광석화 트레이너의 승리!");
static const u8 sFrontierTrainerText099PlayerWon[] = _("전광석화 같은 패배였어...");
static const u8 sFrontierTrainerText100Before[] = _("가속 히어로 등장!");
static const u8 sFrontierTrainerText100PlayerLost[] = _("가속 히어로의 압도적인 승리!");
static const u8 sFrontierTrainerText100PlayerWon[] = _("가속 히어로는 도망쳤다!!");
static const u8 sFrontierTrainerText101Before[] = _("자전거를 타는 것보단\n달리는 게 낫지");
static const u8 sFrontierTrainerText101PlayerLost[] = _("자전거나 타고 가지 그래?");
static const u8 sFrontierTrainerText101PlayerWon[] = _("러닝슈즈로 빠르게 도망치겠어");
static const u8 sFrontierTrainerText102Before[] = _("자 배틀 시작이야!");
static const u8 sFrontierTrainerText102PlayerLost[] = _("이번엔 내가 이겼네!");
static const u8 sFrontierTrainerText102PlayerWon[] = _("으 생각보다 강하잖아...");
static const u8 sFrontierTrainerText103Before[] = _("진심으로 상대해줄게!");
static const u8 sFrontierTrainerText103PlayerLost[] = _("승리는 내 차지야!");
static const u8 sFrontierTrainerText103PlayerWon[] = _("좋은 승부였어");
static const u8 sFrontierTrainerText104Before[] = _("좋아 승부하자!");
static const u8 sFrontierTrainerText104PlayerLost[] = _("봤지? 내가 이겼어!");
static const u8 sFrontierTrainerText104PlayerWon[] = _("가서 게임이나 해야지");
static const u8 sFrontierTrainerText105Before[] = _("신속하게 승부!!");
static const u8 sFrontierTrainerText105PlayerLost[] = _("신속하게 이겼다!");
static const u8 sFrontierTrainerText105PlayerWon[] = _("신속하게 졌어...");
static const u8 sFrontierTrainerText106Before[] = _("한판 붙어보자!");
static const u8 sFrontierTrainerText106PlayerLost[] = _("아하하 완전 못해!");
static const u8 sFrontierTrainerText106PlayerWon[] = _("아하하 재밌었어!");
static const u8 sFrontierTrainerText107Before[] = _("내 자전거는 아주 비싸");
static const u8 sFrontierTrainerText107PlayerLost[] = _("실력도 내가 한 수 위구나!");
static const u8 sFrontierTrainerText107PlayerWon[] = _("아쉽지만 완패야...");
static const u8 sFrontierTrainerText108Before[] = _("꺄악 승부한다!!");
static const u8 sFrontierTrainerText108PlayerLost[] = _("꺄악 내가 이겼잖아!?");
static const u8 sFrontierTrainerText108PlayerWon[] = _("꺄악 미안해!!");
static const u8 sFrontierTrainerText109Before[] = _("전력으로 덤벼!\n시간 없어");
static const u8 sFrontierTrainerText109PlayerLost[] = _("내 실력 어땠어?");
static const u8 sFrontierTrainerText109PlayerWon[] = _("다음엔 꼭 이길 거야");
static const u8 sFrontierTrainerText110Before[] = _("자! 배틀 시작이야!");
static const u8 sFrontierTrainerText110PlayerLost[] = _("이번엔 내가 이겼네!");
static const u8 sFrontierTrainerText110PlayerWon[] = _("으 생각보다 좀 하네...");
static const u8 sFrontierTrainerText111Before[] = _("공중날기 하는 네게\n따라가때리기를 해주겠어");
static const u8 sFrontierTrainerText111PlayerLost[] = _("나는 위너!\n울부짖기 하는 나");
static const u8 sFrontierTrainerText111PlayerWon[] = _("뛰어오르기 할 타이밍을 놓쳤나...");
static const u8 sFrontierTrainerText112Before[] = _("밤의 학교는 정말 무서워");
static const u8 sFrontierTrainerText112PlayerLost[] = _("귀신이야 사람 살려!");
static const u8 sFrontierTrainerText112PlayerWon[] = _("졌어... 너 강하네");
static const u8 sFrontierTrainerText113Before[] = _("준비됐어? 간다!");
static const u8 sFrontierTrainerText113PlayerLost[] = _("내 힘을 뼈저리게 느꼈지?");
static const u8 sFrontierTrainerText113PlayerWon[] = _("형편없어... 나는 형편없어...");
static const u8 sFrontierTrainerText114Before[] = _("모든 배틀에는 만남이 있어요");
static const u8 sFrontierTrainerText114PlayerLost[] = _("달콤한향기 덕분에 이겼어요!");
static const u8 sFrontierTrainerText114PlayerWon[] = _("악취보다 강한 당신...");
static const u8 sFrontierTrainerText115Before[] = _("나 포켓몬 잘해! 덤벼!!");
static const u8 sFrontierTrainerText115PlayerLost[] = _("역시 내가 한 수 위야!");
static const u8 sFrontierTrainerText115PlayerWon[] = _("뭐야!? 대체 어떻게?");
static const u8 sFrontierTrainerText116Before[] = _("후후후...");
static const u8 sFrontierTrainerText116PlayerLost[] = _("킥킥...");
static const u8 sFrontierTrainerText116PlayerWon[] = _("하하하...");
static const u8 sFrontierTrainerText117Before[] = _("하하하... 각오해...!");
static const u8 sFrontierTrainerText117PlayerLost[] = _("내 실력 어땠어?");
static const u8 sFrontierTrainerText117PlayerWon[] = _("강하잖아? 흥!");
static const u8 sFrontierTrainerText118Before[] = _("어? 뭐야 너?");
static const u8 sFrontierTrainerText118PlayerLost[] = _("이번엔 내가 이겼네!");
static const u8 sFrontierTrainerText118PlayerWon[] = _("졌어 흑흑...");
static const u8 sFrontierTrainerText119Before[] = _("오늘은! 배틀이! 답이야!");
static const u8 sFrontierTrainerText119PlayerLost[] = _("더! 배틀! 할래!");
static const u8 sFrontierTrainerText119PlayerWon[] = _("오! 강하다! 너!");
static const u8 sFrontierTrainerText120Before[] = _("난 너밖에 몰라");
static const u8 sFrontierTrainerText120PlayerLost[] = _("실례지만 넌 만만해!");
static const u8 sFrontierTrainerText120PlayerWon[] = _("너 꽤 대단한데!");
static const u8 sFrontierTrainerText121Before[] = _("서로 마음껏 돌머리를\n부딪쳐 보자고!");
static const u8 sFrontierTrainerText121PlayerLost[] = _("너 돌머리구나");
static const u8 sFrontierTrainerText121PlayerWon[] = _("네 돌머리에\n내 돌머리가 깨졌어...");
static const u8 sFrontierTrainerText122Before[] = _("흉내내기의 힘을 보여줄게!");
static const u8 sFrontierTrainerText122PlayerLost[] = _("토게피처럼 기뻐하기!");
static const u8 sFrontierTrainerText122PlayerWon[] = _("망키처럼 화내기!");
static const u8 sFrontierTrainerText123Before[] = _("에스퍼 느낌으로 승부하자!");
static const u8 sFrontierTrainerText123PlayerLost[] = _("망각술이라도 썼니?");
static const u8 sFrontierTrainerText123PlayerWon[] = _("명상이나 해야지...");
static const u8 sFrontierTrainerText124Before[] = _("포켓몬의 힘을 보여줄게!");
static const u8 sFrontierTrainerText124PlayerLost[] = _("지금 승부 꽤 좋았어!");
static const u8 sFrontierTrainerText124PlayerWon[] = _("근성이 없네...");
static const u8 sFrontierTrainerText125Before[] = _("슬기로움을 갖추고 있다면\n지금 멈추는 게 현명해");
static const u8 sFrontierTrainerText125PlayerLost[] = _("슬기롭지 못했구나");
static const u8 sFrontierTrainerText125PlayerWon[] = _("어라 왜 진 거지?");
static const u8 sFrontierTrainerText126Before[] = _("헤롱헤롱 한 방이면 충분해!");
static const u8 sFrontierTrainerText126PlayerLost[] = _("네 포켓몬\n잘 갖고 놀았어");
static const u8 sFrontierTrainerText126PlayerWon[] = _("헤롱헤롱한 건 나...?");
static const u8 sFrontierTrainerText127Before[] = _("성의를 다해서 상대해줄게!");
static const u8 sFrontierTrainerText127PlayerLost[] = _("사람이 성의를 보이는데\n그게 다야?");
static const u8 sFrontierTrainerText127PlayerWon[] = _("성의를 다해도\n슬픈 건 슬픈 거야");
static const u8 sFrontierTrainerText128Before[] = _("승부 시작!");
static const u8 sFrontierTrainerText128PlayerLost[] = _("나의 승리!");
static const u8 sFrontierTrainerText128PlayerWon[] = _("졌어 분해...");
static const u8 sFrontierTrainerText129Before[] = _("내 애교부리기를 받아랏!");
static const u8 sFrontierTrainerText129PlayerLost[] = _("하하하! 화났어?");
static const u8 sFrontierTrainerText129PlayerWon[] = _("말도 안 돼...\n내가 지다니...");
static const u8 sFrontierTrainerText130Before[] = _("내가 꿀꺽 삼켜줄게");
static const u8 sFrontierTrainerText130PlayerLost[] = _("잘 먹었습니다");
static const u8 sFrontierTrainerText130PlayerWon[] = _("꿀꺽 삼켜졌어");
static const u8 sFrontierTrainerText131Before[] = _("계속 포켓몬을\n키우미집에 맡겼어");
static const u8 sFrontierTrainerText131PlayerLost[] = _("내 포켓몬은 역시 강해!");
static const u8 sFrontierTrainerText131PlayerWon[] = _("역시 직접 키워야 하나...?");
static const u8 sFrontierTrainerText132Before[] = _("이번 승리는 내가 가져갈게!");
static const u8 sFrontierTrainerText132PlayerLost[] = _("불쌍하게 됐네\n그래도 너 잘 싸웠어");
static const u8 sFrontierTrainerText132PlayerWon[] = _("졌지만 완벽한 기분이야!\n정말 고마워");
static const u8 sFrontierTrainerText133Before[] = _("저에게 희망사항 있나요?");
static const u8 sFrontierTrainerText133PlayerLost[] = _("눈에서 잔비가 톡톡?");
static const u8 sFrontierTrainerText133PlayerWon[] = _("날 이기지 말아줘요!");
static const u8 sFrontierTrainerText134Before[] = _("싫은소리 해줄까?");
static const u8 sFrontierTrainerText134PlayerLost[] = _("내 싫은소리 작전은 최고");
static const u8 sFrontierTrainerText134PlayerWon[] = _("네 귀는 방음이야?");
static const u8 sFrontierTrainerText135Before[] = _("구멍파기 승부닷!");
static const u8 sFrontierTrainerText135PlayerLost[] = _("네 마음에 구멍파기");
static const u8 sFrontierTrainerText135PlayerWon[] = _("마음이 구멍파기 당했어...");
static const u8 sFrontierTrainerText136Before[] = _("쳐봐! 난 두꺼운지방이라고");
static const u8 sFrontierTrainerText136PlayerLost[] = _("쳐봤자 배북이 될 뿐");
static const u8 sFrontierTrainerText136PlayerWon[] = _("흐어억 명치 맞았어...");
static const u8 sFrontierTrainerText137Before[] = _("내 최면술을 받아 봐!");
static const u8 sFrontierTrainerText137PlayerLost[] = _("봤지? 최면술!");
static const u8 sFrontierTrainerText137PlayerWon[] = _("내 최면술 작전이 안 먹히다니...");
static const u8 sFrontierTrainerText138Before[] = _("한판 붙어보자!");
static const u8 sFrontierTrainerText138PlayerLost[] = _("이제 나가");
static const u8 sFrontierTrainerText138PlayerWon[] = _("뭐야 너 나 알아?");
static const u8 sFrontierTrainerText139Before[] = _("노공룡에게도 달콤한향기가 있을걸");
static const u8 sFrontierTrainerText139PlayerLost[] = _("소곤룡 같네 하하하!");
static const u8 sFrontierTrainerText139PlayerWon[] = _("폭음룡처럼 울 거야");
static const u8 sFrontierTrainerText140Before[] = _("너로 정했다 이거야!");
static const u8 sFrontierTrainerText140PlayerLost[] = _("내가 이겼다 이거야!");
static const u8 sFrontierTrainerText140PlayerWon[] = _("네가 이겼다 이거야!");
static const u8 sFrontierTrainerText141Before[] = _("쉽게 이길 생각 하지 마!");
static const u8 sFrontierTrainerText141PlayerLost[] = _("나 실력 좋지?");
static const u8 sFrontierTrainerText141PlayerWon[] = _("다음엔 꼭 이길 거야");
static const u8 sFrontierTrainerText142Before[] = _("배틀해서 미안해요!");
static const u8 sFrontierTrainerText142PlayerLost[] = _("이겨서 미안해요!");
static const u8 sFrontierTrainerText142PlayerWon[] = _("미안해요 제발 봐주세요!");
static const u8 sFrontierTrainerText143Before[] = _("넌 이기긴 틀렸어!");
static const u8 sFrontierTrainerText143PlayerLost[] = _("하늘의은총은 내게 있어!");
static const u8 sFrontierTrainerText143PlayerWon[] = _("좋은 승부였어");
static const u8 sFrontierTrainerText144Before[] = _("크아앙!!! 배틀 준비!!");
static const u8 sFrontierTrainerText144PlayerLost[] = _("크아앙!!! 다음 배틀!!");
static const u8 sFrontierTrainerText144PlayerWon[] = _("흐아앙...");
static const u8 sFrontierTrainerText145Before[] = _("난 네 비밀을 알아");
static const u8 sFrontierTrainerText145PlayerLost[] = _("이겼으니까 알려줄게\n거짓말이었어");
static const u8 sFrontierTrainerText145PlayerWon[] = _("졌으니까 비밀로 할게");
static const u8 sFrontierTrainerText146Before[] = _("네 배틀 센스는\n훌쩍훌쩍 눈물이 나");
static const u8 sFrontierTrainerText146PlayerLost[] = _("내 배틀 센스는 멋져\n그렇지?");
static const u8 sFrontierTrainerText146PlayerWon[] = _("오늘 내 배틀 센스는\n마이너스...");
static const u8 sFrontierTrainerText147Before[] = _("내 실력을 보여주지!");
static const u8 sFrontierTrainerText147PlayerLost[] = _("이 순간을 카메라에 담고 싶다");
static const u8 sFrontierTrainerText147PlayerWon[] = _("카메라 치워...");
static const u8 sFrontierTrainerText148Before[] = _("자 흉내내기 간다!");
static const u8 sFrontierTrainerText148PlayerLost[] = _("승리한 켄타로스 흉내내기!");
static const u8 sFrontierTrainerText148PlayerWon[] = _("패배한 밀탱크 흉내내기...");
static const u8 sFrontierTrainerText149Before[] = _("뱀눈초리 같은 눈으로\n마비시켜 주지!");
static const u8 sFrontierTrainerText149PlayerLost[] = _("그렇게 째려보기 없기!");
static const u8 sFrontierTrainerText149PlayerWon[] = _("겁나는얼굴만으론\n부족했나 봐...");
static const u8 sFrontierTrainerText150Before[] = _("학교 끝났어!\n놀 시간이야!");
static const u8 sFrontierTrainerText150PlayerLost[] = _("내 남자친구도\n학교에서 배웠대");
static const u8 sFrontierTrainerText150PlayerWon[] = _("다음 주엔 일해야 해...");
static const u8 sFrontierTrainerText151Before[] = _("학교 끝! 놀자!");
static const u8 sFrontierTrainerText151PlayerLost[] = _("내 남자친구는\n만화를 좋아해");
static const u8 sFrontierTrainerText151PlayerWon[] = _("또 학교를 가야 한다니...");
static const u8 sFrontierTrainerText152Before[] = _("드래곤포켓몬은 무적이야!");
static const u8 sFrontierTrainerText152PlayerLost[] = _("네 실력도 나쁘진 않았어\n내 실력이 더 좋았을 뿐");
static const u8 sFrontierTrainerText152PlayerWon[] = _("이제 만족했어?");
static const u8 sFrontierTrainerText153Before[] = _("내 순수한힘은\n마치 기계 같지!");
static const u8 sFrontierTrainerText153PlayerLost[] = _("마하펀치로 깨트리기!");
static const u8 sFrontierTrainerText153PlayerWon[] = _("으악 이럴 수가!!");
static const u8 sFrontierTrainerText154Before[] = _("내 패션 센스\n뚜벅쵸 같지 않아?");
static const u8 sFrontierTrainerText154PlayerLost[] = _("우리 집 패션은\n라플레시아 같아!");
static const u8 sFrontierTrainerText154PlayerWon[] = _("네 패션 센스\n진지하게 냄새꼬 같아");
static const u8 sFrontierTrainerText155Before[] = _("좋아! 그래그래!!");
static const u8 sFrontierTrainerText155PlayerLost[] = _("와하하하! 와하하하!!");
static const u8 sFrontierTrainerText155PlayerWon[] = _("미안... 내 잘못이야");
static const u8 sFrontierTrainerText156Before[] = _("내 열풍 느껴져?");
static const u8 sFrontierTrainerText156PlayerLost[] = _("그래! 나 불타오르고 있어!");
static const u8 sFrontierTrainerText156PlayerWon[] = _("널 위해 불탔는데...");
static const u8 sFrontierTrainerText157Before[] = _("격투와 기합!\n그게 나야!");
static const u8 sFrontierTrainerText157PlayerLost[] = _("실은 더 귀여운 포켓몬이\n갖고 싶어");
static const u8 sFrontierTrainerText157PlayerWon[] = _("네 포켓몬 꽤 귀엽네");
static const u8 sFrontierTrainerText158Before[] = _("배틀은 기합으로 정해지지!");
static const u8 sFrontierTrainerText158PlayerLost[] = _("못 받아들이겠어?");
static const u8 sFrontierTrainerText158PlayerWon[] = _("난 내 길을 갈 거야");
static const u8 sFrontierTrainerText159Before[] = _("네 포켓몬 도감\n정말 굉장한데?");
static const u8 sFrontierTrainerText159PlayerLost[] = _("우와! 네 도감 갖고 싶은데!");
static const u8 sFrontierTrainerText159PlayerWon[] = _("전국도감이 있었으면\n이길 수 있었을까");
static const u8 sFrontierTrainerText160Before[] = _("여기가 내가 있을 곳이야!\n이야호!");
static const u8 sFrontierTrainerText160PlayerLost[] = _("난 지금이 제일 신나!");
static const u8 sFrontierTrainerText160PlayerWon[] = _("아무도 내 행복에\n짓밟기를 쓸 순 없어!");
static const u8 sFrontierTrainerText161Before[] = _("곧 겨울이 오겠네");
static const u8 sFrontierTrainerText161PlayerLost[] = _("겨울이 오니까 용돈 좀");
static const u8 sFrontierTrainerText161PlayerWon[] = _("겨울이 와서 용돈은 못 줘");
static const u8 sFrontierTrainerText162Before[] = _("아름답게 배틀할 수 있어?");
static const u8 sFrontierTrainerText162PlayerLost[] = _("너 배틀 방식은 좀 추해");
static const u8 sFrontierTrainerText162PlayerWon[] = _("너한테 아름다움은 뭐야?");
static const u8 sFrontierTrainerText163Before[] = _("지금 목말라 죽겠어...");
static const u8 sFrontierTrainerText163PlayerLost[] = _("차가운 음료가 필요해");
static const u8 sFrontierTrainerText163PlayerWon[] = _("이 패배는 마시기 어렵네");
static const u8 sFrontierTrainerText164Before[] = _("공부 많이 하는 척은 잘해");
static const u8 sFrontierTrainerText164PlayerLost[] = _("용돈 때문에 엄마를 속였어");
static const u8 sFrontierTrainerText164PlayerWon[] = _("공부 더 하긴 싫어...");
static const u8 sFrontierTrainerText165Before[] = _("난 만화도 게임도 좋아");
static const u8 sFrontierTrainerText165PlayerLost[] = _("음악 아이돌도 좋아해");
static const u8 sFrontierTrainerText165PlayerWon[] = _("그래도 공부는 더 해야 해");
static const u8 sFrontierTrainerText166Before[] = _("걱정이 많아서 잠이 안 와");
static const u8 sFrontierTrainerText166PlayerLost[] = _("명상 덕분에 이겼어");
static const u8 sFrontierTrainerText166PlayerWon[] = _("불면이 더 심해지겠네...");
static const u8 sFrontierTrainerText167Before[] = _("아로마테라피 목욕을 믿어");
static const u8 sFrontierTrainerText167PlayerLost[] = _("건강한 클리어바디가 좋아");
static const u8 sFrontierTrainerText167PlayerWon[] = _("아로마테라피가\n좀 싸면 좋을 텐데");
static const u8 sFrontierTrainerText168Before[] = _("내 취미가 궁금해?");
static const u8 sFrontierTrainerText168PlayerLost[] = _("물놀이라면 뭐든 좋아");
static const u8 sFrontierTrainerText168PlayerWon[] = _("흙놀이는 뭐든 싫어...");
static const u8 sFrontierTrainerText169Before[] = _("내가 너무 약해서 슬퍼");
static const u8 sFrontierTrainerText169PlayerLost[] = _("네가 너무 강한 건 아니야");
static const u8 sFrontierTrainerText169PlayerWon[] = _("어이 내가 뭘 했다고?");
static const u8 sFrontierTrainerText170Before[] = _("의욕이 올라왔어!");
static const u8 sFrontierTrainerText170PlayerLost[] = _("의욕으로 널 밀어냈어");
static const u8 sFrontierTrainerText170PlayerWon[] = _("어떻게 진 건지 모르겠어");
static const u8 sFrontierTrainerText171Before[] = _("심심해... 나를 위해 춤춰줘");
static const u8 sFrontierTrainerText171PlayerLost[] = _("더 심심해졌잖아");
static const u8 sFrontierTrainerText171PlayerWon[] = _("화풀이는 다른 데 가서 해");
static const u8 sFrontierTrainerText172Before[] = _("내 근사함을 배틀로 기념하자");
static const u8 sFrontierTrainerText172PlayerLost[] = _("칭찬하기엔 너무 약했어");
static const u8 sFrontierTrainerText172PlayerWon[] = _("네 배틀 센스 좀 웃기네");
static const u8 sFrontierTrainerText173Before[] = _("멋진 배틀을 해 보자");
static const u8 sFrontierTrainerText173PlayerLost[] = _("멋지게 이겼어");
static const u8 sFrontierTrainerText173PlayerWon[] = _("안녕? 난 그냥 애야");
static const u8 sFrontierTrainerText174Before[] = _("내 비밀의힘은 압도적이야");
static const u8 sFrontierTrainerText174PlayerLost[] = _("봤어? 방금 그거!");
static const u8 sFrontierTrainerText174PlayerWon[] = _("연막 쓰고 도망칠게...");
static const u8 sFrontierTrainerText175Before[] = _("모든 상대를 풀베기로 베겠어");
static const u8 sFrontierTrainerText175PlayerLost[] = _("져도 원념 품지는 마");
static const u8 sFrontierTrainerText175PlayerWon[] = _("그 겁나는얼굴 좀 치워줘...");
static const u8 sFrontierTrainerText176Before[] = _("내 열차를 기다리는 중이야");
static const u8 sFrontierTrainerText176PlayerLost[] = _("내 열차 아직 안 왔어...");
static const u8 sFrontierTrainerText176PlayerWon[] = _("왔다 내 열차! 잘 있어!");
static const u8 sFrontierTrainerText177Before[] = _("지난주에 열풍이 불었지");
static const u8 sFrontierTrainerText177PlayerLost[] = _("열풍은 못 버티겠어");
static const u8 sFrontierTrainerText177PlayerWon[] = _("싸라기눈도 같이 왔던가?");
static const u8 sFrontierTrainerText178Before[] = _("난 물에서 노는 게 좋아");
static const u8 sFrontierTrainerText178PlayerLost[] = _("밖으로 나가긴 싫어");
static const u8 sFrontierTrainerText178PlayerWon[] = _("물속에선 별로였네");
static const u8 sFrontierTrainerText179Before[] = _("이 유치원 잡지\n내용이 너무 세다");
static const u8 sFrontierTrainerText179PlayerLost[] = _("선생님 괴롭히기 있어?");
static const u8 sFrontierTrainerText179PlayerWon[] = _("급식이 맛있으면 즐겁지?");
static const u8 sFrontierTrainerText180Before[] = _("곧 벌레 이벤트가 열린대");
static const u8 sFrontierTrainerText180PlayerLost[] = _("벌레 패션쇼였어!");
static const u8 sFrontierTrainerText180PlayerWon[] = _("벌레 포켓몬 싫어해?");
static const u8 sFrontierTrainerText181Before[] = _("무적의 벌레타입\n트레이너 등장!");
static const u8 sFrontierTrainerText181PlayerLost[] = _("무적의 벌레타입 트레이너!\n그게 바로 나!");
static const u8 sFrontierTrainerText181PlayerWon[] = _("내가 얼마나 빨리\n도망가는지 봐봐!");
static const u8 sFrontierTrainerText182Before[] = _("낚시 학교에 다녔어");
static const u8 sFrontierTrainerText182PlayerLost[] = _("낚시 명예의 전당급이야");
static const u8 sFrontierTrainerText182PlayerWon[] = _("다시 돌아가고 싶어...");
static const u8 sFrontierTrainerText183Before[] = _("완전 멋진 크로스촙 보여줘");
static const u8 sFrontierTrainerText183PlayerLost[] = _("넌 크로스촙 하기엔 약해");
static const u8 sFrontierTrainerText183PlayerWon[] = _("이거 실수였나?");
static const u8 sFrontierTrainerText184Before[] = _("일하다 보니 건강해졌어");
static const u8 sFrontierTrainerText184PlayerLost[] = _("어때? 나 건강하지!");
static const u8 sFrontierTrainerText184PlayerWon[] = _("너 나보다 더 건강하네...");
static const u8 sFrontierTrainerText185Before[] = _("어이! 잘 봐!!");
static const u8 sFrontierTrainerText185PlayerLost[] = _("잘 가 고마워! 웃겼어");
static const u8 sFrontierTrainerText185PlayerWon[] = _("패배한 내 모습을 보지 마!!");
static const u8 sFrontierTrainerText186Before[] = _("내 최면술 볼래?");
static const u8 sFrontierTrainerText186PlayerLost[] = _("어린 트레이너의\n마구할퀴기와 괴력!");
static const u8 sFrontierTrainerText186PlayerWon[] = _("쳇... 내가 너무 약했나...");
static const u8 sFrontierTrainerText187Before[] = _("이 배틀은 엄마를 위한 거야");
static const u8 sFrontierTrainerText187PlayerLost[] = _("엄마가 기뻐하시겠지");
static const u8 sFrontierTrainerText187PlayerWon[] = _("엄마 보고 싶어!");
static const u8 sFrontierTrainerText188Before[] = _("우리 음악은 밤새 울릴 거야");
static const u8 sFrontierTrainerText188PlayerLost[] = _("밤이 되면 내가 제일 잘해");
static const u8 sFrontierTrainerText188PlayerWon[] = _("아침햇살 뜰 때까지 파티야!");
static const u8 sFrontierTrainerText189Before[] = _("나 유행 좀 타지?");
static const u8 sFrontierTrainerText189PlayerLost[] = _("지금 완전 힙하잖아!");
static const u8 sFrontierTrainerText189PlayerWon[] = _("난 늘 유행이야\n정말 고마워");
static const u8 sFrontierTrainerText190Before[] = _("비행타입의 비기를 보여줄게");
static const u8 sFrontierTrainerText190PlayerLost[] = _("비행타입의 승리야!");
static const u8 sFrontierTrainerText190PlayerWon[] = _("졌으니 공중날기로 날아갈래");
static const u8 sFrontierTrainerText191Before[] = _("꿈 때문에 기분이 이상해");
static const u8 sFrontierTrainerText191PlayerLost[] = _("네 겁나는얼굴이\n내 꿈에 나왔어");
static const u8 sFrontierTrainerText191PlayerWon[] = _("믿기 힘든 꿈이었어\n정말 이상했지");
static const u8 sFrontierTrainerText192Before[] = _("어제처럼 춤춰보자!");
static const u8 sFrontierTrainerText192PlayerLost[] = _("내 춤 어때? 마음에 들어?");
static const u8 sFrontierTrainerText192PlayerWon[] = _("내 춤을 몰라주네");
static const u8 sFrontierTrainerText193Before[] = _("내 여자친구가\n천사의키스를 해줬어");
static const u8 sFrontierTrainerText193PlayerLost[] = _("여자친구는 내 보물이야");
static const u8 sFrontierTrainerText193PlayerWon[] = _("넌 이겨도\n천사의키스는 못 받을걸");
static const u8 sFrontierTrainerText194Before[] = _("슬기로움만으론 못 이겨");
static const u8 sFrontierTrainerText194PlayerLost[] = _("난 별로 안 슬기로운데 이겼어");
static const u8 sFrontierTrainerText194PlayerWon[] = _("날 속이다니!");
static const u8 sFrontierTrainerText195Before[] = _("충전! 충전!!");
static const u8 sFrontierTrainerText195PlayerLost[] = _("벌써 항복이야?");
static const u8 sFrontierTrainerText195PlayerWon[] = _("방전! 방전!!");
static const u8 sFrontierTrainerText196Before[] = _("받아라! 이글이글 트릭!");
static const u8 sFrontierTrainerText196PlayerLost[] = _("내 이글이글 트릭에 놀랐어?");
static const u8 sFrontierTrainerText196PlayerWon[] = _("내 트릭에 안 넘어가다니");
static const u8 sFrontierTrainerText197Before[] = _("불타는 미식가가 바로 나야!");
static const u8 sFrontierTrainerText197PlayerLost[] = _("맛있는 미식가의 승리야!");
static const u8 sFrontierTrainerText197PlayerWon[] = _("이런 재앙이 따로 없네!");
static const u8 sFrontierTrainerText198Before[] = _("빨리 시작하고 싶어!");
static const u8 sFrontierTrainerText198PlayerLost[] = _("시작했으니 이만 안녕!");
static const u8 sFrontierTrainerText198PlayerWon[] = _("이제 움직여야겠어");
static const u8 sFrontierTrainerText199Before[] = _("나한테 프레젠트 줄 거야?");
static const u8 sFrontierTrainerText199PlayerLost[] = _("음... 꽤 맛있는 프레젠트인걸...");
static const u8 sFrontierTrainerText199PlayerWon[] = _("매정한 녀석");
static const u8 sFrontierTrainerText200Before[] = _("내가 원하는 건 조가비갑옷이야");
static const u8 sFrontierTrainerText200PlayerLost[] = _("엄마 아빠도 내\n패배는 용납 안 하셔");
static const u8 sFrontierTrainerText200PlayerWon[] = _("제발! 조가비갑옷이 필요해!");
static const u8 sFrontierTrainerText201Before[] = _("지면 학교 공부할 거야");
static const u8 sFrontierTrainerText201PlayerLost[] = _("내가 공부? 그럴 리 없지");
static const u8 sFrontierTrainerText201PlayerWon[] = _("고맙지만 난 잘래");
static const u8 sFrontierTrainerText202Before[] = _("이런 배틀도 괜찮지?");
static const u8 sFrontierTrainerText202PlayerLost[] = _("얼다바람에 파도타기까지!");
static const u8 sFrontierTrainerText202PlayerWon[] = _("스톤샤워는 어때?");
static const u8 sFrontierTrainerText203Before[] = _("포켓몬 패션 콘테스트는\n꽤 멋져");
static const u8 sFrontierTrainerText203PlayerLost[] = _("난 유행하는 패션이 정말 좋아");
static const u8 sFrontierTrainerText203PlayerWon[] = _("넌 패션 감각이 완전 부족해");
static const u8 sFrontierTrainerText204Before[] = _("풀타입 포켓몬이 더 필요해");
static const u8 sFrontierTrainerText204PlayerLost[] = _("풀포켓몬 교환해줘 제발");
static const u8 sFrontierTrainerText204PlayerWon[] = _("풀타입 포켓몬이\n아직 모자라");
static const u8 sFrontierTrainerText205Before[] = _("뿌리박기는 내 특기!");
static const u8 sFrontierTrainerText205PlayerLost[] = _("아무도 날 움직일 순 없어!");
static const u8 sFrontierTrainerText205PlayerWon[] = _("뿌리째 뽑혀 버렸다...");
static const u8 sFrontierTrainerText206Before[] = _("이 배틀을 즐기고 싶어");
static const u8 sFrontierTrainerText206PlayerLost[] = _("너무 쉬웠잖아!");
static const u8 sFrontierTrainerText206PlayerWon[] = _("이런 걸 어떻게 즐기란 거야");
static const u8 sFrontierTrainerText207Before[] = _("일요일엔 쾌청이길 빌어");
static const u8 sFrontierTrainerText207PlayerLost[] = _("일요일이 영원히 안 오네...");
static const u8 sFrontierTrainerText207PlayerWon[] = _("예보에서 싸라기눈이래");
static const u8 sFrontierTrainerText208Before[] = _("내 회오리에 휘말려랏!");
static const u8 sFrontierTrainerText208PlayerLost[] = _("상대는 이렇게 가라앉히는 거야");
static const u8 sFrontierTrainerText208PlayerWon[] = _("넌 태풍이었구나!");
static const u8 sFrontierTrainerText209Before[] = _("넌 몸통박치기가 딱이야!");
static const u8 sFrontierTrainerText209PlayerLost[] = _("도망치지 마 패배자!");
static const u8 sFrontierTrainerText209PlayerWon[] = _("카운터를 맞을 줄은 몰랐어");
static const u8 sFrontierTrainerText210Before[] = _("내 왕자님 될 사람은 어디에!");
static const u8 sFrontierTrainerText210PlayerLost[] = _("고마워!\n이런 자극도 나쁘지 않네");
static const u8 sFrontierTrainerText210PlayerWon[] = _("난 공주님이 아닌가 봐");
static const u8 sFrontierTrainerText211Before[] = _("너 때문에 라라라\n흥얼거리게 돼!");
static const u8 sFrontierTrainerText211PlayerLost[] = _("라라라! 난 안 져!");
static const u8 sFrontierTrainerText211PlayerWon[] = _("라라라... 어?");
static const u8 sFrontierTrainerText212Before[] = _("넌 내 힘의 피뢰침이야");
static const u8 sFrontierTrainerText212PlayerLost[] = _("피뢰침이 성능이 안 좋은걸");
static const u8 sFrontierTrainerText212PlayerWon[] = _("피뢰침이 이기면 어떡해");
static const u8 sFrontierTrainerText213Before[] = _("난 때를 참고 기다릴 거야");
static const u8 sFrontierTrainerText213PlayerLost[] = _("벌써 끝난 거야?");
static const u8 sFrontierTrainerText213PlayerWon[] = _("실수의 대가는 비싼 법이구나...");
static const u8 sFrontierTrainerText214Before[] = _("귀여운 포켓몬 보여줘");
static const u8 sFrontierTrainerText214PlayerLost[] = _("킥킥... 정말 고마워");
static const u8 sFrontierTrainerText214PlayerWon[] = _("쳇... 네 포켓몬\n그렇게 나이스하진 않네");
static const u8 sFrontierTrainerText215Before[] = _("좋은 선물을 갖고 싶어...");
static const u8 sFrontierTrainerText215PlayerLost[] = _("제발 포켓몬 게임 사줘");
static const u8 sFrontierTrainerText215PlayerWon[] = _("편지는 좀 그렇지");
static const u8 sFrontierTrainerText216Before[] = _("네 전력을 보여줘");
static const u8 sFrontierTrainerText216PlayerLost[] = _("그건 전력이 아니었어!");
static const u8 sFrontierTrainerText216PlayerWon[] = _("재미없어... 너무 강하잖아");
static const u8 sFrontierTrainerText217Before[] = _("일 때문에 일찍 일어나게 됐어");
static const u8 sFrontierTrainerText217PlayerLost[] = _("일만 하고 놀지는 못해...");
static const u8 sFrontierTrainerText217PlayerWon[] = _("버티기밖에 할 수 없어...");
static const u8 sFrontierTrainerText218Before[] = _("와아! 강한 트레이너!");
static const u8 sFrontierTrainerText218PlayerLost[] = _("아아! 흐느적흐느적 트레이너!");
static const u8 sFrontierTrainerText218PlayerWon[] = _("멋져! 천재 트레이너!");
static const u8 sFrontierTrainerText219Before[] = _("꼴깍몬 모양 과자 좀 먹을래?");
static const u8 sFrontierTrainerText219PlayerLost[] = _("포켓몬 미식가들만 알고 있는\n비밀의 아이템이야");
static const u8 sFrontierTrainerText219PlayerWon[] = _("맛있지! 상쾌하기도 해!");
static const u8 sFrontierTrainerText220Before[] = _("난 다른 트레이너들보다 뛰어나");
static const u8 sFrontierTrainerText220PlayerLost[] = _("기뻐서 점프킥 해버렸어");
static const u8 sFrontierTrainerText220PlayerWon[] = _("집에 돌아갈래...");
static const u8 sFrontierTrainerText221Before[] = _("아직 한 번도 안 졌어!");
static const u8 sFrontierTrainerText221PlayerLost[] = _("슬픈 표정도 잘 어울리네");
static const u8 sFrontierTrainerText221PlayerWon[] = _("믿을 수 없어...");
static const u8 sFrontierTrainerText222Before[] = _("최고의 트레이너가 바로 나야!");
static const u8 sFrontierTrainerText222PlayerLost[] = _("최고 랭크는 내 거야!");
static const u8 sFrontierTrainerText222PlayerWon[] = _("내 역린을 건드리다니!");
static const u8 sFrontierTrainerText223Before[] = _("내 구슬던지기로\n힘껏치기 해주지!");
static const u8 sFrontierTrainerText223PlayerLost[] = _("이 정도도 예상 못 했어?");
static const u8 sFrontierTrainerText223PlayerWon[] = _("도무지 이해가 안 돼...");
static const u8 sFrontierTrainerText224Before[] = _("난 이 세상의 보물이야");
static const u8 sFrontierTrainerText224PlayerLost[] = _("내 세계는 신비로 가득해");
static const u8 sFrontierTrainerText224PlayerWon[] = _("왜 이렇게 형편없는 거지?");
static const u8 sFrontierTrainerText225Before[] = _("오... 겁나는얼굴의 트레이너네");
static const u8 sFrontierTrainerText225PlayerLost[] = _("아하하! 겉보기에만 무섭잖아!");
static const u8 sFrontierTrainerText225PlayerWon[] = _("꺄악! 정말 무섭잖아!");
static const u8 sFrontierTrainerText226Before[] = _("근성 있는 모습을 보여 줄게!");
static const u8 sFrontierTrainerText226PlayerLost[] = _("뭐든지 근성이야!");
static const u8 sFrontierTrainerText226PlayerWon[] = _("말도 안 돼... 자폭 모드!");
static const u8 sFrontierTrainerText227Before[] = _("진짜 대단한 배틀을 찾고 있어");
static const u8 sFrontierTrainerText227PlayerLost[] = _("더 나은 배틀이 필요해...");
static const u8 sFrontierTrainerText227PlayerWon[] = _("이건 좀 버겁네");
static const u8 sFrontierTrainerText228Before[] = _("요! 가자!!");
static const u8 sFrontierTrainerText228PlayerLost[] = _("요! 나 이겼어 요!");
static const u8 sFrontierTrainerText228PlayerWon[] = _("요! 나 졌어 요...");
static const u8 sFrontierTrainerText229Before[] = _("내 포켓몬은 힘이 너무 넘쳐");
static const u8 sFrontierTrainerText229PlayerLost[] = _("지금 더 강해졌어!");
static const u8 sFrontierTrainerText229PlayerWon[] = _("조금만 살살 부탁해...");
static const u8 sFrontierTrainerText230Before[] = _("그럼 이 포켓몬은 통할까?");
static const u8 sFrontierTrainerText230PlayerLost[] = _("너무 강했던 것 같네");
static const u8 sFrontierTrainerText230PlayerWon[] = _("상성이 안 맞았던 것 같아");
static const u8 sFrontierTrainerText231Before[] = _("내 포켓몬은 전부 날 좋아해");
static const u8 sFrontierTrainerText231PlayerLost[] = _("행복한 헤롱헤롱바디 포켓몬!");
static const u8 sFrontierTrainerText231PlayerWon[] = _("귀여운 포켓몬한테 너무하네");
static const u8 sFrontierTrainerText232Before[] = _("네 포켓몬을 보고 싶어");
static const u8 sFrontierTrainerText232PlayerLost[] = _("뭐야 다들 시시하네? 아하하");
static const u8 sFrontierTrainerText232PlayerWon[] = _("네 포켓몬은 좀 다르네");
static const u8 sFrontierTrainerText233Before[] = _("난 어리고 강해!");
static const u8 sFrontierTrainerText233PlayerLost[] = _("어때? 나 강하지?");
static const u8 sFrontierTrainerText233PlayerWon[] = _("이번 승부는\n완전 안 풀렸어");
static const u8 sFrontierTrainerText234Before[] = _("드래곤포켓몬이\n내 마음속 1등이야");
static const u8 sFrontierTrainerText234PlayerLost[] = _("드래곤포켓몬의 승리를 만끽해야지");
static const u8 sFrontierTrainerText234PlayerWon[] = _("드래곤포켓몬이 지면 안 되는데!");
static const u8 sFrontierTrainerText235Before[] = _("네 울부짖기를 들려줘!");
static const u8 sFrontierTrainerText235PlayerLost[] = _("크아앙! 승리!!");
static const u8 sFrontierTrainerText235PlayerWon[] = _("크아앙! 왜!?");
static const u8 sFrontierTrainerText236Before[] = _("난 드래곤포켓몬하고만 살아");
static const u8 sFrontierTrainerText236PlayerLost[] = _("내 삶의 방식은 완벽해");
static const u8 sFrontierTrainerText236PlayerWon[] = _("내 삶의 방식이 무너졌어");
static const u8 sFrontierTrainerText237Before[] = _("이 승부는 빠르게 끝날 거야");
static const u8 sFrontierTrainerText237PlayerLost[] = _("별로 오래 걸리지도 않았네");
static const u8 sFrontierTrainerText237PlayerWon[] = _("이렇게 빨리 질 수는 없어!");
static const u8 sFrontierTrainerText238Before[] = _("난 단단한 포켓몬이 제일 좋아");
static const u8 sFrontierTrainerText238PlayerLost[] = _("강인함이 답이야");
static const u8 sFrontierTrainerText238PlayerWon[] = _("봉제인형 컬렉션도 있어");
static const u8 sFrontierTrainerText239Before[] = _("약한 트레이너는 사절이야");
static const u8 sFrontierTrainerText239PlayerLost[] = _("흥! 또 약한 트레이너인가...");
static const u8 sFrontierTrainerText239PlayerWon[] = _("너 약한 구석이 없네");
static const u8 sFrontierTrainerText240Before[] = _("또 다른 배틀이라고?");
static const u8 sFrontierTrainerText240PlayerLost[] = _("이기긴 했는데 피곤해...");
static const u8 sFrontierTrainerText240PlayerWon[] = _("좋아 드디어 끝났다...");
static const u8 sFrontierTrainerText241Before[] = _("배틀걸! 그건 바로 나!");
static const u8 sFrontierTrainerText241PlayerLost[] = _("배틀걸! 굉장하지 않아?");
static const u8 sFrontierTrainerText241PlayerWon[] = _("배틀걸! 싫어?");
static const u8 sFrontierTrainerText242Before[] = _("내 무적의 공격을 받아라!");
static const u8 sFrontierTrainerText242PlayerLost[] = _("넌 배워야 할 게 많아");
static const u8 sFrontierTrainerText242PlayerWon[] = _("무적의 공격도 여기까진가");
static const u8 sFrontierTrainerText243Before[] = _("만나서 반가워\n어린 트레이너!");
static const u8 sFrontierTrainerText243PlayerLost[] = _("와하하하! 포기해!");
static const u8 sFrontierTrainerText243PlayerWon[] = _("꼬마 너\n강한 트레이너구나");
static const u8 sFrontierTrainerText244Before[] = _("나 얕보면 안 돼\n알겠지?");
static const u8 sFrontierTrainerText244PlayerLost[] = _("공격하기 너무 쉽다");
static const u8 sFrontierTrainerText244PlayerWon[] = _("그럼 그럼... 난 항복...");
static const u8 sFrontierTrainerText245Before[] = _("난 늙은 게 아니라 숙련된 거다!");
static const u8 sFrontierTrainerText245PlayerLost[] = _("숙련자라고 불러다오!");
static const u8 sFrontierTrainerText245PlayerWon[] = _("충격이야!\n난 이만 가마!");
static const u8 sFrontierTrainerText246Before[] = _("넌 날 이길 수 없어!");
static const u8 sFrontierTrainerText246PlayerLost[] = _("하하! 내가 널 이겼어!");
static const u8 sFrontierTrainerText246PlayerWon[] = _("마구찌르기 당해서\n풀이 죽었어...");
static const u8 sFrontierTrainerText247Before[] = _("그럼 시작해 볼까?");
static const u8 sFrontierTrainerText247PlayerLost[] = _("뭐야 벌써 끝났어?");
static const u8 sFrontierTrainerText247PlayerWon[] = _("그래... 내가 너무 약했네");
static const u8 sFrontierTrainerText248Before[] = _("네 얘기 많이 들었어");
static const u8 sFrontierTrainerText248PlayerLost[] = _("내가 잘못 들었나봐");
static const u8 sFrontierTrainerText248PlayerWon[] = _("듣던 말이 맞았네");
static const u8 sFrontierTrainerText249Before[] = _("나는 슈퍼 포켓몬 히어로!");
static const u8 sFrontierTrainerText249PlayerLost[] = _("이 정도면 충분했지?");
static const u8 sFrontierTrainerText249PlayerWon[] = _("히어로를 이기면 안 되지!");
static const u8 sFrontierTrainerText250Before[] = _("쉬운 승부가 되겠네");
static const u8 sFrontierTrainerText250PlayerLost[] = _("정말 쉬웠어");
static const u8 sFrontierTrainerText250PlayerWon[] = _("이제 만족해?");
static const u8 sFrontierTrainerText251Before[] = _("꿰뚫어보기를 쓰니\n내 승리가 보여");
static const u8 sFrontierTrainerText251PlayerLost[] = _("내 꿰뚫어보기는 완벽했어!");
static const u8 sFrontierTrainerText251PlayerWon[] = _("꿰뚫어보기를 꿰뚫어봤니...?");
static const u8 sFrontierTrainerText252Before[] = _("여기서 좋은 일이 생길 거야");
static const u8 sFrontierTrainerText252PlayerLost[] = _("봤지? 환상적이야!");
static const u8 sFrontierTrainerText252PlayerWon[] = _("네게 좋은 일이었구나");
static const u8 sFrontierTrainerText253Before[] = _("트레이너들이 전부 약해빠졌어...");
static const u8 sFrontierTrainerText253PlayerLost[] = _("이 배틀도 하품이 나와");
static const u8 sFrontierTrainerText253PlayerWon[] = _("졸다가 져버렸네");
static const u8 sFrontierTrainerText254Before[] = _("난 그렇게 못된 트레이너가 아냐");
static const u8 sFrontierTrainerText254PlayerLost[] = _("꽤 괜찮은 승부 아니었어?");
static const u8 sFrontierTrainerText254PlayerWon[] = _("네가 못돼서 진 거야...");
static const u8 sFrontierTrainerText255Before[] = _("내가 이겨도 원념 품지 마");
static const u8 sFrontierTrainerText255PlayerLost[] = _("화난 모습 보니 미안하네");
static const u8 sFrontierTrainerText255PlayerWon[] = _("너한테 원념이 생겼어");
static const u8 sFrontierTrainerText256Before[] = _("독가루를 흩뿌려 줄게");
static const u8 sFrontierTrainerText256PlayerLost[] = _("내 작전이 무섭게 먹혔지?");
static const u8 sFrontierTrainerText256PlayerWon[] = _("너도 네 포켓몬도 싫어");
static const u8 sFrontierTrainerText257Before[] = _("무서운 포켓몬을 보고 싶어?");
static const u8 sFrontierTrainerText257PlayerLost[] = _("무서웠지?");
static const u8 sFrontierTrainerText257PlayerWon[] = _("넌 내 포켓몬보다\n더 무섭네");
static const u8 sFrontierTrainerText258Before[] = _("여보세요? 안녕!?");
static const u8 sFrontierTrainerText258PlayerLost[] = _("여보세요 엄마!\n나 이겼어!");
static const u8 sFrontierTrainerText258PlayerWon[] = _("전화가 안 되네...");
static const u8 sFrontierTrainerText259Before[] = _("이제 네 뽐내기는 끝이야");
static const u8 sFrontierTrainerText259PlayerLost[] = _("이젠 뽐내기 못 하겠네?");
static const u8 sFrontierTrainerText259PlayerWon[] = _("내 뽐내기 시간이 끝인가...");
static const u8 sFrontierTrainerText260Before[] = _("나 완전 멋진 거 알아!");
static const u8 sFrontierTrainerText260PlayerLost[] = _("날 존경해도 좋아");
static const u8 sFrontierTrainerText260PlayerWon[] = _("너 멋지다! 진짜야!");
static const u8 sFrontierTrainerText261Before[] = _("이건 높은 수준의\n배틀이 될 거야");
static const u8 sFrontierTrainerText261PlayerLost[] = _("수준 높고 신나는 승부였어");
static const u8 sFrontierTrainerText261PlayerWon[] = _("네 수준이 너무 높았어...");
static const u8 sFrontierTrainerText262Before[] = _("나 아직 그렇게 늙지 않았어");
static const u8 sFrontierTrainerText262PlayerLost[] = _("누가 나보고 늙었대?");
static const u8 sFrontierTrainerText262PlayerWon[] = _("제발... 나 정말 그렇게\n안 늙었단 말이야");
static const u8 sFrontierTrainerText263Before[] = _("조언 몇 개 해줄까?");
static const u8 sFrontierTrainerText263PlayerLost[] = _("다이어트 말고 스포츠를 해");
static const u8 sFrontierTrainerText263PlayerWon[] = _("TV 대신 책을 보라고?");
static const u8 sFrontierTrainerText264Before[] = _("제발 무섭게 만들지 마");
static const u8 sFrontierTrainerText264PlayerLost[] = _("고마워... 이제 기뻐");
static const u8 sFrontierTrainerText264PlayerWon[] = _("실망이야...");
static const u8 sFrontierTrainerText265Before[] = _("잘 들어! 난 언제나 이겨");
static const u8 sFrontierTrainerText265PlayerLost[] = _("내가 천재 아니면 뭐겠어?");
static const u8 sFrontierTrainerText265PlayerWon[] = _("승부에선 졌지만\n슬기로움은 내가 더 높아");
static const u8 sFrontierTrainerText266Before[] = _("스포츠계도 포켓몬을 받아들여야 해");
static const u8 sFrontierTrainerText266PlayerLost[] = _("고마워!\n상쾌한 승리였어");
static const u8 sFrontierTrainerText266PlayerWon[] = _("고마워!\n상쾌한 패배였어");
static const u8 sFrontierTrainerText267Before[] = _("우리 함께 달려볼까?");
static const u8 sFrontierTrainerText267PlayerLost[] = _("근성을 더 보여달라고");
static const u8 sFrontierTrainerText267PlayerWon[] = _("오 이런!");
static const u8 sFrontierTrainerText268Before[] = _("또 트레이너 배틀이야...?");
static const u8 sFrontierTrainerText268PlayerLost[] = _("이거 끝나긴 해?");
static const u8 sFrontierTrainerText268PlayerWon[] = _("드디어 잠자기 좀 하겠네");
static const u8 sFrontierTrainerText269Before[] = _("파도타기 아래로 다이빙!");
static const u8 sFrontierTrainerText269PlayerLost[] = _("야호! 다이빙 받아라!");
static const u8 sFrontierTrainerText269PlayerWon[] = _("가라앉겠어...");
static const u8 sFrontierTrainerText270Before[] = _("미리 유연해지게\n몸 풀고 왔어?");
static const u8 sFrontierTrainerText270PlayerLost[] = _("준비 운동을 더 해야겠는데");
static const u8 sFrontierTrainerText270PlayerWon[] = _("유연해도 소용없었네");
static const u8 sFrontierTrainerText271Before[] = _("공격하는 게 좋아");
static const u8 sFrontierTrainerText271PlayerLost[] = _("킥킥... 넌 끝났어");
static const u8 sFrontierTrainerText271PlayerWon[] = _("공격이 왜 안 통했는지\n모르겠어");
static const u8 sFrontierTrainerText272Before[] = _("소닉붐처럼 등장!");
static const u8 sFrontierTrainerText272PlayerLost[] = _("풀죽게 해서 미안");
static const u8 sFrontierTrainerText272PlayerWon[] = _("초음파 같은 속도로\n퇴장할게");
static const u8 sFrontierTrainerText273Before[] = _("포켓몬 마스터!\n그게 내 꿈이야");
static const u8 sFrontierTrainerText273PlayerLost[] = _("내 꿈은 멀지 않았어!");
static const u8 sFrontierTrainerText273PlayerWon[] = _("꿈이 이뤄지질 않네...");
static const u8 sFrontierTrainerText274Before[] = _("나 귀엽지?");
static const u8 sFrontierTrainerText274PlayerLost[] = _("귀여움만 갖춘 게 아니라고");
static const u8 sFrontierTrainerText274PlayerWon[] = _("헤롱헤롱바디로도\n널 홀리진 못했네?");
static const u8 sFrontierTrainerText275Before[] = _("난 언제나 기뻐 기뻐 기뻐!");
static const u8 sFrontierTrainerText275PlayerLost[] = _("이겨서 야호 야호 야호!");
static const u8 sFrontierTrainerText275PlayerWon[] = _("야호! 네가 기뻐서 좋아");
static const u8 sFrontierTrainerText276Before[] = _("벌레포켓몬을 잔뜩 데려왔어");
static const u8 sFrontierTrainerText276PlayerLost[] = _("내 벌레포켓몬은 최강이라고!");
static const u8 sFrontierTrainerText276PlayerWon[] = _("내 벌레포켓몬이\n전부 뒤집혔어!");
static const u8 sFrontierTrainerText277Before[] = _("불타입과 비행타입이 정말 싫어");
static const u8 sFrontierTrainerText277PlayerLost[] = _("벌레포켓몬도 나쁘지 않지?");
static const u8 sFrontierTrainerText277PlayerWon[] = _("우리가 뭘 싫어하는지 알지?");
static const u8 sFrontierTrainerText278Before[] = _("낚시란 인생의 선택이야");
static const u8 sFrontierTrainerText278PlayerLost[] = _("물포켓몬에게\n끝없이 끌려!");
static const u8 sFrontierTrainerText278PlayerWon[] = _("다음에는 이렇게 안 될걸");
static const u8 sFrontierTrainerText279Before[] = _("어른인 나는 배틀이 쉬워");
static const u8 sFrontierTrainerText279PlayerLost[] = _("어른답게 기쁨을 삼켰어");
static const u8 sFrontierTrainerText279PlayerWon[] = _("어른답게 화풀이는 안 해");
static const u8 sFrontierTrainerText280Before[] = _("최선을 다하겠어!");
static const u8 sFrontierTrainerText280PlayerLost[] = _("충분히 노력하면 이길 수 있어");
static const u8 sFrontierTrainerText280PlayerWon[] = _("그래도 노력은 했잖아?");
static const u8 sFrontierTrainerText281Before[] = _("어제까지 방학이었어");
static const u8 sFrontierTrainerText281PlayerLost[] = _("내 실력 아직 안 죽었네");
static const u8 sFrontierTrainerText281PlayerWon[] = _("이제 끝이야...\n난 잠이 필요해");
static const u8 sFrontierTrainerText282Before[] = _("왜 그래?\n내가 무서워?");
static const u8 sFrontierTrainerText282PlayerLost[] = _("난 멋지지만 무섭진 않아!");
static const u8 sFrontierTrainerText282PlayerWon[] = _("내 멋진 패션 센스를 봐");
static const u8 sFrontierTrainerText283Before[] = _("난 포켓몬을\n보는 게 더 좋아");
static const u8 sFrontierTrainerText283PlayerLost[] = _("어? 내가 이겼다고!?");
static const u8 sFrontierTrainerText283PlayerWon[] = _("봤지? 난 항상 진다니까");
static const u8 sFrontierTrainerText284Before[] = _("나한테 발버둥 쳐봐야 소용없어");
static const u8 sFrontierTrainerText284PlayerLost[] = _("지옥의바퀴처럼\n아래로 굴러가렴");
static const u8 sFrontierTrainerText284PlayerWon[] = _("아래로 아래로 내려간다!");
static const u8 sFrontierTrainerText285Before[] = _("내 노래 들어볼래?");
static const u8 sFrontierTrainerText285PlayerLost[] = _("난 만족했어!");
static const u8 sFrontierTrainerText285PlayerWon[] = _("만족할 수가 없어");
static const u8 sFrontierTrainerText286Before[] = _("비행포켓몬보다 나은 건 없지");
static const u8 sFrontierTrainerText286PlayerLost[] = _("넌 이길 수 없어!\n비행포켓몬은 최고니까");
static const u8 sFrontierTrainerText286PlayerWon[] = _("비행포켓몬 더 없나?");
static const u8 sFrontierTrainerText287Before[] = _("내 포켓몬 마음에 들어?");
static const u8 sFrontierTrainerText287PlayerLost[] = _("역시 내 포켓몬이\n마음에 들었구나?");
static const u8 sFrontierTrainerText287PlayerWon[] = _("그럼 내 포켓몬이\n싫다는 거야?");
static const u8 sFrontierTrainerText288Before[] = _("이기게 해주면\n은혜갚기를 할게");
static const u8 sFrontierTrainerText288PlayerLost[] = _("자 여기 맹독 사탕");
static const u8 sFrontierTrainerText288PlayerWon[] = _("은혜갚기를 하겠다고?\n뭐 하려고!?");
static const u8 sFrontierTrainerText289Before[] = _("행복한 자랑 좀 해도 될까?");
static const u8 sFrontierTrainerText289PlayerLost[] = _("내 자랑 좀 들어줘");
static const u8 sFrontierTrainerText289PlayerWon[] = _("내 말을\n안 들어줘서 실망이야");
static const u8 sFrontierTrainerText290Before[] = _("덤벼! 기술을 써줄 테니");
static const u8 sFrontierTrainerText290PlayerLost[] = _("이제 낮잠 잘 수 있겠다");
static const u8 sFrontierTrainerText290PlayerWon[] = _("이제 낮잠 좀 자야겠어");
static const u8 sFrontierTrainerText291Before[] = _("내가 얼마나 강한지 가르쳐 줄게");
static const u8 sFrontierTrainerText291PlayerLost[] = _("봐! 나한테 아주\n깨트리기를 제대로 당했지?");
static const u8 sFrontierTrainerText291PlayerWon[] = _("내 화풀이는 분화 직전이야");
static const u8 sFrontierTrainerText292Before[] = _("완벽한 불꽃몸이란\n바로 이런 거지!");
static const u8 sFrontierTrainerText292PlayerLost[] = _("내 이글이글 댄스를 봐!");
static const u8 sFrontierTrainerText292PlayerWon[] = _("여기서 콱 대폭발을 해 버려?");
static const u8 sFrontierTrainerText293Before[] = _("노인들 중에선 내가 1등일세");
static const u8 sFrontierTrainerText293PlayerLost[] = _("말했잖나 1등이라고!");
static const u8 sFrontierTrainerText293PlayerWon[] = _("이젠 1등이 아니구먼...");
static const u8 sFrontierTrainerText294Before[] = _("나 지금 들떴으니까\n너도 그래야 해");
static const u8 sFrontierTrainerText294PlayerLost[] = _("들떠도 승부를\n이렇게 하면 안 되지");
static const u8 sFrontierTrainerText294PlayerWon[] = _("들떠서 멀리 떠나갈 거야");
static const u8 sFrontierTrainerText295Before[] = _("함께 배틀을 즐기자");
static const u8 sFrontierTrainerText295PlayerLost[] = _("이거야! 정말 고마워");
static const u8 sFrontierTrainerText295PlayerWon[] = _("이거야! 계속 가");
static const u8 sFrontierTrainerText296Before[] = _("난 너무 예쁜 패션은 싫어");
static const u8 sFrontierTrainerText296PlayerLost[] = _("패션은 사람과 맞아야 해");
static const u8 sFrontierTrainerText296PlayerWon[] = _("예쁜 것도 괜찮을 수 있지");
static const u8 sFrontierTrainerText297Before[] = _("난 전력을 다할 거야!");
static const u8 sFrontierTrainerText297PlayerLost[] = _("애처럼 굴지 마!");
static const u8 sFrontierTrainerText297PlayerWon[] = _("네가 이겼어! 계속 가!");
static const u8 sFrontierTrainerText298Before[] = _("상쾌한 트레이너가 좋아");
static const u8 sFrontierTrainerText298PlayerLost[] = _("승리의 향기는 달콤한향기!");
static const u8 sFrontierTrainerText298PlayerWon[] = _("뭐야 이 지독한 악취는!");
static const u8 sFrontierTrainerText299Before[] = _("트레이너로서 역린\n폭주를 보여주겠어");
static const u8 sFrontierTrainerText299PlayerLost[] = _("당연한 결과야! 잘 가!");
static const u8 sFrontierTrainerText299PlayerWon[] = _("믿기 어렵지만 축하해");

static const u8 *const sFrontierTrainerText[][3] =
{
    [FRONTIER_TRAINER_BRADY] = {sFrontierTrainerText000Before, sFrontierTrainerText000PlayerLost, sFrontierTrainerText000PlayerWon},
    [FRONTIER_TRAINER_CONNER] = {sFrontierTrainerText001Before, sFrontierTrainerText001PlayerLost, sFrontierTrainerText001PlayerWon},
    [FRONTIER_TRAINER_BRADLEY] = {sFrontierTrainerText002Before, sFrontierTrainerText002PlayerLost, sFrontierTrainerText002PlayerWon},
    [FRONTIER_TRAINER_CYBIL] = {sFrontierTrainerText003Before, sFrontierTrainerText003PlayerLost, sFrontierTrainerText003PlayerWon},
    [FRONTIER_TRAINER_RODETTE] = {sFrontierTrainerText004Before, sFrontierTrainerText004PlayerLost, sFrontierTrainerText004PlayerWon},
    [FRONTIER_TRAINER_PEGGY] = {sFrontierTrainerText005Before, sFrontierTrainerText005PlayerLost, sFrontierTrainerText005PlayerWon},
    [FRONTIER_TRAINER_KEITH] = {sFrontierTrainerText006Before, sFrontierTrainerText006PlayerLost, sFrontierTrainerText006PlayerWon},
    [FRONTIER_TRAINER_GRAYSON] = {sFrontierTrainerText007Before, sFrontierTrainerText007PlayerLost, sFrontierTrainerText007PlayerWon},
    [FRONTIER_TRAINER_GLENN] = {sFrontierTrainerText008Before, sFrontierTrainerText008PlayerLost, sFrontierTrainerText008PlayerWon},
    [FRONTIER_TRAINER_LILIANA] = {sFrontierTrainerText009Before, sFrontierTrainerText009PlayerLost, sFrontierTrainerText009PlayerWon},
    [FRONTIER_TRAINER_ELISE] = {sFrontierTrainerText010Before, sFrontierTrainerText010PlayerLost, sFrontierTrainerText010PlayerWon},
    [FRONTIER_TRAINER_ZOEY] = {sFrontierTrainerText011Before, sFrontierTrainerText011PlayerLost, sFrontierTrainerText011PlayerWon},
    [FRONTIER_TRAINER_MANUEL] = {sFrontierTrainerText012Before, sFrontierTrainerText012PlayerLost, sFrontierTrainerText012PlayerWon},
    [FRONTIER_TRAINER_RUSS] = {sFrontierTrainerText013Before, sFrontierTrainerText013PlayerLost, sFrontierTrainerText013PlayerWon},
    [FRONTIER_TRAINER_DUSTIN] = {sFrontierTrainerText014Before, sFrontierTrainerText014PlayerLost, sFrontierTrainerText014PlayerWon},
    [FRONTIER_TRAINER_TINA] = {sFrontierTrainerText015Before, sFrontierTrainerText015PlayerLost, sFrontierTrainerText015PlayerWon},
    [FRONTIER_TRAINER_GILLIAN1] = {sFrontierTrainerText016Before, sFrontierTrainerText016PlayerLost, sFrontierTrainerText016PlayerWon},
    [FRONTIER_TRAINER_ZOE] = {sFrontierTrainerText017Before, sFrontierTrainerText017PlayerLost, sFrontierTrainerText017PlayerWon},
    [FRONTIER_TRAINER_CHEN] = {sFrontierTrainerText018Before, sFrontierTrainerText018PlayerLost, sFrontierTrainerText018PlayerWon},
    [FRONTIER_TRAINER_AL] = {sFrontierTrainerText019Before, sFrontierTrainerText019PlayerLost, sFrontierTrainerText019PlayerWon},
    [FRONTIER_TRAINER_MITCH] = {sFrontierTrainerText020Before, sFrontierTrainerText020PlayerLost, sFrontierTrainerText020PlayerWon},
    [FRONTIER_TRAINER_ANNE] = {sFrontierTrainerText021Before, sFrontierTrainerText021PlayerLost, sFrontierTrainerText021PlayerWon},
    [FRONTIER_TRAINER_ALIZE] = {sFrontierTrainerText022Before, sFrontierTrainerText022PlayerLost, sFrontierTrainerText022PlayerWon},
    [FRONTIER_TRAINER_LAUREN] = {sFrontierTrainerText023Before, sFrontierTrainerText023PlayerLost, sFrontierTrainerText023PlayerWon},
    [FRONTIER_TRAINER_KIPP] = {sFrontierTrainerText024Before, sFrontierTrainerText024PlayerLost, sFrontierTrainerText024PlayerWon},
    [FRONTIER_TRAINER_JASON] = {sFrontierTrainerText025Before, sFrontierTrainerText025PlayerLost, sFrontierTrainerText025PlayerWon},
    [FRONTIER_TRAINER_JOHN] = {sFrontierTrainerText026Before, sFrontierTrainerText026PlayerLost, sFrontierTrainerText026PlayerWon},
    [FRONTIER_TRAINER_ANN] = {sFrontierTrainerText027Before, sFrontierTrainerText027PlayerLost, sFrontierTrainerText027PlayerWon},
    [FRONTIER_TRAINER_EILEEN] = {sFrontierTrainerText028Before, sFrontierTrainerText028PlayerLost, sFrontierTrainerText028PlayerWon},
    [FRONTIER_TRAINER_CARLIE] = {sFrontierTrainerText029Before, sFrontierTrainerText029PlayerLost, sFrontierTrainerText029PlayerWon},
    [FRONTIER_TRAINER_GORDON] = {sFrontierTrainerText030Before, sFrontierTrainerText030PlayerLost, sFrontierTrainerText030PlayerWon},
    [FRONTIER_TRAINER_AYDEN] = {sFrontierTrainerText031Before, sFrontierTrainerText031PlayerLost, sFrontierTrainerText031PlayerWon},
    [FRONTIER_TRAINER_MARCO] = {sFrontierTrainerText032Before, sFrontierTrainerText032PlayerLost, sFrontierTrainerText032PlayerWon},
    [FRONTIER_TRAINER_CIERRA] = {sFrontierTrainerText033Before, sFrontierTrainerText033PlayerLost, sFrontierTrainerText033PlayerWon},
    [FRONTIER_TRAINER_MARCY] = {sFrontierTrainerText034Before, sFrontierTrainerText034PlayerLost, sFrontierTrainerText034PlayerWon},
    [FRONTIER_TRAINER_KATHY] = {sFrontierTrainerText035Before, sFrontierTrainerText035PlayerLost, sFrontierTrainerText035PlayerWon},
    [FRONTIER_TRAINER_PEYTON] = {sFrontierTrainerText036Before, sFrontierTrainerText036PlayerLost, sFrontierTrainerText036PlayerWon},
    [FRONTIER_TRAINER_JULIAN] = {sFrontierTrainerText037Before, sFrontierTrainerText037PlayerLost, sFrontierTrainerText037PlayerWon},
    [FRONTIER_TRAINER_QUINN] = {sFrontierTrainerText038Before, sFrontierTrainerText038PlayerLost, sFrontierTrainerText038PlayerWon},
    [FRONTIER_TRAINER_HAYLEE] = {sFrontierTrainerText039Before, sFrontierTrainerText039PlayerLost, sFrontierTrainerText039PlayerWon},
    [FRONTIER_TRAINER_AMANDA] = {sFrontierTrainerText040Before, sFrontierTrainerText040PlayerLost, sFrontierTrainerText040PlayerWon},
    [FRONTIER_TRAINER_STACY] = {sFrontierTrainerText041Before, sFrontierTrainerText041PlayerLost, sFrontierTrainerText041PlayerWon},
    [FRONTIER_TRAINER_RAFAEL] = {sFrontierTrainerText042Before, sFrontierTrainerText042PlayerLost, sFrontierTrainerText042PlayerWon},
    [FRONTIER_TRAINER_OLIVER] = {sFrontierTrainerText043Before, sFrontierTrainerText043PlayerLost, sFrontierTrainerText043PlayerWon},
    [FRONTIER_TRAINER_PAYTON] = {sFrontierTrainerText044Before, sFrontierTrainerText044PlayerLost, sFrontierTrainerText044PlayerWon},
    [FRONTIER_TRAINER_PAMELA] = {sFrontierTrainerText045Before, sFrontierTrainerText045PlayerLost, sFrontierTrainerText045PlayerWon},
    [FRONTIER_TRAINER_ELIZA] = {sFrontierTrainerText046Before, sFrontierTrainerText046PlayerLost, sFrontierTrainerText046PlayerWon},
    [FRONTIER_TRAINER_MARISA] = {sFrontierTrainerText047Before, sFrontierTrainerText047PlayerLost, sFrontierTrainerText047PlayerWon},
    [FRONTIER_TRAINER_LEWIS] = {sFrontierTrainerText048Before, sFrontierTrainerText048PlayerLost, sFrontierTrainerText048PlayerWon},
    [FRONTIER_TRAINER_YOSHI] = {sFrontierTrainerText049Before, sFrontierTrainerText049PlayerLost, sFrontierTrainerText049PlayerWon},
    [FRONTIER_TRAINER_DESTIN] = {sFrontierTrainerText050Before, sFrontierTrainerText050PlayerLost, sFrontierTrainerText050PlayerWon},
    [FRONTIER_TRAINER_KEON] = {sFrontierTrainerText051Before, sFrontierTrainerText051PlayerLost, sFrontierTrainerText051PlayerWon},
    [FRONTIER_TRAINER_STUART] = {sFrontierTrainerText052Before, sFrontierTrainerText052PlayerLost, sFrontierTrainerText052PlayerWon},
    [FRONTIER_TRAINER_NESTOR] = {sFrontierTrainerText053Before, sFrontierTrainerText053PlayerLost, sFrontierTrainerText053PlayerWon},
    [FRONTIER_TRAINER_DERRICK] = {sFrontierTrainerText054Before, sFrontierTrainerText054PlayerLost, sFrontierTrainerText054PlayerWon},
    [FRONTIER_TRAINER_BRYSON] = {sFrontierTrainerText055Before, sFrontierTrainerText055PlayerLost, sFrontierTrainerText055PlayerWon},
    [FRONTIER_TRAINER_CLAYTON] = {sFrontierTrainerText056Before, sFrontierTrainerText056PlayerLost, sFrontierTrainerText056PlayerWon},
    [FRONTIER_TRAINER_TRENTON] = {sFrontierTrainerText057Before, sFrontierTrainerText057PlayerLost, sFrontierTrainerText057PlayerWon},
    [FRONTIER_TRAINER_JENSON] = {sFrontierTrainerText058Before, sFrontierTrainerText058PlayerLost, sFrontierTrainerText058PlayerWon},
    [FRONTIER_TRAINER_WESLEY] = {sFrontierTrainerText059Before, sFrontierTrainerText059PlayerLost, sFrontierTrainerText059PlayerWon},
    [FRONTIER_TRAINER_ANTON] = {sFrontierTrainerText060Before, sFrontierTrainerText060PlayerLost, sFrontierTrainerText060PlayerWon},
    [FRONTIER_TRAINER_LAWSON] = {sFrontierTrainerText061Before, sFrontierTrainerText061PlayerLost, sFrontierTrainerText061PlayerWon},
    [FRONTIER_TRAINER_SAMMY] = {sFrontierTrainerText062Before, sFrontierTrainerText062PlayerLost, sFrontierTrainerText062PlayerWon},
    [FRONTIER_TRAINER_ARNIE] = {sFrontierTrainerText063Before, sFrontierTrainerText063PlayerLost, sFrontierTrainerText063PlayerWon},
    [FRONTIER_TRAINER_ADRIAN] = {sFrontierTrainerText064Before, sFrontierTrainerText064PlayerLost, sFrontierTrainerText064PlayerWon},
    [FRONTIER_TRAINER_TRISTAN] = {sFrontierTrainerText065Before, sFrontierTrainerText065PlayerLost, sFrontierTrainerText065PlayerWon},
    [FRONTIER_TRAINER_JULIANA] = {sFrontierTrainerText066Before, sFrontierTrainerText066PlayerLost, sFrontierTrainerText066PlayerWon},
    [FRONTIER_TRAINER_RYLEE] = {sFrontierTrainerText067Before, sFrontierTrainerText067PlayerLost, sFrontierTrainerText067PlayerWon},
    [FRONTIER_TRAINER_CHELSEA] = {sFrontierTrainerText068Before, sFrontierTrainerText068PlayerLost, sFrontierTrainerText068PlayerWon},
    [FRONTIER_TRAINER_DANELA] = {sFrontierTrainerText069Before, sFrontierTrainerText069PlayerLost, sFrontierTrainerText069PlayerWon},
    [FRONTIER_TRAINER_LIZBETH] = {sFrontierTrainerText070Before, sFrontierTrainerText070PlayerLost, sFrontierTrainerText070PlayerWon},
    [FRONTIER_TRAINER_AMELIA] = {sFrontierTrainerText071Before, sFrontierTrainerText071PlayerLost, sFrontierTrainerText071PlayerWon},
    [FRONTIER_TRAINER_JILLIAN] = {sFrontierTrainerText072Before, sFrontierTrainerText072PlayerLost, sFrontierTrainerText072PlayerWon},
    [FRONTIER_TRAINER_ABBIE] = {sFrontierTrainerText073Before, sFrontierTrainerText073PlayerLost, sFrontierTrainerText073PlayerWon},
    [FRONTIER_TRAINER_BRIANA] = {sFrontierTrainerText074Before, sFrontierTrainerText074PlayerLost, sFrontierTrainerText074PlayerWon},
    [FRONTIER_TRAINER_ANTONIO] = {sFrontierTrainerText075Before, sFrontierTrainerText075PlayerLost, sFrontierTrainerText075PlayerWon},
    [FRONTIER_TRAINER_JADEN] = {sFrontierTrainerText076Before, sFrontierTrainerText076PlayerLost, sFrontierTrainerText076PlayerWon},
    [FRONTIER_TRAINER_DAKOTA] = {sFrontierTrainerText077Before, sFrontierTrainerText077PlayerLost, sFrontierTrainerText077PlayerWon},
    [FRONTIER_TRAINER_BRAYDEN] = {sFrontierTrainerText078Before, sFrontierTrainerText078PlayerLost, sFrontierTrainerText078PlayerWon},
    [FRONTIER_TRAINER_CORSON] = {sFrontierTrainerText079Before, sFrontierTrainerText079PlayerLost, sFrontierTrainerText079PlayerWon},
    [FRONTIER_TRAINER_TREVIN] = {sFrontierTrainerText080Before, sFrontierTrainerText080PlayerLost, sFrontierTrainerText080PlayerWon},
    [FRONTIER_TRAINER_PATRICK] = {sFrontierTrainerText081Before, sFrontierTrainerText081PlayerLost, sFrontierTrainerText081PlayerWon},
    [FRONTIER_TRAINER_KADEN] = {sFrontierTrainerText082Before, sFrontierTrainerText082PlayerLost, sFrontierTrainerText082PlayerWon},
    [FRONTIER_TRAINER_MAXWELL] = {sFrontierTrainerText083Before, sFrontierTrainerText083PlayerLost, sFrontierTrainerText083PlayerWon},
    [FRONTIER_TRAINER_DARYL] = {sFrontierTrainerText084Before, sFrontierTrainerText084PlayerLost, sFrontierTrainerText084PlayerWon},
    [FRONTIER_TRAINER_KENNETH] = {sFrontierTrainerText085Before, sFrontierTrainerText085PlayerLost, sFrontierTrainerText085PlayerWon},
    [FRONTIER_TRAINER_RICH] = {sFrontierTrainerText086Before, sFrontierTrainerText086PlayerLost, sFrontierTrainerText086PlayerWon},
    [FRONTIER_TRAINER_CADEN] = {sFrontierTrainerText087Before, sFrontierTrainerText087PlayerLost, sFrontierTrainerText087PlayerWon},
    [FRONTIER_TRAINER_MARLON] = {sFrontierTrainerText088Before, sFrontierTrainerText088PlayerLost, sFrontierTrainerText088PlayerWon},
    [FRONTIER_TRAINER_NASH] = {sFrontierTrainerText089Before, sFrontierTrainerText089PlayerLost, sFrontierTrainerText089PlayerWon},
    [FRONTIER_TRAINER_ROBBY] = {sFrontierTrainerText090Before, sFrontierTrainerText090PlayerLost, sFrontierTrainerText090PlayerWon},
    [FRONTIER_TRAINER_REECE] = {sFrontierTrainerText091Before, sFrontierTrainerText091PlayerLost, sFrontierTrainerText091PlayerWon},
    [FRONTIER_TRAINER_KATHRYN] = {sFrontierTrainerText092Before, sFrontierTrainerText092PlayerLost, sFrontierTrainerText092PlayerWon},
    [FRONTIER_TRAINER_ELLEN] = {sFrontierTrainerText093Before, sFrontierTrainerText093PlayerLost, sFrontierTrainerText093PlayerWon},
    [FRONTIER_TRAINER_RAMON] = {sFrontierTrainerText094Before, sFrontierTrainerText094PlayerLost, sFrontierTrainerText094PlayerWon},
    [FRONTIER_TRAINER_ARTHUR] = {sFrontierTrainerText095Before, sFrontierTrainerText095PlayerLost, sFrontierTrainerText095PlayerWon},
    [FRONTIER_TRAINER_ALONDRA] = {sFrontierTrainerText096Before, sFrontierTrainerText096PlayerLost, sFrontierTrainerText096PlayerWon},
    [FRONTIER_TRAINER_ADRIANA] = {sFrontierTrainerText097Before, sFrontierTrainerText097PlayerLost, sFrontierTrainerText097PlayerWon},
    [FRONTIER_TRAINER_MALIK] = {sFrontierTrainerText098Before, sFrontierTrainerText098PlayerLost, sFrontierTrainerText098PlayerWon},
    [FRONTIER_TRAINER_JILL] = {sFrontierTrainerText099Before, sFrontierTrainerText099PlayerLost, sFrontierTrainerText099PlayerWon},
    [FRONTIER_TRAINER_ERIK] = {sFrontierTrainerText100Before, sFrontierTrainerText100PlayerLost, sFrontierTrainerText100PlayerWon},
    [FRONTIER_TRAINER_YAZMIN] = {sFrontierTrainerText101Before, sFrontierTrainerText101PlayerLost, sFrontierTrainerText101PlayerWon},
    [FRONTIER_TRAINER_JAMAL] = {sFrontierTrainerText102Before, sFrontierTrainerText102PlayerLost, sFrontierTrainerText102PlayerWon},
    [FRONTIER_TRAINER_LESLIE] = {sFrontierTrainerText103Before, sFrontierTrainerText103PlayerLost, sFrontierTrainerText103PlayerWon},
    [FRONTIER_TRAINER_DAVE] = {sFrontierTrainerText104Before, sFrontierTrainerText104PlayerLost, sFrontierTrainerText104PlayerWon},
    [FRONTIER_TRAINER_CARLO] = {sFrontierTrainerText105Before, sFrontierTrainerText105PlayerLost, sFrontierTrainerText105PlayerWon},
    [FRONTIER_TRAINER_EMILIA] = {sFrontierTrainerText106Before, sFrontierTrainerText106PlayerLost, sFrontierTrainerText106PlayerWon},
    [FRONTIER_TRAINER_DALIA] = {sFrontierTrainerText107Before, sFrontierTrainerText107PlayerLost, sFrontierTrainerText107PlayerWon},
    [FRONTIER_TRAINER_HITOMI] = {sFrontierTrainerText108Before, sFrontierTrainerText108PlayerLost, sFrontierTrainerText108PlayerWon},
    [FRONTIER_TRAINER_RICARDO] = {sFrontierTrainerText109Before, sFrontierTrainerText109PlayerLost, sFrontierTrainerText109PlayerWon},
    [FRONTIER_TRAINER_SHIZUKA] = {sFrontierTrainerText110Before, sFrontierTrainerText110PlayerLost, sFrontierTrainerText110PlayerWon},
    [FRONTIER_TRAINER_JOANA] = {sFrontierTrainerText111Before, sFrontierTrainerText111PlayerLost, sFrontierTrainerText111PlayerWon},
    [FRONTIER_TRAINER_KELLY] = {sFrontierTrainerText112Before, sFrontierTrainerText112PlayerLost, sFrontierTrainerText112PlayerWon},
    [FRONTIER_TRAINER_RAYNA] = {sFrontierTrainerText113Before, sFrontierTrainerText113PlayerLost, sFrontierTrainerText113PlayerWon},
    [FRONTIER_TRAINER_EVAN] = {sFrontierTrainerText114Before, sFrontierTrainerText114PlayerLost, sFrontierTrainerText114PlayerWon},
    [FRONTIER_TRAINER_JORDAN] = {sFrontierTrainerText115Before, sFrontierTrainerText115PlayerLost, sFrontierTrainerText115PlayerWon},
    [FRONTIER_TRAINER_JOEL] = {sFrontierTrainerText116Before, sFrontierTrainerText116PlayerLost, sFrontierTrainerText116PlayerWon},
    [FRONTIER_TRAINER_KRISTEN] = {sFrontierTrainerText117Before, sFrontierTrainerText117PlayerLost, sFrontierTrainerText117PlayerWon},
    [FRONTIER_TRAINER_SELPHY] = {sFrontierTrainerText118Before, sFrontierTrainerText118PlayerLost, sFrontierTrainerText118PlayerWon},
    [FRONTIER_TRAINER_CHLOE] = {sFrontierTrainerText119Before, sFrontierTrainerText119PlayerLost, sFrontierTrainerText119PlayerWon},
    [FRONTIER_TRAINER_NORTON] = {sFrontierTrainerText120Before, sFrontierTrainerText120PlayerLost, sFrontierTrainerText120PlayerWon},
    [FRONTIER_TRAINER_LUKAS] = {sFrontierTrainerText121Before, sFrontierTrainerText121PlayerLost, sFrontierTrainerText121PlayerWon},
    [FRONTIER_TRAINER_ZACH] = {sFrontierTrainerText122Before, sFrontierTrainerText122PlayerLost, sFrontierTrainerText122PlayerWon},
    [FRONTIER_TRAINER_KAITLYN] = {sFrontierTrainerText123Before, sFrontierTrainerText123PlayerLost, sFrontierTrainerText123PlayerWon},
    [FRONTIER_TRAINER_BREANNA] = {sFrontierTrainerText124Before, sFrontierTrainerText124PlayerLost, sFrontierTrainerText124PlayerWon},
    [FRONTIER_TRAINER_KENDRA] = {sFrontierTrainerText125Before, sFrontierTrainerText125PlayerLost, sFrontierTrainerText125PlayerWon},
    [FRONTIER_TRAINER_MOLLY] = {sFrontierTrainerText126Before, sFrontierTrainerText126PlayerLost, sFrontierTrainerText126PlayerWon},
    [FRONTIER_TRAINER_JAZMIN] = {sFrontierTrainerText127Before, sFrontierTrainerText127PlayerLost, sFrontierTrainerText127PlayerWon},
    [FRONTIER_TRAINER_KELSEY] = {sFrontierTrainerText128Before, sFrontierTrainerText128PlayerLost, sFrontierTrainerText128PlayerWon},
    [FRONTIER_TRAINER_JALEN] = {sFrontierTrainerText129Before, sFrontierTrainerText129PlayerLost, sFrontierTrainerText129PlayerWon},
    [FRONTIER_TRAINER_GRIFFEN] = {sFrontierTrainerText130Before, sFrontierTrainerText130PlayerLost, sFrontierTrainerText130PlayerWon},
    [FRONTIER_TRAINER_XANDER] = {sFrontierTrainerText131Before, sFrontierTrainerText131PlayerLost, sFrontierTrainerText131PlayerWon},
    [FRONTIER_TRAINER_MARVIN] = {sFrontierTrainerText132Before, sFrontierTrainerText132PlayerLost, sFrontierTrainerText132PlayerWon},
    [FRONTIER_TRAINER_BRENNAN] = {sFrontierTrainerText133Before, sFrontierTrainerText133PlayerLost, sFrontierTrainerText133PlayerWon},
    [FRONTIER_TRAINER_BALEY] = {sFrontierTrainerText134Before, sFrontierTrainerText134PlayerLost, sFrontierTrainerText134PlayerWon},
    [FRONTIER_TRAINER_ZACKARY] = {sFrontierTrainerText135Before, sFrontierTrainerText135PlayerLost, sFrontierTrainerText135PlayerWon},
    [FRONTIER_TRAINER_GABRIEL] = {sFrontierTrainerText136Before, sFrontierTrainerText136PlayerLost, sFrontierTrainerText136PlayerWon},
    [FRONTIER_TRAINER_EMILY] = {sFrontierTrainerText137Before, sFrontierTrainerText137PlayerLost, sFrontierTrainerText137PlayerWon},
    [FRONTIER_TRAINER_JORDYN] = {sFrontierTrainerText138Before, sFrontierTrainerText138PlayerLost, sFrontierTrainerText138PlayerWon},
    [FRONTIER_TRAINER_SOFIA] = {sFrontierTrainerText139Before, sFrontierTrainerText139PlayerLost, sFrontierTrainerText139PlayerWon},
    [FRONTIER_TRAINER_BRADEN] = {sFrontierTrainerText140Before, sFrontierTrainerText140PlayerLost, sFrontierTrainerText140PlayerWon},
    [FRONTIER_TRAINER_KAYDEN] = {sFrontierTrainerText141Before, sFrontierTrainerText141PlayerLost, sFrontierTrainerText141PlayerWon},
    [FRONTIER_TRAINER_COOPER] = {sFrontierTrainerText142Before, sFrontierTrainerText142PlayerLost, sFrontierTrainerText142PlayerWon},
    [FRONTIER_TRAINER_JULIA] = {sFrontierTrainerText143Before, sFrontierTrainerText143PlayerLost, sFrontierTrainerText143PlayerWon},
    [FRONTIER_TRAINER_AMARA] = {sFrontierTrainerText144Before, sFrontierTrainerText144PlayerLost, sFrontierTrainerText144PlayerWon},
    [FRONTIER_TRAINER_LYNN] = {sFrontierTrainerText145Before, sFrontierTrainerText145PlayerLost, sFrontierTrainerText145PlayerWon},
    [FRONTIER_TRAINER_JOVAN] = {sFrontierTrainerText146Before, sFrontierTrainerText146PlayerLost, sFrontierTrainerText146PlayerWon},
    [FRONTIER_TRAINER_DOMINIC] = {sFrontierTrainerText147Before, sFrontierTrainerText147PlayerLost, sFrontierTrainerText147PlayerWon},
    [FRONTIER_TRAINER_NIKOLAS] = {sFrontierTrainerText148Before, sFrontierTrainerText148PlayerLost, sFrontierTrainerText148PlayerWon},
    [FRONTIER_TRAINER_VALERIA] = {sFrontierTrainerText149Before, sFrontierTrainerText149PlayerLost, sFrontierTrainerText149PlayerWon},
    [FRONTIER_TRAINER_DELANEY] = {sFrontierTrainerText150Before, sFrontierTrainerText150PlayerLost, sFrontierTrainerText150PlayerWon},
    [FRONTIER_TRAINER_MEGHAN] = {sFrontierTrainerText151Before, sFrontierTrainerText151PlayerLost, sFrontierTrainerText151PlayerWon},
    [FRONTIER_TRAINER_ROBERTO] = {sFrontierTrainerText152Before, sFrontierTrainerText152PlayerLost, sFrontierTrainerText152PlayerWon},
    [FRONTIER_TRAINER_DAMIAN] = {sFrontierTrainerText153Before, sFrontierTrainerText153PlayerLost, sFrontierTrainerText153PlayerWon},
    [FRONTIER_TRAINER_BRODY] = {sFrontierTrainerText154Before, sFrontierTrainerText154PlayerLost, sFrontierTrainerText154PlayerWon},
    [FRONTIER_TRAINER_GRAHAM] = {sFrontierTrainerText155Before, sFrontierTrainerText155PlayerLost, sFrontierTrainerText155PlayerWon},
    [FRONTIER_TRAINER_TYLOR] = {sFrontierTrainerText156Before, sFrontierTrainerText156PlayerLost, sFrontierTrainerText156PlayerWon},
    [FRONTIER_TRAINER_JAREN] = {sFrontierTrainerText157Before, sFrontierTrainerText157PlayerLost, sFrontierTrainerText157PlayerWon},
    [FRONTIER_TRAINER_CORDELL] = {sFrontierTrainerText158Before, sFrontierTrainerText158PlayerLost, sFrontierTrainerText158PlayerWon},
    [FRONTIER_TRAINER_JAZLYN] = {sFrontierTrainerText159Before, sFrontierTrainerText159PlayerLost, sFrontierTrainerText159PlayerWon},
    [FRONTIER_TRAINER_ZACHERY] = {sFrontierTrainerText160Before, sFrontierTrainerText160PlayerLost, sFrontierTrainerText160PlayerWon},
    [FRONTIER_TRAINER_JOHAN] = {sFrontierTrainerText161Before, sFrontierTrainerText161PlayerLost, sFrontierTrainerText161PlayerWon},
    [FRONTIER_TRAINER_SHEA] = {sFrontierTrainerText162Before, sFrontierTrainerText162PlayerLost, sFrontierTrainerText162PlayerWon},
    [FRONTIER_TRAINER_KAILA] = {sFrontierTrainerText163Before, sFrontierTrainerText163PlayerLost, sFrontierTrainerText163PlayerWon},
    [FRONTIER_TRAINER_ISIAH] = {sFrontierTrainerText164Before, sFrontierTrainerText164PlayerLost, sFrontierTrainerText164PlayerWon},
    [FRONTIER_TRAINER_GARRETT] = {sFrontierTrainerText165Before, sFrontierTrainerText165PlayerLost, sFrontierTrainerText165PlayerWon},
    [FRONTIER_TRAINER_HAYLIE] = {sFrontierTrainerText166Before, sFrontierTrainerText166PlayerLost, sFrontierTrainerText166PlayerWon},
    [FRONTIER_TRAINER_MEGAN] = {sFrontierTrainerText167Before, sFrontierTrainerText167PlayerLost, sFrontierTrainerText167PlayerWon},
    [FRONTIER_TRAINER_ISSAC] = {sFrontierTrainerText168Before, sFrontierTrainerText168PlayerLost, sFrontierTrainerText168PlayerWon},
    [FRONTIER_TRAINER_QUINTON] = {sFrontierTrainerText169Before, sFrontierTrainerText169PlayerLost, sFrontierTrainerText169PlayerWon},
    [FRONTIER_TRAINER_SALMA] = {sFrontierTrainerText170Before, sFrontierTrainerText170PlayerLost, sFrontierTrainerText170PlayerWon},
    [FRONTIER_TRAINER_ANSLEY] = {sFrontierTrainerText171Before, sFrontierTrainerText171PlayerLost, sFrontierTrainerText171PlayerWon},
    [FRONTIER_TRAINER_HOLDEN] = {sFrontierTrainerText172Before, sFrontierTrainerText172PlayerLost, sFrontierTrainerText172PlayerWon},
    [FRONTIER_TRAINER_LUCA] = {sFrontierTrainerText173Before, sFrontierTrainerText173PlayerLost, sFrontierTrainerText173PlayerWon},
    [FRONTIER_TRAINER_JAMISON] = {sFrontierTrainerText174Before, sFrontierTrainerText174PlayerLost, sFrontierTrainerText174PlayerWon},
    [FRONTIER_TRAINER_GUNNAR] = {sFrontierTrainerText175Before, sFrontierTrainerText175PlayerLost, sFrontierTrainerText175PlayerWon},
    [FRONTIER_TRAINER_CRAIG] = {sFrontierTrainerText176Before, sFrontierTrainerText176PlayerLost, sFrontierTrainerText176PlayerWon},
    [FRONTIER_TRAINER_PIERCE] = {sFrontierTrainerText177Before, sFrontierTrainerText177PlayerLost, sFrontierTrainerText177PlayerWon},
    [FRONTIER_TRAINER_REGINA] = {sFrontierTrainerText178Before, sFrontierTrainerText178PlayerLost, sFrontierTrainerText178PlayerWon},
    [FRONTIER_TRAINER_ALISON] = {sFrontierTrainerText179Before, sFrontierTrainerText179PlayerLost, sFrontierTrainerText179PlayerWon},
    [FRONTIER_TRAINER_HANK] = {sFrontierTrainerText180Before, sFrontierTrainerText180PlayerLost, sFrontierTrainerText180PlayerWon},
    [FRONTIER_TRAINER_EARL] = {sFrontierTrainerText181Before, sFrontierTrainerText181PlayerLost, sFrontierTrainerText181PlayerWon},
    [FRONTIER_TRAINER_RAMIRO] = {sFrontierTrainerText182Before, sFrontierTrainerText182PlayerLost, sFrontierTrainerText182PlayerWon},
    [FRONTIER_TRAINER_HUNTER] = {sFrontierTrainerText183Before, sFrontierTrainerText183PlayerLost, sFrontierTrainerText183PlayerWon},
    [FRONTIER_TRAINER_AIDEN] = {sFrontierTrainerText184Before, sFrontierTrainerText184PlayerLost, sFrontierTrainerText184PlayerWon},
    [FRONTIER_TRAINER_XAVIER] = {sFrontierTrainerText185Before, sFrontierTrainerText185PlayerLost, sFrontierTrainerText185PlayerWon},
    [FRONTIER_TRAINER_CLINTON] = {sFrontierTrainerText186Before, sFrontierTrainerText186PlayerLost, sFrontierTrainerText186PlayerWon},
    [FRONTIER_TRAINER_JESSE] = {sFrontierTrainerText187Before, sFrontierTrainerText187PlayerLost, sFrontierTrainerText187PlayerWon},
    [FRONTIER_TRAINER_EDUARDO] = {sFrontierTrainerText188Before, sFrontierTrainerText188PlayerLost, sFrontierTrainerText188PlayerWon},
    [FRONTIER_TRAINER_HAL] = {sFrontierTrainerText189Before, sFrontierTrainerText189PlayerLost, sFrontierTrainerText189PlayerWon},
    [FRONTIER_TRAINER_GAGE] = {sFrontierTrainerText190Before, sFrontierTrainerText190PlayerLost, sFrontierTrainerText190PlayerWon},
    [FRONTIER_TRAINER_ARNOLD] = {sFrontierTrainerText191Before, sFrontierTrainerText191PlayerLost, sFrontierTrainerText191PlayerWon},
    [FRONTIER_TRAINER_JARRETT] = {sFrontierTrainerText192Before, sFrontierTrainerText192PlayerLost, sFrontierTrainerText192PlayerWon},
    [FRONTIER_TRAINER_GARETT] = {sFrontierTrainerText193Before, sFrontierTrainerText193PlayerLost, sFrontierTrainerText193PlayerWon},
    [FRONTIER_TRAINER_EMANUEL] = {sFrontierTrainerText194Before, sFrontierTrainerText194PlayerLost, sFrontierTrainerText194PlayerWon},
    [FRONTIER_TRAINER_GUSTAVO] = {sFrontierTrainerText195Before, sFrontierTrainerText195PlayerLost, sFrontierTrainerText195PlayerWon},
    [FRONTIER_TRAINER_KAMERON] = {sFrontierTrainerText196Before, sFrontierTrainerText196PlayerLost, sFrontierTrainerText196PlayerWon},
    [FRONTIER_TRAINER_ALFREDO] = {sFrontierTrainerText197Before, sFrontierTrainerText197PlayerLost, sFrontierTrainerText197PlayerWon},
    [FRONTIER_TRAINER_RUBEN] = {sFrontierTrainerText198Before, sFrontierTrainerText198PlayerLost, sFrontierTrainerText198PlayerWon},
    [FRONTIER_TRAINER_LAMAR] = {sFrontierTrainerText199Before, sFrontierTrainerText199PlayerLost, sFrontierTrainerText199PlayerWon},
    [FRONTIER_TRAINER_JAXON] = {sFrontierTrainerText200Before, sFrontierTrainerText200PlayerLost, sFrontierTrainerText200PlayerWon},
    [FRONTIER_TRAINER_LOGAN] = {sFrontierTrainerText201Before, sFrontierTrainerText201PlayerLost, sFrontierTrainerText201PlayerWon},
    [FRONTIER_TRAINER_EMILEE] = {sFrontierTrainerText202Before, sFrontierTrainerText202PlayerLost, sFrontierTrainerText202PlayerWon},
    [FRONTIER_TRAINER_JOSIE] = {sFrontierTrainerText203Before, sFrontierTrainerText203PlayerLost, sFrontierTrainerText203PlayerWon},
    [FRONTIER_TRAINER_ARMANDO] = {sFrontierTrainerText204Before, sFrontierTrainerText204PlayerLost, sFrontierTrainerText204PlayerWon},
    [FRONTIER_TRAINER_SKYLER] = {sFrontierTrainerText205Before, sFrontierTrainerText205PlayerLost, sFrontierTrainerText205PlayerWon},
    [FRONTIER_TRAINER_RUTH] = {sFrontierTrainerText206Before, sFrontierTrainerText206PlayerLost, sFrontierTrainerText206PlayerWon},
    [FRONTIER_TRAINER_MELODY] = {sFrontierTrainerText207Before, sFrontierTrainerText207PlayerLost, sFrontierTrainerText207PlayerWon},
    [FRONTIER_TRAINER_PEDRO] = {sFrontierTrainerText208Before, sFrontierTrainerText208PlayerLost, sFrontierTrainerText208PlayerWon},
    [FRONTIER_TRAINER_ERICK] = {sFrontierTrainerText209Before, sFrontierTrainerText209PlayerLost, sFrontierTrainerText209PlayerWon},
    [FRONTIER_TRAINER_ELAINE] = {sFrontierTrainerText210Before, sFrontierTrainerText210PlayerLost, sFrontierTrainerText210PlayerWon},
    [FRONTIER_TRAINER_JOYCE] = {sFrontierTrainerText211Before, sFrontierTrainerText211PlayerLost, sFrontierTrainerText211PlayerWon},
    [FRONTIER_TRAINER_TODD] = {sFrontierTrainerText212Before, sFrontierTrainerText212PlayerLost, sFrontierTrainerText212PlayerWon},
    [FRONTIER_TRAINER_GAVIN] = {sFrontierTrainerText213Before, sFrontierTrainerText213PlayerLost, sFrontierTrainerText213PlayerWon},
    [FRONTIER_TRAINER_MALORY] = {sFrontierTrainerText214Before, sFrontierTrainerText214PlayerLost, sFrontierTrainerText214PlayerWon},
    [FRONTIER_TRAINER_ESTHER] = {sFrontierTrainerText215Before, sFrontierTrainerText215PlayerLost, sFrontierTrainerText215PlayerWon},
    [FRONTIER_TRAINER_OSCAR] = {sFrontierTrainerText216Before, sFrontierTrainerText216PlayerLost, sFrontierTrainerText216PlayerWon},
    [FRONTIER_TRAINER_WILSON] = {sFrontierTrainerText217Before, sFrontierTrainerText217PlayerLost, sFrontierTrainerText217PlayerWon},
    [FRONTIER_TRAINER_CLARE] = {sFrontierTrainerText218Before, sFrontierTrainerText218PlayerLost, sFrontierTrainerText218PlayerWon},
    [FRONTIER_TRAINER_TESS] = {sFrontierTrainerText219Before, sFrontierTrainerText219PlayerLost, sFrontierTrainerText219PlayerWon},
    [FRONTIER_TRAINER_LEON] = {sFrontierTrainerText220Before, sFrontierTrainerText220PlayerLost, sFrontierTrainerText220PlayerWon},
    [FRONTIER_TRAINER_ALONZO] = {sFrontierTrainerText221Before, sFrontierTrainerText221PlayerLost, sFrontierTrainerText221PlayerWon},
    [FRONTIER_TRAINER_VINCE] = {sFrontierTrainerText222Before, sFrontierTrainerText222PlayerLost, sFrontierTrainerText222PlayerWon},
    [FRONTIER_TRAINER_BRYON] = {sFrontierTrainerText223Before, sFrontierTrainerText223PlayerLost, sFrontierTrainerText223PlayerWon},
    [FRONTIER_TRAINER_AVA] = {sFrontierTrainerText224Before, sFrontierTrainerText224PlayerLost, sFrontierTrainerText224PlayerWon},
    [FRONTIER_TRAINER_MIRIAM] = {sFrontierTrainerText225Before, sFrontierTrainerText225PlayerLost, sFrontierTrainerText225PlayerWon},
    [FRONTIER_TRAINER_CARRIE] = {sFrontierTrainerText226Before, sFrontierTrainerText226PlayerLost, sFrontierTrainerText226PlayerWon},
    [FRONTIER_TRAINER_GILLIAN2] = {sFrontierTrainerText227Before, sFrontierTrainerText227PlayerLost, sFrontierTrainerText227PlayerWon},
    [FRONTIER_TRAINER_TYLER] = {sFrontierTrainerText228Before, sFrontierTrainerText228PlayerLost, sFrontierTrainerText228PlayerWon},
    [FRONTIER_TRAINER_CHAZ] = {sFrontierTrainerText229Before, sFrontierTrainerText229PlayerLost, sFrontierTrainerText229PlayerWon},
    [FRONTIER_TRAINER_NELSON] = {sFrontierTrainerText230Before, sFrontierTrainerText230PlayerLost, sFrontierTrainerText230PlayerWon},
    [FRONTIER_TRAINER_SHANIA] = {sFrontierTrainerText231Before, sFrontierTrainerText231PlayerLost, sFrontierTrainerText231PlayerWon},
    [FRONTIER_TRAINER_STELLA] = {sFrontierTrainerText232Before, sFrontierTrainerText232PlayerLost, sFrontierTrainerText232PlayerWon},
    [FRONTIER_TRAINER_DORINE] = {sFrontierTrainerText233Before, sFrontierTrainerText233PlayerLost, sFrontierTrainerText233PlayerWon},
    [FRONTIER_TRAINER_MADDOX] = {sFrontierTrainerText234Before, sFrontierTrainerText234PlayerLost, sFrontierTrainerText234PlayerWon},
    [FRONTIER_TRAINER_DAVIN] = {sFrontierTrainerText235Before, sFrontierTrainerText235PlayerLost, sFrontierTrainerText235PlayerWon},
    [FRONTIER_TRAINER_TREVON] = {sFrontierTrainerText236Before, sFrontierTrainerText236PlayerLost, sFrontierTrainerText236PlayerWon},
    [FRONTIER_TRAINER_MATEO] = {sFrontierTrainerText237Before, sFrontierTrainerText237PlayerLost, sFrontierTrainerText237PlayerWon},
    [FRONTIER_TRAINER_BRET] = {sFrontierTrainerText238Before, sFrontierTrainerText238PlayerLost, sFrontierTrainerText238PlayerWon},
    [FRONTIER_TRAINER_RAUL] = {sFrontierTrainerText239Before, sFrontierTrainerText239PlayerLost, sFrontierTrainerText239PlayerWon},
    [FRONTIER_TRAINER_KAY] = {sFrontierTrainerText240Before, sFrontierTrainerText240PlayerLost, sFrontierTrainerText240PlayerWon},
    [FRONTIER_TRAINER_ELENA] = {sFrontierTrainerText241Before, sFrontierTrainerText241PlayerLost, sFrontierTrainerText241PlayerWon},
    [FRONTIER_TRAINER_ALANA] = {sFrontierTrainerText242Before, sFrontierTrainerText242PlayerLost, sFrontierTrainerText242PlayerWon},
    [FRONTIER_TRAINER_ALEXAS] = {sFrontierTrainerText243Before, sFrontierTrainerText243PlayerLost, sFrontierTrainerText243PlayerWon},
    [FRONTIER_TRAINER_WESTON] = {sFrontierTrainerText244Before, sFrontierTrainerText244PlayerLost, sFrontierTrainerText244PlayerWon},
    [FRONTIER_TRAINER_JASPER] = {sFrontierTrainerText245Before, sFrontierTrainerText245PlayerLost, sFrontierTrainerText245PlayerWon},
    [FRONTIER_TRAINER_NADIA] = {sFrontierTrainerText246Before, sFrontierTrainerText246PlayerLost, sFrontierTrainerText246PlayerWon},
    [FRONTIER_TRAINER_MIRANDA] = {sFrontierTrainerText247Before, sFrontierTrainerText247PlayerLost, sFrontierTrainerText247PlayerWon},
    [FRONTIER_TRAINER_EMMA] = {sFrontierTrainerText248Before, sFrontierTrainerText248PlayerLost, sFrontierTrainerText248PlayerWon},
    [FRONTIER_TRAINER_ROLANDO] = {sFrontierTrainerText249Before, sFrontierTrainerText249PlayerLost, sFrontierTrainerText249PlayerWon},
    [FRONTIER_TRAINER_STANLY] = {sFrontierTrainerText250Before, sFrontierTrainerText250PlayerLost, sFrontierTrainerText250PlayerWon},
    [FRONTIER_TRAINER_DARIO] = {sFrontierTrainerText251Before, sFrontierTrainerText251PlayerLost, sFrontierTrainerText251PlayerWon},
    [FRONTIER_TRAINER_KARLEE] = {sFrontierTrainerText252Before, sFrontierTrainerText252PlayerLost, sFrontierTrainerText252PlayerWon},
    [FRONTIER_TRAINER_JAYLIN] = {sFrontierTrainerText253Before, sFrontierTrainerText253PlayerLost, sFrontierTrainerText253PlayerWon},
    [FRONTIER_TRAINER_INGRID] = {sFrontierTrainerText254Before, sFrontierTrainerText254PlayerLost, sFrontierTrainerText254PlayerWon},
    [FRONTIER_TRAINER_DELILAH] = {sFrontierTrainerText255Before, sFrontierTrainerText255PlayerLost, sFrontierTrainerText255PlayerWon},
    [FRONTIER_TRAINER_CARLY] = {sFrontierTrainerText256Before, sFrontierTrainerText256PlayerLost, sFrontierTrainerText256PlayerWon},
    [FRONTIER_TRAINER_LEXIE] = {sFrontierTrainerText257Before, sFrontierTrainerText257PlayerLost, sFrontierTrainerText257PlayerWon},
    [FRONTIER_TRAINER_MILLER] = {sFrontierTrainerText258Before, sFrontierTrainerText258PlayerLost, sFrontierTrainerText258PlayerWon},
    [FRONTIER_TRAINER_MARV] = {sFrontierTrainerText259Before, sFrontierTrainerText259PlayerLost, sFrontierTrainerText259PlayerWon},
    [FRONTIER_TRAINER_LAYTON] = {sFrontierTrainerText260Before, sFrontierTrainerText260PlayerLost, sFrontierTrainerText260PlayerWon},
    [FRONTIER_TRAINER_BROOKS] = {sFrontierTrainerText261Before, sFrontierTrainerText261PlayerLost, sFrontierTrainerText261PlayerWon},
    [FRONTIER_TRAINER_GREGORY] = {sFrontierTrainerText262Before, sFrontierTrainerText262PlayerLost, sFrontierTrainerText262PlayerWon},
    [FRONTIER_TRAINER_REESE] = {sFrontierTrainerText263Before, sFrontierTrainerText263PlayerLost, sFrontierTrainerText263PlayerWon},
    [FRONTIER_TRAINER_MASON] = {sFrontierTrainerText264Before, sFrontierTrainerText264PlayerLost, sFrontierTrainerText264PlayerWon},
    [FRONTIER_TRAINER_TOBY] = {sFrontierTrainerText265Before, sFrontierTrainerText265PlayerLost, sFrontierTrainerText265PlayerWon},
    [FRONTIER_TRAINER_DOROTHY] = {sFrontierTrainerText266Before, sFrontierTrainerText266PlayerLost, sFrontierTrainerText266PlayerWon},
    [FRONTIER_TRAINER_PIPER] = {sFrontierTrainerText267Before, sFrontierTrainerText267PlayerLost, sFrontierTrainerText267PlayerWon},
    [FRONTIER_TRAINER_FINN] = {sFrontierTrainerText268Before, sFrontierTrainerText268PlayerLost, sFrontierTrainerText268PlayerWon},
    [FRONTIER_TRAINER_SAMIR] = {sFrontierTrainerText269Before, sFrontierTrainerText269PlayerLost, sFrontierTrainerText269PlayerWon},
    [FRONTIER_TRAINER_FIONA] = {sFrontierTrainerText270Before, sFrontierTrainerText270PlayerLost, sFrontierTrainerText270PlayerWon},
    [FRONTIER_TRAINER_GLORIA] = {sFrontierTrainerText271Before, sFrontierTrainerText271PlayerLost, sFrontierTrainerText271PlayerWon},
    [FRONTIER_TRAINER_NICO] = {sFrontierTrainerText272Before, sFrontierTrainerText272PlayerLost, sFrontierTrainerText272PlayerWon},
    [FRONTIER_TRAINER_JEREMY] = {sFrontierTrainerText273Before, sFrontierTrainerText273PlayerLost, sFrontierTrainerText273PlayerWon},
    [FRONTIER_TRAINER_CAITLIN] = {sFrontierTrainerText274Before, sFrontierTrainerText274PlayerLost, sFrontierTrainerText274PlayerWon},
    [FRONTIER_TRAINER_REENA] = {sFrontierTrainerText275Before, sFrontierTrainerText275PlayerLost, sFrontierTrainerText275PlayerWon},
    [FRONTIER_TRAINER_AVERY] = {sFrontierTrainerText276Before, sFrontierTrainerText276PlayerLost, sFrontierTrainerText276PlayerWon},
    [FRONTIER_TRAINER_LIAM] = {sFrontierTrainerText277Before, sFrontierTrainerText277PlayerLost, sFrontierTrainerText277PlayerWon},
    [FRONTIER_TRAINER_THEO] = {sFrontierTrainerText278Before, sFrontierTrainerText278PlayerLost, sFrontierTrainerText278PlayerWon},
    [FRONTIER_TRAINER_BAILEY] = {sFrontierTrainerText279Before, sFrontierTrainerText279PlayerLost, sFrontierTrainerText279PlayerWon},
    [FRONTIER_TRAINER_HUGO] = {sFrontierTrainerText280Before, sFrontierTrainerText280PlayerLost, sFrontierTrainerText280PlayerWon},
    [FRONTIER_TRAINER_BRYCE] = {sFrontierTrainerText281Before, sFrontierTrainerText281PlayerLost, sFrontierTrainerText281PlayerWon},
    [FRONTIER_TRAINER_GIDEON] = {sFrontierTrainerText282Before, sFrontierTrainerText282PlayerLost, sFrontierTrainerText282PlayerWon},
    [FRONTIER_TRAINER_TRISTON] = {sFrontierTrainerText283Before, sFrontierTrainerText283PlayerLost, sFrontierTrainerText283PlayerWon},
    [FRONTIER_TRAINER_CHARLES] = {sFrontierTrainerText284Before, sFrontierTrainerText284PlayerLost, sFrontierTrainerText284PlayerWon},
    [FRONTIER_TRAINER_RAYMOND] = {sFrontierTrainerText285Before, sFrontierTrainerText285PlayerLost, sFrontierTrainerText285PlayerWon},
    [FRONTIER_TRAINER_DIRK] = {sFrontierTrainerText286Before, sFrontierTrainerText286PlayerLost, sFrontierTrainerText286PlayerWon},
    [FRONTIER_TRAINER_HAROLD] = {sFrontierTrainerText287Before, sFrontierTrainerText287PlayerLost, sFrontierTrainerText287PlayerWon},
    [FRONTIER_TRAINER_OMAR] = {sFrontierTrainerText288Before, sFrontierTrainerText288PlayerLost, sFrontierTrainerText288PlayerWon},
    [FRONTIER_TRAINER_PETER] = {sFrontierTrainerText289Before, sFrontierTrainerText289PlayerLost, sFrontierTrainerText289PlayerWon},
    [FRONTIER_TRAINER_DEV] = {sFrontierTrainerText290Before, sFrontierTrainerText290PlayerLost, sFrontierTrainerText290PlayerWon},
    [FRONTIER_TRAINER_COREY] = {sFrontierTrainerText291Before, sFrontierTrainerText291PlayerLost, sFrontierTrainerText291PlayerWon},
    [FRONTIER_TRAINER_ANDRE] = {sFrontierTrainerText292Before, sFrontierTrainerText292PlayerLost, sFrontierTrainerText292PlayerWon},
    [FRONTIER_TRAINER_FERRIS] = {sFrontierTrainerText293Before, sFrontierTrainerText293PlayerLost, sFrontierTrainerText293PlayerWon},
    [FRONTIER_TRAINER_ALIVIA] = {sFrontierTrainerText294Before, sFrontierTrainerText294PlayerLost, sFrontierTrainerText294PlayerWon},
    [FRONTIER_TRAINER_PAIGE] = {sFrontierTrainerText295Before, sFrontierTrainerText295PlayerLost, sFrontierTrainerText295PlayerWon},
    [FRONTIER_TRAINER_ANYA] = {sFrontierTrainerText296Before, sFrontierTrainerText296PlayerLost, sFrontierTrainerText296PlayerWon},
    [FRONTIER_TRAINER_DAWN] = {sFrontierTrainerText297Before, sFrontierTrainerText297PlayerLost, sFrontierTrainerText297PlayerWon},
    [FRONTIER_TRAINER_ABBY] = {sFrontierTrainerText298Before, sFrontierTrainerText298PlayerLost, sFrontierTrainerText298PlayerWon},
    [FRONTIER_TRAINER_GRETEL] = {sFrontierTrainerText299Before, sFrontierTrainerText299PlayerLost, sFrontierTrainerText299PlayerWon},
};

static const u8 sSlateportTentTrainerText000Before[] = _("내일의 나는 뭐가 될까?");
static const u8 sSlateportTentTrainerText000PlayerLost[] = _("오늘은 금요일 같은 기분이야!");
static const u8 sSlateportTentTrainerText000PlayerWon[] = _("월요일 같은 기분이네...");
static const u8 sSlateportTentTrainerText001Before[] = _("나쁜 소식이야!\n모래지옥이다!");
static const u8 sSlateportTentTrainerText001PlayerLost[] = _("야호! 해냈다!");
static const u8 sSlateportTentTrainerText001PlayerWon[] = _("모래지옥에 당해서 졌어...");
static const u8 sSlateportTentTrainerText002Before[] = _("가라!! 내 목욕 포켓몬!!");
static const u8 sSlateportTentTrainerText002PlayerLost[] = _("야호-!! 내 목욕 포켓몬!!");
static const u8 sSlateportTentTrainerText002PlayerWon[] = _("아악!! 내 목욕 포켓몬!!");
static const u8 sSlateportTentTrainerText003Before[] = _("나라는 바다회오리에 휘말려봐");
static const u8 sSlateportTentTrainerText003PlayerLost[] = _("너도 꽤 괜찮은 바다회오리구나");
static const u8 sSlateportTentTrainerText003PlayerWon[] = _("엄청난 바다회오리였어...");
static const u8 sSlateportTentTrainerText004Before[] = _("대화는 내가 이긴 뒤에 하자");
static const u8 sSlateportTentTrainerText004PlayerLost[] = _("멋져! 이제 신나게 가볼게");
static const u8 sSlateportTentTrainerText004PlayerWon[] = _("아니야! 아직 진심 아니었어");
static const u8 sSlateportTentTrainerText005Before[] = _("내 아름다움에 위축됐니?");
static const u8 sSlateportTentTrainerText005PlayerLost[] = _("미안하지만 너 좀 시시해");
static const u8 sSlateportTentTrainerText005PlayerWon[] = _("이거 정말 즐거운걸!");
static const u8 sSlateportTentTrainerText006Before[] = _("메깅을 잡아 와 줘");
static const u8 sSlateportTentTrainerText006PlayerLost[] = _("뭐야 메깅이 없잖아");
static const u8 sSlateportTentTrainerText006PlayerWon[] = _("부탁이야! 메깅이 꼭 필요해");
static const u8 sSlateportTentTrainerText007Before[] = _("크르르르!! 크르르르!!");
static const u8 sSlateportTentTrainerText007PlayerLost[] = _("울부짖기!! 울부짖기!!");
static const u8 sSlateportTentTrainerText007PlayerWon[] = _("으으... 으아앙!!");
static const u8 sSlateportTentTrainerText008Before[] = _("널 위해 꽃잎댄스를\n조금 보여줄게!");
static const u8 sSlateportTentTrainerText008PlayerLost[] = _("이건 어디까지나 일이야");
static const u8 sSlateportTentTrainerText008PlayerWon[] = _("어떻게 나한테\n그럴 수 있어?");
static const u8 sSlateportTentTrainerText009Before[] = _("나가서 마음껏 달리고 싶어");
static const u8 sSlateportTentTrainerText009PlayerLost[] = _("와아! 같이 달릴래?");
static const u8 sSlateportTentTrainerText009PlayerWon[] = _("자전거 타는 것도 괜찮겠지");
static const u8 sSlateportTentTrainerText010Before[] = _("내 이상한빛을 잘 봐");
static const u8 sSlateportTentTrainerText010PlayerLost[] = _("야호! 내 이상한빛이 최고야");
static const u8 sSlateportTentTrainerText010PlayerWon[] = _("으악!!! 미 미안해!");
static const u8 sSlateportTentTrainerText011Before[] = _("들어봐... 너\n그리 잘하진 않아");
static const u8 sSlateportTentTrainerText011PlayerLost[] = _("봤지? 내 말이 맞았어");
static const u8 sSlateportTentTrainerText011PlayerWon[] = _("그래 그래... 제법이네 너");
static const u8 sSlateportTentTrainerText012Before[] = _("...... ...... ......?");
static const u8 sSlateportTentTrainerText012PlayerLost[] = _("...... ...... ......\n와아");
static const u8 sSlateportTentTrainerText012PlayerWon[] = _("...... ...... ......\n야호");
static const u8 sSlateportTentTrainerText013Before[] = _("식스테일에 네이티오에\n블래키에... 음...");
static const u8 sSlateportTentTrainerText013PlayerLost[] = _("코코파스에... 음... 세비퍼!");
static const u8 sSlateportTentTrainerText013PlayerWon[] = _("코코파스에... 음...\n잠만보... 아차");
static const u8 sSlateportTentTrainerText014Before[] = _("맛있게 즐겨볼까!");
static const u8 sSlateportTentTrainerText014PlayerLost[] = _("이 맛있는 승리를 즐길게");
static const u8 sSlateportTentTrainerText014PlayerWon[] = _("최악이야!! 정말 최악!!");
static const u8 sSlateportTentTrainerText015Before[] = _("맛있어 보이는 빛이 나");
static const u8 sSlateportTentTrainerText015PlayerLost[] = _("못 참겠어! 악취가 나");
static const u8 sSlateportTentTrainerText015PlayerWon[] = _("넌 날 멈출 수 없어...");
static const u8 sSlateportTentTrainerText016Before[] = _("포켓몬은 돈이나\n가족보다 먼저야");
static const u8 sSlateportTentTrainerText016PlayerLost[] = _("그래서 내가 강한 거야");
static const u8 sSlateportTentTrainerText016PlayerWon[] = _("다 제쳐둔 결과가 이거라니");
static const u8 sSlateportTentTrainerText017Before[] = _("네 강한 모습이 정말 마음에 들어");
static const u8 sSlateportTentTrainerText017PlayerLost[] = _("네가 발버둥 치는 방식\n마음에 들었어");
static const u8 sSlateportTentTrainerText017PlayerWon[] = _("넌 못되고 지독한 트레이너야");
static const u8 sSlateportTentTrainerText018Before[] = _("내 저주로\n네 기세를 꺾어주지");
static const u8 sSlateportTentTrainerText018PlayerLost[] = _("저주? 거짓말이지...");
static const u8 sSlateportTentTrainerText018PlayerWon[] = _("내 저주는 영원히 남을 거야");
static const u8 sSlateportTentTrainerText019Before[] = _("응?\n배틀이라고 했어?");
static const u8 sSlateportTentTrainerText019PlayerLost[] = _("응?\n강하지만 아직 부족해");
static const u8 sSlateportTentTrainerText019PlayerWon[] = _("응?\n네 괴력에는 항복이야");
static const u8 sSlateportTentTrainerText020Before[] = _("미안하지만\n넌 집단구타를 맞게 될 거야");
static const u8 sSlateportTentTrainerText020PlayerLost[] = _("말했잖아\n넌 집단구타 당할 거라고");
static const u8 sSlateportTentTrainerText020PlayerWon[] = _("어쩌다 내가\n집단구타를 당한 거야?");
static const u8 sSlateportTentTrainerText021Before[] = _("난 귀여운 포켓몬만 원해");
static const u8 sSlateportTentTrainerText021PlayerLost[] = _("그게 너랑 무슨 상관이야?");
static const u8 sSlateportTentTrainerText021PlayerWon[] = _("너 좀 굉장한데...");
static const u8 sSlateportTentTrainerText022Before[] = _("장난감! 장난감이 더 필요해");
static const u8 sSlateportTentTrainerText022PlayerLost[] = _("쉽게 벌 돈이 빨리 필요해");
static const u8 sSlateportTentTrainerText022PlayerWon[] = _("돈을 벌려면 일해야겠어");
static const u8 sSlateportTentTrainerText023Before[] = _("으으음... 뭐 할까?");
static const u8 sSlateportTentTrainerText023PlayerLost[] = _("으으음...\n너 뭐 했어?");
static const u8 sSlateportTentTrainerText023PlayerWon[] = _("으으음...\n오 그래 이거야");
static const u8 sSlateportTentTrainerText024Before[] = _("잡담은 싫으니까\n바로 하자");
static const u8 sSlateportTentTrainerText024PlayerLost[] = _("그래! 바로 이거야");
static const u8 sSlateportTentTrainerText024PlayerWon[] = _("고마워! 안녕");
static const u8 sSlateportTentTrainerText025Before[] = _("미스터 심사위원\n잘 부탁해");
static const u8 sSlateportTentTrainerText025PlayerLost[] = _("목표는 콘테스트 1등");
static const u8 sSlateportTentTrainerText025PlayerWon[] = _("나 포기 안 할래\n내 아이돌 꿈");
static const u8 sSlateportTentTrainerText026Before[] = _("이런 곳에서 날 만나다니\n운이 없구나?");
static const u8 sSlateportTentTrainerText026PlayerLost[] = _("대단했어\n전력으로 덤볐구나");
static const u8 sSlateportTentTrainerText026PlayerWon[] = _("저리 가...");
static const u8 sSlateportTentTrainerText027Before[] = _("상성이 어떻든 상관없어");
static const u8 sSlateportTentTrainerText027PlayerLost[] = _("하! 넌 트레이너스쿨로\n돌아가야겠는데");
static const u8 sSlateportTentTrainerText027PlayerWon[] = _("공부해야겠네");
static const u8 sSlateportTentTrainerText028Before[] = _("오- 나는 기분이 미끈미끈");
static const u8 sSlateportTentTrainerText028PlayerLost[] = _("네 연승 기록도 미끈미끈\n하하하");
static const u8 sSlateportTentTrainerText028PlayerWon[] = _("나는 당연히 미끈미끈");
static const u8 sSlateportTentTrainerText029Before[] = _("아빠 때문에 화가 나...");
static const u8 sSlateportTentTrainerText029PlayerLost[] = _("난 정말 아빠가 싫어!");
static const u8 sSlateportTentTrainerText029PlayerWon[] = _("그래도 난 아빠를\n정말 좋아해");

static const u8 *const sSlateportTentTrainerText[][3] =
{
    [SLATEPORT_TENT_TRAINER_JOLIE] = {sSlateportTentTrainerText000Before, sSlateportTentTrainerText000PlayerLost, sSlateportTentTrainerText000PlayerWon},
    [SLATEPORT_TENT_TRAINER_MALACHI] = {sSlateportTentTrainerText001Before, sSlateportTentTrainerText001PlayerLost, sSlateportTentTrainerText001PlayerWon},
    [SLATEPORT_TENT_TRAINER_KELSIE] = {sSlateportTentTrainerText002Before, sSlateportTentTrainerText002PlayerLost, sSlateportTentTrainerText002PlayerWon},
    [SLATEPORT_TENT_TRAINER_DAVON] = {sSlateportTentTrainerText003Before, sSlateportTentTrainerText003PlayerLost, sSlateportTentTrainerText003PlayerWon},
    [SLATEPORT_TENT_TRAINER_GLENDA] = {sSlateportTentTrainerText004Before, sSlateportTentTrainerText004PlayerLost, sSlateportTentTrainerText004PlayerWon},
    [SLATEPORT_TENT_TRAINER_HELENA] = {sSlateportTentTrainerText005Before, sSlateportTentTrainerText005PlayerLost, sSlateportTentTrainerText005PlayerWon},
    [SLATEPORT_TENT_TRAINER_RODOLFO] = {sSlateportTentTrainerText006Before, sSlateportTentTrainerText006PlayerLost, sSlateportTentTrainerText006PlayerWon},
    [SLATEPORT_TENT_TRAINER_DAVION] = {sSlateportTentTrainerText007Before, sSlateportTentTrainerText007PlayerLost, sSlateportTentTrainerText007PlayerWon},
    [SLATEPORT_TENT_TRAINER_KENDALL] = {sSlateportTentTrainerText008Before, sSlateportTentTrainerText008PlayerLost, sSlateportTentTrainerText008PlayerWon},
    [SLATEPORT_TENT_TRAINER_COLTEN] = {sSlateportTentTrainerText009Before, sSlateportTentTrainerText009PlayerLost, sSlateportTentTrainerText009PlayerWon},
    [SLATEPORT_TENT_TRAINER_IRVIN] = {sSlateportTentTrainerText010Before, sSlateportTentTrainerText010PlayerLost, sSlateportTentTrainerText010PlayerWon},
    [SLATEPORT_TENT_TRAINER_SHAUN] = {sSlateportTentTrainerText011Before, sSlateportTentTrainerText011PlayerLost, sSlateportTentTrainerText011PlayerWon},
    [SLATEPORT_TENT_TRAINER_KYLER] = {sSlateportTentTrainerText012Before, sSlateportTentTrainerText012PlayerLost, sSlateportTentTrainerText012PlayerWon},
    [SLATEPORT_TENT_TRAINER_MAGGIE] = {sSlateportTentTrainerText013Before, sSlateportTentTrainerText013PlayerLost, sSlateportTentTrainerText013PlayerWon},
    [SLATEPORT_TENT_TRAINER_STEPHON] = {sSlateportTentTrainerText014Before, sSlateportTentTrainerText014PlayerLost, sSlateportTentTrainerText014PlayerWon},
    [SLATEPORT_TENT_TRAINER_REBECCA] = {sSlateportTentTrainerText015Before, sSlateportTentTrainerText015PlayerLost, sSlateportTentTrainerText015PlayerWon},
    [SLATEPORT_TENT_TRAINER_REGGIE] = {sSlateportTentTrainerText016Before, sSlateportTentTrainerText016PlayerLost, sSlateportTentTrainerText016PlayerWon},
    [SLATEPORT_TENT_TRAINER_JANAE] = {sSlateportTentTrainerText017Before, sSlateportTentTrainerText017PlayerLost, sSlateportTentTrainerText017PlayerWon},
    [SLATEPORT_TENT_TRAINER_CAIDEN] = {sSlateportTentTrainerText018Before, sSlateportTentTrainerText018PlayerLost, sSlateportTentTrainerText018PlayerWon},
    [SLATEPORT_TENT_TRAINER_KIRSTEN] = {sSlateportTentTrainerText019Before, sSlateportTentTrainerText019PlayerLost, sSlateportTentTrainerText019PlayerWon},
    [SLATEPORT_TENT_TRAINER_KURTIS] = {sSlateportTentTrainerText020Before, sSlateportTentTrainerText020PlayerLost, sSlateportTentTrainerText020PlayerWon},
    [SLATEPORT_TENT_TRAINER_STEFAN] = {sSlateportTentTrainerText021Before, sSlateportTentTrainerText021PlayerLost, sSlateportTentTrainerText021PlayerWon},
    [SLATEPORT_TENT_TRAINER_AVERY] = {sSlateportTentTrainerText022Before, sSlateportTentTrainerText022PlayerLost, sSlateportTentTrainerText022PlayerWon},
    [SLATEPORT_TENT_TRAINER_DWANE] = {sSlateportTentTrainerText023Before, sSlateportTentTrainerText023PlayerLost, sSlateportTentTrainerText023PlayerWon},
    [SLATEPORT_TENT_TRAINER_MCKENNA] = {sSlateportTentTrainerText024Before, sSlateportTentTrainerText024PlayerLost, sSlateportTentTrainerText024PlayerWon},
    [SLATEPORT_TENT_TRAINER_CAMRYN] = {sSlateportTentTrainerText025Before, sSlateportTentTrainerText025PlayerLost, sSlateportTentTrainerText025PlayerWon},
    [SLATEPORT_TENT_TRAINER_NATASHA] = {sSlateportTentTrainerText026Before, sSlateportTentTrainerText026PlayerLost, sSlateportTentTrainerText026PlayerWon},
    [SLATEPORT_TENT_TRAINER_AUSTYN] = {sSlateportTentTrainerText027Before, sSlateportTentTrainerText027PlayerLost, sSlateportTentTrainerText027PlayerWon},
    [SLATEPORT_TENT_TRAINER_DONOVAN] = {sSlateportTentTrainerText028Before, sSlateportTentTrainerText028PlayerLost, sSlateportTentTrainerText028PlayerWon},
    [SLATEPORT_TENT_TRAINER_TAMIA] = {sSlateportTentTrainerText029Before, sSlateportTentTrainerText029PlayerLost, sSlateportTentTrainerText029PlayerWon},
};

static const u8 sVerdanturfTentTrainerText000Before[] = _("거짓울음 없이는\n하루도 못 살아");
static const u8 sVerdanturfTentTrainerText000PlayerLost[] = _("아- 상쾌해라!");
static const u8 sVerdanturfTentTrainerText000PlayerWon[] = _("내가 받는 건 늘 트집뿐이야");
static const u8 sVerdanturfTentTrainerText001Before[] = _("내가 얼마나 지루한지\n넌 몰라");
static const u8 sVerdanturfTentTrainerText001PlayerLost[] = _("지는 건\n하나도 신나지 않아...");
static const u8 sVerdanturfTentTrainerText001PlayerWon[] = _("신난다!!\n지루함은 이제 안녕");
static const u8 sVerdanturfTentTrainerText002Before[] = _("곧 휴가를 갈 거야");
static const u8 sVerdanturfTentTrainerText002PlayerLost[] = _("돈을 좀 벌어야 해");
static const u8 sVerdanturfTentTrainerText002PlayerWon[] = _("집에 갈 때까지 잠은 없어");
static const u8 sVerdanturfTentTrainerText003Before[] = _("난 똑똑해!\n지면 자폭할 거야");
static const u8 sVerdanturfTentTrainerText003PlayerLost[] = _("기쁨의 대폭발은\n멈추지 않아");
static const u8 sVerdanturfTentTrainerText003PlayerWon[] = _("졌어...\n자폭할 시간이야");
static const u8 sVerdanturfTentTrainerText004Before[] = _("아이돌 노릇도\n이젠 지긋지긋해");
static const u8 sVerdanturfTentTrainerText004PlayerLost[] = _("행복에는 배틀이 최고야");
static const u8 sVerdanturfTentTrainerText004PlayerWon[] = _("져도 난 전혀\n신경 안 써");
static const u8 sVerdanturfTentTrainerText005Before[] = _("내 아름다움이\n너를 놀래키기라도 했니?");
static const u8 sVerdanturfTentTrainerText005PlayerLost[] = _("내가 널 위협했니?");
static const u8 sVerdanturfTentTrainerText005PlayerWon[] = _("내 아름다움이\n네게 전혀 통하지 않았어");
static const u8 sVerdanturfTentTrainerText006Before[] = _("덤벼... 진지하게 배틀하자");
static const u8 sVerdanturfTentTrainerText006PlayerLost[] = _("포기해? 정말 약하네");
static const u8 sVerdanturfTentTrainerText006PlayerWon[] = _("바톤터치를 해야겠어");
static const u8 sVerdanturfTentTrainerText007Before[] = _("좋아! 또 신나는 배틀이야!");
static const u8 sVerdanturfTentTrainerText007PlayerLost[] = _("네 포켓몬은 약하고 시시해");
static const u8 sVerdanturfTentTrainerText007PlayerWon[] = _("와! 신나는 패배였어");
static const u8 sVerdanturfTentTrainerText008Before[] = _("내 수퍼한 기술을 봐!");
static const u8 sVerdanturfTentTrainerText008PlayerLost[] = _("힘들었어...\n나 괜찮은 거야?");
static const u8 sVerdanturfTentTrainerText008PlayerWon[] = _("하이퍼한 널 용서 못 해");
static const u8 sVerdanturfTentTrainerText009Before[] = _("외롭지만 난 혼자 휴가를 가");
static const u8 sVerdanturfTentTrainerText009PlayerLost[] = _("내 조가비갑옷 안으로\n껍질에숨기할 거야");
static const u8 sVerdanturfTentTrainerText009PlayerWon[] = _("오... 언제나처럼 혼자네");
static const u8 sVerdanturfTentTrainerText010Before[] = _("너 정말 강한 거야?");
static const u8 sVerdanturfTentTrainerText010PlayerLost[] = _("와하하하! 와하하하!!");
static const u8 sVerdanturfTentTrainerText010PlayerWon[] = _("잘했어! 난 장난이었지만");
static const u8 sVerdanturfTentTrainerText011Before[] = _("이건 널 위한 악몽이야");
static const u8 sVerdanturfTentTrainerText011PlayerLost[] = _("용서해줘...\n이건 꿈이야");
static const u8 sVerdanturfTentTrainerText011PlayerWon[] = _("이 꿈에서\n깨어나고 싶어");
static const u8 sVerdanturfTentTrainerText012Before[] = _("이 파티는 영원히 계속될 거야!");
static const u8 sVerdanturfTentTrainerText012PlayerLost[] = _("끝없는 음악이 줄줄 흐르고");
static const u8 sVerdanturfTentTrainerText012PlayerWon[] = _("당장 이 음악 멈추지 못해!");
static const u8 sVerdanturfTentTrainerText013Before[] = _("세계 영화 컬렉션을\n만들고 있어");
static const u8 sVerdanturfTentTrainerText013PlayerLost[] = _("마치 영화 같은 승리야!");
static const u8 sVerdanturfTentTrainerText013PlayerWon[] = _("영화에서도\n이렇게 지지는 않아...");
static const u8 sVerdanturfTentTrainerText014Before[] = _("나 쉬엄쉬엄할 거야");
static const u8 sVerdanturfTentTrainerText014PlayerLost[] = _("쉬엄쉬엄했는데도 이기네");
static const u8 sVerdanturfTentTrainerText014PlayerWon[] = _("너무 쉬엄쉬엄했나...");
static const u8 sVerdanturfTentTrainerText015Before[] = _("너 나보다 강해?");
static const u8 sVerdanturfTentTrainerText015PlayerLost[] = _("그치-!\n네가 나보다 강할 리 없지");
static const u8 sVerdanturfTentTrainerText015PlayerWon[] = _("심술궂기는!!");
static const u8 sVerdanturfTentTrainerText016Before[] = _("포켓몬은 쉬워!");
static const u8 sVerdanturfTentTrainerText016PlayerLost[] = _("이렇게나 쉬운데");
static const u8 sVerdanturfTentTrainerText016PlayerWon[] = _("아앙-!\n근데 왜 진 거지?");
static const u8 sVerdanturfTentTrainerText017Before[] = _("덤벼!\n뭐든 받아낼 테니까");
static const u8 sVerdanturfTentTrainerText017PlayerLost[] = _("이게 다야?\n아직 시작도 안 했다고");
static const u8 sVerdanturfTentTrainerText017PlayerWon[] = _("와우!!");
static const u8 sVerdanturfTentTrainerText018Before[] = _("프레셔 느끼고 있어?");
static const u8 sVerdanturfTentTrainerText018PlayerLost[] = _("약해 약해 너무 약해!");
static const u8 sVerdanturfTentTrainerText018PlayerWon[] = _("프레셔가 너무 강해!");
static const u8 sVerdanturfTentTrainerText019Before[] = _("발버둥 치는\n근사한 모습을 보여줘");
static const u8 sVerdanturfTentTrainerText019PlayerLost[] = _("정말 근사했어!");
static const u8 sVerdanturfTentTrainerText019PlayerWon[] = _("근사하진 않아도\n네가 이겼어");
static const u8 sVerdanturfTentTrainerText020Before[] = _("위험해!\n위험한 기운이 느껴져");
static const u8 sVerdanturfTentTrainerText020PlayerLost[] = _("내 거짓말을 믿은 거야!?");
static const u8 sVerdanturfTentTrainerText020PlayerWon[] = _("정말로 위험한 게 있었네...");
static const u8 sVerdanturfTentTrainerText021Before[] = _("배리어 전개!!");
static const u8 sVerdanturfTentTrainerText021PlayerLost[] = _("응?\n내가 이겼다고?");
static const u8 sVerdanturfTentTrainerText021PlayerWon[] = _("전혀 못 막을 줄\n알았다니까");
static const u8 sVerdanturfTentTrainerText022Before[] = _("날 이기면 공중날기를\n쓰겠다고 약속해");
static const u8 sVerdanturfTentTrainerText022PlayerLost[] = _("너무 약해...\n대신 공중날기라도 써봐");
static const u8 sVerdanturfTentTrainerText022PlayerWon[] = _("언젠가 공중날기를\n써줄 거라고 믿어!");
static const u8 sVerdanturfTentTrainerText023Before[] = _("해볼래... 배틀?");
static const u8 sVerdanturfTentTrainerText023PlayerLost[] = _("해볼래... 배틀 데이트?");
static const u8 sVerdanturfTentTrainerText023PlayerWon[] = _("해볼래... 배틀 미식가?");
static const u8 sVerdanturfTentTrainerText024Before[] = _("아침햇살이\n내게 괴력을 줘");
static const u8 sVerdanturfTentTrainerText024PlayerLost[] = _("하지만 난\n달의불빛도 좋아해");
static const u8 sVerdanturfTentTrainerText024PlayerWon[] = _("넌 지독한 모래바람 같아...");
static const u8 sVerdanturfTentTrainerText025Before[] = _("내 마이페이스에\n말려들게 해줄게");
static const u8 sVerdanturfTentTrainerText025PlayerLost[] = _("나 이겼어?\n깜짝이야");
static const u8 sVerdanturfTentTrainerText025PlayerWon[] = _("아아... 낮잠이 필요해");
static const u8 sVerdanturfTentTrainerText026Before[] = _("어떡하지-!\n손가락흔들기 어때?");
static const u8 sVerdanturfTentTrainerText026PlayerLost[] = _("어떡하지-!\n우유마시기 할까?");
static const u8 sVerdanturfTentTrainerText026PlayerWon[] = _("어떡하지-!\n잠자기 할까?");
static const u8 sVerdanturfTentTrainerText027Before[] = _("사람들은 내가\n노말타입이라고 말해");
static const u8 sVerdanturfTentTrainerText027PlayerLost[] = _("잘 봤어?\n난 노말하지 않다고");
static const u8 sVerdanturfTentTrainerText027PlayerWon[] = _("내가 소란피기를\n일으켜 볼까?");
static const u8 sVerdanturfTentTrainerText028Before[] = _("귀여운 TV 아이돌\n좋아해?");
static const u8 sVerdanturfTentTrainerText028PlayerLost[] = _("오늘 밤 방송!\n놓치지 말아줘");
static const u8 sVerdanturfTentTrainerText028PlayerWon[] = _("이러다가 방송에\n지각하겠어");
static const u8 sVerdanturfTentTrainerText029Before[] = _("내 멋지고\n귀여운 패션 어때?");
static const u8 sVerdanturfTentTrainerText029PlayerLost[] = _("널 이기기 위한\n내 헤롱헤롱바디");
static const u8 sVerdanturfTentTrainerText029PlayerWon[] = _("이 패션 센스를\n못 알아본다고?");

static const u8 *const sVerdanturfTentTrainerText[][3] =
{
    [VERDANTURF_TENT_TRAINER_BRENNA] = {sVerdanturfTentTrainerText000Before, sVerdanturfTentTrainerText000PlayerLost, sVerdanturfTentTrainerText000PlayerWon},
    [VERDANTURF_TENT_TRAINER_DILAN] = {sVerdanturfTentTrainerText001Before, sVerdanturfTentTrainerText001PlayerLost, sVerdanturfTentTrainerText001PlayerWon},
    [VERDANTURF_TENT_TRAINER_ELIANA] = {sVerdanturfTentTrainerText002Before, sVerdanturfTentTrainerText002PlayerLost, sVerdanturfTentTrainerText002PlayerWon},
    [VERDANTURF_TENT_TRAINER_MARKUS] = {sVerdanturfTentTrainerText003Before, sVerdanturfTentTrainerText003PlayerLost, sVerdanturfTentTrainerText003PlayerWon},
    [VERDANTURF_TENT_TRAINER_CAITLYN] = {sVerdanturfTentTrainerText004Before, sVerdanturfTentTrainerText004PlayerLost, sVerdanturfTentTrainerText004PlayerWon},
    [VERDANTURF_TENT_TRAINER_DESIREE] = {sVerdanturfTentTrainerText005Before, sVerdanturfTentTrainerText005PlayerLost, sVerdanturfTentTrainerText005PlayerWon},
    [VERDANTURF_TENT_TRAINER_RONALD] = {sVerdanturfTentTrainerText006Before, sVerdanturfTentTrainerText006PlayerLost, sVerdanturfTentTrainerText006PlayerWon},
    [VERDANTURF_TENT_TRAINER_ASHTEN] = {sVerdanturfTentTrainerText007Before, sVerdanturfTentTrainerText007PlayerLost, sVerdanturfTentTrainerText007PlayerWon},
    [VERDANTURF_TENT_TRAINER_GERARD] = {sVerdanturfTentTrainerText008Before, sVerdanturfTentTrainerText008PlayerLost, sVerdanturfTentTrainerText008PlayerWon},
    [VERDANTURF_TENT_TRAINER_BRADLY] = {sVerdanturfTentTrainerText009Before, sVerdanturfTentTrainerText009PlayerLost, sVerdanturfTentTrainerText009PlayerWon},
    [VERDANTURF_TENT_TRAINER_DENNIS] = {sVerdanturfTentTrainerText010Before, sVerdanturfTentTrainerText010PlayerLost, sVerdanturfTentTrainerText010PlayerWon},
    [VERDANTURF_TENT_TRAINER_PRESTIN] = {sVerdanturfTentTrainerText011Before, sVerdanturfTentTrainerText011PlayerLost, sVerdanturfTentTrainerText011PlayerWon},
    [VERDANTURF_TENT_TRAINER_ERNESTO] = {sVerdanturfTentTrainerText012Before, sVerdanturfTentTrainerText012PlayerLost, sVerdanturfTentTrainerText012PlayerWon},
    [VERDANTURF_TENT_TRAINER_NALA] = {sVerdanturfTentTrainerText013Before, sVerdanturfTentTrainerText013PlayerLost, sVerdanturfTentTrainerText013PlayerWon},
    [VERDANTURF_TENT_TRAINER_DARNELL] = {sVerdanturfTentTrainerText014Before, sVerdanturfTentTrainerText014PlayerLost, sVerdanturfTentTrainerText014PlayerWon},
    [VERDANTURF_TENT_TRAINER_ASHLYN] = {sVerdanturfTentTrainerText015Before, sVerdanturfTentTrainerText015PlayerLost, sVerdanturfTentTrainerText015PlayerWon},
    [VERDANTURF_TENT_TRAINER_ADDISON] = {sVerdanturfTentTrainerText016Before, sVerdanturfTentTrainerText016PlayerLost, sVerdanturfTentTrainerText016PlayerWon},
    [VERDANTURF_TENT_TRAINER_JUSTINE] = {sVerdanturfTentTrainerText017Before, sVerdanturfTentTrainerText017PlayerLost, sVerdanturfTentTrainerText017PlayerWon},
    [VERDANTURF_TENT_TRAINER_TYSON] = {sVerdanturfTentTrainerText018Before, sVerdanturfTentTrainerText018PlayerLost, sVerdanturfTentTrainerText018PlayerWon},
    [VERDANTURF_TENT_TRAINER_LAILA] = {sVerdanturfTentTrainerText019Before, sVerdanturfTentTrainerText019PlayerLost, sVerdanturfTentTrainerText019PlayerWon},
    [VERDANTURF_TENT_TRAINER_WAREN] = {sVerdanturfTentTrainerText020Before, sVerdanturfTentTrainerText020PlayerLost, sVerdanturfTentTrainerText020PlayerWon},
    [VERDANTURF_TENT_TRAINER_TOBIAS] = {sVerdanturfTentTrainerText021Before, sVerdanturfTentTrainerText021PlayerLost, sVerdanturfTentTrainerText021PlayerWon},
    [VERDANTURF_TENT_TRAINER_JOSIAH] = {sVerdanturfTentTrainerText022Before, sVerdanturfTentTrainerText022PlayerLost, sVerdanturfTentTrainerText022PlayerWon},
    [VERDANTURF_TENT_TRAINER_DION] = {sVerdanturfTentTrainerText023Before, sVerdanturfTentTrainerText023PlayerLost, sVerdanturfTentTrainerText023PlayerWon},
    [VERDANTURF_TENT_TRAINER_KENZIE] = {sVerdanturfTentTrainerText024Before, sVerdanturfTentTrainerText024PlayerLost, sVerdanturfTentTrainerText024PlayerWon},
    [VERDANTURF_TENT_TRAINER_LILLIAN] = {sVerdanturfTentTrainerText025Before, sVerdanturfTentTrainerText025PlayerLost, sVerdanturfTentTrainerText025PlayerWon},
    [VERDANTURF_TENT_TRAINER_LESLEY] = {sVerdanturfTentTrainerText026Before, sVerdanturfTentTrainerText026PlayerLost, sVerdanturfTentTrainerText026PlayerWon},
    [VERDANTURF_TENT_TRAINER_MARQUIS] = {sVerdanturfTentTrainerText027Before, sVerdanturfTentTrainerText027PlayerLost, sVerdanturfTentTrainerText027PlayerWon},
    [VERDANTURF_TENT_TRAINER_FREDDY] = {sVerdanturfTentTrainerText028Before, sVerdanturfTentTrainerText028PlayerLost, sVerdanturfTentTrainerText028PlayerWon},
    [VERDANTURF_TENT_TRAINER_CECILIA] = {sVerdanturfTentTrainerText029Before, sVerdanturfTentTrainerText029PlayerLost, sVerdanturfTentTrainerText029PlayerWon},
};

static const u8 sFallarborTentTrainerText000Before[] = _("매일 다이어트해야 해");
static const u8 sFallarborTentTrainerText000PlayerLost[] = _("달콤한 악몽에 깜짝 놀랐어");
static const u8 sFallarborTentTrainerText000PlayerWon[] = _("포기하면 지는 거야");
static const u8 sFallarborTentTrainerText001Before[] = _("돈은 아무리 있어도 부족해");
static const u8 sFallarborTentTrainerText001PlayerLost[] = _("이겼지만 돈은 더 필요해");
static const u8 sFallarborTentTrainerText001PlayerWon[] = _("자전거 살 돈이 필요해");
static const u8 sFallarborTentTrainerText002Before[] = _("내 배틀 방식은 좀 이상해");
static const u8 sFallarborTentTrainerText002PlayerLost[] = _("너 여기 오기엔 너무 약해");
static const u8 sFallarborTentTrainerText002PlayerWon[] = _("다음엔 쉬운 상대를 보내줘");
static const u8 sFallarborTentTrainerText003Before[] = _("내 손가락흔들기를 보고 잠들어라");
static const u8 sFallarborTentTrainerText003PlayerLost[] = _("그래!\n최면술은 완전 대단해");
static const u8 sFallarborTentTrainerText003PlayerWon[] = _("내 최면술이 안 통했어...");
static const u8 sFallarborTentTrainerText004Before[] = _("내가 이기면\n컬렉션용 포켓몬을 줘");
static const u8 sFallarborTentTrainerText004PlayerLost[] = _("네 포켓몬은\n모으기엔 너무 약해");
static const u8 sFallarborTentTrainerText004PlayerWon[] = _("네 포켓몬은\n정말 남다르네...");
static const u8 sFallarborTentTrainerText005Before[] = _("내 이름은 정말 수수께끼야");
static const u8 sFallarborTentTrainerText005PlayerLost[] = _("내 이름은 수수께끼로 남겨둘게");
static const u8 sFallarborTentTrainerText005PlayerWon[] = _("내 이름?\n나는 네 엄마다");
static const u8 sFallarborTentTrainerText006Before[] = _("나는 사상 최고의 영웅이야!");
static const u8 sFallarborTentTrainerText006PlayerLost[] = _("무슨 말인지 알겠지?");
static const u8 sFallarborTentTrainerText006PlayerWon[] = _("응?\n내 말이 맞았다고?");
static const u8 sFallarborTentTrainerText007Before[] = _("세계 엄청난힘\n짓밟기 콘테스트!!");
static const u8 sFallarborTentTrainerText007PlayerLost[] = _("내가 1등이야!!\n내 울부짖기를 들어라");
static const u8 sFallarborTentTrainerText007PlayerWon[] = _("항복! 네가 1등이야!");
static const u8 sFallarborTentTrainerText008Before[] = _("너 좋은 트레이너야?\n믿기지 않아");
static const u8 sFallarborTentTrainerText008PlayerLost[] = _("넌 꽤 만만한 트레이너잖아");
static const u8 sFallarborTentTrainerText008PlayerWon[] = _("너는 나한테 너무 벅차");
static const u8 sFallarborTentTrainerText009Before[] = _("내 포켓몬은\n비단처럼 매끈해!");
static const u8 sFallarborTentTrainerText009PlayerLost[] = _("내 매끈한 포켓몬이 최고야!");
static const u8 sFallarborTentTrainerText009PlayerWon[] = _("내 포켓몬이\n네 점착에 당했어");
static const u8 sFallarborTentTrainerText010Before[] = _("꿰뚫어보기...\n그것이 나의 힘");
static const u8 sFallarborTentTrainerText010PlayerLost[] = _("넌 둔감해서 못 하나 보지?\n꿰뚫어보기!");
static const u8 sFallarborTentTrainerText010PlayerWon[] = _("내 꿰뚫어보기는\n언제나 옳다고!");
static const u8 sFallarborTentTrainerText011Before[] = _("네 포켓몬으론\n나 못 이겨");
static const u8 sFallarborTentTrainerText011PlayerLost[] = _("대체 날 어떻게 이긴 거야?");
static const u8 sFallarborTentTrainerText011PlayerWon[] = _("그래 네가 다 해먹어라...");
static const u8 sFallarborTentTrainerText012Before[] = _("뭐 해먹고 살지?");
static const u8 sFallarborTentTrainerText012PlayerLost[] = _("렛츠 댄스!");
static const u8 sFallarborTentTrainerText012PlayerWon[] = _("포켓몬은 틀렸으니\n음악으로 먹고 살래...");
static const u8 sFallarborTentTrainerText013Before[] = _("네 진심을 보여줘");
static const u8 sFallarborTentTrainerText013PlayerLost[] = _("이래서 매일 공부하는 거야");
static const u8 sFallarborTentTrainerText013PlayerWon[] = _("이래 봬도 매일 공부한다고");
static const u8 sFallarborTentTrainerText014Before[] = _("내 힘이 보이니?");
static const u8 sFallarborTentTrainerText014PlayerLost[] = _("참 시시하네...\n잘 가");
static const u8 sFallarborTentTrainerText014PlayerWon[] = _("내가 약한 트레이너라고?");
static const u8 sFallarborTentTrainerText015Before[] = _("세상엔 거짓말\n같은 일들도 있지...");
static const u8 sFallarborTentTrainerText015PlayerLost[] = _("일요일 만화 같은 일이야");
static const u8 sFallarborTentTrainerText015PlayerWon[] = _("영화에서 나온 장면 같아");
static const u8 sFallarborTentTrainerText016Before[] = _("포켓몬은 최고의\n잠자기 선생님");
static const u8 sFallarborTentTrainerText016PlayerLost[] = _("슬기로움이 승리의 비결");
static const u8 sFallarborTentTrainerText016PlayerWon[] = _("위로 가는구나!\n아래에서 보자!");
static const u8 sFallarborTentTrainerText017Before[] = _("아하하 예스!\n러브러브 포켓몬 세계");
static const u8 sFallarborTentTrainerText017PlayerLost[] = _("나는 승리승리\n너는 패배패배");
static const u8 sFallarborTentTrainerText017PlayerWon[] = _("너 포켓몬 싫어해?");
static const u8 sFallarborTentTrainerText018Before[] = _("너...\n덤벼!");
static const u8 sFallarborTentTrainerText018PlayerLost[] = _("수행이 더 필요해");
static const u8 sFallarborTentTrainerText018PlayerWon[] = _("그만! 충분해...\n충분하다고...");
static const u8 sFallarborTentTrainerText019Before[] = _("너는 그거야");
static const u8 sFallarborTentTrainerText019PlayerLost[] = _("그게 뭐냐고?\n미지근한 재능");
static const u8 sFallarborTentTrainerText019PlayerWon[] = _("그게 뭐냐고?\n천재");
static const u8 sFallarborTentTrainerText020Before[] = _("내 잠재파워 신나!");
static const u8 sFallarborTentTrainerText020PlayerLost[] = _("네 잠재파워 하자 있어");
static const u8 sFallarborTentTrainerText020PlayerWon[] = _("아앙!\n나한테 흉내내기 쓰지 마");
static const u8 sFallarborTentTrainerText021Before[] = _("승리자가 될 거야!");
static const u8 sFallarborTentTrainerText021PlayerLost[] = _("승리자가 됐어!");
static const u8 sFallarborTentTrainerText021PlayerWon[] = _("패배란\n기묘한 꿈과도 같은 것");
static const u8 sFallarborTentTrainerText022Before[] = _("너 머리 회전이\n빠른 편은 아니구나?");
static const u8 sFallarborTentTrainerText022PlayerLost[] = _("미안!\n너보고 한 말은 아니었어");
static const u8 sFallarborTentTrainerText022PlayerWon[] = _("네가 떠나니 슬퍼졌어...");
static const u8 sFallarborTentTrainerText023Before[] = _("너 소란피기 하지 마!");
static const u8 sFallarborTentTrainerText023PlayerLost[] = _("이제 마음껏 소란피기 해");
static const u8 sFallarborTentTrainerText023PlayerWon[] = _("졌으니까 소란피기 할 거야!");
static const u8 sFallarborTentTrainerText024Before[] = _("파티 가고 싶다");
static const u8 sFallarborTentTrainerText024PlayerLost[] = _("유행하는 파티에 가서\n상쾌해지고 싶어");
static const u8 sFallarborTentTrainerText024PlayerWon[] = _("너 파티 싫어해?");
static const u8 sFallarborTentTrainerText025Before[] = _("내 PC 속에 비밀기지!");
static const u8 sFallarborTentTrainerText025PlayerLost[] = _("이겼으니\n네 PC를 살펴볼게");
static const u8 sFallarborTentTrainerText025PlayerWon[] = _("졌다고 내 PC를\n보여주진 않을 거야");
static const u8 sFallarborTentTrainerText026Before[] = _("딱히 예쁘진 않지만\n노력 중이야");
static const u8 sFallarborTentTrainerText026PlayerLost[] = _("제법이네\n그래도 다들 대단했어");
static const u8 sFallarborTentTrainerText026PlayerWon[] = _("제법인데 너!");
static const u8 sFallarborTentTrainerText027Before[] = _("너 정도는 편하게 이기지");
static const u8 sFallarborTentTrainerText027PlayerLost[] = _("막상 이기니까\n편하지만은 않네");
static const u8 sFallarborTentTrainerText027PlayerWon[] = _("잘 가 그리고 땡큐");
static const u8 sFallarborTentTrainerText028Before[] = _("라디오 또는 TV 삽니다");
static const u8 sFallarborTentTrainerText028PlayerLost[] = _("사서 네 패배를\n방송할 거야");
static const u8 sFallarborTentTrainerText028PlayerWon[] = _("뭐든 물건이 있어야 즐거워");
static const u8 sFallarborTentTrainerText029Before[] = _("백화점에 쇼핑 가고 싶어");
static const u8 sFallarborTentTrainerText029PlayerLost[] = _("혼자서 쇼핑 가긴 싫은데");
static const u8 sFallarborTentTrainerText029PlayerWon[] = _("같이 쇼핑하러 갈래?");

static const u8 *const sFallarborTentTrainerText[][3] =
{
    [FALLARBOR_TENT_TRAINER_AMBER] = {sFallarborTentTrainerText000Before, sFallarborTentTrainerText000PlayerLost, sFallarborTentTrainerText000PlayerWon},
    [FALLARBOR_TENT_TRAINER_JAVIER] = {sFallarborTentTrainerText001Before, sFallarborTentTrainerText001PlayerLost, sFallarborTentTrainerText001PlayerWon},
    [FALLARBOR_TENT_TRAINER_NATALIA] = {sFallarborTentTrainerText002Before, sFallarborTentTrainerText002PlayerLost, sFallarborTentTrainerText002PlayerWon},
    [FALLARBOR_TENT_TRAINER_TREVE] = {sFallarborTentTrainerText003Before, sFallarborTentTrainerText003PlayerLost, sFallarborTentTrainerText003PlayerWon},
    [FALLARBOR_TENT_TRAINER_ARIANNA] = {sFallarborTentTrainerText004Before, sFallarborTentTrainerText004PlayerLost, sFallarborTentTrainerText004PlayerWon},
    [FALLARBOR_TENT_TRAINER_JADYN] = {sFallarborTentTrainerText005Before, sFallarborTentTrainerText005PlayerLost, sFallarborTentTrainerText005PlayerWon},
    [FALLARBOR_TENT_TRAINER_GERARDO] = {sFallarborTentTrainerText006Before, sFallarborTentTrainerText006PlayerLost, sFallarborTentTrainerText006PlayerWon},
    [FALLARBOR_TENT_TRAINER_JONN] = {sFallarborTentTrainerText007Before, sFallarborTentTrainerText007PlayerLost, sFallarborTentTrainerText007PlayerWon},
    [FALLARBOR_TENT_TRAINER_ESTEBAN] = {sFallarborTentTrainerText008Before, sFallarborTentTrainerText008PlayerLost, sFallarborTentTrainerText008PlayerWon},
    [FALLARBOR_TENT_TRAINER_JAMESON] = {sFallarborTentTrainerText009Before, sFallarborTentTrainerText009PlayerLost, sFallarborTentTrainerText009PlayerWon},
    [FALLARBOR_TENT_TRAINER_ALANZO] = {sFallarborTentTrainerText010Before, sFallarborTentTrainerText010PlayerLost, sFallarborTentTrainerText010PlayerWon},
    [FALLARBOR_TENT_TRAINER_HOWARD] = {sFallarborTentTrainerText011Before, sFallarborTentTrainerText011PlayerLost, sFallarborTentTrainerText011PlayerWon},
    [FALLARBOR_TENT_TRAINER_CONRAD] = {sFallarborTentTrainerText012Before, sFallarborTentTrainerText012PlayerLost, sFallarborTentTrainerText012PlayerWon},
    [FALLARBOR_TENT_TRAINER_MAKENNA] = {sFallarborTentTrainerText013Before, sFallarborTentTrainerText013PlayerLost, sFallarborTentTrainerText013PlayerWon},
    [FALLARBOR_TENT_TRAINER_BRAYAN] = {sFallarborTentTrainerText014Before, sFallarborTentTrainerText014PlayerLost, sFallarborTentTrainerText014PlayerWon},
    [FALLARBOR_TENT_TRAINER_MARIANA] = {sFallarborTentTrainerText015Before, sFallarborTentTrainerText015PlayerLost, sFallarborTentTrainerText015PlayerWon},
    [FALLARBOR_TENT_TRAINER_SHELDON] = {sFallarborTentTrainerText016Before, sFallarborTentTrainerText016PlayerLost, sFallarborTentTrainerText016PlayerWon},
    [FALLARBOR_TENT_TRAINER_GIANNA] = {sFallarborTentTrainerText017Before, sFallarborTentTrainerText017PlayerLost, sFallarborTentTrainerText017PlayerWon},
    [FALLARBOR_TENT_TRAINER_YAHIR] = {sFallarborTentTrainerText018Before, sFallarborTentTrainerText018PlayerLost, sFallarborTentTrainerText018PlayerWon},
    [FALLARBOR_TENT_TRAINER_BRITNEY] = {sFallarborTentTrainerText019Before, sFallarborTentTrainerText019PlayerLost, sFallarborTentTrainerText019PlayerWon},
    [FALLARBOR_TENT_TRAINER_HECTER] = {sFallarborTentTrainerText020Before, sFallarborTentTrainerText020PlayerLost, sFallarborTentTrainerText020PlayerWon},
    [FALLARBOR_TENT_TRAINER_TANNOR] = {sFallarborTentTrainerText021Before, sFallarborTentTrainerText021PlayerLost, sFallarborTentTrainerText021PlayerWon},
    [FALLARBOR_TENT_TRAINER_BENJI] = {sFallarborTentTrainerText022Before, sFallarborTentTrainerText022PlayerLost, sFallarborTentTrainerText022PlayerWon},
    [FALLARBOR_TENT_TRAINER_RORY] = {sFallarborTentTrainerText023Before, sFallarborTentTrainerText023PlayerLost, sFallarborTentTrainerText023PlayerWon},
    [FALLARBOR_TENT_TRAINER_ELEANOR] = {sFallarborTentTrainerText024Before, sFallarborTentTrainerText024PlayerLost, sFallarborTentTrainerText024PlayerWon},
    [FALLARBOR_TENT_TRAINER_EVELYN] = {sFallarborTentTrainerText025Before, sFallarborTentTrainerText025PlayerLost, sFallarborTentTrainerText025PlayerWon},
    [FALLARBOR_TENT_TRAINER_ARIELLE] = {sFallarborTentTrainerText026Before, sFallarborTentTrainerText026PlayerLost, sFallarborTentTrainerText026PlayerWon},
    [FALLARBOR_TENT_TRAINER_CONNAR] = {sFallarborTentTrainerText027Before, sFallarborTentTrainerText027PlayerLost, sFallarborTentTrainerText027PlayerWon},
    [FALLARBOR_TENT_TRAINER_MAURICE] = {sFallarborTentTrainerText028Before, sFallarborTentTrainerText028PlayerLost, sFallarborTentTrainerText028PlayerWon},
    [FALLARBOR_TENT_TRAINER_KIANNA] = {sFallarborTentTrainerText029Before, sFallarborTentTrainerText029PlayerLost, sFallarborTentTrainerText029PlayerWon},
};

void FrontierTrainerStringToString(u16 trainerId, u8 whichText)
{
    const u8 *text = NULL;

    SetFacilityPtrsGetLevel();
    if (whichText > FRONTIER_PLAYER_WON_TEXT)
        whichText = FRONTIER_BEFORE_TEXT;

    if (gFacilityTrainers == gSlateportBattleTentTrainers)
    {
        if (trainerId < ARRAY_COUNT(sSlateportTentTrainerText))
            text = sSlateportTentTrainerText[trainerId][whichText];
    }
    else if (gFacilityTrainers == gVerdanturfBattleTentTrainers)
    {
        if (trainerId < ARRAY_COUNT(sVerdanturfTentTrainerText))
            text = sVerdanturfTentTrainerText[trainerId][whichText];
    }
    else if (gFacilityTrainers == gFallarborBattleTentTrainers)
    {
        if (trainerId < ARRAY_COUNT(sFallarborTentTrainerText))
            text = sFallarborTentTrainerText[trainerId][whichText];
    }
    else
    {
        if (trainerId < ARRAY_COUNT(sFrontierTrainerText))
            text = sFrontierTrainerText[trainerId][whichText];
    }

    if (text != NULL)
        StringCopy(gStringVar4, text);
    else
        gStringVar4[0] = EOS;
}

/* End generated frontier trainer text tables. */

static void GetOpponentIntroSpeech(void)
{
    u16 trainerId;
    SetFacilityPtrsGetLevel();

    if (gSpecialVar_0x8005)
        trainerId = gTrainerBattleOpponent_B;
    else
        trainerId = gTrainerBattleOpponent_A;

    if (trainerId == TRAINER_EREADER)
        FrontierSpeechToString(gSaveBlock2Ptr->frontier.ereaderTrainer.greeting);
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
        FrontierTrainerStringToString(trainerId, FRONTIER_BEFORE_TEXT);
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
        FrontierSpeechToString(gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].greeting);
    else
        BufferApprenticeChallengeText(trainerId - TRAINER_RECORD_MIXING_APPRENTICE);
}

static void HandleSpecialTrainerBattleEnd(void)
{
    s32 i;

    RecordedBattle_SaveBattleOutcome();
    switch (gBattleScripting.specialTrainerBattleType)
    {
    case SPECIAL_BATTLE_TOWER:
    case SPECIAL_BATTLE_DOME:
    case SPECIAL_BATTLE_PALACE:
    case SPECIAL_BATTLE_ARENA:
    case SPECIAL_BATTLE_FACTORY:
    case SPECIAL_BATTLE_PIKE_SINGLE:
    case SPECIAL_BATTLE_PIKE_DOUBLE:
    case SPECIAL_BATTLE_PYRAMID:
        if (gSaveBlock2Ptr->frontier.battlesCount < 0xFFFFFF)
        {
            gSaveBlock2Ptr->frontier.battlesCount++;
            if (gSaveBlock2Ptr->frontier.battlesCount % 20 == 0)
                UpdateGymLeaderRematch();
        }
        else
        {
            gSaveBlock2Ptr->frontier.battlesCount = 0xFFFFFF;
        }
        break;
    case SPECIAL_BATTLE_SECRET_BASE:
        for (i = 0; i < PARTY_SIZE; i++)
        {
            u16 itemBefore = GetMonData(&gSaveBlock1Ptr->playerParty[i], MON_DATA_HELD_ITEM);
            SetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM, &itemBefore);
        }
        break;
    case SPECIAL_BATTLE_EREADER:
        CopyEReaderTrainerFarewellMessage();
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

static void Task_StartBattleAfterTransition(u8 taskId)
{
    if (IsBattleTransitionDone() == TRUE)
    {
        gMain.savedCallback = HandleSpecialTrainerBattleEnd;
        SetMainCallback2(CB2_InitBattle);
        DestroyTask(taskId);
    }
}

void DoSpecialTrainerBattle(void)
{
    s32 i;

    gBattleScripting.specialTrainerBattleType = gSpecialVar_0x8004;
    switch (gSpecialVar_0x8004)
    {
    case SPECIAL_BATTLE_TOWER:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER;
        switch (VarGet(VAR_FRONTIER_BATTLE_MODE))
        {
        case FRONTIER_MODE_SINGLES:
            FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
            break;
        case FRONTIER_MODE_DOUBLES:
            FillFrontierTrainerParty(FRONTIER_DOUBLES_PARTY_SIZE);
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
            break;
        case FRONTIER_MODE_MULTIS:
            FillFrontierTrainersParties(FRONTIER_MULTI_PARTY_SIZE);
            gPartnerTrainerId = gSaveBlock2Ptr->frontier.trainerIds[17];
            FillPartnerParty(gPartnerTrainerId);
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE | BATTLE_TYPE_INGAME_PARTNER | BATTLE_TYPE_MULTI | BATTLE_TYPE_TWO_OPPONENTS;
            break;
        case FRONTIER_MODE_LINK_MULTIS:
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE | BATTLE_TYPE_LINK | BATTLE_TYPE_MULTI | BATTLE_TYPE_x800000;
            FillFrontierTrainersParties(FRONTIER_MULTI_PARTY_SIZE);
            break;
        }
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(0));
        break;
    case SPECIAL_BATTLE_SECRET_BASE:
        for (i = 0; i < PARTY_SIZE; i++)
        {
            u16 itemBefore = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);
            SetMonData(&gSaveBlock1Ptr->playerParty[i], MON_DATA_HELD_ITEM, &itemBefore);
        }
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(12));
        break;
    case SPECIAL_BATTLE_EREADER:
        ZeroEnemyPartyMons();
        for (i = 0; i < 3; i++)
            CreateBattleTowerMon(&gEnemyParty[i], &gSaveBlock2Ptr->frontier.ereaderTrainer.party[i]);
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_EREADER_TRAINER;
        gTrainerBattleOpponent_A = 0;
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(13));
        break;
    case SPECIAL_BATTLE_DOME:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOME;
        if (VarGet(VAR_FRONTIER_BATTLE_MODE) == FRONTIER_MODE_DOUBLES)
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
        if (gTrainerBattleOpponent_A == TRAINER_FRONTIER_BRAIN)
            FillFrontierTrainerParty(DOME_BATTLE_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        CreateTask_PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(3));
        break;
    case SPECIAL_BATTLE_PALACE:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_PALACE;
        if (VarGet(VAR_FRONTIER_BATTLE_MODE) == FRONTIER_MODE_DOUBLES)
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
        if (gSaveBlock2Ptr->frontier.lvlMode != FRONTIER_LVL_TENT)
            FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
        else
            FillTentTrainerParty(FRONTIER_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(4));
        break;
    case SPECIAL_BATTLE_ARENA:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_ARENA;
        if (gSaveBlock2Ptr->frontier.lvlMode != FRONTIER_LVL_TENT)
            FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
        else
            FillTentTrainerParty(FRONTIER_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(5));
        break;
    case SPECIAL_BATTLE_FACTORY:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_FACTORY;
        if (VarGet(VAR_FRONTIER_BATTLE_MODE) == FRONTIER_MODE_DOUBLES)
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
        FillFactoryTrainerParty();
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(6));
        break;
    case SPECIAL_BATTLE_PIKE_SINGLE:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER;
        FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(7));
        break;
    case SPECIAL_BATTLE_PYRAMID:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_PYRAMID;
        FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(10));
        break;
    case SPECIAL_BATTLE_PIKE_DOUBLE:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS;
        FillFrontierTrainersParties(1);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(7));
        break;
    case SPECIAL_BATTLE_STEVEN:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER;
        FillPartnerParty(TRAINER_STEVEN_PARTNER);
        gApproachingTrainerId = 0;
        BattleSetup_ConfigureTrainerBattle(MossdeepCity_SpaceCenter_2F_EventScript_MaxieTrainer + 1);
        gApproachingTrainerId = 1;
        BattleSetup_ConfigureTrainerBattle(MossdeepCity_SpaceCenter_2F_EventScript_TabithaTrainer + 1);
        gPartnerTrainerId = TRAINER_STEVEN_PARTNER;
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(B_TRANSITION_MAGMA);
        break;
    }
}

static void SaveCurrentWinStreak(void)
{
    u8 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u8 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
    u16 winStreak = GetCurrentBattleTowerWinStreak(lvlMode, battleMode);

    if (gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][lvlMode] < winStreak)
        gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][lvlMode] = winStreak;
}

static void SaveBattleTowerRecord(void)
{
    s32 i;
    u8 lvlMode, battleMode, class;
    struct EmeraldBattleTowerRecord *playerRecord = &gSaveBlock2Ptr->frontier.towerPlayer;

    ClearBattleTowerRecord(playerRecord);
    lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
    if (gSaveBlock2Ptr->playerGender != MALE)
    {
        class = gTowerFemaleFacilityClasses[(gSaveBlock2Ptr->playerTrainerId[0] +
                                       gSaveBlock2Ptr->playerTrainerId[1] +
                                       gSaveBlock2Ptr->playerTrainerId[2] +
                                       gSaveBlock2Ptr->playerTrainerId[3]) % ARRAY_COUNT(gTowerFemaleFacilityClasses)];
    }
    else
    {
        class = gTowerMaleFacilityClasses[(gSaveBlock2Ptr->playerTrainerId[0] +
                                     gSaveBlock2Ptr->playerTrainerId[1] +
                                     gSaveBlock2Ptr->playerTrainerId[2] +
                                     gSaveBlock2Ptr->playerTrainerId[3]) % ARRAY_COUNT(gTowerMaleFacilityClasses)];
    }
    playerRecord->lvlMode = lvlMode;
    playerRecord->facilityClass = class;
    CopyTrainerId(playerRecord->trainerId, gSaveBlock2Ptr->playerTrainerId);
    StringCopy7(playerRecord->name, gSaveBlock2Ptr->playerName);
    playerRecord->winStreak = GetCurrentBattleTowerWinStreak(lvlMode, battleMode);

    for (i = 0; i < EASY_CHAT_BATTLE_WORDS_COUNT; i++)
    {
        playerRecord->greeting[i] = gSaveBlock1Ptr->easyChatBattleStart[i];
        playerRecord->speechWon[i] = gSaveBlock1Ptr->easyChatBattleWon[i];
        playerRecord->speechLost[i] = gSaveBlock1Ptr->easyChatBattleLost[i];
    }

    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
    {
        if (gSaveBlock2Ptr->frontier.selectedPartyMons[i] != 0)
            ConvertPokemonToBattleTowerPokemon(&gPlayerParty[gSaveBlock2Ptr->frontier.selectedPartyMons[i] - 1], &playerRecord->party[i]);
    }

    playerRecord->language = gGameLanguage;
    CalcEmeraldBattleTowerChecksum(&gSaveBlock2Ptr->frontier.towerPlayer);
    SaveCurrentWinStreak();
}

static void SaveTowerChallenge(void)
{
    u16 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u16 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
    s32 challengeNum = (signed)(gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][lvlMode] / 7);

    if (gSpecialVar_0x8005 == 0 && (challengeNum > 1 || gSaveBlock2Ptr->frontier.curChallengeBattleNum != 0))
        SaveBattleTowerRecord();

    gSaveBlock2Ptr->frontier.challengeStatus = gSpecialVar_0x8005;
    VarSet(VAR_TEMP_0, 0);
    gSaveBlock2Ptr->frontier.challengePaused = TRUE;
    SaveGameFrontier();
}

static void BattleTowerNop1(void)
{

}

static void BattleTowerNop2(void)
{

}

static void GetApprenticeMultiPartnerParty(u16 trainerId)
{
    s32 i, count;
    u32 validSpecies[MULTI_PARTY_SIZE];
    u16 species1 = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL);
    u16 species2 = GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL);

    count = 0;
    for (i = 0; i < MULTI_PARTY_SIZE; i++)
    {
        u16 apprenticeSpecies = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].party[i].species;
        if (apprenticeSpecies != species1 && apprenticeSpecies != species2)
        {
            validSpecies[count] = i;
            count++;
        }
    }

    gFrontierTempParty[0] = validSpecies[Random() % count];
    do
    {
        gFrontierTempParty[1] = validSpecies[Random() % count];
    } while (gFrontierTempParty[0] == gFrontierTempParty[1]);
}

static void GetRecordMixFriendMultiPartnerParty(u16 trainerId)
{
    s32 i, count;
    u32 validSpecies[3];
    u32 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u16 species1 = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL);
    u16 species2 = GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL);

    count = 0;
    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
    {
        if (gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[i].species != species1
            && gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[i].species != species2
            && gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[i].level <= GetFrontierEnemyMonLevel(lvlMode)
            && gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[i].species != 0)
        {
            validSpecies[count] = i;
            count++;
        }
    }

    gFrontierTempParty[2] = validSpecies[Random() % count];
    do
    {
        gFrontierTempParty[3] = validSpecies[Random() % count];
    } while (gFrontierTempParty[2] == gFrontierTempParty[3]);
}

static void LoadMultiPartnerCandidatesData(void)
{
    s32 i, j, k;
    u32 spArray[5];
    s32 r10;
    u16 trainerId;
    u16 monId;
    u32 lvlMode, battleMode;
    s32 challengeNum;
    u32 species1, species2;
    u32 level;
    struct ObjectEventTemplate *objEventTemplates;

    objEventTemplates = gSaveBlock1Ptr->objectEventTemplates;
    lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
    challengeNum = gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][lvlMode] / 7;
    species1 = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL);
    species2 = GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL);
    level = SetFacilityPtrsGetLevel();

    j = 0;
    do
    {
        do
        {
            trainerId = GetRandomScaledFrontierTrainerId(challengeNum, 0);
            for (i = 0; i < j; i++)
            {
                if (gSaveBlock2Ptr->frontier.trainerIds[i] == trainerId)
                    break;
                if (gFacilityTrainers[gSaveBlock2Ptr->frontier.trainerIds[i]].facilityClass == gFacilityTrainers[trainerId].facilityClass)
                    break;
            }
        } while (i != j);
        gSaveBlock2Ptr->frontier.trainerIds[j] = trainerId;
        j++;
    } while (j < 6);

    r10 = 8;
    for (i = 0; i < 6; i++)
    {
        trainerId = gSaveBlock2Ptr->frontier.trainerIds[i];
        objEventTemplates[i + 1].graphicsId = GetBattleFacilityTrainerGfxId(trainerId);
        for (j = 0; j < 2; j++)
        {
            while (1)
            {
                monId = GetRandomFrontierMonFromSet(trainerId);
                if (j % 2 != 0 && gFacilityTrainerMons[gSaveBlock2Ptr->frontier.trainerIds[r10 - 1]].itemTableId == gFacilityTrainerMons[monId].itemTableId)
                    continue;

                for (k = 8; k < r10; k++)
                {
                    if (gFacilityTrainerMons[gSaveBlock2Ptr->frontier.trainerIds[k]].species == gFacilityTrainerMons[monId].species)
                        break;
                    if (species1 == gFacilityTrainerMons[monId].species)
                        break;
                    if (species2 == gFacilityTrainerMons[monId].species)
                        break;
                }
                if (k == r10)
                    break;
            }

            gSaveBlock2Ptr->frontier.trainerIds[r10] = monId;
            r10++;
        }
    }

    r10 = 0;
    ValidateApprenticesChecksums();
    for (i = 0; i < APPRENTICE_COUNT; i++)
    {
        if (gSaveBlock2Ptr->apprentices[i].lvlMode != 0
            && sApprenticeChallengeThreshold[gSaveBlock2Ptr->apprentices[i].numQuestions] / 7 <= challengeNum
            && gSaveBlock2Ptr->apprentices[i].lvlMode - 1 == lvlMode)
        {
            k = 0;
            for (j = 0; j < MULTI_PARTY_SIZE; j++)
            {
                if (species1 != gSaveBlock2Ptr->apprentices[i].party[j].species
                    && species2 != gSaveBlock2Ptr->apprentices[i].party[j].species)
                {
                    k++;
                }
            }
            if (k > 2)
            {
                spArray[r10] = i + TRAINER_RECORD_MIXING_APPRENTICE;
                r10++;
            }
        }
    }
    if (r10 != 0)
    {
        gSaveBlock2Ptr->frontier.trainerIds[6] = spArray[Random() % r10];
        objEventTemplates[7].graphicsId = GetBattleFacilityTrainerGfxId(gSaveBlock2Ptr->frontier.trainerIds[6]);
        FlagClear(FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1);
        GetApprenticeMultiPartnerParty(gSaveBlock2Ptr->frontier.trainerIds[6]);
    }

    r10 = 0;
    for (i = 0; i < BATTLE_TOWER_RECORD_COUNT; i++)
    {
        u32 *record = (u32*)(&gSaveBlock2Ptr->frontier.towerRecords[i]);
        u32 recordHasData = 0;
        u32 checksum = 0;
        for (j = 0; j < (sizeof(struct EmeraldBattleTowerRecord) - 4) / 4; j++) // - 4, because of the last field being the checksum itself.
        {
            recordHasData |= record[j];
            checksum += record[j];
        }

        if (gSaveBlock2Ptr->frontier.towerRecords[i].winStreak / 7 <= challengeNum
            && gSaveBlock2Ptr->frontier.towerRecords[i].lvlMode == lvlMode
            && recordHasData
            && gSaveBlock2Ptr->frontier.towerRecords[i].checksum == checksum)
        {
            k = 0;
            for (j = 0; j < MAX_FRONTIER_PARTY_SIZE; j++)
            {
                if (species1 != gSaveBlock2Ptr->frontier.towerRecords[i].party[j].species
                    && species2 != gSaveBlock2Ptr->frontier.towerRecords[i].party[j].species
                    && gSaveBlock2Ptr->frontier.towerRecords[i].party[j].level <= GetFrontierEnemyMonLevel(lvlMode)
                    && gSaveBlock2Ptr->frontier.towerRecords[i].party[j].species != 0)
                {
                    k++;
                }
            }
            if (k > 1)
            {
                spArray[r10] = i + TRAINER_RECORD_MIXING_FRIEND;
                r10++;
            }
        }
    }
    if (r10 != 0)
    {
        gSaveBlock2Ptr->frontier.trainerIds[7] = spArray[Random() % r10];
        objEventTemplates[8].graphicsId = GetBattleFacilityTrainerGfxId(gSaveBlock2Ptr->frontier.trainerIds[7]);
        FlagClear(FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2);
        GetRecordMixFriendMultiPartnerParty(gSaveBlock2Ptr->frontier.trainerIds[7]);
    }
}

static void GetPotentialPartnerMoveAndSpecies(u16 trainerId, u16 monId)
{
    u16 move = 0;
    u16 species = 0;
    SetFacilityPtrsGetLevel();

    if (trainerId != TRAINER_EREADER)
    {
        if (trainerId < FRONTIER_TRAINERS_COUNT)
        {
            move = gFacilityTrainerMons[monId].moves[0];
            species = gFacilityTrainerMons[monId].species;
        }
        else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
        {
            move = gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[gFrontierTempParty[gSpecialVar_0x8005 + 1]].moves[0];
            species = gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[gFrontierTempParty[gSpecialVar_0x8005 + 1]].species;
        }
        else
        {
            s32 i;

            move = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].party[gFrontierTempParty[gSpecialVar_0x8005 - 1]].moves[0];
            species = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].party[gFrontierTempParty[gSpecialVar_0x8005 - 1]].species;
            for (i = 0; i < PLAYER_NAME_LENGTH; i++)
                gStringVar3[i] = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].playerName[i];
            gStringVar3[i] = EOS;
            ConvertInternationalString(gStringVar3, gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].language);
        }
    }

    StringCopy(gStringVar1, gMoveNames[move]);
    StringCopy(gStringVar2, gSpeciesNames[species]);
}

// For multi battles in the Battle Tower, the player may choose a partner by talking to them
// These partners can be an NPC or a former/record-mixed Apprentice
// When talked to, their response consists of:
// PARTNER_MSGID_INTRO - A greeting
// PARTNER_MSGID_MON1 - Naming one pokemon on their team, and a move it has
// PARTNER_MSGID_MON2_ASK - Naming a second pokemon on their team, a move it has, and asking if they'd like to be their partner
// PARTNER_MSGID_ACCEPT - If the player agrees to be their partner
// PARTNER_MSGID_REJECT - If the player declines to be their partner
static void ShowPartnerCandidateMessage(void)
{
    s32 i, j, partnerId;
    s32 monId;
    s32 level = SetFacilityPtrsGetLevel();
    u16 winStreak = GetCurrentFacilityWinStreak();
    s32 challengeNum = winStreak / 7;
    s32 k = gSpecialVar_LastTalked - 2;
    s32 trainerId = gSaveBlock2Ptr->frontier.trainerIds[k];

    for (partnerId = 0; partnerId < ARRAY_COUNT(sPartnerTrainerTextTables); partnerId++)
    {
        if (sPartnerTrainerTextTables[partnerId].facilityClass == GetFrontierTrainerFacilityClass(trainerId))
            break;
    }

    switch (gSpecialVar_0x8005)
    {
    case PARTNER_MSGID_INTRO:
        if (trainerId == TRAINER_EREADER)
            return;
        if (trainerId < FRONTIER_TRAINERS_COUNT)
        {
            GetFrontierTrainerName(gStringVar1, trainerId);
        }
        else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
        {
            GetFrontierTrainerName(gStringVar1, trainerId);
        }
        else
        {
            s32 i;
            for (i = 0; i < PLAYER_NAME_LENGTH; i++)
                gStringVar1[i] = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].playerName[i];
            gStringVar1[i] = EOS;
            ConvertInternationalString(gStringVar1, gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].language);
            ConvertIntToDecimalStringN(gStringVar2, gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].number, STR_CONV_MODE_LEFT_ALIGN, 3);
            GetFrontierTrainerName(gStringVar3, trainerId);
        }
        break;
    case PARTNER_MSGID_MON1:
        monId = gSaveBlock2Ptr->frontier.trainerIds[8 + k * 2];
        GetPotentialPartnerMoveAndSpecies(trainerId, monId);
        break;
    case PARTNER_MSGID_MON2_ASK:
        monId = gSaveBlock2Ptr->frontier.trainerIds[9 + k * 2];
        GetPotentialPartnerMoveAndSpecies(trainerId, monId);
        break;
    case PARTNER_MSGID_ACCEPT:
        gPartnerTrainerId = trainerId;
        if (trainerId < FRONTIER_TRAINERS_COUNT)
        {
            gSaveBlock2Ptr->frontier.trainerIds[18] = gSaveBlock2Ptr->frontier.trainerIds[8 + k * 2];
            gSaveBlock2Ptr->frontier.trainerIds[19] = gSaveBlock2Ptr->frontier.trainerIds[9 + k * 2];
        }
        else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
        {
            gSaveBlock2Ptr->frontier.trainerIds[18] = gFrontierTempParty[2];
            gSaveBlock2Ptr->frontier.trainerIds[19] = gFrontierTempParty[3];
        }
        else
        {
            gSaveBlock2Ptr->frontier.trainerIds[18] = gFrontierTempParty[0];
            gSaveBlock2Ptr->frontier.trainerIds[19] = gFrontierTempParty[1];
        }
        for (k = 0; k < 14; k++)
        {
            while (1)
            {
                i = GetRandomScaledFrontierTrainerId(challengeNum, k / 2);
                if (gPartnerTrainerId == i)
                    continue;

                for (j = 0; j < k; j++)
                {
                    if (gSaveBlock2Ptr->frontier.trainerIds[j] == i)
                        break;
                }
                if (j == k)
                    break;
            }
            gSaveBlock2Ptr->frontier.trainerIds[k] = i;
        }
        gSaveBlock2Ptr->frontier.trainerIds[17] = trainerId;
        break;
    case PARTNER_MSGID_REJECT:
        break;
    }

    if (trainerId == TRAINER_EREADER)
        return;

    // First check is redundant, only needs to make sure it's not an Apprentice
    if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        ShowFieldMessage(sPartnerTrainerTextTables[partnerId].strings[gSpecialVar_0x8005]);
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        ShowFieldMessage(sPartnerTrainerTextTables[partnerId].strings[gSpecialVar_0x8005]);
    }
    // Trainer is a former/record-mixed Apprentice, do Apprentice message
    else
    {
        u8 apprenticeId = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id;
        ShowFieldMessage(sPartnerApprenticeTextTables[apprenticeId][gSpecialVar_0x8005]);
    }
}

static void LoadLinkMultiOpponentsData(void)
{
    s32 challengeNum;
    s32 i, j;
    s32 trainerId = 0;
    u32 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
    u32 battleNum = gSaveBlock2Ptr->frontier.curChallengeBattleNum;
    GetMultiplayerId(); // Yet another pointless function call.

    switch (gSpecialVar_Result)
    {
    case 0:
        if (battleMode == FRONTIER_MODE_LINK_MULTIS)
        {
            challengeNum = gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][lvlMode] / 7;
            if (IsLinkTaskFinished())
            {
                SendBlock(bitmask_all_link_players_but_self(), &challengeNum, sizeof(challengeNum));
                gSpecialVar_Result = 1;
            }
        }
        else
        {
            gSpecialVar_Result = 6;
        }
        break;
    case 1:
        if ((GetBlockReceivedStatus() & 3) == 3)
        {
            ResetBlockReceivedFlags();
            if (gBlockRecvBuffer[0][0] > gBlockRecvBuffer[1][0])
                challengeNum = gBlockRecvBuffer[0][0];
            else
                challengeNum = gBlockRecvBuffer[1][0];
            for (i = 0; i < 14; i++)
            {
                do
                {
                    trainerId = GetRandomScaledFrontierTrainerId(challengeNum, i / 2);
                    for (j = 0; j < i; j++)
                    {
                        if (gSaveBlock2Ptr->frontier.trainerIds[j] == trainerId)
                            break;
                    }
                } while (i != j);
                if (i == j) // This condition is always true, because of the loop above.
                    gSaveBlock2Ptr->frontier.trainerIds[i] = trainerId;
            }
            gSpecialVar_Result = 2;
        }
        break;
    case 2:
        if (IsLinkTaskFinished())
        {
            SendBlock(bitmask_all_link_players_but_self(), &gSaveBlock2Ptr->frontier.trainerIds, sizeof(gSaveBlock2Ptr->frontier.trainerIds));
            gSpecialVar_Result = 3;
        }
        break;
    case 3:
        if ((GetBlockReceivedStatus() & 3) == 3)
        {
            ResetBlockReceivedFlags();
            memcpy(&gSaveBlock2Ptr->frontier.trainerIds, gBlockRecvBuffer, sizeof(gSaveBlock2Ptr->frontier.trainerIds));
            gTrainerBattleOpponent_A = gSaveBlock2Ptr->frontier.trainerIds[battleNum * 2];
            gTrainerBattleOpponent_B = gSaveBlock2Ptr->frontier.trainerIds[battleNum * 2 + 1];
            SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
            SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_B, 1);
            if (gReceivedRemoteLinkPlayers != 0 && gWirelessCommType == 0)
                gSpecialVar_Result = 4;
            else
                gSpecialVar_Result = 6;
        }
        break;
    case 4:
        SetCloseLinkCallback();
        gSpecialVar_Result = 5;
        break;
    case 5:
        if (gReceivedRemoteLinkPlayers == 0)
        {
            gSpecialVar_Result = 6;
        }
        break;
    case 6:
        return;
    }
}

static void TowerTryCloseLink(void)
{
    if (gWirelessCommType != 0)
        SetCloseLinkCallback();
}

static void SetMultiPartnerGfx(void)
{
    // 0xF below means use VAR_OBJ_GFX_ID_E
    SetBattleFacilityTrainerGfxId(gSaveBlock2Ptr->frontier.trainerIds[17], 0xF); 
}

static void SetTowerInterviewData(void)
{
    s32 i;
    u8 text[32];

    if (VarGet(VAR_FRONTIER_BATTLE_MODE) != FRONTIER_MODE_SINGLES)
        return;

    GetFrontierTrainerName(text, gTrainerBattleOpponent_A);
    StripExtCtrlCodes(text);
    StringCopy(gSaveBlock2Ptr->frontier.towerInterview.opponentName, text);
    GetBattleTowerTrainerLanguage(&gSaveBlock2Ptr->frontier.towerInterview.opponentLanguage, gTrainerBattleOpponent_A);
    gSaveBlock2Ptr->frontier.towerInterview.opponentSpecies = GetMonData(&gEnemyParty[gBattlerPartyIndexes[1]], MON_DATA_SPECIES, NULL);
    gSaveBlock2Ptr->frontier.towerInterview.playerSpecies = GetMonData(&gPlayerParty[gBattlerPartyIndexes[0]], MON_DATA_SPECIES, NULL);
    for (i = 0; i < POKEMON_NAME_LENGTH + 1; i++)
        gSaveBlock2Ptr->frontier.towerInterview.opponentMonNickname[i] = gBattleMons[0].nickname[i];
    gSaveBlock2Ptr->frontier.towerBattleOutcome = gBattleOutcome;
}

static void ValidateBattleTowerRecordChecksums(void)
{
    s32 i, j;
    u32 *record = (u32*)(&gSaveBlock2Ptr->frontier.towerPlayer);
    u32 checksum = 0;

    for (j = 0; j < (sizeof(struct EmeraldBattleTowerRecord) - 4) / 4; j++) // - 4, because of the last field being the checksum itself.
    {
        checksum += record[j];
    }
    if (gSaveBlock2Ptr->frontier.towerPlayer.checksum != checksum)
        ClearBattleTowerRecord(&gSaveBlock2Ptr->frontier.towerPlayer);

    for (i = 0; i < BATTLE_TOWER_RECORD_COUNT; i++)
    {
        record = (u32*)(&gSaveBlock2Ptr->frontier.towerRecords[i]);
        checksum = 0;
        for (j = 0; j < (sizeof(struct EmeraldBattleTowerRecord) - 4) / 4; j++) // - 4, because of the last field being the checksum itself.
        {
            checksum += record[j];
        }
        if (gSaveBlock2Ptr->frontier.towerRecords[i].checksum != checksum)
            ClearBattleTowerRecord(&gSaveBlock2Ptr->frontier.towerRecords[i]);
    }
}

void CalcEmeraldBattleTowerChecksum(struct EmeraldBattleTowerRecord *record)
{
    u32 i;

    record->checksum = 0;
    for (i = 0; i < (sizeof(struct EmeraldBattleTowerRecord) - 4) / 4; i++) // - 4, because of the last field being the checksum itself.
        record->checksum += ((u32 *)record)[i];
}

void CalcRubyBattleTowerChecksum(struct RSBattleTowerRecord *record)
{
    u32 i;

    record->checksum = 0;
    for (i = 0; i < (sizeof(struct RSBattleTowerRecord) - 4) / 4; i++) // - 4, because of the last field being the checksum itself.
        record->checksum += ((u32 *)record)[i];
}

static void ClearBattleTowerRecord(struct EmeraldBattleTowerRecord *record)
{
    u32 i;

    for (i = 0; i < sizeof(struct EmeraldBattleTowerRecord) / 4; i++)
        ((u32 *)record)[i] = 0;
}

u16 GetCurrentBattleTowerWinStreak(u8 lvlMode, u8 battleMode)
{
    u16 winStreak = gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][lvlMode];

    if (winStreak > 9999)
        return 9999;
    else
        return winStreak;
}

static u8 GetMonCountForBattleMode(u8 battleMode)
{
    u8 partySizes[ARRAY_COUNT(sBattleTowerPartySizes)];
    memcpy(partySizes, sBattleTowerPartySizes, sizeof(sBattleTowerPartySizes));

    if (battleMode < ARRAY_COUNT(sBattleTowerPartySizes))
        return partySizes[battleMode];
    else
        return FRONTIER_PARTY_SIZE;
}

struct RibbonCounter
{
    u8 partyIndex;
    u8 count;
};

static void AwardBattleTowerRibbons(void)
{
    s32 i;
    u32 partyIndex;
    struct RibbonCounter ribbons[3]; // BUG: 4 Pokemon can receive ribbons in a double battle mode.
    u8 ribbonType = 0;
    u8 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u8 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
    u8 monCount = GetMonCountForBattleMode(battleMode);

    if (lvlMode != FRONTIER_LVL_50)
        ribbonType = MON_DATA_VICTORY_RIBBON;
    else
        ribbonType = MON_DATA_WINNING_RIBBON;

    gSpecialVar_Result = FALSE;

    if (GetCurrentBattleTowerWinStreak(lvlMode, battleMode) > 55)
    {
        for (i = 0; i < monCount; i++)
        {
            partyIndex = gSaveBlock2Ptr->frontier.selectedPartyMons[i] - 1;
            ribbons[i].partyIndex = partyIndex;
            ribbons[i].count = 0;
            if (!GetMonData(&gSaveBlock1Ptr->playerParty[partyIndex], ribbonType))
            {
                gSpecialVar_Result = TRUE;
                SetMonData(&gSaveBlock1Ptr->playerParty[partyIndex], ribbonType, &gSpecialVar_Result);
                ribbons[i].count = GetRibbonCount(&gSaveBlock1Ptr->playerParty[partyIndex]);
            }
        }
    }

    if (gSpecialVar_Result)
    {
        IncrementGameStat(GAME_STAT_RECEIVED_RIBBONS);
        for (i = 1; i < monCount; i++)
        {
            if (ribbons[i].count > ribbons[0].count)
            {
                struct RibbonCounter prevBest = ribbons[0];
                ribbons[0] = ribbons[i];
                ribbons[i] = prevBest;
            }
        }
        if (ribbons[0].count > NUM_CUTIES_RIBBONS)
        {
            TryPutSpotTheCutiesOnAir(&gSaveBlock1Ptr->playerParty[ribbons[0].partyIndex], ribbonType);
        }
    }
}

// This is a leftover debugging function that is used to populate the E-Reader
// trainer with the player's current data.
static void FillEReaderTrainerWithPlayerData(void)
{
    struct BattleTowerEReaderTrainer *ereaderTrainer = &gSaveBlock2Ptr->frontier.ereaderTrainer;
    s32 i, j;

    if (gSaveBlock2Ptr->playerGender != MALE)
    {
        ereaderTrainer->facilityClass = gTowerFemaleFacilityClasses[(gSaveBlock2Ptr->playerTrainerId[0] + gSaveBlock2Ptr->playerTrainerId[1]
                                                        + gSaveBlock2Ptr->playerTrainerId[2] + gSaveBlock2Ptr->playerTrainerId[3]) % ARRAY_COUNT(gTowerFemaleFacilityClasses)];
    }
    else
    {
        ereaderTrainer->facilityClass = gTowerMaleFacilityClasses[(gSaveBlock2Ptr->playerTrainerId[0] + gSaveBlock2Ptr->playerTrainerId[1]
                                                        + gSaveBlock2Ptr->playerTrainerId[2] + gSaveBlock2Ptr->playerTrainerId[3]) % ARRAY_COUNT(gTowerMaleFacilityClasses)];
    }

    CopyTrainerId(ereaderTrainer->trainerId, gSaveBlock2Ptr->playerTrainerId);
    StringCopy7(ereaderTrainer->name, gSaveBlock2Ptr->playerName);

    ereaderTrainer->winStreak = 1;

    j = 7;
    for (i = 0; i < 6; i++)
    {
        ereaderTrainer->greeting[i] = gSaveBlock1Ptr->easyChatBattleStart[i];
        ereaderTrainer->farewellPlayerLost[i] = j;
        ereaderTrainer->farewellPlayerWon[i] = j + 6;
        j++;
    }

    for (i = 0; i < 3; i++)
        ConvertPokemonToBattleTowerPokemon(&gPlayerParty[i], &ereaderTrainer->party[i]);

    SetEReaderTrainerChecksum(ereaderTrainer);
}

u8 GetEreaderTrainerFrontSpriteId(void)
{
    return gFacilityClassToPicIndex[gSaveBlock2Ptr->frontier.ereaderTrainer.facilityClass];
}

u8 GetEreaderTrainerClassId(void)
{
    return gFacilityClassToTrainerClass[gSaveBlock2Ptr->frontier.ereaderTrainer.facilityClass];
}

void GetEreaderTrainerName(u8 *dst)
{
    s32 i;

    for (i = 0; i < 5; i++)
        dst[i] = gSaveBlock2Ptr->frontier.ereaderTrainer.name[i];

    dst[i] = EOS;
}

// Checks if the saved E-Reader trainer is valid.
void ValidateEReaderTrainer(void)
{
    u32 i;
    u32 checksum;
    struct BattleTowerEReaderTrainer *ereaderTrainer;

    gSpecialVar_Result = FALSE;
    ereaderTrainer = &gSaveBlock2Ptr->frontier.ereaderTrainer;

    checksum = 0;
    for (i = 0; i < (sizeof(struct BattleTowerEReaderTrainer) - 4) / 4; i++) // - 4, because of the last field being the checksum itself.
        checksum |= ((u32 *)ereaderTrainer)[i];

    if (checksum == 0)
    {
        gSpecialVar_Result = TRUE;
        return;
    }

    checksum = 0;
    for (i = 0; i < (sizeof(struct BattleTowerEReaderTrainer) - 4) / 4; i++) // - 4, because of the last field being the checksum itself.
        checksum += ((u32 *)ereaderTrainer)[i];

    if (gSaveBlock2Ptr->frontier.ereaderTrainer.checksum != checksum)
    {
        ClearEReaderTrainer(&gSaveBlock2Ptr->frontier.ereaderTrainer);
        gSpecialVar_Result = TRUE;
    }
}

static void SetEReaderTrainerChecksum(struct BattleTowerEReaderTrainer *ereaderTrainer)
{
    s32 i;

    ereaderTrainer->checksum = 0;
    for (i = 0; i < (sizeof(struct BattleTowerEReaderTrainer) - 4) / 4; i++) // - 4, because of the last field being the checksum itself.
        ereaderTrainer->checksum += ((u32 *)ereaderTrainer)[i];
}

void ClearEReaderTrainer(struct BattleTowerEReaderTrainer *ereaderTrainer)
{
    u32 i;

    for (i = 0; i < (sizeof(struct BattleTowerEReaderTrainer)) / 4; i++)
        ((u32 *)ereaderTrainer)[i] = 0;
}

void CopyEReaderTrainerGreeting(void)
{
    FrontierSpeechToString(gSaveBlock2Ptr->frontier.ereaderTrainer.greeting);
}

static void CopyEReaderTrainerFarewellMessage(void)
{
    if (gBattleOutcome == B_OUTCOME_DREW)
        gStringVar4[0] = EOS;
    else if (gBattleOutcome == B_OUTCOME_WON)
        FrontierSpeechToString(gSaveBlock2Ptr->frontier.ereaderTrainer.farewellPlayerWon);
    else
        FrontierSpeechToString(gSaveBlock2Ptr->frontier.ereaderTrainer.farewellPlayerLost);
}

void TryHideBattleTowerReporter(void)
{
    if (gSaveBlock2Ptr->frontier.challengeStatus == CHALLENGE_STATUS_SAVING)
        HideBattleTowerReporter();
    if (FlagGet(FLAG_CANCEL_BATTLE_ROOM_CHALLENGE) == TRUE)
    {
        HideBattleTowerReporter();
        FlagClear(FLAG_CANCEL_BATTLE_ROOM_CHALLENGE);
    }
}

#define STEVEN_OTID 61226

static void FillPartnerParty(u16 trainerId)
{
    s32 i, j;
    u32 ivs, level;
    u32 friendship;
    u16 monId;
    u32 otID;
    u8 trainerName[PLAYER_NAME_LENGTH + 1];
    SetFacilityPtrsGetLevel();

    if (trainerId == TRAINER_STEVEN_PARTNER)
    {
        for (i = 0; i < MULTI_PARTY_SIZE; i++)
        {
            do
            {
                j = Random32();
            } while (IsShinyOtIdPersonality(STEVEN_OTID, j) || sStevenMons[i].nature != GetNatureFromPersonality(j));
            CreateMon(&gPlayerParty[MULTI_PARTY_SIZE + i],
                      sStevenMons[i].species,
                      sStevenMons[i].level,
                      sStevenMons[i].fixedIV,
                      TRUE, 
                      #ifdef BUGFIX
                      j,
                      #else
                      i, // BUG: personality was stored in the 'j' variable. As a result, Steven's pokemon do not have the intended natures.
                      #endif
                      OT_ID_PRESET, STEVEN_OTID);
            for (j = 0; j < PARTY_SIZE; j++)
                SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_HP_EV + j, &sStevenMons[i].evs[j]);
            for (j = 0; j < MAX_MON_MOVES; j++)
                SetMonMoveSlot(&gPlayerParty[MULTI_PARTY_SIZE + i], sStevenMons[i].moves[j], j);
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_OT_NAME, gTrainers[TRAINER_STEVEN].trainerName);
            j = MALE;
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_OT_GENDER, &j);
            CalculateMonStats(&gPlayerParty[MULTI_PARTY_SIZE + i]);
        }
    }
    else if (trainerId == TRAINER_EREADER)
    {
        // Scrapped, lol.
        trainerName[0] = gGameLanguage;
    }
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        level = SetFacilityPtrsGetLevel();
        ivs = GetFrontierTrainerFixedIvs(trainerId);
        otID = Random32();
        for (i = 0; i < FRONTIER_MULTI_PARTY_SIZE; i++)
        {
            monId = gSaveBlock2Ptr->frontier.trainerIds[i + 18];
            CreateMonWithEVSpreadNatureOTID(&gPlayerParty[MULTI_PARTY_SIZE + i],
                                                 gFacilityTrainerMons[monId].species,
                                                 level,
                                                 gFacilityTrainerMons[monId].nature,
                                                 ivs,
                                                 gFacilityTrainerMons[monId].evSpread,
                                                 otID);
            friendship = MAX_FRIENDSHIP;
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                SetMonMoveSlot(&gPlayerParty[MULTI_PARTY_SIZE + i], gFacilityTrainerMons[monId].moves[j], j);
                if (gFacilityTrainerMons[monId].moves[j] == MOVE_FRUSTRATION)
                    friendship = 0;
            }
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_FRIENDSHIP, &friendship);
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_HELD_ITEM, &gBattleFrontierHeldItems[gFacilityTrainerMons[monId].itemTableId]);
            for (j = 0; j < PLAYER_NAME_LENGTH + 1; j++)
                trainerName[j] = gFacilityTrainers[trainerId].trainerName[j];
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_OT_NAME, &trainerName);
            j = IsFrontierTrainerFemale(trainerId);
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_OT_GENDER, &j);
        }
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        trainerId -= TRAINER_RECORD_MIXING_FRIEND;
        for (i = 0; i < FRONTIER_MULTI_PARTY_SIZE; i++)
        {
            struct EmeraldBattleTowerRecord *record = &gSaveBlock2Ptr->frontier.towerRecords[trainerId];
            struct BattleTowerPokemon monData = record->party[gSaveBlock2Ptr->frontier.trainerIds[18 + i]];
            StringCopy(trainerName, record->name);
            if (record->language == LANGUAGE_JAPANESE)
            {
                if (monData.nickname[0] != EXT_CTRL_CODE_BEGIN || monData.nickname[1] != EXT_CTRL_CODE_JPN)
                {
                    monData.nickname[5] = EOS;
                    ConvertInternationalString(monData.nickname, LANGUAGE_JAPANESE);
                }
            }
            else
            {
                if (monData.nickname[0] == EXT_CTRL_CODE_BEGIN && monData.nickname[1] == EXT_CTRL_CODE_JPN)
                    trainerName[5] = EOS;
            }
            CreateBattleTowerMon2(&gPlayerParty[MULTI_PARTY_SIZE + i], &monData, TRUE);
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_OT_NAME, trainerName);
            j = IsFrontierTrainerFemale(trainerId + TRAINER_RECORD_MIXING_FRIEND);
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_OT_GENDER, &j);
        }
    }
    else
    {
        trainerId -= TRAINER_RECORD_MIXING_APPRENTICE;
        for (i = 0; i < FRONTIER_MULTI_PARTY_SIZE; i++)
        {
            CreateApprenticeMon(&gPlayerParty[MULTI_PARTY_SIZE + i], &gSaveBlock2Ptr->apprentices[trainerId], gSaveBlock2Ptr->frontier.trainerIds[18 + i]);
            j = IsFrontierTrainerFemale(trainerId + TRAINER_RECORD_MIXING_APPRENTICE);
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_OT_GENDER, &j);
        }
    }
}

bool32 RubyBattleTowerRecordToEmerald(struct RSBattleTowerRecord *src, struct EmeraldBattleTowerRecord *dst)
{
    s32 i, validMons = 0;

    for (i = 0; i < FRONTIER_PARTY_SIZE; i++)
    {
        if (src->party[i].species)
            validMons++;
    }

    if (validMons != FRONTIER_PARTY_SIZE)
    {
        memset(dst, 0, sizeof(*dst));
        return FALSE;
    }
    else
    {
        dst->lvlMode = src->lvlMode;
        dst->winStreak = src->winStreak;
        // UB: Reading outside the array. sRubyFacilityClassToEmerald has less than FACILITY_CLASSES_COUNT entries.
        #ifdef UBFIX
        for (i = 0; i < ARRAY_COUNT(sRubyFacilityClassToEmerald); i++)
        #else
        for (i = 0; i < FACILITY_CLASSES_COUNT; i++)
        #endif
        {
            if (sRubyFacilityClassToEmerald[i][0] == src->facilityClass)
                break;
        }
        if (i != FACILITY_CLASSES_COUNT)
            dst->facilityClass = sRubyFacilityClassToEmerald[i][1];
        else
            dst->facilityClass = FACILITY_CLASS_YOUNGSTER;

        for (i = 0; i < PLAYER_NAME_LENGTH + 1; i++)
            dst->name[i] = src->name[i];
        for (i = 0; i < TRAINER_ID_LENGTH; i++)
            dst->trainerId[i] = src->trainerId[i];
        for (i = 0; i < EASY_CHAT_BATTLE_WORDS_COUNT; i++)
            dst->greeting[i] = src->greeting[i];
        for (i = 0; i < EASY_CHAT_BATTLE_WORDS_COUNT; i++)
            dst->speechWon[i] = sRecordTrainerSpeechWon[i];
        for (i = 0; i < EASY_CHAT_BATTLE_WORDS_COUNT; i++)
            dst->speechLost[i] = sRecordTrainerSpeechLost[i];
        for (i = 0; i < FRONTIER_PARTY_SIZE; i++)
            dst->party[i] = src->party[i];

        CpuFill32(0, &dst->party[FRONTIER_PARTY_SIZE], sizeof(dst->party[FRONTIER_PARTY_SIZE]));
        CalcEmeraldBattleTowerChecksum(dst);
        return TRUE;
    }
}

bool32 EmeraldBattleTowerRecordToRuby(struct EmeraldBattleTowerRecord *src, struct RSBattleTowerRecord *dst)
{
    s32 i, validMons = 0;

    for (i = 0; i < FRONTIER_PARTY_SIZE; i++)
    {
        if (src->party[i].species)
            validMons++;
    }

    if (validMons != FRONTIER_PARTY_SIZE)
    {
        memset(dst, 0, sizeof(*dst));
        return FALSE;
    }
    else
    {
        dst->lvlMode = src->lvlMode;
        dst->winStreak = src->winStreak;
        // UB: Reading outside the array. sRubyFacilityClassToEmerald has less than FACILITY_CLASSES_COUNT entries.
        #ifdef UBFIX
        for (i = 0; i < ARRAY_COUNT(sRubyFacilityClassToEmerald); i++)
        #else
        for (i = 0; i < FACILITY_CLASSES_COUNT; i++)
        #endif
        {
            if (sRubyFacilityClassToEmerald[i][1] == src->facilityClass)
                break;
        }
        if (i != FACILITY_CLASSES_COUNT)
            dst->facilityClass = sRubyFacilityClassToEmerald[i][0];
        else
            dst->facilityClass = RS_FACILITY_CLASS_YOUNGSTER;

        for (i = 0; i < PLAYER_NAME_LENGTH + 1; i++)
            dst->name[i] = src->name[i];
        for (i = 0; i < TRAINER_ID_LENGTH; i++)
            dst->trainerId[i] = src->trainerId[i];
        for (i = 0; i < EASY_CHAT_BATTLE_WORDS_COUNT; i++)
            dst->greeting[i] = src->greeting[i];
        for (i = 0; i < FRONTIER_PARTY_SIZE; i++)
            dst->party[i] = src->party[i];

        CalcRubyBattleTowerChecksum(dst);
        return TRUE;
    }
}

void CalcApprenticeChecksum(struct Apprentice *apprentice)
{
    s32 i;

    apprentice->checksum = 0;
    for (i = 0; i < (sizeof(struct Apprentice) - 4) / 4; i++)
        apprentice->checksum += ((u32 *)apprentice)[i];
}

static void ClearApprentice(struct Apprentice *apprentice)
{
    s32 i;

    for (i = 0; i < (sizeof(struct Apprentice)) / 4; i++)
        ((u32 *)apprentice)[i] = 0;
    ResetApprenticeStruct(apprentice);
}

static void ValidateApprenticesChecksums(void)
{
    s32 i, j;

    for (i = 0; i < APPRENTICE_COUNT; i++)
    {
        u32 *data = (u32*) &gSaveBlock2Ptr->apprentices[i];
        u32 checksum = 0;
        for (j = 0; j < (sizeof(struct Apprentice) - 4) / 4; j++)
            checksum += data[j];
        if (gSaveBlock2Ptr->apprentices[i].checksum != checksum)
            ClearApprentice(&gSaveBlock2Ptr->apprentices[i]);
    }
}

void GetBattleTowerTrainerLanguage(u8 *dst, u16 trainerId)
{
    if (trainerId == TRAINER_EREADER)
    {
        *dst = gGameLanguage;
    }
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        *dst = gGameLanguage;
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            *dst = GetRecordedBattleRecordMixFriendLanguage();
        else
            *dst = gSaveBlock2Ptr->frontier.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].language;
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            *dst = GetRecordedBattleApprenticeLanguage();
        else
            *dst = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].language;
    }
}

u8 SetFacilityPtrsGetLevel(void)
{
    if (gSaveBlock2Ptr->frontier.lvlMode == FRONTIER_LVL_TENT)
    {
        return SetTentPtrsGetLevel();
    }
    else
    {
        gFacilityTrainers = gBattleFrontierTrainers;
        gFacilityTrainerMons = gBattleFrontierMons;
        return GetFrontierEnemyMonLevel(gSaveBlock2Ptr->frontier.lvlMode);
    }
}

u8 GetFrontierEnemyMonLevel(u8 lvlMode)
{
    u8 level;

    switch (lvlMode)
    {
    default:
    case FRONTIER_LVL_50:
        level = 50;
        break;
    case FRONTIER_LVL_OPEN:
        level = GetHighestLevelInPlayerParty();
        if (level < 60)
            level = 60;
        break;
    }

    return level;
}

s32 GetHighestLevelInPlayerParty(void)
{
    s32 highestLevel = 0;
    s32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL)
            && GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2, NULL) != SPECIES_EGG)
        {
            s32 level = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL, NULL);
            if (level > highestLevel)
                highestLevel = level;
        }
    }

    return highestLevel;
}

// Frontier Trainer parties are roughly scaled in difficulty with higher trainer IDs, so scale IVs as well
// Duplicated in Battle Dome as GetDomeTrainerMonIvs
static u8 GetFrontierTrainerFixedIvs(u16 trainerId)
{
    u8 fixedIv;

    if (trainerId <= FRONTIER_TRAINER_JILL)         // 0 - 99
        fixedIv = 3;
    else if (trainerId <= FRONTIER_TRAINER_CHLOE)   // 100 - 119
        fixedIv = 6;
    else if (trainerId <= FRONTIER_TRAINER_SOFIA)   // 120 - 139
        fixedIv = 9;
    else if (trainerId <= FRONTIER_TRAINER_JAZLYN)  // 140 - 159
        fixedIv = 12;
    else if (trainerId <= FRONTIER_TRAINER_ALISON)  // 160 - 179
        fixedIv = 15;
    else if (trainerId <= FRONTIER_TRAINER_LAMAR)   // 180 - 199
        fixedIv = 18;
    else if (trainerId <= FRONTIER_TRAINER_TESS)    // 200 - 219
        fixedIv = 21;
    else                                            // 220+ (- 299)
        fixedIv = 31;

    return fixedIv;
}

static u16 GetBattleTentTrainerId(void)
{
    u32 facility = VarGet(VAR_FRONTIER_FACILITY);

    if (facility == FRONTIER_FACILITY_PALACE)       // Verdanturf Tent; uses Palace mechanics
        return Random() % NUM_BATTLE_TENT_TRAINERS;
    else if (facility == FRONTIER_FACILITY_ARENA)   // Fallarbor Tent; uses Arena mechanics
        return Random() % NUM_BATTLE_TENT_TRAINERS;
    else if (facility == FRONTIER_FACILITY_FACTORY) // Slateport Tent; uses Factory mechanics
        return Random() % NUM_BATTLE_TENT_TRAINERS;
    else if (facility == FRONTIER_FACILITY_TOWER)
        return 0;
    else
        return 0;
}

static u8 SetTentPtrsGetLevel(void)
{
    u8 level = 30;
    u32 facility = VarGet(VAR_FRONTIER_FACILITY);

    if (facility == FRONTIER_FACILITY_FACTORY)
    {
        gFacilityTrainers = gSlateportBattleTentTrainers;
        gFacilityTrainerMons = gSlateportBattleTentMons;
    }
    else if (facility == FRONTIER_FACILITY_PALACE)
    {
        gFacilityTrainers = gVerdanturfBattleTentTrainers;
        gFacilityTrainerMons = gVerdanturfBattleTentMons;
    }
    else if (facility == FRONTIER_FACILITY_ARENA)
    {
        gFacilityTrainers = gFallarborBattleTentTrainers;
        gFacilityTrainerMons = gFallarborBattleTentMons;
    }
    else
    {
        gFacilityTrainers = gBattleFrontierTrainers;
        gFacilityTrainerMons = gBattleFrontierMons;
    }

    level = GetHighestLevelInPlayerParty();
    if (level < 30)
        level = 30;

    return level;
}

static void SetNextBattleTentOpponent(void)
{
    s32 i;
    u16 trainerId;

    do
    {
        trainerId = GetBattleTentTrainerId();
        for (i = 0; i < gSaveBlock2Ptr->frontier.curChallengeBattleNum; i++)
        {
            if (gSaveBlock2Ptr->frontier.trainerIds[i] == trainerId)
                break;
        }
    } while (i != gSaveBlock2Ptr->frontier.curChallengeBattleNum);

    gTrainerBattleOpponent_A = trainerId;
    SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
    if (gSaveBlock2Ptr->frontier.curChallengeBattleNum + 1 < 3)
       gSaveBlock2Ptr->frontier.trainerIds[gSaveBlock2Ptr->frontier.curChallengeBattleNum] = gTrainerBattleOpponent_A;
}

static void FillTentTrainerParty_(u16 trainerId, u8 firstMonId, u8 monCount)
{
    s32 i, j;
    u16 chosenMonIndices[MAX_FRONTIER_PARTY_SIZE];
    u8 friendship;
    u8 level = SetTentPtrsGetLevel();
    u8 fixedIV = 0;
    u8 bfMonCount;
    const u16 *monSet = NULL;
    u32 otID = 0;
    u16 monId;

    monSet = gFacilityTrainers[gTrainerBattleOpponent_A].monSet;

    bfMonCount = 0;
    monId = monSet[bfMonCount];
    while (monId != 0xFFFF)
    {
        bfMonCount++;
        monId = monSet[bfMonCount];
        if (monId == 0xFFFF)
            break;
    }

    i = 0;
    otID = Random32();
    while (i != monCount)
    {
        u16 monId = monSet[Random() % bfMonCount];

        // Ensure this pokemon species isn't a duplicate.
        for (j = 0; j < i + firstMonId; j++)
        {
            if (GetMonData(&gEnemyParty[j], MON_DATA_SPECIES, NULL) == gFacilityTrainerMons[monId].species)
                break;
        }
        if (j != i + firstMonId)
            continue;

        // Ensure this Pokemon's held item isn't a duplicate.
        for (j = 0; j < i + firstMonId; j++)
        {
            if (GetMonData(&gEnemyParty[j], MON_DATA_HELD_ITEM, NULL) != 0
             && GetMonData(&gEnemyParty[j], MON_DATA_HELD_ITEM, NULL) == gBattleFrontierHeldItems[gFacilityTrainerMons[monId].itemTableId])
                break;
        }
        if (j != i + firstMonId)
            continue;

        // Ensure this exact pokemon index isn't a duplicate. This check doesn't seem necessary
        // because the species and held items were already checked directly above.
        for (j = 0; j < i; j++)
        {
            if (chosenMonIndices[j] == monId)
                break;
        }
        if (j != i)
            continue;

        chosenMonIndices[i] = monId;

        // Place the chosen pokemon into the trainer's party.
        CreateMonWithEVSpreadNatureOTID(&gEnemyParty[i + firstMonId],
                                             gFacilityTrainerMons[monId].species,
                                             level,
                                             gFacilityTrainerMons[monId].nature,
                                             fixedIV,
                                             gFacilityTrainerMons[monId].evSpread,
                                             otID);

        friendship = MAX_FRIENDSHIP;
        // Give the chosen pokemon its specified moves.
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            SetMonMoveSlot(&gEnemyParty[i + firstMonId], gFacilityTrainerMons[monId].moves[j], j);
            if (gFacilityTrainerMons[monId].moves[j] == MOVE_FRUSTRATION)
                friendship = 0;  // Frustration is more powerful the lower the pokemon's friendship is.
        }

        SetMonData(&gEnemyParty[i + firstMonId], MON_DATA_FRIENDSHIP, &friendship);
        SetMonData(&gEnemyParty[i + firstMonId], MON_DATA_HELD_ITEM, &gBattleFrontierHeldItems[gFacilityTrainerMons[monId].itemTableId]);

        // The pokemon was successfully added to the trainer's party, so it's safe to move on to
        // the next party slot.
        i++;
    }
}

u8 FacilityClassToGraphicsId(u8 facilityClass)
{
    u8 trainerObjectGfxId;
    u8 i;

    // Search male classes.
    for (i = 0; i < ARRAY_COUNT(gTowerMaleFacilityClasses); i++)
    {
        if (gTowerMaleFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gTowerMaleFacilityClasses))
    {
        trainerObjectGfxId = gTowerMaleTrainerGfxIds[i];
        return trainerObjectGfxId;
    }

    // Search female classes.
    for (i = 0; i < ARRAY_COUNT(gTowerFemaleFacilityClasses); i++)
    {
        if (gTowerFemaleFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gTowerFemaleFacilityClasses))
    {
        trainerObjectGfxId = gTowerFemaleTrainerGfxIds[i];
        return trainerObjectGfxId;
    }
    else
    {
        return OBJ_EVENT_GFX_BOY_1;
    }
}

bool32 ValidateBattleTowerRecord(u8 recordId) // unused
{
    s32 i;
    u32 *record = (u32*)(&gSaveBlock2Ptr->frontier.towerRecords[recordId]);
    u32 checksum = 0;
    u32 hasData = 0;
    for (i = 0; i < (sizeof(struct EmeraldBattleTowerRecord) - 4) / 4; i++) // - 4, because of the last fjeld bejng the checksum jtself.
    {
        checksum += record[i];
        hasData |= record[i];
    }

    if (checksum == 0 && hasData == 0)
    {
        return FALSE;
    }
    else if (gSaveBlock2Ptr->frontier.towerRecords[recordId].checksum != checksum)
    {
        ClearBattleTowerRecord(&gSaveBlock2Ptr->frontier.towerRecords[recordId]);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void TrySetLinkBattleTowerEnemyPartyLevel(void)
{
    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_x2000000))
    {
        s32 i;
        u8 enemyLevel = SetFacilityPtrsGetLevel();

        for (i = 0; i < PARTY_SIZE; i++)
        {
            u32 species = GetMonData(&gEnemyParty[i], MON_DATA_SPECIES, NULL);
            if (species)
            {
                SetMonData(&gEnemyParty[i], MON_DATA_EXP, &gExperienceTables[gBaseStats[species].growthRate][enemyLevel]);
                CalculateMonStats(&gEnemyParty[i]);
            }
        }
    }
}
