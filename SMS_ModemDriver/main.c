#include "main.h"

//MYSQL my_connection;

//main����
//�Դ��ڽ��л�������
//���Ͷ���
//��ȡ����
int main(int argc, char **argv)
{
	conf_head = readcfg( CONF_FILE );
	//print_conf_node( conf_head );
	
	char *dev  = get_conf_node_value( conf_head, "SERIAL_DEV" );	

	pthread_t id1, id2, id3, id4;
	
	fd = OpenDev(dev);				//�򿪴���
	
	char *bond_rate_c = get_conf_node_value( conf_head, "BOND_RATE" );
	int bond_rate_i = atoi( bond_rate_c );
	//printf( "bond_rate is:%d\n", bond_rate_i );
	set_speed( fd, bond_rate_i );			//���ô��ڵĲ�����
	
	if (set_Parity(fd,8,1,'N') == FALSE)	//���ô��ڵ�У��λ
	{
		printf("Set Parity Error\n");
		exit (0);
	}
	
	//�����������ڿ��Ʒ���ʱ�����ͳ�����
	pthread_mutex_init ( &mutex_send, NULL );

	//�����������ڿ��ƽ���ʱ�����ͳ�����
	pthread_mutex_init ( &mutex_receive, NULL );
	
	//�����������ڿ��Ʒ��ͺͽ���ʱ���Դ��ڵĶ���д
	pthread_mutex_init ( &mutex, NULL );
	 
	connecting( conf_head );							//�������ݿ�
	 
	pthread_create(&id1, NULL, (void*)SendThread2ScanDB, NULL);			//�����߳�һ
	 
	pthread_create(&id2, NULL, (void*)SendThread2ScanList, NULL);		//�����̶߳�
	
	pthread_create(&id3, NULL, (void*)RecvThread2ScanPort, NULL);		//�����߳���
		
	pthread_create(&id4, NULL, (void*)RecvThread2ScanList, NULL);		//�����߳���
	
	pthread_join(id1, NULL);				//�����߳�һ

	pthread_join(id2, NULL);				//�����̶߳�
  
	pthread_join(id3, NULL);				//�����߳���
   
	pthread_join(id4, NULL);				//�����߳���
	
	close(fd); 							// �رմ��� 
	
	free_conf_node( conf_head );		//�ͷſ��ٵĿռ�
		
	mysql_close( &my_connection );		//�ر����ݿ�
	//mysql_library_end();	//
	return TRUE;
}
