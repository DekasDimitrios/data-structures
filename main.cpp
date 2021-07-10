#include "command_interpreter.h"
#include "datahandler.h"
#include "dfs.h"
int main(int argsc, char ** argsv) {
    int mode = std::stoi(argsv[1]); //Get mode
    datahandler *db = new datahandler(mode); // Start the data handler

    dfs * df = new dfs(db);
    command_interpreter *cmd = new command_interpreter(
        "input.txt",
        "output.txt",
        "commands.txt", db, df); // Initialize the command interpreter
    cmd->start_parsing(); // start the interpreter.

    return 0;
}