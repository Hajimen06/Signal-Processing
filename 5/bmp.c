/* 静岡大学　安藤和敏先生のプログラムを，真鍋が一部改変．												*/
/* http://coconut.sys.eng.shizuoka.ac.jp/bmp/																*/

/*****************************************************************************/
/*                                                                           */
/*     bmp.c: bmp ファイル処理のライブラリ                                   */
/*                                                                           */
/*             Kazutoshi Ando (Shizuoka Univ.)                               */
/*                                                                           */
/*                  Ver. 2004.11.30                                          */
/*                      WriteBmp: ヘッダ情報の欠落を修正.                    */
/*                  Ver. 2004.11.26                                          */
/*                      Diminish:  減調(?)ルーチンを追加.                    */
/*                      PrintBmpInfo: bmpファイル以外のファイルを読んだとき  */
/*                               に, エラーを出力するように変更.             */
/*                  Ver. 2004.08.20                                          */
/*                      ReadBmp: 24bit色のbmpファイル以外のファイルを        */
/*                               読んだときに, エラーを出力するように変更.   */
/*                      PrintBmpInfo: 水平, 垂直解像度を出力するように変更.  */
/*                      WriteBmp: ヘッダ情報の欠落を修正.                    */
/*                  Ver. 2004.08.18                                          */
/*                        Gray を追加.                                       */
/*                  Ver. 2004.08.17                                          */
/*                        4byte 境界に合わせるための計算式を改良,            */
/*                        Rotate90, Shrink, Mosaic を追加.                   */
/*                        エラーメッセージの出力先を標準エラー出力に変更.    */
/*                  Ver. 2003.11.04                                          */
/*                  Ver. 2010.10.19                                          */
/*                        long int を int で出力していると警告がでるので修正 */
/*                                                                           */
/*****************************************************************************/
#include "bmp.h"

/*
   関数名: ReadBmp
   引数  : char *filename, img *imgp
   返り値: void
   動作  : bmp形式のファイル filename を開いて, その画像データを
		   2次元配列 imgp->data に格納する. 同時に, ヘッダから読み込まれた
		   画像の幅と高さをグローバル変数 Bmp_width とBmp_height にセットする.
*/
void ReadBmp(char *filename, img *imgp) {
	int i, j;
	int Real_width;
	FILE *Bmp_Fp = fopen(filename, "rb");  /* バイナリモード読み込み用にオープン  */
	unsigned char *Bmp_Data;           /* 画像データを1行分格納               */


	unsigned char Bmp_headbuf[HEADERSIZE];/* ヘッダを格納するための変数          */
	char Bmp_type[2];                     /* ファイルタイプ "BM"                 */
	long Bmp_height;                      /* 高さ (ピクセル)                     */
	long Bmp_width;                       /* 幅   (ピクセル)                     */
	unsigned short Bmp_color;          /* 色 (ビット)     24                  */


	if (Bmp_Fp == NULL) {
		fprintf(stderr, "Error: file %s couldn\'t open for read!.\n", filename);
		exit(1);
	}

	/* ヘッダ読み込み */
	fread(Bmp_headbuf, sizeof(unsigned char), HEADERSIZE, Bmp_Fp);

	memcpy(&Bmp_type, Bmp_headbuf, sizeof(Bmp_type));
	if (strncmp(Bmp_type, "BM", 2) != 0) {
		fprintf(stderr, "Error: %s is not a bmp file.\n", filename);
		exit(1);
	}

	memcpy(&imgp->width, Bmp_headbuf + 18, 4);//sizeof(Bmp_width));
	memcpy(&imgp->height, Bmp_headbuf + 22, 4);//sizeof(Bmp_height));
	memcpy(&Bmp_color, Bmp_headbuf + 28, sizeof(Bmp_color));

	printf("width:%d\n", imgp->width);
	printf("height:%d\n", imgp->height);
	if (Bmp_color != 24) {
		fprintf(stderr, "Error: Bmp_color = %d is not implemented in this program.\n", Bmp_color);
		exit(1);
	}

	if (imgp->width > MAXWIDTH) {
		fprintf(stderr, "Error: Bmp_width = %ld > %d = MAXWIDTH!\n", imgp->width, MAXWIDTH);
		exit(1);
	}

	if (imgp->height > MAXHEIGHT) {
		fprintf(stderr, "Error: Bmp_height = %ld > %d = MAXHEIGHT!\n", imgp->height, MAXHEIGHT);
		exit(1);
	}

	Real_width = imgp->width * 3 + imgp->width % 4; /* 4byte 境界にあわせるために実際の幅の計算 */

   /* 配列領域の動的確保. 失敗した場合はエラーメッセージを出力して終了 */
	if ((Bmp_Data = (unsigned char *)calloc(Real_width, sizeof(unsigned char))) == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for Bmp_Data!\n");
		exit(1);
	}

	/* 画像データ読み込み */
	for (i = 0; i < imgp->height; i++) {
		fread(Bmp_Data, 1, Real_width, Bmp_Fp);
		for (j = 0; j < imgp->width; j++) {
			imgp->data[imgp->height - i - 1][j].b = Bmp_Data[j * 3];
			imgp->data[imgp->height - i - 1][j].g = Bmp_Data[j * 3 + 1];
			imgp->data[imgp->height - i - 1][j].r = Bmp_Data[j * 3 + 2];
		}
	}

	/* 動的に確保した配列領域の解放 */
	free(Bmp_Data);

	/* ファイルクローズ */
	fclose(Bmp_Fp);
}

