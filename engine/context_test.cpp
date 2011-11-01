// Copyright 2011 Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
// * Neither the name of Google Inc. nor the names of its contributors
//   may be used to endorse or promote products derived from this software
//   without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <map>
#include <string>

#include <atf-c++.hpp>

#include "engine/context.hpp"
#include "utils/env.hpp"
#include "utils/fs/operations.hpp"
#include "utils/fs/path.hpp"

namespace fs = utils::fs;


ATF_TEST_CASE_WITHOUT_HEAD(ctor_and_getters);
ATF_TEST_CASE_BODY(ctor_and_getters)
{
    std::map< std::string, std::string > env;
    env["foo"] = "first";
    env["bar"] = "second";
    const engine::context context(fs::path("/foo/bar"), env);
    ATF_REQUIRE_EQ(fs::path("/foo/bar"), context.cwd());
    ATF_REQUIRE(env == context.env());
}


ATF_TEST_CASE_WITHOUT_HEAD(current);
ATF_TEST_CASE_BODY(current)
{
    const engine::context context = engine::context::current();
    ATF_REQUIRE_EQ(fs::current_path(), context.cwd());
    ATF_REQUIRE(utils::getallenv() == context.env());
}


ATF_TEST_CASE_WITHOUT_HEAD(unique_address);
ATF_TEST_CASE_BODY(unique_address)
{
    std::map< std::string, std::string > env;
    env["foo"] = "first";
    const engine::context context1(fs::path("/foo/bar"), env);
    {
        const engine::context context2 = context1;
        const engine::context context3(fs::path("/foo/bar"), env);
        ATF_REQUIRE(context1.unique_address() == context2.unique_address());
        ATF_REQUIRE(context1.unique_address() != context3.unique_address());
        ATF_REQUIRE(context2.unique_address() != context3.unique_address());
    }
    ATF_REQUIRE(context1.unique_address() == context1.unique_address());
}


ATF_INIT_TEST_CASES(tcs)
{
    ATF_ADD_TEST_CASE(tcs, ctor_and_getters);
    ATF_ADD_TEST_CASE(tcs, current);
    ATF_ADD_TEST_CASE(tcs, unique_address);
}
