#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <iomanip>

class ALU
{
    std::map<std::string, int> M = {
        {"M0", 0}, {"M1", 1}, {"M2", 2}, {"M3", 3}, {"M4", 4}, {"M5", 5}, {"M6", 6}, {"M7", 7}, {"M8", 8}, {"M9", 9}, {"M10", 10}, {"M11", 11}, {"M12", 12}, {"M13", 13}, {"M14", 14}, {"M15", 15}};

    // build a dictionary of op codes

    std::map<std::string, std::string> OPCODES = {
        {"am", "0000"},
        {"sm", "0001"},
        {"mm", "0010"},
        {"dm", "0011"},
        {"bnem", "0100"},
        {"sltm", "0101"},
        {"ai", "0110"},
        {"si", "0111"},
        {"mi", "1000"},
        {"di", "1001"},
        {"lci", "1010"},
        {"sci", "1011"},
        {"lo", "1100"},
        {"so", "1101"},
        {"jb", "1110"}};

    int pc = 32; // Program counter

    // Array to hold function pointers, indexed by opcode
    std::vector<std::function<int(std::string, std::string, std::string)>> functions;

    // array of integers to represent memory
    std::vector<int> &memory;

    // size of memory
    int memorySize;

public:
    ALU(std::vector<int> &mem, int memSize) : memory(mem), memorySize(memSize)
    {
        // not sure if we need memSize

        // Initialize the function array with 15 opcodes
        functions.resize(15);

        // Map opcodes to corresponding functions
        functions[0] = [this](std::string op1, std::string op2, std::string op3)
        { return am(op1, op2, op3); };
        functions[1] = [this](std::string op1, std::string op2, std::string op3)
        { return sm(op1, op2, op3); };
        functions[2] = [this](std::string op1, std::string op2, std::string op3)
        { return mm(op1, op2, op3); };
        functions[3] = [this](std::string op1, std::string op2, std::string op3)
        { return dm(op1, op2, op3); };
        functions[4] = [this](std::string op1, std::string op2, std::string op3)
        { return bnem(op1, op2, op3); };
        functions[5] = [this](std::string op1, std::string op2, std::string op3)
        { return sltm(op1, op2, op3); };
        functions[6] = [this](std::string op1, std::string op2, std::string op3)
        { return ai(op1, op2, op3); };
        functions[7] = [this](std::string op1, std::string op2, std::string op3)
        { return si(op1, op2, op3); };
        functions[8] = [this](std::string op1, std::string op2, std::string op3)
        { return mi(op1, op2, op3); };
        functions[9] = [this](std::string op1, std::string op2, std::string op3)
        { return di(op1, op2, op3); };
        functions[10] = [this](std::string op1, std::string op2, std::string op3)
        { return lci(op1, op2, op3); };
        functions[11] = [this](std::string op1, std::string op2, std::string op3)
        { return sci(op1, op2, op3); };
        functions[12] = [this](std::string op1, std::string op2, std::string op3)
        { return lo(op1, op2, op3); };
        functions[13] = [this](std::string op1, std::string op2, std::string op3)
        { return so(op1, op2, op3); };
        functions[14] = [this](std::string op1, std::string op2, std::string op3)
        { return jb(op1, op2, op3); };
    }

    // add memory-memory
    // opcode 0000
    int am(std::string op1, std::string op2, std::string op3)
    {
        memory[M[op3]] = memory[M[op1]] + memory[M[op2]];
        return 1;
    }

    // subtract memory-memory
    // opcode 0001
    int sm(std::string op1, std::string op2, std::string op3)
    {
        memory[M[op3]] = memory[M[op1]] - memory[M[op2]];
        return 1;
    }

    // multiply memory-memory
    // opcode 0010
    int mm(std::string op1, std::string op2, std::string op3)
    {
        memory[M[op3]] = memory[M[op1]] * memory[M[op2]];
        return 1;
    }

