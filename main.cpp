#include "DxLib.h"
#include "define.h"
#define DOGMOUNT 100

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("ドドドドS");
	ChangeWindowMode(TRUE);//ウィンドウモードに設定
	SetGraphMode(800, 600, 32);//ウィンドウサイズ
	SetBackgroundColor(255, 255, 255);//背景を白色
	SetDrawScreen(DX_SCREEN_BACK);//裏面に設定

	//Dxライブラリの初期化描画を裏画面に設定する
	if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0){
		return -1;//えらーが起きたら直ちに終了
	}
	int dog = LoadGraph("1UP1UPnew.png");//キノコの画像
	int sun = LoadGraph("sun_remake_R2.png");//太陽の画像
	int StartGraph = LoadGraph("Start.png");//Start画面
	int FinishGraph = LoadGraph("mario99_R2.png");//普通のマリオ
	int FinishGraph2 = LoadGraph("finish_sun_R.png");//
	int debumario = LoadGraph("debumario_R.png");//ゲーム中マリオ
	int night = LoadGraph("nightlandscape_R.png");//夜の風景
	int Finishmario = LoadGraph("Finishmario_R2.png");//100いった時のマリオ
	int true_clear = LoadGraph("true_clear.png");//100いった時の太陽
	int Rizap = LoadSoundMem("VALUE!.mp3");//Rizap音楽
	int PowerUP = LoadSoundMem("powerup01.mp3");//1UP効果音
	SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
	int dogX[DOGMOUNT], dogY[DOGMOUNT];//犬の座標
	int dogFlag[DOGMOUNT] = { 0 };//犬製造確認
	int Key_Check = 0;//Keyが押されているか確認
	int TurnFlag = 0;
	int StartTime = GetNowCount();
	int ChangeFlag = 0;//場面変更
	double Count = 0;
	int StackFlag[DOGMOUNT] = { 0 };
	int LRmove[DOGMOUNT];
	for (int i = 0; i < DOGMOUNT; i++)
	{
		LRmove[i] = 3;
	}
//===============================ループ開始=========================================================================================//
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		ClearDrawScreen();//画面の初期化

		switch (ChangeFlag){

			//------------------------------------------------------------------------------------------------------------------------------------------------------

		case 0:{

			DrawGraph(0, 0, StartGraph, FALSE);

			if (CheckHitKey(KEY_INPUT_K)){
				StartTime = GetNowCount();
				ChangeFlag = 1;
			}

			break;
		}

			//-------------------------------------------------------------------------------------------------------------------------------------------------------

		case 1:{

			PlaySoundMem(Rizap, DX_PLAYTYPE_BACK);
			ChangeFlag = 2;
		}


		case 2:{

			DrawGraph(0, 0, night, TRUE);


			if (GetNowCount() - StartTime > 10000)
			{
				ChangeFlag = 3;
				break;
			}

			//===========================================弾の出現============================================================-

			if (CheckHitKey(KEY_INPUT_S))
			{
				PlaySoundMem(PowerUP, DX_PLAYTYPE_BACK);

				if (Key_Check == 0)//Sが押されていない
				{
					for (int i = 0; i < DOGMOUNT; i++)
					{
						if (dogFlag[i] == 0)
						{
							dogX[i] = 400;//弾の出現するX座標
							dogY[i] = 400;//弾の出現するY座標

							Count++;
							TurnFlag++;

							dogFlag[i] = 1;//弾が存在
							break;//抜ける
						}
					}
				}

				Key_Check = 1;//Sが推されたよ
			}
			else
			{
				Key_Check = 0;
			}

			//==========================================弾の動き方====================================================--//


			for (int i = 0; i < DOGMOUNT; i += 2)
			{
				if (dogFlag[i] == 1)
				{
					if (dogY[i] >= 100 && dogX[i] == 400)
					{
						dogY[i] -= 3;
					}


					if (dogY[i] == 100)
					{
						dogX[i] += 2;
					}

					if (dogY[i] >= 100 && dogX[i] == 600 && StackFlag[i] == 0)
					{
						dogY[i] += 5;
						if (dogY[i] >= 525)
						{
							StackFlag[i] = 1;
						}
					}

					DrawGraph(dogX[i], dogY[i], sun, TRUE);
				}
			}




			for (int i = 1; i < DOGMOUNT; i += 2)
			{
				if (dogFlag[i] == 1)
				{
					if (dogY[i] >= 100 && dogX[i] == 400)
					{
						dogY[i] -= 3;
					}

					if (dogY[i] == 100)
					{
						dogX[i] -= 2;
					}

					if (dogY[i] >= 100 && dogX[i] == 200 && StackFlag[i] == 0)
					{
						dogY[i] += 5;
						if (dogY[i] >= 525)
						{
							StackFlag[i] = 1;

						}
					}

					DrawGraph(dogX[i], dogY[i], sun, TRUE);
				}
			}
				for (int i = 0; i < DOGMOUNT; i++)
				{
					
					if (StackFlag[i] == 1)
					{						
						dogX[i] += LRmove[i]; 
						if (dogX[i] >= 725)
						{
							LRmove[i] *= -1;
						}
						if (dogX[i] <= 0)
						{
							LRmove[i] *= -1;
						}
					}
				}
			}
		
		break;
		case 3:{

			StopSoundMem(Rizap);
			if (Count == 10){
				DrawGraph(0, 0, true_clear, FALSE);

			}
			else{
				DrawGraph(0, 0, FinishGraph2, FALSE);
			}
			if (CheckHitKey(KEY_INPUT_B)){

				for (int i = 0; i < DOGMOUNT; i++)
				{
					dogFlag[i] =  0 ;//犬製造確認
					dogX[i] = 0;
					dogY[i] = 0;
					Count = 0;
					Key_Check = 0;
					StackFlag[i] = 0;

				}
				ChangeFlag = 0;
			}

			DrawFormatString(400, 300, RED, "あなたの連打回数%.1lf", Count);
			DrawFormatString(400, 350, RED, "あなたの連打速度 時速%.3lf回 ", Count/10*3600);
			break;
		}
		default:{
			DxLib_End();
			return 0;
			break;
		}
	}
		
