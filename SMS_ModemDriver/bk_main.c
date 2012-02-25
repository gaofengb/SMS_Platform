#include "main.h"

//main����
//�Դ��ڽ��л�������
//���Ͷ���
//��ȡ����
int main(int argc, char **argv)
{
		CONF_NODE *conf_head;
		conf_head = readcfg( CONF_FILE );
		
		char *dev  = SERIAL_DEV;			//��ʼ������

	 	pthread_t id1,id2,id3,id4;
		
 		fd = OpenDev(dev);				//�򿪴���
 		
		set_speed( fd,115200 );			//���ô��ڵĲ�����
		
		if (set_Parity(fd,8,1,'N') == FALSE)	//���ô��ڵ�У��λ
		{
				printf("Set Parity Error\n");
				exit (0);
		}
		
		//�����������ڿ��Ʒ���ʱ�����ͳ�����
  		pthread_mutex_init (&mutex_send,NULL);
    
		//�����������ڿ��ƽ���ʱ�����ͳ�����
  		pthread_mutex_init (&mutex_receive,NULL);
		
		//�����������ڿ��Ʒ��ͺͽ���ʱ���Դ��ڵĶ���д
		pthread_mutex_init (&mutex,NULL);
 		 
		 connect();							//�������ݿ�
 		 
/*         pthread_create(&id1, NULL, (void*)myThread1, NULL);		//�����߳�һ*/
	 
		pthread_create(&id2, NULL, (void*)myThread2, NULL);		//�����̶߳�
	
		 pthread_create(&id3, NULL, (void*)myThread3, NULL);		//�����߳���
		
		pthread_create(&id4, NULL, (void*)myThread4, NULL);		//�����߳���
		
/*        pthread_join(id1, NULL);				//�����߳�һ*/
	
		pthread_join(id2, NULL);				//�����̶߳�
	  
		pthread_join(id3, NULL);				//�����߳���
	   
		pthread_join(id4, NULL);				//�����߳���
	  	
		close(fd); 							// �رմ��� 
			
		//mysql_close( &my_connection );		//�ر����ݿ�
		//mysql_library_end();	//
		return TRUE;
}
