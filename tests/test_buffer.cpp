#include <test_buffer.h>

#include <cstddef>
#include <ds/Buffer.hpp>
#include <ds/constants.hpp>
#include <string>
#include <vector>

TestBuffer::TestBuffer() {};

TEST_F(TestBuffer, BufferCreation) {
	ds::Buffer buffer;

	EXPECT_EQ(buffer.getBlockSize(), constants::READBUFSIZE);
	EXPECT_EQ(buffer.getCapacity(), constants::READBUFSIZE);
	EXPECT_EQ(buffer.getSize(), 0);
};

TEST_F(TestBuffer, BufferStringFunction) {
	const char *s = "ABCDEF";
	size_t len = 6;

	ds::Buffer buffer(s, len, 8);

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 8);
	EXPECT_EQ(buffer.getSize(), len);
	EXPECT_EQ(buffer.str(), s);
}

TEST_F(TestBuffer, BufferStringFunctionEmpty) {
	const char *s = "";
	size_t len = 0;

	ds::Buffer buffer(s, len, 8);

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 8);
	EXPECT_EQ(buffer.getSize(), len);
	EXPECT_EQ(buffer.str(), s);
}

TEST_F(TestBuffer, BufferCreationWithString) {
	const char *s = "test string";
	size_t len = 11;

	ds::Buffer buffer(s, len);

	EXPECT_EQ(buffer.getBlockSize(), constants::READBUFSIZE);
	EXPECT_EQ(buffer.getCapacity(), constants::READBUFSIZE);
	EXPECT_EQ(buffer.getSize(), len);
	EXPECT_EQ(buffer.str(), s);
}

TEST_F(TestBuffer, BufferCreationWithExpand) {
	const char *s = "test string";
	size_t len = 11;

	ds::Buffer buffer(s, len, 8);

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 16);
	EXPECT_EQ(buffer.getSize(), len);
	EXPECT_EQ(buffer.str(), s);
}

TEST_F(TestBuffer, BufferCreationWithStringExpand) {
	std::string s("test string");
	size_t len = 11;

	ds::Buffer buffer(s, 8);

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 16);
	EXPECT_EQ(buffer.getSize(), len);
	EXPECT_EQ(buffer.str(), s);
}

TEST_F(TestBuffer, BufferMultipleAppend) {
	const char *s = "test string";
	size_t len = 11;

	ds::Buffer buffer(s, len, 8);

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 16);
	EXPECT_EQ(buffer.getSize(), len);
	EXPECT_EQ(buffer.str(), s);

	buffer.append("A", 1);
	EXPECT_EQ(buffer.str(), "test stringA");
	EXPECT_EQ(buffer.getSize(), 12);
	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 16);

	buffer.append("BCDE", 4);
	EXPECT_EQ(buffer.str(), "test stringABCDE");
	EXPECT_EQ(buffer.getSize(), 16);
	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 16);

	buffer.append("F", 1);
	EXPECT_EQ(buffer.str(), "test stringABCDEF");
	EXPECT_EQ(buffer.getSize(), 17);
	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 24);
}

TEST_F(TestBuffer, BufferMultipleOperatorAppend) {
	ds::Buffer buffer("", 0, 8);

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 8);
	EXPECT_EQ(buffer.getSize(), 0);
	EXPECT_EQ(buffer.str(), "");

	buffer += "A";

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 8);
	EXPECT_EQ(buffer.getSize(), 1);
	EXPECT_EQ(buffer.str(), "A");

	buffer << "B";

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 8);
	EXPECT_EQ(buffer.getSize(), 2);
	EXPECT_EQ(buffer.str(), "AB");

	buffer += std::string("C");

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 8);
	EXPECT_EQ(buffer.getSize(), 3);
	EXPECT_EQ(buffer.str(), "ABC");

	buffer << std::string("D");

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 8);
	EXPECT_EQ(buffer.getSize(), 4);
	EXPECT_EQ(buffer.str(), "ABCD");
}

TEST_F(TestBuffer, ChangingBlockSize) {
	const char *s = "test string";
	size_t len = 11;

	ds::Buffer buffer(s, len, 8);

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 16);
	EXPECT_EQ(buffer.getSize(), len);
	EXPECT_EQ(buffer.str(), s);

	buffer.setBlockSize(16);
	buffer.append("ABCDEF", 6);
	EXPECT_EQ(buffer.str(), "test stringABCDEF");
	EXPECT_EQ(buffer.getSize(), 17);
	EXPECT_EQ(buffer.getBlockSize(), 16);
	EXPECT_EQ(buffer.getCapacity(), 32);

	buffer.setBlockSize(8);
	for (int i = 0; i < 16; i++) {
		buffer.append("Z", 1);
	}

	EXPECT_EQ(buffer.str(), "test stringABCDEFZZZZZZZZZZZZZZZZ");
	EXPECT_EQ(buffer.getSize(), 33);
	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 40);
}

