#ifndef ORDER_MATCHING_ENGINE_WRITER_H
#define ORDER_MATCHING_ENGINE_WRITER_H


#include <iostream>
#include <string>
#include <fstream>

class Writer{
    std::string fileName;
    std::ofstream file;

public:

    /**
     * Constructor for Writer class
     *
     * If unable to open file to read print to standard error a message.
     * If file has been opened correctly, write it to standard output.
     *
     * @param[in] _fileName destination csv files to update.
     */
    Writer(const std::string& fileName);
    Writer() = default;
    ~Writer();

    /**
     * Writes string to stream
     *
     * It used to write the Message and the OrderBook strings to the outfiles.
     * @param[in] stringToWrite string to write to the csv.
     */
    void writeLine(const std::string &);
    std::string getFileName() const;
};

#endif //ORDER_MATCHING_ENGINE_WRITER_H
