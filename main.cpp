#include "DxLib.h"
#include "define.h"
#include <vector>
#include	"Header.h"

using namespace std;

#define DOGMOUNT 100

class Point {
public:
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	};

	int x;
	int y;
};

class Texture {
private:
	int graphics;
public:
	vector<Point> pos;

	Texture(const char* FileName, bool autoPush = TRUE) {
		if (autoPush) this->pos.push_back(Point(0, 0));
		this->graphics = LoadGraph(FileName);
	};

	void add(Point p) {
		this->pos.push_back(p);
	};

	void draw(int flag = FALSE) const {
		for (auto i = 0; i < pos.size(); i++) {
			DrawGraph(this->pos.at(i).x, this->pos.at(i).y, this->graphics, flag);
		}
	};

};


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

	// 画面に表示を行うテクスチャー
	Texture sun("sun_remake_R2.png", FALSE);// 太陽の画像
	Texture start("Start.png");				// スタート画像
	Texture finish("finish_sun_R.png");		// 終了画像
	Texture night("nightlandscape_R.png");	// 夜の背景画像
	Texture true_clear("true_clear.png");	// ゲームクリア画像


	int Rizap = LoadSoundMem("VALUE!.mp3");//Rizap音楽
	int PowerUP = LoadSoundMem("powerup01.mp3");//1UP効果音

	SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);

	int gameStage = 0;		// 現在のゲーム画面状態
	int StartTime;			// ゲーム開始時間
	bool keyRock = FALSE;	// キー入力をロック




	int dogX[DOGMOUNT], dogY[DOGMOUNT];//犬の座標
	int dogFlag[DOGMOUNT] = { 0 };//犬製造確認





	int TurnFlag = 0;


	double Count = 0;
	int StackFlag[DOGMOUNT] = { 0 };
	int LRmove[DOGMOUNT];
	for (int i = 0; i < DOGMOUNT; i++)
	{
		LRmove[i] = 3;
	}

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){

		ClearDrawScreen();	// 画面の初期化

		switch (gameStage){

		// ゲーム開始画面
		case 0:{

			start.draw();

			if (CheckHitKey(KEY_INPUT_K)) {
				StartTime = GetNowCount();
				gameStage = 1;
			}

			break;
		}

		// プレイ画面
		case 1:{

			// ゲームBGMの再生
			PlaySoundMem(Rizap, DX_PLAYTYPE_BACK);

			night.draw(TRUE);

			// ゲームの終了画面へ推移
			if (GetNowCount() - StartTime > 10000)
			{
				gameStage = 2;
				break;
			}

			// 弾の発射処理
			if (CheckHitKey(KEY_INPUT_S))
			{

				// キー入力ロックを確認
				if (keyRock) {

					// 発射音の再生
					PlaySoundMem(PowerUP, DX_PLAYTYPE_BACK);

					// 新しい球を追加
					sun.add(Point(400, 400));

				}

				keyRock = TRUE; // キー入力をロック

			} else {
				keyRock = FALSE; // キー入力ロックを解除
			}


			// 弾の移動処理
			for (auto i = 0; i < sun.pos.size(); i++) {
				
			}

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
		case 2:{

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
					//Key_Check = 0;
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