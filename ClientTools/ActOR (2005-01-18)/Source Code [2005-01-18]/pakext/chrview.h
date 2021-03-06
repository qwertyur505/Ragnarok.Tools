#ifndef __MY_CHRVIEW__
#define __MY_CHRVIEW__

#include <libintl.h>
#include <locale.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include "../common/global.h"
#include "../common/pak.h"
#include "../common/Sprite.h"
#include "../common/vec.h"
#include "../common/codeconv.h"

#define GL_WIN_WIDTH 300
#define GL_WIN_HEIGHT 300

#define MAX_PC_PAT 9

typedef struct {
  char *filename;
  char *dispname;
} NAME_FvsD;

typedef struct {
  int num;
  NAME_FvsD *name;
} NFD;

#ifndef WIN32
typedef long LONG;

typedef struct {
  LONG x, y;
} POINT;
#endif

typedef struct {
  POINT *offs;
} POINTs;

typedef struct {
  char name[256];
  POINTs *ofs;
} HEADOffs;

class CChrView
{
private:
  CPAK *pak1;

  void InitNFDMob(char *fnp, NFD *nfd);
  void InitNFDPCBody(char *fnp, NFD *nfd, char *suffix);
  void InitNFDPCAcc(char *fnp, NFD *nfd);
  void InitNFDNPC(char *fnp, NFD *nfd);
  void InitNFDADD(char *dn, char *fn, NFD *nfd);
  void TrimDirSuffix(char *to, char *from, int leftlen);

  char *GetNFDFnameFromDname(NFD *nfd, char *dispname);
  void ChangeToSpr(char *fname, char *sprname);
  void GetItemNoToWeaponType(char *fname, int no);

public:
  CChrView(CPAK *pak);
  virtual ~CChrView();

  bool inMDragging;
  bool inRDragging;
  POINT first_mp, old_mp, new_mp;
  CAM_STATE camera;

  NFD NFDMob;
  NFD NFDPCBodyM;
  NFD NFDPCBodyF;
  NFD NFDPCAccM;
  NFD NFDPCAccF;
  NFD NFDPCWeapon;
  NFD NFDPCShield;
  NFD NFDNPC;

  bool sprready;
  CSprite *sprite_Body;
  CSprite *sprite_Head;
  CSprite *sprite_Acc1;
  CSprite *sprite_Acc2;
  CSprite *sprite_Acc3;
  CSprite *sprite_Weapon;
  CSprite *sprite_WpAftimg;
  CSprite *sprite_Shield;
  int curAct, curPat;
  int numAct, numPat;
  int curdirection;
  int curHead;
  int curAcc1, curAcc2, curAcc3;
  DWORD colBG;

  void DestroySpriteAll(void);
  void DestroySprite(CSprite **sprite);
  void DestroyNFD(NFD *nfd);
  void DestroyNFD_WeapShield(void);
  void ClearNFD(void);
  void InitNFD(void);

  void InitControlsWeaponShieldPre(void);

  void InitOpenGL();
  void SetCameraDefault(void);
  void CameraSet(void);
  void GLZoom(void);
  void GLPan(void);

  bool SpriteSetMob(CSprite **sprite, char *dispname);
  bool SpriteSetPCBody(CSprite **sprite, char *dispname, char *fname_base, bool male);
  void DestroySprites_GM2(void);
  bool SpriteSetPCHead(CSprite **sprite, bool male);
  bool SpriteSetPCAcc(CSprite **sprite, char *dispname, int no, bool male);
  bool SpriteSetPCWeapon(CSprite **sprite, char *dispname, char *bodyname, char *sexname);
  bool SpriteSetPCWeaponAftImage(char *fname, char *bodyname, char *sexname, int idWeapon);
  bool SpriteSetPCShield(CSprite **sprite, char *bodyname, char *sexname, char *dispname);
  bool SpriteSetNPC(CSprite **sprite, char *dispname);
  bool SpriteSet(CSprite **sprite, char *actname, char *sprname);
  void DrawSprites(void);
  void DrawSpritesHead(CSprite *sprite, int x, int y);

  void InitNumActPat(void);
  void SetNullSprites(void);

  void SelectAct(int idAct);
  void SelectDirection(int idAct, int idDirection);

  void SetWeaponName(char *fnp, char *bodynameW, char *bodyname2);
  void SetShieldName(char *fnp, char *bodynameS, char *bodyname2);

