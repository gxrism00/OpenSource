int check_gameover(void) { //���ӿ��� üũ(���ӿ����� 1��ȯ �ƴҽ� 0��ȯ)
	int i, j;
	for (i = 0;i<4;i++) 
		for (j = 0;j<4;j++) 
			if (num[i][j] == 0) return 0; //��ĭ ����

	for (i = 0;i<3;i++) 
		for (j = 0;j<3;j++)
			if (num[i][j] == num[i + 1][j] || num[i][j] == num[i][j + 1]) return 0; //[0,0]���� [2,2]���� �˻� 

	for (i = 0;i<3;i++) 
		if (num[i][3] == num[i + 1][3]) return 0; //[0,3]~[3,3] �Ʒ��� �˻�

	for (j = 0;j<3;j++) 
		if (num[3][j] == num[3][j + 1]) return 0; //[3,0]~[3,3] ������ �˻� 

	return 1;     
}//���� ���� ���� �پ��ִٸ� ���ӿ����� �ƴ϶�� �Ǵ� �ݴ�� ���� ���� �پ������ʴٸ� ���ӿ���