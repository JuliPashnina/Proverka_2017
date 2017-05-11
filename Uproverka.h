//---------------------------------------------------------------------------

#ifndef UproverkaH
#define UproverkaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <Db.hpp>
#include <AxCtrls.hpp>
#include <OleCtrls.hpp>
#include <vcf1.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "dbf.hpp"
#include "dbf_lang.hpp"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TDbf *D1;
        TDbf *D2;
        TLabel *Label1;
        TLabel *Label2;
        TButton *Bsel;
        TFileListBox *FLB1;
        TCheckBox *ChBselall;
        TButton *Bcheck;
        TBitBtn *BBclose;
        TDbf *D3;
        TCheckBox *ChBdblls;
        TLabel *Label3;
        TComboBox *CBmes;
        TDbf *Dstat;
        TGroupBox *GBstat;
        TButton *Bstatuch;
        TButton *Bstatsum;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BcheckClick(TObject *Sender);
        void __fastcall BselClick(TObject *Sender);
        void __fastcall ChBselallClick(TObject *Sender);
        void __fastcall FLB1Click(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall CBmesChange(TObject *Sender);
        void __fastcall BstatuchClick(TObject *Sender);
        void __fastcall BstatsumClick(TObject *Sender);
private:	// User declarations
TStringList *list;
TStringList *spisok;
TStringList *u4astki;
TStringList *chlist;

int met_raion, kolvo, SELDIRHELP, rec_null, fio_empty, street_empty, mes_num, ny4d_kol;
int uchastok, StatView;
int e001,e002,e003,e004,e005,e006,e007,e008,e009,e010;
int e011,/*e012,*/e013,/*e014,e015,e016,e017,e018,*/e019,e020;
int e021,e022,e023,e024/*,e027,e029,e030,e031*/;
double velichina, value;
bool b;
void AddField(AnsiString, TFieldType type, int length=0);
void AddStr(AnsiString Rec, AnsiString Txt, int Numrec, int Rn, AnsiString Ls);
AnsiString TipField(int tip);
void Statistika(void);
void __fastcall CopyStructDBF(AnsiString Path1, AnsiString FileName1, AnsiString Path2, AnsiString FileName2, TDbf *Dbf1, TDbf *Dbf2);
void __fastcall AddRecDBF(TDbf *Dbf1, TDbf *Dbf2);

public:		// User declarations
AnsiString dir, Directory, rec, uchastki, LS, ProgDir, mes_opl;

        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
