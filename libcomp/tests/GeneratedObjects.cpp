/**
 * @file libcomp/tests/GeneratedObjects.cpp
 * @ingroup libcomp
 *
 * @author COMP Omega <compomega@tutanota.com>
 *
 * @brief Test some objects generated by objgen.
 *
 * This file is part of the COMP_hack Library (libcomp).
 *
 * Copyright (C) 2016-2020 COMP_hack Team <compomega@tutanota.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <PushIgnore.h>
#include <gtest/gtest.h>
#include <PopIgnore.h>

#include <TestObject.h>

using namespace libcomp;
using namespace objects;

void WriteMapU16Char(char* map, uint16_t idx, char val)
{
    uint32_t stringLength = 1;

    size_t offset1 = sizeof(idx);
    size_t offset2 = offset1 + sizeof(stringLength);

    memcpy(map, &idx, sizeof(idx));
    memcpy(map + offset1, &stringLength, sizeof(stringLength));
    memcpy(map + offset2, &val, sizeof(val));
}

TEST(Object, TestObject)
{
    TestObject data;

    //
    // Boolean
    //
    EXPECT_EQ(true, data.GetBoolean());
    EXPECT_TRUE(data.SetBoolean(false));

    //
    // Unsigned 8-bit
    //
    EXPECT_EQ(42, data.GetUnsigned8());

    // Attempt to set below the minimum.
    EXPECT_FALSE(data.SetUnsigned8(0));
    EXPECT_EQ(42, data.GetUnsigned8());

    // Attempt to set above the maximum.
    EXPECT_FALSE(data.SetUnsigned8(136));
    EXPECT_EQ(42, data.GetUnsigned8());

    // Attempt to set a valid value.
    EXPECT_TRUE(data.SetUnsigned8(135));
    EXPECT_EQ(135, data.GetUnsigned8());

    //
    // Signed 8-bit
    //
    EXPECT_EQ(0, data.GetSigned8());

    // Attempt to set below the minimum.
    EXPECT_FALSE(data.SetSigned8(-120));
    EXPECT_EQ(0, data.GetSigned8());

    // Attempt to set above the maximum.
    EXPECT_FALSE(data.SetSigned8(125));
    EXPECT_EQ(0, data.GetSigned8());

    // Attempt to set a valid value.
    EXPECT_TRUE(data.SetSigned8(-15));
    EXPECT_EQ(-15, data.GetSigned8());

    //
    // Unsigned 16-bit
    //
    EXPECT_EQ(1337, data.GetUINT16());

    // Attempt to set a valid value.
    EXPECT_TRUE(data.SetUINT16(12345));
    EXPECT_EQ(12345, data.GetUINT16());

    //
    // Signed 32-bit
    //
    EXPECT_EQ(90210, data.GetSigned32());

    //
    // String (CP932, set length)
    //
    EXPECT_EQ("日本語", data.GetStringCP932());

    // Attempt to set a value that is too long.
    EXPECT_FALSE(data.SetStringCP932("日本人は大好きです！"));
    EXPECT_EQ("日本語", data.GetStringCP932());

    // Attempt to set an invalid value.
    EXPECT_FALSE(data.SetStringCP932("日曜日"));
    EXPECT_EQ("日本語", data.GetStringCP932());

    // Attempt to set a valid value.
    EXPECT_TRUE(data.SetStringCP932("日本人"));
    EXPECT_EQ("日本人", data.GetStringCP932());

    //
    // String (null-terminated)
    //
    EXPECT_EQ("", data.GetStringNull());

    std::string nullTerminatedString = "NotANull!!!";

    // Attempt to set a valid value.
    EXPECT_TRUE(data.SetStringNull(nullTerminatedString));
    EXPECT_EQ(nullTerminatedString, data.GetStringNull());

    //
    // String (fixed length)
    //
    EXPECT_EQ("", data.GetStringFixed());

    std::string fixedLengthString = "FixedLengthStrng";

    // Attempt to set a valid value.
    EXPECT_TRUE(data.SetStringFixed(fixedLengthString));
    EXPECT_EQ(fixedLengthString, data.GetStringFixed());

    //
    // Array
    //
    std::array<float, 3> arrayValues = data.GetXYZ();
    EXPECT_EQ(-3.14159e2f, arrayValues[0]);
    EXPECT_EQ(-3.14159e2f, arrayValues[1]);
    EXPECT_EQ(-3.14159e2f, arrayValues[2]);

    // Try to get a value out of the range.
    EXPECT_EQ(0, data.GetXYZ(10));

    // Try to set some elements with wrong values.
    EXPECT_FALSE(data.SetXYZ(10, 123));
    EXPECT_FALSE(data.SetXYZ(0, -90210));
    EXPECT_FALSE(data.SetXYZ(2, 90210));

    // Try to set some valid values.
    EXPECT_TRUE(data.SetXYZ(0, -0.5f));
    EXPECT_TRUE(data.SetXYZ(1, 1.5f));
    EXPECT_TRUE(data.SetXYZ(2, 3.14159f));

    //
    // List of int8_t
    //
    EXPECT_EQ(0, data.GetList().size());

    // Attempt to set some valid values.
    EXPECT_TRUE(data.AppendList(3));
    EXPECT_TRUE(data.PrependList(1));
    EXPECT_TRUE(data.InsertList(1, 2));
    EXPECT_TRUE(data.AppendList(4));

    EXPECT_EQ(4, data.ListCount());
    EXPECT_EQ(1, data.GetList(0));
    EXPECT_EQ(2, data.GetList(1));
    EXPECT_EQ(3, data.GetList(2));
    EXPECT_EQ(4, data.GetList(3));

    auto listIter = data.ListBegin();
    EXPECT_EQ(1, *listIter);

    int elementCount = 0;
    while(listIter != data.ListEnd())
    {
        elementCount++;
        listIter++;
    }
    EXPECT_EQ(4, elementCount);

    //
    // Map of int16_t and string
    //
    EXPECT_EQ(0, data.GetMap().size());

    // Attempt to set some valid values.
    EXPECT_TRUE(data.SetMap(1, "1"));
    EXPECT_TRUE(data.SetMap(2, "2"));
    EXPECT_TRUE(data.SetMap(3, "3"));
    EXPECT_TRUE(data.SetMap(4, "4"));

    EXPECT_EQ(4, data.MapCount());
    EXPECT_TRUE(data.MapKeyExists(2));
    EXPECT_EQ("2", data.GetMap(2));

    elementCount = 0;
    auto mapIter = data.MapBegin();
    //The underlying map is unordered
    //EXPECT_EQ(1, mapIter->first);
    while(mapIter != data.MapEnd())
    {
        elementCount++;
        mapIter++;
    }
    EXPECT_EQ(4, elementCount);

    //
    // Enum
    //
    EXPECT_EQ(TestObject::EnumYN_t::YES, data.GetEnumYN());

    // Attempt to set an invalid value (commented out for GCC build)
    //auto invalidEnum = (TestObject::EnumYN_t)-1;
    //EXPECT_FALSE(data.SetEnumYN(invalidEnum));

    // Attempt to set a valid value
    EXPECT_TRUE(data.SetEnumYN(TestObject::EnumYN_t::NO));

    std::stringstream streamOutStream(std::stringstream::out |
        std::stringstream::binary);
    libcomp::ObjectOutStream streamOut(streamOutStream);

    EXPECT_TRUE(data.Save(streamOut));

    std::string stringData = streamOutStream.str();

    struct
    {
        uint8_t Unsigned8;
        int8_t Signed8;
        uint16_t UINT16;
        int32_t Signed32;
        char stringCP932[16];
        char stringNull[12] = { 0 };        //11 + null
        uint32_t stringFixedLength = 16;
        char stringFixed[16];
        float XYZ[3];
        char listContents[4];              //uint8_t x 4
        char mapContents[28];              //(uint16_t[2] + string length[4] + 1 char) x 4
        TestObject::EnumYN_t enumYesNo = TestObject::EnumYN_t::NO;
        bool Boolean = false;
    } testData;

    testData.Unsigned8 = 135;
    testData.Signed8 = -15;
    testData.UINT16 = 12345;
    testData.Signed32 = 90210;
    testData.XYZ[0] = -0.5f;
    testData.XYZ[1] = 1.5f;
    testData.XYZ[2] = 3.14159f;

    size_t len = data.GetStringNull().Length();
    strncpy(testData.stringNull, data.GetStringNull().C(), len);
    len = data.GetStringFixed().Length();
    strncpy(testData.stringFixed, data.GetStringFixed().C(), len);

    testData.listContents[0] = 1;
    testData.listContents[1] = 2;
    testData.listContents[2] = 3;
    testData.listContents[3] = 4;

    //Make sure to use an iterator here since the order can change per implementation
    mapIter = data.MapBegin();
    WriteMapU16Char(&testData.mapContents[0], mapIter->first, mapIter->second.ToUtf8()[0]);
    mapIter++;
    WriteMapU16Char(&testData.mapContents[7], mapIter->first, mapIter->second.ToUtf8()[0]);
    mapIter++;
    WriteMapU16Char(&testData.mapContents[14], mapIter->first, mapIter->second.ToUtf8()[0]);
    mapIter++;
    WriteMapU16Char(&testData.mapContents[21], mapIter->first, mapIter->second.ToUtf8()[0]);

    memset(testData.stringCP932, 0, sizeof(testData.stringCP932));
    std::vector<char> strA = libcomp::Convert::ToEncoding(
        libcomp::Convert::ENCODING_CP932, "日本人");
    memcpy(testData.stringCP932, &strA[0], 15 < strA.size() ? 15 : strA.size());
    //strncpy(testData.string, "日本人", 15);

    //bool offsets it since size can only increase by increments of 4
    size_t testDataSize = (size_t)sizeof(testData) - 3;
    EXPECT_EQ(testDataSize, stringData.size())
        << "Check the object save data size against the test data structure size.";
    EXPECT_EQ(0, memcmp(&testData, stringData.c_str(), testDataSize))
        << "Check the object save data against the test data.";

    testData.Boolean = true;
    testData.Unsigned8 = 23;
    testData.Signed8 = -77;
    testData.UINT16 = 32814;
    testData.Signed32 = -19842016;

    memset(testData.stringCP932, 0, sizeof(testData.stringCP932));
    std::vector<char> strB = libcomp::Convert::ToEncoding(
        libcomp::Convert::ENCODING_CP932, "日本一");
    memcpy(testData.stringCP932, &strB[0], 15 < strB.size() ? 15 : strB.size());
    //strncpy(testData.string, "日本一", 15);

    memset(testData.stringNull, 0, sizeof(testData.stringNull));
    const char* nullStr = "MaybeANull?";
    memcpy(testData.stringNull, nullStr, sizeof(testData.stringNull));

    memset(testData.stringFixed, 0, sizeof(testData.stringFixed));
    const char* fixedStr = "LengthIsFixedNow";
    memcpy(testData.stringFixed, fixedStr, sizeof(testData.stringFixed));

    testData.listContents[0] = 5;
    testData.listContents[1] = 6;
    testData.listContents[2] = 7;
    testData.listContents[3] = 8;

    WriteMapU16Char(&testData.mapContents[0], 5, '5');
    WriteMapU16Char(&testData.mapContents[7], 6, '6');
    WriteMapU16Char(&testData.mapContents[14], 7, '7');
    WriteMapU16Char(&testData.mapContents[21], 8, '8');

    testData.enumYesNo = TestObject::EnumYN_t::YES;

    std::stringstream streamInStream(std::stringstream::in |
        std::stringstream::binary);
    libcomp::ObjectInStream streamIn(streamInStream);
    streamIn.dynamicSizes = streamOut.dynamicSizes;

    streamInStream.str(std::string(reinterpret_cast<char*>(&testData),
        reinterpret_cast<char*>(&testData) + sizeof(testData)));

    EXPECT_TRUE(data.Load(streamIn)) << "Loading from instream";

    EXPECT_EQ(true, data.GetBoolean());
    EXPECT_EQ(23, data.GetUnsigned8());
    EXPECT_EQ(-77, data.GetSigned8());
    EXPECT_EQ(32814, data.GetUINT16());
    EXPECT_EQ(-19842016, data.GetSigned32());
    EXPECT_EQ("日本一", data.GetStringCP932());
    EXPECT_EQ("MaybeANull?", data.GetStringNull());
    EXPECT_EQ("LengthIsFixedNow", data.GetStringFixed());

    EXPECT_EQ(3, data.GetXYZ().size());
    EXPECT_EQ(-0.5f, data.GetXYZ(0));
    EXPECT_EQ(1.5f, data.GetXYZ(1));
    EXPECT_EQ(3.14159f, data.GetXYZ(2));

    EXPECT_EQ(4, data.ListCount());
    EXPECT_EQ(5, data.GetList(0));
    EXPECT_EQ(6, data.GetList(1));
    EXPECT_EQ(7, data.GetList(2));
    EXPECT_EQ(8, data.GetList(3));
    data.ClearList();
    EXPECT_EQ(0, data.ListCount()) << "Verifying List cleared";

    EXPECT_EQ(4, data.MapCount());
    EXPECT_EQ("5", data.GetMap(5));
    EXPECT_EQ("6", data.GetMap(6));
    EXPECT_EQ("7", data.GetMap(7));
    EXPECT_EQ("8", data.GetMap(8));
    data.ClearMap();
    EXPECT_EQ(0, data.MapCount()) << "Verifying Map cleared";

    EXPECT_EQ(TestObject::EnumYN_t::YES, data.GetEnumYN());
}

int main(int argc, char *argv[])
{
    try
    {
        ::testing::InitGoogleTest(&argc, argv);

        return RUN_ALL_TESTS();
    }
    catch(...)
    {
        return EXIT_FAILURE;
    }
}
