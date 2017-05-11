//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Ustat_rep.h"
#include "Uproverka.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dbf"
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TForm3::StatRep(void)
{
 if(FileExists(Form1->ProgDir+"\\tmp_stat.dbf"))
 {
  Drep->Active= false;
  Drep->FilePath= Form1->ProgDir;
  Drep->TableName= "tmp_stat.dbf";
  Drep->Active= true;

  QuickRep1->Preview();
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::QuickRep1AfterPreview(TObject *Sender)
{
 Drep->Active= false;
}
//---------------------------------------------------------------------------
