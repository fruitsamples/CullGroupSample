/****************************//*        MENUS             *//* By Brian Greenstone      *//****************************//***************//* EXTERNALS   *//***************/#include <Fonts.h>#include <Menus.h>#include <ToolUtils.h>#include <Devices.h>#include <QD3D.h>#include <QD3DCamera.h>#include <QD3DDrawContext.h>#include <QD3DErrors.h>#include <QD3DGeometry.h>#include <QD3DGroup.h>#include <QD3DIO.h>#include <QD3DTransform.h>#include "myglobals.h"#include "qd3d_support.h"#include "mymenus.h"#include "misc.h"#include "main.h"#include "process.h"#include "objects.h"#include "mywindows.h"#include "3dmf.h"extern	QD3DSetupOutputType		gModelViewInfo;extern	Boolean				gUseCullingGroups,gShowBBoxes;extern	int					gCurrentTest;/******************//*  PROTOTYPES    *//******************/static void HandleSpecialMenuChoice(short theItem);/****************************//*    CONSTANTS             *//****************************/									// MENU BAR ITEMS //#define	NOT_A_NORMAL_MENU	-1#define	APPLE_MENU_ID		400#define	FILE_MENU_ID		401#define EDIT_MENU_ID		402#define SPECIAL_MENU_ID		128									// EDIT MENU ITEMS //									enum{	UNDO_ITEM	=	1,	CUT_ITEM	=	3,	COPY_ITEM	=	4,		PASTE_ITEM	=	5,	CLEAR_ITEM	=	6};									// FILE MENU ITEMS //enum{	OPEN_ITEM	= 1,	SAVE_ITEM	= 2,	QUIT_ITEM	= 5};									// APPLE MENU ITEMS //enum									{										ABOUT_ITEM = 1,	HELP_ITEM = 2};/**********************//*     VARIABLES      *//**********************/MenuHandle	gAppleMenu;/******************//* INIT MENU BAR  *//******************/void InitMenuBar(void){Handle	myMenuBar;							/* ALLOCATE MAIN MENU BAR */		if ((myMenuBar	=	GetNewMBar(400)) == NIL_POINTER)			DoFatalAlert("\pWhered the menu bar go?!");;	SetMenuBar(myMenuBar);						/* SET APPLE MENU */	if ((gAppleMenu	=	GetMenuHandle(400)) == NIL_POINTER)			DoFatalAlert("\pGetMHandle failed!");	AppendResMenu (gAppleMenu, 'DRVR');						// APPEND DESK ACCESSORIES		DrawMenuBar();}/***************************//* HANDLE MENU BAR CHOICE  *//***************************/void HandleMenuChoice(long menuChoice){short	theMenu;short	theItem;			if	(menuChoice != 0)	{		theMenu	=	HiWord(menuChoice);		theItem	=	LoWord(menuChoice);		switch	(theMenu)		{			case	APPLE_MENU_ID:					HandleAppleChoice(theItem);					break;								case	FILE_MENU_ID:					HandleFileChoice(theItem);					break;								case	EDIT_MENU_ID:					HandleEditChoice(theItem);					break;								case	SPECIAL_MENU_ID:					HandleSpecialMenuChoice(theItem);					break;							}		HiliteMenu(0);	}}/*****************************//* HANDLE APPLE MENU CHOICE  *//*****************************/void HandleAppleChoice(short theItem){Str255	accName;short		accNumber;			switch	(theItem)	{		case	ABOUT_ITEM:						Alert(402,NIL_POINTER);				break;		case	HELP_ITEM:				Alert(128,NIL_POINTER);				break;					default:				GetMenuItemText(gAppleMenu,theItem,accName);				accNumber	=	OpenDeskAcc(accName);				break;	}}/****************************//* HANDLE FILE MENU CHOICE  *//****************************/void HandleFileChoice(short theItem){	switch(theItem)	{		case	OPEN_ITEM:				break;						case	SAVE_ITEM:				Save3DMFModel(&gModelViewInfo, nil, DrawObjects);				break;						case	QUIT_ITEM:				DeleteAllObjects();				QD3D_DisposeWindowSetup(&gModelViewInfo);				DisposeWindow(gModelViewInfo.window);				CleanQuit();				break;					}}/****************************//* HANDLE SPECIAL MENU CHOICE  *//****************************/static void HandleSpecialMenuChoice(short theItem){MenuHandle	aMenu;	switch(theItem)	{					case	1:				// DO IT				QD3D_CalcFramesPerSecond();				while(!Button())					DoModelWindowNullEvent();				break;						case	2:				// USE BBOX				gUseCullingGroups = !gUseCullingGroups;				aMenu = GetMenuHandle(SPECIAL_MENU_ID);				if (gUseCullingGroups)					SetItemMark(aMenu, theItem, checkMark);				else					SetItemMark(aMenu, theItem, noMark);				BuildCurrentTest();				break;						case	3:				// SHOW BBOX				gShowBBoxes = !gShowBBoxes;				aMenu = GetMenuHandle(SPECIAL_MENU_ID);				if (gShowBBoxes)					SetItemMark(aMenu, theItem, checkMark);				else					SetItemMark(aMenu, theItem, noMark);				BuildCurrentTest();				break;						case	5:				// TriMesh test				gCurrentTest = TEST_TRIMESH;				BuildCurrentTest();				break;		case	6:				// Sphere test				gCurrentTest = TEST_SPHERE;				BuildCurrentTest();				break;		case	7:				// Torus test				gCurrentTest = TEST_TORUS;				BuildCurrentTest();				break;					}}/****************************//* HANDLE EDIT MENU CHOICE  *//****************************/void HandleEditChoice(short theItem){	SystemEdit(theItem-1);			switch(theItem)	{	}}