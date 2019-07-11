#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

struct _Position { //좌표를 저장하기위한 구조체
	int x;
	int y;
};

typedef _Position P; //구초체의 별칭을 선언 구조체변수선언시 P라는 별칭으로선언 가능하다.
typedef _Position* PP;//구초체의 !포인터형!으로 별칭을 선언 구조체변수선언시 PP라는 별칭으로선언 가능하다.

/*
0.벽
1.길
2.시작점
3.도착지점
*/



//미로를 출력하기위한 함수이다.
void runMiro(char maze[21][21], PP player) {
	for (int i = 0; i < 20; i++) { 
		for (int j = 0; j < 20; j++) {
			if (maze[i][j] == '0')
				cout << "■";
			else if (player->x == j&&player->y == i)
				cout << "●";
			else if (maze[i][j] == '1')
				cout << "  ";
			else if (maze[i][j] == '2')
				cout << "○";
			else if (maze[i][j] == '3')
				cout << "★";
		}
		cout << endl;
	}
}
//플레이어를 위로이동시켜주는 함수
void moveUp(char maze[21][21], PP player) {
	if (player->y-1 >= 0) {//플레이어가 위로이동했을때의위치가 y좌표 0 이상일때만 작동
		if (maze[player->y - 1][player->x] != '0')//플레이어의위치보다 한칸위에 벽이아니라면
			--player->y; // 플레이어의 y좌표를 감소
	}
	return;
}
//플레이어를 아래로 이동시켜주는 함수
void moveDown(char maze[21][21], PP player) {
	if (player->y + 1 <= 19) {//플레이어가 아래로이동했을때 위치가 y좌표19 이하일때만작동
		if (maze[player->y + 1][player->x] != '0')//플레이어의 위치보다 한칸아래가 벽이아니라면
			++player->y;//플레이어의 y좌표를 증가시킨다
	}
	return;
}
//플레이어를 왼쪽으로 이동시켜주는 함수
void moveLeft(char maze[21][21], PP player) {
	if (player->x -1 >= 0) {//플레이어가 왼쪽으로 이동했을때 위치가 x좌표0이상일때만 작동
		if (maze[player->y][player->x-1] != '0')//플레이어의 위치 바로왼쪽이 벽이 아니라면
			--player->x; //플레이어의 x좌표를 감소시킨다.
	}
	return;
}
//플레이어를 오른쪽으로 이동시켜주는 함수
void moveRight(char maze[21][21], PP player) {
	if (player->x + 1 <=19) {//플레이어가 오른쪽으로 이동했을때 위치가 x좌표19이하일때만 작동
		if (maze[player->y][player->x + 1] != '0')//플레이어 위치 바로 오른쪽이 벽이 아니라면
			++player->x; //플레이어의 x좌표를 증가시킨다
	}
	return;
}



int main() {
	char strMiro[21][21] = {};
	P player; //플레이어의좌표를저장하기위한 구조체변수
	P stp; //시작점의 좌표를 저장 하기위한 구조체변수
	P endp; //골인 지점의 좌표를 저장하기위한 구조체변수

	stp.x = 0;//시작점의 x좌표
	stp.y = 0;//시작점의 y좌표
	endp.x = 19;//골인지점의 x좌표
	endp.y = 19;//골인지점의 y좌표

	player = stp;//맨처음 플레이어의 x,y좌표는 시작점의 x,y 좌표

	//*먼저 미로리스트 파일을 읽어온다
	FILE* pFile = NULL;
	fopen_s(&pFile, "MazeList.txt", "rt");
	char** pMazeList = NULL; //*더블포인터
	//*이제 여기서 미로의 갯수를 받아서 저장해준다.
	if (pFile) {
		char cCount;
		fread(&cCount, 1, 1, pFile);//*문자열 3을 읽어옴
		int iMazeCount = atoi(&cCount);//*문자를 정수3으로 바꿔주는 함수
		fread(&cCount, 1, 1, pFile);//* \n을 읽어오기위함
		pMazeList = new char*[iMazeCount];//*포인터 배열 동적할당
		for (int i = 0; i < iMazeCount; i++) {
			int iNameCount = 0;
			pMazeList[i] = new char[256]; //*2차원 배열로 만들어버리기
			while (true) {
				fread(&cCount, 1, 1, pFile);//*하나읽어들이기
				if (cCount != '\n') {//*근데 읽은게 개행이 아니라면
					pMazeList[i][iNameCount] = cCount;//*읽어온문자를 하나씩읽어버리기
					iNameCount++;//*하나읽어서 들어갔으면 갯수도 증가해야겠지
				}
				else//*\n을 만나버렸다면
					break;//*while문을 통과
			}
			pMazeList[i][iNameCount] = 0;//*그리고 맨마지막에0을 넣음으로써 문자열의 끝임을 알린다
		}
		fclose(pFile);
		for (int i = 0; i < iMazeCount; i++) {
			cout << i + 1 << "." << pMazeList[i] << endl;
		}
		cout << "미로를 하나 선택하세요:" << endl;
		int select;
		cin >> select;
		fopen_s(&pFile, pMazeList[select - 1], "rt");
		if (pFile) {
			char pText;
			for (int i = 0; i < 20; i++) {
				fread(strMiro[i], 1, 20, pFile);
				fread(&cCount, 1, 1, pFile);
			}
			fclose(pFile);
		}
	}



	
	while (true)
	{ 
		system("cls");
		//미로를 출력해준다.
		runMiro(strMiro, &player);

		if (player.x == endp.x && player.y == endp.y) {
			cout << "미로를 탈출해버렸다" << endl;
			break;
		}
			
		cout << "W:상 S:하 A:좌 D:우 Q:게임종료";
		cout << endl;
		int cInput = _getch(); //콘솔창에서 입력을받기위한 함수 cin과 다르게 enter없이 바로 입력됨
		if (cInput == 'q' || cInput == 'Q')
			break;
		switch (cInput)
		{
		 case 'w':
		 case 'W':
			 moveUp(strMiro, &player);//상
			 break;
		 case 's':
		 case 'S':
			 moveDown(strMiro, &player);//하
			 break;
		 case 'a':
		 case 'A':
			 moveLeft(strMiro, &player);//좌
			 break;
		 case 'd':
		 case 'D':
			 moveRight(strMiro, &player);//우
			 break;
		}
	}
}