    // divide memory-memory
    // opcode 0011
    int dm(std::string op1, std::string op2, std::string op3)
    {
        if (memory[M[op2]] == 0)
        {
            return 0;
        }
        memory[M[op3]] = memory[M[op1]] / memory[M[op2]];
        return 1;
    }

    // branch if not equal memory-memory
    // opcode 0100
    int bnem(std::string op1, std::string op2, std::string op3)
    {
        if (memory[M[op1]] != memory[M[op2]])
        {
            return std::stoi(op3); // Adjust program counter
        }
        else
        {
            return 1;
        }
    }

    // set less than memory-memory
    // opcode 0101
    int sltm(std::string op1, std::string op2, std::string op3)
    {
        memory[M[op3]] = (memory[M[op1]] < memory[M[op2]]) ? 1 : 0;
        return 1;
    }

    // add immediate
    // opcode 0110
    int ai(std::string op1, std::string op2, std::string op3)
    {
        memory[M[op3]] = memory[M[op1]] + std::stoi(op2);
        return 1;
    }

    // subtract immediate
    // opcode 0111
    int si(std::string op1, std::string op2, std::string op3)
    {
        memory[M[op3]] = memory[M[op1]] - std::stoi(op2);
        return 1;
    }

    // multiply immediate
    // opcode 1000
    int mi(std::string op1, std::string op2, std::string op3)
    {
        memory[M[op3]] = memory[M[op1]] * std::stoi(op2);
        return 1;
    }

    // divide immediate
    // opcode 1001
    int di(std::string op1, std::string op2, std::string op3)
    {
        if (std::stoi(op2) == 0)
        {
            return 0;
        }
        memory[M[op3]] = memory[M[op1]] / std::stoi(op2);
        return 1;
    }

    // load constant immediate
    // opcode 1010
    int lci(std::string op1, std::string op2, std::string op3)
    {
        memory[M[op3]] = std::stoi(op1) + std::stoi(op2);
        return 1;
    }

    // subtract constant immediate
    // opcode 1011
    int sci(std::string op1, std::string op2, std::string op3)
    {
        // is this right?
        memory[M[op3]] = std::stoi(op1) + std::stoi(op2);
        return 1;
    }

    // load using offset
    // opcode 1100
    int lo(std::string op1, std::string op2, std::string op3)
    {
        memory[M[op3]] = memory[memory[M[op1]] + memory[M[op2]]];
        return 1;
    }

    // store using offset
    // opcode 1101
    int so(std::string op1, std::string op2, std::string op3)
    {
        memory[memory[M[op1]] + memory[M[op2]]] = memory[M[op3]];
        return 1;
    }

    // jump back
    // opcode 1110
    int jb(std::string op1, std::string op2, std::string op3)
    {
        return -(std::stoi(op1) + std::stoi(op2) + std::stoi(op3));
    }

    void printMemory()
    {
        int c = 0;
        for (auto const &x : memory)
        {
            std::cout << c << " : " << x << std::endl;
            c++;
        }
    }

    void printInColumns(const std::vector<int> &list, int columns)
    {
        int rows = (list.size() + columns - 1) / columns; // Calculate number of rows needed

        // Print the elements in multiple columns
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                int index = i + j * rows;
                if (index < list.size())
                {
                    // Print index with leading zeros
                    std::cout << std::setfill('0') << std::setw(2) << index << " : ";
                    // Print value with alignment
                    std::cout << std::setw(10) << list[index] << " | ";
                }
            }
            std::cout << std::endl;
        }
    }

    void printPC()
    {
        std::cout << "PC: " << pc << std::endl;
    }

    // execute("0000","0000","0000","0000")
    // or
    // execute("am","M0","M0","M0")
    // or a combination of both?
    void execute(std::string opcode, std::string op1, std::string op2, std::string op3)
    // void execute(uint8_t opcode, uint8_t op1, uint8_t op2, uint8_t op3)
    {
        // print opcode, op1, op2, op3
        std::cout << opcode << " " << op1 << " " << op2 << " " << op3 << std::endl;
        std::string mappedOpCode = OPCODES[opcode];
        int op = std::stoi(mappedOpCode, 0, 2);
        if (op >= 0 && op < functions.size())
        {
            int inc = functions[op](op1, op2, op3);
            if (inc)
            {
                pc += inc;
                std::cout << "Operation successful." << std::endl;
            }
            else
            {
                std::cout << "Error: Operation failed." << std::endl;
            }
        }
        else
        {
            std::cout << "Error: Invalid opcode." << std::endl;
        }
        // printMemory();
        printInColumns(memory, 8);
        printPC();
    }

    void setPC(int newPC)
    {
        pc = newPC;
    }

    int getPC()
    {
        return pc;
    }
};

