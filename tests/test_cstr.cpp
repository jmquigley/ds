#include <ds/cstr.h>
#include <testing_base.h>

#include <iostream>
#include <string>

class TestStr : public TestingBase {
public:

	TestStr() : TestingBase() {}
};

TEST_F(TestStr, TrimSpaces) {
	const char *inp = "     Test String     ";
	const char *res = "Test String";

	strcpy(temp, inp);

	bufptr = ds::dtrim(temp);
	EXPECT_EQ(std::string(bufptr), res);
};

TEST_F(TestStr, TrimSpacesBadInput) {
	bufptr = ds::dtrim(nullptr);
	EXPECT_EQ(bufptr, nullptr);
}

TEST_F(TestStr, TrimSpacesEmpty) {
	bufptr = ds::dtrim(temp);
	EXPECT_EQ(std::string(bufptr), "");
}

TEST_F(TestStr, StringToUpper) {
	const char *inp = "Test String";
	const char *res = "TEST STRING";

	strcpy(temp, inp);

	bufptr = ds::upperCase(temp);
	EXPECT_EQ(std::string(bufptr), res);
}

TEST_F(TestStr, StringToUpperBadInput) {
	bufptr = ds::upperCase(nullptr);
	EXPECT_EQ(bufptr, nullptr);
}

TEST_F(TestStr, StringToUpperSpacesEmpty) {
	bufptr = ds::upperCase(temp);
	EXPECT_EQ(std::string(bufptr), "");
}

TEST_F(TestStr, RemoveIt) {
	const char *inp = "abcdefghij";
	const char *rem = "bdf";
	const char *rem2 = "abcdefghij";
	const char *res = "aceghij";

	strcpy(temp, inp);

	bufptr = ds::removeIt(temp, rem);
	EXPECT_EQ(std::string(bufptr), res);

	strcpy(temp, inp);

	bufptr = ds::removeIt(temp, rem2);
	EXPECT_EQ(std::string(bufptr), "");
}

TEST_F(TestStr, RemoveItBadInput) {
	const char *inp = "abcdefghij";
	const char *rem = "bdf";

	strcpy(temp, inp);

	bufptr = ds::removeIt(NULL, rem);
	EXPECT_EQ(bufptr, nullptr);

	bufptr = ds::removeIt(temp, NULL);
	EXPECT_EQ(std::string(bufptr), std::string(temp));

	bufptr = ds::removeIt(NULL, NULL);
	EXPECT_EQ(bufptr, nullptr);
}

TEST_F(TestStr, RemoveItSpacesEmpty) {
	bufptr = ds::removeIt(temp, "");
	EXPECT_EQ(std::string(bufptr), "");
}

TEST_F(TestStr, ReplaceIt) {
	const char *inp = "abababab";
	char from = 'a';
	char to = 'b';
	const char *res = "bbbbbbbb";

	strcpy(temp, inp);

	bufptr = ds::replaceIt(temp, from, to);
	EXPECT_EQ(std::string(bufptr), res);
}

TEST_F(TestStr, ReplaceItBadInput) {
	bufptr = ds::replaceIt(nullptr, 'a', 'b');
	EXPECT_EQ(bufptr, nullptr);
}

TEST_F(TestStr, ReplaceItSpacesEmpty) {
	bufptr = ds::replaceIt(temp, 'a', 'b');
	EXPECT_EQ(std::string(bufptr), "");
}

TEST_F(TestStr, RemoveCRLF) {
	const char *inp = "abcd\r\n";
	const char *res = "abcd  ";

	strcpy(temp, inp);

	bufptr = ds::removeCRLF(temp);
	EXPECT_EQ(std::string(bufptr), res);
}

TEST_F(TestStr, RemoveCRLFBadInput) {
	bufptr = ds::removeCRLF(nullptr);
	EXPECT_EQ(bufptr, nullptr);
}

TEST_F(TestStr, RemoveCRLFSpacesEmpty) {
	bufptr = ds::removeCRLF(temp);
	EXPECT_EQ(std::string(bufptr), "");
}

TEST_F(TestStr, TokenSplit) {
	const char *inp = "a|b|c|d";
	const char *delimit = "|";
	char *databuf[4] = {nullptr};
	int databufSize = sizeof(databuf) / sizeof(char *);
	int totalTokens = 0;

	EXPECT_EQ(databufSize, 4);

	strcpy(temp, inp);
	totalTokens = ds::tokenSplit(temp, delimit, databuf, databufSize);

	EXPECT_EQ(totalTokens, databufSize);
	EXPECT_EQ(std::string(databuf[0]), "a");
	EXPECT_EQ(std::string(databuf[1]), "b");
	EXPECT_EQ(std::string(databuf[2]), "c");
	EXPECT_EQ(std::string(databuf[3]), "d");
}