TEST_F(TestBuffer, BufferClear) {
	const char *s = "test string";
	size_t len = 11;

	ds::Buffer buffer(s, len, 8);

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 16);
	EXPECT_EQ(buffer.getSize(), len);
	EXPECT_EQ(buffer.str(), s);

	buffer.clear();

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 16);
	EXPECT_EQ(buffer.getSize(), 0);
	EXPECT_EQ(buffer.str(), "");

	// Shows that the contents are retained even though the size is 0
	EXPECT_EQ(buffer.data()[0], 't');
	EXPECT_EQ(buffer.data()[1], 'e');
	EXPECT_EQ(buffer.data()[2], 's');
	EXPECT_EQ(buffer.data()[3], 't');

	buffer.clear(true, 0);

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 16);
	EXPECT_EQ(buffer.getSize(), 0);
	EXPECT_EQ(buffer.str(), "");

	for (size_t i = 0; i < buffer.getCapacity(); i++) {
		EXPECT_EQ(buffer.data()[0], 0);
	}

	buffer.clear(true, 'z');

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 16);
	EXPECT_EQ(buffer.getSize(), 0);
	EXPECT_EQ(buffer.str(), "");

	for (size_t i = 0; i < buffer.getCapacity(); i++) {
		EXPECT_EQ(buffer.data()[0], 'z');
	}
}

TEST_F(TestBuffer, BufferUnaryOperatorClear) {
	const char *s = "test string";
	size_t len = 11;

	ds::Buffer buffer(s, len, 8);

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 16);
	EXPECT_EQ(buffer.getSize(), len);
	EXPECT_EQ(buffer.str(), s);

	~buffer;

	EXPECT_EQ(buffer.getBlockSize(), 8);
	EXPECT_EQ(buffer.getCapacity(), 16);
	EXPECT_EQ(buffer.getSize(), 0);
	EXPECT_EQ(buffer.str(), "");
}

TEST_F(TestBuffer, BufferAssignmentOperators) {
	ds::Buffer buf1("ABC", 3, 16);
	ds::Buffer buf2("XYZ", 3, 32);

	EXPECT_EQ(buf1.getBlockSize(), 16);
	EXPECT_EQ(buf1.getCapacity(), 16);
	EXPECT_EQ(buf1.getSize(), 3);
	EXPECT_EQ(buf1.str(), "ABC");

	buf1 = "DEF";

	EXPECT_EQ(buf1.getBlockSize(), 16);
	EXPECT_EQ(buf1.getCapacity(), 16);
	EXPECT_EQ(buf1.getSize(), 3);
	EXPECT_EQ(buf1.str(), "DEF");

	buf1 = std::string("GHI");

	EXPECT_EQ(buf1.getBlockSize(), 16);
	EXPECT_EQ(buf1.getCapacity(), 16);
	EXPECT_EQ(buf1.getSize(), 3);
	EXPECT_EQ(buf1.str(), "GHI");

	buf1 = buf2;

	EXPECT_EQ(buf1.getBlockSize(), 32);
	EXPECT_EQ(buf1.getCapacity(), 32);
	EXPECT_EQ(buf1.getSize(), 3);
	EXPECT_EQ(buf1.str(), "XYZ");
}

TEST_F(TestBuffer, BufferCopyConstructor) {
	ds::Buffer buf1("ABC", 3, 16);
	ds::Buffer buf2(buf1);

	EXPECT_EQ(buf1.getBlockSize(), 16);
	EXPECT_EQ(buf1.getCapacity(), 16);
	EXPECT_EQ(buf1.getSize(), 3);
	EXPECT_EQ(buf1.str(), "ABC");

	EXPECT_EQ(buf2.getBlockSize(), 16);
	EXPECT_EQ(buf2.getCapacity(), 16);
	EXPECT_EQ(buf2.getSize(), 3);
	EXPECT_EQ(buf2.str(), "ABC");

	EXPECT_NE(buf1.data(), buf2.data());
}

