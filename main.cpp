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
	SetMainWindowText("�h�h�h�hS");
	ChangeWindowMode(TRUE);//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(800, 600, 32);//�E�B���h�E�T�C�Y
	SetBackgroundColor(255, 255, 255);//�w�i�𔒐F
	SetDrawScreen(DX_SCREEN_BACK);//���ʂɐݒ�

	//Dx���C�u�����̏������`��𗠉�ʂɐݒ肷��
	if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0){
		return -1;//����[���N�����璼���ɏI��
	}

	// ��ʂɕ\�����s���e�N�X�`���[
	Texture sun("sun_remake_R2.png", FALSE);// ���z�̉摜
	Texture start("Start.png");				// �X�^�[�g�摜
	Texture finish("finish_sun_R.png");		// �I���摜
	Texture night("nightlandscape_R.png");	// ��̔w�i�摜
	Texture true_clear("true_clear.png");	// �Q�[���N���A�摜


	int Rizap = LoadSoundMem("VALUE!.mp3");//Rizap���y
	int PowerUP = LoadSoundMem("powerup01.mp3");//1UP���ʉ�

	SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);

	int gameStage = 0;		// ���݂̃Q�[����ʏ��
	int StartTime;			// �Q�[���J�n����
	bool keyRock = FALSE;	// �L�[���͂����b�N




	int dogX[DOGMOUNT], dogY[DOGMOUNT];//���̍��W
	int dogFlag[DOGMOUNT] = { 0 };//�������m�F





	int TurnFlag = 0;


	double Count = 0;
	int StackFlag[DOGMOUNT] = { 0 };
	int LRmove[DOGMOUNT];
	for (int i = 0; i < DOGMOUNT; i++)
	{
		LRmove[i] = 3;
	}

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){

		ClearDrawScreen();	// ��ʂ̏�����

		switch (gameStage){

		// �Q�[���J�n���
		case 0:{

			start.draw();

			if (CheckHitKey(KEY_INPUT_K)) {
				StartTime = GetNowCount();
				gameStage = 1;
			}

			break;
		}

		// �v���C���
		case 1:{

			// �Q�[��BGM�̍Đ�
			PlaySoundMem(Rizap, DX_PLAYTYPE_BACK);

			night.draw(TRUE);

			// �Q�[���̏I����ʂ֐���
			if (GetNowCount() - StartTime > 10000)
			{
				gameStage = 2;
				break;
			}

			// �e�̔��ˏ���
			if (CheckHitKey(KEY_INPUT_S))
			{

				// �L�[���̓��b�N���m�F
				if (keyRock) {

					// ���ˉ��̍Đ�
					PlaySoundMem(PowerUP, DX_PLAYTYPE_BACK);

					// �V��������ǉ�
					sun.add(Point(400, 400));

				}

				keyRock = TRUE; // �L�[���͂����b�N

			} else {
				keyRock = FALSE; // �L�[���̓��b�N������
			}


			// �e�̈ړ�����
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
					dogFlag[i] =  0 ;//�������m�F
					dogX[i] = 0;
					dogY[i] = 0;
					Count = 0;
					//Key_Check = 0;
					StackFlag[i] = 0;

				}
				ChangeFlag = 0;
			}

			DrawFormatString(400, 300, RED, "���Ȃ��̘A�ŉ�%.1lf", Count);
			DrawFormatString(400, 350, RED, "���Ȃ��̘A�ő��x ����%.3lf�� ", Count/10*3600);
			break;
		}
		default:{
			DxLib_End();
			return 0;
			break;
		}
	}
		
//============================��ʂ̍X�V================================================================//
		ScreenFlip();
	}

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}