TEST_F(TestStr, TokenSplitBadInput) {
	const char *delimit = "|";
	char *databuf[4] = {nullptr};
	int databufSize = sizeof(databuf) / sizeof(char *);
	int totalTokens = 0;

	EXPECT_EQ(databufSize, 4);

	// bad buffer
	totalTokens = ds::tokenSplit(nullptr, "|", databuf, databufSize);
	EXPECT_EQ(totalTokens, -1);
	EXPECT_EQ(databuf[0], nullptr);
	EXPECT_EQ(databuf[1], nullptr);
	EXPECT_EQ(databuf[2], nullptr);
	EXPECT_EQ(databuf[3], nullptr);

	// bad delimiter
	totalTokens = ds::tokenSplit(temp, nullptr, databuf, databufSize);
	EXPECT_EQ(totalTokens, -1);
	EXPECT_EQ(databuf[0], nullptr);
	EXPECT_EQ(databuf[1], nullptr);
	EXPECT_EQ(databuf[2], nullptr);
	EXPECT_EQ(databuf[3], nullptr);

	// bad data buffer
	totalTokens = ds::tokenSplit(temp, delimit, nullptr, databufSize);
	EXPECT_EQ(totalTokens, -1);
	EXPECT_EQ(databuf[0], nullptr);
	EXPECT_EQ(databuf[1], nullptr);
	EXPECT_EQ(databuf[2], nullptr);
	EXPECT_EQ(databuf[3], nullptr);

	// bad data buffer size
	totalTokens = ds::tokenSplit(temp, delimit, databuf, -1);
	EXPECT_EQ(totalTokens, -1);
	EXPECT_EQ(databuf[0], nullptr);
	EXPECT_EQ(databuf[1], nullptr);
	EXPECT_EQ(databuf[2], nullptr);
	EXPECT_EQ(databuf[3], nullptr);
}

TEST_F(TestStr, TokenSplitSpacesEmpty) {
	char *databuf[4] = {nullptr};
	int databufSize = sizeof(databuf) / sizeof(char *);
	int totalTokens = 0;

	EXPECT_EQ(databufSize, 4);

	totalTokens = ds::tokenSplit(temp, "|", databuf, databufSize);
	EXPECT_EQ(databuf[0], nullptr);
	EXPECT_EQ(databuf[1], nullptr);
	EXPECT_EQ(databuf[2], nullptr);
	EXPECT_EQ(databuf[3], nullptr);
	EXPECT_EQ(totalTokens, 0);
	EXPECT_EQ(std::string(temp), "");
}

TEST_F(TestStr, CopyBufferToString) {
	char buffer[5];
	const char *s = "ABCDE";
	std::string str;

	memcpy(buffer, "ABCDE", 5);	 // not NULL terminated

	str = ds::moveBufferToString(buffer, 5);
	EXPECT_EQ(str, s);
	EXPECT_EQ(str.size(), 5);

	str = ds::moveBufferToString(buffer, 3);
	EXPECT_EQ(str, "ABC");
	EXPECT_EQ(str.size(), 3);
}

TEST_F(TestStr, CopyEmptyBuffer) {
	char buffer[5];
	std::string str;

	str = ds::moveBufferToString(buffer, 0);
	EXPECT_EQ(str, "");

	str = ds::moveBufferToString(buffer, -1);
	EXPECT_EQ(str, "");

	str = ds::moveBufferToString(nullptr, -1);
	EXPECT_EQ(str, "");
}

TEST_F(TestStr, SafeCopy) {
	char buf1[4 + 1];
	const char *s = "ABCDEFGHIJ";
	bool ret = false;

	memset(buf1, 0, sizeof(buf1));
	ret = ds::safecopy(buf1, 4, s, strlen(s));

	EXPECT_TRUE(ret);
	EXPECT_EQ(std::string(buf1), "ABCD");
	EXPECT_EQ(strlen(buf1), 4);
}

TEST_F(TestStr, SafeCopyEmptyBuffer) {
	char buf1[4 + 1];
	const char *s = "ABCDEFGHIJ";
	bool ret = true;

	memset(buf1, 0, sizeof(buf1));

	ret = ds::safecopy(nullptr, 4, s, strlen(s));
	EXPECT_FALSE(ret);

	ret = ds::safecopy(buf1, 0, s, strlen(s));
	EXPECT_FALSE(ret);

	ret = ds::safecopy(buf1, 4, nullptr, strlen(s));
	EXPECT_FALSE(ret);

	ret = ds::safecopy(buf1, 4, s, -1);
	EXPECT_FALSE(ret);

	ret = ds::safecopy(buf1, 4, s, 0);
	EXPECT_TRUE(ret);
	EXPECT_EQ(std::string(buf1), "");
	EXPECT_EQ(strlen(buf1), 0);
}