int main()
{

    const int memSize = 128;
    std::vector<int> mainMemory(memSize, 0);

    ALU alu(mainMemory, memSize);

    alu.execute("lci", "0", "8", "M0");  // min
    alu.execute("lci", "0", "8", "M1");  // max
    alu.execute("lci", "0", "7", "M2");  // 2
    alu.execute("lci", "0", "11", "M3"); // 3
    alu.execute("lci", "0", "10", "M4"); // 4
    alu.execute("lci", "0", "4", "M5");  // size
    alu.execute("lci", "0", "1", "M6");  // idx
    alu.execute("lci", "0", "0", "M7");  // logic compare 1
    alu.execute("lci", "0", "1", "M8");  // logic compare 0
    alu.execute("lci", "0", "1", "M9");  // base address

    // am m9 m6 m15
    alu.execute("am", "M9", "M6", "M15"); // am operation (add mem-mem)
    // lo m15 m7 m0
    alu.execute("lo", "M15", "M7", "M10"); // lo operation (load using offset)

    // sltm m10 m0 m11
    alu.execute("sltm", "M10", "M0", "M11"); // sltm operation (set less than mem-mem)
    // bnem m11 m8 2
    alu.execute("bnem", "M11", "M8", "2"); // bnem operation (branch if not equal mem-mem)
    // lo m9 m6 m0
    alu.execute("lo", "M9", "M6", "M0"); // lo operation (load using offset)

    // sltm m1 m10 m11
    alu.execute("sltm", "M1", "M10", "M11"); // sltm operation (set less than mem-mem)
    // bnem m11 m8 2
    alu.execute("bnem", "M11", "M8", "2"); // bnem operation (branch if not equal mem-mem)
    // lo m9 m6 m1
    alu.execute("lo", "M9", "M6", "M1"); // lo operation (load using offset)

    // ai m6 1 m6
    alu.execute("ai", "M6", "1", "M6"); // ai operation (add immediate)
    // sltm m6 m5 m11
    alu.execute("sltm", "M6", "M5", "M11"); // sltm operation (set less than mem-mem)
    // bnem m11 m8 2
    alu.execute("bnem", "M11", "M8", "2"); // bnem operation (branch if not equal mem-mem)
    // jb 0 0 11
    alu.execute("jb", "0", "0", "11"); // jb operation (jump back)

    // lci 0 15 m12
    alu.execute("lci", "0", "15", "M12"); // lci operation (load constant immediate)
    // lci 0 15 m13
    alu.execute("lci", "0", "15", "M13"); // lci operation (load constant immediate)
    // ai m12 1 m12
    alu.execute("ai", "M12", "1", "M12"); // ai operation (add immediate)
    // ai m13 2 m13
    alu.execute("ai", "M13", "2", "M13"); // ai operation (add immediate)
    // so m12 m7 m0
    alu.execute("so", "M12", "M7", "M0"); // so operation (store using offset)
    // so m13 m7 m1
    alu.execute("so", "M13", "M7", "M1"); // so operation (store using offset)

    return 0;
}
