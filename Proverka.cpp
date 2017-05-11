//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Proverka.res");
USEFORM("Uproverka.cpp", Form1);
USEFORM("Ustat_form.cpp", Form2);
USEFORM("Ustat_rep.cpp", Form3);
USEFORM("Ustsum_f.cpp", Form4);
USEFORM("Ustsum_r.cpp", Form5);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TForm2), &Form2);
                 Application->CreateForm(__classid(TForm3), &Form3);
                 Application->CreateForm(__classid(TForm4), &Form4);
                 Application->CreateForm(__classid(TForm5), &Form5);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
