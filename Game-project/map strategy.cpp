//📄 Tile and Chunk Definitions
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstring>

const int TILE_SIZE = 16;
const int CHUNK_DIM = 32; // 32x32 tiles
const int TILES_PER_CHUNK = CHUNK_DIM * CHUNK_DIM;
const int NUM_CHUNKS = 1; // just 1 chunk for this example

#pragma pack(push, 1)
struct Tile {
    uint8_t tileType;      // 0 = land, 1 = river, 2 = sea
    int16_t height;        // elevation
    uint16_t waterDepth;   // river/sea depth
    uint8_t biome;         // biome type
    uint8_t flags;         // custom flags
    uint8_t resource;      // optional resource
    uint8_t reserved[2];   // reserved
    uint32_t customData;   // custom pointer or ID
};

struct PakHeader {
    char magic[4] = {'M', 'P', 'A', 'K'};
    uint16_t version = 1;
    uint32_t numChunks = NUM_CHUNKS;
    uint64_t indexOffset; // set later
};

struct ChunkIndexEntry {
    uint16_t chunkX;
    uint16_t chunkY;
    uint64_t offset;
    uint32_t size;
};
#pragma pack(pop)


//📦 Writing the .pak File
void writePakFile(const std::string& filename) {
    std::ofstream pak(filename, std::ios::binary);
    if (!pak) {
        std::cerr << "Failed to open file for writing.\n";
        return;
    }

    // 1. Write temporary header
    PakHeader header;
    header.indexOffset = sizeof(PakHeader);
    pak.write(reinterpret_cast<char*>(&header), sizeof(header));

    // 2. Create a simple tile and fill chunk
    Tile exampleTile = {0, 10, 0, 1, 0, 0, {0, 0}, 42};
    std::vector<Tile> chunkTiles(TILES_PER_CHUNK, exampleTile);
    std::vector<char> chunkData(reinterpret_cast<char*>(chunkTiles.data()),
                                reinterpret_cast<char*>(chunkTiles.data()) + TILES_PER_CHUNK * sizeof(Tile));

    // 3. Write index entry (only 1 for now)
    ChunkIndexEntry index = {0, 0, sizeof(PakHeader) + sizeof(ChunkIndexEntry), static_cast<uint32_t>(chunkData.size())};
    pak.write(reinterpret_cast<char*>(&index), sizeof(index));

    // 4. Write the actual chunk data
    pak.write(chunkData.data(), chunkData.size());

    pak.close();
    std::cout << "Wrote " << filename << " with 1 chunk.\n";
}


//📥 Reading the .pak File
void readPakFile(const std::string& filename) {
    std::ifstream pak(filename, std::ios::binary);
    if (!pak) {
        std::cerr << "Failed to open file for reading.\n";
        return;
    }

    // 1. Read header
    PakHeader header;
    pak.read(reinterpret_cast<char*>(&header), sizeof(header));
    if (std::memcmp(header.magic, "MPAK", 4) != 0) {
        std::cerr << "Invalid file format.\n";
        return;
    }

    // 2. Read index entry
    ChunkIndexEntry index;
    pak.read(reinterpret_cast<char*>(&index), sizeof(index));

    // 3. Seek and read chunk data
    pak.seekg(index.offset);
    std::vector<Tile> chunkTiles(TILES_PER_CHUNK);
    pak.read(reinterpret_cast<char*>(chunkTiles.data()), index.size);

    // 4. Print first tile
    Tile& tile = chunkTiles[0];
    std::cout << "First tile:\n";
    std::cout << "  Type: " << (int)tile.tileType << "\n";
    std::cout << "  Height: " << tile.height << "m\n";
    std::cout << "  Depth: " << tile.waterDepth << "m\n";
    std::cout << "  Biome: " << (int)tile.biome << "\n";
    std::cout << "  CustomData: " << tile.customData << "\n";

    pak.close();
}


//🧪 main() Function
int main() {
    writePakFile("map.pak");
    readPakFile("map.pak");
    return 0;
}



/*
🎯 Summary of What This Does
Creates a .pak file containing:

A header

A chunk index (one chunk in this example)

A single chunk's tile data (32x32 = 1024 tiles)

Each tile is 16 bytes

Reads back the file and prints the first tile


✅ What This Gives You
A working .pak file with:

1 header

1 chunk index entry

1 chunk of tile data (32x32)

Easy to expand for multiple chunks or compression

🚀 Next Steps
Want help with:

Adding compression (e.g. Zlib, LZ4)?

Supporting multiple chunks?

Integrating into Unreal Engine or Unity?
Let me know and I’ll provide that code too.
*/