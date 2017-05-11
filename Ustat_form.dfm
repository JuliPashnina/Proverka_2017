object Form2: TForm2
  Left = 192
  Top = 126
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Статистика по участкам'
  ClientHeight = 353
  ClientWidth = 577
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 577
    Height = 353
    Caption = 'Условия выбора данных'
    Color = clTeal
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 80
      Width = 122
      Height = 16
      Caption = 'Доступные даты'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 64
      Top = 48
      Width = 433
      Height = 16
      Caption = 'из окна  доступных дат в окно дат для вывода статистики'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clLime
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 72
      Top = 32
      Width = 425
      Height = 16
      Caption = 'Добавьте даты, по которым хотите получить статистику,'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clLime
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 384
      Top = 80
      Width = 156
      Height = 16
      Caption = 'Даты для статистики'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LB1: TListBox
      Left = 8
      Top = 104
      Width = 209
      Height = 145
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ItemHeight = 16
      ParentFont = False
      TabOrder = 0
    end
    object Button1: TButton
      Left = 232
      Top = 144
      Width = 113
      Height = 25
      Caption = 'Добавить ->'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 232
      Top = 184
      Width = 113
      Height = 25
      Caption = 'Убрать <-'
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = Button2Click
    end
    object LB2: TListBox
      Left = 360
      Top = 104
      Width = 209
      Height = 145
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ItemHeight = 16
      ParentFont = False
      TabOrder = 3
    end
    object Button3: TButton
      Left = 192
      Top = 280
      Width = 193
      Height = 33
      Caption = 'Вывести статистику'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnClick = Button3Click
    end
  end
  object BitBtn1: TBitBtn
    Left = 480
    Top = 320
    Width = 91
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = 'Закрыть'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    Kind = bkClose
  end
  object Dst1: TDbf
    IndexDefs = <>
    OpenMode = omAutoCreate
    TableLevel = 4
    UseFloatFields = True
    Left = 200
    Top = 320
  end
  object Dst2: TDbf
    IndexDefs = <>
    OpenMode = omAutoCreate
    TableLevel = 4
    UseFloatFields = True
    Left = 240
    Top = 320
  end
end
