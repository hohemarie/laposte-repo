/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apr_file_io.h"
#include "apr_file_info.h"
#include "apr_errno.h"
#include "apr_general.h"
#include "apr_strings.h"
#include "apr_lib.h"
#include "apr_thread_proc.h"
#include "testutil.h"

static void test_mkdir(abts_case *tc, void *data)
{
    apr_status_t rv;
    apr_finfo_t finfo;

    rv = apr_dir_make("data/testdir",
                      APR_FPROT_UREAD | APR_FPROT_UWRITE | APR_FPROT_UEXECUTE,
                      p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_stat(&finfo, "data/testdir", APR_FINFO_TYPE, p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    ABTS_INT_EQUAL(tc, APR_DIR, finfo.filetype);
}

static void test_mkdir_recurs(abts_case *tc, void *data)
{
    apr_status_t rv;
    apr_finfo_t finfo;

    rv = apr_dir_make_recursive("data/one/two/three", 
                                APR_FPROT_UREAD | APR_FPROT_UWRITE | APR_FPROT_UEXECUTE,
                                p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_stat(&finfo, "data/one", APR_FINFO_TYPE, p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    ABTS_INT_EQUAL(tc, APR_DIR, finfo.filetype);

    rv = apr_stat(&finfo, "data/one/two", APR_FINFO_TYPE, p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    ABTS_INT_EQUAL(tc, APR_DIR, finfo.filetype);

    rv = apr_stat(&finfo, "data/one/two/three", APR_FINFO_TYPE, p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    ABTS_INT_EQUAL(tc, APR_DIR, finfo.filetype);
}

struct thread_data
{
    abts_case *tc;
    apr_pool_t *pool;
};

static void *APR_THREAD_FUNC thread_mkdir_func(apr_thread_t *thd, void *data)
{
    struct thread_data *td = data;
    apr_status_t s1, s2, s3, s4, s5;

    s1 = apr_dir_make_recursive("data/prll/one/thwo/three",
                                APR_FPROT_UREAD | APR_FPROT_UWRITE | APR_FPROT_UEXECUTE,
                                td->pool);
    s2 = apr_dir_make_recursive("data/prll/four/five/six/seven/eight",
                                APR_FPROT_UREAD | APR_FPROT_UWRITE | APR_FPROT_UEXECUTE,
                                td->pool);
    s3 = apr_dir_make_recursive("data/prll/nine/ten",
                                APR_FPROT_UREAD | APR_FPROT_UWRITE | APR_FPROT_UEXECUTE,
                                td->pool);
    s4 = apr_dir_make_recursive("data/prll/11/12/13/14/15/16/17/18/19/20",
                                APR_FPROT_UREAD | APR_FPROT_UWRITE | APR_FPROT_UEXECUTE,
                                td->pool);
    s5 = apr_dir_make_recursive("data/fortytwo",
                                APR_FPROT_UREAD | APR_FPROT_UWRITE | APR_FPROT_UEXECUTE,
                                td->pool);

    ABTS_INT_EQUAL(td->tc, APR_SUCCESS, s1);
    ABTS_INT_EQUAL(td->tc, APR_SUCCESS, s2);
    ABTS_INT_EQUAL(td->tc, APR_SUCCESS, s3);
    ABTS_INT_EQUAL(td->tc, APR_SUCCESS, s4);
    ABTS_INT_EQUAL(td->tc, APR_SUCCESS, s5);
    return NULL;
}

static void test_mkdir_recurs_parallel(abts_case *tc, void *data)
{
    struct thread_data td1, td2, td3, td4;
    apr_thread_t *t1, *t2, *t3, *t4;
    apr_status_t s1, s2, s3, s4;

    td1.tc = td2.tc = td3.tc = td4.tc = tc;
    apr_pool_create(&td1.pool, p);
    apr_pool_create(&td2.pool, p);
    apr_pool_create(&td3.pool, p);
    apr_pool_create(&td4.pool, p);

    s1 = apr_thread_create(&t1, NULL, thread_mkdir_func, &td1, td1.pool);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, s1);
    s2 = apr_thread_create(&t2, NULL, thread_mkdir_func, &td2, td2.pool);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, s2);
    s3 = apr_thread_create(&t3, NULL, thread_mkdir_func, &td3, td3.pool);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, s3);
    s4 = apr_thread_create(&t4, NULL, thread_mkdir_func, &td4, td4.pool);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, s4);

    apr_thread_join(&s1, t1);
    apr_thread_join(&s2, t2);
    apr_thread_join(&s3, t3);
    apr_thread_join(&s4, t4);

    ABTS_INT_EQUAL(tc, APR_SUCCESS, s1);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, s2);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, s3);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, s4);
}

