// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

// This unit test belongs in gutil, but it depends on test_main which is
// part of util.
#include "kudu/gutil/map-util.h"

#include <gtest/gtest.h>
#include <map>
#include <memory>

using std::map;
using std::string;
using std::unique_ptr;

namespace kudu {

TEST(FloorTest, TestMapUtil) {
  map<int, int> my_map;

  ASSERT_EQ(nullptr, FindFloorOrNull(my_map, 5));

  my_map[5] = 5;
  ASSERT_EQ(5, *FindFloorOrNull(my_map, 6));
  ASSERT_EQ(5, *FindFloorOrNull(my_map, 5));
  ASSERT_EQ(nullptr, FindFloorOrNull(my_map, 4));

  my_map[1] = 1;
  ASSERT_EQ(5, *FindFloorOrNull(my_map, 6));
  ASSERT_EQ(5, *FindFloorOrNull(my_map, 5));
  ASSERT_EQ(1, *FindFloorOrNull(my_map, 4));
  ASSERT_EQ(1, *FindFloorOrNull(my_map, 1));
  ASSERT_EQ(nullptr, FindFloorOrNull(my_map, 0));
}

TEST(ComputeIfAbsentTest, TestComputeIfAbsent) {
  map<string, string> my_map;
  auto result = ComputeIfAbsent(&my_map, "key", []{ return "hello_world"; });
  ASSERT_EQ(*result, "hello_world");
  auto result2 = ComputeIfAbsent(&my_map, "key", [] { return "hello_world2"; });
  ASSERT_EQ(*result2, "hello_world");
}

TEST(ComputeIfAbsentTest, TestComputeIfAbsentAndReturnAbsense) {
  map<string, string> my_map;
  auto result = ComputeIfAbsentReturnAbsense(&my_map, "key", []{ return "hello_world"; });
  ASSERT_TRUE(result.second);
  ASSERT_EQ(*result.first, "hello_world");
  auto result2 = ComputeIfAbsentReturnAbsense(&my_map, "key", [] { return "hello_world2"; });
  ASSERT_FALSE(result2.second);
  ASSERT_EQ(*result2.first, "hello_world");
}

} // namespace kudu