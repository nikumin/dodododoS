#include "DxLib.h"
#include "define.h"
#define DOGMOUNT 100

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
	int dog = LoadGraph("1UP1UPnew.png");//�L�m�R�̉摜
	int sun = LoadGraph("sun_remake_R2.png");//���z�̉摜
	int StartGraph = LoadGraph("Start.png");//Start���
	int FinishGraph = LoadGraph("mario99_R2.png");//���ʂ̃}���I
	int FinishGraph2 = LoadGraph("finish_sun_R.png");//
	int debumario = LoadGraph("debumario_R.png");//�Q�[�����}���I
	int night = LoadGraph("nightlandscape_R.png");//��̕��i
	int Finishmario = LoadGraph("Finishmario_R2.png");//100���������̃}���I
	int true_clear = LoadGraph("true_clear.png");//100���������̑��z
	int Rizap = LoadSoundMem("VALUE!.mp3");//Rizap���y
	int PowerUP = LoadSoundMem("powerup01.mp3");//1UP���ʉ�
	SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
	int dogX[DOGMOUNT], dogY[DOGMOUNT];//���̍��W
	int dogFlag[DOGMOUNT] = { 0 };//�������m�F
	int Key_Check = 0;//Key��������Ă��邩�m�F
	int TurnFlag = 0;
	int StartTime = GetNowCount();
	int ChangeFlag = 0;//��ʕύX
	double Count = 0;
	int StackFlag[DOGMOUNT] = { 0 };
	int LRmove[DOGMOUNT];
	for (int i = 0; i < DOGMOUNT; i++)
	{
		LRmove[i] = 3;
	}
//===============================���[�v�J�n=========================================================================================//
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		ClearDrawScreen();//��ʂ̏�����

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

			//===========================================�e�̏o��============================================================-

			if (CheckHitKey(KEY_INPUT_S))
			{
				PlaySoundMem(PowerUP, DX_PLAYTYPE_BACK);

				if (Key_Check == 0)//S��������Ă��Ȃ�
				{
					for (int i = 0; i < DOGMOUNT; i++)
					{
						if (dogFlag[i] == 0)
						{
							dogX[i] = 400;//�e�̏o������X���W
							dogY[i] = 400;//�e�̏o������Y���W

							Count++;
							TurnFlag++;

							dogFlag[i] = 1;//�e������
							break;//������
						}
					}
				}

				Key_Check = 1;//S�������ꂽ��
			}
			else
			{
				Key_Check = 0;
			}

			//==========================================�e�̓�����====================================================--//


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
					dogFlag[i] =  0 ;//�������m�F
					dogX[i] = 0;
					dogY[i] = 0;
					Count = 0;
					Key_Check = 0;
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

//#include "DxLib.h"
//
//
//int Flag;
//
//// �v���O������ WinMain ����n�܂�܂�
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//	SetMainWindowText("cat");
//	ChangeWindowMode(TRUE);//�E�B���h�E���[�h�ɐݒ�
//	DxLib_Init();//Dxlibrary������
//	SetGraphMode(800, 600, 32);
//	SetBackgroundColor(255, 255, 255);//�w�i�𔒐F
//
//	if (DxLib_Init() == -1)		// �c�w���C�u��������������
//	{
//		return -1;			// �G���[���N�����璼���ɏI��
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
//	//�}�E�X��\����Ԃɂ���
//	//SetMouseDispFlag(TRUE);
//
//	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
//
//		//��ʂ̏�����
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
//		//��ʂ̍X�V
//		ScreenFlip();
//	}
//
//
//
//	DxLib_End();			// �c�w���C�u�����g�p�̏I������
//
//	return 0;				// �\�t�g�̏I�� 
//}

//#include "DxLib.h"
//
//
//
//
//// �v���O������ WinMain ����n�܂�܂�
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//	SetMainWindowText("cat");
//	ChangeWindowMode(TRUE);//�E�B���h�E���[�h�ɐݒ�
//	DxLib_Init();//Dxlibrary������
//	SetGraphMode(800, 600, 32);
//	SetBackgroundColor(255, 255, 255);//�w�i�𔒐F
//
//	if (DxLib_Init() == -1)		// �c�w���C�u��������������
//	{
//		return -1;			// �G���[���N�����璼���ɏI��
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
//	//int cat1Flag = 0, cat2Flag = 0;//�L�̑��݊m�F
//	int catFlag[100];
//	int catBFlag = 0;
//	int sx[100], sy[100];
//	cat = LoadGraph("mos.png");
//
//	//�}�E�X��\����Ԃɂ���
//	//SetMouseDispFlag(TRUE);
//
//	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
//
//		//��ʂ̏�����
//		ClearDrawScreen();
//
//		//SetDrawScreen(DX_SCREEN_BACK);
////-----------------------------�L�̑���---------------------------------------//
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
//		//��ʂ̍X�V
//		ScreenFlip();
//	}
//
//
//
//	DxLib_End();			// �c�w���C�u�����g�p�̏I������
//
//	return 0;				// �\�t�g�̏I�� 
//}

//#include "DxLib.h"
//
//
//
//
//// �v���O������ WinMain ����n�܂�܂�
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//	SetMainWindowText("cat");
//	ChangeWindowMode(TRUE);//�E�B���h�E���[�h�ɐݒ�
//	DxLib_Init();//Dxlibrary������
//	SetGraphMode(800, 600, 32);
//	SetBackgroundColor(255, 255, 255);//�w�i�𔒐F
//
//	if (DxLib_Init() == -1)		// �c�w���C�u��������������
//	{
//		return -1;			// �G���[���N�����璼���ɏI��
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
//	//int cat1Flag = 0, cat2Flag = 0;//�L�̑��݊m�F
//	int catFlag[10];
//	int catBFlag = 0;
//	int sx[100], sy[100];
//	cat = LoadGraph("mos.png");
//
//	//�}�E�X��\����Ԃɂ���
//	//SetMouseDispFlag(TRUE);
//
//	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
//
//		//��ʂ̏�����
//		ClearDrawScreen();
//
//		//SetDrawScreen(DX_SCREEN_BACK);
//		//-----------------------------�L�̑���---------------------------------------//
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
//		//��ʂ̍X�V
//		ScreenFlip();
//	}
//
//
//
//	DxLib_End();			// �c�w���C�u�����g�p�̏I������
//
//	return 0;				// �\�t�g�̏I�� 
//}