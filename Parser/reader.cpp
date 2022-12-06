#include "reader.h"

Reader::Reader(std::string _fileName, std::string _stock) :
        fileName(std::move(_fileName)), stock(std::move(_stock)) {
    file.open(fileName);
    if (!file.is_open()) {
        std::cerr << "The input file: " << fileName << " cannot be open! " << std::endl;
    } else {
        std::cout << "Opened " << fileName << " to read ITCH 5.0. messages." << std::endl;
        validFile = true;
    }
    start = time(0);
}

Reader::Reader(std::string _stock) : stock(std::move(_stock)) {}

void Reader::printProgress(){
    count ++;
    if(count % 10000000 == 0) {
        std::cout << "Processed " << count / 1000000 << "Million messages. "
                  << int(count / difftime(time(0), start) / 10000) / 100. << " Mio messages per sec." << std::endl;
    }
}

void Reader::readBytesIntoMessage(const long &size){
    file.read(message, size);
}

void Reader::skipBytes(const long &size){
    file.ignore(size);
}

char Reader::getKey(){
    char key;
    file.get(key);
    return key;
}

Message Reader::createMessage(){
//    char str[1024];

    printProgress();
    Message msg;
    skipBytes(2);
    char key = getKey();
//    std::cout << "key: " << key << "   Pos: "<<  this->file.tellg() << std::endl;
    char ticker[9];
    strncpy(ticker, stock.c_str(), 8); ticker[8] = 0;


    switch(key){
        uint64_t timeStamp, orderId, oldOrderId, newOrderId;
        uint32_t size, price, execSize, cancSize, newSize, newPrice;

        // debug
        uint64_t locateCode, trackingNumb;
        char eventCode;

        char direction;
        char mpid[5];


        case 'S':
            readBytesIntoMessage(11);
            break;
        case 'R':
            readBytesIntoMessage(38);
            break;
        case 'H':
            readBytesIntoMessage(24);
            break;
        case 'T':
            readBytesIntoMessage(19);
            break;
        case 'z':
            readBytesIntoMessage(19);
            break;
        case 'Y':
            readBytesIntoMessage(19);
            break;
        case 'L':
            readBytesIntoMessage(25);
            break;
        case 'V':
            readBytesIntoMessage(34);
            break;
        case 'W':
            readBytesIntoMessage(11);
            break;
        case 'K':
            readBytesIntoMessage(27);
            break;
        case 'J':
            readBytesIntoMessage(34);
            break;
        case 'h':
            readBytesIntoMessage(20);
            break;
        case 'A':
            readBytesIntoMessage(35);
            timeStamp = parse_ts(message+4);
            orderId = parse_uint64(message+10);
            direction = message[18];
            size = parse_uint32(message+19);
            strncpy(ticker, message+23, 8); ticker[8] = 0;
            price = parse_uint32(message+31);
            msg.setType(key);
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(orderId));
            msg.setSide(static_cast<side_type>(direction == 'S'));
            msg.setRemSize(static_cast<size_type>(size));
            msg.setPrice(static_cast<price_type>(price)/10000);
            break;
        case 'F':
            readBytesIntoMessage(39);
            timeStamp = parse_ts(message+4);
            orderId = parse_uint64(message+10);
            direction = message[18];
            size = parse_uint32(message+19);
            strncpy(ticker, message+23, 8); ticker[8] = 0;
            price = parse_uint32(message+31);
            // if(debug){
            //    locateCode = parse_uint16(message);
            //    trackingNumb = parse_uint16(message+2);
            strncpy(mpid, message+35, 4); mpid[4] = 0;
            //     sprintf(str,"%c,%" PRIu16 ",%" PRIu16 ",%" PRIu64 ",%" PRIu64 ",%c,%" PRIu32 ",%s,%" PRIu32 ".%04" PRIu32 ",%s\n",
            //     key,locateCode,trackingNumb,timeStamp,orderId,
            //     direction,size,ticker,
            //     price/10000,price%10000,mpid);
            // }
            msg.setType(key);
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(orderId));
            msg.setSide(static_cast<side_type>(direction == 'S'));
            msg.setRemSize(static_cast<size_type>(size));
            msg.setPrice(static_cast<price_type>(price)/10000);
            msg.setMPID(*mpid);
            break;
        case 'E':
            readBytesIntoMessage(30);
            timeStamp = parse_ts(message+4);
            orderId = parse_uint64(message+10);
            execSize = parse_uint32(message+18);
            // if(debug){
            //    locateCode = parse_uint16(message);
            //    trackingNumb = parse_uint16(message+2);
            //     matchNumber = parse_uint64(message+22);
            //     sprintf(str,"%c,%" PRIu16 ",%" PRIu16 ",%" PRIu64 ",%" PRIu64 ",%" PRIu32 ",%" PRIu64 "\n",
            //     key,locateCode,trackingNumb,timeStamp,orderId,
            //     execSize,matchNumber);
            // }
            msg.setType(key);
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(orderId));
            msg.setExecSize(static_cast<size_type>(execSize));
            break;
        case 'C':
            readBytesIntoMessage(35);
            timeStamp = parse_ts(message+4);
            orderId = parse_uint64(message+10);
            execSize = parse_uint32(message+18);
            price = parse_uint32(message+31);
            // if(debug){
            //    locateCode = parse_uint16(message);
            //    trackingNumb = parse_uint16(message+2);
            //     matchNumber = parse_uint64(message+22);
            //     printable = message[30];
            //     sprintf(str,"%c,%" PRIu16 ",%" PRIu16 ",%" PRIu64 ",%" PRIu64 ",%" PRIu32 ",%" PRIu64 ",%c,%" PRIu32 ".%04" PRIu32 "\n",
            //     key,locateCode,trackingNumb,timeStamp,orderId,
            //     execSize,matchNumber,printable,
            //     price/10000,price%10000);
            // }
            msg.setType(key);
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(orderId));
            msg.setExecSize(static_cast<size_type>(execSize));
            msg.setPrice(static_cast<price_type>(price)/10000);
            break;
        case 'X':
            readBytesIntoMessage(22);
            timeStamp = parse_ts(message+4);
            orderId = parse_uint64(message+10);
            cancSize = parse_uint32(message+18);
            // if(debug){
            //    locateCode = parse_uint16(message);
            //    trackingNumb = parse_uint16(message+2);
            //     sprintf(str,"%c,%" PRIu16 ",%" PRIu16 ",%" PRIu64 ",%" PRIu64 ",%" PRIu32 "\n",
            //     key,locateCode,trackingNumb,timeStamp,orderId,cancSize);
            // }
            msg.setType(key);
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(orderId));
            msg.setCancSize(static_cast<size_type>(cancSize));
            break;
        case 'D':
            readBytesIntoMessage(18);
            timeStamp = parse_ts(message+4);
            orderId = parse_uint64(message+10);
            // if(debug){
            //    locateCode = parse_uint16(message);
            //    trackingNumb = parse_uint16(message+2);
            //     sprintf(str,"%c,%" PRIu16 ",%" PRIu16 ",%" PRIu64 ",%" PRIu64 "\n",
            //     key,locateCode,trackingNumb,timeStamp,orderId);
            // }
            msg.setType(key);
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(orderId));
            break;
        case 'U':
            readBytesIntoMessage(34);
            timeStamp = parse_ts(message+4);
            oldOrderId = parse_uint64(message+10);
            newOrderId = parse_uint64(message+18);
            newSize = parse_uint32(message+26);
            newPrice = parse_uint32(message+30);
            // if(debug){
            //    locateCode = parse_uint16(message);
            //    trackingNumb = parse_uint16(message+2);
            //     sprintf(str,"%c,%" PRIu16 ",%" PRIu16 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%" PRIu32 ",%" PRIu32 ".%04" PRIu32 "\n",
            //     key,locateCode,trackingNumb,timeStamp,oldOrderId,
            //     newOrderId,newSize,newPrice/10000,newPrice%10000);
            // }
            msg.setType(key);
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(newOrderId));
            msg.setOldId(static_cast<id_type>(oldOrderId));
            msg.setRemSize(static_cast<size_type>(newSize));
            msg.setPrice(static_cast<price_type>(newPrice)/10000);
            break;
        case 'P':
            readBytesIntoMessage(43);
            timeStamp = parse_ts(message+4);
            orderId = parse_uint64(message+10);
            direction = message[18];
            size = parse_uint32(message+19);
            strncpy(ticker, message+23, 8); ticker[8] = 0;
            price = parse_uint32(message+31);
            // if(debug){
            //    locateCode = parse_uint16(message);
            //    trackingNumb = parse_uint16(message+2);
            //    matchId = parse_uint64(message+35);
            //     sprintf(str,"%c,%" PRIu16 ",%" PRIu16 ",%" PRIu64 ",%" PRIu64 ",%c,%" PRIu32 ",%s,%" PRIu32 ".%04" PRIu32 ",%" PRIu64 "\n",
            //     key,locateCode,trackingNumb,timeStamp,orderId,
            //     direction,size,ticker,price/10000,price%10000,matchId);
            // }
            msg.setType(key);
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(orderId));
            msg.setSide(static_cast<side_type>(direction == 'S'));
            msg.setExecSize(static_cast<size_type>(size));
            msg.setPrice(static_cast<price_type>(price)/10000);
            break;
        case 'Q':
            readBytesIntoMessage(39);
            break;
        case 'B':
            readBytesIntoMessage(18);
            break;
        case 'I':
            readBytesIntoMessage(49);
            break;
        case 'N':
            readBytesIntoMessage(19);
            break;
        default:
            if (!eof()) {
                std::cerr << "Type " << key << " not found: abort" << std::endl;
                validFile = false;
            }
            break;
    }
//     if(debug){
//         parserWriter.writeLine(std::string(str));
//     }

//    if (key == 'D')
//    {
//        std::cerr << "Type " << key << " found" << std::endl;
//    }

//    // Skip Bytes
//    if (key != 'T' && key != 'z')
//        skipBytes(22);


    if (strcmp(ticker, stock.c_str()) != 0) {
        return {};
    }
    return msg;
}

bool Reader::eof(){
    return file.eof();
}

bool Reader::isValid() const{
    return validFile;
}

std::string Reader::getFileName() const{
    return fileName;
}

std::string Reader::getStock() const{
    return stock;
}

void Reader::setMessage(const char* str){
    memcpy(message, str, 64);
}

Reader::~Reader(){
    if (file.is_open()){
        file.close();
        std::cout << "File " << fileName << " has been closed" << std::endl;
        std::cout << "Finished, processed " << count << " messages in " << difftime(time(0),start) << "seconds."  << std::endl;
    }
}