TEST_F(TestBuffer, BufferAtPos) {
	ds::Buffer buf("ABCDEF", 6, 16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), 6);
	EXPECT_EQ(buf.str(), "ABCDEF");

	EXPECT_EQ(buf.at(0), 'A');
	EXPECT_EQ(buf.at(5), 'F');
}

TEST_F(TestBuffer, BufferAtPosBad) {
	ds::Buffer buf("ABCDEF", 6, 16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), 6);
	EXPECT_EQ(buf.str(), "ABCDEF");

	EXPECT_THROW(buf.at(6), std::out_of_range);
}

TEST_F(TestBuffer, BufferIndexPos) {
	ds::Buffer buf("ABCDEF", 6, 16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), 6);
	EXPECT_EQ(buf.str(), "ABCDEF");

	EXPECT_EQ(buf[0], 'A');
	EXPECT_EQ(buf[5], 'F');
}

TEST_F(TestBuffer, BufferIndexPosBad) {
	ds::Buffer buf("ABCDEF", 6, 16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), 6);
	EXPECT_EQ(buf.str(), "ABCDEF");

	EXPECT_THROW(buf[6], std::out_of_range);
}

TEST_F(TestBuffer, BufferFrontBackPointers) {
	const char *s = "ABCDEF";
	size_t len = strlen(s);
	ds::Buffer buf(s, len, 16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), len);
	EXPECT_EQ(buf.str(), s);

	EXPECT_EQ(*buf.front(), 'A');
	EXPECT_EQ(*buf.back(), 'F');
}

TEST_F(TestBuffer, BufferToVector) {
	const char *s = "ABCDEF";
	size_t len = strlen(s);
	ds::Buffer buf(s, len, 16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), len);
	EXPECT_EQ(buf.str(), s);

	std::vector v = buf.vec();

	EXPECT_EQ(v.size(), 6);
	EXPECT_EQ(v[0], 'A');
	EXPECT_EQ(v[1], 'B');
	EXPECT_EQ(v[2], 'C');
	EXPECT_EQ(v[3], 'D');
	EXPECT_EQ(v[4], 'E');
	EXPECT_EQ(v[5], 'F');
}

TEST_F(TestBuffer, BufferSectionCreation) {
	const char *s = "ABCDEF";
	size_t len = strlen(s);
	ds::Buffer buf(s, len, 16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), len);
	EXPECT_EQ(buf.str(), s);

	std::vector<char> v;
	v = buf.section(1, 3);
	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v[0], 'B');
	EXPECT_EQ(v[1], 'C');
	EXPECT_EQ(v[2], 'D');

	v = buf.section(0, 0);
	EXPECT_EQ(v.size(), 1);
	EXPECT_EQ(v[0], 'A');

	v = buf.section(5, 5);
	EXPECT_EQ(v.size(), 1);
	EXPECT_EQ(v[0], 'F');
}

TEST_F(TestBuffer, BufferSectionBadCreation) {
	const char *s = "ABCDEF";
	size_t len = strlen(s);
	ds::Buffer buf(s, len, 16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), len);
	EXPECT_EQ(buf.str(), s);

	std::vector<char> v;
	EXPECT_THROW(v = buf.section(0, len), std::out_of_range);
	EXPECT_THROW(v = buf.section(len + 1, len + 1), std::out_of_range);
	EXPECT_THROW(v = buf.section(3, len + 1), std::out_of_range);
}

TEST_F(TestBuffer, BufferSectionCreationWithOperator) {
	const char *s = "ABCDEF";
	size_t len = strlen(s);
	ds::Buffer buf(s, len, 16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), len);
	EXPECT_EQ(buf.str(), s);

	std::vector<char> v;
	v = buf(1, 3);
	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v[0], 'B');
	EXPECT_EQ(v[1], 'C');
	EXPECT_EQ(v[2], 'D');

	v = buf(0, 0);
	EXPECT_EQ(v.size(), 1);
	EXPECT_EQ(v[0], 'A');

	v = buf(5, 5);
	EXPECT_EQ(v.size(), 1);
	EXPECT_EQ(v[0], 'F');
}

TEST_F(TestBuffer, BufferEquals) {
	const char *s = "ABCDEF";
	size_t len = strlen(s);
	ds::Buffer buf1(s, len, 16);
	ds::Buffer buf2(s, len, 16);

	EXPECT_EQ(buf1.getBlockSize(), 16);
	EXPECT_EQ(buf1.getCapacity(), 16);
	EXPECT_EQ(buf1.getSize(), len);
	EXPECT_EQ(buf1.str(), s);

	EXPECT_EQ(buf2.getBlockSize(), 16);
	EXPECT_EQ(buf2.getCapacity(), 16);
	EXPECT_EQ(buf2.getSize(), len);
	EXPECT_EQ(buf2.str(), s);

	EXPECT_TRUE(buf1 == buf2);
	buf2.append("G", 1);
	EXPECT_FALSE(buf1 == buf2);
}