/*
   関数名: WriteBmp
   引数  : char *filename, img *tp
   返り値: void
   動作  : 2次元配列 tp->data の内容を画像データとして, 24ビット
		   bmp形式のファイル filename に書き出す.
*/
void WriteBmp(char *filename, img *tp) {

	int i, j;
	int Real_width;
	FILE *Out_Fp = fopen(filename, "wb");  /* ファイルオープン */
	unsigned char *Bmp_Data;     /* 画像データを1行分格納               */

	unsigned char Bmp_headbuf[HEADERSIZE];/* ヘッダを格納するための変数          */

	unsigned long Bmp_size;               /* bmpファイルのサイズ (バイト)        */
	unsigned int Bmp_info_header_size; /* 情報ヘッダのサイズ = 40             */
	unsigned int Bmp_header_size;      /* ヘッダサイズ = 54*/
	long Bmp_height;                      /* 高さ (ピクセル)                     */
	long Bmp_width;                       /* 幅   (ピクセル)                     */
	unsigned short Bmp_planes;          /* プレーン数 常に 1                   */
	unsigned short Bmp_color;          /* 色 (ビット)     24                  */
	long Bmp_image_size;                  /* 画像部分のファイルサイズ (バイト)   */
	long Bmp_xppm;                        /* 水平解像度 (ppm)                    */
	long Bmp_yppm;                        /* 垂直解像度 (ppm)                    */

	if (Out_Fp == NULL) {
		fprintf(stderr, "Error: file %s couldn\'t open for write!\n", filename);
		exit(1);
	}

	Bmp_color = 24;
	Bmp_header_size = HEADERSIZE;
	Bmp_info_header_size = 40;
	Bmp_planes = 1;

	Real_width = tp->width * 3 + tp->width % 4;  /* 4byte 境界にあわせるために実際の幅の計算 */

	/* 配列領域の動的確保. 失敗した場合はエラーメッセージを出力して終了 */
	if ((Bmp_Data = (unsigned char *)calloc(Real_width, sizeof(unsigned char))) == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for Bmp_Data!\n");
		exit(1);
	}

	/* ヘッダ情報の準備 */
	Bmp_xppm = Bmp_yppm = 0;
	Bmp_image_size = tp->height*Real_width;
	Bmp_size = Bmp_image_size + HEADERSIZE;
	Bmp_headbuf[0] = 'B'; Bmp_headbuf[1] = 'M';
	memcpy(Bmp_headbuf + 2, &Bmp_size, sizeof(Bmp_size));
	Bmp_headbuf[6] = Bmp_headbuf[7] = Bmp_headbuf[8] = Bmp_headbuf[9] = 0;
	memcpy(Bmp_headbuf + 10, &Bmp_header_size, sizeof(Bmp_header_size));
	Bmp_headbuf[11] = Bmp_headbuf[12] = Bmp_headbuf[13] = 0;
	memcpy(Bmp_headbuf + 14, &Bmp_info_header_size, sizeof(Bmp_info_header_size));
	Bmp_headbuf[15] = Bmp_headbuf[16] = Bmp_headbuf[17] = 0;
	memcpy(Bmp_headbuf + 18, &tp->width, sizeof(Bmp_width));
	memcpy(Bmp_headbuf + 22, &tp->height, sizeof(Bmp_height));
	memcpy(Bmp_headbuf + 26, &Bmp_planes, sizeof(Bmp_planes));
	memcpy(Bmp_headbuf + 28, &Bmp_color, sizeof(Bmp_color));
	Bmp_headbuf[30] = Bmp_headbuf[31] = Bmp_headbuf[32] = Bmp_headbuf[33] = 0;
	memcpy(Bmp_headbuf + 34, &Bmp_image_size, sizeof(Bmp_image_size));
	memcpy(Bmp_headbuf + 38, &Bmp_xppm, sizeof(Bmp_xppm));
	memcpy(Bmp_headbuf + 42, &Bmp_yppm, sizeof(Bmp_yppm));
	Bmp_headbuf[46] = Bmp_headbuf[47] = Bmp_headbuf[48] = Bmp_headbuf[49] = 0;
	Bmp_headbuf[50] = Bmp_headbuf[51] = Bmp_headbuf[52] = Bmp_headbuf[53] = 0;

	/* ヘッダ情報書き出し */
	fwrite(Bmp_headbuf, sizeof(unsigned char), HEADERSIZE, Out_Fp);

	/* 画像データ書き出し */
	for (i = 0; i < tp->height; i++) {
		for (j = 0; j < tp->width; j++) {
			Bmp_Data[j * 3] = tp->data[tp->height - i - 1][j].b;
			Bmp_Data[j * 3 + 1] = tp->data[tp->height - i - 1][j].g;
			Bmp_Data[j * 3 + 2] = tp->data[tp->height - i - 1][j].r;
		}
		for (j = tp->width * 3; j < Real_width; j++) {
			Bmp_Data[j] = 0;
		}
		fwrite(Bmp_Data, sizeof(unsigned char), Real_width, Out_Fp);
	}

	/* 動的に確保した配列領域の解放 */
	free(Bmp_Data);

	/* ファイルクローズ */
	fclose(Out_Fp);
}

