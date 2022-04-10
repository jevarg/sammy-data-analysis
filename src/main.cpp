#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

#define RES_MAGIC_NUMBER 0x921A

struct HeaderInfo
{
    uint16_t    signature = 0;
    uint32_t    footerAddr = 0;
} __attribute__((packed));

struct FileInfo
{
    char        ext[4];

    uint8_t     c0; // probably enum
    uint8_t     c1; // probably enum

    uint16_t    dataAddr;

    uint16_t    unk0;
    uint16_t    size;
    uint16_t    unk1;
    uint16_t    unk2;

    void*       data = nullptr;
} __attribute__((packed));

HeaderInfo *readHeader(std::ifstream &ifs)
{
    HeaderInfo *header = new HeaderInfo;

    ifs.read(reinterpret_cast<char*>(header), sizeof(HeaderInfo));
    std::cout << std::showbase << std::setw(4) << std::hex;
    std::cout   << "Signature: " << header->signature << std::endl
                << "Footer addr: " << header->footerAddr << std::endl;

    if (header->signature != RES_MAGIC_NUMBER)
    {
        std::cerr << "Invalid magic number!" << std::endl;
        return nullptr;
    }

    std::cout << "Magic number is valid!\n\n";
    return header;
}

void readFileInfo(std::ifstream &ifs, FileInfo &fileInfo)
{
    ifs.read(reinterpret_cast<char*>(&fileInfo), sizeof(FileInfo) - sizeof(void *));
    std::cout   << "ext:        \"" << fileInfo.ext << '"' << std::endl
                << "dataAddr:   " << fileInfo.dataAddr << std::endl
                << "size:       " << fileInfo.size << " bytes\n\n";

    fileInfo.data = malloc(fileInfo.size);

    std::streampos pos = ifs.tellg();
    ifs.seekg(fileInfo.dataAddr);
    // TODO: check for failure

    ifs.read(reinterpret_cast<char *>(fileInfo.data), fileInfo.size);

    if (pos == -1)
    {
        ifs.seekg(0, std::ios::end);
    }
    else
    {
        ifs.seekg(pos);
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " FILE.RES" << std::endl;
        return 1;
    }

    std::ifstream ifs(argv[1], std::ios::binary);

    if (!ifs.is_open() || !ifs.good())
    {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }

    std::cout << "Opened file " << argv[1] << std::endl;

    HeaderInfo *header = readHeader(ifs);
    if (header == nullptr)
    {
        return 1;
    }


    ifs.seekg(header->footerAddr);
    std::vector<FileInfo> files;
    while (!ifs.eof() && ifs.peek() != EOF) {
        FileInfo file;
        readFileInfo(ifs, file);
        files.push_back(file);
    }

    std::cout << std::endl << "Found " << std::dec << files.size() << " files" << std::endl;

    int i = 0;
    for (auto it = files.begin(); it != files.end(); ++it)
    {
        ++i;
        if (it->data != nullptr)
        {
            std::ofstream outFile(std::to_string(i) + '.' + std::string(it->ext), std::ios::binary);
            outFile.write(static_cast<char *>(it->data), it->size);
            outFile.close();
            free(it->data);
        }
    }

    ifs.close();
    return 0;
}
