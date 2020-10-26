#include "tags.h"

Tags::Tags(std::string& file, std::string& path, bool read) {
    name = file;
    fullPath = path;
}

QVariant Tags::getTag(int column) const {
    std::vector<QVariant (Tags::*)(void) const> hash {
        &Tags::getName,
        &Tags::getPath
    };
    QVariant res = std::invoke(hash[column], this);

    return res;
}

QVariant Tags::getName() const {
    return name.c_str();
}

QVariant Tags::getPath() const {
    return fullPath.c_str();
}