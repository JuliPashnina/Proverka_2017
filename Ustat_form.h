//---------------------------------------------------------------------------

#ifndef Ustat_formH
#define Ustat_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Db.hpp>
#include "dbf.hpp"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TListBox *LB1;
        TLabel *Label1;
        TLabel *Label2;
        TButton *Button1;
        TButton *Button2;
        TListBox *LB2;
        TLabel *Label3;
        TLabel *Label4;
        TButton *Button3;
        TBitBtn *BitBtn1;
        TDbf *Dst1;
        TDbf *Dst2;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
AnsiString NameMonth(int num);

        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
