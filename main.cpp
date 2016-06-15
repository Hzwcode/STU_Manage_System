#include "operation.h"
#include <cstdio>

void mainmenu(void);

int main(){
	Operation operation;
	int op;
	do{
		mainmenu();
		cout << "Please input your option[1-5]: ";
		cin >> op;
		cout << endl;
		int cmd;
		switch(op){
			case 1:
				cout << "---------------����----------------" << endl;
				cout << "        1.��ѯѧ����Ϣ" <<endl;
				cout << "        2.����ѧ����Ϣ" <<endl;
				cout << "        3.�޸�ѧ����Ϣ" <<endl;
				cout << "        4.ɾ��ѧ����Ϣ" <<endl;
				cout << "        5.������һ��" <<endl;
				cout << "-----------------------------------" << endl;
				cout << "Please input your option[1-5]: ";
				cin >> cmd;
				switch(cmd){
					case 1:{
                        string sno;
                        cout << "���������ѯѧ����ѧ�ţ� ";
                        cin >> sno;
                        operation.Search_stu(sno);
						break;
					}
					case 2:
					    operation.add();
						break;
					case 3:
					    operation.update();
						break;
					case 4:
					    operation.del();
						break;
                    case 5:
                        break;
					default:
					    cout << "doesn't have the choice, please choose again!" << endl;
						break;
				}
				cout << "Press any key to continue...";
				getchar();getchar();
				break;
			case 2:
				cout << "--------------------��ѯ---------------------" << endl;
				cout << "    1. ��ѧ�Ų�ѯѧ���ɼ���ѧ����Ϣ" <<endl;
				cout << "    2. ���γ̲�ѯĳ�ſγ̵�����ѧ���ɼ�" <<endl;
				cout << "    3. ������һ��" <<endl;
				cout << "---------------------------------------------" << endl;
				cout << "Please input your option[1-3]: ";
				cin >> cmd;

				if(cmd == 1){
					string sno;
					cout << "������ѧ�ţ� ";
					cin >> sno;
					operation.Search_sno(sno);
				}
				else if(cmd == 2){
                    string cno;
					cout << "������γ̺ţ� ";
					cin >> cno;
					operation.Search_cno(cno);
				}
				else if(cmd == 3){}
				else{
                    cout << "doesn't have the choice, please choose again!" << endl;
				}
				cout << "Press any key to continue...";
				getchar();getchar();
				break;
			case 3:
				cout << "--------------------ͳ��---------------------" << endl;
				cout << "    1. ���γ�ͳ�Ʋ�����ѧ��" <<endl;
				cout << "    2. ���γ̽�ĳ�ſεĳɼ�����" <<endl;
				cout << "    3. �����пγ̵���ѧ������" <<endl;
				cout << "    4. ������һ��" <<endl;
				cout << "---------------------------------------------" << endl;
				cout << "Please input your option[1-4]: ";
				cin >> cmd;
				if(cmd == 1)
					operation.Stat1();
				else if(cmd == 2)
					operation.Stat2();
				else if(cmd == 3)
                    operation.Stat3();
                else if(cmd == 4)
                    ;
                else
                    cout << "doesn't have the choice, please choose again!" << endl;
				cout << "Press any key to continue...";
				getchar();getchar();
				break;
            case 4:
                operation.save();
                op = 5;
                break;
            case 5:
                break;
			default:
			    cout << "doesn't have the choice, please choose again!" << endl;
				break;
		}
	}while(op != 5);
	cout << endl << "--------------------Welcome again!--------------------" << endl;
	return 0;
}

void mainmenu(void){
	cout << endl;
	cout << "***************���˵�**************" << endl;
	cout << "          1. ѧ����Ϣ" <<endl;
	cout << "          2. �ɼ���ѯ" <<endl;
	cout << "          3. �ɼ�ͳ��" <<endl;
	cout << "          4. ���沢�˳�"    <<endl;
	cout << "          5. �������˳�"    <<endl;
	cout << "***************���˵�**************" << endl;
}
