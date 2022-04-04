#include <iostream>
#include <iomanip>
#include <fstream>

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

    void*       data;
} __attribute__((packed));

HeaderInfo *readHeader(std::ifstream &ifs)
{
    HeaderInfo *header = new HeaderInfo;

    ifs.read(reinterpret_cast<char*>(header), sizeof(HeaderInfo));
    std::cout   << "Signature: " << std::showbase << std::setw(4) << std::hex
                << header->signature << std::endl
                << "Footer addr: " << std::hex << header->footerAddr << std::endl;

    if (header->signature != RES_MAGIC_NUMBER)
    {
        std::cerr << "Invalid magic number!" << std::endl;
        return nullptr;
    }

    std::cout << "Magic number is valid!" << std::endl;
    return header;
}

FileInfo *readFileInfo(std::ifstream &ifs)
{
    FileInfo *fileInfo = new FileInfo;

    ifs.read(reinterpret_cast<char*>(fileInfo), sizeof(FileInfo));
    std::cout   << "ext: " << fileInfo->ext << std::endl
                << "dataAddr: " << fileInfo->dataAddr << std::endl
                << "size: " << fileInfo->size << " bytes" << std::endl;

    return fileInfo;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " FILE.RES" << std::endl;
        return 1;
    }

    std::ifstream ifs(argv[1], std::ios_base::binary);

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

    FileInfo *fileInfo = readFileInfo(ifs);
    if (fileInfo == nullptr)
    {
        return 1;
    }

    ifs.close();
    return 0;
}