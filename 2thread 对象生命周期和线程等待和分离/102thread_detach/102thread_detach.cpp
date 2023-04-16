#include <thread>
#include <iostream>
//Linux -lpthread
using namespace std;
bool is_exit = false;
void ThreadMain()
{
    cout << "begin sub thread main " << this_thread::get_id() << endl;
    for (int i = 0; i < 10; i++)
    {
        if (!is_exit) break;
        cout << "in thread " << i << endl;
        this_thread::sleep_for(chrono::seconds(1));//1000ms
    }
    cout << "end sub thread main " << this_thread::get_id() << endl;
}
int main(int argc, char* argv[])
{
    {
        //thread th(ThreadMain); //出错，thread对象被销毁
    }
    {
        thread th(ThreadMain);
        th.detach(); // 等待子线程，子线程和主线程分离
    }

    {
        thread th(ThreadMain);
        this_thread::sleep_for(chrono::seconds(1));//1000ms
        is_exit = true; //֪ͨ���߳��˳�
        cout << "" << endl;
        th.join(); //等待子线程推出
        cout << "结束" << endl;
    }
    getchar();

    return 0;
}