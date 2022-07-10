#include <thread>
#include <string>

void open_document_and_display_gui(std::string const& filename)
{}

bool done_editing()
{
    return true;
}

enum command_type{
    open_new_document
};


struct user_command
{
    command_type type;

    user_command():
            type(open_new_document)
    {}
};

user_command get_user_input()
{
    return user_command();
}

std::string get_filename_from_user()
{
    return "foo.doc";
}

void process_user_input(user_command const& cmd)
{}

void edit_document(std::string const& filename)
{
    open_document_and_display_gui(filename);
    while(!done_editing())
    {
        user_command cmd=get_user_input();
        if(cmd.type==open_new_document)
        {
            std::string const new_name=get_filename_from_user();
            std::thread t(edit_document,new_name);
            t.detach();
        }
        else
        {
            process_user_input(cmd);
        }
    }
}

int main()
{
    edit_document("bar.doc");
}

//如果用户选择打开一个新文档，需要启动一个新线程去打开新文档①，并分离线程②。
// 与当前线程做出的操作一样，新线程只不过是打开另一个文件而已。所以，edit_document函数可以复用，通过传参的形式打开新的文件。