  void GetPCBodyName(char *bodyname, char *sexname, char *dispname, bool male);

  int GetTimeInterval(void);
};


extern "C" {
int NAME_FvsDSortFuncByDisp(const void *a, const void *b);
}

#define PC_ACTNAME_INT "PCActName%d"
#define MOB_ACTNAME_INT "MobActName%d"

#define MALE_STR "\263\262"
#define FEMALE_STR "\277\251"
#define AFTERIMAGE_STR "\260\313\261\244"
#define AFTIMG_ADD_STR "\137\260\313\261\244"
#define SHORTSWORD_AFTIMG_STR "\264\334\260\313\137\260\313\261\244"
#define SWORD_AFTIMG_STR "\260\313\137\260\313\261\244"
#define AXE_AFTIMG_STR "\265\265\263\242\137\260\313\261\244"
#define SPEAR_AFTIMG_STR "\303\242\137\260\313\261\244"
#define ROD_AFTIMG_STR "\267\324\265\345\137\260\313\261\244"
#define CRUB_AFTIMG_STR "\305\254\267\264\137\260\313\261\244"
#define CLAW_AFTIMG_STR "\263\312\305\254\137\260\313\261\244"

//#define MOB_DIR "data\\sprite\\몬스터\\"
#define MOB_DIR "\144\141\164\141\134\163\160\162\151\164\145\134\270\363\275\272\305\315\134"
//#define PCBODY_M_DIR "data\sprite\인간족\몸흟E남\"
#define PCBODY_M_DIR "\144\141\164\141\134\163\160\162\151\164\145\134\300\316\260\243\301\267\134\270\366\305\353\134\263\262\134"
//#define PCBODY_F_DIR "data\sprite\인간족\몸흟E여\"
#define PCBODY_F_DIR "\144\141\164\141\134\163\160\162\151\164\145\134\300\316\260\243\301\267\134\270\366\305\353\134\277\251\134"
//#define PCHEAD_M_DIR "data\sprite\인간족\머리흟E남\"
#define PCHEAD_M_DIR "\144\141\164\141\134\163\160\162\151\164\145\134\300\316\260\243\301\267\134\270\323\270\256\305\353\134\263\262\134"
//#define PCHEAD_F_DIR "data\sprite\인간족\머리흟E여\"
#define PCHEAD_F_DIR "\144\141\164\141\134\163\160\162\151\164\145\134\300\316\260\243\301\267\134\270\323\270\256\305\353\134\277\251\134"
//#define PCACC_M_DIR "data\sprite\악세사리\남\"
#define PCACC_M_DIR "\144\141\164\141\134\163\160\162\151\164\145\134\276\307\274\274\273\347\270\256\134\263\262\134"
//#define PCACC_F_DIR "data\sprite\악세사리\여\"
#define PCACC_F_DIR "\144\141\164\141\134\163\160\162\151\164\145\134\276\307\274\274\273\347\270\256\134\277\251\134"
//#define WEAPON_DIR "data\sprite\인간족\"
#define WEAPON_DIR "\144\141\164\141\134\163\160\162\151\164\145\134\300\316\260\243\301\267\134"
//#define SHIELD_DIR "data\sprite\방패"\"
#define SHIELD_DIR "\144\141\164\141\134\163\160\162\151\164\145\134\271\346\306\320\134"
#define NPC_DIR "data\\sprite\\npc\\"

