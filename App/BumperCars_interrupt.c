#include "common.h"
#include "include.h"
#include "BumperCars_interrupt.h"
/*****����ͷ���ж�*****/
 uint32 n_L,n_R;//�����ȫ�ֱ���
 uint8 Dir_L,Dir_R;//�����ȫ�ֱ���
void PORTA_IRQHandler(void)
{
    uint8  n;
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;

    n = 29;
    if(flag & (1 << n))
    {
        camera_vsync();
    }

}

/*****DMA�ж�*****/
void DMA0_IRQHandler(void)
{
    camera_dma();
}

/*****��ʱ��ȡ��������ֵ�ж�*****/
void PIT3_IRQHandler(void)
 {
    
  //  nll=nl;
    //nrl=nr;
   // n_L =ftm_input_get(FTM1,FTM_CH0);//PTA8 �ϱ�������֪�������������ҵ��
   /// n_R =ftm_input_get(FTM2,FTM_CH1);//PTA11 �±�����
    //=nl-nll;
    //=nr-nrl;
    Dir_L=gpio_get(PTA10);      //�ϱ�����
    Dir_R=gpio_get(PTA9);       //�±�����
    
   // ftm_input_clean(FTM1);      
   // ftm_input_clean(FTM2);      //�����ֵ
     n_L=ftm_quad_get(FTM1);          //��ȡFTM �������� ��������(������ʾ������)
     n_R=ftm_quad_get(FTM2);
     ftm_quad_clean(FTM1);
     ftm_quad_clean(FTM2);
    
    PIT_Flag_Clear(PIT3);
}/*init�ļ���ȡ��//enable_irq(PIT3_IRQn);ע��*/
