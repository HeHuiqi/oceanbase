/**
 * (C) 2010-2012 Alibaba Group Holding Limited.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * Version: $Id$
 *
 * ob_file_table_test.cpp
 *
 * Authors:
 *   Junquan Chen <jianming.cjq@taobao.com>
 *
 */

#include <gtest/gtest.h>
#include "ob_file_table.h"
#include "common/utility.h"
#include "common/ob_row.h"

using namespace oceanbase::sql;
using namespace oceanbase::sql::test;
using namespace oceanbase::common;

#define OK(value) ASSERT_EQ(OB_SUCCESS, (value))


TEST(ObFileTableTest, basic_test)
{
  ObFileTable table("test_cases/ob_file_table.ini");
  OK(table.open());

  const ObRow *row = NULL;
  uint64_t table_id = 0;
  uint64_t column_id = 0;
  const ObObj *value = NULL;

  bool is_add = false;
  int64_t int_value = 0;
  ObString str_value;

  int64_t column1[] = {34, 52, 32};
  bool add1[] = {false, true, false};

  char *column2[] = {(char*)"chenjunquan", (char*)"hello", (char*)"guorui"};

  int64_t column3[] = {32, 2, 323};
  bool add3[] = {false, true, false};

  char *column4[] = {(char*)"jianming", (char*)"chen",(char*)"chengyu"};

  for(int i=0;i<3;i++)
  {
    OK(table.get_next_row(row));
    OK(row->raw_get_cell(0, value, table_id, column_id));
    OK(value->get_int(int_value, is_add));
    ASSERT_EQ(int_value, column1[i]);
    ASSERT_EQ(is_add, add1[i]);

    OK(row->raw_get_cell(1, value, table_id, column_id));
    OK(value->get_varchar(str_value));
    ASSERT_EQ(0, strncmp(column2[i], str_value.ptr(), str_value.length()));

    OK(row->raw_get_cell(2, value, table_id, column_id));
    OK(value->get_int(int_value, is_add));
    ASSERT_EQ(int_value, column3[i]);
    ASSERT_EQ(is_add, add3[i]);

    OK(row->raw_get_cell(3, value, table_id, column_id));
    OK(value->get_varchar(str_value));
    ASSERT_EQ(0, strncmp(column4[i], str_value.ptr(), str_value.length()));
  }
  
  OK(table.close());
}

int main(int argc, char **argv)
{
  ob_init_memory_pool();
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}

