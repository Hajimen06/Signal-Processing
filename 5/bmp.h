/* 静岡大学　安藤和敏先生のプログラムを，真鍋が改変．												*/
/* http://coconut.sys.eng.shizuoka.ac.jp/bmp/																*/

/*****************************************************************************/
/*                                                                           */
/*     bmp.h: bmp ファイル処理のライブラリのためのヘッダファイル             */
/*                                                                           */
/*             Kazutoshi Ando (Shizuoka Univ.)                               */
/*                                                                           */
/*                  Ver. 2004.08.18                                          */
/*                  Ver. 2004.08.17                                          */
/*                  Ver. 2003.11.04                                          */
/*                                                                           */
/*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HEADERSIZE   54               /* ヘッダのサイズ 54 = 14 + 40         */
#define PALLETSIZE 1024               /* パレットのサイズ                    */
#define MAXWIDTH   1000               /* 幅(pixel)の上限                     */
#define MAXHEIGHT  1000               /* 高さ(pixel) の上限                  */


typedef struct {                      /* 1ピクセルあたりの赤緑青の各輝度     */
	unsigned char r;
	unsigned char g;
	unsigned char b;
} color;

typedef struct {
	long height;
	long width;
	color data[MAXHEIGHT][MAXWIDTH];
} img;

void ReadBmp(char *filename, img *imgp);
void WriteBmp(char *filename, img *tp);
