#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

struct _Position { //��ǥ�� �����ϱ����� ����ü
	int x;
	int y;
};

typedef _Position P; //����ü�� ��Ī�� ���� ����ü��������� P��� ��Ī���μ��� �����ϴ�.
typedef _Position* PP;//����ü�� !��������!���� ��Ī�� ���� ����ü��������� PP��� ��Ī���μ��� �����ϴ�.

/*
0.��
1.��
2.������
3.��������
*/



//�̷θ� ����ϱ����� �Լ��̴�.
void runMiro(char maze[21][21], PP player) {
	for (int i = 0; i < 20; i++) { 
		for (int j = 0; j < 20; j++) {
			if (maze[i][j] == '0')
				cout << "��";
			else if (player->x == j&&player->y == i)
				cout << "��";
			else if (maze[i][j] == '1')
				cout << "  ";
			else if (maze[i][j] == '2')
				cout << "��";
			else if (maze[i][j] == '3')
				cout << "��";
		}
		cout << endl;
	}
}
//�÷��̾ �����̵������ִ� �Լ�
void moveUp(char maze[21][21], PP player) {
	if (player->y-1 >= 0) {//�÷��̾ �����̵�����������ġ�� y��ǥ 0 �̻��϶��� �۵�
		if (maze[player->y - 1][player->x] != '0')//�÷��̾�����ġ���� ��ĭ���� ���̾ƴ϶��
			--player->y; // �÷��̾��� y��ǥ�� ����
	}
	return;
}
//�÷��̾ �Ʒ��� �̵������ִ� �Լ�
void moveDown(char maze[21][21], PP player) {
	if (player->y + 1 <= 19) {//�÷��̾ �Ʒ����̵������� ��ġ�� y��ǥ19 �����϶����۵�
		if (maze[player->y + 1][player->x] != '0')//�÷��̾��� ��ġ���� ��ĭ�Ʒ��� ���̾ƴ϶��
			++player->y;//�÷��̾��� y��ǥ�� ������Ų��
	}
	return;
}
//�÷��̾ �������� �̵������ִ� �Լ�
void moveLeft(char maze[21][21], PP player) {
	if (player->x -1 >= 0) {//�÷��̾ �������� �̵������� ��ġ�� x��ǥ0�̻��϶��� �۵�
		if (maze[player->y][player->x-1] != '0')//�÷��̾��� ��ġ �ٷο����� ���� �ƴ϶��
			--player->x; //�÷��̾��� x��ǥ�� ���ҽ�Ų��.
	}
	return;
}
//�÷��̾ ���������� �̵������ִ� �Լ�
void moveRight(char maze[21][21], PP player) {
	if (player->x + 1 <=19) {//�÷��̾ ���������� �̵������� ��ġ�� x��ǥ19�����϶��� �۵�
		if (maze[player->y][player->x + 1] != '0')//�÷��̾� ��ġ �ٷ� �������� ���� �ƴ϶��
			++player->x; //�÷��̾��� x��ǥ�� ������Ų��
	}
	return;
}



int main() {
	char strMiro[21][21] = {};
	P player; //�÷��̾�����ǥ�������ϱ����� ����ü����
	P stp; //�������� ��ǥ�� ���� �ϱ����� ����ü����
	P endp; //���� ������ ��ǥ�� �����ϱ����� ����ü����

	stp.x = 0;//�������� x��ǥ
	stp.y = 0;//�������� y��ǥ
	endp.x = 19;//���������� x��ǥ
	endp.y = 19;//���������� y��ǥ

	player = stp;//��ó�� �÷��̾��� x,y��ǥ�� �������� x,y ��ǥ

	//*���� �̷θ���Ʈ ������ �о�´�
	FILE* pFile = NULL;
	fopen_s(&pFile, "MazeList.txt", "rt");
	char** pMazeList = NULL; //*����������
	//*���� ���⼭ �̷��� ������ �޾Ƽ� �������ش�.
	if (pFile) {
		char cCount;
		fread(&cCount, 1, 1, pFile);//*���ڿ� 3�� �о��
		int iMazeCount = atoi(&cCount);//*���ڸ� ����3���� �ٲ��ִ� �Լ�
		fread(&cCount, 1, 1, pFile);//* \n�� �о��������
		pMazeList = new char*[iMazeCount];//*������ �迭 �����Ҵ�
		for (int i = 0; i < iMazeCount; i++) {
			int iNameCount = 0;
			pMazeList[i] = new char[256]; //*2���� �迭�� ����������
			while (true) {
				fread(&cCount, 1, 1, pFile);//*�ϳ��о���̱�
				if (cCount != '\n') {//*�ٵ� ������ ������ �ƴ϶��
					pMazeList[i][iNameCount] = cCount;//*�о�¹��ڸ� �ϳ����о������
					iNameCount++;//*�ϳ��о ������ ������ �����ؾ߰���
				}
				else//*\n�� �������ȴٸ�
					break;//*while���� ���
			}
			pMazeList[i][iNameCount] = 0;//*�׸��� �Ǹ�������0�� �������ν� ���ڿ��� ������ �˸���
		}
		fclose(pFile);
		for (int i = 0; i < iMazeCount; i++) {
			cout << i + 1 << "." << pMazeList[i] << endl;
		}
		cout << "�̷θ� �ϳ� �����ϼ���:" << endl;
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
		//�̷θ� ������ش�.
		runMiro(strMiro, &player);

		if (player.x == endp.x && player.y == endp.y) {
			cout << "�̷θ� Ż���ع��ȴ�" << endl;
			break;
		}
			
		cout << "W:�� S:�� A:�� D:�� Q:��������";
		cout << endl;
		int cInput = _getch(); //�ܼ�â���� �Է����ޱ����� �Լ� cin�� �ٸ��� enter���� �ٷ� �Էµ�
		if (cInput == 'q' || cInput == 'Q')
			break;
		switch (cInput)
		{
		 case 'w':
		 case 'W':
			 moveUp(strMiro, &player);//��
			 break;
		 case 's':
		 case 'S':
			 moveDown(strMiro, &player);//��
			 break;
		 case 'a':
		 case 'A':
			 moveLeft(strMiro, &player);//��
			 break;
		 case 'd':
		 case 'D':
			 moveRight(strMiro, &player);//��
			 break;
		}
	}
}