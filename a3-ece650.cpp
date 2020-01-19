#include <iostream>
#include <unistd.h>
#include <vector>
#include <signal.h>
#include <sys/wait.h>

int processB(void) {
    while (!std::cin.eof()) {

        std::string inputstring;
        std::getline(std::cin, inputstring);
        std::cout << inputstring << std::endl;
    }

    return 0;
}


int main (int argc, char **argv) {

    int RtoA1[2];
    int A1toA2[2];
    pipe(RtoA1);
    pipe(A1toA2);
    pid_t child_id;

    child_id = fork();
    if(child_id == 0)
    {

        dup2(RtoA1[1], STDOUT_FILENO);
        close(RtoA1[0]);
        close(RtoA1[1]);

        execv("./rgen",argv);
        }
    else{


    pid_t child2_id = fork();
    if(child2_id == 0)
    {
        dup2(RtoA1[0], STDIN_FILENO);
        close(RtoA1[0]);
        close(RtoA1[1]);

        dup2(A1toA2[1], STDOUT_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);

        char *argv1[3];

        argv1[0] = (char *)"python";
        argv1[1] = (char *)"a1ece650.py";
        argv1[2] = nullptr;

        execvp("python", argv1);
    }
    else{
    pid_t child3_id = fork();
    if(child3_id == 0)
    {
        dup2(A1toA2[0], STDIN_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);

        execv("a2-ece650", argv);

    }
    dup2(A1toA2[1], STDOUT_FILENO);
    close(A1toA2[0]);
    close(A1toA2[1]);
    int end_of_file = processB();



       int check;
        kill(child_id, SIGTERM);
        waitpid(child_id, &check, 0);
        kill(child2_id, SIGTERM);
        waitpid(child2_id, &check, 0);
        kill(child3_id, SIGTERM);
        waitpid(child3_id, &check, 0);

    return end_of_file;
}}}