#ifdef XXX
void PrintBmpInfo(char *filename) {


	unsigned char Bmp_headbuf[HEADERSIZE];/* ヘッダを格納するための変数          */
	unsigned char Bmp_Pallet[PALLETSIZE]; /* カラーパレットを格納                */

	char Bmp_type[2];                     /* ファイルタイプ "BM"                 */
	unsigned long Bmp_size;               /* bmpファイルのサイズ (バイト)        */
	unsigned int Bmp_info_header_size; /* 情報ヘッダのサイズ = 40             */
	unsigned int Bmp_header_size;      /* ヘッダサイズ = 54*/
	long Bmp_height;                      /* 高さ (ピクセル)                     */
	long Bmp_width;                       /* 幅   (ピクセル)                     */
	unsigned short Bmp_planes;          /* プレーン数 常に 1                   */
	unsigned short Bmp_color;          /* 色 (ビット)     24                  */
	long Bmp_comp;                        /* 圧縮方法         0                  */
	long Bmp_image_size;                  /* 画像部分のファイルサイズ (バイト)   */
	long Bmp_xppm;                        /* 水平解像度 (ppm)                    */
	long Bmp_yppm;                        /* 垂直解像度 (ppm)                    */


  FILE *Bmp_Fp=fopen(filename,"rb");        /* バイナリモード読み込み用にオープン  */
  if(Bmp_Fp==NULL){
    fprintf(stderr,"Error: file %s couldn\'t open for write!\n",filename);
    exit(1);
  }

  fread(Bmp_headbuf,sizeof(unsigned char),HEADERSIZE,Bmp_Fp);

  memcpy(&Bmp_type,Bmp_headbuf,sizeof(Bmp_type));
  if (strncmp(Bmp_type,"BM",2)!=0) {
    fprintf(stderr,"Error: %s is not a bmp file.\n",filename);
    exit(1);
  }
  memcpy(&Bmp_size,Bmp_headbuf+2,sizeof(Bmp_size));
  memcpy(&Bmp_width,Bmp_headbuf+18,sizeof(Bmp_width));
  memcpy(&Bmp_height,Bmp_headbuf+22,sizeof(Bmp_height));
  memcpy(&Bmp_color,Bmp_headbuf+28,sizeof(Bmp_color));
  memcpy(&Bmp_comp,Bmp_headbuf+30,sizeof(Bmp_comp));
  memcpy(&Bmp_image_size,Bmp_headbuf+34,sizeof(Bmp_size));
  memcpy(&Bmp_xppm,Bmp_headbuf+38,sizeof(Bmp_xppm));
  memcpy(&Bmp_yppm,Bmp_headbuf+42,sizeof(Bmp_yppm));


  printf("ファイル名       = %s \n",filename);
  printf("ファイルタイプ   = %c%c \n",Bmp_type[0],Bmp_type[1]);
  printf("ファイルサイズ   = %ld (byte)\n",Bmp_size);
  printf("幅               = %ld (pixel)\n",Bmp_width);
  printf("高さ             = %ld (pixel)\n",Bmp_height);
  printf("色               = %d (bit)\n",Bmp_color);
  printf("圧縮             = %ld\n",Bmp_comp);
  printf("画像部分のサイズ = %ld (byte)\n",Bmp_image_size);
  printf("水平解像度       = %ld (ppm)\n",Bmp_xppm);
  printf("垂直解像度       = %ld (ppm)\n",Bmp_yppm);

	long temp;
	int i;
	i = 2;
  memcpy(&temp,Bmp_headbuf+i, 4);
	printf("%d:%d\n", i, temp);
	i = 6;
	memcpy(&temp,Bmp_headbuf+i, 4);
	printf("%d:%d\n", i, temp);
	i = 10;
	memcpy(&temp,Bmp_headbuf+i, 4);
	printf("%d:%d\n", i, temp);
	i = 14;
	memcpy(&temp,Bmp_headbuf+i, 4);
	printf("%d:%d\n", i, temp);
	i = 18;
	memcpy(&temp,Bmp_headbuf+i, 4);
	printf("%d:%d\n", i, temp);
	i = 22;
	memcpy(&temp,Bmp_headbuf+i, 2);
	printf("%d:%d\n", i, temp);
	i = 26;
	memcpy(&temp,Bmp_headbuf+i, 2);
	printf("%d:%d\n", i, temp);
	i = 30;
	memcpy(&temp,Bmp_headbuf+i, 4);
	printf("%d:%d\n", i, temp);
	i = 34;
	memcpy(&temp,Bmp_headbuf+i, 4);
	printf("%d:%d\n", i, temp);
	i = 38;
	memcpy(&temp,Bmp_headbuf+i, 4);
	printf("%d:%d\n", i, temp);
	i = 42;
	memcpy(&temp,Bmp_headbuf+i, 4);
	printf("%d:%d\n", i, temp);
	i = 46;
	memcpy(&temp,Bmp_headbuf+i, 4);
	printf("%d:%d\n", i, temp);
	i = 50;
	memcpy(&temp,Bmp_headbuf+i, 4);
	printf("%d:%d\n", i, temp);

  fclose(Bmp_Fp);
}
#endif
