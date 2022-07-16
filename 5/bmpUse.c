#include <stdio.h>
#include "bmp.h"	//�w�b�_�t�@�C�����C���N���[�h����

// bmp.h, bmp.c�̎g������

int main()
{
  int i,j;
  char filename[256];
  img image;		//�摜��img�\���̂ň���
  img *pimage;		//img�\���̂̃|�C���^

  sprintf( filename, "Lena256.bmp");	
  ReadBmp( filename, &image);			//���ꂪbmp�t�@�C���̓ǂݍ��ݕ�

  for( i=0; i<image.width; i++){		//�摜�����ɍ��̉������������[�v
    image.data[image.height/2][i].r = 0;	//�s�N�Z���̐Ԑ���
    image.data[image.height/2][i].g = 0;	//�s�N�Z���̗ΐ���
    image.data[image.height/2][i].b = 0;	//�s�N�Z���̐���
  }

  sprintf( filename, "lena_modified.bmp");
  WriteBmp( filename, &image);			//���ꂪbmp�t�@�C���̏������ݕ�


  //�[������摜�����
  if( (pimage = (img*)malloc(sizeof(img)))==NULL){	//���I��img���m��
    printf("malloc error\n");
    exit(1);
  }
  pimage->width = 128;	//�摜�̉���
  pimage->height = 64;	//�摜�̏c��
  for( i=0; i<pimage->height; i++){		//�摜�̊e�s�N�Z����rgb�̒l�����郋�[�v
    for( j=0; j<pimage->width; j++){
      pimage->data[i][j].r = j*2;
      pimage->data[i][j].g = i*4;
      pimage->data[i][j].b = 0;
    }
  }
  sprintf( filename, "testBmp.bmp");
  WriteBmp( filename, pimage);		//bmp�t�@�C���̏�������
  free( pimage);					//���I�ɕϐ����m�ۂ�����C��ŉ������

  return 0;
}
