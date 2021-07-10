#include "command_interpreter.h"

command_interpreter::command_interpreter(std::string input, std::string output,
                                         std::string commands,
                                         datahandler *db, dfs* df) {
    this->input_stream = new std::fstream(input, std::ios::in);
    this->output_stream = new std::fstream(output, std::ios::out);
    this->commands_stream = new std::fstream(commands, std::ios::in);
    this->db = db;
    this->df = df;
}

/*
 * Reads the input from the input stream and inserts to datahandler.
 */
void command_interpreter::read_input() {
    int n1, n2;
    while (*input_stream >> n1 && *input_stream >> n2) {
        db->insert(n1, n2);
    }
}


void command_interpreter::start_parsing() {

    clock_t c = clock();

    if (read_nextstr(commands_stream) == "READ_DATA") {
        read_input();
        while (!commands_stream->eof()) { // Continue reading until it reaches the end of file.
            std::string command = read_nextstr(commands_stream); // Read the command
            //Cases:
            if (command == "INSERT_LINK") {
                int n1 = read_nextint(commands_stream);
                int n2 = read_nextint(commands_stream);
                db->insert(n1, n2);
            } else if (command == "DELETE_LINK") {
                int n1 = read_nextint(commands_stream);
                int n2 = read_nextint(commands_stream);
                db->remove(n1, n2);
            } else if (command == "FIND_NEIGHBORS") {
                int n = read_nextint(commands_stream);
                std::vector<int> neighs = db->findNeighbors(n);
                *output_stream << n << ", " << neighs.size();
                if (neighs.size() != 0) {
                    *output_stream << ", ";
                    for (int i = 0; i < neighs.size(); i++) {
                        *output_stream << neighs[i] << " ";
                    }
                    *output_stream << std::endl;
                }
            } else if (command == "FIND_NUM_CONNECTED_COMPONENTS") { // DFS
                Array<webclass> output = db->dfs(); // non-directional graph
                int a = df->start_dfs(output); // actual dfs function
                *output_stream << "Connected : " << a << std::endl; // output components
            }
        }
    } else {
        return;
    }
    double a = (double)(clock() - c) / CLOCKS_PER_SEC;
    *output_stream << "Execution Time : " << a << std::endl;
}

std::string command_interpreter::read_nextstr(std::fstream *stream) {
    std::string tmp;
    *stream >> tmp;

    return tmp;
}

int command_interpreter::read_nextint(std::fstream *stream) {
    int i = std::stoi(read_nextstr(stream));
    return i;
}