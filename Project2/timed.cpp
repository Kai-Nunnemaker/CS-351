#include <cstdio>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>

#include <barrier>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>

#include "ScopeTimer.h"
using Timer = ScopeTimer<seconds>;

const char *path = DATA_PATH "/Data.bin";
const size_t DefaultNumThreads = 8;

template <typename Type>
Type *loadData(const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror(path);
        exit(1);
    }
    off_t size = lseek(fd, 0, SEEK_END);
    void *memory = mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0);
    return reinterpret_cast<Type *>(memory);
}

int main(int argc, char *argv[]) {
    // SERIAL SECTION #1: program start-up
    Timer timer{"main program"};

    size_t numThreads = argc > 1 ? std::stoul(argv[1]) : DefaultNumThreads;

    using Byte = unsigned char;
    using Bytes = Byte *;
    Bytes data = loadData<Byte>(path);

    size_t numHashes = *reinterpret_cast<size_t *>(data);
    data += sizeof(numHashes);

    using Hash = unsigned long long;
    using Hashes = std::vector<Hash>;
    Hashes hashes(numHashes);

    size_t hashID = 0;

    std::mutex getHashData;
    std::mutex storeHash;
    std::barrier barrier(numThreads);

    // End of serial init; record elapsed
    --numThreads;
    timer.elapsed();

    // PARALLEL SECTION: thread creation & hashing
    for (size_t id = 0; id <= numThreads; ++id) {
        std::thread t([&]() {
            while (true) {
                size_t myHashID;
                size_t numBytes;
                Bytes  myHashData;
                {
                    std::lock_guard lock{getHashData};
                    if (hashID >= numHashes) break;
                    myHashID   = hashID++;
                    numBytes   = *reinterpret_cast<size_t *>(data);
                    myHashData = data + sizeof(numBytes);
                    data      += sizeof(numBytes) + numBytes;
                }
                // compute hash
                const Hash multiplier = 2654435789ULL;
                Hash       hash       = 104395301ULL;
                Bytes      bytes      = reinterpret_cast<Bytes>(myHashData);
                for (size_t j = 0; j < numBytes; ++j)
                    hash += (multiplier * bytes[j]) ^ (hash >> 23);
                {
                    std::lock_guard lock{storeHash};
                    hashes[myHashID] = hash;
                }
            }
            barrier.arrive_and_wait();
        });
        (id < numThreads) ? t.detach() : t.join();
    }

    // SERIAL SECTION #2: results output
    {
        Timer resultsTimer{"results output"};
        std::string outpath{argv[0]};
        outpath += ".txt";
        std::ofstream output{outpath};
        for (auto h : hashes) output << h << "\n";
        output.close();
    }

    return 0;
}
