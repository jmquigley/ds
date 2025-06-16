#pragma once

#include <string>

namespace ds {

char *dtrim(char *);
std::string moveBufferToString(const char *, ssize_t);
char *removeCRLF(char *);
char *removeIt(char *, const char *);
char *replaceIt(char *, char, char);
bool safecopy(char *dst, ssize_t dstSize, const char *src, ssize_t srcSize);
int tokenSplit(char *, const char *, char **, int);
char *upperCase(char *);

}  // namespace ds
