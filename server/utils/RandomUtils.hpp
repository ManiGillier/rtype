/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** RandomUtils
*/

#ifndef RANDOMUTILS_HPP_
    #define RANDOMUTILS_HPP_

    #include <string>

class RandomUtils {
    public:
        static std::string generateRandomUUID(int size) {
            static constexpr const char tokens[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
            std::string randomString;

            for (int i = 0; i < size; i++) {
                randomString += tokens[rand() % (sizeof(tokens) - 1)];
                if (i && (i + 1) % 4 == 0 && i + 1 != size)
                    randomString += "-";
            }
            return randomString;
        }
};

#endif /* !RANDOMUTILS_HPP_ */
