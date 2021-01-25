#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h> // time�Լ��̿�
#include <stdlib.h> // rand ,srand�̿�
#include <windows.h> // �ý����Լ� (cls ,pause, Sleep) ,  �ܼ�âũ��, Ÿ��Ʋ, �ؽ�Ʈ ����




void gotoxy(int x, int y) // X Y��ǥ ����

{

	COORD pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

int bubble(int lotto[], int num) {	//�������� �����Լ�
	int temp, i, j;
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			if (lotto[j] > lotto[j + 1])
			{
				temp = lotto[j];
				lotto[j] = lotto[j + 1];
				lotto[j + 1] = temp;
			}
		}
	}
}

int main()
{
	system("mode con cols=72 lines=25"); // �ܼ�â ũ�� ����
	system("title �ζ� ��ȣ ���߱�"); // Ÿ��Ʋ �̸� ���� 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // �ؽ�Ʈ ���� ����
	
	
	



	int arr[45];
	int fixnum;
	int lastnum[6], adnum[12]; //��ȸ�� ��÷��ȣ, ������
	int lotto[6];	//�̹��� �����ȣ
	int i, evencnt = 0, oddcnt = 0;
	int rannum, token = 0;
	srand(time(NULL)); // rand�Լ� �ð����� ������ �ʱ�ȭ

	for (i = 0; i < 45; i++)
		arr[i] = i + 1;

	fixnum = lotto[0] = 12;	//������ȣ :�ִٺ���
	arr[fixnum - 1] = 0;


	gotoxy(25, 8);
	printf("E�� �ζ� ������\n");

	gotoxy(25,11);
	printf("������ ��÷��ȣ\n\n\t\t\t");
	for (i = 0; i < 6; i++)
	{
		scanf("%d", &lastnum[i]);	//��ȸ�� ��ȣ�Է�(������������ �Է�)
	

		if (lastnum[i] == 1) {
			adnum[i * 2] = 0;
			adnum[i * 2 + 1] = 2;
		}

		else if (lastnum[i] == 45) {
			adnum[i * 2] = 44;
			adnum[i * 2 + 1] = 0;
		}

		else {
			if (lastnum[i] - 1 == lotto[0])		//�������� ���� ��� ����
				adnum[i * 2] = 0;
			else
				adnum[i * 2] = lastnum[i] - 1;	//������ ���ϱ�		

			if (lastnum[i] + 1 == lotto[0])
				adnum[i * 2 + 1] = 0;
			else
				adnum[i * 2 + 1] = lastnum[i] + 1;

			if (i != 0 && adnum[i * 2 - 1] > adnum[i * 2]) {	//��ȸ�� ��ȣ�� ���� ��� ����
				adnum[i * 2 - 1] = adnum[i * 2] = 0;
			}
		}
		arr[lastnum[i] - 1] = 0;	//��ȸ�� ��ȣ����
	}
	system("cls");

	/*
	for (i = 0; i < 12; i++)
		printf("%d\t", adnum[i]);
	printf(": ������\n\n");
	*/

	do 
	{
		lotto[1] = adnum[rand() % 12]; //������ �� ���� ����
		lotto[2] = adnum[rand() % 12];
	} while (lotto[1] == 0 || lotto[2] == 0 || lotto[1] == lotto[2]); //�ߺ�����

	for (i = 0; i < 12; i++) {	//����������
		if (adnum[i] != 0)
			arr[adnum[i] - 1] = 0;
	}

	/*
	for (i = 0; i < 45; i++)
		printf(" %d\t", arr[i]);	//���� ��
	printf(" : ������\n\n");
	*/

	while (token != 5)
	{

		token = evencnt = oddcnt = 0;
		for (i = 0; i < 3; i++) {
			if (lotto[i] % 2 == 0)
				evencnt++;
			else
				oddcnt++;
		}

		for (i = 3; i < 6;) //Ȧ¦���� ���߱� 3:3
		{	

			rannum = rand() % 45;

			if (arr[rannum] != 0 && arr[rannum] != lotto[i - 1] && arr[rannum] != lotto[i - 2]) //�ߺ�����
			{	

				if (arr[rannum] % 2 == 0 && evencnt < 3) 
				{
					lotto[i] = arr[rannum];
					evencnt++;
					i++;
				}
				else if (arr[rannum] % 2 == 1 && oddcnt < 3) 
				{
					lotto[i] = arr[rannum];
					oddcnt++;
					i++;
				}
			}
		}

		bubble(lotto, i - 1);	//�������� ����

		for (i = 1; i < 6; i++) 
		{
			if (lotto[i - 1] + 1 != lotto[i] || lotto[i] != lotto[i + 1] - 1)	//3�� �̻� ���ӵ� �� ����
				token++;
		}

	}

	gotoxy(25, 12); // X��ǥ 25 Y��ǥ 20
	printf("��ȣ ������ �����մϴ�.");
	Sleep(2000);
	system("cls"); // ȭ�� ���� �����

	gotoxy(25, 12);
	printf("�̹��� �����ȣ \n\n\t\t");
	for (i = 0; i < 6; i++)
	{
		printf("%5d", lotto[i]);
		Sleep(850);
	}

	system("pause>nul"); //������ ���
	return 0;
}