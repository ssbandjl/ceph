// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2016 SUSE LINUX GmbH
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software
 * Foundation.  See file COPYING.
 *
 */

#include "test/rbd_mirror/test_mock_fixture.h"
#include "test/librbd/mock/MockImageCtx.h"

namespace librbd {

namespace {

struct MockTestImageCtx : public librbd::MockImageCtx {
  MockTestImageCtx(librbd::ImageCtx &image_ctx)
    : librbd::MockImageCtx(image_ctx) {
  }
};

} // anonymous namespace

} // namespace librbd

// template definitions
#include "tools/rbd_mirror/ImageSyncThrottler.cc"

namespace rbd {
namespace mirror {

class TestMockImageSyncThrottler : public TestMockFixture {
public:
  typedef ImageSyncThrottler<librbd::MockTestImageCtx> MockImageSyncThrottler;

};

TEST_F(TestMockImageSyncThrottler, Single_Sync) {
  MockImageSyncThrottler throttler(g_ceph_context);
  C_SaferCond on_start;
  throttler.start_op("ns", "id", &on_start);
  ASSERT_EQ(0, on_start.wait());
  throttler.finish_op("ns", "id");
}

TEST_F(TestMockImageSyncThrottler, Multiple_Syncs) {
  MockImageSyncThrottler throttler(g_ceph_context);
  throttler.set_max_concurrent_syncs(2);

  C_SaferCond on_start1;
  throttler.start_op("ns", "id1", &on_start1);
  C_SaferCond on_start2;
  throttler.start_op("ns", "id2", &on_start2);
  C_SaferCond on_start3;
  throttler.start_op("ns", "id3", &on_start3);
  C_SaferCond on_start4;
  throttler.start_op("ns", "id4", &on_start4);

  ASSERT_EQ(0, on_start2.wait());
  throttler.finish_op("ns", "id2");
  ASSERT_EQ(0, on_start3.wait());
  throttler.finish_op("ns", "id3");
  ASSERT_EQ(0, on_start1.wait());
  throttler.finish_op("ns", "id1");
  ASSERT_EQ(0, on_start4.wait());
  throttler.finish_op("ns", "id4");
}

TEST_F(TestMockImageSyncThrottler, Cancel_Running_Sync) {
  MockImageSyncThrottler throttler(g_ceph_context);
  C_SaferCond on_start;
  throttler.start_op("ns", "id", &on_start);
  ASSERT_EQ(0, on_start.wait());
  ASSERT_FALSE(throttler.cancel_op("ns", "id"));
  throttler.finish_op("ns", "id");
}

TEST_F(TestMockImageSyncThrottler, Cancel_Waiting_Sync) {
  MockImageSyncThrottler throttler(g_ceph_context);
  throttler.set_max_concurrent_syncs(1);

  C_SaferCond on_start1;
  throttler.start_op("ns", "id1", &on_start1);
  C_SaferCond on_start2;
  throttler.start_op("ns", "id2", &on_start2);

  ASSERT_EQ(0, on_start1.wait());
  ASSERT_TRUE(throttler.cancel_op("ns", "id2"));
  ASSERT_EQ(-ECANCELED, on_start2.wait());
  throttler.finish_op("ns", "id1");
}

TEST_F(TestMockImageSyncThrottler, Cancel_Running_Sync_Start_Waiting) {
  MockImageSyncThrottler throttler(g_ceph_context);
  throttler.set_max_concurrent_syncs(1);

  C_SaferCond on_start1;
  throttler.start_op("ns", "id1", &on_start1);
  C_SaferCond on_start2;
  throttler.start_op("ns", "id2", &on_start2);

  ASSERT_EQ(0, on_start1.wait());
  ASSERT_FALSE(throttler.cancel_op("ns", "id1"));
  throttler.finish_op("ns", "id1");
  ASSERT_EQ(0, on_start2.wait());
  throttler.finish_op("ns", "id2");
}

TEST_F(TestMockImageSyncThrottler, Duplicate) {
  MockImageSyncThrottler throttler(g_ceph_context);
  throttler.set_max_concurrent_syncs(1);

  C_SaferCond on_start1;
  throttler.start_op("ns", "id1", &on_start1);
  ASSERT_EQ(0, on_start1.wait());

  C_SaferCond on_start2;
  throttler.start_op("ns", "id1", &on_start2);
  ASSERT_EQ(0, on_start2.wait());

  C_SaferCond on_start3;
  throttler.start_op("ns", "id2", &on_start3);
  C_SaferCond on_start4;
  throttler.start_op("ns", "id2", &on_start4);
  ASSERT_EQ(-ENOENT, on_start3.wait());

  throttler.finish_op("ns", "id1");
  ASSERT_EQ(0, on_start4.wait());
  throttler.finish_op("ns", "id2");
}

TEST_F(TestMockImageSyncThrottler, Duplicate2) {
  MockImageSyncThrottler throttler(g_ceph_context);
  throttler.set_max_concurrent_syncs(2);

  C_SaferCond on_start1;
  throttler.start_op("ns", "id1", &on_start1);
  ASSERT_EQ(0, on_start1.wait());
  C_SaferCond on_start2;
  throttler.start_op("ns", "id2", &on_start2);
  ASSERT_EQ(0, on_start2.wait());

  C_SaferCond on_start3;
  throttler.start_op("ns", "id3", &on_start3);
  C_SaferCond on_start4;
  throttler.start_op("ns", "id3", &on_start4); // dup
  ASSERT_EQ(-ENOENT, on_start3.wait());

  C_SaferCond on_start5;
  throttler.start_op("ns", "id4", &on_start5);

  throttler.finish_op("ns", "id1");
  ASSERT_EQ(0, on_start4.wait());

  throttler.finish_op("ns", "id2");
  ASSERT_EQ(0, on_start5.wait());

  C_SaferCond on_start6;
  throttler.start_op("ns", "id5", &on_start6);

  throttler.finish_op("ns", "id3");
  ASSERT_EQ(0, on_start6.wait());

  throttler.finish_op("ns", "id4");
  throttler.finish_op("ns", "id5");
}

TEST_F(TestMockImageSyncThrottler, Increase_Max_Concurrent_Syncs) {
  MockImageSyncThrottler throttler(g_ceph_context);
  throttler.set_max_concurrent_syncs(2);

  C_SaferCond on_start1;
  throttler.start_op("ns", "id1", &on_start1);
  C_SaferCond on_start2;
  throttler.start_op("ns", "id2", &on_start2);
  C_SaferCond on_start3;
  throttler.start_op("ns", "id3", &on_start3);
  C_SaferCond on_start4;
  throttler.start_op("ns", "id4", &on_start4);
  C_SaferCond on_start5;
  throttler.start_op("ns", "id5", &on_start5);

  ASSERT_EQ(0, on_start1.wait());
  ASSERT_EQ(0, on_start2.wait());

  throttler.set_max_concurrent_syncs(4);

  ASSERT_EQ(0, on_start3.wait());
  ASSERT_EQ(0, on_start4.wait());

  throttler.finish_op("ns", "id4");
  ASSERT_EQ(0, on_start5.wait());

  throttler.finish_op("ns", "id1");
  throttler.finish_op("ns", "id2");
  throttler.finish_op("ns", "id3");
  throttler.finish_op("ns", "id5");
}

TEST_F(TestMockImageSyncThrottler, Decrease_Max_Concurrent_Syncs) {
  MockImageSyncThrottler throttler(g_ceph_context);
  throttler.set_max_concurrent_syncs(4);

  C_SaferCond on_start1;
  throttler.start_op("ns", "id1", &on_start1);
  C_SaferCond on_start2;
  throttler.start_op("ns", "id2", &on_start2);
  C_SaferCond on_start3;
  throttler.start_op("ns", "id3", &on_start3);
  C_SaferCond on_start4;
  throttler.start_op("ns", "id4", &on_start4);
  C_SaferCond on_start5;
  throttler.start_op("ns", "id5", &on_start5);

  ASSERT_EQ(0, on_start1.wait());
  ASSERT_EQ(0, on_start2.wait());
  ASSERT_EQ(0, on_start3.wait());
  ASSERT_EQ(0, on_start4.wait());

  throttler.set_max_concurrent_syncs(2);

  throttler.finish_op("ns", "id1");
  throttler.finish_op("ns", "id2");
  throttler.finish_op("ns", "id3");

  ASSERT_EQ(0, on_start5.wait());

  throttler.finish_op("ns", "id4");
  throttler.finish_op("ns", "id5");
}

TEST_F(TestMockImageSyncThrottler, Drain) {
  MockImageSyncThrottler throttler(g_ceph_context);
  throttler.set_max_concurrent_syncs(1);

  C_SaferCond on_start1;
  throttler.start_op("ns", "id1", &on_start1);
  C_SaferCond on_start2;
  throttler.start_op("ns", "id2", &on_start2);

  ASSERT_EQ(0, on_start1.wait());
  throttler.drain("ns", -ESTALE);
  ASSERT_EQ(-ESTALE, on_start2.wait());
}

} // namespace mirror
} // namespace rbd