//============================画面の更新================================================================//
		ScreenFlip();
	}

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

//#include "DxLib.h"
//
//
//int Flag;
//
//// プログラムは WinMain から始まります
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//	SetMainWindowText("cat");
//	ChangeWindowMode(TRUE);//ウィンドウモードに設定
//	DxLib_Init();//Dxlibrary初期化
//	SetGraphMode(800, 600, 32);
//	SetBackgroundColor(255, 255, 255);//背景を白色
//
//	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
//	{
//		return -1;			// エラーが起きたら直ちに終了
//	}
//
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	int i;
//	int Cr, Cr2;
//	int MouseX = 0, MouseY = 0;
//	int x = 0, y = 0;
//	Cr = (0, 0, 0);
//	Cr2 = (255, 255, 255);
//	int cat;
//	
//
//	cat = LoadGraph("kuro.png");
//
//	//マウスを表示状態にする
//	//SetMouseDispFlag(TRUE);
//
//	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
//
//		//画面の初期化
//		ClearDrawScreen();
//
//		//SetDrawScreen(DX_SCREEN_BACK);
//		if (CheckHitKey(KEY_INPUT_Z)){
//			if (Flag==0){
//				Flag = 1;
//				x = 400;
//				y = 400;
//			}
//		}
//		if (Flag==1){
//			y -= 1;
//			if (y < 0)Flag = 0;
//		}
//		 if(Flag==1) DrawGraph(x, y, cat, FALSE);
//		//画面の更新
//		ScreenFlip();
//	}
//
//
//
//	DxLib_End();			// ＤＸライブラリ使用の終了処理
//
//	return 0;				// ソフトの終了 
//}

