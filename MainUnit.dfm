object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'MainForm'
  ClientHeight = 615
  ClientWidth = 652
  Color = clBtnFace
  Constraints.MinHeight = 682
  Constraints.MinWidth = 670
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnResize = FormResize
  DesignSize = (
    652
    615)
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 5
    Width = 91
    Height = 13
    Caption = #1048#1089#1093#1086#1076#1085#1074#1077' '#1076#1072#1085#1085#1099#1077
  end
  object Label2: TLabel
    Left = 8
    Top = 21
    Width = 159
    Height = 13
    Caption = #1042#1084#1077#1089#1090#1080#1084#1086#1089#1090#1100' '#1090#1088#1072#1085#1089#1087#1086#1088#1090#1072' ('#1095#1077#1083'):'
  end
  object Label3: TLabel
    Left = 8
    Top = 211
    Width = 407
    Height = 13
    Caption = 
      #1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090', '#1091#1095#1080#1090#1099#1074#1072#1102#1097#1080#1081' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1074#1099#1093#1086#1076#1103#1097#1080#1093' '#1080' '#1074#1093#1086#1076#1103#1097#1080#1093' '#1087#1072#1089#1089#1072#1078#1080 +
      #1088#1086#1074':'
  end
  object Label4: TLabel
    Left = 8
    Top = 116
    Width = 74
    Height = 13
    Caption = #1063#1080#1089#1083#1086' '#1076#1074#1077#1088#1077#1081':'
  end
  object Label5: TLabel
    Left = 8
    Top = 312
    Width = 231
    Height = 13
    Caption = #1042#1088#1077#1084#1103' '#1074#1099#1093#1086#1076#1072' '#1080' '#1074#1093#1086#1076#1072' '#1086#1076#1085#1086#1075#1086' '#1087#1072#1089#1089#1072#1078#1080#1088#1072', t0 '
  end
  object Label6: TLabel
    Left = 319
    Top = 312
    Width = 251
    Height = 13
    Caption = #1052#1080#1085#1080#1084#1072#1083#1100#1085#1099#1081' '#1080#1085#1090#1077#1088#1074#1072#1083' '#1084#1077#1078#1076#1091' '#1090#1088#1072#1085#1089#1087#1086#1088#1090#1086#1084' ('#1084'), i'
  end
  object Label7: TLabel
    Left = 8
    Top = 362
    Width = 118
    Height = 13
    Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090#1099' '#1086#1073#1088#1072#1073#1086#1090#1082#1080
  end
  object Charts: TImage
    Left = 352
    Top = 400
    Width = 294
    Height = 167
    Stretch = True
  end
  object LChart: TLabel
    Left = 352
    Top = 381
    Width = 3
    Height = 13
  end
  object CapacityGrid: TStringGrid
    Left = 8
    Top = 40
    Width = 638
    Height = 73
    ColCount = 2
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goFixedRowDefAlign]
    TabOrder = 0
    OnKeyPress = IntGridKeyPress
  end
  object NumDoorsGrid: TStringGrid
    Left = 8
    Top = 135
    Width = 638
    Height = 73
    ColCount = 2
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goFixedRowDefAlign]
    TabOrder = 1
    OnKeyPress = IntGridKeyPress
  end
  object CoefQuanGrid: TStringGrid
    Left = 8
    Top = 230
    Width = 638
    Height = 73
    ColCount = 2
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goFixedRowDefAlign]
    TabOrder = 2
    OnKeyPress = DoubleKeyPress
  end
  object ETimeIE: TEdit
    Left = 245
    Top = 309
    Width = 68
    Height = 21
    TabOrder = 3
    OnKeyPress = DoubleKeyPress
  end
  object EMinInterval: TEdit
    Left = 578
    Top = 309
    Width = 68
    Height = 21
    TabOrder = 4
    OnKeyPress = DoubleKeyPress
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 596
    Width = 652
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object ScrollBoxRes: TScrollBox
    Left = 8
    Top = 381
    Width = 322
    Height = 217
    TabOrder = 6
  end
  object BCalcData: TButton
    Left = 8
    Top = 331
    Width = 118
    Height = 25
    Caption = #1054#1073#1088#1072#1073#1086#1090#1072#1090#1100' '#1076#1072#1085#1085#1099#1077
    TabOrder = 7
    OnClick = BCalcDataClick
  end
  object BNextChart: TButton
    Left = 526
    Top = 565
    Width = 118
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1057#1083#1077#1076#1091#1102#1097#1080#1081' '#1075#1088#1072#1092#1080#1082
    TabOrder = 8
    OnClick = BNextChartClick
  end
  object BPrevChart: TButton
    Left = 350
    Top = 565
    Width = 121
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1055#1088#1077#1076#1099#1076#1091#1097#1080#1081' '#1075#1088#1072#1092#1080#1082
    TabOrder = 9
    OnClick = BPrevChartClick
  end
  object MainMenu: TMainMenu
    Left = 472
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object MCreate: TMenuItem
        Caption = #1057#1086#1079#1076#1072#1090#1100
        OnClick = MCreateClick
      end
      object MOpen: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100'...'
        OnClick = MOpenClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object MSave: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        OnClick = MSaveClick
      end
      object MSaveAs: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082'...'
        OnClick = MSaveAsClick
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object MClose: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = MCloseClick
      end
    end
    object N4: TMenuItem
      Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
      object MAddCapacity: TMenuItem
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1074#1084#1077#1089#1090#1080#1084#1086#1089#1090#1100
        OnClick = MAddCapacityClick
      end
      object MDelCapacity: TMenuItem
        Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1084#1077#1089#1090#1080#1084#1086#1089#1090#1100
        OnClick = MDelCapacityClick
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object MAddNumDoors: TMenuItem
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1095#1080#1089#1083#1086' '#1076#1074#1077#1088#1077#1081
        OnClick = MAddNumDoorsClick
      end
      object MDelNumDoors: TMenuItem
        Caption = #1059#1076#1072#1083#1080#1090#1100' '#1095#1080#1089#1083#1086' '#1076#1074#1077#1088#1077#1081
        OnClick = MDelNumDoorsClick
      end
      object N6: TMenuItem
        Caption = '-'
      end
      object MAddCoefQuan: TMenuItem
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1082#1086#1101#1092'. '#1074#1093#1086#1076#1072' '#1080' '#1074#1099#1093#1086#1076#1072
        OnClick = MAddCoefQuanClick
      end
      object MDelCoefQuan: TMenuItem
        Caption = #1059#1076#1072#1083#1080#1090#1100' '#1082#1086#1101#1092'. '#1074#1093#1086#1076#1072' '#1080' '#1074#1099#1093#1086#1076#1072
        OnClick = MDelCoefQuanClick
      end
    end
    object N7: TMenuItem
      Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090#1099
      object MCalcData: TMenuItem
        Caption = #1054#1073#1088#1072#1073#1086#1090#1072#1090#1100' '#1076#1072#1085#1085#1099#1077
        OnClick = BCalcDataClick
      end
    end
  end
  object SaveFileDialog: TSaveDialog
    DefaultExt = 'bso'
    Filter = #1060#1072#1081#1083#1099' '#1089' '#1080#1089#1093#1086#1076#1085#1099#1084#1080' '#1076#1072#1085#1085#1099#1084#1080' (*.bso)|*.bso|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Left = 616
    Top = 336
  end
  object OpenFileDialog: TOpenDialog
    DefaultExt = 'bso'
    Filter = #1060#1072#1081#1083#1099' '#1089' '#1080#1089#1093#1086#1076#1085#1099#1084#1080' '#1076#1072#1085#1085#1099#1084#1080' (*.bso)|*.bso|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Left = 576
    Top = 336
  end
end