static void test_remove(abts_case *tc, void *data)
{
    apr_status_t rv;
    apr_finfo_t finfo;

    rv = apr_dir_remove("data/testdir", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_stat(&finfo, "data/testdir", APR_FINFO_TYPE, p);
    ABTS_INT_EQUAL(tc, 1, APR_STATUS_IS_ENOENT(rv));
}

static void test_removeall_fail(abts_case *tc, void *data)
{
    apr_status_t rv;

    rv = apr_dir_remove("data/one", p);
    ABTS_INT_EQUAL(tc, 1, APR_STATUS_IS_ENOTEMPTY(rv));
}

static void test_removeall(abts_case *tc, void *data)
{
    apr_status_t rv;

    rv = apr_dir_remove("data/one/two/three", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/one/two", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/one", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/one/thwo/three", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/one/thwo", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/one", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/four/five/six/seven/eight", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/four/five/six/seven", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/four/five/six", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/four/five", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/four", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/nine/ten", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/nine", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/11/12/13/14/15/16/17/18/19/20", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/11/12/13/14/15/16/17/18/19", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/11/12/13/14/15/16/17/18", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/11/12/13/14/15/16/17", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/11/12/13/14/15/16", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/11/12/13/14/15", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/11/12/13/14", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/11/12/13", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/11/12", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll/11", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/prll", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("data/fortytwo", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
}

static void test_remove_notthere(abts_case *tc, void *data)
{
    apr_status_t rv;

    rv = apr_dir_remove("data/notthere", p);
    ABTS_INT_EQUAL(tc, 1, APR_STATUS_IS_ENOENT(rv));
}

static void test_mkdir_twice(abts_case *tc, void *data)
{
    apr_status_t rv;

    rv = apr_dir_make("data/testdir", APR_FPROT_UREAD | APR_FPROT_UWRITE | APR_FPROT_UEXECUTE,
                      p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_make("data/testdir", APR_FPROT_UREAD | APR_FPROT_UWRITE | APR_FPROT_UEXECUTE,
                      p);
    ABTS_INT_EQUAL(tc, 1, APR_STATUS_IS_EEXIST(rv));

    rv = apr_dir_remove("data/testdir", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
}

static void test_opendir(abts_case *tc, void *data)
{
    apr_status_t rv;
    apr_dir_t *dir;

    rv = apr_dir_open(&dir, "data", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    apr_dir_close(dir);
}

static void test_opendir_notthere(abts_case *tc, void *data)
{
    apr_status_t rv;
    apr_dir_t *dir;

    rv = apr_dir_open(&dir, "notthere", p);
    ABTS_INT_EQUAL(tc, 1, APR_STATUS_IS_ENOENT(rv));
}

static void test_closedir(abts_case *tc, void *data)
{
    apr_status_t rv;
    apr_dir_t *dir;

    rv = apr_dir_open(&dir, "data", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    rv = apr_dir_close(dir);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
}

static void test_rewind(abts_case *tc, void *data)
{
    apr_dir_t *dir;
    apr_finfo_t first, second;

    APR_ASSERT_SUCCESS(tc, "apr_dir_open failed", apr_dir_open(&dir, "data", p));

    APR_ASSERT_SUCCESS(tc, "apr_dir_read failed",
                       apr_dir_read(&first, APR_FINFO_DIRENT, dir));

    APR_ASSERT_SUCCESS(tc, "apr_dir_rewind failed", apr_dir_rewind(dir));

    APR_ASSERT_SUCCESS(tc, "second apr_dir_read failed",
                       apr_dir_read(&second, APR_FINFO_DIRENT, dir));

    APR_ASSERT_SUCCESS(tc, "apr_dir_close failed", apr_dir_close(dir));

    ABTS_STR_EQUAL(tc, first.name, second.name);
}

/* Test for a (fixed) bug in apr_dir_read().  This bug only happened
   in threadless cases. */
static void test_uncleared_errno(abts_case *tc, void *data)
{
    apr_file_t *thefile = NULL;
    apr_finfo_t finfo;
    apr_int32_t finfo_flags = APR_FINFO_TYPE | APR_FINFO_NAME;
    apr_dir_t *this_dir;
    apr_status_t rv; 

    rv = apr_dir_make("dir1", APR_FPROT_OS_DEFAULT, p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    rv = apr_dir_make("dir2", APR_FPROT_OS_DEFAULT, p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    rv = apr_file_open(&thefile, "dir1/file1",
                       APR_FOPEN_READ | APR_FOPEN_WRITE | APR_FOPEN_CREATE,
                       APR_FPROT_OS_DEFAULT, p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    rv = apr_file_close(thefile);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    /* Try to remove dir1.  This should fail because it's not empty.
       However, on a platform with threads disabled (such as FreeBSD),
       `errno' will be set as a result. */
    rv = apr_dir_remove("dir1", p);
    ABTS_INT_EQUAL(tc, 1, APR_STATUS_IS_ENOTEMPTY(rv));
    
    /* Read `.' and `..' out of dir2. */
    rv = apr_dir_open(&this_dir, "dir2", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    rv = apr_dir_read(&finfo, finfo_flags, this_dir);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    rv = apr_dir_read(&finfo, finfo_flags, this_dir);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    /* Now, when we attempt to do a third read of empty dir2, and the
       underlying system readdir() returns NULL, the old value of
       errno shouldn't cause a false alarm.  We should get an ENOENT
       back from apr_dir_read, and *not* the old errno. */
    rv = apr_dir_read(&finfo, finfo_flags, this_dir);
    ABTS_INT_EQUAL(tc, 1, APR_STATUS_IS_ENOENT(rv));

    rv = apr_dir_close(this_dir);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
		 
    /* Cleanup */
    rv = apr_file_remove("dir1/file1", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    rv = apr_dir_remove("dir1", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    rv = apr_dir_remove("dir2", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

}

static void test_rmkdir_nocwd(abts_case *tc, void *data)
{
    char *cwd, *path;

    APR_ASSERT_SUCCESS(tc, "make temp dir",
                       apr_dir_make("dir3", APR_FPROT_OS_DEFAULT, p));

    APR_ASSERT_SUCCESS(tc, "obtain cwd", apr_filepath_get(&cwd, 0, p));

    APR_ASSERT_SUCCESS(tc, "determine path to temp dir",
                       apr_filepath_merge(&path, cwd, "dir3", 0, p));

    APR_ASSERT_SUCCESS(tc, "change to temp dir", apr_filepath_set(path, p));

    APR_ASSERT_SUCCESS(tc, "restore cwd", apr_filepath_set(cwd, p));

    APR_ASSERT_SUCCESS(tc, "remove cwd", apr_dir_remove(path, p));
}

static void test_readmore_info(abts_case* tc, void* data)
{
    apr_status_t rv;
    apr_dir_t* dir;
    apr_file_t* thefile;
    apr_finfo_t finfo;
    /* Ask for information that is not stored in dirent. */
    apr_uint32_t wanted = APR_FINFO_MIN | APR_FINFO_OWNER;

    rv = apr_dir_make("dir1",
                      APR_FPROT_UREAD | APR_FPROT_UWRITE | APR_FPROT_UEXECUTE,
                      p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_file_open(&thefile, "dir1/file1",
                       APR_FOPEN_READ | APR_FOPEN_WRITE | APR_FOPEN_CREATE,
                       APR_FPROT_OS_DEFAULT, p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    rv = apr_file_close(thefile);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_file_open(&thefile, "dir1/file2",
                       APR_FOPEN_READ | APR_FOPEN_WRITE | APR_FOPEN_CREATE,
                       APR_FPROT_OS_DEFAULT, p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    rv = apr_file_close(thefile);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_open(&dir, "dir1", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    while (1) {
        rv = apr_dir_read(&finfo, wanted, dir);
        if (APR_STATUS_IS_ENOENT(rv))
            break;

        ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
        ABTS_TRUE(tc, finfo.valid & wanted);
    }

    apr_dir_close(dir);

    rv = apr_file_remove("dir1/file1", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_file_remove("dir1/file2", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = apr_dir_remove("dir1", p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
}

#if APR_POOL_DEBUG
static void test_pread(abts_case *tc, void *data)
{
    apr_dir_t *dir;
    apr_finfo_t finfo;
    apr_size_t before, after;
    apr_pool_t *subp;

    APR_ASSERT_SUCCESS(tc, "apr_dir_open failed", apr_dir_open(&dir, "data", p));
    
    apr_pool_create(&subp, p);

    before = apr_pool_num_bytes(p, 0);
    
    APR_ASSERT_SUCCESS(tc, "apr_dir_read failed",
                       apr_dir_pread(&finfo, APR_FINFO_DIRENT, dir, subp));

    after = apr_pool_num_bytes(p, 0);

    ABTS_PTR_EQUAL(tc, finfo.pool, subp);

    apr_pool_destroy(subp);
    
    APR_ASSERT_SUCCESS(tc, "apr_dir_close failed", apr_dir_close(dir));

    ABTS_INT_EQUAL(tc, before, after);
    
}
#endif

/* Ensure that apr_dir_read() doesn't have side-effects, because
 * finfo->name points to a static buffer inside the apr_dir_t */
static void test_read_side_effects(abts_case *tc, void *data)
{
    apr_dir_t *dir;
    apr_finfo_t f1;
    apr_finfo_t f2;
    char name[APR_PATH_MAX], fname[APR_PATH_MAX];

    APR_ASSERT_SUCCESS(tc, "apr_dir_open failed", apr_dir_open(&dir, "data", p));
    
    APR_ASSERT_SUCCESS(tc, "apr_dir_read failed",
                       apr_dir_read(&f1, APR_FINFO_DIRENT, dir));

    if (f1.name)
        apr_cpystrn(name, f1.name, sizeof name);
    if (f1.fname)
        apr_cpystrn(fname, f1.fname, sizeof fname);

    APR_ASSERT_SUCCESS(tc, "second apr_dir_read failed",
                       apr_dir_read(&f2, APR_FINFO_DIRENT, dir));

    if (f1.name)
        ABTS_STR_EQUAL(tc, name, f1.name);
    if (f1.fname)
        ABTS_STR_EQUAL(tc, fname, f1.fname);
    
    APR_ASSERT_SUCCESS(tc, "apr_dir_close failed", apr_dir_close(dir));
}

abts_suite *testdir(abts_suite *suite)
{
    suite = ADD_SUITE(suite)

    abts_run_test(suite, test_mkdir, NULL);
    abts_run_test(suite, test_mkdir_recurs, NULL);
    abts_run_test(suite, test_mkdir_recurs_parallel, NULL);
    abts_run_test(suite, test_remove, NULL);
    abts_run_test(suite, test_removeall_fail, NULL);
    abts_run_test(suite, test_removeall, NULL);
    abts_run_test(suite, test_remove_notthere, NULL);
    abts_run_test(suite, test_mkdir_twice, NULL);
    abts_run_test(suite, test_rmkdir_nocwd, NULL);

    abts_run_test(suite, test_rewind, NULL);

    abts_run_test(suite, test_opendir, NULL);
    abts_run_test(suite, test_opendir_notthere, NULL);
    abts_run_test(suite, test_closedir, NULL);
    abts_run_test(suite, test_uncleared_errno, NULL);
    abts_run_test(suite, test_readmore_info, NULL);
#if APR_POOL_DEBUG
    abts_run_test(suite, test_pread, NULL);
#endif
    abts_run_test(suite, test_read_side_effects, NULL);
    
    return suite;
}