//#define BAPHOMET_PET "baphomet_뼉다구모자"
#define BAPHOMET_PET "\142\141\160\150\157\155\145\164\137\273\301\264\331\261\270\270\360\300\332"
//#define BON_GON_PET "bon_gun_영환도사검"
#define BON_GON_PET "\142\157\156\137\147\165\156\137\277\265\310\257\265\265\273\347\260\313"
//#define CHOCHO_PET "chocho_방독툈E"
#define CHOCHO_PET "\143\150\157\143\150\157\137\271\346\265\266\270\351"
//#define DESERT_WOLF_B_PET "desert_wolf_b_퓖E嶺뭏疸�"
#define DESERT_WOLF_B_PET "\144\145\163\145\162\164\137\167\157\154\146\137\142\137\277\354\301\326\272\271\270\323\270\256"
//#define DEVIRUCHI_PET "deviruchi_젖꼭햨E"
#define DEVIRUCHI_PET "\144\145\166\151\162\165\143\150\151\137\301\245\262\300\301\366"
//#define DOKEBI_PET "dokebi_아후로머리"
#define DOKEBI_PET "\144\157\153\145\142\151\137\276\306\310\304\267\316\270\323\270\256"
//#define ISIS_PET "isis_클레오파트라머리턿E"
#define ISIS_PET "\151\163\151\163\137\305\254\267\271\277\300\306\304\306\256\266\363\270\323\270\256\266\354"
//#define LUNATIC_PET "lunatic_리본"
#define LUNATIC_PET "\154\165\156\141\164\151\143\137\270\256\272\273"
//#define MUNAK_PET "munak_요술봉"
#define MUNAK_PET "\155\165\156\141\153\137\277\344\274\372\272\300"
//#define ORK_WARRIOR_PET "ork_warrior_꽃"
#define ORK_WARRIOR_PET "\157\162\153\137\167\141\162\162\151\157\162\137\262\311"
//#define PECOPECO_PET "pecopeco_냄틒E"
#define PECOPECO_PET "\160\145\143\157\160\145\143\157\137\263\277\272\361"
//#define PETIT_PET "petit_별"
#define PETIT_PET "\160\145\164\151\164\137\272\260"
//#define PICKEY_PET "picky_알껍햨E"
#define PICKY_PET "\160\151\143\153\171\137\276\313\262\256\301\372"
//#define PORING_PET "poring_책가퉩E"
#define PORING_PET "\160\157\162\151\156\147\137\303\245\260\241\271\346"
//#define ROCKER_PET "rocker_메뚜기안컖E"
#define ROCKER_PET "\162\157\143\153\145\162\137\270\336\266\321\261\342\276\310\260\346"
//#define SAVAGE_BABE_PET "savage_babe_레이스"
#define SAVAGE_BABE_PET "\163\141\166\141\147\145\137\142\141\142\145\137\267\271\300\314\275\272"
//#define SMOKIE_PET "smokie_머플러"
#define SMOKIE_PET "\163\155\157\153\151\145\137\270\323\307\303\267\257"
//#define SOHEE_PET "sohee_방퓖E"
#define SOHEE_PET "\163\157\150\145\145\137\271\346\277\357"
//#define SPORE_PET "spore_원주민치마"
#define SPORE_PET "\163\160\157\162\145\137\277\370\301\326\271\316\304\241\270\266"
//#define YOYO_PET "yoyo_머리턿E"
#define YOYO_PET "\171\157\171\157\137\270\323\270\256\266\354"

