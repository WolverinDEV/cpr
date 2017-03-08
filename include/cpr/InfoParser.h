#ifndef CPR_INFOPARSER_H
#define CPR_INFOPARSER_H

#include <curl/curl.h>

namespace cpr {
    typedef void (*InfoReaderFn) (CURL* curl);
    class InfoReader {
    public:
        explicit InfoReader(){}
        InfoReader(InfoReaderFn function) : func(function){ }

        virtual void parseInfo(CURL* curl){
            if(func) func(curl);
        }
    private:
        InfoReaderFn func = nullptr;
    };

} // namespace cpr

#endif //CPR_INFOPARSER_H
