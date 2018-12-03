int check_gameover(void) { //게임오버 체크(게임오버시 1반환 아닐시 0반환)
	int i, j;
	for (i = 0;i<4;i++) 
		for (j = 0;j<4;j++) 
			if (num[i][j] == 0) return 0; //빈칸 존재

	for (i = 0;i<3;i++) 
		for (j = 0;j<3;j++)
			if (num[i][j] == num[i + 1][j] || num[i][j] == num[i][j + 1]) return 0; //[0,0]부터 [2,2]까지 검사 

	for (i = 0;i<3;i++) 
		if (num[i][3] == num[i + 1][3]) return 0; //[0,3]~[3,3] 아래쪽 검사

	for (j = 0;j<3;j++) 
		if (num[3][j] == num[3][j + 1]) return 0; //[3,0]~[3,3] 오른쪽 검사 

	return 1;     
}//서로 같은 값이 붙어있다면 게임오버가 아니라고 판단 반대로 같은 값이 붙어있지않다면 게임오버