static int weaponid2type[][2] = {
  // 0: short sword
  // 1: one hand sword
  // 2: two hand sword
  // 3: axe
  // 4: spear
  // 5: rod
  // 6: crub
  // 7: book
  // 8: claw
  // 9: inst
  // 10: whip
  // 11: katar?
  1101, 1,  //�\�[긤
  1102, 1,  //�\�[긤
  1103, 1,  //�\�[긤
  1104, 1,  //긲�@깑긘긆깛
  1105, 1,  //긲�@깑긘긆깛
  1106, 1,  //긲�@깑긘긆깛
  1107, 1,  //긳깒귽긤
  1108, 1,  //긳깒귽긤
  1109, 1,  //긳깒귽긤
  1110, 1,  //깒귽긯귺
  1111, 1,  //깒귽긯귺
  1112, 1,  //깒귽긯귺
  1113, 1,  //긘�~�^�[
  1114, 1,  //긘�~�^�[
  1115, 1,  //긘�~�^�[
  1116, 2,  //긇�^긥
  1117, 2,  //긇�^긥
  1118, 2,  //긇�^긥
  1119, 1,  //긟깑긎
  1120, 1,  //긟깑긎
  1121, 1,  //긟깑긎
  1122, 1,  //듏벆뫞뱚
  1123, 1,  //둇뱦뙐
  1124, 1,  //긆�[긌긞긘깄�\�[긤
  1125, 1,  //듏벆뫞뱚
  1126, 1,  //긖�[긹깑
  1127, 1,  //긖�[긹깑
  1128, 1,  //둇뱦뙐
  1129, 1,  //긲깋깛긹깑긙긃
  1130, 1,  //긨귽긊깛
  1131, 1,  //귺귽긚긲�@깑긘긆깛
  1132, 1,  //긄긞긙
  1133, 1,  //긲�@귽귺�[긳깋깛긤
  1134, 1,  //긘�[긗�[긛�\�[긤
  1135, 1,  //긇긣깋긚
  1136, 1,  //뫞뾸뙐
  1137, 1,  //긄긏긚긌긿깏긫�[
  1138, 1,  //�~긚긡�[깑긡귽깛
  1139, 1,  //긡귽깑긲귻깛긐
  1140, 1,  //빶�_뙐
  1141, 1,  //뼰�`뙐
  1142, 1,  //긙깄긄깑�\�[긤
  1143, 1,  //긊귽귺�\�[긤
  1144, 1,  //럋릆뺧뮍
  1145, 1,  //긼�[깏�[귺깞긃깛긙긿�[
  //1151, 2,  //긚깒귽깂�[
  //1152, 2,  //긚깒귽깂�[
  //1153, 2,  //긚깒귽깂�[
  //1154, 2,  //긫긚�^�[긤�\�[긤
  //1155, 2,  //긫긚�^�[긤�\�[긤
  //1156, 2,  //긫긚�^�[긤�\�[긤
  //1157, 2,  //긟�[긪깛긤�\�[긤
  //1158, 2,  //긟�[긪깛긤�\�[긤
  //1159, 2,  //긟�[긪깛긤�\�[긤
  //1160, 2,  //긳깓�[긤�\�[긤
  //1161, 2,  //긫깑��깛
  //1162, 2,  //긳깓�[긤�\�[긤
  //1163, 2,  //긏깒귽긾귺
  //1164, 2,  //뫚맫
  //1165, 2,  //맫�@
  //1166, 2,  //긤깋긕깛긚깒귽깂�[
  //1167, 2,  //긘깄긫귽�`긃깑긘긿긹깑
  //1168, 2,  //긟깞�@귽긪깛�_�[
  //1169, 2,  //긄긏긚긌깄�[긘깈긥�[
  //1170, 2,  //긇긞긟긫깑긒깑
  1201, 0,  //긥귽긲
  1202, 0,  //긥귽긲
  1203, 0,  //긥귽긲
  1204, 0,  //긇긞�^�[
  1205, 0,  //긇긞�^�[
  1206, 0,  //긇긞�^�[
  1207, 0,  //�}귽깛긕�[긘깄
  1208, 0,  //�}귽깛긕�[긘깄
  1209, 0,  //�}귽깛긕�[긘깄
  1210, 0,  //�_�[긏
  1211, 0,  //�_�[긏
  1212, 0,  //�_�[긏
  1213, 0,  //�_긊�[
  1214, 0,  //�_긊�[
  1215, 0,  //�_긊�[
  1216, 0,  //긚긡귻깒긞긣
  1217, 0,  //긚긡귻깒긞긣
  1218, 0,  //긚긡귻깒긞긣
  1219, 0,  //긐깋긢귻긂긚
  1220, 0,  //긐깋긢귻긂긚
  1221, 0,  //긐깋긢귻긂긚
  1222, 0,  //�_�}긚긇긚
  1223, 0,  //긲긅�[�`깄깛�\�[긤
  1224, 0,  //�\�[긤긳깒귽긇�[
  1225, 0,  //긽귽깑긳깒귽긇�[
  1226, 0,  //�_�}긚긇긚
  1227, 0,  //긂귻�[�_�[긥귽긲
  1228, 0,  //긓깛긫긞긣긥귽긲
  1229, 0,  //뺧뮍
  1230, 0,  //릫
  1231, 0,  //긫�[깋깑긤
  1232, 0,  //귺긖긘깛�_긊�[
  1233, 0,  //긄긌긖�[긖귽긛
  1234, 0,  //뙉뚹뙐
  1235, 0,  //귺�]�[긣
  1236, 0,  //긚긏긖�}긞긤
  1237, 0,  //긆�[긊긣귾�[긚
  1238, 0,  //�[긦�[긥귽긲
  1239, 0,  //�|귽긛깛긥귽긲
  1240, 0,  //긵깏깛긜긚긥귽긲
  1241, 0,  //긇�[긚�_긊�[
  1242, 0,  //긇긂깛�^�[�_긊�[
  //1250, 11,  //긙깄깑
  //1251, 11,  //긙깄깑
  //1252, 11,  //긇�^�[깑
  //1253, 11,  //긇�^�[깑
  //1254, 11,  //긙긿�}�_긪깑
  //1255, 11,  //긙긿�}�_긪깑
  1301, 3,  //귺긞긏긚
  1302, 3,  //귺긞긏긚
  1303, 3,  //귺긞긏긚
  1304, 3,  //긆�[긌긞긘깄귺긞긏긚
  1305, 3,  //긏깏�[깞�@�[
  1306, 3,  //긂긅�[귺긏긚
  1351, 3,  //긫긣깑귺긞긏긚
  1352, 3,  //긫긣깑귺긞긏긚
  1353, 3,  //긫긣깑귺긞긏긚
  1354, 3,  //긪깛�}�[
  1355, 3,  //긪깛�}�[
  1356, 3,  //긪깛�}�[
  1357, 3,  //긫긚�^�[
  1358, 3,  //긫긚�^�[
  1359, 3,  //긫긚�^�[
  1360, 3,  //긟�[긪깛긤귺긞긏긚
  1361, 3,  //긟�[긪깛긤귺긞긏긚
  1362, 3,  //긟�[긪깛긤귺긞긏긚
  1363, 3,  //긳깋긞긤귺긞긏긚
  1364, 3,  //긐깒귽긣귺긞긏긚
  1365, 3,  //긖긫긚
  1366, 3,  //깋귽긣긄긵긘깓깛
  1367, 3,  //긚깓�[�^�[
  1368, 3,  //긣�}긼�[긏
  1369, 3,  //긎깓�`깛
  1401, 4,  //긙긿긹깏깛
  1402, 4,  //긙긿긹깏깛
  1403, 4,  //긙긿긹깏깛
  1404, 4,  //긚긯귺�[
  1405, 4,  //긚긯귺�[
  1406, 4,  //긚긯귺�[
  1407, 4,  //긬귽긏
  1408, 4,  //긬귽긏
  1409, 4,  //긬귽긏
  1410, 4,  //깋깛긚
  1411, 4,  //깋깛긚
  1412, 4,  //깋깛긚
  1413, 4,  //긐깛긐긦�[깑
  1414, 4,  //긒깋긤깏귺
  1415, 4,  //뗹
  1416, 4,  //긡깄깛긐깒긡귻�[
  1417, 4,  //�|�[깑귺긏긚
  1451, 4,  //긎긗깑��
  1452, 4,  //긎긗깑��
  1453, 4,  //긎긗깑��
  1454, 4,  //긐깒귽깞
  1455, 4,  //긐깒귽깞
  1456, 4,  //긐깒귽깞
  1457, 4,  //긬깑�`긗깛
  1458, 4,  //긬깑�`긗깛
  1459, 4,  //긬깑�`긗깛
  1460, 4,  //긣깋귽긢깛긣
  1461, 4,  //긣깋귽긢깛긣
  1462, 4,  //긣깋귽긢깛긣
  1463, 4,  //긪깑긫�[긤
  1464, 4,  //긪깑긫�[긤
  1465, 4,  //긪깑긫�[긤
  1466, 4,  //긏깒긜깛긣긖귽�_�[
  1467, 4,  //긮깑긎긗깑��
  1468, 4,  //�[긯깄깓긚
  1469, 4,  //깓깛긎긧긚궻몖
  1470, 4,  //긳깏깄�[긥긏
  1471, 4,  //긶깑긲�@귽귺
  1472, 5,  //긚�^긞긲긆긳�\긂깑
  1473, 5,  //긂귻긗�[긤긚�^긞긲
  1501, 6,  //긏깋긳
  1502, 6,  //긏깋긳
  1503, 6,  //긏깋긳
  1504, 6,  //긽귽긚
  1505, 6,  //긽귽긚
  1506, 6,  //긽귽긚
  1507, 6,  //긚�}긞긘긿�[
  1508, 6,  //긚�}긞긘긿�[
  1509, 6,  //긚�}긞긘긿�[
  1510, 6,  //긲깒귽깑
  1511, 6,  //긲깒귽깑
  1512, 6,  //긲깒귽깑
  1513, 6,  //긾긦깛긐긚�^�[
  1514, 6,  //긾긦깛긐긚�^�[
  1515, 6,  //긾긦깛긐긚�^�[
  1516, 6,  //�\�[긤긽귽긚
  1517, 6,  //�\�[긤긽귽긚
  1518, 6,  //�\�[긤긽귽긚
  1519, 6,  //�`긃귽깛
  1520, 6,  //�`긃귽깛
  1521, 6,  //�`긃귽깛
  1522, 6,  //긚�^긥�[
  1523, 6,  //긚긬귽긏
  1524, 6,  //긕�[깑긢깛긽귽긚
  1525, 6,  //깓깛긐긽귽긚
  1526, 6,  //긚깋긞긘깄 
  1527, 6,  //긇긤깏�[깑
  1528, 6,  //긐깋깛긤긏깓긚
  1529, 6,  //귺귽귺깛긤깋귽긫�[
  1530, 6,  //�~깈깑긦�[깑
  1531, 6,  //긚긬긥
  //1550, ,  //긳긞긏
  //1551, ,  //긫귽긳깑
  //1552, ,  //�^긳깒긞긣
  1601, 5,  //깓긞긤
  1602, 5,  //깓긞긤
  1603, 5,  //깓긞긤
  1604, 5,  //깗깛긤
  1605, 5,  //깗깛긤
  1606, 5,  //깗깛긤
  1607, 5,  //긚�^긞긲
  1608, 5,  //긚�^긞긲
  1609, 5,  //긚�^긞긲
  1610, 5,  //귺�[긏깗깛긤
  1611, 5,  //귺�[긏깗깛긤
  1612, 5,  //귺�[긏깗깛긤
  1613, 5,  //�}귽긣긚�^긞긲
  1614, 5,  //�_뒸궻륇
  1615, 5,  //�[뜙궻륇
  //1701, ,  //�{긂
  //1702, ,  //�{긂
  //1703, ,  //�{긂
  //1704, ,  //긓깛�|긙긞긣�{긂
  //1705, ,  //긓깛�|긙긞긣�{긂
  //1706, ,  //긓깛�|긙긞긣�{긂
  //1707, ,  //긐깒귽긣�{긂
  //1708, ,  //긐깒귽긣�{긂
  //1709, ,  //긐깒귽긣�{긂
  //1710, ,  //긏깓긚�{긂
  //1711, ,  //긏깓긚�{긂
  //1712, ,  //긏깓긚�{긂
  //1713, ,  //귺�[긫깒긚긣
  //1714, ,  //둷�|
  //1715, ,  //귺�[긫깒긚긣
  //1716, ,  //둷�|
  //1718, ,  //긪깛�^�[�{긂
  //1719, ,  //뱪뫍궻�|
  //1720, ,  //깑긤깋궻�|
  //1721, ,  //쁀쏻
  //1722, ,  //긫깏긚�^
  1801, 8,  //긫긐긥긂
  1802, 8,  //긫긐긥긂
  1803, 8,  //긥긞긏깑�_긚�^�[
  1804, 8,  //긥긞긏깑�_긚�^�[
  1805, 8,  //긼깋
  1806, 8,  //긼깋
  1807, 8,  //긲귻긚긣
  1808, 8,  //긲귻긚긣
  1809, 8,  //긏깓�[
  1810, 8,  //긏깓�[
  1811, 8,  //긲귻깛긊�[
  1812, 8,  //긲귻깛긊�[
  1813, 8,  //긇귽긗�[긥긞긏깑
  1814, 8  //긹깑긜깑긏
  //1901, ,  //긫귽긆깏깛
  //1902, ,  //긫귽긆깏깛
  //1903, ,  //�}깛긤깏깛
  //1904, ,  //�}깛긤깏깛
  //1905, ,  //깏깄�[긣
  //1906, ,  //깏깄�[긣
  //1907, ,  //긎�^�[
  //1908, ,  //긎�^�[
  //1909, ,  //긪�[긵
  //1910, ,  //긪�[긵
  //1911, ,  //긕��깛긕
  //1912, ,  //긕��깛긕
  //1950, ,  //깓�[긵
  //1951, ,  //깓�[긵
  //1952, ,  //깋귽깛
  //1953, ,  //깋귽깛
  //1954, ,  //깗귽깂�[
  //1955, ,  //깗귽깂�[
  //1956, ,  //깋깛긡
  //1957, ,  //깋깛긡
  //1958, ,  //긡귽깑
  //1959, ,  //긡귽깑
  //1960, ,  //긼귽긞긵
  //1961, ,  //긼귽긞긵
  //1962, ,  //깋깏긄긞긣
  //1963, ,  //깋긵�`긿�[깓�[긛
  //1964, ,  //긘깄긽긡귻
};

#endif // __MY_CHRVIEW__
