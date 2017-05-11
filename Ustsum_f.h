//---------------------------------------------------------------------------

#ifndef Ustsum_fH
#define Ustsum_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "dbf.hpp"
#include <Db.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TComboBox *CBuch;
        TButton *Button1;
        TListBox *LBuch;
        TButton *Button2;
        TGroupBox *GroupBox3;
        TBitBtn *BitBtn1;
        TButton *Button3;
        TLabel *Label1;
        TDateTimePicker *DTP1;
        TDateTimePicker *DTP2;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TDbf *Dsum1;
        TDbf *Dsum2;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
int e001,e002,e003,e004,e005,e006,e007,e008,e009,e010,e010_1,e010_2;
int e011,e013,e019,e020,e021,e022,e023,e024,e025;
public:		// User declarations
        __fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
