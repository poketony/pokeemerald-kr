#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_message.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "data.h"
#include "event_data.h"
#include "frontier_util.h"
#include "international_string_util.h"
#include "item.h"
#include "link.h"
#include "menu.h"
#include "palette.h"
#include "recorded_battle.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "trainer_hill.h"
#include "window.h"
#include "korean.h"
#include "constants/battle_dome.h"
#include "constants/battle_string_ids.h"
#include "constants/berry.h"
#include "constants/frontier_util.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/trainers.h"
#include "constants/trainer_hill.h"
#include "constants/weather.h"

struct BattleWindowText
{
    u8 fillValue;
    u8 fontId;
    u8 x;
    u8 y;
    u8 letterSpacing;
    u8 lineSpacing;
    u8 speed;
    u8 fgColor;
    u8 bgColor;
    u8 shadowColor;
};

extern const u16 gUnknown_08D85620[];

// this file's functions
static void ChooseMoveUsedParticle(u8 *textPtr);
static void ChooseTypeOfMoveUsedString(u8 *dst);
static void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst);

// EWRAM vars
static EWRAM_DATA u8 sBattlerAbilities[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA struct BattleMsgData *gBattleMsgDataPtr = NULL;
static EWRAM_DATA bool8 sHasJong = FALSE;

// const rom data
// todo: make some of those names less vague: attacker/target vs pkmn, etc.
static const u8 sText_Trainer1LoseText[] = _("{B_TRAINER1_LOSE_TEXT}");
static const u8 sText_PkmnGainedEXP[] = _("{B_BUFF1}{B_TXT_EUNNEUN}{B_BUFF2}\n{B_BUFF3} 경험치를 얻었다!\p"); // § §あ けいけんちを もらった!ｐ
static const u8 sText_EmptyString4[] = _(""); // は
static const u8 sText_ABoosted[] = _(" 많은 양의"); // は おおめにｎ
static const u8 sText_PkmnGrewToLv[] = _("{B_BUFF1}{B_TXT_EUNNEUN}\n레벨{B_BUFF2}{B_TXT_EU}로 올랐다!{WAIT_SE}\p"); // § はｎレベル§あ に あがった!©こｐ
static const u8 sText_PkmnLearnedMove[] = _("{B_BUFF1}{B_TXT_EUNNEUN}\n{B_BUFF2}{B_TXT_EULREUL} 배웠다!{WAIT_SE}\p"); // § はｎ§あを おぼえた!©こｐ
static const u8 sText_TryToLearnMove1[] = _("{B_BUFF1}{B_TXT_EUNNEUN} 새로\n{B_BUFF2}{B_TXT_EULREUL} 배우고 싶다...!\p"); // § は あたらしくｎ§あを おぼえたい………!ｐ
static const u8 sText_TryToLearnMove2[] = _("그러나 {B_BUFF1}{B_TXT_EUNNEUN} 기술을 4개\n알고 있으므로 더 이상 배울 수 없다!\p"); // しかし § は わざを 4つｎおぼえるので せいいっぱいだ!ｐ
static const u8 sText_TryToLearnMove3[] = _("{B_BUFF2} 대신\n다른 기술을 잊게 하겠습니까?"); // §あの かわりにｎほかの わざを わすれさせますか?
static const u8 sText_PkmnForgotMove[] = _("{B_BUFF1}{B_TXT_EUNNEUN} {B_BUFF2}{B_TXT_EULREUL}\n깨끗이 잊었다!\p"); // § は §あのｎつかいかたを きれいに わすれた!ｐ
static const u8 sText_StopLearningMove[] = _("{PAUSE 32}그럼... {B_BUFF2}{B_TXT_EULREUL}\n배우는 것을 포기하겠습니까?"); // ©くみそれでは…… §あをｎおぼえるのを あきらめますか?
static const u8 sText_DidNotLearnMove[] = _("{B_BUFF1}{B_TXT_EUNNEUN} {B_BUFF2}{B_TXT_EULREUL}\n결국 배우지 않았다!\p"); // § は §あをｎおぼえずに おわった!ｐ
static const u8 sText_UseNextPkmn[] = _("다음 포켓몬을 쓰겠습니까?"); // つぎの ポケモンを つかいますか?
static const u8 sText_AttackMissed[] = _("그러나 {B_ATK_NAME_WITH_PREFIX}의\n공격은 빗나갔다!"); // しかし §そのｎこうげきは はずれた!
static const u8 sText_PkmnProtectedItself[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 공격으로부터\n몸을 지켰다!"); // §たは こうげきからｎみを まもった!
static const u8 sText_AvoidedDamage[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_ABILITY} 때문에\n데미지를 입지 않는다!"); // §たは §のでｎダメ-ジを うけない!
static const u8 sText_PkmnMakesGroundMiss[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_ABILITY} 때문에\n땅타입의 기술이 맞지 않는다!"); // §たは §のでｎじめんタイプの わざが あたらない!
static const u8 sText_PkmnAvoidedAttack[] = _("{B_DEF_NAME_WITH_PREFIX}에게는\n맞지 않았다!"); // §たにはｎあたらなかった!
static const u8 sText_ItDoesntAffect[] = _("{B_DEF_NAME_WITH_PREFIX}에게는\n효과가 없는 것 같다..."); // §たにはｎこうかが ない みたいだ……
static const u8 sText_AttackerFainted[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 쓰러졌다!\p"); // §そは たおれた!ｐ
static const u8 sText_TargetFainted[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 쓰러졌다!\p"); // §たは たおれた!ｐ
static const u8 sText_PlayerGotMoney[] = _("{B_PLAYER_NAME}{B_TXT_EUNNEUN} 상금으로\n{B_BUFF1}원을 손에 넣었다!\p"); // §もは しょうきんとしてｎ§ ￥ てにいれた!ｐ
static const u8 sText_PlayerWhiteout[] = _("{B_PLAYER_NAME}에게는\n싸울 수 있는 포켓몬이 없다!\p"); // §もの てもとにはｎたたかえる ポケモンが いない!ｐ
static const u8 sText_PlayerWhiteout2[] = _("{B_PLAYER_NAME}{B_TXT_EUNNEUN}\n눈앞이 캄캄해졌다!{PAUSE_UNTIL_PRESS}"); // §もはｎめのまえが まっくらに なった!©け
static const u8 sText_PreventsEscape[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 {B_SCR_ACTIVE_ABILITY}\n때문에 도망칠 수 없다!\p"); // §ての §はでｎにげられない!ｐ
static const u8 sText_CantEscape2[] = _("도망칠 수 없다!\p"); // にげられない!ｐ
static const u8 sText_AttackerCantEscape[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 도망칠 수 없다!"); // §そは にげられない!
static const u8 sText_HitXTimes[] = _("{B_BUFF1}번 맞았다!"); // § かい あたった!
static const u8 sText_PkmnFellAsleep[] = _("{B_EFF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n잠들어 버렸다!"); // §ちはｎねむってしまった!
static const u8 sText_PkmnMadeSleep[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 {B_SCR_ACTIVE_ABILITY}\n때문에 {B_EFF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 잠들어 버렸다!"); // §ての §はでｎ§ちは ねむってしまった!
static const u8 sText_PkmnAlreadyAsleep[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 이미\n잠들어 있다"); // §たは すでにｎねむっている
static const u8 sText_PkmnAlreadyAsleep2[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 이미\n잠들어 있다"); // §そは すでにｎねむっている
static const u8 sText_PkmnWasntAffected[] = _("그러나 {B_DEF_NAME_WITH_PREFIX}에게는\n효과가 없다!"); // しかし §たにはｎきかなかった!
static const u8 sText_PkmnWasPoisoned[] = _("{B_EFF_NAME_WITH_PREFIX}의 몸에 독이 퍼졌다!"); // §ちは どくをあびた!
static const u8 sText_PkmnPoisonedBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 {B_SCR_ACTIVE_ABILITY} 때문에\n{B_EFF_NAME_WITH_PREFIX}의 몸에 독이 퍼졌다!"); // §ての §はでｎ§ちは どくをあびた!
static const u8 sText_PkmnHurtByPoison[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n독에 의한 데미지를 입고 있다!"); // §そはｎどくの ダメ-ジを うけている!
static const u8 sText_PkmnAlreadyPoisoned[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 이미\n몸에 독이 퍼진 상태다"); // §たは すでにｎどくを あびている
static const u8 sText_PkmnBadlyPoisoned[] = _("{B_EFF_NAME_WITH_PREFIX}의\n몸에 맹독이 퍼졌다!"); // §ちはｎもうどくをあびた!
static const u8 sText_PkmnEnergyDrained[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EU}로부터\n체력을 흡수했다!"); // §たからｎたいりょくを すいとった!
static const u8 sText_PkmnWasBurned[] = _("{B_EFF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n화상을 입었다!"); // §ちはｎやけどをおった!
static const u8 sText_PkmnBurnedBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 {B_SCR_ACTIVE_ABILITY} 때문에\n{B_EFF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 화상을 입었다!"); // §ての §はでｎ§ちは やけどをおった!
static const u8 sText_PkmnHurtByBurn[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n화상 데미지를 입고 있다!"); // §そはｎやけどの ダメ-ジを うけている!
static const u8 sText_PkmnAlreadyHasBurn[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 이미\n화상을 입은 상태다"); // $§たは すでにｎやけどを おっている
static const u8 sText_PkmnWasFrozen[] = _("{B_EFF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n얼어붙었다!"); // §ちはｎこおりづけになった!
static const u8 sText_PkmnFrozenBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 {B_SCR_ACTIVE_ABILITY} 때문에\n{B_EFF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 얼어붙었다!"); // §ての §はでｎ§ちは こおりづけになった!
static const u8 sText_PkmnIsFrozen[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n얼어버려서 움직이지 않는다!"); // §そはｎこおって しまって うごかない!
static const u8 sText_PkmnWasDefrosted[] = _("{B_DEF_NAME_WITH_PREFIX}의\n얼음이 녹았다!"); // §たのｎこおりが とけた!
static const u8 sText_PkmnWasDefrosted2[] = _("{B_ATK_NAME_WITH_PREFIX}의\n얼음이 녹았다!"); // §そのｎこおりが とけた!
static const u8 sText_PkmnWasDefrostedBy[] = _("{B_ATK_NAME_WITH_PREFIX}의 얼음이\n{B_CURRENT_MOVE}{B_TXT_EU}로 녹았다!"); // §その こおりがｎ§とで とけた!
static const u8 sText_PkmnWasParalyzed[] = _("{B_EFF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 마비되어\n기술이 나오기 어려워졌다!"); // §ちは まひしてｎわざが でにくくなった!
static const u8 sText_PkmnWasParalyzedBy[] = _("{B_EFF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 {B_SCR_ACTIVE_ABILITY} 때문에\l마비되어 기술이 나오기 어려워졌다!"); // §ちはｎ§ての §はでｌまひして わざが でにくくなった!
static const u8 sText_PkmnIsParalyzed[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n몸이 저려서 움직일 수 없다"); // §そはｎからだが しびれて うごけない
static const u8 sText_PkmnIsAlreadyParalyzed[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 이미\n마비되어 있다"); // §たは すでにｎまひしている
static const u8 sText_PkmnHealedParalysis[] = _("{B_DEF_NAME_WITH_PREFIX}의\n마비가 풀렸다!"); // §たのｎまひが なおった!
static const u8 sText_PkmnDreamEaten[] = _("{B_DEF_NAME_WITH_PREFIX}의\n꿈을 먹었다!"); // §たのｎゆめを くった!
static const u8 sText_StatsWontIncrease[] = _("{B_ATK_NAME_WITH_PREFIX}의\n{B_BUFF1}{B_TXT_EUNNEUN} 더 올라가지 않는다!"); // §そのｎ§ は もうあがらない!
static const u8 sText_StatsWontDecrease[] = _("{B_DEF_NAME_WITH_PREFIX}의\n{B_BUFF1}{B_TXT_EUNNEUN} 더 떨어지지 않는다!"); // §たのｎ§ は もうさがらない!
static const u8 sText_TeamStoppedWorking[] = _("우리 편 {B_BUFF1}의\n효과가 떨어졌다!"); // みかたの § のｎこうかが きれた!
static const u8 sText_FoeStoppedWorking[] = _("상대 {B_BUFF1}의\n효과가 떨어졌다!"); // あいての § のｎこうかが きれた!
static const u8 sText_PkmnIsConfused[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n혼란에 빠져 있다!"); // §そはｎこんらんしている!
static const u8 sText_PkmnHealedConfusion[] = _("{B_ATK_NAME_WITH_PREFIX}의\n혼란이 풀렸다!"); // §そのｎこんらんが とけた!
static const u8 sText_PkmnWasConfused[] = _("{B_EFF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n혼란에 빠졌다!"); // §ちはｎこんらんした!
static const u8 sText_PkmnAlreadyConfused[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n이미 혼란에 빠져 있다"); // §たはｎすでに こんらん している
static const u8 sText_PkmnFellInLove[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n헤롱헤롱해졌다!"); // §たはｎメロメロに なった!
static const u8 sText_PkmnInLove[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_SCR_ACTIVE_NAME_WITH_PREFIX}에게 헤롱헤롱해 있다!"); // §そはｎ§てに メロメロだ!
static const u8 sText_PkmnImmobilizedByLove[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 헤롱헤롱해서\n기술을 쓸 수 없었다!"); // §そは メロメロでｎわざが だせなかった!
static const u8 sText_PkmnBlownAway[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n날려가 버렸다!"); // §たはｎふきとばされた!
static const u8 sText_PkmnChangedType[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_BUFF1}타입이 됐다!"); // §そはｎ§ タイプに なった!
static const u8 sText_PkmnFlinched[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 풀이 죽어\n움직일 수 없었다!"); // §そは ひるんでｎうごけなかった!
static const u8 sText_PkmnRegainedHealth[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 체력을\n회복했다!"); // §たは たいりょくをｎかいふくした!
static const u8 sText_PkmnHPFull[] = _("그러나 {B_DEF_NAME_WITH_PREFIX}의\n체력은 가득찬 상태다!"); // しかし §たのｎたいりょくは まんたんだ!
static const u8 sText_PkmnRaisedSpDef[] = _("{B_ATK_PREFIX2} {B_CURRENT_MOVE}{B_TXT_EU}로\n특수공격에 강해졌다!"); // §れ §とでｎとくこうに つよくなった!
static const u8 sText_PkmnRaisedSpDefALittle[] = _("{B_ATK_PREFIX2} {B_CURRENT_MOVE}{B_TXT_EU}로\n특수공격에 조금 강해졌다!"); // §れ §とでｎとくこうに すこし つよくなった!
static const u8 sText_PkmnRaisedDef[] = _("{B_ATK_PREFIX2} {B_CURRENT_MOVE}{B_TXT_EU}로\n물리 공격에 강해졌다!"); // §れ §とでｎだげきこうげきに つよくなった!
static const u8 sText_PkmnRaisedDefALittle[] = _("{B_ATK_PREFIX2} {B_CURRENT_MOVE}{B_TXT_EU}로\n물리 공격에 조금 강해졌다!"); // §れ §とでｎだげきこうげきに すこし つよくなった!
static const u8 sText_PkmnCoveredByVeil[] = _("{B_ATK_PREFIX2}\n신비의 베일에 둘러싸였다!"); // §れｎしんぴのベ-ルに つつまれた!
static const u8 sText_PkmnUsedSafeguard[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EULREUL}\n신비의 베일이 지켜주고 있다!"); // §たはｎしんぴのベ-ルに まもられている!
static const u8 sText_PkmnSafeguardExpired[] = _("{B_ATK_PREFIX3} 감싸던\n신비의 베일이 없어졌다!"); // §わ つつんでいたｎしんぴの ベ-ルが なくなった!
static const u8 sText_PkmnWentToSleep[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n잠을 자기 시작했다!"); // §そはｎねむりはじめた!
static const u8 sText_PkmnSleptHealthy[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n건강한 상태로 잠을 자기 시작했다!");
static const u8 sText_PkmnWhippedWhirlwind[] = _("{B_ATK_NAME_WITH_PREFIX}의 주위에서\n공기가 소용돌이친다!");
static const u8 sText_PkmnTookSunlight[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n빛을 흡수했다!");
static const u8 sText_PkmnLoweredHead[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n목을 움츠렸다!");
static const u8 sText_PkmnIsGlowing[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EULREUL}\n세찬 빛이 감쌌다!");
static const u8 sText_PkmnFlewHigh[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n하늘 높이 날아올랐다!");
static const u8 sText_PkmnDugHole[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n구멍을 파서 땅속에 파고들었다!");
static const u8 sText_PkmnHidUnderwater[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n물속에 몸을 숨겼다!");
static const u8 sText_PkmnSprangUp[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n뛰어올랐다!");
static const u8 sText_PkmnSqueezedByBind[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_ATK_NAME_WITH_PREFIX}에게 조이기를 당했다!");
static const u8 sText_PkmnTrappedInVortex[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n소용돌이 속에 갇혔다!");
static const u8 sText_PkmnTrappedBySandTomb[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n모래지옥에 붙잡혔다!");
static const u8 sText_PkmnWrappedBy[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_ATK_NAME_WITH_PREFIX}에게 휘감겼다!");
static const u8 sText_PkmnClamped[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_ATK_NAME_WITH_PREFIX}의 껍질에 꼈다!");
static const u8 sText_PkmnHurtBy[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_BUFF1}의\n데미지를 입고 있다");
static const u8 sText_PkmnFreedFrom[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_EU}로부터 풀려났다!");
static const u8 sText_PkmnCrashed[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n의욕이 넘쳐서 땅에 부딪혔다!");
const u8 gText_PkmnShroudedInMist[] = _("{B_ATK_PREFIX2}\n흰안개에 둘러싸였다!");
static const u8 sText_PkmnProtectedByMist[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EULREUL}\n흰안개가 지켜주고 있다");
const u8 gText_PkmnGettingPumped[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n의욕이 넘치고 있다!");
static const u8 sText_PkmnHitWithRecoil[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n공격의 반동을 입었다!");
static const u8 sText_PkmnProtectedItself2[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n방어 태세에 들어갔다!");
static const u8 sText_PkmnBuffetedBySandstorm[] = _("모래바람이 {B_ATK_NAME_WITH_PREFIX}{B_TXT_EULREUL}\n덮쳤다!"); // すなあらしが §そをｎおそう!
static const u8 sText_PkmnPeltedByHail[] = _("싸라기눈이 {B_ATK_NAME_WITH_PREFIX}{B_TXT_EULREUL}\n덮쳤다!"); // あられが §そをｎおそう!
static const u8 sText_PkmnsXWoreOff[] = _("{B_ATK_PREFIX1} {B_BUFF1}의\n효과가 떨어졌다!"); // §り § のｎこうかが きれた!
static const u8 sText_PkmnSeeded[] = _("{B_DEF_NAME_WITH_PREFIX}에게\n씨앗을 심었다!"); // §たにｎたねを うえつけた!
static const u8 sText_PkmnEvadedAttack[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n공격을 피했다!"); // §たはｎこうげきを かわした!
static const u8 sText_PkmnSappedByLeechSeed[] = _("씨뿌리기가 {B_ATK_NAME_WITH_PREFIX}의\n체력을 빼앗는다!"); // やどりぎが §そのｎたいりょくを うばう!
static const u8 sText_PkmnFastAsleep[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n쿨쿨 잠들어 있다"); // §そはｎぐうぐう ねむっている
static const u8 sText_PkmnWokeUp[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 눈을 떴다!"); // §そは めを さました!
static const u8 sText_PkmnUproarKeptAwake[] = _("그러나 {B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_IGA}\n소란스러워서 잠들 수 없다!"); // しかし §てがｎさわいでいて ねむれなかった!
static const u8 sText_PkmnWokeUpInUproar[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 소란스러워서\n눈을 떴다!"); // §そは さわがしくてｎめが さめた!
static const u8 sText_PkmnCausedUproar[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 소란피기 시작했다!"); // §そは さわぎだした!
static const u8 sText_PkmnMakingUproar[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 소란피우고 있다!"); // §そは さわいでいる!
static const u8 sText_PkmnCalmedDown[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n얌전해졌다"); // §そはｎおとなしくなった
static const u8 sText_PkmnCantSleepInUproar[] = _("그러나 {B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n소란스러워서 잠들 수 없다!"); // しかし§たはｎさわいでいて ねむらない!
static const u8 sText_PkmnStockpiled[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_BUFF1}개 비축했다!");
static const u8 sText_PkmnCantStockpile[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n더 이상 비축할 수 었다!");
static const u8 sText_PkmnCantSleepInUproar2[] = _("그러나 {B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n소란피고 있어서 잠들지 않는다!");
static const u8 sText_UproarKeptPkmnAwake[] = _("그러나 {B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n소란스러워서 잠들 수 없다!");
static const u8 sText_PkmnStayedAwakeUsing[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_DEF_ABILITY} 때문에 잠들지 않는다!"); // たはｎ§ので ねむらない!
static const u8 sText_PkmnStoringEnergy[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 참고 있다"); // §そは がまんしている
static const u8 sText_PkmnUnleashedEnergy[] = _("{B_ATK_NAME_WITH_PREFIX}의\n참기가 풀렸다!"); // §そのｎがまんが とかれた!
static const u8 sText_PkmnFatigueConfusion[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n몹시 지쳐서 혼란에 빠졌다!"); // §そはｎつかれはてて こんらんした!
static const u8 sText_PkmnPickedUpItem[] = _("{B_PLAYER_NAME}{B_TXT_EUNNEUN}\n{B_BUFF1}원을 주웠다!\p"); // §もは § ￥ｎひろった!ｐ
static const u8 sText_PkmnUnaffected[] = _("{B_DEF_NAME_WITH_PREFIX}에게는\n전혀 효과가 없다!");
static const u8 sText_PkmnTransformedInto[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_EU}로 변신했다!");
static const u8 sText_PkmnMadeSubstitute[] = _("{B_ATK_NAME_WITH_PREFIX}의\n분신이 나타났다"); // §そのｎぶんしんが あらわれた
static const u8 sText_PkmnHasSubstitute[] = _("{B_ATK_NAME_WITH_PREFIX}의\n대타는 이미 나와있다!"); // しかし §そのｎみがわりは すでに でていた!
static const u8 sText_SubstituteDamaged[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EULREUL} 대신하여\n분신이 공격을 받았다!\p"); // §たに かわってｎぶんしんが こうげきを うけた!ｐ
static const u8 sText_PkmnSubstituteFaded[] = _("{B_DEF_NAME_WITH_PREFIX}의 분신은\n사라져 버렸다...\p"); // §たの ぶんしんはｎきえてしまった……ｐ
static const u8 sText_PkmnMustRecharge[] = _("공격의 반동으로\n{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 움직일 수 없다!"); // こうげきの はんどうでｎ§そは うごけない!
static const u8 sText_PkmnRageBuilding[] = _("{B_DEF_NAME_WITH_PREFIX}의 분노\n볼티지가 올라가고 있다!"); // §たの いかりのｎボルテ-ジが あがっていく!
static const u8 sText_PkmnMoveWasDisabled[] = _("{B_DEF_NAME_WITH_PREFIX}의\n{B_BUFF1}{B_TXT_EULREUL} 봉인했다!"); // §たのｎ§ を ふうじこめた!
static const u8 sText_PkmnMoveDisabledNoMore[] = _("{B_ATK_NAME_WITH_PREFIX}의\n사슬묶기가 풀렸다!"); // §そのｎかなしばりが とけた!
static const u8 sText_PkmnGotEncore[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n앵콜을 받았다!"); // §たはｎアンコ-ルを うけた!
static const u8 sText_PkmnEncoreEnded[] = _("{B_ATK_NAME_WITH_PREFIX}의\n앵콜 상태가 풀렸다!"); // §そのｎアンコ-ルじょうたいが とけた!
static const u8 sText_PkmnTookAim[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 목표를\n{B_DEF_NAME_WITH_PREFIX}{B_TXT_EU}로 결정했다!");
static const u8 sText_PkmnSketchedMove[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_EULREUL} 스케치했다!");
static const u8 sText_PkmnTryingToTakeFoe[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 상대를\n길동무로 삼으려 하고 있다");
static const u8 sText_PkmnTookFoe[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_ATK_NAME_WITH_PREFIX}{B_TXT_EULREUL}\n길동무로 삼았다!");
static const u8 sText_PkmnReducedPP[] = _("{B_DEF_NAME_WITH_PREFIX}의\n{B_BUFF1}{B_TXT_EULREUL} {B_BUFF2} 깎았다!");
static const u8 sText_PkmnStoleItem[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_NAME_WITH_PREFIX}{B_TXT_EU}로부터\n{B_LAST_ITEM}{B_TXT_EULREUL} 빼앗았다!"); // §そは §たからｎ§にを うばいとった!
static const u8 sText_TargetCantEscapeNow[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n이제 도망칠 수 없다!");
static const u8 sText_PkmnFellIntoNightmare[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n악몽을 꾸기 시작했다!");
static const u8 sText_PkmnLockedInNightmare[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n악몽에 시달리고 있다!");
static const u8 sText_PkmnLaidCurse[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n자신의 체력을 깎아서\l{B_DEF_NAME_WITH_PREFIX}에게 저주를 걸었다!");
static const u8 sText_PkmnAfflictedByCurse[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n저주받고 있다!");
static const u8 sText_SpikesScattered[] = _("{B_DEF_PREFIX1}의 발밑에\n압정이 뿌려졌다!");
static const u8 sText_PkmnHurtBySpikes[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 압정뿌리기의\n데미지를 입었다!");
static const u8 sText_PkmnIdentified[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_NAME_WITH_PREFIX}의\n정체를 꿰뚫어 보았다!");
static const u8 sText_PkmnPerishCountFell[] = _("{B_ATK_NAME_WITH_PREFIX}의 멸망의\n카운트가 {B_BUFF1}{B_TXT_IGA} 되었다!");
static const u8 sText_PkmnBracedItself[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n버티기 태세에 들어갔다!");
static const u8 sText_PkmnEnduredHit[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n공격을 버텼다!");
static const u8 sText_MagnitudeStrength[] = _("매그니튜드{B_BUFF1}!!");
static const u8 sText_PkmnCutHPMaxedAttack[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 체력을 깎아서\n풀파워로 만들었다!");
static const u8 sText_PkmnCopiedStatChanges[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_NAME_WITH_PREFIX}의\n능력 변화를 복사했다!");
static const u8 sText_PkmnGotFree[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_NAME_WITH_PREFIX}의\n{B_BUFF1}{B_TXT_EU}로부터 풀려났다!");
static const u8 sText_PkmnShedLeechSeed[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n씨앗을 날려버렸다!");
static const u8 sText_PkmnBlewAwaySpikes[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n압정을 날려버렸다!");
static const u8 sText_PkmnFledFromBattle[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 배틀에서\n이탈했다!"); // §そは せんとうからｎりだつした!
static const u8 sText_PkmnForesawAttack[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 미래의\n공격을 예지했다!"); // §そは みらいにｎこうげきを よちした!
static const u8 sText_PkmnTookAttack[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_BUFF1} 공격을 받았다!"); // §たは § のｎこうげきを うけた!
static const u8 sText_PkmnChoseXAsDestiny[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_CURRENT_MOVE}{B_TXT_EULREUL}\n미래에 맡겼다!"); // §そは §とをｎみらいに たくした!
static const u8 sText_PkmnAttack[] = _("{B_BUFF1}의 공격!");
static const u8 sText_PkmnCenterAttention[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n주목의 대상이 되었다!");
static const u8 sText_PkmnChargingPower[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n충전을 시작했다!");
static const u8 sText_NaturePowerTurnedInto[] = _("자연의힘은\n{B_CURRENT_MOVE}{B_TXT_IGA} 되었다!"); // しぜんのちからはｎ§とに なった!
static const u8 sText_PkmnStatusNormal[] = _("{B_ATK_NAME_WITH_PREFIX}의 상태이상이\n나았다!");
static const u8 sText_PkmnSubjectedToTorment[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n트집을 잡혔다!");
static const u8 sText_PkmnTighteningFocus[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n집중력을 높이고 있다!");
static const u8 sText_PkmnFellForTaunt[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n도발에 넘어가 버렸다!");
static const u8 sText_PkmnReadyToHelp[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_NAME_WITH_PREFIX}에게\n도우미가 되어주려 한다!");
static const u8 sText_PkmnSwitchedItems[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 서로의\n도구를 교체했다!");
static const u8 sText_PkmnObtainedX[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_EULREUL} 손에 넣었다!");
static const u8 sText_PkmnObtainedX2[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_BUFF2}{B_TXT_EULREUL} 손에 넣었다!");
static const u8 sText_PkmnObtainedXYObtainedZ[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_BUFF1}{B_TXT_EULREUL}\n손에 넣었다!\p{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_BUFF2}{B_TXT_EULREUL}\n손에 넣었다!"); // §そは § をｎてに いれた!ｐ§たは §あをｎてに いれた!
static const u8 sText_PkmnCopiedFoe[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_NAME_WITH_PREFIX}의\n{B_DEF_ABILITY}{B_TXT_EULREUL} 복사했다!");
static const u8 sText_PkmnMadeWish[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n희망사항을 썼다!");
static const u8 sText_PkmnWishCameTrue[] = _("{B_BUFF1}의\n희망사항이 이루어졌다!");
static const u8 sText_PkmnPlantedRoots[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 뿌리를 뻗었다!");
static const u8 sText_PkmnAbsorbedNutrients[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 뿌리로부터\n양분을 흡수했다!");
static const u8 sText_PkmnAnchoredItself[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 뿌리를 뻗어서\n움직이지 않는다!");
static const u8 sText_PkmnWasMadeDrowsy[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_NAME_WITH_PREFIX}의\n졸음을 유도했다!");
static const u8 sText_PkmnKnockedOff[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_NAME_WITH_PREFIX}의\n{B_LAST_ITEM}{B_TXT_EULREUL} 탁쳐서 떨구었다!");
static const u8 sText_PkmnSwappedAbilities[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 서로의\n특성을 교체했다!");
static const u8 sText_PkmnSealedOpponentMove[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 상대의\n기술을 봉인했다!");
static const u8 sText_PkmnWantsGrudge[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 상대에게\n원념을 걸려 하고 있다!");
static const u8 sText_PkmnLostPPGrudge[] = _("{B_ATK_NAME_WITH_PREFIX}의 {B_BUFF1}{B_TXT_EUNNEUN}\n원념으로 PP가 0이 되었다!");
static const u8 sText_PkmnShroudedItself[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_CURRENT_MOVE}에 둘러싸였다!");
static const u8 sText_PkmnMoveBounced[] = _("{B_ATK_NAME_WITH_PREFIX}의 {B_CURRENT_MOVE}{B_TXT_EUNNEUN}\n매직코트에 튕겨졌다!");
static const u8 sText_PkmnWaitsForTarget[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n상대의 움직임을 살피고 있다!");
static const u8 sText_PkmnSnatchedMove[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_SCR_ACTIVE_NAME_WITH_PREFIX}의\n기술을 가로챘다!");
static const u8 sText_ElectricityWeakened[] = _("전기의 위력이 약해졌다!");
static const u8 sText_FireWeakened[] = _("불꽃의 위력이 약해졌다!");
static const u8 sText_XFoundOneY[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_LAST_ITEM}{B_TXT_EULREUL} 주워 왔다!");
static const u8 sText_SoothingAroma[] = _("기분 좋은 향기가 퍼졌다!");
static const u8 sText_ItemsCantBeUsedNow[] = _("여기에서는 도구를\n사용할 수 없습니다!{PAUSE 64}"); // ここでは どうぐを つかうことはｎできません!©くぞ
static const u8 sText_ForXCommaYZ[] = _("{B_LAST_ITEM}{B_TXT_EUNNEUN} {B_SCR_ACTIVE_NAME_WITH_PREFIX}에게는\n{B_BUFF1}");
static const u8 sText_PkmnUsedXToGetPumped[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EULREUL} 써서\n의욕이 넘치기 시작했다!");
static const u8 sText_PkmnLostFocus[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 집중력이\n떨어져서 기술을 쓸 수 없었다!");
static const u8 sText_PkmnWasDraggedOut[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 배틀에\n끌려 나왔다!\p");
static const u8 sText_TheWallShattered[] = _("벽이 깨졌다!"); // かべが こわれた!
static const u8 sText_ButNoEffect[] = _("그러나 효과가 없었다!"); // しかし こうかが なかった!
static const u8 sText_PkmnHasNoMovesLeft[] = _("{B_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 쓸 수 있는\n기술이 없다!\p");
static const u8 sText_PkmnMoveIsDisabled[] = _("{B_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 사슬묶기 때문에\n{B_CURRENT_MOVE}{B_TXT_EULREUL} 쓸 수 없다!\p");
static const u8 sText_PkmnCantUseMoveTorment[] = _("{B_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n트집을 잡혔기 때문에\l계속해서 같은 기술을 쓸 수 없다!\p");
static const u8 sText_PkmnCantUseMoveTaunt[] = _("{B_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 도발당한 상태라서\n{B_CURRENT_MOVE}{B_TXT_EULREUL} 쓸 수 없다!\p");
static const u8 sText_PkmnCantUseMoveSealed[] = _("{B_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 봉인 때문에\n{B_CURRENT_MOVE}{B_TXT_EULREUL} 쓸 수 없다!\p"); // §つは ふういんでｎ§とが だせない!ｐ
static const u8 sText_PkmnMadeItRain[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 {B_SCR_ACTIVE_ABILITY} 때문에\n비가 내리기 시작했다!"); // §ての §はでｎあめが ふりはじめた!
static const u8 sText_PkmnRaisedSpeed[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 {B_SCR_ACTIVE_ABILITY} 때문에\n스피드가 올라갔다!"); // §ては §はでｎすばやさが あがった!
static const u8 sText_PkmnProtectedBy[] = _("{B_DEF_NAME_WITH_PREFIX}의 {B_DEF_ABILITY} 때문에\n효과가 없었다!"); // §たは §のでｎきかなかった!
static const u8 sText_PkmnPreventsUsage[] = _("{B_DEF_NAME_WITH_PREFIX}의 {B_DEF_ABILITY} 때문에\n{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\l{B_CURRENT_MOVE}{B_TXT_EULREUL} 할 수 없다!");
static const u8 sText_PkmnRestoredHPUsing[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_DEF_ABILITY}{B_TXT_EU}로 인해 회복했다!");
static const u8 sText_PkmnsXMadeYUseless[] = _("{B_DEF_NAME_WITH_PREFIX}의 {B_DEF_ABILITY} 때문에\n{B_CURRENT_MOVE}{B_TXT_EUNNEUN} 효과가 없었다!"); // §たの §のでｎ§とは こうかが なかった!
static const u8 sText_PkmnChangedTypeWith[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_ABILITY} 때문에\n{B_BUFF1}타입이 되었다!"); // §たは §のでｎ§ タイプに なった!
static const u8 sText_PkmnPreventsParalysisWith[] = _("{B_EFF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_ABILITY}\n때문에 마비되지 않는다!"); // §ちは §のでｎまひしない!
static const u8 sText_PkmnPreventsRomanceWith[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_ABILITY} 때문에\n헤롱헤롱해지지 않는다!");
static const u8 sText_PkmnPreventsPoisoningWith[] = _("{B_EFF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_DEF_ABILITY} 때문에\l독에 걸리지 않는다!");
static const u8 sText_PkmnPreventsConfusionWith[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_ABILITY}\n때문에 혼란되지 않는다!");
static const u8 sText_PkmnRaisedFirePowerWith[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_ABILITY} 때문에\n불꽃의 위력이 올라갔다!");
static const u8 sText_PkmnAnchorsItselfWith[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_ABILITY} 때문에\n들러붙어 있다!");
static const u8 sText_PkmnCutsAttackWith[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 {B_SCR_ACTIVE_ABILITY} 때문에\n{B_DEF_NAME_WITH_PREFIX}의 공격이 떨어졌다!");
static const u8 sText_PkmnPreventsStatLossWith[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_SCR_ACTIVE_ABILITY} 때문에\n능력이 떨어지지 않는다!");
static const u8 sText_PkmnHurtsWith[] = _("{B_DEF_NAME_WITH_PREFIX}의 {B_DEF_ABILITY} 때문에\n{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 상처를 입었다!");
static const u8 sText_PkmnTraced[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_BUFF1}의\n{B_BUFF2}{B_TXT_EULREUL} 트레이스했다!");
static const u8 sText_PkmnsXPreventsBurns[] = _("{B_EFF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_EFF_ABILITY} 때문에\n화상을 입지 않는다!");
static const u8 sText_PkmnsXBlocksY[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_ABILITY} 때문에\n{B_CURRENT_MOVE}{B_TXT_EULREUL} 받지 않는다!");
static const u8 sText_PkmnsXBlocksY2[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_SCR_ACTIVE_ABILITY} 때문에\l{B_CURRENT_MOVE}{B_TXT_EULREUL} 받지 않는다!");
static const u8 sText_PkmnsXRestoredHPALittle2[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_ATK_ABILITY}{B_TXT_EU}로 인해 조금 회복했다");
static const u8 sText_PkmnsXWhippedUpSandstorm[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 {B_SCR_ACTIVE_ABILITY}\n때문에 모래바람이 불었다!");
static const u8 sText_PkmnsXIntensifiedSun[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 {B_SCR_ACTIVE_ABILITY}\n때문에 햇살이 강해졌다!");
static const u8 sText_PkmnsXPreventsYLoss[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_SCR_ACTIVE_ABILITY} 때문에\n{B_BUFF1}{B_TXT_IGA} 떨어지지 않는다!");
static const u8 sText_PkmnsXInfatuatedY[] = _("{B_DEF_NAME_WITH_PREFIX}의 {B_DEF_ABILITY}\n때문에 {B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 헤롱헤롱해졌다!");
static const u8 sText_PkmnsXMadeYIneffective[] = _("{B_DEF_NAME_WITH_PREFIX}의\n{B_DEF_ABILITY} 때문에\l{B_CURRENT_MOVE}{B_TXT_EUNNEUN} 효과가 없다!");
static const u8 sText_PkmnsXCuredYProblem[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_SCR_ACTIVE_ABILITY} 때문에\n{B_BUFF1}상태가 나았다!");
static const u8 sText_ItSuckedLiquidOoze[] = _("해감액을 흡수했다!"); // ヘドロえきを すいとった!
static const u8 sText_PkmnTransformed[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 모습이\n변화했다!"); // §ての すがたがｎへんかした!
static const u8 sText_PkmnsXTookAttack[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_DEF_ABILITY} 때문에\n공격을 받았다!"); // §たは §のでｎこうげきを うけた!
const u8 gText_PkmnsXPreventsSwitching[] = _("{B_BUFF1}의 {B_LAST_ABILITY} 때문에\n{B_BUFF2}{B_TXT_EULREUL} 불러들일 수 없다!\p"); // § の §ぬでｎ§あを もどすことが できない!ｐ
static const u8 sText_PreventedFromWorking[] = _("{B_DEF_NAME_WITH_PREFIX}의\n{B_DEF_ABILITY} 때문에\l{B_SCR_ACTIVE_NAME_WITH_PREFIX}의\l{B_BUFF1}{B_TXT_EUNNEUN} 효과가 없었다!"); // §たの §のでｎ§ての § は きかなかった!
static const u8 sText_PkmnsXMadeItIneffective[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 {B_SCR_ACTIVE_ABILITY}\n때문에 실패했다!");
static const u8 sText_PkmnsXPreventsFlinching[] = _("{B_EFF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_EFF_ABILITY}\n때문에 풀이 죽지 않는다!");
static const u8 sText_PkmnsXPreventsYsZ[] = _("{B_ATK_NAME_WITH_PREFIX}의 {B_ATK_ABILITY}{B_TXT_EUNNEUN}\n{B_DEF_NAME_WITH_PREFIX}의\l{B_DEF_ABILITY} 때문에 효과가 없었다!");
static const u8 sText_PkmnsXCuredItsYProblem[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_SCR_ACTIVE_ABILITY} 때문에\n{B_BUFF1}상태가 나았다!");
static const u8 sText_PkmnsXHadNoEffectOnY[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 {B_SCR_ACTIVE_ABILITY}{B_TXT_EUNNEUN}\n{B_EFF_NAME_WITH_PREFIX}에게는 효과가 없었다!");
static const u8 sText_StatSharply[] = _("크게 ");
const u8 gText_StatRose[] = _("올라갔다!");
static const u8 sText_StatHarshly[] = _("매우 크게 ");
static const u8 sText_StatFell[] = _("떨어졌다!");
static const u8 sText_PkmnsStatChanged[] = _("{B_ATK_NAME_WITH_PREFIX}의\n{B_BUFF1}{B_TXT_IGA} {B_BUFF2}");
const u8 gText_PkmnsStatChanged2[] = _("{B_DEF_NAME_WITH_PREFIX}의\n{B_BUFF1}{B_TXT_IGA} {B_BUFF2}");
static const u8 sText_UsingXTheYOfZN[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n{B_BUFF1}{B_TXT_IGA} {B_BUFF2}"); // §ては §にでｎ§ が §あ
static const u8 sText_PkmnsStatChanged3[] = _("{B_ATK_NAME_WITH_PREFIX}의\n{B_BUFF1}{B_TXT_IGA} {B_BUFF2}");
static const u8 sText_PkmnsStatChanged4[] = _("{B_DEF_NAME_WITH_PREFIX}의\n{B_BUFF1}{B_TXT_IGA} {B_BUFF2}");
static const u8 sText_StatsWontIncrease2[] = _("{B_ATK_NAME_WITH_PREFIX}의 능력은\n더 올라가지 않는다!"); // §その のうりょくはｎもう あがらない!
static const u8 sText_StatsWontDecrease2[] = _("{B_DEF_NAME_WITH_PREFIX}의 능력은\n더 떨어지지 않는다!"); // §たの のうりょくはｎもう さがらない!
static const u8 sText_CriticalHit[] = _("급소에 맞았다!"); // きゅうしょに あたった!
static const u8 sText_OneHitKO[] = _("일격필살!"); // いちげき ひっさつ!
static const u8 sText_123Poof[] = _("{PAUSE 32}1, {PAUSE 15}2, {PAUSE 15}... {PAUSE 15}... {PAUSE 15}... {PLAY_SE 0x0038}짠!\p"); // ©くみ1 ©くそ2の ©くそ…©くそ…©くそ… ©くそ©たぎ ポカン!ｐ
static const u8 sText_AndEllipsis[] = _("그리고...!\p");
static const u8 sText_HMMovesCantBeForgotten[] = _("중요한 기술입니다!\n잊게 할 수 없습니다!\p"); // それは たいせつな わざですｎわすれさせることは できません!ｐ
static const u8 sText_NotVeryEffective[] = _("효과가 별로인 듯하다"); // こうかは いまひとつの ようだ
static const u8 sText_SuperEffective[] = _("효과가 굉장했다!"); // こうかは ばつぐんだ!
static const u8 sText_GotAwaySafely[] = _("{PLAY_SE 0x0011}무사히 도망쳤다!\p"); // ©たち うまく にげきれた!
static const u8 sText_PkmnFledUsingIts[] = _("{PLAY_SE 0x0011}{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 가지고 있던\n{B_LAST_ITEM}{B_TXT_EULREUL} 써서 도망쳤다\p");
static const u8 sText_PkmnFledUsing[] = _("{PLAY_SE 0x0011}{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_ATK_ABILITY}{B_TXT_EULREUL} 써서 도망쳤다\p");
static const u8 sText_WildPkmnFled[] = _("{PLAY_SE 0x0011}야생 {B_BUFF1}{B_TXT_EUNNEUN} 도망쳤다!");
static const u8 sText_PlayerDefeatedLinkTrainer[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_WAGWA}의\n승부에서 이겼다!");
static const u8 sText_TwoLinkTrainersDefeated[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_WAGWA}\n{B_LINK_OPPONENT2_NAME}{B_TXT_WAGWA}의\l승부에서 이겼다!");
static const u8 sText_PlayerLostAgainstLinkTrainer[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_WAGWA}의\n승부에서 졌다!");
static const u8 sText_PlayerLostToTwo[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_WAGWA}\n{B_LINK_OPPONENT2_NAME}{B_TXT_WAGWA}의\l승부에서 졌다!");
static const u8 sText_PlayerBattledToDrawLinkTrainer[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_WAGWA}의\n승부에서 비겼다!");
static const u8 sText_PlayerBattledToDrawVsTwo[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_WAGWA}\n{B_LINK_OPPONENT2_NAME}{B_TXT_WAGWA}의\l승부에서 비겼다!");
static const u8 sText_WildFled[] = _("{PLAY_SE 0x0011}{B_LINK_OPPONENT1_NAME}{B_TXT_EUNNEUN} 도망쳤다!");
static const u8 sText_TwoWildFled[] = _("{PLAY_SE 0x0011}{B_LINK_OPPONENT1_NAME}{B_TXT_WAGWA} {B_LINK_OPPONENT2_NAME}{B_TXT_EUNNEUN}\n도망쳤다!");
static const u8 sText_NoRunningFromTrainers[] = _("안돼! 승부 도중에\n상대에게 등을 보일 순 없어!\p");
static const u8 sText_CantEscape[] = _("도망칠 수 없다!\p");
static const u8 sText_DontLeaveBirch[] = _("털보박사: 외, 외면하지 말아줘-!\p");
static const u8 sText_ButNothingHappened[] = _("그러나 아무 일도 일어나지 않았다");
static const u8 sText_ButItFailed[] = _("그러나 실패하고 말았다!");
static const u8 sText_ItHurtConfusion[] = _("영문도 모른 채\n자신을 공격했다!");
static const u8 sText_MirrorMoveFailed[] = _("그러나 따라하기는\n실패로 끝났다!");
static const u8 sText_StartedToRain[] = _("비가 내리기 시작했다!");
static const u8 sText_DownpourStarted[] = _("폭우로 변했다!");
static const u8 sText_RainContinues[] = _("비가 계속 내리고 있다");
static const u8 sText_DownpourContinues[] = _("폭우가 계속 내리고 있다");
static const u8 sText_RainStopped[] = _("비가 그쳤다!");
static const u8 sText_SandstormBrewed[] = _("모래바람이 불기 시작했다!");
static const u8 sText_SandstormRages[] = _("모래바람이 세차게 분다");
static const u8 sText_SandstormSubsided[] = _("모래바람이 가라앉았다!");
static const u8 sText_SunlightGotBright[] = _("햇살이 강해졌다!");
static const u8 sText_SunlightStrong[] = _("햇살이 강하다");
static const u8 sText_SunlightFaded[] = _("햇살이 약해졌다!");
static const u8 sText_StartedHail[] = _("싸라기눈이 내리기 시작했다!");
static const u8 sText_HailContinues[] = _("싸라기눈이 계속 내리고 있다");
static const u8 sText_HailStopped[] = _("싸라기눈이 그쳤다!");
static const u8 sText_FailedToSpitUp[] = _("그러나 아무것도 토해낼 수 없었다!");
static const u8 sText_FailedToSwallow[] = _("그러나 아무것도 꿀꺽할 수 없었다!");
static const u8 sText_WindBecameHeatWave[] = _("바람은 열풍이 되었다!");
static const u8 sText_StatChangesGone[] = _("모든 상태가\n원래대로 되돌아왔다!");
static const u8 sText_CoinsScattered[] = _("돈이 주위에 흩어졌다!");
static const u8 sText_TooWeakForSubstitute[] = _("그러나 분신을 쓰기에는\n체력이 부족했다!");
static const u8 sText_SharedPain[] = _("서로의 체력을 나누어 가졌다!");
static const u8 sText_BellChimed[] = _("방울소리가 울려 퍼졌다!");
static const u8 sText_FaintInThree[] = _("멸망의노래를 들은 포켓몬은\n3턴 후에 쓰러져 버린다!");
static const u8 sText_NoPPLeft[] = _("남은 기술 포인트가 없다!\p");
static const u8 sText_ButNoPPLeft[] = _("그러나\n남은 기술 포인트가 없었다!");
static const u8 sText_PkmnIgnoresAsleep[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 잠든 채로\n명령을 무시했다!");
static const u8 sText_PkmnIgnoredOrders[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 명령을 무시했다!");
static const u8 sText_PkmnBeganToNap[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 낮잠을 자기 시작했다!");
static const u8 sText_PkmnLoafing[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 게으름을 피우고 있다!");
static const u8 sText_PkmnWontObey[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 말을 듣지 않는다!");
static const u8 sText_PkmnTurnedAway[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 외면했다!");
static const u8 sText_PkmnPretendNotNotice[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 모른 체했다!");
static const u8 sText_EnemyAboutToSwitchPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_EUNNEUN}\n{B_BUFF2}{B_TXT_EULREUL} 내보내려 하고 있다\p{B_PLAYER_NAME}도 포켓몬을\n교체하겠습니까?");
static const u8 sText_PkmnLearnedMove2[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_EULREUL} 배웠다!");
static const u8 sText_PlayerDefeatedLinkTrainerTrainer1[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_WAGWA}의\n승부에서 이겼다!\p");
static const u8 sText_CreptCloser[] = _("{B_PLAYER_NAME}{B_TXT_EUNNEUN}\n{B_OPPONENT_MON1_NAME}에게 다가갔다!");
static const u8 sText_CantGetCloser[] = _("{B_PLAYER_NAME}{B_TXT_EUNNEUN}\n더 이상 다가갈 수 없다!");
static const u8 sText_PkmnWatchingCarefully[] = _("{B_OPPONENT_MON1_NAME}{B_TXT_EUNNEUN}\n상황을 살피고 있다!");
static const u8 sText_PkmnCuriousAboutX[] = _("{B_OPPONENT_MON1_NAME}{B_TXT_EUNNEUN}\n{B_BUFF1}에 대해 관심을 가졌다!");
static const u8 sText_PkmnEnthralledByX[] = _("{B_OPPONENT_MON1_NAME}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_IGA} 마음에 들었다!");
static const u8 sText_PkmnIgnoredX[] = _("{B_OPPONENT_MON1_NAME}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_EULREUL} 무시했다!");
static const u8 sText_ThrewPokeblockAtPkmn[] = _("{B_PLAYER_NAME}{B_TXT_EUNNEUN}\n{B_OPPONENT_MON1_NAME}에게 포켓몬스넥을 던졌다!");
static const u8 sText_OutOfSafariBalls[] = _("{PLAY_SE 0x0049}방송: 딩동!\n사파리볼을 다 썼으므로\l종료합니다!\p"); // アナウンス『ピンポ-ン! サファリボ-ルがｎなくなったので しゅうりょうで-す!ｐ
static const u8 sText_OpponentMon1Appeared[] = _("{B_OPPONENT_MON1_NAME}{B_TXT_IGA} 튀어나왔다!\p");
static const u8 sText_WildPkmnAppeared[] = _("앗! 야생 {B_OPPONENT_MON1_NAME}{B_TXT_IGA} 튀어나왔다!\p");
static const u8 sText_WildPkmnAppeared2[] = _("앗! 야생 {B_OPPONENT_MON1_NAME}{B_TXT_IGA} 나타났다!\p");
static const u8 sText_WildPkmnAppearedPause[] = _("앗! 야생 {B_OPPONENT_MON1_NAME}{B_TXT_IGA} 튀어나왔다!\p{PAUSE 127}");
static const u8 sText_TwoWildPkmnAppeared[] = _("앗! 야생 {B_OPPONENT_MON1_NAME}{B_TXT_WAGWA}\n{B_OPPONENT_MON2_NAME}{B_TXT_IGA} 튀어나왔다!\p");
static const u8 sText_Trainer1WantsToBattle[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_IGA}\n승부를 걸어왔다!\p");
static const u8 sText_LinkTrainerWantsToBattle[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_IGA}\n승부를 걸어왔다!");
static const u8 sText_TwoLinkTrainersWantToBattle[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_WAGWA} {B_LINK_OPPONENT2_NAME}{B_TXT_IGA}\n승부를 걸어왔다!");
static const u8 sText_Trainer1SentOutPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_EUNNEUN}\n{B_OPPONENT_MON1_NAME}{B_TXT_EULREUL} 내보냈다!");
static const u8 sText_Trainer1SentOutTwoPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_EUNNEUN}\n{B_OPPONENT_MON1_NAME}{B_TXT_WAGWA} {B_OPPONENT_MON2_NAME}{B_TXT_EULREUL} 내보냈다!");
static const u8 sText_Trainer1SentOutPkmn2[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_EULREUL} 내보냈다!");
static const u8 sText_LinkTrainerSentOutPkmn[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_EUNNEUN}\n{B_OPPONENT_MON1_NAME}{B_TXT_EULREUL} 내보냈다!");
static const u8 sText_LinkTrainerSentOutTwoPkmn[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_EUNNEUN}\n{B_OPPONENT_MON1_NAME}{B_TXT_WAGWA} {B_OPPONENT_MON2_NAME}{B_TXT_EULREUL} 내보냈다!");
static const u8 sText_TwoLinkTrainersSentOutPkmn[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_EUNNEUN}\n{B_LINK_OPPONENT_MON1_NAME}{B_TXT_EULREUL} 내보냈다!\p{B_LINK_OPPONENT2_NAME}{B_TXT_EUNNEUN}\n{B_LINK_OPPONENT_MON2_NAME}{B_TXT_EULREUL} 내보냈다!");
static const u8 sText_LinkTrainerSentOutPkmn2[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_EULREUL} 내보냈다!");
static const u8 sText_LinkTrainerMultiSentOutPkmn[] = _("{B_LINK_SCR_TRAINER_NAME}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_EULREUL} 내보냈다!");
static const u8 sText_GoPkmn[] = _("가랏! {B_PLAYER_MON1_NAME}!");
static const u8 sText_GoTwoPkmn[] = _("가랏! {B_PLAYER_MON1_NAME}! {B_PLAYER_MON2_NAME}!");
static const u8 sText_GoPkmn2[] = _("가랏! {B_BUFF1}!");
static const u8 sText_DoItPkmn[] = _("널 믿어! {B_BUFF1}!");
static const u8 sText_GoForItPkmn[] = _("힘내! {B_BUFF1}!");
static const u8 sText_YourFoesWeakGetEmPkmn[] = _("상대가 약해져 있어!\n기회다! {B_BUFF1}!"); // あいてが よわっている!ｎチャンスだ! § !
static const u8 sText_LinkPartnerSentOutPkmnGoPkmn[] = _("{B_LINK_PARTNER_NAME}{B_TXT_EUNNEUN}\n{B_LINK_PLAYER_MON2_NAME}{B_TXT_EULREUL} 내보냈다!\l가랏! {B_LINK_PLAYER_MON1_NAME}!");
static const u8 sText_PkmnThatsEnough[] = _("{B_BUFF1} 교대!\n돌아와!"); // §  もういい!ｎもどれ!
static const u8 sText_PkmnComeBack[] = _("{B_BUFF1}\n돌아와!"); // § ｎもどれ!
static const u8 sText_PkmnOkComeBack[] = _("{B_BUFF1} 좋았어!\n돌아와!"); // §  いいぞ!ｎもどれ!
static const u8 sText_PkmnGoodComeBack[] = _("{B_BUFF1} 잘했어!\n돌아와!"); // §  よくやった!ｎもどれ!
static const u8 sText_Trainer1WithdrewPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_EULREUL} 넣어버렸다!");
static const u8 sText_LinkTrainer1WithdrewPkmn[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_EULREUL} 넣어버렸다!");
static const u8 sText_LinkTrainer2WithdrewPkmn[] = _("{B_LINK_SCR_TRAINER_NAME}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_EULREUL} 넣어버렸다!");
static const u8 sText_WildPkmnPrefix[] = _("야생 "); // やせいの 
static const u8 sText_FoePkmnPrefix[] = _("상대 "); // あいての 
static const u8 sText_EmptyString8[] = _("");
static const u8 sText_FoePkmnPrefix2[] = _("상대"); // あいての
static const u8 sText_AllyPkmnPrefix[] = _("우리 편"); // みかたの
static const u8 sText_FoePkmnPrefix3[] = _("상대는"); // あいては
static const u8 sText_AllyPkmnPrefix2[] = _("우리 편은"); // みかたは
static const u8 sText_FoePkmnPrefix4[] = _("상대를"); // あいてを
static const u8 sText_AllyPkmnPrefix3[] = _("우리 편을"); // みかたを
static const u8 sText_AttackerUsedX[] = _("{B_ATK_NAME_WITH_PREFIX}{B_BUFF1}\n{B_BUFF2}"); // §そ§ ｎ§あ
static const u8 sText_ExclamationMark[] = _("{B_TXT_EULREUL} 썼다!"); // を つかった!
static const u8 sText_ExclamationMark2[] = _("{B_TXT_EULREUL} 썼다!"); // した!
static const u8 sText_ExclamationMark3[] = _("{B_TXT_EULREUL} 썼다!"); // を した!
static const u8 sText_ExclamationMark4[] = _(" 공격!"); //  こうげき!
static const u8 sText_ExclamationMark5[] = _("!"); // !
static const u8 sText_HP2[] = _("체력"); // たいりょく
static const u8 sText_Attack2[] = _("공격"); // こうげきりょく
static const u8 sText_Defense2[] = _("방어"); // ぼうぎょりょく
static const u8 sText_Speed[] = _("스피드"); // すばやさ
static const u8 sText_SpAtk2[] = _("특수공격"); // とくこう
static const u8 sText_SpDef2[] = _("특수방어"); // とくぼう
static const u8 sText_Accuracy[] = _("명중률"); // めいちゅうりつ
static const u8 sText_Evasiveness[] = _("회피율"); // かいひりつ

const u8 * const gStatNamesTable[NUM_BATTLE_STATS] =
{
    [STAT_HP]      = sText_HP2,
    [STAT_ATK]     = sText_Attack2,
    [STAT_DEF]     = sText_Defense2,
    [STAT_SPEED]   = sText_Speed,
    [STAT_SPATK]   = sText_SpAtk2,
    [STAT_SPDEF]   = sText_SpDef2,
    [STAT_ACC]     = sText_Accuracy,
    [STAT_EVASION] = sText_Evasiveness,
};

static const u8 sText_PokeblockWasTooSpicy[] = _("너무 맵다!");
static const u8 sText_PokeblockWasTooDry[] = _("너무 떫다!");
static const u8 sText_PokeblockWasTooSweet[] = _("너무 달다!");
static const u8 sText_PokeblockWasTooBitter[] = _("너무 쓰다!");
static const u8 sText_PokeblockWasTooSour[] = _("너무 시다!");

const u8 * const gPokeblockWasTooXStringTable[FLAVOR_COUNT] =
{
    [FLAVOR_SPICY]  = sText_PokeblockWasTooSpicy,
    [FLAVOR_DRY]    = sText_PokeblockWasTooDry,
    [FLAVOR_SWEET]  = sText_PokeblockWasTooSweet,
    [FLAVOR_BITTER] = sText_PokeblockWasTooBitter,
    [FLAVOR_SOUR]   = sText_PokeblockWasTooSour
};

static const u8 sText_PlayerUsedItem[] = _("{B_PLAYER_NAME}{B_TXT_EUNNEUN}\n{B_LAST_ITEM}{B_TXT_EULREUL} 썼다!");
static const u8 sText_WallyUsedItem[] = _("민진은\n{B_LAST_ITEM}{B_TXT_EULREUL} 썼다!");
static const u8 sText_Trainer1UsedItem[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_EUNNEUN}\n{B_LAST_ITEM}{B_TXT_EULREUL} 썼다!");
static const u8 sText_TrainerBlockedBall[] = _("트레이너가 볼을 튕겨내 버렸다!");
static const u8 sText_DontBeAThief[] = _("남의 것에 손대면 도둑!");
static const u8 sText_ItDodgedBall[] = _("피했다!\n이 녀석은 잡힐 것 같지 않군!");
static const u8 sText_YouMissedPkmn[] = _("포켓몬에게\n제대로 맞지 않았다!");
static const u8 sText_PkmnBrokeFree[] = _("안돼! 포켓몬이\n볼에서 나와버렸다!");
static const u8 sText_ItAppearedCaught[] = _("아아!\n잡았다고 생각했는데!");
static const u8 sText_AarghAlmostHadIt[] = _("아쉽다!\n조금만 더하면 잡을 수 있었는데!");
static const u8 sText_ShootSoClose[] = _("아깝다!\n조금만 더하면 됐는데!");
static const u8 sText_GotchaPkmnCaught[] = _("신난다-!\n{B_OPPONENT_MON1_NAME}{B_TXT_EULREUL} 붙잡았다!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}\p");
static const u8 sText_GotchaPkmnCaught2[] = _("신난다-!\n{B_OPPONENT_MON1_NAME}{B_TXT_EULREUL} 붙잡았다!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}{PAUSE 127}");
static const u8 sText_GiveNicknameCaptured[] = _("잡은 {B_OPPONENT_MON1_NAME}에게\n닉네임을 붙이겠습니까?");
static const u8 sText_PkmnSentToPC[] = _("{B_OPPONENT_MON1_NAME}{B_TXT_EUNNEUN}\n{B_PC_CREATOR_NAME} PC로 전송되었다!");
static const u8 sText_Someones[] = _("누군가의");
static const u8 sText_Lanettes[] = _("유미의");
static const u8 sText_PkmnDataAddedToDex[] = _("{B_OPPONENT_MON1_NAME}의 데이터가 새로\n포켓몬 도감에 등록됩니다!\p");
static const u8 sText_ItIsRaining[] = _("비가 내리고 있다");
static const u8 sText_SandstormIsRaging[] = _("모래바람이 세차게 불고 있다");
static const u8 sText_BoxIsFull[] = _("박스가 가득 찼습니다!\n더 이상 잡을 수 없습니다!\p");
static const u8 sText_EnigmaBerry[] = _("의문열매");
static const u8 sText_BerrySuffix[] = _("열매");
static const u8 sText_PkmnsItemCuredParalysis[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n마비가 풀렸다!"); // ては §にでｎまひが なおった!
static const u8 sText_PkmnsItemCuredPoison[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n독이 해독됐다!"); // §ては §にでｎどくが なおった!
static const u8 sText_PkmnsItemHealedBurn[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n화상이 나았다!"); // §ては §にでｎやけどが なおった!
static const u8 sText_PkmnsItemDefrostedIt[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n얼음상태가 나았다!"); // §ては §にでｎこおりじょうたいが なおった!
static const u8 sText_PkmnsItemWokeIt[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n잠에서 깼다!"); // §ては §にでｎねむりから さめた!
static const u8 sText_PkmnsItemSnappedOut[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n혼란이 풀렸다!"); // §ては §にでｎこんらんが なおった!
static const u8 sText_PkmnsItemCuredProblem[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n{B_BUFF1}상태가 나았다!"); // §ては §にでｎ§ じょうたいが なおった!
static const u8 sText_PkmnsItemNormalizedStatus[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n상태이상이 나았다!"); // §ては §にでｎじょうたいいじょうが なおった!
static const u8 sText_PkmnsItemRestoredHealth[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n체력을 회복했다!"); // §ては §にでｎたいりょくを かいふくした!
static const u8 sText_PkmnsItemRestoredPP[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n{B_BUFF1}의 PP를 회복했다!"); // §ては §にでｎ§ の わざポイントを かいふくした!
static const u8 sText_PkmnsItemRestoredStatus[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n상태를 원래대로 되돌렸다!"); // §ては §にでｎステ-タスを もとに もどした!
static const u8 sText_PkmnsItemRestoredHPALittle[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n조금 회복했다"); // §ては §にでｎすこし かいふく
static const u8 sText_ItemAllowsOnlyYMove[] = _("{B_LAST_ITEM}의 효과로\n{B_CURRENT_MOVE}밖에 쓸 수 없다!\p"); // §にの こうかでｎ§としか だすことができない!ｐ
static const u8 sText_PkmnHungOnWithX[] = _("{B_DEF_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} {B_LAST_ITEM}{B_TXT_EU}로\n버텼다!"); // §たは §にでｎもちこたえた!
const u8 gText_EmptyString3[] = _(" ");
static const u8 sText_YouThrowABallNowRight[] = _("여기서 볼을 던지는 거군요\n저... 해볼게요!"); // ここで ボ-ルを なげるんだねｎぼく…… やってみるよ!

// early declaration of strings
static const u8 sText_PkmnIncapableOfPower[];
static const u8 sText_GlintAppearsInEye[];
static const u8 sText_PkmnGettingIntoPosition[];
static const u8 sText_PkmnBeganGrowlingDeeply[];
static const u8 sText_PkmnEagerForMore[];
static const u8 sText_DefeatedOpponentByReferee[];
static const u8 sText_LostToOpponentByReferee[];
static const u8 sText_TiedOpponentByReferee[];
static const u8 sText_QuestionForfeitMatch[];
static const u8 sText_ForfeitedMatch[];
static const u8 sText_Trainer1WinText[];
static const u8 sText_Trainer2WinText[];
static const u8 sText_TwoInGameTrainersDefeated[];
static const u8 sText_Trainer2LoseText[];

const u8 * const gBattleStringsTable[BATTLESTRINGS_COUNT] =
{
    [STRINGID_TRAINER1LOSETEXT - 12] = sText_Trainer1LoseText,
    [STRINGID_PKMNGAINEDEXP - 12] = sText_PkmnGainedEXP,
    [STRINGID_PKMNGREWTOLV - 12] = sText_PkmnGrewToLv,
    [STRINGID_PKMNLEARNEDMOVE - 12] = sText_PkmnLearnedMove,
    [STRINGID_TRYTOLEARNMOVE1 - 12] = sText_TryToLearnMove1,
    [STRINGID_TRYTOLEARNMOVE2 - 12] = sText_TryToLearnMove2,
    [STRINGID_TRYTOLEARNMOVE3 - 12] = sText_TryToLearnMove3,
    [STRINGID_PKMNFORGOTMOVE - 12] = sText_PkmnForgotMove,
    [STRINGID_STOPLEARNINGMOVE - 12] = sText_StopLearningMove,
    [STRINGID_DIDNOTLEARNMOVE - 12] = sText_DidNotLearnMove,
    [STRINGID_PKMNLEARNEDMOVE2 - 12] = sText_PkmnLearnedMove2,
    [STRINGID_ATTACKMISSED - 12] = sText_AttackMissed,
    [STRINGID_PKMNPROTECTEDITSELF - 12] = sText_PkmnProtectedItself,
    [STRINGID_STATSWONTINCREASE2 - 12] = sText_StatsWontIncrease2,
    [STRINGID_AVOIDEDDAMAGE - 12] = sText_AvoidedDamage,
    [STRINGID_ITDOESNTAFFECT - 12] = sText_ItDoesntAffect,
    [STRINGID_ATTACKERFAINTED - 12] = sText_AttackerFainted,
    [STRINGID_TARGETFAINTED - 12] = sText_TargetFainted,
    [STRINGID_PLAYERGOTMONEY - 12] = sText_PlayerGotMoney,
    [STRINGID_PLAYERWHITEOUT - 12] = sText_PlayerWhiteout,
    [STRINGID_PLAYERWHITEOUT2 - 12] = sText_PlayerWhiteout2,
    [STRINGID_PREVENTSESCAPE - 12] = sText_PreventsEscape,
    [STRINGID_HITXTIMES - 12] = sText_HitXTimes,
    [STRINGID_PKMNFELLASLEEP - 12] = sText_PkmnFellAsleep,
    [STRINGID_PKMNMADESLEEP - 12] = sText_PkmnMadeSleep,
    [STRINGID_PKMNALREADYASLEEP - 12] = sText_PkmnAlreadyAsleep,
    [STRINGID_PKMNALREADYASLEEP2 - 12] = sText_PkmnAlreadyAsleep2,
    [STRINGID_PKMNWASNTAFFECTED - 12] = sText_PkmnWasntAffected,
    [STRINGID_PKMNWASPOISONED - 12] = sText_PkmnWasPoisoned,
    [STRINGID_PKMNPOISONEDBY - 12] = sText_PkmnPoisonedBy,
    [STRINGID_PKMNHURTBYPOISON - 12] = sText_PkmnHurtByPoison,
    [STRINGID_PKMNALREADYPOISONED - 12] = sText_PkmnAlreadyPoisoned,
    [STRINGID_PKMNBADLYPOISONED - 12] = sText_PkmnBadlyPoisoned,
    [STRINGID_PKMNENERGYDRAINED - 12] = sText_PkmnEnergyDrained,
    [STRINGID_PKMNWASBURNED - 12] = sText_PkmnWasBurned,
    [STRINGID_PKMNBURNEDBY - 12] = sText_PkmnBurnedBy,
    [STRINGID_PKMNHURTBYBURN - 12] = sText_PkmnHurtByBurn,
    [STRINGID_PKMNWASFROZEN - 12] = sText_PkmnWasFrozen,
    [STRINGID_PKMNFROZENBY - 12] = sText_PkmnFrozenBy,
    [STRINGID_PKMNISFROZEN - 12] = sText_PkmnIsFrozen,
    [STRINGID_PKMNWASDEFROSTED - 12] = sText_PkmnWasDefrosted,
    [STRINGID_PKMNWASDEFROSTED2 - 12] = sText_PkmnWasDefrosted2,
    [STRINGID_PKMNWASDEFROSTEDBY - 12] = sText_PkmnWasDefrostedBy,
    [STRINGID_PKMNWASPARALYZED - 12] = sText_PkmnWasParalyzed,
    [STRINGID_PKMNWASPARALYZEDBY - 12] = sText_PkmnWasParalyzedBy,
    [STRINGID_PKMNISPARALYZED - 12] = sText_PkmnIsParalyzed,
    [STRINGID_PKMNISALREADYPARALYZED - 12] = sText_PkmnIsAlreadyParalyzed,
    [STRINGID_PKMNHEALEDPARALYSIS - 12] = sText_PkmnHealedParalysis,
    [STRINGID_PKMNDREAMEATEN - 12] = sText_PkmnDreamEaten,
    [STRINGID_STATSWONTINCREASE - 12] = sText_StatsWontIncrease,
    [STRINGID_STATSWONTDECREASE - 12] = sText_StatsWontDecrease,
    [STRINGID_TEAMSTOPPEDWORKING - 12] = sText_TeamStoppedWorking,
    [STRINGID_FOESTOPPEDWORKING - 12] = sText_FoeStoppedWorking,
    [STRINGID_PKMNISCONFUSED - 12] = sText_PkmnIsConfused,
    [STRINGID_PKMNHEALEDCONFUSION - 12] = sText_PkmnHealedConfusion,
    [STRINGID_PKMNWASCONFUSED - 12] = sText_PkmnWasConfused,
    [STRINGID_PKMNALREADYCONFUSED - 12] = sText_PkmnAlreadyConfused,
    [STRINGID_PKMNFELLINLOVE - 12] = sText_PkmnFellInLove,
    [STRINGID_PKMNINLOVE - 12] = sText_PkmnInLove,
    [STRINGID_PKMNIMMOBILIZEDBYLOVE - 12] = sText_PkmnImmobilizedByLove,
    [STRINGID_PKMNBLOWNAWAY - 12] = sText_PkmnBlownAway,
    [STRINGID_PKMNCHANGEDTYPE - 12] = sText_PkmnChangedType,
    [STRINGID_PKMNFLINCHED - 12] = sText_PkmnFlinched,
    [STRINGID_PKMNREGAINEDHEALTH - 12] = sText_PkmnRegainedHealth,
    [STRINGID_PKMNHPFULL - 12] = sText_PkmnHPFull,
    [STRINGID_PKMNRAISEDSPDEF - 12] = sText_PkmnRaisedSpDef,
    [STRINGID_PKMNRAISEDDEF - 12] = sText_PkmnRaisedDef,
    [STRINGID_PKMNCOVEREDBYVEIL - 12] = sText_PkmnCoveredByVeil,
    [STRINGID_PKMNUSEDSAFEGUARD - 12] = sText_PkmnUsedSafeguard,
    [STRINGID_PKMNSAFEGUARDEXPIRED - 12] = sText_PkmnSafeguardExpired,
    [STRINGID_PKMNWENTTOSLEEP - 12] = sText_PkmnWentToSleep,
    [STRINGID_PKMNSLEPTHEALTHY - 12] = sText_PkmnSleptHealthy,
    [STRINGID_PKMNWHIPPEDWHIRLWIND - 12] = sText_PkmnWhippedWhirlwind,
    [STRINGID_PKMNTOOKSUNLIGHT - 12] = sText_PkmnTookSunlight,
    [STRINGID_PKMNLOWEREDHEAD - 12] = sText_PkmnLoweredHead,
    [STRINGID_PKMNISGLOWING - 12] = sText_PkmnIsGlowing,
    [STRINGID_PKMNFLEWHIGH - 12] = sText_PkmnFlewHigh,
    [STRINGID_PKMNDUGHOLE - 12] = sText_PkmnDugHole,
    [STRINGID_PKMNSQUEEZEDBYBIND - 12] = sText_PkmnSqueezedByBind,
    [STRINGID_PKMNTRAPPEDINVORTEX - 12] = sText_PkmnTrappedInVortex,
    [STRINGID_PKMNWRAPPEDBY - 12] = sText_PkmnWrappedBy,
    [STRINGID_PKMNCLAMPED - 12] = sText_PkmnClamped,
    [STRINGID_PKMNHURTBY - 12] = sText_PkmnHurtBy,
    [STRINGID_PKMNFREEDFROM - 12] = sText_PkmnFreedFrom,
    [STRINGID_PKMNCRASHED - 12] = sText_PkmnCrashed,
    [STRINGID_PKMNSHROUDEDINMIST - 12] = gText_PkmnShroudedInMist,
    [STRINGID_PKMNPROTECTEDBYMIST - 12] = sText_PkmnProtectedByMist,
    [STRINGID_PKMNGETTINGPUMPED - 12] = gText_PkmnGettingPumped,
    [STRINGID_PKMNHITWITHRECOIL - 12] = sText_PkmnHitWithRecoil,
    [STRINGID_PKMNPROTECTEDITSELF2 - 12] = sText_PkmnProtectedItself2,
    [STRINGID_PKMNBUFFETEDBYSANDSTORM - 12] = sText_PkmnBuffetedBySandstorm,
    [STRINGID_PKMNPELTEDBYHAIL - 12] = sText_PkmnPeltedByHail,
    [STRINGID_PKMNSEEDED - 12] = sText_PkmnSeeded,
    [STRINGID_PKMNEVADEDATTACK - 12] = sText_PkmnEvadedAttack,
    [STRINGID_PKMNSAPPEDBYLEECHSEED - 12] = sText_PkmnSappedByLeechSeed,
    [STRINGID_PKMNFASTASLEEP - 12] = sText_PkmnFastAsleep,
    [STRINGID_PKMNWOKEUP - 12] = sText_PkmnWokeUp,
    [STRINGID_PKMNUPROARKEPTAWAKE - 12] = sText_PkmnUproarKeptAwake,
    [STRINGID_PKMNWOKEUPINUPROAR - 12] = sText_PkmnWokeUpInUproar,
    [STRINGID_PKMNCAUSEDUPROAR - 12] = sText_PkmnCausedUproar,
    [STRINGID_PKMNMAKINGUPROAR - 12] = sText_PkmnMakingUproar,
    [STRINGID_PKMNCALMEDDOWN - 12] = sText_PkmnCalmedDown,
    [STRINGID_PKMNCANTSLEEPINUPROAR - 12] = sText_PkmnCantSleepInUproar,
    [STRINGID_PKMNSTOCKPILED - 12] = sText_PkmnStockpiled,
    [STRINGID_PKMNCANTSTOCKPILE - 12] = sText_PkmnCantStockpile,
    [STRINGID_PKMNCANTSLEEPINUPROAR2 - 12] = sText_PkmnCantSleepInUproar2,
    [STRINGID_UPROARKEPTPKMNAWAKE - 12] = sText_UproarKeptPkmnAwake,
    [STRINGID_PKMNSTAYEDAWAKEUSING - 12] = sText_PkmnStayedAwakeUsing,
    [STRINGID_PKMNSTORINGENERGY - 12] = sText_PkmnStoringEnergy,
    [STRINGID_PKMNUNLEASHEDENERGY - 12] = sText_PkmnUnleashedEnergy,
    [STRINGID_PKMNFATIGUECONFUSION - 12] = sText_PkmnFatigueConfusion,
    [STRINGID_PKMNPICKEDUPITEM - 12] = sText_PkmnPickedUpItem,
    [STRINGID_PKMNUNAFFECTED - 12] = sText_PkmnUnaffected,
    [STRINGID_PKMNTRANSFORMEDINTO - 12] = sText_PkmnTransformedInto,
    [STRINGID_PKMNMADESUBSTITUTE - 12] = sText_PkmnMadeSubstitute,
    [STRINGID_PKMNHASSUBSTITUTE - 12] = sText_PkmnHasSubstitute,
    [STRINGID_SUBSTITUTEDAMAGED - 12] = sText_SubstituteDamaged,
    [STRINGID_PKMNSUBSTITUTEFADED - 12] = sText_PkmnSubstituteFaded,
    [STRINGID_PKMNMUSTRECHARGE - 12] = sText_PkmnMustRecharge,
    [STRINGID_PKMNRAGEBUILDING - 12] = sText_PkmnRageBuilding,
    [STRINGID_PKMNMOVEWASDISABLED - 12] = sText_PkmnMoveWasDisabled,
    [STRINGID_PKMNMOVEISDISABLED - 12] = sText_PkmnMoveIsDisabled,
    [STRINGID_PKMNMOVEDISABLEDNOMORE - 12] = sText_PkmnMoveDisabledNoMore,
    [STRINGID_PKMNGOTENCORE - 12] = sText_PkmnGotEncore,
    [STRINGID_PKMNENCOREENDED - 12] = sText_PkmnEncoreEnded,
    [STRINGID_PKMNTOOKAIM - 12] = sText_PkmnTookAim,
    [STRINGID_PKMNSKETCHEDMOVE - 12] = sText_PkmnSketchedMove,
    [STRINGID_PKMNTRYINGTOTAKEFOE - 12] = sText_PkmnTryingToTakeFoe,
    [STRINGID_PKMNTOOKFOE - 12] = sText_PkmnTookFoe,
    [STRINGID_PKMNREDUCEDPP - 12] = sText_PkmnReducedPP,
    [STRINGID_PKMNSTOLEITEM - 12] = sText_PkmnStoleItem,
    [STRINGID_TARGETCANTESCAPENOW - 12] = sText_TargetCantEscapeNow,
    [STRINGID_PKMNFELLINTONIGHTMARE - 12] = sText_PkmnFellIntoNightmare,
    [STRINGID_PKMNLOCKEDINNIGHTMARE - 12] = sText_PkmnLockedInNightmare,
    [STRINGID_PKMNLAIDCURSE - 12] = sText_PkmnLaidCurse,
    [STRINGID_PKMNAFFLICTEDBYCURSE - 12] = sText_PkmnAfflictedByCurse,
    [STRINGID_SPIKESSCATTERED - 12] = sText_SpikesScattered,
    [STRINGID_PKMNHURTBYSPIKES - 12] = sText_PkmnHurtBySpikes,
    [STRINGID_PKMNIDENTIFIED - 12] = sText_PkmnIdentified,
    [STRINGID_PKMNPERISHCOUNTFELL - 12] = sText_PkmnPerishCountFell,
    [STRINGID_PKMNBRACEDITSELF - 12] = sText_PkmnBracedItself,
    [STRINGID_PKMNENDUREDHIT - 12] = sText_PkmnEnduredHit,
    [STRINGID_MAGNITUDESTRENGTH - 12] = sText_MagnitudeStrength,
    [STRINGID_PKMNCUTHPMAXEDATTACK - 12] = sText_PkmnCutHPMaxedAttack,
    [STRINGID_PKMNCOPIEDSTATCHANGES - 12] = sText_PkmnCopiedStatChanges,
    [STRINGID_PKMNGOTFREE - 12] = sText_PkmnGotFree,
    [STRINGID_PKMNSHEDLEECHSEED - 12] = sText_PkmnShedLeechSeed,
    [STRINGID_PKMNBLEWAWAYSPIKES - 12] = sText_PkmnBlewAwaySpikes,
    [STRINGID_PKMNFLEDFROMBATTLE - 12] = sText_PkmnFledFromBattle,
    [STRINGID_PKMNFORESAWATTACK - 12] = sText_PkmnForesawAttack,
    [STRINGID_PKMNTOOKATTACK - 12] = sText_PkmnTookAttack,
    [STRINGID_PKMNATTACK - 12] = sText_PkmnAttack,
    [STRINGID_PKMNCENTERATTENTION - 12] = sText_PkmnCenterAttention,
    [STRINGID_PKMNCHARGINGPOWER - 12] = sText_PkmnChargingPower,
    [STRINGID_NATUREPOWERTURNEDINTO - 12] = sText_NaturePowerTurnedInto,
    [STRINGID_PKMNSTATUSNORMAL - 12] = sText_PkmnStatusNormal,
    [STRINGID_PKMNHASNOMOVESLEFT - 12] = sText_PkmnHasNoMovesLeft,
    [STRINGID_PKMNSUBJECTEDTOTORMENT - 12] = sText_PkmnSubjectedToTorment,
    [STRINGID_PKMNCANTUSEMOVETORMENT - 12] = sText_PkmnCantUseMoveTorment,
    [STRINGID_PKMNTIGHTENINGFOCUS - 12] = sText_PkmnTighteningFocus,
    [STRINGID_PKMNFELLFORTAUNT - 12] = sText_PkmnFellForTaunt,
    [STRINGID_PKMNCANTUSEMOVETAUNT - 12] = sText_PkmnCantUseMoveTaunt,
    [STRINGID_PKMNREADYTOHELP - 12] = sText_PkmnReadyToHelp,
    [STRINGID_PKMNSWITCHEDITEMS - 12] = sText_PkmnSwitchedItems,
    [STRINGID_PKMNCOPIEDFOE - 12] = sText_PkmnCopiedFoe,
    [STRINGID_PKMNMADEWISH - 12] = sText_PkmnMadeWish,
    [STRINGID_PKMNWISHCAMETRUE - 12] = sText_PkmnWishCameTrue,
    [STRINGID_PKMNPLANTEDROOTS - 12] = sText_PkmnPlantedRoots,
    [STRINGID_PKMNABSORBEDNUTRIENTS - 12] = sText_PkmnAbsorbedNutrients,
    [STRINGID_PKMNANCHOREDITSELF - 12] = sText_PkmnAnchoredItself,
    [STRINGID_PKMNWASMADEDROWSY - 12] = sText_PkmnWasMadeDrowsy,
    [STRINGID_PKMNKNOCKEDOFF - 12] = sText_PkmnKnockedOff,
    [STRINGID_PKMNSWAPPEDABILITIES - 12] = sText_PkmnSwappedAbilities,
    [STRINGID_PKMNSEALEDOPPONENTMOVE - 12] = sText_PkmnSealedOpponentMove,
    [STRINGID_PKMNCANTUSEMOVESEALED - 12] = sText_PkmnCantUseMoveSealed,
    [STRINGID_PKMNWANTSGRUDGE - 12] = sText_PkmnWantsGrudge,
    [STRINGID_PKMNLOSTPPGRUDGE - 12] = sText_PkmnLostPPGrudge,
    [STRINGID_PKMNSHROUDEDITSELF - 12] = sText_PkmnShroudedItself,
    [STRINGID_PKMNMOVEBOUNCED - 12] = sText_PkmnMoveBounced,
    [STRINGID_PKMNWAITSFORTARGET - 12] = sText_PkmnWaitsForTarget,
    [STRINGID_PKMNSNATCHEDMOVE - 12] = sText_PkmnSnatchedMove,
    [STRINGID_PKMNMADEITRAIN - 12] = sText_PkmnMadeItRain,
    [STRINGID_PKMNRAISEDSPEED - 12] = sText_PkmnRaisedSpeed,
    [STRINGID_PKMNPROTECTEDBY - 12] = sText_PkmnProtectedBy,
    [STRINGID_PKMNPREVENTSUSAGE - 12] = sText_PkmnPreventsUsage,
    [STRINGID_PKMNRESTOREDHPUSING - 12] = sText_PkmnRestoredHPUsing,
    [STRINGID_PKMNCHANGEDTYPEWITH - 12] = sText_PkmnChangedTypeWith,
    [STRINGID_PKMNPREVENTSPARALYSISWITH - 12] = sText_PkmnPreventsParalysisWith,
    [STRINGID_PKMNPREVENTSROMANCEWITH - 12] = sText_PkmnPreventsRomanceWith,
    [STRINGID_PKMNPREVENTSPOISONINGWITH - 12] = sText_PkmnPreventsPoisoningWith,
    [STRINGID_PKMNPREVENTSCONFUSIONWITH - 12] = sText_PkmnPreventsConfusionWith,
    [STRINGID_PKMNRAISEDFIREPOWERWITH - 12] = sText_PkmnRaisedFirePowerWith,
    [STRINGID_PKMNANCHORSITSELFWITH - 12] = sText_PkmnAnchorsItselfWith,
    [STRINGID_PKMNCUTSATTACKWITH - 12] = sText_PkmnCutsAttackWith,
    [STRINGID_PKMNPREVENTSSTATLOSSWITH - 12] = sText_PkmnPreventsStatLossWith,
    [STRINGID_PKMNHURTSWITH - 12] = sText_PkmnHurtsWith,
    [STRINGID_PKMNTRACED - 12] = sText_PkmnTraced,
    [STRINGID_STATSHARPLY - 12] = sText_StatSharply,
    [STRINGID_STATROSE - 12] = gText_StatRose,
    [STRINGID_STATHARSHLY - 12] = sText_StatHarshly,
    [STRINGID_STATFELL - 12] = sText_StatFell,
    [STRINGID_PKMNSSTATCHANGED - 12] = sText_PkmnsStatChanged,
    [STRINGID_PKMNSSTATCHANGED2 - 12] = gText_PkmnsStatChanged2,
    [STRINGID_PKMNSSTATCHANGED3 - 12] = sText_PkmnsStatChanged3,
    [STRINGID_PKMNSSTATCHANGED4 - 12] = sText_PkmnsStatChanged4,
    [STRINGID_CRITICALHIT - 12] = sText_CriticalHit,
    [STRINGID_ONEHITKO - 12] = sText_OneHitKO,
    [STRINGID_123POOF - 12] = sText_123Poof,
    [STRINGID_ANDELLIPSIS - 12] = sText_AndEllipsis,
    [STRINGID_NOTVERYEFFECTIVE - 12] = sText_NotVeryEffective,
    [STRINGID_SUPEREFFECTIVE - 12] = sText_SuperEffective,
    [STRINGID_GOTAWAYSAFELY - 12] = sText_GotAwaySafely,
    [STRINGID_WILDPKMNFLED - 12] = sText_WildPkmnFled,
    [STRINGID_NORUNNINGFROMTRAINERS - 12] = sText_NoRunningFromTrainers,
    [STRINGID_CANTESCAPE - 12] = sText_CantEscape,
    [STRINGID_DONTLEAVEBIRCH - 12] = sText_DontLeaveBirch,
    [STRINGID_BUTNOTHINGHAPPENED - 12] = sText_ButNothingHappened,
    [STRINGID_BUTITFAILED - 12] = sText_ButItFailed,
    [STRINGID_ITHURTCONFUSION - 12] = sText_ItHurtConfusion,
    [STRINGID_MIRRORMOVEFAILED - 12] = sText_MirrorMoveFailed,
    [STRINGID_STARTEDTORAIN - 12] = sText_StartedToRain,
    [STRINGID_DOWNPOURSTARTED - 12] = sText_DownpourStarted,
    [STRINGID_RAINCONTINUES - 12] = sText_RainContinues,
    [STRINGID_DOWNPOURCONTINUES - 12] = sText_DownpourContinues,
    [STRINGID_RAINSTOPPED - 12] = sText_RainStopped,
    [STRINGID_SANDSTORMBREWED - 12] = sText_SandstormBrewed,
    [STRINGID_SANDSTORMRAGES - 12] = sText_SandstormRages,
    [STRINGID_SANDSTORMSUBSIDED - 12] = sText_SandstormSubsided,
    [STRINGID_SUNLIGHTGOTBRIGHT - 12] = sText_SunlightGotBright,
    [STRINGID_SUNLIGHTSTRONG - 12] = sText_SunlightStrong,
    [STRINGID_SUNLIGHTFADED - 12] = sText_SunlightFaded,
    [STRINGID_STARTEDHAIL - 12] = sText_StartedHail,
    [STRINGID_HAILCONTINUES - 12] = sText_HailContinues,
    [STRINGID_HAILSTOPPED - 12] = sText_HailStopped,
    [STRINGID_FAILEDTOSPITUP - 12] = sText_FailedToSpitUp,
    [STRINGID_FAILEDTOSWALLOW - 12] = sText_FailedToSwallow,
    [STRINGID_WINDBECAMEHEATWAVE - 12] = sText_WindBecameHeatWave,
    [STRINGID_STATCHANGESGONE - 12] = sText_StatChangesGone,
    [STRINGID_COINSSCATTERED - 12] = sText_CoinsScattered,
    [STRINGID_TOOWEAKFORSUBSTITUTE - 12] = sText_TooWeakForSubstitute,
    [STRINGID_SHAREDPAIN - 12] = sText_SharedPain,
    [STRINGID_BELLCHIMED - 12] = sText_BellChimed,
    [STRINGID_FAINTINTHREE - 12] = sText_FaintInThree,
    [STRINGID_NOPPLEFT - 12] = sText_NoPPLeft,
    [STRINGID_BUTNOPPLEFT - 12] = sText_ButNoPPLeft,
    [STRINGID_PLAYERUSEDITEM - 12] = sText_PlayerUsedItem,
    [STRINGID_WALLYUSEDITEM - 12] = sText_WallyUsedItem,
    [STRINGID_TRAINERBLOCKEDBALL - 12] = sText_TrainerBlockedBall,
    [STRINGID_DONTBEATHIEF - 12] = sText_DontBeAThief,
    [STRINGID_ITDODGEDBALL - 12] = sText_ItDodgedBall,
    [STRINGID_YOUMISSEDPKMN - 12] = sText_YouMissedPkmn,
    [STRINGID_PKMNBROKEFREE - 12] = sText_PkmnBrokeFree,
    [STRINGID_ITAPPEAREDCAUGHT - 12] = sText_ItAppearedCaught,
    [STRINGID_AARGHALMOSTHADIT - 12] = sText_AarghAlmostHadIt,
    [STRINGID_SHOOTSOCLOSE - 12] = sText_ShootSoClose,
    [STRINGID_GOTCHAPKMNCAUGHT - 12] = sText_GotchaPkmnCaught,
    [STRINGID_GOTCHAPKMNCAUGHT2 - 12] = sText_GotchaPkmnCaught2,
    [STRINGID_GIVENICKNAMECAPTURED - 12] = sText_GiveNicknameCaptured,
    [STRINGID_PKMNSENTTOPC - 12] = sText_PkmnSentToPC,
    [STRINGID_PKMNDATAADDEDTODEX - 12] = sText_PkmnDataAddedToDex,
    [STRINGID_ITISRAINING - 12] = sText_ItIsRaining,
    [STRINGID_SANDSTORMISRAGING - 12] = sText_SandstormIsRaging,
    [STRINGID_CANTESCAPE2 - 12] = sText_CantEscape2,
    [STRINGID_PKMNIGNORESASLEEP - 12] = sText_PkmnIgnoresAsleep,
    [STRINGID_PKMNIGNOREDORDERS - 12] = sText_PkmnIgnoredOrders,
    [STRINGID_PKMNBEGANTONAP - 12] = sText_PkmnBeganToNap,
    [STRINGID_PKMNLOAFING - 12] = sText_PkmnLoafing,
    [STRINGID_PKMNWONTOBEY - 12] = sText_PkmnWontObey,
    [STRINGID_PKMNTURNEDAWAY - 12] = sText_PkmnTurnedAway,
    [STRINGID_PKMNPRETENDNOTNOTICE - 12] = sText_PkmnPretendNotNotice,
    [STRINGID_ENEMYABOUTTOSWITCHPKMN - 12] = sText_EnemyAboutToSwitchPkmn,
    [STRINGID_CREPTCLOSER - 12] = sText_CreptCloser,
    [STRINGID_CANTGETCLOSER - 12] = sText_CantGetCloser,
    [STRINGID_PKMNWATCHINGCAREFULLY - 12] = sText_PkmnWatchingCarefully,
    [STRINGID_PKMNCURIOUSABOUTX - 12] = sText_PkmnCuriousAboutX,
    [STRINGID_PKMNENTHRALLEDBYX - 12] = sText_PkmnEnthralledByX,
    [STRINGID_PKMNIGNOREDX - 12] = sText_PkmnIgnoredX,
    [STRINGID_THREWPOKEBLOCKATPKMN - 12] = sText_ThrewPokeblockAtPkmn,
    [STRINGID_OUTOFSAFARIBALLS - 12] = sText_OutOfSafariBalls,
    [STRINGID_PKMNSITEMCUREDPARALYSIS - 12] = sText_PkmnsItemCuredParalysis,
    [STRINGID_PKMNSITEMCUREDPOISON - 12] = sText_PkmnsItemCuredPoison,
    [STRINGID_PKMNSITEMHEALEDBURN - 12] = sText_PkmnsItemHealedBurn,
    [STRINGID_PKMNSITEMDEFROSTEDIT - 12] = sText_PkmnsItemDefrostedIt,
    [STRINGID_PKMNSITEMWOKEIT - 12] = sText_PkmnsItemWokeIt,
    [STRINGID_PKMNSITEMSNAPPEDOUT - 12] = sText_PkmnsItemSnappedOut,
    [STRINGID_PKMNSITEMCUREDPROBLEM - 12] = sText_PkmnsItemCuredProblem,
    [STRINGID_PKMNSITEMRESTOREDHEALTH - 12] = sText_PkmnsItemRestoredHealth,
    [STRINGID_PKMNSITEMRESTOREDPP - 12] = sText_PkmnsItemRestoredPP,
    [STRINGID_PKMNSITEMRESTOREDSTATUS - 12] = sText_PkmnsItemRestoredStatus,
    [STRINGID_PKMNSITEMRESTOREDHPALITTLE - 12] = sText_PkmnsItemRestoredHPALittle,
    [STRINGID_ITEMALLOWSONLYYMOVE - 12] = sText_ItemAllowsOnlyYMove,
    [STRINGID_PKMNHUNGONWITHX - 12] = sText_PkmnHungOnWithX,
    [STRINGID_EMPTYSTRING3 - 12] = gText_EmptyString3,
    [STRINGID_PKMNSXPREVENTSBURNS - 12] = sText_PkmnsXPreventsBurns,
    [STRINGID_PKMNSXBLOCKSY - 12] = sText_PkmnsXBlocksY,
    [STRINGID_PKMNSXRESTOREDHPALITTLE2 - 12] = sText_PkmnsXRestoredHPALittle2,
    [STRINGID_PKMNSXWHIPPEDUPSANDSTORM - 12] = sText_PkmnsXWhippedUpSandstorm,
    [STRINGID_PKMNSXPREVENTSYLOSS - 12] = sText_PkmnsXPreventsYLoss,
    [STRINGID_PKMNSXINFATUATEDY - 12] = sText_PkmnsXInfatuatedY,
    [STRINGID_PKMNSXMADEYINEFFECTIVE - 12] = sText_PkmnsXMadeYIneffective,
    [STRINGID_PKMNSXCUREDYPROBLEM - 12] = sText_PkmnsXCuredYProblem,
    [STRINGID_ITSUCKEDLIQUIDOOZE - 12] = sText_ItSuckedLiquidOoze,
    [STRINGID_PKMNTRANSFORMED - 12] = sText_PkmnTransformed,
    [STRINGID_ELECTRICITYWEAKENED - 12] = sText_ElectricityWeakened,
    [STRINGID_FIREWEAKENED - 12] = sText_FireWeakened,
    [STRINGID_PKMNHIDUNDERWATER - 12] = sText_PkmnHidUnderwater,
    [STRINGID_PKMNSPRANGUP - 12] = sText_PkmnSprangUp,
    [STRINGID_HMMOVESCANTBEFORGOTTEN - 12] = sText_HMMovesCantBeForgotten,
    [STRINGID_XFOUNDONEY - 12] = sText_XFoundOneY,
    [STRINGID_PLAYERDEFEATEDTRAINER1 - 12] = sText_PlayerDefeatedLinkTrainerTrainer1,
    [STRINGID_SOOTHINGAROMA - 12] = sText_SoothingAroma,
    [STRINGID_ITEMSCANTBEUSEDNOW - 12] = sText_ItemsCantBeUsedNow,
    [STRINGID_FORXCOMMAYZ - 12] = sText_ForXCommaYZ,
    [STRINGID_USINGXTHEYOFZN - 12] = sText_UsingXTheYOfZN,
    [STRINGID_PKMNUSEDXTOGETPUMPED - 12] = sText_PkmnUsedXToGetPumped,
    [STRINGID_PKMNSXMADEYUSELESS - 12] = sText_PkmnsXMadeYUseless,
    [STRINGID_PKMNTRAPPEDBYSANDTOMB - 12] = sText_PkmnTrappedBySandTomb,
    [STRINGID_EMPTYSTRING4 - 12] = sText_EmptyString4,
    [STRINGID_ABOOSTED - 12] = sText_ABoosted,
    [STRINGID_PKMNSXINTENSIFIEDSUN - 12] = sText_PkmnsXIntensifiedSun,
    [STRINGID_PKMNMAKESGROUNDMISS - 12] = sText_PkmnMakesGroundMiss,
    [STRINGID_YOUTHROWABALLNOWRIGHT - 12] = sText_YouThrowABallNowRight,
    [STRINGID_PKMNSXTOOKATTACK - 12] = sText_PkmnsXTookAttack,
    [STRINGID_PKMNCHOSEXASDESTINY - 12] = sText_PkmnChoseXAsDestiny,
    [STRINGID_PKMNLOSTFOCUS - 12] = sText_PkmnLostFocus,
    [STRINGID_USENEXTPKMN - 12] = sText_UseNextPkmn,
    [STRINGID_PKMNFLEDUSINGITS - 12] = sText_PkmnFledUsingIts,
    [STRINGID_PKMNFLEDUSING - 12] = sText_PkmnFledUsing,
    [STRINGID_PKMNWASDRAGGEDOUT - 12] = sText_PkmnWasDraggedOut,
    [STRINGID_PREVENTEDFROMWORKING - 12] = sText_PreventedFromWorking,
    [STRINGID_PKMNSITEMNORMALIZEDSTATUS - 12] = sText_PkmnsItemNormalizedStatus,
    [STRINGID_TRAINER1USEDITEM - 12] = sText_Trainer1UsedItem,
    [STRINGID_BOXISFULL - 12] = sText_BoxIsFull,
    [STRINGID_PKMNAVOIDEDATTACK - 12] = sText_PkmnAvoidedAttack,
    [STRINGID_PKMNSXMADEITINEFFECTIVE - 12] = sText_PkmnsXMadeItIneffective,
    [STRINGID_PKMNSXPREVENTSFLINCHING - 12] = sText_PkmnsXPreventsFlinching,
    [STRINGID_PKMNALREADYHASBURN - 12] = sText_PkmnAlreadyHasBurn,
    [STRINGID_STATSWONTDECREASE2 - 12] = sText_StatsWontDecrease2,
    [STRINGID_PKMNSXBLOCKSY2 - 12] = sText_PkmnsXBlocksY2,
    [STRINGID_PKMNSXWOREOFF - 12] = sText_PkmnsXWoreOff,
    [STRINGID_PKMNRAISEDDEFALITTLE - 12] = sText_PkmnRaisedDefALittle,
    [STRINGID_PKMNRAISEDSPDEFALITTLE - 12] = sText_PkmnRaisedSpDefALittle,
    [STRINGID_THEWALLSHATTERED - 12] = sText_TheWallShattered,
    [STRINGID_PKMNSXPREVENTSYSZ - 12] = sText_PkmnsXPreventsYsZ,
    [STRINGID_PKMNSXCUREDITSYPROBLEM - 12] = sText_PkmnsXCuredItsYProblem,
    [STRINGID_ATTACKERCANTESCAPE - 12] = sText_AttackerCantEscape,
    [STRINGID_PKMNOBTAINEDX - 12] = sText_PkmnObtainedX,
    [STRINGID_PKMNOBTAINEDX2 - 12] = sText_PkmnObtainedX2,
    [STRINGID_PKMNOBTAINEDXYOBTAINEDZ - 12] = sText_PkmnObtainedXYObtainedZ,
    [STRINGID_BUTNOEFFECT - 12] = sText_ButNoEffect,
    [STRINGID_PKMNSXHADNOEFFECTONY - 12] = sText_PkmnsXHadNoEffectOnY,
    [STRINGID_TWOENEMIESDEFEATED - 12] = sText_TwoInGameTrainersDefeated,
    [STRINGID_TRAINER2LOSETEXT - 12] = sText_Trainer2LoseText,
    [STRINGID_PKMNINCAPABLEOFPOWER - 12] = sText_PkmnIncapableOfPower,
    [STRINGID_GLINTAPPEARSINEYE - 12] = sText_GlintAppearsInEye,
    [STRINGID_PKMNGETTINGINTOPOSITION - 12] = sText_PkmnGettingIntoPosition,
    [STRINGID_PKMNBEGANGROWLINGDEEPLY - 12] = sText_PkmnBeganGrowlingDeeply,
    [STRINGID_PKMNEAGERFORMORE - 12] = sText_PkmnEagerForMore,
    [STRINGID_DEFEATEDOPPONENTBYREFEREE - 12] = sText_DefeatedOpponentByReferee,
    [STRINGID_LOSTTOOPPONENTBYREFEREE - 12] = sText_LostToOpponentByReferee,
    [STRINGID_TIEDOPPONENTBYREFEREE - 12] = sText_TiedOpponentByReferee,
    [STRINGID_QUESTIONFORFEITMATCH - 12] = sText_QuestionForfeitMatch,
    [STRINGID_FORFEITEDMATCH - 12] = sText_ForfeitedMatch,
    [STRINGID_PKMNTRANSFERREDSOMEONESPC - 12] = gText_PkmnTransferredSomeonesPC,
    [STRINGID_PKMNTRANSFERREDLANETTESPC - 12] = gText_PkmnTransferredLanettesPC,
    [STRINGID_PKMNBOXSOMEONESPCFULL - 12] = gText_PkmnTransferredSomeonesPCBoxFull,
    [STRINGID_PKMNBOXLANETTESPCFULL - 12] = gText_PkmnTransferredLanettesPCBoxFull,
    [STRINGID_TRAINER1WINTEXT - 12] = sText_Trainer1WinText,
    [STRINGID_TRAINER2WINTEXT - 12] = sText_Trainer2WinText,
};

const u16 gMissStringIds[] =
{
    STRINGID_ATTACKMISSED, STRINGID_PKMNPROTECTEDITSELF,
    STRINGID_PKMNAVOIDEDATTACK, STRINGID_AVOIDEDDAMAGE,
    STRINGID_PKMNMAKESGROUNDMISS
};

const u16 gNoEscapeStringIds[] =
{
    STRINGID_CANTESCAPE, STRINGID_DONTLEAVEBIRCH, STRINGID_PREVENTSESCAPE,
    STRINGID_CANTESCAPE2, STRINGID_ATTACKERCANTESCAPE
};

const u16 gMoveWeatherChangeStringIds[] =
{
    STRINGID_STARTEDTORAIN, STRINGID_DOWNPOURSTARTED, STRINGID_BUTITFAILED,
    STRINGID_SANDSTORMBREWED, STRINGID_SUNLIGHTGOTBRIGHT, STRINGID_STARTEDHAIL
};

const u16 gSandStormHailContinuesStringIds[] =
{
    STRINGID_SANDSTORMRAGES, STRINGID_HAILCONTINUES
};

const u16 gSandStormHailDmgStringIds[] =
{
    STRINGID_PKMNBUFFETEDBYSANDSTORM, STRINGID_PKMNPELTEDBYHAIL
};

const u16 gSandStormHailEndStringIds[] =
{
    STRINGID_SANDSTORMSUBSIDED, STRINGID_HAILSTOPPED
};

const u16 gRainContinuesStringIds[] =
{
    STRINGID_RAINCONTINUES, STRINGID_DOWNPOURCONTINUES, STRINGID_RAINSTOPPED
};

const u16 gProtectLikeUsedStringIds[] =
{
    STRINGID_PKMNPROTECTEDITSELF2, STRINGID_PKMNBRACEDITSELF, STRINGID_BUTITFAILED
};

const u16 gReflectLightScreenSafeguardStringIds[] =
{
    STRINGID_BUTITFAILED, STRINGID_PKMNRAISEDDEF, STRINGID_PKMNRAISEDDEFALITTLE,
    STRINGID_PKMNRAISEDSPDEF, STRINGID_PKMNRAISEDSPDEFALITTLE, STRINGID_PKMNCOVEREDBYVEIL
};

const u16 gLeechSeedStringIds[] =
{
    STRINGID_PKMNSEEDED, STRINGID_PKMNEVADEDATTACK,
    STRINGID_ITDOESNTAFFECT, STRINGID_PKMNSAPPEDBYLEECHSEED, STRINGID_ITSUCKEDLIQUIDOOZE,
};

const u16 gRestUsedStringIds[] =
{
    STRINGID_PKMNWENTTOSLEEP, STRINGID_PKMNSLEPTHEALTHY
};

const u16 gUproarOverTurnStringIds[] =
{
    STRINGID_PKMNMAKINGUPROAR, STRINGID_PKMNCALMEDDOWN
};

const u16 gStockpileUsedStringIds[] =
{
    STRINGID_PKMNSTOCKPILED, STRINGID_PKMNCANTSTOCKPILE,
};

const u16 gWokeUpStringIds[] =
{
    STRINGID_PKMNWOKEUP, STRINGID_PKMNWOKEUPINUPROAR
};

const u16 gSwallowFailStringIds[] =
{
    STRINGID_FAILEDTOSWALLOW, STRINGID_PKMNHPFULL
};

const u16 gUproarAwakeStringIds[] =
{
    STRINGID_PKMNCANTSLEEPINUPROAR2, STRINGID_UPROARKEPTPKMNAWAKE, STRINGID_PKMNSTAYEDAWAKEUSING
};

const u16 gStatUpStringIds[] =
{
    STRINGID_PKMNSSTATCHANGED, STRINGID_PKMNSSTATCHANGED2, STRINGID_STATSWONTINCREASE,
    STRINGID_EMPTYSTRING3, STRINGID_USINGXTHEYOFZN, STRINGID_PKMNUSEDXTOGETPUMPED
};

const u16 gStatDownStringIds[] =
{
    STRINGID_PKMNSSTATCHANGED3, STRINGID_PKMNSSTATCHANGED4, STRINGID_STATSWONTDECREASE, STRINGID_EMPTYSTRING3
};

// Index read from sTWOTURN_STRINGID
const u16 gFirstTurnOfTwoStringIds[] =
{
    STRINGID_PKMNWHIPPEDWHIRLWIND, // MOVE_RAZOR_WIND
    STRINGID_PKMNTOOKSUNLIGHT,     // MOVE_SOLAR_BEAM
    STRINGID_PKMNLOWEREDHEAD,      // MOVE_SKULL_BASH
    STRINGID_PKMNISGLOWING,        // MOVE_SKY_ATTACK
    STRINGID_PKMNFLEWHIGH,         // MOVE_FLY
    STRINGID_PKMNDUGHOLE,          // MOVE_DIG
    STRINGID_PKMNHIDUNDERWATER,    // MOVE_DIVE
    STRINGID_PKMNSPRANGUP          // MOVE_BOUNCE
};

// Index copied from move's index in gTrappingMoves
const u16 gWrappedStringIds[] =
{
    STRINGID_PKMNSQUEEZEDBYBIND,   // MOVE_BIND
    STRINGID_PKMNWRAPPEDBY,        // MOVE_WRAP
    STRINGID_PKMNTRAPPEDINVORTEX,  // MOVE_FIRE_SPIN
    STRINGID_PKMNCLAMPED,          // MOVE_CLAMP
    STRINGID_PKMNTRAPPEDINVORTEX,  // MOVE_WHIRLPOOL
    STRINGID_PKMNTRAPPEDBYSANDTOMB // MOVE_SAND_TOMB
};

const u16 gMistUsedStringIds[] =
{
    STRINGID_PKMNSHROUDEDINMIST, STRINGID_BUTITFAILED
};

const u16 gFocusEnergyUsedStringIds[] =
{
    STRINGID_PKMNGETTINGPUMPED, STRINGID_BUTITFAILED
};

const u16 gTransformUsedStringIds[] =
{
    STRINGID_PKMNTRANSFORMEDINTO, STRINGID_BUTITFAILED
};

const u16 gSubsituteUsedStringIds[] =
{
    STRINGID_PKMNMADESUBSTITUTE, STRINGID_TOOWEAKFORSUBSTITUTE
};

const u16 gGotPoisonedStringIds[] =
{
    STRINGID_PKMNWASPOISONED, STRINGID_PKMNPOISONEDBY
};

const u16 gGotParalyzedStringIds[] =
{
    STRINGID_PKMNWASPARALYZED, STRINGID_PKMNWASPARALYZEDBY
};

const u16 gFellAsleepStringIds[] =
{
    STRINGID_PKMNFELLASLEEP, STRINGID_PKMNMADESLEEP,
};

const u16 gGotBurnedStringIds[] =
{
    STRINGID_PKMNWASBURNED, STRINGID_PKMNBURNEDBY
};

const u16 gGotFrozenStringIds[] =
{
    STRINGID_PKMNWASFROZEN, STRINGID_PKMNFROZENBY
};

const u16 gGotDefrostedStringIds[] =
{
    STRINGID_PKMNWASDEFROSTED2, STRINGID_PKMNWASDEFROSTEDBY
};

const u16 gKOFailedStringIds[] =
{
    STRINGID_ATTACKMISSED, STRINGID_PKMNUNAFFECTED
};

const u16 gAttractUsedStringIds[] =
{
    STRINGID_PKMNFELLINLOVE, STRINGID_PKMNSXINFATUATEDY
};

const u16 gLeechSeedDrainStringIds[] =
{
    STRINGID_PKMNENERGYDRAINED, STRINGID_ITSUCKEDLIQUIDOOZE
};

const u16 gSportsUsedStringIds[] =
{
    STRINGID_ELECTRICITYWEAKENED, STRINGID_FIREWEAKENED
};

const u16 gPartyStatusHealStringIds[] =
{
    STRINGID_BELLCHIMED, STRINGID_BELLCHIMED, STRINGID_BELLCHIMED, STRINGID_BELLCHIMED,
    // interesting how there are four instances of the same string
    STRINGID_SOOTHINGAROMA
};

const u16 gFutureMoveUsedStringIds[] =
{
    STRINGID_PKMNFORESAWATTACK, STRINGID_PKMNCHOSEXASDESTINY
};

const u16 gBallEscapeStringIds[] =
{
    STRINGID_PKMNBROKEFREE, STRINGID_ITAPPEAREDCAUGHT, STRINGID_AARGHALMOSTHADIT, STRINGID_SHOOTSOCLOSE
};

// Overworld weathers that don't have an associated battle weather default to "It is raining."
const u16 gWeatherStartsStringIds[] =
{
    [WEATHER_NONE]               = STRINGID_ITISRAINING,
    [WEATHER_SUNNY_CLOUDS]       = STRINGID_ITISRAINING,
    [WEATHER_SUNNY]              = STRINGID_ITISRAINING,
    [WEATHER_RAIN]               = STRINGID_ITISRAINING,
    [WEATHER_SNOW]               = STRINGID_ITISRAINING,
    [WEATHER_RAIN_THUNDERSTORM]  = STRINGID_ITISRAINING,
    [WEATHER_FOG_HORIZONTAL]     = STRINGID_ITISRAINING,
    [WEATHER_VOLCANIC_ASH]       = STRINGID_ITISRAINING,
    [WEATHER_SANDSTORM]          = STRINGID_SANDSTORMISRAGING,
    [WEATHER_FOG_DIAGONAL]       = STRINGID_ITISRAINING,
    [WEATHER_UNDERWATER]         = STRINGID_ITISRAINING,
    [WEATHER_SHADE]              = STRINGID_ITISRAINING,
    [WEATHER_DROUGHT]            = STRINGID_SUNLIGHTSTRONG,
    [WEATHER_DOWNPOUR]           = STRINGID_ITISRAINING,
    [WEATHER_UNDERWATER_BUBBLES] = STRINGID_ITISRAINING,
    [WEATHER_ABNORMAL]           = STRINGID_ITISRAINING
};

const u16 gInobedientStringIds[] =
{
    STRINGID_PKMNLOAFING, STRINGID_PKMNWONTOBEY, STRINGID_PKMNTURNEDAWAY,
    STRINGID_PKMNPRETENDNOTNOTICE, STRINGID_PKMNINCAPABLEOFPOWER
};

const u16 gSafariGetNearStringIds[] =
{
    STRINGID_CREPTCLOSER, STRINGID_CANTGETCLOSER
};

const u16 gSafariPokeblockResultStringIds[] =
{
    STRINGID_PKMNCURIOUSABOUTX, STRINGID_PKMNENTHRALLEDBYX, STRINGID_PKMNIGNOREDX
};

const u16 gTrainerItemCuredStatusStringIds[] =
{
    STRINGID_PKMNSITEMSNAPPEDOUT, STRINGID_PKMNSITEMCUREDPARALYSIS, STRINGID_PKMNSITEMDEFROSTEDIT,
    STRINGID_PKMNSITEMHEALEDBURN, STRINGID_PKMNSITEMCUREDPOISON, STRINGID_PKMNSITEMWOKEIT
};

const u16 gBerryEffectStringIds[] =
{
    STRINGID_PKMNSITEMCUREDPROBLEM, STRINGID_PKMNSITEMNORMALIZEDSTATUS
};

const u16 gBRNPreventionStringIds[] =
{
    STRINGID_PKMNSXPREVENTSBURNS, STRINGID_PKMNSXPREVENTSYSZ, STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gPRLZPreventionStringIds[] =
{
    STRINGID_PKMNPREVENTSPARALYSISWITH, STRINGID_PKMNSXPREVENTSYSZ, STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gPSNPreventionStringIds[] =
{
    STRINGID_PKMNPREVENTSPOISONINGWITH, STRINGID_PKMNSXPREVENTSYSZ, STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gItemSwapStringIds[] =
{
    STRINGID_PKMNOBTAINEDX, STRINGID_PKMNOBTAINEDX2, STRINGID_PKMNOBTAINEDXYOBTAINEDZ
};

const u16 gFlashFireStringIds[] =
{
    STRINGID_PKMNRAISEDFIREPOWERWITH, STRINGID_PKMNSXMADEYINEFFECTIVE
};

const u16 gCaughtMonStringIds[] =
{
    STRINGID_PKMNTRANSFERREDSOMEONESPC, STRINGID_PKMNTRANSFERREDLANETTESPC, STRINGID_PKMNBOXSOMEONESPCFULL, STRINGID_PKMNBOXLANETTESPCFULL,
};

const u16 gTrappingMoves[] =
{
    MOVE_BIND,
    MOVE_WRAP,
    MOVE_FIRE_SPIN,
    MOVE_CLAMP,
    MOVE_WHIRLPOOL,
    MOVE_SAND_TOMB,
    0xFFFF
};

const u8 gText_PkmnIsEvolving[] = _("...오잉!?\n{STR_VAR_1}의 모습이...!");
const u8 gText_CongratsPkmnEvolved[] = _("축하합니다! {STR_VAR_1}{B_TXT_EUNNEUN}\n{STR_VAR_2}{B_TXT_EU}로 진화했습니다!{WAIT_SE}\p");
const u8 gText_PkmnStoppedEvolving[] = _("얼라리...?\n{STR_VAR_1}의 변화가 멈췄다!\p");
const u8 gText_EllipsisQuestionMark[] = _("...?\p");
const u8 gText_WhatWillPkmnDo[] = _("{B_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n무엇을 할까?");
const u8 gText_WhatWillPkmnDo2[] = _("{B_PLAYER_NAME}{B_TXT_EUNNEUN}\n무엇을 할까?");
const u8 gText_WhatWillWallyDo[] = _("민진은\n무엇을 할까?");
const u8 gText_LinkStandby[] = _("{PAUSE 16}통신 대기 중...");
const u8 gText_BattleMenu[] = _("{SIZE 7}싸운다{CLEAR_TO 48}가방\n포켓몬{CLEAR_TO 48}도망간다");
const u8 gText_SafariZoneMenu[] = _("{SIZE 7}볼{CLEAR_TO 40}포켓몬스넥\n다가간다{CLEAR_TO 40}도망간다");
const u8 gText_MoveInterfacePP[] = _("PP ");
const u8 gText_MoveInterfaceType[] = _("타입/");
const u8 gText_MoveInterfacePpType[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}PP\n타입/");
const u8 gText_MoveInterfaceDynamicColors[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}");
const u8 gText_WhichMoveToForget4[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}바꿀 기술을\n선택해주세요");
const u8 gText_BattleYesNoChoice[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}예\n아니오");
const u8 gText_BattleSwitchWhich[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}바꿀 기술을\n선택해주세요");
const u8 gText_BattleSwitchWhich2[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}");
const u8 gText_BattleSwitchWhich3[] = _("{UP_ARROW}");
const u8 gText_BattleSwitchWhich4[] = _("{ESCAPE 4}");
const u8 gText_BattleSwitchWhich5[] = _("-");

static const u8 sText_HP[] = _("HP");
static const u8 sText_Attack[] = _("공격");
static const u8 sText_Defense[] = _("방어");
static const u8 sText_SpAtk[] = _("특수공격");
static const u8 sText_SpDef[] = _("특수방어");

const u8 * const gStatNamesTable2[] =
{
    sText_HP, sText_SpAtk, sText_Attack,
    sText_SpDef, sText_Defense, sText_Speed
};

const u8 gText_SafariBalls[] = _("{HIGHLIGHT DARK_GREY}사파리볼");
const u8 gText_SafariBallLeft[] = _("{HIGHLIGHT DARK_GREY}{ENG}개 남음$" "{HIGHLIGHT DARK_GREY}");
const u8 gText_Sleep[] = _("잠듦");
const u8 gText_Poison[] = _("독");
const u8 gText_Burn[] = _("화상");
const u8 gText_Paralysis[] = _("마비");
const u8 gText_Ice[] = _("얼음");
const u8 gText_Confusion[] = _("혼란");
const u8 gText_Love[] = _("헤롱헤롱");
const u8 gText_SpaceAndSpace[] = _("{B_TXT_WAGWA} ");
const u8 gText_CommaSpace[] = _(", ");
const u8 gText_Space2[] = _(" ");
const u8 gText_LineBreak[] = _("\l");
const u8 gText_NewLine[] = _("\n");
const u8 gText_Are[] = _("{B_TXT_EUNNEUN}");
const u8 gText_Are2[] = _("{B_TXT_EUNNEUN}");
const u8 gText_BadEgg[] = _("불량알");
const u8 gText_BattleWallyName[] = _("민진");
const u8 gText_Win[] = _("{HIGHLIGHT TRANSPARENT}승");
const u8 gText_Loss[] = _("{HIGHLIGHT TRANSPARENT}패");
const u8 gText_Draw[] = _("{HIGHLIGHT TRANSPARENT}무승부");
static const u8 sText_SpaceIs[] = _("{B_TXT_EUNNEUN}");
static const u8 sText_ApostropheS[] = _("의");

// For displaying names of invalid moves
static const u8 sATypeMove_Table[][NUMBER_OF_MON_TYPES - 1] =
{
    [TYPE_NORMAL]   = _("노말 기술"),
    [TYPE_FIGHTING] = _("격투 기술"),
    [TYPE_FLYING]   = _("비행 기술"),
    [TYPE_POISON]   = _("독 기술"),
    [TYPE_GROUND]   = _("땅 기술"),
    [TYPE_ROCK]     = _("바위 기술"),
    [TYPE_BUG]      = _("벌레 기술"),
    [TYPE_GHOST]    = _("고스트 기술"),
    [TYPE_STEEL]    = _("강철 기술"),
    [TYPE_MYSTERY]  = _("??? 기술"),
    [TYPE_FIRE]     = _("불꽃 기술"),
    [TYPE_WATER]    = _("물 기술"),
    [TYPE_GRASS]    = _("풀 기술"),
    [TYPE_ELECTRIC] = _("전기 기술"),
    [TYPE_PSYCHIC]  = _("에스퍼 기술"),
    [TYPE_ICE]      = _("얼음 기술"),
    [TYPE_DRAGON]   = _("드래곤 기술"),
    [TYPE_DARK]     = _("악 기술")
};

const u8 gText_BattleTourney[] = _("배틀토너먼트");
static const u8 sText_Round1[] = _("1차");
static const u8 sText_Round2[] = _("2차");
static const u8 sText_Semifinal[] = _("준결승");
static const u8 sText_Final[] = _("결승");

const u8 *const gRoundsStringTable[DOME_ROUNDS_COUNT] =
{
    [DOME_ROUND1]    = sText_Round1,
    [DOME_ROUND2]    = sText_Round2,
    [DOME_SEMIFINAL] = sText_Semifinal,
    [DOME_FINAL]     = sText_Final
};

const u8 gText_TheGreatNewHope[] = _("기대받는 대형 신인!\p");
const u8 gText_WillChampionshipDreamComeTrue[] = _("꿈꾸던 우승은 이루어질 것인가!?\p");
const u8 gText_AFormerChampion[] = _("전 챔피언!\p");
const u8 gText_ThePreviousChampion[] = _("전회 챔피언!\p");
const u8 gText_TheUnbeatenChampion[] = _("무적의 챔피언!\p");
const u8 gText_PlayerMon1Name[] = _("{B_PLAYER_MON1_NAME}");
const u8 gText_Vs[] = _("vs");
const u8 gText_OpponentMon1Name[] = _("{B_OPPONENT_MON1_NAME}");
const u8 gText_Mind[] = _("마음");
const u8 gText_Skill[] = _("기술");
const u8 gText_Body[] = _("몸");
const u8 gText_Judgement[] = _("{B_BUFF1}{CLEAR 13}판정{CLEAR 13}{B_BUFF2}");
static const u8 sText_TwoTrainersSentPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_EUNNEUN}\n{B_OPPONENT_MON1_NAME}{B_TXT_EULREUL} 내보냈다!\p{B_TRAINER2_CLASS} {B_TRAINER2_NAME}{B_TXT_EUNNEUN}\n{B_OPPONENT_MON2_NAME}{B_TXT_EULREUL} 내보냈다!");
static const u8 sText_Trainer2SentOutPkmn[] = _("{B_TRAINER2_CLASS} {B_TRAINER2_NAME}{B_TXT_EUNNEUN}\n{B_BUFF1}{B_TXT_EULREUL} 내보냈다!");
static const u8 sText_TwoTrainersWantToBattle[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_WAGWA}\n{B_TRAINER2_CLASS} {B_TRAINER2_NAME}{B_TXT_IGA}\l승부를 걸어왔다!\p");
static const u8 sText_InGamePartnerSentOutZGoN[] = _("{B_PARTNER_CLASS} {B_PARTNER_NAME}{B_TXT_EUNNEUN}\n{B_PLAYER_MON2_NAME}{B_TXT_EULREUL} 내보냈다!\l가랏! {B_PLAYER_MON1_NAME}!");
static const u8 sText_TwoInGameTrainersDefeated[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_WAGWA}\n{B_TRAINER2_CLASS} {B_TRAINER2_NAME}{B_TXT_WAGWA}의\l승부에서 이겼다!\p");
static const u8 sText_Trainer2LoseText[] = _("{B_TRAINER2_LOSE_TEXT}");
static const u8 sText_PkmnIncapableOfPower[] = _("{B_ATK_NAME_WITH_PREFIX}{B_TXT_EUNNEUN}\n자신의 힘을 발휘할 수 없는 것 같다!");
static const u8 sText_GlintAppearsInEye[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}의 눈빛이 바뀌었다!");
static const u8 sText_PkmnGettingIntoPosition[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 태세를 가다듬었다!");
static const u8 sText_PkmnBeganGrowlingDeeply[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 낮게 으르렁거리기 시작했다!");
static const u8 sText_PkmnEagerForMore[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}{B_TXT_EUNNEUN} 아직도 의욕이 넘친다!");

const u16 gBattlePalaceFlavorTextTable[] =
{
    STRINGID_GLINTAPPEARSINEYE, 
    STRINGID_PKMNGETTINGINTOPOSITION,
    STRINGID_PKMNBEGANGROWLINGDEEPLY, 
    STRINGID_PKMNEAGERFORMORE
};

static const u8 sText_RefIfNothingIsDecided[] = _("심판: 앞으로 3턴 뒤에 결착이\n나지 않으면 판정을 하게 됩니다!"); // しんぱん『あと 3タ-ンで けっちゃくがｎつかないと はんていに なります!
static const u8 sText_RefThatsIt[] = _("심판: 거기까지---!\n이 대결은 판정을 하겠습니다!"); // しんぱん『そこまで---!ｎこの たいけつは はんていに なります!
static const u8 sText_RefJudgeMind[] = _("심판: 첫 번째 판정! “마음”!\n공격할 마음을 보여주었는가!\p"); // しんぱん『はんてい その1! 「こころ」!ｎせめる きもちを みせたもの!ｐ
static const u8 sText_RefJudgeSkill[] = _("심판: 두 번째 판정! “기술”!\n제대로 기술을 썼는가!\p"); // しんぱん『はんてい その2! 「わざ」!ｎてきかくに わざを くりだしたもの!ｐ
static const u8 sText_RefJudgeBody[] = _("심판: 세 번째 판정! “몸”!\n넘치는 체력을 가졌는가!\p"); // しんぱん『はんてい その3! 「からだ」!ｎあふれる たいりょくを もちえるもの!ｐ
static const u8 sText_RefJudgement1[] = _("심판: 판정 {B_BUFF1} 대 {B_BUFF2}\n승자! {B_PLAYER_NAME}의 {B_PLAYER_MON1_NAME}!\p"); // しんぱん『はんてい §  たい §あｎしょうしゃ! §もの §お!ｐ
static const u8 sText_RefJudgement2[] = _("심판: 판정 {B_BUFF1} 대 {B_BUFF2}\n승자! {B_TRAINER1_NAME}의 {B_OPPONENT_MON1_NAME}!\p"); // しんぱん『はんてい §  たい §あｎしょうしゃ! §への §か!ｐ
static const u8 sText_RefJudgement3[] = _("심판: 판정 3 대 3!\n무승부---!\p"); // しんぱん『はんてい 3 たい 3ｎひきわけ---!ｐ
static const u8 sText_DefeatedOpponentByReferee[] = _("{B_PLAYER_MON1_NAME}{B_TXT_EUNNEUN} 판정으로\n상대 {B_OPPONENT_MON1_NAME}{B_TXT_EULREUL} 이겼다!"); // §おは はんていでｎあいての §かに かった!
static const u8 sText_LostToOpponentByReferee[] = _("{B_PLAYER_MON1_NAME}{B_TXT_EUNNEUN} 판정으로\n상대 {B_OPPONENT_MON1_NAME}에게 졌다!"); // §おは はんていでｎあいての §かに まけた!
static const u8 sText_TiedOpponentByReferee[] = _("{B_PLAYER_MON1_NAME}{B_TXT_EUNNEUN} 판정으로\n상대 {B_OPPONENT_MON1_NAME}{B_TXT_WAGWA} 비겼다!"); // おは はんていでｎあいての §かと ひきわけた!
static const u8 sText_RefCommenceBattle[] = _("심판: {B_PLAYER_MON1_NAME} VS {B_OPPONENT_MON1_NAME}\n승부! 시작---!!"); // しんぱん『§お VS §かｎしょうぶ! はじめ---!!

const u8 * const gRefereeStringsTable[] =
{
    sText_RefIfNothingIsDecided,
    sText_RefThatsIt,
    sText_RefJudgeMind,
    sText_RefJudgeSkill,
    sText_RefJudgeBody,
    sText_RefJudgement1,
    sText_RefJudgement2,
    sText_RefJudgement3,
    sText_RefCommenceBattle,
};

static const u8 sText_QuestionForfeitMatch[] = _("승부를 포기하고\n해산하겠습니까?"); // しょうぶを あきらめてｎこうさん しますか?
static const u8 sText_ForfeitedMatch[] = _("{B_PLAYER_NAME}{B_TXT_EUNNEUN}\n승부를 포기했다!"); // §もはｎしょうぶを あきらめた!
static const u8 sText_Trainer1WinText[] = _("{B_TRAINER1_WIN_TEXT}"); // §ゆ
static const u8 sText_Trainer2WinText[] = _("{B_TRAINER2_WIN_TEXT}"); // §ぅ
static const u8 sText_Trainer1Fled[] = _( "{PLAY_SE SE_FLEE}{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_EUNNEUN}\n도망쳤다!"); // ©たち §ふの §へはｎにげだした!
static const u8 sText_PlayerLostAgainstTrainer1[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_WAGWA}의\n승부에서 졌다!"); // §ふの §へｎとの しょうぶに まけた!
static const u8 sText_PlayerBattledToDrawTrainer1[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}{B_TXT_WAGWA}의\n승부에서 비겼다!"); // §ふの §へｎとの しょうぶに ひきわけた!
const u8 gText_RecordBattleToPass[] = _("지금의 배틀을 프런티어패스에\n기록하겠습니까?"); // いまの たたかいを フロンティアパスにｎきろく しますか?
const u8 gText_BattleRecordedOnPass[] = _("{B_PLAYER_NAME}의 배틀이\n프런티어패스에 기록되었다!"); // §もの たたかいがｎフロンティアパスに きろく された!
static const u8 sText_LinkTrainerWantsToBattlePause[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_IGA}\n승부를 걸어왔다!{PAUSE 49}"); // §みがｎしょうぶを しかけてきた!©くぅ
static const u8 sText_TwoLinkTrainersWantToBattlePause[] = _("{B_LINK_OPPONENT1_NAME}{B_TXT_WAGWA} {B_LINK_OPPONENT2_NAME}{B_TXT_IGA}\n승부를 걸어왔다!{PAUSE 49}"); // §みと §むがｎしょうぶを しかけてきた!©くぅ

// This is four lists of moves which use a different attack string in Japanese
// to the default. See the documentation for ChooseTypeOfMoveUsedString for more detail.
static const u16 sGrammarMoveUsedTable[] =
{
    MOVE_SWORDS_DANCE, MOVE_STRENGTH, MOVE_GROWTH,
    MOVE_HARDEN, MOVE_MINIMIZE, MOVE_SMOKESCREEN,
    MOVE_WITHDRAW, MOVE_DEFENSE_CURL, MOVE_EGG_BOMB,
    MOVE_SMOG, MOVE_BONE_CLUB, MOVE_FLASH, MOVE_SPLASH,
    MOVE_ACID_ARMOR, MOVE_BONEMERANG, MOVE_REST, MOVE_SHARPEN,
    MOVE_SUBSTITUTE, MOVE_MIND_READER, MOVE_SNORE,
    MOVE_PROTECT, MOVE_SPIKES, MOVE_ENDURE, MOVE_ROLLOUT,
    MOVE_SWAGGER, MOVE_SLEEP_TALK, MOVE_HIDDEN_POWER,
    MOVE_PSYCH_UP, MOVE_EXTREME_SPEED, MOVE_FOLLOW_ME,
    MOVE_TRICK, MOVE_ASSIST, MOVE_INGRAIN, MOVE_KNOCK_OFF,
    MOVE_CAMOUFLAGE, MOVE_ASTONISH, MOVE_ODOR_SLEUTH,
    MOVE_GRASS_WHISTLE, MOVE_SHEER_COLD, MOVE_MUDDY_WATER,
    MOVE_IRON_DEFENSE, MOVE_BOUNCE, 0,

    MOVE_TELEPORT, MOVE_RECOVER, MOVE_BIDE, MOVE_AMNESIA,
    MOVE_FLAIL, MOVE_TAUNT, MOVE_BULK_UP, 0,

    MOVE_MEDITATE, MOVE_AGILITY, MOVE_MIMIC, MOVE_DOUBLE_TEAM,
    MOVE_BARRAGE, MOVE_TRANSFORM, MOVE_STRUGGLE, MOVE_SCARY_FACE,
    MOVE_CHARGE, MOVE_WISH, MOVE_BRICK_BREAK, MOVE_YAWN,
    MOVE_FEATHER_DANCE, MOVE_TEETER_DANCE, MOVE_MUD_SPORT,
    MOVE_FAKE_TEARS, MOVE_WATER_SPORT, MOVE_CALM_MIND, 0,

    MOVE_POUND, MOVE_SCRATCH, MOVE_VICE_GRIP,
    MOVE_WING_ATTACK, MOVE_FLY, MOVE_BIND, MOVE_SLAM,
    MOVE_HORN_ATTACK, MOVE_WRAP, MOVE_THRASH, MOVE_TAIL_WHIP,
    MOVE_LEER, MOVE_BITE, MOVE_GROWL, MOVE_ROAR,
    MOVE_SING, MOVE_PECK, MOVE_ABSORB, MOVE_STRING_SHOT,
    MOVE_EARTHQUAKE, MOVE_FISSURE, MOVE_DIG, MOVE_TOXIC,
    MOVE_SCREECH, MOVE_METRONOME, MOVE_LICK, MOVE_CLAMP,
    MOVE_CONSTRICT, MOVE_POISON_GAS, MOVE_BUBBLE,
    MOVE_SLASH, MOVE_SPIDER_WEB, MOVE_NIGHTMARE, MOVE_CURSE,
    MOVE_FORESIGHT, MOVE_CHARM, MOVE_ATTRACT, MOVE_ROCK_SMASH,
    MOVE_UPROAR, MOVE_SPIT_UP, MOVE_SWALLOW, MOVE_TORMENT,
    MOVE_FLATTER, MOVE_ROLE_PLAY, MOVE_ENDEAVOR, MOVE_TICKLE,
    MOVE_COVET, 0
};

static const u8 sDummyWeirdStatusString[] = {EOS, EOS, EOS, EOS, EOS, EOS, EOS, EOS, 0, 0};

static const struct BattleWindowText sTextOnWindowsInfo_Normal[] =
{
// The corresponding WindowTemplate is gStandardBattleWindowTemplates[] within src/battle_bg.c
    { // 0 Standard battle message
        .fillValue = PIXEL_FILL(0xF),
        .fontId = 1,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 1,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    { // 1 "What will (pokemon) do?"
        .fillValue = PIXEL_FILL(0xF),
        .fontId = 1,
        .x = 1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    { // 2 "Fight/Pokemon/Bag/Run"
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 3 Top left move
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 7,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 4 Top right move
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 7,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 5 Bottom left move
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 7,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 6 Bottom right move
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 7,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 7 "PP"
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    { // 8
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 9 PP remaining
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = 2,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    { // 10 "type"
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 7,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 11 "switch which?"
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 7,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 12 "gText_BattleYesNoChoice"
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 13
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 14
        .fillValue = PIXEL_FILL(0),
        .fontId = 1,
        .x = 32,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 0,
        .shadowColor = 2,
    },
    { // 15
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 16
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 17
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 18
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 19
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 20
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 21
        .fillValue = PIXEL_FILL(0),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 0,
        .shadowColor = 6,
    },
    { // 22
        .fillValue = PIXEL_FILL(0),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 0,
        .shadowColor = 6,
    },
    { // 23
        .fillValue = PIXEL_FILL(0x0),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 0,
        .shadowColor = 6,
    },
};

static const struct BattleWindowText sTextOnWindowsInfo_Arena[] =
{
    { // 0
        .fillValue = PIXEL_FILL(0xF),
        .fontId = 1,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 1,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    { // 1
        .fillValue = PIXEL_FILL(0xF),
        .fontId = 1,
        .x = 1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    { // 2
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 3
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 7,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 4
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 7,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 5
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 7,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 6
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 7,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 7
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    { // 8
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 9
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = 2,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    { // 10
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 7,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 11
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 7,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 12
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 13
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 14
        .fillValue = PIXEL_FILL(0),
        .fontId = 1,
        .x = 32,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 0,
        .shadowColor = 2,
    },
    { // 15
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 16
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 17
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 18
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 19
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 20
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 21
        .fillValue = PIXEL_FILL(0xE),
        .fontId = 1,
        .x = -1,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    { // 22
        .fillValue = PIXEL_FILL(0x1),
        .fontId = 1,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 1,
        .fgColor = 2,
        .bgColor = 1,
        .shadowColor = 3,
    },
};

static const struct BattleWindowText *const sBattleTextOnWindowsInfo[] =
{
    sTextOnWindowsInfo_Normal, sTextOnWindowsInfo_Arena
};

static const u8 sRecordedBattleTextSpeeds[] = {8, 4, 1, 0};

// code
void BufferStringBattle(u16 stringID)
{
    s32 i;
    const u8 *stringPtr = NULL;

    gBattleMsgDataPtr = (struct BattleMsgData*)(&gBattleBufferA[gActiveBattler][4]);
    gLastUsedItem = gBattleMsgDataPtr->lastItem;
    gLastUsedAbility = gBattleMsgDataPtr->lastAbility;
    gBattleScripting.battler = gBattleMsgDataPtr->scrActive;
    *(&gBattleStruct->field_52) = gBattleMsgDataPtr->unk1605E;
    *(&gBattleStruct->hpScale) = gBattleMsgDataPtr->hpScale;
    gPotentialItemEffectBattler = gBattleMsgDataPtr->itemEffectBattler;
    *(&gBattleStruct->stringMoveType) = gBattleMsgDataPtr->moveType;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        sBattlerAbilities[i] = gBattleMsgDataPtr->abilities[i];
    }
    for (i = 0; i < TEXT_BUFF_ARRAY_COUNT; i++)
    {
        gBattleTextBuff1[i] = gBattleMsgDataPtr->textBuffs[0][i];
        gBattleTextBuff2[i] = gBattleMsgDataPtr->textBuffs[1][i];
        gBattleTextBuff3[i] = gBattleMsgDataPtr->textBuffs[2][i];
    }

    switch (stringID)
    {
    case STRINGID_INTROMSG: // first battle msg
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_x2000000))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_x800000)
                {
                    stringPtr = sText_TwoTrainersWantToBattle;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = sText_TwoLinkTrainersWantToBattlePause;
                    else
                        stringPtr = sText_TwoLinkTrainersWantToBattle;
                }
                else
                {
                    if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                        stringPtr = sText_Trainer1WantsToBattle;
                    else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = sText_LinkTrainerWantsToBattlePause;
                    else
                        stringPtr = sText_LinkTrainerWantsToBattle;
                }
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                    stringPtr = sText_TwoTrainersWantToBattle;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_TwoTrainersWantToBattle;
                else
                    stringPtr = sText_Trainer1WantsToBattle;
            }
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY)
                stringPtr = sText_WildPkmnAppeared2;
            else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) // interesting, looks like they had something planned for wild double battles
                stringPtr = sText_TwoWildPkmnAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_WALLY_TUTORIAL)
                stringPtr = sText_WildPkmnAppearedPause;
            else
                stringPtr = sText_WildPkmnAppeared;
        }
        break;
    case STRINGID_INTROSENDOUT: // poke first send-out
        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                    stringPtr = sText_InGamePartnerSentOutZGoN;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_GoTwoPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkPartnerSentOutPkmnGoPkmn;
                else
                    stringPtr = sText_GoTwoPkmn;
            }
            else
            {
                stringPtr = sText_GoPkmn;
            }
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_TwoTrainersSentPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_x800000)
                    stringPtr = sText_TwoTrainersSentPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_TwoLinkTrainersSentOutPkmn;
                else if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_x2000000))
                    stringPtr = sText_LinkTrainerSentOutTwoPkmn;
                else
                    stringPtr = sText_Trainer1SentOutTwoPkmn;
            }
            else
            {
                if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_x2000000)))
                    stringPtr = sText_Trainer1SentOutPkmn;
                else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                    stringPtr = sText_Trainer1SentOutPkmn;
                else
                    stringPtr = sText_LinkTrainerSentOutPkmn;
            }
        }
        break;
    case STRINGID_RETURNMON: // sending poke to ball msg
        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0)
                stringPtr = sText_PkmnThatsEnough;
            else if (*(&gBattleStruct->hpScale) == 1 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = sText_PkmnComeBack;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sText_PkmnOkComeBack;
            else
                stringPtr = sText_PkmnGoodComeBack;
        }
        else
        {
            if (gTrainerBattleOpponent_A == TRAINER_LINK_OPPONENT || gBattleTypeFlags & BATTLE_TYPE_x2000000)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkTrainer2WithdrewPkmn;
                else
                    stringPtr = sText_LinkTrainer1WithdrewPkmn;
            }
            else
            {
                stringPtr = sText_Trainer1WithdrewPkmn;
            }
        }
        break;
    case STRINGID_SWITCHINMON: // switch-in msg
        if (GetBattlerSide(gBattleScripting.battler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = sText_GoPkmn2;
            else if (*(&gBattleStruct->hpScale) == 1)
                stringPtr = sText_DoItPkmn;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sText_GoForItPkmn;
            else
                stringPtr = sText_YourFoesWeakGetEmPkmn;
        }
        else
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_x2000000))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_x800000)
                {
                    if (gBattleScripting.battler == 1)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_Trainer2SentOutPkmn;
                }
                else
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                        stringPtr = sText_LinkTrainerMultiSentOutPkmn;
                    else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_LinkTrainerSentOutPkmn2;
                }
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                {
                    if (gBattleScripting.battler == 1)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_Trainer2SentOutPkmn;
                }
                else
                {
                    stringPtr = sText_Trainer1SentOutPkmn2;
                }
            }
        }
        break;
    case STRINGID_USEDMOVE: // pokemon used a move msg
        ChooseMoveUsedParticle(gBattleTextBuff1);

        if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT)
            StringCopy(gBattleTextBuff2, sATypeMove_Table[*(&gBattleStruct->stringMoveType)]);
        else
            StringCopy(gBattleTextBuff2, gMoveNames[gBattleMsgDataPtr->currentMove]);

        ChooseTypeOfMoveUsedString(gBattleTextBuff2);
        stringPtr = sText_AttackerUsedX;
        break;
    case STRINGID_BATTLEEND: // battle end
        if (gBattleTextBuff1[0] & B_OUTCOME_LINK_BATTLE_RAN)
        {
            gBattleTextBuff1[0] &= ~(B_OUTCOME_LINK_BATTLE_RAN);
            if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTextBuff1[0] == B_OUTCOME_LOST || gBattleTextBuff1[0] == B_OUTCOME_DREW)
                stringPtr = sText_GotAwaySafely;
            else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                stringPtr = sText_TwoWildFled;
            else
                stringPtr = sText_WildFled;
        }
        else
        {
            if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    if (gBattleTypeFlags & BATTLE_TYPE_x800000)
                        stringPtr = sText_TwoInGameTrainersDefeated;
                    else
                        stringPtr = sText_TwoLinkTrainersDefeated;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostToTwo;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawVsTwo;
                    break;
                }
            }
            else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainerTrainer1;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstTrainer1;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawTrainer1;
                    break;
                }
            }
            else
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainer;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstLinkTrainer;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawLinkTrainer;
                    break;
                }
            }
        }
        break;
    default: // load a string from the table
        if (stringID >= BATTLESTRINGS_COUNT + BATTLESTRINGS_ID_ADDER)
        {
            gDisplayedStringBattle[0] = EOS;
            return;
        }
        else
        {
            stringPtr = gBattleStringsTable[stringID - BATTLESTRINGS_ID_ADDER];
        }
        break;
    }

    BattleStringExpandPlaceholdersToDisplayedString(stringPtr);
}

u32 BattleStringExpandPlaceholdersToDisplayedString(const u8* src)
{
    BattleStringExpandPlaceholders(src, gDisplayedStringBattle);
}

static const u8* TryGetStatusString(u8 *src)
{
    u32 i;
    u8 status[8];
    u32 chars1, chars2;
    u8* statusPtr;

    memcpy(status, sDummyWeirdStatusString, 8);

    statusPtr = status;
    for (i = 0; i < 8; i++)
    {
        if (*src == EOS) break; // one line required to match -g
        *statusPtr = *src;
        src++;
        statusPtr++;
    }

    chars1 = *(u32*)(&status[0]);
    chars2 = *(u32*)(&status[4]);

    for (i = 0; i < ARRAY_COUNT(gStatusConditionStringsTable); i++)
    {
        if (chars1 == *(u32*)(&gStatusConditionStringsTable[i][0][0])
            && chars2 == *(u32*)(&gStatusConditionStringsTable[i][0][4]))
            return gStatusConditionStringsTable[i][1];
    }
    return NULL;
}

#define HANDLE_NICKNAME_STRING_CASE(battlerId, monIndex)                \
    if (GetBattlerSide(battlerId) != B_SIDE_PLAYER)                     \
    {                                                                   \
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)                     \
            toCpy = sText_FoePkmnPrefix;                                \
        else                                                            \
            toCpy = sText_WildPkmnPrefix;                               \
        while (*toCpy != EOS)                                           \
        {                                                               \
            dst[dstID] = *toCpy;                                        \
            dstID++;                                                    \
            toCpy++;                                                    \
        }                                                               \
        GetMonData(&gEnemyParty[monIndex], MON_DATA_NICKNAME, text);    \
    }                                                                   \
    else                                                                \
    {                                                                   \
        GetMonData(&gPlayerParty[monIndex], MON_DATA_NICKNAME, text);   \
    }                                                                   \
    StringGetEnd10(text);                                               \
    toCpy = text;

u32 BattleStringExpandPlaceholders(const u8 *src, u8 *dst)
{
    u32 dstID = 0; // if they used dstID, why not use srcID as well?
    const u8 *toCpy = NULL;
    u8 text[30];
    u8 multiplayerId;
    u16 prevChar;
    s32 i;

    if (gBattleTypeFlags & BATTLE_TYPE_x2000000)
        multiplayerId = gUnknown_0203C7B4;
    else
        multiplayerId = GetMultiplayerId();

    while (*src != EOS)
    {
        if (*src == PLACEHOLDER_BEGIN)
        {
            src++;
            switch (*src)
            {
            case B_TXT_BUFF1:
                if (gBattleTextBuff1[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff1, gStringVar1);
                    toCpy = gStringVar1;
                }
                else
                {
                    toCpy = TryGetStatusString(gBattleTextBuff1);
                    if (toCpy == NULL)
                        toCpy = gBattleTextBuff1;
                }
                break;
            case B_TXT_BUFF2:
                if (gBattleTextBuff2[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff2, gStringVar2);
                    toCpy = gStringVar2;
                }
                else
                {
                    BattleStringExpandPlaceholders(gBattleTextBuff2, gStringVar2);
                    toCpy = gStringVar2;
                }
                break;
            case B_TXT_BUFF3:
                if (gBattleTextBuff3[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff3, gStringVar3);
                    toCpy = gStringVar3;
                }
                else
                    toCpy = gBattleTextBuff3;
                break;
            case B_TXT_EUNNEUN:
                if (sHasJong)
                    toCpy = gText_ExpandedPlaceholder_Eun;
                else
                    toCpy = gText_ExpandedPlaceholder_Neun;
                break;
            case B_TXT_IGA:
                if (sHasJong)
                    toCpy = gText_ExpandedPlaceholder_I;
                else
                    toCpy = gText_ExpandedPlaceholder_Ga;
                break;
            case B_TXT_EULREUL:
                if (sHasJong)
                    toCpy = gText_ExpandedPlaceholder_Eul;
                else
                    toCpy = gText_ExpandedPlaceholder_Reul;
                break;
            case B_TXT_EU:
                if (sHasJong)
                    toCpy = gText_ExpandedPlaceholder_Eu;
                else
                    toCpy = gText_ExpandedPlaceholder_Empty;
                break;
            case B_TXT_I:
                if (sHasJong)
                    toCpy = gText_ExpandedPlaceholder_I;
                else
                    toCpy = gText_ExpandedPlaceholder_Empty;
                break;
            case B_TXT_WAGWA:
                if (sHasJong)
                    toCpy = gText_ExpandedPlaceholder_Gwa;
                else
                    toCpy = gText_ExpandedPlaceholder_Wa;
                break;
            case B_TXT_AYA:
                if (sHasJong)
                    toCpy = gText_ExpandedPlaceholder_A;
                else
                    toCpy = gText_ExpandedPlaceholder_Ya;
                break;
            case B_TXT_COPY_VAR_1:
                toCpy = gStringVar1;
                break;
            case B_TXT_COPY_VAR_2:
                toCpy = gStringVar2;
                break;
            case B_TXT_COPY_VAR_3:
                toCpy = gStringVar3;
                break;
            case B_TXT_PLAYER_MON1_NAME: // first player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)]],
                           MON_DATA_NICKNAME, text);
                StringGetEnd10(text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON1_NAME: // first enemy poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)]],
                           MON_DATA_NICKNAME, text);
                StringGetEnd10(text);
                toCpy = text;
                break;
            case B_TXT_PLAYER_MON2_NAME: // second player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)]],
                           MON_DATA_NICKNAME, text);
                StringGetEnd10(text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON2_NAME: // second enemy poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT)]],
                           MON_DATA_NICKNAME, text);
                StringGetEnd10(text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON1_NAME: // link first player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id]],
                           MON_DATA_NICKNAME, text);
                StringGetEnd10(text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON1_NAME: // link first opponent poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 1]],
                           MON_DATA_NICKNAME, text);
                StringGetEnd10(text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON2_NAME: // link second player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 2]],
                           MON_DATA_NICKNAME, text);
                StringGetEnd10(text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON2_NAME: // link second opponent poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 3]],
                           MON_DATA_NICKNAME, text);
                StringGetEnd10(text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX_MON1: // attacker name with prefix, only battlerId 0/1
                HANDLE_NICKNAME_STRING_CASE(gBattlerAttacker,
                                            gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker))])
                break;
            case B_TXT_ATK_PARTNER_NAME: // attacker partner name
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker)) + 2]], MON_DATA_NICKNAME, text);
                else
                    GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker)) + 2]], MON_DATA_NICKNAME, text);

                StringGetEnd10(text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX: // attacker name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerAttacker, gBattlerPartyIndexes[gBattlerAttacker])
                break;
            case B_TXT_DEF_NAME_WITH_PREFIX: // target name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerTarget, gBattlerPartyIndexes[gBattlerTarget])
                break;
            case B_TXT_EFF_NAME_WITH_PREFIX: // effect battlerId name with prefix
                HANDLE_NICKNAME_STRING_CASE(gEffectBattler, gBattlerPartyIndexes[gEffectBattler])
                break;
            case B_TXT_ACTIVE_NAME_WITH_PREFIX: // active battlerId name with prefix
                HANDLE_NICKNAME_STRING_CASE(gActiveBattler, gBattlerPartyIndexes[gActiveBattler])
                break;
            case B_TXT_SCR_ACTIVE_NAME_WITH_PREFIX: // scripting active battlerId name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler, gBattlerPartyIndexes[gBattleScripting.battler])
                break;
            case B_TXT_CURRENT_MOVE: // current move name
                if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT)
                    toCpy = sATypeMove_Table[gBattleStruct->stringMoveType];
                else
                    toCpy = gMoveNames[gBattleMsgDataPtr->currentMove];
                break;
            case B_TXT_LAST_MOVE: // originally used move name
                if (gBattleMsgDataPtr->originallyUsedMove >= MOVES_COUNT)
                    toCpy = sATypeMove_Table[gBattleStruct->stringMoveType];
                else
                    toCpy = gMoveNames[gBattleMsgDataPtr->originallyUsedMove];
                break;
            case B_TXT_LAST_ITEM: // last used item
                if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_x2000000))
                {
                    if (gLastUsedItem == ITEM_ENIGMA_BERRY)
                    {
                        if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
                        {
                            if ((gBattleScripting.multiplayerId != 0 && (gPotentialItemEffectBattler & BIT_SIDE))
                                || (gBattleScripting.multiplayerId == 0 && !(gPotentialItemEffectBattler & BIT_SIDE)))
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                            {
                                toCpy = sText_EnigmaBerry;
                            }
                        }
                        else
                        {
                            if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                                toCpy = sText_EnigmaBerry;
                        }
                    }
                    else
                    {
                        CopyItemName(gLastUsedItem, text);
                        toCpy = text;
                    }
                }
                else
                {
                    CopyItemName(gLastUsedItem, text);
                    toCpy = text;
                }
                break;
            case B_TXT_LAST_ABILITY: // last used ability
                toCpy = gAbilityNames[gLastUsedAbility];
                break;
            case B_TXT_ATK_ABILITY: // attacker ability
                toCpy = gAbilityNames[sBattlerAbilities[gBattlerAttacker]];
                break;
            case B_TXT_DEF_ABILITY: // target ability
                toCpy = gAbilityNames[sBattlerAbilities[gBattlerTarget]];
                break;
            case B_TXT_SCR_ACTIVE_ABILITY: // scripting active ability
                toCpy = gAbilityNames[sBattlerAbilities[gBattleScripting.battler]];
                break;
            case B_TXT_EFF_ABILITY: // effect battlerId ability
                toCpy = gAbilityNames[sBattlerAbilities[gEffectBattler]];
                break;
            case B_TXT_TRAINER1_CLASS: // trainer class name
                if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
                    toCpy = gTrainerClassNames[GetSecretBaseTrainerClass()];
                else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                    toCpy = gTrainerClassNames[GetUnionRoomTrainerClass()];
                else if (gTrainerBattleOpponent_A == TRAINER_FRONTIER_BRAIN)
                    toCpy = gTrainerClassNames[GetFrontierBrainTrainerClass()];
                else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                    toCpy = gTrainerClassNames[GetFrontierOpponentClass(gTrainerBattleOpponent_A)];
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                    toCpy = gTrainerClassNames[GetTrainerHillOpponentClass(gTrainerBattleOpponent_A)];
                else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
                    toCpy = gTrainerClassNames[GetEreaderTrainerClassId()];
                else
                    toCpy = gTrainerClassNames[gTrainers[gTrainerBattleOpponent_A].trainerClass];
                break;
            case B_TXT_TRAINER1_NAME: // trainer1 name
                if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
                {
                    for (i = 0; i < (s32) ARRAY_COUNT(gBattleResources->secretBase->trainerName); i++)
                        text[i] = gBattleResources->secretBase->trainerName[i];
                    text[i] = EOS;
                    ConvertInternationalString(text, gBattleResources->secretBase->language);
                    toCpy = text;
                }
                else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                {
                    toCpy = gLinkPlayers[multiplayerId ^ BIT_SIDE].name;
                }
                else if (gTrainerBattleOpponent_A == TRAINER_FRONTIER_BRAIN)
                {
                    CopyFrontierBrainTrainerName(text);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    GetFrontierTrainerName(text, gTrainerBattleOpponent_A);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    GetTrainerHillTrainerName(text, gTrainerBattleOpponent_A);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
                {
                    GetEreaderTrainerName(text);
                    toCpy = text;
                }
                else
                {
                    toCpy = gTrainers[gTrainerBattleOpponent_A].trainerName;
                }
                break;
            case B_TXT_LINK_PLAYER_NAME: // link player name
                toCpy = gLinkPlayers[multiplayerId].name;
                break;
            case B_TXT_LINK_PARTNER_NAME: // link partner name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_PARTNER(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT1_NAME: // link opponent 1 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_OPPOSITE(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT2_NAME: // link opponent 2 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_PARTNER(BATTLE_OPPOSITE(gLinkPlayers[multiplayerId].id)))].name;
                break;
            case B_TXT_LINK_SCR_TRAINER_NAME: // link scripting active name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(gBattleScripting.battler)].name;
                break;
            case B_TXT_PLAYER_NAME: // player name
                if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                    toCpy = gLinkPlayers[0].name;
                else
                    toCpy = gSaveBlock2Ptr->playerName;
                break;
            case B_TXT_TRAINER1_LOSE_TEXT: // trainerA lose text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerALoseText();
                }
                break;
            case B_TXT_TRAINER1_WIN_TEXT: // trainerA win text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                break;
            case B_TXT_26: // ?
                HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler, *(&gBattleStruct->field_52))
                break;
            case B_TXT_PC_CREATOR_NAME: // lanette pc
                if (FlagGet(FLAG_SYS_PC_LANETTE))
                    toCpy = sText_Lanettes;
                else
                    toCpy = sText_Someones;
                break;
            case B_TXT_ATK_PREFIX2:
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_DEF_PREFIX2:
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_ATK_PREFIX1:
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_DEF_PREFIX1:
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_ATK_PREFIX3:
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_DEF_PREFIX3:
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_TRAINER2_CLASS:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                    toCpy = gTrainerClassNames[GetFrontierOpponentClass(gTrainerBattleOpponent_B)];
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                    toCpy = gTrainerClassNames[GetTrainerHillOpponentClass(gTrainerBattleOpponent_B)];
                else
                    toCpy = gTrainerClassNames[gTrainers[gTrainerBattleOpponent_B].trainerClass];
                break;
            case B_TXT_TRAINER2_NAME:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    GetFrontierTrainerName(text, gTrainerBattleOpponent_B);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    GetTrainerHillTrainerName(text, gTrainerBattleOpponent_B);
                    toCpy = text;
                }
                else
                {
                    toCpy = gTrainers[gTrainerBattleOpponent_B].trainerName;
                }
                break;
            case B_TXT_TRAINER2_LOSE_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerBLoseText();
                }
                break;
            case B_TXT_TRAINER2_WIN_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                break;
            case B_TXT_PARTNER_CLASS:
                toCpy = gTrainerClassNames[GetFrontierOpponentClass(gPartnerTrainerId)];
                break;
            case B_TXT_PARTNER_NAME:
                GetFrontierTrainerName(text, gPartnerTrainerId);
                toCpy = text;
                break;
            }

            // missing if (toCpy != NULL) check
            while (*toCpy != EOS)
            {
                dst[dstID] = *toCpy;
                dstID++;
                toCpy++;
            }
            if (*src == B_TXT_TRAINER1_LOSE_TEXT || *src == B_TXT_TRAINER2_LOSE_TEXT
                || *src == B_TXT_TRAINER1_WIN_TEXT || *src == B_TXT_TRAINER2_WIN_TEXT)
            {
                dst[dstID] = EXT_CTRL_CODE_BEGIN;
                dstID++;
                dst[dstID] = EXT_CTRL_CODE_PAUSE_UNTIL_PRESS;
                dstID++;
            }
        }
        else
        {
            dst[dstID] = *src;
            dstID++;
        }
        src++;

        // 종성유무 체크
        prevChar = (dst[dstID - 2] << 8) | dst[dstID - 1];
        sHasJong = HasJong(prevChar);
    }

    dst[dstID] = *src;
    dstID++;

    return dstID;
}

static void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst)
{
    u32 srcID = 1;
    u32 value = 0;
    u8 text[12];
    u16 hword;

    *dst = EOS;
    while (src[srcID] != B_BUFF_EOS)
    {
        switch (src[srcID])
        {
        case B_TXT_EUNNEUN:
            if (sHasJong)
                StringAppend(dst, gText_ExpandedPlaceholder_Eun);
            else
                StringAppend(dst, gText_ExpandedPlaceholder_Neun);
            srcID += 1;
            break;
        case B_TXT_IGA:
            if (sHasJong)
                StringAppend(dst, gText_ExpandedPlaceholder_I);
            else
                StringAppend(dst, gText_ExpandedPlaceholder_Ga);
            srcID += 1;
            break;
        case B_TXT_EULREUL:
            if (sHasJong)
                StringAppend(dst, gText_ExpandedPlaceholder_Eul);
            else
                StringAppend(dst, gText_ExpandedPlaceholder_Reul);
            srcID += 1;
            break;
        case B_TXT_EU:
            if (sHasJong)
                StringAppend(dst, gText_ExpandedPlaceholder_Eu);
            else
                StringAppend(dst, gText_ExpandedPlaceholder_Empty);
            srcID += 1;
            break;
        case B_TXT_I:
            if (sHasJong)
                StringAppend(dst, gText_ExpandedPlaceholder_I);
            else
                StringAppend(dst, gText_ExpandedPlaceholder_Empty);
            srcID += 1;
            break;
        case B_TXT_WAGWA:
            if (sHasJong)
                StringAppend(dst, gText_ExpandedPlaceholder_Gwa);
            else
                StringAppend(dst, gText_ExpandedPlaceholder_Wa);
            srcID += 1;
            break;
        case B_TXT_AYA:
            if (sHasJong)
                StringAppend(dst, gText_ExpandedPlaceholder_A);
            else
                StringAppend(dst, gText_ExpandedPlaceholder_Ya);
            srcID += 1;
            break;
        case B_BUFF_STRING: // battle string
            hword = T1_READ_16(&src[srcID + 1]);
            StringAppend(dst, gBattleStringsTable[hword - BATTLESTRINGS_ID_ADDER]);
            srcID += 3;
            break;
        case B_BUFF_NUMBER: // int to string
            switch (src[srcID + 1])
            {
            case 1:
                value = src[srcID + 3];
                break;
            case 2:
                value = T1_READ_16(&src[srcID + 3]);
                break;
            case 4:
                value = T1_READ_32(&src[srcID + 3]);
                break;
            }
            ConvertIntToDecimalStringN(dst, value, STR_CONV_MODE_LEFT_ALIGN, src[srcID + 2]);
            srcID += src[srcID + 1] + 3;
            break;
        case B_BUFF_MOVE: // move name
            StringAppend(dst, gMoveNames[T1_READ_16(&src[srcID + 1])]);
            srcID += 3;
            break;
        case B_BUFF_TYPE: // type name
            StringAppend(dst, gTypeNames[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_MON_NICK_WITH_PREFIX: // poke nick with prefix
            if (GetBattlerSide(src[srcID + 1]) == B_SIDE_PLAYER)
            {
                GetMonData(&gPlayerParty[src[srcID + 2]], MON_DATA_NICKNAME, text);
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                    StringAppend(dst, sText_FoePkmnPrefix);
                else
                    StringAppend(dst, sText_WildPkmnPrefix);

                GetMonData(&gEnemyParty[src[srcID + 2]], MON_DATA_NICKNAME, text);
            }
            StringGetEnd10(text);
            StringAppend(dst, text);
            srcID += 3;
            break;
        case B_BUFF_STAT: // stats
            StringAppend(dst, gStatNamesTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_SPECIES: // species name
            GetSpeciesName(dst, T1_READ_16(&src[srcID + 1]));
            srcID += 3;
            break;
        case B_BUFF_MON_NICK: // poke nick without prefix
            if (GetBattlerSide(src[srcID + 1]) == B_SIDE_PLAYER)
                GetMonData(&gPlayerParty[src[srcID + 2]], MON_DATA_NICKNAME, dst);
            else
                GetMonData(&gEnemyParty[src[srcID + 2]], MON_DATA_NICKNAME, dst);
            StringGetEnd10(dst);
            srcID += 3;
            break;
        case B_BUFF_NEGATIVE_FLAVOR: // flavor table
            StringAppend(dst, gPokeblockWasTooXStringTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_ABILITY: // ability names
            StringAppend(dst, gAbilityNames[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_ITEM: // item name
            hword = T1_READ_16(&src[srcID + 1]);
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_x2000000))
            {
                if (hword == ITEM_ENIGMA_BERRY)
                {
                    if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                    {
                        StringCopy(dst, gEnigmaBerries[gPotentialItemEffectBattler].name);
                        StringAppend(dst, sText_BerrySuffix);
                    }
                    else
                    {
                        StringAppend(dst, sText_EnigmaBerry);
                    }
                }
                else
                {
                    CopyItemName(hword, dst);
                }
            }
            else
            {
                CopyItemName(hword, dst);
            }
            srcID += 3;
            break;
        }
    }
}

// Loads one of two text strings into the provided buffer. This is functionally
// unused, since the value loaded into the buffer is not read; it loaded one of
// two particles (either "は" or "の") which works in tandem with ChooseTypeOfMoveUsedString
// below to effect changes in the meaning of the line.
static void ChooseMoveUsedParticle(u8* textBuff)
{
    s32 counter = 0;
    u32 i = 0;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == 0)
            counter++;
        if (sGrammarMoveUsedTable[i++] == gBattleMsgDataPtr->currentMove)
            break;
    }

    if (counter >= 0)
    {
        if (counter <= 2)
            StringCopy(textBuff, sText_SpaceIs); // is
        else if (counter <= MAX_MON_MOVES)
            StringCopy(textBuff, sText_ApostropheS); // 's
    }
}

// Appends "!" to the text buffer `dst`. In the original Japanese this looked
// into the table of moves at sGrammarMoveUsedTable and varied the line accordingly.
//
// sText_ExclamationMark was a plain "!", used for any attack not on the list.
// It resulted in the translation "<NAME>'s <ATTACK>!".
//
// sText_ExclamationMark2 was "を つかった！". This resulted in the translation
// "<NAME> used <ATTACK>!", which was used for all attacks in English.
//
// sText_ExclamationMark3 was "した！". This was used for those moves whose
// names were verbs, such as Recover, and resulted in translations like "<NAME>
// recovered itself!".
//
// sText_ExclamationMark4 was "を した！" This resulted in a translation of
// "<NAME> did an <ATTACK>!".
//
// sText_ExclamationMark5 was " こうげき！" This resulted in a translation of
// "<NAME>'s <ATTACK> attack!".
static void ChooseTypeOfMoveUsedString(u8* dst)
{
    s32 counter = 0;
    s32 i = 0;

    while (*dst != EOS)
        dst++;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == MOVE_NONE)
            counter++;
        if (sGrammarMoveUsedTable[i++] == gBattleMsgDataPtr->currentMove)
            break;
    }

    switch (counter)
    {
    case 0:
        StringCopy(dst, sText_ExclamationMark);
        break;
    case 1:
        StringCopy(dst, sText_ExclamationMark2);
        break;
    case 2:
        StringCopy(dst, sText_ExclamationMark3);
        break;
    case 3:
        StringCopy(dst, sText_ExclamationMark4);
        break;
    case 4:
        StringCopy(dst, sText_ExclamationMark5);
        break;
    }
}

void BattlePutTextOnWindow(const u8 *text, u8 windowId)
{
    const struct BattleWindowText *textInfo = sBattleTextOnWindowsInfo[gBattleScripting.windowsType];
    bool32 copyToVram;
    struct TextPrinterTemplate printerTemplate;
    u8 speed;

    if (windowId & 0x80)
    {
        windowId &= ~(0x80);
        copyToVram = FALSE;
    }
    else
    {
        FillWindowPixelBuffer(windowId, textInfo[windowId].fillValue);
        copyToVram = TRUE;
    }

    printerTemplate.currentChar = text;
    printerTemplate.windowId = windowId;
    printerTemplate.fontId = textInfo[windowId].fontId;
    printerTemplate.x = textInfo[windowId].x;
    printerTemplate.y = textInfo[windowId].y;
    printerTemplate.currentX = printerTemplate.x;
    printerTemplate.currentY = printerTemplate.y;
    printerTemplate.letterSpacing = textInfo[windowId].letterSpacing;
    printerTemplate.lineSpacing = textInfo[windowId].lineSpacing;
    printerTemplate.unk = 0;
    printerTemplate.fgColor = textInfo[windowId].fgColor;
    printerTemplate.bgColor = textInfo[windowId].bgColor;
    printerTemplate.shadowColor = textInfo[windowId].shadowColor;

    if (printerTemplate.x == 0xFF)
    {
        u32 width = sub_80397C4(gBattleScripting.windowsType, windowId);
        s32 alignX = GetStringCenterAlignXOffsetWithLetterSpacing(printerTemplate.fontId, printerTemplate.currentChar, width, printerTemplate.letterSpacing);
        printerTemplate.x = printerTemplate.currentX = alignX;
    }

    if (windowId == 0x16)
        gTextFlags.useAlternateDownArrow = 0;
    else
        gTextFlags.useAlternateDownArrow = 1;

    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED))
        gTextFlags.autoScroll = 1;
    else
        gTextFlags.autoScroll = 0;

    if (windowId == 0 || windowId == 0x16)
    {
        if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_x2000000))
            speed = 1;
        else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            speed = sRecordedBattleTextSpeeds[GetTextSpeedInRecordedBattle()];
        else
            speed = GetPlayerTextSpeedDelay();

        gTextFlags.canABSpeedUpPrint = 1;
    }
    else
    {
        speed = textInfo[windowId].speed;
        gTextFlags.canABSpeedUpPrint = 0;
    }

    AddTextPrinter(&printerTemplate, speed, NULL);

    if (copyToVram)
    {
        PutWindowTilemap(windowId);
        CopyWindowToVram(windowId, 3);
    }
}

void SetPpNumbersPaletteInMoveSelection(void)
{
    struct ChooseMoveStruct *chooseMoveStruct = (struct ChooseMoveStruct*)(&gBattleBufferA[gActiveBattler][4]);
    const u16 *palPtr = gUnknown_08D85620;
    u8 var = GetCurrentPpToMaxPpState(chooseMoveStruct->currentPp[gMoveSelectionCursor[gActiveBattler]],
                         chooseMoveStruct->maxPp[gMoveSelectionCursor[gActiveBattler]]);

    gPlttBufferUnfaded[92] = palPtr[(var * 2) + 0];
    gPlttBufferUnfaded[91] = palPtr[(var * 2) + 1];

    CpuCopy16(&gPlttBufferUnfaded[92], &gPlttBufferFaded[92], sizeof(u16));
    CpuCopy16(&gPlttBufferUnfaded[91], &gPlttBufferFaded[91], sizeof(u16));
}

u8 GetCurrentPpToMaxPpState(u8 currentPp, u8 maxPp)
{
    if (maxPp == currentPp)
    {
        return 3;
    }
    else if (maxPp <= 2)
    {
        if (currentPp > 1)
            return 3;
        else
            return 2 - currentPp;
    }
    else if (maxPp <= 7)
    {
        if (currentPp > 2)
            return 3;
        else
            return 2 - currentPp;
    }
    else
    {
        if (currentPp == 0)
            return 2;
        if (currentPp <= maxPp / 4)
            return 1;
        if (currentPp > maxPp / 2)
            return 3;
    }

    return 0;
}
