/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** PacketCompressor
*/

#ifndef PACKETCOMPRESSOR_HPP_
    #define PACKETCOMPRESSOR_HPP_

    #include <zlib.h>
    #include <vector>
    #include <cstdint>

class PacketCompressor {
    public:
        static std::vector<uint8_t> compress(const std::vector<uint8_t> &data) {
            if (data.empty())
                return {};
            uLongf compressedSize = compressBound(data.size());
            std::vector<uint8_t> compressed(compressedSize);
            int result = compress2(compressed.data(), &compressedSize,
                data.data(), data.size(), Z_DEFAULT_COMPRESSION);    
            if (result != Z_OK)
                throw Packet::PacketException("Could not compress packet.");

            compressed.resize(compressedSize);
            return compressed;
        }

    static std::vector<uint8_t> decompress(const std::vector<uint8_t> &data,
                                            std::size_t originalSize,
                                            std::size_t compressedSize) {
        if (data.empty())
            return {};
        std::vector<uint8_t> decompressed(originalSize);
        uLongf decompressedSize = originalSize;

        int result = uncompress(decompressed.data(), &decompressedSize,
            data.data(), compressedSize);
        if (result != Z_OK)
            throw Packet::PacketException("Could not decompress packet.");
        decompressed.resize(decompressedSize);
        return decompressed;
    }
};

#endif /* !PACKETCOMPRESSOR_HPP_ */
