//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Ustsum_r.h"
#include "Uproverka.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dbf"
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TForm5::StatSum(AnsiString Zagolovok)
{
 if(FileExists(Form1->ProgDir+"\\tmp_sum.dbf"))
 {
  Zagolovok= "Статистика ошибок БД за "+Zagolovok;
  QRLabel1->Caption= Zagolovok;

  Dsum->Active= false;
  Dsum->FilePath= Form1->ProgDir;
  Dsum->TableName= "tmp_sum.dbf";
  Dsum->Active= true;

  QuickRep1->Preview();
 }//end_if(file_exists)
}
//---------------------------------------------------------------------------
void __fastcall TForm5::QuickRep1AfterPreview(TObject *Sender)
{
 Dsum->Active= false;
}
//---------------------------------------------------------------------------
