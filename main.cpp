#include <iostream>
#include<fstream>
#define FILE_NAME "test.dat"
#define CHUNKSIZE 1024*1024*1024
#define FILE_SIZE_IN_GB 16
#include<algorithm>

class TotaRunTime {
    clock_t start;
    std::string _name{};
public:
    TotaRunTime(const std::string& name="*");
    ~TotaRunTime();
};
TotaRunTime::TotaRunTime(const std::string& name):_name(name) {
    start = clock();
};
TotaRunTime::~TotaRunTime() {
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken by %s is %f seconds\n",_name.c_str(), time_spent);
};


void generate();
int main() {
    generate();
    return 0;
};
void generate() {
    const TotaRunTime t{"generate()"};
    FILE *file;
    file = fopen(FILE_NAME, "w+b");
    if (file == NULL) {
        printf("File could not be opened\n");
        return;
    };
    char*buffer = new char[CHUNKSIZE];
    for (int i=1;i<=FILE_SIZE_IN_GB;++i) {
        if (fwrite(buffer,sizeof(char),CHUNKSIZE,file)) {
            printf("%dGB Generated\n",i);
        }else {
            printf("File could not be written\n");
            break;
        };
    }
    delete[] buffer;
    fclose(file);
};