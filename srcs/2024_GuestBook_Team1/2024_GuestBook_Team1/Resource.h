//{{NO_DEPENDENCIES}}
// Microsoft Visual C++에서 생성한 포함 파일입니다.
// 다음에서 사용 2024_GuestBook_Team1.rc
#pragma once

#define ID_RIGHT_PANEL			1002
#define IDS_APP_TITLE			103
#define ID_FILE_LIST			101
#define IDR_MAINFRAME			128
#define IDD_MY2024GUESTBOOKTEAM1_DIALOG	102
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105

#define IDI_MY2024GUESTBOOKTEAM1			107
#define IDI_SMALL				108
#define IDC_MY2024GUESTBOOKTEAM1			109
#define IDI_YUHAN256			256
#define IDI_YUHAN				7065
#define IDC_MYICON				2

///사용자 정의 상수
#define DROW_CLASS L"DrowWindowClass"
#define DROW_NAME L"DrawWindow"

#define NAME_CLASS L"NameBarClass"
#define NAME_NAME L"NameBar"


// 브러쉬 종류 버튼 
#define BASIC 300
#define BRUSH 301
#define PENCIL 302 
#define SPRAY 303
#define MARKER 304
#define WATERCOLOR 305
#define STAMP 306

// 펜 굵기 
#define IDC_CLOSE_BUTTON		505
#define IDD_PEN_THICKNESS       504
#define IDC_THICKNESS_SLIDER    503  // 슬라이더의 ID
#define IDC_THICKNESS_EDIT      502  // 에디트 박스의 ID
//#define IDD_PEN_THICKNESS		501


/// 그리기 영역
#define PAINT_R_LEFT 10
#define PAINT_R_TOP 120
#define PAINT_R_RIGHT 1425
#define PAINT_R_BOTTOM 830

/// 펜, 스탬프 굵기 영역
#define WIDTH_R_LEFT 420
#define WIDTH_R_TOP  15
#define WIDTH_R_RIGHT 460
#define WIDTH_R_BOTTOM 45

/// 스탬프 변경 기능
#define IDI_HEART_ICON						140
#define IDI_UH_ICON							141
#define IDI_YUHAN_ICON						142
#define IDI_GU_ICON							145
#define IDI_PF_ICON							147

// 버튼 호출 상수
#define COLOR1 1001
#define COLOR2 1002
#define COLOR3 1003
#define P_WIDTH 1004
#define CLEAR 1005
#define NEW_FILE 1006
#define SAVE	 1007
#define LOAD 1008
#define FILE_MANAGER 1009
#define CREDIT 1010

#define EXCEL "..\\VisitList.csv"

#define TEXTSPEED 20

#ifndef IDC_STATIC
#define IDC_STATIC				-1


#define DEF_ID						65000
#define BUTTON_ID (DEF_ID + 1)
#define DEF_DROW_BT					(DEF_ID + 1)
#define DEF_LOAD_BT					(DEF_ID + 2)
#define DEF_CREDIT_BT				(IDM_ABOUT)



//DrowWindow
#define DW_DEF						(DEF_ID + 100)


#define CANVAS_DEF					(DEF_ID + 200)


#define NAMEBAR_DEF					(DEF_ID + 300)

#define NB_BACK_BT					(NAMEBAR_DEF + 1)
#define NB_SIDE_BT					(NAMEBAR_DEF + 2)
#define NB_FILE_NAME				(NAMEBAR_DEF + 3)


#define SIDE_DEF					(DEF_ID + 400)

#define SD_NEWFILE_BT				(SIDE_DEF + 1)
#define SD_SAVEFILE_BT				(SIDE_DEF + 2)
#define SD_LOADFILE_BT				(DEF_LOAD_BT)
#define SD_FILEMANAGER_BT			(SIDE_DEF + 4)
#define SD_CREDIT_BT				(DEF_CREDIT_BT)



#define TOOL_DEF					(DEF_ID + 500)

#define TL_COLOR1_BT				(TOOL_DEF + 1)
#define TL_COLOR2_BT				(TOOL_DEF + 2)
#define TL_COLOR3_BT				(TOOL_DEF + 3)
#define TL_PEN_WIDTH_BT				(TOOL_DEF + 4)
#define TL_CLEAR_BT					(TOOL_DEF + 5)
#define TL_SAVE_BT					(SD_SAVEFILE_BT)
#define TL_PLAY_BT					(TOOL_DEF + 7)
#define TL_RESET_BT					(TOOL_DEF + 8)
#define TL_COLORBOX_BT				(TOOL_DEF + 9)

#define IDI_TEST_IMAGE              555
#define IDI_PEN_ICON                551
#define IDI_BRUSH_ICON              552
//#define IDI_ERASE_ICON              553
#define IDI_PENCIL_ICON             554
#define IDI_SPRAY_ICON              556
#define IDI_RECTPEN_ICON            557
#define IDI_WATERPEN_ICON           558
#define IDI_THICK_ICON              560
#define IDI_PENEFFECT_ICON           561
#define IDI_COLOREFFECT_ICON        562
#define IDI_ERASE_ICON              564
#define IDI_STOP_ICON               565
#define IDI_PLAY_ICON               566
#define IDI_PAUSE_ICON              567
#define IDI_FILE_ICON               568
#define IDI_MENU_ICON               569
#define IDI_CLOSE_MENU_ICON         570

#define IDI_NEW_FILE_ICON           571
#define IDI_SAVE_ICON               563
#define IDI_LOAD_ICON               572
#define IDI_FILEMANAGER_ICON        573
#define IDI_CREDIT_ICON             574
#define IDI_EXIT_ICON               575

#define IDI_MAIN_SIGN_ICON          600
#define IDI_MAIN_LOAD_ICON          601
#define IDI_MAIN_CREDIT_ICON        602

#endif
// 다음은 새 개체에 사용할 기본값입니다.
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

#define _APS_NO_MFC					130
#define _APS_NEXT_RESOURCE_VALUE	129
#define _APS_NEXT_COMMAND_VALUE		32771
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		110
#endif
#endif

