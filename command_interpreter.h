#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H
#include "dfs.h"
#include "datahandler.h"
#include <fstream>
#include <string>
class command_interpreter {
  private:
    std::fstream *input_stream;    // input.txt
    std::fstream *output_stream;   // output.txt
    std::fstream *commands_stream; // commands.txt
    std::string read_nextstr(std::fstream *); // reads the next string from a given fstream
    void read_input(); // reads the input.txt and inserts to datahandler
    int read_nextint(
        std::fstream *stream); // reads the next int from a given stringo
    datahandler *db;
    dfs * df;
  public:
    command_interpreter(std::string path, std::string path2, std::string path3,
                        datahandler *db, dfs *df);
    void start_parsing(); // starts the cmd interpreter
};
#endif