TEST_F(TestBuffer, BufferNotEquals) {
	const char *s1 = "ABCDEF";
	const char *s2 = "XYZPDQ";
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);

	ds::Buffer buf1(s1, len1, 16);
	ds::Buffer buf2(s2, len2, 16);

	EXPECT_EQ(buf1.getBlockSize(), 16);
	EXPECT_EQ(buf1.getCapacity(), 16);
	EXPECT_EQ(buf1.getSize(), len1);
	EXPECT_EQ(buf1.str(), s1);

	EXPECT_EQ(buf2.getBlockSize(), 16);
	EXPECT_EQ(buf2.getCapacity(), 16);
	EXPECT_EQ(buf2.getSize(), len2);
	EXPECT_EQ(buf2.str(), s2);

	EXPECT_TRUE(buf1 != buf2);

	buf2.clear();
	buf2.append(s1, len1);

	EXPECT_FALSE(buf1 != buf2);
}

TEST_F(TestBuffer, BufferSizesNoteEqualFailure) {
	const char *s = "ABCDEF";
	size_t len = strlen(s);

	ds::Buffer buf1(s, len, 16);
	ds::Buffer buf2(s, len, 32);

	buf2.append("Z", 1);

	EXPECT_EQ(buf1.getBlockSize(), 16);
	EXPECT_EQ(buf1.getCapacity(), 16);
	EXPECT_EQ(buf1.getSize(), len);
	EXPECT_EQ(buf1.str(), s);

	EXPECT_EQ(buf2.getBlockSize(), 32);
	EXPECT_EQ(buf2.getCapacity(), 32);
	EXPECT_EQ(buf2.getSize(), len + 1);
	EXPECT_EQ(buf2.str(), "ABCDEFZ");

	EXPECT_FALSE(buf1 == buf2);
	EXPECT_TRUE(buf1 != buf2);
}

TEST_F(TestBuffer, BufferFindCharacterString) {
	const char *s = "ABCDEFGHI";
	size_t len = strlen(s);
	ds::Buffer buf(s, len, 16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), len);
	EXPECT_EQ(buf.str(), s);

	const char *ret = buf.find("DEF");
	EXPECT_NE(ret, nullptr);
	EXPECT_EQ(ret[0], 'D');
	EXPECT_EQ(ret[1], 'E');
	EXPECT_EQ(ret[2], 'F');

	ret = buf.find(std::string("BCD"));
	EXPECT_NE(ret, nullptr);
	EXPECT_EQ(ret[0], 'B');
	EXPECT_EQ(ret[1], 'C');
	EXPECT_EQ(ret[2], 'D');
}

TEST_F(TestBuffer, BufferFindOnEmptyBuffer) {
	const char *search = "XxX";
	ds::Buffer buf(16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), 0);
	EXPECT_EQ(buf.str(), "");

	EXPECT_THROW(buf.find(search), std::out_of_range);
}

TEST_F(TestBuffer, BufferFindWithBadSearchString) {
	const char *s = "ABCDEFGHI";
	const char *search = "XXXXXXXXXXXXXXXXXXXX";
	size_t len = strlen(s);
	ds::Buffer buf(s, len, 16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), len);
	EXPECT_EQ(buf.str(), s);

	EXPECT_THROW(buf.find(search), std::out_of_range);
}

TEST_F(TestBuffer, BufferFindWithNullSearch) {
	const char *s = "ABCDEFGHI";
	size_t len = strlen(s);
	ds::Buffer buf(s, len, 16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), len);
	EXPECT_EQ(buf.str(), s);

	const char *ret = buf.find(nullptr);
	EXPECT_EQ(ret, nullptr);
}

TEST_F(TestBuffer, BufferFindWithNotFound) {
	const char *s = "ABCDEFGHI";
	const char *search = "XxX";
	size_t len = strlen(s);
	ds::Buffer buf(s, len, 16);

	EXPECT_EQ(buf.getBlockSize(), 16);
	EXPECT_EQ(buf.getCapacity(), 16);
	EXPECT_EQ(buf.getSize(), len);
	EXPECT_EQ(buf.str(), s);

	const char *ret = buf.find(search);
	EXPECT_EQ(ret, nullptr);
}