//#include "DxLib.h"
//
//
//
//
//// プログラムは WinMain から始まります
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//	SetMainWindowText("cat");
//	ChangeWindowMode(TRUE);//ウィンドウモードに設定
//	DxLib_Init();//Dxlibrary初期化
//	SetGraphMode(800, 600, 32);
//	SetBackgroundColor(255, 255, 255);//背景を白色
//
//	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
//	{
//		return -1;			// エラーが起きたら直ちに終了
//	}
//
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	int i;
//	int Cr, Cr2;
//	int MouseX = 0, MouseY = 0;
//	int x, y,x2,y2;
//	Cr = (0, 0, 0);
//	Cr2 = (255, 255, 255);
//	int cat;
//	//int cat1Flag = 0, cat2Flag = 0;//猫の存在確認
//	int catFlag[100];
//	int catBFlag = 0;
//	int sx[100], sy[100];
//	cat = LoadGraph("mos.png");
//
//	//マウスを表示状態にする
//	//SetMouseDispFlag(TRUE);
//
//	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
//
//		//画面の初期化
//		ClearDrawScreen();
//
//		//SetDrawScreen(DX_SCREEN_BACK);
////-----------------------------猫の存在---------------------------------------//
//
//		if (CheckHitKey(KEY_INPUT_Z)){
//			if (catBFlag == 0){
//
//				for (i = 0; i < 10; ++i)
//				{
//					if(catFlag[i] == 0){
//						sx[i] = 400;
//						sy[i] = 500;
//					}
//				}
//				//if (cat1Flag == 0){
//				//	x = 400;
//				//	y = 400;
//				//	cat1Flag = 1;
//				//}
//				//else if(cat2Flag == 0){
//				//	x2 = 400;
//				//	y2 = 500;
//				//	cat2Flag = 1;
//				//}
//			}
//			catBFlag = 1;
//		}
//		else{
//			catBFlag = 0;
//		}
//		for (i = 0; i < 6; ++i){
//			if (catFlag)
//
//		}
//
//			//if (cat1Flag == 1){
//			//	y -= 3;
//			//	DrawGraph(x, y, cat, FALSE);
//			//	if (y < 0)cat1Flag = 0;
//			//}
//			//if (cat2Flag == 1){
//			//	y2 -= 3;
//			//	DrawGraph(x2, y2, cat, FALSE);
//			//	if (y2 < 0)cat2Flag = 0;
//			//}
//		
//		//画面の更新
//		ScreenFlip();
//	}
//
//
//
//	DxLib_End();			// ＤＸライブラリ使用の終了処理
//
//	return 0;				// ソフトの終了 
//}

//#include "DxLib.h"
//
//
//
//
//// プログラムは WinMain から始まります
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//	SetMainWindowText("cat");
//	ChangeWindowMode(TRUE);//ウィンドウモードに設定
//	DxLib_Init();//Dxlibrary初期化
//	SetGraphMode(800, 600, 32);
//	SetBackgroundColor(255, 255, 255);//背景を白色
//
//	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
//	{
//		return -1;			// エラーが起きたら直ちに終了
//	}
//
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	int i;
//	int Cr, Cr2;
//	int MouseX = 0, MouseY = 0;
//	int x, y, x2, y2;
//	Cr = (0, 0, 0);
//	Cr2 = (255, 255, 255);
//	int cat;
//	//int cat1Flag = 0, cat2Flag = 0;//猫の存在確認
//	int catFlag[10];
//	int catBFlag = 0;
//	int sx[100], sy[100];
//	cat = LoadGraph("mos.png");
//
//	//マウスを表示状態にする
//	//SetMouseDispFlag(TRUE);
//
//	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
//
//		//画面の初期化
//		ClearDrawScreen();
//
//		//SetDrawScreen(DX_SCREEN_BACK);
//		//-----------------------------猫の存在---------------------------------------//
//
//		if (CheckHitKey(KEY_INPUT_Z)){
//			if (catBFlag == 0){
//
//				for (i = 0; i < 10; i++)
//				{
//					if (catFlag[i] == 0){
//						sx[i] = 100;
//						sy[i] = 100;
//						catFlag[i] = 1;
//					}
//				}
//				//if (cat1Flag == 0){
//				//	x = 400;
//				//	y = 400;
//				//	cat1Flag = 1;
//				//}
//				//else if(cat2Flag == 0){
//				//	x2 = 400;
//				//	y2 = 500;
//				//	cat2Flag = 1;
//				//}
//			}
//			catBFlag = 1;
//		}
//		else{
//			catBFlag = 0;
//		}
//			for (i = 0; i < 10; i++){
//				if (catFlag[i] == 1){
//					sy[i] -= 3;
//				}
//			}
//			for (i = 0; i < 10; i++){
//				if (catFlag[i] == 1){
//					DrawGraph(sx[i], sy[i], cat, FALSE);
//				}
//			}
//
//		//if (cat1Flag == 1){
//		//	y -= 3;
//		//	DrawGraph(x, y, cat, FALSE);
//		//	if (y < 0)cat1Flag = 0;
//		//}
//		//if (cat2Flag == 1){
//		//	y2 -= 3;
//		//	DrawGraph(x2, y2, cat, FALSE);
//		//	if (y2 < 0)cat2Flag = 0;
//		//}
//
//		//画面の更新
//		ScreenFlip();
//	}
//
//
//
//	DxLib_End();			// ＤＸライブラリ使用の終了処理
//
//	return 0;				// ソフトの終了 
//}