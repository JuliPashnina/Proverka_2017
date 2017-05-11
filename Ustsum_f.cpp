//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Ustsum_f.h"
#include "Uproverka.h"
#include "Ustsum_r.h"
#include "Ustat_form.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dbf"
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormShow(TObject *Sender)
{
 CBuch->Clear();
 LBuch->Clear();
 DTP1->Date= Date();
 DTP2->Date= Date();

 //dobavlrnie_uchastkov_iz_stat.dbf
 Dsum1->Active= false;
 Dsum1->FilePath= Form1->ProgDir;
 Dsum1->TableName= "stat.dbf";
 Dsum1->Active= true;
 AnsiString uch="",raion="";
 bool rai=false;

 while(!Dsum1->Eof)
 {
  rai=false;
  uch= IntToStr(Dsum1->FieldByName("n_uch")->AsInteger).Trim();
  for(int SpUch=0;SpUch<=CBuch->Items->Count-1;SpUch++)
  {
   if(uch==CBuch->Items->Strings[SpUch]) rai=true;
  }
  if(rai) Dsum1->Next();
  else
  {
   CBuch->Items->Add(uch);
   Dsum1->Next();
  }
 }

 Dsum1->Active= false;

 CBuch->ItemIndex= -1;
 Button2->Enabled= false;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button1Click(TObject *Sender)
{
 bool rai=false;

 if(CBuch->ItemIndex<0)
 {
  ShowMessage("ÍÓÆÍÎ ÂÛÁÐÀÒÜ Ó×ÀÑÒÎÊ Â ÂÛÏÀÄÀÞÙÅÌ ÑÏÈÑÊÅ!");
  CBuch->SetFocus();
 }
 else
 {
  for(int SpUch=0;SpUch<=LBuch->Items->Count-1;SpUch++)
  {
   if(CBuch->Items->Strings[CBuch->ItemIndex]==LBuch->Items->Strings[SpUch]) rai=true;
  }
  if(rai) ShowMessage("Ó×ÀÑÒÎÊ "+CBuch->Items->Strings[CBuch->ItemIndex]+" ÓÆÅ ÄÎÁÀÂËÅÍ!");
  else
  {
   LBuch->Items->Add(CBuch->Items->Strings[CBuch->ItemIndex]);
   Button2->Enabled= true;
  }
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button2Click(TObject *Sender)
{
 if(LBuch->ItemIndex<0)
 {
  ShowMessage("ÍÓÆÍÎ ÂÛÁÐÀÒÜ Ó×ÀÑÒÎÊ Â ÑÏÈÑÊÅ!");
  LBuch->SetFocus();
 }
 else
 {
  LBuch->Items->Delete(LBuch->ItemIndex);
  if(LBuch->Items->Count==0) Button2->Enabled= false;
  else Button2->Enabled= true;
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button3Click(TObject *Sender)
{

if(LBuch->Items->Count==0)
{
 ShowMessage("ÍÓÆÍÎ ÄÎÁÀÂÈÒÜ Ó×ÀÑÒÊÈ!");
 CBuch->SetFocus();
}
else
{
 AnsiString dtp1=DTP1->Date, dtp2=DTP2->Date;
 dtp1= dtp1.SubString(1,10);
 dtp2= dtp2.SubString(1,10);
 if(StrToDateTime(dtp1)>StrToDateTime(dtp2))
 {
  ShowMessage("Â ÈÍÒÅÐÂÀËÅ ÄÀÒ ÄÀÒÀ 'Ñ...' ÄÎËÆÍÀ ÁÛÒÜ ÌÅÍÜØÅ ÄÀÒÛ 'ÏÎ...'");
  DTP1->SetFocus();
 }
 else
 {
   Dsum2->Active= false;
   Dsum2->FilePath= Form1->ProgDir;
   Dsum2->TableName= "tmp_sum.dbf";
  //ñîçäà¸ì âðåìåííûé ôàéë
  if(!FileExists(Form1->ProgDir+"\\tmp_sum.dbf"))
  {
   Dsum2->FieldDefs->Clear();
   Dsum2->FieldDefs->Add("n_uch",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e001",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e002",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e003",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e004",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e005",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e006",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e007",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e008",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e009",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e010",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e010_1",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e010_2",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e011",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e013",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e019",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e020",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e021",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e022",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e023",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e024",ftInteger,0,false);
   Dsum2->FieldDefs->Add("e025",ftInteger,0,false);
   Dsum2->CreateTable();
  }
  else
  {
   Dsum2->Active= true;
   if(Dsum2->RecordCount>0) while(!Dsum2->Eof) Dsum2->Delete();
   Dsum2->Active= false;
  }
  //kodirovka
  FILE *F;
  char cRus='\0';
  AnsiString rai=Form1->ProgDir+"\\tmp_sum.dbf";
  F= fopen(rai.c_str(),"r+");
  fseek(F,29,0);
  fwrite(&cRus,sizeof(cRus),1,F);
  fclose(F);
 //==========================================
 //!!!OTCHET_ZA_1_MESYATS!!!
 if(StrToDateTime(dtp1)==StrToDateTime(dtp2))
 {
  AnsiString mes= dtp1.Trim();
  mes= mes.SubString(4,7);
  mes= mes.Delete(mes.Pos("."),3);
  Dsum1->Active= false;
  Dsum1->FilePath= Form1->ProgDir;
  Dsum1->TableName= "stat.dbf";
  Dsum1->Active= true;
  bool y=false;
  for(int SpUch=0;SpUch<=LBuch->Items->Count-1;SpUch++)//probegaem_po_spisku_uch
  {
   e001=0;e002=0;e003=0;e004=0;e005=0;e006=0;e007=0;e008=0;e009=0;e010=0;
   e010_1=0;e010_2=0;e011=0;e013=0;e019=0;e020=0;e021=0;e022=0;e023=0;e024=0;e025=0;
   y=false;
   int uch=StrToInt(LBuch->Items->Strings[SpUch]);
   Dsum1->First();
   while(!Dsum1->Eof)
   {
    if(Dsum1->FieldByName("n_mes")->AsString==mes & Dsum1->FieldByName("n_uch")->AsInteger==uch)
    {
     y= true;
     e001+= Dsum1->FieldByName("e001")->AsInteger;
     e002+= Dsum1->FieldByName("e002")->AsInteger;
     e003+= Dsum1->FieldByName("e003")->AsInteger;
     e004+= Dsum1->FieldByName("e004")->AsInteger;
     e005+= Dsum1->FieldByName("e005")->AsInteger;
     e006+= Dsum1->FieldByName("e006")->AsInteger;
     e007+= Dsum1->FieldByName("e007")->AsInteger;
     e008+= Dsum1->FieldByName("e008")->AsInteger;
     e009+= Dsum1->FieldByName("e009")->AsInteger;
     e010+= Dsum1->FieldByName("e010")->AsInteger;
     e010_1+= Dsum1->FieldByName("e010_1")->AsInteger;
     e010_2+= Dsum1->FieldByName("e010_2")->AsInteger;
     e011+= Dsum1->FieldByName("e011")->AsInteger;
     e013+= Dsum1->FieldByName("e013")->AsInteger;
     e019+= Dsum1->FieldByName("e019")->AsInteger;
     e020+= Dsum1->FieldByName("e020")->AsInteger;
     e021+= Dsum1->FieldByName("e021")->AsInteger;
     e022+= Dsum1->FieldByName("e022")->AsInteger;
     e023+= Dsum1->FieldByName("e023")->AsInteger;
     e024+= Dsum1->FieldByName("e024")->AsInteger;
     e025+= Dsum1->FieldByName("e025")->AsInteger;
    }
    Dsum1->Next();
   }//end_while(!Dsum1->Eof)
   if(y)//åñëè_çàïèñè_íàéäåíû_âíîñèì_â_ôàéë
   {
    Dsum2->Active= true;
    Dsum2->Insert();
    Dsum2->FieldByName("n_uch")->AsInteger= uch;
    Dsum2->FieldByName("e001")->AsInteger= e001;
    Dsum2->FieldByName("e002")->AsInteger= e002;
    Dsum2->FieldByName("e003")->AsInteger= e003;
    Dsum2->FieldByName("e004")->AsInteger= e004;
    Dsum2->FieldByName("e005")->AsInteger= e005;
    Dsum2->FieldByName("e006")->AsInteger= e006;
    Dsum2->FieldByName("e007")->AsInteger= e007;
    Dsum2->FieldByName("e008")->AsInteger= e008;
    Dsum2->FieldByName("e009")->AsInteger= e009;
    Dsum2->FieldByName("e010")->AsInteger= e010;
    Dsum2->FieldByName("e010_1")->AsInteger= e010_1;
    Dsum2->FieldByName("e010_2")->AsInteger= e010_2;
    Dsum2->FieldByName("e011")->AsInteger= e011;
    Dsum2->FieldByName("e013")->AsInteger= e013;
    Dsum2->FieldByName("e019")->AsInteger= e019;
    Dsum2->FieldByName("e020")->AsInteger= e020;
    Dsum2->FieldByName("e021")->AsInteger= e021;
    Dsum2->FieldByName("e022")->AsInteger= e022;
    Dsum2->FieldByName("e023")->AsInteger= e023;
    Dsum2->FieldByName("e024")->AsInteger= e024;
    Dsum2->FieldByName("e025")->AsInteger= e025;
    Dsum2->Post();
    Dsum2->Active= false;
   }
  }//end_for_probeg_po_spisku
  Dsum1->Active= false;

  AnsiString title="",month=dtp1;
  month= month.SubString(month.Pos(".")+1,2);
  int mes_n= StrToInt(month);
  month= Form2->NameMonth(mes_n);
  title= dtp1.SubString(4,7)+" "+month+" ïî ó÷àñòêàì: "+LBuch->Items->CommaText;
  Form5->StatSum(title);
 }//end_if(dtp1==dtp2)
 //==========================================
 //!!!OTCHET_ZA_PERIOD!!!
 if(StrToDateTime(dtp1)<StrToDateTime(dtp2))
 {
  AnsiString mes1= dtp1.Trim(), mes2= dtp2.Trim();
  mes1= mes1.SubString(4,7);
  mes1= mes1.Delete(mes1.Pos("."),3);
  mes2= mes2.SubString(4,7);
  mes2= mes2.Delete(mes2.Pos("."),3);
  Dsum1->Active= false;
  Dsum1->FilePath= Form1->ProgDir;
  Dsum1->TableName= "stat.dbf";
  Dsum1->Active= true;
  bool y=false;
  for(int SpUch=0;SpUch<=LBuch->Items->Count-1;SpUch++)//probegaem_po_spisku_uch
  {
   e001=0;e002=0;e003=0;e004=0;e005=0;e006=0;e007=0;e008=0;e009=0;e010=0;
   e010_1=0;e010_2=0;e011=0;e013=0;e019=0;e020=0;e021=0;e022=0;e023=0;e024=0;e025=0;
   y=false;
   int uch=StrToInt(LBuch->Items->Strings[SpUch]);
   Dsum1->First();
   while(!Dsum1->Eof)
   {
    if(Dsum1->FieldByName("n_mes")->AsString>=mes1 & Dsum1->FieldByName("n_mes")->AsString<=mes2 & Dsum1->FieldByName("n_uch")->AsInteger==uch)
    {
     y= true;
     e001+= Dsum1->FieldByName("e001")->AsInteger;
     e002+= Dsum1->FieldByName("e002")->AsInteger;
     e003+= Dsum1->FieldByName("e003")->AsInteger;
     e004+= Dsum1->FieldByName("e004")->AsInteger;
     e005+= Dsum1->FieldByName("e005")->AsInteger;
     e006+= Dsum1->FieldByName("e006")->AsInteger;
     e007+= Dsum1->FieldByName("e007")->AsInteger;
     e008+= Dsum1->FieldByName("e008")->AsInteger;
     e009+= Dsum1->FieldByName("e009")->AsInteger;
     e010+= Dsum1->FieldByName("e010")->AsInteger;
     e010_1+= Dsum1->FieldByName("e010_1")->AsInteger;
     e010_2+= Dsum1->FieldByName("e010_2")->AsInteger;
     e011+= Dsum1->FieldByName("e011")->AsInteger;
     e013+= Dsum1->FieldByName("e013")->AsInteger;
     e019+= Dsum1->FieldByName("e019")->AsInteger;
     e020+= Dsum1->FieldByName("e020")->AsInteger;
     e021+= Dsum1->FieldByName("e021")->AsInteger;
     e022+= Dsum1->FieldByName("e022")->AsInteger;
     e023+= Dsum1->FieldByName("e023")->AsInteger;
     e024+= Dsum1->FieldByName("e024")->AsInteger;
     e025+= Dsum1->FieldByName("e025")->AsInteger;
    }
    Dsum1->Next();
   }//end_while(!Dsum1->Eof)
   if(y)//åñëè_çàïèñè_íàéäåíû_âíîñèì_â_ôàéë
   {
    Dsum2->Active= true;
    Dsum2->Insert();
    Dsum2->FieldByName("n_uch")->AsInteger= uch;
    Dsum2->FieldByName("e001")->AsInteger= e001;
    Dsum2->FieldByName("e002")->AsInteger= e002;
    Dsum2->FieldByName("e003")->AsInteger= e003;
    Dsum2->FieldByName("e004")->AsInteger= e004;
    Dsum2->FieldByName("e005")->AsInteger= e005;
    Dsum2->FieldByName("e006")->AsInteger= e006;
    Dsum2->FieldByName("e007")->AsInteger= e007;
    Dsum2->FieldByName("e008")->AsInteger= e008;
    Dsum2->FieldByName("e009")->AsInteger= e009;
    Dsum2->FieldByName("e010")->AsInteger= e010;
    Dsum2->FieldByName("e010_1")->AsInteger= e010_1;
    Dsum2->FieldByName("e010_2")->AsInteger= e010_2;
    Dsum2->FieldByName("e011")->AsInteger= e011;
    Dsum2->FieldByName("e013")->AsInteger= e013;
    Dsum2->FieldByName("e019")->AsInteger= e019;
    Dsum2->FieldByName("e020")->AsInteger= e020;
    Dsum2->FieldByName("e021")->AsInteger= e021;
    Dsum2->FieldByName("e022")->AsInteger= e022;
    Dsum2->FieldByName("e023")->AsInteger= e023;
    Dsum2->FieldByName("e024")->AsInteger= e024;
    Dsum2->FieldByName("e025")->AsInteger= e025;
    Dsum2->Post();
    Dsum2->Active= false;
   }
  }//end_for_probeg_po_spisku
  Dsum1->Active= false;

  AnsiString title="",month1=dtp1,month2=dtp2;
  month1= month1.SubString(month1.Pos(".")+1,2);
  month2= month2.SubString(month2.Pos(".")+1,2);
  int mes_n1= StrToInt(month1), mes_n2=StrToInt(month2);
  month1= Form2->NameMonth(mes_n1);
  month2= Form2->NameMonth(mes_n2);
  title= "ïåðèîä ñ "+dtp1.SubString(4,7)+" "+month1+" ïî "+dtp2.SubString(4,7)+" "+month2+" ïî ó÷àñòêàì: "+LBuch->Items->CommaText;
  Form5->StatSum(title);
 }//end_if(dtp1<dtp2)
 //==========================================
 }//end_else_if(StrToDateTime(dtp1)>=StrToDateTime(dtp2))
}//end_else_if(LBuch->Items->Count==0)

}
//---------------------------------------------------------------------------
