#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h> // time함수이용
#include <stdlib.h> // rand ,srand이용
#include <windows.h> // 시스템함수 (cls ,pause, Sleep) ,  콘솔창크기, 타이틀, 텍스트 색상




void gotoxy(int x, int y) // X Y좌표 설정

{

	COORD pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

int bubble(int lotto[], int num) {	//오름차순 정렬함수
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
	system("mode con cols=72 lines=25"); // 콘솔창 크기 조절
	system("title 로또 번호 맞추기"); // 타이틀 이름 설정 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // 텍스트 색상 변경
	
	
	



	int arr[45];
	int fixnum;
	int lastnum[6], adnum[12]; //전회차 당첨번호, 인접값
	int lotto[6];	//이번주 예상번호
	int i, evencnt = 0, oddcnt = 0;
	int rannum, token = 0;
	srand(time(NULL)); // rand함수 시간단위 난수로 초기화

	for (i = 0; i < 45; i++)
		arr[i] = i + 1;

	fixnum = lotto[0] = 12;	//고정번호 :최다빈출
	arr[fixnum - 1] = 0;


	gotoxy(25, 8);
	printf("E조 로또 생성기\n");

	gotoxy(25,11);
	printf("저번주 당첨번호\n\n\t\t\t");
	for (i = 0; i < 6; i++)
	{
		scanf("%d", &lastnum[i]);	//전회차 번호입력(오름차순으로 입력)
	

		if (lastnum[i] == 1) {
			adnum[i * 2] = 0;
			adnum[i * 2 + 1] = 2;
		}

		else if (lastnum[i] == 45) {
			adnum[i * 2] = 44;
			adnum[i * 2 + 1] = 0;
		}

		else {
			if (lastnum[i] - 1 == lotto[0])		//고정값과 같을 경우 제거
				adnum[i * 2] = 0;
			else
				adnum[i * 2] = lastnum[i] - 1;	//인접값 구하기		

			if (lastnum[i] + 1 == lotto[0])
				adnum[i * 2 + 1] = 0;
			else
				adnum[i * 2 + 1] = lastnum[i] + 1;

			if (i != 0 && adnum[i * 2 - 1] > adnum[i * 2]) {	//전회차 번호와 같은 경우 제거
				adnum[i * 2 - 1] = adnum[i * 2] = 0;
			}
		}
		arr[lastnum[i] - 1] = 0;	//전회차 번호제외
	}
	system("cls");

	/*
	for (i = 0; i < 12; i++)
		printf("%d\t", adnum[i]);
	printf(": 인접수\n\n");
	*/

	do 
	{
		lotto[1] = adnum[rand() % 12]; //인접값 중 랜덤 선택
		lotto[2] = adnum[rand() % 12];
	} while (lotto[1] == 0 || lotto[2] == 0 || lotto[1] == lotto[2]); //중복제거

	for (i = 0; i < 12; i++) {	//인접값제외
		if (adnum[i] != 0)
			arr[adnum[i] - 1] = 0;
	}

	/*
	for (i = 0; i < 45; i++)
		printf(" %d\t", arr[i]);	//남은 수
	printf(" : 남은수\n\n");
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

		for (i = 3; i < 6;) //홀짝비율 맞추기 3:3
		{	

			rannum = rand() % 45;

			if (arr[rannum] != 0 && arr[rannum] != lotto[i - 1] && arr[rannum] != lotto[i - 2]) //중복제거
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

		bubble(lotto, i - 1);	//오름차순 정렬

		for (i = 1; i < 6; i++) 
		{
			if (lotto[i - 1] + 1 != lotto[i] || lotto[i] != lotto[i + 1] - 1)	//3번 이상 연속된 수 제거
				token++;
		}

	}

	gotoxy(25, 12); // X좌표 25 Y좌표 20
	printf("번호 예측을 시작합니다.");
	Sleep(2000);
	system("cls"); // 화면 내용 지우기

	gotoxy(25, 12);
	printf("이번주 예상번호 \n\n\t\t");
	for (i = 0; i < 6; i++)
	{
		printf("%5d", lotto[i]);
		Sleep(850);
	}

	system("pause>nul"); //종료전 대기
	return 0;
}