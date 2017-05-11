object Form1: TForm1
  Left = 192
  Top = 126
  Width = 281
  Height = 568
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Proverka (16.03.2017)'
  Color = clSilver
  Constraints.MaxWidth = 281
  Constraints.MinHeight = 568
  Constraints.MinWidth = 281
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Visible = True
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object Label1: TLabel
    Left = 16
    Top = 72
    Width = 242
    Height = 16
    Caption = 'Выберите файл(ы) для проверки'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGray
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 24
    Top = 88
    Width = 231
    Height = 16
    Caption = 'и нажмите кнопку "Проверить"'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGray
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 40
    Top = 8
    Width = 188
    Height = 16
    Caption = 'Выберите текущий месяц'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Bsel: TButton
    Left = 16
    Top = 136
    Width = 241
    Height = 25
    Caption = 'Выбрать папку с файлами'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = BselClick
  end
  object FLB1: TFileListBox
    Left = 8
    Top = 160
    Width = 257
    Height = 144
    Anchors = [akLeft, akTop, akRight, akBottom]
    Color = clSilver
    Enabled = False
    ExtendedSelect = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ItemHeight = 20
    Mask = 'bd??_??.dbf'
    MultiSelect = True
    ParentFont = False
    TabOrder = 1
    OnClick = FLB1Click
  end
  object ChBselall: TCheckBox
    Left = 16
    Top = 112
    Width = 169
    Height = 17
    Caption = 'Выбрать все файлы'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = ChBselallClick
  end
  object Bcheck: TButton
    Left = 56
    Top = 350
    Width = 161
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = 'Проверить'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = BcheckClick
  end
  object BBclose: TBitBtn
    Left = 176
    Top = 510
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
    TabOrder = 4
    Kind = bkClose
  end
  object ChBdblls: TCheckBox
    Left = 8
    Top = 320
    Width = 249
    Height = 17
    Anchors = [akLeft, akBottom]
    Caption = 'Проверка на двойные лицевые'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
  end
  object CBmes: TComboBox
    Left = 72
    Top = 32
    Width = 129
    Height = 24
    Style = csDropDownList
    DropDownCount = 12
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ItemHeight = 16
    ParentFont = False
    TabOrder = 6
    OnChange = CBmesChange
    Items.Strings = (
      '01 - Январь'
      '02 - Февраль'
      '03 - Март'
      '04 - Апрель'
      '05 - Май'
      '06 - Июнь'
      '07 - Июль'
      '08 - Август'
      '09 - Сентябрь'
      '10 - Октябрь'
      '11 - Ноябрь'
      '12 - Декабрь')
  end
  object GBstat: TGroupBox
    Left = 0
    Top = 384
    Width = 273
    Height = 121
    Anchors = [akLeft, akBottom]
    Caption = 'Статистика'
    Color = clGreen
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold, fsUnderline]
    ParentColor = False
    ParentFont = False
    TabOrder = 7
    object Bstatuch: TButton
      Left = 24
      Top = 32
      Width = 225
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = 'Статистика по участкам'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = BstatuchClick
    end
    object Bstatsum: TButton
      Left = 24
      Top = 72
      Width = 225
      Height = 25
      Caption = 'Суммарная статистика'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = BstatsumClick
    end
  end
  object D1: TDbf
    IndexDefs = <>
    OpenMode = omAutoCreate
    TableLevel = 4
    UseFloatFields = True
    Left = 8
    Top = 504
  end
  object D2: TDbf
    IndexDefs = <>
    OpenMode = omAutoCreate
    TableLevel = 4
    UseFloatFields = True
    Left = 40
    Top = 504
  end
  object D3: TDbf
    IndexDefs = <>
    OpenMode = omAutoCreate
    TableLevel = 4
    UseFloatFields = True
    Left = 72
    Top = 504
  end
  object Dstat: TDbf
    IndexDefs = <>
    OpenMode = omAutoCreate
    TableLevel = 4
    UseFloatFields = True
    Left = 104
    Top = 504
  end
end
