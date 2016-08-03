object main: Tmain
  Left = 0
  Top = 0
  Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1072' '#1087#1088#1080#1077#1084#1072'\'#1087#1088#1086#1088#1080#1089#1086#1074#1082#1080' '#1076#1072#1085#1085#1099#1093' '#1086#1090' FTDI '
  ClientHeight = 277
  ClientWidth = 502
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object startButton: TButton
    Left = 414
    Top = 8
    Width = 75
    Height = 25
    Caption = #1057#1058#1040#1056#1058
    TabOrder = 0
    OnClick = startButtonClick
  end
  object viewerChart: TChart
    Left = 8
    Top = 0
    Width = 400
    Height = 250
    Legend.Visible = False
    Title.Text.Strings = (
      #1055#1088#1080#1085#1103#1090#1099#1077' '#1076#1072#1085#1085#1099#1077)
    BottomAxis.Title.Caption = #1089#1077#1082#1091#1085#1076#1099
    View3D = False
    TabOrder = 1
    object Series1: TFastLineSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      LinePen.Color = clRed
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
  object refreshTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = refreshTimerTimer
    Top = 232
  end
end
