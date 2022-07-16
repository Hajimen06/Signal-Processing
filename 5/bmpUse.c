#include <stdio.h>
#include "bmp.h"	//ヘッダファイルをインクルードする

// bmp.h, bmp.cの使い方例

int main()
{
  int i,j;
  char filename[256];
  img image;		//画像はimg構造体で扱う
  img *pimage;		//img構造体のポインタ

  sprintf( filename, "Lena256.bmp");	
  ReadBmp( filename, &image);			//これがbmpファイルの読み込み方

  for( i=0; i<image.width; i++){		//画像中央に黒の横線を引くループ
    image.data[image.height/2][i].r = 0;	//ピクセルの赤成分
    image.data[image.height/2][i].g = 0;	//ピクセルの緑成分
    image.data[image.height/2][i].b = 0;	//ピクセルの青成分
  }

  sprintf( filename, "lena_modified.bmp");
  WriteBmp( filename, &image);			//これがbmpファイルの書き込み方


  //ゼロから画像を作る
  if( (pimage = (img*)malloc(sizeof(img)))==NULL){	//動的にimgを確保
    printf("malloc error\n");
    exit(1);
  }
  pimage->width = 128;	//画像の横幅
  pimage->height = 64;	//画像の縦幅
  for( i=0; i<pimage->height; i++){		//画像の各ピクセルにrgbの値を入れるループ
    for( j=0; j<pimage->width; j++){
      pimage->data[i][j].r = j*2;
      pimage->data[i][j].g = i*4;
      pimage->data[i][j].b = 0;
    }
  }
  sprintf( filename, "testBmp.bmp");
  WriteBmp( filename, pimage);		//bmpファイルの書き込み
  free( pimage);					//動的に変数を確保したら，後で解放する

  return 0;
}
